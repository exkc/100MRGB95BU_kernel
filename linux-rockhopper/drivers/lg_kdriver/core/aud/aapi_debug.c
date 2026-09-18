/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2020 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

#include <linux/module.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>

#include "os_util.h"
#include "debug_util.h"

#include "log.h"

#include "aapi.h"
#include "aud_kapi.h"
#include "aud_kapi_debug.h"

#include "block.h"
#include "block_manager.h"
#include "decoder.h"
#include "renderer.h"
#include "dsp_control.h"

logm_define (adeug, log_level_info);
#define trace(fmt,args...)  logm_trace(adeug,fmt,##args)
#define debug(fmt,args...)  logm_debug(adeug,fmt,##args)
#define info(fmt,args...)   logm_info(adeug,fmt,##args)
#define noti(fmt,args...)   logm_noti(adeug,fmt,##args)
#define warn(fmt,args...)   logm_warning(adeug,fmt,##args)
#define error(fmt,args...)  logm_error(adeug,fmt,##args)

static int adebug_get_block (struct adebug_info_t *adebug_info, char *block_type, int index)
{
    struct aud_block_info *block_info = NULL;
    int ret = -1;

    block_info = bm_get_block_info_by_index (block_type, index);
    if (block_info)
    {
        noti ("fetch block OK\n");
        adebug_info->is_created = false;
    }
    else
    {
        noti ("block is not created yet.. so create\n");
        block_info = bm_create_block (block_type, index);
        if (block_info == NULL)
        {
            error ("can't create block %s!!\n", block_type);
            goto exit;
        }

        adebug_info->is_created = true;
    }

    adebug_info->index = index;
    adebug_info->block_info = block_info;
    noti ("block_info %p, %s\n", block_info, block_info->block_type);

    ret = 0;
  exit:

    return ret;
}

static int adebug_ren_set_param (struct adebug_info_t *adebug_info, char *param_str)
{
    struct aud_block_info *block_info = NULL;
    int ret = -1;

    block_info = adebug_info->block_info;
    if (strcmp (block_info->block_type, "renderer"))
    {
        error ("this function is for renderer!!!! not %s!!\n", block_info->block_type);
        goto exit;
    }

    ret = renderer_set_param (block_info, param_str);
  exit:

    return ret;
}

static int adebug_ren_get_param (struct adebug_info_t *adebug_info, char *param_str, int *ret_value)
{
    struct aud_block_info *block_info = NULL;

    int ret = -1;

    block_info = adebug_info->block_info;
    if (strcmp (block_info->block_type, "renderer"))
    {
        error ("this function is for renderer!!!! not %s!!\n", block_info->block_type);
        goto exit;
    }

    ret = renderer_get_param (block_info, param_str, ret_value);

  exit:
    return ret;
}

static int adebug_suspend (struct adebug_info_t *adebug_info, bool suspend)
{
    struct aud_block_info *block_info = NULL;

    int ret = -1;

    block_info = adebug_info->block_info;
    if (suspend)
        ret = bm_suspend ();
    else
        ret = bm_resume ();

    return ret;
}

long adebug_ioctl (struct adebug_info_t *info, unsigned int cmd, union audio_dbg_ioctl_args *args)
{
    long ret;

    switch (cmd)
    {
        case ADBG_IOW_OPEN_BLOCK:
        {
            struct adbg_open_block *open_block;

            open_block = &(args->open_block);
            noti ("block = %s%d\n", open_block->name, open_block->index);

            ret = adebug_get_block (info, open_block->name, open_block->index);
            break;
        }

        case ADBG_IOW_REN_SET_PARAM:
            ret = adebug_ren_set_param (info, args->ren_param.args);
            break;

        case ADBG_IOR_REN_GET_PARAM:
            noti ("get %s", args->ren_param.args);
            ret = adebug_ren_get_param (info, args->ren_param.args, &args->ren_param.ret_val);
            break;

        case ADBG_IOR_SUSPEND:
            noti ("suspend..\n");
            ret = adebug_suspend (info, true);
            break;

        case ADBG_IOR_RESUME:
            noti ("resume..\n");
            ret = adebug_suspend (info, false);
            break;

        case ADBG_IO_RESET:
            noti ("reset...\n");
            ret = aud_dsp_reset ();
            break;

        default:
            /* redundant check but it seems more readable */
            error ("Invalid IOCTL Call!!! %x\n", cmd);
            ret = RET_INVALID_IOCTL;
            break;
    }

    return ret;
}

struct adebug_info_t *adebug_open (void)
{
    struct adebug_info_t *adebug_info = NULL;

    adebug_info = kzalloc (sizeof (struct adebug_info_t), GFP_KERNEL);

    noti ("adebug opened %p", adebug_info);

    return adebug_info;
}

int adebug_close (struct adebug_info_t *adebug_info)
{
    if (adebug_info->is_created)
    {
        noti ("close created block %s%d\n", adebug_info->block_info->block_type,
            adebug_info->index);
        bm_destroy_block (adebug_info->block_info);
    }

    kfree (adebug_info);

    noti ("done\n");
    return 0;
}
