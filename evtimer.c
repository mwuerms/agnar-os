/**
 * Martin Wuerms
 * 2015-09-07
 *
 * this module must fit the architecture (mcu)
 */

/* - includes --------------------------------------------------------------- */
#include <string.h>
#include <stdint.h>
#include "process.h"
#include "evtimer.h"
#include "fifo.h"

/* - defines ---------------------------------------------------------------- */
#define cEVTIMER_NB_EVENTS  16

/* - typedefs --------------------------------------------------------------- */
typedef struct {
    uint16_t compare;
    event_t  ev;
} evtimer_event_t;

/* - variables -------------------------------------------------------------- */
uint8_t *evtimer_pid;    /// point to pid of event timer
static process_t evtimer_process;
static char evtimer_name[] = "event timer";
static evtimer_event_t event_list[cEVTIMER_NB_EVENTS];
static fifo_index_t event_fifo;

/* - private function ------------------------------------------------------- */

/**
 * the event timer process
 * process the next event to send
 */
int8_t evtimer_Process(uint8_t event, void *data) {
    return(1);
}

/* - public function -------------------------------------------------------- */

/**
 * initialize the event timer
 */
void evtimer_Init(void) {
    // vars
    evtimer_pid = &evtimer_process.pid;
    evtimer_process.name = evtimer_name;
    evtimer_process.process = evtimer_Process;
    memset(&evtimer_process, 0, sizeof(evtimer_process));
    memset(&event_list, 0, sizeof(event_list));
    fifo_Init(&event_fifo, cEVTIMER_NB_EVENTS);

    process_Add(&evtimer_process);
}

/**
 * start the event timer
 * @param   periode   of event timer
 * @return  =1: could start event timer
 *          =0: could not start event timer
 */
int8_t evtimer_Start(uint16_t periode) {
    // start the timer
    return(process_Start(evtimer_process.pid));
}

/**
 * stop the event timer
 * @return  =1: could stop event timer
 *          =0: could not stop event timer
 */
int8_t evtimer_Stop(void) {
    //process_Stop(evtimer_process.pid);
    return(0);
}

/**
 * add a single event to the event timer
 * @param   timeout after which to send the event
 * @param	pid		process identifier
 * @param	event	event for the process to execute
 * @param	data	additional data to process (if unused = NULL)
 * @return	status 	=1: OK, could add event
 *					=0: error, could not add event
 */
int8_t evtimer_AddSingleEvent(uint16_t timeout, uint8_t pid, uint8_t event, void *data) {
    uint16_t sr, duration, now = 0;
    uint8_t write_pos, write_pos_1, move_elements, found;
    fifo_index_t fifo_save;

    // sanity check
    if(timeout == 0) {
        // invalid timeout
        return(0);
    }

    // get next free element
    if(fifo_IncWriteIndex(&event_fifo) == 0) {
        // cannot get next element: fifo is full
        return(0);
    }

    // copy event definition
    //now = read timer register

    // sort event into list according to its duration value, smallest duration first
    // duration = compare - now
    lock_interrupts(sr);
    memcpy(&fifo_save, &event_fifo, sizeof(event_fifo));	// save event_fifo to restore at the end

    // go from .read to .write
    write_pos = 0;
    found = 0;
    while(fifo_IncReadIndex(&event_fifo) == 1) {
    	duration = event_list[event_fifo.read].compare - now;
    	if(timeout < duration) {
    		// found position where the new duration is < than in the list
			write_pos = event_fifo.read;
			found = 1;
			break;
		}
    }

    if(found == 1) {
    	// found position, move all elements 1 position from write_pos to .write
    	write_pos_1 = fifo_IncUint8(write_pos, event_fifo.size-1);
    	move_elements = 0;
    	if(write_pos_1 > event_fifo.write)
    	memcpy(&event_list[write_pos_1], &event_list[write_pos], sizeof(evtimer_event_t)*move_elements);
		// set new event again to write_pos
		event_list[write_pos].ev.pid = pid;
		event_list[write_pos].ev.event = event;
		event_list[write_pos].ev.data = data;
		event_list[write_pos].compare = now + timeout;
    }
    else {
        event_list[event_fifo.write].ev.pid = pid;
        event_list[event_fifo.write].ev.event = event;
        event_list[event_fifo.write].ev.data = data;
        event_list[event_fifo.write].compare = now + timeout;
    }
    memcpy(&event_fifo, &fifo_save, sizeof(event_fifo));	// restore fifo
    restore_interrupt(sr);

    return(1);
}
