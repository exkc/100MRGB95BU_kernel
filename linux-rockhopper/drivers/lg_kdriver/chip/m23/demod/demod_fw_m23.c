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
 *	demod api warpper
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-06-13
 *	@note
 */

#define DEMOD_TAG "[CHIP.FW] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_Common_API.h>
#include <DBB_DEMOD_L1_TABLE.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/kernel.h>	/**< printk() */
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/errno.h>

#if defined(PLATFORM_FPGA)
#include <asm/io.h>			/**< For ioremap_nocache */
#endif

#include "sys_regs.h"
#include "hma_alloc.h"
#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"
#include "demod_util.h"

#include "demod_common_m23.h"
#include "demod_dvb_m23.h"

#include "demod_fw_m23.h"
#include "demod_util_m23.h"
#include "demod_api_m23.h"
#include "demod_ipc_m23.h"

#include <lg1k/te/demod.h>
/*
#include <O22_DEMOD_ALL_FW_A_2_1_DDR.h>
#define DEMOD_DDR_FW 	O22_DEMOD_ALL_FW_A_2_1
#define DEMOD_FW_NAME 	"O22_DEMOD_FW_A_2_1"
*/

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <WinSock2.h>
#include <O22_DEMOD_ALL_FW_A_2_1_DDR.h>
#define DEMOD_DDR_FW 	O22_DEMOD_ALL_FW_A_2_1
#define DEMOD_FW_NAME 	"O22_DEMOD_FW_A_2_1"

extern LX_DEMOD_L2_Context * DEMOD_GetContext (void);
#define DEMOD_Get_LGDBB_Context DEMOD_GetContext

#include "demod_fw_m23.h"
#include "demod_ipc_m23.h"

#include "demod_common_gui.h"

#else
#error not support platform
#endif

/* macro definition */
#define DEMOD_CHIP_INFO	0x23f0

#if defined(DEMOD_CONFIG_EXT)
#define DEMOD_CHIP_IF	LX_DEMOD_L0_IF_EXT
#else
#define DEMOD_CHIP_IF	LX_DEMOD_L0_IF_SOC
#endif

#define FW_MAKER_MAGIC	"DEMOD_FW"

#define SET_INIT		1
#define REL_INIT		0

//#define DEMOD_SPEND_TIME_CHECK
#if defined(DEMOD_SPEND_TIME_CHECK)
#define SPEND_TIME_START() \
	start_clock = DEMOD_L0_SystemClock();

#define SPEND_TIME_CHECK(desc) { \
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us); \
	DEMOD_INFO("TC: %s, spend %3u.%03ums\n", desc, spend_ms, spend_us); \
	start_clock = DEMOD_L0_SystemClock(); \
}
#define SPEND_TIME_CHECK_MSG(desc) { \
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us); \
	DEMOD_NOTI("TC: %s, spend %3u.%03ums\n", desc, spend_ms, spend_us); \
	start_clock = DEMOD_L0_SystemClock(); \
}

#else
#define SPEND_TIME_START()
#define SPEND_TIME_CHECK(desc)
#define SPEND_TIME_CHECK_MSG(desc) { \
	DEMOD_NOTI("%s done\n", desc); \
}

#endif

static void _DEMOD_M23_CTOP_DBB_Init (int init) {
	DEMOD_PRINT("init %d\n", init);

	switch(init) {
		case SET_INIT: {
#if defined(PLATFORM_FPGA)
			volatile UINT32 * ctop_reg = (volatile UINT32 *)ioremap(0xC6111014, sizeof(UINT32));
			if (NULL == ctop_reg) {
				DEMOD_ERROR("ioremap for te_reg failed\n");
				return;
			}

			DEMOD_DEBUG("ctop_reg org 0x%08x\n", *ctop_reg);
			*ctop_reg = 0x0;
			DEMOD_DEBUG("ctop_reg chk 0x%08x\n", *ctop_reg);
			iounmap((void *)ctop_reg);
			ctop_reg = NULL;
			DEMOD_NOTI("WA: ctrl ctop reg to dbb deactivation\n");
#endif
			DEMOD_PRINT("set Init\n");
			break;
		}
					   
		case REL_INIT: {
#if defined(PLATFORM_FPGA)
			volatile UINT32 * ctop_reg = (volatile UINT32 *)ioremap(0xC6111014, sizeof(UINT32));
			if (NULL == ctop_reg) {
				DEMOD_ERROR("ioremap for te_reg failed\n");
				return;
			}
			DEMOD_DEBUG("ctop_reg org 0x%08x\n", *ctop_reg);
			*ctop_reg = 0x1;
			DEMOD_DEBUG("ctop_reg chk 0x%08x\n", *ctop_reg);
			iounmap((void *)ctop_reg);
			ctop_reg = NULL;
			DEMOD_NOTI("WA: ctrl ctop reg to dbb activation\n");
#endif
			DEMOD_PRINT("release init\n");
			break;
		}
		default:
			DEMOD_INFO("invalid init %d\n", init);
			break;
	}
}

static void	_DEMOD_M23_CTOP_DBB_REG_Init (int init)	{

	DEMOD_PRINT("init %d\n", init);
	//IP_CTRL_DBB

	switch(init) {
		case SET_INIT:

			CTOP_CTRL_M23Ax_RdFL(IP_CTRL_DBB, ipw_dbb_005);
			CTOP_CTRL_M23Ax_Wr01(IP_CTRL_DBB, ipw_dbb_005,	reg_dbb_reg_init,	1);
			CTOP_CTRL_M23Ax_WrFL(IP_CTRL_DBB, ipw_dbb_005);

			DEMOD_PRINT("set Init\n");
			break;
		case REL_INIT:

			CTOP_CTRL_M23Ax_RdFL(IP_CTRL_DBB, ipw_dbb_005);
			CTOP_CTRL_M23Ax_Wr01(IP_CTRL_DBB, ipw_dbb_005,	reg_dbb_reg_init,	0);
			CTOP_CTRL_M23Ax_WrFL(IP_CTRL_DBB, ipw_dbb_005);

			DEMOD_PRINT("release init\n");
			break;
		default:
			DEMOD_INFO("invalid init %d\n", init);
			break;
	}
}

