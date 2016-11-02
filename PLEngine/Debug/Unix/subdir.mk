################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Unix/PLEngineSysAPI_Unix.cpp \
../Unix/PLEngineSysIOAPI_Unix.cpp \
../Unix/PLEngineSysNetworkAPI_Unix.cpp \
../Unix/PLEngineSysProcessAPI_Unix.cpp \
../Unix/PLEngineSysSynchron_Unix.cpp 

OBJS += \
./Unix/PLEngineSysAPI_Unix.o \
./Unix/PLEngineSysIOAPI_Unix.o \
./Unix/PLEngineSysNetworkAPI_Unix.o \
./Unix/PLEngineSysProcessAPI_Unix.o \
./Unix/PLEngineSysSynchron_Unix.o 

CPP_DEPS += \
./Unix/PLEngineSysAPI_Unix.d \
./Unix/PLEngineSysIOAPI_Unix.d \
./Unix/PLEngineSysNetworkAPI_Unix.d \
./Unix/PLEngineSysProcessAPI_Unix.d \
./Unix/PLEngineSysSynchron_Unix.d 


# Each subdirectory must supply rules for building sources it contributes
Unix/%.o: ../Unix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


