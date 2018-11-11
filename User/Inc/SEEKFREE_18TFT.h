/*********************************************************************************************************************	
1.8 TFT液晶接线定义：
------------------------------------ 
模块管脚            单片机管脚
SCL                 A15
SDA                 A16
RES                 B16
DC                  B17
CS                  A14

电源引脚
BL  3.3V电源（背光控制引脚，也可以接PWM来控制亮度）
VCC 3.3V电源
GND 电源地

------------------------------------ 
********************************************************************************************************************/



#ifndef _SEEKFREE_18TFT_H
#define _SEEKFREE_18TFT_H

#include "Include.h"





void lcd_init(void);
void dsp_single_colour(int color);
void displayimage032(uint8 *p);
void displayimage7725(unsigned char *p);



#endif
