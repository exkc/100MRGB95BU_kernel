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
#include "hdmi21_rx_snps_pdec.h"
#include "hdmi21_rx_snps_pextract.h"
#include "hdmi21_rx_disland.h"
#include "hdmi21_rx_audio.h"
#include "os_util.h" /* jiffies_to_msec */

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
static UINT8 __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_DISLAND_DATA_T type);
static void __HDMI21_PDEC_Rx_Get_PktDataACR(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataGCP(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataACP(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataISRC1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataISRC2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataGAMUT(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataAMD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataVSI(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataAVI(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataSPD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataAIF(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataNTSCVBI(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataDRM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataGEN0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataGEN1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_PDEC_Rx_Get_PktDataEMD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

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
========================================================================================*/
void HDMI21_PDEC_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Set ACT N/CTS Override Free */
	HDMI21_PDEC_Rx_Set_AudioNCtsOverride(_p, false, 0, 0);
	/* Set AVMute Overrider Free */
	HDMI21_PDEC_Rx_Set_AVMuteOverride(_p, false, false, false);
	/* Use AVMute, make sure it is not disabled */
	HDMI21_PDEC_Rx_Set_AVMuteDisable(_p, false);
	/* Clear N/CTS Min/Max History */
	HDMI21_PDEC_Rx_Set_ResetAcrNCtsTrackingHistory(_p);

	/* Control PDEC snapshot */
	if(gHDMI21RxDevLinkControler[HDMI21__LINK_PDEC_USE_PKT_SNAPSHOT].value > 0) __data = 0x0;
	else __data = 0x1;
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_SNAPSHOT_BYP_CONTROL, __data);


	return;
}

void HDMI21_PDEC_Rx_Set_AudioCtsDiffThresHold(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 val)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __val = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_CONFIG);
	
	/* Calculate Value to be set */
	__data &= (~HDMI21_SNPS_FIELD_PKTDEC_ACR_DELTACTS_THR_QST);
	if(val <= 1) { __val = 0 ;}
	else if(val <= 2)	{ __val = 1; }
	else if(val <= 4)	{ __val = 2; }
	else if(val <= 8)	{ __val = 3; }
	else if(val <= 16)	{ __val = 4; }
	else if(val <= 32)	{ __val = 5; }
	else __val = 5;

	__val = __val << 4; 
	__val &= (HDMI21_SNPS_FIELD_PKTDEC_ACR_DELTACTS_THR_QST);
	
	/* Set Field */
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_ACR_CONFIG, __data);

	return;
}

void HDMI21_PDEC_Rx_Set_AudioNCtsOverride(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isOverride, UINT32 acr_n, UINT32 acr_cts)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* CTS : Set Register regardless of override mode */
	__data = (acr_cts & HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_OVR_VALUE);
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_ACR_CTS_CONFIG, __data);

	/* N : Set Register regardless of override mode */
	__data = (acr_n & HDMI21_SNPS_FIELD_PKTDEC_ACR_N_OVR_VALUE);
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_ACR_N_CONFIG, __data);

	/* Set Override value */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_CONFIG);

	if(isOverride) 	{ __data |= ( HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_N_OVR_EN); }
	else 			{ __data &= (~HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_N_OVR_EN); }


	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_ACR_CONFIG, __data);

	return;
}

