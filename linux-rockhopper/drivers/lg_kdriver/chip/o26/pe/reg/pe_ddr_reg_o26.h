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

/** @file pe_ddr_reg_o26.h
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
#ifndef _PE_DDR_REG_O26_H_
#define _PE_DDR_REG_O26_H_
#include "pe_vsd_reg_o26a0.h"
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
/**
* version history
* 0x1 : 20150507, 1st edition
*/
#define PE_DDR_O26_DB_VER					(0x3)

#define PE_DDR_O26_SEC_MAX_SIZE             60

#ifndef PE_DRC_LUT_SIZE
#define PE_DRC_LUT_SIZE		1185
#endif

/*LX_PE_CM_GLOBAL_POINT + LX_PE_CM_LOCAL_POINT +2 +
	LX_PE_CM_FREE_POINT x LX_PE_CM_LOCAL_CURVE_FW x 4 */
#define PE_DRC_O26_FW_LUT_SIZE		156
/*LX_PE_CM_GLOBAL_POINT + LX_PE_CM_LOCAL_POINT +2 +
	LX_PE_CM_FREE_POINT x LX_PE_CM_LOCAL_CURVE_FW2 x 4 */
#define PE_DRC_O26_FW_LUT_SIZE2		276


/* section size */
#define PE_DDR_O26_MODE_SIZE                1
#define PE_DDR_O26_DRC_LUT_SIZE             PE_DRC_LUT_SIZE
#define PE_DDR_O26_SCL_12T_FLT_SIZE         896
#define PE_DDR_O26_SCL_08T_FLT_SIZE         640
#define PE_DDR_O26_SCL_04T_FLT_SIZE         384
#define PE_DDR_O26_SCL_GAV_FLT_SIZE			(PE_DDR_O26_SCL_12T_FLT_SIZE*4+PE_DDR_O26_SCL_08T_FLT_SIZE*2)

#define PE_DDR_O26_TNR_LUT_SIZE             45
/* cnt:1 + ui:1 + lut_lm:16 + gain:5 + tmp:15*/
#define PE_DDR_O26_TNR_USER_SIZE            38
#define PE_DDR_O26_CVD_DFLT_SIZE            145
#define PE_DDR_O26_DRC_CURV_SIZE            PE_DRC_O26_FW_LUT_SIZE
#define PE_DDR_O26_DRC_CURV_SIZE2           PE_DRC_O26_FW_LUT_SIZE2
/* cnt:1 + ui:1 + tmp:8*/
#define PE_DDR_O26_DNR_USER_SIZE            (1+1+8)
#define PE_DDR_O26_DCNT_USER_SIZE           (1+1+8)
#define PE_DDR_O26_DCNT_LED_USER_SIZE           (1+1+8)

/* cnt:1 + ui:1 + sqm:11*/
#define PE_DDR_O26_TNR_SQM_SIZE             (1+1+11)

/* cnt:1 + ui:1 + sqm:17 - o26*/
//#define PE_DDR_O26_DNR_SQM_SIZE             (1+1+19)
#define PE_DDR_O26_DNR_SQM_SIZE             (1+1+17)
#define PE_DDR_O26_DNR2ND_SQM_SIZE          (1+1+15)


/* cnt:1 + ui:1 + sqm:23 -> 27 SICREQ-530*/
#define PE_DDR_O26_DCNT_SQM_SIZE            (1+1+27)

/* cnt:1 + ui:1 + sqm:35*/
#define PE_DDR_O26_CCODCNT_SQM_SIZE            (1+1+35)

/* cnt:1 + ui:1 + sqm:49 -> 57 TVPLAT-598870*/
#define PE_DDR_O26_SHP_UI_SQM_2K_SIZE       (1+1+57) 

/* cnt:1 + ui:1 + sqm:51 -> 59 TVPLAT-598870*/
#define PE_DDR_O26_SHP_SQM_CMN_2K_SIZE      (1+1+59)

/* cnt:1 + ui:1 + sqm:50 -> 65 TVPLAT-598870*/
#define PE_DDR_O26_SHP_UI_SQM_VSD_SIZE      (1+1+65)

/* cnt:1 + ui:1 + sqm:71 ->87 TVPLAT-598870*/
#define PE_DDR_O26_SHP_SQM_CMN_VSD_SIZE     (1+1+87)

/* idx:1 + bin:32 x 3 ea */
#define PE_DDR_O26_HST_SRC_Y_SIZE     (1+32+32+32)

