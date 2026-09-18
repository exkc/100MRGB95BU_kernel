/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file hal_vsc.c
 *
 *  It is the file for Video HAL functions.
 *  The function of Video HAL is controlled by this file.
 *
 *  @author	Lee, Jong-Hun(drmyung@lge.com)
 *  @modified Goudar,Manjunath(manjunath.goudar@lge.com)
 *  @version	0.1
 *  @date		2011.08.01
 *  @note
 *  @see
 */

#if 0	//not used
/*-----------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/
#define VDEC_MULTI_INSTANCE
//#define USE_GLOBAL_VARIABLES_FOR_GET_WINDOW

/*-----------------------------------------------------------------------------
	File Inclusions
------------------------------------------------------------------------------*/
#include <linux/unistd.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>    
#include <asm/uaccess.h> 
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/prctl.h>
#include <linux/unistd.h>
#include <linux/time.h>
#include <linux/delay.h>
#include "base_types.h"
#include "os_util.h"

#include "hal_hwrap_common.h"
#include "hal_vsc_hwrap.h"

#include "../vp_kwrap.h"
#include "../vp_kwrap_hdmi.h"
#include "../../hdmi20/hdmi20_kwarp.h"
#include "../de_kwrap.h"

#include "../../afe/afe_kwrap.h"
#include "../hdmi20/hdmi20_kwarp.h"

#ifdef V4L2_VSC_BBD_USE_PRIV
#else
#include "../vp_kwrap_bbd.h"
#endif

/*-----------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/
extern int g_vp_logm_fd;
/*-----------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/

#define HAL_VSC_CHECK_CODE(__checker, __if_action, fmt,args...)   __CHECK_IF_ERROR(__checker, DE_ERROR, __if_action , fmt, ##args )

#define HAL_VSC_BREAK_WRONG(arg)           { printf("[HAL_VSC]  %s : %d Wrong (0x%x)\n",  __L__, arg); ret = NOT_OK; break; }

#define HAL_CHECK_SRC_ID(ptr) 	if (ptr>VIDEO_WID_MAX) { DE_ERROR("[HAL_VSC][%d] Invalid parameters wId[%d].\n", __L__, ptr); return NOT_OK; }
#define HAL_CHECK_NULL(ptr)  		if (!ptr) { DE_ERROR("[HAL_VSC][%d] %s is Null\n", __L__, #ptr); return NOT_OK; }

#define TBL_NUM(X) 			(sizeof(X) /sizeof((X)[0]))
#define T_ENUM_(TBL, X) 		ConvertEnum (TBL, TBL_NUM(TBL), (X))
#define u16CHK_RANGE(X, Y, offset) ((UINT16)((X)+(offset)-(Y))<=(offset*2))

#define USE_VP_THREAD
#ifdef  USE_VP_THREAD
#define VP_THREAD_TIMEOUT 40	// 40ms thread
#endif

#define HAL_MAX_INPUT_CHECK 8

/*-----------------------------------------------------------------------------
	Extern Variables & Function Prototype Declarations
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	Local Constant Definitions
------------------------------------------------------------------------------*/
#define JPEG_FROM_CPU_TO_DE

#ifdef USE_VP_THREAD

static struct task_struct* _gVPThread = NULL;
#endif

/*-----------------------------------------------------------------------------
	Local Type Definitions
------------------------------------------------------------------------------*/
typedef enum {
	VSC_HDR_OFF,
	VSC_HDR_ON,
	VSC_HDR_OFF_MAXN
}VSC_HDR_STATUS_T;

typedef enum {
	E_VSC_CONNECT_INIT = 0x0,
	E_VSC_CONNECT_DONE,
	E_VSC_DISCONNECT_INIT,
	E_VSC_DISCONNECT_DONE,
	E_VDO_CONNECT_INIT,
	E_VDO_CONNECT_DONE,
	E_VDO_DISCONNECT_INIT,
	E_VDO_DISCONNECT_DONE,
	E_API_UNKNOWN
} VSC_API_STATUS_T;


typedef struct {
    VIDEO_WID_T ewinId;
    VSC_HDR_TYPE_T eHdrMode;
	VSC_API_STATUS_T eVscStatus;
	VSC_API_STATUS_T eVdoStatus;
}API_CALL_MONITOR_T;




/*-----------------------------------------------------------------------------
	Global Type Definitions
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	Static Variables & Function Prototypes Declarations
------------------------------------------------------------------------------*/
BOOLEAN _gHalVscOpenStatus[VIDEO_WID_MAXN] = {FALSE, FALSE, FALSE, FALSE};
VSC_OUTPUT_MODE_T _gHalVscOutputMode[VIDEO_WID_MAXN] = {VSC_OUTPUT_MAXN, VSC_OUTPUT_MAXN, VSC_OUTPUT_MAXN, VSC_OUTPUT_MAXN};
VIDEO_WID_T       _gHalVscOutputWin[VSC_OUTPUT_MAXN] = { 0, 0, 0, 0 };
API_CALL_MONITOR_T _gsHalAPIStatus[VIDEO_WID_MAXN+1] = {{0,VSC_HDR_MAXN,E_API_UNKNOWN,E_API_UNKNOWN}, {0,VSC_HDR_MAXN,E_API_UNKNOWN,E_API_UNKNOWN},\
	{0,VSC_HDR_MAXN,E_API_UNKNOWN,E_API_UNKNOWN}, {0,VSC_HDR_MAXN,E_API_UNKNOWN,E_API_UNKNOWN}};

VIDEO_WID_T		gwId = VIDEO_WID_0;
/*-----------------------------------------------------------------------------
	Global Variables & Function Prototypes Declarations
------------------------------------------------------------------------------*/
BOOLEAN		_gHalVscInit = FALSE;

LX_DE_RECT_T 	_gDeOutWin[VIDEO_WID_MAXN] = {{0, 0, 0, 0}, {0, 0, 0, 0}};
LX_DE_RECT_T 	_gDeInWin[VIDEO_WID_MAXN] = {{0, 0, 0, 0}, {0, 0, 0, 0}};
LX_DE_RECT_T 	_gDeInSize[VIDEO_WID_MAXN] = {{0, 0, 0, 0}, {0, 0, 0, 0}};

kwrap_vp_src_info_t	_gVPSrcInfo[VIDEO_WID_MAXN] = {{SRC_INPUT_NONE, 0, 0, 0}, {SRC_INPUT_NONE, 0, 0, 0}};
UINT32				_gDelay = 80; //ms


VSC_HDR_INFO_T gsHdrInfo[VIDEO_WID_MAXN] = {{0,0}, {0,0}, {0,0}, {0,0}};

// for debug
BOOLEAN 			_gHalVscDebugPrintOn = FALSE;
BOOLEAN				_gHalVscDisableMute = FALSE;
BOOLEAN				_gHalVscDisableOutWindow = FALSE;

// for del
VIDEO_TIMING_INFO_T _gPrevTiming[VIDEO_WID_MAXN] = {{0, }, {0, }};
VIDEO_SRC_INFO_T	gVideoSrcInfo[VIDEO_WID_MAXN];
static LX_DE_VENC_FMT_T _gVencInfo = {0, 0, 0, 0, 0};

typedef struct {
	BOOLEAN isTile;
	UINT16 uMaxRow;
	UINT16 uMaxCol;
	UINT16 uTileID;
} VIDEO_DDI_Tile_T;

static VIDEO_DDI_Tile_T _gTileInfo = {FALSE, 0xffff, 0xffff, 0xffff};
static LX_DE_UD_CTRL_T _gUDCtrl = LX_DE_UD_OFF;
static UINT16 _gQuadWin = 0;
static UINT16 _gPBPMode = 0;
static UINT32 _gHDRControl = 0;
static LX_DE_FIRMWARE_INFO_T de_fw_info = { 0 };
static UINT32 _gAdaptive_4k_window = 0;
static VSC_HDR_STATUS_T _geHDROnOff = VSC_HDR_OFF;
static UINT32 _gVdo_port[VIDEO_WID_MAXN] = { 0 };
static UINT32 _g_use_vdec_multi_instance[VIDEO_WID_MAXN] = { 0 };
static LX_DE_SUB_MODE_T _gSubMode = LX_DE_SUB_MODE_NONE;

/*-----------------------------------------------------------------------------
	Local Variables & Function Prototypes Declarations
------------------------------------------------------------------------------*/
static void HAL_VIDEO_VP_Thread(void);

static VIDEO_WID_T _VSC_Set_Winmap(VIDEO_WID_T wId, VSC_INPUT_SRC_INFO_T vscInput, VSC_OUTPUT_MODE_T outputmode);
static VIDEO_WID_T _VSC_Get_Winmap(VIDEO_WID_T wId);

static DTV_STATUS_T hal_vsc_hwrap_DM_Open(void);
static DTV_STATUS_T hal_vsc_hwrap_DM_Close(void);
static DTV_STATUS_T hal_vsc_hwrap_DM_Connect(void);
static DTV_STATUS_T hal_vsc_hwrap_DM_Disconnect(void);

/*-----------------------------------------------------------------------------
	Function Definitions
------------------------------------------------------------------------------*/
#define DE_NOTI printk
#define DE_ERROR printk
#define DE_WARN printk

/**
 *	function
 */
int ConvertEnum(const sHAL_OUT_ENUM  * pTbl, int aTblSize, int aVal)
{
    int idx = 0;

    for (idx = 0 ; idx < aTblSize ; idx++, pTbl++)
    {
        if (aVal == pTbl->PreEnum)
        {
			//printf("pTbl->CortezEnum %d ",pTbl->PreEnum );
            return pTbl->PostEnum;
        }
    }
	//printf("Enum convert error PostEnum %d ",aVal );
    return -1;
}
/**
 * This API function be used for initializing DDI VIDEO and SoC Video.
 *
 * @param [in] void.
 * @return int
 */
DTV_STATUS_T hal_vsc_hwrap_initialize(void)
{
	DTV_STATUS_T	ret = OK;

	if (!_gHalVscInit)
	{
		DE_NOTI("[HAL_VSC][%d] start \n ", __L__);

		//ret = vp_kwrap_open();

		ret = vp_kwrap_initialize();

		if (de_kwrap_getfirmwareinfo(&de_fw_info) < 0)
			DE_ERROR("[HAL_VSC][%d] return error at de_kwrap_GetFirmWareInfo.\n", __L__);
		else
			DE_NOTI("[HAL_VSC]DE firmware ver. %d(%d/%d/%d).\n", de_fw_info.version,de_fw_info.date.year, de_fw_info.date.month, de_fw_info.date.day);

		ret = vp_kwrap_setwinblank(VIDEO_WID_0, TRUE, 0, 0);

		_gHalVscInit = 1;

		//ret |= HAL_GCP_Init();

#ifdef USE_VP_THREAD
		if(_gVPThread == NULL) {
			_gVPThread = kthread_create ((void*)&HAL_VIDEO_VP_Thread,0,"vp_thread");
			if (_gVPThread  == NULL)
			{
				DE_NOTI("[HAL_VSC][%d] ERR!! VP Thread Not Created  \n", __L__);
			}
			else
			{
				wake_up_process(_gVPThread);
				DE_NOTI("[HAL_VSC][%d] ERR!! VP kernel layer Thread  Created  \n", __L__);
			}
		}
		else {
			DE_NOTI("VP thread already created\n");
		}
#endif

		DE_NOTI("[HAL_VSC][%d] end \n ", __L__);
	}
	else
	{
		DE_NOTI("[HAL_VSC][%d] Already initialize.\n", __L__);
	}

	return ret;
}


/**
 * This API function be used for uninitializing DDI VIDEO and SoC Video.
 *
 * @param [in] void.
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_Uninitialize(void)
{
	DTV_STATUS_T	ret = OK;

	DE_NOTI("[HAL_VSC][%d] Uninitialize \n ", __L__);

	ret = vp_kwrap_uninitialize();

	//ret |= HAL_GCP_Finalize();

	_gHalVscInit = FALSE;

	return ret;
}


/**
 * hal_vsc_hwrap_open
 *
 * @param wId[in] VIDEO_WID_T
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_open(VIDEO_WID_T wId)
{
	DTV_STATUS_T	ret = OK;

	if (wId > VIDEO_WID_MAX)
	{
		DE_ERROR("[HAL_VSC][%d] Invalid parameters wId[%d].\n", __L__, wId);
		return INVALID_PARAMS;
	}

	if (_gHalVscOpenStatus[wId] == TRUE)
	{
		DE_NOTI("[HAL_VSC][%d] wId[%d] is already opened.\n", __L__, wId);
		ret = OK;
	}
	else
	{
		_gHalVscOpenStatus[wId] = TRUE;

		if (_gHalVscDebugPrintOn)
			DE_NOTI("[HAL_VSC][%d] wId[%d] is opened, OpenStatus [wId 0 - %d] [wId 1 - %d].\n", \
				 __L__, wId, _gHalVscOpenStatus[0], _gHalVscOpenStatus[1]);
	}

	return ret;
}


/**
 * hal_vsc_hwrap_close
 *
 * @param wId[in] VIDEO_WID_T.
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_close(VIDEO_WID_T wId)
{
	DTV_STATUS_T	ret = OK;

	if (wId > VIDEO_WID_MAX)
	{
		DE_ERROR("[HAL_VSC][%d] Invalid parameters wId[%d].\n", __L__, wId);
		return INVALID_PARAMS;
	}

	do {
		if (_gHalVscOpenStatus[wId] == FALSE)
		{
			DE_NOTI("[HAL_VSC][%d] wId[%d] is already closed.\n", __L__, wId);
			break;
		}

 		if (_gHalVscOutputMode[wId] != VSC_OUTPUT_MAXN)
 		{
			DE_ERROR("[HAL_VSC][%d] wId[%d] cannot close, Because The status of this wid is not disconnect.\n", __L__, wId);
			ret = NOT_OK;
			break;
		}

		_gHalVscOpenStatus[wId] = FALSE;

		if (_gHalVscDebugPrintOn)
			DE_NOTI("[HAL_VSC][%d] wId[%d] is closed, OpenStatus [wId 0 - %d] [wId 1 - %d].\n", \
				 __L__, wId, _gHalVscOpenStatus[0], _gHalVscOpenStatus[1]);
	} while (0);

	return ret;
}

/**
 * hal_vsc_hwrap_vdo_connect
 * @param vdo_port [in] VSC_VDO_PORT_T
 * @param vdec_port [in] UINT16
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_vdo_connect(VSC_VDO_PORT_T vdo_port, UINT16 vdec_port)
{
	DTV_STATUS_T	ret = OK;

	if(vdo_port > VSC_VDO_PORT_MAX)
	{
		DE_ERROR("invalid vdo_port = %d", vdo_port);
		return NOT_OK;
	}

	_gsHalAPIStatus[vdo_port].eVdoStatus = E_VDO_CONNECT_INIT;
	//ret = KADP_VDEC_ConnectVideoWindow ((UINT32)vdec_port, (UINT32)vdo_port);
	//HAL_VDEC_Connect ((UINT8)vdec_port, (UINT8)0xFF, (UINT8)vdo_port);

	_gVdo_port[vdo_port] = vdec_port;

	_g_use_vdec_multi_instance[vdo_port] = 1;

	_gsHalAPIStatus[vdo_port].eVdoStatus = E_VDO_CONNECT_DONE;
	DE_NOTI("vdo_port/vdec_port = %d/%d", vdo_port, vdec_port);

	return ret;
}

/**
 * hal_vsc_hwrap_vdo_disconnect
 * @param vdo_port [in] VSC_VDO_PORT_T
 * @param vdec_port [in] UINT16
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_vdo_disconnect(VSC_VDO_PORT_T vdo_port, UINT16 vdec_port)
{
	DTV_STATUS_T	ret = OK;

	if(vdo_port > VSC_VDO_PORT_MAX)
	{
		DE_ERROR("invalid vdo_port = %d", vdo_port);
		return NOT_OK;
	}

	//ret = vp_kwrap_setvdoconnectinfo((UINT32)vdec_port, (UINT32)vdec_port, 0/*disconnect*/);
	if(ret) return RET_ERROR;

	_gsHalAPIStatus[vdo_port].eVdoStatus = E_VDO_DISCONNECT_INIT;
	//ret = KADP_VDEC_DisconnectVideoWindow ((UINT32)vdec_port, (UINT32)vdo_port);
	if(ret) return RET_ERROR;
	//HAL_VDEC_Connect ((UINT8)vdec_port, (UINT8)0xFE, (UINT8)vdo_port);

	_gVdo_port[vdo_port] = 0xFF;

	_g_use_vdec_multi_instance[vdo_port] = 0;

	_gsHalAPIStatus[vdo_port].eVdoStatus = E_VDO_DISCONNECT_DONE;
	DE_NOTI("vdo_port/vdec_port = %d/%d", vdo_port, vdec_port);

	return ret;
}

