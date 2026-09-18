/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  main configuration file for lgbus device
 *	lgbus device will teach you how to make device driver with new platform.
 *
 *  author		hwang.hayun@lge.com
 *  version		1.0
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus_mpro
 *	@{
 */


/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/vmalloc.h>
#include <linux/kmod.h>

#include "os_util.h"
#include "sys_regs.h"

#include "lgbus_drv.h"
#include "lgbus_hw.h"
#include "lgbus_cfg.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Macro Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */

#define MPRO_ISR_ENABLE_OFFSET 		(0x4)
#define MPRO_ISR_STATUS_OFFSET 		(0x8)
#define MPRO_ISR_CLEAR_OFFSET 		(0xc)
#define MPRO_SLOT_ENABLE_OFFSET		(0x24)
#define MPRO_RANGE_OFFSET			(0x28)
#define MPRO_VIO_OFFSET				(0x40)


#define MPRO_ISR_ENABLE 			(0xC000)
#define MPRO_ISR_CLEAR 				(0xC000)
#define MPRO_ISR_STATUS 			(0xC000)
#define MPRO_ISR_STATUS_WR 			(0x8000)
#define MPRO_ISR_STATUS_RD 			(0x4000)

#define LBUS_QOS_CMN_BASE0			(0xC40F0400)//N
#define LBUS_QOS_CMN_BASE1			(0xC40F0000)//S
#define	LBUS_QOS_CMN_BASE2			(0xC40F0800)//FAST

#define mpro_reg_read(addr)				__raw_readl((void*)(addr))
#define mpro_reg_write(val,addr)		__raw_writel(val, (void*)(addr))

#define error 		LGBUS_ERROR

#define CHECK_RET(x, __if_action) { \
	__CHECK_IF_ERROR(x != 0, error, __if_action , "Error! [E = %d]\n", x);\
}
#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
	__CHECK_IF_ERROR(__checker, error, __if_action , fmt, ##args )

#define COLOR_NONE		"\x1b[0m"
#define COLOR_RED		"\x1b[1;31m"

#define HEX9_4_STR		"0x%01llx_%04llx_%04llx"
#define HEX9_4_VAL(x)	(x >> 32),((x>>16)&0xffff),(x&0xffff)

#define LGBUS_MPRO_CTRL_LOCK()		do{ spin_lock_irqsave(&lgbus_mpro_ctrl_lock, flag);}while(0)
#define LGBUS_MPRO_CTRL_UNLOCK()	do{ spin_unlock_irqrestore(&lgbus_mpro_ctrl_lock, flag);}while(0)

#define DEBUG_LEVEL     3
#define EVENT_LEVEL     4
#define RELEASE_LEVEL   5
/*----------------------------------------------------------------------------------------
  Type Definitions
----------------------------------------------------------------------------------------*/

//slot enable(slot_ctrl)
//[28] 1 : logic vs physical
//[16] 1 : stall
//[8] 1 : slot0 enable
//[4] 1 : slot1 enable
//[0] 1 : slot2 enable
typedef struct
{
	UINT32
	slot2_enable:1,		//0
				:3,		//1:3
	slot1_enable:1,		//4
				:3,		//5:7
	slot0_enable:1,		//8
				:7,		//9:15
	stall		:1,		//16
				:11,	//17:27
	logic		:1,		//28
				:3;		//29:31
}SLOT_CTRL_T;

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static int	user_mpro_cnt;
static ulong  o24_user_mpro[6] = { 0, 0, 0, 0, 0, 0 };
module_param_array(o24_user_mpro, ulong, &user_mpro_cnt, 0644);

static uint32_t platform_mode;
/*----------------------------------------------------------------------------------------
  External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int lgbus_mpro_init(void);
static int lgbus_mpro_cleanup(void);
static int lgbus_mpro_resume(void);
static int lgbus_mpro_suspend(void);
static int lgbus_mpro_request_irq(void);
static int lgbus_mpro_free_irq(void);
static int lgbus_mpro_isr_enable(void);
static int lgbus_mpro_isr_disable(void);
static int lgbus_mpro_ioremap(void);
static int lgbus_mpro_iounmap(void);
static int lgbus_mpro_get_range(void);
static irqreturn_t lgbus_mpro_isr(int irq, void *dev);
static int lgbus_mpro_regs_save(void);
static int lgbus_mpro_regs_restore(void);
static int lgbus_mpro_isr_enable_module(int i);
static void lgbus_mpro_user_mpro(void);

/* address switch */
static int lgbus_get_addr_switch(void);
static int lgbus_get_bwb(void);

/* lgbus memory protector proc functions */
static int lgbus_mpro_proc_init(void);
static int lgbus_mpro_proc_status_op(struct seq_file *s, void *data);
static int lgbus_mpro_proc_status_open(struct inode *inode, struct file *file);
static ssize_t lgbus_mpro_proc_status_write(struct file *file
        , const char __user *buf, size_t size, loff_t *off);
static ssize_t lgbus_mpro_proc_asw_write(struct file *file
        , const char __user *buf, size_t size, loff_t *off);

static int lgbus_mpro_proc_asw_op(struct seq_file *s, void *data);
static int lgbus_mpro_proc_asw_open(struct inode *inode, struct file *file);

/*----------------------------------------------------------------------------------------
  Static Variables
----------------------------------------------------------------------------------------*/

//memory protect, qos reg btop base address
static lgbus_o24_mpro_t mpro_ctrl[] =
{
	{"CORE",		0xCA201000},
	{"FAST",		0xCA201400},
	{"AXI_PERI",	0xCA200000},
	{"AHB_PERI",	0xCA202000},
	{"LZMA",		0xCA201200},
	{"GPU0",		0xC40F1000},
	{"GPU1",		0xC40F1200},
	{"GFX",			0xC40F1400},
	{"LOWBW",		0xC40F1600},
	{"ICODVENC",	0xC40F1800},
	{"MEFMS",		0xC40F1A00},
	{"FMC0_R",		0xC40F1C00},
	{"FMC0_W",		0xC40F1E00},
	{"FMC1_R",		0xC40F2000},
	{"FMC1_W",		0xC40F2200},
	{"FMGSSR",		0xC40F2400},
	{"CCO0",		0xC40F2600},
	{"CCO1",		0xC40F2800},
	{"ND0",			0xC40F2A00},
	{"ND1",			0xC40F2C00},
	{"VDOIMXW0",	0xC40F2E00},
	{"VDOIMXW1",	0xC40F3000},
	{"VDOIMXW2",	0xC40F3200},
	{"VDOIMXW3",	0xC40F3400},
	{"IMXR01",		0xC40F3600},
	{"IMXR23",		0xC40F3800},
	{"TCON",		0xC40F3A00},
	{"AUD",			0xC40F3C00},
	{"LNX0",		0xC40F3E00},
	{"LNX1",		0xC40F4000},
	{"LNX2",		0xC40F4200},
	{"VD0A",		0xC40F4400},
	{"VD0B",		0xC40F4600},
	{"VD1A",		0xC40F4800},
	{"VD1B",		0xC40F4A00},
	{"VD2VMCU",		0xC40F4C00},
	{"VD2B",		0xC40F4E00},
};

static ulong lbus_qos_cmn_base0;//N
static ulong lbus_qos_cmn_base1;//S
static ulong lbus_qos_cmn_base2;//FAST

static u32 isr_cnt_limit = 3;
module_param_named(o24_mpro_cnt_limit, isr_cnt_limit, int, 0644);

static u32 mpro_logic = 1;
module_param_named(o24_mpro_logic, mpro_logic, int, 0644);

static DEFINE_SPINLOCK(lgbus_mpro_ctrl_lock);
/*========================================================================================
    Implementation Group
========================================================================================*/
static void check_platform_mode(void)
{
	char mode[16];

	platform_mode = DEBUG_LEVEL;

	if(OS_ScanKernelCmdline("debugMode=%s", mode) == RET_OK)
	{
		platform_mode = mode[0] - '0';

		if(platform_mode < DEBUG_LEVEL)
			platform_mode = DEBUG_LEVEL;
		else if(platform_mode > RELEASE_LEVEL)
			platform_mode = DEBUG_LEVEL;
	}
}
static int lgbus_mpro_init(void)
{
	int ret = 0;

	check_platform_mode();

	ret = lgbus_get_addr_switch();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_get_bwb();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_ioremap();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_request_irq();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_get_range();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_proc_init();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_isr_enable();
	CHECK_RET(ret, goto func_exit);

	lgbus_mpro_user_mpro();

func_exit: /* control error */

	return ret;
}

static int lgbus_mpro_cleanup(void)
{
	lgbus_mpro_isr_disable();
	lgbus_mpro_free_irq();
	lgbus_mpro_iounmap();

	return 0;
}

static int lgbus_mpro_resume(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int ret;

	ret = lgbus_mpro_regs_restore();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_get_range();
	CHECK_RET(ret, goto func_exit);

	ret = lgbus_mpro_isr_enable();
	CHECK_RET(ret, goto func_exit);
	return 0;

func_exit:
	return ret;
#else
	return 0;
#endif
}

static int lgbus_mpro_suspend(void)
{
	lgbus_mpro_regs_save();
	return 0;
}

static int lgbus_mpro_get_range(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i,j;
	int ret = RET_ERROR;
	u64 start;
	u64 end;
	u32 slot_ctrl;
	u32 *ctrl_addr;
	u32 *range_addr;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");

		//slot enable(slot_ctrl)
		//[28] 1 : logic vs physical
		//[16] 1 : stall
		//[8] 1 : slot0 enable
		//[4] 1 : slot1 enable
		//[0] 1 : slot2 enable

		ctrl_addr = (u32 *)(mpro_ctrl[i].base_addr + MPRO_SLOT_ENABLE_OFFSET);
		slot_ctrl = mpro_reg_read(ctrl_addr);
		mpro_ctrl[i].slot_ctrl = slot_ctrl;

#if 0
		printk("mpro, addr_type:%s, stall:%s, slot[%s/%s/%s]\n"
									, ((SLOT_CTRL_T *)&slot_ctrl)->logic?"L":"P"
									, ((SLOT_CTRL_T *)&slot_ctrl)->stall?"o":"x"
									, ((SLOT_CTRL_T *)&slot_ctrl)->slot0_enable?"o":"x"
									, ((SLOT_CTRL_T *)&slot_ctrl)->slot1_enable?"o":"x"
									, ((SLOT_CTRL_T *)&slot_ctrl)->slot2_enable?"o":"x");
#endif

		range_addr = (u32 *)(mpro_ctrl[i].base_addr + MPRO_RANGE_OFFSET);
		for(j = 0; j < O24_MPRO_RANGE_SLOT_CNT; j++)
		{
			//BUS MPRO REG
			//[28:08] 21 : [32:12] start address
			//[28:08] 21 : [32:12] end address
			start	= (u64)((mpro_reg_read(range_addr++) >> 8) & 0x1FFFFF) << 12;
			end		= ((u64)((mpro_reg_read(range_addr++) >> 8) & 0x1FFFFF) << 12) | 0xFFF;
			if(end == 0xfff) end = 0x0;

			mpro_ctrl[i].range[j].start = start;
			mpro_ctrl[i].range[j].end = end;

			LGBUS_PRINT("[%-10s] mpro range(%d) "HEX9_4_STR" ~ "HEX9_4_STR"\n", mpro_ctrl[i].name
																, j
																, HEX9_4_VAL(mpro_ctrl[i].range[j].start)
																, HEX9_4_VAL(mpro_ctrl[i].range[j].end));
		}
	}
	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_regs_save(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i;
	int ret = RET_ERROR;
	u32 *save_addr;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		volatile u32 *src;
		volatile u32 *des;
		u32 size;
		u32 x;

		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");
		save_addr = (u32 *)(mpro_ctrl[i].base_addr + MPRO_SLOT_ENABLE_OFFSET);

		src = save_addr;
		des = (volatile u32 *)&(mpro_ctrl[i].reg_save);
		size = sizeof(lgbus_o24_mpro_reg_save_t) / sizeof(u32);

		for(x = 0; x < size; x++)
			des[x] = src[x];
	}
	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_regs_restore(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i;
	int ret = RET_ERROR;
	u32 *save_addr;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		volatile u32 *src;
		volatile u32 *des;
		u32 size;
		u32 x;

		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");
		save_addr = (u32 *)(mpro_ctrl[i].base_addr + MPRO_SLOT_ENABLE_OFFSET);

		des = save_addr;
		src = (volatile u32 *)&(mpro_ctrl[i].reg_save);
		size = sizeof(lgbus_o24_mpro_reg_save_t) / sizeof(u32);

		for(x = 0; x < size; x++)
			des[x] = src[x];
	}
	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}

