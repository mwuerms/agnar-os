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

/* - typedefs --------------------------------------------------------------- */

/* - variables -------------------------------------------------------------- */
uint8_t *evtimer_pid;    /// point to pid of event timer
static process_t evtimer_process;

/* - public function -------------------------------------------------------- */

/**
 * initialize the event timer
 */
void evtimer_Init(void) {
    memset(&evtimer_process, 0, sizeof(evtimer_process));
    evtimer_pid = &evtimer_process.pid;
}

/**
 * start the event timer
 * @param   periode   of event timer
 * @return  =1: could start event timer
 *          =0: could not start event timer
 */
int8_t evtimer_Start(uint16_t periode) {
    return(0);
}

/**
 * stop the event timer
 * @return  =1: could stop event timer
 *          =0: could not stop event timer
 */
int8_t evtimer_Stop(void) {
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
    return(0);
}
