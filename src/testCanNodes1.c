#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"
#include "oled_driver.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    adc_init();
    oled_init();

    

    can_controller_init();

    int arr[] = {0b01010101, 0b01001111, 0b01001011, 0b0111100}; //85, 79, 75, 60
    int arr2[] = {0b01011101, 0b0100101, 0b01101011, 0b0111110}; //93, 37, 107, 62
    int8_t arr3[] = {0,0};
    int length = SIZE(arr);
    int length2 = SIZE(arr2);
    int length3 = SIZE(arr3);

    while (1) {
    adc_get_joystick_position(&arr3);
    adc_print_current_position();
    printf("\n\r");
    printf("Arr 3 = %d\n\r", arr3[0]);
    printf("\n\r");
    printf("Arr 3 = %d\n\r", arr3[1]);
    printf("\n\r");
    printf("\n\r");
    can_send_message(0, length3, &arr3, 0);
    _delay_ms(5000);
    // can_send_message(0b1, length2, &arr2, 1);
    // _delay_ms(50000);
    }
    return 0;
}