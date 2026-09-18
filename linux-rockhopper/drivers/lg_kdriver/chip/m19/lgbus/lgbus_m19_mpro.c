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
 *  author		kukhyun85.kim@lge.com
 *  version		1.0
 *  note		Additional information.
 *  date		2018.MAY.
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

#define LBUS_QOS_CMN_BASE			(0xc9820000)
#define GBUS_QOS_CMN_BASE			(0xc9100000)

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



#define LGBUS_MPRO_CTRL_LOCK()		do{ spin_lock_irqsave(&lgbus_mpro_ctrl_lock, flag);}while(0)
#define LGBUS_MPRO_CTRL_UNLOCK()	do{ spin_unlock_irqrestore(&lgbus_mpro_ctrl_lock, flag);}while(0)
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

/* address switch */
static int lgbus_get_addr_switch(void);
static int lgbus_get_bwb(void);

/* lgbus memory protector proc functions */
static int lgbus_mpro_proc_init(void);
static int lgbus_mpro_proc_status_op(struct seq_file *s, void *data);
static int lgbus_mpro_proc_status_open(struct inode *inode, struct file *file);
static ssize_t lgbus_mpro_proc_status_write(struct file *file
        , const char __user *buf, size_t size, loff_t *off);

static int lgbus_mpro_proc_asw_op(struct seq_file *s, void *data);
static int lgbus_mpro_proc_asw_open(struct inode *inode, struct file *file);
/*----------------------------------------------------------------------------------------
  Static Variables
----------------------------------------------------------------------------------------*/

//memory protect, qos reg btop base address
static lgbus_m19_mpro_t mpro_ctrl[] =
{
	{ "CPU",		0xC9231200 },
	{ "CPUPERI",	0xC9231400 },
	{ "CPULZMA",	0xC9231600 },

	{ "GPU",		0xC9822000 },
	{ "GFX",		0xC9822200 },
	{ "TI", 		0xC9822400 },
	{ "AUD",		0xC9822600 },
	{ "VDEC0_M0",	0xC9822800 },
	{ "VDEC0_M1",	0xC9822A00 },
	{ "VDEC1_M0",	0xC9822C00 },
	{ "VDEC1_M1",	0xC9822E00 },
	{ "MCU",		0xC9823000 },
	{ "CCO",		0xC9823200 },
	{ "FMC0",		0xC9823400 },
	{ "FMC1",		0xC9823600 },
	{ "TCON",		0xC9823800 },
	{ "ME0",		0xC9823A00 },
	{ "FMS0",		0xC9823C00 },
	{ "CVI",		0xC9101000 },
	{ "VDM0",		0xC9101200 },
	{ "SRE",		0xC9101200 },
	{ "VDM1",		0xC9101400 },
	{ "SMX0",		0xC9101600 },
	{ "SMX1",		0xC9101800 },
	{ "ND0",		0xC9101A00 },
	{ "ND1",		0xC9101C00 },
	{ "GSC0",		0xC9102000 },
	{ "GSC1",		0xC9102200 },
	{ "ME1",		0xC9102400 },
	{ "DBB",		0xC9102600 },
	{ "VENC",		0xC9102800 },
};

static ulong lbus_qos_cmn_base;
static ulong gbus_qos_cmn_base;

static u32 isr_cnt_limit = 3;


