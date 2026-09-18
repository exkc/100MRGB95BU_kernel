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
 *  @date		2019-04-17
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi21_hal_driver.h"
#include "hdmi21_rx_disland.h"
#include "hdmi21_rx_snps_pdec.h"
#include <linux/seq_file.h>
#include "../hdmi20_drv.h" // For debug prints

#include "os_util.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI21_SPD_AMD_FREESYNC_PACKETTYPE	0x83
#define HDMI21_SPD_AMD_FREESYNC_VERSION		0x01
#define HDMI21_SPD_AMD_FREESYNC_VERSION2	0x02
#define HDMI21_SPD_AMD_FREESYNC_VERSION3	0x03
#define HDMI21_SPD_AMD_FREESYNC_LENGTH		0x08
#define HDMI21_SPD_AMD_FREESYNC_LENGTH_V2	0x09 /* AMD said this would be 0x9 rather that whats in the spec(0xA) */
#define HDMI21_SPD_AMD_FREESYNC_LENGTH_V2_1 0x0A /* FreeSync V2 spec */
#define HDMI21_SPD_AMD_FREESYNC_LENGTH_V3	0x1B /* FreeSync V3 spec */
#define HDMI21_SPD_AMD_FREESYNC_OUI_PB1 	0x1A
#define HDMI21_SPD_AMD_FREESYNC_OUI_PB2 	0x00
#define HDMI21_SPD_AMD_FREESYNC_OUI_PB3 	0x00

#define HDMI21_PACKET_NAME_SIZE		10	
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
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

/* Number of Max operable ports */
extern int		g_hdmi20_number_of_ports;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
char sPacketNameHDMI21[HDMI21_DISLAND_DATA_MAXNUM][HDMI21_PACKET_NAME_SIZE] =
{
	{"ACR"},
	{"GCP"},
	{"ACP"},
	{"ISRC1"},
	{"ISRC2"},
	{"GAMUT"},
	{"AMD"},
	{"VSI"},
	{"AVI"},
	{"SPD"},
	{"AIF"},
	{"NTSCVBI"},
	{"DRM"},
	{"GEN0"},
	{"GEN1"},
	{"EMD"},
	{"VSI H14"},
	{"VSI HF"},
	{"VSI DOLBY"},
	{"VSI DOVI"} /* 2020/08/21 : VSI Dolby & H14 */
};

int dataPacketNumHDMI21[HDMI21_DISLAND_DATA_MAXNUM] = 
{
	0x01,
	0x03,
	0x04,
	0x05,
	0x06,
	0x0A,
	0x0D,
	0x81,
	0x82,
	0x83,
	0x84,
	0x86,
	0x87,
	0x00,
	0x00,
	0x7F
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
void HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_NAME_TYPE_T type, UINT8 port)
{
	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	if(type >= 	HDMI21_EMPACKET_MAXNUM){
		HDMI21_LINE_DBG(145, "DBG[%d] : Reset Extended Meta Packet Buffer Type[ALL]/LINK\n", port);

		/* Need to add for other packets */
		/* VTEM */
		memset((void *)gHDMI21RxHandler[port].emp_vtemPacket, 0,(sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH));
		memset((void *)gHDMI21RxHandler[port].emp_cvtemPacket, 0,(sizeof(UINT8)*HDMI21_MAX_CVTEM_LENGHT));
	}
	else{
		HDMI21_LINE_DBG(145,"DBG[%d] : Reset Extended Meta Packet Buffer Type[%d]\n", port, type);

		switch(type)
		{
			case HDMI21_EMPACKET_CVTEM:
				memset((void *)gHDMI21RxHandler[port].emp_cvtemPacket, 0,(sizeof(UINT8)*HDMI21_MAX_CVTEM_LENGHT));
				break;
			case HDMI21_EMPACKET_VSEMDS:
			case HDMI21_EMPACKET_HDRDM:
				/* Not defined Yet */
				break;
			case HDMI21_EMPACKET_VTEM:
				memset((void *)gHDMI21RxHandler[port].emp_vtemPacket, 0,(sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH));
				break;
			default :
				break;
		}
	}
}