#undef LBUS_IRQ
#define LBUS_IRQ			O24_IRQ_LBUS_QOS_CPU

#undef CPU_IRQ
#undef CPU_AXI_PERI_IRQ
#undef CPU_AHB_PERI_IRQ
#undef CPU_LZMA_IRQ
#undef CPU_FAST_IRQ
#define CPU_IRQ				O24_IRQ_QOS_CPU
#define CPU_AXI_PERI_IRQ	O24_IRQ_QOS_AXI_PERI
#define CPU_AHB_PERI_IRQ	O24_IRQ_QOS_AHB_PERI
#define CPU_LZMA_IRQ		O24_IRQ_QOS_LZMA
#define CPU_FAST_IRQ		O24_IRQ_QOS_CPU_FAST


static int lgbus_mpro_request_irq(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int ret;

	ret = request_irq(CPU_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(CPU_AXI_PERI_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_AXI_PERI_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(CPU_AHB_PERI_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_AHB_PERI_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(CPU_LZMA_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_LZMA_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(CPU_FAST_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_FAST", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(LBUS_IRQ, lgbus_mpro_isr, IRQF_SHARED, "LBUS_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	return 0;

func_exit:
	lgbus_mpro_free_irq();

	return ret;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_free_irq(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	free_irq(CPU_IRQ, (void*)&mpro_ctrl);
	free_irq(CPU_AXI_PERI_IRQ, (void*)&mpro_ctrl);
	free_irq(CPU_AHB_PERI_IRQ, (void*)&mpro_ctrl);
	free_irq(CPU_LZMA_IRQ, (void*)&mpro_ctrl);
	free_irq(CPU_FAST_IRQ, (void*)&mpro_ctrl);
	free_irq(LBUS_IRQ, (void*)&mpro_ctrl);
	return 0;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_isr_enable(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i;
	int ret = RET_ERROR;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	/* isr enable to active memory protector */
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		ulong addr = mpro_ctrl[i].base_addr + MPRO_ISR_ENABLE_OFFSET;
		uint32_t val;

		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");

		val = mpro_reg_read(addr);
		val |= MPRO_ISR_ENABLE;
		mpro_reg_write(val, addr);
		LGBUS_PRINT("[%-10s] addr : 0x%08lx, val : 0x%x\n"
											, mpro_ctrl[i].name
											, addr, val);
	}

	CHECK_ERROR(!lbus_qos_cmn_base0, goto func_exit, "base is null\n");
	CHECK_ERROR(!lbus_qos_cmn_base1, goto func_exit, "base is null\n");
	CHECK_ERROR(!lbus_qos_cmn_base2, goto func_exit, "base is null\n");

	mpro_reg_write(0xffffffff, lbus_qos_cmn_base0 + MPRO_ISR_ENABLE_OFFSET);
	mpro_reg_write(0xffffffff, lbus_qos_cmn_base1 + MPRO_ISR_ENABLE_OFFSET);
	mpro_reg_write(0xffffffff, lbus_qos_cmn_base2 + MPRO_ISR_ENABLE_OFFSET);

	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}

/* TODO: this function must call with LOCK */
static int lgbus_mpro_isr_enable_module(int i)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	ulong addr;
	uint32_t val;
	int ret = RET_ERROR;
	//ulong flag;

	//LGBUS_MPRO_CTRL_LOCK();
	/* isr disable to active memory protector */
	CHECK_ERROR(i >= ARRAY_SIZE(mpro_ctrl), goto func_exit, "Invalid param\n");

	CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");

	mpro_ctrl[i].isr_cnt = 0;

	addr = mpro_ctrl[i].base_addr + MPRO_ISR_ENABLE_OFFSET;
	val = mpro_reg_read(addr);
	val |= MPRO_ISR_ENABLE;
	mpro_reg_write(val, addr);
	LGBUS_PRINT("addr : 0x%08lx, val : 0x%x\n", addr, val);
	ret = RET_OK;

func_exit:
	//LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_isr_cnt_clear(void)
{
	int i;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();

	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		if(mpro_ctrl[i].isr_cnt)
		{
			lgbus_mpro_isr_enable_module(i);
			mpro_ctrl[i].isr_cnt = 0;
		}
	}

	LGBUS_MPRO_CTRL_UNLOCK();

	return RET_OK;
}

static int lgbus_mpro_isr_disable(void)
{
	int i;
	int ret = RET_ERROR;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	/* isr disable to active memory protector */
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		ulong addr = mpro_ctrl[i].base_addr + MPRO_ISR_ENABLE_OFFSET;
		uint32_t val;

		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");

		val = mpro_reg_read(addr);
		val &= (~((u32)MPRO_ISR_ENABLE));
		mpro_reg_write(val, addr);
		LGBUS_PRINT("addr : 0x%08lx, val : 0x%x\n", addr, val);
	}
	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
}

/* TODO: this function must call with LOCK */
static int lgbus_mpro_isr_disable_module(int i)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	ulong addr;
	uint32_t val;
	int ret = RET_ERROR;
	//ulong flag;

	//LGBUS_MPRO_CTRL_LOCK();
	/* isr disable to active memory protector */
	CHECK_ERROR(i >= ARRAY_SIZE(mpro_ctrl), goto func_exit, "Invalid param\n");

	CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");

	addr = mpro_ctrl[i].base_addr + MPRO_ISR_ENABLE_OFFSET;
	val = mpro_reg_read(addr);
	val &= (~((u32)MPRO_ISR_ENABLE));
	mpro_reg_write(val, addr);
	LGBUS_PRINT("addr : 0x%08lx, val : 0x%x\n", addr, val);
	ret = RET_OK;

func_exit:
	//LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_ioremap(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i;
	//ulong flag;

	//LGBUS_MPRO_CTRL_LOCK();
	/* ioremap : get virtual address */
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		/* at arm, ioremap == ioremap */
		mpro_ctrl[i].base_addr = (ulong)ioremap(mpro_ctrl[i].base_addr_phy, 0x200);

		LGBUS_PRINT("[%-10s] ioremap phy : 0x%08lx, addr : 0x%08lx\n", mpro_ctrl[i].name
										   , mpro_ctrl[i].base_addr_phy
										   , mpro_ctrl[i].base_addr);

		if(!mpro_ctrl[i].base_addr)
		{
			//LGBUS_MPRO_CTRL_UNLOCK();
			LGBUS_ERROR("fail ioremap\n");
			lgbus_mpro_iounmap();
			return RET_ERROR;
		}
	}

	lbus_qos_cmn_base0 = (ulong)ioremap(LBUS_QOS_CMN_BASE0, 0x200);
	lbus_qos_cmn_base1 = (ulong)ioremap(LBUS_QOS_CMN_BASE1, 0x200);
	lbus_qos_cmn_base2 = (ulong)ioremap(LBUS_QOS_CMN_BASE2, 0x200);

	if(!lbus_qos_cmn_base0 || !lbus_qos_cmn_base1 || !lbus_qos_cmn_base2)
	{
		//LGBUS_MPRO_CTRL_UNLOCK();
		LGBUS_ERROR("fail ioremap\n");
		lgbus_mpro_iounmap();
		return RET_ERROR;
	}

	//LGBUS_MPRO_CTRL_UNLOCK();
#endif
	return RET_OK;
}

static int lgbus_mpro_iounmap(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i;
	//ulong flag;

	//LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		if(mpro_ctrl[i].base_addr)
		{
			iounmap((void*)mpro_ctrl[i].base_addr);
			mpro_ctrl[i].base_addr = 0;

			LGBUS_PRINT("[%-10s] iounmap phy : 0x%08lx, addr : 0x%08lx\n", mpro_ctrl[i].name
																 	   , mpro_ctrl[i].base_addr_phy
																	   , mpro_ctrl[i].base_addr);
		}
	}

	if(lbus_qos_cmn_base0)
	{
		iounmap((void*)lbus_qos_cmn_base0);
		lbus_qos_cmn_base0 = 0;
	}
	if(lbus_qos_cmn_base1)
	{
		iounmap((void*)lbus_qos_cmn_base1);
		lbus_qos_cmn_base1 = 0;
	}
	if(lbus_qos_cmn_base2)
	{
		iounmap((void*)lbus_qos_cmn_base2);
		lbus_qos_cmn_base2 = 0;
	}



	//LGBUS_MPRO_CTRL_UNLOCK();
#endif
	return RET_OK;
}

static void violation_fault_manager(char *str)
{
	static char buf[256];
	static char cmd_path[] = "/bin/touch";
	static char* cmd_argv[] = {cmd_path, buf, NULL};
	static char* cmd_envp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};
	static int cnt = 0;

	int result;

	snprintf(buf, 256, "/tmp/faultmanager/kernel/%s-%d", str, cnt++);

	result = call_usermodehelper(cmd_path, cmd_argv, cmd_envp, UMH_NO_WAIT);

	if(result != 0)
		LGBUS_ERROR("fail touch-fault_manager\n");
}

