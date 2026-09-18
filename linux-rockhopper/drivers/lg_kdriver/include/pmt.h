/*
	SystemIC Center, LG Electronics
    COPYRIGHT(c) LGE CO.,LTD. 2020. SEOUL, KOREA.\n
    All rights are reserved.\n
    No part of this work covered by the copyright hereon may be
    reproduced, stored in a retrieval system, in any form or
    by any means, electronic, mechanical, photocopying, recording
    or otherwise, without the prior permission of LG Electronics.
    
	@code
    ASD Group, SystemIC Center, LG Electronics
    @endcode

    @file	pmt.h
    @author	hyunsoo0802.lim@lg.com
    @date	2020/01/01
    @brief  BUS Performance MoniToring header
*/


#ifndef _PERF_MON_TARGET_H_
#define _PERF_MON_TARGET_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	USE_BASE_TYPES_H

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif

#ifdef USE_BASE_TYPES_H
#include "base_types.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	PMT_MODULE_NAME			"perfmon"
#define	PMT_MAJOR_NUM			1261
#define	PMT_DEV_NAME			"/dev/perfmon"

#define MAXBUFSIZE			1460
#define MHz						1000000

#define CLIENT_MAX			2

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef TRUE
#define TRUE					1
#endif

#ifndef FALSE
#define FALSE					0
#endif

#ifndef RET_OK
#define RET_OK					0
#endif

#ifndef RET_ERROR
#define RET_ERROR				-1
#endif

#ifndef __F__
#define __F__					__FUNCTION__
#endif
#ifndef __L__
#define __L__					__LINE__
#endif
#ifndef __FL__
#define __FL__					__FILE__
#endif

/** simple form of aligned(v) attribute. __aligned(x) is defined at kernel/incldue/linux/compiler-gcc.h */
#ifdef  __aligned
#undef  __aligned
#endif

#define __aligned(x)            __attribute__((aligned(x)))


