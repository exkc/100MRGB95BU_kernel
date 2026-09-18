/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/*****************************************************************************
**
**  Name:demod_common_o22.c
**
**  Description:    DBB common block.
**
**  Functions
**  Implemented:   int	DEMOD_O22_ResetHW
**                  int DEMOD_O22_SetI2C
**                  int DEMOD_O22_SetInclk
**                  int DEMOD_O22_AdcInit
**                  int DEMOD_O22_RepeaterEnable
**                  int DEMOD_O22_SoftwareReset
**                  int DEMOD_O22_Power_Save
**                  int DEMOD_O22_StdOperModeContrl
**                  int DEMOD_O22_NeverlockScan
**                  int DEMOD_O22_TPOutEnable
**                  int DEMOD_O22_Set_IF_Frq
**                  int DEMOD_O22_Set_AGCPolarity
**                  int DEMOD_O22_Get_Id
**                  int DEMOD_O22_Get_SpectrumStatus
**                  int DEMOD_O22_Get_IFAGC
**                  int DEMOD_O22_Get_OperMode
**                  int DEMOD_O22_Get_NeverLockStatus
**                  int DEMOD_O22_Get_CarrierFreqOffset
**                  int DEMOD_O22_Get_VABER
**                  int DEMOD_O22_Get_Packet_Error
**                  int DEMOD_O22_Get_BandWidthMode
**                  int DEMOD_O22_Get_QAMMode
**                  int DEMOD_O22_Get_MseInfo
**                  int DEMOD_O22_Get_Lock
**
**  References:
**
**  Exports:
**
**  Dependencies:   demod_impl.h for system configuration data.
**				 demod_analog_m16.h, demod_reg_m16.h
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   30-12-2009  Jeongpil Yun    Initial draft.
**   31-07-2013   Jeongpil Yun
**
*****************************************************************************/
#define DEMOD_TAG "[CHIP.COMMON] "

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>			/**< printk() */
#include <linux/slab.h>			 	/**< kmalloc() */
#include <linux/fs.h> 				/**< everything\ldots{} */
#include <linux/types.h>		 	/**< size_t */
#include <linux/fcntl.h>			/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>			/**< For request_region, check_region etc */
#include <asm/io.h>					/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/delay.h>

#include "sys_regs.h"
#include "hma_alloc.h"

#include "demod_common_o22.h"


#include "demod_impl.h"
#include "demod_util.h"
#include "demod_util_o22.h"

/* static variables (file scope) */
typedef struct lx_demod_context {
	LX_DEMOD_L2_Context		L2_Context;	// frontend
	LX_DEMOD_L1_Context		L1_Context;	// core (demod)
	LX_DEMOD_L0_Context		L0_Context;	// chip

	LX_DEMOD_L1_IPC			L1_IPC;

	LX_DEMOD_L1_CmdObj		L1_Cmd;
	LX_DEMOD_L1_CmdReplyObj		L1_CmdReply;
	LX_DEMOD_L1_PropObj		L1_Prop;
//	LX_DEMOD_L1_CommonReplayObj  	L1_CommonReply;
	LX_DEMOD_L1_PropObj		L1_PropShadow;
} LX_DEMOD_CONTEXT;

static LX_DEMOD_CONTEXT 	gLGDBB_Context;
static volatile UINT8 		gLGDBB_Context_Init = 0;

/* global variables */
UINT8						gLGDBB_PowerOnInit = 1;

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_GetContext.
 * DEMOD Context init & return
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - return LX_DEMOD_L2_Context else return NULL
 * @see
 * @author samin.ryu (samin.ryu@lge.com)
*/

LX_DEMOD_L2_Context * DEMOD_O22_GetContext (void) {
	if (unlikely(gLGDBB_Context_Init == 0)) {
		DEMOD_INFO("Context Init\n");

		memset(&gLGDBB_Context, 0, sizeof(LX_DEMOD_CONTEXT));

		gLGDBB_Context.L2_Context.demod			= &gLGDBB_Context.L1_Context;

		gLGDBB_Context.L2_Context.demod->chip		= &gLGDBB_Context.L0_Context;

		gLGDBB_Context.L2_Context.demod->ipc		= &gLGDBB_Context.L1_IPC;

		gLGDBB_Context.L2_Context.demod->cmd		= &gLGDBB_Context.L1_Cmd;
		gLGDBB_Context.L2_Context.demod->rsp		= &gLGDBB_Context.L1_CmdReply;
		gLGDBB_Context.L2_Context.demod->prop		= &gLGDBB_Context.L1_Prop;
//		gLGDBB_Context.L2_Context.demod->status		= &gLGDBB_Context.L1_CommonReply;
		gLGDBB_Context.L2_Context.demod->propShadow	= &gLGDBB_Context.L1_PropShadow;

		gLGDBB_Context_Init = 1;
	}

	return &gLGDBB_Context.L2_Context;
}

#if 0
static volatile unsigned int *
	gMapped_address = NULL;

