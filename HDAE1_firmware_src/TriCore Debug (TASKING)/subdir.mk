################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../Sys_Init.c 

COMPILED_SRCS += \
Cpu0_Main.src \
Cpu1_Main.src \
Cpu2_Main.src \
Sys_Init.src 

C_DEPS += \
Cpu0_Main.d \
Cpu1_Main.d \
Cpu2_Main.d \
Sys_Init.d 

OBJS += \
Cpu0_Main.o \
Cpu1_Main.o \
Cpu2_Main.o \
Sys_Init.o 


# Each subdirectory must supply rules for building sources it contributes
Cpu0_Main.src: ../Cpu0_Main.c subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/0729prj/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Cpu0_Main.o: Cpu0_Main.src subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Cpu1_Main.src: ../Cpu1_Main.c subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/0729prj/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Cpu1_Main.o: Cpu1_Main.src subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Cpu2_Main.src: ../Cpu2_Main.c subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/0729prj/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Cpu2_Main.o: Cpu2_Main.src subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Sys_Init.src: ../Sys_Init.c subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/0729prj/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Sys_Init.o: Sys_Init.src subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean--2e-

clean--2e-:
	-$(RM) Cpu0_Main.d Cpu0_Main.o Cpu0_Main.src Cpu1_Main.d Cpu1_Main.o Cpu1_Main.src Cpu2_Main.d Cpu2_Main.o Cpu2_Main.src Sys_Init.d Sys_Init.o Sys_Init.src

.PHONY: clean--2e-

