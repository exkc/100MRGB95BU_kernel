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
 *  misc driver for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-01-07
 *  @note		Additional information.
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/kthread.h>

#include "te_impl.h"
#include "te_emul.h"
#include "te_emul_regs.h"


/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define CHECK_REG_REGION(addr)	\
	CHECK_ERROR((addr) < emul_reg_base || (addr) >= emul_reg_end, \
			return RET_INVALID_PARAMS, "invalid reg addr(0x%x)\n", addr)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/
UINT8 *g_te_emul_reg_base;
EXPORT_SYMBOL(g_te_emul_reg_base);

UINT32 g_te_emul_reg_size;
EXPORT_SYMBOL(g_te_emul_reg_size);

UINT32 g_te_emul_reg_addr;
EXPORT_SYMBOL(g_te_emul_reg_addr);

UINT32 g_te_emul_mem_base;
UINT32 g_te_emul_mem_size;

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static UINT32 emul_reg_base;
static UINT32 emul_reg_end;





int TE_EMUL_RegRead(UINT32 addr, UINT32 *val)
{
	CHECK_REG_REGION(addr);

	*val = MEM_READ32(addr);

	return RET_OK;
}
EXPORT_SYMBOL(TE_EMUL_RegRead);


int TE_EMUL_RegWrite(UINT32 addr, UINT32 val)
{
	UINT32 offset;

	CHECK_REG_REGION(addr);

	offset = addr - emul_reg_base;;
	if(offset >= REG_MCU0_OFFSET && offset < (REG_MCU0_OFFSET+REG_MCU0_SIZE))
	{
		offset -= REG_MCU0_OFFSET;
		TE_EMUL_MCU_RegWrite(0, offset, val);
	}
	else if(offset >= REG_MCU1_OFFSET && offset < (REG_MCU1_OFFSET+REG_MCU1_SIZE))
	{
		MEM_WRITE32(addr, val);
	}
	else if(offset >= REG_ATSC3_OFFSET && offset < (REG_ATSC3_OFFSET+REG_ATSC3_SIZE))
	{
		offset -= REG_ATSC3_OFFSET;
		TE_EMUL_ATSC3_RegWrite(offset, val);
	}
	else
	{
		MEM_WRITE32(addr, val);
	}

	return RET_OK;
}
EXPORT_SYMBOL(TE_EMUL_RegWrite);

#if 0
static void InitATSC3(void)
{
	UINT32 v;
	UINT8 *meta_buf, *data_buf;

#define DATA_BUF_SIZE	((64*1024)*10)
#define META_BUF_SIZE	(16*(DATA_BUF_SIZE/64))		// TODO: guess the average payload size

	/* Set META Buffer */
	meta_buf = kmalloc(META_BUF_SIZE, GFP_KERNEL);
	CHECK_ERROR(!meta_buf, return, "can't alloc mem\n");

	data_buf = kmalloc(DATA_BUF_SIZE, GFP_KERNEL);
	CHECK_ERROR(!meta_buf, return, "can't alloc mem\n");

	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_META_SPTR(0), (UINT32)meta_buf);
	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_META_EPTR(0), (UINT32)(meta_buf + META_BUF_SIZE));
	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_META_RPTR(0), (UINT32)meta_buf);

	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_DATA_SPTR(0), (UINT32)data_buf);
	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_DATA_EPTR(0), (UINT32)(data_buf + DATA_BUF_SIZE));
	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_DATA_RPTR(0), (UINT32)data_buf);

	/* Enable channel 0 */
	v = A3_REG_CH_CONF_ENABLE | A3_REG_CH_CONF_LAYER_BB;
	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_CONF(0), v);

	v = A3_REG_CH_FILTER_PLP_EN | A3_REG_CH_FILTER_PLP_ID(0);
	TE_EMUL_ATSC3_RegWrite(A3_REG_OFFSET_CH_FILTER(0), v);
}
#endif

int TE_EMUL_Init(void)
{
	TE_CFG_T *cfg = TE_GetConfig();
	LX_MEMCFG_T *mem_cfg;

	g_te_emul_reg_addr = cfg->reg_base_addr;
	g_te_emul_reg_size = cfg->reg_total_size;

	g_te_emul_reg_base = kcalloc(1, g_te_emul_reg_size, GFP_KERNEL);
	CHECK_ERROR(!g_te_emul_reg_base, return RET_ERROR, "no memory");

	emul_reg_base	= (UINT32)g_te_emul_reg_base;
	emul_reg_end	= emul_reg_base + g_te_emul_reg_size;

	mem_cfg = TE_GetMemConfig(TE_MEM_TYPE_0);
	g_te_emul_mem_size = mem_cfg->size;
	g_te_emul_mem_base = (UINT32)vmap_phys(mem_cfg->base, mem_cfg->size);
	CHECK_ERROR(!g_te_emul_mem_base, return RET_OUT_OF_MEMORY, "vmap_phys fail");

	LOG_NOTI("TE_EMUL_Init - reg:0x%08x--0x%08x, mem:0x%08x++0x%x\n",
			emul_reg_base, emul_reg_end, g_te_emul_mem_base, g_te_emul_mem_size);

#if 0
	InitATSC3();
#endif

	return RET_OK;
}
