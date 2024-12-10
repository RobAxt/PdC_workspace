#ifndef _SERVER_H_
#define _SERVER_H_

/** @file server.h
 ** @brief Declaración de la interface server
 **/
typedef enum
{
  OK_SERVER = 0,
  NULL_SERVER,
  SOCKET_ERROR,
  BIND_ERROR,
  LISTEN_ERROR,
  POLL_ERROR,
  OOPS_ERROR
} serverStatus_t;
typedef struct server_s* server_t;

/**
 * @brief
 *
 * @param void
 * @return server_t
 */
server_t setupServerSockets(void);

/**
 * @brief
 *
 * @param server_t
 * @return serverStatus_t
 */
serverStatus_t loopServerClients(server_t server);

/**
 * @brief
 *
 * @param server_t
 * @return void
 */
void serverDeinit(server_t server);
#endif
