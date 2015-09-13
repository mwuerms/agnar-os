/**
 * Martin Wuerms
 * 2015-07-23
 *
 */

#ifndef _PROCESS_H_
#define _PROCESS_H_

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include "debug.h"

/* - defines ---------------------------------------------------------------- */
#define cNB_OF_PROCESSES         16 /// number of processes
#define cNB_OF_EVENTS_IN_QUEUE   32 /// number of events in event queue

/* - typedefs --------------------------------------------------------------- */
typedef int8_t (*process_func_t) (uint8_t event, void *data);

typedef struct {
  process_func_t  process;
  char *name;
  uint8_t pid;    /// PID: process identifier
  uint8_t state;  /// state of the process: none=0, started, running
} process_t;
// .pid
#define cPROCESS_PID_IDLE       0   // the idle process has pid = 0

// .state
#define cPROCESS_STATE_NONE     0
#define cPROCESS_STATE_ACTIVE   1
#define cPROCESS_STATE_RUNNING  2

typedef struct {
  void * data;
  uint8_t pid;
  uint8_t event;
} event_t;
// events from 0 ... 127 are for user purpose
// predefined events
#define cEV_START   128
#define cEV_STOP    129
#define cEV_POLL    130

/* - prototypes ------------------------------------------------------------- */
void process_Init(void);
int8_t process_Add(process_t *p);
int8_t process_Remove(process_t *p);
int8_t process_Start(uint8_t pid);
int8_t process_Stop(uint8_t pid);
int8_t process_AddIdle(process_t *p);
int8_t process_SendEvent(uint8_t pid, uint8_t event, void *data);
int8_t process_IsEventQueueEmpty(void);
int8_t process_Run(void);

#endif /* _PROCESS_H_ */
