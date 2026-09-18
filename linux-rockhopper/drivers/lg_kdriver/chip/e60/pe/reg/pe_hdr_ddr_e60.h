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

/** @file pe_hdr_ddr_e60.h
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
#ifndef _PE_HDR_DDR_E60_H_
#define _PE_HDR_DDR_E60_H_

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
/* hdr ddr version : 0x00 ~ 0xff */
#define PE_HDR_DDR_E60_VERSION			0x7

#define PE_HDR_DDR_E60_BASE_ADDR		(PE_E60_DDR_DB1_BASE)

/*****************************************************************************************/
/* version.7 main */
/*****************************************************************************************/
/* index size : 0x0020 = 8x4 byte : total:32 byte */
#define PE_HDR_DDR_E60_HEADER_SIZE		0x00000020
#define PE_HDR_DDR_E60_HEADER_OFST		0x00000000
/* info size : 0x0400 = 1024 = 256x4 byte : total:12288 byte */
#define PE_HDR_DDR_E60_INFO_SIZE		0x00000800
#define PE_HDR_DDR_E60_INFO_A1_OFST		(PE_HDR_DDR_E60_HEADER_OFST +PE_HDR_DDR_E60_HEADER_SIZE)
#define PE_HDR_DDR_E60_INFO_A2_OFST		(PE_HDR_DDR_E60_INFO_A1_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_A3_OFST		(PE_HDR_DDR_E60_INFO_A2_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_B1_OFST		(PE_HDR_DDR_E60_INFO_A3_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_B2_OFST		(PE_HDR_DDR_E60_INFO_B1_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_B3_OFST		(PE_HDR_DDR_E60_INFO_B2_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_C1_OFST		(PE_HDR_DDR_E60_INFO_B3_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_C2_OFST		(PE_HDR_DDR_E60_INFO_C1_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_C3_OFST		(PE_HDR_DDR_E60_INFO_C2_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_D1_OFST		(PE_HDR_DDR_E60_INFO_C3_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_D2_OFST		(PE_HDR_DDR_E60_INFO_D1_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR_E60_INFO_D3_OFST		(PE_HDR_DDR_E60_INFO_D2_OFST+PE_HDR_DDR_E60_INFO_SIZE)
/* eotf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR0_E60_EOTF_SIZE		0x00001000
#define PE_HDR_DDR0_E60_EOTF_A_OFST		(PE_HDR_DDR_E60_INFO_D3_OFST+PE_HDR_DDR_E60_INFO_SIZE)
#define PE_HDR_DDR0_E60_EOTF_B_OFST		(PE_HDR_DDR0_E60_EOTF_A_OFST+PE_HDR_DDR0_E60_EOTF_SIZE)
#define PE_HDR_DDR0_E60_EOTF_C_OFST		(PE_HDR_DDR0_E60_EOTF_B_OFST+PE_HDR_DDR0_E60_EOTF_SIZE)
#define PE_HDR_DDR0_E60_EOTF_D_OFST		(PE_HDR_DDR0_E60_EOTF_C_OFST+PE_HDR_DDR0_E60_EOTF_SIZE)
/* oetf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR0_E60_OETF_SIZE		0x00001000
#define PE_HDR_DDR0_E60_OETF_A_OFST		(PE_HDR_DDR0_E60_EOTF_D_OFST+PE_HDR_DDR0_E60_EOTF_SIZE)
#define PE_HDR_DDR0_E60_OETF_B_OFST		(PE_HDR_DDR0_E60_OETF_A_OFST+PE_HDR_DDR0_E60_OETF_SIZE)
#define PE_HDR_DDR0_E60_OETF_C_OFST		(PE_HDR_DDR0_E60_OETF_B_OFST+PE_HDR_DDR0_E60_OETF_SIZE)
#define PE_HDR_DDR0_E60_OETF_D_OFST		(PE_HDR_DDR0_E60_OETF_C_OFST+PE_HDR_DDR0_E60_OETF_SIZE)
/* tone map lut size  : 0x0318 = 792 = 66x3x4 byte : total:4752 byte */
#define PE_HDR_DDR0_E60_TONE_SIZE		0x00000318
#define PE_HDR_DDR0_E60_TONE_A_OFST		(PE_HDR_DDR0_E60_OETF_D_OFST+PE_HDR_DDR0_E60_OETF_SIZE)
#define PE_HDR_DDR0_E60_TONE_B_OFST		(PE_HDR_DDR0_E60_TONE_A_OFST+PE_HDR_DDR0_E60_TONE_SIZE)
#define PE_HDR_DDR0_E60_TONE_C_OFST		(PE_HDR_DDR0_E60_TONE_B_OFST+PE_HDR_DDR0_E60_TONE_SIZE)
#define PE_HDR_DDR0_E60_TONE_D_OFST		(PE_HDR_DDR0_E60_TONE_C_OFST+PE_HDR_DDR0_E60_TONE_SIZE)
#define PE_HDR_DDR0_E60_TONE_E_OFST		(PE_HDR_DDR0_E60_TONE_D_OFST+PE_HDR_DDR0_E60_TONE_SIZE)
#define PE_HDR_DDR0_E60_TONE_F_OFST		(PE_HDR_DDR0_E60_TONE_E_OFST+PE_HDR_DDR0_E60_TONE_SIZE)
/* ygain lut size  : 0x0084 = 132 = 33x4 byte : total:264 byte */
#define PE_HDR_DDR0_E60_YLUT_SIZE		0x00000084
#define PE_HDR_DDR0_E60_YLUT_A_OFST		(PE_HDR_DDR0_E60_TONE_F_OFST+PE_HDR_DDR0_E60_TONE_SIZE)
#define PE_HDR_DDR0_E60_YLUT_B_OFST		(PE_HDR_DDR0_E60_YLUT_A_OFST+PE_HDR_DDR0_E60_YLUT_SIZE)

