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
**  Name:demod_common_m16.c
**
**  Description:    ABB/GBB common block.
**
**  Functions
**  Implemented:   int	DEMOD_M16P_ResetHW
**                  int DEMOD_M16P_SetI2C
**                  int DEMOD_M16P_SetInclk
**                  int DEMOD_M16P_AdcInit
**                  int DEMOD_M16P_RepeaterEnable
**                  int DEMOD_M16P_SoftwareReset
**                  int DEMOD_M16P_Serial_Control
**                  int DEMOD_M16P_Power_Save
**                  int DEMOD_M16P_StdOperModeContrl
**                  int DEMOD_M16P_NeverlockScan
**                  int DEMOD_M16P_TPOutEnable
**                  int DEMOD_M16P_Set_IF_Frq
**                  int DEMOD_M16P_Set_AGCPolarity
**                  int DEMOD_M16P_Set_SpectrumCtrl
**                  int DEMOD_M16P_Get_Id
**                  int DEMOD_M16P_Get_SpectrumStatus
**                  int DEMOD_M16P_Get_IFAGC
**                  int DEMOD_M16P_Get_OperMode
**                  int DEMOD_M16P_Get_NeverLockStatus
**                  int DEMOD_M16P_Get_CarrierFreqOffset
**                  int DEMOD_M16P_Get_TPIFStatus
**                  int DEMOD_M16P_Get_VABER
**                  int DEMOD_M16P_Get_Packet_Error
**                  int DEMOD_M16P_Get_BandWidthMode
**                  int DEMOD_M16P_Get_QAMMode
**                  int DEMOD_M16P_Get_MseInfo
**                  int DEMOD_M16P_Get_Lock
**                  int DEMOD_M16P_VSB_Get_SysLockTime
**                  int DEMOD_M16P_VSB_Get_FecLockTime
**
**                  int DEMOD_M16P_ANALOG_ResetHW
**                  int DEMOD_M16P_ANALOG_SetI2C
**                  int DEMOD_M16P_ANALOG_Set_AbbMode
**                  int DEMOD_M16P_ANALOG_Set_WorkAround
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

#include "demod_impl.h"
#include "demod_common_m16p.h"
//#include "demod_reg_m16.h"

#if 0
#endif

UINT8 gM16PGBB_PowerOnInit = 1;

#if 0
#endif

LX_DEMOD_L2_Context gM16P_LGDBB_Frontend;
static int	gDemodFwMemConfigured = 0;


