#ifndef _HANDLETCPCLIENT_H_
#define _HANDLETCPCLIENT_H_

/** @file logger.h
 ** @brief Declaración del manejador del cliente tcp
 **/

#include <stdbool.h>

#include "serverConfig.h"

typedef struct handleTCPClient_s* handleTCPClient_t;

/**
 * @brief
 *
 * @param serverConfig_t
 * @return handleTCPClient_t
 */
handleTCPClient_t handleTCPClientInit(serverConfig_t config);

/**
 * @brief
 *
 * @param handleTCPClient_t
 * @param char *
 * @param int
 * @return bool
 */
bool handleTCPClientInsert(handleTCPClient_t client, char* array, int length);

/**
 * @brief
 *
 * @param handleTCPClient_t
 * @return void
 */
void handleTCPClientDeinit(handleTCPClient_t client);

#endif
