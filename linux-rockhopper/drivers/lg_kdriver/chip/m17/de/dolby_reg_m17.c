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
 * author	  manjunath.goudar (manjunath.goudar@lge.com)
 * version	  1.0
 * date		  2011.03.28
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <linux/slab.h>

#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/uaccess.h>

#include "base_types.h"
#include "os_util.h"

#include "de_kapi.h"
#include "de_def.h"
#include "../../../core/de/dolby_io.h"
#include "dolby_reg_m17.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define VDO_FRAME_BUFFER1 0x18000000
#define VDO_FRAME_BUFFER2 0x1C000000
#define MD_PGM_START_OFFSET 0x8
#define MD_PGM_STOP_OFFSET 0xC
#define COMPOSER_OFFSET 0xC8
#define DM_OFFSET 0x18
#define MD_RDY_INTR_MASK_OFFSET 0x54
#define MD_RDY_INTR_STATUS_OFFSET 0x50
#define MCU_INTR_CLEAR_OFFSET 0x04
#define PIC_START_OFFSET 0x04
#define LUT_3D_OFFSET 0x26C
#define TC_LUT_OFFSET 0x6C
#define VDEC_MEMORY_ALLIGNMENT	4 //Vdec will provide data in 4 byte alligned memory
#define DOLBY_HAL_CHECK_NULL(_param) if(_param==NULL){DE_ERROR("Error: [%s:%d] NULL Pointer Error!!\n",__F__,__L__); ret = RET_ERROR; break;}
#define LBUS_VDEC_M0 0xC98240A0
#define LBUS_GPU 0xC98232A0
#define LBUS_GFX 0xC98234A0

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

DOLBY_DEVICE_DATA_T gsDolbyReg;
UINT32 gVDOFramePtr[2] = {VDO_FRAME_BUFFER1,VDO_FRAME_BUFFER2};
UINT32 gForceMDPath_M17 = 0;
UINT32 gunvdecport[2];
UINT32 gungpuport[2];
UINT32 gungfxport[2];

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static int DE_DHDR_IP_REG_InitDevHandler(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);
static int DE_DHDR_IP_REG_Phy2Virt(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);
static int DE_DHDR_IP_REG_GetLBUSDefaultports(void);
static int DE_DHDR_IP_REG_SetLBUSPorts(UINT32 i_enable);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/


