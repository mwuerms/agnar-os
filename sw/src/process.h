/**
 * Martin Wuerms
 * 2015-07-23
 *
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>

/* - defines ---------------------------------------------------------------- */
#define cNB_OF_PROCESSES         16 /// number of processes
#define cNB_OF_EVENTS_IN_QUEUE   32 /// number of events in event queue

/* - typedefs --------------------------------------------------------------- */
typedef int8_t (*process_func_t) (uint8_t event, void *data);

typedef struct {
  process_func_t  process;
  char *process_name;
  uint8_t pid;    /// PID: process identifier
  uint8_t state;  /// state of the process: none=0, started, running
} process_t;
// .state
#define cPROCESS_STATE_NONE     0
#define cPROCESS_STATE_ACTIVE   1
#define cPROCESS_STATE_RUNNING  2

typedef struct {
  void * data;
  uint8_t pid;
  uint8_t event;
} event_t;
// predefined events
#define cEV_START   1
#define cEV_STOP    2
#define cEV_POLL    3

/* - prototypes ------------------------------------------------------------- */
void process_Init(void);
int8_t process_Add(process_t *p);
int8_t process_Start(uint8_t pid);
int8_t process_SendEvent(uint8_t pid, uint8_t event, void *data);
int8_t process_IsEventQueueEmpty(void);
int8_t process_Run(void);


