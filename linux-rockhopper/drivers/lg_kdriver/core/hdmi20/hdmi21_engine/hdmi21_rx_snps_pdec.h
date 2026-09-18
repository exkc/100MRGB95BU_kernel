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
 *  @date       2019-04-01
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_PDEC_H_
#define	_HDMI21_RX_SNPS_PDEC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif

/* PKT_2_INTVEC 
 * [2:0] RESERVED
 * [3] ACR
 * [4] GCP
 * [5] ACP
 * [6] ISRC1
 * [7] ISRC2
 * [8] GMD
 * [9] AMD
 * [10] VSI
 * [11] AVI
 * [12] SRCPDIF
 * [13] AUDIF
 * [14] RSVD
 * [15] NTSCVBI
 * [16] DRM
 * [17] GEN PKT0
 * [18] GEN PKT1
 * [20:19] RSVD
 * [21] EMD
 * [22] CVTEM
 * [23] VTEM
 */


#define HDMI21_SNPS_REG_PKTDEC_ACR_CONFIG 				(0x1000) 	
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_DELTACTS_THR_QST	MSK(3,4)
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_N_OVR_EN		BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_CTS_CONFIG 			(0x1004) 	   
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_OVR_VALUE		MSK(20, 0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_N_CONFIG 			(0x1008) 	
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_N_OVR_VALUE		MSK(20, 0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_MAXMIN_CLEAR 		(0x100c) 	
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_N_MAXMIN_CLR_P	BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_CTS_MAX_STATUS 		(0x1010)   
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_MAX_STS		MSK(20, 0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_CTS_MIN_STATUS 		(0x1014)
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_MIN_STS		MSK(20, 0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_N_MAX_STATUS 		(0x1018) 	 
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_N_MAX_STS			MSK(20, 0)

#define HDMI21_SNPS_REG_PKTDEC_ACR_N_MIN_STATUS 		(0x101c) 	   
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_N_MIN_STS			MSK(20, 0)

#define HDMI21_SNPS_REG_PKTDEC_SP_VALID_CONFIG 			(0x1020) 	
#define HDMI21_SNPS_FIELD_PKTDEC_GCP_SP0_ONLY_QST		BIT(4)
#define HDMI21_SNPS_FIELD_PKTDEC_ACR_SP0_ONLY_QST		BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_GCP_AVMUTE_CONFIG 		(0x1024)
#define HDMI21_SNPS_FIELD_PKTDEC_AUTO_CLEAR_AVMUTE_SEL	MSK(3, 13)
#define HDMI21_SNPS_FIELD_PKTDEC_AUTO_CLEAR_AVMUTE_EN		BIT(12)
#define HDMI21_SNPS_FIELD_PKTDEC_GCP_CLR_AVMUTE_OVR_VALUE BIT(8)
#define HDMI21_SNPS_FIELD_PKTDEC_GCP_SET_AVMUTE_OVR_VALUE BIT(4)
#define HDMI21_SNPS_FIELD_PKTDEC_GCP_AVMUTE_OVR_EN		BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_AVMUTE_DIS_CONTROL 		(0x1028)   
#define HDMI21_SNPS_FIELD_PKTDEC_AVMUTE_DISABLE			BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_EMD_STATUS 				(0x102C) 	
#define HDMI21_SNPS_FIELD_PKTDEC_EMD_VTEM_STS			BIT(1)
#define HDMI21_SNPS_FIELD_PKTDEC_EMD_CVTEM_STS			BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_GCP_AVMUTE_STATUS 		(0x1030)    
#define HDMI21_SNPS_FIELD_PKTDEC_GCP_CLR_AVMUTE_STS		BIT(4)
#define HDMI21_SNPS_FIELD_PKTDEC_GCP_SET_AVMUTE_STS		BIT(0)

#define HDMI21_SNPS_REG_PKTDEC_SNAPSHOT_BYP_CONTROL 	(0x1040) 

#define HDMI21_SNPS_REG_PKTDEC_ACR_PH2_1 				(0x1100) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB3_0 				(0x1104) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB7_4 				(0x1108) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB11_8  				(0x110c) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB15_12  			(0x1110) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB19_16  			(0x1114) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB23_20  			(0x1118) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACR_PB27_24  			(0x111c) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PH2_1  				(0x1120) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB3_0  				(0x1124) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB7_4  				(0x1128) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB11_8  				(0x112c) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB15_12  			(0x1130) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB19_16  			(0x1134) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB23_20  			(0x1138) 	   
#define HDMI21_SNPS_REG_PKTDEC_GCP_PB27_24  			(0x113c) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACP_PH2_1  				(0x1140) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACP_PB3_0  				(0x1144) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACP_PB7_4  				(0x1148) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACP_PB11_8  				(0x114c) 	   
#define HDMI21_SNPS_REG_PKTDEC_ACP_PB15_12  			(0x1150) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC1_PH2_1  			(0x1160) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC1_PB3_0  			(0x1164) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC1_PB7_4  			(0x1168) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC1_PB11_8  			(0x116c)    
#define HDMI21_SNPS_REG_PKTDEC_ISRC1_PB15_12  			(0x1170)   
#define HDMI21_SNPS_REG_PKTDEC_ISRC2_PH2_1  			(0x1180) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC2_PB3_0  			(0x1184) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC2_PB7_4  			(0x1188) 	   
#define HDMI21_SNPS_REG_PKTDEC_ISRC2_PB11_8 	 		(0x118c)    
#define HDMI21_SNPS_REG_PKTDEC_ISRC2_PB15_12  			(0x1190)   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PH2_1  				(0x11a0) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB3_0  				(0x11a4) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB7_4  				(0x11a8) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB11_8  				(0x11ac) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB15_12  			(0x11b0) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB19_16  			(0x11b4) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB23_20  			(0x11b8) 	   
#define HDMI21_SNPS_REG_PKTDEC_GMD_PB27_24  			(0x11bc) 	   
#define HDMI21_SNPS_REG_PKTDEC_AMD_PH2_1  				(0x11c0) 	   
#define HDMI21_SNPS_REG_PKTDEC_AMD_PB3_0  				(0x11c4) 	   
#define HDMI21_SNPS_REG_PKTDEC_AMD_PB7_4  				(0x11c8) 	   
#define HDMI21_SNPS_REG_PKTDEC_AMD_PB11_8  				(0x11cc) 	   
#define HDMI21_SNPS_REG_PKTDEC_AMD_PB15_12  			(0x11d0) 	   
#define HDMI21_SNPS_REG_PKTDEC_AMD_PB19_16  			(0x11d4) 	   
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PH2_1  				(0x11e0) 	   
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB3_0  				(0x11e4) 	   
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB7_4  				(0x11e8) 	   
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB11_8  			(0x11ec) 	   
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB15_12  			(0x11f0) 
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB19_16  			(0x11f4) 
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB23_20  			(0x11f8) 
#define HDMI21_SNPS_REG_PKTDEC_VSIF_PB27_24  			(0x11fc) 
#define HDMI21_SNPS_REG_PKTDEC_AVIIF_PH2_1  			(0x1200) 	   
#define HDMI21_SNPS_REG_PKTDEC_AVIIF_PB3_0  			(0x1204) 	   
#define HDMI21_SNPS_REG_PKTDEC_AVIIF_PB7_4  			(0x1208) 	   
#define HDMI21_SNPS_REG_PKTDEC_AVIIF_PB11_8  			(0x120c) 
#define HDMI21_SNPS_REG_PKTDEC_AVIIF_PB15_12  			(0x1210)
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PH2_1  			(0x1220)   
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB3_0  			(0x1224)   
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB7_4  			(0x1228)   
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB11_8 			(0x122c)   
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB15_12 			(0x1230)  
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB19_16 			(0x1234)  
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB23_20 			(0x1238)  
#define HDMI21_SNPS_REG_PKTDEC_SRCPDIF_PB27_24 			(0x123c)  
#define HDMI21_SNPS_REG_PKTDEC_AUDIF_PH2_1  			(0x1240) 	   
#define HDMI21_SNPS_REG_PKTDEC_AUDIF_PB3_0  			(0x1244) 	   
#define HDMI21_SNPS_REG_PKTDEC_AUDIF_PB7_4  			(0x1248) 	   
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PH2_1 			(0x1280)
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB3_0 			(0x1284)
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB7_4 			(0x1288) 
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB11_8 		(0x128c) 
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB15_12 		(0x1290)
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB19_16 		(0x1294)
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB23_20 		(0x1298)
#define HDMI21_SNPS_REG_PKTDEC_NTSCVBIIF_PB27_24 		(0x129c) 
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PH2_1  			(0x12a0) 	  
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB3_0  			(0x12a4) 	  
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB7_4  			(0x12a8) 	  
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB11_8  			(0x12ac) 
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB15_12  			(0x12b0)
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB19_16  			(0x12b4)
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB23_20  			(0x12b8)
#define HDMI21_SNPS_REG_PKTDEC_DRMIF_PB27_24  			(0x12bc)
#define HDMI21_SNPS_REG_PKTDEC_EMD_PH2_1  				(0x12c0) 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB3_0  				(0x12c4) 	 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB7_4  				(0x12c8) 	 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB11_8  				(0x12cc) 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB15_12  			(0x12d0) 	 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB19_16  			(0x12d4) 	 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB23_20  			(0x12d8) 	 
#define HDMI21_SNPS_REG_PKTDEC_EMD_PB27_24  			(0x12dc) 	 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_PB3_0  			(0x1300) 	
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_PB6_4  			(0x1304) 	
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD3_0  			(0x1308) 	 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD7_4  			(0x130c) 	  
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD11_8  			(0x1310)  
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD15_12  			(0x1314) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD19_16  			(0x1318) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD23_20  			(0x131c) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD27_24  			(0x1320) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD31_28  			(0x1324) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD35_32  			(0x1328) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD39_36  			(0x132c) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD43_40  			(0x1330) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD47_44  			(0x1334) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD51_48  			(0x1338) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD55_52  			(0x133c) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD59_56  			(0x1340) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD63_60  			(0x1344) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD67_64  			(0x1348) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD71_68  			(0x134c) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD75_72  			(0x1350) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD79_76  			(0x1354) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD83_80  			(0x1358) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD87_84  			(0x135c) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD91_88  			(0x1360) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD95_92  			(0x1364) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD99_96  			(0x1368) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD103_100 			(0x136c)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD107_104 			(0x1370)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD111_108 			(0x1374)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD115_112 			(0x1378)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD119_116 			(0x137c)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD123_120 			(0x1380)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD127_124 			(0x1384)
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD131_128 			(0x1388) 
#define HDMI21_SNPS_REG_PKTDEC_CVTEM_MD135_132 			(0x138c) 
#define HDMI21_SNPS_REG_PKTDEC_VTEM_PB3_0  				(0x13a0) 	
#define HDMI21_SNPS_REG_PKTDEC_VTEM_PB6_4  				(0x13a4) 	
#define HDMI21_SNPS_REG_PKTDEC_VTEM_MD3_0  				(0x13a8) 	  
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PH2_1  			(0x1480) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB3_0  			(0x1484)  
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB7_4  			(0x1488) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB11_8 			(0x148c) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB15_12 			(0x1490) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB19_16 			(0x1494) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB23_20 			(0x1498) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT0_PB27_24 			(0x149c) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PH2_1  			(0x14a0) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB3_0  			(0x14a4)  
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB7_4  			(0x14a8)  
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB11_8 			(0x14ac)  
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB15_12 			(0x14b0) 
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB19_16 			(0x14b4)  
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB23_20 			(0x14b8)
#define HDMI21_SNPS_REG_PKTDEC_GENPKT1_PB27_24 			(0x14bc) 



/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
	
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_PDEC_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_PDEC_Rx_Set_StorePktToHander(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_DISLAND_DATA_T type);
void HDMI21_PDEC_Rx_Get_PktDataVTEM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_PDEC_Rx_Get_PktDataCVTEM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_PDEC_Rx_Set_AudioCtsDiffThresHold(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 val);
void HDMI21_PDEC_Rx_Set_AudioNCtsOverride(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isOverride, UINT32 acr_n, UINT32 acr_cts);
void HDMI21_PDEC_Rx_Set_AVMuteOverride(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isOverride, bool setAVmute, bool clearAVmute);
void HDMI21_PDEC_Rx_Set_AVMuteDisable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isDisable);

/* N/CTS Min Max tracker */
void HDMI21_PDEC_Rx_Set_ResetAcrNCtsTrackingHistory(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_PDEC_Rx_Get_AudioAcrCtsMin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_PDEC_Rx_Get_AudioAcrCtsMax(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_PDEC_Rx_Get_AudioAcrNMin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_PDEC_Rx_Get_AudioAcrNMax(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

bool HDMI21_PDEC_Rx_Get_AVMuteSetStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
bool HDMI21_PDEC_Rx_Get_AVMuteClearStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
bool HDMI21_PDEC_Rx_Get_VTemActiveStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
bool HDMI21_PDEC_Rx_Get_CVTemActiveStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

