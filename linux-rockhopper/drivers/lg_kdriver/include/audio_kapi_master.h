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


/** @file audio_kadp_master.h
 *
 *  This is a wrapper function file for adec_ddi.c to process ADEC function.
 *  The simple wrapper function for audio kernel module.
 *
 *  @author Won Chang Shin(wonchang.shin@lge.com)
 *  @version   0.1
 *  @date       2012.04.18
 *  @note       The simple wrapper function for audio kernel module.
 *
 *  @addtogroup lg1150_audio
 *  @{
 */

#ifndef _AUDIO_KAPI_MASTER_H_
#define _AUDIO_KAPI_MASTER_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include "audio_kapi.h"
#include "linux/alsa-ext/alsa-ext-sndout.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define AUD_MASTER_IOC_MAGIC        'M'

/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/* IO Command Name */
#define AUD_MASTER_IOW_SET_VOLUME                       _IOW(AUD_MASTER_IOC_MAGIC,  0, LX_AUD_MASTER_CONFIG_VOLUME_T)
#define AUD_MASTER_IOW_SET_MUTE                         _IOW(AUD_MASTER_IOC_MAGIC,  1, LX_AUD_MASTER_CONFIG_MUTE_T)
#define AUD_MASTER_IOW_SET_DELAY                        _IOW(AUD_MASTER_IOC_MAGIC,  2, LX_AUD_MASTER_CONFIG_DELAY_T)
#define AUD_MASTER_IOW_SET_SPDIF_OUTPUT                 _IOW(AUD_MASTER_IOC_MAGIC,  3, LX_AUD_MASTER_SPDIF_OUTPUT_T)        /* deprecated */
#define AUD_MASTER_IOW_SET_IEC_OUTPUT                   _IOW(AUD_MASTER_IOC_MAGIC,  4, LX_AUD_MASTER_CONFIG_IEC_OUTPUT_T)
#define AUD_MASTER_IOW_SET_SPDIF_SCMS                   _IOW(AUD_MASTER_IOC_MAGIC,  5, LX_AUD_MASTER_SPDIF_SCMS_T)
#define AUD_MASTER_IOW_SET_SPDIF_CATEGORY_CODE          _IOW(AUD_MASTER_IOC_MAGIC,  6, UINT32)
#define AUD_MASTER_IOW_SET_BALANCE                      _IOW(AUD_MASTER_IOC_MAGIC,  7, LX_AUD_MASTER_CONFIG_BALANCE_T)      /* deprecated */
#define AUD_MASTER_IOW_SET_BASS                         _IOW(AUD_MASTER_IOC_MAGIC,  8, LX_AUD_MASTER_CONFIG_BASS_T)         /* deprecated */
#define AUD_MASTER_IOW_SET_TREBLE                       _IOW(AUD_MASTER_IOC_MAGIC,  9, LX_AUD_MASTER_CONFIG_TREBLE_T)       /* deprecated */
#define AUD_MASTER_IOW_SET_ADC_INPUT_PORT               _IOW(AUD_MASTER_IOC_MAGIC, 10, UINT32)

#define AUD_MASTER_IO_SET_DRC_DOWNMIX_MODE              _IO(AUD_MASTER_IOC_MAGIC, 11)
#define AUD_MASTER_IOW_SET_ARC_SCMS                     _IOW(AUD_MASTER_IOC_MAGIC, 12, LX_AUD_MASTER_ARC_SCMS_T)
#define AUD_MASTER_IOW_SET_ARC_CATEGORY_CODE            _IOW(AUD_MASTER_IOC_MAGIC, 13, UINT32)
#define AUD_MASTER_IOW_SET_DOLBY_OTT_MODE               _IOW(AUD_MASTER_IOC_MAGIC, 14, LX_AUD_MASTER_DOLBY_OTT_MODE_T)
#define AUD_MASTER_IOW_DISABLE_ATMOS_NOTI               _IOW(AUD_MASTER_IOC_MAGIC, 15, UINT32)
#define AUD_MASTER_IOW_SET_DRC_CUT_BOOST_MODE           _IOW(AUD_MASTER_IOC_MAGIC, 16, LX_AUD_MASTER_DRC_CUT_BOOST_MODE_T)

#define AUD_MASTER_IOW_SET_SPK_OUTPUT                   _IOW(AUD_MASTER_IOC_MAGIC, 20, LX_AUD_MASTER_SPK_OUTPUT_T)
#define AUD_MASTER_IOW_SET_MIXER_VOLUME                 _IOW(AUD_MASTER_IOC_MAGIC, 21, LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T)
#define AUD_MASTER_IOW_SET_OUT_MODE                     _IOW(AUD_MASTER_IOC_MAGIC, 22, LX_AUD_MASTER_CONFIG_OUT_MODE_T)
#define AUD_MASTER_IOW_SET_DAC_VOLUME                   _IOW(AUD_MASTER_IOC_MAGIC, 23, LX_AUD_MASTER_CONFIG_DAC_VOLUME_T)   /* deprecated */
#define AUD_MASTER_IOW_SET_DAC_MUTE                     _IOW(AUD_MASTER_IOC_MAGIC, 24, LX_AUD_MASTER_CONFIG_DAC_MUTE_T)
#define AUD_MASTER_IOR_GET_KDRV_HANDLE                  _IOR(AUD_MASTER_IOC_MAGIC, 27, UINT32)
#define AUD_MASTER_IOW_SET_MS12_VERSION                 _IOW(AUD_MASTER_IOC_MAGIC, 28, LX_AUD_MS12_VERSION_T)
#define AUD_MASTER_IOW_SET_MIXER_MUTE                   _IOW(AUD_MASTER_IOC_MAGIC, 29, LX_AUD_MASTER_CONFIG_MIXER_MUTE_T)

#define AUD_MASTER_IOW_SET_LGSE_MODE                    _IOW(AUD_MASTER_IOC_MAGIC, 31, LX_AUD_MASTER_LGSE_MODE_T)
#define AUD_MASTER_IOW_CONNECT_OUTPUT                   _IOW(AUD_MASTER_IOC_MAGIC, 32, LX_AUD_MASTER_CONNECT_OUTPUT_INDEX_T)
#define AUD_MASTER_IOW_DISCONNECT_OUTPUT                _IOW(AUD_MASTER_IOC_MAGIC, 33, LX_AUD_MASTER_DISCONNECT_OUTPUT_INDEX_T)
#define AUD_MASTER_IOR_GET_SPDIF_OUTPUT                 _IOR(AUD_MASTER_IOC_MAGIC, 34, LX_AUD_MASTER_SPDIF_OUTPUT_T)        /* deprecated */
#define AUD_MASTER_IOWR_GET_IEC_OUTPUT                  _IOWR(AUD_MASTER_IOC_MAGIC,35, LX_AUD_MASTER_CONFIG_IEC_OUTPUT_T)
#define AUD_MASTER_IOR_GET_IEC_OUTPUT                   _IOR(AUD_MASTER_IOC_MAGIC, 36, LX_AUD_MASTER_CONFIG_IEC_OUTPUT_T)   /* deprecated */
#define AUD_MASTER_IOW_SET_OUTPUT_CONNECT_CONFIG        _IOW(AUD_MASTER_IOC_MAGIC, 37, LX_AUD_MASTER_OUTPUT_CONNECT_CONFIG_T)
#define AUD_MASTER_IOWR_GET_OUTPUT_CONNECT_CONFIG       _IOWR(AUD_MASTER_IOC_MAGIC,38, LX_AUD_MASTER_OUTPUT_CONNECT_CONFIG_T)
#define AUD_MASTER_IOR_GET_EARC_OUTPUT_INFO             _IOR(AUD_MASTER_IOC_MAGIC, 39, LX_AUD_MASTER_EARC_OUTPUT_INFO_T)

#define AUD_MASTER_IOW_ENABLE_SOUNDBAR                  _IOW(AUD_MASTER_IOC_MAGIC, 40, LX_AUD_MASTER_SOUNDBAR_T)
#define AUD_MASTER_IOW_SET_SOUNDBAR_PARAM               _IOW(AUD_MASTER_IOC_MAGIC, 41, LX_AUD_MASTER_SOUNDBAR_PARAM_T)
#define AUD_MASTER_IOR_GET_SOUNDBAR_STATUS              _IOR(AUD_MASTER_IOC_MAGIC, 42, LX_AUD_MASTER_SOUNDBAR_STATUS_T)

