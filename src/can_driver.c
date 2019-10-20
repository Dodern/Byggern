#include "can_controller_driver.h"
#include "can_driver.h"
#include "mcp2515.h"

void can_send_message(int id, int length, int* arr, int transmit_line){ 
    struct can_message message;
    message.id = id;
    message.length = length;
    for (int i = 0; i < length; i++){
        message.data[i] = arr[i];
    }
    int transmit_address = 0;
    int id_high_address = 0;
    int id_low_address = 0;
    int msg_length_address = 0;
    int request_to_send_address = 0;
    int transmit_buffer_flag_bit = 0;
    switch (transmit_line)
    {
    case 0:
        transmit_buffer_flag_bit = MCP_TX0IF;
        transmit_address = MCP_TXB0D0;
        id_high_address = MCP_TXB0SIDH;
        id_low_address = MCP_TXB0SIDL;
        msg_length_address = MCP_TXB0DLC;
        request_to_send_address = MCP_RTS_TX0;
        break;
    case 1:
        transmit_buffer_flag_bit = MCP_TX1IF;
        transmit_address = MCP_TXB1D0;
        id_high_address = MCP_TXB1SIDH;
        id_low_address = MCP_TXB1SIDL;
        msg_length_address = MCP_TXB1DLC;
        request_to_send_address = MCP_RTS_TX1;
        break;
    case 2:
        transmit_buffer_flag_bit = MCP_TX2IF;
        transmit_address = MCP_TXB2D0;
        id_high_address = MCP_TXB2SIDH;
        id_low_address = MCP_TXB2SIDL;
        msg_length_address = MCP_TXB2DLC;
        request_to_send_address = MCP_RTS_TX2;
        break;
    default:
        break;
    }
    can_controller_write_struct(transmit_address, &message);
    can_controller_bit_modify(id_low_address, 0b11100000, 0); // We only use ids that fit in the high address
    can_controller_write(id_high_address, id);
    can_controller_write(msg_length_address, message.length);
    can_controller_request_to_send(request_to_send_address);
    can_controller_bit_modify(MCP_CANINTF, transmit_buffer_flag_bit, 0);
}

struct can_message can_read_message(int read_line){
    int read_address = 0;
    int msg_length_address = 0;
    int id_high_address = 0;
    int receive_buffer_flag_bit = 0;
    switch (read_line)
    {
    case 0:
        receive_buffer_flag_bit = MCP_RX0IF;
        read_address = MCP_RXB0D0;
        id_high_address = MCP_RXB0SIDH;
        msg_length_address = MCP_RXB0DLC;
        break;
    case 1:
        receive_buffer_flag_bit = MCP_RX1IF;
        read_address = MCP_RXB1D0;
        id_high_address = MCP_RXB1SIDH;
        msg_length_address = MCP_RXB1DLC;
        break;
    default:
        break;
    }
    struct can_message message;
    message.length = can_controller_read(msg_length_address);
    message.id = can_controller_read(id_high_address);
    can_controller_read_struct(read_address, &message.data, message.length);
    can_controller_bit_modify(MCP_CANINTF, receive_buffer_flag_bit, 0);
    return message;
}