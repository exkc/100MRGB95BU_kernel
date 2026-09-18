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
 *
 *  @author		
 *  @version	1.0 
 *  @date		
 *
 *  @addtogroup 
 *	@{
 */

#ifndef	_IPC_HAL_H_
#define	_IPC_HAL_H_

/*-----------------------------------------------------------------------------
	Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    File Inclusions
-----------------------------------------------------------------------------*/
#include "ipc_cmd_header.h"
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#include "de_ver_def.h" 
#include "de_kapi.h"
#include "de_model.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
	Constant Definitions
-----------------------------------------------------------------------------*/
#define MAX_DEV_NAME  16
#define MAX_IPC_LOG   200

/*-----------------------------------------------------------------------------
	Macro Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    Type Definitions
-----------------------------------------------------------------------------*/
struct ipc_client {
	int (*write)(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
	int (*read)( UINT32 mcu_id, void *pMsg, UINT32 msgCnt);
	int (*wrmem)(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
};

struct ipc_handle {
	struct ipc_client *m_ipc_client;
	char *p_ready; // flag for firmware ready
	char dev_name[MAX_DEV_NAME];
	UINT32 mcu_id;
	void *prev;
};

struct ipc_log {
	UINT32 cmd[MAX_IPC_LOG];
	char  *buf[MAX_IPC_LOG];
	UINT32 cnt[MAX_IPC_LOG];
	UINT32 idx;
};


#ifdef USE_KDRV_CODES_FOR_L18

typedef struct {
	DE_IPC_CMD_T			key;

	LX_DE_PANEL_TYPE_T		panel_type;			//DE_IPC_DE_INIT
	LX_DE_FIRMWARE_INFO_T	firmware_info;		//DE_IPC_GET_FIRMWARE_INFO
	LX_DE_WIN_DIMENSION_T	in_win_dimension;	//DE_IPC_SET_INPUT_WIN
	LX_DE_WIN_DIMENSION_T	out_win_dimension;	//DE_IPC_SET_OUT_WIN
	BOOLEAN					dis_out;			//DE_IPC_SET_DIS_OUT
	LX_DE_DIS_FMT_T			dis_fmt;			//DE_IPC_SET_DIS_FMT
	LX_DE_CVI_SRC_TYPE_T	cvi_src_type;		//DE_IPC_SET_CVI_SRC_TYPE
#ifdef USE_SUPPORT_EUROPE
	LX_DE_FR_RATE_T			fr_rate;			//DE_IPC_SET_FR_RATE
#endif
	LX_DE_COLOR_T			color;				//DE_IPC_SET_BG_COLOR:
	LX_DE_SET_WIN_BLANK_T	set_win_blank;		//DE_IPC_SET_WIN_BLANK
	LX_DE_CVI_FIR_T			cvi_fir;			//DE_IPC_SET_CVI_FIR
	LX_DE_CVI_TPG_T			cvi_tpg;			//DE_IPC_SET_CVI_TPG
	LX_DE_CSAMPLE_MODE_T	csample_mode;		//DE_IPC_SET_CVI_CSAMPLE_MODE
	UINT32					low_delay_ctrl;		//DE_IPC_SET_LOW_DELAY
	UINT32					platform_ver;		//DE_IPC_SET_PLATFORM_VERSION
	LX_DE_IF_CONFIG_T		if_config;			//DE_IPC_SET_IF_CONFIG
	LX_DE_LOW_DELAY_T		low_delay;			//DE_IPC_GET_LOW_DELAY
	LX_DE_INNER_PATTERN_T	inner_pattern;		//DE_IPC_SET_INNER_PATTERN
	LX_DE_INPUT_SOURCE_T	input_source;		//DE_IPC_SET_WIN_PORT_SRC
	LX_DE_WIN_FREEZE_T		win_freeze;			//DE_IPC_SET_WIN_FREEZE
	LX_DE_SOURCE_SIZE_WIN_T source_size_win;	//DE_IPC_SET_SOURCE_SIZE_INFO
	UINT32					pql_set_colorfilter;		// PQL_IPC_SET_COLORFILTER 
	
} DE_IPC_KEY_VALUE_T;

#endif

/*-----------------------------------------------------------------------------
	Extern Function Prototype Declaration
-----------------------------------------------------------------------------*/
int ipc_hal_init(void);
int ipc_hal_cleanup(void);
struct ipc_handle *ipc_hal_open(char *name, MCU_ID_TYPE mcu_id);
int ipc_hal_close(struct ipc_handle *ipc_handle);
int ipc_hal_list(void);
int ipc_hal_start(UINT32 mcu_id, char flag);
int ipc_hal_trace(BOOLEAN p);
int ipc_hal_restore(void);
int ipc_hal_ready_to_use(int enable);
int ipc_hal_set_mask(UINT32 disable);
UINT32 ipc_hal_get_mask(void);

/*-----------------------------------------------------------------------------
	Extern Variables
-----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _IPC_HAL_H_ */

/** @} */

