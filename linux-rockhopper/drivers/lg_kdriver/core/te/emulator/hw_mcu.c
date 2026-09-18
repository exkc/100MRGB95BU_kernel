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
 *  Emulator driver for TE
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
#include <linux/smp.h>

#include "te_impl.h"
#include "te_emul.h"
#include "te_emul_regs.h"


/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define MCU_FLAGS_IRQ_ENABLE	(0x1 << 0)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	void	(*func)(void);
} IRQ_HANDLER_T;

typedef struct
{
	volatile UINT32	status;
	volatile UINT32	enable;
} IRQ_REG_T;


/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static IRQ_HANDLER_T irqs[MCU_IRQ_NUM_MAX];
static IRQ_REG_T irq_reg;

static DEFINE_SPINLOCK(mcu_lock);


static void ISR(void *info)
{
	int i;
	UINT32 val;

	//LOG_MCU("MCU ISR(%d)\n", signo);

	while(1)
	{
		val = irq_reg.status&irq_reg.enable;
		if(!val) break;

		for(i=(MCU_IRQ_NUM_MAX-1); i>=0; i--)
		{
			if((1<<i)&irq_reg.status)
			{
				if(irqs[i].func)
				{
					irqs[i].func();
				}
			}
		}
	}
}


static void SetIrqStatus(int num, int enable)
{
	unsigned long flag;

	if(num >= MCU_IRQ_NUM_MAX)
	{
		LOG_ERROR("invalid irq num(%d):enable(%d)\n", num, enable);
		return;
	}

	spin_lock_irqsave(&mcu_lock, flag);
	if(enable)	irq_reg.status |= (0x1 << num);
	else		irq_reg.status &= ~(0x1 << num);
	spin_unlock_irqrestore(&mcu_lock, flag);
}

static int SendEvent(void)
{
	int rc;
#if 0
	struct call_single_data data = { .flags = 0 };

	data.func = ISR;
	data.info = NULL;
	rc = smp_call_function_single_async(0, &data);
#else
	rc = smp_call_function_single(MCU_KTHREAD_CPU_ID, ISR, NULL, 0);
#endif
	if(rc)
	{
		LOG_ERROR("can't send event to mcu. rc=%d\n", rc);
		return rc;
	}

	return 0;
}

void TE_EMUL_MCU_SetIrqStatus(int num)
{
	SetIrqStatus(num, 1);
	SendEvent();
}
EXPORT_SYMBOL(TE_EMUL_MCU_SetIrqStatus);

void TE_EMUL_MCU_ClearIrqStatus(int num)
{
	SetIrqStatus(num, 0);
}
EXPORT_SYMBOL(TE_EMUL_MCU_ClearIrqStatus);


void TE_EMUL_MCU_IrqRequest(int num, void (*handler)(void))
{
	if(num >= MCU_IRQ_NUM_MAX)
	{
		LOG_ERROR("invalid irq num(%d)\n", num);
		return;
	}

	LOG_MCU("MCU_IrqRequest(%d,%p)\n", num, handler);

	irqs[num].func = handler;
}
EXPORT_SYMBOL(TE_EMUL_MCU_IrqRequest);

void TE_EMUL_MCU_EnableIrq(UINT32 mask)
{
	unsigned long flag;

	spin_lock_irqsave(&mcu_lock, flag);
	irq_reg.enable |= mask;
	spin_unlock_irqrestore(&mcu_lock, flag);

}
EXPORT_SYMBOL(TE_EMUL_MCU_EnableIrq);

void TE_EMUL_MCU_DisableIrq(UINT32 mask)
{
	unsigned long flag;

	spin_lock_irqsave(&mcu_lock, flag);
	irq_reg.enable &= ~(mask);
	spin_unlock_irqrestore(&mcu_lock, flag);
}
EXPORT_SYMBOL(TE_EMUL_MCU_DisableIrq);

