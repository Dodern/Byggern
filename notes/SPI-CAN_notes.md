# Definitions

## SPI

- SPCR: SPI control register
    - SPIE: SPI interrupt enable bit
    - SPE: SPI enable bit
    - DORD: Data order bit
        - high -> LSB transmitted first
        - low -> MSB transmitted first
    - MSTR: 
        - high -> Sets Master SPI mode
        - low -> Sets Slave SPI mode
    - CPOL: Clock polarity bit
        - high -> SCK high when idle
        - low -> SCK low when idle
    - CPHA: Clock phase bit
        - high -> Sample on trailing edge
        - low -> Sample on leading edge
    - SPR0/SPR1: SPI clock rate selection (see table)
        - Ours is set to f_osc/16
- SPSR: SPI status register
    - SPIF: SPI end of transmission flag, set when a transmission is complete
    - WCOL: Write collison flag, set when SPDR is read during a data transfer
    - SPI2X: Double SPI speed bit, SCK frequency doubled while in master mode if set
- SPDR: SPI data register

# Information

When in master mode:

Set SS low to start transmission
Set SPDR to the byte you want to transmit, this starts the clock
Byte will be transmitted one bit at a time each clock pulse
After the byte has been transmitted SPIF flag will be set and the clock will stop
If you want to transmit more bytes set SPDR to the next byte
Continue until finished with packet
Set SS high to end transmission


When in slave mode:

MISO is tri-stated as long as SS is high
    Data will not be shifted in by clock signals, but can change in the SPDR register
Set SS to low to recieve data
When one byte has been recieved SPIF will be set
Data in SPDR will be sent to the master when the master sends to the slave
    This can be done before the new data is read

When receiving data, a received character must beread from the SPI Data Register before the next character has been completely shifted in. Oth-erwise, the first byte is lost.

