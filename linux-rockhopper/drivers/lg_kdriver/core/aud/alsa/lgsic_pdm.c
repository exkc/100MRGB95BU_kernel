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

/** @file pdm.c
 *
 *  driver implementation for pdm device.
 *
 *  @author Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version    0.1
 *  @date       2019.12.26
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/
#define ENABLE_HW_UPDATE

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <sound/soc.h>

#include "os_util.h"
#include "hma_alloc.h"
#include "fwload_wov.h"

#ifndef CHIP_TYPE_FPGA
#if defined (CHIP_NAME_o22)
#include "chip/o22/sys/ctop_ctrl_reg_o22.h"
#elif defined (CHIP_NAME_m23)
#include "chip/m23/sys/ctop_ctrl_reg_m23.h"
#elif defined (CHIP_NAME_o24)
#include "chip/o24/sys/ctop_ctrl_reg_o24.h"
#elif defined (CHIP_NAME_o26)
#include "chip/o26/sys/ctop_ctrl_reg_o26.h"
#else
#error "Please Define Chip Definition"
#endif
#endif

#include "pdm.h"
#include "pdm_reg.h"
#include "log.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define PDM_CTRL                (0x0004/4)
#define PDM_INT                 (0x0008/4)
#define PDM_DMAC                (0x000C/4)
#define PDM_DMADSTADDR0         (0x0010/4)
#define PDM_DMADSTADDR1         (0x0014/4)
#define PDM_FIFO                (0x0018/4)
#define VAD_WAE_B_a1            (0x001C/4)
#define VAD_WAE_a2_c            (0x0020/4)
#define PDM_DMA_CNT             (0x0024/4)
#define PDM_ENG_ZCR_COEF01      (0x0028/4)
#define PDM_ENG_ZCR_COEF23      (0x002C/4)
#define PDM_ENG_ZCR_COEF4_QFOM  (0x0030/4)
#define PDM_CORE_CTRL           (0x0034/4)
#define PDM_FIFO_CNT            (0x0038/4)
#define PDM_FIFO_DATA           (0x003C/4)
#define PDM_VAD_SNR_TH          (0x0040/4)
#define PDM_NS_STEP_SIZE        (0x0054/4)
#define PDM_CORE_CTRL2          (0x0058/4)
#define VAD_INTR_ADDR           (0x0060/4)
#define VAD_INTR_ADDR_CLEAR     (0x0064/4)
#define VAD_INTR_NUM            (0x0068/4)
#define DMA_INTR_NUM            (0x0070/4)

#define PCM_BUFFER_SIZE         (0x0140/4)
#define DMA0_ADDR_UPDATE        (0x0144/4)
#define DMA1_ADDR_UPDATE        (0x0148/4)

#define BYTES_PER_WORD          (4)
#define NUM_OF_CHANNEL          (2)
#define SAMPLES_IN_PERIOD       (256)
#define WORDS_IN_PERIOD         (SAMPLES_IN_PERIOD * NUM_OF_CHANNEL)
#define BYTES_IN_PERIOD         (WORDS_IN_PERIOD * BYTES_PER_WORD)
#define MAX_BUFFER_BYTES        (BYTES_IN_PERIOD * 32)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)	    logm_trace(aud_pdm,fmt,##args)
#define debug(fmt,args...)	    logm_debug(aud_pdm,fmt,##args)
#define info(fmt,args...)	    logm_info(aud_pdm,fmt,##args)
#define noti(fmt,args...)	    logm_noti(aud_pdm,fmt,##args)
#define warn(fmt,args...)	    logm_warning(aud_pdm,fmt,##args)
#define error(fmt,args...)	    logm_error(aud_pdm,fmt,##args)

#define get_tuning_data(type) ((mic_tuning_data[type] == -1)? \
                                default_mic_tuning_data[type] : mic_tuning_data[type])

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct pdm_priv
{
    struct snd_pcm_substream *substream;

    volatile uint32_t *reg;

    phys_addr_t dma_addr;
    void *dma_vaddr;
    unsigned int dma_size;
    unsigned int cur_dma_size;

    int cur_dma;
    int unit_size;

    int wr_off;
    int rd_off;

    int irq_num;
};

enum
{ HPGAIN, ADCHPD, SOFT_MUTE, SINC_SHIFT, S_CYCLES, DATA_VALID_DELAY, WOV_PDM_CLKOUT_MUX_SEL };

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
static int set_fwloadwov_mic_tuning_data (void);
static irqreturn_t handle_irq (int irq, void *dev);
static int pdm_hw_load_filter (struct pdm_priv *p);
static int pdm_hw_init (struct pdm_priv *p, struct snd_pcm_runtime *runtime);
static int pdm_hw_start (struct pdm_priv *p);
static int pdm_hw_stop (struct pdm_priv *p);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
static int pdm_open (struct snd_pcm_substream *substream);
static int pdm_close (struct snd_pcm_substream *substream);
static int pdm_hw_params (struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params);
static int pdm_hw_free (struct snd_pcm_substream *substream);
static int pdm_prepare (struct snd_pcm_substream *substream);
static int pdm_trigger (struct snd_pcm_substream *substream, int cmd);
static snd_pcm_uframes_t pdm_pointer (struct snd_pcm_substream *substream);
static int pdm_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma);
static int pdm_ack (struct snd_pcm_substream *substream);
static int pdm_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd);
static void pdm_pcm_free (struct snd_pcm *pcm);
#else
static int pdm_open (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int pdm_close (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int pdm_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params);
static int pdm_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int pdm_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int pdm_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd);
static snd_pcm_uframes_t pdm_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int pdm_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma);
static int pdm_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream);
static int pdm_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd);
static void pdm_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int pdm_probe (struct snd_soc_component *component);
static void pdm_remove (struct snd_soc_component *component);
#else
static int pdm_probe (struct snd_soc_platform *platform);
static int pdm_remove (struct snd_soc_platform *platform);
#endif
static int pdm_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt);
static int pdm_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static void pdm_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int pdm_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai);
static int pdm_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int pdm_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int pdev_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev);
#else
static int pdev_remove (struct platform_device *pdev);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
logm_define (aud_pdm, log_level_info);

static struct snd_pcm_hardware pdm_pcm_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
    .rates = SNDRV_PCM_RATE_8000_48000,
    .rate_min = 8000,
    .rate_max = 48000,
    .channels_min = NUM_OF_CHANNEL,
    .channels_max = NUM_OF_CHANNEL,
    .period_bytes_min = BYTES_IN_PERIOD,
    .period_bytes_max = BYTES_IN_PERIOD,
    .periods_min = 2,
    .periods_max = MAX_BUFFER_BYTES / BYTES_IN_PERIOD * 8,
    .buffer_bytes_max = MAX_BUFFER_BYTES,
    .fifo_size = 4,
};

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
static const struct snd_pcm_ops pdm_pcm_ops = {
    .open = pdm_open,
    .close = pdm_close,
    .ioctl = snd_pcm_lib_ioctl,
    .hw_params = pdm_hw_params,
    .hw_free = pdm_hw_free,
    .prepare = pdm_prepare,
    .trigger = pdm_trigger,
    .pointer = pdm_pointer,
    .mmap = pdm_mmap,
    .ack = pdm_ack,
};
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver pdm_component = {
#else
static const struct snd_soc_platform_driver pdm_platform = {
#endif
    .probe = pdm_probe,
    .remove = pdm_remove,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    .pcm_new = pdm_pcm_new,
    .pcm_free = pdm_pcm_free,
    .ops = &pdm_pcm_ops,
    .compr_ops = NULL,          //pdm_compr_ops,
#else
    .pcm_construct = pdm_pcm_new,
    .pcm_destruct = pdm_pcm_free,
    .open = pdm_open,
    .close = pdm_close,
    .hw_params = pdm_hw_params,
    .hw_free = pdm_hw_free,
    .prepare = pdm_prepare,
    .trigger = pdm_trigger,
    .pointer = pdm_pointer,
    .mmap = pdm_mmap,
    .ack = pdm_ack,
    .compress_ops = NULL,
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    .name = "lgsic-pdm",
#endif
};

static const struct snd_soc_dai_ops pdm_dai_ops = {
    .set_fmt = pdm_dai_set_fmt,
    .startup = pdm_dai_startup,
    .shutdown = pdm_dai_shutdown,
    .hw_params = pdm_dai_hw_params,
    .hw_free = pdm_dai_hw_free,
    .prepare = pdm_dai_prepare,
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver pdm_component[] = {
    {.name = "lgsic-pdm",},
};
#endif

static struct snd_soc_dai_driver pdm_dai[] = {
    {
            .name = "lgsic-pdm",
            .id = 0,
            .capture = {
                    .channels_min = 2,
                    .channels_max = 2,
                    .rates = SNDRV_PCM_RATE_8000_48000,
                    .formats =
                    SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
                },
            .ops = &pdm_dai_ops,
        },
};

static struct platform_driver pdev_driver = {
    .driver = {
            .name = "lgsic-pdm",
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

static const int default_mic_tuning_data[] = {
#if defined (CHIP_NAME_m23)
    [HPGAIN] = 0xB,
    [ADCHPD] = 0x1,
    [SOFT_MUTE] = 0x0,
    [SINC_SHIFT] = 0x0,
    [S_CYCLES] = 0x0,
    [DATA_VALID_DELAY] = 0x1,
    [WOV_PDM_CLKOUT_MUX_SEL] = 0x3,
#else
/*  https://harmony.lge.com:8443/issue/browse/SICREQ-603
    unsigned int highpass_filter_on_off;        -> 1
    unsigned int highpass_filter_coeff;         -> 3
    unsigned int gain_soft_mute;                -> 0
    unsigned int gain_sinc_shift;               -> 16
    unsigned int s_cycles;                      -> 0
    unsigned int pdm_data_valid_delay;          -> 0
*/
    [HPGAIN] = 0x3,
