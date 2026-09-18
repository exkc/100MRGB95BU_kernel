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
 * @ingroup alsa_se
 *
 * @brief
 * ALSA Implementation for Sound engine
 *
 * @author      Youngwoo Jin
 * @version     1.0
 * @date        2020.08.37
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
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/list.h>
#include <sound/soc.h>

#include "se.h"
#include "linux/alsa-ext/alsa-ext-renderer.h"
#include "linux/alsa-ext/tv_alsa-ext-soundengine.h"
#ifdef SUPPORT_DAFC
#include "linux/alsa-ext/alsa-ext-sndout.h"
#endif /* end of SUPPORT_DAFC */
#include "block_manager.h"
#include "alsa_support_sndout.h"

#include "os_util.h"
#include "logm.h"

#include "alsa_se.h"
#if !defined (CHIP_NAME_m23)
#include "common/imc/cmd/module_cmd_lgse_ll.h"
#endif

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define SE_INT_MIN              (0x80000000)
#define SE_INT_MAX              (0x7FFFFFFF)
#define SE_PORT_DOWNMIX         (1)     // 8ch
#define SE_PORT_NORMAL          (0)     // 2ch

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)      logm_trace(alsase,fmt,##args)
#define debug(fmt,args...)      logm_debug(alsase,fmt,##args)
#define info(fmt,args...)       logm_info(alsase,fmt,##args)
#define noti(fmt,args...)       logm_noti(alsase,fmt,##args)
#define warn(fmt,args...)       logm_warning(alsase,fmt,##args)
#define error(fmt,args...)      logm_error(alsase,fmt,##args)

#define MAKE_PRIV(_index, _size)    (((_index & 0xFFFF) << 16) |    \
    (((_size > LGSE_DATA_MAX_SIZE) ? LGSE_DATA_MAX_SIZE : _size) & 0xFFFF))
#define GET_INDEX(_priv)            (_priv >> 16)
#define GET_SIZE(_priv)             (_priv & 0xFFFF)
#define GET_ELEM_TYPE(_unit_size)   ((_unit_size == 1) ? \
    SNDRV_CTL_ELEM_TYPE_BYTES : SNDRV_CTL_ELEM_TYPE_INTEGER)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct alsa_se_type_info
{
    const char *name;
    int base_index;
    bool upmix;
};

struct _type_info
{
    struct list_head list;

    char *name;
    int base_index;
    bool upmix;
    struct _alsa_se_info *alsa_se;

    lgse_se_init_ext_type_t lgse_init;
    lgse_se_mode_ext_type_t lgse_mode;
    bool downmix;

    int lgse_mode_index;
#ifdef SUPPORT_DAFC
    int dafc_conf_status;
    int dafc_center_extract_status;
    int dafc_output_type;
#endif                          /* end of SUPPORT_DAFC */

    unsigned char **param_datas;
    unsigned char **new_param_datas;
};

struct _alsa_se_info
{
    struct list_head list;

    char *name;
    struct snd_soc_card *card;
    se_handle_t handle;
    struct list_head type_list;
    struct _type_info *current_type;
    lgse_index_ouptut_t se_index_output;
};

#if !defined (CHIP_NAME_m23)
struct _lgse_ll_priv
{
    struct aud_block_info *lgse_ll_info;
    int is_opened;
    int is_started;
};

struct _lgse_ll_config_range_type
{
    char *mode_name;
    int min;
    int max;
};
#endif


/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/
extern struct proc_dir_entry *aproc_seetv;

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/
logm_define (alsase, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static const char *_get_mode_name (lgse_se_mode_ext_type_t mode);
static int _change_mode (struct _type_info *type_info, bool bSpeakerOn);
static int _se_callback (void *param);
static bool _get_downmix_mode (struct _type_info *type_info);
static int _kcontrol_init_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_init_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_init_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_mode_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_mode_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_mode_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_downmix_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_downmix_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_downmix_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_matched_output_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_matched_output_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_matched_output_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_param_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_param_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_param_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol);
#ifdef SUPPORT_DAFC
static int _kcontrol_dafc_conf_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_dafc_conf_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_dafc_conf_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_dafc_center_extraction_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_dafc_center_extraction_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_dafc_center_extraction_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_dafc_output_type_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_dafc_output_type_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_dafc_output_type_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
#endif /* end of SUPPORT_DAFC */
static const char *_get_lgse_mode_name (lgse_se_mode_ext_type_t lgse_mode);
static int _proc_se_status_show (struct seq_file *m, void *data);
static int _proc_se_status_open (struct inode *inode, struct file *file);
/**
 * @brief
 * Create alsa se module
 *
 * @details
 * alsa se module 하나를 생성
 *
 * @param[in] name alsa se module name
 * @param[in] card alsa card
 * @return handle of alsa se module
 * @see
 */
static alsa_se_handle_t _se_create (const char *name, struct snd_soc_card *card);

/**
 * @brief
 * Add type for alsa se module
 *
 * @details
 * alsa se module 에서 사용할 type 추가
 *
 * @param[in] handle alsa se module handle
 * @param[in] name type name
 * @param[in] index base index number for type
 * @return result of function call
 * @see
 */
static int _se_add_type (alsa_se_handle_t handle, struct alsa_se_type_info *info);

#if !defined (CHIP_NAME_m23)
static int _kcontrol_ll_ver_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_ver_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_open_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_open_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_open_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_close_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_close_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_close_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_start_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_start_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_start_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_stop_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_stop_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_stop_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_config_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_config_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_config_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_brightness_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_brightness_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _kcontrol_ll_light_freq_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo);
static int _kcontrol_ll_light_freq_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol);
static int _register_lgse_ll_kcontrols (struct snd_soc_card *card);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct list_head _alsa_se_list = LIST_HEAD_INIT (_alsa_se_list);
static bool _initialized = false;
/* *INDENT-OFF* */
static struct
{
    unsigned int number_of_params;
    struct se_param_info *param_list;
} _se_param_info = { 0, NULL, };
/* *INDENT-ON* */

static char *_se_output_name (int id)
{
#define LGSE_OUTPUT_TYPE_TO_STR(_x) case (_x):return #_x

    switch (id)
    {
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_SPK);
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_SPK_BTSUR);
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_BT_BTSUR);
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_ARC);
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_BT);
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_SPK_ARC);
#ifdef SUPPORT_DAFC
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_DAFC);
#endif /* end of SUPPORT_DAFC */
            LGSE_OUTPUT_TYPE_TO_STR (LGSE_NONE);

        default:
            return "LGSE_SPK";
    }
}

static const struct snd_kcontrol_new _kcontrols[] = {
    /* *INDENT-OFF* */
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_SOUNDENGINE_INIT,
        .info = _kcontrol_init_info,
        .get = _kcontrol_init_get,
        .put = _kcontrol_init_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_SOUNDENGINE_MODE,
        .info = _kcontrol_mode_info,
        .get = _kcontrol_mode_get,
        .put = _kcontrol_mode_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_DOWNMIX,
        .info = _kcontrol_downmix_info,
        .get = _kcontrol_downmix_get,
        .put = _kcontrol_downmix_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_SE_INDEX_MATCHED_OUTPUT,
        .info = _kcontrol_matched_output_info,
        .get = _kcontrol_matched_output_get,
        .put = _kcontrol_matched_output_put,
    },
#ifdef SUPPORT_DAFC
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS,
        .info = _kcontrol_dafc_conf_info,
        .get = _kcontrol_dafc_conf_get,
        .put = _kcontrol_dafc_conf_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = SNDOUT_CENTER_EXTRACTION_ONOFF,
        .info = _kcontrol_dafc_center_extraction_info,
        .get = _kcontrol_dafc_center_extraction_get,
        .put = _kcontrol_dafc_center_extraction_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = SNDOUT_DAFC_OUTPUT_TYPE,
        .info = _kcontrol_dafc_output_type_info,
        .get = _kcontrol_dafc_output_type_get,
        .put = _kcontrol_dafc_output_type_put,
    },
