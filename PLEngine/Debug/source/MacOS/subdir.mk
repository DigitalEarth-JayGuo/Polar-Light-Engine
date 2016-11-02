################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/MacOS/PLEngineSysAPI_MacOS.cpp \
../source/MacOS/PLEngineSysIOAPI_MacOS.cpp \
../source/MacOS/PLEngineSysNetworkAPI_MacOS.cpp \
../source/MacOS/PLEngineSysProcessAPI_MacOS.cpp \
../source/MacOS/PLEngineSysSynchron_MacOS.cpp 

OBJS += \
./source/MacOS/PLEngineSysAPI_MacOS.o \
./source/MacOS/PLEngineSysIOAPI_MacOS.o \
./source/MacOS/PLEngineSysNetworkAPI_MacOS.o \
./source/MacOS/PLEngineSysProcessAPI_MacOS.o \
./source/MacOS/PLEngineSysSynchron_MacOS.o 

CPP_DEPS += \
./source/MacOS/PLEngineSysAPI_MacOS.d \
./source/MacOS/PLEngineSysIOAPI_MacOS.d \
./source/MacOS/PLEngineSysNetworkAPI_MacOS.d \
./source/MacOS/PLEngineSysProcessAPI_MacOS.d \
./source/MacOS/PLEngineSysSynchron_MacOS.d 


# Each subdirectory must supply rules for building sources it contributes
source/MacOS/%.o: ../source/MacOS/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