/* item number */
#define PE_DDR_O26_MODE_ITEM_NUM            1
#define PE_DDR_O26_DRC_LUT_ITEM_NUM         4
#define PE_DDR_O26_CVD_DFLT_ITEM_NUM        12
#if 0
#define PE_DDR_O26_SCL_12T_M_ITEM_NUM       (17+2)
#define PE_DDR_O26_SCL_12T_H_ITEM_NUM       (2+2)
#define PE_DDR_O26_SCL_08T_F_ITEM_NUM       (11+2)
#define PE_DDR_O26_SCL_08T_H_ITEM_NUM       (2+2)
#define PE_DDR_O26_SCL_04T_F_ITEM_NUM       (9+2)
#define PE_DDR_O26_SCL_04T_H_ITEM_NUM       (2+2)
//#else
#define PE_DDR_O26_SCL_12T_M_ITEM_NUM       17
#define PE_DDR_O26_SCL_12T_H_ITEM_NUM       2
#define PE_DDR_O26_SCL_08T_F_ITEM_NUM       11
#define PE_DDR_O26_SCL_08T_H_ITEM_NUM       2
#define PE_DDR_O26_SCL_04T_F_ITEM_NUM       9
#define PE_DDR_O26_SCL_04T_H_ITEM_NUM       2
#endif
#define PE_DDR_O26_TNR_LUT_ITEM_NUM         4
#define PE_DDR_O26_TNR_USER_ITEM_NUM        1
#define PE_DDR_O26_DRC_CURV_ITEM_NUM        1
/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_DDR_REG_O26_SEC_TYPE_TO_STR(_x)		(\
	((_x)==PE_DDR_O26_SEC_MODE     )? "MODE     ":\
	((_x)==PE_DDR_O26_SEC_CVD_DFLT )? "CVD_DFLT ":\
	((_x)==PE_DDR_O26_SEC_SCL_1212T)? "SCL_1212T":\
	((_x)==PE_DDR_O26_SEC_SCL_1208T)? "SCL_1208T":\
	((_x)==PE_DDR_O26_SEC_SCL_1206T)? "SCL_1206T":\
	((_x)==PE_DDR_O26_SEC_SCL_1204T)? "SCL_1204T":\
	((_x)==PE_DDR_O26_SEC_SCL_1202T)? "SCL_1202T":\
	((_x)==PE_DDR_O26_SEC_SCL_0808T)? "SCL_0808T":\
	((_x)==PE_DDR_O26_SEC_SCL_0806T)? "SCL_0806T":\
	((_x)==PE_DDR_O26_SEC_SCL_0804T)? "SCL_0804T":\
	((_x)==PE_DDR_O26_SEC_SCL_0802T)? "SCL_0802T":\
	((_x)==PE_DDR_O26_SEC_SCL_0404T)? "SCL_0404T":\
	((_x)==PE_DDR_O26_SEC_SCL_0402T)? "SCL_0402T":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE01)? "GAV_CASE01":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE02)? "GAV_CASE02":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE03)? "GAV_CASE03":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE04)? "GAV_CASE04":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE05)? "GAV_CASE05":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE06)? "GAV_CASE06":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE07)? "GAV_CASE07":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE08)? "GAV_CASE08":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE09)? "GAV_CASE09":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE10)? "GAV_CASE10":\
	((_x)==PE_DDR_O26_SEC_SCL_CASE11)? "GAV_CASE11":\
	((_x)==PE_DDR_O26_SEC_TNR_LUT  )? "TNR_LUT  ":\
	((_x)==PE_DDR_O26_SEC_TNR_USER )? "TNR_USER ":\
	((_x)==PE_DDR_O26_SEC_DRC_CURV )? "DRC_CURV ":\
	((_x)==PE_DDR_O26_SEC_TNR2ND_USER     )? "TNR2ND_USER    ":\
	((_x)==PE_DDR_O26_SEC_DNR_USER        )? "DNR_USER       ":\
	((_x)==PE_DDR_O26_SEC_DNR_DCNT_USER   )? "DNR_DCNT_USER  ":\
	((_x)==PE_DDR_O26_SEC_LED_DCNT_USER   )? "LED_DCNT_USER  ":\
	((_x)==PE_DDR_O26_SEC_TNR_SQM         )? "TNR_SQM        ":\
	((_x)==PE_DDR_O26_SEC_TNR2ND_SQM      )? "TNR2ND_SQM     ":\
	((_x)==PE_DDR_O26_SEC_DNR_SQM         )? "DNR_SQM        ":\
	((_x)==PE_DDR_O26_SEC_DNR_DCNT_SQM    )? "DNR_DCNT_SQM   ":\
	((_x)==PE_DDR_O26_SEC_SHP_UI_SQM_2K   )? "SHP_UI_SQM_2K  ":\
	((_x)==PE_DDR_O26_SEC_SHP_SQM_CMN_2K  )? "SHP_SQM_CMN_2K ":\
	((_x)==PE_DDR_O26_SEC_SHP_UI_SQM_VSD  )? "SHP_UI_SQM_VSD ":\
	((_x)==PE_DDR_O26_SEC_SHP_SQM_CMN_VSD )? "SHP_SQM_CMN_VSD":\
	((_x)==PE_DDR_O26_SEC_CCO_DCNT_SQM    )? "CCO_DCNT_SQM   ":\
	((_x)==PE_DDR_O26_SEC_TNR3RD_USER     )? "TNR3RD_USER    ":\
	((_x)==PE_DDR_O26_SEC_DNR2ND_USER     )? "DNR2ND_USER    ":\
	((_x)==PE_DDR_O26_SEC_DNR_DCNT2ND_USER)? "DNR_DCNT2ND_USER":\
	((_x)==PE_DDR_O26_SEC_TNR3RD_SQM      )? "TNR3RD_SQM     ":\
	((_x)==PE_DDR_O26_SEC_DNR2ND_SQM      )? "DNR2ND_SQM     ":\
	((_x)==PE_DDR_O26_SEC_DNR_DCNT2ND_SQM )? "DNR_DCNT2ND_SQM":\
	((_x)==PE_DDR_O26_SEC_HST_SCR_Y       )? "HST_SCR_Y":\
	((_x)==PE_DDR_O26_SEC_OBC_CTRL        )? "OBC_CTRL":\
	((_x)==PE_DDR_O26_SEC_OBC_LUT         )? "OBC_LUT":\
	"SEC_NUM  ")

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
* section type enum
* - causion : should be PE_DDR_O26_SEC_NUM < PE_DDR_O26_SEC_MAX_SIZE
*/
typedef enum
{
	PE_DDR_O26_SEC_MODE            =  0,  ///< mode
	PE_DDR_O26_SEC_CVD_DFLT        =  1,  ///< cvd default
	PE_DDR_O26_SEC_SCL_1212T       =  2,  ///< msc 12_12tap
	PE_DDR_O26_SEC_SCL_1208T       =  3,  ///< msc 12_08tap
	PE_DDR_O26_SEC_SCL_1206T       =  4,  ///< msc 12_06tap
	PE_DDR_O26_SEC_SCL_1204T       =  5,  ///< msc 12_04ap
	PE_DDR_O26_SEC_SCL_1202T       =  6,  ///< msc 12_02_ap
	PE_DDR_O26_SEC_SCL_0808T       =  7,  ///< msc 08_04tap
	PE_DDR_O26_SEC_SCL_0806T       =  8,  ///< msc 08_04tap
	PE_DDR_O26_SEC_SCL_0804T       =  9,  ///< msc 08_04tap
	PE_DDR_O26_SEC_SCL_0802T       = 10,  ///< msc 08_04tap
	PE_DDR_O26_SEC_SCL_0404T       = 11,  ///< msc 04_04tap
	PE_DDR_O26_SEC_SCL_0402T       = 12,  ///< msc 04_02tap
	PE_DDR_O26_SEC_SCL_CASE01      = 13,  ///< scl case01 12t_06t_0610 + 12t_06t_0610 + 12t_06t_0610 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE02      = 14,  ///< scl case02 12t_04t_0008 + 12t_04t_0008 + 12t_04t_0308 + 12t_04t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE03      = 15,  ///< scl case03 12t_04t_0008 + 12t_04t_0008 + 12t_04t_0008 + 12t_04t_0008 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE04      = 16,  ///< scl case04 12t_12t_0004 + 12t_12t_0004 + 12t_06t_0610 + 12t_06t_0610 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE05      = 17,  ///< scl case05 12t_12t_0006 + 12t_12t_0006 + 12t_04t_0308 + 12t_04t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE06      = 18,  ///< scl case06 12t_12t_0004 + 12t_12t_0004 + 12t_12t_0306 + 12t_12t_0306 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE07      = 19,  ///< scl case07 12t_12t_0304 + 12t_12t_0304 + 12t_12t_0306 + 12t_12t_0306 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE08      = 20,  ///< scl case08 12t_12t_0104 + 12t_12t_0104 + 12t_12t_0306 + 12t_12t_0306 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE09      = 21,  ///< scl case09 12t_04t_0910 + 12t_04t_0910 + 12t_02t_0308 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE10      = 22,  ///< scl case10 12t_04t_1410 + 12t_04t_1410 + 12t_02t_0308 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_SCL_CASE11      = 23,  ///< scl case11 12t_04t_1510 + 12t_04t_1510 + 12t_02t_0308 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SEC_TNR_LUT         = 24,  ///< tnr lut
	PE_DDR_O26_SEC_TNR_USER        = 25,  ///< tnr user
	PE_DDR_O26_SEC_DRC_CURV        = 26,  ///< drc lut
	PE_DDR_O26_SEC_TNR2ND_USER     = 27,  ///< tnr2nd user
	PE_DDR_O26_SEC_DNR_USER        = 28,  ///< dnr_user
	PE_DDR_O26_SEC_DNR_DCNT_USER   = 29,  ///< dnr_dcnt_user
	PE_DDR_O26_SEC_LED_DCNT_USER   = 30,  ///< led_dcnt_user
	PE_DDR_O26_SEC_TNR_SQM         = 31,  ///< tnr_sqm
	PE_DDR_O26_SEC_TNR2ND_SQM      = 32,  ///< tnr2nd_sqm
	PE_DDR_O26_SEC_DNR_SQM         = 33,  ///< dnr_sqm
	PE_DDR_O26_SEC_DNR_DCNT_SQM    = 34,  ///< dnr_dcnt_sqm
	PE_DDR_O26_SEC_SHP_UI_SQM_2K   = 35,  ///< shp_ui_sqm_2k
	PE_DDR_O26_SEC_SHP_SQM_CMN_2K  = 36,  ///< shp_sqm_cmn_2k
	PE_DDR_O26_SEC_SHP_UI_SQM_VSD  = 37,  ///< shp_ui_sqm_vsd
	PE_DDR_O26_SEC_SHP_SQM_CMN_VSD = 38,  ///< shp_sqm_cmn_vsd
	PE_DDR_O26_SEC_CCO_DCNT_SQM    = 39,  ///< cco_dcnt_sqm
	PE_DDR_O26_SEC_TNR3RD_USER     = 40,  ///< tnr3rd user
	PE_DDR_O26_SEC_DNR2ND_USER     = 41,  ///< dnr2nd_user
	PE_DDR_O26_SEC_DNR_DCNT2ND_USER= 42,  ///< dnr_dcnt2nd_user
	PE_DDR_O26_SEC_TNR3RD_SQM      = 43,  ///< tnr3rd sqm
	PE_DDR_O26_SEC_DNR2ND_SQM      = 44,  ///< dnr2nd_sqm
	PE_DDR_O26_SEC_DNR_DCNT2ND_SQM = 45,  ///< dnr_dcnt2nd_sqm
	PE_DDR_O26_SEC_HST_SCR_Y       = 46,  ///< src hsitogram y
	PE_DDR_O26_SEC_OBC_CTRL        = 47,  ///< V4L2_CID_EXT_VPQ_OBC_CTRL
	PE_DDR_O26_SEC_OBC_LUT         = 48,  ///< V4L2_CID_EXT_VPQ_OBC_LUT
	PE_DDR_O26_SEC_NUM                    ///< max num
}
PE_DDR_O26_SEC_TYPE;

