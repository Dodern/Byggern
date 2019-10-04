#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H

void spi_transmit(char cData);
void spi_init(void);
void spi_slave_init(void);
char spi_slave_receive(void);

#endif