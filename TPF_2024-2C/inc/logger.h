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

#define loggerTrace(...) loggerLog(TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define loggerDebug(...) loggerLog(DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define loggerInfo(...)  loggerLog(INFO, __FILE__, __LINE__, __VA_ARGS__)
#define loggerWarn(...)  loggerLog(WARN, __FILE__, __LINE__, __VA_ARGS__)
#define loggerError(...) loggerLog(ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define loggerFatal(...) loggerLog(FATAL, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Función para crear u obtener el logger del sistema
 *
 * @param void
 * @return bool Indicando si se pudo allocar o no el objeto
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
