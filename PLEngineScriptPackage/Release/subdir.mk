################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineScriptAPI.cpp \
../EngineScriptDataDispose.cpp \
../EngineScriptRegProxy_SysEnv.cpp \
../EngineScriptRegProxy_System.cpp \
../PLEngineScriptPackage.cpp 

OBJS += \
./EngineScriptAPI.o \
./EngineScriptDataDispose.o \
./EngineScriptRegProxy_SysEnv.o \
./EngineScriptRegProxy_System.o \
./PLEngineScriptPackage.o 

CPP_DEPS += \
./EngineScriptAPI.d \
./EngineScriptDataDispose.d \
./EngineScriptRegProxy_SysEnv.d \
./EngineScriptRegProxy_System.d \
./PLEngineScriptPackage.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetPrjExport_Script -DIDESetGCCCompiler -I/home/Dev/3DEngine -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


