/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013-2019 by LG Electronics Inc.
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


/*  @file
 *
 *	demod register map
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-12-30
 *	@note		LGDBB O22 Kdriver <-> MCU Register Map
 */

#ifndef __DBB_DEMOD_L0_REGMAP_H__
#define __DBB_DEMOD_L0_REGMAP_H__

typedef enum {
	/* Kdriver -> MCU Circular Buffer */
	REG_KDRV_TO_MCU_BASE = 	0x5300,
	/* ... */
	REG_KDRV_TO_MCU_LAST = 	0x533C,

	/* MCU -> Kdriver Circular Buffer */
	REG_MCU_TO_KDRV_BASE = 	0x5340,
	/* ... */
	REG_MCU_TO_KDRV_LAST = 	0x53FC,

	REG_FW_DATE =		0x5400,		/* FW Information */
	REG_MCU_STALL =		0x5404,		/* MCU Stall */
	REG_MCU_STARTVECSEL =	0x5408,		/* MCU Start Vector Select : Default 0x1 */
	REG_CLK_N_ADC = 	0x540C,

	REG_TRACE_EN =		0x5410,
	REG_TRACE_FWDN_DONE =	0x5414,
	REG_TRACE_DATA =	0x5418,
	REG_TRACE_PC =		0x541C,

	REG_I2C_SLAVE =		0x5420,
	REG_I2C_HBASE = 	0x5424,
	REG_I2C_TIMEOUT =	0x5428,
	REG_I2C_SCL =		0x542C,

	REG_FW_DL_BASE =	0x5430,
	REG_FW_IRAM_BASE =	0x5434,
	REG_FW_DRAM_BASE =	0x5438,
	REG_FW_SIZE =		0x543C, 	/* 31:24 iram size, 23:16 dram size */

	REG_INT_SRC =		0x5440, 	/* 7 : MCU->CPU int src, 0 : CPU->MCU int src */
	REG_GPO =		0x5444, 	/* 15:8: gpo en(active low, default 0xff), 7:0 gpo value */
	REG_FW_DL_ADDR =	0x5448,
	REG_FW_DL_CTRL = 	0x544C,

	REG_PDEBUG_INST =	0x5450,		/* lx7 debug */
	REG_PFAULT_INFO =	0x5454,		/* lx7 fault */

	RSVD_FOR_M23_1 =	0x5458,
	RSVD_FOR_M23_2 =	0x545C,

	REG_CLK_TYPE =		0x5460, /* TER: 0, SAT: 1, if it is over 2, that used to set custom clk freq*/
	REG_ADC_TYPE =		0x5464, /* TER: 0, SAT: 1, if it is over 2, that used to set custom adc freq*/

	REG_FW_STATE =		0x5468,
	REG_FW_VER =		0x546C,

	REG_SYS_TIME =		0x5470,
	REG_DEBUG_MODE =        0x5474, /* Log mode  NONE: 0x0, IPC   0x1, UART  0x2, IPC + UART  0x3, ... */
	REG_DEBUG_FLAG =        0x5478, /* Log Level NONE: 0x0, ERROR 0x1, PRINT 0x2, ERR + PRINT 0x3, DEBUG 0x4, ... */
	REG_DDR_DATA_INFO = 	0x547C,

	REG_KDRV_TO_MCU_HEAD =	0x5480,
	REG_KDRV_TO_MCU_TAIL =	0x5484,
	REG_KDRV_TO_MCU_STATE =	0x5488,
						//  0x548C,
	REG_MCU_TO_KDRV_HEAD =	0x5490,
	REG_MCU_TO_KDRV_TAIL =	0x5494,
	REG_MCU_TO_KDRV_STATE =	0x5498,
						//  0x549C,

	/* ... */
	REG_EXTRA_FLAG =	0x54A0, /* 31: pe_mon on/off
									   30: atsc3 plp/wav mon */

	REG_RESET_FLAG =	0x54A8,
	REG_ERROR_FLAG =	0x54AC,

	DDR_MCU_TO_DBG_HEAD =	0x54B0,
	DDR_MCU_TO_DBG_TAIL =	0x54B4,
	DDR_MCU_TO_DBG_STATE =	0x54B8,

	/* Code Running Information (4 words) */
	REG_INFO_CODE_0 =	0x54C0,
	REG_INFO_CODE_1 =	0x54C4,
	REG_INFO_CODE_2 =	0x54C8,
	REG_INFO_CODE_3 =	0x54CC,

	/* Error Information (4 words) */
	REG_INFO_ERROR_0 =	0x54D0,
	REG_INFO_ERROR_1 =	0x54D4,
	REG_INFO_ERROR_2 =	0x54D8,
	REG_INFO_ERROR_3 =	0x54DC,

	REG_DDR_OFFSET =	0x54E0,

	REG_ASYNC =		0x54F8,
	REG_MONITOR =		0x54FC,

	REG_ISDBT_BADDR =	0x550C,
	REG_T2_BADDR =		0x5510,
	REG_DJB_BADDR =		0x5514,
	REG_RISIC_W_BADDR =	0x5518,
	REG_RISIC_R_BADDR =	0x551C,
	REG_DTMB_BADDR =	0x5520,

	REG_ATSC3_CSTS_BADDR =	0x5524,
	REG_ATSC3_FDI_BADDR =	0x5528,
	REG_ATSC3_FDI_SIZE =	0x552C,
	REG_ATSC3_L1D_BADDR =	0x5530,
	REG_ATSC3_NOTDI_BADDR =	0x5534,
	REG_ATSC3_CTDI0_BADDR =	0x5558,
	REG_ATSC3_CTDI1_BADDR =	0x555C,
	REG_ATSC3_CTBDI_BADDR =	0x5560,
	REG_ATSC3_CDL_BADDR =	0x5574,
} LX_DEMOD_L0_REGMAP;

