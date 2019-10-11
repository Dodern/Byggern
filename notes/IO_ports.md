# Notes on using the IO Ports

- DDRx
    - By default all the pins are set as input. This is done in the DDRx register for each port.
        - The DDx(pin number) corresponding to pin is the controlling bit
        - When set to 0 => input
        - When set to 1 => output

- Using as input:
    - To use the pin as input the only you need to set is the DDRx.
    - Reading the pins is done through the **PINx** register, NOT PORTx
        - The entire input register can be read by: `i = PINx`
        - Individual pins can be read by: `i = PINx & (1 << pin_numb)`

- Using as output:
    - To use the pins as output you only need to set DDRx
    - When setting output you only work with **PORTx** and don't touch PINx!!
        - Setting indivdual pins is done as normal
        - Setting entire register to 0 : `PORTx = 0`
        - Setting entire register to 1 : `PORTx = 0xFF`
            - SETTING `PORTx = 1` DOES NOT WORK!!