/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialization of H/W Address
 *
 * @param *o_PtrDolbyInit [OUT] H/W Addresses
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
static int DE_DHDR_IP_REG_InitDevHandler(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyInit);

		o_PtrDolbyInit->sCompDMRegMap.unHwAddr			= DOLBY_HAL_M17_CTRL_ADDR;
		o_PtrDolbyInit->sCompDMRegMap.unSize			= DOLBY_HAL_M17_CTRL_SIZE;
		o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr		= NULL;
		if(gForceMDPath_M17 == 0){
			if (lx_chip_rev() >= LX_CHIP_REV(M17,C0))
				o_PtrDolbyInit->sMDRegMap.unHwAddr		= DOLBY_HAL_M17C0_HDMI_MD_ADDR;
			else
				o_PtrDolbyInit->sMDRegMap.unHwAddr		= DOLBY_HAL_M17A0_HDMI_MD_ADDR;
		}
		o_PtrDolbyInit->sMDRegMap.unSize				= DOLBY_HAL_M17_HDMI_TOTMD_SIZE;
		o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr			= NULL;

		o_PtrDolbyInit->sOTTMDRegMap.unHwAddr			= DOLBY_HAL_M17_OTTMD_DDR_ADDR;
		o_PtrDolbyInit->sOTTMDRegMap.unSize				= DOLBY_HAL_M17_OTTMD_DDR_SIZE;
		o_PtrDolbyInit->sOTTMDRegMap.unPtrVirtAddr		= NULL;

		o_PtrDolbyInit->sLUTDDRRegMap.unHwAddr			= DOLBY_HAL_M17_LUT_DDR_ADDR;
		o_PtrDolbyInit->sLUTDDRRegMap.unSize			= DOLBY_HAL_M17_LUT_DDR_SIZE;
		o_PtrDolbyInit->sLUTDDRRegMap.unPtrVirtAddr		= NULL;

		o_PtrDolbyInit->sCompDMDDRRegMap.unHwAddr		= DOLBY_HAL_M17_IP_CONFIG_DDR_ADDR;
		o_PtrDolbyInit->sCompDMDDRRegMap.unSize			= DOLBY_HAL_M17_IP_CONFIG_DDR_SIZE;
		o_PtrDolbyInit->sCompDMDDRRegMap.unPtrVirtAddr	= NULL;

		o_PtrDolbyInit->sFrameIdxRegMap.unHwAddr		= DOLBY_HAL_M17_FRAME_INDEX_BASE;
		o_PtrDolbyInit->sFrameIdxRegMap.unSize			= DOLBY_HAL_M17_FRAME_INDEX_SIZE;
		o_PtrDolbyInit->sFrameIdxRegMap.unPtrVirtAddr	= NULL;

		o_PtrDolbyInit->sDoviDDRMap.unHwAddr			= HDR_BASE_ADDRESS;
		if(lx_chip_rev() >= LX_CHIP_REV(M17,C0))
			o_PtrDolbyInit->sDoviDDRMap.unSize			= VIDEO_M17_HDR_IPC_MEM_SIZE_C0;
		else
			o_PtrDolbyInit->sDoviDDRMap.unSize			= VIDEO_M17_HDR_IPC_MEM_SIZE;

		o_PtrDolbyInit->sDoviDDRMap.unPtrVirtAddr		= NULL;

		o_PtrDolbyInit->eDolbyDrvState 					= DOLBY_UNINTIALIZED;
		o_PtrDolbyInit->unFrameNum						= 0;
		o_PtrDolbyInit->unHDRIntrIrqNum					= DOLBY_HAL_M17_HDRINTRIRQ_NUMBER;
		o_PtrDolbyInit->unMCUIntrIrqNum					= DOLBY_HAL_M17_MCUIRQ_NUMBER;
		if(o_PtrDolbyInit->eCurMode == LX_DOLBY_HDMI_LL_MODE)
			o_PtrDolbyInit->eHdmiDescMethod				= LX_DOLBY_HDMI_NOMD_DESC;
		else if(lx_chip_rev() >= LX_CHIP_REV(M17,C0))
			o_PtrDolbyInit->eHdmiDescMethod				= LX_DOLBY_HDMI_MDHW_DESC;
		else
			o_PtrDolbyInit->eHdmiDescMethod				= LX_DOLBY_HDMI_MDSW_DESC;

	}while(0);

	ret = RET_OK;
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Convert Physical Address to Virtual Address
 *
 * @param void
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
static int DE_DHDR_IP_REG_Phy2Virt(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyInit);
		
		if(o_PtrDolbyInit->eCurMode == LX_DOLBY_HDMI_MODE ) {
			if(o_PtrDolbyInit->eHdmiDescMethod == LX_DOLBY_HDMI_MDHW_DESC) {
				if(o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr == NULL) {
					o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr = ioremap(o_PtrDolbyInit->sMDRegMap.unHwAddr,o_PtrDolbyInit->sMDRegMap.unSize);
					DE_NOTI("Info: MD H/W & Virtual Addr 0x%x %p\n",o_PtrDolbyInit->sMDRegMap.unHwAddr,o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr);
				}
				else {
					iounmap((void *)o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr);
					o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr = ioremap(o_PtrDolbyInit->sMDRegMap.unHwAddr,o_PtrDolbyInit->sMDRegMap.unSize);
				}
			}
		}
		else if(o_PtrDolbyInit->eCurMode == LX_DOLBY_HDMI_LL_MODE) {
			//need to add code for LL mode if any memory related
			DE_NOTI("HDMI LL Mode\n");
		}
		if(o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr == NULL) {
			o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr = ioremap(o_PtrDolbyInit->sCompDMRegMap.unHwAddr,o_PtrDolbyInit->sCompDMRegMap.unSize);
			DE_NOTI("Info: MD H/W & Virtual Addr 0x%x %p\n",o_PtrDolbyInit->sCompDMRegMap.unHwAddr,o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr);
		}
		else {
			iounmap((void *)o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr);
			o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr = ioremap(o_PtrDolbyInit->sCompDMRegMap.unHwAddr,o_PtrDolbyInit->sCompDMRegMap.unSize);
		}
	}while(0);

	ret = RET_OK;
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize memory,irq & resource of  Dolby driver for OTT/HDMI mode
 *
 * @param *io_PtrDolbyInit [IN/OUT] takes dolby mode as input & gives 3D,TC & G2L LUT address as output
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit)
{
	int ret = RET_ERROR;
	UINT32 unchipver = lx_chip_rev();
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	DE_NOTI("Info: Dolby Driver Init Mode [%d]", io_PtrDolbyInit->eCurMode);

	do{
		DOLBY_HAL_CHECK_NULL(io_PtrDolbyInit);
		
		ret = DE_DHDR_IP_REG_InitDevHandler(io_PtrDolbyInit);
		if(ret != RET_OK) {
			DE_ERROR("Error: Init Dev Handler Failed\n");
			break;
		}

		ret = DE_DHDR_IP_REG_Phy2Virt(io_PtrDolbyInit);
		if(io_PtrDolbyInit->eCurMode == LX_DOLBY_HDMI_MODE && (((unchipver>>8) == LX_CHIP_M17) && ((unchipver&0x00FF) >= 0xC0))) {
			ret = DE_DHDR_IP_REG_GetLBUSDefaultports();
			if(ret != RET_OK)
				break;
			ret = DE_DHDR_IP_REG_SetLBUSPorts(1);
		}
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Reads the IRQ status of HDR/MCU interrupt
 *
 * @param *o_PtrHdrIrqStatus [OUT] to get the IRQ status of HDR,MCU Interrupt Status
 *
 * @param i_unFlag [IN] Flag to decide MCU/HDR
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Set the IRQ status of HDR/MCU interrupt
 *
 * @param *o_PtrHdrIrqStatus [IN] to set the IRQ status of HDR,MCU Interrupt Status
 *
 * @param i_unFlag [IN] Flag to decide MCU/HDR
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Gets the HDMI DM MetaData
 *
 * @param *o_PtrMetaData [OUT] HDMI DM MetaData
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_sptrDolby,LX_DOLBY_DM_MD_T *o_sptrMetaData)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_sptrDolby);
		DOLBY_HAL_CHECK_NULL(o_sptrMetaData);
		
		if(i_sptrDolby->sMDRegMap.unPtrVirtAddr != NULL) {
			/*Copy HDMI DM MetaData from Dolby HDR IP*/
			memcpy((void *)o_sptrMetaData->ucDMMetaData,(void *)i_sptrDolby->sMDRegMap.unPtrVirtAddr,DOLBY_HAL_M17_HDMI_TOTMD_SIZE);
			o_sptrMetaData->usSize = DOLBY_HAL_M17_HDMI_TOTMD_SIZE;
		}
		else {
			DE_ERROR("Error: [%s:%d] Device Driver access without initialization.\n", __F__, __L__);
			return RET_ERROR;
		}
	}while(0);

	return RET_OK;
}

