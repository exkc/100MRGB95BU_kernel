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
#include "dolby_reg_o18.h"

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

//DOLBY_DEVICE_DATA_T gsDolbyReg;
//UINT32 gVDOFramePtr[2] = {VDO_FRAME_BUFFER1,VDO_FRAME_BUFFER2};
UINT32 gForceMDPath_O18 = 0;

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static int DE_DHDR_IP_REG_O18_InitDevHandler(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);
static int DE_DHDR_IP_REG_O18_Phy2Virt(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);

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
static int DE_DHDR_IP_REG_O18_InitDevHandler(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyInit);

		o_PtrDolbyInit->sCompDMRegMap.unHwAddr			= DOLBY_HAL_O18_CTRL_ADDR;
		o_PtrDolbyInit->sCompDMRegMap.unSize			= DOLBY_HAL_O18_CTRL_SIZE;
		o_PtrDolbyInit->sCompDMRegMap.unPtrVirtAddr		= NULL;
		if(gForceMDPath_O18 == 0){
			o_PtrDolbyInit->sMDRegMap.unHwAddr				= DOLBY_HAL_O18_HDMI_MD_ADDR;
		}
		o_PtrDolbyInit->sMDRegMap.unSize				= DOLBY_HAL_O18_HDMI_TOTMD_SIZE;
		o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr			= NULL;

		o_PtrDolbyInit->sOTTMDRegMap.unHwAddr			= DOLBY_HAL_O18_OTTMD_DDR_ADDR;
		o_PtrDolbyInit->sOTTMDRegMap.unSize				= DOLBY_HAL_O18_OTTMD_DDR_SIZE;
		o_PtrDolbyInit->sOTTMDRegMap.unPtrVirtAddr		= NULL;

		o_PtrDolbyInit->sLUTDDRRegMap.unHwAddr			= DOLBY_HAL_O18_LUT_DDR_ADDR;
		o_PtrDolbyInit->sLUTDDRRegMap.unSize			= DOLBY_HAL_O18_LUT_DDR_SIZE;
		o_PtrDolbyInit->sLUTDDRRegMap.unPtrVirtAddr		= NULL;

		o_PtrDolbyInit->sCompDMDDRRegMap.unHwAddr		= DOLBY_HAL_O18_IP_CONFIG_DDR_ADDR;
		o_PtrDolbyInit->sCompDMDDRRegMap.unSize			= DOLBY_HAL_O18_IP_CONFIG_DDR_SIZE;
		o_PtrDolbyInit->sCompDMDDRRegMap.unPtrVirtAddr	= NULL;

		o_PtrDolbyInit->sFrameIdxRegMap.unHwAddr		= DOLBY_HAL_O18_FRAME_INDEX_BASE;
		o_PtrDolbyInit->sFrameIdxRegMap.unSize			= DOLBY_HAL_O18_FRAME_INDEX_SIZE;
		o_PtrDolbyInit->sFrameIdxRegMap.unPtrVirtAddr	= NULL;

		o_PtrDolbyInit->sDoviDDRMap.unHwAddr			= HDR_BASE_ADDRESS;
		o_PtrDolbyInit->sDoviDDRMap.unSize				= VIDEO_O18_HDR_IPC_MEM_SIZE;
		o_PtrDolbyInit->sDoviDDRMap.unPtrVirtAddr		= NULL;

		o_PtrDolbyInit->eDolbyDrvState 					= DOLBY_UNINTIALIZED;
		o_PtrDolbyInit->unFrameNum						= 0;
		o_PtrDolbyInit->unHDRIntrIrqNum					= DOLBY_HAL_O18_HDRINTRIRQ_NUMBER;
		o_PtrDolbyInit->unMCUIntrIrqNum					= DOLBY_HAL_O18_MCUIRQ_NUMBER;

		if(o_PtrDolbyInit->eCurMode == LX_DOLBY_HDMI_LL_MODE)
			o_PtrDolbyInit->eHdmiDescMethod				= LX_DOLBY_HDMI_NOMD_DESC;
		else
			o_PtrDolbyInit->eHdmiDescMethod				= LX_DOLBY_HDMI_MDHW_DESC;

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
static int DE_DHDR_IP_REG_O18_Phy2Virt(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
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
int DE_DHDR_IP_REG_O18_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	DE_NOTI("Info: Dolby Driver Init Mode [%d]", io_PtrDolbyInit->eCurMode);

	do{
		DOLBY_HAL_CHECK_NULL(io_PtrDolbyInit);
		
		ret = DE_DHDR_IP_REG_O18_InitDevHandler(io_PtrDolbyInit);
		if(ret != RET_OK) {
			DE_ERROR("Error: Init Dev Handler Failed\n");
			break;
		}

		ret = DE_DHDR_IP_REG_O18_Phy2Virt(io_PtrDolbyInit);
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
int DE_DHDR_IP_REG_O18_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag)
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
int DE_DHDR_IP_REG_O18_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag)
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
int DE_DHDR_IP_REG_O18_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_sptrDolby,LX_DOLBY_DM_MD_T *o_sptrMetaData)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_sptrDolby);
		DOLBY_HAL_CHECK_NULL(o_sptrMetaData);
		
		if(i_sptrDolby->sMDRegMap.unPtrVirtAddr != NULL) {
			/*Copy HDMI DM MetaData from Dolby HDR IP*/
			memcpy((void *)o_sptrMetaData->ucDMMetaData,(void *)i_sptrDolby->sMDRegMap.unPtrVirtAddr,DOLBY_HAL_O18_HDMI_TOTMD_SIZE);
			o_sptrMetaData->usSize = DOLBY_HAL_O18_HDMI_TOTMD_SIZE;
		}
		else {
			DE_ERROR("Error: [%s:%d] Device Driver access without initialization.\n", __F__, __L__);
			return RET_ERROR;
		}
	}while(0);

	return RET_OK;
}

