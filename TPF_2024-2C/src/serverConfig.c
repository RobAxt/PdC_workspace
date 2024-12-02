/** @file serverConfig.c
 ** @brief Definición de la interface de configuracion del server
 **/
#include "serverConfig.h"

#include "logger.h"

const char* const CONFIG_FILENAME = "./config/pdcServer.cfg";

const int DEFAULT_TCP_PORT = 9999;
const int DEFAULT_UDP_PORT = 9999;
const bool DEFAULT_SENSITVE = false;
const int DEFAULT_CLIENT_TIMEOUT = 60;

typedef struct serverConfig_s
{
  bool sensitive;
  int TCPPort;
  int UDPPort;
  int timeout;
  logger_t logger;
};