/**
 * hal_vsc_hwrap_connect
 * @param wId [in] VIDEO_WID_T
 * @param vscInput [in] VSC_INPUT_TYPE_T
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_connect(VIDEO_WID_T wId, VSC_INPUT_SRC_INFO_T vscInput, VSC_OUTPUT_MODE_T outputmode)
{
	DTV_STATUS_T	ret = OK;
	kwrap_vp_src_info_t	vpSrcInfo = {SRC_INPUT_NONE, 0, 0, 0};
	LX_DE_OPERATION_CTRL_T 	vpOprParam = {0, LX_DE_OPER_ONE_WIN, FALSE, LX_DE_UD_OFF, {0,0,0,0,0},	{2,LX_DE_PROGRESSIVE,0,0,0}};
	LX_DE_SUB_OPERATION_CTRL_T vpSubOprParam = {0, LX_DE_SUB_OPER_VENC, 0, {0, 0, 0, 0, 0}};
	LX_DE_OUTPUT_MODE_T outMode = {LX_DE_WIN_0, LX_DE_OUT_DEV_VTD, 0};
	LX_DE_SUB_MODE_T sub_mode;
	LX_DE_CAPACITY_T capa;

	_gsHalAPIStatus[wId].eVscStatus = E_VSC_CONNECT_INIT;
	de_kwrap_getcapacity(&capa);

	if (_gHalVscOpenStatus[wId] == FALSE)
	{
		DE_ERROR("[HAL_VSC][%d] wId[%d] when is not opened can not connect.\n", __L__, wId);
		_gsHalAPIStatus[wId].eVscStatus = E_API_UNKNOWN;
		ret = NOT_SUPPORTED;
		goto func_exit;
	}

	DE_NOTI("wId[%d] resourceIdx[%d] type[%d] outputmode[%d]\n",\
		wId, vscInput.resourceIndex, vscInput.type, outputmode);
	ret = _VSC_Set_Winmap(wId, vscInput, outputmode);
	if(ret != OK){
		_gsHalAPIStatus[wId].eVscStatus = E_API_UNKNOWN;
		return INVALID_PARAMS;
	}

	wId = _VSC_Get_Winmap(wId);

	if (wId > VIDEO_WID_0 && _gHalVscOutputMode[wId] != outputmode && _gHalVscOutputMode[wId] != VSC_OUTPUT_MAXN)
	{
		DE_ERROR("[HAL_VSC][%d] wId[%d] The previous connect[%d] info differs from the Currnet Connect Info[%d]\n", \
			__L__, wId, _gHalVscOutputMode[wId], outputmode);
		_gsHalAPIStatus[wId].eVscStatus = E_API_UNKNOWN;
		ret = NOT_OK;
		goto func_exit;
	}

	do {
		if ((wId > VIDEO_WID_MAX) || (vscInput.type > VSC_INPUTSRC_MAX) )
		{
			ret = INVALID_PARAMS;
			break;
		}

		vpSrcInfo.Port = outMode.srcId = wId;
		de_kwrap_setoutputmode(&outMode);

		if ( (wId > VIDEO_WID_0) && ( (outputmode == VSC_OUTPUT_MEMORY_MODE) || (outputmode == VSC_OUTPUT_AVE_MODE) ) )
		{

		}
		else
		{
			switch (vscInput.type)
			{
				case VSC_INPUTSRC_AVD:
					if (vscInput.attr == 0) //VSC_ATV_INPUT
					{
						vpSrcInfo.Type = SRC_INPUT_ATV;
						vpSrcInfo.Attr = LX_AFE_CVBS_IN1;
					}
					else if (vscInput.attr == 1) //VSC_CVBS_INPUT
					{
						vpSrcInfo.Type = SRC_INPUT_CVBS;
						vpSrcInfo.Attr = LX_AFE_CVBS_IN3;
					}
					else if (vscInput.attr == 2)	//VSC_SCART_INPUT
					{
						vpSrcInfo.Type = SRC_INPUT_SCART;
						vpSrcInfo.Attr = LX_AFE_CVBS_IN2;
					}
					else
					{
						ret = INVALID_PARAMS;
					}
					break;

				case VSC_INPUTSRC_ADC:
					if (vscInput.attr == 0) //ADC_SRC_TYPE_COMPONENT
					{
						vpSrcInfo.Type = SRC_INPUT_YPBPR;
						vpSrcInfo.Attr = LX_ADC_YPbPr_IN2;
					}
					else if (vscInput.attr == 1) //ADC_SRC_TYPE_RGB
					{
						vpSrcInfo.Type = SRC_INPUT_VGA;
						vpSrcInfo.Attr = LX_ADC_YPbPr_IN2;
					}
					else
					{
						ret = INVALID_PARAMS;
					}
					break;

				case VSC_INPUTSRC_HDMI:
					vpSrcInfo.Type = SRC_INPUT_HDMI;
	//				vpSrcInfo.Port = vscInput.attr;
					vpSrcInfo.Attr = vscInput.resourceIndex;
					vp_kwrap_sethdmiport(wId, vpSrcInfo.Attr);
					break;

				case VSC_INPUTSRC_VDEC:
					{
						vpSrcInfo.Type = SRC_INPUT_MVI;

						// resourceIndex = vdo port from  gld4tv#61 tvservice 20170728

						if(0)//_g_use_vdec_multi_instance[wId])
						{
							vpSrcInfo.Port = (UINT32)wId;
							vpSrcInfo.Attr = (UINT32)wId;
						}
						else
						{
							vpSrcInfo.Port = vscInput.resourceIndex;
							vpSrcInfo.Attr = vscInput.resourceIndex;
						}
					}
					break;

				case VSC_INPUTSRC_JPEG:
					vpSrcInfo.Type = SRC_INPUT_JPG;
					vpSrcInfo.Port = vscInput.resourceIndex;
					break;

				default:
					vpSrcInfo.Type = SRC_INPUT_NONE;
					ret = INVALID_PARAMS;
					break;
			}
		}

		_gVPSrcInfo[wId].Type = vpSrcInfo.Type;
		_gVPSrcInfo[wId].Port = vpSrcInfo.Port;
		_gVPSrcInfo[wId].Attr = vpSrcInfo.Attr;
		_gVPSrcInfo[wId].Resv = vpSrcInfo.Resv;

		if (wId > VIDEO_WID_0)
		{
			switch (outputmode)
			{
				case VSC_OUTPUT_DISPLAY_MODE:	// Multi display
					outMode.outDev = LX_DE_OUT_DEV_VTD;     ///< Video To Display
					outMode.devId = wId;
					vpOprParam.operation = LX_DE_OPER_TWO_WIN;
					if(wId == 1)
					{
						if(	vpSrcInfo.Type == _gVPSrcInfo[0].Type &&
							vpSrcInfo.Attr == _gVPSrcInfo[0].Attr )
						{
							vpOprParam.multiCtrl = 2; // livezoom & magzoom (mirror mode)
						}
						else
						{
							vpOprParam.multiCtrl = 1;
						}
						DE_NOTI("win0.type/attr[%d/%d], win1.type/attr[%d/%d]\n", \
							_gVPSrcInfo[0].Type, _gVPSrcInfo[0].Attr, vpSrcInfo.Type, vpSrcInfo.Attr);
					}
					else if(wId >= 2)
					{
						vpOprParam.multiCtrl = 4;
					}
					if (_gHalVscOutputMode[wId] == outputmode) 	break;
					ret = vp_kwrap_setoperation(wId, &vpOprParam);
					break;

				case VSC_OUTPUT_VENC_MODE:		// DVR or 2ndTV
					if(capa.chip_id >= 5)/*M16 WA for multiview-venc conflict*/
					{
						sub_mode = LX_DE_SUB_MODE_NONE;
						ret = vp_kwrap_setsubwinmode(sub_mode);
						vpOprParam.operation = LX_DE_OPER_TWO_WIN;
						vpOprParam.multiCtrl = FALSE;
						ret |= vp_kwrap_setoperation(1, &vpOprParam);
						if(ret != OK) DE_ERROR("ret error");
					}
					outMode.outDev = 	LX_DE_OUT_DEV_VTV;     ///< Video To Venc
					outMode.devId = 0;
					vpSubOprParam.operation = LX_DE_SUB_OPER_VENC;
					_gVencInfo.bOnOff = vpSubOprParam.vencCtrl.bOnOff = 2;
					_gVencInfo.scan = vpSubOprParam.vencCtrl.scan = LX_DE_PROGRESSIVE;
					_gVencInfo.hSize = vpSubOprParam.vencCtrl.hSize = 0;
					_gVencInfo.vSize = vpSubOprParam.vencCtrl.vSize = 0;
					_gVencInfo.frRate = vpSubOprParam.vencCtrl.frRate = 0;
					//ret = vp_kwrap_setsuboperation(&vpSubOprParam);
					break;

				case VSC_OUTPUT_MEMORY_MODE:	// Capture
					outMode.outDev = 	LX_DE_OUT_DEV_VTM;     ///< Video To Memory
					outMode.devId = 0;
					vpSubOprParam.operation = LX_DE_SUB_OPER_CAPTURE;
					vpSubOprParam.capture_enable = 1;
					//ret = vp_kwrap_setsuboperation(&vpSubOprParam);
					break;

				case VSC_OUTPUT_AVE_MODE:		// Scart Out
					outMode.outDev = LX_DE_OUT_DEV_VTS;     ///< Video To Scart-Out
					outMode.devId = 0;
					vpSubOprParam.operation = LX_DE_SUB_OPER_SCART_OUT;
					vpSubOprParam.capture_enable = 1;
					//ret = vp_kwrap_setsuboperation(&vpSubOprParam);
					break;

				default:
					outMode.outDev = LX_DE_OUT_DEV_NONE;
					outMode.devId = 0;
					ret = INVALID_PARAMS;
					break;
			}
			if (ret == INVALID_PARAMS)	break;
		}
 		_gHalVscOutputMode[wId] = outputmode;
		_gHalVscOutputWin[outputmode] = wId;
	} while (0);

	if ((ret == INVALID_PARAMS) || (ret == NOT_SUPPORTED))
	{
		DE_ERROR("[HAL_VSC][%d] Invalid parameters or Not supported.\n", __L__);
		DE_ERROR("[HAL_VSC][%d] wId[%d] HAL input.type[%d] input.attr[%d] outputmode[%d].\n", \
			 __L__, wId, vscInput.type, vscInput.attr, outputmode);
		_gsHalAPIStatus[wId].eVscStatus = E_API_UNKNOWN;
		goto func_exit;
	}

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d] wId[%d] HAL input.type[%d] input.attr[%d] outputmode[%d].\n", \
			__L__, wId, vscInput.type, vscInput.attr, outputmode);
		DE_NOTI("[HAL_VSC][%d] wId[%d] KADP inSrc.Type[%d] inSrc.Port[%d] inSrc.Attr[%d].\n", \
			__L__, wId, vpSrcInfo.Type, vpSrcInfo.Port, vpSrcInfo.Attr);
		DE_NOTI("[HAL_VSC][%d] OutputMode[%d] =  %d\n", \
			__L__, wId, _gHalVscOutputMode[wId]);
	}

	if(0)//	wId > VIDEO_WID_0 && _g_use_vdec_multi_instance[0] == 1 && (_gSubMode == LX_DE_SUB_MODE_LIVEZOOM || _gSubMode == LX_DE_SUB_MODE_MAGZOOM))
	{
		DE_NOTI("skip SetInputSrc of wId_1 & mirror mode");
	}
	else
	{
		ret = vp_kwrap_setinputsrc(wId, &vpSrcInfo);
		ret = vp_kwrap_resettiminginfo(wId);
	}

	_gsHalAPIStatus[wId].eVscStatus = E_VSC_CONNECT_DONE;

	if(wId == VIDEO_WID_0 && vpSrcInfo.Type >= SRC_INPUT_HDMI \
		&& _gHDRControl > 0 && _gHDRControl < VSC_HDR_MAXN )
	{
		if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)) {
			VSC_HDR_TYPE_T eHdrMode = (_gHDRControl-1);
			//hal_vsc_hwrap_hdr_open(wId);
			//hal_vsc_hwrap_hdr_connect(wId,eHdrMode);
			DE_NOTI("start by manual control (HdrMode:%d)(Fake:%d)\n",eHdrMode,_gHDRControl);
		}
		else {
			//hal_vsc_hwrap_DM_Open();
			//hal_vsc_hwrap_DM_Connect();
			DE_NOTI("start by manual control (SW Dolby HDR)\n");
		}

	}
	else if(_gHDRControl >= 9/*General Capture Path*/ && vpSrcInfo.Type >= SRC_INPUT_DTV)
	{
		//HAL_GCP_Open(_gHDRControl);
	}

func_exit:

	return ret;
}


/**
 * hal_vsc_hwrap_disconnect
 * @param wId [in] VIDEO_WID_T
 * @param vscInput [in] VSC_INPUT_TYPE_T
 * @return  int
 */