#define AUD_MASTER_IOW_SET_SPDIF_ONOFF                  _IOW(AUD_MASTER_IOC_MAGIC, 43, UINT32)
#define AUD_MASTER_IOW_SET_SOUNDBAR_POWER               _IOW(AUD_MASTER_IOC_MAGIC, 44, UINT32)

#define AUD_MASTER_IOW_SET_I2S_NUM                      _IOW(AUD_MASTER_IOC_MAGIC, 45, UINT32)                              /* deprecated */

#define AUD_MASTER_IOW_SET_ARC_ONOFF                    _IOW(AUD_MASTER_IOC_MAGIC, 46, UINT32)
#define AUD_MASTER_IOR_GET_CONFIG                       _IOR(AUD_MASTER_IOC_MAGIC, 47, LX_AUD_MASTER_GET_CONFIG_T)
#define AUD_MASTER_IOR_GET_ARC_OUTPUT_INFO              _IOR(AUD_MASTER_IOC_MAGIC, 48, LX_AUD_MASTER_ARC_OUTPUT_INFO_T)
#define AUD_MASTER_IOW_SET_EARC_ONOFF                   _IOW(AUD_MASTER_IOC_MAGIC, 49, UINT32)

/* Get GSTC */
#define AUD_MASTER_IOR_GET_GSTC                         _IOR(AUD_MASTER_IOC_MAGIC, 50, UINT64)

/* Audio Processing SE/DAP */
#define AUD_MASTER_IOW_SET_SE_FN                        _IOW(AUD_MASTER_IOC_MAGIC, 60, LX_AUD_MASTER_PARAM_SE_FN_T)
#define AUD_MASTER_IOWR_GET_SE_FN                       _IOWR(AUD_MASTER_IOC_MAGIC,61, LX_AUD_MASTER_PARAM_SE_FN_T)
#define AUD_MASTER_IOWR_GET_SE_PARAM                    _IOWR(AUD_MASTER_IOC_MAGIC,62, LX_AUD_MASTER_PARAM_SE_FN_T)
#define AUD_MASTER_IOW_SET_DAP_FN                       _IOW(AUD_MASTER_IOC_MAGIC, 63, LX_AUD_MASTER_PARAM_DAP_FN_T)
#define AUD_MASTER_IOWR_GET_DAP_FN                      _IOWR(AUD_MASTER_IOC_MAGIC,64, LX_AUD_MASTER_PARAM_DAP_FN_T)
#define AUD_MASTER_IOW_SET_DAP_VIRTUALIZER_MODE         _IOW(AUD_MASTER_IOC_MAGIC, 65, LX_AUD_MASTER_PARAM_DAP_VIRTUALIZER_MODE_T)
#define AUD_MASTER_IOW_SET_AUDIO_PROCESSING_STATUS      _IOW(AUD_MASTER_IOC_MAGIC, 66, LX_AUD_MASTER_AUDIO_PROCESSING_STATUS_T)
#define AUD_MASTER_IOR_GET_AUDIO_PROCESSING_STATUS      _IOR(AUD_MASTER_IOC_MAGIC, 67, LX_AUD_MASTER_AUDIO_PROCESSING_STATUS_T)
#define AUD_MASTER_IOR_GET_DAP_VIRTUALIZER_MODE         _IOR(AUD_MASTER_IOC_MAGIC, 68, LX_AUD_MASTER_PARAM_DAP_VIRTUALIZER_MODE_T)
#define AUD_MASTER_IOW_SET_DE_GAIN                      _IOW(AUD_MASTER_IOC_MAGIC, 68, LX_AUD_SET_DE_GAIN_T)
#define AUD_MASTER_IOW_SET_VX_FN                        _IOW(AUD_MASTER_IOC_MAGIC, 69, LX_AUD_VX_FN_PARAM_T)                /* deprecated */
#define AUD_MASTER_IOR_GET_VX_FN                        _IOR(AUD_MASTER_IOC_MAGIC, 70, LX_AUD_VX_FN_PARAM_T)                /* deprecated */
#define AUD_MASTER_IOW_SET_VX_CERT_PARAM                _IOW(AUD_MASTER_IOC_MAGIC, 71, BOOLEAN)                             /* deprecated */
#define AUD_MASTER_IOW_SET_SE_DOWNMIX                   _IOW(AUD_MASTER_IOC_MAGIC, 72, BOOLEAN)
#define AUD_MASTER_IOW_SET_SE_PARAM_INDEX               _IOW(AUD_MASTER_IOC_MAGIC, 73, LX_AUD_MASTER_SE_PARAM_T)

/* Event */
#define AUD_MASTER_IOW_SET_EVENT                        _IOW(AUD_MASTER_IOC_MAGIC, 75, LX_AUD_EVENT_TYPE_T)
#define AUD_MASTER_IORW_GET_EVENT                       _IOWR(AUD_MASTER_IOC_MAGIC,76, LX_AUD_EVENT_TYPE_T)

/* Sound Bar & SPDIF */
#define AUD_MASTER_IOW_SET_SOUNDBAR_CMD                 _IOW(AUD_MASTER_IOC_MAGIC, 80, LX_AUD_MASTER_SOUNDBAR_CMD_T)
#define AUD_MASTER_IOW_SET_MAIN_DECODER                 _IOW(AUD_MASTER_IOC_MAGIC, 81, UINT32)                              /* deprecated */
#define AUD_MASTER_IOR_GET_MAIN_DECODER                 _IOR(AUD_MASTER_IOC_MAGIC, 82, UINT32)                              /* deprecated */
#define AUD_MASTER_IOW_SET_SPDIF_CONFIG                 _IOW(AUD_MASTER_IOC_MAGIC, 83, LX_AUD_MASTER_CONFIG_SPDIF_T)        /* deprecated */
#define AUD_MASTER_IOW_SET_IEC_OUT_ENCODED_TYPE         _IOW(AUD_MASTER_IOC_MAGIC, 84, LX_AUD_MASTER_CONFIG_IEC_OUT_ENCODED_T)
#define AUD_MASTER_IOW_SET_MAIN_OUTPUT                  _IOW(AUD_MASTER_IOC_MAGIC, 85, UINT32)
#define AUD_MASTER_IOR_GET_MAIN_OUTPUT                  _IOR(AUD_MASTER_IOC_MAGIC, 86, UINT32)

/* AAD */
#define AUD_MASTER_IO_RESET_AAD_MODULE                  _IO( AUD_MASTER_IOC_MAGIC, 90)
#define AUD_MASTER_IO_SET_AAD_SIF_INPUT                 _IOW(AUD_MASTER_IOC_MAGIC, 91, LX_AUD_SIF_INPUT_T)

/* Get Delay */
#define AUD_MASTER_IOR_GET_DELAY                        _IOWR(AUD_MASTER_IOC_MAGIC, 100, UINT32)                            /* deprecated */
#define AUD_IOWR_GET_INDEX_DELAY                        _IOWR(AUD_MASTER_IOC_MAGIC, 101, LX_AUD_GET_INDEX_DELAY_T)          /* deprecated */

/* Set Volume/Delay for index */
#define AUD_IOW_SET_INPUT_VOLUME                        _IOW(AUD_MASTER_IOC_MAGIC,  111, LX_AUD_SET_INPUT_VOLUME_T)
#define AUD_IOW_SET_INPUT_MUTE                          _IOW(AUD_MASTER_IOC_MAGIC,  112, LX_AUD_SET_INPUT_MUTE_T)
#define AUD_IOW_SET_INPUT_DELAY                         _IOW(AUD_MASTER_IOC_MAGIC,  113, LX_AUD_INPUT_DELAY_T)
#define AUD_IOR_GET_START_INFO                          _IOR(AUD_MASTER_IOC_MAGIC,  114, LX_AUD_GET_START_INFO_T)           /* deprecated */
#define AUD_IOWR_GET_INPUT_DELAY                        _IOWR(AUD_MASTER_IOC_MAGIC, 115, LX_AUD_INPUT_DELAY_T)

