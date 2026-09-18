/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#include "te_impl.h"
#include "te_cfg.h"

#define TE_REG_SIZE			0x3000

#define TE_MCU0_REG_OFFSET		0x0000
#define TE_MCU1_REG_OFFSET		0x0400

#define TE_A3_REG_OFFSET		0x0800
#define TE_DUMPER_REG_OFFSET		0x0800
#define TE_ARIB_REG_OFFSET		0x0C00
#define TE_DEMOD_REG_OFFSET		0x1000
#define TE_TOP_REG_OFFSET		0x1100
#define TE_UPLOAD0_REG_OFFSET		0x1200
#define TE_UPLOAD1_REG_OFFSET		0x1300
#define TE_DSC_TOP_REG_OFFSET		0x1400
#define TE_BE_TOP_REG_OFFSET		0x1600
#define TE_CIPLUS_REG_OFFSET		0x1800
#define TE_FE_PIDF_REG_OFFSET		0x2000
#define TE_FE_TSBUF_REG_OFFSET		0x2500
#define TE_FE_STCC_REG_OFFSET		0x2600
#define TE_DSC2_TOP_REG_OFFSET		0x2A00

#define TE_MCU0_IRQ_OFFSET		0
#define TE_MCU1_IRQ_OFFSET		1
#define TE_HW_IRQ_OFFSET		2

#if CONFIG_LX_BOARD_FPGA
#define COMMON_TE_CLK_DIVIDER		80
#else
#define COMMON_TE_CLK_DIVIDER		1
#endif

/* E60 : LG1811 */
#define E60_TE_REG_BASE			0xC98B0000
#define E60_TE_IRQ_BASE			(32 + 80)
#define E60_TE_CLK_DIVIDER		COMMON_TE_CLK_DIVIDER

/* O22 : LG1213 */
#define O22_TE_REG_BASE			0xCAB00000
#define O22_TE_IRQ_BASE			(32 + 80)
#define O22_TE_CLK_DIVIDER		COMMON_TE_CLK_DIVIDER

/* M23 : LG1315 */
#define M23_TE_REG_BASE			0xCEFE0000
#define M23_TE_IRQ_BASE			(32 + 73)
#define M23_TE_CLK_DIVIDER		COMMON_TE_CLK_DIVIDER
//Consider renaming it after M23
#define M23_TE_MCU_IRQ_OFFSET		0
#define M23_TE_HW_IRQ_OFFSET		1

/* O24 : LG1214 */
#define O24_TE_REG_BASE			0xC8470000
#define O24_TE_IRQ_BASE			(32 + 130)
#define O24_TE_CLK_DIVIDER		COMMON_TE_CLK_DIVIDER

/* O26 : LG1215 */
#define O26_TE_REG_BASE			0xC87F0000
#define O26_TE_IRQ_BASE			(32 + 137)
#define O26_TE_CLK_DIVIDER		COMMON_TE_CLK_DIVIDER

LX_MEMCFG_T gMemCfgTE[4] = {
	[TE_MEM_MCU]	= {.name = "mcu",},
	[TE_MEM_SDEC]	= {.name = "sdec",} ,
	[TE_MEM_SHARED]	= {.name = "shared",},
	[TE_MEM_PVR]	= {.name = "pvr",},
};

static const LX_TE_INPUT_PORT_T tpi_info_normal[] = {	/* O18 ~ */
	LX_TE_INPUT_PORT_TPI_IN_DEMOD0,
	LX_TE_INPUT_PORT_TPI_EXT_INPUT0,
	LX_TE_INPUT_PORT_TPI_EXT_INPUT1,
	LX_TE_INPUT_PORT_TPI_CI_INPUT,
	LX_TE_INPUT_PORT_TPI_CI_OUTPUT,
};

