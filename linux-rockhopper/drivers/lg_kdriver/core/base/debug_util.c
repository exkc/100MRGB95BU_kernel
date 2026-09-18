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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
int         g_global_debug_fd;
EXPORT_SYMBOL(g_global_debug_fd);

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
    Implementation Group
========================================================================================*/
void OS_DEBUG_Init(void)
{
    g_global_debug_fd = DBG_OPEN("kdrvcore");

    if (g_global_debug_fd >= 0)
    {
        LOGM_ObjBitMaskEnable(g_global_debug_fd, LX_LOGM_LEVEL_ERROR);
        LOGM_ObjBitMaskEnable(g_global_debug_fd, LX_LOGM_LEVEL_WARNING);
        LOGM_ObjBitMaskEnable(g_global_debug_fd, LX_LOGM_LEVEL_NOTI);
    }
}

void    OS_DEBUG_Cleanup(void)
{
    DBG_CLOSE(g_global_debug_fd);
}

bool check_force_hma_pool(const char* pool)
{
    char* tok, *sav_tok;
    char delim[] = ",";
    char pool_list[256];

    int ret;

    if (!pool) return false;

    ret = OS_ScanKernelCmdline("force_hma_pool=%s", pool_list);

    if (ret == RET_OK)
    {
        //printk("pool_list=%s, pool=%s\n", pool_list, pool);

        for (tok = simple_strtok(pool_list, delim, &sav_tok); tok; tok = simple_strtok(NULL, delim, &sav_tok))
        {
			int sz0 = strlen(tok);
			int sz1 = strlen(pool);

            if (sz0 == sz1 && !strncmp(tok, pool, sz0))
            {
                return true;
            }
        }
    }

    return false;
}

EXPORT_SYMBOL(check_force_hma_pool);
