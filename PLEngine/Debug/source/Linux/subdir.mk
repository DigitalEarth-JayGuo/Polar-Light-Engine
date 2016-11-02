################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Linux/PLEngineSysAPI_Linux.cpp \
../source/Linux/PLEngineSysIOAPI_Linux.cpp \
../source/Linux/PLEngineSysNetworkAPI_Linux.cpp \
../source/Linux/PLEngineSysProcessAPI_Linux.cpp \
../source/Linux/PLEngineSysSynchron_Linux.cpp 

OBJS += \
./source/Linux/PLEngineSysAPI_Linux.o \
./source/Linux/PLEngineSysIOAPI_Linux.o \
./source/Linux/PLEngineSysNetworkAPI_Linux.o \
./source/Linux/PLEngineSysProcessAPI_Linux.o \
./source/Linux/PLEngineSysSynchron_Linux.o 

CPP_DEPS += \
./source/Linux/PLEngineSysAPI_Linux.d \
./source/Linux/PLEngineSysIOAPI_Linux.d \
./source/Linux/PLEngineSysNetworkAPI_Linux.d \
./source/Linux/PLEngineSysProcessAPI_Linux.d \
./source/Linux/PLEngineSysSynchron_Linux.d 


# Each subdirectory must supply rules for building sources it contributes
source/Linux/%.o: ../source/Linux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