static const struct te_io_cfg common_io_cfg = {
	.version		= 4,
	.num_dumper		= 4,
	.num_tpi_input		= ARRAY_SIZE(tpi_info_normal),
	.tpi_info		= tpi_info_normal,
	.num_ci_input		= 1,
	.num_ciplus_input	= 3,
	.num_ciplus_demux	= 3,
};

static const struct te_clk_cfg common_clk_cfg = {
	.num_stcc	= 4,
	.num_gstcc	= 4,
	.divider	= COMMON_TE_CLK_DIVIDER,
};

#ifdef INCLUDE_O26_CHIP_KDRV
static struct te_config config_o26 = {
	.reg_addr = {
		.base	= (O26_TE_REG_BASE),
		.dumper	= (O26_TE_REG_BASE + TE_DUMPER_REG_OFFSET),
		.tpi	= (O26_TE_REG_BASE + TE_DEMOD_REG_OFFSET),
		.top	= (O26_TE_REG_BASE + TE_TOP_REG_OFFSET),
		.pidf	= (O26_TE_REG_BASE + TE_FE_PIDF_REG_OFFSET),
		.tsbuf	= (O26_TE_REG_BASE + TE_FE_TSBUF_REG_OFFSET),
		.stcc	= (O26_TE_REG_BASE + TE_FE_STCC_REG_OFFSET),
		.be	= (O26_TE_REG_BASE + TE_BE_TOP_REG_OFFSET),
		.dsc	= {(O26_TE_REG_BASE + TE_DSC_TOP_REG_OFFSET),
			(O26_TE_REG_BASE + TE_DSC2_TOP_REG_OFFSET)},
		.upload	= {(O26_TE_REG_BASE + TE_UPLOAD0_REG_OFFSET),
			(O26_TE_REG_BASE + TE_UPLOAD1_REG_OFFSET)},
		.mcu	= {(O26_TE_REG_BASE + TE_MCU0_REG_OFFSET),
			(O26_TE_REG_BASE + TE_MCU1_REG_OFFSET)},
		.ciplus	= (O26_TE_REG_BASE + TE_CIPLUS_REG_OFFSET),
	},

	.hw_irq_num	= (O26_TE_IRQ_BASE + TE_HW_IRQ_OFFSET),
	.mcu_irq_num	= {(O26_TE_IRQ_BASE + TE_MCU0_IRQ_OFFSET),
		(O26_TE_IRQ_BASE + TE_MCU1_IRQ_OFFSET)},
	.num_mcu	= 2,
	.num_dsc	= 2,
	.num_upload	= 2,
};
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
static struct te_config config_o24 = {
	.reg_addr = {
		.base	= (O24_TE_REG_BASE),
		.dumper	= (O24_TE_REG_BASE + TE_DUMPER_REG_OFFSET),
		.tpi	= (O24_TE_REG_BASE + TE_DEMOD_REG_OFFSET),
		.top	= (O24_TE_REG_BASE + TE_TOP_REG_OFFSET),
		.pidf	= (O24_TE_REG_BASE + TE_FE_PIDF_REG_OFFSET),
		.tsbuf	= (O24_TE_REG_BASE + TE_FE_TSBUF_REG_OFFSET),
		.stcc	= (O24_TE_REG_BASE + TE_FE_STCC_REG_OFFSET),
		.be	= (O24_TE_REG_BASE + TE_BE_TOP_REG_OFFSET),
		.dsc	= {(O24_TE_REG_BASE + TE_DSC_TOP_REG_OFFSET),
			(O24_TE_REG_BASE + TE_DSC2_TOP_REG_OFFSET)},
		.upload	= {(O24_TE_REG_BASE + TE_UPLOAD0_REG_OFFSET),
			(O24_TE_REG_BASE + TE_UPLOAD1_REG_OFFSET)},
		.mcu	= {(O24_TE_REG_BASE + TE_MCU0_REG_OFFSET),
			(O24_TE_REG_BASE + TE_MCU1_REG_OFFSET)},
		.ciplus	= (O24_TE_REG_BASE + TE_CIPLUS_REG_OFFSET),
	},

