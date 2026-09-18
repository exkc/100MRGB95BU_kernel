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
 *  main driver implementation for gpio device.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  			jun.kong (jun.kong@lge.com)
 *  version		1.0
 *  date		2012.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg115x_gpio
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/device.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "gpio_drv.h"
#include "gpio_reg.h"
#include "sys_regs.h"
#include "sys_io.h"

#ifndef O24_GPIO0_BASE
	#define O24_GPIO0_BASE (0xfd400000)
#endif

#ifndef O26_GPIO0_BASE
	#define O26_GPIO0_BASE (0xfd400000)
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#define GPIO_STRSIZE       32
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define GPIO_LOCK_INIT(dev)		OS_InitMutex(&dev->lock, OS_SEM_ATTR_DEFAULT)

/* ret 0: lock ok 1: lock fail */
#define GPIO_LOCK(dev,ret)					\
	do{ 								\
		if(in_interrupt() == 0){ 		\
			ret = OS_LockMutex(&dev->lock);	\
		}								\
		else 							\
		{								\
			ret = 1;					\
		}								\
	}while(0)
//#define GPIO_LOCK(dev)			OS_LockMutex(&dev->lock)


#define GPIO_UNLOCK(dev,ret)				\
	do{									\
		if(ret == 0){		\
			OS_UnlockMutex(&dev->lock);	\
		}								\
	}while(0)

//#define GPIO_UNLOCK(dev)		OS_UnlockMutex(&dev->lock)

#define GPIO_EX_LOCK_INIT(dev)	OS_InitMutex(&dev->ex_lock, OS_SEM_ATTR_DEFAULT)


/* ret 0: lock ok 1: lock fail */
#define GPIO_EX_LOCK(dev,ret)					\
	do{ 								\
		if(in_interrupt() == 0){ 		\
			ret = OS_LockMutex(&dev->ex_lock);	\
		}								\
		else 							\
		{								\
			ret = 1;					\
		}								\
	}while(0)


#define GPIO_EX_UNLOCK(dev,ret)				\
	do{									\
		if(ret == 0){		\
			OS_UnlockMutex(&dev->ex_lock);	\
		}								\
	}while(0)


#if 0
#define GPIO_CORE_DEBUG(format, args...)	GPIO_ERROR(format, ##args)
#else
#define GPIO_CORE_DEBUG(format, args...)	do{}while(0)
#endif

//BEGIN GPIO_KERNEL_API
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>

#define GPIOIPNUM	18


struct gpiod_lookup_table gpios_table = {

	.dev_id = "gpio_kerneltable",
	.table = {
#if defined(INCLUDE_O18_CHIP_KDRV)  || defined(INCLUDE_M17_CHIP_KDRV) ||defined(INCLUDE_M19_CHIP_KDRV) ||defined(INCLUDE_O20_CHIP_KDRV) || defined(INCLUDE_E60_CHIP_KDRV) || defined(INCLUDE_O22_CHIP_KDRV)  || defined(INCLUDE_M23_CHIP_KDRV) || defined(INCLUDE_O24_CHIP_KDRV) || defined(INCLUDE_O26_CHIP_KDRV)
		GPIO_LOOKUP_IDX("fd400000.gpio", 0, "0", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 1, "1", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 2, "2", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 3, "3", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 4, "4", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 5, "5", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 6, "6", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd400000.gpio", 7, "7", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd410000.gpio", 0, "8", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 1, "9", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 2, "10", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 3, "11", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 4, "12", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 5, "13", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 6, "14", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd410000.gpio", 7, "15", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd420000.gpio", 0, "16", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 1, "17", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 2, "18", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 3, "19", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 4, "20", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 5, "21", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 6, "22", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd420000.gpio", 7, "23", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd430000.gpio", 0, "24", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 1, "25", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 2, "26", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 3, "27", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 4, "28", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 5, "29", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 6, "30", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd430000.gpio", 7, "31", 0, GPIO_ACTIVE_HIGH),


		GPIO_LOOKUP_IDX("fd440000.gpio", 0, "32", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 1, "33", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 2, "34", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 3, "35", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 4, "36", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 5, "37", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 6, "38", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd440000.gpio", 7, "39", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd450000.gpio", 0, "40", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 1, "41", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 2, "42", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 3, "43", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 4, "44", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 5, "45", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 6, "46", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd450000.gpio", 7, "47", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd460000.gpio", 0, "48", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 1, "49", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 2, "50", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 3, "51", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 4, "52", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 5, "53", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 6, "54", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd460000.gpio", 7, "55", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd470000.gpio", 0, "56", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 1, "57", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 2, "58", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 3, "59", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 4, "60", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 5, "61", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 6, "62", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd470000.gpio", 7, "63", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd480000.gpio", 0, "64", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 1, "65", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 2, "66", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 3, "67", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 4, "68", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 5, "69", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 6, "70", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd480000.gpio", 7, "71", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd490000.gpio", 0, "72", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 1, "73", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 2, "74", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 3, "75", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 4, "76", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 5, "77", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 6, "78", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd490000.gpio", 7, "79", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd4a0000.gpio", 0, "80", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 1, "81", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 2, "82", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 3, "83", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 4, "84", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 5, "85", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 6, "86", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4a0000.gpio", 7, "87", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd4b0000.gpio", 0, "88", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 1, "89", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 2, "90", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 3, "91", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 4, "92", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 5, "93", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 6, "94", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4b0000.gpio", 7, "95", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd4c0000.gpio", 0, "96", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 1, "97", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 2, "98", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 3, "99", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 4, "100", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 5, "101", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 6, "102", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4c0000.gpio", 7, "103", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd4d0000.gpio", 0, "104", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 1, "105", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 2, "106", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 3, "107", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 4, "108", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 5, "109", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 6, "110", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4d0000.gpio", 7, "111", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd4e0000.gpio", 0, "112", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 1, "113", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 2, "114", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 3, "115", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 4, "116", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 5, "117", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 6, "118", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4e0000.gpio", 7, "119", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd4f0000.gpio", 0, "120", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 1, "121", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 2, "122", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 3, "123", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 4, "124", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 5, "125", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 6, "126", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd4f0000.gpio", 7, "127", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd500000.gpio", 0, "128", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 1, "129", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 2, "130", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 3, "131", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 4, "132", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 5, "133", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 6, "134", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd500000.gpio", 7, "135", 0, GPIO_ACTIVE_HIGH),

		GPIO_LOOKUP_IDX("fd510000.gpio", 0, "136", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 1, "137", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 2, "138", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 3, "139", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 4, "140", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 5, "141", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 6, "142", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("fd510000.gpio", 7, "143", 0, GPIO_ACTIVE_HIGH),
#endif
		{ },
	},
};

//END GPIO_KERNEL_API

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT8	direction;
	UINT8	data;
} GPIO_PM_DATA_T;


typedef struct GPIO_DEV
{
	OS_SEM_T	lock;
	bool			is_suspended;
	UINT32		max_num;
	UINT32 		intr_num[GPIO_IRQ_NUM_NR];
	UINT32		isGpio[GPIO_PIN_MAX];
	UINT32		useIntr[GPIO_PIN_MAX];
	int 		(*SetPinMux)(UINT32 port, BOOLEAN enable);
	int 		(*GetPinMux)(UINT32 port, BOOLEAN *enable);
	int 		(*SetValue)	(UINT32 port, LX_GPIO_VALUE_T value);
	int 		(*GetValue)	(UINT32 port, LX_GPIO_VALUE_T *value);
	int 		(*SetMode)	(UINT32 port, LX_GPIO_MODE_T mode);
	int 		(*GetMode)	(UINT32 port, LX_GPIO_MODE_T *mode);
	//int 		(*SetIntr)	(UINT32 port, void (*pfnGPIO_CB)(UINT32 value), UINT32 enable );
	int 		(*SetIntrAction)	(UINT32 port, void (*pfnGPIO_CB)(UINT32 value), UINT32 enable, LX_GPIO_INFO_T *info);
	int 		(*GetIntrValue)	(UINT32 *port, LX_GPIO_VALUE_T *value);
	int 		(*SetIntrArrayNum)	(UINT32 intrArrayNum);
	int 		(*GetIntrCntDur)	(UINT32 port, UINT32 count, UINT32 *us);

	/* To access gpio pins in LG115xAN(ACE) */
	OS_SEM_T	ex_lock;
	UINT32		max_ex_num;
	int 		(*ExSetPinMux)(UINT32 port, BOOLEAN enable);
	int 		(*ExGetPinMux)(UINT32 port, BOOLEAN *enable);
	int 		(*ExSetValue) (UINT32 port, LX_GPIO_VALUE_T value);
	int 		(*ExGetValue) (UINT32 port, LX_GPIO_VALUE_T *value);
	int 		(*ExSetMode)  (UINT32 port, LX_GPIO_MODE_T mode);
	int 		(*ExGetMode)  (UINT32 port, LX_GPIO_MODE_T *mode);

#ifdef KDRV_CONFIG_PM
	int			(*Resume)	(void);
	int			(*Suspend)	(void);
	int			(*BeforeSuspend)	(void);
	GPIO_PM_DATA_T*	pmdata;
#endif
} GPIO_DEV_T;


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

int GPIO_DevResume(void);
int GPIO_DevSuspend(void);
int GPIO_DevBeforeSuspend(void);
int GPIO_DevSetPinMux(UINT32 port, BOOLEAN enable);
int GPIO_DevGetPinMux(UINT32 port, BOOLEAN *enable);
int GPIO_DevSetValue(UINT32 port, LX_GPIO_VALUE_T value);
int GPIO_DevGetValue(UINT32 port, LX_GPIO_VALUE_T *value);
int GPIO_DevSetMode(UINT32 port, LX_GPIO_MODE_T mode);
int GPIO_DevGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
int GPIO_DevSetISR(UINT32 port, void (*pfnGPIO_CB)	(UINT32 ), UINT32 enable, LX_GPIO_INFO_T * info);
int GPIO_DevGetIntrValue(UINT32 *port, LX_GPIO_VALUE_T *value);
int GPIO_DevGetIntrCntDur(UINT32 port, UINT32 count, UINT32 *usec);
static int _GPIO_ExSetPinMux(UINT32 port, BOOLEAN enable);
static int _GPIO_ExGetPinMux(UINT32 port, BOOLEAN *enable);
int _GPIO_SetPinMux_O26Ax(UINT32 port, BOOLEAN enable);
static int _GPIO_GetPinMux_O26Ax(UINT32 port, BOOLEAN *enable);
int _GPIO_SetPinMux_O24Ax(UINT32 port, BOOLEAN enable);
static int _GPIO_GetPinMux_O24Ax(UINT32 port, BOOLEAN *enable);
int _GPIO_SetPinMux_O22Ax(UINT32 port, BOOLEAN enable);
static int _GPIO_GetPinMux_O22Ax(UINT32 port, BOOLEAN *enable);
int _GPIO_SetPinMux_M23Ax(UINT32 port, BOOLEAN enable);
static int _GPIO_GetPinMux_M23Ax(UINT32 port, BOOLEAN *enable);
int _GPIO_SetMode(UINT32 port, LX_GPIO_MODE_T mode);
int _GPIO_SetIntr(UINT32 port, UINT32 enable);
int _GPIO_GetMode(UINT32 port, LX_GPIO_MODE_T *mode);
int _GPIO_GetModeEx(UINT32 port);
int _GPIO_GetModeR(UINT32 port);
int _GPIO_SetIntrAction(UINT32 port, void (*pfnGPIO_CB)(UINT32 value), UINT32 enable, LX_GPIO_INFO_T * info);
int _GPIO_GetValue(UINT32 port, LX_GPIO_VALUE_T *value);
int _GPIO_GetValueEx(UINT32 port);
int _GPIO_GetValueR(UINT32 port);
int _GPIO_SetValue(UINT32 port, LX_GPIO_VALUE_T value);
int GPIO_DevSetPinMux(UINT32 port, BOOLEAN enable);
int GPIO_DevGetPinMux(UINT32 port, BOOLEAN *enable);
int GPIO_DevSetValue(UINT32 port, LX_GPIO_VALUE_T value);
int GPIO_DevSetIntrArrayNum(UINT32 intrArrayNum);
int GPIO_DevGetValue(UINT32 port, LX_GPIO_VALUE_T *value);
int GPIO_DevSetMode(UINT32 port, LX_GPIO_MODE_T mode);
int GPIO_DevGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
int GPIO_DevSetISR(UINT32 port, void (*pfnGPIO_CB)(UINT32 ), UINT32 enable, LX_GPIO_INFO_T * info);
int GPIO_DevGetIntrValue(UINT32 *port, LX_GPIO_VALUE_T *value);
int GPIO_DevGetIntrCntDur(UINT32 port, UINT32 count, UINT32 *usec);
int GPIO_DevExSetPinMux(UINT32 port, BOOLEAN enable);
int GPIO_DevExGetPinMux(UINT32 port, BOOLEAN *enable);
int GPIO_DevExSetValue(UINT32 port, LX_GPIO_VALUE_T value);
int GPIO_DevExGetValue(UINT32 port, LX_GPIO_VALUE_T *value);
int GPIO_DevExSetMode(UINT32 port, LX_GPIO_MODE_T mode);
int GPIO_DevExGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
int GPIO_DevInit(void);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

static GPIO_DEV_T *_pGpioDev;
void 			 **_gpioBaseAddr;
#ifdef INCLUDE_O26_CHIP_KDRV
int _GPIO_SetPinMux_O26Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_O26Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
int _GPIO_SetPinMux_O24Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_O24Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
int _GPIO_SetPinMux_M23Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_M23Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
int _GPIO_SetPinMux_O22Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_O22Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
int _GPIO_SetPinMux_E60Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_E60Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
int _GPIO_SetPinMux_O20Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_O20Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
int _GPIO_SetPinMux_M19Ax(UINT32 port, BOOLEAN enable)
{
	return 0;
}
static int _GPIO_GetPinMux_M19Ax(UINT32 port, BOOLEAN *enable)
{
	return 0;
}
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
int _GPIO_SetPinMux_O18Ax(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	// always return OK when GPIO_KERNEL_API used
	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	if(port <= 29)	/* 10 ~ 28 */ //default gpio enable
	{
		if(port <= 9)	/* 0 ~ 9*/
		{
			//0x10
			//#define O18_A0_CTOP_NDO_BASE				0xC7FE_0000

			value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
			mask = 1 << ((port - 0) + 12);
			if(enable)	value &= (~mask);
			else		value |= mask;
			CTOP_CTRL_O18A0_WRITE(CTOP_ND0,0x10,value);
			return 0;
		}
		else if(port <= 29)/* 10~ 29*/
		{
			//	ctr33
			//#define O18_A0_CTOP_CTOP_DPE_BASE    	0xC930_A400

			value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0x84);
			mask = 1 << ((port - 10) + 8);

			if(port == 14 || port == 15 )
			{
				mask |= (1 <<  4);
			}
			else if(port == 16)
			{
				mask |= (1 <<  1);
			}
			else if(port == 17)
			{
				mask |= (1 <<  0);
			}
			else if(port == 18 || port == 19 )
			{
				mask |= (3 <<  5);
			}
			else if(port == 21)
			{
				mask |= (1 <<  3);
			}
			else if(port == 22 || port == 23 )
			{
				mask |= (1 <<  2);
				mask |= (1 <<  28);
			}

			if(enable)	value &= (~mask);
			else		value |= mask;

			CTOP_CTRL_O18A0_WRITE(CTOP_DPE,0x84,value);

			return 0;
		}

	}
	else if(port <= 31)	/* 30 ~ 31 */
	{
		//0x0000
		//#define O18_A0_CTOP_CTOP_CCO_BASE    			0xC97d_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x00);
		mask = 1 << ((port - 30) + 17);
		if(enable)	value &= (~mask);
		else		value |= mask;

		CTOP_CTRL_O18A0_WRITE(CTOP_CCO,0x00,value);
		return 0;

	}
	else if(port <= 39)	/* 32 ~ 39 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE    			0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 32) + 8);
		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_O18A0_WRITE(BMC_SYN,0x94,value);
		return 0;

	}
	else if(port <= 44)	/* 40 ~ 44 */
	{
	}
	else if(port <= 47)	/* 45 ~ 47 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE    			0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 45) + 16);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(BMC_SYN,0x94,value);
		return 0;
	}
	else if(port <= 53) /* 48 ~ 53 */
	{
		//0x0004
		//#define O18_A0_CTRL_EDID_BASE    0xC68F0000
		value = CTOP_CTRL_O18A0_READ(CTRL_EDID,0x04);
		mask = 1 << ((port - 48) + 1);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTRL_EDID,0x04,value);
	}
	else if(port <= 55) /* 54 ~ 55 */
	{
	}
	else if(port <= 63)	/* 56 ~ 63 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_CCO_BASE    			0xC97D_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x00);
		mask = 1 << ((port - 56) + 8);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_CCO,0x00,value);
		return 0;

	}
	else if(port <= 67)	/* 64 ~ 67 */
	{
	}
	else if(port <= 68)	/* 68 ~ 68 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_CCO_BASE    			0xC97D_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x00);
		mask = 1 << ((port - 68) + 16);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_CCO,0x00,value);
		return 0;

	}
	else if(port <= 71)	/* 69 ~ 71 */
	{
	}
	else if(port <= 77)	/* 72 ~ 77 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE    			0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 72) + 19);

		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(BMC_SYN,0x94,value);
		return 0;
	}
	else if(port <= 79)	/* 78 ~ 79 */
	{
		//0x10
		//#define O18_A0_CTOP_CTOP_ND0_BASE    			0xC7fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << ((port - 78) + 10);
		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_O18A0_WRITE(CTOP_ND0,0x10,value);
		return 0;
	}
	else if(port <= 87)	/* 80 ~ 87 */
	{
			//0x0000
		//#define O18_A0_CTOP_CTOP_CCO_BASE    			0xC97d_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x0);
		mask = 1 << ((port - 80) + 0);
		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_O18A0_WRITE(CTOP_CCO,0x0,value);
		return 0;

	}
	else if(port <= 93)	/* 88 ~ 93 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_MEU_BASE    			0xC8fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_MEU,0x00);
		mask = 1 << ((port - 88) + 3);

		if(enable)	value &= (~mask);
		else		value |= mask;
		CTOP_CTRL_O18A0_WRITE(CTOP_MEU,0x00,value);
		return 0;
	}
	else if(port <= 95)	/* 94 ~ 95 */
	{
		//0x00a0
		//#define O18_A0_CTOP_BMC_SYN_BASE    			0xC8fe_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0xa0);
		mask = 1 << ((port - 94) + 0);

		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(BMC_SYN,0xa0,value);
		return 0;
	}
	else if(port <= 103)	/* 96 ~ 103 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE    			0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 96) + 0);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(BMC_SYN,0x94,value);
		return 0;
	}

	else if(port <= 104)	/* 104 ~ 104 */
	{
	}
	else if(port <= 106)	/* 105 ~ 106 */
	{

		//#define O18_A0_CTOP_CTOP_DPE_BASE		0xC930_A400

		value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0xc0);

