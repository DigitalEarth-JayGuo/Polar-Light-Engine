################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineFontAPI.cpp \
../PLEngineFontPackage.cpp 

OBJS += \
./EngineFontAPI.o \
./PLEngineFontPackage.o 

CPP_DEPS += \
./EngineFontAPI.d \
./PLEngineFontPackage.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetPrjExport_SysFont -DIDESetGCCCompiler -I/home/Dev/3DEngine/PLEngine -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