	.hw_irq_num	= (O24_TE_IRQ_BASE + TE_HW_IRQ_OFFSET),
	.mcu_irq_num	= {(O24_TE_IRQ_BASE + TE_MCU0_IRQ_OFFSET),
		(O24_TE_IRQ_BASE + TE_MCU1_IRQ_OFFSET)},
	.num_mcu	= 2,
	.num_dsc	= 2,
	.num_upload	= 2,
};
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
static struct te_config config_m23 = {
	.reg_addr = {
		.base	= (M23_TE_REG_BASE),
		.dumper	= (M23_TE_REG_BASE + TE_DUMPER_REG_OFFSET),
		.tpi	= (M23_TE_REG_BASE + TE_DEMOD_REG_OFFSET),
		.top	= (M23_TE_REG_BASE + TE_TOP_REG_OFFSET),
		.pidf	= (M23_TE_REG_BASE + TE_FE_PIDF_REG_OFFSET),
		.tsbuf	= (M23_TE_REG_BASE + TE_FE_TSBUF_REG_OFFSET),
		.stcc	= (M23_TE_REG_BASE + TE_FE_STCC_REG_OFFSET),
		.be	= (M23_TE_REG_BASE + TE_BE_TOP_REG_OFFSET),
		.dsc	= {(M23_TE_REG_BASE + TE_DSC_TOP_REG_OFFSET),
			(M23_TE_REG_BASE + TE_DSC2_TOP_REG_OFFSET)},
		.upload	= {(M23_TE_REG_BASE + TE_UPLOAD0_REG_OFFSET),
			(M23_TE_REG_BASE + TE_UPLOAD1_REG_OFFSET)},
		.mcu	= {(M23_TE_REG_BASE + TE_MCU0_REG_OFFSET),
			(M23_TE_REG_BASE + TE_MCU1_REG_OFFSET)},
		.ciplus	= (M23_TE_REG_BASE + TE_CIPLUS_REG_OFFSET),
	},

	.hw_irq_num	= (M23_TE_IRQ_BASE + M23_TE_HW_IRQ_OFFSET),
	.mcu_irq_num	= {(M23_TE_IRQ_BASE + M23_TE_MCU_IRQ_OFFSET), },
	.num_mcu	= 1,
	.num_dsc	= 2,
	.num_upload	= 2,
	.include_demod = true,
};
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
static struct te_config config_o22 = {
	.reg_addr = {
		.base	= (O22_TE_REG_BASE),
		.dumper	= (O22_TE_REG_BASE + TE_DUMPER_REG_OFFSET),
		.tpi	= (O22_TE_REG_BASE + TE_DEMOD_REG_OFFSET),
		.top	= (O22_TE_REG_BASE + TE_TOP_REG_OFFSET),
		.pidf	= (O22_TE_REG_BASE + TE_FE_PIDF_REG_OFFSET),
		.tsbuf	= (O22_TE_REG_BASE + TE_FE_TSBUF_REG_OFFSET),
		.stcc	= (O22_TE_REG_BASE + TE_FE_STCC_REG_OFFSET),
		.be	= (O22_TE_REG_BASE + TE_BE_TOP_REG_OFFSET),
		.dsc	= {(O22_TE_REG_BASE + TE_DSC_TOP_REG_OFFSET),
			(O22_TE_REG_BASE + TE_DSC2_TOP_REG_OFFSET)},
		.upload	= {(O22_TE_REG_BASE + TE_UPLOAD0_REG_OFFSET),
			(O22_TE_REG_BASE + TE_UPLOAD1_REG_OFFSET)},
		.mcu	= {(O22_TE_REG_BASE + TE_MCU0_REG_OFFSET),
			(O22_TE_REG_BASE + TE_MCU1_REG_OFFSET)},
		.ciplus	= (O22_TE_REG_BASE + TE_CIPLUS_REG_OFFSET),
	},

