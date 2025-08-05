################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Emergency_stop.c \
../Modules/LightButton.c \
../Modules/UltraBuzzer.c 

COMPILED_SRCS += \
Modules/Emergency_stop.src \
Modules/LightButton.src \
Modules/UltraBuzzer.src 

C_DEPS += \
Modules/Emergency_stop.d \
Modules/LightButton.d \
Modules/UltraBuzzer.d 

OBJS += \
Modules/Emergency_stop.o \
Modules/LightButton.o \
Modules/UltraBuzzer.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/Emergency_stop.src: ../Modules/Emergency_stop.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/Emergency_stop.o: Modules/Emergency_stop.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/LightButton.src: ../Modules/LightButton.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/LightButton.o: Modules/LightButton.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
Modules/UltraBuzzer.src: ../Modules/UltraBuzzer.c Modules/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Modules/UltraBuzzer.o: Modules/UltraBuzzer.src Modules/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Modules

clean-Modules:
	-$(RM) Modules/Emergency_stop.d Modules/Emergency_stop.o Modules/Emergency_stop.src Modules/LightButton.d Modules/LightButton.o Modules/LightButton.src Modules/UltraBuzzer.d Modules/UltraBuzzer.o Modules/UltraBuzzer.src

.PHONY: clean-Modules

