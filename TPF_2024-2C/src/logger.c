/** @file logger.c
 ** @brief Definición del objeto logger
 **/
 
#include "logger.h"
#include <pthread.h>
#include <stdio.h>

#define LOGGER_FILENAME "./log/pdcServer.log"

const char * levelNames[] = { "TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "FATAL" };

struct logger_h
{
  int fd;  
};

static logger_t instance = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

logger_t loggerInit(void)
{
  pthread_mutex_lock(&mutex);
  if(NULL == instance)
  {
    instance = malloc(sizeof(struct logger_h));
    instance->fd = open(LOGGER_FILENAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd <= 0)
    {
      perror("[ERROR] Error opening file for writing");
      free(instance);
      instance = NULL;
    }
  }
  pthread_mutex_unlock(&mutex);

  return instance;
}

void loggerLog(level_t level, const char *file, int line, logger_t logger,  const char *fmt, ...)
{
  if( NULL == logger)
  {
     fprintf(stderr, "[ERROR] NULL Pointer Logger");
     return;
  }
  
  pthread_mutex_lock(&mutex);
  
  dprintf(logger->fd, "[%s] %s:%d - %s", levelNames[level], file, line, fmt);
  
  pthread_mutex_unlock(&mutex);
}

void loggerDeinit(logger_t logger)
{
  pthread_mutex_lock(&mutex);
  if(NULL != logger)
  {
    free(instance);
    instance = NULL;
  }
  pthread_mutex_unlock(&mutex);
}