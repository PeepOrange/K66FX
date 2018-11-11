#include "SPI_TFT_LCD.h"
#include "LCD_Font.h"


/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换
#define USE_HORIZONTAL  		1	//定义是否使用横屏 		0,不使用.1,使用.

//-----------------------------SPI 总线配置--------------------------------------//
#define USE_HARDWARE_SPI     1  //1:Enable Hardware SPI;  0:USE Soft SPI

//-------------------------屏幕物理像素设置--------------------------------------//
#define LCD_X_SIZE	        176
#define LCD_Y_SIZE	        220

#if USE_HORIZONTAL//如果定义了横屏 
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif
//////////////////////////////////////////////////////////////////////////////////
	 
//RGB常用颜色
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   		//灰色0   3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1   00000 000000 00000
#define GRAY2   0x4208      	//灰色2   1111111111011111


void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);


//---------------------------------function----------------------------------------------------//
/****************************************************************************
* 名    称：void LCD_GPIO_Init(void)
* 功    能：STM32_模拟SPI所用到的GPIO初始化
* 入口参数：无
* 出口参数：无
* 说    明：初始化模拟SPI所用的GPIO
****************************************************************************/
 void SPIv_GPIO_Init(void)
{
   gpio_init(TFT_LCD_LED,GPO,1);
   gpio_init(TFT_LCD_RS,GPO,1);
   gpio_init(TFT_LCD_CS,GPO,1);
   gpio_init(TFT_LCD_RST,GPO,1);
   gpio_init(TFT_LCD_SCL,GPO,1);
   gpio_init(TFT_LCD_SDA,GPO,1);

}
/****************************************************************************
* 名    称：void  SPIv_WriteData(u8 Data)
* 功    能：STM32_模拟SPI写一个字节数据底层函数
* 入口参数：Data
* 出口参数：无
* 说    明：STM32_模拟SPI读写一个字节数据底层函数
****************************************************************************/
 void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  TFT_LCD_SDA_SET; //输出数据
      else TFT_LCD_SDA_CLR;
	   
      TFT_LCD_SCL_CLR;       
      TFT_LCD_SCL_SET;
      Data<<=1; 
	}
}

/****************************************************************************
* 名    称：u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
* 功    能：STM32_硬件SPI读写一个字节数据底层函数
* 入口参数：SPIx,Byte
* 出口参数：返回总线收到的数据
* 说    明：STM32_硬件SPI读写一个字节数据底层函数
****************************************************************************/
static u8 SPI_WriteByte(u8 Byte)
{
  u8 data=Byte;
  spi_mosi(TFT_LCD_SPI, TFT_LCD_SPI_CS, &data, &data, 1);  
  return data;
} 

/****************************************************************************
* 名    称：void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
* 功    能：设置SPI的速度
* 入口参数：SPIx,SpeedSet
* 出口参数：无
* 说    明：SpeedSet:1,高速;0,低速;
****************************************************************************/
 void SPI_SetSpeed(u8 SpeedSet)
{
	if(SpeedSet==1)//高速	16M
	{
  spi_init(TFT_LCD_SPI,TFT_LCD_SPI_CS,TFT_LCD_SPI_MODE,TFT_LCD_SPI_High_Speed);
	}
	else//低速 1M
	{
  spi_init(TFT_LCD_SPI,TFT_LCD_SPI_CS,TFT_LCD_SPI_MODE,TFT_LCD_SPI_Low_Speed);
	}
} 

/****************************************************************************
* 名    称：SPI2_Init(void)
* 功    能：STM32_SPI2硬件配置初始化
* 入口参数：无
* 出口参数：无
* 说    明：STM32_SPI2硬件配置初始化,配置为16M
****************************************************************************/
static void SPI_TFT_LCD_Init(void)	
{
   gpio_init(TFT_LCD_RS,GPO,1);
   gpio_init(TFT_LCD_RST,GPO,1);
   spi_init(TFT_LCD_SPI,TFT_LCD_SPI_CS,TFT_LCD_SPI_MODE,TFT_LCD_SPI_High_Speed);
}

/****************************************************************************
* 名    称：Lcd_WriteIndex(u8 Index)
* 功    能：向液晶屏写一个8位指令
* 入口参数：Index   寄存器地址
* 出口参数：无
* 说    明：调用前需先选中控制器，内部函数
****************************************************************************/
static void Lcd_WriteIndex(u8 Index)
{

#if USE_HARDWARE_SPI   
   TFT_LCD_RS_CLR;
   SPI_WriteByte(Index);
#else
   TFT_LCD_CS_CLR;
   TFT_LCD_RS_CLR;   
   SPIv_WriteData(Index);
   TFT_LCD_CS_SET;   
#endif 
}

