################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Windows/PLEngineSysAPI_Windows.cpp \
../source/Windows/PLEngineSysIOAPI_Windows.cpp \
../source/Windows/PLEngineSysNetworkAPI_Windows.cpp \
../source/Windows/PLEngineSysProcessAPI_Windows.cpp \
../source/Windows/PLEngineSysSynchron_Windows.cpp 

OBJS += \
./source/Windows/PLEngineSysAPI_Windows.o \
./source/Windows/PLEngineSysIOAPI_Windows.o \
./source/Windows/PLEngineSysNetworkAPI_Windows.o \
./source/Windows/PLEngineSysProcessAPI_Windows.o \
./source/Windows/PLEngineSysSynchron_Windows.o 

CPP_DEPS += \
./source/Windows/PLEngineSysAPI_Windows.d \
./source/Windows/PLEngineSysIOAPI_Windows.d \
./source/Windows/PLEngineSysNetworkAPI_Windows.d \
./source/Windows/PLEngineSysProcessAPI_Windows.d \
./source/Windows/PLEngineSysSynchron_Windows.d 


# Each subdirectory must supply rules for building sources it contributes
source/Windows/%.o: ../source/Windows/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


