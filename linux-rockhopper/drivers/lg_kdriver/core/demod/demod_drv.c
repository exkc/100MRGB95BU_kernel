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
 *  main driver implementation for demod device.
 *	demod device will teach you how to make device driver with new platform.
 *
 *  author		jeongpil.yun (jeongpil.yun@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#define DEMOD_TAG "[CORE.DRV] "

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_DEMOD_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "os_util.h"
//#include "base_dev_cfg.h"
#include "base_device.h"

#include "demod_module.h"

#include "demod_impl.h"
#include "demod_drv.h"

#include "demod_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/**
 *	main control block for demod device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
	dev_t		devno;			///< device number
	struct cdev	cdev;			///< char device structure
	//OS_SEM_T	sem;
	struct mutex mtx;
	int			opencnt;
}
DEMOD_DEVICE_T;

UINT8 *ui8DemodPrintColor[8] = {
			"COLOR_BLACK",
			"COLOR_RED",
			"COLOR_GREEN",
			"COLOR_YELLOW",
			"COLOR_BLUE",
			"COLOR_PURPLE",
			"COLOR_CYAN",
			"COLOR_GRAY",
};

#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}DEMOD_DRVDATA_T;


#endif
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#if 0
extern	void	DEMOD_PROC_Init(void);
extern	void	DEMOD_PROC_Cleanup(void);
#endif


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		DEMOD_Init(void);
void	DEMOD_Cleanup(void);

static void DEMOD_CLR_Device_Data(void);
//static void DEMOD_Mutex_Init (struct mutex * mtx);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int	g_demod_debug_fd;
EXPORT_SYMBOL(g_demod_debug_fd);

int 	g_demod_major = DEMOD_MAJOR;
int 	g_demod_minor = DEMOD_MINOR;
int    	g_demod_trace_depth;

BOOLEAN _g_print_enb = TRUE;

BOOLEAN _gExecuteHwRest_gbb = FALSE;

BOOLEAN _gIsOpen = FALSE;
BOOLEAN _gIsFWDn = FALSE;
BOOLEAN _gIs_ioremap = FALSE;

extern BOOLEAN		gPanama;

UINT8	_gSelplp = 0;

/* demod context */
DEMOD_CTX_T	g_demod_ctx_info[DEMOD_MAX_DEVICE];
EXPORT_SYMBOL(g_demod_ctx_info);

void DEMOD_CLR_CTX ()
{
	int i;
	memset(&g_demod_ctx_info[0], 0, sizeof(DEMOD_CTX_T) * DEMOD_MAX_DEVICE);
	for (i = 0; i < DEMOD_MAX_DEVICE; i++)
		g_demod_ctx_info[i].operMode = LX_DEMOD_DVBT;
}
EXPORT_SYMBOL(DEMOD_CLR_CTX);

DEMOD_CTX_T * DEMOD_Get_CTX (int devno)
{
	return &g_demod_ctx_info[(devno < DEMOD_MAX_DEVICE) ? devno : 0];
}
EXPORT_SYMBOL(DEMOD_Get_CTX);

/* demod device data */
static DEMOD_DEV_T g_demod_dev_data;


void DEMOD_CLR_Device_Data(void) {
	memset(&g_demod_dev_data, 0, sizeof(DEMOD_DEV_T));
}

DEMOD_DEV_T * DEMOD_Get_Device_Data(void) {
	return &g_demod_dev_data;
}

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int		DEMOD_Open(struct inode *, struct file *);
static int		DEMOD_Close(struct inode *, struct file *);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int		DEMOD_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long		DEMOD_Ioctl (struct file *, unsigned int, unsigned long );
#ifdef CONFIG_COMPAT
static long		DEMOD_CompatIoctl (struct file *, unsigned int, unsigned long );
#endif
#endif


#ifdef SUPPORT_DEMOD_DEVICE_READ_WRITE_FOPS
static ssize_t  DEMOD_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  DEMOD_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for demod device
*/
static DEMOD_DEVICE_T*		g_demod_device = NULL;

static UINT32 _get_system_time (void) {
	return (UINT32)jiffies_to_msecs(jiffies);
}

static UINT32 _check_spend_time (UINT32 start_time) {
	UINT32 current_time = _get_system_time();
	UINT32 spend_time = 0;

	if (current_time >= start_time) {
		spend_time = current_time - start_time;
	} else {
		spend_time = current_time + (UINT_MAX - start_time);
	}

	DEMOD_DEBUG("start %u, current %u, spend %u\n", start_time, current_time, spend_time);
	return spend_time;
}

/** lock demod device */
typedef struct {
	int cnt;
	int pid;
	const char * file;
	int line;
} lock_info_t;

static volatile lock_info_t _lock_info;

int DEMOD_Mutex_Lock (const char * path, int line)
{
	int retry = 10;
	int ret = RET_OK;

	char * file = strrchr(path, '/');

	UINT32 start_time;
	UINT32 spend_time;

	int check_cnt = 0;

	struct mutex * mtx =  &g_demod_device->mtx;

	start_time = _get_system_time();

	if(_lock_info.cnt != 0) {
		DEMOD_INFO("wait" ", cnt %d, cur pid %d, %s:%d, req pid %d, %s:%d\n",
							_lock_info.cnt,	_lock_info.pid, _lock_info.file, _lock_info.line,
							 current->pid, file, line);
		check_cnt = _lock_info.cnt;
	}

	do {
		ret = mutex_lock_interruptible(mtx);
	} while ((ret != RET_OK) && retry--);

	spend_time = _check_spend_time(start_time);

	if (check_cnt) {
		DEMOD_INFO("wait done, spend %ums" ", cnt %d->%d, cur pid %d, %s:%d, req pid %d, %s:%d\n", spend_time,
							check_cnt, _lock_info.cnt,	_lock_info.pid, _lock_info.file, _lock_info.line,
							 current->pid, file, line);
	}

	if (ret != RET_OK) {
		DEMOD_ERROR("failed get mutex lock, ret %d, spend %u, retry %d" ", cnt %d, cur pid %d, %s:%d, req pid %d, %s:%d\n",
							ret, spend_time, retry,
							_lock_info.cnt,	_lock_info.pid, _lock_info.file, _lock_info.line,
							 current->pid, file, line);
		dump_stack();
		return ret;
	}

	if(_lock_info.cnt != 0) {
		DEMOD_ERROR("invalid lockcnt" ", cnt %d, cur pid %d, %s:%d, req pid %d, %s:%d\n",
							_lock_info.cnt,	_lock_info.pid, _lock_info.file, _lock_info.line,
							 current->pid, file, line);
		dump_stack();
	}

	_lock_info.pid = current->pid;
	_lock_info.file = file;
	_lock_info.line = line;
	_lock_info.cnt++;

	return ret;
}

/** unlock demod device */
void DEMOD_Mutex_Unlock (const char * path, int line)
{
	struct mutex * mtx = &g_demod_device->mtx;

	char * file = strrchr(path, '/');

	_lock_info.cnt--;

	if(_lock_info.cnt != 0) {
		DEMOD_ERROR("invalid lockcnt" ", cnt %d, cur pid %d, %s:%d, req pid %d, %s:%d\n",
							_lock_info.cnt,	_lock_info.pid, _lock_info.file, _lock_info.line,
							 current->pid, file, line);
		dump_stack();
		return;
	}

	_lock_info.pid = 0;
	_lock_info.file = NULL;
	_lock_info.line = 0;
	mutex_unlock(mtx);
}

#if 0
/** init mutex */
void DEMOD_Mutex_Init (struct mutex * mtx)
{
	mutex_init(&g_demod_device->mtx);
}
#endif


/* kthread for DEMOD TASK */
struct task_struct 	*g_pstDemodTuningTask = NULL;

void DEMOD_TASK_Open(void)
{
	DEMOD_LockDevice_NoRet();
	_gIsOpen 	= FALSE;
	g_demod_device->opencnt++;

	if(NULL == g_pstDemodTuningTask) {
		//Create thread for DEMOD module
		g_pstDemodTuningTask = kthread_create(DEMOD_Tuning_Task, (void*)NULL, "DEMODTASK");

		if (NULL == g_pstDemodTuningTask) {
			DEMOD_ERROR("failed to create DEMOD_TASK\n");
		} else {
			wake_up_process(g_pstDemodTuningTask);
			DEMOD_INFO("success to create DEMOD_TASK\n");
		}
	} else {
		DEMOD_INFO("DEMOD_TASK already created");
	}

	_gIsOpen = TRUE;
	DEMOD_UnlockDevice();

	DEMOD_NOTI("TASK_Open done, task %p, OpenCount %d\n", g_pstDemodTuningTask, g_demod_device->opencnt);
}

void DEMOD_TASK_Close(void)
{
	DEMOD_LockDevice_NoRet();
	if (g_demod_device->opencnt > 0)
	{
		-- g_demod_device->opencnt;
	}

	if (g_demod_device->opencnt == 0) {
		_gIsOpen   = FALSE;
		if(g_pstDemodTuningTask) {
			DEMOD_WakeUpTask();
			kthread_stop(g_pstDemodTuningTask);
			g_pstDemodTuningTask = NULL;
			DEMOD_NOTI("stop DEMOD_TASK done\n");
		}
	}
	DEMOD_UnlockDevice();
}

