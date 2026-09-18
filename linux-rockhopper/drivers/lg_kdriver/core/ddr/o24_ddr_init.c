#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <asm/io.h>

#include "REGISTER/register_o24.h"
#include "config.h"

uint32_t *REG_DPG0_M0_S, *REG_DPG0_M1_S;
uint32_t *REG_DPG1_M0_S, *REG_DPG1_M1_S;
uint32_t *REG_DPG2_M0_S, *REG_DPG2_M1_S;
uint32_t *REG_DPG3_M0_S, *REG_DPG3_M1_S;

extern void dmc_test(void);
extern int dmcu_init(void);

int reg_o24_ioremap(void);
int o24_run_init(void);

int reg_o24_ioremap(void)
{
	/* DDR Register */
	gpREG_DDRT_M0 = (REG_DDRT_M0_T *)ioremap(APB_DDRT_M0_BASE, sizeof(REG_DDRT_M0_T));
	gpREG_DDRC_M0 = (REG_DDRC_M0_T *)ioremap(APB_DDRC_M0_BASE, sizeof(REG_DDRC_M0_T));
	gpREG_DDRP_M0 = (REG_DDRP_M0_T *)ioremap(APB_DDRP_M0_BASE, sizeof(REG_DDRP_M0_T));

	gpREG_DPG0_M0 = (REG_DPG0_M0_T *)ioremap(APB_DPG0_M0_BASE, sizeof(REG_DPG0_M0_T));
	gpREG_DPG1_M0 = (REG_DPG1_M0_T *)ioremap(APB_DPG1_M0_BASE, sizeof(REG_DPG1_M0_T));
	gpREG_DPG2_M0 = (REG_DPG2_M0_T *)ioremap(APB_DPG2_M0_BASE, sizeof(REG_DPG2_M0_T));
	gpREG_DPG3_M0 = (REG_DPG3_M0_T *)ioremap(APB_DPG3_M0_BASE, sizeof(REG_DPG3_M0_T));

	REG_DPG0_M0_S = (uint32_t *)ioremap(APB_DPG0_M0_BASE - 0x100, sizeof(uint32_t));
	REG_DPG1_M0_S = (uint32_t *)ioremap(APB_DPG1_M0_BASE - 0x100, sizeof(uint32_t));
	REG_DPG2_M0_S = (uint32_t *)ioremap(APB_DPG2_M0_BASE - 0x100, sizeof(uint32_t));
	REG_DPG3_M0_S = (uint32_t *)ioremap(APB_DPG3_M0_BASE - 0x100, sizeof(uint32_t));

	gpREG_DDRT_M1 = (REG_DDRT_M1_T *)ioremap(APB_DDRT_M1_BASE, sizeof(REG_DDRT_M1_T));
	gpREG_DDRC_M1 = (REG_DDRC_M1_T *)ioremap(APB_DDRC_M1_BASE, sizeof(REG_DDRC_M1_T));
	gpREG_DDRP_M1 = (REG_DDRP_M1_T *)ioremap(APB_DDRP_M1_BASE, sizeof(REG_DDRP_M1_T));

	gpREG_DPG0_M1 = (REG_DPG0_M1_T *)ioremap(APB_DPG0_M1_BASE, sizeof(REG_DPG0_M1_T));
	gpREG_DPG1_M1 = (REG_DPG1_M1_T *)ioremap(APB_DPG1_M1_BASE, sizeof(REG_DPG1_M1_T));
	gpREG_DPG2_M1 = (REG_DPG2_M1_T *)ioremap(APB_DPG2_M1_BASE, sizeof(REG_DPG2_M1_T));
	gpREG_DPG3_M1 = (REG_DPG3_M1_T *)ioremap(APB_DPG3_M1_BASE, sizeof(REG_DPG3_M1_T));

	REG_DPG0_M1_S = (uint32_t *)ioremap(APB_DPG0_M0_BASE - 0x100, sizeof(uint32_t));
	REG_DPG1_M1_S = (uint32_t *)ioremap(APB_DPG1_M0_BASE - 0x100, sizeof(uint32_t));
	REG_DPG2_M1_S = (uint32_t *)ioremap(APB_DPG2_M0_BASE - 0x100, sizeof(uint32_t));
	REG_DPG3_M1_S = (uint32_t *)ioremap(APB_DPG3_M0_BASE - 0x100, sizeof(uint32_t));

	gpREG_SYSTEM = (REG_SYSTEM_T *)ioremap(APB_SYSTEM_BASE, sizeof(REG_SYSTEM_T));
	gpREG_MCU = (REG_MCU_T *)ioremap(APB_MCU_BASE, sizeof(REG_MCU_T));

	pr_info("dmc: o24_ioremap\n");

	return 0;
}

int o24_run_init(void)
{
	//dmc_test();
	dmcu_init();

	pr_info("dmc: o24_run_init\n");

	return 0;
}