#endif /* end of SUPPORT_DAFC */
    /* *INDENT-ON* */
};

#if !defined (CHIP_NAME_m23)
static const struct snd_kcontrol_new _kcontrols_ll[] = {
    /* *INDENT-OFF* */
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_VERSION,
        .access = SNDRV_CTL_ELEM_ACCESS_READ,
        .info = _kcontrol_ll_ver_info,
        .get = _kcontrol_ll_ver_get,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_OPEN,
        .info = _kcontrol_ll_open_info,
        .get = _kcontrol_ll_open_get,
        .put = _kcontrol_ll_open_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_CLOSE,
        .info = _kcontrol_ll_close_info,
        .get = _kcontrol_ll_close_get,
        .put = _kcontrol_ll_close_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_START,
        .info = _kcontrol_ll_start_info,
        .get = _kcontrol_ll_start_get,
        .put = _kcontrol_ll_start_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_STOP,
        .info = _kcontrol_ll_stop_info,
        .get = _kcontrol_ll_stop_get,
        .put = _kcontrol_ll_stop_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_CONFIG,
        .info = _kcontrol_ll_config_info,
        .get = _kcontrol_ll_config_get,
        .put = _kcontrol_ll_config_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_BRIGHTNESS,
        .access = SNDRV_CTL_ELEM_ACCESS_READ,
        .info = _kcontrol_ll_brightness_info,
        .get = _kcontrol_ll_brightness_get,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = LGSE_LL_LIGHT_FREQUENCY,
        .access = SNDRV_CTL_ELEM_ACCESS_READ,
        .info = _kcontrol_ll_light_freq_info,
        .get = _kcontrol_ll_light_freq_get,
    },
    /* *INDENT-ON* */
};

static struct _lgse_ll_config_range_type lgse_ll_config_range[] = {
    /* *INDENT-OFF* */
    { "ll_mode",        0,      7 },
    { "led_unit_num",   2,      100 },
    { "period",         10,     200 },
    { "max_power",      -100,   3 },
    { "min_power",      -100,   3 },
    { "upper_bound",    0,      24000 },
    { "lower_bound",    0,      24000 },
    /* *INDENT-ON* */
};
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops _proc_se_status_fops = {
    .proc_open = _proc_se_status_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static struct file_operations _proc_se_status_fops = {
    .open = _proc_se_status_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};
#endif


/*==============================================================================
    Implementation Group
==============================================================================*/
#if !defined (CHIP_NAME_m23)
static int _kcontrol_ll_ver_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_ver_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;
    int version;
    int ret;

    if (lgse_ll == NULL)
    {
        error ("lgse is null\n");
        return -EINVAL;
    }

    ret = lgse_ll_get_param (lgse_ll->lgse_ll_info, LL_CMD_GET_VERSION, 0, &version);
    if (ret < 0)
    {
        error ("get version err\n");
        return -1;
    }
    ucontrol->value.integer.value[0] = version;

    info ("LL version = 0x%lX\n", ucontrol->value.integer.value[0]);
    return 0;
}

static int _kcontrol_ll_open_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_open_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    ucontrol->value.integer.value[0] = lgse_ll->is_opened;

    return 0;
}

static int _kcontrol_ll_open_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    info ("lgse ll open\n");

    if (lgse_ll->is_opened == 0)
    {
        lgse_ll->lgse_ll_info = bm_create_block ("lgse_ll", -1);

        if (lgse_ll->lgse_ll_info == NULL)
        {
            error ("lgse ll open error\n");
            return -1;
        }

        lgse_ll->is_opened = 1;
    }
    else
    {
        info ("lgse ll already open\n");
    }
    return 0;
}

static int _kcontrol_ll_close_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_close_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    ucontrol->value.integer.value[0] = (lgse_ll->is_opened ? 0 : 1);

    return 0;
}

static int _kcontrol_ll_close_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    if (lgse_ll->is_opened == 1)
    {
        if (lgse_ll->lgse_ll_info == NULL)
        {
            error ("lgse ll is not opened\n");
            return -1;
        }

        bm_disconnect_block (lgse_ll->lgse_ll_info, 0);
        bm_destroy_block (lgse_ll->lgse_ll_info);

        lgse_ll->lgse_ll_info = NULL;
        lgse_ll->is_started = 0;
        lgse_ll->is_opened = 0;
    }
    else
    {
        info ("lgse ll already closed\n");
    }
    return 0;
}

static int _kcontrol_ll_start_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_start_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    ucontrol->value.integer.value[0] = lgse_ll->is_started;

    return 0;
}

static int _kcontrol_ll_start_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;
    struct aud_block_info *mixer_info = bm_get_block_info_by_index ("mixer", 0);

    info ("lgse ll start\n");

    if (lgse_ll->lgse_ll_info == NULL)
    {
        error ("lgse ll is not opened\n");
        return -1;
    }

    if (mixer_info)
        bm_connect_block (mixer_info, 0, lgse_ll->lgse_ll_info, 0);
    else
        noti ("mixer_info is NULL\n");

    lgse_ll->is_started = 1;
    return 0;
}

static int _kcontrol_ll_stop_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_stop_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    ucontrol->value.integer.value[0] = (lgse_ll->is_started ? 0 : 1);

    return 0;
}

static int _kcontrol_ll_stop_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;

    info ("lgse ll start\n");

    if (lgse_ll->lgse_ll_info == NULL)
    {
        noti ("lgse ll is not opened\n");
        return -1;
    }

    bm_disconnect_block (lgse_ll->lgse_ll_info, 0);

    lgse_ll->is_started = 0;

    return 0;
}

static int _kcontrol_ll_config_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 7;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_config_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;
    int params[7] = { };
    int ret;

    if (lgse_ll == NULL)
    {
        error ("lgse is null\n");
        return -(EINVAL);
    }

    ret = lgse_ll_get_param (lgse_ll->lgse_ll_info, LL_CMD_GET_PARAM, 0, params);
    if (ret < 0)
    {
        error ("get parm err\n");
        return -1;
    }

    ucontrol->value.integer.value[0] = params[0];
    ucontrol->value.integer.value[1] = params[1];
    ucontrol->value.integer.value[2] = params[2];
    ucontrol->value.integer.value[4] = params[3];
    ucontrol->value.integer.value[3] = params[4];
    ucontrol->value.integer.value[6] = params[5];
    ucontrol->value.integer.value[5] = params[6];

    info ("mode=%ld, led_num=%ld, period=%ld, max_pow=%ld, min_pow=%ld, up_bnd=%ld, low_bnd=%ld\n",
        ucontrol->value.integer.value[0], ucontrol->value.integer.value[1],
        ucontrol->value.integer.value[2], ucontrol->value.integer.value[3],
        ucontrol->value.integer.value[4], ucontrol->value.integer.value[5],
        ucontrol->value.integer.value[6]);

    return 0;
}

