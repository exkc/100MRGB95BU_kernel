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
 *  main driver implementation for micom device.
 *	micom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2017.04.13
 *  note			Additional information.
 *
 *  @addtogroup lg1313_micom
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/platform_device.h>

#include <asm/uaccess.h>
#include <linux/poll.h>
#include "os_util.h"
#include "base_device.h"
#include "ucom_drv.h"
#include "ucom_core.h"

#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/cpu.h>
#include <linux/io.h>

#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/suspend.h>


#include <linux/tick.h>
#include <trace/events/power.h>

#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>

#include <generated/uapi/linux/version.h>

#include "ucom_o26_common.h"

#define UCOM_COPY_FROM_USER(d,s,l,_action) 						\
			do {												\
				if (copy_from_user((void*)d, (void *)s, l)) {	\
					KDRV_UCOM_ERROR("ioctl: copy_from_user\n");	\
					_action; 									\
				}												\
			} while(0)

#define UCOM_COPY_TO_USER(d,s,l,_action)							\
			do {												\
				if (copy_to_user((void*)d, (void *)s, l)) { 	\
					KDRV_UCOM_ERROR("ioctl: copy_to_user [%p]<=[%p] [%x]\n",d,s,l );	\
					_action; 									\
				}												\
			} while(0)



/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
OS_SEM_T			o26_ucom_mutex;


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

static void o26_ucom_init(void);
static void o26_ucom_chipreset(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int o26_ucom_enable = 1;
static int o26_ucom_inited = 0;

module_param(o26_ucom_enable, int, S_IRUGO);
MODULE_PARM_DESC(o26_ucom_enable, "ucom enable");

static ucom_o26_func_t* ucom_o26_func = NULL;
extern void __iomem *o26_micom_eeprom_base;

extern UINT16 o26_ucomkey;
extern UINT32 o26_ucom_abnormal;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

int o26_ucom_ioctl_main (unsigned int cmd, unsigned long arg, struct file *file);
struct file * o26_ucom_getfp(void);
/**
 * ioctl handler for micom device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

int o26_ucom_ioctl_main (unsigned int cmd, unsigned long arg, struct file *file)
{
	int ret = 0;
	UINT8	sbuf[100];
	UINT8*	kbuf;
	UINT8*	ubuf;

	switch (cmd)
	{
		case UCOM_IOW_COMMAND_SET:
		{
			LX_UCOM_PARAM_T	param;
			UCOM_COPY_FROM_USER(&param, arg, sizeof(LX_UCOM_PARAM_T), return -EFAULT);
			ubuf = param.ubuf;
			kbuf = sbuf;
			KDRV_UCOM_DEBUG("DATA W cmd:%x  %x\n",cmd, param.bufSize);
			if( param.bufSize > 0)
			{
				UCOM_COPY_FROM_USER(kbuf, (void __user *)ubuf, param.bufSize, return -EFAULT);
			}
			param.ubuf = kbuf;

			O26_KDRV_UCOM_LOCK();
			ret = ucom_o26_func->write(&param);
			O26_KDRV_UCOM_UNLOCK();
			if (ret < 0)
				KDRV_UCOM_DEBUG("check ukdrv SET[%x]\n",param.Cmd);
			return ret;
		}
			break;
		case UCOM_IORW_COMMAND_GET:
		{
			LX_UCOM_PARAM_T	param;

			UCOM_COPY_FROM_USER(&param, arg, sizeof(LX_UCOM_PARAM_T), return -EFAULT);
			ubuf = param.ubuf;
			kbuf = sbuf;
			param.ubuf = kbuf;

			O26_KDRV_UCOM_LOCK();
			ret = ucom_o26_func->read(&param);
			O26_KDRV_UCOM_UNLOCK();

			if(ret >= 0)
			{
				UCOM_COPY_TO_USER((void __user *)ubuf, (void*)kbuf, param.bufSize, return -EFAULT);
			}
			else
				KDRV_UCOM_DEBUG("check ukdrv GET[%x]\n",param.Cmd);

		 	return ret;
		}
			break;
		case UCOM_INIT:
		{
			KDRV_UCOM_NOTI("ioctl: UCOM_INIT\n");
			o26_ucom_init();
			return ret;
		}
			break;
		case UCOM_CHIPRESET:
		{
			KDRV_UCOM_DEBUG("ioctl: UCOM_CHIPRESET\n");
			O26_KDRV_UCOM_LOCK();
			o26_ucom_chipreset();
			O26_KDRV_UCOM_UNLOCK();
			return ret;
		}
			break;
		default:
		{
			KDRV_UCOM_ERROR("%s %d check cmd %x\n", __func__,__LINE__,cmd);
			ret = -EINVAL;
			return ret;
		}
			break;
	}
	return ret;
}

static int o26_ucom_ioctl (unsigned int cmd, unsigned long arg, struct file *file)
{
	int ret = 0;

	if ((_IOC_TYPE(cmd) != UCOM_IOC_MAGIC) )
		return -EINVAL;
	if(o26_get_micom_disable() == 1)
	{
		KDRV_UCOM_DEBUG("skip micom[%d]\n",o26_get_micom_disable());
		return 0;
	}
	ret = o26_ucom_ioctl_main(cmd, arg, file);

    return ret;
}

static int o26_ucom_suspend(void)
{
	printk("ucom suspend[%d]\n",o26_get_micom_disable());

	return 0;
}

static int o26_ucom_resume(void)
{
	unsigned int reg = 0;

	o26_ucomkey = 0;
	o26_ucom_abnormal = 0;
	o26_set_micom_disable(0);
	printk("ucom resume[%d]\n",o26_get_micom_disable());

	/* to make mainsoc access eeprom */
	if(o26_micom_eeprom_base != NULL){
		reg = readl(o26_micom_eeprom_base);
		reg = reg &(~0x0000f0f0) ;
		reg = reg | 0x00003030;
		writel(reg, o26_micom_eeprom_base );
		writel(reg, o26_micom_eeprom_base );
	}


	return 0;
}


struct file * o26_ucom_getfp(void)
{
	return g_ucomfp;
}


static void o26_ucom_init(void)
{
	/* initialize micom control base */

	if(o26_ucom_inited == 0)
	{
		O26_KDRV_UCOM_LOCK_INIT();
		ucom_o26_func = get_o26_ucom_func();
		ucom_o26_func->init();
		o26_ucom_inited = 1;
	}

	return;
}

static void o26_ucom_chipreset(void)
{
	ucom_o26_func = get_o26_ucom_func();
	ucom_o26_func->chipreset();
	return;
}
static ucom_driver_t o26_ucom_driver =
{
	.init = o26_ucom_init,
	.ioctl = o26_ucom_ioctl,
	.suspend = o26_ucom_suspend,
	.resume = o26_ucom_resume,
	.getfp = o26_ucom_getfp,
	.spiread = o26_ucom_spi_read,
	.spiwrite = o26_ucom_spi_write,
};

ucom_driver_t* get_o26_ucom_driver(void)
{
	return &o26_ucom_driver;
}

