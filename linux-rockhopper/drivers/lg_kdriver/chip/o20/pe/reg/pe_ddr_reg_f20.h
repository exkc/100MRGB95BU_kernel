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

/** @file pe_ddr_reg_f20.h
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
#ifndef _PE_DDR_REG_F20_H_
#define _PE_DDR_REG_F20_H_
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
#define PE_DDR_F20_DB_VER					(0x1)

#define PE_DDR_F20_SEC_MAX_SIZE             50

#ifndef PE_DRC_LUT_SIZE
#define PE_DRC_LUT_SIZE		1185
#endif

/*LX_PE_CM_GLOBAL_POINT + LX_PE_CM_LOCAL_POINT +2 +
	LX_PE_CM_FREE_POINT x LX_PE_CM_LOCAL_CURVE_FW x 4 */
#define PE_DRC_F20_FW_LUT_SIZE		156

/* section size */
#define PE_DDR_F20_MODE_SIZE                1
#define PE_DDR_F20_DRC_LUT_SIZE             5222
#define PE_DDR_F20_SCL_12T_FLT_SIZE         896
#define PE_DDR_F20_SCL_08T_FLT_SIZE         640
#define PE_DDR_F20_SCL_04T_FLT_SIZE         384
#define PE_DDR_F20_TNR_LUT_SIZE             45
/* cnt:1 + ui:1 + lut_lm:16 + gain:5 + tmp:15*/
#define PE_DDR_F20_TNR_USER_SIZE            38
#define PE_DDR_F20_CVD_DFLT_SIZE            145
#define PE_DDR_F20_DRC_CURV_SIZE            PE_DRC_F20_FW_LUT_SIZE
/* cnt:1 + ui:1 + tmp:5*/
//#define PE_DDR_F20_DNR_USER_SIZE            (1+1+5)
//#define PE_DDR_F20_DCNT_USER_SIZE           (1+1+5)
#define PE_DDR_F20_DNR_USER_SIZE            (1+1+8)
#define PE_DDR_F20_DCNT_USER_SIZE           (1+1+8)
#define PE_DDR_F20_DCNT_LED_USER_SIZE           (1+1+8)

/* cnt:1 + ui:1 + sqm:11*/
#define PE_DDR_F20_TNR_SQM_SIZE             (1+1+11)

/* cnt:1 + ui:1 + sqm:19 - o18*/
/* cnt:1 + ui:1 + sqm:15 - f20*/
//#define PE_DDR_F20_DNR_SQM_SIZE             (1+1+19)
#define PE_DDR_F20_DNR_SQM_SIZE             (1+1+15)

/* cnt:1 + ui:1 + sqm:23*/
#define PE_DDR_F20_DCNT_SQM_SIZE            (1+1+23)

/* cnt:1 + ui:1 + sqm:40*/
#define PE_DDR_F20_SHP_UI_SQM_VSD_SIZE      (1+1+40)

/* cnt:1 + ui:1 + sqm:51*/
#define PE_DDR_F20_SHP_SQM_CMN_VSD_SIZE     (1+1+51)

