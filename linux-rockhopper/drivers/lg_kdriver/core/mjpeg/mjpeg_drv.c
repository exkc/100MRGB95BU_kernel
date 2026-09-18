/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

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
 *  main driver implementation for mjpeg device.
 *	MJPEG device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.04.09
 *  note		Additional information.
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/
// #undef    SUPPORT_MJPEG_DEVICE_READ_WRITE_FOPS

/*-----------------------------------------------------------------------------
        File Inclusions
-----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <linux/spinlock.h>
#include <linux/freezer.h>

#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "mjpeg_drv.h"
#include "mjpeg_header.h"
#include "mjpeg_core_sic.h"
#include "icod_clockgate.h"
#include "hma_alloc.h"

#include <linux/dma-mapping.h>
#include <asm/cacheflush.h>

logm_define(jpeg, log_level_noti);
/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/

#define LX_MJPEG_COPY_FROM_USER(TYPE, NAME, ARG, ret)                          \
	{                                                                          \
		NAME = (TYPE *)OS_KMalloc(sizeof(TYPE));                               \
		if (NAME == NULL) {                                                    \
			MJPEG_ERROR("Error in KMALLOC!!\n");                               \
			ret = -ENOMEM;                                                     \
			goto exit;                                                         \
		}                                                                      \
		ret = copy_from_user((void *)NAME, (void __user *)ARG, sizeof(TYPE));  \
		if (ret != RET_OK) {                                                   \
			MJPEG_ERROR("Error in COPY_FROM_USER!!\n");                        \
			OS_KFree(NAME);                                                    \
			NAME = NULL;                                                       \
			goto exit;                                                         \
		}                                                                      \
	};

#define LX_MJPEG_COPY_PARAM(TYPE, NAME, ARG, ret)                              \
	{                                                                          \
		NAME = (TYPE *)OS_KMalloc(sizeof(TYPE));                               \
		if (NAME == NULL) {                                                    \
			MJPEG_ERROR("Error in KMALLOC!!\n");                               \
			ret = -ENOMEM;                                                     \
			break;                                                             \
		}                                                                      \
		memcpy((void *)NAME, &ARG, sizeof(TYPE));                              \
		if (ret != RET_OK) {                                                   \
			MJPEG_ERROR("Error in memcpy!!\n");                                \
			OS_KFree(NAME);                                                    \
			break;                                                             \
		}                                                                      \
	};

/*-----------------------------------------------------------------------------
        Type Definitions
-----------------------------------------------------------------------------*/

/**
 *	main control block for MJPEG device.
 *	each minor device has unique control block
 *
 */
typedef struct {
	// BEGIN of common device
	dev_t devno; ///< device number
	struct cdev cdev; ///< char device structure
			// END of command device

	// BEGIN of device specific data
	// OS_EVENT_T                stEvent;            ///< evnet to catch
	// decode_done. Move to core.

	LX_MJPEG_HEADER_T stHeader; ///< header information of current image
	LX_MJPEG_IMAGE_INFO_T stImageInfo; ///< image informatino of current image
	LX_MJPEG_OPTION_T stOption;

	LX_MJPEG_MEM_BUF_T stDataBuffer; ///< encoded data buffer
	LX_MJPEG_IMAGE_BUF_T stImageBuffer; ///< image buffer

	UINT32 ui32InputSize;
	UINT32 ui32OutputSize;

	BOOLEAN bFirstBlock;
	// END of device specific data
} MJPEG_DEVICE_T;

struct driver_priv {
	bool have_hardware;
	struct device *dev;
	unsigned long cache_addr;
	unsigned int buf_len;
	struct page *page;
	unsigned int
			ui32Memory_base; // Replace MJPEG OPEN Global variable : gMemCfgMjpeg
	unsigned int ui32Memory_size;
	BOOLEAN mmaped;
	BOOLEAN dec_init;
};

#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
typedef struct {
	// add here extra parameter
	bool is_suspended;
} MJPEG_DRVDATA_T;
#endif

typedef struct {
	struct mutex lock;
	wait_queue_head_t wq;

	UINT32 intr[LX_MJPEG_MAX_INTR_DATA];
	volatile UINT32 widx;
	volatile UINT32 ridx;
} MJPEG_INTR_DATA_T;

/*-----------------------------------------------------------------------------
        External Function Prototype Declarations
-----------------------------------------------------------------------------*/
int MJPEG_probe(struct platform_device *pdev);

/*-----------------------------------------------------------------------------
        External Variables
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Functions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Variables
-----------------------------------------------------------------------------*/
int g_MJPEG_major = MJPEG_MAJOR;
int g_MJPEG_minor = MJPEG_MINOR;
int mjpeg_opennum = 0;

OS_SEM_T mjpeg_mutex;

#if defined(MJPEG_DEBUG_REG_DUMP) || defined(MJPEG_DEBUG_TRACE_DUMP)
char *_logBuffer = NULL;
int _logIndex = 0;
int _logNumber = 0;
#endif

static MJPEG_INTR_DATA_T _gMJPEG_Intr; /* notifier */

