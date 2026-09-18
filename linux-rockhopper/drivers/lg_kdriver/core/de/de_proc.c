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
 *  Linux proc interface for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *  author		dongho7.park (dongho7.park@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_de
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/io.h>

#include "de_drv.h"
#include "de_def.h"
#include "de_proc_cmn.h"
#include "proc_util.h"
#include "debug_util.h"
#include <linux/string.h>
#include "de_hal.h"
#include "de_io.h"
#include "resource_mgr.h"
#include "debug_util.h"
#include "os_util.h"
#include "hma_alloc.h"
#include <linux/kallsyms.h>
#include <linux/vmalloc.h>
#include <linux/seq_file.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "de_sync.h"
#include "hal/ipc_hal.h"
#include "vsc/hal_vsc_hwrap.h"
#include "v4l2_vsc_event.h"
#include "vsc_bwm.h"
#include "vsc_fw.h"
#include "vsc_wdog.h"
#include "vsc_print.h"
#include "be_kapi.h"
#include "../be/be_def.h"
#include "../be/frc/frc_hal.h"

#include "vsc_bbd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define FUNCTION_NAME_CMD	//specify if function name is to be given as input or function number
//#define DISABLE_LGSI_CODE_RESTRUCTING
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
// Moved the macro definition to de_proc_cmn.h
#if 0
#define CALL_IO(func) { \
	if(1){ret = func(arg);} /*\
	ret = __push_ioc_buf(cmd, #func, arg);\
	__pop_ioc_buf(0, cmd);*/ }
#endif
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_COMMAND,
	PROC_ID_DBG_FUNC,
	PROC_ID_LOGM,
	PROC_ID_ARGS,
	PROC_ID_HELP,
	PROC_ID_PIP,
	PROC_ID_CALLHISTORY,
	PROC_ID_SETHISTFUNC,
	PROC_ID_ACT_CMN_HIST,
//	PROC_ID_CLR_HIST,
	PROC_ID_CMN_HIST,
	PROC_ID_STATUS,
	PROC_ID_USAGES,
	PROC_ID_DNN_VALUE,
	PROC_ID_DFT_MODE,
	PROC_ID_NET_SYNC,
	PROC_ID_VTV_INPUT_POSITION,
	PROC_ID_FORCE_CMA_ERROR,
	PROC_ID_SET_VENC,
	PROC_ID_SET_DELAY_INTR,
//	PROC_ID_HAL_VSC_HWRAP_DEBUG,
//	PROC_ID_HAL_VT_HWRAP_DEBUG,
//	PROC_ID_HAL_VSC_HWRAP_Initialize,
//	PROC_ID_HAL_VSC_HWRAP_Uninitialize,
//	PROC_ID_HAL_VSC_HWRAP_DEBUG_FUNC,
//	PROC_ID_HAL_VSC_HWRAP_DEBUG_HELP,
	PROC_ID_V4l2_VSC_DEBUG_FUNC,