DTV_STATUS_T hal_vsc_hwrap_disconnect(VIDEO_WID_T wId, VSC_INPUT_SRC_INFO_T vscInput, VSC_OUTPUT_MODE_T outputmode)
{
	DTV_STATUS_T	ret = OK;
	kwrap_vp_src_info_t	vpSrcInfo ={SRC_INPUT_NONE, 0, 0, 0};
	LX_DE_OPERATION_CTRL_T 	vpOprParam = {0, LX_DE_OPER_ONE_WIN, FALSE, LX_DE_UD_OFF, {0xff, 0xff, 0xff, 0xff, 0xff}, {2, LX_DE_PROGRESSIVE, 0, 0, 0}};
	LX_DE_SUB_OPERATION_CTRL_T vpSubOprParam = {0, LX_DE_SUB_OPER_VENC, 0, {0, 0, 0, 0, 0}};
	LX_DE_OUTPUT_MODE_T outMode = {LX_DE_WIN_0, LX_DE_OUT_DEV_NONE, 0};
	LX_DE_SRC_STATUS_T srcStatus;
	LX_DE_CAPACITY_T capa;

	_gsHalAPIStatus[wId].eVscStatus = E_VSC_DISCONNECT_INIT;
	de_kwrap_getcapacity(&capa);

	memset( &srcStatus, 0, sizeof( LX_DE_SRC_STATUS_T ));

	if (_gHalVscOpenStatus[wId] == FALSE)
	{
		DE_ERROR("[HAL_VSC][%d] wId[%d] when is not opened can not disconnect.\n", __L__, wId);
		ret = NOT_SUPPORTED;
		_gsHalAPIStatus[wId].eVscStatus = E_API_UNKNOWN;
		goto func_exit;
	}

	DE_NOTI("wId[%d] outputmode[%d]\n", wId, outputmode);
	wId = _VSC_Get_Winmap(wId);

	if (wId > VIDEO_WID_MAX)
	{
		DE_ERROR("[HAL_VSC][%d] Invalid parameters wId[%d].\n", __L__, wId);
		ret = INVALID_PARAMS;
		_gsHalAPIStatus[wId].eVscStatus = E_API_UNKNOWN;
		goto func_exit;
	}

	if(wId == VIDEO_WID_0 && _gHDRControl > 0 && _gHDRControl < VSC_HDR_MAXN)
	{
		if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)) {
			//hal_vsc_hwrap_hdr_disconnect(wId);
			//hal_vsc_hwrap_hdr_close(wId);
			DE_NOTI("stop by manual control (Fake:%d)\n",_gHDRControl);
		}
		else {
			//hal_vsc_hwrap_DM_Disconnect();
			//hal_vsc_hwrap_DM_Close();
			DE_NOTI("stop by manual control (SW Dolby HDR)\n");
		}
	}
	else if(_gHDRControl >= 9/*General Capture Path*/)
	{
		//HAL_GCP_Close();
	}

	do {
		vpSrcInfo.Port = outMode.srcId = wId;

		if (wId == VIDEO_WID_0)
		{
			srcStatus.status_type = LX_DE_SRC_STATUS_OPER;
			de_kwrap_getsourcestatus(&srcStatus);

			if (_gHalVscDebugPrintOn)
			{
				DE_NOTI("[HAL_VSC][%d] wId[0]  operation status before disconnect (ONE[0] TWO[1] 3D[2] UD[3] VENC[4]) = %d .\n", \
					__L__, srcStatus.operType);
			}

			if (srcStatus.operType == LX_DE_OPER_3D)
			{
				vpOprParam.operation = LX_DE_OPER_3D;
				vpOprParam.ctrl3D.run_mode = LX_DE_3D_RUNMODE_OFF;
				ret = vp_kwrap_setoperation(wId, &vpOprParam);
				if(ret != OK) DE_ERROR("ret error");
			}
			else if (srcStatus.operType == LX_DE_OPER_UD)
			{
				//vpOprParam.operation = LX_DE_OPER_UD;
				//vpOprParam.udCtrl= LX_DE_UD_OFF;
			}
		}
		else //if (wId > VIDEO_WID_0)
		{
			LX_DE_SUB_MODE_T sub_mode;

			if (_gHalVscOutputMode[wId] != outputmode)
			{
				DE_NOTI("[HAL_VSC][%d] wId[%d] The connect[%d] info differs from the Disconnect info[%d]\n", \
					__L__, wId, _gHalVscOutputMode[wId], outputmode);
				outputmode = _gHalVscOutputMode[wId];
			}

			switch (outputmode)
			{
				case VSC_OUTPUT_DISPLAY_MODE:	// Multi display
					outMode.devId = 1;
					if(_gPBPMode && capa.chip_id >= 5/*M16 only for 2 run mode*/)
					{
						sub_mode = LX_DE_SUB_MODE_PBP;
						ret = vp_kwrap_setsubwinmode(sub_mode); // set to the default mode (PBP)
						if(ret != OK) DE_ERROR("ret = %d", ret);
					}
					else
					{
						vpOprParam.operation = LX_DE_OPER_TWO_WIN;
						vpOprParam.multiCtrl = FALSE;
						ret = vp_kwrap_setoperation(wId, &vpOprParam);
						if(ret != OK) DE_ERROR("ret = %d", ret);
					}
					break;

				case VSC_OUTPUT_VENC_MODE:		// DVR or 2ndTV
					vpSubOprParam.operation = LX_DE_SUB_OPER_VENC;
					_gVencInfo.bOnOff = vpSubOprParam.vencCtrl.bOnOff = 0;
					_gVencInfo.scan = vpSubOprParam.vencCtrl.scan = LX_DE_PROGRESSIVE;
					_gVencInfo.hSize = vpSubOprParam.vencCtrl.hSize = 0;
					_gVencInfo.vSize = vpSubOprParam.vencCtrl.vSize = 0;
					_gVencInfo.frRate = vpSubOprParam.vencCtrl.frRate = 0;
					//ret = vp_kwrap_setsuboperation(&vpSubOprParam);
					break;

				case VSC_OUTPUT_MEMORY_MODE:	// Capture
					vpSubOprParam.operation = LX_DE_SUB_OPER_CAPTURE;
					vpSubOprParam.capture_enable = 0;
					//ret = vp_kwrap_setsuboperation(&vpSubOprParam);
					break;

				case VSC_OUTPUT_AVE_MODE:		// Scart Out
					vpSubOprParam.operation = LX_DE_SUB_OPER_SCART_OUT;
					vpSubOprParam.capture_enable = 0;
					//ret = vp_kwrap_setsuboperation(&vpSubOprParam);
					break;

				default:
					 break;
			}
		}

		if(ret != OK) DE_ERROR("ret error");

		if (_gHalVscOutputMode[wId] != VSC_OUTPUT_VENC_MODE)
		{
			ret = vp_kwrap_setwinblank(wId, 1/*on*/, VP_WIN_COLOR_BLACK, 0);
			if(ret != OK) DE_ERROR("ret error");
		}
		//ret = vp_kwrap_SetVdoConnectInfo((UINT32)wId, 0, 0/*disconnect*/);
		if(ret != OK) DE_ERROR("ret error");
		ret = de_kwrap_setoutputmode(&outMode);
		if(ret != OK) DE_ERROR("ret error");
		ret = vp_kwrap_setinputsrc(wId, &vpSrcInfo);
		if(ret != OK) DE_ERROR("ret error");
		ret = vp_kwrap_resettiminginfo(wId);

		_gVPSrcInfo[wId].Type = vpSrcInfo.Type;
		_gVPSrcInfo[wId].Port = vpSrcInfo.Port;
		_gVPSrcInfo[wId].Attr = vpSrcInfo.Attr;
		_gVPSrcInfo[wId].Resv = vpSrcInfo.Resv;

		_gHalVscOutputMode[wId] = VSC_OUTPUT_MAXN;
	} while (0);

func_exit:

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d] wId[%d] HAL input.type[%d] input.attr[%d] outputmode[%d].\n", \
			__L__, wId, vscInput.type, vscInput.attr, outputmode);
		DE_NOTI("[HAL_VSC][%d] wId[%d] KADP inSrc.Type[%d] inSrc.Port[%d] inSrc.Attr[%d].\n", \
			__L__, wId, vpSrcInfo.Type, vpSrcInfo.Port, vpSrcInfo.Attr);
	}

	_gsHalAPIStatus[wId].eVscStatus = E_VSC_DISCONNECT_DONE;
	return ret;
}


