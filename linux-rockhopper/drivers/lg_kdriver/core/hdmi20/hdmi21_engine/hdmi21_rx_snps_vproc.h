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
 *  @author     won.hur
 *  @version    1.0
 *  @date       2019-04-01
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_VPROC_H_
#define	_HDMI21_RX_SNPS_VPROC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi21_hal_driver.h"		/* Device Handler */

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif


#define HDMI21_SNPS_REG_VIDEO_CD_CONFIG			(0x420)
#define HDMI21_SNPS_FIELD_VPROC_CD_OVR_VALUE	MSK(4,4)
#define HDMI21_SNPS_FIELD_VPROC_CD_OVR_EN		BIT(0)

#define HDMI21_SNPS_REG_VIDEO_PP_CONFIG			(0x424)
#define HDMI21_SNPS_FIELD_VPROC_PP_DIFF_THR		MSK(8, 16)
#define HDMI21_SNPS_FIELD_VPROC_PP_DIFF_ON_VALID_Q ST	BIT(8)
#define HDMI21_SNPS_FIELD_VPROC_PP_OVR_VALUE	MSK(4, 4)
#define HDMI21_SNPS_FIELD_VPROC_PP_OVR_EN		BIT(0)


#define HDMI21_SNPS_REG_VIDEO_CONFIG1			(0x428)
#define HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_BACK_FIX_EN	BIT(30)
#define HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN_SEL			MSK(2, 28)
#define HDMI21_SNPS_FIELD_VPROC_FRL_SYNCGEN2_SEL			BIT(29)
#define HDMI21_SNPS_FIELD_VPROC_FRL_SYNC_GEN_VB_CONST 	BIT(27)
#define HDMI21_SNPS_FIELD_VPROC_BYPASS_48B_MODE	BIT(26)
#define HDMI21_SNPS_FIELD_VPROC_BYPASS			BIT(25)
#define HDMI21_SNPS_FIELD_VPROC_VMUTE_EN		BIT(16)

#define HDMI21_SNPS_REG_VIDEO_CONFIG2			(0x42C)
#define HDMI21_SNPS_FIELD_VPROC_VSYNC_POL_OVR_VAL	BIT(19)
#define HDMI21_SNPS_FIELD_VPROC_VSYNC_POL_OVR_EN	BIT(18)
#define HDMI21_SNPS_FIELD_VPROC_HSYNC_POL_OVR_VAL	BIT(17)
#define HDMI21_SNPS_FIELD_VPROC_HSYNC_POL_OVR_EN	BIT(16)
#define HDMI21_SNPS_FIELD_VPROC_3D_FMT_OVR_VALUE 	MSK(4, 12)
#define HDMI21_SNPS_FIELD_VPROC_3D_FMT_OVR_EN		BIT(8)
#define HDMI21_SNPS_FIELD_VPROC_FMT_OVR_VALUE	MSK(3, 4)
#define HDMI21_SNPS_FIELD_VPROC_FMT_OVR_EN		BIT(0)

#define HDMI21_SNPS_REG_VIDEO_MUTE_VALUE_H		(0x430)
#define HDMI21_SNPS_FIELD_VPROC_VMUTE_VALUE_HIGH MSK(16,0)

#define HDMI21_SNPS_REG_VIDEO_MUTE_VALUE_L		(0x434)
#define HDMI21_SNPS_FIELD_VPROC_VMUTE_VALUE_LOW	(0xFFFFFFFF)

#define HDMI21_SNPS_REG_VIDEO_STATUS			(0x43C)
#define HDMI21_SNPS_FIELD_VPROC_PP_DIFF_CNT		MSK(8,8)
#define HDMI21_SNPS_FIELD_VPROC_PP_CURRENT		MSK(3,4)
#define HDMI21_SNPS_FIELD_VPROC_CD_CURRENT		MSK(4,0)

#define HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG1	(0x440)
#define HDMI21_SNPS_FIELD_VPROC_HSYNC_WIDTH_QST	MSK(16, 16)
#define HDMI21_SNPS_FIELD_VPROC_HFRONT_WIDTH_QST MSK(16, 0)

#define HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG2	(0x444)
#define HDMI21_SNPS_FIELD_VPROC_VSYNC_WIDTH_QST	MSK(16, 16)
#define HDMI21_SNPS_FIELD_VPROC_VFRONT_WIDTH_QST MSK(16, 0)

#define HDMI21_SNPS_REG_VIDEO_FVA_VRR_CONFIG	(0x448)
#define HDMI21_SNPS_FIELD_VPROC_ACTIVE_SPACE_QST MSK(16, 0)

#define HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG3	(0x44C)

#define HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG4	(0x450)

#define HDMI21_SNPS_REG_VIDEO_SYNCGEN_CONFIG5	(0x454)
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

typedef enum
{
	HDMI21_RX_VPROC_CD_NONE = 0,
	HDMI21_RX_VPROC_CD_8BIT = 4,
	HDMI21_RX_VPROC_CD_10BIT = 5,
	HDMI21_RX_VPROC_CD_12BIT = 6,
	HDMI21_RX_VPROC_CD_16BIT = 7,
	HDMI21_RX_VPROC_CD_MAXNUM
} HDMI21_RX_VPROC_CD_TYPE_T;

typedef enum
{
	HDMI21_RX_VPROC_PP_PHASE_4 = 0,
	HDMI21_RX_VPROC_PP_PHASE_1 = 1,
	HDMI21_RX_VPROC_PP_PHASE_2 = 2,
	HDMI21_RX_VPROC_PP_PHASE_3 = 3,
	HDMI21_RX_VPROC_PP_MAXNUM
} HDMI21_RX_VPROC_PP_PHASE_TYPE_T;
	
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_VPROC_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_VPROC_Rx_Set_SyncGenSel(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int value);
void HDMI21_VPROC_Rx_Set_RGB444OverRide(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isOverRide);
void HDMI21_VPROC_Rx_Set_Mute(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet);
void HDMI21_VPROC_Rx_Set_LinkBypassForDSC(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet, int mode);
void HDMI21_VPROC_Rx_Set_MuteColor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isYCbCr444or422);
void HDMI21_VPROC_Rx_Set_ForceColorDepth8Bit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet);

int  HDMI21_VPROC_Rx_Get_IsMute(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
HDMI21_RX_VPROC_CD_TYPE_T HDMI21_VPROC_Rx_Get_ColorDepth(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_VPROC_Rx_Set_HVSyncPolarity(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isOverRide, bool hNegative, bool  vNegative);
void HDMI21_VPROC_Rx_Set_OverRideColorDepth(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isOverRide, HDMI21_RX_VPROC_CD_TYPE_T type);
int  HDMI21_VPROC_Rx_Get_OverRideColorDepth(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_VPROC_Rx_Set_OverRidePixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isOverRide, HDMI21_RX_VPROC_PP_PHASE_TYPE_T pP);
int  HDMI21_VPROC_Rx_Get_OverRidePixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
HDMI21_RX_VPROC_PP_PHASE_TYPE_T HDMI21_VPROC_Rx_Get_PixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
int HDMI21_VPROC_Rx_Get_SyncGenSel(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
int HDMI21_VPROC_Rx_Set_OverRideSyncGenValWithVic(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 vicCode);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

