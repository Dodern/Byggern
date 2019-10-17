# CAN bus lab lecture

## Ex 5 notes

Same componentes on both the nodes
Nodes are completey communicating via IDs and not memory
All messages are received by a node, but the nodes can chose to act based on the ID of the message
In CAN each node is a master

### For slide CAN Physical Layer

120 ohms on both nodes!
Uses differential signaling to reduce noise produced that would be present from switching between 0V to 5V

### SPI

Can use GPIO pins as extra Slave Selects (SS) if needing extra slaves
**Should use mode 0 of SPI because that is the only one that CAN supports**

### Using the MCP2515

Really look at the
You are not supposed to use CS everytime you send something
If you look at the two diagrams on this slide and figure out the what registries you need for initialization, the setup should go well.
There are also tools that you can use for single bit manipulation

Node2 should be in Listen-only mode (in the next lab)

Send this, 0XFF as dummy bit, and not 0x00 to the CAN

You do not have two different registers for reading and writing (it happens at the same time)

## Ex 6 notes

In node 2 the hardware is set up and only need to program. Reuse the code from the first node!
The datasheet for node two tells you which pins you need to use. If you unplug the shield could get damaged.

### Transmission using MCP2515

All registers needed to communicate between the nodes is on this slide!!
Extra: You can use a filter or mask bit as an ID to filter different types of messages. Feks. this could be display could have a bit masked to it

### Tips

Hierarchi: SPI under CAN controller, under CAN Driver.
The Driver should have bigger functions such as (Send_message)
Have clear boundaries for these