		mask = 1 << ((port - 105) + 0);

		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_DPE,0xc0,value);
		return 0;

	}
	else if(port <= 108)	/* 107 ~ 108 */
	{

		//#define O18_A0_CTOP_CTOP_DPE_BASE		0xC930_A400

		value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0xc0);

		mask = 1 << ((port - 107) + 2);

		if(enable)	value &= (~mask);
		else		value |= mask;
		CTOP_CTRL_O18A0_WRITE(CTOP_DPE,0xc0,value);
		return 0;

	}
	else if(port <= 110)	/* 109 ~ 110 */
	{
		//0x10
		//#define O18_A0_CTOP_CTOP_ND0_BASE    			0xC7fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << ((port - 109) + 4);
		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_O18A0_WRITE(CTOP_ND0,0x10,value);
		return 0;

	}
	else if(port <= 111)	/* 111 ~ 111 */
	{

	}
	else if(port <= 129)	/* 112 ~ 127 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_MEU_BASE    			0xC8fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_MEU,0x00);
		mask = 1 << ((port - 112) + 9);

		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_MEU,0x00,value);
		return 0;

	}
	else if(port <= 135)	/* 130 ~ 135 */
	{
		//	0x4

		//#define O18_A0_CTOP_CTOP_ME1_BASE		0xC5ff0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ME1,0x4);

		mask = 1 << ((port - 130) + 0);

		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_ME1,0x4,value);
		return 0;

	}
	else if(port <= 139)	/* 136 ~ 139 */
	{
		//0x10
		//#define O18_A0_CTOP_CTOP_ND0_BASE    			0xC7fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << ((port - 136) + 6);
		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_O18A0_WRITE(CTOP_ND0,0x10,value);
		return 0;
	}
	return rc;
}

static int _GPIO_GetPinMux_O18Ax(UINT32 port, BOOLEAN *enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	// not used function. always return OK when GPIO_KERNEL_API used
	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	if(port <= 29)	/* 10 ~ 28 */ //default gpio enable
	{
		if(port <= 9)	/* 0 ~ 9*/
		{
			//0x10
			//#define O18_A0_CTOP_NDO_BASE				0xC7FE_0000

			value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
			mask = 1 << ((port - 0) + 12);
			*enable = ((value & mask) == mask) ? 0 : 1;
			return 0;
		}
		else if(port <= 29)/* 10~ 29*/
		{
			//	ctr33
			//#define O18_A0_CTOP_CTOP_DPE_BASE		0xC930_A400

			value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0x84);
			mask = 1 << ((port - 10) + 8);

			if(port == 14 || port == 15 )
			{
				mask |= (1 <<  4);
			}
			else if(port == 16)
			{
				mask |= (1 <<  1);
			}
			else if(port == 17)
			{
				mask |= (1 <<  0);
			}
			else if(port == 18 || port == 19 )
			{
				mask |= (3 <<  5);
			}
			else if(port == 21)
			{
				mask |= (1 <<  3);
			}
			else if(port == 22 || port == 23 )
			{
				mask |= (1 <<  2);
				mask |= (1 <<  28);
			}

			*enable = ((value & mask) == mask) ? 0 : 1;
			return 0;
		}

	}
	else if(port <= 31) /* 30 ~ 31 */
	{
		//0x0000
		//#define O18_A0_CTOP_CTOP_CCO_BASE				0xC97d_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x00);
		mask = 1 << ((port - 30) + 17);
		*enable = ((value & mask) == mask) ? 0 : 1;
		return 0;


	}
	else if(port <= 39) /* 32 ~ 39 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE				0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 32) + 8);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 44) /* 40 ~ 44 */
	{
	}
	else if(port <= 47) /* 45 ~ 47 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE				0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 45) + 16);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;

	}
	else if(port <= 53) /* 48 ~ 53 */
	{
		//0x0004
		//#define O18_A0_CTRL_EDID_BASE    0xC68F0000
		value = CTOP_CTRL_O18A0_READ(CTRL_EDID,0x04);
		mask = 1 << ((port - 48) + 1);
		*enable = ((value & mask) == mask) ? 1 : 0;
		CTOP_CTRL_O18A0_WRITE(CTRL_EDID,0x04,value);
	}
	else if(port <= 55) /* 54 ~ 55 */
	{
	}
	else if(port <= 63) /* 56 ~ 63 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_CCO_BASE				0xC97D_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x00);
		mask = 1 << ((port - 56) + 8);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 67) /* 64 ~ 67 */
	{
	}
	else if(port <= 68) /* 68 ~ 68 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_CCO_BASE				0xC97D_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x00);
		mask = 1 << ((port - 68) + 16);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 71) /* 69 ~ 71 */
	{
	}
	else if(port <= 77) /* 72 ~ 77 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE				0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 72) + 19);

		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;

	}
	else if(port <= 79) /* 78 ~ 79 */
	{
		//0x10
		//#define O18_A0_CTOP_CTOP_ND0_BASE				0xC7fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << ((port - 78) + 10);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;

	}
	else if(port <= 87) /* 80 ~ 87 */
	{
			//0x0000
		//#define O18_A0_CTOP_CTOP_CCO_BASE				0xC97d_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_CCO,0x0);
		mask = 1 << ((port - 80) + 0);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 93) /* 88 ~ 93 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_MEU_BASE				0xC8fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_MEU,0x00);
		mask = 1 << ((port - 88) + 3);

		*enable = ((value & mask) == mask) ? 0 : 1;
		return 0;

	}
	else if(port <= 95) /* 94 ~ 95 */
	{
		//0x00a0
		//#define O18_A0_CTOP_BMC_SYN_BASE				0xC8fe_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0xa0);
		mask = 1 << ((port - 94) + 0);

		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;

	}
	else if(port <= 103)	/* 96 ~ 103 */
	{
		//0x0094
		//#define O18_A0_CTOP_BMC_SYN_BASE				0xC7FC_0000

		value = CTOP_CTRL_O18A0_READ(BMC_SYN,0x94);
		mask = 1 << ((port - 96) + 0);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;

	}

	else if(port <= 104)	/* 104 ~ 104 */
	{
	}

	else if(port <= 106)	/* 105 ~ 106 */
	{

		//#define O18_A0_CTOP_CTOP_DPE_BASE		0xC930_A400

		value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0xc0);

		mask = 1 << ((port - 105) + 0);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 108)	/* 107 ~ 108 */
	{

		//#define O18_A0_CTOP_CTOP_DPE_BASE		0xC930_A400

		value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0xc0);

		mask = 1 << ((port - 107) + 2);

		*enable = ((value & mask) == mask) ? 0 : 1;
		return 0;


	}
	else if(port <= 110)	/* 109 ~ 110 */
	{
		//0x10
		//#define O18_A0_CTOP_CTOP_ND0_BASE				0xC7fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << ((port - 109) + 4);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 111)	/* 111 ~ 111 */
	{

	}
	else if(port <= 129)	/* 112 ~ 127 */
	{
		//0x0
		//#define O18_A0_CTOP_CTOP_MEU_BASE				0xC8fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_MEU,0x00);
		mask = 1 << ((port - 112) + 9);

		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 135)	/* 130 ~ 135 */
	{
		//	0x4

		//#define O18_A0_CTOP_CTOP_ME1_BASE		0xC5ff0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ME1,0x4);

		mask = 1 << ((port - 130) + 0);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;


	}
	else if(port <= 139)	/* 136 ~ 139 */
	{
		//0x10
		//#define O18_A0_CTOP_CTOP_ND0_BASE				0xC7fe_0000

		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << ((port - 136) + 6);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;
	}
	return rc;
}

#endif //INCLUDE_O18_CHIP_KDRV

/*
BMC_SYN_REG_L18F_A0 	   * BMC;
CPU_SYN_REG_L18F_A0 	   * CPU;
EDID_SYN_REG_L18F_A0	   * EDID;
MICOM_SYN_REG_L18F_A0	   * MICOM;
PQE_SYN_REG_L18F_A0 	   * PQE;
VDEC_SYN_REG_L18F_A0	   * VDEC;

SYN_CODEC_SYN_REG_L18F_A0  * CODEC_SYN;
SYN_CPU_SYN_REG_L18F_A0    * CPU_SYN;
SYN_DPE_CRC_REG_L18F_A0    * DPE_CRC;
SYN_M0_SYN_REG_L18F_A0	   * M0_SYN;
SYN_MIP_SYN_REG_L18F_A0    * MIP_SYN;
SYN_PQE_SYN_REG_L18F_A0    * PQE_SYN;
SYN_VDEC0_SYN_REG_L18F_A0  * VDEC0_SYN;
*/

//#define L18_A0_CTOP_BMC_BASE    0xC930E400
//#define L18_A0_CTOP_CPU_BASE    0xC9230400
//#define L18_A0_CTOP_EDID_BASE   0xC9303000
//#define L18_A0_CTOP_MICOM_BASE  0xC930C400
//#define L18_A0_CTOP_PQE_BASE    0xC9300100
//#define L18_A0_CTOP_VDEC_BASE   0xC9C70400
//#define L18_A0_CTOP_CODEC_SYN_BASE   0xC9C50000
//#define L18_A0_CTOP_CPU_SYN_BASE     0xC9230000
//#define L18_A0_CTOP_DPE_CRC_BASE     0xC930AC00
//#define L18_A0_CTOP_M0_SYN_BASE      0xC9908000
//#define L18_A0_CTOP_MIP_SYN_BASE     0xC930E000
//#define L18_A0_CTOP_PQE_SYN_BASE     0xC9300000
//#define L18_A0_CTOP_VDEC0_SYN_BASE   0xC9C70000

#ifdef INCLUDE_L18_CHIP_KDRV


int _GPIO_SetPinMux_L18Ax(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	if(port <= 37)	/* 0 ~ 31 */ //default gpio enable
	{
		if(port <= 21)	/* 0 ~ 21*/
		{
			return 0;
			// Do nothing...
		}
		else if(port <= 37)/* 22~ 37*/
		{
			//0x009C	SYN_BMC39
			//#define L18_A0_CTOP_BMC_BASE    0xC930E400

			value = CTOP_CTRL_L18A0_READ(BMC,0x9c);
			if(port <= 23)/* 22~ 23*/
			{
				mask = 1 << ((port - 22) + 6);
			}
			else if(port <= 24)/* 24~ 24*/
			{

			}
			else if(port <= 31)/* 25~ 37*/
			{
				mask = 1 << ((port - 22) + 6);
			}

			if(enable)	value |= mask;
			else		value &= (~mask);

			CTOP_CTRL_L18A0_WRITE(BMC,0x9c,value);
			return 0;
		}

	}
	else if(port <= 45)	/* 38 ~ 45 */
	{
		//0x0008	SYN_EDID02
		//#define L18_A0_CTOP_EDID_BASE   0xC9303000

		value = CTOP_CTRL_L18A0_READ(EDID,0x8);
		mask = 1 << ((port - 38) + 6);

		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_L18A0_WRITE(EDID,0x8,value);
		return 0;
	}
	else if(port <= 71)	/* 46 ~ 71 */
	{
		//0x0x0038	SYN_PQE14
		//#define L18_A0_CTOP_PQE_BASE    0xC9300100

		value = CTOP_CTRL_L18A0_READ(PQE,0x38);

		if(port <= 47)/* 46~ 47*/
		{
			mask = 1 << ((port - 46) + 30);
		}
		else if(port <= 55)/* 48~ 55*/
		{
			mask = 1 << ((port - 48) + 16);
		}
		else if(port <= 63)/* 56~ 63*/
		{
			mask = 1 << ((port - 56) + 8);
		}
		else if(port <= 71)/* 64~ 71*/
		{
			mask = 1 << ((port - 64) + 0);
		}

		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_L18A0_WRITE(PQE,0x38,value);
		return 0;
	}
	else if(port <= 103)	/* 72 ~ 103 */
	{
		//0x003C	SYN_PQE15

		//#define L18_A0_CTOP_PQE_BASE    0xC9300100

		value = CTOP_CTRL_L18A0_READ(PQE,0x3C);

		if(port <= 79)/* 72~ 79*/
		{
			mask = 1 << ((port - 72) + 24);
		}
		else if(port <= 87)/* 80~ 87*/
		{
			mask = 1 << ((port - 80) + 16);
		}
		else if(port <= 95)/* 88~ 95*/
		{
			mask = 1 << ((port - 88) + 8);
		}
		else if(port <= 103)/* 96~ 103*/
		{
			mask = 1 << ((port - 96) + 0);
		}

		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_L18A0_WRITE(PQE,0x3C,value);
		return 0;
	}
	else if(port <= 124)	/* 104 ~ 124 */
	{
		//0x0040	SYN_PQE16
		//#define L18_A0_CTOP_PQE_BASE    0xC9300100

		value = CTOP_CTRL_L18A0_READ(PQE,0x40);

		if(port <= 111)/* 104~ 111*/
		{
			mask = 1 << ((port - 104) + 24);
		}
		else if(port <= 119)/* 112~ 119*/
		{
			mask = 1 << ((port - 80) + 16);
		}
		else if(port <= 124)/* 120~ 124*/
		{
			mask = 1 << ((port - 120) + 8);
		}

		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_L18A0_WRITE(PQE,0x40,value);
		return 0;
	}
	else if(port <= 141)	/* 125 ~ 142*/
	{
		//0x0004	SYN_VDEC01
		//#define L18_A0_CTOP_VDEC_BASE   0xC9C70400

		value = CTOP_CTRL_L18A0_READ(VDEC,0x4);

		if(port <= 127)/* 125~ 127*/
		{
			mask = 1 << ((port - 125) + 13);
		}
		else if(port <= 135)/* 128 135*/
		{
			mask = 1 << ((port - 128) + 16);
		}
		else if(port <= 141)/* 136~ 141*/
		{
			mask = 1 << ((port - 136) + 24);
		}

		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_L18A0_WRITE(VDEC,0x4,value);
		return 0;
	}
	else if(port <= 142)	/* 142 ~ 142*/
	{
		//0x009C	SYN_BMC39
		//#define L18_A0_CTOP_BMC_BASE	  0xC930E400

		value = CTOP_CTRL_L18A0_READ(BMC,0x9c);
		mask = 1 << ((port - 142) + 22);

		if(enable)	value |= mask;
		else		value &= (~mask);

		CTOP_CTRL_L18A0_WRITE(BMC,0x9c,value);
		return 0;
	}


	return rc;
}


