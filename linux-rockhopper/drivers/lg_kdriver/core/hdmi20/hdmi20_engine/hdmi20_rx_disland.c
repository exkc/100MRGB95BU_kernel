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
 *  @author		won.hur
 *  @version	1.0 
 *  @date		2016-05-02
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/delay.h>

#include "hdmi20_rx_disland.h"
#include <linux/seq_file.h>
#include "hdmi20_hal_driver.h"
#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "../hdmi20_drv.h" // For debug prints

#include "os_util.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI20_SPD_AMD_FREESYNC_PACKETTYPE	0x83
#define HDMI20_SPD_AMD_FREESYNC_VERSION		0x01
#define HDMI20_SPD_AMD_FREESYNC_LENGTH		0x08
#define HDMI20_SPD_AMD_FREESYNC_OUI_PB1 	0x1A
#define HDMI20_SPD_AMD_FREESYNC_OUI_PB2 	0x00
#define HDMI20_SPD_AMD_FREESYNC_OUI_PB3 	0x00

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile HDMI20_HAL_RX_DEVICE_DATA gHDMI20RxHandler[HDMI20_NUM_OF_RX_PORTS];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI20RxDevControler[HDMI20__DEV_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
char sPacketName[hdmi_rx_ctrl_packet_cnt][PACKET_MAXNUM] =
{
	{"ACR"},
	{"GCP"},
	{"ACP"},
	{"ISRC1"},
	{"ISRC2"},
	{"GAMUT"},
	{"VSI"},
	{"AVI"},
	{"SPD"},
	{"AIF"},
	{"MPEGS"},
	{"NTSCVBI"},
	{"AMP"},
	{"HDR"},
	{"H14VSI"},
	{"HFVSI"},
	{"DOLBY VSI"}
};

int dataPacketNum[PACKET_MAXNUM] = 
{
	0x01,
	0x03,
	0x04,
	0x05,
	0x06,
	0x0A,
	0x81,
	0x82,
	0x83,
	0x84,
	0x85,
	0x86,
	0x0D,
	0x87
};


/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/

/* Tools */
static char *uint8ToBinary(UINT8 i);


/*========================================================================================
	Implementation Group
========================================================================================*/
void HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_NAME_TYPE_T type, UINT8 port)
{
	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	HDMI20_PACKET("Reset Extended Meta Packet Buffer Type[%d]/LINK[%d]\n", type, port);

	if(type >= 	HDMI20_EMPACKET_MAXNUM){
		/* Need to add for other packets */
		/* VTEM */
		memset((void *)gHDMI20RxHandler[port].emp_vtemPacket, 0,(sizeof(UINT8)*MAX_DATA_PACKET_LENGTH));
	}
	else{
		switch(type)
		{
			case HDMI20_EMPACKET_VSEMDS:
			case HDMI20_EMPACKET_CVTEM:
			case HDMI20_EMPACKET_HDRDM:
				/* Not defined Yet */
				break;
			case HDMI20_EMPACKET_VTEM:
				memset((void *)gHDMI20RxHandler[port].emp_vtemPacket, 0,(sizeof(UINT8)*MAX_DATA_PACKET_LENGTH));
				break;
			default :
				break;
		}
	}
}

void HDMI20_ResetDataPacketBuffer(int type ,UINT8 port)
{
	int i;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	HDMI20_PACKET("Reset DataPacket Buffer Type[%d]/LINK[%d]\n", type, port);
	if(type >= 	hdmi_rx_ctrl_packet_cnt){
		for(i=0;i<hdmi_rx_ctrl_packet_cnt; i++){
			memset((void *)gHDMI20RxHandler[port].dataPacket[i], 0,(sizeof(UINT8)*MAX_DATA_PACKET_LENGTH));
		}
	}
	else{
		memset((void *)gHDMI20RxHandler[port].dataPacket[type], 0,(sizeof(UINT8)*MAX_DATA_PACKET_LENGTH));
	}
}