#ifdef SUPPORT_SOUNDBAR
    [ADCHPD] = 0x0,
#else
    [ADCHPD] = 0x1,
#endif
    [SOFT_MUTE] = 0x0,
    [SINC_SHIFT] = 0x10,
    [S_CYCLES] = 0x0,
    [DATA_VALID_DELAY] = 0x0,
    [WOV_PDM_CLKOUT_MUX_SEL] = 0x1,
#endif
};

static int mic_tuning_data[] = { -1, -1, -1, -1, -1, -1, -1 };

static int mic_tuning_data_count = 0;
module_param_array (mic_tuning_data, int, &mic_tuning_data_count, 0644);
module_param (mic_tuning_data_count, int, 0644);

static bool pull_down = false;
module_param (pull_down, bool, 0644);

static int clock_source = -1;
module_param (clock_source, int, 0644);

static char *pdm_poolname = "audio_buffer";
module_param (pdm_poolname, charp, 0644);

/*------------------------------------------------------------------------------
    Static Function Implementation
 ------------------------------------------------------------------------------*/
static int set_fwloadwov_mic_tuning_data (void)
{
    struct fwload_wov_mic_tuning_data data[2] = { };

    data[0].highpass_filter_on_off = (unsigned int) default_mic_tuning_data[ADCHPD];
    data[0].highpass_filter_coeff = (unsigned int) default_mic_tuning_data[HPGAIN];
    data[0].gain_soft_mute = (unsigned int) default_mic_tuning_data[SOFT_MUTE];
    data[0].gain_sinc_shift = (unsigned int) default_mic_tuning_data[SINC_SHIFT];
    data[0].s_cycles = (unsigned int) default_mic_tuning_data[S_CYCLES];
    data[0].pdm_data_valid_delay = (unsigned int) default_mic_tuning_data[DATA_VALID_DELAY];
    data[0].wov_pdm_clkout_mux_sel = (unsigned int) default_mic_tuning_data[WOV_PDM_CLKOUT_MUX_SEL];

    data[1].highpass_filter_on_off = (unsigned int) mic_tuning_data[ADCHPD];
    data[1].highpass_filter_coeff = (unsigned int) mic_tuning_data[HPGAIN];
    data[1].gain_soft_mute = (unsigned int) mic_tuning_data[SOFT_MUTE];
    data[1].gain_sinc_shift = (unsigned int) mic_tuning_data[SINC_SHIFT];
    data[1].s_cycles = (unsigned int) mic_tuning_data[S_CYCLES];
    data[1].pdm_data_valid_delay = (unsigned int) mic_tuning_data[DATA_VALID_DELAY];
    data[1].wov_pdm_clkout_mux_sel = (unsigned int) mic_tuning_data[WOV_PDM_CLKOUT_MUX_SEL];

    fwload_wov_set_mic_tuning_data (data);

    noti ("highpass_filter_on_off[ADCHPD]         = %d\n", default_mic_tuning_data[ADCHPD]);
    noti ("highpass_filter_coeff[HPGAIN]          = %d\n", default_mic_tuning_data[HPGAIN]);
    noti ("gain_soft_mute[SOFT_MUTE]              = %d\n", default_mic_tuning_data[SOFT_MUTE]);
    noti ("gain_sinc_shift[SINC_SHIFT]            = %d\n", default_mic_tuning_data[SINC_SHIFT]);
    noti ("s_cycles[S_CYCLES]                     = %d\n", default_mic_tuning_data[S_CYCLES]);
    noti ("pdm_data_valid_delay[DATA_VALID_DELAY] = %d\n",
        default_mic_tuning_data[DATA_VALID_DELAY]);
    return 0;
}