static int _GPIO_GetPinMux_L18Ax(UINT32 port, BOOLEAN *enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	if(port <= 37)	/* 0 ~ 31 */ //default gpio enable
	{
		if(port <= 21)	/* 0 ~ 21*/
		{
			return 0;
			// Do nothing...
		}
		else if(port <= 37)/* 22~ 37*/
		{
			//0x009C	SYN_BMC39
			//#define L18_A0_CTOP_BMC_BASE    0xC930E400

			value = CTOP_CTRL_L18A0_READ(BMC,0x9c);
			if(port <= 23)/* 22~ 23*/
			{
				mask = 1 << ((port - 22) + 6);
			}
			else if(port <= 24)/* 24~ 24*/
			{

			}
			else if(port <= 31)/* 25~ 37*/
			{
				mask = 1 << ((port - 22) + 6);
			}
			*enable = ((value & mask) == mask) ? 1 : 0;
			return 0;
		}

	}
	else if(port <= 45)	/* 38 ~ 45 */
	{
		//0x0008	SYN_EDID02
		//#define L18_A0_CTOP_EDID_BASE   0xC9303000

		value = CTOP_CTRL_L18A0_READ(EDID,0x8);
		mask = 1 << ((port - 38) + 6);
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 71)	/* 46 ~ 71 */
	{
		//0x0x0038	SYN_PQE14
		//#define L18_A0_CTOP_PQE_BASE    0xC9300100

		value = CTOP_CTRL_L18A0_READ(PQE,0x38);

		if(port <= 47)/* 46~ 47*/
		{
			mask = 1 << ((port - 46) + 30);
		}
		else if(port <= 55)/* 48~ 55*/
		{
			mask = 1 << ((port - 48) + 16);
		}
		else if(port <= 63)/* 56~ 63*/
		{
			mask = 1 << ((port - 56) + 8);
		}
		else if(port <= 71)/* 64~ 71*/
		{
			mask = 1 << ((port - 64) + 0);
		}
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 103)	/* 72 ~ 103 */
	{
		//0x003C	SYN_PQE15

		//#define L18_A0_CTOP_PQE_BASE    0xC9300100

		value = CTOP_CTRL_L18A0_READ(PQE,0x3C);

		if(port <= 79)/* 72~ 79*/
		{
			mask = 1 << ((port - 72) + 24);
		}
		else if(port <= 87)/* 80~ 87*/
		{
			mask = 1 << ((port - 80) + 16);
		}
		else if(port <= 95)/* 88~ 95*/
		{
			mask = 1 << ((port - 88) + 8);
		}
		else if(port <= 103)/* 96~ 103*/
		{
			mask = 1 << ((port - 96) + 0);
		}
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 124)	/* 104 ~ 124 */
	{
		//0x0040	SYN_PQE16
		//#define L18_A0_CTOP_PQE_BASE    0xC9300100

		value = CTOP_CTRL_L18A0_READ(PQE,0x40);

		if(port <= 111)/* 104~ 111*/
		{
			mask = 1 << ((port - 104) + 24);
		}
		else if(port <= 119)/* 112~ 119*/
		{
			mask = 1 << ((port - 80) + 16);
		}
		else if(port <= 124)/* 120~ 124*/
		{
			mask = 1 << ((port - 120) + 8);
		}
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 141)	/* 125 ~ 142*/
	{
		//0x0004	SYN_VDEC01
		//#define L18_A0_CTOP_VDEC_BASE   0xC9C70400

		value = CTOP_CTRL_L18A0_READ(VDEC,0x4);

		if(port <= 127)/* 125~ 127*/
		{
			mask = 1 << ((port - 125) + 13);
		}
		else if(port <= 135)/* 128 135*/
		{
			mask = 1 << ((port - 128) + 16);
		}
		else if(port <= 141)/* 136~ 141*/
		{
			mask = 1 << ((port - 136) + 24);
		}
		*enable = ((value & mask) == mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 142)	/* 142 ~ 142*/
	{
		//0x009C	SYN_BMC39
		//#define L18_A0_CTOP_BMC_BASE	  0xC930E400

		value = CTOP_CTRL_L18A0_READ(BMC,0x9c);
		mask = 1 << ((port - 142) + 22);
		*enable = ((value & mask) == mask) ? 1 : 0;

		return 0;
	}
	return rc;
}



#endif //INCLUDE_L18_CHIP_KDRV

#ifdef INCLUDE_M17_CHIP_KDRV

//#define M16PP_A0_CTOP_DPE_BASE			0xC930A400		//0xC930_A400
//#define M16PP_A0_CTOP_FMC_BASE			0xC9309400		//0xC930_9400
//#define M16PP_A0_CTOP_FME0_BASE		0xC9308800		//0xC930_8800
//#define M16PP_A0_CTOP_FMS_BASE			0xC930C400		//0xC930_C400
//#define M16PP_A0_CTOP_GFX_BASE			0xC9C10400		//0xC9C1_0400
//#define M16PP_A0_CTOP_SR_BASE			0xC9305400		//0xC930_5400
//#define M16PP_A0_CTOP_AUD_SYN_BASE		0xC9C60000		//0xC9C6_0000
//#define M16PP_A0_CTOP_CCO_SYN_BASE		0xC9307000		//0xC930_7000
//#define M16PP_A0_CTOP_CVI_SYN_BASE		0xC9302000		//0xC930_2000
//#define M16PP_A0_CTOP_DPE_CRC_BASE		0xC930AC00		//0xC930_AC00
//#define M16PP_A0_CTOP_DPE_SYN_BASE		0xC930A000		//0xC930_A000
//#define M16PP_A0_CTOP_EMMC_SYN_BASE	0xC3680000		//0xC368_0000
//#define M16PP_A0_CTOP_FMC_SYN_BASE		0xC9309000		//0xC930_9000
//#define M16PP_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
//#define M16PP_A0_CTOP_FME1_SYN_BASE	0xC930B000		//0xC930_B000
//#define M16PP_A0_CTOP_FMS_SYN_BASE		0xC930C000		//0xC930_C000
//#define M16PP_A0_CTOP_GBUS_SYN_BASE	0xC9301000		//0xC930_1000
//#define M16PP_A0_CTOP_GEM_SYN_BASE		0xC3501000		//0xC350_1000
//#define M16PP_A0_CTOP_GFX_SYN_BASE		0xC9C10000		//0xC9C1_0000
//#define M16PP_A0_CTOP_GPU_SYN_BASE		0xC9205000		//0xC920_5000
//#define M16PP_A0_CTOP_IMX_SYN_BASE		0xC9303000		//0xC930_3000
//#define M16PP_A0_CTOP_LBM_SYN_BASE		0xC9300000		//0xC930_0000
//#define M16PP_A0_CTOP_M0_SYN_BASE		0xC9C30000		//0xC9C3_0000
//#define M16PP_A0_CTOP_M1_SYN_BASE		0xC9C40000		//0xC9C4_0000
//#define M16PP_A0_CTOP_MIP_SYN_BASE		0xC930E000		//0xC930_E000
//#define M16PP_A0_CTOP_ND0_SYN_BASE		0xC9304000		//0xC930_4000
//#define M16PP_A0_CTOP_PERI_SYN_BASE	0xC9230000		//0xC923_0000
//#define M16PP_A0_CTOP_SRE_SYN_BASE		0xC9305000		//0xC930_5000
//#define M16PP_A0_CTOP_TIV_SYN_BASE		0xC9C50000		//0xC9C5_0000
//#define M16PP_A0_CTOP_VDEC0_SYN_BASE	0xC9C701C0		//0xC9C7_01C0
//#define M16PP_A0_CTOP_VDEC1_SYN_BASE	0xC9C711C0		//0xC9C7_11C0
//#define M16PP_A0_CTOP_VSD_CRC_BASE		0xC9306800		//0xC930_6800
//#define M16PP_A0_CTOP_VSD_SYN_BASE		0xC9306000		//0xC930_6000

int _GPIO_SetPinMux_M17Cx(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	// not used function. always return OK when GPIO_KERNEL_API used
	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	if(port <= 31)	/* 0 ~ 31 */ //default gpio enable
	{
		if(port <= 15)	/* 0 ~ 15*/
		{
			return 0;
			// Do nothing...
		}
		else if(port <= 23)/* 16~ 23*/
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);

			mask = mask | (1 << 20);
			mask = mask | (1 << 21);
			mask = mask | (1 << 22);
			mask = mask | (1 << 23);
			mask = mask | (1 << 24);

			if(port <= 16)/* 16~ 16*/
			{
				mask = mask | (1 << 13);
				mask = mask | (1 << 26);
			}
			else if(port <= 17)/* 17~ 17*/
			{
				mask = mask | (1 << 26);
			}
			else if(port <= 19)/* 18~ 19*/
			{
				mask = mask | (1 << 8);
				mask = mask | (1 << 11);
				if(enable)	value &= (~mask);
				CTOP_CTRL_M17A0_WRITE(FMC,0x1c,value);

				//M16PP_A0_CTOP_FMS_BASE 0xC930C400
				//CTOP_FMS_R12 0xC930C430
				mask = 0;
				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FMS,0x30);
				if(enable)	value &= (~mask);
				/* ignore non gpio case */
				CTOP_CTRL_M17A0_WRITE(FMS,0x30,value);
				return 0;
			}
			else if(port <= 20)/* 20~ 20*/
			{
			}
			else if(port <= 21)/* 21~ 21*/
			{
				mask = mask | (1 << 12);
				mask = mask | (1 << 25);
			}
			else if(port <= 23)/* 23~ 23*/
			{
			}

			if(enable)	value &= (~mask);
			/* is pinmuxed with multi function, ignore nongpio(else) case*/
			CTOP_CTRL_M17A0_WRITE(FMC,0x1c,value);
			return 0;
		}
		else if(port <= 29)/* 24 ~ 29*/
		{
				//M16PP_A0_CTOP_FME0_BASE		0xC9308800
				//CTOP_FME0_R16 0xC9308840

				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FME0,0x40);
				if(enable)	value &= (~mask);
				else		value |= mask;
				CTOP_CTRL_M17A0_WRITE(FME0,0x40,value);
			return 0;
			// Do nothing...
		}
		else if(port <= 30)/* 1 ~ 17*/
		{
			return 0;
			// Do nothing...
		}

		return 0;
		// Do nothing...
	}
	else if(port <= 39) /* 32 ~ 39 */
	{

		//M16PP_A0_CTOP_SR_BASE 0xC9305400
		//0xC9305410  CTOP_SR_R04
		mask = 1 << ((port - 32) + 24);
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(SR,0x10,value);
		return 0;
	}
	else if(port <= 43) /* 40 ~ 43 */ //need to check : gp5_0~3
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 53) /* 44 ~ 53 */
	{
		//M16PP_A0_CTOP_FMS_BASE	0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		if( port <= 47) /* 44 ~ 47 */
		{
			mask = 1 << ((port - 44)+ 28);
		}
		else if( port <= 53)  /* 48 ~ 53 */
		{
			mask = 1 << ((port - 48)+ 13);
		}

		value = CTOP_CTRL_M17A0_READ(FMS,0x2c);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FMS,0x2c,value);
		return 0;
	}
	else if(port <= 55) /* 54 ~ 55 */ //need to check : gp6_6~7
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 71) /* 56 ~ 71 */
	{
		//M16PP_A0_CTOP_FMC_BASE	0xC9309400
		//0xC9309418 FMC CTOP_FMC_R06

		if( port <= 63) /* 56 ~ 63 */
		{
			mask = 1 << ((port - 56)+ 24);
		}
		else if ( port <= 64)	/* 64 ~ 64 */
		{
			mask = 1 << ((port - 64)+ 23);
		}
		else if ( port <= 68)	/* 65 ~ 68 */
		{
			return 0;  // Do nothing...
		}
		else if( port <= 71)  /* 69 ~ 71 */
		{
			mask = 1 << ((port - 68)+ 16);
		}
		value = CTOP_CTRL_M17A0_READ(FMC,0x18);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FMC,0x18,value);
		return 0;
	}
	else if(port <= 79) /* 72 ~ 79 */
	{
		//M16PP_A0_CTOP_SR_BASE 0xC9305400
		//0xC9305410  CTOP_SR_R04

		if( port <= 73) /* 72 ~ 73 */
		{
			mask = 1 << ((port - 72)+ 15);
		}
		else if( port <= 74)  /* 74 ~ 74 */
		{
			mask = 1 << (7);
		}
		else if( port <= 75)  /* 75 ~ 75 */
		{
			mask = 1 << (11);
		}
		else if( port <= 77)  /* 76~ 77 */
		{
			mask = 1 << ((port - 76)+ 17);
		}
		else if( port <= 78)  /* 78 78 */
		{
			mask = 1 << (8);
		}
		else if( port <= 79)  /* 79 79 */
		{
			mask = 1 << (12);
		}
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(SR,0x10,value);
		return 0;
	}
	else if(port <= 87) /* 80 ~ 87 */
	{
		if( port <= 80) /* 80 ~ 80 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			mask = 1 << (19);
			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			if(enable)	value |= mask;
			else		value &= (~mask);
			CTOP_CTRL_M17A0_WRITE(FMC,0x18,value);
			return 0;
		}
		else if (port <= 84)	/* 81 ~ 84 */
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			mask = 1 << ((81 - port) + 30);
			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);
			if(enable)	value |= mask;
			else		value &= (~mask);
			CTOP_CTRL_M17A0_WRITE(FMC,0x1c,value);
			return 0;
		}
		else if(port <= 87) /* 85 ~ 87 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			mask = 1 << ((port - 85)+ 20);

			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			if(enable)	value |= mask;
			else		value &= (~mask);
			CTOP_CTRL_M17A0_WRITE(FMC,0x18,value);
			return 0;
		}
	}
	else if(port <= 93)  /* 88 ~ 93*/
	{
		//M16PP_A0_CTOP_FME0_BASE	0xC9308800
		//0xC9308830 AUD CTOP_FME0_R12
		mask = 1 << ((port - 88)+ 24);

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);

		if(port == 89)
		{
			if(enable)	value |= mask;
			else		value &= (~mask);
		}
		else
		{
			if(enable)	value &= (~mask);
			else		value |= mask;
		}
		CTOP_CTRL_M17A0_WRITE(FME0,0x30,value);
		return 0;
	}
	else if(port <= 95) /* 94 ~ 95 */ //need to check : gp11_6, gp11_7
	{
		//0xC9308030 AUD CTOP_FME0_R12
		mask = 1 << ((port - 94)+ 30);
		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FME0,0x30,value);
		return 0;
		// Do nothing...
	}
	else if( port <= 103)  /* 96 ~ 103 */
	{
		//M16PP_A0_CTOP_FMS_BASE 0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		mask = 1 << ((port - 96)+ 20); //gone

		value = CTOP_CTRL_M17A0_READ(FMC,0x2c);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FMC,0x2c,value);
		return 0;
	}
	else if(port <= 104)	/* 104 ~ 104 */ //need to check : gp13_0
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 110)	/* 105 ~ 110 */
	{
		// M16PP_A0_CTOP_DPE_SYN_BASE	0xC930A000
		//0xC930A080 DPE CTOP_DPE_R32
		mask = 1 << ((port - 105) + 26);

		value = CTOP_CTRL_M17A0_READ(DPE,0x80);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(DPE,0x80,value);
		return 0;
	}
	else if(port <= 111)	/* 111 ~ 111 */
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 135)	/* 112 ~ 135 */
	{
		//M16PP_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
		//0xC9308030 AUD CTOP_FME0_R12

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{
			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 129)  /* 128 ~ 129 */
			{
				/* bit field is disappeared in M16+ B0 */
				return 0;
			}
			else if( port <= 135)  /* 130 ~ 135 */
			{
				mask = 1 << ((port - 130) + 2);
			}
		}
		else if(lx_chip_rev() >= LX_CHIP_REV(M16P, A0))
		{

			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 135)  /* 128 ~ 135 */
			{
				mask = 1 << ((port - 128) + 0);
			}
		}

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FME0,0x30,value);

		return 0;
	}
	else if(port <= 143)	/* 136 ~ 143 */
	{
		//M16PP_A0_CTOP_SR_BASE 0xC9305400
		//0xC9305410  CTOP_SR_R04

		if(port <= 136) /* 136 ~ 136 */
		{
			mask = 1 << (9);
		}
		else if(port <= 137)	/* 137 ~ 137 */
		{
			mask = 1 << (13);
		}
		else if(port <= 138)	/* 138 ~ 138 */
		{
			mask = 1 << (10);
		}
		else if(port <= 139)	/* 139 ~ 139 */
		{
			mask = 1 << (14);
		}
#if 0 //need to check
		else if( port <= 140)  /* 140 ~ 140 */
		{
			mask = 1 << ((port - 140)+ 19);
		}
		else if( port <= 143)  /* 141 ~ 143 */
		{
			mask = 1 << ((port - 141)+ 21);
		}
#endif
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(SR,0x10,value);
		return 0;
	}
	return rc;
}