/**
 *
 * @param wId [in] VIDEO_WID_T.
 * @param bOnOff [in] BOOLEAN.
 * @param color		[in] VIDEO_DDI_WIN_COLOR_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T hal_vsc_hwrap_setwinblank(VIDEO_WID_T wId, BOOLEAN bOnOff, VIDEO_DDI_WIN_COLOR_T color)
{
	DTV_STATUS_T	ret = OK;

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	if ((_gHalVscDisableMute == TRUE) && (bOnOff))
	{
		DE_NOTI("[HAL_VSC][%d] Skip wId[%d] isOn %x color %d.\n",  __L__, wId, bOnOff, color);
		return NOT_OK;
	}

#ifdef USE_SIGNAGE_FEATURE
#if defined(CHIP_NAME_h15)
	if (_gQuadWin)
	{
		//ret = VDE_SetWinBlank (wId, bOnOff);

		DE_NOTI("[HAL_VSC][%d] wId[%d] isOn %x color %d.\n",	__L__, wId, bOnOff, color);

		return ret;
	}
#endif
#endif

	if (_gHalVscOutputMode[wId] != VSC_OUTPUT_VENC_MODE)
	ret = vp_kwrap_setwinblank(wId, bOnOff, color, 0);

	DE_NOTI("[HAL_VSC][%d] wId[%d] isOn %x color %d.\n",	__L__, wId, bOnOff, color);

   	return ret;
}


/**
 *
 * @param wId [in] VIDEO_WID_T.
 * @param pInRegion [out] VIDEO_RECT_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T	hal_vsc_hwrap_getinputregion(VIDEO_WID_T wId, VIDEO_RECT_T *pInRegion)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_RECT_T 	inWin = {0, 0, 0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);
	HAL_CHECK_NULL(pInRegion);

	ret = vp_kwrap_getinputwin(wId, &inWin);

#ifdef USE_GLOBAL_VARIABLES_FOR_GET_WINDOW
	pInRegion->h	= _gDeInWin[wId].h;
	pInRegion->w	= _gDeInWin[wId].w;
	pInRegion->x	= _gDeInWin[wId].x;
	pInRegion->y	= _gDeInWin[wId].y;
#else
	pInRegion->h	= inWin.h;
	pInRegion->w	= inWin.w;
	pInRegion->x	= inWin.x;
	pInRegion->y	= inWin.y;
#endif
	return ret;
}


/**
 *
 * @param wId [in] VIDEO_WID_T.
 * @param inRegion [in] VIDEO_RECT_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T    hal_vsc_hwrap_setinputregion(VIDEO_WID_T wId, VIDEO_RECT_T inRegion, VIDEO_RECT_T originalInput)
{
	DTV_STATUS_T ret = OK;
	LX_DE_RECT_T inSize = {0, 0, 0, 0};
	LX_DE_RECT_T inWin = {0, 0, 0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	inSize.h = _gDeInSize[wId].h = originalInput.h;
	inSize.w = _gDeInSize[wId].w = originalInput.w;
	inSize.x = _gDeInSize[wId].x = originalInput.x;
	inSize.y = _gDeInSize[wId].y = originalInput.y;

	inWin.h = _gDeInWin[wId].h = inRegion.h;	//for backup  //  _gDeInWin 수정 금지.
	inWin.w = _gDeInWin[wId].w = inRegion.w;
	inWin.x = _gDeInWin[wId].x = inRegion.x;
	inWin.y = _gDeInWin[wId].y = inRegion.y;

	ret = de_kwrap_setsourcesizewin(wId, (LX_DE_RECT_T*)&inSize, (LX_DE_RECT_T*)&inWin);
	ret = vp_kwrap_setinputwin(wId, inWin);

	DE_NOTI("[HAL_VSC][%d] Set wId[%d] Window src_wh(%d,%d) in_xywh(%d,%d,%d,%d)***", \
			__L__, wId, inSize.w, inSize.h, inWin.x, inWin.y, inWin.w, inWin.h);
	if(inRegion.w == 0 || inRegion.h == 0) ret = NOT_OK;
	if(inSize.w < inRegion.w || inSize.h < inRegion.h) ret = NOT_OK;

	return ret;
}


/**
 *
 * @param wId [in] VIDEO_WID_T.
 * @param pOutRegion [out] VIDEO_RECT_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T	hal_vsc_hwrap_getoutputregion(VIDEO_WID_T wId, VIDEO_RECT_T *pOutRegion)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_RECT_T 	outWin = {0, 0, 0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);
	HAL_CHECK_NULL(pOutRegion);

	ret = vp_kwrap_getoutwin(wId, &outWin);

#ifdef USE_GLOBAL_VARIABLES_FOR_GET_WINDOW
	pOutRegion->h	= _gDeOutWin[wId].h;
	pOutRegion->w	= _gDeOutWin[wId].w;
	pOutRegion->x	= _gDeOutWin[wId].x;
	pOutRegion->y	= _gDeOutWin[wId].y;
#else
	pOutRegion->h	= outWin.h;
	pOutRegion->w	= outWin.w;
	pOutRegion->x	= outWin.x;
	pOutRegion->y	= outWin.y;
#endif

	return ret;
}


/**
 *
 * @param wId [in] VIDEO_WID_T.
 * @param outRegion [in] VIDEO_RECT_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T	hal_vsc_hwrap_setoutputregion(VIDEO_WID_T wId, VIDEO_RECT_T outRegion)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_RECT_T 	outWin = {0, 0, 0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	if (_gHalVscDisableOutWindow == TRUE)
	{
		DE_NOTI("[HAL_VSC][%d] SKIP wId[%d] out_xywh(%d,%d,%d,%d).\n", \
			__L__, wId, outRegion.x, outRegion.y, outRegion.w, outRegion.h);
		return ret;
	}

	outWin.h = _gDeOutWin[wId].h = outRegion.h; // _gDeOutWin for backup
	outWin.w = _gDeOutWin[wId].w = outRegion.w;
	outWin.x = _gDeOutWin[wId].x = outRegion.x;
	outWin.y = _gDeOutWin[wId].y = outRegion.y;

	do {
		if ((wId >= VIDEO_WID_1) && (_gHalVscOutputMode[wId] > VSC_OUTPUT_DISPLAY_MODE) )
		{
			DE_NOTI("[HAL_VSC][%d]  Set wId[%d] Skip output window at venc(%d/%d) \n", __L__, wId, outWin.w, outWin.h);
			break;
		}
		ret = vp_kwrap_setoutwin(wId, outWin);

		DE_NOTI("[HAL_VSC][%d]  Set wId[%d] Window out_xywh(%d,%d,%d,%d)***", \
			__L__, wId,outWin.x, outWin.y, outWin.w, outWin.h);
	} while (0);

	return ret;
}

DTV_STATUS_T hal_vsc_hwrap_setinputoutputregion (VIDEO_WID_T wId, VSC_ROTATE_T rotation, VSC_INPUT_REGION_T *pInputRegion, VIDEO_RECT_T *pOutputRegion)
{
	DTV_STATUS_T ret = OK;
	LX_DE_ROTATE_INFO_T lx_rotate;
	LX_DE_RECT_T inSize = {0, 0, 0, 0};
	LX_DE_RECT_T inWin  = {0, 0, 0, 0};
	LX_DE_RECT_T outWin = {0, 0, 0, 0};
	LX_DE_WIN_INFO_T win_info;

	wId = _VSC_Get_Winmap(wId);
	HAL_CHECK_SRC_ID(wId);

	do {
		switch(rotation)
		{
			case VSC_ROTATE_0:
			default:
				lx_rotate = LX_DE_ROTATE_0;
				break;
			case VSC_ROTATE_90:
				lx_rotate = LX_DE_ROTATE_90;
				break;
			case VSC_ROTATE_180:
				lx_rotate = LX_DE_ROTATE_180;
				break;
			case VSC_ROTATE_270:
				lx_rotate = LX_DE_ROTATE_270;
				break;
		}
		win_info.rot = lx_rotate;
		ret = de_kwrap_setrotate(lx_rotate);

		if(pInputRegion == NULL)
		{
			inSize.w = _gDeInSize[wId].w;
			inSize.h = _gDeInSize[wId].h;
			inSize.x = _gDeInSize[wId].x;
			inSize.y = _gDeInSize[wId].y;

			inWin.h = _gDeInWin[wId].h;
			inWin.w = _gDeInWin[wId].w;
			inWin.x = _gDeInWin[wId].x;
			inWin.y = _gDeInWin[wId].y;
		}
		else
		{
			inSize.w = _gDeInSize[wId].w = pInputRegion->originalInput.w;
			inSize.h = _gDeInSize[wId].h = pInputRegion->originalInput.h;
			inSize.x = _gDeInSize[wId].x = pInputRegion->originalInput.x;
			inSize.y = _gDeInSize[wId].y = pInputRegion->originalInput.y;

			inWin.h = _gDeInWin[wId].h = pInputRegion->inRegion.h;
			inWin.w = _gDeInWin[wId].w = pInputRegion->inRegion.w;
			inWin.x = _gDeInWin[wId].x = pInputRegion->inRegion.x;
			inWin.y = _gDeInWin[wId].y = pInputRegion->inRegion.y;
		}
		if(pOutputRegion == NULL)
		{
			outWin.h = _gDeOutWin[wId].h;
			outWin.w = _gDeOutWin[wId].w;
			outWin.x = _gDeOutWin[wId].x;
			outWin.y = _gDeOutWin[wId].y;
		}
		else
		{
			outWin.h = _gDeOutWin[wId].h = pOutputRegion->h; // _gDeOutWin for backup
			outWin.w = _gDeOutWin[wId].w = pOutputRegion->w;
			outWin.x = _gDeOutWin[wId].x = pOutputRegion->x;
			outWin.y = _gDeOutWin[wId].y = pOutputRegion->y;
		}

		ret |= de_kwrap_setsourcesizewin(wId, (LX_DE_RECT_T*)&inSize, (LX_DE_RECT_T*)&inWin);
		ret |= vp_kwrap_setinputwin(wId, inWin);

		if ((wId >= VIDEO_WID_1) && (_gHalVscOutputMode[wId] > VSC_OUTPUT_DISPLAY_MODE) )
		{
			DE_NOTI("[HAL_VSC][%d]  Set wId[%d] Skip output window at venc(%d/%d) \n", __L__, wId, outWin.w, outWin.h);
		}
		else
		{
			ret |= vp_kwrap_setoutwin(wId, outWin);
		}

		win_info.wId = (LX_DE_WIN_ID_T)wId;
		memcpy(&win_info.in_size, &inSize,  sizeof(LX_DE_RECT_T));
		memcpy(&win_info.in_win,  &inWin,  sizeof(LX_DE_RECT_T));
		memcpy(&win_info.out_win, &outWin, sizeof(LX_DE_RECT_T));

		ret |= vp_kwrap_setwindowinfo(&win_info);

	} while(0);

	DE_NOTI(" rot(%d) src_wh(%d,%d) in_xywh(%d,%d,%d,%d) out_xywh(%d,%d,%d,%d) [pIn:%s,pout:%s]",\
		rotation, inSize.w, inSize.h, inWin.x, inWin.y, inWin.w, inWin.h, outWin.x, outWin.y, outWin.w, outWin.h,\
		(pInputRegion==NULL)?"NULL":"Up", (pOutputRegion==NULL)?"NULL":"Up");

	return ret;
}

/**
 * @param frame_rate [in] UINT16.
 * @param scan_type [in] UINT16.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T	hal_vsc_hwrap_setvencmode (UINT16 frame_rate, UINT16 scan_type)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_SUB_OPERATION_CTRL_T subParam = {0, LX_DE_SUB_OPER_VENC, 0, {0, 0, 0, 0, 0}};
	kwrap_vp_timing_info_t	vpTimingInfo ={0, };

	do {
		if (_gHalVscOutputMode[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]]  != VSC_OUTPUT_VENC_MODE)
		{
			DE_ERROR("[HAL_VSC][%d] The output mode of VSC is not opened [%d].\n", \
				__L__, _gHalVscOutputMode[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]]);
			break;
		}

		if (_gHalVscDebugPrintOn)
		{
			DE_NOTI("[HAL_VSC][%d] VENC Mode w/h/scan/fr(%d,%d,%s,%d) from DIL \n",
				 __L__, _gDeOutWin[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]].w, _gDeOutWin[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]].h, (scan_type==1)?"P":"I", frame_rate);
		}

		if (_gDeOutWin[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]].w == 0 || _gDeOutWin[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]].h == 0)	 break;

		subParam.operation = LX_DE_SUB_OPER_VENC;
		subParam.vencCtrl.bOnOff = 2;

		subParam.vencCtrl.hSize = _gDeOutWin[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]].w;
		subParam.vencCtrl.vSize =  _gDeOutWin[_gHalVscOutputWin[VSC_OUTPUT_VENC_MODE]].h;
		subParam.vencCtrl.scan = scan_type;
		subParam.vencCtrl.frRate = frame_rate;
		subParam.win_id          = _gHalVscOutputWin[VSC_OUTPUT_VENC_MODE];

		DE_NOTI("h/v = %d/%d", subParam.vencCtrl.hSize, subParam.vencCtrl.vSize );

		if (u16CHK_RANGE(vpTimingInfo.vFreq,60,5))
			subParam.vencCtrl.frRate = 60;
		else if (u16CHK_RANGE(vpTimingInfo.vFreq,50,5))
			subParam.vencCtrl.frRate = 50;

		if (memcmp(&_gVencInfo, &subParam.vencCtrl, sizeof(subParam.vencCtrl)) != 0)
		{
			//ret = vp_kwrap_setsuboperation(&subParam);
			if (ret) break;
			memcpy(&_gVencInfo, &subParam.vencCtrl, sizeof(subParam.vencCtrl) );
		}
		else
		{
			if (_gHalVscDebugPrintOn)
			{
				DE_NOTI("[HAL_VSC][%d] Skip VENC Mode setting \n", __L__);
			}
		}
	} while (0);

	if (1)//_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d] VENC Mode[%d] w/h/scan/fr(%d,%d,%s,%d) \n",
		 __L__, _gHalVscOutputWin[VSC_OUTPUT_VENC_MODE], _gVencInfo.hSize, _gVencInfo.vSize,(scan_type==1)?"P":"I", frame_rate);
	}

	return ret;
}

/**
 * @param wId [in] VIDEO_WID_T.
 * @param bOnOff [in] BOOLEAN. BOOLEAN bAll.// Add "BOOLEAN bAll" parameter, by choonghoon.park 20170203
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T hal_vsc_hwrap_setwinfreeze(VIDEO_WID_T wId, BOOLEAN bOnOff, BOOLEAN bAll)
{
	DTV_STATUS_T	ret = OK;
	UINT32 win_num = 0;
	LX_DE_WIN_FREEZE_T param = {LX_DE_WIN_0, FALSE, LX_DE_FREEZE_DISP};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	if(bAll == TRUE)
	{
		win_num = 0;
		do {
			param.win_id   = win_num;
			param.bEnable  = bOnOff;
			ret = de_kwrap_setwinfreeze(&param);
		} while(win_num++ < VIDEO_WID_MAXN);
	}
	else
	{
		param.win_id   = wId;
		param.bEnable  = bOnOff;
		ret = de_kwrap_setwinfreeze(&param);
	}

	DE_NOTI("[HAL_VSC][%d] wId %d isOn %d.\n",  __L__, wId, bOnOff);

	return ret;
}


/**
 * @brief  HAL_VIDEO_CaptuerVideoFrame
 * @param place[IN]VIDEO_DDI_CAPTURE_PLACE_T
 * @param pCaptureInfo[OUT]VIDEO_DDI_CAPTURE_INFO_T
 * @retval  int
 */
DTV_STATUS_T	hal_vsc_hwrap_capturevideoframe(VIDEO_DDI_CAPTURE_PLACE_T place, VIDEO_DDI_CAPTURE_INFO_T* pCaptureInfo)
{
	DTV_STATUS_T	ret = OK;

	return ret;
}


/**
* Freeze Video Frame Buffer.
*
* @param bFreezeOn [in] BOOLEAN
* @return int
*/
DTV_STATUS_T hal_vsc_hwrap_freezevideoframebuffer(BOOLEAN bFreezeOn)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_CVI_CAPTURE_FREEZE_T cvi_cap_freeze;

	if (bFreezeOn)
	{
		cvi_cap_freeze.bCaptureOnOff= TRUE;
		cvi_cap_freeze.bCviFreezeOnOff= TRUE;
	}
	else
	{
		cvi_cap_freeze.bCaptureOnOff= FALSE;
		cvi_cap_freeze.bCviFreezeOnOff= FALSE;
	}

	ret  = de_kwrap_setcvifreeze(cvi_cap_freeze);

	if (ret != OK)
		DE_ERROR("[HAL_VSC][%d] return error at de_kwrap_setcvifreeze.\n", __L__);

    return ret;
}


/**
* Read Video Frame Buffer.
*
* @param wId [in] VIDEO_WID_T
* @param *pIn [in] VIDEO_RECT_T
* @param *pRead [in] VIDEO_DDI_PIXEL_STANDARD_COLOR_T
* @param *pcolor_standard [in] VIDEO_DDI_PIXEL_STANDARD_COLOR_T
* @param *pPixelColorFormat [in] VIDEO_DDI_PIXEL_COLOR_FORMAT_T
* @return DTV_STATUS
*/
DTV_STATUS_T hal_vsc_hwrap_readvideoframebuffer(VIDEO_WID_T wId, VIDEO_RECT_T *pIn, VIDEO_DDI_PIXEL_STANDARD_COLOR_T *pRead, VIDEO_DDI_COLOR_STANDARD_T *pcolor_standard,
															VIDEO_DDI_PIXEL_COLOR_FORMAT_T * pPixelColorFormat)
{
	DTV_STATUS_T	ret = OK;
	LX_HDMI_STATUS_T hdmiStatus;
	LX_DE_CVI_RW_VIDEO_FRAME_T cvi_video_frame_buffer;
	UINT32 array_colorbar_level_Y = 0;
	UINT32 array_colorbar_level_Cb = 0;
	UINT32 array_colorbar_level_Cr = 0;
	UINT8 hdmi_phys_port = de_kwrap_gethdmiport(wId);
	kwrap_vp_timing_info_t vpTimingInfo;
	LX_DE_CAPACITY_T chip_capa;

	if (pIn == NULL || pRead == NULL)
	{
		DE_ERROR("[HAL_VSC][%d] invalid parameters for PIN or pRead.\n", __L__);
		return NOT_OK;
	}

	if (_gHalVscOpenStatus[wId] == FALSE)
	{
		DE_ERROR("[HAL_VSC][%d] WidID[%d] don't work when open status[%d] outputMode[%d]\n",\
			 __L__, wId, _gHalVscOpenStatus[wId],_gHalVscOutputMode[wId]);
		return NOT_OK;
	}

	de_kwrap_getcapacity(&chip_capa);

	wId = _VSC_Get_Winmap(wId);

	*pPixelColorFormat = VIDEO_DDI_PIXEL_10BIT;

	cvi_video_frame_buffer.region.win_id = wId;
	cvi_video_frame_buffer.region.pixelGrabX = (UINT32)pIn->x;
	cvi_video_frame_buffer.region.pixelGrabY = (UINT32)pIn->y;
	cvi_video_frame_buffer.region.pixelGrabW = (UINT32)pIn->w;
	cvi_video_frame_buffer.region.pixelGrabH = (UINT32)pIn->h;
	cvi_video_frame_buffer.region.colorDepth = 1; //10bits
	cvi_video_frame_buffer.color = (LX_DE_GRAB_COLOR_T *)pRead;
	cvi_video_frame_buffer.bReadOnOff = TRUE;

	switch (_gVPSrcInfo[wId].Type)
	{
		case SRC_INPUT_VGA:
			*pcolor_standard = VIDEO_DDI_COLOR_STANDARD_YUV;
			break;

		case SRC_INPUT_HDMI:
#ifdef USE_VP_HDMI_API
			ret = vp_kwrap_hdmi_rx_gethdmistate(hdmi_phys_port, &hdmiStatus);
			if(ret != RET_OK) DE_ERROR("vp_kwrap_hdmi_rx_gethdmistate fail");
#else
			if(hdmi20_kwrap_checkport)//need to add code for HDMi when we got the header file for HDMI//if(hdmi20_kwrap_CheckPor()
			{
				//ret = hdmi20_kwrap_rx_gethdmistate(UINT8 port, LX_HDMI_STATUS_T * pHdmiStatus)((UINT8)hdmi20_kwrap_get_connectedport(), &hdmiStatus);
			}
			else
			{
				hdmiStatus.prt_num = -1;
				ret  = hdmi_kwrap_gethdmistate(&hdmiStatus); need to do first HDMI 
			}
			if (ret != OK)
			{
				DE_ERROR("[HAL_VSC][%d] return error at KADP_HDMI_GetHDMIState.\n", __L__);
				return ret;
			}
#endif
			if (hdmiStatus.csc == LX_HDMI_AVI_COLORSPACE_RGB)
				*pcolor_standard = VIDEO_DDI_COLOR_STANDARD_YUV;	// CSC conversion is done by BSP
			else
				*pcolor_standard = VIDEO_DDI_COLOR_STANDARD_YUV;
			break;

		case SRC_INPUT_YPBPR:
			*pcolor_standard = VIDEO_DDI_COLOR_STANDARD_YUV;
			break;

		default:
			*pcolor_standard = VIDEO_DDI_COLOR_STANDARD_YUV;
			break;
	}

	DE_NOTI("[HAL_VSC][%d] win %d, dimension to be read (x,y,w,h)=(%d,%d,%d,%d) and CSC = %d .\n",\
		__L__,wId,(UINT32)pIn->x,(UINT32)pIn->y,(UINT32)pIn->w,(UINT32)pIn->h, *pcolor_standard);

	if ( lx_chip_rev() >= LX_CHIP_REV(M17,C0) ) /*Use VT capture for M16++(6)/O18(8) */
	{
		vp_kwrap_gettiminginfo(wId, &vpTimingInfo);

		ret = de_kwrap_read_cvivideoframebuffer_4k(cvi_video_frame_buffer, 0, 0, 0);
	}
	else if(chip_capa.chip_id >= 5) /*Use VT capture for M16 */
	{
		vp_kwrap_gettiminginfo(wId, &vpTimingInfo);
		if(vpTimingInfo.hActive > 2048)
			cvi_video_frame_buffer.region.pixelGrabX = cvi_video_frame_buffer.region.pixelGrabX >> 1;	//for 4K : capture only odd field
		ret = de_kwrap_read_cvivideoframebuffer_4k(cvi_video_frame_buffer, 0, 0, 0);
		/*
		   vp_kwrap_gettiminginfo(wId, &vpTimingInfo);
		   if(_gVPSrcInfo[wId].Type == SRC_INPUT_HDMI)
		   {
		   cvi_video_frame_buffer.region.realPixelGrabW = vpTimingInfo.hActive;
		   cvi_video_frame_buffer.region.realPixelGrabH = vpTimingInfo.vActive;
		   DE_NOTI("width = %d height=%d\n", cvi_video_frame_buffer.region.realPixelGrabW, cvi_video_frame_buffer.region.realPixelGrabH);
		   ret = de_kwrap_GetSourceCaptureBuffer(cvi_video_frame_buffer);
		   }
		   else
		   */
	}
	else if(chip_capa.chip_id == 4) /*Use VT capture for H15C0*/
	{
		vp_kwrap_gettiminginfo(wId, &vpTimingInfo);
		//ret = de_kwrap_Read_CviVideoFrameBuffer(cvi_video_frame_buffer, 0, 0);
		if(cvi_video_frame_buffer.region.pixelGrabX > 2048)
		{
			if(cvi_video_frame_buffer.region.pixelGrabX > (vpTimingInfo.hActive >> 1) )
				cvi_video_frame_buffer.region.pixelGrabX -= (vpTimingInfo.hActive >> 1);
			else
				cvi_video_frame_buffer.region.pixelGrabX = 0;
			ret = de_kwrap_read_cvivideoframebuffer_4k(cvi_video_frame_buffer, 0, 0, 1);
		}
		else
			ret = de_kwrap_read_cvivideoframebuffer_4k(cvi_video_frame_buffer, 0, 0, 0);
	}
	else
	{
		ret = de_kwrap_set_cvirwvideoframebuffer(cvi_video_frame_buffer);
	}

	if (_gHalVscDebugPrintOn)
	{
		int i,j;
		for ( i=0; i<pIn->h; i++)
		{
			for ( j=0; j<pIn->w; j++)
			{
				array_colorbar_level_Y +=  (pRead +j+(i*pIn->w))->pixelStandardY;
				array_colorbar_level_Cb += (pRead +j+(i*pIn->w))->pixelStandardCb;
				array_colorbar_level_Cr += (pRead +j+(i*pIn->w))->pixelStandardCr;
			}
		}
		DE_NOTI("[G:%03d] [B:%03d] [R:%03d] \n",array_colorbar_level_Y, array_colorbar_level_Cb, array_colorbar_level_Cr);
	}
	cvi_video_frame_buffer.color = NULL;

	if (ret != OK)
		DE_ERROR("[HAL_VSC][%d] return error at de_kwrap_set_cvirwvideoframebuffer.\n", __L__);

	return ret;
}