typedef enum
{
	PE_DDR_O26_1212T_FLT_0004		=  0,
	PE_DDR_O26_1212T_FLT_0006		=  1,
	PE_DDR_O26_1212T_FLT_0104		=  2,
	PE_DDR_O26_1212T_FLT_0304		=  3,
	PE_DDR_O26_1212T_FLT_0306		=  4,
	PE_DDR_O26_1212T_FLT_0404		=  5,
	PE_DDR_O26_1212T_FLT_0406		=  6,
	PE_DDR_O26_1212T_FLT_0606		=  7,
	PE_DDR_O26_1212T_FLT_0806		=  8,
	PE_DDR_O26_1212T_FLT_0808		=  9,
	PE_DDR_O26_1212T_FLT_1006		= 10,
	PE_DDR_O26_1212T_FLT_1410		= 11,
	PE_DDR_O26_1212T_FLT_DUMY0      = 12,
	PE_DDR_O26_1212T_FLT_DUMY1 		= 13,
	PE_DDR_O26_1212T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_1212T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_1208T_FLT_0004	=  0,
	PE_DDR_O26_1208T_FLT_0006	=  1,
	PE_DDR_O26_1208T_FLT_0104	=  2,
	PE_DDR_O26_1208T_FLT_0304	=  3,
	PE_DDR_O26_1208T_FLT_0306	=  4,
	PE_DDR_O26_1208T_FLT_0606	=  5,
	PE_DDR_O26_1208T_FLT_0806	=  6,
	PE_DDR_O26_1208T_FLT_1410	=  7,
	PE_DDR_O26_1208T_FLT_DUMY0  =  8,
	PE_DDR_O26_1208T_FLT_DUMY1  =  9,
	PE_DDR_O26_1208T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_1208T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_1206T_FLT_0006	=  0,
	PE_DDR_O26_1206T_FLT_0306	=  1,
	PE_DDR_O26_1206T_FLT_0610   =  2,
	PE_DDR_O26_1206T_FLT_DUMY0  =  3,
	PE_DDR_O26_1206T_FLT_DUMY1  =  4,
	PE_DDR_O26_1206T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_1206T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_1204T_FLT_0006	=  0,
	PE_DDR_O26_1204T_FLT_0008	=  1,
	PE_DDR_O26_1204T_FLT_0306   =  2,
	PE_DDR_O26_1204T_FLT_0308	=  3,
	PE_DDR_O26_1204T_FLT_0406	=  4,
	PE_DDR_O26_1204T_FLT_0606	=  5,
	PE_DDR_O26_1204T_FLT_0808	=  6,
	PE_DDR_O26_1204T_FLT_0910	=  7,
	PE_DDR_O26_1204T_FLT_1410	=  8,
	PE_DDR_O26_1204T_FLT_1510	=  9,
	PE_DDR_O26_1204T_FLT_0610	= 10,
	PE_DDR_O26_1204T_FLT_repeat = 11,
	PE_DDR_O26_1204T_FLT_DUMY1  = 12,
	PE_DDR_O26_1204T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_1204T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_1202T_FLT_0308	=  0,
	PE_DDR_O26_1202T_FLT_DUMY0  =  1,
	PE_DDR_O26_1202T_FLT_DUMY1  =  2,
	PE_DDR_O26_1202T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_1202T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_0808T_FLT_0004		=  0,
	PE_DDR_O26_0808T_FLT_0606		=  1,
	PE_DDR_O26_0808T_FLT_DUMY0		=  2,
	PE_DDR_O26_0808T_FLT_DUMY1		=  3,
	PE_DDR_O26_0808T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_0808T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_0806T_FLT_0306		=  0,
	PE_DDR_O26_0806T_FLT_0610		=  1,
	PE_DDR_O26_0806T_FLT_DUMY0		=  2,
	PE_DDR_O26_0806T_FLT_DUMY1		=  3,
	PE_DDR_O26_0806T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_0806T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_0804T_FLT_0008		=  0,
	PE_DDR_O26_0804T_FLT_0308		=  1,
	PE_DDR_O26_0804T_FLT_0910		=  2,
	PE_DDR_O26_0804T_FLT_1410		=  3,
	PE_DDR_O26_0804T_FLT_1510		=  4,
	PE_DDR_O26_0804T_FLT_0610		=  5,
	PE_DDR_O26_0804T_FLT_0306		=  6,
	PE_DDR_O26_0804T_FLT_DUMY0		=  7,
	PE_DDR_O26_0804T_FLT_DUMY1		=  8,
	PE_DDR_O26_0804T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_0804T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_0802T_FLT_0308		=  0,
	PE_DDR_O26_0802T_FLT_DUMY0		=  1,
	PE_DDR_O26_0802T_FLT_DUMY1		=  2,
	PE_DDR_O26_0802T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_0802T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_0404T_FLT_0308		=  0,
	PE_DDR_O26_0404T_FLT_0910		=  1,
	PE_DDR_O26_0404T_FLT_1410		=  2,
	PE_DDR_O26_0404T_FLT_1510		=  3,
	PE_DDR_O26_0404T_FLT_0610		=  4,
	PE_DDR_O26_0404T_FLT_0008		=  5,
	PE_DDR_O26_0404T_FLT_DUMY0		=  6,
	PE_DDR_O26_0404T_FLT_DUMY1		=  7,
	PE_DDR_O26_0404T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_0404T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_0402T_FLT_0308		=  0,
	PE_DDR_O26_0402T_FLT_DUMY0		=  1,
	PE_DDR_O26_0402T_FLT_DUMY1		=  2,
	PE_DDR_O26_0402T_FLT_NUM                  ///< max num
}
PE_DDR_O26_SCL_0402T_FLT_TYPE;

