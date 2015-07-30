/**
 * Martin Wuerms
 * 2015-07-23
 */

/* - includes --------------------------------------------------------------- */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/eventQueue.h"

/* - defines ---------------------------------------------------------------- */

/* - typedefs --------------------------------------------------------------- */

/* - public functions ------------------------------------------------------- */
void test_eventQueue(void **state)
{
    assert_int_equal(3, 3);
    assert_int_not_equal(3, 3);
}
#if 0

int8_t test1(uint8_t event, void *data) {
	printf("call test1, event: %d, data: %p\n", event, data);
	return(-1);
}

int main(void) {

	printf("== TEST evQueue ==\n");
	event_t ev = {.data = NULL, .pid = 1, .event = 1};
	int8_t ret;
	evQueue_Init();

	printf("evQueue_Get() from empty event queue, should not work = return = 0\n");
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());


	printf("evQueue_Push()\n");
	ev.event = 1;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 2;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 3;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 4;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 5;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 6;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 7;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 8;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 9;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 10;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 11;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 12;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 13;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 14;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 15;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 16;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 17;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 18;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 19;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());
	ev.event = 20;
	ret = evQueue_Push(&ev);
	printf("evQueue_Push: %d, ev.event: %d, length: %d\n", ret, ev.event, evQueue_GetLength());

	printf("evQueue_Get()\n");
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());
	ret = evQueue_Get(&ev);
	printf("evQueue_Get: %d, ev.event: %d, ev.pid: %d, ev.data: %p, length: %d\n", ret, ev.event, ev.pid, ev.data, evQueue_GetLength());

	return(1);
}
#endif 

