# ADC operation

The internal voltage reference the ADC uses can be decoupled by an external capacitor into AREF on the controller. The reference voltage can be choosen to either be AVCC, internal 1.1V refernces, internal 2.56V reference or external AREF pin.

The input cheannel is selected by writing the MUX bits in ADMUX and ADCSRB.
A single ended ADC input is just a signal in reference to GND signal. 

Single ended conversion: $ADC = (V_{in}*1024)/V_{ref}$

## On our controller

We will be using a Single Ended ADC Input.
We will also be using Free Running mode so the ADC continually reads the analog signal and performs conversion. 

A0 - This is the output of the opamp that returns the photo diode values.