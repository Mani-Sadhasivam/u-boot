// SPDX-License-Identifier: GPL-2.0+
/*
 * Actions Semi OWL SoCs Clock driver
 *
 * Copyright (C) 2015 Actions Semi Co., Ltd.
 * Copyright (C) 2018 Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#include <common.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <fdtdec.h>
#include <asm/arch-owl/clk_owl.h>
#include <asm/io.h>
#include <asm/types.h>

static int owl_clk_probe(struct udevice *dev)
{
	struct owl_clk_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr(dev);
	if (priv->base == FDT_ADDR_T_NONE)
		return -EINVAL;

	/* setup necessary clocks */
	owl_clk_init(priv);

	return 0;
}

static int owl_clk_enable(struct clk *clk)
{
	return owl_periph_clk_enable(clk);
}

static int owl_clk_disable(struct clk *clk)
{
	return owl_periph_clk_disable(clk);
}

static struct clk_ops owl_clk_ops = {
	.enable = owl_clk_enable,
	.disable = owl_clk_disable,
};

static const struct udevice_id owl_clk_ids[] = {
	{ .compatible = "actions,s900-cmu" },
	{ }
};

U_BOOT_DRIVER(clk_owl) = {
	.name		= "clk_owl",
	.id		= UCLASS_CLK,
	.of_match	= owl_clk_ids,
	.ops		= &owl_clk_ops,
	.priv_auto_alloc_size = sizeof(struct owl_clk_priv),
	.probe		= owl_clk_probe,
	.flags		= DM_FLAG_PRE_RELOC,
};
