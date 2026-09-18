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

#ifndef  OVI_HW_O20_INC
#define  OVI_HW_O20_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
 #if (CONFIG_LX_O20_CHIP_FIRMWARE == 1)
#define BE_OVI_HW_O20_USE_VX1_CHIP_INFO
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
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO

//#define BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE

#define BE_OVI_HW_O20_VX1_CHIP_INFO_TOTAL_MEM_SIZE 0x00100000
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_SIZE 49152
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_TOTAL_NUM 6 // including the buffer for PE
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM 2
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP 3
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET 31732
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_SIZE 17408 // == 0x4400
#define BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE (BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_SIZE+12) // 12 = 4:Header + 4:CRC + 4:End Packet

#define OVI_HW_O20_GAMMA_TABLE_SIZENUM 1024

#define OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZENUM ((1024*3)+1)
#define OVI_HW_O20_VX1_CHIP_INFO_DPG_CTRL_SIZENUM (4)
#define OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_SIZENUM (14)
#define BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_SIZENUM (2)
#define BE_HW_O20_VX1_CHIP_INFO_PCC_SIZENUM (18)
#define BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZENUM (2)
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
#define BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZENUM (1206)
#else
#define BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZENUM (1227)
#endif
#define OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZE (OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZENUM*sizeof(UINT32))
#define OVI_HW_O20_VX1_CHIP_INFO_DPG_CTRL_SIZE (OVI_HW_O20_VX1_CHIP_INFO_DPG_CTRL_SIZENUM*sizeof(UINT32))
#define OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_SIZE (OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_SIZENUM*sizeof(UINT32))
#define BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE (BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_SIZENUM*sizeof(UINT32))
#define BE_HW_O20_VX1_CHIP_INFO_PCC_SIZE (BE_HW_O20_VX1_CHIP_INFO_PCC_SIZENUM*sizeof(UINT32))
#define BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE (BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZENUM*sizeof(UINT32))
#define BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZE (BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZENUM*sizeof(UINT32))

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
typedef enum {
	OVI_HW_O20_VX1_CHIP_INFO_DPG = 0,
	OVI_HW_O20_VX1_CHIP_INFO_CLR_TMP = 1,
	BE_HW_O20_VX1_CHIP_INFO_LED_CTRL = 8,
	BE_HW_O20_VX1_CHIP_INFO_PCC = 9,
	BE_HW_O20_VX1_CHIP_INFO_OSD_LVL = 16,
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_MAX
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_TYPE;

#define BE_OVI_HW_O20_VX1_CHIP_INFO_APB_NUM BE_OVI_HW_O20_VX1_CHIP_INFO_APB_MAX
#define BE_OVI_HW_O20_VX1_CHIP_INFO_HDR		(0x05190000)
#define BE_OVI_HW_O20_VX1_CHIP_INFO_EP		(0x8ED00000)

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 maxNum       				:8;	//7:0
		UINT32 rsvd                         :12;
		UINT32 bufIdx1                      :4;	//23:20
		UINT32 bufIdx0                      :4;	//27:24
		UINT32 version                      :4;	//31:28
	};
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_INFO_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 offset                       :16;//15:0
		UINT32 size                         :16;//31:16
	};
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_POS_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 dpg                          :4;	//3:0
		UINT32 colorTemp                    :4;	//7:4
		UINT32 rsvd0             	        :4;	//11:8
		UINT32 rsvd1                        :4;	//15:12
		UINT32 rsvd2                   	    :4;	//19:16
		UINT32 rsvd3                        :4;	//23:20
		UINT32 rsvd4                        :4;	//27:24
		UINT32 rsvd5                        :4;	//31:28
	};
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT0_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 ledSpiCtrl                   :4;	//3:0
		UINT32 pcc                          :4;	//7:4
		UINT32 rsvd0                        :4;	//11:8
		UINT32 rsvd1                        :4;	//15:12
		UINT32 rsvd2                        :4;	//19:16
		UINT32 rsvd3                        :4;	//23:20
		UINT32 rsvd4                        :4;	//27:24
		UINT32 rsvd5                        :4;	//31:28
	};
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT1_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 osdLvCtrl                    :4;	//3:0
		UINT32 rsvd0                        :4;	//7:4
		UINT32 rsvd1                        :4;	//11:8
		UINT32 rsvd2                        :4;	//15:12
		UINT32 rsvd3                        :4;	//19:16
		UINT32 rsvd4                        :4;	//23:20
		UINT32 rsvd5                        :4;	//27:24
		UINT32 rsvd6                        :4;	//31:28
	};
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT2_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 rsvd0                        :4;	//3:0
		UINT32 rsvd1                        :4;	//7:4
		UINT32 rsvd2                        :4;	//11:8
		UINT32 rsvd3                        :4;	//15:12
		UINT32 rsvd4                        :4;	//19:16
		UINT32 rsvd5                        :4;	//23:20
		UINT32 rsvd6                        :4;	//27:24
		UINT32 rsvd7                        :4;	//31:28
	};
} BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT3_T;

typedef struct
{
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_INFO_T info;
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT0_T cnt0;
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT1_T cnt1;
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT2_T cnt2;
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT3_T cnt3;
	BE_OVI_HW_O20_VX1_CHIP_INFO_APB_POS_T pos[32];
} BE_OVI_HW_O20_VX1_CHIP_INFO_DAT_HDR_T;

typedef struct {
	UINT32 wDataRegAddr; // offset [0x98]
	UINT32 wdata[OVI_HW_O20_GAMMA_TABLE_SIZENUM*3];
/*
	UINT32 wrDoneRegAddr;
	UINT32 wrDoneVal;
	UINT32 enRegAddr;
	UINT32 enVal;*/ // Write in F/W
} OVI_HW_O20_VX1_CHIP_INFO_DPG_T;

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
} OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_T;