#define DEMOD_APB_REG_WR(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define DEMOD_APB_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#endif

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O22_Get_Lock_FEC
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_FEC (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O22_Get_Lock_TR
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_TR (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O22_Get_Lock_CARR
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_CARR (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_PSYNC (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O22_Get_Lock_TPS
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_TPS (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O22_Get_Lock_AGC
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_AGC (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O22_Get_Lock_Mode_Det (LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ResetHW (void)
{
	DEMOD_INFO("Start\n");
	
#if 1
	usleep_range(1000,10000);	/* 1ms ~ 10ms */

	CTOP_CTRL_O22Ax_RdFL(DBB_IPW_TOP, ipw_dbb_004);
	CTOP_CTRL_O22Ax_Wr01(DBB_IPW_TOP, ipw_dbb_004, reg_dbb_reset, 1);
	CTOP_CTRL_O22Ax_WrFL(DBB_IPW_TOP, ipw_dbb_004);

	usleep_range(1000,10000);	/* 1ms ~ 10ms */

	CTOP_CTRL_O22Ax_RdFL(DBB_IPW_TOP, ipw_dbb_004);
	CTOP_CTRL_O22Ax_Wr01(DBB_IPW_TOP, ipw_dbb_004, reg_dbb_reset, 0);
	CTOP_CTRL_O22Ax_WrFL(DBB_IPW_TOP, ipw_dbb_004);
#endif

#if 1 // for low power mode

	usleep_range(1000,10000);	/* 1ms ~ 10ms */

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip8);
	CTOP_CTRL_O22Ax_Wr02(BND_CTRL_BMC, admd_mip8, reg_admd_dpll_pdb,1,reg_admd_apll_pdb,1);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip8);
	
	usleep_range(1000,10000);	/* 1ms ~ 10ms */

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip7);
	CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_dpll_insel, 1);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip7);

	usleep_range(1000,10000);	/* 1ms ~ 10ms */
 

	CTOP_CTRL_O22Ax_RdFL(DBB_IPW_TOP, ipw_dbb_003);
	CTOP_CTRL_O22Ax_Wr01(DBB_IPW_TOP, ipw_dbb_003, pll_cgen, 1);
	CTOP_CTRL_O22Ax_WrFL(DBB_IPW_TOP, ipw_dbb_003);

#endif

	usleep_range(3000,10000);	/* 3ms ~ 10ms */

	CTOP_CTRL_O22Ax_RdFL(DBB_IPW_TOP, ipw_dbb_004);
	CTOP_CTRL_O22Ax_Wr01(DBB_IPW_TOP, ipw_dbb_004, reg_dbb_reset, 1);
	CTOP_CTRL_O22Ax_WrFL(DBB_IPW_TOP, ipw_dbb_004);

	gLGDBB_PowerOnInit = 1;

	DEMOD_INFO("End\n");
	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_SetI2C (void)
{

#if 0
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_O22_SetI2C Start !! \n");

	ACE_REG_O22A0_RdFL(dbb_00);

	ACE_REG_O22A0_Wr01(dbb_00, dbb_i2csel, 0);

	ACE_REG_O22A0_WrFL(dbb_00);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_O22_SetI2C end !! \n");

#endif
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_SetInclk.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_SetInclk (LX_DEMOD_INCLK_SEL_T *inclk)
{
#if defined(DEMOD_CHIP_NAME_o20)
	DEMOD_PRINT("Start \n");

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip7);

	switch(*inclk)
	{
		case LX_DEMOD_ARM_SETTING:
		{
			CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_dpll_insel, 0);
		}
		break;

		case LX_DEMOD_EXTERN_PIN:
		{
			CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_dpll_insel, 1);
		}
		break;

		default:
			DEMOD_PRINT("Invalid LX_DEMOD_INCLK_SEL_T type \n");
			return -1;
	}

	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip7);

	DEMOD_PRINT("End \n");

#endif
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_AdcInit.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_AdcInit (void)
{
	DEMOD_PRINT("Start \n");

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip8);
	CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip8, reg_admd_dpll_pdb, 1);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip8);

	DEMOD_PRINT("End \n");

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_RepeaterEnable.
 * Enable / Disable GBB I2C repeater function
 *
 * @param bEnable [IN] 	BOOLEAN - Enable/Disable I2C repeater
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_RepeaterEnable (BOOLEAN bEnable)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	if(bEnable == TRUE)
		DEMOD_L2_Tuner_I2C_Enable(pFrontend);
	else
		DEMOD_L2_Tuner_I2C_Disable(pFrontend);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_SoftwareReset.
 * Reset DVB module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_SoftwareReset (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	if (RET_OK != DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0))
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_Set_SoftRst() \n");
		return RET_ERROR;
	}
	DEMOD_PRINT("SUCCESS DEMOD_L2_Set_SoftRst() \n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Power_Save
 * Enable/Disable power save mode
 *
 * @param bEnable 	[IN] power save mode(TRUE) / normal mode(FALSE)
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_Power_Save (BOOLEAN bEnable)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	bEnable = bEnable & 0x1;
	DEMOD_INFO("%s power_save\n", (bEnable ? "enter" : "leave"));

	if(bEnable == TRUE)
	{
		if (DEMOD_L2_Standby(pFrontend)!= NO_DEMOD_ERROR )
		{
			DEMOD_PRINT("FAIL, DEMOD_L2_Standby() \n");
			return RET_ERROR;
		}
	}
	else
	{
		if (DEMOD_L2_WakeUp(pFrontend)!= NO_DEMOD_ERROR )
		{
			DEMOD_PRINT("FAIL, DEMOD_L2_WakeUp() \n");
			return RET_ERROR;
		}
	}
	
	DEMOD_PRINT("DEMOD_O22_Power_Save End \n");

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_StdOperModeContrl
 * Set standard operation mode, Bandwidth and symbol rate
 *
 * @param *InitParam [IN] LX_DEMOD_INIT_PARAM_T - operation RF Mode, bandWidth, Symbol rate
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_StdOperModeContrl (LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8	reg_admd_dpll_odpost = 0;
	UINT8	reg_admd_dpll_odpre = 0;

	UINT8	reg_admd_apll_m = 0;
	UINT8	reg_admd_dpll_cken = 0;
	UINT8	reg_admd_q_pdb = 0;
	UINT8	reg_admd_i_pdb = 0;
	UINT8	reg_admd_t_pdb = 0;
	UINT8	reg_admd_adc_refsel = 0;
	UINT8	reg_admd_dpll_divint = 0;
	UINT8	reg_admd_dpll_icp = 0;
	UINT8 	reg_admd_bias_pdb = 0;
	BOOL	register_set_flag = FALSE;

	// PAD / BND Control register
	UINT8	reg_pad_fefctrl_mux_sel = 0; //fefctrl : 1: TP(default) , 0: fefctrl
	UINT8	reg_pad_diseqc_mux_sel = 0; //0: diseqco, 1: gp3_in[5] (gp3_out[5]), 2: i_stpi_val_ext3,
	
	UINT8	reg_pad_diseqc_cmd_mux_sel = 0; // 0: diseqc_cmd, 1: gp3_in[6] (gp3_out[6]), 2: i_stpi_sop_ext3, 
	UINT8	reg_pad_diseqci_mux_sel = 0; // 0: diseqci, 1: gp3_in[7] (gp3_out[7]), 2: i_stpi_ext3_clk,
	UINT8	reg_tpi_cam_mux_sel = 0; // 0: tpi_*_cam, 1: stpi_*_ext3

	UINT8	new_standard = 0;

	DEMOD_PRINT("OperationMode = 0x%02x \n", operMode);

	pFrontend = DEMOD_O22_GetContext();

	/* becuase M16+ demod memory region is initialized to CMA, driver should acquire
	 * demod memory with "cma alloc" from kernel before the first ISDB-T channel change.
	 * NEVER free the allocated memory.
	 *
	 * raxis.lim (2016/06/27)
	 * To save BSP memory, demod will allocate its runtime memory from "te_shared" hma pool.
	 */

	if(operMode == LX_DEMOD_ISDBT)
	{
		if( RET_OK != DEMOD_ISDBT_Set_MemSconfig())
		{
		  DEMOD_PRINT("FAIL, DEMOD_ISDBT_Set_MemSconfig() \n");
		  return RET_ERROR;
		}
	}

	if(operMode == LX_DEMOD_DVBT ||operMode == LX_DEMOD_DVBT2 ||operMode == LX_DEMOD_DVBS || operMode == LX_DEMOD_DVBS2)
	{
		if( RET_OK != DEMOD_DVB_Set_MemSconfig())
		{
		  DEMOD_PRINT("FAIL, DEMOD_DVB_Set_MemSconfig()\n");
		  return RET_ERROR;
		}
	}

	if(operMode == LX_DEMOD_DTMB)
	{
		if( RET_OK != DEMOD_DTMB_Set_MemSconfig())
		{
		  DEMOD_PRINT("FAIL, DEMOD_DTMB_Set_MemSconfig()\n");
		  return RET_ERROR;
		}
	}
	
	if(operMode == LX_DEMOD_ATSC3)
	{
		if( RET_OK != DEMOD_ATSC3_Set_MemSconfig())
		{
		  DEMOD_PRINT("FAIL, DEMOD_ATSC3_Set_MemSconfig()\n");
		  return RET_ERROR;
		}
	}

	usleep_range(20000,30000);	/* 1ms ~ 10ms */
	switch(operMode)
	{
		case LX_DEMOD_ATSC:
			new_standard			= DEMOD_MODULATION_VSB;
			//24MHz 384MH
			reg_admd_dpll_odpost	= 0x18;
			reg_admd_dpll_odpre		= 0x05;
			reg_admd_apll_m			= 0x19;
			reg_admd_dpll_cken		= 0x05;
			reg_admd_adc_refsel		= 0x1;
			reg_admd_q_pdb			= 0x0;
			reg_admd_i_pdb			= 0x0;
			reg_admd_t_pdb			= 0x1;
			reg_admd_dpll_divint	= 0xc0;
			reg_admd_dpll_icp		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			register_set_flag		= TRUE;
			break;

		case LX_DEMOD_QAM:
			new_standard			= DEMOD_MODULATION_QAM;
			//24MHz 384MHz

			reg_admd_dpll_odpost	= 0x18;
			reg_admd_dpll_odpre		= 0x05;
			reg_admd_apll_m			= 0x19;
			reg_admd_dpll_cken		= 0x05;
			reg_admd_adc_refsel		= 0x1;
			reg_admd_q_pdb			= 0x0;
			reg_admd_i_pdb			= 0x0;
			reg_admd_t_pdb			= 0x1;
			reg_admd_dpll_divint	= 0xc0;
			reg_admd_dpll_icp		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			register_set_flag		= TRUE;

			break;

		case LX_DEMOD_ISDBT:
			new_standard			= DEMOD_MODULATION_ISDBT;
			//24MHz 384MHz
			reg_admd_apll_m			= 0x19;
			reg_admd_dpll_odpost	= 0x18;
			reg_admd_dpll_odpre		= 0x05;
			reg_admd_dpll_cken		= 0x05;
			reg_admd_adc_refsel		= 0x1;
			reg_admd_q_pdb			= 0x0;
			reg_admd_i_pdb			= 0x0;
			reg_admd_t_pdb 			= 0x1;
			reg_admd_dpll_divint 	= 0xc0;
			reg_admd_dpll_icp 		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			register_set_flag 		= TRUE;

			break;

		case LX_DEMOD_DVBT:
		case LX_DEMOD_DVBT2:
			new_standard 			= DEMOD_MODULATION_DVBT;
			//24MHz 384MHz

			reg_admd_dpll_odpost 	= 0x18;
			reg_admd_dpll_odpre 	= 0x05;
			reg_admd_apll_m 		= 0x19;
			reg_admd_dpll_cken 		= 0x05;
			reg_admd_adc_refsel 	= 0x1;
			reg_admd_q_pdb 			= 0x0;
			reg_admd_i_pdb 			= 0x0;
			reg_admd_t_pdb 			= 0x1;
			reg_admd_dpll_divint 	= 0xc0;
			reg_admd_dpll_icp 		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			reg_pad_fefctrl_mux_sel = 0x0;

			register_set_flag 		= TRUE;

			break;

		case LX_DEMOD_DVBC:
			new_standard 			= DEMOD_MODULATION_DVBC;
			//24MHz 384MHz

			reg_admd_dpll_odpost 	= 0x18;
			reg_admd_dpll_odpre 	= 0x05;
			reg_admd_apll_m 		= 0x19;
			reg_admd_dpll_cken 		= 0x05;
			reg_admd_adc_refsel 	= 0x1;
			reg_admd_q_pdb 			= 0x0;
			reg_admd_i_pdb 			= 0x0;
			reg_admd_t_pdb 			= 0x1;
			reg_admd_dpll_divint 	= 0xc0;
			reg_admd_dpll_icp 		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			register_set_flag 		= TRUE;
			break;

		case LX_DEMOD_DTMB:
			new_standard 			= DEMOD_MODULATION_DTMB;
			//24MHz 384MHz

			reg_admd_dpll_odpost 	= 0x18;
			reg_admd_dpll_odpre 	= 0x05;
			reg_admd_apll_m 		= 0x19;
			reg_admd_dpll_cken 		= 0x05;
			reg_admd_adc_refsel 	= 0x1;
			reg_admd_q_pdb 			= 0x0;
			reg_admd_i_pdb 			= 0x0;
			reg_admd_t_pdb 			= 0x1;
			reg_admd_dpll_divint 	= 0xc0;
			reg_admd_dpll_icp 		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			register_set_flag 		= TRUE;
			break;


		case LX_DEMOD_DVBS:
		case LX_DEMOD_DVBS2:
			new_standard 			= DEMOD_MODULATION_DVBS;
			//124MHz 496MHz

			reg_admd_dpll_odpost 	= 0x04;
			reg_admd_dpll_odpre 	= 0x05;
			reg_admd_apll_m 		= 0x19;
			reg_admd_dpll_cken 		= 0x03;
			reg_admd_adc_refsel 	= 0x1;
			reg_admd_q_pdb 			= 0x1;
			reg_admd_i_pdb 			= 0x1;
			reg_admd_t_pdb 			= 0x0;
			reg_admd_dpll_divint 	= 0xf8;
			reg_admd_dpll_icp 		= 0x0c;
			reg_admd_bias_pdb		= 0x1;

			reg_pad_diseqc_mux_sel 	= 0x0;
			reg_pad_diseqc_cmd_mux_sel 	= 0x0;
			reg_pad_diseqci_mux_sel 	= 0x0;

			register_set_flag 		= TRUE;

			break;

		case LX_DEMOD_ATSC3:
			new_standard 			= DEMOD_MODULATION_ATSC3;
			reg_admd_dpll_odpost	= 0x18;
			reg_admd_dpll_odpre		= 0x05;
			reg_admd_apll_m			= 0x19;
			reg_admd_dpll_cken		= 0x05;
			reg_admd_adc_refsel		= 0x1;
			reg_admd_q_pdb			= 0x0;
			reg_admd_i_pdb			= 0x0;
			reg_admd_t_pdb			= 0x1;
			reg_admd_dpll_divint	= 0xc0;
			reg_admd_dpll_icp		= 0x08;
			reg_admd_bias_pdb		= 0x1;

			register_set_flag 		= TRUE;

			break;

		default :
			DEMOD_ERROR("Invaild Opermode parameter \n");
			return RET_ERROR;
	}

	// ADC reference voltage selection
	// DMD ADC reference voltage selection (00: 1.0Vpp, 01: 1.2Vpp, 10: 1.4Vpp, 11: 1.6Vpp, Default:00)
#if 1 // for FPGA Test
	if (register_set_flag)
	{
		DEMOD_NOTI("Change register setting \n");

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip5);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip5, reg_admd_i_pdb, reg_admd_i_pdb);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip5);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip6);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip6, reg_admd_dpll_odpre, reg_admd_dpll_odpre);
		CTOP_CTRL_O22Ax_Wr02(BND_CTRL_BMC, admd_mip6, reg_admd_q_pdb, reg_admd_q_pdb, reg_admd_t_pdb, reg_admd_t_pdb);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip6);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_dpll_cken, reg_admd_dpll_cken);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_bias_pdb, reg_admd_bias_pdb);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip7);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip8, reg_admd_dpll_odpost, reg_admd_dpll_odpost);
		CTOP_CTRL_O22Ax_Wr02(BND_CTRL_BMC, admd_mip8, reg_admd_dpll_divint,reg_admd_dpll_divint,reg_admd_dpll_icp,reg_admd_dpll_icp);
		CTOP_CTRL_O22Ax_Wr02(BND_CTRL_BMC, admd_mip8, reg_admd_apll_m, reg_admd_apll_m, reg_admd_adc_refsel, reg_admd_adc_refsel);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip8);
	
		//DVB-S/S2 only
		if (new_standard == DEMOD_MODULATION_DVBS)
		{			
			DEMOD_NOTI("DVB-S/S2 PAD Control \n");

			CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd065);
			CTOP_CTRL_O22Ax_Wr03(FUNC_IOMUX_VD0, pad_vd065, reg_pad_diseqc_cmd_mux_sel, reg_pad_diseqc_cmd_mux_sel,reg_pad_diseqci_mux_sel,reg_pad_diseqci_mux_sel,reg_pad_diseqc_mux_sel,reg_pad_diseqc_mux_sel);
			CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd065);

			
			DEMOD_NOTI("DVB-S/S2 BND Control \n");

			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_CPU, bnd_cpu_r18);
			CTOP_CTRL_O22Ax_Wr01(BND_CTRL_CPU, bnd_cpu_r18, reg_tpi_cam_mux_sel, reg_tpi_cam_mux_sel);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_CPU, bnd_cpu_r18);
			
		}

		//DVB-T/T2 only
		if (new_standard == DEMOD_MODULATION_DVBT)
		{
			DEMOD_NOTI("DVB-T/T2 PAD Control \n");

			CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd065);
			CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd065, reg_pad_fefctrl_mux_sel,reg_pad_fefctrl_mux_sel);
			CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd065);

			DEMOD_NOTI("DVB-T/T2 BND Control \n");
			
			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_CPU, bnd_cpu_r18);
			CTOP_CTRL_O22Ax_Wr01(BND_CTRL_CPU, bnd_cpu_r18, reg_tpi_cam_mux_sel, reg_tpi_cam_mux_sel);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_CPU, bnd_cpu_r18);

		}
		
		DEMOD_O22_MCU_Set_UART(TRUE);
	}
	else
	{
		DEMOD_WARN("FAIL, Change register setting \n");
	}
