################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libraries/subdir.mk
-include 3-APP/GarageSys/subdir.mk
-include 1-HAL/voltameter/subdir.mk
-include 1-HAL/step_motor/subdir.mk
-include 1-HAL/SWITCH/subdir.mk
-include 1-HAL/SSD/subdir.mk
-include 1-HAL/LM35/subdir.mk
-include 1-HAL/LED/subdir.mk
-include 1-HAL/LDR/subdir.mk
-include 1-HAL/KEYPAD/subdir.mk
-include 1-HAL/DC_motor/subdir.mk
-include 1-HAL/DAC/subdir.mk
-include 1-HAL/CLCD/subdir.mk
-include 0-MCAL/5-ADC/subdir.mk
-include 0-MCAL/4-GIE/subdir.mk
-include 0-MCAL/3-EXTI/subdir.mk
-include 0-MCAL/2-Port/subdir.mk
-include 0-MCAL/1-DIO/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LDR_garageSystem.lss \

FLASH_IMAGE += \
LDR_garageSystem.hex \

EEPROM_IMAGE += \
LDR_garageSystem.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: LDR_garageSystem.elf secondary-outputs

# Tool invocations
LDR_garageSystem.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,LDR_garageSystem.map -mmcu=atmega32 -o "LDR_garageSystem.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LDR_garageSystem.lss: LDR_garageSystem.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S LDR_garageSystem.elf  >"LDR_garageSystem.lss"
	@echo 'Finished building: $@'
	@echo ' '

LDR_garageSystem.hex: LDR_garageSystem.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex LDR_garageSystem.elf  "LDR_garageSystem.hex"
	@echo 'Finished building: $@'
	@echo ' '

LDR_garageSystem.eep: LDR_garageSystem.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex LDR_garageSystem.elf  "LDR_garageSystem.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LDR_garageSystem.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 LDR_garageSystem.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) LDR_garageSystem.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
