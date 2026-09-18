/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 * @ingroup se
 *
 * @brief
 * Sound engine module API Implementation for audio kernel driver
 *
 * @author      Youngwoo Jin
 * @version     1.0
 * @date        2020.06.18
 *
 * @details
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/slab.h>
#include <linux/version.h>

#include "se.h"
#include "linux/alsa-ext/alsa-ext-lgse.h"
#ifdef SUPPORT_DAFC
#include <linux/fs.h>
#include "linux/alsa-ext/alsa-ext-dap.h"
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
#include <linux/kernel_read_file.h>
#endif
#endif
#include "os_util.h"

#include "fwload.h"

#include "se.h"
#include "logm.h"
#include "block.h"
#include "block_manager.h"
#include "pipeline.h"
#include "kaimc.h"
#include "module/adec_module_list.h"    ///< ADEC_CORE_ARM
#include "common/module/uid.h"  ///< AUD_MODID_REGISTRY ()
#include "common/imc/cmd/module_cmd_se_common.h"
#include "common/imc/cmd/module_cmd_se.h"
#include "common/imc/cmd/module_cmd_aisound.h"
#include "common/imc/cmd/module_cmd_lgse_ll.h"
#ifdef SUPPORT_DAFC
#include "common/imc/cmd/module_cmd_dapv2.h"
#endif /* end of SUPPORT_DAFC */
#include "hma_alloc.h"
#include <asm/io.h>
#include "sys_regs.h"
#include "blind.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define DEFAULT_NUMBER_OF_OUTPUT_CHANNELS       (2)

#ifdef _LNX_
#define __MB(v) ((v)<<20)
#define DEFAULT_MEMSIZE_LNX_SCRATCH             (0x130000)      //0x120000(FW)
#define DEFAULT_LNX_MEM_NAME                    "audio_lnx"
#define LNX_CLK_GATE_KEY                        "ipw_clock_gating"
// For LNX2 rst and AXI flush
#if defined(CHIP_NAME_o26)
#define LNX2_HCR_HOST                   0xCC5EE000 // LNX2_REG_BASE + LNX2_REG_OFFS_HCR_HOST = 0xCC5E0000 + 0xE000
#define LNX2_HCR_HOST_AXI_FLUSH_EN      0x0
#define LNX2_HCR_HOST_AXI_FLUSH_DONE    0x4
#define LNX2_AXI_FLUSH_EN_VAL           0xD
#elif defined(CHIP_NAME_o24)
#define LNX2_HCR_HOST                   0xCCD87800 // LNX2_REG_BASE + LNX2_REG_OFFS_HCR_HOST = 0xCCD80000 + 0x7800
#define LNX2_HCR_HOST_AXI_FLUSH_EN      0x0
#define LNX2_HCR_HOST_AXI_FLUSH_DONE    0x4
#define LNX2_AXI_FLUSH_EN_VAL           0xF
#endif
#else   // ifndef _LNX_
#if defined(CHIP_NAME_o22)
// For LNE rst and AXI flush
#define LNE_SYSREG_BASE         0xC4D02000
#define LNE_SYSREG_FLUSH_EN     0x8
#define LNE_SYSREG_FLUSH_DONE   0xC
#elif defined(CHIP_NAME_m23)
// For LNE rst and AXI flush
#define LNE_SYSREG_BASE         0xCC872000
#define LNE_SYSREG_FLUSH_EN     0x8
#define LNE_SYSREG_FLUSH_DONE   0xC
#endif
#endif  // END OF _LNX_

static unsigned int *mapped_addr;

#define AUD_SE_REG_WRITE(addr, data) \
        mapped_addr = (unsigned int *)ioremap (addr, sizeof(unsigned int));\
    do{\
        if(mapped_addr == NULL) break;\
        *mapped_addr = data;\
        iounmap((void *)mapped_addr);\
    }while(0);\

#define AUD_SE_REG_READ(addr, data) \
        mapped_addr = (unsigned int *)ioremap (addr, sizeof(unsigned int));\
    do{\
        if(mapped_addr == NULL) {data =0; break;}\
        data = (unsigned int)*mapped_addr;\
        iounmap((void *)mapped_addr);\
    }while(0);\


#ifdef SUPPORT_SOUNDBAR
#define CONTENT_SE_MODULE_NAME              "content_se"
#define DEVICE_SE_MODULE_NAME               "device_se"
#define AI_MODULE_NAME                      "aisound"
#ifdef SUPPORT_DAFC
#define FLEXREN_MODULE_NAME                 "flexren"
#endif
#else
#define SE_MODULE_NAME                      "se"
#define AI_MODULE_NAME                      "aisound"
#if (MS12_VER >= 28)
#define DAP_MODULE_NAME                     "flap"
#else
#define DAP_MODULE_NAME                     "dap"
#endif
#endif

#ifdef SUPPORT_DAFC
#ifdef SUPPORT_SOUNDBAR
#define MAX_DAFC_CONF_FILE_SIZE             (0x80000)   // 512kbyte
#else
#define MAX_DAFC_CONF_FILE_SIZE             (0x32000)   // 200kbyte
#endif
#endif /* end of SUPPORT_DAFC */

#ifdef SUPPORT_SOUNDBAR
#if defined (CHIP_NAME_o24)
#define CONTENT_SE_OUT_CH_DAFC_ON           (10)
#define CONTENT_SE_OUT_CH_DAFC_OFF          (8)
//#define DEVICE_SE_OUT_CH_DAFC_ON            (10)
//#define DEVICE_SE_OUT_CH_DAFC_OFF           (4)
#else   // o26
#define CONTENT_SE_OUT_CH_DAFC_ON           (12)    // 7.1.4
#define CONTENT_SE_OUT_CH_DAFC_OFF          (12)    // 5.4.3
//#define DEVICE_SE_OUT_CH_DAFC_ON            (21)  // 9.5.7
//#define DEVICE_SE_OUT_CH_DAFC_OFF           (12)  // 5.4.3
#endif

#define SE_UPMIX_CHANNEL                    (1)
#define CONTENT_SE_BYPASS                   (2)
#define DEVICE_SE_BYPASS                    (1)
#if defined (CHIP_NAME_o24)
#define AI_OUT_CH_DAFC_ON                   (10)
#define AI_OUT_CH_DAFC_OFF                  (10)
#else   // o26
#define AI_OUT_CH_DAFC_ON                   (12)
#define AI_OUT_CH_DAFC_OFF                  (16)
#endif
#endif

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
/// @brief Print log message for trace level
#define trace(fmt,args...)      logm_trace (aud_se, fmt, ##args)
/// @brief Print log message for debug level
#define debug(fmt,args...)      logm_debug (aud_se, fmt, ##args)
/// @brief Print log message for info level
#define info(fmt,args...)       logm_info (aud_se, fmt, ##args)
/// @brief Print log message for noti level
#define noti(fmt,args...)       logm_noti (aud_se, fmt, ##args)
/// @brief Print log message for warning level
#define warn(fmt,args...)       logm_warning (aud_se, fmt, ##args)
/// @brief Print log message for error level
#define error(fmt,args...)      logm_error (aud_se, fmt, ##args)
#define SEDRV_ALIGN(n,base)    (((n)+((base)-1))&~((unsigned)((base)-1)))

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
/**
 * pipeline info
 */
struct _pipeline
{
    struct apipeline *pipeline;
    unsigned int module;
};

/**
 * module infomation
 */
struct _module
{
    const char *name;
    struct mod_cmd_se_cmn_param_list_info list_info;
    struct mod_cmd_se_cmn_param_info *param_infos;
    struct mod_cmd_se_cmn_param_info **param_info_list;
};

#ifdef _LNX_
/**
 * se,lne buffer addr info
 */
struct _se_buffer_info
{
    phys_addr_t base;
    unsigned int size;
    unsigned int unit_size;
    unsigned int format;
};
#endif

/**
 * Sound enginge block information.
 */
struct _info
{
    struct aud_block_info block_info;

#ifdef SUPPORT_SOUNDBAR
    struct _pipeline pipeline_ai;
    struct _pipeline pipeline_content_se;
    struct _pipeline pipeline_flex;
    struct _pipeline pipeline_device_se;
#else
    struct _pipeline pipeline_in[2];
    struct _pipeline pipeline_core[2];
    struct _pipeline pipeline_out;
#endif

    unsigned int number_of_output_channels;
#ifdef SUPPORT_SOUNDBAR
    unsigned int output_freq;
#endif

    int event_id;
    se_callback_func cb_func;
    void *cb_param;

    bool suspended;
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
logm_define (aud_se, log_level_noti);   ///< @brief declaration logm fd

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _get_parameter_info (void);
static int _make_parameter_list (void);
static unsigned int _get_module_uid (struct _info *se_info, const char *name);
static int _create_pipeline (struct _pipeline *pipeline, char *name);
static void _destroy_pipeline (struct _pipeline *pipeline);;
static int _connect_pipelines (struct _info *se_info, const char *name, int port);
static void _disconnect_pipelines (struct _info *se_info);
#ifdef SUPPORT_SOUNDBAR
static void _set_bypass (unsigned int uid, int bypass);
static void _set_upmix (unsigned int uid, unsigned int upmix_ch);
static void _set_ai_out_ch (unsigned int uid, int out_ch_num);
static void _set_output_freq (unsigned int uid, unsigned int freq);
#else
static void _set_bypass (unsigned int uid, bool bypass);
static void _set_upmix (unsigned int uid, bool enable);
#endif
static void _set_fade (unsigned int uid, bool inout);
static void _set_number_of_output_channels (unsigned int uid, unsigned int number);
static int _set_lne_data (unsigned int uid);
static int _set_lne_lnx2_reset (void);
#if defined (CHIP_NAME_o22) || defined (CHIP_NAME_m23)
static int _set_lne_reset (void);
#elif defined (CHIP_NAME_o24) || defined (CHIP_NAME_o26)
static int _set_lnx2_reset (void);
#ifndef SUPPORT_SOUNDBAR
static int _set_lnx2_clk_gate (bool on);
#endif
#endif
static int _cb_se_lne_lnx_reset (void *param, int paramLen, void *cbParam);
#ifdef SUPPORT_DAFC
static void _set_dafc (unsigned int uid, bool onoff);
static void _set_dafc_dconf (unsigned int uid, unsigned int dconf, int fsize);
static void _set_dafc_sconf (unsigned int uid, unsigned int sconf, int fsize);
static void _set_dafc_center_extract_status (unsigned int uid, unsigned int status);
#endif /* end of SUPPORT_DAFC */
static int _create (struct aud_block_info *block);
static void _destroy (struct aud_block_info *block);
static int _suspend (struct aud_block_info *block);
static int _resume (struct aud_block_info *block);
/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static bool _parameter_info_loaded = false;
static struct _module _modules[] = {
    /* *INDENT-OFF* */
#ifdef SUPPORT_SOUNDBAR
    { CONTENT_SE_MODULE_NAME,   {0, 0}, NULL },
    { DEVICE_SE_MODULE_NAME,    {0, 0}, NULL },
    { AI_MODULE_NAME,           {0, 0}, NULL },
#else
    { SE_MODULE_NAME,   {0, 0}, NULL },
    { AI_MODULE_NAME, {0, 0}, NULL },
#if !defined(CHIP_NAME_m23)
    { DAP_MODULE_NAME,  {0, 0}, NULL },
#endif
#endif
    /* *INDENT-ON* */
};

static int _num_of_params = 0;
static int (*_param_list)[ARRAY_SIZE (_modules)] = NULL;
static struct se_param_info *_se_param_info_list = NULL;

#ifdef SE_FUNC_LIST_DEF
#undef SE_FUNC_LIST_DEF
#endif
#define SE_FUNC_LIST_DEF(name, unit_size, min, max, order, size, ...) \
    { name, unit_size, min, max, order, size, },

#ifdef SUPPORT_SOUNDBAR
static struct se_param_info _content_se_func_list[] = {
#include "common/module/se_func_list.h"
};

static struct se_param_info _device_se_func_list[] = {
#include "common/module/se_func_list.h"
};
#else
static struct se_param_info _se_func_list[] = {
#include "common/module/se_func_list.h"
};

#if !defined(CHIP_NAME_m23)
static struct se_param_info _dap_func_list[] = {
#include "common/module/dap_func_list.h"
};
#endif
#endif
static struct se_param_info _ai_func_list[] = {
#include "common/module/ai_func_list.h"
};

#undef SE_FUNC_LIST_DEF

#ifdef SUPPORT_DAFC
static phys_addr_t dconf_addr = 0;
static phys_addr_t sconf_addr = 0;
static void *dconf_vmap_addr = NULL;
static void *sconf_vmap_addr = NULL;
#endif /* end of SUPPORT_DAFC */

static struct audio_block_impl _block_impl = {
    .block_info_size = sizeof (struct _info),
    .block_type = "se",
    .preffered_processor = ADEC_CORE_DSP1,
    .constructor = _create,
    .destructor = _destroy,
    .suspend = _suspend,
    .resume = _resume,
};

struct lgse_ll_info
{
    struct aud_block_info parent;