/* 2020/01/03 won.hur : Check what does what 
 *   원래 값 : E13813
 *    
 *     Default of PKT0 : E13813
 *     PKT2            : 813E00
 *               
 *                   
 *     E13813 :   1110 0001 0011 1000 0001 0011
 *     813E00 :   1000 0001 0011 1110 0000 0000
 *
 *
 *     PKT0   :   0110 0000 0000 0000 0001 0011
 *
 *                           
 *     [아직 켜 있는것]
 *     22 : CVTEM
 *     21 : EMD
 *     4  : GCP
 *     1  : ACR N
 *     0  : ACR CTS
 *
 *
 *     [PKT 2에서 하는것]
 *     23 : VTEM
 *     16 : DRM
 *     13 : Audio IF
 *     12 : SPD
 *     11 : AVI
 *     10 : VSI
 *     9  : Audio IF
 */
void HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA_T type ,UINT8 port)
{
	int i;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	if(type >= 	HDMI21_DISLAND_DATA_MAXNUM){
		HDMI21_LINE_DBG(145, "DBG[%d] : Reset DataPacket Buffer Type[ALL]\n",port);

		for(i=0;i<HDMI21_DISLAND_DATA_MAXNUM; i++){
			memset((void *)gHDMI21RxHandler[port].dataPacket[i], 0,(sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH));
			/* only for whats left in PKT0 */
			if((i == HDMI21_DISLAND_DATA__ACR)||(i == HDMI21_DISLAND_DATA__GCP)) {
				HDMI21_PDEC_Rx_Set_StorePktToHander(&gHDMI21RxHandler[port],  i);
			}

		}
		/* SJ Youm */
		HDMI21_HAL_Rx_Set_PqeHdrInfo(&gHDMI21RxHandler[port], 0, 1);
	}
	else{
		HDMI21_LINE_DBG(145, "DBG[%d] : Reset DataPacket Buffer Type[%s]\n",port, sPacketNameHDMI21[type]);

		memset((void *)gHDMI21RxHandler[port].dataPacket[type], 0,(sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH));

		/* only for whats left in PKT0 */
		if((type == HDMI21_DISLAND_DATA__ACR)||(type == HDMI21_DISLAND_DATA__GCP)) {
			HDMI21_PDEC_Rx_Set_StorePktToHander(&gHDMI21RxHandler[port],  type);
		}

		if(type == HDMI21_DISLAND_DATA__DRM){	
			/* SJ Youm */
			HDMI21_HAL_Rx_Set_PqeHdrInfo(&gHDMI21RxHandler[port], 0, 1);
		}
	}
}

void HDMI21_DISLAND_Rx_Get_PrintPktBuf(HDMI21_DISLAND_DATA_T type ,UINT8 port)
{
	int i,y;
	int printLength = 0;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	if(type < HDMI21_DISLAND_DATA_MAXNUM){
		HDMI20_DBG("Data Packet Type  =>  %s  \n", sPacketNameHDMI21[type]);
		for(i=0;i<3;i++){
			HDMI20_DBG("[%s][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", sPacketNameHDMI21[type], i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].dataPacket[type][i]), (UINT8)gHDMI21RxHandler[port].dataPacket[type][i]);
		}

		printLength = HDMI21_MAX_DATA_PACKET_LENGTH;

		for(i=3;i<printLength; i++){
			HDMI20_DBG("[%s][ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", sPacketNameHDMI21[type], (i-3), uint8ToBinary((UINT8)gHDMI21RxHandler[port].dataPacket[type][i]) ,(UINT8)gHDMI21RxHandler[port].dataPacket[type][i]);
		}
	}
	else {
		for(y=0; y<HDMI21_DISLAND_DATA_MAXNUM; y++){
			HDMI20_DBG("Data Packet y  =>  %s  \n", sPacketNameHDMI21[y]);
			for(i=0;i<3;i++){
				HDMI20_DBG("[%s][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", sPacketNameHDMI21[type], i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].dataPacket[y][i]) ,(UINT8)gHDMI21RxHandler[port].dataPacket[y][i]);
			}

			/* Overflow protection : Length does not include checksum space */
			printLength = gHDMI21RxHandler[port].dataPacket[y][2] + 5;

			if(printLength >= HDMI21_MAX_DATA_PACKET_LENGTH){
				printLength = HDMI21_MAX_DATA_PACKET_LENGTH;
			}

			for(i=3;i<printLength; i++){
				HDMI20_DBG("[%s][ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", sPacketNameHDMI21[type], (i-3), uint8ToBinary( (UINT8)gHDMI21RxHandler[port].dataPacket[y][i] ) ,(UINT8)gHDMI21RxHandler[port].dataPacket[y][i]);
			}
		}
	}

}

