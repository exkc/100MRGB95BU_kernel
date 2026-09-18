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
 * @file SL_compute.c
 *
 * @section DESCRIPTION
 * Compute C_LUT, P_LUT, Range, mu0 / mu1 and OCT<br>
*/

#include "SL_compute.h"
#include "SL_LUT_fill.h"

static int ShadowGain[201] = {
    255,   255,   255,   253,   227,   208,   194,   182,
    172,   164,   157,   151,   145,   140,   136,   131,
    128,   124,   121,   118,   115,   112,   110,   107,
    105,   103,   101,    99,    97,    95,    94,    92,
     91,    89,    88,    86,    85,    84,    82,    81,
     80,    79,    78,    77,    76,    75,    74,    73,
     72,    71,    70,    69,    68,    67,    67,    66,
     65,    64,    64,    63,    62,    61,    61,    60,
     59,    59,    58,    58,    57,    56,    56,    55,
     55,    54,    54,    53,    53,    52,    52,    51,
     51,    50,    50,    49,    49,    48,    48,    47,
     47,    46,    46,    46,    45,    45,    44,    44,
     44,    43,    43,    42,    42,    42,    41,    41,
     41,    40,    40,    40,    39,    39,    39,    38,
     38,    38,    37,    37,    37,    36,    36,    36,
     36,    35,    35,    35,    34,    34,    34,    34,
     33,    33,    33,    32,    32,    32,    32,    31,
     31,    31,    31,    30,    30,    30,    30,    29,
     29,    29,    29,    29,    28,    28,    28,    28,
     27,    27,    27,    27,    27,    26,    26,    26,
     26,    25,    25,    25,    25,    25,    24,    24,
     24,    24,    24,    23,    23,    23,    23,    23,
     23,    22,    22,    22,    22,    22,    21,    21,
     21,    21,    21,    21,    20,    20,    20,    20,
     20,    20,    19,    19,    19,    19,    19,    19,
     18,
};

/**
 * @brief Fill metadata with recovery mode values
 *
 * @param sl_hdr_metadata[in] : current metadata
 * @param TargetDisplayLuminance[in] : display brightness
 * @param colour_primaries[in] : ITU-R BT.709 or ITU-R BT.2020
 * @param transfer_characteristics[in] : ITU-R BT.709 or SMPTE ST-2084
 *
 * @return void
*/
void Fill_MetadataRecovery(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int colour_primaries, int transfer_characteristics)
{
  unsigned char Lhdr_idx = TargetDisplayLuminance / 50;
  int shadow_gain = (TargetDisplayLuminance == 100) ? 115 : ShadowGain[Lhdr_idx];

  if (transfer_characteristics == 16) {
    sl_hdr_metadata->partID = 2;
    sl_hdr_metadata->chromaToLumaInjection[1] = 0;
    sl_hdr_metadata->u.variables.saturationGainNumVal = 0;
  }
  else {
    sl_hdr_metadata->partID = 1;
    sl_hdr_metadata->chromaToLumaInjection[1] = (colour_primaries == 1) ? 0 : 1638;
    sl_hdr_metadata->u.variables.saturationGainNumVal = 1;
    sl_hdr_metadata->u.variables.saturationGainX[0] = 0;
    sl_hdr_metadata->u.variables.saturationGainY[0] = (colour_primaries == 1) ? 115 : 118;
  }

  sl_hdr_metadata->payloadMode = 0;

  if (colour_primaries == 1) {
    sl_hdr_metadata->hdrPicColourSpace = 0;
    sl_hdr_metadata->hdrDisplayColourSpace = 0;
    sl_hdr_metadata->matrixCoefficient[0] = 915;
    sl_hdr_metadata->matrixCoefficient[1] = 464;
    sl_hdr_metadata->matrixCoefficient[2] = 392;
    sl_hdr_metadata->matrixCoefficient[3] = 987;
  }
  else {
    sl_hdr_metadata->hdrPicColourSpace = 1;
    sl_hdr_metadata->hdrDisplayColourSpace = 2;
    sl_hdr_metadata->matrixCoefficient[0] = 889;
    sl_hdr_metadata->matrixCoefficient[1] = 470;
    sl_hdr_metadata->matrixCoefficient[2] = 366;
    sl_hdr_metadata->matrixCoefficient[3] = 994;
  }

  sl_hdr_metadata->hdrDisplayMaxLuminance = (TargetDisplayLuminance == 100) ? 1000 : TargetDisplayLuminance;
  sl_hdr_metadata->hdrDisplayMinLuminance = 0;
  sl_hdr_metadata->sdrPicColourSpace = sl_hdr_metadata->hdrPicColourSpace;
  sl_hdr_metadata->sdrDisplayColourSpace = sl_hdr_metadata->hdrDisplayColourSpace;
  sl_hdr_metadata->sdrDisplayMaxLuminance = 100;
  sl_hdr_metadata->sdrDisplayMinLuminance = 0;
  sl_hdr_metadata->kCoefficient[0] = 0;
  sl_hdr_metadata->kCoefficient[1] = 0;
  sl_hdr_metadata->kCoefficient[2] = 0;
  sl_hdr_metadata->chromaToLumaInjection[0] = 0;
  sl_hdr_metadata->u.variables.tmInputSignalBlackLevelOffset = 0;
  sl_hdr_metadata->u.variables.tmInputSignalWhiteLevelOffset = 0;
  sl_hdr_metadata->u.variables.shadowGain = shadow_gain;
  sl_hdr_metadata->u.variables.highlightGain = 255;
  sl_hdr_metadata->u.variables.midToneWidthAdjFactor = 64;
  sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal = 0;
}

