################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/Ethernet/lwip/src/netif/bridgeif.c" \
"../Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.c" \
"../Libraries/Ethernet/lwip/src/netif/ethernet.c" \
"../Libraries/Ethernet/lwip/src/netif/lowpan6.c" \
"../Libraries/Ethernet/lwip/src/netif/lowpan6_ble.c" \
"../Libraries/Ethernet/lwip/src/netif/lowpan6_common.c" \
"../Libraries/Ethernet/lwip/src/netif/zepif.c" 

COMPILED_SRCS += \
"Libraries/Ethernet/lwip/src/netif/bridgeif.src" \
"Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.src" \
"Libraries/Ethernet/lwip/src/netif/ethernet.src" \
"Libraries/Ethernet/lwip/src/netif/lowpan6.src" \
"Libraries/Ethernet/lwip/src/netif/lowpan6_ble.src" \
"Libraries/Ethernet/lwip/src/netif/lowpan6_common.src" \
"Libraries/Ethernet/lwip/src/netif/zepif.src" 

C_DEPS += \
"./Libraries/Ethernet/lwip/src/netif/bridgeif.d" \
"./Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.d" \
"./Libraries/Ethernet/lwip/src/netif/ethernet.d" \
"./Libraries/Ethernet/lwip/src/netif/lowpan6.d" \
"./Libraries/Ethernet/lwip/src/netif/lowpan6_ble.d" \
"./Libraries/Ethernet/lwip/src/netif/lowpan6_common.d" \
"./Libraries/Ethernet/lwip/src/netif/zepif.d" 

OBJS += \
"Libraries/Ethernet/lwip/src/netif/bridgeif.o" \
"Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.o" \
"Libraries/Ethernet/lwip/src/netif/ethernet.o" \
"Libraries/Ethernet/lwip/src/netif/lowpan6.o" \
"Libraries/Ethernet/lwip/src/netif/lowpan6_ble.o" \
"Libraries/Ethernet/lwip/src/netif/lowpan6_common.o" \
"Libraries/Ethernet/lwip/src/netif/zepif.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/Ethernet/lwip/src/netif/bridgeif.src":"../Libraries/Ethernet/lwip/src/netif/bridgeif.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/bridgeif.o":"Libraries/Ethernet/lwip/src/netif/bridgeif.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.src":"../Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.o":"Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/ethernet.src":"../Libraries/Ethernet/lwip/src/netif/ethernet.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/ethernet.o":"Libraries/Ethernet/lwip/src/netif/ethernet.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/lowpan6.src":"../Libraries/Ethernet/lwip/src/netif/lowpan6.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/lowpan6.o":"Libraries/Ethernet/lwip/src/netif/lowpan6.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/lowpan6_ble.src":"../Libraries/Ethernet/lwip/src/netif/lowpan6_ble.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/lowpan6_ble.o":"Libraries/Ethernet/lwip/src/netif/lowpan6_ble.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/lowpan6_common.src":"../Libraries/Ethernet/lwip/src/netif/lowpan6_common.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/lowpan6_common.o":"Libraries/Ethernet/lwip/src/netif/lowpan6_common.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/zepif.src":"../Libraries/Ethernet/lwip/src/netif/zepif.c" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/netif/zepif.o":"Libraries/Ethernet/lwip/src/netif/zepif.src" "Libraries/Ethernet/lwip/src/netif/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-netif

clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-netif:
	-$(RM) ./Libraries/Ethernet/lwip/src/netif/bridgeif.d ./Libraries/Ethernet/lwip/src/netif/bridgeif.o ./Libraries/Ethernet/lwip/src/netif/bridgeif.src ./Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.d ./Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.o ./Libraries/Ethernet/lwip/src/netif/bridgeif_fdb.src ./Libraries/Ethernet/lwip/src/netif/ethernet.d ./Libraries/Ethernet/lwip/src/netif/ethernet.o ./Libraries/Ethernet/lwip/src/netif/ethernet.src ./Libraries/Ethernet/lwip/src/netif/lowpan6.d ./Libraries/Ethernet/lwip/src/netif/lowpan6.o ./Libraries/Ethernet/lwip/src/netif/lowpan6.src ./Libraries/Ethernet/lwip/src/netif/lowpan6_ble.d ./Libraries/Ethernet/lwip/src/netif/lowpan6_ble.o ./Libraries/Ethernet/lwip/src/netif/lowpan6_ble.src ./Libraries/Ethernet/lwip/src/netif/lowpan6_common.d ./Libraries/Ethernet/lwip/src/netif/lowpan6_common.o ./Libraries/Ethernet/lwip/src/netif/lowpan6_common.src ./Libraries/Ethernet/lwip/src/netif/zepif.d ./Libraries/Ethernet/lwip/src/netif/zepif.o ./Libraries/Ethernet/lwip/src/netif/zepif.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-netif

