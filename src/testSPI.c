#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "uart_node2.h" //#include "uart.h"
//#include "xmem.h"
//#include "adc_driver.h"
//#include "oled_driver.h"
#include "spi_driver_node2.h" //#include "spi_driver.h"
#include "bit_macros.h"

#define FOSC 16000000 //4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    //xmem_init();
    //adc_init();
    //oled_init();

    unsigned char letter = 'U';
	_delay_ms(300);
	printf("chararcter: %c\n\r", letter);

    spi_master_init();
    //// Setting the direction of test pin
    // set_bit(DDRB, DDB3);

    // to test the spi_receive I set the function to continually 
    // read the data, and while this occured I simply pulled MISO         
    // high and low and the print function registered different inputs
    while (1) {
        // clear_bit(PORTB, CAN_SS);
        // spi_transmit('c');
        // set_bit(PORTB, CAN_SS);
        
        clear_bit(PORTB, CAN_SS);
        int read = spi_receive();
        set_bit(PORTB, CAN_SS);
        printf("SPI recieve data: %d\n\r", read);
        _delay_ms(3000);
     

    }
    return 0;
}