################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Src/lab1.s 

C_SRCS += \
../Core/Src/common.c \
../Core/Src/k_mem.c \
../Core/Src/kernel.c \
../Core/Src/main.c \
../Core/Src/mainLAB3.c \
../Core/Src/main_group30.c \
../Core/Src/main_jekel.c \
../Core/Src/main_learn.c \
../Core/Src/main_learn1.c \
../Core/Src/main_robust.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/util.c 

OBJS += \
./Core/Src/common.o \
./Core/Src/k_mem.o \
./Core/Src/kernel.o \
./Core/Src/lab1.o \
./Core/Src/main.o \
./Core/Src/mainLAB3.o \
./Core/Src/main_group30.o \
./Core/Src/main_jekel.o \
./Core/Src/main_learn.o \
./Core/Src/main_learn1.o \
./Core/Src/main_robust.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/util.o 

S_DEPS += \
./Core/Src/lab1.d 

C_DEPS += \
./Core/Src/common.d \
./Core/Src/k_mem.d \
./Core/Src/kernel.d \
./Core/Src/main.d \
./Core/Src/mainLAB3.d \
./Core/Src/main_group30.d \
./Core/Src/main_jekel.d \
./Core/Src/main_learn.d \
./Core/Src/main_learn1.d \
./Core/Src/main_robust.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/util.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o: ../Core/Src/%.s Core/Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/common.cyclo ./Core/Src/common.d ./Core/Src/common.o ./Core/Src/common.su ./Core/Src/k_mem.cyclo ./Core/Src/k_mem.d ./Core/Src/k_mem.o ./Core/Src/k_mem.su ./Core/Src/kernel.cyclo ./Core/Src/kernel.d ./Core/Src/kernel.o ./Core/Src/kernel.su ./Core/Src/lab1.d ./Core/Src/lab1.o ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mainLAB3.cyclo ./Core/Src/mainLAB3.d ./Core/Src/mainLAB3.o ./Core/Src/mainLAB3.su ./Core/Src/main_group30.cyclo ./Core/Src/main_group30.d ./Core/Src/main_group30.o ./Core/Src/main_group30.su ./Core/Src/main_jekel.cyclo ./Core/Src/main_jekel.d ./Core/Src/main_jekel.o ./Core/Src/main_jekel.su ./Core/Src/main_learn.cyclo ./Core/Src/main_learn.d ./Core/Src/main_learn.o ./Core/Src/main_learn.su ./Core/Src/main_learn1.cyclo ./Core/Src/main_learn1.d ./Core/Src/main_learn1.o ./Core/Src/main_learn1.su ./Core/Src/main_robust.cyclo ./Core/Src/main_robust.d ./Core/Src/main_robust.o ./Core/Src/main_robust.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/util.cyclo ./Core/Src/util.d ./Core/Src/util.o ./Core/Src/util.su

.PHONY: clean-Core-2f-Src