    unsigned int uid_lgse_ll;

    int mode;
    int led_num;
    int period;
    int min_power;
    int max_power;
    int lower_bound;
    int upper_bound;

    bool suspended;
};

#ifdef _LNX_
struct _se_buffer_info lnx_scratch = { 0, };

static unsigned int lnx2_dump_cnt = 0;
#endif

static int _lgse_ll_create (struct aud_block_info *block)
{
    struct lgse_ll_info *lgse_ll = (struct lgse_ll_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    noti ("create lgse_ll\n");

    block->pipeline = apipeline_new2 (preferred_proc, "lgse_ll");
    lgse_ll->uid_lgse_ll = apipeline_appendf (block->pipeline, "lgse_ll");

    lgse_ll->mode = LGSE_LL_MODE_VU_METER;
    lgse_ll->led_num = 40;
    lgse_ll->period = 100;
    lgse_ll->min_power = -20;
    lgse_ll->max_power = 3;
    lgse_ll->lower_bound = 250;
    lgse_ll->upper_bound = 2500;

    block->isOpened = true;
    return 0;
}

static void _lgse_ll_destroy (struct aud_block_info *block)
{
    noti ("called\n");

    if (block == NULL)
    {
        error ("lgse_ll_info is NULL!!\n");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("lgse_ll is already closed. \n");
        goto exit;
    }

    if (block->pipeline)
        apipeline_del (block->pipeline);
    block->isOpened = false;

  exit:
    return;
}

static int _lgse_ll_suspend (struct aud_block_info *block)
{
    struct lgse_ll_info *lgse_ll = (struct lgse_ll_info *) block;

    if (block->pipeline)
        apipeline_del (block->pipeline);

    block->pipeline = NULL;

    lgse_ll->suspended = true;

    noti ("suspend lgse_ll\n");

    return 0;
}

static int _lgse_ll_resume (struct aud_block_info *block)
{
    struct lgse_ll_info *lgse_ll = (struct lgse_ll_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    block->pipeline = apipeline_new2 (preferred_proc, "lgse_ll");

    lgse_ll->uid_lgse_ll = apipeline_appendf (block->pipeline, "lgse_ll");
    block->isOpened = true;

    // TODO: set property ??? (mode, led_num, period, min/max_pow, low/upp_bound)

    lgse_ll->suspended = false;

    noti ("resume lgse_ll\n");

    return 0;
}

static struct audio_block_impl _block_impl_lgse_ll = {
    .block_info_size = sizeof (struct lgse_ll_info),
    .block_type = "lgse_ll",
    .preffered_processor = ADEC_CORE_DSP1,
    .constructor = _lgse_ll_create,
    .destructor = _lgse_ll_destroy,
    .suspend = _lgse_ll_suspend,
    .resume = _lgse_ll_resume,
};

struct _lgse_ll_cmd_info
{
    int cmd;
    int imc_cmd;
    int param_size;
};
static int _lgse_ll_get_imccmd (int cmd, int *imc_cmd, int *param_size)
{
    struct _lgse_ll_cmd_info cmd_info[LL_CMD_MAX] = {
        /* *INDENT-OFF* */
        { LL_CMD_SET_PARAM,         LGSE_LL_CMD_SET_PARAM,      sizeof (LgseLLCmdSetParam) },
        { LL_CMD_GET_PARAM,         LGSE_LL_CMD_GET_PARAM,      sizeof (LgseLLCmdGetParam) },
        { LL_CMD_GET_BRIGHTNESS,    LGSE_LL_CMD_GET_BRIGHTNESS, sizeof (LgseLLCmdGetBrightness) },
        { LL_CMD_GET_LIGHT_FREQ,    LGSE_LL_CMD_GET_LIGHT_FREQ, sizeof (LgseLLCmdGetLightFreq) },
        { LL_CMD_GET_VERSION,       LGSE_LL_CMD_GET_VERSION,    sizeof (LgseLLCmdGetVersion) },
        { LL_CMD_START,             ADEC_CMD_START,             0 },
        { LL_CMD_STOP,              ADEC_CMD_STOP,              0 },
        /* *INDENT-ON* */
    };
    int i;

    if (cmd < LL_CMD_SET_PARAM || cmd >= LL_CMD_MAX)
    {
        error ("invalid cmd (%d)\n", cmd);
        return -1;
    }

    for (i = 0; i < LL_CMD_MAX; i++)
    {
        if (cmd_info[i].cmd == cmd)
        {
            if (imc_cmd)
                *imc_cmd = cmd_info[i].imc_cmd;
            if (param_size)
                *param_size = cmd_info[i].param_size;
            return 0;
        }
    }

    return -1;
}


int lgse_ll_get_param (struct aud_block_info *block, int cmd, int size, unsigned int *data)
{
    struct lgse_ll_info *lgse_ll_info = (struct lgse_ll_info *) block;
    int imc_cmd;
    int param_size;
    int ret;

    if (lgse_ll_info == NULL || data == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    if (lgse_ll_info->uid_lgse_ll == 0)
    {
        error ("not opend lgse ll module\n");
        return -1;
    }

    if (cmd < LL_CMD_SET_PARAM || cmd > LL_CMD_MAX)
    {
        error ("invalid cmd (%d)\n", cmd);
        return -1;
    }

    ret = _lgse_ll_get_imccmd (cmd, &imc_cmd, &param_size);
    if (ret < 0)
    {
        error ("get imc cmd err (cmd=%d)\n", cmd);
        return -1;
    }
    aimc_send_command_return (NULL, imc_cmd, 0, lgse_ll_info->uid_lgse_ll, data, param_size);

    return 0;
}

int lgse_ll_set_param (struct aud_block_info *block, int cmd, int size, unsigned int *data)
{
    struct lgse_ll_info *lgse_ll_info = (struct lgse_ll_info *) block;
    int imc_cmd;
    int param_size;
    int ret;

    if (lgse_ll_info == NULL || data == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    if (lgse_ll_info->uid_lgse_ll == 0)
    {
        error ("not opend lgse ll module\n");
        return -1;
    }

    if (cmd < LL_CMD_SET_PARAM || cmd > LL_CMD_MAX)
    {
        error ("invalid cmd (%d)\n", cmd);
        return -1;
    }

    ret = _lgse_ll_get_imccmd (cmd, &imc_cmd, &param_size);
    if (ret < 0)
    {
        error ("get imc cmd err (cmd=%d)\n", cmd);
        return -1;
    }
    aimc_send_command (NULL, imc_cmd, 0, lgse_ll_info->uid_lgse_ll, data, param_size);

    // TODO: save config (mode, led_num, period, min/max_pow, low/upp_bound)

    return 0;
}

#ifndef SUPPORT_SOUNDBAR
typedef enum _SE_CORE_ID
{
    SE_CORE_ID_DAP = 0,
    SE_CORE_ID_AI,
    SE_CORE_ID_MAX = 2,
} SE_CORE_ID;
#endif

/*==============================================================================
    Implementation Group
==============================================================================*/

static int _get_param_list_info (const char *module_name, unsigned int *param_num,
    unsigned int *param_list_size)
{
    struct se_param_info *func_list_info;
    int list_num;
    unsigned int i;

#ifdef SUPPORT_SOUNDBAR
    if (!strcmp (module_name, CONTENT_SE_MODULE_NAME))
    {
        func_list_info = _content_se_func_list;
        list_num = ARRAY_SIZE (_content_se_func_list);
    }
    else if (!strcmp (module_name, DEVICE_SE_MODULE_NAME))
    {
        func_list_info = _device_se_func_list;
        list_num = ARRAY_SIZE (_device_se_func_list);
    }
    else if (!strcmp (module_name, AI_MODULE_NAME))
    {
        func_list_info = _ai_func_list;
        list_num = ARRAY_SIZE (_ai_func_list);
    }
    else
    {
        noti ("module name(%s) is unknown\n", module_name);
        return -1;
    }
#else
    if (!strcmp (module_name, SE_MODULE_NAME))
    {
        func_list_info = _se_func_list;
        list_num = ARRAY_SIZE (_se_func_list);
    }
    else if (!strcmp (module_name, AI_MODULE_NAME))
    {
        func_list_info = _ai_func_list;
        list_num = ARRAY_SIZE (_ai_func_list);
    }
#if !defined(CHIP_NAME_m23)
    else if (!strcmp (module_name, DAP_MODULE_NAME))
    {
        func_list_info = _dap_func_list;
        list_num = ARRAY_SIZE (_dap_func_list);
    }
#endif
    else
    {
        noti ("module name(%s) is unknown\n", module_name);
        return -1;
    }
#endif

    *param_num = list_num;

    for (i = 0; i < list_num; i++)
    {
        unsigned int name_size;
        *param_list_size += sizeof (struct mod_cmd_se_cmn_param_info);
        name_size = strlen (func_list_info[i].name) + 1;        // with null
        *param_list_size += SEDRV_ALIGN (name_size, 4);
    }

    return 0;
}

static int _get_param_list (const char *module_name, struct mod_cmd_se_cmn_param_info *list)
{
    struct se_param_info *func_list_info;
    struct mod_cmd_se_cmn_param_info *infos = list;
    int list_num;
    unsigned int i;

    if (!list)
    {
        noti ("list is null\n");
        return -1;
    }

#ifdef SUPPORT_SOUNDBAR
    if (!strcmp (module_name, CONTENT_SE_MODULE_NAME))
    {
        func_list_info = _content_se_func_list;
        list_num = ARRAY_SIZE (_content_se_func_list);
    }
    else if (!strcmp (module_name, DEVICE_SE_MODULE_NAME))
    {
        func_list_info = _device_se_func_list;
        list_num = ARRAY_SIZE (_device_se_func_list);
    }
    else if (!strcmp (module_name, AI_MODULE_NAME))
    {
        func_list_info = _ai_func_list;
        list_num = ARRAY_SIZE (_ai_func_list);
    }
    else
    {
        noti ("module name(%s) is unknown\n", module_name);
        return -1;
    }
#else
    if (!strcmp (module_name, SE_MODULE_NAME))
    {
        func_list_info = _se_func_list;
        list_num = ARRAY_SIZE (_se_func_list);
    }
    else if (!strcmp (module_name, AI_MODULE_NAME))
    {
        func_list_info = _ai_func_list;
        list_num = ARRAY_SIZE (_ai_func_list);
    }
#if !defined(CHIP_NAME_m23)
    else if (!strcmp (module_name, DAP_MODULE_NAME))
    {
        func_list_info = _dap_func_list;
        list_num = ARRAY_SIZE (_dap_func_list);
    }
#endif
    else
    {
        noti ("module name(%s) is unknown\n", module_name);
        return -1;
    }
#endif

    for (i = 0; i < list_num; i++)
    {
        unsigned int name_size;
        infos->unit_size = func_list_info[i].unit_size;
        infos->min_value = func_list_info[i].min_value;
        infos->max_value = func_list_info[i].max_value;
        infos->order = func_list_info[i].order;
        infos->param_size = func_list_info[i].size;
        name_size = strlen (func_list_info[i].name) + 1;
        infos->name_size = SEDRV_ALIGN (name_size, 4);
        memset (infos->name, 0, infos->name_size);
        memcpy (infos->name, func_list_info[i].name, name_size);

        debug ("name_size:%2d, infos->name:%32s, func_list_info[%d].name:%32s, infos->name_size:%2d\n", \
                name_size, infos->name, i, func_list_info[i].name, infos->name_size);

        infos = (struct mod_cmd_se_cmn_param_info *) (((void *) infos)
            + infos->name_size + sizeof (struct mod_cmd_se_cmn_param_info));
    }

    return 0;
}

static int _get_parameter_info (void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE (_modules); i++)
    {
        struct _module *module = _modules + i;
        unsigned int list_size;
        void *buffer;
        unsigned int param_num = 0;
        unsigned int param_list_size = 0;
        int j;

        if (module->param_infos)
        {
            kfree (module->param_infos);
            module->param_infos = NULL;
        }

        trace ("Get parameter info for %s\n", module->name);
        _get_param_list_info (module->name, &param_num, &param_list_size);
        module->list_info.number_of_paramters = param_num;
        module->list_info.size_of_param_list = param_list_size;
        debug ("Get list info %d %d\n", module->list_info.number_of_paramters,
            module->list_info.size_of_param_list);

        list_size =
            sizeof (struct mod_cmd_se_cmn_param_info *) * module->list_info.number_of_paramters;

        buffer = kmalloc (module->list_info.size_of_param_list + list_size, GFP_KERNEL);
        if (buffer == NULL)
            continue;

        module->param_infos = buffer;
        module->param_info_list = buffer + module->list_info.size_of_param_list;

        _get_param_list (module->name, module->param_infos);

        for (j = 0; j < module->list_info.number_of_paramters; j++)
        {
            module->param_info_list[j] = buffer;
            buffer +=
                sizeof (struct mod_cmd_se_cmn_param_info) + module->param_info_list[j]->name_size;
        }

        _num_of_params += module->list_info.number_of_paramters;
        info ("%s module has %u ea functions, total: %d\n", module->name,
            module->list_info.number_of_paramters, _num_of_params);
    }

    return 0;
}

static int _make_parameter_list (void)
{
    int param_list_size = sizeof (int[ARRAY_SIZE (_modules)]) * _num_of_params;
    int se_param_info_list_size = sizeof (struct se_param_info) * _num_of_params;
    int module_id;

    // alloc list buffers
    _param_list = kmalloc (param_list_size + se_param_info_list_size, GFP_KERNEL);
    if (_param_list == NULL)
    {
        error ("no memory\n");
        return -1;
    }

    _se_param_info_list = ((void *) _param_list) + param_list_size;

    // param_list buffer initialize
    for (module_id = 0; module_id < ARRAY_SIZE (_modules); module_id++)
    {
        int param_id;

        for (param_id = 0; param_id < _num_of_params; param_id++)
        {
            _param_list[param_id][module_id] = -1;
        }
    }

    _num_of_params = 0;

    for (module_id = 0; module_id < ARRAY_SIZE (_modules); module_id++)
    {
        struct _module *module = _modules + module_id;
        int param_count = 0;
        int param_id_module;

        for (param_id_module = 0; param_id_module < module->list_info.number_of_paramters;
            param_id_module++)
        {
            struct mod_cmd_se_cmn_param_info *new_param = module->param_info_list[param_id_module];
            int param_id_list;

            for (param_id_list = 0; param_id_list < _num_of_params; param_id_list++)
            {
                struct mod_cmd_se_cmn_param_info *cur_param = NULL;
                int i;

                for (i = 0; i < module_id; i++)
                {
                    if (_param_list[param_id_list][i] != -1)
                    {
                        cur_param = _modules[i].param_info_list[_param_list[param_id_list][i]];
                        break;
                    }
                }

                if (!memcmp (new_param, cur_param,
                        sizeof (struct mod_cmd_se_cmn_param_info) + cur_param->name_size))
                {
                    _param_list[param_id_list][module_id] = param_id_module;
                    break;
                }
            }

            if (param_id_list == _num_of_params)
            {
                _se_param_info_list[_num_of_params + param_count].name = new_param->name;
                _se_param_info_list[_num_of_params + param_count].unit_size = new_param->unit_size;
                _se_param_info_list[_num_of_params + param_count].min_value = new_param->min_value;
                _se_param_info_list[_num_of_params + param_count].max_value = new_param->max_value;
                _se_param_info_list[_num_of_params + param_count].order = new_param->order;
                _se_param_info_list[_num_of_params + param_count].size = new_param->param_size;

                _param_list[_num_of_params + param_count][module_id] = param_id_module;
                param_count++;
            }
        }

        _num_of_params += param_count;
    }
    info ("total func num:%d\n", _num_of_params);

    return 0;
}

static unsigned int _get_module_uid (struct _info *se_info, const char *name)
{
#ifdef SUPPORT_SOUNDBAR
    struct _pipeline *pipeline;

    if (!strcmp (name, CONTENT_SE_MODULE_NAME))
        pipeline = &se_info->pipeline_content_se;
    else if (!strcmp (name, DEVICE_SE_MODULE_NAME))
        pipeline = &se_info->pipeline_device_se;
    else if (!strcmp (name, AI_MODULE_NAME))
        pipeline = &se_info->pipeline_ai;
#ifdef SUPPORT_DAFC
    else if (!strcmp (name, FLEXREN_MODULE_NAME))
        pipeline = &se_info->pipeline_flex;
#endif
    else
        pipeline = NULL;

    if (pipeline == NULL)
    {
        info ("%s pipeline is not created\n", name);
        return 0;
    }

    return pipeline->module;
#else
    const char *pipeline;
    int i;

    pipeline = apipeline_get_name (se_info->pipeline_out.pipeline);
    if (pipeline == NULL)
    {
        return 0;
    }

    if (!strcmp (pipeline, name))
    {
        return se_info->pipeline_out.module;
    }

    for (i = 0; i < SE_CORE_ID_MAX; i++)
    {
        pipeline = apipeline_get_name (se_info->pipeline_core[i].pipeline);
        if (pipeline == NULL)
        {
            continue;
        }

        if (!strcmp (pipeline, name))
        {
            return se_info->pipeline_core[i].module;
        }
    }
    return 0;
#endif
}

static int _create_pipeline (struct _pipeline *pipeline, char *name)
{
    int core = ADEC_CORE_DSP1;

    if (pipeline->pipeline != NULL)
    {
#ifdef SUPPORT_SOUNDBAR
        info ("%s is created already\n", name);

        return 0;
#else
        const char *pipelineName;

        pipelineName = apipeline_get_name (pipeline->pipeline);

        if (pipelineName == NULL)
        {
            apipeline_del (pipeline->pipeline);
            pipeline->pipeline = NULL;
        }
        else if (!strcmp (pipelineName, DAP_MODULE_NAME))
        {
            info ("Already %s is created 0x%p\n", DAP_MODULE_NAME, pipeline);
            return 0;
        }
        else
            return 0;
#endif
    }

#ifdef SUPPORT_SOUNDBAR
    if (!strcmp (name, CONTENT_SE_MODULE_NAME))
        core = ADEC_CORE_DSP2;
    else if (!strcmp (name, DEVICE_SE_MODULE_NAME))
        core = ADEC_CORE_DSP1;
    else if (!strcmp (name, AI_MODULE_NAME))
        core = ADEC_CORE_DSP2;
#ifdef SUPPORT_DAFC
    else if (!strcmp (name, FLEXREN_MODULE_NAME))
        core = ADEC_CORE_DSP3;
#endif
    else
    {
        noti ("%s is not supported on sound bar\n", name);
        return -1;
    }
#endif

    pipeline->pipeline = apipeline_new2 (core, name);
    if (pipeline->pipeline == NULL)
    {
        return -1;
    }

    pipeline->module = apipeline_appendf (pipeline->pipeline, name);
    if (pipeline->module == 0)
    {
        apipeline_del (pipeline->pipeline);
        pipeline->pipeline = NULL;
        return -1;
    }

    return 0;
}

static void _destroy_pipeline (struct _pipeline *pipeline)
{
    if (pipeline->pipeline)
    {
        apipeline_del (pipeline->pipeline);
        pipeline->pipeline = NULL;
    }

    pipeline->module = 0;
}

static int _connect_pipelines (struct _info *se_info, const char *name, int port)
{
#ifdef SUPPORT_SOUNDBAR
    // ai - content_se
    apipeline_connect (se_info->pipeline_ai.pipeline, 0, se_info->pipeline_content_se.pipeline, 0);

    if (se_info->pipeline_flex.pipeline)
    {
        // content_se - flex_ren
        apipeline_connect (se_info->pipeline_content_se.pipeline, 0,
            se_info->pipeline_flex.pipeline, 0);
        // flex_ren - device_se
        apipeline_connect (se_info->pipeline_flex.pipeline, 0, se_info->pipeline_device_se.pipeline,
            0);
    }
    else
    {
        // content_se - device_se
        apipeline_connect (se_info->pipeline_content_se.pipeline, 0,
            se_info->pipeline_device_se.pipeline, 0);
    }

    return 0;
#else
    SE_CORE_ID coreId = SE_CORE_ID_MAX;

    if (port >= ARRAY_SIZE (se_info->pipeline_in))
    {
        return -1;
    }

    if (!strcmp (name, "ATMOS"))
        coreId = SE_CORE_ID_DAP;
    else if (!strcmp (name, "AISOUND"))
        coreId = SE_CORE_ID_AI;

    if ((coreId < SE_CORE_ID_MAX) && (se_info->pipeline_core[coreId].pipeline))
    {
        apipeline_connect (se_info->pipeline_in[port].pipeline, 0,
            se_info->pipeline_core[coreId].pipeline, 0);

        apipeline_connect (se_info->pipeline_core[coreId].pipeline, 0,
            se_info->pipeline_out.pipeline, 0);
    }
    else
    {
        apipeline_connect (se_info->pipeline_in[port].pipeline, 0,
            se_info->pipeline_out.pipeline, 0);
    }

    return 0;
#endif
}

static void _disconnect_pipelines (struct _info *se_info)
{
#ifdef SUPPORT_SOUNDBAR
    if (se_info->pipeline_device_se.pipeline)
    {
        apipeline_disconnect (se_info->pipeline_device_se.pipeline, 0);
    }
    if (se_info->pipeline_flex.pipeline)
    {
        apipeline_disconnect (se_info->pipeline_flex.pipeline, 0);
    }
    if (se_info->pipeline_content_se.pipeline)
    {
        apipeline_disconnect (se_info->pipeline_content_se.pipeline, 0);
    }
#else
    int i;

    if (se_info->pipeline_out.pipeline)
    {
        apipeline_disconnect (se_info->pipeline_out.pipeline, 0);
    }

    for (i = 0; i < SE_CORE_ID_MAX; i++)
    {
        if (se_info->pipeline_core[i].pipeline)
        {
            apipeline_disconnect (se_info->pipeline_core[i].pipeline, 0);
        }
    }
#endif
}

#ifdef SUPPORT_SOUNDBAR
static void _set_bypass (unsigned int uid, int bypass)
{
    if (uid == 0)
    {
        return;
    }

    debug ("set bypass = %d\n", bypass);

    aimc_set_property (uid, "bypass_mode=%d", bypass);
}
#else
static void _set_bypass (unsigned int uid, bool bypass)
{
    SeCmdSetBypass param = {.bypass = bypass ? 1 : 0 };

    if (uid == 0)
    {
        return;
    }

    debug ("%s bypass\n", bypass ? "enabe" : "disable");

    aimc_send_command (NULL, SE_CMD_SET_BYPASS, 0, uid, (void *) &param, sizeof (SeCmdSetBypass));
}
#endif

#ifdef SUPPORT_SOUNDBAR
static void _set_upmix (unsigned int uid, unsigned int upmix_ch)
{
    SeCmdSetUpmix param;

    if (uid == 0)
    {
        return;
    }

    debug ("set upmixer channel: %u\n", upmix_ch);
    param.upmix = upmix_ch;

    aimc_send_command (NULL, SE_CMD_SET_UPMIX, 0, uid, (void *) &param, sizeof (SeCmdSetUpmix));
}
#else
static void _set_upmix (unsigned int uid, bool enable)
{
    SeCmdSetUpmix param = {.upmix = enable ? 1 : 0 };
    if (uid == 0)
    {
        return;
    }

    debug ("%s upmix\n", enable ? "enabe" : "disable");

    aimc_send_command (NULL, SE_CMD_SET_UPMIX, 0, uid, (void *) &param, sizeof (SeCmdSetUpmix));
}
#endif

#ifdef SUPPORT_SOUNDBAR
static void _set_ai_out_ch (unsigned int uid, int out_ch_num)
{
    if (uid == 0)
    {
        warn ("It's wrong uid : 0\n");
        return;
    }

    info ("set the ouput channel number of aisound: %d\n", out_ch_num);

    aimc_set_property (uid, "num_of_out_ch=%d", out_ch_num);
}
#endif

static void _set_fade (unsigned int uid, bool inout)
{
    SeCmdFade param;
    unsigned int cmd;
    if (uid == 0)
    {
        return;
    }

    if (inout)                  // fade in
    {
        cmd = SE_CMD_SET_FADE_IN;
        param.delay = 1792;
        param.duration = 256;

    }
    else                        // fade out
    {
        cmd = SE_CMD_SET_FADE_OUT;
        param.delay = 0;
        param.duration = 256;
    }

    noti ("fade %s \n", inout ? "IN" : "OUT");

    aimc_send_command (NULL, cmd, 0, uid, (void *) &param, sizeof (SeCmdFade));
}

static void _set_number_of_output_channels (unsigned int uid, unsigned int number)
{
    SeCmdSetOutCh param = {.ch = number };

    if (uid == 0)
    {
        return;
    }

    debug ("Set number of output channels %d\n", number);

    aimc_send_command (NULL, SE_CMD_SET_OUTCH, 0, uid, (void *) &param, sizeof (SeCmdSetOutCh));
}

#ifdef SUPPORT_SOUNDBAR
static void _set_output_freq (unsigned int uid, unsigned int freq)
{
    if (uid == 0)
    {
        noti ("It's wrong uid : 0\n");
        return;
    }

    info ("set output frquency: %u\n", freq);
    aimc_set_property (uid, "output_sampling_rate=%u", freq);
}
#endif

#ifdef SUPPORT_DAFC
static void _set_dafc (unsigned int uid, bool onoff)
{
    if (uid == 0)
    {
        warn ("It's wrong uid : 0\n");
        return;
    }

    noti ("dafc is %s mode \n", onoff ? "DAFC" : "FIXED");      /* 1 :DAFC, 0:FIXED */

    aimc_set_property (uid, "flap_mode=%d", onoff);
}

static void _set_dafc_dconf (unsigned int uid, unsigned int dconf, int fsize)
{
    if (uid == 0)
    {
        warn ("It's wrong uid : 0\n");
        return;
    }

    noti ("dafc dconf file is set. %pap (size:%d)\n", &dconf, fsize);

    aimc_set_property (uid, "dconf=%d\\dconf_size=%d", dconf, fsize);
}

static void _set_dafc_sconf (unsigned int uid, unsigned int sconf, int fsize)
{
    if (uid == 0)
    {
        warn ("It's wrong uid : 0\n");
        return;
    }

    noti ("dafc sconf file is set. %pap (size:%d)\n", &sconf, fsize);

    aimc_set_property (uid, "sconf=%d\\sconf_size=%d", sconf, fsize);
}

int se_set_dafc_conf (se_handle_t se, const char *dconf_path, const char *sconf_path)
{
    struct _info *se_info = (struct _info *) se;
    unsigned int uid_flex;
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,11,0)
    loff_t dconf_size = 0, sconf_size = 0;
    int rc_dconf, rc_sconf;
#else
    ssize_t dconf_size = 0, sconf_size = 0;
#endif

    int conf_max_size = MAX_DAFC_CONF_FILE_SIZE;

    if (se == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    if (dconf_addr)
    {
        noti ("Already allocated dconf memory: %pap\n", &dconf_addr);
        hma_free ("audio_buffer", dconf_addr);
        dconf_addr = 0x00;
    }

    if (sconf_addr)
    {
        noti ("Already allocated sconf memory: %pap\n", &sconf_addr);
        hma_free ("audio_buffer", sconf_addr);
        sconf_addr = 0x00;
    }

    /* alloc by PHY addr */
    dconf_addr = hma_alloc_user ("audio_buffer", conf_max_size, 1024, "dafc_dconf");
    sconf_addr = hma_alloc_user ("audio_buffer", conf_max_size, 1024, "dafc_sconf");

    if (!dconf_addr || !sconf_addr)
    {
        error ("cannot allocate \"%s\" dconf_addr:%pap sconf_addr:%pap\n", "audio_buffer",
            &dconf_addr, &sconf_addr);
        goto exit;
    }

    /* convert by VIRTUAL addr */
    dconf_vmap_addr = hma_map (dconf_addr, conf_max_size);
    if (dconf_vmap_addr == NULL)
    {
        error ("hma map failed.\n");
        goto exit;
    }

    sconf_vmap_addr = hma_map (sconf_addr, conf_max_size);
    if (sconf_vmap_addr == NULL)
    {
        error ("hma map failed.\n");
        goto exit;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,11,0)
    rc_dconf =
        kernel_read_file_from_path (dconf_path, &dconf_vmap_addr, &dconf_size, conf_max_size,
        READING_FIRMWARE_PREALLOC_BUFFER);

    info ("path %s, read size %lld\n", dconf_path, dconf_size);

    if (rc_dconf < 0)
    {
        error ("can not find/read %s\n", dconf_path);
        goto exit;
    }

    rc_sconf =
        kernel_read_file_from_path (sconf_path, &sconf_vmap_addr, &sconf_size, conf_max_size,
        READING_FIRMWARE_PREALLOC_BUFFER);

    info ("path %s, read size %lld\n", sconf_path, sconf_size);

    if (rc_sconf < 0)
    {
        error ("can not find/read %s\n", sconf_path);
        goto exit;
    }
#else
    dconf_size =
        kernel_read_file_from_path (dconf_path, 0, &dconf_vmap_addr, conf_max_size, NULL,
        READING_FIRMWARE);

    info ("path %s, read size %ld\n", dconf_path, dconf_size);

    if (dconf_size < 0)
    {
        error ("can not find/read %s\n", dconf_path);
        goto exit;
    }

    sconf_size =
        kernel_read_file_from_path (sconf_path, 0, &sconf_vmap_addr, conf_max_size, NULL,
        READING_FIRMWARE);

    info ("path %s, read size %ld\n", sconf_path, sconf_size);

    if (sconf_size < 0)
    {
        error ("can not find/read %s\n", sconf_path);
        goto exit;
    }
#endif

#ifdef SUPPORT_SOUNDBAR
    uid_flex = se_info->pipeline_flex.module;
#else
    uid_flex = se_info->pipeline_core[SE_CORE_ID_DAP].module;
#endif
    _set_dafc_dconf (uid_flex, (unsigned int) dconf_addr, dconf_size);
    _set_dafc_sconf (uid_flex, (unsigned int) sconf_addr, sconf_size);

    return 0;

  exit:
    if (dconf_vmap_addr)
    {
        hma_unmap (dconf_vmap_addr);
        dconf_vmap_addr = NULL;
    }

    if (sconf_vmap_addr)
    {
        hma_unmap (sconf_vmap_addr);
        sconf_vmap_addr = NULL;
    }

    if (dconf_addr)
    {
        hma_free ("audio_buffer", dconf_addr);
        dconf_addr = 0x00;
    }

    if (sconf_addr)
    {
        hma_free ("audio_buffer", sconf_addr);
        sconf_addr = 0x00;
    }

    return -1;
}

static void _set_dafc_center_extract_status (unsigned int uid, unsigned int status)
{
    if (uid == 0)
    {
        warn ("It's wrong uid : 0\n");
        return;
    }

    noti ("dafc calibration status is set : %d\n", status);

    aimc_set_property (uid, "center_extract_mode=%d", status);

    return;
}

int se_set_dafc_center_extract_status (se_handle_t se, unsigned int status)
{
    struct _info *se_info = (struct _info *) se;
    unsigned int uid_flex;

    if (se == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

#ifdef SUPPORT_SOUNDBAR
    uid_flex = se_info->pipeline_flex.module;
#else
    uid_flex = se_info->pipeline_core[SE_CORE_ID_DAP].module;
#endif
    _set_dafc_center_extract_status (uid_flex, status);

    return 0;
}

int se_set_dafc_by_handle (se_handle_t se, bool onoff)
{
    struct _info *se_info = (struct _info *) se;
    unsigned int uid_module = -1;

    if (se == NULL)
    {
        warn ("invalid handle\n");
        return -1;
    }

#ifdef SUPPORT_SOUNDBAR
    if (se_info->pipeline_flex.module <= 0)
    {
        warn ("invalid module : flap(flex)\n");
        return -1;
    }
    uid_module = se_info->pipeline_flex.module;
#else
    if (se_info->pipeline_core[SE_CORE_ID_DAP].module <= 0)
    {
        warn ("invalid module : flap(flex)\n");
        return -1;
    }
    uid_module = se_info->pipeline_core[SE_CORE_ID_DAP].module;
#endif
    _set_dafc (uid_module, onoff);

    return 0;
}
#endif /* end of SUPPORT_DAFC */

static int _set_lne_data (unsigned int uid)
{
    AisoundCmdSetModel aisound_model = { 0, };
    AisoundCmdSetWeight aisound_weight;
    struct fwload_image_info img_info;

#ifdef _LNX_
    AisoundCmdSetScratch aisound_scratch = { 0, };

    if (fwload_get_image_info (DEFAULT_LNX_MEM_NAME, "weight1", &img_info) == 0)
    {
        noti ("load LNX weight1 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_weight.gen_flags = AISOUND_CMD_GEN1_FLAG;
        aisound_weight.addr = img_info.phys_addr;
        aisound_weight.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_WEIGHT, 0, uid, (void *) &aisound_weight,
            sizeof (AisoundCmdSetWeight));
    }

    if (fwload_get_image_info (DEFAULT_LNX_MEM_NAME, "model1", &img_info) == 0)
    {
        noti ("load LNX model1 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_model.gen_flags = AISOUND_CMD_GEN1_FLAG;
        aisound_model.addr = img_info.phys_addr;
        aisound_model.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_MODEL, 0, uid, (void *) &aisound_model,
            sizeof (AisoundCmdSetModel));
    }

    if (fwload_get_image_info (DEFAULT_LNX_MEM_NAME, "weight2", &img_info) == 0)
    {
        noti ("load LNX weight2 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_weight.gen_flags = AISOUND_CMD_GEN2_FLAG;
        aisound_weight.addr = img_info.phys_addr;
        aisound_weight.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_WEIGHT, 0, uid, (void *) &aisound_weight,
            sizeof (AisoundCmdSetWeight));
    }

    if (fwload_get_image_info (DEFAULT_LNX_MEM_NAME, "model2", &img_info) == 0)
    {
        noti ("load LNX model2 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_model.gen_flags = AISOUND_CMD_GEN2_FLAG;
        aisound_model.addr = img_info.phys_addr;
        aisound_model.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_MODEL, 0, uid, (void *) &aisound_model,
            sizeof (AisoundCmdSetModel));
    }

    if (fwload_get_image_info (DEFAULT_LNX_MEM_NAME, "weight4", &img_info) == 0)
    {
        noti ("load LNX weight4 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_weight.gen_flags = AISOUND_CMD_GEN4_FLAG;
        aisound_weight.addr = img_info.phys_addr;
        aisound_weight.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_WEIGHT, 0, uid, (void *) &aisound_weight,
            sizeof (AisoundCmdSetWeight));
    }

    if (fwload_get_image_info (DEFAULT_LNX_MEM_NAME, "model4", &img_info) == 0)
    {
        noti ("load LNX model4 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_model.gen_flags = AISOUND_CMD_GEN4_FLAG;
        aisound_model.addr = img_info.phys_addr;
        aisound_model.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_MODEL, 0, uid, (void *) &aisound_model,
            sizeof (AisoundCmdSetModel));
    }

    if (lnx_scratch.base)
    {
        noti ("Already allocated scratch memory: %pap\n", &lnx_scratch.base);
        hma_free (DEFAULT_LNX_MEM_NAME, lnx_scratch.base);
        lnx_scratch.base = 0x00;
    }

    lnx_scratch.size = DEFAULT_MEMSIZE_LNX_SCRATCH;
    lnx_scratch.base = hma_alloc_user (DEFAULT_LNX_MEM_NAME, lnx_scratch.size, 1024, "scratch");
    if (!lnx_scratch.base)
    {
        error ("cannot allocate \"%s\". size %d\n", "scratch", lnx_scratch.size);
        return -1;
    }

    noti ("allocate LNX scratch memory %pap 0x%08X\n", &lnx_scratch.base, lnx_scratch.size);

    aisound_scratch.addr = lnx_scratch.base;
    aisound_scratch.size = lnx_scratch.size;
    aimc_send_command (NULL, AISOUND_CMD_SET_SCRATCH, 0, uid, (void *) &aisound_scratch,
        sizeof (AisoundCmdSetScratch));
#else
    if (fwload_get_image_info ("aud1", "weight1", &img_info) == 0)
    {
        noti ("load LNE weight1 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_weight.gen_flags = AISOUND_CMD_GEN1_FLAG;
        aisound_weight.addr = img_info.phys_addr;
        aisound_weight.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_WEIGHT, 0, uid, (void *) &aisound_weight,
            sizeof (AisoundCmdSetModel));

        aisound_model.gen_flags |= AISOUND_CMD_GEN1_FLAG;
    }

    if (fwload_get_image_info ("aud1", "weight2", &img_info) == 0)
    {
        noti ("load LNE weight2 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_weight.gen_flags = AISOUND_CMD_GEN2_FLAG;
        aisound_weight.addr = img_info.phys_addr;
        aisound_weight.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_WEIGHT, 0, uid, (void *) &aisound_weight,
            sizeof (AisoundCmdSetModel));

        aisound_model.gen_flags |= AISOUND_CMD_GEN2_FLAG;
    }

    if (fwload_get_image_info ("aud1", "weight4", &img_info) == 0)
    {
        noti ("load LNE weight4 %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

        aisound_weight.gen_flags = AISOUND_CMD_GEN4_FLAG;
        aisound_weight.addr = img_info.phys_addr;
        aisound_weight.size = img_info.size;
        aimc_send_command (NULL, AISOUND_CMD_SET_WEIGHT, 0, uid, (void *) &aisound_weight,
            sizeof (AisoundCmdSetModel));

        aisound_model.gen_flags |= AISOUND_CMD_GEN4_FLAG;
    }

    if (fwload_get_image_info ("aud1", "model", &img_info) != 0)
    {
        error ("fail to call fwload_wov_get_image_info() for model\n");
        return -1;
    }

    noti ("load LNE model %pap 0x%08X\n", &img_info.phys_addr, img_info.size);

    aisound_model.addr = img_info.phys_addr;
    aisound_model.size = img_info.size;
    aimc_send_command (NULL, AISOUND_CMD_SET_MODEL, 0, uid, (void *) &aisound_model,
        sizeof (AisoundCmdSetModel));
#endif
    return 0;
}

static int _set_lne_lnx2_reset (void)
{
#if defined (CHIP_NAME_o22) || defined (CHIP_NAME_m23)
    _set_lne_reset ();
#elif defined (CHIP_NAME_o24) || defined (CHIP_NAME_o26)
    _set_lnx2_reset ();
#endif
    return 0;
}

#if defined (CHIP_NAME_o22) || defined (CHIP_NAME_m23)
static int _set_lne_reset (void)
{
    unsigned long long start, end;
    unsigned int val = 0x0;

    // AXI Flush Enable
    AUD_SE_REG_WRITE (LNE_SYSREG_BASE + LNE_SYSREG_FLUSH_EN, 0x3);
    AUD_SE_REG_READ (LNE_SYSREG_BASE + LNE_SYSREG_FLUSH_EN, val);       // Code to prevent APB setting reveral

    // AXI Flush Done
    start = ktime_to_us (ktime_get ());
    while (1)
    {
        end = ktime_to_us (ktime_get ());
        AUD_SE_REG_READ (LNE_SYSREG_BASE + LNE_SYSREG_FLUSH_DONE, val);
        if ((val & 0xF) == 0x3)
        {
            info ("AXI Flush Done %llu\n", end - start);
            break;
        }
        else if (end - start > 2000)
        {
            warn ("AXI Flush is not done till timeout (2ms)\n");
            return -ETIME;
        }
    }

    // LNE Reset
#if defined (CHIP_NAME_o22)
    CTOP_CTRL_O22Ax_RdFL (SCRG_CTRL_LNE, crg_lne03);
    CTOP_CTRL_O22Ax_Wr01 (SCRG_CTRL_LNE, crg_lne03, reg_soft_rst_lne_tle0_n, 0x1);
    CTOP_CTRL_O22Ax_WrFL (SCRG_CTRL_LNE, crg_lne03);
    msleep (1);
    CTOP_CTRL_O22Ax_RdFL (SCRG_CTRL_LNE, crg_lne03);
    CTOP_CTRL_O22Ax_Wr01 (SCRG_CTRL_LNE, crg_lne03, reg_soft_rst_lne_tle0_n, 0x0);
    CTOP_CTRL_O22Ax_WrFL (SCRG_CTRL_LNE, crg_lne03);
#elif defined (CHIP_NAME_m23)
    CTOP_CTRL_M23Ax_RdFL (SCRG_CTRL_LNE, crg_lne03);
    CTOP_CTRL_M23Ax_Wr01 (SCRG_CTRL_LNE, crg_lne03, reg_soft_rst_lne_tle0_n, 0x1);
    CTOP_CTRL_M23Ax_WrFL (SCRG_CTRL_LNE, crg_lne03);
    msleep (1);
    CTOP_CTRL_M23Ax_RdFL (SCRG_CTRL_LNE, crg_lne03);
    CTOP_CTRL_M23Ax_Wr01 (SCRG_CTRL_LNE, crg_lne03, reg_soft_rst_lne_tle0_n, 0x0);
    CTOP_CTRL_M23Ax_WrFL (SCRG_CTRL_LNE, crg_lne03);
#endif

    // AXI Flush Disable
    AUD_SE_REG_WRITE (LNE_SYSREG_BASE + LNE_SYSREG_FLUSH_EN, 0x0);
    AUD_SE_REG_READ (LNE_SYSREG_BASE + LNE_SYSREG_FLUSH_EN, val);       // Code to prevent APB Setting reveral

    return 0;
}
#endif

#ifdef _LNX_
static int _set_lnx2_reset (void)
{
    unsigned long long start, end;
    unsigned int val = 0x0;

    // AXI Flush Enable
    AUD_SE_REG_WRITE (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_EN, LNX2_AXI_FLUSH_EN_VAL);
    AUD_SE_REG_READ (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_EN, val);    // Code to prevent APB setting reveral

    // AXI Flush Done Polling
    start = ktime_to_us (ktime_get());
    while (1)
    {
        end = ktime_to_us (ktime_get ());
        AUD_SE_REG_READ (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_DONE, val);
        if ((val & LNX2_AXI_FLUSH_EN_VAL) == LNX2_AXI_FLUSH_EN_VAL)
        {
            info ("AXI Flush Done %llu\n", end - start);
            break;
        }
        else if (end - start > 2000)
        {
            warn ("AXI Flush is not done till timeout (2ms)\n");
            return -ETIME;
        }
    }
#ifndef CHIP_TYPE_FPGA
#if defined(CHIP_NAME_o24)
    // LNX CRG Reset Assert (core & axi_flush) (axi_flush for axi_async)
    CTOP_CTRL_O24Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx23);
    CTOP_CTRL_O24Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx23, reg_soft_rst_lnx2_core_n, 0x1);
    CTOP_CTRL_O24Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx23, reg_soft_rst_lnx2_axi_flush_n, 0x1);
    CTOP_CTRL_O24Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx23);
    CTOP_CTRL_O24Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx23);   // Code to prevent APB setting reveral

    // AXI Flush Disable
    AUD_SE_REG_WRITE (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_EN, 0x0);
    AUD_SE_REG_READ (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_EN, val);  // Code to prevent APB setting reveral

    // LNX CRG Reset Assert (apb, core & axi_flush)
    CTOP_CTRL_O24Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx23);
    CTOP_CTRL_O24Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx23, reg_soft_rst_lnx2_apb_n, 0x1);
    CTOP_CTRL_O24Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx23);

    // LNX CRG Reset Release
    CTOP_CTRL_O24Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx23);
    CTOP_CTRL_O24Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx23, reg_soft_rst_lnx2_core_n, 0x0);
    CTOP_CTRL_O24Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx23, reg_soft_rst_lnx2_axi_flush_n, 0x0);
    CTOP_CTRL_O24Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx23, reg_soft_rst_lnx2_apb_n, 0x0);
    CTOP_CTRL_O24Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx23);
    CTOP_CTRL_O24Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx23);   // Code to prevent APB setting reveral
