/**
 * Martin Wuerms
 * 2015-08-10
 */

#ifndef _FIFO_H_
#define _FIFO_H_

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include <string.h>

/* - typedef ---------------------------------------------------------------- */
typedef struct {
	uint8_t write;	/// write index
	uint8_t read;	/// read index
	uint8_t length;	/// length of fifo
	uint8_t size;	/// size, numbers of elements
} fifo_index_t;

/* - public functions ------------------------------------------------------- */

void fifo_Init(fifo_index_t *fi, uint8_t size);
int8_t fifo_IsFull(fifo_index_t *fi);
int8_t fifo_IsEmpty(fifo_index_t *fi);
int8_t fifo_IncWriteIndex(fifo_index_t *fi);
int8_t fifo_IncReadIndex(fifo_index_t *fi);
uint8_t fifo_IncUint8(uint8_t value, uint8_t max);

#endif /* _FIFO_H_ */
