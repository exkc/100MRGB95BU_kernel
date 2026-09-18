/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 *	OVI module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

#ifndef  OVI_HW_O22_INC
#define  OVI_HW_O22_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)
#define BE_OVI_HW_O22_USE_VX1_CHIP_INFO
#endif

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ovi_kapi.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO

#ifdef BUILD_FEATURE_y22_board
#undef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
#else
#define BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
#endif


#define BE_OVI_HW_O22_VX1_CHIP_INFO_TOTAL_MEM_SIZE 0x00100000
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_SIZE 49152
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_TOTAL_NUM 6 // including the buffer for PE
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM 2
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP 3
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET 31732
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_SIZE 17408 // == 0x4400
#define BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE (BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_SIZE+12) // 12 = 4:Header + 4:CRC + 4:End Packet

#define OVI_HW_O22_GAMMA_TABLE_SIZENUM 1024

#define OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZENUM ((1024*3)+1)
#define OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZENUM (4)
#define OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZENUM (14)
#define BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZENUM (2)
#define BE_HW_O22_VX1_CHIP_INFO_PCC_SIZENUM (18)
#define BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZENUM (2)
#define BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZENUM (128)
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
#define BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZENUM (1074)
#else
#define BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZENUM (1097)
#endif
#define OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE (OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZENUM*sizeof(UINT32))
#define OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE (OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZENUM*sizeof(UINT32))
#define OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE (OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZENUM*sizeof(UINT32))
#define BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE (BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZENUM*sizeof(UINT32))
#define BE_HW_O22_VX1_CHIP_INFO_PCC_SIZE (BE_HW_O22_VX1_CHIP_INFO_PCC_SIZENUM*sizeof(UINT32))
#define BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE (BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZENUM*sizeof(UINT32))
#define BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZE (BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZENUM*sizeof(UINT32))
#define BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZE (BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZENUM*sizeof(UINT32))

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
typedef enum {
	OVI_HW_O22_VX1_CHIP_INFO_DPG = 0,
	OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP = 1,
	BE_HW_O22_VX1_CHIP_INFO_LED_CTRL = 4,
	BE_HW_O22_VX1_CHIP_INFO_PCC = 5,
	BE_HW_O22_VX1_CHIP_INFO_OSD_LVL = 8,
	BE_HW_O22_VX1_CHIP_INFO_PHDR = 9,
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_MAX
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_TYPE;

#define BE_OVI_HW_O22_VX1_CHIP_INFO_APB_NUM BE_OVI_HW_O22_VX1_CHIP_INFO_APB_MAX
#define BE_OVI_HW_O22_VX1_CHIP_INFO_HDR		(0x05190000)
#define BE_OVI_HW_O22_VX1_CHIP_INFO_EP		(0x8ED00000)

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 maxNum       				:8;	//7:0
		UINT32 rsvd                         :12;
		UINT32 bufIdx1                      :4;	//23:20
		UINT32 bufIdx0                      :4;	//27:24
		UINT32 version                      :4;	//31:28
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_INFO_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 offset                       :16;//15:0
		UINT32 size                         :16;//31:16
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_POS_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 dpg                          :8;	//7:0
		UINT32 colorTemp                    :8;	//15:8
		UINT32 rsvd0             	        :8;	//23:16
		UINT32 rsvd1                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT0_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 ledSpiCtrl                   :8;	//7:0
		UINT32 pcc                          :8;	//15:8
		UINT32 rsvd0             	        :8;	//23:16
		UINT32 rsvd1                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT1_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 osdLvCtrl                    :8;	//7:0
		UINT32 phdr                         :8;	//15:8
		UINT32 rsvd0             	        :8;	//23:16
		UINT32 rsvd1                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT2_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 rsvd0                        :8;	//7:0
		UINT32 rsvd1                        :8;	//15:8
		UINT32 rsvd2             	        :8;	//23:16
		UINT32 rsvd3                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT3_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 rsvd0                        :8;	//7:0
		UINT32 rsvd1                        :8;	//15:8
		UINT32 rsvd2             	        :8;	//23:16
		UINT32 rsvd3                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT4_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 rsvd0                        :8;	//7:0
		UINT32 rsvd1                        :8;	//15:8
		UINT32 rsvd2             	        :8;	//23:16
		UINT32 rsvd3                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT5_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 rsvd0                        :8;	//7:0
		UINT32 rsvd1                        :8;	//15:8
		UINT32 rsvd2             	        :8;	//23:16
		UINT32 rsvd3                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT6_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 rsvd0                        :8;	//7:0
		UINT32 rsvd1                        :8;	//15:8
		UINT32 rsvd2             	        :8;	//23:16
		UINT32 rsvd3                        :8;	//31:24
	};
} BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT7_T;

