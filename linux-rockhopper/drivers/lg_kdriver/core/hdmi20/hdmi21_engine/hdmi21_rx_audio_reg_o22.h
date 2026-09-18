/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/



/** @file
 *
 *  ADEC register details. (used only within kdriver)
 *
 *  author     taejun.lee
 *  version    3.3.0
 *  date       2021.03.31
 *
 */

#ifndef _HDMI21_RX_AUD_REG_O22_H_
#define _HDMI21_RX_AUD_REG_O22_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0000 ram_reserved ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0600 HDMI21_RX_AUD_INTHW_ID0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hmr0spdif0csd_update                   : 1,	//     0
	hmr0spdif1csd_update                   : 1,	//     1
	hmr0spdif2csd_update                   : 1,	//     2
	hmr0spdif3csd_update                   : 1,	//     3
	hmr0spdif0pc_update                    : 1,	//     4
	hmr0spdif1pc_update                    : 1,	//     5
	hmr0spdif2pc_update                    : 1,	//     6
	hmr0spdif3pc_update                    : 1,	//     7
	hmr0spdif0pd_update                    : 1,	//     8
	hmr0spdif1pd_update                    : 1,	//     9
	hmr0spdif2pd_update                    : 1,	//    10
	hmr0spdif3pd_update                    : 1, //    11
	hmr1spdif0csd_update                   : 1,	//    12
	hmr1spdif1csd_update                   : 1,	//    13
	hmr1spdif2csd_update                   : 1,	//    14
	hmr1spdif3csd_update                   : 1,	//    15
	hmr1spdif0pc_update                    : 1,	//    16
	hmr1spdif1pc_update                    : 1,	//    17
	hmr1spdif2pc_update                    : 1,	//    18
	hmr1spdif3pc_update                    : 1,	//    19
	hmr1spdif0pd_update                    : 1,	//    20
	hmr1spdif1pd_update                    : 1,	//    21
	hmr1spdif2pd_update                    : 1,	//    22
	hmr1spdif3pd_update                    : 1, //    23
	hmr2spdif0csd_update                   : 1,	//    24
	hmr2spdif1csd_update                   : 1,	//    25
	hmr2spdif2csd_update                   : 1,	//    26
	hmr2spdif3csd_update                   : 1,	//    27
	hmr2spdif0pc_update                    : 1,	//    28
	hmr2spdif1pc_update                    : 1,	//    29
	hmr2spdif2pc_update                    : 1,	//    30
	hmr2spdif3pc_update                    : 1;	//    31
} HDMI21_RX_AUD_O22_INTHW_ID0;