/* Output Delay */
#define AUD_MASTER_IOWR_GET_OUTPUT_DELAY                _IOWR(AUD_MASTER_IOC_MAGIC, 130, LX_AUD_MASTER_CONNECT_INDEX_OUTPUT_T)
#define AUD_MASTER_IOW_SET_OUTPUT_DELAY                 _IOW(AUD_MASTER_IOC_MAGIC,  131, LX_AUD_MASTER_CONNECT_INDEX_OUTPUT_T)

/* Power Control */
#define AUD_MASTER_IOW_SET_POWER_CTRL                   _IOW(AUD_MASTER_IOC_MAGIC,  140, LX_AUD_MASTER_CONFIG_POWER_CTRL_T) /* deprecated */

#define AUD_MASTER_IOW_SET_MS12_CERTI                   _IOW(AUD_MASTER_IOC_MAGIC,  150, BOOLEAN)

/* Get Video Output and Panel Type. */
#define AUD_IOR_GET_VIDEO_OUTPUT_INFO                   _IOR(AUD_MASTER_IOC_MAGIC,  170, LX_AUD_VIDEO_OUTPUT_STATUS_T)      /* deprecated */

#define AUD_IOR_GET_INPUT_INT_COUNT                     _IOR(AUD_MASTER_IOC_MAGIC,  171, LX_AUD_INPUT_INT_COUNT_T)

/* Download DSP Image for test */
#define AUD_MASTER_DOWNALOD_DSP0                        _IOW(AUD_MASTER_IOC_MAGIC,  180, LX_AUD_CODEC_T)                    /* deprecated */
#define AUD_MASTER_DOWNALOD_DSP1                        _IOW(AUD_MASTER_IOC_MAGIC,  181, LX_AUD_CODEC_T)                    /* deprecated */
#define AUD_MASTER_DOWNLOAD_DSP                         _IOW(AUD_MASTER_IOC_MAGIC,  182, LX_AUD_DOWNLOAD_DSP_T)
#define AUD_MASTER_DOWNLOAD_DSP0                        _IOW(AUD_MASTER_IOC_MAGIC,  183, LX_AUD_CODEC_T)
#define AUD_MASTER_DOWNLOAD_DSP1                        _IOW(AUD_MASTER_IOC_MAGIC,  184, LX_AUD_CODEC_T)
#define AUD_MASTER_WAIT_FIRMWARE_LOAD                   _IO (AUD_MASTER_IOC_MAGIC,  185)                                    /* deprecated */

/* Debug control */
#define AUD_IOW_DEBUG_ALSA_MEM_DUMP_START               _IOW(AUD_MASTER_IOC_MAGIC, 188, LX_AUD_MASTER_ALSA_DUMP_PARAMS_T)
#define AUD_IO_DEBUG_ALSA_MEM_DUMP_STOP                 _IO(AUD_MASTER_IOC_MAGIC, 189)

#define AUD_IOWR_READ_AND_WRITE_REG                     _IOWR(AUD_MASTER_IOC_MAGIC, 190, LX_AUD_REG_INFO_T)
#define AUD_IOW_CUSTOM_IMC                              _IOWR(AUD_MASTER_IOC_MAGIC, 191, LX_AUD_CUSTOM_IMC_T)
#define AUD_IO_DEBUG_DEV_INFO                           _IO(AUD_MASTER_IOC_MAGIC,   192)
#define AUD_IOW_DEBUG_PRINT_CTRL                        _IOW(AUD_MASTER_IOC_MAGIC,  193, LX_AUD_DEBUG_CTRL_T)
#define AUD_IOW_DEBUG_MEM_DUMP                          _IOW(AUD_MASTER_IOC_MAGIC,  194, LX_AUD_DEBUG_MEM_DUMP_T)
#define AUD_IO_DEBUG_ALLOC_INFO                         _IO(AUD_MASTER_IOC_MAGIC,   195)
#define AUD_IOWR_DEBUG_GET_MOD_INFO                     _IOWR(AUD_MASTER_IOC_MAGIC, 196, LX_AUD_DEBUG_MOD_INFO_T)
#define AUD_IOR_GET_FW_DEBUG_PRINT_INFO                 _IOR(AUD_MASTER_IOC_MAGIC,  197, LX_AUD_FW_DEBUG_INFO_T)
#define AUD_IOW_SET_FW_DEBUG_MASK                       _IOW(AUD_MASTER_IOC_MAGIC,  198, UINT32)
#define AUD_IOWR_GET_DECODED_INFO                       _IOWR(AUD_MASTER_IOC_MAGIC, 199, LX_AUD_GET_DECODED_INFO_T)
#define AUD_IOW_DEBUG_FEED_DUMP_START                   _IOW(AUD_MASTER_IOC_MAGIC, 200, LX_AUD_FEED_DUMP_PARAMS_T)
#define AUD_IO_DEBUG_FEED_DUMP_STOP                     _IO(AUD_MASTER_IOC_MAGIC, 201)
#define AUD_IO_RESTART                                  _IO(AUD_MASTER_IOC_MAGIC, 202)

#define AUD_DEBUG_IOW_SET_UI_PARAM                      _IOW(AUD_MASTER_IOC_MAGIC, 203, LX_AUD_DEBUG_UI_PARAM_T)
#define AUD_DEBUG_IOR_GET_UI_PARAM                      _IOR(AUD_MASTER_IOC_MAGIC, 204, LX_AUD_DEBUG_UI_PARAM_T)

#define AUD_MASTER_IOC_MAXNR                            205

#define NUM_OF_START_INFO                               14  // DEC ( 2)+ REN(12)

#define NO_EASE_DURATION                                0
#define NO_EASE_TYPE                                    4

/* Output Adjust Delay */
#define OUTPUT_DELAY_ADJUST_NONE                        0       // 0 msec
#if 0
#define OUTPUT_DELAY_ADJUST_ENCODER                     64      // 64 msec
#else
#define OUTPUT_DELAY_ADJUST_ENCODER                     0
#endif

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * AUDIO MASTER Output Port.
 */
typedef enum {
    LX_AUD_MASTER_OUTPUT_SPEAKER,                       ///< Speaker output
    LX_AUD_MASTER_OUTPUT_HP,                            ///< Headphone output
    LX_AUD_MASTER_OUTPUT_SPDIF,                         ///< SPDIF output
    LX_AUD_MASTER_OUTPUT_ARC,                           ///< ARC output
    LX_AUD_MASTER_OUTPUT_MAX                            ///< the max marker of this enumeration
} LX_AUD_MASTER_OUTPUT_T;

/**
 * AUDIO MASTER Output Mode.
 */
typedef enum {
    LX_AUD_MASTER_OUT_LR,                               ///< Left Right Output
    LX_AUD_MASTER_OUT_LL,                               ///< Left Left output
    LX_AUD_MASTER_OUT_RR,                               ///< Right Right output
    LX_AUD_MASTER_OUT_MIX,                              ///< Left Right Mixe output
    LX_AUD_MASTER_OUT_MODE_MAX,                         ///< the max marker of this enumeration
} LX_AUD_MASTER_OUT_MODE_T;

/**
 * AUDIO MASTER SPDIF Output Type.
 */
typedef enum {
    LX_AUD_MASTER_SPDIF_PCM             =   0,          ///< SPDIF PCM Output
    LX_AUD_MASTER_SPDIF_ES              =   1,          ///< SPDIF ES Output
    LX_AUD_MASTER_SPDIF_DDP             =   2,          ///< SPDIF DDP Output
    LX_AUD_MASTER_SPDIF_MIXED_DD        =   3,          ///< SPDIF Mixed DD Output
    LX_AUD_MASTER_SPDIF_MIXED_DDP       =   4,          ///< SPDIF Mixed DDP Output
#ifdef SUPPORT_DTSX
    LX_AUD_MASTER_SPDIF_MIXED_DTS       =   5,          ///< SPDIF Mixed DTS Output
#endif
    LX_AUD_MASTER_SPDIF_FIXED_DD        =   6,          ///< SPDIF Fixed DD Output
    LX_AUD_MASTER_SPDIF_FIXED_DDP       =   7,          ///< SPDIF Fixed DDP Output
    LX_AUD_MASTER_SPDIF_MAX,                            ///< the max marker of this enumeration
} LX_AUD_MASTER_SPDIF_OUTPUT_T;

