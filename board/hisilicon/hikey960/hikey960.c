// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2015 Linaro
 * Peter Griffin <peter.griffin@linaro.org>
 */
#include <common.h>
#include <dm.h>
#include <dm/platform_data/serial_pl01x.h>
#include <errno.h>
#include <malloc.h>
#include <netdev.h>
#include <asm/io.h>
#include <asm/arch/hi3660.h>
#include <asm/armv8/mmu.h>
#include <asm/psci.h>

DECLARE_GLOBAL_DATA_PTR;

#if !CONFIG_IS_ENABLED(OF_CONTROL)

static const struct pl01x_serial_platdata serial_platdata = {
#if CONFIG_CONS_INDEX == 7
	.base = HI3660_UART6_BASE,
#else
#error "Unsupported console index value."
#endif
	.type = TYPE_PL011,
	.clock = 19200000
};

U_BOOT_DEVICE(hikey960_seriala) = {
	.name = "serial_pl01x",
	.platdata = &serial_platdata,
};
#endif

static struct mm_region hikey_mem_map[] = {
	{
		.virt = 0x0UL, /* DDR */
		.phys = 0x0UL,
		.size = 0xC0000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		.virt = 0xE0000000UL, /* Peripheral block */
		.phys = 0xE0000000UL,
		.size = 0x20000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = hikey_mem_map;


int board_early_init_f(void)
{
	return 0;
}

int misc_init_r(void)
{
	return 0;
}

int board_init(void)
{
	return 0;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;

	return 0;
}

int dram_init_banksize(void)
{
	/*
	 * Reserve regions below from DT memory node (which gets generated
	 * by U-Boot from the dram banks in arch_fixup_fdt() before booting
	 * the kernel. This will then match the kernel hikey dts memory node.
	 *
	 *  0x05e0,0000 - 0x05ef,ffff: MCU firmware runtime using
	 *  0x05f0,1000 - 0x05f0,1fff: Reboot reason
	 *  0x06df,f000 - 0x06df,ffff: Mailbox message data
	 *  0x0740,f000 - 0x0740,ffff: MCU firmware section
	 *  0x21f0,0000 - 0x21ff,ffff: pstore/ramoops buffer
	 *  0x3e00,0000 - 0x3fff,ffff: OP-TEE
	*/

	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = 0xc0000000;

	gd->bd->bi_dram[1].start = 0x1ac00000;
	gd->bd->bi_dram[1].size = 0x00098000;

	gd->bd->bi_dram[2].start = 0xc0000000;
	gd->bd->bi_dram[2].size = 0x20000000;

	gd->bd->bi_dram[3].start = 0x32000000;
	gd->bd->bi_dram[3].size = 0x00100000;

	gd->bd->bi_dram[4].start = 0x32100000;
	gd->bd->bi_dram[4].size = 0x00001000;

	gd->bd->bi_dram[5].start = 0x3e000000;
	gd->bd->bi_dram[5].size = 0x02000000;

	gd->bd->bi_dram[6].start = 0x89B80000;
	gd->bd->bi_dram[6].size = 0x00100000;

	gd->bd->bi_dram[7].start = 0x89C80000;
	gd->bd->bi_dram[7].size = 0x00040000;

	gd->bd->bi_dram[8].start = 0x200000000;
	gd->bd->bi_dram[8].size = 0x20000000;

	return 0;
}

void reset_cpu(ulong addr)
{
	psci_system_reset();
}
