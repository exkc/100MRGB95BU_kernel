/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_fwi_o26.c
 *
 *  driver for firmware interface functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.12
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_o26.h"
#include "pe_reg_o26.h"
#include "pe_fwi_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_O26_FW_SRC_OFF		(0)
#define PE_FWI_O26_FW_SRC_ON		(1)
#define PE_FWI_O26_FW_RESET_STATUS_OFF		(0)
#define PE_FWI_O26_FW_RESET_STATUS_ON		(1)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_O26_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if (_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#ifdef INCLUDE_KDRV_DE
#define PE_FWI_O26_IPC0_CHK_NULL()		\
	PE_FWI_O26_CHECK_CODE((pe_fwi_o26_mcu0_ipc==NULL || \
	pe_fwi_o26_mcu0_ipc->m_ipc_client->write==NULL || \
	pe_fwi_o26_mcu0_ipc->m_ipc_client->read==NULL), \
	ret = RET_ERROR;break, "mcu0_ipc is null.\n")

#define PE_FWI_O26_IPC0_CHK_READY()		\
	PE_FWI_O26_CHECK_CODE(pe_fwi_o26_mcu0_ipc->p_ready==NULL, \
	ret = RET_ERROR;break, "mcu0_ipc is not ready.\n")

#define PE_FWI_O26_IPC0_SET_DATA(cmd, msg, size)		\
	pe_fwi_o26_mcu0_ipc->m_ipc_client->write(cmd, msg, size)
#define PE_FWI_O26_IPC0_GET_DATA(mcu, msg, size)		\
	pe_fwi_o26_mcu0_ipc->m_ipc_client->read(mcu, msg, size)

#define PE_FWI_O26_IPC1_CHK_NULL()		\
	PE_FWI_O26_CHECK_CODE((pe_fwi_o26_mcu1_ipc==NULL || \
	pe_fwi_o26_mcu1_ipc->m_ipc_client->write==NULL || \
	pe_fwi_o26_mcu1_ipc->m_ipc_client->read==NULL), \
	ret = RET_ERROR;break, "mcu1_ipc is null.\n")

#define PE_FWI_O26_IPC1_CHK_READY()		\
	PE_FWI_O26_CHECK_CODE(pe_fwi_o26_mcu1_ipc->p_ready==NULL, \
	ret = RET_ERROR;break, "mcu1_ipc is not ready.\n")

#define PE_FWI_O26_IPC1_SET_DATA(cmd, msg, size)		\
	pe_fwi_o26_mcu1_ipc->m_ipc_client->write(cmd, msg, size)
#else
#define PE_FWI_M23_IPC0_CHK_NULL()
#define PE_FWI_M23_IPC0_CHK_READY()
#define PE_FWI_M23_IPC0_SET_DATA(cmd, msg, size)
#define PE_FWI_M23_IPC0_GET_DATA(mcu, msg, size)
#define PE_FWI_M23_IPC1_CHK_NULL()
#define PE_FWI_M23_IPC1_CHK_READY()
#define PE_FWI_M23_IPC1_SET_DATA(cmd, msg, size)
#endif

#define PE_PACK_CMD(_id, _cmd) 	PACK_CMD(0, 0, (_id), (_cmd))

