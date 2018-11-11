#ifndef _MK66_lptmr_h
#define _MK66_lptmr_h


#include "Misc.h"
#include "Common.h"
#include "MK66_port.h"
#include "MK66_gpio.h"
#include "MK66_port_cfg.h"


typedef enum
{
    lpt0_alt1 = 1,      // A19
    lpt0_alt2 = 2       // C5
} LPT0_ALTn;

typedef enum
{
    LPT_Rising  = 0,    //上升沿触发
    LPT_Falling = 1     //下降沿触发
} LPT_CFG;


#define LPTMR_Flag_Clear()  (LPTMR0->CSR |= LPTMR_CSR_TCF_MASK)         //清除LPT比较标志位




void lptmr_pulse_init(LPT0_ALTn altn, uint16 count, LPT_CFG cfg);
uint16 lptmr_pulse_get(void);
void lptmr_pulse_clean(void);


#endif
