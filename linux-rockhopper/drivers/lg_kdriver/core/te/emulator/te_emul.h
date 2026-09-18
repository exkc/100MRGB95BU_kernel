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


#ifndef	_TE_EMUL_H_
#define	_TE_EMUL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

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
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int TE_EMUL_Init(void);

int TE_EMUL_RegRead(UINT32 addr, UINT32 *val);
int TE_EMUL_RegWrite(UINT32 addr, UINT32 val);

void TE_EMUL_MCU_RegWrite(UINT8 mcu, UINT32 offset, UINT32 val);

void TE_EMUL_ATSC3_RegWrite(UINT32 offset, UINT32 val);
void TE_EMUL_ATSC3_PutStream(const UINT8* buf, UINT32 size);


void TE_EMUL_MCU_SetIrqStatus(int num);
void TE_EMUL_MCU_ClearIrqStatus(int num);

void TE_EMUL_MCU_IrqRequest(int num, void (*handler)(void));
void TE_EMUL_MCU_EnableIrq(UINT32 mask);
void TE_EMUL_MCU_DisableIrq(UINT32 mask);


void TE_EMUL_CPU_SetIrqStatus(UINT32 num);
void TE_EMUL_CPU_ClearIrqStatus(UINT32 num);
int TE_EMUL_CPU_IrqRequest(unsigned int irq, irq_handler_t handler, unsigned long flags,
							const char *name, void *dev);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern UINT32	g_te_emul_reg_addr;		/* register physical address */
extern UINT8	*g_te_emul_reg_base;
extern UINT32	g_te_emul_reg_size;;

extern UINT32	g_te_emul_mem_base;
extern UINT32	g_te_emul_mem_size;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _TE_EMUL_H_ */

/** @} */

