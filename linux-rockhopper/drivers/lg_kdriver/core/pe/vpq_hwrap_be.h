/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/


/** @file vpq_hwrap_be.h
 *
 *  application interface header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_VPQ_HWRAP_BE_H_
#define	_VPQ_HWRAP_BE_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
#define V4L2_HWRAP_CSC_MUX_LUT_SIZE 4

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
#define PQDB_PHDR_SC_TH_DATA_LENGTH 7
#define PQDB_PHDR_SC_TH__80_DATA_LENGTH 12
#define PQDB_PHDR_RDF_DATA_LENGTH 5
#define PQDB_PHDR_RDF_LUMA_X_LUT_LENGTH 8
#define PQDB_PHDR_RDF_LUMA_Y_LUT_LENGTH 8

typedef enum
{
	v4l2_hwrap_led_ui_adj_off           = 0,
	v4l2_hwrap_led_ui_adj_sdr_low       = 1,
	v4l2_hwrap_led_ui_adj_sdr_medium    = 2,
	v4l2_hwrap_led_ui_adj_sdr_high      = 3,
	v4l2_hwrap_led_ui_adj_hdr_low       = 4,
	v4l2_hwrap_led_ui_adj_hdr_medium    = 5,
	v4l2_hwrap_led_ui_adj_hdr_high      = 6,
	v4l2_hwrap_led_ui_adj_hdr_pattern   = 7,
	v4l2_hwrap_led_ui_adj_max
}v4l2_hwrap_led_ui_adj_type;

typedef enum
{
	v4l2_hwrap_led_ui_adj_v2_off           = 0,
	v4l2_hwrap_led_ui_adj_v2_sdr_low       = 1,
	v4l2_hwrap_led_ui_adj_v2_sdr_medium    = 2,
	v4l2_hwrap_led_ui_adj_v2_sdr_high      = 3,
	v4l2_hwrap_led_ui_adj_v2_hdr_low       = 4,
	v4l2_hwrap_led_ui_adj_v2_hdr_medium    = 5,
	v4l2_hwrap_led_ui_adj_v2_hdr_high      = 6,
	v4l2_hwrap_led_ui_adj_v2_hdr_pattern   = 7,
	v4l2_hwrap_led_ui_adj_v2_rtings		   = 8,
	v4l2_hwrap_led_ui_adj_v2_max
}v4l2_hwrap_led_ui_adj_type_v2;

typedef enum
{
	v4l2_hwrap_led_ui_adj_v3_off           = 0,
	v4l2_hwrap_led_ui_adj_v3_sdr_low       = 1,
	v4l2_hwrap_led_ui_adj_v3_sdr_medium    = 2,
	v4l2_hwrap_led_ui_adj_v3_sdr_high      = 3,
	v4l2_hwrap_led_ui_adj_v3_hdr_low       = 4,
	v4l2_hwrap_led_ui_adj_v3_hdr_medium    = 5,
	v4l2_hwrap_led_ui_adj_v3_hdr_high      = 6,
	v4l2_hwrap_led_ui_adj_v3_hdr_pattern   = 7,
	v4l2_hwrap_led_ui_adj_v3_rtings		   = 8,
	v4l2_hwrap_led_ui_adj_v3_max
}v4l2_hwrap_led_ui_adj_type_v3;

typedef struct 
{
	unsigned int size;
	union {
		unsigned int *pData;
		unsigned int compat_pData;
		unsigned long long sizer;
	};
}v4l2_hwrap_led_db_info;

typedef struct 
{
	v4l2_hwrap_led_db_info  sbiHCoef;
	v4l2_hwrap_led_db_info  sbiVCoef;
	v4l2_hwrap_led_db_info  lres1TabCoef;
	v4l2_hwrap_led_db_info  lres5TabCoef;
}v4l2_hwrap_led_light_profile_info;

typedef struct 
{
	v4l2_hwrap_led_db_info  upperCurve[v4l2_hwrap_led_ui_adj_max];
	v4l2_hwrap_led_db_info  lowerCurve[v4l2_hwrap_led_ui_adj_max];
}v4l2_hwrap_led_dimming_curve_info;

typedef struct
{
	unsigned int lutVersion;
	v4l2_hwrap_led_db_info              pq_common;
	v4l2_hwrap_led_db_info              moduleAdj;
	v4l2_hwrap_led_db_info              unsharpMask;
	v4l2_hwrap_led_light_profile_info   lightProfile;
	v4l2_hwrap_led_dimming_curve_info   dimmingCurve;
	v4l2_hwrap_led_db_info              uiAdj_lut[v4l2_hwrap_led_ui_adj_max];
	v4l2_hwrap_led_db_info              pixelCompensation[v4l2_hwrap_led_ui_adj_max];
	v4l2_hwrap_led_db_info              smartBvGain;
}v4l2_hwrap_led_lut;

typedef struct
{
	v4l2_hwrap_led_db_info  upperCurve[v4l2_hwrap_led_ui_adj_v2_max];
	v4l2_hwrap_led_db_info  lowerCurve[v4l2_hwrap_led_ui_adj_v2_max];
}v4l2_hwrap_led_dimming_curve_info_v2;

typedef struct
{
	unsigned int lutVersion;
	v4l2_hwrap_led_db_info               pq_common;
	v4l2_hwrap_led_db_info               moduleAdj;
	v4l2_hwrap_led_db_info               unsharpMask;
	v4l2_hwrap_led_light_profile_info    lightProfile;
	v4l2_hwrap_led_dimming_curve_info_v2 dimmingCurve;
	v4l2_hwrap_led_db_info               uiAdj_lut[v4l2_hwrap_led_ui_adj_v2_max];
	v4l2_hwrap_led_db_info               pixelCompensation[v4l2_hwrap_led_ui_adj_v2_max];
	v4l2_hwrap_led_db_info               smartBvGain;
}v4l2_hwrap_led_lut_v2;

typedef struct
{
	v4l2_hwrap_led_db_info  upperCurve[v4l2_hwrap_led_ui_adj_v3_max];
	v4l2_hwrap_led_db_info  lowerCurve[v4l2_hwrap_led_ui_adj_v3_max];
}v4l2_hwrap_led_dimming_curve_info_v3;

typedef struct
{
	unsigned int lutVersion;
	v4l2_hwrap_led_db_info               pq_common;
	v4l2_hwrap_led_db_info               moduleAdj;
	v4l2_hwrap_led_db_info               unsharpMask;
	v4l2_hwrap_led_light_profile_info    lightProfile;
	v4l2_hwrap_led_dimming_curve_info_v2 dimmingCurve;
	v4l2_hwrap_led_db_info               uiAdj_lut[v4l2_hwrap_led_ui_adj_v3_max];
	v4l2_hwrap_led_db_info               pixelCompensation[v4l2_hwrap_led_ui_adj_v3_max];
	v4l2_hwrap_led_db_info               smartBvGain;
}v4l2_hwrap_led_lut_v3;

typedef struct 
{
	unsigned int mux_l3d_in;
	unsigned int mux_blend_in;
	unsigned int mux_4p_lut_in;
	unsigned int mux_oetf_out;
	unsigned int b4p_lut_x[V4L2_HWRAP_CSC_MUX_LUT_SIZE];
	unsigned int b4p_lut_y[V4L2_HWRAP_CSC_MUX_LUT_SIZE];
}v4l2_hwrap_csc_mux_lut;

typedef struct
{      
	unsigned char bGamma;      
	unsigned char bDeGamma;      
	short matrix[9];
	v4l2_hwrap_csc_mux_lut mux_blend;
}v4l2_hwrap_gamut_post;

typedef struct
{
	unsigned char  lllut_en;
	unsigned char  lllut_csc_en;
	unsigned short lllut_r[128];
	unsigned short lllut_g[128];
	unsigned short lllut_b[128];
	short          matrix[9];
	unsigned char  blend_in_sel;
	short          r2y_matrix[3];
	unsigned short blend_lut_x[6];
	unsigned short blend_lut_y[6];
	unsigned char  hue_gain;
	unsigned char  sat_gain;
}v4l2_hwrap_pcc_lllut;

typedef struct
{
	unsigned char bGamma;
	unsigned char bDeGamma;
	short matrix[9];
	v4l2_hwrap_csc_mux_lut mux_blend;
	union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
}v4l2_hwrap_gamut_post_v2;

typedef struct 
{
	unsigned int u_Sat_gain;
	unsigned int uHue_comp_gain;
	unsigned int uSta_comp_gain;
	unsigned int uLumaGainLUT_x[4];
	unsigned int uLumaGainLUT_y[4];
	unsigned int uSatGainLUT_x[5];
	unsigned int uSatGainLUT_y[5];
}v4l2_hwrap_csc_post_pcc_lut;

typedef struct {

   short fMatrix[4][9];
   unsigned char y_adaptive_en;
   unsigned int luma_th0;
   unsigned int luma_th1;
   unsigned int luma_th2;
   unsigned int luma_th3;
}v4l2_hwrap_csc_luma_pcc_lut;


typedef struct
{
	unsigned char bGamma;
	unsigned char bDeGamma;
	short matrix[9];
	v4l2_hwrap_csc_mux_lut mux_blend;
	v4l2_hwrap_csc_post_pcc_lut post_pcc_lut;
	v4l2_hwrap_csc_luma_pcc_lut luma_pcc_lut;
	union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
}v4l2_hwrap_gamut_post_v3;

typedef struct 
{
	unsigned short block_apl_min;
	unsigned short block_apl_max;
}v4l2_hwrap_led_apl_info;

typedef struct
{
	 unsigned short phdr_boost[9];
	 unsigned short phdr_apl_force[3];
	 unsigned short phdr_sat[5];
	 unsigned short phdr_sat_gain_lut_x[8];
	 unsigned short phdr_sat_gain_lut_y[8];
	 unsigned short phdr_global_gain_lut_x[32];
	 unsigned short phdr_global_gain_lut_y[32];
	 unsigned short phdr_osd_alpha_lut_x[8];
	 unsigned short phdr_osd_alpha_lut_y[8];
	 unsigned short phdr_lsr_gain_lut_x[8];
	 unsigned short phdr_lsr_gain_lut_y[8];
	 unsigned short oapl_ctrl[8];
}v4l2_hwrap_post_hdr_lut;

typedef struct
{
	 unsigned short phdr_boost[9];
	 unsigned short phdr_apl_force[3];
	 unsigned short phdr_sat[5];
	 unsigned short phdr_sat_gain_lut_x[8];
	 unsigned short phdr_sat_gain_lut_y[8];
	 unsigned short phdr_global_gain_lut_x[32];
	 unsigned short phdr_global_gain_lut_y[32];
	 unsigned short phdr_osd_alpha_lut_x[8];
	 unsigned short phdr_osd_alpha_lut_y[8];
	 unsigned short phdr_lsr_gain_lut_x[8];
	 unsigned short phdr_lsr_gain_lut_y[8];
	 unsigned short oapl_ctrl[8];

	 unsigned char phdr_color_histogram_lut_x[8];
	 unsigned char phdr_color_histogram_lut_y[8];
	 unsigned short phdr_sat_gain_lut_y2[8];
}v4l2_hwrap_post_hdr_lut_50;

typedef struct
{
	 unsigned short phdr_boost[9];
	 unsigned short phdr_apl_force[3];
	 unsigned short phdr_sat[5];
	 unsigned short phdr_sat_gain_lut_x[8];
	 unsigned short phdr_sat_gain_lut_y[8];
	 unsigned short phdr_global_gain_lut_x[32];
	 unsigned short phdr_global_gain_lut_y[32];
	 unsigned short phdr_osd_alpha_lut_x[8];
	 unsigned short phdr_osd_alpha_lut_y[8];
	 unsigned short phdr_lsr_gain_lut_x[8];
	 unsigned short phdr_lsr_gain_lut_y[8];
	 unsigned short oapl_ctrl[8];

	 unsigned char phdr_color_histogram_lut_x[8];
	 unsigned char phdr_color_histogram_lut_y[8];
	 unsigned short phdr_sat_gain_lut_y2[8];

	 unsigned short phdr_sc_th_data[PQDB_PHDR_SC_TH_DATA_LENGTH];
	 unsigned short phdr_rdf_data[PQDB_PHDR_RDF_DATA_LENGTH];
	 unsigned short phdr_rdf_luma_x_data[PQDB_PHDR_RDF_LUMA_X_LUT_LENGTH];
	 unsigned short phdr_rdf_luma_y_data[PQDB_PHDR_RDF_LUMA_Y_LUT_LENGTH];
}v4l2_hwrap_post_hdr_lut_60;


typedef struct
{
	 unsigned short phdr_boost[9];
	 unsigned short phdr_apl_force[3];
	 unsigned short phdr_sat[5];
	 unsigned short phdr_sat_gain_lut_x[8];
	 unsigned short phdr_sat_gain_lut_y[8];
	 unsigned short phdr_global_gain_lut_x[32];
	 unsigned short phdr_global_gain_lut_y[32];
	 unsigned short phdr_osd_alpha_lut_x[8];
	 unsigned short phdr_osd_alpha_lut_y[8];
	 unsigned short phdr_lsr_gain_lut_x[8];
	 unsigned short phdr_lsr_gain_lut_y[8];
	 unsigned short oapl_ctrl[8];

	 unsigned char phdr_color_histogram_lut_x[8];
	 unsigned char phdr_color_histogram_lut_y[8];
	 unsigned short phdr_sat_gain_lut_y2[8];

	 unsigned short phdr_sc_th_data[PQDB_PHDR_SC_TH__80_DATA_LENGTH];
	 unsigned short phdr_rdf_data[PQDB_PHDR_RDF_DATA_LENGTH];
	 unsigned short phdr_rdf_luma_x_data[PQDB_PHDR_RDF_LUMA_X_LUT_LENGTH];
	 unsigned short phdr_rdf_luma_y_data[PQDB_PHDR_RDF_LUMA_Y_LUT_LENGTH];
}v4l2_hwrap_post_hdr_lut_80;

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/
extern int vpq_hwrap_memc_setmotioncomp(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_memc_lowdelaymode(unsigned int *p_param);
extern int vpq_hwrap_memc_motionpro(unsigned int *p_param);
extern int vpq_hwrap_gamut_matrix_post(struct v4l2_ext_vpq_cmn_data *param, UINT16 *p_PccMatrix);

#endif /* _VPQ_HWRAP_BE_H_ */
