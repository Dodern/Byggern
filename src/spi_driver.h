#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H

#define CAN_SS PORTB4

void spi_master_init(void);
void spi_slave_init(void);
void spi_transmit(char cData);
char spi_receive(void);

#endif