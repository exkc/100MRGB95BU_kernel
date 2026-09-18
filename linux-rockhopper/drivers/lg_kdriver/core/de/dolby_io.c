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

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_qkb.h"
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <asm/uaccess.h>
#include <asm/io.h>


#include "base_types.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "de_kapi.h"
#include "dolby_io.h"
//#include "dolby_int.h"
#include "hal/dolby_hal.h"

#include "de_def.h"
#include "hal/ipc_hal.h"
#include "de_hal.h"
#include "de_io.h"
#include "mcu/de_ipc.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *----------------------i-----------------------------------------------------------------*/

#define CP_FROM_USER(a,b,c)    if(!io_resume){ret = copy_from_user(a,b,c);if(ret)break;}\
							   else{memcpy(a,b,c);}
#define CP_TO_USER(a,b,c)      if(!io_resume){ret = copy_to_user(a,b,c);if(ret)break;}\
	                           else{memcpy(a,b,c);}
#define CHECK_IO_RET()   if(ret != RET_OK) {DE_ERROR("Error: RET_ERROR ret = %d\n", ret);}
#define CHECK_WIN_ID(param) if(param >= DOLBY_MAX_WIN) {ret = RET_ERROR;DE_ERROR("Error: Unsupported window Id %d for Dolby HDR %d!!\n",param,ret);break;}
#define DOLBY_OTT_MODE_RET 1
#define DOLBY_HDMI_MODE_RET 2
#define DE_DHDR_FPGA

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

extern char io_resume;
extern int gde_mdunblock;


/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

static DOLBY_DEVICE_DATA_T gsDolbyDevHandler[DOLBY_MAX_WIN];
static DECLARE_WAIT_QUEUE_HEAD(wqForMDCallbk);
static UINT32 gMDWakeUpRecvTimeOut;