#elif defined(CHIP_NAME_o26)
    // LNX CRG Reset Assert (core & axi_flush) (axi_flush for axi_async)
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2003);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2003, reg_soft_rst_lnx2_core_n, 0x1);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx2003);
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2003);   // Code to prevent APB setting reveral

    // AXI Flush Disable
    AUD_SE_REG_WRITE (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_EN, 0x0);
    AUD_SE_REG_READ (LNX2_HCR_HOST + LNX2_HCR_HOST_AXI_FLUSH_EN, val);    // Code to prevent APB setting reveral

    // LNX CRG Reset Assert (apb, core & axi_flush)
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2003);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2003, reg_soft_rst_lnx2_apb_async_n, 0x1);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx2003);

    // LNX CRG Reset Release
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2003);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2003, reg_soft_rst_lnx2_core_n, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2003, reg_soft_rst_lnx2_apb_async_n, 0x0);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx2003);
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2003);   // Code to prevent APB setting reveral
#endif
#endif
    return 0;
}

#ifndef SUPPORT_SOUNDBAR
static int _set_lnx2_clk_gate (bool on)
{
#ifndef CHIP_TYPE_FPGA
    unsigned int flags;

    if (lx_board_opt () & LX_BOARD_OPT_SLT)
    {
        on = false;

        noti ("LNX clk gating is off in SLT mode.\n");
    }

    info ("LNX clk gating %s. LNX clk %s\n", (on) ? "ON" : "OFF", (on) ? "OFF" : "ON");

    CTOP_CTRL_EnterCriticalSection (LNX_CLK_GATE_KEY, flags);

    if (on)                     // clk off
    {
        _set_lnx2_reset ();     // lnx2 reset and axi flush

#if defined(CHIP_NAME_o24)
        CTOP_CTRL_O24Ax_RdFL (MICOM_PW_CTRL, power_02);
        CTOP_CTRL_O24Ax_Wr01 (MICOM_PW_CTRL, power_02, reg_lnx2_ipw_clk_gate_en, 0x1);
        CTOP_CTRL_O24Ax_WrFL (MICOM_PW_CTRL, power_02);
#elif defined(CHIP_NAME_o26)
        CTOP_CTRL_O26Ax_RdFL (MICOM_PW_CTRL, power_02);
        CTOP_CTRL_O26Ax_Wr01 (MICOM_PW_CTRL, power_02, reg_lnx2_ipw_clk_gate_en, 0x1);
        CTOP_CTRL_O26Ax_WrFL (MICOM_PW_CTRL, power_02);
#endif
    }
    else                        // clk on
    {
#if defined (CHIP_NAME_o24)
        CTOP_CTRL_O24Ax_RdFL (MICOM_PW_CTRL, power_02);
        CTOP_CTRL_O24Ax_Wr01 (MICOM_PW_CTRL, power_02, reg_lnx2_ipw_clk_gate_en, 0x0);
        CTOP_CTRL_O24Ax_WrFL (MICOM_PW_CTRL, power_02);
#elif defined (CHIP_NAME_o26)
        CTOP_CTRL_O26Ax_RdFL (MICOM_PW_CTRL, power_02);
        CTOP_CTRL_O26Ax_Wr01 (MICOM_PW_CTRL, power_02, reg_lnx2_ipw_clk_gate_en, 0x0);
        CTOP_CTRL_O26Ax_WrFL (MICOM_PW_CTRL, power_02);
#endif
    }

    CTOP_CTRL_ExitCriticalSection (LNX_CLK_GATE_KEY, flags);
#endif
    return 0;
}
#endif /* End of SUPPORT_SOUNDBAR */
#endif /* End of LNX */

