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


#ifndef	_PM_KAPI_H_
#define	_PM_KAPI_H_

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
#define PM_CHIP_M16P 		(LX_CHIP_REV(M16P, A0) & 0xFFFFFF00)	// 추후 지울것
#define PM_CHIP_M17 		(LX_CHIP_REV(M17, A0) & 0xFFFFFF00)

#define PM_IOC_MAGIC               'g'

#define PMINFO_HEADER						0x504d4657
#define PMINFO_VERSION_1					1

#define PMINFO_SIZE							0x4000
#define PMINFO_OFFSET						(0x40000 - PMINFO_SIZE)

#define PM_CM3_RECOVERY
#define PMS_PARTITION_FW_SIZE	0x10000		// 64KB
#define PMS_HEADER_SIZE			0x200
#define PMS_FW_SHADOW_MAGIC_1 	0x706d6677
#define PMS_FW_SHADOW_MAGIC_2 	0x73686472

#define PMS_CMD_CPU_FREQ					1
#define PMS_CMD_CPU_VOL						2
#define PMS_CMD_GPU_FREQ					4
#define PMS_CMD_GPU_VOL						5
#define PMS_CMD_CHECK_INIT					6
#define PMS_CMD_CPU_AVS						7
#define PMS_CMD_CORE_AVS					8
#define PMS_CMD_CORE_VOL					9
#define PMS_CMD_CORE_SWITCHING_FREQ			10


#define PMS_OFF								0
#define PMS_ON								1

#define	TEST_FULL							0x0
#define	TEST_DVFS							0x1
#define	TEST_HOTPLUG						0x2
#define	TEST_FIXED							0x3

#define	PM_THERMAL_LOG_OFF			0x0
#define	PM_THERMAL_LOG_ON			0x1
#define	IPC_PACKET_BASE (0xF7083E00)  /* Limit ~0x2000_3FFF 256 bytes CA15:0xF7083E00~ */
#define	IPC_PACKET_SIZE (4*8)       /* 4Byte unit */
#define 	IPC_STATUS_BASE         ((IPC_PACKET_BASE) + (IPC_PACKET_SIZE)*(7) )    /* 0x20003EE0 */
#define	IPC_TS_BASE            ((IPC_STATUS_BASE) + (0x1C))    /* offset: 0x1c */
#define	IPC_TS_VAL(NUM)        (*( int *) (IPC_TS_BASE + 4*NUM)) /* NUM: 0~3  range : -40 ~ +125 Celcius */
#define	IPC_TS_ADDR(NUM)        ( (IPC_TS_BASE) + 4*(NUM)) /* NUM: 0~3  range : -40 ~ +125 Celcius */
#define	TS_CELCIUS_MAX		(125)
#define	TS_CELCIUS_MIN		(-40)
#define	TS_NUM	3
#define	TS_HISTORY_NUM		10	/* should be even number */

#define	STATUS_TEMPERATURE_STABLE			0
#define	STATUS_TEMPERATURE_INCREASING		1
#define	STATUS_TEMPERATURE_DECREASING		2
#define	STATUS_TEMPERATURE_LOW_WARNING		3
#define	STATUS_TEMPERATURE_HIGH_WARNING		4
#define	STATUS_TEMPERATURE_LOW_CRITICAL		5
#define	STATUS_TEMPERATURE_HIGH_CRITICAL		6

#define	TEMPERATURE_LOW_WARNING		(0)
#define	TEMPERATURE_HIGH_WARNING		(100)
#define	TEMPERATURE_LOW_CRITICAL		(-10)
#define	TEMPERATURE_HIGH_CRITICAL		(120)





/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	unsigned int	module;
	unsigned int 	sub;
	unsigned int 	state;
}LX_PM_CLOCKGATING_T;

typedef struct
{
	unsigned int	cpu_freq;
	unsigned int 	cpu_vol;
	unsigned int 	cpu_on;
	unsigned int 	core_vol;
	unsigned int 	core_switching_freq;
	unsigned int 	gpu_freq;
	unsigned int 	gpu_vol;
	unsigned int 	gpu_on;
	unsigned int 	sel;	// 0: no change,  1:cpu freq change, 2:cpu vol change, 4:gpu freq change, 5:gpu vol change,
	unsigned int 	thernal_0;
	unsigned int 	thernal_1;
	unsigned int 	thernal_2;
	unsigned int 	pm_inited;
	unsigned int 	cpu_avs;
	unsigned int 	core_avs;
}LX_PM_STATUS_T;

typedef struct
{
	unsigned int	interval; // autodown interval
	unsigned int 	testmode; // 0 : notest, 1: cpu, 2:gpu
}LX_PM_TEST_FACTOR_T;


typedef struct
{
	unsigned char *	src;
	unsigned int	fwsize;
}LX_PM_CM3_INFO_T;

#define PM_IOCTL_MAGIC	177
#define PM_IORW_INIT    _IOWR(PM_IOCTL_MAGIC,   50, LX_PM_STATUS_T)
#define PM_IOW_COMMAND_SET     _IOW(PM_IOCTL_MAGIC,    51, LX_PM_STATUS_T)
#define PM_IORW_COMMAND_GET    _IOWR(PM_IOCTL_MAGIC,   52, LX_PM_STATUS_T)

#define PM_CLK_ON	0
#define PM_CLK_OFF	1

#define PM_NULL		0
#define PM_SUB_ALL	0xFFFFFFFF
#define PM_SUB_MAX	5

typedef  enum
{
	PM_VENC = 1,
 	PM_VDEC = 2,
	PM_VIP =3,
	PM_MAX = 3,
} CLOCK_GATING_MODULE;