#define FPGA_WORKAROUND

int DE_DHDR_IP_REG_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	
	do {
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}
/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Configures the Composer & DM Dolby HDR IP
 *
 * @param *i_PtrConfig [IN] Composer & DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}


/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief  Get Composer & DM register values from Dolby HDR IP
 *
 * @param *i_PtrConfig [IN] Composer & DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_PtrDolby);
		DOLBY_HAL_CHECK_NULL(i_PtrConfig);

		if(i_PtrDolby->eCurMode== LX_DOLBY_OTT_MODE){
			ret = DE_DHDR_IP_REG_GetCompConfig(i_PtrDolby,&i_PtrConfig->sCompRegMap);
			ret = DE_DHDR_IP_REG_GetDMConfig(i_PtrDolby,&i_PtrConfig->sDMRegMap);
		}
		else{
			ret = DE_DHDR_IP_REG_GetDMConfig(i_PtrDolby,&i_PtrConfig->sDMRegMap);
		}

		DE_NOTI("Info: Get REG Config DOne!!\n");
		
	}while(0);

	ret = RET_OK;
	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Configures the Composer & DM Dolby HDR IP
 *
 * @param *i_PtrCompConfig [IN] Composer register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_SetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_COMP_REG_T *i_PtrCompConfig)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Get Composer register values from Dolby HDR IP
 *
 * @param *i_PtrCompConfig [IN] Composer register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_GetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_COMP_REG_T *i_PtrCompConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_PtrDolby);
		DOLBY_HAL_CHECK_NULL(i_PtrCompConfig);

		if(i_PtrDolby->sCompDMRegMap.unPtrVirtAddr != NULL) {
			memcpy((void *)i_PtrCompConfig,(void *)(i_PtrDolby->sCompDMRegMap.unPtrVirtAddr + COMPOSER_OFFSET),sizeof(LX_DOLBY_COMP_REG_T));			
		}
		else {
			DE_ERROR("Error: [%s:%d]  Device Driver access without initialization.\n", __F__, __L__);
		}
	}while(0);

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Configures the Composer & DM Dolby HDR IP
 *
 * @param *i_PtrDMConfig [IN] DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_SetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_REG_T *i_PtrDMConfig)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief  Get DM register values from Dolby HDR IP
 *
 * @param *i_PtrDMConfig [IN] DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_GetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_REG_T *i_PtrDMConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_PtrDolby);
		DOLBY_HAL_CHECK_NULL(i_PtrDMConfig);

		if(i_PtrDolby->sCompDMRegMap.unPtrVirtAddr != NULL) {
			memcpy((void *)i_PtrDMConfig,(void *)(i_PtrDolby->sCompDMRegMap.unPtrVirtAddr + DM_OFFSET),sizeof(LX_DOLBY_DM_REG_T));
		}
		else {
			DE_ERROR("Error: [%s:%d]  Device Driver access without initialization.\n", __F__, __L__);
		}
	}while(0);

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Configures the 3D,TC & G2L DDR Address to Dolby HDR IP
 *
 * @param *i_PtrFrameNum [IN] Frame Number
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
//CR::Need to verify if reconfigure the 3D & TC LUt address
int DE_DHDR_IP_REG_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief PIC start for Dolby HDR IP
 *
 * @param void
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DE_NOTI("Info: Not Implemented Kept it for future\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Unintialization of dolby driver
 *
 * @param void
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyUninit)
{
	int ret = RET_ERROR;
	UINT32 unchipver = lx_chip_rev();
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyUninit);
		
		if(o_PtrDolbyUninit->eCurMode == LX_DOLBY_HDMI_MODE) {
			if(o_PtrDolbyUninit->eHdmiDescMethod == LX_DOLBY_HDMI_MDHW_DESC) {
				if(o_PtrDolbyUninit->sMDRegMap.unPtrVirtAddr != NULL) {
					iounmap((void *)o_PtrDolbyUninit->sMDRegMap.unPtrVirtAddr);
					o_PtrDolbyUninit->sMDRegMap.unPtrVirtAddr = NULL;
				}
			}
		}
		if(o_PtrDolbyUninit->sCompDMRegMap.unPtrVirtAddr != NULL) {
			iounmap((void *)o_PtrDolbyUninit->sCompDMRegMap.unPtrVirtAddr);
			o_PtrDolbyUninit->sCompDMRegMap.unPtrVirtAddr = NULL;
		}
		if(o_PtrDolbyUninit->eCurMode == LX_DOLBY_HDMI_MODE && (((unchipver>>8) == LX_CHIP_M17) && ((unchipver&0x00FF) >= 0xC0))) {
			ret = DE_DHDR_IP_REG_SetLBUSPorts(0);
		}

	}while(0);

	ret = RET_OK;
	return ret;
}