/*-----------------------------------------------------------------------------
        Static Function Prototypes Declarations
-----------------------------------------------------------------------------*/
static int MJPEG_Open(struct inode *inode, struct file *filp);
static int MJPEG_Close(struct inode *inode, struct file *file);

static long MJPEG_UnlockedIoctl(struct file *filp, unsigned int cmd,
								unsigned long arg);
#ifdef CONFIG_COMPAT
static long MJPEG_CompatIoctl(struct file *filp, unsigned int cmd,
							  unsigned long arg);
#endif

static int MJPEG_mmap(struct file *filp, struct vm_area_struct *vma);
static ssize_t MJPEG_Read(struct file *file, char __user *data, size_t size,
						  loff_t *off);

/*-----------------------------------------------------------------------------
        Static Variables
-----------------------------------------------------------------------------*/

/**
 * main control block for MJPEG device
 */
static MJPEG_DEVICE_T *g_MJPEG_device;

/**
 * file I/O description for MJPEG device
 *
 */
static struct file_operations g_MJPEG_fops = {
	.open = MJPEG_Open,
	.release = MJPEG_Close,
	.unlocked_ioctl = MJPEG_UnlockedIoctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = MJPEG_CompatIoctl,
#endif
	.mmap = MJPEG_mmap,
	.read = MJPEG_Read,
};

/*========================================================================================
        Implementation Group
========================================================================================*/
#if defined(MJPEG_DEBUG_REG_DUMP) || defined(MJPEG_DEBUG_TRACE_DUMP)
static void _LogInit(char *name)
{
	if (_logBuffer == NULL) {
		_logBuffer = OS_KMalloc(1024 * 1024);
	}

	_logIndex = 0;
	_logNumber++;

	if (name != NULL) {
		_logIndex += sprintf(_logBuffer + _logIndex, "%s\n", name);
	}
}

static void _LogFinal(void)
{
	if (_logBuffer != NULL && _logIndex > 0) {
		OS_FILE_T logFile;
		char filename[256] = {};

		sprintf(filename, "/tmp/mjpeg_%02d.log", _logNumber);
		printk("Write log to [%s]\n", filename);

		if (RET_OK == OS_OpenFile(&logFile, filename,
								  O_CREAT | O_APPEND | O_LARGEFILE, 0666)) {
			OS_WriteFile(&logFile, (char *)_logBuffer, _logIndex);
			OS_CloseFile(&logFile);
		}
	}

	if (_logBuffer != NULL) {
		OS_KFree(_logBuffer);
		_logBuffer = NULL;
	}

	_logIndex = 0;
}
#endif

static int MJPEG_InitNotify(void)
{
	// initialize
	memset(&_gMJPEG_Intr, 0, sizeof(_gMJPEG_Intr));

	mutex_init(&_gMJPEG_Intr.lock);
	init_waitqueue_head(&_gMJPEG_Intr.wq);

	return RET_OK;
}

static int MJPEG_ResetNotify(void)
{
	mutex_lock(&_gMJPEG_Intr.lock);

	memset(_gMJPEG_Intr.intr, 0, sizeof(_gMJPEG_Intr.intr));
	_gMJPEG_Intr.ridx = 0;
	_gMJPEG_Intr.widx = 0;

	mutex_unlock(&_gMJPEG_Intr.lock);
	return RET_OK;
}

int MJPEG_AddNotify(UINT32 intr)
{
	int ret = RET_ERROR;
	UINT32 ridx, widx, next_widx;
	static int notify_max_errors =
			10; /* To prevent the message buffer overflow in abnormal case */

	mutex_lock(&_gMJPEG_Intr.lock);

	widx = _gMJPEG_Intr.widx;
	ridx = _gMJPEG_Intr.ridx;

	MJPEG_DEBUG("widx[%d] ridx[%d] intr[0x%08x]\n", widx, ridx, intr);

	next_widx = (widx + 1) % LX_MJPEG_MAX_INTR_DATA;
	if (next_widx == ridx) {
		/* buffer is full, reset to 0 */
		_gMJPEG_Intr.widx = 0;
		_gMJPEG_Intr.ridx = 0;

		if (notify_max_errors > 0) {
			MJPEG_ERROR("Krdv->User Msg Queue is full");
			notify_max_errors--;
		}
		ret = RET_ERROR;
	} else {
		_gMJPEG_Intr.intr[widx] = intr;
		_gMJPEG_Intr.widx = next_widx;
		ret = RET_OK;
	}

	mutex_unlock(&_gMJPEG_Intr.lock);
	return ret;
}

void MJPEG_WakeupNotify(void)
{
	MJPEG_DEBUG("Wake up!\n");
	wake_up_interruptible(&_gMJPEG_Intr.wq);
}

