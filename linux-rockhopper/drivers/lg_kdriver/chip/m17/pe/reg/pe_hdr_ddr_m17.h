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

/** @file pe_hdr_ddr_m17.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.17
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef _PE_HDR_DDR_M17_H_
#define _PE_HDR_DDR_M17_H_

#include "pe_hdr_ddr_m17c0.h"
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
/* hdr ddr version : 0x00 ~ 0xff */
#define PE_HDR_DDR_M17_VERSION			0x3

#define PE_HDR_DDR_M17_BASE_OFST		0x00200000
#define PE_HDR_DDR_M17_BASE_ADDR		(PE_M17_DDR_DB_BASE+PE_HDR_DDR_M17_BASE_OFST)

/*****************************************************************************************/
/* version.1 */
/*****************************************************************************************/
/* index size : 0x0010 = 4x4 */
#define PE_HDR_DDR_M17_INDEX_SIZE		0x00000010
#define PE_HDR_DDR_M17_INDEX_OFST		0x00000000
/* 3dlut size : 0x6660 = 26208 = 6552x4 (6552 = ((17x17x17)/3+1)x4) */
#define PE_HDR_DDR_M17_3D_LUT_SIZE		0x00006660
#define PE_HDR_DDR_M17_3D_LUT1_OFST		(PE_HDR_DDR_M17_INDEX_OFST+PE_HDR_DDR_M17_INDEX_SIZE)
#define PE_HDR_DDR_M17_3D_LUT2_OFST		(PE_HDR_DDR_M17_3D_LUT1_OFST+PE_HDR_DDR_M17_3D_LUT_SIZE)
#define PE_HDR_DDR_M17_3D_LUT3_OFST		(PE_HDR_DDR_M17_3D_LUT2_OFST+PE_HDR_DDR_M17_3D_LUT_SIZE)
/* eotf,oetf lut size : 0x1000 = 4096 = 1024x4 */
#define PE_HDR_DDR_M17_EOTF_LUT_SIZE	0x00001000
#define PE_HDR_DDR_M17_EOTF_LUT_OFST	(PE_HDR_DDR_M17_3D_LUT3_OFST+PE_HDR_DDR_M17_3D_LUT_SIZE)
#define PE_HDR_DDR_M17_OETF_LUT_SIZE	0x00001000
#define PE_HDR_DDR_M17_OETF_LUT_OFST	(PE_HDR_DDR_M17_EOTF_LUT_OFST+PE_HDR_DDR_M17_EOTF_LUT_SIZE)
/* tone map lut size  : 0x0084 = 132 = 33x4 */
#define PE_HDR_DDR_M17_TONE_LUT_SIZE	0x00000084
#define PE_HDR_DDR_M17_TONE_LUT0_OFST	(PE_HDR_DDR_M17_OETF_LUT_OFST+PE_HDR_DDR_M17_OETF_LUT_SIZE)
#define PE_HDR_DDR_M17_TONE_LUT1_OFST	(PE_HDR_DDR_M17_TONE_LUT0_OFST+PE_HDR_DDR_M17_TONE_LUT_SIZE)
#define PE_HDR_DDR_M17_TONE_LUT2_OFST	(PE_HDR_DDR_M17_TONE_LUT1_OFST+PE_HDR_DDR_M17_TONE_LUT_SIZE)
/* total size */
#define PE_HDR_DDR_M17_TOTAL_SIZE		(PE_HDR_DDR_M17_TONE_LUT2_OFST+PE_HDR_DDR_M17_TONE_LUT_SIZE)

/* base(version.1) */
#define PE_HDR_DDR_M17_INDEX_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_INDEX_OFST)
#define PE_HDR_DDR_M17_3D_LUT1_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_3D_LUT1_OFST)
#define PE_HDR_DDR_M17_3D_LUT2_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_3D_LUT2_OFST)
#define PE_HDR_DDR_M17_3D_LUT3_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_3D_LUT3_OFST)
#define PE_HDR_DDR_M17_EOTF_LUT_BASE	(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_EOTF_LUT_OFST)
#define PE_HDR_DDR_M17_OETF_LUT_BASE	(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_OETF_LUT_OFST)
#define PE_HDR_DDR_M17_TONE_LUT0_BASE	(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_TONE_LUT0_OFST)
#define PE_HDR_DDR_M17_TONE_LUT1_BASE	(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_TONE_LUT1_OFST)
#define PE_HDR_DDR_M17_TONE_LUT2_BASE	(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_TONE_LUT2_OFST)
/*****************************************************************************************/

