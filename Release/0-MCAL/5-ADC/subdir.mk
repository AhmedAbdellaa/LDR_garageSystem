################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0-MCAL/5-ADC/ADC_prog.c 

OBJS += \
./0-MCAL/5-ADC/ADC_prog.o 

C_DEPS += \
./0-MCAL/5-ADC/ADC_prog.d 


# Each subdirectory must supply rules for building sources it contributes
0-MCAL/5-ADC/%.o: ../0-MCAL/5-ADC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


