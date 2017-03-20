/*
 * Copyright (c) 2017, Linaro Limited and Contributors. All rights reserved.
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

#include <arch.h>
#include <arch_helpers.h>
#include <arm_gic.h>
#include <assert.h>
#include <bl31.h>
#include <bl_common.h>
#include <console.h>
#include <cortex_a53.h>
#include <debug.h>
#include <errno.h>
#include <generic_delay_timer.h>
#include <hi3798cv200.h>
#include <mmio.h>
#include <platform_def.h>
#include <platform.h>
#include <plat_arm.h>
#include <plat_private.h>
#include <string.h>
#include <stddef.h>

unsigned long __RO_START__;
unsigned long __RO_END__;

unsigned long __COHERENT_RAM_START__;
unsigned long __COHERENT_RAM_END__;

/*
 * The next 2 constants identify the extents of the code & RO data region.
 * These addresses are used by the MMU setup code and therefore they must be
 * page-aligned.  It is the responsibility of the linker script to ensure that
 * __RO_START__ and __RO_END__ linker symbols refer to page-aligned addresses.
 */
#define BL31_RO_BASE (unsigned long)(&__RO_START__)
#define BL31_RO_LIMIT (unsigned long)(&__RO_END__)

/*
 * The next 2 constants identify the extents of the coherent memory region.
 * These addresses are used by the MMU setup code and therefore they must be
 * page-aligned.  It is the responsibility of the linker script to ensure that
 * __COHERENT_RAM_START__ and __COHERENT_RAM_END__ linker symbols
 * refer to page-aligned addresses.
 */
#define BL31_COHERENT_RAM_BASE (unsigned long)(&__COHERENT_RAM_START__)
#define BL31_COHERENT_RAM_LIMIT (unsigned long)(&__COHERENT_RAM_END__)

static entry_point_info_t bl33_image_ep_info;

/*******************************************************************************
 * This variable holds the non-secure image entry address
 ******************************************************************************/
extern uint64_t ns_image_entrypoint;

/*******************************************************************************
 * Return a pointer to the 'entry_point_info' structure of the next image for
 * security state specified. BL33 corresponds to the non-secure image type
 * while BL32 corresponds to the secure image type.
 ******************************************************************************/
entry_point_info_t *bl31_plat_get_next_image_ep_info(uint32_t type)
{
	return &bl33_image_ep_info;
}

/*******************************************************************************
 * Perform any BL31 specific platform actions. Populate the BL33 and BL32 image
 * info.
 ******************************************************************************/
void bl31_early_platform_setup(bl31_params_t *from_bl2, void *plat_params_from_bl2)
{
	console_init(PL011_UART0_BASE, PL011_UART0_CLK_IN_HZ, PL011_BAUDRATE);
	plat_crash_console_init();

	bl33_image_ep_info = *from_bl2->bl33_ep_info;
}

/*******************************************************************************
 * Initialize the gic, configure the SCR.
 ******************************************************************************/
void bl31_platform_setup(void)
{
	generic_delay_timer_init();
	plat_arm_gic_driver_init();
	plat_arm_gic_init();
}

void bl31_plat_runtime_setup(void)
{
}

/*******************************************************************************
 * Perform the very early platform specific architectural setup here. At the
 * moment this only intializes the mmu in a quick and dirty way.
 ******************************************************************************/
void bl31_plat_arch_setup(void)
{
	plat_configure_mmu_el3(BL31_RO_BASE,
			(BL31_COHERENT_RAM_LIMIT - BL31_RO_BASE),
			BL31_RO_BASE,
			BL31_RO_LIMIT,
			BL31_COHERENT_RAM_BASE,
			BL31_COHERENT_RAM_LIMIT);

	INFO("Boot bl33 from 0x%lx for %lu Bytes\n",
		bl33_image_ep_info.pc,
		bl33_image_ep_info.args.arg2);
}
