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
#include "hdmi21_rx_snps_vproc.h"
#include "hdmi21_rx_dsc.h"
#include "hdmi21_rx_misc.h"

/* LX_CHIP_REV() */
#include "os_util.h"
#include "sys_regs.h"
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
static int __HDMI21_VPROC_Rx_Get_SyncGenSetForDSC(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 *pHsyncHFront, UINT32 *pHactiveHback, UINT32 *pVsyncVFront, UINT32 *pVback, UINT32 vicOverRide);
static int __HDMI21_VPROC_Rx_Get_SyncValforSyncGen1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 *pHsyncHFront, UINT32 *pHactiveHback, UINT32 *pVsyncVFront, UINT32 *pVback);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

extern HDMI21_DSC_VIC_LIST_T gHdmi21DscVicList[];
extern HDMI21_DSC_VIC_H_PARAM_T gHdmi21DscHParam_Frl12g[];
extern HDMI21_DSC_VIC_H_PARAM_T gHdmi21DscHParam_Frl10g[];
extern HDMI21_DSC_VIC_H_PARAM_T gHdmi21DscHParam_Frl8g[];
extern HDMI21_DSC_VIC_H_PARAM_T gHdmi21DscHParam_Frl6g[];
extern HDMI21_DSC_VIC_H_PARAM_T gHdmi21DscHParam_Frl3g[];

extern HDMI21_MISC_VIC_TABLE_T gHdmi21CtaTable[HDMI21_MISC_CTA861G_IDX_CNT];
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
void HDMI21_VPROC_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	/* Defence Code */
	if(!_p->initiated) return;


	/* Sync values when generating video sync from FRL */
	/* H values : Hsync & Hfront */
	if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L) {
		__data  = gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HSYNC_3L].value;
		__data &= (0x0000FFFF); __data = __data << 16; 
		__data &= (HDMI21_SNPS_FIELD_VPROC_HSYNC_WIDTH_QST);
		__data |= gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HFRONT_3L].value;
	}
	else {
		__data  = gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HSYNC_4L].value;
		__data &= (0x0000FFFF); __data = __data << 16; 
		__data &= (HDMI21_SNPS_FIELD_VPROC_HSYNC_WIDTH_QST);
		__data |= gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HFRONT_4L].value;
	}
	_p->link_write(	HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, __data);

	/* V values : Vsync & Vfront */
	__data  = gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_VSYNC].value;
	__data &= (0x0000FFFF); __data = __data << 16; 
	__data &= (HDMI21_SNPS_FIELD_VPROC_VSYNC_WIDTH_QST);
	__data |= gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_VFRONT].value;
	_p->link_write(	HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, __data);


	/* 2020/06/04 : VRR on FRL issue fix */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_FVA_VRR_CONFIG,  0x00000001);


	/* Sync Gen default value */
	HDMI21_VPROC_Rx_Set_SyncGenSel(_p, 0);

	HDMI21_VPROC_Rx_Set_LinkBypassForDSC(_p, 0, 1);

	/* Default PP mode */
	HDMI21_VPROC_Rx_Set_OverRidePixelPackingPhase(_p, 0, HDMI21_RX_VPROC_PP_PHASE_4);

	return;
}

void HDMI21_VPROC_Rx_Set_OverRidePixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isOverRide, HDMI21_RX_VPROC_PP_PHASE_TYPE_T pP)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __phase;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Read Register */
	__data  = _p->link_read(HDMI21_SNPS_REG_VIDEO_PP_CONFIG);
	
	/* Clear Existing Fields */
	__data &= (~HDMI21_SNPS_FIELD_VPROC_PP_OVR_VALUE);
	__data &= (~HDMI21_SNPS_FIELD_VPROC_PP_OVR_EN);

	if(isOverRide) {
		__data |= (HDMI21_SNPS_FIELD_VPROC_PP_OVR_EN);
		if((pP >= HDMI21_RX_VPROC_PP_MAXNUM)|| (pP < 0)) {
			__phase = HDMI21_RX_VPROC_PP_PHASE_4;
		}
		else {
			__phase = pP;
		}

		/* Bit shift as this is for [7:4] */
		__phase = __phase << 4; 
		__phase &= 0xF0;

		__data |= __phase;
	}

	/* Write register */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_PP_CONFIG, __data);

	return;
}

int HDMI21_VPROC_Rx_Get_OverRidePixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	int ret = 0;

	/* Defence Code */
	if(!_p->initiated) return ret;

	/* Read Register */
	__data  = _p->link_read(HDMI21_SNPS_REG_VIDEO_PP_CONFIG);

	/* Read Field */
	__data &= (HDMI21_SNPS_FIELD_VPROC_PP_OVR_EN);

	if(__data != 0) ret = 1;
	else ret = 0;

	return ret;
}

HDMI21_RX_VPROC_CD_TYPE_T HDMI21_VPROC_Rx_Get_ColorDepth(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_RX_VPROC_CD_TYPE_T ret = HDMI21_RX_VPROC_CD_NONE;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return ret;

	/* Read Register */
	__data  = _p->link_read(HDMI21_SNPS_REG_VIDEO_STATUS);
	__data &= (HDMI21_SNPS_FIELD_VPROC_CD_CURRENT);

	/* Convert data to type */
	ret = (HDMI21_RX_VPROC_CD_TYPE_T)__data;

	return ret;
}

