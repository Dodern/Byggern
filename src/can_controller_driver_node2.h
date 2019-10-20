#ifndef __CAN_CONTROLLER_DRIVER_NODE2_H
#define __CAN_CONTROLLER_DRIVER_NODE2_H

#include <stdint.h>

struct can_message{
    unsigned int id;
    uint8_t length;
    int8_t data[8];
};

//int* can_controller_read_struct(int address);
void can_controller_read_struct(int address, int8_t* arr, int length);
void can_controller_write_struct(int address, struct can_message* msg);
void can_controller_write_struct2(int address, struct can_message* msg);
int can_controller_init();
void can_controller_reset(); // Send single command

int can_controller_read();
void can_controller_write(int address, int data);

void can_controller_bit_modify(int address, int mask_byte, int data);
void can_controller_request_to_send(int rts_transmit_buffer);
int can_controller_read_status();

#endif