#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int MJPEG_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef KDRV_CONFIG_PM_MJPEG
	MJPEG_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	printk("MJPEG - suspend BEGIN\n");

	// add here the suspend code

	if (drv_data->is_suspended == 1) {
		printk("MJPEG - suspend FAIL\n");
		return -1; // If already in suspend state, so ignore
	}

	drv_data->is_suspended = 1;
	printk("MJPEG - suspend OK\n");
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
static int MJPEG_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_MJPEG
	MJPEG_DRVDATA_T *drv_data;

	printk("MJPEG - resume BEGIN\n");

	drv_data = platform_get_drvdata(pdev);

	if (drv_data->is_suspended == 0) {
		printk("MJPEG - resume FAIL\n");
		return -1;
	}
	// add here the resume code

	drv_data->is_suspended = 0;
	ICOD_ClockResume();
	printk("MJPEG - resume OK\n");
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
int MJPEG_probe(struct platform_device *pdev)
{
	MJPEG_DRVDATA_T *drv_data;

	drv_data = (MJPEG_DRVDATA_T *)kmalloc(sizeof(MJPEG_DRVDATA_T), GFP_KERNEL);

	// add here driver registering code & allocating resource code

	MJPEG_PRINT("[%s] done probe\n", MJPEG_MODULE);
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
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
static void MJPEG_remove(struct platform_device *pdev)
#else
static int MJPEG_remove(struct platform_device *pdev)
#endif
{
	MJPEG_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	MJPEG_PRINT("released\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 12, 0)
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
static void MJPEG_release(struct device *dev)
{
	MJPEG_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver mjpeg_driver = {
    .probe = MJPEG_probe,
    .suspend = MJPEG_suspend,
    .remove = MJPEG_remove,
    .resume = MJPEG_resume,
    .driver =
        {
            .name = MJPEG_MODULE,
        },
};

static struct platform_device mjpeg_device = {
    .name = MJPEG_MODULE,
    .id = -1,
    .dev =
        {
            .release = MJPEG_release,
        },
};
#endif

int MJPEG_Init(void)
{
	int i;
	int err;
	dev_t dev;

	/* allocate main device handler, register current device.
   *
   * If devie major is predefined then register device using that number.
   * otherwise, major number of device is automatically assigned by Linux
   * kernel.
   *
   */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if (platform_driver_register(&mjpeg_driver) < 0) {
		MJPEG_ERROR("[%s] platform driver register failed\n", MJPEG_MODULE);
	} else {
		if (platform_device_register(&mjpeg_device)) {
			platform_driver_unregister(&mjpeg_driver);
			MJPEG_ERROR("[%s] platform device register failed\n", MJPEG_MODULE);
		} else {
			MJPEG_DEBUG("[%s] platform register done\n", MJPEG_MODULE);
		}
	}
#endif
	err = icod_ipw_clk_gate_init();
	if (err < 0) {
		MJPEG_ERROR("ipw ioremap fail\n");
		return -ENOMEM;
	}

	g_MJPEG_device = (MJPEG_DEVICE_T *)OS_KMalloc(sizeof(MJPEG_DEVICE_T) *
												  MJPEG_MAX_DEVICE);

	if (NULL == g_MJPEG_device) {
		MJPEG_WARN("out of memory. can't allocate %d bytes\n",
				   (int)(sizeof(MJPEG_DEVICE_T) * MJPEG_MAX_DEVICE));
		return -ENOMEM;
	}

	memset(g_MJPEG_device, 0x0, sizeof(MJPEG_DEVICE_T) * MJPEG_MAX_DEVICE);

	if (g_MJPEG_major) {
		dev = MKDEV(g_MJPEG_major, g_MJPEG_minor);
		err = register_chrdev_region(dev, MJPEG_MAX_DEVICE, MJPEG_MODULE);
	} else {
		err = alloc_chrdev_region(&dev, g_MJPEG_minor, MJPEG_MAX_DEVICE,
								  MJPEG_MODULE);
		g_MJPEG_major = MAJOR(dev);
	}

	if (err < 0) {
		MJPEG_WARN("can't register MJPEG device\n");
		return -EIO;
	}

	for (i = 0; i < MJPEG_MAX_DEVICE; i++) {
		/* initialize cdev structure with predefined variable */
		dev = MKDEV(g_MJPEG_major, g_MJPEG_minor + i);
		cdev_init(&(g_MJPEG_device[i].cdev), &g_MJPEG_fops);
		g_MJPEG_device[i].devno = dev;
		g_MJPEG_device[i].cdev.owner = THIS_MODULE;
		g_MJPEG_device[i].cdev.ops = &g_MJPEG_fops;

		/* TODO: initialize minor device */

		/* END */

		err = cdev_add(&(g_MJPEG_device[i].cdev), dev, 1);

		if (err) {
			MJPEG_ERROR("error (%d) while adding MJPEG device (%d.%d)\n", err,
						MAJOR(dev), MINOR(dev));
			return -EIO;
		}

		OS_CreateDeviceClass(g_MJPEG_device[i].devno, "%s%d", MJPEG_MODULE, i);
	}

	/* initialize notifier */
	err = MJPEG_InitNotify();
	MJPEG_CHECK_ERROR(err != RET_OK, return err,
					  "Error(%d) in MJPEG_InitNotify()", err);

	MJPEG_HwInit();
	ICOD_ClockInit();

	MJPEG_NOTI("MJPEG device initialized\n");

	return 0;
}

void MJPEG_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV(g_MJPEG_major, g_MJPEG_minor);

	MJPEG_HwEnd();

	/* remove all minor devicies and unregister current device */
	for (i = 0; i < MJPEG_MAX_DEVICE; i++) {
		/* TODO: cleanup each minor device */

		/* END */
		cdev_del(&(g_MJPEG_device[i].cdev));
	}

	unregister_chrdev_region(dev, MJPEG_MAX_DEVICE);

	OS_Free(g_MJPEG_device);

	MJPEG_NOTI("MJPEG device cleanup\n");
}

static DEFINE_MUTEX(hardware_lock);
static int __must_check get_hardware(struct driver_priv *priv)
{
	int ret = 0;

	if (!priv->have_hardware) {
		ret = mutex_lock_interruptible(&hardware_lock);
		if (ret < 0)
			MJPEG_WARN("cannot get hardware lock. %d\n", ret);
		else {
			priv->have_hardware = TRUE;
			MJPEG_INFO("have the hardware.\n");
		}
	}

	return ret;
}

static int put_hardware(struct driver_priv *priv)
{
	if (priv->have_hardware) {
		MJPEG_INFO("put the hardware.\n");
		mutex_unlock(&hardware_lock);
		priv->have_hardware = FALSE;
	}

	return 0;
}

/**
 * open handler for MJPEG device
 *
 */
static int MJPEG_Open(struct inode *inode, struct file *filp)
{
	struct driver_priv *priv;

	priv = kcalloc(sizeof(*priv), 1, GFP_KERNEL);
	if (!priv) {
		MJPEG_ERROR("alloc fail\n");
		return -ENOMEM;
	}

	filp->private_data = priv;
	priv->dev = &mjpeg_device.dev;

	MJPEG_INFO("device opened\n");

	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0)) {
		priv->ui32Memory_size = gMemCfgMjpeg.ui32Memory_size;
		priv->ui32Memory_base =
				hma_alloc_user("photofb", MROUND(priv->ui32Memory_size, 0x1000),
							   0x1000, "mjpeg");
		if (!priv->ui32Memory_base) {
			MJPEG_ERROR("hma alloc for mjpeg fail\n");
			kfree(priv);
			return -ENOMEM;
		}
		MJPEG_INFO("hma alloc success %#010x\n", priv->ui32Memory_base);
	} else {
		priv->ui32Memory_base = gMemCfgMjpeg.ui32Memory_base;
		priv->ui32Memory_size = gMemCfgMjpeg.ui32Memory_size;

		if (!gMemCfgMjpeg.ui32Memory_base) {
			MJPEG_ERROR("Memory is empty!! \n");
			return -ENOMEM;
		}
	}

	ICOD_ClockOn();
	mjpeg_opennum++;
	MJPEG_INFO("open success (open count %d)\n", mjpeg_opennum);
	return 0;
}

/**
 * release handler for MJPEG device
 *
 */
static int MJPEG_Close(struct inode *inode, struct file *file)
{
	struct driver_priv *priv = file->private_data;

	if (!priv) {
		MJPEG_ERROR("Memory is empty!! \n");
		return -ENOMEM;
	}

	MJPEG_INFO("device closing\n");

	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0)) {
		if (priv->ui32Memory_base) {
			hma_free("photofb", priv->ui32Memory_base);
			priv->ui32Memory_base = 0;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0))
			if (priv->cache_addr)
				memunmap((void *)priv->cache_addr);
