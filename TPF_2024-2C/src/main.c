/** @file main.c
 ** @brief Definición de la función principal del programa
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

// Estructura para representar la instancia Singleton
typedef struct
{
  int data;
} Singleton;

// Variable global para almacenar la instancia
static Singleton* instance = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Función para obtener la instancia (thread-safe)
Singleton* get_instance()
{
  pthread_mutex_lock(&mutex);
  if(instance == NULL)
  {
    instance = malloc(sizeof(Singleton));
    instance->data = 42;
  }
  pthread_mutex_unlock(&mutex);

  return instance;
}

int main(int argc, char* argv[])
{
  printf("Compilation Date %s - %s\n", __DATE__, __TIME__);

  Singleton* s1 = get_instance();
  Singleton* s2 = get_instance();
  logger_t logger = loggerInit();

  // Ambos apuntan a la misma instancia
  loggerInfo(logger,  "s1->data = %d, s2->data = %d\n", s1->data, s2->data);
  loggerDebug(logger, "*s1 = %p, *s2 = %p\n"          , (void*)s1, (void*)s2);

  // Liberar la memoria al finalizar
  free(instance);
  instance = NULL;
  loggerDeinit(logger);
  return EXIT_SUCCESS;
}
