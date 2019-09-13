#include "xmem.h"

void xmem_init(void){
    MCUCR |= (1 << SRE);//enable XMEM
    SFIOR |= (1 << XMM2);//mask unused bits PC7-PC4
}

void xmem_write(uint8_t data, uint16_t addr, uint16_t base_address){
    volatile char *ext_mem = (char *) base_address; // Start address for the SRAM
    ext_mem[addr] = data;
}

uint8_t xmem_read(uint16_t addr, uint16_t base_address){
    volatile char *ext_mem = (char *) base_address; // Start address for the SRAM
    uint8_t ret_val = ext_mem[addr];
    return ret_val;
}