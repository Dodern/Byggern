
#include "mcp2515.h"
#include "spi_driver.h"

// Initiates the controller by starting SPI interface, Resets the controller,
// and ensure that the controller is set up in Configuration Mode.
int can_controller_init(){

    spi_master_init(); // Initialize SPI
    can_controller_reset(); // Send reset-command

    // Self-test to see if in Configuration Mode
    int reg_canstat = can_controller_read(MCP_CANSTAT);
    if ((reg_canstat & MODE_MASK) != MODE_CONFIG) {
        printf(”MCP2515 is NOT in configuration mode
        after reset!\n”);
        return 1;
    }

    // More initialization

    return 0;
}

// Resetting the CAN controller only requires the instruction byte MPC_RESET
// It does not require sending of address or other data 
void can_controller_reset(){
    clear_bit(PORTB, CAN_SS); // Select CAN-controller
    spi_transmit(MCP_RESET); // Send write instruction
    set_bit(PORTB, CAN_SS); // Deselect CAN-controller
}

//Function that reads to the general registers that we specify.
int can_controller_read(int address) {
    int result;

    clear_bit(PORTB, CAN_SS); // Select CAN-controller
    
    spi_transmit(MCP_READ); // Send read instruction
    spi_transmit(address); // Send address
    result = spi_receive(); // Read result

    set_bit(PORTB, CAN_SS); // Deselect CAN-controller

    return result;
}

//Function that writes to the general registers that we specify.
void can_controller_write(int address, int data) {
    clear_bit(PORTB, CAN_SS); // Select CAN-controller
    
    spi_transmit(MCP_WRITE); // Send write instruction
    spi_transmit(address); // Send address
    spi_transmit(data); // Send address

    set_bit(PORTB, CAN_SS); // Deselect CAN-controller
}

// A function to be used to modify individual bits in a 
// particular register. This is not available for all registers
// so be careful to check before using it. The mask byte 
// indicates which bit that will be changed, indicated by a 1.
void can_controller_bit_modify(int address, int mask_byte, int data) {
    clear_bit(PORTB, CAN_SS); // Select CAN-controller
    
    spi_transmit(MCP_BITMOD); // Send write instruction
    spi_transmit(address); // Send address
    spi_transmit(mask_byte); // Send address
    spi_transmit(data); // Send address

    set_bit(PORTB, CAN_SS); // Deselect CAN-controller
}

// This function will choose one of the three transmission buffers in
// the MCP that it wishes to send. The input is the last three bits of the 
// address, but since we have the mcp2515.h the input argument can either be:
// MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2 
void can_controller_request_to_send(int rts_transmit_buffer) {
    clear_bit(PORTB, CAN_SS); // Select CAN-controller
    spi_transmit(rts_transmit_buffer); // Sends the instruction
    set_bit(PORTB, CAN_SS); // Deselect CAN-controller
}

// A function that reads the status buffers from the CAN Controller.
// The controller will repeat data transmission, but the SPIF flag in
// spi_transmit() will automatically stop after a byte.
int can_controller_read_status() {
    clear_bit(PORTB, CAN_SS); // Select CAN-controller

    spi_transmit(MCP_READ_STATUS); // Sending instruction
    int read_status = spi_receive(); 

    set_bit(PORTB, CAN_SS); // Deselect CAN-controller

    return read_status;
}