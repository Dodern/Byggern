#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "testSRAM.h"

#include "bit_macros.h"
#include "uart.h"
#include "xmem.h"
#include "mcp2515.h"
#include "testSRAM.h"
#include "can_controller_driver.h"
#include "can_driver.h"

void SRAM_test(void) {
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n\r");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    printf("Seed is: %d\n\r", seed);


    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = i+10;
        //uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        // xmem_write(some_value, i, 0x1800);
        // uint8_t retreived_value = xmem_read(i, 0x1800);
        if (retreived_value != some_value) {
            //printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i,
            //retreived_value, some_value);
            write_errors++;
        }
    }

    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed); // reset the PRNG to the state it had before the write phase
    printf("Seed is: %d\n\r", seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = i+10;
        // printf("some value %d\n\r", some_value);
        //uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        // uint8_t retreived_value = xmem_read(i, 0x1800);
        // printf("retreived value %d\n\r", retreived_value);
        if (retreived_value != some_value) {
            //printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrieval phase\n\n\r", write_errors, retrieval_errors);
}

void SRAM_test_can(void) {
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n\r");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    printf("Seed is: %d\n\r", seed);


    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = i+10;
        //uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        // xmem_write(some_value, i, 0x1800);
        // uint8_t retreived_value = xmem_read(i, 0x1800);
        if (retreived_value != some_value) {
            //printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i,
            //retreived_value, some_value);
            write_errors++;
        }
    }

    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed); // reset the PRNG to the state it had before the write phase
    printf("Seed is: %d\n\r", seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = i+10;
        // printf("some value %d\n\r", some_value);
        //uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        // uint8_t retreived_value = xmem_read(i, 0x1800);
        // printf("retreived value %d\n\r", retreived_value);
        if (retreived_value != some_value) {
            //printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    uint8_t sram_errors[2];
    sram_errors[0] = write_errors;
    printf("Write errors = %d\n\r", sram_errors[0]);
    sram_errors[1] = retrieval_errors;
    printf("Retrieval errors = %d\n\r", sram_errors[1]);
    can_send_message(SRAM_TESTED, 2, sram_errors, 2);

    printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrieval phase\n\n\r", write_errors, retrieval_errors);
}