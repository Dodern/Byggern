// #include "pid.h"
// #include "stdint.h"

// #include "uart.h"

// void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid) {
// 	// Start values for PID controller
// 	pid->sumError         = 0;
// 	pid->lastProcessValue = 0;
// 	// Tuning constants for PID loop
// 	pid->P_Factor = p_factor;
// 	pid->I_Factor = i_factor;
// 	pid->D_Factor = d_factor;
// 	// Limits to avoid overflow
// 	pid->maxError    = MAX_INT / (pid->P_Factor + 1);
// 	pid->maxSumError = MAX_I_TERM / (pid->I_Factor + 1);
// }

// int16_t pid_Controller(int16_t setPoint, int16_t processValue, struct PID_DATA *pid_st) {
// 	int16_t errors, p_term, d_term;
// 	int32_t i_term, ret, temp;

// 	errors = setPoint - processValue;

// 	printf("Errors = %d\n\r", errors);

// 	// Calculate Pterm and limit error overflow

// 	printf("P-factor = %d\n\r", pid_st->P_Factor);

// 	p_term = pid_st->P_Factor * errors;
// 	// if (errors > pid_st->maxError) {
// 	// 	p_term = MAX_INT;
// 	// } else if (errors < -pid_st->maxError) {
// 	// 	p_term = -MAX_INT;
// 	// } else {
// 	// 	p_term = pid_st->P_Factor * errors;
// 	// }

// 	printf("P-term = %d\n\r", p_term);

// 	// Calculate Iterm and limit integral runaway
// 	temp = pid_st->sumError + errors;
// 	pid_st->sumError = temp;
// 	i_term           = pid_st->I_Factor * pid_st->sumError;
// 	// if (temp > pid_st->maxSumError) {
// 	// 	i_term           = MAX_I_TERM;
// 	// 	pid_st->sumError = pid_st->maxSumError;
// 	// } else if (temp < -pid_st->maxSumError) {
// 	// 	i_term           = -MAX_I_TERM;
// 	// 	pid_st->sumError = -pid_st->maxSumError;
// 	// } else {
// 	// 	pid_st->sumError = temp;
// 	// 	i_term           = pid_st->I_Factor * pid_st->sumError;
// 	// }

// 	printf("sumError = %d\n\r", pid_st->sumError);
// 	printf("I-term = %d\n\r", i_term);

// 	// Calculate Dterm
// 	d_term = pid_st->D_Factor * (pid_st->lastProcessValue - processValue);

// 	printf("D-term = %d\n\r", d_term);

// 	pid_st->lastProcessValue = processValue;

// 	printf("processvalue = %d\n\r", processValue);

// 	ret = (p_term + i_term + d_term) / SCALING_FACTOR;
// 	// if (ret > MAX_UINT) {
// 	// 	ret = MAX_UINT;
// 	// } else if (ret < -MAX_UINT) {
// 	// 	ret = -MAX_UINT;
// 	// }

// 	printf("Ret = %d\n\r", ret);

// 	return ((int16_t)ret);
// }


// void pid_Reset_Integrator(pidData_t *pid_st) {
// 	pid_st->sumError = 0;
// }

#include "pid.h"
#include "stdint.h"

#include "uart.h"

volatile int sumError = 0;
volatile int last_current_position = 0;

// void pid_init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid) {
// 	// Start values for PID controller
// 	pid->sumError         = 0;
// 	pid->last_current_position = 0;
// 	// Tuning constants for PID loop
// 	pid->P_Factor = p_factor;
// 	pid->I_Factor = i_factor;
// 	pid->D_Factor = d_factor;
// 	// Limits to avoid overflow
// 	pid->maxError    = MAX_INT / (pid->P_Factor + 1);
// 	pid->maxSumError = MAX_I_TERM / (pid->I_Factor + 1);
// }

int16_t pid_controller(int p, int i, int d, int16_t set_point, int16_t current_position) {
	int16_t errors, p_term;
	int32_t ret, temp;
    int32_t i_term = 0;
    int32_t d_term = 0;

	errors = set_point - current_position;

	// printf("Errors = %d\n\r", errors);

	// Calculate Pterm
	p_term = p * errors;

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

	ret = floor((p_term + i_term + d_term)/80); // / SCALING_FACTOR;
	
	// LIMITER
	if (ret > 100) {
		ret = 100;
	} else if (ret < -100) {
		ret = -100;
	}

	if (ret > 10 && ret < 50){
		ret = 50;
	}
	if (ret < -10 && ret > -50){
		ret = -50;
	}
	

	printf("Ret = %d\n\r", ret);

	return ((int16_t)ret);
}


void pid_Reset_Integrator(pidData_t *pid_st) {
	pid_st->sumError = 0;
}