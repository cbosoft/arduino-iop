FQBN 			= archlinux-arduino:avr:uno
HARDWARE	=	/usr/share/arduino/hardware
TOOLS			=	/usr/bin
BUILD			= build
TARGET		= blink

# upload options
CONFIG		= /etc/avrdude.conf
PARTNO		= atmega328p
PROG			= arduino
PORT			= /dev/ttyACM0
BAUD			= 115200


build: $(TARGET)/$(TARGET).ino
	mkdir -p $(BUILD)
	arduino-builder -fqbn $(FQBN) -hardware $(HARDWARE) -tools $(TOOLS) -verbose -build-path $(BUILD) $(TARGET)

upload: build
	$(TOOLS)/avrdude -c$(PROG) -C$(CONFIG) -v -p$(PARTNO) -P$(PORT) -b$(BAUD) -D -Uflash:w:$(BUILD)/$(TARGET).ino.hex:i


clean:
	rm -rf build
