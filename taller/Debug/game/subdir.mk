################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/BolaDeNieve.cpp \
../game/ContactListener.cpp \
../game/CosaConMovimiento.cpp \
../game/GestorEscenario.cpp \
../game/Jugador.cpp \
../game/LectorJson.cpp \
../game/LectorJsonTest.cpp \
../game/LogManager.cpp \
../game/Personaje.cpp \
../game/Resources.cpp \
../game/SnowBross.cpp \
../game/VectorXY.cpp \
../game/World.cpp \
../game/main.cpp 

OBJS += \
./game/BolaDeNieve.o \
./game/ContactListener.o \
./game/CosaConMovimiento.o \
./game/GestorEscenario.o \
./game/Jugador.o \
./game/LectorJson.o \
./game/LectorJsonTest.o \
./game/LogManager.o \
./game/Personaje.o \
./game/Resources.o \
./game/SnowBross.o \
./game/VectorXY.o \
./game/World.o \
./game/main.o 

CPP_DEPS += \
./game/BolaDeNieve.d \
./game/ContactListener.d \
./game/CosaConMovimiento.d \
./game/GestorEscenario.d \
./game/Jugador.d \
./game/LectorJson.d \
./game/LectorJsonTest.d \
./game/LogManager.d \
./game/Personaje.d \
./game/Resources.d \
./game/SnowBross.d \
./game/VectorXY.d \
./game/World.d \
./game/main.d 


# Each subdirectory must supply rules for building sources it contributes
game/%.o: ../game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -I/usr/include/Box2D -I"./game" -I"./common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


