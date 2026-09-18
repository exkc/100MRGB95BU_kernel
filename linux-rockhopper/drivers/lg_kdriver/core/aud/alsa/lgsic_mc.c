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

/** @file mc.c
 *
 *  mixer capture ALSA driver
 *
 *  @author Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version    0.1
 *  @date       2021.02.16
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <sound/soc.h>

#include "logm.h"

#include "hma_alloc.h"
#include "block_manager.h"
#include "kaimc.h"
#include "imc/cmd/module_cmd_capture.h"
#include "linux/alsa-ext/alsa-ext-renderer.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define PERIOD_SIZE             (256/*sample*/ * 2/*channel*/ * 4/*byte*/)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define error(fmt,args...)      logm_error(mix_cap,fmt,##args)
#define warn(fmt,args...)       logm_warning(mix_cap,fmt,##args)
#define noti(fmt,args...)       logm_noti(mix_cap,fmt,##args)
#define info(fmt,args...)       logm_info(mix_cap,fmt,##args)
#define debug(fmt,args...)      logm_debug(mix_cap,fmt,##args)
#define trace(fmt,args...)      logm_trace(mix_cap,fmt,##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct mc_priv
{
    struct snd_pcm_substream *substream;

    struct aud_block_info *capture_info;

    bool is_connected;
    int event_id;

    phys_addr_t dma_addr;
    unsigned int dma_size;
    void *dma_vaddr;

    unsigned int wrOffset;
    unsigned int rdOffset;
    int out_bps;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _mc_updated (void *_param, int _param_len, void *_cb_param);
static int _mc_connect (struct mc_priv *mc, const char *dai_link_name);
static int _mc_disconnect (struct mc_priv *mc, const char *dai_link_name);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
static int mc_open (struct snd_pcm_substream *substream);
static int mc_close (struct snd_pcm_substream *substream);
static int mc_prepare (struct snd_pcm_substream *substream);
static int mc_trigger (struct snd_pcm_substream *substream, int cmd);
static int mc_hw_params (struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params);
static int mc_hw_free (struct snd_pcm_substream *substream);
static snd_pcm_uframes_t mc_pointer (struct snd_pcm_substream *substream);
static int mc_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma);
static int mc_ack (struct snd_pcm_substream *substream);
static int mc_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd);
static void mc_pcm_free (struct snd_pcm *pcm);
#else
static int mc_open (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int mc_close (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int mc_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int mc_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd);
static int mc_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params);
static int mc_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static snd_pcm_uframes_t mc_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int mc_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma);
static int mc_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int mc_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd);
static void mc_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int mc_probe (struct snd_soc_component *component);
static void mc_remove (struct snd_soc_component *component);
#else
static int mc_probe (struct snd_soc_platform *platform);
static int mc_remove (struct snd_soc_platform *platform);
#endif
static int mc_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt);
static int mc_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static void mc_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int mc_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai);
static int mc_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int mc_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int pdev_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev);
#else
static int pdev_remove (struct platform_device *pdev);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
logm_define (mix_cap, log_level_noti);