void HDMI21_PDEC_Rx_Set_AVMuteOverride(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isOverride, bool setAVmute, bool clearAVmute)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __temp;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Set Set/Clear AVMute register value regardless of Override mode */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_AVMUTE_CONFIG);

	if(setAVmute)	{ __data |= ( HDMI21_SNPS_FIELD_PKTDEC_GCP_SET_AVMUTE_OVR_VALUE); }
	else			{ __data &= (~HDMI21_SNPS_FIELD_PKTDEC_GCP_SET_AVMUTE_OVR_VALUE); }

	if(clearAVmute) { __data |= ( HDMI21_SNPS_FIELD_PKTDEC_GCP_CLR_AVMUTE_OVR_VALUE); }
	else			{ __data &= (~HDMI21_SNPS_FIELD_PKTDEC_GCP_CLR_AVMUTE_OVR_VALUE); }

	if(isOverride)	{ __data |= ( HDMI21_SNPS_FIELD_PKTDEC_GCP_AVMUTE_OVR_EN); }
	else			{ __data &= (~HDMI21_SNPS_FIELD_PKTDEC_GCP_AVMUTE_OVR_EN); }

	if(gHDMI21RxDevLinkControler[HDMI21__LINK_PDEC_AVMUTE_AUTO_CLEAR_ENABLE].value > 0) {
		__temp = gHDMI21RxDevLinkControler[HDMI21__LINK_PDEC_AVMUTE_AUTO_CLEAR_TIME].value;
		__temp = __temp << 13;
		__temp &= (HDMI21_SNPS_FIELD_PKTDEC_AUTO_CLEAR_AVMUTE_SEL);

		__data |= (HDMI21_SNPS_FIELD_PKTDEC_AUTO_CLEAR_AVMUTE_EN);
		__data |= __temp;
	}
	else {
		__data &= (~HDMI21_SNPS_FIELD_PKTDEC_AUTO_CLEAR_AVMUTE_SEL);
		__data &= (~HDMI21_SNPS_FIELD_PKTDEC_AUTO_CLEAR_AVMUTE_EN);
	}

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_GCP_AVMUTE_CONFIG, __data);

	return;
}

void HDMI21_PDEC_Rx_Set_AVMuteDisable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isDisable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/*Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_AVMUTE_DIS_CONTROL);

	/* Set Value */
	if(isDisable )	{ __data |= ( HDMI21_SNPS_FIELD_PKTDEC_AVMUTE_DISABLE); }
	else			{ __data &= (~HDMI21_SNPS_FIELD_PKTDEC_AVMUTE_DISABLE); }


	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_AVMUTE_DIS_CONTROL, __data);

	return;
}

void HDMI21_PDEC_Rx_Set_ResetAcrNCtsTrackingHistory(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/*Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_MAXMIN_CLEAR);

	/* Set Bit */
	__data |= (HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_N_MAXMIN_CLR_P);

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_PKTDEC_ACR_MAXMIN_CLEAR, __data);

	return;
}

UINT32 HDMI21_PDEC_Rx_Get_AudioAcrCtsMin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 ret = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Get Value */
	ret = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_CTS_MIN_STATUS) & HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_MIN_STS;

	return ret;
}

UINT32 HDMI21_PDEC_Rx_Get_AudioAcrCtsMax(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 ret = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Get Value */
	ret = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_CTS_MAX_STATUS) & HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_MAX_STS;

	return ret;
}

UINT32 HDMI21_PDEC_Rx_Get_AudioAcrNMin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 ret = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Get Value */
	ret = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_N_MIN_STATUS) & HDMI21_SNPS_FIELD_PKTDEC_ACR_N_MIN_STS;

	return ret;
}

UINT32 HDMI21_PDEC_Rx_Get_AudioAcrNMax(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 ret = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Get Value */
	ret = _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_N_MAX_STATUS) & HDMI21_SNPS_FIELD_PKTDEC_ACR_N_MAX_STS;

	return ret;
}


bool HDMI21_PDEC_Rx_Get_AVMuteSetStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	bool ret = false;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_AVMUTE_STATUS);
	
	/* Read Field */
	if((__data & HDMI21_SNPS_FIELD_PKTDEC_GCP_SET_AVMUTE_STS ) != 0) ret = true;
	
	return ret;
}

bool HDMI21_PDEC_Rx_Get_AVMuteClearStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	bool ret = false;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_AVMUTE_STATUS);
	
	/* Read Field */
	if((__data & HDMI21_SNPS_FIELD_PKTDEC_GCP_CLR_AVMUTE_STS) != 0) ret = true;
	
	return ret;

}

bool HDMI21_PDEC_Rx_Get_VTemActiveStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	bool ret = false;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_STATUS);
	
	/* Read Field */
	if((__data & HDMI21_SNPS_FIELD_PKTDEC_EMD_VTEM_STS) != 0) ret = true;
	
	return ret;
}

bool HDMI21_PDEC_Rx_Get_CVTemActiveStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	bool ret = false;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_STATUS);
	
	/* Read Field */
	if((__data & HDMI21_SNPS_FIELD_PKTDEC_EMD_CVTEM_STS) != 0) ret = true;
	
	return ret;
}


