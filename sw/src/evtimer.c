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

/* - defsines --------------------------------------------------------------- */
#define cEVTIMER_NB_EVENTS  16

/* - typedefs --------------------------------------------------------------- */
typedef struct {
    uint16_t timeout;   /// =0: unused
    uint16_t compare:
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
    uint16_t now = 0;
    // get next free element
    if(fifo_IncWriteIndex(&event_fifo)) {
        // cannot get next element: fifo is full
        return(0);
    }

    // sort event into list according to its compare value
    
    // copy event definition
    //now = read timer register
    event_list[event_fifo.write].timeout = timeout;
    event_list[event_fifo.write].ev.pid = pid;
    event_list[event_fifo.write].ev.event = event;
    event_list[event_fifo.write].ev.data = data;
    event_list[event_fifo.write].compare = now + timeout;

    return(1);
}
