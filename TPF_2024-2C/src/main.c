/** @file main.c
 ** @brief Definición de la función principal del programa
 **/
#include <stdlib.h>

#include "logger.h"
#include "server.h"
#include "serverConfig.h"

int main(int argc, char* argv[])
{
  loggerInit();

  loggerInfo("Compilation Date %s - %s", __DATE__, __TIME__);

  server_t server = setupServerSockets();

  if(NULL != server)
  {
    loopServerClients(server);
  }

  serverDeinit(server);
  loggerDeinit();
  return EXIT_SUCCESS;
}