void HDMI21_PDEC_Rx_Set_StorePktToHander(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_DISLAND_DATA_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Type Defence */
	if(type >= HDMI21_DISLAND_DATA_MAXNUM) {
		HDMI21_LINE_DBG(380, "DBG[%d] : Unknown PDEC store type[%d] recieved. Discard data\n", _p->port, type);
		return;
	}

	HDMI21_LINE_DBG(381, "DBG[%d] : PDEC store data type[%d]\n", _p->port, type);

	switch(type)
	{
		case HDMI21_DISLAND_DATA__ACR:
			__HDMI21_PDEC_Rx_Get_PktDataACR(_p);
			break;
		case HDMI21_DISLAND_DATA__GCP:
			__HDMI21_PDEC_Rx_Get_PktDataGCP(_p);
			break;
		case HDMI21_DISLAND_DATA__ACP:
			__HDMI21_PDEC_Rx_Get_PktDataACP(_p);
			break;
		case HDMI21_DISLAND_DATA__ISRC1:
			__HDMI21_PDEC_Rx_Get_PktDataISRC1(_p);
			break;
		case HDMI21_DISLAND_DATA__ISRC2:
			__HDMI21_PDEC_Rx_Get_PktDataISRC2(_p);
			break;
		case HDMI21_DISLAND_DATA__GAMUT:
			__HDMI21_PDEC_Rx_Get_PktDataGAMUT(_p);
			break;
		case HDMI21_DISLAND_DATA__AMD:
			__HDMI21_PDEC_Rx_Get_PktDataAMD(_p);
			break;
		case HDMI21_DISLAND_DATA__VSI:
			__HDMI21_PDEC_Rx_Get_PktDataVSI(_p);
			break;
		case HDMI21_DISLAND_DATA__AVI:
			__HDMI21_PDEC_Rx_Get_PktDataAVI(_p);
			break;
		case HDMI21_DISLAND_DATA__SPD:
			__HDMI21_PDEC_Rx_Get_PktDataSPD(_p);
			break;
		case HDMI21_DISLAND_DATA__AIF:
			__HDMI21_PDEC_Rx_Get_PktDataAIF(_p);
			break;
		case HDMI21_DISLAND_DATA__NTSCVBI:
			__HDMI21_PDEC_Rx_Get_PktDataNTSCVBI(_p);
			break;
		case HDMI21_DISLAND_DATA__DRM:
			__HDMI21_PDEC_Rx_Get_PktDataDRM(_p);
			break;
		case HDMI21_DISLAND_DATA__GEN0:
			__HDMI21_PDEC_Rx_Get_PktDataGEN0(_p);
			break;
		case HDMI21_DISLAND_DATA__GEN1:
			__HDMI21_PDEC_Rx_Get_PktDataGEN1(_p);
			break;
		case HDMI21_DISLAND_DATA__EMD:
			__HDMI21_PDEC_Rx_Get_PktDataEMD(_p);
			break;
		default:
			break;
	}

	return;
}


void HDMI21_PDEC_Rx_Get_PktDataVTEM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __pb3_0;
	UINT32 __pb6_4;
	UINT32 __md3_0;
	UINT32 __t;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->emp_vtemPacket[0]	= 0x7F;
	_p->emp_vtemPacket[1]	= 0xC0;
	_p->emp_vtemPacket[2]	= 0x0;

	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__pb3_0		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VTEM_PB3_0);
	__pb6_4		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VTEM_PB6_4);
	__md3_0		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VTEM_MD3_0);
	__t			= _p->link_read(0x13aC);

	HDMI21_LINE_DBG(476, "DBG[%d] : VTEM-->[0x%08x] [0x%08x] [0x%08x]  [0x%08x]\n", _p->port, __pb3_0, __pb6_4, __md3_0, __t);


	/* Filter for non VTEM packets : SNPS link triggers isr even though the EMP Parameters are not valid for VTEM */

	/* Copy Data to Dev Handler memory */	
	_p->emp_vtemPacket[3]	= (UINT8)((__pb3_0 & 0x000000FF));
	_p->emp_vtemPacket[4]	= (UINT8)((__pb3_0 & 0x0000FF00)>> 8);
	_p->emp_vtemPacket[5]	= (UINT8)((__pb3_0 & 0x00FF0000)>> 16);
	_p->emp_vtemPacket[6]	= (UINT8)((__pb3_0 & 0xFF000000)>> 24);

	_p->emp_vtemPacket[7]	= (UINT8)((__pb6_4 & 0x000000FF));
	_p->emp_vtemPacket[8]	= (UINT8)((__pb6_4 & 0x0000FF00)>> 8);
	_p->emp_vtemPacket[9]	= (UINT8)((__pb6_4 & 0x00FF0000)>> 16);

	_p->emp_vtemPacket[10]	= (UINT8)((__md3_0 & 0x000000FF));
	_p->emp_vtemPacket[11]	= (UINT8)((__md3_0 & 0x0000FF00)>> 8);
	_p->emp_vtemPacket[12]	= (UINT8)((__md3_0 & 0x00FF0000)>> 16);
	_p->emp_vtemPacket[13]	= (UINT8)((__md3_0 & 0xFF000000)>> 24);

	return;
}