typedef struct
{
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_INFO_T info;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT0_T cnt0;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT1_T cnt1;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT2_T cnt2;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT3_T cnt3;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT4_T cnt4;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT5_T cnt5;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT6_T cnt6;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT7_T cnt7;
	BE_OVI_HW_O22_VX1_CHIP_INFO_APB_POS_T pos[32];
} BE_OVI_HW_O22_VX1_CHIP_INFO_DAT_HDR_T;

typedef struct {
	UINT32 wDataRegAddr; // offset [0x98]
	UINT32 wdata[OVI_HW_O22_GAMMA_TABLE_SIZENUM*3];
/*
	UINT32 wrDoneRegAddr;
	UINT32 wrDoneVal;
	UINT32 enRegAddr;
	UINT32 enVal;*/ // Write in F/W
} OVI_HW_O22_VX1_CHIP_INFO_DPG_T;

typedef struct {
	UINT32 wbEnRegAddr;
	UINT32 wbEnVal;
	UINT32 wbRGainRegAddr;
	UINT32 wbRGainVal;
	UINT32 wbROffsetRegAddr;
	UINT32 wbROffsetVal;
	UINT32 wbGGainRegAddr;
	UINT32 wbGGainVal;
	UINT32 wbGOffsetRegAddr;
	UINT32 wbGOffsetVal;
	UINT32 wbBGainRegAddr;
	UINT32 wbBGainVal;
	UINT32 wbBOffsetRegAddr;
	UINT32 wbBOffsetVal;
} OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_T;

typedef struct {
	UINT32 ledSpiCtrlRegAddr;
	UINT32 ledSpiCtrlVal;
} BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_T;

typedef struct {
	UINT32 pccCoef0RegAddr;
	UINT32 pccCoef0Val;
	UINT32 pccCoef1RegAddr;
	UINT32 pccCoef1Val;
	UINT32 pccCoef2RegAddr;
	UINT32 pccCoef2Val;
	UINT32 pccCoef3RegAddr;
	UINT32 pccCoef3Val;
	UINT32 pccCoef4RegAddr;
	UINT32 pccCoef4Val;
	UINT32 pccCoef5RegAddr;
	UINT32 pccCoef5Val;
	UINT32 pccCoef6RegAddr;
	UINT32 pccCoef6Val;
	UINT32 pccCoef7RegAddr;
	UINT32 pccCoef7Val;
	UINT32 pccCtrlRegAddr;
	UINT32 pccCtrlVal;
} BE_HW_O22_VX1_CHIP_INFO_PCC_T;

typedef struct {
	UINT32 osdLvCtrlRegAddr;
	UINT32 osdLvCtrlVal;
} BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T;

