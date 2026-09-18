/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   COPYRIGHT(c) 1998-2010 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work covered by this copyright hereon
 *   may be reproduced, stored in a retrieval system, in any form
 *   or by any means, electronic, mechanical, photocopying, recording
 *   or otherwise, without the prior written  permission of LG Electronics.
 *****************************************************************************/

/** @file hdmi20_kwrap.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		won.hur (won.hur@lge.com)
 *  @version	1.0
 *  @date		2018-04-18
 *  @note		Additional information.
 */

#ifndef	_HDMI20_KWRAP_H_
#define	_HDMI20_KWRAP_H_

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef enum
{
	KWARP_HDMI20_RETURN_WRONG_DATA = -12,
	KWARP_HDMI20_RETURN_DEVICE_NOT_INIT = -11,
	KWARP_HDMI20_RETURN_DEVICE_NOT_OPEN = -10,
	KWARP_HDMI20_RETURN_DEVICE_NULL_POINTER = -9,
	KWARP_HDMI20_RETURN_WRONG_PORT = -8,
	KWARP_HDMI20_RETURN_IGNORE_MULTIPLE_OPEN = -7,
	KWARP_HDMI20_RETURN_IGNORE_MULTIPLE_INIT = -6,
} KWARP_HDMI20_RETURN_VALUE_T;

/*------------------------------------------------------------------------------
	Extern Function Prototype Declaration
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Extern Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Function Definitions
------------------------------------------------------------------------------*/
int KWARP_HDMI20_Open(void);
int KWARP_HDMI20_Close(void);
int KWARP_HDMI20_IsOpen(void);
int KWARP_HDMI20_RX_Initialize(void);
int KWARP_HDMI20_RX_HDCP14_TestMode(UINT8 mode);
int KWARP_HDMI20_RX_GetTimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pTimingInfo, int isInternalCall);
int KWARP_HDMI20_RX_GetColorDomain(UINT8 port, LX_HDMI_COLOR_STATUS_T *pColorDomain );
int KWARP_HDMI20_RX_GetAspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pAspectRatio );
int KWARP_HDMI20_RX_Set_ExecuteDscModule(UINT8 port);
int KWARP_HDMI20_RX_WriteHDCP14(UINT8 port, UINT8 *pData, int size, int isRepeater);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

