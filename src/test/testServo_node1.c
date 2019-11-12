#include <avr/interrupt.h>
#include <util/delay.h>
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

    uint8_t arr[] = {0b01010101, 0b01001111, 0b01001011, 0b0111100}; //85, 79, 75, 60
    uint8_t arr2[] = {0b01011101, 0b0100101, 0b01101011, 0b0111110}; //93, 37, 107, 62
    uint8_t arr3[] = {0,0};
    int8_t center_arr[] = {0,0};
    uint8_t right_slider_position = 0;
    int length = SIZE(arr);
    int length2 = SIZE(arr2);
    int length3 = SIZE(arr3);
    int center_arr_length = SIZE(center_arr);
    int length_right_slider_msg = 1;

    while (1) {
        // ***** For Direct Joystick Input ******* //

        adc_get_joystick_position(&arr3);
        printf("Arr 3[0] = %d, Arr 3[1] = %d\n\r", arr3[0], arr3[1]);
        can_send_message(0, length3, &arr3, 0);
        _delay_ms(1000);

        // ***** For Percentage Joystick Input ******* //

        // adc_get_joystick_percent_position(&center_arr);
        // // printf("arr3[0] = %d, arr3[1] = %d\n\r", center_arr[0], center_arr[1]);
        // can_send_message(0, center_arr_length, &center_arr, 0);
        // _delay_ms(1000);

        // ***** For Slider Input ******* //

        // right_slider_position = adc_get_right_slider_position();
        // printf("Right slider position = %d\n\r", right_slider_position);
        // can_send_message(0, length_right_slider_msg, &right_slider_position, 0);
        // _delay_ms(1000);
    }
    return 0;
}