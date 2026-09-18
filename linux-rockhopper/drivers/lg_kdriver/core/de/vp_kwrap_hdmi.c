/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   COPYRIGHT(c) 1998-2010 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work covered by this copyright hereon
 *   may be reproduced, stored in a retrieval system, in any form
 *   or by any means, electronic, mechanical, photocopying, recording
 *   or otherwise, without the prior written  permission of LG Electronics.
 *****************************************************************************/


/** @file vp_hdmi_kadp.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author	won.hur (won.hur@lge.com)
 *  @version	1.0
 *  @date	2015-07-14
 *  @note	Additional information.
 *  @note	SEE TV mapping (harish.singh@lge.com)
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#define SEE_TV
#ifdef SEE_TV
#include <linux/errno.h>
#include "vp_kwrap.h"
#include "../hdmi20/hdmi20_kwarp.h"
#include "base_types.h"

#else
#include "osa_kwrap.h"
#include "debug_kwrap.h"
#include "../hdmi20/hdmi20_kwarp.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef SEE_TV
#define VP_PRINT(fmt, args...) 	{}
#define VP_ERROR(fmt, args...) 	{}
#else
#define VP_PRINT(fmt, args...) 	KWRAP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_INFO, fmt, ##args)
#define VP_ERROR(fmt, args...) 	KWRAP_LOGM_PRINT(g_vp_logm_fd, LX_LOGM_LEVEL_ERROR, fmt, ##args)
#endif
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int g_vp_logm_fd;


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int gVpHDMIDebugPrintEnable = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
#if 0	//not used
int vp_kwrap_hdmi_rx_getcolordomain(UINT8 port, LX_HDMI_COLOR_STATUS_T *pData)
{
	int ret = RET_OK;

	do{
		/* Trace */
		if(gVpHDMIDebugPrintEnable){
			VP_PRINT("%s called with port[%d]/Addr[0x%08x]", __F__, port, (UINT32)pData);
		}

		/* Check VP Initialization */
		//if(!vp_kwrap_isinitialized()){
		if(1){
			VP_ERROR("VP_KADP was not initialized\n");
			break;
		}

#ifdef INCLUDE_KDRV_HDMI20
		ret = KWARP_HDMI20_RX_GetColorDomain(port, pData);
		if(ret <0){
			VP_ERROR("Error on hdmi20_kwrap_rx_getcolordomain() = %d\n", ret);
			break;
		}
#endif

		ret = RET_OK;
	} while(0);

	return ret;
}


int vp_kwrap_hdmi_rx_getaspectratio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData)
{
	int ret = RET_ERROR;


	do{
		/* Trace */
		if(gVpHDMIDebugPrintEnable){
			VP_PRINT("%s called with port[%d]/Addr[0x%08x]", __F__, port, (UINT32)pData);
		}

		/* Check VP Initialization */
		//if(!vp_kwrap_isinitialized()){
		if(1){
			VP_ERROR("VP_KWRAP was not initialized\n");
			break;
		}

#ifdef INCLUDE_KDRV_HDMI20
		ret = KWARP_HDMI20_RX_GetAspectRatio(port, pData);
		if(ret <0){
			VP_ERROR("Error on hdmi20_kwrap_rx_getaspectratio() = %d\n", ret);
			break;
		}
#endif


		ret = RET_OK;
	} while(0);

	return ret;

}

int vp_kwrap_hdmi_rx_gettiminginfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int isFakeInfo)
{
	int ret = RET_ERROR;
	UINT16 fix_offset;

	do{
		/* Trace */
		if(gVpHDMIDebugPrintEnable){
			VP_PRINT("%s called with port[%d]/Addr[0x%08x]", __F__, port, (UINT32)pData);
		}

		/* Check VP Initialization */
		//if(!vp_kwrap_isinitialized()){
		if(1){
			VP_ERROR("VP_KADP was not initialized\n");
			break;
		}

		if(pData == NULL){
			VP_ERROR("Provided pointer is NULL[0x%08x]\n", pData);
			break;
		}

		//ret = hdmi20_kwrap_rx_gettiminginfo(port, pData, 1);
		if(ret <0){
			VP_ERROR("Error on hdmi20_kwrap_rx_gettiminginfo() = %d\n", ret);
			break;
		}

		if(isFakeInfo > 0){
			switch(pData->extInfo)
			{
				case LX_HDMI_EXT_3D_FRAMEPACK:
					if ( (pData->hActive == 640 && pData->vActive == 480) \
							|| (pData->hActive == 720 && pData->vActive == 480) \
							|| (pData->hActive == 720 && pData->vActive == 576) \
							|| (pData->hActive == 1280 && pData->vActive == 720) \
							|| (pData->hActive == 1920 && pData->vActive == 1080) )
					{
						/* Do nothing */
					}
					else if ( (pData->vActive == 2228) ||(pData->vActive == 1028) )		//1080i & 480i
					{
						pData->scanType = 0;
						pData->vActive = (pData->vActive - 68) >> 1;	//68 : 23+22+23
					}
					else if (pData->vActive == 1226)		//576i
					{
						pData->scanType = 0;
						pData->vActive = (pData->vActive - 74) >> 1;	//74 : 25+24+25
					}
					else if (pData->vActive == 1103)		// interace
					{
						/* Do nothing */
					}
					else
					{
						pData->vActive = (pData->vActive - pData->vTotal + pData->vActive) >> 1;
					}
					break;
				case LX_HDMI_EXT_3D_FIELD_ALTERNATIVE:

					if (pData->vActive == 1103)			fix_offset = 23;
					else if (pData->vActive == 601) 	fix_offset = 25;
					else if (pData->vActive == 503)		fix_offset = 23;
					else 								fix_offset = 0;
					pData->vActive = pData->vActive - fix_offset;

					break;

				case LX_HDMI_EXT_3D_LINE_ALTERNATIVE:
					pData->vTotal = pData->vTotal >> 1;
					pData->vActive = pData->vActive >> 1;
					pData->vStart = pData->vStart >> 1;
					break;
				case LX_HDMI_EXT_3D_SBSFULL:
					pData->hTotal = pData->hTotal >> 1;
					pData->hActive = pData->hActive >> 1;
					pData->hStart = pData->hStart >> 1;
					break;
				case LX_HDMI_EXT_3D_TNB:
					break;
				case LX_HDMI_EXT_3D_SBS:
					break;
				case LX_HDMI_EXT_3D_L_DEPTH:
				case LX_HDMI_EXT_3D_L_GRAPHICS:
				case LX_HDMI_EXT_2D_FORMAT:
				default :
					break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int vp_kwrap_hdmi_rx_gethdmistate(UINT8 port, LX_HDMI_STATUS_T *pData)
{
	int ret = RET_ERROR;


	do{
		/* Trace */
		if(gVpHDMIDebugPrintEnable){
			VP_PRINT("%s called with port[%d]/Addr[0x%08x]", __F__, port, (UINT32)pData);
		}

		/* Check VP Initialization */
		//if(!vp_kwrap_isinitialized()){
		if(1){
			VP_ERROR("VP_KWRAP was not initialized\n");
			break;
		}

		//ret = hdmi20_kwrap_rx_gethdmistate(port, pData);
		//if(ret <0){
		//	VP_ERROR("Error on hdmi20_kwrap_rx_gethdmistate() = %d\n", ret);
		//	break;
		//}

		ret = RET_OK;
	} while(0);

	return ret;
}
#endif

