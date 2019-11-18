#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "bit_macros.h"
#include "solenoid_driver.h"
#include "uart.h"

volatile int timer_state = 0;

ISR(TIMER3_CAPT_vect){ 
    timer_state = 0; 
    printf("Timer state = %d\n\r", timer_state); 
    solenoid_timer_stop();
} 

// Checking if ISR is bad
// ISR(BAD_ISR){
//     printf("BAD ISR\n\r");
// }

void solenoid_init(){

    cli();
    //Setting up trigger for Solenoid
    set_bit(DDRH, SOLENOID_TRIG_PIN); // Set the direction of solenoid trigger pin
    set_bit(PORTH, SOLENOID_TRIG_PIN); // Set the output initially high

    //Disabling interrupts while setting up
    

    // Interrupt
    set_bit(TIMSK3, ICIE3); // Enable interrupts when ICFn flag is set

    // Timer 3 setup
    clear_bit(TCCR3A, COM3A0);
    clear_bit(TCCR3A, COM3A1); // OC3A Disconnected
    set_bit(TCCR3B, WGM32); // Clear timer on compare match bit 2 
    set_bit(TCCR3B, WGM33); // Clear timer on compare match bit 3
    set_bit(TCCR3B, CS32); // Clk active with prescaling to clk/256
    ICR3 = 0b1111010000100100; // Set TOP to 62500 (1 second)
    solenoid_timer_stop();

    //Output
    printf("TCCR3B = %d\n\r", TCCR3B);
}

void solenoid_punch(){
    // Check for timer
    if(timer_state == 1) {
        printf("Timer is not done\n\r");
        return;
    }

    printf("Solenoid punch!\n\r");
    cli();
    clear_bit(PORTH, SOLENOID_TRIG_PIN);
    _delay_ms(1500);
    set_bit(PORTH, SOLENOID_TRIG_PIN);
    sei();
    // solenoid_timer_reset();
    solenoid_timer_start();
}

void solenoid_timer_reset(){
    TCNT3 = 0b0;
    timer_state = 1;
}

void solenoid_timer_read(){
    printf("TCNT3 = %u\n\r", TCNT3);
}

void solenoid_timer_start(){
    timer_state = 1;
    set_bit(TCCR3B, CS32); // Clk active with prescaling to clk/256
}

void solenoid_timer_stop(){
    clear_bit(TCCR3B, CS30);
    clear_bit(TCCR3B, CS31);
    clear_bit(TCCR3B, CS32); // Clear clk bits
}