static int _kcontrol_ll_config_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;
    int params[7] = { };
    int ret, i;

    params[0] = ucontrol->value.integer.value[0];
    params[1] = ucontrol->value.integer.value[1];
    params[2] = ucontrol->value.integer.value[2];
    params[3] = ucontrol->value.integer.value[4];
    params[4] = ucontrol->value.integer.value[3];
    params[5] = ucontrol->value.integer.value[6];
    params[6] = ucontrol->value.integer.value[5];

    for (i = 0; i < ARRAY_SIZE (lgse_ll_config_range); i++)
    {
        if ((params[i] < lgse_ll_config_range[i].min) || (params[i] > lgse_ll_config_range[i].max))
        {
            error ("out of range mode=%s, min=%d, max=%d, param[%d]=%d\n",
                lgse_ll_config_range[i].mode_name,
                lgse_ll_config_range[i].min, lgse_ll_config_range[i].max, i, params[i]);
            return -EINVAL;
        }
    }

    ret = lgse_ll_set_param (lgse_ll->lgse_ll_info, LL_CMD_SET_PARAM, 0, params);
    if (ret < 0)
    {
        error ("set param err\n");
        return -1;
    }

    return 0;
}

static int _kcontrol_ll_brightness_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = LGSE_LL_MAX_NUM_LED;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_brightness_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;
    int params[LGSE_LL_MAX_NUM_LED] = { };
    int i;
    int ret;

    ret = lgse_ll_get_param (lgse_ll->lgse_ll_info, LL_CMD_GET_BRIGHTNESS, 0, params);
    if (ret < 0)
    {
        error ("get parm err\n");
        return -1;
    }

    info ("Get Brightness\n");
    for (i = 0; i < LGSE_LL_MAX_NUM_LED; i++)
    {
        ucontrol->value.integer.value[i] = params[i];
        info ("%02d: 0x%08lX\n", i, ucontrol->value.integer.value[i]);
    }

    return 0;
}

static int _kcontrol_ll_light_freq_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;

    return 0;
}

static int _kcontrol_ll_light_freq_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _lgse_ll_priv *lgse_ll = (struct _lgse_ll_priv *) kcontrol->private_data;
    int params[2] = { };
    int i;
    int ret;

    ret = lgse_ll_get_param (lgse_ll->lgse_ll_info, LL_CMD_GET_LIGHT_FREQ, 0, params);
    if (ret < 0)
    {
        error ("get parm err\n");
        return -1;
    }

    info ("Get Light Frequency\n");
    for (i = 0; i < 2; i++)
    {
        ucontrol->value.integer.value[i] = params[i];
        info ("%02d: 0x%08lX\n", i, ucontrol->value.integer.value[i]);
    }

    return 0;
}

static int _register_lgse_ll_kcontrols (struct snd_soc_card *card)
{
    int ret;
    int i;
    struct _lgse_ll_priv *lgse_ll_priv =
        (struct _lgse_ll_priv *) kzalloc (sizeof (struct _lgse_ll_priv), GFP_KERNEL);

    for (i = 0; i < ARRAY_SIZE (_kcontrols_ll); i++)
    {
        struct snd_kcontrol_new kcontrol = _kcontrols_ll[i];

        ret = snd_ctl_add (card->snd_card, snd_ctl_new1 (&kcontrol, lgse_ll_priv));
        if (ret != RET_OK)
        {
            error ("add _kcontrols_ll[%d] is failed (ret %d)\n", i, ret);
            return ret;
        }
    }

    return ret;
}
#endif

static const char *_get_mode_name (lgse_se_mode_ext_type_t mode)
{
    switch (mode)
    {
        default:
        case LGSE_MODE_UNKNOWN:
        case LGSE_MODE_LGSE_VX:
            return NULL;

        case LGSE_MODE_LGSE_ONLY:
            return "SE";

        case LGSE_MODE_LGSE_ATMOS:
            return "ATMOS";

        case LGSE_MODE_LGSE_AISOUND:
            return "AISOUND";
    }
}

static int _change_mode (struct _type_info *type_info, bool bSpeakerOn)
{
    struct se_mode_info mode_info;
    int i;

    mode_info.name = _get_mode_name (type_info->lgse_mode);
    if (mode_info.name == NULL)
    {
        error ("invalid mode %d\n", type_info->lgse_mode);
        return -EINVAL;
    }

    mode_info.port = _get_downmix_mode (type_info) ? SE_PORT_DOWNMIX : SE_PORT_NORMAL;
    mode_info.upmix = type_info->upmix;

    if (bSpeakerOn)
        sndout_speaker_onoff (false);   // mute on, delay 0ms

    se_set_mode (type_info->alsa_se->handle, &mode_info, type_info->name);

    for (i = 0; i < _se_param_info.number_of_params; i++)
    {
        struct se_param param = {
            .index = i,
            .size = _se_param_info.param_list[i].size,
            .data = type_info->param_datas[i],
        };

        if (param.data == NULL)
        {
            continue;
        }

        se_set_param (type_info->alsa_se->handle, &param);
    }

    if (bSpeakerOn)
        sndout_speaker_onoff (true);    // mute off, delay recovery

    return 0;
}

static int _se_callback (void *param)
{
    struct _alsa_se_info *alsa_se = (struct _alsa_se_info *) param;

    if (param == NULL)
    {
        error ("param is null\n");
        return -1;
    }

    if (alsa_se->current_type == NULL)
    {
        return se_set_mode (alsa_se->handle, NULL, NULL);
    }

    return _change_mode (alsa_se->current_type, TRUE);
}

static int _register_func_list (void)
{
    struct _alsa_se_info *alsa_se;

    if (_se_param_info.number_of_params > 0)
    {
        info ("kcontrol list was registered already\n");
        return 0;
    }

    if (se_make_func_list () < 0)
    {
        error ("fail to make function list\n");
        return -1;
    }

    _se_param_info.number_of_params = se_get_parameter_list (&_se_param_info.param_list);
    if (_se_param_info.number_of_params <= 0)
    {
        error ("fail to get parameter list\n");
        return -1;
    }

    list_for_each_entry (alsa_se, &_alsa_se_list, list)
    {
        struct snd_soc_card *card = alsa_se->card;
        struct _type_info *type_info;

        list_for_each_entry (type_info, &alsa_se->type_list, list)
        {
            int ret;
            int i;

            if (type_info->param_datas == NULL)
            {
                unsigned int list_size = sizeof (unsigned char *) * _se_param_info.number_of_params;

                type_info->param_datas = (unsigned char **) kzalloc (list_size, GFP_KERNEL);
                if (type_info->param_datas == NULL)
                {
                    error ("no mem\n");
                    return -ENOMEM;
                }
                type_info->new_param_datas = (unsigned char **) kzalloc (list_size, GFP_KERNEL);
                if (type_info->new_param_datas == NULL)
                {
                    error ("no mem\n");
                    kfree (type_info->param_datas);
                    type_info->param_datas = NULL;
                    return -ENOMEM;
                }
            }

            for (i = 0; i < ARRAY_SIZE (_kcontrols); i++)
            {
                struct snd_kcontrol_new kcontrol = _kcontrols[i];

                kcontrol.index += type_info->base_index;

                ret = snd_ctl_add (card->snd_card, snd_ctl_new1 (&kcontrol, type_info));
                if (ret != RET_OK)
                {
                    if (ret == -EBUSY)
                        info (" controls[%d] is failed (ret %d)\n", i, ret);
                    else
                        warn ("add _kcontrols[%d] is failed (ret %d)\n", i, ret);
                    return ret;
                }
            }

            debug ("add kcontrol %s %d\n", type_info->name, _se_param_info.number_of_params);

            for (i = 0; i < _se_param_info.number_of_params; i++)
            {
                struct snd_kcontrol_new kcontrol = {
                    .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
                    .name = _se_param_info.param_list[i].name,
                    .info = _kcontrol_param_info,
                    .get = _kcontrol_param_get,
                    .put = _kcontrol_param_put,
                    .index = type_info->base_index,
                };
                int param_size = _se_param_info.param_list[i].size;

                if (!strcmp (kcontrol.name, LGSE_MODE))
                {
                    type_info->lgse_mode_index = i;
                }

                do
                {
                    kcontrol.private_value = MAKE_PRIV (i, param_size);

                    ret = snd_ctl_add (card->snd_card, snd_ctl_new1 (&kcontrol, type_info));
                    if (ret != RET_OK)
                    {
                        if (ret == -EBUSY)
                            info ("control[%s:%d] is already used. It's busy (ret %d)\n",
                                kcontrol.name, kcontrol.index, ret);
                        else
                            warn ("add control[%s:%d] is failed (ret %d)\n",
                                kcontrol.name, kcontrol.index, ret);
                        return ret;
                    }

                    trace ("add control[%s] %d 0x%0lx\n", kcontrol.name, kcontrol.index,
                        kcontrol.private_value);

                    kcontrol.index++;
                    param_size -= LGSE_DATA_MAX_SIZE;
                }
                while (param_size > 0);
            }
        }
    }

    return 0;
}

