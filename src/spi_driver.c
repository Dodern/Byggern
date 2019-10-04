#include <avr/io.h>

#include "spi_driver.h"

void spi_init(void){
    /* Set MOSI and SCK output, all others input */
    DDRB |= (1<<DDB5)|(1<<DDB7); /*DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);*/
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void spi_slave_init(void){
    /* Set MISO output, all others input */
    DDRB |= (1<<DDB6); /*DDR_SPI = (1<<DD_MISO);*/
    /* Enable SPI */
    SPCR |= (1<<SPE);
}
    
void spi_transmit(char cData){
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF))){};
}

char spi_slave_receive(void){
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF))){};
    /* Return data register */
    return SPDR;
}