	.hw_irq_num	= (O22_TE_IRQ_BASE + TE_HW_IRQ_OFFSET),
	.mcu_irq_num	= {(O22_TE_IRQ_BASE + TE_MCU0_IRQ_OFFSET),
		(O22_TE_IRQ_BASE + TE_MCU1_IRQ_OFFSET)},
	.num_mcu	= 2,
	.num_dsc	= 2,
	.num_upload	= 2,
};
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
static struct te_config config_e60 = {
	.reg_addr = {
		.base	= (E60_TE_REG_BASE),
		.dumper	= (E60_TE_REG_BASE + TE_DUMPER_REG_OFFSET),
		.tpi	= (E60_TE_REG_BASE + TE_DEMOD_REG_OFFSET),
		.top	= (E60_TE_REG_BASE + TE_TOP_REG_OFFSET),
		.pidf	= (E60_TE_REG_BASE + TE_FE_PIDF_REG_OFFSET),
		.tsbuf	= (E60_TE_REG_BASE + TE_FE_TSBUF_REG_OFFSET),
		.stcc	= (E60_TE_REG_BASE + TE_FE_STCC_REG_OFFSET),
		.be	= (E60_TE_REG_BASE + TE_BE_TOP_REG_OFFSET),
		.dsc	= {(E60_TE_REG_BASE + TE_DSC_TOP_REG_OFFSET),
			(E60_TE_REG_BASE + TE_DSC2_TOP_REG_OFFSET)},
		.upload	= {(E60_TE_REG_BASE + TE_UPLOAD0_REG_OFFSET),
			(E60_TE_REG_BASE + TE_UPLOAD1_REG_OFFSET)},
		.mcu	= {(E60_TE_REG_BASE + TE_MCU0_REG_OFFSET),
			(E60_TE_REG_BASE + TE_MCU1_REG_OFFSET)},
		.ciplus	= (E60_TE_REG_BASE + TE_CIPLUS_REG_OFFSET),
	},

	.hw_irq_num	= (E60_TE_IRQ_BASE + TE_HW_IRQ_OFFSET),
	.mcu_irq_num	= {(E60_TE_IRQ_BASE + TE_MCU0_IRQ_OFFSET),
		(E60_TE_IRQ_BASE + TE_MCU1_IRQ_OFFSET)},
	.num_mcu	= 2,
	.num_dsc	= 2,
	.num_upload	= 2,
};
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
static struct te_mem_cfg mem_config_old = {	/* M16P3, O20 ... */
	.region = {
		[TE_MEM_MCU]	= { .size = 0x00200000},	/* 2MB */
		[TE_MEM_SDEC]	= { .size = 0x00900000},	/* 9MB */
		[TE_MEM_SHARED]	= { .size = 0x02800000},	/* 40MB */
		[TE_MEM_PVR]	= { .size = 0x01800000},	/* 24MB */
	},
};
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
/* SICDTV-9433 */
static struct te_mem_cfg mem_config_o22 = {	/* O22 ... */
	.region = {
		[TE_MEM_MCU]	= { .size = 0x00200000},	/* 2MB */
		[TE_MEM_SDEC]	= { .size = 0x00900000},	/* 9MB */
		[TE_MEM_SHARED]	= { .size = 0x02B00000},	/* 43MB */
	},
};
#endif

static struct te_mem_cfg mem_config_current = {	/* O24 ... */
	.region = {
		[TE_MEM_MCU]	= { .size = 0x00200000},	/* 2MB */
		[TE_MEM_SDEC]	= { .size = 0x00900000},	/* 9MB */
		[TE_MEM_SHARED]	= { .size = 0x02900000},	/* 41MB */
	},
};

#ifdef INCLUDE_M23_CHIP_KDRV
/* SICDTV-10766 */
static struct te_mem_cfg mem_config_reduced = {	/* M23 */
	.region = {
		[TE_MEM_MCU]	= { .size = 0x00200000},	/*  2 MB */
		[TE_MEM_SDEC]	= { .size = 0x00900000},	/*  9 MB */
		[TE_MEM_SHARED]	= { .size = 0x02800000},	/* 40 MB */
	},
};

