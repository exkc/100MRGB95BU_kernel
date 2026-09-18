/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  driver debug output utility
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version     1.0
 *  date        2009.11.18
 *
 *  @addtogroup lg1150_base
 *  @{
 */

#ifndef _DEBUG_UTIL_H_
#define _DEBUG_UTIL_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
//#include <linux/proc_fs.h>
#include "base_types.h"
#include "logm_kapi.h"

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
#define DBG_OPEN(module_name)   LOGM_ObjRegister(module_name)
#define DBG_CLOSE(module_fd)    do { /* do nothing */ } while(0)

#define DBG_PRINT(fd, idx, fmt, args...) \
    do { \
        if((fd)>=0) LOGM_WriteLog(&(fd), NULL, (LX_LOGM_LOGLEVEL_T)(idx), __F__, __L__, fmt, ##args); \
    } while(0)

#define DBG_PRINT_ERROR(fmt, args...)   DBG_PRINT(lg1k_core_logm_fd, LX_LOGM_LEVEL_ERROR, fmt, ##args)
#define DBG_PRINT_WARNING(fmt, args...) DBG_PRINT(lg1k_core_logm_fd,LX_LOGM_LEVEL_WARNING, fmt, ##args)
#define DBG_PRINTX                      DBG_PRINT

extern int lg1k_core_logm_fd;

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
    DBG_LEVEL_OFF   = 0,        ///< debug off
    DBG_LEVEL_ERR   = 1,        ///< only error level is printed
    DBG_LEVEL_WRN   = 2,        ///< only error and warning level are printed
    DBG_LEVEL_DBG   = 3,        ///< all debugs are printed
    DBG_LEVEL_ALL   = DBG_LEVEL_DBG,
};

enum
{
    DBG_COLOR_NONE  = 0,

    DBG_COLOR_BLACK,            ///< foreground : black
    DBG_COLOR_RED,              ///< foreground : red
    DBG_COLOR_GREEN,            ///< foreground : green
    DBG_COLOR_YELLOW,           ///< foreground : yellow
    DBG_COLOR_BLUE,             ///< foreground : blue
    DBG_COLOR_PURPLE,           ///< foreground : purple
    DBG_COLOR_CYAN,             ///< foreground : cyan
    DBG_COLOR_GRAY,             ///< foreground : gray

    DBG_COLOR_UL_BLACK,         ///< foreground : black (underline attribute)
    DBG_COLOR_UL_RED,           ///< foreground : red   (underline attribute)
    DBG_COLOR_UL_GREEN,         ///< foreground : green (underline attribute)
    DBG_COLOR_UL_YELLOW,        ///< foreground : yellow (underline attribute)
    DBG_COLOR_UL_BLUE,          ///< foreground : blue  (underline attribute)
    DBG_COLOR_UL_PURPLE,        ///< foreground : purple (underline attribute)
    DBG_COLOR_UL_CYAN,          ///< foreground : cyan  (underline attribute)
    DBG_COLOR_UL_GRAY,          ///< foreground : gray  (underline attribute)


    DBG_COLOR_BG_BLACK,         ///< background : black
    DBG_COLOR_BG_RED,           ///< background : red
    DBG_COLOR_BG_GREEN,         ///< background : green
    DBG_COLOR_BG_YELLOW,        ///< background : yellow
    DBG_COLOR_BG_BLUE,          ///< background : blue
    DBG_COLOR_BG_PURPLE,        ///< background : purple
    DBG_COLOR_BG_CYAN,          ///< background : cyan
    DBG_COLOR_BG_GRAY,          ///< background : gray
};

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
#define OS_DEBUG_EnableModule(module_fd)                        do { /* do nothing */ } while(0)
#define OS_DEBUG_EnableModuleByIndex(module_fd, index,color)    LOGM_ObjBitMaskEnable(module_fd, index)
#define OS_DEBUG_DisableModuleByIndex(module_fd, index)         LOGM_ObjBitMaskDisable(module_fd, index)
#define OS_DEBUG_SetModuleMask(module_fd,mask)                  LOGM_ObjMaskSet(module_fd, mask)

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEBUG_UTIL_H */

/** @} */
/** @} */