#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
static irqreturn_t lgbus_mpro_isr(int irq, void *dev)
{
	int i;

	if(irq == LBUS_IRQ || irq == CPU_IRQ || irq == CPU_AXI_PERI_IRQ || irq == CPU_AHB_PERI_IRQ || irq == CPU_LZMA_IRQ || irq == CPU_FAST_IRQ )
	{
		ulong flag;
		LGBUS_MPRO_CTRL_LOCK();

		for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
		{
			ulong 	irq_status_addr = mpro_ctrl[i].base_addr + MPRO_ISR_STATUS_OFFSET;
			ulong 	irq_clear_addr = mpro_ctrl[i].base_addr + MPRO_ISR_CLEAR_OFFSET;
			u32 	irq_status;
			u32 	irq_clear;
			u32		j;

			CHECK_ERROR(!mpro_ctrl[i].base_addr,
					LGBUS_MPRO_CTRL_UNLOCK(); return RET_ERROR, "base is null\n");
			CHECK_ERROR(!lbus_qos_cmn_base0,
					LGBUS_MPRO_CTRL_UNLOCK(); return RET_ERROR, "base is null\n");
			CHECK_ERROR(!lbus_qos_cmn_base1,
					LGBUS_MPRO_CTRL_UNLOCK(); return RET_ERROR, "base is null\n");
			CHECK_ERROR(!lbus_qos_cmn_base2,
					LGBUS_MPRO_CTRL_UNLOCK(); return RET_ERROR, "base is null\n");

			irq_status = mpro_reg_read(irq_status_addr);
			if(irq_status & MPRO_ISR_STATUS)
			{
				for(j = 0; j < O24_MPRO_RANGE_SLOT_CNT; j++)
				{
					LGBUS_INFO("[%-10s] mpro range(%d) "HEX9_4_STR" ~ "HEX9_4_STR"\n", mpro_ctrl[i].name
							, j
							, HEX9_4_VAL(mpro_ctrl[i].range[j].start)
							, HEX9_4_VAL(mpro_ctrl[i].range[j].end));
				}

				{
					ulong vio_reg_addr;
					struct
					{
						u32 rd_vio_addr;
						u32 rd_vio_id;
						u32 wr_vio_addr;
						u32 wr_vio_id;
					}rw_vio_data[O24_MPRO_RANGE_SLOT_CNT];

					volatile u32 *src;
					volatile u32 *des;
					u32 size;
					u32 x;

					vio_reg_addr = mpro_ctrl[i].base_addr + MPRO_VIO_OFFSET;

					src = (u32*)vio_reg_addr;
					des = (u32*)rw_vio_data;
					size = (sizeof(rw_vio_data))/(sizeof(u32));

					for(x = 0; x < size; x++)
						des[x] = src[x];

					if(irq_status & MPRO_ISR_STATUS_WR)
					{
						for(j = 0; j < O24_MPRO_RANGE_SLOT_CNT; j++)
						{
							if((rw_vio_data[j].wr_vio_id & 0x1) && (rw_vio_data[j].wr_vio_addr != 0xffffffff))
							{
								LGBUS_ERROR(COLOR_RED"[%-10s] Detect write violation!. ip phy "HEX9_4_STR"(%d)-id:0x%08x"COLOR_NONE"\n"
										,mpro_ctrl[i].name, HEX9_4_VAL((u64)rw_vio_data[j].wr_vio_addr << 2), j, rw_vio_data[j].wr_vio_id);

								mpro_ctrl[i].vio_addr = (u64)rw_vio_data[j].wr_vio_addr << 2;
								mpro_ctrl[i].vio_type = MPRO_ISR_STATUS_WR;

								if (LGBUS_ignore_notify(mpro_ctrl[i].name, true))
								{
									LGBUS_ERROR("ignore notify\n");
									continue;
								}

								// write violation
								// debug/event	| release
								// panic		| fault_manager
								if(platform_mode == RELEASE_LEVEL)
								{
									//fault_namager
									char str[64];
									snprintf(str, 64, "DDR_violation-wr-%s", mpro_ctrl[i].name);
									violation_fault_manager(str);
								}
								else
								{
									//panic
									panic("[%-10s] Detect write violation!. ip phy "HEX9_4_STR"(%d)\n"
										,mpro_ctrl[i].name, HEX9_4_VAL((u64)rw_vio_data[j].wr_vio_addr << 2), j);

								}
							}
						}
					}
					if(irq_status & MPRO_ISR_STATUS_RD)
					{
						for(j = 0; j < O24_MPRO_RANGE_SLOT_CNT; j++)
						{
							if((rw_vio_data[j].rd_vio_id & 0x1) && (rw_vio_data[j].rd_vio_addr != 0xffffffff))
							{
								LGBUS_ERROR(COLOR_RED"[%-10s] Detect read violation!. ip phy "HEX9_4_STR"(%d)-id:0x%08x"COLOR_NONE"\n"
										,mpro_ctrl[i].name, HEX9_4_VAL((u64)rw_vio_data[j].rd_vio_addr << 2), j, rw_vio_data[j].rd_vio_id);

								mpro_ctrl[i].vio_addr = (u64)rw_vio_data[j].rd_vio_addr << 2;
								mpro_ctrl[i].vio_type = MPRO_ISR_STATUS_RD;

								if (LGBUS_ignore_notify(mpro_ctrl[i].name, false))
								{
									LGBUS_ERROR("ignore notify\n");
									continue;
								}

								// read violation
								// debug/event   | release
								// fault_manager | fault_manager
								{
									char str[64];
									snprintf(str, 64, "DDR_violation-rd-%s", mpro_ctrl[i].name);
									violation_fault_manager(str);
								}
							}
						}
					}
				}

				if(++mpro_ctrl[i].isr_cnt >= isr_cnt_limit)
					lgbus_mpro_isr_disable_module(i);

				irq_clear = mpro_reg_read(irq_clear_addr);
				irq_clear |= MPRO_ISR_CLEAR;
				mpro_reg_write(irq_clear, irq_clear_addr);

				mpro_reg_write(0xffffffff, lbus_qos_cmn_base0+MPRO_ISR_CLEAR_OFFSET);
				mpro_reg_write(0xffffffff, lbus_qos_cmn_base1+MPRO_ISR_CLEAR_OFFSET);
				mpro_reg_write(0xffffffff, lbus_qos_cmn_base2+MPRO_ISR_CLEAR_OFFSET);
			}
		}

		LGBUS_MPRO_CTRL_UNLOCK();

	}
	return IRQ_HANDLED;
}
#endif