static DEFINE_SPINLOCK(lgbus_mpro_ctrl_lock);
/*========================================================================================
    Implementation Group
========================================================================================*/
static int lgbus_mpro_init(void)
{
	int ret;

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

	return 0;

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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int i,j;
	int ret = RET_ERROR;
	ulong start;
	ulong end;
	u32 *range_addr;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");
		range_addr = (u32*)(mpro_ctrl[i].base_addr + MPRO_RANGE_OFFSET);

		for(j = 0; j < M19_MPRO_RANGE_SLOT_CNT; j++)
		{
			start	= (mpro_reg_read(range_addr++) & 0xFFFFF000);
			end		= (mpro_reg_read(range_addr++) & 0xFFFFF000) | 0xFFF;
			if(end == 0xfff) end = 0x0;

			mpro_ctrl[i].range[j].start = start;
			mpro_ctrl[i].range[j].end = end;

			LGBUS_PRINT("[%-10s] mpro range(%d) 0x%08llx ~ 0x%08llx\n", mpro_ctrl[i].name
																, j
																, mpro_ctrl[i].range[j].start
																, mpro_ctrl[i].range[j].end);
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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int i;
	int ret = RET_ERROR;
	u32 *save_addr;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");
		save_addr = (u32 *)(mpro_ctrl[i].base_addr + MPRO_SLOT_ENABLE_OFFSET);

		memcpy_fromio(&(mpro_ctrl[i].reg_save), save_addr, sizeof(lgbus_m19_mpro_reg_save_t));
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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int i;
	int ret = RET_ERROR;
	u32 *save_addr;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		CHECK_ERROR(!mpro_ctrl[i].base_addr, goto func_exit, "base is null\n");
		save_addr = (u32 *)(mpro_ctrl[i].base_addr + MPRO_SLOT_ENABLE_OFFSET);

		memcpy_toio(save_addr, &(mpro_ctrl[i].reg_save), sizeof(lgbus_m19_mpro_reg_save_t));
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
#undef GBUS_IRQ
#define LBUS_IRQ	M19_IRQ_INTR_LBUS
#define GBUS_IRQ	M19_IRQ_INTR_GBUS

#undef CPU_IRQ
#undef CPU_PERI_IRQ
#undef CPU_LZMA_IRQ

#define CPU_IRQ			M19_IRQ_INTR_QOS_TIMER_CPU
#define CPU_PERI_IRQ	M19_IRQ_INTR_QOS_TIMER_PERI
#define CPU_LZMA_IRQ	M19_IRQ_INTR_QOS_TIMER_LZMA


static int lgbus_mpro_request_irq(void)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int ret;

	ret = request_irq(CPU_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(CPU_PERI_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_PERI_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(CPU_LZMA_IRQ, lgbus_mpro_isr, IRQF_SHARED, "CPU_LZMA_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(LBUS_IRQ, lgbus_mpro_isr, IRQF_SHARED, "LBUS_MPRO", (void *)&mpro_ctrl);
	CHECK_RET(ret, goto func_exit);

	ret = request_irq(GBUS_IRQ, lgbus_mpro_isr, IRQF_SHARED, "GBUS_MPRO", (void *)&mpro_ctrl);
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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	free_irq(CPU_IRQ, (void*)&mpro_ctrl);
	free_irq(CPU_PERI_IRQ, (void*)&mpro_ctrl);
	free_irq(CPU_LZMA_IRQ, (void*)&mpro_ctrl);
	free_irq(LBUS_IRQ, (void*)&mpro_ctrl);
	free_irq(GBUS_IRQ, (void*)&mpro_ctrl);
	return 0;
#else
	return RET_OK;
#endif
}

static int lgbus_mpro_isr_enable(void)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
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

	CHECK_ERROR(!lbus_qos_cmn_base, goto func_exit, "base is null\n");
	CHECK_ERROR(!gbus_qos_cmn_base, goto func_exit, "base is null\n");

	mpro_reg_write(0xffffffff, lbus_qos_cmn_base + MPRO_ISR_ENABLE_OFFSET);
	mpro_reg_write(0xffffffff, gbus_qos_cmn_base + MPRO_ISR_ENABLE_OFFSET);

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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
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
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int i;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
	/* ioremap : get virtual address */
	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{
		/* at arm, ioremap == ioremap_nocache */
		mpro_ctrl[i].base_addr = (ulong)ioremap_nocache(mpro_ctrl[i].base_addr_phy, 0x200);

		LGBUS_PRINT("[%-10s] ioremap phy : 0x%08lx, addr : 0x%08lx\n", mpro_ctrl[i].name
										   , mpro_ctrl[i].base_addr_phy
										   , mpro_ctrl[i].base_addr);

		if(!mpro_ctrl[i].base_addr)
		{
			LGBUS_MPRO_CTRL_UNLOCK();
			LGBUS_ERROR("fail ioremap\n");
			lgbus_mpro_iounmap();
			return RET_ERROR;
		}
	}

	lbus_qos_cmn_base = (ulong)ioremap_nocache(LBUS_QOS_CMN_BASE, 0x200);
	gbus_qos_cmn_base = (ulong)ioremap_nocache(GBUS_QOS_CMN_BASE, 0x200);

	if(!lbus_qos_cmn_base || !gbus_qos_cmn_base)
	{
		LGBUS_MPRO_CTRL_UNLOCK();
		LGBUS_ERROR("fail ioremap\n");
		lgbus_mpro_iounmap();
		return RET_ERROR;
	}

	LGBUS_MPRO_CTRL_UNLOCK();
#endif
	return RET_OK;
}

static int lgbus_mpro_iounmap(void)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int i;
	ulong flag;

	LGBUS_MPRO_CTRL_LOCK();
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

	if(lbus_qos_cmn_base)
	{
		iounmap((void*)lbus_qos_cmn_base);
		lbus_qos_cmn_base = 0;
	}
	if(gbus_qos_cmn_base)
	{
		iounmap((void*)gbus_qos_cmn_base);
		gbus_qos_cmn_base = 0;
	}

	LGBUS_MPRO_CTRL_UNLOCK();
#endif
	return RET_OK;
}

#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
static irqreturn_t lgbus_mpro_isr(int irq, void *dev)
{
	int i;

	if(irq == LBUS_IRQ || irq == GBUS_IRQ || irq == CPU_IRQ || irq == CPU_PERI_IRQ || irq == CPU_LZMA_IRQ)
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
			CHECK_ERROR(!lbus_qos_cmn_base,
					LGBUS_MPRO_CTRL_UNLOCK(); return RET_ERROR, "base is null\n");
			CHECK_ERROR(!gbus_qos_cmn_base,
					LGBUS_MPRO_CTRL_UNLOCK(); return RET_ERROR, "base is null\n");

			irq_status = mpro_reg_read(irq_status_addr);
			if(irq_status & MPRO_ISR_STATUS)
			{
				for(j = 0; j < M19_MPRO_RANGE_SLOT_CNT; j++)
				{
					LGBUS_INFO("[%-10s] mpro range(%d) 0x%08llx ~ 0x%08llx\n", mpro_ctrl[i].name
							, j
							, mpro_ctrl[i].range[j].start
							, mpro_ctrl[i].range[j].end);
				}

				{
					ulong vio_reg_addr;
					struct
					{
						u32 rd_vio_addr;
						u32 rd_vio_id;
						u32 wr_vio_addr;
						u32 wr_vio_id;
					}rw_vio_data[M19_MPRO_RANGE_SLOT_CNT];

					vio_reg_addr = mpro_ctrl[i].base_addr + MPRO_VIO_OFFSET;

					memcpy_fromio((void*)rw_vio_data, (void*)vio_reg_addr, sizeof(rw_vio_data));

					if(irq_status & MPRO_ISR_STATUS_WR)
					{
						for(j = 0; j < M19_MPRO_RANGE_SLOT_CNT; j++)
						{
							if((rw_vio_data[j].wr_vio_id & 0x1) && (rw_vio_data[j].wr_vio_addr != 0xffffffff))
							{
								LGBUS_ERROR(COLOR_RED"[%-10s] Detect write violation!. ddr phy 0x%08x(%d)"COLOR_NONE"\n"
										,mpro_ctrl[i].name, rw_vio_data[j].wr_vio_addr,j);

								mpro_ctrl[i].vio_addr = rw_vio_data[j].wr_vio_addr;
								mpro_ctrl[i].vio_type = MPRO_ISR_STATUS_WR;
							}
						}
					}
					if(irq_status & MPRO_ISR_STATUS_RD)
					{
						for(j = 0; j < M19_MPRO_RANGE_SLOT_CNT; j++)
						{
							if((rw_vio_data[j].rd_vio_id & 0x1) && (rw_vio_data[j].rd_vio_addr != 0xffffffff))
							{
								LGBUS_ERROR(COLOR_RED"[%-10s] Detect read violation!. ddr phy 0x%08x(%d)"COLOR_NONE"\n"
										,mpro_ctrl[i].name, rw_vio_data[j].rd_vio_addr,j);

								mpro_ctrl[i].vio_addr = rw_vio_data[j].rd_vio_addr;
								mpro_ctrl[i].vio_type = MPRO_ISR_STATUS_RD;
							}
						}
					}
				}

				if(++mpro_ctrl[i].isr_cnt >= isr_cnt_limit)
					lgbus_mpro_isr_disable_module(i);

				irq_clear = mpro_reg_read(irq_clear_addr);
				irq_clear |= MPRO_ISR_CLEAR;
				mpro_reg_write(irq_clear, irq_clear_addr);

				mpro_reg_write(0xffffffff, lbus_qos_cmn_base+MPRO_ISR_CLEAR_OFFSET);
				mpro_reg_write(0xffffffff, gbus_qos_cmn_base+MPRO_ISR_CLEAR_OFFSET);
			}
		}

		LGBUS_MPRO_CTRL_UNLOCK();

	}
	return IRQ_HANDLED;
}
#endif