static void	_DEMOD_M23_CTOP_DBB_ADC_Init (int init) {

	DEMOD_PRINT("init %d\n", init);
	
	switch(init) {
		case SET_INIT:
			CTOP_CTRL_M23Ax_RdFL(MIP_ADC_CTRL_BMC, mip_adc02);
			CTOP_CTRL_M23Ax_Wr01(MIP_ADC_CTRL_BMC, mip_adc02, reg_admd_bias_pdb, 0);
			CTOP_CTRL_M23Ax_WrFL(MIP_ADC_CTRL_BMC, mip_adc02);

			DEMOD_PRINT("set Init\n");
			break;
		case REL_INIT:
			CTOP_CTRL_M23Ax_RdFL(MIP_ADC_CTRL_BMC, mip_adc02);
			CTOP_CTRL_M23Ax_Wr01(MIP_ADC_CTRL_BMC, mip_adc02, reg_admd_bias_pdb, 1);
			CTOP_CTRL_M23Ax_WrFL(MIP_ADC_CTRL_BMC, mip_adc02);

			DEMOD_PRINT("release init\n");
			break;
		default:
			DEMOD_INFO("invalid init %d\n", init);
			break;
	}
}

#include <asm/io.h>
#define DEMOD_APB_REG_WR(address, data) \
	do { \
		volatile UINT32 * dbb_ip_reg = NULL; \
		dbb_ip_reg = (volatile UINT32 *)ioremap(address, sizeof(UINT32)); \
		if(dbb_ip_reg == NULL) { DEMOD_WARN("failed ioremap for 0x%08x\n", address); break; } \
		*dbb_ip_reg = data; \
		iounmap((void *)dbb_ip_reg); \
		dbb_ip_reg = NULL; \
	} while(0); \

#define DEMOD_APB_REG_RD(address,data) \
	do { \
		volatile UINT32 * dbb_ip_reg = NULL; \
		dbb_ip_reg = (volatile UINT32 *)ioremap(address, sizeof(UINT32)); \
		if(dbb_ip_reg == NULL) { DEMOD_WARN("failed ioremap for 0x%08x\n", address); break; } \
		data = *dbb_ip_reg; \
		iounmap((void *)dbb_ip_reg); \
		dbb_ip_reg = NULL; \
	} while(0); \

#include "demod_cfg.h"

#define ATSC3_MEM_OFFSET_FDI	0x00000000
#define ATSC3_MEM_LENGTH_FDI	0x00400000		// 0x400000 4MB
#define ATSC3_MEM_OFFSET_L1D	ATSC3_MEM_OFFSET_FDI + ATSC3_MEM_LENGTH_FDI
#define ATSC3_MEM_LENGTH_L1D	0x00100000		// 0x100000 1MB

#define ATSC3_MEM_OFFSET_NOTDI	ATSC3_MEM_OFFSET_L1D + ATSC3_MEM_LENGTH_L1D
#define ATSC3_MEM_OFFSET_CDL	ATSC3_MEM_OFFSET_L1D + ATSC3_MEM_LENGTH_L1D
#define ATSC3_MEM_OFFSET_CTBDI	ATSC3_MEM_OFFSET_L1D + ATSC3_MEM_LENGTH_L1D + 0x800000
#define ATSC3_MEM_OFFSET_CTDI0	ATSC3_MEM_OFFSET_L1D + ATSC3_MEM_LENGTH_L1D
#define ATSC3_MEM_OFFSET_CTDI1	ATSC3_MEM_OFFSET_L1D + ATSC3_MEM_LENGTH_L1D + 0x800000
#define ATSC3_MEM_LENGTH_STREAM	0x01000000

#define ATSC3_MEM_OFFSET_CSTS	ATSC3_MEM_OFFSET_FDI + ATSC3_MEM_LENGTH_FDI + ATSC3_MEM_LENGTH_STREAM
#define ATSC3_MEM_LENGTH_CSTS	0x00140000

