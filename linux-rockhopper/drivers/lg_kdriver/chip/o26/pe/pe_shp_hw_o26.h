/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_shp_hw_o26.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_SHP_HW_O26_H_
#define	_PE_SHP_HW_O26_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_O26_SCL_MENU_TO_STR(_x)		(\
	((_x)==PE_SHP_HW_O26_RD_SCL_DISP  )? "DISP  ":\
	((_x)==PE_SHP_HW_O26_RD_SCL_INFO  )? "INFO  ":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G0Y_H1)? "G0Y_H1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G0Y_H2)? "G0Y_H2":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G0Y_V1)? "G0Y_V1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G0Y_V2)? "G0Y_V2":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G1Y_H1)? "G1Y_H1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G1Y_H2)? "G1Y_H2":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G1Y_V1)? "G1Y_V1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G1Y_V2)? "G1Y_V2":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G0C_H1)? "G0C_H1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G0C_V1)? "G0C_V1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G1C_H1)? "G1C_H1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_G1C_V1)? "G1C_V1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_P1Y_H1)? "P1Y_H1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_P1Y_H2)? "P1Y_H2":\
	((_x)==PE_SHP_HW_O26_RD_SCL_P1Y_V1)? "P1Y_V1":\
	((_x)==PE_SHP_HW_O26_RD_SCL_P1Y_V2)? "P1Y_V2":\
	"NUM")

#define PE_SHP_HW_O26_RES_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_RES_SD)? \
	"PE_SHP_O26_RES_SD":\
	((_x)==PE_SHP_O26_RES_HD)? \
	"PE_SHP_O26_RES_HD":\
	((_x)==PE_SHP_O26_RES_UHD)? \
	"PE_SHP_O26_RES_UHD":\
	((_x)==PE_SHP_O26_RES_DTV_SD)? \
	"PE_SHP_O26_RES_DTV_SD":\
	((_x)==PE_SHP_O26_RES_DTV_HD)? \
	"PE_SHP_O26_RES_DTV_HD":\
	((_x)==PE_SHP_O26_RES_SEEMLESS)? \
	"PE_SHP_O26_RES_SEEMLESS":\
	((_x)==PE_SHP_O26_RES_8K)? \
	"PE_SHP_O26_RES_8K":\
	"PE_SHP_O26_RES_NUM")

#define PE_SHP_HW_O26_SRE_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_SRE_HD)? \
	"PE_SHP_O26_SRE_HD":\
	((_x)==PE_SHP_O26_SRE_SD)? \
	"PE_SHP_O26_SRE_SD":\
	((_x)==PE_SHP_O26_SRE_ATV)? \
	"PE_SHP_O26_SRE_ATV":\
	((_x)==PE_SHP_O26_SRE_SEEMLESS)? \
	"PE_SHP_O26_SRE_SEEMLESS":\
	"PE_SHP_O26_SRE_NUM")

#define PE_SHP_HW_O26_2KS_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_2KS_HD)? \
	"PE_SHP_O26_2KS_HD":\
	((_x)==PE_SHP_O26_2KS_SD)? \
	"PE_SHP_O26_2KS_SD":\
	((_x)==PE_SHP_O26_2KS_UHD)? \
	"PE_SHP_O26_2KS_UHD":\
	((_x)==PE_SHP_O26_2KS_ATV)? \
	"PE_SHP_O26_2KS_ATV":\
	((_x)==PE_SHP_O26_2KS_DTV_SD)? \
	"PE_SHP_O26_2KS_DTV_SD":\
	((_x)==PE_SHP_O26_2KS_DTV_HD)? \
	"PE_SHP_O26_2KS_DTV_HD":\
	((_x)==PE_SHP_O26_2KS_SEEMLESS)? \
	"PE_SHP_O26_2KS_SEEMLESS":\
	((_x)==PE_SHP_O26_2KS_HDMI_720P)? \
	"PE_SHP_O26_2KS_HDMI_720P":\
	"PE_SHP_O26_2KS_NUM")

#define PE_SHP_HW_O26_CHR_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_CHR_HD)? \
	"PE_SHP_O26_CHR_HD":\
	((_x)==PE_SHP_O26_CHR_SD)? \
	"PE_SHP_O26_CHR_SD":\
	((_x)==PE_SHP_O26_CHR_UHD)? \
	"PE_SHP_O26_SRE_ATV":\
	"PE_SHP_O26_CHR_UHD")