void HDMI21_DISLAND_Rx_Get_PrintEmPkttBuf(HDMI21_EMPACKET_NAME_TYPE_T type, UINT8 port)
{
	int i;
	UINT32 __data = 0;
	int length = 0;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Need to add for other packets */
	
	/* VTEM */
	if(type ==  HDMI21_EMPACKET_VTEM){
		HDMI20_DBG("Data Packet Type  =>  %s  \n", "EMP VTEM");
		for(i=0;i<3;i++){
			HDMI20_DBG("[VTEM][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]);
		}

		for(i=3;i<10;i++){
			HDMI20_DBG("[VTEM][PB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-3), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]);
		}

		__data  = (UINT32)gHDMI21RxHandler[port].emp_vtemPacket[8];
		__data  = __data << 8; 
		__data |= (0x000000FF & (UINT32)gHDMI21RxHandler[port].emp_vtemPacket[9]);

		length = 10 + (int)__data; 

		for(i=10;i<length; i++){
			HDMI20_DBG("[VTEM][ MD%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-10), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]) ,(UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]);
		}
	}
	else if(type == HDMI21_EMPACKET_CVTEM) {
		HDMI20_DBG("Data Packet Type  =>  %s  \n", "EMP CVTEM");
		for(i=0;i<3;i++){
			HDMI20_DBG("[CVTEM][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]);
		}

		for(i=3;i<10;i++){
			HDMI20_DBG("[CVTEM][PB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-3), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]);
		}


		for(i=10;i<HDMI21_MAX_CVTEM_LENGHT; i++){
			HDMI20_DBG("[CVTEM][MD%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-10), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]) ,(UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]);
		}

	}
}


/* IOCTL */
int HDMI21_DISLAND_Rx_Get_DRMInfo(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall)
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

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI20_RX_DRM_PACKET_T));


		/* Step 2. Copy data */
		userdata.nVersion	= gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__DRM][1];
		userdata.nLength	= gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__DRM][2];

		memcpy((void *)&userdata.metaData[0], (void *)&gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__DRM][0], HDMI21_MAX_DATA_PACKET_LENGTH);

		/* DBG : UI SDR/HDR override */
		if(gHDMI21RxHandler[port].hdrOverRide > 0) {
			userdata.nVersion = 0x01; 
			userdata.nLength = 0x1a;
			userdata.metaData[0] = 0x87;
			userdata.metaData[4] = (UINT8)(gHDMI21RxHandler[port].hdrOverRide - 1); 
			userdata.metaData[5] = 0x00;	// eMeta_Desc

			/* 2020/01/06 */
			HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(port);
		}

		/* DBG : Force DRM Data */
		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_HDR10_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI21RxDevVideoControler[HDMI21__FORCE_HDR10_SAMPLE_PACKET].value;
			if (dbg_value==0x3||dbg_value==0x103)
			{
				userdata.nVersion = 0x01; 
				userdata.nLength = 0x1a;
				userdata.metaData[0] = 0x87;
				userdata.metaData[4] = 0x03;	// eEOTFType(HLG)
				userdata.metaData[5] = 0x00;	// eMeta_Desc
			}
			else if (dbg_value==0x2||dbg_value==0x102)
			{
				userdata.nVersion = 0x01;
				userdata.nLength = 0x1a;
				userdata.metaData[0] = 0x87;
				userdata.metaData[4] = 0x02;	// eEOTFType(HDR10)
				userdata.metaData[5] = 0x00;	// eMeta_Desc
			}
			else if (dbg_value==0x1||dbg_value==0x101)
			{
				userdata.nVersion = 0x01; 
				userdata.nLength = 0x1a;
				userdata.metaData[0] = 0x00;
				userdata.metaData[4] = 0x00;	// eEOTFType
				userdata.metaData[5] = 0x00;	// eMeta_Desc
			}
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI20_RX_DRM_PACKET_T *)pData, &userdata, sizeof(LX_HDMI20_RX_DRM_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI20_RX_DRM_PACKET_T *)pData, &userdata, sizeof(LX_HDMI20_RX_DRM_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketNameHDMI21[HDMI21_DISLAND_DATA__DRM], port);
				break;
			}
		}

		cur_data = userdata.metaData[23]<<12|userdata.metaData[22]<<4|userdata.metaData[4];
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
int HDMI21_DISLAND_Rx_Get_AVIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_INFO_PACKET_T userdata;
	UINT32 dbg_value = 0;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_INFO_PACKET_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_INFO_PACKET_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_INFO_PACKET_T));

		/* Defence Code : If length is 0, clear Data */
		if((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][2] == 0)||(gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][2] > 0x20)||(gHDMI21RxHandler[port].video.dvi)){
			memset((void *)&userdata.dataBytes, 0, HDMI21_MAX_DATA_PACKET_LENGTH - 4);
		}

		/* Step 2. Copy data */
		userdata.InfoFrameType = 0x82;
		memcpy((void *)&userdata.header, (void *)&gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][1], 2);
		memcpy((void *)&userdata.dataBytes, (void *)&gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][3], HDMI21_MAX_DATA_PACKET_LENGTH - 3);

		/* Notice : WEBOS & Pioneer gets DVI/HDMI information through this 7th bytes of AVI info frame...
		 *          This is not a standard in the specification.
		 *          Only LGE way... Do not know the history of this.. But i think the one who first did this
		 *          was a lazy guy and did not want a new IOCTL command for this..*/
		if(gHDMI21RxHandler[port].video.dvi){
			userdata.dataBytes[7] &= 0xFE;
		}
		else{
			userdata.dataBytes[7] |= 0x01;
		}

		/* DBG : Force COLOR Data */
		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_COLOR_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI21RxDevVideoControler[HDMI21__FORCE_COLOR_SAMPLE_PACKET].value;
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
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketNameHDMI21[HDMI21_DISLAND_DATA__AVI], port);
				break;
			}
		}
		ret = RET_OK;
	} while(0);

	return ret;
}


