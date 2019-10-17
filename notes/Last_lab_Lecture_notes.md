# Last Lab lecture notes

## CAN

- Good idea to have a delay between sending messages
- Not all extras will give points
- Mention them and add explain the design consideration
- Don't focus on extras until you have finished the main tasks

## AVR Timer

- Timer is exam relevant and should consider doing something with the built in timer.
- Can use the external Tn pins for timer dependent extras
- Have to use prescaler for 20 ms delay WHEN USING THE SERVO (see other slides)
- You can define the max and minimum of the timer yourself. When the max is exceeded it will overflow to minimum
- Timer can be used to generate PWM on physical output pins
- Remember that a timer should be used for a single purpose
- The timer needs to be used for a can controller and for the PID control.

### For interrupts

- Have to initialize global interrupts
- Have to init IO interupts
- Have to write the ISR

### PWM

- Have to use an RC low-pass filter before putting the input into the dc motor.
- Check the PWM pulse on the scope before connecting to the servo motor.

### Laser

- We will probably be using the opamp for the light diode.
- Can use the internal ADC of the for ATmega162 to interpret the signal from the opamp and the laser and diode
- Use digital filtering. Read the ADC value 4 or 5 times and take the average to make sure that you are getting the desired value and not just noise.

## Ex 8 

- Sends address, then command, then data.
- Download the I2C drivers from blackboard!

### Encoder

- Have to take two measurements, divide the difference by time
- Have to have either PI or PD or PID!! They want us to use a regulator with a timing part.

## Extras

- Priority is to finish the project, and then try to implement some extras
- Expect smart extras and 
- Online tuning mechanism in controller is a good extra
- Does not have to be an added on extra
- Should be extras within embedded domain AND/OR controller domain
- Bluetooth is another extra that is good
- Can use the USB card as there are a bunch of extras.

- Can email him about CAN help either this week or next week

