################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineOpenGLRdrAPI.cpp \
../EngineRenderAPI.cpp \
../PLEngineRenderPackage.cpp 

OBJS += \
./EngineOpenGLRdrAPI.o \
./EngineRenderAPI.o \
./PLEngineRenderPackage.o 

CPP_DEPS += \
./EngineOpenGLRdrAPI.d \
./EngineRenderAPI.d \
./PLEngineRenderPackage.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DIDESetPrjExport_Render -DIDESetLinuxOperatSystem -DIDESetGCCCompiler -I/home/Dev/3DEngine/PLEngine -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


