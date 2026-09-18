/****************** COPYRIGHT AND CONFIDENTIALITY INFORMATION ******************
  Copyright (C) 2014-2018  Technicolor Technology Licensing LLC and/or
                           its Group Company
  All rights reserved.

  This program contains proprietary information which is a trade secret of
  Technicolor and also is protected by intellectual property as an unpublished
  work under applicable Copyright laws/right of authorship.
  This program is also subject to some patent and pending patent applications.
  Technicolor (R) is registered trademark and trade name of Technicolor group
  company, and shall not be used in any manner without express written from
  Technicolor.
  The use of the program and documentation is strictly limited to your own
  internal evaluation of such program and its functionalities, unless expressly
  agreed otherwise by Technicolor under a specific agreement.
  Recipient is to retain this program in confidence and is not permitted to use
  or make copies thereof other than as permitted in a written agreement with
  Technicolor, unless otherwise expressly allowed by applicable laws.
  Recipient is not allowed to make any copy, decompile, reverse engineer,
  disassemble, and attempt to derive the source code of, modify, or create
  derivative works of the program, any update, or any part thereof.
  Any violation or attempt to do so is a violation of the rights of Technicolor.
  If you or any person under your control or authority breach this restriction,
  you may be subject to prosecution and damages.
*******************************************************************************/

/**
 * @file SL_common.h
 *
 * @section DESCRIPTION
 * Definition of some common Macros and constants<br>
*/

#ifndef SL_COMMON_H
#define SL_COMMON_H

#define PE_PRIME_V142

#ifdef PE_PRIME_V142
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"
#include "pe_def.h"
//#define printf(format ,args...)		printk(format ,##args)

/************/
/* stdint.h */
/************/
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#define INT8_MAX    0x7f
#define INT16_MAX   0x7fff
//#define INT32_MAX   0x7fffffff
#define INT64_MAX   0x7fffffffffffffff
#define INT8_MIN    (-0x7f - 1)
#define INT16_MIN   (-0x7fff - 1)
//#define INT32_MIN   (-0x7fffffff - 1)
#define INT64_MIN   (-0x7fffffffffffffff - 1)
#define UINT8_MAX 0xff /* 255U */
#define UINT16_MAX 0xffff /* 65535U */
#define UINT32_MAX 0xffffffff  /* 4294967295U */
#define UINT64_MAX 0xffffffffffffffffULL /* 18446744073709551615ULL */
/************/

#else
#include <stdint.h>
#endif

#ifndef INT32_MIN
#define INT32_MIN (-2147483647-1)
#endif

#ifndef INT32_MAX
#define INT32_MAX (2147483647)
#endif

#define Min(a, b)   ( ((a) < (b)) ? (a) : (b) )
#define Max(a, b)   ( ((a) < (b)) ? (b) : (a) )
#define CLAMP(v, a, b)  ((v < a)? a: ((v > b)? b: v))

#define YUV_FULL_RANGE    1
#define YUV_LIMITED_RANGE 0

#define BT1886 0
#define PQ     1
#define LINEAR 2

struct sl_hdr_metadata_variables {
  int tmInputSignalBlackLevelOffset;
  int tmInputSignalWhiteLevelOffset;
  int shadowGain;
  int highlightGain;
  int midToneWidthAdjFactor;
  int tmOutputFineTuningNumVal;
  int tmOutputFineTuningX[10];
  int tmOutputFineTuningY[10];
  int saturationGainNumVal;
  int saturationGainX[6];
  int saturationGainY[6];
};

struct sl_hdr_metadata_tables {
  int luminanceMappingNumVal;
  int luminanceMappingX[65];
  int luminanceMappingY[65];
  int colourCorrectionNumVal;
  int colourCorrectionX[65];
  int colourCorrectionY[65];
};

struct sl_hdr_metadata {
  int partID;
  int majorSpecVersionID;
  int minorSpecVersionID;
  int payloadMode;
  int hdrPicColourSpace;
  int hdrDisplayColourSpace;
  int hdrDisplayMaxLuminance;
  int hdrDisplayMinLuminance;
  int sdrPicColourSpace;
  int sdrDisplayColourSpace;
  int sdrDisplayMaxLuminance;
  int sdrDisplayMinLuminance;
  int matrixCoefficient[4];
  int chromaToLumaInjection[2];
  int kCoefficient[3];
  union
  {
    struct sl_hdr_metadata_variables variables;
    struct sl_hdr_metadata_tables tables;
  } u;
};

