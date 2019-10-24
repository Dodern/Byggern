JMP 12 går til PB 6 som er pin 6 på Arduino porten og pin 7 på IO-kortet

if the TXD pin is low at power-up, theCANH and CANL pins will remain in high impedanceuntil TXD goes high

Transmit priority is a prioritization within the MCP2515of the pending transmittable messages. This isindependent from, and not necessarily related to, anyprioritization implicit in the message arbitration schemebuilt into the CAN protocol

Prior to sending the SOF, the priority of all buffers thatare queued for transmission is compared. The transmitbuffer with the highest priority will be sent first. Forexample, if transmit buffer 0 has a higher priority settingthan transmit buffer 1, buffer 0 will be sent first.If two buffers have the same priority setting, the bufferwith the highest buffer number will be sent first. 

Forexample, if transmit buffer 1 has the same prioritysetting as transmit buffer 0, buffer 1 will be sent first.There are four levels of transmit priority. IfTXBnCTRL.TXP<1:0> for a particular message bufferis set to 11, that buffer has the highest possible priority.If TXBnCTRL.TXP<1:0> for a particular message buf-fer is 00, that buffer has the lowest possible priority

RXB0, the higher priority buffer, has one mask and twomessage acceptance filters associated with it. Thereceived message is applied to the mask and filters forRXB0 first.RXB1 is the lower priority buffer, with one mask andfour acceptance filters associated with it

ACM0 for uart på USB
ttyS0 for uart på serial port