static void _DEMOD_M23_DBB_IP_ClrBaseAddr (void) {
	UINT32 baddr;

	/* if not defined base address of each standards, set as gMemCfgDEMOD.memory_base to avoid memory bus violation */
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_FDI_BADDR,   0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_L1D_BADDR,   0x00000000);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_NOTDI_BADDR, 0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CDL_BADDR,   0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTBDI_BADDR, 0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI0_BADDR, 0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI1_BADDR, 0x00000000);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CSTS_BADDR,  0x00000000);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ISDBT_BADDR,       0x00000000);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_DTMB_BADDR,        0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_T2_BADDR,          0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_DJB_BADDR,         0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_RISIC_W_BADDR,     0x00000000);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_RISIC_R_BADDR,     0x00000000);

	/* check baseaddr registers */
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_FDI_BADDR,   baddr); DEMOD_INFO("check ATSC3_FDI_BADDR   (@0x%04x) %08x == %08x\n", REG_ATSC3_FDI_BADDR, baddr,   gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_FDI);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_L1D_BADDR,   baddr); DEMOD_INFO("check ATSC3_L1D_BADDR   (@0x%04x) %08x == %08x\n", REG_ATSC3_L1D_BADDR, baddr,   gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_L1D);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_NOTDI_BADDR, baddr); DEMOD_INFO("check ATSC3_NOTDI_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_NOTDI_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_NOTDI);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CDL_BADDR,   baddr); DEMOD_INFO("check ATSC3_CDL_BADDR   (@0x%04x) %08x == %08x\n", REG_ATSC3_CDL_BADDR, baddr,   gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CDL);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTBDI_BADDR, baddr); DEMOD_INFO("check ATSC3_CTBDI_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_CTBDI_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTBDI);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI0_BADDR, baddr); DEMOD_INFO("check ATSC3_CTDI0_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_CTDI0_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTDI0);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI1_BADDR, baddr); DEMOD_INFO("check ATSC3_CTDI1_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_CTDI1_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTDI1);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CSTS_BADDR,  baddr); DEMOD_INFO("check ATSC3_CSTS_BADDR  (@0x%04x) %08x == %08x\n", REG_ATSC3_CSTS_BADDR, baddr,  gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CSTS);

	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ISDBT_BADDR,       baddr); DEMOD_INFO("check ISDBT_BADDR       (@0x%04x) %08x == %08x\n", REG_ISDBT_BADDR, baddr,       gMemCfgDEMOD_ISDBT.memory_base);

	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_DTMB_BADDR,        baddr); DEMOD_INFO("check DTMB_BADDR        (@0x%04x) %08x == %08x\n", REG_DTMB_BADDR, baddr,        gMemCfgDEMOD_DTMB.memory_base);

	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_T2_BADDR,          baddr); DEMOD_INFO("check T2_BADDR          (@0x%04x) %08x == %08x\n", REG_T2_BADDR, baddr,          gMemCfgDEMOD_DVB_TDI.memory_base + 0x00000000);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_DJB_BADDR,         baddr); DEMOD_INFO("check DJB_BADDR         (@0x%04x) %08x == %08x\n", REG_DJB_BADDR, baddr,         gMemCfgDEMOD_DVB_TDI.memory_base + 0x00680000);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_RISIC_W_BADDR,     baddr); DEMOD_INFO("check RISIC_W_BADDR     (@0x%04x) %08x == %08x\n", REG_RISIC_W_BADDR, baddr,     gMemCfgDEMOD_DVB_TDI.memory_base + 0x00780000);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_RISIC_R_BADDR,     baddr); DEMOD_INFO("check RISIC_R_BADDR     (@0x%04x) %08x == %08x\n", REG_RISIC_R_BADDR, baddr,     gMemCfgDEMOD_DVB_TDI.memory_base + 0x00780000);

	return;
}


static void _DEMOD_M23_DBB_IP_SetBaseAddr (void) {
	UINT32 baddr;

	/* if not defined base address of each standards, set as gMemCfgDEMOD.memory_base to avoid memory bus violation */
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_FDI_BADDR,   (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_FDI)     : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_FDI_SIZE,    ATSC3_MEM_LENGTH_FDI);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_L1D_BADDR,   (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_L1D)     : gMemCfgDEMOD.memory_base);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_NOTDI_BADDR, (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_NOTDI)   : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CDL_BADDR,   (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CDL)     : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTBDI_BADDR, (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTBDI)   : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI0_BADDR, (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTDI0)   : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI1_BADDR, (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTDI1)   : gMemCfgDEMOD.memory_base);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ATSC3_CSTS_BADDR,  (gMemCfgDEMOD_ATSC3.memory_base)   ? (gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CSTS)   : gMemCfgDEMOD.memory_base);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_ISDBT_BADDR,       (gMemCfgDEMOD_ISDBT.memory_base)   ? (gMemCfgDEMOD_ISDBT.memory_base + 0x00000000)   : gMemCfgDEMOD.memory_base);

	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_DTMB_BADDR,        (gMemCfgDEMOD_DTMB.memory_base)    ? (gMemCfgDEMOD_DTMB.memory_base + 0x00000000)    : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_T2_BADDR,          (gMemCfgDEMOD_DVB_TDI.memory_base) ? (gMemCfgDEMOD_DVB_TDI.memory_base + 0x00000000) : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_DJB_BADDR,         (gMemCfgDEMOD_DVB_TDI.memory_base) ? (gMemCfgDEMOD_DVB_TDI.memory_base + 0x00680000) : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_RISIC_W_BADDR,     (gMemCfgDEMOD_DVB_TDI.memory_base) ? (gMemCfgDEMOD_DVB_TDI.memory_base + 0x00780000) : gMemCfgDEMOD.memory_base);
	DEMOD_APB_REG_WR(M23_DBB_IP_TOP_BASE + REG_RISIC_R_BADDR,     (gMemCfgDEMOD_DVB_TDI.memory_base) ? (gMemCfgDEMOD_DVB_TDI.memory_base + 0x00780000) : gMemCfgDEMOD.memory_base);

	/* check baseaddr registers */
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_FDI_BADDR,   baddr); DEMOD_INFO("check ATSC3_FDI_BADDR   (@0x%04x) %08x == %08x\n", REG_ATSC3_FDI_BADDR, baddr,   gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_FDI);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_L1D_BADDR,   baddr); DEMOD_INFO("check ATSC3_L1D_BADDR   (@0x%04x) %08x == %08x\n", REG_ATSC3_L1D_BADDR, baddr,   gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_L1D);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_NOTDI_BADDR, baddr); DEMOD_INFO("check ATSC3_NOTDI_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_NOTDI_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_NOTDI);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CDL_BADDR,   baddr); DEMOD_INFO("check ATSC3_CDL_BADDR   (@0x%04x) %08x == %08x\n", REG_ATSC3_CDL_BADDR, baddr,   gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CDL);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTBDI_BADDR, baddr); DEMOD_INFO("check ATSC3_CTBDI_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_CTBDI_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTBDI);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI0_BADDR, baddr); DEMOD_INFO("check ATSC3_CTDI0_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_CTDI0_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTDI0);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CTDI1_BADDR, baddr); DEMOD_INFO("check ATSC3_CTDI1_BADDR (@0x%04x) %08x == %08x\n", REG_ATSC3_CTDI1_BADDR, baddr, gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CTDI1);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ATSC3_CSTS_BADDR,  baddr); DEMOD_INFO("check ATSC3_CSTS_BADDR  (@0x%04x) %08x == %08x\n", REG_ATSC3_CSTS_BADDR, baddr,  gMemCfgDEMOD_ATSC3.memory_base + ATSC3_MEM_OFFSET_CSTS);

	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_ISDBT_BADDR,       baddr); DEMOD_INFO("check ISDBT_BADDR       (@0x%04x) %08x == %08x\n", REG_ISDBT_BADDR, baddr,       gMemCfgDEMOD_ISDBT.memory_base);

	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_DTMB_BADDR,        baddr); DEMOD_INFO("check DTMB_BADDR        (@0x%04x) %08x == %08x\n", REG_DTMB_BADDR, baddr,        gMemCfgDEMOD_DTMB.memory_base);

	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_T2_BADDR,          baddr); DEMOD_INFO("check T2_BADDR          (@0x%04x) %08x == %08x\n", REG_T2_BADDR, baddr,          gMemCfgDEMOD_DVB_TDI.memory_base + 0x00000000);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_DJB_BADDR,         baddr); DEMOD_INFO("check DJB_BADDR         (@0x%04x) %08x == %08x\n", REG_DJB_BADDR, baddr,         gMemCfgDEMOD_DVB_TDI.memory_base + 0x00680000);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_RISIC_W_BADDR,     baddr); DEMOD_INFO("check RISIC_W_BADDR     (@0x%04x) %08x == %08x\n", REG_RISIC_W_BADDR, baddr,     gMemCfgDEMOD_DVB_TDI.memory_base + 0x00780000);
	DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_RISIC_R_BADDR,     baddr); DEMOD_INFO("check RISIC_R_BADDR     (@0x%04x) %08x == %08x\n", REG_RISIC_R_BADDR, baddr,     gMemCfgDEMOD_DVB_TDI.memory_base + 0x00780000);

	return;
}