int DEMOD_TASK_OpenCount(void) {
	return g_demod_device->opencnt;
}

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int DEMOD_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef KDRV_CONFIG_PM_DEMOD

	DEMOD_DRVDATA_T *drv_data;
	DEMOD_DEV_T	*pDemodDev;

	printk(KERN_NOTICE "DEMOD - suspend BEGIN\n");

	pDemodDev = DEMOD_Get_Device_Data();
	if ((DEMOD_SW_TYPE_NONE != pDemodDev->sw_type) && (FALSE == pDemodDev->power_save)) {
		DEMOD_Power_Save(TRUE);
	}

	drv_data = platform_get_drvdata(pdev);
	drv_data->is_suspended = 1;

#if defined(DEMOD_CONFIG_IPC)
	DEMOD_IPC_Enable(FALSE);
	DEMOD_INFO("DEMOD_IPC is disabled\n");
#endif

	DEMOD_API_Suspend();
	_gIsFWDn	= FALSE;
	_gIs_ioremap 	= FALSE;
	DEMOD_INFO("suspend done, sw_type 0x%x, fwdn %d, ioremap %d\n", pDemodDev->sw_type, _gIsFWDn, _gIs_ioremap);

	printk(KERN_NOTICE "DEMOD - suspend END\n");
#endif
	return 0;
}


/**
 *
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int DEMOD_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_DEMOD
	DEMOD_DRVDATA_T 		*drv_data;
	DEMOD_CTX_T 			*pDemodInfo;
	DEMOD_DEV_T			*pDemodDev;

	printk(KERN_NOTICE "DEMOD - resume BEGIN\n");

	_gIsFWDn 	= FALSE;
	_gIs_ioremap 	= FALSE;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0)
	{
		printk(KERN_ERR "DEMOD - resume FAIL (is_suspended %d)\n", drv_data->is_suspended);
		return -1;
	}

	DEMOD_InitHW();

	pDemodInfo = DEMOD_Get_CTX(0);
	pDemodDev = DEMOD_Get_Device_Data();

	DEMOD_NOTI("resume check, fwdn[%d], ioremap[%d], panama[%d], sw_type[%d], mem_alloc[%d]\n", _gIsFWDn, _gIs_ioremap, gPanama, pDemodDev->sw_type, pDemodDev->mem_alloc);

#ifdef INCLUDE_O18_CHIP_KDRV
	if (lx_chip() == LX_CHIP_O18)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_ATSC_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DVB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
			{
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DTMB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}

			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_PRINT("FAIL, DEMOD_FW_Initialize() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
	}
#endif

#ifdef INCLUDE_M19_CHIP_KDRV
	if (lx_chip() == LX_CHIP_M19)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_ATSC_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DVB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			
			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_PRINT("FAIL, DEMOD_FW_Initialize() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			pDemodInfo->operMode = LX_DEMOD_DVBT;

		}
	}
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
	if (lx_chip() == LX_CHIP_O20)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_ATSC_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DVB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
			{
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DTMB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			
			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_PRINT("FAIL, DEMOD_FW_Initialize() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			pDemodInfo->operMode = LX_DEMOD_DVBT;
		}
	}
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
	if (lx_chip() == LX_CHIP_E60)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_ATSC_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DVB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			else if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
			{
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_PRINT("FAIL, DEMOD_DTMB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			
			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_PRINT("FAIL, DEMOD_FW_Initialize() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			pDemodInfo->operMode = LX_DEMOD_DVBT;

		}
	}
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
	if (lx_chip() == LX_CHIP_O22)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_ATSC_SW_Init)\n");
					return -1;
				}
			}
			if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_DVB_SW_Init)\n");
					return -1;
				}
			}
			if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
			{
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_DTMB_SW_Init)\n");
					return -1;
				}
			}
			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_ERROR("resume failed (DEMOD_FW_Initialize)\n");
				return -1;
			}
			pDemodInfo->operMode = LX_DEMOD_DVBT;

		}

	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	if (lx_chip() == LX_CHIP_M23)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_ATSC_SW_Init)\n");
					return -1;
				}
			}
			if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_DVB_SW_Init)\n");
					return -1;
				}
			}
			if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
			{
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_DTMB_SW_Init)\n");
					return -1;
				}
			}
			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_ERROR("resume failed (DEMOD_FW_Initialize)\n");
				return -1;
			}
			pDemodInfo->operMode = LX_DEMOD_DVBT;

		}
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV //!//
	if (lx_chip() == LX_CHIP_O24)
	{
		if(_gIsOpen == TRUE)
		{
			if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
			{
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_ATSC_SW_Init)\n");
					return -1;
				}
			}
			if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
			{
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_DVB_SW_Init)\n");
					return -1;
				}
			}
			if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
			{
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_ERROR("resume failed (DEMOD_DTMB_SW_Init)\n");
					return -1;
				}
			}
			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_ERROR("resume failed (DEMOD_FW_Initialize)\n");
				return -1;
			}
			pDemodInfo->operMode = LX_DEMOD_DVBT;

		}
	}
#endif
#ifdef INCLUDE_O26_CHIP_KDRV //!//
		if (lx_chip() == LX_CHIP_O26)
		{
			if(_gIsOpen == TRUE)
			{
				if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)
				{
					if(RET_OK != DEMOD_ATSC_SW_Init())
					{
						DEMOD_ERROR("resume failed (DEMOD_ATSC_SW_Init)\n");
						return -1;
					}
				}
				if(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)
				{
					if(RET_OK != DEMOD_DVB_SW_Init())
					{
						DEMOD_ERROR("resume failed (DEMOD_DVB_SW_Init)\n");
						return -1;
					}
				}
				if(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)
				{
					if(RET_OK != DEMOD_DTMB_SW_Init())
					{
						DEMOD_ERROR("resume failed (DEMOD_DTMB_SW_Init)\n");
						return -1;
					}
				}
				if(RET_OK != DEMOD_FW_Initialize())
				{
					DEMOD_ERROR("resume failed (DEMOD_FW_Initialize)\n");
					return -1;
				}
				pDemodInfo->operMode = LX_DEMOD_DVBT;
	
			}
		}
#endif

	drv_data->is_suspended = 0;
	DEMOD_INFO("resume END, qsm %d, is_suspended %d\n", pDemodInfo->instantBoot, drv_data->is_suspended);
	printk(KERN_NOTICE "DEMOD - resume END\n");
#endif
	return 0;
}
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int DEMOD_probe(struct platform_device *pdev)
#else
static int __init DEMOD_probe(struct platform_device *pdev)
#endif
{

	DEMOD_DRVDATA_T *drv_data;

	drv_data = (DEMOD_DRVDATA_T *)kmalloc(sizeof(DEMOD_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	DEMOD_PRINT("[%s] done probe\n", DEMOD_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function. this function will be called in rmmod fbdev module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void DEMOD_remove (struct platform_device *pdev)
#else
static int DEMOD_remove (struct platform_device *pdev)
#endif
{
	DEMOD_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	DEMOD_PRINT("released\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif

}

/**
 *
 * module release function. this function will be called in rmmod module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void DEMOD_release (struct device *dev)
{
	DEMOD_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver demod_driver =
{
	.probe          	= DEMOD_probe,
	.suspend        	= DEMOD_suspend,
	.remove        		= DEMOD_remove,
	.resume         	= DEMOD_resume,
	.driver         	=
	{
		.name   = DEMOD_MODULE,
	},
};

static struct platform_device demod_device = {
	.name 		= DEMOD_MODULE,
	.id 		= 0,
	.id 		= -1,
	.dev 		=
	{
		.release = DEMOD_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void DEMOD_PreInit (void)
{
	DEMOD_SetupMemMap();
}

static void DEMOD_ShowConfig (void)
{
	char init_msg[64];
	int idx = 0;

#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
#if defined(CHIP_NAME_m19)
	idx += sprintf(init_msg + idx, "M19 / ");
#elif defined(CHIP_NAME_o20)
	idx += sprintf(init_msg + idx, "O20 / ");
#elif defined(CHIP_NAME_e60)
	idx += sprintf(init_msg + idx, "E60 / ");
#elif defined(CHIP_NAME_o22)
	idx += sprintf(init_msg + idx, "O22 / ");
#elif defined(CHIP_NAME_m23)
	idx += sprintf(init_msg + idx, "M23 / ");
#elif defined(CHIP_NAME_o24) //!//
	idx += sprintf(init_msg + idx, "O24 / ");
#elif defined(CHIP_NAME_o26) //chungiii
		idx += sprintf(init_msg + idx, "O26 / ");
#else
	idx += sprintf(init_msg + idx, "??? / ", );
#endif
#endif

#if defined(DEMOD_CHIP_NAME_m19)
	idx += sprintf(init_msg + idx, "M19, ");
#elif defined(DEMOD_CHIP_NAME_o20)
	idx += sprintf(init_msg + idx, "O20, ");
#elif defined(DEMOD_CHIP_NAME_e60)
	idx += sprintf(init_msg + idx, "E60, ");
#elif defined(CHIP_NAME_o22)
	idx += sprintf(init_msg + idx, "O22, ");
#elif defined(CHIP_NAME_m23)
	idx += sprintf(init_msg + idx, "M23, ");
#elif defined(CHIP_NAME_o24) //!//
	idx += sprintf(init_msg + idx, "O24, ");
#elif defined(CHIP_NAME_o26) //chungiii
	idx += sprintf(init_msg + idx, "O26, ");
#else
	idx += sprintf(init_msg + idx, "???, ");
#endif

#if defined(DEMOD_CONFIG_EXT)
	idx += sprintf(init_msg + idx, "External, ");
#endif
#if defined(DEMOD_CONFIG_SOC)
	idx += sprintf(init_msg + idx, "SoC, ");
#endif
#if defined(DEMOD_CONFIG_IPC)
	idx += sprintf(init_msg + idx, "IPC, ");
#if defined(DEMOD_CONFIG_IPC_RETRANSMIT)
	idx += sprintf(init_msg + idx, "RETX, ");
#endif
#endif
#if defined(DEMOD_CONFIG_DDR)
	idx += sprintf(init_msg + idx, "DDR, ");
#endif

	init_msg[idx - 1] = '\0';

	DEMOD_INFO("[CONFIG] %s\n", init_msg);
}

/**
 * file I/O description for demod device
 *
*/
static struct file_operations g_demod_fops =
{
	.open 			= DEMOD_Open,
	.release		= DEMOD_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl			= DEMOD_Ioctl,
#else
	.unlocked_ioctl	= DEMOD_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= DEMOD_CompatIoctl,
#endif
#endif
#ifdef SUPPORT_DEMOD_DEVICE_READ_WRITE_FOPS
	.read 			= DEMOD_Read,
	.write 			= DEMOD_Write,
#else
	.read			= NULL,
	.write			= NULL,
#endif
};

