################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineResourceLoadAPI.cpp \
../PLEngineResourceLoadPackage.cpp 

OBJS += \
./EngineResourceLoadAPI.o \
./PLEngineResourceLoadPackage.o 

CPP_DEPS += \
./EngineResourceLoadAPI.d \
./PLEngineResourceLoadPackage.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetPrjExport_ResLoad -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -I/home/Dev/3DEngine -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