#endif
		}
	}
	put_hardware(priv);
	kfree(priv);

	ICOD_ClockOff();
	mjpeg_opennum--;
	MJPEG_INFO("close success (open count %d)\n", mjpeg_opennum);
	return 0;
}

static int MJPEG_Process_CommandGeneral(MJPEG_DEVICE_T *my_dev,
										unsigned long arg)
{
	int ret = -EFAULT;

	LX_MJPEG_GENERAL_CMD_PARAM_T *stCmdParam = NULL;
	LX_MJPEG_COPY_FROM_USER(LX_MJPEG_GENERAL_CMD_PARAM_T, stCmdParam, arg, ret);

	switch (stCmdParam->command) {
	case LX_MJPEG_CMD_SW_RESET:
		MJPEG_HwReset();
		break;

	case LX_MJPEG_CMD_USE_QUEUE: {
		BOOLEAN *bUseQueue;
		LX_MJPEG_COPY_PARAM(BOOLEAN, bUseQueue, stCmdParam->param.use_queue,
							ret);

		ret = MJPEG_SetIsUseQueue(*bUseQueue);

		OS_KFree(bUseQueue);
	} break;

	case LX_MJPEG_CMD_STOP_READ: {
		MJPEG_AddNotify(LX_MJPEG_RESULT_STOP);
		MJPEG_WakeupNotify();
		break;
	}

	case LX_MJPEG_CMD_CLEAR_INTR: {
		MJPEG_ResetNotify();
		break;
	}

	default:
		MJPEG_ERROR("!!\n");
		break;
	}

exit:
	if (stCmdParam)
		OS_KFree(stCmdParam);
	return ret;
}