int DEMOD_Init (void)
{
	int		i;
	int		err;
	dev_t		dev;

	/* Get the handle of debug output for demod device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_demod_debug_fd = DBG_OPEN( DEMOD_MODULE );

	if(g_demod_debug_fd < 0)
	{
		return -1;
	}

	/* debug level set default */
	DEMOD_Set_Debug_Level(0);

	_g_print_enb = TRUE;

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&demod_driver) < 0)
	{
		DEMOD_PRINT_ALWAYS("[%s] platform driver register failed\n",DEMOD_MODULE);
	} else {
		switch (lx_chip()) {
			case LX_CHIP_M23: {
				// M23 device will register by TE, for TE + DEMOD uni mcu
				DEMOD_INFO("skip device register for TE+DEMOD uni mcu\n");
			}
			break;
			default: {
				if(platform_device_register(&demod_device))
				{
					platform_driver_unregister(&demod_driver);
					DEMOD_PRINT_ALWAYS("[%s] platform device register failed\n",DEMOD_MODULE);
				}
				else
				{
					device_enable_async_suspend(&((&demod_device)->dev));
					DEMOD_PRINT_ALWAYS("[%s] platform register done\n", DEMOD_MODULE);
				}
			}
			break;
		}
	}
#endif
	g_demod_device = (DEMOD_DEVICE_T*)OS_KMalloc( sizeof(DEMOD_DEVICE_T)*DEMOD_MAX_DEVICE );

	if ( NULL == g_demod_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", (int)sizeof(DEMOD_DEVICE_T)* DEMOD_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_demod_device, 0x0, sizeof(DEMOD_DEVICE_T)* DEMOD_MAX_DEVICE );

	/* init Mutex for DEMOD_LoccDevice/DEMOD_UnlockDevice */
	//OS_InitMutex(&g_demod_device->sem, OS_SEM_ATTR_DEFAULT);
	mutex_init(&g_demod_device->mtx);

	if (g_demod_major)
	{
		dev 	= MKDEV( g_demod_major, g_demod_minor );
		err 	= register_chrdev_region(dev, DEMOD_MAX_DEVICE, DEMOD_MODULE );
	}
	else
	{
		err 	= alloc_chrdev_region(&dev, g_demod_minor, DEMOD_MAX_DEVICE, DEMOD_MODULE );
		g_demod_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register demod device\n" );
		return -EIO;
	}

	DEMOD_CLR_CTX();
	DEMOD_CLR_Device_Data();

	DEMOD_ShowConfig();

	/* initialize proc system */
	DEMOD_PROC_Init ( );

	/* TODO : initialize your module not specific minor device */
	DEMOD_InitHW();

#if defined(DEMOD_CONFIG_IPC)
	DEMOD_NOTI("####chungiii DEMOD_IPC_Init\n");
	DEMOD_IPC_Init();
#endif
	/* END */

	for ( i=0; i<DEMOD_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_demod_major, g_demod_minor+i );
		cdev_init( &(g_demod_device[i].cdev), &g_demod_fops );
		g_demod_device[i].devno			= dev;
		g_demod_device[i].cdev.owner 	= THIS_MODULE;
		g_demod_device[i].cdev.ops   		= &g_demod_fops;

		/* TODO: initialize minor device */

		/* END */
		err = cdev_add (&(g_demod_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding demod device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_demod_device[i].devno, "%s%d", DEMOD_MODULE, i );
	}

	DEMOD_PRINT_ALWAYS("demod device initialized\n");

	return 0;
}

void DEMOD_Cleanup(void)
{
	int 	i;
	dev_t dev = MKDEV( g_demod_major, g_demod_minor );

	DEMOD_Reg_Close();
	DEMOD_NOTI("DEMOD_Reg_Close done\n");

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&demod_driver);
	platform_device_unregister(&demod_device);