/**
* Write Video Frame Buffer.
*
* @param wId [IN] VIDEO_WID_T
* @param *pIn [IN] VIDEO_RECT_T
* @param *pWrite [IN] VIDEO_DDI_PIXEL_STANDARD_COLOR_T
* @return int
*/
DTV_STATUS_T hal_vsc_hwrap_writevideoframebuffer(VIDEO_WID_T wId, VIDEO_RECT_T *pIn, VIDEO_DDI_PIXEL_STANDARD_COLOR_T *pWrite)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_CVI_RW_VIDEO_FRAME_T cvi_video_frame_buffer;

	if (pIn == NULL || pWrite == NULL)
	{
		DE_ERROR("[HAL_VSC][%d] invalid parameters for pIn or pWrite.\n", __L__);
		return NOT_OK;
	}

	if (_gHalVscOpenStatus[wId] == FALSE)
	{
		DE_ERROR("[HAL_VSC][%d] WidID[%d] don't work when open status[%d] outputMode[%d]\n",\
			 __L__, wId, _gHalVscOpenStatus[wId],_gHalVscOutputMode[wId]);
		return NOT_OK;
	}

	wId = _VSC_Get_Winmap(wId);

	cvi_video_frame_buffer.region.win_id = wId;
	cvi_video_frame_buffer.region.pixelGrabX = (UINT32)pIn->x;
	cvi_video_frame_buffer.region.pixelGrabY = (UINT32)pIn->y;
	cvi_video_frame_buffer.region.pixelGrabW = (UINT32)pIn->w;
	cvi_video_frame_buffer.region.pixelGrabH = (UINT32)pIn->h;
	cvi_video_frame_buffer.region.colorDepth = 1; //10bits
	cvi_video_frame_buffer.color = (LX_DE_GRAB_COLOR_T *)pWrite;
	cvi_video_frame_buffer.bReadOnOff = FALSE;

	DE_NOTI("[HAL_VSC][%d] win %d, dimension to write (x,y,w,h)=(%d,%d,%d,%d).\n",\
		__L__,wId,(UINT32)pIn->x,(UINT32)pIn->y,(UINT32)pIn->w,(UINT32)pIn->h);

	ret = de_kwrap_set_cvirwvideoframebuffer(cvi_video_frame_buffer);

	if (ret != OK)
		DE_ERROR("[HAL_VSC][%d] return error at de_kwrap_set_cvirwvideoframebuffer.\n", __L__);

    return ret;
}


/**
 * 	hal_vsc_hwrap_setrgb444mode.
 *
 * 	@param bOnOff [in] BOOLEAN
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_setrgb444mode(BOOLEAN bOnOff)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_HDMI444_MODE_T hdmi_444_mode = LX_DE_HDMI444_NONE;

	if (bOnOff)
		hdmi_444_mode = LX_DE_HDMI444_ON;
	else
		hdmi_444_mode = LX_DE_HDMI444_OFF;

	ret = de_kwrap_sethdmi444mode(hdmi_444_mode);

	if (_gHalVscDebugPrintOn)
		DE_NOTI("[HAL_VSC][%d] HDMI444 mode = %d *** ",  __L__, bOnOff);

	return ret;
}

/**
* hal_vsc_hwrap_openV2G
* @param	wId [In] VIDEO_WID_T
* @return 	int
*/
DTV_STATUS_T hal_vsc_hwrap_openV2G(VIDEO_WID_T wId)
{
	DTV_STATUS_T	ret = OK;

	return ret;
}

/**
* DIL_VSC_CloseV2G
* @param	wId [In] VIDEO_WID_T
* @return 	int
*/
DTV_STATUS_T hal_vsc_hwrap_closeV2G(VIDEO_WID_T wId)
{
	DTV_STATUS_T	ret = OK;

	return ret;
}

/**
* hal_vsc_hwrap_GetV2GFramebuffer
* @param	wId [In] VIDEO_WID_T
* @param	pCaptureInfo [Out] VIDEO_DDI_CAPTURE_INFO_T
* @return 	int
*/
DTV_STATUS_T hal_vsc_hwrap_GetV2GFramebuffer(VIDEO_WID_T wId, VIDEO_DDI_CAPTURE_INFO_T* pCaptureInfo)
{
	DTV_STATUS_T	ret = OK;

	return ret;
}

/**
 * @brief Video Processor Thread function
 *
 * @return
 */
static void HAL_VIDEO_VP_Thread(void)
{
	//prctl (PR_SET_NAME, "VSC_vp", NULL, NULL, NULL);

	while (1)
	{
		if (_gHalVscInit == TRUE)
		{
			vp_kwrap_thread();
		}
		else
		{
			if (_gHalVscDebugPrintOn)
				DE_NOTI("[HAL_VSC][%d] VP Thread skip for uninit \n", __L__);
		}

		msleep(VP_THREAD_TIMEOUT);
	}

	kthread_stop(_gVPThread);
}

/**
 * 	HAL_VIDEO_SetUDInput
 *
 * 	@param VIDEO_UD_MODE_T
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetUDInput(VIDEO_UD_MODE_T videoUDMode)
{
	DTV_STATUS_T ret = OK;
	LX_DE_UD_CTRL_T udCtrl = LX_DE_UD_OFF;

	if (_gHalVscOpenStatus[VIDEO_WID_0] == FALSE || _gHalVscOutputMode[VIDEO_WID_0] != VSC_OUTPUT_DISPLAY_MODE)
	{
		DE_ERROR("[HAL_VSC][%d] don't work when open status[%d] outputMode[win0:%d]\n",\
			 __L__, _gHalVscOpenStatus[VIDEO_WID_0],_gHalVscOutputMode[VIDEO_WID_0]);
		ret = NOT_OK;
		return ret;
	}

	do {
		if (videoUDMode == UD_MODE_UD_HALF)
			udCtrl = LX_DE_UD_HALF;
		else if (videoUDMode == UD_MODE_UD)
			break;
		else
			udCtrl = LX_DE_UD_OFF;

		ret = de_kwrap_setudmode(udCtrl);
	} while (0);

	if (_gHalVscDebugPrintOn)
		DE_NOTI("[HAL_VSC][%d] UD input(0:FHD, 1:UD, 2:UD_HALF) = %d \n", __L__, videoUDMode);

	return ret;
}

/**
 * 	HAL_VIDEO_SetUDOutput
 *	 - DE부터 UD 출력과 FHD 출력을 변환함.
 *
 * 	@param VIDEO_DDI_DIS_FMT_T
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetUDOutput(VIDEO_DDI_DIS_FMT_T disFmt)
{
	DTV_STATUS_T ret = OK;
#if 0
	LX_DE_DIS_FMT_T de_dis_fmt;
	be_display_type_t	 stParams;
	be_frc_color_yuv444_t	 stParams1;
	LX_DE_OPERATION_CTRL_T param = {0, 0, 0, 0, {0xff, 0xff, 0xff, 0xff, 0xff}, };

	if (_gHalVscOpenStatus[VIDEO_WID_0] == FALSE || _gHalVscOutputMode[VIDEO_WID_0] != VSC_OUTPUT_DISPLAY_MODE \
		|| _gHalVscOutputMode[VIDEO_WID_1] == VSC_OUTPUT_DISPLAY_MODE)
	{
		DE_ERROR("[HAL_VSC][%d] don't work when open status[%d] outputMode[win0:%d][win1:%d].\n",\
			 __L__, _gHalVscOpenStatus[VIDEO_WID_0],_gHalVscOutputMode[VIDEO_WID_0],_gHalVscOutputMode[VIDEO_WID_1]);
		ret = NOT_OK;
		return ret;
	}

	do {
		if ((_gUDCtrl == LX_DE_UD_OFF) && (disFmt.isUD == FALSE))
		{
			if (_gHalVscDebugPrintOn)
				DE_NOTI("[HAL_VSC][%d] skip UD Output disable\n", __L__);

			break;
		}

		de_dis_fmt.fr_rate = disFmt.fr_rate;
		de_dis_fmt.h_total = disFmt.h_total;
		de_dis_fmt.v_total = disFmt.v_total;
		de_dis_fmt.dev_type = LX_PANEL_DEV_LCD;

		if (disFmt.isUD == TRUE)
			de_dis_fmt.panel_type = LX_PANEL_TYPE_3840;
		else
			de_dis_fmt.panel_type = LX_PANEL_TYPE_1920;

		ret |= de_kwrap_setdisfmt(de_dis_fmt); //출력 포맷설정 , 설정후 스케일링 설정에 문제발생

		if (disFmt.isUD == TRUE) //UD
		{
			param.operation = LX_DE_OPER_UD;
			param.udCtrl = LX_DE_UD_ON;
			ret |= vp_kwrap_setoperation(0, &param);

			/* BE settings for UD mode */
			stParams.u32BEPanelType	 =	2; /* 2: for UD 30Hz(2X) HSLVDS, 3:for 60Hz FHD HSLVDS */
			stParams.u32BEPanelRate	 =	0; /* leave empty. No function */
			stParams.u32BEPanelReverse	 =	0;/* leave empty. No function */
			stParams1.u8ColorYuv = 1; /* 0:422, 1:444 */
			stParams1.u8ColorDepth = 0xF; /* leave empty */
			stParams1.u8CompMode = 0xF; /* leave empty */

			/* 아래 함수 콜 순서가 중요함 */
			ret |= be_kwrap_frc_set_yuv_444_mode(&stParams1);
			ret |= be_kwrap_top_set_display_type(&stParams);
			_gUDCtrl = LX_DE_UD_ON;
		}
		else // FHD
		{
			param.operation = LX_DE_OPER_UD;
			param.udCtrl = LX_DE_UD_OFF;
			ret |= vp_kwrap_setoperation(0, &param);

			//FHD 설정시 FrameRate정보를 업데이트해줌.

			/* BE settings for UD mode */
			stParams.u32BEPanelType	 =	3; /* 2: for UD 30Hz(2X) HSLVDS, 3:for 60Hz FHD HSLVDS */
			stParams.u32BEPanelRate	 =	0; /* leave empty. No function */
			stParams.u32BEPanelReverse	 =	0;/* leave empty. No function */
			stParams1.u8ColorYuv = 0;//_gFRCStatus_RGB444; /* 0:422, 1:444 */
			stParams1.u8ColorDepth = 0xF; /* leave empty */
			stParams1.u8CompMode = 0xF; /* leave empty */
			/* 아래 함수 콜 순서가 중요함 */
			ret |= be_kwrap_top_set_display_type(&stParams);
			ret |= be_kwrap_frc_set_yuv_444_mode(&stParams1);
			_gUDCtrl = LX_DE_UD_OFF;
		}
	} while (0);

	if (_gHalVscDebugPrintOn)
		DE_NOTI("[HAL_VSC][%d] UD Output  isUD[%d]  frRate[%d] \n", __L__, disFmt.isUD, disFmt.fr_rate);

#endif
	return ret;
}

/**
 * 	hal_vsc_hwrap_GetVideoDelayedTime
 *	@param wId [In] VIDEO_WID_T
 * 	@param pDelayedTime [Out] UINT16 *
 * 	@return int
 */