static void _DEMOD_M23_DBB_IP_Reset (LX_DEMOD_OPER_MODE_T opmode)	{
	volatile UINT32 * dbb_reg_0000 = (volatile UINT32 *)ioremap(M23_DBB_IP_TOP_BASE + 0x0000, sizeof(UINT32));
	volatile UINT32 * dbb_reg_0500 = (volatile UINT32 *)ioremap(M23_DBB_IP_TOP_BASE + 0x0500, sizeof(UINT32));
	volatile UINT32 * dbb_reg_0504 = (volatile UINT32 *)ioremap(M23_DBB_IP_TOP_BASE + 0x0504, sizeof(UINT32));
	volatile UINT32 * dbb_reg_540c = (volatile UINT32 *)ioremap(M23_DBB_IP_TOP_BASE + 0x540c, sizeof(UINT32));

	UINT32 spend_us;
	UINT32 spend_ms;
	UINT64 start_clock;

	UINT8 dma_req_clear_flag = 0;

	DEMOD_PRINT("IP Reset for opmode %d\n", opmode);

	if (!dbb_reg_0000 || !dbb_reg_0500 || !dbb_reg_0504 || !dbb_reg_540c) {
		DEMOD_ERROR("failed ioremap, %p,%p,%p,%p\n", dbb_reg_0000, dbb_reg_0500, dbb_reg_0504, dbb_reg_540c);
		return;
	}

	*dbb_reg_540c = *dbb_reg_540c & 0xfffffffb; // dbb fifo disable
	*dbb_reg_0000 = *dbb_reg_0000 & 0x7fffffff; // demod sync1rstb reset

	if((opmode == LX_DEMOD_DVBT) || (opmode == LX_DEMOD_DVBT2))
	{
		*dbb_reg_0500 = (*dbb_reg_0500 & 0xfffffeff) | 0x00000100; // dma rst req

		start_clock = DEMOD_L0_SystemClock();
		do
		{
			if((*dbb_reg_0504 & 0x00000001) == 1) // dma rst ack
			{
				DEMOD_L0_system_wait (1);
				*dbb_reg_0500 = *dbb_reg_0500 & 0xfffffeff; // dma rst req clear
				DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
				dma_req_clear_flag = 1;
				break;
			}
		} while (spend_ms < 50);

		DEMOD_NOTI("DMA req clear flag %d, spend %u ms\n", dma_req_clear_flag, spend_ms);
	}
	DEMOD_L0_system_wait (10);

	DEMOD_NOTI("dbb ip fifo disable & sync1 reset done\n");

	*dbb_reg_540c = *dbb_reg_540c & 0xfffffffd; // dbb clock gating
	DEMOD_NOTI("dbb ip clock gating done\n");

	iounmap((void *)dbb_reg_0000);
	iounmap((void *)dbb_reg_0500);
	iounmap((void *)dbb_reg_0504);
	iounmap((void *)dbb_reg_540c);
	return;
}

static int _DEMOD_M23_ResetFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int ret = NO_DEMOD_ERROR;

	// have to clear fw type, fw ver before send SYSTEM_INIT to mcu
	ret = DEMOD_L1_API_FinishFirmware(pFrontend->demod);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_API_FinishFirmware with ret %d\n", ret);
		return ret;
	}

	ret = DEMOD_L1_IPC_Send_Sync(pFrontend->demod, CMD_TYPE_SYSTEM_INIT, 0, NULL, 0);

	if (ret != NO_DEMOD_ERROR) {
		DEMOD_NOTI("send SYSTEM_INIT fail, ret %d\n", ret);
		pFrontend->demod->fw_state = DEMOD_FW_STATE_FAULT;
		return ret;
	}

	//usleep_range(10000,11000);	/* 10ms ~ 11ms */
	DEMOD_L0_system_wait(10);

	pFrontend->demod->fw_ver = 0;
	pFrontend->demod->fw_date = 0;

	return NO_DEMOD_ERROR;
}

