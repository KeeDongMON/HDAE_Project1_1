################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.c 

COMPILED_SRCS += \
Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.src 

C_DEPS += \
Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.d 

OBJS += \
Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.src: ../Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.c Libraries/iLLD/TC37A/Tricore/Geth/Eth/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/�꽕移섑봽濡쒓렇�옩_(KDT)�엫踰좊뵒�뱶 �냼�봽�듃�썾�뼱 媛쒕컻 湲곗큹/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.o: Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.src Libraries/iLLD/TC37A/Tricore/Geth/Eth/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Geth-2f-Eth

clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Geth-2f-Eth:
	-$(RM) Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.d Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.o Libraries/iLLD/TC37A/Tricore/Geth/Eth/IfxGeth_Eth.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Geth-2f-Eth

