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
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.02.19
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#undef INCLUDE_KDRV_VENC

#define USE_1_DEDICATED_VT_BUFFER // check de_mem_init (cma allocated buffer)
#define USE_GRAB_PIXEL_BY_CAPTURING_FRAME
#undef  USE_CVI_COPY_TO_NFS
#undef  USE_DSP_COPY_TO_NFS
#define USE_DE_WIN_BLANK_AT_MCU_PART
#define USE_DE_CVI_FIR_AT_MCU_PART
#define USE_DE_CVI_TPG_AT_MCU_PART
#define USE_DE_CVI_CSAMPLE_AT_MCU_PART
#ifdef USE_DE_CVI_FIR_AT_MCU_PART
#define USE_DE_CVI_FIR_FROM_HAL
#endif

#if defined(USE_CVI_COPY_TO_NFS) || defined(USE_DSP_COPY_TO_NFS)
#  define USE_FRAME_COPY_TO_NFS
#endif
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

#include "de_def.h"
#include "hal/ipc_hal.h"
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#include "mcu/de_fw_def.h"
#include "mcu/de_fw.h"
//#include "mcu/ipc_cmd_header.h"
#include "de_hal.h"
#include "dolby_hal.h"
#include "de_io.h"
#include "vsc_fw.h"
#ifdef INCLUDE_KDRV_VENC
#include "venc_cfg.h"
#endif
#ifdef INCLUDE_KDRV_BE
#include "pwm_hal.h"
#include "ovi_hal.h"
#endif
#ifdef TEST_GPIO_CONTROL
#include "../gpio/gpio_drv.h"
#include "../gpio/gpio_core.h"
#endif
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *----------------------i-----------------------------------------------------------------*/
#define CP_FROM_USER(a,b,c,d)  if(d == 0){if(!io_resume){ret = copy_from_user(a,b,c);if(ret)break;}\
	                           else{memcpy(a,b,c);}} else {memcpy(a,b,c);}
#define CP_TO_USER(a,b,c,d)    if(d == 0) { if(!io_resume){ret = copy_to_user(a,b,c);if(ret)break;}\
	                           else{memcpy(a,b,c);}} else {memcpy(a,b,c); ret = RET_OK;/*printk("ret val####### = %d\n",ret);*/}

#define MCU_Write(a,b,c) h_ipc->m_ipc_client->write( a , b , c )
#define MCU_Read(a,b,c)  h_ipc->m_ipc_client->read( a , b , c )

#define CHECK_MCU_IPC()  if(h_ipc == NULL                      ||\
							h_ipc->m_ipc_client->write == NULL ||\
							h_ipc->m_ipc_client->read  == NULL)  \
							{DE_ERROR("ipc handler is null\n");  \
							ret = RET_ERROR;return ret;}
#define CHECK_IO_RET()   if(ret != RET_OK) \
							{DE_ERROR("RET_ERROR ret = %d\n", ret);}

#define u16CHK_RANGE(X,Y,offset)		((UINT16) ((X) + (offset) - (Y)) <= (offset*2))

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_VENC
extern LX_VENC_MEM_CFG_S_T *gpstVencMemConfig;
#endif

LX_DE_VTM_FRAME_INFO_T gVtmParams;
UINT32 global_mute_status[2] = { 0 };

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/
void DE_IO_AddListener( void(*fn)(unsigned long arg) );
void DE_IO_MaskControl(int flag);

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/
struct ipc_handle *h_ipc = NULL;
char io_resume = FALSE;
LX_DE_CAPACITY_T g_capa;
LX_DE_FW_DWLD_T stFirmware_qsm;
LX_DE_FW_DWLD_T stFirmware_mcu1_qsm;
LX_DE_PANEL_TYPE_T g_Diplay_type = LX_PANEL_TYPE_MAX;
int _g_gcp_enable_count = 0;
BOOLEAN _g_freeze_status = 0;
LX_DE_WIN_INFO_T prev_win_info;
LX_DE_CVI_SPLIT_MODE_T prev_split_mode;
LX_DE_INPUT_SOURCE_T prev_input_src;
LX_DE_SET_DELAY_BUFFER_T prev_bt_cfg, prev_vr_cfg = { 0 };
struct mutex     vsc_mutex_lock0;
struct mutex     vsc_mutex_lock1;

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static void(*g_DEListener)(unsigned long) = NULL;

/**
 * @brief register DE event listener (temporary workaround only by raxis.lim (2014/10/22)
 *
 */
void DE_IO_AddListener( void(*fn)(unsigned long arg) )
{
	g_DEListener = fn;
}

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
BOOLEAN _g_gcp_mode = FALSE;

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
/*static int DE_IO_GetHWOpt(UINT32 *opt)
{
	UINT32 panel_mode = 1; //default = UHD
	char hw_opt[24];

	if(RET_OK==OS_ScanKernelCmdline("hwopt=%s", hw_opt))
	{
		switch(hw_opt[1]) {
			case '2':
					panel_mode = ATSC30_BOX; // ATSC3.0 legacy BOX
			break;
			default:
				panel_mode = 1;
			break; // LED/OLED
		}
	}

	*opt = panel_mode;

	return RET_OK;
}*/

int DE_IO_SetMcuSuspend(UINT32 arg)
{
	int ret = RET_OK;
	UINT32 enable;
	CHECK_MCU_IPC();
	enable = arg;
	DE_NOTI("enable:%d\n",enable);
	ret = MCU_Write(DE_PACK_CMD(DE_IPC_SET_SUSPEND), &enable, sizeof(enable));
	CHECK_IO_RET();
	return RET_OK;
}


int DE_IO_Resume(unsigned long arg)
{
	if(arg) io_resume = TRUE;
	else    io_resume = FALSE;
	return RET_OK;
}

int DE_IO_IPC_Init(unsigned long arg)
{
	int ret = RET_OK;

	stFirmware_qsm.pData = NULL;
	stFirmware_mcu1_qsm.pData = NULL;

	ret = DE_HAL_Select_Chip();
	if(ret) return ret;

	ret = DE_DHDR_IP_HAL_Select_Chip();
	if(ret) return ret;

	memset(&g_capa, 0, sizeof(LX_DE_CAPACITY_T));
	ret = DE_HAL_GetCapacity(&g_capa);
	if(ret) return ret;

	ret = ipc_hal_init();
	if(ret) return ret;

	h_ipc = ipc_hal_open("de", MCU_ID_0);
	if(!h_ipc)
	{
		ret = RET_ERROR;
		DE_ERROR("ipc_hal open fail !\n");
	}

	DE_PRINT("mcu ipc handle = %p\n", h_ipc);

	return ret;
}

int DE_IO_IPC_Cleanup(unsigned long arg)
{
	ipc_hal_close(h_ipc);
	if(stFirmware_qsm.pData)
	{
		OS_Free(stFirmware_qsm.pData);
		stFirmware_qsm.pData = NULL;
	}
	if(stFirmware_mcu1_qsm.pData)
	{
		OS_Free(stFirmware_mcu1_qsm.pData);
		stFirmware_mcu1_qsm.pData = NULL;
	}
	return RET_OK;
}

static int _DE_IO_SetInitData_lagecy(LX_DE_PANEL_TYPE_T stParams)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipcCmd;
	UINT32 platformVersion = lx_chip_rev();

	do {
		CHECK_MCU_IPC();
		ipcCmd = DE_IPC_DE_INIT;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;

		ipcCmd = DE_IPC_SET_PLATFORM_VERSION;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &platformVersion, sizeof(platformVersion));
		if (ret) break;
	} while (0);

	return ret;
}

int DE_IO_SupportInitData(void)
{
	return DE_HAL_SupportInitData();
}

int DE_IO_SetInitData(void)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipcCmd;
	LX_DE_IPC_INIT_DATA_T init_data;
	UINT32 platform_ver = lx_chip_rev();

	do {
		CHECK_MCU_IPC();

		memset(&init_data,0,sizeof(init_data));
		ret = DE_HAL_GetInitData(&init_data);
		if (ret) break;

		ipcCmd = DE_IPC_DE_INIT;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &init_data, sizeof(init_data));
		if (ret) break;

		ipcCmd = DE_IPC_SET_PLATFORM_VERSION;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &platform_ver, sizeof(platform_ver));
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize de moudle
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_Init(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_PANEL_TYPE_T stParams;

#ifdef TEST_GPIO_CONTROL
	GPIO_DevSetPinMux(TEST_GPIO_CONTROL, TRUE);
	GPIO_DevSetMode(TEST_GPIO_CONTROL, LX_GPIO_MODE_OUTPUT);
	GPIO_DevSetValue(TEST_GPIO_CONTROL, 1);
#endif
	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		stParams = LX_PANEL_TYPE_3840;

		if (RET_OK != DE_IO_SupportInitData())
		{
			ret = _DE_IO_SetInitData_lagecy(stParams);
			if (ret) break;
		}

		ret = DE_HAL_Init(&stParams);
		if (ret) break;
		g_Diplay_type = stParams;

		// init bt config
		memset(&prev_bt_cfg, 0, sizeof(LX_DE_SET_DELAY_BUFFER_T));
		memset(&prev_vr_cfg, 0, sizeof(LX_DE_SET_DELAY_BUFFER_T));

		mutex_init(&vsc_mutex_lock0);
		mutex_init(&vsc_mutex_lock1);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of firmware
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetFirmwareInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_FIRMWARE_INFO_T stParams;
	LX_DE_FIRMWARE_INFO_T *pstParams = (LX_DE_FIRMWARE_INFO_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_FIRMWARE_INFO;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(LX_DE_FIRMWARE_INFO_T));
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
#ifdef TEST_GPIO_CONTROL
		GPIO_DevSetValue(TEST_GPIO_CONTROL, 0);
		msleep(10);
		GPIO_DevSetValue(TEST_GPIO_CONTROL, 1);
#endif
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set background color (non-active region color).
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetBgColor(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_COLOR_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_BG_COLOR;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetBgColor(&stParams);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set blank of selected window and blank color
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetWinBlank(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
#ifdef USE_DE_WIN_BLANK_AT_MCU_PART
	LX_DE_SET_WIN_BLANK_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_WIN_BLANK;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
#ifdef TEST_GPIO_CONTROL
		if(stParams.win_id == 0 && stParams.bEnable == 0)
			GPIO_DevSetValue(TEST_GPIO_CONTROL, 0);
#endif
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SET_WIN_BLANK_T));
	} while(0);