/**
 * AUDIO MASTER IEC Output Type.
 */
typedef enum {
    LX_AUD_MASTER_IEC_OUT_PCM,          ///< IEC PCM Output
    LX_AUD_MASTER_IEC_OUT_ES,           ///< IEC ES Output
    LX_AUD_MASTER_IEC_OUT_DDP,          ///< IEC DDP Output
    LX_AUD_MASTER_IEC_OUT_BYPASS,       ///< IEC BYPASS Output
    LX_AUD_MASTER_IEC_OUT_BYPASS_DDP,   ///< IEC BYPASS Output
    LX_AUD_MASTER_IEC_OUT_MIXED_DD,     ///< IEC Mixed DD Output
    LX_AUD_MASTER_IEC_OUT_MIXED_DDP,    ///< IEC Mixed DDP Output
#ifdef SUPPORT_DTSX
    LX_AUD_MASTER_IEC_OUT_MIXED_DTS,    ///< IEC Mixed DTS Output
#endif
    LX_AUD_MASTER_IEC_OUT_FIXED_DD,     ///< IEC Fixed DD Output
    LX_AUD_MASTER_IEC_OUT_FIXED_DDP,    ///< IEC Fixed DDP Output
    LX_AUD_MASTER_IEC_OUT_MAT,          ///< IEC MAT Output
    LX_AUD_MASTER_IEC_OUT_BYPASS_MPEG4_AAC,   ///< IEC BYPASS Output(MPEG4 AAC)
    LX_AUD_MASTER_IEC_OUT_MAX,          ///< the max marker of this enumeration
} LX_AUD_MASTER_IEC_OUT_T;

/**
  * AUDIO MASTER IEC Output Type.
  * NOTE: modify master_encoded_output_name accordingly.
  */
typedef enum {
    LX_AUD_MASTER_IEC_OUT_ENCODED_NONE,     ///< IEC PCM Output
    LX_AUD_MASTER_IEC_OUT_ENCODED_DD,       ///< IEC DD converted Output
    LX_AUD_MASTER_IEC_OUT_ENCODED_DDP,      ///< IEC DDP encoded Output
#ifdef SUPPORT_DTSX
    LX_AUD_MASTER_IEC_OUT_ENCODED_DTS,      ///< IEC DTS encoded Output
#endif
    LX_AUD_MASTER_IEC_OUT_ENCODED_AAC,      ///< IEC AAC encoded Output
    LX_AUD_MASTER_IEC_OUT_ENCODED_BYPASS,   ///< IEC Bypass Output
    LX_AUD_MASTER_IEC_OUT_ENCODED_MAT,      ///< IEC MAT encoded Output
    LX_AUD_MASTER_IEC_OUT_ENCODED_MAX,      ///< the max marker of this enumeration
} LX_AUD_MASTER_IEC_OUT_ENCODED_T;

/**
 * AUDIO MASTER SPDIF SCMS(Serial Copy Management System) state.
 */
typedef enum {
    LX_AUD_MASTER_SPDIF_COPY_FREE       =   0,          ///< Copy Free state
    LX_AUD_MASTER_SPDIF_COPY_NO_MORE    =   1,          ///< Copy no more state
    LX_AUD_MASTER_SPDIF_COPY_ONCE       =   2,          ///< Copy once state
    LX_AUD_MASTER_SPDIF_COPY_NEVER      =   3,          ///< Copy never state
} LX_AUD_MASTER_SPDIF_SCMS_T;

/**
 * AUDIO MASTER ARC SCMS(Serial Copy Management System) state.
 */
typedef enum {
    LX_AUD_MASTER_ARC_COPY_FREE         =   0,          ///< Copy Free state
    LX_AUD_MASTER_ARC_COPY_NO_MORE      =   1,          ///< Copy no more state
    LX_AUD_MASTER_ARC_COPY_ONCE         =   2,          ///< Copy once state
    LX_AUD_MASTER_ARC_COPY_NEVER        =   3,          ///< Copy never state
} LX_AUD_MASTER_ARC_SCMS_T;

/**
 * AUDIO MASTER SE ID.
 */
typedef enum LX_AUD_MASTER_SE_ID {
    LX_AUD_MASTER_SE_ID_0,                               ///< ADEC_MODULE_SE_0
    LX_AUD_MASTER_SE_ID_1,                               ///< ADEC_MODULE_SE_1
    LX_AUD_MASTER_SE_ID_MAX,                             ///< SE ID Max
} LX_AUD_MASTER_SE_ID_T;

/**
 * AUDIO MASTER SE PARAM Index.
 */
typedef enum LX_AUD_MASTER_SE_PARAM {
    LX_AUD_MASTER_SE_PARAM_SPK,                         ///< speaker only for speaker.
    LX_AUD_MASTER_SE_PARAM_SPK_BT_SPK,                  ///< speaker + bt/bt surround for speaker.
    LX_AUD_MASTER_SE_PARAM_SPK_ARC,                     ///< arc for arc.
    LX_AUD_MASTER_SE_PARAM_SPK_BT_BT,                   ///< speaker + bt for bt.
    LX_AUD_MASTER_SE_PARAM_SPK_BTSUR_BT,                ///< speaker/arc + bt surround for bt.
    LX_AUD_MASTER_SE_PARAM_MAX,                         ///< SE PARAM Max
} LX_AUD_MASTER_SE_PARAM_T;

/**
 * AUDIO MASTER SE Function Mode.
 */
typedef enum {
    LX_AUD_MASTER_SE_FN_000,            ///< SDV
    LX_AUD_MASTER_SE_FN_000_1,          ///< SDV
    LX_AUD_MASTER_SE_FN_001,            ///< AGC
    LX_AUD_MASTER_SE_FN_001_1,          ///< AGC
    LX_AUD_MASTER_SE_FN_002,            ///< DB
    LX_AUD_MASTER_SE_FN_002_1,          ///< DB
    LX_AUD_MASTER_SE_FN_003,            ///< DEQ
    LX_AUD_MASTER_SE_FN_004,            ///< SSM
    LX_AUD_MASTER_SE_FN_004_1,          ///< SSM
    LX_AUD_MASTER_SE_FN_005,            ///< SO
    LX_AUD_MASTER_SE_FN_006,            ///< not used
    LX_AUD_MASTER_SE_FN_007,            ///< not used
    LX_AUD_MASTER_SE_FN_008,            ///< HC
    LX_AUD_MASTER_SE_FN_008_1,          ///< HC
    LX_AUD_MASTER_SE_FN_009,            ///< Sound Engine Volume
    LX_AUD_MASTER_SE_FN_010,            ///< INCHECK
    LX_AUD_MASTER_SE_FN_011,            ///< IVSE
    LX_AUD_MASTER_SE_FN_012,            ///< not used
    LX_AUD_MASTER_SE_FN_013,            ///< NE
    LX_AUD_MASTER_SE_FN_014,            ///< ASC
    LX_AUD_MASTER_SE_FN_015,            ///< not used
    LX_AUD_MASTER_SE_FN_016,            ///< ELC
    LX_AUD_MASTER_SE_FN_017,            ///< SXP
    LX_AUD_MASTER_SE_FN_017_1,          ///< SXP
    LX_AUD_MASTER_SE_FN_017_2,          ///< SXP
    LX_AUD_MASTER_SE_FN_017_3,          ///< SXP
    LX_AUD_MASTER_SE_FN_018,            ///< ROOMEQ
    LX_AUD_MASTER_SE_FN_019,            ///< DRC
    LX_AUD_MASTER_SE_FN_019_1,          ///< DRC
    LX_AUD_MASTER_SE_FN_020,            ///< not used
    LX_AUD_MASTER_SE_FN_021,            ///< not used
    LX_AUD_MASTER_SE_FN_022,            ///< SSC
    LX_AUD_MASTER_SE_FN_022_1,          ///< SSC
    LX_AUD_MASTER_SE_FN_022_2,          ///< SSC
    LX_AUD_MASTER_SE_FN_023,            ///< Reverberator
    LX_AUD_MASTER_SE_FN_024,            ///< Harmonizer
    LX_AUD_MASTER_SE_FN_025,            ///< User EQ
    LX_AUD_MASTER_SE_FN_026,            ///< CNXT Req
    LX_AUD_MASTER_SE_FN_027,            ///< Add AMB
    LX_AUD_MASTER_SE_FN_028,            ///< SXP Sup
    LX_AUD_MASTER_SE_FN_029,            ///< DRC Sup
    LX_AUD_MASTER_SE_FN_030,            ///< AI Sound feature extraction
    LX_AUD_MASTER_SE_FN_030_1,          ///< AI Sound Synthesizer
    LX_AUD_MASTER_SE_FN_031,            ///< AI Sound Surround
    LX_AUD_MASTER_SE_FN_032,            ///< AI Sound Clear voice
    LX_AUD_MASTER_SE_FN_MAX,            ///< SE Function Max
    LX_AUD_MASTER_SE_FN_GET,            ///< mode to get SE inforamtion
    LX_AUD_MASTER_SE_MAIN               =   101,        ///< MAIN
    LX_AUD_MASTER_SE_FN_SET             =   102,        ///< mode to set functions
    LX_AUD_MASTER_SE_FN_UPDATE_PARAM    =   103,        ///< mode to update setted parameters for reset
} LX_AUD_MASTER_SE_FN_T;