/* item number */
#define PE_DDR_F20_MODE_ITEM_NUM            1
#define PE_DDR_F20_DRC_LUT_ITEM_NUM         4
#define PE_DDR_F20_CVD_DFLT_ITEM_NUM        12
#if 0
#define PE_DDR_F20_SCL_12T_M_ITEM_NUM       (17+2)
#define PE_DDR_F20_SCL_12T_H_ITEM_NUM       (2+2)
#define PE_DDR_F20_SCL_08T_F_ITEM_NUM       (11+2)
#define PE_DDR_F20_SCL_08T_H_ITEM_NUM       (2+2)
#define PE_DDR_F20_SCL_04T_F_ITEM_NUM       (9+2)
#define PE_DDR_F20_SCL_04T_H_ITEM_NUM       (2+2)
//#else
#define PE_DDR_F20_SCL_12T_M_ITEM_NUM       17
#define PE_DDR_F20_SCL_12T_H_ITEM_NUM       2
#define PE_DDR_F20_SCL_08T_F_ITEM_NUM       11
#define PE_DDR_F20_SCL_08T_H_ITEM_NUM       2
#define PE_DDR_F20_SCL_04T_F_ITEM_NUM       9
#define PE_DDR_F20_SCL_04T_H_ITEM_NUM       2
#endif
#define PE_DDR_F20_TNR_LUT_ITEM_NUM         4
#define PE_DDR_F20_TNR_USER_ITEM_NUM        1
#define PE_DDR_F20_DRC_CURV_ITEM_NUM        1
/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_DDR_REG_F20_SEC_TYPE_TO_STR(_x)		(\
	((_x)==PE_DDR_F20_SEC_MODE  )? "MODE  ":\
	((_x)==PE_DDR_F20_SEC_DRC_LUT  )? "DRC_LUT  ":\
	((_x)==PE_DDR_F20_SEC_SCL_1212T)? "SCL_1212T":\
	((_x)==PE_DDR_F20_SEC_SCL_1206T)? "SCL_1206T":\
	((_x)==PE_DDR_F20_SEC_SCL_1204T)? "SCL_1204T":\
	((_x)==PE_DDR_F20_SEC_SCL_0804T)? "SCL_0804T":\
	((_x)==PE_DDR_F20_SEC_TNR_LUT  )? "TNR_LUT  ":\
	((_x)==PE_DDR_F20_SEC_TNR_USER )? "TNR_USER ":\
	((_x)==PE_DDR_F20_SEC_DRC_CURV )? "DRC_CUV  ":\
	((_x)==PE_DDR_F20_SEC_DNR_USER        )? "DNR_USER       ":\
	((_x)==PE_DDR_F20_SEC_DNR_DCNT_USER   )? "DNR_DCNT_USER  ":\
	((_x)==PE_DDR_F20_SEC_LED_DCNT_USER   )? "LED_DECNT_USER ":\
	((_x)==PE_DDR_F20_SEC_TNR_SQM         )? "TNR_SQM        ":\
	((_x)==PE_DDR_F20_SEC_DNR_SQM         )? "DNR_SQM        ":\
	((_x)==PE_DDR_F20_SEC_DNR_DCNT_SQM    )? "DNR_DCNT_SQM   ":\
	((_x)==PE_DDR_F20_SEC_LED_DCNT_SQM    )? "LED_DCNT_SQM   ":\
	((_x)==PE_DDR_F20_SEC_SHP_UI_SQM_VSD  )? "SHP_UI_SQM_VSD ":\
	((_x)==PE_DDR_F20_SEC_SHP_SQM_CMN_VSD )? "SHP_SQM_CMN_VSD":\
	"SEC_NUM  ")

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
* section type enum
* - causion : should be PE_DDR_F20_SEC_NUM < PE_DDR_F20_SEC_MAX_SIZE
*/
typedef enum
{
	PE_DDR_F20_SEC_MODE            =  0,  ///< mode
	PE_DDR_F20_SEC_DRC_LUT         =  1,  ///< drc lut
	PE_DDR_F20_SEC_SCL_1212T       =  2,  ///< msc 12_12tap
	PE_DDR_F20_SEC_SCL_1206T       =  3,  ///< msc 12_06tap
	PE_DDR_F20_SEC_SCL_1204T       =  4,  ///< msc 12_04ap
	PE_DDR_F20_SEC_SCL_0804T       =  5,  ///< msc 08_04tap
	PE_DDR_F20_SEC_DRC_CURV        =  6,  ///< drc lut
	PE_DDR_F20_SEC_TNR_LUT         =  7,  ///< tnr lut
	PE_DDR_F20_SEC_TNR_USER        =  8,  ///< tnr user
	PE_DDR_F20_SEC_TNR_SQM         =  9,  ///< tnr_sqm
	PE_DDR_F20_SEC_DNR_USER        = 10,  ///< dnr_user
	PE_DDR_F20_SEC_DNR_SQM         = 11,  ///< dnr_sqm
	PE_DDR_F20_SEC_DNR_DCNT_USER   = 12,  ///< dnr_dcnt_user
	PE_DDR_F20_SEC_DNR_DCNT_SQM    = 13,  ///< dnr_dcnt_sqm
	PE_DDR_F20_SEC_LED_DCNT_USER   = 14,  ///< led_dcnt_user
	PE_DDR_F20_SEC_LED_DCNT_SQM    = 15,  ///< led_dcnt_sqm
	PE_DDR_F20_SEC_SHP_UI_SQM_VSD  = 16,  ///< shp_ui_sqm_vsd
	PE_DDR_F20_SEC_SHP_SQM_CMN_VSD = 17,  ///< shp_sqm_cmn_vsd
	PE_DDR_F20_SEC_NUM                  ///< max num
}
PE_DDR_F20_SEC_TYPE;