#endif

	pFrontend->demod->standard = new_standard;

	DEMOD_NOTI("ChangeTransMedia = %s\n", DEMOD_L1_API_Modulation_Text(new_standard)); 

	return RET_OK;

}


/**
 * DEMOD_O22_NeverlockScan
 * Get the neverlock flag indicator.
 *
 * @param	*pDemodInfo			[IN] DEMOD_CTX_T.
 * @param	ResetOn				[IN] 	LX_DEMOD_FLAG_T  - force to initialize the postjob.
 * @param	*pScanProcessing		[OUT] LX_DEMOD_FLAG_T- the flag that scan is done or not done.
 * @param	*pScanLock			[OUT] LX_DEMOD_LOCK_STATE_T - scan lock result.
 * @return if Succeeded - RET_OK else-TU_ERROR
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/
int DEMOD_O22_NeverlockScan (DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock)
{
	static LX_DEMOD_LOCK_STATE_T	_demodScanLock	= LX_DEMOD_UNKOWN_STATE;
	static unsigned int				_neverLockResetTime = 0;
	static unsigned int 			_maxTimeOut = 0;
	unsigned int 					elapsedTime = 0;
	LX_DEMOD_LOCK_STATE_T 			neverLockStatus;
	LX_DEMOD_OPER_MODE_T 			scanMode;

	scanMode = pDemodInfo->operMode;

	if(LX_DEMOD_FLAG_ON == ResetOn)
	{
		*pScanProcessing 	= LX_DEMOD_FLAG_ING;
		*pScanLock			= LX_DEMOD_UNLOCKED;

		switch(scanMode)
		{
			case LX_DEMOD_DVBT :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1500;
				break;
			case LX_DEMOD_DVBT2 :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1500;
				break;
			case LX_DEMOD_DVBC :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1500;
				break;
			case LX_DEMOD_ATSC :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;
			case LX_DEMOD_QAM :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;
			case LX_DEMOD_ISDBT :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;
			case LX_DEMOD_DVBS :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_10000;
				break;
			case LX_DEMOD_DVBS2 :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_10000;
				break;
			case LX_DEMOD_DTMB :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;
			default :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;
		}
		_neverLockResetTime = jiffies_to_msecs(jiffies);
		return RET_OK;
	}


	if (RET_OK != DEMOD_O22_Get_NeverLockStatus(scanMode, &neverLockStatus))
	{
		DEMOD_PRINT("FAIL, KADP_DEMOD_VQI_ChanScan_GetStatus() !!!\n");
		*pScanLock	= LX_DEMOD_UNLOCKED;
		return RET_ERROR;
	}

	switch (neverLockStatus)
	{

		case LX_DEMOD_DETECTION_PROCESSING:
			{
				elapsedTime 			= jiffies_to_msecs(jiffies) - _neverLockResetTime;
				_demodScanLock			= LX_DEMOD_UNKOWN_STATE;
//				DEMOD_PRINT("ElapsedTime = %d, MaxTimeOut = %d \n", elapsedTime,_maxTimeOut  );

				if(elapsedTime > _maxTimeOut)
				{
					*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
					_demodScanLock		= LX_DEMOD_UNLOCKED;
//					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_DETECTION_PROCESSING \n");
				}
			}
			break;

		case LX_DEMOD_DETECTION_FAIL:
			{
				*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
				_demodScanLock		= LX_DEMOD_UNLOCKED;
				DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_DETECTION_FAIL \n");
			}
			break;

		case LX_DEMOD_DETECTED:
			{
				*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
				_demodScanLock		= LX_DEMOD_TR_LOCK;
				DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_DETECTED \n");
			}
			break;
		default:
			_demodScanLock	= LX_DEMOD_UNLOCKED;
			DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_UNLOCKED(%d) \n", neverLockStatus);
			break;
	}

	*pScanLock	= _demodScanLock;

//	DEMOD_PRINT("[DEMOD_CHIP] Nerver Lock status is 0x%x\n", _demodScanLock);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_TPOutEnable
 * Enable/Diable the output of TP
 *
 * @param bEnable	  [IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_TPOutEnable (BOOLEAN bEnable)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	DEMOD_PRINT("Current TPOutEn property is %d", pFrontend->demod->prop->dd_tpout_mode.tpOutEn );
	
	if(bEnable == TRUE)
	{
		pFrontend->demod->prop->dd_tpout_mode.tpOutEn = DEMOD_PROP_TPOUT_MODE_TPSRMSB_ENABLE;
	}
	else
	{
		pFrontend->demod->prop->dd_tpout_mode.tpOutEn = DEMOD_PROP_TPOUT_MODE_TPSRMSB_DISABLE;
	}

	pFrontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ALWAYS; 
	DEMOD_PRINT("Set PropertyWriteMode to DEMOD_DD_DOWNLOAD_ALWAYS \n");


	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_PROP_TPOUT_MODE_CODE )!= NO_DEMOD_ERROR )
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_Set_Property() \n");
		return RET_ERROR;
	}

	pFrontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ON_CHANGE;
	DEMOD_PRINT("Set PropertyWriteMode to DEMOD_DD_DOWNLOAD_ON_CHANGE \n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_GetTsClkRate
 * Get the output of TP
 *
 * @param UINT32 *	  [OUT] demodTsClkRate.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_GetTsClkRate (UINT32 *demodTsClkRate)
{

	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	DEMOD_PRINT("Start\n");

	if (DEMOD_L2_Get_TsClkStatus(pFrontend, demodTsClkRate))
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_Get_TsClkStatus() \n");
		return RET_ERROR;
	}

	DEMOD_PRINT("demodTsClkRate = %d \n", *demodTsClkRate);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Set_IF_Frq
 * Set IF frequency registers on DVB-C mode.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Set_IF_Frq (UINT32 ifFrq)
{
#if 1
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	if(ifFrq == LX_DEMOD_IF_FREQ_05_000_KHZ)
	{
		pFrontend->demod->prop->dd_if_freq.if_freq = DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ;
		DEMOD_PRINT("Set IF Frq  5MHz \n");
	}
	else if(ifFrq == LX_DEMOD_IF_FREQ_06_000_KHZ)
	{
		pFrontend->demod->prop->dd_if_freq.if_freq = DEMOD_PROP_IF_FREQ_IF_FREQ_6MHZ;
		DEMOD_PRINT("Set_IF_Frq  6MHz \n");
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, DEMOD_L2_Set_Property() \n");
		return RET_ERROR;
	}

#endif

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Set_AGCPolarity
 * Set IF frequency registers on DVB.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Set_AGCPolarity (LX_DEMOD_AGC_POLAR_T agcPola)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_O22_GetContext();

	if(agcPola == LX_DEMOD_AGC_ACTIVE_HIGH)
	{
		pFrontend->demod->prop->dd_agc.agc_pol  = DEMOD_PROP_AGC_POLARITY_NORMAL;
		DEMOD_PRINT("DEMOD_PROP_AGC_POLARITY_NORMAL \n");
	}
	else
	{
		pFrontend->demod->prop->dd_agc.agc_pol  = DEMOD_PROP_AGC_POLARITY_INVERSION;
		DEMOD_PRINT("DEMOD_PROP_AGC_POLARITY_INVERSION \n");
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_PROP_AGC_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("Fail, DEMOD_L2_Set_Property() \n");
		return RET_ERROR;

	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_Id.
 * Get GBB demod ID.
 *
 * @param *cell_id [OUT] UINT16 - GBB demod ID
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_Id (UINT8 *pCellIDLength, UINT16 *pId)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	*pId = signalStatus.cell_id;
	*pCellIDLength = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_SpectrumInvStatus
 * Get spectrum mode state on DVB.
 *
 * @param *pSpectrumAuto 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_AUTO, LX_DEMOD_MANUAL.
 * @param *pSpectrumInv 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_NORMAL, LX_DEMOD_INVERSION.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_SpectrumStatus (LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;
	LX_DEMOD_LOCK_STATE_T	SpectrumAuto = LX_DEMOD_AUTO;
	LX_DEMOD_LOCK_STATE_T	SpectrumInv = LX_DEMOD_NORMAL;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	switch (signalStatus.spInv)
	{
		case DEMOD_PROP_MODE_SPECINV_INVERSION: SpectrumInv = LX_DEMOD_INVERSION; break;
		case DEMOD_PROP_MODE_SPECINV_NORMAL: 	SpectrumInv = LX_DEMOD_NORMAL; break;
		default:
			break;
	}

	if (DEMOD_L2_Get_Property(pFrontend, DEMOD_PROP_MODE_CODE))
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_Get_Property() \n");
		return RET_ERROR;
	}

	SpectrumAuto 		= pFrontend->demod->prop->dd_mode.specinvauto;
	*pSpectrumAuto 		= SpectrumAuto;
	*pSpectrumInv 		= SpectrumInv;

	DEMOD_PRINT("check spectrum  auto ? manual [%d] \n", SpectrumAuto);
	DEMOD_PRINT("check spectrum  inverted ?    [%d] \n", SpectrumInv);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_IFAGCValue
 * Get IF AGC value on DVB.
 *
 * @param *pIfagcValue 	[OUT] UINT16
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_IFAGC (UINT16 *pIfAgc)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	*pIfAgc = signalStatus.if_agc;
	DEMOD_PRINT("IF AGC = 0x%x \n", *pIfAgc);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_OperMode.
 * Get GBB operation mode.
 *
 * @param *pOperMode [OUT] LX_DEMOD_VQI_RF_MODE_T - GBB RF demodulation mode
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_OperMode (LX_DEMOD_OPER_MODE_T *pOperMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_OPER_MODE_T	reply_opmode;
	const char *			reply_opmode_text = NULL;

	int			retc = 0;

	pFrontend = DEMOD_O22_GetContext();

//	retc = DEMOD_L1_GET_DD_Status(pFrontend->demod);
	retc = DEMOD_L2_Get_OperMode(pFrontend, &reply_opmode);

	if(NO_DEMOD_ERROR != retc)
	{
		*pOperMode = LX_DEMOD_UNKOWN_OPMODE;

		return RET_ERROR;
	}

	switch (reply_opmode)
	{
		case LX_DEMOD_DVBT:		reply_opmode_text = "DVB-T";	break;
		case LX_DEMOD_DVBT2: 	reply_opmode_text = "DVB-T2";	break;
		case LX_DEMOD_ATSC: 	reply_opmode_text = "ATSC";		break;
		case LX_DEMOD_ISDBT:	reply_opmode_text = "ISDBT";	break;
		case LX_DEMOD_DTMB:		reply_opmode_text = "DTMB";		break;
		case LX_DEMOD_ATSC3:	reply_opmode_text = "ATSC3";	break;
		case LX_DEMOD_DVBC:		reply_opmode_text = "DVB-C";	break;
		case LX_DEMOD_DVBC2:	reply_opmode_text = "DVB-C2";	break;
		case LX_DEMOD_QAM:		reply_opmode_text = "QAM";		break;
		case LX_DEMOD_ISDBC:	reply_opmode_text = "ISDBC";	break;
		case LX_DEMOD_DVBS:		reply_opmode_text = "DVB-S";	break;
		case LX_DEMOD_DVBS2: 	reply_opmode_text = "DVB-S2";	break;
		case LX_DEMOD_BS: 		reply_opmode_text = "BS";		break;
		case LX_DEMOD_CS:		reply_opmode_text = "CS";		break;
		case LX_DEMOD_ANALOG:	reply_opmode_text = "ANALOG";	break;

		default :
			DEMOD_ERROR("LX_DEMOD_UNKNOWN_OPMODE value : 0x%02x\n", reply_opmode);
			return RET_ERROR;

	}

	DEMOD_PRINT("OPmode is the %s(0x%02x)\n", reply_opmode_text, reply_opmode);

	*pOperMode = reply_opmode;

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_NeverLockStatus
 * Get neverlock state on DVB.
 *
 * @param scanMode 	[OUT] LX_DEMOD_OPER_MODE_T
 * @param *pNeverLockStatus 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMODLOCKED, LX_DEMOD_UNLOCKED.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_NeverLockStatus (LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8			neverlock;

	pFrontend = DEMOD_O22_GetContext();

	*pNeverLockStatus = LX_DEMOD_UNKOWN_STATE;

	neverlock = DEMOD_L2_Check_NeverLock_state(pFrontend);

	switch(neverlock)
	{
		case 0x00 : // Initialization process
			*pNeverLockStatus = LX_DEMOD_DETECTION_FAIL;
			break;
		case 0x01 : // Signal checking process
			*pNeverLockStatus = LX_DEMOD_DETECTED;
			break;
		case 0x02 :// Normal state (available channel)
			*pNeverLockStatus = LX_DEMOD_DETECTION_PROCESSING;
			break;
		default :// neverlock state (empty channel)
			*pNeverLockStatus = LX_DEMOD_DETECTION_FAIL;
			break;
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_CarrierFreqOffset
 * Get carrier offset frequency .
 *
 * @param *pFreqOff 	[OUT] SINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_CarrierFreqOffset (SINT32 *pFreqOff)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	SINT32			freqOffset;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	freqOffset = signalStatus.offsetFrq_Hz/1000;

//	DEMOD_PRINT("(freqOffset: %d) \n", freqOffset);

	*pFreqOff = freqOffset ;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_VABER
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_VABER (UINT32 *pVber)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	*pVber = signalStatus.ber ;

	DEMOD_PRINT("BER: %d \n", *pVber);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_Packet_Error
 * Get packet error on DVB
 *
 * @param *pSnr 	[OUT] UINT8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_Packet_Error (UINT32 *pError)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	*pError = signalStatus.packetError;

	DEMOD_PRINT("*pError = %d  \n",*pError);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_BandWidthMode
 * Get the information of bandwidth .
 *
 * @param *ChannelBW 	[OUT] LX_DEMOD_BWMODE_T - 6, 7 and 8 MHZ.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_BandWidthMode (LX_DEMOD_BWMODE_T *ChannelBW )
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}
	switch(signalStatus.bandwidth)
	{
		case 0x08:
			*ChannelBW = LX_DEMOD_BW_8MHZ;
			break;
		case 0x07:
			*ChannelBW = LX_DEMOD_BW_7MHZ;
			break;
		case 0x06:
			*ChannelBW = LX_DEMOD_BW_6MHZ;
			break;
		case 0x05:
			*ChannelBW = LX_DEMOD_BW_5MHZ;
			break;
		default:
			*ChannelBW = LX_DEMOD_BW_UNKNOWN;
			break;
	}

//	*ChannelBW = LX_DEMOD_BW_UNKNOWN;(signalStatus.constellation)

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_QAMMode
 * Get the information of QAM mode .
 *
 * @param *pQamMode [OUT] LX_DEMOD_RF_MODE_T - 16QAM, 32QAM, 64QAM, 128QAM, 256QAM, QPSK.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_QAMMode (LX_DEMOD_RF_MODE_T *pQamMode )
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;
	LX_DEMOD_OPER_MODE_T	mode;

	pFrontend = DEMOD_O22_GetContext();

/*
	if(RET_OK != DEMOD_O22_Get_OperMode(&mode))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_O22_Get_OperMode() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}
	//printk("DEMOD_L2_SignalStatus============ signalStatus.constellation[%d]  \n ", signalStatus.constellation);

	switch (pFrontend->demod->rsp->dd_status.reply_operMod)
	{
		case DEMOD_MODULATION_VSB:		mode = LX_DEMOD_ATSC;	break;
		case DEMOD_MODULATION_QAM: 		mode = LX_DEMOD_QAM;	break;
		case DEMOD_MODULATION_ISDBT: 	mode = LX_DEMOD_ISDBT;	break;
		case DEMOD_MODULATION_DVBT:		mode = LX_DEMOD_DVBT;	break;
		case DEMOD_MODULATION_DVBT2:	mode = LX_DEMOD_DVBT2;	break;
		case DEMOD_MODULATION_DVBC:		mode = LX_DEMOD_DVBC;	break;
		case DEMOD_MODULATION_DVBC2:	mode = LX_DEMOD_DVBC2;	break;
		case DEMOD_MODULATION_DVBS:		mode = LX_DEMOD_DVBS;	break;
		case DEMOD_MODULATION_DVBS2:	mode = LX_DEMOD_DVBS2;	break;
		case DEMOD_MODULATION_DTMB:		mode = LX_DEMOD_DTMB;	break;

		default :
			DEMOD_ERROR("Fail, LX_DEMOD_UNKOWN_OPMODE \n");
			return RET_ERROR;
	}

	switch(mode)
	{
		case LX_DEMOD_DVBT:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;

		case LX_DEMOD_DVBT2:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_CONSTELLATION_QAM32:
						*pQamMode = LX_DEMOD_32QAM;
						break;
					case DEMOD_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_CONSTELLATION_QAM128 :
						*pQamMode = LX_DEMOD_128QAM;
						break;
					case DEMOD_CONSTELLATION_QAM256 :
						*pQamMode = LX_DEMOD_256QAM;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;

		case LX_DEMOD_DVBC:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_CONSTELLATION_QAM32 :
						*pQamMode = LX_DEMOD_32QAM;
						break;
					case DEMOD_CONSTELLATION_QAM64 :
						 *pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_CONSTELLATION_QAM128 :
						 *pQamMode = LX_DEMOD_128QAM;
						break;
					case DEMOD_CONSTELLATION_QAM256 :
						*pQamMode = LX_DEMOD_256QAM;
						break;
					default :
						 *pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;

				}
			}
			break;

		case LX_DEMOD_DVBC2:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_CONSTELLATION_QAM64 :
						 *pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_CONSTELLATION_QAM256 :
						 *pQamMode = LX_DEMOD_256QAM;
						break;
					case DEMOD_CONSTELLATION_QAM1024 :
						*pQamMode = LX_DEMOD_1024QAM;
						break;
					case DEMOD_CONSTELLATION_QAM4096 :
						*pQamMode = LX_DEMOD_4096QAM;
						break;
					default :
						 *pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;

				}
			}
			break;
		case LX_DEMOD_QAM:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_CONSTELLATION_QAM256:
						*pQamMode = LX_DEMOD_256QAM;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;


		case LX_DEMOD_ISDBT:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_DQPSK :
						*pQamMode = LX_DEMOD_DQPSK;
						break;
					case DEMOD_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;

		case LX_DEMOD_DVBS:
			{
				*pQamMode = LX_DEMOD_QPSK;
			}
			break;

		case LX_DEMOD_DVBS2:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_CONSTELLATION_PSK8:
						*pQamMode = LX_DEMOD_8PSK;
						break;
					case DEMOD_CONSTELLATION_APSK16 :
						*pQamMode = LX_DEMOD_16APSK;
						break;
					case DEMOD_CONSTELLATION_APSK32 :
						*pQamMode = LX_DEMOD_32APSK;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;


		default :
			DEMOD_PRINT("FAIL, UNKNOWN RF MODE \n");
			return RET_ERROR;

	}


	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_MseInfo
 * Get signal MSE info.
 *
 * @param *pSigMse [OUT] LX_DEMOD_MSE_T.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_MseInfo (LX_DEMOD_MSE_T *pSigMse)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;

	}

	pSigMse->bMse 		= 0;
	pSigMse->mse 		= signalStatus.mse_info_eq;
	pSigMse->constPwr 	= signalStatus.constPwr;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_Lock (LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState)
{

	const char * 			mod_name = "Unknown";
	UINT8			reply_operMod = 0;
	UINT8			demodLock = 0;
	static UINT8	prvLock = 0xFF;
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend 		= DEMOD_O22_GetContext();



	if (DEMOD_L2_Get_LockStatus(pFrontend, &reply_operMod, &demodLock ))
	{
		*lockState = LX_DEMOD_UNLOCKED;
		DEMOD_ERROR("Fail, DEMOD_L2_Get_LockStatus() \n");
		return RET_ERROR;
	}

	mod_name = DEMOD_L1_API_Modulation_Text(reply_operMod);

	if (demodLock == 1) {
 		*lockState = LX_DEMOD_LOCKED;
	} else {
		*lockState = LX_DEMOD_UNLOCKED;
	}

	if (prvLock != demodLock)
		DEMOD_INFO("Checking [%s] %s...\n", mod_name, (demodLock == 1) ? "Lock" : "Unlock");
	prvLock = demodLock;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_CountryGrpSetting
 * send country Group code to FW for CAM setting
 *
 * @param bEnable	  [IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_CountryGrpSetting (BOOLEAN bEnable)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend		= DEMOD_O22_GetContext();

	DEMOD_INFO("Start\n");

	if(bEnable == TRUE)
	{
		pFrontend->demod->prop->dd_country_grp.grp = DEMOD_PROP_COUNTRY_GRP_EU;
		DEMOD_NOTI("DEMOD_DD_COUNTRY_GRP_PROP_EU set\n");
	}
	else
	{
		pFrontend->demod->prop->dd_country_grp.grp = DEMOD_PROP_COUNTRY_GRP_NONE;
		DEMOD_NOTI("DEMOD_DD_COUNTRY_GRP_PROP_NONE set\n");
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_PROP_COUNTRY_GRP_CODE )!= NO_DEMOD_ERROR )
	{
		DEMOD_PRINT("Fail, DEMOD_L2_Set_Property() \n");
		return RET_ERROR;
	}

	DEMOD_NOTI("End\n");
	return RET_OK;
}

int DEMOD_O22_Get_I2C_Handle (UINT8 portI2C, UINT16 deviceID)
{
	LX_DEMOD_L2_Context *	pFrontend;
	UINT32			handle;

	DEMOD_PRINT("Start \n");

	pFrontend		= DEMOD_O22_GetContext();

	handle			= portI2C << 24;
	handle			= handle + deviceID;

	//pFrontend->demod->chip->i2c_handle = handle;

	return RET_OK;
}

int DEMOD_O22_OperModeReset(LX_DEMOD_OPER_MODE_T operMode)
{
	UINT8	reg_admd_t_pdb = 0;

	DEMOD_NOTI("OPmode is 0x%x \n", operMode);

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip6);
	CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip6, reg_admd_t_pdb, reg_admd_t_pdb);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip6);

	usleep_range(1000,2000);

	return RET_OK;
}

int DEMOD_O22_FW_Configuration_Initialize (LX_DEMOD_OPER_MODE_T operMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	UINT32			retc;

	pFrontend		= DEMOD_O22_GetContext();

	DEMOD_NOTI("OPmode is 0x%x \n", operMode);

	/* At this point, FW is loaded and started.  */
	retc = DEMOD_L2_Opermode_Configure (pFrontend , operMode) ;
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("ERROR DEMOD_L2_Opermode_Configure() 0x%02x: %s \n", retc, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}
	return RET_OK;

}

