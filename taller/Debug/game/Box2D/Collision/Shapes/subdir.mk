################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2ChainShape.cpp \
/home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2CircleShape.cpp \
/home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2EdgeShape.cpp \
/home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2PolygonShape.cpp 

OBJS += \
./game/Box2D/Collision/Shapes/b2ChainShape.o \
./game/Box2D/Collision/Shapes/b2CircleShape.o \
./game/Box2D/Collision/Shapes/b2EdgeShape.o \
./game/Box2D/Collision/Shapes/b2PolygonShape.o 

CPP_DEPS += \
./game/Box2D/Collision/Shapes/b2ChainShape.d \
./game/Box2D/Collision/Shapes/b2CircleShape.d \
./game/Box2D/Collision/Shapes/b2EdgeShape.d \
./game/Box2D/Collision/Shapes/b2PolygonShape.d 


# Each subdirectory must supply rules for building sources it contributes
game/Box2D/Collision/Shapes/b2ChainShape.o: /home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2ChainShape.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/demian/git/taller/taller/game" -I/home/demian/Documentos/Include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

game/Box2D/Collision/Shapes/b2CircleShape.o: /home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2CircleShape.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/demian/git/taller/taller/game" -I/home/demian/Documentos/Include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

game/Box2D/Collision/Shapes/b2EdgeShape.o: /home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2EdgeShape.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/demian/git/taller/taller/game" -I/home/demian/Documentos/Include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

game/Box2D/Collision/Shapes/b2PolygonShape.o: /home/demian/git/taller/taller/game/Box2D/Collision/Shapes/b2PolygonShape.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"/home/demian/git/taller/taller/game" -I/home/demian/Documentos/Include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