typedef struct {
	UINT32 phdrCtrl003RegAddr;
	UINT32 phdrCtrl003Val;
	UINT32 phdrCtrl004RegAddr;
	UINT32 phdrCtrl004Val;
	UINT32 phdrCtrl005RegAddr;
	UINT32 phdrCtrl005Val;
	UINT32 phdrCtrl006RegAddr;
	UINT32 phdrCtrl006Val;
	UINT32 phdrCtrl008RegAddr;
	UINT32 phdrCtrl008Val;
	UINT32 phdrCtrl010RegAddr;
	UINT32 phdrCtrl010Val;
	UINT32 phdrCtrl011RegAddr;
	UINT32 phdrCtrl011Val;
	UINT32 phdrCtrl012RegAddr;
	UINT32 phdrCtrl012Val;
	UINT32 phdrCtrl013RegAddr;
	UINT32 phdrCtrl013Val;
	UINT32 phdrCtrl014RegAddr;
	UINT32 phdrCtrl014Val;
	UINT32 phdrCtrl015RegAddr;
	UINT32 phdrCtrl015Val;
	UINT32 phdrCtrl016RegAddr;
	UINT32 phdrCtrl016Val;
	UINT32 phdrCtrl017RegAddr;
	UINT32 phdrCtrl017Val;
	UINT32 phdrCtrl078RegAddr;
	UINT32 phdrCtrl078Val;
	UINT32 phdrCtrl079RegAddr;
	UINT32 phdrCtrl079Val;
	UINT32 phdrCtrl080RegAddr;
	UINT32 phdrCtrl080Val;
	UINT32 phdrCtrl081RegAddr;
	UINT32 phdrCtrl081Val;
	UINT32 phdrCtrl082RegAddr;
	UINT32 phdrCtrl082Val;
	UINT32 phdrCtrl083RegAddr;
	UINT32 phdrCtrl083Val;
	UINT32 phdrCtrl084RegAddr;
	UINT32 phdrCtrl084Val;
	UINT32 phdrCtrl085RegAddr;
	UINT32 phdrCtrl085Val;
	UINT32 phdrCtrl086RegAddr;
	UINT32 phdrCtrl086Val;
	UINT32 phdrCtrl087RegAddr;
	UINT32 phdrCtrl087Val;
	UINT32 phdrCtrl088RegAddr;
	UINT32 phdrCtrl088Val;
	UINT32 phdrCtrl089RegAddr;
	UINT32 phdrCtrl089Val;
	UINT32 phdrCtrl090RegAddr;
	UINT32 phdrCtrl090Val;
	UINT32 phdrCtrl091RegAddr;
	UINT32 phdrCtrl091Val;
	UINT32 phdrCtrl092RegAddr;
	UINT32 phdrCtrl092Val;
	UINT32 phdrCtrl093RegAddr;
	UINT32 phdrCtrl093Val;
	UINT32 phdrCtrl094RegAddr;
	UINT32 phdrCtrl094Val;
	UINT32 phdrCtrl095RegAddr;
	UINT32 phdrCtrl095Val;
	UINT32 phdrCtrl096RegAddr;
	UINT32 phdrCtrl096Val;
	UINT32 phdrCtrl097RegAddr;
	UINT32 phdrCtrl097Val;
	UINT32 phdrCtrl098RegAddr;
	UINT32 phdrCtrl098Val;
	UINT32 phdrCtrl099RegAddr;
	UINT32 phdrCtrl099Val;
	UINT32 phdrCtrl100RegAddr;
	UINT32 phdrCtrl100Val;
	UINT32 phdrCtrl101RegAddr;
	UINT32 phdrCtrl101Val;
	UINT32 phdrCtrl102RegAddr;
	UINT32 phdrCtrl102Val;
	UINT32 phdrCtrl103RegAddr;
	UINT32 phdrCtrl103Val;
	UINT32 phdrCtrl104RegAddr;
	UINT32 phdrCtrl104Val;
	UINT32 phdrCtrl105RegAddr;
	UINT32 phdrCtrl105Val;
	UINT32 phdrCtrl106RegAddr;
	UINT32 phdrCtrl106Val;
	UINT32 phdrCtrl107RegAddr;
	UINT32 phdrCtrl107Val;
	UINT32 phdrCtrl108RegAddr;
	UINT32 phdrCtrl108Val;
	UINT32 phdrCtrl109RegAddr;
	UINT32 phdrCtrl109Val;
	UINT32 phdrCtrl134RegAddr;
	UINT32 phdrCtrl134Val;
	UINT32 phdrCtrl135RegAddr;
	UINT32 phdrCtrl135Val;
	UINT32 phdrCtrl136RegAddr;
	UINT32 phdrCtrl136Val;
	UINT32 phdrCtrl137RegAddr;
	UINT32 phdrCtrl137Val;
	UINT32 phdrCtrl138RegAddr;
	UINT32 phdrCtrl138Val;
	UINT32 phdrCtrl139RegAddr;
	UINT32 phdrCtrl139Val;
	UINT32 phdrCtrl140RegAddr;
	UINT32 phdrCtrl140Val;
	UINT32 phdrCtrl141RegAddr;
	UINT32 phdrCtrl141Val;
	UINT32 oledCtrl02RegAddr;
	UINT32 oledCtrl02Val;
	UINT32 oaplCtrl00RegAddr;
	UINT32 oaplCtrl00Val;
	UINT32 oaplCtrl01RegAddr;
	UINT32 oaplCtrl01Val;

	UINT32 phdrHist00RegAddr;
	UINT32 phdrHist00Val;
	UINT32 phdrHist01RegAddr;
	UINT32 phdrHist01Val;
	UINT32 phdrHist02RegAddr;
	UINT32 phdrHist02Val;
	UINT32 phdrHist03RegAddr;
	UINT32 phdrHist03Val;
	UINT32 phdrSatGain00RegAddr;
	UINT32 phdrSatGain00Val;
	UINT32 phdrSatGain01RegAddr;
	UINT32 phdrSatGain01Val;
	UINT32 phdrSatGain02RegAddr;
	UINT32 phdrSatGain02Val;
	UINT32 phdrSatGain03RegAddr;
	UINT32 phdrSatGain03Val;
} BE_HW_O22_VX1_CHIP_INFO_PHDR_T;

