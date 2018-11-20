#include "Include.h"


int main(void)
{
    get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
	SPI_TFT_Lcd_Init();
   // uart_init (uart2, 115200);                          //初始换串口与电脑通信
	camera_init();

	EnableInterrupts;
    for(;;)
	{
		if(mt9v032_finish_flag)
        {
		  	disable_irq(PORTC_IRQn);                             		//关闭PTC的中断
			SPI_TFT_Lcd_displayimage032_bw();
			enable_irq (PORTC_IRQn);
            mt9v032_finish_flag = 0;				
        }
	}
}

