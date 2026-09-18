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

/** @file bc.c
 *
 *  buffer control ALSA driver
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2021.02.10
 *
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
#include <linux/dma-mapping.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <sound/soc.h>

#include "fwload_wov.h"
#include "hma_alloc.h"
#include "log.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define PERIOD_SIZE             (256/*sample*/ * 8/*channel*/ * 4/*byte*/)

// AUD_REGISTER -> PERI_CTRL -> AEC_SAI
#define REG_OFF_SAIINTCLR           (0x00A4/4)
#define REG_OFF_SAICTRL             (0x0600/4)
#define REG_OFF_SAIEN               (0x0604/4)
#define REG_OFF_SAI_BC_CTRL         (0x0610/4)
#define REG_OFF_SAI_BC_STR_ADDR     (0x0620/4)
#define REG_OFF_SAI_BC_END_ADDR     (0x0624/4)
#define REG_OFF_SAI_BC_READ_ADDR    (0x0628/4)
#define REG_OFF_SAI_BC_AF_LVL       (0x062C/4)
#define REG_OFF_SAI_BC_INT_LVL      (0x0630/4)
#define REG_OFF_SAI_BC_WPTR_STATUS  (0x0634/4)
#define REG_OFF_SAI_INT_CPU_CTRL    (0x0640/4)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)	    logm_trace(aud_bc,fmt,##args)
#define debug(fmt,args...)	    logm_debug(aud_bc,fmt,##args)
#define info(fmt,args...)	    logm_info(aud_bc,fmt,##args)
#define noti(fmt,args...)	    logm_noti(aud_bc,fmt,##args)
#define warn(fmt,args...)	    logm_warning(aud_bc,fmt,##args)
#define error(fmt,args...)	    logm_error(aud_bc,fmt,##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct bc_priv
{
    struct snd_pcm_substream *substream;

    volatile uint32_t *reg;

    phys_addr_t dma_addr;
    unsigned int dma_size;
    void *dma_vaddr;
    int wr_off;

    int irq_num;

    uint32_t flags;
#define FLAG_OUTPUT     (1<<0)
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
static void _hal_int_clear (volatile uint32_t * reg);
static void _hal_int_enable (volatile uint32_t * reg);
static void _hal_int_disable (volatile uint32_t * reg);
static void _hal_init (volatile uint32_t * reg);
static void _hal_reset (volatile uint32_t * reg, bool on);
static void _hal_enable (volatile uint32_t * reg);
static void _hal_disable (volatile uint32_t * reg);
static bool _hal_is_busy (volatile uint32_t * reg);
static void _hal_buffer_init (volatile uint32_t * reg, uint32_t start, uint32_t size);
static uint32_t _hal_buffer_get_write (volatile uint32_t * reg);
static void _hal_buffer_set_read (volatile uint32_t * reg, uint32_t address);
static irqreturn_t handle_irq (int irq, void *dev);
static int bc_hw_init (struct bc_priv *p, unsigned int bc_buffer_size);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
static int bc_open (struct snd_pcm_substream *substream);
static int bc_close (struct snd_pcm_substream *substream);
static int bc_hw_params (struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params);
static int bc_hw_free (struct snd_pcm_substream *substream);
static int bc_prepare (struct snd_pcm_substream *substream);
static int bc_trigger (struct snd_pcm_substream *substream, int cmd);
static snd_pcm_uframes_t bc_pointer (struct snd_pcm_substream *substream);
static int bc_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma);
static int bc_ack (struct snd_pcm_substream *substream);
static int bc_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd);
static void bc_pcm_free (struct snd_pcm *pcm);
#else
static int bc_open (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int bc_close (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int bc_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params);
static int bc_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int bc_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int bc_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd);
static snd_pcm_uframes_t bc_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int bc_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma);
static int bc_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int bc_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd);
static void bc_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int bc_probe (struct snd_soc_component *component);
static void bc_remove (struct snd_soc_component *component);
#else
static int bc_probe (struct snd_soc_platform *platform);
static int bc_remove (struct snd_soc_platform *platform);
#endif
static int bc_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt);
static int bc_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static void bc_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int bc_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai);
static int bc_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int bc_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);;
static int pdev_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev);
#else
static int pdev_remove (struct platform_device *pdev);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
logm_define (aud_bc, log_level_noti);