/********************/
/* vdec_kadp_defs.h */
/********************/
struct hdr_vui
{
  unsigned char transfer_characteristics;
  unsigned char color_primaries;
  unsigned char matrix_coeffs;
  int video_full_range_flag;
};

struct hdr_sei
{
  unsigned short disp_prim_x[3];
  unsigned short disp_prim_y[3];
  unsigned short white_point_x;
  unsigned short white_point_y;
  unsigned int max_disp_mastering_luminance;
  unsigned int min_disp_mastering_luminance;
  unsigned short max_content_light_level;
  unsigned short max_pic_average_light_level;
  unsigned char hdr_transfer_characteristic_idc;
};

struct hdr_cri
{
  unsigned int    colour_remap_id;
  unsigned char   colour_remap_cancel_flag;
  unsigned char   colour_remap_persistence_flag;
  unsigned char   colour_remap_video_signal_info_present_flag;
  unsigned char   colour_remap_full_range_flag;
  unsigned char   colour_remap_primaries;
  unsigned char   colour_remap_transfer_function;
  unsigned char   colour_remap_matrix_coefficients;
  unsigned char   colour_remap_input_bit_depth;
  unsigned char   colour_remap_bit_depth;
  unsigned char   pre_lut_num_val_minus1[3];
  unsigned short  pre_lut_coded_value[3][33];
  unsigned short  pre_lut_target_value[3][33];
  unsigned char   colour_remap_matrix_present_flag;
  unsigned char   log2_matrix_denom;
  unsigned int    colour_remap_coeffs[3][3];
  unsigned char   post_lut_num_val_minus1[3];
  unsigned short  post_lut_coded_value[3][33];
  unsigned short  post_lut_target_value[3][33];
};

struct hdr_tsi
{
  unsigned int itu_t_t35_country_code;
  unsigned short terminal_provider_code;
  unsigned char terminal_provider_oriented_code_message_idc;
  unsigned char ts_103_433_spec_version;
  unsigned char ts_103_433_payload_mode;
};

struct hdr_cvri
{
  unsigned int itu_t_t35_country_code;
  unsigned short terminal_provider_code;
  unsigned char terminal_provider_oriented_code_message_idc;
  unsigned int cv_rec_id;
  unsigned char cv_rec_cancel_flag;
  unsigned char cv_rec_persistence_flag;
  unsigned int cv_rec_repetition_period;
  unsigned char cv_rec_target_info_flag;
  unsigned char cv_rec_primaries;
  unsigned char cv_rec_matrix_coefficients;
  unsigned char tone_mapping_input_signal_black_level_offset;
  unsigned char tone_mapping_input_signal_white_level_offset;
  unsigned char shadow_gain_control;
  unsigned char highlight_gain_control;
  unsigned char mid_tone_width_adjustment_factor;
  unsigned char tone_mapping_output_fine_tuning_num_val;
  unsigned char tone_mapping_output_fine_tuning_x[10];
  unsigned char tone_mapping_output_fine_tuning_y[10];
  unsigned char saturation_gain_num_val;
  unsigned char saturation_gain_x[6];
  unsigned char saturation_gain_y[6];
};

struct gamut_mapping_params
{
  unsigned char sat_mapping_mode;

  // sat_mapping_mode == 1 only
  unsigned char sat_global_1seg_ratio;
  unsigned char sat_global_2seg_ratio_wcg;
  unsigned char sat_global_2seg_ratio_scg;
  // sat_mapping_mode == 2 only
  unsigned char sat_1seg_ratio[6];
  unsigned char sat_2seg_ratio_wcg[6];
  unsigned char sat_2seg_ratio_scg[6];

  unsigned char lightness_mapping_mode;
  unsigned char lm_weight_factor[6];
  unsigned char cropping_mode_scg;
  unsigned char cm_weight_factor[6];
  unsigned char cm_cropped_lm_enabled_flag;
  unsigned char hue_adjustment_mode;
  unsigned char hue_global_preservation_ratio;
  unsigned char hue_preservation_ratio[6];
  unsigned char hue_adjustment_correction_info_present_flag;
  unsigned char hue_alignment_correction[6];
  unsigned char chrom_adjustment_info_present_flag;
  unsigned char chrom_adjustment_param[6];
};

