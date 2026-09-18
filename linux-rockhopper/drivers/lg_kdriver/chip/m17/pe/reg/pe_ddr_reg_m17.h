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

/** @file pe_ddr_reg_m17.h
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
#ifndef _PE_DDR_REG_M17_H_
#define _PE_DDR_REG_M17_H_
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
#define PE_DDR_M17_DB_VER					(0x0)

#define PE_DDR_M17_SEC_MAX_SIZE             50

#define PE_DDR_M17_NEW_DB

#ifndef PE_DRC_LUT_SIZE
#define PE_DRC_LUT_SIZE		1185
#endif

/*LX_PE_CM_GLOBAL_POINT + LX_PE_CM_LOCAL_POINT +2 +
	LX_PE_CM_FREE_POINT x LX_PE_CM_LOCAL_CURVE_FW x 4 */
#define PE_DRC_M17_FW_LUT_SIZE		156

/* section size */
#define PE_DDR_M17_MODE_SIZE                1
#define PE_DDR_M17_DRC_LUT_SIZE             PE_DRC_LUT_SIZE
#define PE_DDR_M17_SCL_12T_FLT_SIZE         896
#define PE_DDR_M17_SCL_08T_FLT_SIZE         640
#define PE_DDR_M17_SCL_04T_FLT_SIZE         384
#define PE_DDR_M17_TNR_LUT_SIZE             45
/* cnt:1 + ui:1 + lut_lm:16 + gain:5 + tmp:32*/
#define PE_DDR_M17_TNR_USER_SIZE            55
#define PE_DDR_M17_CVD_DFLT_SIZE            145
#define PE_DDR_M17_BLK_APL_SIZE             1728
#define PE_DDR_M17_DRC_CURV_SIZE            PE_DRC_M17_FW_LUT_SIZE

/* item number */
#define PE_DDR_M17_MODE_ITEM_NUM            1
#define PE_DDR_M17_DRC_LUT_ITEM_NUM         4
#define PE_DDR_M17_CVD_DFLT_ITEM_NUM        12
#if 1
#define PE_DDR_M17_SCL_12T_M_ITEM_NUM       (17+2)
#define PE_DDR_M17_SCL_12T_H_ITEM_NUM       (2+2)
#define PE_DDR_M17_SCL_08T_F_ITEM_NUM       (11+2)
#define PE_DDR_M17_SCL_08T_H_ITEM_NUM       (2+2)
#define PE_DDR_M17_SCL_04T_F_ITEM_NUM       (9+2)
#define PE_DDR_M17_SCL_04T_H_ITEM_NUM       (2+2)
#else
#define PE_DDR_M17_SCL_12T_M_ITEM_NUM       17
#define PE_DDR_M17_SCL_12T_H_ITEM_NUM       2
#define PE_DDR_M17_SCL_08T_F_ITEM_NUM       11
#define PE_DDR_M17_SCL_08T_H_ITEM_NUM       2
#define PE_DDR_M17_SCL_04T_F_ITEM_NUM       9
#define PE_DDR_M17_SCL_04T_H_ITEM_NUM       2
#endif
#define PE_DDR_M17_TNR_LUT_ITEM_NUM         4
#define PE_DDR_M17_TNR_USER_ITEM_NUM        1
#define PE_DDR_M17_BLK_APL_ITEM_NUM         2
#define PE_DDR_M17_DRC_CURV_ITEM_NUM        1
/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_DDR_REG_M17_SEC_TYPE_TO_STR(_x)		(\
	((_x)==PE_DDR_M17_SEC_MODE     )? "MODE     ":\
	((_x)==PE_DDR_M17_SEC_DRC_LUT  )? "DRC_LUT  ":\
	((_x)==PE_DDR_M17_SEC_CVD_DFLT )? "CVD_DFLT ":\
	((_x)==PE_DDR_M17_SEC_SCL_12T_M)? "SCL_12T_M":\
	((_x)==PE_DDR_M17_SEC_SCL_12T_H)? "SCL_12T_H":\
	((_x)==PE_DDR_M17_SEC_SCL_08T_F)? "SCL_08T_M":\
	((_x)==PE_DDR_M17_SEC_SCL_08T_H)? "SCL_08T_H":\
	((_x)==PE_DDR_M17_SEC_SCL_04T_F)? "SCL_04T_F":\
	((_x)==PE_DDR_M17_SEC_SCL_04T_H)? "SCL_04T_H":\
	((_x)==PE_DDR_M17_SEC_TNR_LUT  )? "TNR_LUT  ":\
	((_x)==PE_DDR_M17_SEC_TNR_USER )? "TNR_USER ":\
	((_x)==PE_DDR_M17_SEC_BLK_APL  )? "BLK_APL  ":\
	((_x)==PE_DDR_M17_SEC_DRC_CURV )? "DRC_CUV  ":\
	"SEC_NUM  ")

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
* section type enum
* - causion : should be PE_DDR_M17_SEC_NUM < PE_DDR_M17_SEC_MAX_SIZE
*/
typedef enum
{
	PE_DDR_M17_SEC_MODE          =  0,  ///< mode
	PE_DDR_M17_SEC_DRC_LUT       =  1,  ///< drc lut
	PE_DDR_M17_SEC_CVD_DFLT      =  2,  ///< cvd default
	PE_DDR_M17_SEC_SCL_12T_M     =  3,  ///< msc 12tap main
	PE_DDR_M17_SEC_SCL_12T_H     =  4,  ///< msc 12tap half
	PE_DDR_M17_SEC_SCL_08T_F     =  5,  ///< msc 08tap main
	PE_DDR_M17_SEC_SCL_08T_H     =  6,  ///< msc 08tap half
	PE_DDR_M17_SEC_SCL_04T_F     =  7,  ///< msc 04tap main
	PE_DDR_M17_SEC_SCL_04T_H     =  8,  ///< msc 04tap half
	PE_DDR_M17_SEC_TNR_LUT       =  9,  ///< tnr lut
	PE_DDR_M17_SEC_TNR_USER      = 10,  ///< tnr user
	PE_DDR_M17_SEC_BLK_APL       = 11,  ///< block apl
	PE_DDR_M17_SEC_DRC_CURV      = 12,  ///< drc lut
	PE_DDR_M17_SEC_NUM                  ///< max num
}
PE_DDR_M17_SEC_TYPE;

