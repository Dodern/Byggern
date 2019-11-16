#include "pid.h"
#include "stdint.h"

#include "uart.h"

volatile int sumError = 0;
volatile int last_current_position = 0;

uint8_t pid_controller(int p, int i, int d, uint16_t set_point, uint16_t current_position) {
	int16_t errors, p_term;
	int32_t ret, temp;
    int32_t i_term = 0;
    int32_t d_term = 0;

	errors = set_point - current_position;
	printf("errors = %d\n\r", errors);

	// printf("Errors = %d\n\r", errors);

	// Calculate Pterm
	p_term = p * errors;
	printf("p_term = %d\n\r", p_term);

	// printf("P-term = %d\n\r", p_term);

	// Calculate Iterm
	// temp = sumError + errors;
	// sumError = temp;
	// i_term = i * sumError;
	// printf("SumError = %d\n\r", sumError);
	// printf("Temp = %d\n\r", temp);

	// printf("sumError = %d\n\r", sumError);
	// printf("I-term = %d\n\r", i_term);

	// Calculate Dterm
	//d_term = d * (last_current_position - current_position);

	// printf("D-term = %d\n\r", d_term);

	last_current_position = current_position;

	// printf("current_position = %d\n\r", current_position);

	ret = floor((p_term + i_term + d_term)/15); // / SCALING_FACTOR;
	printf("ret = %d\n\r", ret);

	if (ret < 0) {
        set_motor_direction(0);
    } else {
        set_motor_direction(1);
    }
	
	ret = abs(ret);
	// LIMITER
	if (ret > 100) {
		ret = 100;
	}

	// if (ret > 30 && ret < 65){
	// 	ret = 65;
	// }

	printf("Ret = %d\n\r", ret);

	return ret;
}


// void pid_Reset_Integrator(pidData_t *pid_st) {
// 	pid_st->sumError = 0;
// }