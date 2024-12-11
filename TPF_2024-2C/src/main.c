/** @file main.c
 ** @brief Definición de la función principal del programa
 **/
#include <signal.h>
#include <stdlib.h>

#include "logger.h"
#include "server.h"
#include "serverConfig.h"

void sigintHandler(int sigint);

server_t server = NULL;

int main(int argc, char* argv[])
{
  signal(SIGINT, sigintHandler);

  loggerInit();

  loggerInfo("Compilation Date %s - %s", __DATE__, __TIME__);

  server = setupServerSockets();

  if(NULL != server)
  {
    loopServerClients(server);
  }

  serverDeinit(server);
  loggerDeinit();
  return EXIT_SUCCESS;
}

void sigintHandler(int sigint)
{
  serverDeinit(server);
  loggerDeinit();
  exit(EXIT_SUCCESS);
}