/* define for refresh pq fw table when fw reset */
#define PE_FWI_O26_CHECK_REFRESH_TBL( )	\
	do {\
		PE_FWI_O26_SETTINGS_T *p_temp_info = &_g_pe_fwi_o26_info;\
		if ((p_temp_info->fw_status.reset) == PE_FWI_O26_FW_RESET_STATUS_ON)\
		{\
			PE_DBG_FWI("RESET ON, fw src_info:%d\n",p_temp_info->fw_status.src_info);\
			ret = PE_FWI_O26_RefreshFwTable();\
			PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_RefreshFwTable() error.\n");\
			(p_temp_info->fw_status.reset) = PE_FWI_O26_FW_RESET_STATUS_OFF;\
		}\
	} while (0)

#define PE_MCU_O26_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_MCU_O26,data,_r);\
		PE_REG_SHDW_Wr03(gPE_MCU_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_MCU_O26,data,_r);}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sr_inference_mode                  :1 ,	// 0:0
	reserved0                          :3 ,	// 3:1
	sr_sqm_enalbe                      :1 ,	// 4
	reserved1                          :3 ,	// 7:5
	user_data_ready                    :1 ,	// 8
	reserved2                          :3 ,	// 11:9
	tra_halt                           :1 ,	// 12
	reserved3                          :3 ,	// 15:13
	srsqm_ui                           :1 ,	// 16
	reserved4                          :3 ,	// 19:17
	accel_srsqm                        :1 ,	// 20
	reserved5                          :3 ,	// 23:21
	accel_tra                          :1 ;	// 24
}PE_O26_REG_FW_IPC_20_T;
typedef struct
{
	UINT32
	sr_sqm_position_y                  :12 ,	// 11:0
	sr_sqm_position_x                  :12 ,	// 23:12
	pos_count                              :2  ;	// 25:24
}PE_O26_REG_FW_CROP_POS_T;
typedef struct
{
	UINT32
	tra_or_valid_run                   :2 ;	// 1:0 , 0x1: tra_run, 0x2: valid_run
}PE_O26_REG_FW_IPC_22_T;
typedef struct
{
	UINT32
	sr_demo_onoff                      :1 ,	// 0:0
	reserved0                          :3 ,	// 3:1
	left_or_right                      :1 ,	// 4    [0: left is DNN-SR result, 1: right is  DNN-SR result]
	reserved1                          :11, // 15:5
	obc_demo_onoff                     :1 ;	// 16
}PE_O26_REG_FW_IPC_23_T;


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T gPeMem[10];//[0]:fw_dnn, [1~9]:none

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DE
struct ipc_handle *pe_fwi_o26_mcu0_ipc = NULL;
struct ipc_handle *pe_fwi_o26_mcu1_ipc = NULL;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_FWI_O26_IPC_SetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
static int PE_FWI_O26_IPC_GetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
static int PE_FWI_O26_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize);
static int PE_FWI_O26_RefreshFwTable(void);
// static int PE_LGSR_HW_O26_DownloadLGSRDb(UINT32 *pUser);
// static int PE_LGSR_HW_O26_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser);
// static int PE_LGSR_HW_O26F22_DownloadLGSRDb(UINT32 *pUser);
// static int PE_LGSR_HW_O26F22_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_FWI_O26_SETTINGS_T _g_pe_fwi_o26_info;
static PE_O26_REG_FW_IPC_20_T _g_pe_fwi_o26_ipc_20;
static PE_O26_REG_FW_CROP_POS_T _g_pe_fwi_o26_crop_pos;
static PE_O26_REG_FW_IPC_22_T _g_pe_fwi_o26_ipc_22;
static PE_O26_REG_FW_IPC_23_T _g_pe_fwi_o26_ipc_23;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set f/w ipc set data
 *	- never use this on sync handler
 *
 * @param   mcuId [in] UINT32
 * @param   cmd [in] UINT32
 * @param   *msg [in] void
 * @param   size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_FWI_O26_IPC_SetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	do {
		if (lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			PE_PRINT_NOTI("SLT skip ipc\n");
			break;
		}

		CHECK_KNULL(pMsg);
		PE_DBG_FWI("mcuId:%d, ipcCmd:0x%08X, msgCnt:%d\n", mcuId, ipcCmd, msgCnt);

		if (mcuId == MCU_ID_0 || mcuId == MCU_ID_1)
		{
			PE_FWI_O26_IPC0_CHK_NULL();
			PE_FWI_O26_IPC0_CHK_READY();
			PE_FWI_O26_IPC0_SET_DATA(ipcCmd, pMsg, msgCnt);
		}
		else
		{
			PE_PRINT_ERROR("mcuId(%d) is invalid.\n",mcuId);
			ret = RET_ERROR;
		}

	} while (0);
	#endif
	return ret;
}
/**
 * set f/w ipc get data
 *	- never use this on sync handler
 *
 * @param   mcuId [in] UINT32
 * @param   cmd [in] UINT32
 * @param   *msg [in] void
 * @param   size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_FWI_O26_IPC_GetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	do {
		if (lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			PE_PRINT_NOTI("SLT skip ipc\n");
			break;
		}

		CHECK_KNULL(pMsg);
		PE_DBG_FWI("mcuId:%d, ipcCmd:0x%08X, msgCnt:%d\n", mcuId, ipcCmd, msgCnt);

		if (mcuId == MCU_ID_0 || mcuId == MCU_ID_1)
		{
			PE_FWI_O26_IPC0_CHK_NULL();
			PE_FWI_O26_IPC0_CHK_READY();
			PE_FWI_O26_IPC0_GET_DATA(mcuId, pMsg, msgCnt);
		}
		else
		{
			PE_PRINT_ERROR("mcuId(%d) is invalid.\n",mcuId);
			ret = RET_ERROR;
		}

	} while (0);
	#endif
	return ret;
}
/**
 * set pq f/w settings
 *	- never use this on sync handler
 *
 * @param   header [in] PE_FWI_PQ_TABLE_HEAD_T
 * @param   *table [in] UINT8
 * @param   tbl_size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_FWI_O26_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	UINT32 offset;
	UINT32 length;
	UINT32 dataSize;
	UINT8 *pData = NULL;
	DE_IPC_CMD_T ipcCmd = PQL_IPC_SET_TABLE;
	do {
		offset = header.offset;
		length = header.length;
		PE_FWI_O26_CHECK_CODE(!length, break, "length is zero.\n");
		PE_FWI_O26_CHECK_CODE(!pTable, break, "pTable is null.\n");
		PE_FWI_O26_CHECK_CODE(!tblSize, break, "tblSize is zero.\n");
		PE_FWI_O26_CHECK_CODE(((offset+length)>tblSize), break, \
			"offset(%d) and length(%d) is greater than tblSize(%d).\n", \
			offset, length, tblSize);
		PE_DBG_FWI(" wid:%d, ofs:%d, len:%d, tbl_size:%d\n", \
			header.win_id, header.offset, header.length, tblSize);
		dataSize = sizeof(header)+length;
		pData = OS_KMalloc(dataSize);
		PE_FWI_O26_CHECK_CODE(!pData, break, "pData is null.\n");
		memcpy(pData, &header, sizeof(header));
		memcpy(&pData[sizeof(header)], &pTable[offset], length);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipcCmd, pData, dataSize);
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_IPC_SetData() error.\n");
	} while (0);
	if (pData)	OS_Free(pData);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * refresh f/w table
 *	- never use this on sync handler
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_FWI_O26_RefreshFwTable(void)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP

	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_O26_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_O26_SETTINGS_T *pInfo=&_g_pe_fwi_o26_info;
	do {
		pTable = (UINT8 *)&table;
		tbl_size = sizeof(PE_FWI_O26_PQ_IPC_CTRL);
		header.win_id = LX_PE_WIN_0;
		header.offset = PE_FWI_O26_REFRESH_TBL_OFST;
		header.length = PE_FWI_O26_REFRESH_TBL_SIZE;
		memcpy(&(table.tnr_ctrl), &(pInfo->tnr_ctrl[LX_PE_WIN_0]), sizeof(PE_FWI_O26_TNR_CTRL));
		memcpy(&(table.fw_ctrl), &(pInfo->fw_ctrl), sizeof(PE_FWI_O26_FW_CTRL));
		memcpy(&(table.src_info), &(pInfo->src_info), sizeof(PE_FWI_O26_SRC_INFO));
		memcpy(&(table.dnr_common), &(pInfo->dnr_common), sizeof(PE_FWI_O26_DNR_COMMON));
		memcpy(&(table.dnr_detail), &(pInfo->dnr_detail), sizeof(PE_FWI_O26_DNR_DETAIL));
		memcpy(&(table.shp_e_ctrl), &(pInfo->shp_e_ctrl), sizeof(PE_FWI_O26_EDGE_GAIN));
		memcpy(&(table.shp_t_ctrl), &(pInfo->shp_t_ctrl), sizeof(PE_FWI_O26_TEXTURE_GAIN));
		#if 0	//not_used
		memcpy(&(table.shp_h_ctrl), &(pInfo->shp_h_ctrl), sizeof(PE_FWI_O26_HOR_CTRL));
		memcpy(&(table.shp_m_ctrl), &(pInfo->shp_m_ctrl), sizeof(PE_FWI_O26_MISC_CTRL));
		memcpy(&(table.src_info), &(pInfo->src_info), sizeof(PE_FWI_O26_SRC_INFO));
		memcpy(&(table.cen_ctrl), &(pInfo->cen_ctrl), sizeof(PE_FWI_O26_CEN_CTRL));
		#endif
		PE_DBG_FWI("wid:%d, ofs:%d, len:%d, tbl_size:%d\n", \
			header.win_id, header.offset, header.length, tbl_size);
		ret = PE_FWI_O26_SetFwSettings(header,  pTable,  tbl_size);
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_SetFwSettings() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * open fwi ipc
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_IPC_Open(void)
{
	int ret = RET_OK;
	#ifdef INCLUDE_KDRV_DE
	do {
		PE_PRINT_NOTI("open ipc.\n");
		/* check pe_fwi_o26_mcu0_ipc is already opened */
		if(pe_fwi_o26_mcu0_ipc == NULL)
		{
			pe_fwi_o26_mcu0_ipc = ipc_hal_open("pe", MCU_ID_0);
			PE_FWI_O26_CHECK_CODE(!pe_fwi_o26_mcu0_ipc,ret = RET_ERROR;break,"PE_fwi_o26_mcu0_ipc open fail.\n");
		}
		/* check pe_fwi_o26_mcu1_ipc is already opened */
		if(pe_fwi_o26_mcu1_ipc == NULL)
		{
			pe_fwi_o26_mcu1_ipc = ipc_hal_open("pe", MCU_ID_1);
			PE_FWI_O26_CHECK_CODE(!pe_fwi_o26_mcu1_ipc,ret = RET_ERROR;break,"PE_fwi_o26_mcu1_ipc open fail.\n");
		}
	} while (0);
	#endif
	return ret;
}

