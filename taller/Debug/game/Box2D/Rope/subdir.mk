################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/demian/git/taller/taller/game/Box2D/Rope/b2Rope.cpp 

OBJS += \
./game/Box2D/Rope/b2Rope.o 

CPP_DEPS += \
./game/Box2D/Rope/b2Rope.d 


# Each subdirectory must supply rules for building sources it contributes
game/Box2D/Rope/b2Rope.o: /home/demian/git/taller/taller/game/Box2D/Rope/b2Rope.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/demian/git/taller/taller/game" -I/home/demian/Documentos/Include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


