/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   COPYRIGHT(c) 1998-2010 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work covered by this copyright hereon
 *   may be reproduced, stored in a retrieval system, in any form
 *   or by any means, electronic, mechanical, photocopying, recording
 *   or otherwise, without the prior written  permission of LG Electronics.
 *****************************************************************************/

/** @file vp_hdmi20_kadp.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		won.hur (won.hur@lge.com)
 *  @version	1.0
 *  @date		2015-07-15
 *  @note		Additional information.
  * @note		SEE TV mapping (harish.singh@lge.com)
 */

#ifndef	_VP_HDMI_KWRAP_H_
#define	_VP_HDMI_KWRAP_H_

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/

#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/
#define USE_VP_HDMI_API

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Extern Function Prototype Declaration
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Extern Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Function Definitions
------------------------------------------------------------------------------*/
#if 0	//not used
int vp_kwrap_hdmi_rx_getcolordomain(UINT8 port, LX_HDMI_COLOR_STATUS_T *pData);
int vp_kwrap_hdmi_rx_getaspectratio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData);
int vp_kwrap_hdmi_rx_gettiminginfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int isFakeInfo);
int vp_kwrap_hdmi_rx_gethdmistate(UINT8 port, LX_HDMI_STATUS_T *pData);
#endif

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

