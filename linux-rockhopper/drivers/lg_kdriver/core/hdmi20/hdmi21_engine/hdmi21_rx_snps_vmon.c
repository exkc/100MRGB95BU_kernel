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
 *  @date		2019-03-25
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
#include "hdmi21_rx_snps_vmon.h"

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
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];

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
========================================================================================*/
void HDMI21_VMON_Rx_Set_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int sourceType)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __reg;

	/* Check if handler is initiated */
	if(!_p->initiated) {
		HDMI20_ERROR("Error[%s][%d] Port [%d]->Access without Initialization\n", __F__, __L__,  _p->port);
		return;
	}

	/* Get Reg */
	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_CONTROL);
	

	/* Set source Type */
	__reg &= (~HDMI21_SNPS_FIELD_VMON_SOURCE_SEL);

	if((sourceType < 0) || (sourceType >= 8)) __data = 0;
	else __data = sourceType;

	__data = (__data << 28) & HDMI21_SNPS_FIELD_VMON_SOURCE_SEL;
	__reg |= __data;
	
	
	/* Set ISR THRES : VMON IRQ*/
	if(gHDMI21RxDevLinkControler[HDMI21__LINK_VMON_IRQ_THR_MODE].value > 0) __reg |= (HDMI21_SNPS_FIELD_VMON_IRQ_THR_MODE);
	else __reg &= (~HDMI21_SNPS_FIELD_VMON_IRQ_THR_MODE);

	/* Write Reg */
	_p->link_write(HDMI21_SNPS_REG_VMON_CONTROL, __reg);

	return;
}


void HDMI21_VMON_Rx_Get_VideoSync(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_VMON_VIDEO_SYNC_T *pData)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_VMON_VIDEO_SYNC_T __data;
	UINT32 __reg;

	/* Null Pointer defence */
	if(pData == NULL) return;

	/* Check if handler is initiated */
	if(!_p->initiated) {
		HDMI20_ERROR("Error[%s][%d] Port [%d]->Access without Initialization\n", __F__, __L__,  _p->port);
		return;
	}

	/* Clear memory */
	memset((void *)&__data, 0, sizeof(HDMI21_VMON_VIDEO_SYNC_T));

	/* Get Data */
	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS1);
	__data.hsync	= 0x0000FFFF & ((HDMI21_SNPS_FIELD_VMON_HSYNCWIDTH 	& __reg)>>16); 
	__data.hfront	= 0x0000FFFF & ( HDMI21_SNPS_FIELD_VMON_HFRONT		& __reg);

	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS2);
	__data.hblank	= 0x0000FFFF & ((HDMI21_SNPS_FIELD_VMON_HBLANK		& __reg)>>16);
	__data.hback	= 0x0000FFFF & ( HDMI21_SNPS_FIELD_VMON_HBACK		& __reg);

	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS3);
	__data.htotal	= 0x0000FFFF & ((HDMI21_SNPS_FIELD_VMON_HTOTAL		& __reg)>>16);
	__data.hactive	= 0x0000FFFF & ( HDMI21_SNPS_FIELD_VMON_HACTIVE		& __reg);;
	
	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS4);
	__data.vsync	= 0x0000FFFF & ((HDMI21_SNPS_FIELD_VMON_VSYNCWIDTH 	& __reg)>>16);
	__data.vfront	= ( HDMI21_SNPS_FIELD_VMON_VFRONT		& __reg);

	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS5);
	__data.vblank	= 0x0000FFFF & ((HDMI21_SNPS_FIELD_VMON_VBLANK		& __reg)>>16);
	__data.vback	= 0x0000FFFF & ( HDMI21_SNPS_FIELD_VMON_VBACK		& __reg);

	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS6);
	__data.vtotal	= 0x0000FFFF & ((HDMI21_SNPS_FIELD_VMON_VTOTAL		& __reg)>>16);
	__data.vactive	= 0x0000FFFF & ( HDMI21_SNPS_FIELD_VMON_VACTIVE		& __reg);;

	__reg = _p->link_read(HDMI21_SNPS_REG_VMON_STATUS7);
	if( HDMI21_SNPS_FIELD_VMON_ALT_DETECT & __reg) __data.isEvenFrame = true;
	if( HDMI21_SNPS_FIELD_VMON_ILACE_DETECT & __reg) __data.isInterlaced = true;
	if( HDMI21_SNPS_FIELD_VMON_FIELD_DETECT & __reg) __data.isField1 = true;

	HDMI21_LINE_DBG(164, "DBG[%d] :  [%d](%d) x [%d](%d)\n", _p->port,  __data.hactive, __data.htotal, __data.vactive, __data.vtotal);

	/* Copy Data */
	memcpy((void *)pData, (void *)&__data, sizeof(HDMI21_VMON_VIDEO_SYNC_T));

	return;
}

void HDMI21_VMON_Rx_Set_InsertVideoSyncToHandler(HDMI21_VMON_VIDEO_SYNC_T *pData, HDMI21_HAL_VIDEO_TIMING_T *pDest)
{
	/* Null Pointer defence */
	if(pData == NULL) return;

	if(pDest == NULL) return;

	pDest->interlaced = pData->isInterlaced;/** Interlaced */
	pDest->voffset	= pData->vsync;	/** Vertical offset */
	pDest->vactive	= pData->vactive;/** Vertical active */
	pDest->vtotal	= pData->vtotal;/** Vertical total */
	pDest->hoffset	= pData->hsync;/** Horizontal offset */
	pDest->hactive	= pData->hactive;/** Horizontal active */
	pDest->htotal	= pData->htotal;	/** Horizontal total */


	return;
}
/*========================================================================================
 Static Function Implementation 
======================================================================================== */


