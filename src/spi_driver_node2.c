#include <avr/io.h>

#include "spi_driver_node2.h"
#include "bit_macros.h"


void spi_master_init(void){
     /* Set MOSI and SCK output, all others input */
    //PORTB |= (1<<PINB0) | (1<<PINB1) | (1<<PINB2) | (1<<PINB7); /*PINBR_SPI = (1<<PINB_MOSI)|(1<<PINB_SCK);*/
    /* Set MOSI, SCK, and SS output, all others input */
    DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB7); /*DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);*/
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void spi_slave_init(void){
    /* Set MISO output, all others input */
    DDRB |= (1<<DDB3); /*DDR_SPI = (1<<DD_MISO);*/
    /* Enable SPI */
    SPCR |= (1<<SPE);
}

void spi_transmit(char cData){
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF))){};
}

char spi_receive(void){
    // Have to initiate reading by writing a dummy value to SPDR
    SPDR = 0x00;
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF))){};
    /* Return data register */
    return SPDR;
}

void spi_start_transmit(){
    clear_bit(PORTB, CAN_SS);
}

void spi_end_transmit(){
    set_bit(PORTB, CAN_SS);
}