/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/** @file
 *
 *	BE REG module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>	/**< printk() */
#include <asm/io.h>			/**< For ioremap_nocache */
#include "os_util.h"

#include "be_dbg.h"
#include "be_def.h"
#include "be_reg_hw_o26.h"
#include "be_reg_def_o26.h"
#include "be_reg_dpe_o26.h"
#include "be_reg_pwm_o26.h"
#include "be_reg_cco_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define REG_WD( addr, value)	( *( volatile UINT32 * )( addr )) = ( UINT32 )( value)
#define REG_RD( addr )			( *( volatile UINT32 * )( addr ))
#define GET_BITS(val,nd,wd)		(((val)>>(nd))&(0xFFFFFFFF>>(32-(wd))))
#define GET_PVAL(val,nd,wd)		(GET_BITS(val,nd,wd)<<(nd))

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BE_PWM_REG_O26_T gBE_PWM_O26;
BE_LED_REG_O26_T gBE_LED_O26;
BE_OLED_REG_O26_T gBE_OLED_O26;
BE_PCC_REG_O26_T gBE_PCC_O26;
BE_PCC_WIN_REG_O26_T gBE_PCC_WIN_O26;
BE_L3D_REG_O26_T gBE_L3D_O26;
BE_OSD_REG_O26_T gBE_OSD_O26;
BE_UCR_REG_O26_T gBE_UCR_O26;
BE_DEC_REG_O26_T gBE_DEC_O26;
BE_CC2_REG_O26_T gBE_CC2_O26;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_REG_HW_O26_Initialize(void)
{
	int ret = RET_OK;

	do {
		gBE_PWM_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_PWM_T));
		gBE_LED_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_LED_T));
		gBE_OLED_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_OLED_T));
		gBE_PCC_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_CC_PE_PCC_T));
		gBE_PCC_WIN_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_CC_PCC_WINCTRL_T));
		gBE_L3D_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_L3D_L3D_CORE_CTRL_T));
		gBE_OSD_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T));
		gBE_UCR_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_UCR_T));
		gBE_DEC_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_CCO_DEC_T));
		gBE_CC2_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(BE_O26A0_REG_CC2_T));

		gBE_PWM_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_PWM_T_BASE, sizeof(BE_O26A0_REG_PWM_T));
		gBE_LED_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_LED_T_BASE, sizeof(BE_O26A0_REG_LED_T));
		gBE_OLED_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_OLED_T_BASE, sizeof(BE_O26A0_REG_OLED_T));
		gBE_PCC_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_CC_PE_PCC_T_BASE, sizeof(BE_O26A0_REG_CC_PE_PCC_T));
		gBE_PCC_WIN_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_CC_PCC_WINCTRL_T_BASE, sizeof(BE_O26A0_REG_CC_PCC_WINCTRL_T));
		gBE_L3D_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_L3D_L3D_CORE_CTRL_T_BASE, sizeof(BE_O26A0_REG_L3D_L3D_CORE_CTRL_T));
		gBE_OSD_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T_BASE, sizeof(BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T));
		gBE_UCR_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_UCR_T_BASE, sizeof(BE_O26A0_REG_UCR_T));
		gBE_DEC_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_CCO_DEC_T_BASE, sizeof(BE_O26A0_REG_CCO_DEC_T));
		gBE_CC2_O26.phys.addr = (volatile UINT32 *)ioremap(BE_O26A0_REG_CC2_T_BASE, sizeof(BE_O26A0_REG_CC2_T));

	} while(0);

	return ret;
}

