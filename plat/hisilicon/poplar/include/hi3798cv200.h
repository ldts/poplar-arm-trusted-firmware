/*
 * Copyright (c) 2014-2015, Linaro Ltd and Contributors. All rights reserved.
 * Copyright (c) 2014-2015, Hisilicon Ltd and Contributors. All rights reserved.
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

#ifndef __HI3798cv200_H__
#define __HI3798cv200_H__

/* PL011 */
#define PL011_UART0_BASE		(0xf8b00000)
#define PL011_BAUDRATE			(115200)
#define PL011_UART0_CLK_IN_HZ		(75000000)

/*
 * SYS COUNTER
 */
#define SYS_COUNTER_FREQ_IN_TICKS	(24000000)
#define SYS_COUNTER_FREQ_IN_MHZ		(24)

/* Timer */
#define SEC_TIMER0_BASE			(0xf8008000)
#define TIMER00_LOAD			(SEC_TIMER0_BASE + 0x000)
#define TIMER00_VALUE			(SEC_TIMER0_BASE + 0x004)
#define TIMER00_CONTROL			(SEC_TIMER0_BASE + 0x008)
#define TIMER00_BGLOAD			(SEC_TIMER0_BASE + 0x018)

#define SEC_TIMER2_BASE			(0xf8009000)
#define TIMER20_LOAD			(SEC_TIMER2_BASE + 0x000)
#define TIMER20_VALUE			(SEC_TIMER2_BASE + 0x004)
#define TIMER20_CONTROL			(SEC_TIMER2_BASE + 0x008)
#define TIMER20_BGLOAD			(SEC_TIMER2_BASE + 0x018)

/* GPIO */
#define	GPIO_MAX			(12)
#define GPIO_BASE(x)			( x != 5 ? 			\
					0xf820000 + x * 0x1000 :	\
					0xf8004000 )

/* SCTL */
#define REG_BASE_SCTL                   (0xF8000000)
#define REG_SC_GEN12                    (0x00B0)

/* CRG */
#define REG_BASE_CRG			(0xF8A22000)
#define REG_PERI_CRG39			(0x9C)
#define REG_PERI_CRG40			(0xA0)

/* MCI */
#define REG_BASE_MCI			(0xF9830000)
#define MCI_CDETECT			(0x50)
#define MCI_VERID			(0x6C)
#define MCI_VERID_VALUE			(0x5342250A)
#define MCI_VERID_VALUE2		(0x5342270A)

/*
 * EMMC
 */
#define REG_EMMC_PERI_CRG		REG_PERI_CRG40
#define REG_SDCARD_PERI_CRG		REG_PERI_CRG39
#define EMMC_CLK_MASK			(0x7 << 8)
#define EMMC_SRST_REQ			(0x1 << 4)
#define EMMC_CKEN			(0x1 << 1)
#define EMMC_BUS_CKEN			(0x1 << 0)
#define EMMC_CLK_100M			(0 << 8)
#define EMMC_CLK_50M			(1 << 8)
#define EMMC_CLK_25M			(2 << 8)

#define EMMC_DESC_SIZE			(0xF0000)
#define EMMC_INIT_PARAMS(base) 				\
	{	.bus_width = EMMC_BUS_WIDTH_8,		\
		.clk_rate = 25 * 1000 * 1000,		\
		.desc_base = (base) - EMMC_DESC_SIZE,	\
		.desc_size = EMMC_DESC_SIZE,		\
		.flags =  EMMC_FLAG_CMD23,		\
		.reg_base = REG_BASE_MCI,		\
	}

/*******************************************************************************
 * GIC-400 & interrupt handling related constants
 ******************************************************************************/
#define BASE_GICD_BASE		(0xf1001000)
#define BASE_GICC_BASE		(0xf1002000)
#define BASE_GICR_BASE		(0xf1000000)

/* FIQ platform related define */
#define HISI_IRQ_SEC_SGI_0		8

#define HISI_IRQ_SEC_SGI_1		9
#define HISI_IRQ_SEC_SGI_2		10
#define HISI_IRQ_SEC_SGI_3		11
#define HISI_IRQ_SEC_SGI_4		12
#define HISI_IRQ_SEC_SGI_5		13
#define HISI_IRQ_SEC_SGI_6		14
#define HISI_IRQ_SEC_SGI_7		15

#define HISI_IRQ_SEC_PPI_0		29

#define HISI_IRQ_SEC_TIMER0		60
#define HISI_IRQ_SEC_TIMER1		50
#define HISI_IRQ_SEC_TIMER2		52
#define HISI_IRQ_SEC_TIMER3		88
#define HISI_IRQ_SEC_AXI		110

/*******************************************************************************
 * WDG related constants
 ******************************************************************************/
#define HISI_WDG0_BASE 			0xF8A2C000

#define HISI_PRIMARY_CPU		0x0

#endif	/* __HI3798cv200_H__ */