static bool _get_downmix_mode (struct _type_info *type_info)
{
    if ((type_info->lgse_mode == LGSE_MODE_LGSE_ATMOS) ||
        (type_info->lgse_mode == LGSE_MODE_LGSE_AISOUND))
    {
        return true;
    }

    return type_info->downmix;
}

// LGSE_SOUNDENGINE_INIT
static int _kcontrol_init_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_init_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return RET_ERROR;
    }

    ucontrol->value.integer.value[0] = type_info->lgse_init;

    info ("LGSE SOUNDENGINE INIT=0x%lX\n", ucontrol->value.integer.value[0]);
    return 0;
}

static int _kcontrol_init_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    lgse_se_init_ext_type_t lgse_init = ucontrol->value.integer.value[0];

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if (lgse_init > LGSE_INIT_LGSE_AISOUND)
    {
        noti ("lgse init(%u) is LGSE_INIT_LGSE_AISOUND(%d).\n", lgse_init, LGSE_INIT_LGSE_AISOUND);
        return -EINVAL;
    }

    if (lgse_init == LGSE_INIT_LGSE_VX)
    {
        noti ("LGSE_INIT_LGSE_VX is not supported, set LGSE_INIT_LGSE_ONLY\n");
        lgse_init = LGSE_INIT_LGSE_ONLY;
    }
    else if (lgse_init == LGSE_INIT_LGSE_VX_AISOUND)
    {
        noti ("LGSE_INIT_LGSE_VX_AISOUND is not supported, set LGSE_INIT_LGSE_ONLY\n");
        lgse_init = LGSE_INIT_LGSE_ONLY;
    }

    type_info->lgse_init = lgse_init;

    info ("LGSE SOUNDENGINE INIT=%d\n", type_info->lgse_init);
    return 0;
}

// LGSE_SOUNDENGINE_MODE
static int _kcontrol_mode_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_mode_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    ucontrol->value.integer.value[0] = type_info->lgse_mode;

    info ("LGSE SOUNDENGINE MODE=0x%lX (idx=%d)\n", ucontrol->value.integer.value[0],
        ucontrol->id.index);
    return 0;
}

static int _kcontrol_mode_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    lgse_se_mode_ext_type_t mode_ext_type = ucontrol->value.integer.value[0];

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if (mode_ext_type == LGSE_MODE_LGSE_VX)
    {
        error ("LGSE_MODE_LGSE_VX is not supported, set LGSE_MODE_LGSE_ONLY\n");
        return -EINVAL;
    }

    if (mode_ext_type > LGSE_MODE_LGSE_AISOUND || mode_ext_type == LGSE_MODE_UNKNOWN)
    {
        warn ("SE mode is invalid (%d)\n", mode_ext_type);
        return -EINVAL;
    }

#ifdef SUPPORT_SOUNDBAR
    type_info->lgse_mode = mode_ext_type;
#else
    if (type_info->lgse_mode != mode_ext_type)
    {
        type_info->lgse_mode = mode_ext_type;

        if (type_info->alsa_se->current_type == type_info)
        {
            if (_change_mode (type_info, TRUE) != 0)
            {
                return -EINVAL;
            }
        }
    }
#endif

    noti ("LGSE SOUNDENGINE MODE=0x%X (%s idx=%d)\n", mode_ext_type, type_info->name,
        type_info->base_index);
    return 0;
}

// LGSE_DONWMIX_MODE
static int _kcontrol_downmix_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_downmix_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    ucontrol->value.integer.value[0] = type_info->downmix;

    info ("LGSE DOWNMIX=0x%lX\n", ucontrol->value.integer.value[0]);
    return 0;
}

/*
 * COMMON_SPK
 * LGSE_MODE_LGSE_ONLY
 * DOWNMIX off
 * MIX_0 -- SE -- OUT_SPK -- PCM
 * DOWNMIX on
 * PCMREN -- SE -- OUT_SPK -- PCM
 */
static int _kcontrol_downmix_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    bool enable = ! !ucontrol->value.integer.value[0];

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%d)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if (ucontrol->value.integer.value[0] != 0 && ucontrol->value.integer.value[0] != 1)
    {
        error ("invalid value (%ld)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

#ifdef SUPPORT_SOUNDBAR
    type_info->downmix = enable;
#else
    if (type_info->downmix != enable)
    {
        bool pre_downmix_mode = _get_downmix_mode (type_info);

        type_info->downmix = enable;

        if ((type_info->alsa_se->current_type == type_info) &&
            (_get_downmix_mode (type_info) != pre_downmix_mode))
        {
            if (_change_mode (type_info, TRUE) != 0)
            {
                return -EINVAL;
            }
        }
    }
#endif

    noti ("LGSE DOWNMIX=%d (%s idx=%d)\n", enable, type_info->name, type_info->base_index);
    return 0;
}

static int _kcontrol_matched_output_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
#ifdef SUPPORT_DAFC
    uinfo->count = 5;
#else
    uinfo->count = 4;
#endif
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_matched_output_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    alsa_se_handle_t handle;

    handle = alsa_se_get_handle ("COMMON_SPK");
    if (handle == NULL)
    {
        noti ("handle of COMMON_SPK is NULL\n");
        ucontrol->value.integer.value[0] = LGSE_NONE;
    }
    else
        ucontrol->value.integer.value[0] = handle->se_index_output;

    handle = alsa_se_get_handle ("COMMON_SE_BT");
    if (handle == NULL)
    {
        noti ("handle of COMMON_SE_BT is NULL\n");
        ucontrol->value.integer.value[1] = LGSE_NONE;
    }
    else
        ucontrol->value.integer.value[1] = handle->se_index_output;

    handle = alsa_se_get_handle ("COMMON_SE_ARC");
    if (handle == NULL)
    {
        noti ("handle of COMMON_SE_ARC is NULL\n");
        ucontrol->value.integer.value[2] = LGSE_NONE;
    }
    else
        ucontrol->value.integer.value[2] = handle->se_index_output;

    handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");
    if (handle == NULL)
    {
        noti ("handle of COMMON_DAP_HP_BT is NULL\n");
        ucontrol->value.integer.value[3] = LGSE_NONE;
    }
    else
        ucontrol->value.integer.value[3] = handle->se_index_output;

#ifdef SUPPORT_DAFC
    handle = alsa_se_get_handle ("COMMON_DAFC");
    if (handle == NULL)
    {
        noti ("handle of COMMON_DAFC is NULL\n");
        ucontrol->value.integer.value[4] = LGSE_NONE;
    }
    else
        ucontrol->value.integer.value[4] = handle->se_index_output;
#endif /* end of SUPPORT_DAFC */

#ifdef SUPPORT_DAFC
    info ("Get LGSE SE INDEX MATCHED OUTPUT 0:%ld, 1:%ld, 2:%ld, 3:%ld, 4:%ld \n",
        ucontrol->value.integer.value[0], ucontrol->value.integer.value[1],
        ucontrol->value.integer.value[2], ucontrol->value.integer.value[3],
        ucontrol->value.integer.value[4]);
#else
    info ("Get LGSE SE INDEX MATCHED OUTPUT 0:%ld, 1:%ld, 2:%ld, 3:%ld \n",
        ucontrol->value.integer.value[0], ucontrol->value.integer.value[1],
        ucontrol->value.integer.value[2], ucontrol->value.integer.value[3]);
#endif /* end of SUPPORT_DAFC */

    return 0;
}

