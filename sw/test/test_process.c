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
void test_Process(void **state) {

	// init all
	process_Init();

	// test after init
	assert_int_equal(0, 0);	
}

