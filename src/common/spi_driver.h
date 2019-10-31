#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H

#if defined (__AVR_ATmega162__)
    #define CAN_SS PORTB4
#elif defined (__AVR_ATmega2560__)
    #define CAN_SS PORTB7
#endif

void spi_master_init(void);
void spi_slave_init(void);
void spi_transmit(char cData);
char spi_receive(void);
void spi_start_transmit();
void spi_end_transmit();

#endif