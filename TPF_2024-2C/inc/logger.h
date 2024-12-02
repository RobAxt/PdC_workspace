#ifndef _LOGGER_H_
#define _LOGGER_H_

/** @file logger.h
 ** @brief Declaración de la interface logger
 **/
 
typedef struct logger_s * logger_t;
typedef enum { TRACE, DEBUG, INFO, WARN, ERROR, FATAL } level_t;

#define loggerTrace(logger_t logger, ...) loggerLog(TRACE, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerDebug(logger_t logger, ...) loggerLog(DEBUG, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerInfo(logger_t logger, ...)  loggerLog(INFO,  __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerWarn(logger_t logger, ...)  loggerLog(WARN,  __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerError(logger_t logger, ...) loggerLog(ERROR, __FILE__, __LINE__, logger, __VA_ARGS__)
#define loggerFatal(logger_t logger,...)  loggerLog(FATAL, __FILE__, __LINE__, logger, __VA_ARGS__)

/**
 * @brief Función para crear u obtener el logger del sistema 
 *
 * @param void
 * @return logger_t Puntero al objeto creado
 */
logger_t loggerInit(void);

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
void loggerLog(level_t level, const char *file, int line, logger_t logger,  const char *fmt, ...);

/**
 * @brief Función para desalocar los datos del logger del sistema
 *
 * @param logger_t Puntero al logger del sistema
 * @return void
 */
void loggerDeinit(logger_t logger);
#endif