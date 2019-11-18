#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc_driver.h"
#include "uart.h"
#include "bit_macros.h"

void adc_init(){
    // cli();
    clear_bit(DDRF, PF0); // Setting as input
    set_bit(ADCSRA, ADEN); // To enable the ADC

    // Prescaler set to 4 times lower
    clear_bit(ADCSRA, ADPS0); // REF table, will cause ADC_clock to be 4 times slower than system clock.
    set_bit(ADCSRA, ADPS1); // REF table, will cause ADC_clock to be 4 times slower than system clock.
    clear_bit(ADCSRA, ADPS2); // REF table, will cause ADC_clock to be 4 times slower than system clock.

    // Setting internal voltage
    clear_bit(ADMUX, REFS0); // REF table, Internal 1.1 voltage reference
    set_bit(ADMUX, REFS1); // REF table, Internal 1.1 voltage reference
    // For single ended inputs on ADC0 pin, the ADMUX bits
    // are automatically set to read ADC0
    adc_read();
}

int adc_read(){
    // cli();
    set_bit(ADCSRA, ADSC); // To start conversion
    while (!read_bit(ADCSRA, ADIF)){}; // Waits until flag is set

    // Reading from both registries
    uint8_t data_low = ADCL;
    uint16_t data_high = ADCH;
    uint16_t data = (data_high << 8) | (data_low & 0xFF);
    // int data = data_low + data_high*0b10000000;
    // sei();
    return data;
}

void adc_print(){
    int adc_data = adc_read();
    printf("ADC Node 2 value: %d\n\r", adc_data);
}