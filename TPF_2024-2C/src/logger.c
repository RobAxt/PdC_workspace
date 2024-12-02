/** @file logger.c
 ** @brief Definición del objeto logger
 **/

#include "logger.h"

#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SUBMESSAGE_SIZE 128

const char *const LOGGER_FILENAME = "./log/pdcServer.log";
const char *levelNames[] = {"TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "FATAL"};

struct logger_s
{
  int fd;
};

static logger_t instance = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

bool loggerInit(void)
{
  pthread_mutex_lock(&mutex);
  if(NULL == instance)
  {
    instance = (logger_t)malloc(sizeof(struct logger_s));
    instance->fd = open(LOGGER_FILENAME, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if(instance->fd <= 0)
    {
      perror("[ERROR] Error opening file for writing");
      free(instance);
      instance = NULL;
    }
  }
  pthread_mutex_unlock(&mutex);

  return (NULL != instance);
}

void loggerLog(level_t level, const char *file, int line, const char *fmt, ...)
{
  char message[SUBMESSAGE_SIZE] = {0};

  if(NULL == instance)
  {
    fprintf(stderr, "[ERROR] NULL Pointer Logger\r\n");
    return;
  }

  pthread_mutex_lock(&mutex);

  va_list args;
  va_start(args, fmt);
  vsprintf(message, fmt, args);
  va_end(args);

  dprintf(instance->fd, "[%s] %s:%d - %s", levelNames[level], file, line, message);

  pthread_mutex_unlock(&mutex);
}

void loggerDeinit(void)
{
  pthread_mutex_lock(&mutex);
  if(NULL != instance)
  {
    close(instance->fd);
    free(instance);
    instance = NULL;
  }
  pthread_mutex_unlock(&mutex);
}
