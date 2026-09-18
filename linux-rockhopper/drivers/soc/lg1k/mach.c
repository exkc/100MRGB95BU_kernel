#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/amba/pl08x.h>
#include <linux/amba/pl080.h>

#ifdef CONFIG_AMBA_PL08X
extern struct pl08x_platform_data dmac_data;
#endif
extern struct pl022_ssp_controller spi0_data;
extern struct pl022_ssp_controller spi1_data;

#ifdef CONFIG_SPI_DESIGNWARE
extern struct dw_spi_mmio dwspi_data;
#endif

static struct of_dev_auxdata lg115x_auxdata_lookup[] __initdata = {
#ifdef CONFIG_AMBA_PL08X
	OF_DEV_AUXDATA("arm,pl080", 0xff200000, "dmac", &dmac_data),
#endif
#ifdef CONFIG_SPI_PL022
	OF_DEV_AUXDATA("arm,pl022", 0xfe800000, "spi0", &spi0_data),
	OF_DEV_AUXDATA("arm,pl022", 0xfe900000, "spi1", &spi1_data),
#endif
	{ },
};

#ifdef CONFIG_SPI_DESIGNWARE
extern struct dw_spi_mmio dwspi_data;
#endif

static struct of_dev_auxdata lg121x_auxdata_lookup[] __initdata = {
#ifdef CONFIG_AMBA_PL08X
	OF_DEV_AUXDATA("arm,pl080", 0xff200000, "dmac", &dmac_data),
#endif
#ifdef CONFIG_SPI_DESIGNWARE
	OF_DEV_AUXDATA("snps.dw-apb-ssi", 0xfe800000, "spi0", &dwspi_data),
#endif
#ifdef CONFIG_SPI_PL022
	OF_DEV_AUXDATA("arm,pl022", 0xfe900000, "spi1", &spi1_data),
#endif
	{ },
};

static int __init lg115x_init_machine(void)
{
	if (of_machine_is_compatible("lge,lg1213") || of_machine_is_compatible("lge,lg1214")){
		of_platform_populate(NULL, of_default_bus_match_table,
			lg121x_auxdata_lookup, NULL);
	}else{
		of_platform_populate(NULL, of_default_bus_match_table,
			lg115x_auxdata_lookup, NULL);
	}

	return 0;
}
arch_initcall(lg115x_init_machine);

