#include <stdlib.h>
#include <avr/interrupt.h>

#include "bit_macros.h"
#include "servo_driver.h"
#include "uart.h"


static uint8_t prev_pwm_input = 0;

void servo_init(){
    cli();
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
    servo_input(135);
}

void servo_input(uint8_t pwm_input){
    // printf("pwm input %d\n\r", pwm_input);
    // printf("previous pwm input %d\n\r", pwm_input);
    cli();
    if (abs(prev_pwm_input - pwm_input) > 20){
        // printf("inside if statement\n\r");
        // Set dutycyle to between 0.045 (0.9 ms, to the left) and 0.105 (2.1 ms, to the right)
        //printf("pwm_input = %d\n\r", pwm_input);
        float dutycycle = 0.045 + (255-(255-pwm_input))*0.000235;
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
    sei();
}

void servo_stop(){
    clear_bit(TCCR1B, CS11);
}

void servo_start(){
    set_bit(TCCR1B, CS11);
}