static int _GPIO_GetPinMux_M17Cx(UINT32 port, BOOLEAN *enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	// not used function. always return OK when GPIO_KERNEL_API used
	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	if(port <= 31)	/* 0 ~ 31 */ //default gpio enable
	{
		if(port <= 15)	/* 0 ~ 15*/
		{
			return 0;
			// Do nothing...
		}
		else if(port <= 23)/* 16~ 23*/
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);

			mask = mask | (1 << 20);
			mask = mask | (1 << 21);
			mask = mask | (1 << 22);
			mask = mask | (1 << 23);
			mask = mask | (1 << 24);

			if(port <= 16)/* 16~ 16*/
			{
				mask = mask | (1 << 13);
				mask = mask | (1 << 26);
			}
			else if(port <= 17)/* 17~ 17*/
			{
				mask = mask | (1 << 26);
			}
			else if(port <= 19)/* 18~ 19*/
			{
				mask = mask | (1 << 8);
				mask = mask | (1 << 11);

				if( (value & mask) != mask)
				{
					*enable = 0;
					return 0;
				}

				//M16PP_A0_CTOP_FMS_BASE 0xC930C400
				//CTOP_FMS_R12 0xC930C430
				mask = 0;
				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FMS,0x30);
				*enable = ((value & mask) == mask) ? 1 : 0;
				return 0;
			}
			else if(port <= 20)/* 20~ 20*/
			{
			}
			else if(port <= 21)/* 21~ 21*/
			{
				mask = mask | (1 << 12);
				mask = mask | (1 << 25);
			}
			else if(port <= 23)/* 23~ 23*/
			{
			}

			*enable = ((value & mask) == mask) ? 1 : 0;
			return 0;
		}
		else if(port <= 29)/* 24 ~ 29*/ //default gpio enable
		{
				//M16PP_A0_CTOP_FME0_SYN_BASE	0xC9308000
				//CTOP_FME0_R16 0xC9308040

				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FME0,0x40);
				*enable = (value & mask) ? 0 : 1;
			return 0;
			// Do nothing...
		}
		else if(port <= 30)/* 1 ~ 17*/ //default gpio enable
		{
			return 0;
			// Do nothing...
		}

		return 0;
		// Do nothing...
	}
	else if(port <= 39) /* 32 ~ 39 */
	{

		//M16PP_A0_CTOP_SR_BASE 0xC9305400
		//0xC9305410  CTOP_SR_R04
		mask = 1 << ((port - 32) + 24);
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 43) /* 40 ~ 43 */ //need to check : gp5_0~3
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 53) /* 44 ~ 53 */
	{
		//M16PP_A0_CTOP_FMS_BASE	0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		if( port <= 47) /* 44 ~ 47 */
		{
			mask = 1 << ((port - 44)+ 28);
		}
		else if( port <= 53)  /* 48 ~ 53 */
		{
			mask = 1 << ((port - 48)+ 13);
		}

		value = CTOP_CTRL_M17A0_READ(FMS,0x2c);
		*enable = (value & mask) ? 1 : 0;

		return 0;
	}
	else if(port <= 55) /* 54 ~ 55 */ //need to check : gp6_6~7
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 71) /* 56 ~ 71 */
	{
		//M16PP_A0_CTOP_FMC_BASE	0xC9309400
		//0xC9309418 FMC CTOP_FMC_R06


		if( port <= 63) /* 56 ~ 63 */
		{
			mask = 1 << ((port - 56)+ 24);
		}
		else if ( port <= 64)	/* 64 ~ 64 */
		{
			mask = 1 << ((port - 64)+ 23);
		}
		else if ( port <= 68)	/* 65 ~ 68 */
		{
			return 0;  // Do nothing...
		}
		else if( port <= 71)  /* 69 ~ 71 */
		{
			mask = 1 << ((port - 68)+ 16);
		}
		value = CTOP_CTRL_M17A0_READ(FMC,0x18);
		*enable = (value & mask) ? 1 : 0;

		return 0;
	}
	else if(port <= 79) /* 72 ~ 79 */
	{
		//M16PP_A0_CTOP_SR_BASE 0xC9305400
		//0xC9305410  CTOP_SR_R04

		if( port <= 73) /* 72 ~ 73 */
		{
			mask = 1 << ((port - 72)+ 15);
		}
		else if( port <= 74)  /* 74 ~ 74 */
		{
			mask = 1 << (7);
		}
		else if( port <= 75)  /* 75 ~ 75 */
		{
			mask = 1 << (11);
		}
		else if( port <= 77)  /* 76~ 77 */
		{
			mask = 1 << ((port - 76)+ 17);
		}
		else if( port <= 78)  /* 78 78 */
		{
			mask = 1 << (8);
		}
		else if( port <= 79)  /* 79 79 */
		{
			mask = 1 << (12);
		}
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 87) /* 80 ~ 87 */
	{
		if( port <= 80) /* 80 ~ 80 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			mask = 1 << (19);
			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			*enable = (value & mask) ? 1 : 0;
			return 0;
		}
		else if (port <= 84)	/* 81 ~ 84 */
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			mask = 1 << ((81 - port) + 30);
			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);
			*enable = (value & mask) ? 1 : 0;
			return 0;
		}
		else if(port <= 87) /* 85 ~ 87 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M16PP_A0_CTOP_FMC_SYN_BASE	0xC9309000

			mask = 1 << ((port - 85)+ 20);

			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			*enable = (value & mask) ? 1 : 0;
			return 0;
		}
	}
	else if(port <= 93)  /* 88 ~ 93*/
	{
		//M16PP_A0_CTOP_FME0_BASE	0xC9308800
		//0xC9308830 AUD CTOP_FME0_R12
		mask = 1 << ((port - 88)+ 24);

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);

		if(port == 89)
		{
			*enable = (value & mask) ? 1 : 0;
		}
		else
		{
			*enable = (value & mask) ? 0 : 1;
		}
		return 0;
	}
	else if(port <= 95) /* 94 ~ 95 */ //need to check : gp11_6, gp11_7
	{
		//0xC9308830 AUD CTOP_FME0_R12
		mask = 1 << ((port - 94)+ 30);
		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		*enable = (value & mask) ? 1 : 0;
		return 0;
		// Do nothing...
	}
	else if( port <= 103)  /* 96 ~ 103 */
	{
		//M16PP_A0_CTOP_FMS_BASE 0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		mask = 1 << ((port - 96)+ 20); //gone

		value = CTOP_CTRL_M17A0_READ(FMC,0x2c);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 104)	/* 104 ~ 104 */ //need to check : gp13_0
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 110)	/* 105 ~ 110 */
	{
		// M16PP_A0_CTOP_DPE_SYN_BASE	0xC930A000
		//0xC930A080 DPE CTOP_DPE_R32
		mask = 1 << ((port - 105) + 26);

		value = CTOP_CTRL_M17A0_READ(DPE,0x80);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 111)	/* 111 ~ 111 */
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 135)	/* 112 ~ 135 */
	{
		//M16PP_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
		//0xC9308030 AUD CTOP_FME0_R12

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{

			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 129)  /* 128 ~ 129 */
			{
				/* bit field is disappeared in M16+ B0 */
				return 0;
			}
			else if( port <= 135)  /* 130 ~ 135 */
			{
				mask = 1 << ((port - 130) + 2);
			}
		}
		else if(lx_chip_rev() >= LX_CHIP_REV(M16P, A0))
		{

			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 135)  /* 128 ~ 135 */
			{
				mask = 1 << ((port - 128) + 0);
			}
		}

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 143)	/* 136 ~ 143 */
	{
		//M16PP_A0_CTOP_SR_BASE 0xC9305400
		//0xC9305410  CTOP_SR_R04

		if(port <= 136) /* 136 ~ 136 */
		{
			mask = 1 << (9);
		}
		else if(port <= 137)	/* 137 ~ 137 */
		{
			mask = 1 << (13);
		}
		else if(port <= 138)	/* 138 ~ 138 */
		{
			mask = 1 << (10);
		}
		else if(port <= 139)	/* 139 ~ 139 */
		{
			mask = 1 << (14);
		}
#if 0 //need to check
		else if( port <= 140)  /* 140 ~ 140 */
		{
			mask = 1 << ((port - 140)+ 19);
		}
		else if( port <= 143)  /* 141 ~ 143 */
		{
			mask = 1 << ((port - 141)+ 21);
		}
#endif
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		*enable = (value & mask) ? 1 : 0;

		return 0;
	}
	return rc;
}

#endif //INCLUDE_M16PP_CHIP_KDRV

#ifdef INCLUDE_M17_CHIP_KDRV

//#define M17_A0_CTOP_DPE_BASE			0xC930A400		//0xC930_A400
//#define M17_A0_CTOP_FMC_BASE			0xC9309400		//0xC930_9400
//#define M17_A0_CTOP_FME0_BASE		0xC9308800		//0xC930_8800
//#define M17_A0_CTOP_FMS_BASE			0xC930C400		//0xC930_C400
//#define M17_A0_CTOP_GFX_BASE			0xC9C10400		//0xC9C1_0400
//#define M17_A0_CTOP_SR_BASE			0xC9305400		//0xC930_5400
//#define M17_A0_CTOP_AUD_SYN_BASE		0xC9C60000		//0xC9C6_0000
//#define M17_A0_CTOP_CCO_SYN_BASE		0xC9307000		//0xC930_7000
//#define M17_A0_CTOP_CVI_SYN_BASE		0xC9302000		//0xC930_2000
//#define M17_A0_CTOP_DPE_CRC_BASE		0xC930AC00		//0xC930_AC00
//#define M17_A0_CTOP_DPE_SYN_BASE		0xC930A000		//0xC930_A000
//#define M17_A0_CTOP_EMMC_SYN_BASE	0xC3680000		//0xC368_0000
//#define M17_A0_CTOP_FMC_SYN_BASE		0xC9309000		//0xC930_9000
//#define M17_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
//#define M17_A0_CTOP_FME1_SYN_BASE	0xC930B000		//0xC930_B000
//#define M17_A0_CTOP_FMS_SYN_BASE		0xC930C000		//0xC930_C000
//#define M17_A0_CTOP_GBUS_SYN_BASE	0xC9301000		//0xC930_1000
//#define M17_A0_CTOP_GEM_SYN_BASE		0xC3501000		//0xC350_1000
//#define M17_A0_CTOP_GFX_SYN_BASE		0xC9C10000		//0xC9C1_0000
//#define M17_A0_CTOP_GPU_SYN_BASE		0xC9205000		//0xC920_5000
//#define M17_A0_CTOP_IMX_SYN_BASE		0xC9303000		//0xC930_3000
//#define M17_A0_CTOP_LBM_SYN_BASE		0xC9300000		//0xC930_0000
//#define M17_A0_CTOP_M0_SYN_BASE		0xC9C30000		//0xC9C3_0000
//#define M17_A0_CTOP_M1_SYN_BASE		0xC9C40000		//0xC9C4_0000
//#define M17_A0_CTOP_MIP_SYN_BASE		0xC930E000		//0xC930_E000
//#define M17_A0_CTOP_ND0_SYN_BASE		0xC9304000		//0xC930_4000
//#define M17_A0_CTOP_PERI_SYN_BASE	0xC9230000		//0xC923_0000
//#define M17_A0_CTOP_SRE_SYN_BASE		0xC9305000		//0xC930_5000
//#define M17_A0_CTOP_TIV_SYN_BASE		0xC9C50000		//0xC9C5_0000
//#define M17_A0_CTOP_VDEC0_SYN_BASE	0xC9C701C0		//0xC9C7_01C0
//#define M17_A0_CTOP_VDEC1_SYN_BASE	0xC9C711C0		//0xC9C7_11C0
//#define M17_A0_CTOP_VSD_CRC_BASE		0xC9306800		//0xC930_6800
//#define M17_A0_CTOP_VSD_SYN_BASE		0xC9306000		//0xC930_6000

