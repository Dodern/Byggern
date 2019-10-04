# Definitions

## SPI

- SPCR: SPI control register
    - SPE: SPI enable bit
    - MSTR: 
        - high -> Sets Master SPI mode
        - low -> Sets Slave SPI mode
    - SPR0/SPR1: SPI clock rate selection (see table)
        - Ours is set to f_osc/16
- SPSR: SPI status register
    - SPIF: SPI interrupt flag, set when a transmission is complete

