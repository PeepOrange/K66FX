#include "MK66_pit.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit初始化
//  @param      pitn            选择pit模块
//  @param      cnt             定时中断的时间
//  @return     void
//  @since      v1.0
//  Sample usage:               pit_init(pit0,1000);								//定时1000个bus时钟后中断
//								set_irq_priority(PIT0_IRQn,1);						//设置优先级,根据自己的需求设置
//								enable_irq(PIT0_IRQn);								//打开pit0的中断开关
//								EnableInterrupts;									//打开总的中断开关
//-------------------------------------------------------------------------------------------------------------------
void pit_init(PITn pitn, uint32 cnt)
{
	SIM->SCGC6       |= SIM_SCGC6_PIT_MASK;        			//使能PIT时钟
	PIT->MCR         = 0;									//使能PIT定时器时钟 ，调试模式下继续运行
	PIT->CHANNEL[pitn].LDVAL  = cnt;              			//设置溢出中断时间
	PIT_FlAG_CLR(pitn);										//清除中断标志位
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //禁止PITn定时器（用于清空计数值）
    PIT->CHANNEL[pitn].TCTRL  = ( 0
								| PIT_TCTRL_TEN_MASK        //使能 PITn定时器
								| PIT_TCTRL_TIE_MASK        //开PITn中断
								);
	//enable_irq( (IRQn_Type)((int)pitn + PIT0_IRQn) );       //开中断
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit初始化
//  @param      pitn            选择pit模块
//  @param      cnt             定时延时的时间
//  @return     void
//  @since      v1.0
//  Sample usage:               pit_init(pit0,1000);		//延时1000个bus时钟
//-------------------------------------------------------------------------------------------------------------------
void pit_delay(PITn pitn, uint32 cnt)
{
	SIM->SCGC6       |= SIM_SCGC6_PIT_MASK;        			//使能PIT时钟
	PIT->MCR         = 0;									//使能PIT定时器时钟 ，调试模式下继续运行
	PIT->CHANNEL[pitn].LDVAL  = cnt;              			//设置溢出中断时间
	PIT_FlAG_CLR(pitn);										//清除中断标志位
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //禁止PITn定时器（用于清空计数值）
    PIT->CHANNEL[pitn].TCTRL  = ( 0
								| PIT_TCTRL_TEN_MASK        //使能 PITn定时器
								//| PIT_TCTRL_TIE_MASK        //开PITn中断
								);
	while( !((PIT->CHANNEL[pitn].TFLG) & PIT_TFLG_TIF_MASK) ){}//等待时间到

    PIT_FlAG_CLR(pitn);                                     //清中断标志位
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit初始化
//  @param      pitn            选择pit模块
//  @return     void
//  @since      v1.0
//  Sample usage:               pit_time_start(pit0);		//pit0开始计时
//-------------------------------------------------------------------------------------------------------------------
void pit_time_start(PITn pitn)
{
	SIM->SCGC6       |= SIM_SCGC6_PIT_MASK;        			//使能PIT时钟
	PIT->MCR         = 0;									//使能PIT定时器时钟 ，调试模式下继续运行
	PIT->CHANNEL[pitn].LDVAL  = ~0;              			//设置溢出中断时间
	PIT_FlAG_CLR(pitn);										//清除中断标志位
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //禁止PITn定时器（用于清空计数值）
    PIT->CHANNEL[pitn].TCTRL  = ( 0
								| PIT_TCTRL_TEN_MASK        //使能 PITn定时器
								//| PIT_TCTRL_TIE_MASK        //开PITn中断
								);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit初始化
//  @param      pitn            选择pit模块
//  @return     void
//  @since      v1.0
//  Sample usage:               pit_time_get(pit0);			//获取当前pit0计时时间
//-------------------------------------------------------------------------------------------------------------------
uint32 pit_time_get(PITn pitn)
{
	uint32 val;
	val = (uint32)(~0) - PIT->CHANNEL[pitn].CVAL;
	if(PIT->CHANNEL[pitn].TFLG &  PIT_TFLG_TIF_MASK)		//判断时间是否超时
	{
		PIT_FlAG_CLR(pitn);									//清除中断标志位
		PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;   //禁止PITn定时器（用于清空计数值）
		return 0XFFFFFFFF;									//超时返回最大值
	}
	return val;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit初始化
//  @param      pitn            选择pit模块
//  @return     void
//  @since      v1.0
//  Sample usage:               pit_close(pit0);			//pit0停止计时
//-------------------------------------------------------------------------------------------------------------------
void pit_close(PITn pitn)
{
	PIT_FlAG_CLR(pitn);										//清除中断标志位
	PIT->CHANNEL[pitn].TCTRL &= ~ PIT_TCTRL_TEN_MASK;       //禁止PITn定时器（用于清空计数值）
}


