HDMI21_RX_VPROC_PP_PHASE_TYPE_T HDMI21_VPROC_Rx_Get_PixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_RX_VPROC_PP_PHASE_TYPE_T ret = HDMI21_RX_VPROC_PP_PHASE_4;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return ret;

	/* Read Register */
	__data  = _p->link_read(HDMI21_SNPS_REG_VIDEO_STATUS);
	__data &= (HDMI21_SNPS_FIELD_VPROC_PP_CURRENT);
	__data = __data >> 4;

	if((__data == 0) || (__data == 4)) 	ret = HDMI21_RX_VPROC_PP_PHASE_4;
	else if(__data == 1) 				ret = HDMI21_RX_VPROC_PP_PHASE_1;
	else if(__data == 2)				ret = HDMI21_RX_VPROC_PP_PHASE_2;	
	else if(__data == 3)				ret = HDMI21_RX_VPROC_PP_PHASE_3;	
	else								ret = HDMI21_RX_VPROC_PP_PHASE_4;
	
	return ret;
}

void HDMI21_VPROC_Rx_Set_MuteColor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isYCbCr444or422)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data0;
	UINT32 __data1;

	/* Defence Code */
	if(!_p->initiated) return;


	/* Set Bit Field */
	if(isYCbCr444or422)	{ 
		/* YCbCr 4:4:4 and YCbCr 4:2:2 */
		/* O20B0 : on 4:2:2 this should be set to 0x0 */
		if((_p->hwVideo.video_format == 1)|| (_p->hwVideo.video_format == 3)) {
			__data0 = 0x0; 
		}
		else {
			__data0 = 0x8000;
		}
		__data0 &= ( HDMI21_SNPS_FIELD_VPROC_VMUTE_VALUE_HIGH);

		__data1 = 0x8000;
	}
	else { 
		/* RGB and YCbCr4:2:0 */
		__data0 = 0x0; 
		__data0 &= ( HDMI21_SNPS_FIELD_VPROC_VMUTE_VALUE_HIGH);
	
		__data1 = 0x0;
	}

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_MUTE_VALUE_H, __data0);
	_p->link_write(HDMI21_SNPS_REG_VIDEO_MUTE_VALUE_L, __data1);

	return;
}

void HDMI21_VPROC_Rx_Set_SyncGenSel(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	UINT32 __val;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG1);

	/* Set Bit Field */
	if(value >= 3) __val = 3;
	else if(value <= 0) __val = 0;
	else __val = (UINT32)value;

	__val  = __val << 28;
	
	/* Clear other bits */
	__data &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_SEL);
	__data |= __val;

	/* 2020/09/15 : Shim Wook Jin/Kim Jin Hyuk : set BACK_FIX_EN to 1 when FRL Sync Gen is set to 1 */
	if(value == 1) {
		__data |= ( HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_BACK_FIX_EN);
		if((_p->isDSC == 0) \
				&& (_p->hwVideo.video_format == 3)\
				&& (_p->hwVideo.hactive <= gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VBCONST_HACT].value)) {
			__data &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);
		}
		else {
			__data |= ( HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);
		}

		if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VBCONST_ZERO_FORCE].value > 0) {
			__data &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);
		}

		/* 2021/07/23 : BACK_FIX_EN should be zero for O22, due to VBACK shaking issue */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			__data &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_BACK_FIX_EN);
		}
	}
	else {
		__data &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_BACK_FIX_EN);
		if(( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )&&(value ==2)){
			
			__data |= (HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);
		}
		else{
			__data &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);
		}
	}

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_CONFIG1, __data);


	return;
}

int HDMI21_VPROC_Rx_Get_SyncGenSel(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	UINT32 __data;

	do{
		/* Defence Code */
		if(!_p->initiated) {
			break;
		}

		/* Read Register */
		__data = _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG1);

		/* Mask */
		__data &= (HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_SEL);
		
		/* Shift */
		__data = (__data >> 28);

		ret = (int)__data;
	} while(0);

	return ret;
}


void HDMI21_VPROC_Rx_Set_Mute(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG1);

	/* Set Bit Field */
	if(isSet)	{ __data |= ( HDMI21_SNPS_FIELD_VPROC_VMUTE_EN);  }
	else 		{ __data &= (~HDMI21_SNPS_FIELD_VPROC_VMUTE_EN); }

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_CONFIG1, __data);
	
	return;
}


/* Return 1 on mute status */
int HDMI21_VPROC_Rx_Get_IsMute(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;

	/* Defence Code */
	if(!_p->initiated) return ret;

	/* If Mute, return 1 */
	if( _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG1) & HDMI21_SNPS_FIELD_VPROC_VMUTE_EN){
		ret = 1;
	}

	return ret;
}

