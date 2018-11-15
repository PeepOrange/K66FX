#include "SEEKFREE_18TFT.h"

#define	TFT_X_MAX	128	//液晶X方宽度
#define TFT_Y_MAX	160 //液晶Y方宽度


#define DC_PIN		B17	//液晶命令位硬件定义		
#define REST_PIN	B16 //液晶复位引脚定义
#define DC(x)   	gpio_set(DC_PIN,x);
#define REST(x) 	gpio_set(REST_PIN,x);


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


void tft_delay(long t)
{
    while(t--);
}

void  Lcd_WriteIndex(uint8 dat)			//写命令
{	
    DC(0);
    spi_mosi(spi0,SPI_PCS0,&dat,&dat,1);		

}

void Lcd_WriteData(uint8 dat)			//写数据
{
    DC(1);
    spi_mosi(spi0,SPI_PCS0,&dat,&dat,1);
}

void  LCD_WriteData_16Bit(uint16 dat)	//向液晶屏写一个16位数据
{
    uint8 h,l;
    h = dat >> 8;
    l = (uint8)dat;
    
    DC(1);
    spi_mosi(spi0,SPI_PCS0,&h,&h,1); 	//写入高8位数据
    spi_mosi(spi0,SPI_PCS0,&l,&l,1);	//写入低8位数据
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶坐标设置
//  @param      x_start     	坐标x方向的起点
//  @param      y_start     	坐标y方向的起点
//  @param      x_end       	坐标x方向的终点
//  @param      y_end       	坐标y方向的终点
//  @return     void
//  @since      v1.0
//  Sample usage:               Lcd_SetRegion(0,0,10,10);// x、y的起点都是0，终点都是10
//-------------------------------------------------------------------------------------------------------------------
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_start+1);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_end+1);	

	Lcd_WriteIndex(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               dsp_single_colour(YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void dsp_single_colour(int color)
{
 	uint8 i,j;
	Lcd_SetRegion(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
 	for (i=0;i<TFT_Y_MAX;i++)
    	for (j=0;j<TFT_X_MAX;j++)
        	LCD_WriteData_16Bit(color);
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶初始化
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_init(void)
{	
    (void)spi_init(spi0,SPI_PCS0, MASTER,25*1000*1000);//硬件SPI初始化

    gpio_init(DC_PIN,GPO,0);
    gpio_init(REST_PIN,GPO,0);
    
    REST(0);
    tft_delay(999999);
    REST(1);
    tft_delay(999999);
    Lcd_WriteIndex(0x11);
    tft_delay(999999);

    Lcd_WriteIndex(0xB1); 
    Lcd_WriteData(0x01); 
    Lcd_WriteData(0x2C); 
    Lcd_WriteData(0x2D); 
    
    Lcd_WriteIndex(0xB2); 
    Lcd_WriteData(0x01); 
    Lcd_WriteData(0x2C); 
    Lcd_WriteData(0x2D); 
    
    Lcd_WriteIndex(0xB3); 
    Lcd_WriteData(0x01); 
    Lcd_WriteData(0x2C); 
    Lcd_WriteData(0x2D); 
    Lcd_WriteData(0x01); 
    Lcd_WriteData(0x2C); 
    Lcd_WriteData(0x2D); 
    
    Lcd_WriteIndex(0xB4);
    Lcd_WriteData(0x07); 

    Lcd_WriteIndex(0xC0); 
    Lcd_WriteData(0xA2); 
    Lcd_WriteData(0x02); 
    Lcd_WriteData(0x84); 
    Lcd_WriteIndex(0xC1); 
    Lcd_WriteData(0xC5); 
    
    Lcd_WriteIndex(0xC2); 
    Lcd_WriteData(0x0A); 
    Lcd_WriteData(0x00); 
    
    Lcd_WriteIndex(0xC3); 
    Lcd_WriteData(0x8A); 
    Lcd_WriteData(0x2A); 
    Lcd_WriteIndex(0xC4); 
    Lcd_WriteData(0x8A); 
    Lcd_WriteData(0xEE); 
    
    Lcd_WriteIndex(0xC5);
    Lcd_WriteData(0x0E); 
    
    Lcd_WriteIndex(0x36);
    Lcd_WriteData(0xC0); 
	Lcd_WriteData(0xC8); 

    Lcd_WriteIndex(0xe0); 
    Lcd_WriteData(0x0f); 
    Lcd_WriteData(0x1a); 
    Lcd_WriteData(0x0f); 
    Lcd_WriteData(0x18); 
    Lcd_WriteData(0x2f); 
    Lcd_WriteData(0x28); 
    Lcd_WriteData(0x20); 
    Lcd_WriteData(0x22); 
    Lcd_WriteData(0x1f); 
    Lcd_WriteData(0x1b); 
    Lcd_WriteData(0x23); 
    Lcd_WriteData(0x37); 
    Lcd_WriteData(0x00); 	
    Lcd_WriteData(0x07); 
    Lcd_WriteData(0x02); 
    Lcd_WriteData(0x10); 
    
    Lcd_WriteIndex(0xe1); 
    Lcd_WriteData(0x0f); 
    Lcd_WriteData(0x1b); 
    Lcd_WriteData(0x0f); 
    Lcd_WriteData(0x17); 
    Lcd_WriteData(0x33); 
    Lcd_WriteData(0x2c); 
    Lcd_WriteData(0x29); 
    Lcd_WriteData(0x2e); 
    Lcd_WriteData(0x30); 
    Lcd_WriteData(0x30); 
    Lcd_WriteData(0x39); 
    Lcd_WriteData(0x3f); 
    Lcd_WriteData(0x00); 
    Lcd_WriteData(0x07); 
    Lcd_WriteData(0x03); 
    Lcd_WriteData(0x10);  
    
    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00+2);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x80+2);
    
    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00+3);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x80+3);
    
    Lcd_WriteIndex(0xF0); 
    Lcd_WriteData(0x01); 
    Lcd_WriteIndex(0xF6);
    Lcd_WriteData(0x00); 
    
    Lcd_WriteIndex(0x3A);
    Lcd_WriteData(0x05); 
    
    
    Lcd_WriteIndex(0x29);

    dsp_single_colour(0xffff);//全白
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风(灰度摄像头)液晶显示函数
//  @param      *p     			图像数组地址
//  @return     void
//  @since      v1.0
//  Sample usage:              
//-------------------------------------------------------------------------------------------------------------------
void displayimage032(uint8 *p) 
{
    int i,j; 
	
    uint16 color = 0;
	uint16 temp = 0;
	
	for(i=0;i<120;i++)
    {
        Lcd_SetRegion(i,0,i,160-1);		//坐标设置
        for(j=0;j<160;j++)
        {	
			temp = *(p + i*MT9V032_ROW/120*MT9V032_COL + (MT9V032_COL-1)-j*(MT9V032_COL-1)/(160-1));//读取像素点
			
			color=(0x001f&((temp)>>3))<<11;
            color=color|(((0x003f)&((temp)>>2))<<5);
            color=color|(0x001f&((temp)>>3));
			LCD_WriteData_16Bit(color);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风(二值化摄像头)液晶显示函数
//  @param      *p     			图像数组地址
//  @return     void
//  @since      v1.0
//  @note      	图像分辨率需要设置在120(高)*160(宽)以下       
//-------------------------------------------------------------------------------------------------------------------
void displayimage7725(uint8 *p) 
{
    int i,j,k; 
	
    uint16 temp = 0;
	for(i=0;i<OV7725_H;i++)
    {
        Lcd_SetRegion(i,0,i,OV7725_W-1);		//坐标设置
        for(j=OV7725_W/8;j>=0;j--)
        {	
			temp = *( p+i*(OV7725_W/8)+ j );
		  	for(k=0; k<8; k++)
			{
				if( (temp>>k)&0x01 )	LCD_WriteData_16Bit(0xffff);
				else					LCD_WriteData_16Bit(0x0000);
			}
        }
    }
}

