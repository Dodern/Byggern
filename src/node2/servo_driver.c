#include <stdlib.h>
#include <avr/interrupt.h>

#include "bit_macros.h"
#include "servo_driver.h"
#include "uart.h"


static uint8_t prev_pwm_input = 0;

void servo_init(){
    printf("Running servo init\n\r");
    cli();
    //set_bit(DDRB, PB4);
    
    //set_bit(DDRB, PB6);
    // set_bit(PORTB, PB4);
    // set_bit(PORTB, PB5);
    // set_bit(PORTB, PB6);
    set_bit(TCCR1A, COM1A1); // Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at BOTTOM (non-inverting mode)
    //set_bit(TCCR1A, COM1B1);
    set_bit(TCCR1A, WGM11); // PWM Fast mode bit 1
    set_bit(TCCR1B, CS11); // Clk active with prescaling to clk/8
    set_bit(TCCR1B, WGM12); // PWM Fast mode bit 2
    set_bit(TCCR1B, WGM13); // PWM Fast mode bit 3, When Fast mode is active Input capture function is disabled
    // Set TOP to 40 000 -> Sets period to 20 ms
    ICR1 = 0b1001110001000000;
    // Set OC1A as output
    set_bit(DDRB, PB5);
    // Set servo to 0
    // servo_input(135);
}

void servo_input(uint8_t pwm_input){
    printf("Moving servo\n\r");    
    printf("pwm input %d\n\r", pwm_input);
    printf("previous pwm input %d\n\r", prev_pwm_input);
    cli();
    if (abs(prev_pwm_input - pwm_input) > 20){
        printf("inside if statement\n\r");
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
        printf("OCR1A = %d\n\r", OCR1A);
        printf("OCR1B = %d\n\r", OCR1B);
        prev_pwm_input = pwm_input;
    }
    sei();
}

void servo_stop(){
    printf("Servo Stopped\n\r");
    clear_bit(TCCR1B, CS11);
}

void servo_start(){
    printf("Starting servo\n\r");
    set_bit(TCCR1B, CS11);
}

void servo_init_timer4(){
    printf("Running servo init\n\r");
    cli();
    //set_bit(DDRB, PB4);
    
    //set_bit(DDRB, PB6);
    // set_bit(PORTB, PB4);
    // set_bit(PORTB, PB5);
    // set_bit(PORTB, PB6);
    set_bit(TCCR4A, COM4A1); // Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at BOTTOM (non-inverting mode)
    //set_bit(TCCR1A, COM1B1);
    set_bit(TCCR4A, WGM41); // PWM Fast mode bit 1
    set_bit(TCCR4B, CS41); // Clk active with prescaling to clk/8
    set_bit(TCCR4B, WGM42); // PWM Fast mode bit 2
    set_bit(TCCR4B, WGM43); // PWM Fast mode bit 3, When Fast mode is active Input capture function is disabled
    // Set TOP to 40 000 -> Sets period to 20 ms
    ICR4 = 0b1001110001000000;
    // Set OC1A as output
    set_bit(DDRH, PH4);
    // Set servo to 0
    // servo_input(135);
}

void servo_input_timer4(uint8_t pwm_input){
    //printf("Moving servo\n\r");    
    //printf("pwm input %d\n\r", pwm_input);
    //printf("previous pwm input %d\n\r", prev_pwm_input);
    cli();
    if (abs(prev_pwm_input - pwm_input) > 20){
        //printf("inside if statement\n\r");
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
        OCR4A = (int) (dutycycle * ICR4);
        printf("OCR4A = %d\n\r", OCR4A);
        printf("OCR4B = %d\n\r", OCR4B);
        prev_pwm_input = pwm_input;
    }
    sei();
}