static struct snd_pcm_hardware bc_pcm_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S32_LE,
    .rates = SNDRV_PCM_RATE_48000,
    .rate_min = 48000,
    .rate_max = 48000,
    .channels_min = 8,
    .channels_max = 8,
    .period_bytes_min = PERIOD_SIZE,
    .period_bytes_max = PERIOD_SIZE,
    .periods_min = 2,
    .periods_max = UINT_MAX,
    .buffer_bytes_max = PERIOD_SIZE * 32,
    .fifo_size = 4,
};

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
static const struct snd_pcm_ops bc_pcm_ops = {
    .open = bc_open,
    .close = bc_close,
    .ioctl = snd_pcm_lib_ioctl,
    .hw_params = bc_hw_params,
    .hw_free = bc_hw_free,
    .prepare = bc_prepare,
    .trigger = bc_trigger,
    .pointer = bc_pointer,
    .mmap = bc_mmap,
    .ack = bc_ack,
};
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver bc_component = {
#else
static const struct snd_soc_platform_driver bc_platform = {
#endif
    .probe = bc_probe,
    .remove = bc_remove,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    .pcm_new = bc_pcm_new,
    .pcm_free = bc_pcm_free,
    .ops = &bc_pcm_ops,
    .compr_ops = NULL,          //bc_compr_ops,
#else
    .pcm_construct  = bc_pcm_new,
    .pcm_destruct   = bc_pcm_free,
    .open = bc_open,
    .close = bc_close,
    .hw_params = bc_hw_params,
    .hw_free = bc_hw_free,
    .prepare = bc_prepare,
    .trigger = bc_trigger,
    .pointer = bc_pointer,
    .mmap = bc_mmap,
    .ack = bc_ack,
    .compress_ops = NULL,
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    .name = "lgsic-bc",
#endif
};

static const struct snd_soc_dai_ops bc_dai_ops = {
    .set_fmt = bc_dai_set_fmt,
    .startup = bc_dai_startup,
    .shutdown = bc_dai_shutdown,
    .hw_params = bc_dai_hw_params,
    .hw_free = bc_dai_hw_free,
    .prepare = bc_dai_prepare,
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver bc_component[] = {
    {.name = "lgsic-bc",},
};
#endif

static struct snd_soc_dai_driver bc_dai[] = {
    {
            .name = "lgsic-bc",
            .id = 0,
            .capture = {
                    .channels_min = 8,
                    .channels_max = 8,
                    .rates = SNDRV_PCM_RATE_48000,
                    .formats = SNDRV_PCM_FMTBIT_S32_LE,
                },
            .ops = &bc_dai_ops,
        },
};

static struct platform_driver pdev_driver = {
    .driver = {
            .name = "lgsic-bc",
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

static char *bc_poolname = "audio_buffer";
module_param (bc_poolname, charp, 0644);

/*==============================================================================
    Implementation Group
==============================================================================*/
static void _hal_int_clear (volatile uint32_t * reg)
{
    reg[REG_OFF_SAIINTCLR] |= 1 << 5;
}

static void _hal_int_enable (volatile uint32_t * reg)
{
    reg[REG_OFF_SAI_BC_CTRL] |= (1 << 3);
}

static void _hal_int_disable (volatile uint32_t * reg)
{
    reg[REG_OFF_SAIEN] &= ~(1 << 0);
}

static void _hal_init (volatile uint32_t * reg)
{
    reg[REG_OFF_SAICTRL] = 0x03;
    reg[REG_OFF_SAI_BC_CTRL] |= (0x03 << 4);
    reg[REG_OFF_SAI_BC_AF_LVL] = 0;
    reg[REG_OFF_SAI_BC_INT_LVL] = PERIOD_SIZE;
}

static void _hal_reset (volatile uint32_t * reg, bool on)
{
    if (on)
        reg[REG_OFF_SAI_BC_CTRL] |= 1 << 1;
    else
        reg[REG_OFF_SAI_BC_CTRL] &= ~(1 << 1);
}

static void _hal_enable (volatile uint32_t * reg)
{
    reg[REG_OFF_SAIEN] |= 1 << 0;
}

static void _hal_disable (volatile uint32_t * reg)
{
    reg[REG_OFF_SAIEN] &= ~(1 << 0);
}

static bool _hal_is_busy (volatile uint32_t * reg)
{
    return ! !((reg[REG_OFF_SAI_BC_CTRL] >> 16) & 0x3);
}

static void _hal_buffer_init (volatile uint32_t * reg, uint32_t start, uint32_t size)
{
    reg[REG_OFF_SAI_BC_STR_ADDR] = start;
    reg[REG_OFF_SAI_BC_END_ADDR] = start + size;
    reg[REG_OFF_SAI_BC_READ_ADDR] = start;
}

static uint32_t _hal_buffer_get_write (volatile uint32_t * reg)
{
    return reg[REG_OFF_SAI_BC_WPTR_STATUS];
}

static void _hal_buffer_set_read (volatile uint32_t * reg, uint32_t address)
{
    reg[REG_OFF_SAI_BC_READ_ADDR] = address;
}

static irqreturn_t handle_irq (int irq, void *dev)
{
    struct bc_priv *p = dev;
#ifndef CHIP_TYPE_FPGA
    uint32_t wr_offset = _hal_buffer_get_write (p->reg) - fwloadwov_wovbus_addr (p->dma_addr);
#else
    uint32_t wr_offset = _hal_buffer_get_write (p->reg) - (p->dma_addr);
#endif

    debug ("irq %d\n", irq);

    if (p->wr_off < wr_offset)
    {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
        dcache_inval_poc((unsigned long)(p->dma_vaddr + p->wr_off), (unsigned long)(p->dma_vaddr + wr_offset));
#else
        __dma_map_area (p->dma_vaddr + p->wr_off, wr_offset - p->wr_off, DMA_FROM_DEVICE);
#endif
    }
    else
    {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
        dcache_inval_poc((unsigned long)(p->dma_vaddr + p->wr_off), (unsigned long)(p->dma_vaddr + p->dma_size));
        dcache_inval_poc((unsigned long)(p->dma_vaddr), (unsigned long)(p->dma_vaddr + wr_offset));
#else
        __dma_map_area (p->dma_vaddr + p->wr_off, p->dma_size - p->wr_off, DMA_FROM_DEVICE);
        __dma_map_area (p->dma_vaddr, wr_offset, DMA_FROM_DEVICE);
#endif
    }

    p->wr_off = wr_offset;

    _hal_int_clear (p->reg);

    snd_pcm_period_elapsed (p->substream);

    return IRQ_HANDLED;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_open (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int bc_open (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    int ret;

    info ("\n");
    info ("name %s\n", substream->name);
    info ("pcm name %s\n", substream->pcm->name);
    info ("pcm card name %s\n", substream->pcm->card->shortname);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu dai name %s -> %s\n", soc_pcm_rtd->cpu_dai->name, soc_pcm_rtd->codec_dai->name);
#endif
    info ("reg %p\n", p->reg);
    info ("irq %d\n", p->irq_num);

    snd_soc_set_runtime_hwparams (substream, &bc_pcm_hardware);

    _hal_int_enable (p->reg);
    p->substream = substream;
    ret =
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
        request_irq (p->irq_num, handle_irq, IRQF_SHARED | IRQF_TRIGGER_HIGH,
        cpu_dai->name, p);
#else
        request_irq (p->irq_num, handle_irq, IRQF_SHARED | IRQF_TRIGGER_HIGH,
        soc_pcm_rtd->cpu_dai->name, p);
#endif
    if (ret < 0)
    {
        error ("cannot register irq. %d\n", p->irq_num);
        return ret;
    }

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0))
static int bc_close (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int bc_close (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    info ("\n");
    _hal_int_disable (p->reg);
    free_irq (p->irq_num, p);
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#else
static int bc_hw_params (struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    const struct snd_interval *intv;

    /* dma buffer */
    p->dma_size = bc_pcm_hardware.buffer_bytes_max;
    p->dma_addr = hma_alloc_user (bc_poolname, p->dma_size, 1024, "cap_spk");
    if (!p->dma_addr)
    {
        error ("no mem for dma\n");
        return -ENOMEM;
    }
    p->dma_vaddr = hma_map_cache (p->dma_addr, p->dma_size);
    if (!p->dma_vaddr)
    {
        error ("cannot map dma buffer\n");
        hma_free (bc_poolname, p->dma_addr);
        return -EIO;
    }

    substream->dma_buffer.addr = p->dma_addr;
    substream->dma_buffer.area = p->dma_vaddr;
    substream->dma_buffer.bytes = p->dma_size;

    info ("\n");
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
static int bc_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int bc_hw_free (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    info ("\n");
    snd_pcm_set_runtime_buffer (substream, NULL);

    hma_unmap (p->dma_vaddr);
    hma_free (bc_poolname, p->dma_addr);

    return 0;
}

static int bc_hw_init (struct bc_priv *p, unsigned int bc_buffer_size)
{
    /* wait hardware busy */
    while (_hal_is_busy (p->reg));

    /* reset hardware ant configure */
    _hal_reset (p->reg, true);

    _hal_init (p->reg);

#ifndef CHIP_TYPE_FPGA
    _hal_buffer_init (p->reg, fwloadwov_wovbus_addr (p->dma_addr), bc_buffer_size);
#else
    _hal_buffer_init (p->reg, p->dma_addr, bc_buffer_size);
#endif

    _hal_reset (p->reg, false);

    p->wr_off = 0;

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int bc_prepare (struct snd_pcm_substream *substream)
#endif
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    info ("buffer_size %lu(%zd)\n", runtime->buffer_size, frames_to_bytes (runtime,
            runtime->buffer_size));

    bc_hw_init (p, frames_to_bytes (runtime, runtime->buffer_size));

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd)
#else
static int bc_trigger (struct snd_pcm_substream *substream, int cmd)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    info ("\n");
    switch (cmd)
    {
        case SNDRV_PCM_TRIGGER_STOP:
            info ("stop\n");
            _hal_disable (p->reg);
            break;

        case SNDRV_PCM_TRIGGER_START:
            info ("start\n");
            _hal_enable (p->reg);
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
static snd_pcm_uframes_t bc_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static snd_pcm_uframes_t bc_pointer (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    uint32_t hw_ptr;
    snd_pcm_uframes_t ret;

#ifndef CHIP_TYPE_FPGA
    hw_ptr = _hal_buffer_get_write (p->reg) - fwloadwov_wovbus_addr (p->dma_addr);
#else
    hw_ptr = _hal_buffer_get_write (p->reg) - (p->dma_addr);
#endif
    if (hw_ptr > p->dma_size)
    {
        error ("wrong hardware pointer. hw_ptr 0x%x, dma_size 0x%x\n", hw_ptr, p->dma_size);
        hw_ptr = 0;
    }

    ret = bytes_to_frames (substream->runtime, hw_ptr);
    debug ("hw_ptr 0x%05x, frames %4ld/%ld\n", hw_ptr, ret, substream->runtime->buffer_size);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#else
static int bc_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#endif
{
    int ret;

    info ("\n");
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
    vm_flags_set (vma, VM_DONTEXPAND | VM_DONTDUMP);
#else
    vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
#endif
    ret = remap_pfn_range (vma, vma->vm_start,
        substream->dma_buffer.addr >> PAGE_SHIFT, vma->vm_end - vma->vm_start, vma->vm_page_prot);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int bc_ack (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct bc_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct bc_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    snd_pcm_sframes_t sw_ptr;

    sw_ptr = runtime->control->appl_ptr % runtime->buffer_size;
    debug ("sw_ptr %4ld/%ld\n", sw_ptr, runtime->buffer_size);

#ifndef CHIP_TYPE_FPGA
    _hal_buffer_set_read (p->reg, fwloadwov_wovbus_addr (p->dma_addr) + frames_to_bytes (runtime,
            sw_ptr));
#else
    _hal_buffer_set_read (p->reg, p->dma_addr + frames_to_bytes (runtime, sw_ptr));
#endif
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int bc_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd)
#else
static int bc_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd)
#endif
{
    info ("\n");
    info ("dai_link %p\n", soc_pcm_rtd->dai_link);
    if (soc_pcm_rtd->dai_link)
        info ("dai_link name %s(%s)\n", soc_pcm_rtd->dai_link->name,
            soc_pcm_rtd->dai_link->stream_name);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu_dai name %s(%p)\n", soc_pcm_rtd->cpu_dai->name,
        snd_soc_dai_get_drvdata (soc_pcm_rtd->cpu_dai));
    info ("codec_dai name %s\n", soc_pcm_rtd->codec_dai->name);
#endif
    info ("device name %s\n", dev_name (soc_pcm_rtd->dev));
    info ("card name %s\n", soc_pcm_rtd->card->name);
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void bc_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm)
#else
static void bc_pcm_free (struct snd_pcm *pcm)
#endif
{
    info ("\n");
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int bc_probe (struct snd_soc_component *component)
#else
static int bc_probe (struct snd_soc_platform *platform)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct platform_device *pdev = to_platform_device (component->dev);
#else
    struct platform_device *pdev = to_platform_device (platform->dev);
#endif
    struct resource *res;
    struct bc_priv *p;
    int size;
    info ("pdev name %s.%d\n", pdev->name, pdev->id);
    p = kzalloc (sizeof (struct bc_priv), GFP_KERNEL);
    if (!p)
        return -ENOMEM;
    p->irq_num = platform_get_irq (pdev, 0);
    info ("irq %d\n", p->irq_num);
    res = platform_get_resource_byname (pdev, IORESOURCE_DMA, "output");
    if (res)
        p->flags |= FLAG_OUTPUT;
    info ("direction %sput\n", p->flags & FLAG_OUTPUT ? "out" : "in");
    /* register mapping */
    res = platform_get_resource_byname (pdev, IORESOURCE_MEM, "reg");
    if (!res)
    {
        error ("no \"reg\" resource\n");
        kfree (p);
        return -EINVAL;
    }
    info ("reg start %pap -> %pap\n", &res->start, &res->end);
    size = res->end - res->start + 1;
    p->reg = ioremap (res->start, size);
    if (!p->reg)
    {
        error ("cannot remap reg. %pap(0x%x)\n", &res->start, size);
        kfree (p);
        return -EIO;
    }
    info ("reg %p\n", p->reg);
    dev_set_drvdata (&pdev->dev, p);
    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void bc_remove (struct snd_soc_component *component)
{
    struct bc_priv *p = dev_get_drvdata (component->dev);

    info ("\n");
    iounmap (p->reg);
    kfree (p);
    info ("\n");
}
#else
static int bc_remove (struct snd_soc_platform *platform)
{
    struct bc_priv *p = dev_get_drvdata (platform->dev);

    info ("\n");
    iounmap (p->reg);
    kfree (p);
    info ("\n");
    return 0;
}
#endif

static int bc_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt)
{
    info ("\n");
    return 0;
}

static int bc_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
    return 0;
}

static void bc_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
}

static int bc_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai)
{
    info ("\n");
    return 0;
}

static int bc_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("\n");
    return 0;
}

static int bc_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("\n");
    return 0;
}

static int pdev_probe (struct platform_device *pdev)
{
    int ret;
    info ("probe.. %s\n", pdev->name);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_platform (&pdev->dev, &bc_platform);
    if (ret < 0)
    {
        error ("cannot register_platform(). %d\n", ret);
        return ret;
    }
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_component (&pdev->dev, &bc_component, bc_dai, ARRAY_SIZE (bc_dai));
#else
    ret = snd_soc_register_component (&pdev->dev, bc_component, bc_dai, ARRAY_SIZE (bc_dai));
#endif
    if (ret < 0)
    {
        error ("cannot register component. %d\n", ret);
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
    info ("done.\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return 0;
#endif
}

module_platform_driver (pdev_driver);
MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG SIC BC alsa driver");
MODULE_LICENSE ("GPL");
