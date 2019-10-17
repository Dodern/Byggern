# Regular Lecture on CAN

- Two frame formats:
  - Standard - 11 bits 
  - Extended - 29 bits 
- Four frames:
  - Data frame
  - Remote frame
  - Error frame
  - Overload frame

### Can bus access

- Multi-master: Any node may initiate a transfer when the network is idle.
  - The bit values on the bus may take one or two signal states. Recessive or Dominant
  - Recessive (logical 1) and a dominant is logical low (0)
- Messages IDs defines a static priority:
  - IDs with the most significant dominant bits get the highest priority (That is the ID with the lowest numerical number)
  - Arbitration by message priority
    - Non destructive
    - CSMA/AMP
      - Carrier Sense Multiple Access / Arbitration by Multiple Priority
  - **Dont push messages repeatedly on the CAN bus**   
  - Does not respond well to spamming
  
  
### Error Detection

- Bit monitoring
  - Error messages have identifiers have 6 consequtive bits after eachother. If a node receives this it will discard or ignore the message
- Bit stuffing
  - Inserts or injects in the bit stream, complementary bits (ones in different states) in rows of more than five equal bits (happens automatically)
  - Avoids DC component on bus
  - Burst Errors are detected
  - Gives synch. edges
- Frame check (Form Error)
- Ack.Check
- CRC

- All nodes on the network monitors the bus for all errors simultaneously and responds immediately with an error frame in case of error detection.
- P(undetected error) = error rate * 4.7e(-11)

### Fault Confinement

- CAN protocol incorporates mechanisms to suppress and exclued faulty nodes.
- All nodes defined to be in one of 3 error states. 
  - Error Active 
  - Error Passive
  - Bus Off
- The CAN node state depends on the value of two internally managed counters:
  - TEC- Transmit Error Count
  - REC- Receive Error Count