/****************************************************************************
* 名    称：Lcd_WriteData(u8 Data)
* 功    能：向液晶屏写一个8位数据
* 入口参数：dat     寄存器数据
* 出口参数：无
* 说    明：向控制器指定地址写入数据，内部函数
****************************************************************************/
static void Lcd_WriteData(u8 Data)
{

#if USE_HARDWARE_SPI 
   TFT_LCD_RS_SET;     
   SPI_WriteByte(Data);
#else
   TFT_LCD_CS_CLR;
   TFT_LCD_RS_SET;   
   SPIv_WriteData(Data);
   TFT_LCD_CS_SET;   
#endif 
}



/****************************************************************************
* 名    称：void Lcd_WriteData_16Bit(u16 Data)
* 功    能：向液晶屏写一个16位数据
* 入口参数：Data
* 出口参数：无
* 说    明：向控制器指定地址写入一个16位数据
****************************************************************************/
static void Lcd_WriteData_16Bit(u16 Data)
{	
	Lcd_WriteData(Data>>8);
	Lcd_WriteData(Data);	
}


/****************************************************************************
* 名    称：void LCD_WriteReg(u8 Index,u16 Data)
* 功    能：写寄存器数据
* 入口参数：Index,Data
* 出口参数：无
* 说    明：本函数为组合函数，向Index地址的寄存器写入Data值
****************************************************************************/
static void LCD_WriteReg(u8 Index,u16 Data)
{
	Lcd_WriteIndex(Index);
  	Lcd_WriteData_16Bit(Data);
}


/****************************************************************************
* 名    称：void SPI_TFT_Lcd_Reset(void)
* 功    能：液晶硬复位函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化前需执行一次复位操作
****************************************************************************/
void SPI_TFT_Lcd_Reset(void)
{
	TFT_LCD_RST_CLR;
	systick_delay_ms(100);
	TFT_LCD_RST_SET;
	systick_delay_ms(50);
}
/****************************************************************************
* 名    称：void SPI_TFT_Lcd_Init(void)
* 功    能：液晶初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化_ILI9225_176X220
****************************************************************************/
void SPI_TFT_Lcd_Init(void)
{	
#if USE_HARDWARE_SPI //使用硬件SPI
	SPI_TFT_LCD_Init();
#else	
	LCD_GPIO_Init();//使用模拟SPI
#endif
	SPI_TFT_Lcd_Reset(); //Reset before LCD Init.

	//************* Start Initial Sequence **********//
  Lcd_WriteIndex(0x02); Lcd_WriteData_16Bit(0x0100); // set 1 line inversion
#if USE_HORIZONTAL//如果定义了横屏
	//R01H:SM=0,GS=0,SS=0 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x01, 0x001C); // set the display line number and display direction
	//R03H:BGR=1,ID0=1,ID1=1,AM=1 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x03, 0x1038); // set GRAM write direction .
#else//竖屏
	//R01H:SM=0,GS=0,SS=1 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x01, 0x011C); // set the display line number and display direction 
	//R03H:BGR=1,ID0=1,ID1=1,AM=0 (for details,See the datasheet of ILI9225)
	LCD_WriteReg(0x03, 0x1030); // set GRAM write direction.
#endif

  Lcd_WriteIndex(0x08); Lcd_WriteData_16Bit(0x0808); // set BP and FP
  Lcd_WriteIndex(0x0B); Lcd_WriteData_16Bit(0x1100); //frame cycle
  Lcd_WriteIndex(0x0C); Lcd_WriteData_16Bit(0x0000); // RGB interface setting R0Ch=0x0110 for RGB 18Bit and R0Ch=0111for RGB16Bit
  Lcd_WriteIndex(0x0F); Lcd_WriteData_16Bit(0x1401); // Set frame rate----0801
  Lcd_WriteIndex(0x15); Lcd_WriteData_16Bit(0x0000); //set system interface
  Lcd_WriteIndex(0x20); Lcd_WriteData_16Bit(0x0000); // Set GRAM Address
  Lcd_WriteIndex(0x21); Lcd_WriteData_16Bit(0x0000); // Set GRAM Address
  //*************Power On sequence ****************//
    systick_delay_ms(50);                         // Delay 50ms
  Lcd_WriteIndex(0x10); Lcd_WriteData_16Bit(0x0800); // Set SAP,DSTB,STB----0A00
  Lcd_WriteIndex(0x11); Lcd_WriteData_16Bit(0x1F3F); // Set APON,PON,AON,VCI1EN,VC----1038
    systick_delay_ms(50);                         // Delay 50ms
  Lcd_WriteIndex(0x12); Lcd_WriteData_16Bit(0x0121); // Internal reference voltage= Vci;----1121
  Lcd_WriteIndex(0x13); Lcd_WriteData_16Bit(0x006F); // Set GVDD----0066
  Lcd_WriteIndex(0x14); Lcd_WriteData_16Bit(0x4349); // Set VCOMH/VCOML voltage----5F60
  //-------------- Set GRAM area -----------------//
  Lcd_WriteIndex(0x30); Lcd_WriteData_16Bit(0x0000);
  Lcd_WriteIndex(0x31); Lcd_WriteData_16Bit(0x00DB);
  Lcd_WriteIndex(0x32); Lcd_WriteData_16Bit(0x0000);
  Lcd_WriteIndex(0x33); Lcd_WriteData_16Bit(0x0000);
  Lcd_WriteIndex(0x34); Lcd_WriteData_16Bit(0x00DB);
  Lcd_WriteIndex(0x35); Lcd_WriteData_16Bit(0x0000);
  Lcd_WriteIndex(0x36); Lcd_WriteData_16Bit(0x00AF);
  Lcd_WriteIndex(0x37); Lcd_WriteData_16Bit(0x0000);
  Lcd_WriteIndex(0x38); Lcd_WriteData_16Bit(0x00DB);
  Lcd_WriteIndex(0x39); Lcd_WriteData_16Bit(0x0000);
  // ----------- Adjust the Gamma Curve ----------//
  Lcd_WriteIndex(0x50); Lcd_WriteData_16Bit(0x0001);  //0400
  Lcd_WriteIndex(0x51); Lcd_WriteData_16Bit(0x200B);  //060B
  Lcd_WriteIndex(0x52); Lcd_WriteData_16Bit(0x0000);  //0C0A
  Lcd_WriteIndex(0x53); Lcd_WriteData_16Bit(0x0404);  //0105
  Lcd_WriteIndex(0x54); Lcd_WriteData_16Bit(0x0C0C);  //0A0C
  Lcd_WriteIndex(0x55); Lcd_WriteData_16Bit(0x000C);  //0B06
  Lcd_WriteIndex(0x56); Lcd_WriteData_16Bit(0x0101);  //0004
  Lcd_WriteIndex(0x57); Lcd_WriteData_16Bit(0x0400);  //0501
  Lcd_WriteIndex(0x58); Lcd_WriteData_16Bit(0x1108);  //0E00
  Lcd_WriteIndex(0x59); Lcd_WriteData_16Bit(0x050C);  //000E
  systick_delay_ms(50);                                     // Delay 50ms
  Lcd_WriteIndex(0x07); Lcd_WriteData_16Bit(0x1017);
  Lcd_WriteIndex(0x22);	
}



