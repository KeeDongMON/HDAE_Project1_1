/**********************************************************************************************************************
 * \file Lcf_Tasking_Tricore_Tc.lsl
 * \brief Linker command file for Tasking compiler.
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
 
#define LCF_CSA0_SIZE 8k
#define LCF_USTACK0_SIZE 2k
#define LCF_ISTACK0_SIZE 1k

#define LCF_HEAP_SIZE  4k

#define LCF_CPU0 0

#define LCF_DSPR0_START 0x70000000
#define LCF_DSPR0_SIZE  240k

#define LCF_CSA0_OFFSET     (LCF_DSPR0_SIZE - 1k - LCF_CSA0_SIZE)
#define LCF_ISTACK0_OFFSET  (LCF_CSA0_OFFSET - 256 - LCF_ISTACK0_SIZE)
#define LCF_USTACK0_OFFSET  (LCF_ISTACK0_OFFSET - 256 - LCF_USTACK0_SIZE)

#define LCF_HEAP0_OFFSET    (LCF_USTACK0_OFFSET - LCF_HEAP_SIZE)

#define LCF_INTVEC0_START 0x802FE000

#define LCF_TRAPVEC0_START 0x80000100

#define LCF_STARTPTR_CPU0 0x80000000

#define LCF_STARTPTR_NC_CPU0 0xA0000000

#define INTTAB0             (LCF_INTVEC0_START)
#define TRAPTAB0            (LCF_TRAPVEC0_START)

#define RESET LCF_STARTPTR_CPU0

#include "tc1v1_6_2.lsl"

// Specify a multi-core processor environment (mpe)
processor mpe
{
    derivative = tc37;
}

derivative tc37
{
    core tc0
    {
        architecture = TC1V1.6.2;
        space_id_offset = 100;            // add 100 to all space IDs in the architecture definition
        copytable_space = vtc:linear;     // use the copy table in the virtual core for 'bss' and initialized data sections
    }
    
    core vtc
    {
        architecture = TC1V1.6.2;
        import tc0;                     // add all address spaces of core tc0 to core vtc for linking and locating
    }

    bus sri
    {
        mau = 8;                        // (Minimal Addressable Units, 8Bit = 1 Byte)
        width = 32;                     // there are 32 data lines on the bus
        
        map (dest=bus:tc0:fpi_bus, src_offset=0, dest_offset=0, size=0xc0000000);
        map (dest=bus:vtc:fpi_bus, src_offset=0, dest_offset=0, size=0xc0000000);
    }

    memory dsram0 // Data Scratch Pad Ram
    {
        mau = 8;
        size = 240k;
        type = ram;
        map (dest=bus:tc0:fpi_bus, dest_offset=0xd0000000, size=240k, priority=8);
        map (dest=bus:sri, dest_offset=0x70000000, size=240k);
    }
    
    memory psram0 // Program Scratch Pad Ram
    {
        mau = 8;
        size = 64k;
        type = ram;
        map (dest=bus:tc0:fpi_bus, dest_offset=0xc0000000, size=64k, priority=8);
        map (dest=bus:sri, dest_offset=0x70100000, size=64k);
    }
    
    memory pfls0
    {
        mau = 8;
        size = 3M;
        type = rom;
        map     cached (dest=bus:sri, dest_offset=0x80000000,           size=3M);
        map not_cached (dest=bus:sri, dest_offset=0xa0000000, reserved, size=3M);
    }
    
    memory dfls0
    {
        mau = 8;
        size = 256K;
        type = reserved nvram;
        map (dest=bus:sri, dest_offset=0xaf000000, size=256K);
    }
    
    memory ucb
    {
        mau = 8;
        size = 24k;
        type = rom;
        map (dest=bus:sri, dest_offset=0xaf400000, reserved, size=24k);
    }
    
    memory cpu0_dlmu
    {
        mau = 8;
        size = 64k;
        type = ram;
        map     cached (dest=bus:sri, dest_offset=0x90000000,           size=64k);
        map not_cached (dest=bus:sri, dest_offset=0xb0000000, reserved, size=64k);
    }
  
    section_setup :vtc:linear
    {
        start_address
        (
            symbol = "_START"
        );
        
        stack "ustack_tc0" (min_size = 1k, fixed, align = 8);
        stack "istack_tc0" (min_size = 1k, fixed, align = 8);
        
        copytable
        (
            align = 4,
            dest = linear,
            table
            {
                symbol = "_lc_ub_table_tc0";
                space = :tc0:linear, :tc0:abs24, :tc0:abs18, :tc0:csa;
            }
        );
    }

    /*Sections located at absolute fixed address*/
    section_layout :vtc:linear
    {
        group (ordered)
        {
            /*Fixed memory Allocations for stack memory and CSA*/
            group ustack0(align = 8, run_addr = mem:dsram0[LCF_USTACK0_OFFSET])
            {
                stack "ustack_tc0" (size = LCF_USTACK0_SIZE);
            }
            "__USTACK0":= sizeof(group:ustack0) > 0  ? "_lc_ue_ustack_tc0" : 0;
            "__USTACK0_END"="_lc_gb_ustack0";
            
            group istack0(align = 8, run_addr = mem:dsram0[LCF_ISTACK0_OFFSET])
            {
                stack "istack_tc0" (size = LCF_ISTACK0_SIZE);
            }
            "__ISTACK0":= sizeof(group:istack0) > 0  ? "_lc_ue_istack_tc0" : 0;
            "__ISTACK0_END"="_lc_gb_istack0";
            
            group (align = 64, attributes=rw, run_addr=mem:dsram0[LCF_CSA0_OFFSET]) 
                reserved "csa_tc0" (size = LCF_CSA0_SIZE);
            "__CSA0":=        "_lc_ub_csa_tc0";
            "__CSA0_END":=    "_lc_ue_csa_tc0";
        }
        
        group (ordered)
        {
            /*Fixed memory Allocations for _START*/
            group  reset (run_addr=RESET)
            {
                section "reset" ( size = 0x20, fill = 0x0800, attributes = r )
                {
                    select ".text.start";
                }
            }
            group  interface_const (run_addr=mem:pfls0[0x0020])
            {
                select "*.interface_const";
            }
            "__IF_CONST" := addressof(group:interface_const);
            "__START0" := LCF_STARTPTR_NC_CPU0;
        
            /*Fixed memory Allocations for Trap Vector Table*/
            group trapvec_tc0 (align = 8, run_addr=LCF_TRAPVEC0_START)
            {
                section "trapvec_tc0" (size=0x100, attributes=rx, fill=0)
                {
                    select "(.text.traptab_cpu0*)";
                }
            }
            "__TRAPTAB_CPU0" := TRAPTAB0;
        
            /*Fixed memory Allocations for Start up code*/
            group start_tc0 (run_addr=LCF_STARTPTR_NC_CPU0)
            {
                select "(.text.start_cpu0*)";
            }
            "__ENABLE_INDIVIDUAL_C_INIT_CPU0" := 0; /* Not used */
        
            /*Fixed memory Allocations for Interrupt Vector Table*/
            group int_tab_tc0 (ordered)
            {
#                include "inttab0.lsl"
            }
            "_lc_u_int_tab" = (LCF_INTVEC0_START);
            "__INTTAB_CPU0" = (LCF_INTVEC0_START);
        }
    }
        
    /*Near Abbsolute Addressable Data Sections*/
    section_layout :vtc:abs18
    {
        /*Near Absolute Data, selectable by toolchain*/
        group (ordered, contiguous, align = 4, attributes=rw, run_addr = mem:dsram0)
        {
            group zdata(attributes=rw)
            {
                select "(.zdata|.zdata.*)";
                select "(.zbss|.zbss.*)";
            }
        }
        
        /*Near Absolute Const, selectable with patterns and user defined sections*/
        group
        {
            group (ordered, align = 4, contiguous, run_addr=mem:pfls0)
            {
                select "(.zrodata|.zrodata.*)";
            }
        }
    }
        
    /*Far Data / Far Const Sections, selectable with patterns and user defined sections*/
    section_layout :vtc:linear
    {       
        /*Far Data Sections, selectable by toolchain*/
        group data (ordered, contiguous, align = 4, attributes=rw, run_addr = mem:dsram0)
        {
            select "(.data|.data.*)";
        }
        group bss (ordered, contiguous, align = 4, attributes=rw, run_addr = mem:dsram0)
        {
            select "(.bss|.bss.*)";
        }
        
        /*Heap allocation*/
        group (ordered, align = 4, run_addr = mem:dsram0[LCF_HEAP0_OFFSET])
        {
            heap "heap" (size = LCF_HEAP_SIZE);
        }
        
        /*Far Const Sections, selectable by toolchain*/
        group rodata (ordered, align = 4, run_addr=mem:pfls0)
        {
            select "(.rodata|.rodata.*)";
        }

        group code_psram0 (ordered, attributes=rwx, copy, run_addr=mem:psram0)
        {
            select "(.text.cpu0_psram|.text.cpu0_psram.*)";
        }

        /*Code Sections, selectable by toolchain*/
        group text (ordered, run_addr=mem:pfls0)
        {
            select "(.text|.text.*)";
        }
    }
    
    /*Relative A0/A1/A8/A9 Addressable Sections*/
    section_layout :vtc:linear
    {
        /*Relative A0 Addressable Data, selectable by toolchain*/
        group a0 (ordered, contiguous, align = 4, attributes=rw, run_addr = mem:dsram0)
        {
            select "(.data_a0.sdata|.data_a0.sdata.*)";
            select "(.bss_a0.sbss|.bss_a0.sbss.*)";
        }
        "_SMALL_DATA_" := sizeof(group:a0) > 0 ? addressof(group:a0) : addressof(group:a0) & 0xF0000000 + 32k;
        "__A0_MEM" = "_SMALL_DATA_";
        
        /*Relative A1 Addressable Const, selectable by toolchain*/
        /*Small constant sections, No option given for CPU specific user sections to make generated code portable across Cpus*/
        group  a1 (ordered, align = 4, run_addr=mem:pfls0)
        {
            select "(.rodata_a1.srodata|.rodata_a1.srodata.*)";
            select "(.ldata|.ldata.*)";
        }
        "_LITERAL_DATA_" := sizeof(group:a1) > 0 ? addressof(group:a1) : addressof(group:a1) & 0xF0000000 + 32k;
        "__A1_MEM" = "_LITERAL_DATA_";
        
        /*Relative A9 Addressable Data, selectable with patterns and user defined sections*/
        group a9 (ordered, align = 4, run_addr=mem:cpu0_dlmu)
        {
            select "(.data_a9.a9sdata|.data_a9.a9sdata.*)";
            select "(.bss_a9.a9sbss|.bss_a9.a9sbss.*)";
        }
        "_A9_DATA_" := sizeof(group:a9) > 0 ? addressof(group:a9) : addressof(group:a9) & 0xF0000000 + 32k;
        "__A9_MEM" = "_A9_DATA_";

        /*Relative A8 Addressable Const, selectable with patterns and user defined sections*/
        group  a8 (ordered, align = 4, run_addr=mem:pfls0)
        {
            select "(.rodata_a8.a8srodata|.rodata_a8.a8srodata.*)";
        }
        "_A8_DATA_" := sizeof(group:a8) > 0 ? addressof(group:a8) : addressof(group:a8) & 0xF0000000 + 32k;
        "__A8_MEM" = "_A8_DATA_";
    }
}
