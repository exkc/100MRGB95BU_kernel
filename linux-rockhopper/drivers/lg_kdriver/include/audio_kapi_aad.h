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


/** @file audio_kadp_aad.h
 *
 *  This is a wrapper function file for adec_ddi.c to process ADEC function.
 *  The simple wrapper function for audio kernel module.
 *
 *  @author     Won Chang Shin(wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2015.12.18
 *  @note       The simple wrapper function for audio kernel module.
 *
 *  @addtogroup lg1150_audio
 *  @{
 */

#ifndef _AUDIO_KAPI_AAD_H_
#define _AUDIO_KAPI_AAD_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "audio_kapi.h"
#include "aad_kapi.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define AUD_AAD_IOC_MAGIC               'A'

// The Size of AUD AAD KDRV IPC Command
#define LX_AAD_IPC_ARRAY_SIZE           100


/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define AUD_AAD_IOR_GET_KDRV_HANDLE                 _IOR(AUD_AAD_IOC_MAGIC, 1, UINT32)
#define AUD_AAD_IO_START                            _IO(AUD_AAD_IOC_MAGIC, 2)
#define AUD_AAD_IO_STOP                             _IO(AUD_AAD_IOC_MAGIC, 3)
#define AUD_AAD_IO_FLUSH                            _IO(AUD_AAD_IOC_MAGIC, 4)
#define AUD_AAD_IO_CLOSE_DEVICE                     _IO(AUD_AAD_IOC_MAGIC, 5)

#define AUD_AAD_IOW_INIT_MODULE                     _IOW(AUD_AAD_IOC_MAGIC,  10, LX_AAD_INIT_TYPE_T)
#define AUD_AAD_IOW_SIF_SET_HIGH_DEV_MODE           _IOW(AUD_AAD_IOC_MAGIC,  11, LX_AAD_HIGH_DEV_SET_T)
#define AUD_AAD_IOW_SIF_SET_BAND_SETUP              _IOW(AUD_AAD_IOC_MAGIC,  12, LX_AAD_SIF_SOUNDSYSTEM_T)
#define AUD_AAD_IOW_SIF_SET_MODE_SETUP              _IOW(AUD_AAD_IOC_MAGIC,  13, LX_AAD_SIF_STANDARD_T)
#define AUD_AAD_IOW_SIF_SET_USER_ANALOG_MODE        _IOW(AUD_AAD_IOC_MAGIC,  14, LX_ATV_AUDIO_MODE_SET_T)
#define AUD_AAD_IOW_SIF_SET_THRESHOLD_LEVEL         _IOW(AUD_AAD_IOC_MAGIC,  15, LX_AAD_SIF_THRESHOLD_T)
#define AUD_AAD_IORW_SIF_GET_BAND_DETECT            _IOWR(AUD_AAD_IOC_MAGIC, 16, LX_AAD_SIF_SYSTEM_INFO_T)
#define AUD_AAD_IORW_SIF_CHECK_SOUND_MODE           _IOWR(AUD_AAD_IOC_MAGIC, 17, LX_AAD_SIF_STANDARD_INFO_T)
#define AUD_AAD_IOR_SIF_GET_THRESHOLD_LEVEL         _IOWR(AUD_AAD_IOC_MAGIC, 18, LX_AAD_SIF_THRESHOLD_T)
#define AUD_AAD_IOR_SIF_GET_CUR_ANALOG_MODE         _IOR(AUD_AAD_IOC_MAGIC,  19, LX_ATV_AUDIO_MODE_GET_T)
#define AUD_AAD_IOR_SIF_GET_SIF_STATUS              _IOR(AUD_AAD_IOC_MAGIC,  20, BOOLEAN)
#define AUD_AAD_IOW_SIF_SET_EQ_MODE                 _IOW(AUD_AAD_IOC_MAGIC,  21, UINT32)

#define AUD_AAD_IORW_SIF_READ_AND_WRITE_REG         _IOWR(AUD_AAD_IOC_MAGIC, 30, LX_AAD_REG_INFO_T)
#define AUD_AAD_IOW_DEBUG_PRINT_CTRL                _IOW(AUD_AAD_IOC_MAGIC,  31, LX_AAD_DEBUG_CTRL_T)

#define AUD_AAD_IORW_SET_IMC_COMMAND                _IOWR(AUD_AAD_IOC_MAGIC, 50, LX_AAD_IMC_CMD_T)

#define AUD_AAD_IOC_MAXNR                           200


/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * Set AUDIO AAD IPC Command.
 * audio ioctl parameter.
 * @see AUD_AAD_IOW_DEBUG_IMC_COMMAND
*/
typedef struct {
    UINT32      command;                        ///< The data of AAD IPC command
    UINT32      paramSize;                      ///< The size of AAD IPC parameter command
    UINT32      param[LX_AAD_IPC_ARRAY_SIZE];   ///< The data of parameters for AAD IPC command
} LX_AAD_IMC_CMD_T;



#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUDIO_KAPI_AAD_H_ */

/** @} */