#define PE_SHP_HW_O26_SRL_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_SRL_HD)? \
	"PE_SHP_O26_SRL_HD":\
	((_x)==PE_SHP_O26_SRL_SD)? \
	"PE_SHP_O26_SRL_SD":\
	"PE_SHP_O26_SRE_NUM")

#define PE_SHP_HW_O26_PBL_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_PBL_ATV_NT)? \
	"PE_SHP_O26_PBL_ATV_NT":\
	((_x)==PE_SHP_O26_PBL_ATV_PAL)? \
	"PE_SHP_O26_PBL_ATV_PAL":\
	((_x)==PE_SHP_O26_PBL_AV)? \
	"PE_SHP_O26_PBL_AV":\
	((_x)==PE_SHP_O26_PBL_SECAM)? \
	"PE_SHP_O26_PBL_SECAM":\
	((_x)==PE_SHP_O26_PBL_COMP_SD)? \
	"PE_SHP_O26_PBL_COMP_SD":\
	((_x)==PE_SHP_O26_PBL_DTV_SD)? \
	"PE_SHP_O26_PBL_DTV_SD":\
	((_x)==PE_SHP_O26_PBL_HDMI_SD)? \
	"PE_SHP_O26_PBL_HDMI_SD":\
	((_x)==PE_SHP_O26_PBL_HD)? \
	"PE_SHP_O26_PBL_HD":\
	((_x)==PE_SHP_O26_PBL_PC)? \
	"PE_SHP_O26_PBL_PC":\
	((_x)==PE_SHP_O26_PBL_UD)? \
	"PE_SHP_O26_PBL_UD":\
	((_x)==PE_SHP_O26_PBL_VR_360)? \
	"PE_SHP_O26_PBL_VR_360":\
	"PE_SHP_O26_PBL_NUM")

#define PE_SHP_HW_O26_CTI_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_CTI_HD)? \
	"PE_SHP_O26_CTI_HD":\
	((_x)==PE_SHP_O26_CTI_SD)? \
	"PE_SHP_O26_CTI_SD":\
	((_x)==PE_SHP_O26_CTI_VR_360)? \
	"PE_SHP_O26_CTI_VR_360":\
	((_x)==PE_SHP_O26_CTI_ATV)? \
	"PE_SHP_O26_CTI_ATV":\
	((_x)==PE_SHP_O26_CTI_UD)? \
	"PE_SHP_O26_CTI_UD":\
	"PE_SHP_O26_CTI_NUM")

#define PE_SHP_HW_O26_TBL_IDX_TO_STR(_x)		(\
	((_x)==PE_SHP_HW_O26_TBL_IDX_RES)? "RES":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_CTI)? "CTI":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_PBL)? "PBL":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_SRS)? "SRS":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_SRS_2K)? "SRS2K":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_OBC_FACE)? "OBF":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_OBC_OBJT)? "OBO":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_OBE)? "OBE":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_SRS_SUB)? "SRSUB":\
	((_x)==PE_SHP_HW_O26_TBL_IDX_RES_GAV)? "GAV":\
	"NUM")

#define PE_SHP_HW_O26_OBC_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_OBC_HD)? \
	"PE_SHP_O26_OBC_HD":\
	((_x)==PE_SHP_O26_OBC_SD)? \
	"PE_SHP_O26_OBC_SD":\
	((_x)==PE_SHP_O26_OBC_UD)? \
	"PE_SHP_O26_OBC_UD":\
	"PE_SHP_O26_OBC_UHD")
#define PE_SHP_HW_O26_AMG_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_AMG_HD)? \
	"PE_SHP_O26_AMG_HD":\
	((_x)==PE_SHP_O26_AMG_SD)? \
	"PE_SHP_O26_AMG_SD":\
	((_x)==PE_SHP_O26_AMG_UD)? \
	"PE_SHP_O26_AMG_UD":\
	"PE_SHP_O26_AMG_UHD")
#define PE_SHP_HW_O26_OBE_FMT_TO_STR(_x)		(\
	((_x)==PE_SHP_O26_OBE_HD)? \
	"PE_SHP_O26_OBE_HD":\
	((_x)==PE_SHP_O26_OBE_SD)? \
	"PE_SHP_O26_OBE_SD":\
	((_x)==PE_SHP_O26_OBE_UD)? \
	"PE_SHP_O26_OBE_UD":\
	"PE_SHP_O26_OBE_UHD")
