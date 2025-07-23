################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.c" \
"../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.c" 

COMPILED_SRCS += \
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.src" \
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.src" 

C_DEPS += \
"./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.d" \
"./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.d" 

OBJS += \
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.o" \
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.src":"../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.c" "Libraries/Infra/Ssw/TC37A/Tricore/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.o":"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.src" "Libraries/Infra/Ssw/TC37A/Tricore/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.src":"../Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.c" "Libraries/Infra/Ssw/TC37A/Tricore/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.o":"Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.src" "Libraries/Infra/Ssw/TC37A/Tricore/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Infra-2f-Ssw-2f-TC37A-2f-Tricore

clean-Libraries-2f-Infra-2f-Ssw-2f-TC37A-2f-Tricore:
	-$(RM) ./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.d ./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.o ./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Infra.src ./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.d ./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.o ./Libraries/Infra/Ssw/TC37A/Tricore/Ifx_Ssw_Tc0.src

.PHONY: clean-Libraries-2f-Infra-2f-Ssw-2f-TC37A-2f-Tricore