/*-----------------------------------------------------------------------------
	0x0604 HDMI21_RX_AUD_O22_INTHW_ID1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hmr2spdif0pd_update 				   : 1, //	   0
	hmr2spdif1pd_update 				   : 1, //	   1
	hmr2spdif2pd_update 				   : 1, //	   2
	hmr2spdif3pd_update 				   : 1, //	   3
	hmr3spdif0csd_update				   : 1, //	   4
	hmr3spdif1csd_update				   : 1, //	   5
	hmr3spdif2csd_update				   : 1, //	   6
	hmr3spdif3csd_update				   : 1, //	   7
	hmr3spdif0pc_update 				   : 1, //	   8
	hmr3spdif1pc_update 				   : 1, //	   9
	hmr3spdif2pc_update 				   : 1, //	  10
	hmr3spdif3pc_update 				   : 1, //	  11
	hmr3spdif0pd_update 				   : 1, //	  12
	hmr3spdif1pd_update 				   : 1, //	  13
	hmr3spdif2pd_update 				   : 1, //	  14
	hmr3spdif3pd_update 				   : 1, //	  15
	hmr4spdif0csd_update				   : 1, //	  16
	hmr4spdif1csd_update				   : 1, //	  17
	hmr4spdif2csd_update				   : 1, //	  18
	hmr4spdif3csd_update				   : 1, //	  19
	hmr4spdif0pc_update 				   : 1, //	  20
	hmr4spdif1pc_update 				   : 1, //	  21
	hmr4spdif2pc_update 				   : 1, //	  22
	hmr4spdif3pc_update 				   : 1, //	  23
	hmr4spdif0pd_update 				   : 1, //	  24
	hmr4spdif1pd_update 				   : 1, //	  25
	hmr4spdif2pd_update 				   : 1, //	  26
	hmr4spdif3pd_update 				   : 1, //	  27
	dma0_tx_done_update 				   : 1, //	  28
	Byte_search_interrupt_update 		   : 1, //	  29
	reserved                            : 2;	//    2 reserved
} HDMI21_RX_AUD_O22_INTHW_ID1;

/*-----------------------------------------------------------------------------
	0x0608 HDMI21_RX_AUD_O22_INTHW_ID2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	inthw_pcmmain		 				   : 1, //	   0
	inthw_iec0			 				   : 1, //	   1
	inthw_pcmsub		 				   : 1, //	   2
	inthw_iec1			 				   : 1, //	   3
	inthw_sat0							   : 1, //	   4
	inthw_sat1							   : 1, //	   5
	inthw_sat2							   : 1, //	   6
	inthw_sat3							   : 1, //	   7
	inthw_sat4			 				   : 1, //	   8
	inthw_tpm			 				   : 1, //	   9
	inthw_tpa			 				   : 1, //	  10
	inthw_tpmstc		 				   : 1, //	  11
	inthw_teipc			 				   : 1, //	  12
	inthw_earc_i2s		 				   : 1, //	  13
	inthw_earc_spdif	 				   : 1, //	  14
	inthw_aadi0			 				   : 1, //	  15
	inthw_aadi1			 				   : 1, //	  16
	inthw_aadi2			 				   : 1, //	  17
	inthw_src			 				   : 1, //	  18
	inthw_stcc0			 				   : 1, //	  19
	inthw_stcc1			 				   : 1, //	  20
	inthw_lne			 				   : 1, //	  21
	inthw_aud_clk_cnt	 				   : 1, //	  22
	reserved							   : 9; //    23~31(9 reserved)
} HDMI21_RX_AUD_O22_INTHW_ID2;


/*-----------------------------------------------------------------------------
	0x060C HDMI21_RX_AUD_O22_INTHW_CLR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	aud_inthw_clr					: 1;	//	   0
} HDMI21_RX_AUD_O22_INTHW_CLR;

/*-----------------------------------------------------------------------------
	0x0610 HDMI21_RX_AUD_O22_INTHW_EN ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	aud_inthw_en					: 1;	//	   0
} HDMI21_RX_AUD_O22_INTHW_EN;

/*-----------------------------------------------------------------------------
	0x0614 HDMI21_RX_AUD_O22_INTHW_MASK0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hmr0spdif0csd_update_mask				   : 1, //	   0
	hmr0spdif1csd_update_mask				   : 1, //	   1
	hmr0spdif2csd_update_mask				   : 1, //	   2
	hmr0spdif3csd_update_mask				   : 1, //	   3
	hmr0spdif0pc_update_mask 				   : 1, //	   4
	hmr0spdif1pc_update_mask 				   : 1, //	   5
	hmr0spdif2pc_update_mask 				   : 1, //	   6
	hmr0spdif3pc_update_mask 				   : 1, //	   7
	hmr0spdif0pd_update_mask 				   : 1, //	   8
	hmr0spdif1pd_update_mask 				   : 1, //	   9
	hmr0spdif2pd_update_mask 				   : 1, //	  10
	hmr0spdif3pd_update_mask 				   : 1, //	  11
	hmr1spdif0csd_update_mask				   : 1, //	  12
	hmr1spdif1csd_update_mask				   : 1, //	  13
	hmr1spdif2csd_update_mask				   : 1, //	  14
	hmr1spdif3csd_update_mask				   : 1, //	  15
	hmr1spdif0pc_update_mask 				   : 1, //	  16
	hmr1spdif1pc_update_mask 				   : 1, //	  17
	hmr1spdif2pc_update_mask 				   : 1, //	  18
	hmr1spdif3pc_update_mask 				   : 1, //	  19
	hmr1spdif0pd_update_mask 				   : 1, //	  20
	hmr1spdif1pd_update_mask 				   : 1, //	  21
	hmr1spdif2pd_update_mask 				   : 1, //	  22
	hmr1spdif3pd_update_mask 				   : 1, //	  23
	hmr2spdif0csd_update_mask				   : 1, //	  24
	hmr2spdif1csd_update_mask				   : 1, //	  25
	hmr2spdif2csd_update_mask				   : 1, //	  26
	hmr2spdif3csd_update_mask				   : 1, //	  27
	hmr2spdif0pc_update_mask 				   : 1, //	  28
	hmr2spdif1pc_update_mask 				   : 1, //	  29
	hmr2spdif2pc_update_mask 				   : 1, //	  30
	hmr2spdif3pc_update_mask 				   : 1; //	  31
} HDMI21_RX_AUD_O22_INTHW_MASK0;

/*-----------------------------------------------------------------------------
	0x0618 HDMI21_RX_AUD_O22_INTHW_MASK1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hmr2spdif0pd_update_mask 				   : 1, //	   0
	hmr2spdif1pd_update_mask 				   : 1, //	   1
	hmr2spdif2pd_update_mask 				   : 1, //	   2
	hmr2spdif3pd_update_mask 				   : 1, //	   3
	hmr3spdif0csd_update_mask				   : 1, //	   4
	hmr3spdif1csd_update_mask				   : 1, //	   5
	hmr3spdif2csd_update_mask				   : 1, //	   6
	hmr3spdif3csd_update_mask				   : 1, //	   7
	hmr3spdif0pc_update_mask 				   : 1, //	   8
	hmr3spdif1pc_update_mask 				   : 1, //	   9
	hmr3spdif2pc_update_mask 				   : 1, //	  10
	hmr3spdif3pc_update_mask 				   : 1, //	  11
	hmr3spdif0pd_update_mask 				   : 1, //	  12
	hmr3spdif1pd_update_mask 				   : 1, //	  13
	hmr3spdif2pd_update_mask 				   : 1, //	  14
	hmr3spdif3pd_update_mask 				   : 1, //	  15
	hmr4spdif0csd_update_mask				   : 1, //	  16
	hmr4spdif1csd_update_mask				   : 1, //	  17
	hmr4spdif2csd_update_mask				   : 1, //	  18
	hmr4spdif3csd_update_mask				   : 1, //	  19
	hmr4spdif0pc_update_mask 				   : 1, //	  20
	hmr4spdif1pc_update_mask 				   : 1, //	  21
	hmr4spdif2pc_update_mask 				   : 1, //	  22
	hmr4spdif3pc_update_mask 				   : 1, //	  23
	hmr4spdif0pd_update_mask 				   : 1, //	  24
	hmr4spdif1pd_update_mask 				   : 1, //	  25
	hmr4spdif2pd_update_mask 				   : 1, //	  26
	hmr4spdif3pd_update_mask 				   : 1, //	  27
	dma0_tx_done_update_mask 				   : 1, //	  28
	Byte_search_interrupt_update_mask		   : 1, //	  29
	reserved					     		   : 2; //	  2 reserved
} HDMI21_RX_AUD_O22_INTHW_MASK1;

/*-----------------------------------------------------------------------------
	0x061C HDMI21_RX_AUD_O22_INTHW_MASK2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	inthw_mask_pcmmain		 				   : 1, //	   0
	inthw_mask_iec0			 				   : 1, //	   1
	inthw_mask_pcmsub		 				   : 1, //	   2
	inthw_mask_iec1			 				   : 1, //	   3
	inthw_mask_sat0							   : 1, //	   4
	inthw_mask_sat1							   : 1, //	   5
	inthw_mask_sat2							   : 1, //	   6
	inthw_mask_sat3							   : 1, //	   7
	inthw_mask_sat4			 				   : 1, //	   8
	inthw_mask_tpm			 				   : 1, //	   9
	inthw_mask_tpa			 				   : 1, //	  10
	inthw_mask_tpmstc		 				   : 1, //	  11
	inthw_mask_teipc			 			   : 1, //	  12
	inthw_mask_earc_i2s		 				   : 1, //	  13
	inthw_mask_earc_spdif	 				   : 1, //	  14
	inthw_mask_aadi0			 			   : 1, //	  15
	inthw_mask_aadi1			 			   : 1, //	  16
	inthw_mask_aadi2			 			   : 1, //	  17
	inthw_mask_src			 				   : 1, //	  18
	inthw_mask_stcc0			 			   : 1, //	  19
	inthw_mask_stcc1			 			   : 1, //	  20
	inthw_mask_lne			 				   : 1, //	  21
	inthw_mask_aud_clk_cnt	 				   : 1, //	  22
	reserved							   	   : 9; //    23~31(9 reserved)
} HDMI21_RX_AUD_O22_INTHW_MASK2;


/*-----------------------------------------------------------------------------
	0x0670 HDMI21_RX_AUD_O22_SWRESET ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	aresetout                       : 1,	//     0
	apbresetout                     : 1,	//     1
	aversetout                      : 1,	//     2
	fs22resetout                    : 1,	//     3
	fs20resetout                    : 1,	//     4
	fs21resetout                    : 1,	//     5
	fs23resetout                    : 1,	//     6
	fs24resetout                    : 1,	//     7
	fs25resetout                    : 1,	//     8
	fs26resetout                    : 1,	//     9
	dsp0ocdresetout                 : 1,	//    10
	dsp1ocdresetout                 : 1,	//    11
	dsp0bresetout                   : 1,	//    12
	dsp1bresetout                   : 1,	//    13
	aadresetout                     : 1,	//    14
	aadapbresetout                  : 1,	//    15
	aadferesetout                   : 1,	//    16
	hmr0spdifresetout               : 1,	//    17
	hmr1spdifresetout               : 1,	//    18
	hmr2spdifresetout               : 1,	//    19
	hmr3spdifresetout               : 1,	//    20
	dsp0dreset                      : 1,	//    21
	dsp1dreset                      : 1,	//    22
	aad_Tresetout                   : 1,	//    23
	aad_i2s_resetout                : 1,	//    24
	dsp2ocdresetout                 : 1,	//    25
	dsp2bresetout                   : 1,    //    26
	dsp3ocdresetout                 : 1,    //    27
	dsp3bresetout                   : 1,    //    28
	dsp2dreset                      : 1,    //    29
	dsp3dreset                      : 1,    //    30
	reserved                        : 1;	//    31
} HDMI21_RX_AUD_O22_SWRESET;

/* HMR0 */
/*-----------------------------------------------------------------------------
	0x1000 HDMI21_RX_AUD_O22_HMR0_CSD0_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD0_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD0_0;

/*-----------------------------------------------------------------------------
	0x1004 HDMI21_RX_AUD_O22_HMR0_CSD1_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD1_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD1_0;

/*-----------------------------------------------------------------------------
	0x1008 HDMI21_RX_AUD_O22_HMR0_CSD2_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD2_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD2_0;

/*-----------------------------------------------------------------------------
	0x100C HDMI21_RX_AUD_O22_HMR0_CSD3_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD3_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD3_0;

/*-----------------------------------------------------------------------------
	0x1010 HDMI21_RX_AUD_O22_HMR0_CSD4_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD4_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD4_0;

/*-----------------------------------------------------------------------------
	0x1014 HDMI21_RX_AUD_O22_HMR0_CSD5_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD5_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD5_0;

/*-----------------------------------------------------------------------------
	0x1018 HDMI21_RX_AUD_O22_HMR0_PCPD_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR0pd_0                          :16,	//  0:15
	HMR0pc_0                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR0_PCPD_0;

/*-----------------------------------------------------------------------------
	0x101C HDMI21_RX_AUD_O22_HMR0_PCPD_0_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR0pc_0                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR0pd_0                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR0_PCPD_0_CLEAR;


/*-----------------------------------------------------------------------------
	0x1020 HDMI21_RX_AUD_O22_HMR0_CSD0_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD0_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD0_1;

/*-----------------------------------------------------------------------------
	0x1024 HDMI21_RX_AUD_O22_HMR0_CSD1_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD1_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD1_1;

/*-----------------------------------------------------------------------------
	0x1028 HDMI21_RX_AUD_O22_HMR0_CSD2_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD2_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD2_1;

/*-----------------------------------------------------------------------------
	0x102C HDMI21_RX_AUD_O22_HMR0_CSD3_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD3_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD3_1;

/*-----------------------------------------------------------------------------
	0x1010 HDMI21_RX_AUD_O22_HMR0_CSD4_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD4_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD4_1;

/*-----------------------------------------------------------------------------
	0x1034 HDMI21_RX_AUD_O22_HMR0_CSD5_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD5_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD5_1;

/*-----------------------------------------------------------------------------
	0x1038 HDMI21_RX_AUD_O22_HMR0_PCPD_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR0pd_1                          :16,	//  0:15
	HMR0pc_1                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR0_PCPD_1;

/*-----------------------------------------------------------------------------
	0x103C HDMI21_RX_AUD_O22_HMR0_PCPD_1_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR0pc_1                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR0pd_1                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR0_PCPD_1_CLEAR;

/*-----------------------------------------------------------------------------
	0x1040 HDMI21_RX_AUD_O22_HMR0_CSD0_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD0_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD0_2;

/*-----------------------------------------------------------------------------
	0x1044 HDMI21_RX_AUD_O22_HMR0_CSD1_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD1_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD1_2;

/*-----------------------------------------------------------------------------
	0x1048 HDMI21_RX_AUD_O22_HMR0_CSD2_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD2_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD2_2;

/*-----------------------------------------------------------------------------
	0x104C HDMI21_RX_AUD_O22_HMR0_CSD3_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD3_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD3_2;

/*-----------------------------------------------------------------------------
	0x1050 HDMI21_RX_AUD_O22_HMR0_CSD4_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD4_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD4_2;

/*-----------------------------------------------------------------------------
	0x1054 HDMI21_RX_AUD_O22_HMR0_CSD5_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD5_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD5_2;

/*-----------------------------------------------------------------------------
	0x1058 HDMI21_RX_AUD_O22_HMR0_PCPD_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR0pd_2                          :16,	//  0:15
	HMR0pc_2                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR0_PCPD_2;

/*-----------------------------------------------------------------------------
	0x105C HDMI21_RX_AUD_O22_HMR0_PCPD_2_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR0pc_2                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR0pd_2                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR0_PCPD_2_CLEAR;


/*-----------------------------------------------------------------------------
	0x1060 HDMI21_RX_AUD_O22_HMR0_CSD0_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD0_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD0_3;

/*-----------------------------------------------------------------------------
	0x1064 HDMI21_RX_AUD_O22_HMR0_CSD1_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD1_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD1_3;

/*-----------------------------------------------------------------------------
	0x1068 HDMI21_RX_AUD_O22_HMR0_CSD2_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD2_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD2_3;

/*-----------------------------------------------------------------------------
	0x106C HDMI21_RX_AUD_O22_HMR0_CSD3_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD3_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD3_3;

/*-----------------------------------------------------------------------------
	0x1070 HDMI21_RX_AUD_O22_HMR0_CSD4_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD4_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD4_3;

/*-----------------------------------------------------------------------------
	0x1074 HDMI21_RX_AUD_O22_HMR0_CSD5_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI0_CSD5_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR0_CSD5_3;

/*-----------------------------------------------------------------------------
	0x1078 HDMI21_RX_AUD_O22_HMR0_PCPD_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR0pd_3                          :16,	//  0:15
	HMR0pc_3                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR0_PCPD_3;

/*-----------------------------------------------------------------------------
	0x107C HDMI21_RX_AUD_O22_HMR0_PCPD_3_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR0pc_3                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR0pd_3                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR0_PCPD_3_CLEAR;


/*-----------------------------------------------------------------------------
	0x1080 HDMI21_RX_AUD_O22_HMR0_MUTE ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR0mute                        : 1;	//     0
} HDMI21_RX_AUD_O22_HMR0_MUTE;



/* HMR1 */
/*-----------------------------------------------------------------------------
	0x1100 HDMI21_RX_AUD_O22_HMR1_CSD0_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD0_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD0_0;

/*-----------------------------------------------------------------------------
	0x1104 HDMI21_RX_AUD_O22_HMR1_CSD1_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD1_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD1_0;

/*-----------------------------------------------------------------------------
	0x1108 HDMI21_RX_AUD_O22_HMR1_CSD2_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD2_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD2_0;

/*-----------------------------------------------------------------------------
	0x110C HDMI21_RX_AUD_O22_HMR1_CSD3_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD3_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD3_0;

/*-----------------------------------------------------------------------------
	0x1110 HDMI21_RX_AUD_O22_HMR1_CSD4_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD4_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD4_0;

/*-----------------------------------------------------------------------------
	0x1114 HDMI21_RX_AUD_O22_HMR1_CSD5_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD5_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD5_0;

/*-----------------------------------------------------------------------------
	0x1118 HDMI21_RX_AUD_O22_HMR1_PCPD_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR1pd_0                          :16,	//  0:15
	HMR1pc_0                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR1_PCPD_0;

/*-----------------------------------------------------------------------------
	0x111C HDMI21_RX_AUD_O22_HMR1_PCPD_0_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR1pc_0                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR1pd_0                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR1_PCPD_0_CLEAR;


/*-----------------------------------------------------------------------------
	0x1120 HDMI21_RX_AUD_O22_HMR1_CSD0_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD0_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD0_1;

/*-----------------------------------------------------------------------------
	0x1124 HDMI21_RX_AUD_O22_HMR1_CSD1_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD1_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD1_1;

/*-----------------------------------------------------------------------------
	0x1128 HDMI21_RX_AUD_O22_HMR1_CSD2_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD2_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD2_1;

/*-----------------------------------------------------------------------------
	0x112C HDMI21_RX_AUD_O22_HMR1_CSD3_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD3_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD3_1;

/*-----------------------------------------------------------------------------
	0x1110 HDMI21_RX_AUD_O22_HMR1_CSD4_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD4_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD4_1;

/*-----------------------------------------------------------------------------
	0x1134 HDMI21_RX_AUD_O22_HMR1_CSD5_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD5_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD5_1;

/*-----------------------------------------------------------------------------
	0x1138 HDMI21_RX_AUD_O22_HMR1_PCPD_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR1pd_1                          :16,	//  0:15
	HMR1pc_1                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR1_PCPD_1;

/*-----------------------------------------------------------------------------
	0x113C HDMI21_RX_AUD_O22_HMR1_PCPD_1_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR1pc_1                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR1pd_1                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR1_PCPD_1_CLEAR;


/*-----------------------------------------------------------------------------
	0x1140 HDMI21_RX_AUD_O22_HMR1_CSD0_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD0_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD0_2;

/*-----------------------------------------------------------------------------
	0x1144 HDMI21_RX_AUD_O22_HMR1_CSD1_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD1_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD1_2;

/*-----------------------------------------------------------------------------
	0x1148 HDMI21_RX_AUD_O22_HMR1_CSD2_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD2_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD2_2;

/*-----------------------------------------------------------------------------
	0x114C HDMI21_RX_AUD_O22_HMR1_CSD3_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD3_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD3_2;

/*-----------------------------------------------------------------------------
	0x1150 HDMI21_RX_AUD_O22_HMR1_CSD4_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD4_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD4_2;

/*-----------------------------------------------------------------------------
	0x1154 HDMI21_RX_AUD_O22_HMR1_CSD5_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD5_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD5_2;

/*-----------------------------------------------------------------------------
	0x1158 HDMI21_RX_AUD_O22_HMR1_PCPD_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR1pd_2                          :16,	//  0:15
	HMR1pc_2                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR1_PCPD_2;

/*-----------------------------------------------------------------------------
	0x115C HDMI21_RX_AUD_O22_HMR1_PCPD_2_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR1pc_2                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR1pd_2                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR1_PCPD_2_CLEAR;


/*-----------------------------------------------------------------------------
	0x1160 HDMI21_RX_AUD_O22_HMR1_CSD0_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD0_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD0_3;

/*-----------------------------------------------------------------------------
	0x1164 HDMI21_RX_AUD_O22_HMR1_CSD1_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD1_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD1_3;

/*-----------------------------------------------------------------------------
	0x1168 HDMI21_RX_AUD_O22_HMR1_CSD2_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD2_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD2_3;

/*-----------------------------------------------------------------------------
	0x116C HDMI21_RX_AUD_O22_HMR1_CSD3_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD3_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD3_3;

/*-----------------------------------------------------------------------------
	0x1170 HDMI21_RX_AUD_O22_HMR1_CSD4_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD4_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD4_3;

/*-----------------------------------------------------------------------------
	0x1174 HDMI21_RX_AUD_O22_HMR1_CSD5_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI1_CSD5_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR1_CSD5_3;

/*-----------------------------------------------------------------------------
	0x1178 HDMI21_RX_AUD_O22_HMR1_PCPD_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR1pd_3                          :16,	//  0:15
	HMR1pc_3                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR1_PCPD_3;

/*-----------------------------------------------------------------------------
	0x117C HDMI21_RX_AUD_O22_HMR1_PCPD_3_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR1pc_3                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR1pd_3                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR1_PCPD_3_CLEAR;


/*-----------------------------------------------------------------------------
	0x1180 HDMI21_RX_AUD_O22_HMR1_MUTE ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR1mute                        : 1;	//     0
} HDMI21_RX_AUD_O22_HMR1_MUTE;


/* HMR2 */
/*-----------------------------------------------------------------------------
	0x1200 HDMI21_RX_AUD_O22_HMR2_CSD0_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD0_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD0_0;

/*-----------------------------------------------------------------------------
	0x1204 HDMI21_RX_AUD_O22_HMR2_CSD1_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD1_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD1_0;

/*-----------------------------------------------------------------------------
	0x1208 HDMI21_RX_AUD_O22_HMR2_CSD2_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD2_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD2_0;

/*-----------------------------------------------------------------------------
	0x120C HDMI21_RX_AUD_O22_HMR2_CSD3_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD3_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD3_0;

/*-----------------------------------------------------------------------------
	0x1210 HDMI21_RX_AUD_O22_HMR2_CSD4_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD4_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD4_0;

/*-----------------------------------------------------------------------------
	0x1214 HDMI21_RX_AUD_O22_HMR2_CSD5_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD5_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD5_0;

/*-----------------------------------------------------------------------------
	0x1218 HDMI21_RX_AUD_O22_HMR2_PCPD_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR2pd_0                          :16,	//  0:15
	HMR2pc_0                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR2_PCPD_0;

/*-----------------------------------------------------------------------------
	0x121C HDMI21_RX_AUD_O22_HMR2_PCPD_0_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR2pc_0                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR2pd_0                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR2_PCPD_0_CLEAR;


/*-----------------------------------------------------------------------------
	0x1220 HDMI21_RX_AUD_O22_HMR2_CSD0_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD0_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD0_1;

/*-----------------------------------------------------------------------------
	0x1224 HDMI21_RX_AUD_O22_HMR2_CSD1_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD1_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD1_1;

/*-----------------------------------------------------------------------------
	0x1228 HDMI21_RX_AUD_O22_HMR2_CSD2_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD2_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD2_1;

/*-----------------------------------------------------------------------------
	0x122C HDMI21_RX_AUD_O22_HMR2_CSD3_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD3_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD3_1;

/*-----------------------------------------------------------------------------
	0x1210 HDMI21_RX_AUD_O22_HMR2_CSD4_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD4_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD4_1;

/*-----------------------------------------------------------------------------
	0x1234 HDMI21_RX_AUD_O22_HMR2_CSD5_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD5_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD5_1;

/*-----------------------------------------------------------------------------
	0x1238 HDMI21_RX_AUD_O22_HMR2_PCPD_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR2pd_1                          :16,	//  0:15
	HMR2pc_1                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR2_PCPD_1;

/*-----------------------------------------------------------------------------
	0x123C HDMI21_RX_AUD_O22_HMR2_PCPD_1_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR2pc_1                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR2pd_1                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR2_PCPD_1_CLEAR;


/*-----------------------------------------------------------------------------
	0x1240 HDMI21_RX_AUD_O22_HMR2_CSD0_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD0_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD0_2;

/*-----------------------------------------------------------------------------
	0x1244 HDMI21_RX_AUD_O22_HMR2_CSD1_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD1_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD1_2;

/*-----------------------------------------------------------------------------
	0x1248 HDMI21_RX_AUD_O22_HMR2_CSD2_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD2_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD2_2;

/*-----------------------------------------------------------------------------
	0x124C HDMI21_RX_AUD_O22_HMR2_CSD3_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD3_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD3_2;

/*-----------------------------------------------------------------------------
	0x1250 HDMI21_RX_AUD_O22_HMR2_CSD4_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD4_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD4_2;

/*-----------------------------------------------------------------------------
	0x1254 HDMI21_RX_AUD_O22_HMR2_CSD5_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD5_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD5_2;

/*-----------------------------------------------------------------------------
	0x1258 HDMI21_RX_AUD_O22_HMR2_PCPD_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR2pd_2                          :16,	//  0:15
	HMR2pc_2                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR2_PCPD_2;

/*-----------------------------------------------------------------------------
	0x125C HDMI21_RX_AUD_O22_HMR2_PCPD_2_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR2pc_2                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR2pd_2                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR2_PCPD_2_CLEAR;


/*-----------------------------------------------------------------------------
	0x1260 HDMI21_RX_AUD_O22_HMR2_CSD0_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD0_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD0_3;

/*-----------------------------------------------------------------------------
	0x1264 HDMI21_RX_AUD_O22_HMR2_CSD1_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD1_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD1_3;

/*-----------------------------------------------------------------------------
	0x1268 HDMI21_RX_AUD_O22_HMR2_CSD2_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD2_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD2_3;

/*-----------------------------------------------------------------------------
	0x126C HDMI21_RX_AUD_O22_HMR2_CSD3_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD3_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD3_3;

/*-----------------------------------------------------------------------------
	0x1270 HDMI21_RX_AUD_O22_HMR2_CSD4_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD4_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD4_3;

/*-----------------------------------------------------------------------------
	0x1274 HDMI21_RX_AUD_O22_HMR2_CSD5_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI2_CSD5_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR2_CSD5_3;

/*-----------------------------------------------------------------------------
	0x1278 HDMI21_RX_AUD_O22_HMR2_PCPD_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR2pd_3                          :16,	//  0:15
	HMR2pc_3                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR2_PCPD_3;

/*-----------------------------------------------------------------------------
	0x127C HDMI21_RX_AUD_O22_HMR2_PCPD_3_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR2pc_3                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR2pd_3                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR2_PCPD_3_CLEAR;


/*-----------------------------------------------------------------------------
	0x1280 HDMI21_RX_AUD_O22_HMR2_MUTE ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR2mute                        : 1;	//     0
} HDMI21_RX_AUD_O22_HMR2_MUTE;


/* HMR3 */
/*-----------------------------------------------------------------------------
	0x1300 HDMI21_RX_AUD_O22_HMR3_CSD0_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD0_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD0_0;

/*-----------------------------------------------------------------------------
	0x1304 HDMI21_RX_AUD_O22_HMR3_CSD1_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD1_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD1_0;

/*-----------------------------------------------------------------------------
	0x1308 HDMI21_RX_AUD_O22_HMR3_CSD2_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD2_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD2_0;

/*-----------------------------------------------------------------------------
	0x130C HDMI21_RX_AUD_O22_HMR3_CSD3_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD3_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD3_0;

/*-----------------------------------------------------------------------------
	0x1310 HDMI21_RX_AUD_O22_HMR3_CSD4_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD4_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD4_0;

/*-----------------------------------------------------------------------------
	0x1314 HDMI21_RX_AUD_O22_HMR3_CSD5_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD5_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD5_0;

/*-----------------------------------------------------------------------------
	0x1318 HDMI21_RX_AUD_O22_HMR3_PCPD_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR3pd_0                          :16,	//  0:15
	HMR3pc_0                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR3_PCPD_0;

/*-----------------------------------------------------------------------------
	0x131C HDMI21_RX_AUD_O22_HMR3_PCPD_0_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR3pc_0                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR3pd_0                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR3_PCPD_0_CLEAR;


/*-----------------------------------------------------------------------------
	0x1320 HDMI21_RX_AUD_O22_HMR3_CSD0_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD0_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD0_1;

/*-----------------------------------------------------------------------------
	0x1324 HDMI21_RX_AUD_O22_HMR3_CSD1_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD1_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD1_1;

/*-----------------------------------------------------------------------------
	0x1328 HDMI21_RX_AUD_O22_HMR3_CSD2_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD2_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD2_1;

/*-----------------------------------------------------------------------------
	0x132C HDMI21_RX_AUD_O22_HMR3_CSD3_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD3_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD3_1;

/*-----------------------------------------------------------------------------
	0x1310 HDMI21_RX_AUD_O22_HMR3_CSD4_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD4_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD4_1;

/*-----------------------------------------------------------------------------
	0x1334 HDMI21_RX_AUD_O22_HMR3_CSD5_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD5_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD5_1;

/*-----------------------------------------------------------------------------
	0x1338 HDMI21_RX_AUD_O22_HMR3_PCPD_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR3pd_1                          :16,	//  0:15
	HMR3pc_1                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR3_PCPD_1;

/*-----------------------------------------------------------------------------
	0x131C HDMI21_RX_AUD_O22_HMR3_PCPD_1_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR3pc_1                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR3pd_1                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR3_PCPD_1_CLEAR;


/*-----------------------------------------------------------------------------
	0x1340 HDMI21_RX_AUD_O22_HMR3_CSD0_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD0_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD0_2;

/*-----------------------------------------------------------------------------
	0x1344 HDMI21_RX_AUD_O22_HMR3_CSD1_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD1_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD1_2;

/*-----------------------------------------------------------------------------
	0x1348 HDMI21_RX_AUD_O22_HMR3_CSD2_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD2_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD2_2;

/*-----------------------------------------------------------------------------
	0x134C HDMI21_RX_AUD_O22_HMR3_CSD3_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD3_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD3_2;

/*-----------------------------------------------------------------------------
	0x1350 HDMI21_RX_AUD_O22_HMR3_CSD4_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD4_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD4_2;

/*-----------------------------------------------------------------------------
	0x1354 HDMI21_RX_AUD_O22_HMR3_CSD5_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD5_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD5_2;

/*-----------------------------------------------------------------------------
	0x1358 HDMI21_RX_AUD_O22_HMR3_PCPD_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR3pd_2                          :16,	//  0:15
	HMR3pc_2                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR3_PCPD_2;

/*-----------------------------------------------------------------------------
	0x135C HDMI21_RX_AUD_O22_HMR3_PCPD_2_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR3pc_2                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR3pd_2                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR3_PCPD_2_CLEAR;


/*-----------------------------------------------------------------------------
	0x1360 HDMI21_RX_AUD_O22_HMR3_CSD0_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD0_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD0_3;

/*-----------------------------------------------------------------------------
	0x1364 HDMI21_RX_AUD_O22_HMR3_CSD1_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD1_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD1_3;

/*-----------------------------------------------------------------------------
	0x1368 HDMI21_RX_AUD_O22_HMR3_CSD2_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD2_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD2_3;

/*-----------------------------------------------------------------------------
	0x136C HDMI21_RX_AUD_O22_HMR3_CSD3_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD3_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD3_3;

/*-----------------------------------------------------------------------------
	0x1370 HDMI21_RX_AUD_O22_HMR3_CSD4_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD4_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD4_3;

/*-----------------------------------------------------------------------------
	0x1374 HDMI21_RX_AUD_O22_HMR3_CSD5_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI3_CSD5_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR3_CSD5_3;

/*-----------------------------------------------------------------------------
	0x1378 HDMI21_RX_AUD_O22_HMR3_PCPD_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR3pd_3                          :16,	//  0:15
	HMR3pc_3                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR3_PCPD_3;

/*-----------------------------------------------------------------------------
	0x137C HDMI21_RX_AUD_O22_HMR3_PCPD_3_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR3pc_3                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR3pd_3                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR3_PCPD_3_CLEAR;


/*-----------------------------------------------------------------------------
	0x1380 HDMI21_RX_AUD_O22_HMR3_MUTE ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR3mute                        : 1;	//     0
} HDMI21_RX_AUD_O22_HMR3_MUTE;


/* HMR4 */
/*-----------------------------------------------------------------------------
	0x1400 HDMI21_RX_AUD_O22_HMR4_CSD0_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD0_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD0_0;

/*-----------------------------------------------------------------------------
	0x1404 HDMI21_RX_AUD_O22_HMR4_CSD1_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD1_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD1_0;

/*-----------------------------------------------------------------------------
	0x1408 HDMI21_RX_AUD_O22_HMR4_CSD2_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD2_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD2_0;

/*-----------------------------------------------------------------------------
	0x140C HDMI21_RX_AUD_O22_HMR4_CSD3_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD3_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD3_0;

/*-----------------------------------------------------------------------------
	0x1410 HDMI21_RX_AUD_O22_HMR4_CSD4_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD4_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD4_0;

/*-----------------------------------------------------------------------------
	0x1414 HDMI21_RX_AUD_O22_HMR4_CSD5_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD5_0                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD5_0;

/*-----------------------------------------------------------------------------
	0x1418 HDMI21_RX_AUD_O22_HMR4_PCPD_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR4pd_0                          :16,	//  0:15
	HMR4pc_0                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR4_PCPD_0;

/*-----------------------------------------------------------------------------
	0x141C HDMI21_RX_AUD_O22_HMR4_PCPD_0_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR4pc_0                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR4pd_0                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR4_PCPD_0_CLEAR;


/*-----------------------------------------------------------------------------
	0x1420 HDMI21_RX_AUD_O22_HMR4_CSD0_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD0_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD0_1;

/*-----------------------------------------------------------------------------
	0x1424 HDMI21_RX_AUD_O22_HMR4_CSD1_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD1_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD1_1;

/*-----------------------------------------------------------------------------
	0x1428 HDMI21_RX_AUD_O22_HMR4_CSD2_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD2_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD2_1;

/*-----------------------------------------------------------------------------
	0x142C HDMI21_RX_AUD_O22_HMR4_CSD3_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD3_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD3_1;

/*-----------------------------------------------------------------------------
	0x1410 HDMI21_RX_AUD_O22_HMR4_CSD4_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD4_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD4_1;

/*-----------------------------------------------------------------------------
	0x1434 HDMI21_RX_AUD_O22_HMR4_CSD5_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD5_1                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD5_1;

/*-----------------------------------------------------------------------------
	0x1438 HDMI21_RX_AUD_O22_HMR4_PCPD_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR4pd_1                          :16,	//  0:15
	HMR4pc_1                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR4_PCPD_1;

/*-----------------------------------------------------------------------------
	0x143C HDMI21_RX_AUD_O22_HMR4_PCPD_1_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR4pc_1                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR4pd_1                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR4_PCPD_1_CLEAR;


/*-----------------------------------------------------------------------------
	0x1440 HDMI21_RX_AUD_O22_HMR4_CSD0_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD0_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD0_2;

/*-----------------------------------------------------------------------------
	0x1444 HDMI21_RX_AUD_O22_HMR4_CSD1_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD1_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD1_2;

/*-----------------------------------------------------------------------------
	0x1448 HDMI21_RX_AUD_O22_HMR4_CSD2_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD2_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD2_2;

/*-----------------------------------------------------------------------------
	0x144C HDMI21_RX_AUD_O22_HMR4_CSD3_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD3_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD3_2;

/*-----------------------------------------------------------------------------
	0x1450 HDMI21_RX_AUD_O22_HMR4_CSD4_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD4_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD4_2;

/*-----------------------------------------------------------------------------
	0x1454 HDMI21_RX_AUD_O22_HMR4_CSD5_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD5_2                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD5_2;

/*-----------------------------------------------------------------------------
	0x1458 HDMI21_RX_AUD_O22_HMR4_PCPD_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR4pd_2                          :16,	//  0:15
	HMR4pc_2                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR4_PCPD_2;

/*-----------------------------------------------------------------------------
	0x145C HDMI21_RX_AUD_O22_HMR4_PCPD_2_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR4pc_2                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR4pd_2                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR4_PCPD_2_CLEAR;


/*-----------------------------------------------------------------------------
	0x1460 HDMI21_RX_AUD_O22_HMR4_CSD0_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD0_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD0_3;

/*-----------------------------------------------------------------------------
	0x1464 HDMI21_RX_AUD_O22_HMR4_CSD1_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD1_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD1_3;

/*-----------------------------------------------------------------------------
	0x1468 HDMI21_RX_AUD_O22_HMR4_CSD2_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD2_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD2_3;

/*-----------------------------------------------------------------------------
	0x146C HDMI21_RX_AUD_O22_HMR4_CSD3_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD3_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD3_3;

/*-----------------------------------------------------------------------------
	0x1470 HDMI21_RX_AUD_O22_HMR4_CSD4_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD4_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD4_3;

/*-----------------------------------------------------------------------------
	0x1474 HDMI21_RX_AUD_O22_HMR4_CSD5_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HDMI4_CSD5_3                        ;   	// 31: 0
} HDMI21_RX_AUD_O22_HMR4_CSD5_3;

/*-----------------------------------------------------------------------------
	0x1478 HDMI21_RX_AUD_O22_HMR4_PCPD_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR4pd_3                          :16,	//  0:15
	HMR4pc_3                          :16;	// 16:31
} HDMI21_RX_AUD_O22_HMR4_PCPD_3;

/*-----------------------------------------------------------------------------
	0x147C HDMI21_RX_AUD_O22_HMR4_PCPD_3_CLEAR ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	CLEAR_HMR4pc_3                          : 1,	//  0
	reserved_01				   	   			: 3, 	//  1~3(3 reserved)
	CLEAR_HMR4pd_3                          : 1,	//  4
	reserved_02				   	   			:27; 	//  5~31(27 reserved)
} HDMI21_RX_AUD_O22_HMR4_PCPD_3_CLEAR;


/*-----------------------------------------------------------------------------
	0x1480 HDMI21_RX_AUD_O22_HMR4_MUTE ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	HMR4mute                        : 1;	//     0
} HDMI21_RX_AUD_O22_HMR4_MUTE;



typedef struct {
	UINT32                          	ram_reserved                    ;	// 0x0000 : ''
	UINT32                          	                 __rsvd_00[ 383];	// 0x0004 ~ 0x05FC
	HDMI21_RX_AUD_O22_INTHW_ID0             AUD_INTHW_ID0          	        ;	// 0x0600 : ''
	HDMI21_RX_AUD_O22_INTHW_ID1             AUD_INTHW_ID1                   ;	// 0x0604 : ''
	HDMI21_RX_AUD_O22_INTHW_ID2             AUD_INTHW_ID2                   ;	// 0x0608 : ''
	HDMI21_RX_AUD_O22_INTHW_CLR             AUD_INTHW_CLR                   ;	// 0x060C : ''
	HDMI21_RX_AUD_O22_INTHW_EN              AUD_INTHW_EN                    ;	// 0x0610 : ''
	HDMI21_RX_AUD_O22_INTHW_MASK0           AUD_INTHW_MASK0                 ;	// 0x0614 : ''
	HDMI21_RX_AUD_O22_INTHW_MASK1           AUD_INTHW_MASK1                 ;	// 0x0618 : ''
	HDMI21_RX_AUD_O22_INTHW_MASK2           AUD_INTHW_MASK2                 ;	// 0x061C : ''
	UINT32                          	                 __rsvd_01[  20];	// 0x0620 ~ 0x066C
	HDMI21_RX_AUD_O22_SWRESET               AUD_SWRESET                     ;	// 0x0670 : ''	
	UINT32                          	                 __rsvd_02[ 611];	// 0x0674 ~ 0x0FFC
	HDMI21_RX_AUD_O22_HMR0_CSD0_0			AUD_HMR0_CSD0_0                 ;	// 0x1000 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD1_0			AUD_HMR0_CSD1_0                 ;	// 0x1004 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD2_0			AUD_HMR0_CSD2_0                 ;	// 0x1008 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD3_0			AUD_HMR0_CSD3_0                 ;	// 0x100C : ''
	
	
	HDMI21_RX_AUD_O22_HMR0_CSD4_0			AUD_HMR0_CSD4_0                 ;	// 0x1010 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD5_0			AUD_HMR0_CSD5_0                 ;	// 0x1014 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_0			AUD_HMR0_PCPD_0                 ;	// 0x1018 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_0_CLEAR     AUD_HMR0_PCPD_0_CLEAR			;	// 0x101C : ''
	HDMI21_RX_AUD_O22_HMR0_CSD0_1			AUD_HMR0_CSD0_1                 ;	// 0x1020 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD1_1			AUD_HMR0_CSD1_1                 ;	// 0x1024 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD2_1			AUD_HMR0_CSD2_1                 ;	// 0x1028 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD3_1			AUD_HMR0_CSD3_1                 ;	// 0x102C : ''
	HDMI21_RX_AUD_O22_HMR0_CSD4_1			AUD_HMR0_CSD4_1                 ;	// 0x1030 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD5_1			AUD_HMR0_CSD5_1                 ;	// 0x1034 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_1			AUD_HMR0_PCPD_1                 ;	// 0x1038 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_1_CLEAR     AUD_HMR0_PCPD_1_CLEAR			;	// 0x103C : ''
	HDMI21_RX_AUD_O22_HMR0_CSD0_2			AUD_HMR0_CSD0_2                 ;	// 0x1040 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD1_2			AUD_HMR0_CSD1_2                 ;	// 0x1044 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD2_2			AUD_HMR0_CSD2_2                 ;	// 0x1048 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD3_2			AUD_HMR0_CSD3_2                 ;	// 0x104C : ''
	HDMI21_RX_AUD_O22_HMR0_CSD4_2			AUD_HMR0_CSD4_2                 ;	// 0x1050 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD5_2			AUD_HMR0_CSD5_2                 ;	// 0x1054 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_2			AUD_HMR0_PCPD_2                 ;	// 0x1058 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_2_CLEAR     AUD_HMR0_PCPD_2_CLEAR			;	// 0x105C : ''
	HDMI21_RX_AUD_O22_HMR0_CSD0_3			AUD_HMR0_CSD0_3                 ;	// 0x1060 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD1_3			AUD_HMR0_CSD1_3                 ;	// 0x1064 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD2_3			AUD_HMR0_CSD2_3                 ;	// 0x1068 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD3_3			AUD_HMR0_CSD3_3                 ;	// 0x106C : ''
	HDMI21_RX_AUD_O22_HMR0_CSD4_3			AUD_HMR0_CSD4_3                 ;	// 0x1070 : ''
	HDMI21_RX_AUD_O22_HMR0_CSD5_3			AUD_HMR0_CSD5_3                 ;	// 0x1074 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_3			AUD_HMR0_PCPD_3                 ;	// 0x1078 : ''
	HDMI21_RX_AUD_O22_HMR0_PCPD_3_CLEAR     AUD_HMR0_PCPD_3_CLEAR			;	// 0x107C : ''
	HDMI21_RX_AUD_O22_HMR0_MUTE			    AUD_HMR0_MUTE 				    ;	// 0x1080 : ''
    UINT32                          	                 __rsvd_03[  31];	// 0x1084 ~ 0x10FC
	HDMI21_RX_AUD_O22_HMR1_CSD0_0			AUD_HMR1_CSD0_0 				;	// 0x1100 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD1_0			AUD_HMR1_CSD1_0 				;	// 0x1104 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD2_0			AUD_HMR1_CSD2_0 				;	// 0x1108 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD3_0			AUD_HMR1_CSD3_0 				;	// 0x110C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD4_0			AUD_HMR1_CSD4_0 				;	// 0x1110 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD5_0			AUD_HMR1_CSD5_0 				;	// 0x1114 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_0			AUD_HMR1_PCPD_0 				;	// 0x1118 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_0_CLEAR		AUD_HMR1_PCPD_0_CLEAR			;	// 0x111C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD0_1			AUD_HMR1_CSD0_1 				;	// 0x1120 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD1_1			AUD_HMR1_CSD1_1 				;	// 0x1124 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD2_1			AUD_HMR1_CSD2_1 				;	// 0x1128 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD3_1			AUD_HMR1_CSD3_1 				;	// 0x112C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD4_1			AUD_HMR1_CSD4_1 				;	// 0x1130 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD5_1			AUD_HMR1_CSD5_1 				;	// 0x1134 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_1			AUD_HMR1_PCPD_1 				;	// 0x1138 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_1_CLEAR		AUD_HMR1_PCPD_1_CLEAR			;	// 0x113C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD0_2			AUD_HMR1_CSD0_2 				;	// 0x1140 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD1_2			AUD_HMR1_CSD1_2 				;	// 0x1144 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD2_2			AUD_HMR1_CSD2_2 				;	// 0x1148 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD3_2			AUD_HMR1_CSD3_2 				;	// 0x114C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD4_2			AUD_HMR1_CSD4_2 				;	// 0x1150 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD5_2			AUD_HMR1_CSD5_2 				;	// 0x1154 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_2			AUD_HMR1_PCPD_2 				;	// 0x1158 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_2_CLEAR		AUD_HMR1_PCPD_2_CLEAR			;	// 0x115C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD0_3			AUD_HMR1_CSD0_3 				;	// 0x1160 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD1_3			AUD_HMR1_CSD1_3 				;	// 0x1164 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD2_3			AUD_HMR1_CSD2_3 				;	// 0x1168 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD3_3			AUD_HMR1_CSD3_3 				;	// 0x116C : ''
	HDMI21_RX_AUD_O22_HMR1_CSD4_3			AUD_HMR1_CSD4_3 				;	// 0x1170 : ''
	HDMI21_RX_AUD_O22_HMR1_CSD5_3			AUD_HMR1_CSD5_3 				;	// 0x1174 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_3			AUD_HMR1_PCPD_3 				;	// 0x1178 : ''
	HDMI21_RX_AUD_O22_HMR1_PCPD_3_CLEAR		AUD_HMR1_PCPD_3_CLEAR			;	// 0x117C : ''
	HDMI21_RX_AUD_O22_HMR1_MUTE 			AUD_HMR1_MUTE					;	// 0x1180 : ''
	UINT32												 __rsvd_04[  31];	// 0x1184 ~ 0x11FC
	HDMI21_RX_AUD_O22_HMR2_CSD0_0			AUD_HMR2_CSD0_0 				;	// 0x1200 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD1_0			AUD_HMR2_CSD1_0 				;	// 0x1204 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD2_0			AUD_HMR2_CSD2_0 				;	// 0x1208 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD3_0			AUD_HMR2_CSD3_0 				;	// 0x120C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD4_0			AUD_HMR2_CSD4_0 				;	// 0x1210 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD5_0			AUD_HMR2_CSD5_0 				;	// 0x1214 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_0			AUD_HMR2_PCPD_0 				;	// 0x1218 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_0_CLEAR		AUD_HMR2_PCPD_0_CLEAR			;	// 0x121C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD0_1			AUD_HMR2_CSD0_1 				;	// 0x1220 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD1_1			AUD_HMR2_CSD1_1 				;	// 0x1224 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD2_1			AUD_HMR2_CSD2_1 				;	// 0x1228 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD3_1			AUD_HMR2_CSD3_1 				;	// 0x122C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD4_1			AUD_HMR2_CSD4_1 				;	// 0x1230 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD5_1			AUD_HMR2_CSD5_1 				;	// 0x1234 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_1			AUD_HMR2_PCPD_1 				;	// 0x1238 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_1_CLEAR		AUD_HMR2_PCPD_1_CLEAR			;	// 0x123C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD0_2			AUD_HMR2_CSD0_2 				;	// 0x1240 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD1_2			AUD_HMR2_CSD1_2 				;	// 0x1244 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD2_2			AUD_HMR2_CSD2_2 				;	// 0x1248 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD3_2			AUD_HMR2_CSD3_2 				;	// 0x124C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD4_2			AUD_HMR2_CSD4_2 				;	// 0x1250 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD5_2			AUD_HMR2_CSD5_2 				;	// 0x1254 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_2			AUD_HMR2_PCPD_2 				;	// 0x1258 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_2_CLEAR		AUD_HMR2_PCPD_2_CLEAR			;	// 0x125C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD0_3			AUD_HMR2_CSD0_3 				;	// 0x1260 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD1_3			AUD_HMR2_CSD1_3 				;	// 0x1264 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD2_3			AUD_HMR2_CSD2_3 				;	// 0x1268 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD3_3			AUD_HMR2_CSD3_3 				;	// 0x126C : ''
	HDMI21_RX_AUD_O22_HMR2_CSD4_3			AUD_HMR2_CSD4_3 				;	// 0x1270 : ''
	HDMI21_RX_AUD_O22_HMR2_CSD5_3			AUD_HMR2_CSD5_3 				;	// 0x1274 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_3			AUD_HMR2_PCPD_3 				;	// 0x1278 : ''
	HDMI21_RX_AUD_O22_HMR2_PCPD_3_CLEAR		AUD_HMR2_PCPD_3_CLEAR			;	// 0x127C : ''
	HDMI21_RX_AUD_O22_HMR2_MUTE 			AUD_HMR2_MUTE					;	// 0x1280 : ''
	UINT32												 __rsvd_05[  31];	// 0x1284 ~ 0x12FC
	HDMI21_RX_AUD_O22_HMR3_CSD0_0			AUD_HMR3_CSD0_0 				;	// 0x1300 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD1_0			AUD_HMR3_CSD1_0 				;	// 0x1304 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD2_0			AUD_HMR3_CSD2_0 				;	// 0x1308 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD3_0			AUD_HMR3_CSD3_0 				;	// 0x130C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD4_0			AUD_HMR3_CSD4_0 				;	// 0x1310 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD5_0			AUD_HMR3_CSD5_0 				;	// 0x1314 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_0			AUD_HMR3_PCPD_0 				;	// 0x1318 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_0_CLEAR		AUD_HMR3_PCPD_0_CLEAR			;	// 0x131C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD0_1			AUD_HMR3_CSD0_1 				;	// 0x1320 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD1_1			AUD_HMR3_CSD1_1 				;	// 0x1324 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD2_1			AUD_HMR3_CSD2_1 				;	// 0x1328 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD3_1			AUD_HMR3_CSD3_1 				;	// 0x132C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD4_1			AUD_HMR3_CSD4_1 				;	// 0x1330 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD5_1			AUD_HMR3_CSD5_1 				;	// 0x1334 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_1			AUD_HMR3_PCPD_1 				;	// 0x1338 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_1_CLEAR		AUD_HMR3_PCPD_1_CLEAR			;	// 0x133C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD0_2			AUD_HMR3_CSD0_2 				;	// 0x1340 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD1_2			AUD_HMR3_CSD1_2 				;	// 0x1344 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD2_2			AUD_HMR3_CSD2_2 				;	// 0x1348 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD3_2			AUD_HMR3_CSD3_2 				;	// 0x134C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD4_2			AUD_HMR3_CSD4_2 				;	// 0x1350 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD5_2			AUD_HMR3_CSD5_2 				;	// 0x1354 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_2			AUD_HMR3_PCPD_2 				;	// 0x1358 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_2_CLEAR		AUD_HMR3_PCPD_2_CLEAR			;	// 0x135C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD0_3			AUD_HMR3_CSD0_3 				;	// 0x1360 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD1_3			AUD_HMR3_CSD1_3 				;	// 0x1364 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD2_3			AUD_HMR3_CSD2_3 				;	// 0x1368 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD3_3			AUD_HMR3_CSD3_3 				;	// 0x136C : ''
	HDMI21_RX_AUD_O22_HMR3_CSD4_3			AUD_HMR3_CSD4_3 				;	// 0x1370 : ''
	HDMI21_RX_AUD_O22_HMR3_CSD5_3			AUD_HMR3_CSD5_3 				;	// 0x1374 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_3			AUD_HMR3_PCPD_3 				;	// 0x1378 : ''
	HDMI21_RX_AUD_O22_HMR3_PCPD_3_CLEAR		AUD_HMR3_PCPD_3_CLEAR			;	// 0x137C : ''
	HDMI21_RX_AUD_O22_HMR3_MUTE 			AUD_HMR3_MUTE					;	// 0x1380 : ''
	UINT32												 __rsvd_06[  31];	// 0x1384 ~ 0x13FC
	HDMI21_RX_AUD_O22_HMR4_CSD0_0			AUD_HMR4_CSD0_0 				;	// 0x1400 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD1_0			AUD_HMR4_CSD1_0 				;	// 0x1404 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD2_0			AUD_HMR4_CSD2_0 				;	// 0x1408 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD3_0			AUD_HMR4_CSD3_0 				;	// 0x140C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD4_0			AUD_HMR4_CSD4_0 				;	// 0x1410 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD5_0			AUD_HMR4_CSD5_0 				;	// 0x1414 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_0			AUD_HMR4_PCPD_0 				;	// 0x1418 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_0_CLEAR		AUD_HMR4_PCPD_0_CLEAR			;	// 0x141C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD0_1			AUD_HMR4_CSD0_1 				;	// 0x1420 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD1_1			AUD_HMR4_CSD1_1 				;	// 0x1424 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD2_1			AUD_HMR4_CSD2_1 				;	// 0x1428 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD3_1			AUD_HMR4_CSD3_1 				;	// 0x142C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD4_1			AUD_HMR4_CSD4_1 				;	// 0x1430 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD5_1			AUD_HMR4_CSD5_1 				;	// 0x1434 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_1			AUD_HMR4_PCPD_1 				;	// 0x1438 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_1_CLEAR		AUD_HMR4_PCPD_1_CLEAR			;	// 0x143C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD0_2			AUD_HMR4_CSD0_2 				;	// 0x1440 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD1_2			AUD_HMR4_CSD1_2 				;	// 0x1444 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD2_2			AUD_HMR4_CSD2_2 				;	// 0x1448 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD3_2			AUD_HMR4_CSD3_2 				;	// 0x144C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD4_2			AUD_HMR4_CSD4_2 				;	// 0x1450 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD5_2			AUD_HMR4_CSD5_2 				;	// 0x1454 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_2			AUD_HMR4_PCPD_2 				;	// 0x1458 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_2_CLEAR		AUD_HMR4_PCPD_2_CLEAR			;	// 0x145C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD0_3			AUD_HMR4_CSD0_3 				;	// 0x1460 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD1_3			AUD_HMR4_CSD1_3 				;	// 0x1464 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD2_3			AUD_HMR4_CSD2_3 				;	// 0x1468 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD3_3			AUD_HMR4_CSD3_3 				;	// 0x146C : ''
	HDMI21_RX_AUD_O22_HMR4_CSD4_3			AUD_HMR4_CSD4_3 				;	// 0x1470 : ''
	HDMI21_RX_AUD_O22_HMR4_CSD5_3			AUD_HMR4_CSD5_3 				;	// 0x1474 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_3			AUD_HMR4_PCPD_3 				;	// 0x1478 : ''
	HDMI21_RX_AUD_O22_HMR4_PCPD_3_CLEAR		AUD_HMR4_PCPD_3_CLEAR			;	// 0x147C : ''
	HDMI21_RX_AUD_O22_HMR4_MUTE 			AUD_HMR4_MUTE					;	// 0x1480 : ''
	UINT32												 __rsvd_07[  31];	// 0x1484 ~ 0x14FC
} HDMI21_RX_AUD_REG_O22_T;
/* 261 regs, 261 types */

