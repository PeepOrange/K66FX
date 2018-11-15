#include "Include.h"


int main(void)
{
    get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
    uart_init (uart2, 115200);                          //初始换串口与电脑通信
    camera_init();
	EnableInterrupts;
    for(;;)
	{
		if(mt9v032_finish_flag)
        {
            //seekfree_sendimg_032();
			SPI_TFT_Lcd_displayimage032((uint8_t *)image);
            mt9v032_finish_flag = 0;			
        }
	}
}

