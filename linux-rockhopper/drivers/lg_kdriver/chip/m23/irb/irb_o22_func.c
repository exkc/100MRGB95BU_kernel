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
 *  author		hankyung.yu (hankyung.yu@lge.com)
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

#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/delay.h>

#include <generated/uapi/linux/version.h>
#include <linux/clk.h>

#include "irb_o22common.h"
#include "irb_drv.h"
#include "reg_ctrl.h"

#define IRB_KEY_MAX_SIZE	511
#define	IRB_MAX_MBOX_BYTE	32
#define	IRB_MAX_MBOX_WORD	(IRB_MAX_MBOX_BYTE / 4)

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

static void __iomem *a2m_ipc_base = NULL;
static void __iomem *m2a_ipc_base = NULL;
static void __iomem *a2m_irq_base = NULL;
static void __iomem *m2a_irq_base = NULL;
static void __iomem *irb_key_base = NULL;


void o22_irb_funcInit(void)
{

	KDRV_IRB_DEBUG("o22_irb init\n");
	m2a_ipc_base = ioremap(0xF0004100, 0x80);
	m2a_irq_base = ioremap(0xF0004180, 0x4);
	a2m_ipc_base = ioremap(0xF0004200, 0x80);
	//a2m_irq_base = ioremap(0xF000428c, 0x4);
	/* irq noti :requested by micom fw */
	a2m_irq_base = ioremap(0xFD3004CC, 0x4);

	irb_key_base = ioremap(0xF101b800, 0x7fc);
}

int o22_irb_tx(LX_IRB_PARAM_T * param)
{
	UINT32	micomcmd[5]	= {0,};
	UINT32 * pbuf = NULL;
	UINT32 * mbuf = NULL;
	UINT32 i=0,index=0,midx=0;

	/*  busy status is same in o22  checked by micom engineer 210428*/
	if (readl(a2m_ipc_base + 0x44))
	{
  		KDRV_IRB_NOTI("irb busy\n");
		return -1;
	}

	//micomcmd[0] = 0 ; /* status by micom  */
	micomcmd[1] = param->carrierFrequency ; /* carrier freq  */
	micomcmd[2] = param->dutyCycle ; /* duty  */
	/* only handle MakeTimes */
	micomcmd[3] = param->numMakeTimes;

	//micomcmd[3] = param->numCharTimes + param->numMakeTimes +
	//	param->numReapeatTimes + param->numBreakTimes; /* total size */


	if(micomcmd[3] > IRB_KEY_MAX_SIZE)
	{
  		KDRV_IRB_NOTI("check irb size %d\n",micomcmd[3]);
		return -1;
	}

	mbuf = kmalloc(param->numMakeTimes*4 , GFP_KERNEL);

	if(mbuf == NULL ){
	  	KDRV_IRB_NOTI("check malloc\n");
		return -1;
	}

	memset((UINT8 *)mbuf,0x0,param->numMakeTimes*4);


	if( param->numMakeTimes)
	{
		index = param->numMakeTimes;
		pbuf = (UINT32 *)param->maketime;


		for(i = 0; i < index ; i++)
		{
			if(pbuf[i] != 0)
			{
				mbuf[midx++] = pbuf[i];
			}
			else if((pbuf[i] == 0 && i < 2) ||( pbuf[i] == 0 && pbuf[i+1] == 0))
			{
  				KDRV_IRB_NOTI("check maketime \n");
				if(mbuf)
				kfree(mbuf);
				return -1;
			}
			else if( (i > 1 ) && (i+1 < param->numMakeTimes) && pbuf[i] == 0 && pbuf[i+1] != 0 )
			{
				mbuf[midx-1] = mbuf[midx-1] + pbuf[i+1];
  				KDRV_IRB_NOTI("zero maketime \n");
				i++;
			}
		}
	}


	if(midx)
	{
		index = midx;
		pbuf = (UINT32 *)mbuf;
		for(i = 0; i < index ; i++)
		{
  			KDRV_IRB_DEBUG("make[%d]=[%d]\n",i,pbuf[i]);
			/*  normal delay is requested by micom fw 210428*/
			writel(pbuf[i], irb_key_base + 4*i);
		}
	}
	else
	{
  		KDRV_IRB_NOTI("check irb makesize\n");
		if(mbuf)
			kfree(mbuf);
		return -1;
	}

	micomcmd[3] = index;
	micomcmd[4] = 0xf101b800; /* make store location */

	for(i = 1; i < 5 ; i++)
		writel(micomcmd[i] , a2m_ipc_base + 0x44 + 4*i);

	/* noti to micom */
	writel(1, a2m_irq_base);

	/*  no done clear  in o22  checked by micom engineer 210428*/

	KDRV_IRB_DEBUG("o22_irb tx makenum[%x] pbuf[%x]\n",
		midx,pbuf[0]);
	if(mbuf)
		kfree(mbuf);
	return 0;
}


void o22_irb_funcReInit(void)
{

  KDRV_IRB_NOTI("o22_irb reinit\n");
}
void o22_irb_exit(void)
{
  KDRV_IRB_DEBUG("o22_irb end\n");
}


static irbs_o22_func_t o22_irb_func =
{
	.init = o22_irb_funcInit,
	.reinit = o22_irb_funcReInit,
	.tx = o22_irb_tx,
	.exit = o22_irb_exit,
};

irbs_o22_func_t* get_o22_irb_func(void)
{
	return &o22_irb_func;
}

