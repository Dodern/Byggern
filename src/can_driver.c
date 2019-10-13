#include "can_controller_driver.h"
#include "can_driver.h"

void can_message_send(int transmit_buffer, int data){

    // int transmit_buffer = can_controller_read(0b00110110);
    // printf("CAN transmit buffer data preloading : %d\n\r", transmit_buffer);

    can_controller_write(transmit_buffer, data);

    // transmit_buffer = can_controller_read(0b00110110);
    // printf("CAN transmit buffer data: %d\n\r", transmit_buffer);

    can_controller_write(MCP_TXB0SIDH, 0x00);
    can_controller_write(MCP_TXB0SIDL, 0x00);
    can_controller_write(MCP_TXB0DLC, 0x01);

    can_controller_bit_modify(MCP_TXB0CTRL,0b00001000, 0b00001000);
    can_controller_request_to_send(MCP_RTS_TX0);

}
