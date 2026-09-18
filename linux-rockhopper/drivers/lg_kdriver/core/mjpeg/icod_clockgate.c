/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2021 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  clock gating implementation for icod device
 *
 *  author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2013.06.27
 *  note		Additional information.
 *
 *  @addtogroup lg115x_icod
 *	@{
 */

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        File Inclusions
-----------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <asm/io.h>

#include "base_types.h"
#include "icod_clockgate.h"
#include "mjpeg_drv.h"
#include "os_util.h"
#include "sys_regs.h"

/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/
#define ICOD_NOTI(format, args...) MJPEG_NOTI(format, ##args)

#if 1
#define ICOD_DEBUG(format, args...) MJPEG_DEBUG(format, ##args)
#else
#define ICOD_DEBUG(format, args...)
#endif

/*-----------------------------------------------------------------------------
        Type Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        External Function Prototype Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        External Variables
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Functions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
  Static Function Prototypes Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
  Static Variables
-----------------------------------------------------------------------------*/

/*========================================================================================
  Implementation Group
========================================================================================*/

DEFINE_SPINLOCK(icod_lock);

#define ICOD_LOCK() spin_lock(&icod_lock)
#define ICOD_UNLOCK() spin_unlock(&icod_lock)

#if defined(CHIP_NAME_o26)
//#define ICOD_BRINGUP
#define IPW_ICOD_BRINGUP
#endif

#if defined(CHIP_NAME_o26)
#define IPW_CLK_GATE_BASE (0xCA3A2014)
#define VENC_IPW_CLK_GATE_BASE_SHIFT (2)
#define ICOD_IPW_CLK_GATE_BASE_SHIFT (5)
#define ICVE_IPW_CLK_GATE_BASE_SHIFT (1) //reg_tivvm_sbw_clk_gate_en
static volatile unsigned int *ipw_clk_gate_power_02_reg;
#elif defined(CHIP_NAME_o24)
#define IPW_CLK_GATE_BASE (0xF33F3014)
#define VENC_IPW_CLK_GATE_BASE_SHIFT (2)
#define ICOD_IPW_CLK_GATE_BASE_SHIFT (5)
#define ICVE_IPW_CLK_GATE_BASE_SHIFT (1) //reg_icve_sbw_clk_gate_en
static volatile unsigned int *ipw_clk_gate_power_02_reg;
#endif

static UINT32 icod_clock_status;

int icod_ipw_clk_gate_init(void)
{
#if !defined(CHIP_NAME_o22) && !defined(CHIP_NAME_m23)
#if defined(ICOD_ON_FPGA) || defined(ICOD_BRINGUP) || defined(IPW_ICOD_BRINGUP)
	return 0;
#endif
	ipw_clk_gate_power_02_reg = (volatile unsigned int *)ioremap(
			IPW_CLK_GATE_BASE, sizeof(unsigned int));
	if (!ipw_clk_gate_power_02_reg)
		return -1;
#endif
	return 0;
}

static void icod_ipw_clk_gate_enable(bool on)
{
#if !defined(CHIP_NAME_o22) && !defined(CHIP_NAME_m23)
	volatile unsigned int val;
	unsigned long flags;

#if defined(ICOD_ON_FPGA) || defined(ICOD_BRINGUP) || defined(IPW_ICOD_BRINGUP)
	return;
#endif
	CTOP_CTRL_EnterCriticalSection("ipw_clock_gating", flags);
	val = ioread32(ipw_clk_gate_power_02_reg);
	ICOD_DEBUG("=> val %x (ipw gate_enable %d)\n", val, on);
	if (on) {
		if (val &
			(1
			 << VENC_IPW_CLK_GATE_BASE_SHIFT)) // check venc bit when gate enable
			val = val |
				  (1 << ICVE_IPW_CLK_GATE_BASE_SHIFT); // set icve bit also

		val = val | (1 << ICOD_IPW_CLK_GATE_BASE_SHIFT);
	} else {
		val = val & ~(1 << ICOD_IPW_CLK_GATE_BASE_SHIFT);
		val = val &
			  ~(1 << ICVE_IPW_CLK_GATE_BASE_SHIFT); // icve gate disable also
	}
	iowrite32(val, ipw_clk_gate_power_02_reg);
	ICOD_DEBUG("<= val %x (ipw gate_enable %d)\n", val, on);
	CTOP_CTRL_ExitCriticalSection("ipw_clock_gating", flags);
#endif
}

static inline void ICOD_ClockEnable(ICOD_CLOCK_TYPE_T eClockType)
{
	// clock_sel (0:enable,1:disable)
	UINT8 clock_sel = (eClockType == ICOD_CLOCK_TYPE_DISABLE) ? 0x1 : 0x0;

#if defined(ICOD_ON_FPGA) || defined(ICOD_BRINGUP)
	return;
#endif
	ICOD_DEBUG("%s :: ENTER\n", __F__);

	icod_ipw_clk_gate_enable(false);

#if defined(CHIP_NAME_o22)
	CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ICOD, crg_icod02);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ICOD, crg_icod02, reg_jpeg_clk_gate_en,
						 clock_sel);
	CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ICOD, crg_icod02);
#elif defined(CHIP_NAME_m23)
	CTOP_CTRL_M23Ax_RdFL(SCRG_CTRL_ICOD, crg_icod02);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_ICOD, crg_icod02, reg_jpeg_clk_gate_en,
						 clock_sel);
	CTOP_CTRL_M23Ax_WrFL(SCRG_CTRL_ICOD, crg_icod02);
#elif defined(CHIP_NAME_o24)
	CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_ICOD, crg_icod2);
	CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_ICOD, crg_icod2, reg_jpeg_clk_gate_en,
						 clock_sel);
	CTOP_CTRL_O24Ax_WrFL(SCRG_CTRL_ICOD, crg_icod2);
#elif defined(CHIP_NAME_o26)
	CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_ICOD, crg_icod002);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ICOD, crg_icod002, reg_jpeg_clk_gate_en,
						 clock_sel);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ICOD, crg_icod002);
#endif

	if (eClockType == ICOD_CLOCK_TYPE_DISABLE)
		icod_ipw_clk_gate_enable(true);

	ICOD_NOTI("%s :: Clock gating: %s\n", __FUNCTION__,
			  (eClockType == ICOD_CLOCK_TYPE_DISABLE) ? "Enable" : "Disable");
	ICOD_DEBUG("%s :: EXIT\n", __F__);

	return;
}

void ICOD_ClockOff(void)
{
	ICOD_LOCK();
	if (icod_clock_status > 0)
		icod_clock_status--;

	if (!icod_clock_status)
		ICOD_ClockEnable(ICOD_CLOCK_TYPE_DISABLE);
	ICOD_UNLOCK();
}

void ICOD_ClockOn(void)
{
	ICOD_LOCK();
	if (!icod_clock_status)
		ICOD_ClockEnable(ICOD_CLOCK_TYPE_ENABLE);
	icod_clock_status++;
	ICOD_UNLOCK();
}

void ICOD_ClockResume(void)
{
	ICOD_LOCK();
	if (!icod_clock_status)
		ICOD_ClockEnable(ICOD_CLOCK_TYPE_DISABLE);
	else
		ICOD_ClockEnable(ICOD_CLOCK_TYPE_ENABLE);
	ICOD_UNLOCK();
}

void ICOD_ClockInit(void)
{
	ICOD_LOCK();
	icod_clock_status = 0;
	ICOD_ClockEnable(ICOD_CLOCK_TYPE_DISABLE);
	ICOD_UNLOCK();
}
// EOF
