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
 *	@date		2019-05-28
 *	@note		LGDBB O20 Kdriver <-> MCU Register Map
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
	REG_MCU_TO_KDRV_LAST = 	0x53EC,

	/* FW Information */
	REG_SYS_TIME =		0x53F0,
	REG_FW_STATE =		0x53F4,
	REG_FW_VER =		0x53F8,

	/* DEAD Mem Space, can't use it */
	REG_DEAD_0 =	 	0x53FC,

	/* FW Information */
	REG_FW_DATE =		0x5400,

	/* MCU Stall */
	REG_MCU_STALL =		0x5404,

	/* MCU Start Vector Select : Default 0x1 */
	REG_MCU_STARTVECSEL =	0x5408,

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
	REG_FW_SIZE =		0x543C, /* 31:24 iram size, 23:16 dram size */
	REG_INT_SRC =		0x5440, /* 7 : MCU->CPU int src, 0 : CPU->MCU int src */
	REG_GPO =		0x5444, /* 15:8: gpo en(active low, default 0xff), 7:0 gpo value */
	REG_FW_DL_ADDR =	0x5448,
	REG_FW_DL_CTRL = 	0x544C,
	/* ... */

	REG_CLK_TYPE =		0x5460, /* TER: 0, SAT: 1, if it is over 2, that used to set custom clk freq*/
	REG_ADC_TYPE =		0x5464, /* TER: 0, SAT: 1, if it is over 2, that used to set custom adc freq*/
	/* ... */

	REG_DEBUG_MODE =	0x5470, /* Log mode  NONE: 0x0, IPC   0x1, UART  0x2, IPC + UART  0x3, ... */
	REG_DEBUG_FLAG =	0x5474, /* Log Level NONE: 0x0, ERROR 0x1, PRINT 0x2, ERR + PRINT 0x3, DEBUG 0x4, ... */
	/* ... */

	REG_KDRV_TO_MCU_HEAD =	0x5480,
	REG_KDRV_TO_MCU_TAIL =	0x5484,
	REG_KDRV_TO_MCU_STATE =	0x5488,
	REG_KDRV_TO_MCU_COUNT =	0x548C,
	REG_MCU_TO_KDRV_HEAD =	0x5490,
	REG_MCU_TO_KDRV_TAIL =	0x5494,
	REG_MCU_TO_KDRV_STATE =	0x5498,
	REG_MCU_TO_KDRV_COUNT =	0x549C,

	/* ... */

	/* Code Running Information (4 words) */
	REG_INFO_CODE_0 =		0x54C0,
	REG_INFO_CODE_1 =		0x54C4,
	REG_INFO_CODE_2 =		0x54C8,
	REG_INFO_CODE_3 =		0x54CC,

	/* Error Information (4 words) */
	REG_INFO_ERROR_0 =	 	0x54D0,
	REG_INFO_ERROR_1 =	 	0x54D4,
	REG_INFO_ERROR_2 =	 	0x54D8,
	REG_INFO_ERROR_3 =		0x54DC,

	/* ... */

	REG_ISDBT_BADDR =	0x54E0,
	REG_T2_BADDR =		0x54E4,
	REG_DJB_BADDR =		0x54E8,
	REG_RISIC_W_BADDR =	0x54EC,
	REG_RISIC_R_BADDR =	0x54F0,
	REG_DTMB_BADDR =	0x54F4,
	REG_ASYNC =		0x54F8,
	REG_MONITOR =		0x54FC,
} LX_DEMOD_L0_REGMAP;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#define DEMOD_REGMAP_BASE		0xF0045300
#define DEMOD_REGMAP_SIZE		0x200
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#define DEMOD_REGMAP_BASE		0x5300
#define DEMOD_REGMAP_SIZE		DEMOD_O20_SYSTEM_REG_SIZE
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#define DEMOD_REGMAP_BASE		0x0
#define DEMOD_REGMAP_SIZE		0x200
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#define DEMOD_REGMAP_BASE		0x0
#define DEMOD_REGMAP_SIZE		0x200
#endif

#define DEMOD_KDRV_TO_MCU_SIZE	(REG_KDRV_TO_MCU_LAST - REG_KDRV_TO_MCU_BASE + 4)
#define DEMOD_MCU_TO_KDRV_SIZE	(REG_MCU_TO_KDRV_LAST - REG_MCU_TO_KDRV_BASE + 4)

#endif
