/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  mjpeg encode/decode interface header.
 *
 *  @author		Jihoon Lee (gaius.lee@lge.com)
 *  @version	1.0
 *  @date		2015.02.04
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

#ifndef _MJPEG_CORE_SIC_H_
#define _MJPEG_CORE_SIC_H_

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    File Inclusions
-----------------------------------------------------------------------------*/
#include "base_types.h"
#include "mjpeg_kapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    Type Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Generic Usage Functions
    -----------------------------------------------------------------------------*/
int MJPEG_HwInit(void);
int MJPEG_HwEnd(void);
int MJPEG_HwReset(void);
int MJPEG_SetIsUseQueue(BOOLEAN bUseQueue);
UINT32 MJPEG_ENC_Init(LX_MJPEG_IMAGE_INFO_T *i_pstImageInfo,
					  LX_MJPEG_IMAGE_BUF_T *i_pstImageBuf,
					  LX_MJPEG_OPTION_T *i_pstOption,
					  LX_MJPEG_HEADER_T *o_pstHeader);
int MJPEG_ENC_Start(LX_MJPEG_MEM_BUF_T *i_pstDataBuf,
					UINT32 *pui32ReceivedEvent);
int MJPEG_ENC_Continue(UINT32 *pui32ReceivedEvent, UINT32 *pui32Size);
UINT32 MJPEG_ENC_End(void);
UINT32 MJPEG_DEC_Init(LX_MJPEG_HEADER_T *i_pstHeader,
					  LX_MJPEG_IMAGE_BUF_T *i_pstImageBuf,
					  LX_MJPEG_OPTION_T *i_pstOption,
					  LX_MJPEG_IMAGE_INFO_T *o_pstImageInfo);
int MJPEG_DEC_Start(LX_MJPEG_MEM_BUF_T *i_pstDataBuf, UINT32 i_ui32DataLength,
					BOOLEAN bEndofStream);
int MJPEG_DEC_Continue(LX_MJPEG_MEM_BUF_T *i_pstDataBuf,
					   UINT32 i_ui32DataLength, BOOLEAN bEndofStream,
					   BOOLEAN bSkipCheck);
int MJPEG_DEC_PartialContinue(UINT32 u32PartialBuffer);
int MJPEG_DEC_GetCurrentCoordinate(UINT16 *x, UINT16 *y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MJPEG_CORE_SIC_H_ */

/** @} */
