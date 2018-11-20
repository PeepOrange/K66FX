#include "MK66_adc.h"

ADC_Type * const ADCX[] = ADC_BASE_PTRS; //定义两个指针数组保存 ADCN 的地址




void adc_start(ADCn_Ch adcn_ch, ADC_nbit bit)
{
    ADCn adcn = (ADCn)(adcn_ch >> 5) ;
    uint8 ch = (uint8)(adcn_ch & 0x1F);

    //初始化ADC默认配置
    ADCX[adcn]->CFG1 = (0
                        //| ADC_CFG1_ADLPC_MASK         //ADC功耗配置，0为正常功耗，1为低功耗
                        | ADC_CFG1_ADIV(2)              //时钟分频选择,分频系数为 2^n,2bit
                        | ADC_CFG1_ADLSMP_MASK          //采样时间配置，0为短采样时间，1 为长采样时间
                        | ADC_CFG1_MODE(bit)
                        | ADC_CFG1_ADICLK(0)            //0为总线时钟,1为总线时钟/2,2为交替时钟（ALTCLK），3为 异步时钟（ADACK）。
                       );


    ADCX[adcn]->CFG2  = (0
                         //| ADC_CFG2_MUXSEL_MASK       	//ADC复用选择,0为a通道，1为b通道。
                         //| ADC_CFG2_ADACKEN_MASK      //异步时钟输出使能,0为禁止，1为使能。
                         | ADC_CFG2_ADHSC_MASK          //高速配置,0为正常转换序列，1为高速转换序列
                         | ADC_CFG2_ADLSTS(0)           //长采样时间选择，ADCK为4+n个额外循环，额外循环，0为20，1为12，2为6，3为2
                        );

    //写入 SC1A 启动转换
    ADCX[adcn]->SC1[0] = (0
                          | ADC_SC1_AIEN_MASK          // 转换完成中断,0为禁止，1为使能
                          //| ADC_SC1_DIFF_MASK        // 差分模式使能,0为单端，1为差分
                          | ADC_SC1_ADCH( ch )
                         );

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      adcn_ch         选择ADC通道
//  @return     void
//  @since      v1.0
//  Sample usage:               adc_init(ADC0_SE8);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADCn_Ch adcn_ch)
{
    uint8 adcn = adcn_ch >> 5 ;

    switch(adcn)
    {
    case adc0:       //   ADC0
        SIM->SCGC6 |= (SIM_SCGC6_ADC0_MASK );        //开启ADC0时钟
        SIM->SOPT7 &= ~(SIM_SOPT7_ADC0ALTTRGEN_MASK  | SIM_SOPT7_ADC0PRETRGSEL_MASK);
        SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(0);
        break;
    case adc1:       //   ADC1
        SIM->SCGC3 |= (SIM_SCGC3_ADC1_MASK );
        SIM->SOPT7 &= ~(SIM_SOPT7_ADC1ALTTRGEN_MASK  | SIM_SOPT7_ADC1PRETRGSEL_MASK) ;
        SIM->SOPT7 |= SIM_SOPT7_ADC1TRGSEL(0);
        break;
    default:
        break;
    }

    switch(adcn_ch)
    {
    case ADC0_SE8:       // B0
        port_init(B0, ALT0);
        break;
    case ADC0_SE9:       // B1
        port_init(B1, ALT0);
        break;
    case ADC0_SE10:      // A7
        port_init(A7, ALT0);
        break;
    case ADC0_SE11:      // A8
        port_init(A8, ALT0);
        break;
    case ADC0_SE12:      // B2
        port_init(B2, ALT0);
        break;
    case ADC0_SE13:      // B3
        port_init(B3, ALT0);
        break;
    case ADC0_SE14:      // C0
        port_init(C0, ALT0);
        break;
    case ADC0_SE15:      // C1
        port_init(C1, ALT0);
        break;
    case ADC0_SE17:      // E24
        port_init(E24, ALT0);
        break;
    case ADC0_SE18:      // E25
        port_init(E25, ALT0);
        break;

    case ADC0_DP0:
    case ADC0_DP1:
    case ADC0_DP3:
    case ADC0_DM0:       // ADC0_DM0
    case ADC0_DM1:       // ADC0_DM1
    case ADC0_SE16:      // ADC0_SE16
    case Temp0_Sensor:   // Temperature Sensor,内部温度测量，可用ADC函数
    case VREFH0:         // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
    case VREFL0:         // 参考低电压,可用ADC函数 ,结果恒为 0
        break;          //这部分管脚不用配置复用

        // ---------------------------------ADC1-------------------------
    case ADC1_DP0:
    case ADC1_DP1:
    case ADC1_DP3:
        break;
    case ADC1_SE4a:      // E0
        port_init(E0, ALT0);
        break;
    case ADC1_SE5a:      // E1
        port_init(E1, ALT0);
        break;
    case ADC1_SE6a:      // E2
        port_init(E2, ALT0);
        break;
    case ADC1_SE7a:      // E3
        port_init(E3, ALT0);
        break;

    case ADC1_SE8:       // B0
        port_init(B0, ALT0);
        break;
    case ADC1_SE9:       // B1
        port_init(B1, ALT0);
        break;
    case ADC1_SE10:      // B4
        port_init(B4, ALT0);
        break;
    case ADC1_SE11:      // B5
        port_init(B5, ALT0);
        break;
    case ADC1_SE12:      // B6
        port_init(B6, ALT0);
        break;
    case ADC1_SE13:      // B7
        port_init(B7, ALT0);
        break;
    case ADC1_SE14:      // B10
        port_init(B10, ALT0);
        break;
    case ADC1_SE15:      // B11
        port_init(B11, ALT0);
        break;
    case ADC1_SE17:      // A17
        port_init(A17, ALT0);
        break;

    case ADC1_SE16:      // ADC1_SE16
    case VREF_OUTPUT:    // VREF Output
    case ADC1_DM0:       // ADC1_DM0
    case ADC1_DM1:       // ADC1_DM1
    case Temp1_Sensor:
    case VREFH1:         // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
    case VREFL1:         // 参考低电压,可用ADC函数 ,结果恒为 0
        break;

    default:
        break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择分辨率ADC_8bit、ADC_10bit、ADC_12bit、ADC_16bit
//  @return     void
//  @since      v1.0
//  Sample usage:               uint16 dat = adc_once(ADC0_SE8,ADC_16bit);//采集ADC0_SE8电压，分辨率16位
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_once(ADCn_Ch adcn_ch, ADC_nbit bit) //采集某路模拟量的AD值
{
    uint16 result = 0;
    ADCn adcn = (ADCn)(adcn_ch >> 5) ;
    adc_start(adcn_ch, bit);      //启动ADC转换
    
    while (( ADCX[adcn]->SC1[0] & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);   //只支持 A通道
    result = ADCX[adcn]->R[0];
    ADCX[adcn]->SC1[0] &= ~ADC_SC1_COCO_MASK;
    return result;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC停止采集
//  @param      adcn_ch         选择ADC通道
//  @return     void
//  @since      v1.0
//  Sample usage:               adc_stop(adc0);
//-------------------------------------------------------------------------------------------------------------------
void adc_stop(ADCn adcn)
{
    ADCX[adcn]->SC1[0] = (0
                          | ADC_SC1_AIEN_MASK                       // 转换完成中断,0为禁止，1为使能
                          //| ADC_SC1_DIFF_MASK                     // 差分模式使能,0为单端，1为差分
                          | ADC_SC1_ADCH(Module0_Dis)               //输入通道选择,此处选择禁止通道
                         );
}

