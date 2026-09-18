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

#include "ucom_m23_common.h"

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
static OS_SEM_T			ucom_mutex;

#define KDRV_UCOM_LOCK_INIT()		OS_InitMutex(&ucom_mutex, OS_SEM_ATTR_DEFAULT)
#define KDRV_UCOM_LOCK()                      \
    do{                                             \
        if(OS_LockMutex(&ucom_mutex) < 0)             \
        {                                           \
            KDRV_UCOM_ERROR("Mutex Lock Fail\n");   \
            return -1;                              \
        }                                           \
    }while(0)

#define KDRV_UCOM_UNLOCK()                    \
    do{                                             \
        OS_UnlockMutex(&ucom_mutex);                  \
    }while(0)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

static void m23_ucom_init(void);
static void m23_ucom_chipreset(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int m23_ucom_enable = 1;
static int m23_ucom_inited = 0;

module_param(m23_ucom_enable, int, S_IRUGO);
MODULE_PARM_DESC(m23_ucom_enable, "ucom enable");

static ucom_m23_func_t* ucom_m23_func = NULL;
extern void __iomem *m23_micom_eeprom_base;

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
int m23_ucom_ioctl_main (unsigned int cmd, unsigned long arg, struct file *file);
struct file * m23_ucom_getfp(void);


/**
 * ioctl handler for micom device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

int m23_ucom_ioctl_main (unsigned int cmd, unsigned long arg, struct file *file)
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

			KDRV_UCOM_LOCK();
			ret = ucom_m23_func->write(&param);
			KDRV_UCOM_UNLOCK();
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

			KDRV_UCOM_LOCK();
			ret = ucom_m23_func->read(&param);
			KDRV_UCOM_UNLOCK();

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
			m23_ucom_init();
			return ret;
		}
			break;
		case UCOM_CHIPRESET:
		{
			KDRV_UCOM_DEBUG("ioctl: UCOM_CHIPRESET\n");
			KDRV_UCOM_LOCK();
			m23_ucom_chipreset();
			KDRV_UCOM_UNLOCK();
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

static int m23_ucom_ioctl (unsigned int cmd, unsigned long arg, struct file *file)
{
	int ret = 0;

	if ((_IOC_TYPE(cmd) != UCOM_IOC_MAGIC) )
		return -EINVAL;
	if(m23_get_micom_disable() == 1)
	{
		KDRV_UCOM_DEBUG("skip micom[%d]\n",m23_get_micom_disable());
		return 0;
	}
	ret = m23_ucom_ioctl_main(cmd, arg, file);

    return ret;
}

static int m23_ucom_suspend(void)
{
	printk("ucom suspend[%d]\n",m23_get_micom_disable());

	return 0;
}

static int m23_ucom_resume(void)
{
	//unsigned int reg = 0;
	m23_set_micom_disable(0);
	printk("ucom resume[%d]\n",m23_get_micom_disable());

	/* to make mainsoc access eeprom */
	#if 0
	if(m23_micom_eeprom_base != NULL){
		reg = readl(m23_micom_eeprom_base);
		reg = reg &(~0xf0f0) ;
		reg = reg | 0x2020; /* micom i2c enable */
		writel(reg, m23_micom_eeprom_base );
	}
	#endif


	return 0;
}


struct file * m23_ucom_getfp(void)
{
	return g_ucomfp;
}


static void m23_ucom_init(void)
{
	/* initialize micom control base */

	if(m23_ucom_inited == 0)
	{
		KDRV_UCOM_LOCK_INIT();
		ucom_m23_func = get_m23_ucom_func();
		ucom_m23_func->init();
		m23_ucom_inited = 1;
	}

	return;
}

static void m23_ucom_chipreset(void)
{
	ucom_m23_func = get_m23_ucom_func();
	ucom_m23_func->chipreset();
	return;
}
static ucom_driver_t m23_ucom_driver =
{
	.init = m23_ucom_init,
	.ioctl = m23_ucom_ioctl,
	.suspend = m23_ucom_suspend,
	.resume = m23_ucom_resume,
	.getfp = m23_ucom_getfp,
};

ucom_driver_t* get_m23_ucom_driver(void)
{
	return &m23_ucom_driver;
}

