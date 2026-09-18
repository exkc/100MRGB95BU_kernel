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
#include "be_reg_hw_e60.h"
#include "be_reg_def_e60.h"
#include "be_reg_dpe_e60.h"
#include "be_reg_pwm_e60.h"

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
typedef struct {

} BE_REG_HW_E60_INFO_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
PE_PWM_REG_E60_T gPE_PWM_E60;
DPE_LED_REG_E60_T gDPE_LED_E60;
DPE_OLED_REG_E60_T gDPE_OLED_E60;
PE_PCC_REG_E60_T gPE_PCC_E60;
L3D_REG_E60_T gL3D_E60;
PE_OSD_REG_E60_T gPE_OSD_E60;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
//static BE_REG_HW_E60_INFO_T gstBeRegHwE60Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_REG_HW_E60_Initialize(void)
{
	int ret = RET_OK;

	do {
		gPE_PWM_E60.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PWM_REG_E60A0_T));
		gDPE_LED_E60.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DPE_LED_REG_E60A0_T));
		gDPE_OLED_E60.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DPE_OLED_REG_E60A0_T));
		gPE_PCC_E60.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PCC_REG_E60A0_T));
		gL3D_E60.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(L3D_REG_E60A0_T));
		gPE_OSD_E60.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OSD0_IMAGE_REG_E60A0_T));

		gPE_PWM_E60.phys.addr = (volatile UINT32 *)ioremap(PE_PWM_REG_E60A0_BASE, sizeof(PE_PWM_REG_E60A0_T));
		gDPE_LED_E60.phys.addr = (volatile UINT32 *)ioremap(DPE_LED_REG_E60A0_BASE, sizeof(DPE_LED_REG_E60A0_T));
		gDPE_OLED_E60.phys.addr = (volatile UINT32 *)ioremap(DPE_OLED_REG_E60A0_BASE, sizeof(DPE_OLED_REG_E60A0_T));
		gPE_PCC_E60.phys.addr = (volatile UINT32 *)ioremap(PE_PCC_REG_E60A0_BASE, sizeof(PE_PCC_REG_E60A0_T));
		gL3D_E60.phys.addr = (volatile UINT32 *)ioremap(L3D_REG_E60A0_BASE, sizeof(L3D_REG_E60A0_T));
		gPE_OSD_E60.phys.addr = (volatile UINT32 *)ioremap(PE_OSD_REG_E60A0_BASE, sizeof(PE_OSD0_IMAGE_REG_E60A0_T));
	} while(0);

	return ret;
}

int BE_REG_HW_E60_Close(void)
{
	int ret = RET_OK;

	if (gPE_PWM_E60.shdw.addr) OS_Free((void *)gPE_PWM_E60.shdw.addr);
	if (gDPE_LED_E60.shdw.addr) OS_Free((void *)gDPE_LED_E60.shdw.addr);
	if (gDPE_OLED_E60.shdw.addr) OS_Free((void *)gDPE_OLED_E60.shdw.addr);
	if (gPE_PCC_E60.shdw.addr) OS_Free((void *)gPE_PCC_E60.shdw.addr);
	if (gL3D_E60.shdw.addr) OS_Free((void *)gL3D_E60.shdw.addr);
	if (gPE_OSD_E60.shdw.addr) OS_Free((void *)gPE_OSD_E60.shdw.addr);

	if (gPE_PWM_E60.phys.addr) iounmap((void *)gPE_PWM_E60.phys.addr);
	if (gDPE_LED_E60.phys.addr) iounmap((void *)gDPE_LED_E60.phys.addr);
	if (gDPE_OLED_E60.phys.addr) iounmap((void *)gDPE_OLED_E60.phys.addr);
	if (gPE_PCC_E60.phys.addr) iounmap((void *)gPE_PCC_E60.phys.addr);
	if (gL3D_E60.phys.addr) iounmap((void *)gL3D_E60.phys.addr);
	if (gPE_OSD_E60.phys.addr) iounmap((void *)gPE_OSD_E60.phys.addr);

	return ret;
}

int BE_REG_HW_E60_Read(BE_REG_RW_TYPE_T type, void *addr, UINT32 *data)
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
									(uintptr_t)gDPE_LED_E60.phys.addr);
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

int BE_REG_HW_E60_Write(BE_REG_RW_TYPE_T type, void *addr, UINT32 data)
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
									(uintptr_t)gDPE_LED_E60.phys.addr);
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