int LGBUS_M19_SetMproRange(lgbus_mpro_range_t *mpro_range)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int 		ret = RET_ERROR;
	uint32_t 	port, cnt;
	uint32_t 	ctr;
	u32 *range_addr;
	u32 *enable_addr;
	ulong 		flag;

	CHECK_ERROR(!mpro_range, return RET_ERROR, "param is null\n");
	CHECK_ERROR(mpro_range->port >= M19_MPRO_PORT_MAX, return RET_ERROR, "Invalid port\n");
	CHECK_ERROR(mpro_range->port < M19_MPRO_PORT_START, return RET_ERROR, "Invalid port\n");

	port = mpro_range->port - M19_MPRO_PORT_START;

	LGBUS_MPRO_CTRL_LOCK();
	CHECK_ERROR(!mpro_ctrl[port].base_addr, goto func_exit, "base is null\n");
	range_addr = (u32 *)(mpro_ctrl[port].base_addr + MPRO_RANGE_OFFSET);

	for(cnt = 0; cnt < M19_MPRO_RANGE_SLOT_CNT; cnt++)
	{
		uint32_t ctr0, ctr1;

		if(!mpro_range->range[cnt].start && !mpro_range->range[cnt].end)
			continue;

		mpro_ctrl[port].range[cnt].start = mpro_range->range[cnt].start;
		mpro_ctrl[port].range[cnt].end = mpro_range->range[cnt].end;

		ctr0 = mpro_ctrl[port].range[cnt].start & 0xfffff000;
		ctr1 = mpro_ctrl[port].range[cnt].end & 0xfffff000;

		mpro_reg_write(ctr0, range_addr++);
		mpro_reg_write(ctr1, range_addr++);

		LGBUS_PRINT("[%-10s][%u] 0x%08llx ~ 0x%08llx\n"
									, mpro_ctrl[port].name
									, cnt
									, mpro_ctrl[port].range[cnt].start
									, mpro_ctrl[port].range[cnt].end);
	}

	//slot enable
	enable_addr = (u32 *)(mpro_ctrl[port].base_addr + MPRO_SLOT_ENABLE_OFFSET);
	ctr = (1<<8) | (1<<4) | 1;
	mpro_reg_write(ctr, enable_addr);

	ret = RET_OK;