static struct snd_pcm_hardware mc_pcm_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE,
    .rates = SNDRV_PCM_RATE_48000,
    .rate_min = 48000,
    .rate_max = 48000,
    .channels_min = 2,
    .channels_max = 8,
    .period_bytes_min = PERIOD_SIZE,
    .period_bytes_max = PERIOD_SIZE,
    .periods_min = 2,
    .periods_max = UINT_MAX,
    .buffer_bytes_max = PERIOD_SIZE * 64,
    .fifo_size = 4,
};

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
static const struct snd_pcm_ops mc_pcm_ops = {
    .open = mc_open,
    .close = mc_close,
    .ioctl = snd_pcm_lib_ioctl,
    .prepare = mc_prepare,
    .trigger = mc_trigger,
    .hw_params = mc_hw_params,
    .hw_free = mc_hw_free,
    .pointer = mc_pointer,
    .mmap = mc_mmap,
    .ack = mc_ack,
};
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver mc_component = {
#else
static const struct snd_soc_platform_driver mc_platform = {
#endif
    .probe = mc_probe,
    .remove = mc_remove,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
    .pcm_new = mc_pcm_new,
    .pcm_free = mc_pcm_free,
    .ops = &mc_pcm_ops,
    .compr_ops = NULL,          //mc_compr_ops,
#else
    .pcm_construct  = mc_pcm_new,
    .pcm_destruct   = mc_pcm_free,
    .open = mc_open,
    .close = mc_close,
    .prepare = mc_prepare,
    .trigger = mc_trigger,
    .hw_params = mc_hw_params,
    .hw_free = mc_hw_free,
    .pointer = mc_pointer,
    .mmap = mc_mmap,
    .ack = mc_ack,
    .compress_ops = NULL,          //mc_compr_ops,
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    .name = "lgsic-mc",
#endif
};

static const struct snd_soc_dai_ops mc_dai_ops = {
    .set_fmt = mc_dai_set_fmt,
    .startup = mc_dai_startup,
    .shutdown = mc_dai_shutdown,
    .hw_params = mc_dai_hw_params,
    .hw_free = mc_dai_hw_free,
    .prepare = mc_dai_prepare,
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver mc_component[] = {
    {.name = "lgsic-mc",},
};
#endif

static struct snd_soc_dai_driver mc_dai[] = {
    {
            .name = "lgsic-mc",
            .id = 0,
            .capture = {
                    .channels_min = 2,
                    .channels_max = 8,
                    .rates = SNDRV_PCM_RATE_48000,
                    .formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE,
                },
            .ops = &mc_dai_ops,
        },
};

static struct platform_driver pdev_driver = {
    .driver = {
            .name = "lgsic-mc",
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

//static unsigned int capture_source = ADEC_MODULE_MIX_0;
//module_param (capture_source, int, 0644);

static char *mc_poolname = "audio_buffer";
module_param (mc_poolname, charp, 0644);

/*==============================================================================
    Implementation Group
==============================================================================*/

static int _mc_updated (void *_param, int _param_len, void *_cb_param)
{
    struct mc_priv *mc = _cb_param;
    int wrOffset = 0;

    debug ("got callback from\n");

    if (_param && _param_len)
    {
        wrOffset = *(int *) _param;
        trace ("wrOffset is 0x%08x dma_buffer.addr %pad\n", wrOffset,
            &mc->substream->dma_buffer.addr);

        mc->wrOffset = wrOffset;

        snd_pcm_period_elapsed (mc->substream);
    }

    return 0;
}

extern struct aud_block_info *sndout_get_se_info (common_output_ext_type_t output);
static int _mc_connect (struct mc_priv *mc, const char *dai_link_name)
{
    int uid_capture = 0;
    int ret = 0;
    struct aud_block_info *mixer_info = NULL;
    struct aud_block_info *se_info = NULL;

    debug ("called\n");

    if (mc->is_connected == true)
    {
        debug ("already connected.\n");
        _mc_disconnect (mc, dai_link_name);
    }

    mixer_info = bm_get_block_info_by_index ("mixer", 0);
    if (mixer_info)
    {
        if (!strcmp (dai_link_name, "SoundEngineCapture"))
        {
            se_info = sndout_get_se_info (COMMON_SPK);
            if (se_info)
            {
                mc->capture_info = bm_create_block_peer ("capture", -1, se_info, true);

                if (mc->capture_info)
                {
#ifndef SUPPORT_SOUNDBAR
                    bm_connect_block (mixer_info, 0, se_info, 0);
#endif
                    bm_connect_block (se_info, 0, mc->capture_info, 0);
                }
            }
        }
        else
        {
            mc->capture_info = bm_create_block_peer ("capture", -1, mixer_info, true);

            if (mc->capture_info)
            {
                bm_connect_block (mixer_info, 0, mc->capture_info, 0);
            }
        }
    }

    uid_capture = bm_get_block_tail (mc->capture_info);
    ret = aimc_register_named_event (mc, _mc_updated, uid_capture, "update", true);
    if (ret < 0)
    {
        if (mc->capture_info)
        {
            bm_destroy_block (mc->capture_info);
            mc->capture_info = NULL;
        }

        error ("fail to register evnet %d\n", ret);
        return ret;
    }

    mc->event_id = ret;

    return ret;
}

static int _mc_disconnect (struct mc_priv *mc, const char *dai_link_name)
{
    int ret = 0;

    debug ("called\n");
    if (mc->is_connected == false)
    {
        debug ("not connected.\n");
        goto exit;
    }

    mc->is_connected = false;

    if (mc->capture_info)
    {
#ifndef SUPPORT_SOUNDBAR
        if (!strcmp (dai_link_name, "SoundEngineCapture"))
        {
            struct aud_block_info *se_info = NULL;
            se_info = sndout_get_se_info (COMMON_SPK);
            if (!se_info)
            {
                bm_disconnect_block (se_info, 0);
            }
        }
#endif

        bm_disconnect_block (mc->capture_info, 0);
        bm_destroy_block (mc->capture_info);
        aimc_unregister_named_event (mc->event_id);
        mc->capture_info = NULL;
    }

  exit:
    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_open (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int mc_open (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
    struct mc_priv *mc;

    debug ("called\n");
    info ("name %s\n", substream->name);
    info ("pcm name %s\n", substream->pcm->name);
    info ("pcm card name %s\n", substream->pcm->card->shortname);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu dai name %s -> %s\n", soc_pcm_rtd->cpu_dai->name, soc_pcm_rtd->codec_dai->name);
#endif
    info ("hw name = %s \n", soc_pcm_rtd->dai_link->name);

    snd_soc_set_runtime_hwparams (substream, &mc_pcm_hardware);

    mc = kzalloc (sizeof (struct mc_priv), GFP_KERNEL);
    if (!mc)
        return -ENOMEM;

    mc->is_connected = false;

    mc->substream = substream;

    substream->runtime->private_data = mc;

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_close (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int mc_close (struct snd_pcm_substream *substream)
#endif
{
    struct mc_priv *mc = substream->runtime->private_data;
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;

    debug ("called\n");

    if (!mc)
    {
        error ("already closed!!\n");
        return -EIO;
    }

    //TODO: block disconnection prior to destroy
    _mc_disconnect (mc, soc_pcm_rtd->dai_link->name);

    kfree (mc);

    noti ("free mc done.\n");

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int mc_prepare (struct snd_pcm_substream *substream)
#endif
{
    struct mc_priv *mc = substream->runtime->private_data;
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
    CaptureCmdSetBuffer cmd = { };
    int uid_capture = 0;
    int ret = 0;

    ret = _mc_connect (mc, soc_pcm_rtd->dai_link->name);
    if (ret < 0)
    {
        error ("Error in mc module create or connection.");
        return -EIO;
    }
    mc->is_connected = true;

    uid_capture = bm_get_block_tail (mc->capture_info);
    // send dma address to mc module
    //TODO: AUDIO_GetLgbusAddr??
    cmd.buf_addr_p = mc->dma_addr;
    cmd.buf_size = snd_pcm_lib_buffer_bytes (substream);

    aimc_send_command_sync (NULL, CAPTURE_CMD_SET_BUFFER, 0, uid_capture,
        &cmd, sizeof (CaptureCmdSetBuffer));

    aimc_send_command_sync (NULL, CAPTURE_CMD_RESET_BUFFER, 0, uid_capture, NULL, 0);

    mc->wrOffset = 0;

    info ("reset buffer done.\n");

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd)
#else
static int mc_trigger (struct snd_pcm_substream *substream, int cmd)
#endif
{
    struct mc_priv *mc = substream->runtime->private_data;
    int uid_capture = 0;

    uid_capture = bm_get_block_tail (mc->capture_info);

    switch (cmd)
    {
        case SNDRV_PCM_TRIGGER_STOP:
            aimc_send_command (NULL, ADEC_CMD_STOP, 0, uid_capture, NULL, 0);
            info ("stop\n");
            break;

        case SNDRV_PCM_TRIGGER_START:
            aimc_send_command (NULL, ADEC_CMD_START, 0, uid_capture, NULL, 0);
            info ("start\n");
            break;

        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
            info ("pause_push\n");
            break;

        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
            info ("pause_release\n");
            break;

        case SNDRV_PCM_TRIGGER_SUSPEND:
            info ("suspend\n");
            break;

        case SNDRV_PCM_TRIGGER_RESUME:
            info ("resume\n");
            break;

        case SNDRV_PCM_TRIGGER_DRAIN:
            info ("drain\n");
            break;

        default:
            error ("unknown command. %d\n", cmd);
            return -EINVAL;
    }

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#else
static int mc_hw_params (struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#endif
{
    struct mc_priv *mc = substream->runtime->private_data;
    const struct snd_interval *intv;

    debug ("called\n");

    /* dma buffer */
    mc->dma_size = mc_pcm_hardware.buffer_bytes_max;
    mc->dma_addr = hma_alloc_user (mc_poolname, mc->dma_size, 1024, "alsa_capture");
    if (!mc->dma_addr)
    {
        error ("no mem for dma\n");
        kfree (mc);
        return -ENOMEM;
    }
    mc->dma_vaddr = hma_map (mc->dma_addr, mc->dma_size);
    if (!mc->dma_vaddr)
    {
        error ("cannot map dma buffer\n");
        hma_free (mc_poolname, mc->dma_addr);
        kfree (mc);
        return -EIO;
    }
    info ("dma buffer %pap(0x%x), %p\n", &mc->dma_addr, mc->dma_size, mc->dma_vaddr);

    substream->dma_buffer.addr = mc->dma_addr;
    substream->dma_buffer.area = mc->dma_vaddr;
    substream->dma_buffer.bytes = mc->dma_size;

    info ("substream->dma_buffer.dev.type %d\n", substream->dma_buffer.dev.type);
    info ("substream->dma_buffer.dev.dev %p(%s)\n",
        substream->dma_buffer.dev.dev,
        substream->dma_buffer.dev.dev ? dev_name (substream->dma_buffer.dev.dev) : "NULL");
    info ("substream->dma_buffer.area %p\n", substream->dma_buffer.area);
    info ("substream->dma_buffer.addr %pad\n", &substream->dma_buffer.addr);
    info ("substream->dma_buffer.bytes %zu\n", substream->dma_buffer.bytes);
    info ("substream->dma_buffer.private_data %p\n", &substream->dma_buffer.private_data);

    intv = hw_param_interval_c (params, SNDRV_PCM_HW_PARAM_BUFFER_SIZE);
    info ("buffer_size min %d - max %d\n", intv->min, intv->max);

    snd_pcm_set_runtime_buffer (substream, &substream->dma_buffer);

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int mc_hw_free (struct snd_pcm_substream *substream)
#endif
{
    struct mc_priv *mc = substream->runtime->private_data;

    debug ("called\n");

    snd_pcm_set_runtime_buffer (substream, NULL);

    hma_unmap (mc->dma_vaddr);
    hma_free ((const char *) mc_poolname, mc->dma_addr);
    info ("hma free done\n");

    mc->dma_vaddr = NULL;
    mc->dma_addr = 0;

    info ("done\n");
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static snd_pcm_uframes_t mc_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static snd_pcm_uframes_t mc_pointer (struct snd_pcm_substream *substream)
#endif
{
    struct mc_priv *mc = substream->runtime->private_data;
    snd_pcm_uframes_t ret;
    unsigned int wrOffset = mc->wrOffset;

    if (wrOffset >= snd_pcm_lib_buffer_bytes (substream))
    {
        error
            ("wrong hardware pointer. hw_ptr 0x%x snd_pcm_lib_buffer_bytes (substream) %zd dma_buffer.addr %pad\n",
            wrOffset, snd_pcm_lib_buffer_bytes (substream), &mc->substream->dma_buffer.addr);
        wrOffset = 0;
    }

    ret = bytes_to_frames (substream->runtime, wrOffset);
    debug ("wrOffset 0x%05x, frames %4ld/%ld dma_buffer.addr %pad\n", wrOffset, ret,
        substream->runtime->buffer_size, &mc->substream->dma_buffer.addr);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#else
static int mc_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#endif
{
    int ret;

    debug ("called\n");
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
    vm_flags_set (vma, VM_DONTEXPAND | VM_DONTDUMP);
#else
    vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
#endif
    vma->vm_page_prot = pgprot_noncached (vma->vm_page_prot);

    ret = remap_pfn_range (vma, vma->vm_start,
        substream->dma_buffer.addr >> PAGE_SHIFT, vma->vm_end - vma->vm_start, vma->vm_page_prot);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int mc_ack (struct snd_pcm_substream *substream)
#endif
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct mc_priv *mc = substream->runtime->private_data;
    snd_pcm_sframes_t sw_ptr;

    debug ("called\n");

    sw_ptr = runtime->control->appl_ptr % runtime->buffer_size;
    mc->rdOffset = frames_to_bytes (substream->runtime, sw_ptr);
    debug ("rdOffset 0x%05x(%4ld)/%ld (buffered size %d)\n", mc->rdOffset, sw_ptr,
        runtime->buffer_size, (mc->wrOffset - mc->rdOffset));

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int mc_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd)
#else
static int mc_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd)
#endif
{
    debug ("called");
    info ("dai_link %p", soc_pcm_rtd->dai_link);
    if (soc_pcm_rtd->dai_link)
        info ("dai_link name %s(%s)", soc_pcm_rtd->dai_link->name,
            soc_pcm_rtd->dai_link->stream_name);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu_dai name %s(%p)", soc_pcm_rtd->cpu_dai->name,
        snd_soc_dai_get_drvdata (soc_pcm_rtd->cpu_dai));
    info ("codec_dai name %s", soc_pcm_rtd->codec_dai->name);
#endif
    info ("device name %s", dev_name (soc_pcm_rtd->dev));
    info ("card name %s", soc_pcm_rtd->card->name);

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void mc_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm)
#else
static void mc_pcm_free (struct snd_pcm *pcm)
#endif
{
    debug ("called");
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int mc_probe (struct snd_soc_component *component)
#else
static int mc_probe (struct snd_soc_platform *platform)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct platform_device *pdev = to_platform_device (component->dev);
#else
    struct platform_device *pdev = to_platform_device (platform->dev);
#endif

    info ("pdev name %s.%d", pdev->name, pdev->id);
    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void mc_remove (struct snd_soc_component *component)
{
    debug ("called");
}
#else
static int mc_remove (struct snd_soc_platform *platform)
{
    debug ("called");

    return 0;
}
#endif

static int mc_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt)
{
    debug ("called");
    return 0;
}

static int mc_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s", dai->name);
    return 0;
}

static void mc_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s", dai->name);
}

static int mc_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai)
{
    debug ("called");
    return 0;
}

static int mc_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("called");
    return 0;
}

static int mc_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("called");
    return 0;
}

static int pdev_probe (struct platform_device *pdev)
{
    int ret;

    info ("probe.. %s", pdev->name);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_platform (&pdev->dev, &mc_platform);
    if (ret < 0)
    {
        error ("cannot register_platform(). %d", ret);
        return ret;
    }
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_component (&pdev->dev, &mc_component, mc_dai, ARRAY_SIZE (mc_dai));
#else
    ret = snd_soc_register_component (&pdev->dev, mc_component, mc_dai, ARRAY_SIZE (mc_dai));
#endif
    if (ret < 0)
    {
        error ("cannot register component. %d", ret);
        return ret;
    }

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev)
#else
static int pdev_remove (struct platform_device *pdev)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    snd_soc_unregister_component (&pdev->dev);
#else
    snd_soc_unregister_platform (&pdev->dev);
#endif

    info ("done.");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return 0;
#endif
}

module_platform_driver (pdev_driver);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG SIC Mixer Capture alsa driver");
MODULE_LICENSE ("GPL");
