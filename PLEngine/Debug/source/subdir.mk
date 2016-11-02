################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/MainLib.cpp \
../source/PLEngineHeavyH.cpp \
../source/PLEngineLogSystemAPI.cpp \
../source/PLEngineMath.cpp \
../source/PLEngineMemoryPool.cpp \
../source/PLEngineRenderAPI.cpp \
../source/PLEngineResourceLoadAPI.cpp \
../source/PLEngineResourceManagerAPI.cpp \
../source/PLEngineScriptAPI.cpp \
../source/PLEngineSysAPI.cpp \
../source/PLEngineSysEnvIFM.cpp \
../source/PLEngineSysIO.cpp \
../source/PLEngineSysNetworkAPI.cpp \
../source/PLEngineSysProcess.cpp \
../source/PLEngineSysSTLArithmeticAPI.cpp \
../source/PLEngineSysSchedulerAPI.cpp \
../source/PLEngineSysSynchron.cpp \
../source/PLEngineSysThreadPool.cpp \
../source/PLEngineSysWindowsAPI.cpp 

OBJS += \
./source/MainLib.o \
./source/PLEngineHeavyH.o \
./source/PLEngineLogSystemAPI.o \
./source/PLEngineMath.o \
./source/PLEngineMemoryPool.o \
./source/PLEngineRenderAPI.o \
./source/PLEngineResourceLoadAPI.o \
./source/PLEngineResourceManagerAPI.o \
./source/PLEngineScriptAPI.o \
./source/PLEngineSysAPI.o \
./source/PLEngineSysEnvIFM.o \
./source/PLEngineSysIO.o \
./source/PLEngineSysNetworkAPI.o \
./source/PLEngineSysProcess.o \
./source/PLEngineSysSTLArithmeticAPI.o \
./source/PLEngineSysSchedulerAPI.o \
./source/PLEngineSysSynchron.o \
./source/PLEngineSysThreadPool.o \
./source/PLEngineSysWindowsAPI.o 

CPP_DEPS += \
./source/MainLib.d \
./source/PLEngineHeavyH.d \
./source/PLEngineLogSystemAPI.d \
./source/PLEngineMath.d \
./source/PLEngineMemoryPool.d \
./source/PLEngineRenderAPI.d \
./source/PLEngineResourceLoadAPI.d \
./source/PLEngineResourceManagerAPI.d \
./source/PLEngineScriptAPI.d \
./source/PLEngineSysAPI.d \
./source/PLEngineSysEnvIFM.d \
./source/PLEngineSysIO.d \
./source/PLEngineSysNetworkAPI.d \
./source/PLEngineSysProcess.d \
./source/PLEngineSysSTLArithmeticAPI.d \
./source/PLEngineSysSchedulerAPI.d \
./source/PLEngineSysSynchron.d \
./source/PLEngineSysThreadPool.d \
./source/PLEngineSysWindowsAPI.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -DIDESetPrjExport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


