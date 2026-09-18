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


/** @file audio_kadp_decoder.h
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

#ifndef _AUDFW_KAPI_H_
#define _AUDFW_KAPI_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "common/adec_config.h"
#include "module/adec_module.h"
#include "buffer/adec_au_info.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define AUDFW_IOC_MAGIC                         'F'

/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/* firmware general */
#define AUDFW_IO_RESET                      _IO(AUDFW_IOC_MAGIC,    1)
#define AUDFW_IO_START                      _IO(AUDFW_IOC_MAGIC,    2)
#define AUDFW_IO_STOP                       _IO(AUDFW_IOC_MAGIC,    3)

/* imc command */
#define AUDFW_IOW_SEND_IMC_CMD              _IOW(AUDFW_IOC_MAGIC,   4, LX_AUD_MODULE_SEND_IMC_CMD_T)
#define AUDFW_IOW_RESPONSE_IMC_CMD          _IOW(AUDFW_IOC_MAGIC,   5, LX_AUD_MODULE_RESPONSE_IMC_CMD_T)
#define AUDFW_IOW_RAISE_IMC_EVENT           _IOW(AUDFW_IOC_MAGIC,   6, LX_AUD_MODULE_RAISE_IMC_EVENT_T)

/* module */
#define AUDFW_IOW_REGISTER_MODULE           _IOW(AUDFW_IOC_MAGIC,   7, LX_AUD_MODULE_REGISTER_T)

/* buffer */
#define AUDFW_IOWR_BUF_CTRL                 _IOWR(AUDFW_IOC_MAGIC,  8, LX_AUD_BUF_CTRL_T)

/* register */
#define AUDFW_IOWR_REG_READ                 _IOWR(AUDFW_IOC_MAGIC,  9, LX_AUD_REG_READ_T)
#define AUDFW_IOW_REG_WRITE                 _IOW(AUDFW_IOC_MAGIC,   10, LX_AUD_REG_WRITE_T)

/* misc */
#define AUDFW_IOW_CNM_GET_INPUT_MODULE_ID   _IOW(AUDFW_IOC_MAGIC,   11, LX_AUD_CNM_GET_INPUT_MODULE_ID_T)
#define AUDFW_IO_CHECK                      _IO(AUDFW_IOC_MAGIC,    12)

#define AUDFW_IOC_MAXNR                     200

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/**
 * AUDFW_IOW_SEND_IMC_CMD
 */
typedef struct {
    int                     cmd;
    ADEC_MODULE_ID          target;
    ADEC_MODULE_ID          source;
    IMC_INTERRUPT_TYPE      requestInterrupt;
    union
    {
        void*                   param;
        unsigned int            compat_param;
        unsigned long long      sizer;
    };
    int                     paramLen;
} LX_AUD_MODULE_SEND_IMC_CMD_T;

/**
 * AUDFW_IOW_RESPONSE_IMC_CMD
 */
typedef struct {
    ImcSenderInfo           target;
    ADEC_MODULE_ID          sender;
    IMC_INTERRUPT_TYPE      requestInterrupt;
    int                     cmd;
    ADEC_RESULT             result;
    union
    {
        void*                   param;
        unsigned int            compat_param;
        unsigned long long      sizer;
    };
    int                     paramLen;
} LX_AUD_MODULE_RESPONSE_IMC_CMD_T;

/**
 * AUDFW_IOW_RAISE_IMC_EVENT
 */
typedef struct {
    unsigned int            event;
    ADEC_MODULE_ID          owner;
    IMC_INTERRUPT_TYPE      requestInterrupt;
    union
    {
        void*                   param;
        unsigned int            compat_param;
        unsigned long long      sizer;
    };
    int                     paramLen;
} LX_AUD_MODULE_RAISE_IMC_EVENT_T;

/**
 * AUDFW_IOW_REGISTER_MODULE
 */
typedef struct {
    unsigned int            ui32ModuleId;
    AdecModuleTag           moduleTag;
    char                    szModuleName[ADEC_CNST_MODULE_NAME_LENGTH+1];
    unsigned int            ui32NumOfInput;
    unsigned int            ui32NumOfOutput;
} LX_AUD_MODULE_REGISTER_T;

/**
 * AUDFW_IOW_BUF_CTRL
 */
typedef enum {
    BUF_CTRL_INIT,
    BUF_CTRL_GET_FREE_SIZE,
    BUF_CTRL_GET_USED_SIZE,
    BUF_CTRL_GET_AU_CNT,
    BUF_CTRL_GET_MAX_SIZE,
    BUF_CTRL_GET_MAX_AU,
    BUF_CTRL_GET_MAX_AU_LENGTH,
    BUF_CTRL_CREATE_NEW_AU,
    BUF_CTRL_WRITE_DATA,
    BUF_CTRL_INSERT_AU,
    BUF_CTRL_UPDATE_AU,
    BUF_CTRL_GET_AU_INFO,
    BUF_CTRL_GET_CURRENT_INFO,
    BUF_CTRL_READ_DATA,
    BUF_CTRL_FLUSH_DATA,
    BUF_CTRL_READ_AU,
    BUF_CTRL_FINISH_AU,
} AUDFW_BUF_CTRL_TYPE_T;

typedef struct {
    AUDFW_BUF_CTRL_TYPE_T       type;
    unsigned int                buf_instance;

    union {
        /**
         * AUDFW_IOW_BUF_CREATE_NEW_AU
         */
        struct {
            ADEC_AU_INFO_T          info;
        } create_new_au;

        /**
         * AUDFW_IOW_BUF_WRITE_DATA
         */
        struct {
            unsigned char*          src;
            int                     length;
        } write_data;

        /**
         * AUDFW_IOW_BUF_INSERT_AU
         */
        struct {
            unsigned char*          src;
            int                     length;
            ADEC_AU_INFO_T          info;
        } insert_au;

        /**
         * AUDFW_IOW_BUF_UPDATE_AU
         */
        struct {
            ADEC_AU_INFO_T          info;
        } update_au;

        /**
         * AUDFW_IORW_BUF_GET_AU_INFO
         */
        struct {
            int                     index;
            int                     offset;
            ADEC_AU_INFO_T          info;
        } get_au_info;

        /**
         * AUDFW_IORW_BUF_GET_CURRENT_INFO
         */
        struct {
            int                     offset;
            ADEC_AU_INFO_T          info;
        } get_current_info;

        /**
         * AUDFW_IORW_BUF_READ_DATA
         */
        struct {
            void*                   dst;
            int                     size;
            int                     au_in_data;
        } read_data;

        /**
         * AUDFW_IOW_BUF_FLUSH_DATA
         */
        struct {
            int                     size;
        } flush_data;

        /**
         * AUDFW_IOW_BUF_READ_AU
         */
        struct {
            unsigned char*          dst;
            int                     size;
            int                     au_cnt;
        } read_au;
    } p;
} LX_AUD_BUF_CTRL_T;

/**
 * AUDFW_IOWR_REG_READ
 */
typedef struct {
    unsigned int            reg;
    unsigned int            data;
} LX_AUD_REG_READ_T;

/**
 * AUDFW_IOWR_REG_WRITE
 */
typedef struct {
    unsigned int            reg;
    unsigned int            data;
} LX_AUD_REG_WRITE_T;

/**
 * AUDFW_IOW_CNM_GET_INPUT_MODULE_ID
 */
typedef struct {
    unsigned int            ui32ModuleId;
    int                     port;
} LX_AUD_CNM_GET_INPUT_MODULE_ID_T;

#endif /* _AUDFW_KAPI_H_ */

/** @} */
