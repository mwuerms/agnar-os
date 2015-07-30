/**
 * Martin Wuerms
 * 2015-07-23
 */

#ifndef _TEST_EVENT_QUEUE_H_
#define _TEST_EVENT_QUEUE_H_

/* - includes --------------------------------------------------------------- */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/* - defines ---------------------------------------------------------------- */

/* - typedefs --------------------------------------------------------------- */

/* - public functions ------------------------------------------------------- */
void test_eventQueue_Init(void **state);
void test_eventQueue_WriteFull(void **state);
void test_eventQueue_ReadEmpty(void **state);

#endif /* _TEST_EVENT_QUEUE_H_ */

