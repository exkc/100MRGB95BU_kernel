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
#define DBG_OPEN(module_name)                       LOGM_ObjRegister(module_name)
#define DBG_CLOSE(module_fd)                        LOGM_ObjRegister(g_logm_obj_map[module_fd].name)

#define DBG_PRINT_ERROR(format, args...)            LOGM_PRINT(g_global_debug_fd,LX_LOGM_LEVEL_ERROR,format, ##args)
#define DBG_PRINT_WARNING(format, args...)          LOGM_PRINT(g_global_debug_fd,LX_LOGM_LEVEL_WARNING,format, ##args)

#define DBG_PRINT(module_fd,index,format, args...)  LOGM_PRINT(module_fd,(LX_LOGM_LOGLEVEL_T)index,format, ##args)
#define DBG_PRINTX(module_fd,index,format, args...) LOGM_PRINT(module_fd,(LX_LOGM_LOGLEVEL_T)index,format, ##args)

#define DBG_MSG(format, args...)                    LOGM_PRINT(g_global_debug_fd,LX_LOGM_LEVEL_NOTI,format, ##args)
#define DBG_TRACE(format, args...)                  LOGM_PRINT(g_global_debug_fd,LX_LOGM_LEVEL_TRACE,format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * debug output level
 *
 * @see OS_DEBUG_SetGlobalLevel
 * @see OS_DEBUG_GetGlobalLevel
 */
typedef enum
{
    DBG_LEVEL_OFF   = 0,        ///< debug off
    DBG_LEVEL_ERR   = 1,        ///< only error level is printed
    DBG_LEVEL_WRN   = 2,        ///< only error and warning level are printed
    DBG_LEVEL_DBG   = 3,        ///< all debugs are printed
    DBG_LEVEL_ALL   = DBG_LEVEL_DBG,
}
DBG_LEVEL_T;

/**
 * color definition for debug output
 *
 * @see OS_DEBUG_EnableModuleByIndex
 */
typedef enum
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
}
DBG_COLOR_T;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void         OS_DEBUG_Init(void);
extern void         OS_DEBUG_Cleanup(void);

#define OS_DEBUG_EnableModule(module_fd)
#define OS_DEBUG_PrintError_Tag(l, fi, fn, ln, f, args...)      LOGM_PRINT(g_global_debug_fd, LX_LOGM_LEVEL_ERROR, f, ##args)
#define OS_DEBUG_EnableModuleByIndex(module_fd, index,color )   LOGM_ObjBitMaskEnable(module_fd, index)
#define OS_DEBUG_DisableModuleByIndex(module_fd, index )        LOGM_ObjBitMaskDisable(module_fd, index)
#define OS_DEBUG_SetModuleMask(module_fd,mask )                 LOGM_ObjMaskSet(module_fd, mask)

// CMA 로 설정된 메모리풀의 안정성을 검증하기 위한 실험을 지원한다.
// 테스터는 force_hma_pool=a,b,c,d 형식으로 CMA 에서 HMA(NO_CMA) 로 전환할 pool name 리스트를 전달한다.
// CMA 타입의 메모리풀을 만드는 모듈에서는 check_force_hma_pool() 함수를 호출하여, 테스터의 의하여
// 강제 HMA 타입의 메모리풀 생성을 요청 받았는지 반드시 확인해야 한다.
//
extern bool         check_force_hma_pool(const char* pool);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/
extern int  g_global_debug_fd;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _BASE_DRV_H_ */

/** @} */
/** @} */