/**
 * DMA operations for MJPEG data transfer
 *
 */

static void dma_cache_ops(unsigned long dma_start_addr, unsigned int length,
						  int dma_direction)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
	unsigned long dma_end_addr = dma_start_addr + length;
	if (dma_direction == DMA_TO_DEVICE) {
		dcache_clean_poc(dma_start_addr, dma_end_addr);
	} else {
		dcache_inval_poc(dma_start_addr, dma_end_addr);
	}
#else
	__dma_map_area((void *)dma_start_addr, length, dma_direction);
#endif
}

static int MJPEG_Process_CommandDecode(struct file *filp,
									   MJPEG_DEVICE_T *my_dev,
									   unsigned long arg)
{
	int ret = -EFAULT;
	int offset = 0;
	BOOLEAN bUserCopy = FALSE;
	struct driver_priv *priv = filp->private_data;
	LX_MJPEG_GENERAL_CMD_PARAM_T *stCmdParam = NULL;

	if (!priv) {
		MJPEG_ERROR("Memory is empty!! \n");
		return -ENOMEM;
	}

	LX_MJPEG_COPY_FROM_USER(LX_MJPEG_GENERAL_CMD_PARAM_T, stCmdParam, arg, ret);

	switch (stCmdParam->command) {
	case LX_MJPEG_CMD_DECODE_START: {
		LX_MJPEG_DEC_START_PARAM_T *stDecParam = NULL;
		LX_MJPEG_COPY_PARAM(LX_MJPEG_DEC_START_PARAM_T, stDecParam,
							stCmdParam->param.dec_start, ret);

		memcpy((void *)&my_dev->stDataBuffer, (void *)&stDecParam->stDataBuffer,
			   sizeof(LX_MJPEG_MEM_BUF_T));
		my_dev->ui32InputSize += stDecParam->ui32DataLength;

		offset = my_dev->stDataBuffer.addr - priv->ui32Memory_base;
		MJPEG_TRACE("start-->offset:%d, addr:%u, base_addr:%u\n", offset,
					my_dev->stDataBuffer.addr, priv->ui32Memory_base);
		if (offset < 0) {
			MJPEG_ERROR("start-->offset value is invalid!! "
						"(offset:%d, addr:%u, base_addr:%u)\n",
						offset, my_dev->stDataBuffer.addr,
						priv->ui32Memory_base);
			OS_KFree(stDecParam);
			break;
		}

		dma_cache_ops(priv->cache_addr + offset, my_dev->stDataBuffer.length,
					  DMA_TO_DEVICE);

		ret = MJPEG_DEC_Start(&my_dev->stDataBuffer, stDecParam->ui32DataLength,
							  stDecParam->bEndOfStream);
		OS_KFree(stDecParam);
		break;
	}

	case LX_MJPEG_CMD_DECODE_CONTINUE: {
		LX_MJPEG_DEC_CONTINUE_PARAM_T *stDecParam = NULL;
		LX_MJPEG_COPY_PARAM(LX_MJPEG_DEC_CONTINUE_PARAM_T, stDecParam,
							stCmdParam->param.dec_continue, ret);

		memcpy((void *)&my_dev->stDataBuffer, (void *)&stDecParam->stDataBuffer,
			   sizeof(LX_MJPEG_MEM_BUF_T));
		my_dev->ui32InputSize += stDecParam->ui32DataLength;

		offset = my_dev->stDataBuffer.addr - priv->ui32Memory_base;
		MJPEG_TRACE("continue-->offset:%d, addr:%u, base_addr:%u\n", offset,
					my_dev->stDataBuffer.addr, priv->ui32Memory_base);
		if (offset < 0) {
			MJPEG_ERROR("continue-->offset value is invalid!! "
						"(offset:%d, addr:%u, base_addr:%u)\n",
						offset, my_dev->stDataBuffer.addr,
						priv->ui32Memory_base);
			OS_KFree(stDecParam);
			break;
		}

		dma_cache_ops(priv->cache_addr + offset, my_dev->stDataBuffer.length,
					  DMA_TO_DEVICE);

		ret = MJPEG_DEC_Continue(&my_dev->stDataBuffer,
								 stDecParam->ui32DataLength,
								 stDecParam->bEndOfStream,
								 stDecParam->bSkipCheck);

		OS_KFree(stDecParam);

		break;
	}

	case LX_MJPEG_CMD_DECODE_STOP: {
		LX_MJPEG_DEC_STOP_PARAM_T *stStopParam;
		stStopParam = (LX_MJPEG_DEC_STOP_PARAM_T *)OS_KMalloc(
				sizeof(LX_MJPEG_DEC_STOP_PARAM_T));
		if (stStopParam == NULL) {
			ret = -ENOMEM;
			put_hardware(priv);
			break;
		}

		memcpy((void *)&stStopParam->stImageInfo, (void *)&my_dev->stImageInfo,
			   sizeof(LX_MJPEG_IMAGE_INFO_T));
		memcpy((void *)&(stCmdParam->param.dec_stop), (void *)stStopParam,
			   sizeof(LX_MJPEG_DEC_STOP_PARAM_T));
		bUserCopy = TRUE;

		OS_KFree(stStopParam);

		// set use queue flag to FALSE
		MJPEG_SetIsUseQueue(FALSE);

		put_hardware(priv);

		break;
	}

	case LX_MJPEG_CMD_DECODE_CLEAR_DPB: {
		ret = MJPEG_DEC_PartialContinue(LX_MJPEG_RESULT_BUFFER0);
		break;
	}

	case LX_MJPEG_CMD_DECODE_COPY_CACHE_DATA: {
		dma_cache_ops(priv->cache_addr + priv->buf_len / 4,
					  priv->buf_len * 3 / 4, DMA_FROM_DEVICE);
		ret = 0;
		break;
	}

	case LX_MJPEG_CMD_DECODE_GET_CURRENT_COORD: {
		LX_MJPEG_DEC_GET_CUR_COORD_T stParam;
		UINT16 x = 0, y = 0;

		MJPEG_DEC_GetCurrentCoordinate(&x, &y);

		stParam.x = x;
		stParam.y = y;

		memcpy((void *)&(stCmdParam->param.dec_coord), (void *)&stParam,
			   sizeof(LX_MJPEG_DEC_GET_CUR_COORD_T));
		bUserCopy = TRUE;
		break;
	}

	default:
		MJPEG_ERROR("!!\n");
		break;
	}

	if (bUserCopy) {
		ret = copy_to_user((void __user *)arg, (void *)stCmdParam,
						   sizeof(LX_MJPEG_GENERAL_CMD_PARAM_T));
	}

exit:
	if (stCmdParam)
		OS_KFree(stCmdParam);

	return ret;
}