typedef struct {
	UINT32 rsvd[BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZENUM];
} BE_HW_O22_VX1_CHIP_INFO_RSVD_T;

typedef struct {
	UINT32 hwHdr; 										// offset [0x0] 
	BE_OVI_HW_O22_VX1_CHIP_INFO_DAT_HDR_T datHdr;		//		 [0x4]
	OVI_HW_O22_VX1_CHIP_INFO_DPG_T dpg;					//		 [0xA8]
	OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_T colorTemp;	//		 [0x30AC]
	BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_T ledSpiCtrl;	//		 [0x30E4]
	BE_HW_O22_VX1_CHIP_INFO_PCC_T pcc;					//		 [0x30EC]
	BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T osdLvCtrl;	//		 [0x3134]
	BE_HW_O22_VX1_CHIP_INFO_PHDR_T phdr; 				//       [0x313C]
	BE_HW_O22_VX1_CHIP_INFO_RSVD_T rsvd;				//		 [0x333C]
	UINT32 hwCrc;										//		 [0x4404]
	UINT32 endPacket; // end of APB slave buffer			//		 [0x4408]
} BE_OVI_HW_O22_VX1_CHIP_INFO_T;

#else

typedef struct {
	UINT32 dataHwHdr; // offset [0x0]
	UINT32 wDataRegAddr;
	UINT32 wdata[OVI_HW_O22_GAMMA_TABLE_SIZENUM*3];
	UINT32 dataHwCrc;

	UINT32 ctrlHwHdr; // offset [0x300C]
	UINT32 wrDoneRegAddr;
	UINT32 wrDoneVal;
	UINT32 enRegAddr;
	UINT32 enVal;
	UINT32 ctrlHwCrc;
} OVI_HW_O22_VX1_CHIP_INFO_DPG_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 wbEnRegAddr;
	UINT32 wbEnVal;
	UINT32 wbRGainRegAddr;
	UINT32 wbRGainVal;
	UINT32 wbROffsetRegAddr;
	UINT32 wbROffsetVal;
	UINT32 wbGGainRegAddr;
	UINT32 wbGGainVal;
	UINT32 wbGOffsetRegAddr;
	UINT32 wbGOffsetVal;
	UINT32 wbBGainRegAddr;
	UINT32 wbBGainVal;
	UINT32 wbBOffsetRegAddr;
	UINT32 wbBOffsetVal;
	UINT32 hwCrc;
} OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 ledSpiCtrlRegAddr;
	UINT32 ledSpiCtrlVal;
	UINT32 hwCrc;
} BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 pccCoef0RegAddr;
	UINT32 pccCoef0Val;
	UINT32 pccCoef1RegAddr;
	UINT32 pccCoef1Val;
	UINT32 pccCoef2RegAddr;
	UINT32 pccCoef2Val;
	UINT32 pccCoef3RegAddr;
	UINT32 pccCoef3Val;
	UINT32 pccCoef4RegAddr;
	UINT32 pccCoef4Val;
	UINT32 pccCoef5RegAddr;
	UINT32 pccCoef5Val;
	UINT32 pccCoef6RegAddr;
	UINT32 pccCoef6Val;
	UINT32 pccCoef7RegAddr;
	UINT32 pccCoef7Val;
	UINT32 pccCtrlRegAddr;
	UINT32 pccCtrlVal;
	UINT32 hwCrc;
} BE_HW_O22_VX1_CHIP_INFO_PCC_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 osdLvCtrlRegAddr;
	UINT32 osdLvCtrlVal;
	UINT32 hwCrc;
} BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 phdrCtrl003RegAddr;
	UINT32 phdrCtrl003Val;
	UINT32 phdrCtrl004RegAddr;
	UINT32 phdrCtrl004Val;
	UINT32 phdrCtrl005RegAddr;
	UINT32 phdrCtrl005Val;
	UINT32 phdrCtrl006RegAddr;
	UINT32 phdrCtrl006Val;
	UINT32 phdrCtrl008RegAddr;
	UINT32 phdrCtrl008Val;
	UINT32 phdrCtrl010RegAddr;
	UINT32 phdrCtrl010Val;
	UINT32 phdrCtrl011RegAddr;
	UINT32 phdrCtrl011Val;
	UINT32 phdrCtrl012RegAddr;
	UINT32 phdrCtrl012Val;
	UINT32 phdrCtrl013RegAddr;
	UINT32 phdrCtrl013Val;
	UINT32 phdrCtrl014RegAddr;
	UINT32 phdrCtrl014Val;
	UINT32 phdrCtrl015RegAddr;
	UINT32 phdrCtrl015Val;
	UINT32 phdrCtrl016RegAddr;
	UINT32 phdrCtrl016Val;
	UINT32 phdrCtrl017RegAddr;
	UINT32 phdrCtrl017Val;
	UINT32 phdrCtrl078RegAddr;
	UINT32 phdrCtrl078Val;
	UINT32 phdrCtrl079RegAddr;
	UINT32 phdrCtrl079Val;
	UINT32 phdrCtrl080RegAddr;
	UINT32 phdrCtrl080Val;
	UINT32 phdrCtrl081RegAddr;
	UINT32 phdrCtrl081Val;
	UINT32 phdrCtrl082RegAddr;
	UINT32 phdrCtrl082Val;
	UINT32 phdrCtrl083RegAddr;
	UINT32 phdrCtrl083Val;
	UINT32 phdrCtrl084RegAddr;
	UINT32 phdrCtrl084Val;
	UINT32 phdrCtrl085RegAddr;
	UINT32 phdrCtrl085Val;
	UINT32 phdrCtrl086RegAddr;
	UINT32 phdrCtrl086Val;
	UINT32 phdrCtrl087RegAddr;
	UINT32 phdrCtrl087Val;
	UINT32 phdrCtrl088RegAddr;
	UINT32 phdrCtrl088Val;
	UINT32 phdrCtrl089RegAddr;
	UINT32 phdrCtrl089Val;
	UINT32 phdrCtrl090RegAddr;
	UINT32 phdrCtrl090Val;
	UINT32 phdrCtrl091RegAddr;
	UINT32 phdrCtrl091Val;
	UINT32 phdrCtrl092RegAddr;
	UINT32 phdrCtrl092Val;
	UINT32 phdrCtrl093RegAddr;
	UINT32 phdrCtrl093Val;
	UINT32 phdrCtrl094RegAddr;
	UINT32 phdrCtrl094Val;
	UINT32 phdrCtrl095RegAddr;
	UINT32 phdrCtrl095Val;
	UINT32 phdrCtrl096RegAddr;
	UINT32 phdrCtrl096Val;
	UINT32 phdrCtrl097RegAddr;
	UINT32 phdrCtrl097Val;
	UINT32 phdrCtrl098RegAddr;
	UINT32 phdrCtrl098Val;
	UINT32 phdrCtrl099RegAddr;
	UINT32 phdrCtrl099Val;
	UINT32 phdrCtrl100RegAddr;
	UINT32 phdrCtrl100Val;
	UINT32 phdrCtrl101RegAddr;
	UINT32 phdrCtrl101Val;
	UINT32 phdrCtrl102RegAddr;
	UINT32 phdrCtrl102Val;
	UINT32 phdrCtrl103RegAddr;
	UINT32 phdrCtrl103Val;
	UINT32 phdrCtrl104RegAddr;
	UINT32 phdrCtrl104Val;
	UINT32 phdrCtrl105RegAddr;
	UINT32 phdrCtrl105Val;
	UINT32 phdrCtrl106RegAddr;
	UINT32 phdrCtrl106Val;
	UINT32 phdrCtrl107RegAddr;
	UINT32 phdrCtrl107Val;
	UINT32 phdrCtrl108RegAddr;
	UINT32 phdrCtrl108Val;
	UINT32 phdrCtrl109RegAddr;
	UINT32 phdrCtrl109Val;
	UINT32 phdrCtrl134RegAddr;
	UINT32 phdrCtrl134Val;
	UINT32 phdrCtrl135RegAddr;
	UINT32 phdrCtrl135Val;
	UINT32 phdrCtrl136RegAddr;
	UINT32 phdrCtrl136Val;
	UINT32 phdrCtrl137RegAddr;
	UINT32 phdrCtrl137Val;
	UINT32 phdrCtrl138RegAddr;
	UINT32 phdrCtrl138Val;
	UINT32 phdrCtrl139RegAddr;
	UINT32 phdrCtrl139Val;
	UINT32 phdrCtrl140RegAddr;
	UINT32 phdrCtrl140Val;
	UINT32 phdrCtrl141RegAddr;
	UINT32 phdrCtrl141Val;
	UINT32 oledCtrl02RegAddr;
	UINT32 oledCtrl02Val;
	UINT32 oaplCtrl00RegAddr;
	UINT32 oaplCtrl00Val;
	UINT32 oaplCtrl01RegAddr;
	UINT32 oaplCtrl01Val;

	UINT32 phdrHist00RegAddr;
	UINT32 phdrHist00Val;
	UINT32 phdrHist01RegAddr;
	UINT32 phdrHist01Val;
	UINT32 phdrHist02RegAddr;
	UINT32 phdrHist02Val;
	UINT32 phdrHist03RegAddr;
	UINT32 phdrHist03Val;
	UINT32 phdrSatGain00RegAddr;
	UINT32 phdrSatGain00Val;
	UINT32 phdrSatGain01RegAddr;
	UINT32 phdrSatGain01Val;
	UINT32 phdrSatGain02RegAddr;
	UINT32 phdrSatGain02Val;
	UINT32 phdrSatGain03RegAddr;
	UINT32 phdrSatGain03Val;
	UINT32 hwCrc;
} BE_HW_O22_VX1_CHIP_INFO_PHDR_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 rsvd[BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZENUM];
	UINT32 hwCrc;
} BE_HW_O22_VX1_CHIP_INFO_RSVD_T;