int _GPIO_SetPinMux_M17Ax(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	// not used function. always return OK when GPIO_KERNEL_API used
	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	if(port <= 31)	/* 0 ~ 31 */ //default gpio enable
	{
		if(port <= 15)	/* 0 ~ 15*/
		{
			return 0;
			// Do nothing...
		}
		else if(port <= 23)/* 16~ 23*/
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);

			mask = mask | (1 << 20);
			mask = mask | (1 << 21);
			mask = mask | (1 << 22);
			mask = mask | (1 << 23);
			mask = mask | (1 << 24);

			if(port <= 16)/* 16~ 16*/
			{
				mask = mask | (1 << 13);
				mask = mask | (1 << 26);
			}
			else if(port <= 17)/* 17~ 17*/
			{
				mask = mask | (1 << 26);
			}
			else if(port <= 19)/* 18~ 19*/
			{
				mask = mask | (1 << 8);
				mask = mask | (1 << 11);
				if(enable)	value &= (~mask);
				CTOP_CTRL_M17A0_WRITE(FMC,0x1c,value);

				//M17_A0_CTOP_FMS_BASE 0xC930C400
				//CTOP_FMS_R12 0xC930C430
				mask = 0;
				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FMS,0x30);
				if(enable)	value &= (~mask);
				/* ignore non gpio case */
				CTOP_CTRL_M17A0_WRITE(FMS,0x30,value);
				return 0;
			}
			else if(port <= 20)/* 20~ 20*/
			{
			}
			else if(port <= 21)/* 21~ 21*/
			{
				mask = mask | (1 << 12);
				mask = mask | (1 << 25);
			}
			else if(port <= 23)/* 23~ 23*/
			{
			}

			if(enable)	value &= (~mask);
			/* is pinmuxed with multi function, ignore nongpio(else) case*/
			CTOP_CTRL_M17A0_WRITE(FMC,0x1c,value);
			return 0;
		}
		else if(port <= 29)/* 24 ~ 29*/
		{
				//M17_A0_CTOP_FME0_BASE		0xC9308800
				//CTOP_FME0_R16 0xC9308840

				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FME0,0x40);
				if(enable)	value &= (~mask);
				else		value |= mask;
				CTOP_CTRL_M17A0_WRITE(FME0,0x40,value);
			return 0;
			// Do nothing...
		}
		else if(port <= 30)/* 1 ~ 17*/
		{
			return 0;
			// Do nothing...
		}

		return 0;
		// Do nothing...
	}
	else if(port <= 39) /* 32 ~ 39 */
	{

		//M17_A0_CTOP_SR_BASE	0xC9305400
		//0xC9305410  CTOP_SR_R04
		mask = 1 << ((port - 32) + 24);
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(SR,0x10,value);
		return 0;
	}
	else if(port <= 43) /* 40 ~ 43 */ //need to check : gp5_0~3
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 53) /* 44 ~ 53 */
	{
		//M17_A0_CTOP_FMS_BASE	0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		if( port <= 47) /* 44 ~ 47 */
		{
			mask = 1 << ((port - 44)+ 28);
		}
		else if( port <= 53)  /* 48 ~ 53 */
		{
			mask = 1 << ((port - 48)+ 13);
		}

		value = CTOP_CTRL_M17A0_READ(FMS,0x2c);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FMS,0x2c,value);
		return 0;
	}
	else if(port <= 55) /* 54 ~ 55 */ //need to check : gp6_6~7
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 71) /* 56 ~ 71 */
	{
		//M17_A0_CTOP_FMC_BASE 	0xC9309400
		//0xC9309418 FMC CTOP_FMC_R06

		if( port <= 63) /* 56 ~ 63 */
		{
			mask = 1 << ((port - 56)+ 24);
		}
		else if ( port <= 67)	/* 64 ~ 67 */
		{
			return 0;  // Do nothing...
		}

		else if( port <= 68)  /* 68 ~ 68 */
		{
			mask = 1 << ((port - 68)+ 23);
		}
		else if( port <= 71)  /* 69 ~ 71 */
		{
			mask = 1 << ((port - 68)+ 16);
		}
		value = CTOP_CTRL_M17A0_READ(FMC,0x18);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FMC,0x18,value);
		return 0;
	}
	else if(port <= 79) /* 72 ~ 79 */
	{
		//M17_A0_CTOP_SR_BASE	0xC9305400
		//0xC9305410  CTOP_SR_R04

		if( port <= 73) /* 72 ~ 73 */
		{
			mask = 1 << ((port - 72)+ 15);
		}
		else if( port <= 74)  /* 74 ~ 74 */
		{
			mask = 1 << (7);
		}
		else if( port <= 75)  /* 75 ~ 75 */
		{
			mask = 1 << (11);
		}
		else if( port <= 77)  /* 76~ 77 */
		{
			mask = 1 << ((port - 76)+ 17);
		}
		else if( port <= 78)  /* 78 78 */
		{
			mask = 1 << (8);
		}
		else if( port <= 79)  /* 79 79 */
		{
			mask = 1 << (12);
		}
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(SR,0x10,value);
		return 0;
	}
	else if(port <= 87) /* 80 ~ 87 */
	{
		if( port <= 80) /* 80 ~ 80 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			mask = 1 << (19);
			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			if(enable)	value |= mask;
			else		value &= (~mask);
			CTOP_CTRL_M17A0_WRITE(FMC,0x18,value);
			return 0;
		}
		else if (port <= 84)	/* 81 ~ 84 */
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			mask = 1 << ((81 - port) + 30);
			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);
			if(enable)	value |= mask;
			else		value &= (~mask);
			CTOP_CTRL_M17A0_WRITE(FMC,0x1c,value);
			return 0;
		}
		else if(port <= 87) /* 85 ~ 87 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			mask = 1 << ((port - 85)+ 20);

			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			if(enable)	value |= mask;
			else		value &= (~mask);
			CTOP_CTRL_M17A0_WRITE(FMC,0x18,value);
			return 0;
		}
	}
	else if(port <= 93)  /* 88 ~ 93*/
	{
		//M17_A0_CTOP_FME0_BASE	0xC9308800
		//0xC9308830 AUD CTOP_FME0_R12
		mask = 1 << ((port - 88)+ 24);

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);

		if(port == 89)
		{
			if(enable)	value |= mask;
			else		value &= (~mask);
		}
		else
		{
			if(enable)	value &= (~mask);
			else		value |= mask;
		}
		CTOP_CTRL_M17A0_WRITE(FME0,0x30,value);
		return 0;
	}
	else if(port <= 95) /* 94 ~ 95 */ //need to check : gp11_6, gp11_7
	{
		//0xC9308030 AUD CTOP_FME0_R12
		mask = 1 << ((port - 94)+ 30);
		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FME0,0x30,value);
		return 0;
		// Do nothing...
	}
	else if( port <= 103)  /* 96 ~ 103 */
	{
		//M17_A0_CTOP_FMS_BASE 0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		mask = 1 << ((port - 96)+ 20); //gone

		value = CTOP_CTRL_M17A0_READ(FMC,0x2c);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FMC,0x2c,value);
		return 0;
	}
	else if(port <= 104)	/* 104 ~ 104 */ //need to check : gp13_0
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 110)	/* 105 ~ 110 */
	{
		// M17_A0_CTOP_DPE_SYN_BASE	0xC930A000
		//0xC930A080 DPE CTOP_DPE_R32
		mask = 1 << ((port - 105) + 26);

		value = CTOP_CTRL_M17A0_READ(DPE,0x80);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(DPE,0x80,value);
		return 0;
	}
	else if(port <= 111)	/* 111 ~ 111 */
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 135)	/* 112 ~ 135 */
	{
		//M17_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
		//0xC9308030 AUD CTOP_FME0_R12

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{
			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 129)  /* 128 ~ 129 */
			{
				/* bit field is disappeared in M16+ B0 */
				return 0;
			}
			else if( port <= 135)  /* 130 ~ 135 */
			{
				mask = 1 << ((port - 130) + 2);
			}
		}
		else if(lx_chip_rev() >= LX_CHIP_REV(M16P, A0))
		{

			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 135)  /* 128 ~ 135 */
			{
				mask = 1 << ((port - 128) + 0);
			}
		}

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(FME0,0x30,value);

		return 0;
	}
	else if(port <= 143)	/* 136 ~ 143 */
	{
		//M17_A0_CTOP_SR_BASE	0xC9305400
		//0xC9305410  CTOP_SR_R04

		if(port <= 136) /* 136 ~ 136 */
		{
			mask = 1 << (9);
		}
		else if(port <= 137)	/* 137 ~ 137 */
		{
			mask = 1 << (13);
		}
		else if(port <= 138)	/* 138 ~ 138 */
		{
			mask = 1 << (10);
		}
		else if(port <= 139)	/* 139 ~ 139 */
		{
			mask = 1 << (14);
		}
	#if 0 //need to check
		else if( port <= 140)  /* 140 ~ 140 */
		{
			mask = 1 << ((port - 140)+ 19);
		}
		else if( port <= 143)  /* 141 ~ 143 */
		{
			mask = 1 << ((port - 141)+ 21);
		}
	#endif
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_M17A0_WRITE(SR,0x10,value);
		return 0;
	}
	return rc;
}


static int _GPIO_GetPinMux_M17Ax(UINT32 port, BOOLEAN *enable)
{
	int rc = 0;
	UINT32 mask = 0;
	UINT32 value;

	// not used function. always return OK when GPIO_KERNEL_API used
	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	if(port <= 31)	/* 0 ~ 31 */ //default gpio enable
	{
		if(port <= 15)	/* 0 ~ 15*/
		{
			return 0;
			// Do nothing...
		}
		else if(port <= 23)/* 16~ 23*/
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);

			mask = mask | (1 << 20);
			mask = mask | (1 << 21);
			mask = mask | (1 << 22);
			mask = mask | (1 << 23);
			mask = mask | (1 << 24);

			if(port <= 16)/* 16~ 16*/
			{
				mask = mask | (1 << 13);
				mask = mask | (1 << 26);
			}
			else if(port <= 17)/* 17~ 17*/
			{
				mask = mask | (1 << 26);
			}
			else if(port <= 19)/* 18~ 19*/
			{
				mask = mask | (1 << 8);
				mask = mask | (1 << 11);

				if( (value & mask) != mask)
				{
					*enable = 0;
					return 0;
				}

				//M17_A0_CTOP_FMS_BASE 0xC930C400
				//CTOP_FMS_R12 0xC930C430
				mask = 0;
				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FMS,0x30);
				*enable = ((value & mask) == mask) ? 1 : 0;
				return 0;
			}
			else if(port <= 20)/* 20~ 20*/
			{
			}
			else if(port <= 21)/* 21~ 21*/
			{
				mask = mask | (1 << 12);
				mask = mask | (1 << 25);
			}
			else if(port <= 23)/* 23~ 23*/
			{
			}

			*enable = ((value & mask) == mask) ? 1 : 0;
			return 0;
		}
		else if(port <= 29)/* 24 ~ 29*/ //default gpio enable
		{
				//M17_A0_CTOP_FME0_SYN_BASE	0xC9308000
				//CTOP_FME0_R16 0xC9308040

				mask = 1 <<(25);
				value = CTOP_CTRL_M17A0_READ(FME0,0x40);
				*enable = (value & mask) ? 0 : 1;
			return 0;
			// Do nothing...
		}
		else if(port <= 30)/* 1 ~ 17*/ //default gpio enable
		{
			return 0;
			// Do nothing...
		}

		return 0;
		// Do nothing...
	}
	else if(port <= 39) /* 32 ~ 39 */
	{

		//M17_A0_CTOP_SR_BASE	0xC9305400
		//0xC9305410  CTOP_SR_R04
		mask = 1 << ((port - 32) + 24);
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 43) /* 40 ~ 43 */ //need to check : gp5_0~3
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 53) /* 44 ~ 53 */
	{
		//M17_A0_CTOP_FMS_BASE	0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		if( port <= 47) /* 44 ~ 47 */
		{
			mask = 1 << ((port - 44)+ 28);
		}
		else if( port <= 53)  /* 48 ~ 53 */
		{
			mask = 1 << ((port - 48)+ 13);
		}

		value = CTOP_CTRL_M17A0_READ(FMS,0x2c);
		*enable = (value & mask) ? 1 : 0;

		return 0;
	}
	else if(port <= 55) /* 54 ~ 55 */ //need to check : gp6_6~7
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 71) /* 56 ~ 71 */
	{
		//M17_A0_CTOP_FMC_BASE 	0xC9309400
		//0xC9309418 FMC CTOP_FMC_R06


		if( port <= 63) /* 56 ~ 63 */
		{
			mask = 1 << ((port - 56)+ 24);
		}
		else if ( port <= 67)	/* 64 ~ 67 */
		{
			return 0;  // Do nothing...
		}

		else if( port <= 68)  /* 68 ~ 68 */
		{
			mask = 1 << ((port - 68)+ 23);
		}
		else if( port <= 71)  /* 69 ~ 71 */
		{
			mask = 1 << ((port - 68)+ 16);
		}
		value = CTOP_CTRL_M17A0_READ(FMC,0x18);
		*enable = (value & mask) ? 1 : 0;

		return 0;
	}
	else if(port <= 79) /* 72 ~ 79 */
	{
		//M17_A0_CTOP_SR_BASE	0xC9305400
		//0xC9305410  CTOP_SR_R04

		if( port <= 73) /* 72 ~ 73 */
		{
			mask = 1 << ((port - 72)+ 15);
		}
		else if( port <= 74)  /* 74 ~ 74 */
		{
			mask = 1 << (7);
		}
		else if( port <= 75)  /* 75 ~ 75 */
		{
			mask = 1 << (11);
		}
		else if( port <= 77)  /* 76~ 77 */
		{
			mask = 1 << ((port - 76)+ 17);
		}
		else if( port <= 78)  /* 78 78 */
		{
			mask = 1 << (8);
		}
		else if( port <= 79)  /* 79 79 */
		{
			mask = 1 << (12);
		}
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 87) /* 80 ~ 87 */
	{
		if( port <= 80) /* 80 ~ 80 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			mask = 1 << (19);
			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			*enable = (value & mask) ? 1 : 0;
			return 0;
		}
		else if (port <= 84)	/* 81 ~ 84 */
		{
			//0xC930901C FMC CTOP_FMC_R07
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			mask = 1 << ((81 - port) + 30);
			value = CTOP_CTRL_M17A0_READ(FMC,0x1c);
			*enable = (value & mask) ? 1 : 0;
			return 0;
		}
		else if(port <= 87) /* 85 ~ 87 */
		{
			//0xC9309018 FMC CTOP_FMC_R06
			//M17_A0_CTOP_FMC_SYN_BASE 	0xC9309000

			mask = 1 << ((port - 85)+ 20);

			value = CTOP_CTRL_M17A0_READ(FMC,0x18);
			*enable = (value & mask) ? 1 : 0;
			return 0;
		}
	}
	else if(port <= 93)  /* 88 ~ 93*/
	{
		//M17_A0_CTOP_FME0_BASE	0xC9308800
		//0xC9308830 AUD CTOP_FME0_R12
		mask = 1 << ((port - 88)+ 24);

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);

		if(port == 89)
		{
			*enable = (value & mask) ? 1 : 0;
		}
		else
		{
			*enable = (value & mask) ? 0 : 1;
		}
		return 0;
	}
	else if(port <= 95) /* 94 ~ 95 */ //need to check : gp11_6, gp11_7
	{
		//0xC9308830 AUD CTOP_FME0_R12
		mask = 1 << ((port - 94)+ 30);
		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		*enable = (value & mask) ? 1 : 0;
		return 0;
		// Do nothing...
	}
	else if( port <= 103)  /* 96 ~ 103 */
	{
		//M17_A0_CTOP_FMS_BASE 0xC930C400
		//CTOP_FMS_R11 0xC930C42c

		mask = 1 << ((port - 96)+ 20); //gone

		value = CTOP_CTRL_M17A0_READ(FMC,0x2c);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 104)	/* 104 ~ 104 */ //need to check : gp13_0
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 110)	/* 105 ~ 110 */
	{
		// M17_A0_CTOP_DPE_SYN_BASE	0xC930A000
		//0xC930A080 DPE CTOP_DPE_R32
		mask = 1 << ((port - 105) + 26);

		value = CTOP_CTRL_M17A0_READ(DPE,0x80);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 111)	/* 111 ~ 111 */
	{
		return 0;
		// Do nothing...
	}
	else if(port <= 135)	/* 112 ~ 135 */
	{
		//M17_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
		//0xC9308030 AUD CTOP_FME0_R12

		if(lx_chip_rev() >= LX_CHIP_REV(M16P, B0))
		{

			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 129)  /* 128 ~ 129 */
			{
				/* bit field is disappeared in M16+ B0 */
				return 0;
			}
			else if( port <= 135)  /* 130 ~ 135 */
			{
				mask = 1 << ((port - 130) + 2);
			}
		}
		else if(lx_chip_rev() >= LX_CHIP_REV(M16P, A0))
		{

			if(port <= 119) /* 112 ~ 119 */
			{
				mask = 1 << ((port - 112)+ 16);
			}
			else if( port <= 127)  /* 120 ~ 127 */
			{
				mask = 1 << ((port - 120)+ 8);
			}
			else if( port <= 135)  /* 128 ~ 135 */
			{
				mask = 1 << ((port - 128) + 0);
			}
		}

		value = 		CTOP_CTRL_M17A0_READ(FME0,0x30);
		*enable = (value & mask) ? 1 : 0;
		return 0;
	}
	else if(port <= 143)	/* 136 ~ 143 */
	{
		//M17_A0_CTOP_SR_BASE	0xC9305400
		//0xC9305410  CTOP_SR_R04

		if(port <= 136) /* 136 ~ 136 */
		{
			mask = 1 << (9);
		}
		else if(port <= 137)	/* 137 ~ 137 */
		{
			mask = 1 << (13);
		}
		else if(port <= 138)	/* 138 ~ 138 */
		{
			mask = 1 << (10);
		}
		else if(port <= 139)	/* 139 ~ 139 */
		{
			mask = 1 << (14);
		}
	#if 0 //need to check
		else if( port <= 140)  /* 140 ~ 140 */
		{
			mask = 1 << ((port - 140)+ 19);
		}
		else if( port <= 143)  /* 141 ~ 143 */
		{
			mask = 1 << ((port - 141)+ 21);
		}
	#endif
		value = CTOP_CTRL_M17A0_READ(SR,0x10);
		*enable = (value & mask) ? 1 : 0;

		return 0;
	}
	return rc;
}
#endif //INCLUDE_M17_CHIP_KDRV



/*************************************************************************
* Set Pinmux
*************************************************************************/


static int _GPIO_SetIntrArrayNum(UINT32 intrArrayNum)
{
	g_poll_intr_idx = intrArrayNum;
	return 0;
}


