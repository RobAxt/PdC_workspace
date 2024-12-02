/** @file server.c
 ** @brief Definición del objeto server
 **/
#include "serverConfig.h"
#include "serverStats.h"

typedef struct server_s
{
  serverConfig_t config;
  serverStat_t   stats;
  logger_t       logger;
};