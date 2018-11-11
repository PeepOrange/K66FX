/*********************************************************************************************************************
2.8TFT液晶屏接线定义：
------------------------------------ 
模块管脚       	单片机管脚
DB0-DB15        D0-D15
RS              E7
WR              E10
CS              E6
RST             E12
RD              E11
------------------------------------ 
********************************************************************************************************************/
 
 
#ifndef _SEEKFREE_28LCD_H
#define _SEEKFREE_28LCD_H		

#include "Include.h"









//LCD的画笔颜色和背景色	   
extern uint16  POINT_COLOR;//默认红色    
extern uint16  BACK_COLOR; //背景颜色.默认为白色
//LCD重要参数集
typedef struct  
{										    
	uint16 width;			//LCD 宽度
	uint16 height;			//LCD 高度
	uint16 id;				//LCD ID
	uint8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16	 wramcmd;		//开始写gram指令
	uint16  setxcmd;		//设置x坐标指令
	uint16  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	


extern const uint8 timer[];
extern const unsigned char gImage_36[34602];
extern const uint8 unlocked[];
extern const uint8 locked[];
extern const uint8 timer_running[];
extern const uint8 timer_stop[];
extern const uint8 now_time[];
extern const uint8 lap_length[];
extern const uint8 fin_speed[];


//LCD参数  管理LCD重要参数
extern _lcd_dev lcddev;	

void LCD_Init(void); 
void LCD_Clear(uint16 Color);
void LCD_WR_DATA(int Data);
void LCD_WR_REG(int Reg);
void LCD_SetCursor(uint16 Xpos, uint16 Ypos);//设置光标位置
void LCD_SetWindows(uint16 xStar, uint16 yStar,uint16 xEnd,uint16 yEnd);//设置显示窗口
void LCD_DrawPoint(uint16 x,uint16 y);//画点
void LCD_WriteRAM_Prepare(void);
void LCD_SetParam(void);
void LCD_Display_16x8Str(uint16 x, uint16 y, int8 * str, uint16 color);
void LCD_Display_32x16Str(uint16 x, uint16 y, int8 * str, uint16 color);
void LCD_Display_16x8Num(uint16 x, uint16 y, int dat, uint8 number, uint16 color);
void LCD_Display_32x16Num(uint16 x, uint16 y, int dat, uint8 number, uint16 color);
void LCD_Displayimage032(uint8 *p);
void LCD_Displayimage7725(uint8 *p);
void LCD_Display_Chinese(uint16 x, uint16 y, uint8 number, uint8 size, const uint8 * p, uint16 color);
void LCD_Display_image(uint16 x, uint16 y, uint16 size_x, uint16 size_y, const uint8 *p);

#endif  
	 
	 



