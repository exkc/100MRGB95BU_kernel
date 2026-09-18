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
 *	hardware abstraction layer for ipc.
 *
 *	author		
 *	version		1.0
 *	date		
 *	note		
 *
 *	@addtogroup 
 *	@{
 */

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/
#define ENABLE_FW_IPC_LOG

/*------------------------------------------------------------------------------
	File Inclusions
------------------------------------------------------------------------------*/
#include <linux/slab.h>
#include "os_util.h"
#include "base_device.h"

#include "de_ver_def.h"
#include "de_def.h"
#include "ipc_hal.h"
#include "ipc_phys_hal.h"

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/
#define CHECK_REG_NULL(fp) {if(fp == NULL || g_chip_id < 0)\
							{DE_ERROR("%s is null\n",#fp); \
							return RET_ERROR;}}
#define GET_ID() g_chip_id

#define IPC_TRACE(format, args...)\
	if(g_ipc_trace==1) DE_PRINT(format, ##args);\
	else if(g_ipc_trace==2) printk(format, ##args);

#define IPC_DUMP(format, args...)\
	if(g_ipc_trace==2) printk(format, ##args)

#define MCU_ID(a) ((a >> 16) & 0xF)
#define STR_IPC_DST(d, s)\
	switch(d)\
	{\
		case IPC_DST_DE:\
			s = "DE";break;\
		case IPC_DST_FMT3D:\
			s = "FMT3D";break;\
		case IPC_DST_DENC:\
			s = "DENC";break;\
		case IPC_DST_PQL:\
			s = "PQL";break;\
		case IPC_DST_TOP:\
			s = "TOP";break;\
		case IPC_DST_H3D:\
			s = "H3D";break;\
		case IPC_DST_FRC:\
			s = "FRC";break;\
		case IPC_DST_SRE:\
			s = "SRE";break;\
		case IPC_DST_DPPA:\
			s = "DPPA";break;\
		case IPC_DST_DPPB:\
			s = "DPPB";break;\
		case IPC_DST_PWM:\
			s = "PWM";break;\
		case IPC_DST_DBG:\
			s = "DBG";break;\
		default:\
			s = "NULL";break;\
	}

#ifdef USE_KDRV_CODES_FOR_L18
#define CP_MSG2PQE(a)	memcpy( &param->a, msg, cnt)
#define CP_MSG4PQE(a)	memcpy( msg, &param->a, cnt)
#endif

/*------------------------------------------------------------------------------
	Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Function Prototype Declarations
------------------------------------------------------------------------------*/
extern int DE_KIPC_SetData(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
extern int DE_KIPC_GetData(UINT32 mcu_id, void *pMsg, UINT32 msgCnt);
extern int DE_KIPC_SetMem(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
#ifdef INCLUDE_KDRV_BE
extern int BE_MCU_SetData(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
extern int BE_MCU_GetData(UINT32 mcu_id, void *pMsg, UINT32 msgCnt);
#endif

#ifdef INCLUDE_KDRV_PQE
#ifdef USE_KDRV_CODES_FOR_L18
extern int pqe_ipc_command(DE_IPC_KEY_VALUE_T *data);
extern int pqe_ipc_status(DE_IPC_KEY_VALUE_T *data);
extern OS_SEM_T	_g_de_ipc_snd_sem[SOC_MCU_MAX];
#endif
#endif
/*------------------------------------------------------------------------------
	External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	global Functions  
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	global Variables
------------------------------------------------------------------------------*/
struct ipc_client g_ipc_client[MCU_ID_MAX] = 
{
	{ // MCU_ID_0
		DE_KIPC_SetData,
		DE_KIPC_GetData,
		DE_KIPC_SetMem,
	},
	{ // MCU_ID_1
		NULL, NULL, NULL
	},
	{ // MCU_ID_2
		NULL, NULL, NULL
	},
	{ // MCU_ID_3
		NULL, NULL, NULL
	},
	{ // MCU_ID_EXT_0
		NULL, NULL, NULL
	},
	{ // MCU_ID_EXT_1
		NULL, NULL, NULL
	},

};

static struct ipc_handle *gp_last_ipc_handle = NULL;
static char g_ipc_ready[MCU_ID_MAX];
static struct ipc_log g_ipc_log;
static struct ipc_log g_ipc_log_backup;
static UINT32 g_ipc_trace = 0;
#ifdef USE_KDRV_CODES_FOR_L18
static DE_IPC_KEY_VALUE_T g_ipc_key_value;
#endif

static int g_ipc_hal_ready_to_use = 0;
static UINT32 g_ipc_hal_ipc_mask = 0x0;

/*------------------------------------------------------------------------------
	Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int ipc_hal_write(UINT32 cmd, void *msg, UINT32 cnt);
static int ipc_hal_read(UINT32 mcu_id, void *msg, UINT32 cnt);

#ifdef INCLUDE_KDRV_PQE
#ifdef USE_KDRV_CODES_FOR_L18
static int ipc_hal_cmd_lowend(UINT32 cmd, void *msg, UINT32 cnt);
static int ipc_hal_read_lowend(UINT32 cmd, void *msg, UINT32 cnt);
#endif
#endif

/*------------------------------------------------------------------------------
	Static Variables
------------------------------------------------------------------------------*/
OS_SEM_T	_g_ipc_hal_sem;

/*==============================================================================
	Implementation Group
==============================================================================*/

int ipc_hal_init(void)
{
	int ret = RET_OK;

	OS_InitMutex(&_g_ipc_hal_sem, OS_SEM_ATTR_DEFAULT);

	ret = ipc_phys_hal_init();
	if(ret) return RET_ERROR;

	memset(g_ipc_client, 0, sizeof(struct ipc_client) * MCU_ID_MAX);
	memset(g_ipc_ready,  0, sizeof(char) * MCU_ID_MAX);
	memset(g_ipc_log.cmd, 0, sizeof(UINT32) * MAX_IPC_LOG);
	memset(g_ipc_log.buf, 0, sizeof(char*) * MAX_IPC_LOG);
#ifdef USE_KDRV_CODES_FOR_L18
	memset(&g_ipc_key_value, 0, sizeof(DE_IPC_KEY_VALUE_T));
#endif

	g_ipc_log.idx = 0;

	memset(g_ipc_log_backup.cmd, 0, sizeof(UINT32) * MAX_IPC_LOG);
	memset(g_ipc_log_backup.buf, 0, sizeof(char*) * MAX_IPC_LOG);
	g_ipc_log_backup.idx = 0;

#ifdef INCLUDE_KDRV_PQE
#ifdef USE_KDRV_CODES_FOR_L18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) ) {
		g_ipc_client[MCU_ID_0].write = ipc_hal_cmd_lowend;
		g_ipc_client[MCU_ID_0].read  = ipc_hal_read_lowend;

		g_ipc_client[MCU_ID_1].write = ipc_hal_cmd_lowend;
		g_ipc_client[MCU_ID_1].read  = ipc_hal_read_lowend;
	} else
#endif
#endif
	if ( lx_chip_rev() >= LX_CHIP_REV(O18,A0) ) {
		g_ipc_client[MCU_ID_0].write = ipc_hal_write;
		g_ipc_client[MCU_ID_0].read  = ipc_hal_read;
		g_ipc_client[MCU_ID_0].wrmem = DE_KIPC_SetMem;

		g_ipc_client[MCU_ID_1].write = ipc_hal_write;
		g_ipc_client[MCU_ID_1].read  = ipc_hal_read;
	}
	else
	{
		DE_ERROR("undefined chip\n");
		ret = RET_ERROR;
	}

	return ret;
}

int ipc_hal_cleanup(void)
{
	int ret = RET_OK;
	int i;

	for(i=0;i<MAX_IPC_LOG;i++)
	{
		if(g_ipc_log.buf[i] != NULL)
			kfree(g_ipc_log.buf[i]);
	}

	DE_PRINT("done.\n");

	return ret;
}

struct ipc_handle *ipc_hal_open(char *name, MCU_ID_TYPE mcu_id)
{
	struct ipc_handle *ipc_handle = (struct ipc_handle *)kmalloc( \
										sizeof(struct ipc_handle),\
										GFP_KERNEL);
	int i;

	if(ipc_handle == NULL)
	{
		DE_ERROR("ipc_handle kmalloc fail\n");
		return NULL;
	}

	if(	g_ipc_client[mcu_id].write != NULL &&\
		g_ipc_client[mcu_id].read  != NULL )
	{
		ipc_handle->m_ipc_client = &g_ipc_client[mcu_id];
		memset(ipc_handle->dev_name, 0, MAX_DEV_NAME);
		for(i=0;i<(MAX_DEV_NAME-1);i++)
		{
			ipc_handle->dev_name[i] = name[i];
			if(name[i] == 0) break;
		}
	}
	else
	{
		DE_ERROR("client function is null  (write:%p, read:%p\n",\
				g_ipc_client[mcu_id].write,\
				g_ipc_client[mcu_id].read);
		kfree(ipc_handle);
		return NULL;
	}

	ipc_handle->p_ready = &g_ipc_ready[mcu_id];
	ipc_handle->mcu_id = mcu_id;
	ipc_handle->prev   = (void *)gp_last_ipc_handle;
	gp_last_ipc_handle = ipc_handle;

	DE_PRINT("ipc_hal_open is done for %s , mcu_id %d\n", name, mcu_id);

	return ipc_handle;
}

int ipc_hal_close(struct ipc_handle *ipc_handle)
{
	if(!ipc_handle)
		return RET_ERROR;

	kfree(ipc_handle);

	DE_PRINT("ipc_close done.\n");
	
	return RET_OK;
}

int ipc_hal_list(void)
{
	struct ipc_handle *h = gp_last_ipc_handle;

	DE_PRINT("List of mcu ipc handler  | fw ready[%d/%d]\n", \
									g_ipc_ready[0], g_ipc_ready[1]);

	if(h == NULL) 
	{
		DE_PRINT("No list for mcu ipc\n");
		return RET_OK;
	}

	do {
		DE_PRINT("\t%s\t:  mcu %d\th->%p\n", h->dev_name,\
                                                h->mcu_id,  \
                                                h);
		if(h->prev == NULL) break;
		h = h->prev;
	} while(1);

	return RET_OK;
}

int ipc_hal_start(UINT32 mcu_id, char p)
{
	g_ipc_ready[mcu_id] = p;
	return RET_OK;
}


/* LGSI code restructing for the function "ipc_hal_trace" */

static void _ipc_dump_data( char *pBuf, UINT32 cnt)
{
	int i, j, m=0;
	char buffer[512];
	j = sprintf(buffer, "%-9s","packet]");
	for(i=0; i<cnt && j<500; i++)
	{
		j += sprintf(buffer+j, "%02X ", pBuf[i]);
		if(m++ == 3) {j += sprintf(buffer+j, " ");m=0;}
	}
	m = 0;
	printk("%s\n character count = %d\n",buffer,j);
}

static void _ipc_hal_log( struct ipc_log *ipc_log )
{
	int i = 0, k = 0;
	char *str;
	int ipc_total_size = 0;

	if (ipc_log == NULL)	return;

	printk("\n\n DE IPC HAL log (max %d, The last row is the latest ipc.)\n\n", MAX_IPC_LOG);
	for(i=0;i<MAX_IPC_LOG;i++)
	{
		k = i + ipc_log->idx;
		if(k >= MAX_IPC_LOG)
			k -= MAX_IPC_LOG;
		if( ipc_log->cmd[k] == 0 || \
			ipc_log->buf[k] == NULL) continue;
		STR_IPC_DST((ipc_log->cmd[k] >> DST_OFFSET) & 0xF, str);
		printk("\x1b[1;32m %03d ) %s MCU[%d] CMD[0x%08X] SIZE[%d] \x1b[0m \n",\
				k, str, MCU_ID(ipc_log->cmd[k]), \
				ipc_log->cmd[k], ipc_log->cnt[k]);

		_ipc_dump_data( ipc_log->buf[k], ipc_log->cnt[k] );

		ipc_total_size += sizeof(UINT32);  /* cmd */
		ipc_total_size += ipc_log->cnt[k];/* cnt */
		ipc_total_size += sizeof(char*) ;  /* param-pointer */
	}
	ipc_total_size += sizeof(UINT32)    ;  /* index */
	printk("Total size of ipc_log  %d  Bytes.\n", ipc_total_size);
}

int ipc_hal_trace(UINT32 param)
{
	int i = 0;
	char *str;

	switch(param)
	{
		case 0:
		case 1:
		case 2:
			g_ipc_trace = param;
			break;
		case 4:
			DE_PRINT("Destination of mcu ipc\n");
			for(i=IPC_DST_DE;i<IPC_DST_MAX;i++)
			{
				STR_IPC_DST(i, str);
				DE_PRINT("  %s	[%d]\n", str, i);
			}
			break;
		case 3:
			{
				_ipc_hal_log(&g_ipc_log);
			}
			break;
		case 5:
			{
				_ipc_hal_log(&g_ipc_log_backup);
			}
			break;
		default:
			break;
	}
	return RET_OK;
}

int ipc_hal_restore(void)
{
	int ret = RET_OK;
	int i = 0;
	UINT32 cmd;
	void *msg;
	UINT32 cnt;

	ret = OS_LockMutex(&_g_ipc_hal_sem);
	if(ret) return RET_OK;

	for(i=0;i<MAX_IPC_LOG;i++)
	{
		if( g_ipc_log_backup.cmd[i] == 0 || \
			g_ipc_log_backup.buf[i] == NULL) continue;

		cmd = g_ipc_log_backup.cmd[i];
		msg = (void *)g_ipc_log_backup.buf[i];
		cnt = g_ipc_log_backup.cnt[i];
		ret = DE_KIPC_SetData(cmd, msg, cnt);
		if (ret != RET_OK)
		{
			DE_NOTI("[%03d]cmd:0x%08x,cnt:%d\n",i,cmd,cnt);
		}
	}

	OS_UnlockMutex(&_g_ipc_hal_sem);

	return ret;
}

int ipc_hal_ready_to_use(int enable)
{
	int ret = RET_OK;
	int i;

	ret = OS_LockMutex(&_g_ipc_hal_sem);
	if(ret) return RET_OK;

	if (enable == 0)
	{
		/* cleanup cmd,buf */
		g_ipc_log_backup.idx = 0;

		for(i=0;i<MAX_IPC_LOG;i++)
		{
			if(g_ipc_log_backup.cmd[i] != 0) {
				g_ipc_log_backup.cmd[i] = 0;
			}

			if(g_ipc_log_backup.buf[i] != NULL) {
				kfree(g_ipc_log_backup.buf[i]);
				g_ipc_log_backup.buf[i] = NULL;
			}
		}
	}

	g_ipc_hal_ready_to_use = enable;

	OS_UnlockMutex(&_g_ipc_hal_sem);

	return RET_OK;
}

int ipc_hal_set_mask(UINT32 mask)
{
	g_ipc_hal_ipc_mask = mask;
	return RET_OK;
}

UINT32 ipc_hal_get_mask(void)
{
	return g_ipc_hal_ipc_mask;
}

#ifdef ENABLE_FW_IPC_LOG
static int ipc_hal_log(UINT32 cmd, void *msg, UINT32 cnt)
{
	int ret = RET_OK;
	UINT32 *p_idx = &g_ipc_log.idx;
	char *buf;

	ret = OS_LockMutex(&_g_ipc_hal_sem);
	if(ret) return RET_OK;

	do {
		//OS_GetCurrentTicks(&t.sec, &t.msec, &t.usec);
		if(g_ipc_log.buf[*p_idx] != NULL) kfree(g_ipc_log.buf[*p_idx]);
		buf = (char *)kmalloc(cnt, GFP_KERNEL);
		if (buf == NULL)	break;
		memcpy(buf, (char*)msg, cnt);
		g_ipc_log.cmd[*p_idx] = cmd;
		g_ipc_log.cnt[*p_idx] = cnt;
		g_ipc_log.buf[*p_idx] = buf;
		if(++*p_idx >= MAX_IPC_LOG) *p_idx = 0;
	} while(0);

	OS_UnlockMutex(&_g_ipc_hal_sem);

	return ret;
}
#endif

static int ipc_hal_log_backup(UINT32 cmd, void *msg, UINT32 cnt)
{
	int ret = RET_OK;
	UINT32 *p_idx = &g_ipc_log_backup.idx;
	char *buf;

	ret = OS_LockMutex(&_g_ipc_hal_sem);
	if(ret) return RET_OK;

	do {
		if((*p_idx+1) >= MAX_IPC_LOG)	break;
		if(g_ipc_log_backup.buf[*p_idx] != NULL)
		{
			kfree(g_ipc_log_backup.buf[*p_idx]);
			g_ipc_log_backup.buf[*p_idx] = NULL;
		}
		buf = (char *)kmalloc(cnt, GFP_KERNEL);
		if (buf == NULL)	break;
		memcpy(buf, (char*)msg, cnt);
		g_ipc_log_backup.cmd[*p_idx] = cmd;
		g_ipc_log_backup.cnt[*p_idx] = cnt;
		g_ipc_log_backup.buf[*p_idx] = buf;
		if(++*p_idx >= MAX_IPC_LOG) *p_idx = 0;
	} while(0);

	OS_UnlockMutex(&_g_ipc_hal_sem);

	return ret;
}

static int ipc_hal_write(UINT32 cmd, void *msg, UINT32 cnt)
{
	char *str;
	STR_IPC_DST((cmd >> DST_OFFSET) & 0xF, str);
	IPC_TRACE("WR: mcu [%d]  %s 	cmd[0x%08X] size[%d] use[%d] mask[0x%08X]\n", \
			MCU_ID(cmd), str, cmd, cnt, g_ipc_hal_ready_to_use, g_ipc_hal_ipc_mask);
	//if (cmd == DE_IPC_SET_FR_RATE) {DE_NOTI("set_frate cmd[0x%08X] size[%d] use[%d] mask[0x%08X]\n",cmd,cnt,g_ipc_hal_ready_to_use,g_ipc_hal_ipc_mask);}
	if(g_ipc_trace == 2)
	{
		_ipc_dump_data( (char *)msg, cnt );
	}
#ifdef ENABLE_FW_IPC_LOG
	ipc_hal_log(cmd, msg, cnt);
#endif

	if ((g_ipc_hal_ipc_mask >= 0xF0000000) && (cmd != DE_IPC_SET_SUSPEND))	return RET_OK;
	if (g_ipc_hal_ipc_mask == cmd)			return RET_OK;

	if (g_ipc_hal_ready_to_use==0)
		return ipc_hal_log_backup(cmd, msg, cnt);

	return DE_KIPC_SetData(cmd, msg, cnt);
}


static int ipc_hal_read(UINT32 mcu_id, void *msg, UINT32 cnt)
{
	int ret = RET_OK;
	int i, m=0;
	IPC_TRACE("RD: mcu [%d] size[%d]\n", mcu_id, cnt);

	ret = DE_KIPC_GetData(mcu_id, msg, cnt);

	if(g_ipc_trace == 2)
	{
		IPC_DUMP("packet]  ");
		for(i=0;i<cnt;i++)
		{
			IPC_DUMP("%02X ", *(char *)msg);
			if(m++ == 3) {IPC_DUMP(" ");m=0;}
		}
		m = 0;
		IPC_DUMP("\n\n");
	}
	return ret;
}


#ifdef INCLUDE_KDRV_PQE
#ifdef USE_KDRV_CODES_FOR_L18
static int ipc_is_readcmd( DE_IPC_CMD_T key )
{
	int ret = RET_ERROR;

	switch ( key )
	{
		case DE_IPC_GET_FIRMWARE_INFO:
		case DE_IPC_GET_INPUT_WIN:
		case DE_IPC_GET_OUT_WIN:
		case DE_IPC_GET_LOW_DELAY:
			ret = RET_OK;
			break;
	
		default :
			ret  = RET_ERROR;
			break;
	}

	return ret;
}

static int ipc_hal_read_lowend(UINT32 cmd, void *msg, UINT32 cnt)
{
	return RET_OK;
}

static int ipc_hal_cmd_lowend(UINT32 cmd, void *msg, UINT32 cnt)
{
	int ret = RET_OK;
	char *str;
	STR_IPC_DST((cmd >> DST_OFFSET) & 0xF, str);
	IPC_TRACE("WR: mcu [%d]  %s 	cmd[0x%08X] size[%d]\n", \
			MCU_ID(cmd), str, cmd, cnt);

	if(g_ipc_trace == 2)
	{
		_ipc_dump_data( (char *)msg, cnt );
	}
#ifdef ENABLE_FW_IPC_LOG
	ipc_hal_log(cmd, msg, cnt);
#endif

	DE_IPC_KEY_VALUE_T *param = &g_ipc_key_value;
	param->key  = cmd;

	if( ipc_is_readcmd(param->key) != RET_OK )
	{
		IPC_TRACE("[%s:%d] MCU WRITE!!!\n", __func__, __LINE__);

		//MCU_Write
		switch(param->key)
		{
		case DE_IPC_DE_INIT:
			CP_MSG2PQE( panel_type );		break;

		case DE_IPC_SET_INPUT_WIN:
			CP_MSG2PQE( in_win_dimension );	break;

		case DE_IPC_SET_OUT_WIN:
			CP_MSG2PQE( out_win_dimension );	break;

		case DE_IPC_SET_DIS_OUT:
			CP_MSG2PQE( dis_out );			break;

		case DE_IPC_SET_DIS_FMT:
			CP_MSG2PQE( dis_fmt );			break;

		case DE_IPC_SET_CVI_SRC_TYPE:
			CP_MSG2PQE( cvi_src_type );		break;

		case DE_IPC_SET_CVI_CSAMPLE_MODE :
			CP_MSG2PQE( csample_mode );		break;

#ifdef USE_SUPPORT_EUROPE
		case DE_IPC_SET_FR_RATE:
			CP_MSG2PQE( fr_rate );			break;
#endif

		case DE_IPC_SET_WIN_BLANK:
			CP_MSG2PQE( set_win_blank );	break;

		case DE_IPC_SET_CVI_FIR:
			CP_MSG2PQE( cvi_fir );			break;

		case DE_IPC_SET_CVI_TPG:
			CP_MSG2PQE( cvi_tpg );			break;

		case DE_IPC_SET_LOW_DELAY:
			CP_MSG2PQE( low_delay_ctrl );	break;

		case DE_IPC_SET_PLATFORM_VERSION:
			CP_MSG2PQE( platform_ver );		break;

		case DE_IPC_SET_IF_CONFIG:
			CP_MSG2PQE( if_config );		break;

		case DE_IPC_SET_INNER_PATTERN:
			CP_MSG2PQE( inner_pattern );		break;

		case DE_IPC_SET_WIN_PORT_SRC:
			CP_MSG2PQE( input_source );		break;

		case DE_IPC_SET_WIN_FREEZE:
			CP_MSG2PQE( win_freeze );		break;

		case PQL_IPC_SET_COLORFILTER :
			CP_MSG2PQE( pql_set_colorfilter );	break;

		default:
			DE_ERROR( "Not Support IPC CMD (0x%08X)\n", param->key);
			return RET_ERROR;
		}

		OS_LockMutex(&_g_de_ipc_snd_sem[0]);
		ret = pqe_ipc_command( param );
		OS_UnlockMutex(&_g_de_ipc_snd_sem[0]);
	}
	else
	{
		IPC_TRACE("[%s:%d] MCU_READ!!!\n", __func__, __LINE__);

		//MCU_Read
		OS_LockMutex(&_g_de_ipc_snd_sem[0]);
		pqe_ipc_status( param );
		OS_UnlockMutex(&_g_de_ipc_snd_sem[0]);

		//MCU READ
		switch(cmd)
		{
		case DE_IPC_GET_FIRMWARE_INFO:
			CP_MSG4PQE( firmware_info );	break;

		case DE_IPC_GET_INPUT_WIN:
			CP_MSG4PQE( in_win_dimension );	break;

		case DE_IPC_GET_OUT_WIN:
			CP_MSG4PQE( out_win_dimension );	break;

		case DE_IPC_GET_LOW_DELAY:
			CP_MSG4PQE( low_delay ); 	break;

		default:
			break;
		}

	}

	return ret;
}

#endif
#endif

