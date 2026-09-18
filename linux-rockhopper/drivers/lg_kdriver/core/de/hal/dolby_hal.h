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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     manjunath.goudar (manjunath.goudar@lge.com)
 * version    1.0
 * date       2016.03.29
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

#ifndef  DOLBY_HAL_INC
#define  DOLBY_HAL_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "../dolby_io.h"
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_DHDR_IP_HAL_Select_Chip(void);
int DE_DHDR_IP_HAL_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit);
int DE_DHDR_IP_HAL_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrHdrIrqStatus,int i_unFlag);
int DE_DHDR_IP_HAL_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *i_PtrIrqStatus,int i_unFlag);
int DE_DHDR_IP_HAL_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_PtrMetaData);
int DE_DHDR_IP_HAL_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_OTT_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId);
int DE_DHDR_IP_HAL_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
int DE_DHDR_IP_HAL_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
int DE_DHDR_IP_HAL_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum);
int DE_DHDR_IP_HAL_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby);
int DE_DHDR_IP_HAL_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);
int DE_DHDR_IP_HAL_SetMDPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path);

#endif  

/**  @} */
