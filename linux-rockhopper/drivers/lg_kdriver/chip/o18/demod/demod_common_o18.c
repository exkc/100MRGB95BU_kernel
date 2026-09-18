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
**  Name:demod_common_o18.c
**
**  Description:    ABB/GBB common block.
**
**  Functions
**  Implemented:   int	DEMOD_O18_ResetHW
**                  int DEMOD_O18_SetI2C
**                  int DEMOD_O18_SetInclk
**                  int DEMOD_O18_AdcInit
**                  int DEMOD_O18_RepeaterEnable
**                  int DEMOD_O18_SoftwareReset
**                  int DEMOD_O18_Serial_Control
**                  int DEMOD_O18_Power_Save
**                  int DEMOD_O18_StdOperModeContrl
**                  int DEMOD_O18_NeverlockScan
**                  int DEMOD_O18_TPOutEnable
**                  int DEMOD_O18_Set_IF_Frq
**                  int DEMOD_O18_Set_AGCPolarity
**                  int DEMOD_O18_Set_SpectrumCtrl
**                  int DEMOD_O18_Get_Id
**                  int DEMOD_O18_Get_SpectrumStatus
**                  int DEMOD_O18_Get_IFAGC
**                  int DEMOD_O18_Get_OperMode
**                  int DEMOD_O18_Get_NeverLockStatus
**                  int DEMOD_O18_Get_CarrierFreqOffset
**                  int DEMOD_O18_Get_TPIFStatus
**                  int DEMOD_O18_Get_VABER
**                  int DEMOD_O18_Get_Packet_Error
**                  int DEMOD_O18_Get_BandWidthMode
**                  int DEMOD_O18_Get_QAMMode
**                  int DEMOD_O18_Get_MseInfo
**                  int DEMOD_O18_Get_Lock
**                  int DEMOD_O18_VSB_Get_SysLockTime
**                  int DEMOD_O18_VSB_Get_FecLockTime
**
**                  int DEMOD_O18_ANALOG_ResetHW
**                  int DEMOD_O18_ANALOG_SetI2C
**                  int DEMOD_O18_ANALOG_Set_AbbMode
**                  int DEMOD_O18_ANALOG_Set_WorkAround
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
#include "demod_common_o18.h"

//#include <te_mcu.h>

//#include "demod_reg_m16.h"

#if 0
#endif

UINT8 					gO18GBB_PowerOnInit = 1;
LX_DEMOD_L2_Context 	gO18_LGDBB_Frontend;
static int					gDemodFwMemConfigured = 0;

#if 1
static volatile unsigned int *gMapped_address;
#define DEMOD_APB_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
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
 * _DEMOD_O18_Get_Lock_FEC
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_FEC( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O18_Get_Lock_TR
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_TR( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O18_Get_Lock_CARR
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_CARR( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_PSYNC( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O18_Get_Lock_TPS
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_TPS( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_O18_Get_Lock_AGC
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_AGC( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int _DEMOD_O18_Get_Lock_Mode_Det( LX_DEMOD_OPER_MODE_T operMode, UINT8 *lockStatus)
{
	*lockStatus = 0;

	return RET_OK;
}

#if 0
#endif


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_ResetHW(void)
{
	UINT32	swrst_f24m;
	UINT8	reg_dmd_adc_refsel = 0x07;
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

#ifdef INCLUDE_O18_CHIP_KDRV



#if 0
	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 1);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

//	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc01);
//	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc01, swrst_apb, 0);
//	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc01);

	usleep_range(1000,10000);	/* 1ms ~ 10ms */

	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 0);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

//	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc01);
//	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc01, swrst_apb, 1);
//	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc01);

	usleep_range(3000,10000);	/* 3ms ~ 10ms */

//	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc01);
//	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc01, swrst_apb, 0);
//	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc01);

	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 1);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

#else
		DEMOD_APB_REG_WR(0xC600f004, 0x00000001);

		DEMOD_APB_REG_WR(0xC6000004, 0x200c0000);
//		DEMOD_APB_REG_WR(0xC7FC0038, 0x07300250);
//		DEMOD_APB_REG_WR(0xC7FC0038, 0x17300250);

		usleep_range(1000,5000);	/* 1ms ~ 10ms */

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 0);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);
		usleep_range(1000,5000);	/* 1ms ~ 10ms */

		CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
		CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 0);
		CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

		usleep_range(3000,8000);
		CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
		CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 1);
		CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

		usleep_range(1000,5000);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_ort, 0);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_oen, 5);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_odiv, 2);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_mc, 0x30);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_icp, 7);
//		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr17);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr17, reg_dmd_adc_refsel, reg_dmd_adc_refsel);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr17);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		usleep_range(1000,5000);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr18);
		CTOP_CTRL_O18A0_Wr03(BMC_SYN, bmc_ctr18, reg_dmd_sadc_q_pdb,0 , reg_dmd_sadc_i_pdb,0 , reg_dmd_tadc_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr18);

		usleep_range(1000,5000);

#endif

#ifdef INCLUDE_O18_CHIP_KDRV // For debugging

	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc01);
	CTOP_CTRL_O18A0_Rd01(CTRL_BMC, crg_bmc01, swrst_f24m, swrst_f24m);

	if(swrst_f24m == 1)
	{
		DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127] ### chungiii ooops!!! STILL  swrst_f24m_bb is reset state  \n");
	}
	else
	{
		DEMOD_PRINT_ALWAYS("[KDRV_DEMOD][1127]  ### chungiii OK!!!! swrst_f24m_bb is normal state  \n");
	}
#endif

	gO18GBB_PowerOnInit = 1;

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_ResetHW end !! \n");

#endif
#endif

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_OperModeReset(LX_DEMOD_OPER_MODE_T operMode)
{

//	UINT32		swrst_f24m;
	UINT8		reg_dmd_adc_refsel ;
//	UINT32 		busPendCount = 0;
//	UINT8 		tryCount;
	UINT8 		busDoneCount;
	UINT32 		busFlushDone = 0;
//	UINT32 		rData = 0;
//	UINT32 		wrData = 0;

	DEMOD_PRINT("[KDRV_DEMOD]  DEMOD_ResetHW  start !! \n");

	DEMOD_APB_REG_WR(0xC600f004, 0x00000001);
#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### before SW/HW reset  Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(5000,10000);	/* 3ms ~ 10ms */

 	}
#endif
	DEMOD_APB_REG_WR(0xC6003010, 0x20400);
	DEMOD_APB_REG_WR(0xC6005030, 0xf0000);

	usleep_range(10000,20000);	/* 1ms ~ 10ms */

	DEMOD_APB_REG_WR(0xC6000000, 0x7c000000);

	usleep_range(2000,10000);	/* 1ms ~ 10ms */

	DEMOD_APB_REG_WR(0xc7fc2130, 0x00000000);  //bus gating enable
	DEMOD_APB_REG_WR(0xc7fc2138, 0x00000001);  //flush enable

	for(busDoneCount =0;busDoneCount < 10;busDoneCount++)
	{
		DEMOD_APB_REG_RD(0xc7fc2138, busFlushDone);  //flush enable
		if((busFlushDone & 0x1)== 1)
	   	{
			CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
			CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 0);
			CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

			DEMOD_APB_REG_WR(0xc7fc2138, 0x00000001);  //flush enable

			usleep_range(3000,10000);	/* 3ms ~ 10ms */

			CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
			CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 1);
			CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

			usleep_range(2000,10000);	/* 3ms ~ 10ms */

			DEMOD_PRINT_ALWAYS("###1 (%d try) Bus flush done = %d, OK ####\n",busDoneCount, (busFlushDone & 0x1));

			break;

	   	}
		else
		{
			DEMOD_PRINT_ALWAYS("###1 (%d try) Bus flush done = %d, NOT ####\n",busDoneCount, (busFlushDone & 0x1));
			usleep_range(5000,10000);	/* 5ms ~ 10ms */
		}
	}

	DEMOD_APB_REG_WR(0xc7fc2138, 0x00000000);  //flush disable
	DEMOD_APB_REG_WR(0xc7fc2130, 0x00000011);  //bus gating release
	DEMOD_APB_REG_WR(0xC6000000, 0xfc000000);
#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### After HW reset 1 Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(5000,10000);	/* 3ms ~ 10ms */

 	}
