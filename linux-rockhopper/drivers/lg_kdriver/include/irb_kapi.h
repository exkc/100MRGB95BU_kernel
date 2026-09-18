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
 *  main driver implementation for pm device.
 *	pm device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_pm
 */


#ifndef	_IRB_KAPI_H_
#define	_IRB_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define IRB_CHIP_O20 		(LX_CHIP_REV(O20, A0) & 0xFFFFFF00)

#define IRB_IOC_MAGIC               'r'

#define IRB_INIT                _IO(IRB_IOC_MAGIC, 0)



/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/



typedef struct irb_waveforms_kdrv
{
	int numToggleIndex;
	int dutyCycle;
	int carrierFrequency;
	int numCharTimes;
	//int *characteristicTime;
	union
	{
		//unsigned short	*chartime;
		UINT8 *		chartime;
		UINT32		chartime_compat;
		UINT64		chartime_sizer;
	};
	int numMakeTimes;
	//int *makeTimes;
	union
	{
		//unsigned short	*maketime;
		UINT8 *		maketime;
		UINT32		maketime_compat;
		UINT64		maketime_sizer;
	};

	int numReapeatTimes;
	//int *repeatTimes;
	union
	{
		//unsigned short	*reptime;
		UINT8 *		reptime;
		UINT32		reptime_compat;
		UINT64		reptime_sizer;
	};

	int numBreakTimes;
	//int *breakTimes;
	union
	{
		//unsigned short	*brtime;
		UINT8 *		brtime;
		UINT32		brtime_compat;
		UINT64		brtime_sizer;
	};

}LX_IRB_PARAM_T;

#define IRB_IOW_COMMAND_SET		_IOW(IRB_IOC_MAGIC,	10, LX_IRB_PARAM_T)
//#define IRB_IORW_COMMAND_GET		_IOWR(IRB_IOC_MAGIC,	11, LX_IRB_PARAM_T)

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _IRB_DRV_H_ */

/** @} */
