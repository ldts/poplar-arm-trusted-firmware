#
# Copyright (c) 2017, Linaro Ltd and Contributors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# Neither the name of ARM nor the names of its contributors may be used
# to endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

# Flag used by the HISI_platform port to determine the version of ARM GIC
# architecture to use for interrupt management in EL3.

ERRATA_A53_855873       := 1
NEED_BL33		:= yes

COLD_BOOT_SINGLE_CPU    := 1
ENABLE_PLAT_COMPAT      := 0
CTX_INCLUDE_FPREGS	:= 1

ARM_GIC_ARCH		:= 2
$(eval $(call add_define,ARM_GIC_ARCH))

PLAT_PL061_MAX_GPIOS 	:= 104
$(eval $(call add_define,PLAT_PL061_MAX_GPIOS))

PLAT_INCLUDES		:=	-Iinclude/plat/arm/common/		\
				-Iinclude/plat/arm/common/aarch64/	\
				-Iplat/hisilicon/poplar/include		\
				-Iplat/hisilicon/poplar			\
				-Iinclude/common/tbbr			\
				-Iinclude/drivers/io

PLAT_BL_COMMON_SOURCES	:=						\
		drivers/arm/pl011/pl011_console.S			\
		drivers/arm/gic/common/gic_common.c			\
		drivers/arm/gic/v2/gicv2_main.c				\
		drivers/arm/gic/v2/gicv2_helpers.c			\
		drivers/delay_timer/delay_timer.c			\
		drivers/delay_timer/generic_delay_timer.c		\
		lib/aarch64/xlat_tables.c				\
		plat/arm/common/arm_gicv2.c				\
		plat/arm/common/aarch64/arm_helpers.S			\
		plat/common/aarch64/plat_common.c			\
		plat/common/plat_gicv2.c				\
		plat/hisilicon/poplar/aarch64/platform_common.c

BL1_SOURCES	+=							\
		plat/common/aarch64/platform_up_stack.S			\
		drivers/arm/pl061/pl061_gpio.c				\
		lib/cpus/aarch64/cortex_a53.S				\
		drivers/io/io_storage.c					\
		drivers/io/io_block.c					\
		drivers/gpio/gpio.c					\
		drivers/io/io_fip.c					\
		drivers/io/io_memmap.c					\
		plat/hisilicon/poplar/aarch64/plat_helpers.S		\
		plat/hisilicon/poplar/plat_storage.c			\
		plat/hisilicon/poplar/bl1_plat_setup.c

BL2_SOURCES	+=      						\
		plat/common/aarch64/platform_up_stack.S			\
		drivers/arm/pl061/pl061_gpio.c				\
		drivers/io/io_storage.c					\
		drivers/io/io_block.c					\
		drivers/io/io_fip.c					\
		drivers/gpio/gpio.c					\
		drivers/io/io_memmap.c					\
		plat/hisilicon/poplar/plat_storage.c			\
		plat/hisilicon/poplar/bl2_plat_setup.c

BL31_SOURCES	+=					                \
		lib/cpus/aarch64/aem_generic.S				\
		lib/cpus/aarch64/cortex_a53.S				\
		plat/common/aarch64/platform_mp_stack.S			\
		plat/common/aarch64/plat_psci_common.c			\
		plat/hisilicon/poplar/bl31_plat_setup.c			\
		plat/hisilicon/poplar/aarch64/plat_helpers.S		\
		plat/hisilicon/poplar/plat_topology.c			\
		plat/hisilicon/poplar/plat_pm.c