/*************************************************************************
* Set Mode
*************************************************************************/
int _GPIO_SetMode(UINT32 port, LX_GPIO_MODE_T mode)
{
	UINT32 direction, mask;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		direction = GPIONDIR(port/8);

		mask = 1 << (port % 8);
		direction = (mode == LX_GPIO_MODE_INPUT) ?
					direction & (~mask) : direction | mask;

		GPIONDIR(port/8) = direction;
	}
	else // GPIO_KERNEL_API
	{
		struct gpio_desc *gpiod;
		struct device dev = { .init_name = "gpio_kerneltable", };
		UINT8 portstr[GPIO_STRSIZE];
		int val,ret = 0;
		ret = snprintf(portstr,GPIO_STRSIZE,"%d", port);
		if(ret < 0)
		{
			GPIO_ERROR("snprint fail\n");
			return -1;
		}
		#ifdef INCLUDE_M17_CHIP_KDRV
		if(port == 107 || port == 108)
		{
			UINT32 direction, mask;
			direction = GPIONDIR(port/8);

			mask = 1 << (port % 8);
			direction = (mode == LX_GPIO_MODE_INPUT) ?
						direction & (~mask) : direction | mask;
			GPIONDIR(port/8) = direction;
		}
		else
		#endif
		{
			gpiod = gpiod_get(&dev, portstr, GPIOD_ASIS);

			if (IS_ERR(gpiod))
			{
				GPIO_ERROR("unable to get gpio desc[%d:%p]\n",port,gpiod);
				return 0;
			}

			val = gpiod_get_value(gpiod);
			direction = (mode == LX_GPIO_MODE_INPUT) ?
						gpiod_direction_input(gpiod): gpiod_direction_output(gpiod,val);
			gpiod_put(gpiod);
		}
	}

	return 0;
}

 int _GPIO_SetIntr(UINT32 port, UINT32 enable)
{
	UINT32 enable_array=0, sense_array=0,both_edge_array=0,high_array=0, mask=0;

	sense_array = GPIONIS(port/8);
	high_array  = GPIONIEV(port/8);
	both_edge_array = GPIONIBE(port/8);
	enable_array = GPIONIE(port/8);

	mask = 1 << (port % 8);

	/* same sense_array setting is need */
	sense_array = sense_array & (~mask) /*0*/;

	switch(enable)
	{
		case 0:
		case 1:
			high_array	= (enable == 1) ?
						  (high_array | mask) /*1*/: high_array & (~mask);

			both_edge_array = (enable == 1) ?
						  (both_edge_array | mask) /*1*/: both_edge_array & (~mask);

			enable_array = (enable == 1) ?
						  (enable_array | mask) /*1*/: enable_array & (~mask);

			break;
		case LOW_EDGE_ENABLE:
			high_array = high_array & (~mask);
			both_edge_array = both_edge_array & (~mask);
			enable_array = enable_array | mask;

			break;

		case HIGH_EDGE_ENABLE:

			high_array = high_array | mask;
			both_edge_array = both_edge_array & (~mask);
			enable_array = enable_array | mask;
			break;
		default:

			break;

		}

	GPIONIS(port/8) = sense_array;
	GPIONIEV(port/8) = high_array;
	GPIONIBE(port/8) = both_edge_array;
	GPIONIE(port/8) = enable_array;

	return 0;
}

 int _GPIO_GetMode(UINT32 port, LX_GPIO_MODE_T *mode)
{
	UINT32 direction, mask;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		direction = GPIONDIR(port/8);
		mask = 1 << (port % 8);
		*mode = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;
	}
	else // GPIO_KERNEL_API
	{
		struct gpio_desc *gpiod;
		struct device dev = { .init_name = "gpio_kerneltable", };
		UINT8 portstr[GPIO_STRSIZE];
		int ret = 0;
		ret = snprintf(portstr,GPIO_STRSIZE,"%d", port);
		if(ret < 0)
		{
			GPIO_ERROR("snprint fail\n");
			return -1;
		}

		#ifdef INCLUDE_M17_CHIP_KDRV
		if(port == 107 || port == 108)
		{
			UINT32 direction, mask;

			direction = GPIONDIR(port/8);
			mask = 1 << (port % 8);
			*mode = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;

		}
		else
		#endif
		{
			gpiod = gpiod_get(&dev, portstr, GPIOD_ASIS);

			if (IS_ERR(gpiod))
			{
				GPIO_ERROR("unable to get gpio desc[%d:%p]\n",port,gpiod);
				return 0;
			}
			//printk("getmode gpiod[%x] port[%d] \n",gpiod,port);

			direction = gpiod_get_direction(gpiod);
			if( direction <= LX_GPIO_MODE_OUTPUT)
			{
				*mode  = (LX_GPIO_MODE_T)!direction;
			}
			else
			{
				GPIO_ERROR("check get direction port[%d] direction[%d]\n",port,direction);
				gpiod_put(gpiod);
				return -1;
			}
			gpiod_put(gpiod);
		}
	}

	return 0;
}

 int _GPIO_GetModeEx(UINT32 port)
{
	int	ret = 0;
	UINT32 direction, mask;
	direction = GPIONDIR(port/8);
	mask = 1 << (port % 8);
	ret = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;
	return ret;
}
 int _GPIO_GetModeR(UINT32 port)
{
	int	ret = 0;
	UINT32 direction, mask;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		direction = GPIONDIR(port/8);
		mask = 1 << (port % 8);
		ret = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;
	}
	else // GPIO_KERNEL_API
	{
		struct gpio_desc *gpiod;
		struct device dev = { .init_name = "gpio_kerneltable", };
		UINT8 portstr[GPIO_STRSIZE];
		ret = snprintf(portstr,GPIO_STRSIZE,"%d", port);
		if(ret < 0)
		{
			GPIO_ERROR("snprint fail\n");
			return -1;
		}

		#ifdef INCLUDE_M17_CHIP_KDRV
		if( port == 107 || port == 108)
		{
			UINT32 direction, mask;
			int ret;

			direction = GPIONDIR(port/8);
			mask = 1 << (port % 8);
			ret = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;

		}
		else
		#endif
		{
			gpiod = gpiod_get(&dev, portstr, GPIOD_ASIS);

			if (IS_ERR(gpiod))
			{
				GPIO_ERROR("unable to get gpio desc[%d:%p]\n",port,gpiod);
				return -1;
			}

			//GPIO_ERROR("getmode gpiod[%x] port[%d] \n",gpiod,port);

			ret = gpiod_get_direction(gpiod);

			if( ret <= LX_GPIO_MODE_OUTPUT)
			{
				ret = !ret;
			}
			else
			{
				GPIO_ERROR("check get direction port[%d] ret[%d]\n",port,ret);
				gpiod_put(gpiod);
				return -1;
			}
			gpiod_put(gpiod);
		}
	}

	return ret;
}


/*
	port : hw gpio pin
    INT_ARRAY : handling 24 gpio intr
*/
int _GPIO_SetIntrAction(UINT32 port, void (*pfnGPIO_CB)(UINT32 value), UINT32 enable, LX_GPIO_INFO_T * info)
{
	ULONG	flags;
	UINT32 	pid = 0;

	if(info == NULL)
	{
		GPIO_DEBUG("task creation info should be checked \n" );
		return -1;
	}

	pid = gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY] & 0xffff;
	GPIO_DEBUG("current->pid[%8x] prev pid[%8x] en[%d]\n",current->pid,pid,enable);

	gpio_isr_info[port].count_enable = 0;
	gpio_isr_info[port].cb_enable = 0;

	info->task = NOT_CREATE;// CREATE_TASK when CALLBACK_ENABLE

	if(enable== CALLBACK_ENABLE)
	{

		gpio_isr_info[port].cb_enable = 1;
		//for setting bit(enabled gpio intr) in a int_array in CALLBACK_ENABLE
		if((gpio_intrarray_used[port/GPIO_NUM_IN_INT_ARRAY] & (1 << (port % GPIO_NUM_IN_INT_ARRAY)) ) == 0)
		{
			GPIO_DEBUG("CALLBACK_ENABLE enable[%d] port[%d]\n",enable,port );
			gpio_intrarray_used[port / GPIO_NUM_IN_INT_ARRAY] |= 1 << (port % GPIO_NUM_IN_INT_ARRAY);
		}


		// for terminating previous USER Task waiting same gpio intrrupt		//pid != 0 means there was poll reqeuset in this intr array
		if( (pid != 0 && pid != current->pid) )
		{


			GPIO_DEBUG("terminate previous CUR[%d] PREV[%d]\n",current->pid,pid );
			spin_lock_irqsave(&gpioPoll_lock, flags);
			gpio_intr_pin = INT_POLL_CLEAR;
			spin_unlock_irqrestore(&gpioPoll_lock, flags);

			gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY] = current->pid & 0xffff;
			info->task =  CREATE_TASK; //jun.kong
			//info->task =  NOT_CREATE; //jun.kong
			wake_up_interruptible_all(gGPIOPollWaitQueueT[port/GPIO_NUM_IN_INT_ARRAY]);

		}
		// for skipping USER Task creation if task handling 24 interrupt in same int_array exists
		else if (	pid != 0 && pid == current->pid)
		{
			GPIO_DEBUG("skip CUR[%d] PREV[%d]\n",current->pid,pid );
			info->task =  NOT_CREATE;
		}
		// for create USER Task if task handling 24 interrupt in same intr)array not exist yet
		//else if (pid == 0 && pfnGPIO_CB == NULL && enable== CALLBACK_ENABLE )
		else if (pid == 0 && pfnGPIO_CB != NULL )
		{
			GPIO_DEBUG("create CUR[%d] PREV[%d]\n",current->pid,pid );
			info->task =  CREATE_TASK;
			gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY] = current->pid & 0xffff;

		}

	}
	// for terminate USER Level GPIO TASK if there is not enabeld gpio intr in same int_array
	else if (enable == CALLBACK_DISABLE)
	{
		gpio_isr_info[port].cb_enable = 0;
		GPIO_DEBUG("CALLBACK_ENABLE enable[%d] port[%d gpio_intrarray_used[%x]gpio_intrarray_used[%x] \n",enable,port,gpio_intrarray_used[port/GPIO_NUM_IN_INT_ARRAY],gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY]  );
		gpio_intrarray_used[port/GPIO_NUM_IN_INT_ARRAY] &= (~(1 << (port % GPIO_NUM_IN_INT_ARRAY)));

		//f there is not enabeld gpio intr in same int_array
		if(gpio_intrarray_used[port/GPIO_NUM_IN_INT_ARRAY] == 0)
		{
			spin_lock_irqsave(&gpioPoll_lock, flags);
			gpio_intr_pin = INT_POLL_CLEAR;
			spin_unlock_irqrestore(&gpioPoll_lock, flags);
			info->task =  NOT_CREATE;
			gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY] = 0;
			wake_up_interruptible_all(gGPIOPollWaitQueueT[port/GPIO_NUM_IN_INT_ARRAY]);
			GPIO_DEBUG("CALLBACK_DISABLE enable[%d] port[%d]\n",enable,port );
		}
	}
	else if (enable == COUNT_ENABLE)
	{
		GPIO_DEBUG("COUNT ENALBE enable[%d] port[%d]\n",enable,port );
		gpio_isr_info[port].count_enable = 1;
		enable = 1;  //for _GPIO_SetIntr
	}
	else if (enable == COUNT_DISABLE)
	{
		GPIO_DEBUG("COUNT DISABLE enable[%d] port[%d]\n",enable,port );
		 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
		gpio_isr_info[port].count_enable = 0;
		gpio_isr_info[port].intr_count= 0;
		enable = 0; //for _GPIO_SetIntr
	}
	else if (enable == HIGH_EDGE_ENABLE || enable == LOW_EDGE_ENABLE)
	{

		if(enable == HIGH_EDGE_ENABLE )
			GPIO_DEBUG("COUNT HIGH_EDGE_ENABLE enable[%d] port[%d]\n",enable,port );
		else if (enable == LOW_EDGE_ENABLE )
			GPIO_DEBUG("COUNT LOW_EDGE_ENABLE enable[%d] port[%d]\n",enable,port );

		gpio_isr_info[port].cb_enable = 1;
		//for setting bit(enabled gpio intr) in a int_array in CALLBACK_ENABLE
		if((gpio_intrarray_used[port/GPIO_NUM_IN_INT_ARRAY] & (1 << (port % GPIO_NUM_IN_INT_ARRAY)) ) == 0)
		{
			GPIO_DEBUG("CALLBACK_ENABLE enable[%d] port[%d]\n",enable,port );
			gpio_intrarray_used[port / GPIO_NUM_IN_INT_ARRAY] |= 1 << (port % GPIO_NUM_IN_INT_ARRAY);
		}


		// for terminating previous USER Task waiting same gpio intrrupt		//pid != 0 means there was poll reqeuset in this intr array
		if( (pid != 0 && pid != current->pid) )
		{


			GPIO_DEBUG("terminate previous CUR[%d] PREV[%d]\n",current->pid,pid );
			spin_lock_irqsave(&gpioPoll_lock, flags);
			gpio_intr_pin = INT_POLL_CLEAR;
			spin_unlock_irqrestore(&gpioPoll_lock, flags);

			gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY] = current->pid & 0xffff;
			info->task =  CREATE_TASK; //jun.kong
			//info->task =  NOT_CREATE; //jun.kong
			wake_up_interruptible_all(gGPIOPollWaitQueueT[port/GPIO_NUM_IN_INT_ARRAY]);

		}
		// for skipping USER Task creation if task handling 24 interrupt in same int_array exists
		else if (	pid != 0 && pid == current->pid)
		{
			GPIO_DEBUG("skip CUR[%d] PREV[%d]\n",current->pid,pid );
			info->task =  NOT_CREATE;
		}
		// for create USER Task if task handling 24 interrupt in same intr)array not exist yet
		//else if (pid == 0 && pfnGPIO_CB == NULL && enable== CALLBACK_ENABLE )
		else if (pid == 0 && pfnGPIO_CB != NULL )
		{
			GPIO_DEBUG("create CUR[%d] PREV[%d]\n",current->pid,pid );
			info->task =  CREATE_TASK;
			gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY] = current->pid & 0xffff;

		}

		_GPIO_SetMode( port, LX_GPIO_MODE_INPUT );
		_GPIO_SetIntr( port, enable );
		return 0;
	}



	GPIO_DEBUG("_GPIO_SetIntr  arrayid[%x] value[%x] poll context[%8x] gpiinfo[%8x] last[%d] enable[%d] port[%d]\n",port/GPIO_NUM_IN_INT_ARRAY,gpio_intrarray_used[port/GPIO_NUM_IN_INT_ARRAY],gpio_pollarray_context[port/GPIO_NUM_IN_INT_ARRAY],info->task, g_poll_intr_idx,enable,port );
	_GPIO_SetMode( port, LX_GPIO_MODE_INPUT );
	_GPIO_SetIntr( port, enable );

	return 0;
}

static int _GPIO_GetIntrValue(UINT32 * port, LX_GPIO_VALUE_T *value)
{
	ULONG flags = 0;

	if (gpio_intr_pin == INT_POLL_CLEAR)
	{
		*port =  (UINT32)INT_POLL_CLEAR;
		spin_lock_irqsave(&gpioPoll_lock, flags);
		gpio_intr_pin = 0;
		gpio_intr_pin_value = 0;
		spin_unlock_irqrestore(&gpioPoll_lock, flags);
	}
	else if( gpio_intr_pin != 0)
	{
		*port =  (UINT32)gpio_intr_pin;
		*value = (LX_GPIO_VALUE_T)gpio_intr_pin_value;

		spin_lock_irqsave(&gpioPoll_lock, flags);
		gpio_intr_pin = 0;
		gpio_intr_pin_value = 0;
		spin_unlock_irqrestore(&gpioPoll_lock, flags);
	}
	else
	{
		*port =  (UINT32)0;
		*value = (LX_GPIO_VALUE_T)0;
	}
	return 0;
}

/*************************************************************************
* Get Value
*************************************************************************/

