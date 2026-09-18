/*
 * lg1k specific CMA reservation interface
 * arch/arm/mach-lg1k/cma.c
 */
#include <linux/memblock.h>
#include <linux/cma.h>
#include <linux/mm.h>
#include <linux/dma-map-ops.h>

#define CMA_DEV_LEN 16

struct lg1k_cma_area {
	char name[CMA_DEV_LEN];
	struct cma *cma;
	phys_addr_t size;
	phys_addr_t base;
	phys_addr_t end;
	phys_addr_t limit;
	phys_addr_t size_req;
	phys_addr_t base_req;
	phys_addr_t end_req;
};

static struct lg1k_cma_area lg1k_cma[CONFIG_CMA_AREAS];
static int cma_area_num = 0;

struct reserve_range {
	phys_addr_t base;
	phys_addr_t size;
};
static struct reserve_range res[CONFIG_CMA_AREAS * 2];
static int res_num = 0;
/*
 * 0: disable
 * 1: enable but not use
 * 2: enable and alloc anon pages
 */
static int __cma_on = 0;
int cma_on = 0;
EXPORT_SYMBOL(cma_on);

static int __init lg1k_cma_on(char *p)
{
	pr_debug("%s(%s)\n", __func__, p);
	__cma_on = 1;
	if (!p)
		return 0;
	if (!strcmp("anon", p))
                __cma_on = 2;
	return 0;
}
early_param("cma_on", lg1k_cma_on);

int is_cma_on(void)
{
	return cma_on;
}
EXPORT_SYMBOL(is_cma_on);

static char* __init _parse_cma(struct lg1k_cma_area *cma, char **p)
{
	phys_addr_t alignment= PAGE_SIZE << max(pageblock_order, MAX_PAGE_ORDER -1);
	char *tok = 0;
	unsigned int len;

	pr_debug("%s(%s)\n", __func__, *p);

	tok = strchr(*p, ',');
	if (tok) {
		len = tok - *p;
		if (len > CMA_DEV_LEN)
			return 0;
		memcpy(cma->name , *p, len);
		*p = tok + 1;
		pr_debug("%s(%s)\n", __func__, cma->name);
	}

	cma->size_req = memparse(*p, p);
	if (**p != '@') {
		cma->size = round_up(cma->size_req, alignment);
		cma->base = 0;
		return 0;
	}

	cma->base_req = memparse(*p + 1, p);
	cma->end_req = cma->base_req + cma->size_req;

	cma->end = round_up(cma->end_req, alignment);
	cma->base = round_down(cma->base_req, alignment);
	cma->size = cma->end - cma->base;

	pr_debug("%s: %lx-%lx\n",__func__,
			(unsigned long)cma->base, (unsigned long)cma->end);

	if (**p != '-') {
		cma->limit = cma->base + cma->size;
		return 0;
	}
	cma->limit = memparse(*p + 1, p);
	return 0;
}

static int __init early_lg1k_cma(char *p)
{
	do {
		_parse_cma(&lg1k_cma[cma_area_num++], &p);
	} while (*p++ == ';');

	pr_debug("%s: %d\n",__func__, cma_area_num);

	return 0;
}
early_param("hma", early_lg1k_cma);

static int __init early_lg1k_cma_dev(char *p)
{
	return early_lg1k_cma(p);
}
early_param("cma_dev", early_lg1k_cma_dev);

void dev_bind_cma_area(struct device *dev, char *name)
{
	int i;
	bool found = false;
	struct lg1k_cma_area *cma_area;

	pr_debug("%s %p, %s\n",__func__, dev, name);
	if (!dev || strlen(name) > CMA_DEV_LEN) {
		pr_err("invalid argument or string length passed\n");
		return;
	}

	for ( i = 0; i <  cma_area_num; i++) {
		cma_area = &lg1k_cma[i];
		pr_debug("cma_area(%d),%s 0x%llx\n",i, cma_area->name,  cma_area->size);
		if( cma_area->name &&
		    !strncmp(name, cma_area->name, strlen(name))) {
			dev->cma_area = cma_area->cma;
			found = true;
			pr_info ("Find reserved CMA area for %s:%p\n",name, dev->cma_area);
			break;
		}
	}

	if (found == false)
		pr_err ("Can't find reserved CMA area for %s\n",name);

}
EXPORT_SYMBOL(dev_bind_cma_area);