#endif
	if((operMode == LX_DEMOD_DVBT) || (operMode == LX_DEMOD_DVBC) )
	{
		reg_dmd_adc_refsel = 0x07;
		DEMOD_APB_REG_WR(0xC6000004, 0x200c0000);

		//DEMOD_APB_REG_WR(0xC6000004, 0x21280000);

		usleep_range(10000,15000);	/* 1ms ~ 10ms */

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 0);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);
		usleep_range(1000,10000);	/* 1ms ~ 10ms */

		DEMOD_APB_REG_WR(0xC6003010, 0x20400);
		DEMOD_APB_REG_WR(0xC6005030, 0xf0000);

		usleep_range(10000,20000);	/* 1ms ~ 10ms */

		DEMOD_APB_REG_WR(0xC6000000, 0x7c000000);

		usleep_range(2000,10000);	/* 1ms ~ 10ms */

		DEMOD_APB_REG_WR(0xc7fc2130, 0x00000000);  //bus gating enable
		DEMOD_APB_REG_WR(0xc7fc2138, 0x00000001);  //flush enable

		for(busDoneCount =0;busDoneCount < 10;busDoneCount++)
		{
			DEMOD_APB_REG_RD(0xc7fc2138, busFlushDone);  //flush enable
			if((busFlushDone & 0x1)== 1)
		   	{
				CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
				CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 0);
				CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

				DEMOD_APB_REG_WR(0xc7fc2138, 0x00000001);  //flush enable

				usleep_range(3000,10000);	/* 3ms ~ 10ms */

				CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
				CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 1);
				CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

				usleep_range(2000,10000);	/* 3ms ~ 10ms */

				DEMOD_PRINT_ALWAYS("###1 (%d try) Bus flush done = %d, OK ####\n",busDoneCount, (busFlushDone & 0x1));

				break;

		   	}
			else
			{
				DEMOD_PRINT_ALWAYS("###1 (%d try) Bus flush done = %d, NOT ####\n",busDoneCount, (busFlushDone & 0x1));
				usleep_range(5000,10000);	/* 5ms ~ 10ms */
			}
		}

		DEMOD_APB_REG_WR(0xc7fc2138, 0x00000000);  //flush disable
		DEMOD_APB_REG_WR(0xc7fc2130, 0x00000011);  //bus gating release
		DEMOD_APB_REG_WR(0xC6000000, 0xfc000000);

#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### After HW reset 2 Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(5000,10000);	/* 3ms ~ 10ms */

 	}
#endif
//		_DEMOD_O18_RegisterSet();

//		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr17);
//		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr17, reg_dmd_adc_refsel, 0x7);
//		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr17);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_ort, 0);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_oen, 5);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_odiv, 2);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_mc, 0x30);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_icp, 7);
//		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr17);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr17, reg_dmd_adc_refsel, reg_dmd_adc_refsel);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr17);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		usleep_range(1000,10000);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr18);
		CTOP_CTRL_O18A0_Wr03(BMC_SYN, bmc_ctr18, reg_dmd_sadc_q_pdb,0 , reg_dmd_sadc_i_pdb,0 , reg_dmd_tadc_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr18);

		usleep_range(1000,10000);
	}
	else if (operMode == LX_DEMOD_DVBS)
	{
		reg_dmd_adc_refsel = 0x02;

		DEMOD_APB_REG_WR(0xC6000004, 0x600c0000);

//		DEMOD_APB_REG_WR(0xC7FC0038, 0x073E0231);
//		DEMOD_APB_REG_WR(0xC7FC0038, 0x173E0231);

		usleep_range(1000,10000);	/* 1ms ~ 10ms */

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 0);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		usleep_range(1000,10000);	/* 1ms ~ 10ms */

		DEMOD_APB_REG_WR(0xC6003010, 0x20400);
		DEMOD_APB_REG_WR(0xC6005030, 0xf0000);

		usleep_range(10000,20000);	/* 1ms ~ 10ms */

		DEMOD_APB_REG_WR(0xC6000000, 0x7c000000);

		usleep_range(2000,10000);	/* 1ms ~ 10ms */

		DEMOD_APB_REG_WR(0xc7fc2130, 0x00000000);  //bus gating enable
		DEMOD_APB_REG_WR(0xc7fc2138, 0x00000001);  //flush enable


		for(busDoneCount =0;busDoneCount < 10;busDoneCount++)
		{
			DEMOD_APB_REG_RD(0xc7fc2138, busFlushDone);  //flush enable
			if((busFlushDone & 0x1)== 1)
		   	{
				CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
				CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 0);
				CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);


				DEMOD_APB_REG_WR(0xc7fc2138, 0x00000001);  //flush enable

				usleep_range(3000,10000);	/* 3ms ~ 10ms */

				CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
				CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, dbb_reset, 1);
				CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

				usleep_range(2000,10000);	/* 3ms ~ 10ms */

				DEMOD_PRINT_ALWAYS("###1 (%d try) Bus flush done = %d, OK ####\n",busDoneCount, (busFlushDone & 0x1));

				break;

		   	}
			else
			{
				DEMOD_PRINT_ALWAYS("###1 (%d try) Bus flush done = %d, NOT ####\n",busDoneCount, (busFlushDone & 0x1));
				usleep_range(5000,10000);	/* 5ms ~ 10ms */
			}
		}

		DEMOD_APB_REG_WR(0xc7fc2138, 0x00000000);  //flush disable
		DEMOD_APB_REG_WR(0xc7fc2130, 0x00000011);  //bus gating release
		DEMOD_APB_REG_WR(0xC6000000, 0xfc000000);
#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### After HW reset 3 Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(5000,10000);	/* 3ms ~ 10ms */

 	}
#endif
//		_DEMOD_O18_RegisterSet();

//		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr17);
//		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr17, reg_dmd_adc_refsel, 0x2);
//		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr17);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_ort, 1);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_oen, 3);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_odiv, 2);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_mc, 0x3e);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_icp, 7);
//		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr17);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr17, reg_dmd_adc_refsel, reg_dmd_adc_refsel);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr17);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

		usleep_range(1000,10000);

		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr18);
		CTOP_CTRL_O18A0_Wr03(BMC_SYN, bmc_ctr18, reg_dmd_sadc_q_pdb,1 , reg_dmd_sadc_i_pdb,1 , reg_dmd_tadc_pdb, 0);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr18);

		usleep_range(1000,10000);

	}
#if 0
	else if (operMode == LX_DEMOD_DVBC)
	{
		DEMOD_O18_StdOperModeContrl( LX_DEMOD_DVBC, LX_DEMOD_DVBT_NO_OPERATION, LX_DEMOD_SYMR_DVBC_NO_OPERATION_MODE);
	}
#endif
	else
	{
		DEMOD_PRINT("[KDRV_DEMOD] Fail DEMOD_O18_OperModeReset !! \n");
		return RET_OK;
	}

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_O18_OperModeReset end !! \n");

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_SetI2C(void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_SetInclk.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_SetInclk(LX_DEMOD_INCLK_SEL_T *inclk)
{
#ifdef INCLUDE_O18_CHIP_KDRV
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetInclk Start !! \n");

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr16);

	switch(*inclk)
	{
		case LX_DEMOD_ARM_SETTING:
		{
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr16, reg_dmd_pll_finsel, 0);
		}
		break;

		case LX_DEMOD_EXTERN_PIN:
		{
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr16, reg_dmd_pll_finsel, 1);
		}
		break;

		default:
			DEMOD_PRINT("Invalid LX_DEMOD_INCLK_SEL_T type\n");
			return -1;
	}

	CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr16);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetInclk End !! \n");

#endif
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_AdcInit.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_AdcInit(void)
{
#ifdef INCLUDE_O18_CHIP_KDRV
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_O18_AdcInit Start !! \n");

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
	CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_pdb, 1);
	CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

	#if 0
	// ADC reference voltage selection
	// (000: 0.6Vpp, 001: 0.8Vpp, 010: 1.0Vpp, 011: 1.2Vpp, 100: 1.4Vpp, 101: 1.6Vpp, 110: 1.8Vpp, 111: 2.0Vpp)
	//	default: T2(111), S2(010)
	CTOP_CTRL_L18A0_RdFL(BMC, BMC_CTR17);
	CTOP_CTRL_L18A0_Wr01(BMC, BMC_CTR17, reg_dmd_adc_refsel, 7);
	CTOP_CTRL_L18A0_WrFL(BMC, BMC_CTR17);
	#endif

	#if 0 // need to check register name for O18
	CTOP_CTRL_O18A0_RdFL(BMC, syn_bmc39);
	CTOP_CTRL_O18A0_Wr01(BMC, syn_bmc39, reg_use_cpu_gpio_17_6, 0);
	CTOP_CTRL_O18A0_WrFL(BMC, syn_bmc39);

	CTOP_CTRL_O18A0_RdFL(BMC, syn_bmc39);
	CTOP_CTRL_O18A0_Wr01(BMC, syn_bmc39, reg_use_cpu_gpio_4_4, 0);
	CTOP_CTRL_O18A0_WrFL(BMC, syn_bmc39);

	CTOP_CTRL_O18A0_RdFL(BMC, syn_bmc39);
	CTOP_CTRL_O18A0_Wr01(BMC, syn_bmc39, reg_use_cpu_gpio_4_3, 0);
	CTOP_CTRL_O18A0_WrFL(BMC, syn_bmc39);
	#endif

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_O18_AdcInit end !! \n");