DTV_STATUS_T	hal_vsc_hwrap_GetVideoDelayedTime (VIDEO_WID_T eWinId, UINT16 *pDelayedTime)
{
	DTV_STATUS_T ret = OK;
	LX_DE_LOW_DELAY_T param = {0, 0, 0, 0};

	eWinId = _VSC_Get_Winmap(eWinId);

	HAL_CHECK_SRC_ID(eWinId);
	HAL_CHECK_NULL(pDelayedTime);

	if (_gHalVscOpenStatus[eWinId] == FALSE)
	{
		DE_ERROR("[HAL_VSC][%d] wId[%d] when is not opened can not connect.\n", __L__, eWinId);
		ret = NOT_SUPPORTED;
		goto func_exit;
	}

	param.wId_enable = eWinId;
	ret = de_kwrap_getlowdelaymode(&param);

	//*pDelayedTime = (param.time /100) + ((param.time%100)>=50 ? 1 : 0);
	*pDelayedTime = (param.locked_time /100) + ((param.locked_time%100)>=50 ? 1 : 0);

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d] wid[%d] enable[%d] lock[%d] time[%d ms(00.00)] frame[%d(0.00)], loked_time[%d ms(00.00)]\n",\
			__L__, eWinId, param.wId_enable, param.lock, param.time, param.frame, param.locked_time);
	}

func_exit:

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetTileMode
 *	@param bOnOff [In] BOOLEAN
 * 	@return int
 */
DTV_STATUS_T 	hal_vsc_hwrap_SetTileMode(BOOLEAN bOnOff)
{
	DTV_STATUS_T ret = OK;

	if (_gHalVscOpenStatus[VIDEO_WID_0] == FALSE || _gHalVscOutputMode[VIDEO_WID_0] != VSC_OUTPUT_DISPLAY_MODE)
	{
		DE_ERROR("[HAL_VSC][%d] don't work when open status[%d] outputMode[win0:%d]\n",\
			 __L__, _gHalVscOpenStatus[VIDEO_WID_0],_gHalVscOutputMode[VIDEO_WID_0]);
		ret = NOT_OK;
		return ret;
	}

	if (bOnOff == TRUE)
	{
		_gTileInfo.isTile = TRUE;
	}
	else
	{
		_gTileInfo.isTile = FALSE;
		_gTileInfo.uMaxRow = 0xffff;
		_gTileInfo.uMaxCol = 0xffff;
		_gTileInfo.uTileID= 0xffff;

		ret = de_kwrap_setmultivision(0, 0, 0, 0);
	}

	if (_gHalVscDebugPrintOn)
		DE_NOTI("[HAL_VSC][%d] Tile Mode bOnOff[%d]\n", __L__, bOnOff);

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetTileMaxRowVal
 *	@param uMaxRow [In] UINT8
 *	@param uMaxCol [In] UINT8
 * 	@return int
 */
DTV_STATUS_T 	hal_vsc_hwrap_SetTileMaxRowVal(UINT8 uMaxRow, UINT8 uMaxCol)
{
	DTV_STATUS_T ret = OK;

	if (_gTileInfo.isTile == TRUE)
	{
		_gTileInfo.uMaxRow = uMaxRow;
		_gTileInfo.uMaxCol = uMaxCol;

		ret = de_kwrap_setmultivision(_gTileInfo.uMaxRow, _gTileInfo.uMaxCol, 0, 0);

		if (_gHalVscDebugPrintOn)
		DE_NOTI("[HAL_VSC][%d] Tile Mode bOnOff[%d], Row[%d], Col[%d] \n", __L__, _gTileInfo.isTile, uMaxRow, uMaxCol);
	}
	else
	{
		DE_ERROR("[HAL_VSC][%d] Tile Mode Status is disable\n", __L__);
		ret = NOT_OK;
	}

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetTileID
 *	@param uTileID [In] UINT8
 * 	@return int
 */
DTV_STATUS_T 	hal_vsc_hwrap_SetTileID(UINT8 uTileID)
{
	DTV_STATUS_T ret = OK;
	UINT16 x = 0, y = 0;

	if (_gTileInfo.isTile == TRUE &&	 _gTileInfo.uMaxRow != 0xffff && _gTileInfo.uMaxCol != 0xffff && uTileID > 0)
	{
		uTileID = uTileID - 1;

		if (uTileID > 0)
		{
			if (_gTileInfo.uMaxRow > 1 && _gTileInfo.uMaxCol > 1)
			{
				x = uTileID % _gTileInfo.uMaxRow;
				y = (uTileID / _gTileInfo.uMaxRow) % _gTileInfo.uMaxCol;
			}
			else if (_gTileInfo.uMaxRow == 1 && _gTileInfo.uMaxCol > 1)
			{
				y = uTileID;
			}
			else if (_gTileInfo.uMaxRow > 1 && _gTileInfo.uMaxCol == 1)
			{
				x = uTileID;
			}
		}

		ret = de_kwrap_setmultivision(_gTileInfo.uMaxRow, _gTileInfo.uMaxCol, x, y);

		if (_gHalVscDebugPrintOn)
		{
			DE_NOTI("[HAL_VSC][%d] Tile Mode bOnOff[%d], Row[%d], Col[%d] \n", \
				__L__, _gTileInfo.isTile, _gTileInfo.uMaxRow, _gTileInfo.uMaxCol);
			DE_NOTI("[HAL_VSC][%d] Tile ID[%d], x[%d], y[%d] \n", __L__, _gTileInfo.isTile, x, y);
		}
	}
	else
	{
		DE_ERROR("[HAL_VSC][%d] Tile Mode Status is disable\n", __L__);
		ret = NOT_OK;
	}

	return ret;
}

/**
 * 	hal_vsc_hwrap_setadaptivestream
 *	@param wId [In] VIDEO_WID_T
 *	@param bOnOff [In] BOOLEAN
 * 	@return int
 */
DTV_STATUS_T 	hal_vsc_hwrap_setadaptivestream(VIDEO_WID_T wId, BOOLEAN bOnOff)
{
	DTV_STATUS_T ret = OK;
	LX_DE_ACT_FORMAT_T param = {0, 0};

	if (_gHalVscOpenStatus[VIDEO_WID_0] == FALSE || _gHalVscOutputMode[VIDEO_WID_0] != VSC_OUTPUT_DISPLAY_MODE)
	{
		DE_ERROR("[HAL_VSC][%d] don't work when open status[%d] or outputMode[win0:%d]\n",\
			 __L__, _gHalVscOpenStatus[VIDEO_WID_0],_gHalVscOutputMode[VIDEO_WID_0]);
	}

	if(_gAdaptive_4k_window == 2 && bOnOff == 1)
	{
		param.enable = 2;
	}
	else
	{
		_gAdaptive_4k_window = param.enable = bOnOff;
	}

	param.win_id = (UINT16)wId;

	ret = vp_kwrap_setactfmtdetect(param);

	DE_NOTI("[HAL_VSC][%d]  Adaptive Stream control win_id[%d] enable[%d] \n", \
		__L__,  param.win_id, param.enable);

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetLocalMute
 *	@param bOnOff [In] int  (0:enable local mute, 1:disable local mute)
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetLocalMute( UINT16 bOnOff )
{
	DTV_STATUS_T ret = OK;
	LX_DE_SET_DBG_T ctrl;

	ctrl.type = LX_DE_DBG_MUTE_DISABLE;
	ctrl.u32Param = bOnOff;

	ret = de_kwrap_setdbgctrl(ctrl);

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d]  Local mute control [%d] - enable/disable : 0/1\n", \
			__L__, bOnOff);
	}

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetQuadWinMode
 *	@param bOnOff [In] int  (0:quad window mode off, 1:on)
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetQuadWinMode( UINT16 bOnOff )
{
	DTV_STATUS_T ret = OK;

	_gQuadWin = bOnOff;
	ret = vp_kwrap_setquadwinmode(bOnOff);

	DE_NOTI("[HAL_VSC][%d]  set quad window [%d] - disable/enable : 0/1\n", \
			__L__, bOnOff);

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetPBPMode
 *	@param bOnOff [In] int  (0:off, 1:on)
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetPBPMode( UINT16 bOnOff )
{
	DTV_STATUS_T ret = OK;

	_gPBPMode = bOnOff;

	DE_NOTI("[HAL_VSC][%d]  set PBP mode [%d] - disable/enable : 0/1\n", \
			__L__, bOnOff);

	return ret;
}

/**
 * hal_vsc_hwrap_SetInput
 * @param wId [in] VIDEO_WID_T.
 * @param inRegion [in] VIDEO_RECT_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T	hal_vsc_hwrap_SetInput(VIDEO_WID_T wId, VIDEO_RECT_T inRegion, VIDEO_RECT_T srcInfo)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_RECT_T 	inWin = {0, 0, 0, 0};
	LX_DE_RECT_T 	inSize = {0, 0, 0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	inWin.h = _gDeInWin[wId].h = inRegion.h;	//for backup  //  _gDeInWin 수정 금지.
	inWin.w = _gDeInWin[wId].w = inRegion.w;
	inWin.x = _gDeInWin[wId].x = inRegion.x;
	inWin.y = _gDeInWin[wId].y = inRegion.y;

	inSize.h = srcInfo.h;	//for backup  //  _gDeInWin 수정 금지.
	inSize.w = srcInfo.w;
	inSize.x = srcInfo.x;
	inSize.y = srcInfo.y;

	ret = vp_kwrap_setinputsize(wId, inSize);
	ret |= vp_kwrap_setinputwin(wId, inWin);

	DE_NOTI("[HAL_VSC][%d] Set wId[%d] Source size  xywh(%d,%d,%d,%d)***", \
			__L__, wId, inSize.x, inSize.y, inSize.w, inSize.h);
	DE_NOTI("[HAL_VSC][%d] Set wId[%d] Input window xywh(%d,%d,%d,%d)***", \
			__L__, wId, inWin.x, inWin.y, inWin.w, inWin.h);

	return ret;
}

/**
 * hal_vsc_hwrap_SetOutput
 * @param wId [in] VIDEO_WID_T.
 * @param outRegion [in] VIDEO_RECT_T.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T	hal_vsc_hwrap_SetOutput(VIDEO_WID_T wId, VIDEO_RECT_T outRegion, VIDEO_RECT_T srcInfo)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_RECT_T 	outWin = {0, 0, 0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	if (_gHalVscDisableOutWindow == TRUE)
	{
		DE_NOTI("[HAL_VSC][%d] SKIP wId[%d] out_xywh(%d,%d,%d,%d).\n", \
			__L__, wId, outRegion.x, outRegion.y, outRegion.w, outRegion.h);
		return ret;
	}

	outWin.h = _gDeOutWin[wId].h = outRegion.h; // _gDeOutWin for backup
	outWin.w = _gDeOutWin[wId].w = outRegion.w;
	outWin.x = _gDeOutWin[wId].x = outRegion.x;
	outWin.y = _gDeOutWin[wId].y = outRegion.y;

	do {
		if ((wId >= VIDEO_WID_1) && (_gHalVscOutputMode[wId] > VSC_OUTPUT_DISPLAY_MODE) )
		{
			if (_gHalVscDebugPrintOn)
				DE_NOTI("[HAL_VSC][%d]  Set wId[%d] Skip output window \n", __L__, wId);
			break;
		}
		ret = vp_kwrap_setoutwin(wId, outWin);

		DE_NOTI("[HAL_VSC][%d]  Set wId[%d] Window out_xywh(%d,%d,%d,%d)***", \
			__L__, wId,outWin.x, outWin.y, outWin.w, outWin.h);
	} while (0);

	return ret;
}

/**
 *  hal_vsc_hwrap_setdelaybuffer
 * @param wId [in] VIDEO_WID_T.
 * @param ubuffer [in] buffer number for delay.
 * @return if succeeded - RET_OK, else - RET_ERROR.
 */
DTV_STATUS_T hal_vsc_hwrap_setdelaybuffer(VIDEO_WID_T wId, UINT8 ubuffer)
{
	DTV_STATUS_T	ret = OK;

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	ret = vp_kwrap_setdelaybuffer(wId, ubuffer);

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetSubWinMode
 *
 *	@param Op_mode [In] VSC_SUB_MODE_T   Sub window type (PIP/PBP)
 *	@param bOverrange [In] BOOLEAN
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_setsubwinmodeex(VSC_SUB_MODE_T mode, VSC_SUB_CONNECT_TYPE_T connectType, VSC_SUB_MEMORY_USE_T memoryUse)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_SUB_MODE_T sub_mode = LX_DE_SUB_MODE_NONE;
	LX_DE_OPERATION_CTRL_T 	vpOprParam = {0, LX_DE_OPER_ONE_WIN, FALSE, LX_DE_UD_OFF, {0xff, 0xff, 0xff, 0xff, 0xff}, {2, LX_DE_PROGRESSIVE, 0, 0, 0}};
	LX_DE_CAPACITY_T capa;

	de_kwrap_getcapacity(&capa);

	DE_NOTI("mode[%d] connectType[%d] memoryUse[%d]\n", mode, connectType, memoryUse);

	switch(mode)
	{
		case VSC_SUB_MODE_PBP :
			sub_mode = LX_DE_SUB_MODE_PBP;
			_gPBPMode = TRUE;
			break;
		case VSC_SUB_MODE_PIP :
			if(connectType == VSC_SUB_CONNECT_TYPE_MIRROR && memoryUse == VSC_SUB_MEMORY_USE_MULTI)
			{
				sub_mode = LX_DE_SUB_MODE_LIVEZOOM; // live zoom
			}
			else if(connectType == VSC_SUB_CONNECT_TYPE_MIRROR && memoryUse == VSC_SUB_MEMORY_USE_SINGLE)
			{
				sub_mode = LX_DE_SUB_MODE_MAGZOOM; // magnifier
			}
			else if(connectType == VSC_SUB_CONNECT_TYPE_NON_MIRROR && memoryUse == VSC_SUB_MEMORY_USE_MULTI)
			{
				sub_mode = LX_DE_SUB_MODE_PIP; // overlay miracast
			}
			else
			{
				sub_mode = LX_DE_SUB_MODE_NONE;
			}
			_gPBPMode = FALSE;
			break;
		default :
			sub_mode = LX_DE_SUB_MODE_NONE;
			_gPBPMode = FALSE;
			break;
	}

	ret = vp_kwrap_setsubwinmode(sub_mode);

	if(ret != OK) DE_ERROR("ret = %d", ret);

	if(capa.chip_id >= 5/*M16 only*/ && _gHalVscOutputMode[1] == VSC_OUTPUT_MAXN && sub_mode == LX_DE_SUB_MODE_NONE)
	{
		vpOprParam.operation = LX_DE_OPER_TWO_WIN;
		vpOprParam.multiCtrl = FALSE;
		ret = vp_kwrap_setoperation(1, &vpOprParam);
		DE_NOTI("set multi win off. (_gHalVscOutputMode[1] == VSC_OUTPUT_MAXN)");
	}

	DE_NOTI("[HAL_VSC][%d]  SetSubWinMode [%d] (0:OFF, 1:PIP, 2:PBP, 5:LZ, 6:MZ)************************\n", __L__, sub_mode);

	return ret;
}

/**
 * 	hal_vsc_hwrap_setsubwinshape
 *
 *	@param Op_mode [In] VSC_SUB_SHAPE_T   Sub window shape (CIRCLE/RECTANGLE )
 *	@param rect [In] VIDEO_RECT_T
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_setsubwinshape(VSC_SUB_SHAPE_T shape, VIDEO_RECT_T rect)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_SUB_MGF_SHAPE_T sub_shape;
	LX_DE_RECT_T	orgWin = {0, 0, 0, 0};

	switch(shape)
	{
		case VSC_MGF_TYPE_CIRCLE :
			sub_shape = LX_DE_MGF_TYPE_CIRCLE;
			break;
		case VSC_MGF_TYPE_RECTANGLE :
		default :
			sub_shape = LX_DE_MGF_TYPE_RECTANGLE;
			break;
	}

	orgWin.x = orgWin.y = 0;
	orgWin.w = rect.w;
	orgWin.h = rect.h;
	ret = vp_kwrap_setsubwinshape(sub_shape, orgWin);

	if(ret != OK) DE_ERROR("ret = %d", ret);

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d]  SetSubWinShape shape , rect(w/h) [%d] , [%d/%d] - \n", \
			__L__, shape, rect.w, rect.h);
	}

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetSignageMode
 *
 *	@param rect [In] bOnOff
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetSignageMode(BOOLEAN bOnOff)
{
	DTV_STATUS_T	ret = OK;


	if(bOnOff != 0)
		bOnOff = 1;

	ret = de_kwrap_setsignagemode(bOnOff);
	if(ret != OK) DE_ERROR("ret = %d", ret);

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d]  hal_vsc_hwrap_SetSignageMode bOnOff=[%d]\n", __L__, bOnOff);
	}

	return ret;
}

/**
 * 	hal_vsc_hwrap_setzorder
 *
 *	@param zOrder [In] order/alpha , uWindowNo [In] max window
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_setzorder(VSC_ZORDER_T *zOrder, UINT8 uWindowNo)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_ZLIST_T param;

	if(uWindowNo > VIDEO_WID_MAX)
		return NOT_OK;

	param.enable = TRUE;
	param.z_list[0] = zOrder[0].uZorder;
	param.z_list[1] = zOrder[1].uZorder;
	param.alpha[0]  = zOrder[0].uAlpha;
	param.alpha[1]  = zOrder[1].uAlpha;

	ret = de_kwrap_setzorderandalphablending(param);

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetDualMode (for Netflix dual video effect)
 *
 *	@param bOnOff [In] on/off
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetDualMode(BOOLEAN bOnOff)
{
	DTV_STATUS_T	ret = OK;

	ret = de_kwrap_set4kdualmode(bOnOff);

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d]  hal_vsc_hwrap_SetDualMode bOnOff=[%d]\n", __L__, bOnOff);
	}
	return ret;
}

/**
 * 	hal_vsc_hwrap_makecoloredvideo (for white pattern)
 *
 *	@param videoColor [In] on/off
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_makecoloredvideo(VSC_VIDEO_COLOR_TYPE_T videoColor)
{
	DTV_STATUS_T	ret = OK;

	LX_DE_INNER_PATTERN_T inner_param;
	UINT8 greyPattern20PointsIRE[21] =
	/* IRE      0|  5|  10| 15| 20| 25| 30| 35|  40|  45|  50|  55|  60|  65|  70|  75|  80|  85|  90|  95| 100| */
	/* Level *///{	0, 19, 38, 49, 60, 71, 82, 93, 104, 115, 126, 137, 147, 158, 169, 180, 191, 202, 213, 224, 235};
	/* Level */{16, 27, 38, 49, 60, 71, 82, 93, 104, 115, 126, 137, 147, 158, 169, 180, 191, 202, 213, 224, 235};

	inner_param.level = (UINT32)greyPattern20PointsIRE[20];
	switch (videoColor)
	{
		case VSC_VIDEO_COLOR_WHITE:
			inner_param.enable = 0x1;
			inner_param.type = LX_DE_PATTERN_WHITE_BOX_MOVING;
			break;
		case VSC_VIDEO_COLOR_OFF:
		default:
			inner_param.enable = 0x0;
			inner_param.type = LX_DE_PATTERN_FULL_GRAY;	//default
			break;
	}

	ret = de_kwrap_setinnerpattern(&inner_param);

	if (_gHalVscDebugPrintOn)
	{
		DE_NOTI("[HAL_VSC][%d]  hal_vsc_hwrap_makecoloredvideo bOnOff=[%d]\n", __L__, videoColor);
	}

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetTwinZoom
 *
 *	@param bOnOff [In] on/off
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_SetTwinZoom(BOOLEAN bOnOff)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_SUB_MODE_T sub_mode;

	if(_gPBPMode == TRUE)
	{
		DE_NOTI(" _gPBPMode == TRUE, skip this control...\n");
		return ret;
	}

	switch(bOnOff)
	{
		case TRUE :
			sub_mode = LX_DE_SUB_MODE_TWIN_ON;
			break;
		case FALSE :
		default :
			sub_mode = LX_DE_SUB_MODE_TWIN_OFF;
			break;
	}

	ret = vp_kwrap_setsubwinmode(sub_mode);

	DE_NOTI(" bOnOff [%d]\n", bOnOff);

	return ret;
}

/**
 * 	hal_vsc_hwrap_rotatevideo
 *
 *	@param rotation   [IN] rotation degree 0', 90', 180', 270'
 * 	@return int
 */
DTV_STATUS_T hal_vsc_hwrap_rotatevideo(VIDEO_WID_T wId, VSC_ROTATE_T rotation)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_ROTATE_INFO_T lx_rotate;

	if(wId > 0)
	{
		DE_ERROR(" not support this window [%d] - %d \n", wId, rotation);
		return NOT_OK;
	}

	switch(rotation)
	{
		case VSC_ROTATE_0:
		default:
			lx_rotate = LX_DE_ROTATE_0;
			break;
		case VSC_ROTATE_90:
			lx_rotate = LX_DE_ROTATE_90;
			break;
		case VSC_ROTATE_180:
			lx_rotate = LX_DE_ROTATE_180;
			break;
		case VSC_ROTATE_270:
			lx_rotate = LX_DE_ROTATE_270;
			break;
	}

	ret = de_kwrap_setrotate(lx_rotate);

	DE_NOTI(" rotation 0/90/180/270 degree  [%d]  [0/1/2/3] \n", rotation);

	return ret;
}

DTV_STATUS_T    hal_vsc_hwrap_registermuteoffcallback(PFN_VSC_NOTIFY_MUTE_OFF_T pfnMuteOffCB)
{
	DTV_STATUS_T	ret = OK;

	ret = vp_kwrap_registermuteoffcallback((PFN_VP_NOTIFY_MUTE_OFF_T)pfnMuteOffCB);

	return ret;
}

DTV_STATUS_T    hal_vsc_hwrap_getlimitedwindow(VIDEO_WID_T wId, VSC_SCALER_RATIO_T *scalerRatio)
{
	DTV_STATUS_T	ret = OK;

	scalerRatio->h_scaleup_ratio = 0;
	scalerRatio->v_scaleup_ratio = 0;
	scalerRatio->h_scaledown_ratio = 0;
	scalerRatio->h_scaledown_ratio = 0;

	return ret;
}

DTV_STATUS_T    hal_vsc_hwrap_setpattern(BOOLEAN bOnOff, VIDEO_WID_T wId, VIDEO_PATTERN_LOCATION_T pattern_location)
{
	DTV_STATUS_T	ret = OK;
	LX_DE_SET_DBG_T param;

	param.type           = LX_DE_DBG_SET_PATTERN;
	param.pattern.win_id = (LX_DE_WIN_ID_T)wId;;
	param.pattern.bOnOff = bOnOff;

	switch(pattern_location)
	{
		case VIDEO_PATTERN_MUX:
			param.pattern.location = LX_DE_PAT_INPUT;
			break;
		case VIDEO_PATTERN_DI_NR:
			param.pattern.location = LX_DE_PAT_ND;
			break;
		case VIDEO_PATTERN_SCALER:
			param.pattern.location = LX_DE_PAT_SRE;
			break;
		case VIDEO_PATTERN_MEMC:
			param.pattern.location = LX_DE_PAT_WCP;
			break;
		case VIDEO_PATTERN_DISPLAY:
		default:
			param.pattern.location = LX_DE_PAT_LED;
			break;
	}

	ret = de_kwrap_setdbgctrl(param);

	DE_NOTI(" win[%d] onoff[%d] pattern input/ND/SRE/FMC/LED  %d\n", \
		param.pattern.win_id, param.pattern.bOnOff, param.pattern.location);

	return ret;
}

#if 1
VIDEO_WID_T g_wId_map[VIDEO_WID_MAXN] = {0, 1, 2, 3};

VIDEO_WID_T _VSC_Set_Winmap(VIDEO_WID_T wId, VSC_INPUT_SRC_INFO_T vscInput, VSC_OUTPUT_MODE_T outputmode)
{
	DTV_STATUS_T ret = OK;

	LX_DE_CAPACITY_T capa;

	de_kwrap_getcapacity(&capa);

	if(wId > VIDEO_WID_MAX) return NOT_OK;

	if(wId > 0)
	{
		switch(outputmode)
		{
#if 0
			case VSC_OUTPUT_DISPLAY_MODE:
				if(capa.max_win > 1)
					g_wId_map[wId] = 2;
				else
					g_wId_map[wId] = 1;
				break;
#endif
			case VSC_OUTPUT_VENC_MODE:
				if(capa.max_win > 2)
					g_wId_map[wId] = 2;
				else
					g_wId_map[wId] = 1;
				break;
			default:
				g_wId_map[wId] = wId;
				break;
		}
	}

	return ret;
}

VIDEO_WID_T _VSC_Get_Winmap(VIDEO_WID_T wId)
{
	if(wId > VIDEO_WID_MAX) return VIDEO_WID_MAX;
	return g_wId_map[wId];
}
#endif

typedef enum
{
    VSC_PIVOT_MODE_NONE = 0,
	VSC_PIVOT_MODE_0_CW,
    VSC_PIVOT_MODE_90_CW,
    VSC_PIVOT_MODE_270_CW,
} VSC_PIVOT_MODE_T;

/**
 * 	hal_vsc_hwrap_SetContentRotateMode
 *
 *	@param pivot_ctrl [In] pivot mode
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_SetContentRotateMode(VSC_PIVOT_MODE_T pivot_ctrl)
{
	DTV_STATUS_T ret = OK;

#ifdef USE_SIGNAGE_FEATURE
#if defined(CHIP_NAME_h15)
	BOOLEAN quadMode = _gQuadWin;

	quadMode = TRUE;

	if (pivot_ctrl != VSC_PIVOT_MODE_NONE)
	{
		if (!_gQuadWin)
		{
			// take over mute control from HAL_VSC
			hal_vsc_hwrap_setwinblank (0, FALSE, VIDEO_DDI_WIN_COLOR_BLACK);
			hal_vsc_hwrap_setwinblank (1, FALSE, VIDEO_DDI_WIN_COLOR_BLACK);
			hal_vsc_hwrap_setwinblank (2, FALSE, VIDEO_DDI_WIN_COLOR_BLACK);
			hal_vsc_hwrap_setwinblank (3, FALSE, VIDEO_DDI_WIN_COLOR_BLACK);
		}
		hal_vsc_hwrap_SetQuadWinMode (TRUE);
	}
	else
	{
		hal_vsc_hwrap_SetQuadWinMode (FALSE);
	}

	//ret = VDE_SetContentRotateMode(quadMode, pivot_ctrl);
#endif
#endif

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetRotatedOutputRegion
 *
 *	@param wid [In] window id , outRegion [In] output region size
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_SetRotatedOutputRegion(VIDEO_WID_T wid, VIDEO_RECT_T outRegion)
{
	DTV_STATUS_T ret = OK;

#ifdef USE_SIGNAGE_FEATURE
#if defined(CHIP_NAME_h15)
	//ret = VDE_SetRotatedOutputRegion(wid, outRegion);
#endif
#endif

	return ret;
}

/**
 * 	hal_vsc_hwrap_DM_Open
 *
 *	@param
 * 	@return DTV_STATUS_T
 */
static DTV_STATUS_T hal_vsc_hwrap_DM_Open(void)
{
	DTV_STATUS_T ret = OK;

	if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)) {
		//ret = HAL_GCP_Open(_gHDRControl);
	}
	return ret;
}

