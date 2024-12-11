#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

/** @file circularBuffer.h
 ** @brief Declaración de objeto circular buffer
 **/

#include <stdbool.h>

typedef struct circularBuffer_s *circularBuffer_t;

/**
 * @brief
 *
 * @param void
 * @return circularBuffer_t
 */
circularBuffer_t bufferInit(void);

/**
 * @brief
 *
 * @param circularBuffer_t
 * @return bool
 */
bool bufferIsFull(circularBuffer_t buffer);

/**
 * @brief
 *
 * @param circularBuffer_t
 * @return bool
 */
bool bufferIsEmpty(circularBuffer_t buffer);

/**
 * @brief
 *
 * @param circularBuffer_t
 * @param const char *
 * @param int
 * @return bool
 */
bool bufferInsertArray(circularBuffer_t buffer, const char *array, int length);

/**
 * @brief
 *
 * @param circularBuffer_t
 * @param const char *
 * @return bool
 */
bool bufferExtractChar(circularBuffer_t buffer, char *c);

/**
 * @brief
 *
 * @param circularBuffer_t
 * @return void
 */
void bufferDeinit(circularBuffer_t buffer);

#endif