int DEMOD_O22_Opermode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_opermode;

	switch (pDemodInfo->operMode)
	{
		case LX_DEMOD_ATSC:			new_opermode = DEMOD_MODULATION_VSB; break;
		case LX_DEMOD_QAM: 			new_opermode = DEMOD_MODULATION_QAM; break;
		case LX_DEMOD_ISDBT: 		new_opermode = DEMOD_MODULATION_ISDBT; break;
		case LX_DEMOD_DVBC:			new_opermode = DEMOD_MODULATION_DVBC; break;
		case LX_DEMOD_DVBC2:			new_opermode = DEMOD_MODULATION_DVBC2; break;
		case LX_DEMOD_DVBT:			new_opermode = DEMOD_MODULATION_DVBT; break;
		case LX_DEMOD_DVBT2:			new_opermode = DEMOD_MODULATION_DVBT2; break;
		case LX_DEMOD_DVBS:			new_opermode = DEMOD_MODULATION_DVBS; break;
		case LX_DEMOD_DVBS2:			new_opermode = DEMOD_MODULATION_DVBS2; break;
		case LX_DEMOD_DTMB:			new_opermode = DEMOD_MODULATION_DTMB; break;

		default:				new_opermode = DEMOD_MODULATION_UNKNOWN; break;
	}

	return new_opermode;
}

