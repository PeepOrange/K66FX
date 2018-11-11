#ifndef _MK66_cmt_h
#define _MK66_cmt_h


#include "MK66_port.h"


#define CMT_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON


void cmt_pwm_init(uint16 period, uint16 duty);
void cmt_pwm_duty(uint16 duty);
void cmt_pwm_freq(uint16 freq, uint16 duty);

#endif