/*****************************************************************************************/
/* version.2 */
/*****************************************************************************************/
/* index size : 0x0020 = 8x4 */
#define PE_HDR_DDR_M17_V2_HEADER_SIZE		0x00000020
#define PE_HDR_DDR_M17_V2_HEADER_OFST		0x00000000
/* 3dlut size : 0x6660 = 26208 = 6552x4 (6552 = ((17x17x17)/3+1)x4) */
#define PE_HDR_DDR_M17_V2_3D_SIZE			0x00006660
#define PE_HDR_DDR_M17_V2_3D_SDR1_OFST		(PE_HDR_DDR_M17_V2_HEADER_OFST +PE_HDR_DDR_M17_V2_HEADER_SIZE)
#define PE_HDR_DDR_M17_V2_3D_SDR2_OFST		(PE_HDR_DDR_M17_V2_3D_SDR1_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_SDR3_OFST		(PE_HDR_DDR_M17_V2_3D_SDR2_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_HDR1_OFST		(PE_HDR_DDR_M17_V2_3D_SDR3_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_HDR2_OFST		(PE_HDR_DDR_M17_V2_3D_HDR1_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_HDR3_OFST		(PE_HDR_DDR_M17_V2_3D_HDR2_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_HLG1_OFST		(PE_HDR_DDR_M17_V2_3D_HDR3_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_HLG2_OFST		(PE_HDR_DDR_M17_V2_3D_HLG1_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_HLG3_OFST		(PE_HDR_DDR_M17_V2_3D_HLG2_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_S2H1_OFST		(PE_HDR_DDR_M17_V2_3D_HLG3_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_S2H2_OFST		(PE_HDR_DDR_M17_V2_3D_S2H1_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_3D_S2H3_OFST		(PE_HDR_DDR_M17_V2_3D_S2H2_OFST+PE_HDR_DDR_M17_V2_3D_SIZE)
/* eotf,oetf lut size : 0x1000 = 4096 = 1024x4 */
#define PE_HDR_DDR_M17_V2_EOTF_SIZE			0x00001000
#define PE_HDR_DDR_M17_V2_EOTF_SDR_OFST		(PE_HDR_DDR_M17_V2_3D_S2H3_OFST +PE_HDR_DDR_M17_V2_3D_SIZE)
#define PE_HDR_DDR_M17_V2_EOTF_HDR_OFST		(PE_HDR_DDR_M17_V2_EOTF_SDR_OFST+PE_HDR_DDR_M17_V2_EOTF_SIZE)
#define PE_HDR_DDR_M17_V2_EOTF_HLG_OFST		(PE_HDR_DDR_M17_V2_EOTF_HDR_OFST+PE_HDR_DDR_M17_V2_EOTF_SIZE)
#define PE_HDR_DDR_M17_V2_EOTF_S2H_OFST		(PE_HDR_DDR_M17_V2_EOTF_HLG_OFST+PE_HDR_DDR_M17_V2_EOTF_SIZE)
#define PE_HDR_DDR_M17_V2_OETF_SIZE			0x00001000
#define PE_HDR_DDR_M17_V2_OETF_SDR_OFST		(PE_HDR_DDR_M17_V2_EOTF_S2H_OFST+PE_HDR_DDR_M17_V2_EOTF_SIZE)
#define PE_HDR_DDR_M17_V2_OETF_HDR_OFST		(PE_HDR_DDR_M17_V2_OETF_SDR_OFST+PE_HDR_DDR_M17_V2_OETF_SIZE)
#define PE_HDR_DDR_M17_V2_OETF_HLG_OFST		(PE_HDR_DDR_M17_V2_OETF_HDR_OFST+PE_HDR_DDR_M17_V2_OETF_SIZE)
#define PE_HDR_DDR_M17_V2_OETF_S2H_OFST		(PE_HDR_DDR_M17_V2_OETF_HLG_OFST+PE_HDR_DDR_M17_V2_OETF_SIZE)
/* tone map lut size  : 0x018c = 396 = 99x4 */
#define PE_HDR_DDR_M17_V2_TONE_SIZE			0x0000018c
#define PE_HDR_DDR_M17_V2_TONE_SDR_OFST		(PE_HDR_DDR_M17_V2_OETF_S2H_OFST+PE_HDR_DDR_M17_V2_OETF_SIZE)
#define PE_HDR_DDR_M17_V2_TONE_HDR_OFST		(PE_HDR_DDR_M17_V2_TONE_SDR_OFST+PE_HDR_DDR_M17_V2_TONE_SIZE)
#define PE_HDR_DDR_M17_V2_TONE_HLG_OFST		(PE_HDR_DDR_M17_V2_TONE_HDR_OFST+PE_HDR_DDR_M17_V2_TONE_SIZE)
#define PE_HDR_DDR_M17_V2_TONE_S2H_OFST		(PE_HDR_DDR_M17_V2_TONE_HLG_OFST+PE_HDR_DDR_M17_V2_TONE_SIZE)
/* total size */
#define PE_HDR_DDR_M17_V2_TOTAL_SIZE		(PE_HDR_DDR_M17_V2_TONE_S2H_OFST+PE_HDR_DDR_M17_V2_TONE_SIZE)

