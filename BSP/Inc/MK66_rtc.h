#ifndef _MK66_rtc_h
#define _MK66_rtc_h



#include "Misc.h"
#include "Common.h"
#include "stdlib.h"


#define rtc_alarm_irq_en()      RTC->IER |= RTC_IER_TAIE_MASK      //使能闹钟中断
#define rtc_alarm_irq_dis()     RTC->IER &= ~RTC_IER_TAIE_MASK     //禁止闹钟中断


#define rtc_overflow_irq_en()   RTC->IER |= RTC_IER_TOIE_MASK      //使能溢出中断
#define rtc_overflow_irq_dis()  RTC->IER &= ~RTC_IER_TOIE_MASK     //禁止溢出中断

#define rtc_invalid_irq_en()    RTC->IER |= RTC_IER_TIIE_MASK      //使能无效设置中断
#define rtc_invalid_irq_dis()   RTC->IER &= ~RTC_IER_TIIE_MASK     //禁止无效设置中断



void     rtc_init(void);                         //初始化

void     rtc_set_time(uint32 seconds);           //设置时间
uint32   rtc_get_time(void);                     //获取时间

uint8    rtc_set_alarm(uint32 alarm);            //设置闹钟
void     rtc_close_alarm(void);                  //关闭闹钟









#endif
