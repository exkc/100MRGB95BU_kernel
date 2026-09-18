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


/** @file
 *
 *  emulator driver for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-03-29
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/slab.h>

#include "logm_kapi.h"

#include "te_emul.h"
#include "te_emul_regs.h"

#include "proc.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define TE_EMUL_NAME		"te_emul"

#define EMUL_LOG(level,fmt,args...)	LOGM_PRINT(g_te_emul_logm_fd, LX_LOGM_LEVEL_##level, fmt, ##args)

#define LOG_ERROR(fmt,args...)		EMUL_LOG(ERROR, fmt, ##args)
#define LOG_WARNING(fmt,args...)	EMUL_LOG(WARNING, fmt, ##args)
#define LOG_NOTI(fmt,args...)		EMUL_LOG(NOTI, fmt, ##args)


#define IS_REG_ADDR(x)			((x) >= reg_addr_base && (x) < reg_addr_end)


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/
unsigned char *xemul_reg_base;

int	g_te_emul_logm_fd = -1;

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static UINT32 reg_addr_base;
static UINT32 reg_addr_end;
static struct task_struct *thread;


int XEMUL_LOG_Write(const char *fmt, ...)
{
	va_list	args;
	char	*str;
	int		n;
	int		len = 1024;

	while(1)
	{
		str = kmalloc(len, GFP_ATOMIC);
		if(!str) return -ENOMEM;

		va_start (args, fmt);
		n = vsnprintf(str, len, fmt, args);
		va_end (args);

		if(n < len)
		{
			LOG_NOTI("%s", str);
			kfree(str);
			break;
		}

		kfree(str);
		len <<= 1;
	}

	return n;
}

void XEMUL_MCU_IrqRequest(int num, void (*handler)(void))
{
	TE_EMUL_MCU_IrqRequest(num, handler);
}

void XEMUL_MCU_EnableIrq(unsigned int mask)
{
	TE_EMUL_MCU_EnableIrq(mask);
}

void XEMUL_MCU_DisableIrq(unsigned int mask)
{
	TE_EMUL_MCU_DisableIrq(mask);
}

void XEMUL_DataWrite(UINT32 addr, UINT32 value)
{
//	printk("%s(addr=0x%08x,value=0x%x)\n", __FUNCTION__, addr, value);

	if(IS_REG_ADDR(addr))
	{
		TE_EMUL_RegWrite(addr, value);
	}
	else
	{
		MEM_WRITE32(addr, value);
	}
}

UINT32 XEMUL_DataRead(UINT32 addr)
{
	UINT32 val;

	if(IS_REG_ADDR(addr))
	{
		TE_EMUL_RegRead(addr, &val);
	}
	else
	{
		val = MEM_READ32(addr);
	}

	return val;
}

static int thread_func(void *unused)
{
	extern int mcu_main(void);

	mcu_main();

	return 0;
}

static void init_logm(void)
{
	g_te_emul_logm_fd = LOGM_ObjRegister(TE_EMUL_NAME);

	LOGM_ObjBitMaskEnable(g_te_emul_logm_fd, LX_LOGM_LEVEL_ERROR);
	LOGM_ObjBitMaskEnable(g_te_emul_logm_fd, LX_LOGM_LEVEL_WARNING);
	LOGM_ObjBitMaskEnable(g_te_emul_logm_fd, LX_LOGM_LEVEL_NOTI);
}

static int init(void)
{
	printk("initialize TE mcu emulator\n");

	init_logm();

	proc_init();

	xemul_reg_base	= g_te_emul_reg_base;

	reg_addr_base	= (UINT32)g_te_emul_reg_base;
	reg_addr_end	= (UINT32)g_te_emul_reg_base + g_te_emul_reg_size;

	printk("reg addr(0x%08x--0x%08x)\n", reg_addr_base, reg_addr_end);

	thread = kthread_create(thread_func, NULL, "mcu_emul");
	if(!thread)
	{
		printk("can't create thread\n");
		return -EIO;
	}
	kthread_bind(thread, MCU_KTHREAD_CPU_ID);

	wake_up_process(thread);

	return 0;
}

static void cleanup(void)
{
	kthread_stop(thread);

	proc_cleanup();

	LOGM_ObjDeregister(TE_EMUL_NAME);
}



module_init(init);
module_exit(cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("LG TE mcu emulator driver");
MODULE_LICENSE("GPL");

