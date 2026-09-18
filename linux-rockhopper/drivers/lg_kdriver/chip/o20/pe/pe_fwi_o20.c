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

/** @file pe_fwi_o20.c
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

#include "pe_hw_o20.h"
#include "pe_reg_o20.h"
#include "pe_fwi_o20.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#undef PE_FWI_O20_USE_PACK_CMD

#define PE_FWI_O20_FW_SRC_OFF		(0)
#define PE_FWI_O20_FW_SRC_ON		(1)
#define PE_FWI_O20_FW_RESET_STATUS_OFF		(0)
#define PE_FWI_O20_FW_RESET_STATUS_ON		(1)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_O20_ERROR	PE_PRINT_ERROR

#define PE_FWI_O20_DBG_PRINT(fmt, args...)	\
	if (_g_fwi_o20_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, PE_CHIP_VER, \
			g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}
#define PE_FWI_O20_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if (_checker){PE_FWI_O20_ERROR(fmt, ##args);_action;}}

#define PE_FWI_O20_IPC0_CHK_NULL()		\
	PE_FWI_O20_CHECK_CODE((pe_fwi_o20_mcu0_ipc==NULL || \
	pe_fwi_o20_mcu0_ipc->m_ipc_client->write==NULL || \
	pe_fwi_o20_mcu0_ipc->m_ipc_client->read==NULL), \
	ret = RET_ERROR;break, "[%s,%d] mcu0_ipc is null.\n", __F__, __L__)

#define PE_FWI_O20_IPC0_CHK_READY()		\
	PE_FWI_O20_CHECK_CODE(pe_fwi_o20_mcu0_ipc->p_ready==NULL, \
	ret = RET_ERROR;break, "[%s,%d] mcu0_ipc is not ready.\n", __F__, __L__)

#define PE_FWI_O20_IPC0_SET_DATA(cmd, msg, size)		\
	pe_fwi_o20_mcu0_ipc->m_ipc_client->write(cmd, msg, size)
#define PE_FWI_O20_IPC0_GET_DATA(mcu, msg, size)		\
	pe_fwi_o20_mcu0_ipc->m_ipc_client->read(mcu, msg, size)

#define PE_FWI_O20_IPC1_CHK_NULL()		\
	PE_FWI_O20_CHECK_CODE((pe_fwi_o20_mcu1_ipc==NULL || \
	pe_fwi_o20_mcu1_ipc->m_ipc_client->write==NULL || \
	pe_fwi_o20_mcu1_ipc->m_ipc_client->read==NULL), \
	ret = RET_ERROR;break, "[%s,%d] mcu1_ipc is null.\n", __F__, __L__)

#define PE_FWI_O20_IPC1_CHK_READY()		\
	PE_FWI_O20_CHECK_CODE(pe_fwi_o20_mcu1_ipc->p_ready==NULL, \
	ret = RET_ERROR;break, "[%s,%d] mcu1_ipc is not ready.\n", __F__, __L__)

#define PE_FWI_O20_IPC1_SET_DATA(cmd, msg, size)		\
	pe_fwi_o20_mcu1_ipc->m_ipc_client->write(cmd, msg, size)

#define PE_PACK_CMD(_id, _cmd) 	PACK_CMD(0, 0, (_id), (_cmd))

/* define for refresh pq fw table when fw reset */
#define PE_FWI_O20_CHECK_REFRESH_TBL( )	\
	do{\
		if (PE_KDRV_VER_O20)\
		{\
			PE_FWI_O20_SETTINGS_T *p_temp_info = &_g_pe_fwi_o20_info;\
			if ((p_temp_info->fw_status.reset) == PE_FWI_O20_FW_RESET_STATUS_ON)\
			{\
				PE_FWI_O20_DBG_PRINT("RESET ON, fw src_info:%d\n", \
					p_temp_info->fw_status.src_info);\
				ret = PE_FWI_O20_RefreshFwTable();\
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_RefreshFwTable() error.\n", __F__, __L__);\
				(p_temp_info->fw_status.reset) = PE_FWI_O20_FW_RESET_STATUS_OFF;\
			}\
		}\
	}while (0)

#define PE_MCU_O20_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_MCU_O20,data,_r);\
		PE_REG_SHDW_Wr03(gPE_MCU_O20,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_MCU_O20,data,_r);}

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
}PE_O20_REG_FW_IPC_20_T;
typedef struct
{
	UINT32
	sr_sqm_position_y                  :12 ,	// 11:0
	sr_sqm_position_x                  :12 ,	// 23:12
	pos_count                              :2  ;	// 25:24
}PE_O20_REG_FW_CROP_POS_T;
typedef struct
{
	UINT32
	tra_or_valid_run                   :2 ;	// 1:0 , 0x1: tra_run, 0x2: valid_run
}PE_O20_REG_FW_IPC_22_T;
typedef struct
{
	UINT32
	sr_demo_onoff                      :1 ,	// 0:0
	reserved0                          :3 ,	// 3:1
	left_or_right                      :1 ,	// 4    [0: left is DNN-SR result, 1: right is  DNN-SR result]
	reserved1                          :11, // 15:5
	obc_demo_onoff                     :1 ;	// 16
}PE_O20_REG_FW_IPC_23_T;


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
				
extern LX_DE_IPC_SYSTEM_INFO_T g_pe_lgsr_mem_info;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
struct ipc_handle *pe_fwi_o20_mcu0_ipc = NULL;
struct ipc_handle *pe_fwi_o20_mcu1_ipc = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_FWI_O20_IPC_SetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
static int PE_FWI_O20_IPC_GetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
static int PE_FWI_O20_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize);
static int PE_FWI_O20_RefreshFwTable(void);
static int PE_LGSR_HW_O20_DownloadLGSRDb(UINT32 *pUser);
static int PE_LGSR_HW_O20_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser);
static int PE_LGSR_HW_F20_DownloadLGSRDb(UINT32 *pUser);
static int PE_LGSR_HW_F20_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser);
static int PE_LGSR_HW_O20_CompareLGSRDb(UINT32 *pUser, UINT32 base_user);
static int PE_LGSR_HW_O20_CompareLGSROneSet(UINT32 setNum, UINT32* pUser, UINT32 base_user);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_fwi_o20_trace=0x0;	//default should be off.
static PE_FWI_O20_SETTINGS_T _g_pe_fwi_o20_info;
static PE_O20_REG_FW_IPC_20_T _g_pe_fwi_o20_ipc_20;
static PE_O20_REG_FW_CROP_POS_T _g_pe_fwi_o20_crop_pos;
static PE_O20_REG_FW_IPC_22_T _g_pe_fwi_o20_ipc_22;
static PE_O20_REG_FW_IPC_23_T _g_pe_fwi_o20_ipc_23;

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
static int PE_FWI_O20_IPC_SetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pMsg);
		PE_FWI_O20_DBG_PRINT("mcuId:%d, ipcCmd:0x%08X, msgCnt:%d\n", mcuId, ipcCmd, msgCnt);
		if (PE_KDRV_VER_O20)
		{
			if (mcuId == MCU_ID_0 || mcuId == MCU_ID_1)
			{
				PE_FWI_O20_IPC0_CHK_NULL();
				PE_FWI_O20_IPC0_CHK_READY();
				#ifdef PE_FWI_O20_USE_PACK_CMD
				PE_FWI_O20_IPC0_SET_DATA(PE_PACK_CMD(mcuId, ipcCmd), pMsg, msgCnt);
				#else
				PE_FWI_O20_IPC0_SET_DATA(ipcCmd, pMsg, msgCnt);
				#endif
			}
			else
			{
				PE_FWI_O20_ERROR("[%s,%d] mcuId(%d) is invalid.\n", __F__, __L__, mcuId);
				ret = RET_ERROR;
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while (0);
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
static int PE_FWI_O20_IPC_GetData(UINT32 mcuId, UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pMsg);
		PE_FWI_O20_DBG_PRINT("mcuId:%d, ipcCmd:0x%08X, msgCnt:%d\n", mcuId, ipcCmd, msgCnt);
		if (PE_KDRV_VER_O20)
		{
			if (mcuId == MCU_ID_0 || mcuId == MCU_ID_1)
			{
				PE_FWI_O20_IPC0_CHK_NULL();
				PE_FWI_O20_IPC0_CHK_READY();
				PE_FWI_O20_IPC0_GET_DATA(mcuId, pMsg, msgCnt);
			}
			else
			{
				PE_FWI_O20_ERROR("[%s,%d] mcuId(%d) is invalid.\n", __F__, __L__, mcuId);
				ret = RET_ERROR;
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while (0);
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
static int PE_FWI_O20_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 offset;
	UINT32 length;
	UINT32 dataSize;
	UINT8 *pData = NULL;
	DE_IPC_CMD_T ipcCmd = PQL_IPC_SET_TABLE;
	do{
		offset = header.offset;
		length = header.length;
		PE_FWI_O20_CHECK_CODE(!length, break, "[%s,%d] length is zero.\n", __F__, __L__);
		PE_FWI_O20_CHECK_CODE(!pTable, break, "[%s,%d] pTable is null.\n", __F__, __L__);
		PE_FWI_O20_CHECK_CODE(!tblSize, break, "[%s,%d] tblSize is zero.\n", __F__, __L__);
		PE_FWI_O20_CHECK_CODE(((offset+length)>tblSize), break, \
			"[%s,%d] offset(%d) and length(%d) is greater than tblSize(%d).\n", \
			__F__, __L__, offset, length, tblSize);
		PE_FWI_O20_DBG_PRINT(" wid:%d, ofs:%d, len:%d, tbl_size:%d\n", \
			header.win_id, header.offset, header.length, tblSize);
		dataSize = sizeof(header)+length;
		pData = OS_KMalloc(dataSize);
		PE_FWI_O20_CHECK_CODE(!pData, break, "[%s,%d] pData is null.\n", __F__, __L__);
		memcpy(pData, &header, sizeof(header));
		memcpy(&pData[sizeof(header)], &pTable[offset], length);
		ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipcCmd, pData, dataSize);
		PE_FWI_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
	}while (0);
	if (pData)	OS_Free(pData);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_FWI_O20_RefreshFwTable(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_O20_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_O20_SETTINGS_T *pInfo=&_g_pe_fwi_o20_info;
	do{
		if (PE_KDRV_VER_O20)
		{
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_O20_PQ_IPC_CTRL);
			header.win_id = LX_PE_WIN_0;
			header.offset = PE_FWI_O20_REFRESH_TBL_OFST;
			header.length = PE_FWI_O20_REFRESH_TBL_SIZE;
			memcpy(&(table.tnr_ctrl), &(pInfo->tnr_ctrl[LX_PE_WIN_0]), sizeof(PE_FWI_O20_TNR_CTRL));
			memcpy(&(table.fw_ctrl), &(pInfo->fw_ctrl), sizeof(PE_FWI_O20_FW_CTRL));
			memcpy(&(table.src_info), &(pInfo->src_info), sizeof(PE_FWI_O20_SRC_INFO));
			memcpy(&(table.dnr_common), &(pInfo->dnr_common), sizeof(PE_FWI_O20_DNR_COMMON));
			memcpy(&(table.dnr_detail), &(pInfo->dnr_detail), sizeof(PE_FWI_O20_DNR_DETAIL));
			memcpy(&(table.shp_e_ctrl), &(pInfo->shp_e_ctrl), sizeof(PE_FWI_O20_EDGE_GAIN));
			memcpy(&(table.shp_t_ctrl), &(pInfo->shp_t_ctrl), sizeof(PE_FWI_O20_TEXTURE_GAIN));
			#if 0	//not_used
			memcpy(&(table.shp_h_ctrl), &(pInfo->shp_h_ctrl), sizeof(PE_FWI_O20_HOR_CTRL));
			memcpy(&(table.shp_m_ctrl), &(pInfo->shp_m_ctrl), sizeof(PE_FWI_O20_MISC_CTRL));
			memcpy(&(table.src_info), &(pInfo->src_info), sizeof(PE_FWI_O20_SRC_INFO));
			memcpy(&(table.cen_ctrl), &(pInfo->cen_ctrl), sizeof(PE_FWI_O20_CEN_CTRL));
			#endif
			PE_FWI_O20_DBG_PRINT("wid:%d, ofs:%d, len:%d, tbl_size:%d\n", \
				header.win_id, header.offset, header.length, tbl_size);
			ret = PE_FWI_O20_SetFwSettings(header,  pTable,  tbl_size);
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_SetFwSettings() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * set debug print enable
 *
 * @param   on_off [in] UINT32
 * @return  void
 * @see
 * @author
 */
void PE_FWI_O20_SetDbgPrint(UINT32 on_off)
{
	_g_fwi_o20_trace = on_off? 1:0;
	return;
}
/**
 * get debug print enable
 *
 * @param   void
 * @return  on, off
 * @see
 * @author
 */
UINT32 PE_FWI_O20_GetDbgPrint(void)
{
	return _g_fwi_o20_trace;
}
/**
 * open fwi ipc
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_IPC_Open(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	do{
		if (PE_KDRV_VER_O20)
		{
			PE_PRINT_NOTI("open ipc.\n");
			/* check pe_fwi_o20_mcu0_ipc is already opened */
			if(pe_fwi_o20_mcu0_ipc == NULL)
			{
				pe_fwi_o20_mcu0_ipc = ipc_hal_open("pe", MCU_ID_0);
				PE_FWI_O20_CHECK_CODE(!pe_fwi_o20_mcu0_ipc, ret = RET_ERROR;break, \
					"[%s,%d] pe_fwi_o20_mcu0_ipc open fail.\n", __F__, __L__);
			}
			/* check pe_fwi_o20_mcu1_ipc is already opened */
			if(pe_fwi_o20_mcu1_ipc == NULL)
			{
				pe_fwi_o20_mcu1_ipc = ipc_hal_open("pe", MCU_ID_1);
				PE_FWI_O20_CHECK_CODE(!pe_fwi_o20_mcu1_ipc, ret = RET_ERROR;break, \
					"[%s,%d] pe_fwi_o20_mcu1_ipc open fail.\n", __F__, __L__);
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_IPC_Close(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	do{
		if (PE_KDRV_VER_O20)
		{
			PE_PRINT_NOTI("close ipc.\n");
			if (pe_fwi_o20_mcu0_ipc)
			{
				ipc_hal_close(pe_fwi_o20_mcu0_ipc);
				pe_fwi_o20_mcu0_ipc = NULL;
			}
			if (pe_fwi_o20_mcu1_ipc)
			{
				ipc_hal_close(pe_fwi_o20_mcu1_ipc);
				pe_fwi_o20_mcu1_ipc = NULL;
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("init global values.\n");
			memset(&_g_pe_fwi_o20_info, 0x0, sizeof(PE_FWI_O20_SETTINGS_T));
			_g_pe_fwi_o20_info.src_info.dtv_mode = 0xff;	//default
			_g_pe_fwi_o20_info.src_info.hdd_mode = 0xff;	//default
			memset(&_g_pe_fwi_o20_ipc_20, 0x0, sizeof(UINT32));
			memset(&_g_pe_fwi_o20_crop_pos, 0x0, sizeof(UINT32));
			memset(&_g_pe_fwi_o20_ipc_22, 0x0, sizeof(UINT32));
			memset(&_g_pe_fwi_o20_ipc_23, 0x0, sizeof(UINT32));
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * check f/w status(periodic)
 *
 * @param   *pCfg [in] PE_TSK_O20_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_CheckFwStatus(PE_TSK_O20_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	PE_INF_O20_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_FWI_O20_SETTINGS_T *pInfo=&_g_pe_fwi_o20_info;
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_O20)
		{
			if (pInfo->fw_status.src_info != ctrl0_info->fw_src)
			{
				PE_FWI_O20_DBG_PRINT("fw_src changed : %d -> %d.\n", \
					pInfo->fw_status.src_info, ctrl0_info->fw_src);
				if ((pInfo->fw_status.src_info != PE_FWI_O20_FW_SRC_OFF) && \
					(ctrl0_info->fw_src == PE_FWI_O20_FW_SRC_OFF))
				{
					PE_FWI_O20_DBG_PRINT("fw_reset status on\n");
					pInfo->fw_status.reset = PE_FWI_O20_FW_RESET_STATUS_ON;
				}
				pInfo->fw_status.src_info = ctrl0_info->fw_src;
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_SetColorFilter(UINT32 cflter_state)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_COLORFILTER;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("set state : %d\n", cflter_state);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &cflter_state, sizeof(cflter_state));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_LoadDbData(UINT32 base_addr)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_DB_DATA;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("base_addr : 0x%08x\n", base_addr);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &base_addr, sizeof(base_addr));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_LoadDbDone(UINT32 *pData, UINT32 size)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_DB_DONE;
	do{
		CHECK_KNULL(pData);
		if (!size)	break;
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("LoadDbDone(0x%08x)(%d)(%d)(size:%d)\n",pData[0],pData[1],pData[2],size);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pData, size);
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * load hdr info
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_LoadHdrInfo(UINT32 *pInfo)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_HDR_INFO;
	do{
		CHECK_KNULL(pInfo);
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("hdr base : 0x%08x\n", pInfo[0]);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
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
int PE_FWI_O20_SetHdrInfo(UINT32 *pInfo)
{
	int ret = RET_OK;
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_HDR_INFO;
	do{
		CHECK_KNULL(pInfo);
		if (PE_KDRV_VER_O20)
		{
			if (pre_info != pInfo[0])
			{
				PE_FWI_O20_DBG_PRINT("hdr info : 0x%08x <- 0x%08x\n", pInfo[0], pre_info);
				ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
				pre_info = pInfo[0];
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	return ret;
}
/**
 * PE_FWI_O20_GetHdrMode
 *	- never use this on sync handler
 *
 * @param   *pInfo [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_GetHdrMode(UINT32 *pInfo)
{
	int ret = RET_OK;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_GET_HDR_MODE;
	do{
		CHECK_KNULL(pInfo);
		if (PE_KDRV_VER_O20)
		{
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
			ret = PE_FWI_O20_IPC_GetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_GetData() error.\n", __F__, __L__);
			PE_FWI_O20_DBG_PRINT("hdr mode : %d\n", pInfo[0]);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
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
int PE_FWI_O20_SetPattern(UINT32 *pInfo)
{
	int ret = RET_OK;
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_TPG;
	do {
		CHECK_KNULL(pInfo);
		if (pre_info != pInfo[0])
		{
			PE_PRINT_NOTI("set pat : 0x%x <- 0x%x\n", pInfo[0], pre_info);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, "PE_FWI_O20_IPC_SetData() error.\n");
			pre_info = pInfo[0];
		}
	} while (0);
	return ret;
}
/**
 * set fw cvi csc
 *	- never use this on sync handler
 *
 * @param   *pstParams [in] PE_FWI_O20_CSC_INPUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_SetCviCsc(PE_FWI_O20_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = DE_IPC_SET_CVI_CSC;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("set[%d] : idx:%d\n",pstParams->win_id,pstParams->enable);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0,ipc_cmd,(void *)pstParams,sizeof(PE_FWI_O20_CSC_INPUT_T));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_SetColorimetry(UINT32 *pInfo)
{
	int ret = RET_OK;
	static UINT32 pre_info = 0xff;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_COLORIMETRY;
	do{
		CHECK_KNULL(pInfo);
		if (PE_KDRV_VER_O20)
		{
			if (pre_info != pInfo[0])
			{
				PE_FWI_O20_DBG_PRINT("colorimetry : 0x%08x <- 0x%08x\n", pInfo[0], pre_info);
				ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pInfo, sizeof(UINT32));
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
				pre_info = pInfo[0];
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	return ret;
}
/**
 * set src info to f/w
 *	- never use this on sync handler
 *
 * @param   *pstParams [in] PE_FWI_O20_SRC_INFO
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_SetSrcInfo(PE_FWI_O20_SRC_INFO *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_O20_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_O20_SETTINGS_T *pInfo=&_g_pe_fwi_o20_info;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_CHECK_REFRESH_TBL();
			if ((pInfo->src_info.dtv_mode!=pstParams->dtv_mode) || \
				(pInfo->src_info.hdd_mode!=pstParams->hdd_mode))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_O20_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_O20_SRC_INFO);
				header.length = sizeof(PE_FWI_O20_SRC_INFO);
				table.src_info.dtv_mode = pstParams->dtv_mode;
				table.src_info.hdd_mode = pstParams->hdd_mode;
				PE_FWI_O20_DBG_PRINT("\n wid:%d, ofs:%d, len:%d, "\
					"tbl_size:%d, src_info.dtv:%d->%d, hdd:%d->%d\n", \
					header.win_id, header.offset, header.length, \
					tbl_size, pInfo->src_info.dtv_mode, table.src_info.dtv_mode, \
					pInfo->src_info.hdd_mode, table.src_info.hdd_mode);
				ret = PE_FWI_O20_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_SetFwSettings() error.\n", __F__, __L__);
				pInfo->src_info.dtv_mode=pstParams->dtv_mode;
				pInfo->src_info.hdd_mode=pstParams->hdd_mode;
			}
			else
			{
				PE_FWI_O20_DBG_PRINT("src_info.dtv:%d->%d, hdd:%d->%d, same..\n", \
					pInfo->src_info.dtv_mode, pstParams->dtv_mode, \
					pInfo->src_info.hdd_mode, pstParams->hdd_mode);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_SetPicMode(UINT32 mode)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	static UINT32 pre_mode = 0xffffffff;
	UINT32 cur_mode;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PIC_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			cur_mode = mode;
			if (pre_mode != cur_mode)
			{
				PE_FWI_O20_DBG_PRINT("set mode : 0x%08x <- 0x%08x (diff)\n", cur_mode, pre_mode);
				ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &mode, sizeof(mode));
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
				pre_mode = cur_mode;
			}
			else
			{
				PE_FWI_O20_DBG_PRINT("set mode : 0x%08x <- 0x%08x (same)\n", cur_mode, pre_mode);
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * get f/w settings
 *
 * @param   *pstParams [in] PE_FWI_O20_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_O20_GetCurFwiSettings(PE_FWI_O20_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	PE_FWI_O20_SETTINGS_T *pInfo=&_g_pe_fwi_o20_info;
	do{
		CHECK_KNULL(pstParams);
		memcpy(pstParams, pInfo, sizeof(PE_FWI_O20_SETTINGS_T));
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_FWI_O20_LoadLGSRDbData(UINT32 base_addr)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_LOAD_SRINF_DB_DATA;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("base_addr : 0x%08x\n", base_addr);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &base_addr, sizeof(base_addr));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O20_DoneDownloadDdr(UINT32 onoff)
{
#define PE_FWI_O20_FW_SIZE_WGT (0x7D000)
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 *pWgt_0=NULL;
	UINT32 *pWgt_1=NULL;
	UINT32 *pOut=NULL;
	UINT32 base_wgt0;
	UINT32 base_wgt1;
	UINT32 base_out;
	UINT32 *pWgt_0_dnn=NULL;
	UINT32 *pWgt_1_dnn=NULL;
	UINT32 *pOut_dnn=NULL;
	UINT32 base_wgt0_dnn;
	UINT32 base_wgt1_dnn;
	UINT32 base_out_dnn;
	PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T *pUserO20=NULL;
	PE_USER_LGSR_DDR_DB_PHYS_REG_F20_T *pUserF20=NULL;
	UINT32 base_user;
	LX_DE_IPC_SYSTEM_INFO_T *currMem = &g_pe_lgsr_mem_info;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			if (!currMem->fw_dnn.base)	{PE_PRINT_NOTI("fw_dnn.base0 : skip\n");break;}
			if (!currMem->fw_dnn.size)	{PE_PRINT_NOTI("fw_dnn.size0 : skip\n");break;}
			if (!currMem->fw_mcu3.base)	{PE_PRINT_NOTI("fw_mcu3.base0 : skip\n");break;}
			if (!currMem->fw_mcu3.size)	{PE_PRINT_NOTI("fw_mcu3.size0 : skip\n");break;}
			if (!currMem->fw_mcu4.base)	{PE_PRINT_NOTI("fw_mcu4.base0 : skip\n");break;}
			if (!currMem->fw_mcu4.size)	{PE_PRINT_NOTI("fw_mcu4.size0 : skip\n");break;}

			if(onoff)
			{
				/*copy defualt O20 DB from user ddr DB(fw.dnn)*/
				base_user = currMem->fw_dnn.base + 0x1700000;
				pUserO20    = (volatile UINT32 *)vmap_phys(base_user,sizeof(PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T)+PAGE_SIZE);
				ret = PE_LGSR_HW_O20_DownloadLGSRDb(pUserO20);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_LGSR_HW_O20_DownloadLGSRDb() error.\n", __F__, __L__);
				/*copy defualt F20 DB from user ddr DB(fw.dnn)*/
				base_user = currMem->fw_dnn.base + 0x1700000 + sizeof(PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T);
				pUserF20    = (volatile UINT32 *)vmap_phys(base_user,sizeof(PE_USER_LGSR_DDR_DB_PHYS_REG_F20_T)+PAGE_SIZE);
				ret = PE_LGSR_HW_F20_DownloadLGSRDb(pUserF20);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_LGSR_HW_F20_DownloadLGSRDb() error.\n", __F__, __L__);
				/*copy wgt0/1 from fw.mcu3/4 to pe DB*/
				base_wgt0 = currMem->fw_mcu3.base + 0x100000;
				pWgt_0 = (volatile UINT32 *)vmap_phys(base_wgt0, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);
				base_wgt1 = currMem->fw_mcu4.base + 0x100000;
				pWgt_1 = (volatile UINT32 *)vmap_phys(base_wgt1, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);

				base_wgt0_dnn = currMem->fw_dnn.base + 0x1600000;
				pWgt_0_dnn = (volatile UINT32 *)vmap_phys(base_wgt0_dnn, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);
				base_wgt1_dnn = currMem->fw_dnn.base + 0x1600000 + PE_FWI_O20_FW_SIZE_WGT;
				pWgt_1_dnn = (volatile UINT32 *)vmap_phys(base_wgt1_dnn, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);

				base_out = currMem->fw_mcu3.base + 0x33100;
				pOut = (volatile UINT32 *)vmap_phys(base_out, 0x400+PAGE_SIZE);

				base_out_dnn = currMem->fw_dnn.base + 0x16FFC00;
				pOut_dnn = (volatile UINT32 *)vmap_phys(base_out_dnn, 0x400+PAGE_SIZE);

				memcpy((UINT32 *)pWgt_0, pWgt_0_dnn, PE_FWI_O20_FW_SIZE_WGT);
				memcpy((UINT32 *)pWgt_1, pWgt_1_dnn, PE_FWI_O20_FW_SIZE_WGT);
				memcpy((UINT32 *)pOut, pOut_dnn, 0x400);
				wmb();
				PE_PRINT_NOTI("copy done!!!!\n");
			}
			PE_PRINT_NOTI("done_donwload : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.sr_inference_mode = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_DoneDownloadDdr() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (pWgt_0) vunmap_phys((void *)pWgt_0);
	if (pWgt_1) vunmap_phys((void *)pWgt_1);
	if (pWgt_0_dnn) vunmap_phys((void *)pWgt_0_dnn);
	if (pWgt_1_dnn) vunmap_phys((void *)pWgt_1_dnn);
	if (pOut) vunmap_phys((void *)pOut);
	if (pOut_dnn) vunmap_phys((void *)pOut_dnn);
	if (pUserO20)  vunmap_phys((void *)pUserO20);
	if (pUserF20)  vunmap_phys((void *)pUserF20);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
int PE_LGSR_HW_O20_CompareDdr(UINT32 onoff)
{
#define PE_FWI_O20_FW_SIZE_WGT (0x7D000)
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 *pWgt_0=NULL;
	UINT32 *pWgt_1=NULL;
	UINT32 *pOut=NULL;
	UINT32 base_wgt0;
	UINT32 base_wgt1;
	UINT32 base_out;
	UINT32 *pWgt_0_dnn=NULL;
	UINT32 *pWgt_1_dnn=NULL;
	UINT32 *pOut_dnn=NULL;
	UINT32 base_wgt0_dnn;
	UINT32 base_wgt1_dnn;
	UINT32 base_out_dnn;
	PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T *pUserO20=NULL;
	PE_USER_LGSR_DDR_DB_PHYS_REG_F20_T *pUserF20=NULL;
	UINT32 base_user;
	LX_DE_IPC_SYSTEM_INFO_T *currMem = &g_pe_lgsr_mem_info;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	int i;
	do{
		if (PE_KDRV_VER_O20)
		{
			if (!currMem->fw_dnn.base)	{PE_PRINT_NOTI("fw_dnn.base0 : skip\n");break;}
			if (!currMem->fw_dnn.size)	{PE_PRINT_NOTI("fw_dnn.size0 : skip\n");break;}
			if (!currMem->fw_mcu3.base)	{PE_PRINT_NOTI("fw_mcu3.base0 : skip\n");break;}
			if (!currMem->fw_mcu3.size)	{PE_PRINT_NOTI("fw_mcu3.size0 : skip\n");break;}
			if (!currMem->fw_mcu4.base)	{PE_PRINT_NOTI("fw_mcu4.base0 : skip\n");break;}
			if (!currMem->fw_mcu4.size)	{PE_PRINT_NOTI("fw_mcu4.size0 : skip\n");break;}

			/*copy defualt O20 DB from user ddr DB(fw.dnn)*/
			base_user = currMem->fw_dnn.base + 0x1700000;
			pUserO20    = (volatile UINT32 *)vmap_phys(base_user,sizeof(PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T)+PAGE_SIZE);
			ret = PE_LGSR_HW_O20_CompareLGSRDb(pUserO20, base_user);
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_DownloadLGSRDb() error.\n", __F__, __L__);
			/*copy defualt F20 DB from user ddr DB(fw.dnn)*/
			//base_user = currMem->fw_dnn.base + 0x1700000 + sizeof(PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T);
			//pUserF20    = (volatile UINT32 *)vmap_phys(base_user,sizeof(PE_USER_LGSR_DDR_DB_PHYS_REG_F20_T)+PAGE_SIZE);
			//ret = PE_LGSR_HW_F20_DownloadLGSRDb(pUserF20);
			//PE_FWI_O20_CHECK_CODE(ret, break, \
			//	"[%s,%d] PE_LGSR_HW_F20_DownloadLGSRDb() error.\n", __F__, __L__);
			/*copy wgt0/1 from fw.mcu3/4 to pe DB*/
			#if 1
			base_wgt0 = currMem->fw_mcu3.base + 0x100000;
			pWgt_0 = (volatile UINT32 *)vmap_phys(base_wgt0, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);
			base_wgt1 = currMem->fw_mcu4.base + 0x100000;
			pWgt_1 = (volatile UINT32 *)vmap_phys(base_wgt1, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);

			base_wgt0_dnn = currMem->fw_dnn.base + 0x1600000;
			pWgt_0_dnn = (volatile UINT32 *)vmap_phys(base_wgt0_dnn, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);
			base_wgt1_dnn = currMem->fw_dnn.base + 0x1600000 + PE_FWI_O20_FW_SIZE_WGT;
			pWgt_1_dnn = (volatile UINT32 *)vmap_phys(base_wgt1_dnn, PE_FWI_O20_FW_SIZE_WGT+PAGE_SIZE);

			base_out = currMem->fw_mcu3.base + 0x33100;
			pOut = (volatile UINT32 *)vmap_phys(base_out, 0x400+PAGE_SIZE);

			base_out_dnn = currMem->fw_dnn.base + 0x16FFC00;
			pOut_dnn = (volatile UINT32 *)vmap_phys(base_out_dnn, 0x400+PAGE_SIZE);
			wmb();

			#endif

			//memcpy((UINT32 *)pWgt_0, pWgt_0_dnn, PE_FWI_O20_FW_SIZE_WGT);
			//memcpy((UINT32 *)pWgt_1, pWgt_1_dnn, PE_FWI_O20_FW_SIZE_WGT);
			for(i=0; i<PE_FWI_O20_FW_SIZE_WGT/4; i++)
			{
				if(pWgt_0[i]!=pWgt_0_dnn[i])
				{
					printk("pWgt_0 uerDB [%d] addr: 0x%08x, data:0x%08x  ddrDB addr: 0x%08x, data:0x%08x\n",\
						i, base_wgt0_dnn+i*4, pWgt_0_dnn[i],\
						base_wgt0+i*4, pWgt_0[i]);
				}
				if(pWgt_1[i]!=pWgt_1_dnn[i])
				{
					printk("pWgt_1 uerDB [%d] addr: 0x%08x, data:0x%08x  ddrDB addr: 0x%08x, data:0x%08x\n",\
						i,base_wgt1_dnn+i*4, pWgt_1_dnn[i],\
						base_wgt1+i*4, pWgt_1[i]);
				}
			}
			//memcpy((UINT32 *)pOut, pOut_dnn, 0x400);
			for(i=0; i<0x100; i++)
			{
				if(pOut[i]!=pOut_dnn[i])
				{
					printk("pOut uerDB [%d] addr: 0x%08x, data:0x%08x  ddrDB addr: 0x%08x, data:0x%08x\n",\
						i,base_out_dnn+i*4, pOut_dnn[i],\
						base_out+i*4, pOut[i]);
				}
			}
				
			
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (pWgt_0) vunmap_phys((void *)pWgt_0);
	if (pWgt_1) vunmap_phys((void *)pWgt_1);
	if (pWgt_0_dnn) vunmap_phys((void *)pWgt_0_dnn);
	if (pWgt_1_dnn) vunmap_phys((void *)pWgt_1_dnn);
	if (pOut) vunmap_phys((void *)pOut);
	if (pOut_dnn) vunmap_phys((void *)pOut_dnn);
	if (pUserO20)  vunmap_phys((void *)pUserO20);
	//if (pUserF20)  vunmap_phys((void *)pUserF20);
	printk("compare completed!!\n");
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

static int PE_LGSR_HW_O20_CompareLGSRDb(UINT32 *pUser, UINT32 base_user)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i;
	PE_CFG_CTRL_T stParams;
	PE_LGSR_DDR_DB_SHDW_REG_O20_T *p_shdw_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O20_T *p_phys_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O20_T *p_phys_db_chk = NULL;
	p_shdw_db = gPE_LGSR_DDR_DB_O20.shdw.data;
	p_phys_db = gPE_LGSR_DDR_DB_O20.phys.data;
	do{
		CHECK_KNULL(pUser);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_O20)
		{
			//p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_LGSR_DDR_O20_DB_VER;
			//p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_LGSR_DDR_O20_BASE_ADDR;
			//p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_LGSR_DDR_O20_SEC_NUM;
			/* *********************************************************************/
			/* Causion : Should be arranged in enum order **************************/
			/* *********************************************************************/
			rmb();
			for(i =0; i< PE_LGSR_DDR_O20_SEC_NUM/2 ; i++)
			{
				ret = PE_LGSR_HW_O20_CompareLGSROneSet(i,pUser, base_user);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_LGSR_HW_O20_CompareLGSROneSet() error.\n",__F__,__L__);
			}
			/* inform load db data */
			//ret = PE_FWI_O20_LoadLGSRDbData(p_shdw_db->top_h.db_base);
			//PE_FWI_O20_CHECK_CODE(ret, break, \
			//	"[%s,%d] PE_FWI_O20_LoadLGSRDbData() error.\n",__F__,__L__);
			/* *********************************************************************/
			rmb();
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_LGSR_HW_O20_CompareLGSROneSet(UINT32 setNum, UINT32* pUser, UINT32 base_user)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size, sec_typ;
	PE_LGSR_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_LGSR_DDR_DB_O20.shdw.data;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_LGSR_DDR_DB_O20.phys.data;
	volatile UINT32 *p_apb_data = p_phys_db->inf_set[setNum].inf_apb;
	volatile UINT32 *p_weight_data = p_phys_db->inf_set[setNum].inf_weight;
	PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T *p_user_db = (PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T*)pUser;
	UINT32 i, user_addr, ddr_addr;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_apb_data);
		CHECK_KNULL(p_weight_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = setNum;//PE_LGSR_DDR_O20_SEC_TYPE
			
			/* header */
			//p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			//p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			//p_phys_db->inf_set[sec_typ].header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			//p_phys_db->inf_set[sec_typ].header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			/* data */
			size = ((PE_LGSR_DDR_O20_INF_WEIGHT_SIZE+PE_LGSR_DDR_O20_INF_APB_SIZE+PE_LGSR_DDR_O20_INF_DUMMY_SIZE) * sizeof(UINT32));
			#if 0
			if(sec_typ == 0)//PE_LGSR_DDR_O20_SEC_INF_SET_00
			{
				p_shdw_db->top_h.sec_base[sec_typ] = \
					p_shdw_db->top_h.db_base+sizeof(PE_LGSR_DDR_O20_TOP_HEADER_T);
			}
			else
			{
				p_shdw_db->top_h.sec_base[sec_typ] = \
					p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			}
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_LGSR_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_LGSR_DDR_O20_HEADER_T);

			
			p_shdw_db->sec_d[sec_typ].header.base_apb  = p_shdw_db->sec_d[sec_typ].data_base;
			p_shdw_db->sec_d[sec_typ].header.base_weight = \
				p_shdw_db->sec_d[sec_typ].header.base_apb + \
				((PE_LGSR_DDR_O20_INF_APB_SIZE+PE_LGSR_DDR_O20_INF_DUMMY_SIZE) * sizeof(UINT32));
			p_phys_db->inf_set[sec_typ].header.base_apb= p_shdw_db->sec_d[sec_typ].header.base_apb;
			p_phys_db->inf_set[sec_typ].header.base_weight= p_shdw_db->sec_d[sec_typ].header.base_weight;
			
			#endif
			/* compare ddr */
			//memcpy(p_apb_data,p_user_db->inf_set[setNum].inf_apb,\
			//(PE_LGSR_DDR_O20_INF_APB_SIZE * sizeof(UINT32)));
			user_addr = base_user + (PE_LGSR_DDR_O20_INF_WEIGHT_SIZE+PE_LGSR_DDR_O20_INF_APB_SIZE)*4*sec_typ;
			ddr_addr = p_phys_db->inf_set[sec_typ].header.base_apb;
			for(i=0; i<PE_LGSR_DDR_O20_INF_APB_SIZE; i++)
			{
				if(p_apb_data[i]!=p_user_db->inf_set[sec_typ].inf_apb[i])
				{
					printk("apb uerDB sec[%d][i] addr: 0x%08x, data:0x%08x  ddrDB addr: 0x%08x, data:0x%08x\n",\
						sec_typ,i,\
						user_addr+i*4, p_user_db->inf_set[sec_typ].inf_apb[i],\
						ddr_addr+i*4, p_apb_data[i]);
				}
			}
			//mcpy(p_weight_data,p_user_db->inf_set[setNum].inf_weight,\
			//E_LGSR_DDR_O20_INF_WEIGHT_SIZE * sizeof(UINT32)));
			/* noti */
			//user_addr = base_user + (PE_LGSR_DDR_O20_INF_WEIGHT_SIZE+PE_LGSR_DDR_O20_INF_APB_SIZE)*4*sec_typ;
			user_addr = user_addr +PE_LGSR_DDR_O20_INF_APB_SIZE*4;
			ddr_addr = p_phys_db->inf_set[sec_typ].header.base_weight;
			for(i=0; i<PE_LGSR_DDR_O20_INF_WEIGHT_SIZE; i++)
			{
				if(p_weight_data[i]!=p_user_db->inf_set[sec_typ].inf_weight[i])
				{
					printk("weight userDB sec[%d][i] addr: 0x%08x, data:0x%08x  ddrDB addr: 0x%08x, data:0x%08x\n",\
						sec_typ,i,\
						user_addr+i*4, p_user_db->inf_set[sec_typ].inf_weight[i],\
						ddr_addr+i*4, p_weight_data[i]);
				}
			}
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_LGSR_HW_O20_DownloadLGSRDb(UINT32 *pUser)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i;
	PE_CFG_CTRL_T stParams;
	PE_LGSR_DDR_DB_SHDW_REG_O20_T *p_shdw_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O20_T *p_phys_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O20_T *p_phys_db_chk = NULL;
	p_shdw_db = gPE_LGSR_DDR_DB_O20.shdw.data;
	p_phys_db = gPE_LGSR_DDR_DB_O20.phys.data;
	do{
		CHECK_KNULL(pUser);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_O20)
		{
			p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_LGSR_DDR_O20_DB_VER;
			p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_LGSR_DDR_O20_BASE_ADDR;
			p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_LGSR_DDR_O20_SEC_NUM;
			/* *********************************************************************/
			/* Causion : Should be arranged in enum order **************************/
			/* *********************************************************************/
			for(i =0; i< PE_LGSR_DDR_O20_SEC_NUM ; i++)
			{
				ret = PE_LGSR_HW_O20_DownloadLGSROneSet(i,pUser);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_CMN_HW_O20_DownloadLGSROneSet() error.\n",__F__,__L__);
			}
			wmb();
			/* inform load db data */
			ret = PE_FWI_O20_LoadLGSRDbData(p_shdw_db->top_h.db_base);
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_LoadLGSRDbData() error.\n",__F__,__L__);
			/* *********************************************************************/
			PE_PRINT_NOTI("DL db done.(base:0x%08x)\n", PE_LGSR_DDR_O20_BASE_ADDR);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_LGSR_HW_O20_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size, sec_typ;
	PE_LGSR_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_LGSR_DDR_DB_O20.shdw.data;
	volatile PE_LGSR_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_LGSR_DDR_DB_O20.phys.data;
	volatile UINT32 *p_apb_data = p_phys_db->inf_set[setNum].inf_apb;
	volatile UINT32 *p_weight_data = p_phys_db->inf_set[setNum].inf_weight;
	PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T *p_user_db = (PE_USER_LGSR_DDR_DB_PHYS_REG_O20_T*)pUser;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_apb_data);
		CHECK_KNULL(p_weight_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = setNum;//PE_LGSR_DDR_O20_SEC_TYPE
			
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_phys_db->inf_set[sec_typ].header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->inf_set[sec_typ].header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			/* data */
			size = ((PE_LGSR_DDR_O20_INF_WEIGHT_SIZE+PE_LGSR_DDR_O20_INF_APB_SIZE+PE_LGSR_DDR_O20_INF_DUMMY_SIZE) * sizeof(UINT32));
			if(sec_typ == 0)//PE_LGSR_DDR_O20_SEC_INF_SET_00
			{
				p_shdw_db->top_h.sec_base[sec_typ] = \
					p_shdw_db->top_h.db_base+sizeof(PE_LGSR_DDR_O20_TOP_HEADER_T);
			}
			else
			{
				p_shdw_db->top_h.sec_base[sec_typ] = \
					p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			}
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_LGSR_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_LGSR_DDR_O20_HEADER_T);

			
			p_shdw_db->sec_d[sec_typ].header.base_apb  = p_shdw_db->sec_d[sec_typ].data_base;
			p_shdw_db->sec_d[sec_typ].header.base_weight = \
				p_shdw_db->sec_d[sec_typ].header.base_apb + \
				((PE_LGSR_DDR_O20_INF_APB_SIZE+PE_LGSR_DDR_O20_INF_DUMMY_SIZE) * sizeof(UINT32));
			p_phys_db->inf_set[sec_typ].header.base_apb= p_shdw_db->sec_d[sec_typ].header.base_apb;
			p_phys_db->inf_set[sec_typ].header.base_weight= p_shdw_db->sec_d[sec_typ].header.base_weight;
			/* wr ddr */
			memcpy(p_apb_data,p_user_db->inf_set[setNum].inf_apb,\
			(PE_LGSR_DDR_O20_INF_APB_SIZE * sizeof(UINT32)));
			memcpy(p_weight_data,p_user_db->inf_set[setNum].inf_weight,\
			(PE_LGSR_DDR_O20_INF_WEIGHT_SIZE * sizeof(UINT32)));
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)(apb:0x%08x)(weight:0x%08x)\n", \
				PE_LGSR_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],\
				p_shdw_db->sec_d[sec_typ].header.base_apb, p_shdw_db->sec_d[sec_typ].header.base_weight);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_LGSR_HW_F20_DownloadLGSRDb(UINT32 *pUser)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i;
	PE_CFG_CTRL_T stParams;
	PE_LGSR_DDR_DB_SHDW_REG_F20_T *p_shdw_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_F20_T *p_phys_db = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_F20_T *p_phys_db_chk = NULL;
	p_shdw_db = gPE_LGSR_DDR_DB_F20.shdw.data;
	p_phys_db = gPE_LGSR_DDR_DB_F20.phys.data;
	do{
		CHECK_KNULL(pUser);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_O20)
		{
			p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_LGSR_DDR_F20_DB_VER;
			p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_LGSR_DDR_F20_BASE_ADDR;
			p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_LGSR_DDR_F20_SEC_NUM;
			/* *********************************************************************/
			/* Causion : Should be arranged in enum order **************************/
			/* *********************************************************************/
			for(i =0; i< PE_LGSR_DDR_F20_SEC_NUM ; i++)
			{
				ret = PE_LGSR_HW_F20_DownloadLGSROneSet(i,pUser);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_CMN_HW_O20_DownloadLGSROneSet() error.\n",__F__,__L__);
			}
			wmb();
			/* inform load db done */
			do {
				UINT32 load_data[3];
				UINT32 sec_typ;
				UINT32 ddr_total=0;
				UINT32 load_size=0;
				#if 0
				for (sec_typ=0; sec_typ<PE_LGSR_DDR_F20_SEC_NUM; sec_typ++)
				{
					ddr_total += p_shdw_db->top_h.sec_size[sec_typ];
					//PE_PRINT_NOTI("%s:size:%d, total: %d\n", PE_LGSR_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ), p_phys_db->top_h.sec_size[sec_typ],ddr_total2);
				}
				#endif
				load_data[0] = PE_LGSR_DDR_F20_BASE_ADDR;
				load_data[1] = sizeof(PE_LGSR_DDR_DB_PHYS_REG_F20_T);
				load_data[2] = 1;
				load_size = (UINT32)(sizeof(UINT32)*3);
				ret = PE_FWI_O20_LoadDbDone(load_data, load_size);
				PE_FWI_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_LoadDbDone() error.\n",__F__,__L__);
				PE_PRINT_NOTI("LoadDbDone(base:0x%08x)(size:%d)(data:%d)\n",load_data[0],load_data[1],load_data[2]);
			} while(0);
			/* *********************************************************************/
			PE_PRINT_NOTI("DL db done.(base:0x%08x)\n", PE_LGSR_DDR_F20_BASE_ADDR);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_LGSR_HW_F20_DownloadLGSROneSet(UINT32 setNum, UINT32* pUser)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size, sec_typ;
	PE_LGSR_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_LGSR_DDR_DB_F20.shdw.data;
	volatile PE_LGSR_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_LGSR_DDR_DB_F20.phys.data;
	volatile UINT32 *p_apb_data = p_phys_db->inf_set[setNum].inf_apb;
	volatile UINT32 *p_weight_data = p_phys_db->inf_set[setNum].inf_weight;
	PE_USER_LGSR_DDR_DB_PHYS_REG_F20_T *p_user_db = (PE_USER_LGSR_DDR_DB_PHYS_REG_F20_T*)pUser;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_apb_data);
		CHECK_KNULL(p_weight_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = setNum;//PE_LGSR_DDR_F20_SEC_TYPE
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_phys_db->inf_set[sec_typ].header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->inf_set[sec_typ].header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			/* data */
			size = ((PE_LGSR_DDR_F20_INF_WEIGHT_SIZE+PE_LGSR_DDR_F20_INF_APB_SIZE+PE_LGSR_DDR_F20_INF_DUMMY_SIZE) * sizeof(UINT32));
			if(sec_typ == 0)//PE_LGSR_DDR_F20_SEC_INF_SET_00
			{
				p_shdw_db->top_h.sec_base[sec_typ] = \
					p_shdw_db->top_h.db_base+sizeof(PE_LGSR_DDR_F20_TOP_HEADER_T);
			}
			else
			{
				p_shdw_db->top_h.sec_base[sec_typ] = \
					p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			}
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_LGSR_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_LGSR_DDR_F20_HEADER_T);
			p_shdw_db->sec_d[sec_typ].header.base_apb  = p_shdw_db->sec_d[sec_typ].data_base;
			p_shdw_db->sec_d[sec_typ].header.base_weight = \
				p_shdw_db->sec_d[sec_typ].header.base_apb + \
				((PE_LGSR_DDR_F20_INF_APB_SIZE+PE_LGSR_DDR_F20_INF_DUMMY_SIZE) * sizeof(UINT32));
			p_phys_db->inf_set[sec_typ].header.base_apb= p_shdw_db->sec_d[sec_typ].header.base_apb;
			p_phys_db->inf_set[sec_typ].header.base_weight= p_shdw_db->sec_d[sec_typ].header.base_weight;
			/* wr ddr */
			memcpy(p_apb_data,p_user_db->inf_set[setNum].inf_apb,\
			(PE_LGSR_DDR_F20_INF_APB_SIZE * sizeof(UINT32)));
			memcpy(p_weight_data,p_user_db->inf_set[setNum].inf_weight,\
			(PE_LGSR_DDR_F20_INF_WEIGHT_SIZE * sizeof(UINT32)));
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)(apb:0x%08x)(weight:0x%08x)\n", \
				PE_LGSR_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],\
				p_shdw_db->sec_d[sec_typ].header.base_apb, p_shdw_db->sec_d[sec_typ].header.base_weight);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O20_SetSrSQM(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("set sqm : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.sr_sqm_enalbe = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_SetSrSQM() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

int PE_LGSR_HW_O20_HaltTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("halt tra : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.tra_halt = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_HaltTRA() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

int PE_LGSR_HW_O20_RunTRA(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 reg_ipc22 = 0x1;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRTRAVLD_RUN;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("run_tra : %d\n",onoff);
			_g_pe_fwi_o20_ipc_22.tra_or_valid_run = GET_BITS(reg_ipc22,0,2);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_22 : 0x%08x\n", _g_pe_fwi_o20_ipc_22);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_22, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_RunTRA() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
int PE_LGSR_HW_O20_SetCropSize(UINT32 *pPosition)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	PE_INF_O20_SETTINGS_T inf_set;
	static UINT32 pos_count=1;
	//DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRSQM_POS;
	do{
		CHECK_KNULL(pPosition);
		ret = PE_INF_O20_GetCurInfSettings(&inf_set);
		PE_FWI_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_O20_GetCurInfSettings() error.\n", __F__, __L__);
		if(inf_set.disp_info[0].act_fmt) // if seamless
			return 0;
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("crop_position x, y : 0x%08x, 0x%08x\n",pPosition[0], pPosition[1]);
			_g_pe_fwi_o20_crop_pos.sr_sqm_position_x =  GET_BITS(pPosition[0],0,12);
			_g_pe_fwi_o20_crop_pos.sr_sqm_position_y =  GET_BITS(pPosition[1],0,12);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_crop_pos : 0x%08x\n", _g_pe_fwi_o20_crop_pos);
			PE_MCU_O20_QWr03(ad_gen_14, sr_sqm_position_y, GET_BITS(pPosition[1],0,12),\
										sr_sqm_position_x, GET_BITS(pPosition[0],0,12),\
										pos_count,         GET_BITS(pos_count++,0,2));
			if(pos_count ==4)
				pos_count =0;
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

int PE_LGSR_HW_O20_UserReady(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("user data ready : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.user_data_ready= GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_UserReady() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

int PE_LGSR_HW_O20_ValidRun(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 reg_ipc22 = 0x2;
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_SRTRAVLD_RUN;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("vaild Run : %d\n",onoff);
			_g_pe_fwi_o20_ipc_22.tra_or_valid_run = GET_BITS(reg_ipc22,0,2);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_22 : 0x%08x\n", _g_pe_fwi_o20_ipc_22);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_22, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_ValidRun() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

int PE_LGSR_HW_O20_DemoMode(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PQ_STOREMODE;
	UINT32 srOnOff = 0;
	UINT32 srLeftRight = 0;
	do{
		if (PE_KDRV_VER_O20)
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
				PE_FWI_O20_DBG_PRINT("wrong UI value %d:\n", onoff);
				return RET_ERROR;
			}
			PE_FWI_O20_DBG_PRINT("sr-sqm demo mode on/off : %d\n",onoff);
			PE_FWI_O20_DBG_PRINT("sr-sqm demo mode srOnOff : %d\n",srOnOff);
			PE_FWI_O20_DBG_PRINT("sr-sqm demo mode srLeftRight : %d\n",srLeftRight);
			_g_pe_fwi_o20_ipc_23.sr_demo_onoff = GET_BITS(srOnOff,0,1);
			_g_pe_fwi_o20_ipc_23.left_or_right = GET_BITS(srLeftRight,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_23 : 0x%08x\n", _g_pe_fwi_o20_ipc_23);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_23, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_DemoMode() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

int PE_FWI_HW_O20_ObcDemoMode(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_PQ_STOREMODE;
	UINT32 srOnOff = 0;
	UINT32 srLeftRight = 0;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("obc demo mode on/off : %d\n",onoff);
			_g_pe_fwi_o20_ipc_23.obc_demo_onoff = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_23 : 0x%08x\n", _g_pe_fwi_o20_ipc_23);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_23, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_OBC_HW_O20_DemoMode() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_LGSR_HW_O20_AccelModeSrSqm(UINT32 onoff)
{
	int ret = RET_OK;
#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("set accel sr-sqm : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.accel_srsqm = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_AccelModeSrSqm() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
#endif /*PE_HW_O20_BRINGUP*/
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
int PE_LGSR_HW_O20_AccelModeTRA(UINT32 onoff)
{
	int ret = RET_OK;
#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("set accel tra : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.accel_tra= GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_AccelModeTRA() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
#endif /*PE_HW_O20_BRINGUP*/
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
int PE_LGSR_HW_O20_PrintLGSRStatus(void)
{
	int ret = RET_OK;
#ifdef PE_HW_O20_BRINGUP
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_PRINT_NOTI(" PE_O20_REG_FW_IPC_20_T : 0x%08x \n", _g_pe_fwi_o20_ipc_20);
			PE_PRINT_NOTI("	sr_inference_mode: 0x%x \n", _g_pe_fwi_o20_ipc_20.sr_inference_mode);
			PE_PRINT_NOTI("	sr_sqm_enalbe    : 0x%x \n", _g_pe_fwi_o20_ipc_20.sr_sqm_enalbe);
			PE_PRINT_NOTI("	user_data_ready  : 0x%x \n", _g_pe_fwi_o20_ipc_20.user_data_ready);
			PE_PRINT_NOTI("	tra_halt         : 0x%x \n", _g_pe_fwi_o20_ipc_20.tra_halt);
			PE_PRINT_NOTI("	srsqm_ui         : 0x%x \n", _g_pe_fwi_o20_ipc_20.srsqm_ui);
			PE_PRINT_NOTI("	accel_srsqm      : 0x%x \n", _g_pe_fwi_o20_ipc_20.accel_srsqm);
			PE_PRINT_NOTI("	accel_tra        : 0x%x \n", _g_pe_fwi_o20_ipc_20.accel_tra);
			PE_PRINT_NOTI("********************\n");
			PE_PRINT_NOTI(" PE_O20_REG_FW_IPC_21_T : 0x%08x \n", _g_pe_fwi_o20_crop_pos);
			PE_PRINT_NOTI("	sr_sqm_position_y: 0x%x \n", _g_pe_fwi_o20_crop_pos.sr_sqm_position_y);
			PE_PRINT_NOTI("	sr_sqm_position_x: 0x%x \n", _g_pe_fwi_o20_crop_pos.sr_sqm_position_x);
			PE_PRINT_NOTI("********************\n");
			PE_PRINT_NOTI(" PE_O20_REG_FW_IPC_22_T : 0x%08x \n", _g_pe_fwi_o20_ipc_22);
			PE_PRINT_NOTI("	tra_or_valid_run : 0x%x \n", _g_pe_fwi_o20_ipc_22.tra_or_valid_run);
			PE_PRINT_NOTI("********************\n");
			PE_PRINT_NOTI(" PE_O20_REG_FW_IPC_23_T : 0x%08x \n", _g_pe_fwi_o20_ipc_23);
			PE_PRINT_NOTI("	sr_demo_onoff    : 0x%x \n", _g_pe_fwi_o20_ipc_23.sr_demo_onoff);
			PE_PRINT_NOTI("	obc_demo_onoff   : 0x%x \n", _g_pe_fwi_o20_ipc_23.obc_demo_onoff);
			PE_PRINT_NOTI("********************\n");
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
#endif /*PE_HW_O20_BRINGUP*/
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
int PE_LGSR_HW_O20_UIOnoff(UINT32 onoff)
{
	int ret = RET_OK;
#ifdef PE_HW_O20_BRINGUP

	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("ui on/ff : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.srsqm_ui = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_UIOnoff() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

int PE_LGSR_HW_O20_GetLneStatus(UINT32 *status)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_REG_PHYS_RdFL(gPE_MCU_O20,data,reg_mcu_ad_lne_ctrl);
			*status = PE_REG_SHDW_Rd32(gPE_MCU_O20,data,reg_mcu_ad_lne_ctrl);
			PE_FWI_O20_DBG_PRINT("reg_mcu_ad_lne_ctrl : 0x%08x\n", *status);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
int PE_LGSR_HW_O20_GetTraStatus(UINT32 *status)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_REG_PHYS_RdFL(gPE_MCU_O20,data,reg_mcu_ad_tra_ctrl);
			*status = PE_REG_SHDW_Rd32(gPE_MCU_O20,data,reg_mcu_ad_tra_ctrl);
			PE_FWI_O20_DBG_PRINT("reg_mcu_ad_tra_ctrl : 0x%08x\n", *status);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
int PE_LGSR_HW_O20_SetDnnDownLoadDone(UINT32 onoff)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DNNSR_MODE;
	do{
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("done_donwload : %d\n",onoff);
			_g_pe_fwi_o20_ipc_20.sr_inference_mode = GET_BITS(onoff,0,1);
			PE_FWI_O20_DBG_PRINT("_g_pe_fwi_o20_ipc_20 : 0x%08x\n", _g_pe_fwi_o20_ipc_20);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, &_g_pe_fwi_o20_ipc_20, sizeof(UINT32));
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_LGSR_HW_O20_UIOnoff() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
//############# for F20 ##############//
/**
 * load db done
 *	- never use this on sync handler
 *
 * @param   base,size [in] *UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_F20_SetDrcCurvDb(UINT32 *pData)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	DE_IPC_CMD_T ipc_cmd = PQL_IPC_SET_DRC_CRV;
	do{
		CHECK_KNULL(pData);
		if (PE_KDRV_VER_O20)
		{
			PE_FWI_O20_DBG_PRINT("SET_DRC_CRV(base:0x%08x)(size:%d)\n",pData[0],pData[1]);
			ret = PE_FWI_O20_IPC_SetData(MCU_ID_0, ipc_cmd, pData, sizeof(UINT32)*2);
			PE_FWI_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_O20_IPC_SetData() error.\n", __F__, __L__);
		}
		else
		{
			PE_FWI_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

