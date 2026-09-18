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
 * modifier   harish chandra singh (harish.singh@lge.com)
 * version	  1.0
 * date		  2023.04.17
 * note		  Additional information.
 * Added support for o26 fpga/soc
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
#include "dolby_reg_o26.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

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


/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static int DE_DHDR_IP_REG_O26_InitDevHandler(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);
static int DE_DHDR_IP_REG_O26_Phy2Virt(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit);

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
static int DE_DHDR_IP_REG_O26_InitDevHandler(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
{
	int ret = RET_ERROR;

	/*We don't need H/W mapping as we are using shared memory. F/w is sharing metadata in that. */
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyInit);

		/* Initialize physical address for HDMI metadata */
		o_PtrDolbyInit->sMDRegMap.unHwAddr = DOLBY_HAL_O26A0_HDMI_MD_ADDR;
		o_PtrDolbyInit->sMDRegMap.unSize = DOLBY_HAL_O26_HDMI_TOTMD_SIZE;
		o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr = NULL;

		o_PtrDolbyInit->eDolbyDrvState = DOLBY_UNINTIALIZED;

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
static int DE_DHDR_IP_REG_O26_Phy2Virt(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyInit);

		if(o_PtrDolbyInit->eCurMode == LX_DOLBY_HDMI_MODE){
			if(o_PtrDolbyInit->eHdmiDescMethod == LX_DOLBY_HDMI_MDHW_DESC){
				if(o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr == NULL){
					o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr = (volatile UINT32 *)ioremap(o_PtrDolbyInit->sMDRegMap.unHwAddr,o_PtrDolbyInit->sMDRegMap.unSize);
					DE_NOTI("Info: MD H/W and Virtual Addr 0x%x %p\n",o_PtrDolbyInit->sMDRegMap.unHwAddr,o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr);
				}
				else {
					iounmap(o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr);
					o_PtrDolbyInit->sMDRegMap.unPtrVirtAddr = (volatile UINT32 *)ioremap(o_PtrDolbyInit->sMDRegMap.unHwAddr,o_PtrDolbyInit->sMDRegMap.unSize);
				}
			}
		}
		else
			DE_NOTI("Info: No mapping required [%d] mode",o_PtrDolbyInit->eCurMode);
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
int DE_DHDR_IP_REG_O26_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	DE_NOTI("Info: Dolby Driver Init Mode [%d]", io_PtrDolbyInit->eCurMode);

	do{
		DOLBY_HAL_CHECK_NULL(io_PtrDolbyInit);
		ret = DE_DHDR_IP_REG_O26_InitDevHandler(io_PtrDolbyInit);
		if(ret != RET_OK) {
			DE_ERROR("Error: Init Dev Handler Failed\n");
			break;
		}

		ret = DE_DHDR_IP_REG_O26_Phy2Virt(io_PtrDolbyInit);
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
int DE_DHDR_IP_REG_O26_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag)
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
int DE_DHDR_IP_REG_O26_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrIrqStatus,int i_unFlag)
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
int DE_DHDR_IP_REG_O26_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_sptrDolby,LX_DOLBY_DM_MD_T *o_sptrMetaData)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_sptrDolby);
		DOLBY_HAL_CHECK_NULL(o_sptrMetaData);
		if(i_sptrDolby->sMDRegMap.unPtrVirtAddr != NULL){
			memcpy(o_sptrMetaData->ucDMMetaData,(void *)i_sptrDolby->sMDRegMap.unPtrVirtAddr,DOLBY_HAL_O26_HDMI_TOTMD_SIZE);
			o_sptrMetaData->usSize = DOLBY_HAL_O26_HDMI_TOTMD_SIZE;
			ret = RET_OK;
		}
		else {
			DE_NOTI("Error: [%s:%d] HDMI metadata mapping failed\n",__F__,__L__);
		}
	}while(0);

	return ret;
}

#define FPGA_WORKAROUND

int DE_DHDR_IP_REG_O26_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId)
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
int DE_DHDR_IP_REG_O26_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
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
int DE_DHDR_IP_REG_O26_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(i_PtrDolby);
		DOLBY_HAL_CHECK_NULL(i_PtrConfig);

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
int DE_DHDR_IP_REG_O26_SetCompConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_IP_REG_T *i_PtrCompConfig)
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
 * @brief Configures the Composer & DM Dolby HDR IP
 *
 * @param *i_PtrDMConfig [IN] DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_REG_O26_SetDMConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_IP_REG_T *i_PtrDMConfig)
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
 * @brief Configures the 3D,TC & G2L DDR Address to Dolby HDR IP
 *
 * @param *i_PtrFrameNum [IN] Frame Number
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
//CR::Need to verify if reconfigure the 3D & TC LUt address
int DE_DHDR_IP_REG_O26_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum)
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
int DE_DHDR_IP_REG_O26_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby)
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
int DE_DHDR_IP_REG_O26_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyUninit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		DOLBY_HAL_CHECK_NULL(o_PtrDolbyUninit);
		if(o_PtrDolbyUninit->eCurMode == LX_DOLBY_HDMI_MODE){
			if(o_PtrDolbyUninit->sMDRegMap.unPtrVirtAddr){
				iounmap(o_PtrDolbyUninit->sMDRegMap.unPtrVirtAddr);
				o_PtrDolbyUninit->sMDRegMap.unPtrVirtAddr = NULL;
                        }
		}
		DE_NOTI("Unintialization completed");
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
int DE_DHDR_IP_REG_O26_SetMdPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path)
{
	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do{
		if(e_md_path == E_MD_IPP_M0 || e_md_path == E_MD_HDR_HDMI_HW)
			io_PtrDolby->sMDRegMap.unHwAddr = DOLBY_HAL_O26A0_HDMI_MD_ADDR;
		else{
			DE_NOTI("Info: Not Supported.\n");
			return RET_ERROR;
		}

		io_PtrDolby->sMDRegMap.unSize = DOLBY_HAL_O26_HDMI_TOTMD_SIZE;
	}while(0);

	return ret;
}


/**  @} */