func_exit:
	LGBUS_MPRO_CTRL_UNLOCK();
	return ret;
#else
	return RET_OK;
#endif
}
EXPORT_SYMBOL(LGBUS_M19_SetMproRange);

int LGBUS_M19_GetMproRange(lgbus_mpro_range_t *mpro_range)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	uint32_t 	port, cnt;
	ulong 		flag;

	CHECK_ERROR(!mpro_range, return RET_ERROR, "param is null\n");
	CHECK_ERROR(mpro_range->port >= M19_MPRO_PORT_MAX, return RET_ERROR, "Invalid port\n");
	CHECK_ERROR(mpro_range->port < M19_MPRO_PORT_START, return RET_ERROR, "Invalid port\n");

	port = mpro_range->port - M19_MPRO_PORT_START;

	LGBUS_MPRO_CTRL_LOCK();
	memcpy(mpro_range->range, mpro_ctrl[port].range, sizeof(mpro_ctrl[port].range));
	LGBUS_MPRO_CTRL_UNLOCK();

	for(cnt = 0; cnt < M19_MPRO_RANGE_SLOT_CNT; cnt++)
	{
		LGBUS_PRINT("0x%08llx ~ 0x%08llx\n", mpro_range->range[cnt].start
									, mpro_range->range[cnt].end);
	}
#else
	uint32_t cnt;
	for(cnt = 0; cnt < M19_MPRO_RANGE_SLOT_CNT; cnt++)
	{
		mpro_range->range[cnt].start = 0x0;
		mpro_range->range[cnt].end	= 0x0;
	}
#endif
	return RET_OK;
}
EXPORT_SYMBOL(LGBUS_M19_GetMproRange);

