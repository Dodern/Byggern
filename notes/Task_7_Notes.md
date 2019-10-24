15:31

Create a driver for the timer/counter module which allows you to use the pwm functionality (fast-pwm).
	- On Node 2 with Arduino
	- Search datasheet of ATMega2560 for "fast pwm" to set up PWM
	If you still are having a hard time configuring PWMtake a look at Figure 17-7in theATmega2560datasheet, it explains how the different counter registers interact with eachother. Table 17-2show some of the same info for all the different modes, you probably want to usemode 14.
	
	

Implement interrupt

Create a pwm and/or servo driver which will use your controller output as an input and calculate the correct duty cycle/on time which you will provide to your time/counter driver. Also implement safety features which will never let the pwm go out of valid range for the servo.

Use an oscilloscope to verify that your driver in fact never go outside valid range for the servo (0.9-2.1ms)

Connect the servo on the game board to one of the PWM outputs of the Arduino.

Use the joystick position sent from Node 1 to control the servo position.

“Goals” are registered by blocking an IR beam. Install the IR-LED and IR-photodiode in the two holes located at the sidewalls of the game board
	- Some digital cameras, such as the one in your cell phone, can detect IR light. You can use this to check if the IR-LED is active

Connect the IR diodes in a way that makes it possible to detect when the IR beam is blocked. An example is given in Figure 17, and you might also consider implementing an analog filter.
	- If necessary, a simple RC filter can be used for low-pass filtering the IR-sensor/photodiode signal.

As the IR signal is noisy and unstable you need to use the internal ADC of the Arduino to read the signal and filter out valid signal states. The motor will take up some pins of PORTF, but you should have some vacant pins for ADC usage.

Create a driver that will read the IR signal. You may want to implement a digital filter to reduce noise.
	- Read values from the IR sensor and print them to the terminal to find the appropriate thresholds settings.

Create a function that is able to count the score. This will later be used for the game application
	- Consider implementing delays for score detection that will eliminate spurious goals due to ball bouncing etc.


Things to do:
	- Read up on timers and how to use them for PWM
	- Create driver to implement PWM (Timer driver)
	- Read up on interrupts and implement the timer interrupt
	- Create PWM driver that calculates duty cycle for motor driver
		○ Implement safety features to avoid going out of range!
	- Connect the servo 