typedef enum
{
	PE_DDR_M17_12T_M_FLT_0002		=  0,
	PE_DDR_M17_12T_M_FLT_0003		=  1,
	PE_DDR_M17_12T_M_FLT_0004		=  2,
	PE_DDR_M17_12T_M_FLT_0006		=  3,
	PE_DDR_M17_12T_M_FLT_0110		=  4,
	PE_DDR_M17_12T_M_FLT_0202		=  5,
	PE_DDR_M17_12T_M_FLT_0204		=  6,
	PE_DDR_M17_12T_M_FLT_0304		=  7,
	PE_DDR_M17_12T_M_FLT_0306		=  8,
	PE_DDR_M17_12T_M_FLT_0404		=  9,
	PE_DDR_M17_12T_M_FLT_0406		= 10,
	PE_DDR_M17_12T_M_FLT_0606		= 11,
	PE_DDR_M17_12T_M_FLT_0806		= 12,
	PE_DDR_M17_12T_M_FLT_1006		= 13,
	PE_DDR_M17_12T_M_FLT_1410		= 14,
	PE_DDR_M17_12T_M_FLT_0104		= 15,
	PE_DDR_M17_12T_M_FLT_1010		= 16,
	PE_DDR_M17_12T_M_FLT_DUMY0		= 17,
	PE_DDR_M17_12T_M_FLT_DUMY1		= 18,
	PE_DDR_M17_12T_M_FLT_NUM                  ///< max num
}
PE_DDR_M17_SCL_12T_M_FLT_TYPE;

typedef enum
{
	PE_DDR_M17_12T_H_FLT_0006		=  0,
	PE_DDR_M17_12T_H_FLT_0306		=  1,
	PE_DDR_M17_12T_H_FLT_DUMY0		=  2,
	PE_DDR_M17_12T_H_FLT_DUMY1		=  3,
	PE_DDR_M17_12T_H_FLT_NUM                  ///< max num
}
PE_DDR_M17_SCL_12T_H_FLT_TYPE;