int DEMOD_O22_Get_BW (DEMOD_CTX_T *pDemodInfo, UINT16 *pter_bandwidth_KHz)
{
	UINT16  ter_bandwidth_KHz = 8000;

	switch (pDemodInfo->operMode)
	{
			case LX_DEMOD_ATSC:					ter_bandwidth_KHz = 6000; break;
			case LX_DEMOD_QAM:					ter_bandwidth_KHz = 6000; break;
			case LX_DEMOD_ISDBT: 				ter_bandwidth_KHz = 6000; break;
			case LX_DEMOD_DVBC: 					ter_bandwidth_KHz = 8000; break;
			case LX_DEMOD_DVBT:
				{
					switch(pDemodInfo->setCfgParam.dvbt.channelBW)
					{
						case LX_DEMOD_BW_6MHZ: 		ter_bandwidth_KHz = 6000; break;
						case LX_DEMOD_BW_7MHZ:		ter_bandwidth_KHz = 7000; break;
						case LX_DEMOD_BW_8MHZ:		ter_bandwidth_KHz = 8000; break;
						default :			break;
					}
				}
				break;

			case LX_DEMOD_DVBT2:
				{
					switch(pDemodInfo->setCfgParam.dvbt2.channelBW)
					{
						case LX_DEMOD_BW_1_7MHZ: 	ter_bandwidth_KHz = 1700; break;
						case LX_DEMOD_BW_5MHZ:		ter_bandwidth_KHz = 5000; break;
						case LX_DEMOD_BW_6MHZ: 		ter_bandwidth_KHz = 6000; break;
						case LX_DEMOD_BW_7MHZ:		ter_bandwidth_KHz = 7000; break;
						case LX_DEMOD_BW_8MHZ:		ter_bandwidth_KHz = 8000; break;
						default :			break;

					}
				}
				break;

			case LX_DEMOD_DTMB:
				{
					switch(pDemodInfo->setCfgParam.dtmb.channelBW)
					{
						case LX_DEMOD_BW_6MHZ:		ter_bandwidth_KHz = 6000; break;
						case LX_DEMOD_BW_7MHZ:		ter_bandwidth_KHz = 7000; break;
						case LX_DEMOD_BW_8MHZ:		ter_bandwidth_KHz = 8000; break;
						default :			break;
					}
				}
				break;

			default:						return 0xffff;
	}

	*pter_bandwidth_KHz = ter_bandwidth_KHz;

	return RET_OK;
}

