################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineBSPTreeAPI.cpp \
../EngineOctreeTreeAPI.cpp \
../EngineSceneGraphAPI.cpp \
../PLEngineScenePackage.cpp 

OBJS += \
./EngineBSPTreeAPI.o \
./EngineOctreeTreeAPI.o \
./EngineSceneGraphAPI.o \
./PLEngineScenePackage.o 

CPP_DEPS += \
./EngineBSPTreeAPI.d \
./EngineOctreeTreeAPI.d \
./EngineSceneGraphAPI.d \
./PLEngineScenePackage.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetLinuxOperatSystem -DIDESetPrjExport_Scene -DIDESetGCCCompiler -I/home/Dev/3DEngine/PLEngine -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


