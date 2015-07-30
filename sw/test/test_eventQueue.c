/**
 * Martin Wuerms
 * 2015-07-23
 */

/* - includes --------------------------------------------------------------- */
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/eventQueue.h"

/* - defines ---------------------------------------------------------------- */

/* - typedefs --------------------------------------------------------------- */

/* - public functions ------------------------------------------------------- */

/**
 * initialize event queue
 */
void test_eventQueue_Init(void **state) {
    // test event
    event_t ev = {.data = NULL, .pid = 1, .event = 1};

    evQueue_Init();
    assert_int_equal(0, evQueue_GetLength());
    // should not work, queue empty
    assert_int_equal(0, evQueue_Read(&ev));    
}

/**
 * write event queue until full
 */
void test_eventQueue_WriteFull(void **state) {
    // test event
    event_t ev = {.data = NULL, .pid = 1, .event = 1};
    uint8_t i;

    // fill queue completely, cEVENT_QUEUE_SIZE-1 elements
    printf("eventQueue has %d elements\n", cEVENT_QUEUE_SIZE);
    for(i = 1; i < (cEVENT_QUEUE_SIZE); i++) {
        assert_int_equal(1, evQueue_Write(&ev));
        assert_int_equal(i, evQueue_GetLength());
    }
    
    // queue is full now
    assert_int_equal(0, evQueue_Write(&ev));
    assert_int_equal(cEVENT_QUEUE_SIZE-1, evQueue_GetLength());
    
}

/**
 * read event queue until empty
 */
void test_eventQueue_ReadEmpty(void **state) {
    // test event
    event_t ev = {.data = NULL, .pid = 1, .event = 1};
    uint8_t i;

    // event queue has been filled previously
    assert_int_equal(cEVENT_QUEUE_SIZE-1, evQueue_GetLength());

    // read queue completely, cEVENT_QUEUE_SIZE-1 elements
    printf("eventQueue has %d elements\n", cEVENT_QUEUE_SIZE);
    for(i = cEVENT_QUEUE_SIZE-1; i > 0; i--) {
        assert_int_equal(i, evQueue_GetLength());
        assert_int_equal(1, evQueue_Read(&ev));
    }
    // queue is empty now
    assert_int_equal(0, evQueue_GetLength());
    assert_int_equal(0, evQueue_Read(&ev));
}

