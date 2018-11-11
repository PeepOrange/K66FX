#ifndef _MK66_uart_h
#define _MK66_uart_h



#include "Misc.h"
#include "Common.h"
#include "MK66_port.h"
#include "MK66_gpio.h"
#include "MK66_port_cfg.h"
#include "stdio.h"

typedef enum
{
    uart0,
    uart1,
    uart2,
    uart3,
    uart4,
} UARTn;



#define DEBUG_PORT  uart2
#define DEBUG_BAUD  115200

void uart_init(UARTn uartn, uint32 baud);
void uart_putchar (UARTn uartn, uint8 ch);
void uart_putbuff (UARTn uartn, uint8 *buff, uint32 len);
void uart_putstr (UARTn uartn, const uint8 *str);
void uart_getchar (UARTn uartn, uint8 *ch);
char uart_querychar (UARTn uartn, uint8 *ch);
void uart_rx_irq_en(UARTn uartn);
void uart_txc_irq_en(UARTn uartn);
void uart_rx_irq_dis(UARTn uartn);
void uart_txc_irq_dis(UARTn uartn);

#endif