int _GPIO_GetValue(UINT32 port, LX_GPIO_VALUE_T *value)
{
	int ret = 0;
	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		UINT32 data = GPIONDATA(port/8);
		*value = ((data >> (port % 8)) & 0x1) ? LX_GPIO_VALUE_HIGH : LX_GPIO_VALUE_LOW;
	}
	else
	{
		struct gpio_desc *gpiod;

		struct device dev = { .init_name = "gpio_kerneltable", };

		UINT8 portstr[GPIO_STRSIZE];
		ret = snprintf(portstr,GPIO_STRSIZE,"%d", port);
		if(ret < 0)
		{
			GPIO_ERROR("snprint fail\n");
			return -1;
		}

		#ifdef INCLUDE_M17_CHIP_KDRV
		/* gpio 31,13,107,108 is directly controlled by kernel */
		if(port == 107 || port == 108)
		{
			UINT32 data = GPIONDATA(port/8);
			*value = ((data >> (port % 8)) & 0x1) ? LX_GPIO_VALUE_HIGH : LX_GPIO_VALUE_LOW;
		}
		else
		#endif
		{
			gpiod = gpiod_get(&dev, portstr, GPIOD_IN);

			if (IS_ERR(gpiod))
			{
				GPIO_ERROR("unable to get gpio desc[%d:%p]\n",port,gpiod);
				return 0;
			}

			ret = gpiod_get_value(gpiod);
			if( ret < 0)
			{
				GPIO_ERROR("check get val port[%d] ret[%d]\n",port,ret);
				gpiod_put(gpiod);
				return -1;
			}
			*value = (LX_GPIO_VALUE_T)(ret);
			gpiod_put(gpiod);
		}
	}

	return 0;
}

int _GPIO_GetValueEx(UINT32 port)
{

	int value;
	UINT32 data = GPIONDATA(port/8);
	value = ((data >> (port % 8)) & 0x1) ? 1 : 0;

	return value;
}

int _GPIO_GetValueR(UINT32 port)
{
	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		LX_GPIO_VALUE_T ret;
		_GPIO_GetValue(port, &ret);
		return ret;
	}
	else
	{
		LX_GPIO_VALUE_T ret;
		struct gpio_desc *gpiod;
		struct device dev = { .init_name = "gpio_kerneltable", };

		UINT8 portstr[GPIO_STRSIZE];
		int r = 0;
		r = snprintf(portstr,GPIO_STRSIZE,"%d", port);
		if(r < 0)
		{
			GPIO_DEBUG("check port\n");
		}

		#ifdef INCLUDE_M17_CHIP_KDRV
		/* gpio 31,13,107,108 is directly controlled by kernel */
		if(port == 107 || port == 108)
		{
			LX_GPIO_VALUE_T ret;
			_GPIO_GetValue(port, &ret);
			return ret;
		}
		else
		#endif
		{
			gpiod = gpiod_get(&dev, portstr, GPIOD_IN);

			if (IS_ERR(gpiod))
			{
				GPIO_ERROR("unable to get gpio desc[%d:%p]\n",port,gpiod);
				return -1;
			}
			ret = (LX_GPIO_VALUE_T)(gpiod_get_value(gpiod));

			if( ret < 0)
			{
				GPIO_ERROR("check get val port[%d] ret[%d]\n",port,ret);
				gpiod_put(gpiod);
				return -1;
			}
			gpiod_put(gpiod);
			return ret;
		}
	}

	return 0;
}

int _GPIO_SetValue(UINT32 port, LX_GPIO_VALUE_T value)
{
	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		UINT32 mask = 0, data = 0;

		mask = 1 << (2 + (port % 8));

		data = (value == LX_GPIO_VALUE_HIGH) ? 0xff : 0x0;
		SYS_WRITE32(GPION_BASE(port/8) + mask, data);
	}
	else
	{
		struct gpio_desc *gpiod;
		struct device dev = { .init_name = "gpio_kerneltable", };

		UINT8 portstr[GPIO_STRSIZE];
		int ret = 0;
		ret = snprintf(portstr,GPIO_STRSIZE,"%d", port);
		if(ret < 0)
		{
			GPIO_DEBUG("check port\n");
		}

		#ifdef INCLUDE_M17_CHIP_KDRV
		/* gpio 107,108 is directly controlled by kernel
		   we cann't use 107,108 using gpiod_get directlry*/
		if( port == 107 || port == 108)
		{
			UINT32 mask = 0, data = 0;

			mask = 1 << (2 + (port % 8));

			data = (value == LX_GPIO_VALUE_HIGH) ? 0xff : 0x0;
			SYS_WRITE32(GPION_BASE(port/8) + mask, data);
		}
		else
		#endif
		{
			gpiod = gpiod_get(&dev, portstr, GPIOD_OUT_HIGH);
			if (IS_ERR(gpiod))
			{
				GPIO_ERROR("unable to get gpio desc[%d,%p]\n",port,gpiod);
				return 0;
			}
			gpiod_set_value(gpiod, (int) value);

			gpiod_put(gpiod);
		}
	}

	return 0;
}


#ifdef KDRV_CONFIG_PM

int GPIO_DevResume(void)
{
	if(_pGpioDev->Resume) _pGpioDev->Resume();
	_pGpioDev->is_suspended = 0;
	return 0;
}

int GPIO_DevSuspend(void)
{
	if(_pGpioDev->Suspend) _pGpioDev->Suspend();
	_pGpioDev->is_suspended = 1;
	return 0;
}

int GPIO_DevBeforeSuspend(void)
{
	if(_pGpioDev->BeforeSuspend) _pGpioDev->BeforeSuspend();
	return 0;
}
#endif


int GPIO_DevSetPinMux(UINT32 port, BOOLEAN enable)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->SetPinMux(port, enable);
		_pGpioDev->isGpio[port] = enable;
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}
EXPORT_SYMBOL (GPIO_DevSetPinMux);

int GPIO_DevGetPinMux(UINT32 port, BOOLEAN *enable)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->GetPinMux(port, enable);
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevSetValue(UINT32 port, LX_GPIO_VALUE_T value)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->SetValue(port, value);
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}
EXPORT_SYMBOL (GPIO_DevSetValue);


int GPIO_DevSetIntrArrayNum(UINT32 intrArrayNum)
{
	int rc = -1, ret = 1;

		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->SetIntrArrayNum(intrArrayNum);
		GPIO_UNLOCK(_pGpioDev,ret);

	return rc;
}

int GPIO_DevGetValue(UINT32 port, LX_GPIO_VALUE_T *value)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->GetValue(port, value);
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}


int GPIO_DevSetMode(UINT32 port, LX_GPIO_MODE_T mode)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->SetMode(port, mode);
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}
EXPORT_SYMBOL (GPIO_DevSetMode);

int GPIO_DevGetMode(UINT32 port, LX_GPIO_MODE_T *mode)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->GetMode(port, mode);
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevSetISR(UINT32 port, void (*pfnGPIO_CB)	(UINT32 ), UINT32 enable, LX_GPIO_INFO_T * info)
//int GPIO_DevSetISR(UINT32 port, GPIO_INTR_CALLBACK_T )
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		if(enable == CALLBACK_ENABLE )
			_pGpioDev->useIntr[port] = 1;
		else
			_pGpioDev->useIntr[port] = 0;
		rc = _pGpioDev->SetIntrAction(port, pfnGPIO_CB, enable, info);
		GPIO_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevGetIntrValue(UINT32 *port, LX_GPIO_VALUE_T *value)
{
	int rc = -1, ret = 1;

	//if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->GetIntrValue(port, value);
		GPIO_UNLOCK(_pGpioDev,ret);
	}

	return rc;
}


int GPIO_DevGetIntrCntDur(UINT32 port, UINT32 count, UINT32 *usec)
{
	int rc = -1;
	LX_GPIO_INFO_T gpioInfo;


	if(_pGpioDev->is_suspended)
	{
		GPIO_DEBUG("%s skipped in suspend\n",__func__);
		return rc;
	}

	if(port < _pGpioDev->max_num)
	{
		// 0. intialize
		gpio_isr_info[port].dur = 0;
		gpio_isr_info[port].measured = 0;
		gpio_isr_info[port].intr_count  = count + DISCARD_SAMPLE_NUMBER  + EXTRA_SAMPLE_FOR_COUNT;
		gpio_isr_info[port].start_count = gpio_isr_info[port].intr_count - DISCARD_SAMPLE_NUMBER;

		// 1. enable count_enable interrupt
		_pGpioDev->SetIntrAction(port, NULL, COUNT_ENABLE, &gpioInfo);

		// 2. wait until interrupt to take place and the condtion satisfied or
		// wait upto 5sec(to overcome in situation where interrupt never happens)
		//  wait_event_interruptible_timeout(*(gGPIOPollWaitQueueT[port/GPIO_NUM_IN_INT_ARRAY]), (gpio_isr_info[port].count_enable == 0), (5 * HZ));
		wait_event_interruptible_timeout(gGPIOIntrDurWaitQueue, (gpio_isr_info[port].count_enable == 0), (5 * HZ));

		if(gpio_isr_info[port].count_enable != 0) // for timeout  case
		{
			int cktime = (int)(ktime_to_us(ktime_get()));
			gpio_isr_info[port].dur = (int)( cktime - (int)gpio_isr_info[port].start );

			if( gpio_isr_info[port].start_count > gpio_isr_info[port].intr_count)
			{
				GPIO_DEBUG("Timeout:  samples number expected:[%d], but  less intr occur[%d] taken[%u]us\n", count, gpio_isr_info[port].start_count - gpio_isr_info[port].intr_count,gpio_isr_info[port].dur);
			}
			//*usec  = gpio_isr_info[port].dur;
			*usec  = 0;	// inform timeout using usec == 0
			rc = 0;
			// interrupt disable even at timeoutcase
			_pGpioDev->SetIntrAction(port, NULL, COUNT_DISABLE, &gpioInfo);

			GPIO_DEBUG("IntrCntDur timeout\n");
			}
		else
		{
			// 3. grab time and return
			*usec  = gpio_isr_info[port].dur;
			_pGpioDev->SetIntrAction(port, NULL, COUNT_DISABLE, &gpioInfo);
		}

		// 4. display erorr msg if triggered
		if (*usec <= 0)
		       GPIO_DEBUG("counter[%d] or/and duration value(%u)us is/are not correct\n",count,*usec);

		GPIO_DEBUG("samples number expected:[%d], time taken:[%u]us\n", count, *usec);

		rc = 0;
	}
	else
	{
		GPIO_ERROR("GPIO_DevGetIntCntDur: Invalid pin number(%d)\n",port);
	}

	return rc;
}


/*****************************************
 * ACCESS GPIOs in LG115xAN(ACE)         *
 *****************************************/
static int _GPIO_ExSetPinMux(UINT32 port, BOOLEAN enable)
{
	// do nothing
	return 0;
}

static int _GPIO_ExGetPinMux(UINT32 port, BOOLEAN *enable)
{
	*enable = 1;
	return 0;
}

typedef struct GPIO_USB_VBUS_CTL_SUSPEND
{
	UINT32		port;
	UINT32		val;
} GPIO_USB_VBUS_CTL_SUSPEND_T;

#ifdef INCLUDE_O26_CHIP_KDRV
static int _GPIO_ExGetValue_O26Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
    GPIO_CORE_DEBUG("_GPIO_ExGetValue_O26Ax. port:%d\n", port);

    return 0;
}

static int _GPIO_ExSetValue_O26Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
    GPIO_CORE_DEBUG("_GPIO_ExSetValue_O26Ax. port:%d, value:%d\n", port, value);

    return 0;
}

static int _GPIO_ExSetMode_O26Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

    GPIO_CORE_DEBUG("_GPIO_ExSetMode_O26Ax. port:%d, mode:%d\n", port, mode);
    return 0;
}

static int _GPIO_ExGetMode_O26Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
    GPIO_CORE_DEBUG("_GPIO_ExGetMode_O26Ax. port:%d\n", port);
    return 0;
}


#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_O26(void)
{
    int i;

    if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
    {
        return 0;
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        GPIONDATA(i) = _pGpioDev->pmdata[i].data;
    }
    return 0;
}

static int _GPIO_Suspend_O26(void)
{
    int i;

    if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
    {
        return 0;
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        _pGpioDev->pmdata[i].direction = GPIONDIR(i);
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        _pGpioDev->pmdata[i].data = GPIONDATA(i);
    }

    for(i = 0; i < _pGpioDev->max_num; i++)
    {
        if(gpio_isr_info[i].count_enable)
             wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
    }

    return 0;
}

static int _GPIO_BeforeSuspend_O26(void)
{
    return 0;
}
#endif //
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
static int _GPIO_ExGetValue_O24Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
    GPIO_CORE_DEBUG("_GPIO_ExGetValue_O24Ax. port:%d\n", port);

    return 0;
}

static int _GPIO_ExSetValue_O24Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
    GPIO_CORE_DEBUG("_GPIO_ExSetValue_O24Ax. port:%d, value:%d\n", port, value);

    return 0;
}

static int _GPIO_ExSetMode_O24Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

    GPIO_CORE_DEBUG("_GPIO_ExSetMode_O24Ax. port:%d, mode:%d\n", port, mode);
    return 0;
}

static int _GPIO_ExGetMode_O24Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
    GPIO_CORE_DEBUG("_GPIO_ExGetMode_O24Ax. port:%d\n", port);
    return 0;
}


#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_O24(void)
{
    int i;

    if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
    {
        return 0;
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        GPIONDATA(i) = _pGpioDev->pmdata[i].data;
    }
    return 0;
}

static int _GPIO_Suspend_O24(void)
{
    int i;

    if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
    {
        return 0;
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        _pGpioDev->pmdata[i].direction = GPIONDIR(i);
    }

    for(i = 0; i < _pGpioDev->max_num/8; i++)
    {
        _pGpioDev->pmdata[i].data = GPIONDATA(i);
    }

    for(i = 0; i < _pGpioDev->max_num; i++)
    {
        if(gpio_isr_info[i].count_enable)
             wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
    }

    return 0;
}

static int _GPIO_BeforeSuspend_O24(void)
{
    return 0;
}
#endif //
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
static int _GPIO_ExGetValue_M23Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_M23Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_M23Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_M23Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_M23Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_M23Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_M23Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_M23Ax. port:%d\n", port);
	return 0;
}


#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_M23(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_M23(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_M23(void)
{
	return 0;
}
#endif //
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
static int _GPIO_ExGetValue_O22Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_O22Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_O22Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_O22Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_O22Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_O22Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_O22Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_O22Ax. port:%d\n", port);
	return 0;
}


#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_O22(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_O22(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_O22(void)
{
	return 0;
}
#endif //
#endif


#ifdef INCLUDE_E60_CHIP_KDRV
static int _GPIO_ExGetValue_E60Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_E60Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_E60Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_E60Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_E60Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_E60Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_E60Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_E60Ax. port:%d\n", port);
	return 0;
}


#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_E60(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_E60(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_E60(void)
{
	return 0;
}
#endif //
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
static int _GPIO_ExGetValue_O20Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_O20Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_O20Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_O20Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_O20Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_O20Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_O20Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_O20Ax. port:%d\n", port);
	return 0;
}

#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_O20(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_O20(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_O20(void)
{
	return 0;
}
#endif //
#endif


#ifdef INCLUDE_M19_CHIP_KDRV
static int _GPIO_ExGetValue_M19Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_M19Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_M19Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_M19Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_M19Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_M19Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_M19Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_M19Ax. port:%d\n", port);
	return 0;
}

#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_M19(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_M19(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_M19(void)
{
	return 0;
}
#endif //
#endif


#ifdef INCLUDE_O18_CHIP_KDRV
static int _GPIO_ExGetValue_O18Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_O18Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_O18Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_O18Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_O18Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_O18Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_O18Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_O18Ax. port:%d\n", port);
	return 0;
}

#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_O18(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_O18(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_O18(void)
{
	return 0;
}
#endif //
#endif


#ifdef INCLUDE_L18_CHIP_KDRV
static int _GPIO_ExGetValue_L18Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_L18Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_L18Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_L18Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_L18Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_L18Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_L18Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_L18Ax. port:%d\n", port);
	return 0;
}

