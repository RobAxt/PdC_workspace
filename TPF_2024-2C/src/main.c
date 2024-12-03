/** @file main.c
 ** @brief Definición de la función principal del programa
 **/
#include <stdlib.h>

#include "logger.h"
#include "serverConfig.h"

int main(int argc, char* argv[])
{
  loggerInit();

  loggerInfo("Compilation Date %s - %s", __DATE__, __TIME__);

  serverConfig_t config = initServerConfig();

  serverConfigDeinit(config);
  loggerDeinit();
  return EXIT_SUCCESS;
}