/**
 * @callgraph
 * @callergraph
 * @brief select from which hw block to read HDMI Metadata
 *
 * @param e_md_path[IN] enum to select md hw path
 *
 * @return RET_OK(0) if success, <0 for otherwise
 */
int DE_DHDR_IP_REG_SetMdPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		if(e_md_path == E_MD_IPP_M0)
			io_PtrDolby->sMDRegMap.unHwAddr		= DOLBY_HAL_M17C0_HDMI_MD_ADDR;
		else if(e_md_path == E_MD_HDR_HDMI_HW)
			io_PtrDolby->sMDRegMap.unHwAddr		= DOLBY_HAL_M17A0_HDMI_MD_ADDR;
		else {
			gForceMDPath_M17 = 0;
			DE_ERROR("Invalid Md path specified. Not changing HDMI MD address Mapping and turn off force mode gForceMDPath_M17 %d\n",gForceMDPath_M17);			
			ret = RET_ERROR;
			break;
		}
		io_PtrDolby->sMDRegMap.unSize	= DOLBY_HAL_M17_HDMI_TOTMD_SIZE;
		gForceMDPath_M17 = 1;
		if(io_PtrDolby->sMDRegMap.unPtrVirtAddr){
			iounmap((void *)io_PtrDolby->sMDRegMap.unPtrVirtAddr);
			io_PtrDolby->sMDRegMap.unPtrVirtAddr = (volatile UINT32 *)ioremap(io_PtrDolby->sMDRegMap.unHwAddr,io_PtrDolby->sMDRegMap.unSize);
		}else{
			io_PtrDolby->sMDRegMap.unPtrVirtAddr = (volatile UINT32 *)ioremap(io_PtrDolby->sMDRegMap.unHwAddr,io_PtrDolby->sMDRegMap.unSize);
		}
		DE_ERROR("Info: MD H/W & Virtual Addr 0x%x %p force mode gForceMDPath_M17 %d\n",io_PtrDolby->sMDRegMap.unHwAddr,io_PtrDolby->sMDRegMap.unPtrVirtAddr,gForceMDPath_M17);
	}while(0);

	return ret;
}

