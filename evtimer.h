/**
 * Martin Wuerms
 * 2015-09-07
 */

#ifndef _EV_TIMER_H_
#define _EV_TIMER_H_

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include "debug.h"

/* - defines ---------------------------------------------------------------- */

/* - typedefs --------------------------------------------------------------- */

/* - variables -------------------------------------------------------------- */
extern uint8_t *evtimer_pid;    /// point to pid of event timer

/* - public function -------------------------------------------------------- */
void evtimer_Init(void);
uint8_t evtimer_GetPID(void);
int8_t evtimer_Start(uint16_t periode);
int8_t evtimer_Stop(void);
int8_t evtimer_AddSingleEvent(uint16_t timeout, uint8_t pid, uint8_t event, void *data);

#endif /* _EV_TIMER_H_ */
