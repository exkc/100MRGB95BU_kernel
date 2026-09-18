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

#define CPU_FLAGS_IRQ_ENABLE		(0x1 << 0)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	unsigned int	irq;
	const char		*name;
	irq_handler_t	func;
	void			*dev;
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
static IRQ_HANDLER_T irqs[CPU_IRQ_NUM_MAX];
static IRQ_REG_T irq_reg;


static DEFINE_SPINLOCK(cpu_lock);


static void ISR(void *info)
{
	int i;
	UINT32 val;

//	LOG_CPU("CPU ISR(%d)\n", signo);

	while(1)
	{
		val = irq_reg.status&irq_reg.enable;
		if(!val) break;

		for(i=0; i<CPU_IRQ_NUM_MAX; i++)
		{
			if((1<<i)&irq_reg.status)
			{
				IRQ_HANDLER_T *h = &irqs[i];
				if(h->func)
				{
					h->func(h->irq, h->dev);
				}
			}
		}
	}
}


int TE_EMUL_CPU_IrqRequest(unsigned int irq, irq_handler_t handler, unsigned long flags,
							const char *name, void *dev)
{
	int n;
	IRQ_HANDLER_T *h;
	unsigned long flag;
	TE_CFG_T *cfg = TE_GetConfig();

	if(irq == cfg->hw_irq_num) n = CPU_IRQ_NUM_HW;
	else if(irq == cfg->mcu_irq_num[0]) n = CPU_IRQ_NUM_MCU0;
	else if(irq == cfg->mcu_irq_num[1]) n = CPU_IRQ_NUM_MCU1;
	else
	{
		LOG_ERROR("invalid irq(%d)\n", irq);
		return -EINVAL;
	}

//	LOG_CPU("IrqRequestCPU(%d,%p)\n", num, handler);

	h = &irqs[n];

	h->irq	= irq;
	h->name	= name;
	h->func	= handler;
	h->dev	= dev;

	spin_lock_irqsave(&cpu_lock, flag);
	irq_reg.enable |= (0x1 << n);
	spin_unlock_irqrestore(&cpu_lock, flag);

	return 0;
}

static void SetIrqStatus(UINT32 num, int enable)
{
	unsigned long flag;

	if(num >= CPU_IRQ_NUM_MAX)
	{
		LOG_ERROR("invalid irq num(%d)\n", num);
		return;
	}

	spin_lock_irqsave(&cpu_lock, flag);
	if(enable)	irq_reg.status |= (0x1 << num);
	else		irq_reg.status &= ~(0x1 << num);
	spin_unlock_irqrestore(&cpu_lock, flag);
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
	rc = smp_call_function_single(0, ISR, NULL, 0);
#endif
	if(rc)
	{
		LOG_ERROR("can't send event to cpu. rc=%d\n", rc);
		return rc;
	}

	return 0;
}

void TE_EMUL_CPU_SetIrqStatus(UINT32 num)
{
	SetIrqStatus(num, 1);
	SendEvent();
}

void TE_EMUL_CPU_ClearIrqStatus(UINT32 num)
{
	SetIrqStatus(num, 0);
}

