################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Ethernet/socket.c \
../Core/Src/Ethernet/w5500.c \
../Core/Src/Ethernet/w5500_spi.c \
../Core/Src/Ethernet/wizchip_conf.c 

OBJS += \
./Core/Src/Ethernet/socket.o \
./Core/Src/Ethernet/w5500.o \
./Core/Src/Ethernet/w5500_spi.o \
./Core/Src/Ethernet/wizchip_conf.o 

C_DEPS += \
./Core/Src/Ethernet/socket.d \
./Core/Src/Ethernet/w5500.d \
./Core/Src/Ethernet/w5500_spi.d \
./Core/Src/Ethernet/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Ethernet/%.o: ../Core/Src/Ethernet/%.c Core/Src/Ethernet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Cx -c -I../Core/Inc -I"C:/Users/ensty/STM32CubeIDE/workspace_1.7.0/EthernetDen/Core/Inc/Application" -I"C:/Users/ensty/STM32CubeIDE/workspace_1.7.0/EthernetDen/Core/Inc/Ethernet" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