static irqreturn_t handle_irq (int irq, void *dev)
{
    struct pdm_priv *p = dev;
    REG_MMR_PDM_INT_T pdm_int;
    REG_MMR_DMA_INTR_NUM_T dma_intr_num;

    // Read PDM interrupt status
    pdm_int.w = p->reg[PDM_INT];

    // Read DMA interrupt status
    dma_intr_num.w = p->reg[DMA_INTR_NUM];

    // Clear PDM interrupt status
    p->reg[PDM_INT] = pdm_int.w;

    debug ("irq %d 0x%08X 0x%08X\n", irq, dma_intr_num.f.dma_intr_num, pdm_int.f.raw_status_clear);

    // Process DMA interrupt
    if (pdm_int.f.raw_status_clear & 0x01)
    {
#ifdef ENABLE_HW_UPDATE
#define INVALID_ADDRESS     (0xFFFFFFFF)
#ifndef CHIP_TYPE_FPGA
        const unsigned int start_addr = fwloadwov_wovbus_addr (p->dma_addr);
#else
        const unsigned int start_addr = (p->dma_addr);
#endif
        const unsigned int end_addr = start_addr + p->dma_size;
        const unsigned int last_addr = end_addr - p->unit_size;
        unsigned int wr_addrs[2] = { INVALID_ADDRESS, INVALID_ADDRESS };
        int i;

        for (i = 0; i < 2; i++)
        {
            if (dma_intr_num.f.dma_intr_num & (1 << i))
            {
                unsigned int wr_addr = p->reg[(i == 0) ? DMA0_ADDR_UPDATE : DMA1_ADDR_UPDATE];

                if ((wr_addr < start_addr) || (end_addr <= wr_addr))
                {
                    error ("Wrong write address [%d]0x%08X\n", i, wr_addr);
                    continue;
                }

                // DMAx_ADDR_UPDATE is current writing start address. So calculating written end address
                wr_addrs[i] = (wr_addr == start_addr) ? last_addr : wr_addr - p->unit_size;
            }
        }

        if (wr_addrs[0] == INVALID_ADDRESS && wr_addrs[1] == INVALID_ADDRESS)
        {
            error ("All write address are invalid\n");
        }
        else
        {
            unsigned int wr_addr;
            unsigned int wr_offset;

            // Find last written address
            if ((wr_addrs[0] == INVALID_ADDRESS) || (wr_addrs[1] == INVALID_ADDRESS))
            {
                wr_addr = (wr_addrs[0] == INVALID_ADDRESS) ? wr_addrs[1] : wr_addrs[0];
            }
            else if (((wr_addrs[0] == start_addr) && (wr_addrs[1] == last_addr)) ||
                ((wr_addrs[1] == start_addr) && (wr_addrs[0] == last_addr)))
            {
                wr_addr = start_addr;
            }
            else
            {
                wr_addr = (wr_addrs[0] < wr_addrs[1]) ? wr_addrs[1] : wr_addrs[0];
            }

            wr_offset = wr_addr - fwloadwov_wovbus_addr (p->dma_addr);

            if (wr_offset < p->wr_off)
            {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
                dcache_inval_poc((unsigned long)(p->dma_vaddr + p->wr_off), (unsigned long)(p->dma_vaddr + p->dma_size));
                dcache_inval_poc((unsigned long)(p->dma_vaddr), (unsigned long)(p->dma_vaddr + wr_offset));
#else
                __dma_map_area (p->dma_vaddr + p->wr_off, p->dma_size - p->wr_off, DMA_FROM_DEVICE);
                __dma_map_area (p->dma_vaddr, wr_offset, DMA_FROM_DEVICE);
#endif
            }
            else
            {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
                dcache_inval_poc((unsigned long)(p->dma_vaddr + p->wr_off), (unsigned long)(p->dma_vaddr + p->dma_size));
#else
                __dma_map_area (p->dma_vaddr + p->wr_off, wr_offset - p->wr_off, DMA_FROM_DEVICE);
#endif
            }

            p->wr_off = wr_offset;

            debug ("Update write offset 0x%08X\n", p->wr_off);
        }
#else //ENABLE_HW_UPDATE
        int next_wroff;

        if (dma_intr_num.f.dma_intr_num & (1 << (p->cur_dma ^ 1)))
        {
            error ("ISR skipped %d! 0x%08X\n", p->cur_dma, dma_intr_num.f.dma_intr_num);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
            dcache_inval_poc((unsigned long)(p->dma_vaddr + p->wr_off), (unsigned long)(p->dma_vaddr + p->wr_off + p->unit_size));
#else
            __dma_map_area (p->dma_vaddr + p->wr_off, p->unit_size, DMA_FROM_DEVICE);
#endif

            p->wr_off += p->unit_size;
            if (p->wr_off >= p->cur_dma_size)
                p->wr_off = 0;
            next_wroff = p->wr_off + p->unit_size;
            if (next_wroff >= p->cur_dma_size)
                next_wroff = 0;

            p->cur_dma ^= 1;
        }

        if (dma_intr_num.f.dma_intr_num & (1 << p->cur_dma))
        {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
            dcache_inval_poc((unsigned long)(p->dma_vaddr + p->wr_off), (unsigned long)(p->dma_vaddr + p->wr_off + p->unit_size));
#else
            __dma_map_area (p->dma_vaddr + p->wr_off, p->unit_size, DMA_FROM_DEVICE);
#endif

            p->wr_off += p->unit_size;
            if (p->wr_off >= p->cur_dma_size)
                p->wr_off = 0;
            next_wroff = p->wr_off + p->unit_size;
            if (next_wroff >= p->cur_dma_size)
                next_wroff = 0;

            p->reg[PDM_DMADSTADDR0 + p->cur_dma] = fwloadwov_wovbus_addr (p->dma_addr) + next_wroff;
            p->cur_dma ^= 1;
        }
        else
        {
            error ("Lost ISR %d!! 0x%08X\n", p->cur_dma, dma_intr_num.f.dma_intr_num);
        }
#endif
    }

    if (pdm_int.f.raw_status_clear & ~0x01)
    {
        warn ("Unexpected interrupt status 0x%08X\n", pdm_int.w);
    }

    snd_pcm_period_elapsed (p->substream);

    return IRQ_HANDLED;
}

