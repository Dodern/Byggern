## Output compare unit

Do not write the TCNTn equal to TOP in PWM modes withvariable TOP values. The compare match for the TOP will be ignored and the counter will continue to 0xFFFF.Similarly, do not write the TCNTn value equal to BOTTOM when the counter is downcounting.

The setup of the OCnx should be performed before setting the Data Direction Register for the port pin to output.The easiest way of setting the OCnx value is to use the Force Output Compare (FOCnx) strobe bits in Normalmode. The OCnx Register keeps its value even when changing between Waveform Generation modes.

## Registers for Timer

TCCR1A : Timer / Counter 1 Control Register A
    = 0b10000010 (PWM Fast mode bit 1, Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at BOTTOM (non-inverting mode))

TCCR1B : Timer / Counter 1 Control Register B
    = 0b00011010 (PWM Fast mode bits 2 and 3, Clk active with prescaling to clk/8, Input capture function disabled)

ICR1 : Input Capture Register 1
    = 0b1001110001000000 (Set TOP to 40 000)

OCR1A : Output compare register 1 A
    = 0.9 ms -> 2.1 ms

### PWM Speed
20 ms = 20 * 10^-3 = 0.02 s
f_Pwm = 1/0.02 = 50 per sekund
f_clk = 16 000 000 per sekund
N = 8
Top = ?

f_Pwm * N(1+Top) = f_clk
=>
f_pwm * N + f_pwm * N * Top = f_clk
=>
Top * f_pwm * N = f_clk - f_pwm * N
=>
Top = (f_clk - f_pwm * N) / (f_pwm * N)
=>
Top = (16 000 000 - 50*8) / 50*8
=>
Top = 40 000