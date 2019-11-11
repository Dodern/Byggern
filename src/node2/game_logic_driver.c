#include <util/delay.h>
#include <stdint.h>

#include "uart.h"
#include "adc_driver.h"
#include "game_logic_driver.h"
#include "servo_driver.h"
#include "bit_macros.h"

static uint8_t game_score;

void game_logic_update_score(){
    adc_print();
    int adc_data = adc_read();
    if (adc_data < 100){
        printf("Jeg oppdaterer Game Score\n\r");
        game_score++;
    }
    printf("Game score = %d\n\r", game_score);
    // _delay_ms(1000);
}

int game_logic_get_score(){
    return game_score;
}