#include <util/delay.h>

#include "uart.h"
#include "mcp2515.h"
#include "spi_driver.h"
#include "can_controller_driver.h"

// Initiates the controller by starting SPI interface, Resets the controller,
// and ensure that the controller is set up in Configuration Mode.
int can_controller_init(){

    spi_master_init(); // Initialize SPI
    can_controller_reset(); // Send reset-command
    _delay_ms(100);
    // Self-test to see if in Configuration Mode
    int reg_canstat = can_controller_read(MCP_CANSTAT);
    printf("reg_canstat = %d\n\r", reg_canstat);
    printf("MODE_MASK = %d\n\r", MODE_MASK);
    printf("MODE_CONFIG = %d\n\r", MODE_CONFIG);
    if ((reg_canstat & MODE_MASK) != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset!\n\r");
        return 1;
    }
    
    printf("MCP2515 is in configuration mode after reset!\n\r");
    // Sets the CAN to loopback mode
    //can_controller_bit_modify(MCP_CANCTRL,0b11100000, MODE_LOOPBACK);
    can_controller_bit_modify(MCP_CANCTRL,0b11100000, MODE_NORMAL);
    printf("MCP2515 is now in normal mode after reset!\n\r");

    return 0;
}

// Resetting the CAN controller only requires the instruction byte MPC_RESET
// It does not require sending of address or other data 
void can_controller_reset(){
    spi_start_transmit(); // Select CAN-controller
    spi_transmit(MCP_RESET); // Send write instruction
    spi_end_transmit(); // Deselect CAN-controller
}

//Function that reads to the general registers that we specify.
/*The internal Address Pointer is automatically incremented to the next address once each byte of data is shifted out. 
Therefore, it is possible to read thenext consecutive register address by continuing to pro-vide clock pulses. 
Any number of consecutive registerlocations can be read sequentially using this method.*/ 
//Vi kan legge til slik at vi kan lese flere bytes etter hverandre
int can_controller_read(int address) {
    int result;

    spi_start_transmit(); // Select CAN-controller
    
    spi_transmit(MCP_READ); // Send read instruction
    spi_transmit(address); // Send address
    result = spi_receive(); // Read result

    spi_end_transmit(); // Deselect CAN-controller

    return result;
}

// int* can_controller_read_struct(int address) {
//     int length = 8;//can_controller_read(MCP_RXB0DLC);
//     int result[length];
//     printf("LengdeRead = %d\n\r",length);
//     spi_start_transmit(); // Select CAN-controller
    
//     spi_transmit(MCP_READ); // Send read instruction
//     spi_transmit(address); // Send address
//     for (uint8_t i = 0; i < 2; i++){     
//         result[i] = spi_receive(); // read data
//     }
//     spi_end_transmit(); // Deselect CAN-controller

//     return result;
// }

void can_controller_read_struct(int address, uint8_t* arr, int length) {
    //int length = 8;//can_controller_read(MCP_RXB0DLC);
    //int result[length];
    //printf("LengdeRead = %d\n\r",length);
    spi_start_transmit(); // Select CAN-controller
    
    spi_transmit(MCP_READ); // Send read instruction
    spi_transmit(address); // Send address
    for (uint8_t i = 0; i < length; i++){     
        arr[i] = spi_receive(); // read data
        //printf("Dette leste jeg: %d\n\r", arr[i]);
    }
    spi_end_transmit(); // Deselect CAN-controller
}


void can_controller_write(int address, int data) {
    spi_start_transmit(); // Select CAN-controller
    
    spi_transmit(MCP_WRITE); // Send write instruction
    spi_transmit(address); // Send address
    spi_transmit(data); // Send data

    spi_end_transmit(); // Deselect CAN-controller
}

void can_controller_write_struct(int address, struct can_message* msg) {
    spi_start_transmit(); // Select CAN-controller
    spi_transmit(MCP_WRITE); // Send write instruction
    spi_transmit(address); // Send address
    //printf("MsgLength %d\n\r", msg->length);
    for (uint8_t i = 0; i < msg->length; i++){ 
        spi_transmit(msg->data[i]); // Send data
        //printf("Dette printa jeg ut: %d\n\r", msg->data[i]);
    }
    spi_end_transmit(); // Deselect CAN-controller
}

// void can_controller_write_struct2(int address, struct can_message* msg) {
//     printf("MsgLength %d\n\r", msg->length);
//     for (uint8_t i = 0; i < msg->length; i++){ 
//         can_controller_write(address + i, msg->data[i]);
//         printf("Dette printa jeg ut: %d\n\r", msg->data[i]);
//     }
// }

// A function to be used to modify individual bits in a 
// particular register. This is not available for all registers
// so be careful to check before using it. The mask byte 
// indicates which bit that will be changed, indicated by a 1.
void can_controller_bit_modify(int address, int mask_byte, int data) {
    spi_start_transmit(); // Select CAN-controller
    
    spi_transmit(MCP_BITMOD); // Send write instruction
    spi_transmit(address); // Send address
    spi_transmit(mask_byte); // Send mask byte
    spi_transmit(data); // Send data

    spi_end_transmit(); // Deselect CAN-controller
}

// This function will choose one of the three transmission buffers in
// the MCP that it wishes to send. The input is the last three bits of the 
// address, but since we have the mcp2515.h the input argument can either be:
// MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2 
void can_controller_request_to_send(int rts_transmit_buffer) {
    spi_start_transmit(); // Select CAN-controller
    spi_transmit(rts_transmit_buffer); // Sends the instruction
    spi_end_transmit(); // Deselect CAN-controller
}

// A function that reads the status buffers from the CAN Controller.
// The controller will repeat data transmission, but the SPIF flag in
// spi_transmit() will automatically stop after a byte.
int can_controller_read_status() {
    spi_start_transmit(); // Select CAN-controller

    spi_transmit(MCP_READ_STATUS); // Sending instruction
    int read_status = spi_receive(); // Read status

    spi_end_transmit(); // Deselect CAN-controller

    return read_status;
}