#endif
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_RepeaterEnable.
 * Enable / Disable GBB I2C repeater function
 *
 * @param bEnable [IN] 	BOOLEAN - Enable/Disable I2C repeater
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_RepeaterEnable(BOOLEAN bEnable)
{
	UINT16 	address;
	UINT8 	rdBuffer;
	UINT8 	wrBuffer;

	DEMOD_PRINT("before[DEMOD O18p]   DEMOD_O18_RepeaterEnable  ###### chungiii \n");

	//address= 0x7103;
	address= 0x7103;

	if(RET_OK != DEMOD_I2C_Read(address, 1, &rdBuffer))
	{
		DEMOD_PRINT("[O18 DBB I2C] FAIL (%s:%d) DEMOD_I2C_Read  !!!\n", __F__, __L__);
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
 * DEMOD_O18_SoftwareReset.
 * Reset DVB module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_SoftwareReset(void)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;

	if (RET_OK != DEMOD_L1_SET_DD_Restart(pFrontend->demod))
	{
		DEMOD_PRINT("[DEMOD O18] FAIL (%s:%d) DEMOD_L1_SET_DD_Restart() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
	DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_L1_SET_DD_Restart OK!!!! \n", __F__, __L__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Serial_Control
 * Control TS output mode(serial/Parallel)
 *
 * @param bEnable 	[IN] Serial(TRUE) / Parallel(FALSE)
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Serial_Control(BOOLEAN bEnable)
{
	return	RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Power_Save
 * Enable/Disable power save mode
 *
 * @param bEnable 	[IN] power save mode(TRUE) / normal mode(FALSE)
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_Power_Save(BOOLEAN bEnable)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;

	if(bEnable == TRUE)
	{
		if (DEMOD_L2_Standby(pFrontend)!= NO_DEMOD_ERROR )
		{
			DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_L2_Standby  Fail!! \n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
//		DEMOD_APB_REG_WR(0xC600f004, 0x00000001);
	}
	else
	{
//		DEMOD_APB_REG_WR(0xC600f004, 0x00000000);
		if (DEMOD_L2_WakeUp(pFrontend)!= NO_DEMOD_ERROR )
		{
			DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_L2_WakeUp  Fail!! \n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_StdOperModeContrl
 * Set standard operation mode, Bandwidth and symbol rate
 *
 * @param *InitParam [IN] LX_DEMOD_INIT_PARAM_T - operation RF Mode, bandWidth, Symbol rate
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_StdOperModeContrl( LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr)
{
	#if 0
	UINT32 dmd_inck_sel_dmdpll;
	UINT32 dmd_inck_divsel_dmdpll;
	UINT32 dmd_bypass_dmdpll;
	#endif

//	UINT8					reg_dmd_pll_ort;
//	UINT8					reg_dmd_pll_d_oen;
//	UINT8					reg_dmd_pll_d_odiv;
//	UINT8					reg_dmd_pll_mc;

//	UINT8					reg_dmd_sadc_q_pdb, reg_dmd_sadc_i_pdb;
//	UINT8					reg_dmd_tadc_pdb;
//	UINT8					reg_dmd_adc_refsel;

//	UINT8 					new_standard = 0;
	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend		= &gO18_LGDBB_Frontend;

	DEMOD_PRINT(" == @ %s  ==(oper = 0x%x)\n",__F__,operMode);

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

		gMemCfgDEMOD.memory_base 	= demod_mem;

		if(RET_OK != DEMOD_ISDBT_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_ISDBT_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}


	}
#else
	if(operMode == LX_DEMOD_ISDBT)
	{
	#if 0
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
#else
		if( RET_OK != DEMOD_ISDBT_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_ISDBT_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}
#endif

	}

	if(operMode == LX_DEMOD_DVBT ||operMode == LX_DEMOD_DVBT2)
	{
		if( RET_OK != DEMOD_DVBT2_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_DVBT2_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}
	}

	if(operMode == LX_DEMOD_DVBS || operMode == LX_DEMOD_DVBS2)
	{
		if( RET_OK != DEMOD_DVBS2_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_DVBS2_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}
	}

	if(operMode == LX_DEMOD_DTMB)
	{
		if( RET_OK != DEMOD_DTMB_Set_MemSconfig())
		{
		  DEMOD_PRINT("[DEMOD] FAIL (%s:%d) FAIL, DEMOD_DTMB_Set_MemSconfig() !!!\n", __F__, __L__);
		  DEMOD_RETURN_FAIL(__F__);
		}
	}

#endif

	usleep_range(20000,30000);	/* 1ms ~ 10ms */
#if 0
	switch(operMode)
	{
		case LX_DEMOD_ATSC:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_VSB;
			 //24MHz 384MHz
			 reg_dmd_pll_mc 	= 0x30;
			 reg_dmd_pll_d_odiv	= 0x2;
			 reg_dmd_pll_ort	= 0x0;
			 reg_dmd_pll_d_oen	= 0x5;

			 reg_dmd_adc_refsel = 0x7;
			 reg_dmd_sadc_q_pdb = 0;
			 reg_dmd_sadc_i_pdb = 0;
			 reg_dmd_tadc_pdb = 1;
			break;

		case LX_DEMOD_QAM:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_QAM;
			 //24MHz 384MHz
			 reg_dmd_pll_mc 	= 0x30;
			 reg_dmd_pll_d_odiv	= 0x2;
			 reg_dmd_pll_ort	= 0x0;
			 reg_dmd_pll_d_oen	= 0x5;

			 reg_dmd_adc_refsel = 0x7;
			 reg_dmd_sadc_q_pdb = 0;
			 reg_dmd_sadc_i_pdb = 0;
			 reg_dmd_tadc_pdb = 1;
			break;

		case LX_DEMOD_ISDBT:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_ISDBT;
			 //24MHz 384MHz
			 reg_dmd_pll_mc 	= 0x30;
			 reg_dmd_pll_d_odiv	= 0x2;
			 reg_dmd_pll_ort	= 0x0;
			 reg_dmd_pll_d_oen	= 0x5;

			 reg_dmd_adc_refsel = 0x7;
			 reg_dmd_sadc_q_pdb = 0;
			 reg_dmd_sadc_i_pdb = 0;
			 reg_dmd_tadc_pdb = 1;
			break;

		case LX_DEMOD_DVBT:
		case LX_DEMOD_DVBT2:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_DVBT;
			 //24MHz 384MHz
			 reg_dmd_pll_mc 	= 0x30;
			 reg_dmd_pll_d_odiv	= 0x2;
			 reg_dmd_pll_ort	= 0x0;
			 reg_dmd_pll_d_oen	= 0x5;

			 reg_dmd_adc_refsel = 0x7;
			 reg_dmd_sadc_q_pdb = 0;
			 reg_dmd_sadc_i_pdb = 0;
			 reg_dmd_tadc_pdb = 1;
			break;

		case LX_DEMOD_DVBC:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_DVBC;
			 //24MHz 384MHz
			 reg_dmd_pll_mc 	= 0x30;
			 reg_dmd_pll_d_odiv	= 0x2;
			 reg_dmd_pll_ort	= 0x0;
			 reg_dmd_pll_d_oen	= 0x5;

			 reg_dmd_adc_refsel = 0x7;
			 reg_dmd_sadc_q_pdb = 0;
			 reg_dmd_sadc_i_pdb = 0;
			 reg_dmd_tadc_pdb = 1;
			break;

		case LX_DEMOD_DTMB:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_DTMB;
			 //24MHz 384MHz
			 reg_dmd_pll_mc 	= 0x30;
			 reg_dmd_pll_d_odiv	= 0x2;
			 reg_dmd_pll_ort	= 0x0;
			 reg_dmd_pll_d_oen	= 0x5;

			 reg_dmd_adc_refsel = 0x7;
			 reg_dmd_sadc_q_pdb = 0;
			 reg_dmd_sadc_i_pdb = 0;
			 reg_dmd_tadc_pdb = 1;
			break;

		case LX_DEMOD_DVBS:
		case LX_DEMOD_DVBS2:
			 new_standard = DEMOD_DD_MODE_PROP_MODULATION_DVBS;
			 //96MHz 384MHz
			 reg_dmd_pll_mc 	= 0x3e;
			 reg_dmd_pll_d_odiv = 0x2;
			 reg_dmd_pll_ort	= 0x1;
			 reg_dmd_pll_d_oen	= 0x3;

			 reg_dmd_adc_refsel = 0x2;
			 reg_dmd_sadc_q_pdb = 1;
			 reg_dmd_sadc_i_pdb = 1;
			 reg_dmd_tadc_pdb = 0;

			break;

		default :
			DEMOD_PRINT_ALWAYS("[DEMOD O18](%s,%d) Invaild Opermode parameter !!!\n",__F__, __L__);
			return RET_ERROR;
	}

	// ADC reference voltage selection
	// (000: 0.6Vpp, 001: 0.8Vpp, 010: 1.0Vpp, 011: 1.2Vpp, 100: 1.4Vpp, 101: 1.6Vpp, 110: 1.8Vpp, 111: 2.0Vpp)
	//  default: T2(111), S2(010)

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr17);
	CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr17, reg_dmd_adc_refsel, reg_dmd_adc_refsel);
	CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr17);

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr15);
	CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_mc, reg_dmd_pll_mc);
	CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_odiv, reg_dmd_pll_d_odiv);
	CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_ort, reg_dmd_pll_ort);
	CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr15, reg_dmd_pll_d_oen, reg_dmd_pll_d_oen);
	CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr15);

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr18);
	CTOP_CTRL_O18A0_Wr03(BMC_SYN, bmc_ctr18, reg_dmd_sadc_q_pdb, reg_dmd_sadc_q_pdb, reg_dmd_sadc_i_pdb, reg_dmd_sadc_i_pdb, reg_dmd_tadc_pdb, reg_dmd_tadc_pdb);
	CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr18);

	if(RET_OK != DEMOD_L2_Switch_to_standard(pFrontend,new_standard))
	{
		DEMOD_PRINT("[O18 LGDBB] FAIL (%s:%d) DEMOD_L2_Switch_to_standard !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	usleep_range(20000,30000);	/* 1ms ~ 10ms */


	DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) ChangeTransMedia = %s !!!\n", __F__, __L__,(new_standard == DEMOD_DD_MODE_PROP_MODULATION_VSB) ? "VSB" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_QAM) ? "QAM" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_ISDBT) ? "ISDBT" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBT) ? "DVBT" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBT2) ? "DVBT2" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBT2) ? "ISDBT2" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS) ? "DVBS" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2) ? "DVBS2" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DTMB) ? "DTMB" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBC) ? "DVBC" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_DVBC2) ? "DVBC2" :
																			(new_standard == DEMOD_DD_MODE_PROP_MODULATION_ATSC3) ? "ATSC3.0" : "NTSC");


