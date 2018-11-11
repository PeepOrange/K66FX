#include "Common.h"


#define EX_REF_CLK  50 //(定义外部参考时钟为50MHZ)
uint32 mcgout_clk_mhz = 100;
uint32 core_clk_mhz = 100;
uint32 bus_clk_mhz = 100;

void get_clk(void)
{
    mcgout_clk_mhz = EX_REF_CLK * ((MCG->C6 & MCG_C6_VDIV0_MASK) + 16);
	mcgout_clk_mhz = mcgout_clk_mhz/ ((MCG->C5 & MCG_C5_PRDIV0_MASK) + 1)/2;
    core_clk_mhz = mcgout_clk_mhz / ((SIM->CLKDIV1 >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
    bus_clk_mhz = mcgout_clk_mhz / (((SIM->CLKDIV1 >> SIM_CLKDIV1_OUTDIV2_SHIFT) & 0x0f) + 1);
    
    uart_init(DEBUG_PORT,DEBUG_BAUD);   //初始化调试串口，如果不使用printf可以屏蔽
}
