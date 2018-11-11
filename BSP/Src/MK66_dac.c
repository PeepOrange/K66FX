#include "MK66_dac.h"

DAC_Type * const DACX[2] = DAC_BASE_PTRS; //定义两个指针数组保存 DACN 的地址

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      dacn         选择DAC通道
//  @param      volta        需要输出的电压
//  @return     void
//  @since      v1.0
//  Sample usage:               dac_init(dac0,1000);//输出电压等于(1000/(1<<12)*3.3)V
//-------------------------------------------------------------------------------------------------------------------
void dac_init(DACn dacn,uint16 volta)
{
    volta &= 0x0FFF; 
    
    // 使能时钟 
    SIM->SCGC2 |= (SIM_SCGC2_DAC0_MASK << dacn) ;    //使能DAC模块
    
    //  配置DAC寄存器  

    //配置DAC_C0寄存器
    DACX[dacn]->C0  = ( 0
                        |  DAC_C0_DACTRGSEL_MASK                //选择软件触发
                        |  DAC_C0_DACRFS_MASK                   //选择参考VDD电压(3.3V)
                        |  DAC_C0_DACEN_MASK                    //使能DAC模块
                      );

    //配置DAC_C1寄存器
    DACX[dacn]->C1 = ( 0 ) ;
    //配置DAC_C2寄存器
    DACX[dacn]->C2 = ( 0
                       | DAC_C2_DACBFRP(0)             //设置缓冲区读指针指向0
                     );

    DACX[dacn]->DAT[0].DATH = volta>>8;   //默认输出最低电压
    DACX[dacn]->DAT[0].DATL = (uint8)volta;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      改变输出电压
//  @param      dacn         选择DAC通道
//  @param      volta        需要输出的电压
//  @return     void
//  @since      v1.0
//  Sample usage:               dac_out(dac0,1000);//输出电压等于(1000/(1<<12)*3.3)V
//-------------------------------------------------------------------------------------------------------------------
void dac_out(DACn dacn, uint16 volta)
{
    volta &= 0x0FFF; 
    DACX[dacn]->DAT[0].DATH = volta>>8;   //默认输出最低电压
    DACX[dacn]->DAT[0].DATL = (uint8)volta;
}









