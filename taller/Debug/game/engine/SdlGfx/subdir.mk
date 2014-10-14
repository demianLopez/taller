################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/engine/SdlGfx/SDL2_framerate.cpp \
../game/engine/SdlGfx/SDL2_gfxPrimitives.cpp \
../game/engine/SdlGfx/SDL2_imageFilter.cpp \
../game/engine/SdlGfx/SDL2_rotozoom.cpp 

OBJS += \
./game/engine/SdlGfx/SDL2_framerate.o \
./game/engine/SdlGfx/SDL2_gfxPrimitives.o \
./game/engine/SdlGfx/SDL2_imageFilter.o \
./game/engine/SdlGfx/SDL2_rotozoom.o 

CPP_DEPS += \
./game/engine/SdlGfx/SDL2_framerate.d \
./game/engine/SdlGfx/SDL2_gfxPrimitives.d \
./game/engine/SdlGfx/SDL2_imageFilter.d \
./game/engine/SdlGfx/SDL2_rotozoom.d 


# Each subdirectory must supply rules for building sources it contributes
game/engine/SdlGfx/%.o: ../game/engine/SdlGfx/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -I/usr/include/Box2D -I"./game" -I"./common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