#ifndef __CHECK_IF_ERROR
#define __CHECK_IF_ERROR(__checker,__if_output,__if_action,fmt,args...) \
{ \
	if (unlikely(__checker)) { \
		__if_output(fmt,##args); \
		__if_action; \
	} \
}
#endif

#define PMT_REG_RD(addr)		(*(volatile UINT32*)(addr))
#define PMT_REG_WR(addr,value)	(*(volatile UINT32*)(addr)) = (UINT32)(value)

#define COLOR_RED		"\x1b[1;31m"
#define COLOR_BLUE      "\x1b[1;34m"
#define COLOR_NONE		"\x1b[0m"

#ifndef BOOLEAN
typedef unsigned char			BOOLEAN;
#endif
#ifndef UINT8
typedef unsigned char			UINT8;
#endif
#ifndef UINT16
typedef unsigned short			UINT16;
#endif
#ifndef UINT32
typedef unsigned int			UINT32;
#endif
#ifndef ULONG
typedef unsigned long			ULONG;
#endif
#ifndef UINT64
typedef unsigned long long		UINT64;
#endif

#define STX				0xFD
#define ETX				0xFE

#define PKT_RECV_CONTINUE		0
#define PKT_RECV_COMPLETE		1

#define PKT_RECV_ERR_STX		-1
#define PKT_RECV_ERR_PSIZE		-2
#define PKT_RECV_ERR_CHKSUM		-3
#define PKT_RECV_ERR_ETX		-4


#define	PMT_IOC_MAGIC				'p'
#define IOCTL_PMT_INIT_CONFIG		_IOW(PMT_IOC_MAGIC, 0, REG_MULTIPLE_T)
#define IOCTL_PMT_CHIP_ID			_IOWR(PMT_IOC_MAGIC, 1, UINT32)
#define IOCTL_PMT_INIT_TBL			_IOW(PMT_IOC_MAGIC, 2, REG_MULTIPLE_T)
#define IOCTL_PMT_READ				_IOR(PMT_IOC_MAGIC, 6, UINT64)			// change U32 to U64 to hold pointer to array in both aarch32 and aarch64
#define IOCTL_PMT_READ_REG			_IOR(PMT_IOC_MAGIC, 7, UINT64)			// change U32 to U64 to hold pointer to array in both aarch32 and aarch64
#define IOCTL_PMT_WRITE_REG			_IOW(PMT_IOC_MAGIC, 8, REG_MULTIPLE_T)
#define IOCTL_PMT_FAST_START		_IOW(PMT_IOC_MAGIC, 9, REG_MULTIPLE_T)
#define IOCTL_PMT_FAST_STOP			_IOW(PMT_IOC_MAGIC, 10, REG_MULTIPLE_T)
#define IOCTL_PMT_DEBUG_PRINT	   	_IOW(PMT_IOC_MAGIC, 16, UINT32)
#define IOCTL_PMT_START			   	_IO(PMT_IOC_MAGIC, 17)
#define IOCTL_PMT_STOP				_IO(PMT_IOC_MAGIC, 18)
#define IOCTL_PMT_END		    	_IO(PMT_IOC_MAGIC, 19)
#define IOCTL_PMT_EXIT			   	_IO(PMT_IOC_MAGIC, 20)

typedef struct
{
	UINT32			xxx;		// dummy
	UINT32			nValue;
	volatile void** value; 		// array to hold ioremapped register list (pointer to volatile void*)
}
REG_LIST_T;

typedef struct
{
	UINT32 cmd;
	UINT32 nValue;
	union
	{
		UINT32*	value;			// 32bit array to hold register list or register value
		UINT32	compat_Data;
		UINT64	sizer;			// 64bit sizer for aarch64 kernel
	};
}
REG_MULTIPLE_T;

typedef struct {
	void (*init_config)(UINT32 *data);
	void (*init_tbl)(REG_LIST_T* addr_tbl, REG_MULTIPLE_T* value_tbl, REG_MULTIPLE_T* addr, UINT32 nValue);
	void (*read)(REG_LIST_T* addr, REG_MULTIPLE_T* value);
	void (*write_reg)(UINT32 *data, UINT32 nValue);
	void (*start)(void);
	void (*stop)(void);
	void (*end)(void);
}
pmt_ops_t;

typedef enum
{
	LBUS_IDX,
	GBUS_IDX,
	EBUS_IDX,
	BUS_MAX_IDX
}
BUS_IDX_E;

typedef enum
{
	FPGA_IDX,
	ASIC_IDX
}
CHIP_MODE_IDX_E;



typedef enum
{
	SZ_STX = 		1,
	SZ_PSIZE = 		2,
	SZ_CMD = 		1,
	SZ_HEADER =     SZ_STX + SZ_PSIZE + SZ_CMD,
	SZ_CHKSUM = 	1,
	SZ_ETX = 		1,
	SZ_TAIL =		SZ_CHKSUM + SZ_ETX,
	SZ_METADATA =	SZ_HEADER + SZ_TAIL
}
PACKET_SIZEBYTE_T;

typedef enum
{
	IDX_STX = 0,
	IDX_PSIZE = SZ_STX,
	IDX_CMD = SZ_STX + SZ_PSIZE,
	IDX_PAYLOAD = SZ_STX + SZ_PSIZE + SZ_CMD
}
PACKET_IDX_E;

typedef struct
{
	UINT8	Stx;
	UINT16	Psize;
	UINT8	Cmd;
	UINT32*	Data;
	UINT32	Addr;
	UINT8	ChkSum;
	UINT8	Etx;
	UINT32 	DataSize;
	UINT32	nData;
}
PACKET_RECV_INFO_T;

typedef enum
{
	CMD_START =     		0x00,
	CMD_STOP =      		0x01,
	CMD_INIT_CONFIG = 		0x02,
	CMD_INIT_ADDR =			0x03,
	CMD_INIT_POST =			0x04,
	CMD_END =	    		0x0F,
	CMD_READ =	  	 		0x10,
	CMD_READ_REG =	   		0x11,
	CMD_WRITE_REG =	   		0x12,
	CMD_WRITE_ONLY =	  	0x13,
	CMD_VSYNC_START =		0x20,
	CMD_VSYNC_DATA =		0x21,
	CMD_VSYNC_END =			0x22,
	CMD_PQE_FRAME =			0x23,
	CMD_VDEC_FRAME =		0x24,
	CMD_MEMORY_DATA =		0x25,
	CMD_MPROT_SET =		 	0x26,
	CMD_MPROT_DATA =		0x27,

	CMD_READ_TOTALBW =		0x90,
	CMD_CONTROL_START =	  	0xA0,
	CMD_CONTROL_END =	  	0xF0,
	
	CMD_TEMP_1 =		  	0xF1,
	CMD_TEMP_2 =		  	0xF2,
	CMD_TEMP_3 =		  	0xF3,
	CMD_TEMP_4 =		  	0xF4,
	CMD_TEMP_5 =		  	0xF5,
	CMD_TEMP_6 =		  	0xF6,
	CMD_TEMP_7 =		  	0xF7,
	CMD_TEMP_8 =		  	0xF8,
	CMD_TEMP_9 =		  	0xF9,
	
	CMD_FAIL =      		0xFF
}
PACKET_CMD_E;

#endif /*_PERF_MON_TARGET_H_*/