//	PROC_ID_V4l2_VSC_DEBUG_HELP,
	PROC_ID_V4L2_VSC_EVENT,
	PROC_ID_V4L2_VT,
	PROC_ID_V4L2_GPS,
	PROC_ID_V4L2_PIXELGRAB,
	PROC_ID_VT_BUF_INFO,
	PROC_ID_FPP_INIT,
	PROC_ID_FPP_FINAL,
	PROC_ID_SWITCH_MCU,
	PROC_ID_IPC_HISTORY,
	PROC_ID_FW_DL_HISTORY,
	PROC_ID_BIN_DOWNLOAD,
	PROC_ID_KEEP_SUB_MODE,
	PROC_ID_ENABLE_DBG_MAP,
	PROC_ID_IPC_MASK,
	PROC_ID_PM_TEST,
	PROC_ID_BWM,
	PROC_ID_DISP,
	PROC_ID_SLT_STATUS,
	PROC_ID_BBD,
	PROC_ID_WDOG,
	PROC_ID_ALLOC_DBG_MAP,
	PROC_ID_FW_STATUS,
	PROC_ID_VSC_OPRINT,
	PROC_ID_FR_RATE,
	PROC_ID_V4L2_VT_READ, // 45
	PROC_ID_MAX,
};
typedef enum
{
	V4l2_SET_INPUT,
	V4l2_SET_MUTE,
	V4l2_VSC_SET_WININFO,
	V4l2_SET_SUB_MODE,
	V4l2_SET_ZORDER,
	V4l2_SET_LAT_PATTERN = 5,
	V4l2_SET_VDO_MODE,
	V4l2_SET_PAT,
	V4l2_SET_FRM_DLY,
	V4l2_SET_AD_STRM,
	V4l2_SET_RGB444 = 10,
	V4l2_SET_HDR_TYPE,
	V4l2_SET_REG_ACTWIN,
	V4l2_SET_DBG_ACTWIN,
	V4l2_SET_SWITCH_MCU,
	V4l2_SET_RUNCOMMAND = 15,
	V4l2_SET_POST_EVENT,
	V4l2_SET_FW_DL_TEST,
	V4l2_SET_FOPEN_TEST,
	V4l2_SET_FWIPC_TEST = 20,
	V4l2_SET_VENC,
	V4L2_GET_GPS_DROP,
	V4L2_SET_SUB_OCCUPY,
	V4L2_SET_FREEZE,
	V4L2_SET_ORBIT = 25,
	V4L2_SET_ORBIT_POLICY,
	V4L2_SET_IPMODE,
	V4L2_SET_IPC_TEST = 31,
	V4l2_SET_ZORDER_INFO = 32,
	V4l2_SET_MAX,
}V4l2_PROC_DEBUG_FUNC;
enum
{
	PROC_ID_WIN_STATUS,
	PROC_ID_WIN_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_PE
extern int vpq_proc_set_block_func_dftmode(int mode);
extern int lgsr_proc_set_block_func_dftmode(int mode);
#endif
extern int v4l2_vsc_pm_runtime_help(char* buffer);
extern int v4l2_vsc_pm_runtime_test(char* command);
extern int v4l2_vt_pm_runtime_test(char* command);
extern int v4l2_gps_pm_runtime_test(char* command);

extern int de_proc_slt_push_log(char *str);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int g_de_debug_fd;
extern int gUseHistory;

extern DE_Func_Debugger_ptr_t DE_Func_Debugger_ptr_array[MAX_DBG_FUNC];
extern DE_Assign_Debug_Gbl_ptr_t DE_Assign_Debug_Gbl_ptr_array[MAX_DBG_FUNC];
//VIDEO_WID_T		gwId = VIDEO_WID_0;
//VSC_INPUT_SRC_INFO_T gvscInput = {0, 0};
//static void __HAL_HWRAP_Debug(char *command);
//static void __HAL_HWRAP_Help(void);
static void __V4l2_PROC_Debug(char *command);
//static void __V4l2_PROC_Help(void);
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
// Moved the strcuture definition to de_proc_cmn.h
#if 0
typedef struct DE_FUNCLIST{
	char sName[50];
	int iFunc_no;
}DE_FUNCLIST;
#endif /* #if 0 .. */

static char g_functioname[50];
void *g_args;
static int g_histfunc_cmd = -1;

DE_FUNCLIST gDE_FuncList[]={\
	{"Init",0x01},\
	{"GetFirmWareInfo",0x02},\
	{"GetSysStatus",0x03},\
	{"SetIFConfig",0x04},\
	{"SetDisFmt",0x05},\
	{"SetFrRate",0x06},\
	{"GetOutFrRate",0x07},\
	{"SetDisOut",0x08},\
	{"SetWinPortSrc",0x09},\
	{"SetCviSrcType",0x0A},\
	{"SetCviFIR",0x0B},\
	{"SetCviCsampleMode",0x0C},\
	{"GetScalerInfo",0x0D},\
	{"SetSrcMirror",0x0E},\
	{"GetInputWin",0x0F},\
	{"SetInputWin",0x10},\
	{"GetOutWin",0x11},\
	{"SetOutWin",0x12},\
	{"SetWinBlank",0x13},\
	{"SetBgColor",0x14},\
	{"SetInnerPattern",0x15},\
	{"SetActFmtDetect",0x16},\
	{"SetZList",0x17},\
	{"SetMultiVision",0x18},\
	{"MultiWinEnable",0x19},\
	{"GetSourceStatus",0x1A},\
	{"Set3DInOutCtrl",0x1B},\
	{"SetLowDelay",0x1C},\
	{"GetLowDelay",0x1D},\
	{"SetDvrFmtCtrl",0x1E},\
	{"SetUDMode",0x1F},\
	{"SetVTM",0x20},\
	{"GetVTM",0x21},\
	{"SetWinFreeze",0x22},\
	{"SetHDMIPort",0x23},\
	{"GetCapacity",0x24},\
	{"SetCviTpg",0x25},\
	{"SetSubWindow",0x26},\
	{"SetCve",0x27},\
	{"SetCviFreeze",0x28},\
	{"SetCviVideoFrameBuffer",0x29},\
	{"SetCaptureControl",0x2A},\
	{"SetVcs",0x2B},\
	{"SetOperation",0x2C},\
	{"RegRd",0x2D},\
	{"RegWr",0x2E},\
	{"SetUart4MCU",0x2F},\
	{"SetSubOperation",0x30}
};
struct proc_dir_entry *vsc_proc_seetv;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int _DE_WriteProcDbgFunc( char* command );
int _DE_WriteProcPIP ( char* command );
int _DE_WriteProcArgs ( char* command );
void DE_Log_Level_Ctrl(int dbg_level, int dbg_onoff);
int DE_Make_Arg_From_Short(int LSW,int MSW);
int DE_Make_Arg_From_Char(int LSB,int L2B,int M2B, int MSB);
int DE_Make_CMD(int orgcmd);
int DE_Assign_Debug_Gbl_Ptr(int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Func_Debugger (int funcNo,int iDefArgs);
int de_proc_enable_dbg_map(UINT32 flag);
void de_proc_alloc_dbg_map(char *command);
void DE_PROC_Init (void);
void DE_PROC_Cleanup (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static void _DE_PrintStatus (struct seq_file *m, void* data);
static void _DE_PrintUsages (struct seq_file *m, void* data);
static int _DE_PrintSltStatus (struct seq_file *m);
static void _DE_PrintFwStatus (struct seq_file *m);
static void _DE_PrintCgStatus (struct seq_file *m);

OS_PROC_SEQRD_DEFINE_EX(_g_de_status_proc_fops, _DE_PrintStatus, NULL)
OS_PROC_SEQRD_DEFINE_EX(_g_de_usages_proc_fops, _DE_PrintUsages, NULL)
OS_PROC_SEQRD_DEFINE(_g_de_slt_status_fops, _DE_PrintSltStatus)
OS_PROC_SEQRD_DEFINE(_g_de_fw_status_fops, _DE_PrintFwStatus)
OS_PROC_SEQRD_DEFINE(_g_de_cg_status_fops, _DE_PrintCgStatus)

static OS_PROC_DESC_TABLE_T	_g_de_device_proc_table[] =
{
	{ "author",				PROC_ID_AUTHOR,			OS_PROC_FLAG_READ },
	{ "help",				PROC_ID_HELP, 			OS_PROC_FLAG_READ },
	{ "history",			PROC_ID_CALLHISTORY,	OS_PROC_FLAG_READ },
	{ "cmn_history",		PROC_ID_CMN_HIST, 		OS_PROC_FLAG_READ },
	{ "command",			PROC_ID_COMMAND , 		OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "debug_function",		PROC_ID_DBG_FUNC,		OS_PROC_FLAG_WRITE },
	{ "log_level",			PROC_ID_LOGM,			OS_PROC_FLAG_WRITE },
	{ "function_args",		PROC_ID_ARGS,			OS_PROC_FLAG_WRITE },
	{ "pip",				PROC_ID_PIP,			OS_PROC_FLAG_WRITE },
	{ "set_hist_func",		PROC_ID_SETHISTFUNC,	OS_PROC_FLAG_WRITE },
//	{ "clear_history",		PROC_ID_CLR_HIST,		OS_PROC_FLAG_WRITE },
	{ "activate_cmn_history",PROC_ID_ACT_CMN_HIST,	OS_PROC_FLAG_WRITE },
	{ "status",				PROC_ID_STATUS,			OS_PROC_FLAG_SEQRD, (void*)&_g_de_status_proc_fops },
	{ "usages",				PROC_ID_USAGES,			OS_PROC_FLAG_SEQRD, (void*)&_g_de_usages_proc_fops },
	{ "dnn_value",			PROC_ID_DNN_VALUE,		OS_PROC_FLAG_READ },
	{ "dft_mode",			PROC_ID_DFT_MODE,		OS_PROC_FLAG_WRITE },
	{ "netsync",            PROC_ID_NET_SYNC,       OS_PROC_FLAG_WRITE },
	{ "vtv_position",       PROC_ID_VTV_INPUT_POSITION,       OS_PROC_FLAG_WRITE },
	{ "force_cma_error",       PROC_ID_FORCE_CMA_ERROR,       OS_PROC_FLAG_WRITE },
	{ "set_venc",	PROC_ID_SET_VENC,       OS_PROC_FLAG_WRITE },
	{ "set_delay_intr",	PROC_ID_SET_DELAY_INTR,		OS_PROC_FLAG_WRITE },
//	{ "hal_vsc_debug",		PROC_ID_HAL_VSC_HWRAP_DEBUG,OS_PROC_FLAG_READ },
//	{ "hal_vt_debug",		PROC_ID_HAL_VT_HWRAP_DEBUG,OS_PROC_FLAG_READ },
//	{ "hal_vsc_init",		PROC_ID_HAL_VSC_HWRAP_Initialize,OS_PROC_FLAG_READ },
//	{ "hal_vsc_uninit",		PROC_ID_HAL_VSC_HWRAP_Uninitialize,OS_PROC_FLAG_READ },
//	{ "hal_vsc_debug_func", PROC_ID_HAL_VSC_HWRAP_DEBUG_FUNC,OS_PROC_FLAG_WRITE},
//	{ "hal_vsc_debug_help", PROC_ID_HAL_VSC_HWRAP_DEBUG_HELP,OS_PROC_FLAG_READ},
	{ "v4l2_vsc_debug_func",PROC_ID_V4l2_VSC_DEBUG_FUNC,OS_PROC_FLAG_WRITE},
//	{ "v4l2_vsc_debug_help",PROC_ID_V4l2_VSC_DEBUG_HELP,OS_PROC_FLAG_READ},
	{ "v4l2_event",PROC_ID_V4L2_VSC_EVENT,OS_PROC_FLAG_WRITE},
	{ "v4l2_capture",PROC_ID_V4L2_VT,OS_PROC_FLAG_WRITE},
	{ "v4l2_capture_read",PROC_ID_V4L2_VT_READ,OS_PROC_FLAG_READ},
	{ "v4l2_pixelgrab",PROC_ID_V4L2_PIXELGRAB,OS_PROC_FLAG_WRITE},
	{ "v4l2_gps_get_drop",PROC_ID_V4L2_GPS,OS_PROC_FLAG_READ},
	{ "v4l2_gps_debug",PROC_ID_V4L2_GPS,OS_PROC_FLAG_READ},
	{ "vt_get_addr",PROC_ID_VT_BUF_INFO,OS_PROC_FLAG_READ},
	{ "fpp_initialize",PROC_ID_FPP_INIT,OS_PROC_FLAG_WRITE},
	{ "fpp_finalize",PROC_ID_FPP_FINAL,OS_PROC_FLAG_WRITE},
	{ "switch_mcu",PROC_ID_SWITCH_MCU,OS_PROC_FLAG_WRITE},
	{ "ipc_history",PROC_ID_IPC_HISTORY,OS_PROC_FLAG_WRITE},
	{ "fw_dl_history",PROC_ID_FW_DL_HISTORY,OS_PROC_FLAG_WRITE},
	{ "bin_download",PROC_ID_BIN_DOWNLOAD,OS_PROC_FLAG_WRITE},
	{ "keep_submode",PROC_ID_KEEP_SUB_MODE,OS_PROC_FLAG_WRITE},
	{ "enable_dbg_map",PROC_ID_ENABLE_DBG_MAP,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "ipc_mask",PROC_ID_IPC_MASK,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "pm_test",PROC_ID_PM_TEST,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "bwm",PROC_ID_BWM,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "disp",PROC_ID_DISP,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "slt_status",PROC_ID_SLT_STATUS,OS_PROC_FLAG_SEQRD,(void*)&_g_de_slt_status_fops},
	{ "bbd",PROC_ID_BBD,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "wdog",PROC_ID_WDOG,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "alloc_dbg_map",PROC_ID_ALLOC_DBG_MAP,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "fw-status",PROC_ID_FW_STATUS,OS_PROC_FLAG_SEQRD,(void*)&_g_de_fw_status_fops},
	{ "vsc_oprint",PROC_ID_VSC_OPRINT,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "fr_rate",PROC_ID_FR_RATE,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "cg-status",PROC_ID_FW_STATUS,OS_PROC_FLAG_SEQRD,(void*)&_g_de_cg_status_fops},

	{ NULL, 				PROC_ID_MAX		, 0 }
};

static void _DE_WIN_PrintStatus	(struct seq_file *m, void* data);

OS_PROC_SEQRD_DEFINE_EX(_g_de_win0_status_proc_fops, _DE_WIN_PrintStatus,	LX_DE_WIN_0)
OS_PROC_SEQRD_DEFINE_EX(_g_de_win1_status_proc_fops, _DE_WIN_PrintStatus,	LX_DE_WIN_1)
OS_PROC_SEQRD_DEFINE_EX(_g_de_win2_status_proc_fops, _DE_WIN_PrintStatus,	LX_DE_WIN_2)
OS_PROC_SEQRD_DEFINE_EX(_g_de_win3_status_proc_fops, _DE_WIN_PrintStatus,	LX_DE_WIN_3)

static const OS_PROC_DESC_TABLE_T _g_de_win0_proc_table[] = {
    { "status", 	PROC_ID_WIN_STATUS,	OS_PROC_FLAG_SEQRD, (void*)&_g_de_win0_status_proc_fops },
	{ NULL,			PROC_ID_WIN_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_de_win1_proc_table[] = {
    { "status", 	PROC_ID_WIN_STATUS,	OS_PROC_FLAG_SEQRD, (void*)&_g_de_win1_status_proc_fops },
	{ NULL,			PROC_ID_WIN_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_de_win2_proc_table[] = {
    { "status", 	PROC_ID_WIN_STATUS,	OS_PROC_FLAG_SEQRD, (void*)&_g_de_win2_status_proc_fops },
	{ NULL,			PROC_ID_WIN_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_de_win3_proc_table[] = {
    { "status", 	PROC_ID_WIN_STATUS,	OS_PROC_FLAG_SEQRD, (void*)&_g_de_win3_status_proc_fops },
	{ NULL,			PROC_ID_WIN_MAX, 0 } };

/*========================================================================================
	Implementation Group
========================================================================================*/
/*
Log Level Control Function
*/
void DE_Log_Level_Ctrl(int dbg_level, int dbg_onoff)
{
	if (dbg_level>31 || dbg_level<0 || dbg_onoff<0)
	{
		printk("invalid(%d,%d)\n",dbg_level,dbg_onoff);
		return;
	}

	if (dbg_onoff != 0)
	{
		OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, dbg_level, DBG_COLOR_NONE );
	}
	else
	{
		OS_DEBUG_DisableModuleByIndex( g_de_debug_fd, dbg_level);
	}
	return;
}

/*
Function to make integer argument from two short arguments
*/
int DE_Make_Arg_From_Short(int LSW,int MSW)
{
	int retArg = 0;

	retArg = (0x0000ffff&LSW)| ((MSW<<16)&0xffff0000);

	return retArg;
}

int DE_Make_Arg_From_Char(int LSB,int L2B,int M2B, int MSB)
{
	int retArg = 0;

	retArg = (0x000000ff&LSB) | ((L2B<<8)&0x0000ff00) | ((M2B<<16)&0x00ff0000) | ((MSB<<24)&0xff000000);
	return retArg;
}

static const int de_cmd_lut[256] =
{
	DE_IOW_DE_INIT, DE_IOR_GET_FIRMWARE_INFO, DE_IOW_FW_DOWNLOAD, DE_IOW_SET_IF_CONFIG,
	DE_IOR_GET_CAPACITY, 0, 0, 0, 0, 0, DE_IOW_SET_WIN_PORT_SRC, DE_IOW_SET_CVI_SRC_TYPE,
	DE_IOW_SET_CVI_FIR, DE_IOW_SET_CVI_CSAMPLE_MODE, DE_IOR_GET_MVI_COLORIMETRY,
	DE_IOW_SET_CVI_HDMIPORT, 0, 0, 0, 0, DE_IOW_SET_DIS_FMT, DE_IOW_SET_FR_RATE,
	DE_IOR_GET_OUT_FR_RATE, DE_IOW_SET_DIS_OUT, DE_IOW_SET_SUB_WIN, 0, 0, 0, 0, 0, DE_IOR_GET_INPUT_WIN,
	DE_IOR_GET_OUT_WIN, DE_IOW_SET_INPUT_WIN, DE_IOW_SET_OUT_WIN, DE_IOW_SET_ZLIST,
	DE_IOW_SET_MULTI_VISION, DE_IOW_SET_WIN_BLANK,  DE_IOW_SET_BG_COLOR, DE_IOW_SET_INNER_PATTERN, 0,
	DE_IOW_SET_OUTPUT_MODE, DE_IOW_SET_3D_INOUT_CTRL, DE_IOW_SET_UD_MODE, DE_IOW_MULTI_WIN_ENABLE,
	DE_IOR_GET_LOW_DELAY, DE_IOW_SET_LOW_DELAY, DE_IOR_GET_SCALER_INFO, DE_IOW_SET_CVE,
	DE_IOW_SET_DVR_FMT_CTRL, DE_IOW_SET_VTM, DE_IOR_GET_VTM, DE_IOW_SET_CAPTURE, DE_IOW_SET_SRC_MIRROR,
	DE_IOW_SET_ACT_FMT_DETECT, DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER, DE_IOWR_SET_VTM_BLOCK_STATE,
	0, 0, 0, 0, DE_IOW_SET_WIN_FREEZE, DE_IOW_SET_SUB_SC_FREEZE, DE_IOW_SET_CVI_FREEZE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	DE_IOR_REG_RD, DE_IOW_REG_WR, DE_IOR_GET_DBG, DE_IOW_SET_DBG, DE_IOW_SET_UART_FOR_MCU, DE_IOW_SET_VCS,
	DE_IOR_GET_SYS_STATUS, DE_IOR_GET_SRC_STATUS, DE_IOW_SET_CVI_TPG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	DE_IOW_SET_EVAL_DBG, DE_IOW_SET_SCART_RGB_BYPASS_MODE, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	DE_IOW_SET_OPERATION, DE_IOW_SET_SUB_OPERATION, DE_IOW_SET_DEINTERLACE
};

/*
Function to make ioctl command for history
*/

int DE_Make_CMD(int orgcmd)
{
	int retcmd;

	retcmd = de_cmd_lut[orgcmd];

	return retcmd ;
}

/*
Function to assign argument pointer according to the function that needs to be debugged.
iFuncNo is the function number
iArgOffset is the integer offset of the argument value passed.
iArgvalue is the value of the argument at the specified integer offset
*/
int DE_Assign_Debug_Gbl_Ptr(int iFuncNo,int iArgOffset,int iArgvalue)
{
	int ret = RET_OK;

	if (iFuncNo < 0x1 || iFuncNo > 0x30)
	{
		printk("invalid function number. please use a valid function number\n");
		ret = RET_ERROR;
	}
	else
	{
		ret = DE_Assign_Debug_Gbl_ptr_array[iFuncNo-1](iFuncNo, iArgOffset, iArgvalue);
	}
	return ret;
}

int DE_Func_Debugger (int funcNo,int iDefArgs)
{
	int ret = RET_OK;

	if (funcNo < 0x1 || funcNo > 0x30)
	{
		printk("invalid function number. please use a valid function number\n");
		ret = RET_ERROR;
	}
	else
	{
#ifdef ENABLE_PROC_FUNCTION
		ret = DE_Func_Debugger_ptr_array[funcNo-1](iDefArgs);
#endif
	}

	return ret;
}

/*
 * read_proc implementation of de device
 *
*/
static int	_DE_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret = RET_OK;
	int listsize,i;
	/* TODO: add your proc_write implementation */
	listsize = sizeof(gDE_FuncList)/sizeof(gDE_FuncList[0]);
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			int len = 0;
			len += sprintf( buffer+len, "see guide : http://collab.lge.com/main/x/HOz_Tw\n");
			len += sprintf( buffer+len, "- usage:\n");
			len += sprintf( buffer+len, "echo [mcu command] end > /proc/lg/de/command\n");
			len += sprintf( buffer+len, "- example:\n");
			len += sprintf( buffer+len, "print fw log on  : echo ipc log 1 end > /proc/lg/de/command\n");
			len += sprintf( buffer+len, "print fw log off : echo ipc log 0 end > /proc/lg/de/command\n");
			len += sprintf( buffer+len, "curr 0           : echo curr 0 end > /proc/lg/de/command\n");
			len += sprintf( buffer+len, "pat ipp m0       : echo pat ipp m0 end > /proc/lg/de/command\n");
			len += sprintf( buffer+len, "exit(do not use) : echo quit end > /proc/lg/de/command\n");
			ret = len;
		}
		break;
		case PROC_ID_IPC_MASK:
		{
			int len = 0;
			len += sprintf( buffer+len, "- curr  : 0x%08x\n",ipc_hal_get_mask());
			len += sprintf( buffer+len, "- usage : echo [mask] > /proc/lg/de/ipc_mask\n");
			len += sprintf( buffer+len, "- example:\n");
			len += sprintf( buffer+len, "mask all  : echo 0xffffffff > /proc/lg/de/ipc_mask\n");
			len += sprintf( buffer+len, "mask mute : echo 0x0000001f > /proc/lg/de/ipc_mask\n");
			ret = len;
		}break;
		case PROC_ID_ENABLE_DBG_MAP :
		{
			int len = 0;
			len += sprintf( buffer+len, "- usage:\n");
			len += sprintf( buffer+len, "echo [on,off] > /proc/lg/de/enable_dbg_map\n");
			len += sprintf( buffer+len, "- example:\n");
			len += sprintf( buffer+len, "echo 1 > /proc/lg/de/enable_dbg_map\n");
			len += sprintf( buffer+len, "echo 0 > /proc/lg/de/enable_dbg_map\n");
			ret = len;
		}break;
		case PROC_ID_ALLOC_DBG_MAP :
		{
			int len = 0;
			len += sprintf( buffer+len, "- usage:\n");
			len += sprintf( buffer+len, "echo [alloc,free] [debug0,debug1] [size(MB)] > /proc/lg/de/alloc_dbg_map\n");
			len += sprintf( buffer+len, "- example:\n");
			len += sprintf( buffer+len, "echo alloc debug1 10 > /proc/lg/de/alloc_dbg_map\n");
			len += sprintf( buffer+len, "echo free debug1 0 > /proc/lg/de/alloc_dbg_map\n");
			ret = len;
		}break;
		case PROC_ID_VSC_OPRINT :
		{
			int len = 0;
			len += sprintf( buffer+len, "debug osd print\n");
			len += sprintf( buffer+len, "- usage:\n");
			len += sprintf( buffer+len, "echo [string] > /proc/lg/de/vsc_oprint\n");
			ret = len;
		}break;
		case PROC_ID_FR_RATE :
		{
			int len = 0;
			len += sprintf( buffer+len, "set fr rate\n");
			len += sprintf( buffer+len, "- usage:\n");
			len += sprintf( buffer+len, "echo [freerun:0,1] [fr_rate:50,60] > /proc/lg/de/fr_rate\n");
			ret = len;
		}break;
		case PROC_ID_PM_TEST :
		{
			ret = v4l2_vsc_pm_runtime_help(buffer);
		}break;
		case PROC_ID_BWM :
		{
			ret = vsc_bwm_help(buffer);
		}break;
		case PROC_ID_DISP :
		{
			extern int de_proc_disp_help(char* buffer);
			ret = de_proc_disp_help(buffer);
		}break;
		case PROC_ID_BBD :
		{
			ret = vsc_bbd_status(buffer);
		}break;
		case PROC_ID_WDOG :
		{
			ret = vsc_wdog_status(buffer);
		}break;
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer, 48, "%s\n", "dongho7.park (dongho7.park@lge.com)" );
		}
		break;
		case PROC_ID_HELP:
		{
			printk("---------------------------------------------------------------------------------------\n\
Usage Steps:\n\
Set Log Level:\n\
echo [log level] > /proc/lg/de/log_level\n\
example:\n\
echo 5 > /proc/lg/de/log_level\n\n\
---------------------------------------------------------------------------------------\n");
printk("Call History Usage:\n\
Activate DE,PE call history - \n\
echo 1 > /proc/lg/de/activate_cmn_history\n\
Get all module history since activation - \n\
cat /proc/lg/de/cmn_history\n\
Get history from bootup time for only DE functions\n\
cat /proc/lg/de/history\n\n\
To get info for only a specific function\n\
echo [ioctl_command_number] > /proc/lg/de/set_hist_func\n\
cat /proc/lg/de/history\n\
example: for DE_IO_SetOutWin function call history\n\
echo 33 > /proc/lg/de/set_hist_func\n\
cat /proc/lg/de/history\n\n\
---------------------------------------------------------------------------------------\n");
printk("Pip Checker usage:\n\
echo 1 > /proc/lg/de/pip       // enable pip window with tuner src at bottom right(default case)\n\
echo 0 > /proc/lg/de/pip       // turn off pip\n\
echo 1 1 > /proc/lg/de/pip     // enable pip window with tuner src at bottom left\n\
echo 1 2 > /proc/lg/de/pip     // enable pip window with tuner src at top left\n\
echo 1 3 > /proc/lg/de/pip     // enable pip window with tuner src at top right\n\
---------------------------------------------------------------------------------------\n");
printk("Debugger Usage:\n\
echo [function number] [argument integer offset] [argument value at offset] > /proc/lg/de/function_args\n\
echo [function number] [use default arg flag] > /proc/lg/de/debug_function\n\n\
example:\n\
echo 4 0 2 > /proc/lg/de/function_args \n\
sets the argument at integer offset 0 to 2 for function number 4\n\
echo 4 1 > /proc/lg/de/debug_function\n\
will call the function 4 with the set arguments\n\
echo 4 0 > /proc/lg/de/debug_function\n\
will call the function 4 with default arguments\n\
you can also pass two short values to the value at the offset as follows:\n\
echo 5 1 60 4096  > /proc/lg/de/function_args        //pass to arg integer offset 1 of function no 5 two shorts 60 and 4096\n\
to pass three or four char values at the offset, you can do as follows: \n");
printk("echo e 0 1 2 3 > /proc/lg/de/function_args           //pass to arg 0 of function number e three chars 1,2 and 3\n\
---------------------------------------------------------------------------------------\n\n\
Function Number\t\t Function Name\n");
		for(i=0;i<listsize;i++)
			{
				printk("0x%x\t\tDE_IO_%s\n",gDE_FuncList[i].iFunc_no,gDE_FuncList[i].sName);
			}
			printk("---------------------------------------------------------------------------------------\n");
		}break;
		case PROC_ID_CALLHISTORY:
		{
			/* temporary */
			#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
			int command;
			int (*pop_fn_ptr)(BOOLEAN dump_all, unsigned int c);
			de_sync_display();
			ipc_hal_list();
			pop_fn_ptr=NULL;
			pop_fn_ptr = (void *)kallsyms_lookup_name("__pop_ioc_buf");
			if(pop_fn_ptr == NULL)
				break;
			OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, LX_LOGM_LEVEL_TRACE, DBG_COLOR_NONE );
			if(g_histfunc_cmd<0)
				{
					(*pop_fn_ptr)(TRUE,1);
				}
			else
				{
					command = DE_Make_CMD(g_histfunc_cmd);

					(*pop_fn_ptr)(FALSE,command);
				}
			OS_DEBUG_DisableModuleByIndex( g_de_debug_fd, LX_LOGM_LEVEL_TRACE);
			#else
			de_sync_display();
			ipc_hal_list();
			#endif
		}break;
		case PROC_ID_CMN_HIST:
		{
			/* temporary */
			#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
			int (*pop_fn_ptr)(int show_num);
			pop_fn_ptr=NULL;
			pop_fn_ptr = (void *)kallsyms_lookup_name("Pop_Ioc_Hist");
			if(pop_fn_ptr == NULL)
				break;
			(*pop_fn_ptr)(1000);
			#else
			printk("not support\n");
			#endif
		}break;
		case PROC_ID_DNN_VALUE:
		{
			UINT32 a, b, c, d, e, f;
			DE_IO_GetPQE_DNNResult(&a, &b, &c, &d, &e, &f);
			ret = sprintf( buffer, "%d %d %d %d %d %d\n", a, b, c, d, e, f);
		}break;
		//case PROC_ID_HAL_VSC_HWRAP_DEBUG:
		//{
			//extern void	HAL_VSC_VIDEO_DEBUG_Test (void);
			//HAL_VSC_VIDEO_DEBUG_Test();
		//}break;
		//case PROC_ID_HAL_VT_HWRAP_DEBUG:
		//{
		//	extern void HAL_VT_DEBUG_Test(void);
			//HAL_VT_DEBUG_Test();
		//}break;
		//case PROC_ID_HAL_VSC_HWRAP_Initialize:
		//{
			//hal_vsc_hwrap_initialize();
		//	printk("***********************hal_vsc_hwrap_initialize calle***************\n");
		//}break;
		//case PROC_ID_HAL_VSC_HWRAP_Uninitialize:
		//{
			//hal_vsc_hwrap_Uninitialize();
		//}break;
		//case PROC_ID_HAL_VSC_HWRAP_DEBUG_HELP:
		//{
			//__HAL_HWRAP_Help();
		//}break;
		//case PROC_ID_V4l2_VSC_DEBUG_HELP:
		//{
		//	__V4l2_PROC_Help();
		//}break;
		case PROC_ID_V4L2_GPS:
		{
			unsigned int /*inst,*/ count[8];
			int i;
			extern int proc_gps_get_frame_drop(unsigned int id, unsigned int *count);
			for(i=0;i<8;i++)
			{
				proc_gps_get_frame_drop(i, &count[i]);
			}
			ret = sprintf( buffer, "%d %d %d %d %d %d %d %d\n", \
				count[0], count[1], count[2], count[3], \
				count[4], count[5], count[6], count[7]);
		}break;
		case PROC_ID_VT_BUF_INFO:
		{
			extern int DE_Get_BufferInfo(UINT32 *addr0, UINT32 *size0, UINT32 *addr1, UINT32 *size1);
			UINT32 addr0, size0, addr1, size1;
			DE_Get_BufferInfo(&addr0, &size0, &addr1, &size1);
			ret = sprintf( buffer, "%x %x %x %x\n", \
				addr0, size0, addr1, size1);
		}break;
		case PROC_ID_V4L2_VT_READ:
		{
			int c=3, w=0, h=0;
			unsigned int v, p;
			int proc_capture(int cmd, int w, int h, unsigned int *v, unsigned int *p);
			proc_capture(c, w, h, &v, &p);
			ret = sprintf(buffer, "%x %x \n" ,v, p);
			//printk("hist cmd = %d param = %d", v, p);
		} break;
		case PROC_ID_FPP_INIT :
		{
			unsigned long arg;
			UINT32 stParams = TRUE;
			arg = (unsigned long)&stParams;
			DE_IO_GetFPPInfo(arg, 1);

			ret = sprintf( buffer, "%x \n", \
				stParams);
		}break;

		case PROC_ID_SWITCH_MCU :
		{
			printk("20190604\n");
			printk("Usage : echo [id] > /proc/lg/de/switch_mcu\n");
			printk("echo 0 > /proc/lg/de/switch_mcu\n");
		}break;

		case PROC_ID_LOGM:
		{
			printk("Usage : echo [level] [onoff] > /proc/lg/de/log_level\n");
			printk("level : 0:ERROR, 1:WARN, 2:NOTI, 3:INFO, 4:DEBUG, 5:TRACE, 6:VTV, 7:SYNC\n");
			printk("echo 2 0 > /proc/lg/de/log_level\n");
			printk("echo 2 1 > /proc/lg/de/log_level\n");
			printk("echo 5 0 > /proc/lg/de/log_level\n");
			printk("echo 5 1 > /proc/lg/de/log_level\n");
			printk("echo 7 0 > /proc/lg/de/log_level\n");
			printk("echo 7 1 > /proc/lg/de/log_level\n");
		}break;

		case PROC_ID_IPC_HISTORY :
		{
			printk("*************** normal log ***************\n");
			ipc_hal_trace(3);
			printk("*************** backup log ***************\n");
			ipc_hal_trace(5);
		}break;

		case PROC_ID_FW_DL_HISTORY :
		{
			printk("*************** core log ***************\n");
			vsc_fw_view_log();
			printk("\n");
			printk("*************** chip log ***************\n");
			DE_HAL_ViewInfo(0);
			printk("****************************************\n");
		}break;

		case PROC_ID_BIN_DOWNLOAD :
		{
			extern int de_proc_bin_read_function(int id);
			de_proc_bin_read_function(0);
		}break;

		default:
		{
			ret = snprintf( buffer, 48, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

int de_proc_enable_dbg_map(UINT32 flag)
{
	int ret = 0;

	if (flag > 0)
	{
		ret = DE_HAL_GetMemFromCma("de-dbgbuf", 1, NULL, TRUE);
		#ifdef INCLUDE_KDRV_BE
		{
			LX_BE_FRC_CMD_T params = {"DEDBG 1"};
			OS_MsecSleep(40);
			BE_FRC_HAL_RunCommand(&params);
			DE_NOTI("Command(%s)\n",params.str);
		}
		#endif
	}
	else
	{
		#ifdef INCLUDE_KDRV_BE
		{
			LX_BE_FRC_CMD_T params = {"DEDBG 0"};
			BE_FRC_HAL_RunCommand(&params);
			DE_NOTI("Command(%s)\n",params.str);
			OS_MsecSleep(40);
		}
		#endif
		ret = DE_HAL_GetMemFromCma("de-dbgbuf", 1, NULL, FALSE);
	}

	return ret;
}

void de_proc_alloc_dbg_map(char *command)
{
	UINT32 size;
	char cmd[16], pool[16];

	struct pool_cfg {
		char *name;
		phys_addr_t paddr;
	};
	struct pool_cfg *p;
	static struct pool_cfg entry[4] = {
		[0] = {.name = "debug0",.paddr=0},
		[1] = {.name = "debug1",.paddr=0},
		[2] = {.name = "debug2",.paddr=0},
		[3] = {.name = NULL},
	};

	sscanf(command," %s %s %d",cmd,pool,&size);
	DE_NOTI("command %s %s %d\n",cmd,pool,size);

	p = entry;
	while (p->name)
	{
		if (!strncmp(pool,p->name,strlen(p->name))) {
			break;
		}
		p++;
	}

	if (!p->name) {
		DE_NOTI("invalid pool(%s)\n",pool);
		return;
	}

	DE_NOTI("=> %s %s %d(MB)\n",cmd,p->name,size);

	if (!strncmp(cmd,"alloc",strlen("alloc")) && p->paddr == 0 && size > 0) {
		p->paddr = hma_alloc(p->name,size<<20, (1<<14));//align:16k
		if (p->paddr == 0)
		{
			DE_NOTI("alloc fail %s\n",p->name);
			return;
		}
		DE_NOTI("alloc %s %d(MB)\n",p->name,size);
	}
	else if (!strncmp(cmd,"free",strlen("free")) && p->paddr != 0) {
		hma_free(p->name,p->paddr);
		p->paddr = 0;
		DE_NOTI("free %s\n",p->name);
	}
	else {
		DE_NOTI("invalid cmd %s\n",cmd);
		return;
	}
}

/*
 * write_proc implementation of de device
 *
*/
static int _DE_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			#ifdef INCLUDE_KDRV_BE
			UINT32 run_command = 1;
			LX_BE_FRC_CMD_T params;
			char s0[20],s1[20],s2[20],s3[20],s4[20],s5[20],s6[20];
			memset(params.str,0,sizeof(LX_BE_FRC_CMD_T));
			sscanf(command,"%s %s %s %s %s %s %s\n",s0,s1,s2,s3,s4,s5,s6);

			if (!strcmp(s1, "end"))			sprintf(params.str,"%s",s0);
			else if (!strcmp(s2, "end"))	sprintf(params.str,"%s %s",s0,s1);
			else if (!strcmp(s3, "end"))	sprintf(params.str,"%s %s %s",s0,s1,s2);
			else if (!strcmp(s4, "end"))	sprintf(params.str,"%s %s %s %s",s0,s1,s2,s3);
			else if (!strcmp(s5, "end"))	sprintf(params.str,"%s %s %s %s %s",s0,s1,s2,s3,s4);
			else if (!strcmp(s6, "end"))	sprintf(params.str,"%s %s %s %s %s %s",s0,s1,s2,s3,s4,s5);
			else							run_command = 0;

			if (run_command) {
				printk("RunCommand [ %s ]\n",params.str);
				if (!strcmp(s0, "slt") || !strcmp(s0, "SLT")) {
					de_proc_slt_push_log(params.str);
				}
				BE_FRC_HAL_RunCommand(&params);
			}
			else if (!strncmp(s0, "mcususpend", 10)) {
				printk("DE_IO_SetMcuSuspend(1)\n");
				DE_IO_SetMcuSuspend(1);
			}
			else if (!strncmp(s0, "mcuresume", 9)) {
				printk("DE_IO_SetMcuSuspend(0)\n");
				DE_IO_SetMcuSuspend(0);
			}
			else if (!strncmp(s0, "ipcenable", 10)) {
				printk("ipc_hal_ready_to_use(1)\n");
				ipc_hal_ready_to_use(1);
			}
			else if (!strncmp(s0, "ipcdisable", 9)) {
				printk("ipc_hal_ready_to_use(0)\n");
				ipc_hal_ready_to_use(0);
			}
			else {
				printk("do nothing\n");
			}
			#endif
		}break;

		case PROC_ID_PM_TEST:
		{
			if (!strncasecmp(command, "vt_", strlen("vt_"))) {
				v4l2_vt_pm_runtime_test(command);
			}
			else if (!strncasecmp(command, "gps_", strlen("gps_"))) {
				v4l2_gps_pm_runtime_test(command);
			}
			else {
				v4l2_vsc_pm_runtime_test(command);
			}
		}break;

		case PROC_ID_BWM:
		{
			vsc_bwm_set_dbg(command);
		}break;

		case PROC_ID_DISP:
		{
			extern int de_proc_disp_command(char* command);
			de_proc_disp_command(command);
		}break;

		case PROC_ID_BBD:
		{
			vsc_bbd_command(command);
		}break;

		case PROC_ID_WDOG:
		{
			vsc_wdog_command(command);
		}break;

		case PROC_ID_IPC_MASK:
		{
			UINT32 mask;
			sscanf( command, " %x", &mask);
			printk("ipc_hal_set_mask(0x%08x)\n",mask);
			ipc_hal_set_mask(mask);
		}break;

		case PROC_ID_DBG_FUNC:
		{
			int ret = RET_OK;

			ret = _DE_WriteProcDbgFunc(command);
		}break;

		case PROC_ID_ARGS:
		{
			int ret = RET_OK;

			ret = _DE_WriteProcArgs(command);
		}break;

		case PROC_ID_LOGM:
		{
			int ilog_level, ilog_onoff;
			sscanf( command, " %d %d", &ilog_level, &ilog_onoff);
			DE_Log_Level_Ctrl(ilog_level,ilog_onoff);
		}break;
		case PROC_ID_PIP:
		{
			int ret = RET_OK;

			ret = _DE_WriteProcPIP( command );
		}break;
		case PROC_ID_SETHISTFUNC:
		{
			sscanf( command, " %d", &g_histfunc_cmd);
		}break;
	/*	case PROC_ID_CLR_HIST:
		{
			int (*clr_fn_ptr)(BOOLEAN sel);
			int clr = 0;
			sscanf(command, "%d",&clr);
			clr_fn_ptr = NULL;
			clr_fn_ptr = (void *)kallsyms_lookup_name("_init_ioc_buf");
			if(clr_fn_ptr == NULL)
				break;
			if(clr)
				{
					(*clr_fn_ptr)(FALSE);
				}
		}break;*/
		//case PROC_ID_HAL_VSC_HWRAP_DEBUG_FUNC:
		//{
			//HAL_VSC_HWRAP_DEBUG_FUNCNUM func_num;
			//sscanf(" %d ",&func_num)
			//__HAL_HWRAP_Debug(command);
		//}
		case PROC_ID_V4l2_VSC_DEBUG_FUNC:
		{
			__V4l2_PROC_Debug(command);
		}break;
		case PROC_ID_ACT_CMN_HIST:
		{
			sscanf( command, " %d", &gUseHistory);
		}break;
		
		case PROC_ID_DFT_MODE:
		{
			int ret = RET_OK;
			UINT32 mode;
			sscanf( command, " %d", &mode);
			ret = DE_IO_SetDftMode(mode);
			#ifdef INCLUDE_KDRV_PE
			ret = vpq_proc_set_block_func_dftmode(mode);
			ret = lgsr_proc_set_block_func_dftmode(mode);
			#endif
		}break;

		case PROC_ID_NET_SYNC:
		{
			int ret = RET_OK;
			LX_DE_NETWORK_SYNC_T param;
			int onoff, dbg_control;
			int x, y, w, h;
			ret = sscanf( command, "%d %d %d %d %d %d", &onoff, &dbg_control, &x, &y, &w, &h);
			param.onfoff = (UINT32)onoff;
			param.dbg_control = (UINT32)dbg_control;
			param.dbg_rect.x = (UINT16)x;
			param.dbg_rect.y = (UINT16)y;
			param.dbg_rect.w = (UINT16)w;
			param.dbg_rect.h = (UINT16)h;
			DE_NOTI("%d : %d %d %d %d %d %d", ret, onoff, dbg_control, x,y,w,h);
			ret = DE_IO_SetNetworkSync((unsigned long)&param);
		}break;

		case PROC_ID_VTV_INPUT_POSITION:
		{
			int ret = RET_OK;
			LX_DE_WIN_DIMENSION_T param;
			int win_id;
			int x, y, w, h;
			sscanf( command, " %d %d %d %d %d", &win_id, &x, &y, &w, &h);
			param.win_id = (LX_DE_WIN_ID_T)win_id;
			param.rect.x = (UINT16)x;
			param.rect.y = (UINT16)y;
			param.rect.w = (UINT16)w;
			param.rect.h = (UINT16)h;
			ret = DE_IO_SetVTVInputPosition((unsigned long)&param);
		}break;

		case PROC_ID_FORCE_CMA_ERROR:
		{
			extern void DE_IO_MaskControl(int flag);
			int flag = 0;
			sscanf( command, " %d", &flag);
			DE_IO_MaskControl(flag);
		}break;

		case PROC_ID_SET_VENC:
		{
			int ret = RET_OK;
			LX_DE_DVR_DISFMT_T param;
			int bOnOff;
			int w, h, fr;
			param.scan = 0;
			printk("\nset_venc  bOnOff h_size v_size fr_rate\n");
			sscanf( command, " %d %d %d %d", &bOnOff, &w, &h, &fr);
			param.bOnOff = (BOOLEAN)bOnOff;
			param.h_size = w;
			param.v_size = h;
			param.fr_rate = fr;
			ret = DE_IO_SetDvrFmtCtrl((unsigned long)&param,1);
		}break;

		case PROC_ID_SET_DELAY_INTR:
		{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
			extern void VIDEO_CPU_VIDEO_DELAY_FROM_MCU(struct tasklet_struct *temp);
			struct tasklet_struct *temp = NULL;
#else
			extern void VIDEO_CPU_VIDEO_DELAY_FROM_MCU(unsigned long temp);
			unsigned long temp = 0;
#endif
			VIDEO_CPU_VIDEO_DELAY_FROM_MCU(temp);
		}break;

		case PROC_ID_V4L2_VSC_EVENT:
		{
			//int ret = RET_OK;
			int win, type, val;
			extern void post_event(int win, int type, int val);
			sscanf( command, " %d %d %d", &win, &type, &val);
			post_event(win, type, val);
		}break;

		case PROC_ID_V4L2_VT :
		{
			int c=5, w, h;
			unsigned int v, p;
			int proc_capture(int cmd, int w, int h, unsigned int *v, unsigned int *p);
			sscanf( command, " %d %d %d %d", &w, &h, &v, &p); // manual set cmd
			proc_capture(c, w, h, &v, &p);
			printk("set hist cmd = %d param = %d", v, p);
		}break;

		case PROC_ID_V4L2_GPS :
		{
			int cmd, p1, p2, p3, p4, p5;
			int proc_gps(int cmd, int p1, int p2, int p3, int p4, int p5);
			sscanf( command, " %d %d %d %d %d %d", &cmd, &p1, &p2, &p3, &p4, &p5);
			proc_gps(cmd, p1, p2, p3, p4, p5);
		}break;

		case PROC_ID_V4L2_PIXELGRAB :
		{
			int test_read_cvi_pixel_BarPixelGrab(void);
			test_read_cvi_pixel_BarPixelGrab();
		}break;

		case PROC_ID_FPP_FINAL :
		{
			unsigned long arg;
			UINT32 stParams = FALSE;
			arg = (unsigned long)&stParams;
			DE_IO_GetFPPInfo(arg, 1);
		}break;

		case PROC_ID_SWITCH_MCU :
		{
			UINT32 id;
			sscanf( command, " %d", &id);
			v4l2_vsc_switchmcu(id);
		}break;

		case PROC_ID_BIN_DOWNLOAD :
		{
			extern int de_proc_bin_write_function(int id, char* command);
			de_proc_bin_write_function(0, command);
		}break;

		case PROC_ID_KEEP_SUB_MODE :
		{
			UINT32 id;
			sscanf( command, " %d", &id);
			v4l2_vsc_keep_submode(id);
		}break;

		case PROC_ID_ENABLE_DBG_MAP :
		{
			int ret = RET_OK;
			UINT32 flag;
			sscanf( command, " %d", &flag);
			ret = de_proc_enable_dbg_map(flag);
		}break;

		case PROC_ID_ALLOC_DBG_MAP :
		{
			de_proc_alloc_dbg_map(command);
		}break;

		case PROC_ID_VSC_OPRINT :
		{
			if (!strncmp(command,"off",strlen("off"))) {
				vsc_oprint_enable(0);
			}
			else if (!strncmp(command,"on",strlen("on"))) {
				vsc_oprint_enable(1);
			}
			else if (!strncmp(command,"big",strlen("big"))) {
				vsc_oprint_set_size(1);
			}
			else if (!strncmp(command,"small",strlen("small"))) {
				vsc_oprint_set_size(0);
			}
			else if (!strncmp(command,"red",strlen("red"))) {
				vsc_oprint_set_color(1,0,0);
			}
			else if (!strncmp(command,"green",strlen("green"))) {
				vsc_oprint_set_color(0,1,0);
			}
			else if (!strncmp(command,"blue",strlen("blue"))) {
				vsc_oprint_set_color(0,0,1);
			}
			else if (!strncmp(command,"white",strlen("white"))) {
				vsc_oprint_set_color(1,1,1);
			}
			else if (!strncmp(command,"black",strlen("black"))) {
				vsc_oprint_set_color(0,0,0);
			}
			else {
				vsc_oprint("%s",command);
			}
		}break;

		case PROC_ID_FR_RATE :
		{
			int ret = RET_OK;
			LX_DE_FR_RATE_T frate;
			UINT32 freerun,rate;
			ret = sscanf( command, "%d %d", &freerun, &rate);
			frate.isForceFreeRun = freerun;
			frate.fr_rate = (UINT32)rate;
			ret = resource_mgr_ioctl(DE_IOW_SET_FR_RATE,(unsigned long)&frate,CALL_FROM_KERNEL);
		}break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

int _DE_WriteProcDbgFunc( char* command )
{
	int icountMax;
	int funcNo = -1;
	int iDefArgs;
	int ret = RET_OK;
	char *str;

	icountMax = sizeof(gDE_FuncList)/sizeof(gDE_FuncList[0]);
#ifdef FUNCTION_NAME_CMD
	sscanf( command, " %s %d", g_functioname,&iDefArgs);

	for(i=0;i<icountMax;i++)
	{
		if(!strcmp(g_functioname,gDE_FuncList[i].sName))
		{
			funcNo = gDE_FuncList[i].iFunc_no;
			break;
		}
	}
	if(funcNo == -1){
		printk("Invalid Function Name. Please Enter Valid Driver function Name (without DE_IO_)\n");
		return RET_ERROR;
	}
	printk("Function to be debugged is %s\n",g_functioname);
#else
	sscanf( command, " %x %d", &funcNo,&iDefArgs);
	if(funcNo<=0 || funcNo>icountMax)
	{
		printk("Invalid Function Number. Please Enter valid Function Number value\n");
		return RET_ERROR;
	}
	str = gDE_FuncList[funcNo-1].sName;
	
	if(strlen(str) < MAX_CHAR_LENGTH)
		strncpy(g_functioname,str, strlen(str));
	printk("Function to be debugged is %s\n",g_functioname);
#endif
	printk("funcNo 0x%x\n",funcNo);
	//printk("iDefArgs %d\n",iDefArgs);

	if(0 != iDefArgs ){
		if(g_args ==NULL){
				printk("Please fill the arguments before calling the function with non-default arguments\n");
				return RET_ERROR;
		}
	}
	ret = DE_Func_Debugger(funcNo,iDefArgs)	;

	if(ret==RET_OK)
	{
		printk("DE_IO_%s Success\n",g_functioname);
	}
	else
	{
		printk("DE_IO_%s Fail\n",g_functioname);
	}
	return ret;
}

int _DE_WriteProcArgs ( char* command )
{
	int iFuncNo = -1,iArgNo = -1,iArgvalue = -1;
	int iArgvalue1=-1,iArgvalue2=-1,iArgvalue3=-1,iArgvalue4=-1;//to handle user inputs of full int, two shorts, or 4 chars
	//in case of single integer only iArgvalue1, two shorts, LSW = iArgvalue1 MSW = iArgvalue2, four chars iArgvalue1 = LSB iArgvalue2 = 2nd Low Byte, iArgvalue3 = 2nd Upper Byte, iArgvalue4 = MSB
	int ret = RET_OK;
	int icountMax;

	//sscanf( command, "%d %d %d", &iFuncNo,&iArgNo,&iArgvalue);
	icountMax = sizeof(gDE_FuncList)/sizeof(gDE_FuncList[0]);
#ifdef FUNCTION_NAME_CMD
	sscanf( command, " %s %d %d %d %d %d", g_functioname,&iArgNo,&iArgvalue1,&iArgvalue2,&iArgvalue3,&iArgvalue4);

	for(i=0;i<icountMax;i++)
	{
		if(!strcmp(g_functioname,gDE_FuncList[i].sName))
		{
			iFuncNo = gDE_FuncList[i].iFunc_no;
			break;
		}
	}
	if(iFuncNo == -1){
		printk("Invalid Function Name. Please Enter Valid Driver function Name (without DE_IO_)\n");
		return RET_ERROR;
	}

#else
	sscanf( command, " %x %d %d %d %d %d", &iFuncNo,&iArgNo,&iArgvalue1,&iArgvalue2,&iArgvalue3,&iArgvalue4);
	if(iFuncNo<=0 || iFuncNo>icountMax)
	{
		printk("Invalid Function Number. Please Enter valid Function Number value\n");
		return RET_ERROR;
	}
	strncpy(g_functioname,gDE_FuncList[iFuncNo-1].sName,48);
#endif
	printk("Arg at offset %d provided for DE_IO_%s\n",iArgNo,g_functioname);
	//printk("%d %d %d %d\n",iArgvalue1,iArgvalue2,iArgvalue3,iArgvalue4);
	if(-1==iArgvalue2 )
	{
		iArgvalue = iArgvalue1;
	}
	else if(-1 == iArgvalue3)
	{
		iArgvalue = DE_Make_Arg_From_Short(iArgvalue1,iArgvalue2);
		//printk("iArgvalue1 = 0x%08x iArgvalue2 = 0x%08x, iArgvalue = 0x%08x\n",iArgvalue1,iArgvalue2,iArgvalue);
	}
	else
	{
		iArgvalue = DE_Make_Arg_From_Char(iArgvalue1,iArgvalue2,iArgvalue3,iArgvalue4);
		//printk("iArgvalue1 = 0x%08x iArgvalue2 = 0x%08x,iArgvalue3 = 0x%08x iArgvalue4 = 0x%08x, iArgvalue = 0x%08x\n",iArgvalue1,iArgvalue2,iArgvalue3,iArgvalue4,iArgvalue);
	}

	ret = DE_Assign_Debug_Gbl_Ptr(iFuncNo,iArgNo,iArgvalue);
	return ret;
}

int _DE_WriteProcPIP ( char* command )
{
	int iPipState = 0,iPipPos = 0;
	int ret = RET_OK;
	unsigned long arg;

	LX_DE_INPUT_SOURCE_T SrcIpParam = {0, };
	LX_DE_WIN_DIMENSION_T WinOutParam;
	sscanf(command, "%d %d",&iPipState,&iPipPos);

	arg = (unsigned long)&iPipState;
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_MultiWinEnable);

	SrcIpParam.srcId = LX_DE_WIN_SUB;
	SrcIpParam.srcType = LX_DE_IN_SRC_MVI;
	SrcIpParam.srcPort = 0;
	SrcIpParam.srcAttr = 0;
	arg = (unsigned long)&SrcIpParam;
	CALL_IO(DE_IO_SetWinPortSrc);

	WinOutParam.win_id = LX_DE_WIN_SUB;

	switch(iPipPos)
	{
		case 0:{//right bottom
				WinOutParam.rect.w = 1350;
				WinOutParam.rect.h = 900;
				WinOutParam.rect.x = 2300;
				WinOutParam.rect.y = 1100;
			}break;
		case 1:{//left bottom
				WinOutParam.rect.w = 1350;
				WinOutParam.rect.h = 900;
				WinOutParam.rect.x = 100;
				WinOutParam.rect.y = 1100;
			}break;
		case 2:{//left top
				WinOutParam.rect.w = 1350;
				WinOutParam.rect.h = 900;
				WinOutParam.rect.x = 100;
				WinOutParam.rect.y = 100;
			}break;
		case 3:
		default:{//right top
				WinOutParam.rect.w = 1350;
				WinOutParam.rect.h = 900;
				WinOutParam.rect.x = 2300;
				WinOutParam.rect.y = 100;
			}break;
	}
	arg = (unsigned long)&WinOutParam;
	CALL_IO(DE_IO_SetOutWin);

	return RET_OK;
}

#if 0	//not used
static void _DE_WIN_PrintoutLowDelay (struct seq_file *m, LX_DE_WIN_ID_T win_id)
{
	LX_DE_LOW_DELAY_T param;

	unsigned long arg;
	int ret;

	memset( &param, 0, sizeof(param));

	param.wId_enable = win_id;

	arg = (unsigned long)((LX_DE_LOW_DELAY_T __user*)&param);
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetLowDelay);

	seq_printf(m,
			"low-delay.enable: %d\n"
			"low-delay.lock: %d\n"
			"low-delay.time: %d ms\n"
			"low-delay.frame: %d\n"
			"low-delay.locked_time: %d ms\n",
			param.wId_enable,
			param.lock,
			param.time,
			param.frame,
			param.locked_time
			);
}
#endif

static void _DE_WIN_PrintTimingInfo(struct seq_file *m, LX_DE_WIN_ID_T win_id)
{
	kwrap_vp_timing_info_t ti;

	if (lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		return;
	}

	if (0 == vsc_get_timinginfo((UINT8)win_id,&ti))
	{
		seq_printf(m,"h/v active : %d / %d\n",ti.hActive,ti.vActive);
		seq_printf(m,"scanType   : %d\n",ti.scanType);
		seq_printf(m,"vFreq      : %d\n",ti.vFreq);
		seq_printf(m,"svp        : %d\n",ti.svp);
		seq_printf(m,"hdr_type   : %d\n",ti.hdr_type);
		seq_printf(m,"colordomain: %d\n",ti.colordomain);
		seq_printf(m,"hdmi444mode: %d\n",ti.hdmi444mode);
		seq_printf(m,"phyMode    : %d\n",ti.phyMode);
	}
}

#if 0	//not used
static void _DE_WIN_PrintoutInputWin (struct seq_file *m, LX_DE_WIN_ID_T win_id)
{
	LX_DE_WIN_DIMENSION_T param;
	unsigned long arg;
	int ret;

	memset( &param, 0, sizeof(param));

	param.win_id = win_id;

	arg = (unsigned long)((LX_DE_WIN_DIMENSION_T __user*)&param);

	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetInputWin);

	seq_printf(m,
			"input-win.w: %d\n"
			"input-win.h: %d\n"
			"input-win.x: %d\n"
			"input-win.y: %d\n",
			param.rect.w,
			param.rect.h,
			param.rect.x,
			param.rect.y
			);
}

static void _DE_WIN_PrintoutOutWin (struct seq_file *m, LX_DE_WIN_ID_T win_id)
{
	LX_DE_WIN_DIMENSION_T param;
	unsigned long arg;
	int ret;

	memset( &param, 0, sizeof(param));

	param.win_id = win_id;

	arg = (unsigned long)((LX_DE_WIN_DIMENSION_T __user*)&param);

	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetOutWin);

	seq_printf(m,
			"output-win.w: %d\n"
			"output-win.h: %d\n"
			"output-win.x: %d\n"
			"output-win.y: %d\n",
			param.rect.w,
			param.rect.h,
			param.rect.x,
			param.rect.y
			);
}
#endif
static void _DE_WIN_PrintoutFWVer (struct seq_file *m)
{
	LX_DE_FIRMWARE_INFO_T param;
	unsigned long arg;
	int ret;

	memset( &param, 0, sizeof(param));

	arg = (unsigned long)((LX_DE_FIRMWARE_INFO_T __user*)&param);

	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetFirmwareInfo);
	DE_IO_Resume(FALSE);