/* Mode : 0 for 24bit compressed, Mode : Else for 48 bit compressed */
void HDMI21_VPROC_Rx_Set_LinkBypassForDSC(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet, int mode)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __regValue = 0;
	UINT32 hSyncHfront = 0;
	UINT32 hActiveHback = 0;
	UINT32 vSyncVfront = 0;
	UINT32 vBack = 0;
	UINT32 __data = 0;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Get Reg Value */
	__regValue = _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG1);

	/* Data set up for SYNCGEN_CONFIG1 revert : 2020/06/04*/
	if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L){
		__data  = gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HSYNC_3L].value;
		__data &= (0x0000FFFF); __data = __data << 16; 
		__data &= (HDMI21_SNPS_FIELD_VPROC_HSYNC_WIDTH_QST);
		__data |= gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HFRONT_3L].value;
	}
	else {
		__data  = gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HSYNC_4L].value;
		__data &= (0x0000FFFF); __data = __data << 16; 
		__data &= (HDMI21_SNPS_FIELD_VPROC_HSYNC_WIDTH_QST);
		__data |= gHDMI21RxDevLinkControler[HDMI21__LINK_VPROC_FRLSYNC_HFRONT_4L].value;
	}

	/* Set bit field */
	if(isSet) {
		__regValue |= (HDMI21_SNPS_FIELD_VPROC_BYPASS);
		__regValue |= (HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);

		if(mode) {
			__regValue |= (HDMI21_SNPS_FIELD_VPROC_BYPASS_48B_MODE);

			if(__HDMI21_VPROC_Rx_Get_SyncGenSetForDSC(_p, &hSyncHfront, &hActiveHback, &vSyncVfront, &vBack, 0) == RET_OK) {
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, hSyncHfront); /* VPROC : FRL SYNC GEN FOR HSYNC/HFRONT */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, vSyncVfront); /* VPROC : FRL SYNC GEN FOR VSYNC/VFRONT */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, hActiveHback); /* VPROC : FRL SYNC GEN FOR HACTIVE/HBACK */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, vBack); /* VPROC : VBACK adjustment */
			}
			else {
				/* Default Sync Setting for DSC when the signal is not supported by HDMI2.1 spec table 7-35/7-36 */
				if((_p->pps.pic_width >= 7000 ) && ( _p->pps.pic_height >= 4000) ){
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00b40850); /* VPROC : FRL SYNC GEN FOR HSYNC/HFRONT */
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00140010); /* VPROC : FRL SYNC GEN FOR VSYNC/VFRONT */
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x00000430); /* VPROC : FRL SYNC GEN FOR HACTIVE/HBACK */
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, 0x0008002C); /* VPROC : VBACK adjustment */
				}
				else {
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00e8057c); //hsync width / hfront width
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x000a0008); //vsync width / vfront width 16
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x000002bc); //hactive width / hback width 
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, 0x00080048); //vback width 44
				}
			}

			//QEVENTTF-7000 : all hwVideo.vfreq has been changed to video.vfreq
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){

				if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value > 0) {
					if(_p->hwVideo.vfreq >= 130) {
						/* Syncgen2 setting on O24 144khz DSC */
						HDMI20_INFO("DBG[%d] : Detected Over 130Hz on DSC\n", _p->port);	

						__regValue &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_SEL);
						__regValue |= HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN2_SEL;
						_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00000000); //hsync width / hfront width
						_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00000000); //vsync width / vfront width 					
					}
				}
				else {
					if(_p->video.vfreq >= 130) {
						/* Syncgen2 setting on O24 144khz DSC */
						HDMI20_INFO("DBG[%d] : Detected Over 130Hz on DSC\n", _p->port);	

						__regValue &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_SEL);
						__regValue |= HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN2_SEL;
						_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00000000); //hsync width / hfront width
						_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00000000); //vsync width / vfront width 					
					}
				}
			}else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				if(_p->video.vfreq >= 130) {
					/* Syncgen2 setting on O24 144khz DSC */
					HDMI20_INFO("DBG[%d] : Detected Over 130Hz on DSC\n", _p->port);	

					__regValue &= (~HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_SEL);
					__regValue |= HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN2_SEL;
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00000000); //hsync width / hfront width
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00000000); //vsync width / vfront width 					
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x00000100); 
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, 0x0008000A); 
				} 
			}
		}
		else {

			__regValue &= (~HDMI21_SNPS_FIELD_VPROC_BYPASS_48B_MODE);
			/* Restore Sync Gen Setting */

			if((HDMI21_VPROC_Rx_Get_SyncGenSel(_p) == 1) \
					&& (__HDMI21_VPROC_Rx_Get_SyncValforSyncGen1(_p, &hSyncHfront, &hActiveHback, &vSyncVfront, &vBack) == RET_OK)\
					&& (_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)) {
				_p->link_write(	HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, __data);
		
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, hSyncHfront); /* VPROC : FRL SYNC GEN FOR HSYNC/HFRONT */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, vSyncVfront); /* VPROC : FRL SYNC GEN FOR VSYNC/VFRONT */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, hActiveHback); /* VPROC : FRL SYNC GEN FOR HACTIVE/HBACK */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, vBack); /* VPROC : VBACK adjustment */
			}
			else if((HDMI21_VPROC_Rx_Get_SyncGenSel(_p) == 2) \
					&& (__HDMI21_VPROC_Rx_Get_SyncValforSyncGen1(_p, &hSyncHfront, &hActiveHback, &vSyncVfront, &vBack) == RET_OK)\
					&& (_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)){
				_p->link_write(	HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, __data);
		
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, hSyncHfront); /* VPROC : FRL SYNC GEN FOR HSYNC/HFRONT */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, vSyncVfront); /* VPROC : FRL SYNC GEN FOR VSYNC/VFRONT */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, hActiveHback); /* VPROC : FRL SYNC GEN FOR HACTIVE/HBACK */
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, vBack); /* VPROC : VBACK adjustment */
			}
			else {
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
				__regValue |= HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN2_SEL;
					/*  Mail From YBIN HONG 
					 *  ADDR = 0xc8d30428  WDATA = 0x28000000
	   					ADDR = 0xc8d30440  WDATA = 0x00200000
	   					ADDR = 0xc8d30444  WDATA = 0x00000000
	   					ADDR = 0xc8d30448  WDATA = 0x00000001
	  					ADDR = 0xc8d3044c  WDATA = 0x00000000 */

					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00200000);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00000000);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_FVA_VRR_CONFIG,  0x00000001);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x00000000);
				}
				else {
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, __data);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00020002);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x00000000);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000);
					_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, 0x00080000);
				}
			}
		}
	}
	else {
		__regValue &= (~HDMI21_SNPS_FIELD_VPROC_BYPASS);
		__regValue &= (~HDMI21_SNPS_FIELD_VPROC_BYPASS_48B_MODE);
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(HDMI21_VPROC_Rx_Get_SyncGenSel(_p) == 2){
				__regValue |= (HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST);
			}
		}

		/* Restore Sync Gen Setting */
		if((HDMI21_VPROC_Rx_Get_SyncGenSel(_p) == 1) && (__HDMI21_VPROC_Rx_Get_SyncValforSyncGen1(_p, &hSyncHfront, &hActiveHback, &vSyncVfront, &vBack) == RET_OK)) {
			_p->link_write(	HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, __data);

			_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, hSyncHfront); /* VPROC : FRL SYNC GEN FOR HSYNC/HFRONT */
			_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, vSyncVfront); /* VPROC : FRL SYNC GEN FOR VSYNC/VFRONT */
			_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, hActiveHback); /* VPROC : FRL SYNC GEN FOR HACTIVE/HBACK */
			_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
			_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, vBack); /* VPROC : VBACK adjustment */
		}
		else {
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			__regValue |= HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN2_SEL;
				/*  Mail From YBIN HONG 
				 *  ADDR = 0xc8d30428  WDATA = 0x28000000
   					ADDR = 0xc8d30440  WDATA = 0x00200000
   					ADDR = 0xc8d30444  WDATA = 0x00000000
   					ADDR = 0xc8d30448  WDATA = 0x00000001
  					ADDR = 0xc8d3044c  WDATA = 0x00000000 */

				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, 0x00200000);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00000000);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_FVA_VRR_CONFIG,  0x00000001);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x00000000);
			}
			else {
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, __data);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, 0x00020002);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, 0x00000000);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000);
				_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, 0x00080000);
			}
		}
	}

	/* Write Reg */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_CONFIG1, __regValue);

	if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVRRIDE_EN].value > 0) {
		_p->link_write(HDMI21_SNPS_REG_VIDEO_CONFIG1, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVR_VIDCONFIG1].value);
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG1].value);
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG2].value);
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG3].value);
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG4].value);
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG5].value);
	}

	return;
}

