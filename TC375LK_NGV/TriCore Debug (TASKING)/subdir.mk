################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Sys_Init.c" \
"../main.c" 

COMPILED_SRCS += \
"Sys_Init.src" \
"main.src" 

C_DEPS += \
"./Sys_Init.d" \
"./main.d" 

OBJS += \
"Sys_Init.o" \
"main.o" 


# Each subdirectory must supply rules for building sources it contributes
"Sys_Init.src":"../Sys_Init.c" "subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Sys_Init.o":"Sys_Init.src" "subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"main.src":"../main.c" "subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"main.o":"main.src" "subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean--2e-

clean--2e-:
	-$(RM) ./Sys_Init.d ./Sys_Init.o ./Sys_Init.src ./main.d ./main.o ./main.src

.PHONY: clean--2e-