/* IOCTL */
int HDMI21_DISLAND_Rx_Get_SPDInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall)
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

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_INFO_PACKET_T));

		/* Step 2. Copy data */
		userdata.InfoFrameType = 0x83;
		memcpy((void *)&userdata.header, (void *)&gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__SPD][1], 2);
		memcpy((void *)&userdata.dataBytes, (void *)&gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__SPD][3], HDMI21_MAX_DATA_PACKET_LENGTH - 3);

		/* Defence Code : If length is 0, clear Data */
		if((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__SPD][2] == 0)||(gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__SPD][2] > 0x20)){
			memset((void *)&userdata.dataBytes, 0, HDMI21_MAX_DATA_PACKET_LENGTH - 4);
		}


		if(isInternalCall > 0){
			memcpy((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketNameHDMI21[HDMI21_DISLAND_DATA__SPD], port);
				break;
			}
		}
		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI21_DISLAND_Rx_Get_VSIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type)
{
	int ret = RET_ERROR;
	LX_HDMI_INFO_PACKET_T userdata;
	HDMI21_DISLAND_DATA_T __t = HDMI21_DISLAND_DATA__VSI;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_INFO_PACKET_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_INFO_PACKET_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		switch(type)
		{
			case LX_HDMI20_VSI_H14B_VSIF:
				__t = HDMI21_DISLAND_DATA__H14VSI;
				break;

			case LX_HDMI20_VSI_HF_VSIF:
				__t = HDMI21_DISLAND_DATA__HFVSI;
				break;

			case LX_HDMI20_VSI_DOLBY:
				__t = HDMI21_DISLAND_DATA__DOLBYVSI;
				break;

			case LX_HDMI20_VSI_UNKNOWN:
				__t = HDMI21_DISLAND_DATA__VSI;
				break;
			default :
				__t = HDMI21_DISLAND_DATA__VSI;
				break;
		}


		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_INFO_PACKET_T));

		/* Step 2. Copy data */
		userdata.InfoFrameType = 0x81;
		memcpy((void *)&userdata.header, (void *)&gHDMI21RxHandler[port].dataPacket[__t][1], 2);
		memcpy((void *)&userdata.dataBytes, (void *)&gHDMI21RxHandler[port].dataPacket[__t][3], HDMI21_MAX_DATA_PACKET_LENGTH - 3);

		/* Defence Code : If length is 0, clear Data */
		if((gHDMI21RxHandler[port].dataPacket[__t][2] == 0)||(gHDMI21RxHandler[port].dataPacket[__t][2] > 0x20)){
			memset((void *)&userdata.dataBytes, 0, HDMI21_MAX_DATA_PACKET_LENGTH - 4);
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
		}
		else{
			ret = copy_to_user((LX_HDMI_INFO_PACKET_T *)pData, &userdata, sizeof(LX_HDMI_INFO_PACKET_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", sPacketNameHDMI21[__t], port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI21_DISLAND_Rx_Get_MultipleVSIPacket(UINT8 port, LX_HDMI20_MULTIPLE_VSI_T *pData, int size)
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

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI20_MULTIPLE_VSI_T));


		/* Step 2. Copy data */
		/* Till full implementation, only send VSI H14B */
		userdata.numberOfVSI = 1;
		userdata.packet[0].type = 0x81;
		userdata.packet[0].version = gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__VSI][1];
		userdata.packet[0].length = gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__VSI][2];
		memcpy((void *)&userdata.packet[0].dataBytes, (void *)&gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__VSI][3], HDMI21_MAX_DATA_PACKET_LENGTH - 3);

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
int HDMI21_DISLAND_Rx_Get_COLORInfo(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall)
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

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Reset memory */
		memset((void *)&data , 0 , sizeof(LX_HDMI_COLOR_DOMAIN_T));

		if(gHDMI21RxHandler[port].video.dvi){
			data.bHdmiMode = 0;
		}
		else{
			data.bHdmiMode = 1;
		}
		
		video_format = gHDMI21RxHandler[port].video.video_format;
		data.ePixelEncoding = (UINT16)(video_format);
		data.eColorimetry = (UINT16)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][5] & 0xC0)>>6) ;
		data.eExtColorimetry = (UINT16)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][6] & 0x70)>>4) ;
		data.eITContent = (UINT16)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][6] & 0x80)>>7);
		data.eRGBQuantizationRange = (UINT16)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][6] & 0x0C)>>2);

		/* DBG : Force COLOR Data */
		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_COLOR_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI21RxDevVideoControler[HDMI21__FORCE_COLOR_SAMPLE_PACKET].value;
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
int HDMI21_DISLAND_Rx_Get_EMPInfo(UINT8 port, UINT8 *pData, LX_HDMI20_EMP_TYPE_T type, int isInternalCall)
{
	int ret = RET_ERROR;
	UINT8 userdata[31] = {0,};
	unsigned char cvtemData[HDMI21_MAX_CVTEM_LENGHT];

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
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
			memcpy((void *)&userdata[0], (void *)&gHDMI21RxHandler[port].emp_vtemPacket[0], 3);
			memcpy((void *)&userdata[3], (void *)&gHDMI21RxHandler[port].emp_vtemPacket[3], 28);
		}
		else if (type == LX_HDMI20_EMP_CVTEM) {
			memcpy((void *)&cvtemData[0], (void *)&gHDMI21RxHandler[port].emp_cvtemPacket[0], sizeof(unsigned char) * HDMI21_MAX_CVTEM_LENGHT);
		}

		if(isInternalCall) {
			if(type == LX_HDMI20_EMP_VTEM) { 
				memcpy((void *)pData, (void *)&userdata, 31 * sizeof(UINT8));
			}
			else if(type == LX_HDMI20_EMP_CVTEM) {
				memcpy((void *)pData, (void *)&cvtemData,  HDMI21_MAX_CVTEM_LENGHT * sizeof(unsigned char));
			}
		}
		else {
			if(type == LX_HDMI20_EMP_VTEM) { 
				ret = copy_to_user((void *)pData, (void *)&userdata, 31 * sizeof(UINT8));
			}
			else if(type == LX_HDMI20_EMP_CVTEM)  {
				ret = copy_to_user((void *)pData, (void *)&cvtemData, HDMI21_MAX_CVTEM_LENGHT * sizeof(unsigned char));
			}

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
int HDMI21_DISLAND_Rx_Get_AspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall)
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

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Reset memory */
		memset((void *)&data , 0 , sizeof(LX_HDMI_ASPECTRATIO_T));

		data.eAspectRatio = (UINT16)(gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][5] & 0x0F);

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


int HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 data = 0;
	UINT32 dbg_value = 0;
	static UINT32 pre_data[HDMI21_NUM_OF_MAX_PORTS] = {0,};
	UINT32 __t = 0; // For HDR/SDR override UI menu
	
	do{
		/* Check Port */
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* 2019/12/27 : UI SDR/HDR Override*/
		__t = (UINT32)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__DRM][4] & 0x0F));
		if(gHDMI21RxHandler[port].hdrOverRide > 0) {
			__t = (UINT32)(gHDMI21RxHandler[port].hdrOverRide - 1);
		}

		/* 20170124, color domain data -> max_display_mastering_luminance */
		#if 0
		data = (UINT32)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__AVI][5]&0x60)>>5);
		data = data & 0x3;
		data = data <<4;
		#else
		data = (UINT32)((gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__DRM][22]<<8)|gHDMI21RxHandler[port].dataPacket[HDMI21_DISLAND_DATA__DRM][21]);
		data = (!data)? 1:((data-1)/1000+1);
		if (data>0xF)	data=0xF;
		data = data <<4;
		#endif

		data &= (0xFFFFFFF0);
		data |= __t;

		/* DBG : Force DRM Data */
		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_HDR10_SAMPLE_PACKET].value > 0){
			dbg_value = gHDMI21RxDevVideoControler[HDMI21__FORCE_HDR10_SAMPLE_PACKET].value;
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

		HDMI21_HAL_Rx_Set_PqeHdrInfo(&gHDMI21RxHandler[port], data, 0);

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


int HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSync(UINT8 *dataPacket)
{
	int ret = RET_ERROR; 
	UINT8 data[HDMI21_MAX_DATAPACKET_SIZE] = {0};

	do{
		/* Check Port */
		if(dataPacket == NULL){
			HDMI20_ERROR("Error! Null Pointer access\n");
			break;
		}

		/* Get Data */
		memcpy((UINT8 *)&data, (UINT8 *)dataPacket, HDMI21_MAX_DATAPACKET_SIZE);

		if(data[0] != HDMI21_SPD_AMD_FREESYNC_PACKETTYPE) break;
		if(data[1] != HDMI21_SPD_AMD_FREESYNC_VERSION) break;
		if(data[2] != HDMI21_SPD_AMD_FREESYNC_LENGTH) break;
		if(data[4] != HDMI21_SPD_AMD_FREESYNC_OUI_PB1) break;
		if(data[5] != HDMI21_SPD_AMD_FREESYNC_OUI_PB2) break;
		if(data[6] != HDMI21_SPD_AMD_FREESYNC_OUI_PB3) break;

		if((data[9] & 0x03) == 0x03){
			ret = RET_OK;	
		}

	} while(0);

	return ret;
}

int HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSyncV2( UINT8 *dataPacket){
	int ret = RET_ERROR;
	UINT8 data[HDMI21_MAX_DATAPACKET_SIZE] = {0,};

	do{
		if(!dataPacket){
			HDMI20_ERROR("Error! Null Pointer access\n");
			break;
		}

		memcpy( (UINT8 *)&data, (UINT8 *)dataPacket, HDMI21_MAX_DATAPACKET_SIZE);

		if(data[0] != HDMI21_SPD_AMD_FREESYNC_PACKETTYPE) break;
		if(data[1] != HDMI21_SPD_AMD_FREESYNC_VERSION2) break;
		//if(data[2] != HDMI21_SPD_AMD_FREESYNC_LENGTH_V2) break;
		if(data[4] != HDMI21_SPD_AMD_FREESYNC_OUI_PB1) break;
		if(data[5] != HDMI21_SPD_AMD_FREESYNC_OUI_PB2) break;
		if(data[6] != HDMI21_SPD_AMD_FREESYNC_OUI_PB3) break;

		if((data[2] == HDMI21_SPD_AMD_FREESYNC_LENGTH_V2) || (data[2] == HDMI21_SPD_AMD_FREESYNC_LENGTH_V2_1)) {
			//Check FreeSync (active, enable, supported bit)
			if( (data[9] & 0x03) == 0x03 ){
				ret = RET_OK;
			}
		}
	}while(0);

	return ret;
}

int HDMI21_DISLAND_Rx_Get_IsSpdAmdFreeSyncV3( UINT8 *dataPacket){
	int ret = RET_ERROR;
	UINT8 data[HDMI21_MAX_DATAPACKET_SIZE] = {0,};

	do{
		if(!dataPacket){
			HDMI20_ERROR("Error! Null Pointer access\n");
			break;
		}

		memcpy( (UINT8 *)&data, (UINT8 *)dataPacket, HDMI21_MAX_DATAPACKET_SIZE);

		if(data[0] != HDMI21_SPD_AMD_FREESYNC_PACKETTYPE) break;
		if(data[1] != HDMI21_SPD_AMD_FREESYNC_VERSION3) break;
		//if(data[2] != HDMI21_SPD_AMD_FREESYNC_LENGTH_V3) break;
		if(data[4] != HDMI21_SPD_AMD_FREESYNC_OUI_PB1) break;
		if(data[5] != HDMI21_SPD_AMD_FREESYNC_OUI_PB2) break;
		if(data[6] != HDMI21_SPD_AMD_FREESYNC_OUI_PB3) break;

		//Check FreeSync (active, enable, supported bit)
		if( (data[9] & 0x03) == 0x03 ){
			ret = RET_OK;
		}

	}while(0);

	return ret;
}




void HDMI21_DISLAND_Rx_PROC_PrintPktBuf(int port, struct seq_file* m)
{
	int i,y;
	int printLength = 0;

	if(port >= g_hdmi20_number_of_ports){
		seq_printf(m, "Error! Port exceeded max port size(%d)]n", port);
		return;
	}


	for(y=0; y<HDMI21_DISLAND_DATA_MAXNUM; y++){
		seq_printf(m, "Data Packet y  =>  %s  \n", sPacketNameHDMI21[y]);
		for(i=0;i<3;i++){
			seq_printf(m, "[%s][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", sPacketNameHDMI21[y], i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].dataPacket[y][i]) ,(UINT8)gHDMI21RxHandler[port].dataPacket[y][i]);
		}

		/* Overflow protection : Length does not include checksum space */
		printLength = gHDMI21RxHandler[port].dataPacket[y][2] + 5;

		if(printLength >= HDMI21_MAX_DATA_PACKET_LENGTH){
			printLength = HDMI21_MAX_DATA_PACKET_LENGTH;
		}

		for(i=3;i<printLength; i++){
			seq_printf(m, "[%s][ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", sPacketNameHDMI21[y], (i-3), uint8ToBinary( (UINT8)gHDMI21RxHandler[port].dataPacket[y][i] ) ,(UINT8)gHDMI21RxHandler[port].dataPacket[y][i]);
		}
	}
}