void HDMI21_VPROC_Rx_Set_RGB444OverRide(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isOverRide)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Get Reg Value */
	__data = _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG2);

	/* Set bit field */
	if(isOverRide) {
		__data &= (~HDMI21_SNPS_FIELD_VPROC_FMT_OVR_VALUE);	/* [6:4]=0 : RGB 4:4:4 override */
		__data |= (HDMI21_SNPS_FIELD_VPROC_FMT_OVR_EN);

	}
	else {
		__data &= (~HDMI21_SNPS_FIELD_VPROC_FMT_OVR_EN);
	}

	/* Write Reg */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_CONFIG2, __data);
	return;
}


void HDMI21_VPROC_Rx_Set_HVSyncPolarity(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isOverRide, bool hNegative, bool  vNegative)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg = 0x0;


	do{
		/* Defence Code */
		if(!_p->initiated) break;

		HDMI21_LINE_DBG(557, "DBG[%d] : Sync Polarity Set[%s] -> H[%s] V[%s]\n",\
				_p->port,isOverRide?"Override":"Auto", hNegative?"Negative":"Positive", vNegative?"Negative":"Positive");

		__reg = _p->link_read(HDMI21_SNPS_REG_VIDEO_CONFIG2);

		if(isOverRide)	{	
			__reg |= ( HDMI21_SNPS_FIELD_VPROC_HSYNC_POL_OVR_EN);
			__reg |= ( HDMI21_SNPS_FIELD_VPROC_VSYNC_POL_OVR_EN);
		}
		else			{
			__reg &= (~HDMI21_SNPS_FIELD_VPROC_HSYNC_POL_OVR_EN);
			__reg &= (~HDMI21_SNPS_FIELD_VPROC_VSYNC_POL_OVR_EN);
		}

		if(hNegative)	{	__reg &= (~HDMI21_SNPS_FIELD_VPROC_HSYNC_POL_OVR_VAL);	}
		else			{	__reg |= ( HDMI21_SNPS_FIELD_VPROC_HSYNC_POL_OVR_VAL);	}

		if(vNegative)	{	__reg &= (~HDMI21_SNPS_FIELD_VPROC_VSYNC_POL_OVR_VAL);	}
		else			{	__reg |= ( HDMI21_SNPS_FIELD_VPROC_VSYNC_POL_OVR_VAL);	}

		/* Write Register */
		_p->link_write(HDMI21_SNPS_REG_VIDEO_CONFIG2, __reg);
	}while(0);

	return;
}

