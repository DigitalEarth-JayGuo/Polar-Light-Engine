################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/SysSTL/PLEngineSysSTLHashMap.cpp \
../source/SysSTL/PLEngineSysSTLPriorityQueue.cpp 

OBJS += \
./source/SysSTL/PLEngineSysSTLHashMap.o \
./source/SysSTL/PLEngineSysSTLPriorityQueue.o 

CPP_DEPS += \
./source/SysSTL/PLEngineSysSTLHashMap.d \
./source/SysSTL/PLEngineSysSTLPriorityQueue.d 


# Each subdirectory must supply rules for building sources it contributes
source/SysSTL/%.o: ../source/SysSTL/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


