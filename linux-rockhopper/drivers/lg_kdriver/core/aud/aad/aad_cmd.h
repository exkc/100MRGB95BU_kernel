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
 *  Audio AAD(Analog Audio Decoder) Command register details. ( used only within kdriver )
 *
 *  @author		JongSang Oh (jongsang.oh@lge.com)
 *  version		1.1
 *  @date		2016.04.04
 */

#ifndef _AUDIO_AAD_CMD_H_
#define _AUDIO_AAD_CMD_H_

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
	0x0560 aud_aad_agc1 ''
------------------------------------------------------------------------------*/
struct AUD_AAD_AGC1 {
	UINT32
	agc_feedback                    : 5,	//  0: 4
	                                : 3,	//  5: 7 reserved
	manual_gain                     : 8,	//  8:15
	auto_freeze                     : 1,	//    16
	                                : 7,	// 17:23 reserved
	agc_enable                      : 1;	//    24
};

/*-----------------------------------------------------------------------------
	0x0564 aud_aad_agc2 ''
------------------------------------------------------------------------------*/
struct AUD_AAD_AGC2 {
	UINT32
	peak_sif                        :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	target_mag                      : 9;	// 16:24
};

/*-----------------------------------------------------------------------------
	0x0570 aud_aad_band_info ''
------------------------------------------------------------------------------*/
struct AUD_AAD_BAND_INFO {
	UINT32
	stereo_search_result            : 4;	//  0: 3
};

/*-----------------------------------------------------------------------------
	0x0574 aud_aad_sys_info ''
------------------------------------------------------------------------------*/
struct AUD_AAD_SYS_INFO {
	UINT32
	sif_system                      : 4;	//  0: 3
};

/*-----------------------------------------------------------------------------
	0x0578 aud_aad_status ''
------------------------------------------------------------------------------*/
struct AUD_AAD_STATUS {
	UINT32
	car1_good                       : 1,	//     0
	car2_good                       : 1,	//     1
	sound_status                    : 1,	//     2
	sound_car                       : 1,	//     3
	stereo                          : 1,	//     4
	nicam                           : 1,	//     5
	bisap                           : 1,	//     6
	band_detect_enable              : 1;	//     7
};

/*-----------------------------------------------------------------------------
	0x0594 aud_aad_c1_mag_cnr ''
------------------------------------------------------------------------------*/
struct AUD_AAD_C1_MAG_CNR {
	UINT32
	car1_cnr                        :16,	//  0:15
	car1_mag                        :16;	// 16:31
};

/*-----------------------------------------------------------------------------
	0x059c aud_aad_c1_noise_am_noise ''
------------------------------------------------------------------------------*/
struct AUD_AAD_C1_NOISE_AM_NOISE {
	UINT32
	car1_am_noise                   :16,	//  0:15
	car1_noise                      :16;	// 16:31
};

/*-----------------------------------------------------------------------------
	0x05a4 aud_aad_c2_mag_cnr ''
------------------------------------------------------------------------------*/
struct AUD_AAD_C2_MAG_CNR {
	UINT32
	car2_cnr                        :16,	//  0:15
	car2_mag                        :16;	// 16:31
};

/*-----------------------------------------------------------------------------
	0x05ac aud_aad_c2_noise_dqpsk_noise ''
------------------------------------------------------------------------------*/
struct AUD_AAD_C2_NOISE_DQPSK_NOISE {
	UINT32
	dqpsk_noise                     :16,	//  0:15
	car2_noise                      :16;	// 16:31
};

/*-----------------------------------------------------------------------------
	0x05b0 aud_aad_sap_mag_noise ''
------------------------------------------------------------------------------*/
struct AUD_AAD_SAP_MAG_NOISE {
	UINT32
	sap_noise                       :16,	//  0:15
	sap_mag                         :16;	// 16:31
};

/*-----------------------------------------------------------------------------
	0x05b4 aud_aad_nicam_info ''
------------------------------------------------------------------------------*/
struct AUD_AAD_NICAM_INFO {
	UINT32
	frame_flag                      : 1,	//     0
	nicam_mode                      : 2,	//  1: 2
	                                : 1,	//     3 reserved
	ad_same                         : 1,	//     4
	frame_sync_lock                 : 1,	//     5
	sync_searchng                   : 1,	//     6
	                                : 9,	//  7:15 reserved
	nicam_error_rate                :16;	// 16:31
};

/*-----------------------------------------------------------------------------
	0x05b8 aud_aad_pll_info ''
------------------------------------------------------------------------------*/
struct AUD_AAD_PLL_INFO {
	UINT32
	pilot_mag                       : 8,	//  0: 7
	id_bi_mag                       : 8,	//  8:15
	id_st_mag                       : 8;	// 16:23
};

/*-----------------------------------------------------------------------------
	0x05bc aud_aad_out_cont ''
------------------------------------------------------------------------------*/
struct AUD_AAD_OUT_CONT {
	UINT32
	a2_output_result                : 4,	//  0: 3
	btsc_output_result              : 4,	//  4: 7
	nicam_output_result             : 4;	//  8:11
};

/* 18 regs, 13 types in Total*/

#ifdef __cplusplus
}
#endif

#endif	/* _AUDIO_AAD_CMD_H_ */

/* from 'D:/77_UTC/REGISTER/M17/20160205_M17_AUD_reg_man-v0.6/20160205_M17_AUD_reg_man-v0.6_ARM.csv'
    대한민국 표준시 by getregs v2.7 */