int BE_REG_HW_O26_Close(void)
{
	int ret = RET_OK;

	if (gBE_PWM_O26.shdw.addr) OS_Free((void *)gBE_PWM_O26.shdw.addr);
	if (gBE_LED_O26.shdw.addr) OS_Free((void *)gBE_LED_O26.shdw.addr);
	if (gBE_OLED_O26.shdw.addr) OS_Free((void *)gBE_OLED_O26.shdw.addr);
	if (gBE_PCC_O26.shdw.addr) OS_Free((void *)gBE_PCC_O26.shdw.addr);
	if (gBE_PCC_WIN_O26.shdw.addr) OS_Free((void *)gBE_PCC_WIN_O26.shdw.addr);
	if (gBE_L3D_O26.shdw.addr) OS_Free((void *)gBE_L3D_O26.shdw.addr);
	if (gBE_OSD_O26.shdw.addr) OS_Free((void *)gBE_OSD_O26.shdw.addr);
	if (gBE_UCR_O26.shdw.addr) OS_Free((void *)gBE_UCR_O26.shdw.addr);
	if (gBE_DEC_O26.shdw.addr) OS_Free((void *)gBE_DEC_O26.shdw.addr);
	if (gBE_CC2_O26.shdw.addr) OS_Free((void *)gBE_CC2_O26.shdw.addr);

	if (gBE_PWM_O26.phys.addr) iounmap((void *)gBE_PWM_O26.phys.addr);
	if (gBE_LED_O26.phys.addr) iounmap((void *)gBE_LED_O26.phys.addr);
	if (gBE_OLED_O26.phys.addr) iounmap((void *)gBE_OLED_O26.phys.addr);
	if (gBE_PCC_O26.phys.addr) iounmap((void *)gBE_PCC_O26.phys.addr);
	if (gBE_PCC_WIN_O26.phys.addr) iounmap((void *)gBE_PCC_WIN_O26.phys.addr);
	if (gBE_L3D_O26.phys.addr) iounmap((void *)gBE_L3D_O26.phys.addr);
	if (gBE_OSD_O26.phys.addr) iounmap((void *)gBE_OSD_O26.phys.addr);
	if (gBE_DEC_O26.phys.addr) iounmap((void *)gBE_DEC_O26.phys.addr);
	if (gBE_CC2_O26.phys.addr) iounmap((void *)gBE_CC2_O26.phys.addr);

	return ret;
}

int BE_REG_HW_O26_Read(BE_REG_RW_TYPE_T type, void *addr, UINT32 *data)
{
	int ret = RET_OK;
	UINT32 value;
	void *recvAddr;
	void *currAddr;
	UINT32 nextValue;
	uintptr_t dBit;
	uintptr_t wBit;

	do{
		recvAddr  = addr;

		switch(type)
		{
			case BE_REG_RW_TYPE_DPPB_LED:
				recvAddr = (void *)((uintptr_t)recvAddr +
									(uintptr_t)gBE_LED_O26.phys.addr);
				break;
			case BE_REG_RW_TYPE_NONE:
			default :
				return RET_ERROR;
		}

		currAddr = recvAddr;
		/* for safety */
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);

		value = REG_RD(currAddr);
		if(currAddr == recvAddr) break;
		nextValue = REG_RD(currAddr+4);
		dBit = ((uintptr_t)recvAddr - (uintptr_t)currAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	} while(0);

	*data = value;

	return ret;
}

int BE_REG_HW_O26_Write(BE_REG_RW_TYPE_T type, void *addr, UINT32 data)
{
	int ret = RET_OK;
	UINT32 value;
	void *recvAddr;
	void *currAddr;
	UINT32 nextValue;
	UINT32 currValue;
	uintptr_t dBit;
	uintptr_t wBit;

	do{
		recvAddr  = addr;
		value = data;

		switch(type)
		{
			case BE_REG_RW_TYPE_DPPB_LED:
				recvAddr = (void *)((uintptr_t)recvAddr +
									(uintptr_t)gBE_LED_O26.phys.addr);
				break;
			case BE_REG_RW_TYPE_NONE:
			default :
				return RET_ERROR;
		}

		currAddr = recvAddr;

		/* for safety */
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);

		if(currAddr == recvAddr)
		{
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(currAddr);
		nextValue = REG_RD((currAddr+4));
		dBit = ((uintptr_t)recvAddr - (uintptr_t)currAddr)<<3;
		wBit = (32 - dBit);
		currValue  = GET_BITS(currValue, 0, dBit);
		currValue += GET_PVAL(value    , dBit, wBit);
		nextValue  = GET_PVAL(nextValue, dBit, wBit);
		nextValue += GET_BITS(value    , 0	 , dBit);
		REG_WD(currAddr	, currValue);
		REG_WD((currAddr+4), nextValue);
	}
	while(0);

	return ret;
}

/** @} */