/**
 *	pe read scl filter coeff reg menu enumeration
 *	- msl(r):main scaler L(R), ssc:sub scaler
 */
typedef enum
{
	PE_SHP_HW_O26_RD_SCL_DISP = 0,		///< menu display
	PE_SHP_HW_O26_RD_SCL_INFO,			///< INFO
	PE_SHP_HW_O26_RD_SCL_DRV_ON,		///< scl drv on
	PE_SHP_HW_O26_RD_SCL_DRV_OFF,		///< scl drv off
	PE_SHP_HW_O26_RD_RDY_RD_G0Y,		///< ready rd m1y
	PE_SHP_HW_O26_RD_RDY_RD_G1Y,		///< ready rd m2y
	PE_SHP_HW_O26_RD_RDY_RD_G0C,		///< ready rd m1c
	PE_SHP_HW_O26_RD_RDY_RD_G1C,		///< ready rd m2c
	PE_SHP_HW_O26_RD_RDY_RD_P1Y,		///< ready rd p1y
	PE_SHP_HW_O26_RD_SCL_G0Y_H1,		///< G0Y_H1
	PE_SHP_HW_O26_RD_SCL_G0Y_H2,		///< G0Y_H2
	PE_SHP_HW_O26_RD_SCL_G0Y_V1,		///< G0Y_V1
	PE_SHP_HW_O26_RD_SCL_G0Y_V2,		///< G0Y_V2
	PE_SHP_HW_O26_RD_SCL_G1Y_H1,		///< G1Y_H1
	PE_SHP_HW_O26_RD_SCL_G1Y_H2,		///< G1Y_H2
	PE_SHP_HW_O26_RD_SCL_G1Y_V1,		///< G1Y_V1
	PE_SHP_HW_O26_RD_SCL_G1Y_V2,		///< G1Y_V2
	PE_SHP_HW_O26_RD_SCL_G0C_H1,		///< G0C_H1
	PE_SHP_HW_O26_RD_SCL_G0C_V1,		///< G0C_V1
	PE_SHP_HW_O26_RD_SCL_G1C_H1,		///< G0C_H1
	PE_SHP_HW_O26_RD_SCL_G1C_V1,		///< G0C_V1
	PE_SHP_HW_O26_RD_SCL_P1Y_H1,		///< P1Y_H1
	PE_SHP_HW_O26_RD_SCL_P1Y_H2,		///< P1Y_H2
	PE_SHP_HW_O26_RD_SCL_P1Y_V1,		///< P1Y_V1
	PE_SHP_HW_O26_RD_SCL_P1Y_V2,		///< P1Y_V2
	PE_SHP_HW_O26_RD_SCL_MAX			///< max num
}
PE_SHP_HW_O26_RD_SCL_MENU;


/**
 *	pe read default reg menu enumeration(for O26AX)
 */
