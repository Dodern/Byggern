#ifndef BIT_MACROS_H
#define BIT_MACROS_H

int read_bit(int reg, int pin) {reg & (1 << pin);};

#endif
