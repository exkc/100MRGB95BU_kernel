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

#include "os_util.h"
#include "sys_regs.h"

#include "../hdmi20_drv.h" 			/* For debug prints */
#include "hdmi21_hal_driver.h"		/* Device Handler */
#include "hdmi21_rx_snps_scdc.h"

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


extern char gHdmi21ScdcDeviceID_H;
extern char gHdmi21ScdcDeviceID_L;
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
HDMI21_SCDC_FRL_MODE_T HDMI21_SCDC_Rx_Get_ScdcMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_SCDC_FRL_MODE_T ret = HDMI21_SCDC_TMDS_3G;
	UINT32 _r1;
	UINT32 _r2;

	/* Defence Code */
	if(!_p->initiated) return ret;

	/* Get Scramble EN */
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		_r1 = _p->link_read(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_STATUS1);
	}
	else {
		_r1 = _p->link_read(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_STATUS1);
	}
	_r1 &= HDMI21_SNPS_FIELD_SCDC_TMDSBITCLKRATIO;

	/* Get FRL Rate */
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		_r2 = _p->link_read(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_STATUS2);
	}
	else {
		_r2 = _p->link_read(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_STATUS2);
	}
	_r2 &= HDMI21_SNPS_FIELD_SCDC_FRL_RATE;
	_r2 = _r2>>8; _r2 &= 0xF;	

	/* If Current SCDC mode is HDMI1.4*/
	if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_3G) {
		if(_r1) 	ret = HDMI21_SCDC_TMDS_6G;
		else {
			if(_r2 == 0){
				ret = HDMI21_SCDC_TMDS_3G;
			}
			else {
				/* From HDMI2.1 Spec Table 10-21 */
				if(_r2 == 1) 		ret = HDMI21_SCDC_FRL_3G_3L;
				else if(_r2 == 2)	ret = HDMI21_SCDC_FRL_6G_3L;
				else if(_r2 == 3)	ret = HDMI21_SCDC_FRL_6G_4L;
				else if(_r2 == 4)	ret = HDMI21_SCDC_FRL_8G_4L;
				else if(_r2 == 5)	ret = HDMI21_SCDC_FRL_10G_4L;
				else if(_r2 == 6)	ret = HDMI21_SCDC_FRL_12G_4L;
				else ret = HDMI21_SCDC_TMDS_3G;	
			}
		}
	}
	else if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
		/* From HDMI2.1 Spec Table 10-21 */
		if(_r2 == 1) 		ret = HDMI21_SCDC_FRL_3G_3L;
		else if(_r2 == 2)	ret = HDMI21_SCDC_FRL_6G_3L;
		else if(_r2 == 3)	ret = HDMI21_SCDC_FRL_6G_4L;
		else if(_r2 == 4)	ret = HDMI21_SCDC_FRL_8G_4L;
		else if(_r2 == 5)	ret = HDMI21_SCDC_FRL_10G_4L;
		else if(_r2 == 6)	ret = HDMI21_SCDC_FRL_12G_4L;
		else {
			if(_r1) 	{ret = HDMI21_SCDC_TMDS_6G;}
			else 		{ret = HDMI21_SCDC_TMDS_3G;}
		}
	}
	else {
		/* From HDMI2.1 Spec Table 10-21 */
		if(_r2 == 1) 		ret = HDMI21_SCDC_FRL_3G_3L;
		else if(_r2 == 2)	ret = HDMI21_SCDC_FRL_6G_3L;
		else if(_r2 == 3)	ret = HDMI21_SCDC_FRL_6G_4L;
		else if(_r2 == 4)	ret = HDMI21_SCDC_FRL_8G_4L;
		else if(_r2 == 5)	ret = HDMI21_SCDC_FRL_10G_4L;
		else if(_r2 == 6)	ret = HDMI21_SCDC_FRL_12G_4L;
		else {
			if(_r1) 	{ret = HDMI21_SCDC_TMDS_6G;}
			else 		{ret = HDMI21_SCDC_TMDS_3G;}
		}
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		HDMI21_LINE_DBG(3939, "DBG[%d] : SCDC return is [%d]. SCDC Status2[0x%08x], Status1[0x%08x]\n",\
				_p->port, ret, _p->link_read(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_STATUS2),\
				_p->link_read(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_STATUS1));
	}
	else{
		HDMI21_LINE_DBG(3939, "DBG[%d] : SCDC return is [%d]. SCDC Status2[0x%08x], Status1[0x%08x]\n",\
				_p->port, ret, _p->link_read(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_STATUS2),\
				_p->link_read(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_STATUS1));
	}

	return ret;
}

