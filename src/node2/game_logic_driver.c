#include <util/delay.h>
#include <stdint.h>

#include "uart.h"
#include "game_logic_driver.h"
#include "timer_driver.h"
#include "bit_macros.h"

static uint8_t game_score;

void game_logic_update_score(){
    printf("PE3 = %d\n\r", read_bit(PORTE, PE3));
    if (!(read_bit(PORTE, PE3))){
        printf("Jeg oppdaterer Game Score\n\r");
        timer3_reset();
        game_score++;
    }
    printf("Game score = %d\n\r", game_score);
}

int game_logic_get_score(){
    return game_score;
}