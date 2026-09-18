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
#include "hdmi21_rx_snps_vpgen.h"

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
static char *vpgen_type_to_str(HDMI21_RX_VPGEN_CONN_TYPE_T type);
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
void HDMI21_VPROC_Rx_Set_VPGenConnection(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_RX_VPGEN_CONN_TYPE_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __reg;
	/* Defence Code */
	if(!_p->initiated) return;

	HDMI21_LINE_DBG(88, "DBG[%d] : Set VPGEN connection[%s]\n", _p->port, vpgen_type_to_str(type));	

	__reg  = _p->link_read(HDMI21_SNPS_REG_VPG_CONFIG0);
	__reg &= (~HDMI21_SNPS_FIELD_VPG_CONNECTION_SEL_QST);
	
	switch(type)
	{
		case HDMI21_RX_VPGEN_CONN_DISCONNECT:
			__data = 0;
			break;
		case HDMI21_RX_VPGEN_CONN_HDCP:
			__data = 1;
			break;
		case HDMI21_RX_VPGEN_CONN_VPROC:
			__data = 2;
			break;
		case HDMI21_RX_VPGEN_CONN_PVO:
			__data = 3;
			break;
		default :
			__data = 0;	
			break;
	}

	__data  = __data << 28;
	__data &= (HDMI21_SNPS_FIELD_VPG_CONNECTION_SEL_QST);

	__data |= __reg;

	if(type == HDMI21_RX_VPGEN_CONN_DISCONNECT) {
		__data &= (~0x1);
	}

	_p->link_write(HDMI21_SNPS_REG_VPG_CONFIG0, __data);

	return;
}

HDMI21_RX_VPGEN_CONN_TYPE_T HDMI21_VPROC_Rx_Get_VPGenConnection(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_RX_VPGEN_CONN_TYPE_T ret;
	
	UINT32 __reg;

	/* Defence Code */
	if(!_p->initiated) return HDMI21_RX_VPGEN_CONN_MAXNUM;


	__reg  = _p->link_read(HDMI21_SNPS_REG_VPG_CONFIG0);
	__reg  &= (HDMI21_SNPS_FIELD_VPG_CONNECTION_SEL_QST);
	
	__reg = __reg >> 28;

	switch(__reg)
	{
		case HDMI21_RX_VPGEN_CONN_DISCONNECT:
			ret = HDMI21_RX_VPGEN_CONN_DISCONNECT;
			break;
		case HDMI21_RX_VPGEN_CONN_HDCP:
			ret = HDMI21_RX_VPGEN_CONN_HDCP;
			break;
		case HDMI21_RX_VPGEN_CONN_VPROC:
			ret = HDMI21_RX_VPGEN_CONN_VPROC;
			break;
		case HDMI21_RX_VPGEN_CONN_PVO:
			ret = HDMI21_RX_VPGEN_CONN_PVO;
			break;
		default :
			ret = -1;
			break;
	}

	return ret;
}


/*========================================================================================
 Static Function Implementation 
 ======================================================================================== */
static char *vpgen_type_to_str(HDMI21_RX_VPGEN_CONN_TYPE_T type)
{
	switch(type)
	{
		case HDMI21_RX_VPGEN_CONN_DISCONNECT:
		return "Disconnect";
		case HDMI21_RX_VPGEN_CONN_HDCP:
		return "HDCP";
		case HDMI21_RX_VPGEN_CONN_VPROC:
		return "VPROC";
		case HDMI21_RX_VPGEN_CONN_PVO:
		return "PVO";
		default :
		return "Unknown";
	}

}