static int DE_DHDR_IP_REG_GetLBUSDefaultports(void)
{
	void *unPtrVirtVdecAddr = NULL;
	void *unPtrVirtGpuAddr = NULL;
	void *unPtrVirtGfxAddr = NULL;

	do {
		unPtrVirtVdecAddr = ioremap(LBUS_VDEC_M0+8,8);
		if(!unPtrVirtVdecAddr) {
			DE_ERROR("Error:: Memory Map failed for LBUS VDEC_M0\n");
			return RET_ERROR;
		}
		unPtrVirtGpuAddr = ioremap(LBUS_GPU+8,8);
		if(!unPtrVirtGpuAddr) {
			DE_ERROR("Error:: Memory Map failed for LBUS GPU_M0\n");
			if(unPtrVirtVdecAddr)
				iounmap(unPtrVirtVdecAddr);
			return RET_ERROR;
		}
		unPtrVirtGfxAddr = ioremap(LBUS_GFX+8,8);
		if(!unPtrVirtGfxAddr) {
			DE_ERROR("Error:: Memory Map failed for LBUS GFX M0\n");
			if(unPtrVirtVdecAddr)
				iounmap(unPtrVirtVdecAddr);
			if(unPtrVirtGfxAddr)
				iounmap(unPtrVirtGpuAddr);
			return RET_ERROR;
		}

		gunvdecport[0] = ioread32(unPtrVirtVdecAddr);
		gunvdecport[1] = ioread32(unPtrVirtVdecAddr+4);
		gungpuport[0] = ioread32(unPtrVirtGpuAddr);
		gungpuport[1] = ioread32(unPtrVirtGpuAddr+4);
		gungfxport[0] = ioread32(unPtrVirtGfxAddr);
		gungfxport[1] = ioread32(unPtrVirtGfxAddr+ 4);

		iounmap(unPtrVirtVdecAddr);
		iounmap(unPtrVirtGpuAddr);
		iounmap(unPtrVirtGfxAddr);
	}while(0);

	return RET_OK;
}

