#include "circularBuffer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

struct circularBuffer_s
{
  char data[BUFFER_SIZE];
  int head;
  int tail;
  int size;
};

circularBuffer_t bufferInit(void)
{
  circularBuffer_t buffer = (circularBuffer_t)malloc(sizeof(struct circularBuffer_s));

  if(NULL != buffer)
  {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->size = 0;

    return buffer;
  }

  return NULL;
}

bool bufferIsFull(circularBuffer_t buffer)
{
  if(NULL != buffer)
    return buffer->size == BUFFER_SIZE;
  return false;
}

bool bufferIsEmpty(circularBuffer_t buffer)
{
  if(NULL != buffer)
    return buffer->size == 0;
  return false;
}

bool bufferInsertArray(circularBuffer_t buffer, const char *array, int length)
{
  if(NULL == buffer && buffer->size + length > BUFFER_SIZE)
    return false;

  for(int i = 0; i < length; i++)
  {
    buffer->data[buffer->head] = array[i];
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;
  }

  buffer->size += length;
  return true;
}

bool bufferExtractChar(circularBuffer_t buffer, char *c)
{
  if(NULL == buffer && bufferIsEmpty(buffer))
    return false;

  *c = buffer->data[buffer->tail];
  buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
  buffer->size--;
  return true;
}

void bufferDeinit(circularBuffer_t buffer)
{
  if(NULL != buffer)
    free(buffer);
}