/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
static void Lcd_SetXY(u16 Xpos, u16 Ypos)
{	
#if USE_HORIZONTAL//如果定义了横屏  	    	
	LCD_WriteReg(0x21,Xpos);
	LCD_WriteReg(0x20,Ypos);
#else//竖屏	
	LCD_WriteReg(0x20,Xpos);
	LCD_WriteReg(0x21,Ypos);
#endif
	Lcd_WriteIndex(0x22);		
} 
/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
//设置显示窗口
static void Lcd_SetRegion(u8 xStar, u8 yStar,u8 xEnd,u8 yEnd)
{
#if USE_HORIZONTAL//如果定义了横屏	
	LCD_WriteReg(0x38,xEnd);
	LCD_WriteReg(0x39,xStar);
	LCD_WriteReg(0x36,yEnd);
	LCD_WriteReg(0x37,yStar);
	LCD_WriteReg(0x21,xStar);
	LCD_WriteReg(0x20,yStar);
#else//竖屏	
	LCD_WriteReg(0x36,xEnd);
	LCD_WriteReg(0x37,xStar);
	LCD_WriteReg(0x38,yEnd);
	LCD_WriteReg(0x39,yStar);
	LCD_WriteReg(0x20,xStar);
	LCD_WriteReg(0x21,yStar);
#endif
	Lcd_WriteIndex(0x22);	
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：xy坐标和颜色数据
返回值：无
*************************************************/
 void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetXY(x,y);
	Lcd_WriteData_16Bit(Data);
}    

/*************************************************
函数名： SPI_TFT_Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void SPI_TFT_Lcd_Clear(u16 Color)               
{	
   unsigned int i;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   TFT_LCD_RS_SET;	
   for(i=0;i<38720;i++)
   {	
#if USE_HARDWARE_SPI   
		SPI_WriteByte(Color>>8);
		SPI_WriteByte(Color);
#else
   		TFT_LCD_CS_CLR;		
		SPIv_WriteData(Color>>8);
		SPIv_WriteData(Color);
		TFT_LCD_CS_SET;		
#endif 
   }   
}


//16位BMP 40X40 QQ图像取模数据
//Image2LCD取模选项设置
//水平扫描
//16位
//40X40
//不包含图像头数据
//自左至右
//自顶至底
//低位在前
void SPI_TFT_Lcd_ShowPiture(const unsigned char *p) //显示40*40 QQ图片
{
  	int i,j,k; 
	unsigned char picH,picL; 
	SPI_TFT_Lcd_Clear(GRAY0);

	for(k=0;k<Y_MAX_PIXEL/40;k++)
	{
	   	for(j=0;j<X_MAX_PIXEL/40;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				Lcd_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}




void SPI_TFT_Lcd_ShowFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)	//字体颜色和背景颜色
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{
		

			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x01<<j))	Gui_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x01<<j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
		
	}
}