typedef enum
{
	PE_DDR_O26_G0_MULTIRUN_FLT_00	=  0,
	PE_DDR_O26_G0_MULTIRUN_FLT_01	=  1,
	PE_DDR_O26_G0_MULTIRUN_FLT_02   =  2,
	PE_DDR_O26_G0_MULTIRUN_FLT_03	=  3,
	PE_DDR_O26_G0_MULTIRUN_FLT_04	=  4,
	PE_DDR_O26_G0_MULTIRUN_FLT_05	=  5,
	PE_DDR_O26_G0_MULTIRUN_FLT_06	=  6,
	PE_DDR_O26_G0_MULTIRUN_FLT_07	=  7,
	PE_DDR_O26_G0_MULTIRUN_FLT_08	=  8,
	PE_DDR_O26_G0_MULTIRUN_FLT_09	=  9,
	PE_DDR_O26_G0_MULTIRUN_FLT_10	= 10,
	PE_DDR_O26_G0_MULTIRUN_FLT_NUM                  ///< max num
}PE_DDR_O26_SCL_G0_MULTIRUN_FLT_TYPE;




/**
* top header type
* - sec_num : PE_DDR_O26_SEC_NUM
* - sec_base[N+1] = sec_base[N] + [N]header + ([N]item_num * [N]item_size)
*   ([N]header = sizeof(PE_DDR_O26_HEADER_T))
*/
typedef struct
{
	UINT32 version;      ///< version
	UINT32 db_base;      ///< db base addr
	UINT32 sec_num;      ///< section max number
	UINT32 sec_base[PE_DDR_O26_SEC_MAX_SIZE];   ///< each section start base
	UINT32 sec_size[PE_DDR_O26_SEC_MAX_SIZE];   ///< each section start size
}
PE_DDR_O26_TOP_HEADER_T;