/* base */
#define PE_HDR_DDR_E60_HEADER_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_HEADER_OFST)

#define PE_HDR_DDR0_E60_INF_A1_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_A1_OFST)
#define PE_HDR_DDR0_E60_INF_A2_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_A2_OFST)
#define PE_HDR_DDR0_E60_INF_A3_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_A3_OFST)
#define PE_HDR_DDR0_E60_INF_B1_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_B1_OFST)
#define PE_HDR_DDR0_E60_INF_B2_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_B2_OFST)
#define PE_HDR_DDR0_E60_INF_B3_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_B3_OFST)
#define PE_HDR_DDR0_E60_INF_C1_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_C1_OFST)
#define PE_HDR_DDR0_E60_INF_C2_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_C2_OFST)
#define PE_HDR_DDR0_E60_INF_C3_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_C3_OFST)
#define PE_HDR_DDR0_E60_INF_D1_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_D1_OFST)
#define PE_HDR_DDR0_E60_INF_D2_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_D2_OFST)
#define PE_HDR_DDR0_E60_INF_D3_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR_E60_INFO_D3_OFST)

#define PE_HDR_DDR0_E60_EOTF_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_EOTF_A_OFST)
#define PE_HDR_DDR0_E60_EOTF_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_EOTF_B_OFST)
#define PE_HDR_DDR0_E60_EOTF_C_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_EOTF_C_OFST)
#define PE_HDR_DDR0_E60_EOTF_D_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_EOTF_D_OFST)
#define PE_HDR_DDR0_E60_OETF_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_OETF_A_OFST)
#define PE_HDR_DDR0_E60_OETF_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_OETF_B_OFST)
#define PE_HDR_DDR0_E60_OETF_C_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_OETF_C_OFST)
#define PE_HDR_DDR0_E60_OETF_D_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_OETF_D_OFST)
#define PE_HDR_DDR0_E60_TONE_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_TONE_A_OFST)
#define PE_HDR_DDR0_E60_TONE_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_TONE_B_OFST)
#define PE_HDR_DDR0_E60_TONE_C_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_TONE_C_OFST)
#define PE_HDR_DDR0_E60_TONE_D_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_TONE_D_OFST)
#define PE_HDR_DDR0_E60_TONE_E_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_TONE_E_OFST)
#define PE_HDR_DDR0_E60_TONE_F_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_TONE_F_OFST)
#define PE_HDR_DDR0_E60_YLUT_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_YLUT_A_OFST)
#define PE_HDR_DDR0_E60_YLUT_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR0_E60_YLUT_B_OFST)