static int pdm_hw_load_filter (struct pdm_priv *p)
{
    static const struct
    {
        int offs;
        uint32_t value;
    } filters[] =
    {
        /* *INDENT-OFF* */
        { 0x080/4, 0x001fffff, },
        { 0x084/4, 0x00f6a701, },
        { 0x088/4, 0x00179be5, },
        { 0x08c/4, 0x000cfdc0, },
        { 0x090/4, 0x00095536, },
        { 0x094/4, 0x000cfdc0, },
        { 0x098/4, 0x001fffff, },
        { 0x09c/4, 0x00ed294f, },
        { 0x0a0/4, 0x000fba2a, },
        { 0x0a4/4, 0x000e74c8, },
        { 0x0a8/4, 0x0011bcb6, },
        { 0x0ac/4, 0x000e74c8, },
        { 0x0b0/4, 0x001fffff, },
        { 0x0b4/4, 0x00e37a7b, },
        { 0x0b8/4, 0x00085757, },
        { 0x0bc/4, 0x000e30d7, },
        { 0x0c0/4, 0x001a977d, },
        { 0x0c4/4, 0x000e30d7, },
        { 0x0c8/4, 0x001fffff, },
        { 0x0cc/4, 0x00fb6fd7, },
        { 0x0d0/4, 0x001d7237, },
        { 0x0d4/4, 0x0003ed6b, },
        { 0x0d8/4, 0x0001f3ed, },
        { 0x0dc/4, 0x0003ed6b, },
        { 0x0e0/4, 0x001fffff, },
        { 0x0e4/4, 0x001b6694, },
        { 0x0e8/4, 0x00023a09, },
        { 0x0ec/4, 0x00f9e93f, },
        { 0x0f0/4, 0x00fc58cc, },
        { 0x0f4/4, 0x00000000, },
        { 0x100/4, 0x0042958c, },
        { 0x104/4, 0x00fc80b3, },
        { 0x108/4, 0x00fc56be, },
        { 0x10c/4, 0x00f67c12, },
        { 0x110/4, 0x00021114, },
        { 0x114/4, 0x00000000, },
#ifdef SUPPORT_SOUNDBAR
        { 0x120/4, 0x00104646, },
#else
        { 0x120/4, 0x00134646, },
#endif
        { 0x128/4, 0x001fffff, },
        { 0x12c/4, 0x00fc0b3a, },
        { 0x130/4, 0x001785cc, },
        { 0x134/4, 0x000da716, },
        { 0x138/4, 0x000c0f52, },
        { 0x13c/4, 0x000da716, },
        /* *INDENT-ON* */
    };
    int i;

    for (i = 0; i < ARRAY_SIZE (filters); i++)
        p->reg[filters[i].offs] = filters[i].value;

    return 0;
}

