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


/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     won.hur
 *  @version    1.0
 *  @date       2019-04-17
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_DISLAND_H_
#define	_HDMI21_RX_DISLAND_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI21_MAX_DATAPACKET_SIZE 32


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HDMI21_EMPACKET_VSEMDS,	/* Vendor Specific */
	HDMI21_EMPACKET_CVTEM,	/* Compressed Video Transport */
	HDMI21_EMPACKET_HDRDM,	/* HDR Dynamic MetaData */
	HDMI21_EMPACKET_VTEM,	/* Video Timing Extended MetaData */
	HDMI21_EMPACKET_MAXNUM
} HDMI21_EMPACKET_NAME_TYPE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
/* Debug */
void HDMI21_DISLAND_Rx_Get_PrintPktBuf(HDMI21_DISLAND_DATA_T type ,UINT8 port);
void HDMI21_DISLAND_Rx_Get_PrintEmPkttBuf(HDMI21_EMPACKET_NAME_TYPE_T type, UINT8 port);
/* For PROC */
void HDMI21_DISLAND_Rx_PROC_PrintPktBuf(int port, struct seq_file* m);
void HDMI21_DISLAND_Rx_PROC_PrintEmPkttBuf(int port, struct seq_file* m);

/* Miscelaneous control */
void HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA_T type ,UINT8 port);
void HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_NAME_TYPE_T type, UINT8 port);


/* IOCTL Calls */
int HDMI21_DISLAND_Rx_Get_AVIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int HDMI21_DISLAND_Rx_Get_SPDInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int HDMI21_DISLAND_Rx_Get_VSIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type);
int HDMI21_DISLAND_Rx_Get_COLORInfo(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall);
int HDMI21_DISLAND_Rx_Get_AspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall);
int HDMI21_DISLAND_Rx_Get_DRMInfo(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall);
int HDMI21_DISLAND_Rx_Get_MultipleVSIPacket(UINT8 port, LX_HDMI20_MULTIPLE_VSI_T *pData, int size);
int HDMI21_DISLAND_Rx_Get_EMPInfo(UINT8 port, UINT8 *pData, LX_HDMI20_EMP_TYPE_T type, int isInternalCall);
int HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(UINT8 port);

int HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSync(UINT8 *dataPacket);
int HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSyncV2(UINT8 *dataPacket);
int HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSyncV3(UINT8 *dataPacket);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