typedef enum
{
	PE_SHP_HW_O26_RD_MENU_DISP = 0,	///< 00 menu display
	PE_SHP_HW_O26_RD_RES1_DISP,		///< 01 res1 display
	PE_SHP_HW_O26_RD_RES2_DISP,		///< 02 res2 display
	PE_SHP_HW_O26_RD_RES1_DFLT,		///< 03 res1 default
	PE_SHP_HW_O26_RD_RES1_USER,		///< 04 res1 user
	PE_SHP_HW_O26_RD_RES1_MASK,		///< 05 res1 mask
	PE_SHP_HW_O26_RD_RES1_DATA,		///< 06 res1 data
	PE_SHP_HW_O26_RD_CTI1_DISP,		///< 07 cti1 display
	PE_SHP_HW_O26_RD_CTI2_DISP,		///< 08 cti2 display
	PE_SHP_HW_O26_RD_CTI1_DFLT,		///< 09 cti1 default
	PE_SHP_HW_O26_RD_CTI1_USER,		///< 0a cti1 user
	PE_SHP_HW_O26_RD_CTI1_MASK,		///< 0b cti1 mask
	PE_SHP_HW_O26_RD_CTI1_DATA,		///< 0c cti1 data
	PE_SHP_HW_O26_RD_PBL1_DISP,		///< 0d pbl1 display
	PE_SHP_HW_O26_RD_PBL2_DISP,		///< 0e pbl2 display
	PE_SHP_HW_O26_RD_PBL1_DFLT,		///< 0f pbl1 default
	PE_SHP_HW_O26_RD_PBL1_USER,		///< 10 pbl1 user
	PE_SHP_HW_O26_RD_PBL1_MASK,		///< 11 pbl1 mask
	PE_SHP_HW_O26_RD_PBL1_DATA,		///< 12 pbl1 data
	PE_SHP_HW_O26_RD_2KS1_DISP,		///< 13 srs1 display
	PE_SHP_HW_O26_RD_2KS1_DFLT,		///< 14 srs1 default
	PE_SHP_HW_O26_RD_2KS1_USER,		///< 15 srs1 user
	PE_SHP_HW_O26_RD_2KS1_MASK,		///< 16 srs1 mask
	PE_SHP_HW_O26_RD_2KS1_DATA,		///< 17 srs1 data
	PE_SHP_HW_O26_RD_2KS2_DISP,		///< 18 srs2 display
	PE_SHP_HW_O26_RD_2KS2_DFLT,		///< 19 srs2 default
	PE_SHP_HW_O26_RD_2KS2_USER,		///< 1a srs2 user
	PE_SHP_HW_O26_RD_2KS2_MASK,		///< 1b srs2 mask
	PE_SHP_HW_O26_RD_2KS2_DATA,		///< 1c srs2 data
	PE_SHP_HW_O26_RD_GAV1_DISP,		///< 1d  GAV1display
	PE_SHP_HW_O26_RD_GAV1_DFLT,		///< 1e GAV1default
	PE_SHP_HW_O26_RD_GAV1_USER,		///< 1f  GAV1user
	PE_SHP_HW_O26_RD_GAV1_MASK,		///< 20  GAV1 mask
	PE_SHP_HW_O26_RD_GAV1_DATA,		///< 21  GAV1data
	PE_SHP_HW_O26_RD_OBE1_DISP,		///< 22 obe1 display
	PE_SHP_HW_O26_RD_OBE1_DFLT,		///< 23 obe1 default
	PE_SHP_HW_O26_RD_OBE1_USER,		///< 24 obe1 user
	PE_SHP_HW_O26_RD_OBE1_MASK,		///< 25 obe1 mask
	PE_SHP_HW_O26_RD_OBE1_DATA,		///< 26 obe1 data
	PE_SHP_HW_O26_RD_MENU_MAX			///< 2cmax num
}
PE_SHP_HW_O26_RD_DFLT_MENU;
/**
 *	pe table index enumeration(for O26AX)
 */
typedef enum
{
	PE_SHP_HW_O26_TBL_IDX_RES = 0,    ///< shp
	PE_SHP_HW_O26_TBL_IDX_CTI,        ///< cti
	PE_SHP_HW_O26_TBL_IDX_PBL,        ///< pre blur
	PE_SHP_HW_O26_TBL_IDX_SRS,        ///< sre shp(srs)
	PE_SHP_HW_O26_TBL_IDX_SRS_2K,     ///< sre shp(srs) 2k
	PE_SHP_HW_O26_TBL_IDX_OBC_FACE,   ///< obc face
	PE_SHP_HW_O26_TBL_IDX_OBC_OBJT,   ///< obc object
	PE_SHP_HW_O26_TBL_IDX_OBE,        ///< obe
	PE_SHP_HW_O26_TBL_IDX_SRS_SUB,     ///< sre shp(srs) sub
	PE_SHP_HW_O26_TBL_IDX_RES_GAV,     ///< gav shp
	PE_SHP_HW_O26_TBL_IDX_NUM         ///< max num
}
PE_SHP_HW_O26_TBL_IDX;