lgbus_m19_mpro_func_t	lgbus_m19_mpro_func =
{
	.init       = lgbus_mpro_init,
	.cleanup    = lgbus_mpro_cleanup,
	.suspend	= lgbus_mpro_suspend,
	.resume		= lgbus_mpro_resume,
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// get address switch /////////////////////////////////////

#define CPU_ADDR_SWITCH_BASE			(0xc9231080) /* M16P3 - QOS_CMN_CPU */
#define M19_ADDR_SWITCH_SLOT			(12)

#define CPU_BWB_BASE					(0xc9231100)
#define M19_BWB_SLOT					(8)
#define _reg_read(addr)					__raw_readl((void*)(addr))

#define BWB_OFFSET_M0		4
#define BWB_OFFSET_M1		5

static lgbus_addr_switch_t	m19_addr_switch[M19_ADDR_SWITCH_SLOT];
static lgbus_bwb_t			m19_bwb[M19_BWB_SLOT];

static int lgbus_get_addr_switch(void)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int 	i;
	u32*	base_addr;
	u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

	base_addr = (u32 *)ioremap_nocache(CPU_ADDR_SWITCH_BASE, 0x100);
	CHECK_ERROR(!base_addr, return -1, "base is null\n");

	reg_base = (u32 *)base_addr;
	for(i = 0; i < M19_ADDR_SWITCH_SLOT; i++)
	{
		u32 d0, d1;

		d0 = _reg_read(reg_base++);
		d1 = _reg_read(reg_base++);

		m19_addr_switch[i].start = ((u64)(d0 >> 16) & 0xfff) << 20;
		m19_addr_switch[i].end = (u64)(d0 & 0xfff) << 20;
		m19_addr_switch[i].offset = (u64)(d1 & 0xfff) << 20;

		if(m19_addr_switch[i].end)
			m19_addr_switch[i].end |= 0xfffff;

		LGBUS_PRINT("s:0x%010llx ~ e:0x%010llx,o:0x%010llx\n", m19_addr_switch[i].start
															 , m19_addr_switch[i].end
															 , m19_addr_switch[i].offset);
	}

	if(base_addr)
		iounmap((void*)base_addr);
#endif
	return RET_OK;
}

static int lgbus_get_bwb(void)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int 	i;
	ulong	base_addr;
	u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

	base_addr = (ulong)ioremap_nocache(CPU_BWB_BASE, 0x100);
	CHECK_ERROR(!base_addr, return -1, "base is null\n");

	reg_base = (u32 *)base_addr;
	for(i = 0; i < M19_BWB_SLOT; i++)
	{
		u32 d0, d1;

		d0 = _reg_read(reg_base++);
		d1 = _reg_read(reg_base++);

		m19_bwb[i].start = ((u64)(d0 >> 12) & 0x7ff) << 20;
		m19_bwb[i].end = (u64)(d0 & 0x7ff) << 20;

		m19_bwb[i].offset = (u64)(d1 & 0xfff) << 20;
		m19_bwb[i].offset_mode = (d1 >> 28) & 0x7;

		if(m19_bwb[i].end)
			m19_bwb[i].end |= 0xfffff;

		LGBUS_PRINT("s:0x%010llx ~ e:0x%010llx,o:0x%010llx[%x]\n", m19_bwb[i].start
															 , m19_bwb[i].end
															 , m19_bwb[i].offset
															 , m19_bwb[i].offset_mode);
	}

	if(base_addr)
		iounmap((void*)base_addr);
#endif
	return RET_OK;
}

u64 lgbus_m19_get_ddr_addr(u64 phy_addr)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	int i;
	u64 tmp = phy_addr;
	u64 bwb_addr;

	for(i = 0; i < M19_ADDR_SWITCH_SLOT; i++)
	{
		if(m19_addr_switch[i].start <= phy_addr &&
				m19_addr_switch[i].end >= phy_addr)
		{
			phy_addr += m19_addr_switch[i].offset;
			phy_addr &= 0xffffffff; /* wrap around */
			break;
		}
	}

	//calc bwb offset
	bwb_addr = (phy_addr & 0x7fffffff);

	for(i = 0; i < M19_BWB_SLOT; i++)
	{
		if(m19_bwb[i].offset)
		{
			if(m19_bwb[i].start <= bwb_addr &&
					m19_bwb[i].end >= bwb_addr)
			{
				if(m19_bwb[i].offset_mode == BWB_OFFSET_M0 &&
						bwb_addr == phy_addr)
				{
					phy_addr += m19_bwb[i].offset;
				}

				else if(m19_bwb[i].offset_mode == BWB_OFFSET_M1 &&
						bwb_addr != phy_addr)
				{
					phy_addr += m19_bwb[i].offset;
				}

				//bwb offset wrap around
				phy_addr &= 0xffffffff;

				break;
			}
		}
	}


	LGBUS_PRINT("%s: 0x%010llx -> 0x%010llx\n", __func__, tmp, phy_addr);
