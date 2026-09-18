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

/** @file pe_dcm_ddr_reg_e60f20.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  inkyung.park (inkyung.park@lge.com)
 * version	  1.0
 * date		  2020.08.28
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef _PE_DCM_DDR_REG_E60F20_H_
#define _PE_DCM_DDR_REG_E60F20_H_
 /*----------------------------------------------------------------------------------------
  *   Control Constants
  *---------------------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------------------
  *   File Inclusions
  *---------------------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------------------
  *   Constant Definitions
  *---------------------------------------------------------------------------------------*/
 /**
 * version history
 * 0x1 : 200828, 1st edition
 */
#define PE_DCM_DDR_E60F20_DB_VER					(0x1)
 
#define PE_DCM_DDR_E60F20_SEC_MAX_SIZE             50


/*DCE size */
#define PE_DCM_DDR_E60F20_DCM_DYN_SIZE             79
#define PE_DCM_DDR_E60F20_DCM_APL_SIZE             263
#define PE_DCM_DDR_E60F20_DCM_GAIN_SIZE            (231-3)
#define PE_DCM_DDR_E60F20_DCM_TABLE_SIZE           32


/* model*inputtyep*UI + dummyset*/
#define PE_DCM_DDR_E60F20_DCM_DYN_ITEM_NUM         ((2*4*5+1)+(3*4*5))
#define PE_DCM_DDR_E60F20_DCM_APL_ITEM_NUM         ((2*4*5+1)+(3*4*5))
/* (model+dymmy)*(input+dummy)*UI*/
#define PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM         (8+28)
#define PE_DCM_DDR_E60F20_DCM_TABLE_ITEM_NUM        ((1+2)*(1+2)*1)
 /*----------------------------------------------------------------------------------------
  *   Macro Definitions
  *---------------------------------------------------------------------------------------*/
#define PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(_x)		(\
	 ((_x)==PE_DCM_DDR_E60F20_SEC_DNY )?   "DNY  ":\
	 ((_x)==PE_DCM_DDR_E60F20_SEC_APL	)? "APL  ":\
	 ((_x)==PE_DCM_DDR_E60F20_SEC_GAIN)?   "GAIN ":\
	 ((_x)==PE_DCM_DDR_E60F20_SEC_TABLE)?  "TABLE":\
	 "SEC_NUM  ")
 
/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
* section type enum
* - causion : should be PE_DCM_DDR_E60F20_SEC_NUM < PE_DCM_DDR_E60F20_SEC_MAX_SIZE
*/
typedef enum
{
	 PE_DCM_DDR_E60F20_SEC_DNY        =  0,  ///< mode
	 PE_DCM_DDR_E60F20_SEC_APL        =  1,  ///< drc lut
	 PE_DCM_DDR_E60F20_SEC_GAIN       =  2,  ///< msc 12_12tap
	 PE_DCM_DDR_E60F20_SEC_TABLE      =  3,  ///< msc 12_06tap
	 PE_DCM_DDR_E60F20_SEC_NUM 				 ///< max num
}
PE_DCM_DDR_E60F20_SEC_TYPE;

/**
* top header type
* - sec_num : PE_DCM_DDR_E60F20_SEC_NUM
* - sec_base[N+1] = sec_base[N] + [N]header + ([N]item_num * [N]item_size)
*	 ([N]header = sizeof(PE_DCM_DDR_E60F20_HEADER_T))
*/
typedef struct
{
	 UINT32 version;	  ///< version
	 UINT32 db_base;	  ///< db base addr
	 UINT32 sec_num;	  ///< section max number
	 UINT32 sec_base[PE_DCM_DDR_E60F20_SEC_MAX_SIZE];	 ///< each section start base
	 UINT32 sec_size[PE_DCM_DDR_E60F20_SEC_MAX_SIZE];	 ///< each section start size
}
PE_DCM_DDR_E60F20_TOP_HEADER_T;

/**
* header type
* - sec_type : see PE_DCM_DDR_E60F20_SEC_TYPE 
*/
typedef struct
{
	 UINT32 version;	///< version
	 UINT32 sec_type;	///< section type
	 UINT32 item_num;	///< item number
	 UINT32 item_size;	///< item size
}
PE_DCM_DDR_E60F20_HEADER_T;