static int _DEMOD_M23_StopFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int ret = NO_DEMOD_ERROR;

	ret = DEMOD_L1_API_FinishFirmware(pFrontend->demod);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_API_FinishFirmware with ret %d\n", ret);
		return ret;
	}
	/* WA for Integration FPGA test */
	//_DEMOD_M23_CTOP_DBB_Init(SET_INIT);

	pFrontend->demod->fw_ver = 0;
	pFrontend->demod->fw_date = 0;

	return ret;
}

static int _DEMOD_M23_InitFirmware (LX_DEMOD_L2_Context * pFrontend, UINT32 fw_clk, UINT32 adc_clk) {
	int		ret = NO_DEMOD_ERROR;
#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64	start_clock;
	UINT64	spend_clock;
	UINT32	spend_us;
	UINT32	spend_ms;
#endif
	SPEND_TIME_START();

	DEMOD_NOTI("check fw_type @context %d\n", pFrontend->demod->chip->fw_type);

	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RESET) {
			DEMOD_INFO("reg set\n");
			_DEMOD_M23_CTOP_DBB_REG_Init(SET_INIT);
			SPEND_TIME_CHECK("REG_INIT SET");

			DEMOD_L0_system_wait(1);
			SPEND_TIME_CHECK("wait(1)");

			DEMOD_INFO("reg clr\n");
			_DEMOD_M23_CTOP_DBB_REG_Init(REL_INIT);
			SPEND_TIME_CHECK("REG_INIT RELEASE");

			//DEMOD_INFO("clr baseaddr\n");
			//_DEMOD_M23_DBB_IP_ClrBaseAddr();
			DEMOD_NOTI("set baseaddr\n");
			_DEMOD_M23_DBB_IP_SetBaseAddr();

		} else {
			DEMOD_INFO("reg reset skip\n");
		}
	}

	/* MCU FW control register init */
	DEMOD_INFO("init %u,%u\n", fw_clk, adc_clk);
	ret = DEMOD_L1_API_InitFirmware(pFrontend->demod, fw_clk, adc_clk);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_API_InitFirmware with ret %d\n", ret);
		return ret;
	}
	SPEND_TIME_CHECK("InitFirmware");

	return NO_DEMOD_ERROR;
}

static int _DEMOD_M23_MemSetFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int		ret = NO_DEMOD_ERROR;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#if defined(INCLUDE_KDRV_TE)
	//if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RESET)
	if (1)
	{	UINT32 fw_ver = 0;

		UINT32 ddr_base = gMemCfgDEMOD_FW.memory_base;
		UINT32 ddr_size = gMemCfgDEMOD_FW.memory_size;
		UINT32 ddr_offset = 0;

		DEMOD_APB_REG_RD(M23_DBB_IP_TOP_BASE + REG_FW_VER,  fw_ver);

		DEMOD_NOTI("fw ver check 0x%08x\n", fw_ver);

		if (((fw_ver & 0xFFFF) >= 0x0009) && ((fw_ver & 0xFFFF) < 0x000C) ) {
			ddr_base   = gMemCfgDEMOD.memory_base;
			ddr_offset = gMemCfgDEMOD_FW.memory_base - gMemCfgDEMOD.memory_base;
			ddr_size   = ddr_offset + gMemCfgDEMOD_FW.memory_size;
		}

		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_DDR_OFFSET, 4, &ddr_offset))
			DEMOD_WARN("ddr offset write failed\n");

		ret = te_mcu_set_demod_sram_addr(ddr_base, ddr_size);
		if (ret) {
			DEMOD_WARN("set demod sram failed with %d\n", ret);
		} else {
			DEMOD_NOTI("set demod sram addr succeed, 0x%08x, %u\n", ddr_base, ddr_size);
		}
	} else {
		DEMOD_INFO("set demod sram skip\n");
	}
#else
	DEMOD_WARN("need te kdrv\n");
	return -ERROR_DEMOD_FW_NOT_READY;
#endif
#endif

	return NO_DEMOD_ERROR;
}

static int _DEMOD_M23_StartFirmware (LX_DEMOD_L2_Context * pFrontend)
{
	int  			tryCount = 0;
	int  			ret = 0;

#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64			start_clock;
	UINT64			spend_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
#endif
	SPEND_TIME_START();

	/* WA for Integration FPGA test */
	//_DEMOD_M23_CTOP_DBB_Init(REL_INIT);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#if defined(INCLUDE_KDRV_TE)
	ret = te_mcu_enable_demod(true);
	if (ret && (-EBUSY != ret)) {	// except EBUSY (alread enabled)
		DEMOD_WARN("te_mcu_enable_demod(true) failed with %d\n", ret);
		return -ERROR_DEMOD_FW_NOT_READY;
	} else {
		DEMOD_NOTI("te_mcu_enable_demod(true) succeed with %d\n", ret);
		ret = NO_DEMOD_ERROR;
	}
#endif
#endif

	tryCount = 10;
	do {
		ret = DEMOD_L1_API_StartFirmware(pFrontend->demod);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_API_StartFirmware() 0x%02x: %s\n",
				ret, DEMOD_L1_API_Error_Text(ret));
			DEMOD_L0_system_wait(3);
			continue;
		}
	} while ((tryCount-- > 0) && (ret != NO_DEMOD_ERROR));

	if(ret != NO_DEMOD_ERROR) 	{
		DEMOD_ERROR("failed f/w downloading with ret %d, tryCount %d\n", ret, tryCount);
		return ret;
	}

	SPEND_TIME_CHECK("StartFirmware");

	DEMOD_L0_system_wait(10);
	SPEND_TIME_CHECK("wait(10)");

	tryCount = 1000;
	while ((tryCount-- > 0) && ((ret = DEMOD_L1_API_IsReady(pFrontend->demod)) != NO_DEMOD_ERROR)) {
		DEMOD_L0_system_wait(1);
	}
	SPEND_TIME_CHECK("IsReady");

	DEMOD_NOTI("FW ver 0x%08x, date 0x%08x\n", pFrontend->demod->fw_ver, pFrontend->demod->fw_date);

	if(ret != NO_DEMOD_ERROR) 	{
		DEMOD_ERROR("failed f/w start with ret %d, tryCount %d\n", ret, tryCount);
		return ret;
	}

	return NO_DEMOD_ERROR;
}