typedef enum {
	DDR_ADDR_START =	0xB0000000,
		DDR_INFO_START =	0xB0000000,
			/* ... */
			DDR_MCU_TO_DBG_BASE =	0xB0002000,
			DDR_MCU_TO_DBG_LAST =	0xB0002FFC,
			/* ... */
			DDR_TEST_INFO_BASE =	0xB000C000,
			DDR_DEBUG_INFO_BASE =	0xB000D000,
			DDR_ERROR_INFO_BASE =	0xB000E000,
			DDR_FAULT_INFO_BASE =	0xB000F000,
		DDR_INFO_END =		0xB000FFFC,

		DDR_DATA_START =	0xB0010000,
			DDR_A3_NOTI_TABLE_BASE =	0xB0010000,
			DDR_A3_NOTI_TABLE_LAST =	0xB003FFFC,
		DDR_DATA_END =		0xB003FFFC,

	DDR_ADDR_END =		0xB007FFFC,
} LX_DEMOD_L0_DDRMAP;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#define DEMOD_REGMAP_BASE	0xF0045300
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#define DEMOD_REGMAP_BASE	0x5300
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#define DEMOD_REGMAP_BASE	0x0
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#define DEMOD_REGMAP_BASE	0x0
#endif
#define DEMOD_REGMAP_SIZE	0x300

#define DEMOD_KDRV_TO_MCU_SIZE	(REG_KDRV_TO_MCU_LAST - REG_KDRV_TO_MCU_BASE + 4)
#define DEMOD_MCU_TO_KDRV_SIZE	(REG_MCU_TO_KDRV_LAST - REG_MCU_TO_KDRV_BASE + 4)

#define DEMOD_APB_BASE		0xF0040000

#define DEMOD_MCU_TO_DBG_SIZE	(DDR_MCU_TO_DBG_LAST - DDR_MCU_TO_DBG_BASE + 4)
#endif