#else
	LX_DE_SET_WIN_BLANK_T stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_SetWinBlank(&stParams);
	} while (0);
#endif
	global_mute_status[stParams.win_id] = stParams.bEnable;
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of selected window about size and offset of input window
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetInputWin(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_DIMENSION_T stParams;
	LX_DE_WIN_DIMENSION_T *pstParams = (LX_DE_WIN_DIMENSION_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_INPUT_WIN;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_WIN_DIMENSION_T));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(LX_DE_WIN_DIMENSION_T));
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of selected window about size and offset of output window
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetOutWin(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_DIMENSION_T stParams;
	LX_DE_WIN_DIMENSION_T *pstParams = (LX_DE_WIN_DIMENSION_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_OUT_WIN;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_WIN_DIMENSION_T));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(LX_DE_WIN_DIMENSION_T));
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information of selected window about size and offset of input window
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetInputWin(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_DIMENSION_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_INPUT_WIN;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information of selected window about size and offset of output window
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetOutWin(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_DIMENSION_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_OUT_WIN;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information of selected window about rot, source size, input window, output window
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetWinInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_INFO_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_WIN_INFO;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		memcpy(&prev_win_info, &stParams, sizeof(stParams));
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of selected window about rot, source size, input window, output window
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetWinInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_INFO_T stParams;
	LX_DE_WIN_INFO_T *pstParams = (LX_DE_WIN_INFO_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_WIN_INFO;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_WIN_INFO_T));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(LX_DE_WIN_INFO_T));
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Determine to make Display turn On or Off
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDisOut(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DIS_OUT;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Determine selected multi window to turn On or Off
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_MultiWinEnable(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_MULTI_WIN_ENALBE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(BOOLEAN));
		if (ret) break;
       	ret = DE_HAL_SetMultiWin(&stParams);
	} while(0);
	CHECK_IO_RET();
	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief Set signage mode on/off  (concurrent video output thru hdmi-tx)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSignageMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SIGNAGE_MODE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(BOOLEAN));
		if (ret) break;
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set hdmi-tx in/out clock
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetHDMITXInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_HDMITX_OUTPUT_INFO_T stParams;

	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_HDMITX_OUT_INFO;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_HDMITX_SetClk(&stParams);
		if (ret) break;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_HDMITX_OUTPUT_INFO_T));
		if (ret) break;
	} while(0);

	CHECK_IO_RET();
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
int DE_IO_SetCviSrcType(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CVI_SRC_TYPE_T stParams;
	LX_DE_INPUT_SOURCE_T stParams_input;
	LX_DE_WIN_INFO_T stParams_win;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_SRC_TYPE;
#ifdef USE_DE_CVI_FIR_FROM_HAL
	LX_DE_CVI_FIR_T fir;
	DE_IPC_CMD_T ipcCmd_fir = DE_IPC_SET_CVI_FIR;
#endif

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
#ifdef USE_DE_CVI_FIR_FROM_HAL
		ret = DE_HAL_GetFIR(&stParams, &fir);
		if (ret) break;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd_fir), &fir, sizeof(fir));
		if (ret) break;
		ret = DE_HAL_SetCviFir(&fir);
		if (ret) break;
