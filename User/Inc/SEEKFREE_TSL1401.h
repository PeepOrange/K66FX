/*********************************************************************************************************************
TSL1401接线定义：
------------------------------------ 
模块管脚       	单片机管脚
CCD_AO	   		B0
CCD_CLK	   		E4
CCD_SI	   		E5
------------------------------------ 
********************************************************************************************************************/



#ifndef _TSL1401_c
#define _TSL1401_c

#include "Include.h"

extern uint16 ccd_data[128];                   //CCD数据


void ccd_init(void);
void ccd_collect(void);
















#endif

