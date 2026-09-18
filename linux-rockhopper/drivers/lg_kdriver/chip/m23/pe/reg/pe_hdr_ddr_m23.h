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

/** @file pe_hdr_ddr_m23.h
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
#ifndef _PE_HDR_DDR_M23_H_
#define _PE_HDR_DDR_M23_H_

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
/* hdr ddr version : 0x00 ~ 0xff */
#define PE_HDR_DDR_M23_VERSION			0x7

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
}PE_HDR_DDR_INFO_M23_T;

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
}PE_HDR_DDR_CNT0_M23_T;

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
}PE_HDR_DDR_CNT1_M23_T;

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
}PE_HDR_DDR_CNT2_M23_T;

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
}PE_HDR_DDR_CNT3_M23_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ofst         :24;//23:0
	};
}PE_HDR_DDR_POS_M23_T;

typedef struct
{
	PE_HDR_DDR_INFO_M23_T        info;
	PE_HDR_DDR_CNT0_M23_T        cnt00;//CPU WO, MCU RO
	PE_HDR_DDR_CNT1_M23_T        cnt01;//CPU WO, MCU RO
	PE_HDR_DDR_CNT2_M23_T        cnt02;//CPU WO, MCU RO
	PE_HDR_DDR_CNT3_M23_T        cnt03;//CPU WO, MCU RO
	PE_HDR_DDR_POS_M23_T         pos0[32];
}PE_HDR_DDR_H_M23_T;

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
}PE_HDR_DDR_LUT_M23_T;

/* need to gap over 0x20(to avoid mcu,cpu racing) */
typedef struct
{
	UINT32 rsvd[16];
}PE_HDR_DDR_RSVD_M23_T;

typedef struct
{
	UINT32 hist_cnt;    //24
	UINT32 hist_1[128]; //24
	UINT32 hist_2[128]; //24
	UINT32 hist_3[128]; //24
}PE_HDR_DDR_STAT_M23_T;

/*
size check : 2022/04/07/15:27:56
PE_HDR_DDR_H_M23_T    :   148 B,   0 KB
PE_HDR_DDR_LUT_M23_T  : 37944 B,  37 KB
PE_HDR_DDR_STAT_M23_T :  1540 B,   1 KB
PE_HDR_DDR_RSVD_M23_T :    64 B,   0 KB
PE_HDR_DDR_M23_T      : 39696 B,  38 KB
*/
typedef struct
{
	PE_HDR_DDR_H_M23_T           head;
	PE_HDR_DDR_LUT_M23_T         lut0;
	PE_HDR_DDR_RSVD_M23_T        rsvd;
	PE_HDR_DDR_STAT_M23_T        stat;
}PE_HDR_DDR_M23_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_HDR_DDR_M23_H_ */

