#ifndef __CAN_DRIVER_H
#define __CAN_DRIVER_H

void can_send_message(int id, int length, uint8_t* arr, int transmit_line);
void can_send_array(int id, uint8_t* arr, int transmit_line);
struct can_message can_read_message(int read_line);


#endif