void HDMI21_SCDC_Rx_Set_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Read Data */
	__data  = _p->link_read(HDMI21_SNPS_REG_SCDC_CONFIG);

	/* Set Bit field for selected condition */
	if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRL_START_CHK_SB_QST].value > 0){
		__data |= (HDMI21_SNPS_FIELD_FRL_START_CHK_SB_QST);
	}
	else {
		__data &= (~HDMI21_SNPS_FIELD_FRL_START_CHK_SB_QST);
	}

	/* Write Data */
	_p->link_write(HDMI21_SNPS_REG_SCDC_CONFIG, __data);

	return;
}

void HDMI21_SCDC_Rx_Set_FrlStartManualOn(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Read Data */
	__data  = _p->link_read(HDMI21_SNPS_REG_SCDC_CONTROL);

	/* Set Bit field for selected condition */
	__data |= (HDMI21_SNPS_FIELD_FRL_START_OVR_P);

	HDMI20_PRINT("Link[%d] : FRL Start OVR_P to HIGH\n", _p->port);

	/* Write Data */
	_p->link_write(HDMI21_SNPS_REG_SCDC_CONTROL, __data);

	return;
}

void HDMI21_SCDC_Rx_Set_ScdcConfig(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __data0;
	UINT32 __data1;
	UINT32 __data2;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Read Data */
	__data  = _p->link_read(HDMI21_SNPS_REG_SCDC_CONFIG);
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		__data0 = _p->link_read(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG0);
	}
	else{
		__data0 = _p->link_read(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG0);
	}

	/* Set Device ID String for LG SIC */
	__data1 = HDMI20_SCDC_CHIP_DESCRIPTION_0;
	__data2 = HDMI20_SCDC_CHIP_DESCRIPTION_1;

	__data2 |= (((UINT32)gHdmi21ScdcDeviceID_H & 0xFF) << 16);
	__data2 |= (((UINT32)gHdmi21ScdcDeviceID_L & 0xFF) << 24);

	/* Set Bit field for selected condition */
	if(isSet) {
		__data &= (~HDMI21_SNPS_FIELD_SCDC_HPDLOW);
		__data &= (~HDMI21_SNPS_FIELD_SCDC_STANDBY);
		__data |= HDMI21_SNPS_FIELD_SCDC_POWERPROVIDED;

		__data0 &= (~HDMI21_SNPS_FIELD_SCDC_SINKVERSION_QST);
		__data0 |= 0x1;	//Sink version is set to 1
	}
	else {
		__data |= HDMI21_SNPS_FIELD_SCDC_HPDLOW;
		__data |= HDMI21_SNPS_FIELD_SCDC_STANDBY;
		__data &= (~HDMI21_SNPS_FIELD_SCDC_POWERPROVIDED);

		__data0 &= (~HDMI21_SNPS_FIELD_SCDC_SINKVERSION_QST);
		__data0 |= 0x1;	//Sink version is set to 1
	}

	/* Write Data */
	_p->link_write(HDMI21_SNPS_REG_SCDC_CONFIG, __data);
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		_p->link_write(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG0, __data0);
		
		_p->link_write(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG2, __data1);
		_p->link_write(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG3, __data2);
	}
	else {
		_p->link_write(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG0, __data0);

		_p->link_write(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG2, __data1);
		_p->link_write(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG3, __data2);
	}

	return;
}

void HDMI21_SCDC_Rx_Set_CedCountRst(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isReset)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __data0;

	/* Defence Code */
	if(!_p->initiated) return;

	HDMI21_LINE_DBG(276, "DBG[%d] : SCDC CED Counter Rst Pin[%s]\n", _p->port, isReset?"Reset High":"Reset Low");

	/* Read Data */
	__data  = _p->link_read(HDMI21_SNPS_REG_SCDC_CONFIG);
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		__data0 = _p->link_read(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG0);
	}
	else{
		__data0 = _p->link_read(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG0);
	}

	/* Set Bit field for selected condition */
	if(isReset) {
		__data |= ( HDMI21_SNPS_FIELD_SCDC_STANDBY);
	}
	else {
		__data &= (~HDMI21_SNPS_FIELD_SCDC_STANDBY);
	}

	/* Write Data */
	_p->link_write(HDMI21_SNPS_REG_SCDC_CONFIG, __data);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		_p->link_write(HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG0, __data0);
	}
	else {
		_p->link_write(HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG0, __data0);
	}

	return;
}

/*========================================================================================
 Static Function Implementation 
======================================================================================== */