static int _kcontrol_matched_output_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct aud_block_info *block_info;
    alsa_se_handle_t handle;

    common_output_ext_type_t output = ucontrol->value.integer.value[0];
    lgse_index_ouptut_t index = ucontrol->value.integer.value[1];

    switch (output)
    {
        case COMMON_SPK:
            handle = alsa_se_get_handle ("COMMON_SPK");
            break;
        case COMMON_SE_BT:
        case COMMON_SE_BT_SUR:
            handle = alsa_se_get_handle ("COMMON_SE_BT");
            break;
        case COMMON_SE_ARC:
            handle = alsa_se_get_handle ("COMMON_SE_ARC");
            break;
        case COMMON_DAP_HP_BT:
            handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");
            break;
#ifdef SUPPORT_DAFC
        case COMMON_DAFC:
            handle = alsa_se_get_handle ("COMMON_DAFC");
            break;
#endif /* end of SUPPORT_DAFC */
        default:
            handle = NULL;
    }
    if (handle == NULL)
    {
        noti ("Invalid output type (%d)\n", output);
        return -EINVAL;
    }

    if ((index != LGSE_SPK) && (index != LGSE_SPK_BTSUR)
        && (index != LGSE_BT_BTSUR) && (index != LGSE_ARC)
        && (index != LGSE_BT) && (index != LGSE_SPK_ARC) && (index != LGSE_NONE)
#ifdef SUPPORT_DAFC
        && (index != LGSE_DAFC)
#endif /* end of SUPPORT_DAFC */
        )
    {
        noti ("Invalid index (%d)\n", index);
        return -EINVAL;
    }

    block_info = alsa_se_get_block (handle);

    // Only set type, if SE module is existed
    if (block_info != NULL)
    {
        if ((output_is_added (output)) || ((output == COMMON_SE_BT)
                && (output_is_added (COMMON_SE_BT_SUR))))
        {
            alsa_se_set_type (handle, _se_output_name (index));
            info ("Only set type when SE Moudle is existed\n");
        }
    }
    else
        noti ("block info is null\n");

    handle->se_index_output = index;

    info ("LGSE SE INDEX 0x%x MATCHED OUTPUT=0x%x %s\n", index, output, _se_output_name (index));
    return 0;
}

static int _kcontrol_param_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    unsigned int param_index = GET_INDEX (kcontrol->private_value);
    unsigned int param_size = GET_SIZE (kcontrol->private_value);
    struct se_param_info *param_info = _se_param_info.param_list + param_index;

    if (param_index >= _se_param_info.number_of_params)
    {
        error ("invalid value 0x%0lx\n", kcontrol->private_value);
        return -1;
    }

    info ("[%s]private value 0x%0lx\n", kcontrol->id.name, kcontrol->private_value);

    uinfo->type = GET_ELEM_TYPE (param_info->unit_size);
    uinfo->count = param_size / param_info->unit_size;

    if (uinfo->type == SNDRV_CTL_ELEM_TYPE_INTEGER)
    {
        uinfo->value.integer.min = SE_INT_MIN;
        uinfo->value.integer.max = SE_INT_MAX;
    }

    return 0;
}

static int _kcontrol_param_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    unsigned int offset = (ucontrol->id.index % 10) * LGSE_DATA_MAX_SIZE;
    unsigned int param_index = GET_INDEX (kcontrol->private_value);
    unsigned int param_size = GET_SIZE (kcontrol->private_value);
    struct se_param_info *param_info = _se_param_info.param_list + param_index;
    unsigned char *param_data = NULL;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if (param_index >= _se_param_info.number_of_params)
    {
        error ("invalid value 0x%0lx\n", kcontrol->private_value);
        return -1;
    }

    info ("[%s] %s(%d) get lgse param(0x%0lx)\n", kcontrol->id.name, type_info->name,
        type_info->base_index, kcontrol->private_value);

    param_data = type_info->param_datas[param_index];
    if (param_data == NULL)
    {
        struct se_param param = {
            .index = param_index,
            .size = param_info->size,
        };
        int ret;

        param_data = (unsigned char *) kmalloc (param_info->size, GFP_KERNEL);
        if (param_data == NULL)
        {
            error ("no mem\n");
            return -ENOMEM;
        }

        type_info->param_datas[param_index] = param_data;
        param.data = param_data;

        ret = se_get_param (type_info->alsa_se->handle, &param);
        if (ret)
        {
            error ("[%s] %s(%d) fail to se_get_param %d\n", kcontrol->id.name,
                type_info->name, type_info->base_index, ret);
            return -EINVAL;
        }
    }

    if (param_info->unit_size == 1)
    {
        memcpy (ucontrol->value.bytes.data, param_data + offset, param_size);
    }
    else
    {
        int *buffer = (int *) (param_data + offset);
        int i;

        for (i = 0; i < (param_size / param_info->unit_size); i++)
        {
            ucontrol->value.integer.value[i] = buffer[i];
        }
    }

    return 0;
}

static int _kcontrol_param_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    unsigned int offset = (ucontrol->id.index % 10) * LGSE_DATA_MAX_SIZE;
    unsigned int size = GET_SIZE (kcontrol->private_value);
    unsigned int param_index = GET_INDEX (kcontrol->private_value);
    unsigned int param_size = GET_SIZE (kcontrol->private_value);
    struct se_param_info *param_info = _se_param_info.param_list + param_index;
    unsigned char *param_data = NULL;
    unsigned char *new_param_data = NULL;
    unsigned int param_send_idx = ucontrol->id.index;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if (param_index >= _se_param_info.number_of_params)
    {
        error ("invalid value 0x%0lx\n", kcontrol->private_value);
        return -1;
    }

    info ("[%s] %s(%d) set lgse param(0x%0lx)\n", kcontrol->id.name, type_info->name,
        type_info->base_index, kcontrol->private_value);

    if (ucontrol->id.index % 10 == 0)
    {
        int data_value = (param_info->unit_size == 4) ?
            ucontrol->value.integer.value[param_info->order] :
            ucontrol->value.bytes.data[param_info->order];

        if ((data_value < param_info->min_value) || (data_value > param_info->max_value))
        {
            error ("[%s] %s(%d) check param fail (%d %d %d)\n", kcontrol->id.name, type_info->name,
                type_info->base_index, param_info->min_value, param_info->max_value, data_value);
            return -EINVAL;
        }
    }

    new_param_data = type_info->new_param_datas[param_index];
    if (new_param_data == NULL)
    {
        new_param_data = (unsigned char *) kmalloc (param_info->size, GFP_KERNEL);
        if (new_param_data == NULL)
        {
            error ("no mem\n");
            return -ENOMEM;
        }

        type_info->new_param_datas[param_index] = new_param_data;
    }

    if (param_info->unit_size == 1)
    {
        memcpy (new_param_data + offset, ucontrol->value.bytes.data, param_size);
    }
    else
    {
        int *buffer = (int *) (new_param_data + offset);
        int i;

        for (i = 0; i < (param_size / param_info->unit_size); i++)
        {
            buffer[i] = ucontrol->value.integer.value[i];
        }
    }

    /* se func의 param 전달시
     * DAP 경우 max idx -> min idx
     * SE 경우 min idx -> max idx
     * 위와 같이 전달하도록 수정한다.
     */
    if (((strncmp ("LGSE DAP", kcontrol->id.name, 8) == 0) && (param_send_idx % 10 == 0))
        || ((strncmp ("LGSE DAP", kcontrol->id.name, 8) != 0)
            && ((offset + size) == param_info->size)))
    {
        param_data = type_info->param_datas[param_index];

        if (type_info->alsa_se->current_type == type_info)
        {
            struct se_param param = {
                .index = param_index,
                .size = param_info->size,
                .data = new_param_data,
            };
            int ret;

            if ((param_data != NULL)
                && (memcmp (param_data, new_param_data, param_info->size) == 0))
            {
                info ("parameters is same with current it, so skip\n");
                return 0;
            }

            debug ("set param to fw\n");
            ret = se_set_param (type_info->alsa_se->handle, &param);
            if (ret)
            {
                error ("[%s] %s(%d) fail to se_set_param %d\n", kcontrol->id.name,
                        type_info->name, type_info->base_index, ret);
                return -EINVAL;
            }
        }

        if (param_data == NULL)
        {
            param_data = (unsigned char *) kmalloc (param_info->size, GFP_KERNEL);
            if (param_data == NULL)
            {
                error ("no mem\n");
                return -ENOMEM;
            }

            type_info->param_datas[param_index] = param_data;
        }

        debug ("save param\n");
        memcpy (param_data, new_param_data, param_info->size);
    }

    return 0;
}