/**
* dc_contrast_lib type
* - header.item_num = PE_DCM_DDR_E60F20_DCM_DYN_ITEM_NUM
* - header.item_size = PE_DCM_DDR_E60F20_DCM_DYN_SIZE
*
* version history :
* 0x1 : 20200828, 1st edition
*/
typedef struct
{
	 PE_DCM_DDR_E60F20_HEADER_T header; ///< header
	 UINT32 data[PE_DCM_DDR_E60F20_DCM_DYN_ITEM_NUM*PE_DCM_DDR_E60F20_DCM_DYN_SIZE]; ///< data
}
PE_DCM_DDR_E60F20_DCM_DYN_T;

/**
* dc_apl type
* - header.item_num = PE_DCM_DDR_E60F20_DCM_APL_ITEM_NUM
* - header.item_size = PE_DCM_DDR_E60F20_DCM_APL_SIZE
*
* version history :
* 0x1 : 20200828, 1st edition
*/
typedef struct
{
	 PE_DCM_DDR_E60F20_HEADER_T header; ///< header
	 UINT32 data[PE_DCM_DDR_E60F20_DCM_APL_ITEM_NUM*PE_DCM_DDR_E60F20_DCM_APL_SIZE]; ///< data
}
PE_DCM_DDR_E60F20_DCM_APL_T;


/**
* dc_ai_gain type
* - header.item_num = PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM
* - header.item_size = PE_DCM_DDR_E60F20_DCM_GAIN_SIZE
*
* version history :
* 0x1 : 20200828, 1st edition
*/
typedef struct
{
	 PE_DCM_DDR_E60F20_HEADER_T header; ///< header
	 UINT32 data[PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM*PE_DCM_DDR_E60F20_DCM_GAIN_SIZE]; ///< data
}
PE_DCM_DDR_E60F20_DCM_GAIN_T;

/**
* dc_StabilizerGainTable type
* - header.item_num = PE_DCM_DDR_E60F20_DCM_TABLE_ITEM_NUM
* - header.item_size = PE_DCM_DDR_E60F20_DCM_TABLE_SIZE
*
* version history :
* 0x1 : 20200828, 1st edition
*/
typedef struct
{
	 PE_DCM_DDR_E60F20_HEADER_T header; ///< header
	 UINT32 data[PE_DCM_DDR_E60F20_DCM_TABLE_ITEM_NUM*PE_DCM_DDR_E60F20_DCM_TABLE_SIZE]; ///< data
}
PE_DCM_DDR_E60F20_DCM_TABLE_T;


/**
* ddr data type
*/
	 
typedef struct
{
	 PE_DCM_DDR_E60F20_TOP_HEADER_T      top_h; 	///< top header
	 PE_DCM_DDR_E60F20_DCM_DYN_T         dcm_dny;
	 PE_DCM_DDR_E60F20_DCM_APL_T         dcm_apl;
	 PE_DCM_DDR_E60F20_DCM_GAIN_T        dcm_gain;
	 PE_DCM_DDR_E60F20_DCM_TABLE_T       dcm_table;
	 UINT32 crc;
}
PE_DCM_DDR_DB_PHYS_REG_E60F20_T;


/**
* data type
*/
typedef struct
{
	 PE_DCM_DDR_E60F20_HEADER_T header; ///< header
	 UINT32 data_base;			 ///< data base
}
PE_DCM_DDR_E60F20_DATA_T;

/**
* ddr data type, should sync with PE_DCM_DDR_DB_PHYS_REG_E60F20_T
* - header.sec_type = PE_DCM_DDR_E60F20_SEC_HEADER
* - header.item_num = PE_DCM_DDR_E60F20_SEC_MAX_NUM
* - header.item_size = NA
*/
typedef struct
{
	 PE_DCM_DDR_E60F20_TOP_HEADER_T top_h; 				   ///< top header
	 PE_DCM_DDR_E60F20_DATA_T sec_d[PE_DCM_DDR_E60F20_SEC_MAX_SIZE];	///< section data
}
PE_DCM_DDR_DB_SHDW_REG_E60F20_T;

typedef struct
{
	 union {
		 UINT32 				  *addr;
		 PE_DCM_DDR_DB_SHDW_REG_E60F20_T *data;
	 } shdw;

	 union {
		 volatile UINT32				   *addr;
		 volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *data;
	 } phys;
}
PE_DCM_DDR_DB_REG_TYPE_E60F20_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
	 
#endif	 /* _PE_DCM_DDR_REG_E60F20_H_ */

