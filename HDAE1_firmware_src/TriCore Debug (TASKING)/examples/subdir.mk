################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/DoIP.c \
../examples/can-ethernet.c \
../examples/someip.c \
../examples/tcp_echo.c \
../examples/udp_echo.c 

COMPILED_SRCS += \
examples/DoIP.src \
examples/can-ethernet.src \
examples/someip.src \
examples/tcp_echo.src \
examples/udp_echo.src 

C_DEPS += \
examples/DoIP.d \
examples/can-ethernet.d \
examples/someip.d \
examples/tcp_echo.d \
examples/udp_echo.d 

OBJS += \
examples/DoIP.o \
examples/can-ethernet.o \
examples/someip.o \
examples/tcp_echo.o \
examples/udp_echo.o 


# Each subdirectory must supply rules for building sources it contributes
examples/DoIP.src: ../examples/DoIP.c examples/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
examples/DoIP.o: examples/DoIP.src examples/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
examples/can-ethernet.src: ../examples/can-ethernet.c examples/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
examples/can-ethernet.o: examples/can-ethernet.src examples/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
examples/someip.src: ../examples/someip.c examples/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
examples/someip.o: examples/someip.src examples/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
examples/tcp_echo.src: ../examples/tcp_echo.c examples/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
examples/tcp_echo.o: examples/tcp_echo.src examples/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
examples/udp_echo.src: ../examples/udp_echo.c examples/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
examples/udp_echo.o: examples/udp_echo.src examples/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-examples

clean-examples:
	-$(RM) examples/DoIP.d examples/DoIP.o examples/DoIP.src examples/can-ethernet.d examples/can-ethernet.o examples/can-ethernet.src examples/someip.d examples/someip.o examples/someip.src examples/tcp_echo.d examples/tcp_echo.o examples/tcp_echo.src examples/udp_echo.d examples/udp_echo.o examples/udp_echo.src

.PHONY: clean-examples

