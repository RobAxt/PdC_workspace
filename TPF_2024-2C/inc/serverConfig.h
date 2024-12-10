#ifndef _SERVERCONFIG_H_
#define _SERVERCONFIG_H_

/** @file serverConfig.h
 ** @brief Declaración de la interface de configuracion del server
 **/
#include <stdbool.h>

#define INVALID -1

typedef struct serverConfig_s* serverConfig_t;

/**
 * @brief Función para crear u obtener el objeto que representa la configuracion del server
 *
 * @param void
 * @return serverConfig_t Devuelve un puntero a una configuracion estandar o custom
 */
serverConfig_t initServerConfig(void);

/**
 * @brief
 *
 * @param serverConfig_t
 * @return bool
 */
bool isCaseSensitive(serverConfig_t server);

/**
 * @brief
 *
 * @param serverConfig_t
 * @return int
 */
int getTCPPort(serverConfig_t server);

/**
 * @brief
 *
 * @param serverConfig_t
 * @return int
 */
int getUDPPort(serverConfig_t server);

/**
 * @brief
 *
 * @param serverConfig_t
 * @return int
 */
int getTimeout(serverConfig_t server);

/**
 * @brief
 *
 * @param serverConfig_t
 * @param bool
 * @return bool
 */
int setCaseSensitive(serverConfig_t server, int sensitive);

/**
 * @brief
 *
 * @param serverConfig_t
 * @param int
 * @return int
 */
int setTCPPort(serverConfig_t server, int tcp);

/**
 * @brief
 *
 * @param serverConfig_t
 * @param int
 * @return int
 */
int setUDPPort(serverConfig_t server, int udp);

/**
 * @brief
 *
 * @param serverConfig_t
 * @param int
 * @return int
 */
int setTimeout(serverConfig_t server, int timeout);

/**
 * @brief
 *
 * @param serverConfig_t
 * @return void
 */
void serverConfigDeinit(serverConfig_t server);
#endif