void HDMI21_PDEC_Rx_Get_PktDataCVTEM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __pb3_0;
	UINT32 __pb6_4;
	UINT32 __md[34];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->emp_cvtemPacket[0]	= 0x7F;
	_p->emp_cvtemPacket[1]	= 0xC0;
	_p->emp_cvtemPacket[2]	= 0x0;

	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__pb3_0		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_PB3_0);
	__pb6_4		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_PB6_4);
	__md[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD3_0);
	__md[1]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD7_4); 	  
	__md[2]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD11_8);  
	__md[3]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD15_12); 
	__md[4]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD19_16); 
	__md[5]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD23_20); 
	__md[6]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD27_24); 
	__md[7]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD31_28); 
	__md[8]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD35_32); 
	__md[9]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD39_36); 
	__md[10]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD43_40); 
	__md[11]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD47_44); 
	__md[12]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD51_48); 
	__md[13]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD55_52); 
	__md[14]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD59_56);
	__md[15]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD63_60); 
	__md[16]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD67_64); 
	__md[17]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD71_68); 
	__md[18]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD75_72); 
	__md[19]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD79_76); 
	__md[20]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD83_80); 
	__md[21]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD87_84); 
	__md[22]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD91_88); 
	__md[23]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD95_92);
	__md[24]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD99_96); 
	__md[25]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD103_100);
	__md[26]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD107_104);
	__md[27]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD111_108);
	__md[28]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD115_112);
	__md[29]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD119_116);
	__md[30]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD123_120);
	__md[31]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD127_124);
	__md[32]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD131_128); 
	__md[33]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_CVTEM_MD135_132); 


	/* Copy Data to Dev Handler memory */	
	_p->emp_cvtemPacket[3]	= (UINT8)((__pb3_0 & 0x000000FF));
	_p->emp_cvtemPacket[4]	= (UINT8)((__pb3_0 & 0x0000FF00)>> 8);
	_p->emp_cvtemPacket[5]	= (UINT8)((__pb3_0 & 0x00FF0000)>> 16);
	_p->emp_cvtemPacket[6]	= (UINT8)((__pb3_0 & 0xFF000000)>> 24);

	_p->emp_cvtemPacket[7]	= (UINT8)((__pb6_4 & 0x000000FF));
	_p->emp_cvtemPacket[8]	= (UINT8)((__pb6_4 & 0x0000FF00)>> 8);
	_p->emp_cvtemPacket[9]	= (UINT8)((__pb6_4 & 0x00FF0000)>> 16);

	/* Copy Packet Data */
	memcpy((void *)&_p->emp_cvtemPacket[10], (void *)&__md, sizeof(UINT32) * 34);

	return;
}