/* base(version.2) */
#define PE_HDR_DDR_M17_V2_HEADER_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_HEADER_OFST)
#define PE_HDR_DDR_M17_V2_3D_SDR1_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_SDR1_OFST)
#define PE_HDR_DDR_M17_V2_3D_SDR2_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_SDR2_OFST)
#define PE_HDR_DDR_M17_V2_3D_SDR3_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_SDR3_OFST)
#define PE_HDR_DDR_M17_V2_3D_HDR1_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_HDR1_OFST)
#define PE_HDR_DDR_M17_V2_3D_HDR2_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_HDR2_OFST)
#define PE_HDR_DDR_M17_V2_3D_HDR3_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_HDR3_OFST)
#define PE_HDR_DDR_M17_V2_3D_HLG1_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_HLG1_OFST)
#define PE_HDR_DDR_M17_V2_3D_HLG2_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_HLG2_OFST)
#define PE_HDR_DDR_M17_V2_3D_HLG3_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_HLG3_OFST)
#define PE_HDR_DDR_M17_V2_3D_S2H1_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_S2H1_OFST)
#define PE_HDR_DDR_M17_V2_3D_S2H2_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_S2H2_OFST)
#define PE_HDR_DDR_M17_V2_3D_S2H3_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_3D_S2H3_OFST)
#define PE_HDR_DDR_M17_V2_EOTF_SDR_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_EOTF_SDR_OFST)
#define PE_HDR_DDR_M17_V2_EOTF_HDR_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_EOTF_HDR_OFST)
#define PE_HDR_DDR_M17_V2_EOTF_HLG_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_EOTF_HLG_OFST)
#define PE_HDR_DDR_M17_V2_EOTF_S2H_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_EOTF_S2H_OFST)
#define PE_HDR_DDR_M17_V2_OETF_SDR_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_OETF_SDR_OFST)
#define PE_HDR_DDR_M17_V2_OETF_HDR_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_OETF_HDR_OFST)
#define PE_HDR_DDR_M17_V2_OETF_HLG_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_OETF_HLG_OFST)
#define PE_HDR_DDR_M17_V2_OETF_S2H_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_OETF_S2H_OFST)
#define PE_HDR_DDR_M17_V2_TONE_SDR_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_TONE_SDR_OFST)
#define PE_HDR_DDR_M17_V2_TONE_HDR_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_TONE_HDR_OFST)
#define PE_HDR_DDR_M17_V2_TONE_HLG_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_TONE_HLG_OFST)
#define PE_HDR_DDR_M17_V2_TONE_S2H_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V2_TONE_S2H_OFST)
/*****************************************************************************************/