static int MJPEG_Process_Command(struct file *filp, MJPEG_DEVICE_T *my_dev,
								 unsigned long arg)
{
	int ret = -EFAULT;
	struct driver_priv *priv = filp->private_data;

	LX_MJPEG_GENERAL_CMD_PARAM_T *stCmdParam = NULL;
	LX_MJPEG_COPY_FROM_USER(LX_MJPEG_GENERAL_CMD_PARAM_T, stCmdParam, arg, ret);

	switch (stCmdParam->command) {
	case LX_MJPEG_CMD_SW_RESET:
	case LX_MJPEG_CMD_USE_QUEUE:
	case LX_MJPEG_CMD_STOP_READ:
	case LX_MJPEG_CMD_CLEAR_INTR:
		ret = MJPEG_Process_CommandGeneral(my_dev, arg);
		break;

	case LX_MJPEG_CMD_DECODE_INIT: {
		LX_MJPEG_DEC_INIT_PARAM_T *stInitParam = NULL;
		LX_MJPEG_COPY_PARAM(LX_MJPEG_DEC_INIT_PARAM_T, stInitParam,
							stCmdParam->param.dec_init, ret);

		ret = get_hardware(priv);
		if (ret < 0) {
			OS_KFree(stInitParam);
			break;
		}

		//_SW_Reset();
		MJPEG_HwReset();

		memcpy((void *)&my_dev->stHeader, (void *)&stInitParam->stHeader,
			   sizeof(LX_MJPEG_HEADER_T));
		memcpy((void *)&my_dev->stImageBuffer, (void *)&stInitParam->stImageBuf,
			   sizeof(LX_MJPEG_IMAGE_BUF_T));
		memcpy((void *)&my_dev->stOption, &stInitParam->stOption,
			   sizeof(LX_MJPEG_OPTION_T));
		OS_KFree(stInitParam);

		my_dev->ui32OutputSize =
				MJPEG_DEC_Init(&my_dev->stHeader, &my_dev->stImageBuffer,
							   &my_dev->stOption, &my_dev->stImageInfo);

		if (my_dev->ui32OutputSize == 0) {
			MJPEG_ERROR("Can't calculate output image size\n");
			ret = -EIO;
			put_hardware(priv);
			break;
		}

		my_dev->ui32InputSize = 0;
		my_dev->bFirstBlock = TRUE;
		priv->dec_init = TRUE;
		break;
	}
	case LX_MJPEG_CMD_DECODE_START:
	case LX_MJPEG_CMD_DECODE_CONTINUE:
	case LX_MJPEG_CMD_DECODE_STOP:
	case LX_MJPEG_CMD_DECODE_CLEAR_DPB:
	case LX_MJPEG_CMD_DECODE_GET_CURRENT_COORD:
	case LX_MJPEG_CMD_DECODE_COPY_CACHE_DATA:
		if (priv->dec_init == FALSE) {
			MJPEG_ERROR("MJPEG_DEC_Init is not excuted\n");
			break;
		}
		ret = MJPEG_Process_CommandDecode(filp, my_dev, arg);
		break;

	default:
		MJPEG_ERROR("!!\n");
		break;
	}

exit:
	if (stCmdParam)
		OS_KFree(stCmdParam);
	return ret;
}