void HDMI21_VPROC_Rx_Set_OverRideColorDepth(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isOverRide, HDMI21_RX_VPROC_CD_TYPE_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __regValue = 0;
	UINT32 __data = 0;

	/* Defence Code */
	if(!_p->initiated) return;

	HDMI20_VIDEO("VPROC[%d] : Set GCP ColorDepth Override [%s]. Type[%d]\n",_p->port, isOverRide?"OverRide":"Auto", (int)type);

	/* Get Reg Value */
	__regValue =  _p->link_read(HDMI21_SNPS_REG_VIDEO_CD_CONFIG);

	/* Set clear for the bits we wish to control */
	__regValue &= (~HDMI21_SNPS_FIELD_VPROC_CD_OVR_EN);
	__regValue &= (~HDMI21_SNPS_FIELD_VPROC_CD_OVR_VALUE);
	
	/* Set bit field */
	if(isOverRide) {
		__regValue |= (HDMI21_SNPS_FIELD_VPROC_CD_OVR_EN);
	
		switch(type)
		{
			case HDMI21_RX_VPROC_CD_NONE:
			case HDMI21_RX_VPROC_CD_8BIT:
				__data = 0x4;	
				break;
			case HDMI21_RX_VPROC_CD_10BIT:
				__data = 0x5;
				break;
			case HDMI21_RX_VPROC_CD_12BIT:
				__data = 0x6;
				break;
			case HDMI21_RX_VPROC_CD_16BIT:
				__data = 0x7;
				break;
			default:
				__data = 0x4;
				break;
		}
		/* This is for [7:4], right shift 4 */
		__data = __data << 4;

		__regValue |= __data;
	}

	/* Write Reg */
	_p->link_write(HDMI21_SNPS_REG_VIDEO_CD_CONFIG, __regValue);

	return;
}

int HDMI21_VPROC_Rx_Get_OverRideColorDepth(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;
	UINT32 __regValue = 0;
	UINT32 __isOverRide = 0;
	UINT32 __overRideVal = 0;

	/* Defence Code */
	if(!_p->initiated) return 0;

	/* Get Reg Value */
	__regValue =  _p->link_read(HDMI21_SNPS_REG_VIDEO_CD_CONFIG);

	/* Set clear for the bits we wish to control */
	__isOverRide = __regValue & (HDMI21_SNPS_FIELD_VPROC_CD_OVR_EN);
	__overRideVal = ((__regValue & (HDMI21_SNPS_FIELD_VPROC_CD_OVR_VALUE)) >> 4);
	
	/* Set bit field */
	if(__isOverRide) {
		if(__overRideVal <= HDMI21_RX_VPROC_CD_8BIT) ret = 4;
		else if(__overRideVal <= HDMI21_RX_VPROC_CD_10BIT) ret = 5;
		else if(__overRideVal <= HDMI21_RX_VPROC_CD_12BIT) ret = 6;
		else if(__overRideVal <= HDMI21_RX_VPROC_CD_16BIT) ret = 7;
		else ret = 4; /* Override values for reserved work as 8BIT */

	}
	else {
		ret = 0;
	}

	return ret;
}


int HDMI21_VPROC_Rx_Set_OverRideSyncGenValWithVic(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 vicCode)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	UINT32 hSyncHfront = 0;
	UINT32 hActiveHback = 0;
	UINT32 vSyncVfront = 0;
	UINT32 vBack = 0;

	do{
		/* Step 1. Defence Code */
		if(!_p->initiated) break;

		/* Step 2. Get Sync Gen value from table */
		if(__HDMI21_VPROC_Rx_Get_SyncGenSetForDSC(_p, &hSyncHfront, &hActiveHback, &vSyncVfront, &vBack, vicCode) != RET_OK) {
			break;
		}

		/* Step 3. Override Sync gen value */
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1, hSyncHfront); /* VPROC : FRL SYNC GEN FOR HSYNC/HFRONT */
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2, vSyncVfront); /* VPROC : FRL SYNC GEN FOR VSYNC/VFRONT */
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3, hActiveHback); /* VPROC : FRL SYNC GEN FOR HACTIVE/HBACK */
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4, 0x00100000); //FRL syncgen config
		_p->link_write(HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5, vBack); /* VPROC : VBACK adjustment */

		ret = RET_OK;
	} while(0);

	return ret;
}

/*========================================================================================
 Static Function Implementation 
======================================================================================== */

