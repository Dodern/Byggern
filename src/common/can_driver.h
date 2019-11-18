#ifndef __CAN_DRIVER_H
#define __CAN_DRIVER_H

#define START_GAME 0
#define PLAY_GAME 1
#define STOP_GAME 2
#define TEST_SRAM 10
#define SRAM_TESTED 5

void can_send_message(int id, int length, uint8_t* arr, int transmit_line);
void can_send_array(int id, uint8_t* arr, int transmit_line);
struct can_message can_read_message(int read_line);


#endif