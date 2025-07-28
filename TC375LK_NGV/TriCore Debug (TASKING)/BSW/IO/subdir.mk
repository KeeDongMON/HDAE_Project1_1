################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/IO/Bluetooth.c \
../BSW/IO/Buzzer.c \
../BSW/IO/GPIO.c \
../BSW/IO/Motor.c \
../BSW/IO/ToF.c \
../BSW/IO/Ultrasonic.c 

COMPILED_SRCS += \
BSW/IO/Bluetooth.src \
BSW/IO/Buzzer.src \
BSW/IO/GPIO.src \
BSW/IO/Motor.src \
BSW/IO/ToF.src \
BSW/IO/Ultrasonic.src 

C_DEPS += \
BSW/IO/Bluetooth.d \
BSW/IO/Buzzer.d \
BSW/IO/GPIO.d \
BSW/IO/Motor.d \
BSW/IO/ToF.d \
BSW/IO/Ultrasonic.d 

OBJS += \
BSW/IO/Bluetooth.o \
BSW/IO/Buzzer.o \
BSW/IO/GPIO.o \
BSW/IO/Motor.o \
BSW/IO/ToF.o \
BSW/IO/Ultrasonic.o 


# Each subdirectory must supply rules for building sources it contributes
BSW/IO/Bluetooth.src: ../BSW/IO/Bluetooth.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Bluetooth.o: BSW/IO/Bluetooth.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/Buzzer.src: ../BSW/IO/Buzzer.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Buzzer.o: BSW/IO/Buzzer.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/GPIO.src: ../BSW/IO/GPIO.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/GPIO.o: BSW/IO/GPIO.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/Motor.src: ../BSW/IO/Motor.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Motor.o: BSW/IO/Motor.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/ToF.src: ../BSW/IO/ToF.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/ToF.o: BSW/IO/ToF.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/IO/Ultrasonic.src: ../BSW/IO/Ultrasonic.c BSW/IO/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/multi/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/IO/Ultrasonic.o: BSW/IO/Ultrasonic.src BSW/IO/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-BSW-2f-IO

clean-BSW-2f-IO:
	-$(RM) BSW/IO/Bluetooth.d BSW/IO/Bluetooth.o BSW/IO/Bluetooth.src BSW/IO/Buzzer.d BSW/IO/Buzzer.o BSW/IO/Buzzer.src BSW/IO/GPIO.d BSW/IO/GPIO.o BSW/IO/GPIO.src BSW/IO/Motor.d BSW/IO/Motor.o BSW/IO/Motor.src BSW/IO/ToF.d BSW/IO/ToF.o BSW/IO/ToF.src BSW/IO/Ultrasonic.d BSW/IO/Ultrasonic.o BSW/IO/Ultrasonic.src

.PHONY: clean-BSW-2f-IO