typedef enum
{
	PE_DDR_M17_08T_F_FLT_0006		=  0,
	PE_DDR_M17_08T_F_FLT_0306		=  1,
	PE_DDR_M17_08T_F_FLT_0606		=  2,
	PE_DDR_M17_08T_F_FLT_0610		=  3,
	PE_DDR_M17_08T_F_FLT_0806		=  4,
	PE_DDR_M17_08T_F_FLT_1006		=  5,
	PE_DDR_M17_08T_F_FLT_1210		=  6,
	PE_DDR_M17_08T_F_FLT_1406		=  7,
	PE_DDR_M17_08T_F_FLT_1410		=  8,
	PE_DDR_M17_08T_F_FLT_1514		=  9,
	PE_DDR_M17_08T_F_FLT_1515		= 10,
	PE_DDR_M17_08T_F_FLT_DUMY0		= 11,
	PE_DDR_M17_08T_F_FLT_DUMY1		= 12,
	PE_DDR_M17_08T_F_FLT_NUM                  ///< max num
}
PE_DDR_M17_SCL_08T_F_FLT_TYPE;

typedef enum
{
	PE_DDR_M17_08T_H_FLT_0006		=  0,
	PE_DDR_M17_08T_H_FLT_0306		=  1,
	PE_DDR_M17_08T_H_FLT_0008		=  2,
	PE_DDR_M17_08T_H_FLT_DUMY1		=  3,
	PE_DDR_M17_08T_H_FLT_NUM                  ///< max num
}
PE_DDR_M17_SCL_08T_H_FLT_TYPE;

typedef enum
{
	PE_DDR_M17_04T_F_FLT_0006		=  0,
	PE_DDR_M17_04T_F_FLT_0306		=  1,
	PE_DDR_M17_04T_F_FLT_0606		=  2,
	PE_DDR_M17_04T_F_FLT_0806		=  3,
	PE_DDR_M17_04T_F_FLT_1006		=  4,
	PE_DDR_M17_04T_F_FLT_1406		=  5,
	PE_DDR_M17_04T_F_FLT_1410		=  6,
	PE_DDR_M17_04T_F_FLT_1514		=  7,
	PE_DDR_M17_04T_F_FLT_1515		=  8,
	PE_DDR_M17_04T_F_FLT_DUMY0		=  9,
	PE_DDR_M17_04T_F_FLT_DUMY1		=  10,
	PE_DDR_M17_04T_F_FLT_NUM                  ///< max num
}
PE_DDR_M17_SCL_04T_F_FLT_TYPE;

typedef enum
{
	PE_DDR_M17_04T_H_FLT_0006		=  0,
	PE_DDR_M17_04T_H_FLT_0306		=  1,
	PE_DDR_M17_04T_H_FLT_0308		=  2,
	PE_DDR_M17_04T_H_FLT_DUMY1		=  3,
	PE_DDR_M17_04T_H_FLT_NUM                  ///< max num
}
PE_DDR_M17_SCL_04T_H_FLT_TYPE;


/**
* top header type
* - sec_num : PE_DDR_M17_SEC_NUM
* - sec_base[N+1] = sec_base[N] + [N]header + ([N]item_num * [N]item_size)
*   ([N]header = sizeof(PE_DDR_M17_HEADER_T))
*/
typedef struct
{
	UINT32 version;      ///< version
	UINT32 db_base;      ///< db base addr
	UINT32 sec_num;      ///< section max number
	UINT32 sec_base[PE_DDR_M17_SEC_MAX_SIZE];   ///< each section start base
	UINT32 sec_size[PE_DDR_M17_SEC_MAX_SIZE];   ///< each section start size
}
PE_DDR_M17_TOP_HEADER_T;

/**
* header type
* - sec_type : see PE_DDR_M17_SEC_TYPE 
*/
typedef struct
{
	UINT32 version;    ///< version
	UINT32 sec_type;   ///< section type
	UINT32 item_num;   ///< item number
	UINT32 item_size;  ///< item size
}
PE_DDR_M17_HEADER_T;

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
}
PE_DDR_M17_MD0_T;