/**
 * close fwi ipc
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_IPC_Close(void)
{
	int ret = RET_OK;
	#ifdef INCLUDE_KDRV_DE
	do {
		PE_PRINT_NOTI("close ipc.\n");
		if (pe_fwi_o26_mcu0_ipc)
		{
			ipc_hal_close(pe_fwi_o26_mcu0_ipc);
			pe_fwi_o26_mcu0_ipc = NULL;
		}
		if (pe_fwi_o26_mcu1_ipc)
		{
			ipc_hal_close(pe_fwi_o26_mcu1_ipc);
			pe_fwi_o26_mcu1_ipc = NULL;
		}
	} while (0);
	#endif
	return ret;
}
/**
 * init fwi module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		memset(&_g_pe_fwi_o26_info, 0x0, sizeof(PE_FWI_O26_SETTINGS_T));
		_g_pe_fwi_o26_info.src_info.dtv_mode = 0xff;	//default
		_g_pe_fwi_o26_info.src_info.hdd_mode = 0xff;	//default
		_g_pe_fwi_o26_info.pre_colormetry[0]=_g_pe_fwi_o26_info.pre_colormetry[1]=0xff;
		memset(&_g_pe_fwi_o26_ipc_20, 0x0, sizeof(UINT32));
		memset(&_g_pe_fwi_o26_crop_pos, 0x0, sizeof(UINT32));
		memset(&_g_pe_fwi_o26_ipc_22, 0x0, sizeof(UINT32));
		memset(&_g_pe_fwi_o26_ipc_23, 0x0, sizeof(UINT32));
		PE_PRINT_NOTI("done\n");
	} while (0);
	return ret;

}
/**
 * check f/w status(periodic)
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_CheckFwStatus(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_FWI_O26_SETTINGS_T *pInfo=&_g_pe_fwi_o26_info;
	do {
		CHECK_KNULL(pCfg);
		if (pInfo->fw_status.src_info != ctrl0_info->fw_src)
		{
			PE_DBG_FWI("fw_src changed : %d -> %d.\n", \
				pInfo->fw_status.src_info, ctrl0_info->fw_src);
			if ((pInfo->fw_status.src_info != PE_FWI_O26_FW_SRC_OFF) && \
				(ctrl0_info->fw_src == PE_FWI_O26_FW_SRC_OFF))
			{
				PE_DBG_FWI("fw_reset status on\n");
				pInfo->fw_status.reset = PE_FWI_O26_FW_RESET_STATUS_ON;
			}
			pInfo->fw_status.src_info = ctrl0_info->fw_src;
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set color filter
 *	- never use this on sync handler
 *
 * @param   cflter_state [in] UINT32, 0x0~0x2:off,r,g,b
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetColorFilter(UINT32 cflter_state)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_COLORFILTER;
	do {
		PE_DBG_FWI("set state : %d\n", cflter_state);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &cflter_state, sizeof(cflter_state));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * load db data
 *	- never use this on sync handler
 *
 * @param   base_addr [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_LoadDbData(UINT32 base_addr)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_DB_DATA;
	do {
		PE_DBG_FWI("base_addr : 0x%08x\n", base_addr);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &base_addr, sizeof(base_addr));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * load db done
 *	- never use this on sync handler
 *
 * @param   chip info base,size [in] *UINT32
 * @param   size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_LoadDbDone(UINT32 *pData, UINT32 size)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_DB_DONE;
	do {
		CHECK_KNULL(pData);
		if (!size)	break;
		PE_DBG_FWI("LoadDbDone(0x%08x)(%d)(%d)(size:%d)\n",pData[0],pData[1],pData[2],size);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, pData, size);
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set hdr info
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetHdrInfo(UINT32 *pInfo)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_HDR_INFO;
	do {
		CHECK_KNULL(pInfo);
		if (PE_KDRV_VER_O26)
		{
			if (pre_info != pInfo[0])
			{
				PE_DBG_FWI("hdr info : 0x%08x <- 0x%08x\n", pInfo[0], pre_info);
				ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
				PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_IPC_SetData() error.\n");
				pre_info = pInfo[0];
			}
		}
		else
		{
			PE_DBG_FWI("nothing to do.\n");
			ret = RET_OK;
		}
	} while (0);
	#endif
	return ret;
}
/**
 * PE_FWI_O26_GetHdrMode
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_GetHdrMode(UINT32 *pInfo)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_GET_HDR_MODE;
	do {
		CHECK_KNULL(pInfo);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
		ret = PE_FWI_O26_IPC_GetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_GetData() error.\n");
		PE_PRINT_NOTI("hdr mode : %d\n", pInfo[0]);
	} while (0);
	#endif
	return ret;
}
/**
 * set pattern
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetPattern(UINT32 *pInfo)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_TPG;
	do {
		CHECK_KNULL(pInfo);
		if (pre_info != pInfo[0])
		{
			PE_PRINT_NOTI("set pat : 0x%x <- 0x%x\n", pInfo[0], pre_info);
			ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
			pre_info = pInfo[0];
		}
	} while (0);
	#endif
	return ret;
}
/**
 * set fw cvi csc
 *	- never use this on sync handler
 *
 * @param   *pstParams [in] PE_FWI_O26_CSC_INPUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetCviCsc(PE_FWI_O26_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = DE_IPC_SET_CVI_CSC;
	do {
		CHECK_KNULL(pstParams);
		PE_PRINT_NOTI("set[%d] : idx:%d\n",pstParams->win_id,pstParams->enable);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0,ipc_cmd,(void *)pstParams,sizeof(PE_FWI_O26_CSC_INPUT_T));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set colorimetry
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetColorimetry(UINT32 wid, UINT32 *pInfo)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	UINT32 pre_info[2] = {0xff,0xff};
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_COLORIMETRY;
	PE_FWI_O26_SETTINGS_T *pFWInfo=&_g_pe_fwi_o26_info;

	union colorimetry {
		UINT32 udata32;
		struct {
			UINT32 color : 4;  //[3:0]
			UINT32 resvd : 24; //[27:4]
			UINT32 wid   : 4;  //[31:28]
		};
	} info;
	memcpy(pre_info, pFWInfo->pre_colormetry, sizeof(UINT32)*2);

	do {
		if (wid > LX_PE_WIN_1)	break;
		CHECK_KNULL(pInfo);
		if (pre_info[wid] != pInfo[0])
		{
			info.udata32 = 0;
			info.color = pInfo[0];
			info.wid = wid;
			PE_PRINT_NOTI("[%d] %d (%x <- %x)\n",info.wid,info.color,pInfo[0],pre_info[wid]);
			ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &info, sizeof(union colorimetry));
			PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_IPC_SetData() error.\n");
			pFWInfo->pre_colormetry[wid] = pInfo[0];
		}
	} while (0);
	#endif
	return ret;
}
/**
 * set src info to f/w
 *	- never use this on sync handler
 *
 * @param   *pstParams [in] PE_FWI_O26_SRC_INFO
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetSrcInfo(PE_FWI_O26_SRC_INFO *pstParams)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_O26_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_O26_SETTINGS_T *pInfo=&_g_pe_fwi_o26_info;
	do {
		CHECK_KNULL(pstParams);
		PE_FWI_O26_CHECK_REFRESH_TBL();
		if ((pInfo->src_info.dtv_mode!=pstParams->dtv_mode) || (pInfo->src_info.hdd_mode!=pstParams->hdd_mode))
		{
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_O26_PQ_IPC_CTRL);
			header.win_id = LX_PE_WIN_0;
			header.offset = PE_FWI_OFFSET(PE_FWI_O26_SRC_INFO);
			header.length = sizeof(PE_FWI_O26_SRC_INFO);
			table.src_info.dtv_mode = pstParams->dtv_mode;
			table.src_info.hdd_mode = pstParams->hdd_mode;
			PE_DBG_FWI("\n wid:%d, ofs:%d, len:%d, tbl_size:%d, src_info.dtv:%d->%d, hdd:%d->%d\n", \
				header.win_id, header.offset, header.length, \
				tbl_size, pInfo->src_info.dtv_mode, table.src_info.dtv_mode, \
				pInfo->src_info.hdd_mode, table.src_info.hdd_mode);
			ret = PE_FWI_O26_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_SetFwSettings() error.\n");
			pInfo->src_info.dtv_mode=pstParams->dtv_mode;
			pInfo->src_info.hdd_mode=pstParams->hdd_mode;
		}
		else
		{
			PE_DBG_FWI("src_info.dtv:%d->%d, hdd:%d->%d, same..\n", \
				pInfo->src_info.dtv_mode,pstParams->dtv_mode,pInfo->src_info.hdd_mode,pstParams->hdd_mode);
			ret = RET_OK;
			break;
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * SetPicMode
 *	- never use this on sync handler
 *
 * @param   mode [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_SetPicMode(UINT32 mode)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	static UINT32 pre_mode = 0xffffffff;
	UINT32 cur_mode;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PIC_MODE;
	do {
		cur_mode = mode;
		if (pre_mode != mode)
		{
			PE_DBG_FWI("set mode : 0x%08x <- 0x%08x (diff)\n", mode, pre_mode);
			ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &mode, sizeof(mode));
			PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
			pre_mode = mode;
		}
		else
		{
			PE_DBG_FWI("set mode : 0x%08x <- 0x%08x (same)\n", mode, pre_mode);
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get f/w settings
 *
 * @param   *pstParams [in] PE_FWI_O26_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_GetCurFwiSettings(PE_FWI_O26_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	PE_FWI_O26_SETTINGS_T *pInfo=&_g_pe_fwi_o26_info;
	do {
		CHECK_KNULL(pstParams);
		memcpy(pstParams, pInfo, sizeof(PE_FWI_O26_SETTINGS_T));
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * load lgsr db data
 *	- never use this on sync handler
 *
 * @param   base_addr [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O26_LoadLGSRDbData(UINT32 base_addr)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_SRINF_DB_DATA;
	do {
		PE_DBG_FWI("base_addr : 0x%08x\n", base_addr);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &base_addr, sizeof(base_addr));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_FWI_O26_IPC_SetData() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_DoneDownloadDdr(UINT32 onoff)
{
#define PE_FWI_O26_LGSR_SQM_SIZE_WGT (0x11F90)
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	//volatile UINT32 *pWgt_2k=NULL;
	//volatile UINT32 *pWgt_4k=NULL;
	// UINT32 base_wgt2k=0;
	// UINT32 base_wgt4k=0;
	//LX_DE_IPC_SYSTEM_INFO_T *currMem = &g_pe_lgsr_mem_info;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		if(onoff) //onoff==1 cold booting
		{
			#if 0
			/*download SR-SQM(LNE) 2K weight*/
			if (currMem->fw_mcu3.base!=0 && currMem->fw_mcu3.size!=0)
			{
				base_wgt2k = currMem->fw_mcu3.base + 0x10000;
				pWgt_2k = (volatile UINT32 *)vmap_phys(base_wgt2k, PE_FWI_O26_LGSR_SQM_SIZE_WGT+PAGE_SIZE);
				memcpy((UINT32 *)pWgt_2k, lgsr_sqm_weigth_2k_o26, PE_FWI_O26_LGSR_SQM_SIZE_WGT);
				wmb();
			}

			/*download SR-SQM(LNE) 4K weight*/
			if (currMem->fw_mcu4.base!=0 && currMem->fw_mcu4.size!=0)
			{
				base_wgt4k = currMem->fw_mcu4.base + 0x10000;
				pWgt_4k = (volatile UINT32 *)vmap_phys(base_wgt4k, PE_FWI_O26_LGSR_SQM_SIZE_WGT+PAGE_SIZE);
				memcpy((UINT32 *)pWgt_4k, lgsr_sqm_weigth_4k_o26, PE_FWI_O26_LGSR_SQM_SIZE_WGT);
				wmb();
			}
			PE_PRINT_NOTI("LGSR SQM data : DL done. 2k:0x%08x(0x%08x,%d), 4k:0x%08x(0x%08x,%d)\n",\
				base_wgt2k,currMem->fw_mcu3.base,currMem->fw_mcu3.size,\
				base_wgt4k,currMem->fw_mcu4.base,currMem->fw_mcu4.size);
			#endif
			ret = PE_FWI_O26_LoadLGSRDbData(gPeMem[0].base+0x100000);
			PE_PRINT_NOTI("[Db]LGSR SQM data done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
			PE_INF_HW_O26_BACKUP_TRACE("[Db] lgsr done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
		}
		else  //onoff==0 instance booting
		{
			#if 0
			if (currMem->fw_mcu3.base!=0 && currMem->fw_mcu3.size!=0)
			{
				base_wgt2k = currMem->fw_mcu3.base + 0x10000;
				pWgt_2k = (volatile UINT32 *)vmap_phys(base_wgt2k, sizeof(UINT32)*4 );
				rmb();
				/*check sample DB*/
				if(pWgt_2k[0]!=lgsr_sqm_weigth_2k_o26[0] || pWgt_2k[1]!=lgsr_sqm_weigth_2k_o26[1] || \
					pWgt_2k[2]!=lgsr_sqm_weigth_2k_o26[2] || pWgt_2k[3]!=lgsr_sqm_weigth_2k_o26[3])
				{
					PE_PRINT_NOTI("LGSR SQM data DDR check error : %d\n",onoff);
					if (pWgt_2k) vunmap_phys((void *)pWgt_2k);
					//if (pWgt_4k) vunmap_phys((void *)pWgt_4k);
					return RET_ERROR;
				}
				else
				{
					ret = PE_FWI_O26_LoadLGSRDbData(currMem->fw_dnn.base+0x100000);
					PE_PRINT_NOTI("LGSR SQM data already done_donwload : %d\n",onoff);
				}
			}
			#endif
			ret = PE_FWI_O26_LoadLGSRDbData(gPeMem[0].base+0x100000);
			PE_PRINT_NOTI("[Db]LGSR SQM data already done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
			PE_INF_HW_O26_BACKUP_TRACE("[Db]LGSR SQM data already done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
		}
		_g_pe_fwi_o26_ipc_20.sr_inference_mode = 0x1; // 221031, TVPM-21073
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret, break, "PE_LGSR_HW_O26_DoneDownloadDdr() error.\n");
	} while (0);
	//if (pWgt_2k) vunmap_phys((void *)pWgt_2k);
	//if (pWgt_4k) vunmap_phys((void *)pWgt_4k);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
#if 0
/**
 * download db
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_LGSR_HW_O26_DownloadLGSRDb(UINT32 *pUser)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i;
	PE_CFG_CTRL_T stParams;
	PE_LGSR_DDR_DB_SHDW_REG_O26_T *p_shdw_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O26_T *p_phys_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O26_T *p_phys_db_chk = NULL;
	p_shdw_db = gPE_LGSR_DDR_DB_O26.shdw.data;
	p_phys_db = gPE_LGSR_DDR_DB_O26.phys.data;
	do {
		CHECK_KNULL(pUser);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_LGSR_DDR_O26_DB_VER;
		p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_LGSR_DDR_O26_BASE_ADDR;
		p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_LGSR_DDR_O26_SEC_NUM;
		/* *********************************************************************/
		/* Causion : Should be arranged in enum order **************************/
		/* *********************************************************************/
		for(i =0; i< PE_LGSR_DDR_O26_SEC_NUM ; i++)
		{
			ret = PE_LGSR_HW_O26_DownloadLGSROneSet(i,pUser);
			PE_FWI_O26_CHECK_CODE(ret,break,"PE_CMN_HW_O26_DownloadLGSROneSet() error.\n");
		}
		wmb();
		/* inform load db data */
		ret = PE_FWI_O26_LoadLGSRDbData(p_shdw_db->top_h.db_base);
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_LoadLGSRDbData() error.\n");
		/* *********************************************************************/
		PE_PRINT_NOTI("DL db done.(base:0x%08x)\n", PE_LGSR_DDR_O26_BASE_ADDR);
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * download shp 2k ui sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_LGSR_HW_O26_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 size, sec_typ;
	PE_LGSR_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_LGSR_DDR_DB_O26.shdw.data;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_LGSR_DDR_DB_O26.phys.data;
	volatile UINT32 *p_apb_data = NULL;
	volatile UINT32 *p_weight_data = NULL;
	PE_USER_LGSR_DDR_DB_PHYS_REG_O26_T *p_user_db = (PE_USER_LGSR_DDR_DB_PHYS_REG_O26_T*)pUser;
	do {
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_apb_data = p_phys_db->inf_set[setNum].inf_apb;
		CHECK_KNULL(p_apb_data);
		p_weight_data = p_phys_db->inf_set[setNum].inf_weight;
		CHECK_KNULL(p_weight_data);
		/* dnr_user **************************************************************/
		sec_typ = setNum;//PE_LGSR_DDR_O26_SEC_TYPE
		
		/* header */
		p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
		p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
		p_phys_db->inf_set[sec_typ].header.version   = p_shdw_db->sec_d[sec_typ].header.version;
		p_phys_db->inf_set[sec_typ].header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
		/* data */
		size = ((PE_LGSR_DDR_O26_INF_WEIGHT_SIZE+PE_LGSR_DDR_O26_INF_APB_SIZE+PE_LGSR_DDR_O26_INF_DUMMY_SIZE) * sizeof(UINT32));
		if(sec_typ == 0)//PE_LGSR_DDR_O26_SEC_INF_SET_00
		{
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.db_base+sizeof(PE_LGSR_DDR_O26_TOP_HEADER_T);
		}
		else
		{
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
		}
		p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_LGSR_DDR_O26_HEADER_T);
		p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
		p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
		p_shdw_db->sec_d[sec_typ].data_base = \
			p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_LGSR_DDR_O26_HEADER_T);

		
		p_shdw_db->sec_d[sec_typ].header.base_apb  = p_shdw_db->sec_d[sec_typ].data_base;
		p_shdw_db->sec_d[sec_typ].header.base_weight = \
			p_shdw_db->sec_d[sec_typ].header.base_apb + \
			((PE_LGSR_DDR_O26_INF_APB_SIZE+PE_LGSR_DDR_O26_INF_DUMMY_SIZE) * sizeof(UINT32));
		p_phys_db->inf_set[sec_typ].header.base_apb= p_shdw_db->sec_d[sec_typ].header.base_apb;
		p_phys_db->inf_set[sec_typ].header.base_weight= p_shdw_db->sec_d[sec_typ].header.base_weight;
		/* wr ddr */
		memcpy(p_apb_data,p_user_db->inf_set[setNum].inf_apb,\
		(PE_LGSR_DDR_O26_INF_APB_SIZE * sizeof(UINT32)));
		memcpy(p_weight_data,p_user_db->inf_set[setNum].inf_weight,\
		(PE_LGSR_DDR_O26_INF_WEIGHT_SIZE * sizeof(UINT32)));
		/* noti */
		PE_PRINT_NOTI("%s: DL done.(base:0x%08x)(apb:0x%08x)(weight:0x%08x)\n", \
			PE_LGSR_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],\
			p_shdw_db->sec_d[sec_typ].header.base_apb, p_shdw_db->sec_d[sec_typ].header.base_weight);
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * download db
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_LGSR_HW_O26F22_DownloadLGSRDb(UINT32 *pUser)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i;
	PE_CFG_CTRL_T stParams;
	PE_LGSR_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O26F22_T *p_phys_db_chk = NULL;
	p_shdw_db = gPE_LGSR_DDR_DB_O26F22.shdw.data;
	p_phys_db = gPE_LGSR_DDR_DB_O26F22.phys.data;
	do {
		CHECK_KNULL(pUser);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_LGSR_DDR_O26F22_DB_VER;
		p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_LGSR_DDR_O26F22_BASE_ADDR;
		p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_LGSR_DDR_O26F22_SEC_NUM;
		/* *********************************************************************/
		/* Causion : Should be arranged in enum order **************************/
		/* *********************************************************************/
		for(i =0; i< PE_LGSR_DDR_O26F22_SEC_NUM ; i++)
		{
			ret = PE_LGSR_HW_O26F22_DownloadLGSROneSet(i,pUser);
			PE_FWI_O26_CHECK_CODE(ret,break,"PE_CMN_HW_O26_DownloadLGSROneSet() error.\n");
		}
		wmb();
		/* inform load db done */
		do {
			__attribute__((unused)) UINT32 load_data[3];
			UINT32 sec_typ;
			UINT32 ddr_total=0;
			UINT32 load_size=0;
			#if 0
			for (sec_typ=0; sec_typ<PE_LGSR_DDR_O26F22_SEC_NUM; sec_typ++)
			{
				ddr_total += p_shdw_db->top_h.sec_size[sec_typ];
				//PE_PRINT_NOTI("%s:size:%d, total: %d\n", PE_LGSR_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_phys_db->top_h.sec_size[sec_typ],ddr_total2);
			}
			#endif
			load_data[0] = PE_LGSR_DDR_O26F22_BASE_ADDR;
			load_data[1] = sizeof(PE_LGSR_DDR_DB_PHYS_REG_O26F22_T);
			load_data[2] = 1;
			load_size = (UINT32)(sizeof(UINT32)*3);
			ret = PE_FWI_O26_LoadDbDone(load_data, load_size);
			PE_FWI_O26_CHECK_CODE(ret,break,"PE_FWI_O26_LoadDbDone() error.\n");
			PE_PRINT_NOTI("LoadDbDone(base:0x%08x)(size:%d)(data:%d)\n",load_data[0],load_data[1],load_data[2]);
		} while(0);
		/* *********************************************************************/
		PE_PRINT_NOTI("DL db done.(base:0x%08x)\n", PE_LGSR_DDR_O26F22_BASE_ADDR);
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download shp 2k ui sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_LGSR_HW_O26F22_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 size, sec_typ;
	PE_LGSR_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_LGSR_DDR_DB_O26F22.shdw.data;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_LGSR_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_apb_data = NULL;
	volatile UINT32 *p_weight_data = NULL;
	PE_USER_LGSR_DDR_DB_PHYS_REG_O26F22_T *p_user_db = (PE_USER_LGSR_DDR_DB_PHYS_REG_O26F22_T*)pUser;
	do {
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_apb_data = p_phys_db->inf_set[setNum].inf_apb;
		CHECK_KNULL(p_apb_data);
		p_weight_data = p_phys_db->inf_set[setNum].inf_weight;
		CHECK_KNULL(p_weight_data);
		sec_typ = setNum;//PE_LGSR_DDR_O26F22_SEC_TYPE
		/* header */
		p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
		p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
		p_phys_db->inf_set[sec_typ].header.version   = p_shdw_db->sec_d[sec_typ].header.version;
		p_phys_db->inf_set[sec_typ].header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
		/* data */
		size = ((PE_LGSR_DDR_O26F22_INF_WEIGHT_SIZE+PE_LGSR_DDR_O26F22_INF_APB_SIZE+PE_LGSR_DDR_O26F22_INF_DUMMY_SIZE) * sizeof(UINT32));
		if(sec_typ == 0)//PE_LGSR_DDR_O26F22_SEC_INF_SET_00
		{
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.db_base+sizeof(PE_LGSR_DDR_O26F22_TOP_HEADER_T);
		}
		else
		{
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
		}
		p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_LGSR_DDR_O26F22_HEADER_T);
		p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
		p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
		p_shdw_db->sec_d[sec_typ].data_base = \
			p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_LGSR_DDR_O26F22_HEADER_T);
		p_shdw_db->sec_d[sec_typ].header.base_apb  = p_shdw_db->sec_d[sec_typ].data_base;
		p_shdw_db->sec_d[sec_typ].header.base_weight = \
			p_shdw_db->sec_d[sec_typ].header.base_apb + \
			((PE_LGSR_DDR_O26F22_INF_APB_SIZE+PE_LGSR_DDR_O26F22_INF_DUMMY_SIZE) * sizeof(UINT32));
		p_phys_db->inf_set[sec_typ].header.base_apb= p_shdw_db->sec_d[sec_typ].header.base_apb;
		p_phys_db->inf_set[sec_typ].header.base_weight= p_shdw_db->sec_d[sec_typ].header.base_weight;
		/* wr ddr */
		memcpy(p_apb_data,p_user_db->inf_set[setNum].inf_apb,\
		(PE_LGSR_DDR_O26F22_INF_APB_SIZE * sizeof(UINT32)));
		memcpy(p_weight_data,p_user_db->inf_set[setNum].inf_weight,\
		(PE_LGSR_DDR_O26F22_INF_WEIGHT_SIZE * sizeof(UINT32)));
		/* noti */
		PE_PRINT_NOTI("%s: DL done.(base:0x%08x)(apb:0x%08x)(weight:0x%08x)\n", \
			PE_LGSR_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],\
			p_shdw_db->sec_d[sec_typ].header.base_apb, p_shdw_db->sec_d[sec_typ].header.base_weight);
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
#endif
int PE_LGSR_HW_O26_SetSrSQM(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PQ_PRINT_NOTI("set sqm : %d\n",onoff);
		_g_pe_fwi_o26_ipc_20.sr_sqm_enalbe = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_SetSrSQM() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_HaltTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {

		PE_DBG_FWI("halt tra : %d\n",onoff);
		_g_pe_fwi_o26_ipc_20.tra_halt = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_HaltTRA() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_RunTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 reg_ipc22 = 0x1;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRTRAVLD_RUN;
	do {
		PE_DBG_FWI("run_tra : %d\n",onoff);
		_g_pe_fwi_o26_ipc_22.tra_or_valid_run = GET_BITS(reg_ipc22,0,2);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_22 : 0x%08x\n", _g_pe_fwi_o26_ipc_22);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_22, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_RunTRA() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_SetCropSize(UINT32 *pPosition)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	PE_INF_O26_SETTINGS_T inf_set;
	static UINT32 pos_count=1;
	//DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRSQM_POS;
	do {
		CHECK_KNULL(pPosition);
		ret = PE_INF_O26_GetCurInfSettings(&inf_set);
		PE_FWI_O26_CHECK_CODE(ret,break,
			"PE_INF_O26_GetCurInfSettings() error.\n");
		if(inf_set.disp_info[0].act_fmt) // if seamless
			return 0;

		PE_DBG_FWI("crop_position x, y : 0x%08x, 0x%08x\n",pPosition[0], pPosition[1]);
		_g_pe_fwi_o26_crop_pos.sr_sqm_position_x =  GET_BITS(pPosition[0],0,12);
		_g_pe_fwi_o26_crop_pos.sr_sqm_position_y =  GET_BITS(pPosition[1],0,12);
		//PE_DBG_FWI("_g_pe_fwi_o26_crop_pos : 0x%08x\n", _g_pe_fwi_o26_crop_pos);
		PE_MCU_O26_QWr03(ad_gen_14, sr_sqm_position_y, GET_BITS(pPosition[1],0,12),\
									sr_sqm_position_x, GET_BITS(pPosition[0],0,12),\
									pos_count,         GET_BITS(pos_count++,0,2));
		if(pos_count ==4)
			pos_count =0;
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_UserReady(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("user data ready : %d\n",onoff);
		_g_pe_fwi_o26_ipc_20.user_data_ready= GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_UserReady() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_ValidRun(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 reg_ipc22 = 0x2;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRTRAVLD_RUN;
	do {
		PE_DBG_FWI("vaild Run : %d\n",onoff);
		_g_pe_fwi_o26_ipc_22.tra_or_valid_run = GET_BITS(reg_ipc22,0,2);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_22 : 0x%08x\n", _g_pe_fwi_o26_ipc_22);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_22, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_ValidRun() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_DemoMode(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PQ_STOREMODE;
	__attribute__((unused)) UINT32 srOnOff = 0;
	__attribute__((unused)) UINT32 srLeftRight = 0;
	do {
		if(onoff == 0x0)
		{
			srOnOff = 0x0;
		}
		else if(onoff == 0x1)
		{
			srOnOff = 0x1;
			srLeftRight = 0x0;
		}
		else if(onoff == 0x2)
		{
			srOnOff = 0x1;
			srLeftRight = 0x1;
		}
		else
		{
			PE_DBG_FWI("wrong UI value %d:\n", onoff);
			return RET_ERROR;
		}
		PE_DBG_FWI("sr-sqm demo mode on/off : %d\n",onoff);
		PE_DBG_FWI("sr-sqm demo mode srOnOff : %d\n",srOnOff);
		PE_DBG_FWI("sr-sqm demo mode srLeftRight : %d\n",srLeftRight);
		_g_pe_fwi_o26_ipc_23.sr_demo_onoff = GET_BITS(srOnOff,0,1);
		_g_pe_fwi_o26_ipc_23.left_or_right = GET_BITS(srLeftRight,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_23 : 0x%08x\n", _g_pe_fwi_o26_ipc_23);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_23, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_DemoMode() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_FWI_HW_O26_ObcDemoMode(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PQ_STOREMODE;
	__attribute__((unused)) UINT32 srOnOff = 0;
	__attribute__((unused)) UINT32 srLeftRight = 0;
	do {
		PE_DBG_FWI("obc demo mode on/off : %d\n",onoff);
		_g_pe_fwi_o26_ipc_23.obc_demo_onoff = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_23 : 0x%08x\n", _g_pe_fwi_o26_ipc_23);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_23, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_OBC_HW_O26_DemoMode() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set sr-sqm accelerated mode
 *
 * @param   *pstParams [in/out] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_LGSR_HW_O26_AccelModeSrSqm(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("set accel sr-sqm : %d\n",onoff);
		_g_pe_fwi_o26_ipc_20.accel_srsqm = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_AccelModeSrSqm() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set tra accelerated mode
 *
 * @param   *pstParams [in/out] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_LGSR_HW_O26_AccelModeTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("set accel tra : %d\n",onoff);
		_g_pe_fwi_o26_ipc_20.accel_tra= GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_AccelModeTRA() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * print LGSR status
 *
 * @param   *pstParams [in/out] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_LGSR_HW_O26_PrintLGSRStatus(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do {
		//PE_PRINT_NOTI(" PE_O26_REG_FW_IPC_20_T : 0x%08x \n", _g_pe_fwi_o26_ipc_20);
		PE_PRINT_NOTI("	sr_inference_mode: 0x%x \n", _g_pe_fwi_o26_ipc_20.sr_inference_mode);
		PE_PRINT_NOTI("	sr_sqm_enalbe    : 0x%x \n", _g_pe_fwi_o26_ipc_20.sr_sqm_enalbe);
		PE_PRINT_NOTI("	user_data_ready  : 0x%x \n", _g_pe_fwi_o26_ipc_20.user_data_ready);
		PE_PRINT_NOTI("	tra_halt         : 0x%x \n", _g_pe_fwi_o26_ipc_20.tra_halt);
		PE_PRINT_NOTI("	srsqm_ui         : 0x%x \n", _g_pe_fwi_o26_ipc_20.srsqm_ui);
		PE_PRINT_NOTI("	accel_srsqm      : 0x%x \n", _g_pe_fwi_o26_ipc_20.accel_srsqm);
		PE_PRINT_NOTI("	accel_tra        : 0x%x \n", _g_pe_fwi_o26_ipc_20.accel_tra);
		PE_PRINT_NOTI("********************\n");
		//PE_PRINT_NOTI(" PE_O26_REG_FW_IPC_21_T : 0x%08x \n", _g_pe_fwi_o26_crop_pos);
		PE_PRINT_NOTI("	sr_sqm_position_y: 0x%x \n", _g_pe_fwi_o26_crop_pos.sr_sqm_position_y);
		PE_PRINT_NOTI("	sr_sqm_position_x: 0x%x \n", _g_pe_fwi_o26_crop_pos.sr_sqm_position_x);
		PE_PRINT_NOTI("********************\n");
		//PE_PRINT_NOTI(" PE_O26_REG_FW_IPC_22_T : 0x%08x \n", _g_pe_fwi_o26_ipc_22);
		PE_PRINT_NOTI("	tra_or_valid_run : 0x%x \n", _g_pe_fwi_o26_ipc_22.tra_or_valid_run);
		PE_PRINT_NOTI("********************\n");
		//PE_PRINT_NOTI(" PE_O26_REG_FW_IPC_23_T : 0x%08x \n", _g_pe_fwi_o26_ipc_23);
		PE_PRINT_NOTI("	sr_demo_onoff    : 0x%x \n", _g_pe_fwi_o26_ipc_23.sr_demo_onoff);
		PE_PRINT_NOTI("	obc_demo_onoff   : 0x%x \n", _g_pe_fwi_o26_ipc_23.obc_demo_onoff);
		PE_PRINT_NOTI("********************\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set LGSR on/off
 *
 * @param   *pstParams [in/out] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_LGSR_HW_O26_UIOnoff(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PQ_PRINT_NOTI("ui on/ff : %d\n",onoff);
		_g_pe_fwi_o26_ipc_20.srsqm_ui = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_o26_ipc_20 : 0x%08x\n", _g_pe_fwi_o26_ipc_20);
		ret = PE_FWI_O26_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o26_ipc_20, sizeof(UINT32));
		PE_FWI_O26_CHECK_CODE(ret,break,"PE_LGSR_HW_O26_UIOnoff() error.\n");
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_GetLneStatus(UINT32 *status)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	do {
		PE_REG_PHYS_RdFL(gPE_MCU_O26,data,reg_mcu_ad_lne_ctrl_1);
		*status = PE_REG_SHDW_Rd32(gPE_MCU_O26,data,reg_mcu_ad_lne_ctrl_1);
		PE_DBG_FWI("reg_mcu_ad_lne_ctrl_1 : 0x%08x\n", *status);
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O26_GetTraStatus(UINT32 *status)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	do {
		PE_REG_PHYS_RdFL(gPE_MCU_O26,data,reg_mcu_ad_lne_ctrl_0);
		*status = PE_REG_SHDW_Rd32(gPE_MCU_O26,data,reg_mcu_ad_lne_ctrl_0);
		PE_DBG_FWI("reg_mcu_ad_lne_ctrl_0 : 0x%08x\n", *status);
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
