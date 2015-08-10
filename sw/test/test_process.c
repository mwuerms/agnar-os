/**
 * Martin Wuerms
 * 2015-08-10
 */

/* - includes --------------------------------------------------------------- */
#include <stdio.h>
#include <stdint.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "process.h"

/* - public functions ------------------------------------------------------- */
void test_Fifo(void **state) {

	// init all
	fifo_Init(&findex, FIFO_SIZE);
	memset(fifo_data, 0, sizeof(fifo_data));
	memset(test_memory, 0, sizeof(test_memory));

	// test after init
	assert_int_equal(0, findex.write);
	assert_int_equal(0, findex.read);
	assert_int_equal(0, findex.length);
	assert_int_equal(FIFO_SIZE, findex.size);
	
	// write to fifo
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(1, findex.write);
	assert_int_equal(1, findex.length);
	fifo_data[findex.write] = 1;
	test_memory[1] = 1;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(2, findex.write);
	assert_int_equal(2, findex.length);
	fifo_data[findex.write] = 2;
	test_memory[2] = 2;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(3, findex.write);
	assert_int_equal(3, findex.length);
	fifo_data[findex.write] = 3;
	test_memory[3] = 3;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(4, findex.write);
	assert_int_equal(4, findex.length);
	fifo_data[findex.write] = 4;
	test_memory[4] = 4;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(5, findex.write);
	assert_int_equal(5, findex.length);
	fifo_data[findex.write] = 5;
	test_memory[5] = 5;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(6, findex.write);
	assert_int_equal(6, findex.length);
	fifo_data[findex.write] = 6;
	test_memory[6] = 6;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	// write successful
	
	// read from fifo
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(1, findex.read);
	assert_int_equal(5, findex.length);
	assert_int_equal(1, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[1] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(2, findex.read);
	assert_int_equal(4, findex.length);
	assert_int_equal(2, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[2] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(3, findex.read);
	assert_int_equal(3, findex.length);
	assert_int_equal(3, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[3] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(4, findex.read);
	assert_int_equal(2, findex.length);
	assert_int_equal(4, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[4] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(5, findex.read);
	assert_int_equal(1, findex.length);
	assert_int_equal(5, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[5] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(6, findex.read);
	assert_int_equal(0, findex.length);
	assert_int_equal(6, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[6] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	// read successful
	
	
	// read fails, fifo empty
	assert_int_equal(0, fifo_IncReadIndex(&findex));
	assert_int_equal(6, findex.read);
	assert_int_equal(0, findex.length);
	
	assert_int_equal(0, fifo_IncReadIndex(&findex));
	assert_int_equal(6, findex.read);
	assert_int_equal(0, findex.length);
	
	
	// write until fifo is full
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(7, findex.write);
	assert_int_equal(1, findex.length);
	fifo_data[findex.write] = 1;
	test_memory[7] = 1;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(8, findex.write);
	assert_int_equal(2, findex.length);
	fifo_data[findex.write] = 2;
	test_memory[8] = 2;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(9, findex.write);
	assert_int_equal(3, findex.length);
	fifo_data[findex.write] = 3;
	test_memory[9] = 3;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(10, findex.write);
	assert_int_equal(4, findex.length);
	fifo_data[findex.write] = 4;
	test_memory[10] = 4;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(11, findex.write);
	assert_int_equal(5, findex.length);
	fifo_data[findex.write] = 5;
	test_memory[11] = 5;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(12, findex.write);
	assert_int_equal(6, findex.length);
	fifo_data[findex.write] = 6;
	test_memory[12] = 6;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(13, findex.write);
	assert_int_equal(7, findex.length);
	fifo_data[findex.write] = 7;
	test_memory[13] = 7;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(14, findex.write);
	assert_int_equal(8, findex.length);
	fifo_data[findex.write] = 8;
	test_memory[14] = 8;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(15, findex.write);
	assert_int_equal(9, findex.length);
	fifo_data[findex.write] = 9;
	test_memory[15] = 9;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(0, findex.write);
	assert_int_equal(10, findex.length);
	fifo_data[findex.write] = 10;
	test_memory[0] = 10;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(1, findex.write);
	assert_int_equal(11, findex.length);
	fifo_data[findex.write] = 11;
	test_memory[1] = 11;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(2, findex.write);
	assert_int_equal(12, findex.length);
	fifo_data[findex.write] = 12;
	test_memory[2] = 12;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(3, findex.write);
	assert_int_equal(13, findex.length);
	fifo_data[findex.write] = 13;
	test_memory[3] = 13;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(4, findex.write);
	assert_int_equal(14, findex.length);
	fifo_data[findex.write] = 14;
	test_memory[4] = 14;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(5, findex.write);
	assert_int_equal(15, findex.length);
	fifo_data[findex.write] = 15;
	test_memory[5] = 15;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncWriteIndex(&findex));
	assert_int_equal(6, findex.write);
	assert_int_equal(16, findex.length);
	fifo_data[findex.write] = 16;
	test_memory[6] = 16;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	// fifo is full, IncWriteIndex will fail
	assert_int_equal(0, fifo_IncWriteIndex(&findex));
	assert_int_equal(6, findex.write);
	assert_int_equal(16, findex.length);
	
	assert_int_equal(0, fifo_IncWriteIndex(&findex));
	assert_int_equal(6, findex.write);
	assert_int_equal(16, findex.length);
	// fifo is full
	
	
	
	// read until fifo is empty
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(7, findex.read);
	assert_int_equal(15, findex.length);
	assert_int_equal(1, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[7] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(8, findex.read);
	assert_int_equal(14, findex.length);
	assert_int_equal(2, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[8] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(9, findex.read);
	assert_int_equal(13, findex.length);
	assert_int_equal(3, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[9] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(10, findex.read);
	assert_int_equal(12, findex.length);
	assert_int_equal(4, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[10] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(11, findex.read);
	assert_int_equal(11, findex.length);
	assert_int_equal(5, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[11] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(12, findex.read);
	assert_int_equal(10, findex.length);
	assert_int_equal(6, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[12] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(13, findex.read);
	assert_int_equal(9, findex.length);
	assert_int_equal(7, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[13] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(14, findex.read);
	assert_int_equal(8, findex.length);
	assert_int_equal(8, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[14] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(15, findex.read);
	assert_int_equal(7, findex.length);
	assert_int_equal(9, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[15] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(0, findex.read);
	assert_int_equal(6, findex.length);
	assert_int_equal(10, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[0] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(1, findex.read);
	assert_int_equal(5, findex.length);
	assert_int_equal(11, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[1] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(2, findex.read);
	assert_int_equal(4, findex.length);
	assert_int_equal(12, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[2] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(3, findex.read);
	assert_int_equal(3, findex.length);
	assert_int_equal(13, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[3] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(4, findex.read);
	assert_int_equal(2, findex.length);
	assert_int_equal(14, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[4] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(5, findex.read);
	assert_int_equal(1, findex.length);
	assert_int_equal(15, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[5] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	assert_int_equal(1, fifo_IncReadIndex(&findex));
	assert_int_equal(6, findex.read);
	assert_int_equal(0, findex.length);
	assert_int_equal(16, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[6] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	
	// fifo is empty now
	assert_int_equal(0, fifo_IncReadIndex(&findex));
	assert_int_equal(6, findex.read);
	assert_int_equal(0, findex.length);
	assert_int_equal(0, fifo_data[findex.read]);
	fifo_data[findex.read] = 0;
	test_memory[6] = 0;
	assert_memory_equal(test_memory, fifo_data, sizeof(uint8_t)*FIFO_SIZE);
	// reading fifo done
	
}