/**
 *	pe shp resolution enhance fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_RES_SD,				///< sd
	PE_SHP_O26_RES_HD,				///< hd
	PE_SHP_O26_RES_UHD,				///< hd
	PE_SHP_O26_RES_DTV_SD,			///< dtv sd 
	PE_SHP_O26_RES_DTV_HD,			///< dtv hd
	PE_SHP_O26_RES_8K,				///< 8k hd
	PE_SHP_O26_RES_SEEMLESS,		///< seemless
	PE_SHP_O26_RES_NUM				///< max num
}
PE_SHP_HW_O26_RES_FMT;


/**
 *	pe shp resolution enhance fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_2KS_SD,				///< sd
	PE_SHP_O26_2KS_HD,				///< hd
	PE_SHP_O26_2KS_UHD,				///< uhd
	PE_SHP_O26_2KS_ATV,				///< atv
	PE_SHP_O26_2KS_DTV_SD,			///< sd
	PE_SHP_O26_2KS_DTV_HD,			///< sd
	PE_SHP_O26_2KS_SEEMLESS,		///< seemless
	PE_SHP_O26_2KS_HDMI_720P,		///< hdmi 720p
	PE_SHP_O26_2KS_NUM				///< max num
}
PE_SHP_HW_O26_2KS_FMT;

/**
 *	pe shp resolution enhance fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_CHR_SD,				///< sd
	PE_SHP_O26_CHR_HD,				///< hd
	PE_SHP_O26_CHR_UHD,				///< uhd
	PE_SHP_O26_CHR_NUM				///< max num
}
PE_SHP_HW_O26_CHR_FMT;


/**
 *	pe shp sre fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_SRE_HD = 0,			///< hdmi hd
	PE_SHP_O26_SRE_SD,				///< hdmi sd
	PE_SHP_O26_SRE_ATV,				///< atv
	PE_SHP_O26_SRE_SEEMLESS,		///< seemless cp
	PE_SHP_O26_SRE_NUM				///< max num
}
PE_SHP_HW_O26_SRE_FMT;

/**
 *	pe shp sre lut fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_SRL_HD = 0,			///< hd
	PE_SHP_O26_SRL_SD,				///< sd
	PE_SHP_O26_SRL_NUM				///< max num
}
PE_SHP_HW_O26_SRL_FMT;

/**
 *	pe pre blur(dnr) fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_PBL_ATV_NT = 0,		///< atv nt
	PE_SHP_O26_PBL_ATV_PAL,		///< atv pal
	PE_SHP_O26_PBL_AV,				///< av
	PE_SHP_O26_PBL_SECAM,			///< secam
	PE_SHP_O26_PBL_COMP_SD,		///< comp sd
	PE_SHP_O26_PBL_DTV_SD,			///< dtv sd
	PE_SHP_O26_PBL_HDMI_SD,		///< hdmi sd
	PE_SHP_O26_PBL_HD,				///< hd
	PE_SHP_O26_PBL_PC,				///< pc
	PE_SHP_O26_PBL_UD,				///< ud
	PE_SHP_O26_PBL_VR_360,				///< ud
	PE_SHP_O26_PBL_NUM				///< max num
}
PE_SHP_HW_O26_PBL_FMT;

/**
 *	pe cti(p0d) fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_CTI_HD,				///< hd
	PE_SHP_O26_CTI_SD,				///< sd
	PE_SHP_O26_CTI_VR_360,				///< sd
	PE_SHP_O26_CTI_ATV,				///< atv
	PE_SHP_O26_CTI_UD,				///< atv
	PE_SHP_O26_CTI_NUM				///< max num
}
PE_SHP_HW_O26_CTI_FMT;

/**
 *	pe vsd psp top fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_PST_HD,				///< hd
	PE_SHP_O26_PST_SD,				///< sd
	PE_SHP_O26_PST_UD,				///< ud
	PE_SHP_O26_PST_NUM				///< max num
}
PE_SHP_HW_O26_PST_FMT;

/**
 *	pe vsd psp gain fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_PSG_HD,				///< hd
	PE_SHP_O26_PSG_SD,				///< sd
	PE_SHP_O26_PSG_UD,				///< ud
	PE_SHP_O26_PSG_NUM				///< max num
}
PE_SHP_HW_O26_PSG_FMT;

/**
 *	pe obc face fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_OBC_HD,				///< hd
	PE_SHP_O26_OBC_SD,				///< sd
	PE_SHP_O26_OBC_UD,				///< ud
	PE_SHP_O26_OBC_NUM				///< max num
}
PE_SHP_HW_O26_OBC_FMT;

/**
 *	pe amg  fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_AMG_HD,				///< hd
	PE_SHP_O26_AMG_SD,				///< sd
	PE_SHP_O26_AMG_UD,				///< ud
	PE_SHP_O26_AMG_NUM				///< max num
}
PE_SHP_HW_O26_AMG_FMT;
/**
 *	pe obc objt fmt(for O26X)
 */