/**
* mode
* - header.item_num = PE_DDR_M17_MODE_ITEM_NUM
* - header.item_size = PE_DDR_M17_MODE_SIZE
* - data, see PE_DDR_M17_MD0_T
*
* version history :
* 0x1 : 20140827, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_MODE_ITEM_NUM*PE_DDR_M17_MODE_SIZE]; ///< data
}
PE_DDR_M17_MODE_T;

/**
* drc lut type
* - header.item_num = PE_DDR_M17_DRC_LUT_ITEM_NUM
* - header.item_size = PE_DDR_M17_DRC_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_DRC_LUT_ITEM_NUM*PE_DDR_M17_DRC_LUT_SIZE]; ///< data
}
PE_DDR_M17_DRC_LUT_T;

/**
* cvd default type
* - header.item_num = PE_DDR_M17_CVD_DFLT_ITEM_NUM
* - header.item_size = PE_DDR_M17_CVD_DFLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_CVD_DFLT_ITEM_NUM*PE_DDR_M17_CVD_DFLT_SIZE]; ///< data
}
PE_DDR_M17_CVD_DFLT_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_M17_SCL_12T_M_ITEM_NUM
* - header.item_size = PE_DDR_M17_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_SCL_12T_M_ITEM_NUM*PE_DDR_M17_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_M17_SCL_12T_M_T;

/**
* scaler h12tap sub filter
* - header.item_num = PE_DDR_M17_SCL_12T_S_ITEM_NUM
* - header.item_size = PE_DDR_M17_SCL_S_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_SCL_12T_H_ITEM_NUM*PE_DDR_M17_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_M17_SCL_12T_H_T;

/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_M17_SCL_08T_H_ITEM_NUM
* - header.item_size = PE_DDR_M17_SCL_08T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_SCL_08T_F_ITEM_NUM*PE_DDR_M17_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_M17_SCL_08T_F_T;

/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_M17_SCL_08T_M_ITEM_NUM
* - header.item_size = PE_DDR_M17_SCL_M_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_SCL_08T_H_ITEM_NUM*PE_DDR_M17_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_M17_SCL_08T_H_T;

/**
* scaler v04tap main filter
* - header.item_num = PE_DDR_M17_SCL_04T_H_ITEM_NUM
* - header.item_size = PE_DDR_M17_SCL_04T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_SCL_04T_F_ITEM_NUM*PE_DDR_M17_SCL_04T_FLT_SIZE]; ///< data
}
PE_DDR_M17_SCL_04T_F_T;

/**
* scaler v04tap main filter
* - header.item_num = PE_DDR_M17_SCL_04T_H_ITEM_NUM
* - header.item_size = PE_DDR_M17_SCL_04T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_SCL_04T_H_ITEM_NUM*PE_DDR_M17_SCL_04T_FLT_SIZE]; ///< data
}
PE_DDR_M17_SCL_04T_H_T;

/**
* tnr lut type
* - header.item_num = PE_DDR_M17_TNR_LUT_ITEM_NUM
* - header.item_size = PE_DDR_M17_TNR_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_TNR_LUT_ITEM_NUM*PE_DDR_M17_TNR_LUT_SIZE]; ///< data
}
PE_DDR_M17_TNR_LUT_T;

/**
* tnr user type
* - header.item_num = PE_DDR_M17_TNR_USER_ITEM_NUM
* - header.item_size = PE_DDR_M17_TNR_USER_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_TNR_USER_ITEM_NUM*PE_DDR_M17_TNR_USER_SIZE]; ///< data
}
PE_DDR_M17_TNR_USER_T;

/**
* block alp type
* - header.item_num = PE_DDR_M17_BLK_APL_ITEM_NUM
* - header.item_size = PE_DDR_M17_BLK_APL_SIZE
*
* version history :
* 0x1 : 20160707, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_BLK_APL_ITEM_NUM*PE_DDR_M17_BLK_APL_SIZE]; ///< data
}
PE_DDR_M17_BLK_APL_T;

/**
* drc lut type
* - header.item_num = PE_DDR_M17_DRC_LUT_ITEM_NUM
* - header.item_size = PE_DDR_M17_DRC_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data[PE_DDR_M17_DRC_CURV_ITEM_NUM*PE_DDR_M17_DRC_CURV_SIZE]; ///< data
}
PE_DDR_M17_DRC_CUV_T;

/**
* ddr data type
*/
	
