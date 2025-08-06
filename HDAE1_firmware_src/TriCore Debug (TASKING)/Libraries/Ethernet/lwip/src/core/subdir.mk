################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Ethernet/lwip/src/core/altcp.c \
../Libraries/Ethernet/lwip/src/core/altcp_alloc.c \
../Libraries/Ethernet/lwip/src/core/altcp_tcp.c \
../Libraries/Ethernet/lwip/src/core/def.c \
../Libraries/Ethernet/lwip/src/core/dns.c \
../Libraries/Ethernet/lwip/src/core/inet_chksum.c \
../Libraries/Ethernet/lwip/src/core/init.c \
../Libraries/Ethernet/lwip/src/core/ip.c \
../Libraries/Ethernet/lwip/src/core/mem.c \
../Libraries/Ethernet/lwip/src/core/memp.c \
../Libraries/Ethernet/lwip/src/core/netif.c \
../Libraries/Ethernet/lwip/src/core/pbuf.c \
../Libraries/Ethernet/lwip/src/core/raw.c \
../Libraries/Ethernet/lwip/src/core/stats.c \
../Libraries/Ethernet/lwip/src/core/sys.c \
../Libraries/Ethernet/lwip/src/core/tcp.c \
../Libraries/Ethernet/lwip/src/core/tcp_in.c \
../Libraries/Ethernet/lwip/src/core/tcp_out.c \
../Libraries/Ethernet/lwip/src/core/timeouts.c \
../Libraries/Ethernet/lwip/src/core/udp.c 

COMPILED_SRCS += \
Libraries/Ethernet/lwip/src/core/altcp.src \
Libraries/Ethernet/lwip/src/core/altcp_alloc.src \
Libraries/Ethernet/lwip/src/core/altcp_tcp.src \
Libraries/Ethernet/lwip/src/core/def.src \
Libraries/Ethernet/lwip/src/core/dns.src \
Libraries/Ethernet/lwip/src/core/inet_chksum.src \
Libraries/Ethernet/lwip/src/core/init.src \
Libraries/Ethernet/lwip/src/core/ip.src \
Libraries/Ethernet/lwip/src/core/mem.src \
Libraries/Ethernet/lwip/src/core/memp.src \
Libraries/Ethernet/lwip/src/core/netif.src \
Libraries/Ethernet/lwip/src/core/pbuf.src \
Libraries/Ethernet/lwip/src/core/raw.src \
Libraries/Ethernet/lwip/src/core/stats.src \
Libraries/Ethernet/lwip/src/core/sys.src \
Libraries/Ethernet/lwip/src/core/tcp.src \
Libraries/Ethernet/lwip/src/core/tcp_in.src \
Libraries/Ethernet/lwip/src/core/tcp_out.src \
Libraries/Ethernet/lwip/src/core/timeouts.src \
Libraries/Ethernet/lwip/src/core/udp.src 

C_DEPS += \
Libraries/Ethernet/lwip/src/core/altcp.d \
Libraries/Ethernet/lwip/src/core/altcp_alloc.d \
Libraries/Ethernet/lwip/src/core/altcp_tcp.d \
Libraries/Ethernet/lwip/src/core/def.d \
Libraries/Ethernet/lwip/src/core/dns.d \
Libraries/Ethernet/lwip/src/core/inet_chksum.d \
Libraries/Ethernet/lwip/src/core/init.d \
Libraries/Ethernet/lwip/src/core/ip.d \
Libraries/Ethernet/lwip/src/core/mem.d \
Libraries/Ethernet/lwip/src/core/memp.d \
Libraries/Ethernet/lwip/src/core/netif.d \
Libraries/Ethernet/lwip/src/core/pbuf.d \
Libraries/Ethernet/lwip/src/core/raw.d \
Libraries/Ethernet/lwip/src/core/stats.d \
Libraries/Ethernet/lwip/src/core/sys.d \
Libraries/Ethernet/lwip/src/core/tcp.d \
Libraries/Ethernet/lwip/src/core/tcp_in.d \
Libraries/Ethernet/lwip/src/core/tcp_out.d \
Libraries/Ethernet/lwip/src/core/timeouts.d \
Libraries/Ethernet/lwip/src/core/udp.d 

