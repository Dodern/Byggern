
#include "mcp2515.h"
#include "spi_driver.h"

void can_controller_init(){
    //Initializing the spi on atmega162
    spi_master_init();
    //Reseting the CAN controller duringstartup
    spi_master_transmit(MCP_RESET);
}