typedef struct
{
	PE_DDR_M17_TOP_HEADER_T top_h;     ///< top header
	PE_DDR_M17_MODE_T mode;            ///< num:PE_DDR_M17_MODE_ITEM_NUM       , size:PE_DDR_M17_MODE_SIZE
	PE_DDR_M17_DRC_LUT_T drc_lut;      ///< num:PE_DDR_M17_DRC_LUT_ITEM_NUM    , size:PE_DDR_M17_DRC_LUT_SIZE
	PE_DDR_M17_CVD_DFLT_T cvd_dflt;    ///< num:PE_DDR_M17_CVD_DFLT_ITEM_NUM   , size:PE_DDR_M17_CVD_DFLT_SIZE
	PE_DDR_M17_SCL_12T_M_T t12_m;      ///< num:PE_DDR_M17_SCL_12T_M_ITEM_NUM  , size:PE_DDR_M17_SCL_M_FLT_SIZE 
	PE_DDR_M17_SCL_12T_H_T t12_h;      ///< num:PE_DDR_M17_SCL_12T_H_ITEM_NUM  , size:PE_DDR_M17_SCL_S_FLT_SIZE
	PE_DDR_M17_SCL_08T_F_T t08_f;      ///< num:PE_DDR_M17_SCL_08T_M_ITEM_NUM  , size:PE_DDR_M17_SCL_M_FLT_SIZE
	PE_DDR_M17_SCL_08T_H_T t08_h;      ///< num:PE_DDR_M17_SCL_08T_M_ITEM_NUM  , size:PE_DDR_M17_SCL_M_FLT_SIZE
	PE_DDR_M17_SCL_04T_F_T t04_f;      ///< num:PE_DDR_M17_SCL_04T_M_ITEM_NUM  , size:PE_DDR_M17_SCL_M_FLT_SIZE
	PE_DDR_M17_SCL_04T_H_T t04_h;      ///< num:PE_DDR_M17_SCL_04T_M_ITEM_NUM  , size:PE_DDR_M17_SCL_M_FLT_SIZE
	PE_DDR_M17_TNR_LUT_T tnr_lut;      ///< num:PE_DDR_M17_TNR_LUT_ITEM_NUM    , size:PE_DDR_M17_TNR_LUT_SIZE
	PE_DDR_M17_TNR_USER_T tnr_user;    ///< num:PE_DDR_M17_TNR_USER_ITEM_NUM   , size:PE_DDR_M17_TNR_USER_SIZE
	PE_DDR_M17_BLK_APL_T blk_apl;      ///< num:PE_DDR_M17_BLK_APL_ITEM_NUM   , size:PE_DDR_M17_BLK_APL_SIZE
	#ifdef PE_DDR_M17_NEW_DB
	PE_DDR_M17_DRC_CUV_T drc_cuv;      ///< num:PE_DDR_M17_DRC_CURV_ITEM_NUM   , size:PE_DDR_M17_DRC_CURV_SIZE
	#endif
}
PE_DDR_DB_PHYS_REG_M17_T;


/**
* data type
*/
typedef struct
{
	PE_DDR_M17_HEADER_T header; ///< header
	UINT32 data_base;           ///< data base
}
PE_DDR_M17_DATA_T;

/**
* ddr data type, should sync with PE_DDR_DB_PHYS_REG_M17_T
* - header.sec_type = PE_DDR_M17_SEC_HEADER
* - header.item_num = PE_DDR_M17_SEC_MAX_NUM
* - header.item_size = NA
*/
typedef struct
{
	PE_DDR_M17_TOP_HEADER_T top_h;                    ///< top header
	PE_DDR_M17_DATA_T sec_d[PE_DDR_M17_SEC_MAX_SIZE];  ///< section data
}
PE_DDR_DB_SHDW_REG_M17_T;

typedef struct
{
	union {
		UINT32                   *addr;
		PE_DDR_DB_SHDW_REG_M17_T *data;
	} shdw;

	union {
		volatile UINT32                   *addr;
		volatile PE_DDR_DB_PHYS_REG_M17_T *data;
	} phys;
}
PE_DDR_DB_REG_TYPE_M17_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_DDR_REG_M17_H_ */