int LGBUS_O24_SetMproRange(lgbus_mpro_range_t *mpro_range)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int 		ret = RET_ERROR;
	uint32_t 	port, cnt;
	uint32_t 	slot_ctrl;
	u32 *range_addr;
	u32 *enable_addr;
	ulong 		flag;

	CHECK_ERROR(!mpro_range, return RET_ERROR, "param is null\n");
	CHECK_ERROR(mpro_range->port >= O24_MPRO_PORT_MAX, return RET_ERROR, "Invalid port\n");
	CHECK_ERROR(mpro_range->port < O24_MPRO_PORT_START, return RET_ERROR, "Invalid port\n");

	port = mpro_range->port - O24_MPRO_PORT_START;

	LGBUS_MPRO_CTRL_LOCK();
	CHECK_ERROR(!mpro_ctrl[port].base_addr, goto func_exit, "base is null\n");
	range_addr = (u32 *)(mpro_ctrl[port].base_addr + MPRO_RANGE_OFFSET);

	enable_addr = (u32 *)(mpro_ctrl[port].base_addr + MPRO_SLOT_ENABLE_OFFSET);
	slot_ctrl = mpro_reg_read(enable_addr);

	//slot range 설정전에 slot disable, 설정중 이상 동작 방지.
	mpro_reg_write(0, enable_addr);

	//slot enable
	//[28] 1 : logic vs physical
	//[16] 1 : stall
	//[8] 1 : slot0 enable
	//[4] 1 : slot1 enable
	//[0] 1 : slot2 enable

	if(mpro_logic)
		slot_ctrl |= (1<<28);
	else
		slot_ctrl &= ~(1<<28);

	for(cnt = 0; cnt < O24_MPRO_RANGE_SLOT_CNT; cnt++)//cnt 0,1,2
	{
		uint32_t ctr0, ctr1;

		if(mpro_range->range[cnt].end == 0)//end가 0이면, start->0, disable slot
		{
			//slot disable
			mpro_range->range[cnt].start = 0;
			slot_ctrl &= ~(1 << (8 - (cnt*4)));

		}
		else
		{
			//slot enable
			slot_ctrl |= (1 << (8 - (cnt*4)));
		}

		mpro_ctrl[port].range[cnt].start = mpro_range->range[cnt].start;
		mpro_ctrl[port].range[cnt].end = mpro_range->range[cnt].end;

		//BUS MPRO REG
		//[28:08] 21 : [32:12] start address
		//[28:08] 21 : [32:12] end address
		ctr0 = (mpro_ctrl[port].range[cnt].start >> 12) << 8; // [28:8]
		ctr1 = (mpro_ctrl[port].range[cnt].end >> 12) << 8; // [28:8]

		mpro_reg_write(ctr0, range_addr++);
		mpro_reg_write(ctr1, range_addr++);

		LGBUS_PRINT("[%-10s][%u] "HEX9_4_STR" ~ "HEX9_4_STR"\n"
									, mpro_ctrl[port].name
									, cnt
									, HEX9_4_VAL(mpro_ctrl[port].range[cnt].start)
									, HEX9_4_VAL(mpro_ctrl[port].range[cnt].end));
	}

	mpro_reg_write(slot_ctrl, enable_addr);

	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}
