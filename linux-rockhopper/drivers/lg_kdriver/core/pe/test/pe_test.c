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
 *	main driver implementation for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *	author
 *	version
 *	date
 *	note
 *
 *	@addtogroup
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/time.h>
#include <linux/delay.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
#include "pe_cfg.h"
#include "pe_def.h"
#include "pe_kapi.h"
#include "pe_test.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct pe_test_ctx
{
    int init;
    int (*handler)(struct pe_test_handler *);
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct pe_test_ctx _g_pe_test_ctx = {.init=0,.handler=NULL};

/*========================================================================================
	Implementation Group
========================================================================================*/
static int pe_test_init(void)
{
    int ret = 0;

    if (0)
    {
    }
    #ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26)
    {
        extern int pe_test_o26_handler(struct pe_test_handler *ph);
        _g_pe_test_ctx.handler = pe_test_o26_handler;
    }
    #endif
    #ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24)
    {
        extern int pe_test_o24_handler(struct pe_test_handler *ph);
        _g_pe_test_ctx.handler = pe_test_o24_handler;
    }
    #endif
    else
    {
        /* do nothing */
    }

    if (_g_pe_test_ctx.handler)
    {
        struct pe_test_handler param;
        param.type = pe_test_handler_type_init;
        ret = _g_pe_test_ctx.handler(&param);
    }

    return ret;
}

int pe_test_command(unsigned long arg,unsigned int flag)
{
    int ret = 0;
    int size;
    char *tok, *sav_tok;
    char delim[] = ":= \t\n";
    char str[64];
    LX_PE_TEST_CMD_T cmd;
    struct pe_test_handler handler = {.cmd=(void *)&cmd};
    struct pe_test_ctx *p_ctx = &_g_pe_test_ctx;

    if (!p_ctx->init)
    {
        pe_test_init();
        p_ctx->init = 1;
    }

    if (!p_ctx->handler)
    {
        PE_PRINT_ERROR("no handler(chip : not support)\n");
        return 0;
    }

    memset(&str,0,64);
    if(flag == 0)//from user
    {
        if (copy_from_user(&cmd, (void __user *)arg, sizeof(cmd)))
        {
            PE_PRINT_ERROR("copy_from_user err\n");
            return -1;
        }

        size = (cmd.size > 64)? 64:cmd.size;
        if (copy_from_user(str, (void __user *)cmd.cmd, size))
        {
            PE_PRINT_ERROR("copy_from_user err\n");
            return -1;
        }
    }
    else
    {
        memcpy(&cmd, (void *)arg, sizeof(cmd));
        size = (cmd.size > 64)? 64:cmd.size;
        memcpy(str, cmd.cmd, size);
    }

    //PE_PRINT_NOTI("flag(%d) cfg(%d) state(%d) size(%d) cmd(%s)\n",flag,cmd.cfg,cmd.state,cmd.size,str);

    tok=simple_strtok(str, delim, &sav_tok);

    while (tok)
    {
        if (!strncasecmp(tok, "start", strlen("start")))
        {
            tok=simple_strtok(NULL, delim, &sav_tok);
            handler.type = pe_test_handler_type_start;
            handler.str = tok;
            ret = p_ctx->handler(&handler);
            break;
        }

        if (!strncasecmp(tok, "state", strlen("state")))
        {
            tok=simple_strtok(NULL, delim, &sav_tok);
            handler.type = pe_test_handler_type_state;
            handler.str = tok;
            ret = p_ctx->handler(&handler);
            if(flag == 0)//from user
            {
                if (copy_to_user((void __user *)arg, &cmd, sizeof(cmd)))
                {
                    PE_PRINT_ERROR("copy_to_user err\n");
                    return -1;
                }
            }
            else
            {
                memcpy((void *)arg, &cmd, sizeof(cmd));
            }
            break;
        }

        if (!strncasecmp(tok, "stop", strlen("stop")))
        {
            tok=simple_strtok(NULL, delim, &sav_tok);
            handler.type = pe_test_handler_type_stop;
            handler.str = tok;
            ret = p_ctx->handler(&handler);
            break;
        }

        tok=simple_strtok(NULL, delim, &sav_tok);
    }

    return ret;
}
