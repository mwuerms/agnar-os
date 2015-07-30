/**
 * Martin Wuerms
 * 2015-07-23
 *
 */

/* - includes --------------------------------------------------------------- */
#include "eventQueue.h"
#include <string.h>

/* - defines ---------------------------------------------------------------- */
#define cEVENT_QUEUE_MASK     (cEVENT_QUEUE_SIZE-1)

/* - typedefs --------------------------------------------------------------- */
static event_t event_queue[cEVENT_QUEUE_SIZE];
static uint8_t wr_index, rd_index, queue_length;

/* - public functions ------------------------------------------------------- */

/**
 * @return
 */
void evQueue_Init(void) {
	wr_index = 0;
	rd_index = 0;
	queue_length = 0;
	memset(event_queue, 0, sizeof(event_queue));
}

/**
 * write an event to the event queue
 * @param   event   pointer to event to put into event_queue
 * @return  =1: OK, writing event successfull
 *          =0: Error, could not write, queue is full
 */
int8_t evQueue_Write(event_t *event) {
	uint8_t next = ((wr_index + 1) & cEVENT_QUEUE_MASK);

	// sanity checks
	if(event == NULL)
		return(0);

	// check if event_queue is not yet full
	if(next == rd_index)
		return(0);

	wr_index = next;
	queue_length++;
	event_queue[wr_index].data  = event->data;
	event_queue[wr_index].pid   = event->pid;
	event_queue[wr_index].event = event->event;
	return(1);
}

/**
 * read an event from the event queue
 * @param   event   pointer to event to get from event_queue
 * @return  =1: OK, event is valid
 *          =0: Error, queue is empty, event is invalid
 */
int8_t evQueue_Read(event_t *event) {
	//uint8_t next = ((rd_index + 1) & cEVENT_QUEUE_MASK);

	// sanity checks
	if(event == NULL)
		return(0);

	// check if event_queue is not yet empty
	if(rd_index == wr_index)
		return(0);

	rd_index = ((rd_index + 1) & cEVENT_QUEUE_MASK);//next;
	queue_length--;
	event->data  = event_queue[rd_index].data;
	event->pid   = event_queue[rd_index].pid;
	event->event = event_queue[rd_index].event;
	return(1);
}

/**
 * @return
 */
uint8_t evQueue_GetLength(void) {
	return(queue_length);
}

