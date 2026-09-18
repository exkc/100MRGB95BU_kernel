#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <asm/io.h>

extern int reg_m23_ioremap(void);
extern int m23_run_init(void);
extern int m23_mon_status(void);
extern int m23_dmc_test(void);

extern int reg_o24_ioremap(void);
extern int o24_run_init(void);
extern int o24_mon_status(void);
extern int o24_dmc_test(void);

int reg_ddr_ioremap(void);
int ddr_run_init(void);
int dmc_status(void);
int dmc_test(void);

int reg_ddr_ioremap(void)
{
#if defined(CHIP_NAME_m23)
	return reg_m23_ioremap();
#elif defined(CHIP_NAME_o24)
	return reg_o24_ioremap();
#else
	return -1;
#endif
}

int ddr_run_init(void)
{
#if defined(CHIP_NAME_m23)
	return m23_run_init();
#elif defined(CHIP_NAME_o24)
	return o24_run_init();
#else
	return -1;
#endif
}

int dmc_status(void)
{
#if defined(CHIP_NAME_m23)
	return m23_mon_status();
#elif defined(CHIP_NAME_o24)
	return o24_mon_status();
#else
	return -1;
#endif
}

int dmc_test(void)
{
#if defined(CHIP_NAME_m23)
	return m23_dmc_test();
#elif defined(CHIP_NAME_o24)
	return o24_dmc_test();
#else
	return -1;
#endif
}