typedef  enum
{
	PM_VENC_0 = 0x1,
	PM_VENC_1 = 0x2,
	PM_VENC_MAX = 2,
} CLOCK_GATING_VENC_SUB;

typedef  enum
{
	PM_VDEC0_G1   = 0x1,
	PM_VDEC0_G2   = 0x2,
	PM_VDEC1_HEVC = 0x4,
	PM_VDEC1_G1   = 0x8,
	PM_VDEC2_HEVC = 0x10,
	PM_VDEC2_G1   = 0x20,
	PM_VDEC0_HEVC = 0x40,
	PM_VDEC_MAX   = 7,
} CLOCK_GATING_VDEC_SUB;

typedef  enum
{
	PM_VIP_0 = 0x1,
	PM_VIP_MAX = 1
} CLOCK_GATING_VIP_SUB;

#define	PM_DEV_MAJOR     	177

#define	PM_CPU_GOV_WORK			1
#define	PM_GET_CPU_GOV_STATUS	2
#define	PM_GET_STATUS			3
#define	PM_SET_STATUS			4
#define	PM_GET_CLOCK_GATING		5
#define	PM_SET_CLOCK_GATING		6
#define	PM_GET_TEST_FACTOR		7
#define	PM_SET_TEST_FACTOR		8
#define	PM_GET_LOAD_HISTORY		9
#define	PM_GO_TEST				10
#define	PM_STOP_TEST			11
#define	PM_UART_TO_CM3			12
#define	PM_GET_DEBUG_PRINT		13
#define	PM_SET_DEBUG_PRINT		14
#define	PM_GET_SAMPLING_RATE	15
#define	PM_SET_SAMPLING_RATE	16
#define	PM_RECOVERY_CM3			17
#define	PM_SET_CM3_STOP			18
#define	PM_SET_CM3_START		19
#define	PM_STORE_CM3_FW			20
#define	PM_RECOVERY_CM3_TEST	21
#define	PM_GET_TARGET_FREQ		22
#define	PM_GET_TARGET_VOL		23
#define	PM_GET_TEST_MODE		24
#define	PM_CHECK_INIT			25
#define	PM_GET_TARGET_COREVOL	26



#define	TEST_OFF			0
#define	CPU_VOL_DOWN		1
#define	GPU_VOL_DOWN		2
#define	CPU_FREQ_UP			3
#define	GPU_FREQ_UP			4
#define	CPU_FULL_RANDOM		5
#define	CPU_HOTPLUG_STRESS	6
#define	CPU_DVFS_RANDOM		7
#define	CPU_FREQ_RANDOM		8
#define	CPU_VOL_RANDOM		9
#define	GPU_DVFS_RANDOM		10
#define	GPU_FREQ_RANDOM		11
#define	GPU_VOL_RANDOM		12
#define	CPU_GPU_FULL_RANDOM	13
#define	TS_MON				19

// M17
#define M16_CPU_FREQ_ND		1008	// 추후 지울것
#define M16_CPU_FREQ_UD		600		// 추후 지울것

#define M17_CPU_FREQ_ND		1008
#define M17_CPU_FREQ_UD		600

#define O18_CPU_FREQ_ND		1008
#define O18_CPU_FREQ_UD		600

#define O18_CPU_VOL_ND		940
#define O18_CPU_VOL_UD		800

#define M19_CPU_FREQ_ND		1008
#define M19_CPU_FREQ_UD		600

#define O20_CPU_FREQ_ND		1008
#define O20_CPU_FREQ_UD		600


#define E60_CPU_FREQ_ND		1008
#define E60_CPU_FREQ_UD		600

typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_M16P_LOADINFO_T;			// 추후 지울것

typedef struct
{
	volatile unsigned int	count;
	LX_PM_M16P_LOADINFO_T	history[50];

}LX_PM_M16P_LOAD_HISTORY_T;	// 추후 지울것

typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_M17_LOADINFO_T;

typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_O18_LOADINFO_T;


typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_M19_LOADINFO_T;

typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_O20_LOADINFO_T;

typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_E60_LOADINFO_T;

typedef struct
{
	volatile unsigned int	timestamp;
	volatile unsigned int	freq;
	volatile unsigned int	cpu0;
	volatile unsigned int	cpu1;
	volatile unsigned int	cpu2;
	volatile unsigned int	cpu3;
	volatile unsigned int	max;
	volatile unsigned int	avg;
	volatile unsigned int	core_number;
	volatile unsigned int	ud_per;
	volatile unsigned int	nd_per;
}LX_PM_O22_LOADINFO_T;

typedef struct
{
	volatile unsigned int	count;
	LX_PM_M17_LOADINFO_T	history[50];

}LX_PM_M17_LOAD_HISTORY_T;

typedef struct
{
	volatile unsigned int	count;
	LX_PM_M19_LOADINFO_T	history[50];

}LX_PM_M19_LOAD_HISTORY_T;

typedef struct
{
	volatile unsigned int	count;
	LX_PM_O18_LOADINFO_T	history[50];
}LX_PM_O18_LOAD_HISTORY_T;

typedef struct
{
	volatile unsigned int	count;
	LX_PM_O20_LOADINFO_T	history[50];
}LX_PM_O20_LOAD_HISTORY_T;

typedef struct
{
	volatile unsigned int	count;
	LX_PM_E60_LOADINFO_T	history[50];
}LX_PM_E60_LOAD_HISTORY_T;
typedef struct
{
	volatile unsigned int	count;
	LX_PM_O22_LOADINFO_T	history[50];
}LX_PM_O22_LOAD_HISTORY_T;
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PM_DRV_H_ */

/** @} */