typedef enum
{
	PE_SHP_O26_OBE_HD,				///< hd
	PE_SHP_O26_OBE_SD,				///< sd
	PE_SHP_O26_OBE_UD,				///< ud
	PE_SHP_O26_OBE_HD_TOLED,		///< hd
	PE_SHP_O26_OBE_SD_TOLED,		///< sd
	PE_SHP_O26_OBE_UD_TOLED,		///< ud
	PE_SHP_O26_OBE_NUM				///< max num
}
PE_SHP_HW_O26_OBE_FMT;


/**
 *	pe scl index type
 */
typedef struct
{
	UINT32 m_h0_id;		///< m_h0_id, H1 12t,08t..
	UINT32 m_h1_id;		///< m_h1_id, H1 n/a
	UINT32 m_v0_id;		///< m_v0_id, V1 12t,08t..
	UINT32 m_v1_id;		///< m_v1_id, V1 06t,04t..
	UINT32 s_h0_id;		///< s_h0_id, H2 adaptive filter
	UINT32 s_v0_id;		///< s_v0_id, V2 adaptive filter
}
PE_SHP_HW_O26_SCL_INDX_T;
/**
 *	pe scl ctrl type
 */
typedef struct
{
	PE_SHP_HW_O26_SCL_INDX_T idx;	///< info : index
	UINT32 h_i_size;				///< info : h_i_size
	UINT32 v_i_size;				///< info : v_i_size
	UINT32 h_active;				///< info : h_active
	UINT32 v_active;				///< info : v_active
	UINT32 h_o_size;				///< info : h_o_size
	UINT32 v_o_size;				///< info : v_o_size
	UINT32 in_c_fmt;				///< info : input color format(nd), 0x6:444,0x5:422, else 420
	UINT32 pixel_rp;				///< info : pixel replace
	UINT32 acti_fmt;				///< info : active fmt(1:seamless mode)
	UINT32 flt_v_tap;				///< ctrl : filter v tap
	UINT32 vscl_mode;				///< ctrl : v sc_mode
	UINT32 adaptv_on;				///< ctrl : adaptive mode
	UINT32 blnear_on;				///< ctrl : bilinear mode on
	UINT32 h1_co_num;				///< ctrl : h1 coeff number
	UINT32 h2_co_num;				///< ctrl : h2 coeff number
	UINT32 v1_co_num;				///< ctrl : v1 coeff number
	UINT32 v2_co_num;				///< ctrl : v2 coeff number
	UINT32 h_dwn_lvl;				///< ctrl : h scl down : 0(NA):~70%,1(1/2):69%~40%,2(1/4):39%~20%,3(1/8):19%~
	UINT32 v_dwn_lvl;				///< ctrl : v scl down : 0(NA):~70%,1(1/2):69%~40%,2(1/4):39%~20%,3(1/8):19%~
}
PE_SHP_HW_O26_SCL_CTRL_T;
/**
 *	pe scl info type
 */
typedef struct
{
	PE_SHP_HW_O26_SCL_CTRL_T g0_y;		///< m1_y, msc
	PE_SHP_HW_O26_SCL_CTRL_T g1_y;		///< m2_y, msc
	PE_SHP_HW_O26_SCL_CTRL_T g0_c;		///< m1_c, msc
	PE_SHP_HW_O26_SCL_CTRL_T g1_c;		///< m2_c, msc
	PE_SHP_HW_O26_SCL_CTRL_T p0_y;		///< mp_y, post sc
}
PE_SHP_HW_O26_SCL_INFO_T;

/**
 *	pe sharpness module settings type
 */
