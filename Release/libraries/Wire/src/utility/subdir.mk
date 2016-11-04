################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src/utility/twi.c 

C_DEPS += \
./libraries/Wire/src/utility/twi.c.d 

LINK_OBJ += \
./libraries/Wire/src/utility/twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/src/utility/twi.c.o: /Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src/utility/twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src" -I"/Users/stefan/Documents/Arduino/libraries/SFE_BMP180" -I"/Users/stefan/Documents/Arduino/libraries/SFE_BMP180/src" -I"/Users/stefan/Documents/Arduino/libraries/JetiExSensor" -I"/Users/stefan/Documents/Arduino/libraries/JetiExSensor/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


