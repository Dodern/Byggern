# List all source files to be compiled; separate with space
# SOURCE_FILES := uart.c  spi_driver.c can_controller_driver.c can_driver.c testPrint.c
SOURCE_FILES := uart.c \
				spi_driver.c \
				can_controller_driver.c \
				can_driver.c \
				adc_driver.c \
				servo_driver.c \
				TWI_driver.c \
				game_logic_driver.c \
				solenoid_driver.c \
				motor_driver.c \
				pid.c \
				testMotor.c
				#testSolenoid_node2.c
				# motor_driver.c \
				# pid.c \
				testMotor.c
				# pid.c \
				testTimer_node2.c
				#testCanNodes2.c
				# timer_driver.c \
				# testDay7.c
				# testGameLogic.c
				# testADC_node2.c
				

# Set this flag to "yes" (no quotes) to use JTAG; otherwise ISP (SPI) is used
PROGRAM_WITH_JTAG := yes

# Feel free to ignore anything below this line
PROGRAMMER := atmelice_isp
ifeq ($(PROGRAM_WITH_JTAG), yes)
	PROGRAMMER := atmelice
endif

VPATH := node2:common:test
INCLUDE := node2 common test
BUILD_DIR := build_node2
# TARGET_CPU := atmega2560
TARGET_CPU := atmega2560
TARGET_DEVICE := m2560

CC := avr-gcc
CFLAGS := -O -std=c11 -mmcu=$(TARGET_CPU) $(addprefix -I ,$(INCLUDE))

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.hex: $(OBJECT_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/a.out
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/a.out $(BUILD_DIR)/main.hex

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/main.hex:i

.PHONY: fuse
fuse:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U efuse:w:0xff:m
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U hfuse:w:0x19:m
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U lfuse:w:0xfd:m

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: erase
erase:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -e