	seq_printf(m, "fw_version: %d (%d/%d/%d)\n", param.version, param.date.year, param.date.month, param.date.day);
}

struct de_status_symbol {
	unsigned int value;
	char * string;
};

#define GET_STATUS_SYM(a, v) ( { \
	int i; \
	char * rtn = "NG"; \
	for (i=0; i < ARRAY_SIZE(a); i++) \
		if( a[i].value == v ) { \
			rtn = a[i].string; \
			break; \
		} \
	rtn; \
} )

static void _DE_WIN_PrintoutSystem (struct seq_file *m)
{
	LX_DE_SYS_STATUS_T param;
	unsigned long arg;
	int ret;

	struct de_status_symbol display_type[] = {
		{ LX_DE_DIS_DEV_LCD,  "LCD" },
		{ LX_DE_DIS_DEV_PDP,  "PDP" },
		{ LX_DE_DIS_DEV_OLED, "OLED" },
		{ LX_DE_DIS_DEV_CP,   "CPBOX" },
		{ LX_DE_DIS_DEV_STB,  "SETTOP" },
	};

	struct de_status_symbol display_mirror[] = {
		{ LX_DE_DIS_MIRROR_OFF,  "off" },
		{ LX_DE_DIS_MIRROR_X,    "x" },
		{ LX_DE_DIS_MIRROR_Y,    "y" },
		{ LX_DE_DIS_MIRROR_X_Y,  "xy" },
	};

	struct de_status_symbol frc_type[] = {
		{ LX_DE_FRC_PATH_INTERNAL,  "Internal" },
		{ LX_DE_FRC_PATH_EXTERNAL,  "External" },
	};

	struct de_status_symbol trid_type[] = {
		{ LX_DE_3D_CTRL_OFF,  "off" },
		{ LX_DE_3D_CTRL_ON,   "on" },
	};

	struct de_status_symbol display_size[] = {
		{ LX_PANEL_TYPE_1920, "1920x1080" },
		{ LX_PANEL_TYPE_1366, "1366x768" },
		{ LX_PANEL_TYPE_1024, "1024x768" },
		{ LX_PANEL_TYPE_1365, "1365x768" },
		{ LX_PANEL_TYPE_3840, "3840x2160" },
		{ LX_PANEL_TYPE_1280, "1280x720" },
		{ LX_PANEL_TYPE_720,  "720x480" },
		{ LX_PANEL_TYPE_640,  "640x480" },
		{ LX_PANEL_TYPE_576,  "720x576" },
	};

	memset( &param, 0, sizeof(param));

	param.status_type = LX_DE_SYS_STATUS_ALL;

	arg = (unsigned long)((LX_DE_SYS_STATUS_T __user*)&param);
	DE_IO_Resume(TRUE);
	CALL_IO(DE_IO_GetSystemStatus);
	DE_IO_Resume(FALSE);

	seq_printf(m,
			"display_type: %s (0x%x)\n"
			"display_mirror: %s (0x%x)\n"
			"frc_type: %s (0x%x)\n"
			"trid_type: %s (0x%x)\n"
			"fc_mem: 0x%x\n"
			"display_size: %s (0x%x)\n",
			GET_STATUS_SYM(display_type, param.display_type), param.display_type,
			GET_STATUS_SYM(display_mirror, param.display_mirror), param.display_mirror,
			GET_STATUS_SYM(frc_type, param.frc_type), param.frc_type,
			GET_STATUS_SYM(trid_type, param.trid_type), param.trid_type,
			param.fc_mem,
			GET_STATUS_SYM(display_size, param.display_size), param.display_size
			);
}