#endif

	return RET_OK;

}


/**
 * DEMOD_O18_NeverlockScan
 * Get the neverlock flag indicator.
 *
 * @param	*pDemodInfo			[IN] DEMOD_CTX_T.
 * @param	ResetOn				[IN] 	LX_DEMOD_FLAG_T  - force to initialize the postjob.
 * @param	*pScanProcessing		[OUT] LX_DEMOD_FLAG_T- the flag that scan is done or not done.
 * @param	*pScanLock			[OUT] LX_DEMOD_LOCK_STATE_T - scan lock result.
 * @return if Succeeded - RET_OK else-TU_ERROR
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/
int DEMOD_O18_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock)
{
	static LX_DEMOD_LOCK_STATE_T	_demodScanLock	= LX_DEMOD_UNKOWN_STATE;
	static unsigned int				_neverLockResetTime = 0;
	static unsigned int 				_maxTimeOut = 0;
	unsigned int 					elapsedTime = 0;
	LX_DEMOD_LOCK_STATE_T 		neverLockStatus;
	LX_DEMOD_OPER_MODE_T 		scanMode;

	scanMode = pDemodInfo->operMode;

	if(LX_DEMOD_FLAG_ON == ResetOn)
	{
		*pScanProcessing 	= LX_DEMOD_FLAG_ING;
		*pScanLock			= LX_DEMOD_UNLOCKED;

		switch(scanMode)
		{
			case LX_DEMOD_DVBT :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1000;
//				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1500;
//				_maxTimeOut = LX_DEMOD_LOCK_DEALY_700;
//				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
				break;
			case LX_DEMOD_DVBT2 :
				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1000;
//				_maxTimeOut = LX_DEMOD_LOCK_DEALY_1500;
//				_maxTimeOut = LX_DEMOD_LOCK_DEALY_700;
//				_maxTimeOut = LX_DEMOD_LOCK_DEALY_600;
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

	if (RET_OK != DEMOD_O18_Get_NeverLockStatus(scanMode, &neverLockStatus))
	{
		DEMOD_PRINT("^r^[M16_DVB DTV] FAIL (%s:%d) KADP_DEMOD_VQI_ChanScan_GetStatus() !!!\n", __F__, __L__);
		*pScanLock	= LX_DEMOD_UNLOCKED;
		return RET_ERROR;
	}

	switch (neverLockStatus)
	{

		case LX_DEMOD_DETECTION_PROCESSING:
			{
				elapsedTime 			= jiffies_to_msecs(jiffies) - _neverLockResetTime;
				_demodScanLock			= LX_DEMOD_UNKOWN_STATE;
				DEMOD_PRINT("(%s %d)elapsedTime = %d,_maxTimeOut = %d \n",__F__, __L__, elapsedTime,_maxTimeOut  );

				if(elapsedTime > _maxTimeOut)
				{
					*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
					_demodScanLock		= LX_DEMOD_UNLOCKED;
					DEMOD_PRINT( "[DEMOD O18] NEVERSCAN : LX_DEMOD_NEVERLOCK DETECTION is on processing \n");
				}
			}
			break;

		case LX_DEMOD_DETECTION_FAIL:
			{
				*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
				_demodScanLock		= LX_DEMOD_UNLOCKED;
				DEMOD_PRINT( "[DEMOD O18] NEVERSCAN :  LX_DEMOD_NEVERLOCK DETECTION FAIL  \n");
			}
			break;

		case LX_DEMOD_DETECTED:
			{
				*pScanProcessing	= LX_DEMOD_FLAG_FINISH;
				_demodScanLock		= LX_DEMOD_TR_LOCK;
				DEMOD_PRINT( "[DEMOD O18] NEVERSCAN :  LX_DEMOD_NEVERLOCK DETECTED	!! \n");

			}
			break;
		default:
			_demodScanLock	= LX_DEMOD_UNLOCKED;
			DEMOD_PRINT( "[DEMOD O18] NEVERSCAN :  LX_DEMOD_UNLOCKED(%d)	!! \n",neverLockStatus);
			break;
	}

	*pScanLock	= _demodScanLock;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_TPOutEnable
 * Enable/Diable the output of TP
 *
 * @param bEnable	  [IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_TPOutEnable(BOOLEAN bEnable)
{

	LX_DEMOD_L2_Context 	*pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;

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
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_L2_Set_Property  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Set_IF_Frq
 * Set IF frequency registers on DVB-C mode.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Set_IF_Frq(UINT32 ifFrq)
{
#if 1
	LX_DEMOD_L2_Context 	*pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;


	if(ifFrq == LX_DEMOD_IF_FREQ_05_000_KHZ)
	{
		pFrontend->demod->prop->dd_if_freq.if_freq = DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_O18_Set_IF_Frq  5MHz \n", __F__, __L__);
	}
	else if(ifFrq == LX_DEMOD_IF_FREQ_06_000_KHZ)
	{
		pFrontend->demod->prop->dd_if_freq.if_freq = DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_O18_Set_IF_Frq  6MHz \n", __F__, __L__);
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

#endif

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Set_AGCPolarity
 * Set IF frequency registers on DVB.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Set_AGCPolarity(LX_DEMOD_AGC_POLAR_T agcPola)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;

	if(agcPola == LX_DEMOD_AGC_ACTIVE_HIGH)
	{
		pFrontend->demod->prop->dd_agc.agc_pol  = DEMOD_DD_AGC_PROP_POLARITY_NORMAL;;
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) LX_DEMOD_AGC_ACTIVE_HIGH \n", __F__, __L__);
	}
	else
	{
		pFrontend->demod->prop->dd_agc.agc_pol  = DEMOD_DD_AGC_PROP_POLARITY_INVERSION;;
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) DEMOD_DD_AGC_PROP_POLARITY_INVERSION \n", __F__, __L__);
	}

	if (DEMOD_L2_Set_Property(pFrontend, DEMOD_DD_AGC_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_DD_AGC_PROP_CODE  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Set_SpectrumCtrl.
 * Enable/Disable automatic spectrum mode detection.
 *
 * @param  bAutoEnable [IN] BOOLEAN - enable/disable.
 * @param  bSpecInvEnable [IN] BOOLEAN - enable/disable.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Set_SpectrumCtrl(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable)
{
	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_Id.
 * Get GBB demod ID.
 *
 * @param *cell_id [OUT] UINT16 - GBB demod ID
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_Id(UINT8 *pCellIDLength, UINT16 *pId)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;;
	}

	*pId = signalStatus.cell_id;
	*pCellIDLength = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_SpectrumInvStatus
 * Get spectrum mode state on DVB.
 *
 * @param *pSpectrumAuto 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_AUTO, LX_DEMOD_MANUAL.
 * @param *pSpectrumInv 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_NORMAL, LX_DEMOD_INVERSION.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_SpectrumStatus(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;
	LX_DEMOD_LOCK_STATE_T 		SpectrumAuto = LX_DEMOD_AUTO;
	LX_DEMOD_LOCK_STATE_T 		SpectrumInv = LX_DEMOD_NORMAL;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;
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
		return RET_ERROR;
	}

	SpectrumAuto 		= pFrontend->demod->prop->dd_mode.specinvauto;
	*pSpectrumAuto 		= SpectrumAuto;
	*pSpectrumInv 		= SpectrumInv;

	DEMOD_PRINT("####  [%s]  check spectrum  auto ? manual [%d]\n",  __F__, SpectrumAuto);
	DEMOD_PRINT("####  [%s]  check spectrum  inverted ?    [%d]\n",  __F__, SpectrumInv);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_IFAGCValue
 * Get IF AGC value on DVB.
 *
 * @param *pIfagcValue 	[OUT] UINT16
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_IFAGC(UINT16 *pIfAgc)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;
	}

	*pIfAgc = signalStatus.if_agc;
	DEMOD_PRINT("(%s) IF AGC = 0x%x \n", __F__, *pIfAgc);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_OperMode.
 * Get GBB operation mode.
 *
 * @param *pOperMode [OUT] LX_DEMOD_VQI_RF_MODE_T - GBB RF demodulation mode
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_OperMode(LX_DEMOD_OPER_MODE_T *pOperMode)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_OPER_MODE_T 		reply_opmode;
	UINT8 						retCode = 0;

	pFrontend = &gO18_LGDBB_Frontend;

	//printk("#################################   before  check DEMOD_O18_Get_OperMode reply opmode [%d]\n", reply_opmode);

//	retCode = DEMOD_L1_GET_DD_Status(pFrontend->demod);
	retCode = DEMOD_L2_Get_OperMode(pFrontend, &reply_opmode);

	if(NO_DEMOD_ERROR != retCode)
	{
		*pOperMode = LX_DEMOD_UNKOWN_OPMODE;

		return RET_ERROR;
	}
/*
	switch (pFrontend->demod->rsp->dd_status.reply_operMod)
	{
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:		reply_opmode = LX_DEMOD_ATSC;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM: 		reply_opmode = LX_DEMOD_QAM;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT: 		reply_opmode = LX_DEMOD_ISDBT;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:		reply_opmode = LX_DEMOD_DVBT;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2:		reply_opmode = LX_DEMOD_DVBT2;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:		reply_opmode = LX_DEMOD_DVBC;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC2:		reply_opmode = LX_DEMOD_DVBC2;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS:		reply_opmode = LX_DEMOD_DVBS;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:		reply_opmode = LX_DEMOD_DVBS2;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DTMB:		reply_opmode = LX_DEMOD_DTMB;	break;

		default :
			DEMOD_PRINT_ALWAYS("[DEMOD O18](%s,%d) LX_DEMOD_UNKNOWN_OPMODE!!!value : %02x\n",__F__, __L__, pFrontend->demod->rsp->dd_status.reply_operMod);
			return RET_ERROR;

	}
*/
	DEMOD_PRINT("[DEMOD O18](%s,%d) OPmode !!!value : %02x\n",__F__, __L__, reply_opmode);

	*pOperMode = reply_opmode;
	//printk("######check DEMOD_O18_Get_OperMode reply opmode [%d]\n", reply_opmode);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_NeverLockStatus
 * Get neverlock state on DVB.
 *
 * @param scanMode 	[OUT] LX_DEMOD_OPER_MODE_T
 * @param *pNeverLockStatus 	[OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMODLOCKED, LX_DEMOD_UNLOCKED.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_NeverLockStatus(LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	UINT8 					neverlock;

	pFrontend 			= &gO18_LGDBB_Frontend;
	*pNeverLockStatus 	= LX_DEMOD_UNKOWN_STATE;

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
 * DEMOD_O18_Get_CarrierFreqOffset
 * Get carrier offset frequency .
 *
 * @param *pFreqOff 	[OUT] SINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_CarrierFreqOffset(SINT32 *pFreqOff)
{
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	LX_DEMOD_L2_Context 		*pFrontend;
	SINT32						freqOffset;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

//	DEMOD_PRINT("[O18 LGDBB] (signalStatus.offsetFrq_Hz: %d) \n", signalStatus.offsetFrq_Hz);

	freqOffset = signalStatus.offsetFrq_Hz/1000;

//	DEMOD_PRINT("[O18 LGDBB] (freqOffset: %d) \n", freqOffset);

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

	DEMOD_PRINT("[DEMOD O18] Carrier Offset freq = %d [KHz] !!!\n",*pFreqOff);

	return RET_OK;

#endif
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_TPIFStatus
 * Get the status of TP IF function (active or inactive)
 *
 * @param pbEnable	  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_TPIFStatus(BOOLEAN *pbEnable)
{
	*pbEnable = TRUE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_VABER
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_VABER(UINT32 *pVber)
{
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	LX_DEMOD_L2_Context 		*pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pVber = signalStatus.ber ;

	DEMOD_PRINT("[O18 LGDBB] (BER: %d) \n", *pVber);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_Packet_Error
 * Get packet error on DVB
 *
 * @param *pSnr 	[OUT] UINT8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_Packet_Error(UINT32 *pError)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gO18_LGDBB_Frontend;

	//printk("#################################   before  check DEMOD_O18_Get_Packet_Error\n");

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pError = signalStatus.packetError;

	DEMOD_PRINT(" [O18 LGDBB] DEMOD_O18_Get_Packet_Error *pError = %d  \n",*pError);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_BandWidthMode
 * Get the information of bandwidth .
 *
 * @param *ChannelBW 	[OUT] LX_DEMOD_BWMODE_T - 6, 7 and 8 MHZ.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_BandWidthMode( LX_DEMOD_BWMODE_T *ChannelBW )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus	Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_O18_Get_QAMMode
 * Get the information of QAM mode .
 *
 * @param *pQamMode [OUT] LX_DEMOD_RF_MODE_T - 16QAM, 32QAM, 64QAM, 128QAM, 256QAM, QPSK.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_QAMMode( LX_DEMOD_RF_MODE_T *pQamMode )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;
	LX_DEMOD_OPER_MODE_T 		mode;

	pFrontend = &gO18_LGDBB_Frontend;
/*
	if(RET_OK != DEMOD_O18_Get_OperMode(&mode))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_O18_Get_OperMode() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus	Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	//printk("DEMOD_L2_SignalStatus============ signalStatus.constellation[%d]  \n ", signalStatus.constellation);

	switch (pFrontend->demod->rsp->dd_status.reply_operMod)
	{
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:		mode = LX_DEMOD_ATSC;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM: 		mode = LX_DEMOD_QAM;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT: 		mode = LX_DEMOD_ISDBT;	break;
		case   	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:		mode = LX_DEMOD_DVBT;	break;
		case   	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2:		mode = LX_DEMOD_DVBT2;	break;
		case   	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:		mode = LX_DEMOD_DVBC;	break;
		case    	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC2:		mode = LX_DEMOD_DVBC2;	break;
		case    	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS:		mode = LX_DEMOD_DVBS;	break;
		case    	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:		mode = LX_DEMOD_DVBS2;	break;
		case    	DEMOD_DD_STATUS_RESPONSE_MODULATION_DTMB:		mode = LX_DEMOD_DTMB;	break;

		default :
			DEMOD_PRINT_ALWAYS("[DEMOD O18](%s,%d) LX_DEMOD_UNKOWN_OPMODE!!!\n",__F__, __L__);
			return RET_ERROR;
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

		case LX_DEMOD_DVBT2:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32:
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

		case LX_DEMOD_DVBC2:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
						*pQamMode = LX_DEMOD_16QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
						 *pQamMode = LX_DEMOD_64QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256 :
						 *pQamMode = LX_DEMOD_256QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024 :
						*pQamMode = LX_DEMOD_1024QAM;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096 :
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

		case LX_DEMOD_DVBS:
			{
				*pQamMode = LX_DEMOD_QPSK;
			}
			break;

		case LX_DEMOD_DVBS2:
			{
				switch(signalStatus.constellation)
				{
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
						*pQamMode = LX_DEMOD_QPSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8:
						*pQamMode = LX_DEMOD_8PSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16 :
						*pQamMode = LX_DEMOD_16APSK;
						break;
					case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32 :
						*pQamMode = LX_DEMOD_32APSK;
						break;
					default :
						*pQamMode = LX_DEMOD_UNKOWN_MODE;
						break;
				}
			}
			break;

			case LX_DEMOD_DTMB:
				{
					switch(signalStatus.constellation)
					{
						case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4:
							*pQamMode = LX_DEMOD_4QAM;
							break;
						case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16:
							*pQamMode = LX_DEMOD_16QAM;
							break;
						case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32:
							*pQamMode = LX_DEMOD_32QAM;
							break;
						case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64:
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
 * DEMOD_O18_Get_MseInfo
 * Get signal MSE info.
 *
 * @param *pSigMse [OUT] LX_DEMOD_MSE_T.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_MseInfo( LX_DEMOD_MSE_T *pSigMse)
{

	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);

	}

	pSigMse->bMse 		= 0;
	pSigMse->mse 		= signalStatus.mse_info;
	pSigMse->constPwr 	= signalStatus.constPwr;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_Lock
 * Check the DVB lock state
 *
 * @param eStatus 	[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_Lock(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState)
{

	UINT8 					reply_operMod = 0;
	UINT8					demodLock	= 0;
	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend		= &gO18_LGDBB_Frontend;

	if (DEMOD_L2_Get_LockStatus(pFrontend, &reply_operMod, &demodLock ))
	{
		*lockState = LX_DEMOD_UNLOCKED;
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_Get_LockStatus() \n", __F__);
		return RET_ERROR;
	}

	switch(reply_operMod)
	{
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:
			DEMOD_PRINT("checking [%s] lock...\n", "VSB");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM:
			DEMOD_PRINT("checking [%s] lock...\n", "QAM");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT:
			DEMOD_PRINT("checking [%s] lock...\n", "ISDBT");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:
			DEMOD_PRINT("checking [%s] lock...\n", "DVBC");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC2:
			DEMOD_PRINT("checking [%s] lock...\n", "DVBC2");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:
			DEMOD_PRINT("checking [%s] lock...\n", "DVBT");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2:
			DEMOD_PRINT("checking [%s] lock...\n", "DVBT2");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS:
			DEMOD_PRINT("checking [%s] lock...\n", "DVBS");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:
			DEMOD_PRINT("checking [%s] lock...\n", "DVBS2");
			break;
		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DTMB:
			DEMOD_PRINT("checking [%s] lock...\n", "DTMB");
			break;
		default:
		break;
	}

	if ( demodLock == 1)
	{
//		DEMOD_PRINT("[O18 LGDBB] (%s) demod locked !!!\n",  __F__);
 		*lockState = LX_DEMOD_LOCKED;
	}
	else
	{
//		DEMOD_PRINT("[O18 LGDBB] (%s) demod unlocked !!!\n",  __F__);
		*lockState = LX_DEMOD_UNLOCKED;
	}

	return RET_OK;
}


int DEMOD_O18_VSB_Get_SysLockTime(UINT16 *pSyslocktime)
{
	return RET_OK;
}

int DEMOD_O18_VSB_Get_FecLockTime(UINT16 *pFeclocktime)
{
	return RET_OK;
}

/**
 * DEMOD_O18_FecReset.
 * Reset Fec reset by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_FecReset(BOOLEAN bReset)
{
	return RET_OK;
}
#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_ANALOG_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/


int DEMOD_O18_ANALOG_ResetHW(void)
{
	UINT32 swrst_f24m;
	DEMOD_PRINT("[KDRV_DEMOD] ADEMOD_ResetHW start !! \n");

#ifdef INCLUDE_O18_CHIP_KDRV

	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc20);
	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, abb_reset, 1);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);


	usleep_range(1000,10000);	/* 1ms ~ 10ms */


	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, abb_reset, 0);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);

	usleep_range(3000,10000);	/* 3ms ~ 10ms */

	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc20, abb_reset, 1);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc20);
#endif


#ifdef INCLUDE_O18_CHIP_KDRV  // For debugging
	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc01);
	CTOP_CTRL_O18A0_Rd01(CTRL_BMC, crg_bmc01, swrst_f24m, swrst_f24m);

	if(swrst_f24m == 1)
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
 * DEMOD_O18_ANALOG_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_ANALOG_SetI2C(void)
{
#ifdef INCLUDE_O18_CHIP_KDRV

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetI2C Start !! \n");

	CTOP_CTRL_O18A0_RdFL(CTRL_BMC, crg_bmc19);
	CTOP_CTRL_O18A0_Wr01(CTRL_BMC, crg_bmc19, sel_abb_i2c_sel, 0);
	CTOP_CTRL_O18A0_WrFL(CTRL_BMC, crg_bmc19);

	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_SetI2C end !! \n");

#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_ANALOG_Set_AbbMode.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_ANALOG_Set_AbbMode(BOOLEAN bIsAbbMode)
{
	DEMOD_PRINT("[KDRV_DEMOD] DEMOD_O18_ANALOG_Set_AbbMode -> nothing to do !! \n");

	return RET_OK;
}

#if 0
#endif

#if 1
int DEMOD_O18_Get_I2C_Handle(UINT8 portI2C, UINT16 deviceID)
{
	UINT32	handle;

	handle = portI2C << 24;
	handle = handle + deviceID;

	gO18_LGDBB_Frontend.demodObj.i2cObj.handle = handle;

	return RET_OK;
}


/*
static int RecoveryPreCallback(void *arg)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = &g_demod_ctx_info[0];
	pDemodInfo->bSetParams = 0;

	return 0;
}

static int RecoveryPostCallback(void *arg)
{

	LX_DEMOD_L2_Context *pFrontend;
//	DEMOD_CTX_T *pDemodInfo;

	pFrontend = &gO18_LGDBB_Frontend;
//	pDemodInfo = &g_demod_ctx_info[0];

	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!!\n", __F__);
	}

	return 0;
}
*/

int DEMOD_O18_FW_Initialize(void)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	volatile UINT32 			*pRdata = NULL;
	UINT32 sys_val;//, w_val;
	UINT8  					tryCount = 0;
	UINT8  					ret = 0;
	const void 				*data = NULL;
	UINT32 					size;
//	UINT32 addr;
	UINT32			 		*fw_addr = NULL;
	UINT32			 		mem_base_addr;
//	UINT32 busPendCount = 0;

	pFrontend 					= &gO18_LGDBB_Frontend;
	gDemodFwMemConfigured 	= 0;	// DemodFW memory should be configured (cold boot & instant boot)

	DEMOD_PRINT_ALWAYS("##### DEMOD_O18_FW_Initialize() start #####\n");

	DEMOD_APB_REG_WR(0xC600f004, 0x00000001);

#if 0
	data = O18_DEMOD_FW_0_1_0[0].firmware_table;
	size = sizeof(O18_DEMOD_FW_0_1_0[0].firmware_table);
#endif

	if (lx_chip_rev( ) >= LX_CHIP_REV(O18,B0))
	{
		data 	= O18_DEMOD_FW_b_0_1[0].firmware_table;
		size 		= sizeof(O18_DEMOD_FW_b_0_1[0].firmware_table);
		DEMOD_PRINT_ALWAYS("##### O18 B0 FW uploaded in DEMOD_O18_FW_Initialize()#####\n");
	}
	else
	{
		data 	= O18_DEMOD_FW_0_0_1[0].firmware_table;
		size 		= sizeof(O18_DEMOD_FW_0_0_1[0].firmware_table);
		DEMOD_PRINT_ALWAYS("##### O18 A0 FW uploaded in DEMOD_O18_FW_Initialize()#####\n");
	}


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
		DEMOD_PRINT("[DEMOD O18 DBB] FAIL (%s:%d) DEMOD_L2_Set_MemAddr !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	DEMOD_PRINT_ALWAYS("[DEMOD O18 DBB] mem_base_addr = 0x%x !!!\n", mem_base_addr);

		// need to be check !!!!!
	DEMOD_L2_Set_ChipInfo(pFrontend, 0x18a0);
	DEMOD_PRINT_ALWAYS("##########check START chungiii DEMOD_O18_FW_Initialize\n");

#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(3000,10000);	/* 3ms ~ 10ms */

 	}
#endif

	for(tryCount = 0; tryCount < 5; tryCount++)
	{

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through AXI BUS\n");

		#if 1
			ret = DEMOD_L2_InitMem(pFrontend);

			if(ret == NO_DEMOD_ERROR)
			{
				DEMOD_PRINT_ALWAYS("##########check END chungiii DEMOD_O18_FW_Initialize\n");
				DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}
			else
			{
				printk(" DEMOD_L2_InitMem  ERROR~!!![0x%x]\n", ret);
				DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
		#endif

		}
		else
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through I2C\n");
			if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
			else
			{
				DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}
		}
	}

	if(tryCount == 5)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) LGDBB Fail!! => Count(%d)\n", __F__, __L__, tryCount);
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("##########check chungiii DEMOD_O18_FW_Initialize\n");
	//DEMOD_O18_Get_FW_PartInfo();    // should be check when bringup
	//DEMOD_PRINT_ALWAYS("##########check chungiii skip~!!! DEMOD_O18_FW_Initialize\n");
	// need to check O18 FW ver address ~!!!!!
	do
	{
		pRdata = (volatile UINT32 *)ioremap(0xC600F000, sizeof(UINT32));

		if (pRdata==NULL)
		{
			break;
		}

		sys_val = (*pRdata);
		printk("##########check chungiii reading O18 FW ver through APB[0x%x]\n", sys_val);
	} while(0);
	iounmap((void *)pRdata);
	////////////////////check APB buffer
	#if 0
	printk("#######chungiii check ############################## \n");
	w_val	= 1;
	//DEMOD_APB_Write(0x44, &w_val);
	printk("#######chungiii check ############################## \n");

	DEMOD_L2_SET_REG(pFrontend,  0x0, 4, 0x181234);
	printk("#######chungiii check  MCU buffer \n");
	DEMOD_APB_Read(0x50, &sys_val);
	DEMOD_APB_Read(0x54, &sys_val);
	DEMOD_APB_Read(0x40, &sys_val);
	//DEMOD_APB_Read(0x44, &sys_val);

	#endif

	#if 0
	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!!\n", __F__);
	}
	#endif

	#if 0
	TE_MCU_RegisterRecoveryCallback(TE_MCU_FUNC_TYPE_DEMOD,
			RecoveryPreCallback, RecoveryPostCallback, NULL);
	#endif

	return RET_OK;
}