static int _DEMOD_M23_WaitFirmware (void)
{
	int ret = NO_DEMOD_ERROR;
	int	retry = 100;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#if defined(INCLUDE_KDRV_TE)
	// wait te_mcu ready during 3s
	DEMOD_INFO("wait until te_mcu ready...\n");

	do {
		ret = te_mcu_get_demod_ready();

		if (true == ret) {
			DEMOD_NOTI("te mcu ready, retry %d\n", 100 - retry);
			return NO_DEMOD_ERROR;
		}
		DEMOD_INFO("wait te mcu ready... ret %d, retry %d\n", ret, 100 - retry);
		DEMOD_L0_system_wait(30);
	} while (--retry);

	DEMOD_ERROR("wait te_mcu ready failed\n");
	ret = -ERROR_DEMOD_FW_NOT_READY;
#endif
#endif
	return ret;
}

static int _DEMOD_M23_TE_init_done = 0;
static int _DEMOD_M23_TE_MCU_PreRecovery (void * data);
static int _DEMOD_M23_TE_MCU_PostRecovery (void * data);
static int _DEMOD_M23_TE_MCU_Suspend (void * data);
static int _DEMOD_M23_TE_MCU_Resume (void * data);

static int _DEMOD_M23_FW_Initialize(demod_fw_type fw_type) {
	LX_DEMOD_L2_Context *	pFrontend = DEMOD_Get_LGDBB_Context();

	UINT32			fw_clk = 0;
	UINT32			adc_clk = 0;
	UINT32			chip_rev = lx_chip_rev();
	int 			ret = NO_DEMOD_ERROR;

	UINT64 			begin_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
	UINT64			spend_clock;
#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64 			start_clock;
#endif
	begin_clock = DEMOD_L0_SystemClock();

	SPEND_TIME_START();

	if ((pFrontend->demod->fw_state == DEMOD_FW_STATE_RESET) || (pFrontend->demod->fw_state == DEMOD_FW_STATE_FAULT)) {
		DEMOD_NOTI("skip, already drv mlock, fw_state %d\n", pFrontend->demod->fw_state);
	} else {
		/* first firmware loading after boot */
		DEMOD_LockDevice();
		DEMOD_INFO("got drv mlock\n");
	}
	SPEND_TIME_CHECK("got drv mlock");

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	fw_clk = pFrontend->sysclk;
	adc_clk = pFrontend->adcclk;
#endif
#if defined(PLATFORM_FPGA)
	// o22_fpga, for fpga integrated test
	fw_clk = DEMOD_PROP_CLOCK_MODE_800MHZ;
	if (fw_type == DEMOD_FW_TYPE_TER) {
		adc_clk = DEMOD_PROP_ADC_ADCCLK_24MHZ;
	} else {
		adc_clk = DEMOD_PROP_ADC_ADCCLK_60P8MHZ;
	}
#endif

	if (fw_clk == 0 || adc_clk == 0) {
		fw_clk = DEMOD_PROP_CLOCK_MODE_800MHZ;		// TE MCU clock
		if (fw_type == DEMOD_FW_TYPE_TER) {
			adc_clk = DEMOD_PROP_ADC_ADCCLK_24MHZ;
		} else if (fw_type == DEMOD_FW_TYPE_SAT) {
			adc_clk = DEMOD_PROP_ADC_ADCCLK_124MHZ;
		} else {
			DEMOD_ERROR("fw_type invalid %d\n", fw_type);
			return ERROR_DEMOD_FW_INIT;
		}
	}

	DEMOD_INFO("set chip info 0x%04X\n", DEMOD_CHIP_INFO);
	DEMOD_L2_Set_ChipInfo(pFrontend, DEMOD_CHIP_INFO, DEMOD_CHIP_IF);

	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_device_unlock;
		}
		DEMOD_NOTI("got dev mlock\n");

		if (NO_DEMOD_ERROR != _DEMOD_M23_StopFirmware(pFrontend)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("StopFirmare");

		DEMOD_M23_IPC_Enable(FALSE);
		SPEND_TIME_CHECK("IPC Disable");

		DEMOD_M23_IPC_Reset();
		SPEND_TIME_CHECK("IPC_Reset");

		if (NO_DEMOD_ERROR != _DEMOD_M23_InitFirmware(pFrontend, fw_clk, adc_clk)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("InitFirmware");

		if (NO_DEMOD_ERROR != _DEMOD_M23_WaitFirmware()) {
			DEMOD_ERROR("WaitFirmware failed\n");
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("WaitFirmware");

		if (NO_DEMOD_ERROR != _DEMOD_M23_MemSetFirmware(pFrontend)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("MemSetFirmware");

	} else {
		DEMOD_NOTI("fw re-init for type change, fw_type %d, fw_state %d\n", pFrontend->demod->chip->fw_type, pFrontend->demod->fw_state);

		if (NO_DEMOD_ERROR != DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0)) {
			DEMOD_NOTI("faild SoftRst, fw_state %d\n", pFrontend->demod->fw_state);
			goto retry_fw_init_cause_ipc_error;
		}
		SPEND_TIME_CHECK_MSG("SoftRst");

		if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip))
			return ERROR_DEMOD_LOADING_FIRMWARE;

		DEMOD_NOTI("got dev mlock\n");

		DEMOD_L0_system_wait(10);
		SPEND_TIME_CHECK("wait(10)");

		if (NO_DEMOD_ERROR != _DEMOD_M23_ResetFirmware(pFrontend)) {
			DEMOD_NOTI("faild ResetFirmware, retry forced fw init\n");
			goto retry_fw_init_cause_ipc_error_with_api_unlock;
		}
		SPEND_TIME_CHECK("ResetFirmware");

		pFrontend->demod->fw_state = DEMOD_FW_STATE_RESET;
		DEMOD_M23_IPC_Enable(FALSE);
		SPEND_TIME_CHECK("IPC Disable");

		if (NO_DEMOD_ERROR != _DEMOD_M23_InitFirmware(pFrontend, fw_clk, adc_clk)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("InitFirmware");

		if (NO_DEMOD_ERROR != _DEMOD_M23_WaitFirmware()) {
			DEMOD_ERROR("WaitFirmware failed\n");
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("WaitFirmware");
	}

	if(DEMOD_L1_TABLE_Update(pFrontend->demod) != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_TABLE_Update failed\n");
		ret = -ERROR_DEMOD_ERROR;
		goto return_with_device_unlock;
	}
	SPEND_TIME_CHECK("L1_TABLE update");

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_DDR_DATA_INFO, 4, &chip_rev)) {
		DEMOD_ERROR("failed chip rev write!!!\n");
	} else {
		DEMOD_NOTI("write L1_TABLE, data info (0x%04x) was written\n", chip_rev);
	}

	if (NO_DEMOD_ERROR != _DEMOD_M23_StartFirmware(pFrontend)) {
		ret = ERROR_DEMOD_LOADING_FIRMWARE;
		goto return_with_api_unlock;
	}
	SPEND_TIME_CHECK("StartFirmware");

	DEMOD_M23_IPC_Enable(TRUE);
	SPEND_TIME_CHECK("IPC Enable");

	DEMOD_PRINT("try release dev mlock\n");
	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
	DEMOD_PRINT("dev mlock released\n");
	SPEND_TIME_CHECK("rel dev mlock");

	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("DEMOD_L2_Init Failed\n");
		ret = -ERROR_DEMOD_ERROR;
		goto return_with_device_unlock;
	}
	SPEND_TIME_CHECK("L2_Init");

	spend_clock = DEMOD_L0_CalcSpendClock(begin_clock, &spend_ms, &spend_us);
	DEMOD_INFO("TC: FW_Initialize, total spend %3u.%03ums\n",spend_ms, spend_us);
	DEMOD_NOTI("fw init done\n");

	pFrontend->demod->chip->fw_type = fw_type;
	DEMOD_UnlockDevice();
	DEMOD_INFO("rel drv mlock\n");

	DEMOD_CHIP_PROC_Init();

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	if (_DEMOD_M23_TE_init_done == 0) {
		ret = te_mcu_register_demod_rcallback(_DEMOD_M23_TE_MCU_PreRecovery, _DEMOD_M23_TE_MCU_PostRecovery, _DEMOD_M23_TE_MCU_Suspend, _DEMOD_M23_TE_MCU_Resume, pFrontend);
		if (ret) {
			DEMOD_ERROR("failed register to te_mcu with %d\n", ret);
		}
		_DEMOD_M23_TE_init_done = 1;
	} else {
		DEMOD_INFO("te+demod init already done");
	}
