#ifndef _MK66_dac_h
#define _MK66_dac_h


#include "Misc.h"
#include "Common.h"
#include "MK66_port.h"
#include "MK66_gpio.h"
#include "MK66_port_cfg.h"

typedef enum DACn       //DAC模块
{
    dac0,
    dac1
} DACn;


void dac_init(DACn dacn,uint16 volta);
void dac_out(DACn dacn, uint16 volta);

#endif
