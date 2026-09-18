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
 *  driver interface header for PWM device. ( used only within kdriver )
 *  PWM device will teach you how to make device driver with new platform.
 *
 *  @author     ks.hyun (ks.hyun@lge.com)
 *  @version    1.0
 *  @date       2010.12.13
 *
 *  @addtogroup lg1150_PWM
 *  @{
 */

#ifndef _PWM_DRV_H_
#define _PWM_DRV_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define PWM_LOG_LEVEL_ERROR             LX_LOGM_LEVEL_ERROR
#define PWM_LOG_LEVEL_WARN              LX_LOGM_LEVEL_WARNING
#define PWM_LOG_LEVEL_NOTI              LX_LOGM_LEVEL_NOTI
#define PWM_LOG_LEVEL_DEBUG             LX_LOGM_LEVEL_DEBUG
#define PWM_LOG_LEVEL_TRACE             LX_LOGM_LEVEL_TRACE
#define PWM_LOG_LEVEL_PRINT             (LX_LOGM_LEVEL_TRACE + 1)

#define PWM_PRINT(format, args...)      DBG_PRINT(  g_PWM_debug_fd, PWM_LOG_LEVEL_PRINT, format, ##args)
#define PWM_TRACE(format, args...)      DBG_PRINTX( g_PWM_debug_fd, PWM_LOG_LEVEL_TRACE, format, ##args)
#define PWM_DEBUG(format, args...)      DBG_PRINT( g_PWM_debug_fd, PWM_LOG_LEVEL_DEBUG, format, ##args)
#define PWM_NOTI(format, args...)       DBG_PRINT( g_PWM_debug_fd, PWM_LOG_LEVEL_NOTI, format, ##args)
#define PWM_ERROR(format, args...)      DBG_PRINT( g_PWM_debug_fd, PWM_LOG_LEVEL_ERROR, format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern  void     lg1k_pwm_preinit(void);
extern  int      lg1k_pwm_init(void);
extern  void     lg1k_pwm_cleanup(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/
//extern    int     g_PWM_debug_fd;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _PWM_DRV_H_ */

/** @} */
