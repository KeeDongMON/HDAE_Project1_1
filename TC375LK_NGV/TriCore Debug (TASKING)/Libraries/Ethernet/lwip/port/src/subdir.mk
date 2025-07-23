################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/Ethernet/lwip/port/src/Ifx_Lwip.c" \
"../Libraries/Ethernet/lwip/port/src/netif.c" 

COMPILED_SRCS += \
"Libraries/Ethernet/lwip/port/src/Ifx_Lwip.src" \
"Libraries/Ethernet/lwip/port/src/netif.src" 

C_DEPS += \
"./Libraries/Ethernet/lwip/port/src/Ifx_Lwip.d" \
"./Libraries/Ethernet/lwip/port/src/netif.d" 

OBJS += \
"Libraries/Ethernet/lwip/port/src/Ifx_Lwip.o" \
"Libraries/Ethernet/lwip/port/src/netif.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/Ethernet/lwip/port/src/Ifx_Lwip.src":"../Libraries/Ethernet/lwip/port/src/Ifx_Lwip.c" "Libraries/Ethernet/lwip/port/src/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/port/src/Ifx_Lwip.o":"Libraries/Ethernet/lwip/port/src/Ifx_Lwip.src" "Libraries/Ethernet/lwip/port/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/port/src/netif.src":"../Libraries/Ethernet/lwip/port/src/netif.c" "Libraries/Ethernet/lwip/port/src/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/port/src/netif.o":"Libraries/Ethernet/lwip/port/src/netif.src" "Libraries/Ethernet/lwip/port/src/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-port-2f-src

clean-Libraries-2f-Ethernet-2f-lwip-2f-port-2f-src:
	-$(RM) ./Libraries/Ethernet/lwip/port/src/Ifx_Lwip.d ./Libraries/Ethernet/lwip/port/src/Ifx_Lwip.o ./Libraries/Ethernet/lwip/port/src/Ifx_Lwip.src ./Libraries/Ethernet/lwip/port/src/netif.d ./Libraries/Ethernet/lwip/port/src/netif.o ./Libraries/Ethernet/lwip/port/src/netif.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-port-2f-src