EXPORT_SYMBOL(LGBUS_O24_SetMproRange);

int LGBUS_O24_GetMproRange(lgbus_mpro_range_t *mpro_range)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	uint32_t 	port, cnt;
	ulong 		flag;

	CHECK_ERROR(!mpro_range, return RET_ERROR, "param is null\n");
	CHECK_ERROR(mpro_range->port >= O24_MPRO_PORT_MAX, return RET_ERROR, "Invalid port\n");
	CHECK_ERROR(mpro_range->port < O24_MPRO_PORT_START, return RET_ERROR, "Invalid port\n");

	port = mpro_range->port - O24_MPRO_PORT_START;

	LGBUS_MPRO_CTRL_LOCK();
	memcpy(mpro_range->range, mpro_ctrl[port].range, sizeof(mpro_ctrl[port].range));
	LGBUS_MPRO_CTRL_UNLOCK();

	for(cnt = 0; cnt < O24_MPRO_RANGE_SLOT_CNT; cnt++)
	{
		LGBUS_PRINT("0x%08llx ~ 0x%08llx\n", mpro_range->range[cnt].start
									, mpro_range->range[cnt].end);
	}
#else
	uint32_t cnt;
	for(cnt = 0; cnt < O24_MPRO_RANGE_SLOT_CNT; cnt++)
	{
		mpro_range->range[cnt].start = 0x0;
		mpro_range->range[cnt].end	= 0x0;
	}
#endif
	return RET_OK;
}
EXPORT_SYMBOL(LGBUS_O24_GetMproRange);

/*
 * port	: port number, ref>lgbus_o24_port_t
 * ctrl	: 1:enable stall, 0:disable stall
 */
