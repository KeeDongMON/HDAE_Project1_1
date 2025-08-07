################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.c 

COMPILED_SRCS += \
Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.src 

C_DEPS += \
Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.d 

OBJS += \
Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.src: ../Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.c Libraries/Ethernet/Phy_Dp83825i/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/USER/AURIX-v1.10.2-workspace/0729prj/TC375LK_NGV/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.o: Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.src Libraries/Ethernet/Phy_Dp83825i/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-Ethernet-2f-Phy_Dp83825i

clean-Libraries-2f-Ethernet-2f-Phy_Dp83825i:
	-$(RM) Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.d Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.o Libraries/Ethernet/Phy_Dp83825i/IfxGeth_Phy_Dp83825i.src

.PHONY: clean-Libraries-2f-Ethernet-2f-Phy_Dp83825i