static int MJPEG_IoctlGeneral(struct file *filp, unsigned int cmd,
							  unsigned long arg, MJPEG_DEVICE_T *my_dev)
{
	int ret = 0;
	struct driver_priv *priv = filp->private_data;

	if (!priv) {
		MJPEG_ERROR("Memory is empty!! \n");
		return -ENOMEM;
	}

	switch (cmd) {
	case LX_MJPEG_IO_SW_RESET: {
		ret = get_hardware(priv);
		if (ret < 0)
			break;

		//_SW_Reset();
		MJPEG_HwReset();

		memset(&my_dev->stHeader, 0, sizeof(LX_MJPEG_HEADER_T));

		put_hardware(priv);

		break;
	}

	case LX_MJPEG_IOR_GET_CFG: {
		LX_MJPEG_CFG_T *mjpeg_cfg = MJPEG_GetCfg();

		if (NULL == mjpeg_cfg) {
			ret = RET_ERROR;
			break;
		}
		ret = copy_to_user((void __user *)arg, (void *)mjpeg_cfg,
						   sizeof(LX_MJPEG_CFG_T));
		break;
	}

	case LX_MJPEG_IOR_GET_BUFFER_INFO: {
		LX_MJPEG_MEM_BUF_T stParam;

		stParam.addr = priv->ui32Memory_base;
		stParam.length = priv->ui32Memory_size;

		ret = copy_to_user((void __user *)arg, (void *)&stParam,
						   sizeof(LX_MJPEG_MEM_BUF_T));
		break;
	}

	default: {
		/* redundant check but it seems more readable */
		ret = -ENOTTY;
	}
	}

	return ret;
}

/**
 * ioctl handler for MJPEG device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore
 * or spin lock.
 */

static long MJPEG_UnlockedIoctl(struct file *filp, unsigned int cmd,
								unsigned long arg)
{
	struct inode *inode = filp->f_path.dentry->d_inode;

	int err = 0, ret = 0;

	MJPEG_DEVICE_T *my_dev;
	struct cdev *cdev;
	struct driver_priv *priv = filp->private_data;

	/*
   * get current MJPEG device object
   */
	cdev = inode->i_cdev;
	my_dev = container_of(cdev, MJPEG_DEVICE_T, cdev);

	/*
   * check if IOCTL command is valid or not.
   * - if magic value doesn't match, return error (-ENOTTY)
   * - if command is out of range, return error (-ENOTTY)
   *
   * note) -ENOTTY means "Inappropriate ioctl for device.
   */
	if (_IOC_TYPE(cmd) != MJPEG_IOC_MAGIC) {
		MJPEG_WARN("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd));
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > MJPEG_IOC_MAXNR) {
		MJPEG_WARN("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd));
		return -ENOTTY;
	}

	/* TODO : add some check routine for your device */

	/*
   * check if user memory is valid or not.
   * if memory can't be accessed from kernel, return error (-EFAULT)
   */
	if (_IOC_DIR(cmd) & (_IOC_READ | _IOC_WRITE))
		err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));

	if (err) {
		MJPEG_WARN("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
				   _IOC_NR(cmd), (_IOC_DIR(cmd) & _IOC_READ) ? 'r' : '-',
				   (_IOC_DIR(cmd) & _IOC_WRITE) ? 'w' : '-', (void *)arg);
		return -EFAULT;
	}
	// MJPEG_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch (cmd) {
	case LX_MJPEG_IO_SW_RESET:
	case LX_MJPEG_IOR_GET_CFG:
	case LX_MJPEG_IOR_GET_BUFFER_INFO:
		ret = MJPEG_IoctlGeneral(filp, cmd, arg, my_dev);
		break;

	case LX_MJPEG_IOW_GENERAL_CMD:
		if (priv->mmaped == FALSE) {
			MJPEG_ERROR("MJPEG_MMAP is not excuted\n");
			break;
		}
		ret = MJPEG_Process_Command(filp, my_dev, arg);
		break;

	default: {
		/* redundant check but it seems more readable */
		ret = -ENOTTY;
	}
	}

	return ret;
}

#ifdef CONFIG_COMPAT
static long MJPEG_CompatIoctl(struct file *filp, unsigned int cmd,
							  unsigned long arg)
{
	long ret;

	switch (cmd) {
	case LX_MJPEG_IOR_DECODE_SEQUENCE_INIT: {
		LX_MJPEG_DEC_SEQ_PARAM_T arg_buf;

		ret = copy_from_user(&arg_buf, (void *)arg,
							 sizeof(LX_MJPEG_DEC_SEQ_PARAM_T));
		if (ret) {
			return -EINVAL;
		}

		arg_buf.stDataBuffer.virt_addr =
				(void *)(uintptr_t)arg_buf.stDataBuffer.compat_addr;

		ret = copy_to_user((void *)arg, &arg_buf,
						   sizeof(LX_MJPEG_DEC_SEQ_PARAM_T));
		if (ret) {
			return -EINVAL;
		}

		break;
	}

	default:
		break;
	}

	ret = MJPEG_UnlockedIoctl(filp, cmd, arg);

	return ret;
}
#endif

/**
 * memory mapping to virtual region
 *
 */
