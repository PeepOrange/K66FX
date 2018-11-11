/*********************************************************************************************************************
模拟IIC接线定义
------------------------------------ 
SDA                 C17
SCL                 C16
------------------------------------ 
********************************************************************************************************************/



#ifndef _SEEKFREE_IIC_h
#define _SEEKFREE_IIC_h



#include "Include.h"



#define SEEKFREE_SCL    C16                           //定义SCL引脚
#define SEEKFREE_SDA    C17                           //定义SDA引脚

typedef enum IIC       //DAC模块
{
    IIC,
    SCCB
} IIC_type;



void  IIC_start(void);
void  IIC_stop(void);
void  IIC_ack_main(uint8 ack_main);
void  send_ch(uint8 c);
uint8 read_ch(void);
void  simiic_write_reg(uint8 dev_add, uint8 reg, uint8 dat);
uint8 simiic_read_reg(uint8 dev_add, uint8 reg, IIC_type type);
void  IIC_init(void);











#endif

