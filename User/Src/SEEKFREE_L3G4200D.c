#include "SEEKFREE_L3G4200D.h"

int16 gyro_x = 0, gyro_y = 0, gyro_z = 0;

uint8 Temperature = 0;




//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化L3G4200D陀螺仪
//  @param      NULL
//  @return     void						
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void InitL3G4200D(void)
{
    simiic_write_reg(L3G4200_DEV_ADD, CTRL_REG1_4200, 0x8f);   //
    simiic_write_reg(L3G4200_DEV_ADD, CTRL_REG2_4200, 0x00);   //00
    simiic_write_reg(L3G4200_DEV_ADD, CTRL_REG3_4200, 0x08);   //
    simiic_write_reg(L3G4200_DEV_ADD, CTRL_REG4_4200, 0x30);   //+-2000dps
    simiic_write_reg(L3G4200_DEV_ADD, CTRL_REG5_4200, 0x00);
    Temperature = simiic_read_reg(L3G4200_DEV_ADD, OUT_TEMP_4200, IIC);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取L3G4200D陀螺仪数据
//  @param      NULL
//  @return     void						
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_l3g4200d(void)
{
    uint8 gx, gy, gz;
    uint16 wgx, wgy, wgz;

    if( simiic_read_reg(L3G4200_DEV_ADD, STATUS_REG_4200, IIC)&0x80 )//查看数据是否准备好了。如果没有准备好，读取则可能读取到错误数据。读取频率最好是高于数据输出频率
    {
        wgx = simiic_read_reg(L3G4200_DEV_ADD, OUT_X_H_4200, IIC);
		gx = simiic_read_reg(L3G4200_DEV_ADD, OUT_X_L_4200, IIC);
        gyro_x = (wgx<<8) + gx;
        gyro_x >>= 3;

        wgz = simiic_read_reg(L3G4200_DEV_ADD, OUT_Y_H_4200, IIC);
		gz = simiic_read_reg(L3G4200_DEV_ADD, OUT_Y_L_4200, IIC);
        gyro_z = (wgz<<8) + gz;
        gyro_z >>= 3;

        wgy = simiic_read_reg(L3G4200_DEV_ADD, OUT_Z_H_4200, IIC);
		gy = simiic_read_reg(L3G4200_DEV_ADD, OUT_Z_L_4200, IIC);
        gyro_y = (wgy<<8) + gy;
        gyro_y >>= 3;
    }
}
