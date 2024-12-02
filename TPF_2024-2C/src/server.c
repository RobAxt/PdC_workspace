/** @file server.c
 ** @brief Definición del objeto server
 **/
#include "logger.h"
#include "serverConfig.h"
#include "serverStats.h"

typedef struct server_s
{
  serverConfig_t config;
  serverStats_t stats;
};
