################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Linux/PLEngineSysAPI_Linux.cpp \
../Linux/PLEngineSysIOAPI_Linux.cpp \
../Linux/PLEngineSysNetworkAPI_Linux.cpp \
../Linux/PLEngineSysProcessAPI_Linux.cpp \
../Linux/PLEngineSysSynchron_Linux.cpp 

OBJS += \
./Linux/PLEngineSysAPI_Linux.o \
./Linux/PLEngineSysIOAPI_Linux.o \
./Linux/PLEngineSysNetworkAPI_Linux.o \
./Linux/PLEngineSysProcessAPI_Linux.o \
./Linux/PLEngineSysSynchron_Linux.o 

CPP_DEPS += \
./Linux/PLEngineSysAPI_Linux.d \
./Linux/PLEngineSysIOAPI_Linux.d \
./Linux/PLEngineSysNetworkAPI_Linux.d \
./Linux/PLEngineSysProcessAPI_Linux.d \
./Linux/PLEngineSysSynchron_Linux.d 


# Each subdirectory must supply rules for building sources it contributes
Linux/%.o: ../Linux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