static int MJPEG_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret;
	UINT32 start;
	UINT32 len;
	UINT32 off = ((vma->vm_pgoff) << PAGE_SHIFT);
	struct driver_priv *priv = filp->private_data;

	if (!priv) {
		MJPEG_ERROR("Memory is empty!! \n");
		return -ENOMEM;
	}

	start = priv->ui32Memory_base & PAGE_MASK;
	len = PAGE_ALIGN((start & ~PAGE_MASK) + priv->ui32Memory_size);

	MJPEG_DEBUG("MMAP : start - %08x , len - %08x , off - %08x\n", start, len,
				off);

	if ((vma->vm_end - vma->vm_start + off) > len) {
		MJPEG_ERROR("ERROR : MJPEG_mmap leng is over\n");
		MJPEG_ERROR("start : %x end : %x offset : %x len : %x\n",
					(UINT32)vma->vm_start, (UINT32)vma->vm_end, off, len);
		return RET_INVALID_PARAMS;
	}

	off += start;
	MJPEG_DEBUG("%s:%d -- mmap : start - %08x , len - %08x , off - %08x\n",
				__F__, __L__, start, len, (UINT32)vma->vm_pgoff);

	MJPEG_DEBUG("%s:%d -- vma->vm_start: %lx , vma->vm_end: %lx, len: %ld\n",
				__F__, __L__, vma->vm_start, vma->vm_end,
				vma->vm_end - vma->vm_start);

	vma->vm_pgoff = off >> PAGE_SHIFT;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
	vm_flags_set(vma, VM_IO);
#else
	vma->vm_flags |= VM_IO;
#endif

	ret = io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
							 vma->vm_end - vma->vm_start, vma->vm_page_prot);

	if (ret >= 0) {
		priv->buf_len = len;
		priv->mmaped = TRUE;
		priv->page = phys_to_page(off);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0))
		priv->cache_addr = (unsigned long)memremap(off, len, MEMREMAP_WB);
		if (!priv->cache_addr) {
			MJPEG_ERROR("memremap failed 0x%x\n", off);
			return EINVAL;
		}
#else
		priv->cache_addr = vma->vm_start;
#endif
		MJPEG_DEBUG("%s:%d -- cached buf addr:%lx\n", __F__, __L__,
					priv->cache_addr);
	} else {
		MJPEG_ERROR("%s:%d -- io_remap_pfn_range fail!! (ret:%d)\n", __F__,
					__L__, ret);
	}

	return ret;
}

static ssize_t MJPEG_Read(struct file *file, char __user *data, size_t size,
						  loff_t *off)
{
	int ret = -EFAULT;
	int rc;
	UINT32 widx, ridx, count, wsize;
	int ret_size;

	rc = wait_event_interruptible(_gMJPEG_Intr.wq,
								  _gMJPEG_Intr.widx != _gMJPEG_Intr.ridx);
	if (rc != 0) {
		if (rc == -ERESTARTSYS) {
			if (freezing(current))
				MJPEG_NOTI("freezing in mjpeg read");
			else
				MJPEG_NOTI("signal is received in mjpeg read");
		} else {
			MJPEG_ERROR("Error(%d) in wait_event_interruptible\n", rc);
		}
		ret = rc;
		goto exit;
	}

	MJPEG_DEBUG("I wake up!!");

	mutex_lock(&_gMJPEG_Intr.lock);

	widx = _gMJPEG_Intr.widx;
	ridx = _gMJPEG_Intr.ridx;

	MJPEG_DEBUG("widx[%d] ridx[%d]\n", widx, ridx);

	/* there is no data. forbid false alarm */
	if (widx == ridx) {
		ret = -EAGAIN;
		goto exit;
	}

	if (widx < ridx) { /* wrap around */
		count = LX_MJPEG_MAX_INTR_DATA - ridx;
		wsize = sizeof(UINT32) * count;
		if (copy_to_user((void __user *)data, (void *)&_gMJPEG_Intr.intr[ridx],
						 wsize)) {
			MJPEG_ERROR("copy_to_user\n");
			goto exit;
		}
		ret_size = wsize;

		if (widx > 0) {
			data += sizeof(UINT32) * count;
			wsize = sizeof(UINT32) * widx;
			if (copy_to_user((void __user *)data, (void *)&_gMJPEG_Intr.intr[0],
							 wsize)) {
				MJPEG_ERROR("copy_to_user\n");
				goto exit;
			}

			ret_size += wsize;
		}
	} else {
		count = widx - ridx;
		wsize = sizeof(UINT32) * count;
		if (copy_to_user((void __user *)data, (void *)&_gMJPEG_Intr.intr[ridx],
						 wsize)) {
			MJPEG_ERROR("copy_to_user\n");
			goto exit;
		}
		ret_size = wsize;
	}

	_gMJPEG_Intr.ridx = widx;

	ret = ret_size;

exit:
	mutex_unlock(&_gMJPEG_Intr.lock);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", MJPEG_Init);
#else
module_init(MJPEG_Init);
#endif
module_exit(MJPEG_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("mjpeg driver");
MODULE_LICENSE("GPL");
#endif

/** @} */