/**
 * 	hal_vsc_hwrap_hdr_open
 *	@param wId [In] VIDEO_WID_T
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_hdr_open(VIDEO_WID_T wId)
{
	return OK;//HAL_GCP_Open(_gHDRControl);
}

/**
 * 	hal_vsc_hwrap_DM_Close
 *
 *	@param
 * 	@return DTV_STATUS_T
 */
static DTV_STATUS_T hal_vsc_hwrap_DM_Close(void)
{
	DTV_STATUS_T ret = OK;

	if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)) {
		//ret = HAL_GCP_Close();
	}
	return ret;
}

/**
 * 	hal_vsc_hwrap_hdr_close
 *	@param wId [In] VIDEO_WID_T
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_hdr_close(VIDEO_WID_T wId)
{
	return OK;//HAL_GCP_Close();
}

/**
 * 	hal_vsc_hwrap_DM_Connect
 *
 *	@param
 * 	@return DTV_STATUS_T
 */
static DTV_STATUS_T hal_vsc_hwrap_DM_Connect(void)
{
	UINT32 pipemode;
	int ret;

	if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)) {
		DE_NOTI("This API is Duplicated!!! Use hal_vsc_hwrap_hdr_connect\n");
		return RET_ERROR;
	}

	switch(_gVPSrcInfo[0].Type)
	{
		case SRC_INPUT_HDMI:
			pipemode = 2;
			break;
		case SRC_INPUT_DTV:
		case SRC_INPUT_MVI:
			pipemode = 1;
			break;
		default:
			pipemode = 0;
			DE_ERROR("not available ");
			break;
	}

	DE_NOTI("pipemode = %d (NONE:0/OTT:1/HDMI:2)", pipemode);

	if(pipemode == 2 && (lx_chip_rev() < LX_CHIP_REV(M17,A0)))
	{
		//Not for DOlby IP implementation
		DE_NOTI("fork dovi !!!\n");
		//ret = HAL_GCP_Fork();

		if(ret != OK)
		{
			if(ret==1)	DE_ERROR("already forked.\n");
			else		DE_ERROR("fork dovi fail(%d) !!!\n",ret);
		}
	}

	//ret = HAL_DHDR_Connect(0,pipemode);//need to add 

	return ret;
}