OBJS += \
Libraries/Ethernet/lwip/src/core/altcp.o \
Libraries/Ethernet/lwip/src/core/altcp_alloc.o \
Libraries/Ethernet/lwip/src/core/altcp_tcp.o \
Libraries/Ethernet/lwip/src/core/def.o \
Libraries/Ethernet/lwip/src/core/dns.o \
Libraries/Ethernet/lwip/src/core/inet_chksum.o \
Libraries/Ethernet/lwip/src/core/init.o \
Libraries/Ethernet/lwip/src/core/ip.o \
Libraries/Ethernet/lwip/src/core/mem.o \
Libraries/Ethernet/lwip/src/core/memp.o \
Libraries/Ethernet/lwip/src/core/netif.o \
Libraries/Ethernet/lwip/src/core/pbuf.o \
Libraries/Ethernet/lwip/src/core/raw.o \
Libraries/Ethernet/lwip/src/core/stats.o \
Libraries/Ethernet/lwip/src/core/sys.o \
Libraries/Ethernet/lwip/src/core/tcp.o \
Libraries/Ethernet/lwip/src/core/tcp_in.o \
Libraries/Ethernet/lwip/src/core/tcp_out.o \
Libraries/Ethernet/lwip/src/core/timeouts.o \
Libraries/Ethernet/lwip/src/core/udp.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Ethernet/lwip/src/core/altcp.src: ../Libraries/Ethernet/lwip/src/core/altcp.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/altcp.o: Libraries/Ethernet/lwip/src/core/altcp.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/altcp_alloc.src: ../Libraries/Ethernet/lwip/src/core/altcp_alloc.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/altcp_alloc.o: Libraries/Ethernet/lwip/src/core/altcp_alloc.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/altcp_tcp.src: ../Libraries/Ethernet/lwip/src/core/altcp_tcp.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/altcp_tcp.o: Libraries/Ethernet/lwip/src/core/altcp_tcp.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/def.src: ../Libraries/Ethernet/lwip/src/core/def.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/def.o: Libraries/Ethernet/lwip/src/core/def.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/dns.src: ../Libraries/Ethernet/lwip/src/core/dns.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/dns.o: Libraries/Ethernet/lwip/src/core/dns.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/inet_chksum.src: ../Libraries/Ethernet/lwip/src/core/inet_chksum.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/inet_chksum.o: Libraries/Ethernet/lwip/src/core/inet_chksum.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/init.src: ../Libraries/Ethernet/lwip/src/core/init.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/init.o: Libraries/Ethernet/lwip/src/core/init.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/ip.src: ../Libraries/Ethernet/lwip/src/core/ip.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/ip.o: Libraries/Ethernet/lwip/src/core/ip.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/mem.src: ../Libraries/Ethernet/lwip/src/core/mem.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/mem.o: Libraries/Ethernet/lwip/src/core/mem.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/memp.src: ../Libraries/Ethernet/lwip/src/core/memp.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/memp.o: Libraries/Ethernet/lwip/src/core/memp.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/netif.src: ../Libraries/Ethernet/lwip/src/core/netif.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/netif.o: Libraries/Ethernet/lwip/src/core/netif.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/pbuf.src: ../Libraries/Ethernet/lwip/src/core/pbuf.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/pbuf.o: Libraries/Ethernet/lwip/src/core/pbuf.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/raw.src: ../Libraries/Ethernet/lwip/src/core/raw.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/raw.o: Libraries/Ethernet/lwip/src/core/raw.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/stats.src: ../Libraries/Ethernet/lwip/src/core/stats.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/stats.o: Libraries/Ethernet/lwip/src/core/stats.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/sys.src: ../Libraries/Ethernet/lwip/src/core/sys.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/sys.o: Libraries/Ethernet/lwip/src/core/sys.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/tcp.src: ../Libraries/Ethernet/lwip/src/core/tcp.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/tcp.o: Libraries/Ethernet/lwip/src/core/tcp.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/tcp_in.src: ../Libraries/Ethernet/lwip/src/core/tcp_in.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/tcp_in.o: Libraries/Ethernet/lwip/src/core/tcp_in.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/tcp_out.src: ../Libraries/Ethernet/lwip/src/core/tcp_out.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/tcp_out.o: Libraries/Ethernet/lwip/src/core/tcp_out.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/timeouts.src: ../Libraries/Ethernet/lwip/src/core/timeouts.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/timeouts.o: Libraries/Ethernet/lwip/src/core/timeouts.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/core/udp.src: ../Libraries/Ethernet/lwip/src/core/udp.c Libraries/Ethernet/lwip/src/core/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/core/udp.o: Libraries/Ethernet/lwip/src/core/udp.src Libraries/Ethernet/lwip/src/core/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core

clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core:
	-$(RM) Libraries/Ethernet/lwip/src/core/altcp.d Libraries/Ethernet/lwip/src/core/altcp.o Libraries/Ethernet/lwip/src/core/altcp.src Libraries/Ethernet/lwip/src/core/altcp_alloc.d Libraries/Ethernet/lwip/src/core/altcp_alloc.o Libraries/Ethernet/lwip/src/core/altcp_alloc.src Libraries/Ethernet/lwip/src/core/altcp_tcp.d Libraries/Ethernet/lwip/src/core/altcp_tcp.o Libraries/Ethernet/lwip/src/core/altcp_tcp.src Libraries/Ethernet/lwip/src/core/def.d Libraries/Ethernet/lwip/src/core/def.o Libraries/Ethernet/lwip/src/core/def.src Libraries/Ethernet/lwip/src/core/dns.d Libraries/Ethernet/lwip/src/core/dns.o Libraries/Ethernet/lwip/src/core/dns.src Libraries/Ethernet/lwip/src/core/inet_chksum.d Libraries/Ethernet/lwip/src/core/inet_chksum.o Libraries/Ethernet/lwip/src/core/inet_chksum.src Libraries/Ethernet/lwip/src/core/init.d Libraries/Ethernet/lwip/src/core/init.o Libraries/Ethernet/lwip/src/core/init.src Libraries/Ethernet/lwip/src/core/ip.d Libraries/Ethernet/lwip/src/core/ip.o Libraries/Ethernet/lwip/src/core/ip.src Libraries/Ethernet/lwip/src/core/mem.d Libraries/Ethernet/lwip/src/core/mem.o Libraries/Ethernet/lwip/src/core/mem.src Libraries/Ethernet/lwip/src/core/memp.d Libraries/Ethernet/lwip/src/core/memp.o Libraries/Ethernet/lwip/src/core/memp.src Libraries/Ethernet/lwip/src/core/netif.d Libraries/Ethernet/lwip/src/core/netif.o Libraries/Ethernet/lwip/src/core/netif.src Libraries/Ethernet/lwip/src/core/pbuf.d Libraries/Ethernet/lwip/src/core/pbuf.o Libraries/Ethernet/lwip/src/core/pbuf.src Libraries/Ethernet/lwip/src/core/raw.d Libraries/Ethernet/lwip/src/core/raw.o Libraries/Ethernet/lwip/src/core/raw.src Libraries/Ethernet/lwip/src/core/stats.d Libraries/Ethernet/lwip/src/core/stats.o Libraries/Ethernet/lwip/src/core/stats.src Libraries/Ethernet/lwip/src/core/sys.d Libraries/Ethernet/lwip/src/core/sys.o Libraries/Ethernet/lwip/src/core/sys.src Libraries/Ethernet/lwip/src/core/tcp.d Libraries/Ethernet/lwip/src/core/tcp.o Libraries/Ethernet/lwip/src/core/tcp.src Libraries/Ethernet/lwip/src/core/tcp_in.d Libraries/Ethernet/lwip/src/core/tcp_in.o Libraries/Ethernet/lwip/src/core/tcp_in.src Libraries/Ethernet/lwip/src/core/tcp_out.d Libraries/Ethernet/lwip/src/core/tcp_out.o Libraries/Ethernet/lwip/src/core/tcp_out.src Libraries/Ethernet/lwip/src/core/timeouts.d Libraries/Ethernet/lwip/src/core/timeouts.o Libraries/Ethernet/lwip/src/core/timeouts.src Libraries/Ethernet/lwip/src/core/udp.d Libraries/Ethernet/lwip/src/core/udp.o Libraries/Ethernet/lwip/src/core/udp.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-core

