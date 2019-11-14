#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "bit_macros.h"
#include "solenoid_driver.h"

#define SOLENOID_TRIG_PIN PH5

void solenoid_init(){
    set_bit(DDRH, SOLENOID_TRIG_PIN); // Set the direction of solenoid trigger pin
    set_bit(PORTH, SOLENOID_TRIG_PIN); // Set the output initially high
}

void solenoid_punch(){
    clear_bit(PORTH, SOLENOID_TRIG_PIN);
    _delay_ms(1500);
    set_bit(PORTH, SOLENOID_TRIG_PIN);
}