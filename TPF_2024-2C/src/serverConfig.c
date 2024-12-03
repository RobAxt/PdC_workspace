/** @file serverConfig.c
 ** @brief Definición de la interface de configuracion del server
 **/
#include "serverConfig.h"

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
          break;

        default:
          line[lineIndex++] = readBuffer[i];
          if(lineIndex >= BUFFER_SIZE - 1)
            loggerFatal("Error al parsear linea, configuracion puede estar corrupta");
      }
    }
  }
  close(fd);
  loggerDebug("Finalizado carga de configuracion custom");
}

static void parseLine(char *line, serverConfig_t config)
{
  char *key = strtok(line, " =");
  char *value = strtok(NULL, " =");

  if(key && value)
  {
    // Compara la clave y asigna el valor a la estructura
    if(strcmp(key, "sensitive") == 0)
    {
      config->sensitive = (strcmp(value, "true") == 0);
    }
    else if(strcmp(key, "TCPPort") == 0)
    {
      config->TCPPort = atoi(value);
    }
    else if(strcmp(key, "UDPPort") == 0)
    {
      config->UDPPort = atoi(value);
    }
    else if(strcmp(key, "timeout") == 0)
    {
      config->timeout = atoi(value);
    }
    else
    {
      loggerWarn("Clave/Valor desconocido: %s = %s", key, value);
    }
    loggerInfo("Nueva configuracion: %s = %s", key, value);
  }
  else
    loggerError("Linea mal formada: %s", line);
}

bool isCaseSensitive(serverConfig_t server)
{
  return server->sensitive;
}

int getTCPPort(serverConfig_t server)
{
  return server->TCPPort;
}

int getUDPPort(serverConfig_t server)
{
  return server->UDPPort;
}

int getTimeout(serverConfig_t server)
{
  return server->timeout;
}