/*========================================================================================
 Static Function Implementation 
======================================================================================== */
static void __HDMI21_PDEC_Rx_Get_PktDataACR(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__ACR;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACR_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataGCP(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__GCP;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GCP_PB27_24);

	/* Update Handler AVMute status */
	if(HDMI21_PDEC_Rx_Get_AVMuteSetStatus(_p)){
		if(_p->isMute == 0){
			HDMI20_VIDEO("Notice[%d] : Detected AVMute Set\n", _p->port);
			_p->isMute = true;	
			HDMI21_HAL_Rx_Set_AudioReset(_p->port);
		}
		 _p->avmute_on_time = jiffies_to_msecs(jiffies);
	}
	else if(HDMI21_PDEC_Rx_Get_AVMuteClearStatus(_p)){
		if(_p->isMute == true) {
			HDMI20_VIDEO("Notice[%d] : Detected AVMute Clear\n", _p->port);
		}
			
		HDMI21_LINE_DBG(665, "DBG[%d] : Detected AVMute Clear\n", _p->port);

		_p->isMute = false;
	}

	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataACP(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__ACP;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[4];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACP_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACP_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACP_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACP_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ACP_PB15_12);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 4);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataISRC1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__ISRC1;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[4];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC1_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC1_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC1_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC1_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC1_PB15_12);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 4);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataISRC2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__ISRC2;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[4];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC2_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC2_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC2_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC2_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_ISRC2_PB15_12);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 4);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataGAMUT(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__GAMUT;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GMD_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataAMD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__AMD;

	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[5];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AMD_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AMD_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AMD_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AMD_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AMD_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AMD_PB19_16);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 5);

	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataVSI(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__VSI;

	/* 2020/05/25 */
	UINT8	__vsifHead[3];

	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	UINT32 currentJiffies = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_VSIF_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	/* 2020/05/25 : Copy VSI to buffers */
	/* Get Header */
	__vsifHead[0] = _p->dataPacket[type][4];
	__vsifHead[1] = _p->dataPacket[type][5];
	__vsifHead[2] = _p->dataPacket[type][6];

	/* Get Current Time */
	currentJiffies = jiffies_to_msecs(jiffies);

	/* H14B VSIF */
	if((__vsifHead[0] == HDMI21_RX_VSI_TYPE_H14B_OUI_0) \
			&& (__vsifHead[1] == HDMI21_RX_VSI_TYPE_H14B_OUI_1) \
			&& (__vsifHead[2] == HDMI21_RX_VSI_TYPE_H14B_OUI_2)) {
		memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI], &_p->dataPacket[type], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);


		if((_p->dolbyVsiTimeStamp == 0) || \
				(_p->dolbyVsiTimeStamp > currentJiffies) || /* considering variable overflow  */ \
				((currentJiffies - _p->dolbyVsiTimeStamp) >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_DOVI_PACKET_MS_TIMEOUT].value )) {
			/* 2020/08/21 : Integrated Buffer for Dolby Detection(H14F + Dolby VSI) */
			memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOVI], &_p->dataPacket[type], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);

			/* 2020/11/25 : Timeout feature for DOVI */
			_p->doviTimeStamp = currentJiffies;
		}
	}
	else if((__vsifHead[0] == HDMI21_RX_VSI_TYPE_HF_OUI_0) \
			&& (__vsifHead[1] == HDMI21_RX_VSI_TYPE_HF_OUI_1) \
			&& (__vsifHead[2] == HDMI21_RX_VSI_TYPE_HF_OUI_2)) {
		memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__HFVSI], &_p->dataPacket[type], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
	}
	else if((__vsifHead[0] == HDMI21_RX_VSI_TYPE_DOLBY_OUI_0) \
			&& (__vsifHead[1] == HDMI21_RX_VSI_TYPE_DOLBY_OUI_1) \
			&& (__vsifHead[2] == HDMI21_RX_VSI_TYPE_DOLBY_OUI_2)) {
		memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOLBYVSI], &_p->dataPacket[type], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
		
		/* 2020/08/21 : Integrated Buffer for Dolby Detection(H14F + Dolby VSI) */
		memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOVI], &_p->dataPacket[type], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
	
		/* 2020/11/25 : Timeout feature for DOVI */
		_p->doviTimeStamp = currentJiffies;

		/* 2020/12/03 : Need to keep record of Dolby VSI time stamps */
		_p->dolbyVsiTimeStamp = currentJiffies;
	}

	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataAVI(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__AVI;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[4];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AVIIF_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AVIIF_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AVIIF_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AVIIF_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AVIIF_PB15_12);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 4);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataSPD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__SPD;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);

	/* AMD Free Sync Detection */
	if((HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSync((UINT8 *)&_p->dataPacket[type]) == RET_OK)&&(_p->isPhyLocked > 0)){
		if((_p->isFreeSyncMode == 0) || (_p->isFreeSyncMode == 2)){
			HDMI20_ISR_PRINT("ISR[%d] : Detected AMD Freesync SPD [On] ( %d~%d Hz)\n"\
					,_p->port, (int)_p->dataPacket[type][10], (int)_p->dataPacket[type][11]); 
		
			/* 2025/09/09 won.hur : Work around for SDOSTE-279 issue */
			if(gHDMI21RxDevLinkControler[HDMI21__LINK_WATCHDOG_VRR_VFREQ_WITH_MEASURE].value > 0 ) {
				if(HDMI21_HAL_Rx_Get_CheckVfreqBaseWithStableVfreq(_p) > 0) {
					HDMI20_ISR_PRINT("Notice [%d] : Vfreq changed due to VRR max rate difference with vfreq_real\n", _p->port);
					_p->stable_cnt = 0;
				}
			}
		}

		/* Update V-Front/V-Freq Base */
		_p->vfreq_min = (UINT32)_p->dataPacket[type][10];
		_p->vfreq_max = (UINT32)_p->dataPacket[type][11];
		
		_p->isFreeSyncMode = 1;
	}
	else if( (HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSyncV2((UINT8 *)&_p->dataPacket[type]) == RET_OK) && (_p->isPhyLocked > 0) ){
		if((_p->isFreeSyncMode == 0) ||  (_p->isFreeSyncMode == 2)){
			HDMI20_ISR_PRINT("ISR[%d] : Detected AMD Freesync V2 SPD [On] ( %d~%d Hz)\n"\
					,_p->port, (int)_p->dataPacket[type][10], (int)_p->dataPacket[type][11]); 

			/* 2025/09/09 won.hur : Work around for SDOSTE-279 issue */
			if(gHDMI21RxDevLinkControler[HDMI21__LINK_WATCHDOG_VRR_VFREQ_WITH_MEASURE].value > 0 ) {
				if(HDMI21_HAL_Rx_Get_CheckVfreqBaseWithStableVfreq(_p) > 0) {
					HDMI20_ISR_PRINT("Notice [%d] : Vfreq changed due to VRR max rate difference with vfreq_real\n", _p->port);
					_p->stable_cnt = 0;
				}
			}
		}
		
		/* Update V-Front/V-Freq Base */
		_p->vfreq_min = (UINT32)_p->dataPacket[type][10];
		_p->vfreq_max = (UINT32)_p->dataPacket[type][11];
		
		_p->isFreeSyncMode = 1;
	}
	else if( (HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSyncV3((UINT8 *)&_p->dataPacket[type]) == RET_OK) && (_p->isPhyLocked > 0) ){

		/* Update V-Front/V-Freq Base */
		_p->vfreq_min = (((UINT32)(_p->dataPacket[type][14] & 0x03) << 8) | (UINT32)_p->dataPacket[type][10]);
		_p->vfreq_max = (((UINT32)(_p->dataPacket[type][15] & 0x03) << 8) | (UINT32)_p->dataPacket[type][11]);

		if((_p->isFreeSyncMode == 0) ||  (_p->isFreeSyncMode == 2)){
			HDMI20_ISR_PRINT("ISR[%d] : Detected AMD Freesync V3 SPD [On] ( %d~%d Hz)\n"\
					,_p->port, (int)_p->vfreq_min, (int)_p->vfreq_max); 

			/* 2025/09/09 won.hur : Work around for SDOSTE-279 issue */
			if(gHDMI21RxDevLinkControler[HDMI21__LINK_WATCHDOG_VRR_VFREQ_WITH_MEASURE].value > 0 ) {
				if(HDMI21_HAL_Rx_Get_CheckVfreqBaseWithStableVfreq(_p) > 0) {
					HDMI20_ISR_PRINT("Notice [%d] : Vfreq changed due to VRR max rate difference with vfreq_real\n", _p->port);
					_p->stable_cnt = 0;
				}
			}
		}
		
		_p->isFreeSyncMode = 1;
	}
	else{
		if(_p->isFreeSyncMode == 1) {
			HDMI20_ISR_PRINT("ISR[%d] : Detected AMD Freesync SPD [Off]\n",_p->port); 
			_p->isFreeSyncMode = 0;
		}
	}


	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataAIF(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__AIF;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[2];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AUDIF_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AUDIF_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_AUDIF_PB7_4);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 2);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataNTSCVBI(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__NTSCVBI;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataDRM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__DRM;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_DRMIF_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataGEN0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__GEN0;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataGEN1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__GEN1;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);
	
	return;
}

