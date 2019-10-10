#ifndef BIT_MACROS_H
#define BIT_MACROS_H

#define set_bit(reg, pin) (reg |= (1 << pin))
#define clear_bit(reg, pin) (reg &= ~(1 << pin))
#define read_bit(reg, pin) (reg & (1 << pin))

#endif