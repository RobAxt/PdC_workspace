#ifndef _SERVERCONFIG_H_
#define _SERVERCONFIG_H_

/** @file serverConfig.h
 ** @brief Declaración de la interface de configuracion del server
 **/
#include <stdbool.h>

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
#endif
