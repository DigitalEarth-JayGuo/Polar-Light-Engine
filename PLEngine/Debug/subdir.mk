################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MainLib.cpp \
../PLEngineHeavyH.cpp \
../PLEngineLogSystemAPI.cpp \
../PLEngineMath.cpp \
../PLEngineMemoryPool.cpp \
../PLEngineRenderAPI.cpp \
../PLEngineResourceLoadAPI.cpp \
../PLEngineResourceManagerAPI.cpp \
../PLEngineScriptAPI.cpp \
../PLEngineSysAPI.cpp \
../PLEngineSysEnvIFM.cpp \
../PLEngineSysIO.cpp \
../PLEngineSysNetworkAPI.cpp \
../PLEngineSysProcess.cpp \
../PLEngineSysSTLArithmeticAPI.cpp \
../PLEngineSysSchedulerAPI.cpp \
../PLEngineSysSynchron.cpp \
../PLEngineSysTextChar.cpp \
../PLEngineSysThreadPool.cpp \
../PLEngineSysWindowsAPI.cpp 

OBJS += \
./MainLib.o \
./PLEngineHeavyH.o \
./PLEngineLogSystemAPI.o \
./PLEngineMath.o \
./PLEngineMemoryPool.o \
./PLEngineRenderAPI.o \
./PLEngineResourceLoadAPI.o \
./PLEngineResourceManagerAPI.o \
./PLEngineScriptAPI.o \
./PLEngineSysAPI.o \
./PLEngineSysEnvIFM.o \
./PLEngineSysIO.o \
./PLEngineSysNetworkAPI.o \
./PLEngineSysProcess.o \
./PLEngineSysSTLArithmeticAPI.o \
./PLEngineSysSchedulerAPI.o \
./PLEngineSysSynchron.o \
./PLEngineSysTextChar.o \
./PLEngineSysThreadPool.o \
./PLEngineSysWindowsAPI.o 

CPP_DEPS += \
./MainLib.d \
./PLEngineHeavyH.d \
./PLEngineLogSystemAPI.d \
./PLEngineMath.d \
./PLEngineMemoryPool.d \
./PLEngineRenderAPI.d \
./PLEngineResourceLoadAPI.d \
./PLEngineResourceManagerAPI.d \
./PLEngineScriptAPI.d \
./PLEngineSysAPI.d \
./PLEngineSysEnvIFM.d \
./PLEngineSysIO.d \
./PLEngineSysNetworkAPI.d \
./PLEngineSysProcess.d \
./PLEngineSysSTLArithmeticAPI.d \
./PLEngineSysSchedulerAPI.d \
./PLEngineSysSynchron.d \
./PLEngineSysTextChar.d \
./PLEngineSysThreadPool.d \
./PLEngineSysWindowsAPI.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


