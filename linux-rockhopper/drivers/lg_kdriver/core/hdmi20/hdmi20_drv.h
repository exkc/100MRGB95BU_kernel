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
 *  @author		won.hur (won.hur@lge.com)
 *  @version	1.0
 *  @date		2012.04.17
 *
 *  @addtogroup lg115x_hdmi20
 *	@{
 */

#ifndef	_HDMI20_DRV_H_
#define	_HDMI20_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "hdmi20_kapi.h"
#include <linux/platform_device.h>

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#ifndef DMA_BIT_MASK
#define DMA_BIT_MASK(n)	(((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	HDMI20_ERROR(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_ERROR, format, ##args)
#define	HDMI20_WARN(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_WARNING, format, ##args)
#define	HDMI20_PRINT(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_NOTI, format, ##args)
#define	HDMI20_INFO(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_INFO, format, ##args)
#define	HDMI20_DBG(format, args...)				DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)

#define	HDMI20_AUDIO(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+0, format, ##args)
#define	HDMI20_SWWA(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+1, format, ##args)

#define	HDMI20_VIDEO(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+2, format, ##args)

#define	HDMI20_PACKET(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+3, format, ##args)
#define	HDMI20_LINK_PACKET(format, args...)		DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+4, format, ##args)

#define HDMI20_INTR(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+5, format, ##args)

#define	HDMI20_PHY(format, args...)				DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+6, format, ##args)

#define	HDMI20_SNPS(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+7, format, ##args)
#define	HDMI20_SNPS_ERR(format, args...)		DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+8, format, ##args)

#define	HDMI20_CEC_INFO(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+9, format, ##args)
#define	HDMI20_CEC_DEBUG(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+10, format, ##args)
#define	HDMI20_CEC_ERROR(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+11, format, ##args)

/* Default print on for Audio */
#define	HDMI20_ADEF(format, args...)			DBG_PRINT( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+12, format, ##args)

#define	HDMI20_ISR_PRINT(format, args...)			hdmi20_isr2thread_print(format, ##args);
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct 
{
	UINT32 len;
	UINT8 data[];
} HDMI20_ESM_GRIFFIN_HL_DRV_IOC_CODE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     HDMI20_PreInit(void);
extern	int      HDMI20_Init(void);
extern	void     HDMI20_Cleanup(void);
extern  int  	HDMI20_probe(struct platform_device *pdev);
extern  int 	hdmi20_isr2thread_print(const char *fmt, ...);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_hdmi20_debug_fd;

extern void    HDMI20_InitCfg ( void );


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _HDMI20_DRV_H_ */

/** @} */