int DEMOD_O22_Get_FW_PartInfo (UINT32 *pFW_Info)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_PART_INFO	fw_part_Info;
	UINT32			FW_Info;

	pFrontend		= DEMOD_O22_GetContext();

	if(RET_OK != DEMOD_L2_Get_PartInfo(pFrontend, &fw_part_Info))
	{
		DEMOD_ERROR("DEMOD_L2_Get_PartInfo() \n");
		return RET_ERROR;
	}

	DEMOD_PRINT("fw_major  = [%d]\n", fw_part_Info.fw_major);
	DEMOD_PRINT("fw_minor  = [%d]\n", fw_part_Info.fw_minor);
	DEMOD_PRINT("fw_year   = [%d]\n", fw_part_Info.fw_year);
	DEMOD_PRINT("fw_month  = [%d]\n", fw_part_Info.fw_month);
	DEMOD_PRINT("fw_day    = [%d]\n", fw_part_Info.fw_day);
	DEMOD_PRINT("chip_type = [%d]\n", fw_part_Info.chip_type);
	DEMOD_PRINT("chip_rev  = [%d]\n", fw_part_Info.chip_rev);

	FW_Info = (fw_part_Info.fw_year << 24);
	FW_Info += (fw_part_Info.fw_month << 16);
	FW_Info += (fw_part_Info.chip_type << 8);
	FW_Info += (fw_part_Info.chip_rev << 0);


	DEMOD_PRINT("FW_Info = [%x]\n", (int)FW_Info);

	*pFW_Info = FW_Info;

	return RET_OK;
}