/*
 * @{
 * Naming for register pointer.
 * g_pRealHDMI21O22AudioReg : real register of AUD.
 * g_pTempHDMI21O22AudioReg     : shadow register.
 *
 * @def HDMI21O22Aud_RdFL: Read  FLushing : Shadow <- Real.
 * @def HDMI21O22Aud_WrFL: Write FLushing : Shadow -> Real.
 * @def HDMI21O22Aud_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def HDMI21O22Aud_Wr  : Write whole register(UINT32) from Shadow register.
 * @def HDMI21O22Aud_Rd01 ~ HDMI_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def HDMI21O22Aud_Wr01 ~ HDMI_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define HDMI21AudO22_RdREG(REG)			( *((volatile UINT32*)(REG)))
#define HDMI21AudO22_WrREG(REG,VAL)		( *((volatile UINT32*)(REG)) =(VAL))

#define HDMI21AudO22_RdFL(_r)			((g_pTempHDMI21AudioRegO22->_r)=(g_pRealHDMI21AudioRegO22->_r))
#define HDMI21AudO22_WrFL(_r)			((g_pRealHDMI21AudioRegO22->_r)=(g_pTempHDMI21AudioRegO22->_r))

#define HDMI21AudO22_Rd(_r)			*((UINT32*)(&(g_pTempHDMI21AudioRegO22->_r)))
#define HDMI21AudO22_Wr(_r,_v)			((HDMI21AudO22_Rd(_r))=((UINT32)(_v)))

#define HDMI21AudO22_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
								} while(0)

#define HDMI21AudO22_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
								} while(0)

#define HDMI21AudO22_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
								} while(0)

#define HDMI21AudO22_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
								} while(0)

#define HDMI21AudO22_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
								} while(0)

#define HDMI21AudO22_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
								} while(0)

#define HDMI21AudO22_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
								} while(0)

#define HDMI21AudO22_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
								} while(0)

#define HDMI21AudO22_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
								} while(0)

#define HDMI21AudO22_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
								} while(0)

#define HDMI21AudO22_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
									(_v11) = (g_pTempHDMI21AudioRegO22->_r._f11);				\
								} while(0)

#define HDMI21AudO22_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
									(_v11) = (g_pTempHDMI21AudioRegO22->_r._f11);				\
									(_v12) = (g_pTempHDMI21AudioRegO22->_r._f12);				\
								} while(0)

#define HDMI21AudO22_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
									(_v11) = (g_pTempHDMI21AudioRegO22->_r._f11);				\
									(_v12) = (g_pTempHDMI21AudioRegO22->_r._f12);				\
									(_v13) = (g_pTempHDMI21AudioRegO22->_r._f13);				\
								} while(0)

#define HDMI21AudO22_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
									(_v11) = (g_pTempHDMI21AudioRegO22->_r._f11);				\
									(_v12) = (g_pTempHDMI21AudioRegO22->_r._f12);				\
									(_v13) = (g_pTempHDMI21AudioRegO22->_r._f13);				\
									(_v14) = (g_pTempHDMI21AudioRegO22->_r._f14);				\
								} while(0)

#define HDMI21AudO22_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
									(_v11) = (g_pTempHDMI21AudioRegO22->_r._f11);				\
									(_v12) = (g_pTempHDMI21AudioRegO22->_r._f12);				\
									(_v13) = (g_pTempHDMI21AudioRegO22->_r._f13);				\
									(_v14) = (g_pTempHDMI21AudioRegO22->_r._f14);				\
									(_v15) = (g_pTempHDMI21AudioRegO22->_r._f15);				\
								} while(0)

#define HDMI21AudO22_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (g_pTempHDMI21AudioRegO22->_r._f01);				\
									(_v02) = (g_pTempHDMI21AudioRegO22->_r._f02);				\
									(_v03) = (g_pTempHDMI21AudioRegO22->_r._f03);				\
									(_v04) = (g_pTempHDMI21AudioRegO22->_r._f04);				\
									(_v05) = (g_pTempHDMI21AudioRegO22->_r._f05);				\
									(_v06) = (g_pTempHDMI21AudioRegO22->_r._f06);				\
									(_v07) = (g_pTempHDMI21AudioRegO22->_r._f07);				\
									(_v08) = (g_pTempHDMI21AudioRegO22->_r._f08);				\
									(_v09) = (g_pTempHDMI21AudioRegO22->_r._f09);				\
									(_v10) = (g_pTempHDMI21AudioRegO22->_r._f10);				\
									(_v11) = (g_pTempHDMI21AudioRegO22->_r._f11);				\
									(_v12) = (g_pTempHDMI21AudioRegO22->_r._f12);				\
									(_v13) = (g_pTempHDMI21AudioRegO22->_r._f13);				\
									(_v14) = (g_pTempHDMI21AudioRegO22->_r._f14);				\
									(_v15) = (g_pTempHDMI21AudioRegO22->_r._f15);				\
									(_v16) = (g_pTempHDMI21AudioRegO22->_r._f16);				\
								} while(0)


#define HDMI21AudO22_Wr01(_r,_f01,_v01)													\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
								} while(0)

#define HDMI21AudO22_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
								} while(0)

#define HDMI21AudO22_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
								} while(0)

#define HDMI21AudO22_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
								} while(0)

#define HDMI21AudO22_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
								} while(0)

#define HDMI21AudO22_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
								} while(0)

#define HDMI21AudO22_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
								} while(0)

#define HDMI21AudO22_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
								} while(0)

#define HDMI21AudO22_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
								} while(0)

#define HDMI21AudO22_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
								} while(0)

#define HDMI21AudO22_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
									(g_pTempHDMI21AudioRegO22->_r._f11) = (_v11);				\
								} while(0)

#define HDMI21AudO22_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
									(g_pTempHDMI21AudioRegO22->_r._f11) = (_v11);				\
									(g_pTempHDMI21AudioRegO22->_r._f12) = (_v12);				\
								} while(0)

#define HDMI21AudO22_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
									(g_pTempHDMI21AudioRegO22->_r._f11) = (_v11);				\
									(g_pTempHDMI21AudioRegO22->_r._f12) = (_v12);				\
									(g_pTempHDMI21AudioRegO22->_r._f13) = (_v13);				\
								} while(0)

#define HDMI21AudO22_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
									(g_pTempHDMI21AudioRegO22->_r._f11) = (_v11);				\
									(g_pTempHDMI21AudioRegO22->_r._f12) = (_v12);				\
									(g_pTempHDMI21AudioRegO22->_r._f13) = (_v13);				\
									(g_pTempHDMI21AudioRegO22->_r._f14) = (_v14);				\
								} while(0)

#define HDMI21AudO22_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
									(g_pTempHDMI21AudioRegO22->_r._f11) = (_v11);				\
									(g_pTempHDMI21AudioRegO22->_r._f12) = (_v12);				\
									(g_pTempHDMI21AudioRegO22->_r._f13) = (_v13);				\
									(g_pTempHDMI21AudioRegO22->_r._f14) = (_v14);				\
									(g_pTempHDMI21AudioRegO22->_r._f15) = (_v15);				\
								} while(0)

#define HDMI21AudO22_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(g_pTempHDMI21AudioRegO22->_r._f01) = (_v01);				\
									(g_pTempHDMI21AudioRegO22->_r._f02) = (_v02);				\
									(g_pTempHDMI21AudioRegO22->_r._f03) = (_v03);				\
									(g_pTempHDMI21AudioRegO22->_r._f04) = (_v04);				\
									(g_pTempHDMI21AudioRegO22->_r._f05) = (_v05);				\
									(g_pTempHDMI21AudioRegO22->_r._f06) = (_v06);				\
									(g_pTempHDMI21AudioRegO22->_r._f07) = (_v07);				\
									(g_pTempHDMI21AudioRegO22->_r._f08) = (_v08);				\
									(g_pTempHDMI21AudioRegO22->_r._f09) = (_v09);				\
									(g_pTempHDMI21AudioRegO22->_r._f10) = (_v10);				\
									(g_pTempHDMI21AudioRegO22->_r._f11) = (_v11);				\
									(g_pTempHDMI21AudioRegO22->_r._f12) = (_v12);				\
									(g_pTempHDMI21AudioRegO22->_r._f13) = (_v13);				\
									(g_pTempHDMI21AudioRegO22->_r._f14) = (_v14);				\
									(g_pTempHDMI21AudioRegO22->_r._f15) = (_v15);				\
									(g_pTempHDMI21AudioRegO22->_r._f16) = (_v16);				\
								} while(0)

/* Indexed Register Access.
 *
 * There is in-direct field specified by 'index' field within a register.
 * Normally a register has only one meaning for a 'field_name', but indexed register
 * can hold several data for a 'field_name' specifed by 'index' field of indexed register.
 * When writing an 3rd data for given 'field_name' register, you need to set 'rw' = 0, 'index' = 2,
 * and 'load' = 0.
 *
 * ASSUMPTION
 * For Writing indexed register load bit
 *
 * parameter list
 * _r     : name of register
 * _lname : name of load  bit field	: shall be 0 after macro executed.
 * _rwname: name of rw    bit field : shall be 0 after HDMI21AudO22_Wind(), 1 for HDMI21AudO22_Rind()
 * _iname : name of index bit field
 * _ival  : index value
 * _fname : field name
 * _fval  : field variable that field value shall be stored.
 *
 * HDMI21AudO22_Rind : General indexed register Read.
 * HDMI21AudO22_Wind : General indexed register Read.
 *
 * HDMI21AudO22_Ridx : For 'index', 'rw', 'load' field name
 * HDMI21AudO22_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define HDMI21AudO22_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
							do {												\
								HDMI21AudO22_Wr03(_r,_lname,0,_rwname,1,_iname,_ival);	\
								HDMI21AudO22_WrFL(_r);									\
								HDMI21AudO22_RdFL(_r);									\
								HDMI21AudO22_Rd01(_r,_fname,_fval);						\
							} while (0)

#define HDMI21AudO22_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
				HDMI21AudO22_Wr04(_r, _lname,0, _rwname,0, _iname,_ival, _fname,_fval)


#define HDMI21AudO22_Ridx(_r, _ival, _fname, _fval)	HDMI21AudO22_Rind(_r,load,rw,index,_ival,_fname,_fval)

#define HDMI21AudO22_Widx(_r, _ival, _fname, _fval)	HDMI21AudO22_Wind(_r,load,rw,index,_ival,_fname,_fval)

/** @} *//* end of macro documentation */

#ifdef __cplusplus
}
#endif

#endif	/* _AUD_REG_A0_H_ */