/**
 * AUDIO MASTER Sound Engine Data Option.
 */
typedef enum {
    LX_AUD_MASTER_SE_DATA_INIT_ONLY,                    ///< Initial Value only
    LX_AUD_MASTER_SE_DATA_VARIABLES,                    ///< Variables
    LX_AUD_MASTER_SE_DATA_ALL,                          ///< All
} LX_AUD_MASTER_SE_DATA_T;

/**
 * AUDIO MASTER Sound Engine Variable Option.
 */
typedef enum {
    LX_AUD_MASTER_SE_VAR_00,                            ///< Variable 0
    LX_AUD_MASTER_SE_VAR_01,                            ///< Variable 1
    LX_AUD_MASTER_SE_VAR_02,                            ///< Variable 2
    LX_AUD_MASTER_SE_VAR_03,                            ///< Variable 3
    LX_AUD_MASTER_SE_VAR_04,                            ///< Variable 4
    LX_AUD_MASTER_SE_VAR_ALL,                           ///< Variable All
} LX_AUD_MASTER_SE_VAR_T;

/**
 * AUDIO MASTER Sound Engine Data Access Mode.
 */
typedef enum {
    LX_AUD_MASTER_SE_ACCESS_WRITE,                      ///< Write Mode
    LX_AUD_MASTER_SE_ACCESS_READ,                       ///< Read Mode
} LX_AUD_MASTER_SE_ACCESS_T;

/**
 * AUDIO MASTER Sound Bar Command Mode.
 */
typedef enum {
    LX_AUD_MASTER_SB_CMD_AUTO_VOLUME,                   ///< Auto Volume Mode
    LX_AUD_MASTER_SB_CMD_WOOFER_LEVEL,                  ///< Woofer Level Mode
    LX_AUD_MASTER_SB_CMD_WIRELESS_RESET,                ///< Wireless Reset Mode
} LX_AUD_MASTER_CMD_MODE_T;

/**
 * AUDIO Mixed IP Power Block.
 *
 */
typedef  enum
{
    LX_AUD_MASTER_POWER_AADAFE,                         ///< Mixed IP AADAFE Power Block
    LX_AUD_MASTER_POWER_ADC,                            ///< Mixed IP ADC Power Block
    LX_AUD_MASTER_POWER_DAC,                            ///< Mixed IP DAC Power Block
    LX_AUD_MASTER_POWER_MAX,                            ///< the max marker of this enumeration
} LX_AUD_MASTER_POWER_BLOCK_T;

/**
 * AUDIO Mixed IP Power Mode.
 *
 */
typedef  enum
{
    LX_AUD_MASTER_POWER_DOWN,                           ///< Power down
    LX_AUD_MASTER_POWER_UP,                             ///< Power up
} LX_AUD_MASTER_POWER_MODE_T;

/**
 * AUDIO MASTER Speaker Output Source.
 */
typedef enum {
    LX_AUD_MASTER_SPK_NONE,                             ///< none
    LX_AUD_MASTER_SPK_PCM,                              ///< PCM data of DSP1. default
    LX_AUD_MASTER_SPK_PCM_0,                            ///< PCM data of DSP0
} LX_AUD_MASTER_SPK_OUTPUT_T;

/**
 * Audio Mixer ID.
 */
typedef  enum
{
    LX_AUD_MASTER_MIXER_0,                              ///< Mixer 0
    LX_AUD_MASTER_MIXER_1,                              ///< Mixer 1
    LX_AUD_MASTER_MIXER_2,                              ///< Mixer 2
    LX_AUD_MASTER_MIXER_3,                              ///< Mixer 3
    LX_AUD_MASTER_MIXER_4,                              ///< Mixer 4
    LX_AUD_MASTER_MIXER_5,                              ///< Mixer 5
    LX_AUD_MASTER_MIXER_6,                              ///< Mixer 6
    LX_AUD_MASTER_MIXER_7,                              ///< Mixer 7
    LX_AUD_MASTER_MIXER_MAX,                            ///< the max marker of this enumeration
} LX_AUD_MASTER_MIXER_T;

/**
 * AUDIO MASTER PostProcess modes.
 */
typedef enum {
    LX_AUD_MASTER_POSTPROC_LGSE_MODE,               ///< 0(Use LGSE for Audio post processing)
    LX_AUD_MASTER_POSTPROC_DAP_LGSE_MODE,           ///< 1(Use both LGSE and DAP for Audio post processing)
    LX_AUD_MASTER_POSTPROC_DAP_MODE,                ///< 2(Use DAP for audio post processing and volume and upsampling function with LGSE processing)
} LX_AUD_MASTER_POSTPROC_MODE_T;

/**
 * Video Output modes.
 */
typedef enum {
    LX_AUD_VIDEO_OUTPUT_60HZ_MODE,                  ///< 0( 60Hz UHD Model)
    LX_AUD_VIDEO_OUTPUT_120HZ_MODE,                 ///< 1(120Hz UHD Model)
} LX_AUD_VIDEO_OUTPUT_MODE_T;

/**
 * AUDIO MASTER DAP(Dolby Audio Processing) Functions.
 */
typedef enum LX_AUD_MASTER_DAP_FN {
    LX_AUD_MASTER_DAP_FN_DIALOG_ENHANCER,           ///< 0
    LX_AUD_MASTER_DAP_FN_VOLUME_LEVELER,            ///< 1
    LX_AUD_MASTER_DAP_FN_VOLUME_MODELER,            ///< 2
    LX_AUD_MASTER_DAP_FN_VOLUME_MAXIMIZER,          ///< 3
    LX_AUD_MASTER_DAP_FN_AUDIO_OPTIMIZER,           ///< 4
    LX_AUD_MASTER_DAP_FN_PROCESS_OPTIMIZER,         ///< 5
    LX_AUD_MASTER_DAP_FN_SURROUND_DECODER,          ///< 6
    LX_AUD_MASTER_DAP_FN_SURROUND_COMPRESSOR,       ///< 7
    LX_AUD_MASTER_DAP_FN_SPEAKER_VIRTUALIZER,       ///< 8
    LX_AUD_MASTER_DAP_FN_INTELLIGENT_EQUALIZER,     ///< 9
    LX_AUD_MASTER_DAP_FN_MEDIA_INTELLIGENCE,        ///< 10
    LX_AUD_MASTER_DAP_FN_GRAPHIC_EQUALIZER,         ///< 11
    LX_AUD_MASTER_DAP_FN_PERCEPTUAL_HEIGHT_FILTER,  ///< 12
    LX_AUD_MASTER_DAP_FN_BASS_ENHANCER,             ///< 13
    LX_AUD_MASTER_DAP_FN_BASS_EXTRACTION,           ///< 14
    LX_AUD_MASTER_DAP_FN_AUDIO_REGULATOR,           ///< 15
    LX_AUD_MASTER_DAP_FN_VIRTUAL_BASS,              ///< 16
    LX_AUD_MASTER_DAP_FN_SYS_PARAM,                 ///< 17 Set All DAP
    LX_AUD_MASTER_DAP_FN_SET_ENABLED_MODE,          ///< 18 Set Enabled DAP MODE
    LX_AUD_MASTER_DAP_FN_MAX,                       ///< DAP Function Max
} LX_AUD_MASTER_DAP_FN_T;

