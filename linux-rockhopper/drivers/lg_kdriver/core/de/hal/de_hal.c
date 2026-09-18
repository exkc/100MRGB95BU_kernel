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
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2010.03.08
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------
 *	 Control Constants
 *--------------------------------------------------------------------------*/
#undef USE_KDRV_CODES_FOR_L9

/*----------------------------------------------------------------------------
 *	 File Inclusions
 *--------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "base_types.h"
#include "base_device.h"
#include "os_util.h"

#include "de_model.h"
#include "de_kapi.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "de_hal_def.h"
#include "de_hal.h"
#include "mcu/de_int_def.h"
#include "mcu/de_ipc_def.h"


#ifdef USE_KDRV_CODES_FOR_L18
#include "l18/de/de_fw_l18.h"
#include "l18/de/de_reg_l18.h"
#include "l18/de/de_ipc_l18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M17
#include "m17/de/de_fw_m17.h"
#include "m17/de/de_reg_m17.h"
#include "m17/de/de_ipc_m17.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M19
#include "m19/de/de_fw_m19.h"
#include "m19/de/de_reg_m19.h"
#include "m19/de/de_ipc_m19.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O18
#include "o18/de/de_fw_o18.h"
#include "o18/de/de_reg_o18.h"
#include "o18/de/de_ipc_o18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O20
#include "o20/de/de_fw_o20.h"
#include "o20/de/de_reg_o20.h"
#include "o20/de/de_ipc_o20.h"
#endif
#ifdef USE_KDRV_CODES_FOR_E60
#include "e60/de/de_fw_e60.h"
#include "e60/de/de_reg_e60.h"
#include "e60/de/de_ipc_e60.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O22
#include "o22/de/de_fw_o22.h"
#include "o22/de/de_reg_o22.h"
#include "o22/de/de_ipc_o22.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M23
#include "m23/de/de_fw_m23.h"
#include "m23/de/de_reg_m23.h"
#include "m23/de/de_ipc_m23.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O24
#include "o24/de/de_reg_o24.h"
#include "o24/de/de_ipc_o24.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O26
#include "o26/de/de_reg_o26.h"
#include "o26/de/de_ipc_o26.h"
#endif

/*----------------------------------------------------------------------------
 *	 Constant Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 Macro Definitions
 *--------------------------------------------------------------------------*/
#define CHECK_REG_NULL(fp) {if(fp == NULL || g_chip_id < 0)\
							{DE_ERROR("%s is not supported in this chip.\n",#fp); \
							return RET_ERROR;}}
#define GET_ID() g_chip_id

/*----------------------------------------------------------------------------
 *	 Type Definitions
 *--------------------------------------------------------------------------*/