struct hdr_sl_hdr
{
  unsigned int itu_t_t35_country_code;
  unsigned short terminal_provider_code;
  unsigned char terminal_provider_oriented_code_message_idc;
  unsigned char sl_hdr_mode_value_minus1;
  unsigned char sl_hdr_spec_major_version_idc;
  unsigned char sl_hdr_spec_minor_version_idc;
  unsigned char sl_hdr_cancel_flag;
  unsigned char sl_hdr_persistence_flag;
  unsigned char coded_picture_info_present_flag;
  unsigned char target_picture_info_present_flag;
  unsigned char src_mdcv_info_present_flag;
  unsigned char sl_hdr_extension_present_flag;
  unsigned char sl_hdr_payload_mode;
  unsigned char coded_picture_primaries;
  unsigned short coded_picture_max_luminance;
  unsigned short coded_picture_min_luminance;
  unsigned char target_picture_primaries;
  unsigned short target_picture_max_luminance;
  unsigned short target_picture_min_luminance;
  unsigned short src_mdcv_primaries_x[3];
  unsigned short src_mdcv_primaries_y[3];
  unsigned short src_mdcv_ref_white_x;
  unsigned short src_mdcv_ref_white_y;
  unsigned short src_mdcv_max_mastering_luminance;
  unsigned short src_mdcv_min_mastering_luminance;
  unsigned short matrix_coefficient_value[4];
  unsigned short chroma_to_luma_injection[2];
  unsigned char k_coefficient_value[3];

  // sl_hdr_payload_mode == 0
  unsigned char tone_mapping_input_signal_black_level_offset;
  unsigned char tone_mapping_input_signal_white_level_offset;
  unsigned char shadow_gain_control;
  unsigned char highlight_gain_control;
  unsigned char mid_tone_width_adjustment_factor;
  unsigned char tone_mapping_output_fine_tuning_num_val;
  unsigned char saturation_gain_num_val;
  unsigned char tone_mapping_output_fine_tuning_x[16];
  unsigned char tone_mapping_output_fine_tuning_y[16];
  unsigned char saturation_gain_x[16];
  unsigned char saturation_gain_y[16];
  // sl_hdr_payload_mode == 1
  unsigned char lm_uniform_sampling_flag;
  unsigned char luminance_mapping_num_val;
  unsigned short luminance_mapping_x[128];
  unsigned short luminance_mapping_y[128];
  unsigned char cc_uniform_sampling_flag;
  unsigned char colour_correction_num_val;
  unsigned short colour_correction_x[128];
  unsigned short colour_correction_y[128];

  unsigned char gamut_mapping_mode;
  struct gamut_mapping_params gamut_mapping_params;
  unsigned char sl_hdr_extension_6bits;
  unsigned short sl_hdr_extension_length;
  unsigned char sl_hdr_extension_data_byte[1024];
};

struct hdr_data
{
  struct hdr_vui *vui;
  struct hdr_sei *sei;
  struct hdr_tsi *tsi;
  struct hdr_cri *cri;
  struct hdr_cvri *cvri;
  struct hdr_sl_hdr *sl_hdr;
  unsigned int timestamp;
};
/********************/

typedef struct {
    int mu0;
	int mu1;
    int OCT[7];
    unsigned short C_LUT[65];
    unsigned short P_LUT[65];
    unsigned short S_LUT[65];
    unsigned short I_LUT[65];
    unsigned short D_LUT[65];
    unsigned short D_LUT_THRESHOLD[3];
    unsigned short D_LUT_STEP[4];
}
SL_HDR_PRIME_LUT_T;

//#define SL_HDR_SHARED_MEM "/shmem-pe_kwrap_hdr10"
#define SL_HDR_SHM_SIZE	10

/**
* shared mem data
* [0] : dbg print level
* [1] : display_Brightness
* [3] : display_OETF
* [4] : rsvd(not defined)
* [5] : rsvd(not defined)
* [6] : rsvd(not defined)
* [7] : rsvd(not defined)
* [8] : rsvd(not defined)
* [9] : rsvd(not defined)
*/
typedef struct {
	int data[SL_HDR_SHM_SIZE];
}
SL_HDR_SHM_MAP_T;

#endif // SL_COMMON_H
