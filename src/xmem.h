#pragma once
#include <avr/io.h>

#define BASE_ADDRESS 0x1000

// Address Defintions
// #define IO_MEMORY ((AVR162_IO_MEMORY_REGS*)0x1000)

// // Address Structs
// typedef struct {
//     volatile uint16_t OLED_COMMAND[32];
//     volatile uint16_t OLED_DATA[32];
//     volatile uint16_t ADC[64];
//     volatile uint16_t SRAM[128];
// }AVR162_IO_MEMORY_REGS;

void xmem_init(void);
void xmem_write(uint8_t data, uint16_t addr);
uint8_t xmem_read(uint16_t addr);