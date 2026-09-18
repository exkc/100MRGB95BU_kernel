/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file de_kadp.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author	dongho7.park (dongho7.park@lge.com)
 *  @version	1.0
 *  @date		2010-02-07
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define _SUPPORT_ION_

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/unistd.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/time.h>
#include <linux/delay.h>
#include "base_types.h"
#include "os_util.h"
//#include "osa_kadp.h"
//#include "debug_kadp.h"
#include "de_kwrap.h"
#include "os_util.h"
#include "de_kapi.h"
#include "afe_kapi.h"
//#include "afe_kadp.h"
#include "hdmi_kapi.h"
//#include "hdmi_kadp.h"
//#include "hdmi20_kadp.h"
#include "de_kwrap_defs.h"
//#include <dlfcn.h>
#include "resource_mgr.h"
#include "de_def.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define DE_MODULE_NAME       "/dev/lg/de0"
#define KADP_DE 			"kad-de"
#define JPEG_FROM_CPU_TO_DE
/* 20111115, sj.youm, hdmi scl_c_sample 444 or 422 결정을 위에서 내려오는 값으로 사용하기 위해 */
#define DE_SET_SCL_C_SAMPLING_BY_HDMI444MODE
#define ulong unsigned long
#define DE_FC_MMAP_HEIGHT_SIZE		1080

#define SEE_TV
#undef CHECK_NULL
#define CHECK_NULL(ptr)	{if(ptr == NULL) return RET_ERROR;}
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int g_de_kap_logm_fd = -1;
int memDev = -1;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int de_kwrap_getlowdelaymode(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#define NUM_OF_FIRMWARE 64
char g_mcu_binary[][NUM_OF_FIRMWARE] = {\
		"PQE_FW.bin", 	         \
		"M17A0_PQE_FW.bin",      \
		"M17B0_PQE_FW.bin",      \
		"M17C0_PQE_FW.bin",      \
		"L18FA0_FW.bin",         \
		"O18A0_PQE_FW.bin"};

char g_mcu1_binary[][NUM_OF_FIRMWARE] = {\
		"PQE_FW_MCU1.bin",			 \
		"O18_PQE_FW_MCU1.bin",   \
		};

lx_de_ctx_t		g_de_ctx =
{
	.dev_fd 	= -1,		/* dev_fd should be initialized to -1 */
	//.dev_mtx	= NULL,
	//.dev_shmem	= NULL,
	.ref_cnt 	= 0,
};

__attribute__((unused)) static LX_DE_DIS_FMT_T _g_de_DisInfo = { LX_PANEL_TYPE_1920, 60, 1920, 1080, LX_PANEL_DEV_LCD};

__attribute__((unused)) static LX_DE_ZLIST_T _g_de_zlist = {1, {1, 0}, {255, 255}};
__attribute__((unused)) static LX_DE_DVR_DISFMT_T _g_de_dvrFmt = {0, 0, 0, 0, 0, 0};

static LX_DE_HDMI444_MODE_T _g_de_IsHdmi444Mode[LX_DE_WIN_MAX] = { 0 };
// workaround code for horizontal picture shaking on component 480i
BOOLEAN _g_de_IsADCSrcChange = FALSE;	//110817, wonsik.do

__attribute__((unused)) static LX_DE_UD_CTRL_T _g_de_IsUD = LX_DE_UD_OFF;
__attribute__((unused)) static LX_DE_3D_INOUT_CTRL_T _g_de_Is3D;
__attribute__((unused)) static BOOLEAN _g_de_IsMultiWin = FALSE;
// __attribute__((unused)) static LX_DE_ACT_FORMAT_T _g_de_actFormat = {0, 0};
__attribute__((unused)) static BOOLEAN _g_4k_dual_mode = FALSE;

__attribute__((unused)) static LX_DE_INNER_PATTERN_T _g_de_in_pattern = {0, 0, 0};

__attribute__((unused)) static LX_DE_CAPACITY_T g_chip_capa;
__attribute__((unused)) static UINT32 _g_de_chip_capa_initialized = 0;
__attribute__((unused)) static UINT32	_g_de_hdmi_phys[LX_DE_WIN_MAX] = {0, 0, 0, 0};

BOOLEAN gDE_Debug_InWin = FALSE;
BOOLEAN gDE_Debug_OutWin = FALSE;
BOOLEAN gDE_Debug_Mute = FALSE;


struct cap_info {
	ulong addr_y;
	ulong addr_c;
	ulong w_size;
	ulong addr_y_phys;
	ulong addr_c_phys;
};

struct cap_info cap_info =
{
	.addr_y = 0,
	.addr_c = 0,
	.w_size = 0,
	.addr_y_phys = 0,
	.addr_c_phys = 0,
};

__attribute__((unused)) static UINT32 _g_de_lowdelaymode = 0;

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 *	set hdmi pc label
 *
 */
int de_kwrap_sethdmi444mode(UINT32 win, LX_DE_HDMI444_MODE_T mode)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	_g_de_IsHdmi444Mode[win] = mode;
	return RET_OK;
}

/**
 *	get hdmi pc label
 *
 */
int de_kwrap_gethdmi444mode(UINT32 win, LX_DE_HDMI444_MODE_T *mode)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(mode);
	*mode = _g_de_IsHdmi444Mode[win];
	return RET_OK;
}

/**
 *	Get Source status
 *
 */
int de_kwrap_getsourcestatus(LX_DE_SRC_STATUS_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOR_GET_SRC_STATUS, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_getcapacity(LX_DE_CAPACITY_T *p_capa)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//20240626,Add init in case the de_kwrap_getcapacity() function caller does not initialize the input parameter.
	if (_g_de_chip_capa_initialized == 0)
	{
		memset(&g_chip_capa,0,sizeof(g_chip_capa));
		_g_de_chip_capa_initialized = 1;
		DE_NOTI("init capa\n");
	}

	/* g_chip_capa structure can't be initialized in multi-process environment. */
	/* if de_kwrap_init() is not called. */
	if(g_chip_capa.chip_id == 0 )
	{
		/* init if not initialized. */
		ret = resource_mgr_ioctl( DE_IOR_GET_CAPACITY, (unsigned long)&g_chip_capa,CALL_FROM_KERNEL);
	}
	memcpy(p_capa, &g_chip_capa, sizeof(LX_DE_CAPACITY_T));

	return ret;
}