static void Compute_Mu_OCT(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, unsigned short *mu0, unsigned short *mu1, int *OCT)
{
  int i;

  if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance) {
    if (sl_hdr_metadata->partID == 1) {
      *mu0 = (sl_hdr_metadata->chromaToLumaInjection[0] * (TargetDisplayLuminance - 100) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
      *mu1 = (sl_hdr_metadata->chromaToLumaInjection[1] * (TargetDisplayLuminance - 100) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
    }
    else {
      *mu0 = sl_hdr_metadata->chromaToLumaInjection[0] * (sl_hdr_metadata->hdrDisplayMaxLuminance - TargetDisplayLuminance) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
      *mu1 = sl_hdr_metadata->chromaToLumaInjection[1] * (sl_hdr_metadata->hdrDisplayMaxLuminance - TargetDisplayLuminance) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
    }
  }
  else {
    *mu0 = sl_hdr_metadata->chromaToLumaInjection[0];
    *mu1 = sl_hdr_metadata->chromaToLumaInjection[1];
  }

  for (i = 0; i < 3; i++) {
    if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance && sl_hdr_metadata->partID == 1)
          OCT[i] = sl_hdr_metadata->kCoefficient[i] * (TargetDisplayLuminance - 100) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
    else
      OCT[i] = sl_hdr_metadata->kCoefficient[i];
  }

  for (i = 0; i < 4; i++)
    OCT[i+3] = sl_hdr_metadata->matrixCoefficient[i] - 512;
}

static void Compute_VideoRange(int yuv_range, int *inv_y_ratio, int *inv_chroma_ratio, int *footroom, int *l_headroom, int *c_headroom)
{
    if (yuv_range == YUV_LIMITED_RANGE)
    {
        *inv_y_ratio = 1196;
        *inv_chroma_ratio = 1169;
        *footroom = 64;
        *l_headroom = 940;
        *c_headroom = 960;
    }
    else
    {
        *inv_y_ratio = 1024;
        *inv_chroma_ratio = 1024;
        *footroom = 0;
        *l_headroom = 1023;
        *c_headroom = 1023;
    }
}

/**
 * @brief Compute C_LUT, P_LUT, Range, mu0 / mu1 and OCT (called once per frame)
 *
 * @param sl_hdr_metadata[in] : current metadata
 * @param TargetDisplayLuminance[in] : display brightness
 * @param yuv_range[in] : legal/full
 * @param mu0[out] : mu0
 * @param mu1[out] : mu1
 * @param OCT[out] : OCT
 * @param C_LUT[out] : pointer to the computed C_LUT
 * @param P_LUT[out] : pointer to the computed P_LUT
 * @param inv_y_ratio[out] : inv_y_ratio
 * @param inv_chroma_ratio[out] : inv_chroma_ratio
 * @param footroom[out] : footroom
 * @param l_headroom[out] : l_headroom
 * @param c_headroom[out] : c_headroom
 *
 * @return void
*/
void Compute_LUTs(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int yuv_range, unsigned short *mu0, unsigned short *mu1, int *OCT, unsigned short *C_LUT, unsigned short *P_LUT, int *inv_y_ratio, int *inv_chroma_ratio, int *footroom, int *l_headroom, int *c_headroom)
{
    /* Compute mu0 / mu1 and OCT */
    Compute_Mu_OCT(sl_hdr_metadata, TargetDisplayLuminance, mu0, mu1, OCT);

    /* Compute C_LUT */
    Compute_C_LUT(sl_hdr_metadata, TargetDisplayLuminance, C_LUT);

    /* Compute P_LUT */
    Compute_P_LUT(sl_hdr_metadata, TargetDisplayLuminance, P_LUT);

    /* Compute Range */
    Compute_VideoRange(yuv_range, inv_y_ratio, inv_chroma_ratio, footroom, l_headroom, c_headroom);
}
