#ifndef _MK66_spi_h
#define _MK66_spi_h


#include "Misc.h"
#include "Common.h"
#include "MK66_port.h"
#include "MK66_gpio.h"
#include "MK66_port_cfg.h"
#include "stdlib.h"




//主从机模式

typedef enum
{
    MASTER,    //主机模式
    SLAVE      //从机模式
} SPI_CFG;


//模块号
typedef enum
{
    spi0,
    spi1,
    spi2
} SPIn_e;


//SPI模块片选号
typedef enum
{
    SPI_PCS0 = 1 << 0,
    SPI_PCS1 = 1 << 1,
    SPI_PCS2 = 1 << 2,
    SPI_PCS3 = 1 << 3,
    SPI_PCS4 = 1 << 4,
    SPI_PCS5 = 1 << 5,
} SPI_PCSn_e;

uint32 spi_init(SPIn_e spin, SPI_PCSn_e pcs, SPI_CFG master,uint32 baud);
void spi_mosi(SPIn_e spin, SPI_PCSn_e pcs, uint8 *modata, uint8 *midata, uint32 len);
void spi_mosi_cmd(SPIn_e spin, SPI_PCSn_e pcs, uint8 *mocmd , uint8 *micmd , uint8 *modata , uint8 *midata, uint32 cmdlen , uint32 len);





#endif

