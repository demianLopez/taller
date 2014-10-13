################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/engine/Animation.cpp \
../game/engine/AnimationFrame.cpp \
../game/engine/Game.cpp \
../game/engine/GameElements.cpp \
../game/engine/Graphics.cpp \
../game/engine/Image.cpp \
../game/engine/Particle.cpp \
../game/engine/ParticleEmiter.cpp \
../game/engine/SpriteSheet.cpp \
../game/engine/SubImage.cpp 

OBJS += \
./game/engine/Animation.o \
./game/engine/AnimationFrame.o \
./game/engine/Game.o \
./game/engine/GameElements.o \
./game/engine/Graphics.o \
./game/engine/Image.o \
./game/engine/Particle.o \
./game/engine/ParticleEmiter.o \
./game/engine/SpriteSheet.o \
./game/engine/SubImage.o 

CPP_DEPS += \
./game/engine/Animation.d \
./game/engine/AnimationFrame.d \
./game/engine/Game.d \
./game/engine/GameElements.d \
./game/engine/Graphics.d \
./game/engine/Image.d \
./game/engine/Particle.d \
./game/engine/ParticleEmiter.d \
./game/engine/SpriteSheet.d \
./game/engine/SubImage.d 


# Each subdirectory must supply rules for building sources it contributes
game/engine/%.o: ../game/engine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -I/usr/include/Box2D -I"/home/maxi/git/taller/taller/game" -I"/home/maxi/git/taller/taller/common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