int DEMOD_O18_SAT_FW_Initialize(void)
{
	LX_DEMOD_L2_Context *pFrontend;
	volatile UINT32 *pRdata = NULL;
	UINT32 sys_val; //, w_val;

	UINT8  tryCount = 0;
	UINT8  ret = 0;

	const void *data = NULL;
	UINT32 size;
//	UINT32 addr;
	UINT32 *fw_addr = NULL;
	UINT32 mem_base_addr;
//	UINT32 busPendCount = 0;

	pFrontend = &gO18_LGDBB_Frontend;

	gDemodFwMemConfigured = 0;	// DemodFW memory should be configured (cold boot & instant boot)

	DEMOD_PRINT_ALWAYS("##### DEMOD_O18_SAT_FW_Initialize() start #####\n");

	DEMOD_APB_REG_WR(0xC600f004, 0x00000001);

#if 0
	data = O18_DEMOD_FW_0_1_0[0].firmware_table;
	size = sizeof(O18_DEMOD_FW_0_1_0[0].firmware_table);
#endif

	if (lx_chip_rev( ) >= LX_CHIP_REV(O18,B0))
	{
		data 	= O18_SAT_DEMOD_FW_b_0_1[0].firmware_table;
		size 		= sizeof(O18_SAT_DEMOD_FW_b_0_1[0].firmware_table);

		DEMOD_PRINT_ALWAYS("##### O18 B0 FW uploaded in DEMOD_O18_SAT_FW_Initialize()#####\n");
		DEMOD_PRINT_ALWAYS("##### FW size = 0x%x(%d)#####\n",size,size);
	}
	else
	{
		data 	= O18_SAT_DEMOD_FW_0_0_1[0].firmware_table;
		size 		= sizeof(O18_SAT_DEMOD_FW_0_0_1[0].firmware_table);

		DEMOD_PRINT_ALWAYS("##### O18 A0 FW uploaded in DEMOD_O18_SAT_FW_Initialize()#####\n");
	}

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
		DEMOD_PRINT("[DEMOD O18 DBB] FAIL (%s:%d) DEMOD_L2_Set_MemAddr !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	DEMOD_PRINT_ALWAYS("[DEMOD O18 DBB] mem_base_addr = 0x%x !!!\n", mem_base_addr);

		// need to be check !!!!!
	DEMOD_L2_Set_ChipInfo(pFrontend, 0x18a0);
	DEMOD_PRINT_ALWAYS("##########check START chungiii DEMOD_O18_SAT_FW_Initialize\n");

#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(3000,10000);	/* 3ms ~ 10ms */

 	}
#endif

	for(tryCount = 0; tryCount < 5; tryCount++)
	{

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through AXI BUS\n");

		#if 1
//			ret = DEMOD_L2_InitMem(pFrontend);
			ret = DEMOD_L2_PowerUpWithMem(pFrontend);

/*			if(ret != NO_DEMOD_ERROR)
			{	//PowerUp into bootloader
				DBB_PRINT ("DEMOD_L2_PowerUpWithPatch error 0x%02x: %s\n", ret, DEMOD_L1_API_Error_Text(ret) );
				return ret;
			}
*/
			if(ret == NO_DEMOD_ERROR)
			{
				DEMOD_PRINT_ALWAYS("##########check END chungiii DEMOD_O18_SAT_FW_Initialize\n");
				DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}
			else
			{
				printk(" DEMOD_L2_InitMem  ERROR~!!![0x%x]\n", ret);
				DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
		#endif

		}
		else
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through I2C\n");
			if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
			else
			{
				DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}
		}
	}

	if(tryCount == 5)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) LGDBB Fail!! => Count(%d)\n", __F__, __L__, tryCount);
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("##########check chungiii DEMOD_O18_SAT_FW_Initialize\n");
	//DEMOD_O18_Get_FW_PartInfo();    // should be check when bringup

	//DEMOD_PRINT_ALWAYS("##########check chungiii skip~!!! DEMOD_O18_FW_Initialize\n");


	// need to check O18 FW ver address ~!!!!!
	do
	{
		pRdata = (volatile UINT32 *)ioremap(0xC600F000, sizeof(UINT32));

		if (pRdata==NULL)
		{
			break;
		}

		sys_val = (*pRdata);
		printk("##########check chungiii reading O18 FW ver through APB[0x%x]\n", sys_val);
	} while(0);

	iounmap((void *)pRdata);

	////////////////////check APB buffer
	#if 0
	printk("#######chungiii check ############################## \n");
	w_val	= 1;
	//DEMOD_APB_Write(0x44, &w_val);
	printk("#######chungiii check ############################## \n");

	DEMOD_L2_SET_REG(pFrontend,  0x0, 4, 0x181234);
	printk("#######chungiii check  MCU buffer \n");
	DEMOD_APB_Read(0x50, &sys_val);
	DEMOD_APB_Read(0x54, &sys_val);
	DEMOD_APB_Read(0x40, &sys_val);
	//DEMOD_APB_Read(0x44, &sys_val);

	#endif

	#if 0
	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!!\n", __F__);
	}
	#endif

	#if 0
	TE_MCU_RegisterRecoveryCallback(TE_MCU_FUNC_TYPE_DEMOD,
			RecoveryPreCallback, RecoveryPostCallback, NULL);
	#endif



	return RET_OK;


}

