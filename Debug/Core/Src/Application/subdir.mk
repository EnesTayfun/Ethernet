################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Application/loopback.c 

OBJS += \
./Core/Src/Application/loopback.o 

C_DEPS += \
./Core/Src/Application/loopback.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Application/%.o: ../Core/Src/Application/%.c Core/Src/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Cx -c -I../Core/Inc -I"C:/Users/ensty/STM32CubeIDE/workspace_1.7.0/EthernetDen/Core/Inc/Application" -I"C:/Users/ensty/STM32CubeIDE/workspace_1.7.0/EthernetDen/Core/Inc/Ethernet" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

