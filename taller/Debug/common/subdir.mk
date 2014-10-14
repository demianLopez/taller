################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../common/Logger.cpp 

OBJS += \
./common/Logger.o 

CPP_DEPS += \
./common/Logger.d 


# Each subdirectory must supply rules for building sources it contributes
common/%.o: ../common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -I/usr/include/Box2D -I"./game" -I"./common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


