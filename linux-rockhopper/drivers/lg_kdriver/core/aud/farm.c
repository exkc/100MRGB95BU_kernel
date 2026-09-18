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

/** @defgroup Farm
  * @{
  *
  * @brief
  * farm block
  * @detail
  *
  * @}
  */

/** @file
  * @ingroup Farm
  *
  *  implementation for farm
  *
  *  author	Jihoon Lee (gaius.lee@lge.com)
  *  version	0.1
  *  date	2023.01.06
  *  note	Additional information.
  *
  */

//#include <linux/spinlock.h>
#include <linux/slab.h>

#include "log.h"
#include "kaimc.h"
#include "block.h"
#include "block_manager.h"
#include "farm.h"

#include "module/adec_module_list.h"    ///< ADEC_CORE_ARM


logm_define (afarm, log_level_info);
#define trace(fmt,args...)	logm_trace(afarm,fmt,##args)
#define debug(fmt,args...)	logm_debug(afarm,fmt,##args)
#define info(fmt,args...)	logm_info(afarm,fmt,##args)
#define noti(fmt,args...)	logm_noti(afarm,fmt,##args)
#define error(fmt,args...)	logm_error(afarm,fmt,##args)

static DEFINE_MUTEX (_farm_lock);

#define AUD_FARM_LOCK()		mutex_lock(&_farm_lock)
#define AUD_FARM_UNLOCK()	mutex_unlock(&_farm_lock)

/**
 * AUDIO farm Information.
 */
struct aud_farm_info
{
    struct aud_block_info parent;

    bool suspended;             // for suspend / resume

    int uid_workerbin;
    int uid_master;

    struct aud_block_info *block_master;
};


void farm_set_master_info (struct aud_block_info *block, struct aud_block_info *block_master)
{
    struct aud_farm_info *farm = (struct aud_farm_info *) block;

    AUD_FARM_LOCK ();

    farm->block_master = block_master;
    farm->uid_master = apipeline_tail (block_master->pipeline);

    aimc_set_property (farm->uid_master, "workerbin-uid=%d", farm->uid_workerbin);
    aimc_set_property (farm->uid_workerbin, "decoderbin-uid=%d", farm->uid_master);

    info ("uid of master is 0x%08x\n", farm->uid_master);

    AUD_FARM_UNLOCK ();
}

static void farm_create_pipeline (struct aud_block_info *block)
{
    struct aud_farm_info *farm = (struct aud_farm_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    AUD_FARM_LOCK ();

    info ("create pipeline\n");

    block->pipeline = apipeline_new2 (preferred_proc, "workfarm");

    farm->uid_workerbin = apipeline_appendf (block->pipeline, "workerbin");


    AUD_FARM_UNLOCK ();
}

static int farm_post_reconnect (struct aud_block_info *block)
{
    struct aud_block_info *block_master;

    block_master = bm_get_master_by_block_info (block);
    if (block_master)
        farm_set_master_info (block, block_master);

    info ("post_reconnect is done.");

    return 0;
}

static int farm_suspend (struct aud_block_info *block)
{
    struct aud_farm_info *farm = (struct aud_farm_info *) block;

    info ("suspend farm..\n");

    if (block->pipeline)
        apipeline_del (block->pipeline);

    block->pipeline = NULL;

    farm->block_master = NULL;
    farm->uid_master = 0;
    farm->uid_workerbin = 0;

    farm->suspended = true;

    return 0;
}



static int farm_resume (struct aud_block_info *block)
{
    struct aud_farm_info *farm = (struct aud_farm_info *) block;

    info ("resume farm..\n");

    if (farm->suspended == false)
    {
        farm_suspend (block);
    }

    farm_create_pipeline (block);

    farm->suspended = false;
    return 0;
}

/**
 * create farm
 *
 * Media path - (buffer) - srcbin (mssrc/pcmcvt/sola) - lipsync - gain
 *
 * @param index [in] index of farm
 * @return pointer of farm info
*/
static int farm_create (struct aud_block_info *block)
{
    noti ("create farm\n");

    farm_create_pipeline (block);

    block->isOpened = true;

    noti ("done\n");
    return 0;
}


/**
 * close farm
 *
 * @param farm [in] pointer of farm info
 * @return void
 * @see aud_farm_info
*/
static void farm_destroy (struct aud_block_info *block)
{
    noti ("called\n");

    AUD_FARM_LOCK ();

    if (block == NULL)
    {
        error ("block is NULL!!\n");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("farm is already closed. \n");
        goto exit;
    }

    // destroy pipeline (inside modules are destroyed automatically)
    if (block->pipeline)
        apipeline_del (block->pipeline);

    block->isOpened = false;

  exit:
    AUD_FARM_UNLOCK ();
    noti ("done\n");
}

static struct audio_block_impl block_impl = {
    .block_info_size = sizeof (struct aud_farm_info),
    .block_type = "farm",
    .preffered_processor = ADEC_CORE_DSP3,
    .constructor = farm_create,
    .destructor = farm_destroy,
    .post_reconnect = farm_post_reconnect,
    .suspend = farm_suspend,
    .resume = farm_resume,
};

void farm_initializer (void)
{
    bm_block_registry (&block_impl);
}