/**
 * AUDIO MASTER DAP Virtualizer modes.
 */
typedef enum {
    LX_AUD_MASTER_DAP_VIRTUALIZER_OFF,              ///< 0(Use LGSE for Audio post processing)
    LX_AUD_MASTER_DAP_VIRTUALIZER_ON,               ///< 1(Use LGSE for Audio post processing)
    LX_AUD_MASTER_DAP_VIRTUALIZER_AUTO,             ///< 2(Use LGSE for Audio post processing)
    LX_AUD_MASTER_DAP_VIRTUALIZER_ON_2_0_2,         ///< 3(Use LGSE for Audio post processing)
} LX_AUD_MASTER_DAP_VIRTUALIZER_MODE_T;

/**
 * AUDIO MASTER DAP PARAM Index.
 */
typedef enum LX_AUD_MASTER_DAP_PARAM {
    LX_AUD_MASTER_DAP_PARAM_SPK,                         ///< speaker only for speaker.
    LX_AUD_MASTER_DAP_PARAM_SPK_ARC,                     ///< speaker + arc for speaker/arc.
    LX_AUD_MASTER_DAP_PARAM_MAX,                         ///< DAP PARAM Max
} LX_AUD_MASTER_DAP_PARAM_T;

/**
 * AUDIO MASTER SE Function Parameters.
 */
typedef struct {
    LX_AUD_MASTER_SE_PARAM_T        index;              ///< 0 : SE Only, 1 : SE for Speaker on BT Surround mode, 2 : SE for BT on BT Surround Mode.
    LX_AUD_MASTER_SE_FN_T           fnMode;             ///< function mode
    LX_AUD_MASTER_SE_DATA_T         dataOption;         ///< data option
    LX_AUD_MASTER_SE_VAR_T          varOption;          ///< variable option
    LX_AUD_MASTER_SE_ACCESS_T       accessMode;         ///< access mode
    union
    {
        UINT32                          *ui32Param;         ///< the pointer to parameters
        UINT32                          compat_ui32Param;
        UINT64                          sizer;
    };
    UINT32                          ui32NoParam;        ///< the number of parameters
} LX_AUD_MASTER_PARAM_SE_FN_T;

/**
 * AUDIO MASTER Volume Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T          output;             ///< output
    UINT32                          ui32Volume;         ///< gain. value = origin * gain. For example, if 0x800000, gain is 1, if 0x400000, 0.5.
} LX_AUD_MASTER_CONFIG_VOLUME_T;

/**
 * AUDIO MASTER DAC Volume Configuration.
 */
typedef struct {
    LX_AUD_OUTPUT_PORT_T            dacPort;            ///< DAC port
    UINT32                          ui32Volume;         ///< gain. value = origin * gain. For example, if 0x800000, gain is 1, if 0x400000, 0.5.
} LX_AUD_MASTER_CONFIG_DAC_VOLUME_T;

/**
 * AUDIO MASTER Mute Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T          output;             ///< output
    UINT32                          ui32Mute;           ///< mute on or off
} LX_AUD_MASTER_CONFIG_MUTE_T;

/**
 * AUDIO MASTER DAC Mute Configuration.
 */
typedef struct {
    LX_AUD_OUTPUT_PORT_T            dacPort;            ///< DAC port
    UINT32                          ui32Mute;           ///< mute on or off
    LX_AUD_DAC_MODE_T               mode;               ///< DAC mode
} LX_AUD_MASTER_CONFIG_DAC_MUTE_T;

/**
 * AUDIO MASTER Delay Time Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T          output;             ///< output
    UINT32                          ui32Delay;          ///< delay. unit is milisecond.
} LX_AUD_MASTER_CONFIG_DELAY_T;

/**
 * AUDIO Output Delay Time Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T          output;             ///< output
    UINT32                          ui32Delay;          ///< delay. unit is milisecond.
    UINT32                          ui32AdjustDelay;    ///< adjust delay. unit is milisecond.
} LX_AUD_MASTER_CONFIG_OUTPUT_DELAY_T;

/**
 * AUDIO MASTER Output Mode Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T      output;                 ///< output
    LX_AUD_MASTER_OUT_MODE_T    outMode;                ///< output mode
} LX_AUD_MASTER_CONFIG_OUT_MODE_T;

/**
 * AUDIO MASTER SPDIF Output Type Configuration.
 */
typedef struct {
    LX_AUD_MASTER_IEC_OUT_T spdifOutput;                ///< SPDIF output type
} LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T;

/**
 * AUDIO MASTER IEC Output Type Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T      output;                 ///< output
    LX_AUD_MASTER_IEC_OUT_T     iecOutput;              ///< IEC (SPDIF/ARC) output type
} LX_AUD_MASTER_CONFIG_IEC_OUTPUT_T;

/**
 * AUDIO MASTER Dolby OTT Mode Configuration.
 */
typedef struct {
    UINT32      bIsOTTEnable;               ///< enable/disable OTT Mode
    UINT32      bIsATMOSLockingEnable;      ///< enable/disable ATMOS Locking
} LX_AUD_MASTER_DOLBY_OTT_MODE_T;

/**
 * AUDIO MASTER Dolby DRC Cut & Boost Mode Configuration.
 */
typedef struct {
    UINT32      ui32Cut;                    ///< cut value : 0 ~ 100, Default = 100, mix = 0
    UINT32      ui32Boost;                  ///< boost value : 0 ~ 100, Default = 100, mix = 0
} LX_AUD_MASTER_DRC_CUT_BOOST_MODE_T;

/**
 * AUDIO MASTER Output Connect Index Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T      output;
    UINT32                      ui32Index;
    UINT32                      ui32IsConnect;
} LX_AUD_MASTER_OUTPUT_CONNECT_CONFIG_T;

/**
 * AUDIO MASTER SPDIF SCMS Configuration.
 */
typedef struct {
    LX_AUD_MASTER_SPDIF_SCMS_T  spdifScms;              ///< SPDIF SCMS state
} LX_AUD_MASTER_CONFIG_SPDIF_SCMS_T;

/**
 * AUDIO MASTER ARC SCMS Configuration.
 */
typedef struct {
    LX_AUD_MASTER_ARC_SCMS_T  arcScms;                  ///< ARC SCMS state
} LX_AUD_MASTER_CONFIG_ARC_SCMS_T;

/**
 * AUDIO MASTER BALANCE Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T          output;             ///< output
    UINT32                          ui32Balance;        ///< balance. 0 ~ 100. if 0, left speaker only outputs, if 100, right only.
} LX_AUD_MASTER_CONFIG_BALANCE_T;

/**
 * AUDIO MASTER BASS Configuration. not used.
 */
typedef struct {
    UINT32                          ui32Bass;           ///< bass
} LX_AUD_MASTER_CONFIG_BASS_T;

/**
 * AUDIO MASTER TREBLE Configuration.not used.
 */
typedef struct {
    UINT32                          ui32Treble;         ///< treble
} LX_AUD_MASTER_CONFIG_TREBLE_T;

/**
 * AUDIO Mixed IP Power Structure.
 */
typedef struct {
    LX_AUD_MASTER_POWER_BLOCK_T         powerBlock;     ///< mixed ip power block
    LX_AUD_MASTER_POWER_MODE_T          powerMode;      ///< mixed ip power mode
} LX_AUD_MASTER_CONFIG_POWER_CTRL_T;

