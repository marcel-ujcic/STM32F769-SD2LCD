################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/src/option/syscall.c \
../Middlewares/Third_Party/src/option/unicode.c 

OBJS += \
./Middlewares/Third_Party/src/option/syscall.o \
./Middlewares/Third_Party/src/option/unicode.o 

C_DEPS += \
./Middlewares/Third_Party/src/option/syscall.d \
./Middlewares/Third_Party/src/option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/src/option/%.o: ../Middlewares/Third_Party/src/option/%.c Middlewares/Third_Party/src/option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/BSP/STM32F769I-Discovery -I"C:/Users/marcel/Documents/3_letnik/VGRS/lcd_rtos/lcd_rtos/Middlewares/Third_Party/src" -I/lcd_rtos/Middlewares/Third_Party/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-src-2f-option

clean-Middlewares-2f-Third_Party-2f-src-2f-option:
	-$(RM) ./Middlewares/Third_Party/src/option/syscall.d ./Middlewares/Third_Party/src/option/syscall.o ./Middlewares/Third_Party/src/option/unicode.d ./Middlewares/Third_Party/src/option/unicode.o

.PHONY: clean-Middlewares-2f-Third_Party-2f-src-2f-option