/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_M16P_Get_Lock_FEC
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_FEC( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{

	*lockStatus = 0;

	return RET_OK;

}




/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_M16P_Get_Lock_TR
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_TR( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{

	*lockStatus = 0;

	return RET_OK;

}




/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_M16P_Get_Lock_CARR
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_CARR( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{

	*lockStatus = 0;

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_PSYNC( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{

	*lockStatus = 0;

	return RET_OK;

}




/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_M16P_Get_Lock_TPS
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_TPS( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{

	*lockStatus = 0;

	return RET_OK;

}




/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_M16P_Get_Lock_AGC
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_AGC( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{

   *lockStatus = 0;

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_M16P_Get_Lock_Mode_Det( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;

}


#if 0
#endif


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M16P_ResetHW(void)
{

	UINT32	swrst_f24m_bb;

	#if 1
	UINT32 dmd_inck_sel_dmdpll;
	UINT32 dmd_inck_divsel_dmdpll;
	UINT32 dmd_bypass_dmdpll;

	UINT32	dmd_mc_dmdpll;
	UINT32	dmd_div_adc_dmdpll;
	UINT32	dmd_div1_dmdpll;
	UINT32	dmd_div5_dmdpll;
	#endif

#if 1
	#if 0  // these below is moved to I2C_drv.c because of async resume on instant boot
		ACE_REG_M16PA0_RdFL(soft_reset_0);

		if(ACE_REG_M16PA0_RdFd(soft_reset_0,swrst_f24m) == 1)
		{
			//ACE_REG_M16PA0_RdFL(soft_reset_0);
			ACE_REG_M16PA0_Wr01(soft_reset_0,swrst_f24m,0);
			ACE_REG_M16PA0_WrFL(soft_reset_0);
			DEMOD_PRINT_ALWAYS("[KDRV_DEMOD] NEED TO BE RESET swrst_f24m \n");


		}
		else
		{
			DEMOD_PRINT_ALWAYS("[KDRV_DEMOD] ALREADY RESET swrst_f24m \n");
		}

		if(ACE_REG_M16PA0_RdFd(soft_reset_0,swrst_f24m_bb) == 1)
		{
			//ACE_REG_M16PA0_RdFL(soft_reset_0);
			ACE_REG_M16PA0_Wr01(soft_reset_0,swrst_f24m_bb,0);
			ACE_REG_M16PA0_WrFL(soft_reset_0);
			DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127] NEED TO BE RESET swrst_f24m_bb \n");

		}
		else
		{
			DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127] ALREADY RESET swrst_f24m_bb \n");
		}

	#endif




		DEMOD_PRINT("[KDRV_DEMOD] DEMOD_ResetHW start !! \n");

		ACE_REG_M16PA0_RdFL(dbb_00);
		ACE_REG_M16PA0_Wr01(dbb_00, dbb_reset, 1);
		ACE_REG_M16PA0_WrFL(dbb_00);

		usleep_range(1000,2000);	/* 1ms ~ 2ms */


		ACE_REG_M16PA0_Wr01(dbb_00, dbb_reset, 0);
		ACE_REG_M16PA0_WrFL(dbb_00);

		usleep_range(3000,4000);	/* 3ms ~ 4ms */

		ACE_REG_M16PA0_Wr01(dbb_00, dbb_reset, 1);
		ACE_REG_M16PA0_WrFL(dbb_00);


#if 0 //check 20150325
		ACE_REG_M16PA0_RdFL(dmd_abbpll_0); //ABB clock disable

		ACE_REG_M16PA0_Wr01(dmd_abbpll_0, dmd_pdb_amdp, 0);

		ACE_REG_M16PA0_WrFL(dmd_abbpll_0);

#endif

	#if 1
		dmd_inck_sel_dmdpll = 0; // check!!!
		dmd_inck_divsel_dmdpll = 0;
		dmd_bypass_dmdpll = 1;
		ACE_REG_M16PA0_RdFL(dmd_00);
		ACE_REG_M16PA0_Wr03(dmd_00,dmd_inck_sel_dmdpll,dmd_inck_sel_dmdpll, dmd_inck_divsel_dmdpll,dmd_inck_divsel_dmdpll, dmd_bypass_dmdpll,dmd_bypass_dmdpll);
		ACE_REG_M16PA0_WrFL(dmd_00);
		DEMOD_PRINT("[KDRV_DEMOD] dmd_inck_sel_dmdpll = %d \n",dmd_inck_sel_dmdpll);
		DEMOD_PRINT("[KDRV_DEMOD] dmd_inck_divsel_dmdpll = %d \n",dmd_inck_divsel_dmdpll);
		DEMOD_PRINT("[KDRV_DEMOD] dmd_bypdmd_bypass_dmdpllass_gbbp = %d \n",dmd_bypass_dmdpll);


		dmd_mc_dmdpll	   = 0x10;
		dmd_div_adc_dmdpll = 0x1;
		dmd_div1_dmdpll    = 0x1;
		dmd_div5_dmdpll    = 0x0;
		ACE_REG_M16PA0_RdFL(dmd_00);
		ACE_REG_M16PA0_Wr04(dmd_00,dmd_mc_dmdpll,dmd_mc_dmdpll, dmd_div_adc_dmdpll,dmd_div_adc_dmdpll, dmd_div1_dmdpll,dmd_div1_dmdpll, dmd_div5_dmdpll, dmd_div5_dmdpll);
		ACE_REG_M16PA0_WrFL(dmd_00);
	#endif


#if 1  // For debugging


		ACE_REG_M16PA0_RdFL(soft_reset_00);
		ACE_REG_M16PA0_Rd01(soft_reset_00, swrst_f24m_bb, swrst_f24m_bb);

		if(swrst_f24m_bb == 1)
		{
			DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127] ### chungiii ooops!!! STILL	swrst_f24m_bb is reset state  \n");

		}
		else
		{
			DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127]	### chungiii OK!!!! swrst_f24m_bb is normal state  \n");

		}
#endif



		gM16PGBB_PowerOnInit = 1;

		DEMOD_PRINT("[KDRV_DEMOD] DEMOD_ResetHW end !! \n");

#endif





		return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_SetI2C(void)
{

#if 1
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetI2C Start !! \n");

	ACE_REG_M16PA0_RdFL(dbb_00);

	ACE_REG_M16PA0_Wr01(dbb_00, dbb_i2csel, 0);

	ACE_REG_M16PA0_WrFL(dbb_00);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetI2C end !! \n");

#endif
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_SetInclk.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M16P_SetInclk(LX_DEMOD_INCLK_SEL_T *inclk)
{
#if 1
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetInclk Start !! \n");

	ACE_REG_M16PA0_RdFL(dmd_00);

	switch(*inclk)
	{
		case LX_DEMOD_ARM_SETTING:
		{
			ACE_REG_M16PA0_Wr01(dmd_00, dmd_inck_sel_dmdpll, 0);
		}
		break;

		case LX_DEMOD_EXTERN_PIN:
		{

			ACE_REG_M16PA0_Wr01(dmd_00, dmd_inck_sel_dmdpll, 1);
		}
		break;

		default:
			DEMOD_PRINT("Invalid LX_DEMOD_INCLK_SEL_T type\n");
			return -1;
	}

	ACE_REG_M16PA0_WrFL(dmd_00);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetInclk End !! \n");

#endif


	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_AdcInit.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_AdcInit(void)
{

#if 1
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_M16P_AdcInit Start !! \n");


#if 0
	ACE_REG_M16PA0_RdFL(dmd_adc_2);

	ACE_REG_M14B0_Wr02(dmd_adc_2, dmd_adc_pdbm, 1, dmd_adc_pdb, 1 );

	ACE_REG_M16PA0_WrFL(dmd_adc_2);


	ACE_REG_M16PA0_RdFL(dmd_gbbpll_3);

	ACE_REG_M16PA0_Wr01(dmd_gbbpll_3, dmd_pllctrl_add_gbbp, 0x9);

	ACE_REG_M16PA0_WrFL(dmd_gbbpll_3);


	ACE_REG_M16PA0_RdFL(dmd_abbpll_4);

	ACE_REG_M16PA0_Wr01(dmd_abbpll_4, dmd_pre_fd_amdp, 0x1);

	ACE_REG_M16PA0_WrFL(dmd_abbpll_4);

#endif

	//ADC power on (0: power down, 1: power on)
	ACE_REG_M16PA0_RdFL(dmd_01);
	ACE_REG_M16PA0_Wr01(dmd_01, dmd_adc_pdb, 1);
	ACE_REG_M16PA0_WrFL(dmd_01);

	// ADC reference voltage selection
	// (00: 1.0Vpp, 01: 1.2Vpp, 10: 1.4Vpp, 11: 1.6Vpp)
	ACE_REG_M16PA0_RdFL(dmd_01);
	ACE_REG_M16PA0_Wr01(dmd_01, dmd_adc_vrefsel, 0x3);
	ACE_REG_M16PA0_WrFL(dmd_01);


	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_M16P_AdcInit end !! \n");

#endif


	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_RepeaterEnable.
 * Enable / Disable GBB I2C repeater function
 *
 * @param bEnable [IN] 	BOOLEAN - Enable/Disable I2C repeater
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_RepeaterEnable(BOOLEAN bEnable)
{

	UINT16 	address;
	UINT8 	rdBuffer;
	UINT8 	wrBuffer;

	DEMOD_PRINT("before[DEMOD M16Pp]   DEMOD_M16P_RepeaterEnable  ###### chungiii \n");

	//address= 0x7103;
	address= 0x7103;

	if(RET_OK != DEMOD_I2C_Read(address, 1, &rdBuffer))
	{
		DEMOD_PRINT("[M16P DBB I2C] FAIL (%s:%d) DEMOD_I2C_Read  !!!\n", __F__, __L__);
		return RET_ERROR;
	}
	else
	{
		if(bEnable == TRUE)
			wrBuffer = rdBuffer & 0x7f;
		else
			wrBuffer = rdBuffer | 0x80;

		if(RET_OK != DEMOD_I2C_Write(address, 1, &wrBuffer))
		{
			DEMOD_PRINT("[LGDBB  I2C] FAIL (%s:%d) DEMOD_I2C_Write !!!\n", __F__, __L__);
			return RET_ERROR;
		}
	}

	return RET_OK;

}






/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_SoftwareReset.
 * Reset DVB module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_SoftwareReset(void)
{

	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;

	if (RET_OK != DEMOD_L1_SET_DD_Restart(pFrontend->demod))
	{
		DEMOD_PRINT("[DEMOD M16P] FAIL (%s:%d) DEMOD_L1_SET_DD_Restart() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
	DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_L1_SET_DD_Restart OK!!!! \n", __F__, __L__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Serial_Control
 * Control TS output mode(serial/Parallel)
 *
 * @param bEnable 	[IN] Serial(TRUE) / Parallel(FALSE)
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Serial_Control(BOOLEAN bEnable)
{

	return	RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Power_Save
 * Enable/Disable power save mode
 *
 * @param bEnable 	[IN] power save mode(TRUE) / normal mode(FALSE)
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M16P_Power_Save(BOOLEAN bEnable)
{
	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;

	if(bEnable == TRUE)
	{
		if (DEMOD_L2_Standby(pFrontend)!= NO_DEMOD_ERROR )
		{
			DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_L2_Standby  Fail!! \n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	else
	{
		if (DEMOD_L2_WakeUp(pFrontend)!= NO_DEMOD_ERROR )
		{
			DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_L2_WakeUp  Fail!! \n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}

	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_StdOperModeContrl
 * Set standard operation mode, Bandwidth and symbol rate
 *
 * @param *InitParam [IN] LX_DEMOD_INIT_PARAM_T - operation RF Mode, bandWidth, Symbol rate
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_StdOperModeContrl( LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr)
{

//	UINT32 dmd_inck_sel_dmdpll;
//	UINT32 dmd_inck_divsel_dmdpll;
//	UINT32 dmd_bypass_dmdpll;

//	UINT32	dmd_mc_dmdpll;
//	UINT32	dmd_div_adc_dmdpll;
//	UINT32	dmd_div1_dmdpll;
//	UINT32	dmd_div5_dmdpll;

	LX_DEMOD_L2_Context *pFrontend;

	pFrontend		= &gM16P_LGDBB_Frontend;

	DEMOD_PRINT_ALWAYS(" #########################chungiii== @ %s  ==(oper = 0x%x)\n",__F__,operMode);

	/* becuase M16+ demod memory region is initialized to CMA, driver should acquire
	 * demod memory with "cma alloc" from kernel before the first ISDB-T channel change.
	 * NEVER free the allocated memory.
	 *
	 * raxis.lim (2016/06/27)
	 * To save BSP memory, demod will allocate its runtime memory from "te_shared" hma pool.
	 */
#if 0
	if(operMode == LX_DEMOD_ISDBT && gMemCfgDEMOD.memory_base == 0x0)
	{
		UINT32 demod_mem = (UINT32)hma_alloc("te_shared", gMemCfgDEMOD.memory_size, 0x1000);

		DEMOD_CHECK_CODE(demod_mem==0x0, /* nop */, "demod_mem alloc failed. demod_mem might be already allocated\n");

		gMemCfgDEMOD.memory_base	= demod_mem;

		if(RET_OK != DEMOD_ISDBT_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_ISDBT_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}


	}
#else
	if(operMode == LX_DEMOD_ISDBT)
	{
		if( gMemCfgDEMOD.memory_base == 0x0)
		{
			UINT32 demod_mem = (UINT32)hma_alloc("te_shared", gMemCfgDEMOD.memory_size, 0x1000);

			DEMOD_CHECK_CODE(demod_mem==0x0, /* nop */, "demod_mem alloc failed. demod_mem might be already allocated\n");

			gMemCfgDEMOD.memory_base = demod_mem;
		}

		if( !gDemodFwMemConfigured && RET_OK != DEMOD_ISDBT_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_ISDBT_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}

		gDemodFwMemConfigured = 1;	// Demod FW is configured. DO NOT configure again !
	}

#endif

#if 0  ///debugging chungiii
	dmd_inck_sel_dmdpll = 0; // check!!!
	dmd_inck_divsel_dmdpll = 0;
	dmd_bypass_dmdpll = 1;
	ACE_REG_M16PA0_RdFL(dmd_00);
	ACE_REG_M16PA0_Wr03(dmd_00,dmd_inck_sel_dmdpll,dmd_inck_sel_dmdpll, dmd_inck_divsel_dmdpll,dmd_inck_divsel_dmdpll, dmd_bypass_dmdpll,dmd_bypass_dmdpll);
	ACE_REG_M16PA0_WrFL(dmd_00);
	DEMOD_PRINT("[KDRV_DEMOD] dmd_inck_sel_dmdpll = %d \n",dmd_inck_sel_dmdpll);
	DEMOD_PRINT("[KDRV_DEMOD] dmd_inck_divsel_dmdpll = %d \n",dmd_inck_divsel_dmdpll);
	DEMOD_PRINT("[KDRV_DEMOD] dmd_bypdmd_bypass_dmdpllass_gbbp = %d \n",dmd_bypass_dmdpll);
#endif


#if 0
	switch(operMode)
	{
		case LX_DEMOD_ATSC:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_VSB;
			 //24MHz 384MHz
			 dmd_mc_dmdpll		= 0x10;
			 dmd_div_adc_dmdpll = 0x1;
			 dmd_div1_dmdpll	= 0x1;
			 dmd_div5_dmdpll	= 0x0;
			break;

		case LX_DEMOD_QAM:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_QAM;
			 //24MHz 384MHz
			 dmd_mc_dmdpll		= 0x10;
			 dmd_div_adc_dmdpll = 0x1;
			 dmd_div1_dmdpll	= 0x1;
			 dmd_div5_dmdpll	= 0x0;

			break;

		case LX_DEMOD_ISDBT:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_ISDBT;
			 //24MHz 384MHz
			 dmd_mc_dmdpll		= 0x10;
			 dmd_div_adc_dmdpll = 0x1;
			 dmd_div1_dmdpll	= 0x1;
			 dmd_div5_dmdpll	= 0x0;

			break;

		case LX_DEMOD_DVBT:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_DVBT;
			 //24MHz 384MHz
			 dmd_mc_dmdpll		= 0x10;
			 dmd_div_adc_dmdpll = 0x1;
			 dmd_div1_dmdpll	= 0x1;
			 dmd_div5_dmdpll	= 0x0;

			break;

		case LX_DEMOD_DVBC:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_DVBC;
			 //24MHz 384MHz
			 dmd_mc_dmdpll		= 0x10;
			 dmd_div_adc_dmdpll = 0x1;
			 dmd_div1_dmdpll	= 0x1;
			 dmd_div5_dmdpll	= 0x0;
			break;

		default :
			DEMOD_PRINT_ALWAYS("[DEMOD M16P](%s,%d) Invaild Opermode parameter !!!\n",__F__, __L__);
			return RET_ERROR;
	}

		ACE_REG_M16PA0_RdFL(dmd_00);
		ACE_REG_M16PA0_Wr04(dmd_00,dmd_mc_dmdpll,dmd_mc_dmdpll, dmd_div_adc_dmdpll,dmd_div_adc_dmdpll, dmd_div1_dmdpll,dmd_div1_dmdpll, dmd_div5_dmdpll, dmd_div5_dmdpll);
		ACE_REG_M16PA0_WrFL(dmd_00);

#endif




#if 0
	if(RET_OK != DEMOD_L2_Switch_to_standard(pFrontend,new_standard))
	{
		DEMOD_PRINT("[M16P LGDBB] FAIL (%s:%d) DEMOD_L2_Switch_to_standard !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	OS_MsecSleep(20);

#if 0
	printk("#####################chungiii check tune mode [0x%x]\n", g_demod_ctx_info[0].setCfgParam.vsb.tuneMode);
	if(g_demod_ctx_info[0].setCfgParam.vsb.tuneMode == 0x30)
	{
		OS_MsecSleep(20);
		printk("#####################chungiii scanning delay 20ms \n");
	}
	else
	{
		printk("#####################chungiii tuning no delay \n");
	}

#endif




#if 1
	DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) ChangeTransMedia = %s !!!\n", __F__, __L__,(new_standard == DEMOD_DD_MODE_PROP_MODULATION_VSB) ? "VSB" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_QAM) ? "QAM" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_ISDBT) ? "ISDBT" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_ATSC3) ? "ATSC3.0" : "NTSC");

#endif


#endif





	return RET_OK;

}


/**
 * DEMOD_M16P_NeverlockScan
 * Get the neverlock flag indicator.
 *
 * @param	*pDemodInfo			[IN] DEMOD_CTX_T.
 * @param	ResetOn				[IN] 	LX_DEMOD_FLAG_T  - force to initialize the postjob.
 * @param	*pScanProcessing		[OUT] LX_DEMOD_FLAG_T- the flag that scan is done or not done.
 * @param	*pScanLock			[OUT] LX_DEMOD_LOCK_STATE_T - scan lock result.
 * @return if Succeeded - RET_OK else-TU_ERROR
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/
int DEMOD_M16P_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock)
{

	static	LX_DEMOD_LOCK_STATE_T	_demodScanLock	= LX_DEMOD_UNKOWN_STATE;

	unsigned int elapsedTime = 0;
	static	unsigned int	_neverLockResetTime = 0;

	static unsigned int _maxTimeOut = 0;


	LX_DEMOD_LOCK_STATE_T neverLockStatus;
	LX_DEMOD_OPER_MODE_T scanMode;


	scanMode = pDemodInfo->operMode;

	if(LX_DEMOD_FLAG_ON == ResetOn)
	{

		*pScanProcessing = LX_DEMOD_FLAG_ING;
		*pScanLock	= LX_DEMOD_UNLOCKED;

		switch(scanMode)
		{
			case LX_DEMOD_DVBT :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_450;
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

			default :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;

		}


		_neverLockResetTime = jiffies_to_msecs(jiffies);

		return RET_OK;
	}


	if (RET_OK != DEMOD_M16P_Get_NeverLockStatus(scanMode, &neverLockStatus))
	{
		DEMOD_PRINT("^r^[M16_DVB DTV] FAIL (%s:%d) KADP_DEMOD_VQI_ChanScan_GetStatus() !!!\n", __F__, __L__);
		*pScanLock	= LX_DEMOD_UNLOCKED;
		return RET_ERROR;
	}

	switch (neverLockStatus)
	{

		case LX_DEMOD_DETECTION_PROCESSING:
			{

				elapsedTime = jiffies_to_msecs(jiffies) - _neverLockResetTime;

				if(elapsedTime > _maxTimeOut)
				{
					*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
					_demodScanLock		= LX_DEMOD_UNLOCKED;
					printk( "[DEMOD M16] NEVERSCAN : LX_DEMOD_NEVERLOCK DETECTION is on processing \n");

				}
			}
			break;

		case LX_DEMOD_DETECTION_FAIL:
			{
				*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
				_demodScanLock		= LX_DEMOD_UNLOCKED;
				printk( "[DEMOD M16] NEVERSCAN :  LX_DEMOD_NEVERLOCK DETECTION FAIL  \n");
			}
			break;

		case LX_DEMOD_DETECTED:
			{
				*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
				_demodScanLock		= LX_DEMOD_TR_LOCK;
				printk( "[DEMOD M16] NEVERSCAN :  LX_DEMOD_NEVERLOCK DETECTED	!! \n");

			}
			break;


		default:
			_demodScanLock	= LX_DEMOD_UNLOCKED;
			break;
	}

	*pScanLock	= _demodScanLock;

	return RET_OK;
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_TPOutEnable
 * Enable/Diable the output of TP
 *
 * @param bEnable	  [IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_TPOutEnable(BOOLEAN bEnable)
{

	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;

	if(bEnable == TRUE)
	{
		pFrontend->demod->prop->dd_tpout_mode.tpOutEn = DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_ENABLE;
	}
	else
	{
		pFrontend->demod->prop->dd_tpout_mode.tpOutEn = DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_DISABLE;
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_DD_TPOUT_MODE_PROP_CODE )!= NO_DEMOD_ERROR )
	{
		DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_L2_Set_Property  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}


	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Set_IF_Frq
 * Set IF frequency registers on DVB-C mode.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Set_IF_Frq(UINT32 ifFrq)
{
#if 1
	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;


	if(ifFrq == LX_DEMOD_IF_FREQ_05_000_KHZ)
	{
		pFrontend->demod->prop->dd_if_freq.if_freq = DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;
		DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_M16P_Set_IF_Frq  5MHz \n", __F__, __L__);
	}
	else if(ifFrq == LX_DEMOD_IF_FREQ_06_000_KHZ)
	{
		pFrontend->demod->prop->dd_if_freq.if_freq = DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
		DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_M16P_Set_IF_Frq  6MHz \n", __F__, __L__);
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

#endif


	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Set_AGCPolarity
 * Set IF frequency registers on DVB.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Set_AGCPolarity(LX_DEMOD_AGC_POLAR_T agcPola)
{
	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;


	if(agcPola == LX_DEMOD_AGC_ACTIVE_HIGH)
	{
		pFrontend->demod->prop->dd_agc.agc_pol  = DEMOD_DD_AGC_PROP_POLARITY_NORMAL;;
		DEMOD_PRINT("[M16P LGDBB] (%s:%d) LX_DEMOD_AGC_ACTIVE_HIGH \n", __F__, __L__);
	}
	else
	{
		pFrontend->demod->prop->dd_agc.agc_pol  = DEMOD_DD_AGC_PROP_POLARITY_INVERSION;;
		DEMOD_PRINT("[M16P LGDBB] (%s:%d) DEMOD_DD_AGC_PROP_POLARITY_INVERSION \n", __F__, __L__);
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_DD_AGC_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_DD_AGC_PROP_CODE  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Set_SpectrumCtrl.
 * Enable/Disable automatic spectrum mode detection.
 *
 * @param  bAutoEnable [IN] BOOLEAN - enable/disable.
 * @param  bSpecInvEnable [IN] BOOLEAN - enable/disable.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Set_SpectrumCtrl(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable)
{

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_Id.
 * Get GBB demod ID.
 *
 * @param *cell_id [OUT] UINT16 - GBB demod ID
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_Id(UINT16 *pId)
{
	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_SpectrumInvStatus
 * Get spectrum mode state on DVB.
 *
 * @param *pSpectrumAuto 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_AUTO, LX_DEMOD_MANUAL.
 * @param *pSpectrumInv 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_NORMAL, LX_DEMOD_INVERSION.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_SpectrumStatus(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv)
{


	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	LX_DEMOD_LOCK_STATE_T SpectrumAuto = LX_DEMOD_AUTO;
	LX_DEMOD_LOCK_STATE_T SpectrumInv;
//	LX_DEMOD_OPER_MODE_T opmode;

	pFrontend = &gM16P_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;;
	}

	switch (signalStatus.spInv)
	{
		case DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_INVERTED : SpectrumInv = LX_DEMOD_INVERSION; break;
		case DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_NORMAL  : SpectrumInv = LX_DEMOD_NORMAL; break;
		default:
			break;

	}

	if (DEMOD_L2_Get_Property(pFrontend, DEMOD_DD_MODE_PROP_CODE))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_Get_Property() \n", __F__);
		return RET_ERROR;;
	}

		SpectrumAuto = pFrontend->demod->prop->dd_mode.specinvauto;


	*pSpectrumAuto = SpectrumAuto;
	*pSpectrumInv = SpectrumInv;

	DEMOD_PRINT("####  [%s]  check spectrum  auto ? manual [%d]\n",  __F__, SpectrumAuto);
	DEMOD_PRINT("####  [%s]  check spectrum  inverted ?    [%d]\n",  __F__, SpectrumInv);



	return RET_OK;


}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_IFAGCValue
 * Get IF AGC value on DVB.
 *
 * @param *pIfagcValue 	[OUT] UINT16
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_IFAGC(UINT16 *pIfAgc)
{

	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = &gM16P_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;;
	}

	*pIfAgc = signalStatus.if_agc;
	DEMOD_PRINT("(%s) IF AGC = 0x%x \n", __F__, *pIfAgc);

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_OperMode.
 * Get GBB operation mode.
 *
 * @param *pOperMode [OUT] LX_DEMOD_VQI_RF_MODE_T - GBB RF demodulation mode
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_OperMode(LX_DEMOD_OPER_MODE_T *pOperMode)
{

	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_OPER_MODE_T reply_opmode;

	UINT8 retCode = 0;

	pFrontend = &gM16P_LGDBB_Frontend;

	//printk("#################################   before  check DEMOD_M16P_Get_OperMode reply opmode [%d]\n", reply_opmode);

	retCode = DEMOD_L1_GET_DD_Status(pFrontend->demod);

	if(NO_DEMOD_ERROR != retCode)
	{
		*pOperMode = LX_DEMOD_UNKOWN_OPMODE;

		return RET_ERROR;
	}

	switch (pFrontend->demod->rsp->dd_status.reply_operMod)
	{
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:		reply_opmode = LX_DEMOD_ATSC; break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM: 		reply_opmode = LX_DEMOD_QAM; break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT: 		reply_opmode = LX_DEMOD_ISDBT ; break;
		case    DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:		reply_opmode = LX_DEMOD_DVBC ; break;
		case    DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:		reply_opmode = LX_DEMOD_DVBT ; break;


		default :
			DEMOD_PRINT_ALWAYS("[DEMOD M16P](%s,%d) LX_DEMOD_UNKOWN_OPMODE!!!\n",__F__, __L__);
			return RET_ERROR;

	}

	*pOperMode = reply_opmode;
	//printk("######check DEMOD_M16P_Get_OperMode reply opmode [%d]\n", reply_opmode);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_NeverLockStatus
 * Get neverlock state on DVB.
 *
 * @param scanMode 	[OUT] LX_DEMOD_OPER_MODE_T
 * @param *pNeverLockStatus 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMODLOCKED, LX_DEMOD_UNLOCKED.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_NeverLockStatus(LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus)
{

	LX_DEMOD_L2_Context *pFrontend;

	UINT8 neverlock;

	pFrontend = &gM16P_LGDBB_Frontend;

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
 * DEMOD_M16P_Get_CarrierFreqOffset
 * Get carrier offset frequency .
 *
 * @param *pFreqOff 	[OUT] SINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_CarrierFreqOffset(SINT32 *pFreqOff)
{

	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	LX_DEMOD_L2_Context *pFrontend;
	
	SINT32	freqOffset;
	
	pFrontend = &gM16P_LGDBB_Frontend;


	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	freqOffset = signalStatus.offsetFrq_Hz/1000;

	DEMOD_PRINT("[M16P LGDBB] (freqOffset: %d) \n", freqOffset);

	*pFreqOff = freqOffset ;

	return RET_OK;


#if 0

	UINT8	carrfreqoffset_7_0;
	UINT8	carrfreqoffset_15_8;

	SINT32 tempCarrierOffset = 0;
	SINT32 carrierOffset;

	*pFreqOff = 0;

	Common_RdFL(common_mon28);	//regAddr = 0x009c, COMMON_MON[28]
	Common_Rd01(common_mon28,carrfreqoffset_15_8,carrfreqoffset_15_8); //CARRFREQOFFSET[15:8]
	tempCarrierOffset = (carrfreqoffset_15_8 << 8 ) ;

	Common_RdFL(common_mon29);	//regAddr = 0x009d, COMMON_MON[29]
	Common_Rd01(common_mon29,carrfreqoffset_7_0,carrfreqoffset_7_0); //CARRFREQOFFSET[7:0]
	tempCarrierOffset += (carrfreqoffset_7_0 << 0 ) ;

	if ( tempCarrierOffset & 0x8000 ) tempCarrierOffset = ((0xffff0000) | tempCarrierOffset) ;



	carrierOffset =  tempCarrierOffset * 61 ;	// Carrier frequency offset [MHz] = CARRIERFREQOFFSET / (2^14), 2^14 = 16384
												// 1000000[Hz] / 16384 = 61
	carrierOffset = carrierOffset / 1000 ;		// [Hz] / 1000 -> [KHz]

	*pFreqOff = carrierOffset;

	DEMOD_PRINT("[DEMOD M16P] Carrier Offset freq = %d [KHz] !!!\n",*pFreqOff);

	return RET_OK;

#endif


}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_TPIFStatus
 * Get the status of TP IF function (active or inactive)
 *
 * @param pbEnable	  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_TPIFStatus(BOOLEAN *pbEnable)
{

	*pbEnable = TRUE;

	return RET_OK;


}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_VABER
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_VABER(UINT32 *pVber)
{
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	DEMOD_PRINT("[M16P LGDBB] (BER: %d) \n", *pVber);

	*pVber = signalStatus.ber ;

	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_Packet_Error
 * Get packet error on DVB
 *
 * @param *pSnr 	[OUT] UINT8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_Packet_Error(UINT32 *pError)
{

	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;
	pFrontend = &gM16P_LGDBB_Frontend;

	//printk("#################################   before  check DEMOD_M16P_Get_Packet_Error\n");

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	*pError = signalStatus.packetError;

	DEMOD_PRINT(" [M16P LGDBB] DEMOD_M16P_Get_Packet_Error *pError = %d  \n",*pError);

	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_BandWidthMode
 * Get the information of bandwidth .
 *
 * @param *ChannelBW 	[OUT] LX_DEMOD_BWMODE_T - 6, 7 and 8 MHZ.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_BandWidthMode( LX_DEMOD_BWMODE_T *ChannelBW )
{

	*ChannelBW = LX_DEMOD_BW_UNKNOWN;

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_QAMMode
 * Get the information of QAM mode .
 *
 * @param *pQamMode [OUT] LX_DEMOD_RF_MODE_T - 16QAM, 32QAM, 64QAM, 128QAM, 256QAM, QPSK.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_QAMMode( LX_DEMOD_RF_MODE_T *pQamMode )
{
	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;
	LX_DEMOD_OPER_MODE_T mode;

	pFrontend = &gM16P_LGDBB_Frontend;

	if(RET_OK != DEMOD_M16P_Get_OperMode(&mode))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M16P_Get_OperMode() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_L2_SignalStatus	Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}
	//printk("DEMOD_L2_SignalStatus============ signalStatus.constellation[%d]  \n ", signalStatus.constellation);


	switch(signalStatus.constellation)
	{
		case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64:
				*pQamMode = LX_DEMOD_64QAM;
		break;

		case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256:
				*pQamMode = LX_DEMOD_256QAM;
		break;

		default:
				*pQamMode = LX_DEMOD_UNKOWN_MODE;
		break;
	}

	switch(mode)
	{
		case LX_DEMOD_DVBT:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
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
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32 :
						*pQamMode = LX_DEMOD_32QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
						 *pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128 :
						 *pQamMode = LX_DEMOD_128QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256 :
						*pQamMode = LX_DEMOD_256QAM;
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
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256:
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
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK :
						*pQamMode = LX_DEMOD_DQPSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
						*pQamMode = LX_DEMOD_64QAM;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;


		default :
			DEMOD_PRINT("[DEMOD M16] FAIL,(%s:%d) UNKNOWN RF MODE !!!\n", __F__, __L__);
			return RET_ERROR;

	}


	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_MseInfo
 * Get signal MSE info.
 *
 * @param *pSigMse [OUT] LX_DEMOD_MSE_T.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_MseInfo( LX_DEMOD_MSE_T *pSigMse)
{

	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;
	pFrontend = &gM16P_LGDBB_Frontend;


	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	pSigMse->bMse = 0;
	pSigMse->mse = signalStatus.mse_info;
	pSigMse->constPwr = signalStatus.constPwr;

	return RET_OK;


}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_Get_Lock(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState)
{

	UINT8 	reply_operMod = 0;
	UINT8	demodLock	= 0;


	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend		= &gM16P_LGDBB_Frontend;


	if (DEMOD_L2_Get_LockStatus(pFrontend, &reply_operMod, &demodLock ))
	{
		*lockState = LX_DEMOD_UNLOCKED;
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_Get_LockStatus() \n", __F__);
		return RET_ERROR;
	}


	switch(reply_operMod)
	{
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:
				DEMOD_PRINT("checking [%s] lock...\n", "VSB");
		break;

		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM:
				DEMOD_PRINT("checking [%s] lock...\n", "QAM");
		break;

		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT:
				DEMOD_PRINT("checking [%s] lock...\n", "ISDBT");
		break;

		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:
				DEMOD_PRINT("checking [%s] lock...\n", "DVBC");
		break;

		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:
				DEMOD_PRINT("checking [%s] lock...\n", "DVBT");
		break;



		default:
		break;
	}


	if ( demodLock == 1)
	{
//		DEMOD_PRINT("[M16P LGDBB] (%s) demod locked !!!\n",  __F__);
 		*lockState = LX_DEMOD_LOCKED;
	}
	else
	{
//		DEMOD_PRINT("[M16P LGDBB] (%s) demod unlocked !!!\n",  __F__);
		*lockState = LX_DEMOD_UNLOCKED;
	}

	return RET_OK;

}


int DEMOD_M16P_VSB_Get_SysLockTime(UINT16 *pSyslocktime)
{

	return RET_OK;


}

int DEMOD_M16P_VSB_Get_FecLockTime(UINT16 *pFeclocktime)
{


	return RET_OK;

}

/**
 * DEMOD_M16P_FecReset.
 * Reset Fec reset by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_FecReset(BOOLEAN bReset)
{

	return RET_OK;
}




#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_ANALOG_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/


int DEMOD_M16P_ANALOG_ResetHW(void)
{

	UINT32 swrst_f24m_bb;
	DEMOD_PRINT("[KDRV_DEMOD] ADEMOD_ResetHW start !! \n");

	ACE_REG_M16PA0_RdFL(abb_00);
	ACE_REG_M16PA0_Wr01(abb_00, abb_reset, 1);
	ACE_REG_M16PA0_WrFL(abb_00);

	usleep_range(1000,10000);	/* 1ms ~ 10ms */


	ACE_REG_M16PA0_Wr01(abb_00, abb_reset, 0);
	ACE_REG_M16PA0_WrFL(abb_00);

	usleep_range(3000,10000);	/* 3ms ~ 10ms */

    	ACE_REG_M16PA0_Wr01(abb_00, abb_reset, 1);
	ACE_REG_M16PA0_WrFL(abb_00);



#if 1  // For debugging


	ACE_REG_M16PA0_RdFL(soft_reset_00);
	ACE_REG_M16PA0_Rd01(soft_reset_00, swrst_f24m_bb, swrst_f24m_bb);

	if(swrst_f24m_bb == 1)
	{
		DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127] ### chungiii ooops!!! STILL  swrst_f24m_bb is reset state  \n");

	}
	else
	{
		DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127]  ### chungiii OK!!!! swrst_f24m_bb is normal state  \n");

	}
#endif



	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_ANALOG_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M16P_ANALOG_SetI2C(void)
{

#if 1
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetI2C Start !! \n");

	ACE_REG_M16PA0_RdFL(abb_01);

	ACE_REG_M16PA0_Wr01(abb_01, abb_i2csel, 0);

	ACE_REG_M16PA0_WrFL(abb_01);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetI2C end !! \n");

#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M16P_ANALOG_Set_AbbMode.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M16P_ANALOG_Set_AbbMode(BOOLEAN bIsAbbMode)
{
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_M16P_ANALOG_Set_AbbMode Start !! \n");


	if(TRUE == bIsAbbMode)
	{
		ACE_REG_M16PA0_RdFL(bbdemod_control_00);
		ACE_REG_M16PA0_Wr01(bbdemod_control_00, bbdemod_control, 0);  // 0: ABB, 1 : DBB
		ACE_REG_M16PA0_WrFL(bbdemod_control_00);


		ACE_REG_M16PA0_RdFL(abb_02);
		ACE_REG_M16PA0_Wr01(abb_02, ifagc_sel, 0);  // 0: ABB, 1 : DBB
		ACE_REG_M16PA0_WrFL(abb_02);



	}
	else
	{
		ACE_REG_M16PA0_RdFL(bbdemod_control_00);
		ACE_REG_M16PA0_Wr01(bbdemod_control_00, bbdemod_control, 1);  // 0: ABB, 1 : DBB
		ACE_REG_M16PA0_WrFL(bbdemod_control_00);


		ACE_REG_M16PA0_RdFL(abb_02);
		ACE_REG_M16PA0_Wr01(abb_02, ifagc_sel, 1);  // 0: ABB, 1 : DBB
		ACE_REG_M16PA0_WrFL(abb_02);


	}

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_M16P_ANALOG_Set_AbbMode End !! \n");


	return RET_OK;
}



#if 0
#endif

#if 1

int DEMOD_M16P_Get_I2C_Handle(UINT8 portI2C, UINT16 deviceID)
{
	UINT32	handle;

	handle = portI2C << 24;
	handle = handle + deviceID;


	gM16P_LGDBB_Frontend.demodObj.i2cObj.handle = handle;

	return RET_OK;

}



int DEMOD_M16P_FW_Initialize(void)
{

	UINT8 tryCount = 0;
	LX_DEMOD_L2_Context *pFrontend;

	#if 1    // ###### chungiii should be check when bringup
             // ###### chungiii should be check FW memoty map when bringup , check FW_AXI_EN define

	const void *data = NULL;
	UINT32 size;
//	UINT32 addr;
	UINT32 *fw_addr = NULL;
	UINT32 mem_base_addr;
	pFrontend = &gM16P_LGDBB_Frontend;

	gDemodFwMemConfigured = 0;	// DemodFW memory should be configured (cold boot & instant boot)

	#if 0
	data = M16P_DEMOD_FW_0_1_0[0].firmware_table;
	size = sizeof(M16P_DEMOD_FW_0_1_0[0].firmware_table);
	#endif

	data = M16P_DEMOD_FW_0_8_0[0].firmware_table;
	size = sizeof(M16P_DEMOD_FW_0_8_0[0].firmware_table);


	if(data != NULL)
	{
		if(size > gMemCfgDEMOD_FW.memory_size)
		{
			DEMOD_PRINT_ALWAYS("f/w size(%d) over mem size(%d)\n", size, gMemCfgDEMOD_FW.memory_size);
			return RET_ERROR;
		}

		fw_addr = (UINT32 *)vmap_phys(gMemCfgDEMOD_FW.memory_base, size);
		if(!fw_addr)
		{
			DEMOD_PRINT_ALWAYS("vmap_phys fail!!!\n");
			return RET_ERROR;
		}
		memcpy(fw_addr, data, size);
		wmb(); // use wmb before mcu is awoken

		mem_base_addr = gMemCfgDEMOD_FW.memory_base;
		vunmap_phys(fw_addr);

	}
	else
	{
		return RET_ERROR;
	}

	if(RET_OK != DEMOD_L2_Set_MemAddr(pFrontend, mem_base_addr))
	{
		DEMOD_PRINT("[DEMOD M16P DBB] FAIL (%s:%d) DEMOD_L2_Set_MemAddr !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	#endif

	DEMOD_L2_Set_ChipInfo(pFrontend, 0x16b0);

	DEMOD_PRINT_ALWAYS("##########check START chungiii DEMOD_M16P_FW_Initialize\n");
	for(tryCount = 0; tryCount < 5; tryCount++)
	{

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through AXI BUS\n");
			if(DEMOD_L2_InitMem(pFrontend) != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
			else
			{
				DEMOD_PRINT_ALWAYS("##########check END chungiii DEMOD_M16P_FW_Initialize\n");
				DEMOD_PRINT_ALWAYS("[M16P LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}

		}
		else
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through I2C\n");
			if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT("[M16P LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
			else
			{
				DEMOD_PRINT("[M16P LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}

		}



	}

	if(tryCount == 5)
	{
		DEMOD_PRINT("[M16P LGDBB] (%s:%d) LGDBB Fail!! => Count(%d)\n", __F__, __L__, tryCount);
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("##########check chungiii DEMOD_M16P_FW_Initialize\n");
	//DEMOD_M16P_Get_FW_PartInfo();    // should be check when bringup

	return RET_OK;


}

int DEMOD_M16P_Opermode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_opermode;

	switch (pDemodInfo->operMode)
	{
		case	LX_DEMOD_ATSC:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_VSB; break;
		case	LX_DEMOD_QAM: 			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_QAM; break;
		case	LX_DEMOD_ISDBT: 		new_opermode = DEMOD_DD_MODE_PROP_MODULATION_ISDBT ; break;
		case	LX_DEMOD_DVBC:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBC; break;
		case	LX_DEMOD_DVBT:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBT; break;

		default:						return DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN;
	}

	return new_opermode;
}

int DEMOD_M16P_Get_BW(DEMOD_CTX_T *pDemodInfo, UINT16 *pter_bandwidth_KHz)
{

	UINT16  ter_bandwidth_KHz;
	switch (pDemodInfo->operMode)
	{
			case	LX_DEMOD_ATSC:					ter_bandwidth_KHz = 6000; break;
			case	LX_DEMOD_QAM:					ter_bandwidth_KHz = 6000; break;
			case	LX_DEMOD_ISDBT: 				ter_bandwidth_KHz = 6000 ; break;
			case	LX_DEMOD_DVBC: 					ter_bandwidth_KHz = 8000 ; break;
			case	LX_DEMOD_DVBT: 					ter_bandwidth_KHz = 8000 ; break;

			default:						return 0xffff;
	}

	*pter_bandwidth_KHz = ter_bandwidth_KHz;

	return RET_OK;
}

int DEMOD_M16P_Get_FW_PartInfo(UINT32 *pFW_Info)
{
	LX_DEMOD_L2_PART_INFO fw_part_Info;
	LX_DEMOD_L2_Context *pFrontend;
	
	UINT32	FW_Info;
	
	pFrontend = &gM16P_LGDBB_Frontend;


	if(RET_OK != DEMOD_L2_Get_PartInfo(pFrontend, &fw_part_Info))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_L2_Get_PartInfo() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	DEMOD_PRINT("fw_major  = [%d]\n", fw_part_Info.fw_major);
	DEMOD_PRINT("fw_minor  = [%d]\n", fw_part_Info.fw_minor);
	DEMOD_PRINT("fw_year   = [%d]\n", fw_part_Info.fw_year);
	DEMOD_PRINT("fw_month  = [%d]\n", fw_part_Info.fw_month);
	DEMOD_PRINT("fw_day    = [%d]\n", fw_part_Info.fw_day);
	DEMOD_PRINT("chip_type = [%d]\n", fw_part_Info.chip_type);
	DEMOD_PRINT("chip_rev  = [%d]\n", fw_part_Info.chip_rev);

	FW_Info = (fw_part_Info.fw_major << 24);
	FW_Info += (fw_part_Info.fw_minor << 16);
	FW_Info += (fw_part_Info.chip_type << 8);
	FW_Info += (fw_part_Info.chip_rev << 0);

	DEMOD_PRINT("FW_Info = [0x%x]\n", (int)FW_Info);

	*pFW_Info = FW_Info;

	return RET_OK;
}


int DEMOD_M16P_Debug_ATSC_ReadREGvalue(UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	UINT16 addr;
//	UINT8 vqData;

	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gM16P_LGDBB_Frontend;

	addr = (UINT16)address;

	pFrontend->demod->cmd->dd_get_reg.addressMsb = (UINT8)((addr >> 8) & 0xff);
	pFrontend->demod->cmd->dd_get_reg.addressLsb =  (UINT8)((addr >> 0) & 0xff);
	pFrontend->demod->cmd->dd_get_reg.length = 1;

	if(RET_OK != DEMOD_L2_SendCommand(pFrontend, DEMOD_DD_GET_REG_CMD_CODE))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_I2C_Read() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	*pData = (UINT8)(pFrontend->demod->rsp->dd_get_reg.mData[0]);


	//DEMOD_PRINT_ALWAYS("[DEMOD] address = 0x%x, value = 0x%x !!!\n",addr,vqData );

	return RET_OK;


}



int DEMOD_M16P_Debug_ATSC_WriteREGvalue(UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	UINT8 vqData;

	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gM16P_LGDBB_Frontend;

	vqData = *pData;

	pFrontend->demod->cmd->dd_set_reg.addressMsb = (UINT8)((address >> 8) & 0xff);
	pFrontend->demod->cmd->dd_set_reg.addressLsb =  (UINT8)((address >> 0) & 0xff);
	pFrontend->demod->cmd->dd_set_reg.length = 1;
	pFrontend->demod->cmd->dd_set_reg.data= (UINT32)vqData;


	if(RET_OK != DEMOD_L2_SendCommand(pFrontend, DEMOD_DD_SET_REG_CMD_CODE))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_DBB_I2C_Write() !!!\n", __F__, __L__);
		return RET_ERROR;
	}


	return RET_OK;


}




int DEMOD_M16P_Get_Dump(void)
{

	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gM16P_LGDBB_Frontend;

	printk("########chungii call M16P dump\n");
	if(RET_OK != DEMOD_L2_GetDump(pFrontend))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_L2_GetDump() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	return RET_OK;


}


#endif





