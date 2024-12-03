/** @file serverConfig.c
 ** @brief Definición de la interface de configuracion del server
 **/
#include "serverConfig.h"

#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"

#define BUFFER_SIZE 32

const char *const CONFIG_FILENAME = "./config/pdcServer.cfg";

const int DEFAULT_TCP_PORT = 9999;
const int DEFAULT_UDP_PORT = 9999;
const bool DEFAULT_SENSITVE = false;
const int DEFAULT_CLIENT_TIMEOUT = 60;

struct serverConfig_s
{
  bool sensitive;
  int TCPPort;
  int UDPPort;
  int timeout;
};

typedef int (*action_t)(serverConfig_t server, int value);

typedef struct
{
  char *key;
  action_t action;
} command_t;

static command_t commands[] = {{"sensitive", setCaseSensitive},
                               {"TCPPort", setTCPPort},
                               {"UDPPort", setUDPPort},
                               {"timeout", setTimeout}};

static const int MAX_CMND = sizeof(commands) / sizeof(command_t);

static void loadFileConfig(serverConfig_t config);
static void parseLine(char *line, serverConfig_t config);

serverConfig_t initServerConfig(void)
{
  serverConfig_t this = (serverConfig_t)malloc(sizeof(struct serverConfig_s));

  if(NULL == this)
  {
    loggerFatal("Imposible alocar memoria para la configuracion del servidor");
    exit(EXIT_FAILURE);
  }

  this->sensitive = DEFAULT_SENSITVE;
  this->TCPPort = DEFAULT_TCP_PORT;
  this->UDPPort = DEFAULT_UDP_PORT;
  this->timeout = DEFAULT_CLIENT_TIMEOUT;

  loadFileConfig(this);

  return this;
}

static void loadFileConfig(serverConfig_t config)
{
  char readBuffer[BUFFER_SIZE] = {0};
  char line[BUFFER_SIZE] = {0};
  ssize_t bytesRead = 0;
  int lineIndex = 0;

  int fd = open(CONFIG_FILENAME, O_RDONLY);

  if(fd <= 0)
  {
    loggerWarn("Imposible leer archivo de configuracion, usando configuraciones default");
    return;
  }

  while((bytesRead = read(fd, readBuffer, BUFFER_SIZE - 1)) > 0)
  {
    readBuffer[bytesRead] = '\0';

    for(int i = 0; i < bytesRead; i++)
    {
      switch(readBuffer[i])
      {
        case '\n':
          line[lineIndex] = '\0';
          if(lineIndex > 0)
            parseLine(line, config);
          lineIndex = 0;
          memset(line, '\0', BUFFER_SIZE);
          break;

        case '\r':
        case ' ':
          break;

        default:
          line[lineIndex++] = readBuffer[i];
          if(lineIndex > BUFFER_SIZE)
          {
            loggerFatal("Linea excede los %d caracteres, configuracion puede estar corrupta",
                        BUFFER_SIZE);
            lineIndex = 0;
            memset(line, '\0', BUFFER_SIZE);
          }
      }
    }
  }
  close(fd);
  loggerDebug("Finalizado carga de configuracion custom");
}

static void parseLine(char *line, serverConfig_t config)
{
  char *key = strtok(line, "=");
  char *value = strtok(NULL, "=");
  int cmndIdx = 0;

  if(key && value)
  {
    while(cmndIdx < MAX_CMND)
    {
      if(strcmp(key, commands[cmndIdx].key) == 0)
      {
        commands[cmndIdx].action(config,
                                 isalpha(*value) ? (int)(strcmp(value, "true") == 0) : atoi(value));
        break;
      }
      cmndIdx++;
    }

    if(cmndIdx == MAX_CMND)
      loggerError("Clave/Valor desconocido: %s = %s", key, value);
    else
      loggerInfo("Nueva configuracion: %s = %s", key, value);
  }
  else
    loggerError("Linea mal formada: %s", line);
}

bool isCaseSensitive(serverConfig_t server)
{
  if(NULL != server)
    return server->sensitive;
  return false;
}

int getTCPPort(serverConfig_t server)
{
  if(NULL != server)
    return server->TCPPort;
  return INVALID;
}

int getUDPPort(serverConfig_t server)
{
  if(NULL != server)
    return server->UDPPort;
  return INVALID;
}

int getTimeout(serverConfig_t server)
{
  if(NULL != server)
    return server->timeout;
  return INVALID;
}

int setCaseSensitive(serverConfig_t server, int sensitive)
{
  if(NULL != server)
  {
    server->sensitive = (bool)sensitive;
    return sensitive;
  }
  return INVALID;
}

int setTCPPort(serverConfig_t server, int tcp)
{
  if(NULL != server)
  {
    server->TCPPort = tcp;
    return tcp;
  }
  return INVALID;
}

int setUDPPort(serverConfig_t server, int udp)
{
  if(NULL != server)
  {
    server->UDPPort = udp;
    return udp;
  }
  return INVALID;
}

int setTimeout(serverConfig_t server, int timeout)
{
  if(NULL != server)
  {
    server->timeout = timeout;
    return timeout;
  }
  return INVALID;
}

void serverConfigDeinit(serverConfig_t server)
{
  if(NULL != server)
  {
    free(server);
  }
}
