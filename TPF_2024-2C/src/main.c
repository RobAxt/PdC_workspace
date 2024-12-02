/** @file main.c
 ** @brief Definición de la función principal del programa
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

int main(int argc, char* argv[])
{
  loggerInit();

  loggerInfo("Compilation Date %s - %s\r\n", __DATE__, __TIME__);

  loggerDeinit();
  return EXIT_SUCCESS;
}
