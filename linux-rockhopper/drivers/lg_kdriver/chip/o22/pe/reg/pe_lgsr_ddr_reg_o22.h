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

/** @file pe_lgsr_ddr_reg_o22.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  inkyung.park (inkyung.park@lge.com)
 * version	  1.0
 * date		  2019.05.09
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef _PE_LGSR_DDR_REG_O22_H_
#define _PE_LGSR_DDR_REG_O22_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
#define PE_LGSR_DDR_O22_BASE_ADDR		(PE_O22_DDR_DB0_BASE + 0x00100000)

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
	
//#include "pe_lgsr_inf_def_o22.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
/**
* version history
* 0x1 : 20150507, 1st edition
*/
#define PE_LGSR_DDR_O22_DB_VER					(0x2)

#define PE_LGSR_DDR_O22_SEC_MAX_SIZE             50

/* section size */
#define PE_LGSR_DDR_O22_MODE_SIZE                1
#define PE_LGSR_DDR_O22_DRC_LUT_SIZE             PE_DRC_LUT_SIZE
#define PE_LGSR_DDR_O22_INF_WEIGHT_SIZE          6336
#define PE_LGSR_DDR_O22_INF_APB_SIZE             229
/*DUMMY_SIZE = 4 - (APB_SIZE)%4*/
#define PE_LGSR_DDR_O22_INF_DUMMY_SIZE           3

#define PE_LGSR_DDR_O22_INF_SET_NUM              (8*2)

#define PE_LGSR_DDR_O22_DATA_ONLY_SIZE (PE_LGSR_DDR_O22_INF_WEIGHT_SIZE +PE_LGSR_DDR_O22_INF_APB_SIZE)*PE_LGSR_DDR_O22_INF_SET_NUM
/* item number */
#define PE_LGSR_DDR_O22_MODE_ITEM_NUM            1
/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(_x)		(\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_00  )? "SET_00  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_01  )? "SET_01  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_02  )? "SET_02  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_03  )? "SET_03  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_04  )? "SET_04  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_05  )? "SET_05  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_06  )? "SET_06  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_07  )? "SET_07  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_10  )? "SET_10  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_11  )? "SET_11  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_12  )? "SET_12  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_13  )? "SET_13  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_14  )? "SET_14  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_15  )? "SET_15  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_16  )? "SET_16  ":\
	((_x)==PE_LGSR_DDR_O22_SEC_INF_SET_17  )? "SET_17  ":\
	"SEC_NUM  ")


/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
* section type enum
* - causion : should be PE_LGSR_DDR_O22_SEC_NUM < PE_LGSR_DDR_O22_SEC_MAX_SIZE
*/
typedef enum
{
	PE_LGSR_DDR_O22_SEC_INF_SET_00    =  0,  ///< set_00
	PE_LGSR_DDR_O22_SEC_INF_SET_01    =  1,  ///< set_01
	PE_LGSR_DDR_O22_SEC_INF_SET_02    =  2,  ///< set_02
	PE_LGSR_DDR_O22_SEC_INF_SET_03    =  3,  ///< set_03
	PE_LGSR_DDR_O22_SEC_INF_SET_04    =  4,  ///< set_04
	PE_LGSR_DDR_O22_SEC_INF_SET_05    =  5,  ///< set_05
	PE_LGSR_DDR_O22_SEC_INF_SET_06    =  6,  ///< set_06
	PE_LGSR_DDR_O22_SEC_INF_SET_07    =  7,  ///< set_07
	PE_LGSR_DDR_O22_SEC_INF_SET_10    =  8,   ///< set_10
	PE_LGSR_DDR_O22_SEC_INF_SET_11    =  9,   ///< set_11
	PE_LGSR_DDR_O22_SEC_INF_SET_12    =  10,  ///< set_12
	PE_LGSR_DDR_O22_SEC_INF_SET_13    =  11,  ///< set_13
	PE_LGSR_DDR_O22_SEC_INF_SET_14    =  12,  ///< set_14
	PE_LGSR_DDR_O22_SEC_INF_SET_15    =  13,  ///< set_15
	PE_LGSR_DDR_O22_SEC_INF_SET_16    =  14,  ///< set_16
	PE_LGSR_DDR_O22_SEC_INF_SET_17    =  15,  ///< set_17
	PE_LGSR_DDR_O22_SEC_NUM                  ///< max num
}
PE_LGSR_DDR_O22_SEC_TYPE;



