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


#ifndef	_SWCEC_KAPI_H_
#define	_SWCEC_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define SWCEC_CHIP_H15 		(LX_CHIP_REV(H15, A0) & 0xFFFFFF00)
#define SWCEC_CHIP_M16 		(LX_CHIP_REV(M16, A0) & 0xFFFFFF00)
#define SWCEC_CHIP_M16P 	(LX_CHIP_REV(M16P, A0) & 0xFFFFFF00)	// 추후 지울것
#define SWCEC_CHIP_M17 		(LX_CHIP_REV(M17, A0) & 0xFFFFFF00)

#define SWCEC_IOC_MAGIC		's'
#define SWCEC_IOC_MAXNR		20

typedef enum
{
	LX_SWCEC_COMMAND_TX,
	LX_SWCEC_COMMAND_TX_FORCE,		
	LX_SWCEC_COMMAND_TX_LAST_NOACK,	
	LX_SWCEC_COMMAND_CEC_WR_USING_FILE,		
	LX_SWCEC_COMMAND_DATAINIT,				
} LX_SWCEC_COMMAND_T;


typedef struct
{
	UINT32	gpio;
	UINT32	clk_idx;	
	UINT32	high[100];
	UINT32	low[100];
} LX_SWCEC_CEC_INFO_T;

typedef struct
{
	UINT32	gpio;
} LX_SWCEC_INFO_T;

typedef struct
{	
	UINT32	command;
	UINT32	gpiopin;
	UINT32	bufSize;	
	UINT8	*buf;	
	LX_SWCEC_CEC_INFO_T	cecinfo;
} LX_SWCEC_PARAM_T;

#define SWCEC_IOW_COMMAND_SET		_IOW(SWCEC_IOC_MAGIC,	0, LX_SWCEC_PARAM_T)
#define SWCEC_IORW_COMMAND_GET		_IOWR(SWCEC_IOC_MAGIC,	1, LX_SWCEC_PARAM_T)


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

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

#endif /* _SWCEC_DRV_H_ */

/** @} */