static int pdm_hw_init (struct pdm_priv *p, struct snd_pcm_runtime *runtime)
{
    PDM_REG_T rv;

#ifndef CHIP_TYPE_FPGA
    if (pull_down)
    {
#if defined (CHIP_NAME_o22)
        CTOP_CTRL_O22Ax_RdFL (FUNC_IOMUX_WOV, pad_wov09);
        CTOP_CTRL_O22Ax_Wr01 (FUNC_IOMUX_WOV, pad_wov09, reg_pad_wov_pdm0_datain__pd, 1);
        CTOP_CTRL_O22Ax_WrFL (FUNC_IOMUX_WOV, pad_wov09);
#elif defined (CHIP_NAME_m23)
        CTOP_CTRL_M23Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc06);
        CTOP_CTRL_M23Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc06, reg_pad_wov_pdm0_datain__pd, 1);
        CTOP_CTRL_M23Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc06);
#elif defined (CHIP_NAME_o24)
        CTOP_CTRL_O24Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc_09);
        CTOP_CTRL_O24Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc_09, reg_pad_pdm0_datain__pd, 1);
        CTOP_CTRL_O24Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc_09);
#elif defined (CHIP_NAME_o26)
        CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc13);
        CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc13, reg_pad_pdm0_datain__pd, 1);
#ifdef SUPPORT_SOUNDBAR
        CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc13, reg_pad_pdm1_datain__pd, 1);
#endif
        CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc13);
#else
#error "Please Define Chip Definition"
#endif
    }

#if defined (CHIP_NAME_m23)
    CTOP_CTRL_M23Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc67);
    CTOP_CTRL_M23Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc67, reg_pad_wov_pdm0_datain_mux_sel, 0);
    CTOP_CTRL_M23Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc67, reg_pad_wov_pdm_clkout_mux_sel, 0);
    CTOP_CTRL_M23Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc67);
#elif defined (CHIP_NAME_o24)
    CTOP_CTRL_O24Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc_68);
    CTOP_CTRL_O24Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc_68, reg_pad_pdm0_datain_mux_sel, 2);
    CTOP_CTRL_O24Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc_68, reg_pad_pdm_clkout_mux_sel, 2);
    CTOP_CTRL_O24Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc_68);
#elif defined (CHIP_NAME_o26)
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc70);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc70, reg_pad_pdm0_datain_mux_sel, 2);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc70, reg_pad_pdm_clkout_mux_sel, 2);
#ifdef SUPPORT_SOUNDBAR
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc70, reg_pad_pdm1_datain_mux_sel, 2);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc70, reg_pad_micom_28_mux_sel, 2);
#endif
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc70);
#elif defined (CHIP_NAME_o22)
    CTOP_CTRL_O22Ax_RdFL (FUNC_IOMUX_WOV, pad_wov68);
    CTOP_CTRL_O22Ax_Wr01 (FUNC_IOMUX_WOV, pad_wov68, reg_pad_wov_pdm0_datain_mux_sel, 2);
    CTOP_CTRL_O22Ax_Wr01 (FUNC_IOMUX_WOV, pad_wov68, reg_pad_wov_pdm_clkout_mux_sel, 2);
    CTOP_CTRL_O22Ax_WrFL (FUNC_IOMUX_WOV, pad_wov68);

    if (lx_chip_rev () < LX_CHIP_REV (O22, A1))
    {
        CTOP_CTRL_O22Ax_RdFL (MCRG_CTRL_WOV, crg_main_wov28);
        CTOP_CTRL_O22Ax_Wr01 (MCRG_CTRL_WOV, crg_main_wov28, reg_sel3_aclk_div, 0x0);
        CTOP_CTRL_O22Ax_WrFL (MCRG_CTRL_WOV, crg_main_wov28);

        CTOP_CTRL_O22Ax_RdFL (MCRG_CTRL_WOV, crg_main_wov29);
        CTOP_CTRL_O22Ax_Wr01 (MCRG_CTRL_WOV, crg_main_wov29, reg_sel3_aclk_src, 0x4);
        CTOP_CTRL_O22Ax_WrFL (MCRG_CTRL_WOV, crg_main_wov29);
    }
