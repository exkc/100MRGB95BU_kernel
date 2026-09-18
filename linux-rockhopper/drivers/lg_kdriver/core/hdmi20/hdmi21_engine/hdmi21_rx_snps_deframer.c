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


/** @file 
 *
 *  Brief description. 
 *  Detailed description starts here. 
 *
 *  @author		won.hur
 *  @version	1.0 
 *  @date		2019-04-17
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/delay.h>
#include "../hdmi20_drv.h" 			/* For debug prints */
#include "hdmi21_hal_driver.h"		/* Device Handler */
#include "hdmi21_rx_snps_deframer.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
======================================================================================== */
void HDMI21_DEFRAMER_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Need to Implement */
	/* Set H/V sync inversion --> CVI will recongnize it to normal sync */
	HDMI21_DEFRAMER_Rx_Set_HVSyncPolarity(_p, 1, 0, 0);

	/* Default Preamble Lock value */
	HDMI21_DEFRAMER_Rx_Set_NumOfPreambleLock(_p, 8);

	/* DVI/HDMI threshold */
	HDMI21_DEFRAMER_Rx_Set_DviHdmiThresHold(_p,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_DVI_TO_HDMI_THRESHOLD].value,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_HDMI_TO_DVI_THRESHOLD].value);
	
	return;
}

bool HDMI21_DEFRAMER_Rx_Get_IsDVIMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	bool ret = true;

	do{
		/* Defence Code */
		if(!_p->initiated) break;

		__data = _p->link_read(HDMI21_SNPS_REG_DEFRAMER_STATUS);

		if( (__data & HDMI21_SNPS_FIELD_AUTOHDMIDVI_STS) == 0) ret = true;
		else ret = false;

	}while(0);

	return ret;
}

UINT32 HDMI21_DEFRAMER_Rx_Get_CurrentOpMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 ret = 0;

	do{
		/* Defence Code */
		if(!_p->initiated) break;

		/* Read Register */
		__data = _p->link_read(HDMI21_SNPS_REG_DEFRAMER_STATUS);

		ret = ((__data & HDMI21_SNPS_FIELD_OPMODE_STS) >> 4);
	}while(0);

	return ret;
}

void HDMI21_DEFRAMER_Rx_Set_NumOfPreambleLock(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 num)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg;
	UINT32 __data = 0;

	do{
		/* Defence Code */
		if(!_p->initiated) break;

		if     (num == 0) 	__data = 0;
		else if(num >= 8) 	__data = 8;
		else 				__data = num;

		HDMI21_LINE_DBG(186, "DBG[%d] : Preamble Lock Value set to [%d]\n", _p->port, (int)__data);

		/* Shift & Mask Data */
		/* No need to shift */
		__data &= HDMI21_SNPS_FIELD_NUM_PREAMBLE_LOCK_QST;

		/* Read Register */
		__reg  = _p->link_read(HDMI21_SNPS_REG_DEFRAMER_CONFIG1);
		__reg &= (~HDMI21_SNPS_FIELD_NUM_PREAMBLE_LOCK_QST);
		__reg |= __data;

		HDMI21_LINE_DBG(186, "DEFRAMER[%d] : Preamble Lock Reg Set to [0x%08x]\n", _p->port, __reg);

		/* Write Register */
		_p->link_write(HDMI21_SNPS_REG_DEFRAMER_CONFIG1, __reg);
	}while(0);

	return;

}

void HDMI21_DEFRAMER_Rx_Set_HVSyncPolarity(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isAuto, bool hInversion, bool  vInversion)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg = 0x0;
	UINT32 __data0 = 0x0;
	UINT32 __data1 = 0x0;

	do{
		/* Defence Code */
		if(!_p->initiated) break;

		HDMI21_LINE_DBG(186, "DBG[%d] : Sync Polarity Set -> H[%s] V[%s]\n", _p->port, hInversion?"Invert":"Normal", vInversion?"Invert":"Normal");

		if(isAuto)
		{
			/* Shift & Mask Data */
			__data0 = 0x0;
			__data0 = __data0 <<18;		__data0 &= (HDMI21_SNPS_FIELD_HS_POL_QST);

			/* Shift & Mask Data */
			__data1 = 0x0;
			__data1 = __data1 <<16;		__data1 &= (HDMI21_SNPS_FIELD_VS_POL_QST);
		}
		else{
			/* Shift & Mask Data */
			if(hInversion)	__data0 = 0x1;	
			else			__data0 = 0x2;
			__data0 = __data0 <<18;		__data0 &= (HDMI21_SNPS_FIELD_HS_POL_QST);

			/* Shift & Mask Data */
			if(vInversion)	__data1 = 0x1;	
			else			__data1 = 0x2;
			__data1 = __data1 <<16;		__data1 &= (HDMI21_SNPS_FIELD_VS_POL_QST);
		}

		/* Read Register */
		__reg  = _p->link_read(HDMI21_SNPS_REG_DEFRAMER_CONFIG0);
		__reg &= (~HDMI21_SNPS_FIELD_HS_POL_QST);
		__reg &= (~HDMI21_SNPS_FIELD_VS_POL_QST);
		__reg |= __data0;
		__reg |= __data1;

		/* Write Register */
		_p->link_write(HDMI21_SNPS_REG_DEFRAMER_CONFIG0, __reg);
	}while(0);

	return;

}

void HDMI21_DEFRAMER_Rx_Set_DviHdmiThresHold(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int dviToHdmi, int hdmiToDvi)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg = 0x0;
	UINT32 __data0 = 0x0;
	UINT32 __data1 = 0x0;

	do{
		/* Defence Code */
		if(!_p->initiated) break;

		HDMI21_LINE_DBG(186, "DBG[%d] : Set DVI/HDMI threshold, DVI->HDMI[%d] HDMI->DVI[%d]\n", _p->port, dviToHdmi, hdmiToDvi);

		if(dviToHdmi <= 0) __data0 = 0;
		else if(dviToHdmi >= 8) __data0 = 7;
		else __data0 = (UINT32)dviToHdmi;

		if(hdmiToDvi <= 0) __data1 = 0;
		else if(hdmiToDvi >= 8) __data1 = 7;
		else __data1 = (UINT32)hdmiToDvi;

		__data0 = __data0 << 20;
		__data1 = __data1 << 24;


		/* Read Register */
		__reg  = _p->link_read(HDMI21_SNPS_REG_DEFRAMER_CONFIG1);
		__reg &= (~HDMI21_SNPS_FIELD_HDMI2DVI_THR_QST);
		__reg &= (~HDMI21_SNPS_FIELD_DVI2HDMI_THR_QST);
		__reg |= __data0;
		__reg |= __data1;

		/* Write Register */
		_p->link_write(HDMI21_SNPS_REG_DEFRAMER_CONFIG1, __reg);
	}while(0);

	return;

}

/*========================================================================================
 Static Function Implementation 
======================================================================================== */