static void __HDMI21_PDEC_Rx_Get_PktDataEMD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_DISLAND_DATA_T type = HDMI21_DISLAND_DATA__EMD;
	
	/* Import to read all each of the registers due to snap-shot mechanism */
	UINT32 __ph2_1;
	UINT32 __pb[7];
	int i;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Copy PKT Header Data */
	_p->dataPacket[type][0] = __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(_p, type);
	
	/* Reading the PH2_1 will initate snapshot, and reading the last coressponding register will release snapshot 
	 * Make sure to read all the registers first, then proceed data copy */
	__ph2_1		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PH2_1);	
	__pb[0]		= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB3_0);
	__pb[1] 	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB7_4);
	__pb[2]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB11_8);
	__pb[3]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB15_12);
	__pb[4]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB19_16);
	__pb[5]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB23_20);
	__pb[6]	= _p->link_read(HDMI21_SNPS_REG_PKTDEC_EMD_PB27_24);
	
	/* Copy Data to Dev Handler memory */	
	/* Copy Header */
	_p->dataPacket[type][1] = (UINT8)( __ph2_1 & 0x000000FF);
	_p->dataPacket[type][2] = (UINT8)((__ph2_1 & 0x0000FF00)>> 8);

	/* Copy Packet Data */
	memcpy((void *)&_p->dataPacket[type][3], (void *)&__pb, sizeof(UINT32) * 7);

	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1190){
		for(i=0;i<3;i++){
			HDMI20_DBG("[HB%02d] -  Hex[  0x%02x  ]\n", i,(UINT8)_p->dataPacket[HDMI21_DISLAND_DATA__EMD][i]);
		}
		for(i=3;i<HDMI21_MAX_DATA_PACKET_LENGTH;i++){
			HDMI20_DBG("[PB%02d] -  Hex[  0x%02x  ]\n", i,(UINT8)_p->dataPacket[HDMI21_DISLAND_DATA__EMD][i]);
		}
	}


	return;
}




