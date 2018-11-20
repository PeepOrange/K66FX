#include "include.h" 

#ifndef _SPI_TFT_LCD_H_
#define _SPI_TFT_LCD_H_




//������ʹ�õ���ģ��SPI�ӿ�����
//�����ɸ��Ľӿ�IO���ã�ʹ����������4 IO������ɱ���Һ��������ʾ
//VCC:���Խ�5VҲ���Խ�3.3V
//LED:���Խ�5VҲ���Խ�3.3V����ʹ���������IO����(�ߵ�ƽʹ��)
//GND���ӵ�Դ��
//˵��������Ҫ��������ռ��IO�����Խ�LCD_CS�ӵأ�LCD_LED��3.3V��LCD_RST������Ƭ����λ�ˣ�
//�������ͷ�3������IO


#define TFT_LCD_RS         	C1		//PC1--->>TFT --RS/DC
#define TFT_LCD_CS        	C4 		//PC2--->>TFT --CS/CE
#define TFT_LCD_RST     	C2		//PC3--->>TFT --RST
#define TFT_LCD_SCL        	C3		//PC4--->>TFT --SCL/SCK
#define TFT_LCD_SDA        	C5		//PC5--->>TFT --SDA/DIN



//Һ�����ƿ���1�������궨��
#define	TFT_LCD_CS_SET  	Pin_Set(TFT_LCD_CS)   
#define	TFT_LCD_RS_SET  	Pin_Set(TFT_LCD_RS)    
#define	TFT_LCD_SDA_SET  	Pin_Set(TFT_LCD_SDA)    
#define	TFT_LCD_SCL_SET  	Pin_Set(TFT_LCD_SCL)     
#define	TFT_LCD_RST_SET  	Pin_Set(TFT_LCD_RST)     

//Һ�����ƿ���0�������궨��
#define	TFT_LCD_CS_CLR  	Pin_Reset(TFT_LCD_CS)   
#define	TFT_LCD_RS_CLR  	Pin_Reset(TFT_LCD_RS)     
#define	TFT_LCD_SDA_CLR  	Pin_Reset(TFT_LCD_SDA)       
#define	TFT_LCD_SCL_CLR  	Pin_Reset(TFT_LCD_SCL)   
#define	TFT_LCD_RST_CLR  	Pin_Reset(TFT_LCD_RST) 


//Ӳ��SPI�궨��
#define TFT_LCD_SPI		 		spi0
#define TFT_LCD_SPI_CS   		SPI_PCS0
#define TFT_LCD_SPI_MODE 		MASTER
#define TFT_LCD_SPI_High_Speed  35000000
#define TFT_LCD_SPI_Low_Speed   1000000



void SPI_TFT_Lcd_Reset(void);	//��λ
void SPI_TFT_Lcd_Init(void);	//��ʼ��
void SPI_TFT_Lcd_Clear(u16 Color);	//����
void SPI_TFT_Lcd_ShowPiture(const unsigned char *p); //��ʾ40*40 QQͼƬ
void SPI_TFT_Lcd_ShowFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);	//������ɫ�ͱ�����ɫ
void SPI_TFT_Lcd_displayimage032();//��ʾ����ͷ�Ҷ�ͼ��
void SPI_TFT_Lcd_displayimage032_bw() ;//��ʾ����ͷ��ֵ��ͼ��


#endif
