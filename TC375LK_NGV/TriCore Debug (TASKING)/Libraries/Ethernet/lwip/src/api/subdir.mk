################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Ethernet/lwip/src/api/api_lib.c \
../Libraries/Ethernet/lwip/src/api/api_msg.c \
../Libraries/Ethernet/lwip/src/api/err.c \
../Libraries/Ethernet/lwip/src/api/if_api.c \
../Libraries/Ethernet/lwip/src/api/netbuf.c \
../Libraries/Ethernet/lwip/src/api/netdb.c \
../Libraries/Ethernet/lwip/src/api/netifapi.c \
../Libraries/Ethernet/lwip/src/api/sockets.c \
../Libraries/Ethernet/lwip/src/api/tcpip.c 

COMPILED_SRCS += \
Libraries/Ethernet/lwip/src/api/api_lib.src \
Libraries/Ethernet/lwip/src/api/api_msg.src \
Libraries/Ethernet/lwip/src/api/err.src \
Libraries/Ethernet/lwip/src/api/if_api.src \
Libraries/Ethernet/lwip/src/api/netbuf.src \
Libraries/Ethernet/lwip/src/api/netdb.src \
Libraries/Ethernet/lwip/src/api/netifapi.src \
Libraries/Ethernet/lwip/src/api/sockets.src \
Libraries/Ethernet/lwip/src/api/tcpip.src 

C_DEPS += \
Libraries/Ethernet/lwip/src/api/api_lib.d \
Libraries/Ethernet/lwip/src/api/api_msg.d \
Libraries/Ethernet/lwip/src/api/err.d \
Libraries/Ethernet/lwip/src/api/if_api.d \
Libraries/Ethernet/lwip/src/api/netbuf.d \
Libraries/Ethernet/lwip/src/api/netdb.d \
Libraries/Ethernet/lwip/src/api/netifapi.d \
Libraries/Ethernet/lwip/src/api/sockets.d \
Libraries/Ethernet/lwip/src/api/tcpip.d 

OBJS += \
Libraries/Ethernet/lwip/src/api/api_lib.o \
Libraries/Ethernet/lwip/src/api/api_msg.o \
Libraries/Ethernet/lwip/src/api/err.o \
Libraries/Ethernet/lwip/src/api/if_api.o \
Libraries/Ethernet/lwip/src/api/netbuf.o \
Libraries/Ethernet/lwip/src/api/netdb.o \
Libraries/Ethernet/lwip/src/api/netifapi.o \
Libraries/Ethernet/lwip/src/api/sockets.o \
Libraries/Ethernet/lwip/src/api/tcpip.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Ethernet/lwip/src/api/api_lib.src: ../Libraries/Ethernet/lwip/src/api/api_lib.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/api_lib.o: Libraries/Ethernet/lwip/src/api/api_lib.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/api_msg.src: ../Libraries/Ethernet/lwip/src/api/api_msg.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/api_msg.o: Libraries/Ethernet/lwip/src/api/api_msg.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/err.src: ../Libraries/Ethernet/lwip/src/api/err.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/err.o: Libraries/Ethernet/lwip/src/api/err.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/if_api.src: ../Libraries/Ethernet/lwip/src/api/if_api.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/if_api.o: Libraries/Ethernet/lwip/src/api/if_api.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/netbuf.src: ../Libraries/Ethernet/lwip/src/api/netbuf.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/netbuf.o: Libraries/Ethernet/lwip/src/api/netbuf.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/netdb.src: ../Libraries/Ethernet/lwip/src/api/netdb.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/netdb.o: Libraries/Ethernet/lwip/src/api/netdb.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/netifapi.src: ../Libraries/Ethernet/lwip/src/api/netifapi.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/netifapi.o: Libraries/Ethernet/lwip/src/api/netifapi.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/sockets.src: ../Libraries/Ethernet/lwip/src/api/sockets.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/sockets.o: Libraries/Ethernet/lwip/src/api/sockets.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/api/tcpip.src: ../Libraries/Ethernet/lwip/src/api/tcpip.c Libraries/Ethernet/lwip/src/api/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/api/tcpip.o: Libraries/Ethernet/lwip/src/api/tcpip.src Libraries/Ethernet/lwip/src/api/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-api

clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-api:
	-$(RM) Libraries/Ethernet/lwip/src/api/api_lib.d Libraries/Ethernet/lwip/src/api/api_lib.o Libraries/Ethernet/lwip/src/api/api_lib.src Libraries/Ethernet/lwip/src/api/api_msg.d Libraries/Ethernet/lwip/src/api/api_msg.o Libraries/Ethernet/lwip/src/api/api_msg.src Libraries/Ethernet/lwip/src/api/err.d Libraries/Ethernet/lwip/src/api/err.o Libraries/Ethernet/lwip/src/api/err.src Libraries/Ethernet/lwip/src/api/if_api.d Libraries/Ethernet/lwip/src/api/if_api.o Libraries/Ethernet/lwip/src/api/if_api.src Libraries/Ethernet/lwip/src/api/netbuf.d Libraries/Ethernet/lwip/src/api/netbuf.o Libraries/Ethernet/lwip/src/api/netbuf.src Libraries/Ethernet/lwip/src/api/netdb.d Libraries/Ethernet/lwip/src/api/netdb.o Libraries/Ethernet/lwip/src/api/netdb.src Libraries/Ethernet/lwip/src/api/netifapi.d Libraries/Ethernet/lwip/src/api/netifapi.o Libraries/Ethernet/lwip/src/api/netifapi.src Libraries/Ethernet/lwip/src/api/sockets.d Libraries/Ethernet/lwip/src/api/sockets.o Libraries/Ethernet/lwip/src/api/sockets.src Libraries/Ethernet/lwip/src/api/tcpip.d Libraries/Ethernet/lwip/src/api/tcpip.o Libraries/Ethernet/lwip/src/api/tcpip.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-api

