/*
 * w5500_spi.h
 *
 *  Created on: May 20, 2024
 *      Author: ensty
 */

#ifndef INC_ETHERNET_W5500_SPI_H_
#define INC_ETHERNET_W5500_SPI_H_


#include "stm32f4xx_hal.h"

void W5500Init();

void  wizchip_select(void);
void  wizchip_deselect(void);

uint8_t wizchip_read();
void  wizchip_write(uint8_t wb);

void wizchip_readburst(uint8_t* pBuf, uint16_t len);
void  wizchip_writeburst(uint8_t* pBuf, uint16_t len);


#endif /* INC_ETHERNET_W5500_SPI_H_ */
