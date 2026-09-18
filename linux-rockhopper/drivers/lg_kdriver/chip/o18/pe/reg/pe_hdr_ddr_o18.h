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

/** @file pe_hdr_ddr_o18.h
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
#ifndef _PE_HDR_DDR_O18_H_
#define _PE_HDR_DDR_O18_H_

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
/* hdr ddr version : 0x00 ~ 0xff */
#define PE_HDR_DDR_O18_VERSION			0x6

#define PE_HDR_DDR_O18_BASE_OFST		0x00200000
#define PE_HDR_DDR_O18_BASE_ADDR		(PE_O18_DDR_DB_BASE+PE_HDR_DDR_O18_BASE_OFST)

/*****************************************************************************************/
/* version.4 main */
/*****************************************************************************************/
/* index size : 0x0020 = 8x4 byte : total:32 byte */
#define PE_HDR_DDR_O18_HEADER_SIZE		0x00000020
#define PE_HDR_DDR_O18_HEADER_OFST		0x00000000
/* 3dlut size : 0x6660 = 26208 = 6552x4 (6552 = ((17x17x17)/3+1)x4) byte : total:314496 byte */
#define PE_HDR_DDR_O18_3LUT_SIZE		0x00006660
#define PE_HDR_DDR_O18_3LUT_A1_OFST		(PE_HDR_DDR_O18_HEADER_OFST +PE_HDR_DDR_O18_HEADER_SIZE)
#define PE_HDR_DDR_O18_3LUT_A2_OFST		(PE_HDR_DDR_O18_3LUT_A1_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_A3_OFST		(PE_HDR_DDR_O18_3LUT_A2_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_B1_OFST		(PE_HDR_DDR_O18_3LUT_A3_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_B2_OFST		(PE_HDR_DDR_O18_3LUT_B1_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_B3_OFST		(PE_HDR_DDR_O18_3LUT_B2_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_C1_OFST		(PE_HDR_DDR_O18_3LUT_B3_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_C2_OFST		(PE_HDR_DDR_O18_3LUT_C1_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_C3_OFST		(PE_HDR_DDR_O18_3LUT_C2_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_D1_OFST		(PE_HDR_DDR_O18_3LUT_C3_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_D2_OFST		(PE_HDR_DDR_O18_3LUT_D1_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_3LUT_D3_OFST		(PE_HDR_DDR_O18_3LUT_D2_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
/* eotf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR_O18_EOTF_SIZE		0x00001000
#define PE_HDR_DDR_O18_EOTF_A_OFST		(PE_HDR_DDR_O18_3LUT_D3_OFST+PE_HDR_DDR_O18_3LUT_SIZE)
#define PE_HDR_DDR_O18_EOTF_B_OFST		(PE_HDR_DDR_O18_EOTF_A_OFST+PE_HDR_DDR_O18_EOTF_SIZE)
#define PE_HDR_DDR_O18_EOTF_C_OFST		(PE_HDR_DDR_O18_EOTF_B_OFST+PE_HDR_DDR_O18_EOTF_SIZE)
#define PE_HDR_DDR_O18_EOTF_D_OFST		(PE_HDR_DDR_O18_EOTF_C_OFST+PE_HDR_DDR_O18_EOTF_SIZE)
/* oetf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR_O18_OETF_SIZE		0x00001000
#define PE_HDR_DDR_O18_OETF_A_OFST		(PE_HDR_DDR_O18_EOTF_D_OFST+PE_HDR_DDR_O18_EOTF_SIZE)
#define PE_HDR_DDR_O18_OETF_B_OFST		(PE_HDR_DDR_O18_OETF_A_OFST+PE_HDR_DDR_O18_OETF_SIZE)
#define PE_HDR_DDR_O18_OETF_C_OFST		(PE_HDR_DDR_O18_OETF_B_OFST+PE_HDR_DDR_O18_OETF_SIZE)
#define PE_HDR_DDR_O18_OETF_D_OFST		(PE_HDR_DDR_O18_OETF_C_OFST+PE_HDR_DDR_O18_OETF_SIZE)
/* tone map lut size  : 0x0318 = 792 = 66x3x4 byte : total:4752 byte */
#define PE_HDR_DDR_O18_TONE_SIZE		0x00000318
#define PE_HDR_DDR_O18_TONE_A_OFST		(PE_HDR_DDR_O18_OETF_D_OFST+PE_HDR_DDR_O18_OETF_SIZE)
#define PE_HDR_DDR_O18_TONE_B_OFST		(PE_HDR_DDR_O18_TONE_A_OFST+PE_HDR_DDR_O18_TONE_SIZE)
#define PE_HDR_DDR_O18_TONE_C_OFST		(PE_HDR_DDR_O18_TONE_B_OFST+PE_HDR_DDR_O18_TONE_SIZE)
#define PE_HDR_DDR_O18_TONE_D_OFST		(PE_HDR_DDR_O18_TONE_C_OFST+PE_HDR_DDR_O18_TONE_SIZE)
#define PE_HDR_DDR_O18_TONE_E_OFST		(PE_HDR_DDR_O18_TONE_D_OFST+PE_HDR_DDR_O18_TONE_SIZE)
#define PE_HDR_DDR_O18_TONE_F_OFST		(PE_HDR_DDR_O18_TONE_E_OFST+PE_HDR_DDR_O18_TONE_SIZE)
/* ygain lut size  : 0x0084 = 132 = 33x4 byte : total:264 byte */
#define PE_HDR_DDR_O18_YLUT_SIZE		0x00000084
#define PE_HDR_DDR_O18_YLUT_A_OFST		(PE_HDR_DDR_O18_TONE_F_OFST+PE_HDR_DDR_O18_TONE_SIZE)
#define PE_HDR_DDR_O18_YLUT_B_OFST		(PE_HDR_DDR_O18_YLUT_A_OFST+PE_HDR_DDR_O18_YLUT_SIZE)

