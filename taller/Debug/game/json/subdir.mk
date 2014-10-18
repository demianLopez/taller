################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/json/json_reader.cpp \
../game/json/json_value.cpp \
../game/json/json_writer.cpp 

OBJS += \
./game/json/json_reader.o \
./game/json/json_value.o \
./game/json/json_writer.o 

CPP_DEPS += \
./game/json/json_reader.d \
./game/json/json_value.d \
./game/json/json_writer.d 


# Each subdirectory must supply rules for building sources it contributes
game/json/%.o: ../game/json/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -I/usr/include/Box2D -I"./game" -I"./common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