#endif
		if((stParams.cvi_split_info.split_mode == LX_DE_CVI_SPLIT_1X2_DUP) && \
			(prev_split_mode != LX_DE_CVI_SPLIT_1X2_DUP)) {
			stParams_input.srcId = 0;
			stParams_input.srcType = LX_DE_IN_SRC_HDMI;
			stParams_input.srcAttr = 3; // mercury:0, webos:3
			stParams_input.srcPort = 0;
			stParams_input.hdmiPort = stParams_input.srcAttr;
			ipcCmd = DE_IPC_SET_WIN_PORT_SRC;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_input, sizeof(stParams_input));

			DE_NOTI("w/a for SPLIT_1X2_DUP (8k feedback path)");
		}
		else if((stParams.cvi_split_info.split_mode != LX_DE_CVI_SPLIT_1X2_DUP) && \
			(prev_split_mode == LX_DE_CVI_SPLIT_1X2_DUP)) {
			if(prev_input_src.srcType == LX_DE_IN_SRC_HDMI) {
				ipcCmd = DE_IPC_SET_WIN_PORT_SRC;
				ret = MCU_Write(DE_PACK_CMD(ipcCmd), &prev_input_src, sizeof(prev_input_src));

				DE_NOTI("restore prev port[%d]", prev_input_src.srcAttr);
			}
		}

		ipcCmd = DE_IPC_SET_CVI_SRC_TYPE;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetCviSrcType(&stParams);

		if((stParams.cvi_split_info.split_mode == LX_DE_CVI_SPLIT_1X2_DUP) && \
			(prev_split_mode != LX_DE_CVI_SPLIT_1X2_DUP)) {
			memcpy(&stParams_win, &prev_win_info, sizeof(stParams_win));
			ipcCmd = DE_IPC_SET_WIN_INFO;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_win, sizeof(stParams_win));
		}
		else if((stParams.cvi_split_info.split_mode != LX_DE_CVI_SPLIT_1X2_DUP) && \
			(prev_split_mode == LX_DE_CVI_SPLIT_1X2_DUP)) {
			memcpy(&stParams_win, &prev_win_info, sizeof(stParams_win));
			ipcCmd = DE_IPC_SET_WIN_INFO;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_win, sizeof(stParams_win));
		}
		else
		{
			//skip
		}
	} while (0);
	prev_split_mode = stParams.cvi_split_info.split_mode;
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get MVI source colorimetry information.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetMviColorimetry(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_MVI_COLORIMETRY_T stParams;
	LX_DE_MVI_COLORIMETRY_T *pstParams = (LX_DE_MVI_COLORIMETRY_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_MVI_COLORIMETRY;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_MVI_COLORIMETRY_T));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(LX_DE_MVI_COLORIMETRY_T));
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		ret = DE_HAL_GetMviColorimetry(&stParams);  // NULL
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief determine to make selected surface to turn On or Off
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetZList(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_ZLIST_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_ZLIST;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_ZLIST_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set display pannel formats which are pannel type and frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDisFmt(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_DIS_FMT_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DIS_FMT;
	LX_DE_FR_RATE_T frRate;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_Init(&stParams.panel_type);
		if (ret) break;
		ret = DE_HAL_GetFrRate(&frRate);
		if (ret) break;
		frRate.fr_rate = stParams.fr_rate;
		ret = DE_HAL_SetFrRate(&frRate);

#ifdef INCLUDE_KDRV_BE
		/* Set PWM frequency */
		{
			UINT32 pwmFreq;

			if (frRate.fr_rate == 25 || frRate.fr_rate == 50 || frRate.fr_rate == 100)
			{
				pwmFreq = 50;
			}
			else if (frRate.fr_rate == 48 || frRate.fr_rate == 96)
			{
				pwmFreq = 48;
			}
			else
			{
				pwmFreq = 60;
			}
			BE_PWM_HAL_SetPwmSync(pwmFreq);
		}
#endif
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set display frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetOutFrRate(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_FR_RATE_T stParams;
	LX_DE_FR_RATE_T *pstParams = (LX_DE_FR_RATE_T *)arg;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_GetFrRate(&stParams);
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set display pannel formats which are pannel type and frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetFrRate(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_FR_RATE_T stParams;
	UINT16 v_freq;
#ifdef USE_SUPPORT_EUROPE
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_FR_RATE;
#endif
	char opt[64];
	static UINT64 prev_msec_tick = 0;
	UINT64 curr_msec_tick = 0;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		v_freq = stParams.fr_rate;

		if(g_Diplay_type == LX_PANEL_TYPE_1920_120P || g_Diplay_type == LX_PANEL_TYPE_3840_120P)
		{
			v_freq = v_freq * 2;
			if(u16CHK_RANGE(v_freq,96,2))
				v_freq = 96;
			else if(u16CHK_RANGE(v_freq,100,2))
				v_freq = 100;
			else if(u16CHK_RANGE(v_freq,120,2))
				v_freq = 120;
			else
				v_freq = 120;
		}

		stParams.fr_rate = v_freq;

		curr_msec_tick = OS_GetMsecTicks();
		if(curr_msec_tick > (prev_msec_tick + 1000))
		{
			DE_NOTI("for %sHz model : freq = %d Hz\n", (v_freq>=96)?"120":"60", v_freq);

		}
		prev_msec_tick = curr_msec_tick;

#ifdef USE_SUPPORT_EUROPE
		CHECK_MCU_IPC();

		if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
		{
			#ifdef INCLUDE_KDRV_OVI
			LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
			
			if (RET_OK==OVI_HAL_GetHWDisplayOption(&ovi_opt))
			{
				if (ovi_opt.isDispForceFreerun) 
				{
					stParams.isForceFreeRun = 1;
				}
			}
			#endif
			if(RET_OK==OS_ScanKernelCmdline("disp=%s", opt))
			{
				if(strstr(opt,"hdmi"))
				{
					if(!strncmp(opt,"hdmi60",6))
					{
						DE_NOTI("setenv hdmi60 from bootloader\n");
					}
					else if(!strncmp(opt,"hdmi5060",8))
					{
						DE_NOTI("setenv hdmi5060 from bootloader\n");
					}
					else
					{
						DE_NOTI("setenv hdmi from bootloader\n");
					}
				}
			}
		}
		else
		{
			if(RET_OK==OS_ScanKernelCmdline("disp=%s", opt))
			{
				if(!strncmp(opt,"hdmi60",6))
				{  /* Vsync force freerun */
					stParams.isForceFreeRun = 1;
					stParams.fr_rate        = 60;
					DE_NOTI("Forced free-run by setenv hdmi60 from bootloader\n");
				}
				else if(!strncmp(opt,"hdmi5060",8))
				{  /* Vsync force freerun */
					stParams.isForceFreeRun = 1;
					DE_NOTI("Forced free-run by setenv hdmi5060 from bootloader\n");
				}
				else if(!strncmp(opt,"hdmi",4))
				{
					DE_NOTI("setenv hdmi from bootloader\n");
				}
			}
		}

		DE_NOTI("set_frate fr_rate:%d, isForceFreeRun:%d\n",stParams.fr_rate,stParams.isForceFreeRun);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
#endif
		ret = DE_HAL_SetFrRate(&stParams);

#ifdef INCLUDE_KDRV_BE
		/* Set PWM frequency */
		{
			UINT32 pwmFreq;

			if (stParams.fr_rate == 25 || stParams.fr_rate == 50 || stParams.fr_rate == 100)
			{
				pwmFreq = 50;
			}
			else if (stParams.fr_rate == 48 || stParams.fr_rate == 96)
			{
				pwmFreq = 48;
			}
			else
			{
				pwmFreq = 60;
			}
			BE_PWM_HAL_SetPwmSync(pwmFreq);
		}
#endif
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief de cvi video frame buffer freeze to read/write video frame before cvi csc parameter for self-diagnosis.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviFreeze(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CVI_CAPTURE_FREEZE_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_FREEZE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/* LGSI code restructing for the function "DE_IO_SetCviVideoFrameBuffer" */

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

/* Need to trace and remove the related code */

int DE_IO_SetCviVideoFrameBuffer(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_RegWr(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_REG_WR_T *pstParams = (LX_DE_REG_WR_T*)arg;
	LX_DE_REG_WR_T lReg;
	UINT32 msgCnt = sizeof(LX_DE_REG_WR_T);
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
	DE_IPC_CMD_T ipcCmd = DE_IPC_REG_WD;
#endif

	do {
		CP_FROM_USER(&lReg, (void *)(uintptr_t)pstParams, msgCnt,nFlag);
		ret = DE_HAL_WriteReg((void *)(uintptr_t)lReg.wr_addr, lReg.wr_data);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Read Register
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_RegRd(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 *pstParams = (UINT32*)arg;
	LX_DE_REG_WR_T lReg;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
	DE_IPC_CMD_T ipcCmd = DE_IPC_REG_RD;
#endif

	do {
		CP_FROM_USER(&lReg.wr_addr, (void *)pstParams, sizeof(UINT32),nFlag);
		ret = DE_HAL_ReadReg((void *)(uintptr_t)lReg.wr_addr, &lReg.wr_data);
		if (ret) BREAK_WRONG(ret);
		CP_TO_USER((void *)pstParams, &lReg.wr_data, sizeof(UINT32),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set deinterlace on/off control
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDeinterlace(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN  stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DEINTERLACE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
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
int DE_IO_SetUart4MCU(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN  stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_SetUart4MCU(stParams);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control de UD mode (on/off)
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetUDMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN  stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_UD_MODE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetUdMode(&stParams);
	} while (0);
	CHECK_IO_RET();
	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief set de CVE parameter.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCve(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CVE_PARAM_T  stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while(0);
	CHECK_IO_RET();
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
int DE_IO_SetVcs(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_VCS_IPC_T stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_SetVcs(&stParams);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_IO_FW_Download(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_FW_DWLD_T stParams;

	/* notify DE event */
	//if (g_DEListener) g_DEListener(0x0);

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(LX_DE_FW_DWLD_T),nFlag);
		ret = vsc_fw_io_download((void *)&stParams,nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief send captured video fir coef for double/quad sampling case.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviFir(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
#ifndef USE_DE_CVI_FIR_FROM_HAL
	LX_DE_CVI_FIR_T stParams;
#ifdef USE_DE_CVI_FIR_AT_MCU_PART
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_FIR;
#endif

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
#ifdef USE_DE_CVI_FIR_AT_MCU_PART
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
#else
		ret = DE_HAL_SetCviFir(&stParams);
#endif
	} while (0);
#endif // #ifndef USE_DE_CVI_FIR_FROM_HAL
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video test pattern generator to black.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviTpg(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CVI_TPG_T stParams;
#ifdef USE_DE_CVI_TPG_AT_MCU_PART
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_TPG;
#endif

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
#ifdef USE_DE_CVI_TPG_AT_MCU_PART
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
#else
		ret = DE_HAL_SetCviTpg(&stParams);
#endif
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set  video test pattern.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetTestPattern(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SET_DBG_T stParams;
	LX_DE_PATTERN_T pattern;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_PATTERN;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams), nFlag);
		memcpy(&pattern, &stParams.pattern, sizeof(LX_DE_PATTERN_T));
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &pattern, sizeof(pattern));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set  interlace scanmode.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetScanMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SCAN_MODE_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DEINTERLACE;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams), nFlag);
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_SetPixelToPixel(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_PIXELTOPIXEL;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams), nFlag);
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;

}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video color sampling mode(sub sampling or 3 tap filtering).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviCsampleMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CSAMPLE_MODE_T stParams;
#ifdef USE_DE_CVI_CSAMPLE_AT_MCU_PART
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_CSAMPLE_MODE;
#endif

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
#ifdef USE_DE_CVI_CSAMPLE_AT_MCU_PART
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
#else
		ret = DE_HAL_SetCviCsampleMode(&stParams);
#endif
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set dvr control.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDvrFmtCtrl(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_DVR_DISFMT_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DVR_FMT_CTRL;

	do {
		CHECK_MCU_IPC();
		do{
			CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams), nFlag);
		}while(0);
		if(ret) memcpy(&stParams, (void *)arg, sizeof(LX_DE_DVR_DISFMT_T)); // copy from user pointer
#ifdef INCLUDE_KDRV_VENC
		stParams.baseAddr = (gpstVencMemConfig)?gpstVencMemConfig->uiInBufBase:0x0;
#endif
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set frame caputuring mode On or Off.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSubScFreeze(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SUB_SC_FREEZE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select source for multi window.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SelectMultiWinSrc(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_MULTI_WIN_SRC_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SELECT_MULTI_WIN_SRC;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SelectMultiWinSrc(&stParams);
		if (ret) break;
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select between SCART RGB bypass mode and CVD overlay mode
 *
 * @param arg [IN] bypass enable/disable
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetScartRGBBypassMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	int Enable;

	do {
		CP_FROM_USER(&Enable, (void *)arg, sizeof(int),nFlag);
		//ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		//if (ret) break;
		ret = DE_HAL_SetSCARTRGBBypassMode(&Enable);
		if (ret) break;
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get debug data.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetDebug(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SET_DBG_T stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_GetDebug(&stParams);
		if (ret) break;
		CP_TO_USER((void *)arg, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set debug data.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDebug(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SET_DBG_T stParams;
#ifdef USE_DE_CVI_DELAY_ON_MCU_PART
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_DELAY;
#endif

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
#ifdef USE_DE_CVI_DELAY_ON_MCU_PART
		CHECK_MCU_IPC();
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
#endif
		ret = DE_HAL_SetDebug(&stParams);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set low delay mode for frame delay
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetLowDelay(unsigned long arg,unsigned int nFlag)
{
    int ret = RET_OK;
    UINT32 stParams;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_LOW_DELAY;

    do {
		CHECK_MCU_IPC();
        CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
        ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
    } while (0);
	CHECK_IO_RET();
    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get low delay mode for frame delay
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetLowDelay(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_LOW_DELAY_T stParams;
	LX_DE_LOW_DELAY_T *pstParams = (LX_DE_LOW_DELAY_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_LOW_DELAY;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(stParams));
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set inforamtion for Multi vision
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetMultiVision(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_RECT_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_MULTI_VISION;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set information for video to memory
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */

struct vtm_req_process{
	struct list_head list;
	pid_t   pid;
};

LIST_HEAD(vtm_plist_head);

#define SEND_NEW_VTG_IPC

static int g_cma_alloc = 0;
static int g_vtbuf_count = 0;
void DE_IO_MaskControl(int flag)
{
	g_cma_alloc = flag;
}

int DE_IO_ReleaseVTM(unsigned long arg)
{
	int ret = RET_OK;
	struct vtm_req_process *pReqProcess;
	pid_t pidNew;
	int found = 0;
	//LX_DE_VTG_INFO_T stParams_new;
	//DE_IPC_CMD_T ipcCmd_new_vtg = DE_IPC_GET_FRAME_FOR_WEBOS;

	pidNew = task_tgid_vnr(current);
	//DE_NOTI("check capture process  pidNew = %d", pidNew);

	list_for_each_entry(pReqProcess, &vtm_plist_head, list)
	{
		if(pReqProcess== NULL) return -1;

		if(pReqProcess->pid == pidNew)
		{
			found = 1;
			DE_WARN("found uncompleted capture process...");
			break;
		}
	}

	if(found == 1)
	{
#ifdef USE_1_DEDICATED_VT_BUFFER

#else
#if 0
		// delete from list
		list_del(&pReqProcess->list);
		// capture off
		stParams_new.enable = 0;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd_new_vtg), &stParams_new, sizeof(stParams_new));
		// cma/hma free
		msleep(30);  // wait until last pic init
		ret |= DE_HAL_GetMemFromCma("de-vtgbuffer", g_vtbuf_count, 0); // hma free
		if(ret) DE_ERROR("cma free fail.");

		DE_NOTI("delete list & free cma/hma & capture off");
#else
		ret = DE_HAL_GetMemFromCma("de-vtgbuffer", g_vtbuf_count, NULL, 0); // hma free
		DE_NOTI("hma free only");
#endif
#endif // #ifdef USE_1_DEDICATED_VT_BUFFER
	}

	return ret;
}

int DE_IO_SetVTM(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	struct vtm_req_process *pReqProcess;
	int found = 0;
	pid_t pidNew;
	LX_DE_VTM_FRAME_INFO_T stParams;
	LX_DE_VTM_FRAME_INFO_T *p = NULL;
	LX_DE_VTM_FRAME_INFO_T *pstParams = (LX_DE_VTM_FRAME_INFO_T*)arg;
#ifdef SEND_NEW_VTG_IPC
	//DE_IPC_CMD_T ipcCmd_new_vtg = DE_IPC_SET_VTG;
	DE_IPC_CMD_T ipcCmd_new_vtg = DE_IPC_GET_FRAME_FOR_WEBOS;
	LX_DE_VTG_INFO_T stParams_new = { 0 };
#else
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_FRAME_FOR_WEBOS;
#endif
	char *p_shared_mem = NULL;
	LX_DE_VTM_FRAME_INFO_T *p_shared_mem_from_mcu = NULL;
	int vtm_ready_count = 100;
	int skip_condition = 0;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		CP_FROM_USER(&gVtmParams, (void *)arg, sizeof(stParams),nFlag);
		//pidNew = (pid_t)stParams.address; /*Get pidNew(address) before overwritten by DE_HAL_SetVTM*/
		pidNew = task_tgid_vnr(current);
		//DE_NOTI("pidNew = %d", pidNew);
		ret = DE_HAL_SetVTM(&stParams);
		if (ret) BREAK_WRONG(ret);
		p_shared_mem = vmap_phys(stParams.address, \
				sizeof(LX_DE_VTM_FRAME_INFO_T));
		p_shared_mem_from_mcu = (LX_DE_VTM_FRAME_INFO_T*)vmap_phys(stParams.address + sizeof(LX_DE_VTM_FRAME_INFO_T), \
				sizeof(LX_DE_VTM_FRAME_INFO_T));
		memset(p_shared_mem_from_mcu, 0, sizeof(LX_DE_VTM_FRAME_INFO_T));
		if(p_shared_mem == NULL) BREAK_WRONG(ret);
		if(p_shared_mem_from_mcu == NULL) BREAK_WRONG(ret);
		list_for_each_entry(pReqProcess, &vtm_plist_head, list)
		{
			if(pReqProcess->pid == pidNew)
			{
				found = 1;
				break;
			}
		}
		if(stParams.enable != 0)
		{
			LX_DE_VTM_FRAME_INFO_T stParams_buffer_info;

			if(found == 0)
			{
				pReqProcess = NULL;
				pReqProcess = (struct vtm_req_process *)kmalloc(sizeof(struct vtm_req_process), GFP_KERNEL);
				if(pReqProcess != NULL)
				{
					pReqProcess->pid = pidNew;
					list_add(&pReqProcess->list, &vtm_plist_head);   // ==>
				}
			}
			memset(p_shared_mem, 0, sizeof(LX_DE_VTM_FRAME_INFO_T));
			if(DE_HAL_GetVTM(&stParams_buffer_info) != 0) DE_ERROR("get external buffer fail.");
			p = (LX_DE_VTM_FRAME_INFO_T *)p_shared_mem;
			memcpy((void *)p, (void *)&stParams, sizeof(LX_DE_VTM_FRAME_INFO_T));
			p->isSecure = 0xFF;
			p->y_frame[0] = stParams_buffer_info.address;
			p = (LX_DE_VTM_FRAME_INFO_T *)p_shared_mem_from_mcu;
			memcpy((void *)p, (void *)&stParams, sizeof(LX_DE_VTM_FRAME_INFO_T));
			p->y_frame[0] = 0;
			p->isSecure = 0xFF;
			p->ext_info.w_out_size.x = 0;
			p->ext_info.w_out_size.y = 0;
			p->ext_info.w_out_size.w = 480;
			p->ext_info.w_out_size.h = 270;
			p = (LX_DE_VTM_FRAME_INFO_T *)p_shared_mem;
			DE_NOTI("buffer count = %d", p->reserved);
			g_vtbuf_count = p->reserved;
			stParams.y_frame[0] = stParams_buffer_info.y_frame[0];
			stParams.c_frame[0] = stParams_buffer_info.c_frame[0];
#ifdef		USE_1_DEDICATED_VT_BUFFER
#else
			if(stParams_buffer_info.address && (g_vtbuf_count<=3) && (p->ext_info.frc_mode==0))
			{
				ret = DE_HAL_GetMemFromCma("de-vtgbuffer", g_vtbuf_count, NULL, 1); // alloc for capture buffer
				if(g_cma_alloc) ret = 1;
				if(ret) DE_ERROR("cma alloc fail.");
			}
#endif
			if(stParams.location == 0 && (stParams.ext_info.crop_size.w == 0 || stParams.ext_info.crop_size.h == 0))
			{
				DE_NOTI("skip ipc.. loc[src] w/h[%d/%d]\n", stParams.ext_info.crop_size.w, stParams.ext_info.crop_size.h);
				skip_condition = 1;
			}
			else
			{
#ifdef		USE_1_DEDICATED_VT_BUFFER
				stParams_new.enable  = stParams.enable;
				stParams_new.address = stParams.address;
				ret = MCU_Write(DE_PACK_CMD(ipcCmd_new_vtg), &stParams_new, sizeof(stParams_new));
#else
				if(!ret)
				{
					stParams_new.enable  = stParams.enable;
					stParams_new.address = stParams.address;
					ret = MCU_Write(DE_PACK_CMD(ipcCmd_new_vtg), &stParams_new, sizeof(stParams_new));
				}
				else
				{// return error to kadp
					int i;
					LX_DE_VTM_FRAME_INFO_T *p2 = NULL;
					p2 = vmap_phys(stParams.address + sizeof(LX_DE_VTM_FRAME_INFO_T), sizeof(LX_DE_VTM_FRAME_INFO_T));
					p2->stride = 480;
					for(i=0;i<MAX_VTG_BUFFER;i++)
					{
						p2->y_frame[i] = stParams.y_frame[0] + i*0x100000;
						p2->c_frame[i] = stParams.c_frame[0] + i*0x100000;
					}
					p2->c_frame[2] = p2->y_frame[0]; // set same address of index 0 & 2   to inform RET_ERROR
					DE_ERROR("return no memory...  p2->y_frame[0] = 0x%08x", p2->y_frame[0]);
					vunmap_phys(p2);
					ret = 0;
				}
#endif
			}
		}
		else
		{
			p = (LX_DE_VTM_FRAME_INFO_T *)p_shared_mem;

			if(found == 1)
			{
				list_del(&pReqProcess->list);
				kfree(pReqProcess);
			}
			if(list_empty(&vtm_plist_head))
			{
				p->enable = 0;
			#ifdef SEND_NEW_VTG_IPC
				stParams_new.enable = stParams.enable;
				ret = MCU_Write(DE_PACK_CMD(ipcCmd_new_vtg), &stParams_new, sizeof(stParams_new));
			#else
				ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
			#endif
#ifdef		USE_1_DEDICATED_VT_BUFFER
#else
				msleep(30);  // wait until last pic init
				if(g_vtbuf_count<=3 && (p->ext_info.frc_mode==0))
				{
					ret = DE_HAL_GetMemFromCma("de-vtgbuffer", g_vtbuf_count, NULL, 0); // free for capture buffer
					if(ret) DE_ERROR("cma free fail.");
				}
#endif
			}
		}
		if (ret) BREAK_WRONG(ret);

		if(stParams.enable && (skip_condition == 0))
		{
			while(vtm_ready_count-- > 0)
			{
				if(p_shared_mem_from_mcu->y_frame[0] != 0 && p_shared_mem_from_mcu->y_frame[0] != 0xFFFFFFFF) break;
				OS_MsecSleep(10);
			}
			if(vtm_ready_count <= 0)
			{
				DE_WARN("no input (mcu y_frame[0]=0x%08x), free memory \n", p_shared_mem_from_mcu->y_frame[0]);
				if(pReqProcess != NULL)
				{
					list_del(&pReqProcess->list);
					kfree(pReqProcess);
				}
				stParams_new.enable = 0;
				ret = MCU_Write(DE_PACK_CMD(ipcCmd_new_vtg), &stParams_new, sizeof(stParams_new));
#ifdef		USE_1_DEDICATED_VT_BUFFER
#else
				if(g_vtbuf_count<=3 && (p->ext_info.frc_mode==0))
				{
					ret |= DE_HAL_GetMemFromCma("de-vtgbuffer", g_vtbuf_count, NULL, 0); // hma free
					if(ret) DE_ERROR("cma free fail.");
				}
#endif
			}
			DE_TRACE("VTM ready count [%d] remains\n", vtm_ready_count);
		}

		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);
	if(p_shared_mem) vunmap_phys(p_shared_mem);
	if(p_shared_mem_from_mcu) vunmap_phys(p_shared_mem_from_mcu);
	CHECK_IO_RET();
	return ret;
}


int DE_IO_ResetVTM(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	struct vtm_req_process *pReqProcess, *pReqNext;

	if(arg == 0 /*suspend*/)
	{
		/*release buffers allocated for linkedlist if remains : caused by start/stop mismatch from upper layer*/
		list_for_each_entry_safe(pReqProcess, pReqNext, &vtm_plist_head, list)
		{
			list_del(&pReqProcess->list);
			kfree(pReqProcess);
		}
	}
	else if(arg == 1 /*resume*/)
	{
		/*currently(2015.06.02), this function called when resume from suspend. so release buffers here.*/
		list_for_each_entry_safe(pReqProcess, pReqNext, &vtm_plist_head, list)
		{
			list_del(&pReqProcess->list);
			kfree(pReqProcess);
		}
		/*init linked list for sure.*/
		INIT_LIST_HEAD(&vtm_plist_head);
	}

	return ret;
}

int DE_IO_GetFPPInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_FPP_INFO;

	do {
		CHECK_MCU_IPC();

		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));

		DE_HAL_GetFPPInfo(&stParams);
		CP_TO_USER((void *)arg, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_GetMEMInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_MEM_SYS_INFO_T stParams;

	do {
		memset(&stParams, 0, sizeof(LX_DE_MEM_SYS_INFO_T));
		ret = DE_HAL_GetMEMInfo(&stParams);
		CP_TO_USER((void *)arg, &stParams, sizeof(LX_DE_MEM_SYS_INFO_T),nFlag);
		//DE_NOTI("0x%08x/0x%08x/0x%08x/0x%08x", stParams.de_frm_m1.base, stParams.de_frm_m1.size, stParams.de_frm_m2.base, stParams.de_frm_m2.size);
		if((stParams.de_frm_m1.base + stParams.de_frm_m2.base) == 0)
		{
			DE_NOTI("frame buffer is not accocated yet.");
			ret = RET_ERROR;
		}
	} while (0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_GetTimeDiff(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 stParams;

	do {
		CHECK_MCU_IPC();
		memset(&stParams, 0, sizeof(UINT32));
		ret = DE_HAL_GetTimeDiff(&stParams);
		CP_TO_USER((void *)arg, &stParams, sizeof(UINT32),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_GetVideoDelay(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_VIDEO_DELAY_INFO_MEM_T stParams;
	LX_DE_CB_INFO_T cb_info;

	do {
		CHECK_MCU_IPC();
		memset(&stParams, 0, sizeof(LX_DE_VIDEO_DELAY_INFO_MEM_T));
		ret = DE_HAL_GetVideoDelay(&stParams);

		cb_info.video_delay_info[0] = stParams.win[0];
		cb_info.video_delay_info[1] = stParams.win[1];
		cb_info.video_delay_info[2] = stParams.win[2];
		cb_info.video_delay_info[3] = stParams.win[3];
		cb_info.owin_sync = stParams.owin_sync;
		cb_info.sys_time_diff = 0;
		CP_TO_USER((void *)arg, &cb_info, sizeof(LX_DE_CB_INFO_T),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get information for video to memory
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetVTM(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_VTM_FRAME_INFO_T stParams;

	do {
		DE_HAL_GetVTM(&stParams);
		CP_TO_USER((void *)arg, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set/get VTM block state for each window
 *
 * @param arg [IN] window id & cmd type {set|get}
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetVTMBlockState(unsigned long arg,unsigned int nFlag)
{
	static UINT32 winBlockState[LX_DE_WIN_MAX]={0, 0, 0, 0};
	int ret = RET_OK;
	LX_DE_VTM_BLOCK_STATE_T stParams;
	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);

		if(stParams.win_id >= LX_DE_WIN_MAX)
		{
			ret = RET_INVALID_PARAMS;
			break;
		}

		if(stParams.cmd == 0) /*Get*/
		{
			stParams.VTMBlock = winBlockState[stParams.win_id];
		}
		else if(stParams.cmd == 1) /*Set*/
		{
			winBlockState[stParams.win_id] = stParams.VTMBlock;
		}
		CP_TO_USER((void *)arg, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

typedef struct {
	UINT32		address;
	BOOLEAN		enable;
}
GCP_CNTL_T;
UINT32 ipc_error_sim = 0;

int DE_IO_SetGeneralCapturePath(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

	LX_DE_GCP_INFO_T stParams;
	LX_DE_GCP_INFO_T *p_1, *p_2;
	LX_DE_GCP_INFO_T *pstParams = (LX_DE_GCP_INFO_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_GCP_MODE;
	char *p_shared_mem = NULL;

	int pid;
	pid = task_tgid_vnr(current);

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		_g_gcp_mode = (BOOLEAN)stParams.enable;
		ret = DE_HAL_SetGeneralCapturePath(&stParams);
		if (ret) BREAK_WRONG(ret);
		p_shared_mem = vmap_phys(stParams.address, \
				sizeof(LX_DE_GCP_INFO_T)*2);
		if(p_shared_mem == NULL) BREAK_WRONG(ret);

		if(stParams.frz & 0x0002)
		{
			DE_NOTI("skip send IPC....\n");
			stParams.frz &= 0xFFFD;
		}
		else
		{
			if(stParams.enable == 1)
			{
				_g_gcp_enable_count++;
				if(_g_gcp_enable_count > 1)
				{
					DE_NOTI("GCP is already enable\n");
					break;
				}
	//			ret = DE_HAL_GetMemFromCma("de-vtgbuffer", 1, 1); // alloc for General Captyre Path usgin 4k VT buffer
	//			if(ret != 0) break;
			}
			else
			{
				if(_g_gcp_enable_count == 1)
				{
					_g_gcp_enable_count--;
				}
				else if(_g_gcp_enable_count > 1)
				{
					DE_NOTI("GCP is used by other process\n");
					_g_gcp_enable_count--;
					break;
				}

				if(_g_gcp_enable_count < 0)
				{
					_g_gcp_enable_count = 0;
				}
			}

			DE_NOTI("send IPC....  phys[ 0x%08X ] input buf info[%d]\n", stParams.address, stParams.reserved[0]);
			p_1 = (LX_DE_GCP_INFO_T *)p_shared_mem;
			p_1->mute = 1;
			p_2 = (LX_DE_GCP_INFO_T *)(p_shared_mem + sizeof(LX_DE_GCP_INFO_T));
			p_2->mute = 1; // set local mute (mcu2arm)
#if 1
			{
				GCP_CNTL_T cmd/*, verify*/;
				cmd.address = stParams.address;
				cmd.enable  = stParams.enable;
				if(stParams.enable == 1 && stParams.reserved[0] == 1)
				{
					cmd.enable = 2; // input buffer info
				}

				ipcCmd = DE_IPC_SET_GCP_MODE;
				if(ipc_error_sim)
					ret = MCU_Write(DE_PACK_CMD(0x12340000), &cmd, sizeof(cmd)); // send invalid ipc cmd
				else
					ret = MCU_Write(DE_PACK_CMD(ipcCmd), &cmd, sizeof(cmd));
				if (ret) {DE_NOTI("error !\n");}
				#if 0
				ret = MCU_Read(0, &verify, sizeof(verify));
				if(verify.address != stParams.address || verify.enable != stParams.enable)
				{
					DE_NOTI("retry to send ipc cmd [address:%x, enable:%d]!\n", verify.address, verify.enable);
					ret = MCU_Write(DE_PACK_CMD(ipcCmd), &cmd, sizeof(cmd)); // send valid ipc cmd
					ret |= MCU_Read(0, &verify, sizeof(verify));
					DE_NOTI("MCU_Read [address:%x, enable:%d]!\n", verify.address, verify.enable);
				}
				#endif
			}
#else
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
#endif
			if (ret) BREAK_WRONG(ret);

			if(stParams.enable >= 1) // when GCP ON, force to scaler freeze off & multi_win off
			{ // GCP off 이후에 이 코드가 위치한 이유 = local mute가 먼저 걸려야함. 그렇지 않을 경우에 라이브줌 UI만 장시간 노출됨.
				LX_DE_WIN_FREEZE_T stParams_freeze;
				BOOLEAN stParams_multi_win;
				LX_DE_SUB_MODE_T stParams_sub_mode;
				if(_g_freeze_status)
				{
					stParams_freeze.win_id = 0;
					stParams_freeze.bEnable = 0;
					stParams_freeze.location = LX_DE_FREEZE_DISP;
					ipcCmd = DE_IPC_SET_WIN_FREEZE;
					ret |= MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_freeze, sizeof(stParams_freeze));
					_g_freeze_status = FALSE;

					stParams_multi_win = FALSE;
					ipcCmd = DE_IPC_MULTI_WIN_ENALBE;
					ret |= MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_multi_win, sizeof(stParams_multi_win));

					stParams_sub_mode = LX_DE_SUB_MODE_NONE;
					ipcCmd = DE_IPC_SET_SUB_MODE;
					ret |= MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_sub_mode, sizeof(stParams_sub_mode));

					DE_NOTI("VTV W/A : freeze off & close sub path");
				}
			}
			if (ret) BREAK_WRONG(ret);
		}
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);

	DE_NOTI("pid[%d] _g_gcp_enable_count [%d]\n", pid, _g_gcp_enable_count);

	if(p_shared_mem) vunmap_phys(p_shared_mem);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D input/output control (onoff, format, lr order)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 **/
int DE_IO_Set3DInOutCtrl(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_3D_INOUT_CTRL_T stParams; // 20130327,  check this with mcu's kapi !!!
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_INOUT_CTRL;
	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(FMT3D_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
	} while (0);
	CHECK_IO_RET();
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
int DE_IO_SetInterfaceConfig(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_IF_CONFIG_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_IF_CONFIG;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetInterfaceConfig(&stParams);
		if (ret) break;
	} while (0);
	CHECK_IO_RET();
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
int DE_IO_GetSystemStatus(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SYS_STATUS_T stParams;
	LX_DE_SYS_STATUS_T *pstParams = (LX_DE_SYS_STATUS_T *)arg;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_GetSystemStatus(&stParams);
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);
	CHECK_IO_RET();
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
int DE_IO_GetSourceStatus(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SRC_STATUS_T stParams;
	LX_DE_SRC_STATUS_T *pstParams = (LX_DE_SRC_STATUS_T *)arg;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_GetSourceStatus(&stParams);
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);
	CHECK_IO_RET();
	return ret;
}



/**
 * @callgraph
 * @callergraph
 *
 * @brief Set operation infomation
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetOperation(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_OPERATION_CTRL_T stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_SetOperation(&stParams);
		if (ret) break;
	} while (0);
	CHECK_IO_RET();
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
int DE_IO_SetSubOperation(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SUB_OPERATION_CTRL_T stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_SetSubOperation(&stParams);
		if (ret) break;
	} while (0);
	CHECK_IO_RET();
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
int DE_IO_SetCaptureControl(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CAPTURE_CTRL_T stParams;
	LX_DE_CAPTURE_CTRL_T *pstParams = (LX_DE_CAPTURE_CTRL_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CAPTURE;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		//		ret = DE_HAL_SetCaptureControl(&stParams);
		//		if (ret) break;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(stParams));
		if (ret) break;
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get scaler info
 *
 * @param arg [IN] win idx
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetScalerInfo(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SCALER_INFO_T stParams;
	LX_DE_SCALER_INFO_T *pstParams = (LX_DE_SCALER_INFO_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_SCALER_INFO;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));
		if (ret) break;
		ret = MCU_Read(0, &stParams, sizeof(stParams));
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set inner pattern
 *
 * @param arg [IN] pattern information
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetInnerPattern(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_INNER_PATTERN_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_INNER_PATTERN;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_INNER_PATTERN_T));
	} while (0);
	CHECK_IO_RET();
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
#ifdef INCLUDE_KDRV_APR
// 20130222 maybe, this is unnecessary because of mute-control
#include "../apr/apr_core.h"
#endif

int DE_IO_SetWinPortSrc(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_INPUT_SOURCE_T stParams;
	LX_DE_INPUT_CFG_T stParams1; // old structure
	LX_DE_GCP_INFO_T stParams_hdr;
	LX_DE_WIN_INFO_T stParams_win;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_WIN_PORT_SRC;
#ifdef INCLUDE_KDRV_APR
	LX_APR_CONTROL_T aprParams;
#endif
	mutex_lock(&vsc_mutex_lock0);
	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);

		if(stParams.srcId == LX_DE_WIN_MAIN && stParams.srcType == LX_DE_IN_SRC_NONE && _g_gcp_mode == TRUE)
		{
			_g_gcp_enable_count = 0;
			stParams_hdr.enable = 0;
			ipcCmd = DE_IPC_SET_GCP_MODE;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_hdr, sizeof(LX_DE_GCP_INFO_T));
			if (ret) break;
		}

		if(stParams.srcId == LX_DE_WIN_MAIN && (stParams.srcType > LX_DE_IN_SRC_NONE && stParams.srcType < LX_DE_IN_SRC_MVI))
		{
			DE_IPC_CMD_T ipcCmd_bt = DE_IPC_SET_FRAME_DELAY;
			UINT32 prev_pool_base, prev_pool_size;
			DE_NOTI("=> enter allocate_ext_buf with mutex-lock");

			prev_pool_base = prev_bt_cfg.pool_base[0];
			prev_pool_size = prev_bt_cfg.pool_size[0];
			ret = DE_HAL_GetMemFromCma("de-btbuf", 1, &prev_bt_cfg, 1); // alloc (hdmi only)
			if(ret) {
				DE_ERROR("alloc fail. use default value. base/size[0x%x/0x%x]", prev_pool_base, prev_pool_size);
				prev_bt_cfg.pool_base[0] = prev_pool_base;
				prev_bt_cfg.pool_size[0] = prev_pool_size;
			}
			//if (lx_chip_rev() >= LX_CHIP_REV( E60, A0)) {
			if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) {
				if(prev_bt_cfg.ubuffer == 0) {
					prev_bt_cfg.ubuffer = 1;
					DE_NOTI("E60 only : bt_cfg.ubuffer(0) is forced to 1 from SetWinPortSrc");
				}
			}
			ret = MCU_Write(DE_PACK_CMD(ipcCmd_bt), &prev_bt_cfg, sizeof(LX_DE_SET_DELAY_BUFFER_T));
			DE_NOTI("=> leave allocate_ext_buf");
		}

		stParams1.win_id       = stParams.srcId;
		stParams1.inputSrc     = stParams.srcType;
		stParams1.inputSrcPort = stParams.srcPort;
		stParams1.inputResv    = stParams.srcAttr;
		ret = DE_HAL_SetWinPortSrc(&stParams1);
		if (ret) break;
		ipcCmd = DE_IPC_SET_WIN_PORT_SRC;
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(stParams));

		// init in-out window & sub window only (overlay miracast w/a : QEVENTTWEN-6442)
		if(stParams.srcType==LX_DE_IN_SRC_NONE && stParams.srcId==1) {
			memset(&stParams_win, 0, sizeof(LX_DE_WIN_INFO_T));
			stParams_win.wId = (LX_DE_WIN_ID_T)stParams.srcId;
			ipcCmd = DE_IPC_SET_WIN_INFO;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_win, sizeof(stParams_win));
		}

		if(stParams.srcId == LX_DE_WIN_MAIN && stParams.srcType == LX_DE_IN_SRC_NONE)
		{
			if(prev_input_src.srcType < LX_DE_IN_SRC_MVI) {
				prev_bt_cfg.pool_size[0] = 0;

				/* SDOSTC-975 */
				if (lx_chip_rev() >= LX_CHIP_REV( E60, A0)) {
					ret = MCU_Write(DE_PACK_CMD(DE_IPC_SET_FRAME_DELAY), &prev_bt_cfg, sizeof(LX_DE_SET_DELAY_BUFFER_T));
					DE_NOTI("send DE_IPC_SET_FRAME_DELAY [0x%x/0x%x]",prev_bt_cfg.pool_base[0],prev_bt_cfg.pool_size[0]);
					msleep(40);
					if (ret)	break;
				}

				DE_NOTI("=> enter free_ext_buf");
				ret = DE_HAL_GetMemFromCma("de-btbuf", 1, &prev_bt_cfg, 0); // free

				/* 20210928, moved here, keep base and set size zero (fw req.) */
				prev_bt_cfg.pool_base[0] = 0;

				DE_NOTI("=> leave free_ext_buf");
			}
		}

		if(stParams.srcId==LX_DE_WIN_MAIN)
			memcpy(&prev_input_src, &stParams, sizeof(stParams));

		if(stParams.srcId == 0 && stParams.srcType == 0)
			prev_split_mode = 0;
#ifdef INCLUDE_KDRV_APR
		aprParams.cmd     = 1;
		aprParams.sel_alg = 1;
		aprParams.cap_enb = 0;
		aprParams.fd3_enb = 1;
		aprParams.fmt     = 0;
		APR_Core_SetControl(&aprParams);
#endif
	} while (0);
	mutex_unlock(&vsc_mutex_lock0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Determine to make selected window Freeze or Not with location info
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetWinFreeze(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_WIN_FREEZE_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_WIN_FREEZE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		if(stParams.win_id == LX_DE_WIN_MAIN)
		{
			_g_freeze_status = stParams.bEnable;
		}
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_WIN_FREEZE_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief verify firmware from ddr memory
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_VerifyFirmware(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

	do {
		ret = DE_HAL_VerifyFirmware();
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set mirror output to denc (for scart-out)
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSrcMirror(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SRC_MIRROR_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SRC_MIRROR;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SRC_MIRROR_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set actual format detecting (for seamless switching with external specific input)
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetActFmtDetect(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_ACT_FORMAT_T stParams;
	BOOLEAN  ud_mode = FALSE;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_ACT_FMT_DETECT;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_ACT_FORMAT_T));
		if(stParams.enable == 3) // amazon mode
			ud_mode = TRUE;
		ret = DE_HAL_SetUdMode(&ud_mode);
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set hdmi port for window
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetHDMIPort(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_HDMIPORT_T stParams;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_SetHDMIPort(&stParams);
		if (ret) break;
	} while (0);
	CHECK_IO_RET()
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get capacity of chip
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetCapacity(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_CAPACITY_T stParams;
	LX_DE_CAPACITY_T *pstParams = (LX_DE_CAPACITY_T *)arg;

	do {
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = DE_HAL_GetCapacity(&stParams);
		if (ret) break;
		stParams.user_bin_num = vsc_fw_get_user_bin_num();
		CP_TO_USER((void *)pstParams, &stParams, sizeof(stParams),nFlag);
		if (ret) BREAK_WRONG(ret);
	} while (0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set sub-window index (0 : main or ignore, equal or greater than 1 : sub window)
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSubWindow(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SET_SUB_WIN_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_MULTI_WIN;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SET_SUB_WIN_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get local mute register
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetLocalMuteValue(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 stParams;

	do {
		CHECK_MCU_IPC();
		ret = DE_HAL_GetLocalMuteValue(&stParams);
		*(UINT32*)arg = stParams;
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set frame delay
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetFrameDelay(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SET_DELAY_BUFFER_T stParams;
	LX_DE_SET_DELAY_BUFFER_T buf_info;
	static LX_DE_SET_DELAY_BUFFER_T stParams_prev = { 0 };
	LX_DE_SET_WIN_BLANK_T stParams_mute;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_FRAME_DELAY;
	int enable_mute = 0;

	stParams_mute.isRGB = 0;
	stParams_mute.win_color.r = 128;
	stParams_mute.win_color.g = 0;
	stParams_mute.win_color.b = 128;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);

		if(stParams_prev.ubuffer != stParams.ubuffer)
			enable_mute = TRUE;
		else
			break;

		DE_NOTI("global_mute_status[%d]", global_mute_status[0]);
		if((global_mute_status[0] == 0) && enable_mute) {
			stParams_mute.bEnable = 1;  // global  mute on
			stParams_mute.win_id = 0;
			ipcCmd = DE_IPC_SET_WIN_BLANK;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_mute, sizeof(LX_DE_SET_WIN_BLANK_T));
		}

		if(stParams.ubuffer > 0 && stParams_prev.ubuffer == 0)
		{
			memset(&buf_info, 0, sizeof(LX_DE_SET_DELAY_BUFFER_T));
			//ret = DE_HAL_GetMemFromCma("de-btbuf", 1, &buf_info, 1); // alloc for BT speaker delay
			if(ret != 0) break;
		}
		ipcCmd = DE_IPC_SET_FRAME_DELAY;
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60)) {
			if(stParams.ubuffer == 0) {
				stParams.ubuffer = 1;
				DE_NOTI("E60 only : bt_cfg.ubuffer(0) is forced to 1 from SetFrameDelay");
			}
			else if(stParams.ubuffer == 1) {
				stParams.ubuffer = 2;
			}
			else if(stParams.ubuffer >= 2) {
				stParams.ubuffer = 3;
			}
		}
		if(stParams.ubuffer > 3)
			stParams.ubuffer = 3;
		stParams.pool_base[0] = prev_bt_cfg.pool_base[0];
		stParams.pool_size[0] = prev_bt_cfg.pool_size[0];
		ret |= MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SET_DELAY_BUFFER_T));

		msleep(34);
		if(stParams.ubuffer == 0) {
			//ret |= DE_HAL_GetMemFromCma("de-btbuf", 1, &buf_info, 0); // free
		}
	} while(0);
	CHECK_IO_RET();

	if((global_mute_status[0] == 0) && enable_mute) {
		DE_NOTI("mute off from bt delay control , global_mute_status[off]");
		stParams_mute.bEnable = 0;  // global  mute off
		stParams_mute.win_id = 0;
		ipcCmd = DE_IPC_SET_WIN_BLANK;
		ret |= MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_mute, sizeof(LX_DE_SET_WIN_BLANK_T));
	}

	stParams_prev.win_id = stParams.win_id;
	stParams_prev.ubuffer= stParams.ubuffer;
	prev_bt_cfg.win_id = stParams.win_id;
	prev_bt_cfg.ubuffer = stParams.ubuffer;

	DE_NOTI("_ext_buf delay[%d] prev_bt_cfg.pool_base[0] = 0x%08x", \
		prev_bt_cfg.ubuffer, prev_bt_cfg.pool_base[0]);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set sub window mode (0:PIP, 1:PBP)
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSubMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SUB_MODE_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SUB_MODE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		if (lx_chip_rev() < LX_CHIP_REV( M17, C0)) // for gld4tv
		{
			if(stParams > LX_DE_SUB_MODE_NONE)
			{
				stParams--;
			}
		}
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SUB_MODE_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set sub shape (0:CIRCLE,1:RECT, ORG SIZE:w/h)
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSubShape(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SUB_SHAPE_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SUB_SHAPE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SUB_SHAPE_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set size of source & input window
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSourceSizeWin(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_SOURCE_SIZE_WIN_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SOURCE_SIZE_INFO;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_SOURCE_SIZE_WIN_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set fcw initial value
 *
 * @param arg [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_InitFCW(unsigned long arg,unsigned int nFlag)
{
#define DCO_IN_CLK(npc,nsc)			((UINT32)24*((4*(npc))+(nsc))/12)
#define DCO_FCW(npc,nsc)			((UINT32)27*(1<<23)/(DCO_IN_CLK(npc,nsc)))
	int ret = RET_OK;
	UINT32 regVal = 0;
	LX_DE_PANEL_TYPE_T stParams;

	do {
		if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) )
		{
#if 1
			memcpy(&stParams, (void *)arg, sizeof(stParams));
			/* 2k/4k model 구분
			(4k 60Hz : 0xC930A000[18:16] - 1, 4k 120Hz : 0xC930A000[18:16] - 0)
			(2k 60Hz : 0xC930A000[18:16] - 3, 2k 120Hz : 0xC930A000[18:16] - 2)
			*/
			DE_HAL_ReadReg((void *)(uintptr_t)0xC930A000, &regVal);
			regVal &= ~(0x7 << 16);
			regVal |= (stParams & 0x7) << 16;
			DE_HAL_WriteReg((void *)(uintptr_t)0xC930A000, regVal);
#endif
		}
		else if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) )
		{
			memcpy(&stParams, (void *)arg, sizeof(stParams));
			/* 2k/4k model 구분
			(4k 60Hz : 0xC930A000[18:16] - 1, 4k 120Hz : 0xC930A000[18:16] - 0)
			(2k 60Hz : 0xC930A000[18:16] - 3, 2k 120Hz : 0xC930A000[18:16] - 2)
			*/
			DE_HAL_ReadReg((void *)(uintptr_t)0xC930A000, &regVal);
			regVal &= ~(0x7 << 16);
			regVal |= (stParams & 0x7) << 16;
			DE_HAL_WriteReg((void *)(uintptr_t)0xC930A000, regVal);
		}

	}while(0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_GetDisplayType(UINT32 *disp_type)
{
	UINT32 regVal = 0;
	if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) )
	{
		/* 2k/4k model 구분
		(4k 60Hz : 0xC930A000[18:16] - 1, 4k 120Hz : 0xC930A000[18:16] - 0)
		(2k 60Hz : 0xC930A000[18:16] - 3, 2k 120Hz : 0xC930A000[18:16] - 2)
		*/
		DE_HAL_ReadReg((void *)(uintptr_t)0xC930A000, &regVal);
		regVal = (regVal >> 16) & 0x7;
	}
    else if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) )
	{
		/* 2k/4k model 구분
		(4k 60Hz : 0xC930A000[18:16] - 1, 4k 120Hz : 0xC930A000[18:16] - 0)
		(2k 60Hz : 0xC930A000[18:16] - 3, 2k 120Hz : 0xC930A000[18:16] - 2)
		*/
		DE_HAL_ReadReg((void *)(uintptr_t)0xC930A000, &regVal);
		regVal = (regVal >> 16) & 0x7;
	}


	*disp_type = regVal;

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set 4k dual  mode on/off  (for netflix dual play)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_DualModeEnable(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	BOOLEAN stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DUAL_MODE_ENABLE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(BOOLEAN));
		if (ret) break;
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set new low delay mode using source sync
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetLowDelayBySourceSync(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_LOW_DELAY_BY_SRC;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);

		ret = DE_HAL_SetLowDelayBySourceSync(&stParams);
		if (ret) break;

		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(UINT32));
		if (ret) break;
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set high frame rate mode
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetHighFrameRate(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	UINT32 stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_HIGH_FRAME_RATE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		if(g_Diplay_type == LX_PANEL_TYPE_1920_120P || g_Diplay_type == LX_PANEL_TYPE_3840_120P)
		{
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(UINT32));
		}
		if (ret) break;
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set rotate mode (0/90/180/270 degree)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetRotate(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_ROTATE_INFO_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_ROTATE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(stParams),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_ROTATE_INFO_T));
		if (ret) break;
	} while(0);
	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to indicate Dolby Mode to MCU through IPC
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetIPCHDRMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_ERROR;
	LX_DE_HDR_IPC_MODE_T sParams;
	DE_IPC_CMD_T eIpcCmd = DE_IPC_SET_HDR_MODE;
	LX_DE_HDR_MODE_T hdrMode;
	//LX_HDR_MODE_T eHDRMode;
	static UINT32 deHdrMode = LX_HDR_TYPE_OFF;
	static UINT32 peHdrMode = LX_HDR_TYPE_OFF;

	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER((void *)&sParams,(void *)arg,sizeof(LX_DE_HDR_IPC_MODE_T),nFlag);

		if (lx_chip_rev() >= LX_CHIP_REV( O22, A0))
		{
			if (sParams.eFrom == LX_HDR_MODE_FROM_PQ)
			{
				ret = RET_OK;
				break;
			}
		}

		#if 1	//20170915, add hdrmodefrom to avoid setting invalid hdr mode ipc
		/* udpate peHdrMode and deHdrMode */
		if (sParams.eFrom == LX_HDR_MODE_FROM_PQ)
		{
			peHdrMode = sParams.eIpcMode;
		}
		else
		{
			deHdrMode = sParams.eIpcMode;
		}
		/* set hdrmode according to peHdrMode and deHdrMode */
		if (deHdrMode==LX_HDR_TYPE_OFF)
		{
			if (peHdrMode==LX_HDR_TYPE_OFF || peHdrMode==LX_HDR_TYPE_SDR2HDR)
			{
				hdrMode.hdr_mode = (LX_HDR_MODE_T)peHdrMode;
			}
			else
			{
				hdrMode.hdr_mode = (LX_HDR_MODE_T)deHdrMode;
			}
		}
		else
		{
			hdrMode.hdr_mode = (LX_HDR_MODE_T)deHdrMode;
		}
		DE_NOTI("Before_IPC:[CMD:0x%08x]wid:%x,ipc:%x,from:%x, DE:%x,PE:%x -> %x\n",\
			eIpcCmd,sParams.ucWinID,sParams.eIpcMode,sParams.eFrom,deHdrMode,peHdrMode,hdrMode.hdr_mode);
		if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
		{
			hdrMode.win_id = (LX_DE_WIN_ID_T)sParams.ucWinID;
			ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &hdrMode, sizeof(LX_DE_HDR_MODE_T));
		}
		else
		{
			ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &(hdrMode.hdr_mode), sizeof(LX_HDR_MODE_T));
		}
		DE_NOTI("After_IPC:[CMD:0x%08x]wid:%x,ipc:%x,from:%x, DE:%x,PE:%x -> %x\n",\
			eIpcCmd,sParams.ucWinID,sParams.eIpcMode,sParams.eFrom,deHdrMode,peHdrMode,hdrMode.hdr_mode);
		#else
		if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
		{
			hdrMode.win_id = (LX_DE_WIN_ID_T)sParams.ucWinID;
			hdrMode.hdr_mode = (LX_HDR_MODE_T)sParams.eIpcMode;
			ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &hdrMode, sizeof(LX_DE_HDR_MODE_T));
		}
		else
		{
			eHDRMode = sParams.eIpcMode;
			ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &eHDRMode, sizeof(eHDRMode));
		}
		#endif
		if (ret) break;
	}while(0);

	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief IOCTL function to indicate Dolby Precision Detail Mode to MCU through IPC
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetIPCPDMode(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_IPC_FEATURE_T sParams;
	DE_IPC_CMD_T eIpcCmd = DE_IPC_SET_PD_MODE;

	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER((void *)&sParams,(void *)arg,sizeof(LX_DOLBY_IOCTL_IPC_FEATURE_T),nFlag);

		DE_NOTI("[CMD:0x%08x]wid:%x,feature:%x,Enable/Disable:%x\n",\
			eIpcCmd,sParams.ucWinID,sParams.eDoviFeature,sParams.ucFlag);
		if (lx_chip_rev() >= LX_CHIP_REV( O22, A0))
		{
			ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &sParams, sizeof(LX_DOLBY_IOCTL_IPC_FEATURE_T));
		}
		if (ret) break;
	}while(0);

	CHECK_IO_RET();
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set pattern for latency measure
 *
 * @param arg [IN] Ioctl argument
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
#include "ipc_phys_hal.h"
int DE_IO_SetLatencyMeasure(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_LATENCY_MEASURE_T stParams_measure;
	LX_DE_SET_DBG_T stParams;
//	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_LATENCY_MEASURE;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(LX_DE_SET_DBG_T),nFlag);
		memcpy(&stParams_measure, &stParams.latency_measure, sizeof(LX_DE_LATENCY_MEASURE_T));
		ipc_phys_hal_InitInterrupt(0, stParams_measure.bOnOff);
//		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_measure, sizeof(LX_DE_LATENCY_MEASURE_T));
	} while(0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_GetPQE_DNNResult(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f)
{
	int ret = RET_ERROR;

	ret = DE_HAL_GetPQE_DNNResult(a, b, c, d, e, f);
	
	return ret;
}

int DE_IO_SetDftMode(UINT32 mode)
{
	int ret = RET_ERROR;
	DE_IPC_CMD_T eIpcCmd = DE_IPC_SET_DFT_MODE;

	ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &mode, sizeof(UINT32));
	DE_NOTI("mode = %d", mode);
	return ret;
}

int DE_IO_SetNetworkSync(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DE_NETWORK_SYNC_T stParams;
	DE_IPC_CMD_T eIpcCmd = DE_IPC_SET_NETWORK_SYNC;

	do {
		CHECK_MCU_IPC();
		memcpy(&stParams, (void *)arg, sizeof(LX_DE_NETWORK_SYNC_T));
		ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &stParams, sizeof(LX_DE_NETWORK_SYNC_T));
		if (ret) break;
	} while(0);
	CHECK_IO_RET();

	return ret;
}

int DE_IO_SetVTVInputPosition(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DE_WIN_DIMENSION_T stParams;
	DE_IPC_CMD_T eIpcCmd = DE_IPC_SET_VTV_POSITION;

	do {
		CHECK_MCU_IPC();
		memcpy(&stParams, (void *)arg, sizeof(LX_DE_WIN_DIMENSION_T));
		ret = MCU_Write(DE_PACK_CMD(eIpcCmd), &stParams, sizeof(LX_DE_WIN_DIMENSION_T));
		if (ret) break;
	} while(0);
	CHECK_IO_RET();

	return ret;
}



int DE_IO_GetSharedMem(unsigned long arg)
{
	int ret = 0;
	LX_DE_VTM_FRAME_INFO_T vtg_frame_info;
	LX_DE_GCP_INFO_T vtv_frame_info;
	UINT32 address = 0x20000000;
	UINT32 *p = (UINT32*)arg;
	
	if(*p == 1) {
		ret = DE_HAL_SetVTM(&vtg_frame_info);
		address = vtg_frame_info.address;
	}
	if(*p == 3) {
		ret = DE_HAL_SetGeneralCapturePath(&vtv_frame_info);
		address = vtv_frame_info.address;
	}
	if(address < 0x10000000) return -1;
	memcpy(p, &address, sizeof(UINT32));

	return ret;
}

int DE_IO_SetSharedMem(unsigned long arg)
{
	int ret = 0;
	LX_DE_VTM_FRAME_INFO_T vtg_frame_info;
	LX_DE_GCP_INFO_T       vtv_frame_info;
	LX_DE_VTG_INFO_T vtg_info;
	LX_DE_GCP_INFO_T vtv_info;
	DE_IPC_CMD_T ipcCmd;
	UINT32 *p = (UINT32*)arg;
	char systemd_opt[24];

	mutex_lock(&vsc_mutex_lock1);

	switch(*p)
	{
		case 0:
		case 1:
		{
			ret = DE_HAL_SetVTM(&vtg_frame_info);  // get address of shared memory
			if(vtg_frame_info.address < 0x10000000) return -1;
			vtg_info.win_id = 0;
			vtg_info.enable  = *p;
			vtg_info.address = vtg_frame_info.address;
			ipcCmd = DE_IPC_GET_FRAME_FOR_WEBOS;
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &vtg_info, sizeof(vtg_info)); // set address of shared memory & enable to firmware
		}break;

		case 2:
		case 4:
		{
			ret = DE_HAL_SetGeneralCapturePath(&vtv_frame_info);
			if(vtv_frame_info.address < 0x10000000) return -1;
			vtv_info.address = vtv_frame_info.address;
			vtv_info.enable = (*p-2); // *p = 2:diable, 4:enable
			ipcCmd = DE_IPC_SET_GCP_MODE;
			if (lx_chip_rev() >= LX_CHIP_REV( O22, A0)){// && lx_chip_rev() < LX_CHIP_REV( M23, A0)) {
				if(vtv_info.enable) {
					DE_IPC_CMD_T ipcCmd_bt = DE_IPC_SET_FRAME_DELAY;
					if (lx_chip_rev() >= LX_CHIP_REV( O24, A0)) ipcCmd_bt = DE_IPC_SET_VTG_EXT_BUF;
					DE_NOTI("=> enter VTV allocate_ext_buf");
					ret = DE_HAL_GetMemFromCma("de-vtvrbuf", 1, &prev_bt_cfg, 1); // alloc (VTV external buffer)
					DE_NOTI("=> leave VTV allocate_ext_buf");
					if (ret) {
						DE_ERROR("alloc fail (VTV external buffer)");
						BREAK_WRONG(ret);
					}
					ret = MCU_Write(DE_PACK_CMD(ipcCmd_bt), &prev_bt_cfg, sizeof(LX_DE_SET_DELAY_BUFFER_T));
					if (ret) {DE_ERROR("error\n");}
				}
			}
			ret = MCU_Write(DE_PACK_CMD(ipcCmd), &vtv_info, 8/*sizeof(vtv_info)*/);	// fw checks only 8 Bytes
			OS_ScanKernelCmdline("systemd.unit=%s", systemd_opt);
			if(!strstr(systemd_opt,"socts.target"))
			{
				msleep(40);
			}
			if (lx_chip_rev() >= LX_CHIP_REV( O22, A0)){// && lx_chip_rev() < LX_CHIP_REV( M23, A0)) {
				if(!vtv_info.enable) {
					DE_NOTI("=> enter VTV free_ext_buf");
#if 1
					//20240105, add o24 case for no skip (AVTASK-1386)
					if( prev_input_src.srcType > LX_DE_IN_SRC_NONE && prev_input_src.srcType < LX_DE_IN_SRC_MVI && (lx_chip_rev() < LX_CHIP_REV(O24,A0))) {
					//if( prev_input_src.srcType > LX_DE_IN_SRC_NONE && prev_input_src.srcType < LX_DE_IN_SRC_HDMI) {
						DE_NOTI("=> leave - without free VTV ext_buf. current input is [%d]", \
							prev_input_src.srcType);
						break;
					}
#endif
					ret = DE_HAL_GetMemFromCma("de-vtvrbuf", 1, &prev_bt_cfg, 0); // free
					DE_NOTI("=> leave VTV free_ext_buf");
					if (ret) {
						DE_ERROR("free fail (VTV external buffer)");
						BREAK_WRONG(ret);
					}
				}
			}
		}break;

		case 5:
		case 6:
		{
			if (lx_chip_rev() >= LX_CHIP_REV( O22, A0)) {
				if(*p == 6) { // alloc VTG ext buffer
					DE_IPC_CMD_T ipcCmd_bt = DE_IPC_SET_VTG_EXT_BUF; // o24 : use same ipc for VTG/VTV (common opertaion)
					DE_NOTI("=> enter VTG allocate_ext_buf");
					if(!prev_vr_cfg.pool_base[0])
						ret = DE_HAL_GetMemFromCma("de-vrbuf", 1, &prev_vr_cfg, 1); // alloc (VTG external buffer)
					DE_NOTI("=> leave VTG allocate_ext_buf");
					if (ret) {
						DE_ERROR("alloc fail (VTG external buffer)");
						BREAK_WRONG(ret);
					}
					ret = MCU_Write(DE_PACK_CMD(ipcCmd_bt), &prev_vr_cfg, sizeof(LX_DE_SET_DELAY_BUFFER_T));
					if (ret) {DE_ERROR("error\n");}				
				}
				else if(*p == 5) { // free VTG ext buffer
					DE_NOTI("=> enter VTG free_ext_buf");
					if(prev_vr_cfg.pool_base[0])
						ret = DE_HAL_GetMemFromCma("de-vrbuf", 1, &prev_vr_cfg, 0); // free
					prev_vr_cfg.pool_base[0] = 0;
					DE_NOTI("=> leave VTG free_ext_buf");
					if (ret) {
						DE_ERROR("free fail (VTG external buffer)");
						BREAK_WRONG(ret);
					}
				}
			}
		}break;

		case 7:
		case 8:
		{
			if(vtv_frame_info.address < 0x10000000) return -1;
			if (lx_chip_rev() >= LX_CHIP_REV( O22, A0)){// && lx_chip_rev() < LX_CHIP_REV( M23, A0)) {
				if(*p ==8) {
					DE_IPC_CMD_T ipcCmd_bt = DE_IPC_SET_FRAME_DELAY;
					if (lx_chip_rev() >= LX_CHIP_REV( O24, A0)) ipcCmd_bt = DE_IPC_SET_VTG_EXT_BUF;
					DE_NOTI("=> enter VTV allocate_ext_buf");
					ret = DE_HAL_GetMemFromCma("de-vtvrbuf", 1, &prev_bt_cfg, 1); // alloc (VTV external buffer)
					DE_NOTI("=> leave VTV allocate_ext_buf");
					if (ret) {
						DE_ERROR("alloc fail (VTV external buffer)");
						BREAK_WRONG(ret);
					}
					ret = MCU_Write(DE_PACK_CMD(ipcCmd_bt), &prev_bt_cfg, sizeof(LX_DE_SET_DELAY_BUFFER_T));
					if (ret) {DE_ERROR("error\n");}
				}
			}

			if (lx_chip_rev() >= LX_CHIP_REV( O22, A0)){// && lx_chip_rev() < LX_CHIP_REV( M23, A0)) {
				if(*p==7) {
					DE_NOTI("=> enter VTV free_ext_buf");
					ret = DE_HAL_GetMemFromCma("de-vtvrbuf", 1, &prev_bt_cfg, 0); // free
					DE_NOTI("=> leave VTV free_ext_buf");
					if (ret) {
						DE_ERROR("free fail (VTV external buffer)");
						BREAK_WRONG(ret);
					}
				}
			}
		}
		break;
		default:
			DE_ERROR("not defined");
			break;
	}
	mutex_unlock(&vsc_mutex_lock1);

	return ret;
}

int DE_IO_SetGPSControl(unsigned long arg)
{
	int ret;
	LX_DE_GPS_CTRL_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_GPS;

	do {
		memcpy(&stParams, (LX_DE_GPS_CTRL_T *)arg, sizeof(LX_DE_GPS_CTRL_T));
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_GPS_CTRL_T));		
	}while(0);
	
	return ret;
}

int DE_IO_UserSetGPSDMA(unsigned long arg, unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_GPSDMA_PARAM_T stParams_user;
	LX_DE_GPSDMA_IPC_T stParams_ipc;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_GPS_DMA;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams_user, (void *)arg, sizeof(LX_DE_GPSDMA_PARAM_T),nFlag);

		//memcpy(&stParams, (LX_DE_GPSDMA_IPC_T *)arg, sizeof(LX_DE_GPSDMA_IPC_T));

		stParams_ipc.dst				   = 0; // external buffer from vdec
		stParams_ipc.dpb_y_frame_base	   = stParams_user.src_info.addr_y;
		stParams_ipc.dpb_c_frame_base	   = stParams_user.src_info.addr_c;
		stParams_ipc.out_y_frame_base	   = stParams_user.dst_info.addr_y;
		stParams_ipc.out_c_frame_base	   = stParams_user.dst_info.addr_c;
		stParams_ipc.dpb_type.scan		   = stParams_user.src_info.scan_type;
		stParams_ipc.dpb_type.dpb_map_type = stParams_user.src_info.map_type;
		stParams_ipc.dpb_type.cs		   = stParams_user.src_info.color_sample;
		stParams_ipc.dpb_type.bpp		   = stParams_user.src_info.bpp;
		stParams_ipc.dpb_width			   = stParams_user.src_info.width;
		stParams_ipc.dpb_height 		   = stParams_user.src_info.height;
		stParams_ipc.out_width			   = stParams_user.dst_info.width;
		stParams_ipc.out_height 		   = stParams_user.dst_info.height;
		//crc_mode					   = dst_info->crc_mode;

		
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams_ipc, sizeof(LX_DE_GPSDMA_IPC_T));
	}while(0);
	return ret;
}

int DE_IO_SetGPSDMA(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_GPSDMA_IPC_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_GPS_DMA;

	do {
		memcpy(&stParams, (LX_DE_GPSDMA_IPC_T *)arg, sizeof(LX_DE_GPSDMA_IPC_T));
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_GPSDMA_IPC_T));
	}while(0);
	return ret;
}

int DE_IO_SetOrbit(unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	LX_DE_ORBIT_T stParams;
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_ORBIT;

	do {
		CHECK_MCU_IPC();
		CP_FROM_USER(&stParams, (void *)arg, sizeof(LX_DE_ORBIT_T),nFlag);
		ret = MCU_Write(DE_PACK_CMD(ipcCmd), &stParams, sizeof(LX_DE_ORBIT_T));
		if (ret) break;
		//DE_NOTI("type[%d] vo w/h=%d/%d", stParams.type,stParams.video_output.w,stParams.video_output.h);
	} while(0);
	CHECK_IO_RET();
	return ret;
}

int DE_IO_GetHistoBufferRange(UINT32 *start,UINT32 *end)
{
	int ret = RET_OK;
	ret = DE_HAL_GetHistoBufferRange(start, end);
	return ret;
}

/**  @} */