/*****************************************************************************************/
/* version.3 */
/*****************************************************************************************/
#define PE_HDR_DDR_M17_V3_EOTF_SIZE			0x00001000
#define PE_HDR_DDR_M17_V3_EOTF_DFA_OFST		(PE_HDR_DDR_M17_V2_TONE_S2H_OFST+PE_HDR_DDR_M17_V2_TONE_SIZE)
#define PE_HDR_DDR_M17_V3_EOTF_DFB_OFST		(PE_HDR_DDR_M17_V3_EOTF_DFA_OFST+PE_HDR_DDR_M17_V3_EOTF_SIZE)
#define PE_HDR_DDR_M17_V3_EOTF_DFC_OFST		(PE_HDR_DDR_M17_V3_EOTF_DFB_OFST+PE_HDR_DDR_M17_V3_EOTF_SIZE)
#define PE_HDR_DDR_M17_V3_EOTF_DFD_OFST		(PE_HDR_DDR_M17_V3_EOTF_DFC_OFST+PE_HDR_DDR_M17_V3_EOTF_SIZE)
/* total size */
#define PE_HDR_DDR_M17_V3_TOTAL_SIZE		(PE_HDR_DDR_M17_V3_EOTF_DFD_OFST+PE_HDR_DDR_M17_V3_EOTF_SIZE)

#define PE_HDR_DDR_M17_V3_EOTF_DFA_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V3_EOTF_DFA_OFST)
#define PE_HDR_DDR_M17_V3_EOTF_DFB_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V3_EOTF_DFB_OFST)
#define PE_HDR_DDR_M17_V3_EOTF_DFC_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V3_EOTF_DFC_OFST)
#define PE_HDR_DDR_M17_V3_EOTF_DFD_BASE		(PE_HDR_DDR_M17_BASE_ADDR+PE_HDR_DDR_M17_V3_EOTF_DFD_OFST)
/*****************************************************************************************/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
 *	pe hdr ddr item enumeration
 *	v.1
 */
typedef enum
{
	PE_HDR_DDR_M17_ITEM_BASE = 0,							///< base
	PE_HDR_DDR_M17_ITEM_INDEX = PE_HDR_DDR_M17_ITEM_BASE,	///< index
	PE_HDR_DDR_M17_ITEM_3D_LUT1,							///< 3d lut1
	PE_HDR_DDR_M17_ITEM_3D_LUT2,							///< 3d lut2
	PE_HDR_DDR_M17_ITEM_3D_LUT3,							///< 3d lut3
	PE_HDR_DDR_M17_ITEM_EOTF_LUT,							///< eotf lut
	PE_HDR_DDR_M17_ITEM_OETF_LUT,							///< oetf lut
	PE_HDR_DDR_M17_ITEM_TONE_LUT0,							///< tone lut0
	PE_HDR_DDR_M17_ITEM_TONE_LUT1,							///< tone lut1
	PE_HDR_DDR_M17_ITEM_TONE_LUT2,							///< tone lut2
	PE_HDR_DDR_M17_ITEM_MAX									///< max num
}
PE_HDR_DDR_M17_ITEM;

/**
 *	pe hdr ddr item enumeration
 *	v.2,v.3
 */