/* base */
#define PE_HDR_DDR_O18_HEADER_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_HEADER_OFST)
#define PE_HDR_DDR_O18_3LUT_A1_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_A1_OFST)
#define PE_HDR_DDR_O18_3LUT_A2_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_A2_OFST)
#define PE_HDR_DDR_O18_3LUT_A3_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_A3_OFST)
#define PE_HDR_DDR_O18_3LUT_B1_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_B1_OFST)
#define PE_HDR_DDR_O18_3LUT_B2_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_B2_OFST)
#define PE_HDR_DDR_O18_3LUT_B3_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_B3_OFST)
#define PE_HDR_DDR_O18_3LUT_C1_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_C1_OFST)
#define PE_HDR_DDR_O18_3LUT_C2_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_C2_OFST)
#define PE_HDR_DDR_O18_3LUT_C3_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_C3_OFST)
#define PE_HDR_DDR_O18_3LUT_D1_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_D1_OFST)
#define PE_HDR_DDR_O18_3LUT_D2_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_D2_OFST)
#define PE_HDR_DDR_O18_3LUT_D3_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_3LUT_D3_OFST)
#define PE_HDR_DDR_O18_EOTF_A_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_EOTF_A_OFST)
#define PE_HDR_DDR_O18_EOTF_B_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_EOTF_B_OFST)
#define PE_HDR_DDR_O18_EOTF_C_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_EOTF_C_OFST)
#define PE_HDR_DDR_O18_EOTF_D_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_EOTF_D_OFST)
#define PE_HDR_DDR_O18_OETF_A_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_OETF_A_OFST)
#define PE_HDR_DDR_O18_OETF_B_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_OETF_B_OFST)
#define PE_HDR_DDR_O18_OETF_C_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_OETF_C_OFST)
#define PE_HDR_DDR_O18_OETF_D_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_OETF_D_OFST)
#define PE_HDR_DDR_O18_TONE_A_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_TONE_A_OFST)
#define PE_HDR_DDR_O18_TONE_B_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_TONE_B_OFST)
#define PE_HDR_DDR_O18_TONE_C_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_TONE_C_OFST)
#define PE_HDR_DDR_O18_TONE_D_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_TONE_D_OFST)
#define PE_HDR_DDR_O18_TONE_E_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_TONE_E_OFST)
#define PE_HDR_DDR_O18_TONE_F_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_TONE_F_OFST)
#define PE_HDR_DDR_O18_YLUT_A_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_YLUT_A_OFST)
#define PE_HDR_DDR_O18_YLUT_B_BASE		(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_O18_YLUT_B_OFST)
/*****************************************************************************************/
/* version.4 sub */
/*****************************************************************************************/
/* eotf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR_2_O18_EOTF_SIZE		PE_HDR_DDR_O18_EOTF_SIZE
#define PE_HDR_DDR_2_O18_EOTF_A_OFST	(PE_HDR_DDR_O18_YLUT_B_OFST+PE_HDR_DDR_O18_YLUT_SIZE)
#define PE_HDR_DDR_2_O18_EOTF_B_OFST	(PE_HDR_DDR_2_O18_EOTF_A_OFST+PE_HDR_DDR_2_O18_EOTF_SIZE)
#define PE_HDR_DDR_2_O18_EOTF_C_OFST	(PE_HDR_DDR_2_O18_EOTF_B_OFST+PE_HDR_DDR_2_O18_EOTF_SIZE)
#define PE_HDR_DDR_2_O18_EOTF_D_OFST	(PE_HDR_DDR_2_O18_EOTF_C_OFST+PE_HDR_DDR_2_O18_EOTF_SIZE)
/* oetf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR_2_O18_OETF_SIZE		PE_HDR_DDR_O18_OETF_SIZE
#define PE_HDR_DDR_2_O18_OETF_A_OFST	(PE_HDR_DDR_2_O18_EOTF_D_OFST+PE_HDR_DDR_2_O18_EOTF_SIZE)
#define PE_HDR_DDR_2_O18_OETF_B_OFST	(PE_HDR_DDR_2_O18_OETF_A_OFST+PE_HDR_DDR_2_O18_OETF_SIZE)
#define PE_HDR_DDR_2_O18_OETF_C_OFST	(PE_HDR_DDR_2_O18_OETF_B_OFST+PE_HDR_DDR_2_O18_OETF_SIZE)
#define PE_HDR_DDR_2_O18_OETF_D_OFST	(PE_HDR_DDR_2_O18_OETF_C_OFST+PE_HDR_DDR_2_O18_OETF_SIZE)
/* tone map lut size  : 0x0318 = 792 = 66x3x4 byte : total:4752 byte */
#define PE_HDR_DDR_2_O18_TONE_SIZE		PE_HDR_DDR_O18_TONE_SIZE
#define PE_HDR_DDR_2_O18_TONE_A_OFST	(PE_HDR_DDR_2_O18_OETF_D_OFST+PE_HDR_DDR_2_O18_OETF_SIZE)
#define PE_HDR_DDR_2_O18_TONE_B_OFST	(PE_HDR_DDR_2_O18_TONE_A_OFST+PE_HDR_DDR_2_O18_TONE_SIZE)
#define PE_HDR_DDR_2_O18_TONE_C_OFST	(PE_HDR_DDR_2_O18_TONE_B_OFST+PE_HDR_DDR_2_O18_TONE_SIZE)
#define PE_HDR_DDR_2_O18_TONE_D_OFST	(PE_HDR_DDR_2_O18_TONE_C_OFST+PE_HDR_DDR_2_O18_TONE_SIZE)
#define PE_HDR_DDR_2_O18_TONE_E_OFST	(PE_HDR_DDR_2_O18_TONE_D_OFST+PE_HDR_DDR_2_O18_TONE_SIZE)
#define PE_HDR_DDR_2_O18_TONE_F_OFST	(PE_HDR_DDR_2_O18_TONE_E_OFST+PE_HDR_DDR_2_O18_TONE_SIZE)
/* ygain lut size  : 0x0084 = 132 = 33x4 byte : total:264 byte */
#define PE_HDR_DDR_2_O18_YLUT_SIZE		PE_HDR_DDR_O18_YLUT_SIZE
#define PE_HDR_DDR_2_O18_YLUT_A_OFST	(PE_HDR_DDR_2_O18_TONE_F_OFST+PE_HDR_DDR_2_O18_TONE_SIZE)
#define PE_HDR_DDR_2_O18_YLUT_B_OFST	(PE_HDR_DDR_2_O18_YLUT_A_OFST+PE_HDR_DDR_2_O18_YLUT_SIZE)