/**
 * 	hal_vsc_hwrap_hdr_connect
 *	@param wId [In] VIDEO_WID_T
 *	@param eHdrMode [In] VSC_HDR_TYPE_T
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_hdr_connect(VIDEO_WID_T wId,VSC_HDR_TYPE_T eHdrMode)
{
	UINT32 pipemode;
	int ret;
	LX_HDR_MODE_T ipcMode;
	int nDovi_InputCount = 0;
	UINT32 data[2];
	int unmutestatus = 0;
	DE_NOTI("wId:%d, cur HDR:%d(0~5:HDR10,DOLBY,VP9,HLG,PRIME,DOLBY LL)", wId, eHdrMode);
	if (lx_chip_rev() >= LX_CHIP_REV(O18,A0))
	{
		if(wId >= VIDEO_WID_1)
		{
			DE_NOTI("chip:%x,not supported.",lx_chip_rev());
			return OK;
		}
	}
	else
	{
		if(wId >= VIDEO_WID_1)
		{
			DE_NOTI("chip:%x,not supported.",lx_chip_rev());
			return OK;
		}
	}

	DE_NOTI("HDR Connect!!! VSC API Status [%d]",_gsHalAPIStatus[wId].eVscStatus);
	DE_NOTI("HDR Connect!!! VDO API Status [%d]",_gsHalAPIStatus[wId].eVdoStatus);

	do{
		switch(_gVPSrcInfo[wId].Type)
		{
			case SRC_INPUT_HDMI:
				{
					pipemode = (eHdrMode==VSC_HDR_DOLBY_LL)?3 : 2;
				}
				break;
			case SRC_INPUT_DTV:
			case SRC_INPUT_MVI:
				{
					pipemode = 2;
				}
				break;
			default:
				{
					pipemode = 0;
					DE_ERROR("not available.......,Cnt : [%d]!!",nDovi_InputCount);
				}
				break;
		}

		if((pipemode == 2) || (pipemode == 3) || (pipemode == 1)) {
			DE_NOTI(" HDR input Updated : [%d:%d]!!\n",pipemode,nDovi_InputCount);
			break;
		}
		nDovi_InputCount++;
		msleep(200000);
	}while(nDovi_InputCount <= HAL_MAX_INPUT_CHECK);

	if(nDovi_InputCount > HAL_MAX_INPUT_CHECK) {
		DE_ERROR(" HDR Input is not Updated : [%d:%d]\n",pipemode,nDovi_InputCount);
	}

	DE_NOTI("pipemode:%d(0~3:NONE,OTT,HDMI,HDMI LL)", pipemode);

	if(pipemode == 2 && (lx_chip_rev() < LX_CHIP_REV(M17,A0)))
	{
		//Not for DOlby IP implementation
		DE_NOTI("fork dovi !!!\n");
		//ret = HAL_GCP_Fork();

		if(ret != OK)
		{
			if(ret==1)	DE_ERROR("already forked.\n");
			else		DE_ERROR("fork dovi fail(%d) !!!\n",ret);
		}
	}

	gsHdrInfo[wId].ewinId = wId;
	_gsHalAPIStatus[wId].ewinId = wId;

	if((_geHDROnOff != VSC_HDR_OFF) && ((eHdrMode == VSC_HDR_DOLBY)\
		|| (eHdrMode == VSC_HDR_DOLBY_LL) || (gsHdrInfo[wId].eHdrMode == VSC_HDR_DOLBY)\
		|| (gsHdrInfo[wId].eHdrMode == VSC_HDR_DOLBY_LL))) {
		/*if(!vp_kwrap_ismuteon(wId)) {
		vp_kwrap_setwinblank(wId, 1, 0, 0);
			DE_NOTI("Muting for HDR Mode Change\n");
			unmutestatus = 1;
		}
		else {
			DE_NOTI("Already in mute state \n");
		}*/
		//ret = HAL_DHDR_Disconnect(wId);
		if(ret)
		{
			DE_ERROR("HAL_DHDR_Disconnect error....\n");
			return RET_ERROR;
		}
		DE_NOTI("Calling Disconnect for HDR type %d\n",_geHDROnOff);
	}

	switch(eHdrMode)
	{
		case VSC_HDR_DOLBY:
		case VSC_HDR_DOLBY_LL:
			{
				ipcMode = LX_HDR_TYPE_DOLBY;
				//ret = HAL_DHDR_Connect(wId,pipemode);
			}
			break;
		case VSC_HDR_HDR10:
			{
				ipcMode = LX_HDR_TYPE_HDR10;
				ret = de_kwrap_setipchdrmode(wId,ipcMode,LX_HDR_MODE_FROM_SCL);
			}
			break;
		case VSC_HDR_VP9:
			{
				ipcMode = LX_HDR_TYPE_OFF;
				DE_NOTI("VP9 Not supported yet!!!\n");
				ret = RET_ERROR;
			}
			break;
		case VSC_HDR_HLG:
			{
				ipcMode = LX_HDR_TYPE_HLG;
				ret = de_kwrap_setipchdrmode(wId,ipcMode,LX_HDR_MODE_FROM_SCL);
			}
			break;
		case VSC_HDR_PRIME:
			{
				ipcMode = LX_HDR_TYPE_TECHNICOLOR;
				ret = de_kwrap_setipchdrmode(wId,ipcMode,LX_HDR_MODE_FROM_SCL);
			}
			break;
		default:
			{
				ipcMode = LX_HDR_TYPE_OFF;
				ret = de_kwrap_setipchdrmode(wId,ipcMode,LX_HDR_MODE_FROM_SCL);
			}
			break;
	}
	data[0] = wId;
	data[1] = (UINT32)ipcMode;
	//KWRAP_PE_SetHdrConnect(data);

	if(((_geHDROnOff != VSC_HDR_OFF) && unmutestatus == 1) && ((eHdrMode == VSC_HDR_DOLBY)\
		|| (eHdrMode == VSC_HDR_DOLBY_LL) || (gsHdrInfo[wId].eHdrMode == VSC_HDR_DOLBY)\
		|| (gsHdrInfo[wId].eHdrMode == VSC_HDR_DOLBY_LL))) {
		vp_kwrap_setwinblank(wId, 0, 0, 0);
	}

	gsHdrInfo[wId].eHdrMode = eHdrMode;
	_gsHalAPIStatus[wId].eHdrMode = eHdrMode;
	_geHDROnOff = VSC_HDR_ON;

	return ret;
}

/**
 * 	hal_vsc_hwrap_DM_Disconnect
 *
 *	@param
 * 	@return DTV_STATUS_T
 */
static DTV_STATUS_T hal_vsc_hwrap_DM_Disconnect(void)
{
	int ret;

	if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)) {
		DE_NOTI("This API is Duplicated!!! Use hal_vsc_hwrap_hdr_disconnect\n");
		return RET_ERROR;
	}

	//ret = HAL_DHDR_Disconnect(0);

	if(ret != OK)
		DE_ERROR("disconnect fail !!!\n");

	if(_gVPSrcInfo[0].Type == SRC_INPUT_HDMI)
	{
		DE_NOTI("kill dovi !!!\n");
		//ret = HAL_GCP_Kill();

		if(ret != OK)
		{
			DE_ERROR("kill dovi fail !!!\n");
		}
	}

	DE_NOTI("Done.");

	return ret;
}

/**
 * 	hal_vsc_hwrap_hdr_disconnect
 *	@param wId [In] VIDEO_WID_T
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_hdr_disconnect(VIDEO_WID_T wId)
{
	int ret;
	UINT32 data[2];

	DE_NOTI("wId:%d, pre HDR:%d(0~4:HDR10,DOLBY,VP9,HLG,PRIME)", wId, gsHdrInfo[wId].eHdrMode);
	if (lx_chip_rev() >= LX_CHIP_REV(O18,A0))
	{
		if(wId >= VIDEO_WID_1)
		{
			DE_NOTI("chip:%x,not supported.",lx_chip_rev());
			return OK;
		}
	}
	else
	{
		if(wId >= VIDEO_WID_1)
		{
			DE_NOTI("chip:%x,not supported.",lx_chip_rev());
			return OK;
		}
	}

	switch(gsHdrInfo[wId].eHdrMode)
	{
		case VSC_HDR_DOLBY:
		case VSC_HDR_DOLBY_LL:
			{
				//ret = HAL_DHDR_Disconnect(wId);
			}
			break;
		case VSC_HDR_HDR10:
			{
				ret = de_kwrap_setipchdrmode(wId,LX_HDR_TYPE_OFF,LX_HDR_MODE_FROM_SCL);
			}
			break;
		case VSC_HDR_VP9:
			{
				DE_NOTI("VP9 Not supported yet!!!\n");
				ret = RET_ERROR;
			}
			break;
		case VSC_HDR_HLG:
			{
				ret = de_kwrap_setipchdrmode(wId,LX_HDR_TYPE_OFF,LX_HDR_MODE_FROM_SCL);
			}
			break;
		case VSC_HDR_PRIME:
		default:
			{
				ret = de_kwrap_setipchdrmode(wId,LX_HDR_TYPE_OFF,LX_HDR_MODE_FROM_SCL);
			}
			break;
	}

	gsHdrInfo[wId].eHdrMode = VSC_HDR_MAXN;
	_gsHalAPIStatus[wId].eHdrMode = VSC_HDR_MAXN;
	_geHDROnOff = VSC_HDR_OFF;

	if(ret != OK)
		DE_ERROR("disconnect fail !!!\n");

	if(_gVPSrcInfo[wId].Type == SRC_INPUT_HDMI && (lx_chip_rev() < LX_CHIP_REV(M17,A0)))
	{
		DE_NOTI("kill dovi !!!\n");
		//ret = HAL_GCP_Kill();

		if(ret != OK)
		{
			DE_ERROR("kill dovi fail !!!\n");
		}
	}
	data[0] = wId;
	data[1] = LX_HDR_TYPE_OFF;
	//KADP_PE_SetHdrConnect(data);

	DE_NOTI("Done.");

	return ret;
}

DTV_STATUS_T hal_vsc_hwrap_DM_Fake(UINT32 param)
{
	_gHDRControl = param;
	return 0;
}

/**
 * 	hal_vsc_hwrap_SetLowDelay (new delay delay by source sync)
 *
 *	@param uLowDelay : 0-off, 1-on
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_SetLowDelayBySourceSync(UINT32 uLowDelay)
{
	DTV_STATUS_T ret = OK;

	if(_gVPSrcInfo[0].Type != SRC_INPUT_HDMI)
	{
		DE_WARN("support HDMI only");
		return NOT_SUPPORTED;
	}

	ret = de_kwrap_setlowdelaybysourcesync(uLowDelay);

	DE_NOTI("uLowDelay [%d]", uLowDelay);

	return ret;
}

/**
 * 	hal_vsc_hwrap_SetHighFrameRate (High Frame Rate mode (VDEC 120Hz))
 *
 *	@param param : 0-off, 1-on
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_SetHighFrameRate(UINT32 uHfr)
{
	DTV_STATUS_T ret = OK;

	ret = de_kwrap_sethighframerate(uHfr);

	DE_NOTI("uHighFrameRate [%d]", uHfr);

	return ret;
}

/**
 * 	hal_vsc_hwrap_registeractivevideowindowcallback
 *
 *	@param wId
 *	@param callback
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_registeractivevideowindowcallback(VIDEO_WID_T wId, PFN_VSC_NOTIFY_ACTIVE_VIDEO_WINDOW_T callback)
{
	DTV_STATUS_T ret = OK;
	#ifdef V4L2_VSC_BBD_USE_PRIV
	#else
	ret = vp_kwrap_registeractivevideowindowcallback((UINT32)wId,(PFN_VP_ACTIVE_VIDEO_WINDOW_T)callback);
	#endif
	DE_NOTI("ret = %d, wId[%d] register cb = %p\n", ret, wId, callback);
	return ret;
}

/**
 * 	hal_vsc_hwrap_setinputregion_ForAdaptive
 *
 *	@param wId
 *	@param inRegion
 * 	@return DTV_STATUS_T
 */
DTV_STATUS_T hal_vsc_hwrap_setinputregion_ForAdaptive(VIDEO_WID_T wId, VIDEO_RECT_T inRegion)
{
	DTV_STATUS_T ret = OK;
	LX_DE_RECT_T 	inWin = {0, 0, 0, 0};
	LX_DE_ACT_FORMAT_T param = {0, 0};

	wId = _VSC_Get_Winmap(wId);

	HAL_CHECK_SRC_ID(wId);

	inWin.h = _gDeInWin[wId].h = inRegion.h;
	inWin.w = _gDeInWin[wId].w = inRegion.w;
	inWin.x = _gDeInWin[wId].x = inRegion.x;
	inWin.y = _gDeInWin[wId].y = inRegion.y;

	_gAdaptive_4k_window = param.enable = 2; // set adaptive window for 4k domain >>> if(de_fw_info.version >= 7991), SF = 2 indicates 4k-domain input window.

	ret = vp_kwrap_setactfmtdetect(param);

	ret |= vp_kwrap_setinputwin(wId, inWin);

	DE_NOTI("[HAL_VSC][%d] Set wId[%d] Adaptive uhd-domain in_xywh(%d,%d,%d,%d)***", \
			__L__, wId, inWin.x, inWin.y, inWin.w, inWin.h);

	return ret;
}

DTV_STATUS_T hal_vsc_hwrap_TestVTVOpen(void)
{
	//extern DTV_STATUS_T API_GCP_Init(void);
	//extern DTV_STATUS_T API_GCP_SetOutputBufferResolution(UINT32 w, UINT32 h);

	//API_GCP_Init();
	//API_GCP_SetOutputBufferResolution(1920, 1080);

	return OK;
}

DTV_STATUS_T hal_vsc_hwrap_TestVTVClose(void)
{
	//extern DTV_STATUS_T API_GCP_Finalize(void);

	//API_GCP_Finalize();
	return OK;
}

DTV_STATUS_T hal_vsc_hwrap_setvideolatencypattern(BOOLEAN bOnOff, VSC_PATTERN_TYPE_T bPatternType, VIDEO_RECT_T overlayWindow)
{
	DTV_STATUS_T ret = OK;
	LX_DE_SET_DBG_T dbg_param;

	dbg_param.type = LX_DE_DBG_SET_LATENCY_MEASURE;
	dbg_param.latency_measure.bOnOff = bOnOff;
	switch(bPatternType)
	{
		case VSC_PATTERN_BLACK:
			dbg_param.latency_measure.color = 0;
			break;
		case VSC_PATTERN_WHITE:
		default:
			dbg_param.latency_measure.color = 1;
			break;
	}
	dbg_param.latency_measure.rect.x = overlayWindow.x;
	dbg_param.latency_measure.rect.y = overlayWindow.y;
	dbg_param.latency_measure.rect.w = overlayWindow.w;
	dbg_param.latency_measure.rect.h = overlayWindow.h;

	ret = de_kwrap_setdbgctrl(dbg_param);

	DE_NOTI("bOnOff[%d] bPatternType[%d] rect[%d/%d/%d/%d]", \
		bOnOff, bPatternType, overlayWindow.x, overlayWindow.y, overlayWindow.w, overlayWindow.h);

	return ret;
}
#endif

