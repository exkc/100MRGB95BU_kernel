/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  hw configuration file for lgbus device
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2013.07.04
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus
 *	@{
 */

#ifndef	_LGBUS_HW_H_
#define	_LGBUS_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "lgbus_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define __MHZ				1000000
#define __100KHZ			100000
#define __10KHZ				10000

#define	DDR_NUM_MAX			3
#define	RW_NUM_MAX			2
#define	PORT_NUM_MAX		4

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define LGBUS_RdFL(addr)            ( *( volatile UINT32 * )( addr ))
#define LGBUS_WrFL(addr,value)      ( *( volatile UINT32 * )( addr )) = ( UINT32 )( value )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char	label[16];

	struct
	{
		UINT32	org[DDR_NUM_MAX][RW_NUM_MAX];	// original data LM:org[0], GM:org[1], EM:org[2]
		UINT32	dmy[DDR_NUM_MAX][RW_NUM_MAX];	// dummy data
	}
	bw;
}
LGBUS_PMT_ITEM_DESC_T;

typedef union
{
	UINT32	gen[4];
}
LGBUS_HW_DATA_T;

typedef enum
{
	LGBUS_HW_CMD_TIMER_INIT		= 0,
	LGBUS_HW_CMD_PQE_PERF_INIT,

	LGBUS_HW_CMD_INTR_ENABLE,
	LGBUS_HW_CMD_INTR_DISABLE,
	LGBUS_HW_CMD_INTR_HANDLER,
}
LGBUS_HW_CMD_ID_T;

typedef enum
{
	LGBUS_HW_PROC_ID_SYS_INFO,
	LGBUS_HW_PROC_ID_BW_INFO,
}
LGBUS_HW_PROC_ID_T;

typedef struct
{
#define QOS_IDX_LBUS		0
#define QOS_IDX_GBUS		1
#define QOS_IDX_CPU			2
#define QOS_IDX_CCI			2
#define	QOS_IDX_MAX			3
	UINT32	bus_reg_base[QOS_IDX_MAX];
	UINT32	freq[QOS_IDX_MAX];

	UINT32	rf_timer_init;
	UINT32	irq_num;

	UINT32	ddr_num;				// maximum number of valid bus
	UINT32	ip_num;					// maximum number of ip /w port
	UINT32	port_num;				// maximum number of port per each BUS

	UINT32	max_bw[DDR_NUM_MAX];	// maximum BW of each DDR (MB/s)
	const LGBUS_PMT_ITEM_DESC_T* pmt_desc;
}
LGBUS_HW_CFG_T;

typedef enum
{
	LGBUS_HW_OPT_PMT_BW_ORG		= 0x00000001, // show original packet info
	LGBUS_HW_OPT_PMT_BW_DUMMY	= 0x00000002, // show dummy packet info
	LGBUS_HW_OPT_PMT_SYNC		= 0x00000004, // wait PMT interrupt
}
LGBUS_HW_OPT_T;

typedef struct
{
	int 	(*do_config)(LGBUS_HW_CFG_T* cfg);
	int 	(*do_init)(void);
	int		(*do_cleanup)(void);

	int 	(*do_open)(void);
	int 	(*do_close)(void);

	int 	(*do_resume)(void);
	int 	(*do_suspend)(void);

	int		(*do_hwcmd)(LGBUS_HW_CMD_ID_T cmdId, LGBUS_HW_DATA_T* data);

	void 	(*do_proc)(LGBUS_HW_PROC_ID_T id, struct seq_file* m, LGBUS_HW_DATA_T* data);
}
LGBUS_HW_FUNC_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
LGBUS_HW_FUNC_T* LGBUS_M17_Init(void);
LGBUS_HW_FUNC_T* LGBUS_L18_Init(void);
LGBUS_HW_FUNC_T* LGBUS_O18_Init(void);
LGBUS_HW_FUNC_T* LGBUS_M19_Init(void);
LGBUS_HW_FUNC_T* LGBUS_O20_Init(void);
LGBUS_HW_FUNC_T* LGBUS_E60_Init(void);
LGBUS_HW_FUNC_T* LGBUS_O22_Init(void);
LGBUS_HW_FUNC_T* LGBUS_M23_Init(void);
LGBUS_HW_FUNC_T* LGBUS_O24_Init(void);
LGBUS_HW_FUNC_T* LGBUS_O26_Init(void);

int		LGBUS_HW_Init(void);
void	LGBUS_HW_Cleanup(void);
int		LGBUS_HW_Open(void);
int		LGBUS_HW_Close(void);
int		LGBUS_HW_Resume(void);
int		LGBUS_HW_Suspend(void);

LGBUS_HW_OPT_T LGBUS_HW_GetOption(void);
void	LGBUS_HW_SetOption(LGBUS_HW_OPT_T opts);

void	LGBUS_HW_PrintPMTInfo(struct seq_file *m);
void	LGBUS_HW_PrintStatus (struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _LGBUS_HW_H_ */

/** @} */