typedef struct {
	OVI_HW_O22_VX1_CHIP_INFO_DPG_T dpg;					// offset [0x0] 
	OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_T colorTemp;	//		 [0x3024] 
	BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_T ledSpiCtrl;	//		 [0x3064] 
	BE_HW_O22_VX1_CHIP_INFO_PCC_T pcc;					//		 [0x3074] 
	BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T osdLvCtrl;	//		 [0x30C4] 
	BE_HW_O22_VX1_CHIP_INFO_PHDR_T phdr; 				//       [0x30D4]
	BE_HW_O22_VX1_CHIP_INFO_RSVD_T rsvd;				//		 [0x32DC]
	UINT32 endPacket; // end of APB master buffer -> written by F/W	 [0x4408]
} BE_OVI_HW_O22_VX1_CHIP_INFO_T;
#endif
#endif

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
void OVI_HW_O22_HWDisplayOptionInit(void);
int OVI_HW_O22_PreInitialize(void);
int OVI_HW_O22_Initialize(void);
int OVI_HW_O22_Close(void);
int OVI_HW_O22_Suspend(void);
int OVI_HW_O22_EarlyResume(void);
int OVI_HW_O22_Resume(void);
int OVI_HW_O22_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_O22_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams);
int OVI_HW_O22_SetCombination(UINT32 param);
int OVI_HW_O22_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
int OVI_HW_O22_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_O22_SetFrameOdcEnable(BOOLEAN bParam);
int OVI_HW_O22_SetColorTempEnable(BOOLEAN bParam);
int OVI_HW_O22_SetGammaEnable(BOOLEAN bParam);
int OVI_HW_O22_SetDitherEnable(BOOLEAN bParam);
int OVI_HW_O22_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
int OVI_HW_O22_SetDitherMode(LX_OVI_TCON_DITHER_T enParam);
int OVI_HW_O22_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
int OVI_HW_O22_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams);
int OVI_HW_O22_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_O22_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams);
int OVI_HW_O22_SetTconHReverse(BOOLEAN bParam);
int OVI_HW_O22_SetLvdsHReverse(BOOLEAN bParam);
int OVI_HW_O22_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
int OVI_HW_O22_SetChannelPower(BOOLEAN bParam);
int OVI_HW_O22_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam);
int OVI_HW_O22_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam);
int OVI_HW_O22_SetLvdsBlack(BOOLEAN bParam);
int OVI_HW_O22_SetClock(BOOLEAN bParam);
int OVI_HW_O22_SetEpiDataScramble(BOOLEAN bParam);
int OVI_HW_O22_SetAdvanced10bit(BOOLEAN bParam);
int OVI_HW_O22_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam);
int OVI_HW_O22_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam);
int OVI_HW_O22_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam);
int OVI_HW_O22_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_O22_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams);
int OVI_HW_O22_GetLockStatus(BOOLEAN *pbParam);
int OVI_HW_O22_SetPmMode(UINT32 u32Param);
int OVI_HW_O22_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
int OVI_HW_O22_UpdateChipInfoHeader(void);
int OVI_HW_O22_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_HW_O22_INC  ----- */
/**  @} */

