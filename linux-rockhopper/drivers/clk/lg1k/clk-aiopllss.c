#include <linux/kernel.h>

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/clkdev.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>

struct clk_aiopllss {
	struct clk_hw hw;
	void __iomem *base;
	u32 param[4][3];
	u32 fix[3];
};

#define to_clk_aiopllss(_hw)	container_of(_hw, struct clk_aiopllss, hw)

#define bit_field(o,w,r)	(((r) >> (o)) & ((1 << (w)) - 1))

static unsigned long
clk_aiopllss_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_aiopllss const *clk = to_clk_aiopllss(hw);
	u32 const (*const param)[3] = clk->param;
	u32 regs[3], idv, npc, nsc, odv;
	unsigned long rate;

	regs[0] = clk->fix[0] ^ readl_relaxed(clk->base + 0x00);
	regs[1] = clk->fix[1] ^ readl_relaxed(clk->base + 0x04);
	regs[2] = clk->fix[2] ^ readl_relaxed(clk->base + 0x08);

	idv = bit_field(param[0][1], param[0][2], regs[param[0][0]]);
	npc = bit_field(param[1][1], param[1][2], regs[param[1][0]]);
	nsc = bit_field(param[2][1], param[2][2], regs[param[2][0]]);
	odv = bit_field(param[3][1], param[3][2], regs[param[3][0]]);

	parent_rate /= 1000000;	/* in MHz */

	rate = (npc * 4 + nsc) * parent_rate / ((idv ? : 1) * odv);

	return rate * 1000000;	/* in Hz */
}

static struct clk_ops clk_aiopllss_ops = {
	.recalc_rate	= clk_aiopllss_recalc_rate,
};

static struct clk *
clk_register_aiopllss(struct device *dev, char const *name,
                      char const *parent_name, unsigned long flags,
                      struct clk_ops const *ops, void __iomem *base,
                      u32 const param[], u32 const fix[])
{
	struct clk_aiopllss *clk_aiopllss;
	struct clk_init_data init_data;
	struct clk *clk;
	int i, j;

	clk_aiopllss = kzalloc(sizeof(struct clk_aiopllss), GFP_KERNEL);
	if (!clk_aiopllss) {
		pr_err("%s: can't allocate memory\n", __func__);
		return ERR_PTR(-ENOMEM);
	}

	init_data.name = name;
	init_data.ops = ops;
	init_data.flags = flags;
	init_data.parent_names = &parent_name;
	init_data.num_parents = 1;

	clk_aiopllss->hw.init = &init_data;
	clk_aiopllss->base = base;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			clk_aiopllss->param[i][j] = param[i * 3 + j];
	for (i = 0; i < 3; i++)
		clk_aiopllss->fix[i] = fix[i];

	clk = clk_register(dev, &clk_aiopllss->hw);
	if (IS_ERR(clk))
		kfree(clk_aiopllss);

	return clk;
}

static void __init __clk_aiopllss_of_setup(struct device_node *np)
{
	struct clk *clk;
	char const *clk_name = np->name;
	char const *parent_name;
	void __iomem *base;
	u32 param[12];
	u32 fix[3] = { 0, };

	if (of_property_read_u32_array(np, "param", param, 12)) {
		pr_err("%s: can't find parameter information\n", __func__);
		return;
	}
	parent_name = of_clk_get_parent_name(np, 0);
	if (!parent_name) {
		pr_err("%s: can't find parent clock name\n", __func__);
		return;
	}
	base = of_iomap(np, 0);
	if (!base) {
		pr_err("%s: can't find control address\n", __func__);
		return;
	}
	of_property_read_string(np, "clock-output-names", &clk_name);
	of_property_read_u32_array(np, "fix", fix, 3);

	clk = clk_register_aiopllss(NULL, clk_name, parent_name,
	                            CLK_GET_RATE_NOCACHE, &clk_aiopllss_ops,
	                            base, param, fix);
	if (!IS_ERR(clk))
		of_clk_add_provider(np, of_clk_src_simple_get, clk);
}

static void __init clk_aiopllss_of_setup(struct device_node *np)
{
	__clk_aiopllss_of_setup(np);
}
CLK_OF_DECLARE(clk_aiopllss, "lge,aiopllss-clock", clk_aiopllss_of_setup);