/*****************************************************************************************/
/* version.4 sub */
/*****************************************************************************************/
/* eotf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR1_E60_EOTF_SIZE		PE_HDR_DDR0_E60_EOTF_SIZE
#define PE_HDR_DDR1_E60_EOTF_A_OFST		(PE_HDR_DDR0_E60_YLUT_B_OFST+PE_HDR_DDR0_E60_YLUT_SIZE)
#define PE_HDR_DDR1_E60_EOTF_B_OFST		(PE_HDR_DDR1_E60_EOTF_A_OFST+PE_HDR_DDR1_E60_EOTF_SIZE)
#define PE_HDR_DDR1_E60_EOTF_C_OFST		(PE_HDR_DDR1_E60_EOTF_B_OFST+PE_HDR_DDR1_E60_EOTF_SIZE)
#define PE_HDR_DDR1_E60_EOTF_D_OFST		(PE_HDR_DDR1_E60_EOTF_C_OFST+PE_HDR_DDR1_E60_EOTF_SIZE)
/* oetf lut size : 0x1000 = 4096 = 1024x4 byte : total:16384 byte */
#define PE_HDR_DDR1_E60_OETF_SIZE		PE_HDR_DDR0_E60_OETF_SIZE
#define PE_HDR_DDR1_E60_OETF_A_OFST		(PE_HDR_DDR1_E60_EOTF_D_OFST+PE_HDR_DDR1_E60_EOTF_SIZE)
#define PE_HDR_DDR1_E60_OETF_B_OFST		(PE_HDR_DDR1_E60_OETF_A_OFST+PE_HDR_DDR1_E60_OETF_SIZE)
#define PE_HDR_DDR1_E60_OETF_C_OFST		(PE_HDR_DDR1_E60_OETF_B_OFST+PE_HDR_DDR1_E60_OETF_SIZE)
#define PE_HDR_DDR1_E60_OETF_D_OFST		(PE_HDR_DDR1_E60_OETF_C_OFST+PE_HDR_DDR1_E60_OETF_SIZE)
/* tone map lut size  : 0x0318 = 792 = 66x3x4 byte : total:4752 byte */
#define PE_HDR_DDR1_E60_TONE_SIZE		PE_HDR_DDR0_E60_TONE_SIZE
#define PE_HDR_DDR1_E60_TONE_A_OFST		(PE_HDR_DDR1_E60_OETF_D_OFST+PE_HDR_DDR1_E60_OETF_SIZE)
#define PE_HDR_DDR1_E60_TONE_B_OFST		(PE_HDR_DDR1_E60_TONE_A_OFST+PE_HDR_DDR1_E60_TONE_SIZE)
#define PE_HDR_DDR1_E60_TONE_C_OFST		(PE_HDR_DDR1_E60_TONE_B_OFST+PE_HDR_DDR1_E60_TONE_SIZE)
#define PE_HDR_DDR1_E60_TONE_D_OFST		(PE_HDR_DDR1_E60_TONE_C_OFST+PE_HDR_DDR1_E60_TONE_SIZE)
#define PE_HDR_DDR1_E60_TONE_E_OFST		(PE_HDR_DDR1_E60_TONE_D_OFST+PE_HDR_DDR1_E60_TONE_SIZE)
#define PE_HDR_DDR1_E60_TONE_F_OFST		(PE_HDR_DDR1_E60_TONE_E_OFST+PE_HDR_DDR1_E60_TONE_SIZE)
/* ygain lut size  : 0x0084 = 132 = 33x4 byte : total:264 byte */
#define PE_HDR_DDR1_E60_YLUT_SIZE		PE_HDR_DDR0_E60_YLUT_SIZE
#define PE_HDR_DDR1_E60_YLUT_A_OFST		(PE_HDR_DDR1_E60_TONE_F_OFST+PE_HDR_DDR1_E60_TONE_SIZE)
#define PE_HDR_DDR1_E60_YLUT_B_OFST		(PE_HDR_DDR1_E60_YLUT_A_OFST+PE_HDR_DDR1_E60_YLUT_SIZE)

/* total size */
#define PE_HDR_DDR_E60_TOTAL_SIZE		(PE_HDR_DDR1_E60_YLUT_B_OFST+PE_HDR_DDR1_E60_YLUT_SIZE)

/* base */
#define PE_HDR_DDR1_E60_EOTF_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_EOTF_A_OFST)
#define PE_HDR_DDR1_E60_EOTF_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_EOTF_B_OFST)
#define PE_HDR_DDR1_E60_EOTF_C_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_EOTF_C_OFST)
#define PE_HDR_DDR1_E60_EOTF_D_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_EOTF_D_OFST)
#define PE_HDR_DDR1_E60_OETF_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_OETF_A_OFST)
#define PE_HDR_DDR1_E60_OETF_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_OETF_B_OFST)
#define PE_HDR_DDR1_E60_OETF_C_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_OETF_C_OFST)
#define PE_HDR_DDR1_E60_OETF_D_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_OETF_D_OFST)
#define PE_HDR_DDR1_E60_TONE_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_TONE_A_OFST)
#define PE_HDR_DDR1_E60_TONE_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_TONE_B_OFST)
#define PE_HDR_DDR1_E60_TONE_C_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_TONE_C_OFST)
#define PE_HDR_DDR1_E60_TONE_D_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_TONE_D_OFST)
#define PE_HDR_DDR1_E60_TONE_E_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_TONE_E_OFST)
#define PE_HDR_DDR1_E60_TONE_F_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_TONE_F_OFST)
#define PE_HDR_DDR1_E60_YLUT_A_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_YLUT_A_OFST)
#define PE_HDR_DDR1_E60_YLUT_B_BASE		(PE_HDR_DDR_E60_BASE_ADDR+PE_HDR_DDR1_E60_YLUT_B_OFST)
/*****************************************************************************************/
#define PE_HDR_DDR_E60_IF_CNT_MAX	(0x3)
#define PE_HDR_DDR_E60_EO_CNT_MAX	(0xf)
#define PE_HDR_DDR_E60_OE_CNT_MAX	(0xf)
#define PE_HDR_DDR_E60_TM_CNT_MAX	(0xf)
#define PE_HDR_DDR_E60_YG_CNT_MAX	(0xf)

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
 *	v.7
 */
