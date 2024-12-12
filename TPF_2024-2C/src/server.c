/** @file server.c
 ** @brief Definición del objeto server
 **/
#include "server.h"

#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "handleTCPClient.h"
#include "logger.h"
#include "serverConfig.h"
#include "serverStats.h"

#define BUFFER_SIZE 256
#define MAX_CLIENTS 128
#define MAX_PENDING 128

struct server_s
{
  serverConfig_t config;
  serverStats_t stats;
  int tcpPassiveSocket;
  int udpSocket;
  struct pollfd pollfds[MAX_CLIENTS];
  int nfds;
  handleTCPClient_t TCPclientHandler[MAX_CLIENTS];
};

static server_t initServer();
static serverStatus_t setupTCPServerSocket(server_t server);
static serverStatus_t setupUDPServerSocket(server_t server);

server_t setupServerSockets(void)
{
  server_t this = initServer();

  if(NULL == this)
  {
    return NULL;
  }

  if(OK_SERVER != setupTCPServerSocket(this))
  {
    serverConfigDeinit(this->config);
    // serverStatsDeinit(this->stats);
    free(this);
    return NULL;
  }

  if(OK_SERVER != setupUDPServerSocket(this))
  {
    close(this->tcpPassiveSocket);
    serverConfigDeinit(this->config);
    // serverStatsDeinit(this->stats);
    free(this);
    return NULL;
  }

  return this;
}

static server_t initServer()
{
  server_t this = (server_t)malloc(sizeof(struct server_s));

  if(NULL == this)
  {
    loggerFatal("Imposible alocar memoria para el servidor");
    return NULL;
  }

  this->config = initServerConfig();
  if(NULL == this->config)
  {
    loggerFatal("Imposible inicializar configuracion del servidor");
    free(this);
    return NULL;
  }

  this->stats = NULL;
  // this->stats =  initServerStats();
  // if(NULL == this->stats)
  // {
  //   loggerFatal("Imposible inicializar estadisticas del servidor");
  //   serverConfigDeinit(this->config);
  //   free(this);
  //   return NULL;
  // }

  memset(this->pollfds, '\0', sizeof(this->pollfds));
  this->nfds = 0;

  memset(this->TCPclientHandler, '\0', sizeof(this->TCPclientHandler));

  return this;
}

static serverStatus_t setupTCPServerSocket(server_t server)
{
  struct sockaddr_in serverAddr;

  if((server->tcpPassiveSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    loggerFatal("Error al crear el socket TCP: %s", strerror(errno));
    return SOCKET_ERROR;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(getTCPPort(server->config));

  if(bind(server->tcpPassiveSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    close(server->tcpPassiveSocket);
    loggerFatal("Error de TCP Bind: %s", strerror(errno));
    return BIND_ERROR;
  }

  if(listen(server->tcpPassiveSocket, MAX_PENDING) < 0)
  {
    close(server->tcpPassiveSocket);
    loggerFatal("Error de Listen: %s", strerror(errno));
    return LISTEN_ERROR;
  }

  server->pollfds[server->nfds].fd = server->tcpPassiveSocket;
  server->pollfds[server->nfds].events = POLLIN;
  server->nfds++;

  loggerInfo("TCP Socket Listen to Port %d", getTCPPort(server->config));

  return OK_SERVER;
}

static serverStatus_t setupUDPServerSocket(server_t server)
{
  struct sockaddr_in serverAddr;

  if((server->udpSocket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
  {
    loggerFatal("Error al crear el socket UDP: %s", strerror(errno));
    return SOCKET_ERROR;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(getUDPPort(server->config));

  if(bind(server->udpSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    close(server->udpSocket);
    loggerFatal("Error de UDP Bind: %s", strerror(errno));
    return BIND_ERROR;
  }

  server->pollfds[server->nfds].fd = server->udpSocket;
  server->pollfds[server->nfds].events = POLLIN;
  server->nfds++;

  loggerInfo("UDP Socket Bind to Port %d", getUDPPort(server->config));
  return OK_SERVER;
}

serverStatus_t loopServerClients(server_t server)
{
  int new_socket = -1;
  struct sockaddr_in clientAddress;
  socklen_t clientAddressSize = sizeof(struct sockaddr_in);
  char buffer[BUFFER_SIZE] = {0};

  memset(&clientAddress, '\0', clientAddressSize);

  while(1)
  {
    int poll_count = poll(server->pollfds, server->nfds, -1);

    if(poll_count < 0)
    {
      close(server->udpSocket);
      close(server->tcpPassiveSocket);
      loggerFatal("Error de Poll: %s", strerror(errno));
      return POLL_ERROR;
    }

    for(int i = 0; i < server->nfds; i++)
    {
      if(server->pollfds[i].revents & POLLIN)
      {
        if(server->pollfds[i].fd == server->tcpPassiveSocket)
        {
          // Aceptar nueva conexión TCP
          new_socket = accept(server->tcpPassiveSocket, (struct sockaddr *)&clientAddress,
                              (socklen_t *)&clientAddressSize);
          if(new_socket < 0)
          {
            loggerError("Error al aceptar conexión TCP: %s", strerror(errno));
            continue;
          }
          loggerInfo("Nueva conexión TCP aceptada");

          // Añadir nuevo socket al conjunto de poll
          server->pollfds[server->nfds].fd = new_socket;
          server->pollfds[server->nfds].events = POLLIN;
          server->TCPclientHandler[server->nfds] = handleTCPClientInit(server->config);
          server->nfds++;
        }
        else if(server->pollfds[i].fd == server->udpSocket)
        {
          // Leer datos del socket UDP
          int len = recvfrom(server->udpSocket, buffer, BUFFER_SIZE - 1, 0,
                             (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressSize);
          if(len < 0)
          {
            loggerError("Error al recibir datos UDP: %s", strerror(errno));
            continue;
          }
          buffer[len] = '\0';
          loggerDebug("Mensaje UDP recibido: %s", buffer);

          // Responder al cliente UDP
          sendto(server->udpSocket, "Mensaje recibido\r\n", strlen("Mensaje recibido\r\n"), 0,
                 (struct sockaddr *)&clientAddress, clientAddressSize);
        }
        else
        {
          // Leer datos del socket TCP
          int len = read(server->pollfds[i].fd, buffer, BUFFER_SIZE - 1);
          if(len <= 0)
          {
            // Cerrar conexión TCP
            loggerInfo("Conexión cerrada");
            close(server->pollfds[i].fd);
            handleTCPClientDeinit(server->TCPclientHandler[i]);
            server->nfds--;
            server->pollfds[i] = server->pollfds[server->nfds];
            server->TCPclientHandler[i] = server->TCPclientHandler[server->nfds];
          }
          else
          {
            buffer[len] = '\0';
            loggerDebug("Mensaje TCP recibido: %s", buffer);
            handleTCPClientInsert(server->TCPclientHandler[server->nfds], buffer, len);
            send(server->pollfds[i].fd, "Mensaje recibido\r\n", strlen("Mensaje recibido\r\n"), 0);
          }
        }
      }
    }
  }
  return OOPS_ERROR;
}

void serverDeinit(server_t server)
{
  if(NULL != server)
  {
    for(int i = 0; i < server->nfds; i++)
    {
      close(server->pollfds[i].fd);
      handleTCPClientDeinit(server->TCPclientHandler[i]);
    }
    serverConfigDeinit(server->config);
    // serverStatsDeinit(server->stats);
    free(server);
  }
}
