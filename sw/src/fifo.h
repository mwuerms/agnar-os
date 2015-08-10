/**
 * Martin Wuerms
 * 2015-08-10
 */

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

/**
 * increment an unsigned int 8 bit value from 0 ... max (maximum)
 * @param	value	to increment
 * @param	max		maximum to increment to
 * @return	next value
 */
inline uint8_t _IncUint8(uint8_t value, uint8_t max) {
	if(value < max) {
		return(value + 1);
	}
	return(0);
}

/**
 * initialize the fifo
 * @param	fi		pointer to fifo indexes
 * @param	size	set size of fifo
 */
inline void fifo_Init(fifo_index_t *fi, uint8_t size) {
	memset(fi, 0, sizeof(*fi));
	fi->size = size;
}

/**
 * check if fifo is full
 * @param	fi		pointer to fifo indexes
 * @return 	=1: fifo is full, 
 *			=0: fifo is not full
 */
inline int8_t fifo_IsFull(fifo_index_t *fi) {
	if(fi->length < fi->size) {
		// fifo is not full
		return(0);
	}
	// fifo is full
	return(1);
}

/**
 * check if fifo is empty
 * @param	fi		pointer to fifo indexes
 * @return 	=1: fifo is empty, 
 *			=0: fifo is not empty
 */
inline int8_t fifo_IsEmpty(fifo_index_t *fi) {
	if(fi->length > 0) {
		// fifo is not empty
		return(0);
	}
	// fifo is empty
	return(1);
}

/**
 * write to the fifo, so calc next write index
 * @param	fi		pointer to fifo indexes
 * @return	=1: OK, write pointer incremented
 *			=0: error, fifo is full, cannot write
 */
inline int8_t fifo_IncWriteIndex(fifo_index_t *fi) {
	if(fifo_IsFull(fi) == 1) {
		// fifo is full, cannot write
		return(0);
	}
	
	fi->write = _IncUint8(fi->write, (fi->size)-1);
	fi->length++;
	return(1);
}

/**
 * read from the fifo, so calc next read index
 * @param	fi		pointer to fifo indexes
 * @return	=1: OK, read pointer incremented
 *			=0: error, fifo is empty, cannot read
 */
inline int8_t fifo_IncReadIndex(fifo_index_t *fi) {
	if(fifo_IsEmpty(fi) == 1) {
		// fifo is empty, cannot read
		return(0);
	}
	
	fi->read = _IncUint8(fi->read, (fi->size)-1);
	fi->length--;
	return(1);
}