int DEMOD_O18_ALL_FW_Initialize(void)
{
	LX_DEMOD_L2_Context *pFrontend;
	volatile UINT32 *pRdata = NULL;
	UINT32 sys_val; //, w_val;

	UINT8  tryCount = 0;
	UINT8  ret = 0;

	const void *data = NULL;
	UINT32 size;
//	UINT32 addr;
	UINT32 *fw_addr = NULL;
	UINT32 mem_base_addr;
//	UINT32 busPendCount = 0;

	pFrontend = &gO18_LGDBB_Frontend;

	gDemodFwMemConfigured = 0;	// DemodFW memory should be configured (cold boot & instant boot)

	DEMOD_PRINT_ALWAYS("##### DEMOD_O18_ALL_FW_Initialize() start #####\n");

	DEMOD_APB_REG_WR(0xC600f004, 0x00000001);

#if 0
	data = O18_DEMOD_FW_0_1_0[0].firmware_table;
	size = sizeof(O18_DEMOD_FW_0_1_0[0].firmware_table);
#endif

	if (lx_chip_rev( ) >= LX_CHIP_REV(O18,B0))
	{
		data 	= O18_DEMOD_FW_b_0_1[0].firmware_table;
		size 		= sizeof(O18_DEMOD_FW_b_0_1[0].firmware_table);
		DEMOD_PRINT_ALWAYS("##### O18 B0 FW uploaded in DEMOD_O18_ALL_FW_Initialize()#####\n");
		DEMOD_PRINT_ALWAYS("##### FW size = 0x%x(%d)#####\n",size,size);
	}
	else
	{
		data 	= O18_DEMOD_FW_0_0_1[0].firmware_table;
		size 		= sizeof(O18_DEMOD_FW_0_0_1[0].firmware_table);
		DEMOD_PRINT_ALWAYS("##### O18 A0 FW uploaded in DEMOD_O18_ALL_FW_Initialize()#####\n");
	}

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
		DEMOD_PRINT("[DEMOD O18 DBB] FAIL (%s:%d) DEMOD_L2_Set_MemAddr !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT_ALWAYS("[DEMOD O18 DBB] mem_base_addr = 0x%x !!!\n", mem_base_addr);

		// need to be check !!!!!
	DEMOD_L2_Set_ChipInfo(pFrontend, 0x18a0);
	DEMOD_PRINT_ALWAYS("##########check START chungiii DEMOD_O18_ALL_FW_Initialize\n");

#if 0
	for(tryCount = 0; tryCount < 10; tryCount++)
 	{
		DEMOD_APB_REG_RD(0xC97f2704, busPendCount);
		DEMOD_PRINT_ALWAYS("##### Try %d ####Bus pending count = 0x%x\n",tryCount, busPendCount);
		usleep_range(3000,10000);	/* 3ms ~ 10ms */

 	}
#endif

	for(tryCount = 0; tryCount < 5; tryCount++)
	{

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through AXI BUS\n");

		#if 1
//			ret = DEMOD_L2_InitMem(pFrontend);
			ret = DEMOD_L2_PowerUpWithMem(pFrontend);

/*			if (ret != NO_DEMOD_ERROR)
			{	// PowerUp into bootloader
				DBB_PRINT ("DEMOD_L2_PowerUpWithPatch error 0x%02x: %s\n", ret, DEMOD_L1_API_Error_Text(ret) );
				return ret;
			}
*/
			if(ret == NO_DEMOD_ERROR)
			{
				DEMOD_PRINT_ALWAYS("##########check END chungiii DEMOD_O18_ALL_FW_Initialize\n");
				DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}
			else
			{
				printk(" DEMOD_L2_InitMem  ERROR~!!![0x%x]\n", ret);
				DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
		#endif

		}
		else
		{
			DEMOD_PRINT_ALWAYS("f/w downloading through I2C\n");
			if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!! => Count(%d)\n", __F__, tryCount);
				OS_MsecSleep(20);
				continue;
			}
			else
			{
				DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Success!! => Count(%d)\n", __F__, tryCount);
				break;
			}
		}
	}

	if(tryCount == 5)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s:%d) LGDBB Fail!! => Count(%d)\n", __F__, __L__, tryCount);
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("##########check chungiii DEMOD_O18_ALL_FW_Initialize\n");
	//DEMOD_O18_Get_FW_PartInfo();    // should be check when bringup

	//DEMOD_PRINT_ALWAYS("##########check chungiii skip~!!! DEMOD_O18_FW_Initialize\n");


	// need to check O18 FW ver address ~!!!!!
	do
	{
		pRdata = (volatile UINT32 *)ioremap(0xC600F000, sizeof(UINT32));
		if (pRdata==NULL)
		{
			break;
		}
		sys_val = (*pRdata);
		printk("##########check chungiii reading O18 FW ver through APB[0x%x]\n", sys_val);
	} while(0);
	iounmap((void *)pRdata);

	////////////////////check APB buffer
	#if 0
	printk("#######chungiii check ############################## \n");
	w_val	= 1;
	//DEMOD_APB_Write(0x44, &w_val);
	printk("#######chungiii check ############################## \n");

	DEMOD_L2_SET_REG(pFrontend,  0x0, 4, 0x181234);
	printk("#######chungiii check  MCU buffer \n");
	DEMOD_APB_Read(0x50, &sys_val);
	DEMOD_APB_Read(0x54, &sys_val);
	DEMOD_APB_Read(0x40, &sys_val);
	//DEMOD_APB_Read(0x44, &sys_val);

	#endif

	#if 0
	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT("[O18 LGDBB] (%s) LGDBB Fail!!\n", __F__);
	}
	#endif

	#if 0
	TE_MCU_RegisterRecoveryCallback(TE_MCU_FUNC_TYPE_DEMOD,
			RecoveryPreCallback, RecoveryPostCallback, NULL);
	#endif

	return RET_OK;
}