int DEMOD_O22_Debug_ReadREGvalue (UINT16 address, UINT32 *pData)
{
	LX_DEMOD_L2_Context *	pFrontend;
	UINT8					pvalue[4];

	pFrontend		= DEMOD_O22_GetContext();

	if(RET_OK != DEMOD_L2_GET_REG(pFrontend, address, 4, pvalue))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_GET_REG() !!!\n");
		return RET_ERROR;
	}

	*pData = ((pvalue[0]) |  (pvalue[1] << 8) | (pvalue[2] << 16) | (pvalue[3] << 24));

	return RET_OK;
}


int DEMOD_O22_Debug_ATSC_ReadREGvalue (UINT16 address, UINT32 *pData)
{
	LX_DEMOD_L2_Context *	pFrontend;

//	UINT8			vqData;
	UINT8			pvalue[4];

	pFrontend		= DEMOD_O22_GetContext();

	if(RET_OK != DEMOD_L2_GET_REG(pFrontend, address, 4, pvalue))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_GET_REG() !!!\n");
		return RET_ERROR;
	}

	*pData = ((pvalue[0]) |  (pvalue[1] << 8) | (pvalue[2] << 16) | (pvalue[3] << 24));

	DEMOD_PRINT("address = 0x%x, value = 0x%x !!!\n", address,*pData );

	return RET_OK;
}

