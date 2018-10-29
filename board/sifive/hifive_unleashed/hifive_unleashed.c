// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018, Manivannan Sadhasivam <manivannanece23@gmail.com>
 */

#include <common.h>
#include <linux/io.h>
#include <fdtdec.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Miscellaneous platform dependent initializations
 */

int board_init(void)
{
	return 0;
}

int dram_init(void)
{
	gd->ram_size = CONFIG_SYS_SDRAM_SIZE;

	return 0;
}

int dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size = gd->ram_size;

	return 0;
}
