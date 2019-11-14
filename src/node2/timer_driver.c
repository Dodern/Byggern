#include <stdlib.h>

#include "bit_macros.h"
#include "timer_driver.h"
#include "uart.h"

volatile int interruptcounter = 0;

ISR(TIMER3_CAPT_vect){
    interruptcounter++;
    printf("Interruptcounter = %d\n\r", interruptcounter);
}


void timer3_init(){
    // Interrupt
    clear_bit(TIMSK3, ICIE3);
    //set_bit(TIMSK3, ICIE3); // Enable interrupts when ICFn flag is set

    // Timer
    clear_bit(TCCR3A, COM3A0);
    clear_bit(TCCR3A, COM3A1); // OC3A Disconnected
    set_bit(TCCR3B, WGM32); // Clear timer on compare match bit 2 
    set_bit(TCCR3B, WGM33); // Clear timer on compare match bit 3
    set_bit(TCCR3B, CS32); // Clk active with prescaling to clk/256
    ICR3 = 0b1111010000100100; // Set TOP to 62500 (1 second)
    int16_t second = 0b1111010000100100;
    int8_t second_high = 
    ICR3 = 0b1111010000100100; // Set TOP to 62500 (1 second)

    //Output
    printf("TCCR3B = %d\n\r", TCCR3B);
}

void timer3_reset(){
    TCNT3 = 0b0;
    //printf("TCNT3 = %d\n\r", TCNT3);
}

void read_timer(){
    printf("TCNT3 = %d\n\r", TCNT3);
}
