#include "include.h" 

#ifndef _SPI_TFT_LCD_H_
#define _SPI_TFT_LCD_H_




//本程序使用的是模拟SPI接口驱动
//可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示
//VCC:可以接5V也可以接3.3V
//LED:可以接5V也可以接3.3V或者使用任意空闲IO控制(高电平使能)
//GND：接电源地
//说明：如需要尽可能少占用IO，可以将LCD_CS接地，LCD_LED接3.3V，LCD_RST接至单片机复位端，
//将可以释放3个可用IO


#define TFT_LCD_RS         	C1		//PC1--->>TFT --RS/DC
#define TFT_LCD_CS        	C4 		//PC2--->>TFT --CS/CE
#define TFT_LCD_RST     	C2		//PC3--->>TFT --RST
#define TFT_LCD_SCL        	C3		//PC4--->>TFT --SCL/SCK
#define TFT_LCD_SDA        	C5		//PC5--->>TFT --SDA/DIN



//液晶控制口置1操作语句宏定义
#define	TFT_LCD_CS_SET  	Pin_Set(TFT_LCD_CS)   
#define	TFT_LCD_RS_SET  	Pin_Set(TFT_LCD_RS)    
#define	TFT_LCD_SDA_SET  	Pin_Set(TFT_LCD_SDA)    
#define	TFT_LCD_SCL_SET  	Pin_Set(TFT_LCD_SCL)     
#define	TFT_LCD_RST_SET  	Pin_Set(TFT_LCD_RST)     

//液晶控制口置0操作语句宏定义
#define	TFT_LCD_CS_CLR  	Pin_Reset(TFT_LCD_CS)   
#define	TFT_LCD_RS_CLR  	Pin_Reset(TFT_LCD_RS)     
#define	TFT_LCD_SDA_CLR  	Pin_Reset(TFT_LCD_SDA)       
#define	TFT_LCD_SCL_CLR  	Pin_Reset(TFT_LCD_SCL)   
#define	TFT_LCD_RST_CLR  	Pin_Reset(TFT_LCD_RST) 


//硬件SPI宏定义
#define TFT_LCD_SPI		 		spi0
#define TFT_LCD_SPI_CS   		SPI_PCS0
#define TFT_LCD_SPI_MODE 		MASTER
#define TFT_LCD_SPI_High_Speed  35000000
#define TFT_LCD_SPI_Low_Speed   1000000



void SPI_TFT_Lcd_Reset(void);	//复位
void SPI_TFT_Lcd_Init(void);	//初始化
void SPI_TFT_Lcd_Clear(u16 Color);	//清屏
void SPI_TFT_Lcd_ShowPiture(const unsigned char *p); //显示40*40 QQ图片
void SPI_TFT_Lcd_ShowFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);	//字体颜色和背景颜色
void SPI_TFT_Lcd_displayimage032();//显示摄像头灰度图像
void SPI_TFT_Lcd_displayimage032_bw() ;//显示摄像头二值化图像


#endif