int DEMOD_O18_FW_Configuration_Initialize(LX_DEMOD_OPER_MODE_T operMode)
{
	UINT32 return_code;
	LX_DEMOD_L2_Context *pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;

	DBB_PRINT ("DEMOD_O18_FW_Configuration_Initialize OPmode is %x \n", operMode );

	/* At this point, FW is loaded and started.  */
	return_code = DEMOD_L2_Opermode_Configure (pFrontend , operMode) ;
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L2_Opermode_Configure error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	return RET_OK;

}

int DEMOD_O18_Opermode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_opermode;

	switch (pDemodInfo->operMode)
	{
		case	LX_DEMOD_ATSC:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_VSB;	break;
		case	LX_DEMOD_QAM: 			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_QAM;	break;
		case	LX_DEMOD_ISDBT: 		new_opermode = DEMOD_DD_MODE_PROP_MODULATION_ISDBT;	break;
		case	LX_DEMOD_DVBC:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBC;	break;
		case	LX_DEMOD_DVBC2:		new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBC2;	break;
		case	LX_DEMOD_DVBT:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBT;	break;
		case	LX_DEMOD_DVBT2:		new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;	break;
		case	LX_DEMOD_DVBS:			new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBS;	break;
		case	LX_DEMOD_DVBS2:		new_opermode = DEMOD_DD_MODE_PROP_MODULATION_DVBS2;	break;

		default:						return DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN;
	}

	return new_opermode;
}

