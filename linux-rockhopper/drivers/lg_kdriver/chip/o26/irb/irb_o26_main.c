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
 *  main driver implementation for irb device.
 *	irb device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1313_irb
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
#include "irb_drv.h"
#include "irb_core.h"
#include "gpio_core.h"

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

#include "irb_o26common.h"

#define IRB_COPY_FROM_USER(d,s,l,_action)                                              \
    do {                                                                                            \
	if (copy_from_user((void*)d, (void *)s, l)) {   \
	    KDRV_IRB_ERROR("ioctl: copy_from_user\n");     \
	    _action;                                                                        \
	}                                                                                               \
    } while(0)

#define IRB_COPY_TO_USER(d,s,l,_action)                                                        \
    do {                                                                                            \
	if (copy_to_user((void*)d, (void *)s, l)) {     \
	    KDRV_IRB_ERROR("ioctl: copy_to_user [%p]<=[%p] [%x]\n",d,s,l );        \
	    _action;                                                                        \
	}                                                                                               \
    } while(0)


/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
#define IRB_USE_KERNEL_FUNC

#undef IRB_DEBUG_PRINT_ENABLE
#ifdef IRB_DEBUG_PRINT_ENABLE
#define IRB_DEBUG_PRINT(fmt, args...)		do {printk(fmt, ##args);} while (0)
#else
#define IRB_DEBUG_PRINT(fmt, args...)		do{}while(0)
#endif
OS_SEM_T			o26_irb_mutex;

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/


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
  global Functions
  ---------------------------------------------------------------------------------------*/
static int o26_irbs_enable = 1;
static int o26_irb_inited = 0;

module_param(o26_irbs_enable, int, S_IRUGO);
MODULE_PARM_DESC(o26_irbs_enable, "o26 irbs disable");


static irbs_o26_func_t* irb_o26_func = NULL;
int o26_irb_ioctl_main (unsigned int cmd, unsigned long arg);

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

static void o26_irb_init(void);

/**
 * ioctl handler for irb device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o26_irb_ioctl_main (unsigned int cmd, unsigned long arg)
{

    int ret = 0;
    //unsigned char sbuf[4096];
    unsigned char* mbuf;
    unsigned char* kbuf;
    unsigned char* ubuf;

    switch (cmd)
    {
	case IRB_IOW_COMMAND_SET:
	    {
		LX_IRB_PARAM_T	param;
		KDRV_IRB_DEBUG("ioctlmain: IRB_SET\n");

		IRB_COPY_FROM_USER(&param, arg, sizeof(LX_IRB_PARAM_T), return -EFAULT);
		ubuf = param.maketime;
		mbuf = kmalloc(4096, GFP_KERNEL);
		if(mbuf == NULL){
		    KDRV_IRB_NOTI("check malloc\n");
		    return -1;
		}
		kbuf = mbuf;

		if (copy_from_user((void*)kbuf, (void __user *)ubuf, param.numMakeTimes*4)) {
			KDRV_IRB_ERROR("ioctl: copy_from_user\n");
			if(kbuf != NULL)
				kfree(kbuf);
			return -EFAULT;
		}

		param.maketime = kbuf;
		O26_KDRV_IRB_LOCK();
		ret = irb_o26_func->tx(&param);
		O26_KDRV_IRB_UNLOCK();
		if(mbuf != NULL)
		    kfree(mbuf);

		if (ret < 0)
		    KDRV_IRB_DEBUG("check ikdrv SET\n");
		return ret;
	    }
	case IRB_INIT:
	    {
		KDRV_IRB_NOTI("ioctlmain: IRB_INIT\n");
		o26_irb_init();
		return ret;
	    }

	default:
	    KDRV_IRB_ERROR("%s %d check cmd %x\n", __func__,__LINE__,cmd);
	    ret = -EINVAL;
	    return ret;
    }

    return ret;
}

static int o26_irb_ioctl (unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	if ((_IOC_TYPE(cmd) != IRB_IOC_MAGIC) )
	{
		return -EINVAL;
	}

	if(o26_get_micom_disable() == 1)
	{
		KDRV_IRB_DEBUG("skip micom[%d]\n",o26_get_micom_disable());
		return -1;
	}

	ret = o26_irb_ioctl_main(cmd, arg);

	return ret;
}

static int o26_irb_suspend(void)
{

    return 0;
}

static int o26_irb_resume(void)
{
    irb_o26_func = get_o26_irb_func();
    irb_o26_func->reinit();

    return 0;
}


static void o26_irb_init(void)
{
    /* initialize irbs control base */

    if(o26_irb_inited == 0)
    {
		O26_KDRV_IRB_LOCK_INIT();
		irb_o26_func = get_o26_irb_func();
		irb_o26_func->init();
		o26_irb_inited = 1;
    }

    return;
}

static irbs_driver_t o26_irbs_driver =
{
    .init = o26_irb_init,
    .ioctl = o26_irb_ioctl,
    .suspend = o26_irb_suspend,
    .resume = o26_irb_resume,
};

irbs_driver_t* get_o26_irb_driver(void)
{
    return &o26_irbs_driver;
}