int de_kwrap_setipchdrmode(UINT8 i_ucWinID,LX_HDR_MODE_T i_IpcMode,LX_HDR_MODE_FROM_T i_From)
{
	int ret = RET_ERROR;
	LX_DE_HDR_IPC_MODE_T sParam;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		sParam.ucWinID = i_ucWinID;
		sParam.eIpcMode = i_IpcMode;
		sParam.eFrom = i_From;

		ret = resource_mgr_ioctl( DE_IOW_IPC_SET_HDR_MODE,(unsigned long)&sParam,CALL_FROM_KERNEL);
		if ( ret < 0 )
		{
			DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();
	return 0;
}

/**
 * de set Low delay mode for frame delay.
 *  0 : Off,  1 : Low Delay
 */
int de_kwrap_setlowdelaymode(UINT32 param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	//DE_NOTI("[de_kwrap] SetLowDelayMode = %d\n",  param);
	_g_de_lowdelaymode = param;
	ret = resource_mgr_ioctl( DE_IOW_SET_LOW_DELAY, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_getlowdelaymode(void)
{
	return (int)_g_de_lowdelaymode;
}

/**
 * set inner pattern
 *
 * @param *param [in] LX_DE_INNER_PATTERN_T
 * @return int
 * @see
 * @author
 */
int de_kwrap_setinnerpattern(LX_DE_INNER_PATTERN_T *param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]set inner pattern(en:%d,type:%d,level:%d).\n",\
		param->enable,param->type,param->level);

	_g_de_in_pattern.enable = param->enable;
	_g_de_in_pattern.type = param->type;
	_g_de_in_pattern.level = param->level;

	//ret = resource_mgr_ioctl( DE_IOW_SET_INNER_PATTERN, param);
	ret = resource_mgr_ioctl(DE_IOW_SET_INNER_PATTERN,(unsigned long) param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set input source path of scaler windows
 *
 */
int de_kwrap_setwinsrcport(LX_DE_INPUT_SOURCE_T *param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]set win src port win_id(%d) Src(%d) port_id(%d)\n", \
					param->srcId, param->srcType, param->srcPort);
	ret = resource_mgr_ioctl( DE_IOW_SET_WIN_PORT_SRC, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

#if 0	//not used
/**
 *	de device open
 *
 */

int de_kwrap_open(void)
{
	int		ret = RET_ERROR;

#ifdef SEE_TV
#else
	int		dev_fd;

	/* if device is already opened, just increase ref_cnt and exit */
	if ( g_de_ctx.dev_fd >= 0 )
	{
		//DE_LOCK();
		g_de_ctx.ref_cnt++;
		//DE_TRACE("[de_kwrap] %s : ignore multiple initialization\n", __F__ );
		//DE_UNLOCK();
		return RET_OK;
	}

	DE_INIT_LOCK();

	/* semahore should be locked before any interface to de */
	//DE_LOCK();
	//DE_TRACE_BEGIN();

	dev_fd = open(DE_MODULE_NAME, O_RDWR);
	DE_CHECK_CODE( dev_fd < 0, goto func_exit, "[de_kwrap] %s : can't open DE device (%s)\n", __F__, DE_MODULE_NAME );

	g_de_ctx.dev_fd = dev_fd;
	g_de_ctx.ref_cnt = 1;
#endif

	de_kwrap_setgcpinit();

	ret = RET_OK;

#ifdef SEE_TV
#else

	/* Added for /dev/mem  ACR operation */
	if (memDev<0) {memDev = open("/dev/mem", O_RDWR | O_SYNC); DE_PRINT("MMAP /dev/mem device open return value [%d].\n", memDev);}
// should remove !!! 	if (memDev<0) {DE_ERROR("ERROR! /dev/mem could not be opened!\n");}

	DE_NOTI("[de_kwrap] device is opened (dev_fd = %d)\n" , dev_fd);
#endif

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

    return ret;
}

/**
 *	de device check open status
 *
 */
int de_kwrap_isopen(void)
{
#ifdef SEE_TV //need to decide
	return 0;
#else

	if (g_de_ctx.dev_fd < 0)
		return	RET_ERROR;
	else
		return	RET_OK;
#endif
}

/**
 *	de device is close
 *
 */
int de_kwrap_close(void)
{
	 int	ret = RET_OK;

#ifdef SEE_TV
#else

	if ( g_de_ctx.dev_fd < 0 )
	{
		//DE_TRACE("[de_kwrap] %s : ignore multiple cloesed\n", __F__ );
		return ret;
	}

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	/* check DE ref_cnt before closing the real device */
	if ( --g_de_ctx.ref_cnt > 0 )
	{
		//DE_TRACE("[de_kwrap] %s : ignore multiple closed\n", __F__ );
		ret = RET_OK; goto func_exit;
	}

	ret = close( g_de_ctx.dev_fd );
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : can't close DE device (%s)\n", __F__, DE_MODULE_NAME );

	DE_NOTI("[de_kwrap] device is closed (dev_fd = %d)\n" , g_de_ctx.dev_fd );

	g_de_ctx.dev_fd = -1;

func_exit:
	//DE_TRACE_END();
	//DE_UNLOCK();

	/* osa resource destroyed */
	if ( g_de_ctx.ref_cnt <= 0 )
	{
		KADP_OSA_CloseSema( g_de_ctx.dev_mtx );
		g_de_ctx.dev_mtx 	= NULL;
	}
#endif
	return ret;
}

void de_kwrap_dbg_initialize(void)
{
#ifdef SEE_TV
#else

	g_de_kap_logm_fd = KADP_LOGM_ObjRegister(de_kwrap);
	if (g_de_kap_logm_fd < 0)
	{
		printf("[%s:%u] fail register logm\n", __F__, __L__);
		return;
	}

	KADP_LOGM_BitMaskEnable(g_de_kap_logm_fd, LX_LOGM_LEVEL_NOTI);
	KADP_LOGM_BitMaskEnable(g_de_kap_logm_fd, LX_LOGM_LEVEL_ERROR);
	KADP_LOGM_BitMaskEnable(g_de_kap_logm_fd, LX_LOGM_LEVEL_WARNING);
//	KADP_LOGM_BitMaskEnable(g_de_kap_logm_fd, LX_LOGM_LEVEL_DEBUG);
#endif
}

void de_kwrap_dbg_shutdown(void)
{
#ifdef SEE_TV
#else

	int ret;

	ret = KADP_LOGM_ObjDeregister(de_kwrap);
	if (ret < 0)
	{
		printf("[%s:%u] fail deregister logm\n", __F__, __L__);
		return;
	}
	g_de_kap_logm_fd = -1;
#endif
}

__attribute__((unused)) static int _fw_download_from_libkbl(void)
{
#ifdef SEE_TV
	return 0;
#else

#define KBL_DE_SYM_NAME      "de_get_fw_data"
#define KBL_DE_PATH_00       "/usr/lib/libkbl-de.so"       /* for webOS */
#define KBL_DE_PATH_01       "/usr/local/lib/libkbl-de.so" /* for pioneer */


	LX_DE_FW_DWLD_T de_fw_opt;
	void * handle = NULL;
	unsigned char * (*pfn_get_fw_data)(unsigned int v, int * s, unsigned int * i);
	char * error;
	unsigned char * data;
	int ret = RET_ERROR;
	int version;
	int plt_info;
	int size;
	struct stat file_info;

	if (!lstat(KBL_DE_PATH_00, &file_info))
		handle = dlopen(KBL_DE_PATH_00, RTLD_NOW);
	else
		handle = dlopen(KBL_DE_PATH_01, RTLD_NOW);

	if (!handle)
	{
		DE_ERROR("error: %s\n", dlerror());
		return ret;
	}

	pfn_get_fw_data = dlsym(handle, KBL_DE_SYM_NAME);

	DE_CHECK_CODE((long)(error = dlerror()),goto error_func, "error: %s (%d)\n",error, stderr);

	switch(lx_chip_rev())
	{
		case LX_CHIP_REV(L18, A0):
			version = 0xA000;
			break;
		case LX_CHIP_REV(M16, A0):
			version = 0xA000;
			break;
		default:
			DE_ERROR("error: not supported\n");
			goto error_func;
	}

	data = pfn_get_fw_data(version, &size, (unsigned int *)&plt_info);

	DE_CHECK_CODE((NULL == data)||(0 == size), goto error_func,
				"error: No data in libkbl-de.so (%p):(%d)\n", data, size);

	DE_CHECK_CODE((plt_info != PLATFORM_CHIP_VER), goto error_func,
				"error: Invaild chip version(=%x)\n", plt_info);

	de_fw_opt.inx = 3;
	de_fw_opt.pData = (char *)data;
	de_fw_opt.size = size;

	ret = de_kwrap_fw_download(&de_fw_opt);

error_func:
	dlclose(handle);
	return ret;
#endif
}


__attribute__((unused)) static int _fw_download(int flag)
{
	int ret = RET_ERROR;

#ifdef SEE_TV
	return RET_OK;
#else

	LX_DE_FW_DWLD_T de_fw_opt;
	//FILE *fp_pqe = NULL;
	//FILE *fp = NULL, *fp1 = NULL;
	UINT8 *p_fw = NULL;
	UINT32 fw_size = 0;
	struct file *f;
	struct dile *fp1;
	mm_segment_t fs;

	UINT8 fw_count, fw_count1;
	char root_path[] = "/var/firmware/";
	char pqe_fw[] = "/var/firmware/pqe_fw.info";
	char *fw_name;

	int size = 0;

	fw_count  = (UINT8)(sizeof(g_mcu_binary) / NUM_OF_FIRMWARE);
	fw_count1 = (UINT8)(sizeof(g_mcu1_binary) / NUM_OF_FIRMWARE);

	fw_name = kmalloc(256,GFP_KERNEL);
	memset(fw_name, 0, 256);

	f = filp_open(pqe_fw, O_RDONLY,0);

#if 1
// mcu1 ===========================
	while(--fw_count1)
	{
		memset(fw_name, 0, 256);
		strcat(fw_name, root_path);
		strcat(fw_name, g_mcu1_binary[fw_count1]);
		fp1 = filp_open(fw_name, O_RDONLY,0);
		if(fp1) break;
	}
	if(fp1)
	{
		lseek(fp1, 0L, SEEK_END);
		fw_size = ftell(fp1);
		lseek(fp1, 0L, SEEK_SET);
		if(fw_size > 0)
			p_fw = kmalloc(fw_size,GFP_KERNEL);

		if(p_fw)
		{
			 // Get current segment descriptor
			 fs = get_fs();
			 // Set segment descriptor associated to kernel space
			 set_fs(get_ds());
			 f->f_pos = 0;
			size = fp1->f_op->read(f,p_fw, fw_size, &f->f_pos);
		}

		DE_NOTI("MCU1 firmware [%s]	size = %d KB\n", fw_name, fw_size/1024);
		if(size)
		{
			de_fw_opt.inx = 4;
			de_fw_opt.size = fw_size;
			de_fw_opt.pData = (char*)p_fw;
			ret = de_kwrap_fw_download(&de_fw_opt);
			if(ret)
			{
				DE_ERROR("de_kwrap_fw_download  ret[%d]", ret);
			}
		}
	}
	if(fp1)  filp_close(fp1,NULL);
	if(p_fw) OS_Kfree(p_fw);
	fp1  = NULL;
	p_fw = NULL;
#endif

// mcu0 ===========================
	while(--fw_count)
	{
		memset(fw_name, 0, 256);
		strcat(fw_name, root_path);
		strcat(fw_name, g_mcu_binary[fw_count]);
		fp = fopen(fw_name, "r");
		if(fp) break;
	}

	if(fp)
	{
		fseek(fp, 0L, SEEK_END);
		fw_size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		if(fw_size > 0)
			p_fw = kmalloc(fw_size);
		else
			DE_NOTI("file size 0\n");
		if(p_fw)
		{
			de_fw_opt.inx = 0;
			de_fw_opt.size = 0;
			de_fw_opt.pData = (char*)NULL;

			size = fread(p_fw, 1, fw_size, fp);
			if(size)
			{
				de_fw_opt.inx = 3;
				de_fw_opt.size = fw_size;
				de_fw_opt.pData = (char*)p_fw;
			}
			DE_NOTI("MCU0 firmware [%s]  size = %d KB\n", fw_name, fw_size/1024);
		}
		else
			DE_ERROR("malloc fail !!!!\n", fw_size);
	}
	else
	{
		de_fw_opt.inx = 0;
		de_fw_opt.size = 0;
		de_fw_opt.pData = NULL;

		DE_NOTI("MCU firmware is loading from the header file.\n");
	}

	// de firmware download
	ret = de_kwrap_fw_download(&de_fw_opt);

	if(p_fw)    kfree(p_fw);
	if(fw_name) kfree(fw_name);
	if(fp)      fclose(fp);
	if(fp_pqe)  fclose(fp_pqe);
#endif
	return ret;
}

/**
 *	initialize de block with F/W download
 *
 */
int de_kwrap_Init(BOOLEAN isFullHD)
{
	int ret = RET_ERROR;
	LX_DE_PANEL_TYPE_T panel_type;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	_g_de_Is3D.run_mode = LX_DE_3D_RUNMODE_OFF;

#ifdef SEE_TV
	return RET_OK;
#else

#ifdef __USE_FWDATA_FROM_LIBKBL
	ret = _fw_download_from_libkbl();

	if (ret != RET_OK)
#endif
	//this feature need to be decided later
	//ret = _fw_download(1);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : Fail to download DE firmware\n", __F__ );
#endif
#if (CONFIG_LX_BOARD_UD == 1)
	isFullHD = FALSE;
#endif
	if (isFullHD == TRUE)
	{
		panel_type = LX_PANEL_TYPE_1920;
	}
	else
	{
		panel_type = LX_PANEL_TYPE_3840;
	}

	ret = resource_mgr_ioctl(DE_IOW_DE_INIT,(unsigned long)&panel_type,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

	ret = resource_mgr_ioctl(DE_IOR_GET_CAPACITY, (unsigned long)&g_chip_capa,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

    return ret;
}

/**
 *	Download Firmware of DE
 *
 */
int de_kwrap_fw_download(LX_DE_FW_DWLD_T *param)
{
	int ret = RET_ERROR;
#ifdef SEE_TV
	return RET_OK;
#else
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl(DE_IOW_FW_DOWNLOAD,(unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );
	DE_PRINT("[de_kwrap]OK - u-code downloading is done. ret = %d\n", ret);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	{
		UINT32 a,b,c,d;
		de_kwrap_getcapturebufferinfo(&a, &b, &c, &d);
	}
#endif
	return ret;
}

/**
 *	get de firmware info
 *
 */
int de_kwrap_getfirmwareinfo( LX_DE_FIRMWARE_INFO_T *info )
{
	int ret = RET_ERROR;
	LX_DE_FIRMWARE_INFO_T param = { 0, };

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(info);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	//ret = resource_mgr_ioctl( DE_IOR_GET_FIRMWARE_INFO, (unsigned long)&paramparamparamparam);
	ret = resource_mgr_ioctl(DE_IOR_GET_FIRMWARE_INFO,(unsigned long)&param,CALL_FROM_KERNEL);
	if ( ret < 0 )
	{
		DE_ERROR("[de_kwrap] %s : error in ioctl call %d.\n", __F__ ,ret);

		info->version = 0;
		info->date.year = 0;
		info->date.month = 0;
		info->date.day = 0;

		goto func_exit;
	}

	info->version = param.version;
	info->date.year = param.date.year;
	info->date.month = param.date.month;
	info->date.day = param.date.day;

	DE_PRINT("[de_kwrap]u-code ver.%d  update %d/%d/%d \n", info->version,  info->date.year, info->date.month, info->date.day);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * get inner pattern
 *
 * @param *param [in/out] LX_DE_INNER_PATTERN_T
 * @return int
 * @see
 * @author
 */
int de_kwrap_getinnerpattern(LX_DE_INNER_PATTERN_T *param)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	param->enable = _g_de_in_pattern.enable;
	param->type = _g_de_in_pattern.type;
	param->level = _g_de_in_pattern.level;
	return RET_OK;
}

/**
 *	set background color
 *
 */
int de_kwrap_setbgcolor(UINT8 red, UINT8 green, UINT8 blue)
{
	int ret = RET_ERROR;
	LX_DE_COLOR_T bg_color;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();
	// support only gray color back-ground.
	bg_color.r = 128;//red;
	bg_color.g = green;
	bg_color.b = 128;//blue;

	DE_NOTI("[de_kwrap]set bg color rgb(%d,%d,%d).\n", bg_color.r, bg_color.g, bg_color.b);

	//ret = resource_mgr_ioctl( DE_IOW_SET_BG_COLOR, &bg_color);
	ret = resource_mgr_ioctl(DE_IOW_SET_BG_COLOR,(unsigned long)&bg_color,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get output frame rate
 *
 */
int de_kwrap_getoutfrrate(BOOLEAN *isForceFreeRun, UINT16 *dis_fr)
{
	int ret = RET_ERROR;
	LX_DE_FR_RATE_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(isForceFreeRun);
	CHECK_NULL(dis_fr);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl(DE_IOR_GET_OUT_FR_RATE,(unsigned long)&param,CALL_FROM_KERNEL);

	if ( ret < 0 )
	{
		DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
		*dis_fr = 60;
		*isForceFreeRun = 0;
		goto func_exit;
	}

	*dis_fr = param.fr_rate;
	*isForceFreeRun = param.isForceFreeRun;

	DE_PRINT("[de_kwrap]display framerate is %d Hz and is_forced free run= %d. \n", param.fr_rate, param.isForceFreeRun);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set windows to be blank
 *
 */
int de_kwrap_setwinblank(UINT8 wId, BOOLEAN bOnOff, UINT8 color)
{
	int ret = RET_ERROR;
	LX_DE_SET_WIN_BLANK_T param = {LX_DE_WIN_MAIN, FALSE, {128, 0, 128}, FALSE};

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	if (gDE_Debug_Mute)		return RET_OK;

	//DE_LOCK();
	//DE_TRACE_BEGIN();
#if 0
	if (wId < 1)	param.win_id = LX_DE_WIN_MAIN;
	else			param.win_id = LX_DE_WIN_SUB;
#else
	param.win_id = (LX_DE_WIN_ID_T)wId;
#endif

	param.bEnable = bOnOff;

	if (color == 0)		// VIDEO_DDI_WIN_COLOR_BLACK
	{
		param.win_color.r	= 128;
		param.win_color.g	= 0;	// 16
		param.win_color.b	= 128;
	}
	else if (color == 1)		// VIDEO_DDI_WIN_COLOR_BLUE
	{
		if ( lx_chip_rev( ) == LX_CHIP_REV(L18,A0) )
		{
			param.win_color.r	= 255;
			param.win_color.g	= 100;
			param.win_color.b	= 66;
		}
		else
		{
			param.win_color.r	= 120;//117;
			param.win_color.g	= 28;//46;
			param.win_color.b	= 212;//-19;
		}

	}
	else if (color == 2)		// VIDEO_DDI_WIN_COLOR_GRAY
	{
		param.win_color.r	= 128;
		param.win_color.g	= 128;
		param.win_color.b	= 128;
	}
	else	// default color is black
	{
		param.win_color.r	= 128;
		param.win_color.g	= 0;	//16
		param.win_color.b	= 128;
	}

	param.isRGB = FALSE;

	DE_NOTI("[de_kwrap]blank wid = %d isOn = %d GBR(%d,%d,%d) isRGB = %d \n", param.win_id, param.bEnable,
											 param.win_color.g, param.win_color.b, param.win_color.r, param.isRGB);

	ret = resource_mgr_ioctl(DE_IOW_SET_WIN_BLANK,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get scaler input window size and position
 *
 */
int de_kwrap_getinputwin(UINT8 wId, LX_DE_RECT_T *pIn)
{
	int ret = RET_ERROR;
	LX_DE_WIN_DIMENSION_T param = { 0, };

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(pIn);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	if (wId < 1)	param.win_id = LX_DE_WIN_MAIN;
	else			param.win_id = LX_DE_WIN_SUB;

	ret = resource_mgr_ioctl(DE_IOR_GET_INPUT_WIN,(unsigned long)&param,CALL_FROM_KERNEL);
	if ( ret < 0 )
	{
		pIn->w = 0;
		pIn->h = 0;
		pIn->x = 0;
		pIn->y = 0;
		DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
		goto  func_exit;
	}

	pIn->w = param.rect.w;
	pIn->h = param.rect.h;
	pIn->x = param.rect.x;
	pIn->y = param.rect.y;

	DE_PRINT("[de_kwrap]get input window wid = %d whxy(%d,%d,%d,%d)\n", param.win_id,
													pIn->w, pIn->h, pIn->x, pIn->y);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get scaler output window size and position
 *
 */
int de_kwrap_getoutwin(UINT8 wId, LX_DE_RECT_T *pOut)
{
	int ret = RET_ERROR;
	LX_DE_WIN_DIMENSION_T param = { 0, };

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(pOut);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	if (wId < 1)	param.win_id = LX_DE_WIN_MAIN;
	else			param.win_id = LX_DE_WIN_SUB;

	//ret = resource_mgr_ioctl( DE_IOR_GET_OUT_WIN, &param);
	ret = resource_mgr_ioctl(DE_IOR_GET_OUT_WIN,(unsigned long)&param,CALL_FROM_KERNEL);
	if ( ret < 0 )
	{
		DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
		pOut->w = 0;
		pOut->h = 0;
		pOut->x = 0;
		pOut->y = 0;
		goto  func_exit;
	}

	pOut->w = param.rect.w;
	pOut->h = param.rect.h;
	pOut->x = param.rect.x;
	pOut->y = param.rect.y;

	DE_PRINT("[de_kwrap]get output window wid = %d whxy(%d,%d,%d,%d)\n", param.win_id,
												pOut->w, pOut->h, pOut->x, pOut->y);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get scaler output window size and position from cache.
 *    (instead of querying to DE_firmware)
 *	better in speed but a bit less accurate than querying
 *
 */
int de_kwrap_getoutwincached(UINT8 wId, LX_DE_RECT_T *pOut)
{
	int ret = RET_ERROR;
	LX_DE_WIN_DIMENSION_T param = { 0, };

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(pOut);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	if (wId < 1)	param.win_id = LX_DE_WIN_MAIN;
	else			param.win_id = LX_DE_WIN_SUB;

	//ret = resource_mgr_ioctl( DE_IOR_GET_OUT_WIN_CACHED, &param);
	ret = resource_mgr_ioctl(DE_IOR_GET_OUT_WIN_CACHED,(unsigned long)&param,CALL_FROM_KERNEL);

	if ( ret < 0 )
	{
		DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
		pOut->w = 0;
		pOut->h = 0;
		pOut->x = 0;
		pOut->y = 0;
		goto  func_exit;
	}

	pOut->w = param.rect.w;
	pOut->h = param.rect.h;
	pOut->x = param.rect.x;
	pOut->y = param.rect.y;

	DE_PRINT("[de_kwrap]get output window wid = %d whxy(%d,%d,%d,%d)\n", param.win_id,
												pOut->w, pOut->h, pOut->x, pOut->y);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set scaler input window size and position
 *
 */
int de_kwrap_setinputwin(UINT8 wId, LX_DE_RECT_T *pIn)
{
	int ret = RET_OK;
	LX_DE_WIN_DIMENSION_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(pIn);

	if (gDE_Debug_InWin)		return RET_OK;

	if ( pIn->w ==0 || pIn->h == 0 )
	{
//		DE_NOTI("Not Support --Zero In size.\n");
		return ret;
	}

	//DE_LOCK();
	//DE_TRACE_BEGIN();
#if 0
	if (wId < 1)	param.win_id = LX_DE_WIN_MAIN;
	else			param.win_id = LX_DE_WIN_SUB;
#else
	param.win_id = (LX_DE_WIN_ID_T)wId;
#endif

#if 0
	if(g_chip_capa.max_in_size.w > 1920) // for H15
	{
		if ((pIn->w + pIn->x) > 4096)
		{
			pIn->x = 0;
			pIn->y = 0;
			pIn->w = 4096;
			pIn->h = 2160;
		}
	}
	else // for H13, M14
	{
		if ((pIn->w + pIn->x) > 1920)
		{
			DE_NOTI("HW constraint--H-size/offset!\n");

			pIn->x = 0;
			pIn->y = 0;
			pIn->w = 1920;
			pIn->h = 1080;

			if (_g_de_IsUD)
			{
				pIn->x = 0;
				pIn->y = 0;
				pIn->w = 1920;
				pIn->h = 2160;
			}
		}
	}
#endif
	param.rect.w = pIn->w;
	param.rect.h = pIn->h;
	param.rect.x = pIn->x;
	param.rect.y = pIn->y;

	DE_NOTI("[de_kwrap]set input window wid = %d whxy(%d,%d,%d,%d)\n", param.win_id,
						param.rect.w, param.rect.h, param.rect.x, param.rect.y);

	ret = resource_mgr_ioctl(DE_IOW_SET_INPUT_WIN,(unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set scaler output window size and position
 *
 */
int de_kwrap_setoutwin(UINT8 wId, LX_DE_RECT_T *pOut)
{
	int ret = RET_ERROR;
	LX_DE_WIN_DIMENSION_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(pOut);

	if (gDE_Debug_OutWin)		return RET_OK;

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param.win_id = (LX_DE_WIN_ID_T)wId;

#if 0
	if(g_chip_capa.chip_id >= 5) // for M16
	{
		if ((pOut->w + pOut->x) > 3840)
		{
			pOut->x = 0;
			pOut->w = 3840;
		}
		if ((pOut->h + pOut->y) > 2160)
		{
			pOut->y = 0;
			pOut->h = 2160;
		}
	}
	else if(g_chip_capa.chip_id == 4) // for H15
	{
		if ((pOut->w + pOut->x) > 3840)
		{
			pOut->x = 0;
			pOut->w = 3840;
		}
		if ((pOut->h + pOut->y) > 2160)
		{
			pOut->y = 0;
			pOut->h = 2160;
		}
		if(wId > 0 && _g_4k_dual_mode == FALSE)
		{
			if(pOut->w > 1920)
				pOut->w = 1920;
			if(pOut->h > 1080)
				pOut->h = 1080;
		}
	}
	else
	{
		if ((pOut->w + pOut->x) > 1920)
		{
			pOut->x = 0;
			pOut->w = 1920;
		}
		if ((pOut->h + pOut->y) > 1080)
		{
			pOut->y = 0;
			pOut->h = 1080;
		}
	}

#endif
	param.rect.w = pOut->w;
	param.rect.h = pOut->h;
	param.rect.x = pOut->x;
	param.rect.y = pOut->y;

	DE_NOTI("[de_kwrap]set output window wid = %d whxy(%d,%d,%d,%d)\n", param.win_id,
												param.rect.w, param.rect.h, param.rect.x, param.rect.y);

	ret = resource_mgr_ioctl(DE_IOW_SET_OUT_WIN, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set rotate, source size, in/out window info
 *
 */
int de_kwrap_setwindowinfo(LX_DE_WIN_INFO_T *pWinInfo)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(pWinInfo);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl(DE_IOW_SET_WIN_INFO, (unsigned long)pWinInfo,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	control scaler display out on/off
 *
 */
int de_kwrap_setdisout(BOOLEAN isOn)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_PRINT("de_kwrap_setdisout %s\n", isOn?"ON":"OFF");
	ret = resource_mgr_ioctl( DE_IOW_SET_DIS_OUT, (unsigned long)&isOn,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set display format depend on panel attributes
 *
 */
int de_kwrap_setdisfmt(LX_DE_DIS_FMT_T dis_fmt)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	_g_de_DisInfo.panel_type = dis_fmt.panel_type;
	_g_de_DisInfo.fr_rate = dis_fmt.fr_rate;
	_g_de_DisInfo.h_total = dis_fmt.h_total;
	_g_de_DisInfo.v_total = dis_fmt.v_total;
	_g_de_DisInfo.dev_type = dis_fmt.dev_type;
	_g_de_DisInfo.h_active = dis_fmt.h_active;
	_g_de_DisInfo.v_active = dis_fmt.v_active;

	DE_NOTI("de_kwrap_setdisfmt panel type %d, fr rate =%d h_total = %d, v_total = %d. dev_type = %d\n",
								dis_fmt.panel_type, dis_fmt.fr_rate, dis_fmt.h_total, dis_fmt.v_total, dis_fmt.dev_type);
	ret = resource_mgr_ioctl( DE_IOW_SET_DIS_FMT, (unsigned long)&dis_fmt,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}


/**
 *	get display format Info for GED
 *
 */
int de_kwrap_getdisfmt(LX_DE_DIS_FMT_T *dis_fmt)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(dis_fmt);

	dis_fmt->panel_type = _g_de_DisInfo.panel_type;
	dis_fmt->fr_rate = _g_de_DisInfo.fr_rate;
	dis_fmt->h_total = _g_de_DisInfo.h_total;
	dis_fmt->v_total = _g_de_DisInfo.v_total;
	dis_fmt->dev_type = _g_de_DisInfo.dev_type;
	dis_fmt->h_active = _g_de_DisInfo.h_active;
	dis_fmt->v_active = _g_de_DisInfo.v_active;

	return RET_OK;
}

/**
 *	set display frame rate on forced free run mode
 *
 */
int de_kwrap_setfrrate(BOOLEAN isForceFreeRun, UINT16 frameRates)
{
	int ret = RET_ERROR;
	LX_DE_FR_RATE_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param.isForceFreeRun = isForceFreeRun;
	param.fr_rate = frameRates;

	_g_de_DisInfo.fr_rate = frameRates;

	DE_NOTI("[de_kwrap]SetFrRate isForceFreeRun %s, fr rate =%d. \n", param.isForceFreeRun?"ON":"OFF", param.fr_rate);
	ret = resource_mgr_ioctl( DE_IOW_SET_FR_RATE, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	enable multi windows mode for 60Hz mode(PDP)
 *
 */
int de_kwrap_setmultiwinenable(BOOLEAN isEnable)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	_g_de_IsMultiWin = isEnable;

	DE_NOTI("de_kwrap_setmultiwinenable %d\n", isEnable);
	ret = resource_mgr_ioctl( DE_IOW_MULTI_WIN_ENABLE, (unsigned long)&isEnable,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get  multi windows enable info
 *
 */
int de_kwrap_getmultiwinenable(BOOLEAN *isEnable)
{
	int ret = RET_OK;
	LX_DE_SRC_STATUS_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(isEnable);

	//DE_LOCK();
	//DE_TRACE_BEGI
	param.status_type = LX_DE_SRC_STATUS_OPER;

	ret = resource_mgr_ioctl( DE_IOR_GET_SRC_STATUS, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );
	DE_NOTI("[de_kwrap] operType = %d (_g_de_IsMultiWin=%d) \n\n", param.operType, _g_de_IsMultiWin);

	*isEnable = _g_de_IsMultiWin;

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get MVI source colormetry information.
 *
 */
int de_kwrap_getmvicolorimetry(UINT8 wId, LX_DE_COLOR_STD_T *colorimetry)
{
	int ret = RET_ERROR;
	LX_DE_MVI_COLORIMETRY_T param = { 0, };

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(colorimetry);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param.win_id= wId;

	ret = resource_mgr_ioctl( DE_IOR_GET_MVI_COLORIMETRY, (unsigned long)&param,CALL_FROM_KERNEL);
	if ( ret < 0 )
	{
		DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
		*colorimetry = LX_DE_COLOR_601;
		DE_NOTI("[de_kwrap] return defaut 601 colorimetry \n");
		goto func_exit;
	}

	*colorimetry = param.colorimetry;

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	control to switch uart for mcu, which is only for debugging
 *
 */
int de_kwrap_setuart4mcu(BOOLEAN bUart4MCU)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_PRINT("[de_kwrap]SetUart4MCU %s\n", bUart4MCU?"ON":"OFF");
	ret = resource_mgr_ioctl( DE_IOW_SET_UART_FOR_MCU, (unsigned long)&bUart4MCU,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * set DE for support UD.
 * 0: OFF, 1: UD 2: UD Half.
 *
 */
int de_kwrap_setudmode(LX_DE_UD_CTRL_T udCtrl)
{
	int ret = RET_ERROR;
	BOOLEAN isUD = 0;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] SetUDMode off[0] On[1] Half[2] = %d \n", udCtrl);

	isUD = (BOOLEAN)udCtrl;
	ret = resource_mgr_ioctl( DE_IOW_SET_UD_MODE, (unsigned long)&isUD,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

	_g_de_IsUD = udCtrl;

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * get DE for support UD.
 * 0: OFF, 1: UD 2: UD Half.
 *
 */
int de_kwrap_getudmode(LX_DE_UD_CTRL_T *isUD)
{
	int ret = RET_OK;
	LX_DE_SRC_STATUS_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(isUD);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param.status_type = LX_DE_SRC_STATUS_OPER;

	ret = resource_mgr_ioctl( DE_IOR_GET_SRC_STATUS, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

	if (param.operType == LX_DE_OPER_UD)
		*isUD = param.operCtrlFlag;
	else
		*isUD = _g_de_IsUD;

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set de CVE parameter.
 *	CVE path: select source of DENC w/ OSD or w/o OSD.
 *	CVE standard: timing of NTSC/PAL/SECAM category
 *
 */
int de_kwrap_setcve(LX_DE_CVE_PATH_T path, LX_DE_CVE_TIMING_T standard)
{
	int ret = RET_ERROR;
	LX_DE_CVE_PARAM_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param.fb = path;
	param.std = standard;

	ret = resource_mgr_ioctl( DE_IOW_SET_CVE, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set de VCS parameter.
 *	index of IPC for VCS
 *	data of IPC for VCS
 *
 */
int de_kwrap_setvcs(UINT32 inx, UINT32 data)
{
	int ret = RET_ERROR;
	LX_DE_VCS_IPC_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param.inx = inx;
	param.data = data;

	ret = resource_mgr_ioctl( DE_IOW_SET_VCS, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	read chip register for test purpose
 *
 */
int de_kwrap_regrd(UINT32 addr, UINT32 *data)
{
	int ret = RET_ERROR;
	UINT32 io_data;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(data);

//	//DE_LOCK();
//	//DE_TRACE_BEGIN();

	io_data = addr;

//	if ( io_data > 0x2000 )
//		DE_ERROR("[de_kwrap]Out of DE reg. range.\n");

	ret = resource_mgr_ioctl( DE_IOR_REG_RD, (unsigned long)&io_data,CALL_FROM_KERNEL);
	if ( ret < 0 )
	{
		*data = 0xFFFFFFFF;
		DE_ERROR("[de_kwrap] %s : error in ioctl call.\n", __F__ );
		goto func_exit;
	}

	*data = io_data;

func_exit:

//	//DE_TRACE_END();
//	//DE_UNLOCK();

	return ret;
}

/**
 *	write chip register for test purpose
 *
 */
int de_kwrap_regwr(UINT32 addr, UINT32 data)
{
	int ret = RET_ERROR;
	LX_DE_REG_WR_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

//	//DE_LOCK();
//	//DE_TRACE_BEGIN();

//	if ( addr > 0x2000 )
//		DE_PRINT("[de_kwrap]Out of DE reg. range.\n");

	param.wr_addr = addr;
	param.wr_data = data;
	ret = resource_mgr_ioctl( DE_IOW_REG_WR, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap_regwr] %s : error in ioctl call.\n", __F__ );

func_exit:

//	//DE_TRACE_END();
//	//DE_UNLOCK();

	return ret;
}


/**
 *	get Sample Mode for HDMI.
 *
 */
int de_kwrap_gethdmisamplemode(UINT16 hActive, UINT16 vActive, UINT8 scanType, UINT8 *sample_mode)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(sample_mode);

//	//DE_LOCK();
//	//DE_TRACE_BEGIN();

	//* sh.myoung (2011.10.20) - L9B0
	//* Repetition info 유 : NORMAL SAMPLING 적용 하고 이 함수 호출 후 Repetition 정보 보고 DOUBLE SAMPLING 변경,  422 일 경우 CbCr FIR Filter 적용,  444일 경우 CbCr FIR Filter 미 적용.
	//* Repetition info 무 : NORMAL SAMPLING 적용 하고 422 일 경우 CbCr FIR Filter 적용,  444일 경우 CbCr FIR Filter 미 적용.
	//* QUAD SAMPLING : 422, 444일   경우 Y, CbCr FIR 둘다 적용

	if ( ((vActive == 576) && (scanType == LX_DE_INTERLACED )) ||
		((vActive == 480) && (scanType == LX_DE_INTERLACED )) ||
		((vActive == 288) && (scanType == LX_DE_PROGRESSIVE)) ||
		((vActive == 240) && (scanType == LX_DE_PROGRESSIVE)) )
	{
		if (hActive == 1440 )
		{
			*sample_mode = LX_DE_CVI_NORMAL_SAMPLING;
		}
		else if (hActive == 2880 )
		{
			*sample_mode = LX_DE_CVI_QUAD_SAMPLING;
		}
		else
		{
			*sample_mode = LX_DE_CVI_NORMAL_SAMPLING;
		}
	}
	else if ( ((vActive == 576) && (scanType == LX_DE_PROGRESSIVE)) ||
			((vActive == 480) && (scanType == LX_DE_PROGRESSIVE)) )
	{
		if (hActive == 1440 )
		{
			*sample_mode = LX_DE_CVI_NORMAL_SAMPLING;
		}
		else if (hActive == 2880 )
		{
			*sample_mode = LX_DE_CVI_QUAD_SAMPLING;
		}
		else
		{
			*sample_mode = LX_DE_CVI_NORMAL_SAMPLING;
		}
	}
	else
	{
		*sample_mode = LX_DE_CVI_NORMAL_SAMPLING;
	}

//	//DE_TRACE_END();
//	//DE_UNLOCK();

	return ret;
}

/**
 *	set dvr fmt ctrl
 *
 */
int de_kwrap_setdvrfmtctrl(UINT8 isOn, LX_DE_SCAN_T scan_type, UINT16 h_size, UINT16 v_size, UINT32 fr_rate)
{
	int ret = RET_ERROR;
	LX_DE_DVR_DISFMT_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	_g_de_dvrFmt.bOnOff = param.bOnOff = isOn;
	_g_de_dvrFmt.scan = param.scan = scan_type;
	_g_de_dvrFmt.h_size = param.h_size = h_size;
	_g_de_dvrFmt.v_size = param.v_size = v_size;
	_g_de_dvrFmt.fr_rate = param.fr_rate = fr_rate;

	DE_NOTI("de_kwrap_setdvrfmtctrl isOn %d, fr rate =%d h_size = %d, v_size = %d scan = %d\n",
								param.bOnOff, param.fr_rate, param.h_size, param.v_size, param.scan);

	ret = resource_mgr_ioctl( DE_IOW_SET_DVR_FMT_CTRL, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get dvr fmt ctrl
 *
 */
int de_kwrap_getdvrfmtctrl(LX_DE_DVR_DISFMT_T *dvr_param)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(dvr_param);

	dvr_param->bOnOff = _g_de_dvrFmt.bOnOff;
	dvr_param->scan = _g_de_dvrFmt.scan;
	dvr_param->h_size = _g_de_dvrFmt.h_size;
	dvr_param->v_size = _g_de_dvrFmt.v_size;
	dvr_param->fr_rate = _g_de_dvrFmt.fr_rate;

	return RET_OK;
}

/**
 *	de set sub scaler frame freeze in msc-r or subscaler path
 *
 */
int de_kwrap_setsubscalerfreeze(BOOLEAN isOn)
{
	int ret = RET_ERROR;
	BOOLEAN param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param = isOn;

	ret = resource_mgr_ioctl( DE_IOW_SET_SUB_SC_FREEZE, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );


func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * de z-order and alpha blending.
 */
int de_kwrap_getzorderandalphablending(LX_DE_ZLIST_T *param)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	param->enable =	_g_de_zlist.enable;
	param->z_list[0] = _g_de_zlist.z_list[0];
	param->z_list[1] = _g_de_zlist.z_list[1];
	param->alpha[0] = _g_de_zlist.alpha[0];
	param->alpha[1] = _g_de_zlist.alpha[1];

	return RET_OK;
}



/**
 * de z-order and alpha blending.
 */
int de_kwrap_setzorderandalphablending(LX_DE_ZLIST_T param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	if (param.z_list[0] == param.z_list[1] || param.z_list[0] > 1 || param.z_list[1] > 1 ||	param.alpha[0] > 255 || param.alpha[1] > 255)
	{
		ret = RET_INVALID_PARAMS;
		DE_ERROR("[de_kwrap] %s : Invalid parmas error .\n", __F__);
		goto func_exit;
	}

	_g_de_zlist.enable = param.enable;
	_g_de_zlist.z_list[0] = param.z_list[0];
	_g_de_zlist.z_list[1] = param.z_list[1];
	_g_de_zlist.alpha[0] = param.alpha[0];
	_g_de_zlist.alpha[1] = param.alpha[1];

	DE_NOTI("de_kwrap_setzorderandalphablending TOP z-order[win_id] = %d, BOTTOM z-order[win_id] = %d, enable = %d, Top alpha = %d, BOTTOM  alpha = %d \n",  \
		param.z_list[0], param.z_list[1], param.enable, param.alpha[0], param.alpha[1]);
	ret = resource_mgr_ioctl( DE_IOW_SET_ZLIST, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * workaround code for horizontal picture shaking on component 480i
 */
int de_kwrap_setadcsrcchangeflag(BOOLEAN enable)
{
	//CHECK_DE_FD(g_de_ctx.dev_fd);
	_g_de_IsADCSrcChange = enable;
	return 0;
}


/**
 * all workaround code
 */
int de_kwrap_setdbgctrl(LX_DE_SET_DBG_T param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	if(param.type == LX_DE_DBG_MUTE_DISABLE)
	{
		LX_DE_SET_WIN_BLANK_T param_1;
		LX_DE_FIRMWARE_INFO_T fw_info;

		ret = de_kwrap_getfirmwareinfo(&fw_info);
		if(0)//fw_info.version < 7432)
		{
			DE_PRINT("Not supported function - Local mute control (enable/disable)\n");
			ret = RET_ERROR;
			goto func_exit;
		}

		memset(&param_1, 0, sizeof(LX_DE_SET_WIN_BLANK_T));
		param_1.bEnable = 0;    // mute off
		if(param.u32Param == 0)      // enable local mute
			param_1.isRGB = 4;     // b'100
		else if(param.u32Param == 1) // disable local mute
			param_1.isRGB = 6;     // b'110
		ret = resource_mgr_ioctl( DE_IOW_SET_WIN_BLANK, (unsigned long)&param_1,CALL_FROM_KERNEL);
	}
	else
	{
		ret = resource_mgr_ioctl( DE_IOW_SET_DBG, (unsigned long)&param,CALL_FROM_KERNEL);
	}
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * de get Low delay mode for frame delay.
 */
int de_kwrap_getlowdelaymode(LX_DE_LOW_DELAY_T *param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOR_GET_LOW_DELAY, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	de set Multi Vision
 *
 */
int de_kwrap_setmultivision(UINT16 w_block, UINT16 h_block, UINT16 x, UINT16 y)
{
	int ret = RET_OK;

	return ret;
}

/**
 *	control Internal modules
 *
 */
int de_kwrap_setifconfig(LX_DE_IF_CONFIG_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] Set  flags(%d) display (%d) Mirror(%d) FRC(%d) 3D(%d) \n", \
		param->config_type, param->display_type, param->display_mirror, param->frc_type, param->trid_type);

	ret = resource_mgr_ioctl( DE_IOW_SET_IF_CONFIG, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set 3D input/output control
 *
 */
int de_kwrap_3dinoutctrl(LX_DE_3D_INOUT_CTRL_T *param)
{
	int ret = RET_OK;
	LX_DE_3D_INOUT_CTRL_T 	de_3DInfo = {0xff, 0xff, 0xff, 0xff, 0xff};

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	/* 20110723, sj.youm, 0xff가 내려올 경우엔 f/w에서 처리하지 않으므로 변수 update 안함. */
	if (param->run_mode<LX_DE_3D_RUNMODE_MAX)
		de_3DInfo.run_mode = param->run_mode;

	if (param->in_img_fmt<LX_DE_3D_IMG_IN_MAX)
		de_3DInfo.in_img_fmt = param->in_img_fmt;

	if (param->in_lr_order<LX_DE_3D_LR_ORDER_MAX)
		de_3DInfo.in_lr_order = param->in_lr_order;

	if (param->out_img_fmt<LX_DE_3D_IMG_OUT_MAX)
		de_3DInfo.out_img_fmt = param->out_img_fmt;

	if (param->out_lr_order<LX_DE_3D_LR_ORDER_MAX)
		de_3DInfo.out_lr_order = param->out_lr_order;

	_g_de_Is3D.run_mode = param->run_mode;

	DE_NOTI("[de_kwrap] 3DInOutCtrl run[%d] in_fmt[%d] out_fmt[%d] out_lr[%d]\n", \
		param->run_mode, param->in_img_fmt, param->out_img_fmt, param->out_lr_order);

	ret = resource_mgr_ioctl( DE_IOW_SET_3D_INOUT_CTRL, (unsigned long)&de_3DInfo,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	Get System status
 *
 */
int de_kwrap_getsysstatus(LX_DE_SYS_STATUS_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOR_GET_SYS_STATUS, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	Set Operation( PIP, 3D, UD )
 *
 */
int de_kwrap_setoperation(LX_DE_OPERATION_CTRL_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOW_SET_OPERATION, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	Set Sub operation.
 *
 */
int de_kwrap_setsuboperation(LX_DE_SUB_OPERATION_CTRL_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOW_SET_SUB_OPERATION, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}



/**
 *	Get Video Sacler Info.
 *
 */
int de_kwrap_getscalerinfo(LX_DE_SCALER_INFO_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOR_GET_SCALER_INFO, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	Set Output mode
 *
 */
int de_kwrap_setoutputmode(LX_DE_OUTPUT_MODE_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOW_SET_OUTPUT_MODE, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	freeze function of windows
 *
 */
int de_kwrap_setwinfreeze(LX_DE_WIN_FREEZE_T *param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]set win freeze wid = %d isON = %d loc = %d\n",\
				param->win_id, param->bEnable, param->location);
	ret = resource_mgr_ioctl( DE_IOW_SET_WIN_FREEZE, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set source freeze function of windows
 *
 */
int de_kwrap_setsrcmirror(LX_DE_SRC_MIRROR_T param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] set source mirror : srcPort[%d] desport[%d] enable[%d]\n",\
				param.srcPort, param.destPort, param.enable);
	ret = resource_mgr_ioctl( DE_IOW_SET_SRC_MIRROR, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	set detecting actual format from specific pixel value
 *
 */
int de_kwrap_setactfmtdetect(LX_DE_ACT_FORMAT_T param)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] set actual format detect : enable[%d] \n",\
				param.enable);
	ret = resource_mgr_ioctl( DE_IOW_SET_ACT_FMT_DETECT, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

	memcpy(&_g_de_actFormat, &param, sizeof(LX_DE_ACT_FORMAT_T));

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	get detecting actual format from specific pixel value
 *
 */
int de_kwrap_getactfmtdetect(LX_DE_ACT_FORMAT_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	memcpy(param, &_g_de_actFormat, sizeof(LX_DE_ACT_FORMAT_T));

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

#if 1 // for fpga verification
int de_kwrap_clidbg(LX_DE_SET_EVAL_DBG_T param)
{
	int ret = RET_OK;

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOW_SET_EVAL_DBG, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();
	return ret;
}
int de_kwrap_getfd(void)
{
	return g_de_ctx.dev_fd;
}
#endif // #if 0

int de_kwrap_sethdmiport(UINT8 wId, UINT32 hdmi_port)
{
	int ret = RET_ERROR;
	LX_DE_HDMIPORT_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]set hdmi port(win_id %d, port %d).\n", wId, hdmi_port);

	if(wId >= LX_DE_WIN_MAX) goto func_exit;

	param.win_id   = wId;
	param.port_num = hdmi_port;
	_g_de_hdmi_phys[wId] = hdmi_port;

	ret = resource_mgr_ioctl( DE_IOW_SET_CVI_HDMIPORT, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_gethdmiport(UINT8 wId)
{
	if(wId >= LX_DE_WIN_MAX) return -1;
	return _g_de_hdmi_phys[wId];
}

int de_kwrap_setsubwindow(UINT8 wId)
{
	int ret = RET_ERROR;
	LX_DE_SET_SUB_WIN_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] set sub window id (win_id %d).\n", wId);

	param.win_id   = wId;

	ret = resource_mgr_ioctl( DE_IOW_SET_SUB_WIN, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_setdelaybuffer(UINT32 vpSrcId, UINT8 ubuffer)
{
	int ret = RET_ERROR;
	LX_DE_SET_DELAY_BUFFER_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] set delay (wId %d , buffer %d.\n", vpSrcId, ubuffer);

	param.win_id = vpSrcId;
	param.ubuffer = ubuffer;

	ret = resource_mgr_ioctl( DE_IOW_SET_FRAME_DELAY, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}


int de_kwrap_setsubwinmode(LX_DE_SUB_MODE_T sub_mode)
{
	int ret = RET_ERROR;
	LX_DE_SUB_MODE_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] set sub window mode ( %d).\n", sub_mode);

	param = sub_mode;

	ret = resource_mgr_ioctl( DE_IOW_SET_SUB_MODE, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_getsubwinmode(LX_DE_SUB_MODE_T *param)
{
	int ret = RET_OK;

	//CHECK_DE_FD(g_de_ctx.dev_fd);
	CHECK_NULL(param);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	ret = resource_mgr_ioctl( DE_IOW_GET_SUB_MODE, (unsigned long)param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_setsubwinshape(LX_DE_SUB_MGF_SHAPE_T sub_shape, LX_DE_RECT_T orgWin)
{
	int ret = RET_ERROR;
	LX_DE_SUB_SHAPE_T param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap] set sub window shape & org size w/h ( %d & w/h %d/%d).\n", sub_shape, orgWin.w, orgWin.h);

	param.sub_shape = sub_shape;
	param.org_win.w = orgWin.w;
	param.org_win.h = orgWin.h;
	param.org_win.x = orgWin.x;
	param.org_win.y = orgWin.y;

	ret = resource_mgr_ioctl( DE_IOW_SET_SUB_SHAPE, (unsigned long)&param,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	Set signage mode on/off  (concurrent video output thru hdmi-tx)
 *
 */
int de_kwrap_setsignagemode(BOOLEAN isEnable)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]SetSignageMode %d\n", isEnable);
	ret = resource_mgr_ioctl( DE_IOW_SET_SIGNAGE_MODE, (unsigned long)&isEnable,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 *	Set hdmitx clock & resolutions
 *
 */
int de_kwrap_sethdmitxinfo(LX_DE_HDMITX_OUTPUT_INFO_T  hdmitx_info)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]KWRAP_DE_SetHDMITXInfo width=%d height=%d frate=%d\n", hdmitx_info.width, hdmitx_info.height, hdmitx_info.frate);
	ret = resource_mgr_ioctl( DE_IOW_SET_HDMITX_INFO, (unsigned long)&hdmitx_info,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_setsourcesizewin(UINT8 wId, LX_DE_RECT_T *inSize, LX_DE_RECT_T *inWin)
{
	int ret = RET_ERROR;
	LX_DE_SOURCE_SIZE_WIN_T src_size_info;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	src_size_info.win_id = wId;
	memcpy(&src_size_info.inSize, inSize, sizeof(LX_DE_RECT_T));
	memcpy(&src_size_info.inWin, inWin, sizeof(LX_DE_RECT_T));

	DE_NOTI("[de_kwrap]KWRAP_DE_SetSourceSizeWin win[%d] src size(%d/%d/%d/%d) in win(%d/%d/%d/%d)\n", \
		wId, inSize->x, inSize->y, inSize->w, inSize->h, inWin->x, inWin->y, inWin->w, inWin->h);
	ret = resource_mgr_ioctl( DE_IOW_SET_SRC_SIZE, (unsigned long)&src_size_info,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_getsourcesizewin(UINT8 wId, LX_DE_RECT_T *inSize)
{
	int ret = RET_ERROR;
	LX_DE_SOURCE_SIZE_WIN_T src_size_info;
	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	src_size_info.win_id = wId;
	memset(&src_size_info.inSize, 0x0, sizeof(LX_DE_RECT_T));
	memset(&src_size_info.inWin, 0x0, sizeof(LX_DE_RECT_T));

	ret = resource_mgr_ioctl( DE_IOR_GET_SRC_SIZE, &src_size_info,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );
	DE_NOTI("[de_kwrap]KWRAP_DE_GetSourceSizeWin win[%d] src size(%d/%d/%d/%d) in win(%d/%d/%d/%d)\n", \
		wId, src_size_info.inSize.x, src_size_info.inSize.y, src_size_info.inSize.w, src_size_info.inSize.h, src_size_info.inWin.x, src_size_info.inWin.y, src_size_info.inWin.w, src_size_info.inWin.h);
	memcpy(inSize, &src_size_info.inSize, sizeof(LX_DE_RECT_T));

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_set4kdualmode(BOOLEAN bOnOff)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	_g_4k_dual_mode = bOnOff;
	DE_NOTI("[de_kwrap]KWRAP_DE_Set4kDualMode = %d\n", bOnOff);
	ret = resource_mgr_ioctl( DE_IOW_DUAL_MODE_ENABLE, (unsigned long)&bOnOff,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_setlowdelaybysourcesync(UINT32 uLowDelay)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]KWRAP_DE_SetLowDelay = %d\n", uLowDelay);
	ret = resource_mgr_ioctl( DE_IOW_SET_SRC_SYNC_LOW_DELAY, (unsigned long)&uLowDelay,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_sethighframerate(UINT32 uHfr)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]KWRAP_DE_SetHighFrameRate = %d\n", uHfr);
	ret = resource_mgr_ioctl( DE_IOW_SET_HIGH_FRAME_RATE, (unsigned long)&uHfr,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_setrotate(LX_DE_ROTATE_INFO_T rotate)
{
	int ret = RET_ERROR;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]KWRAP_DE_SetRotate = %d\n", rotate);
	ret = resource_mgr_ioctl( DE_IOW_SET_ROTATE, (unsigned long)&rotate,CALL_FROM_KERNEL);
	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

__attribute__((unused)) static UINT32 *virt_fpp = NULL;
#define	FPP_SHARING_BUF_SIZE	(32*1024)

int de_kwrap_fpp_initialize(int bv_need, UINT32 **base, UINT32 *size)
{
	int ret = RET_ERROR;
	UINT32 param;
	struct fpp_bv_structure *fpp_bv;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param = TRUE;

	ret = resource_mgr_ioctl( DE_IOW_GET_FPP_INFO, (unsigned long)&param,CALL_FROM_KERNEL);
#if 0
	virt_fpp = (UINT32 *)mmap(	NULL,                             \
								FPP_SHARING_BUF_SIZE,\
								PROT_READ|PROT_WRITE, MAP_SHARED, \
								g_de_ctx.dev_fd,         \
								param);
#else
	virt_fpp = ioremap(param,FPP_SHARING_BUF_SIZE);
#endif

	fpp_bv  = (struct fpp_bv_structure *)virt_fpp;
	fpp_bv->bv_need = bv_need;
	fpp_bv->enable = 1;

	*base = virt_fpp;
	*size = sizeof(struct fpp_bv_structure);

	// waiting for DE FW setting time.
	// DE FW will check 'enable' flag every SYNC, so waiting for 10ms
	msleep(10000);

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_fpp_finalize(void)
{
	int ret = RET_ERROR;
	UINT32 param;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	param = FALSE;

	ret = resource_mgr_ioctl( DE_IOW_GET_FPP_INFO, (unsigned long)&param,CALL_FROM_KERNEL);

	if(virt_fpp)
	{
		struct fpp_bv_structure *fpp_bv;
		fpp_bv  = (struct fpp_bv_structure *)virt_fpp;
		fpp_bv->bv_need = 0;
		fpp_bv->enable = 0;
//		munmap((void *)virt_fpp, FPP_SHARING_BUF_SIZE);
		iounmap((void *)virt_fpp);
		virt_fpp = NULL;
	}

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_getcapturebufferinfo(UINT32 *vt0_base, UINT32 *vt0_size, UINT32 *vt1_base, UINT32 *vt1_size)
{
	int ret = RET_ERROR;
	LX_DE_IPC_SYSTEM_NEW_T stParams;

	//CHECK_DE_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[de_kwrap]KWRAP_DE_GetCaptureBufferInfo\n");
	//ret = resource_mgr_ioctl( DE_IOR_GET_MEM_INFO, &stParams);
	ret = resource_mgr_ioctl(DE_IOR_GET_MEM_INFO,(unsigned long)&stParams,CALL_FROM_KERNEL);

	*vt0_base = stParams.de_vt_m1.base;
	*vt0_size = stParams.de_vt_m1.size;
	*vt1_base = stParams.de_vt_m2.base;
	*vt1_size = stParams.de_vt_m2.size;

	DE_CHECK_CODE( ret<0, goto func_exit, "[de_kwrap] %s : error in ioctl call.\n", __F__ );

func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}
#endif