typedef enum
{
	PE_DDR_F20_1212T_FLT_0004		=  0,
	PE_DDR_F20_1212T_FLT_0306		=  1,
	PE_DDR_F20_1212T_FLT_DUMY0      =  2,
	PE_DDR_F20_1212T_FLT_DUMY1 		=  3,
	PE_DDR_F20_1212T_FLT_NUM                  ///< max num
}
PE_DDR_F20_SCL_1212T_FLT_TYPE;

typedef enum
{
	PE_DDR_F20_1206T_FLT_0610   =  0,
	PE_DDR_F20_1206T_FLT_DUMY1  =  1,
	PE_DDR_F20_1206T_FLT_NUM                  ///< max num
}
PE_DDR_F20_SCL_1206T_FLT_TYPE;

typedef enum
{
	PE_DDR_F20_1204T_FLT_0008	=  0,
	PE_DDR_F20_1204T_FLT_0308	=  1,
	PE_DDR_F20_1204T_FLT_0910	=  2,
	PE_DDR_F20_1204T_FLT_1410	=  3,
	PE_DDR_F20_1204T_FLT_1510	=  4,
	PE_DDR_F20_1204T_FLT_DUMY0  =  5,
	PE_DDR_F20_1204T_FLT_DUMY1  =  6,
	PE_DDR_F20_1204T_FLT_NUM                  ///< max num
}
PE_DDR_F20_SCL_1204T_FLT_TYPE;

typedef enum
{
	PE_DDR_F20_0804T_FLT_0610		=  0,
	PE_DDR_F20_0804T_FLT_DUMY1		=  1,
	PE_DDR_F20_0804T_FLT_NUM                  ///< max num
}
PE_DDR_F20_SCL_0804T_FLT_TYPE;


/**
* top header type
* - sec_num : PE_DDR_F20_SEC_NUM
* - sec_base[N+1] = sec_base[N] + [N]header + ([N]item_num * [N]item_size)
*   ([N]header = sizeof(PE_DDR_F20_HEADER_T))
*/
typedef struct
{
	UINT32 version;      ///< version
	UINT32 db_base;      ///< db base addr
	UINT32 sec_num;      ///< section max number
	UINT32 sec_base[PE_DDR_F20_SEC_MAX_SIZE];   ///< each section start base
	UINT32 sec_size[PE_DDR_F20_SEC_MAX_SIZE];   ///< each section start size
}
PE_DDR_F20_TOP_HEADER_T;

/**
* header type
* - sec_type : see PE_DDR_F20_SEC_TYPE 
*/
typedef struct
{
	UINT32 version;    ///< version
	UINT32 sec_type;   ///< section type
	UINT32 item_num;   ///< item number
	UINT32 item_size;  ///< item size
}
PE_DDR_F20_HEADER_T;

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
PE_DDR_F20_MD0_T;

