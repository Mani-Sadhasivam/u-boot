/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2018, Manivannan Sadhasivam <manivannanece23@gmail.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */

/*
 * Print Buffer Size
 */
#define CONFIG_SYS_PBSIZE	\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS	16

/*
 * Boot Argument Buffer Size
 */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

/*
 * Size of malloc() pool
 * 512kB is suggested, (CONFIG_ENV_SIZE + 128 * 1024) was not enough
 */
#define CONFIG_SYS_MALLOC_LEN   (512 << 10)

/* DT blob (fdt) address */
#define CONFIG_SYS_FDT_BASE	0x000f0000

#define CONFIG_SYS_SDRAM_BASE	0x80000000

/* Init Stack Pointer */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x1000000 - \
					GENERATED_GBL_DATA_SIZE)

/*
 * Load address and memory test area should agree with
 * arch/riscv/config.mk. Be careful not to overwrite U-Boot itself.
 */
#define CONFIG_SYS_LOAD_ADDR		0x80100000	/* SDRAM */

#define CONFIG_ENV_SIZE 0x2000

#endif /* __CONFIG_H */
