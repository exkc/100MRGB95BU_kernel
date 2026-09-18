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
 * author     manjunath.goudar	(manjunath.goudar@lge.com)
 * modifier   harish chandra singh (harish.singh@lge.com)
 * version    1.0
 * date       2023.04.17
 * note       Additional information.
 * Added support for O24 fpga and soc
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef  DOLBY_REG_O24_INC
#define  DOLBY_REG_O24_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_cfg.h"
#include "o24/de/de_cfg_o24.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
/*OTT memory map
  *START
*/

#define MAX_FRAMES	2
#define SIZE_PTS	8 //64bit pts
#define COPY_SIZE	2
#define MIF_ALLIGNMENT_BYTE 8 
#define KB 1024

#define HDR_BASE_ADDRESS	g_de_hdr.base
#define DOLBY_HAL_O24A0_HDMI_MD_ADDR 0xCC820200
#define DOLBY_HAL_O24A0_HDMI_MD_LEN_ADDR 0xCC8201FC
#define DOLBY_HAL_O24_HDMI_TOTMD_SIZE 0x200 

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
/*
typedef struct
{
	UINT32 unImageBase;
	UINT32 unLutBase;
	UINT32 unAckFlag;
	UINT32 unReserved;
}DOLBY_HAL_HDR_ADDR_T;
*/
/*----------------------------------------------------------------------------------------
 *   Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_DHDR_IP_REG_O24_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit);
int DE_DHDR_IP_REG_O24_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag);
int DE_DHDR_IP_REG_O24_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *i_PtrIrqStatus,int i_unFlag);
int DE_DHDR_IP_REG_O24_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_PtrMetaData);
int DE_DHDR_IP_REG_O24_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId);
int DE_DHDR_IP_REG_O24_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
int DE_DHDR_IP_REG_O24_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
int DE_DHDR_IP_REG_O24_SetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_IP_REG_T *i_PtrCompConfig);
int DE_DHDR_IP_REG_O24_SetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_IP_REG_T *i_PtrDMConfig);
int DE_DHDR_IP_REG_O24_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum);
int DE_DHDR_IP_REG_O24_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby);
int DE_DHDR_IP_REG_O24_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyUninit);
int DE_DHDR_IP_REG_O24_SetMdPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path);

#endif   /* ----- #ifndef DE_REG_O24_INC  ----- */
/**  @} */
