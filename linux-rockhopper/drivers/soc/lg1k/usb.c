#include <linux/kernel.h>

#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/usb/ehci_pdriver.h>
#include <linux/usb/ohci_pdriver.h>
#include <linux/usb/phy.h>

struct usb_host_data {
	char const *name;
	char const *phy_name;
	int *id;
	void *pdata;
	bool is_userresume;
	bool is_userresume_phy;
};

static int xhci_id;
static int dwc3_id;
static int ehci_id;
static int ohci_id;
static int drd2_id;

static struct usb_ehci_pdata ehci_pdata = {
	.has_synopsys_hc_bug = 1,
	.has_synopsys_shortread_bug = 1,
	.reset_on_resume = 1,
};

static struct usb_ohci_pdata ohci_pdata = {
	.num_ports = 1,
};

static struct usb_host_data xhci_data = {
	.name	= "xhci-hcd",
	.phy_name	= "lg1k-usb3phy",
	.id	= &xhci_id,
	.is_userresume = true,
	.is_userresume_phy = false,
};

static struct usb_host_data dwc3_data = {
	.name   = "dwc3-hcd",
	.phy_name       = "lg1k-usb3phy",
	.id     = &dwc3_id,
	.is_userresume = true,
	.is_userresume_phy = false,
};

static struct usb_host_data ehci_data = {
	.name	= "generic-ehci",
	.phy_name	= "lg1k-usb2phy",
	.id	= &ehci_id,
	.pdata	= &ehci_pdata,
	.is_userresume = true,
	.is_userresume_phy = false,
};

static struct usb_host_data drd2_data = {
	.name	= "snps,dwc2",
	.phy_name	= "lg1k-drd2phy",
	.id	= &drd2_id,
	.is_userresume = true,
	.is_userresume_phy = false,
};

static struct usb_host_data ohci_data = {
	.name	= "generic-ohci",
	.phy_name	= "lg1k-usb1phy",
	.id	= &ohci_id,
	.pdata	= &ohci_pdata,
	.is_userresume = true,
	.is_userresume_phy = false,
};

static struct of_device_id const usb_host_ids[] = {
	{ .compatible = "lge,lg115x-xhci", .data = &xhci_data, },
	{ .compatible = "lge,lg115x-dwc3", .data = &dwc3_data, },
	{ .compatible = "lge,lg115x-ehci", .data = &ehci_data, },
	{ .compatible = "lge,lg115x-ohci", .data = &ohci_data, },
	{ .compatible = "lge,lg115x-drd2", .data = &drd2_data, },
	{ },
};

static int of_update_status_okay(struct device_node *node)
{
	struct property *prop;

	prop = kzalloc(sizeof(*prop), GFP_KERNEL);
	if (!prop)
		return -ENOMEM;

	prop->name = "status";
	prop->value = "okay";
	prop->length = strlen(prop->value) + 1;

	return of_update_property(node, prop);
}

static int lg1k_init_usb(void)
{
	struct device_node *np;
	static int initialized;

	if (initialized) {
		pr_err("lg1k usb host/phy devices are already registered\n");
		return 0;
	}

	for_each_matching_node(np, usb_host_ids) {
		struct usb_host_data const *data;
		struct resource *res;
		struct platform_device *pdev = NULL;
		struct device_node *phy_np = NULL;

		data = of_match_node(usb_host_ids, np)->data;

		res = kzalloc(sizeof(struct resource) * 2, GFP_KERNEL);
		of_address_to_resource(np, 0, &res[0]);
		of_irq_to_resource(np, 0, &res[1]);

		pdev = kzalloc(sizeof(struct platform_device), GFP_KERNEL);
		pdev->name = data->name;
		pdev->id = (*data->id)++;
		pdev->dev.of_node = np;
		pdev->dev.fwnode = &np->fwnode;
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
		pdev->dev.platform_data = data->pdata;
#ifdef CONFIG_PM_SLEEP
		pdev->dev.power.is_userresume = data->is_userresume;
#endif	/* CONFIG_PM_SLEEP */
		of_dma_configure(&pdev->dev, pdev->dev.of_node, true);
		pdev->num_resources = 2;
		pdev->resource = res;

		phy_np = of_get_next_child(np, phy_np);
		if(phy_np) {
			struct platform_device *phy_pdev = NULL;
			if (data == &ohci_data)
				break;

			phy_pdev = kzalloc(sizeof(struct platform_device),
				GFP_KERNEL);
			if (!phy_pdev)
				pr_err("%s-%d phy_pdev alloc error\n",
					data->name, pdev->id);
			phy_pdev->name = data->phy_name;
			phy_pdev->id = pdev->id;
			phy_pdev->dev.of_node = phy_np;
			phy_pdev->dev.dma_mask = &phy_pdev->dev.coherent_dma_mask;
			phy_pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
#ifdef CONFIG_PM_SLEEP
			phy_pdev->dev.power.is_userresume = data->is_userresume_phy;
#endif	/* CONFIG_PM_SLEEP */
			of_dma_configure(&phy_pdev->dev, phy_pdev->dev.of_node, true);
			of_update_status_okay(phy_np);
			platform_device_register(phy_pdev);
		}
		of_update_status_okay(np);
		platform_device_register(pdev);
	}

	initialized++;
	return 0;
}
#ifndef	CONFIG_USER_INITCALL_USB
device_initcall(lg1k_init_usb);
#else	/* CONFIG_USER_INITCALL_USB */
user_initcall_grp("USB", lg1k_init_usb);
#endif	/* CONFIG_USER_INITCALL_USB */
