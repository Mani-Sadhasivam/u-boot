/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2015 Linaro
 *
 * Peter Griffin <peter.griffin@linaro.org>
 *
 * Configuration for HiKey 96boards CE. Parts were derived from other ARM
 * configurations.
 */

#ifndef __HIKEY_H
#define __HIKEY_H

#include <linux/sizes.h>

#define CONFIG_SYS_BOOTM_LEN		SZ_64M

/* Physical Memory Map */

/* CONFIG_SYS_TEXT_BASE needs to align with where ATF loads bl33.bin */

#define PHYS_SDRAM_1			0x00000000
#define PHYS_SDRAM_1_SIZE		0xC0000000

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

#define CONFIG_SYS_INIT_RAM_SIZE	0x1000

#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + 0x7fff0)

#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x80000)

/* Generic Timer Definitions */
#define COUNTER_FREQUENCY		19000000

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			0xe82b1000
#define GICC_BASE			0xe82b2000

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + SZ_8M)

#define CONFIG_ENV_SIZE			0x1000

#endif /* __HIKEY_H */
