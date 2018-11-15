#include "Serial_oscilloscope.h"


//unsigned char data_to_send[16];
void Data_Send(UARTn uratn,unsigned short int *pst)
{
        unsigned char _cnt=0;	unsigned char sum = 0;
	unsigned char data_to_send[23];         //发送缓存
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=(unsigned char)(pst[0]>>8);  //高8位
	data_to_send[_cnt++]=(unsigned char)pst[0];  //低8位
	data_to_send[_cnt++]=(unsigned char)(pst[1]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[1];
	data_to_send[_cnt++]=(unsigned char)(pst[2]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[2];
	data_to_send[_cnt++]=(unsigned char)(pst[3]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[3];
	data_to_send[_cnt++]=(unsigned char)(pst[4]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[4];
	data_to_send[_cnt++]=(unsigned char)(pst[5]>>8);
	data_to_send[_cnt++]=(unsigned char)pst[5];
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	
	
	data_to_send[3] = _cnt-4;
	
	sum = 0;
        
	for(unsigned char i=0;i<_cnt;i++)
		sum += data_to_send[i];
        
	data_to_send[_cnt++] = sum;
    
    for(unsigned char i=0;i<_cnt;i++)
    uart_putchar(uratn,data_to_send[i]);    
}