int lgbus_o24_mpro_stall_ctrl_module(int port, int ctrl)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	ulong addr;
	uint32_t val;
	int ret = RET_ERROR;
	ulong flag;

	CHECK_ERROR(port >= O24_MPRO_PORT_MAX, return RET_ERROR, "Invalid port\n");
	CHECK_ERROR(port < O24_MPRO_PORT_START, return RET_ERROR, "Invalid port\n");
	port = port - O24_MPRO_PORT_START;

	LGBUS_MPRO_CTRL_LOCK();

	CHECK_ERROR(!mpro_ctrl[port].base_addr, goto func_exit, "base is null\n");

	addr = mpro_ctrl[port].base_addr + MPRO_SLOT_ENABLE_OFFSET;
	val = mpro_reg_read(addr);
	((SLOT_CTRL_T *)&val)->stall = ctrl?1:0;
	mpro_reg_write(val, addr);
	LGBUS_PRINT("addr : 0x%08lx, val : 0x%x\n", addr, val);
	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}
EXPORT_SYMBOL(lgbus_o24_mpro_stall_ctrl_module);

static void lgbus_mpro_user_mpro(void)
{
	int	i;
	lgbus_mpro_range_t mpro_range;

	//at least one slot must be set.
	if (!o24_user_mpro[0] && !o24_user_mpro[1] && !o24_user_mpro[2] && !o24_user_mpro[3] && !o24_user_mpro[4] && !o24_user_mpro[5])
		return;

	LGBUS_NOTI("user_mpro=0x%lx,0x%lx,0x%lx,0x%lx,0x%lx,0x%lx, isr_cnt=%d\n",
			o24_user_mpro[0], o24_user_mpro[1], o24_user_mpro[2], o24_user_mpro[3], o24_user_mpro[4], o24_user_mpro[5], isr_cnt_limit);

	mpro_range.range[0].start   = o24_user_mpro[0];
	mpro_range.range[0].end     = o24_user_mpro[1];
	mpro_range.range[1].start   = o24_user_mpro[2];
	mpro_range.range[1].end     = o24_user_mpro[3];
	mpro_range.range[2].start   = o24_user_mpro[4];
	mpro_range.range[2].end     = o24_user_mpro[5];

	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		mpro_range.port = i;
		mpro_range.port += O24_MPRO_PORT_START;
		LGBUS_O24_SetMproRange(&mpro_range);
	}
}

lgbus_o24_mpro_func_t	lgbus_o24_mpro_func =
{
	.init       = lgbus_mpro_init,
	.cleanup    = lgbus_mpro_cleanup,
	.suspend	= lgbus_mpro_suspend,
	.resume		= lgbus_mpro_resume,
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// get address switch /////////////////////////////////////
#define 	QOS_CMN_CPU			(0xCA202200)

#define CPU_ADDR_SWITCH_BASE			(QOS_CMN_CPU + 0x80)
#define O24_ADDR_SWITCH_SLOT			(16)

#define CPU_BWB_BASE					(QOS_CMN_CPU + 0x100)
#define O24_BWB_SLOT					(8)
#define _reg_read(addr)					__raw_readl((void*)(addr))

#define BWB_OFFSET_DIS 		0x0 	//disable offset
#define BWB_OFFSET_M0 		0x4 	//offset for M0 area
#define BWB_OFFSET_M1 		0x5 	//offset for M1 area
#define BWB_OFFSET_M2 		0x6 	//offset for M2 area

static lgbus_addr_switch_t	o24_addr_switch[O24_ADDR_SWITCH_SLOT];
static lgbus_bwb_t			o24_bwb[O24_BWB_SLOT];

static int lgbus_get_addr_switch(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int 	i;
	u32*	base_addr;
	u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

	base_addr = (u32 *)ioremap(CPU_ADDR_SWITCH_BASE, 0x100);
	CHECK_ERROR(!base_addr, return -1, "base is null\n");

	reg_base = (u32 *)base_addr;
	for(i = 0; i < O24_ADDR_SWITCH_SLOT; i++)
	{
		u32 d0, d1;

		d0 = _reg_read(reg_base++);
		d1 = _reg_read(reg_base++);

		//BUS ASW REG
		//[29:16]	14 : start
		//[13:00]	14 : end

		//[28]		1 : enable
		//[13:00]	14: offset
		o24_addr_switch[i].start = ((u64)(d0 >> 16) & 0x3fff) << 20; 	// 29~16	:14bit
		o24_addr_switch[i].end = (u64)(d0 & 0x3fff) << 20; 				// 13~0		:14bit
		o24_addr_switch[i].offset = (u64)(d1 & 0x3fff) << 20; 			// 13~0		:14bit

		if(o24_addr_switch[i].end)
			o24_addr_switch[i].end |= 0xfffff;

		LGBUS_PRINT("s:"HEX9_4_STR" ~ e:"HEX9_4_STR",o:"HEX9_4_STR"\n", HEX9_4_VAL(o24_addr_switch[i].start)
															 , HEX9_4_VAL(o24_addr_switch[i].end)
															 , HEX9_4_VAL(o24_addr_switch[i].offset));
	}

	if(base_addr)
		iounmap((void*)base_addr);
#endif
	return RET_OK;
}

static int lgbus_get_bwb(void)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int 	i;
	ulong	base_addr;
	u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

	base_addr = (ulong)ioremap(CPU_BWB_BASE, 0x100);
	CHECK_ERROR(!base_addr, return -1, "base is null\n");

	reg_base = (u32 *)base_addr;
	for(i = 0; i < O24_BWB_SLOT; i++)
	{
		u32 d0, d1;

		d0 = _reg_read(reg_base++);
		d1 = _reg_read(reg_base++);

		//BUS BWB REG
		//[31:28] 4 : mode
		//[26:24] 3 : unit
		//[22:12] 11 : start
		//[10:0]  11 : end

		//[30:28] 3 : offset_mode
		//[13:0] 14 : offset
		o24_bwb[i].start = ((u64)(d0 >> 12) & 0x7ff) << 20;	//[22:12] 11 : start
		o24_bwb[i].end = (u64)(d0 & 0x7ff) << 20;			//[10:0]  11 : end

		o24_bwb[i].offset = (u64)(d1 & 0x3fff) << 20;		//[13:0] 14 : offset
		o24_bwb[i].offset_mode = (d1 >> 28) & 0x7;

		if(o24_bwb[i].end)
			o24_bwb[i].end |= 0xfffff;

		LGBUS_PRINT("s:0x%09llx ~ e:0x%09llx,o:0x%09llx[%x]\n", o24_bwb[i].start
															 , o24_bwb[i].end
															 , o24_bwb[i].offset
															 , o24_bwb[i].offset_mode);
	}

	if(base_addr)
		iounmap((void*)base_addr);
#endif
	return RET_OK;
}

