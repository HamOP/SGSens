################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/stefan/Documents/Arduino/libraries/JetiExSensor/src/JetiExProtocol.cpp \
/Users/stefan/Documents/Arduino/libraries/JetiExSensor/src/JetiExSerial.cpp 

LINK_OBJ += \
./libraries/JetiExSensor/src/JetiExProtocol.cpp.o \
./libraries/JetiExSensor/src/JetiExSerial.cpp.o 

CPP_DEPS += \
./libraries/JetiExSensor/src/JetiExProtocol.cpp.d \
./libraries/JetiExSensor/src/JetiExSerial.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/JetiExSensor/src/JetiExProtocol.cpp.o: /Users/stefan/Documents/Arduino/libraries/JetiExSensor/src/JetiExProtocol.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -I"/Users/stefan/Documents/Arduino/libraries/JetiExSensor" -I"/Users/stefan/Documents/Arduino/libraries/JetiExSensor/src" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src" -I"/Users/stefan/Documents/Arduino/libraries/SFE_BMP180" -I"/Users/stefan/Documents/Arduino/libraries/SFE_BMP180/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

libraries/JetiExSensor/src/JetiExSerial.cpp.o: /Users/stefan/Documents/Arduino/libraries/JetiExSensor/src/JetiExSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -I"/Users/stefan/Documents/Arduino/libraries/JetiExSensor" -I"/Users/stefan/Documents/Arduino/libraries/JetiExSensor/src" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire" -I"/Applications/sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src" -I"/Users/stefan/Documents/Arduino/libraries/SFE_BMP180" -I"/Users/stefan/Documents/Arduino/libraries/SFE_BMP180/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


