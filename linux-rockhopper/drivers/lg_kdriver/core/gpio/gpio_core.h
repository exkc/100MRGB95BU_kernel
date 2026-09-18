/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.

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
 *  driver interface header for gpio device. ( used only within kdriver )
 *
 *  @author		ks.hyun (ks.hyun@lge.com)
 *  				jun.kong (jun.kong@lge.com)
 *  @version	1.0
 *  @date		2012.05.03
 *
 *  @addtogroup lg115x_gpio
 *	@{
 */

#ifndef	__GPIO_CORE_H__
#define	__GPIO_CORE_H__

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/irqreturn.h>
#include "debug_util.h"
#include "gpio_cfg.h"
#include "gpio_kapi.h"

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
typedef struct GPIO_DEV *LX_GPIO_HANDLE;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	int	GPIO_DevInit(void);

extern	int GPIO_DevSetPinMux(UINT32 port, BOOLEAN enable);
extern	int GPIO_DevGetPinMux(UINT32 port, BOOLEAN *enable);
extern	int GPIO_DevSetMode(UINT32 port, LX_GPIO_MODE_T mode);
extern	int GPIO_DevGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
extern	int GPIO_DevSetValue(UINT32 port, LX_GPIO_VALUE_T value);
extern	int GPIO_DevGetValue(UINT32 port, LX_GPIO_VALUE_T *value);
extern 	int GPIO_DevSetISR(UINT32 port, void (*pfnGPIO_CB)	(UINT32 ), UINT32 enable, void * info);
extern 	int GPIO_DevGetIntrCntDur(UINT32 port, UINT32 count, UINT32 *usec);

extern	int GPIO_DevExSetPinMux(UINT32 port, BOOLEAN enable);
extern	int GPIO_DevExGetPinMux(UINT32 port, BOOLEAN *enable);
extern	int GPIO_DevExSetMode(UINT32 port, LX_GPIO_MODE_T mode);
extern	int GPIO_DevExGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
extern	int GPIO_DevExSetValue(UINT32 port, LX_GPIO_VALUE_T value);
extern	int GPIO_DevExGetValue(UINT32 port, LX_GPIO_VALUE_T *value);
extern   int GPIO_DevGetIntrValue(UINT32 *port, LX_GPIO_VALUE_T *value);
extern 	int GPIO_DevSetIntrArrayNum(UINT32 intrArrayNum);
extern 	int _GPIO_GetValue_H13Bx(UINT32 port, LX_GPIO_VALUE_T *value);


extern 	int _GPIO_GetValue(UINT32 port, LX_GPIO_VALUE_T *value);
extern 	int _GPIO_SetValue(UINT32 port, LX_GPIO_VALUE_T value);

extern int _GPIO_GetMode(UINT32 port, LX_GPIO_MODE_T *mode);
extern int _GPIO_SetMode(UINT32 port, LX_GPIO_MODE_T mode);
extern int _GPIO_GetValueR(UINT32 port);
extern int _GPIO_GetModeR(UINT32 port);
extern int _GPIO_GetValueEx(UINT32 port);
extern int _GPIO_GetModeEx(UINT32 port);
extern int _GPIO_SetIntr(UINT32 port, UINT32 enable);

#ifdef INCLUDE_M17_CHIP_KDRV
extern int _GPIO_SetPinMux_M17Ax(UINT32 port, BOOLEAN enable);
#endif

extern 	int 	_GPIO_SetIntrAction(UINT32 port, void (*pfnGPIO_CB)(UINT32 value), UINT32 enable, LX_GPIO_INFO_T *info);
#ifdef KDRV_CONFIG_PM
extern	int GPIO_DevResume(void);
extern	int GPIO_DevSuspend(void);
extern	int GPIO_DevBeforeSuspend(void);
#endif

extern irqreturn_t GPIO_interrupt(int irq, void *dev_id, struct pt_regs *regs);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern UINT32 *		gpio_intr_num;
extern 	int gpio_intr_pin;
extern  void** _gpioBaseAddr;
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* __GPIO_CORE_H__ */

/** @} */
