################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineResourceManagerAPI.cpp \
../EngineResourceMaterialMgr.cpp \
../EngineResourcePolygonMgr.cpp \
../EngineResourceScriptMgr.cpp \
../EngineResourceSoundMgr.cpp \
../EngineResourceTextureMgr.cpp \
../EngineResourceVideoMgr.cpp \
../EngineResourceWaveMgr.cpp \
../PLEngineResourceManagerPackage.cpp 

OBJS += \
./EngineResourceManagerAPI.o \
./EngineResourceMaterialMgr.o \
./EngineResourcePolygonMgr.o \
./EngineResourceScriptMgr.o \
./EngineResourceSoundMgr.o \
./EngineResourceTextureMgr.o \
./EngineResourceVideoMgr.o \
./EngineResourceWaveMgr.o \
./PLEngineResourceManagerPackage.o 

CPP_DEPS += \
./EngineResourceManagerAPI.d \
./EngineResourceMaterialMgr.d \
./EngineResourcePolygonMgr.d \
./EngineResourceScriptMgr.d \
./EngineResourceSoundMgr.d \
./EngineResourceTextureMgr.d \
./EngineResourceVideoMgr.d \
./EngineResourceWaveMgr.d \
./PLEngineResourceManagerPackage.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetPrjExport_ResManager -DIDESetGCCCompiler -I/home/Dev/3DEngine/PLEngine -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


