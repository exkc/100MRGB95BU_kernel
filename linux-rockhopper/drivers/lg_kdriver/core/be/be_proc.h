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
 *  proc file for BE device
 *
 *  author      dj911.kim
 *  version     1.0
 *  date        2015.05.28
 *  note        Additional information.
 *
 *  @addtogroup BE
 *  @{
 */

#ifndef	_BE_PROC_H_
#define	_BE_PROC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/seq_file.h>

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
typedef enum
{
    BE_FRC_PROC_ID_DETAIL_INFO,
}
BE_FRC_PROC_ID_T;

typedef enum
{
	BE_FWI_PROC_ID_DETAIL_INFO,
}
BE_FWI_PROC_ID_T;

typedef enum
{
	BE_PWM_PROC_ID_DETAIL_INFO,
	BE_PWM_PROC_ID_SIMPLE_INFO,
}
BE_PWM_PROC_ID_T;

typedef enum
{
	BE_LED_PROC_ID_DETAIL_INFO,
}
BE_LED_PROC_ID_T;

typedef enum
{
	BE_TOP_PROC_ID_DETAIL_INFO,
	BE_TOP_PROC_ID_ORBIT_INFO,
	BE_TOP_PROC_ID_LSR_INFO,
	BE_TOP_PROC_ID_GSR_INFO,
	BE_TOP_PROC_ID_OSDLVL_INFO,
	BE_TOP_PROC_ID_CPC_INFO,
}
BE_TOP_PROC_ID_T;

typedef enum
{
	BE_H3D_PROC_ID_DETAIL_INFO,
}
BE_H3D_PROC_ID_T;

#define BE_PQ_RPT_PCCE__STR_MAX  (64)   // mhlee, pcce msg max size
typedef struct
{
	// unsigned int    ui;
	// unsigned int    en;
	// unsigned int    status;
	char            str[BE_PQ_RPT_PCCE__STR_MAX];
} BE_PQ_RPT_PCCE_T;      // mhlee, pcce msg from fw

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