void HDMI20_PrintDataPacketBuffer(int type ,UINT8 port)
{
	int i,y;
	int printLength = 0;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	if(type < 	hdmi_rx_ctrl_packet_cnt){
		HDMI20_DBG("Data Packet Type  =>  %s  \n", sPacketName[type]);
		for(i=0;i<3;i++){
			HDMI20_DBG("[HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI20RxHandler[port].dataPacket[type][i]), (UINT8)gHDMI20RxHandler[port].dataPacket[type][i]);
		}

		printLength = MAX_DATA_PACKET_LENGTH;

		for(i=4;i<printLength; i++){
			HDMI20_DBG("[ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-4), uint8ToBinary((UINT8)gHDMI20RxHandler[port].dataPacket[type][i]) ,(UINT8)gHDMI20RxHandler[port].dataPacket[type][i]);
		}
	}
	else {
		for(y=0; y<hdmi_rx_ctrl_packet_cnt; y++){
			HDMI20_DBG("Data Packet y  =>  %s  \n", sPacketName[y]);
			for(i=0;i<3;i++){
				HDMI20_DBG("[HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI20RxHandler[port].dataPacket[y][i]) ,(UINT8)gHDMI20RxHandler[port].dataPacket[y][i]);
			}

			/* Overflow protection : Length does not include checksum space */
			printLength = gHDMI20RxHandler[port].dataPacket[y][2] + 5;

			if(printLength >= MAX_DATA_PACKET_LENGTH){
				printLength = MAX_DATA_PACKET_LENGTH;
			}

			for(i=4;i<printLength; i++){
				HDMI20_DBG("[ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-4), uint8ToBinary( (UINT8)gHDMI20RxHandler[port].dataPacket[y][i] ) ,(UINT8)gHDMI20RxHandler[port].dataPacket[y][i]);
			}
		}
	}

}

void HDMI20_PrintEMPacketBuffer(HDMI20_EMPACKET_NAME_TYPE_T type, UINT8 port)
{
	int i;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Need to add for other packets */
	
	/* VTEM */
	if(type ==  HDMI20_EMPACKET_VTEM){
		HDMI20_DBG("Data Packet Type  =>  %s  \n", "EMP VTEM");
		for(i=0;i<3;i++){
			HDMI20_DBG("[HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]), (UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]);
		}

		for(i=4;i<MAX_DATA_PACKET_LENGTH; i++){
			HDMI20_DBG("[ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-4), uint8ToBinary((UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]) ,(UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]);
		}
	}
}


int HDMI20_HAL_Packet_Store(struct hdmi_rx_ctrl *ctx, UINT8 type, bool enable)
{
	int error = 0;

	if (ctx == 0)
	{
		return -EINVAL;
	}
	switch (type)
	{
		case 0x01:
			//HDMI20_PACKET("Port %d : Packet Type ACR[0x%x]  En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_ACR, enable);
			break;
		case 0x03:
			//HDMI20_PACKET("Port %d : Packet Type GCP[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_GCP, enable);
			break;
		case 0x04:
			//HDMI20_PACKET("Port %d : Packet Type ACP[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_ACP, enable);
			break;
		case 0x05:
			//HDMI20_PACKET("Port %d : Packet Type ISRC1[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_ISRC1, enable);
			break;
		case 0x06:
			//HDMI20_PACKET("Port %d :Packet Type ISRC2[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_ISRC2, enable);
			break;
		case 0x0D:
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_AMP, enable);
			break;
		case 0x0A:
			//HDMI20_PACKET("Port %d : Packet Type GAMUT[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_GAMUT, enable);
			break;
		case 0x81:
			//HDMI20_PACKET("Port %d : Packet Type VSI[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_VSI, enable);
			break;
		case 0x82:
			//HDMI20_PACKET("Port %d : Packet Type AVI[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_AVI, enable);
			break;
		case 0x83:
			//HDMI20_PACKET("Port %d : Packet Type SPD[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_SPD, enable);
			break;
		case 0x84:
			//HDMI20_PACKET("Port %d : Packet Type AIF[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_AIF, enable);
			break;
		case 0x85:
			//HDMI20_PACKET("Port %d : Packet Type MPEGS[0x%x] En[%d]\n", ctx->device_id, type, enable);
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_MPEGS, enable);
			break;
		case 0x86:
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_NTSCVBI, enable);
			break;
		case 0x87:
			error |= hdmi_rx_ctrl_store(ctx, hdmi_rx_ctrl_packet_HDR, enable);
			break;
		default:
			error = -EINVAL;
			break;
	}
	return error;
}

/* IOCTL */
int HDMI20_HAL_Rx_Get_DRMInfo(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI20_RX_DRM_PACKET_T userdata;
	static UINT8 pre_data[HDMI20_NUM_OF_RX_PORTS] = {0,};
	UINT32 cur_data, dbg_value;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_RX_DRM_PACKET_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_RX_DRM_PACKET_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI20_RX_DRM_PACKET_T));


		/* Step 2. Copy data */
		userdata.nVersion	= gHDMI20RxHandler[port].dataPacket[HDR][1];
		userdata.nLength	= gHDMI20RxHandler[port].dataPacket[HDR][2];

		memcpy((void *)&userdata.metaData[0], (void *)&gHDMI20RxHandler[port].dataPacket[HDR][0], MAX_DATA_PACKET_LENGTH);

		/* DBG : Force DRM Data */
		if(gHDMI20RxDevControler[HDMI20__FORCE_HDR10_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI20RxDevControler[HDMI20__FORCE_HDR10_SAMPLE_PACKET].value;
			if (dbg_value==0x3||dbg_value==0x103)
			{
				userdata.nVersion = 0x01; 
				userdata.nLength = 0x1a;
				userdata.metaData[0] = 0x87;
				userdata.metaData[5] = 0x03;	// eEOTFType(HLG)
				userdata.metaData[6] = 0x00;	// eMeta_Desc
			}
			else if (dbg_value==0x2||dbg_value==0x102)
			{
				userdata.nVersion = 0x01;
				userdata.nLength = 0x1a;
				userdata.metaData[0] = 0x87;
				userdata.metaData[5] = 0x02;	// eEOTFType(HDR10)
				userdata.metaData[6] = 0x00;	// eMeta_Desc
			}
			else if (dbg_value==0x1||dbg_value==0x101)
			{
				userdata.nVersion = 0x01; 
				userdata.nLength = 0x1a;
				userdata.metaData[0] = 0x00;
				userdata.metaData[5] = 0x00;	// eEOTFType
				userdata.metaData[6] = 0x00;	// eMeta_Desc
			}
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI20_RX_DRM_PACKET_T *)pData, &userdata, sizeof(LX_HDMI20_RX_DRM_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI20_RX_DRM_PACKET_T *)pData, &userdata, sizeof(LX_HDMI20_RX_DRM_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketName[HDR], port);
				break;
			}
		}

		cur_data = userdata.metaData[24]<<12|userdata.metaData[23]<<4|userdata.metaData[5];
		if (pre_data[port] != cur_data)
		{
			HDMI20_LINK_PACKET("[%d] 0x%08x <- [0]0x%08x [1]0x%08x [2]0x%08x [3]0x%08x\n", \
				port, cur_data, pre_data[0], pre_data[1], pre_data[2], pre_data[3]);
			pre_data[port] = cur_data;
		}
		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI20_HAL_Rx_Get_AVIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_INFO_PACKET_T userdata;
	UINT32 video_format;
	UINT32 dbg_value = 0;
	UINT8 diff_data = 0;
	UINT8 origin_data;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_INFO_PACKET_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_INFO_PACKET_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_INFO_PACKET_T));

		/* Step 1-1. Preset */
		video_format = gHDMI20RxHandler[port].ctrl.bsp_read(0x3A4);
		video_format = (video_format & 0x60); 
		diff_data = (UINT8)video_format;

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1221){
			HDMI20_DBG("DBG %d : video_format[0x%x]diffdata[0x%x]\n", port, video_format, diff_data);
		}

		/* Defence Code : If length is 0, clear Data */
		if((gHDMI20RxHandler[port].dataPacket[AVI][2] == 0)||(gHDMI20RxHandler[port].dataPacket[AVI][2] > 0x20)){
			memset((void *)&userdata.dataBytes, 0, MAX_DATA_PACKET_LENGTH - 4);
		}

		/* AVI CSC information restore based on HW detected value : Defence code based on NO AVI information detected on PDEC FIFO*/
		if(diff_data != 0){
			origin_data = gHDMI20RxHandler[port].dataPacket[AVI][5];
			origin_data &= (~0x60); 
			origin_data |= diff_data;

			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1221){
				HDMI20_DBG("DBG %d : hw_data[0x%x], packet[5d][0x%x]\n", port, diff_data, gHDMI20RxHandler[port].dataPacket[AVI][5]);
			}		

			gHDMI20RxHandler[port].dataPacket[AVI][5] = origin_data;
		}

		/* 2016/06/20 : Clear CSC value if DVI is detected */
		if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
			gHDMI20RxHandler[port].dataPacket[AVI][5] = 0;
		}

		/* Step 2. Copy data */
		userdata.InfoFrameType = 0x82;
		memcpy((void *)&userdata.header, (void *)&gHDMI20RxHandler[port].dataPacket[AVI][1], 2);
		memcpy((void *)&userdata.dataBytes, (void *)&gHDMI20RxHandler[port].dataPacket[AVI][4], MAX_DATA_PACKET_LENGTH - 4);

		/* Notice : WEBOS & Pioneer gets DVI/HDMI information through this 7th bytes of AVI info frame...
		 *          This is not a standard in the specification.
		 *          Only LGE way... Do not know the history of this.. But i think the one who first did this
		 *          was a lazy guy and did not want a new IOCTL command for this..*/
		if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
			userdata.dataBytes[7] &= 0xFE;
		}
		else{
			userdata.dataBytes[7] |= 0x01;
		}

		/* DBG : Force COLOR Data */
		if(gHDMI20RxDevControler[HDMI20__FORCE_COLOR_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI20RxDevControler[HDMI20__FORCE_COLOR_SAMPLE_PACKET].value;
			if (dbg_value==0x1){/*C1C0:eColorimetry*//*EC2EC1EC0:eExtColorimetry*/
				userdata.dataBytes[0] = (userdata.dataBytes[0] & ~(0x3<<22)) | (LX_HDMI_AVI_COLORIMETRY_ITU601<<22);
				userdata.dataBytes[0] = (userdata.dataBytes[0] & ~(0x7<<28)) | (LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC601<<28);
			}
			else if (dbg_value==0x2){/*C1C0:eColorimetry*//*EC2EC1EC0:eExtColorimetry*/
				userdata.dataBytes[0] = (userdata.dataBytes[0] & ~(0x3<<22)) | (LX_HDMI_AVI_COLORIMETRY_ITU709<<22);
				userdata.dataBytes[0] = (userdata.dataBytes[0] & ~(0x7<<28)) | (LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC709<<28);
			}
			else if (dbg_value==0x3){/*C1C0:eColorimetry*//*EC2EC1EC0:eExtColorimetry*/
				userdata.dataBytes[0] = (userdata.dataBytes[0] & ~(0x3<<22)) | (LX_HDMI_AVI_COLORIMETRY_EXTEND<<22);
				userdata.dataBytes[0] = (userdata.dataBytes[0] & ~(0x7<<28)) | (LX_HDMI_AVI_EXT_COLORIMETRY_BT2020NCL<<28);
			}
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketName[AVI], port);
				break;
			}
		}
		ret = RET_OK;
	} while(0);

	return ret;
}


