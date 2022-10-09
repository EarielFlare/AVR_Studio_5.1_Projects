################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Core \
../Core/inc \
../Core/src


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Core/src/diag_print.c \
../Core/src/usart.c \
../Core/src/usartproj5.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Core/src/diag_print.o \
Core/src/usart.o \
Core/src/usartproj5.o


OBJS_AS_ARGS +=  \
Core/src/diag_print.o \
Core/src/usart.o \
Core/src/usartproj5.o


C_DEPS +=  \
Core/src/diag_print.d \
Core/src/usart.d \
Core/src/usartproj5.d


C_DEPS_AS_ARGS +=  \
Core/src/diag_print.d \
Core/src/usart.d \
Core/src/usartproj5.d


OUTPUT_FILE_PATH +=usartproj5.elf

OUTPUT_FILE_PATH_AS_ARGS +=usartproj5.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler







Core/src/%.o: ../Core/src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -I"../Core/inc"  -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega168p  -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C Linker
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="usartproj5.map" -Wl,-lm   -mmcu=atmega168p  
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "usartproj5.elf" "usartproj5.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "usartproj5.elf" "usartproj5.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "usartproj5.elf" > "usartproj5.lss"
	"C:\WinAVR-20100110\bin\avr-size.exe" -C --mcu=atmega168p  "usartproj5.elf"
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "usartproj5.hex" "usartproj5.lss" "usartproj5.eep" "usartproj5.map"
	