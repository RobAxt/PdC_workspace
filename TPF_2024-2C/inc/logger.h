#ifndef _LOGGER_H_
#define _LOGGER_H_

/** @file logger.h
 ** @brief Declaración de la interface logger
 **/

#include <stdbool.h>

typedef struct logger_s *logger_t;
typedef enum
{
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL
} level_t;

#define loggerTrace(logger, ...) loggerLog(TRACE, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerDebug(logger, ...) loggerLog(DEBUG, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerInfo(logger, ...)  loggerLog(INFO, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerWarn(logger, ...)  loggerLog(WARN, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerError(logger, ...) loggerLog(ERROR, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerFatal(logger, ...) loggerLog(FATAL, __FILE__, __LINE__, logger, __VA_ARGS__)

/**
 * @brief Función para crear u obtener el logger del sistema
 *
 * @param void
 * @return bool indicando si se pudo allocar o no el objeto
 */
bool loggerInit(void);

/**
 * @brief Función base para realizar el loggeo
 *
 * @param level Nivel de Log
 * @param file  Nombre del archivo desde el cual se invoco el logger
 * @param line  Línea desde la cual se invoco el logger
 * @param logger Puntero al logger del sistema
 * @param fmt   Cadena de caracteres a loggear
 * @return void
 */
void loggerLog(level_t level, const char *file, int line, const char *fmt, ...);

/**
 * @brief Función para desalocar los datos del logger del sistema
 *
 * @param logger_t Puntero al logger del sistema
 * @return void
 */
void loggerDeinit(void);
#endif
