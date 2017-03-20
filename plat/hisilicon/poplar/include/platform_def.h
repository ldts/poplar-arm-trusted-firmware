/*
 * Copyright (c) 2017, Linaro Ltd and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <arch.h>
#include <hi3798cv200.h>

/*******************************************************************************
 * Platform binary types for linking
 ******************************************************************************/
#define PLATFORM_LINKER_FORMAT          "elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH            aarch64

#define PLAT_ARM_CRASH_UART_BASE	PL011_UART0_BASE
#define PLAT_ARM_CRASH_UART_CLK_IN_HZ	PL011_UART0_CLK_IN_HZ
#define ARM_CONSOLE_BAUDRATE		PL011_BAUDRATE

/*******************************************************************************
 * Generic platform constants
 ******************************************************************************/
#define PLATFORM_STACK_SIZE 		(0x800)

#define FIRMWARE_WELCOME_STR		"Booting Trusted Firmware\n"
#define BOOT_EMMC_NAME			"l-loader.bin"

#define PLATFORM_CACHE_LINE_SIZE	(64)
#define PLATFORM_CLUSTER_COUNT		(1)
#define PLATFORM_CORE_COUNT		(4)
#define PLATFORM_MAX_CPUS_PER_CLUSTER	(4)

/* io framework user */
#define MAX_IO_DEVICES			(4)
#define MAX_IO_HANDLES			(4)
#define MAX_IO_BLOCK_DEVICES		(2)

/*******************************************************************************
 * Platform memory map related constants
 ******************************************************************************/
#define DDR_BASE			(0x00000000)
#define DDR_SIZE			(0x40000000)

#define DEVICE_BASE			(0xF0000000)
#define DEVICE_SIZE			(0x0F000000)

#define TEE_SEC_MEM_BASE		(0x70000000)
#define TEE_SEC_MEM_SIZE		(0x10000000)


#define LLOADER_TEXT_BASE		(0x00001000)
#define LLOADER_FIP_BASE		(0x0000E000)
#define LLOADER_FIP_SIZE		(0x000C0000)

#define BL_MEM_BASE			(LLOADER_FIP_BASE + LLOADER_FIP_SIZE)
#define BL_MEM_SIZE			(0x00E00000)

#define BL1_RO_BASE			(BL_MEM_BASE)
#define BL1_RO_LIMIT			(0x000E1000)

#define BL1_RW_BASE			(BL1_RO_LIMIT)
#define BL1_RW_LIMIT			(BL1_RW_BASE + 0x00008000)

#define BL2_BASE			(BL1_RW_LIMIT)
#define BL2_LIMIT			(BL2_BASE + 0x00040000)

#define BL31_BASE                       (BL2_LIMIT)
#define BL31_LIMIT                      (BL_MEM_SIZE)

/*******************************************************************************
 * Platform specific page table and MMU setup constants
 ******************************************************************************/
#define ADDR_SPACE_SIZE			(1ull << 32)
#define MAX_XLAT_TABLES			(4)
#define MAX_MMAP_REGIONS		(16)

/*******************************************************************************
 * Declarations and constants to access the mailboxes safely. Each mailbox is
 * aligned on the biggest cache line size in the platform. This is known only
 * to the platform as it might have a combination of integrated and external
 * caches. Such alignment ensures that two maiboxes do not sit on the same cache
 * line at any cache level. They could belong to different cpus/clusters &
 * get written while being protected by different locks causing corruption of
 * a valid mailbox address.
 ******************************************************************************/
#define CACHE_WRITEBACK_SHIFT		(6)
#define CACHE_WRITEBACK_GRANULE		(1 << CACHE_WRITEBACK_SHIFT)

#define PLAT_MAX_PWR_LVL		(MPIDR_AFFLVL1)

/*******************************************************************************
 * Platform power states
 ******************************************************************************/
#define PLAT_MAX_OFF_STATE	2
#define PLAT_MAX_RET_STATE	1

#define PLAT_ARM_GICD_BASE	BASE_GICD_BASE
#define PLAT_ARM_GICC_BASE	BASE_GICC_BASE

#define PLAT_ARM_G1S_IRQS	HISI_IRQ_SEC_SGI_0,  \
				HISI_IRQ_SEC_SGI_1,  \
				HISI_IRQ_SEC_SGI_2,  \
				HISI_IRQ_SEC_SGI_3,  \
				HISI_IRQ_SEC_SGI_4,  \
				HISI_IRQ_SEC_SGI_5,  \
				HISI_IRQ_SEC_SGI_6,  \
				HISI_IRQ_SEC_SGI_7,  \
				HISI_IRQ_SEC_TIMER0, \
				HISI_IRQ_SEC_TIMER1, \
				HISI_IRQ_SEC_TIMER2, \
				HISI_IRQ_SEC_TIMER3, \
				HISI_IRQ_SEC_AXI

#define PLAT_ARM_G0_IRQS

#define PLAT_ARM_NS_IMAGE_OFFSET	0x37000000

#endif /* __PLATFORM_DEF_H__ */