int DEMOD_O18_Get_BW(DEMOD_CTX_T *pDemodInfo, UINT16 *pter_bandwidth_KHz)
{

	UINT16  ter_bandwidth_KHz = 8000;

	switch (pDemodInfo->operMode)
	{
			case	LX_DEMOD_ATSC:			ter_bandwidth_KHz = 6000; break;
			case	LX_DEMOD_QAM:			ter_bandwidth_KHz = 6000; break;
			case	LX_DEMOD_ISDBT: 		ter_bandwidth_KHz = 6000; break;
			case	LX_DEMOD_DVBC: 		ter_bandwidth_KHz = 8000; break;
			case	LX_DEMOD_DVBT:
				{
					switch(pDemodInfo->setCfgParam.dvbt.channelBW)
					{
						case LX_DEMOD_BW_6MHZ: 		ter_bandwidth_KHz = 6000; break;
						case LX_DEMOD_BW_7MHZ:		ter_bandwidth_KHz = 7000; break;
						case LX_DEMOD_BW_8MHZ:		ter_bandwidth_KHz = 8000; break;
						default :					break;
					}
				}
				break;

			case	LX_DEMOD_DVBT2:
				{
					switch(pDemodInfo->setCfgParam.dvbt2.channelBW)
					{
						case LX_DEMOD_BW_1_7MHZ: 		ter_bandwidth_KHz = 1700; break;
						case LX_DEMOD_BW_5MHZ:		ter_bandwidth_KHz = 5000; break;
						case LX_DEMOD_BW_6MHZ: 		ter_bandwidth_KHz = 6000; break;
						case LX_DEMOD_BW_7MHZ:		ter_bandwidth_KHz = 7000; break;
						case LX_DEMOD_BW_8MHZ:		ter_bandwidth_KHz = 8000; break;
						default :					break;

					}
				}
				break;

			case	LX_DEMOD_DTMB:
				{
					switch(pDemodInfo->setCfgParam.dtmb.channelBW)
					{
						case LX_DEMOD_BW_6MHZ:		ter_bandwidth_KHz = 6000; break;
						case LX_DEMOD_BW_7MHZ:		ter_bandwidth_KHz = 7000; break;
						case LX_DEMOD_BW_8MHZ:		ter_bandwidth_KHz = 8000; break;
						default :					break;

					}
				}
				break;

			default:
			{
				ter_bandwidth_KHz = 8000;
				break;
			}
	}

	*pter_bandwidth_KHz = ter_bandwidth_KHz;

	return RET_OK;
}

int DEMOD_O18_Get_FW_PartInfo(UINT32 *pFW_Info)
{
	LX_DEMOD_L2_PART_INFO fw_part_Info;
	LX_DEMOD_L2_Context *pFrontend;

	UINT32	FW_Info;

	pFrontend = &gO18_LGDBB_Frontend;


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

	DEMOD_PRINT("FW_Info = [%x]\n", (int)FW_Info);

	*pFW_Info = FW_Info;

	return RET_OK;
}


int DEMOD_O18_Debug_ATSC_ReadREGvalue(UINT16 address, UINT32 *pData)
{
//	UINT8 	vqData;
	UINT8 	pvalue[4];

	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;


	if(RET_OK != DEMOD_L2_GET_REG(pFrontend, address, 4, pvalue))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_L2_GET_REG() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	*pData = ((pvalue[0]) |  (pvalue[1] << 8) | (pvalue[2] << 16) | (pvalue[3] << 24));

	printk("[DEMOD] address = 0x%x, value = 0x%x !!!\n",address,*pData );

	return RET_OK;
}

int DEMOD_O18_Debug_ATSC_WriteREGvalue(UINT16 address, UINT32 *pData)
{
	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;

	if(RET_OK != DEMOD_L2_SET_REG(pFrontend, address, 4, *pData))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_L2_SET_REG !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	printk("[DEMOD] address = 0x%x, value = 0x%x !!!\n",address, *pData );

	return RET_OK;
}

int DEMOD_O18_Get_Dump(void)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	pFrontend = &gO18_LGDBB_Frontend;

	printk("########chungii call O18 dump\n");
	if(RET_OK != DEMOD_L2_GetDump(pFrontend))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_L2_GetDump() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_Signal_Information
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_Signal_Information(LX_DEMOD_SIGNAL_TOTAL_T *pSignalStatus)
{
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	LX_DEMOD_L2_Context 		*pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

//	*pVber = signalStatus.ber ;

	pSignalStatus->freqOff 			= signalStatus.offsetFrq_Hz/1000;
	pSignalStatus->ifAgc				= signalStatus.if_agc;
	pSignalStatus->packetError 		= signalStatus.packetError;
	pSignalStatus->vBer				= signalStatus.ber;
	pSignalStatus->sigMse.bMse		= 0;
	pSignalStatus->sigMse.mse		= signalStatus.mse_info;
	pSignalStatus->sigMse.constPwr	= signalStatus.constPwr;

	DEMOD_PRINT("(%s) pSignalStatus->freqOff = 0x%x \n", __F__, pSignalStatus->freqOff);
	DEMOD_PRINT("(%s) pSignalStatus->ifAgc = 0x%x \n", __F__, pSignalStatus->ifAgc);
	DEMOD_PRINT("(%s) pSignalStatus->packetError = 0x%x \n", __F__, pSignalStatus->packetError);
	DEMOD_PRINT("(%s) pSignalStatus->vBer = 0x%x \n", __F__, pSignalStatus->vBer);
	DEMOD_PRINT("(%s) pSignalStatus->sigMse.bMse = 0x%x \n", __F__, pSignalStatus->sigMse.bMse);
	DEMOD_PRINT("(%s) pSignalStatus->sigMse.mse = 0x%x \n", __F__, pSignalStatus->sigMse.mse);
	DEMOD_PRINT("(%s) pSignalStatus->sigMse.constPwr = 0x%x \n", __F__, pSignalStatus->sigMse.constPwr);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_Get_CFG_Information
 * Get BER before RS on DVB
 *
 * @param *pVber 	[OUT] UINT32.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_Get_CFG_Information(LX_DEMOD_SIGNAL_TUNE_CFG_T *pSignalStatus)
{
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;
	LX_DEMOD_L2_Context 		*pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[O18 LGDBB] (%s:%d) DEMOD_L2_SignalStatus  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

//	*pVber = signalStatus.ber ;

	pSignalStatus->carr_mode 	= signalStatus.carr_mode;
	pSignalStatus->codeRate		= signalStatus.codeRate;
	pSignalStatus->constellation	= signalStatus.constellation;
	pSignalStatus->fftMode		= signalStatus.fftMode;
	pSignalStatus->guardInterval	= signalStatus.guardInterval;
	pSignalStatus->hierarchy		= signalStatus.hierarchy;
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




#endif