#if DE_DHDR_IP_SIMUATION
static struct timer_list gsTimer;
void DE_DHDR_IP_INTR_TimerCallback( unsigned long);
#endif

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to initialize memory,irq & resource of  Dolby driver
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_Init(LX_DOLBY_IOCTL_INIT_T *sptr_DolbyParam)
{
	int ret = RET_ERROR;
	int initRet = RET_ERROR;
	LX_DOLBY_IO_MAP_T isDolbyinit;
	LX_DOLBY_IOCTL_INIT_T sParams;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		memcpy((void *)&sParams,(void *)sptr_DolbyParam,sizeof(LX_DOLBY_IOCTL_INIT_T));
		CHECK_WIN_ID(sParams.ucWinID);
		memcpy((void *)&isDolbyinit,(void *)sptr_DolbyParam->sptrDolbyInit,sizeof(LX_DOLBY_IO_MAP_T));
		
		gsDolbyDevHandler[sParams.ucWinID].eCurMode = isDolbyinit.eCurMode;

		if(gsDolbyDevHandler[sParams.ucWinID].eCurMode > LX_DOLBY_HDMI_LL_MODE || gsDolbyDevHandler[sParams.ucWinID].eCurMode == LX_DOLBY_DEFAULT_MODE ) {
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_INIT_ERROR;
			DE_ERROR("Error: Dolby Unsupported Mode[%d]\n",gsDolbyDevHandler[sParams.ucWinID].eCurMode);
			break;
		}

		gde_mdunblock = 0;
	//	DE_ERROR("gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState = %d\n",gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState);
		if(gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState == DOLBY_UNINTIALIZED) {
			ret = DE_DHDR_IP_HAL_Init(&gsDolbyDevHandler[sParams.ucWinID]);
			if(ret == RET_ERROR) {
				gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_INIT_ERROR;
				DE_ERROR("Error: Dolby HAL init %d\n",gsDolbyDevHandler[sParams.ucWinID].eCurMode);
				break;
			}
			gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState = DOLBY_INITIALIZED;
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
		}
		else if(gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState == DOLBY_INITIALIZED) {
			initRet = 1;
			DE_NOTI("Info: Dolby Driver Already Initialized Donei %d!!\n",initRet);
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
		}
		else {
			DE_ERROR("Error: Doby Driver is in Wrong State[%d]\n",gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState);
			break;
		}

		isDolbyinit.sDoviLUTMap.unHwAddr		= gsDolbyDevHandler[sParams.ucWinID].sLUTDDRRegMap.unHwAddr;
		isDolbyinit.sDoviLUTMap.unSize			= gsDolbyDevHandler[sParams.ucWinID].sLUTDDRRegMap.unSize;
		isDolbyinit.sDoviLUTMap.unPtrVirtAddr	= NULL;
		isDolbyinit.sDoviRegMap.unHwAddr		= gsDolbyDevHandler[sParams.ucWinID].sCompDMDDRRegMap.unHwAddr;
		isDolbyinit.sDoviRegMap.unSize			= gsDolbyDevHandler[sParams.ucWinID].sCompDMDDRRegMap.unSize;
		isDolbyinit.sDoviRegMap.unPtrVirtAddr	= NULL;
		isDolbyinit.sSyncInfoMap.unHwAddr		= gsDolbyDevHandler[sParams.ucWinID].sFrameIdxRegMap.unHwAddr;;
		isDolbyinit.sSyncInfoMap.unSize			= gsDolbyDevHandler[sParams.ucWinID].sFrameIdxRegMap.unSize;;
		isDolbyinit.sSyncInfoMap.unPtrVirtAddr	= NULL;
		isDolbyinit.sDoviOTTMDMap.unHwAddr		= gsDolbyDevHandler[sParams.ucWinID].sOTTMDRegMap.unHwAddr;
		isDolbyinit.sDoviOTTMDMap.unSize		= gsDolbyDevHandler[sParams.ucWinID].sOTTMDRegMap.unSize;
		isDolbyinit.sDoviOTTMDMap.unPtrVirtAddr = NULL;
		isDolbyinit.eHdmiDescMethod			= gsDolbyDevHandler[sParams.ucWinID].eHdmiDescMethod;
		gsDolbyDevHandler[sParams.ucWinID].unDolbyInitCount++;
		isDolbyinit.sDoviDDRMap.unHwAddr			= gsDolbyDevHandler[sParams.ucWinID].sDoviDDRMap.unHwAddr;
		isDolbyinit.sDoviDDRMap.unSize			= gsDolbyDevHandler[sParams.ucWinID].sDoviDDRMap.unSize;
		isDolbyinit.sDoviDDRMap.unPtrVirtAddr	= NULL;

		DE_NOTI("Info: %d [%s:%d] Dolby Driver Init Done! OTT Md Addr & Size = 0x%x 0x%x Lut DDR Addr & size= 0x%x 0x%x CompDM DDR Addr & size = 0x%x 0x%x FrameIndex DDR Addr & 0x%x = 0x%x\n",ret,__F__,__L__,gsDolbyDevHandler[sParams.ucWinID].sOTTMDRegMap.unHwAddr,gsDolbyDevHandler[sParams.ucWinID].sOTTMDRegMap.unSize,isDolbyinit.sDoviLUTMap.unHwAddr,isDolbyinit.sDoviLUTMap.unSize,isDolbyinit.sDoviRegMap.unHwAddr,isDolbyinit.sDoviRegMap.unSize,isDolbyinit.sSyncInfoMap.unHwAddr,isDolbyinit.sSyncInfoMap.unSize);
//		DE_ERROR("Info: Dolby Driver Already Initialized Done#####################################i %d!!\n",ret);
		memcpy((void *)sParams.sptrDolbyInit, (void *)&isDolbyinit, sizeof(LX_DOLBY_IO_MAP_T));

		if(gsDolbyDevHandler[sParams.ucWinID].unDolbyInitCount > 1){
			ret = RET_ERROR;
			break;
		}
	}while(0);
	//	DE_ERROR("ip_init retval in driver %d %d count %d\n",initRet,ret,gsDolbyDevHandler[sParams.ucWinID].unDolbyInitCount);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to read HDMI DM MetaData from Dolby HDR IP
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_GetHDMIMetaData(LX_DOLBY_IOCTL_HDMI_MD_T *sptr_DolbyParam,LX_DOLBY_DM_MD_TYPE *sptr_eMDtype,LX_DOLBY_DM_MD_T *sptr_HdmiMd)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_HDMI_MD_T sParams;
	LX_DOLBY_DM_MD_TYPE eCmdType;
	LX_DOLBY_DM_MD_T osHdmiMd;

	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		memcpy((void *)&sParams,(void *)sptr_DolbyParam,sizeof(LX_DOLBY_IOCTL_HDMI_MD_T));
		CHECK_WIN_ID(sParams.ucWinID);
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState,gsDolbyDevHandler[sParams.ucWinID].eCmdErr);
		if(gsDolbyDevHandler[sParams.ucWinID].eCurMode == LX_DOLBY_HDMI_MODE) {
			ret = VIDEO_DHDR_IP_INTR_MetaDataReady();
			if(ret != RET_OK) {
				DE_PRINT("Notice: HDMI MD Ready Interrupt Timeout  %s\n",__F__);
				gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_MD_ERROR;
				break;
			}

			if(gsDolbyDevHandler[sParams.ucWinID].eHdmiDescMethod == LX_DOLBY_HDMI_MDSW_DESC) {
				eCmdType = E_DM_FULL_LE;
				CP_TO_USER((void *)sParams.eMDType,(void *)&eCmdType,sizeof(LX_DOLBY_DM_MD_TYPE));
			}
			else {
				ret = DE_DHDR_IP_HAL_GetHDMIMetaData(&gsDolbyDevHandler[sParams.ucWinID],&osHdmiMd);
				if(ret != RET_OK) {
					DE_ERROR("Error: Dolby Driver Failed to Get HDMI MetaData \n");
					gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_MD_ERROR;
					break;
				}

				eCmdType = E_DM_FULL_BE;

				memcpy((void *)sptr_eMDtype,(void *)&eCmdType,sizeof(LX_DOLBY_DM_MD_TYPE));
				memcpy((void *)&sptr_HdmiMd->ucDMMetaData[0],(void *)&osHdmiMd.ucDMMetaData[0],osHdmiMd.usSize);
				memcpy((void *)&sptr_HdmiMd->usSize,(void *)&osHdmiMd.usSize,sizeof(osHdmiMd.usSize));
			}
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
			DE_TRACE("Info: Dolby Driver HDMI MetaData Done MD size %d!!!",sptr_HdmiMd->usSize);
		}
		else if(gsDolbyDevHandler[sParams.ucWinID].eCurMode == LX_DOLBY_HDMI_LL_MODE){
			eCmdType = E_DM_BASE;
			//CP_TO_USER((void *)sParams.eMDType,(void *)&eCmdType,sizeof(LX_DOLBY_DM_MD_TYPE));
			memcpy((void *)sptr_eMDtype,(void *)&eCmdType,sizeof(LX_DOLBY_DM_MD_TYPE));
			ret = RET_OK;
		}
		else{
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_MD_ERROR;
			DE_ERROR("Error: [%s:%d] Dolby Driver GetMetaData Error %d[Mode:%d State:%d]!!\n",__F__,__L__,gsDolbyDevHandler[sParams.ucWinID].eCmdErr,gsDolbyDevHandler[sParams.ucWinID].eCurMode,gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState);
			ret = RET_ERROR;
			break;
		}
		
	}while(0);
	
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to wait for OTT MD interrupt ready occurs from MCU
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_GetOTTMetaData(LX_DOLBY_OTT_MD_IOCTL_T *sptr_DolbyParam)
{
	int ret = RET_ERROR;

	LX_DOLBY_OTT_MD_IOCTL_T sParam;
	
	do {
		//CP_FROM_USER(&sParam,(void *)arg,sizeof(sParam));
		memcpy((void *)&sParam,(void*)sptr_DolbyParam,sizeof(LX_DOLBY_OTT_MD_IOCTL_T));
		CHECK_WIN_ID(sParam.ucWinID);
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[sParam.ucWinID].eDolbyDrvState,gsDolbyDevHandler[sParam.ucWinID].eCmdErr);

		if(gsDolbyDevHandler[sParam.ucWinID].eCurMode == LX_DOLBY_OTT_MODE || gsDolbyDevHandler[sParam.ucWinID].eCurMode == LX_DOLBY_RF_MODE) {
			ret = VIDEO_DHDR_IP_INTR_MetaDataReady();
			if(ret != RET_OK) {
				DE_PRINT("PRINT: OTT MD Ready Interrupt Timeout  %s\n",__F__);
				gsDolbyDevHandler[sParam.ucWinID].eCmdErr = DOLBY_MD_ERROR;
				break;
			}

			gsDolbyDevHandler[sParam.ucWinID].eCmdErr = DOLBY_OK;
			DE_TRACE("Info: Dolby Driver OTT MetaData Done!!!");
		}
		else {
			DE_ERROR("Error: Dolby Driver Mode[%d] \n",gsDolbyDevHandler[sParam.ucWinID].eCurMode);
			gsDolbyDevHandler[sParam.ucWinID].eCmdErr = DOLBY_MD_ERROR;
			break;
		}
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to configure composer & DM Dolby HDR IP
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_SetConfig(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_CONFIG_REG_T sParams;
	LX_DOLBY_CONFIG_REG_T i_sConfigData;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CP_FROM_USER((void *)&sParams,(void *)arg,sizeof(LX_DOLBY_IOCTL_CONFIG_REG_T));
		CHECK_WIN_ID(sParams.ucWinID);
		CP_FROM_USER((void *)&i_sConfigData,(void *)sParams.sDolbyConfig,sizeof(LX_DOLBY_CONFIG_REG_T));
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState,gsDolbyDevHandler[sParams.ucWinID].eCmdErr);
		
		ret = DE_DHDR_IP_HAL_SetConfig(&gsDolbyDevHandler[sParams.ucWinID],&i_sConfigData);
		if(ret == RET_ERROR) {
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_CONFIG_ERROR;
			DE_ERROR("Error: Dolby HAL Config \n");
			return ret;
		}
		DE_NOTI("Info: DOlby Driver Config Done\n");
		gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to get composer & DM register values from Dolby HDR IP
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_GetConfig(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_CONFIG_REG_T sParams;
	LX_DOLBY_CONFIG_REG_T io_sConfigData;
	LX_DOLBY_COMP_DM_CHANGE_T eCompDMChange;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CP_FROM_USER((void *)&sParams,(void *)arg,sizeof(LX_DOLBY_IOCTL_CONFIG_REG_T));
		CHECK_WIN_ID(sParams.ucWinID);
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState,gsDolbyDevHandler[sParams.ucWinID].eCmdErr);

		ret = DE_DHDR_IP_HAL_GetConfig(&gsDolbyDevHandler[sParams.ucWinID],&io_sConfigData);
		if(ret != RET_OK) {
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_CONFIG_ERROR;
			DE_ERROR("Error: Dolby HAL Config \n");
			break;
		}

		if(gsDolbyDevHandler[sParams.ucWinID].eCurMode == LX_DOLBY_OTT_MODE) {
			eCompDMChange = LX_DOLBY_COMP_DM_CHANGE;
			CP_TO_USER((void *)sParams.sDolbyConfig,(void *)&io_sConfigData,sizeof(LX_DOLBY_CONFIG_REG_T));
			CP_TO_USER((void *)&sParams.sDolbyConfig->eCompDMChange,(void *)&eCompDMChange,sizeof(LX_DOLBY_COMP_DM_CHANGE_T));
		}
		else {
			eCompDMChange = LX_DOLBY_DM_CHANGE;
			CP_TO_USER((void *)sParams.sDolbyConfig,(void *)&io_sConfigData,sizeof(LX_DOLBY_CONFIG_REG_T));
			CP_TO_USER((void *)&sParams.sDolbyConfig->eCompDMChange,(void *)&eCompDMChange,sizeof(LX_DOLBY_COMP_DM_CHANGE_T));
		}
		DE_NOTI("Info: Dolby Get Driver Config Done\n");
		if(sParams.ucWinID < DOLBY_MAX_WIN)
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to configure 3D,TC & G2L LUT DDR Address to Dolby HDR IP
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_SetLut(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_CONFIG_LUT_T sParams;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	
	do {
		CP_FROM_USER((void *)&sParams,(void *)arg,sizeof(UINT32));
		CHECK_WIN_ID(sParams.ucWinID);
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[sParams.ucWinID].eDolbyDrvState,gsDolbyDevHandler[sParams.ucWinID].eCmdErr);

		ret = DE_DHDR_IP_HAL_SetLut(&gsDolbyDevHandler[sParams.ucWinID],sParams.unFrameNum);
		if(ret == RET_ERROR) {
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_LUT_ERROR;
			DE_ERROR("Error: Dolby HAL LUT Config \n");
			return ret;
		}
		gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
		DE_NOTI("Info: Dolby Driver LUT Config Done\n");
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief IOCTL function to start PIC start for Dolby HDR IP
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_Start(unsigned long arg)
{
	int ret = RET_ERROR;
	UINT8 ucWinID;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	
	do {
		CP_FROM_USER(&ucWinID,(void *)arg,sizeof(ucWinID));
		CHECK_WIN_ID(ucWinID);
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[ucWinID].eDolbyDrvState,gsDolbyDevHandler[ucWinID].eCmdErr);

		if(gsDolbyDevHandler[ucWinID].eCurMode == LX_DOLBY_HDMI_MODE) {
			ret = DE_DHDR_IP_HAL_Start(&gsDolbyDevHandler[ucWinID]);
		}
		else if(gsDolbyDevHandler[ucWinID].eCurMode == LX_DOLBY_OTT_MODE) {
			//Pic start will be in vsync interrupt
			//State will be initilized in DE_DHDR_IP_INTR_MetaDataReadyvsync interrupt handler
			ret = RET_OK;
			DE_NOTI("Info: Pic start for %d[OTT] Mode will be done in next Vsync\n",gsDolbyDevHandler[ucWinID].eCurMode);
		}
		else {
			gsDolbyDevHandler[ucWinID].eCmdErr = DOLBY_START_ERROR;
			DE_ERROR("Error: [%s:%d] Dolby driver Start Errori %d [State:%d Mode:%d]\n",__F__,__L__,gsDolbyDevHandler[ucWinID].eCmdErr,gsDolbyDevHandler[ucWinID].eDolbyDrvState,gsDolbyDevHandler[ucWinID].eCurMode);			 
		}
		DE_NOTI("Info: Dolby Driver Pic Start done\n");
		gsDolbyDevHandler[ucWinID].eCmdErr = DOLBY_OK;
	}while(0);

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to Uninitialize memory,irq & resource of  Dolby driver
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_IO_Uninit(UINT8 *sptr_DolbyParam)
{
	int ret = RET_ERROR;
	UINT8 ucWinID;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	
	do {
		//CP_FROM_USER(&ucWinID,(void *)arg,sizeof(ucWinID));
		memcpy((void *)&ucWinID,(void *)sptr_DolbyParam,sizeof(UINT8));
		CHECK_WIN_ID(ucWinID);
		gsDolbyDevHandler[ucWinID].unDolbyInitCount--;
		if( gsDolbyDevHandler[ucWinID].unDolbyInitCount == 0) {
			DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[ucWinID].eDolbyDrvState,gsDolbyDevHandler[ucWinID].eCmdErr);

			ret = DE_DHDR_IP_HAL_UnInit(&gsDolbyDevHandler[ucWinID]);
			if(ret) break;

			gsDolbyDevHandler[ucWinID].eDolbyDrvState = DOLBY_UNINTIALIZED;
			gsDolbyDevHandler[ucWinID].eCmdErr = DOLBY_OK;
			DE_NOTI("Info: Dolby Driver Un Init done\n");
		}
		else {
			DE_NOTI("Unitit for multiple process %d!!!\n", gsDolbyDevHandler[ucWinID].unDolbyInitCount);
		}
		ret = RET_OK;
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Initialization of irq's and resource for Dolby driver
 *
 * @param *i_PtrDolbyUnInit [IN] Irq Numbers to free IRQ
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_INTR_Init(DOLBY_DEVICE_DATA_T *i_PtrDolbyDrv)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		DE_NOTI("Info: unHDRIntrIrqNum = %d,unMCUIntrIrqNum = %d\n",i_PtrDolbyDrv->unHDRIntrIrqNum,i_PtrDolbyDrv->unMCUIntrIrqNum);

		DE_NOTI("Info: Irq Initializaiotn Done %s\n",__FUNCTION__);
		ret = RET_OK;
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief IOCTL function to Uninitialize memory,irq & resource of  Dolby driver
 *
 * @param i_PtrDolbyUnInit [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_INTR_UnInit(DOLBY_DEVICE_DATA_T *i_PtrDolbyUnInit)

{
	int ret = RET_ERROR;

	do {

	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Used in Simulation]
 * @brief To unblcok the MetaData read ioctl
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_INTR_MDReadUnblock(UINT8 *sptr_DOlbyParam)
{
	int ret = RET_ERROR;
	UINT8 ucWinID;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);
	
	do {
		//CP_FROM_USER(&ucWinID,(void *)arg,sizeof(ucWinID));
		memcpy((void *)&ucWinID,(void *)sptr_DOlbyParam,sizeof(UINT8));
		CHECK_WIN_ID(ucWinID);
		DOLBY_DRIVER_CHECK_INIT(gsDolbyDevHandler[ucWinID].eDolbyDrvState,gsDolbyDevHandler[ucWinID].eCmdErr);
		
		ret = VIDEO_DHDR_IP_INTR_MDReadUnblock(0);
		DE_NOTI("Info: Blocking MD Rdy Interrupt Flag %d\n",gMDWakeUpRecvTimeOut);
		ret = RET_OK;
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * @brief IOCTL function to select where to take HDMI MD from - IPP M0 or HDR HW block
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, <0 for otherwise
 */

int DE_DHDR_IP_IO_Set_HDMI_MD_Path(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_MD_PATH_T sParams;	
	

	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CP_FROM_USER(&sParams,(void *)arg,sizeof(sParams));
		CHECK_WIN_ID(sParams.ucWinID);

		ret = DE_DHDR_IP_HAL_SetMDPath(&gsDolbyDevHandler[sParams.ucWinID],sParams.e_md_path);
		if(ret == RET_ERROR) {
			gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_LUT_ERROR;
			DE_ERROR("Error: Dolby HAL Set MD Path  - path fail to set %d\n",sParams.e_md_path);
			return ret;
		}
		gsDolbyDevHandler[sParams.ucWinID].eCmdErr = DOLBY_OK;
		DE_NOTI("Info: Dolby Driver Set MD Path Done\n");

	}while(0);
	
	return ret;
}


/**  @} */
