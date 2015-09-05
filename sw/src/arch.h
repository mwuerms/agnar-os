/**
 * Martin Wuerms
 * 2015-08-10
 */

/* - this file contains architecture specific definitions etc ... ----------- */

#ifndef _ARCH_H_
#define _ARCH_H_

/* - includes --------------------------------------------------------------- */
//#include <stdint.h>
//#include <string.h>

/* - define ----------------------------------------------------------------- */
// save status register + disable global interrupt
#define disable_interrupt(x)
// restore status register again
#define enable_interrupt(x)
/*
                            do { \
                            x = SR; \
                            DINT; \
                            } while(0)
*/

/* - typedef ---------------------------------------------------------------- */

/* - public functions ------------------------------------------------------- */


#endif /* _ARCH_H_ */
