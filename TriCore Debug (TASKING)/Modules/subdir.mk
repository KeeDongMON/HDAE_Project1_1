################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/auto_parking.c 

COMPILED_SRCS += \
Modules/auto_parking.src 

C_DEPS += \
Modules/auto_parking.d 

OBJS += \
Modules/auto_parking.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/auto_parking.src: ../Modules/auto_parking.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/myprj/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O1 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/auto_parking.o: Modules/auto_parking.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Modules

clean-Modules:
	-$(RM) Modules/auto_parking.d Modules/auto_parking.o Modules/auto_parking.src

.PHONY: clean-Modules

