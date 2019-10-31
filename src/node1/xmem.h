#ifndef XMEM_H
#define XMEM_H

#include <avr/io.h>

// Address Defintions
#define SRAM 0x1800
#define ADC 0x1400
#define OLED_DATA 0x1200
#define OLED_COMMAND 0x1000


void xmem_init(void);
void xmem_write(uint8_t data, uint16_t addr, uint16_t base_address);
uint8_t xmem_read(uint16_t addr, uint16_t base_address);

#endif