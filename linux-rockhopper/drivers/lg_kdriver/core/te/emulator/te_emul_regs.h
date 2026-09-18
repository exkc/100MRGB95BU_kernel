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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-03-30
 *  @note		Additional information.
 */


#ifndef	_TE_EMUL_REGS_H_
#define	_TE_EMUL_REGS_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "te_emul.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define MCU_KTHREAD_CPU_ID	1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define CPU_IRQ_NUM_MCU0	0
#define CPU_IRQ_NUM_MCU1	1
#define CPU_IRQ_NUM_HW		2
#define CPU_IRQ_NUM_MAX		3


#define MCU_IRQ_NUM_TSBUF	0
#define MCU_IRQ_NUM_DSC		4
#define MCU_IRQ_NUM_BE		5
#define MCU_IRQ_NUM_IPC		9
#define MCU_IRQ_NUM_ATSC3	11

#define MCU_IRQ_NUM_MAX		12




#define REG_MCU0_OFFSET		0x0000
#define REG_MCU0_SIZE		0x200

#define REG_MCU1_OFFSET		0x0400
#define REG_MCU1_SIZE		0x200

#define REG_ATSC3_OFFSET	0x0800
#define REG_ATSC3_SIZE		0x200

#define REG_DEMOD_OFFSET	0x1000
#define REG_DEMOD_SIZE		0x100


#define MCU_REG_OFFSET_INTR2CPU_EN		0x030
#define MCU_REG_OFFSET_INTR2CPU_ST		0x034
#define MCU_REG_OFFSET_INTR2CPU_CL		0x038
#define MCU_REG_OFFSET_INTR2CPU_EV		0x03C

#define MCU_REG_OFFSET_INTR2MCU_EN		0x040
#define MCU_REG_OFFSET_INTR2MCU_ST		0x044
#define MCU_REG_OFFSET_INTR2MCU_CL		0x048
#define MCU_REG_OFFSET_INTR2MCU_EV		0x04C

#define MCU_INTR_IPC_MASK				(0x1 << 0)

#define MCU_REG_OFFSET_IPC				0x100



/* ATSC3.0 */
#define A3_REG_SIZE				0x200

#define A3_REG_OFFSET_INTR_MCU_EN		0x30
#define A3_REG_OFFSET_INTR_MCU_ST		0x34
#define A3_REG_OFFSET_INTR_MCU_CL		0x38
#define A3_REG_OFFSET_INTR_MCU_EV		0x3C

#define A3_REG_INTR_CH_META_WR_INTR_BIT(c)			(0x1 << (0x0 + (c)))
#define A3_REG_INTR_CH_META_UNIT_FULL_INTR_BIT(c)	(0x1 << (0x4 + (c)))
#define A3_REG_INTR_CH_META_AL_FULL_INTR_BIT(c)		(0x1 << (0x8 + (c)))
#define A3_REG_INTR_CH_DATA_UNIT_FULL_INTR_BIT(c)	(0x1 << (0x12 + (c)))
#define A3_REG_INTR_CH_DATA_AL_FULL_INTR_BIT(c)		(0x1 << (0x16 + (c)))




#define A3_REG_CH_MAX			4
#define A3_REG_CH_SIZE			0x40
#define A3_REG_CH_OFFSET		0x100

#define A3_REG_CH_RESET_OFFSET			0x00
#define A3_REG_CH_CONF_OFFSET			0x04
#define A3_REG_CH_FILTER_OFFSET			0x08
#define A3_REG_CH_META_SPTR_OFFSET		0x20
#define A3_REG_CH_META_EPTR_OFFSET		0x24
#define A3_REG_CH_META_WPTR_OFFSET		0x28
#define A3_REG_CH_META_RPTR_OFFSET		0x2C
#define A3_REG_CH_DATA_SPTR_OFFSET		0x30
#define A3_REG_CH_DATA_EPTR_OFFSET		0x34
#define A3_REG_CH_DATA_WPTR_OFFSET		0x38
#define A3_REG_CH_DATA_RPTR_OFFSET		0x3C


#define A3_REG_OFFSET_CH(c)				(A3_REG_CH_OFFSET + (c)*A3_REG_CH_SIZE)

#define A3_REG_OFFSET_CH_RESET(c)		(A3_REG_OFFSET_CH(c) + A3_REG_CH_RESET_OFFSET)
#define A3_REG_OFFSET_CH_CONF(c)		(A3_REG_OFFSET_CH(c) + A3_REG_CH_CONF_OFFSET)
#define A3_REG_CH_CONF_ENABLE				(0x1 << 28)
#define A3_REG_CH_CONF_LAYER_MASK			(0x7 << 0)
#define A3_REG_CH_CONF_LAYER_LGC			(0x0 << 0)
#define A3_REG_CH_CONF_LAYER_BB				(0x1 << 0)
#define A3_REG_CH_CONF_LAYER_ALP			(0x2 << 0)
#define A3_REG_CH_CONF_LAYER_ALP_PAYLOAD	(0x3 << 0)


#define A3_REG_OFFSET_CH_FILTER(c)		(A3_REG_OFFSET_CH(c) + A3_REG_CH_FILTER_OFFSET)
#define A3_REG_CH_FILTER_PLP_EN				(0x1 << 31)
#define A3_REG_CH_FILTER_PLP_ID(id)			((id) << 16)
#define A3_REG_CH_FILTER_GET_PLP_ID(v)		(((v)>>16) & 0xFF)


#define A3_REG_OFFSET_CH_META_SPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_META_SPTR_OFFSET)
#define A3_REG_OFFSET_CH_META_EPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_META_EPTR_OFFSET)
#define A3_REG_OFFSET_CH_META_WPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_META_WPTR_OFFSET)
#define A3_REG_OFFSET_CH_META_RPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_META_RPTR_OFFSET)

#define A3_REG_OFFSET_CH_DATA_SPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_DATA_SPTR_OFFSET)
#define A3_REG_OFFSET_CH_DATA_EPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_DATA_EPTR_OFFSET)
#define A3_REG_OFFSET_CH_DATA_WPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_DATA_WPTR_OFFSET)
#define A3_REG_OFFSET_CH_DATA_RPTR(c)	(A3_REG_OFFSET_CH(c) + A3_REG_CH_DATA_RPTR_OFFSET)




#define MEM_WRITE32(addr,data)	*(volatile UINT32*)(addr) = (UINT32)(data)
#define MEM_READ32(addr)		*(volatile UINT32*)(addr)

#define MEM_WRITE16(addr,data)	*(volatile UINT16*)(addr) = (UINT8)(data)
#define MEM_READ16(addr)		*(volatile UINT16*)(addr)

#define MEM_WRITE8(addr,data)	*(volatile UINT8*)(addr) = (UINT8)(data)
#define MEM_READ8(addr)			*(volatile UINT8*)(addr)

#define MEM_WRITE(addr,data)	MEM_WRITE32(addr, data)
#define MEM_READ(addr)			MEM_READ32(addr)


#define REG_WRITE(offset,data)	MEM_WRITE32(g_te_emul_reg_base+(offset),data)
#define REG_READ(offset)		MEM_READ32(g_te_emul_reg_base+(offset))


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _TE_EMUL_H_ */

/** @} */

