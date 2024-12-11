/** @file handleTCPClient.c
 ** @brief Definición del manejador del cliente TCP
 **/
#include "handleTCPClient.h"

#include <stdlib.h>
#include <unistd.h>

#include "circularBuffer.h"
#include "logger.h"

struct handleTCPClient_s
{
  circularBuffer_t cmndBuffer;
  serverConfig_t config;
  bool isAuth;
};

handleTCPClient_t handleTCPClientInit(serverConfig_t config)
{
  handleTCPClient_t this = (handleTCPClient_t)malloc(sizeof(struct handleTCPClient_s));

  if(NULL == this)
  {
    loggerFatal("Imposible alocar memoria para el manejador");
    return NULL;
  }

  this->cmndBuffer = bufferInit();
  if(NULL == this->cmndBuffer)
  {
    loggerFatal("Imposible alocar memoria para el buffer");
    return NULL;
  }

  this->config = config;
  this->isAuth = false;

  return this;
}

bool handleTCPClientInsert(handleTCPClient_t client, char* array, int length)
{
  if(NULL != client && NULL != array && 0 != length)
  {
    return bufferInsertArray(client->cmndBuffer, array, length);
  }

  return false;
}

void handleTCPClientDeinit(handleTCPClient_t client)
{
  if(NULL != client)
  {
    bufferDeinit(client->cmndBuffer);
    free(client);
  }
}