static int _create (struct aud_block_info *block)
{
    struct _info *se_info = (struct _info *) block;

    noti ("create se");

    if (block == NULL)
    {
        error ("se_info is NULL!!");
        return -EINVAL;
    }

    block->isOpened = true;

    se_info->number_of_output_channels = DEFAULT_NUMBER_OF_OUTPUT_CHANNELS;
    se_info->event_id = 0;
    se_info->cb_func = NULL;
    se_info->cb_param = NULL;
    se_info->suspended = false;

#ifndef SUPPORT_SOUNDBAR
#ifdef _LNX_
    _set_lnx2_clk_gate (true);  // clk off
#endif
#endif

    noti ("done");
    return 0;
}

static void _destroy (struct aud_block_info *block)
{
    struct _info *se_info = (struct _info *) block;
    int i;

    if (block == NULL)
    {
        warn ("se_info is NULL!!");
        return;
    }

    if (block->isOpened == false)
    {
        noti ("se is already closed. \n");
        return;
    }

    // Clear a se resource.
    block->isOpened = false;

    if (se_info->event_id > 0)
        aimc_unregister_named_event (se_info->event_id);
    se_info->event_id = 0;

#ifdef SUPPORT_SOUNDBAR
    _disconnect_pipelines (se_info);

    bm_unregister_port_forward (block, PORT_IN, 0);
    bm_unregister_port_forward (block, PORT_OUT, 0);

    _destroy_pipeline (&se_info->pipeline_ai);
    _destroy_pipeline (&se_info->pipeline_content_se);
    _destroy_pipeline (&se_info->pipeline_flex);
    _destroy_pipeline (&se_info->pipeline_device_se);
#else
    _disconnect_pipelines (se_info);

    for (i = 0; i < ARRAY_SIZE (se_info->pipeline_in); i++)
    {
        _destroy_pipeline (&se_info->pipeline_in[i]);
    }

    for (i = 0; i < SE_CORE_ID_MAX; i++)
    {
        _destroy_pipeline (&se_info->pipeline_core[i]);
    }
    _destroy_pipeline (&se_info->pipeline_out);
    se_info->block_info.pipeline = NULL;
#endif

    if (_param_list)
    {
        kfree (_param_list);
        _param_list = NULL;
    }

    for (i = 0; i < ARRAY_SIZE (_modules); i++)
    {
        if (_modules[i].param_infos)
        {
            kfree (_modules[i].param_infos);
            _modules[i].param_infos = NULL;
        }
    }

#ifdef _LNX_
    if (lnx_scratch.base)
    {
        noti ("Already allocated scratch memory: %pap\n", &lnx_scratch.base);
        hma_free (DEFAULT_LNX_MEM_NAME, lnx_scratch.base);
        lnx_scratch.base = 0x00;
    }
#endif
#ifdef SUPPORT_DAFC
    if (dconf_vmap_addr)
    {
        hma_unmap (dconf_vmap_addr);
        dconf_vmap_addr = NULL;
    }

    if (sconf_vmap_addr)
    {
        hma_unmap (sconf_vmap_addr);
        sconf_vmap_addr = NULL;
    }

    if (dconf_addr)
    {
        noti ("Already allocated dconf memory: %pap\n", &dconf_addr);
        hma_free ("audio_buffer", dconf_addr);
        dconf_addr = 0x00;
    }

    if (sconf_addr)
    {
        noti ("Already allocated sconf memory: %pap\n", &sconf_addr);
        hma_free ("audio_buffer", sconf_addr);
        sconf_addr = 0x00;
    }
#endif /* end of SUPPORT_DAFC */
    noti ("done\n");
}

