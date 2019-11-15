#ifndef SOLENOID_DRIVER_H
#define SOLENOID_DRIVER_H

#define SOLENOID_TRIG_PIN PH5

void solenoid_init();
void solenoid_punch();
void solenoid_timer_reset();
void solenoid_timer_read();

#endif
