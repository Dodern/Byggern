#ifndef __CAN_CONTROLLER_DRIVER_H
#define __CAN_CONTROLLER_DRIVER_H

int can_controller_init();
void can_controller_reset(); // Send single command

int can_controller_read();
void can_controller_write(int address, int data);

void can_controller_bit_modify(int address, int mask_byte, int data);
void can_controller_request_to_send(int rts_transmit_buffer);
int can_controller_read_status();

#endif