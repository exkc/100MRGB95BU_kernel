#ifndef __XTRUNTIME_H__
#define __XTRUNTIME_H__

#include "xemul/te.h"

typedef void (*_xtos_handler)(void);

//irq_disable()
static inline void _xtos_ints_off(unsigned int mask)
{
	XEMUL_MCU_DisableIrq(mask);
}

static inline void _xtos_ints_on(unsigned int mask)
{
	XEMUL_MCU_EnableIrq(mask);
}

//???
static inline void _xtos_clear_ints(unsigned int mask)
{
}

static inline void _xtos_set_interrupt_handler(unsigned int num, _xtos_handler handler)
{
	XEMUL_MCU_IrqRequest(num, handler);
}

#endif