void HDMI21_DISLAND_Rx_PROC_PrintEmPkttBuf(int port, struct seq_file* m)
{
	int i;

	if(port >= g_hdmi20_number_of_ports){
		seq_printf(m, "Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Need to add for other packets */
	/* VTEM */

	seq_printf(m, "Data Packet Type  =>  %s  \n", "EMP VTEM");
	for(i=0;i<3;i++){
		seq_printf(m, "[VTEM][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]);
	}

	for(i=3;i<HDMI21_MAX_DATA_PACKET_LENGTH; i++){
		seq_printf(m, "[VTEM][ B%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-3), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]) ,(UINT8)gHDMI21RxHandler[port].emp_vtemPacket[i]);
	}

	HDMI20_DBG("Data Packet Type  =>  %s  \n", "EMP CVTEM");
	for(i=0;i<3;i++){
		seq_printf(m, "[CVTEM][HB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", i, uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]);
	}

	for(i=3;i<10;i++){
		seq_printf(m, "[CVTEM][PB%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-3), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]), (UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]);
	}

	for(i=10;i<HDMI21_MAX_CVTEM_LENGHT; i++){
		seq_printf(m, "[CVTEM][MD%02d] - Binary[  %s  ]  -  Hex[  0x%02x  ]\n", (i-10), uint8ToBinary((UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]) ,(UINT8)gHDMI21RxHandler[port].emp_cvtemPacket[i]);
	}

}



