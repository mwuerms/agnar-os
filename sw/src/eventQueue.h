/**
 * Martin Wuerms
 * 2015-07-23
 *
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>

/* - defines ---------------------------------------------------------------- */
#define cEVENT_QUEUE_SIZE   16// 32  // use 2^N

/* - typedefs --------------------------------------------------------------- */
typedef struct {
  void * data;
  uint8_t pid;
  uint8_t event;
} event_t;

/* - prototypes ------------------------------------------------------------- */
void evQueue_Init(void);
int8_t evQueue_Write(event_t *event);
int8_t evQueue_Read(event_t *event);
uint8_t evQueue_GetLength(void);


