/*********************************************************************************************************************
MT9V032(总钻风(灰度摄像头))接线定义：
------------------------------------ 
模块管脚            单片机管脚
SDA(51的RX)         C17
SCL(51的TX)         C16
场中断              C6
像素中断            C18           
数据口              C8-C15 
------------------------------------ 

默认分辨率是            188*120
默认FPS                 50帧
********************************************************************************************************************/



#ifndef _MT9V032_h
#define _MT9V032_h

#include "Include.h"


#define MT9V032_COF_UART    uart3
#define MT9V032_COL     	188//图像宽度   范围1-752     K60采集不允许超过188
#define MT9V032_ROW    	 	120//图像高度	范围1-480
#define MT9V032_DMA_Ch  	DMA_CH0	//摄像头图像DMA传输通道
#define MT9V032_VSY_PIN		C18		//像素中断
#define MT9V032_PCLK_PIN	C3		//场中断
#define MT9V032_Threshold	35		//二值化阈值


//摄像头命令枚举
typedef enum
{
    INIT = 0,               //摄像头初始化命令
    AUTO_EXP,               //自动曝光命令
    EXP_TIME,               //曝光时间命令
    FPS,                    //摄像头帧率命令
    SET_COL,                //图像列命令
    SET_ROW,                //图像行命令
    LR_OFFSET,              //图像左右偏移命令
    UD_OFFSET,              //图像上下偏移命令
    GAIN,                   //图像偏移命令
    CONFIG_FINISH,          //非命令位，主要用来占位计数
    
    SET_EXP_TIME = 0XF0,    //单独设置曝光时间命令
    GET_STATUS,             //获取摄像头配置命令
    GET_VERSION,            //固件版本号命令
    
    SET_ADDR = 0XFE,        //寄存器地址命令
    SET_DATA                //寄存器数据命令
}CMD;



extern uint8 mt9v032_finish_flag;  //一场图像采集完成标志位
extern uint8 image[MT9V032_ROW][MT9V032_COL];      //内部使用


void   mt9v032_cof_uart_interrupt(void);
void   VSYNC(void);
void   camera_init(void);
void   seekfree_sendimg_032(void);
void   row_finished(void);



#endif

