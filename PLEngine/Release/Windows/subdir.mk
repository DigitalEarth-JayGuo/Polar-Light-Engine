################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Windows/PLEngineSysAPI_Windows.cpp \
../Windows/PLEngineSysIOAPI_Windows.cpp \
../Windows/PLEngineSysNetworkAPI_Windows.cpp \
../Windows/PLEngineSysProcessAPI_Windows.cpp \
../Windows/PLEngineSysSynchron_Windows.cpp 

OBJS += \
./Windows/PLEngineSysAPI_Windows.o \
./Windows/PLEngineSysIOAPI_Windows.o \
./Windows/PLEngineSysNetworkAPI_Windows.o \
./Windows/PLEngineSysProcessAPI_Windows.o \
./Windows/PLEngineSysSynchron_Windows.o 

CPP_DEPS += \
./Windows/PLEngineSysAPI_Windows.d \
./Windows/PLEngineSysIOAPI_Windows.d \
./Windows/PLEngineSysNetworkAPI_Windows.d \
./Windows/PLEngineSysProcessAPI_Windows.d \
./Windows/PLEngineSysSynchron_Windows.d 


# Each subdirectory must supply rules for building sources it contributes
Windows/%.o: ../Windows/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