#endif
	return NO_DEMOD_ERROR;

return_with_api_unlock:
	DEMOD_NOTI("try demod chip lock release caused by ret %d\n", ret);
	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
	DEMOD_INFO("rel dev mlock\n");
	DEMOD_NOTI("demod chip lock released\n");
return_with_device_unlock:
	DEMOD_UnlockDevice();
	DEMOD_INFO("rel drv mlock\n");
	DEMOD_NOTI("fw init failed caused by ret %d\n", ret);
	pFrontend->demod->chip->fw_type = DEMOD_FW_TYPE_INV;
	return ret;
retry_fw_init_cause_ipc_error_with_api_unlock:
	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
	DEMOD_INFO("rel dev mlock\n");
retry_fw_init_cause_ipc_error:
	if (pFrontend->demod->fw_state > DEMOD_FW_STATE_RUN) {
		DEMOD_NOTI("fw re-init skip cause by fw_state %d\n", pFrontend->demod->fw_state);
		DEMOD_UnlockDevice();
		DEMOD_INFO("rel drv mlock\n");

		spend_clock = DEMOD_L0_SystemClock();
		while (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN) {
			DEMOD_L0_CalcSpendClock(spend_clock, &spend_ms, &spend_us);
			if (spend_ms > 10000) {
				break;
			}
			DEMOD_L0_system_wait(1);
		}
		DEMOD_NOTI("wait for reset process done, took %u.%03u, state %d\n", spend_ms, spend_us, pFrontend->demod->fw_state);

		if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN)
			ret = ERROR_DEMOD_FW_NOT_READY;
		else
			ret = NO_DEMOD_ERROR;
		return ret;
	}
	DEMOD_NOTI("faild re-init process, retry forced fw init, fw_state %d\n", pFrontend->demod->fw_state);
	pFrontend->demod->chip->fw_type = DEMOD_FW_TYPE_INV;
	pFrontend->demod->fw_state = DEMOD_FW_STATE_FAULT;
	return _DEMOD_M23_FW_Initialize(fw_type);
}

static UINT8 _last_demod_fw_type = DEMOD_FW_TYPE_INV;
static LX_DEMOD_OPER_MODE_T _last_demod_op_mode = LX_DEMOD_UNKOWN_OPMODE;