#define FPGA_WORKAROUND

int DE_DHDR_IP_REG_O18_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId)
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
int DE_DHDR_IP_REG_O18_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
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
int DE_DHDR_IP_REG_O18_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_PtrDolby);
		DOLBY_HAL_CHECK_NULL(i_PtrConfig);

		if(i_PtrDolby->eCurMode== LX_DOLBY_OTT_MODE){
			ret = DE_DHDR_IP_REG_O18_GetCompConfig(i_PtrDolby,&i_PtrConfig->sCompRegMap);
			ret = DE_DHDR_IP_REG_O18_GetDMConfig(i_PtrDolby,&i_PtrConfig->sDMRegMap);
		}
		else{
			ret = DE_DHDR_IP_REG_O18_GetDMConfig(i_PtrDolby,&i_PtrConfig->sDMRegMap);
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
int DE_DHDR_IP_REG_O18_SetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_COMP_REG_T *i_PtrCompConfig)
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
int DE_DHDR_IP_REG_O18_GetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_COMP_REG_T *i_PtrCompConfig)
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
int DE_DHDR_IP_REG_O18_SetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_REG_T *i_PtrDMConfig)
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
int DE_DHDR_IP_REG_O18_GetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_REG_T *i_PtrDMConfig)
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
int DE_DHDR_IP_REG_O18_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum)
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
int DE_DHDR_IP_REG_O18_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby)
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
int DE_DHDR_IP_REG_O18_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyUninit)
{
	int ret = RET_ERROR;
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
		else if(o_PtrDolbyUninit->eCurMode == LX_DOLBY_HDMI_LL_MODE) {
			//need to add code for LL mode if any memory related
		}

		if(o_PtrDolbyUninit->sCompDMRegMap.unPtrVirtAddr != NULL) {
			iounmap((void *)o_PtrDolbyUninit->sCompDMRegMap.unPtrVirtAddr);
			o_PtrDolbyUninit->sCompDMRegMap.unPtrVirtAddr = NULL;
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
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_O18_SetMdPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		if(e_md_path == E_MD_IPP_M0)
			io_PtrDolby->sMDRegMap.unHwAddr		= DOLBY_HAL_O18_HDMI_MD_ADDR;
		else if(e_md_path == E_MD_HDR_HDMI_HW)
			io_PtrDolby->sMDRegMap.unHwAddr		= DOLBY_HAL_O18_HDMI_HDR_HW_MD_ADDR;
		else {
			gForceMDPath_O18 = 0;
			DE_ERROR("Invalid Md path specified. Not changing HDMI MD address Mapping Mapping and turn off force mode gForceMDPath_O18 %d \n",gForceMDPath_O18);			
			ret = RET_ERROR;
			break;
		}
		io_PtrDolby->sMDRegMap.unSize	= DOLBY_HAL_O18_HDMI_TOTMD_SIZE;
		gForceMDPath_O18 = 1;
		if(io_PtrDolby->sMDRegMap.unPtrVirtAddr){
			iounmap((void *)io_PtrDolby->sMDRegMap.unPtrVirtAddr);
			io_PtrDolby->sMDRegMap.unPtrVirtAddr = (volatile UINT32 *)ioremap(io_PtrDolby->sMDRegMap.unHwAddr,io_PtrDolby->sMDRegMap.unSize);
		}else{
			io_PtrDolby->sMDRegMap.unPtrVirtAddr = (volatile UINT32 *)ioremap(io_PtrDolby->sMDRegMap.unHwAddr,io_PtrDolby->sMDRegMap.unSize);
		}
		DE_ERROR("Info: MD H/W & Virtual Addr 0x%x %p force mode gForceMDPath_O18 %d\n",io_PtrDolby->sMDRegMap.unHwAddr,io_PtrDolby->sMDRegMap.unPtrVirtAddr,gForceMDPath_O18);
	}while(0);

	return ret;
}


/**  @} */
