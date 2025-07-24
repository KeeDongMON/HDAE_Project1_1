################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.c" 

COMPILED_SRCS += \
"Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.src" 

C_DEPS += \
"./Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.d" 

OBJS += \
"Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.src":"../Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.c" "Libraries/iLLD/TC37A/Tricore/Src/Std/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.o":"Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.src" "Libraries/iLLD/TC37A/Tricore/Src/Std/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Src-2f-Std

clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Src-2f-Std:
	-$(RM) ./Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.d ./Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.o ./Libraries/iLLD/TC37A/Tricore/Src/Std/IfxSrc.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Src-2f-Std

