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
 * author     manjunath.goudar (manjunath.goudar@lge.com)
 * version    1.0
 * date       2016.03.29
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

#ifndef _DOLBY_IO_h
#define _DOLBY_IO_h

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_kapi.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define DOLBY_HAL_M17_DEBUG
#define DOLBY_DRIVER_CHECK_INIT(_param1,_param2) if(_param1 != DOLBY_INITIALIZED) { ret = RET_ERROR ; _param2 = DOLBY_INIT_ERROR; DE_ERROR("Dolby Driver Not Initalized %d!!\n",_param1); break;}
#define MD_CALLBK_WAIT_TIME_MSEC  20
#define TRY_CNT_FOR_MD_READY 10
#define OTT_INTR_ENABLE 0xFF7FFFFF
#define OTT_INTR_BIT 23
#define HDMI_INTR_ENABLE 0xFF7DFFFF
#define HDMI_INTR_BIT 17
#define MCU_INTR_CLEAR_BIT 26

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum {
	DOLBY_INIT_ERROR = -7,
	DOLBY_MD_ERROR,
	DOLBY_CONFIG_ERROR,
	DOLBY_LUT_ERROR,
	DOLBY_START_ERROR,
	DOLBY_INTR_ERROR,
	DOLBY_UNKNOWN_ERROR,
	DOLBY_OK
}DOLBY_CMD_ERROR_T;

typedef enum {
	DOLBY_UNINTIALIZED,
	DOLBY_INITIALIZED
}DOLBY_DRV_STATE_T;

typedef struct
{
	LX_DOLBY_REG_MAP_T 	sMCUIntrRegMap;
	LX_DOLBY_REG_MAP_T 	sHDRCtrlRegMap;
	//LX_DOLBY_REG_MAP_T		sPicStartIntrRegMap;
	LX_DOLBY_REG_MAP_T 	sMCURegMap;
	LX_DOLBY_REG_MAP_T	sLUTIPRegMap;
	LX_DOLBY_REG_MAP_T 	sCompDMRegMap;
	LX_DOLBY_REG_MAP_T 	s3DLUTRAMRegMap;
	LX_DOLBY_REG_MAP_T	sTCLUTRAMRegMap;
	LX_DOLBY_REG_MAP_T	sMDRegMap;
	LX_DOLBY_REG_MAP_T	sOTTMDRegMap;
	LX_DOLBY_REG_MAP_T	sLUTDDRRegMap;
	LX_DOLBY_REG_MAP_T	sFrameIdxRegMap;
	LX_DOLBY_REG_MAP_T	sCompDMDDRRegMap;
	LX_DOLBY_REG_MAP_T	sDoviDDRMap;
	LX_DOLBY_MODE_T	 	eCurMode;
	DOLBY_CMD_ERROR_T	eCmdErr;
	DOLBY_DRV_STATE_T	eDolbyDrvState;
	UINT32	unFrameNum;
	UINT32	unHDRIntrIrqNum;
	UINT32	unMCUIntrIrqNum;
	UINT32	unDolbyInitCount;
	LX_DOLBY_HDMI_MDDESC_METHOD	eHdmiDescMethod;
}DOLBY_DEVICE_DATA_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_DHDR_IP_IO_Init(LX_DOLBY_IOCTL_INIT_T *sptr_DolbyParam);
int DE_DHDR_IP_IO_GetHDMIMetaData(LX_DOLBY_IOCTL_HDMI_MD_T *sptr_DolbyParam,LX_DOLBY_DM_MD_TYPE *sptr_eMDtype,LX_DOLBY_DM_MD_T *sptr_HdmiMd);
int DE_DHDR_IP_IO_GetOTTMetaData(LX_DOLBY_OTT_MD_IOCTL_T *sptr_DolbyParam);
int DE_DHDR_IP_IO_SetConfig(unsigned long arg);
int DE_DHDR_IP_IO_GetConfig(unsigned long arg);
int DE_DHDR_IP_IO_SetLut(unsigned long arg);
int DE_DHDR_IP_IO_Start(unsigned long arg);
int DE_DHDR_IP_IO_Uninit(UINT8 *sptr_DolbyParam);
int DE_DHDR_IP_INTR_Init(DOLBY_DEVICE_DATA_T *i_PtrDolbyDrv);
int DE_DHDR_IP_INTR_UnInit(DOLBY_DEVICE_DATA_T *i_PtrDolbyUnInit);
int DE_DHDR_IP_INTR_MDReadUnblock(UINT8 *sptr_DOlbyParam);
int DE_DHDR_IP_IO_Set_HDMI_MD_Path(unsigned long arg);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif
/**  @} */