#ifdef SUPPORT_DAFC
static int _kcontrol_dafc_conf_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_dafc_conf_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    ucontrol->value.integer.value[0] = type_info->dafc_conf_status;

    return 0;
}

/* DAFC dconf, sconf INF*/
/* type : amixer -c 0 cset name='SoundEngine DAFC Flex Configs Status' 6*/
static int _kcontrol_dafc_conf_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    alsa_se_handle_t handle;
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    struct _alsa_se_info *alsa_se;
    int status = ucontrol->value.integer.value[0];
    int ret = 0;

    if (type_info == NULL)
    {
        noti ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if ((status < FLEX_CONFIGS_STATUS_NONE) || (status > FLEX_CONFIGS_STATUS_UPDATE_DONE))
    {
        noti ("invalid value (%ld)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

    handle = alsa_se_get_handle ("COMMON_DAFC");
    if (handle == NULL)
    {
        error ("handle of COMMON_DAFC is NULL\n");
        return -EINVAL;
    }
    else
        alsa_se = handle;

    if (type_info->dafc_conf_status != status)
    {
        type_info->dafc_conf_status = status;
        info ("dafc_conf_status %d\n", type_info->dafc_conf_status);

        if (status == FLEX_CONFIGS_STATUS_UPDATE_REQUESTED)
        {
            ret =
                se_set_dafc_conf (alsa_se->handle, DAFC_FLEX_CONFIGS_DCONF_PATH,
                DAFC_FLEX_CONFIGS_SCONF_PATH);

            if (ret)
            {
                se_set_dafc_by_handle (alsa_se->handle, false);
                noti ("Fail to se_set_dafc_conf : status %d \n", status);
                return -EINVAL;
            }
            else
            {
                se_set_dafc_by_handle (alsa_se->handle, true);
                type_info->dafc_conf_status = FLEX_CONFIGS_STATUS_UPDATE_DONE;
            }
        }
    }

    return 0;
}

static int _kcontrol_dafc_center_extraction_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_dafc_center_extraction_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    ucontrol->value.integer.value[0] = type_info->dafc_center_extract_status;
    info ("dafc_center_extract_status :%d\n", type_info->dafc_center_extract_status);

    return 0;
}

/* Set the status of DAFC calibartion */
/* type : amixer -c 0 cset name='Sndout Center Extraction OnOff' 1*/
static int _kcontrol_dafc_center_extraction_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    alsa_se_handle_t handle;
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    struct _alsa_se_info *alsa_se;
    int status = ucontrol->value.integer.value[0];
    int ret = 0;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if (status != 0 && status != 1)
    {
        error ("status is invalid (%d)\n", status);
        return -EINVAL;
    }

    handle = alsa_se_get_handle ("COMMON_DAFC");
    if (handle == NULL)
    {
        noti ("handle of COMMON_DAFC is NULL\n");
        return -EINVAL;
    }
    else
        alsa_se = handle;

    if (type_info->dafc_center_extract_status != status)
    {
        type_info->dafc_center_extract_status = status;

        ret = se_set_dafc_center_extract_status (alsa_se->handle, status);
        if (ret)
        {
            warn ("Fail to se_set_dafc_center_extract_status (status%d)\n", status);
            return -EINVAL;
        }
    }

    return 0;

}

static int _kcontrol_dafc_output_type_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = SE_INT_MIN;
    uinfo->value.integer.max = SE_INT_MAX;
    return 0;
}

static int _kcontrol_dafc_output_type_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    ucontrol->value.integer.value[0] = type_info->dafc_output_type;
    info ("dafc_output_type :%d\n", type_info->dafc_output_type);

    return 0;
}

/* type : amixer -c 0 cset name='Sndout DAFC Output Type' 1*/
static int _kcontrol_dafc_output_type_put (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    alsa_se_handle_t handle;
    struct _type_info *type_info = (struct _type_info *) kcontrol->private_data;
    struct _alsa_se_info *alsa_se;
    int output_type = ucontrol->value.integer.value[0];

    if (type_info == NULL)
    {
        error ("invalid kcontrol_index(%u)\n", ucontrol->id.index);
        return -EINVAL;
    }

    if ((output_type < SNDOUT_DAFC_OUTPUT_NONE) || (output_type > SNDOUT_DAFC_OUTPUT_MAX))
    {
        error ("invalid value (%d)\n", output_type);
        return -EINVAL;
    }

    handle = alsa_se_get_handle ("COMMON_DAFC");
    if (handle == NULL)
    {
        noti ("handle of COMMON_DAFC is NULL\n");
        return -EINVAL;
    }
    else
        alsa_se = handle;

    if (type_info->dafc_output_type != output_type)
    {
        type_info->dafc_output_type = output_type;
        info ("dafc_output_type :%d\n", type_info->dafc_output_type);
    }

    return 0;

}

#endif /* end of SUPPORT_DAFC */

static const char *_get_lgse_mode_name (lgse_se_mode_ext_type_t lgse_mode)
{
    switch (lgse_mode)
    {
        case LGSE_MODE_LGSE_ONLY:
            return "LGSE_ONLY";

        case LGSE_MODE_LGSE_ATMOS:
            return "LGSE_ATMOS";

        case LGSE_MODE_LGSE_AISOUND:
            return "LGSE_AISOUND";

        default:
            return "UNKNOWN";
    }
}

static int _proc_se_status_show (struct seq_file *m, void *data)
{
    struct _alsa_se_info *alsa_se;

    list_for_each_entry (alsa_se, &_alsa_se_list, list)
    {
        struct _type_info *type_info;

        list_for_each_entry (type_info, &alsa_se->type_list, list)
        {
            unsigned int lgse_mode = 0;

            if ((type_info->lgse_mode_index != -1) &&
                type_info->param_datas && type_info->param_datas[type_info->lgse_mode_index])
            {
                lgse_mode = *((unsigned int *) type_info->param_datas[type_info->lgse_mode_index]);
            }

            seq_printf (m, "[%s]\n", type_info->name);
            seq_printf (m, "seMode=%s\n", _get_lgse_mode_name (type_info->lgse_mode));
            seq_printf (m, "seDownmix=%d\n", _get_downmix_mode (type_info));
            seq_printf (m, "lgseModeFlag=0x%08X\n", lgse_mode);
            seq_printf (m, "connected=%d\n", type_info->alsa_se->current_type == type_info);
        }
    }

    return 0;
}

