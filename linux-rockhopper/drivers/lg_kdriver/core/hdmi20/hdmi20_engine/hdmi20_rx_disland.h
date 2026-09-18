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
 *  @date       2016-05-02
 *  @note       Additional information.
 */

#ifndef	_HDMI20_RX_DISLAND_H_
#define	_HDMI20_RX_DISLAND_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "./synopsys_api/hdmi_rx_ctrl_hdcp.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI20_MAX_DATAPACKET_SIZE 32


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	ACR = 0,
	GCP,
	ACP,
	ISRC1,
	ISRC2,
	GAMUT,
	VSI,
	AVI,
	SPD,
	AIF,
	MPEGS,
	NTSCVBI,
	AMP,
	HDR,
	H14VSI,
	HFVSI,
	DOLBYVSI,
	PACKET_MAXNUM
} HDMI20_PACKET_NAME_TYPE_T;

typedef enum
{
	HDMI20_EMPACKET_VSEMDS,	/* Vendor Specific */
	HDMI20_EMPACKET_CVTEM,	/* Compressed Video Transport */
	HDMI20_EMPACKET_HDRDM,	/* HDR Dynamic MetaData */
	HDMI20_EMPACKET_VTEM,	/* Video Timing Extended MetaData */
	HDMI20_EMPACKET_MAXNUM
} HDMI20_EMPACKET_NAME_TYPE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
/* Debug */
void HDMI20_PrintDataPacketBuffer(int type ,UINT8 port);

/* Miscelaneous control */
void HDMI20_ResetDataPacketBuffer(int type ,UINT8 port);
int HDMI20_HAL_Packet_Store(struct hdmi_rx_ctrl *ctx, UINT8 type, bool enable);

/* IOCTL Calls */
int HDMI20_HAL_Rx_Get_AVIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Get_SPDInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Get_VSIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type);
int HDMI20_HAL_Rx_Get_COLORInfo(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Get_AspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Get_DRMInfo(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall);


int HDMI20_HAL_Rx_DataPacketFilter(UINT8 port, UINT8 *dataPacket);
int HDMI20_HAL_SetCscHdrInfoToVSC(UINT8 port);

int HDMI20_HAL_Rx_IsCheckSumValid(UINT8 port, UINT8 *dataPacket);
int HDMI20_HAL_Rx_IsSpdAmdFreeSync(UINT8 *dataPacket);

int HDMI20_HAL_Get_MultipleVSIPacket(UINT8 port, LX_HDMI20_MULTIPLE_VSI_T *pData, int size);

void HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_NAME_TYPE_T type, UINT8 port);
void HDMI20_PrintEMPacketBuffer(HDMI20_EMPACKET_NAME_TYPE_T type, UINT8 port);

int HDMI20_HAL_Rx_Get_EMPInfo(UINT8 port, UINT8 *pData, LX_HDMI20_EMP_TYPE_T type, int isInternalCall);

void HDMI20_DISLAND_PROC_PrintDataPacketBuffer(int port, struct seq_file* m);
void HDMI20_DISLAND_PROC_PrintEMPacketBuffer(int port, struct seq_file* m);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

