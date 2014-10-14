################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/polygons/Circle.cpp \
../game/polygons/Paralelogram.cpp \
../game/polygons/Polygon.cpp \
../game/polygons/PolygonFactory.cpp \
../game/polygons/Rectangle.cpp \
../game/polygons/RegularPolygon.cpp \
../game/polygons/Trapezoid.cpp 

OBJS += \
./game/polygons/Circle.o \
./game/polygons/Paralelogram.o \
./game/polygons/Polygon.o \
./game/polygons/PolygonFactory.o \
./game/polygons/Rectangle.o \
./game/polygons/RegularPolygon.o \
./game/polygons/Trapezoid.o 

CPP_DEPS += \
./game/polygons/Circle.d \
./game/polygons/Paralelogram.d \
./game/polygons/Polygon.d \
./game/polygons/PolygonFactory.d \
./game/polygons/Rectangle.d \
./game/polygons/RegularPolygon.d \
./game/polygons/Trapezoid.d 


# Each subdirectory must supply rules for building sources it contributes
game/polygons/%.o: ../game/polygons/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -I/usr/include/Box2D -I"./game" -I"./common" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


