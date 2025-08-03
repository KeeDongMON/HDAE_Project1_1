################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Module/auto_parking.c 

COMPILED_SRCS += \
Module/auto_parking.src 

C_DEPS += \
Module/auto_parking.d 

OBJS += \
Module/auto_parking.o 


# Each subdirectory must supply rules for building sources it contributes
Module/auto_parking.src: ../Module/auto_parking.c Module/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Module/auto_parking.o: Module/auto_parking.src Module/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Module

clean-Module:
	-$(RM) Module/auto_parking.d Module/auto_parking.o Module/auto_parking.src

.PHONY: clean-Module

