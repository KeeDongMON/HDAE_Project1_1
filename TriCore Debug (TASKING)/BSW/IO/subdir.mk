################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/IO/Bluetooth.c \
../BSW/IO/Buzzer.c \
../BSW/IO/Motor.c \
../BSW/IO/gpio.c \
../BSW/IO/ultrasonic.c 

COMPILED_SRCS += \
BSW/IO/Bluetooth.src \
BSW/IO/Buzzer.src \
BSW/IO/Motor.src \
BSW/IO/gpio.src \
BSW/IO/ultrasonic.src 

C_DEPS += \
BSW/IO/Bluetooth.d \
BSW/IO/Buzzer.d \
BSW/IO/Motor.d \
BSW/IO/gpio.d \
BSW/IO/ultrasonic.d 

OBJS += \
BSW/IO/Bluetooth.o \
BSW/IO/Buzzer.o \
BSW/IO/Motor.o \
BSW/IO/gpio.o \
BSW/IO/ultrasonic.o 


# Each subdirectory must supply rules for building sources it contributes
BSW/IO/Bluetooth.src: ../BSW/IO/Bluetooth.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/myprj/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O1 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Bluetooth.o: BSW/IO/Bluetooth.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/Buzzer.src: ../BSW/IO/Buzzer.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/myprj/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O1 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Buzzer.o: BSW/IO/Buzzer.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/Motor.src: ../BSW/IO/Motor.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/myprj/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O1 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Motor.o: BSW/IO/Motor.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/gpio.src: ../BSW/IO/gpio.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/myprj/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O1 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/gpio.o: BSW/IO/gpio.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/ultrasonic.src: ../BSW/IO/ultrasonic.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/myprj/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O1 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/ultrasonic.o: BSW/IO/ultrasonic.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-BSW-2f-IO

clean-BSW-2f-IO:
	-$(RM) BSW/IO/Bluetooth.d BSW/IO/Bluetooth.o BSW/IO/Bluetooth.src BSW/IO/Buzzer.d BSW/IO/Buzzer.o BSW/IO/Buzzer.src BSW/IO/Motor.d BSW/IO/Motor.o BSW/IO/Motor.src BSW/IO/gpio.d BSW/IO/gpio.o BSW/IO/gpio.src BSW/IO/ultrasonic.d BSW/IO/ultrasonic.o BSW/IO/ultrasonic.src

.PHONY: clean-BSW-2f-IO