typedef enum
{
	PE_HDR_DDR_M17_V2_ITEM_BASE = 0,								///< base
	PE_HDR_DDR_M17_V2_ITEM_INDEX = PE_HDR_DDR_M17_V2_ITEM_BASE,		///< index
	PE_HDR_DDR_M17_V2_ITEM_3D_SDR1,									///< 3D_SDR1
	PE_HDR_DDR_M17_V2_ITEM_3D_SDR2,									///< 3D_SDR2
	PE_HDR_DDR_M17_V2_ITEM_3D_SDR3,									///< 3D_SDR3
	PE_HDR_DDR_M17_V2_ITEM_3D_HDR1,									///< 3D_HDR1
	PE_HDR_DDR_M17_V2_ITEM_3D_HDR2,									///< 3D_HDR2
	PE_HDR_DDR_M17_V2_ITEM_3D_HDR3,									///< 3D_HDR3
	PE_HDR_DDR_M17_V2_ITEM_3D_HLG1,									///< 3D_HLG1
	PE_HDR_DDR_M17_V2_ITEM_3D_HLG2,									///< 3D_HLG2
	PE_HDR_DDR_M17_V2_ITEM_3D_HLG3,									///< 3D_HLG3
	PE_HDR_DDR_M17_V2_ITEM_3D_S2H1,									///< 3D_S2H1
	PE_HDR_DDR_M17_V2_ITEM_3D_S2H2,									///< 3D_S2H2
	PE_HDR_DDR_M17_V2_ITEM_3D_S2H3,									///< 3D_S2H3
	PE_HDR_DDR_M17_V2_ITEM_EOTF_SDR,								///< EOTF_SDR
	PE_HDR_DDR_M17_V2_ITEM_EOTF_HDR,								///< EOTF_HDR
	PE_HDR_DDR_M17_V2_ITEM_EOTF_HLG,								///< EOTF_HLG
	PE_HDR_DDR_M17_V2_ITEM_EOTF_S2H,								///< EOTF_S2H
	PE_HDR_DDR_M17_V2_ITEM_OETF_SDR,								///< OETF_SDR
	PE_HDR_DDR_M17_V2_ITEM_OETF_HDR,								///< OETF_HDR
	PE_HDR_DDR_M17_V2_ITEM_OETF_HLG,								///< OETF_HLG
	PE_HDR_DDR_M17_V2_ITEM_OETF_S2H,								///< OETF_S2H
	PE_HDR_DDR_M17_V2_ITEM_TONE_SDR,								///< TONE_SDR
	PE_HDR_DDR_M17_V2_ITEM_TONE_HDR,								///< TONE_HDR
	PE_HDR_DDR_M17_V2_ITEM_TONE_HLG,								///< TONE_HLG
	PE_HDR_DDR_M17_V2_ITEM_TONE_S2H,								///< TONE_S2H
	PE_HDR_DDR_M17_V2_ITEM_MAX,										///< max num(v.2)
	PE_HDR_DDR_M17_V3_ITEM_EOTF_DFA = PE_HDR_DDR_M17_V2_ITEM_MAX,	///< EOTF_DFA
	PE_HDR_DDR_M17_V3_ITEM_EOTF_DFB,								///< EOTF_DFB
	PE_HDR_DDR_M17_V3_ITEM_EOTF_DFC,								///< EOTF_DFC
	PE_HDR_DDR_M17_V3_ITEM_EOTF_DFD,								///< EOTF_DFD
	PE_HDR_DDR_M17_V3_ITEM_MAX										///< max num(v.3)
}
PE_HDR_DDR_M17_V2_ITEM;

/**
 *	pe hdr ddr index0
 *	v.1
 */
typedef struct
{
	UINT32 version       :8 ;  // 7: 0
	UINT32 tridlutidx    :2 ;  // 9: 8
	UINT32 tonelutcnt    :6 ;  //15:10
	UINT32 eotflutcnt    :4 ;  //19:16
	UINT32 oetflutcnt    :4 ;  //23:20
	UINT32 reserved      :8 ;  //31:24
}PE_HDR_DDR_M17_INDEX0_T;

/**
 *	pe hdr ddr header0
 *	v.2
 */
typedef struct
{
	UINT32 version        :16;  //15: 0
	UINT32 idx_3d_sdr     :4 ;  //19:16
	UINT32 idx_3d_hdr     :4 ;  //23:20
	UINT32 idx_3d_hlg     :4 ;  //27:24
	UINT32 idx_3d_s2h     :4 ;  //31:28
}PE_HDR_DDR_M17_HEADER0_T;
/**
 *	pe hdr ddr header1
 *	v.2
 */
typedef struct
{
	UINT32 cnt_eotf_sdr   :4 ;  // 3: 0
	UINT32 cnt_eotf_hdr   :4 ;  // 7: 4
	UINT32 cnt_eotf_hlg   :4 ;  //11: 8
	UINT32 cnt_eotf_s2h   :4 ;  //15:12
	UINT32 cnt_oetf_sdr   :4 ;  //19:16
	UINT32 cnt_oetf_hdr   :4 ;  //23:20
	UINT32 cnt_oetf_hlg   :4 ;  //27:24
	UINT32 cnt_oetf_s2h   :4 ;  //31:28
}PE_HDR_DDR_M17_HEADER1_T;
/**
 *	pe hdr ddr header2
 *	v.2
 */
typedef struct
{
	UINT32 cnt_tone_sdr   :8 ;  // 7: 0
	UINT32 cnt_tone_hdr   :8 ;  //15: 8
	UINT32 cnt_tone_hlg   :8 ;  //23:16
	UINT32 cnt_tone_s2h   :8 ;  //31:24
}PE_HDR_DDR_M17_HEADER2_T;
/**
 *	pe hdr ddr header2
 *	v.3
 */
typedef struct
{
	UINT32 cnt_eotf_dft   :4 ;  // 3: 0
}PE_HDR_DDR_M17_HEADER3_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_HDR_DDR_M17_H_ */

