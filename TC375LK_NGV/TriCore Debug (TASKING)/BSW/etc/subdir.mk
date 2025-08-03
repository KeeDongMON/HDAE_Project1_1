################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/etc/etc.c \
../BSW/etc/my_stdio.c 

COMPILED_SRCS += \
BSW/etc/etc.src \
BSW/etc/my_stdio.src 

C_DEPS += \
BSW/etc/etc.d \
BSW/etc/my_stdio.d 

OBJS += \
BSW/etc/etc.o \
BSW/etc/my_stdio.o 


# Each subdirectory must supply rules for building sources it contributes
BSW/etc/etc.src: ../BSW/etc/etc.c BSW/etc/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/etc/etc.o: BSW/etc/etc.src BSW/etc/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
BSW/etc/my_stdio.src: ../BSW/etc/my_stdio.c BSW/etc/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/Documents/project/workspace2/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
BSW/etc/my_stdio.o: BSW/etc/my_stdio.src BSW/etc/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-BSW-2f-etc

clean-BSW-2f-etc:
	-$(RM) BSW/etc/etc.d BSW/etc/etc.o BSW/etc/etc.src BSW/etc/my_stdio.d BSW/etc/my_stdio.o BSW/etc/my_stdio.src

.PHONY: clean-BSW-2f-etc