#else
#error "Please Define Chip Definition"
#endif
#endif

    rv.w = 0;

#if defined (CHIP_NAME_o26)
    rv.pdm_ctrl.f.sel_adc_pcm = 1;
#endif

#ifdef SUPPORT_SOUNDBAR
    rv.pdm_ctrl.f.debugging0 = 1;
#endif

    rv.pdm_ctrl.f.mic_channel = 3;
    if (runtime->format == SNDRV_PCM_FORMAT_S24_LE || runtime->format == SNDRV_PCM_FORMAT_S32_LE)
    {
        /* physical 4byte per sample, 24bit data + sign extension
         *
         * S32_LE 에 대해서도 테스트를 위해 S32_LE 포멧도 함께 설정한다.
         */
        rv.pdm_ctrl.f.pdm_wordlen = 3;
    }
    else
    {
        rv.pdm_ctrl.f.pdm_wordlen = 0;
    }

#ifdef ENABLE_HW_UPDATE
    rv.pdm_ctrl.f.dma_detec_monitor_enable = 1;
#endif

    rv.pdm_ctrl.f.soft_reset = 1;
    p->reg[PDM_CTRL] = rv.w;
    rv.pdm_ctrl.f.soft_reset = 0;
    p->reg[PDM_CTRL] = rv.w;

    rv.w = 0;
    rv.pdm_core_ctrl2.f.sinc_rate = 1536000 / runtime->rate;
    rv.pdm_core_ctrl2.f.mclkdiv = 4;
    p->reg[PDM_CORE_CTRL2] = rv.w;

    p->reg[PDM_DMADSTADDR0] = fwloadwov_wovbus_addr (p->dma_addr);
    p->reg[PDM_DMADSTADDR1] = fwloadwov_wovbus_addr (p->dma_addr) + p->unit_size;

#ifdef ENABLE_HW_UPDATE
    p->reg[PCM_BUFFER_SIZE] = p->dma_size / BYTES_PER_WORD;
#endif

    rv.w = 0;
    rv.pdm_fifo.f.fifo_flush = 1;
    p->reg[PDM_FIFO] = rv.w;

    rv.w = 0;
    rv.pdm_core_ctrl.f.hpgain = get_tuning_data (HPGAIN);
    rv.pdm_core_ctrl.f.adchpd = get_tuning_data (ADCHPD);
    rv.pdm_core_ctrl.f.soft_mute = get_tuning_data (SOFT_MUTE);
    rv.pdm_core_ctrl.f.sinc_shift = get_tuning_data (SINC_SHIFT);
    rv.pdm_core_ctrl.f.s_cycles = get_tuning_data (S_CYCLES);
    rv.pdm_core_ctrl.f.pdm_data_valid_delay = get_tuning_data (DATA_VALID_DELAY);
    rv.pdm_core_ctrl.f.wov_pdm_clkout_mux_sel = get_tuning_data (WOV_PDM_CLKOUT_MUX_SEL);
    p->reg[PDM_CORE_CTRL] = rv.w;
    noti ("[PDM_CORE_CTRL] = 0x%08X\n", rv.w);

    pdm_hw_load_filter (p);

    rv.w = 0;
    rv.pdm_int.f.trigger_interrupt_mask = 1;
    rv.pdm_int.f.interrupt_enable = 1;
    rv.pdm_int.f.destination = 1;
    rv.pdm_int.f.dma_mask = 0xE;
    p->reg[PDM_INT] = rv.w;

    rv.w = 0;
#ifdef ENABLE_HW_UPDATE
    rv.pdm_dmac.f.dma_controll_mode = 0;
#else
    rv.pdm_dmac.f.dma_controll_mode = 1;
#endif
    rv.pdm_dmac.f.total_length = p->unit_size / 4;
    rv.pdm_dmac.f.transfer_size = 16;
    rv.pdm_dmac.f.dma0_start_addr_set_enable = 1;
    rv.pdm_dmac.f.dma1_start_addr_set_enable = 1;
    rv.pdm_dmac.f.dma_channel = 3;
    rv.pdm_dmac.f.burst_length_32_bit_fixed_word_size = 2;
    rv.pdm_dmac.f.transfer_mode = 1;
    p->reg[PDM_DMAC] = rv.w;

    p->cur_dma = 0;
    p->wr_off = 0;
    p->rd_off = 0;

    rv.w = p->reg[PDM_CTRL];
    rv.pdm_ctrl.f.pdm_demodulator_enable = 1;
    p->reg[PDM_CTRL] = rv.w;
    info ("[PDM_CTRL] = 0x%08X\n", rv.w);

    msleep (10);

    return 0;
}