static UINT8 __HDMI21_PDEC_Rx_Get_ConvertPktEnumToValue(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_DISLAND_DATA_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	if(_p == NULL) return 0xFF;

	switch(type)
	{
		case HDMI21_DISLAND_DATA__ACR:
			return 0x01;
		case HDMI21_DISLAND_DATA__GCP:
			return 0x03;
		case HDMI21_DISLAND_DATA__ACP:
			return 0x04;
		case HDMI21_DISLAND_DATA__ISRC1:
			return 0x05;
		case HDMI21_DISLAND_DATA__ISRC2:
			return 0x06;
		case HDMI21_DISLAND_DATA__GAMUT:
			return 0x0A;
		case HDMI21_DISLAND_DATA__AMD:
			return 0x0D;
		case HDMI21_DISLAND_DATA__VSI:
			return 0x81;
		case HDMI21_DISLAND_DATA__AVI:
			return 0x82;
		case HDMI21_DISLAND_DATA__SPD:
			return 0x83;
		case HDMI21_DISLAND_DATA__AIF:
			return 0x84;
		case HDMI21_DISLAND_DATA__NTSCVBI:
			return 0x86;
		case HDMI21_DISLAND_DATA__DRM:
			return 0x87;
		case HDMI21_DISLAND_DATA__GEN0:
			return HDMI21_PEXTRACT_Rx_Get_GenPKTType(_p, 0);
		case HDMI21_DISLAND_DATA__GEN1:
			return HDMI21_PEXTRACT_Rx_Get_GenPKTType(_p, 1);
		case HDMI21_DISLAND_DATA__EMD:
			return 0x7F;
		default :
			return 0xFF;
	}
}