static int _suspend (struct aud_block_info *block)
{
    struct _info *se_info = (struct _info *) block;
#ifndef SUPPORT_SOUNDBAR
    int i;
#endif

    noti ("suspend se\n");

#ifdef SUPPORT_SOUNDBAR
    _disconnect_pipelines (se_info);

    bm_unregister_port_forward (block, PORT_IN, 0);
    bm_unregister_port_forward (block, PORT_OUT, 0);

    _destroy_pipeline (&se_info->pipeline_ai);
    _destroy_pipeline (&se_info->pipeline_content_se);
    _destroy_pipeline (&se_info->pipeline_flex);
    _destroy_pipeline (&se_info->pipeline_device_se);
#else
    for (i = 0; i < ARRAY_SIZE (se_info->pipeline_in); i++)
    {
        if (se_info->pipeline_in[i].pipeline != NULL)
        {
            bm_unregister_port_forward (&se_info->block_info, PORT_IN, i);
        }

        _destroy_pipeline (&se_info->pipeline_in[i]);
    }

    for (i = 0; i < SE_CORE_ID_MAX; i++)
    {
        _destroy_pipeline (&se_info->pipeline_core[i]);
    }
    _destroy_pipeline (&se_info->pipeline_out);
    se_info->block_info.pipeline = NULL;
#endif

    se_info->suspended = true;

#ifdef _LNX_
    lnx2_dump_cnt = 0;

    if (lnx_scratch.base)
    {
        noti ("Already allocated scratch memory: %pap\n", &lnx_scratch.base);
        hma_free (DEFAULT_LNX_MEM_NAME, lnx_scratch.base);
        lnx_scratch.base = 0x00;
    }
#endif
    return 0;
}