typedef struct
{
	PE_SHP_HW_O26_SCL_INDX_T usr_g0y_idx;				///< user g0y index, m12h,n/a,m12v,m06v, sh, sv
	PE_SHP_HW_O26_SCL_INDX_T usr_g0c_idx;				///< user p0c index, m12h,n/a,m12v,m06v,n/a,n/a
	PE_SHP_HW_O26_SCL_INDX_T usr_g1y_idx;				///< user g1y index, m08h,n/a,m08v,m04v,n/a,n/a
	PE_SHP_HW_O26_SCL_INDX_T usr_p0y_idx;				///< user p0y index, m12h,n/a,m12v,m06v, sh, sv
	PE_SHP_HW_O26_SCL_INFO_T cur_info;					///< current info
	PE_SHP_HW_O26_SCL_INFO_T pre_info;					///< previous info
	UINT32 res0a_fmt;					///< previous pe1 shp res0a fmt
	UINT32 cti0a_fmt;					///< previous dnr cti0a fmt
	UINT32 k2s0a_fmt;					///< previous sre0a fmt
	UINT32 k2s1a_fmt;					///< previous sre1a fmt
	UINT32 chr0a_fmt;					///< previous chr0a fmt
	UINT32 amg0a_fmt;					///< previous amg0a_fmt
	UINT32 obe0a_fmt;					///< previous obe0a_fmt
	UINT32 obc0a_fmt;					///< previous obc0a_fmt
	UINT32 gav0a_fmt;					///< previous gav0a_fmt
	UINT32 obc_stereo_ui;               ///< status ObcStereoCtrl ui
	UINT32 pre_face_gain_lut[4];        ///< status pre_face_gain_lut
	UINT32 pre_obj_gain_lut[4];         ///< status pre_obj_gain_lut
	UINT32 is_external_chip;		///< 4k or 8k model, 0:4k, 1:8k
	UINT32 is_toled;		        ///< 2k oled model (toled)
}
PE_SHP_HW_O26_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_SHP_HW_O26_Init(PE_CFG_CTRL_T *pstParams);
int PE_SHP_HW_O26_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_SHP_HW_O26_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_SHP_HW_O26_GetCurShpSettings(PE_SHP_HW_O26_SETTINGS_T *pstParams);
int PE_SHP_HW_O26_RdDefault(LX_PE_ETC_TBL_T *pstParams);
int PE_SHP_HW_O26_SetReCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_GetReCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetReMiscCtrl(void *pstParams);
int PE_SHP_HW_O26_GetReMiscCtrl(void *pstParams);
int PE_SHP_HW_O26_SetEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_GetEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_SetDetailEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_GetDetailEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSre2KReCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_GetSre2KReCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSre2KReMiscCtrl(void *pstParams);
int PE_SHP_HW_O26_GetSre2KReMiscCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSre2KEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_GetSre2KEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSre2KDetailEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_GetSre2KDetailEnhanceCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSreSubReCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSreSubReMiscCtrl(void *pstParams);
int PE_SHP_HW_O26_SetPblApply(PE_TSK_O26_CFG_T *pCfg);
int PE_SHP_HW_O26_DownloadSclDb(void);
int PE_SHP_HW_O26_SetObcCtrl(void *pstParams);
int PE_SHP_HW_O26_GetObcCtrl(void *pstParams);
int PE_SHP_HW_O26_SetObcLUT(void *pstParams);
int PE_SHP_HW_O26_GetObcLUT(void *pstParams);
int PE_SHP_HW_O26_GetObcData(void *pstParams);
int PE_SHP_HW_O26_DownloadShp2KSqmCmnInitDb(void);
int PE_SHP_HW_O26_DownloadShp2KSqmDetailInitDb(void);
int PE_SHP_HW_O26_DownloadShpSqmCmnInitDb(void);
int PE_SHP_HW_O26_DownloadShpSqmDetailInitDb(void);
int PE_SHP_HW_O26_SetSre2KSqmCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSre2KSqmDetailCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSqmCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSqmDetailCtrl(void *pstParams);
int PE_SHP_HW_O26_SetReEasyCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetSre2KReEasyCmnCtrl(void *pstParams);
int PE_SHP_HW_O26_SetObcStereoCtrl(void *pstParams);
int PE_SHP_HW_O26_GetShp2KSqmCmnUserDb(void *pstParams);
int PE_SHP_HW_O26_GetShp2KSqmDetailUserDb(void *pstParams);
int PE_SHP_HW_O26_GetShpSqmDetailUserDb(void *pstParams);
int PE_SHP_HW_O26_GetShpSqmCmnUserDb(void *pstParams);
int PE_SHP_HW_O26F22_DownloadSclDb(void);
int PE_SHP_HW_O26F22_SetReAllCtrl(void *pstParams);
int PE_SHP_HW_O26_SetOBCGainLUT(void);
int PE_SHP_HW_O26F22_DownloadShpSqmDetailInitDb(void);
int PE_SHP_HW_O26F22_DownloadShpSqmCmnInitDb(void);
int PE_SHP_HW_O26_SetObcMode(void);
int PE_SHP_HW_O26_SetEllipsLutCtrl(void *pstParams);
int PE_SHP_HW_O26_DownloadObcCtrlInitDb(void);
int PE_SHP_HW_O26_DownloadObcLutInitDb(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_SHP_HW_O26_H_ */