static int pdm_hw_start (struct pdm_priv *p)
{
    PDM_REG_T rv;

    rv.w = p->reg[PDM_DMAC];
    rv.pdm_dmac.f.dma_enable = 1;
    p->reg[PDM_DMAC] = rv.w;

    return 0;
}

static int pdm_hw_stop (struct pdm_priv *p)
{
    PDM_REG_T rv;

    rv.w = p->reg[PDM_DMAC];
    rv.pdm_dmac.f.dma_enable = 0;
    p->reg[PDM_DMAC] = rv.w;

#ifndef SUPPORT_SOUNDBAR   // prevent pop noise at pdm1
    rv.w = p->reg[PDM_CTRL];
    rv.pdm_ctrl.f.pdm_demodulator_enable = 0;
    p->reg[PDM_CTRL] = rv.w;
#endif

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_open (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int pdm_open (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
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

    snd_soc_set_runtime_hwparams (substream, &pdm_pcm_hardware);

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

    /* hardware parameters */
    p->unit_size = BYTES_IN_PERIOD;
    p->cur_dma = 0;
    p->wr_off = 0;
    p->rd_off = 0;

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_close (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int pdm_close (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    pdm_hw_stop (p);

    info ("\n");
    free_irq (p->irq_num, p);

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#else
static int pdm_hw_params (struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    const struct snd_interval *intv;

    /* dma buffer */
    p->dma_size = pdm_pcm_hardware.buffer_bytes_max;
    p->dma_addr = hma_alloc_user (pdm_poolname, p->dma_size, 1024, "cap_pdm");
    if (!p->dma_addr)
    {
        error ("no mem for dma\n");
        return -ENOMEM;
    }
    p->dma_vaddr = hma_map_cache (p->dma_addr, p->dma_size);
    if (!p->dma_vaddr)
    {
        error ("cannot map dma buffer\n");
        hma_free (pdm_poolname, p->dma_addr);
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int pdm_hw_free (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    info ("\n");
    snd_pcm_set_runtime_buffer (substream, NULL);

    hma_unmap (p->dma_vaddr);
    hma_free (pdm_poolname, p->dma_addr);

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int pdm_prepare (struct snd_pcm_substream *substream)
#endif
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif

#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    p->cur_dma_size = frames_to_bytes (runtime, runtime->buffer_size);
    info ("prepare... sample rate %dHz, dma_size %d\n", runtime->rate, p->cur_dma_size);
    pdm_hw_init (p, runtime);

    if (p->cur_dma_size % p->unit_size)
    {
        error ("Buffer size should multiple of unit size(0x%08X)\n", p->unit_size);
        return -EINVAL;
    }

    msleep (10);

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd)
#else
static int pdm_trigger (struct snd_pcm_substream *substream, int cmd)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif

    info ("\n");
    switch (cmd)
    {
        case SNDRV_PCM_TRIGGER_STOP:
            info ("stop\n");
            pdm_hw_stop (p);
            break;

        case SNDRV_PCM_TRIGGER_START:
            info ("start\n");
            pdm_hw_start (p);
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static snd_pcm_uframes_t pdm_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static snd_pcm_uframes_t pdm_pointer (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    snd_pcm_uframes_t ret;

    ret = bytes_to_frames (substream->runtime, p->wr_off);
    debug ("hw_ptr 0x%04x, frames %5ld/%ld\n", p->wr_off, ret, substream->runtime->buffer_size);

    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#else
static int pdm_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma)
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int pdm_ack (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
    struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(soc_pcm_rtd, 0);
    struct pdm_priv *p = dev_get_drvdata (cpu_dai->dev);
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->cpu_dai->dev);
#endif
#else
    struct pdm_priv *p = dev_get_drvdata (soc_pcm_rtd->platform->dev);
#endif
    uint32_t sw_ptr;

    sw_ptr = runtime->control->appl_ptr % runtime->buffer_size;
    p->rd_off = sw_ptr;
    debug ("sw_ptr %5d/%ld\n", sw_ptr, runtime->buffer_size);

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int pdm_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd)
#else
static int pdm_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd)
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static void pdm_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm)
#else
static void pdm_pcm_free (struct snd_pcm *pcm)
#endif
{
    info ("\n");
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int pdm_probe (struct snd_soc_component *component)
#else
static int pdm_probe (struct snd_soc_platform *platform)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct platform_device *pdev = to_platform_device (component->dev);
#else
    struct platform_device *pdev = to_platform_device (platform->dev);
#endif
    struct resource *res;
    struct pdm_priv *p;
    int size;

    info ("pdev name %s.%d\n", pdev->name, pdev->id);

    p = kzalloc (sizeof (struct pdm_priv), GFP_KERNEL);
    if (!p)
        return -ENOMEM;

    p->irq_num = platform_get_irq (pdev, 0);
    info ("irq %d\n", p->irq_num);

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
static void pdm_remove (struct snd_soc_component *component)
{
    struct pdm_priv *p = dev_get_drvdata (component->dev);

    info ("\n");

    iounmap (p->reg);

    kfree (p);
    info ("\n");
}
#else
static int pdm_remove (struct snd_soc_platform *platform)
{
    struct pdm_priv *p = dev_get_drvdata (platform->dev);

    info ("\n");

    iounmap (p->reg);

    kfree (p);
    info ("\n");

    return 0;
}
#endif

static int pdm_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt)
{
    info ("\n");
    return 0;
}

static int pdm_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
    return 0;
}

static void pdm_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
}

static int pdm_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai)
{
    info ("\n");
    return 0;
}

static int pdm_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("\n");
    return 0;
}

static int pdm_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("\n");
    return 0;
}

