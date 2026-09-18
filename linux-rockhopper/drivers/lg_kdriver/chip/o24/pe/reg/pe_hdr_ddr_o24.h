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

/** @file pe_hdr_ddr_o24.h
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
#ifndef _PE_HDR_DDR_O24_H_
#define _PE_HDR_DDR_O24_H_

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
/* hdr ddr version : 0x00 ~ 0xff */
#define PE_HDR_DDR_O24_VERSION			0x8

/*****************************************************************************************/
/* version.4 main */
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
typedef union {
	UINT32 udata32;
	struct {
	UINT32 version      :8 ;  // 7: 0
	UINT32 support      :8 ;  //15: 8
	};
}PE_HDR_DDR_INFO_O24_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 eotf_0       :4 ;  // 3: 0
	UINT32 eotf_1       :4 ;  // 7: 4
	UINT32 eotf_2       :4 ;  //11: 8
	UINT32 eotf_3       :4 ;  //15:12
	UINT32 oetf_0       :4 ;  //19:16
	UINT32 oetf_1       :4 ;  //23:20
	UINT32 oetf_2       :4 ;  //27:24
	UINT32 oetf_3       :4 ;  //31:28
	};
}PE_HDR_DDR_CNT0_O24_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 tone_0       :4 ;  // 3: 0
	UINT32 tone_1       :4 ;  // 7: 4
	UINT32 tone_2       :4 ;  //11: 8
	UINT32 tone_3       :4 ;  //15:12
	UINT32 tone_4       :4 ;  //19:16
	UINT32 tone_5       :4 ;  //23:20
	UINT32 ylut_0       :4 ;  //27:24
	UINT32 ylut_1       :4 ;  //31:28
	};
}PE_HDR_DDR_CNT1_O24_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ccr_0        :4 ;  // 3: 0
	UINT32 pcc_0        :4 ;  // 7: 4
	UINT32 resvd2       :4 ;  //11: 8
	UINT32 resvd3       :4 ;  //15:12
	UINT32 resvd4       :4 ;  //19:16
	UINT32 resvd5       :4 ;  //23:20
	UINT32 resvd6       :4 ;  //27:24
	UINT32 resvd7       :4 ;  //31:28
	};
}PE_HDR_DDR_CNT2_O24_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 hist         :4 ;  // 3: 0
	UINT32 resvd1       :4 ;  // 7: 4
	UINT32 resvd2       :4 ;  //11: 8
	UINT32 resvd3       :4 ;  //15:12
	UINT32 resvd4       :4 ;  //19:16
	UINT32 resvd5       :4 ;  //23:20
	UINT32 resvd6       :4 ;  //27:24
	UINT32 resvd7       :4 ;  //31:28
	};
}PE_HDR_DDR_CNT3_O24_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ofst         :24;//23:0
	};
}PE_HDR_DDR_POS_O24_T;

//292B
typedef struct
{
	PE_HDR_DDR_INFO_O24_T        info;
	PE_HDR_DDR_CNT0_O24_T        cnt00;//CPU WO, MCU RO
	PE_HDR_DDR_CNT1_O24_T        cnt01;//CPU WO, MCU RO
	PE_HDR_DDR_CNT2_O24_T        cnt02;//CPU WO, MCU RO
	PE_HDR_DDR_CNT3_O24_T        cnt03;//CPU RO, MCU WO
	PE_HDR_DDR_CNT0_O24_T        cnt10;//CPU WO, MCU RO
	PE_HDR_DDR_CNT1_O24_T        cnt11;//CPU WO, MCU RO
	PE_HDR_DDR_CNT2_O24_T        cnt12;//CPU WO, MCU RO
	PE_HDR_DDR_CNT3_O24_T        cnt13;//CPU RO, MCU WO
	PE_HDR_DDR_POS_O24_T         pos0[32];
	PE_HDR_DDR_POS_O24_T         pos1[32];
}PE_HDR_DDR_H_O24_T;

//37KB
typedef struct
{
	UINT32 eotf_0[1024];//00
	UINT32 eotf_1[1024];//01
	UINT32 eotf_2[1024];//02
	UINT32 eotf_3[1024];//03
	UINT32 oetf_0[1024];//04
	UINT32 oetf_1[1024];//05
	UINT32 oetf_2[1024];//06
	UINT32 oetf_3[1024];//07
	UINT32 tone_0[198]; //08
	UINT32 tone_1[198]; //09
	UINT32 tone_2[198]; //10
	UINT32 tone_3[198]; //11
	UINT32 tone_4[198]; //12
	UINT32 tone_5[198]; //13
	UINT32 ylut_0[33];  //14
	UINT32 ylut_1[33];  //15
	UINT32 ccr_0[30];   //16
	UINT32 pcc_0[10];   //17
}PE_HDR_DDR_LUT_O24_T;

//64B
/* need to gap over 0x20(to avoid mcu,cpu racing) */
typedef struct
{
	UINT32 rsvd[16];
}PE_HDR_DDR_RSVD_O24_T;

//1540B
typedef struct
{
	UINT32 hist_cnt;   //24
	UINT32 hist_1[128];//24
	UINT32 hist_2[128];//24
	UINT32 hist_3[128];//24
}PE_HDR_DDR_STAT_O24_T;

/*
size check : 2023/04/11/14:17:37
PE_HDR_DDR_H_O24_T    :   292 B,   0 KB
PE_HDR_DDR_LUT_O24_T  : 37944 B,  37 KB
PE_HDR_DDR_RSVD_O24_T :    64 B,   0 KB
PE_HDR_DDR_STAT_O24_T :  1540 B,   1 KB
PE_HDR_DDR_O24_T      : 79324 B,  77 KB
*/
typedef struct
{
	PE_HDR_DDR_H_O24_T           head;
	PE_HDR_DDR_LUT_O24_T         lut0;
	PE_HDR_DDR_LUT_O24_T         lut1;
	PE_HDR_DDR_RSVD_O24_T        rsvd;
	PE_HDR_DDR_STAT_O24_T        stat0;
	PE_HDR_DDR_STAT_O24_T        stat1;
}PE_HDR_DDR_O24_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_HDR_DDR_O24_H_ */