/**
* mode
* - header.item_num = PE_DDR_O20_MODE_ITEM_NUM
* - header.item_size = PE_DDR_O20_MODE_SIZE
* - data, see PE_DDR_O20_MD0_T
*
* version history :
* 0x1 : 20140827, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_MODE_ITEM_NUM*PE_DDR_F20_MODE_SIZE]; ///< data
}
PE_DDR_F20_MODE_T;

/**
* drc lut type
* - header.item_num = PE_DDR_F20_DRC_LUT_ITEM_NUM
* - header.item_size = PE_DDR_F20_DRC_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DRC_LUT_ITEM_NUM*PE_DDR_F20_DRC_LUT_SIZE]; ///< data
}
PE_DDR_F20_DRC_LUT_T;

/**
* cvd default type
* - header.item_num = PE_DDR_F20_CVD_DFLT_ITEM_NUM
* - header.item_size = PE_DDR_F20_CVD_DFLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_CVD_DFLT_ITEM_NUM*PE_DDR_F20_CVD_DFLT_SIZE]; ///< data
}
PE_DDR_F20_CVD_DFLT_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_F20_1212T_FLT_NUM
* - header.item_size = PE_DDR_F20_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_1212T_FLT_NUM*PE_DDR_F20_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_F20_SCL_1212T_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_F20_1206T_FLT_NUM
* - header.item_size = PE_DDR_F20_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_1206T_FLT_NUM*PE_DDR_F20_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_F20_SCL_1206T_T;

/**
* scaler h12tap main filter
* - header.item_num = PE_DDR_F20_1204T_FLT_NUM
* - header.item_size = PE_DDR_F20_SCL_12T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_1204T_FLT_NUM*PE_DDR_F20_SCL_12T_FLT_SIZE]; ///< data
}
PE_DDR_F20_SCL_1204T_T;


/**
* scaler v08tap main filter
* - header.item_num = PE_DDR_F20_SCL_08T_H_ITEM_NUM
* - header.item_size = PE_DDR_F20_SCL_08T_FLT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_0804T_FLT_NUM*PE_DDR_F20_SCL_08T_FLT_SIZE]; ///< data
}
PE_DDR_F20_SCL_0804T_T;


/**
* tnr lut type
* - header.item_num = PE_DDR_F20_TNR_LUT_ITEM_NUM
* - header.item_size = PE_DDR_F20_TNR_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_TNR_LUT_ITEM_NUM*PE_DDR_F20_TNR_LUT_SIZE]; ///< data
}
PE_DDR_F20_TNR_LUT_T;

/**
* tnr user type
* - header.item_num = PE_DDR_F20_TNR_USER_ITEM_NUM
* - header.item_size = PE_DDR_F20_TNR_USER_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_TNR_USER_ITEM_NUM*PE_DDR_F20_TNR_USER_SIZE]; ///< data
}
PE_DDR_F20_TNR_USER_T;

/**
* drc lut type
* - header.item_num = PE_DDR_F20_DRC_LUT_ITEM_NUM
* - header.item_size = PE_DDR_F20_DRC_LUT_SIZE
*
* version history :
* 0x1 : 20150507, 1st edition
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DRC_CURV_ITEM_NUM*PE_DDR_F20_DRC_CURV_SIZE]; ///< data
}
PE_DDR_F20_DRC_CUV_T;

typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DNR_USER_SIZE]; ///< data
}
PE_DDR_F20_DNR_USER_T;

typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DCNT_USER_SIZE]; ///< data
}
PE_DDR_F20_DCNT_USER_T;

typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DCNT_LED_USER_SIZE]; ///< data
}
PE_DDR_F20_DCNT_LED_USER_T;


typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_TNR_SQM_SIZE]; ///< data
}
PE_DDR_F20_TNR_SQM_T;

typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DNR_SQM_SIZE]; ///< data
}
PE_DDR_F20_DNR_SQM_T;


typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_DCNT_SQM_SIZE]; ///< data
}
PE_DDR_F20_DCNT_SQM_T;

typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_SHP_UI_SQM_VSD_SIZE]; ///< data
}
PE_DDR_F20_SHP_UI_SQM_VSD_T;

typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data[PE_DDR_F20_SHP_SQM_CMN_VSD_SIZE]; ///< data
}
PE_DDR_F20_SHP_SQM_CMN_VSD_T;

/**
* ddr data type
*/
	
