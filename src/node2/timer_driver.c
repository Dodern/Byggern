#include <stdlib.h>

#include "bit_macros.h"
#include "timer_driver.h"
#include "uart.h"


static uint8_t prev_pwm_input = 0;

void timer_init(){
    set_bit(TCCR1A, COM1A1); // Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at BOTTOM (non-inverting mode)
    set_bit(TCCR1A, WGM11); // PWM Fast mode bit 1
    set_bit(TCCR1B, CS11); // Clk active with prescaling to clk/8
    set_bit(TCCR1B, WGM12); // PWM Fast mode bit 2
    set_bit(TCCR1B, WGM13); // PWM Fast mode bit 3, When Fast mode is active Input capture function is disabled
    // Set TOP to 40 000 -> Sets period to 20 ms
    ICR1 = 0b1001110001000000;
    // Set OC1A as output
    set_bit(DDRB, PB5);
    // Set servo to 0
    timer_input(135);
}

void timer3_init(){
    //clear_bit(PORTE, PE3); // Set OC3A to 0
    //set_bit(TCCR3A, COM3A0); // Clear OC3A on compare match (Set to low)
    set_bit(TCCR3A, COM3A1); // Clear OC3A on compare match (Set to low)
    //set_bit(TCCR3A, WGM30); // Clear timer on compare match bit 0 (With TOP = ICR3)
    set_bit(TCCR3B, WGM32); // Clear timer on compare match bit 2 
    //set_bit(TCCR3B, WGM33); // Clear timer on compare match bit 3
    set_bit(TCCR3B, CS32); // Clk active with prescaling to clk/256
    OCR3A = 0b1111010000100100;
    //ICR3 = 0b1111010000100100; // Set TOP to 62500 (1 second)
    set_bit(DDRE, PE3); // Set OC3A as output
    printf("TCCR3B = %d\n\r", TCCR3B);
}

void timer3_reset(){
    set_bit(PORTE, PE3); // Set OC3A to 1
    TCNT3 = 0b0;
    printf("OC3A = %d\n\r", read_bit(PORTE, PE3));
}

void timer_input(uint8_t pwm_input){
    printf("pwm input %d\n\r", pwm_input);
    printf("previous pwm input %d\n\r", pwm_input);
    if (abs(prev_pwm_input - pwm_input) > 20){
        printf("inside if statement\n\r");
        // Set dutycyle to between 0.045 (0.9 ms, to the left) and 0.105 (2.1 ms, to the right)
        //printf("pwm_input = %d\n\r", pwm_input);
        float dutycycle = 0.045 + (255-pwm_input)*0.000235;
        if (pwm_input > 255 || dutycycle > 0.105){
            dutycycle = 0.105;
        } else if (pwm_input < 0 || dutycycle < 0.045){
            dutycycle = 0.045;
        }
        //printf("dutycycle = %d\n\r", (int) (dutycycle*1000));
        // Scaling the dutycycle in relation to the TOP value
        OCR1A = (int) (dutycycle * ICR1);
        //printf("OCR1A = %d\n\r", OCR1A);
        prev_pwm_input = pwm_input;
    }
}