/* IOCTL */
int HDMI20_HAL_Rx_Get_SPDInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_INFO_PACKET_T userdata;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_INFO_PACKET_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_INFO_PACKET_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_INFO_PACKET_T));

		/* Step 2. Copy data */
		userdata.InfoFrameType = 0x83;
		memcpy((void *)&userdata.header, (void *)&gHDMI20RxHandler[port].dataPacket[SPD][1], 2);
		memcpy((void *)&userdata.dataBytes, (void *)&gHDMI20RxHandler[port].dataPacket[SPD][4], MAX_DATA_PACKET_LENGTH - 4);

		/* Defence Code : If length is 0, clear Data */
		if((gHDMI20RxHandler[port].dataPacket[SPD][2] == 0)||(gHDMI20RxHandler[port].dataPacket[SPD][2] > 0x20)){
			memset((void *)&userdata.dataBytes, 0, MAX_DATA_PACKET_LENGTH - 4);
		}


		if(isInternalCall > 0){
			memcpy((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketName[SPD], port);
				break;
			}
		}
		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI20_HAL_Rx_Get_VSIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type)
{
	int ret = RET_ERROR;
	LX_HDMI_INFO_PACKET_T userdata;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_INFO_PACKET_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_INFO_PACKET_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_INFO_PACKET_T));

		/* Step 2. Copy data */
		userdata.InfoFrameType = 0x81;
		memcpy((void *)&userdata.header, (void *)&gHDMI20RxHandler[port].dataPacket[VSI][1], 2);
		memcpy((void *)&userdata.dataBytes, (void *)&gHDMI20RxHandler[port].dataPacket[VSI][4], MAX_DATA_PACKET_LENGTH - 4);

		/* Defence Code : If length is 0, clear Data */
		if((gHDMI20RxHandler[port].dataPacket[VSI][2] == 0)||(gHDMI20RxHandler[port].dataPacket[VSI][2] > 0x20)){
			memset((void *)&userdata.dataBytes, 0, MAX_DATA_PACKET_LENGTH - 4);
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketName[VSI], port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI20_HAL_Get_MultipleVSIPacket(UINT8 port, LX_HDMI20_MULTIPLE_VSI_T *pData, int size)
{
	int ret = RET_ERROR;
	LX_HDMI20_MULTIPLE_VSI_T userdata;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_MULTIPLE_VSI_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_MULTIPLE_VSI_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI20_MULTIPLE_VSI_T));


		/* Step 2. Copy data */
		/* Till full implementation, only send VSI H14B */
		userdata.numberOfVSI = 1;
		userdata.packet[0].type = 0x81;
		userdata.packet[0].version = gHDMI20RxHandler[port].dataPacket[VSI][1];
		userdata.packet[0].length = gHDMI20RxHandler[port].dataPacket[VSI][2];
		memcpy((void *)&userdata.packet[0].dataBytes, (void *)&gHDMI20RxHandler[port].dataPacket[VSI][4], MAX_DATA_PACKET_LENGTH - 4);

		/* Step x. Copy to User */
		ret = copy_to_user((LX_HDMI20_MULTIPLE_VSI_T *)pData, &userdata, sizeof(LX_HDMI20_MULTIPLE_VSI_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for HDMI MISC data on Port[%d].\n", port);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}



/* IOCTL */
int HDMI20_HAL_Rx_Get_COLORInfo(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_COLOR_DOMAIN_T data;
	UINT32 video_format;
	UINT32 dbg_value = 0;

	do{
		/* Not used */
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_COLOR_DOMAIN_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_COLOR_DOMAIN_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Reset memory */
		memset((void *)&data , 0 , sizeof(LX_HDMI_COLOR_DOMAIN_T));

		if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
			data.bHdmiMode = 0;
		}
		else{
			data.bHdmiMode = 1;
		}
		
		video_format = gHDMI20RxHandler[port].ctrl.bsp_read(0x3A4);
		video_format = (video_format & 0x60); video_format = video_format>>5;
		video_format = video_format & 0x3;

		if(video_format == 0){
			data.ePixelEncoding = (UINT16)((gHDMI20RxHandler[port].dataPacket[AVI][5]&0x60)>>5);
		}
		else{
			data.ePixelEncoding = (UINT16)(video_format);
		}

		HDMI20_HAL_Rx_SetLocalVideoMuteColor(port,  data.ePixelEncoding);

		data.eColorimetry = (UINT16)gHDMI20RxHandler[port].timing_info.colorimetry;
		data.eExtColorimetry = (UINT16)gHDMI20RxHandler[port].timing_info.ext_colorimetry;
		data.eITContent = (UINT16)gHDMI20RxHandler[port].timing_info.it_content;
		data.eRGBQuantizationRange = (UINT16)gHDMI20RxHandler[port].timing_info.rgb_quant_range;

		/* DBG : Force COLOR Data */
		if(gHDMI20RxDevControler[HDMI20__FORCE_COLOR_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI20RxDevControler[HDMI20__FORCE_COLOR_SAMPLE_PACKET].value;
			if (dbg_value==0x1){
				data.eColorimetry = LX_HDMI_AVI_COLORIMETRY_ITU601;
				data.eExtColorimetry = LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC601;
			}
			else if (dbg_value==0x2){
				data.eColorimetry = LX_HDMI_AVI_COLORIMETRY_ITU709;
				data.eExtColorimetry = LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC709;
			}
			else if (dbg_value==0x3){
				data.eColorimetry = LX_HDMI_AVI_COLORIMETRY_EXTEND;
				data.eExtColorimetry = LX_HDMI_AVI_EXT_COLORIMETRY_BT2020NCL;
			}
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI_COLOR_DOMAIN_T *)pData, &data, sizeof(LX_HDMI_COLOR_DOMAIN_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_COLOR_DOMAIN_T *)pData, &data, sizeof(LX_HDMI_COLOR_DOMAIN_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", __F__, port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;

}

/* IOCTL */
int HDMI20_HAL_Rx_Get_EMPInfo(UINT8 port, UINT8 *pData, LX_HDMI20_EMP_TYPE_T type, int isInternalCall)
{
	int ret = RET_ERROR;
	UINT8 userdata[31] = {0,};

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(type >= LX_HDMI20_EMP_MAXNUM){
			HDMI20_ERROR("Error! Unknown Type[%d]]n", type);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, 31);

		/* Step 2. Copy data */
		if(type == LX_HDMI20_EMP_VTEM){
			memcpy((void *)&userdata[0], (void *)&gHDMI20RxHandler[port].emp_vtemPacket[0], 3);
			memcpy((void *)&userdata[3], (void *)&gHDMI20RxHandler[port].emp_vtemPacket[4], 28);
		}
		else{
			/* Not Implemented Yet */
		}

		if(isInternalCall) {
			memcpy((void *)pData, (void *)&userdata, 31 * sizeof(UINT8));
		}
		else{
			ret = copy_to_user((void *)pData, (void *)&userdata, 31 * sizeof(UINT8));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "EMP", port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI20_HAL_Rx_Get_AspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_ASPECTRATIO_T data;


	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_ASPECTRATIO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_ASPECTRATIO_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Reset memory */
		memset((void *)&data , 0 , sizeof(LX_HDMI_ASPECTRATIO_T));

		data.eAspectRatio = (UINT16)gHDMI20RxHandler[port].timing_info.picture_ratio;

		if(isInternalCall > 0){
			memcpy((LX_HDMI_ASPECTRATIO_T *)pData, &data, sizeof(LX_HDMI_ASPECTRATIO_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_ASPECTRATIO_T *)pData, &data, sizeof(LX_HDMI_ASPECTRATIO_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", __F__, port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;

}

int HDMI20_HAL_Rx_DataPacketFilter(UINT8 port, UINT8 *dataPacket)
{
	int ret = RET_OK; 
	UINT8 data[HDMI20_MAX_DATAPACKET_SIZE] = {0};
	UINT8 vsiPacketHeader[3];
	UINT32 vsiHWPacketHeader;

	do{
		/* Check Port */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Get Data */
		memcpy((UINT8 *)&data, (UINT8 *)dataPacket, HDMI20_MAX_DATAPACKET_SIZE);


		/* As from HDMI Datapacket spec, only Infoframes of Data packet have Checksums */
		if(gHDMI20RxDevControler[HDMI20__DATAPACKET_USE_CHSUM_FILTER].value >= 2){
			if((data[0]<0x87) && (data[0] > 0x80)) { // 0x80 higher is InfoFrame of DataPackets, but do not check for HDR10
				if(HDMI20_HAL_Rx_IsCheckSumValid(port, dataPacket) == RET_ERROR){
					ret = RET_ERROR;
					break;
				}
			}
		}
		else if(gHDMI20RxDevControler[HDMI20__DATAPACKET_USE_CHSUM_FILTER].value > 0){
			if(data[0] > 0x80) { // 0x80 higher is InfoFrame of DataPackets
				if(HDMI20_HAL_Rx_IsCheckSumValid(port, dataPacket) == RET_ERROR){
					ret = RET_ERROR;
					break;
				}
			}
		}

		/* Check Specific conditions */
		switch (data[0])
		{
			case AVI:
				{
					if((data[2] == 0) || (data[2] > 0x20)){
						/* Discard weird AVI data packet */
						ret = RET_ERROR;
					}

				}
				break;
			case VSI:
				{
					if(gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value >0){
						vsiHWPacketHeader = gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_CTRL_VSI_ST0);

						vsiPacketHeader[0] = (UINT8)(vsiHWPacketHeader & 0x000000FF);
						vsiPacketHeader[1] = (UINT8)((vsiHWPacketHeader & 0x0000FF00) >> 8);
						vsiPacketHeader[2] = (UINT8)((vsiHWPacketHeader & 0x00FF0000) >> 16);
					}
					else{
						vsiPacketHeader[0] = data[5];
						vsiPacketHeader[1] = data[6];
						vsiPacketHeader[2] = data[7];
					}

					/* 1st filter */
					if((vsiPacketHeader[0] != 0x03) || (vsiPacketHeader[1] != 0x0C) || (vsiPacketHeader[2] != 0x00)) {
						if((vsiPacketHeader[0] != 0x46) || (vsiPacketHeader[1] != 0xD0) || (vsiPacketHeader[2] != 0x00)){
							if((vsiPacketHeader[0] != 0xD8) || (vsiPacketHeader[1] != 0x5D) || (vsiPacketHeader[2] != 0xC4)){
								ret = RET_ERROR;
							}
						}
					}
				}
				break;
			default:
				break;
		}


	} while(0);


	return ret;
}

int HDMI20_HAL_SetCscHdrInfoToVSC(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 data = 0;
	UINT32 dbg_value = 0;
	static UINT32 pre_data[HDMI20_NUM_OF_RX_PORTS] = {0,};

	do{
		/* Check Port */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* 20170124, color domain data -> max_display_mastering_luminance */
		#if 0
		data = (UINT32)((gHDMI20RxHandler[port].dataPacket[AVI][5]&0x60)>>5);
		data = data & 0x3;
		data = data <<4;
		#else
		data = (UINT32)((gHDMI20RxHandler[port].dataPacket[HDR][24]<<8)|gHDMI20RxHandler[port].dataPacket[HDR][23]);
		data = (!data)? 1:((data-1)/1000+1);
		if (data>0xF)	data=0xF;
		data = data <<4;
		#endif

		data &= (0xFFFFFFF0);
		data |= (UINT32)((gHDMI20RxHandler[port].dataPacket[HDR][5] & 0x0F));

		/* DBG : Force DRM Data */
		if(gHDMI20RxDevControler[HDMI20__FORCE_HDR10_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI20RxDevControler[HDMI20__FORCE_HDR10_SAMPLE_PACKET].value;
			switch (dbg_value)
			{
				case 0x11:	data = 0x00;	break;//SDR
				case 0x12:	data = 0x42;	break;//HDR10 3001~4000nit
				case 0x13:	data = 0xa2;	break;//HDR10 9001~10000nit
				case 0x14:	data = 0x13;	break;//HLG
				case 0x101:	data = 0x00;	break;//SDR
				case 0x102:	data = 0x42;	break;//HDR10 3001~4000nit
				case 0x103:	data = 0x13;	break;//HLG
				default:	break;
			}
		}

		//data |= 0x00000080;
		gHDMI20RxHandler[port].ctrl.bsp_write(0x1f40, data);

		if (pre_data[port] != data)
		{
			HDMI20_LINK_PACKET("[%d] 0x%08x <- [0]0x%08x [1]0x%08x [2]0x%08x [3]0x%08x\n", \
				port, data, pre_data[0], pre_data[1], pre_data[2], pre_data[3]);
			pre_data[port] = data;
		}
		ret = RET_OK;
	}while(0);

	return ret;
}

/* Static function for calualtion */
static char *uint8ToBinary(UINT8 i)
{
	static char s[ 8 + 1 ] = {'0', };
	int count = 8;

	do{
		s[--count] = '0' + (char)( i & 1 );
		i = i >> 1;
	} while(count);

	return s;
}

int HDMI20_HAL_Rx_IsCheckSumValid(UINT8 port, UINT8 *dataPacket)
{
	int ret = RET_ERROR; 
	UINT8 data[HDMI20_MAX_DATAPACKET_SIZE] = {0};
	UINT8 result = 0;
	int printlength = 0;
	int i;

	do{
		/* Check Port */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Get Data */
		memcpy((UINT8 *)&data, (UINT8 *)dataPacket, HDMI20_MAX_DATAPACKET_SIZE);

		printlength = data[2] + 5;

		for(i=0;i<3;i++){
			result += data[i];
		}

		for(i=4;i<printlength;i++) {
			result += data[i];
		}

		if(result == 0x0) ret = RET_OK;
		else {
			if((gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1124)||(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1125)){
				HDMI20_DBG("DBG %d : Detected Check Sum Error for Packet Type[0x%02x] of Checksum[0x%02x]\n", port, data[0], result);
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1124){
					for(i=0;i<3;i++){
						HDMI20_DBG("[HB%02d] - [  0x%02x  ]\n",i, (UINT8)data[i]);
					}

					for(i=4;i<printlength; i++){
						HDMI20_DBG("[ B%02d] - [  0x%02x  ]\n",(i-4), (UINT8)data[i]);
					}

				}
			}
			ret = RET_ERROR;
		}
	} while(0);

	return ret;
}

int HDMI20_HAL_Rx_IsSpdAmdFreeSync(UINT8 *dataPacket)
{
	int ret = RET_ERROR; 
	UINT8 data[HDMI20_MAX_DATAPACKET_SIZE] = {0};

	do{
		/* Check Port */
		if(dataPacket == NULL){
			HDMI20_ERROR("Error! Null Pointer access]n");
			break;
		}

		/* Get Data */
		memcpy((UINT8 *)&data, (UINT8 *)dataPacket, HDMI20_MAX_DATAPACKET_SIZE);

		if(data[0] != HDMI20_SPD_AMD_FREESYNC_PACKETTYPE) break;
		if(data[1] != HDMI20_SPD_AMD_FREESYNC_VERSION) break;
		if(data[2] != HDMI20_SPD_AMD_FREESYNC_LENGTH) break;
		if(data[5] != HDMI20_SPD_AMD_FREESYNC_OUI_PB1) break;
		if(data[6] != HDMI20_SPD_AMD_FREESYNC_OUI_PB2) break;
		if(data[7] != HDMI20_SPD_AMD_FREESYNC_OUI_PB3) break;
		
		ret = RET_OK;

	} while(0);

	return ret;
}


void HDMI20_DISLAND_PROC_PrintDataPacketBuffer(int port, struct seq_file* m)
{
	int i,y;
	int printLength = 0;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	for(y=0; y<hdmi_rx_ctrl_packet_cnt; y++){
		seq_printf(m, "Data Packet y  =>  %s  \n", sPacketName[y]);
		for(i=0;i<3;i++){
			seq_printf(m, "[HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI20RxHandler[port].dataPacket[y][i]) ,(UINT8)gHDMI20RxHandler[port].dataPacket[y][i]);
		}

		/* Overflow protection : Length does not include checksum space */
		printLength = gHDMI20RxHandler[port].dataPacket[y][2] + 5;

		if(printLength >= MAX_DATA_PACKET_LENGTH){
			printLength = MAX_DATA_PACKET_LENGTH;
		}

		for(i=4;i<printLength; i++){
			seq_printf(m, "[ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-4), uint8ToBinary( (UINT8)gHDMI20RxHandler[port].dataPacket[y][i] ) ,(UINT8)gHDMI20RxHandler[port].dataPacket[y][i]);
		}
	}

}

void HDMI20_DISLAND_PROC_PrintEMPacketBuffer(int port, struct seq_file* m)
{
	int i;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Need to add for other packets */

	/* VTEM */
	seq_printf(m, "Data Packet Type  =>  %s  \n", "EMP VTEM");
	for(i=0;i<3;i++){
		seq_printf(m, "[HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]), (UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]);
	}

	for(i=4;i<MAX_DATA_PACKET_LENGTH; i++){
		seq_printf(m, "[ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-4), uint8ToBinary((UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]) ,(UINT8)gHDMI20RxHandler[port].emp_vtemPacket[i]);
	}
}