static int _proc_se_status_open (struct inode *inode, struct file *file)
{
    int ret;

    ret = single_open (file, _proc_se_status_show, NULL);
    if (ret < 0)
        return ret;

    return ret;
}

static alsa_se_handle_t _se_create (const char *name, struct snd_soc_card *card)
{
    struct _alsa_se_info *alsa_se;
    void *buffer;
    int info_size;

    if (!_initialized)
    {
        // create proc node for debug status
        proc_create_data ("lgse", 0440, aproc_seetv, &_proc_se_status_fops, NULL);

        _initialized = true;

        noti ("initialized\n");
    }

    if ((name == NULL) || (card == NULL))
    {
        error ("invalid parameter %p %p\n", name, card);
        return NULL;
    }

    info_size = sizeof (struct _alsa_se_info) + strlen (name) + 1;

    buffer = kzalloc (info_size, GFP_KERNEL);
    if (buffer == NULL)
    {
        error ("no memory\n");
        return NULL;
    }

    alsa_se = (struct _alsa_se_info *) buffer;
    alsa_se->name = buffer + sizeof (struct _alsa_se_info);
    alsa_se->se_index_output = LGSE_NONE;

    alsa_se->handle = (se_handle_t) bm_create_block ("se", -1);
    if (alsa_se->handle == NULL)
    {
        error ("fail to create se block\n");
        kfree (buffer);
        return NULL;
    }

    strncpy (alsa_se->name, name, strlen (name));
    alsa_se->card = card;
    INIT_LIST_HEAD (&alsa_se->type_list);
    alsa_se->current_type = NULL;

    se_set_callback (alsa_se->handle, _se_callback, (void *) alsa_se);

    list_add (&alsa_se->list, &_alsa_se_list);

    noti ("create alsa se module %s\n", alsa_se->name);

    return (alsa_se_handle_t) alsa_se;
}

int alsa_se_destroy (alsa_se_handle_t handle)
{
    struct _alsa_se_info *alsa_se = handle;
    struct _type_info *type, *type_scratch;

    if (alsa_se == NULL)
    {
        error ("invalid parameter\n");
        return -1;
    }

    noti ("destroy alsa se module %s\n", alsa_se->name);

    list_for_each_entry_safe (type, type_scratch, &alsa_se->type_list, list)
    {
        int i;

        list_del (&type->list);

        for (i = 0; i < _se_param_info.number_of_params; i++)
        {
            if (type->param_datas[i])
            {
                kfree (type->param_datas[i]);
            }
            if (type->new_param_datas[i])
            {
                kfree (type->new_param_datas[i]);
            }
        }

        kfree (type->param_datas);
        kfree (type->new_param_datas);
        kfree (type);
    }

    list_del (&alsa_se->list);
    kfree ((void *) alsa_se);

    return 0;
}

static int _se_add_type (alsa_se_handle_t handle, struct alsa_se_type_info *info)
{
    struct _alsa_se_info *alsa_se = handle;
    struct _type_info *type_info;
    int info_size;

    if ((alsa_se == NULL) || (info == NULL) || (info->name == NULL))
    {
        error ("invalid parameter\n");
        return -EINVAL;
    }

    info_size = sizeof (struct _type_info) + strlen (info->name) + 1;
    type_info = (struct _type_info *) kzalloc (info_size, GFP_KERNEL);
    if (type_info == NULL)
    {
        error ("no memory\n");
        return -ENOMEM;
    }

    type_info->name = ((void *) type_info) + sizeof (struct _type_info);

    strncpy (type_info->name, info->name, strlen (info->name));
    type_info->base_index = info->base_index;
    type_info->upmix = info->upmix;
    type_info->alsa_se = alsa_se;
    type_info->lgse_init = LGSE_INIT_LGSE_ONLY;
    type_info->lgse_mode = LGSE_MODE_LGSE_ONLY;
    if (!strncmp (alsa_se->name, "COMMON_DAP_HP_BT", strlen (alsa_se->name)))
        type_info->lgse_mode = LGSE_MODE_LGSE_ATMOS;
#ifdef SUPPORT_DAFC
    if (!strncmp (alsa_se->name, "COMMON_DAFC", strlen (alsa_se->name)))
        type_info->lgse_mode = LGSE_MODE_LGSE_ATMOS;
    type_info->dafc_conf_status = FLEX_CONFIGS_STATUS_NONE;
    type_info->dafc_center_extract_status = 1;  /* default : 1 */
#endif /* end of SUPPORT_DAFC */

    type_info->lgse_mode_index = -1;

    if (_se_param_info.number_of_params > 0)
    {
        unsigned int list_size = sizeof (unsigned char *) * _se_param_info.number_of_params;

        type_info->param_datas = (unsigned char **) kzalloc (list_size, GFP_KERNEL);
        if (type_info->param_datas == NULL)
        {
            kfree (type_info);
            return -ENOMEM;
        }
        type_info->new_param_datas = (unsigned char **) kzalloc (list_size, GFP_KERNEL);
        if (type_info->new_param_datas == NULL)
        {
            kfree (type_info->param_datas);
            kfree (type_info);
            return -ENOMEM;
        }
    }

    list_add (&type_info->list, &alsa_se->type_list);

    noti ("add %s type to %s\n", type_info->name, alsa_se->name);

    return 0;
}

int alsa_se_set_type (alsa_se_handle_t handle, const char *name)
{
    struct _alsa_se_info *alsa_se = handle;
    struct _type_info *type_info = NULL;
    struct _type_info *cur_info;

    if (alsa_se == NULL)
    {
        error ("invalid parameter\n");
        return -EINVAL;
    }

    if (name == NULL)
    {
        alsa_se->current_type = NULL;
        se_set_mode (alsa_se->handle, NULL, NULL);

        return 0;
    }

    list_for_each_entry (cur_info, &alsa_se->type_list, list)
    {
        if (!strncmp (cur_info->name, name, strlen (cur_info->name)))
        {
            type_info = cur_info;
            break;
        }
    }

    if (type_info == NULL)
    {
        error ("Unknown type %s\n", name);
        return -EINVAL;
    }

    info ("type_info->name = %s\n", type_info->name);
    if (alsa_se->current_type != type_info)
    {
        if (_change_mode (type_info, FALSE) != 0)
        {
            return -EINVAL;
        }

        alsa_se->current_type = type_info;

        info ("set %s type to %s\n", type_info->name, alsa_se->name);
    }

    return 0;
}

int alsa_se_set_number_of_output_channels (alsa_se_handle_t handle, unsigned int number)
{
    struct _alsa_se_info *alsa_se = handle;

    if (alsa_se == NULL)
    {
        error ("invalid parameter\n");
        return -EINVAL;
    }

    if (se_set_number_of_output_channels (alsa_se->handle, number) != 0)
    {
        return -EINVAL;
    }

    info ("set %s number of output %d\n", alsa_se->name, number);

    return 0;
}

#ifdef SUPPORT_SOUNDBAR
int alsa_se_set_output_freq (alsa_se_handle_t handle, unsigned int freq)
{
    struct _alsa_se_info *alsa_se = handle;

    if (alsa_se == NULL)
    {
        noti ("invalid parameter\n");
        return -EINVAL;
    }

    if (se_set_output_freq (alsa_se->handle, freq) != 0)
    {
        return -EINVAL;
    }

    info ("%s: set output freq %u\n", alsa_se->name, freq);

    return 0;
}
#endif