/* total size */
#define PE_HDR_DDR_O18_TOTAL_SIZE		(PE_HDR_DDR_2_O18_YLUT_B_OFST+PE_HDR_DDR_2_O18_YLUT_SIZE)

/* base */
#define PE_HDR_DDR_2_O18_EOTF_A_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_EOTF_A_OFST)
#define PE_HDR_DDR_2_O18_EOTF_B_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_EOTF_B_OFST)
#define PE_HDR_DDR_2_O18_EOTF_C_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_EOTF_C_OFST)
#define PE_HDR_DDR_2_O18_EOTF_D_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_EOTF_D_OFST)
#define PE_HDR_DDR_2_O18_OETF_A_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_OETF_A_OFST)
#define PE_HDR_DDR_2_O18_OETF_B_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_OETF_B_OFST)
#define PE_HDR_DDR_2_O18_OETF_C_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_OETF_C_OFST)
#define PE_HDR_DDR_2_O18_OETF_D_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_OETF_D_OFST)
#define PE_HDR_DDR_2_O18_TONE_A_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_TONE_A_OFST)
#define PE_HDR_DDR_2_O18_TONE_B_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_TONE_B_OFST)
#define PE_HDR_DDR_2_O18_TONE_C_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_TONE_C_OFST)
#define PE_HDR_DDR_2_O18_TONE_D_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_TONE_D_OFST)
#define PE_HDR_DDR_2_O18_TONE_E_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_TONE_E_OFST)
#define PE_HDR_DDR_2_O18_TONE_F_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_TONE_F_OFST)
#define PE_HDR_DDR_2_O18_YLUT_A_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_YLUT_A_OFST)
#define PE_HDR_DDR_2_O18_YLUT_B_BASE	(PE_HDR_DDR_O18_BASE_ADDR+PE_HDR_DDR_2_O18_YLUT_B_OFST)
/*****************************************************************************************/
#define PE_HDR_DDR_O18_3L_CNT_MAX	(0x3)
#define PE_HDR_DDR_O18_EO_CNT_MAX	(0xf)
#define PE_HDR_DDR_O18_OE_CNT_MAX	(0xf)
#define PE_HDR_DDR_O18_TM_CNT_MAX	(0xf)
#define PE_HDR_DDR_O18_YG_CNT_MAX	(0xf)

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
 *	v.4
 */