static int __HDMI21_VPROC_Rx_Get_SyncGenSetForDSC(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 *pHsyncHFront, UINT32 *pHactiveHback, UINT32 *pVsyncVFront, UINT32 *pVback, UINT32 vicOverRide)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	int i;
	int vicMatch = 0;
	int matchedVicIndex = 0;
	int __tableMaxCnt = HDMI21_DSC_SUPPORT_VIC_CNT;
	HDMI21_DSC_VIC_H_PARAM_T __dsc_h_param;
	
	UINT32 __hsync = 0;
	UINT32 __hfront = 0;
	UINT32 __hback = 0;
	UINT32 __vsync = 0;
	UINT32 __vfront= 0;
	UINT32 __vback = 0;
	UINT32 __temp = 0;

	UINT32 __hctotal = 0;
	UINT32 __attribute__((unused)) __vblankMax = 0;
	UINT32 __attribute__((unused)) __vblankCta = 0;
	UINT32 __vicCode = 0;


	do{
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 550){
			break;
		}

		memset((HDMI21_DSC_VIC_H_PARAM_T *)&__dsc_h_param, 0, sizeof(HDMI21_DSC_VIC_H_PARAM_T));

		/* Dev Handler Defence */
		if(!_p->initiated) {
			HDMI20_ERROR("VPROC : Dev Handler Not initated\n");	
			break;
		}

		/* Null Pointer Defence */
		if((pHsyncHFront == NULL) || (pHactiveHback == NULL) || (pVsyncVFront == NULL) || (pVback == NULL)) {
			HDMI20_ERROR("VPROC[%d] : Null Pointer Defence during syncGen Calculation\n", _p->port);
			break;
		}

		/* Set Initial value for call by reference */
		*pHsyncHFront 	= 0;
		*pHactiveHback 	= 0;
		*pVsyncVFront 	= 0;
		*pVback 		= 0;

		/* Check if VIC code exist in AVI */
		if(vicOverRide == 0) {
			if(_p->hwVideo.vicCode == 0) break;

			__vicCode = _p->hwVideo.vicCode;
		}
		else {
			HDMI20_INFO("VPROC[%d] : SyncGen OverRide search mode for VIC[%d]\n", _p->port, vicOverRide);
			__vicCode = vicOverRide;
		}


		/* Check if 7-35/7-36 has a match in VIC code */
		for(i=0; i<__tableMaxCnt; i++) {
			if(gHdmi21DscVicList[i].vic == __vicCode) {
				HDMI20_VIDEO("VPROC[%d] : Found VIC Match for DSC Table[%d]\n", _p->port, __vicCode);
				/* Flag */
				vicMatch = 1;
				/* VIC matched Index value */
				matchedVicIndex = i;
			
				break;
			}
		}

		/* Get DSC VIC H Param */
		if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
			memcpy((HDMI21_DSC_VIC_H_PARAM_T *)&__dsc_h_param, &gHdmi21DscHParam_Frl12g[matchedVicIndex], sizeof(HDMI21_DSC_VIC_H_PARAM_T));
		}
		else if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
			memcpy((HDMI21_DSC_VIC_H_PARAM_T *)&__dsc_h_param, &gHdmi21DscHParam_Frl10g[matchedVicIndex], sizeof(HDMI21_DSC_VIC_H_PARAM_T));
		}
		else if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) {
			memcpy((HDMI21_DSC_VIC_H_PARAM_T *)&__dsc_h_param, &gHdmi21DscHParam_Frl8g[matchedVicIndex], sizeof(HDMI21_DSC_VIC_H_PARAM_T));
		}
		else if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L) {
			memcpy((HDMI21_DSC_VIC_H_PARAM_T *)&__dsc_h_param, &gHdmi21DscHParam_Frl6g[matchedVicIndex], sizeof(HDMI21_DSC_VIC_H_PARAM_T));
		}
		else if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			memcpy((HDMI21_DSC_VIC_H_PARAM_T *)&__dsc_h_param, &gHdmi21DscHParam_Frl3g[matchedVicIndex], sizeof(HDMI21_DSC_VIC_H_PARAM_T));
		}
		else {
			HDMI20_ERROR("VPROC[%d] : Error! DSC Table only permits FRL Signal. Current PHY State[%d]\n", _p->port, _p->phyInitiatedMode);
			break;
		}

		/* If there was a VIC match, get HCActive/HCBlank from table 7-35/7-36 */
		if(vicMatch > 0) {
			/* V info from VIC Table */
			__vsync = gHdmi21DscVicList[matchedVicIndex].vsync;
			__vfront= gHdmi21DscVicList[matchedVicIndex].vfront;
			__vback = gHdmi21DscVicList[matchedVicIndex].vback;

			/* Get HCActive/HCBlank */
			if((_p->hwVideo.video_format == 0) || (_p->hwVideo.video_format == 2)) {
				__hsync  = __dsc_h_param.hsync_444;
				__hfront = __dsc_h_param.hfront_444;
				__hback  = __dsc_h_param.hback_444;
				__hctotal = gHdmi21DscVicList[matchedVicIndex].hcActive_444 + gHdmi21DscVicList[matchedVicIndex].hcBlank_444;
			}
			else if(_p->hwVideo.video_format == 1) {
				__hsync  = __dsc_h_param.hsync_422;
				__hfront = __dsc_h_param.hfront_422;
				__hback  = __dsc_h_param.hback_422;
				__hctotal = gHdmi21DscVicList[matchedVicIndex].hcActive_422 + gHdmi21DscVicList[matchedVicIndex].hcBlank_422;
			}
			else if(_p->hwVideo.video_format == 3) {
				__hsync  = __dsc_h_param.hsync_420;
				__hfront = __dsc_h_param.hfront_420;
				__hback  = __dsc_h_param.hback_420;
				__hctotal = gHdmi21DscVicList[matchedVicIndex].hcActive_420 + gHdmi21DscVicList[matchedVicIndex].hcBlank_420;
			}
		}
		else {
			HDMI20_INFO("VPROC[%d] : Warning! VIC[%d] is not in HDMI2.1 Table 7-35/7-36. Set to default\n", _p->port, __vicCode);
			break;
		}

		/* Check HCActive/HCBlank Value */
		if((__hsync == 0) || (__hfront == 0) || (__hback == 0)) {
			HDMI20_INFO("VPROC[%d] : VIC[%d] is in Table 7-35/36 but FRL Rate/DSC may not be supported from spec\n", _p->port, __vicCode);
			break;
		}

		if (gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DSC_REDUCE_HBACK].value > 0){
			/* Reduce Hback to have the same values as HSync, and compenstate to HFront for robustness */
			if(__hback > __hsync) {
				__temp   = __hback - __hsync;
				
				__hback  = __hsync;
				__hfront = __hfront + __temp;
			}
			else if( __hsync > __hback) {
				__temp   = __hsync - __hback;

				__hsync  = __hback;
				__hfront = __hfront + __temp;
			}
		}

		/* Byte align for register set, directly to call-by-reference pointer */
		__hsync   = __hsync << 16; __hsync &= (0xFFFF0000);
		__hfront &= (0x0000FFFF);
		*pHsyncHFront 	= (__hsync | __hfront);

		__hback  &= (0x0000FFFF);
		*pHactiveHback 	= __hback; /* 2020/05/19 : HACTIVE value is set to zero, for the HW to calculate for itself */

		if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VS_ZERO_FOR_DSC].value > 0) {
			#if 0 /* 2021/09/02 : VRR+FRL+DSC had issues on latency due to the Synopsys Document recommended setting. Revert to 0 on Vsync/Vfront*/
			/* 2021/05/26 : O22 cannot use 0 values for VSyncFront SyncGen */
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				/* Incase where, there was no VIC match */
				if(vicMatch == 0) {
					*pVsyncVFront = gHDMI21RxDevLinkControler[HDMI21__LINK_O22_FRLSYNCGEN_VFRONTSYNC].value;
				}
				else {
					/* Calculate VBlank_max */
					__vblankCta = (gHdmi21DscVicList[matchedVicIndex].vtotal - gHdmi21DscVicList[matchedVicIndex].vactive);
					__vblankMax = ((__vblankCta * 1000) / ( 1000 + (1012000/__hctotal)));
					
					/* Reduce this value so that this could be a multiple of 4 */
					HDMI21_LINE_DBG(783, "DBG[%d] : Calculated VBlank(max) = [%d] (HcTotal = %d, Vblank(cta) = %d)\n",\
							_p->port, __vblankMax, __hctotal, __vblankCta);
				
					__vblankMax -= 1;
					__vblankMax  = __vblankMax>>2;
					__vblankMax  = __vblankMax<<2;

					/* VSync : VFront = 1:7 */
					__vsync  = __vblankMax >> 3;
					__vfront = __vblankMax - __vsync;

					HDMI21_LINE_DBG(783, "DBG[%d] : Normalized VBlank(max) = [%d]. Calculated Vsync = %d, Vfront = %d\n",\
							_p->port, __vblankMax, __vsync, __vfront);

					__vsync   = __vsync << 16; __vsync &= (0xFFFF0000);
					__vfront &= (0x0000FFFF);
					*pVsyncVFront 	= (__vsync | __vfront);
				}
			}
			else {
				*pVsyncVFront = 0;	
			}
			#else 
			*pVsyncVFront = 0;	
			#endif
		}
		else {
			__vsync   = __vsync << 16; __vsync &= (0xFFFF0000);
			__vfront &= (0x0000FFFF);
			*pVsyncVFront 	= (__vsync | __vfront);
		}

		__vback  &= (0x0000FFFF);
		*pVback = (__vback | 0x00080000);

		HDMI20_VIDEO("VPROC[%d] : DSC Sig(VIC:%d/CSC:%d/FRL:%d) Sync Gen HSyncFront[0x%08x]/HActiveBack[0x%08x]/VsyncFront[0x%08x]/VBack[0x%08x]\n",\
				_p->port, __vicCode, _p->hwVideo.video_format, _p->phyInitiatedMode, *pHsyncHFront, *pHactiveHback, *pVsyncVFront, *pVback);

		ret = RET_OK;
	} while(0);

	return ret;
}



