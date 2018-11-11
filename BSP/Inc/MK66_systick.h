#ifndef _MK66_systick_h
#define _MK66_systick_h


#include "MK66_gpio.h"
#include "Common.h"

void    systick_delay(uint32 time);
void    systick_delay_ms(uint32 ms);
void    systick_timing(uint32 time);
uint32  systick_getval(void);


#endif