typedef enum
{
	PE_HDR_DDR_O18_ITEM_BASE = 0,	///< base
	PE_HDR_DDR_O18_ITEM_INDEX = 0,	///< index 00
	PE_HDR_DDR_O18_ITEM_3LUT_A1,	///< 3LUT_A1
	PE_HDR_DDR_O18_ITEM_3LUT_A2,	///< 3LUT_A2
	PE_HDR_DDR_O18_ITEM_3LUT_A3,	///< 3LUT_A3
	PE_HDR_DDR_O18_ITEM_3LUT_B1,	///< 3LUT_B1
	PE_HDR_DDR_O18_ITEM_3LUT_B2,	///< 3LUT_B2
	PE_HDR_DDR_O18_ITEM_3LUT_B3,	///< 3LUT_B3
	PE_HDR_DDR_O18_ITEM_3LUT_C1,	///< 3LUT_C1
	PE_HDR_DDR_O18_ITEM_3LUT_C2,	///< 3LUT_C2
	PE_HDR_DDR_O18_ITEM_3LUT_C3,	///< 3LUT_C3
	PE_HDR_DDR_O18_ITEM_3LUT_D1,	///< 3LUT_D1 10
	PE_HDR_DDR_O18_ITEM_3LUT_D2,	///< 3LUT_D2
	PE_HDR_DDR_O18_ITEM_3LUT_D3,	///< 3LUT_D3
	PE_HDR_DDR_O18_ITEM_EOTF_A,		///< EOTF_A
	PE_HDR_DDR_O18_ITEM_EOTF_B,		///< EOTF_B
	PE_HDR_DDR_O18_ITEM_EOTF_C,		///< EOTF_C
	PE_HDR_DDR_O18_ITEM_EOTF_D,		///< EOTF_D
	PE_HDR_DDR_O18_ITEM_OETF_A,		///< OETF_A
	PE_HDR_DDR_O18_ITEM_OETF_B,		///< OETF_B
	PE_HDR_DDR_O18_ITEM_OETF_C,		///< OETF_C
	PE_HDR_DDR_O18_ITEM_OETF_D,		///< OETF_D 20
	PE_HDR_DDR_O18_ITEM_TONE_A,		///< TONE_A
	PE_HDR_DDR_O18_ITEM_TONE_B,		///< TONE_B
	PE_HDR_DDR_O18_ITEM_TONE_C,		///< TONE_C
	PE_HDR_DDR_O18_ITEM_TONE_D,		///< TONE_D
	PE_HDR_DDR_O18_ITEM_TONE_E,		///< TONE_E
	PE_HDR_DDR_O18_ITEM_TONE_F,		///< TONE_F
	PE_HDR_DDR_O18_ITEM_YLUT_A,		///< YLUT_A
	PE_HDR_DDR_O18_ITEM_YLUT_B,		///< YLUT_B
	PE_HDR_DDR_2_O18_ITEM_EOTF_A,	///< EOTF_A
	PE_HDR_DDR_2_O18_ITEM_EOTF_B,	///< EOTF_B 30
	PE_HDR_DDR_2_O18_ITEM_EOTF_C,	///< EOTF_C
	PE_HDR_DDR_2_O18_ITEM_EOTF_D,	///< EOTF_D
	PE_HDR_DDR_2_O18_ITEM_OETF_A,	///< OETF_A
	PE_HDR_DDR_2_O18_ITEM_OETF_B,	///< OETF_B
	PE_HDR_DDR_2_O18_ITEM_OETF_C,	///< OETF_C
	PE_HDR_DDR_2_O18_ITEM_OETF_D,	///< OETF_D
	PE_HDR_DDR_2_O18_ITEM_TONE_A,	///< TONE_A
	PE_HDR_DDR_2_O18_ITEM_TONE_B,	///< TONE_B
	PE_HDR_DDR_2_O18_ITEM_TONE_C,	///< TONE_C
	PE_HDR_DDR_2_O18_ITEM_TONE_D,	///< TONE_D 40
	PE_HDR_DDR_2_O18_ITEM_TONE_E,	///< TONE_E
	PE_HDR_DDR_2_O18_ITEM_TONE_F,	///< TONE_F
	PE_HDR_DDR_2_O18_ITEM_YLUT_A,	///< YLUT_A
	PE_HDR_DDR_2_O18_ITEM_YLUT_B,	///< YLUT_B
	PE_HDR_DDR_O18_ITEM_V4_MAX		///< max num(v.4)
}
PE_HDR_DDR_O18_ITEM;

