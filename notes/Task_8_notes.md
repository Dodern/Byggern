Start condition:
	- SDA from high to low while SCL high

Slave address MAX520:
	- 0101000

Command byte:
	- R2, R1, R0 - Set to low
	- PD
		○ High - Power off
		○ Low - Power on 
	- RST 
		○ High - Reset inputs
		○ Low - Don't
    - ACK - Will be pulled low by MAX520 every 9th clock pulse

Output byte:
    - Between 0 - 255 in 8-bit format
        - 00000000 - 11111111

