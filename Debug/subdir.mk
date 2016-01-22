################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bluetooth.c \
../LSM9DS1_drivers.c \
../Main.c \
../timerFunctions.c \
../timerFunctionsLSM.c 

OBJS += \
./Bluetooth.o \
./LSM9DS1_drivers.o \
./Main.o \
./timerFunctions.o \
./timerFunctionsLSM.o 

C_DEPS += \
./Bluetooth.d \
./LSM9DS1_drivers.d \
./Main.d \
./timerFunctions.d \
./timerFunctionsLSM.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=4503003 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC4500_series/Include" -I"C:\DAVE3_workspace\mojWorkspace\Bachelor\Dave\Generated\inc\MOTORLIBS" -I"C:\DAVE3_workspace\mojWorkspace\Bachelor\Dave\Generated\inc\DAVESupport" -I"C:\DAVE3_workspace\mojWorkspace\Bachelor\Dave\Generated\inc\LIBS" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