static int pdev_probe (struct platform_device *pdev)
{
    int ret;

    info ("probe.. %s\n", pdev->name);
    set_fwloadwov_mic_tuning_data ();

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_platform (&pdev->dev, &pdm_platform);
    if (ret < 0)
    {
        error ("cannot register_platform(). %d\n", ret);
        return ret;
    }
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_component (&pdev->dev, &pdm_component, pdm_dai, ARRAY_SIZE (pdm_dai));
#else
    ret = snd_soc_register_component (&pdev->dev, pdm_component, pdm_dai, ARRAY_SIZE (pdm_dai));
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

/*==============================================================================
    Implementation Group
==============================================================================*/
int pdm_set_mic_tuning_data (struct pdm_mic_tuning_data *tuning_data)
{
    if (mic_tuning_data_count > 0)
    {
        noti ("Already set by module_param\n");
        return -1;
    }
    else
    {
        tuning_data->wov_pdm_clkout_mux_sel = 1;
        mic_tuning_data[HPGAIN] = (int) tuning_data->highpass_filter_coeff;
        mic_tuning_data[ADCHPD] = (int) tuning_data->highpass_filter_on_off;
        mic_tuning_data[SOFT_MUTE] = (int) tuning_data->gain_soft_mute;
        mic_tuning_data[SINC_SHIFT] = (int) tuning_data->gain_sinc_shift;
        mic_tuning_data[S_CYCLES] = (int) tuning_data->s_cycles;
        mic_tuning_data[DATA_VALID_DELAY] = (int) tuning_data->pdm_data_valid_delay;
        mic_tuning_data[WOV_PDM_CLKOUT_MUX_SEL] = (int) tuning_data->wov_pdm_clkout_mux_sel;
    }

    set_fwloadwov_mic_tuning_data ();

    noti ("mic_tuning_data[ADCHPD]           = %d\n", mic_tuning_data[ADCHPD]);
    noti ("mic_tuning_data[HPGAIN]           = %d\n", mic_tuning_data[HPGAIN]);
    noti ("mic_tuning_data[SOFT_MUTE]        = %d\n", mic_tuning_data[SOFT_MUTE]);
    noti ("mic_tuning_data[SINC_SHIFT]       = %d\n", mic_tuning_data[SINC_SHIFT]);
    noti ("mic_tuning_data[S_CYCLES]         = %d\n", mic_tuning_data[S_CYCLES]);
    noti ("mic_tuning_data[DATA_VALID_DELAY] = %d\n", mic_tuning_data[DATA_VALID_DELAY]);
    return 0;
}

EXPORT_SYMBOL (pdm_set_mic_tuning_data);

int pdm_get_mic_tuning_data (struct pdm_mic_tuning_data tuning_data[])
{
    tuning_data[0].highpass_filter_on_off = (unsigned int) default_mic_tuning_data[ADCHPD];
    tuning_data[0].highpass_filter_coeff = (unsigned int) default_mic_tuning_data[HPGAIN];
    tuning_data[0].gain_soft_mute = (unsigned int) default_mic_tuning_data[SOFT_MUTE];
    tuning_data[0].gain_sinc_shift = (unsigned int) default_mic_tuning_data[SINC_SHIFT];
    tuning_data[0].s_cycles = (unsigned int) default_mic_tuning_data[S_CYCLES];
    tuning_data[0].pdm_data_valid_delay = (unsigned int) default_mic_tuning_data[DATA_VALID_DELAY];
    tuning_data[0].wov_pdm_clkout_mux_sel =
        (unsigned int) default_mic_tuning_data[WOV_PDM_CLKOUT_MUX_SEL];

    tuning_data[1].highpass_filter_on_off = (unsigned int) mic_tuning_data[ADCHPD];
    tuning_data[1].highpass_filter_coeff = (unsigned int) mic_tuning_data[HPGAIN];
    tuning_data[1].gain_soft_mute = (unsigned int) mic_tuning_data[SOFT_MUTE];
    tuning_data[1].gain_sinc_shift = (unsigned int) mic_tuning_data[SINC_SHIFT];
    tuning_data[1].s_cycles = (unsigned int) mic_tuning_data[S_CYCLES];
    tuning_data[1].pdm_data_valid_delay = (unsigned int) mic_tuning_data[DATA_VALID_DELAY];
    tuning_data[1].wov_pdm_clkout_mux_sel = (unsigned int) mic_tuning_data[WOV_PDM_CLKOUT_MUX_SEL];

    return 0;
}

EXPORT_SYMBOL (pdm_get_mic_tuning_data);

int pdm_set_pull_down (bool on)
{
    pull_down = on;

    return 0;
}

EXPORT_SYMBOL (pdm_set_pull_down);

////////////////////////////////////////////////////////////////////////////////

module_platform_driver (pdev_driver);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG SIC PDM alsa driver");
MODULE_LICENSE ("GPL");
