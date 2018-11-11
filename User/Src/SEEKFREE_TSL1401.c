#include "SEEKFREE_TSL1401.h"




#define CCD_CLK_PORT   E4                     	//CCD CLK引脚定义
#define CCD_SI_PORT    E5                     	//CCD SI 引脚定义
#define AD_CHANNEL     ADC0_SE8                 //定义AD采集通道  B0
#define EXPOSURE_TIME  10                       //定义CCD曝光时间 单位MS



#define CCD_CLK(x)     gpio_set (CCD_CLK_PORT, x)
#define CCD_SI(x)      gpio_set (CCD_SI_PORT,  x)


uint16 ccd_data[128];                           //CCD数据

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401线阵CCD初始化
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void ccd_init(void)     
{       
    adc_init (AD_CHANNEL);                      //B0 1号
    gpio_init(CCD_CLK_PORT, GPO, 1);            //CLK
    gpio_init(CCD_SI_PORT,  GPO, 1);            //SI
    
    DisableInterrupts;
    pit_init_ms(pit0, EXPOSURE_TIME);   		//定时EXPOSURE_TIME(ms) 后中断
    enable_irq(PIT0_IRQn);                      //使能PIT0中断
    EnableInterrupts;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401线阵CCD数据采集
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void ccd_collect(void)
{
    uint16 i = 0;

 
    CCD_CLK(1);
    CCD_SI(0);
    

    CCD_SI(1);
    CCD_CLK(0);
    

    CCD_CLK(1);
    CCD_SI(0);
    
    
    for(i=0;i<128;i++)
    {
        CCD_CLK(0);   
        ccd_data[i] = adc_once(AD_CHANNEL, ADC_12bit);     
        CCD_CLK(1);
    }
}
