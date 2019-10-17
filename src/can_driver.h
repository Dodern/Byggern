#ifndef __CAN_DRIVER_H
#define __CAN_DRIVER_H

void can_send_message(int id, int length, int* arr, int transmit_line);
struct can_message can_read_message(int read_line);


#endif