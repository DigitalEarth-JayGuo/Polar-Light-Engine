################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MacOS/PLEngineSysAPI_MacOS.cpp \
../MacOS/PLEngineSysIOAPI_MacOS.cpp \
../MacOS/PLEngineSysNetworkAPI_MacOS.cpp \
../MacOS/PLEngineSysProcessAPI_MacOS.cpp \
../MacOS/PLEngineSysSynchron_MacOS.cpp 

OBJS += \
./MacOS/PLEngineSysAPI_MacOS.o \
./MacOS/PLEngineSysIOAPI_MacOS.o \
./MacOS/PLEngineSysNetworkAPI_MacOS.o \
./MacOS/PLEngineSysProcessAPI_MacOS.o \
./MacOS/PLEngineSysSynchron_MacOS.o 

CPP_DEPS += \
./MacOS/PLEngineSysAPI_MacOS.d \
./MacOS/PLEngineSysIOAPI_MacOS.d \
./MacOS/PLEngineSysNetworkAPI_MacOS.d \
./MacOS/PLEngineSysProcessAPI_MacOS.d \
./MacOS/PLEngineSysSynchron_MacOS.d 


# Each subdirectory must supply rules for building sources it contributes
MacOS/%.o: ../MacOS/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