typedef enum
{
	PE_HDR_DDR_E60_ITEM_BASE = 0,
	PE_HDR_DDR_E60_ITEM_INDEX = 0,
	PE_HDR_DDR0_E60_ITEM_INF_A1,
	PE_HDR_DDR0_E60_ITEM_INF_A2,
	PE_HDR_DDR0_E60_ITEM_INF_A3,
	PE_HDR_DDR0_E60_ITEM_INF_B1,
	PE_HDR_DDR0_E60_ITEM_INF_B2,
	PE_HDR_DDR0_E60_ITEM_INF_B3,
	PE_HDR_DDR0_E60_ITEM_INF_C1,
	PE_HDR_DDR0_E60_ITEM_INF_C2,
	PE_HDR_DDR0_E60_ITEM_INF_C3,
	PE_HDR_DDR0_E60_ITEM_INF_D1,
	PE_HDR_DDR0_E60_ITEM_INF_D2,
	PE_HDR_DDR0_E60_ITEM_INF_D3,
	PE_HDR_DDR0_E60_ITEM_EOTF_A,
	PE_HDR_DDR0_E60_ITEM_EOTF_B,
	PE_HDR_DDR0_E60_ITEM_EOTF_C,
	PE_HDR_DDR0_E60_ITEM_EOTF_D,
	PE_HDR_DDR0_E60_ITEM_OETF_A,
	PE_HDR_DDR0_E60_ITEM_OETF_B,
	PE_HDR_DDR0_E60_ITEM_OETF_C,
	PE_HDR_DDR0_E60_ITEM_OETF_D,
	PE_HDR_DDR0_E60_ITEM_TONE_A,
	PE_HDR_DDR0_E60_ITEM_TONE_B,
	PE_HDR_DDR0_E60_ITEM_TONE_C,
	PE_HDR_DDR0_E60_ITEM_TONE_D,
	PE_HDR_DDR0_E60_ITEM_TONE_E,
	PE_HDR_DDR0_E60_ITEM_TONE_F,
	PE_HDR_DDR0_E60_ITEM_YLUT_A,
	PE_HDR_DDR0_E60_ITEM_YLUT_B,
	PE_HDR_DDR1_E60_ITEM_EOTF_A,
	PE_HDR_DDR1_E60_ITEM_EOTF_B,
	PE_HDR_DDR1_E60_ITEM_EOTF_C,
	PE_HDR_DDR1_E60_ITEM_EOTF_D,
	PE_HDR_DDR1_E60_ITEM_OETF_A,
	PE_HDR_DDR1_E60_ITEM_OETF_B,
	PE_HDR_DDR1_E60_ITEM_OETF_C,
	PE_HDR_DDR1_E60_ITEM_OETF_D,
	PE_HDR_DDR1_E60_ITEM_TONE_A,
	PE_HDR_DDR1_E60_ITEM_TONE_B,
	PE_HDR_DDR1_E60_ITEM_TONE_C,
	PE_HDR_DDR1_E60_ITEM_TONE_D,
	PE_HDR_DDR1_E60_ITEM_TONE_E,
	PE_HDR_DDR1_E60_ITEM_TONE_F,
	PE_HDR_DDR1_E60_ITEM_YLUT_A,
	PE_HDR_DDR1_E60_ITEM_YLUT_B,
	PE_HDR_DDR_E60_ITEM_V07_MAX
}
PE_HDR_DDR_E60_ITEM;

/**
 *	pe hdr ddr header0
 *	v.7
 */
typedef struct
{
	UINT32 version      :8 ;  // 7: 0
	UINT32 support      :8 ;  //15: 8
	UINT32 cnt_info_a   :4 ;  //19:16
	UINT32 cnt_info_b   :4 ;  //23:20
	UINT32 cnt_info_c   :4 ;  //27:24
	UINT32 cnt_info_d   :4 ;  //31:28
}PE_HDR_DDR_E60_HEADER0_T;

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
}PE_HDR_DDR_E60_HEADER1_T;

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
}PE_HDR_DDR_E60_HEADER2_T;
/**
 *	pe hdr ddr header3
 *	v.4
 */
typedef struct
{
	UINT32 reserved     :32;  //31: 0
}PE_HDR_DDR_E60_HEADER3_T;
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
}PE_HDR_DDR_E60_HEADER4_T;

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
}PE_HDR_DDR_E60_HEADER5_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_HDR_DDR_E60_H_ */

