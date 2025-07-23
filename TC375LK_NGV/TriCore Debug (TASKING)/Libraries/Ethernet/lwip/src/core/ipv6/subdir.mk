################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/ethip6.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/icmp6.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/inet6.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/ip6.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/mld6.c" \
"../Libraries/Ethernet/lwip/src/core/ipv6/nd6.c" 

COMPILED_SRCS += \
"Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/ethip6.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/icmp6.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/inet6.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/ip6.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/mld6.src" \
"Libraries/Ethernet/lwip/src/core/ipv6/nd6.src" 

C_DEPS += \
"./Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/ethip6.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/icmp6.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/inet6.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/ip6.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/mld6.d" \
"./Libraries/Ethernet/lwip/src/core/ipv6/nd6.d" 

OBJS += \
"Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/ethip6.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/icmp6.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/inet6.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/ip6.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/mld6.o" \
"Libraries/Ethernet/lwip/src/core/ipv6/nd6.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.o":"Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ethip6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/ethip6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ethip6.o":"Libraries/Ethernet/lwip/src/core/ipv6/ethip6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/icmp6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/icmp6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/icmp6.o":"Libraries/Ethernet/lwip/src/core/ipv6/icmp6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/inet6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/inet6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/inet6.o":"Libraries/Ethernet/lwip/src/core/ipv6/inet6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ip6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/ip6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ip6.o":"Libraries/Ethernet/lwip/src/core/ipv6/ip6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.src":"../Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.o":"Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.src":"../Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.o":"Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/mld6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/mld6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/mld6.o":"Libraries/Ethernet/lwip/src/core/ipv6/mld6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/nd6.src":"../Libraries/Ethernet/lwip/src/core/ipv6/nd6.c" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	cctc -cs --misrac-version=2004 -D__CPU__=tc37x "-fD:/_github/tc375tp-litekit-ngv/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -Wc-g3 -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/Ethernet/lwip/src/core/ipv6/nd6.o":"Libraries/Ethernet/lwip/src/core/ipv6/nd6.src" "Libraries/Ethernet/lwip/src/core/ipv6/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core-2f-ipv6

clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core-2f-ipv6:
	-$(RM) ./Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.d ./Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.o ./Libraries/Ethernet/lwip/src/core/ipv6/dhcp6.src ./Libraries/Ethernet/lwip/src/core/ipv6/ethip6.d ./Libraries/Ethernet/lwip/src/core/ipv6/ethip6.o ./Libraries/Ethernet/lwip/src/core/ipv6/ethip6.src ./Libraries/Ethernet/lwip/src/core/ipv6/icmp6.d ./Libraries/Ethernet/lwip/src/core/ipv6/icmp6.o ./Libraries/Ethernet/lwip/src/core/ipv6/icmp6.src ./Libraries/Ethernet/lwip/src/core/ipv6/inet6.d ./Libraries/Ethernet/lwip/src/core/ipv6/inet6.o ./Libraries/Ethernet/lwip/src/core/ipv6/inet6.src ./Libraries/Ethernet/lwip/src/core/ipv6/ip6.d ./Libraries/Ethernet/lwip/src/core/ipv6/ip6.o ./Libraries/Ethernet/lwip/src/core/ipv6/ip6.src ./Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.d ./Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.o ./Libraries/Ethernet/lwip/src/core/ipv6/ip6_addr.src ./Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.d ./Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.o ./Libraries/Ethernet/lwip/src/core/ipv6/ip6_frag.src ./Libraries/Ethernet/lwip/src/core/ipv6/mld6.d ./Libraries/Ethernet/lwip/src/core/ipv6/mld6.o ./Libraries/Ethernet/lwip/src/core/ipv6/mld6.src ./Libraries/Ethernet/lwip/src/core/ipv6/nd6.d ./Libraries/Ethernet/lwip/src/core/ipv6/nd6.o ./Libraries/Ethernet/lwip/src/core/ipv6/nd6.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core-2f-ipv6

