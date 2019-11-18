#ifndef __CAN_CONTROLLER_DRIVER_H
#define __CAN_CONTROLLER_DRIVER_H

#include <stdint.h>

#if defined (__AVR_ATmega162__)
    #define CAN_INTERRUPT_DIR_REG DDRD
    #define CAN_INTERRUPT_FLAG_REG GIFR
    #define CAN_INTERRUPT_FLAG_PIN INTF0
    #define CAN_INTERRUPT_PORT PORTD
    #define CAN_INTERRUPT_PIN PD2
    #define CAN_INTERRUPT_VECTOR INT0_vect
    //have to enable external interrupt on node1
#elif defined (__AVR_ATmega2560__)
    #define CAN_INTERRUPT_DIR_REG DDRE
    #define CAN_INTERRUPT_FLAG_REG EIFR
    #define CAN_INTERRUPT_FLAG_PIN INTF4
    #define CAN_INTERRUPT_PORT PORTE
    #define CAN_INTERRUPT_PIN PE4
    #define CAN_INTERRUPT_VECTOR INT4_vect
    //have to enable external interrupt on node1
#endif

struct can_message{
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
};

//int* can_controller_read_struct(int address);
void can_controller_read_struct(int address, uint8_t* arr, int length);
void can_controller_write_struct(int address, struct can_message* msg);
void can_controller_write_struct2(int address, struct can_message* msg);
int can_controller_init();
void can_controller_reset(); // Send single command

int can_controller_read();
void can_controller_write(int address, int data);

void can_controller_bit_modify(int address, int mask_byte, int data);
void can_controller_request_to_send(int rts_transmit_buffer);
int can_controller_read_status();

void can_controller_clear_receive_interrupt_flag();
void can_controller_interrupt_init();

#endif