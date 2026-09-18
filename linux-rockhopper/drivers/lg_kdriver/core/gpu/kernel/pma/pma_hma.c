
#include <linux/version.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/protected_memory_allocator.h>

#include "hma_alloc.h"

static char *pool_name_override;
module_param(pool_name_override, charp, 0644);

struct simple_pma_device {
	struct protected_memory_allocator_device pma_dev;
	struct device *dev;
	char *pool_name;
};

static struct protected_memory_allocation *
simple_pma_alloc_page(struct protected_memory_allocator_device *pma_dev, unsigned int order)
{
	struct simple_pma_device *const epma_dev =
		container_of(pma_dev, struct simple_pma_device, pma_dev);
	struct protected_memory_allocation *pma;

	dev_dbg(epma_dev->dev, "%s(pma_dev=%px, order=%u\n", __func__, (void *)pma_dev, order);

	pma = devm_kzalloc(epma_dev->dev, sizeof(*pma), GFP_KERNEL);
	if (!pma) {
		dev_err(epma_dev->dev, "Failed to alloc pma struct");
		return NULL;
	}

	pma->pa = hma_alloc_user(epma_dev->pool_name, PAGE_SIZE << order,
			PAGE_SIZE, "gpu-pma");
	if (pma->pa == 0) {
		dev_err(epma_dev->dev, "Failed to alloc from \"%s\". order %d\n", epma_dev->pool_name, order);
		devm_kfree(epma_dev->dev, pma);
		return NULL;
	}
	pma->order = order;
	return pma;
}

static phys_addr_t simple_pma_get_phys_addr(struct protected_memory_allocator_device *pma_dev,
					    struct protected_memory_allocation *pma)
{
	struct simple_pma_device *const epma_dev =
		container_of(pma_dev, struct simple_pma_device, pma_dev);

	dev_dbg(epma_dev->dev, "%s(pma_dev=%px, pma=%px, pa=%pK\n", __func__, (void *)pma_dev,
		(void *)pma, (void *)pma->pa);

	return pma->pa;
}

static void simple_pma_free_page(struct protected_memory_allocator_device *pma_dev,
				 struct protected_memory_allocation *pma)
{
	struct simple_pma_device *const epma_dev =
		container_of(pma_dev, struct simple_pma_device, pma_dev);

	WARN_ON(pma == NULL);

	dev_dbg(epma_dev->dev, "%s(pma_dev=%px, pma=%px, pa=%pK\n", __func__, (void *)pma_dev,
		(void *)pma, (void *)pma->pa);

	hma_free(epma_dev->pool_name, pma->pa);
	devm_kfree(epma_dev->dev, pma);
}

static int protected_memory_allocator_probe(struct platform_device *pdev)
{
	struct simple_pma_device *epma_dev;
	struct device_node *np;
	const char *poolname;

	np = pdev->dev.of_node;
	if (!np) {
		dev_err(&pdev->dev, "device node pointer not set\n");
		return -ENODEV;
	}

	poolname = NULL;
	of_property_read_string(np, "hma-pool", &poolname);
	if (pool_name_override)
		poolname = pool_name_override;
	if (!poolname) {
		dev_err(&pdev->dev, "no \"hma-pool\" in device node\n");
		return -ENODEV;
	}

	epma_dev = devm_kzalloc(&pdev->dev, sizeof(*epma_dev), GFP_KERNEL);
	if (!epma_dev)
		return -ENOMEM;

	epma_dev->pma_dev.ops.pma_alloc_page = simple_pma_alloc_page;
	epma_dev->pma_dev.ops.pma_get_phys_addr = simple_pma_get_phys_addr;
	epma_dev->pma_dev.ops.pma_free_page = simple_pma_free_page;
	epma_dev->pma_dev.owner = THIS_MODULE;
	epma_dev->dev = &pdev->dev;
	epma_dev->pool_name = kstrdup(poolname, GFP_KERNEL);

	platform_set_drvdata(pdev, &epma_dev->pma_dev);
	dev_info(&pdev->dev, "Protected memory allocator probed successfully\n");
	dev_info(&pdev->dev, "Protected memory region: \"%s\"\n", epma_dev->pool_name);

	return 0;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void protected_memory_allocator_remove(struct platform_device *pdev)
#else
static int protected_memory_allocator_remove(struct platform_device *pdev)
#endif
{
	struct protected_memory_allocator_device *pma_dev = platform_get_drvdata(pdev);
	struct simple_pma_device *epma_dev;
	struct device *dev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	if (!pma_dev)
		return -EINVAL;
#endif
	epma_dev = container_of(pma_dev, struct simple_pma_device, pma_dev);
	dev = epma_dev->dev;

	platform_set_drvdata(pdev, NULL);
	devm_kfree(dev, epma_dev->pool_name);
	devm_kfree(dev, epma_dev);

	dev_info(&pdev->dev, "Protected memory allocator removed successfully\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static const struct of_device_id protected_memory_allocator_dt_ids[] = {
	{ .compatible = "lgsic,protected-memory-allocator" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, protected_memory_allocator_dt_ids);

static struct platform_driver
	protected_memory_allocator_driver = { .probe = protected_memory_allocator_probe,
					      .remove = protected_memory_allocator_remove,
					      .driver = {
						      .name = "hma_protected_memory_allocator",
						      .of_match_table = of_match_ptr(
							      protected_memory_allocator_dt_ids),
					      } };

module_platform_driver(protected_memory_allocator_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hyunwoo Park <hyonwoo.park at lge.com>");
MODULE_VERSION("1.0");
