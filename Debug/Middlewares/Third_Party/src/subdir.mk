################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/src/diskio.c \
../Middlewares/Third_Party/src/ff.c \
../Middlewares/Third_Party/src/ff_gen_drv.c 

OBJS += \
./Middlewares/Third_Party/src/diskio.o \
./Middlewares/Third_Party/src/ff.o \
./Middlewares/Third_Party/src/ff_gen_drv.o 

C_DEPS += \
./Middlewares/Third_Party/src/diskio.d \
./Middlewares/Third_Party/src/ff.d \
./Middlewares/Third_Party/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/src/%.o: ../Middlewares/Third_Party/src/%.c Middlewares/Third_Party/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F769xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/BSP/STM32F769I-Discovery -I"C:/Users/marcel/Documents/3_letnik/VGRS/lcd_rtos/lcd_rtos/Middlewares/Third_Party/src" -I/lcd_rtos/Middlewares/Third_Party/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-src

clean-Middlewares-2f-Third_Party-2f-src:
	-$(RM) ./Middlewares/Third_Party/src/diskio.d ./Middlewares/Third_Party/src/diskio.o ./Middlewares/Third_Party/src/ff.d ./Middlewares/Third_Party/src/ff.o ./Middlewares/Third_Party/src/ff_gen_drv.d ./Middlewares/Third_Party/src/ff_gen_drv.o

.PHONY: clean-Middlewares-2f-Third_Party-2f-src