#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_L18(void)
{
	int i;
	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_L18(void)
{
	int i;

		for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_L18(void)
{
	return 0;
}
#endif //
#endif

#ifdef INCLUDE_M17_CHIP_KDRV
static int _GPIO_ExGetValue_M17Cx(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_M17Cx. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_M17Cx(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_M17Cx. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_M17Cx(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_M17Cx. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_M17Cx(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_M17Cx. port:%d\n", port);
	return 0;
}

#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_M17Cx(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_M17Cx(void)
{
	int i;

	if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))
	{
		return 0;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_M17Cx(void)
{
	return 0;
}
#endif //
#endif


#ifdef INCLUDE_M17_CHIP_KDRV
static int _GPIO_ExGetValue_M17Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetValue_M17Ax. port:%d\n", port);

	return 0;
}

static int _GPIO_ExSetValue_M17Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	GPIO_CORE_DEBUG("_GPIO_ExSetValue_M17Ax. port:%d, value:%d\n", port, value);

	return 0;
}

static int _GPIO_ExSetMode_M17Ax(UINT32 port, LX_GPIO_MODE_T mode)
{

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_M17Ax. port:%d, mode:%d\n", port, mode);
	return 0;
}

static int _GPIO_ExGetMode_M17Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	GPIO_CORE_DEBUG("_GPIO_ExGetMode_M17Ax. port:%d\n", port);
	return 0;
}

#ifdef KDRV_CONFIG_PM
static int _GPIO_Resume_M17(void)
{
	int i;
	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
	return 0;
}

static int _GPIO_Suspend_M17(void)
{
	int i;

		for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

	for(i = 0; i < _pGpioDev->max_num; i++)
	{
		if(gpio_isr_info[i].count_enable)
			 wake_up_interruptible_all(&gGPIOIntrDurWaitQueue);
	}

	return 0;
}

static int _GPIO_BeforeSuspend_M17(void)
{
	return 0;
}
#endif //
#endif


int GPIO_DevExSetPinMux(UINT32 port, BOOLEAN enable)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->ExSetPinMux(port, enable);
		GPIO_EX_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevExGetPinMux(UINT32 port, BOOLEAN *enable)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->ExGetPinMux(port, enable);
		GPIO_EX_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevExSetValue(UINT32 port, LX_GPIO_VALUE_T value)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->ExSetValue(port, value);
		GPIO_EX_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevExGetValue(UINT32 port, LX_GPIO_VALUE_T *value)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->ExGetValue(port, value);
		GPIO_EX_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}


int GPIO_DevExSetMode(UINT32 port, LX_GPIO_MODE_T mode)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->ExSetMode(port, mode);
		GPIO_EX_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}

int GPIO_DevExGetMode(UINT32 port, LX_GPIO_MODE_T *mode)
{
	int rc = -1, ret = 1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev,ret);
		rc = _pGpioDev->ExGetMode(port, mode);
		GPIO_EX_UNLOCK(_pGpioDev,ret);
	}
	return rc;
}



int GPIO_DevInit(void)
{
	UINT32 i, num_blocks = 0;
	UINT32 phys_base = 0, addr_gap = 0;

	_pGpioDev = (GPIO_DEV_T*)OS_Malloc(sizeof(GPIO_DEV_T));
	memset(_pGpioDev, 0, sizeof(GPIO_DEV_T));


	GPIO_LOCK_INIT(_pGpioDev);
	GPIO_EX_LOCK_INIT(_pGpioDev);

	if(0)
	{}
#ifdef INCLUDE_O26_CHIP_KDRV
    else if(lx_chip() == LX_CHIP_O26)
    {
        if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
        {
            /* need to be declared in kernel */
            gpiod_add_lookup_table(&gpios_table);
            GPIO_NOTI("gpio table Inited\n");
        }
        else
        {
            gpiod_add_lookup_table(&gpios_table);
            GPIO_NOTI("gpio table inited\n");
        }

        phys_base       = O26_GPIO0_BASE;
        addr_gap        = 0x10000;

        _pGpioDev->max_num  = 144;
        num_blocks = (_pGpioDev->max_num+7)/8;

        _pGpioDev->GetValue         = _GPIO_GetValue;
        _pGpioDev->SetValue         = _GPIO_SetValue;
        _pGpioDev->SetMode          = _GPIO_SetMode;
        _pGpioDev->GetMode          = _GPIO_GetMode;
        _pGpioDev->SetPinMux        = _GPIO_SetPinMux_O26Ax;
        _pGpioDev->GetPinMux        = _GPIO_GetPinMux_O26Ax;
        _pGpioDev->SetIntrAction    = _GPIO_SetIntrAction;
        _pGpioDev->SetIntrArrayNum  = _GPIO_SetIntrArrayNum;
        _pGpioDev->GetIntrValue     = _GPIO_GetIntrValue;
        _pGpioDev->GetIntrCntDur    = GPIO_DevGetIntrCntDur;

        _pGpioDev->max_ex_num       = 16;
        _pGpioDev->ExGetValue       = _GPIO_ExGetValue_O26Ax;
        _pGpioDev->ExSetValue       = _GPIO_ExSetValue_O26Ax;
        _pGpioDev->ExSetMode        = _GPIO_ExSetMode_O26Ax;
        _pGpioDev->ExGetMode        = _GPIO_ExGetMode_O26Ax;
        _pGpioDev->ExSetPinMux      = _GPIO_ExSetPinMux;
        _pGpioDev->ExGetPinMux      = _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
        _pGpioDev->pmdata           = (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
        _pGpioDev->Resume           = _GPIO_Resume_O26;
        _pGpioDev->Suspend          = _GPIO_Suspend_O26;
        _pGpioDev->BeforeSuspend    = _GPIO_BeforeSuspend_O26;
#endif //
    }
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if(lx_chip() == LX_CHIP_O24)
    {
        if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
        {
            /* need to be declared in kernel */
            gpiod_add_lookup_table(&gpios_table);
            GPIO_NOTI("gpio table Inited\n");
        }
        else
        {
            gpiod_add_lookup_table(&gpios_table);
            GPIO_NOTI("gpio table inited\n");
        }

        phys_base       = O24_GPIO0_BASE;
        addr_gap        = 0x10000;

        _pGpioDev->max_num  = 144;
        num_blocks = (_pGpioDev->max_num+7)/8;

        _pGpioDev->GetValue         = _GPIO_GetValue;
        _pGpioDev->SetValue         = _GPIO_SetValue;
        _pGpioDev->SetMode          = _GPIO_SetMode;
        _pGpioDev->GetMode          = _GPIO_GetMode;
        _pGpioDev->SetPinMux        = _GPIO_SetPinMux_O24Ax;
        _pGpioDev->GetPinMux        = _GPIO_GetPinMux_O24Ax;
        _pGpioDev->SetIntrAction    = _GPIO_SetIntrAction;
        _pGpioDev->SetIntrArrayNum  = _GPIO_SetIntrArrayNum;
        _pGpioDev->GetIntrValue     = _GPIO_GetIntrValue;
        _pGpioDev->GetIntrCntDur    = GPIO_DevGetIntrCntDur;

        _pGpioDev->max_ex_num       = 16;
        _pGpioDev->ExGetValue       = _GPIO_ExGetValue_O24Ax;
        _pGpioDev->ExSetValue       = _GPIO_ExSetValue_O24Ax;
        _pGpioDev->ExSetMode        = _GPIO_ExSetMode_O24Ax;
        _pGpioDev->ExGetMode        = _GPIO_ExGetMode_O24Ax;
        _pGpioDev->ExSetPinMux      = _GPIO_ExSetPinMux;
        _pGpioDev->ExGetPinMux      = _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
        _pGpioDev->pmdata           = (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
        _pGpioDev->Resume           = _GPIO_Resume_O24;
        _pGpioDev->Suspend          = _GPIO_Suspend_O24;
        _pGpioDev->BeforeSuspend    = _GPIO_BeforeSuspend_O24;
#endif //
    }
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M23)
	{
		if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
		{
			/* need to be declared in kernel */
			gpiod_add_lookup_table(&gpios_table);
			GPIO_ERROR("gpiotable chip !!!\n");
		}
		else
		{
			gpiod_add_lookup_table(&gpios_table);
			GPIO_ERROR("gpiotable2 chip !!!\n");
		}


		phys_base		= M23_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_M23Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_M23Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_M23Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_M23Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_M23Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_M23Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_M23;
		_pGpioDev->Suspend			= _GPIO_Suspend_M23;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_M23;
#endif //
	}
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O22)
	{
		if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
		{
			/* need to be declared in kernel */
			gpiod_add_lookup_table(&gpios_table);
			GPIO_ERROR("gpiotable chip !!!\n");
		}
		else
		{
			gpiod_add_lookup_table(&gpios_table);
			GPIO_ERROR("gpiotable2 chip !!!\n");
		}


		phys_base		= O22_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_O22Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_O22Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_O22Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_O22Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_O22Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_O22Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_O22;
		_pGpioDev->Suspend			= _GPIO_Suspend_O22;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_O22;
#endif //
	}
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_E60)
	{
		if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
		{
			/* need to be declared in kernel */
			gpiod_add_lookup_table(&gpios_table);
			GPIO_ERROR("gpiotable chip !!!\n");
		}
		else
		{
			gpiod_add_lookup_table(&gpios_table);
			GPIO_ERROR("gpiotable2 chip !!!\n");
		}


		phys_base		= E60_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_E60Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_E60Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_E60Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_E60Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_E60Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_E60Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_E60;
		_pGpioDev->Suspend			= _GPIO_Suspend_E60;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_E60;
#endif //
	}
#endif


#ifdef INCLUDE_O20_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O20)
	{
		if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
		{
			/* need to be declared in kernel */
			gpiod_add_lookup_table(&gpios_table);
		}

		phys_base		= O20_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_O20Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_O20Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_O20Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_O20Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_O20Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_O20Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_O20;
		_pGpioDev->Suspend			= _GPIO_Suspend_O20;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_O20;
#endif //
	}
#endif


#ifdef INCLUDE_M19_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M19)
	{
		if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
		{
			/* need to be declared in kernel */
			gpiod_add_lookup_table(&gpios_table);
		}

		phys_base		= M19_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_M19Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_M19Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_M19Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_M19Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_M19Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_M19Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_M19;
		_pGpioDev->Suspend			= _GPIO_Suspend_M19;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_M19;
#endif //
	}
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O18)
	{
		if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
		{
			/* need to be declared in kernel */
			gpiod_add_lookup_table(&gpios_table);
		}

		phys_base		= O18_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_O18Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_O18Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_O18Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_O18Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_O18Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_O18Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_O18;
		_pGpioDev->Suspend			= _GPIO_Suspend_O18;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_O18;
#endif //
	}
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_L18)
	{

		phys_base		= L18_GPIO0_BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 144;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue 		= _GPIO_GetValue;
		_pGpioDev->SetValue 		= _GPIO_SetValue;
		_pGpioDev->SetMode			= _GPIO_SetMode;
		_pGpioDev->GetMode			= _GPIO_GetMode;
		_pGpioDev->SetPinMux		= _GPIO_SetPinMux_L18Ax;
		_pGpioDev->GetPinMux		= _GPIO_GetPinMux_L18Ax;
		_pGpioDev->SetIntrAction	= _GPIO_SetIntrAction;
		_pGpioDev->SetIntrArrayNum	= _GPIO_SetIntrArrayNum;
		_pGpioDev->GetIntrValue 	= _GPIO_GetIntrValue;
		_pGpioDev->GetIntrCntDur	= GPIO_DevGetIntrCntDur;

		_pGpioDev->max_ex_num		= 16;
		_pGpioDev->ExGetValue		= _GPIO_ExGetValue_L18Ax;
		_pGpioDev->ExSetValue		= _GPIO_ExSetValue_L18Ax;
		_pGpioDev->ExSetMode		= _GPIO_ExSetMode_L18Ax;
		_pGpioDev->ExGetMode		= _GPIO_ExGetMode_L18Ax;
		_pGpioDev->ExSetPinMux		= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux		= _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->pmdata			= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
		_pGpioDev->Resume			= _GPIO_Resume_L18;
		_pGpioDev->Suspend			= _GPIO_Suspend_L18;
		_pGpioDev->BeforeSuspend	= _GPIO_BeforeSuspend_L18;
#endif //
	}
#endif

#ifdef INCLUDE_M17_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M17)
	{
		if(lx_chip_rev() >= LX_CHIP_REV(M17,C0))
		{
			/* M16++ */
			if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
			{
				/* need to be declared in kernel */
				gpiod_add_lookup_table(&gpios_table);
			}

			phys_base 	  = M17_GPIO0_BASE;
			addr_gap		  = 0x10000;

			_pGpioDev->max_num  = 144;
			num_blocks = (_pGpioDev->max_num+7)/8;

			_pGpioDev->GetValue		  = _GPIO_GetValue;
			_pGpioDev->SetValue		  = _GPIO_SetValue;
			_pGpioDev->SetMode		  = _GPIO_SetMode;
			_pGpioDev->GetMode		  = _GPIO_GetMode;
			_pGpioDev->SetPinMux		  = _GPIO_SetPinMux_M17Cx;
			_pGpioDev->GetPinMux		  = _GPIO_GetPinMux_M17Cx;
			_pGpioDev->SetIntrAction	  = _GPIO_SetIntrAction;
			_pGpioDev->SetIntrArrayNum  = _GPIO_SetIntrArrayNum;
			_pGpioDev->GetIntrValue	  = _GPIO_GetIntrValue;
			_pGpioDev->GetIntrCntDur	  = GPIO_DevGetIntrCntDur;

			_pGpioDev->max_ex_num 	  = 16;
			_pGpioDev->ExGetValue 	  = _GPIO_ExGetValue_M17Cx;
			_pGpioDev->ExSetValue 	  = _GPIO_ExSetValue_M17Cx;
			_pGpioDev->ExSetMode		  = _GPIO_ExSetMode_M17Cx;
			_pGpioDev->ExGetMode		  = _GPIO_ExGetMode_M17Cx;
			_pGpioDev->ExSetPinMux	  = _GPIO_ExSetPinMux;
			_pGpioDev->ExGetPinMux	  = _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
			_pGpioDev->pmdata 		  = (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
			_pGpioDev->Resume 		  = _GPIO_Resume_M17Cx;
			_pGpioDev->Suspend		  = _GPIO_Suspend_M17Cx;
			_pGpioDev->BeforeSuspend	  = _GPIO_BeforeSuspend_M17Cx;
#endif //
		}
		else
		{
			/* M16+ */
			if(!(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE))  // GPIO_KERNEL_API
			{
				/* need to be declared in kernel */
				gpiod_add_lookup_table(&gpios_table);
			}

			phys_base 	  = M17_GPIO0_BASE;
			addr_gap		  = 0x10000;

			_pGpioDev->max_num  = 144;
			num_blocks = (_pGpioDev->max_num+7)/8;

			_pGpioDev->GetValue		  = _GPIO_GetValue;
			_pGpioDev->SetValue		  = _GPIO_SetValue;
			_pGpioDev->SetMode		  = _GPIO_SetMode;
			_pGpioDev->GetMode		  = _GPIO_GetMode;
			_pGpioDev->SetPinMux		  = _GPIO_SetPinMux_M17Ax;
			_pGpioDev->GetPinMux		  = _GPIO_GetPinMux_M17Ax;
			_pGpioDev->SetIntrAction	  = _GPIO_SetIntrAction;
			_pGpioDev->SetIntrArrayNum  = _GPIO_SetIntrArrayNum;
			_pGpioDev->GetIntrValue	  = _GPIO_GetIntrValue;
			_pGpioDev->GetIntrCntDur	  = GPIO_DevGetIntrCntDur;

			_pGpioDev->max_ex_num 	  = 16;
			_pGpioDev->ExGetValue 	  = _GPIO_ExGetValue_M17Ax;
			_pGpioDev->ExSetValue 	  = _GPIO_ExSetValue_M17Ax;
			_pGpioDev->ExSetMode		  = _GPIO_ExSetMode_M17Ax;
			_pGpioDev->ExGetMode		  = _GPIO_ExGetMode_M17Ax;
			_pGpioDev->ExSetPinMux	  = _GPIO_ExSetPinMux;
			_pGpioDev->ExGetPinMux	  = _GPIO_ExGetPinMux;
#ifdef KDRV_CONFIG_PM
			_pGpioDev->pmdata 		  = (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T)*_pGpioDev->max_num );
			_pGpioDev->Resume 		  = _GPIO_Resume_M17;
			_pGpioDev->Suspend		  = _GPIO_Suspend_M17;
			_pGpioDev->BeforeSuspend	  = _GPIO_BeforeSuspend_M17;
#endif //
		}
	}
#endif
	else
	{

		GPIO_ERROR("AUD : LX_CHIP_REV => Unknown(0x%X) : ERROR\n", lx_chip_rev());
		GPIO_ERROR("Unsupported chip !!!\n");
		return -1;
	}

	_gpioBaseAddr = (void **)OS_Malloc(num_blocks * sizeof(void *));
	for(i=0; i<num_blocks; i++)
	{
		_gpioBaseAddr[i] = (void *)ioremap(phys_base + i*addr_gap , 0x10000);
		GPIO_PRINT("_gpioBaseAddr[%d]=[%p] phy[%x] \n",i,_gpioBaseAddr[i],phys_base + i*addr_gap );
	}

	return 0;
}



/** @} */


