#ifndef _MK66_wdog_h
#define _MK66_wdog_h

#include "Misc.h"
#include "Common.h"
#include "stdlib.h"


//wdog 代码，采用 LPO 时钟，不分频。

void wdog_init_ms(uint32 ms);   //初始化看门狗，设置喂狗时间 ms
void wdog_feed(void);           //喂狗


void wdog_disable(void);        //禁用看门狗
void wdog_enable(void);         //启用看门狗

#endif
