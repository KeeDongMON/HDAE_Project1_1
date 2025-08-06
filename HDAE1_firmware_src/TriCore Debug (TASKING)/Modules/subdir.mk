################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Drive.c \
../Modules/Emergency_stop.c \
../Modules/Headlight.c \
../Modules/LightButton.c \
../Modules/UltraBuzzer.c \
../Modules/auto_parking.c 

COMPILED_SRCS += \
Modules/Drive.src \
Modules/Emergency_stop.src \
Modules/Headlight.src \
Modules/LightButton.src \
Modules/UltraBuzzer.src \
Modules/auto_parking.src 

C_DEPS += \
Modules/Drive.d \
Modules/Emergency_stop.d \
Modules/Headlight.d \
Modules/LightButton.d \
Modules/UltraBuzzer.d \
Modules/auto_parking.d 

OBJS += \
Modules/Drive.o \
Modules/Emergency_stop.o \
Modules/Headlight.o \
Modules/LightButton.o \
Modules/UltraBuzzer.o \
Modules/auto_parking.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/Drive.src: ../Modules/Drive.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/Drive.o: Modules/Drive.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/Emergency_stop.src: ../Modules/Emergency_stop.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/Emergency_stop.o: Modules/Emergency_stop.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/Headlight.src: ../Modules/Headlight.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/Headlight.o: Modules/Headlight.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/LightButton.src: ../Modules/LightButton.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/LightButton.o: Modules/LightButton.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/UltraBuzzer.src: ../Modules/UltraBuzzer.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/UltraBuzzer.o: Modules/UltraBuzzer.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/auto_parking.src: ../Modules/auto_parking.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/HDAE1_firmware_src/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/auto_parking.o: Modules/auto_parking.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Modules

clean-Modules:
	-$(RM) Modules/Drive.d Modules/Drive.o Modules/Drive.src Modules/Emergency_stop.d Modules/Emergency_stop.o Modules/Emergency_stop.src Modules/Headlight.d Modules/Headlight.o Modules/Headlight.src Modules/LightButton.d Modules/LightButton.o Modules/LightButton.src Modules/UltraBuzzer.d Modules/UltraBuzzer.o Modules/UltraBuzzer.src Modules/auto_parking.d Modules/auto_parking.o Modules/auto_parking.src

.PHONY: clean-Modules