/**
 *	pe hdr ddr header0
 *	v.6
 */
typedef struct
{
	UINT32 version      :8 ;  // 7: 0
	UINT32 support      :8 ;  //15: 8
	UINT32 idx_3lut_a   :4 ;  //19:16
	UINT32 idx_3lut_b   :4 ;  //23:20
	UINT32 idx_3lut_c   :4 ;  //27:24
	UINT32 idx_3lut_d   :4 ;  //31:28
}PE_HDR_DDR_O18_HEADER0_T;

/**
 *	pe hdr ddr header1
 *	v.4
 */
typedef struct
{
	UINT32 cnt_eotf_a   :4 ;  // 3: 0
	UINT32 cnt_eotf_b   :4 ;  // 7: 4
	UINT32 cnt_eotf_c   :4 ;  //11: 8
	UINT32 cnt_eotf_d   :4 ;  //15:12
	UINT32 cnt_oetf_a   :4 ;  //19:16
	UINT32 cnt_oetf_b   :4 ;  //23:20
	UINT32 cnt_oetf_c   :4 ;  //27:24
	UINT32 cnt_oetf_d   :4 ;  //31:28
}PE_HDR_DDR_O18_HEADER1_T;

/**
 *	pe hdr ddr header2
 *	v.4
 */
typedef struct
{
	UINT32 cnt_tone_a   :4 ;  // 3: 0
	UINT32 cnt_tone_b   :4 ;  // 7: 4
	UINT32 cnt_tone_c   :4 ;  //11: 8
	UINT32 cnt_tone_d   :4 ;  //15:12
	UINT32 cnt_tone_e   :4 ;  //19:16
	UINT32 cnt_tone_f   :4 ;  //23:20
	UINT32 cnt_ylut_a   :4 ;  //27:24
	UINT32 cnt_ylut_b   :4 ;  //31:28
}PE_HDR_DDR_O18_HEADER2_T;
/**
 *	pe hdr ddr header3
 *	v.4
 */
typedef struct
{
	UINT32 reserved     :32;  //31: 0
}PE_HDR_DDR_O18_HEADER3_T;
/**
 *	pe hdr ddr header4
 *	v.4
 */
typedef struct
{
	UINT32 cnt_eotf_a   :4 ;  // 3: 0
	UINT32 cnt_eotf_b   :4 ;  // 7: 4
	UINT32 cnt_eotf_c   :4 ;  //11: 8
	UINT32 cnt_eotf_d   :4 ;  //15:12
	UINT32 cnt_oetf_a   :4 ;  //19:16
	UINT32 cnt_oetf_b   :4 ;  //23:20
	UINT32 cnt_oetf_c   :4 ;  //27:24
	UINT32 cnt_oetf_d   :4 ;  //31:28
}PE_HDR_DDR_O18_HEADER4_T;

