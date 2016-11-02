################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Unix/PLEngineSysAPI_Unix.cpp \
../source/Unix/PLEngineSysIOAPI_Unix.cpp \
../source/Unix/PLEngineSysNetworkAPI_Unix.cpp \
../source/Unix/PLEngineSysProcessAPI_Unix.cpp \
../source/Unix/PLEngineSysSynchron_Unix.cpp 

OBJS += \
./source/Unix/PLEngineSysAPI_Unix.o \
./source/Unix/PLEngineSysIOAPI_Unix.o \
./source/Unix/PLEngineSysNetworkAPI_Unix.o \
./source/Unix/PLEngineSysProcessAPI_Unix.o \
./source/Unix/PLEngineSysSynchron_Unix.o 

CPP_DEPS += \
./source/Unix/PLEngineSysAPI_Unix.d \
./source/Unix/PLEngineSysIOAPI_Unix.d \
./source/Unix/PLEngineSysNetworkAPI_Unix.d \
./source/Unix/PLEngineSysProcessAPI_Unix.d \
./source/Unix/PLEngineSysSynchron_Unix.d 


# Each subdirectory must supply rules for building sources it contributes
source/Unix/%.o: ../source/Unix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