/**
* top header type
* - sec_num : PE_LGSR_DDR_O22_SEC_NUM
* - sec_base[N+1] = sec_base[N] + [N]header + ([N]item_num * [N]item_size)
*   ([N]header = sizeof(PE_LGSR_DDR_O22_HEADER_T))
*/
typedef struct
{
	UINT32 version;      ///< version
	UINT32 db_base;      ///< db base addr
	UINT32 sec_num;      ///< section max number
	UINT32 sec_base[PE_LGSR_DDR_O22_SEC_MAX_SIZE];   ///< each section start base
	UINT32 sec_size[PE_LGSR_DDR_O22_SEC_MAX_SIZE];   ///< each section start size
	UINT32 dummy;   ///< dummy
}
PE_LGSR_DDR_O22_TOP_HEADER_T;

/**
* header type
* - sec_type : see PE_LGSR_DDR_O22_SEC_TYPE 
*/
typedef struct
{
	UINT32 version;    ///< version
	UINT32 sec_type;   ///< section type
	UINT32 base_apb;   ///< base_apbr
	UINT32 base_weight;///< base_weight
}
PE_LGSR_DDR_O22_HEADER_T;


/**
* mode
* - header.item_num = PE_LGSR_DDR_O22_MODE_ITEM_NUM
* - header.item_size = PE_LGSR_DDR_O22_MODE_SIZE
* - data, see PE_LGSR_DDR_O22_MD0_T
*
* version history :
* 0x1 : 20140827, 1st edition
*/

/**
* data type
*/
typedef struct
{
	PE_LGSR_DDR_O22_HEADER_T header; ///< header
	UINT32 data_base;           ///< data base
}
PE_LGSR_DDR_O22_DATA_T;


typedef struct
{
	PE_LGSR_DDR_O22_HEADER_T header; ///< header
	UINT32 inf_apb[PE_LGSR_DDR_O22_INF_APB_SIZE]; ///< data
	UINT32 dummy[PE_LGSR_DDR_O22_INF_DUMMY_SIZE]; ///< data
	UINT32 inf_weight[PE_LGSR_DDR_O22_INF_WEIGHT_SIZE]; ///< data
}
PE_LGSR_DDR_O22_INF_APB_WEIGHT_T;


typedef struct
{
	PE_LGSR_DDR_O22_TOP_HEADER_T top_h;     ///< top header
	PE_LGSR_DDR_O22_INF_APB_WEIGHT_T inf_set[PE_LGSR_DDR_O22_INF_SET_NUM];
}
PE_LGSR_DDR_DB_PHYS_REG_O22_T;


/**
* ddr data type, should sync with PE_LGSR_DDR_DB_PHYS_REG_O22_T
* - header.sec_type = PE_LGSR_DDR_O22_SEC_HEADER
* - header.item_num = PE_LGSR_DDR_O22_SEC_MAX_NUM
* - header.item_size = NA
*/
typedef struct
{
	PE_LGSR_DDR_O22_TOP_HEADER_T top_h;                    ///< top header
	PE_LGSR_DDR_O22_DATA_T sec_d[PE_LGSR_DDR_O22_SEC_MAX_SIZE];  ///< section data
}
PE_LGSR_DDR_DB_SHDW_REG_O22_T;

typedef struct
{
	union {
		UINT32                   *addr;
		PE_LGSR_DDR_DB_SHDW_REG_O22_T *data;
	} shdw;

	union {
		volatile UINT32                   *addr;
		volatile PE_LGSR_DDR_DB_PHYS_REG_O22_T *data;
	} phys;
}
PE_LGSR_DDR_DB_REG_TYPE_O22_T;


typedef struct
{
	UINT32 inf_apb[PE_LGSR_DDR_O22_INF_APB_SIZE]; ///< data
	UINT32 inf_weight[PE_LGSR_DDR_O22_INF_WEIGHT_SIZE]; ///< data
}
PE_USER_LGSR_DDR_O22_INF_APB_WEIGHT_T;

typedef struct
{
	PE_USER_LGSR_DDR_O22_INF_APB_WEIGHT_T inf_set[PE_LGSR_DDR_O22_INF_SET_NUM];
}
PE_USER_LGSR_DDR_DB_PHYS_REG_O22_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_LGSR_DDR_REG_O22_H_ */