static int __init _reserve_memory(phys_addr_t base,
			phys_addr_t size, bool nomap)
{
	pr_debug("%s: %lx-%lx\n",__func__,
			(unsigned long)base, (unsigned long)(base + size));
	if (nomap)
		return memblock_remove(base, size);
	return memblock_reserve(base, size);
}

static bool addrs_overlap(phys_addr_t base1, phys_addr_t size1,
			  phys_addr_t base2, phys_addr_t size2)
{
        return ((base1 < (base2 + size2)) && (base2 < (base1 + size1)));
}

int __init early_init_dt_reserve_memory_arch(phys_addr_t base,
                                        phys_addr_t size, bool nomap)
{
	if (memblock_is_region_reserved(base, size)) {
		int i, j;
		struct lg1k_cma_area *cma;
		struct reserve_range *_res;
		int ret = 0;

		for (i = 0; i < cma_area_num; i++) {
			cma = &lg1k_cma[i];
			if ((cma->size > 0) && cma->base
				&& memblock_is_region_reserved(cma->base, cma->size)
				&& addrs_overlap(base, size, cma->base, cma->size)) {
				if (base < cma->base) {
					res[res_num].base = base;
					res[res_num].size = cma->base - base;
					res_num++;
				}
				if (cma->base + cma->size < base + size) {
					res[res_num].base = cma->base + cma->size;
					res[res_num].size = (base + size)
							- (cma->base + cma->size);
					res_num++;
				}
			}
		}

		for (j = 0; j < res_num; j++) {
			_res = &res[j];
			for (i = 0; i < cma_area_num; i++) {
				cma = &lg1k_cma[i];
				if ((cma->size > 0) && cma->base
					&& addrs_overlap(_res->base,
							_res->size, cma->base,
							cma->size)) {
					if (cma->base >= _res->base)
						_res->size = cma->base - _res->base;
				}
			}
		}
		for (j = 0; j < res_num; j++) {
			if (res[j].size)
				ret |= _reserve_memory(res[j].base, res[j].size, nomap);
		}

		return ret;
	}
	else
		return _reserve_memory(base, size, nomap);
}


static int __init _lg1k_reserve_cma(struct lg1k_cma_area *cma)
{
	struct cma *_cma = 0;
	int ret;

	if (cma->size <= 0 || !__cma_on)
		return -EINVAL;

	ret = cma_declare_contiguous(cma->base, cma->size,
			cma->limit, 0, 0, true, "cma", &_cma);
	if(_cma)
		cma->cma = _cma;
	return ret;
}

void __init lg1k_reserve_cma(void)
{
	int i = 0;
	int ret;
	int cnt = 0;

	for (i = 0; i < cma_area_num; i++) {
		struct lg1k_cma_area *cma = &lg1k_cma[i];

		ret = _lg1k_reserve_cma(cma);
		if(ret < 0)
			pr_info("cma: Skip to invalid area: 0x%lx-0x%lx\n",
			(unsigned long)cma->base, (unsigned long)cma->end);
		else
			cnt++;
	}

	if (cnt)
		cma_on = __cma_on;
}

static int __init lg1k_cma_prealloc(struct lg1k_cma_area *cma)
{
	if (cma->base_req > cma->base) {
		if(alloc_contig_range(__phys_to_pfn(cma->base),
				__phys_to_pfn(cma->base_req),
				MIGRATE_CMA, GFP_KERNEL))
			goto fail;
		else
			pr_info("Pre-allocate CMA area: %lx-%lx\n",
				(unsigned long)(cma->base),
				(unsigned long)(cma->base_req));
	}

	if (cma->end_req < cma->end) {
		if(alloc_contig_range(__phys_to_pfn(cma->end_req),
				__phys_to_pfn(cma->end),
				MIGRATE_CMA, GFP_KERNEL))
			goto fail;
		else
			pr_info("Pre-allocate CMA area: %lx-%lx\n",
				(unsigned long)(cma->end_req),
				(unsigned long)(cma->end));
	}
	return 0;
fail:
	pr_err("Fail to Pre-alloccate CMA\n");
	return -ENOMEM;

}

static int __init lg1k_cma_init(void)
{
	int i;
	for (i = 0; i < cma_area_num; i++)
		lg1k_cma_prealloc(&lg1k_cma[i]);

	return 0;
}
postcore_initcall(lg1k_cma_init);
