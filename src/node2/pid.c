#include "pid.h"
#include "stdint.h"

#include "uart.h"
#include "motor_driver.h"
#include "encoder_driver.h"

#define MAX_SUM_ERROR 15

volatile int sum_error = 0;
volatile int last_current_position = 0;

// void pid_init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid) {
// 	// Start values for PID controller
// 	pid->sum_error         = 0;
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
    //printf("Errors = %d\n\r", errors);

    // **** Calculate P term **** //
    p_term = p * errors;
    //printf("P-term = %d\n\r", p_term);

    // **** Calculate I term **** //
    temp = sum_error + errors;
    sum_error = temp;
    i_term = i * sum_error;
    if (sum_error > MAX_SUM_ERROR){
		sum_error = MAX_SUM_ERROR;
    } else if (sum_error < -MAX_SUM_ERROR){
		sum_error = -MAX_SUM_ERROR;
	}
    
    // printf("sum_error = %d\n\r", sum_error);
    // printf("Temp = %d\n\r", temp);
    // printf("I-term = %d\n\r", i_term);

    // **** Calculate D term **** //
    //d_term = d * (last_current_position - current_position);
    // printf("D-term = %d\n\r", d_term);

    last_current_position = current_position;
    // printf("current_position = %d\n\r", current_position);

    ret = floor((p_term + i_term + d_term)/90); // / SCALING_FACTOR;

    if (ret < 0) {
        motor_set_direction(MOTOR_LEFT);
    } else {
        motor_set_direction(MOTOR_RIGHT);
    }

    int16_t ret_abs = abs(ret);

    ret_abs = ret_abs + 40;

    // LIMITER
    if (ret_abs > 100) {
      ret_abs = 100;
    } 
    // else if (ret < -100) {
    // //   ret = -100;
    // // }

    // if (ret > 10 && ret < 50){
    //   ret = 50;
    // }
    // if (ret < -10 && ret > -50){
    //   ret = -50;
    // }


    //printf("Ret = %d\n\r", ret);
    //printf("Ret_abs = %d\n\r", ret_abs);

    return ((int16_t)ret_abs);
}


// void pid_reset_integrator(pidData_t *pid_st) {
// 	pid_st->sum_error = 0;
// }




// **** ORIGINAL CODE **** //


// #include "pid.h"
// #include "stdint.h"

// #include "uart.h"

// void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid) {
// 	// Start values for PID controller
// 	pid->sum_error         = 0;
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
// 	temp = pid_st->sum_error + errors;
// 	pid_st->sum_error = temp;
// 	i_term           = pid_st->I_Factor * pid_st->sum_error;
// 	// if (temp > pid_st->maxSumError) {
// 	// 	i_term           = MAX_I_TERM;
// 	// 	pid_st->sum_error = pid_st->maxSumError;
// 	// } else if (temp < -pid_st->maxSumError) {
// 	// 	i_term           = -MAX_I_TERM;
// 	// 	pid_st->sum_error = -pid_st->maxSumError;
// 	// } else {
// 	// 	pid_st->sum_error = temp;
// 	// 	i_term           = pid_st->I_Factor * pid_st->sum_error;
// 	// }

// 	printf("sum_error = %d\n\r", pid_st->sum_error);
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
// 	pid_st->sum_error = 0;
// }
