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
#include "hdmi21_rx_snps_pextract.h"

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
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
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



/*========================================================================================
 Static Function Implementation 
======================================================================================== */
void HDMI21_PEXTRACT_Rx_Set_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* BCH ERROR CONFIG : Enable both Audio/Non-Audio BCH Error Correction */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTEX_BCH_ERRCORR_CONFIG);
	
	__data |= (HDMI21_SNPS_FIELD_BCH_AUD_ERRCORR_EN_QST);
	__data |= (HDMI21_SNPS_FIELD_BCH_ERRCORR_EN_QST);
	
	_p->link_write(HDMI21_SNPS_REG_PKTEX_BCH_ERRCORR_CONFIG, __data);
	HDMI21_LINE_DBG(85, "DBG[%d] : BCH Error Correction Config set as [0x%08x]\n", _p->port, __data);



	/* BCH ERROR FILTERING CONFIG : When configured high, the individual filter register
	 * 								fields discard packets where the BCH Error Correction Code is able
	 * 								to detect errors. Filtering is not applied over packets that have 
	 * 								been corrected by the Error Correction Code mechanism. */
	/* Set Every Packet BCH Filter ON */	
	__data = _p->link_read(HDMI21_SNPS_REG_PKTEX_BCH_ERRFILT_CONFIG);
	
	__data |= (HDMI21_SNPS_FIELD_BCHSP_GENPKT1_ERRFILT_QST);	
	__data |= (HDMI21_SNPS_FIELD_BCHSP_GENPKT0_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_EMD_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_DRMIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_NTSCVBIIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_AUDIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_SRCPDIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_AVIIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_VSIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_AMD_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_GMD_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_ISRC_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_ACP_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_GCP_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHSP_ACR_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_BCHPH_ERRFILT_QST);
	
	_p->link_write(HDMI21_SNPS_REG_PKTEX_BCH_ERRFILT_CONFIG, __data);
	HDMI21_LINE_DBG(85, "DBG[%d] : BCH Error Filter Config set as [0x%08x]\n", _p->port, __data);



	/* CHECKSUM ERROR FILTER FOR INFOFRAMES */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTEX_CHKSUM_ERRFILT_CONFIG);

	__data |= (HDMI21_SNPS_FIELD_CHKSUM_GENPKT1_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_GENPKT0_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_DRMIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_NTSCVBIIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_AUDIF_ERRFILT_QST); 
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_SRCPDIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_AVIIF_ERRFILT_QST);
	__data |= (HDMI21_SNPS_FIELD_CHKSUM_VSIF_ERRFILT_QST);

	_p->link_write(HDMI21_SNPS_REG_PKTEX_CHKSUM_ERRFILT_CONFIG, __data);
	HDMI21_LINE_DBG(85, "DBG[%d] : CheckSum Error Filter Config set as [0x%08x]\n", _p->port, __data);

	return;
}


void HDMI21_PEXTRACT_Rx_Set_GenPKTType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int type, UINT8 header)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __reg = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	HDMI20_INFO("INFO[%d] : Gen Type[%d] set to [0x%02x]\n", _p->port, type, header);

	/* Get current reg value */
	__reg = _p->link_read(HDMI21_SNPS_REG_GENPKT_TYPE_CONFIG);

	__data  = (UINT32)header;
	__data &= 0x000000FF;

	/* Set Value */
	if(type == 0) {
		__reg &= (~HDMI21_SNPS_FIELD_GENPKT0_TYPE);
		__reg |= __data;
	}
	else {
		__data  = __data<<16;
		__data &= HDMI21_SNPS_FIELD_GENPKT1_TYPE;
	
		__reg &= (~HDMI21_SNPS_FIELD_GENPKT1_TYPE);
		__reg |= __data;
	}

	_p->link_write(HDMI21_SNPS_REG_GENPKT_TYPE_CONFIG, __reg);
	
	return;
}

void HDMI21_PEXTRACT_Rx_Set_UpiOutType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	HDMI20_INFO("INFO[%d] : UPI Out set to [0x%08x]\n", _p->port, type);

	_p->link_write(HDMI21_SNPS_REG_PKTEX_UPI_CONFIG, type);

	return;
}

int	HDMI21_PEXTRACT_Rx_Get_AccumBCHErrCnt(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isAudio)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	int ret = -1;

	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;

		/* Get Data */
		__data = _p->link_read(HDMI21_SNPS_REG_PKTEX_BCHERR_ACC_STATUS);

		if(isAudio) {
			__data &= HDMI21_SNPS_FIELD_BCHAUDERR_ACC_STS;
			__data = __data >> 16;
		}
		else{
			__data &= HDMI21_SNPS_FIELD_BCHERR_ACC_STS;
		}

		__data &= 0x0000FFFF;

		ret = __data;
	} while(0);

	return ret;
}
int HDMI21_PEXTRACT_Rx_Get_FieldCntError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isAudio)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	int ret = -1;

	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;

		/* Get Data */
		__data = _p->link_read(HDMI21_SNPS_REG_PKTEX_FIELDS_BCHERR_STATUS);

		if(isAudio) {
			__data &= HDMI21_SNPS_FIELD_FIELDS_SINCE_BCHAUDERR_STS;
			__data = __data >> 16;
		}
		else{
			__data &= HDMI21_SNPS_FIELD_FIELDS_SINCE_BCHERR_STS;
		}

		__data &= 0x0000FFFF;

		ret = __data;
	} while(0);

	return ret;
}

UINT8 HDMI21_PEXTRACT_Rx_Get_GenPKTType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT8 ret = 0xFF;
	UINT32 __data;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Get current reg value */
	__data = _p->link_read(HDMI21_SNPS_REG_GENPKT_TYPE_CONFIG);

	/* Set Value */
	if(type == 0) {
		__data &= HDMI21_SNPS_FIELD_GENPKT1_TYPE;
	}
	else {
		__data &= HDMI21_SNPS_FIELD_GENPKT1_TYPE;
		__data = __data >>16;
	}

	ret = (UINT8)__data;

	return ret;
}