int DEMOD_O22_Debug_ATSC_WriteREGvalue (UINT16 address, UINT32 *pData)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend		= DEMOD_O22_GetContext();

	if(RET_OK != DEMOD_L2_SET_REG(pFrontend, address, 4, *pData))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SET_REG !!!\n");
		return RET_ERROR;
	}

	DEMOD_PRINT("address = 0x%x, value = 0x%x !!!\n",address, *pData );

	return RET_OK;
}

int DEMOD_O22_Get_Dump (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_INFO("START \n");

	pFrontend		= DEMOD_O22_GetContext();

	if(RET_OK != DEMOD_L2_GetDump(pFrontend))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_GetDump() \n");
		return RET_ERROR;
	}

	return RET_OK;
}

int DEMOD_O22_ADC_Enable (void)
{
	DEMOD_INFO("START \n");

	usleep_range(10000,11000);	/* 1ms ~ 2ms */

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip7);
	CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_bias_pdb, 1);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip7);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_Signal_Information
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_Signal_Information (LX_DEMOD_SIGNAL_TOTAL_T *pSignalStatus)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend		= DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

//	*pVber = signalStatus.ber ;

	pSignalStatus->freqOff 			= signalStatus.offsetFrq_Hz/1000;
	pSignalStatus->ifAgc			= signalStatus.if_agc;
	pSignalStatus->packetError 		= signalStatus.packetError;
	pSignalStatus->vBer			= signalStatus.ber;
	pSignalStatus->sigMse.bMse		= 0;
	pSignalStatus->sigMse.mse		= signalStatus.mse_info_eq;
	pSignalStatus->sigMse.constPwr		= signalStatus.constPwr;
	pSignalStatus->snr		= signalStatus.snr_eq;
	


	DEMOD_PRINT("pSignalStatus->freqOff = %d \n", pSignalStatus->freqOff);
	DEMOD_PRINT("pSignalStatus->packetError = %d \n", pSignalStatus->packetError);
	DEMOD_PRINT("pSignalStatus->ifAgc =  %d\n", pSignalStatus->ifAgc);
	DEMOD_PRINT("pSignalStatus->vBer = %d \n", pSignalStatus->vBer);
	DEMOD_PRINT("pSignalStatus->sigMse.bMse = 0x%x \n", pSignalStatus->sigMse.bMse);
	DEMOD_PRINT("pSignalStatus->sigMse.constPwr = %d \n", pSignalStatus->sigMse.constPwr);
	DEMOD_PRINT("pSignalStatus->sigMse.mse = %d \n", pSignalStatus->sigMse.mse);
	DEMOD_PRINT("pSignalStatus->snr = %d \n", pSignalStatus->snr);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_Get_CFG_Information
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_Get_CFG_Information (LX_DEMOD_SIGNAL_TUNE_CFG_T *pSignalStatus)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend		= DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

//	*pVber = signalStatus.ber ;

	pSignalStatus->carr_mode 	= signalStatus.carr_mode;
	pSignalStatus->codeRate		= signalStatus.codeRate;
	pSignalStatus->constellation	= signalStatus.constellation;
	pSignalStatus->fftMode		= signalStatus.fftMode;
	pSignalStatus->guardInterval	= signalStatus.guardInterval;
	pSignalStatus->hierarchy	= signalStatus.hierarchy;
	pSignalStatus->hierarchy_sel	= signalStatus.hierarchy_sel;
	pSignalStatus->il_mode		= signalStatus.il_mode;
	pSignalStatus->pn_const		= signalStatus.pn_const;
	pSignalStatus->pn_mode		= signalStatus.pn_mode;
	pSignalStatus->sym_rate		= signalStatus.sym_rate;

#if 0
	DEMOD_PRINT("(%s) pSignalStatus->carr_mode = 0x%x \n", __F__, pSignalStatus->carr_mode);
	DEMOD_PRINT("(%s) pSignalStatus->codeRate = 0x%x \n", __F__, pSignalStatus->codeRate);
	DEMOD_PRINT("(%s) pSignalStatus->constellation = 0x%x \n", __F__, pSignalStatus->constellation);
	DEMOD_PRINT("(%s) pSignalStatus->fftMode = 0x%x \n", __F__, pSignalStatus->fftMode);
	DEMOD_PRINT("(%s) pSignalStatus->guardInterval = 0x%x \n", __F__, pSignalStatus->guardInterval);
	DEMOD_PRINT("(%s) pSignalStatus->hierarchy = 0x%x \n", __F__, pSignalStatus->hierarchy);
	DEMOD_PRINT("(%s) pSignalStatus->hierarchy_sel = 0x%x \n", __F__, pSignalStatus->hierarchy_sel);
	DEMOD_PRINT("(%s) pSignalStatus->il_mode = 0x%x \n", __F__, pSignalStatus->il_mode);
	DEMOD_PRINT("(%s) pSignalStatus->pn_const = 0x%x \n", __F__, pSignalStatus->pn_const);
	DEMOD_PRINT("(%s) pSignalStatus->pn_mode = 0x%x \n", __F__, pSignalStatus->pn_mode);
	DEMOD_PRINT("(%s) pSignalStatus->sym_rate = 0x%x \n", __F__, pSignalStatus->sym_rate);
#endif

	return RET_OK;
}

int DEMOD_O22_DVB_Set_MemSconfig (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT32			tdi_st_mem = gMemCfgDEMOD_DVB_TDI.memory_base;
	UINT32			djb_st_mem = gMemCfgDEMOD_DVB_DJB.memory_base;
	UINT32			risic_st_mem = gMemCfgDEMOD_DVB_RISIC.memory_base;

	pFrontend		= DEMOD_O22_GetContext();

	if(tdi_st_mem == 0 || djb_st_mem == 0 || risic_st_mem == 0)
	{
		DEMOD_WARN("Error, Wrong Memory Base Address \n");
	}
	else
	{
		DEMOD_NOTI("TDI_addr[0x%x] , DJB_addr[0x%x] , RISIC_addr[0x%x] \n", tdi_st_mem, djb_st_mem, risic_st_mem);

		if(RET_OK != DEMOD_L2_DVB_Set_BaseAddr_AXI(pFrontend, tdi_st_mem, djb_st_mem , risic_st_mem ))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_DVB_Set_BaseAddr_AXI() \n");
			return RET_ERROR;
		}
	}
	return RET_OK;

}

int DEMOD_O22_DVBC_reset (void)
{
	LX_DEMOD_L2_Context * pFrontend = DEMOD_O22_GetContext();

	DEMOD_NOTI("Start \n");
	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, admd_mip7);
	CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, admd_mip7, reg_admd_bias_pdb, 0);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, admd_mip7);

	usleep_range(1000,2000);	/* 1ms ~ 2ms */

	DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0);

	usleep_range(1000,1100);	/* 1ms ~ 2ms */

	DEMOD_NOTI("End \n");

	return RET_OK;
}