static int __HDMI21_VPROC_Rx_Get_SyncValforSyncGen1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 *pHsyncHFront, UINT32 *pHactiveHback, UINT32 *pVsyncVFront, UINT32 *pVback)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	int i;
	int vicMatch = 0;
	int matchedVicIndex = 0;
	int __tableMaxCnt = HDMI21_MISC_CTA861G_IDX_CNT; 
	
	UINT32 __hsync = 0;
	UINT32 __hfront = 0;
	UINT32 __hback = 0;
	UINT32 __vsync = 0;
	UINT32 __vfront= 0;
	UINT32 __vback = 0;

	do{
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 550){
			break;
		}

		/* Dev Handler Defence */
		if(!_p->initiated) {
			HDMI20_ERROR("VPROC : Dev Handler Not initated\n");	
			break;
		}

		/* Null Pointer Defence */
		if((pHsyncHFront == NULL) || (pHactiveHback == NULL) || (pVsyncVFront == NULL) || (pVback == NULL)) {
			HDMI20_ERROR("VPROC[%d] : Null Pointer Defence during syncGen Calculation\n", _p->port);
			break;
		}

		/* Set Initial value for call by reference */
		*pHsyncHFront 	= 0;
		*pHactiveHback 	= 0;
		*pVsyncVFront 	= 0;
		*pVback 		= 0;

		/* 2020/10/19 : SyncGen1 Cal Func Override Op */
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_GENVAL_OVR].value > 0) {
			if(_p->hwVideo.hactive >= 5500) {
				/* 8K */
				*pHsyncHFront 	= 0x00480040; 		/* 0x440 */
				*pHactiveHback 	= 0x48;				/* 0x44C */
				/* 210602 : Hong Yong Bin */
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )	{	
					*pVsyncVFront 	= gHDMI21RxDevLinkControler[HDMI21__LINK_O22_FRLSYNCGEN_VFRONTSYNC].value;	/* 0x444 */ 
					*pVback 		= 0x0008000A;		/* 0x454 */
				}
				else {
					*pVsyncVFront 	= 0;			/* 0x444 */	
					*pVback 		= 0x0008002C;		/* 0x454 */
				}
			}
			else {
				/* Under 4K */
				*pHsyncHFront 	= 0x000F0058; 		/* 0x440 */
				*pHactiveHback 	= 0xF;				/* 0x44C */
				/* 210602 : Hong Yong Bin */
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )	{
					*pVsyncVFront 	= gHDMI21RxDevLinkControler[HDMI21__LINK_O22_FRLSYNCGEN_VFRONTSYNC].value;	/* 0x444 */ 
					*pVback 		= 0x0008000A;		/* 0x454 */
				}
				else {	
					*pVsyncVFront 	= 0;				/* 0x444 */	
					*pVback 		= 0x0008002C;		/* 0x454 */
				}
				
			}


			HDMI20_VIDEO("VPROC[%d] : OVR Mode. FRL(VIC:%d/CSC:%d/FRL:%d) Gen#1 HSyncFront[0x%08x]/HActiveBack[0x%08x]/VsyncFront[0x%08x]/VBack[0x%08x]\n",\
					_p->port, _p->hwVideo.vicCode, _p->hwVideo.video_format, _p->phyInitiatedMode, *pHsyncHFront, *pHactiveHback, *pVsyncVFront, *pVback);


			ret = RET_OK;
			break;
		}

		/* Check if VIC code exist in AVI */
		if(_p->hwVideo.vicCode == 0) break;

		/* Check if 7-35/7-36 has a match in VIC code */
		for(i=0; i<__tableMaxCnt; i++) {
			if(gHdmi21CtaTable[i].vic == _p->hwVideo.vicCode) {
				HDMI20_VIDEO("VPROC[%d] : Found VIC Match for CTA-861 Table[%d]\n", _p->port, _p->hwVideo.vicCode);
				/* Flag */
				vicMatch = 1;
				/* VIC matched Index value */
				matchedVicIndex = i;
			
				break;
			}
		}


		/* If there was a VIC match, get HCActive/HCBlank from table 7-35/7-36 */
		if(vicMatch > 0) {
			/* V info from VIC Table */
			__vsync = gHdmi21CtaTable[matchedVicIndex].Vsync;
			__vfront= gHdmi21CtaTable[matchedVicIndex].Vfront;
			__vback = gHdmi21CtaTable[matchedVicIndex].Vback;

			/* Get hSync/hFront/hBack */
			__hsync  = gHdmi21CtaTable[matchedVicIndex].Hsync;
			__hfront = gHdmi21CtaTable[matchedVicIndex].Hfront;
			__hback  = gHdmi21CtaTable[matchedVicIndex].Hback;
		}
		else {
			HDMI20_INFO("VPROC[%d] : Warning! VIC[%d] is not in CTA-861-G. Set to default\n", _p->port, _p->hwVideo.vicCode);
			break;
		}

		/* Check HCActive/HCBlank Value */
		if((__hsync == 0) || (__hfront == 0) || (__hback == 0)) {
			HDMI20_INFO("VPROC[%d] : VIC[%d] is in CTA-861-G spec, but some H values may be 0\n", _p->port, _p->hwVideo.vicCode);
			break;
		}

		/* Byte align for register set, directly to call-by-reference pointer */
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_HS_ZERO_FOR_GEN1].value > 0) {
			*pHsyncHFront = 0;
		}
		else {
			__hsync   = __hsync << 16; __hsync &= (0xFFFF0000);
			__hfront &= (0x0000FFFF);
			*pHsyncHFront 	= (__hsync | __hfront);
		}

		__hback  &= (0x0000FFFF);
		*pHactiveHback 	= __hback; /* 2020/05/19 : HACTIVE value is set to zero, for the HW to calculate for itself */

		if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VS_ZERO_FOR_GEN1].value > 0) {
			*pVsyncVFront = 0;	
		}
		else {
			__vsync   = __vsync << 16; __vsync &= (0xFFFF0000);
			__vfront &= (0x0000FFFF);
			*pVsyncVFront 	= (__vsync | __vfront);
		}

		__vback  &= (0x0000FFFF);
		*pVback = (__vback | 0x00080000);

		HDMI20_VIDEO("VPROC[%d] : FRL Sig(VIC:%d/CSC:%d/FRL:%d) Sync Gen#1 HSyncFront[0x%08x]/HActiveBack[0x%08x]/VsyncFront[0x%08x]/VBack[0x%08x]\n",\
				_p->port, _p->hwVideo.vicCode, _p->hwVideo.video_format, _p->phyInitiatedMode, *pHsyncHFront, *pHactiveHback, *pVsyncVFront, *pVback);

		ret = RET_OK;
	} while(0);

	return ret;

}
