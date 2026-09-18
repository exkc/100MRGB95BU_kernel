
/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  main configuration file for sdec device
 *  sdec device will teach you how to make device driver with new platform.
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2017-04-10
 *  @note		Additional information.
 */

#include "ci_cfg.h"
#include "ci_debug.h"
/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#define MAX_COUNT_DIV 2


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
	CHIP_CFG_M19_IDX,
	CHIP_CFG_L18F_IDX,
	CHIP_CFG_O18_IDX,
	CHIP_CFG_M17_IDX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 ci_delay_default[DELAY_ENTRY_MAX] =
{
	/* ms */
	DEFAULT_CI_DELAY_CIS_CONFIG_FIRST_TUPLE_OK,
	DEFAULT_CI_DELAY_CIS_CONFIG_FIRST_TUPLE_NG,
	DEFAULT_CI_DELAY_CIS_END_WRITE_COR,
	DEFAULT_CI_DELAY_CIS_DURING_READ_TUPLE,
	DEFAULT_CI_DELAY_CIS_END_READ_TUPLE_INITIAL,
	DEFAULT_CI_DELAY_CIS_PARSE_NON_CI_TUPLE,
	DEFAULT_CI_DELAY_INIT_POWER_CONTROL,
	DEFAULT_CI_DELAY_INIT_AFTER_INTERRUPT_ENABLE,
	DEFAULT_CI_DELAY_CAM_INIT_BTW_VCC_CARDRESET,
	DEFAULT_CI_DELAY_CAM_INIT_BTW_CARDRESET_NOTRESET,
	DEFAULT_CI_DELAY_CAM_INIT_BTW_CARDRESET_EN_PCCARD,
	DEFAULT_CI_DELAY_IO_SOFT_RESET_CHECK_FR,
	DEFAULT_CI_DELAY_IO_END_SOFT_RESET,
	DEFAULT_CI_DELAY_IO_NEGOBUF_BEFORE_SOFTRESET,
	DEFAULT_CI_DELAY_IO_NEGOBUF_CHECK_DA,
	DEFAULT_CI_DELAY_IO_NEGOBUF_CHECK_FR,
	DEFAULT_CI_DELAY_IO_NEGOBUF_AFTER_WRITE_DATA,

	(DEFAULT_CI_DELAY_IO_READ_CHECK_DA / MAX_COUNT_DIV),
	(DEFAULT_CI_DELAY_IO_WRITE_CHECK_DA / MAX_COUNT_DIV),
	(DEFAULT_CI_DELAY_IO_WRITE_CHECK_FR / MAX_COUNT_DIV),

	DEFAULT_CI_DELAY_IO_WRITE_FIRST_BYTE_STAT_RD_FR_WE,
	DEFAULT_CI_DELAY_IO_WRITE_MIDDLE_BYTE_CHECK_WE,
	DEFAULT_CI_DELAY_IO_WRITE_LAST_BYTE_CHECK_WE,
	/* count */
	(MAX_CHECK_COUNT * MAX_COUNT_DIV),
	(MAX_CHECK_COUNT * MAX_COUNT_DIV),

	MAX_CHECK_COUNT,
	MAX_CHECK_COUNT,
	MAX_COUNT_DIV,
	MAXIM_RETRY_COUNT,
	/* count */
	MAX_VALID_TUPLE_CNT_CHK,
};

static CI_CFG_T default_chip_cfg =
{
	.smc_phys_addr		= CI_SMC_BASE,
	.smc_phys_size		= CI_SMC_SIZE,

	.reg_base			= COMMON_CI_REG_BASE,
	.reg_size			= 0x40,
	.mod_base			= COMMON_CI_CAM_BASE,
	.mod_size			= 0x8000,

	.cis_addr_limit		= 0x0,

	.smc_need_vcc		= 0,
};

static CI_CFG_T *ci_cfg;

/*========================================================================================
	Implementation Group
========================================================================================*/
void CI_CFG_PreInit(void)
{
	UINT32 chip = lx_chip();

	ci_cfg = &default_chip_cfg;

	/* get chip config */
	if(0){}
	else if(chip == LX_CHIP_O20)
	{
		ci_cfg->irq_num = O20_IRQ_DVB_CI;
		ci_cfg->smc_need_vcc = 0; //TODO: check lockup
	}
	else if(chip == LX_CHIP_M19)
	{
		ci_cfg->irq_num = M19_IRQ_DVB_CI;
		ci_cfg->smc_need_vcc = 1; //VCC workaround
	}
	else if(chip == LX_CHIP_O18)
	{
		ci_cfg->irq_num = O18_IRQ_DVB_CI;
		ci_cfg->smc_need_vcc = 1; //VCC workaround
	}
	else
	{
		LOG_ERROR("Not defined CHIP!!!");
		ci_cfg->irq_num = M19_IRQ_DVB_CI;
	}

	memcpy(ci_cfg->delays, ci_delay_default, sizeof(ci_delay_default));
}

CI_CFG_T* CI_GetConfig(void)
{
	return ci_cfg;
}

/** @} */
