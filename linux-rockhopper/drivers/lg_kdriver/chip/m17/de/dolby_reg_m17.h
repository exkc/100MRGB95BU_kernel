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
 * version    1.0
 * date       2016.03.28
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef  DOLBY_REG_M17_INC
#define  DOLBY_REG_M17_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "m17/de/de_cfg_m17.h"
#include "de_cfg.h"

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
#define HDR_BASE_ADDRESS	gMemCfgHDR[0].frame_base//VIDEO_M16_FIRMWARE_MEM_BASE_HDR
#define HDR_DOLBY_3D_LUT_SIZE	0x6660
#define HDR_DOLBY_TC_G2L_LUT_SIZE 0x800 //TC+GL

#define HDR_DOLBY_MD_BASE	HDR_BASE_ADDRESS //OTT metadata base address [from Firmware]
//Need not to use dm_metadata_t as it is around 4K and spec says the metadata will not come more than 512 bytes
#define HDR_DOLBY_MD_SIZE	5*KB //(sizeof(rpu_ext_config_fixpt_main_t)+sizeof(dm_metadata_t)+(sizeof(LX_IPC_TYPE_T)+sizeof(UINT32))*3+SIZE_PTS)*MAX_FRAMES+sizeof(LX_IPC_TYPE_T)
#define HDR_DOLBY_LUT_BASE	(HDR_DOLBY_MD_BASE + HDR_DOLBY_MD_SIZE)
#define HDR_DOLBY_LUT_SIZE	(HDR_DOLBY_3D_LUT_SIZE+HDR_DOLBY_TC_G2L_LUT_SIZE+SIZE_PTS+MIF_ALLIGNMENT_BYTE)*MAX_FRAMES*COPY_SIZE
#define HDR_DOLBY_REGMAP_BASE (HDR_DOLBY_LUT_BASE+HDR_DOLBY_LUT_SIZE)
#define HDR_DOLBY_REGMAP_SIZE (sizeof(LX_DOLBY_COMP_REG_T)+sizeof(LX_DOLBY_DM_REG_T)+SIZE_PTS)*MAX_FRAMES*COPY_SIZE	
#define HDR_DOLBY_INDEX_BASE	(HDR_DOLBY_REGMAP_BASE+HDR_DOLBY_REGMAP_SIZE)
#define HDR_DOLBY_INDEX_SIZE	(sizeof(UINT32))*MAX_FRAMES
/*OTT memory map END*/

//Physical address are not sure...so need to get from H/W team......
#define DOLBY_HAL_M17_CTRL_ADDR 0xC9006000
#define DOLBY_HAL_M17_CTRL_SIZE 0x3C4
#define DOLBY_HAL_M17A0_HDMI_MD_ADDR	0xC9005400
#define DOLBY_HAL_M17C0_HDMI_MD_ADDR	0xC9001200
#define DOLBY_HAL_M17_HDMI_TOTMD_SIZE 0x200
#define DOLBY_HAL_M17_HDMI_MD_SIZE 0x6E
#define DOLBY_HAL_M17_LUTIP_ADDR 0xC9003C00
#define DOLBY_HAL_M17_LUTIP_SIZE 0x300
#define DOLBY_HAL_M17_MCUIPC_ADDR 0xC90262E0
#define DOLBY_HAL_M17_LUT_DDR_ADDR HDR_DOLBY_LUT_BASE //Note:need to get from MCU
#define DOLBY_HAL_M17_LUT_DDR_SIZE HDR_DOLBY_LUT_SIZE //Note:need to get from MCU
#define DOLBY_HAL_M17_IP_CONFIG_DDR_ADDR HDR_DOLBY_REGMAP_BASE //Note:need to get from MCU
#define DOLBY_HAL_M17_IP_CONFIG_DDR_SIZE HDR_DOLBY_REGMAP_SIZE //Note:need to get from MCU
#define DOLBY_HAL_M17_OTTMD_DDR_ADDR HDR_DOLBY_MD_BASE //Note:need to get from MCU
#define DOLBY_HAL_M17_OTTMD_DDR_SIZE HDR_DOLBY_MD_SIZE //Note:need to get from MCU
#define DOLBY_HAL_M17_FRAME_INDEX_BASE HDR_DOLBY_INDEX_BASE
#define DOLBY_HAL_M17_FRAME_INDEX_SIZE HDR_DOLBY_INDEX_SIZE

//Interrup address
#define DOLBY_HAL_M17_HDRINTR_ADDR 0xC9005000
#define DOLBY_HAL_M17_HDRINTR_SIZE 0xFC
#define DOLBY_HAL_M17_MCUINTR_ADDR 0xC9026010
#define DOLBY_HAL_M17_MCUINTR_SIZE 0x20
#define DOLBY_HAL_M17_PICSTARTINTR_ADDR 0xC9001104
#define DOLBY_HAL_M17_PICSTARTINTR_SIZE 0x4

//LUT RAM address
#define DOLBY_HAL_M17_RPU_ADDR 0x14000000
#define DOLBY_HAL_M17_RPU_SIZE 0xC2B0
#define DOLBY_HAL_M17_3DLUTRAM_ADDR DOLBY_HAL_M17_RPU_ADDR + 0x00030000
#define DOLBY_HAL_M17_3DLUTRAM_SIZE 0x1B9A0 //0x6660
#define DOLBY_HAL_M17_TCLUTRAM_ADDR DOLBY_HAL_M17_3DLUTRAM_ADDR + DOLBY_HAL_M17_3DLUTRAM_SIZE 
#define DOLBY_HAL_M17_TCLUTRAM_SIZE 0x800

//Irq NUMBER not sure... so need to get from H/W team
#define DOLBY_HAL_M17_HDRINTRIRQ_NUMBER 161
#define DOLBY_HAL_M17_MCUIRQ_NUMBER 90


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

typedef struct
{
	UINT32 unImageBase;
	UINT32 unLutBase;
	UINT32 unAckFlag;
	UINT32 unReserved;
}DOLBY_HAL_HDR_ADDR_T;

/*----------------------------------------------------------------------------------------
 *   Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_DHDR_IP_REG_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit);
int DE_DHDR_IP_REG_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag);
int DE_DHDR_IP_REG_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *i_PtrIrqStatus,int i_unFlag);
int DE_DHDR_IP_REG_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_PtrMetaData);
int DE_DHDR_IP_REG_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId);
int DE_DHDR_IP_REG_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
int DE_DHDR_IP_REG_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
int DE_DHDR_IP_REG_SetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_COMP_REG_T *i_PtrCompConfig);
int DE_DHDR_IP_REG_GetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_COMP_REG_T *i_PtrCompConfig);
int DE_DHDR_IP_REG_SetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_REG_T *i_PtrDMConfig);
int DE_DHDR_IP_REG_GetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_REG_T *i_PtrDMConfig);
int DE_DHDR_IP_REG_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum);
int DE_DHDR_IP_REG_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby);
int DE_DHDR_IP_REG_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyUninit);
int DE_DHDR_IP_REG_SetMdPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path);

#endif   /* ----- #ifndef DE_REG_M17_INC  ----- */
/**  @} */
