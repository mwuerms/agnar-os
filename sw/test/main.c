/**
 * Martin Wuerms
 * 2015-07-30
 * main test file for unit tests
 */

/* - includes --------------------------------------------------------------- */
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "version.h"

/* - includes test units ---------------------------------------------------- */
#include "test_fifo.h"
#include "test_process.h"

/* - public functions ------------------------------------------------------- */
/**
 * main loop: run tests
 */
int main(void) 
{
    printf("unit tests for cooperative os, version: %s\n\n", cVERSION);
    const UnitTest tests[] = 
    {
        unit_test(test_Fifo),
        unit_test(test_Process),
    };
    return run_tests(tests);
}

