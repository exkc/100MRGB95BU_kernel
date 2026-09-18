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
 *  main driver implementation for irb device.
 *	irb device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_irb
 */


#ifndef	_IRB_DRV_H_
#define	_IRB_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "irb_cfg.h"
#include "irb_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#define IRBLASTER_NEC		0x00
#define IRBLASTER_SI12		0x01
#define IRBLASTER_SI15		0x02
#define IRBLASTER_SI20		0x03
#define IRBLASTER_RC_5		0x04
#define IRBLASTER_RC_6		0x05
#define IRBLASTER_SANY		0x06
#define IRBLASTER_CUS0		0x07
#define IRBLASTER_CUS1		0x08
#define IRBLASTER_CUS2		0x09
#define IRBLASTER_CUS3		0x0a
#define IRBLASTER_CUS4		0x0b
#define IRBLASTER_CUS5		0x0c
#define IRBLASTER_MAX		0x0f

#define REPEAT_MASK		0x02
#define PROTOCOL_MASK		0x01


#define CR_IREN 		0
#define CR_TX 			1
#define CR_RPT 			2
#define CR_COFF			3
#define CR_PTYPE		4
#define CR_DUTY			9

#define CR_IREN_SET		(1 << CR_IREN)
#define CR_IREN_CLR		~CR_IREN_SET
#define CR_TX_SET		(1 << CR_TX)
#define CR_TX_CLR		~CR_TX_SET
#define CR_RPT_SET		(1 << CR_RPT)
#define CR_RPT_CLR		~CR_RPT_SET
#define CR_COFF_SET		(1 << CR_COFF)
#define CR_COFF_CLR		~CR_COFF_SET

#define CR_CAR_ON_SET		~CR_COFF_SET /* and operation requrired */

#define CR_PTYPE_SET		(0x1f << CR_PTYPE)
#define CR_PTYPE_CLR		~CR_PTYPE_SET
#define CR_PTYPE_NEC		(0x00 << CR_PTYPE)
#define CR_PTYPE_SI12		(0x01 << CR_PTYPE)
#define CR_PTYPE_SI15		(0x02 << CR_PTYPE)
#define CR_PTYPE_SI20		(0x03 << CR_PTYPE)
#define CR_PTYPE_RC_5		(0x04 << CR_PTYPE)
#define CR_PTYPE_RC_6		(0x05 << CR_PTYPE)
#define CR_PTYPE_SANY		(0x06 << CR_PTYPE)
#define CR_PTYPE_CUS0		(0x1f << CR_PTYPE)
#define CR_DUTY_SET		(1 << CR_DUTY)
#define CR_DUTY_CLR		~CR_DUTY_SET

#define CPR_PSIZE		0
#define CPR_RTYPE		6
#define CPR_RSIZE		8
#define CPR_RTPSP		13

#define CPR_PSIZE_MASK		(0x3f << CPR_PSIZE)

#define SR_BUSY			0
#define SR_RBUSY		1

#define SR_BUSY_SET		(1 << SR_BUSY)
#define SR_RBUSY_SET		(1 << SR_RBUSY)

#define SIZE_PTYPE_NEC		3
#define SIZE_PTYPE_SI12		2
#define SIZE_PTYPE_SI15		2
#define SIZE_PTYPE_SI20		3
#define SIZE_PTYPE_RC_5		2
#define SIZE_PTYPE_RC_6		3
#define SIZE_PTYPE_SANY		3

#define SIZE_PTYPE_CUS_MASK	0x3f

#define DRXCR_MARKFIRSTONE	(1 << 7)
#define DRXCR_MARKFIRSTZERO	(1 << 6)
#define DRXCR_TOGGLE		(1 << 5)
#define DRXCR_MSB		(1 << 4)

#define DRX01_TAIL_OFFSET	8
#define KHZ 1000
#define MHZ (1000*KHZ)
#define PCLK (200*MHZ)
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	KDRV_IRB_PRINT(format, args...)		DBG_PRINT(  g_irb_debug_fd, IRB_MSG_TRACE, format, ##args)
#define	KDRV_IRB_TRACE(format, args...)		DBG_PRINTX( g_irb_debug_fd, IRB_MSG_TRACE, format, ##args)
#define	KDRV_IRB_DEBUG(format, args...)		DBG_PRINT( g_irb_debug_fd, IRB_MSG_DEBUG, format, ##args)
#define	KDRV_IRB_ERROR(format, args...)		DBG_PRINT( g_irb_debug_fd, IRB_MSG_ERROR, format, ##args)
#define	KDRV_IRB_NOTI(format, args...)		DBG_PRINT( g_irb_debug_fd, IRB_MSG_NOTI, format, ##args)


#define IRB_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 __CHECK_IF_ERROR(__checker, IRB_ERROR, __if_action , fmt, ##args )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	IRB_MSG_ERROR = LX_LOGM_LEVEL_ERROR,
	IRB_MSG_WARN = LX_LOGM_LEVEL_WARNING,
	IRB_MSG_NOTI = LX_LOGM_LEVEL_NOTI,
	IRB_MSG_INFO = LX_LOGM_LEVEL_INFO,
	IRB_MSG_DEBUG = LX_LOGM_LEVEL_DEBUG,
	IRB_MSG_TRACE = LX_LOGM_LEVEL_TRACE,
	IRB_MSG_NORMAL = (LX_LOGM_LEVEL_TRACE + 1),	// print
	IRB_MSG_VSYNC = (LX_LOGM_LEVEL_TRACE + 2),		// vsync
	IRB_MSG_TIMER = (LX_LOGM_LEVEL_TRACE + 3),		// timer
	IRB_MSG_INTER = (LX_LOGM_LEVEL_TRACE + 4),		// interrupt

	IRB_MSG_INDEX_COUNT
} IRB_MSG_TYPE_T;

typedef struct
{
	void			(*init)				(void);
	int				(*ioctl)			(unsigned int cmd, unsigned long arg);
	int				(*suspend)			(void);
	int				(*resume)			(void);
} irbs_driver_t;

typedef struct
{
	void			(*init)		(void);
	void			(*cleanup)	(void);
} irbs_proc_t;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     IRB_PreInit(void);
extern	int      IRB_Init(void);
extern	void     IRB_Cleanup(void);
int		IRB_Init(void);
void	IRB_Cleanup(void);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_irb_debug_fd;
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _IRB_DRV_H_ */

/** @} */