#endif
	return phy_addr;
}
EXPORT_SYMBOL(lgbus_m19_get_ddr_addr);


/////////////////////////// PROC for debug information //////////////////////////////
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
static struct file_operations proc_status_fops =
{
	.open = lgbus_mpro_proc_status_open,
	.read = seq_read,
	.write = lgbus_mpro_proc_status_write,
	.llseek = seq_lseek,
	.release = single_release,
};

static struct file_operations asw_status_fops =
{
	.open = lgbus_mpro_proc_asw_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

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

	lgbus_mpro_get_range();

	seq_printf(s, " M16P3 v2.0 ========== memory protector info ==========\n");

	for(i = 0; i < ARRAY_SIZE(mpro_ctrl); i++)
	{

		seq_printf(s, "port : %s[%d]\n", mpro_ctrl[i].name, i);

		for(j = 0; j < ARRAY_SIZE(mpro_ctrl[i].range); j++)
		{
			seq_printf(s, "\trange(%d) 0x%08llx ~ 0x%08llx\n", j
												, mpro_ctrl[i].range[j].start
												, mpro_ctrl[i].range[j].end);

		}
		seq_printf(s, "\tisr_cnt %d\n", mpro_ctrl[i].isr_cnt);

		if(mpro_ctrl[i].vio_type)
		{
			seq_printf(s, COLOR_RED"\t--- check violation ---\n"COLOR_NONE);
			seq_printf(s, COLOR_RED"\tvio addr (ddr phy) 0x%08lx, type %s\n"COLOR_NONE
					, mpro_ctrl[i].vio_addr
					, mpro_ctrl[i].vio_type == MPRO_ISR_STATUS_RD ? "RD": "WR");
		}

		seq_printf(s, "\n");
	}

	return 0;
}


static ssize_t lgbus_mpro_proc_status_write(struct file *file
        , const char __user *buf, size_t size, loff_t *off)
{
	char *str;
	char *p;
	char *temp_str;

	int		i;
	int		addr_cnt;
	int		addr_max = M19_MPRO_RANGE_SLOT_CNT * 2;
	u64		addr[M19_MPRO_RANGE_SLOT_CNT * 2] = {0,};
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
			mpro_range.port += M19_MPRO_PORT_START;
			LGBUS_M19_SetMproRange(&mpro_range);
		}

	}

func_exit:

	vfree(str);

	return size;
}
static int lgbus_mpro_proc_asw_op(struct seq_file *s, void *data)
{
#ifdef SUPPORT_M19_MPRO_CHIP_KDRV
	/* copied from lgbus_mpro_get_range() */
	{
		int 	i;
		u32*	base_addr;
		u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

		base_addr = (u32 *)ioremap_nocache(CPU_ADDR_SWITCH_BASE, 0x100);
		CHECK_ERROR(!base_addr, return -1, "base is null\n");

		reg_base = (u32 *)base_addr;
		for(i = 0; i < M19_ADDR_SWITCH_SLOT; i++)
		{
			u32 d0, d1;

			d0 = _reg_read(reg_base++);
			d1 = _reg_read(reg_base++);

			/* print start, end, offset without low 20bit */
			seq_printf(s, "asw: 0x%04x 0x%04x 0x%04x\n", ((d0>>16) & 0xfff), (d0 & 0xffff), (d1 & 0xfff));
		}

		if(base_addr)
			iounmap((void*)base_addr);
	}

	/* copied from lgbus_get_bwb(void) */
	{
		int 	i;
		ulong	base_addr;
		u32*	reg_base; // It's 32bit register. 64bit kernel ulong is 64bit.

		base_addr = (ulong)ioremap_nocache(CPU_BWB_BASE, 0x100);
		CHECK_ERROR(!base_addr, return -1, "base is null\n");

		reg_base = (u32 *)base_addr;
		for(i = 0; i < M19_BWB_SLOT; i++)
		{
			u32 d0, d1;

			d0 = _reg_read(reg_base++);
			d1 = _reg_read(reg_base++);

			/* print bwb_start, bwb_end, bwb_offset without low 20bit and bwb_mode, bwb_offset_mode */
			seq_printf(s, "bwb: 0x%04x 0x%04x 0x%04x 0x%x 0x%x\n", ((d0>>12) & 0x7ff), (d0 & 0x7ff), (d1 & 0xfff), ((d0>>28)&0x7), ((d1>>28)&0x7));
		}

		if(base_addr)
			iounmap((void*)base_addr);
	}
#endif

	return 0;
}