typedef struct
{
	PE_DDR_F20_TOP_HEADER_T top_h;     ///< top header
	PE_DDR_F20_MODE_T mode;            ///< num:PE_DDR_F20_MODE_ITEM_NUM       , size:PE_DDR_F20_MODE_SIZE
	PE_DDR_F20_DRC_LUT_T drc_lut;      ///< num:PE_DDR_F20_DRC_LUT_ITEM_NUM    , size:PE_DDR_F20_DRC_LUT_SIZE
	PE_DDR_F20_SCL_1212T_T t1212;      ///< num:PE_DDR_F20_1212T_FLT_NUM  , size:PE_DDR_F20_SCL_12T_FLT_SIZE 
	PE_DDR_F20_SCL_1206T_T t1206;      ///< num:PE_DDR_F20_1206T_FLT_NUM  , size:PE_DDR_F20_SCL_12T_FLT_SIZE 
	PE_DDR_F20_SCL_1204T_T t1204;      ///< num:PE_DDR_F20_1204T_FLT_NUM  , size:PE_DDR_F20_SCL_12T_FLT_SIZE 
	PE_DDR_F20_SCL_0804T_T t0804;      ///< num:PE_DDR_F20_0804T_FLT_NUM  , size:PE_DDR_F20_SCL_08T_FLT_SIZE
	PE_DDR_F20_DRC_CUV_T   drc_cuv;      ///< num:PE_DDR_F20_DRC_CURV_ITEM_NUM   , size:PE_DDR_F20_DRC_CURV_SIZE
	PE_DDR_F20_TNR_LUT_T   tnr_lut;      ///< num:PE_DDR_F20_TNR_LUT_ITEM_NUM    , size:PE_DDR_F20_TNR_LUT_SIZE
	PE_DDR_F20_TNR_USER_T  tnr_user;    ///< num:PE_DDR_F20_TNR_USER_ITEM_NUM   , size:PE_DDR_F20_TNR_USER_SIZE
	PE_DDR_F20_TNR_SQM_T         tnr_sqm;
	PE_DDR_F20_DNR_USER_T        dnr_user;
	PE_DDR_F20_DNR_SQM_T         dnr_sqm;
	PE_DDR_F20_DCNT_USER_T       nrd_dcnt_user;
	PE_DDR_F20_DCNT_SQM_T        dnr_dcnt_sqm;
	PE_DDR_F20_DCNT_LED_USER_T   led_dcnt_user;
	PE_DDR_F20_DCNT_SQM_T        led_dcnt_sqm;
	PE_DDR_F20_SHP_UI_SQM_VSD_T  shp_ui_sqm_vsd;
	PE_DDR_F20_SHP_SQM_CMN_VSD_T shp_sqmcmn__vsd;
	UINT32 crc;
}
PE_DDR_DB_PHYS_REG_F20_T;


/**
* data type
*/
typedef struct
{
	PE_DDR_F20_HEADER_T header; ///< header
	UINT32 data_base;           ///< data base
}
PE_DDR_F20_DATA_T;

/**
* ddr data type, should sync with PE_DDR_DB_PHYS_REG_F20_T
* - header.sec_type = PE_DDR_F20_SEC_HEADER
* - header.item_num = PE_DDR_F20_SEC_MAX_NUM
* - header.item_size = NA
*/
typedef struct
{
	PE_DDR_F20_TOP_HEADER_T top_h;                    ///< top header
	PE_DDR_F20_DATA_T sec_d[PE_DDR_F20_SEC_MAX_SIZE];  ///< section data
}
PE_DDR_DB_SHDW_REG_F20_T;

typedef struct
{
	union {
		UINT32                   *addr;
		PE_DDR_DB_SHDW_REG_F20_T *data;
	} shdw;

	union {
		volatile UINT32                   *addr;
		volatile PE_DDR_DB_PHYS_REG_F20_T *data;
	} phys;
}
PE_DDR_DB_REG_TYPE_F20_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_DDR_REG_F20_H_ */