static int DE_DHDR_IP_REG_SetLBUSPorts(UINT32 i_enable)
{

	void *unPtrVirtVdecAddr = NULL;
	void *unPtrVirtGpuAddr = NULL;
	void *unPtrVirtGfxAddr = NULL;
	UINT32 unval[3] = {0,};

	do {
		unPtrVirtVdecAddr = ioremap(LBUS_VDEC_M0,16);
		if(!unPtrVirtVdecAddr) {
			DE_ERROR("Error:: Memory Map failed for LBUS VDEC_M0\n");
			return RET_ERROR;
		}
		unPtrVirtGpuAddr = ioremap(LBUS_GPU,16);
		if(!unPtrVirtGpuAddr) {
			DE_ERROR("Error:: Memory Map failed for LBUS VGPU M0\n");
			if(unPtrVirtVdecAddr)
				iounmap(unPtrVirtVdecAddr);
			return RET_ERROR;
		}
		unPtrVirtGfxAddr = ioremap(LBUS_GFX,16);
		if(!unPtrVirtGfxAddr) {
			DE_ERROR("Error:: Memory Map failed for LBUS GFX M0\n");
			if(unPtrVirtVdecAddr)
				iounmap(unPtrVirtVdecAddr);
			if(unPtrVirtGfxAddr)
				iounmap(unPtrVirtGpuAddr);
			return RET_ERROR;
		}

		if(i_enable) {
			/*Btop VDEC M0*/
			unval[0] = ioread32(unPtrVirtVdecAddr);
			unval[0] |= (0x44<<20)|(0x44<<4);
			iowrite32(unval[0],unPtrVirtVdecAddr);

			unval[1] = gunvdecport[0];
			unval[1] &= 0xFFCCFFFF;
			unval[2] = gunvdecport[1];
			unval[2] &= 0xFFCCFFFF;
			iowrite32(unval[1],unPtrVirtVdecAddr+8);
			iowrite32(unval[2],unPtrVirtVdecAddr+12);

			/*Btop GPU M0*/
			unval[0] = ioread32(unPtrVirtGpuAddr);
			unval[0] |= (0x44<<20)|(0x44<<4);
			iowrite32(unval[0],unPtrVirtGpuAddr);

			unval[1] = gungpuport[0];
			unval[1] &= 0xFFCCFFFF;
			unval[1] |= (0x11<<16);
			unval[2] = gungpuport[1];
			unval[2] &= 0xFFCCFFFF;
			unval[2] |= (0x11<<16);
			iowrite32(unval[1],unPtrVirtGpuAddr+8);
			iowrite32(unval[2],unPtrVirtGpuAddr+12);

			/*Btop GFX M0*/
			unval[0] = ioread32(unPtrVirtGfxAddr);
			unval[0] |= (0x44<<20)|(0x44<<4);
			iowrite32(unval[0],unPtrVirtGfxAddr);

			unval[1] = gungfxport[0];
			unval[1] &= 0xFFCCFFFF;
			unval[1] |= (0x11<<16);
			unval[2] = gungfxport[1];
			unval[2] &= 0xFFCCFFFF;
			unval[2] |= (0x11<<16);
			iowrite32(unval[1],unPtrVirtGfxAddr+8);
			iowrite32(unval[2],unPtrVirtGfxAddr+12);
			DE_NOTI("Info: LBUS VDEC_M0,GPU_M0 and GFX_M0 ports changed to P0,P1,P1 for HDMI STD on\n");

		}
		else {
			/*Btop VDEC M0*/
			iowrite32(gunvdecport[0],unPtrVirtVdecAddr+8);
			iowrite32(gunvdecport[1],unPtrVirtVdecAddr+12);

			/*Btop GPU M0*/
			iowrite32(gungpuport[0],unPtrVirtGpuAddr+8);
			iowrite32(gungpuport[1],unPtrVirtGpuAddr+12);

			/*Btop GFX M0*/
			unval[0] = ioread32(unPtrVirtGfxAddr);
			unval[0] |= (0x44<<20)|(0x44<<4);
			iowrite32(unval[0],unPtrVirtGfxAddr);

			unval[1] = gungfxport[0];
			unval[1] &= 0xFFCCFFFF;
			unval[1] |= (0x22<<16);
			unval[2] = gungfxport[1];
			unval[2] &= 0xFFCCFFFF;
			unval[2] |= (0x22<<16);
			iowrite32(unval[1],unPtrVirtGfxAddr+8);
			iowrite32(unval[2],unPtrVirtGfxAddr+12);
			DE_NOTI("Info: LBUS VDEC_M0,GPU_M0 and GFX_M0 ports changed to Default HDMI STD off\n");
		}

		iounmap(unPtrVirtVdecAddr);
		iounmap(unPtrVirtGpuAddr);
		iounmap(unPtrVirtGfxAddr);
	}while(0);

	return RET_OK;
}
/**  @} */