extern int v4l2_vsc_getlocalmute(int win);
extern int de_kwrap_getlowdelaymode(void);
static void _DE_WIN_PrintStatus( struct seq_file *m, void* data)
{
	LX_DE_WIN_ID_T win_id = (LX_DE_WIN_ID_T)data;

	seq_printf(m, "localmute=%d\n",v4l2_vsc_getlocalmute(win_id));
	if (win_id ==0)	seq_printf(m, "lowdelaymode=%d\n",de_kwrap_getlowdelaymode());

	_DE_WIN_PrintTimingInfo(m, win_id);
	#if 0	//not used
	_DE_WIN_PrintoutInputWin(m, win_id);
	_DE_WIN_PrintoutOutWin(m, win_id);
	_DE_WIN_PrintoutLowDelay(m, win_id);
	#endif
}

extern int vsc_get_dev_info(int win, int param);
extern void de_cfg_print_status(struct seq_file *m);
static void _DE_PrintStatus (struct seq_file * m, void * data)
{
	_DE_WIN_PrintoutFWVer(m);
	seq_printf(m, "socts_option=%d\n",vsc_get_dev_info(0,socts_option));
	_DE_WIN_PrintoutSystem(m);
	de_cfg_print_status(m);
}

static void _DE_PrintUsages (struct seq_file * m, void * data)
{
	struct v4l2_ext_vsc_connect_info input;

	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"vsc_set_sub_mode\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"echo 3 (flag) (wid) (win_mode) (mirror_mode) (mem_type)\n");
	seq_printf(m,"flag : 0:get, 1:set\n");
	seq_printf(m,"win_mode     : 0:none, 1:pip, 2:pbp\n");
	seq_printf(m,"mirror_mode  : 0:none, 1:on, 2:off\n");
	seq_printf(m,"mem_type     : 0:none, 1:single, 2:multi\n");
	seq_printf(m,"pip on  : echo 3 1 1 1 2 2 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"vsc_set_input\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"echo 0 (flag) (wid) (src) (idx) (attr) (disp) > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"flag : 0:get, 1:set\n");
	seq_printf(m,"src  : 0:none, 1:avd, 2:adc, 3:hdmi, 4:vdec, 5:jpeg\n");
	seq_printf(m,"idx  : 0~3:hdmi port\n");
	seq_printf(m,"attr : 0:atv, 1:av\n");
	vsc_set_input(0, 0, &input);
	seq_printf(m,"curr 0 : src:%d, idx:%d, attr:%d, disp:%d\n",input.in.src,input.in.index,input.in.attr,input.out);
	vsc_set_input(0, 1, &input);
	seq_printf(m,"curr 1 : src:%d, idx:%d, attr:%d, disp:%d\n",input.in.src,input.in.index,input.in.attr,input.out);
	vsc_set_input(0, 2, &input);
	seq_printf(m,"curr 2 : src:%d, idx:%d, attr:%d, disp:%d\n",input.in.src,input.in.index,input.in.attr,input.out);
	vsc_set_input(0, 3, &input);
	seq_printf(m,"curr 3 : src:%d, idx:%d, attr:%d, disp:%d\n",input.in.src,input.in.index,input.in.attr,input.out);
	seq_printf(m,"atv(w0)   : echo 0 1 0 1 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"av(w0)    : echo 0 1 0 1 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"comp(w0)  : echo 0 1 0 2 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi0(w0) : echo 0 1 0 3 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi1(w0) : echo 0 1 0 3 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi2(w0) : echo 0 1 0 3 2 2 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi3(w0) : echo 0 1 0 3 3 3 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"vdec(w0)  : echo 0 1 0 4 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"jpeg(w0)  : echo 0 1 0 5 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"atv(w1)   : echo 0 1 1 1 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"av(w1)    : echo 0 1 1 1 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"comp(w1)  : echo 0 1 1 2 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi0(w1) : echo 0 1 1 3 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi1(w1) : echo 0 1 1 3 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi2(w1) : echo 0 1 1 3 2 2 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"hdmi3(w1) : echo 0 1 1 3 3 3 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"vdec(w1)  : echo 0 1 1 4 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"jpeg(w1)  : echo 0 1 1 5 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"vsc_set_win_info\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"echo 2 (flag) (wid) (iw:x,y,w,h) (src:w,h) (ow:x,y,w,h) (rot)\n");
	seq_printf(m,"flag : 0:get, 1:set\n");
	seq_printf(m,"2k(w0) : echo 2 1 0 0 0 1920 1080 1920 1080 0 0 3840 2160 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"2k(w1) : echo 2 1 1 0 0 1920 1080 1920 1080 0 0 3840 2160 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"vsc_set_mute\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"echo 1 (flag) (wid) (color)\n");
	seq_printf(m,"flag  : 0:get, 1:set\n");
	seq_printf(m,"color : 0:off, 1:black, 2:blue, 3:gray\n");
	seq_printf(m,"mute(w0) on  : echo 1 1 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"mute(w1) on  : echo 1 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"mute(w0) off : echo 1 1 0 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"mute(w1) off : echo 1 1 1 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"bbd\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"register(w0)   : echo 12 1 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"unregister(w0) : echo 12 0 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"register(w1)   : echo 12 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"unregister(w1) : echo 12 0 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"dbg off        : echo 13 1 0 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"dbg(w0) on     : echo 13 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"dbg(w1) on     : echo 13 1 2 > /proc/lg/de/v4l2_vsc_debug_func\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"hdr\n");
	seq_printf(m,"----------------------------------------\n");
	seq_printf(m,"echo %d (flag) (wid) (0:sdr,1:h10,2:dovi,3:hlg)\n",V4l2_SET_HDR_TYPE);
	seq_printf(m,"hdr10(w1) : echo %d 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func\n",V4l2_SET_HDR_TYPE);
	seq_printf(m,"hlg(w2)   : echo %d 1 2 3 > /proc/lg/de/v4l2_vsc_debug_func\n",V4l2_SET_HDR_TYPE);
	seq_printf(m,"----------------------------------------\n");
}

extern int de_proc_slt_status(struct seq_file *m);
static int _DE_PrintSltStatus(struct seq_file *m)
{
	return de_proc_slt_status(m);
}

extern void vsc_fw_print_status(struct seq_file *m);
static void _DE_PrintFwStatus(struct seq_file *m)
{
	vsc_fw_print_status(m);
}

extern void vsc_cg_print_status(struct seq_file *m);
static void _DE_PrintCgStatus(struct seq_file *m)
{
	vsc_cg_print_status(m);
}

extern LX_DE_GPS_CTRL_T *g_dbg_pgps_ctx[8];
extern int vsc_get_dev_info(int win, int param);
static int _proc_vsc_status_show(struct seq_file *m, void *data)
{
	int i;
	int index = 0;
	char str_buf[100];
	const char *vsc_connect_type[V4L2_EXT_VSC_INPUT_SRC_JPEG+1] = {
		"NONE", "AVD", "ADC", "HDMI", "VDEC", "JPEG"
	};
	const char *vsc_output_mode[V4L2_EXT_VSC_DEST_AVE+1] = {
		"NONE", "DISPLAY", "VENC", "MEMORY", "AVE"
	};
	const char *vsc_win[6] = {
		"main.p0", "sub.p0", "sub.p1", "sub.p2", "gps.p0", "vt.p0"
	};
	if(!m)
	{
		printk("%s : null", __F__);
		return 0;
	}
	if(!m->private) {
		index = 0;
	}
	else {
		index = *(int *)m->private;
	}
	if(index >= 6)
	{
		printk("invalid index[%d]\n", index);
		return -1;
	}
	memset(str_buf, 0, sizeof(100));

/*	seq_printf(m, "version=linuxtv-ext-header ver.%d.%d.%d (submissions/%d)\n",\
		LINUXTV_EXT_VER_MAJOR, LINUXTV_EXT_VER_MINOR, LINUXTV_EXT_VER_PATCH,\
		LINUXTV_EXT_VER_SUBMISSION);*/
	seq_printf(m, "[%s]\n", vsc_win[index]);
	seq_printf(m, "open=%d\n",            vsc_get_dev_info(index, vdev_open));
	seq_printf(m, "connect_src=%s\n",     vsc_connect_type[vsc_get_dev_info(index, connect_src)]);
	seq_printf(m, "connect_index=%d\n",   vsc_get_dev_info(index, connect_index));
	seq_printf(m, "connect_attr=%d\n",    vsc_get_dev_info(index, connect_index));
	seq_printf(m, "output_mode=%s\n",     vsc_output_mode[vsc_get_dev_info(index, output_mode)]);
	seq_printf(m, "mute=%d\n",            vsc_get_dev_info(index, mute));
	seq_printf(m, "hdr=%d\n",             vsc_get_dev_info(index, hdr));
	seq_printf(m, "source_x=%d\n",        vsc_get_dev_info(index, source_x));
	seq_printf(m, "source_y=%d\n",        vsc_get_dev_info(index, source_y));
	seq_printf(m, "source_w=%d\n",        vsc_get_dev_info(index, source_w));
	seq_printf(m, "source_h=%d\n",        vsc_get_dev_info(index, source_h));
	seq_printf(m, "crop_x=%d\n",          vsc_get_dev_info(index, crop_x));
	seq_printf(m, "crop_y=%d\n",          vsc_get_dev_info(index, crop_y));
	seq_printf(m, "crop_w=%d\n",          vsc_get_dev_info(index, crop_w));
	seq_printf(m, "crop_h=%d\n",          vsc_get_dev_info(index, crop_h));
	seq_printf(m, "out_x=%d\n",           vsc_get_dev_info(index, out_x));
	seq_printf(m, "out_y=%d\n",           vsc_get_dev_info(index, out_y));
	seq_printf(m, "out_w=%d\n",           vsc_get_dev_info(index, out_w));
	seq_printf(m, "out_h=%d\n",           vsc_get_dev_info(index, out_h));
	seq_printf(m, "rotation=%d\n",        vsc_get_dev_info(index, rotation));
	seq_printf(m, "freeze=%d\n",          vsc_get_dev_info(index, freeze));
	seq_printf(m, "rgb444=%d\n",          vsc_get_dev_info(index, rgb444));
	seq_printf(m, "adaptive=%d\n",        vsc_get_dev_info(index, adaptive));
	seq_printf(m, "frame_delay=%d\n",     vsc_get_dev_info(index, frame_delay));
	seq_printf(m, "property_window=%d\n", vsc_get_dev_info(index, property_window));
	seq_printf(m, "property_mirror=%d\n", vsc_get_dev_info(index, property_mirror));
	seq_printf(m, "property_memory=%d\n", vsc_get_dev_info(index, property_memory));
	seq_printf(m, "zorder_value=%d\n",    vsc_get_dev_info(index, zorder_value));
	seq_printf(m, "zorder_alpha=%d\n",    vsc_get_dev_info(index, zorder_alpha));
	seq_printf(m, "pattern=%d\n",         vsc_get_dev_info(index, pattern));
	seq_printf(m, "limited_win_ratio_h_scaleup=%d\n",   vsc_get_dev_info(index, limited_win_ratio_h_scaleup));
	seq_printf(m, "limited_win_ratio_v_scaleup=%d\n",   vsc_get_dev_info(index, limited_win_ratio_v_scaleup));
	seq_printf(m, "limited_win_ratio_h_scaledown=%d\n", vsc_get_dev_info(index, limited_win_ratio_h_scaledown));
	seq_printf(m, "limited_win_ratio_v_scaledown=%d\n", vsc_get_dev_info(index, limited_win_ratio_v_scaledown));

	if(index == 4)//"gps.p0"
	{
		for (i=0;i<8;i++)
		{
			LX_DE_GPS_CTRL_T *p = g_dbg_pgps_ctx[i];
			seq_printf(m, "pgps_ctx[%d] : ",i);
			if (p!=NULL)
			{
				seq_printf(m, "en[%d]/gps[%d]/vdec[%d]/w[%d/%d]h[%d/%d]/s[%d]/y0[0x%08x]/c0[0x%08x]", \
					p->enable, p->gps_id, p->vdec_id, p->width, p->max_w, p->height, p->max_h, p->stride,\
					p->buffer_addr_y[0], p->buffer_addr_c[0]);
				seq_printf(m, "y1[0x%08x]/c1[0x%08x]", p->buffer_addr_y[1], p->buffer_addr_c[1]);
				seq_printf(m, "y2[0x%08x]/c2[0x%08x]", p->buffer_addr_y[2], p->buffer_addr_c[2]);
				seq_printf(m, "bbd[%d][%d/%d/%d/%d/%d]",p->bbd_id,p->bbd_en,\
					(p->bbd_xw>>16)&0xffff,(p->bbd_yh>>16)&0xffff,p->bbd_xw&0xffff,p->bbd_yh&0xffff);
			}
			seq_printf(m, "\n");
		}
	}
	return 0;
}

static int _proc_vsc_status_open(struct inode *inode, struct file *file)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	return single_open(file, _proc_vsc_status_show, pde_data(inode));
#else
	return single_open(file, _proc_vsc_status_show, PDE_DATA(inode));
#endif
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops _proc_vsc_status_fops = {
	.proc_open = _proc_vsc_status_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations _proc_vsc_status_fops = {
	.open = _proc_vsc_status_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
static int vsc_index[6] = {0, 1, 2, 3, 4, 5};
/**
 * initialize proc utility for de device
 *
 * @see DE_Init
*/
void	DE_PROC_Init (void)
{
	struct proc_dir_entry *de_proc_dir;
	struct proc_dir_entry *vsc_proc_seetv_root = OS_PROC_GetLinuxTvEntry();

	de_proc_dir = OS_PROC_CreateEntryEx ( DE_MODULE, _g_de_device_proc_table,
												_DE_ReadProcFunction,
												_DE_WriteProcFunction );

	OS_PROC_CreateEntry( "win0", de_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_de_win0_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "win1", de_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_de_win1_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "win2", de_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_de_win2_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "win3", de_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_de_win3_proc_table, NULL, NULL );

	// seetv proc status
	vsc_proc_seetv = proc_mkdir("scaler", vsc_proc_seetv_root);

	proc_create_data("main.p0", 0440, vsc_proc_seetv, &_proc_vsc_status_fops, &vsc_index[0]);
	proc_create_data("sub.p0",  0440, vsc_proc_seetv, &_proc_vsc_status_fops, &vsc_index[1]);
	proc_create_data("sub.p1",  0440, vsc_proc_seetv, &_proc_vsc_status_fops, &vsc_index[2]);
	proc_create_data("sub.p2",  0440, vsc_proc_seetv, &_proc_vsc_status_fops, &vsc_index[3]);
	proc_create_data("gps.p0",  0440, vsc_proc_seetv, &_proc_vsc_status_fops, &vsc_index[4]);
	proc_create_data("vt.p0",   0440, vsc_proc_seetv, &_proc_vsc_status_fops, &vsc_index[5]);
}

/**
 * cleanup proc utility for de device
 *
 * @see DE_Cleanup
*/
void	DE_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( DE_MODULE );
}
#if 0	//not used
static void __HAL_HWRAP_Debug(char *command)
{
	HAL_VSC_HWRAP_DEBUG_FUNCNUM func_num;
	sscanf(command," %d",&func_num);
	printk(" **************func number is %d %s\n",func_num,command);
	switch(func_num)
	{
		case HAL_VSC_HWRAP_INIT:
		{
			VIDEO_WID_T wId;
			//BOOLEAN bOnOff;
			//BOOLEAN bAll;
			//sscanf(command," %d %d %d %d",&func_num,&wId,&bOnOff,&bAll);
			printk("calling hal_vsc_hwrap_initialize function to create vp Thread\n");
			int ret =  hal_vsc_hwrap_initialize();
		}break;
		case HAL_VSC_HWRAP_UNINIT:
		{
			VIDEO_WID_T wId;
			//BOOLEAN bOnOff;
			//BOOLEAN bAll;
			//sscanf(command," %d %d %d %d",&func_num,&wId,&bOnOff,&bAll);
			printk("calling hal_vsc_hwrap_Uninitialize function to create vp Thread\n");
			int ret =  hal_vsc_hwrap_Uninitialize();
		}break;
		case HAL_VSC_HWRAP_CONNECT:
		{
			VIDEO_WID_T wId;
			VSC_INPUT_SRC_INFO_T vscInput;
			VSC_OUTPUT_MODE_T outputmode;
			printk("calling cvsc_hwrap_connect func..............%s\n",command);
			sscanf(command,"%d %d %d %d %d %d",&func_num,&wId,&vscInput.type,&vscInput.attr,&vscInput.resourceIndex, &outputmode);
			printk("WID = %d outputmode = %d %s\n",wId,outputmode);
			int ret = hal_vsc_hwrap_open(wId);
			if(ret)
				 DE_ERROR("hal VSC Open failed\n");
			ret = hal_vsc_hwrap_connect(wId, vscInput, outputmode);
		}break;
		case HAL_VSC_HWRAP_DISONNECT:
		{
			VIDEO_WID_T wId;
			VSC_INPUT_SRC_INFO_T vscInput;
			VSC_OUTPUT_MODE_T outputmode;
			UINT8 val;
			sscanf(command," %d %d %d %d %d",&func_num,&wId,&vscInput.type,&vscInput.attr,&outputmode);
			printk("arguments from command wid = %d\n",wId);
			int ret;
			ret =hal_vsc_hwrap_disconnect(wId, vscInput, outputmode);
			if(ret)
				DE_ERROR("failed executing the hal_vsc_hwrap_disconnect function\n");
			ret = hal_vsc_hwrap_close(wId);
		}break;
		case HAL_VSC_HWRAP_SETWINBLANK:
		{
			VIDEO_WID_T wId;
			BOOLEAN bOnOff;
			VIDEO_DDI_WIN_COLOR_T color;
			sscanf(command," %d %d %d %d",&func_num,&wId,&bOnOff,&color);
			int ret = hal_vsc_hwrap_setwinblank(wId, bOnOff,color);
			if(ret)
				printk("failed executing the hal_vsc_hwrap_setwinblank function........ %d\n",ret);
		}break;
		case HAL_VSC_HWRAP_SETIPOPRGN:
		{
			VIDEO_WID_T wId;
			VSC_ROTATE_T rotation;
			VSC_INPUT_REGION_T pInputRegion;
			VIDEO_RECT_T pOutputRegion;
			sscanf(command," %d %d %d %d %d %d %d %d %d %d %d %d %d",&func_num,&wId,&rotation,\
				&pInputRegion.originalInput.w,&pInputRegion.originalInput.h,\
				&pInputRegion.inRegion.x,&pInputRegion.inRegion.y,&pInputRegion.inRegion.w,&pInputRegion.inRegion.h,\
				&pOutputRegion.x,&pOutputRegion.y,&pOutputRegion.w,&pOutputRegion.h);
			int ret = hal_vsc_hwrap_setinputoutputregion ( wId,  rotation,  &pInputRegion,  &pOutputRegion);
		}break;
		case HAL_VSC_HWRAP_SETWINFRZ:
		{
			VIDEO_WID_T wId;
			BOOLEAN bOnOff;
			BOOLEAN bAll;
			sscanf(command," %d %d %d %d",&func_num,&wId,&bOnOff,&bAll);
			int ret =  hal_vsc_hwrap_setwinfreeze( wId,  bOnOff,  bAll);
		}break;
		default:
		{
			printk("invalid func numner passed from proc command\n");
		}break;
	}
}
static void __HAL_HWRAP_Help(void)
{
	printk("Hal functions numbers and examples to call hal API's are below\n");
	printk("0:HAL_VSC_HWRAP_INIT\n");
	printk("2:HAL_VSC_HWRAP_CONNECT - hal_vsc_hwrap_connect command:echo 2 0(wid) 3(type) 1(attr) 0(resourceIndex) 3(outputmode)\n");
	printk("3:HAL_VSC_HWRAP_DISONNECT - echo 3 0(win) 0(type) 0(attr) 0(outmode)\n");
	printk("4:HAL_VSC_HWRAP_SETWINBLANK - echo 4 0(win) 0(onoff) 0\n");
	printk("5:HAL_VSC_HWRAP_SETIPOPRGN - echo 5 0(win) 0(rot) 720 480(org) 0 0 720 480(in_win) 0 0 3840 2160(out_win)\n");
	printk("6:HAL_VSC_HWRAP_SETWINFRZ\n");
	printk("echo func_number func_agrs >/ proc/lg/de/hal_vsc_debug_func\n");
	printk("Example: echo 2 0 1 1 > /proc/lg/de/hal_vsc_debug_func which will call hal_vsc_hwrap_setwinblank\n");
}
#endif

struct file *de_filp = NULL;
int fw_size = 0;
extern unsigned int t_vsc_sec_prv, t_vsc_msec_prv;
extern LX_DE_RECT_T t_vsc_rect_prv;

void __V4l2_PROC_Debug(char * command)
{
	int funcnum;
	sscanf(command,"%d",&funcnum);
	switch(funcnum)
	{
		case V4l2_SET_INPUT:
		{
			struct v4l2_ext_vsc_connect_info input;
			BOOLEAN flag;
			UINT32 win, src, index, attr, out;
			sscanf(command,"%d %d %d %d %d %d %d",&funcnum,&flag,&win,&src,&index,&attr,&out);
			input.in.src = (enum v4l2_ext_vsc_input_src)src;
			input.in.index = index;
			input.in.attr = attr;
			input.out = (enum v4l2_ext_vsc_dest)out;
			vsc_set_input(flag,(UINT8)win,&input);
		}break;
		case V4l2_SET_MUTE:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 ip;
			sscanf(command,"%d %d %d %d",&funcnum,&flag,&win,&ip);
			vsc_set_mute(flag,(UINT8)win,&ip);
		}break;
		case V4l2_VSC_SET_WININFO:
		{
			BOOLEAN flag;
			UINT32 win;
			ktime_t 	   t;
			struct timespec64 ts;
			struct v4l2_ext_vsc_win_region ip;
			UINT32 x,y,w,h,resw,resh,outx,outy,outw,outh,rotation;
			extern unsigned int update_win_send_flag[LX_DE_WIN_MAX];
			sscanf(command,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d",\
				&funcnum,&flag,&win,\
				&x,&y,&w,&h,\
				&resw,&resh,\
				&outx,&outy,&outw,&outh,\
				&rotation);
			ip.in.crop.x = (UINT16)x;
			ip.in.crop.y = (UINT16)y;
			ip.in.crop.w = (UINT16)w;
			ip.in.crop.h = (UINT16)h;
			ip.in.res.w  = (UINT16)resw;
			ip.in.res.h  = (UINT16)resh;
			ip.out.x     = (UINT16)outx;
			ip.out.y     = (UINT16)outy;
			ip.out.w     = (UINT16)outw;
			ip.out.h     = (UINT16)outh;
			ip.rotation  = (UINT16)rotation;
			t  = ktime_get_real();
			ts = ktime_to_timespec64(t);
			t_vsc_sec_prv = ts.tv_sec;
			t_vsc_msec_prv = ts.tv_nsec/1000000;
			t_vsc_rect_prv.x = ip.out.x;
			t_vsc_rect_prv.y = ip.out.y;
			t_vsc_rect_prv.w = ip.out.w;
			t_vsc_rect_prv.h = ip.out.h;
			update_win_send_flag[win] = 0;
			vsc_set_win_info(flag,(UINT16)win,0,&ip);
		}break;
		case V4l2_SET_VENC:
		{
			int onoff = 0, pos = 0;
			//BOOLEAN flag;
			//UINT8 win;
			struct v4l2_ext_vsc_connect_info input;
			struct v4l2_ext_vsc_win_region window;

			sscanf(command,"%d %d %d", &funcnum,&onoff, &pos);

			memset(&input, 0, sizeof(struct v4l2_ext_vsc_connect_info));
			memset(&window, 0, sizeof(struct v4l2_ext_vsc_win_region));

			if(onoff==3) {
				input.in.src = V4L2_EXT_VSC_INPUT_SRC_JPEG;
				input.in.attr = 0;
				input.out = V4L2_EXT_VSC_DEST_VENC;
				vsc_set_fbpos(pos); //FB_NONE
			}
			else if(onoff==2) {
				input.in.src = V4L2_EXT_VSC_INPUT_SRC_FB;
				input.in.attr = 0;
				input.out = V4L2_EXT_VSC_DEST_VENC;
				vsc_set_fbpos(pos);
			}
			else if(onoff==1) {
				input.in.src = V4L2_EXT_VSC_INPUT_SRC_AVD; 
				input.in.attr = 0;				
				input.out = V4L2_EXT_VSC_DEST_VENC;
				vsc_set_fbpos(1);
			}
			else {
				input.in.src = V4L2_EXT_VSC_INPUT_SRC_NONE; 
				input.in.attr = 0;				
				input.out = V4L2_EXT_VSC_DEST_NONE;
				vsc_set_fbpos(0);
			}
			input.in.index = 0;
			vsc_set_input(1,1,&input);

			window.in.res.x = window.in.res.y = 0;
			window.in.res.w = 704;
			window.in.res.h = 480;
			window.out.x = window.out.y = 0;
			window.rotation = 0;
			window.out.w = 704;
			window.out.h = 480;
			if(onoff==3) {
				window.out.w = 1280;
				window.out.h = 720;
			}
			vsc_set_win_info(1,1,0,&window);
			if(onoff==3) {
				window.out.w = 640;
				window.out.h = 360;
				vsc_set_win_info(1,2,0,&window);
			}
		}break;
		case V4l2_SET_SUB_MODE:
		{
			BOOLEAN flag;
			UINT32 win;
			struct v4l2_ext_vsc_win_prop sub_data;
			UINT32 win_mode, mirror_mode, mem_type;
			sscanf(command,"%d %d %d %d %d %d\n",&funcnum,&flag,&win,&win_mode,&mirror_mode,&mem_type);
			sub_data.win_mode = (enum v4l2_ext_vsc_win_mode)win_mode;
			sub_data.mirror_mode = (enum v4l2_ext_vsc_mirror_mode)mirror_mode;
			sub_data.mem_type = (enum v4l2_ext_vsc_memory_type)mem_type;
			vsc_set_sub_mode(flag, (UINT8)win, &sub_data);
		}break;
		case V4L2_SET_SUB_OCCUPY:
		{
			BOOLEAN flag;
			UINT32 win;
			BOOLEAN p;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&p);
			vsc_set_sub_occupy(flag, (UINT8)win, &p);
		}break;
		case V4l2_SET_ZORDER:
		{
			BOOLEAN flag;
			UINT32 win, zorder[2], alpha[2];
			struct v4l2_ext_vsc_zorder z_data;
			sscanf(command,"%d %d %d %d %d\n",&funcnum,&flag,&win,&zorder[0],&alpha[0]);
			z_data.zorder = (UINT8)zorder[0];
			z_data.alpha  = (UINT8)alpha[0];
			vsc_set_zorder(flag,(UINT8)win,&z_data);
		}break;
		case V4l2_SET_ZORDER_INFO:
		{
			BOOLEAN flag;
			UINT8 win = 0;
			struct v4l2_ext_vsc_zorder_info z_data;
			sscanf(command,"%d %d %d %d %d %d\n",&funcnum,&flag,&z_data.z[0].zorder,z_data.z[1].zorder,&z_data.z[0].alpha,&z_data.z[1].alpha);
			vsc_set_zorder_info(flag,win,&z_data);
		}break;
		case V4l2_SET_VDO_MODE:
		{
			BOOLEAN flag;
			UINT32 win, vdo_port, vdec_port;
			struct v4l2_ext_vsc_vdo_mode vdo_info;
			sscanf(command,"%d %d %d %d %d\n",&funcnum,&flag,&win,&vdo_port,&vdec_port);
			vdo_info.vdo_port = (UINT8)vdo_port;
			vdo_info.vdec_port = (UINT8)vdec_port;
			vsc_set_vdo_mode(flag,(UINT8)win,&vdo_info);
		}break;
		case V4l2_SET_LAT_PATTERN:
		{
			BOOLEAN flag;
			UINT32 win;
			UINT32 pos_x, pos_y, width, height, p;
			struct v4l2_ext_vsc_latency_pattern_info lat_info;
			sscanf(command,"%d %d %d %d %d %d %d %d\n",&funcnum,&flag,&win,&pos_x,&pos_y,&width,&height,&p);
			lat_info.r.x = (short unsigned int)pos_x;
			lat_info.r.y = (short unsigned int)pos_y;
			lat_info.r.w = (short unsigned int)width;
			lat_info.r.h = (short unsigned int)height;
			lat_info.p   = (short unsigned int)p;
			vsc_set_latency_pattern(flag,(UINT8)win,&lat_info);
		}break;
		case V4l2_SET_PAT:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 data;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&data);
			vsc_set_pattern(flag,(UINT8)win,&data);
		}break;
		case V4l2_SET_FRM_DLY:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 data;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&data);
			vsc_set_frame_delay(flag,(UINT8)win,&data);
		}break;
		case V4l2_SET_AD_STRM:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 data;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&data);
			vsc_set_adaptives_stream(flag,(UINT8)win,&data);
		}break;
		case V4l2_SET_RGB444:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 data;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&data);
			vsc_set_rgb444(flag,(UINT8)win,&data);
		}break;
		case V4l2_SET_HDR_TYPE:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 data;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&data);
			printk("[V4l2_SET_HDR_TYPE] %d %d %d %d\n",funcnum,flag,win,data);
			vsc_set_hdr_type(flag,(UINT8)win,&data);
			printk("[V4l2_SET_HDR_TYPE] hdr_type : %d\n",data);
		}break;
		case V4l2_SET_REG_ACTWIN:
		{
			BOOLEAN flag;
			UINT32 win;
			sscanf(command,"%d %d %d\n",&funcnum,&flag,&win);
			{
				extern int vsc_bbd_simpletest(BOOLEAN flag, unsigned char wid);
				vsc_bbd_simpletest(flag,(UINT8)win);
			}
		}break;
		case V4l2_SET_DBG_ACTWIN:
		{
			BOOLEAN flag;
			SINT32 data;
			sscanf(command,"%d %d %d\n",&funcnum,&flag,&data);
			if (!flag)	printk("getdbglevel : %d\n",vsc_bbd_getdbglevel());
			else		vsc_bbd_setdbglevel(data);
		}break;
		case V4l2_SET_SWITCH_MCU:
		{
			int id;
			sscanf(command,"%d %d\n",&funcnum,&id);
			v4l2_vsc_switchmcu(id);
		}break;
		case V4L2_SET_FREEZE:
		{
			BOOLEAN flag;
			UINT32 win;
			SINT32 data;
			sscanf(command,"%d %d %d %d\n",&funcnum,&flag,&win,&data);
			vsc_set_freeze(flag,(UINT8)win,&data);
		}break;
		case V4l2_SET_RUNCOMMAND:
		{
			printk("not support(see command)\n");
		}break;
		case V4l2_SET_POST_EVENT:
		{
			printk("not support\n");
		}break;
		case V4l2_SET_FW_DL_TEST:
		{
#if 0	//not used
			int ret;
			BOOLEAN flag;
			char buf[64];
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			mm_segment_t old_fs;
#endif
			#define FW_BIN	"/var/firmware/pqe_fw.bin"

			sscanf(command,"%d %d\n",&funcnum,&flag);

			if (flag == 0)
			{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
			    set_fs(KERNEL_DS);
#else
			    set_fs(get_ds());
#endif
#endif
				de_filp = filp_open(FW_BIN, O_RDONLY, 0);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			    set_fs(old_fs);
#endif
				//if (filp < 0)	break;
				printk("filp_open : %p(%d), IS_ERR(filp) : %d\n",de_filp,(int)de_filp,(int)IS_ERR(de_filp));
			}
			else if (flag == 1)
			{
				printk("vfs_llseek SEEK_CUR : %d\n",(int)vfs_llseek(de_filp, 0, SEEK_CUR));
				printk("vfs_llseek SEEK_END : %d\n",(int)vfs_llseek(de_filp, 0, SEEK_END));
				fw_size = vfs_llseek(de_filp, 0, SEEK_END);
				printk("fw_size : %d\n",fw_size);
				printk("vfs_llseek SEEK_SET : %d\n",(int)vfs_llseek(de_filp, 0, SEEK_SET));
			}
			else if (flag == 2)
			{
		    	//filp->f_pos = 0;
		    	printk("filp->f_pos:%d\n", (int)de_filp->f_pos);
				//printk("file(%s) size=%d\n", FW_BIN, filp->f_dentry->d_inode->i_size);
			}
			else if (flag == 3)
			{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
			    set_fs(KERNEL_DS);
#else
			    set_fs(get_ds());
#endif
#endif
				de_filp->f_pos = 0;
				ret = kernel_read(de_filp, buf, sizeof(buf), &de_filp->f_pos);//vfs_read(legacy)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			    set_fs(old_fs);
#endif
		    	printk("kernel_read() ret:%d\n",ret);
				//if (ret < 0)	break;
				printk("buf(%d):%s\n",sizeof(buf),buf);
			}
			else if (flag == 4)
			{
				LX_DE_FW_DWLD_T de_fw_opt;
				de_fw_opt.inx = 3;
				de_fw_opt.cfg = DE_FW_CFG_DOWNLOAD_HEADER;
				de_fw_opt.size = fw_size;
				do {
					de_fw_opt.pData = (char *)kmalloc(fw_size,GFP_KERNEL);
					if (!de_fw_opt.pData)	{printk("kmalloc fail\n");break;}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
				    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				    set_fs(KERNEL_DS);
#else
				    set_fs(get_ds());
#endif
#endif
					de_filp->f_pos = 0;
					ret = kernel_read(de_filp, de_fw_opt.pData, fw_size, &de_filp->f_pos);//vfs_read(legacy)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
				    set_fs(old_fs);
#endif
					// de firmware download
					ret = resource_mgr_ioctl(DE_IOW_FW_DOWNLOAD,(unsigned long)&de_fw_opt,1);
					printk("DE_IOW_FW_DOWNLOAD done\n");
				} while(0);
				if (de_fw_opt.pData)	kfree(de_fw_opt.pData);
			}
			else if (flag == 5)
			{
			    filp_close(de_filp, NULL);  /* filp_close(filp, current->files) ?  */
			    /* restore kernel memory setting */
				printk("filp_close\n");
			}
#endif
		}break;
		case V4l2_SET_FOPEN_TEST:
		{
			char s0[30];
			int flags = 0, mode = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			mm_segment_t old_fs;
#endif
			struct file *test_filp = NULL;
			sscanf(command,"%d %s %d %d\n",&funcnum,s0,&flags,&mode);
			printk("open:%s %d %d\n",s0,flags,mode);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
			set_fs(KERNEL_DS);
#else
			set_fs(get_ds());
#endif
#endif
			//flags : O_RDONLY:0, O_WRONLY:1, O_RDWR:2, O_CREAT:100
			//mode : 644
			test_filp = filp_open(s0, flags, mode);//O_RDWR|O_CREAT
			if (IS_ERR(test_filp))
			{
				printk("filp_open fail(%p)\n",test_filp);
			}
			else
			{
				printk("filp_open ok(%p)\n",test_filp);
				filp_close(test_filp, NULL);
				printk("close:%s %d %d\n",s0,flags,mode);
			}
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
			set_fs(old_fs);
#endif
		}break;
		case V4l2_SET_FWIPC_TEST:
		{
			int flag;
			unsigned int data;
			sscanf(command,"%d %d %d\n",&funcnum,&flag,&data);
			if (flag==0)
			{
				ipc_hal_trace(data);
			}
			else if (flag == 1)
			{
				ipc_hal_restore();
			}
		}break;
		case V4L2_SET_ORBIT:
		{
			BOOLEAN type;
			int win;
			struct v4l2_ext_vsc_orbit_window p;
			UINT32 osd_input_x,osd_input_y,osd_input_w, osd_input_h,vid_input_x, vid_input_y, vid_input_w, vid_input_h,osd_output_x,osd_output_y,osd_output_w,osd_output_h,vid_output_x,vid_output_y,vid_output_w,vid_output_h;
			vid_output_x = vid_output_y = vid_output_w = vid_output_h = 0;
			sscanf(command,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %hd %hd %hd %hd\n",&funcnum,&type,&win,\
				&osd_input_x,&osd_input_y,&osd_input_w,&osd_input_h,\
				&vid_input_x,&vid_input_y,&vid_input_w,&vid_input_h,\
				&osd_output_x,&osd_output_y,&osd_output_w,&osd_output_h,\
				&p.video_output.x,&p.video_output.y,&p.video_output.w,&p.video_output.h);
			p.osd_input.x = (short unsigned int)osd_input_x;
			p.osd_input.y = (short unsigned int)osd_input_y;
			p.osd_input.w = (short unsigned int)osd_input_w;
			p.osd_input.h = (short unsigned int)osd_input_h;
			p.video_input.x = (short unsigned int)vid_input_x;
			p.video_input.y = (short unsigned int)vid_input_y;
			p.video_input.w = (short unsigned int)vid_input_w;
			p.video_input.h = (short unsigned int)vid_input_h;
			p.osd_output.x  = (short unsigned int)osd_output_x;
			p.osd_output.y  = (short unsigned int)osd_output_y;
			p.osd_output.w  = (short unsigned int)osd_output_w;
			p.osd_output.h  = (short unsigned int)osd_output_h;
			p.video_output.x = (short unsigned int)vid_output_x;
			p.video_output.y = (short unsigned int)vid_output_y;
			p.video_output.w = (short unsigned int)vid_output_w;
			p.video_output.h = (short unsigned int)vid_output_h;
			if(type==0)
				vsc_set_orbit_window(1,win,&p);
			else
				vsc_set_orbit_move(1,win,(struct v4l2_ext_vsc_orbit_move *)(&p));
		}break;
		case V4L2_SET_ORBIT_POLICY:
		{
			int win=0, ret;
			struct v4l2_ext_vsc_orbit_policy param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_orbit_policy));
			ret = vsc_set_orbit_policy(1, win, &param);
		}break;
		case V4L2_SET_IPMODE:
		{
			UINT32 param;
			sscanf(command,"%d %d\n",&funcnum,&param);
			vsc_set_ipc_mode(1,0,&param);
		}break;
		case V4L2_SET_IPC_TEST:
		{
			UINT32 param1, param2;
			UINT32 mute = 0, sub_mode = 0;
			sscanf(command,"%d %d %d\n",&funcnum,&param1,&param2);

			if(param1==0) {
			do {
				vsc_set_mute(1,0,&mute);
				vsc_set_sub_occupy(1, 0, &sub_mode);
				} while(param2--);
			}
			else if(param1==1) {
				UINT32 i, count = 100;
				UINT32 *int_intr_event, *int_intr_status, *int_intr_clear;
				int_intr_event  = ioremap(0xCC080018, sizeof(UINT32));
				int_intr_status = ioremap(0xCC080020, sizeof(UINT32));
				int_intr_clear  = ioremap(0xCC080024, sizeof(UINT32));

				for (i=0; i<param2; i++)
				{
					count = 100;
					*int_intr_event = 0x00200000;
					do {
						if(count<1)
						{
							DE_NOTI("[%6u/%6u] EVENT : REG_MCU_INT_INTR_STATUS:%08x\n", i, param2,  *int_intr_status);
						}
						if ((*int_intr_status & 0x00200000)) break;
					} while(count--);
					// Clear IPC interrupt
					*int_intr_clear = 0x00200000;
					count = 100;
					do {
						if(count<1)
						{
							DE_NOTI("[%6u/%6u] CLEAR : REG_MCU_INT_INTR_STATUS:%08x\n", i, param2,  *int_intr_status);
						}
						if (!(*int_intr_status & 0x00200000)) break;
					} while(count--);
				}
				DE_NOTI("[%6u/%6u] OK\n", i, param2);
				iounmap(int_intr_event);
				iounmap(int_intr_status);
				iounmap(int_intr_clear);
			}
			else if(param1==2) {
				UINT32 i;
				UINT32 *apb_tout_cnt;
				apb_tout_cnt  = ioremap(0xCC08008C, sizeof(UINT32));
				i = param2;
				do {
					*apb_tout_cnt = i;
					if(i != *apb_tout_cnt)
					{
						DE_NOTI("[%6u/%6u] WARN : apb_tout_cnt:%6u\n", i, param2,	*apb_tout_cnt);
					}
				} while(i--);
				DE_NOTI("[%6u/%6u] OK\n", ++i, param2);
				iounmap(apb_tout_cnt);
			}
			else if(param1==3) {
				UINT32 i;
				UINT32 *sys_veri_2;
				sys_veri_2 = ioremap(0xCC8C0D08, sizeof(UINT32));
				i = param2;
				do {
					*sys_veri_2   = i;
					if(i != *sys_veri_2)
					{
						DE_NOTI("[%6u/%6u] WARN : sys_veri_2:%6u\n", i, param2,	*sys_veri_2);
					}
				} while(i--);
				DE_NOTI("[%6u/%6u] OK\n", ++i, param2);
				iounmap(sys_veri_2);
		}
			else if(param1==4) {
				int ret;
				LX_DE_FIRMWARE_INFO_T fw_info;
				UINT32 i = 0, error = 0;
				do {
					fw_info.ipc_count = i++;  // set ipc_count
					ret = resource_mgr_ioctl(DE_IOR_GET_FIRMWARE_INFO,(unsigned long)&fw_info,1);
					// FW returns ipc_count+1
					if(i != fw_info.ipc_count) {
						error++;
						DE_ERROR("[SET:%6u / GET:%6u] ", i, fw_info.ipc_count);
						break;
					}
				} while(i < param2);
				DE_NOTI("err_count [%6u/%6u] \n", error, param2);
			}
		}break;
