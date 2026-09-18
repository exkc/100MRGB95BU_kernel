#ifndef __SYS_REGS_H__
#define __SYS_REGS_H__

#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_drv.h"
#include <linux/spinlock.h>

#ifdef INCLUDE_L9_CHIP_KDRV
#include "l9/sys/ctop_ctrl_reg_l9.h"
#include "l9/sys/actop_ctrl_reg_l9.h"
#include "l9/sys/ace_reg_l9.h"
#endif

#ifdef INCLUDE_H13_CHIP_KDRV
#include "h13/sys/ctop_ctrl_reg_h13.h"
#include "h13/sys/ace_reg_h13.h"
#include "h13/sys/cpu_top_reg_h13.h"
#endif

#ifdef INCLUDE_M14_CHIP_KDRV
#include "m14/sys/ctop_ctrl_reg_m14.h"
#include "m14/sys/atop_reg_m14.h"
#include "m14/sys/cpu_top_reg_m14.h"
#endif

#ifdef INCLUDE_H14_CHIP_KDRV
#include "h14/sys/ctop_ctrl_reg_h14.h"
#include "h14/sys/atop_reg_h14.h"
#include "h14/sys/cpu_top_reg_h14.h"
#endif

#ifdef INCLUDE_H15_CHIP_KDRV
#include "h15/sys/ctop_ctrl_reg_h15.h"
#include "h15/sys/atop_reg_h15.h"
//#include "h15/sys/cpu_top_reg_h15.h"
#endif

#ifdef INCLUDE_M16_CHIP_KDRV
#include "m16/sys/ctop_ctrl_reg_m16.h"
#include "m16/sys/atop_reg_m16.h"
#endif

#ifdef INCLUDE_M16P_CHIP_KDRV
#include "m16p/sys/atop_reg_m16p.h"
#include "m16p/sys/ctop_ctrl_reg_m16p.h"
#endif

#ifdef INCLUDE_M17_CHIP_KDRV
#include "m17/sys/atop_reg_m17.h"
#include "m17/sys/ctop_ctrl_reg_m17.h"
#endif

#ifdef INCLUDE_M19_CHIP_KDRV
#include "m19/sys/adc_dig_reg_m19.h"
#include "m19/sys/ctop_ctrl_reg_m19.h"
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
#include "l18/sys/ctop_ctrl_reg_l18.h"
#include "l18/sys/adc_dig_reg_l18.h"
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
#include "o18/sys/ctop_ctrl_reg_o18.h"
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
#include "o20/sys/ctop_ctrl_reg_o20.h"
#include "o20/sys/adc_dig_reg_o20.h"
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
#include "e60/sys/ctop_ctrl_reg_e60.h"
#include "e60/sys/adc_dig_reg_e60.h"
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
#include "o22/sys/ctop_ctrl_reg_o22.h"
#include "o22/sys/mip_dig_reg_o22.h"
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
#include "m23/sys/ctop_ctrl_reg_m23.h"
#include "m23/sys/mip_dig_reg_m23.h"
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
#include "o24/sys/ctop_ctrl_reg_o24.h"
#include "o24/sys/mip_dig_reg_o24.h"
#endif

#ifdef INCLUDE_O26_CHIP_KDRV
#include "o26/sys/ctop_ctrl_reg_o26.h"
#include "o26/sys/mip_dig_reg_o26.h"
#endif

// Common spin lock to pretect critical section of CTOP register among multi processes and interrupt handlers.
// If a ctop register has the defintions for multiple IPs, all functions which use it should get the access right
// before updating the ctop register.
//
// (example)
// unsigned long flags;
//
// CTOP_CTRL_EnterCriticalSection("ipw_clock_gating", flags);
// ...
// CTOP_CTRL_ExitCriticalSection("ipw_clock_gating", flags);
//
// see http://clm.lge.com/issue/browse/SICDTV-12942
//
extern spinlock_t* CTOP_CTRL_GetSpinlock(void);
extern unsigned long _CTOP_CTRL_EnterCriticalSection(const char *func, int line, const char *key);
extern void _CTOP_CTRL_ExitCriticalSection(const char *func, int line, const char *key, unsigned long flags);

#define CTOP_CTRL_EnterCriticalSection(key, flags) \
do { \
        flags = _CTOP_CTRL_EnterCriticalSection(__func__, __LINE__, key); \
} while(0)

#define CTOP_CTRL_ExitCriticalSection(key, flags) \
        _CTOP_CTRL_ExitCriticalSection(__func__, __LINE__, key, flags)

#endif
