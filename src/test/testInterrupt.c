#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"
#include "oled_driver.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// **** Added defines
#define SREG_I 7
#define INT0_BIT 6
#define INT1_BIT 7
#define ISC00_BIT 0
#define ISC01_BIT 1

volatile int interrupt_count = 0;

ISR(INT0_vect){
  interrupt_count++;
  GIFR |= 0;
}

ISR(INT1_vect){
  interrupt_count++;
}

int main(void){
    // Initiating various devices
    USART_Init ( MYUBRR );
    xmem_init();
    adc_init();
    oled_init();
    can_controller_init();

    //**** New Code 


    //Enabling direction of interrupts
    clear_bit(DDRD, DDD2); //not necessary, but to be sure

    //Enabling interrupts;
    /* set_bit(SREG, SREG_I); */
    set_bit(GICR, INT0_BIT);
    ////*** Have to check if the interrupt pin on MCP is active high or active low.
    /* // This sets the interrupts to be enabled detecting a rising edge */
    /* set_bit(MCUCR, ISC00); */
    /* set_bit(MCUCR, ISC01); */
    // This sets the interrupts to be enabled detecting a falling edge
    clear_bit(MCUCR, ISC00);
    set_bit(MCUCR, ISC01);
    ////*** Have to check if the interrupt pin on MCP is active high or active low.
    sei(); // This sets the Global Interrupt Pin in SREG

    while (1) {

        printf("Interrupt counter is now at %d \n\r", interrupt_count);
        _delay_ms(2000);

    }
    return 0;
}