alsa_se_handle_t alsa_se_get_handle (const char *name)
{
    struct _alsa_se_info *alsa_se = NULL;
    struct _alsa_se_info *cur_se;

    if (name == NULL)
    {
        warn ("invalid parameter\n");
        return NULL;
    }

    list_for_each_entry (cur_se, &_alsa_se_list, list)
    {
        if (!strncmp (cur_se->name, name, strlen (cur_se->name)))
        {
            alsa_se = cur_se;
            break;
        }
    }

    if (alsa_se == NULL)
    {
        error ("Unknown name %s\n", name);
        return NULL;
    }

    return alsa_se;
}

struct aud_block_info *alsa_se_get_block (alsa_se_handle_t handle)
{
    struct _alsa_se_info *alsa_se = handle;

    if (alsa_se == NULL)
    {
        error ("invalid parameter\n");
        return NULL;
    }

    return (struct aud_block_info *) alsa_se->handle;
}

enum alse_se_mode alsa_se_get_mode (alsa_se_handle_t handle)
{
    struct _alsa_se_info *alsa_se = handle;
    enum alse_se_mode mode = ALSA_SE_MODE_INVALID;

    if (alsa_se == NULL)
    {
        error ("invalid parameter\n");
        return ALSA_SE_MODE_INVALID;
    }

    if (alsa_se->current_type == NULL)
    {
        error ("invalid parameter\n");
        return ALSA_SE_MODE_INVALID;
    }

    switch (alsa_se->current_type->lgse_mode)
    {
        case LGSE_MODE_LGSE_ONLY:
            mode = ALSA_SE_MODE_LGSE_ONLY;
            break;

        case LGSE_MODE_LGSE_ATMOS:
            mode = ALSA_SE_MODE_LGSE_ATMOS;
            break;

        case LGSE_MODE_LGSE_AISOUND:
        {
            int i;

            for (i = 0; i < _se_param_info.number_of_params; i++)
            {
                if (!strcmp (_se_param_info.param_list[i].name, LGSE_MODE) &&
                    (alsa_se->current_type->param_datas[i] != NULL))
                {
                    int *modes = (int *) alsa_se->current_type->param_datas[i];

                    if ((modes[0] & 0x60000000) == 0x60000000)
                    {
                        mode = ALSA_SE_MODE_LGSE_AISOUND_GEN1_GEN2;
                    }
                    else if ((modes[0] & 0x60000000) == 0x40000000)
                    {
                        mode = ALSA_SE_MODE_LGSE_AISOUND_GEN2;
                    }
                    else if ((modes[0] & 0x60000000) == 0x20000000)
                    {
                        mode = ALSA_SE_MODE_LGSE_AISOUND_GEN1;
                    }
                    else
                    {
                        mode = ALSA_SE_MODE_LGSE_AISOUND_BYPASS;
                    }

                    break;
                }
            }
            break;
        }

        default:
            break;
    }

    return mode;
}

int alsa_se_connect_pipeline (alsa_se_handle_t handle)
{
    struct _alsa_se_info *alsa_se = handle;
    struct _type_info *type_info = NULL;
    struct aud_block_info *block_info;

    if (alsa_se == NULL)
    {
        error ("invalid handle\n");
        return -EINVAL;
    }

    type_info = alsa_se->current_type;
    if (type_info == NULL)
    {
        lgse_index_ouptut_t se_index;

        noti ("no set type_info by no set pipeline\n");

        se_index = alsa_se->se_index_output;

        if (se_index != LGSE_NONE)
        {
            block_info = alsa_se_get_block (handle);

            // Only set type, if SE module is existed
            if (block_info != NULL)
            {
                info ("set type (%s)\n", _se_output_name (se_index));
                alsa_se_set_type (handle, _se_output_name (se_index));
                type_info = alsa_se->current_type;
                if (type_info == NULL)
                {
                    noti ("type info is NULL\n");
                    return -EINVAL;
                }
            }
            else
            {
                noti ("block info is null\n");
                return -EINVAL;
            }
        }
        else
        {
            noti ("se index output is LGSE_NONE\n");
            return -EINVAL;
        }
    }
    else if (_change_mode (type_info, FALSE) != 0)
    {
        return -EINVAL;
    }

    info ("Create pipeline between SE to OUTPUT\n");
    return 0;
}

static struct
{
    const char *name;
    unsigned int number_of_output_channels;
#ifdef SUPPORT_SOUNDBAR
    unsigned int output_freq;
#endif
    struct alsa_se_type_info type_infos[4];
} _se_info[] =
{
    /* *INDENT-OFF* */
#ifdef SUPPORT_SOUNDBAR
#if defined (CHIP_NAME_o24)
    { "COMMON_SPK",       8,  48000, { { "LGSE_SPK",  LGSE_SPK,   true  }, { "LGSE_NONE",  LGSE_NONE,  false } } },
    { "COMMON_DAFC",      10, 48000, { { "LGSE_DAFC", LGSE_DAFC,  false } } },
#else   // o26
    { "COMMON_SPK",       12, 48000, { { "LGSE_SPK",  LGSE_SPK,   true  }, { "LGSE_NONE",  LGSE_NONE,  false } } },
    { "COMMON_DAFC",      21, 48000, { { "LGSE_DAFC", LGSE_DAFC,  false } } },
#endif
#else
    { "COMMON_SPK",        4, { { "LGSE_SPK", LGSE_SPK, true  }, { "LGSE_SPK_BTSUR", LGSE_SPK_BTSUR, true  } , { "LGSE_SPK_ARC", LGSE_SPK_ARC, true } , { "LGSE_NONE",  LGSE_NONE,  false } } },
    { "COMMON_SE_BT",      2, { { "LGSE_BT",  LGSE_BT,  false }, { "LGSE_BT_BTSUR", LGSE_BT_BTSUR,   false } } },
    { "COMMON_SE_ARC",     2, { { "LGSE_ARC", LGSE_ARC, true  }, { NULL, 0, false } } },
    { "COMMON_DAP_HP_BT",  2, { { "LGSE_DAP_HP_BT",  LGSE_DAP_HP_BT,  false } } },
    { "COMMON_DAFC",      10, { { "LGSE_DAFC",  LGSE_DAFC,  false } } },
#endif
    /* *INDENT-ON* */
};

int register_se_kcontrols (struct snd_soc_card *card)
{
    int ret = 0;
    int i = 0;

    // create alsa se module
    for (i = 0; i < ARRAY_SIZE (_se_info); i++)
    {
        alsa_se_handle_t alsa_se = _se_create (_se_info[i].name, card);
        int j;

        if (alsa_se == NULL)
        {
            warn ("fail to create se %s\n", _se_info[i].name);
            continue;
        }

        for (j = 0; j < ARRAY_SIZE (_se_info[i].type_infos); j++)
        {
            if (_se_info[i].type_infos[j].name == NULL)
            {
                continue;
            }

            _se_add_type (alsa_se, &_se_info[i].type_infos[j]);
        }

        alsa_se_set_number_of_output_channels (alsa_se, _se_info[i].number_of_output_channels);
#ifdef SUPPORT_SOUNDBAR
        alsa_se_set_output_freq (alsa_se, _se_info[i].output_freq);
#endif
    }

    // register kcontrols
    if (_register_func_list () < 0)
        error ("register function list is failed\n");

#if !defined (CHIP_NAME_m23)
    ret = _register_lgse_ll_kcontrols (card);
    if (ret != RET_OK)
    {
        error ("register_lgse_ll_kcontrols is failed (ret %d) \n", ret);
        return ret;
    }
#endif

    noti ("completed \n");
    return ret;
}