typedef struct {
	int (*init)(LX_DE_PANEL_TYPE_T *pstParams);
	int (*set_frame_rate)(DE_DPLL_CLK_T dclk);
	int (*set_bg_color)(LX_DE_COLOR_T *pBackColor);
	int (*set_win_blank)(LX_DE_SET_WIN_BLANK_T *pWinBlank);
	int (*get_mvi_colorimetry)(LX_DE_MVI_COLORIMETRY_T *pstParams);
	int (*set_cvi_src_type)(LX_DE_CVI_SRC_TYPE_T *pstParams);
	int (*set_uart4mcu)(int bUart4MCU);
	int (*get_fw_max_num)(UINT32 *pMaxNum);
	int (*download_fw)(LX_DE_FW_DWLD_T *pstParams);
	int (*download_fw_bin)(void);
	int (*download_fw_head)(LX_DE_FW_DWLD_T *pstParams);
	int (*set_cvi_fir)(LX_DE_CVI_FIR_T *pstParams);
	int (*set_cvi_tpg)(LX_DE_CVI_TPG_T *pstParams);
	int (*set_cvi_csample)(LX_DE_CSAMPLE_MODE_T *pstParams);
	int (*set_vcs)(LX_DE_VCS_IPC_T *pstParams);
	int (*reset_de)(BOOLEAN bReset);
	int (*init_phy2virt)(void);
	int (*free_phy2virt)(void);
	int (*init_gpio)(void);
	int (*init_hdmi)(void);
	int (*init_lvds)(void);
	int (*init_misc)(void);
	int (*init_osd)(void);
	BOOLEAN (*is_alive_ipc)(void);
	int (*write_reg)(void *addr, UINT32 value);
	UINT32 (*read_reg)(void *addr);
	int (*set_cvi_buffer)(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
	int (*set_cvi_rw)(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams,\
						LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
	int (*sel_multiwinsrc)(LX_DE_MULTI_WIN_SRC_T *pstParams);
	int (*set_scart_rbg_bypass)(int enable);
	int (*set_ud_mode)(BOOLEAN *pstParams);
	int (*set_debug)(LX_DE_SET_DBG_T *pstParams);
	int (*get_debug)(LX_DE_SET_DBG_T *pstParams);
	int (*set_win_port_src)(LX_DE_INPUT_CFG_T *pstParams);
	int (*set_if_config)(LX_DE_IF_CONFIG_T *pstParams);
	int (*get_sys_status)(LX_DE_SYS_STATUS_T *pstParams);
	int (*get_src_status)(LX_DE_SRC_STATUS_T *pstParams);
	int (*set_operation)(LX_DE_OPERATION_CTRL_T *pstParams);
	int (*set_operation_sub)(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
	int (*set_capture)(LX_DE_CAPTURE_CTRL_T *pstParams);
	BOOLEAN (*check_irq4vsync)(void);
	int (*switch_uart0)(int whichUart);
	int (*set_ttx)(VIDEO_TTX_PACK_T *pTtxPack);
	int (*set_vtm)(LX_DE_VTM_FRAME_INFO_T *pstParams);
	int (*get_vtm)(LX_DE_VTM_FRAME_INFO_T *pstParams);
	int (*get_fir)(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir); 
	int (*verify_fw)(void);
	int (*set_seamless)(LX_DE_RECT_T *pstParams);
	int (*set_hdmi_port)(LX_DE_HDMIPORT_T *pstParams);
	int (*get_capa)(LX_DE_CAPACITY_T *pstParams);
	int (*get_local_mute)(UINT32 *pstParams);
	int (*set_multi_win)(UINT32 *pstParams);
	int (*set_hdmitx_clk)(LX_DE_HDMITX_OUTPUT_INFO_T *pstParams);	
	int (*set_gcp_mode)(LX_DE_GCP_INFO_T *pstParams);
	int (*set_mem_by_cma)(char* mem_name);
	int (*get_mem_from_cma)(char *mem_name, int count, void *buf_info, BOOLEAN flag);
	int (*set_low_delay_clock)(UINT32 *pstParams);
	int (*dump_status)(void);
	int (*get_shared_mem)(UINT32 page_offset, UINT32 **mem_info);
	int (*get_fpp_info)(UINT32* start_address);
	int (*get_mem_info)(LX_DE_MEM_SYS_INFO_T *pstParams);
	int (*get_dnn_result)(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
	int (*set_sys_time)(UINT32 *sec, UINT32 *msec, UINT32 *usec);
	int (*get_time_diff)(UINT32 *diff);
	int (*get_video_delay)(LX_DE_VIDEO_DELAY_INFO_MEM_T *delay);
	int (*view_info)(int type);
	int (*get_init_data)(LX_DE_IPC_INIT_DATA_T *pstParams);
	int (*get_hist_svp_buffer)(UINT32 *start, UINT32 * end);
} DE_REG_CB_T;

DE_REG_CB_T gfn_all[7];
static int g_chip_id = 0;

/*----------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 External Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 global Functions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 global Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 Static Variables
 *--------------------------------------------------------------------------*/
static DE_DPLL_CLK_T sDeDpllClk_1920[] = {
	DCLK_148_5	  ,
	DCLK_148_3516 ,
};

static DE_DPLL_CLK_T sDeDpllClk_1366[] = {
	DCLK_81 ,
	DCLK_81 ,
};

static DE_DPLL_CLK_T sDeDpllClk_1024[] = {
	DCLK_65 ,
	DCLK_65 ,
};

static DE_DPLL_CLK_T sDeDpllClk_3840[] = {
	DCLK_148_5	  ,
	DCLK_148_3516 ,
};

static DE_DPLL_CLK_T sDeDpllClk_480[] = {
	DCLK_54 ,
	DCLK_54 ,
};

static DE_PANEL_SET_T sDePanelSet[] = {
	{ LX_PANEL_TYPE_1920 , sDeDpllClk_1920 },
	{ LX_PANEL_TYPE_1366 , sDeDpllClk_1366 },
	{ LX_PANEL_TYPE_1024 , sDeDpllClk_1024 },
	{ LX_PANEL_TYPE_1365 , sDeDpllClk_1366 },
	{ LX_PANEL_TYPE_3840 , sDeDpllClk_3840 },
	{ LX_PANEL_TYPE_1280 , sDeDpllClk_1920 },
	{ LX_PANEL_TYPE_720  , sDeDpllClk_480  },
	{ LX_PANEL_TYPE_576  , sDeDpllClk_480  }
};

static LX_DE_FR_RATE_T sDeFrRate = { FALSE, 60 };
static LX_DE_PANEL_TYPE_T sDePanelType = LX_PANEL_TYPE_1920;

/*============================================================================
 *	 Implementation Group
 *==========================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief select chip for call-back function 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_Select_Chip(void)
{
#define REG_FN gfn_all[g_chip_id]

	int ret = RET_OK;

	REG_FN.get_init_data = NULL;

#ifdef USE_KDRV_CODES_FOR_O18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O18) ) {
		g_chip_id = 3;
		REG_FN.init                  = DE_REG_O18_Init;
		REG_FN.set_frame_rate        = DE_REG_O18_SetFrRate;
		REG_FN.set_bg_color          = DE_REG_O18_SetBgColor;
		REG_FN.set_win_blank         = DE_REG_O18_SetWinBlank;
		REG_FN.get_mvi_colorimetry   = NULL;
		REG_FN.set_cvi_src_type      = DE_REG_O18_SetCviSrcType;
		REG_FN.set_uart4mcu          = DE_REG_O18_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = NULL;
		REG_FN.download_fw           = DE_REG_O18_FW_Download;
		REG_FN.download_fw_bin       = DE_FW_O18_DownloadFromBin;
		REG_FN.download_fw_head      = DE_FW_O18_DownloadFromHead;
		REG_FN.set_cvi_fir           = DE_REG_O18_SetCviFir;
		REG_FN.set_cvi_tpg           = DE_REG_O18_SetCviTpg;
		REG_FN.set_cvi_csample       = DE_REG_O18_SetCviCsampleMode;
		REG_FN.set_vcs               = DE_REG_O18_SetVcs;
		REG_FN.reset_de              = DE_REG_O18_ResetDE;
		REG_FN.init_phy2virt         = DE_REG_O18_InitPHY2VIRT;
		REG_FN.free_phy2virt         = DE_REG_O18_FreePHY2VIRT;
		REG_FN.init_gpio             = DE_REG_O18_GPIO_Init;
		REG_FN.init_hdmi             = DE_REG_O18_HDMI_Init;
		REG_FN.init_lvds             = DE_REG_O18_LVDS_Init;
		REG_FN.init_misc             = DE_REG_O18_MISC_Init;
		REG_FN.init_osd              = DE_REG_O18_OSD_Init;
		REG_FN.is_alive_ipc          = DE_REG_O18_IPCisAlive;
		REG_FN.write_reg             = DE_REG_O18_WD;
		REG_FN.read_reg              = DE_REG_O18_RD;
		REG_FN.set_cvi_buffer        = DE_REG_O18_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw            = DE_REG_O18_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc       = DE_REG_O18_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode           = DE_REG_O18_SetUdMode;
		REG_FN.set_debug             = DE_REG_O18_SetDebug;
		REG_FN.get_debug             = NULL;
		REG_FN.set_win_port_src      = DE_REG_O18_SetWinPortSrc;
		REG_FN.set_if_config         = DE_REG_O18_SetInterfaceConfig;
		REG_FN.get_sys_status        = DE_REG_O18_GetSystemStatus;
		REG_FN.get_src_status        = DE_REG_O18_GetSourceStatus;
		REG_FN.set_operation         = DE_REG_O18_SetOperation;
		REG_FN.set_operation_sub     = DE_REG_O18_SetSubOperation;
		REG_FN.set_capture           = NULL;
		REG_FN.switch_uart0          = DE_REG_O18_Uart0_Switch;
		REG_FN.set_ttx               = NULL;
		REG_FN.set_vtm               = DE_REG_O18_SetVTM;
		REG_FN.get_vtm               = DE_REG_O18_GetVTM;
		REG_FN.get_fir               = DE_REG_O18_GetFIR;
		REG_FN.verify_fw             = DE_FW_O18_Verify;
		REG_FN.set_hdmi_port         = DE_REG_O18_SetHdmiPort;
		REG_FN.get_capa              = DE_REG_O18_GetCapacity;
		REG_FN.get_local_mute        = DE_REG_O18_GetLocalMute;
		REG_FN.set_multi_win         = DE_REG_O18_SetMultiWin;
		REG_FN.set_hdmitx_clk        =  NULL;
		REG_FN.set_gcp_mode          = DE_REG_O18_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma        = DE_REG_O18_SetMemByCma;
		REG_FN.get_mem_from_cma      = DE_REG_O18_GetMemFromCma;
		REG_FN.set_low_delay_clock   = DE_REG_O18_SetLowDelayClock;
		REG_FN.dump_status           = DE_REG_O18_FW_DumpStatus;
		REG_FN.get_shared_mem        = DE_REG_O18_GetSharedMem;
		REG_FN.get_fpp_info          = DE_REG_O18_GetFPPInfo;
		REG_FN.get_mem_info          = DE_REG_O18_GetMEMInfo;
		REG_FN.get_dnn_result        = DE_REG_O18_GetDNNStatus;
		REG_FN.get_video_delay       = DE_REG_O18_GetVideoDelay;
		REG_FN.view_info             = NULL;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) ) {
		g_chip_id = 2;
		REG_FN.init                  = DE_REG_L18_Init;
		REG_FN.set_frame_rate        = DE_REG_L18_SetFrRate;
		REG_FN.set_bg_color          = DE_REG_L18_SetBgColor;
		REG_FN.set_win_blank         = DE_REG_L18_SetWinBlank;
		REG_FN.get_mvi_colorimetry   = NULL;
		REG_FN.set_cvi_src_type      = DE_REG_L18_SetCviSrcType;
		REG_FN.set_uart4mcu          = DE_REG_L18_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = NULL;
		REG_FN.download_fw           = DE_REG_L18_FW_Download;
		REG_FN.download_fw_bin       = DE_FW_L18_DownloadFromBin;
		REG_FN.download_fw_head      = NULL;
		REG_FN.set_cvi_fir           = DE_REG_L18_SetCviFir;
		REG_FN.set_cvi_tpg           = DE_REG_L18_SetCviTpg;
		REG_FN.set_cvi_csample       = DE_REG_L18_SetCviCsampleMode;
		REG_FN.set_vcs               = NULL;
		REG_FN.reset_de              = DE_REG_L18_ResetDE;
		REG_FN.init_phy2virt         = DE_REG_L18_InitPHY2VIRT;
		REG_FN.free_phy2virt         = DE_REG_L18_FreePHY2VIRT;
		REG_FN.init_gpio             = DE_REG_L18_GPIO_Init;
		REG_FN.init_hdmi             = DE_REG_L18_HDMI_Init;
		REG_FN.init_lvds             = DE_REG_L18_LVDS_Init;
		REG_FN.init_misc             = DE_REG_L18_MISC_Init;
		REG_FN.init_osd              = DE_REG_L18_OSD_Init;
		REG_FN.is_alive_ipc          = DE_REG_L18_IPCisAlive;
		REG_FN.write_reg             = DE_REG_L18_WD;
		REG_FN.read_reg              = DE_REG_L18_RD;
		REG_FN.set_cvi_buffer        = DE_REG_L18_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw            = DE_REG_L18_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc       = NULL;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode           = NULL;
		REG_FN.set_debug             = DE_REG_L18_SetDebug;
		REG_FN.get_debug             = NULL;
		REG_FN.set_win_port_src      = DE_REG_L18_SetWinPortSrc;
		REG_FN.set_if_config         = DE_REG_L18_SetInterfaceConfig;
		REG_FN.get_sys_status        = DE_REG_L18_GetSystemStatus;
		REG_FN.get_src_status        = DE_REG_L18_GetSourceStatus;
		REG_FN.set_operation         = DE_REG_L18_SetOperation;
		REG_FN.set_operation_sub     = NULL;
		REG_FN.set_capture           = NULL;
		REG_FN.switch_uart0          = DE_REG_L18_Uart0_Switch;
		REG_FN.set_ttx               = NULL;
		REG_FN.set_vtm               = NULL;
		REG_FN.get_vtm               = NULL;
		REG_FN.get_fir               = DE_REG_L18_GetFIR;
		REG_FN.verify_fw             = DE_FW_L18_Verify;
		REG_FN.set_hdmi_port         = DE_REG_L18_SetHdmiPort;
		REG_FN.get_capa              = DE_REG_L18_GetCapacity;
		REG_FN.get_local_mute        = DE_REG_L18_GetLocalMute;
		REG_FN.set_multi_win         = NULL;
		REG_FN.set_hdmitx_clk        = NULL;
		REG_FN.set_gcp_mode          = NULL;
		REG_FN.set_mem_by_cma        = DE_REG_L18_SetMemByCma;
		REG_FN.get_mem_from_cma      = DE_REG_L18_GetMemFromCma;
		REG_FN.set_low_delay_clock   = DE_REG_L18_SetLowDelayClock;
		REG_FN.dump_status           = DE_REG_L18_FW_DumpStatus;
		REG_FN.view_info             = NULL;
	} else
#endif

#ifdef USE_KDRV_CODES_FOR_M17
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) ) {
		g_chip_id = 1;
		REG_FN.init                  = DE_REG_M17_Init;
		REG_FN.set_frame_rate        = DE_REG_M17_SetFrRate;
		REG_FN.set_bg_color          = DE_REG_M17_SetBgColor;
		REG_FN.set_win_blank         = DE_REG_M17_SetWinBlank;
		REG_FN.get_mvi_colorimetry   = NULL;
		REG_FN.set_cvi_src_type      = DE_REG_M17_SetCviSrcType;
		REG_FN.set_uart4mcu          = DE_REG_M17_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = NULL;
		REG_FN.download_fw           = DE_REG_M17_FW_Download;
		REG_FN.download_fw_bin       = DE_FW_M17_DownloadFromBin;
		REG_FN.download_fw_head      = NULL;
		REG_FN.set_cvi_fir           = DE_REG_M17_SetCviFir;
		REG_FN.set_cvi_tpg           = DE_REG_M17_SetCviTpg;
		REG_FN.set_cvi_csample       = DE_REG_M17_SetCviCsampleMode;
		REG_FN.set_vcs               = DE_REG_M17_SetVcs;
		REG_FN.reset_de              = DE_REG_M17_ResetDE;
		REG_FN.init_phy2virt         = DE_REG_M17_InitPHY2VIRT;
		REG_FN.free_phy2virt         = DE_REG_M17_FreePHY2VIRT;
		REG_FN.init_gpio             = DE_REG_M17_GPIO_Init;
		REG_FN.init_hdmi             = DE_REG_M17_HDMI_Init;
		REG_FN.init_lvds             = DE_REG_M17_LVDS_Init;
		REG_FN.init_misc             = DE_REG_M17_MISC_Init;
		REG_FN.init_osd              = DE_REG_M17_OSD_Init;
		REG_FN.is_alive_ipc          = DE_REG_M17_IPCisAlive;
		REG_FN.write_reg             = DE_REG_M17_WD;
		REG_FN.read_reg              = DE_REG_M17_RD;
		REG_FN.set_cvi_buffer        = DE_REG_M17_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw            = DE_REG_M17_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc       = DE_REG_M17_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode           = DE_REG_M17_SetUdMode;
		REG_FN.set_debug             = DE_REG_M17_SetDebug;
		REG_FN.get_debug             = NULL;
		REG_FN.set_win_port_src      = DE_REG_M17_SetWinPortSrc;
		REG_FN.set_if_config         = DE_REG_M17_SetInterfaceConfig;
		REG_FN.get_sys_status        = DE_REG_M17_GetSystemStatus;
		REG_FN.get_src_status        = DE_REG_M17_GetSourceStatus;
		REG_FN.set_operation         = DE_REG_M17_SetOperation;
		REG_FN.set_operation_sub     = DE_REG_M17_SetSubOperation;
		REG_FN.set_capture           = NULL;
		REG_FN.switch_uart0          = DE_REG_M17_Uart0_Switch;
		REG_FN.set_ttx               = NULL;
		REG_FN.set_vtm               = DE_REG_M17_SetVTM;
		REG_FN.get_vtm               = DE_REG_M17_GetVTM;
		REG_FN.get_fir               = DE_REG_M17_GetFIR;
		REG_FN.verify_fw             = DE_FW_M17_Verify;
		REG_FN.set_hdmi_port         = DE_REG_M17_SetHdmiPort;
		REG_FN.get_capa              = DE_REG_M17_GetCapacity;
		REG_FN.get_local_mute        = DE_REG_M17_GetLocalMute;
		REG_FN.set_multi_win         = DE_REG_M17_SetMultiWin;
		REG_FN.set_hdmitx_clk        =  NULL;
		REG_FN.set_gcp_mode          = DE_REG_M17_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma        = DE_REG_M17_SetMemByCma;
		REG_FN.get_mem_from_cma      = DE_REG_M17_GetMemFromCma;
		REG_FN.set_low_delay_clock   = DE_REG_M17_SetLowDelayClock;
		REG_FN.dump_status           = DE_REG_M17_FW_DumpStatus;
		REG_FN.get_shared_mem        = DE_REG_M17_GetSharedMem;
		REG_FN.get_fpp_info          = DE_REG_M17_GetFPPInfo;
		REG_FN.get_mem_info          = DE_REG_M17_GetMEMInfo;
		REG_FN.get_dnn_result        = DE_REG_M17_GetDNNStatus;
		REG_FN.set_sys_time          = DE_REG_M17_SetSysTime;
		REG_FN.get_time_diff         = DE_REG_M17_GetTimeDiff;
		REG_FN.get_video_delay       = DE_REG_M17_GetVideoDelay;
		REG_FN.view_info             = NULL;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_M19
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M19) ) {
		g_chip_id = 1;
		REG_FN.init                  = DE_REG_M19_Init;
		REG_FN.set_frame_rate        = DE_REG_M19_SetFrRate;
		REG_FN.set_bg_color          = DE_REG_M19_SetBgColor;
		REG_FN.set_win_blank         = DE_REG_M19_SetWinBlank;
		REG_FN.get_mvi_colorimetry   = NULL;
		REG_FN.set_cvi_src_type      = DE_REG_M19_SetCviSrcType;
		REG_FN.set_uart4mcu          = DE_REG_M19_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_M19_FW_GetMaxNum;
		REG_FN.download_fw           = DE_REG_M19_FW_Download;
		REG_FN.download_fw_bin       = DE_FW_M19_DownloadFromBin;
		REG_FN.download_fw_head      = DE_FW_M19_DownloadFromHead;
		REG_FN.set_cvi_fir           = DE_REG_M19_SetCviFir;
		REG_FN.set_cvi_tpg           = DE_REG_M19_SetCviTpg;
		REG_FN.set_cvi_csample       = DE_REG_M19_SetCviCsampleMode;
		REG_FN.set_vcs               = DE_REG_M19_SetVcs;
		REG_FN.reset_de              = DE_REG_M19_ResetDE;
		REG_FN.init_phy2virt         = DE_REG_M19_InitPHY2VIRT;
		REG_FN.free_phy2virt         = DE_REG_M19_FreePHY2VIRT;
		REG_FN.init_gpio             = DE_REG_M19_GPIO_Init;
		REG_FN.init_hdmi             = DE_REG_M19_HDMI_Init;
		REG_FN.init_lvds             = DE_REG_M19_LVDS_Init;
		REG_FN.init_misc             = DE_REG_M19_MISC_Init;
		REG_FN.init_osd              = DE_REG_M19_OSD_Init;
		REG_FN.is_alive_ipc          = DE_REG_M19_IPCisAlive;
		REG_FN.write_reg             = DE_REG_M19_WD;
		REG_FN.read_reg              = DE_REG_M19_RD;
		REG_FN.set_cvi_buffer        = DE_REG_M19_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw            = DE_REG_M19_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc       = DE_REG_M19_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode           = DE_REG_M19_SetUdMode;
		REG_FN.set_debug             = DE_REG_M19_SetDebug;
		REG_FN.get_debug             = NULL;
		REG_FN.set_win_port_src      = DE_REG_M19_SetWinPortSrc;
		REG_FN.set_if_config         = DE_REG_M19_SetInterfaceConfig;
		REG_FN.get_sys_status        = DE_REG_M19_GetSystemStatus;
		REG_FN.get_src_status        = DE_REG_M19_GetSourceStatus;
		REG_FN.set_operation         = DE_REG_M19_SetOperation;
		REG_FN.set_operation_sub     = DE_REG_M19_SetSubOperation;
		REG_FN.set_capture           = NULL;
		REG_FN.switch_uart0          = DE_REG_M19_Uart0_Switch;
		REG_FN.set_ttx               = NULL;
		REG_FN.set_vtm               = DE_REG_M19_SetVTM;
		REG_FN.get_vtm               = DE_REG_M19_GetVTM;
		REG_FN.get_fir               = DE_REG_M19_GetFIR;
		REG_FN.verify_fw             = DE_FW_M19_Verify;
		REG_FN.set_hdmi_port         = DE_REG_M19_SetHdmiPort;
		REG_FN.get_capa              = DE_REG_M19_GetCapacity;
		REG_FN.get_local_mute        = DE_REG_M19_GetLocalMute;
		REG_FN.set_multi_win         = DE_REG_M19_SetMultiWin;
		REG_FN.set_hdmitx_clk        =  NULL;
		REG_FN.set_gcp_mode          = DE_REG_M19_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma        = DE_REG_M19_SetMemByCma;
		REG_FN.get_mem_from_cma      = DE_REG_M19_GetMemFromCma;
		REG_FN.set_low_delay_clock   = DE_REG_M19_SetLowDelayClock;
		REG_FN.dump_status           = DE_REG_M19_FW_DumpStatus;
		REG_FN.get_shared_mem        = DE_REG_M19_GetSharedMem;
		REG_FN.get_fpp_info          = DE_REG_M19_GetFPPInfo;
		REG_FN.get_mem_info          = DE_REG_M19_GetMEMInfo;
		REG_FN.get_dnn_result        = DE_REG_M19_GetDNNStatus;
		REG_FN.get_video_delay       = DE_REG_M19_GetVideoDelay;
		REG_FN.view_info             = DE_REG_M19_ViewInfo;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O20
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) ) {
		g_chip_id = 4;
		REG_FN.init 				 = DE_REG_O20_Init;
		REG_FN.set_frame_rate		 = DE_REG_O20_SetFrRate;
		REG_FN.set_bg_color 		 = DE_REG_O20_SetBgColor;
		REG_FN.set_win_blank		 = DE_REG_O20_SetWinBlank;
		REG_FN.get_mvi_colorimetry	 = NULL;
		REG_FN.set_cvi_src_type 	 = DE_REG_O20_SetCviSrcType;
		REG_FN.set_uart4mcu 		 = DE_REG_O20_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_O20_FW_GetMaxNum;
		REG_FN.download_fw			 = DE_REG_O20_FW_Download;
		REG_FN.download_fw_bin		 = DE_FW_O20_DownloadFromBin;
		REG_FN.download_fw_head 	 = DE_FW_O20_DownloadFromHead;
		REG_FN.set_cvi_fir			 = DE_REG_O20_SetCviFir;
		REG_FN.set_cvi_tpg			 = DE_REG_O20_SetCviTpg;
		REG_FN.set_cvi_csample		 = DE_REG_O20_SetCviCsampleMode;
		REG_FN.set_vcs				 = DE_REG_O20_SetVcs;
		REG_FN.reset_de 			 = DE_REG_O20_ResetDE;
		REG_FN.init_phy2virt		 = DE_REG_O20_InitPHY2VIRT;
		REG_FN.free_phy2virt		 = DE_REG_O20_FreePHY2VIRT;
		REG_FN.init_gpio			 = DE_REG_O20_GPIO_Init;
		REG_FN.init_hdmi			 = DE_REG_O20_HDMI_Init;
		REG_FN.init_lvds			 = DE_REG_O20_LVDS_Init;
		REG_FN.init_misc			 = DE_REG_O20_MISC_Init;
		REG_FN.init_osd 			 = DE_REG_O20_OSD_Init;
		REG_FN.is_alive_ipc 		 = DE_REG_O20_IPCisAlive;
		REG_FN.write_reg			 = DE_REG_O20_WD;
		REG_FN.read_reg 			 = DE_REG_O20_RD;
		REG_FN.set_cvi_buffer		 = DE_REG_O20_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw			 = DE_REG_O20_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc		 = DE_REG_O20_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode			 = DE_REG_O20_SetUdMode;
		REG_FN.set_debug			 = DE_REG_O20_SetDebug;
		REG_FN.get_debug			 = NULL;
		REG_FN.set_win_port_src 	 = DE_REG_O20_SetWinPortSrc;
		REG_FN.set_if_config		 = DE_REG_O20_SetInterfaceConfig;
		REG_FN.get_sys_status		 = DE_REG_O20_GetSystemStatus;
		REG_FN.get_src_status		 = DE_REG_O20_GetSourceStatus;
		REG_FN.set_operation		 = DE_REG_O20_SetOperation;
		REG_FN.set_operation_sub	 = DE_REG_O20_SetSubOperation;
		REG_FN.set_capture			 = NULL;
		REG_FN.switch_uart0 		 = DE_REG_O20_Uart0_Switch;
		REG_FN.set_ttx				 = NULL;
		REG_FN.set_vtm				 = DE_REG_O20_SetVTM;
		REG_FN.get_vtm				 = DE_REG_O20_GetVTM;
		REG_FN.get_fir				 = DE_REG_O20_GetFIR;
		REG_FN.verify_fw			 = DE_FW_O20_Verify;
		REG_FN.set_hdmi_port		 = DE_REG_O20_SetHdmiPort;
		REG_FN.get_capa 			 = DE_REG_O20_GetCapacity;
		REG_FN.get_local_mute		 = DE_REG_O20_GetLocalMute;
		REG_FN.set_multi_win		 = DE_REG_O20_SetMultiWin;
		REG_FN.set_hdmitx_clk		 =	NULL;
		REG_FN.set_gcp_mode 		 = DE_REG_O20_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma		 = DE_REG_O20_SetMemByCma;
		REG_FN.get_mem_from_cma 	 = DE_REG_O20_GetMemFromCma;
		REG_FN.set_low_delay_clock	 = DE_REG_O20_SetLowDelayClock;
		REG_FN.dump_status			 = DE_REG_O20_FW_DumpStatus;
		REG_FN.get_shared_mem		 = DE_REG_O20_GetSharedMem;
		REG_FN.get_fpp_info 		 = DE_REG_O20_GetFPPInfo;
		REG_FN.get_mem_info 		 = DE_REG_O20_GetMEMInfo;
		REG_FN.get_dnn_result		 = DE_REG_O20_GetDNNStatus;
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,1)
		REG_FN.get_video_delay		 = DE_REG_O20_GetVideoDelay;
#endif
		REG_FN.view_info             = DE_REG_O20_ViewInfo;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_E60
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) {
		g_chip_id = 4;
		REG_FN.init 				 = DE_REG_E60_Init;
		REG_FN.set_frame_rate		 = DE_REG_E60_SetFrRate;
		REG_FN.set_bg_color 		 = DE_REG_E60_SetBgColor;
		REG_FN.set_win_blank		 = DE_REG_E60_SetWinBlank;
		REG_FN.get_mvi_colorimetry	 = NULL;
		REG_FN.set_cvi_src_type 	 = DE_REG_E60_SetCviSrcType;
		REG_FN.set_uart4mcu 		 = DE_REG_E60_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_E60_FW_GetMaxNum;
		REG_FN.download_fw			 = DE_REG_E60_FW_Download;
		REG_FN.download_fw_bin		 = DE_FW_E60_DownloadFromBin;
		REG_FN.download_fw_head 	 = DE_FW_E60_DownloadFromHead;
		REG_FN.set_cvi_fir			 = DE_REG_E60_SetCviFir;
		REG_FN.set_cvi_tpg			 = DE_REG_E60_SetCviTpg;
		REG_FN.set_cvi_csample		 = DE_REG_E60_SetCviCsampleMode;
		REG_FN.set_vcs				 = DE_REG_E60_SetVcs;
		REG_FN.reset_de 			 = DE_REG_E60_ResetDE;
		REG_FN.init_phy2virt		 = DE_REG_E60_InitPHY2VIRT;
		REG_FN.free_phy2virt		 = DE_REG_E60_FreePHY2VIRT;
		REG_FN.init_gpio			 = DE_REG_E60_GPIO_Init;
		REG_FN.init_hdmi			 = DE_REG_E60_HDMI_Init;
		REG_FN.init_lvds			 = DE_REG_E60_LVDS_Init;
		REG_FN.init_misc			 = DE_REG_E60_MISC_Init;
		REG_FN.init_osd 			 = DE_REG_E60_OSD_Init;
		REG_FN.is_alive_ipc 		 = DE_REG_E60_IPCisAlive;
		REG_FN.write_reg			 = DE_REG_E60_WD;
		REG_FN.read_reg 			 = DE_REG_E60_RD;
		REG_FN.set_cvi_buffer		 = DE_REG_E60_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw			 = DE_REG_E60_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc		 = DE_REG_E60_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode			 = DE_REG_E60_SetUdMode;
		REG_FN.set_debug			 = DE_REG_E60_SetDebug;
		REG_FN.get_debug			 = NULL;
		REG_FN.set_win_port_src 	 = DE_REG_E60_SetWinPortSrc;
		REG_FN.set_if_config		 = DE_REG_E60_SetInterfaceConfig;
		REG_FN.get_sys_status		 = DE_REG_E60_GetSystemStatus;
		REG_FN.get_src_status		 = DE_REG_E60_GetSourceStatus;
		REG_FN.set_operation		 = DE_REG_E60_SetOperation;
		REG_FN.set_operation_sub	 = DE_REG_E60_SetSubOperation;
		REG_FN.set_capture			 = NULL;
		REG_FN.switch_uart0 		 = DE_REG_E60_Uart0_Switch;
		REG_FN.set_ttx				 = NULL;
		REG_FN.set_vtm				 = DE_REG_E60_SetVTM;
		REG_FN.get_vtm				 = DE_REG_E60_GetVTM;
		REG_FN.get_fir				 = DE_REG_E60_GetFIR;
		REG_FN.verify_fw			 = DE_FW_E60_Verify;
		REG_FN.set_hdmi_port		 = DE_REG_E60_SetHdmiPort;
		REG_FN.get_capa 			 = DE_REG_E60_GetCapacity;
		REG_FN.get_local_mute		 = DE_REG_E60_GetLocalMute;
		REG_FN.set_multi_win		 = DE_REG_E60_SetMultiWin;
		REG_FN.set_hdmitx_clk		 =	NULL;
		REG_FN.set_gcp_mode 		 = DE_REG_E60_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma		 = DE_REG_E60_SetMemByCma;
		REG_FN.get_mem_from_cma 	 = DE_REG_E60_GetMemFromCma;
		REG_FN.set_low_delay_clock	 = DE_REG_E60_SetLowDelayClock;
		REG_FN.dump_status			 = DE_REG_E60_FW_DumpStatus;
		REG_FN.get_shared_mem		 = DE_REG_E60_GetSharedMem;
		REG_FN.get_fpp_info 		 = DE_REG_E60_GetFPPInfo;
		REG_FN.get_mem_info 		 = DE_REG_E60_GetMEMInfo;
		REG_FN.get_dnn_result		 = DE_REG_E60_GetDNNStatus;
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,1)
		REG_FN.get_video_delay		 = DE_REG_E60_GetVideoDelay;
#endif
		REG_FN.view_info             = DE_REG_E60_ViewInfo;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O22
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
		g_chip_id = 5;
		REG_FN.init 				 = DE_REG_O22_Init;
		REG_FN.set_frame_rate		 = DE_REG_O22_SetFrRate;
		REG_FN.set_bg_color 		 = DE_REG_O22_SetBgColor;
		REG_FN.set_win_blank		 = DE_REG_O22_SetWinBlank;
		REG_FN.get_mvi_colorimetry	 = NULL;
		REG_FN.set_cvi_src_type 	 = DE_REG_O22_SetCviSrcType;
		REG_FN.set_uart4mcu 		 = DE_REG_O22_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_O22_FW_GetMaxNum;
		REG_FN.download_fw			 = DE_REG_O22_FW_Download;
		REG_FN.download_fw_bin		 = DE_FW_O22_DownloadFromBin;
		REG_FN.download_fw_head 	 = DE_FW_O22_DownloadFromHead;
		REG_FN.set_cvi_fir			 = DE_REG_O22_SetCviFir;
		REG_FN.set_cvi_tpg			 = DE_REG_O22_SetCviTpg;
		REG_FN.set_cvi_csample		 = DE_REG_O22_SetCviCsampleMode;
		REG_FN.set_vcs				 = DE_REG_O22_SetVcs;
		REG_FN.reset_de 			 = DE_REG_O22_ResetDE;
		REG_FN.init_phy2virt		 = DE_REG_O22_InitPHY2VIRT;
		REG_FN.free_phy2virt		 = DE_REG_O22_FreePHY2VIRT;
		REG_FN.init_gpio			 = DE_REG_O22_GPIO_Init;
		REG_FN.init_hdmi			 = DE_REG_O22_HDMI_Init;
		REG_FN.init_lvds			 = DE_REG_O22_LVDS_Init;
		REG_FN.init_misc			 = DE_REG_O22_MISC_Init;
		REG_FN.init_osd 			 = DE_REG_O22_OSD_Init;
		REG_FN.is_alive_ipc 		 = DE_REG_O22_IPCisAlive;
		REG_FN.write_reg			 = DE_REG_O22_WD;
		REG_FN.read_reg 			 = DE_REG_O22_RD;
		REG_FN.set_cvi_buffer		 = DE_REG_O22_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw			 = DE_REG_O22_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc		 = DE_REG_O22_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode			 = DE_REG_O22_SetUdMode;
		REG_FN.set_debug			 = DE_REG_O22_SetDebug;
		REG_FN.get_debug			 = NULL;
		REG_FN.set_win_port_src 	 = DE_REG_O22_SetWinPortSrc;
		REG_FN.set_if_config		 = DE_REG_O22_SetInterfaceConfig;
		REG_FN.get_sys_status		 = DE_REG_O22_GetSystemStatus;
		REG_FN.get_src_status		 = DE_REG_O22_GetSourceStatus;
		REG_FN.set_operation		 = DE_REG_O22_SetOperation;
		REG_FN.set_operation_sub	 = DE_REG_O22_SetSubOperation;
		REG_FN.set_capture			 = NULL;
		REG_FN.switch_uart0 		 = DE_REG_O22_Uart0_Switch;
		REG_FN.set_ttx				 = NULL;
		REG_FN.set_vtm				 = DE_REG_O22_SetVTM;
		REG_FN.get_vtm				 = DE_REG_O22_GetVTM;
		REG_FN.get_fir				 = DE_REG_O22_GetFIR;
		REG_FN.verify_fw			 = DE_FW_O22_Verify;
		REG_FN.set_hdmi_port		 = DE_REG_O22_SetHdmiPort;
		REG_FN.get_capa 			 = DE_REG_O22_GetCapacity;
		REG_FN.get_local_mute		 = DE_REG_O22_GetLocalMute;
		REG_FN.set_multi_win		 = DE_REG_O22_SetMultiWin;
		REG_FN.set_hdmitx_clk		 =	NULL;
		REG_FN.set_gcp_mode 		 = DE_REG_O22_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma		 = DE_REG_O22_SetMemByCma;
		REG_FN.get_mem_from_cma 	 = DE_REG_O22_GetMemFromCma;
		REG_FN.set_low_delay_clock	 = DE_REG_O22_SetLowDelayClock;
		REG_FN.dump_status			 = DE_REG_O22_FW_DumpStatus;
		REG_FN.get_shared_mem		 = DE_REG_O22_GetSharedMem;
		REG_FN.get_fpp_info 		 = DE_REG_O22_GetFPPInfo;
		REG_FN.get_mem_info 		 = DE_REG_O22_GetMEMInfo;
		REG_FN.get_dnn_result		 = DE_REG_O22_GetDNNStatus;
		REG_FN.get_video_delay		 = DE_REG_O22_GetVideoDelay;
		REG_FN.view_info             = DE_REG_O22_ViewInfo;
		REG_FN.get_init_data		 = DE_REG_O22_GetInitData;
		REG_FN.get_hist_svp_buffer   = DE_REG_O22_GetHistoBufferRange;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_M23
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
		g_chip_id = 5;
		REG_FN.init 				 = DE_REG_M23_Init;
		REG_FN.set_frame_rate		 = DE_REG_M23_SetFrRate;
		REG_FN.set_bg_color 		 = DE_REG_M23_SetBgColor;
		REG_FN.set_win_blank		 = DE_REG_M23_SetWinBlank;
		REG_FN.get_mvi_colorimetry	 = NULL;
		REG_FN.set_cvi_src_type 	 = DE_REG_M23_SetCviSrcType;
		REG_FN.set_uart4mcu 		 = DE_REG_M23_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_M23_FW_GetMaxNum;
		REG_FN.download_fw			 = DE_REG_M23_FW_Download;
		REG_FN.download_fw_bin		 = NULL;
		REG_FN.download_fw_head 	 = DE_FW_M23_DownloadFromHead;
		REG_FN.set_cvi_fir			 = DE_REG_M23_SetCviFir;
		REG_FN.set_cvi_tpg			 = DE_REG_M23_SetCviTpg;
		REG_FN.set_cvi_csample		 = DE_REG_M23_SetCviCsampleMode;
		REG_FN.set_vcs				 = DE_REG_M23_SetVcs;
		REG_FN.reset_de 			 = DE_REG_M23_ResetDE;
		REG_FN.init_phy2virt		 = DE_REG_M23_InitPHY2VIRT;
		REG_FN.free_phy2virt		 = DE_REG_M23_FreePHY2VIRT;
		REG_FN.init_gpio			 = DE_REG_M23_GPIO_Init;
		REG_FN.init_hdmi			 = DE_REG_M23_HDMI_Init;
		REG_FN.init_lvds			 = DE_REG_M23_LVDS_Init;
		REG_FN.init_misc			 = DE_REG_M23_MISC_Init;
		REG_FN.init_osd 			 = DE_REG_M23_OSD_Init;
		REG_FN.is_alive_ipc 		 = DE_REG_M23_IPCisAlive;
		REG_FN.write_reg			 = NULL;
		REG_FN.read_reg 			 = NULL;
		REG_FN.set_cvi_buffer		 = DE_REG_M23_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw			 = DE_REG_M23_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc		 = DE_REG_M23_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode			 = DE_REG_M23_SetUdMode;
		REG_FN.set_debug			 = DE_REG_M23_SetDebug;
		REG_FN.get_debug			 = NULL;
		REG_FN.set_win_port_src 	 = DE_REG_M23_SetWinPortSrc;
		REG_FN.set_if_config		 = DE_REG_M23_SetInterfaceConfig;
		REG_FN.get_sys_status		 = DE_REG_M23_GetSystemStatus;
		REG_FN.get_src_status		 = DE_REG_M23_GetSourceStatus;
		REG_FN.set_operation		 = DE_REG_M23_SetOperation;
		REG_FN.set_operation_sub	 = DE_REG_M23_SetSubOperation;
		REG_FN.set_capture			 = NULL;
		REG_FN.switch_uart0 		 = DE_REG_M23_Uart0_Switch;
		REG_FN.set_ttx				 = NULL;
		REG_FN.set_vtm				 = DE_REG_M23_SetVTM;
		REG_FN.get_vtm				 = DE_REG_M23_GetVTM;
		REG_FN.get_fir				 = DE_REG_M23_GetFIR;
		REG_FN.verify_fw			 = DE_FW_M23_Verify;
		REG_FN.set_hdmi_port		 = DE_REG_M23_SetHdmiPort;
		REG_FN.get_capa 			 = DE_REG_M23_GetCapacity;
		REG_FN.get_local_mute		 = DE_REG_M23_GetLocalMute;
		REG_FN.set_multi_win		 = DE_REG_M23_SetMultiWin;
		REG_FN.set_hdmitx_clk		 =	NULL;
		REG_FN.set_gcp_mode 		 = DE_REG_M23_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma		 = DE_REG_M23_SetMemByCma;
		REG_FN.get_mem_from_cma 	 = DE_REG_M23_GetMemFromCma;
		REG_FN.set_low_delay_clock	 = DE_REG_M23_SetLowDelayClock;
		REG_FN.dump_status			 = DE_REG_M23_FW_DumpStatus;
		REG_FN.get_shared_mem		 = DE_REG_M23_GetSharedMem;
		REG_FN.get_fpp_info 		 = DE_REG_M23_GetFPPInfo;
		REG_FN.get_mem_info 		 = DE_REG_M23_GetMEMInfo;
		REG_FN.get_dnn_result		 = DE_REG_M23_GetDNNStatus;
		REG_FN.get_video_delay		 = DE_REG_M23_GetVideoDelay;
		REG_FN.view_info             = DE_REG_M23_ViewInfo;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O24
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) ) {
		g_chip_id = 6;
		REG_FN.init 				 = DE_REG_O24_Init;
		REG_FN.set_frame_rate		 = DE_REG_O24_SetFrRate;
		REG_FN.set_bg_color 		 = DE_REG_O24_SetBgColor;
		REG_FN.set_win_blank		 = DE_REG_O24_SetWinBlank;
		REG_FN.get_mvi_colorimetry	 = NULL;
		REG_FN.set_cvi_src_type 	 = DE_REG_O24_SetCviSrcType;
		REG_FN.set_uart4mcu 		 = DE_REG_O24_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_O24_FW_GetMaxNum;
		REG_FN.download_fw			 = DE_REG_O24_FW_Download;
		REG_FN.download_fw_bin		 = NULL;
		REG_FN.download_fw_head 	 = DE_REG_O24_FW_DownloadFromHead;
		REG_FN.set_cvi_fir			 = DE_REG_O24_SetCviFir;
		REG_FN.set_cvi_tpg			 = DE_REG_O24_SetCviTpg;
		REG_FN.set_cvi_csample		 = DE_REG_O24_SetCviCsampleMode;
		REG_FN.set_vcs				 = DE_REG_O24_SetVcs;
		REG_FN.reset_de 			 = DE_REG_O24_ResetDE;
		REG_FN.init_phy2virt		 = DE_REG_O24_InitPHY2VIRT;
		REG_FN.free_phy2virt		 = DE_REG_O24_FreePHY2VIRT;
		REG_FN.init_gpio			 = DE_REG_O24_GPIO_Init;
		REG_FN.init_hdmi			 = DE_REG_O24_HDMI_Init;
		REG_FN.init_lvds			 = DE_REG_O24_LVDS_Init;
		REG_FN.init_misc			 = DE_REG_O24_MISC_Init;
		REG_FN.init_osd 			 = DE_REG_O24_OSD_Init;
		REG_FN.is_alive_ipc 		 = DE_REG_O24_IPCisAlive;
		REG_FN.write_reg			 = NULL;
		REG_FN.read_reg 			 = NULL;
		REG_FN.set_cvi_buffer		 = DE_REG_O24_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw			 = DE_REG_O24_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc		 = DE_REG_O24_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode			 = DE_REG_O24_SetUdMode;
		REG_FN.set_debug			 = DE_REG_O24_SetDebug;
		REG_FN.get_debug			 = NULL;
		REG_FN.set_win_port_src 	 = DE_REG_O24_SetWinPortSrc;
		REG_FN.set_if_config		 = DE_REG_O24_SetInterfaceConfig;
		REG_FN.get_sys_status		 = DE_REG_O24_GetSystemStatus;
		REG_FN.get_src_status		 = DE_REG_O24_GetSourceStatus;
		REG_FN.set_operation		 = DE_REG_O24_SetOperation;
		REG_FN.set_operation_sub	 = DE_REG_O24_SetSubOperation;
		REG_FN.set_capture			 = NULL;
		REG_FN.switch_uart0 		 = DE_REG_O24_Uart0_Switch;
		REG_FN.set_ttx				 = NULL;
		REG_FN.set_vtm				 = DE_REG_O24_SetVTM;
		REG_FN.get_vtm				 = DE_REG_O24_GetVTM;
		REG_FN.get_fir				 = DE_REG_O24_GetFIR;
		REG_FN.verify_fw			 = DE_REG_O24_FW_Verify;
		REG_FN.set_hdmi_port		 = DE_REG_O24_SetHdmiPort;
		REG_FN.get_capa 			 = DE_REG_O24_GetCapacity;
		REG_FN.get_local_mute		 = DE_REG_O24_GetLocalMute;
		REG_FN.set_multi_win		 = DE_REG_O24_SetMultiWin;
		REG_FN.set_hdmitx_clk		 = NULL;
		REG_FN.set_gcp_mode 		 = DE_REG_O24_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma		 = DE_REG_O24_SetMemByCma;
		REG_FN.get_mem_from_cma 	 = DE_REG_O24_GetMemFromCma;
		REG_FN.set_low_delay_clock	 = DE_REG_O24_SetLowDelayClock;
		REG_FN.dump_status			 = DE_REG_O24_FW_DumpStatus;
		REG_FN.get_shared_mem		 = DE_REG_O24_GetSharedMem;
		REG_FN.get_fpp_info 		 = DE_REG_O24_GetFPPInfo;
		REG_FN.get_mem_info 		 = DE_REG_O24_GetMEMInfo;
		REG_FN.get_dnn_result		 = DE_REG_O24_GetDNNStatus;
		REG_FN.get_video_delay		 = DE_REG_O24_GetVideoDelay;
		REG_FN.view_info             = DE_REG_O24_ViewInfo;
		REG_FN.get_init_data		 = DE_REG_O24_GetInitData;
		REG_FN.get_hist_svp_buffer   = DE_REG_O24_GetHistoBufferRange;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O26
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) ) {
		g_chip_id = 6;
		REG_FN.init 				 = DE_REG_O26_Init;
		REG_FN.set_frame_rate		 = DE_REG_O26_SetFrRate;
		REG_FN.set_bg_color 		 = DE_REG_O26_SetBgColor;
		REG_FN.set_win_blank		 = DE_REG_O26_SetWinBlank;
		REG_FN.get_mvi_colorimetry	 = NULL;
		REG_FN.set_cvi_src_type 	 = DE_REG_O26_SetCviSrcType;
		REG_FN.set_uart4mcu 		 = DE_REG_O26_Uart0_Switch;
		REG_FN.get_fw_max_num 		 = DE_REG_O26_FW_GetMaxNum;
		REG_FN.download_fw			 = DE_REG_O26_FW_Download;
		REG_FN.download_fw_bin		 = NULL;
		REG_FN.download_fw_head 	 = DE_REG_O26_FW_DownloadFromHead;
		REG_FN.set_cvi_fir			 = DE_REG_O26_SetCviFir;
		REG_FN.set_cvi_tpg			 = DE_REG_O26_SetCviTpg;
		REG_FN.set_cvi_csample		 = DE_REG_O26_SetCviCsampleMode;
		REG_FN.set_vcs				 = DE_REG_O26_SetVcs;
		REG_FN.reset_de 			 = DE_REG_O26_ResetDE;
		REG_FN.init_phy2virt		 = DE_REG_O26_InitPHY2VIRT;
		REG_FN.free_phy2virt		 = DE_REG_O26_FreePHY2VIRT;
		REG_FN.init_gpio			 = DE_REG_O26_GPIO_Init;
		REG_FN.init_hdmi			 = DE_REG_O26_HDMI_Init;
		REG_FN.init_lvds			 = DE_REG_O26_LVDS_Init;
		REG_FN.init_misc			 = DE_REG_O26_MISC_Init;
		REG_FN.init_osd 			 = DE_REG_O26_OSD_Init;
		REG_FN.is_alive_ipc 		 = DE_REG_O26_IPCisAlive;
		REG_FN.write_reg			 = NULL;
		REG_FN.read_reg 			 = NULL;
		REG_FN.set_cvi_buffer		 = DE_REG_O26_SetCviVideoFrameBuffer;
		REG_FN.set_cvi_rw			 = DE_REG_O26_SetCviRWFrameBuffer;
		REG_FN.sel_multiwinsrc		 = DE_REG_O26_SelectMultiWinSrc;
		REG_FN.set_scart_rbg_bypass  = NULL;
		REG_FN.set_ud_mode			 = DE_REG_O26_SetUdMode;
		REG_FN.set_debug			 = DE_REG_O26_SetDebug;
		REG_FN.get_debug			 = NULL;
		REG_FN.set_win_port_src 	 = DE_REG_O26_SetWinPortSrc;
		REG_FN.set_if_config		 = DE_REG_O26_SetInterfaceConfig;
		REG_FN.get_sys_status		 = DE_REG_O26_GetSystemStatus;
		REG_FN.get_src_status		 = DE_REG_O26_GetSourceStatus;
		REG_FN.set_operation		 = DE_REG_O26_SetOperation;
		REG_FN.set_operation_sub	 = DE_REG_O26_SetSubOperation;
		REG_FN.set_capture			 = NULL;
		REG_FN.switch_uart0 		 = DE_REG_O26_Uart0_Switch;
		REG_FN.set_ttx				 = NULL;
		REG_FN.set_vtm				 = DE_REG_O26_SetVTM;
		REG_FN.get_vtm				 = DE_REG_O26_GetVTM;
		REG_FN.get_fir				 = DE_REG_O26_GetFIR;
		REG_FN.verify_fw			 = DE_REG_O26_FW_Verify;
		REG_FN.set_hdmi_port		 = DE_REG_O26_SetHdmiPort;
		REG_FN.get_capa 			 = DE_REG_O26_GetCapacity;
		REG_FN.get_local_mute		 = DE_REG_O26_GetLocalMute;
		REG_FN.set_multi_win		 = DE_REG_O26_SetMultiWin;
		REG_FN.set_hdmitx_clk		 = NULL;
		REG_FN.set_gcp_mode 		 = DE_REG_O26_SetGeneralCapturePath;
		REG_FN.set_mem_by_cma		 = DE_REG_O26_SetMemByCma;
		REG_FN.get_mem_from_cma 	 = DE_REG_O26_GetMemFromCma;
		REG_FN.set_low_delay_clock	 = DE_REG_O26_SetLowDelayClock;
		REG_FN.dump_status			 = DE_REG_O26_FW_DumpStatus;
		REG_FN.get_shared_mem		 = DE_REG_O26_GetSharedMem;
		REG_FN.get_fpp_info 		 = DE_REG_O26_GetFPPInfo;
		REG_FN.get_mem_info 		 = DE_REG_O26_GetMEMInfo;
		REG_FN.get_dnn_result		 = DE_REG_O26_GetDNNStatus;
		REG_FN.get_video_delay		 = DE_REG_O26_GetVideoDelay;
		REG_FN.view_info             = DE_REG_O26_ViewInfo;
		REG_FN.get_init_data		 = DE_REG_O26_GetInitData;
		REG_FN.get_hist_svp_buffer   = DE_REG_O26_GetHistoBufferRange;
	} else
#endif
	{
		g_chip_id = -1;
		DE_ERROR("not defined chip rev.\n");
		ret = RET_ERROR;
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	int ret = RET_OK;

	sDePanelType = *pstParams;
	CHECK_REG_NULL(gfn_all[GET_ID()].init);
	ret = gfn_all[GET_ID()].init(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get irq number
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_InitRegister(void)
{
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetFrRate(LX_DE_FR_RATE_T *pstParams)
{
	int ret = RET_OK;
	DE_DPLL_CLK_T dclk;
	DE_DPLL_CLK_T *pDisplayPll = NULL;
	int pllIndex;
	int i;

	do {
		CHECK_KNULL(pstParams);
		sDeFrRate = *pstParams;
		pllIndex = 0;

		for (i=0;i<ARRAY_SIZE(sDePanelSet);i++) {
			if (sDePanelSet[i].panelType != sDePanelType) continue;
			pDisplayPll = sDePanelSet[i].pDpllClk;
			break;
		}
		CHECK_KNULL(pDisplayPll);
		dclk = pDisplayPll[pllIndex];

		CHECK_REG_NULL(gfn_all[GET_ID()].set_frame_rate);
		gfn_all[GET_ID()].set_frame_rate(dclk);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get Frame rate of Display
 *
 * @param pFrRate [OUT] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetFrRate(LX_DE_FR_RATE_T *pstParams)
{
	*pstParams = sDeFrRate;
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_bg_color);
	ret = gfn_all[GET_ID()].set_bg_color(pBackColor);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set blank color of selected window
 *
 * @param pWinBlank [IN] structure pointer to carry information about window Id, whether Turn On or Off and blank color
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;
	
	CHECK_REG_NULL(gfn_all[GET_ID()].set_win_blank);
	ret = gfn_all[GET_ID()].set_win_blank(pWinBlank);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
{
	int ret = RET_OK;
	
	CHECK_REG_NULL(gfn_all[GET_ID()].set_cvi_buffer);
	ret = gfn_all[GET_ID()].set_cvi_buffer(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams,\
								LX_DE_CVI_RW_PREW_FRAME_T *prewInfo)
{
	int ret = RET_OK;
	
	CHECK_REG_NULL(gfn_all[GET_ID()].set_cvi_rw);
	ret = gfn_all[GET_ID()].set_cvi_rw(pstParams, prewInfo);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set information which is comming from CVI port
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_cvi_src_type);
	ret = gfn_all[GET_ID()].set_cvi_src_type(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get MVI source colorimetry information.
 *
 * @param pstParams [OUT] value of MVI colorimetry
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetMviColorimetry(LX_DE_MVI_COLORIMETRY_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_mvi_colorimetry);
	ret = gfn_all[GET_ID()].get_mvi_colorimetry(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set uart for MCU or CPU
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetUart4MCU(BOOLEAN bUart4MCU)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_uart4mcu);
	ret = gfn_all[GET_ID()].set_uart4mcu(bUart4MCU);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de VCS parameter.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_vcs);
	ret = gfn_all[GET_ID()].set_vcs(pstParams);

	return ret;
}

int DE_HAL_FW_GetMaxNum(UINT32 *pMaxNum)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_fw_max_num);
	ret = gfn_all[GET_ID()].get_fw_max_num(pMaxNum);

	return ret;
}

#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_HAL_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].download_fw);
	ret = gfn_all[GET_ID()].download_fw(pstParams);

	return ret;
}

int DE_HAL_FW_DumpStatus(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].dump_status);
	ret = gfn_all[GET_ID()].dump_status();

	return ret;
}

#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief send captured video fir coef for double/quad sampling case.
 *
 * @param cvi_channel, fir coef, and enable [IN] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_cvi_fir);
	ret = gfn_all[GET_ID()].set_cvi_fir(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send set captured video test pattern generator to black.
 *
 * @param cvi_channel, pattern enable, freeze enable, pattern color space [IN]] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_cvi_tpg);
	ret = gfn_all[GET_ID()].set_cvi_tpg(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video color sampling mode(sub sampling or 3 tap filtering).
 *
 * @param cvi_channel, color sampling mode(sub_sample, 3-tap-filter) [IN] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_cvi_csample);
	ret = gfn_all[GET_ID()].set_cvi_csample(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief reset Register of DE HW Block
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].reset_de);
	ret = gfn_all[GET_ID()].reset_de(bReset);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init phys -> virt for register access
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_InitPHY2VIRT(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].init_phy2virt);
	ret = gfn_all[GET_ID()].init_phy2virt();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief free phys -> virt for register access
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_FreePHY2VIRT(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].free_phy2virt);
	ret = gfn_all[GET_ID()].free_phy2virt();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init gpio
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GPIO_Init(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].init_gpio);
	ret = gfn_all[GET_ID()].init_gpio();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init hdmi 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_HDMI_Init(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].init_hdmi);
	ret = gfn_all[GET_ID()].init_hdmi();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init lvds 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_LVDS_Init(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].init_lvds);
	ret = gfn_all[GET_ID()].init_lvds();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init misc 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_MISC_Init(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].init_misc);
	ret = gfn_all[GET_ID()].init_misc();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init osd 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_OSD_Init(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].init_osd);
	ret = gfn_all[GET_ID()].init_osd();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief download firmware from binary file
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_FW_DownloadFromBin(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].download_fw_bin);
	ret = gfn_all[GET_ID()].download_fw_bin();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief download firmware from header 
 *
 * @param pstParams [IN] LX_DE_FW_DWLD_T
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_FW_DownloadFromHead(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].download_fw_head);
	ret = gfn_all[GET_ID()].download_fw_head(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check ipc ready
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_IPCisAlive(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].is_alive_ipc);
	ret = gfn_all[GET_ID()].is_alive_ipc();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief write register 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_WriteReg(void *addr, UINT32 value)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].write_reg);
	ret = gfn_all[GET_ID()].write_reg(addr, value);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief read register
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ReadReg(void *addr, UINT32 *value)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].read_reg);
	ret = gfn_all[GET_ID()].read_reg(addr);
	*value = (UINT32)ret;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control ud mode 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_ud_mode);
	ret = gfn_all[GET_ID()].set_ud_mode(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control vtm 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_vtm);
	ret = gfn_all[GET_ID()].set_vtm(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get address for vtm operation
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_vtm);
	ret = gfn_all[GET_ID()].get_vtm(pstParams);

	return ret;
}

int DE_HAL_GetFPPInfo(UINT32 *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_fpp_info);
	ret = gfn_all[GET_ID()].get_fpp_info(pstParams);

	return ret;
}

int DE_HAL_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_mem_info);
	ret = gfn_all[GET_ID()].get_mem_info(pstParams);

	return ret;
}

int DE_HAL_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_gcp_mode);
	ret = gfn_all[GET_ID()].set_gcp_mode(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set pip source
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].sel_multiwinsrc);
	ret = gfn_all[GET_ID()].sel_multiwinsrc(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief sw work-around 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetSCARTRGBBypassMode(int *pEnable)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_scart_rbg_bypass);
	ret = gfn_all[GET_ID()].set_scart_rbg_bypass(*pEnable);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief  
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;
	
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief  
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_debug);
	ret = gfn_all[GET_ID()].set_debug(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_win_port_src);
	ret = gfn_all[GET_ID()].set_win_port_src(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set interface configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_if_config);
	ret = gfn_all[GET_ID()].set_if_config(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set interface configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_sys_status);
	ret = gfn_all[GET_ID()].get_sys_status(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set interface configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_src_status);
	ret = gfn_all[GET_ID()].get_src_status(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set window configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_operation);
	ret = gfn_all[GET_ID()].set_operation(pstParams);

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief Set window configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_operation_sub);
	ret = gfn_all[GET_ID()].set_operation_sub(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set capture control
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCaptureControl(LX_DE_CAPTURE_CTRL_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_capture);
	ret = gfn_all[GET_ID()].set_capture(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make IPC interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SwitchUART0(int whichUart)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].switch_uart0);
	ret = gfn_all[GET_ID()].switch_uart0(whichUart);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set ttx data
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetTtx(VIDEO_TTX_PACK_T *pTtxPack)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_ttx);
	ret = gfn_all[GET_ID()].set_ttx(pTtxPack);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get cvi fir coefficient
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_fir);
	ret = gfn_all[GET_ID()].get_fir(pstParams, fir);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief verify firmware binary
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_VerifyFirmware(void)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].verify_fw);
	ret = gfn_all[GET_ID()].verify_fw();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set hdmi port
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetHDMIPort(LX_DE_HDMIPORT_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get capacity of chip
 *
 * @param pstParams [OUT] capa info
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetCapacity(LX_DE_CAPACITY_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_capa);
	ret = gfn_all[GET_ID()].get_capa(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set seamless info to mcu
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetSeamlessInfo(LX_DE_RECT_T *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_seamless);
	ret = gfn_all[GET_ID()].set_seamless(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get local mute value
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetLocalMuteValue(UINT32 *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_local_mute);
	ret = gfn_all[GET_ID()].get_local_mute(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set multi window information
 *
 * @param pstParams [IN] int
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetMultiWin(UINT32 *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_multi_win);
	ret = gfn_all[GET_ID()].set_multi_win(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set hdmitx in/out clock
 *
 * @param eClk [IN] out clk index
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_HDMITX_SetClk(LX_DE_HDMITX_OUTPUT_INFO_T  *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_hdmitx_clk);
	ret = gfn_all[GET_ID()].set_hdmitx_clk(pstParams);

	return ret;
}

int DE_HAL_SetMemByCma(char* mem_name)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_mem_by_cma);
	ret = gfn_all[GET_ID()].set_mem_by_cma(mem_name);

	return ret;
}

int DE_HAL_GetMemFromCma(char *mem_name, int count, void *buf_info, BOOLEAN flag)
{
	int ret = RET_OK;
	
	CHECK_REG_NULL(gfn_all[GET_ID()].get_mem_from_cma);
	ret = gfn_all[GET_ID()].get_mem_from_cma(mem_name, count, buf_info, flag);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set ctop clock control for new low delay mode
 *
 * @param eClk [IN] out clk index
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetLowDelayBySourceSync(UINT32 *pstParams)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].set_low_delay_clock);
	ret = gfn_all[GET_ID()].set_low_delay_clock(pstParams);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get shared mem for mmap
 *
 * @param eClk [IN] page_offset, mem_info(start/end/size)
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetSharedMem(UINT32 page_offset, UINT32 **mem_info)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_shared_mem);
	ret = gfn_all[GET_ID()].get_shared_mem(page_offset, mem_info);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief pre initialize before mem init
 *
 * @param eClk [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_PreInit(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_M17
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) )
	{
		DE_REG_M17_PreInit(); // specific initialization for memory alloc (M17 B0 / C0)
	}
#endif
#ifdef USE_KDRV_CODES_FOR_M19
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M19) )
	{
		DE_REG_M19_PreInit();
	}
#endif
#ifdef USE_KDRV_CODES_FOR_O20
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
		{
			DE_REG_O20_PreInit();
		}
#endif
#ifdef USE_KDRV_CODES_FOR_E60
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
		{
			DE_REG_E60_PreInit();
		}
#endif
#ifdef USE_KDRV_CODES_FOR_O22
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
		{
			DE_REG_O22_PreInit();
		}
#endif
#ifdef USE_KDRV_CODES_FOR_M23
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) )
		{
			DE_REG_M23_PreInit();
		}
#endif
#ifdef USE_KDRV_CODES_FOR_O24
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )
		{
			DE_REG_O24_PreInit();
		}
#endif
#ifdef USE_KDRV_CODES_FOR_O26
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )
		{
			DE_REG_O26_PreInit();
		}
#endif
	return ret;
}

int DE_HAL_GetPQE_DNNResult(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_dnn_result);
	ret = gfn_all[GET_ID()].get_dnn_result(a, b, c, d, e, f);

	return ret;
}

int DE_HAL_SetSysTime(UINT32 *sec, UINT32 *msec, UINT32 *usec)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_M17
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) )
	{
		CHECK_REG_NULL(gfn_all[GET_ID()].set_sys_time);
		ret = gfn_all[GET_ID()].set_sys_time(sec, msec, usec);
	}
#endif

	return ret;
}

int DE_HAL_GetTimeDiff(UINT32 *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_M17
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) )
	{
		CHECK_REG_NULL(gfn_all[GET_ID()].get_time_diff);
		ret = gfn_all[GET_ID()].get_time_diff(pstParams);
	}
#endif

	return ret;
}

int DE_HAL_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_MEM_T *pstParams)
{
	int ret = RET_OK;

	if(g_chip_id == 0) return -1;
	CHECK_REG_NULL(gfn_all[GET_ID()].get_video_delay);
	ret = gfn_all[GET_ID()].get_video_delay(pstParams);

	return ret;
}

int DE_HAL_ViewInfo(int type)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].view_info);
	ret = gfn_all[GET_ID()].view_info(type);

	return ret;
}

int DE_HAL_SupportInitData(void)
{
	int ret = RET_OK;
	CHECK_REG_NULL(gfn_all[GET_ID()].get_init_data);
	return ret;
}

int DE_HAL_GetInitData(LX_DE_IPC_INIT_DATA_T *pstParams)
{
	int ret = RET_OK;

	ret = DE_HAL_SupportInitData();
	if (ret != RET_OK)	return ret;
	ret = gfn_all[GET_ID()].get_init_data(pstParams);

	return ret;
}

int DE_HAL_GetHistoBufferRange(UINT32 *start,UINT32 *end)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gfn_all[GET_ID()].get_hist_svp_buffer);
	ret = gfn_all[GET_ID()].get_hist_svp_buffer(start, end);

	return ret;

}
/**  @} */
