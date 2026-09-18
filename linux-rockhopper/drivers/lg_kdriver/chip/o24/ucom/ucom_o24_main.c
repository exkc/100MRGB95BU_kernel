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
//#include "gpio_core.h"

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

#include "ucom_o24_common.h"

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

OS_SEM_T			o24_ucom_mutex;


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

static void o24_ucom_init(void);
static void o24_ucom_chipreset(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int o24_ucom_enable = 1;
static int o24_ucom_inited = 0;

module_param(o24_ucom_enable, int, S_IRUGO);
MODULE_PARM_DESC(o24_ucom_enable, "ucom enable");

static ucom_o24_func_t* ucom_o24_func = NULL;
extern void __iomem *o24_micom_eeprom_base;

extern UINT16 ucomkey;
extern UINT32 ucom_abnormal;

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


/**
 * ioctl handler for micom device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

int o24_ucom_ioctl_main (unsigned int cmd, unsigned long arg, struct file *file)
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

			O24_KDRV_UCOM_LOCK();
			ret = ucom_o24_func->write(&param);
			O24_KDRV_UCOM_UNLOCK();
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

			O24_KDRV_UCOM_LOCK();
			ret = ucom_o24_func->read(&param);
			O24_KDRV_UCOM_UNLOCK();

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
			o24_ucom_init();
			return ret;
		}
			break;
		case UCOM_CHIPRESET:
		{
			KDRV_UCOM_DEBUG("ioctl: UCOM_CHIPRESET\n");
			O24_KDRV_UCOM_LOCK();
			o24_ucom_chipreset();
			O24_KDRV_UCOM_UNLOCK();
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

static int o24_ucom_ioctl (unsigned int cmd, unsigned long arg, struct file *file)
{
	int ret = 0;

	if ((_IOC_TYPE(cmd) != UCOM_IOC_MAGIC) )
		return -EINVAL;
	if(o24_get_micom_disable() == 1)
	{
		KDRV_UCOM_DEBUG("skip micom[%d]\n",o24_get_micom_disable());
		return 0;
	}
	ret = o24_ucom_ioctl_main(cmd, arg, file);

    return ret;
}

static int o24_ucom_suspend(void)
{
	printk("ucom suspend[%d]\n",o24_get_micom_disable());

	return 0;
}

static int o24_ucom_resume(void)
{
	unsigned int reg = 0;

	ucomkey = 0;
	ucom_abnormal = 0;
	o24_set_micom_disable(0);
	printk("ucom resume[%d]\n",o24_get_micom_disable());

	/* to make mainsoc access eeprom */
	if(o24_micom_eeprom_base != NULL){
		reg = readl(o24_micom_eeprom_base);
		reg = reg &(~0xf0f00000) ;
		reg = reg | 0x30300000;
		writel(reg, o24_micom_eeprom_base );
	}


	return 0;
}


struct file * o24_ucom_getfp(void)
{
	return g_ucomfp;
}

static void o24_ucom_init(void)
{
	/* initialize micom control base */

	if(o24_ucom_inited == 0)
	{
		O24_KDRV_UCOM_LOCK_INIT();
		ucom_o24_func = get_o24_ucom_func();
		ucom_o24_func->init();
		o24_ucom_inited = 1;
	}
	return;
}

static void o24_ucom_chipreset(void)
{
	ucom_o24_func = get_o24_ucom_func();
	ucom_o24_func->chipreset();
	return;
}
static ucom_driver_t o24_ucom_driver =
{
	.init = o24_ucom_init,
	.ioctl = o24_ucom_ioctl,
	.suspend = o24_ucom_suspend,
	.resume = o24_ucom_resume,
	.getfp = o24_ucom_getfp,
	.spiread = o24_ucom_spi_read,
	.spiwrite = o24_ucom_spi_write,
};

ucom_driver_t* get_o24_ucom_driver(void)
{
	return &o24_ucom_driver;
}

