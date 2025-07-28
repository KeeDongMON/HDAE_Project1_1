################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Ethernet/lwip/src/core/ipv4/autoip.c \
../Libraries/Ethernet/lwip/src/core/ipv4/dhcp.c \
../Libraries/Ethernet/lwip/src/core/ipv4/etharp.c \
../Libraries/Ethernet/lwip/src/core/ipv4/icmp.c \
../Libraries/Ethernet/lwip/src/core/ipv4/igmp.c \
../Libraries/Ethernet/lwip/src/core/ipv4/ip4.c \
../Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.c \
../Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.c 

COMPILED_SRCS += \
Libraries/Ethernet/lwip/src/core/ipv4/autoip.src \
Libraries/Ethernet/lwip/src/core/ipv4/dhcp.src \
Libraries/Ethernet/lwip/src/core/ipv4/etharp.src \
Libraries/Ethernet/lwip/src/core/ipv4/icmp.src \
Libraries/Ethernet/lwip/src/core/ipv4/igmp.src \
Libraries/Ethernet/lwip/src/core/ipv4/ip4.src \
Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.src \
Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.src 

C_DEPS += \
Libraries/Ethernet/lwip/src/core/ipv4/autoip.d \
Libraries/Ethernet/lwip/src/core/ipv4/dhcp.d \
Libraries/Ethernet/lwip/src/core/ipv4/etharp.d \
Libraries/Ethernet/lwip/src/core/ipv4/icmp.d \
Libraries/Ethernet/lwip/src/core/ipv4/igmp.d \
Libraries/Ethernet/lwip/src/core/ipv4/ip4.d \
Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.d \
Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.d 

OBJS += \
Libraries/Ethernet/lwip/src/core/ipv4/autoip.o \
Libraries/Ethernet/lwip/src/core/ipv4/dhcp.o \
Libraries/Ethernet/lwip/src/core/ipv4/etharp.o \
Libraries/Ethernet/lwip/src/core/ipv4/icmp.o \
Libraries/Ethernet/lwip/src/core/ipv4/igmp.o \
Libraries/Ethernet/lwip/src/core/ipv4/ip4.o \
Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.o \
Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Ethernet/lwip/src/core/ipv4/autoip.src: ../Libraries/Ethernet/lwip/src/core/ipv4/autoip.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/autoip.o: Libraries/Ethernet/lwip/src/core/ipv4/autoip.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/dhcp.src: ../Libraries/Ethernet/lwip/src/core/ipv4/dhcp.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/dhcp.o: Libraries/Ethernet/lwip/src/core/ipv4/dhcp.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/etharp.src: ../Libraries/Ethernet/lwip/src/core/ipv4/etharp.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/etharp.o: Libraries/Ethernet/lwip/src/core/ipv4/etharp.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/icmp.src: ../Libraries/Ethernet/lwip/src/core/ipv4/icmp.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/icmp.o: Libraries/Ethernet/lwip/src/core/ipv4/icmp.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/igmp.src: ../Libraries/Ethernet/lwip/src/core/ipv4/igmp.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/igmp.o: Libraries/Ethernet/lwip/src/core/ipv4/igmp.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/ip4.src: ../Libraries/Ethernet/lwip/src/core/ipv4/ip4.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/ip4.o: Libraries/Ethernet/lwip/src/core/ipv4/ip4.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.src: ../Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.o: Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.src: ../Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.c Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.o: Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.src Libraries/Ethernet/lwip/src/core/ipv4/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core-2f-ipv4

clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core-2f-ipv4:
	-$(RM) Libraries/Ethernet/lwip/src/core/ipv4/autoip.d Libraries/Ethernet/lwip/src/core/ipv4/autoip.o Libraries/Ethernet/lwip/src/core/ipv4/autoip.src Libraries/Ethernet/lwip/src/core/ipv4/dhcp.d Libraries/Ethernet/lwip/src/core/ipv4/dhcp.o Libraries/Ethernet/lwip/src/core/ipv4/dhcp.src Libraries/Ethernet/lwip/src/core/ipv4/etharp.d Libraries/Ethernet/lwip/src/core/ipv4/etharp.o Libraries/Ethernet/lwip/src/core/ipv4/etharp.src Libraries/Ethernet/lwip/src/core/ipv4/icmp.d Libraries/Ethernet/lwip/src/core/ipv4/icmp.o Libraries/Ethernet/lwip/src/core/ipv4/icmp.src Libraries/Ethernet/lwip/src/core/ipv4/igmp.d Libraries/Ethernet/lwip/src/core/ipv4/igmp.o Libraries/Ethernet/lwip/src/core/ipv4/igmp.src Libraries/Ethernet/lwip/src/core/ipv4/ip4.d Libraries/Ethernet/lwip/src/core/ipv4/ip4.o Libraries/Ethernet/lwip/src/core/ipv4/ip4.src Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.d Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.o Libraries/Ethernet/lwip/src/core/ipv4/ip4_addr.src Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.d Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.o Libraries/Ethernet/lwip/src/core/ipv4/ip4_frag.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core-2f-ipv4

