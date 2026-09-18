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

/** @file pe_fwi_m23.c
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

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_fwi_m23.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_M23_FW_SRC_OFF		(0)
#define PE_FWI_M23_FW_SRC_ON		(1)
#define PE_FWI_M23_FW_RESET_STATUS_OFF		(0)
#define PE_FWI_M23_FW_RESET_STATUS_ON		(1)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_M23_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if (_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#ifdef INCLUDE_KDRV_DE
#define PE_FWI_M23_IPC0_CHK_NULL()		\
	PE_FWI_M23_CHECK_CODE((pe_fwi_m23_mcu0_ipc==NULL || \
	pe_fwi_m23_mcu0_ipc->m_ipc_client->write==NULL || \
	pe_fwi_m23_mcu0_ipc->m_ipc_client->read==NULL), \
	ret = RET_ERROR;break, "mcu0_ipc is null.\n")

#define PE_FWI_M23_IPC0_CHK_READY()		\
	PE_FWI_M23_CHECK_CODE(pe_fwi_m23_mcu0_ipc->p_ready==NULL, \
	ret = RET_ERROR;break, "mcu0_ipc is not ready.\n")

#define PE_FWI_M23_IPC0_SET_DATA(cmd, msg, size)		\
	pe_fwi_m23_mcu0_ipc->m_ipc_client->write(cmd, msg, size)
#define PE_FWI_M23_IPC0_GET_DATA(mcu, msg, size)		\
	pe_fwi_m23_mcu0_ipc->m_ipc_client->read(mcu, msg, size)

#define PE_FWI_M23_IPC1_CHK_NULL()		\
	PE_FWI_M23_CHECK_CODE((pe_fwi_m23_mcu1_ipc==NULL || \
	pe_fwi_m23_mcu1_ipc->m_ipc_client->write==NULL || \
	pe_fwi_m23_mcu1_ipc->m_ipc_client->read==NULL), \
	ret = RET_ERROR;break, "mcu1_ipc is null.\n")

#define PE_FWI_M23_IPC1_CHK_READY()		\
	PE_FWI_M23_CHECK_CODE(pe_fwi_m23_mcu1_ipc->p_ready==NULL, \
	ret = RET_ERROR;break, "mcu1_ipc is not ready.\n")

#define PE_FWI_M23_IPC1_SET_DATA(cmd, msg, size)		\
	pe_fwi_m23_mcu1_ipc->m_ipc_client->write(cmd, msg, size)
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
#define PE_FWI_M23_CHECK_REFRESH_TBL( )	\
	do {\
		PE_FWI_M23_SETTINGS_T *p_temp_info = &_g_pe_fwi_m23_info;\
		if ((p_temp_info->fw_status.reset) == PE_FWI_M23_FW_RESET_STATUS_ON)\
		{\
			PE_DBG_FWI("RESET ON, fw src_info:%d\n",p_temp_info->fw_status.src_info);\
			ret = PE_FWI_M23_RefreshFwTable();\
			PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_RefreshFwTable() error.\n");\
			(p_temp_info->fw_status.reset) = PE_FWI_M23_FW_RESET_STATUS_OFF;\
		}\
	} while (0)

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
}PE_M23_REG_FW_IPC_20_T;
typedef struct
{
	UINT32
	sr_sqm_position_y                  :12 ,	// 11:0
	sr_sqm_position_x                  :12 ,	// 23:12
	pos_count                              :2  ;	// 25:24
}PE_M23_REG_FW_CROP_POS_T;
typedef struct
{
	UINT32
	tra_or_valid_run                   :2 ;	// 1:0 , 0x1: tra_run, 0x2: valid_run
}PE_M23_REG_FW_IPC_22_T;
typedef struct
{
	UINT32
	sr_demo_onoff                      :1 ,	// 0:0
	reserved0                          :3 ,	// 3:1
	left_or_right                      :1 ,	// 4    [0: left is DNN-SR result, 1: right is  DNN-SR result]
	reserved1                          :11, // 15:5
	obc_demo_onoff                     :1 ;	// 16
}PE_M23_REG_FW_IPC_23_T;

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
struct ipc_handle *pe_fwi_m23_mcu0_ipc = NULL;
struct ipc_handle *pe_fwi_m23_mcu1_ipc = NULL;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_FWI_M23_IPC_SetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
static int PE_FWI_M23_IPC_GetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
static int PE_FWI_M23_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize);
static int PE_FWI_M23_RefreshFwTable(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_FWI_M23_SETTINGS_T _g_pe_fwi_m23_info;
static PE_M23_REG_FW_IPC_20_T _g_pe_fwi_m23_ipc_20;
static PE_M23_REG_FW_CROP_POS_T _g_pe_fwi_m23_crop_pos;
static PE_M23_REG_FW_IPC_22_T _g_pe_fwi_m23_ipc_22;
static PE_M23_REG_FW_IPC_23_T _g_pe_fwi_m23_ipc_23;

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
static int PE_FWI_M23_IPC_SetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pMsg);
		PE_DBG_FWI("mcuId:%d, ipcCmd:0x%08X, msgCnt:%d\n", mcuId, ipcCmd, msgCnt);

		if (mcuId == MCU_ID_0 || mcuId == MCU_ID_1)
		{
			PE_FWI_M23_IPC0_CHK_NULL();
			PE_FWI_M23_IPC0_CHK_READY();
			PE_FWI_M23_IPC0_SET_DATA(ipcCmd, pMsg, msgCnt);
		}
		else
		{
			PE_PRINT_ERROR("mcuId(%d) is invalid.\n", mcuId);
			ret = RET_ERROR;
		}

	} while (0);
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
static int PE_FWI_M23_IPC_GetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pMsg);
		PE_DBG_FWI("mcuId:%d, ipcCmd:0x%08X, msgCnt:%d\n", mcuId, ipcCmd, msgCnt);

		if (mcuId == MCU_ID_0 || mcuId == MCU_ID_1)
		{
			PE_FWI_M23_IPC0_CHK_NULL();
			PE_FWI_M23_IPC0_CHK_READY();
			PE_FWI_M23_IPC0_GET_DATA(mcuId, pMsg, msgCnt);
		}
		else
		{
			PE_PRINT_ERROR("mcuId(%d) is invalid.\n", mcuId);
			ret = RET_ERROR;
		}

	} while (0);
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
static int PE_FWI_M23_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize)
{
	int ret = RET_OK;
	UINT32 offset;
	UINT32 length;
	UINT32 dataSize;
	UINT8 *pData = NULL;
	DE_IPC_CMD_T ipcCmd = PQL_IPC_SET_TABLE;
	do {
		offset = header.offset;
		length = header.length;
		PE_FWI_M23_CHECK_CODE(!length, break, "length is zero.\n");
		PE_FWI_M23_CHECK_CODE(!pTable, break, "pTable is null.\n");
		PE_FWI_M23_CHECK_CODE(!tblSize, break, "tblSize is zero.\n");
		PE_FWI_M23_CHECK_CODE(((offset+length)>tblSize), break, \
			"offset(%d) and length(%d) is greater than tblSize(%d).\n", \
			offset, length, tblSize);
		PE_DBG_FWI(" wid:%d, ofs:%d, len:%d, tbl_size:%d\n", \
			header.win_id, header.offset, header.length, tblSize);
		dataSize = sizeof(header)+length;
		pData = OS_KMalloc(dataSize);
		PE_FWI_M23_CHECK_CODE(!pData, break, "pData is null.\n");
		memcpy(pData, &header, sizeof(header));
		memcpy(&pData[sizeof(header)], &pTable[offset], length);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipcCmd, pData, dataSize);
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
	} while (0);
	if (pData)	OS_Free(pData);
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
static int PE_FWI_M23_RefreshFwTable(void)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_M23_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_M23_SETTINGS_T *pInfo=&_g_pe_fwi_m23_info;
	do {
		pTable = (UINT8 *)&table;
		tbl_size = sizeof(PE_FWI_M23_PQ_IPC_CTRL);
		header.win_id = LX_PE_WIN_0;
		header.offset = PE_FWI_M23_REFRESH_TBL_OFST;
		header.length = PE_FWI_M23_REFRESH_TBL_SIZE;
		memcpy(&(table.tnr_ctrl), &(pInfo->tnr_ctrl), sizeof(PE_FWI_M23_TNR_CTRL));
		memcpy(&(table.fw_ctrl), &(pInfo->fw_ctrl), sizeof(PE_FWI_M23_FW_CTRL));
		memcpy(&(table.src_info), &(pInfo->src_info), sizeof(PE_FWI_M23_SRC_INFO));
		memcpy(&(table.dnr_common), &(pInfo->dnr_common), sizeof(PE_FWI_M23_DNR_COMMON));
		memcpy(&(table.dnr_detail), &(pInfo->dnr_detail), sizeof(PE_FWI_M23_DNR_DETAIL));
		memcpy(&(table.shp_e_ctrl), &(pInfo->shp_e_ctrl), sizeof(PE_FWI_M23_EDGE_GAIN));
		memcpy(&(table.shp_t_ctrl), &(pInfo->shp_t_ctrl), sizeof(PE_FWI_M23_TEXTURE_GAIN));

		PE_DBG_FWI("wid:%d, ofs:%d, len:%d, tbl_size:%d\n", \
			header.win_id, header.offset, header.length, tbl_size);
		ret = PE_FWI_M23_SetFwSettings(header,  pTable,  tbl_size);
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_SetFwSettings() error.\n");
	} while (0);
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
int PE_FWI_M23_IPC_Open(void)
{
	int ret = RET_OK;
	do {
		#ifdef INCLUDE_KDRV_DE
		PE_PRINT_NOTI("open ipc\n");
		/* check pe_fwi_m23_mcu0_ipc is already opened */
		if(pe_fwi_m23_mcu0_ipc == NULL)
		{
			pe_fwi_m23_mcu0_ipc = ipc_hal_open("pe", MCU_ID_0);
			PE_FWI_M23_CHECK_CODE(!pe_fwi_m23_mcu0_ipc,ret = RET_ERROR;break,"pe_fwi_m23_mcu0_ipc open fail.\n");
		}
		/* check pe_fwi_m23_mcu1_ipc is already opened */
		if(pe_fwi_m23_mcu1_ipc == NULL)
		{
			pe_fwi_m23_mcu1_ipc = ipc_hal_open("pe", MCU_ID_1);
			PE_FWI_M23_CHECK_CODE(!pe_fwi_m23_mcu1_ipc,ret = RET_ERROR;break,"pe_fwi_m23_mcu1_ipc open fail.\n");
		}
		#endif
	} while (0);
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
int PE_FWI_M23_IPC_Close(void)
{
	int ret = RET_OK;
	do {
		#ifdef INCLUDE_KDRV_DE
		PE_PRINT_NOTI("close ipc\n");
		if (pe_fwi_m23_mcu0_ipc)
		{
			ipc_hal_close(pe_fwi_m23_mcu0_ipc);
			pe_fwi_m23_mcu0_ipc = NULL;
		}
		if (pe_fwi_m23_mcu1_ipc)
		{
			ipc_hal_close(pe_fwi_m23_mcu1_ipc);
			pe_fwi_m23_mcu1_ipc = NULL;
		}
		#endif
	} while (0);
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
int PE_FWI_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		PE_DBG_FWI("init global values.\n");
		memset(&_g_pe_fwi_m23_info, 0x0, sizeof(PE_FWI_M23_SETTINGS_T));
		_g_pe_fwi_m23_info.src_info.dtv_mode = 0xff;	//default
		_g_pe_fwi_m23_info.src_info.hdd_mode = 0xff;	//default
		_g_pe_fwi_m23_info.pre_colormetry[0]=_g_pe_fwi_m23_info.pre_colormetry[1]=0xff;
		memset(&_g_pe_fwi_m23_ipc_20, 0x0, sizeof(UINT32));
		memset(&_g_pe_fwi_m23_crop_pos, 0x0, sizeof(UINT32));
		memset(&_g_pe_fwi_m23_ipc_22, 0x0, sizeof(UINT32));
		memset(&_g_pe_fwi_m23_ipc_23, 0x0, sizeof(UINT32));
	} while (0);
	return ret;

}
/**
 * check f/w status(periodic)
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_M23_CheckFwStatus(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_FWI_M23_SETTINGS_T *pInfo=&_g_pe_fwi_m23_info;
	do {
		CHECK_KNULL(pCfg);
		if (pInfo->fw_status.src_info != ctrl0_info->fw_src)
		{
			PE_DBG_FWI("fw_src changed : %d -> %d.\n", \
				pInfo->fw_status.src_info, ctrl0_info->fw_src);
			if ((pInfo->fw_status.src_info != PE_FWI_M23_FW_SRC_OFF) && \
				(ctrl0_info->fw_src == PE_FWI_M23_FW_SRC_OFF))
			{
				PE_DBG_FWI("fw_reset status on\n");
				pInfo->fw_status.reset = PE_FWI_M23_FW_RESET_STATUS_ON;
			}
			pInfo->fw_status.src_info = ctrl0_info->fw_src;
		}
	} while (0);
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
int PE_FWI_M23_LoadDbData(UINT32 base_addr)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_DB_DATA;
	do {
		PE_DBG_FWI("base_addr : 0x%08x\n", base_addr);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &base_addr, sizeof(base_addr));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
	} while (0);
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
int PE_FWI_M23_LoadDbDone(UINT32 *pData, UINT32 size)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_DB_DONE;
	do {
		CHECK_KNULL(pData);
		if (!size)	break;
		PE_DBG_FWI("LoadDbDone(0x%08x)(%d)(%d)(size:%d)\n",pData[0],pData[1],pData[2],size);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, pData, size);
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
	} while (0);
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
int PE_FWI_M23_SetHdrInfo(UINT32 *pInfo)
{
	int ret = RET_OK;
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_HDR_INFO;
	do {
		CHECK_KNULL(pInfo);
		if (pre_info != pInfo[0])
		{
			PE_DBG_FWI("hdr info : 0x%08x <- 0x%08x\n", pInfo[0], pre_info);
			ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
			pre_info = pInfo[0];
		}
	} while (0);
	return ret;
}
/**
 * PE_FWI_M23_GetHdrMode
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_M23_GetHdrMode(UINT32 *pInfo)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_GET_HDR_MODE;
	do {
		CHECK_KNULL(pInfo);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
		ret = PE_FWI_M23_IPC_GetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_GetData() error.\n");
		PE_DBG_FWI("hdr mode : %d\n", pInfo[0]);
	} while (0);
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
int PE_FWI_M23_SetPattern(UINT32 *pInfo)
{
	int ret = RET_OK;
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_TPG;
	do {
		CHECK_KNULL(pInfo);
		if (pre_info != pInfo[0])
		{
			PE_PRINT_NOTI("set pat : 0x%x <- 0x%x\n", pInfo[0], pre_info);
			ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
			pre_info = pInfo[0];
		}
	} while (0);
	return ret;
}
/**
 * set fw cvi csc
 *	- never use this on sync handler
 *
 * @param   *pstParams [in] PE_FWI_M23_CSC_INPUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_M23_SetCviCsc(PE_FWI_M23_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipc_cmd = DE_IPC_SET_CVI_CSC;
	do {
		CHECK_KNULL(pstParams);
		PE_DBG_FWI("set[%d] : idx:%d\n",pstParams->win_id,pstParams->enable);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0,ipc_cmd,(void *)pstParams,sizeof(PE_FWI_M23_CSC_INPUT_T));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
	} while (0);
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
int PE_FWI_M23_SetColorimetry(UINT32 wid, UINT32 *pInfo)
{
	int ret = RET_OK;
	UINT32 pre_info[2] = {0xff,0xff};
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_COLORIMETRY;
	PE_FWI_M23_SETTINGS_T *pFWInfo=&_g_pe_fwi_m23_info;

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
			PE_DBG_FWI("[%d] %d (%x <- %x)\n",info.wid,info.color,pInfo[0],pre_info[wid]);
			ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &info, sizeof(union colorimetry));
			PE_FWI_M23_CHECK_CODE(ret,break,"PE_FWI_M23_IPC_SetData() error.\n");
			pFWInfo->pre_colormetry[wid] = pInfo[0];
		}
	} while (0);
	return ret;
}
/**
 * set src info to f/w
 *	- never use this on sync handler
 *
 * @param   *pstParams [in] PE_FWI_M23_SRC_INFO
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_M23_SetSrcInfo(PE_FWI_M23_SRC_INFO *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_M23_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_M23_SETTINGS_T *pInfo=&_g_pe_fwi_m23_info;
	do {
		CHECK_KNULL(pstParams);
		PE_FWI_M23_CHECK_REFRESH_TBL();
		if ((pInfo->src_info.dtv_mode!=pstParams->dtv_mode) || \
			(pInfo->src_info.hdd_mode!=pstParams->hdd_mode))
		{
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_M23_PQ_IPC_CTRL);
			header.win_id = LX_PE_WIN_0;
			header.offset = PE_FWI_OFFSET(PE_FWI_M23_SRC_INFO);
			header.length = sizeof(PE_FWI_M23_SRC_INFO);
			table.src_info.dtv_mode = pstParams->dtv_mode;
			table.src_info.hdd_mode = pstParams->hdd_mode;
			PE_DBG_FWI("\n wid:%d, ofs:%d, len:%d, "\
				"tbl_size:%d, src_info.dtv:%d->%d, hdd:%d->%d\n", \
				header.win_id, header.offset, header.length, \
				tbl_size, pInfo->src_info.dtv_mode, table.src_info.dtv_mode, \
				pInfo->src_info.hdd_mode, table.src_info.hdd_mode);
			ret = PE_FWI_M23_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_SetFwSettings() error.\n");
			pInfo->src_info.dtv_mode=pstParams->dtv_mode;
			pInfo->src_info.hdd_mode=pstParams->hdd_mode;
		}
		else
		{
			PE_DBG_FWI("src_info.dtv:%d->%d, hdd:%d->%d, same..\n", \
				pInfo->src_info.dtv_mode, pstParams->dtv_mode, \
				pInfo->src_info.hdd_mode, pstParams->hdd_mode);
			ret = RET_OK;
			break;
		}

	} while (0);
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
int PE_FWI_M23_SetPicMode(UINT32 mode)
{
	int ret = RET_OK;
	static UINT32 pre_mode = 0xffffffff;
	UINT32 cur_mode;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PIC_MODE;
	do {
		cur_mode = mode;
		if (pre_mode != cur_mode)
		{
			PE_DBG_FWI("set mode : 0x%08x <- 0x%08x (diff)\n", cur_mode, pre_mode);
			ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &mode, sizeof(mode));
			PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
			pre_mode = cur_mode;
		}
		else
		{
			PE_DBG_FWI("set mode : 0x%08x <- 0x%08x (same)\n", cur_mode, pre_mode);
		}
	} while (0);
	return ret;

}

int PE_FWI_M23_LoadLGSRDbData(UINT32 base_addr)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_SRINF_DB_DATA;
	do {
		PE_DBG_FWI("base_addr : 0x%08x\n", base_addr);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &base_addr, sizeof(base_addr));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
	} while (0);
	#endif
	return ret;
}

int PE_LGSR_HW_M23_DoneDownloadDdr(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		ret = PE_FWI_M23_LoadLGSRDbData(gPeMem[0].base+0x100000);
		if(onoff) //onoff==1 cold booting
		{
			PE_PRINT_NOTI("[Db]LGSR SQM data done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
			PE_INF_HW_M23_BACKUP_TRACE("[Db] lgsr done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
		}
		else  //onoff==0 instance booting
		{
			PE_PRINT_NOTI("[Db]LGSR SQM data already done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
			PE_INF_HW_M23_BACKUP_TRACE("[Db]LGSR SQM data already done_donwload : %d, base: %x\n",onoff,gPeMem[0].base+0x100000);
		}
		_g_pe_fwi_m23_ipc_20.sr_inference_mode = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_FWI_M23_IPC_SetData() error.\n");
	} while (0);
	#endif
	return ret;

}

int PE_LGSR_HW_M23_SetSrSQM(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("set sqm : %d\n",onoff);
		_g_pe_fwi_m23_ipc_20.sr_sqm_enalbe = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_SetSrSQM() error.\n");
	} while (0);
	#endif
	return ret;

}

int PE_LGSR_HW_M23_HaltTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("halt tra : %d\n",onoff);
		_g_pe_fwi_m23_ipc_20.tra_halt = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_HaltTRA() error.\n");
	} while (0);
	#endif
	return ret;
}

int PE_LGSR_HW_M23_RunTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 reg_ipc22 = 0x1;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRTRAVLD_RUN;
	do {
		PE_DBG_FWI("run_tra : %d\n",onoff);
		_g_pe_fwi_m23_ipc_22.tra_or_valid_run = GET_BITS(reg_ipc22,0,2);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_22 : 0x%08x\n", _g_pe_fwi_m23_ipc_22);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_22, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_RunTRA() error.\n");
	} while (0);
	#endif
	return ret;

}
int PE_LGSR_HW_M23_SetCropSize(UINT32 *pPosition)
{
	int ret = RET_OK;
	return ret;
}

int PE_LGSR_HW_M23_UserReady(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("user data ready : %d\n",onoff);
		_g_pe_fwi_m23_ipc_20.user_data_ready= GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_UserReady() error.\n");
	} while (0);
	#endif
	return ret;

}

int PE_LGSR_HW_M23_ValidRun(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 reg_ipc22 = 0x2;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRTRAVLD_RUN;
	do {
		PE_DBG_FWI("vaild Run : %d\n",onoff);
		_g_pe_fwi_m23_ipc_22.tra_or_valid_run = GET_BITS(reg_ipc22,0,2);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_22 : 0x%08x\n", _g_pe_fwi_m23_ipc_22);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_22, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_ValidRun() error.\n");
	} while (0);
	#endif
	return ret;

}

int PE_LGSR_HW_M23_DemoMode(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PQ_STOREMODE;
	__attribute__((unused)) UINT32 srOnOff = 0;
	__attribute__((unused)) UINT32 srLeftRight = 0;
	do {
		if (PE_KDRV_VER_M23)
		{
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
			_g_pe_fwi_m23_ipc_23.sr_demo_onoff = GET_BITS(srOnOff,0,1);
			_g_pe_fwi_m23_ipc_23.left_or_right = GET_BITS(srLeftRight,0,1);
			//PE_DBG_FWI("_g_pe_fwi_m23_ipc_23 : 0x%08x\n", _g_pe_fwi_m23_ipc_23);
			ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_23, sizeof(UINT32));
			PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_DemoMode() error.\n");
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

int PE_FWI_HW_M23_ObcDemoMode(UINT32 onoff)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PQ_STOREMODE;
	__attribute__((unused)) UINT32 srOnOff = 0;
	__attribute__((unused)) UINT32 srLeftRight = 0;
	do {
		PE_DBG_FWI("obc demo mode on/off : %d\n",onoff);
		_g_pe_fwi_m23_ipc_23.obc_demo_onoff = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_23 : 0x%08x\n", _g_pe_fwi_m23_ipc_23);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_23, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_OBC_HW_M23_DemoMode() error.\n");
	} while (0);
	#endif
	return ret;
}

int PE_LGSR_HW_M23_AccelModeSrSqm(UINT32 onoff)
{
	int ret = RET_OK;
#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("set accel sr-sqm : %d\n",onoff);
		_g_pe_fwi_m23_ipc_20.accel_srsqm = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_AccelModeSrSqm() error.\n");
	} while (0);
#endif
	return ret;

}

int PE_LGSR_HW_M23_AccelModeTRA(UINT32 onoff)
{
	int ret = RET_OK;
#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("set accel tra : %d\n",onoff);
		_g_pe_fwi_m23_ipc_20.accel_tra= GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_AccelModeTRA() error.\n");
	} while (0);
#endif
	return ret;

}

int PE_LGSR_HW_M23_PrintLGSRStatus(void)
{
	int ret = RET_OK;
	//PE_PRINT_NOTI(" PE_M23_REG_FW_IPC_20_T : 0x%08x \n", _g_pe_fwi_m23_ipc_20);//need to fix warning
	PE_PRINT_NOTI("	sr_inference_mode: 0x%x \n", _g_pe_fwi_m23_ipc_20.sr_inference_mode);
	PE_PRINT_NOTI("	sr_sqm_enalbe    : 0x%x \n", _g_pe_fwi_m23_ipc_20.sr_sqm_enalbe);
	PE_PRINT_NOTI("	user_data_ready  : 0x%x \n", _g_pe_fwi_m23_ipc_20.user_data_ready);
	PE_PRINT_NOTI("	tra_halt         : 0x%x \n", _g_pe_fwi_m23_ipc_20.tra_halt);
	PE_PRINT_NOTI("	srsqm_ui         : 0x%x \n", _g_pe_fwi_m23_ipc_20.srsqm_ui);
	PE_PRINT_NOTI("	accel_srsqm      : 0x%x \n", _g_pe_fwi_m23_ipc_20.accel_srsqm);
	PE_PRINT_NOTI("	accel_tra        : 0x%x \n", _g_pe_fwi_m23_ipc_20.accel_tra);
	PE_PRINT_NOTI("********************\n");
	//PE_PRINT_NOTI(" PE_M23_REG_FW_IPC_21_T : 0x%08x \n", _g_pe_fwi_m23_crop_pos);//need to fix warning
	PE_PRINT_NOTI("	sr_sqm_position_y: 0x%x \n", _g_pe_fwi_m23_crop_pos.sr_sqm_position_y);
	PE_PRINT_NOTI("	sr_sqm_position_x: 0x%x \n", _g_pe_fwi_m23_crop_pos.sr_sqm_position_x);
	PE_PRINT_NOTI("********************\n");
	//PE_PRINT_NOTI(" PE_M23_REG_FW_IPC_22_T : 0x%08x \n", _g_pe_fwi_m23_ipc_22);//need to fix warning
	PE_PRINT_NOTI("	tra_or_valid_run : 0x%x \n", _g_pe_fwi_m23_ipc_22.tra_or_valid_run);
	PE_PRINT_NOTI("********************\n");
	//PE_PRINT_NOTI(" PE_M23_REG_FW_IPC_23_T : 0x%08x \n", _g_pe_fwi_m23_ipc_23);//need to fix warning
	PE_PRINT_NOTI("	sr_demo_onoff    : 0x%x \n", _g_pe_fwi_m23_ipc_23.sr_demo_onoff);
	PE_PRINT_NOTI("	obc_demo_onoff   : 0x%x \n", _g_pe_fwi_m23_ipc_23.obc_demo_onoff);
	PE_PRINT_NOTI("********************\n");
	return ret;

}

int PE_LGSR_HW_M23_UIOnoff(UINT32 onoff)
{
	int ret = RET_OK;
#ifndef PE_HW_M23_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do {
		PE_DBG_FWI("ui on/ff : %d\n",onoff);
		_g_pe_fwi_m23_ipc_20.srsqm_ui = GET_BITS(onoff,0,1);
		//PE_DBG_FWI("_g_pe_fwi_m23_ipc_20 : 0x%08x\n", _g_pe_fwi_m23_ipc_20);
		ret = PE_FWI_M23_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_m23_ipc_20, sizeof(UINT32));
		PE_FWI_M23_CHECK_CODE(ret, break, "PE_LGSR_HW_M23_UIOnoff() error.\n");
	} while (0);
#endif
	return ret;

}

int PE_LGSR_HW_M23_GetLneStatus(UINT32 *status)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do {
		PE_REG_PHYS_RdFL(gPE_MCU_M23,data,reg_mcu_ad_lne_ctrl_1);
		*status = PE_REG_SHDW_Rd32(gPE_MCU_M23,data,reg_mcu_ad_lne_ctrl_1);
		PE_DBG_FWI("reg_mcu_ad_lne_ctrl_1 : 0x%08x\n", *status);
	} while (0);
	#endif
	return ret;
}
int PE_LGSR_HW_M23_GetTraStatus(UINT32 *status)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do {
		PE_REG_PHYS_RdFL(gPE_MCU_M23,data,reg_mcu_ad_lne_ctrl_0);
		*status = PE_REG_SHDW_Rd32(gPE_MCU_M23,data,reg_mcu_ad_lne_ctrl_0);
		PE_DBG_FWI("reg_mcu_ad_lne_ctrl_0 : 0x%08x\n", *status);
	} while (0);
	#endif
	return ret;
}