static int _resume (struct aud_block_info *block)
{
    struct _info *se_info = (struct _info *) block;

    noti ("resume se\n");

    if (se_info->suspended == false)
        se_info->suspended = true;;

    if (se_info->cb_func)
    {
        se_info->cb_func ((void *) se_info->cb_param);
    }

    se_info->suspended = false;

    return 0;
}

int se_make_func_list (void)
{
    if (_parameter_info_loaded)
    {
        trace ("Already initialized\n");
        return 0;
    }

    if (_get_parameter_info () != 0)
    {
        error ("fail to get parmeter infomations\n");
        return -1;
    }

    if (_make_parameter_list () != 0)
    {
        error ("fail to make parmeter infomations\n");
        return -1;
    }

    _parameter_info_loaded = true;

    return 0;
}

void se_initializer (void)
{
    bm_block_registry (&_block_impl);
    bm_block_registry (&_block_impl_lgse_ll);
}

int se_set_callback (se_handle_t se, se_callback_func cb_func, void *cb_param)
{
    struct _info *se_info = (struct _info *) se;
    se_info->cb_func = cb_func;
    se_info->cb_param = cb_param;

    return 0;
}

int se_get_parameter_list (struct se_param_info **list)
{
    if (!_parameter_info_loaded)
    {
        return -1;
    }

    info ("Get parameter list %d\n", _num_of_params);

    *list = _se_param_info_list;

    return _num_of_params;
}