/**
 *	pe hdr ddr header5
 *	v.4
 */
typedef struct
{
	UINT32 cnt_tone_a   :4 ;  // 3: 0
	UINT32 cnt_tone_b   :4 ;  // 7: 4
	UINT32 cnt_tone_c   :4 ;  //11: 8
	UINT32 cnt_tone_d   :4 ;  //15:12
	UINT32 cnt_tone_e   :4 ;  //19:16
	UINT32 cnt_tone_f   :4 ;  //23:20
	UINT32 cnt_ylut_a   :4 ;  //27:24
	UINT32 cnt_ylut_b   :4 ;  //31:28
}PE_HDR_DDR_O18_HEADER5_T;

#if 0
/**
 *	pe hdr ddr item enumeration
 *	v.2,v.3
 */
typedef enum
{
	PE_HDR_DDR_O18_ITEM_BASE = 0,		///< base
	PE_HDR_DDR_O18_ITEM_INDEX = 0,		///< index
	PE_HDR_DDR_O18_ITEM_3D_SDR1,		///< 3D_SDR1
	PE_HDR_DDR_O18_ITEM_3D_SDR2,		///< 3D_SDR2
	PE_HDR_DDR_O18_ITEM_3D_SDR3,		///< 3D_SDR3
	PE_HDR_DDR_O18_ITEM_3D_HDR1,		///< 3D_HDR1
	PE_HDR_DDR_O18_ITEM_3D_HDR2,		///< 3D_HDR2
	PE_HDR_DDR_O18_ITEM_3D_HDR3,		///< 3D_HDR3
	PE_HDR_DDR_O18_ITEM_3D_HLG1,		///< 3D_HLG1
	PE_HDR_DDR_O18_ITEM_3D_HLG2,		///< 3D_HLG2
	PE_HDR_DDR_O18_ITEM_3D_HLG3,		///< 3D_HLG3
	PE_HDR_DDR_O18_ITEM_3D_S2H1,		///< 3D_S2H1
	PE_HDR_DDR_O18_ITEM_3D_S2H2,		///< 3D_S2H2
	PE_HDR_DDR_O18_ITEM_3D_S2H3,		///< 3D_S2H3
	PE_HDR_DDR_O18_ITEM_EOTF_SDR,		///< EOTF_SDR
	PE_HDR_DDR_O18_ITEM_EOTF_HDR,		///< EOTF_HDR
	PE_HDR_DDR_O18_ITEM_EOTF_HLG,		///< EOTF_HLG
	PE_HDR_DDR_O18_ITEM_EOTF_S2H,		///< EOTF_S2H
	PE_HDR_DDR_O18_ITEM_OETF_SDR,		///< OETF_SDR
	PE_HDR_DDR_O18_ITEM_OETF_HDR,		///< OETF_HDR
	PE_HDR_DDR_O18_ITEM_OETF_HLG,		///< OETF_HLG
	PE_HDR_DDR_O18_ITEM_OETF_S2H,		///< OETF_S2H
	PE_HDR_DDR_O18_ITEM_TONE_SDR,		///< TONE_SDR
	PE_HDR_DDR_O18_ITEM_TONE_HDR,		///< TONE_HDR
	PE_HDR_DDR_O18_ITEM_TONE_HLG,		///< TONE_HLG
	PE_HDR_DDR_O18_ITEM_TONE_S2H,		///< TONE_S2H
	PE_HDR_DDR_O18_ITEM_EOTF_DFA,		///< EOTF_DFA
	PE_HDR_DDR_O18_ITEM_EOTF_DFB,		///< EOTF_DFB
	PE_HDR_DDR_O18_ITEM_EOTF_DFC,		///< EOTF_DFC
	PE_HDR_DDR_O18_ITEM_EOTF_DFD,		///< EOTF_DFD
	PE_HDR_DDR_O18_ITEM_MAX				///< max num(v.3)
}
PE_HDR_DDR_O18_ITEM;

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
}PE_HDR_DDR_O18_HEADER0_T;
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
}PE_HDR_DDR_O18_HEADER1_T;
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
}PE_HDR_DDR_O18_HEADER2_T;
/**
 *	pe hdr ddr header2
 *	v.3
 */
typedef struct
{
	UINT32 cnt_eotf_dft   :4 ;  // 3: 0
}PE_HDR_DDR_O18_HEADER3_T;
#endif

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_HDR_DDR_O18_H_ */

