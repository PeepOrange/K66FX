/*********************************************************************************************************************
L3G4200D接线定义
------------------------------------ 
SDA                 C17
SCL                 C16
------------------------------------ 
********************************************************************************************************************/



#ifndef _SEEKFREE_L3G4200D_H
#define _SEEKFREE_L3G4200D_H

#include "Include.h"


//----------L3G4200D内部寄存器地址---------
#define L3G4200D_ID             0x69
#define WHO_AM_I_4200           0x0F
#define CTRL_REG1_4200          0x20
#define CTRL_REG2_4200          0x21
#define CTRL_REG3_4200          0x22
#define CTRL_REG4_4200          0x23
#define CTRL_REG5_4200          0x24
#define REFERENCE_4200          0x25
#define OUT_TEMP_4200           0x26
#define STATUS_REG_4200         0x27
#define OUT_X_L_4200            0x28
#define OUT_X_H_4200            0x29
#define OUT_Y_L_4200            0x2A
#define OUT_Y_H_4200            0x2B
#define OUT_Z_L_4200            0x2C
#define OUT_Z_H_4200            0x2D
#define FIFO_CTRL_REG_4200      0x2E
#define FIFO_SRC_REG_4200       0x2F
#define INT1_CFG_4200           0x30
#define INT1_SRC_4200           0x31
#define INT1_TSH_XH_4200        0x32
#define INT1_TSH_XL_4200        0x33
#define INT1_TSH_YH_4200        0x34
#define INT1_TSH_YL_4200        0x35
#define INT1_TSH_ZH_4200        0x36
#define INT1_TSH_ZL_4200        0x37
#define INT1_DURATION_4200      0x38


#define	L3G4200_DEV_ADD	        0xD2>>1	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改




extern int16 gyro_x, gyro_y, gyro_z;


void InitL3G4200D(void);
void get_l3g4200d(void);






#endif