/**
* header type
* - sec_type : see PE_DDR_O26_SEC_TYPE 
*/
typedef struct
{
	UINT32 version;    ///< version
	UINT32 sec_type;   ///< section type
	UINT32 item_num;   ///< item number
	UINT32 item_size;  ///< item size
}
PE_DDR_O26_HEADER_T;

/**
 *	mode0
 */
typedef struct
{
	UINT32 shp_fw_en        : 1;   ///< 0, shp fw enable, just ready
	UINT32 hst_fw_en        : 1;   ///< 1, hst fw enable, just ready
	UINT32 scl_fw_en        : 1;   ///< 2, scl fw enable
	UINT32 tnr_fw_en        : 1;   ///< 3, tnr fw enable
	UINT32 dnr_fw_en        : 1;   ///< 4, dnr fw enable
	UINT32 dct_fw_en        : 1;   ///< 5, dcontorue fw enable
	UINT32 obc_fw_en        : 1;   ///< 6, obc fw enable
}
PE_DDR_O26_MD0_T;

/**
* mode
* - header.item_num = PE_DDR_O26_MODE_ITEM_NUM
* - header.item_size = PE_DDR_O26_MODE_SIZE
* - data, see PE_DDR_O26_MD0_T
*
* version history :
* 0x1 : 20140827, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_MODE_ITEM_NUM*PE_DDR_O26_MODE_SIZE]; ///< data
}
PE_DDR_O26_MODE_T;

/**
* cvd default type
* - header.item_num = PE_DDR_O26_CVD_DFLT_ITEM_NUM
* - header.item_size = PE_DDR_O26_CVD_DFLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_CVD_DFLT_ITEM_NUM*PE_DDR_O26_CVD_DFLT_SIZE]; ///< data
}
PE_DDR_O26_CVD_DFLT_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_O26_1212T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_1212T_FLT_NUM*PE_DDR_O26_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_1212T_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_O26_1208T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_12T_FLT_SIZE
*
* version history :
* 0x2 : 20210617, 2nd edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_1208T_FLT_NUM*PE_DDR_O26_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_1208T_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_O26_1206T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_1206T_FLT_NUM*PE_DDR_O26_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_1206T_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_O26_1204T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_1204T_FLT_NUM*PE_DDR_O26_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_1204T_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_O26_1202T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_1202T_FLT_NUM*PE_DDR_O26_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_1202T_T;

/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_O26_0808T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_08T_FLT_SIZE
*
* version history :
* 0x2 : 20210617, 2nd edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_0808T_FLT_NUM*PE_DDR_O26_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_0808T_T;

/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_O26_0806T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_08T_FLT_SIZE
*
* version history :
* 0x2 : 20210617, 2nd edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_0806T_FLT_NUM*PE_DDR_O26_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_0806T_T;

/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_O26_0804T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_08T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_0804T_FLT_NUM*PE_DDR_O26_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_0804T_T;

/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_O26_0802T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_08T_FLT_SIZE
*
* version history :
* 0x2 : 20210617, 2nd edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_0802T_FLT_NUM*PE_DDR_O26_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_0802T_T;

/**
* scaler v04tap main filter
* - header.item_num = PE_DDR_O26_0404T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_04T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_0404T_FLT_NUM*PE_DDR_O26_SCL_04T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_0404T_T;

/**
* scaler v04tap main filter
* - header.item_num = PE_DDR_O26_0402T_FLT_NUM
* - header.item_size = PE_DDR_O26_SCL_04T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_0402T_FLT_NUM*PE_DDR_O26_SCL_04T_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_0402T_T;

/**
* G0 scl 12t *4 + 08t x 2
* - header.item_num = 1(4 + 2)
* - header.item_size = PE_DDR_O26_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20250403, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_SCL_GAV_FLT_SIZE]; ///< data
}
PE_DDR_O26_SCL_G0_MULTIRUN_T;


/**
* tnr lut type
* - header.item_num = PE_DDR_O26_TNR_LUT_ITEM_NUM
* - header.item_size = PE_DDR_O26_TNR_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_TNR_LUT_ITEM_NUM*PE_DDR_O26_TNR_LUT_SIZE]; ///< data
}
PE_DDR_O26_TNR_LUT_T;

/**
* tnr user type
* - header.item_num = PE_DDR_O26_TNR_USER_ITEM_NUM
* - header.item_size = PE_DDR_O26_TNR_USER_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_TNR_USER_ITEM_NUM*PE_DDR_O26_TNR_USER_SIZE]; ///< data
}
PE_DDR_O26_TNR_USER_T;

/**
* drc lut type
* - header.item_num = PE_DDR_O26_DRC_LUT_ITEM_NUM
* - header.item_size = PE_DDR_O26_DRC_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_DRC_CURV_ITEM_NUM*PE_DDR_O26_DRC_CURV_SIZE2]; ///< data
}
PE_DDR_O26_DRC_CUV_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_DNR_USER_SIZE]; ///< data
}
PE_DDR_O26_DNR_USER_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_DCNT_USER_SIZE]; ///< data
}
PE_DDR_O26_DCNT_USER_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_DCNT_LED_USER_SIZE]; ///< data
}
PE_DDR_O26_DCNT_LED_USER_T;


typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_TNR_SQM_SIZE]; ///< data
}
PE_DDR_O26_TNR_SQM_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_DNR_SQM_SIZE]; ///< data
}
PE_DDR_O26_DNR_SQM_T;


typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_DCNT_SQM_SIZE]; ///< data
}
PE_DDR_O26_DCNT_SQM_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_CCODCNT_SQM_SIZE]; ///< data
}
PE_DDR_O26_CCODCNT_SQM_T;


typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_SHP_UI_SQM_2K_SIZE]; ///< data
}
PE_DDR_O26_SHP_UI_SQM_2K_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_SHP_SQM_CMN_2K_SIZE]; ///< data
}
PE_DDR_O26_SHP_SQM_CMN_2K_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_SHP_UI_SQM_VSD_SIZE]; ///< data
}
PE_DDR_O26_SHP_UI_SQM_VSD_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data[PE_DDR_O26_SHP_SQM_CMN_VSD_SIZE]; ///< data
}
PE_DDR_O26_SHP_SQM_CMN_VSD_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 idx;//0:null, 1~3:valid
	UINT32 data1[32];
	UINT32 data2[32];
	UINT32 data3[32];
}
PE_DDR_O26_HST_SRC_Y_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 cnt;
	PE_O26_VSD_OBE_CTRL_082_T reg_obe_ctrl_082;//0xCC950348 //0x950348
	PE_O26_VSD_OBE_CTRL_083_T reg_obe_ctrl_083;//0xCC95034C //0x95034C
	PE_O26_VSD_OBE_CTRL_084_T reg_obe_ctrl_084;//0xCC950350 //0x950350
	PE_O26_VSD_OBE_CTRL_085_T reg_obe_ctrl_085;//0xCC950354 //0x950354
}
PE_DDR_O26_OBC_CTRL_T;

typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 cnt;
	PE_O26_VSD_OBE_CTRL_028_T reg_obe_ctrl_028;//0xCC950270 //0x950270
	PE_O26_VSD_OBE_CTRL_029_T reg_obe_ctrl_029;//0xCC950274 //0x950274
	PE_O26_VSD_OBE_CTRL_030_T reg_obe_ctrl_030;//0xCC950278 //0x950278
	PE_O26_VSD_OBE_CTRL_031_T reg_obe_ctrl_031;//0xCC95027C //0x95027C
	PE_O26_VSD_OBE_CTRL_032_T reg_obe_ctrl_032;//0xCC950280 //0x950280
	PE_O26_VSD_OBE_CTRL_033_T reg_obe_ctrl_033;//0xCC950284 //0x950284
	PE_O26_VSD_OBE_CTRL_034_T reg_obe_ctrl_034;//0xCC950288 //0x950288
	PE_O26_VSD_OBE_CTRL_035_T reg_obe_ctrl_035;//0xCC95028C //0x95028C
	PE_O26_VSD_OBE_CTRL_036_T reg_obe_ctrl_036;//0xCC950290 //0x950290
	PE_O26_VSD_OBE_CTRL_037_T reg_obe_ctrl_037;//0xCC950294 //0x950294
	PE_O26_VSD_OBE_CTRL_038_T reg_obe_ctrl_038;//0xCC950298 //0x950298
	PE_O26_VSD_OBE_CTRL_039_T reg_obe_ctrl_039;//0xCC95029C //0x95029C
	PE_O26_VSD_OBE_CTRL_040_T reg_obe_ctrl_040;//0xCC9502A0 //0x9502A0
	PE_O26_VSD_OBE_CTRL_041_T reg_obe_ctrl_041;//0xCC9502A4 //0x9502A4
	PE_O26_VSD_OBE_CTRL_042_T reg_obe_ctrl_042;//0xCC9502A8 //0x9502A8
	PE_O26_VSD_OBE_CTRL_043_T reg_obe_ctrl_043;//0xCC9502AC //0x9502AC
	PE_O26_VSD_OBE_CTRL_044_T reg_obe_ctrl_044;//0xCC9502B0 //0x9502B0
	PE_O26_VSD_OBE_CTRL_045_T reg_obe_ctrl_045;//0xCC9502B4 //0x9502B4
	PE_O26_VSD_OBE_CTRL_046_T reg_obe_ctrl_046;//0xCC9502B8 //0x9502B8
	PE_O26_VSD_OBE_CTRL_047_T reg_obe_ctrl_047;//0xCC9502BC //0x9502BC
	PE_O26_VSD_OBE_CTRL_048_T reg_obe_ctrl_048;//0xCC9502C0 //0x9502C0
	PE_O26_VSD_OBE_CTRL_049_T reg_obe_ctrl_049;//0xCC9502C4 //0x9502C4
	PE_O26_VSD_OBE_CTRL_050_T reg_obe_ctrl_050;//0xCC9502C8 //0x9502C8
	PE_O26_VSD_OBE_CTRL_051_T reg_obe_ctrl_051;//0xCC9502CC //0x9502CC
	PE_O26_VSD_OBE_CTRL_052_T reg_obe_ctrl_052;//0xCC9502D0 //0x9502D0
	PE_O26_VSD_OBE_CTRL_053_T reg_obe_ctrl_053;//0xCC9502D4 //0x9502D4
	PE_O26_VSD_OBE_CTRL_054_T reg_obe_ctrl_054;//0xCC9502D8 //0x9502D8
	PE_O26_VSD_OBE_CTRL_055_T reg_obe_ctrl_055;//0xCC9502DC //0x9502DC
	PE_O26_VSD_OBE_CTRL_056_T reg_obe_ctrl_056;//0xCC9502E0 //0x9502E0
	PE_O26_VSD_OBE_CTRL_057_T reg_obe_ctrl_057;//0xCC9502E4 //0x9502E4
	PE_O26_VSD_OBE_CTRL_058_T reg_obe_ctrl_058;//0xCC9502E8 //0x9502E8
	PE_O26_VSD_OBE_CTRL_059_T reg_obe_ctrl_059;//0xCC9502EC //0x9502EC
	PE_O26_VSD_OBE_CTRL_060_T reg_obe_ctrl_060;//0xCC9502F0 //0x9502F0
	PE_O26_VSD_OBE_CTRL_061_T reg_obe_ctrl_061;//0xCC9502F4 //0x9502F4
	PE_O26_VSD_OBE_CTRL_062_T reg_obe_ctrl_062;//0xCC9502F8 //0x9502F8
	PE_O26_VSD_OBE_CTRL_063_T reg_obe_ctrl_063;//0xCC9502FC //0x9502FC
}
PE_DDR_O26_OBC_LUT_T;

/**
* ddr data type
*/
typedef struct
{
	PE_DDR_O26_TOP_HEADER_T top_h;       ///< top header
	PE_DDR_O26_MODE_T mode;              ///< num:PE_DDR_O26_MODE_ITEM_NUM       , size:PE_DDR_O26_MODE_SIZE
	PE_DDR_O26_CVD_DFLT_T cvd_dflt;      ///< num:PE_DDR_O26_CVD_DFLT_ITEM_NUM   , size:PE_DDR_O26_CVD_DFLT_SIZE
	PE_DDR_O26_SCL_1212T_T t1212;        ///< num:PE_DDR_O26_1212T_FLT_NUM  , size:PE_DDR_O26_SCL_12T_FLT_SIZE
	PE_DDR_O26_SCL_1208T_T t1208;        ///< num:PE_DDR_O26_1208T_FLT_NUM  , size:PE_DDR_O26_SCL_12T_FLT_SIZE
	PE_DDR_O26_SCL_1206T_T t1206;        ///< num:PE_DDR_O26_1206T_FLT_NUM  , size:PE_DDR_O26_SCL_12T_FLT_SIZE
	PE_DDR_O26_SCL_1204T_T t1204;        ///< num:PE_DDR_O26_1204T_FLT_NUM  , size:PE_DDR_O26_SCL_12T_FLT_SIZE
	PE_DDR_O26_SCL_1202T_T t1202;        ///< num:PE_DDR_O26_1202T_FLT_NUM  , size:PE_DDR_O26_SCL_12T_FLT_SIZE
	PE_DDR_O26_SCL_0808T_T t0808;        ///< num:PE_DDR_O26_0808T_FLT_NUM  , size:PE_DDR_O26_SCL_08T_FLT_SIZE
	PE_DDR_O26_SCL_0806T_T t0806;        ///< num:PE_DDR_O26_0806T_FLT_NUM  , size:PE_DDR_O26_SCL_08T_FLT_SIZE
	PE_DDR_O26_SCL_0804T_T t0804;        ///< num:PE_DDR_O26_0804T_FLT_NUM  , size:PE_DDR_O26_SCL_08T_FLT_SIZE
	PE_DDR_O26_SCL_0802T_T t0802;        ///< num:PE_DDR_O26_0802T_FLT_NUM  , size:PE_DDR_O26_SCL_08T_FLT_SIZE
	PE_DDR_O26_SCL_0404T_T t0404;        ///< num:PE_DDR_O26_0404T_FLT_NUM  , size:PE_DDR_O26_SCL_04T_FLT_SIZE
	PE_DDR_O26_SCL_0402T_T t0402;        ///< num:PE_DDR_O26_0402T_FLT_NUM  , size:PE_DDR_O26_SCL_04T_FLT_SIZE
	PE_DDR_O26_SCL_G0_MULTIRUN_T case01; ///< 12t_06t_0610 + 12t_06t_0610 + 12t_06t_0610 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case02; ///< 12t_04t_0008 + 12t_04t_0008 + 12t_04t_0308 + 12t_04t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case03; ///< 12t_04t_0008 + 12t_04t_0008 + 12t_04t_0008 + 12t_04t_0008 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case04; ///< 12t_12t_0004 + 12t_12t_0004 + 12t_06t_0610 + 12t_06t_0610 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case05; ///< 12t_12t_0006 + 12t_12t_0006 + 12t_04t_0308 + 12t_04t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case06; ///< 12t_12t_0004 + 12t_12t_0004 + 12t_12t_0306 + 12t_12t_0306 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case07; ///< 12t_12t_0304 + 12t_12t_0304 + 12t_12t_0306 + 12t_12t_0306 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case08; ///< 12t_12t_0104 + 12t_12t_0104 + 12t_12t_0306 + 12t_12t_0306 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case09; ///< 12t_04t_0910 + 12t_04t_0910 + 12t_02t_0308 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case10; ///< 12t_04t_1410 + 12t_04t_1410 + 12t_02t_0308 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_SCL_G0_MULTIRUN_T case11; ///< 12t_04t_1510 + 12t_04t_1510 + 12t_02t_0308 + 12t_02t_0308 + 08t_04t_0610 x 2
	PE_DDR_O26_TNR_LUT_T   tnr_lut;      ///< num:PE_DDR_O26_TNR_LUT_ITEM_NUM    , size:PE_DDR_O26_TNR_LUT_SIZE
	PE_DDR_O26_TNR_USER_T  tnr_user;     ///< num:PE_DDR_O26_TNR_USER_ITEM_NUM   , size:PE_DDR_O26_TNR_USER_SIZE
	PE_DDR_O26_DRC_CUV_T   drc_cuv;      ///< num:PE_DDR_O26_DRC_CURV_ITEM_NUM   , size:PE_DDR_O26_DRC_CURV_SIZE
	PE_DDR_O26_TNR_USER_T  tnr2nd_user;  ///< num:PE_DDR_O26_TNR_USER_ITEM_NUM   , size:PE_DDR_O26_TNR_USER_SIZE
	PE_DDR_O26_DNR_USER_T        dnr_user;
	PE_DDR_O26_DCNT_USER_T       nrd_dcnt_user;
	PE_DDR_O26_DCNT_LED_USER_T   led_dcnt_user;
	PE_DDR_O26_TNR_SQM_T         tnr_sqm;
	PE_DDR_O26_TNR_SQM_T         tnr2nd_sqm;
	PE_DDR_O26_DNR_SQM_T         dnr_sqm;
	PE_DDR_O26_DCNT_SQM_T        dnr_dcnt_sqm;
	PE_DDR_O26_SHP_UI_SQM_2K_T   shp_ui_sqm_2k;
	PE_DDR_O26_SHP_SQM_CMN_2K_T  shp_sqmcmn__2k;
	PE_DDR_O26_SHP_UI_SQM_VSD_T  shp_ui_sqm_vsd;
	PE_DDR_O26_SHP_SQM_CMN_VSD_T shp_sqmcmn__vsd;
	PE_DDR_O26_CCODCNT_SQM_T     cco_dcnt_sqm;
	PE_DDR_O26_TNR_USER_T        tnr3rd_user;  ///< num:PE_DDR_O26_TNR_USER_ITEM_NUM   , size:PE_DDR_O26_TNR_USER_SIZE
	PE_DDR_O26_DNR_USER_T        dnr2nd_user;
	PE_DDR_O26_DCNT_USER_T       nrd_dcnt2nd_user;
	PE_DDR_O26_TNR_SQM_T         tnr3rd_sqm;
	PE_DDR_O26_DNR_SQM_T         dnr2nd_sqm; /// < dnr2nd sqm use only (1+1+15), dnr sqm (1+1+17)
	PE_DDR_O26_DCNT_SQM_T        dnr_dcnt2nd_sqm;
	PE_DDR_O26_HST_SRC_Y_T       histo_src_y;
	PE_DDR_O26_OBC_CTRL_T        obc_ctrl;
	PE_DDR_O26_OBC_LUT_T         obc_lut;
}
PE_DDR_DB_PHYS_REG_O26_T;


/**
* data type
*/
typedef struct
{
	PE_DDR_O26_HEADER_T header; ///< header
	UINT32 data_base;           ///< data base
}
PE_DDR_O26_DATA_T;

/**
* ddr data type, should sync with PE_DDR_DB_PHYS_REG_O26_T
* - header.sec_type = PE_DDR_O26_SEC_HEADER
* - header.item_num = PE_DDR_O26_SEC_MAX_NUM
* - header.item_size = NA
*/
typedef struct
{
	PE_DDR_O26_TOP_HEADER_T top_h;                    ///< top header
	PE_DDR_O26_DATA_T sec_d[PE_DDR_O26_SEC_MAX_SIZE];  ///< section data
}
PE_DDR_DB_SHDW_REG_O26_T;

typedef struct
{
	union {
		UINT32                   *addr;
		PE_DDR_DB_SHDW_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32                   *addr;
		volatile PE_DDR_DB_PHYS_REG_O26_T *data;
	} phys;
}
PE_DDR_DB_REG_TYPE_O26_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_DDR_REG_O26_H_ */