#endif

	/* cleanup proc system */
	DEMOD_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<DEMOD_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */
		/* END */
		cdev_del( &(g_demod_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, DEMOD_MAX_DEVICE );

	OS_Free( g_demod_device );
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for demod device
 *
 */
static int DEMOD_Open(struct inode *inode, struct file *filp)
{
    int				major,minor;
    struct cdev*    		cdev;
    DEMOD_DEVICE_T*	my_dev;

    cdev		= inode->i_cdev;
    my_dev	= container_of ( cdev, DEMOD_DEVICE_T, cdev);

    DEMOD_NOTI("demod device opened start\n" );

    DEMOD_TASK_Open();

    filp->private_data = my_dev;

    major = imajor(inode);
    minor = iminor(inode);
    DEMOD_NOTI("device opened (%d:%d)\n", major, minor );

	pr_info("LowPower::info::groupother::demod::%d::%s-%s::open::ok\n", DEMOD_TASK_OpenCount(), current->group_leader->comm, current->comm);
    return 0;
}

/**
 * release handler for demod device
 *
 */
static int DEMOD_Close(struct inode *inode, struct file *file)
{
    int			major,minor;
    DEMOD_DEVICE_T *	my_dev;
    struct cdev *	cdev;

    cdev		= inode->i_cdev;
    my_dev		= container_of ( cdev, DEMOD_DEVICE_T, cdev);

    DEMOD_TASK_Close();

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    DEMOD_PRINT("device closed (%d:%d)\n", major, minor );
	pr_info("LowPower::info::groupother::demod::%d::%s-%s::close::ok\n", DEMOD_TASK_OpenCount(), current->group_leader->comm, current->comm);

    return 0;
}

/**
 * ioctl handler for demod device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int DEMOD_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long DEMOD_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg )
#endif
{
	int 		err = 0;
	DEMOD_DEVICE_T*	my_dev;
	struct cdev*	cdev;
	DEMOD_CTX_T *	pDemodInfo;
	DEMOD_DEV_T *	pDemodDev;
	int 		device_no;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#else
	struct inode *	inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current demod device object
	 */
	cdev		= inode->i_cdev;
	my_dev		= container_of ( cdev, DEMOD_DEVICE_T, cdev);
	device_no 	= iminor(inode);

	/*
	* check if IOCTL command is valid or not.
	* - if magic value doesn't match, return error (-ENOTTY)
	* - if command is out of range, return error (-ENOTTY)
	*
	* note) -ENOTTY means "Inappropriate ioctl for device.
	*/
	if (_IOC_TYPE(cmd) != DEMOD_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > DEMOD_IOC_MAXNR)
	{
		DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
		return -ENOTTY;
	}
	/* TODO : add some check routine for your device */

	/*
	* check if user memory is valid or not.
	* if memory can't be accessed from kernel, return error (-EFAULT)
	*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (_IOC_DIR(cmd) & (_IOC_READ | _IOC_WRITE))
	err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
#else
	if (_IOC_DIR(cmd) & _IOC_READ)
	err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
	err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
#endif
	if (err) {
		DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
    													_IOC_NR(cmd),
    													(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
    													(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
    													(void*)arg );
		return -EFAULT;
	}

	DEMOD_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );
	pDemodInfo = DEMOD_Get_CTX(device_no);
	pDemodDev = DEMOD_Get_Device_Data();

	switch(cmd) {
		case DEMOD_IO_HW_RESET: {
			if(FALSE == _gExecuteHwRest_gbb) {
				if(RET_OK != DEMOD_ResetHW()) {
					DEMOD_ERROR("FAIL, DEMOD_ResetHW() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				pDemodInfo->bSetParams = FALSE;
				_gExecuteHwRest_gbb = TRUE;
				DEMOD_NOTI("DEMOD_IO_HW_RESET: done\n");
			} else {
				DEMOD_NOTI("DEMOD_IO_HW_RESET: DEMOD_ResetHW() has been already called, Nothing to do \n");
			}
		}
		break;
		case DEMOD_IOW_I2C_OPEN: {
			LX_DEMOD_I2C_DESC_T i2cOpenParam;

			DEMOD_PRINT("DEMOD_IOW_I2C_OPEN \n");

			if (copy_from_user(&i2cOpenParam, (void *)arg, sizeof(LX_DEMOD_I2C_DESC_T))) {
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_I2C_open(i2cOpenParam.portI2C,i2cOpenParam.slvAddr)) {
				DEMOD_ERROR("FAIL, DEMOD_I2C_open() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			pDemodInfo->handleDTV.portI2C = i2cOpenParam.portI2C;
			pDemodInfo->handleDTV.slvAddr = i2cOpenParam.slvAddr;
		}
		break;
		case DEMOD_IO_I2C_CLOSE: {
			DEMOD_PRINT("DEMOD_IO_I2C_CLOSE ok\n");

			if(RET_OK != DEMOD_I2C_Close()) {
				DEMOD_ERROR("FAIL, DEMOD_I2C_Close() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_MEDIA_CHANGE: {
			LX_DEMOD_INIT_PARAM_T initParam;

			DEMOD_NOTI("DEMOD_IOW_MEDIA_CHANGE \n");

			if (copy_from_user(&initParam, (void *)arg, sizeof(LX_DEMOD_INIT_PARAM_T))) {
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_MediaChange(pDemodInfo, &initParam)) {
				DEMOD_ERROR("FAIL, DEMOD_MediaChange() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_CHANNEL_CHANGE: {
			LX_DEMOD_CONFIG_T configParams;

			DEMOD_NOTI("DEMOD_IOW_CHANNEL_CHANGE \n");

			if (copy_from_user(&configParams, (void *)arg, sizeof(LX_DEMOD_CONFIG_T))) {
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ChannelChange(pDemodInfo,&configParams)) {
				DEMOD_ERROR("FAIL, DEMOD_ChannelChange() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_SERIAL_CONTROL: {
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_SERIAL_CONTROL \n");

			if (copy_from_user(&bEnable, (void *)arg, sizeof(BOOLEAN))) {
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_Serial_Control(bEnable)) {
				DEMOD_ERROR("FAIL, DEMOD_Serial_Control() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_SET_IFAGC_POL: {
			LX_DEMOD_AGC_POLAR_T agcPola;

			DEMOD_PRINT("DEMOD_IOW_SET_IFAGC_POL \n");

			if (copy_from_user(&agcPola, (void *)arg, sizeof(LX_DEMOD_AGC_POLAR_T))) {
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_Set_AGCPolarity(agcPola)) {
				DEMOD_ERROR("FAIL, DEMOD_Set_AGCPolarity() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_CHANNEL_INFO: {
			LX_DEMOD_CONFIG_T demodTunedCfg;

			DEMOD_PRINT("DEMOD_IOR_GET_CHANNEL_INFO \n");

			memcpy(&demodTunedCfg,&(pDemodInfo->getCfgParam), sizeof(LX_DEMOD_CONFIG_T));

			if (copy_to_user((void *)arg, (void *)&demodTunedCfg, sizeof(LX_DEMOD_CONFIG_T))) {
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_SIGNAL_STATUS: {
			LX_DEMOD_SIGNAL_CTX_T sigCtx;

			DEMOD_PRINT("DEMOD_IOR_GET_SIGNAL_STATUS \n");

			if(pDemodInfo->lockStatus != LX_DEMOD_LOCKED) {
				sigCtx.bSignalValid	= FALSE;
				sigCtx.packetError	= 0xffffffff;
				sigCtx.ber			= 0xffffffff;
				sigCtx.agc			= 0;
				sigCtx.m.mse		= 0xffff;
				sigCtx.m.bMse 		= 0xffff;
				sigCtx.m.constPwr 	= 0xffff;
			} else {
				memcpy(&sigCtx,&(pDemodInfo->signalStatus), sizeof(LX_DEMOD_SIGNAL_CTX_T));
			}

			if (copy_to_user((void *)arg, (void *)&sigCtx, sizeof(LX_DEMOD_SIGNAL_CTX_T))) {
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_I2C_READ: {
			LX_DEMOD_I2C_COMM_T 	i2cReadParams;
			LX_DEMOD_I2C_COMM_T	*in;

			DEMOD_PRINT("DEMOD_IOR_I2C_READ \n");

			in = (LX_DEMOD_I2C_COMM_T*)arg;

			if ( copy_from_user( &i2cReadParams, (void *)in , sizeof(LX_DEMOD_I2C_COMM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_I2C_Read(i2cReadParams.address, i2cReadParams.nBytes, i2cReadParams.buf))
			{
				DEMOD_ERROR("FAIL, DEMOD_I2C_Read() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(i2cReadParams.nBytes <= sizeof(in->buf))
			{
				if ( copy_to_user((void *)in->buf, (void *)&i2cReadParams.buf,	i2cReadParams.nBytes ) )
				{
					DEMOD_ERROR("FAIL, copy_to_user() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
		}
		break;

		case DEMOD_IOW_I2C_WRITE:
		{
			LX_DEMOD_I2C_COMM_T i2cWriteParams;

			DEMOD_PRINT("DEMOD_IOW_I2C_WRITE \n");

			if ( copy_from_user( &i2cWriteParams, (void *)arg, sizeof(LX_DEMOD_I2C_COMM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_I2C_Write(i2cWriteParams.address, i2cWriteParams.nBytes, i2cWriteParams.buf))
			{
				DEMOD_ERROR("FAIL, DEMOD_I2C_Write() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_REPEATER_ENB:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_REPEATER_ENB \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_RepeaterEnable(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_RepeaterEnable() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_APB_AccessControl:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_APB_AccessControl \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_APB_AccessControl(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_APB_AccessControl() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_POWER_SAVE:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_POWER_SAVE \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_Power_Save(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_Power_Save() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_TPOUT_ENB:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_TPOUT_ENB \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_TPOutCLKEnable(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_TPOutCLKEnable() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			pDemodInfo->bIsTPoutEn = bEnable;
		}
		break;
		case DEMOD_IOW_SET_IF_FREQ:
		{
			UINT32 ifFrq;

			DEMOD_PRINT("DEMOD_IOW_SET_IF_FREQ \n");

			if ( copy_from_user( &ifFrq, (void *)arg, sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_Set_IF_Frq(ifFrq))
			{
				DEMOD_ERROR("FAIL, DEMOD_Set_IF_Frq() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_SET_SPECTRUM_CTRL:
		{
			LX_DEMOD_SPECTRUM_CTRL_T spectrumParam;

			DEMOD_PRINT("DEMOD_IOW_SET_SPECTRUM_CTRL \n");

			if ( copy_from_user( &spectrumParam, (void *)arg, sizeof(LX_DEMOD_SPECTRUM_CTRL_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_Set_SpectrumCtrl(spectrumParam.bAutoEnable, spectrumParam.bSpecInvEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_ID:
		{
			UINT16 id;

			DEMOD_PRINT("DEMOD_IOR_GET_ID \n");

			if(RET_OK != DEMOD_Get_Id(&id))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_Id() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&id,  sizeof(UINT16 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_SPECTRUM_CTRL:
		{
			LX_DEMOD_SPECTRUM_CTRL_T	getSpectrumParams;
			LX_DEMOD_LOCK_STATE_T 		spectrumAuto;
			LX_DEMOD_LOCK_STATE_T 		spectrumInv;

			DEMOD_PRINT("DEMOD_Get_SpectrumStatus \n");

			if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(LX_DEMOD_AUTO == spectrumAuto)
			{
				getSpectrumParams.bAutoEnable = TRUE;
			}
			else
			{
				getSpectrumParams.bAutoEnable = FALSE;
			}

			if(LX_DEMOD_INVERSION == spectrumInv)
			{
				getSpectrumParams.bSpecInvEnable = TRUE;
			}
			else
			{
				getSpectrumParams.bSpecInvEnable = FALSE;
			}

			if ( copy_to_user((void *)arg, (void *)&getSpectrumParams,  sizeof(LX_DEMOD_SPECTRUM_CTRL_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_IFAGC:
		{
			UINT16 ifAgc;

			DEMOD_PRINT("DEMOD_IOR_GET_IFAGC \n");

			if(pDemodInfo->lockStatus != LX_DEMOD_LOCKED )
			{
				ifAgc = 0;
			}
			else
			{
				ifAgc = pDemodInfo->signalStatus.agc;
			}

			if ( copy_to_user((void *)arg, (void *)&ifAgc,  sizeof(UINT16 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_OPERATION_MODE:
		{
			LX_DEMOD_OPER_MODE_T operMode;

			DEMOD_PRINT("DEMOD_IOR_GET_OPERATION_MODE \n");

			if(RET_OK != DEMOD_Get_OperMode(&operMode))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_OperMode() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&operMode,  sizeof(LX_DEMOD_OPER_MODE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_LOCK_STATUS_NOTIFY:
		{
			BOOLEAN notifiedstatus;

			DEMOD_PRINT("DEMOD_IOR_GET_LOCK_STATUS_NOTIFY \n");

			if((TRUE == pDemodInfo->bNotifiedLock) || (TRUE == pDemodInfo->bNotifiedUnlock))
			{
				notifiedstatus = TRUE;
				DEMOD_PRINT("notifiedstatus = TRUE \n");
			}
			else
			{
				notifiedstatus = FALSE;
				DEMOD_PRINT("notifiedstatus = FALSE \n");

			}

			if(pDemodInfo->operMode == LX_DEMOD_ANALOG)
			{
				if(pDemodInfo->getCfgParam.analog.frequency != pDemodInfo->setCfgParam.analog.frequency)
				{
					notifiedstatus 					= FALSE;
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_START;
					pDemodInfo->acqState			= LX_DEMOD_TUNNING_PROCESS;
					pDemodInfo->scanJobFlag		= LX_DEMOD_FLAG_START;
		   			pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
					pDemodInfo->bNotifiedLock		= FALSE;
					pDemodInfo->bNotifiedUnlock 	= FALSE;

					DEMOD_PRINT("notifiedstatus = FALSE \n");
				}
			}

			if ( copy_to_user((void *)arg, (void *)&notifiedstatus,  sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_OFFSETFRQ:
		{
			SINT32 freqOff;

			DEMOD_PRINT("DEMOD_IOR_GET_OFFSETFRQ \n");

			freqOff = pDemodInfo->freqOffset;

			if ( copy_to_user((void *)arg, (void *)&freqOff,  sizeof(SINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_TPIF_ENB:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOR_GET_TPIF_ENB \n");

			if(RET_OK != DEMOD_Get_TPIFStatus(&bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_TPIFStatus() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			if ( copy_to_user((void *)arg, (void *)&bEnable,  sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_VABER:
		{
			UINT32 vBer;

			DEMOD_PRINT("DEMOD_IOR_GET_VABER \n");

			if(pDemodInfo->lockStatus != LX_DEMOD_LOCKED )
			{
				vBer = 0xffffffff;
			}
			else
			{
				vBer = pDemodInfo->signalStatus.ber;
			}

			if ( copy_to_user((void *)arg, (void *)&vBer,  sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_MSE_INFO:
		{
			LX_DEMOD_MSE_T sigMse;

			DEMOD_PRINT("DEMOD_IOR_GET_MSE_INFO \n");

			if(pDemodInfo->lockStatus != LX_DEMOD_LOCKED )
			{
				sigMse.mse			= 0xffff;
				sigMse.bMse 		= 0xffff;
				sigMse.constPwr 	= 0xffff;
			}
			else
			{
				memcpy(&sigMse,&(pDemodInfo->signalStatus.m),sizeof(LX_DEMOD_MSE_T));
			}

			if ( copy_to_user((void *)arg, (void *)&sigMse,  sizeof(LX_DEMOD_MSE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_PKERROR:
		{
			UINT32 pkError;

			DEMOD_PRINT("DEMOD_IOR_GET_PKERROR \n");

			if(pDemodInfo->lockStatus != LX_DEMOD_LOCKED )
			{
				pkError = 0xffffffff;
			}
			else
			{
				pkError = pDemodInfo->signalStatus.packetError;
			}

			if ( copy_to_user((void *)arg, (void *)&pkError,  sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_BANDWIDTH:
		{
			LX_DEMOD_BWMODE_T channelBW;

			DEMOD_PRINT("DEMOD_IOR_GET_BANDWIDTH \n");

			if(RET_OK != DEMOD_Get_BandWidthMode(&channelBW))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_BandWidthMode() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&channelBW,  sizeof(LX_DEMOD_BWMODE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_QAM_MODE:
		{
			LX_DEMOD_RF_MODE_T qamMode ;

			DEMOD_PRINT("DEMOD_IOR_GET_QAM_MODE \n");

			if(RET_OK != DEMOD_Get_QAMMode(&qamMode))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_QAMMode() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&qamMode,  sizeof(LX_DEMOD_RF_MODE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_LOCK:
		{

			LX_DEMOD_LOCK_STATE_T 	lockState;

			if(TRUE == pDemodInfo->bNotifiedLock)
			{
				lockState = LX_DEMOD_LOCKED;
				DEMOD_PRINT("lockState = LX_DEMOD_LOCKED \n");
			}
			else
			{
				lockState = LX_DEMOD_UNLOCKED;
				DEMOD_PRINT("lockState = LX_DEMOD_UNLOCKED \n");
			}

			if ( copy_to_user((void *)arg, (void *)&lockState,  sizeof(LX_DEMOD_LOCK_STATE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;

		case DEMOD_IOR_GET_SYSLOCKTIME:
		{
			UINT16	syslocktime;

			DEMOD_PRINT("DEMOD_IOR_GET_SYSLOCKTIME \n");

			if(RET_OK != DEMOD_Get_SysLockTime(&syslocktime))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_SysLockTime() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user( (void *)arg, (void *)&syslocktime,  sizeof(UINT16) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_GET_FECLOCKTIME:
		{
			UINT16	feclocktime;

			DEMOD_PRINT("DEMOD_IOR_GET_FECLOCKTIME \n");

			if(RET_OK != DEMOD_Get_FecLockTime(&feclocktime))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_FecLockTime() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user( (void *)arg, (void *)&feclocktime,  sizeof(UINT16) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_QAM_SET_FRAME_RESYNC:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IO_QAM_SET_FRAME_RESYNC \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_Set_Frame_resynchronizaiton(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_IO_QAM_SET_FRAME_RESYNC() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_SOFT_RESET:
		{
			DEMOD_PRINT("DEMOD_IO_SOFT_RESET ok\n");

			if(RET_OK != DEMOD_SoftwareReset())
			{
				DEMOD_ERROR("FAIL, DEMOD_SoftwareReset() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_MONITOR_ENB:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_MONITOR_ENB \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			pDemodInfo->bMonitorEnable = bEnable;
		}
		break;
		case DEMOD_IOW_ADC_CTRL_FOR_TEST:
		{
			LX_DEMOD_ADC_VOLTAGE_SEL_T voltageSel;

			DEMOD_PRINT("DEMOD_IOW_ADC_CTRL_FOR_TEST \n");

			if ( copy_from_user( &voltageSel, (void *)arg, sizeof(LX_DEMOD_ADC_VOLTAGE_SEL_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ADC_Control(voltageSel))
			{
				DEMOD_ERROR("FAIL, DEMOD_ADC_Control() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_PRINT_ON_OFF:
		{
			UINT32  printColor = 0;

			DEMOD_PRINT("DEMOD_IOW_PRINT_ON_OFF \n");

			if(copy_from_user( &printColor, (void __user *)arg, sizeof(UINT32)))
			{
				return RET_ERROR;
			}

			if( (printColor >= 9) )
			{
				DEMOD_ERROR("FAIL, Print color is invalid \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( printColor == DBG_COLOR_NONE)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
				_g_print_enb = FALSE;

				DEMOD_ERROR("DEMOD_PRINT is disabled.\n");
			}
			else
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
				_g_print_enb = TRUE;

				DEMOD_PRINT("DEMOD_PRINT is enabled Color is [%s].\n", ui8DemodPrintColor[printColor-1]);
			}
			return RET_OK;
		}
		break;
//DVBC
		case DEMOD_IOW_DVBC_SET_SYM_RATE:
		{
			LX_DEMOD_SYMBOL_CTX_T symbolRateInfo;

			DEMOD_PRINT("DEMOD_IOW_DVBC_SET_SYM_RATE \n");

			if ( copy_from_user( &symbolRateInfo, (void *)arg, sizeof(LX_DEMOD_SYMBOL_CTX_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBC_AutoSymbolRateDet(symbolRateInfo.symbolMode, symbolRateInfo.symbolRate))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_AutoSymbolRateDet() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBC_SET_CONFIG_AUTO:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_DVBC_SET_CONFIG_AUTO \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBC_Set_Config_auto(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_Config_auto() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBC_SET_QAM_MODE:
		{
			LX_DEMOD_RF_MODE_T constel;

			DEMOD_PRINT("DEMOD_IOW_DVBC_SET_QAM_MODE \n");

			if ( copy_from_user( &constel, (void *)arg, sizeof(LX_DEMOD_RF_MODE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBC_Set_QamMode(constel))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_QamMode() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBC_SET_NEVERLOCK_TIME:
		{
			UINT32 waitMs;

			DEMOD_PRINT("DEMOD_IOW_DVBC_SET_NEVERLOCK_TIME \n");

			if ( copy_from_user( &waitMs, (void *)arg, sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBC_Set_NeverLockWaitTime(waitMs))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_NeverLockWaitTime() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;

		case DEMOD_IOR_DVBC_GET_SYM_STATUS:
		{
			LX_DEMOD_SYMBOLRATE_STATE_T	symbolParam ;

			DEMOD_PRINT("DEMOD_IOR_DVBC_GET_SYM_STATUS \n");

			if(RET_OK != DEMOD_DVBC_Get_SymbolRateStatus(&symbolParam ))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Get_SymbolRateStatus() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&symbolParam,  sizeof(LX_DEMOD_SYMBOLRATE_STATE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DVBC_GET_QAM_STATUS:
		{
			LX_DEMOD_QAMMODE_STATE_T	qamModeDet ;

			DEMOD_PRINT("DEMOD_IOR_DVBC_GET_SYM_STATUS \n");

			if(RET_OK != DEMOD_DVBC_Get_QamModeDetectStatus(&qamModeDet ))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Get_QamModeDetectStatus() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&qamModeDet,  sizeof(LX_DEMOD_QAMMODE_STATE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_DVBC_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_DVBC_PRINT_INFO ok\n");
			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
			}

			if(RET_OK != DEMOD_DVBC_Get_DvbInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Get_DvbInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
			}
		}
		break;
		case DEMOD_IO_DVBC_SET_DEFAULT_VALUE:
		{
			DEMOD_PRINT("DEMOD_IO_DVBC_SET_DEFAULT_VALUE \n");

			if(RET_OK != DEMOD_DVBC_Set_DefaultRegisterValue())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_DefaultRegisterValue() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
//DVBC2
		case DEMOD_IOW_DVBC2_SET_CONFIG_PARTIAL:
		{
			LX_DEMOD_DVBC2_CONFIG_T dvbc2ConfigPartial;

			DEMOD_PRINT("DEMOD_IOW_DVBC2_SET_CONFIG_PARTIAL \n");

			if ( copy_from_user( &dvbc2ConfigPartial, (void *)arg, sizeof(LX_DEMOD_DVBC2_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBC2_Set_PartialConfig(&dvbc2ConfigPartial))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC2_Set_PartialConfig() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DVBC2_GET_MULTIPLP_INFO:
		{
			LX_DEMOD_DVBC2_MULTI_PLP_INFO_T paramMultiPLPInfo;

			DEMOD_PRINT("DEMOD_IOW_DVBC2_GET_MULTIPLP_INFO \n");

			memset( &paramMultiPLPInfo, 0x0, sizeof(LX_DEMOD_DVBC2_MULTI_PLP_INFO_T) );

			if(RET_OK != DEMOD_DVBC2_Get_multiPLP_ID(&paramMultiPLPInfo))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC2_GetMultiPLPInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&paramMultiPLPInfo,  sizeof(LX_DEMOD_DVBC2_MULTI_PLP_INFO_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_DVBC2_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_DVBC2_PRINT_INFO ok\n");

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
			}

			if(RET_OK != DEMOD_DVBC2_Get_DvbInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBC2_Get_TotalInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
			}
		}
		break;
//DVBT
		case DEMOD_IO_DVBT_SET_DEFAULT_VALUE:
		{
			LX_DEMOD_BWMODE_T band;

			band = pDemodInfo->setCfgParam.dvbt.channelBW;

			DEMOD_PRINT("DEMOD_IO_DVBT_SET_DEFAULT_VALUE \n");

			if(RET_OK != DEMOD_DVBT_Set_DefaultRegisterValue(band))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_DefaultRegisterValue() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBT_SET_CONFIG_AUTO:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_DVBT_SET_CONFIG_AUTO \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBT_Set_Config_auto(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_Config_auto() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBT_SET_CONFIG_PARTIAL:
		{
			LX_DEMOD_DVBT_CONFIG_T dvbtConfigPartial;

			DEMOD_PRINT("DEMOD_IOW_DVBT_SET_CONFIG_PARTIAL \n");

			if ( copy_from_user( &dvbtConfigPartial, (void *)arg, sizeof(LX_DEMOD_DVBT_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBT_Set_PartialConfig(&dvbtConfigPartial))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_PartialConfig() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBT_SET_CONFIG_FULL:
		{
			LX_DEMOD_DVBT_CONFIG_T dvbtConfigFull;

			DEMOD_PRINT("DEMOD_IOW_DVBT_SET_CONFIG_FULL \n");

			if ( copy_from_user( &dvbtConfigFull, (void *)arg, sizeof(LX_DEMOD_DVBT_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBT_Set_FullConfig(&dvbtConfigFull))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_FullConfig() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;

		case DEMOD_IOW_DVBT_SET_NEVERLOCK_TIME:
		{
			UINT32 waitMs;

			DEMOD_PRINT("DEMOD_IOW_DVBT_SET_NEVERLOCK_TIME \n");

			if ( copy_from_user( &waitMs, (void *)arg, sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBT_Set_NeverLockWaitTime(waitMs))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_NeverLockWaitTime() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_DVBT_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_DVBT_PRINT_INFO ok\n");

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
			}

			if(RET_OK != DEMOD_DVBT_Get_TotalInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Get_TotalInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
			}
		}
		break;
		case DEMOD_IOR_DVBT_GET_CELL_ID:
		{
			UINT16 	cell_ID;
			UINT8 	cellIDLength;

			DEMOD_PRINT("DEMOD_IOR_DVBT_GET_CELL_ID \n");

			if(RET_OK != DEMOD_DVBT_Get_CellId(&cellIDLength, &cell_ID))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Get_CellId() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&cell_ID,  sizeof(UINT16 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
//DVBT2
		case DEMOD_IOW_DVBT2_SET_CONFIG_PARTIAL:
		{
			LX_DEMOD_DVBT2_CONFIG_T dvbt2ConfigPartial;

			DEMOD_PRINT("DEMOD_IOW_DVBT2_SET_CONFIG_PARTIAL \n");

			if ( copy_from_user( &dvbt2ConfigPartial, (void *)arg, sizeof(LX_DEMOD_DVBT2_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBT2_Set_PartialConfig(&dvbt2ConfigPartial))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_PartialConfig() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DVBT2_GET_MULTIPLP_INFO:
		{
			LX_DEMOD_DVBT2_MULTI_PLP_INFO_T paramMultiPLPInfo;

			DEMOD_PRINT("DEMOD_IOW_DVBT2_GET_MULTIPLP_INFO \n");

			memset( &paramMultiPLPInfo, 0x0, sizeof(LX_DEMOD_DVBT2_MULTI_PLP_INFO_T) );

			if(RET_OK != DEMOD_DVBT2_Get_multiPLP_ID(&paramMultiPLPInfo))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT2_GetMultiPLPInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&paramMultiPLPInfo,  sizeof(LX_DEMOD_DVBT2_MULTI_PLP_INFO_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_DVBT2_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_DVBT2_PRINT_INFO ok\n");

			if(FALSE == _g_print_enb)
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );

			if(RET_OK != DEMOD_DVBT2_Get_TotalInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT2_Get_TotalInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			if(FALSE == _g_print_enb)
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
		}
		break;
//VSB
		case DEMOD_IO_VSB_SET_DEFAULT_VALUE:
		{
			DEMOD_PRINT("DEMOD_IO_VSB_SET_DEFAULT_VALUE \n");

			if(RET_OK != DEMOD_VSB_Set_DefaultRegisterValue())
			{
				DEMOD_ERROR("FAIL, DEMOD_VSB_Set_DefaultRegisterValue() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_VSB_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_VSB_PRINT_INFO ok\n");

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
			}

			if(RET_OK != DEMOD_VSB_Get_TotalInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_VSB_Get_TotalInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
			}
		}
		break;
		case DEMOD_IOR_GET_MSE_DYN:
		{
			BOOLEAN bMsedyn;

			DEMOD_PRINT("DEMOD_IOR_GET_MSE_DYN \n");

			if(RET_OK != DEMOD_VSB_Get_MSEdynStatus(&bMsedyn))
			{
				DEMOD_ERROR("FAIL, DEMOD_VSB_Get_MSEdynStatus() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&bMsedyn,  sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_IS_COCHANNEL:
		{
			BOOLEAN bCochannel;

			DEMOD_PRINT("DEMOD_IOR_IS_COCHANNEL \n");

			if(RET_OK != DEMOD_VSB_CochannelExist(&bCochannel))
			{
				DEMOD_ERROR("FAIL, DEMOD_VSB_CochannelExist() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&bCochannel,  sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
//QAM
		case DEMOD_IO_QAM_SET_DEFAULT_VALUE:
		{
			DEMOD_PRINT("DEMOD_IO_QAM_SET_DEFAULT_VALUE \n");

			if(RET_OK != DEMOD_QAM_Set_DefaultRegisterValue())
			{
				DEMOD_ERROR("FAIL, DEMOD_QAM_Set_DefaultRegisterValue() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_QAM_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_QAM_PRINT_INFO ok\n");

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
			}

			if(RET_OK != DEMOD_QAM_Get_TotalInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_QAM_Get_TotalInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
			}
		}
		break;
//ISDBT
		case DEMOD_IO_ISDBT_SET_DEFAULT_VALUE:
		{
			DEMOD_PRINT("DEMOD_IO_ISDBT_SET_DEFAULT_VALUE \n");

			if(RET_OK != DEMOD_ISDBT_Set_DefaultRegisterValue())
			{
				DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_DefaultRegisterValue() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_ISDBT_SET_CONFIG_AUTO:
		{
			BOOLEAN bEnable;

			DEMOD_PRINT("DEMOD_IOW_ISDBT_SET_CONFIG_AUTO \n");

			if ( copy_from_user( &bEnable, (void *)arg, sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ISDBT_Set_Config_auto(bEnable))
			{
				DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_Config_auto() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_ISDBT_SET_CONFIG_PARTIAL:
		{
			LX_DEMOD_ISDBT_CONFIG_T isdbtConfigPartial;

			DEMOD_PRINT("DEMOD_IOW_ISDBT_SET_CONFIG_PARTIAL \n");

			if ( copy_from_user( &isdbtConfigPartial, (void *)arg, sizeof(LX_DEMOD_ISDBT_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ISDBT_Set_PartialConfig(&isdbtConfigPartial))
			{
				DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_PartialConfig() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_ISDBT_SET_CONFIG_FULL:
		{
			LX_DEMOD_ISDBT_CONFIG_T isdbtConfigFull;

			DEMOD_PRINT("DEMOD_IOW_ISDBT_SET_CONFIG_FULL \n");

			if ( copy_from_user( &isdbtConfigFull, (void *)arg, sizeof(LX_DEMOD_ISDBT_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ISDBT_Set_FullConfig(&isdbtConfigFull))
			{
				DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_FullConfig() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_ISDBT_SET_NEVERLOCK_TIME:
		{
			UINT32 waitMs;

			DEMOD_PRINT("DEMOD_IOW_ISDBT_SET_NEVERLOCK_TIME \n");

			if ( copy_from_user( &waitMs, (void *)arg, sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ISDBT_Set_NeverLockWaitTime(waitMs))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_NeverLockWaitTime() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_ISDBT_PRINT_INFO:
		{
			DEMOD_PRINT("DEMOD_IO_ISDBT_PRINT_INFO ok\n");

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_EnableModuleByIndex ( g_demod_debug_fd, 0, DBG_COLOR_NONE );
			}

			if(RET_OK != DEMOD_ISDBT_Get_TotalInfo())
			{
				DEMOD_ERROR("FAIL, DEMOD_ISDBT_Get_TotalInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(FALSE == _g_print_enb)
			{
				OS_DEBUG_DisableModuleByIndex( g_demod_debug_fd, 0);
			}
		}
		break;

		case DEMOD_IOR_ISDBT_GetEmergencyAlertFlagStatus:
		{
			BOOLEAN bEalarm;

			DEMOD_PRINT("DEMOD_ISDBT_GetEmergencyAlertFlagStatus \n");

			if(RET_OK != DEMOD_ISDBT_GetEmergencyAlertFlagStatus(&bEalarm))
			{
				DEMOD_ERROR("FAIL, DEMOD_ISDBT_GetEmergencyAlertFlagStatus() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&bEalarm,  sizeof(BOOLEAN ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
//DVB-S/S2
#if 0
		case DEMOD_IOW_I2C_SAT_TUNER_OPEN:
		{
			LX_DEMOD_I2C_DESC_T i2cOpenParam;


			DEMOD_PRINT("DEMOD_IOW_I2C_OPEN \n");

			if ( copy_from_user( &i2cOpenParam, (void *)arg, sizeof(LX_DEMOD_I2C_DESC_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_I2C_open(i2cOpenParam.portI2C,i2cOpenParam.slvAddr))
			{
				DEMOD_ERROR("FAIL, DEMOD_I2C_open() \n");
				DEMOD_RETURN_FAIL(__F__);
			}


		}
		break;
#endif
		case DEMOD_IOW_DVBS_SET_DISEQC_MESSAGE:
		{
			LX_DEMOD_DVBS_DiSEqC_MSG_T diseqcMsg;

			DEMOD_PRINT("DEMOD_IOW_DVBS_SET_DISEQC_MESSAGE ok\n");

			if ( copy_from_user( &diseqcMsg, (void *)arg, sizeof(LX_DEMOD_DVBS_DiSEqC_MSG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBS_Set_DiseqcToneMessageCtrl(&diseqcMsg))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_DiseqcControl() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBS_SET_MESSAGE_TYPE:
		{
			LX_DEMOD_MESSAGE_TYPE_T messageType;

			DEMOD_PRINT("DEMOD_IOW_DVBS_SET_MESSAGE_TYPE ok\n");

			if ( copy_from_user( &messageType, (void *)arg, sizeof(LX_DEMOD_MESSAGE_TYPE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DVBS_Set_EnvelopModeCtrl(messageType))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_NeverLockWaitTime() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DVBS_GET_BLIND_INFO:
		{
			LX_DEMOD_DVBS_BLIND_PARAM_T blindParam;

			DEMOD_PRINT("DEMOD_IOR_DVBS_GET_BLIND_INFO ok\n");

			if(RET_OK != DEMOD_DVBS_Get_BlindInfo(pDemodInfo->setCfgParam.dvbs.frequency, &blindParam))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBS_Get_BlindInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&blindParam,  sizeof(LX_DEMOD_DVBS_BLIND_PARAM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DVBSX_BLIND_SCAN_INIT:
		{
			LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T initFreq;

			DEMOD_PRINT("DEMOD_IOW_DVBSX_BLIND_SCAN_INIT ok\n");

			if ( copy_from_user( &initFreq, (void *)arg, sizeof(LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			DEMOD_PRINT("DEMOD_IOW_DVBSX_BLIND_SCAN_INIT() startFreqKhz : %d , endFreqKhz : %d \n", initFreq.startFreqKhz, initFreq.endFreqKhz);

			if(RET_OK != DEMOD_DVBSX_BlindScan_Init(&initFreq))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_BlindScan_Init() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			DEMOD_PRINT("DEMOD_DVBSX_BlindScan_Init \n");
		}
		break;
		case DEMOD_IO_DVBSX_BLIND_SCAN_END:
		{
			DEMOD_PRINT("DEMOD_IO_DVBSX_BLIND_SCAN_END ok\n");

			if(RET_OK != DEMOD_DVBSX_BlindScan_End())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_BlindScan_End() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			DEMOD_PRINT("DEMOD_DVBSX_BlindScan_End \n");
		}
		break;
		case DEMOD_IOR_DVBSX_GET_TUNER_FREQ:
		{
			LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T freqInfo;
			DEMOD_PRINT("DEMOD_IOR_DVBSX_GET_TUNER_FREQ ok\n");

			if(RET_OK != DEMOD_DVBSX_GetTunerFreq(&freqInfo))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_GetTunerFreq() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			DEMOD_PRINT("DEMOD_DVBSX_GetTunerFreq \n");

			if ( copy_to_user((void *)arg, (void *)&freqInfo,  sizeof(LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DVBSX_GET_OFFSET_FREQUENCY:
		{
//			UINT32 freqOff;
//			UINT32 symOffset;

			LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T offsetInfo ;

			DEMOD_PRINT("DEMOD_IOR_DVBSX_GET_OFFSET_FREQUENCY \n");

			if(RET_OK != DEMOD_DVBSX_Get_OffsetFreq(&offsetInfo))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_Get_OffsetFreq() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&offsetInfo,  sizeof(LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			DEMOD_PRINT("DEMOD_IOR_DVBSX_GET_OFFSET_FREQUENCY symrate = %d \n", offsetInfo.SymbolRateKhz);
		}
		break;
		case DEMOD_IO_DVBSX_SYMBOL_RATE_DETECT:
		{
			DEMOD_PRINT("DEMOD_IO_DVBSX_SYMBOL_RATE_DETECT \n");

			if(RET_OK != DEMOD_DVBSX_SymbolRate_Detect())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_SymbolRate_Detect() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_DVBSX_BLIND_LOCK_LOOP:
		{
			DEMOD_PRINT("DEMOD_IO_DVBSX_BLIND_LOCK_LOOP \n");

			if(RET_OK != DEMOD_DVBSX_BlindLock_Loop())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_BlindLock_Loop() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DVBSX_GET_NEXTFREQ_STATUS:
		{
			BOOLEAN bBlindScanEnd;

			DEMOD_PRINT("DEMOD_IOR_DVBSX_GET_NEXTFREQ_STATUS \n");

			if(RET_OK != DEMOD_DVBSX_Get_Nextfreq_Status(&bBlindScanEnd))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBSX_Get_Nextfreq_Status() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&bBlindScanEnd,  sizeof(BOOLEAN) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			DEMOD_PRINT("DEMOD_IOR_DVBSX_GET_NEXTFREQ_STATUS bBlindScanEnd = %d \n", (UINT32)bBlindScanEnd);
		}
		break;
// ATSC3
		case DEMOD_IOW_ATSC3_SET_PLP:
		{
			LX_DEMOD_ATSC3_CONFIG_T Atsc3ConfigParam;

			DEMOD_PRINT("DEMOD_IOW_ATSC3_SET_PLP \n");

			if ( copy_from_user( &Atsc3ConfigParam, (void *)arg, sizeof(LX_DEMOD_ATSC3_CONFIG_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ATSC3_Set_PLP(&Atsc3ConfigParam))
			{
				DEMOD_ERROR("FAIL, DEMOD_IOW_ATSC3_SET_PLP() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;

		case DEMOD_IOW_ATSC3_SELECT_PLP:
		{

			UINT8 PlpSel;

			DEMOD_PRINT("DEMOD_IOW_ATSC3_GET_MPLPInfo \n");

			if ( copy_from_user(&PlpSel, (void *)arg,  sizeof(UINT8) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			_gSelplp = PlpSel;
	

		}
		break;		
		
		case DEMOD_IOR_ATSC3_GET_MPLPInfo:
		{
			LX_DEMOD_ATSC3_MULTI_PLP_ID_T Atsc3mPLPInfo;
			

			DEMOD_PRINT("DEMOD_IOW_ATSC3_GET_MPLPInfo \n");

//			if ( copy_from_user(&PlpSel, (void *)arg,  sizeof(UINT8) ) )
//			{
//				DEMOD_ERROR("FAIL, copy_to_user() \n");
//				DEMOD_RETURN_FAIL(__F__);
//			}

			if(RET_OK != DEMOD_ATSC3_Get_MPLP_Info(&Atsc3mPLPInfo, _gSelplp))
			{
				DEMOD_ERROR("FAIL, DEMOD_IOW_ATSC3_GET_MPLPInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}		

			if ( copy_to_user((void *)arg, (void *)&Atsc3mPLPInfo,	sizeof(LX_DEMOD_ATSC3_MULTI_PLP_ID_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
			
	

		}
		break;

		case DEMOD_IOW_ATSC3_SET_OIFTYPE: // htlim
		{
			LX_DEMOD_ATSC3_OIF_TYPE_T Atsc3OifType;

			DEMOD_PRINT("DEMOD_IOW_ATSC3_SET_OIFTYPE \n");

			if ( copy_from_user( &Atsc3OifType, (void *)arg, sizeof(LX_DEMOD_ATSC3_OIF_TYPE_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_ATSC3_Set_OIFType(&Atsc3OifType))
			{
				DEMOD_ERROR("FAIL, DEMOD_IOW_ATSC3_SET_OIFTYPE() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}		
		break;		





		

//ABB
		case DEMOD_IOW_ANALOG_I2C_OPEN:
		case DEMOD_IO_ANALOG_I2C_CLOSE:
		case DEMOD_IOW_ANALOG_DEMOD_OPEN:
		case DEMOD_IOW_ANALOG_INIT:
		case DEMOD_IO_ANALOG_SOFT_RESET:
		case DEMOD_IOW_ANALOG_SET_CVDLOCK:
		case DEMOD_IOW_ANALOG_SET_AFT_RANGE:
		case DEMOD_IOW_ANALOG_SET_CVBS_DEC_SEL:
		case DEMOD_IO_HW_RESET_ABB:
		case DEMOD_IO_ANALOG_Set_WORK_AROUND:
		case DEMOD_IOW_ANALOG_SET_RATE_CONV_CTRL:
		case DEMOD_IOW_ANALOG_SET_HIGH_RATE_CONV_OFFSET:
		case DEMOD_IOW_ANALOG_SET_SIF_CTRL:
		case DEMOD_IOW_ANALOG_SET_SIF_PATH_CTRL:
		case DEMOD_IOW_ANALOG_SET_SPECIAL_AUD_MODE:
		case DEMOD_IOW_ANALOG_DEBUG_SET_SPECTRUMINV:
		case DEMOD_IOR_ANALOG_I2C_READ:
		case DEMOD_IOW_ANALOG_I2C_WRITE:
		case DEMOD_IO_ANALOG_I2C_REGDUMP:
		case DEMOD_IOW_ANALOG_SET_ABB_MODE:
		case DEMOD_IOW_ANALOG_DEBUG_SET_IF_FREQ:
		case DEMOD_IOW_ANALOG_DEBUG_ABB:
			DEMOD_WARN("No more support ABB, cmd 0x%x\n", cmd);
			//return -ENOIOCTLCMD;
			break;
		case DEMOD_IO_FW_Initialize:
		case DEMOD_IO_ALL_FW_Initialize:
		{
			DEMOD_NOTI("DEMOD_IO_FW_Initialize ok\n");

			if(RET_OK != DEMOD_FW_Initialize())
			{
				DEMOD_ERROR("FAIL, DEMOD_FW_Initialize() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_DVB_SW_Init:
		{
			DEMOD_NOTI("DEMOD_IO_DVB_SW_Init, %s\n", (pDemodDev->sw_type & DEMOD_SW_TYPE_DVB) ? "skip" : "do");
			if (!(pDemodDev->sw_type & DEMOD_SW_TYPE_DVB)) {
				if(RET_OK != DEMOD_DVB_SW_Init())
				{
					DEMOD_ERROR("FAIL, DEMOD_IO_DVB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
		}
		break;
		case DEMOD_IO_DTMB_SW_Init:
		{
			DEMOD_NOTI("DEMOD_IO_DTMB_SW_Init, %s\n", (pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB) ? "skip" : "do");
			if (!(pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB)) {
				if(RET_OK != DEMOD_DTMB_SW_Init())
				{
					DEMOD_ERROR("FAIL, DEMOD_DTMB_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
		}
		break;
		case DEMOD_IO_ATSC_SW_Init:
		{
			DEMOD_NOTI("DEMOD_IO_ATSC_SW_Init, %s\n", (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC) ? "skip" : "do");
			if (!(pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC)) {
				if(RET_OK != DEMOD_ATSC_SW_Init())
				{
					DEMOD_ERROR("FAIL, DEMOD_ATSC_SW_Init() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
		}
		break;
		case DEMOD_IO_VSB_SetDemod_Simple:
		{
			DEMOD_NOTI("DEMOD_IO_VSB_SetDemod_Simple ok\n");

			if(RET_OK != DEMOD_VSB_SetDemod_Simple())
			{
				DEMOD_ERROR("FAIL, DEMOD_IO_VSB_SetDemod_Simple() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DBB_I2C_READ:
		{
			LX_DEMOD_I2C_COMM_T 	i2cReadParams;
			LX_DEMOD_I2C_COMM_T	*in;

			DEMOD_PRINT("DEMOD_IOR_DBB_I2C_READ \n");

			in = (LX_DEMOD_I2C_COMM_T*)arg;

			if ( copy_from_user( &i2cReadParams, (void *)in , sizeof(LX_DEMOD_I2C_COMM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DBB_I2C_Read(i2cReadParams.address, i2cReadParams.nBytes, i2cReadParams.buf))
			{
				DEMOD_ERROR("FAIL, DEMOD_DBB_I2C_Read() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(i2cReadParams.nBytes <= sizeof(in->buf))
			{
				if ( copy_to_user((void *)in->buf, (void *)&i2cReadParams.buf,	i2cReadParams.nBytes ) )
				{
					DEMOD_ERROR("FAIL, copy_to_user() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
		}
		break;
		case DEMOD_IOW_DBB_I2C_WRITE:
		{
			LX_DEMOD_I2C_COMM_T i2cWriteParams;

			DEMOD_PRINT("DEMOD_IOW_DBB_I2C_WRITE \n");

			if ( copy_from_user( &i2cWriteParams, (void *)arg, sizeof(LX_DEMOD_I2C_COMM_T ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DBB_I2C_Write(i2cWriteParams.address, i2cWriteParams.nBytes, i2cWriteParams.buf))
			{
				DEMOD_ERROR("FAIL, DEMOD_DBB_I2C_Write() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DBB_APB_Read:
		{
			LX_DEMOD_APB_COMM_T 	APBReadParams;
			LX_DEMOD_APB_COMM_T	*in;

			DEMOD_PRINT("DEMOD_IOR_DBB_I2C_READ \n");

			in = (LX_DEMOD_APB_COMM_T*)arg;

			if ( copy_from_user( &APBReadParams, (void *)in , sizeof(LX_DEMOD_APB_COMM_T)))
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DBB_APB_Read(APBReadParams.address, &(APBReadParams.buf)))
			{
				DEMOD_ERROR("FAIL, DEMOD_DBB_APB_Read() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((&(in->buf)), &(APBReadParams.buf), sizeof(UINT32)))
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_DBB_APB_Write:
		{
			LX_DEMOD_APB_COMM_T APBWriteParams;

			DEMOD_PRINT("DEMOD_DBB_APB_Write \n");

			if ( copy_from_user( &APBWriteParams, (void *)arg , sizeof(LX_DEMOD_APB_COMM_T)))
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DBB_APB_Write(APBWriteParams.address, &(APBWriteParams.buf)))
			{
				DEMOD_ERROR("FAIL, DEMOD_DBB_APB_Write() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOR_Get_DBB_FW_Info:
		{
			UINT32 FW_info;

			DEMOD_PRINT("DEMOD_Get_FW_PartInfo \n");

			if(RET_OK != DEMOD_Get_FW_PartInfo(&FW_info))
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_FW_PartInfo() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if ( copy_to_user((void *)arg, (void *)&FW_info,  sizeof(UINT32) ) )
			{
				DEMOD_ERROR("FAIL, copy_to_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IO_Get_DBB_Dump:
		{
			DEMOD_PRINT("DEMOD_Get_Dump ok\n");

			if(RET_OK != DEMOD_Get_Dump())
			{
				DEMOD_ERROR("FAIL, DEMOD_Get_Dump() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		case DEMOD_IOW_DBB_PDB_Write:
		{
			UINT32 value;
			DEMOD_PRINT("DEMOD_IOW_DBB_PDB_Write \n");

			if ( copy_from_user( &value, (void *)arg, sizeof(UINT32 ) ) )
			{
				DEMOD_ERROR("FAIL, copy_from_user() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(RET_OK != DEMOD_DBB_PDB_Write(value))
			{
				DEMOD_ERROR("FAIL, DEMOD_DBB_PDB_Write() \n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		break;
		default:
		{
			DEMOD_ERROR("FAIL, Invalid IOCTL() \n");
			DEMOD_RETURN_FAIL(__F__);
		}
    }
    return RET_OK;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
#ifdef CONFIG_COMPAT
static long DEMOD_CompatIoctl ( struct file *filp, unsigned int cmd, unsigned long arg )
{
	long ret;
	int kReturn;

	switch (cmd)
	{
	case DEMOD_IOW_CHANNEL_CHANGE:
	{
		LX_DEMOD_CONFIG_T arg_lx_demod_config_t;
		kReturn = copy_from_user(&arg_lx_demod_config_t, (void __user *)arg,
					   sizeof(LX_DEMOD_CONFIG_T));
		arg_lx_demod_config_t.analog.handleABB =
			(void *)(uintptr_t)arg_lx_demod_config_t.analog.compat_handleABB;
		kReturn = copy_to_user((void __user *)arg, &arg_lx_demod_config_t,
					 sizeof(LX_DEMOD_CONFIG_T));
		break;
	}
	default:
		break;
	}

	ret = DEMOD_Ioctl(filp, cmd, arg);

	return ret;
}
#endif
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",DEMOD_Init);
#else
module_init(DEMOD_Init);
#endif
module_exit(DEMOD_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

