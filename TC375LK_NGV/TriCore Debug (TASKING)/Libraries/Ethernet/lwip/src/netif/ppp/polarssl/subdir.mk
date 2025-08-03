################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.c \
../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.c \
../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.c \
../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.c \
../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.c 

COMPILED_SRCS += \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.src \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.src \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.src \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.src \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.src 

C_DEPS += \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.d \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.d \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.d \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.d \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.d 

OBJS += \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.o \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.o \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.o \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.o \
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.src: ../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.c Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.o: Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.src: ../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.c Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.o: Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.src: ../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.c Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.o: Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.src: ../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.c Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.o: Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.src: ../Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.c Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.o: Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-netif-2f-ppp-2f-polarssl

clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-netif-2f-ppp-2f-polarssl:
	-$(RM) Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.d Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.o Libraries/Ethernet/lwip/src/netif/ppp/polarssl/arc4.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.d Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.o Libraries/Ethernet/lwip/src/netif/ppp/polarssl/des.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.d Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.o Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md4.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.d Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.o Libraries/Ethernet/lwip/src/netif/ppp/polarssl/md5.src Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.d Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.o Libraries/Ethernet/lwip/src/netif/ppp/polarssl/sha1.src

.PHONY: clean-Libraries-2f-Ethernet-2f-lwip-2f-src-2f-netif-2f-ppp-2f-polarssl

