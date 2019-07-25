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

//delete
void hikey960_mmc_init(void);

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
	hikey960_mmc_init();
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

void hikey960_mmc_init(void)
{
	uint32_t data;

	data = readl(SCTRL_SCFPLLCTRL0);
	data |= SCTRL_SCFPLLCTRL0_FPLL0_EN;
	writel(data, SCTRL_SCFPLLCTRL0);	

	// LDO16
	data = readl(PMU_REG_BASE + (0x79 << 2)) & 7;
	data |= 6;
	writel(data, PMU_REG_BASE + (0x79 << 2));

	data = readl(PMU_REG_BASE + (0x78 << 2));
	data |= 2;
	writel(data, PMU_REG_BASE + (0x78 << 2));

	udelay(100);

  // LDO9
  data = readl(PMU_REG_BASE + (0x6b << 2)) & 7;
  data |= 5;
  writel(data, PMU_REG_BASE + (0x6b << 2));
	data = readl(PMU_REG_BASE + (0x6a << 2));
	data |= 2;
	writel(data, PMU_REG_BASE + (0x6a << 2));
	udelay(100);

  // GPIO203
  writel(0, 0xfff11000 + (24 << 2)); // GPIO function

  // SD pinmux
  writel(1, 0xff37e000 + 0x0); // SD_CLK
  writel(1, 0xff37e000 + 0x4); // SD_CMD
  writel(1, 0xff37e000 + 0x8); // SD_DATA0
  writel(1, 0xff37e000 + 0xc); // SD_DATA1
  writel(1, 0xff37e000 + 0x10); // SD_DATA2
  writel(1, 0xff37e000 + 0x14); // SD_DATA3
  writel(15 << 4, 0xff37e800 + 0x0); // SD_CLK float with 32mA
  writel((1 << 0) | (8 << 4), 0xff37e800 + 0x4); // SD_CMD
  writel((1 << 0) | (8 << 4), 0xff37e800 + 0x8); // SD_DATA0
  writel((1 << 0) | (8 << 4), 0xff37e800 + 0xc); // SD_DATA1
  writel((1 << 0) | (8 << 4), 0xff37e800 + 0x10); // SD_DATA2
  writel((1 << 0) | (8 << 4), 0xff37e800 + 0x14); // SD_DATA3

  do {
	data = readl(CRG_REG_BASE + 0xb8);
	data |= ((1 << 6) | (1 << 6 << 16) | (0 << 4) | (3 << 4 << 16));
	writel(data, CRG_REG_BASE + 0xb8);
    data = readl(CRG_REG_BASE + 0xb8);
  } while ((data & ((1 << 6) | (3 << 4))) != ((1 << 6) | (0 << 4)));

  // Unreset SD controller
  writel(1 << 18, CRG_PERRSTDIS4);
  do {
    data = readl(CRG_PERRSTSTAT4);
  } while ((data & (1 << 18)) == (1 << 18));
  // Enable SD controller clock
	data = readl(CRG_REG_BASE + 0);
	data |= (1 << 30);
	writel(data, CRG_REG_BASE + 0);
	data = readl(CRG_REG_BASE + 0x40);
	data |= (1 << 17);
	writel(data, CRG_REG_BASE + 0x40);
  do {
    data = readl(CRG_REG_BASE + 0x48);
  } while ((data & (1 << 17)) != (1 << 17));

}

int board_mmc_init(bd_t *bis)
{
	hikey960_mmc_init();
	return 0;
}

void reset_cpu(ulong addr)
{
	psci_system_reset();
}
