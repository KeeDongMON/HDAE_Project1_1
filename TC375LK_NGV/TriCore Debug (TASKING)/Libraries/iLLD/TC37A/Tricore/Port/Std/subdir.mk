################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.c 

COMPILED_SRCS += \
Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.src 

C_DEPS += \
Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.d 

OBJS += \
Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.src: ../Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.c Libraries/iLLD/TC37A/Tricore/Port/Std/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.o: Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.src Libraries/iLLD/TC37A/Tricore/Port/Std/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Port-2f-Std

clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Port-2f-Std:
	-$(RM) Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.d Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.o Libraries/iLLD/TC37A/Tricore/Port/Std/IfxPort.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Port-2f-Std