typedef struct {
	UINT32 ledSpiCtrlRegAddr;
	UINT32 ledSpiCtrlVal;
} BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_T;

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
} BE_HW_O20_VX1_CHIP_INFO_PCC_T;

typedef struct {
	UINT32 osdLvCtrlRegAddr;
	UINT32 osdLvCtrlVal;
} BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T;

typedef struct {
	UINT32 rsvd[BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZENUM];
} BE_HW_O20_VX1_CHIP_INFO_RSVD_T;

typedef struct {
	UINT32 hwHdr; 										// offset [0x0] 
	BE_OVI_HW_O20_VX1_CHIP_INFO_DAT_HDR_T datHdr;		//		 [0x4]
	OVI_HW_O20_VX1_CHIP_INFO_DPG_T dpg;					//		 [0x98]
	OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_T colorTemp;	//		 [0x309C]
	BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_T ledSpiCtrl;	//		 [0x30D4]
	BE_HW_O20_VX1_CHIP_INFO_PCC_T pcc;					//		 [0x30DC]
	BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T osdLvCtrl;	//		 [0x3124]
	BE_HW_O20_VX1_CHIP_INFO_RSVD_T rsvd;				//		 [0x312C]
	UINT32 hwCrc;										//		 [0x4404]
	UINT32 endPacket; // end of APB slave buffer			//		 [0x4408]
} BE_OVI_HW_O20_VX1_CHIP_INFO_T;

#else

typedef struct {
	UINT32 dataHwHdr; // offset [0x0]
	UINT32 wDataRegAddr;
	UINT32 wdata[OVI_HW_O20_GAMMA_TABLE_SIZENUM*3];
	UINT32 dataHwCrc;

	UINT32 ctrlHwHdr; // offset [0x300C]
	UINT32 wrDoneRegAddr;
	UINT32 wrDoneVal;
	UINT32 enRegAddr;
	UINT32 enVal;
	UINT32 ctrlHwCrc;
} OVI_HW_O20_VX1_CHIP_INFO_DPG_T;

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
} OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 ledSpiCtrlRegAddr;
	UINT32 ledSpiCtrlVal;
	UINT32 hwCrc;
} BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_T;

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
} BE_HW_O20_VX1_CHIP_INFO_PCC_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 osdLvCtrlRegAddr;
	UINT32 osdLvCtrlVal;
	UINT32 hwCrc;
} BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T;

typedef struct {
	UINT32 hwHdr;
	UINT32 rsvd[BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZENUM];
	UINT32 hwCrc;
} BE_HW_O20_VX1_CHIP_INFO_RSVD_T;

typedef struct {
	OVI_HW_O20_VX1_CHIP_INFO_DPG_T dpg;					// offset [0x0] 
	OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_T colorTemp;	//		 [0x3024] 
	BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_T ledSpiCtrl;	//		 [0x3064] 
	BE_HW_O20_VX1_CHIP_INFO_PCC_T pcc;					//		 [0x3074] 
	BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_T osdLvCtrl;	//		 [0x30C4] 
	BE_HW_O20_VX1_CHIP_INFO_RSVD_T rsvd;				//		 [0x30D4] 
	UINT32 endPacket; // end of APB master buffer -> written by F/W	 [0x4408]
} BE_OVI_HW_O20_VX1_CHIP_INFO_T;
#endif
#endif

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
void OVI_HW_O20_HWDisplayOptionInit(void);
int OVI_HW_O20_PreInitialize(void);
int OVI_HW_O20_Initialize(void);
int OVI_HW_O20_Close(void);
int OVI_HW_O20_Suspend(void);
int OVI_HW_O20_EarlyResume(void);
int OVI_HW_O20_Resume(void);
int OVI_HW_O20_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_O20_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams);
int OVI_HW_O20_SetCombination(UINT32 param);
int OVI_HW_O20_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
int OVI_HW_O20_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_O20_SetFrameOdcEnable(BOOLEAN bParam);
int OVI_HW_O20_SetColorTempEnable(BOOLEAN bParam);
int OVI_HW_O20_SetGammaEnable(BOOLEAN bParam);
int OVI_HW_O20_SetDitherEnable(BOOLEAN bParam);
int OVI_HW_O20_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
int OVI_HW_O20_SetDitherMode(LX_OVI_TCON_DITHER_T enParam);
int OVI_HW_O20_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
int OVI_HW_O20_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams);
int OVI_HW_O20_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_O20_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams);
int OVI_HW_O20_SetTconHReverse(BOOLEAN bParam);
int OVI_HW_O20_SetLvdsHReverse(BOOLEAN bParam);
int OVI_HW_O20_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
int OVI_HW_O20_SetChannelPower(BOOLEAN bParam);
int OVI_HW_O20_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam);
int OVI_HW_O20_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam);
int OVI_HW_O20_SetLvdsBlack(BOOLEAN bParam);
int OVI_HW_O20_SetClock(BOOLEAN bParam);
int OVI_HW_O20_SetEpiDataScramble(BOOLEAN bParam);
int OVI_HW_O20_SetAdvanced10bit(BOOLEAN bParam);
int OVI_HW_O20_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam);
int OVI_HW_O20_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam);
int OVI_HW_O20_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam);
int OVI_HW_O20_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_O20_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams);
int OVI_HW_O20_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
int OVI_HW_O20_SetPmMode(UINT32 u32Param);
int OVI_HW_O20_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_HW_O20_INC  ----- */
/**  @} */