int se_get_param (se_handle_t se, struct se_param *param)
{
    struct _info *se_info = (struct _info *) se;
    struct _module *module = NULL;
    unsigned int param_id = -1;
    struct mod_cmd_se_cmn_param_info *param_info = NULL;
    unsigned int uid = 0, temp_uid = 0;
    struct mod_cmd_se_cmn_param_data *param_data = NULL;
    unsigned int size = 0;
    int i;

    if (se == NULL || param == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    if (param->index > _num_of_params || param->data == NULL)
    {
        error ("invalid parameters %d %p\n", param->index, param->data);
        return -1;
    }

    if (_param_list[param->index] == NULL)
    {
        error ("SE PARAM info list is not loaded\n");
        return -1;
    }

    for (i = 0; i < ARRAY_SIZE (_modules); i++)
    {
        module = _modules + i;
        param_id = _param_list[param->index][i];

        if (param_id != -1)
        {
            break;
        }
    }

    if (module == NULL || param_id == -1)
    {
        error ("can't find paramter info %d\n", param->index);
        return -1;
    }

    param_info = module->param_info_list[param_id];
    size =
        sizeof (struct mod_cmd_se_cmn_param_data) + param_info->name_size + param_info->param_size;

    info ("Get parameter %s from %s\n", param_info->name, module->name);

    uid = _get_module_uid (se_info, module->name);
    if (uid == 0)
    {
        temp_uid = aimc_module_create (module->name, -1);
        if (temp_uid == 0)
        {
            return -1;
        }

        uid = temp_uid;
    }

    param_data = kmalloc (size, GFP_KERNEL);
    if (param_data == NULL)
    {
        error ("no memory\n");
        return -1;
    }

    param_data->name_size = param_info->name_size;
    param_data->data_size = param_info->param_size;
    memcpy (param_data->name_data, param_info->name, param_data->name_size);

    aimc_send_command_return (NULL, MOD_CMD_SE_CMN_GET_PARAM_DATA, 0, uid, param_data, size);

    memcpy (param->data, param_data->name_data + param_data->name_size, param_data->data_size);
    kfree (param_data);

    if (temp_uid != 0)
    {
        aimc_module_destroy (temp_uid);
    }

    return 0;
}

int se_set_param (se_handle_t se, struct se_param *param)
{
    struct _info *se_info = (struct _info *) se;
    struct _module *module = NULL;
    unsigned int param_id = -1;
    struct mod_cmd_se_cmn_param_info *param_info = NULL;
    struct mod_cmd_se_cmn_param_data *param_data = NULL;
    unsigned int size = 0;
    int i;

    if (se == NULL || param == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    if (param->index > _num_of_params || param->data == NULL)
    {
        error ("invalid parameters %d %p\n", param->index, param->data);
        return -1;
    }

    if (_param_list[param->index] == NULL)
    {
        error ("SE PARAM info list is not loaded\n");
        return -1;
    }

    for (i = 0; i < ARRAY_SIZE (_modules); i++)
    {
        module = _modules + i;
        param_id = _param_list[param->index][i];

        if (param_id != -1)
        {
            break;
        }
    }

    if (module == NULL || param_id == -1)
    {
        error ("can't find paramter info %d\n", param->index);
        return -1;
    }

    param_info = module->param_info_list[param_id];
    size =
        sizeof (struct mod_cmd_se_cmn_param_data) + param_info->name_size + param_info->param_size;

    param_data = kmalloc (size, GFP_KERNEL);
    if (param_data == NULL)
    {
        error ("no memory\n");
        return -1;
    }

    param_data->name_size = param_info->name_size;
    param_data->data_size = param_info->param_size;
    memcpy (param_data->name_data, param_info->name, param_data->name_size);
    memcpy (param_data->name_data + param_data->name_size, param->data, param_data->data_size);

    for (i = 0; i < ARRAY_SIZE (_modules); i++)
    {
        struct _module *module = _modules + i;
        unsigned int uid = _get_module_uid (se_info, module->name);
        unsigned int param_id = _param_list[param->index][i];

        if (uid == 0 || param_id == -1)
        {
            continue;
        }

        info ("Set parameter %s to %s\n", param_info->name, module->name);

        aimc_send_command (NULL, MOD_CMD_SE_CMN_SET_PARAM_DATA, 0, uid, param_data, size);
    }

    kfree (param_data);

    return 0;
}

#ifdef SUPPORT_SOUNDBAR
static int _se_set_mode_sb (se_handle_t se, struct se_mode_info *mode_info, char *type_name)
{
    struct _info *se_info = (struct _info *) se;
    struct aud_block_info *block = (struct aud_block_info *) se;
    bool aisound_connect = false;
    int ret = 0;

    if (se == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    _set_fade (se_info->pipeline_device_se.module, false);

    msleep (20);

    _disconnect_pipelines (se_info);

    if (se_info->suspended == false)
        bm_disconnect_block (block, 0);

    if ((mode_info == NULL) || (!strcmp (type_name, "LGSE_NONE")))
    {
        if (mode_info == NULL)
            info ("info is null. clear se block\n");
        else
            info ("type is LGSE_NONE. clear se block\n");

        if (se_info->pipeline_ai.pipeline)
            aisound_connect = true;

        if (se_info->event_id > 0)
            aimc_unregister_named_event (se_info->event_id);
        se_info->event_id = 0;

        bm_unregister_port_forward (block, PORT_IN, 0);
        bm_unregister_port_forward (block, PORT_OUT, 0);
        _destroy_pipeline (&se_info->pipeline_ai);
        _destroy_pipeline (&se_info->pipeline_content_se);
        _destroy_pipeline (&se_info->pipeline_flex);
        _destroy_pipeline (&se_info->pipeline_device_se);

        if (aisound_connect)
        {
            aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP2),
                NULL, 0);
            aisound_connect = false;
        }

        return 0;
    }

    // ai sound
    if (!se_info->pipeline_ai.pipeline)
    {
        if (_create_pipeline (&se_info->pipeline_ai, AI_MODULE_NAME) != 0)
        {
            error ("Cannot create pipeline : %s\n", AI_MODULE_NAME);
            return -1;
        }
        aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP2), NULL,
            0);

        if (_set_lne_lnx2_reset () != 0)
        {
            noti ("Can not reset LNE!\n");
        }

        if (_set_lne_data (se_info->pipeline_ai.module) != 0)
        {
            error ("Can not download lne/lnx image!\n");

            _destroy_pipeline (&se_info->pipeline_ai);
            aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP2),
                NULL, 0);
            return -1;
        }

        bm_register_port_forward (block, PORT_IN, 0, se_info->pipeline_ai.pipeline, 0);
    }

    if (se_info->event_id > 0)
        aimc_unregister_named_event (se_info->event_id);
    se_info->event_id =
        aimc_register_named_event (se_info, _cb_se_lne_lnx_reset, se_info->pipeline_ai.module,
        "lnx_reset", true);
    if (se_info->event_id <= 0)
        noti ("fail to register event %d\n", se_info->event_id);

    // content se
    if (!se_info->pipeline_content_se.pipeline)
    {
        if (_create_pipeline (&se_info->pipeline_content_se, CONTENT_SE_MODULE_NAME) != 0)
        {
            error ("Cannot create pipeline : %s\n", CONTENT_SE_MODULE_NAME);
            return -1;
        }
    }

#ifdef SUPPORT_DAFC
    // flexible renderer
    if (!strcmp (type_name, "LGSE_DAFC"))
    {
        if (!se_info->pipeline_flex.pipeline)
        {
            if (_create_pipeline (&se_info->pipeline_flex, FLEXREN_MODULE_NAME) != 0)
            {
                warn ("Cannot create pipeline : %s\n", FLEXREN_MODULE_NAME);
                return -1;
            }

            ret = se_set_dafc_conf (se, DAFC_FLEX_CONFIGS_DCONF_PATH, DAFC_FLEX_CONFIGS_SCONF_PATH);

            /* true : FLAP DAFC MODE */
            if (ret == 0)
               _set_dafc (se_info->pipeline_flex.module, true);
        }
    }
    else
    {
        _destroy_pipeline (&se_info->pipeline_flex);
    }