static struct te_mem_cfg mem_config_2k = {	/* M23 HD */
	.region = {
		[TE_MEM_MCU]	= { .size = 0x00200000},	/*  2 MB */
		[TE_MEM_SDEC]	= { .size = 0x00900000},	/*  9 MB */
		[TE_MEM_SHARED]	= { .size = 0x01800000},	/* 24 MB */
	},
};
#endif

static struct te_mem_cfg *mem_cfg;
static struct te_config *config;

static int enable_stcc;
module_param_named(te_enable_stcc, enable_stcc, int, 0640);

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_M23_CHIP_KDRV
/* MUST be called from PreInit functions */
static bool is_plt_env_fhd_or_hd(void)
{
	u32 plt = lx_chip_plt();

	if (plt == LX_CHIP_PLT_FHD || plt == LX_CHIP_PLT_HD)
		return true;
	else
		return false;
}
#endif

void te_cfg_prepare(void)
{
	int i;

	mem_cfg = &mem_config_current; //prevent no define warning

	/* set configs & memory info */
	switch (lx_chip()) {
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		config = &config_o26;
		//mem_cfg = &mem_config_current;
#ifdef CONFIG_TE_ION
		config->use_ion = true;
#endif
		break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
		config = &config_o24;
		//mem_cfg = &mem_config_current;
#ifdef CONFIG_TE_ION
		config->use_ion = true;
#endif
		break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
		config = &config_m23;
		if (is_plt_env_fhd_or_hd()) {
			config->no_pvr_download = true;
			mem_cfg = &mem_config_2k;
		} else {
			config->no_pvr_download = false;
			mem_cfg = &mem_config_reduced;
		}
		break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	case LX_CHIP_O22:
		config = &config_o22;
		mem_cfg = &mem_config_o22;
		if (lx_chip_rev() == LX_CHIP_REV(O22, A0) && enable_stcc != 1) {
			config->no_stcc_bug = true;
			// MCU should run for O22 clock W/A
			config->reg_clock_gate = false;
		} else {
			config->reg_clock_gate = true;
		}
		break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	case LX_CHIP_E60:
		config = &config_e60;
		mem_cfg = &mem_config_old;
		break;
#endif
	default:
		panic("Not supported chip !!! 0x%x\n", lx_chip());
	}

	config->io = common_io_cfg;
	config->clk = common_clk_cfg;

#if CONFIG_LX_BOARD_FPGA
	config->reg_clock_gate = false;
#endif
	/* set memory info to allocate the memory from base driver */
	for (i = 0; i < TE_MEM_REGION_MAX; i++) {
		gMemCfgTE[i].base = mem_cfg->region[i].addr;
		gMemCfgTE[i].size = mem_cfg->region[i].size;
	}
}

void te_cfg_init(struct te_device *dev)
{
	int i;

	dev->cfg = config;
	dev->mem_cfg = mem_cfg;

	for (i = 0; i < TE_MEM_REGION_MAX; i++)
		mem_cfg->region[i].addr = gMemCfgTE[i].base;

	i = TE_MEM_REGION_MAX - 1;
	mem_cfg->total.addr = gMemCfgTE[0].base;
	mem_cfg->total.size = gMemCfgTE[i].base - gMemCfgTE[0].base +
	    gMemCfgTE[i].size;
}

struct te_config *te_get_config(void)
{
	return config;
}

EXPORT_SYMBOL(te_get_config);

struct te_mem_region_info *te_get_mem_region_info(enum te_mem_region region)
{
	if (region == TE_MEM_TOTAL)
		return &mem_cfg->total;
	else if (region < TE_MEM_REGION_MAX)
		return &mem_cfg->region[region];

	return NULL;
}

EXPORT_SYMBOL(te_get_mem_region_info);

/** @} */
