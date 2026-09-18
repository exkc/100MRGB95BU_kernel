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
 *  driver interface header for spi device. ( used only within kdriver )
 *	spi device will teach you how to make device driver with new platform.
 *
 *  @author		ingyu.yang (ingyu.yang@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_spi
 *	@{
 */

#ifndef	_SPI_DRV_H_
#define	_SPI_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
//#include "spi_cfg.h"
#include "spi_kapi.h"

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
#define	SPI_PRINT(format, args...)		DBG_PRINT(  g_spi_debug_fd, SPI_MSG_TRACE, format, ##args)
#define	SPI_INFO(format, args...)		DBG_PRINT( g_spi_debug_fd, SPI_MSG_INFO, format, ##args)
#define	SPI_DEBUG(format, args...)		DBG_PRINT( g_spi_debug_fd, SPI_MSG_DEBUG, format, ##args)
#define	SPI_ERROR(format, args...)		DBG_PRINT( g_spi_debug_fd, SPI_MSG_ERROR, format, ##args)
#define	SPI_TRACE(format, args...)		DBG_PRINT( g_spi_debug_fd, SPI_MSG_TRACE, format, ##args)
#define	SPI_NOTI(format, args...)		DBG_PRINT( g_spi_debug_fd, SPI_MSG_NOTI, format, ##args)

#define SPI_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 __CHECK_IF_ERROR(__checker, SPI_ERROR, __if_action , fmt, ##args )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	SPI_MSG_ERROR = LX_LOGM_LEVEL_ERROR,
	SPI_MSG_WARN = LX_LOGM_LEVEL_WARNING,
	SPI_MSG_NOTI = LX_LOGM_LEVEL_NOTI,
	SPI_MSG_INFO = LX_LOGM_LEVEL_INFO,
	SPI_MSG_DEBUG = LX_LOGM_LEVEL_DEBUG,
	SPI_MSG_TRACE = LX_LOGM_LEVEL_TRACE,
	SPI_MSG_NORMAL = (LX_LOGM_LEVEL_TRACE + 1),	// print
	SPI_MSG_VSYNC = (LX_LOGM_LEVEL_TRACE + 2),		// vsync
	SPI_MSG_TIMER = (LX_LOGM_LEVEL_TRACE + 3),		// timer
	SPI_MSG_INTER = (LX_LOGM_LEVEL_TRACE + 4),		// interrupt

	SPI_MSG_INDEX_COUNT
} SPI_MSG_TYPE_T;

#define	SPI_MODULE			"spi"
#define SPI_MAX_DEVICE		2
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     SPI_PreInit(void);
extern	int      SPI_Init(void);
extern	void     SPI_Cleanup(void);
int		SPI_Init(void);
void	SPI_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_spi_debug_fd;


extern int spi_intr_pin;
extern int spi_intr_pin_value;

extern spinlock_t spiPoll_lock;

extern int spi_config (unsigned char ch, unsigned char  mode ,unsigned int speed);
extern int spi_send (unsigned char ch, unsigned char  *data, int len, int cmdlen);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _SPI_DRV_H_ */

/** @} */