u64 lgbus_o24_get_ddr_addr(u64 phy_addr)
{
#ifdef SUPPORT_O24_MPRO_CHIP_KDRV
	int i;
	u64 tmp = phy_addr;
	u64 bwb_addr;

	for(i = 0; i < O24_ADDR_SWITCH_SLOT; i++)
	{
		if(o24_addr_switch[i].start <= phy_addr &&
				o24_addr_switch[i].end >= phy_addr)
		{
			phy_addr += o24_addr_switch[i].offset;
			phy_addr &= 0x1ffffffff; /* wrap around, remove mirror */
			break;
		}
	}

	//calc bwb offset
	bwb_addr = (phy_addr & 0x7fffffff);

	for(i = 0; i < O24_BWB_SLOT; i++)
	{
		if(o24_bwb[i].offset)
		{
			if(o24_bwb[i].start <= bwb_addr
					&& o24_bwb[i].end >= bwb_addr
					&& o24_bwb[i].offset)
			{
				if(o24_bwb[i].offset_mode == BWB_OFFSET_M0
						&& phy_addr < 0x80000000)
				{
					phy_addr += o24_bwb[i].offset;
				}
				else if(o24_bwb[i].offset_mode == BWB_OFFSET_M1
						&& 	phy_addr >= 0x80000000 && phy_addr < 0x100000000)
				{
					phy_addr += o24_bwb[i].offset;
				}
				else if(o24_bwb[i].offset_mode == BWB_OFFSET_M2
						&& phy_addr >= 0x100000000)
				{
					phy_addr += o24_bwb[i].offset;
				}

				//bwb offset wrap around
				phy_addr &= 0x1ffffffff;

				break;
			}
		}
	}

	LGBUS_PRINT("%s: v:"HEX9_4_STR" -> p:"HEX9_4_STR"\n", __func__, HEX9_4_VAL(tmp), HEX9_4_VAL(phy_addr));
#endif
	return phy_addr;
}
EXPORT_SYMBOL(lgbus_o24_get_ddr_addr);