/**
 * AUDIO MASTER Speaker Output source Configuration.
 */
typedef struct {
    LX_AUD_MASTER_SPK_OUTPUT_T  spkOutput;              ///< speaker output source.
    UINT32                      ui32I2SNum;             ///< number of I2S.
    LX_AUD_SAMPLING_FREQ_T      samplingFreq;           ///< sampling Frequency.
} LX_AUD_MASTER_CONFIG_SPK_OUTPUT_T;

/**
 * AUDIO MASTER SPDIF Output Type Configuration.
 */
typedef struct {
    LX_AUD_SAMPLING_FREQ_T      samplingFreq;           ///< sampling Frequency.
} LX_AUD_MASTER_CONFIG_SPDIF_T;

/**
 * AUDIO MASTER Mixer Delay Time Configuration. not used.
 */
typedef struct {
    LX_AUD_MASTER_MIXER_T           mixer;              ///< mixer id.
    UINT32                          ui32Port;           ///< mixer input port.
    UINT32                          ui32Delay;          ///< delay. unit is miliseconds.
} LX_AUD_MASTER_CONFIG_MIXER_DELAY_T;

/**
 * AUDIO MASTER Mixer Volume Configuration. not used.
 */
typedef struct {
    LX_AUD_MASTER_MIXER_T           mixer;              ///< mixer id.
    UINT32                          ui32Port;           ///< mixer input port.
    UINT32                          ui32Volume;         ///< volume. 0 ~ 1024.
} LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T;

/**
 * AUDIO MASTER Mixer Volume Configuration. not used.
 */
typedef struct {
    UINT32                          ui32Port;           ///< mixer input port.
    UINT32                          ui32Mute;           ///< Mute On Off.
    UINT32                          ui32Duration;       ///< Duration Time.
    LX_AUD_EASE_TYPE_T              ui32EaseType;       ///< Ease Type.
} LX_AUD_MASTER_CONFIG_MIXER_MUTE_T;

/**
 * AUDIO MASTER LGSE Mode.
 */
struct LX_AUD_MASTER_LGSE_MODE {
    LX_AUD_MASTER_OUTPUT_T      output;                 ///< output
    BOOLEAN                     bUseSE;                 ///< use Sound Engine or not
    BOOLEAN                     bUseDAP;                ///< use DAP(Dolby Audio Processing) or not
    BOOLEAN                     bUseVX;                 ///< use DTS Virtual X or not
    BOOLEAN                     bUseAISE;               ///< use AI Sound or not
};

typedef struct LX_AUD_MASTER_LGSE_MODE LX_AUD_MASTER_LGSE_MODE_T;

/**
 * AUDIO MASTER Connect Configuration.
 */
typedef struct {
    UINT32                      ui32KdrHandler;         ///< allocated device. Hal driver don't need set, kadp driver does.
    UINT32                      ui32Index;              ///< index
    LX_AUD_MASTER_OUTPUT_T      output;                 ///< output
} LX_AUD_MASTER_CONNECT_OUTPUT_INDEX_T;

/**
 * AUDIO MASTER Disconnect Configuration.
 */
typedef struct {
    UINT32                      ui32KdrHandler;         ///< allocated device. Hal driver don't need set, kadp driver does.
    UINT32                      ui32Index;              ///< index
    LX_AUD_MASTER_OUTPUT_T      output;                 ///< output
} LX_AUD_MASTER_DISCONNECT_OUTPUT_INDEX_T;

/**
 * AUDIO MASTER SOUND BAR PARAM.
 */
typedef struct {
    UINT32                      ui32ID;                 ///< Sound Bar id
    UINT32                      ui32Data;               ///< Sound Bar data. 8th bit is mute, 0~7th bits are volume.
} LX_AUD_MASTER_SOUNDBAR_PARAM_T;

/**
 * AUDIO MASTER SOUND BAR COMMAND PARAM.
 */
typedef struct {
    LX_AUD_MASTER_CMD_MODE_T    cmdMode;            ///< command mode
    UINT32                      ui32CmdParam;       ///< the command of parameters
} LX_AUD_MASTER_SOUNDBAR_CMD_T;

/**
 * AUDIO MASTER SOUND BAR/WIRELESS/FRAME SET STATUS.
 */
typedef struct {
    UINT32                      ui32SoundBarOnOff;      ///< Sound Bar on or not.
    UINT32                      ui32SoundFrameOnOff;    ///< Sound Frame on or not.
    UINT32                      ui32WisaSpkOnOff;       ///< WiSA Speaker on or not.
    UINT32                      ui32BlueToothOnOff;     ///< BlueTooth Sound Bar on or not.
    UINT32                      ui32BTSurroundOnOff;    ///< BlueTooth Surround Sound Bar on or not.
} LX_AUD_MASTER_SOUNDBAR_T;

/**
 * AUDIO MASTER SOUND BAR STATUS.
 */
typedef struct {
    UINT32                      ui32SoundBarOnOff;      ///< Sound Bar on or not.
    UINT32                      ui32SubFrameID;         ///< subframe id.
    UINT32                      ui32SubFrameData;       ///< subframe data.
    UINT32                      ui32SubFrameCheckSum;   ///< subframe checksum.
    UINT32                      ui32SoundFrameOnOff;    ///< Sound Frame on or not.
    UINT32                      ui32WisaSpkOnOff;       ///< WiSA Speaker on or not.
    UINT32                      ui32BlueToothOnOff;     ///< BlueTooth Sound Bar on or not.
    UINT32                      ui32BTSurroundOnOff;    ///< BlueTooth Surround Sound Bar on or not.
} LX_AUD_MASTER_SOUNDBAR_STATUS_T;

/**
 * AUDIO MASTER Connect Index to Output Configuration.
 */
typedef struct {
    UINT32                          ui32Index;              ///< allocated device.
    LX_AUD_MASTER_OUTPUT_T          output;                 ///< output
    LX_AUD_MASTER_SPDIF_OUTPUT_T    spdifOutput;            ///< spdif output
} LX_AUD_MASTER_CONNECT_INDEX_OUTPUT_T;

/**
 * AUDIO MASTER Disconnect Index to Output Configuration.
 */
typedef struct {
    UINT32                          ui32Index;              ///< allocated device.
    LX_AUD_MASTER_OUTPUT_T          output;                 ///< output
    LX_AUD_MASTER_SPDIF_OUTPUT_T    spdifOutput;            ///< spdif output
} LX_AUD_MASTER_DISCONNECT_INDEX_OUTPUT_T;

/**
 * Set input volume for index.
 */
typedef struct {
    UINT32                          ui32Index;              ///< allocated device.
    UINT32                          ui32Volume;             ///< volume
    UINT32                          ui32Duration;           ///< duration. ms.
    LX_AUD_EASE_TYPE_T              ui32EaseType;           ///< ease type
} LX_AUD_SET_INPUT_VOLUME_T;

/**
 * Set input mute for index.
 */
typedef struct {
    UINT32                          ui32Index;              ///< allocated device.
    UINT32                          ui32Mute;               ///< mute
    LX_AUD_DEV_OUT_TYPE_T           outType;                ///< device output type.
} LX_AUD_SET_INPUT_MUTE_T;

/**
 * Set input delay for index.
 */
typedef struct {
    UINT32                          ui32Index;              ///< allocated device.
    UINT32                          ui32Delay;              ///< delay
    LX_AUD_DEV_OUT_TYPE_T           outType;                ///< device output type.
} LX_AUD_INPUT_DELAY_T;

/**
 * AUDIO MASTER Get Index Delay Configuration.
 */
typedef struct {
    UINT32                          ui32Index;              ///< allocated device.
    LX_AUD_DEV_TYPE_T               devType;                ///< output
    UINT32                          bLipsyncOnOff;          ///< lipsync On
    UINT32                          ui32Delay;              ///< device delay time(ms)
} LX_AUD_GET_INDEX_DELAY_T;

/**
 * device started or not information.
 */
typedef struct {
    LX_AUD_DEV_TYPE_T               devType;                ///< device type
    LX_AUD_DEV_T                    dev;                    ///< device id
    LX_AUD_DEV_OUT_TYPE_T           devOutType;             ///< device output type
    UINT32                          ui32Index;              ///< device index
    UINT32                          bStarted;               ///< device status is started or not
} LX_AUD_START_INFO_T;

