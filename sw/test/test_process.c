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

/* - test processes --------------------------------------------------------- */
static process_t pidle;
static char idle_name[] = "_idle_";
static int8_t idle_Process(uint8_t event, void *data) {
	printf("run idle process\n");
	return(1);
}

static process_t ptest1;
static char test1_name[] = "_test1_";
static int8_t test1_Process(uint8_t event, void *data) {
	static uint8_t count = 0;
	printf("test1, count: %d\n", count);
	if(count < 10) {
		count++;
		return(1);
	}
	printf("stop test1\n");
	return(0);
}



/* - public functions ------------------------------------------------------- */
void test_Process(void **state) {

	// init all
	process_Init();

	// add idle process
	pidle.process = idle_Process;
	pidle.name = idle_name;
	assert_int_equal(1, process_AddStartIdle(&pidle));
	assert_int_equal(0, pidle.pid);

	// add a test 1
	ptest1.process = test1_Process;
	ptest1.name = test1_name;
	assert_int_equal(1, process_Add(&ptest1));
	assert_int_equal(1, ptest1.pid);
	assert_int_equal(1, process_Start(ptest1.pid));
}