#endif

    // device se
    if (!se_info->pipeline_device_se.pipeline)
    {
        if (_create_pipeline (&se_info->pipeline_device_se, DEVICE_SE_MODULE_NAME) != 0)
        {
            error ("Cannot create pipeline : %s\n", DEVICE_SE_MODULE_NAME);
            return -1;
        }

        bm_register_port_forward (block, PORT_OUT, 0, se_info->pipeline_device_se.pipeline, 0);
    }

    _set_bypass (se_info->pipeline_content_se.module, CONTENT_SE_BYPASS);
    _set_bypass (se_info->pipeline_device_se.module, DEVICE_SE_BYPASS);
    _set_upmix (se_info->pipeline_content_se.module, SE_UPMIX_CHANNEL);
    _set_upmix (se_info->pipeline_device_se.module, SE_UPMIX_CHANNEL);
    if (!strcmp (type_name, "LGSE_DAFC"))
    {
        _set_ai_out_ch (se_info->pipeline_ai.module, AI_OUT_CH_DAFC_ON);
        _set_number_of_output_channels (se_info->pipeline_content_se.module,
            CONTENT_SE_OUT_CH_DAFC_ON);
    }
    else
    {
        _set_ai_out_ch (se_info->pipeline_ai.module, AI_OUT_CH_DAFC_OFF);
        _set_number_of_output_channels (se_info->pipeline_content_se.module,
            CONTENT_SE_OUT_CH_DAFC_OFF);
    }
    _set_number_of_output_channels (se_info->pipeline_device_se.module,
        se_info->number_of_output_channels);
    _set_output_freq (se_info->pipeline_device_se.module, se_info->output_freq);

    info ("mode_info->name = %s type_name = %s \n", mode_info->name, type_name);

    if (_connect_pipelines (se_info, mode_info->name, mode_info->port) != 0)
    {
        warn ("Cannot connect pipeline : %s[port:%d]\n", mode_info->name, mode_info->port);
        return -1;
    }

    if (se_info->suspended == false)
    {
        struct aud_block_info *mixer_block = bm_get_block_info_by_index ("mixer", 0);

        // TODO: check output port number of mixer
        if (mixer_block)
            bm_connect_block (mixer_block, 2, block, 0);        // multi-channel
        else
            noti ("mixer block is null\n");
    }

    _set_fade (se_info->pipeline_device_se.module, true);

    return 0;
}
#else
static int _se_set_mode_tv (se_handle_t se, struct se_mode_info *mode_info, char *type_name)
{
    struct _info *se_info = (struct _info *) se;
    int i;
#ifdef SUPPORT_DAFC
    int ret = 0;
#endif
    bool aisound_connect = false;

    if (se == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    _set_fade (se_info->pipeline_out.module, false);

    msleep (20);

    _disconnect_pipelines (se_info);

    if (mode_info == NULL)
    {
        if (se_info->pipeline_core[SE_CORE_ID_AI].pipeline)
            aisound_connect = true;

        for (i = 0; i < ARRAY_SIZE (se_info->pipeline_in); i++)
        {
            if (se_info->pipeline_in[i].pipeline != NULL)
            {
                bm_unregister_port_forward (&se_info->block_info, PORT_IN, i);
            }

            _destroy_pipeline (&se_info->pipeline_in[i]);
        }

        for (i = 0; i < SE_CORE_ID_MAX; i++)
        {
            _destroy_pipeline (&se_info->pipeline_core[i]);
        }
        _destroy_pipeline (&se_info->pipeline_out);
        se_info->block_info.pipeline = NULL;

        if (aisound_connect)
        {
            aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP1),
                NULL, 0);
#ifdef _LNX_
            _set_lnx2_clk_gate (true);  // clk off
#endif
            aisound_connect = false;
        }

        return 0;
    }

    for (i = 0; i < ARRAY_SIZE (se_info->pipeline_in); i++)
    {
        if (se_info->pipeline_in[i].pipeline == NULL)
        {
            if (_create_pipeline (&se_info->pipeline_in[i], "bypass"))
            {
                return -1;
            }

            bm_register_port_forward (&se_info->block_info, PORT_IN, i,
                se_info->pipeline_in[i].pipeline, 0);
        }
    }

    if (se_info->pipeline_out.pipeline == NULL)
    {
        if (!strcmp (type_name, "LGSE_DAP_HP_BT"))
        {
            info ("Connect Only %s for LGSE_DAP_HP_BT\n", DAP_MODULE_NAME);
            if (_create_pipeline (&se_info->pipeline_out, DAP_MODULE_NAME))
            {
                error ("Cannot create pipeline : %s\n", DAP_MODULE_NAME);
                return -1;
            }
        }
        else if (!strcmp (type_name, "LGSE_NONE"))
        {
            info ("Connect Only %s for LGSE_NONE\n", "bypass");
            if (_create_pipeline (&se_info->pipeline_out, "bypass"))
            {
                error ("Cannot create pipeline : %s\n", "bypass");
                return -1;
            }
        }
        else
        {
            if (_create_pipeline (&se_info->pipeline_out, "se"))
            {
                error ("Cannot create pipeline : se\n");
                return -1;
            }
        }

        se_info->block_info.pipeline = se_info->pipeline_out.pipeline;
    }

    _set_bypass (se_info->pipeline_out.module, false);
    _set_upmix (se_info->pipeline_out.module, mode_info->upmix);
    _set_number_of_output_channels (se_info->pipeline_out.module,
        se_info->number_of_output_channels);

    if (se_info->pipeline_core[SE_CORE_ID_AI].pipeline)
    {
        _destroy_pipeline (&se_info->pipeline_core[SE_CORE_ID_AI]);

        aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP1), NULL,
            0);
#ifdef _LNX_
        _set_lnx2_clk_gate (true);      // clk off
#endif
    }

    if (!strcmp (mode_info->name, "ATMOS"))
    {
        const char *pipelineName = apipeline_get_name (se_info->pipeline_out.pipeline);
        if (strcmp (pipelineName, DAP_MODULE_NAME))
        {
            if (_create_pipeline (&se_info->pipeline_core[SE_CORE_ID_DAP], DAP_MODULE_NAME))
            {
                error ("Cannot create pipeline : %s\n", DAP_MODULE_NAME);
                return -1;
            }
        }

        if (se_info->pipeline_core[SE_CORE_ID_AI].pipeline)
        {
            _destroy_pipeline (&se_info->pipeline_core[SE_CORE_ID_AI]);

            aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP1),
                NULL, 0);
#ifdef _LNX_
            _set_lnx2_clk_gate (true);  // clk off
#endif
        }
        _set_bypass (se_info->pipeline_out.module, true);

#ifdef SUPPORT_DAFC
        if (!strcmp (type_name, "LGSE_DAFC"))
        {
            ret = se_set_dafc_conf (se, DAFC_FLEX_CONFIGS_DCONF_PATH, DAFC_FLEX_CONFIGS_SCONF_PATH);

            /* true : FLAP DAFC MODE */
            if (ret == 0)
                _set_dafc (se_info->pipeline_core[SE_CORE_ID_DAP].module, true);
        }
        else
        {
            /* false : FLAP FIXED MODE == DAP */
            _set_dafc (se_info->pipeline_core[SE_CORE_ID_DAP].module, false);
        }
#endif /* end of SUPPORT_DAFC */
    }
    else if (!strcmp (mode_info->name, "AISOUND"))
    {
#ifdef _LNX_
        _set_lnx2_clk_gate (false);     // clk on
#endif
        if (_create_pipeline (&se_info->pipeline_core[SE_CORE_ID_AI], AI_MODULE_NAME))
        {
            error ("Cannot create pipeline : aisound\n");
            return -1;
        }
        aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP1),
            NULL, 0);

        if (_set_lne_lnx2_reset () != 0)
        {
            noti ("Can not reset LNE!\n");
        }

        if (_set_lne_data (se_info->pipeline_core[SE_CORE_ID_AI].module) != 0)
        {
            return -1;
        }

        if (se_info->event_id > 0)
            aimc_unregister_named_event (se_info->event_id);

        se_info->event_id =
            aimc_register_named_event (&se_info->block_info, _cb_se_lne_lnx_reset,
            se_info->pipeline_core[SE_CORE_ID_AI].module, "lnx_reset", true);

        if (se_info->event_id <= 0)
            noti ("fail to register event %d\n", se_info->event_id);
    }
    else
    {
        // Destory when SOUNDENGINE MODE is not 4 (AISOUND)
        if ((se_info->pipeline_core[SE_CORE_ID_AI].pipeline)
            && (strcmp (mode_info->name, "AISOUND")))
        {
            if (se_info->event_id > 0)
                aimc_unregister_named_event (se_info->event_id);
            _destroy_pipeline (&se_info->pipeline_core[SE_CORE_ID_AI]);

            aimc_send_command_sync (NULL, ADEC_CMD_SYNC, 0, AUD_MODID_REGISTRY (ADEC_CORE_DSP1),
                NULL, 0);
#ifdef _LNX_
            _set_lnx2_clk_gate (true);  // clk off
#endif
            noti ("destroy aisound, clk gate TRUE\n");
        }
    }

    info ("mode_info->name = %s type_name = %s \n", mode_info->name, type_name);
    if (_connect_pipelines (se_info, mode_info->name, mode_info->port) != 0)
    {
        error ("Cannot connect pipeline : %s[%d]\n", mode_info->name, mode_info->port);
        return -1;
    }

    _set_fade (se_info->pipeline_out.module, true);

    return 0;
}
#endif

int se_set_mode (se_handle_t se, struct se_mode_info *mode_info, char *type_name)
{
#ifdef SUPPORT_SOUNDBAR
    return _se_set_mode_sb (se, mode_info, type_name);
#else
    return _se_set_mode_tv (se, mode_info, type_name);
#endif
}

int se_set_number_of_output_channels (se_handle_t se, unsigned int number)
{
    struct _info *se_info = (struct _info *) se;
    unsigned int uid_se;

    if (se == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    if (se_info->number_of_output_channels == number)
    {
        return 0;
    }

    se_info->number_of_output_channels = number;
#ifdef SUPPORT_SOUNDBAR
    uid_se = se_info->pipeline_device_se.module;
#else
    uid_se = se_info->pipeline_out.module;
#endif
    _set_number_of_output_channels (uid_se, number);

    return 0;
}

#ifdef SUPPORT_SOUNDBAR
int se_set_output_freq (se_handle_t se, unsigned int freq)
{
    struct _info *se_info = (struct _info *) se;
    unsigned int uid_se;

    if (se == NULL)
    {
        noti ("invalid parameter\n");
        return -1;
    }

    if (se_info->output_freq == freq)
    {
        return 0;
    }

    se_info->output_freq = freq;
    uid_se = se_info->pipeline_device_se.module;
    _set_output_freq (uid_se, freq);

    return 0;
}
#endif

int se_set_dap_output_device (se_handle_t se, unsigned int output_device)
{
#ifdef SUPPORT_SOUNDBAR
    noti ("sound bar: this function is not supported\n");
#else
    struct _info *se_info = (struct _info *) se;
    unsigned int uid = _get_module_uid (se_info, DAP_MODULE_NAME);
    noti ("uid : 0x%08X,  set output device : %d\n", uid, output_device);
    if (uid)
        aimc_set_property (uid, "output_device=%d", output_device);
#endif

    return 0;
}

static int _cb_se_lne_lnx_reset (void *param, int paramLen, void *cbParam)
{
    struct _info *se_info = (struct _info *) cbParam;
    unsigned int uid_se, uid_ai;

#ifdef _LNX_
    int ret = 0, callret = 0;

    if (lnx2_dump_cnt > 65535)
        lnx2_dump_cnt = 0;
    else
        lnx2_dump_cnt++;

    ret = ablind_call_timeout (HZ * 600, &callret, "lnx2dump", lnx2_dump_cnt);
    if (ret == 1)
        noti ("\"lnx2dump\" done. callret %d, dump_cnt:%d \n", callret, lnx2_dump_cnt);
    else if (ret <= 0)
        noti ("\"lnx2dump\" not handled. ret %d\n", ret);
    else
        noti ("\"lnx2dump\" timeout. ret %d\n", ret);
#endif

#ifdef SUPPORT_SOUNDBAR
    uid_se = se_info->pipeline_device_se.module;
    uid_ai = se_info->pipeline_ai.module;
#else
    uid_se = se_info->pipeline_out.module;
    uid_ai = se_info->pipeline_core[SE_CORE_ID_AI].module;
#endif

    _set_fade (uid_se, false);

    if (_set_lne_lnx2_reset () != 0)
    {
        noti ("Can not reset LNE/LNX2 \n");
    }

    if (_set_lne_data (uid_ai) != 0)
    {
        error ("Can not loading LNE/LNX2 FW\n");
        return -1;
    }

    _set_fade (uid_se, true);

    noti ("call cb fn for LNE/LNX2 reset\n");

    return 0;
}