static int _DEMOD_M23_TE_MCU_PreRecovery (void * data) {
	int ret = 0;

	LX_DEMOD_L2_Context *	pFrontend = (LX_DEMOD_L2_Context *)data;

	if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN) {
		DEMOD_NOTI("fw is not running, skip prepare recovery, fw_state %d\n", pFrontend->demod->fw_state);
		return NO_DEMOD_ERROR;
	}

	DEMOD_NOTI("prepare recovery, check op 0x%02x, fwtype 0x%02x\n", g_demod_ctx_info[0].tranMode, pFrontend->demod->chip->fw_type);

	_last_demod_op_mode = g_demod_ctx_info[0].operMode;
	_last_demod_fw_type = pFrontend->demod->chip->fw_type;

	DEMOD_M23_IPC_Enable(FALSE);
	DEMOD_L1_IPC_Clear(pFrontend->demod);

	pFrontend->demod->fw_state = DEMOD_FW_STATE_RESET;
	DEMOD_L1_IPC_Wait_Cancel(pFrontend->demod);

	DEMOD_LockDevice();
	while (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip)) {
		DEMOD_ERROR("failed L0_LockDevice, fw timeout reset cancelled\n");
		DEMOD_L0_system_wait(10);
		continue;
	}

	_DEMOD_M23_DBB_IP_Reset(_last_demod_op_mode);

	DEMOD_M23_API_Suspend();

	if (NO_DEMOD_ERROR != _DEMOD_M23_StopFirmware(pFrontend)) {
		DEMOD_ERROR("stop fw failed\n");
	}

	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);

	DEMOD_NOTI("finish\n");
	return 0;
}

#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

static struct task_struct * _fw_reset_thread = NULL;
static wait_queue_head_t _fw_reset_wait;
static bool _fw_reset_flag = false;

static int _DEMOD_M23_FW_Reset_Task (void * data) {
	int	ret = NO_DEMOD_ERROR;
	bool	was_frozen = false;
	int	retry;

	DEMOD_PRINT("start, flag %d\n", _fw_reset_flag);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	while (!kthread_freezable_should_stop(&was_frozen)) {
		if (was_frozen) {
			DEMOD_INFO("awaken\n");
		}

		DEMOD_PRINT("wait event, flag %d\n", _fw_reset_flag);
		ret = wait_event_interruptible(_fw_reset_wait, _fw_reset_flag);
		DEMOD_NOTI("wait done, flag %d, ret %d\n", _fw_reset_flag, ret);

		//DEMOD_LockDevice();

		if (NO_DEMOD_ERROR != _DEMOD_M23_WaitFirmware()) {
			DEMOD_ERROR("WaitFirmware failed\n");
			break;
		}
	
		if (LX_DEMOD_UNKOWN_OPMODE != _last_demod_op_mode) {
			DEMOD_NOTI("post te_mcu recovery, lastn opmode 0x%02x, fwtype 0x%02x\n", _last_demod_op_mode, _last_demod_fw_type);
			ret = _DEMOD_M23_FW_Initialize(_last_demod_fw_type);

			if (ret == NO_DEMOD_ERROR) {
				DEMOD_INFO("try newtune\n");
				DEMOD_Retune(_last_demod_op_mode);
			}	
		} else {
			DEMOD_NOTI("skip post te_mcu recovery\n");
		}

		_fw_reset_flag = false;
	}
#endif
	DEMOD_NOTI("finish\n");
	_fw_reset_thread = NULL;
	_fw_reset_flag = false;
	return ret;
}

static int _DEMOD_M23_TE_MCU_PostRecovery (void * data) {
	LX_DEMOD_L2_Context *	pFrontend = (LX_DEMOD_L2_Context *)data;

	DEMOD_INFO("post recovery, thread %p, flag %d\n", _fw_reset_thread, _fw_reset_flag);
	if (NULL == _fw_reset_thread) {
		init_waitqueue_head(&_fw_reset_wait);
		_fw_reset_thread = kthread_run(_DEMOD_M23_FW_Reset_Task, (void *)pFrontend, "demod_fw_reset_handler");
	}

	_fw_reset_flag = true;
	wake_up_interruptible(&_fw_reset_wait);
	return 0;
}

static int _DEMOD_M23_TE_MCU_Suspend (void * data) {
	LX_DEMOD_L2_Context *	pFrontend = (LX_DEMOD_L2_Context *)data;

	DEMOD_INFO("suspend\n");

	return 0;
}

static int _DEMOD_M23_TE_MCU_Resume (void * data) {
	LX_DEMOD_L2_Context *	pFrontend = (LX_DEMOD_L2_Context *)data;

	DEMOD_INFO("resume, demod ip reset\n");
	DEMOD_M23_ResetHW();
	return 0;
}


int DEMOD_M23_FW_Initialize (void)
{
	DEMOD_NOTI("FW_TYPE_TER\n");
	return _DEMOD_M23_FW_Initialize(DEMOD_FW_TYPE_TER);
}

int DEMOD_M23_SAT_FW_Initialize (void)
{
	DEMOD_NOTI("FW_TYPE_SAT\n");
	return _DEMOD_M23_FW_Initialize(DEMOD_FW_TYPE_SAT);
}

int DEMOD_M23_ALL_FW_Initialize (void)
{		
	DEMOD_NOTI("FW_TYPE_TER\n");
	return _DEMOD_M23_FW_Initialize(DEMOD_FW_TYPE_TER);
}

int DEMOD_M23_FW_ReInitalize (int mode) {
//	LX_DEMOD_L2_Context *	pFrontend = DEMOD_Get_LGDBB_Context();
	int						ret = NO_DEMOD_ERROR;

	switch(mode) {
		case 0:
		case 1:
		case 2:
			DEMOD_INFO("not support ReInitialize, mode %d\n", mode);
			break;
		case 9:
			_DEMOD_M23_DBB_IP_SetBaseAddr();
			break;
		case 10:
			_DEMOD_M23_DBB_IP_ClrBaseAddr();
			break;
			
	}

	return ret;
}
