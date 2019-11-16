#ifndef PID_H
#define PID_H

#include "stdint.h"

#define SCALING_FACTOR 128

// Boolean values
#define FALSE 0
#define TRUE 1

uint8_t pid_controller(int p, int i, int d, uint16_t set_point, uint16_t current_position);
// void    pid_Reset_Integrator(pidData_t *pid_st);

#endif