/**
 * Get devices' started or not information.
 */
typedef struct {
    LX_AUD_START_INFO_T             startInfo[NUM_OF_START_INFO];               ///< device started info
} LX_AUD_GET_START_INFO_T;


/**
 * AUDIO MASTER IEC Output Encoded Type Configuration.
 */
typedef struct {
    LX_AUD_MASTER_OUTPUT_T          output;                 ///< output
    LX_AUD_MASTER_IEC_OUT_ENCODED_T iecOutEncodedType;      ///< IEC output encoded type
} LX_AUD_MASTER_CONFIG_IEC_OUT_ENCODED_T;

/**
 * AUDIO MASTER DAP Function Parameters.
 */
typedef struct {
    LX_AUD_MASTER_DAP_FN_T          fnMode;             ///< function mode
    UINT32                          ui32SizeOfParam;    ///< the size of parameters
    union
    {
        void                            *pParam;            ///< the pointer to parameters
        UINT32                          compat_pParam;
        UINT64                          sizer;
    };
} LX_AUD_MASTER_PARAM_DAP_FN_T;

/**
 * AUDIO MASTER DAP SET VIRTUALIZER MODE.
 */
typedef struct {
    LX_AUD_MASTER_DAP_VIRTUALIZER_MODE_T            virtualizerMode;    ///< Virtualizer mode
} LX_AUD_MASTER_PARAM_DAP_VIRTUALIZER_MODE_T;

/**
 * DAP(Dolby Audio Processing) suppported auido type Definition
 *
*/
typedef struct
{
    BOOLEAN     bEnableAll;         /* All audiotype should be processed by DAP */
    BOOLEAN     bEnableATMOS;       /* ATMOS should be processed by DAP, regardless of AC4, eAC3, AC3 and AAC */
    BOOLEAN     bEnableAC4;         /* AC4 should be processed by DAP */
    BOOLEAN     bEnableEAC3;        /* EAC3 should be processed by DAP */
    BOOLEAN     bEnableAC3;         /* AC3 should be processed by DAP */
    BOOLEAN     bEnableAAC;         /* AAC should be processed by DAP */
    BOOLEAN     bEnableMPEGH;       /* MPEGH should be processed by DAP */
    BOOLEAN     bEnableMPEG;        /* MPEG should be processed by DAP */
    BOOLEAN     bEnableDTS;         /* DTS should be processed by DAP */
} LX_AUD_DAP_SUPPORTED_CODEC_T;

/**
 * AUDIO MASTER Virtual X Functions.
 */
typedef enum {
    LX_AUD_VX_FIRST_FN,
    LX_AUD_VX_ENABLE_I32 = LX_AUD_VX_FIRST_FN,
    LX_AUD_VX_INPUT_MODE_I32,
    LX_AUD_VX_OUTPUT_MODE_I32,
    LX_AUD_VX_HEADROOM_GAIN_I32,
    LX_AUD_VX_PROC_OUTPUT_GAIN_I32,
    LX_AUD_VX_REFERENCE_LEVEL_I32,
    LX_AUD_VX_TSX_ENABLE_I32,
    LX_AUD_VX_TSX_PASSIVEMATRIXUPMIX_ENABLE_I32,
    LX_AUD_VX_TSX_HEIGHT_UPMIX_ENABLE_I32,
    LX_AUD_VX_TSX_LPR_GAIN_I32,
    LX_AUD_VX_TSX_CENTER_GAIN_I32,
    LX_AUD_VX_TSX_HORIZ_VIR_EFF_CTRL_I32,
    LX_AUD_VX_TSX_HEIGHTMIX_COEFF_I32,
    LX_AUD_VX_TSX_PROCESS_DISCARD_I32,
    LX_AUD_VX_DC_ENABLE_I32,
    LX_AUD_VX_DC_CONTROL_I32,
    LX_AUD_VX_DEF_ENABLE_I32,
    LX_AUD_VX_DEF_CONTROL_I32,
    LX_AUD_VX_TSX_HORIZ_VIR_EFF_CTRL_2CH_I32,
    LX_AUD_VX_TSX_HORIZ_VIR_EFF_CTRL_MULTICH_I32,
    LX_AUD_VX_TSX_HEIGHTMIX_COEFF_2CH_I32,
    LX_AUD_VX_TSX_HEIGHTMIX_COEFF_MULTICH_I32,
    LX_AUD_VX_TSX_LPR_GAIN_2CH_I32,
    LX_AUD_VX_TSX_LPR_GAIN_MULTICH_I32,
    LX_AUD_VX_FN_MAX,                       ///< Virtual X Function Max
    LX_AUD_VX_TSX_CONTROLS_STU,             ///< not used
} LX_AUD_VX_FN_T;

/**
 * AUDIO MASTER Virtual X Function Parameters.
 */
typedef struct {
    LX_AUD_VX_FN_T           fnMode;             ///< function mode
    SINT32                          param;              ///< parameters
} LX_AUD_VX_FN_PARAM_T;

/**
 * AUDIO MASTER Audio Processing Status.
 */
typedef struct {
    UINT32                              ui32UseSE;                  ///< SE is used.
    UINT32                              ui32UseDAP;                 ///< DAP is used.
    LX_AUD_MASTER_POSTPROC_MODE_T       stPostProcMode;             ///< PostProcess mode.
    LX_AUD_DAP_SUPPORTED_CODEC_T        stDAPSupportedCodec;        ///< structure of Supported Audio Codec Info for DAP.
} LX_AUD_MASTER_AUDIO_PROCESSING_STATUS_T;

/**
 * Video Output and Panel Type Status.
 */
typedef struct {
    LX_AUD_VIDEO_OUTPUT_MODE_T      stVideoOutputMode;      ///< Video Output mode.
    BOOLEAN                         bOLEDModel;             ///< OLED Model.
} LX_AUD_VIDEO_OUTPUT_STATUS_T;

/**
 * AUDIO MASTER Configuration.
 */
typedef struct {
    LX_AUD_MS12_VERSION_T       ms12Ver;            ///< MS12 Version
    UINT32                      arcOnOff;           ///< On or Off for ARC output.
    BOOLEAN                     isOpenEncoder;      ///< wheather Encoder Device is open or not.
    BOOLEAN                     isNewModule;        ///< wheather audio is new module
} LX_AUD_MASTER_GET_CONFIG_T;

/**
 * AUDIO MASTER ALSA DUMP PRARMETER.
 */
typedef struct {
    UINT32                      dumpSize;  ///< dump size(bytes).
    UINT32                      device;    ///< ALSA device num.
} LX_AUD_MASTER_ALSA_DUMP_PARAMS_T;

/**
 * AUDIO MASTER Get ARC Output Info.
 */
typedef struct {
	LX_AUD_CODEC_T              codecType;              ///< audio codec type.
	UINT32                      ui32AudioClock;         ///< ARC Output Audio Clock.
	UINT32                      ui32ChannelNum;         ///< Number of Audio Channels.
	BOOLEAN                     isAtmos;                ///< is ATMOS or not.
} LX_AUD_MASTER_ARC_OUTPUT_INFO_T;

/**
 * AUDIO MASTER Get Input Interrupt Count.
 */
typedef struct {
    UINT32                          ui32InputIntCount;      ///< input interrupt count.
    UINT32                          ui32UnitClockCount;     ///< DTV 90K tick, HDMI input clock per second.
} LX_AUD_INPUT_INT_COUNT_T;

/**
 * AUDIO MASTER EARC Output Info.
 */
typedef struct {
    BOOLEAN                             earc_onoff;
    sndout_earc_output_set_type_t       set_type;
    sndout_earc_output_codec_type_t     codec_type;
    sndout_earc_output_channel_num_t    channel_num;
    sndout_earc_output_sample_rate_t    sample_rate;
    sndout_earc_output_mix_option_t     mix_option;
} LX_AUD_MASTER_EARC_OUTPUT_INFO_T;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUDIO_KAPI_MASTER_H_ */

/** @} */