/////////////////////////// PROC for debug information //////////////////////////////
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static struct proc_ops proc_status_fops =
{
	.proc_open = lgbus_mpro_proc_status_open,
	.proc_read = seq_read,
	.proc_write = lgbus_mpro_proc_status_write,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations proc_status_fops =
{
	.open = lgbus_mpro_proc_status_open,
	.read = seq_read,
	.write = lgbus_mpro_proc_status_write,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static struct proc_ops asw_status_fops =
{
	.proc_open = lgbus_mpro_proc_asw_open,
	.proc_read = seq_read,
	.proc_write = lgbus_mpro_proc_asw_write,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations asw_status_fops =
{
	.open = lgbus_mpro_proc_asw_open,
	.read = seq_read,
	.write = lgbus_mpro_proc_asw_write,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

static struct proc_dir_entry *proc_entry;

static int lgbus_mpro_proc_init(void)
{
	struct proc_dir_entry *pde;

	//make proc to memory protector
	pde = proc_mkdir("lg/mpro", NULL);
	CHECK_ERROR(!pde, return RET_ERROR, "fail proc_mkdir\n");

	proc_entry = pde;

	pde = proc_create ("status", 0440, proc_entry, &proc_status_fops);
	CHECK_ERROR(!pde, return RET_ERROR, "fail proc_create\n");

	pde = proc_create ("asw", 0440, proc_entry, &asw_status_fops);
	CHECK_ERROR(!pde, return RET_ERROR, "fail proc_create\n");

	return 0;
}

static int lgbus_mpro_proc_status_open(struct inode *inode, struct file *file)
{
	return single_open(file, lgbus_mpro_proc_status_op, NULL);
}

static int lgbus_mpro_proc_asw_open(struct inode *inode, struct file *file)
{
	return single_open(file, lgbus_mpro_proc_asw_op, NULL);
}

static int lgbus_mpro_proc_status_op(struct seq_file *s, void *data)
{
	int i, j;
	SLOT_CTRL_T *slot_ctrl;

	lgbus_mpro_get_range();

	seq_printf(s, "========== memory protector info ==========\n");

	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{

		seq_printf(s, "port : %s[%d]\n", mpro_ctrl[i].name, i);

		for(j = 0; j < ARRAY_SIZE(mpro_ctrl[i].range); j++)
		{
			seq_printf(s, "\trange(%d) "HEX9_4_STR" ~ "HEX9_4_STR"\n", j
												, HEX9_4_VAL(mpro_ctrl[i].range[j].start)
												, HEX9_4_VAL(mpro_ctrl[i].range[j].end));

		}
		slot_ctrl = (SLOT_CTRL_T *)&mpro_ctrl[i].slot_ctrl;

		seq_printf(s, "\taddr_type:%s, stall:%s, slot[%s/%s/%s]\n"
				, slot_ctrl->logic?"L":"P"
				, slot_ctrl->stall?"o":"x"
				, slot_ctrl->slot0_enable?"o":"x"
				, slot_ctrl->slot1_enable?"o":"x"
				, slot_ctrl->slot2_enable?"o":"x");

		seq_printf(s, "\tisr_cnt %d\n", mpro_ctrl[i].isr_cnt);

		if(mpro_ctrl[i].vio_type)
		{
			seq_printf(s, COLOR_RED"\t--- check violation ---\n"COLOR_NONE);
			seq_printf(s, COLOR_RED"\tvio addr(ip phy) "HEX9_4_STR", type %s\n"COLOR_NONE
					, HEX9_4_VAL(mpro_ctrl[i].vio_addr)
					, mpro_ctrl[i].vio_type == MPRO_ISR_STATUS_RD ? "RD": "WR");
		}

		seq_printf(s, "\n");
	}

	return 0;
}

static ssize_t lgbus_mpro_proc_asw_write(struct file *file
        , const char __user *buf, size_t size, loff_t *off)
{

	char *str;
	u64 phy_addr;

	CHECK_ERROR(*off != 0, return -EINVAL, "non zero offset\n");

	//printk("size : %lu\n", size);

	str = vmalloc(size);
	CHECK_ERROR(str == NULL, return -EFAULT, "fail vmalloc\n");

	if(copy_from_user(str, buf, size))
	{
		error("fail copy from_user\n");
		vfree(str);
		return -EFAULT;
	}

	str[size-1] = 0;

	phy_addr = simple_strtoull(str, NULL, 0);

	printk("0x%llx => 0x%llx\n", phy_addr, LGBUS_GetDDRAddr(phy_addr));

	return size;
}

static ssize_t lgbus_mpro_proc_status_write(struct file *file
        , const char __user *buf, size_t size, loff_t *off)
{
	char *str;
	char *p;
	char *temp_str;

	int		i;
	int		addr_cnt;
	int		addr_max = O24_MPRO_RANGE_SLOT_CNT * 2;
	u64		addr[O24_MPRO_RANGE_SLOT_CNT * 2] = {0,};
	lgbus_mpro_range_t mpro_range;

	CHECK_ERROR(*off != 0, return -EINVAL, "non zero offset\n");

	//printk("size : %u\n", size);

	str = vmalloc(size);
	CHECK_ERROR(str == NULL, return -EFAULT, "fail vmalloc\n");

	if(copy_from_user(str, buf, size))
	{
		error("fail copy from_user\n");
		vfree(str);
		return -EFAULT;
	}
    str[size-1] = 0;

	//printk("echo %s\n", str);

	if(!strncmp(str, "mpro_cnt", strlen("mpro_cnt")))
	{
		//printk("check mpro_cnt %s\n", str);
		p = str;
		i = 0;

		while(i < size)
		{
			if(*p++ == ':')
			{
				isr_cnt_limit = simple_strtoull(p, NULL, 0);
				printk("mpro isr_cnt_limit : 0x%x\n", isr_cnt_limit);
				lgbus_mpro_isr_cnt_clear();
				goto func_exit;
			}
			i++;
		}
	}
	else if(!strncmp(str, "logic", strlen("logic")))
	{
		p = str;
		i = 0;

		while(i < size)
		{
			if(*p++ == ':')
			{
				mpro_logic = simple_strtoull(p, NULL, 0);
				printk("mpro logic : %u\n", mpro_logic);
				goto func_exit;
			}
			i++;
		}
	}
	else if(!strncmp(str, "stall_en", strlen("stall_en")))
	{
		p = str;
		i = 0;

		while(i < size)
		{
			if(*p++ == ':')
			{
				u32 port_num;
				port_num = simple_strtoull(p, NULL, 0);
				printk("enable stall port : %u\n", port_num);
				port_num += O24_MPRO_PORT_START;
				lgbus_o24_mpro_stall_ctrl_module(port_num, 1);
				goto func_exit;
			}
			i++;
		}
	}
	else if(!strncmp(str, "stall_dis", strlen("stall_dis")))
	{
		p = str;
		i = 0;

		while(i < size)
		{
			if(*p++ == ':')
			{
				u32 port_num;
				port_num = simple_strtoull(p, NULL, 0);
				printk("disable stall port : %u\n", port_num);
				port_num += O24_MPRO_PORT_START;
				lgbus_o24_mpro_stall_ctrl_module(port_num, 0);
				goto func_exit;
			}
			i++;
		}
	}

	p = str;
	i = 0;
	while(i < size)
	{
		temp_str = p;
		for(; i < size; i++, p++)
		{
			if(*p == ':')
			{
				*p = 0;
				p++;
				i++;
				break;
			}
			else if(*p == '\0')
				goto func_exit;
		}

		mpro_range.port = simple_strtoul(temp_str, NULL, 10);

		//printk("module %u\n", mpro_range.port);

		for(addr_cnt = 0; (addr_cnt < addr_max) && (i < size); addr_cnt++)
		{
			temp_str = p;
			for(; i < size; i++, p++)
			{
				if(*p == ',' || *p == '\0')
				{
					*p = 0;
					p++;
					i++;
					break;
				}
			}
			addr[addr_cnt] = simple_strtoull(temp_str, NULL,0);

			//printk("addr : 0x%llx\n", addr[addr_cnt]);
		}

		mpro_range.range[0].start	= addr[0];
		mpro_range.range[0].end		= addr[1];
		mpro_range.range[1].start	= addr[2];
		mpro_range.range[1].end		= addr[3];
		mpro_range.range[2].start	= addr[4];
		mpro_range.range[2].end		= addr[5];

		if(!addr[0] && !addr[1] && !addr[2] && !addr[3] && !addr[4] && !addr[5])
		{
			ulong flag;

			LGBUS_MPRO_CTRL_LOCK();
			lgbus_mpro_isr_enable_module(mpro_range.port);
			LGBUS_MPRO_CTRL_UNLOCK();

			//printk("enable %d module mpro\n", mpro_range.port);
		}
		else
		{
			mpro_range.port += O24_MPRO_PORT_START;
			LGBUS_O24_SetMproRange(&mpro_range);
		}

	}

func_exit:

	vfree(str);

	return size;
}

static int lgbus_mpro_proc_asw_op(struct seq_file *s, void *data)
{
#if 0//def SUPPORT_O24_MPRO_CHIP_KDRV
	/* copied from lgbus_mpro_get_range() */
	{
		int 	i;
		u32*	base_addr;
		u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

		base_addr = (u32 *)ioremap(CPU_ADDR_SWITCH_BASE, 0x100);
		CHECK_ERROR(!base_addr, return -1, "base is null\n");

		reg_base = (u32 *)base_addr;
		for(i = 0; i < O24_ADDR_SWITCH_SLOT; i++)
		{
			u32 d0, d1;

			d0 = _reg_read(reg_base++);
			d1 = _reg_read(reg_base++);

			/* print start, end, offset without low 20bit */
			seq_printf(s, "asw: 0x%04x 0x%04x 0x%04x\n", ((d0>>16) & 0x1fff), (d0 & 0x1ffff), (d1 & 0x1fff));
		}

		if(base_addr)
			iounmap((void*)base_addr);
	}

	/* copied from lgbus_get_bwb(void) */
	{
		int 	i;
		ulong	base_addr;
		u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

		base_addr = (ulong)ioremap(CPU_BWB_BASE, 0x100);
		CHECK_ERROR(!base_addr, return -1, "base is null\n");

		reg_base = (u32 *)base_addr;
		for(i = 0; i < O24_BWB_SLOT; i++)
		{
			u32 d0, d1;

			d0 = _reg_read(reg_base++);
			d1 = _reg_read(reg_base++);

			/* print bwb_start, bwb_end, bwb_offset without low 20bit and bwb_mode, bwb_offset_mode */
			seq_printf(s, "bwb: 0x%04x 0x%04x 0x%04x 0x%x 0x%x\n", ((d0>>12) & 0x7ff), (d0 & 0x7ff), (d1 & 0x1fff), ((d0>>28)&0x7), ((d1>>28)&0x7));
		}

		if(base_addr)
			iounmap((void*)base_addr);
	}
#endif

	return 0;
}