default:
		{
			DE_NOTI("Function number is wrong\n");
		}break;
	}
}
#if 0	//not used
void __V4l2_PROC_Help(void)
{
	printk("Hal functions numbers and examples to call V4L2 API's are below\n");
	printk("0:V4l2_SET_INPUT -> vsc_set_input: echo 0 1(flag) 0(win) 1(src) 0(idx) 0(attr) 1(disp)\n");
	printk("1:V4l2_SET_MUTE -> vsc_set_mute command:echo 1 1(flag) 0(wid) 2(color)\n");
	printk("2:V4l2_SET_WININFO -> echo 2 1 0(win) 0 0 3840 2160 0 0 3840 2160\n");
	printk("11:V4l2_SET_HDR_TYPE -> echo 11 1 0(win) 0(sdr,h10,dovi,hlg,tech,ll) \n");
	printk("12:V4l2_SET_REG_ACTWIN -> echo 12 1(reg) 0(win) or echo 12 0(unreg) 0(win)\n");
	printk("13:V4l2_SET_DBG_ACTWIN -> echo 13 1(set) 2(dbg) or echo 12 0(get) 0(na)\n");
	printk("14:V4l2_SET_SWITCH_MCU -> echo 14 0(id) > ./v4l2_vsc_debug_func\n");
	printk("16:V4l2_SET_POST_EVENT -> echo 16 0(wid) 0(event type) > ./v4l2_vsc_debug_func\n");
	printk("17:V4l2_SET_FW_DL_TEST -> echo 17 > ./v4l2_vsc_debug_func\n");
	printk("18:V4l2_SET_FWDOWNLOAD -> echo 18 0 > ./v4l2_vsc_debug_func\n");
	printk("19:V4l2_SET_FOPEN_TEST -> echo 19 [filename] [flags] [mode] > ./v4l2_vsc_debug_func\n");
	printk("20:V4l2_SET_FWIPC_TEST -> echo 20 0 3 > ./v4l2_vsc_debug_func\n");
	printk("Example:\n");
	printk("echo 0 1 0 1 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func which will call hal_vsc_hwrap_setwinblank\n");
	printk("echo 7 1 0 1 > /proc/lg/de/v4l2_vsc_debug_func : ipp pat on(7 1 0 0 :off), 0(ipp)~5(pe0)\n");
	printk("echo 11 1 0 0 > ./v4l2_vsc_debug_func : sdr\n");
	printk("echo 11 1 0 1 > ./v4l2_vsc_debug_func : h10\n");
	printk("echo 11 1 0 2 > ./v4l2_vsc_debug_func : dovi\n");
	printk("echo 11 1 0 3 > ./v4l2_vsc_debug_func : hlg\n");
	printk("echo 11 1 0 4 > ./v4l2_vsc_debug_func : tech\n");
	printk("echo 12 1 0 > ./v4l2_vsc_debug_func : actwin0 register\n");
	printk("echo 12 0 0 > ./v4l2_vsc_debug_func : actwin0 unregister\n");
	printk("echo 12 1 1 > ./v4l2_vsc_debug_func : actwin1 register\n");
	printk("echo 12 0 1 > ./v4l2_vsc_debug_func : actwin1 unregister\n");
	printk("echo 13 1 0 > ./v4l2_vsc_debug_func : actwin dbg off\n");
	printk("echo 13 1 1 > ./v4l2_vsc_debug_func : actwin0 dbg on\n");
	printk("echo 13 1 2 > ./v4l2_vsc_debug_func : actwin1 dbg on\n");
	printk("echo 16 1 1 > ./v4l2_vsc_debug_func : actwin\n");
	printk("echo 18 2 > ./v4l2_vsc_debug_func : get dl_fw dbg\n");
	printk("echo 21 1   > ./v4l2_vsc_debug_func : 0/1 off/on,  test VENC on\n");
	printk("FW DBG:\n");
	printk("uart mcu0 : echo 0 > /proc/lg/de/switch_mcu\n");
	printk("uart mcu1 : echo 1 > /proc/lg/de/switch_mcu\n");
	printk("bootloader: set dispopts pqefw;save\n");
	printk("fw0(main) : /var/firmware/pqefw0.bin\n");
	printk("fw1(dnn)  : /var/firmware/pqefw1.bin\n");
	printk("fw2(obd)  : /var/firmware/pqefw2.bin\n");
	printk("fw3(lne2k): /var/firmware/pqefw3.bin\n");
	printk("fw4(lne4k): /var/firmware/pqefw4.bin\n");
}
#endif
/** @} */

