/****************** COPYRIGHT AND CONFIDENTIALITY INFORMATION ******************
  Copyright (C) 2014-2018  Technicolor Technology Licensing LLC and/or
                           its Group Company ("Technicolor")

  Technicolor (R) is registered trademark and trade name of Technicolor group
  company, and shall not be used in any manner without express written from
  Technicolor.

  Portions Copyright (C) 2016-2018  Royal Philips N.V.
  Philips Group Innovation
  Eindhoven, The Netherlands
  Philips Confidential
  All rights are reserved. Reproduction in whole or in part is
  prohibited without the written consent of the copyright owner.

  This program contains proprietary information which is a trade secret of
  Technicolor and/or Philips and also is an unpublished
  work protected under applicable intellectual property laws, including laws
  related to copyright/right of authorship.
  This program may also be covered by patents and/or pending patent
  applications.
  You must retain this program in confidence and may not use or make copies
  of this program other than as permitted in a written agreement with
  Technicolor, unless otherwise expressly allowed by applicable laws.

  Unless expressly agreed otherwise by Technicolor under a specific
  written agreement signed by Technicolor and you, you are only
  licensed to use this program under the copyrights owned by
  Technicolor and/or Philips embodied in the program,
  and your use of the program and documentation is strictly limited to your own
  internal evaluation of such program and its functionalities.
  You may not reproduce, decompile, reverse engineer,
  disassemble, attempt to derive the source code of, modify, or create
  derivative works of the program, any update, or any part thereof.
  Any violation or attempt to do so is a violation of the rights of Technicolor.
  If you or any person under your control or authority breaches this
  restriction, you may be subject to prosecution and damages.

  Portions of this program are licensed to Technicolor from Philips under a
  limited copyright license to which Technicolor is providing a sublicense
  to you subject to the above terms.
*******************************************************************************/

/**
 * @file SL_LUT_fill.c
 *
 * @section DESCRIPTION
 * LUT generation for the Prime Single HDR decoder model<br>
*/

#include "SL_common.h"

#include "SL_LUT_fill.h"
#include "SL_math.h"

#define sdrDisplayLuminance 100

enum { SHIFT = 16 };
enum { ONE = 1 << SHIFT };
enum { HALF = ONE >> 1 };

static const int Kappa[201] = {
       0,  56809,  65536,  70857,  74718,  77757,  80268,  82408,
   84274,  85929,  87417,  88769,  90007,  91150,  92211,  93201,
   94130,  95004,  95830,  96613,  97356,  98065,  98741,  99389,
  100009, 100605, 101179, 101731, 102263, 102778, 103276, 103757,
  104224, 104677, 105116, 105543, 105959, 106363, 106757, 107141,
  107515, 107881, 108237, 108586, 108926, 109260, 109586, 109905,
  110218, 110524, 110824, 111119, 111407, 111691, 111969, 112243,
  112511, 112775, 113034, 113289, 113540, 113787, 114029, 114268,
  114504, 114735, 114964, 115189, 115410, 115629, 115844, 116056,
  116266, 116472, 116676, 116877, 117076, 117272, 117466, 117657,
  117845, 118032, 118216, 118398, 118578, 118756, 118931, 119105,
  119277, 119447, 119615, 119781, 119945, 120108, 120269, 120428,
  120586, 120742, 120896, 121049, 121201, 121351, 121499, 121646,
  121792, 121936, 122079, 122221, 122361, 122500, 122638, 122774,
  122910, 123044, 123177, 123309, 123440, 123569, 123698, 123825,
  123952, 124077, 124201, 124325, 124447, 124569, 124689, 124809,
  124927, 125045, 125162, 125278, 125393, 125507, 125620, 125733,
  125845, 125956, 126066, 126175, 126284, 126391, 126498, 126605,
  126710, 126815, 126919, 127023, 127126, 127228, 127329, 127430,
  127530, 127629, 127728, 127826, 127924, 128021, 128117, 128213,
  128308, 128402, 128496, 128590, 128683, 128775, 128867, 128958,
  129048, 129139, 129228, 129317, 129406, 129494, 129581, 129668,
  129755, 129841, 129927, 130012, 130097, 130181, 130264, 130348,
  130431, 130513, 130595, 130676, 130758, 130838, 130919, 130998,
  131078, 131157, 131235, 131314, 131391, 131469, 131546, 131623,
  131699
};

static int apply_pq(int L_in)
{
  enum { L_REF = (10000 << SHIFT) };
  enum { LOG2_SFI_W32F15 = 22713 };
  enum { M1 = 10440 };
  enum { M2 = 5167104 };
  enum { C1 = 54784 };
  enum { C2 = 1235456 };
  enum { C3 = 1224704 };
  int res, num, den, is_lsb_set;

  /* pow(L, m1) */
  res = sfi_w32f15_div(L_in << 1, L_REF);
  res = sfi_w32f15_log(res) - LOG2_SFI_W32F15;
  res = sfi_w32f15_mult(res, M1);
  is_lsb_set = res & 0x1;
  res >>= 1;
  res = sfi_w32f15_exp(res);
  res <<= 1;
  if (is_lsb_set)
    res += (res + (1 << 15)) >> 16;
  /* c1 + c2 * pow(L, m1) */
  num = sfi_w32f15_mult(C2, res);
  ++num;
  num >>= 1;
  num += C1;
  /* 1 + c3 * pow(L, m1) */
  den = sfi_w32f15_mult(C3, res);
  ++den;
  den >>= 1;
  den += ONE;
  /* pow((c1 + c2 * pow(L, m1)) / (1 + c3 * pow(L, m1)), m2)  */
  res = sfi_w32f15_div(num << 1, den);
  res = sfi_w32f15_log(res) - LOG2_SFI_W32F15;
  res = sfi_w32f15_mult(res, M2);
  is_lsb_set = res & 0x1;
  res >>= 1;
  res = sfi_w32f15_exp(res);
  res <<= 1;
  if (is_lsb_set)
    res += (res + (1 << 15)) >> 16;

  return res;
}

static int apply_oetf(int x, int L)
{
  enum { EOTFRHO = (33 << SHIFT) };
  enum { L_REF = (10000 << SHIFT) };
  enum { LOG2_SFI_W32F15 = 22713 };
  enum { ONE_OVER_GAMMA = 27307 };
  int rho_minus1, res, num, den, is_lsb_set;

  /* rho(L) - 1 = (eotfrho - 1) * pow(L / Lref, 1/gamma) */
  rho_minus1 = EOTFRHO - ONE;
  res = sfi_w32f15_div(L << 1, L_REF);
  res = sfi_w32f15_log(res) - LOG2_SFI_W32F15;
  res = sfi_w32f15_mult(res, ONE_OVER_GAMMA);
  is_lsb_set = res & 0x1;
  res >>= 1;
  res = sfi_w32f15_exp(res);
  res <<= 1;
  if (is_lsb_set)
    res += (res + (1 << 15)) >> 16;
  rho_minus1 = sfi_w32f15_mult(rho_minus1, res);
  ++rho_minus1;
  rho_minus1 >>= 1;
  /* (rho(L) - 1) * pow(x, 1/gamma) */
  res = sfi_w32f15_log(x) - LOG2_SFI_W32F15;
  res = sfi_w32f15_mult(res, ONE_OVER_GAMMA);
  is_lsb_set = res & 0x1;
  res >>= 1;
  res = sfi_w32f15_exp(res);
  res <<= 1;
  if (is_lsb_set)
    res += (res + (1 << 15)) >> 16;
  res = sfi_w32f15_mult(rho_minus1, res);
  ++res;
  res >>= 1;
  /* (rho(L) - 1) * pow(x, 1/gamma) + 1 */
  res += ONE;
  /* log((rho(L) - 1) * pow(x, 1/gamma) + 1) / log(rho(L)) */
  num = (sfi_w32f15_log(res) - LOG2_SFI_W32F15) << 1;
  den = (sfi_w32f15_log(rho_minus1 + ONE) - LOG2_SFI_W32F15) << 1;
  res = sfi_w32f15_div(num << 1, den);

  return res;
}

/******************************************************************************
 * C-LUT reconstruction
 ******************************************************************************/

/**
 * @brief Compute the C_LUT (called once per frame)
 *
 * @param sl_hdr_metadata[in] : current metadata
 * @param TargetDisplayLuminance[in] : display brightness
 * @param C_LUT[out] : pointer to the computed C_LUT
 *
 * @return void
*/
void Compute_C_LUT(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, unsigned short *C_LUT)
{
  static unsigned short C_REF_LUT[64] = { 4100, 2050, 1367, 1025, 820, 683, 586, 513, 456, 410, 373, 342, 315, 293, 273, 256, 241, 228, 216, 205, 195, 186, 178, 171, 164, 158, 152, 146, 141, 137, 132, 128, 124, 121, 117, 114, 111, 108, 105, 103, 100, 98, 95, 93, 91, 89, 87, 85, 84, 82, 80, 79, 77, 76, 75, 73, 72, 71, 69, 68, 67, 66, 65, 64 }; /* 16b */
  static unsigned short C_REF_LUT_GAMMA[64] = { 12, 32, 56, 84, 115, 149, 185, 223, 263, 305, 348, 393, 440, 488, 537, 588, 640, 694, 748, 804, 861, 919, 978, 1038, 1099, 1161, 1224, 1287, 1352, 1418, 1485, 1552, 1620, 1690, 1760, 1830, 1902, 1974, 2047, 2121, 2196, 2271, 2347, 2424, 2502, 2580, 2659, 2738, 2818, 2899, 2981, 3063, 3146, 3229, 3313, 3398, 3483, 3569, 3655, 3742, 3830, 3918, 4007, 4096 }; /* 22b */
  int maxCoeff, m3, xl, xs, xt, c = 0, i, j, j_last, sg_size, sg_x[8], sg_y[8], idx[8], sgf[65], betaP[65];

  maxCoeff = sl_hdr_metadata->hdrPicColourSpace ? 482 : 475;
  if (sl_hdr_metadata->partID == 1) /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
    m3 = maxCoeff;
  else /* HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) */
    m3 = sl_hdr_metadata->matrixCoefficient[3] - 512;

  if (!sl_hdr_metadata->payloadMode) { /* payloadMode = 0 (Parameter-based) */
    C_LUT[0] = 2047;
    if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
      for (i = 1; i < 65; i++)
        betaP[i] = C_REF_LUT[i-1];
    }
    else { /* HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) */
      xl = apply_pq(sl_hdr_metadata->hdrDisplayMaxLuminance << SHIFT);
      xs = apply_pq(100 << SHIFT);
      xt = apply_pq(TargetDisplayLuminance << SHIFT);
      c = (((xl - xt) << SHIFT) + ((xl - xs) >> 1)) / (xl - xs);
      for (i = 1; i < 65; i++)
        betaP[i] = C_REF_LUT[i - 1] + ((c * C_REF_LUT_GAMMA[i - 1] + (1 << (SHIFT + 5))) >> (SHIFT + 6));
    }

    sg_size = sl_hdr_metadata->u.variables.saturationGainNumVal;

    if (sg_size) {
      if (sl_hdr_metadata->u.variables.saturationGainX[0] != 0) {
        sg_size += 1;
        sg_x[0] = 0;
        i = 0;
      }
      else {
        sg_x[0] = sl_hdr_metadata->u.variables.saturationGainX[0];
        i = 1;
      }
      sg_y[0] = sl_hdr_metadata->u.variables.saturationGainY[0];

      j = 1;
      while (i < sl_hdr_metadata->u.variables.saturationGainNumVal) {
        sg_x[j] = sl_hdr_metadata->u.variables.saturationGainX[i];
        sg_y[j] = sl_hdr_metadata->u.variables.saturationGainY[i];
        i++;
        j++;
      }

      if (sg_x[sg_size - 1] != 255) {
        sg_size += 1;
        sg_x[sg_size - 1] = 255;
        sg_y[sg_size - 1] = sl_hdr_metadata->u.variables.saturationGainY[sl_hdr_metadata->u.variables.saturationGainNumVal - 1];
      }

      for (i = 0; i < sg_size; i++)
        idx[i] = (sg_x[i] + 2) >> 2;

      j_last = idx[0];
      sgf[0] = sg_y[0] << 3;

      for (i = 1; i < sg_size; i++) {
        for (j = j_last+1; j <= idx[i]; j++) {
          sgf[j] = sgf[j_last] + ((((j - j_last) * (sg_y[i] - sg_y[i - 1])) << 3) + ((idx[i] - j_last + 1) >> 1)) / (idx[i] - j_last);
          sgf[j] = Max(sgf[j], 1);
        }
        j_last = idx[i];
      }

      for (i = 1; i < 65; i++) {
        if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance) {
          if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
            sgf[i] = (((sl_hdr_metadata->hdrDisplayMaxLuminance - TargetDisplayLuminance) << 10) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100 + 1) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100) + (sgf[i] * (TargetDisplayLuminance - 100) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100 + 1) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
          }
          else { /* HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) */
            sgf[i] = ((ONE - c) << 10) + sgf[i] * c;
            sgf[i] = (sgf[i] + HALF) >> SHIFT;
          }
        }
        C_LUT[i] = ((255 * betaP[i] * maxCoeff + ((m3 + 1) >> 1)) / m3 + ((sgf[i] + 1) >> 1)) / sgf[i];
        C_LUT[i] = CLAMP((short)C_LUT[i], 0, (1 << 11) - 1);
      }
    }
    else {
      for (i = 1; i < 65; i++) {
        C_LUT[i] = (((betaP[i] + 2) >> 2) * maxCoeff + ((m3 + 1) >> 1)) / m3;
        C_LUT[i] = CLAMP((short)C_LUT[i], 0, (1 << 11) - 1);
      }
    }
  }
  else { /* payloadMode = 1 (Table-based) */
    if ((sl_hdr_metadata->partID == 1 && TargetDisplayLuminance != sl_hdr_metadata->hdrDisplayMaxLuminance) ||
        (sl_hdr_metadata->partID == 2 && TargetDisplayLuminance != sdrDisplayLuminance)) {
      return;
    }

    for (i = 0; i < 65; i++) {
      betaP[i] = (sl_hdr_metadata->u.tables.colourCorrectionY[i] * maxCoeff + ((m3 + 1) >> 1)) / m3;
      C_LUT[i] = CLAMP(betaP[i], 0, (1 << 11) - 1);
    }
  }
}

/******************************************************************************
 * P-LUT SDR2HDR reconstruction
 ******************************************************************************/

/*
  Perceptual Uniform from Gamma
*/

extern int GammatoOETF[65];

/*
  Inverse Custom Curve
*/

static void invinterpolate_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int *icc_x, int *icc_y, int *icc_size)
{
  int i, j;

  *icc_size = sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal;
  icc_x[0] = 0;
  icc_y[0] = 0;
  if (*icc_size > 0 && sl_hdr_metadata->u.variables.tmOutputFineTuningX[0] == 0 && sl_hdr_metadata->u.variables.tmOutputFineTuningY[0] == 0)
    i = 1;
  else {
    *icc_size += 1;
    i = 0;
  }

  if (sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal > 0 && sl_hdr_metadata->u.variables.tmOutputFineTuningX[sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal - 1] == 255 && sl_hdr_metadata->u.variables.tmOutputFineTuningY[sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal - 1] == 255);
  else
    *icc_size += 1;
  icc_x[*icc_size - 1] = ONE;
  icc_y[*icc_size - 1] = ONE;

  j = 1;
  while (j < *icc_size - 1) {
    icc_x[j] = sl_hdr_metadata->u.variables.tmOutputFineTuningY[i] * 257 + (sl_hdr_metadata->u.variables.tmOutputFineTuningY[i] & 128 ? 1 : 0);
    icc_y[j] = sl_hdr_metadata->u.variables.tmOutputFineTuningX[i] * 257 + (sl_hdr_metadata->u.variables.tmOutputFineTuningX[i] & 128 ? 1 : 0);
    i++;
    j++;
  }
}

static int invinterpolate(int pu, int *icc_x, int *icc_y, int icc_size)
{
  int y = pu, i = 0;
  unsigned int delta_x, delta_y, x_tmp, y_tmp;

  if (icc_size > 2) {
    while (pu >= icc_x[i] && i < icc_size - 1)
      ++i;

    delta_x = icc_x[i] - icc_x[i - 1];
    delta_y = icc_y[i] - icc_y[i - 1];
    x_tmp = pu - icc_x[i - 1];
    y_tmp = icc_y[i - 1];

    y = Min((x_tmp * delta_y + (delta_x >> 1)) / delta_x + y_tmp, ONE);
  }

  return y;
}

/*
  Inverse ParaBoLa
*/

static void invparabola_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int *ipbl_base_gain, int *ipbl_hgc, int *ipbl_one_div_a, int *ipbl_one_div_a_shift, int *ipbl_min_b_div_2a, int *ipbl_lb_b2_min_4ac_rb_div_4a2, int *ipbl_lb_b2_min_4ac_rb_div_4a2_shift, int *ipbl_ylow, int *ipbl_yhigh)
{
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;
  int kappa = Kappa[Lhdr_idx];
  int base_gain, hgc, midadj;
  int pa = 0, pb = 0, pc4 = 0, sh, xmid, xlow, xhigh, ylow, yhigh, den;
  int tmp, num, precision, prec1, prec2, prec3, prec4, prec5, prec6, prec7, sh1, sh2;

  base_gain = (sfi_w32f15_mult(kappa << (SHIFT - 4), HALF + ((sl_hdr_metadata->u.variables.shadowGain * 257 + 1) >> 1)) + (1 << (SHIFT - 4))) >> (SHIFT - 3);
  hgc = (sl_hdr_metadata->u.variables.highlightGain * 257 + 1) >> 1;
  midadj = sl_hdr_metadata->u.variables.midToneWidthAdjFactor * 257 + (sl_hdr_metadata->u.variables.midToneWidthAdjFactor & 128 ? 1 : 0);

  if (midadj) {
    /* pa = -0.5 * (base_gain - hgc) / midadj */
    precision = 6;
    pa = base_gain - hgc;
    if (ABS(pa) < 1 << 17) ++precision;
    if (ABS(pa) < 1 << 16) ++precision;
    if (ABS(pa) < 1 << 15) ++precision;
    if (midadj > 1 << 9)  ++precision;
    if (midadj > 1 << 10) ++precision;
    if (midadj > 1 << 11) ++precision;
    if (midadj > 1 << 12) ++precision;
    if (midadj > 1 << 13) ++precision;
    if (midadj > 1 << 14) ++precision;
    if (midadj > 1 << 15) ++precision;
    pa = sfi_w32f15_div(pa << precision, midadj);
    pa = -(pa >> precision);

    /* pb = (1 - hgc) / midadj + (base_gain + hgc) / 2 */
    precision = 5;
    pb = ONE - hgc;
    if (ABS(pb) < 1 << 15) ++precision;
    if (ABS(pb) < 1 << 14) ++precision;
    if (midadj > 1 << 9)  ++precision;
    if (midadj > 1 << 10) ++precision;
    if (midadj > 1 << 11) ++precision;
    if (midadj > 1 << 12) ++precision;
    if (midadj > 1 << 13) ++precision;
    if (midadj > 1 << 14) ++precision;
    if (midadj > 1 << 15) ++precision;
    pb = sfi_w32f15_div(pb << (2 + precision), midadj);
    pb += (base_gain + hgc) << precision;
    pb = (pb + (1 << precision)) >> (1 + precision);

    /* pc4 (actually 4 * pc) = -4 * SQR((base_gain - hgc) * midadj - 2 * (1 - hgc)) / (8 * (base_gain - hgc) * midadj) */
    den = base_gain - hgc;
    precision = 13;
    den = sfi_w32f15_mult(den, midadj << precision);
    if (den == 0)
      pc4 = INT32_MIN;
    else {
      num = den;
      num -= (ONE - hgc) << (2 + precision);
      tmp = sfi_w32f15_div(num, den);
      num = sfi_w32f15_mult(num >> 9, tmp);
      num >>= (2 - 9 + precision);
      pc4 = -num;
    }
  }

  /* xlow  = (1 - hgc) / (base_gain - hgc) - midadj / 2 */
  /* xhigh = (1 - hgc) / (base_gain - hgc) + midadj / 2 */
  precision = 6;
  xmid = ONE - hgc;
  den = base_gain - hgc;
  if (den == 0)
    xmid = INT32_MAX;
  else
    xmid = sfi_w32f15_div((xmid << (1 + precision)), den);
  xmid = xmid >> precision;
  xlow = xmid - ((midadj + 1) >> 1);
  xhigh = xmid + ((midadj + 1) >> 1);

  /* ylow  = base_gain * xlow        */
  /* yhigh = hgc * xhigh + (1 - hgc) */
  yhigh = base_gain;
  yhigh = sfi_w32f15_mult(yhigh, xlow);
  ylow = (yhigh + 1) >> 1;
  xlow = hgc;
  xlow = sfi_w32f15_mult(xlow, xhigh);
  yhigh = (xlow + 1) >> 1;
  yhigh += ONE - hgc;
  yhigh = Min(yhigh, ONE);

  *ipbl_base_gain = base_gain;
  *ipbl_hgc = hgc;
  *ipbl_one_div_a = 0;
  *ipbl_one_div_a_shift = 0;
  *ipbl_min_b_div_2a = 0;
  *ipbl_lb_b2_min_4ac_rb_div_4a2 = 0;
  *ipbl_lb_b2_min_4ac_rb_div_4a2_shift = 0;
  *ipbl_ylow = ylow;
  *ipbl_yhigh = yhigh;

  if (!pa)
    return;

  /* ((b/2)^2 / a - c) / a = (b^2 - 4 * a * c) / (4 * a^2) */
  /* pa is always less than or equal to zero         */
  /* pb is always greater than to zero               */
  /* pc is always less than to zero                  */
  prec1 = msb32(ABS(pb));
  prec3 = 8 - (prec1 - 15);
  tmp = (prec3 > 0) ? (pb << ABS(prec3)) : (pb >> ABS(prec3));
  /* b * b */
  tmp = sfi_w32f15_mult(tmp, tmp);
  if (prec3 < 0) {
    num = pb & ((1 << ABS(prec3)) - 1);
    num = (2 * pb + num) * num;
  }
  else
    num = 0;
  tmp += num >> (15 + 2 * ABS(prec3));
  prec4 = Max(16 - msb32(ABS(pa)), 0);
  /* b * b / a */
  tmp = sfi_w32f15_div(tmp >> prec4, pa);
  prec5 = 2 * prec3 + 1;
  prec5 -= prec4 + 1;
  prec7 = 31 - msb32(ABS(tmp));
  /* b * b / a - 4 * c */
  if (prec5 > 0)
    tmp -= (pc4 << ABS(prec5));
  else {
    if (prec7 >= ABS(prec5)) {
      tmp = (tmp << ABS(prec5)) - pc4;
      prec5 = 0;
    }
    else
      tmp -= (pc4 >> ABS(prec5));
  }
  prec2 = msb32(ABS(pa));
  prec6 = 31 - msb32(ABS(tmp)) - ((16 - prec2) > 0 ? 16 - prec2 : 0);
  /* (b * b / a - 4 * c) / a */
  if (prec6 > 0)
    tmp = sfi_w32f15_div((tmp << ABS(prec6)), pa);
  else
    tmp = sfi_w32f15_div((tmp >> ABS(prec6)), pa);
  sh = 0; /* shift */
  while (tmp >> sh >= 1 << 23) {
    sh += 2;
  }
  *ipbl_lb_b2_min_4ac_rb_div_4a2 = tmp >> sh;
  *ipbl_lb_b2_min_4ac_rb_div_4a2_shift = prec5 + (prec6 - 1) + 2 - sh;

  precision = 3;
  tmp = -pb;
  tmp = sfi_w32f15_div(tmp << precision, pa);
  *ipbl_min_b_div_2a = (tmp + (1 << (precision - 1))) >> precision;

  tmp = pa;
  sh1 = sh2 = 0;
  while (ABS(pa) << sh1 <= ONE)
    ++sh1;
  tmp = sfi_w32f15_div(1 << 30, pa << sh1);
  while (-tmp >> sh2 >= 1 << 23)
    ++sh2;
  if (sh2 > 0)
    *ipbl_one_div_a = (tmp - (1 << (sh2 - 1))) >> sh2;
  else
    *ipbl_one_div_a = tmp;
  *ipbl_one_div_a_shift = 13 - sh1 - sh2;
}

static int invparabola(int icc, int ipbl_base_gain, int ipbl_hgc, int ipbl_one_div_a, int ipbl_one_div_a_shift, int ipbl_min_b_div_2a, int ipbl_lb_b2_min_4ac_rb_div_4a2, int ipbl_lb_b2_min_4ac_rb_div_4a2_shift, int ipbl_ylow, int ipbl_yhigh)
{
  int perceptualpbl, sh1, sh2;

  if (icc >= ipbl_yhigh) {
    /* perceptualpbl = (icc + hgc - 1) / hgc */
    perceptualpbl = (icc + ipbl_hgc - ONE) << (SHIFT - 2);
    if (!perceptualpbl) {
      if (!ipbl_hgc) {
        perceptualpbl = ONE;
      }
    }
    else {
      if (ipbl_hgc) {
        perceptualpbl /= ipbl_hgc;
        perceptualpbl <<= 2;
      }
    }
  }
  else if (icc <= ipbl_ylow) {
    /* perceptualpbl = icc / base_gain */
    perceptualpbl =  icc << (SHIFT - 2);
    perceptualpbl /= (ipbl_base_gain + 2) >> 2;
  }
  else {
    /* perceptualpbl = (-pb + sqrt(pb * pb - 4 * pa * (pc - icc))) / (2 * pa) */
    sh1 = ipbl_lb_b2_min_4ac_rb_div_4a2_shift;
    sh2 = ipbl_one_div_a_shift;
    perceptualpbl = ipbl_lb_b2_min_4ac_rb_div_4a2;
    if (sh2 - sh1 > 0)
      perceptualpbl <<= ABS(sh2 - sh1);
    else
      perceptualpbl >>= ABS(sh2 - sh1);
    perceptualpbl += sfi_w32f15_mult(ipbl_one_div_a, icc) >> 1;

    if (perceptualpbl > 0) {
      if (sh2 & 0x1) {
        /* sh2 odd -> make even before entering sqrt16() */
        perceptualpbl >>= 1;
        --sh2;
      }

      sh1 = 0;
      if (perceptualpbl != 0) {
        while (((unsigned int)perceptualpbl << sh1) < (1 << 30)) {
          ++sh1;
          ++sh1;
        }
        perceptualpbl <<= sh1;
      }

      perceptualpbl = sqrt16(perceptualpbl);

      /* Correct result of sqrt16() */
      sh1 += sh2 - SHIFT;
      sh1 = sh1 >> 1;
      perceptualpbl = (sh1 > 0) ? perceptualpbl >> ABS(sh1) : perceptualpbl << ABS(sh1);
    }
    else
      perceptualpbl = 0;

    perceptualpbl = ipbl_min_b_div_2a - perceptualpbl;
  }

  perceptualpbl = CLAMP(perceptualpbl, 0, ONE);

  return perceptualpbl;
}

/*
  Inverse Black & White Stretch
*/

static void invbwstretch_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int *ibws_black_stretch, int *ibws_white_stretch)
{
  *ibws_black_stretch = (sl_hdr_metadata->u.variables.tmInputSignalBlackLevelOffset * 257 + 4) >> 3;
  *ibws_white_stretch = (sl_hdr_metadata->u.variables.tmInputSignalWhiteLevelOffset * 257 + 1) >> 1;
}

static int invbwstretch(int ipbl, int ibws_black_stretch, int ibws_white_stretch)
{
  unsigned int perceptualstretched;

  perceptualstretched = (ONE - ibws_white_stretch - ibws_black_stretch) >> 1;
  perceptualstretched *= ipbl;
  perceptualstretched = (perceptualstretched + (HALF >> 1)) >> (SHIFT - 1);
  perceptualstretched += ibws_black_stretch;

  perceptualstretched = CLAMP((int)perceptualstretched, 0, ONE);

  return perceptualstretched;
}

/*
  Inverse Black Gain Limiter
*/

static const int invbglimiter_alpha[201] = {
      0, 42287, 36656, 33903, 32151, 30894, 29928, 29151,
  28506, 27956, 27481, 27062, 26690, 26355, 26052, 25775,
  25521, 25286, 25068, 24865, 24675, 24497, 24329, 24171,
  24021, 23878, 23743, 23614, 23491, 23373, 23261, 23153,
  23049, 22949, 22853, 22761, 22672, 22586, 22502, 22422,
  22344, 22268, 22195, 22123, 22054, 21987, 21921, 21858,
  21796, 21735, 21676, 21619, 21563, 21508, 21455, 21403,
  21351, 21302, 21253, 21205, 21158, 21112, 21067, 21023,
  20980, 20938, 20896, 20855, 20815, 20776, 20737, 20699,
  20662, 20625, 20589, 20554, 20519, 20485, 20451, 20418,
  20385, 20353, 20321, 20290, 20259, 20229, 20199, 20169,
  20140, 20112, 20083, 20056, 20028, 20001, 19974, 19948,
  19922, 19896, 19871, 19845, 19821, 19796, 19772, 19748,
  19724, 19701, 19678, 19655, 19633, 19610, 19588, 19567,
  19545, 19524, 19503, 19482, 19461, 19441, 19421, 19401,
  19381, 19361, 19342, 19323, 19304, 19285, 19266, 19248,
  19229, 19211, 19193, 19176, 19158, 19141, 19123, 19106,
  19089, 19072, 19056, 19039, 19023, 19007, 18991, 18975,
  18959, 18943, 18928, 18912, 18897, 18882, 18867, 18852,
  18837, 18822, 18808, 18793, 18779, 18765, 18751, 18737,
  18723, 18709, 18695, 18682, 18668, 18655, 18642, 18628,
  18615, 18602, 18589, 18577, 18564, 18551, 18539, 18526,
  18514, 18502, 18489, 18477, 18465, 18453, 18442, 18430,
  18418, 18406, 18395, 18383, 18372, 18361, 18349, 18338,
  18327, 18316, 18305, 18294, 18283, 18273, 18262, 18251,
  18241
};

static void invbglimiter_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int *ibgl_alpha, int *ibgl_is_bypassed)
{
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;

  *ibgl_alpha = invbglimiter_alpha[Lhdr_idx];
  *ibgl_is_bypassed = (sl_hdr_metadata->u.variables.tmInputSignalBlackLevelOffset == 0) ? 1 : 0;
}

static int invbglimiter(int pu, int ibws, int ibgl_is_bypassed, int ibgl_alpha)
{
  enum { IMPL_SHIFT = 14 };
  enum { IMPL_HALF = 1 << (IMPL_SHIFT - 1) };
  unsigned int glim = ibws;

  if (ibgl_is_bypassed == 0) {
    glim = pu * ibgl_alpha;
    glim += IMPL_HALF;
    glim >>= IMPL_SHIFT;
    glim = Min((int)glim, ibws);
  }

  glim = CLAMP((int)glim, 0, ONE - 1);

  return glim;
}

/*
  EOTF and Gamma 2.0 or 2.4
*/

extern unsigned short EOTFtoSqrt_alpha[200], EOTFtoGamma_alpha[200];
extern int EOTFtoSqrt_quadrint_50(int x_in);
extern int EOTFtoGamma_quadrint_50(int x_in);
extern int EOTFtoSqrt_quadrint_100(int x_in);
extern int EOTFtoGamma_quadrint_100(int x_in);
extern int EOTFtoSqrt_quadrint_400(int x_in);
extern int EOTFtoGamma_quadrint_400(int x_in);
extern int EOTFtoSqrt_quadrint_700(int x_in);
extern int EOTFtoGamma_quadrint_700(int x_in);
extern int EOTFtoSqrt_quadrint_1000(int x_in);
extern int EOTFtoGamma_quadrint_1000(int x_in);
extern int EOTFtoSqrt_quadrint_2000(int x_in);
extern int EOTFtoGamma_quadrint_2000(int x_in);
extern int EOTFtoSqrt_quadrint_4000(int x_in);
extern int EOTFtoGamma_quadrint_4000(int x_in);
extern int EOTFtoSqrt_quadrint_10000(int x_in);
extern int EOTFtoGamma_quadrint_10000(int x_in);
static int (*EOTFtoSqrt_quadrint_low)(int x_in);
static int (*EOTFtoGamma_quadrint_low)(int x_in);
static int (*EOTFtoSqrt_quadrint_high)(int x_in);
static int (*EOTFtoGamma_quadrint_high)(int x_in);

static void EOTFtoSqrt_initialize(int TargetDisplayLuminance, unsigned short *sqrtY_alpha)
{
  unsigned char Ldisplay_idx = TargetDisplayLuminance / 50;

  *sqrtY_alpha = EOTFtoSqrt_alpha[Ldisplay_idx - 1];

  if (Ldisplay_idx <= 2) {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_50;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_100;
  }
  else if (Ldisplay_idx <= 8) {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_100;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_400;
  }
  else if (Ldisplay_idx <= 14) {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_400;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_700;
  }
  else if (Ldisplay_idx <= 20) {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_700;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_1000;
  }
  else if (Ldisplay_idx <= 40) {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_1000;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_2000;
  }
  else if (Ldisplay_idx <= 80) {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_2000;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_4000;
  }
  else {
    EOTFtoSqrt_quadrint_low = EOTFtoSqrt_quadrint_4000;
    EOTFtoSqrt_quadrint_high = EOTFtoSqrt_quadrint_10000;
  }
}

static int EOTFtoSqrt(int ibgl, unsigned short sqrtY_alpha)
{
  enum { IMPL_SHIFT = 12 };
  enum { IMPL_ONE = (1 << IMPL_SHIFT) };
  int ylow, yhigh, sqrtY;

  ylow = EOTFtoSqrt_quadrint_low(ibgl);
  yhigh = EOTFtoSqrt_quadrint_high(ibgl);

  sqrtY = (sqrtY_alpha * yhigh + (IMPL_ONE - sqrtY_alpha) * ylow + (1 << (IMPL_SHIFT + 2))) >> (IMPL_SHIFT + 3);
  sqrtY = CLAMP(sqrtY, 0, (1 << 13) - 1);

  return sqrtY;
}

static void EOTFtoGamma_initialize(int TargetDisplayLuminance, unsigned short *gammaY_alpha)
{
  unsigned char Ldisplay_idx = TargetDisplayLuminance / 50;

  *gammaY_alpha = EOTFtoGamma_alpha[Ldisplay_idx - 1];

  if (Ldisplay_idx <= 2) {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_50;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_100;
  }
  else if (Ldisplay_idx <= 8) {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_100;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_400;
  }
  else if (Ldisplay_idx <= 14) {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_400;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_700;
  }
  else if (Ldisplay_idx <= 20) {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_700;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_1000;
  }
  else if (Ldisplay_idx <= 40) {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_1000;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_2000;
  }
  else if (Ldisplay_idx <= 80) {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_2000;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_4000;
  }
  else {
    EOTFtoGamma_quadrint_low = EOTFtoGamma_quadrint_4000;
    EOTFtoGamma_quadrint_high = EOTFtoGamma_quadrint_10000;
  }
}

static int EOTFtoGamma(int ibgl, unsigned short gammaY_alpha)
{
  enum { IMPL_SHIFT = 12 };
  enum { IMPL_ONE = (1 << IMPL_SHIFT) };
  int ylow, yhigh, gammaY;

  ylow = EOTFtoGamma_quadrint_low(ibgl);
  yhigh = EOTFtoGamma_quadrint_high(ibgl);

  gammaY = (gammaY_alpha * yhigh + (IMPL_ONE - gammaY_alpha) * ylow + (1 << (IMPL_SHIFT + 2))) >> (IMPL_SHIFT + 3);
  gammaY = CLAMP(gammaY, 0, (1 << 13) - 1);

  return gammaY;
}

static void EOTFtoSqrtGamma_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int *modFactor, unsigned short *sqrtY_alpha, unsigned short *gammaY_alpha)
{
  if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance)
    *modFactor = (((sl_hdr_metadata->hdrDisplayMaxLuminance - TargetDisplayLuminance) << 8) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
  else
    *modFactor = 1;
  EOTFtoSqrt_initialize(TargetDisplayLuminance, sqrtY_alpha);
  EOTFtoGamma_initialize(TargetDisplayLuminance, gammaY_alpha);
}

static int EOTFtoSqrtGamma(int ibgl, int modFactor, unsigned short sqrtY_alpha, unsigned short gammaY_alpha)
{
  int sqrtY, gammaY, sqrtgammaY;

  sqrtY = EOTFtoSqrt(ibgl, sqrtY_alpha);
  gammaY = EOTFtoGamma(ibgl, gammaY_alpha);
  sqrtgammaY = sqrtY + ((modFactor * (gammaY - sqrtY) + 128) >> 8);

  return sqrtgammaY;
}

/******************************************************************************
 * P-LUT HDR2MDR reconstruction
 ******************************************************************************/

/*
  Perceptual Uniform from ST2084
*/

extern unsigned short ST2084toOETF_max_e_brightness_input[201];
extern unsigned short ST2084toOETF_alpha_low[201];
extern unsigned short ST2084toOETF_alpha_mid[201];
extern unsigned short ST2084toOETF_alpha_high[201];
extern int ST2084toOETF_quadrint_100(int x_in);
extern int ST2084toOETF_quadrint_150(int x_in);
extern int ST2084toOETF_quadrint_300(int x_in);
extern int ST2084toOETF_quadrint_600(int x_in);
extern int ST2084toOETF_quadrint_1000(int x_in);
extern int ST2084toOETF_quadrint_3000(int x_in);
extern int ST2084toOETF_quadrint_6000(int x_in);
extern int ST2084toOETF_quadrint_10000(int x_in);
static int (*ST2084toOETF_quadrint_low)(int x_in);
static int (*ST2084toOETF_quadrint_high)(int x_in);

static void ST2084toOETF_initialize(struct sl_hdr_metadata *sl_hdr_metadata, unsigned short *pu_max_e_brightness_input, unsigned short *pu_alpha_low, unsigned short *pu_alpha_mid, unsigned short *pu_alpha_high, int *pu_lower_idx, int *pu_upper_idx)
{
  enum { NUMBER_OF_INTERVALS = 7 };
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;
  int interval_lower_table_[NUMBER_OF_INTERVALS] = { 29, 29, 29, 29, 22, 18, 14 };
  int interval_upper_table_[NUMBER_OF_INTERVALS] = { 39, 39, 39, 39, 33, 27, 23 };

  *pu_max_e_brightness_input = ST2084toOETF_max_e_brightness_input[Lhdr_idx];
  *pu_alpha_low = ST2084toOETF_alpha_low[Lhdr_idx];
  *pu_alpha_mid = ST2084toOETF_alpha_mid[Lhdr_idx];
  *pu_alpha_high = ST2084toOETF_alpha_high[Lhdr_idx];

  if (Lhdr_idx > 6000/50) {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_10000;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_6000;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 1] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 1] << (SHIFT - 6);
  }
  else if (Lhdr_idx > 3000/50) {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_6000;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_3000;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 2] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 2] << (SHIFT - 6);
  }
  else if (Lhdr_idx > 1000/50) {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_3000;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_1000;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 3] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 3] << (SHIFT - 6);
  }
  else if (Lhdr_idx > 600/50) {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_1000;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_600;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 4] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 4] << (SHIFT - 6);
  }
  else if (Lhdr_idx > 300/50) {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_600;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_300;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 5] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 5] << (SHIFT - 6);
  }
  else if (Lhdr_idx > 150/50) {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_300;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_150;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 6] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 6] << (SHIFT - 6);
  }
  else {
    ST2084toOETF_quadrint_high = ST2084toOETF_quadrint_150;
    ST2084toOETF_quadrint_low = ST2084toOETF_quadrint_100;
    *pu_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 7] << (SHIFT - 6);
    *pu_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 7] << (SHIFT - 6);
  }
}

static int ST2084toOETF(int i, unsigned short pu_max_e_brightness_input, unsigned short pu_alpha_low, unsigned short pu_alpha_mid, unsigned short pu_alpha_high, int pu_lower_idx, int pu_upper_idx)
{
  enum { IMPL_SHIFT = 14 };
  enum { IMPL_ONE = (1 << IMPL_SHIFT) };
  enum { IMPL_HALF = 1 << (IMPL_SHIFT - 1) };
  int x, ylow, yhigh, pu;

  x = (i * pu_max_e_brightness_input) >> (6 + IMPL_SHIFT - SHIFT);
  if (x >= (1 << SHIFT))
    return (1 << SHIFT) - 1;

  ylow = ST2084toOETF_quadrint_low(x);
  yhigh = ST2084toOETF_quadrint_high(x);

  if (x < pu_lower_idx)
    pu = pu_alpha_low * ylow + (IMPL_ONE - pu_alpha_low) * yhigh;
  else if (x < pu_upper_idx)
    pu = pu_alpha_mid * ylow + (IMPL_ONE - pu_alpha_mid) * yhigh;
  else
    pu = pu_alpha_high * ylow + (IMPL_ONE - pu_alpha_high) * yhigh;

  pu = (pu + (x << IMPL_SHIFT) + IMPL_HALF) >> IMPL_SHIFT;

  pu = CLAMP(pu, 0, ONE);

  return pu;
}

/*
  Black & white Stretch
*/

static void bwstretch_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int *bws_black_stretch, int *bws_white_stretch)
{
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;
  int kappa = Kappa[Lhdr_idx], lambda, lambdakappa, scale_hor;

  *bws_black_stretch = (sl_hdr_metadata->u.variables.tmInputSignalBlackLevelOffset * 257 + 4) >> 3;
  *bws_white_stretch = (sl_hdr_metadata->u.variables.tmInputSignalWhiteLevelOffset * 257 + 1) >> 1;

  if (TargetDisplayLuminance != sdrDisplayLuminance) {
    lambda = sfi_w32f15_div((sl_hdr_metadata->hdrDisplayMaxLuminance << SHIFT) << 1, TargetDisplayLuminance << SHIFT);
    lambda = apply_oetf(lambda, TargetDisplayLuminance << SHIFT);
    lambdakappa = sfi_w32f15_mult(kappa, lambda);
    scale_hor = sfi_w32f15_div(((lambdakappa - (kappa << 1)) << 1), lambdakappa - (lambda << 1));
    scale_hor = Max(scale_hor, 0);
    *bws_black_stretch = (*bws_black_stretch * scale_hor + HALF) >> SHIFT;
    *bws_white_stretch = (sfi_w32f15_mult(*bws_white_stretch, scale_hor) + 1) >> 1;
  }
}

static int bwstretch(int pu, int bws_black_stretch, int bws_white_stretch)
{
  int perceptualstretched = pu;

  perceptualstretched -= bws_black_stretch;
  perceptualstretched <<= (SHIFT - 1);
  perceptualstretched /= (ONE - bws_white_stretch - bws_black_stretch) >> 1;

  perceptualstretched = CLAMP(perceptualstretched, 0, ONE);

  return perceptualstretched;
}

/*
  ParaBoLa
*/

static void parabola_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int *pbl_base_gain, int *pbl_hgc, int *pbl_pa, int *pbl_pb, int *pbl_pc4, int *pbl_xlow, int *pbl_xhigh)
{
  enum { PRECISION1 = 3 };
  enum { PRECISION2 = 7 };
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;
  int kappa = Kappa[Lhdr_idx], lambda, MIDX, MIDY, SGC4, HGC4, MIDADJ2;
  int base_gain, hgc, midadj;
  int pa = 0, pb = 0, pc4 = 0, sh, xmid, xlow, xhigh, den;
  int tmp, num, precision, scale;

  base_gain = (sfi_w32f15_mult(kappa << (SHIFT - 4), HALF + ((sl_hdr_metadata->u.variables.shadowGain * 257 + 1) >> 1)) + (1 << (SHIFT - 4))) >> (SHIFT - 3 - PRECISION1);
  hgc = (sl_hdr_metadata->u.variables.highlightGain * 257 + (sl_hdr_metadata->u.variables.highlightGain & 128 ? 1 : 0)) << (PRECISION1 - 1);
  midadj = sl_hdr_metadata->u.variables.midToneWidthAdjFactor * 257 + (sl_hdr_metadata->u.variables.midToneWidthAdjFactor & 128 ? 1 : 0);

  if (TargetDisplayLuminance != sdrDisplayLuminance) {
    lambda = sfi_w32f15_div((sl_hdr_metadata->hdrDisplayMaxLuminance << SHIFT) << 1, TargetDisplayLuminance << SHIFT);
    lambda = apply_oetf(lambda, TargetDisplayLuminance << SHIFT);
    num = sfi_w32f15_div((lambda - ONE) << 1, lambda + ONE);
    den = sfi_w32f15_div((kappa - ONE) << 1, kappa + ONE);
    scale = sfi_w32f15_div(num << 1, den);
    num = (ONE << PRECISION1) - hgc;
    den = base_gain - hgc;
    if (den == 0) {
      if (num == 0)
        xmid = ONE << PRECISION2;
      else
        xmid = (num >= 0) ? INT32_MAX : INT32_MIN;
    }
    else
      xmid = sfi_w32f15_div((num << (1 + PRECISION2)), den);
    num = base_gain + (ONE << PRECISION1);
    den = base_gain - (ONE << PRECISION1);
    den = sfi_w32f15_mult(den, ONE - scale) + (ONE << (2 + PRECISION1));
    SGC4 = sfi_w32f15_div((num << (1 + 1 + 1 + 2)), den);
    SGC4 -= (ONE << 2);
    base_gain = (SGC4 + 2) >> 2;

    MIDX = (sfi_w32f15_mult(den - (ONE << (2 + PRECISION1)), xmid) >> 3) + (xmid << PRECISION1);
    MIDY = (sfi_w32f15_mult(num, xmid) >> 1) - MIDX;
    if (MIDX == (ONE << PRECISION2)) {
      if (TargetDisplayLuminance > sl_hdr_metadata->hdrDisplayMaxLuminance)
        HGC4 = 8 * ONE;
      else
        HGC4 = 0;
    }
    else
      HGC4 = Max(sfi_w32f15_div((MIDY - (ONE << (PRECISION1 + PRECISION2))) <<3, MIDX - (ONE << (PRECISION1 + PRECISION2))), 0);
    HGC4 = Min(HGC4, 8 * ONE);
    hgc = (HGC4 + 2) >> 2;

    if (TargetDisplayLuminance == sl_hdr_metadata->hdrDisplayMaxLuminance)
      midadj = 0;
    else {
      MIDADJ2 = apply_oetf(ABS(scale), sl_hdr_metadata->hdrDisplayMaxLuminance << SHIFT);
      MIDADJ2 = sfi_w32f15_mult(midadj, MIDADJ2);
      midadj = (MIDADJ2 + 1) >> 1;
    }
  }
  else {
    base_gain = base_gain >> PRECISION1;
    hgc = hgc >> PRECISION1;
  }

  if (midadj) {
    /* pa = -0.5 * (base_gain - hgc) / midadj */
    precision = 5;
    pa = base_gain - hgc;
    if (ABS(pa) < (1 << 17)) ++precision;
    if (ABS(pa) < (1 << 16)) ++precision;
    if (ABS(pa) < (1 << 15)) ++precision;
    if (midadj > (1 << 9))  ++precision;
    if (midadj > (1 << 10)) ++precision;
    if (midadj > (1 << 11)) ++precision;
    if (midadj > (1 << 12)) ++precision;
    if (midadj > (1 << 13)) ++precision;
    if (midadj > (1 << 14)) ++precision;
    if (midadj > (1 << 15)) ++precision;
    pa = sfi_w32f15_div(pa << precision, midadj);
    pa = -(pa >> precision);

    /* pb = (1 - hgc) / midadj + (base_gain + hgc) / 2 */
    precision = 5;
    pb = ONE - hgc;
    if (ABS(pb) >= (1 << 16)) --precision;
    if (ABS(pb) < (1 << 15)) ++precision;
    if (midadj > (1 << 9))  ++precision;
    if (midadj > (1 << 10)) ++precision;
    if (midadj > (1 << 11)) ++precision;
    if (midadj > (1 << 12)) ++precision;
    if (midadj > (1 << 13)) ++precision;
    if (midadj > (1 << 14)) ++precision;
    if (midadj > (1 << 15)) ++precision;
    if (precision == 13 && base_gain + hgc >= (1 << 17)) --precision;
    pb = sfi_w32f15_div(pb << (2 + precision), midadj);
    pb += (base_gain + hgc) << precision;
    pb = (pb + (1 << precision)) >> (1 + precision);

    /* pc4 (actually 4 * pc) = -4 * SQR((base_gain - hgc) * midadj - 2 * (1 - hgc)) / (8 * (base_gain - hgc) * midadj) */
    den = base_gain - hgc;
    precision = 13 + 16 - Min(msb32(ABS(ONE - hgc)), 16);
    precision = Min(15 - (msb32(ABS(den)) + msb32(midadj) - 30), precision);
    den = sfi_w32f15_mult(den << (precision >> 1), midadj << ((precision + 1) >> 1));
    if (den == 0)
      pc4 = INT32_MIN;
    else {
      num = den;
      num -= (ONE - hgc) << (2 + precision);
      tmp = sfi_w32f15_div(num, den);
      sh = Max((msb32(ABS(tmp)) + msb32(ABS(num)) - 30) - 16, 0);
      num = sfi_w32f15_mult(num >> sh, tmp);
      pc4 = -(num >> (2 - sh + precision));
    }
  }

  /* xlow  = (1 - hgc) / (base_gain - hgc) - midadj / 2 */
  /* xhigh = (1 - hgc) / (base_gain - hgc) + midadj / 2 */
  precision = 3;
  xmid = ONE - hgc;
  den = base_gain - hgc;
  if (den == 0)
    xmid = INT32_MAX;
  else
    xmid = sfi_w32f15_div ((xmid << (1+precision)), den);
  xmid = xmid >> precision;
  xlow = xmid - ((midadj + 1) >> 1);
  xhigh = xmid + ((midadj + 1) >> 1);

  *pbl_base_gain = base_gain;
  *pbl_hgc = hgc;
  *pbl_pa = pa;
  *pbl_pb = pb;
  *pbl_pc4 = pc4;
  *pbl_xlow = xlow;
  *pbl_xhigh = xhigh;
}

static int parabola(int bws, int pbl_base_gain, int pbl_hgc, int pbl_pa, int pbl_pb, int pbl_pc4, int pbl_xlow, int pbl_xhigh)
{
  int perceptualpbl;

  if (bws <= pbl_xlow) {
    /* perceptualpbl = bws * base_gain */
    perceptualpbl = (sfi_w32f15_mult(bws, pbl_base_gain) + 1) >> 1;
  }
  else if (bws >= pbl_xhigh) {
    /* perceptualpbl = bws * hgc + (1 - hgc) */
    perceptualpbl = sfi_w32f15_mult(bws, pbl_hgc);
    perceptualpbl += (ONE - pbl_hgc) << 1;
    perceptualpbl >>= 1;
  }
  else {
    /* perceptualpbl = (pa * bws + pb) * bws + pc */
    perceptualpbl = sfi_w32f15_mult(bws, pbl_pa);
    perceptualpbl += pbl_pb << 1;
    perceptualpbl = sfi_w32f15_mult(perceptualpbl, bws);
    perceptualpbl += pbl_pc4;
    perceptualpbl >>= 2;
  }

  perceptualpbl = CLAMP(perceptualpbl, 0, ONE);

  return perceptualpbl;
}

/*
  Custom Curve
*/

static void interpolate_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int *cc_x, int *cc_y, int *cc_size)
{
  int i, j;
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;
  int ipbl_base_gain, ipbl_hgc, ipbl_one_div_a, ipbl_one_div_a_shift, ipbl_min_b_div_2a, ipbl_lb_b2_min_4ac_rb_div_4a2, ipbl_lb_b2_min_4ac_rb_div_4a2_shift, ipbl_ylow, ipbl_yhigh;
  int ibws_black_stretch = 0, ibws_white_stretch = 0;
  int bws_black_stretch, bws_white_stretch;
  int pbl_base_gain, pbl_hgc, pbl_pa, pbl_pb, pbl_pc4, pbl_xlow, pbl_xhigh;
  int ipbl, ibws, bws, pbl, kappa = Kappa[Lhdr_idx], lambda, scale_ver = 0;

  *cc_size = sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal;
  cc_x[0] = 0;
  cc_y[0] = 0;
  if (sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal > 0 && sl_hdr_metadata->u.variables.tmOutputFineTuningX[0] == 0 && sl_hdr_metadata->u.variables.tmOutputFineTuningY[0] == 0)
    i = 1;
  else {
    *cc_size += 1;
    i = 0;
  }

  if (sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal > 0 && sl_hdr_metadata->u.variables.tmOutputFineTuningX[sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal - 1] == 255 && sl_hdr_metadata->u.variables.tmOutputFineTuningY[sl_hdr_metadata->u.variables.tmOutputFineTuningNumVal - 1] == 255);
  else
    *cc_size += 1;
  cc_x[*cc_size - 1] = ONE;
  cc_y[*cc_size - 1] = ONE;

  if (TargetDisplayLuminance != sdrDisplayLuminance && *cc_size > 2) {
    lambda = sfi_w32f15_div((sl_hdr_metadata->hdrDisplayMaxLuminance << SHIFT) << 1, TargetDisplayLuminance << SHIFT);
    lambda = apply_oetf(lambda, TargetDisplayLuminance << SHIFT);
    scale_ver = sfi_w32f15_div((ONE - lambda) << 1, ONE - kappa);
    scale_ver = Max(scale_ver, 0);

    invparabola_initialize(sl_hdr_metadata, &ipbl_base_gain, &ipbl_hgc, &ipbl_one_div_a, &ipbl_one_div_a_shift, &ipbl_min_b_div_2a, &ipbl_lb_b2_min_4ac_rb_div_4a2, &ipbl_lb_b2_min_4ac_rb_div_4a2_shift, &ipbl_ylow, &ipbl_yhigh);
    invbwstretch_initialize(sl_hdr_metadata, &ibws_black_stretch, &ibws_white_stretch);
    bwstretch_initialize(sl_hdr_metadata, TargetDisplayLuminance, &bws_black_stretch, &bws_white_stretch);
    parabola_initialize(sl_hdr_metadata, TargetDisplayLuminance, &pbl_base_gain, &pbl_hgc, &pbl_pa, &pbl_pb, &pbl_pc4, &pbl_xlow, &pbl_xhigh);
  }

  j = 1;
  while (j < *cc_size - 1) {
    cc_x[j] = sl_hdr_metadata->u.variables.tmOutputFineTuningX[i] * 257 + (sl_hdr_metadata->u.variables.tmOutputFineTuningX[i] & 128 ? 1 : 0);
    cc_y[j] = sl_hdr_metadata->u.variables.tmOutputFineTuningY[i] * 257 + (sl_hdr_metadata->u.variables.tmOutputFineTuningY[i] & 128 ? 1 : 0);
    if (TargetDisplayLuminance != sdrDisplayLuminance) {
      ipbl = invparabola(cc_x[j], ipbl_base_gain, ipbl_hgc, ipbl_one_div_a, ipbl_one_div_a_shift, ipbl_min_b_div_2a, ipbl_lb_b2_min_4ac_rb_div_4a2, ipbl_lb_b2_min_4ac_rb_div_4a2_shift, ipbl_ylow, ipbl_yhigh);
      ibws = invbwstretch(ipbl, ibws_black_stretch, ibws_white_stretch);
      bws = bwstretch(ibws, bws_black_stretch, bws_white_stretch);
      pbl = parabola(bws, pbl_base_gain, pbl_hgc, pbl_pa, pbl_pb, pbl_pc4, pbl_xlow, pbl_xhigh);
      cc_y[j] = CLAMP(((sfi_w32f15_mult(cc_y[j] - cc_x[j], scale_ver) + (pbl << 1)) + 1) >> 1, 0, ONE);
      cc_x[j] = pbl;
    }
    i++;
    j++;
  }
}

static int interpolate(int pbl, int *icc_x, int *icc_y, int icc_size)
{
  int y = pbl, i = 0;
  unsigned int delta_x, delta_y, x_tmp, y_tmp;

  if (icc_size > 2) {
    while (pbl >= icc_x[i] && i < icc_size - 1)
      ++i;

    delta_x = icc_x[i] - icc_x[i - 1];
    delta_y = icc_y[i] - icc_y[i - 1];
    x_tmp = pbl - icc_x[i - 1];
    y_tmp = icc_y[i - 1];

    y = Min((x_tmp * delta_y + (delta_x >> 1)) / delta_x + y_tmp, ONE);
  }

  return y;
}

/*
  Black Gain Limiter
*/

static const int bglimiter_alpha[201] =
{
      0,  6348,  7323,  7918,  8349,  8689,  8969,  9208,
   9417,  9602,  9768,  9919, 10058, 10185, 10304, 10415,
  10518, 10616, 10708, 10796, 10879, 10958, 11034, 11106,
  11175, 11242, 11306, 11368, 11427, 11485, 11540, 11594,
  11646, 11697, 11746, 11794, 11840, 11885, 11929, 11972,
  12014, 12055, 12095, 12134, 12172, 12209, 12245, 12281,
  12316, 12350, 12384, 12417, 12449, 12481, 12512, 12542,
  12572, 12602, 12631, 12659, 12687, 12715, 12742, 12769,
  12795, 12821, 12846, 12871, 12896, 12921, 12945, 12968,
  12992, 13015, 13038, 13060, 13082, 13104, 13126, 13147,
  13168, 13189, 13210, 13230, 13250, 13270, 13290, 13309,
  13328, 13347, 13366, 13385, 13403, 13421, 13439, 13457,
  13475, 13492, 13509, 13526, 13543, 13560, 13577, 13593,
  13609, 13625, 13641, 13657, 13673, 13688, 13704, 13719,
  13734, 13749, 13764, 13779, 13793, 13808, 13822, 13837,
  13851, 13865, 13879, 13892, 13906, 13920, 13933, 13946,
  13960, 13973, 13986, 13999, 14012, 14024, 14037, 14050,
  14062, 14075, 14087, 14099, 14111, 14123, 14135, 14147,
  14159, 14171, 14182, 14194, 14205, 14217, 14228, 14239,
  14250, 14262, 14273, 14284, 14294, 14305, 14316, 14327,
  14337, 14348, 14358, 14369, 14379, 14390, 14400, 14410,
  14420, 14430, 14440, 14450, 14460, 14470, 14480, 14489,
  14499, 14509, 14518, 14528, 14537, 14547, 14556, 14565,
  14575, 14584, 14593, 14602, 14611, 14620, 14629, 14638,
  14647, 14656, 14665, 14673, 14682, 14691, 14699, 14708,
  14716
};

static void bglimiter_initialize(struct sl_hdr_metadata *sl_hdr_metadata, int *bgl_alpha, int *bgl_is_bypassed)
{
  unsigned char Lhdr_idx = sl_hdr_metadata->hdrDisplayMaxLuminance / 50;

  *bgl_alpha = bglimiter_alpha[Lhdr_idx];
  *bgl_is_bypassed = (sl_hdr_metadata->u.variables.tmInputSignalBlackLevelOffset == 0) ? 1 : 0;
}

static int bglimiter(int pu, int cc, int bgl_is_bypassed, int bgl_alpha)
{
  enum { IMPL_SHIFT = 14 };
  enum { IMPL_HALF = 1 << (IMPL_SHIFT - 1) };
  int glim = cc;

  if (bgl_is_bypassed == 0) {
    glim = pu * bgl_alpha;
    glim += IMPL_HALF;
    glim >>= IMPL_SHIFT;
    glim = Max(glim, cc);
  }

  glim = CLAMP(glim, 0, ONE - 1);

  return glim;
}

/*
  EOTF and PQ
*/

extern unsigned short EOTFtoPQ_max_e_brightness_output[201];
extern unsigned short EOTFtoPQ_alpha_low[201];
extern unsigned short EOTFtoPQ_alpha_mid[201];
extern unsigned short EOTFtoPQ_alpha_high[201];
extern int EOTFtoPQ_quadrint_0(int x_in);
extern int EOTFtoPQ_quadrint_50(int x_in);
extern int EOTFtoPQ_quadrint_100(int x_in);
extern int EOTFtoPQ_quadrint_150(int x_in);
extern int EOTFtoPQ_quadrint_300(int x_in);
extern int EOTFtoPQ_quadrint_600(int x_in);
extern int EOTFtoPQ_quadrint_1000(int x_in);
extern int EOTFtoPQ_quadrint_3000(int x_in);
extern int EOTFtoPQ_quadrint_6000(int x_in);
extern int EOTFtoPQ_quadrint_10000(int x_in);
static int (*EOTFtoPQ_quadrint_low)(int x_in);
static int (*EOTFtoPQ_quadrint_high)(int x_in);

static void EOTFtoPQ_initialize(int TargetDisplayLuminance, unsigned short *pqY_max_e_brightness_input, unsigned short *pqY_max_e_brightness_output, unsigned short *pqY_alpha_low, unsigned short *pqY_alpha_mid, unsigned short *pqY_alpha_high, int *pqY_lower_idx, int *pqY_upper_idx)
{
  enum { NUMBER_OF_INTERVALS = 9 };
  int interval_lower_table_[NUMBER_OF_INTERVALS] = { 29, 29, 29, 29, 22, 18, 14, 13, 13 };
  int interval_upper_table_[NUMBER_OF_INTERVALS] = { 39, 39, 39, 39, 33, 27, 23, 23, 23 };
  unsigned char Ldisplay_idx = TargetDisplayLuminance / 50;

  *pqY_max_e_brightness_input = ST2084toOETF_max_e_brightness_input[Ldisplay_idx];
  *pqY_max_e_brightness_output = EOTFtoPQ_max_e_brightness_output[Ldisplay_idx];
  *pqY_alpha_low = EOTFtoPQ_alpha_low[Ldisplay_idx];
  *pqY_alpha_mid = EOTFtoPQ_alpha_mid[Ldisplay_idx];
  *pqY_alpha_high = EOTFtoPQ_alpha_high[Ldisplay_idx];

  if (Ldisplay_idx > 6000/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_10000;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_6000;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 1] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 1] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 3000/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_6000;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_3000;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 2] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 2] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 1000/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_3000;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_1000;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 3] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 3] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 600/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_1000;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_600;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 4] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 4] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 300/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_600;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_300;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 5] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 5] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 150/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_300;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_150;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 6] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 6] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 100/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_150;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_100;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 7] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 7] << (SHIFT - 6);
  }
  else if (Ldisplay_idx > 50/50) {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_100;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_50;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 8] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 8] << (SHIFT - 6);
  }
  else {
    EOTFtoPQ_quadrint_high = EOTFtoPQ_quadrint_50;
    EOTFtoPQ_quadrint_low = EOTFtoPQ_quadrint_0;
    *pqY_lower_idx = interval_lower_table_[NUMBER_OF_INTERVALS - 9] << (SHIFT - 6);
    *pqY_upper_idx = interval_upper_table_[NUMBER_OF_INTERVALS - 9] << (SHIFT - 6);
  }
}

int EOTFtoPQ(int bgl, unsigned short pqY_max_e_brightness_input, unsigned short pqY_max_e_brightness_output, unsigned short pqY_alpha_low, unsigned short pqY_alpha_mid, unsigned short pqY_alpha_high, int pqY_lower_idx, int pqY_upper_idx)
{
  enum { IMPL_SHIFT = 14 };
  enum { IMPL_ONE = (1 << IMPL_SHIFT) };
  int ylow, yhigh, pqY;

  ylow = EOTFtoPQ_quadrint_low(bgl);
  yhigh = EOTFtoPQ_quadrint_high(bgl);

  if (bgl < pqY_lower_idx)
    pqY = pqY_alpha_low * ylow + (IMPL_ONE - pqY_alpha_low) * yhigh;
  else if (bgl < pqY_upper_idx)
    pqY = pqY_alpha_mid * ylow + (IMPL_ONE - pqY_alpha_mid) * yhigh;
  else
    pqY = pqY_alpha_high * ylow + (IMPL_ONE - pqY_alpha_high) * yhigh;

  pqY = (pqY + bgl * pqY_max_e_brightness_output + (1 << (SHIFT - 1))) >> SHIFT;
  pqY = (pqY * pqY_max_e_brightness_input + (1 << IMPL_SHIFT)) >> (IMPL_SHIFT + 1);
  pqY = CLAMP(pqY, 0, (1 << 13) - 1);

  return pqY;
}

/**
 * @brief Compute the P_LUT (called once per frame)
 *
 * @param sl_hdr_metadata[in] : current metadata
 * @param TargetDisplayLuminance[in] : display brightness
 * @param P_LUT[out] : pointer to the computed P_LUT
 *
 * @return void
*/
void Compute_P_LUT(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, unsigned short *P_LUT)
{
  int i, modFactor, pu;
  /* SDR2HDR parameters */
  int icc_x[12], icc_y[12], icc_size;
  int ipbl_base_gain, ipbl_hgc, ipbl_one_div_a, ipbl_one_div_a_shift, ipbl_min_b_div_2a, ipbl_lb_b2_min_4ac_rb_div_4a2, ipbl_lb_b2_min_4ac_rb_div_4a2_shift, ipbl_ylow, ipbl_yhigh;
  int ibws_black_stretch, ibws_white_stretch;
  int ibgl_is_bypassed, ibgl_alpha;
  unsigned short sqrtY_alpha, gammaY_alpha;
  int icc, ipbl, ibws;
  /* HDR2MDR parameters */
  unsigned short pu_max_e_brightness_input, pu_alpha_low, pu_alpha_mid, pu_alpha_high;
  int pu_lower_idx, pu_upper_idx;
  int bws_black_stretch, bws_white_stretch;
  int pbl_base_gain, pbl_hgc, pbl_pa, pbl_pb, pbl_pc4, pbl_xlow, pbl_xhigh;
  int cc_x[12], cc_y[12], cc_size;
  int bgl_alpha, bgl_is_bypassed;
  unsigned short pqY_max_e_brightness_input, pqY_max_e_brightness_output, pqY_alpha_low, pqY_alpha_mid, pqY_alpha_high;
  int pqY_lower_idx, pqY_upper_idx;
  int bws, pbl, cc;

  if (!sl_hdr_metadata->payloadMode) { /* payloadMode = 0 (Parameter-based) */
    if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
      invinterpolate_initialize(sl_hdr_metadata, icc_x, icc_y, &icc_size);
      invparabola_initialize(sl_hdr_metadata, &ipbl_base_gain, &ipbl_hgc, &ipbl_one_div_a, &ipbl_one_div_a_shift, &ipbl_min_b_div_2a, &ipbl_lb_b2_min_4ac_rb_div_4a2, &ipbl_lb_b2_min_4ac_rb_div_4a2_shift, &ipbl_ylow, &ipbl_yhigh);
      invbwstretch_initialize(sl_hdr_metadata, &ibws_black_stretch, &ibws_white_stretch);
      invbglimiter_initialize(sl_hdr_metadata, &ibgl_alpha, &ibgl_is_bypassed);

      for (i = 0; i < 65; ++i) {
        /* Perceptual Uniform from Gamma */
        pu = GammatoOETF[i];

        /* Inverse Custom Curve */
        icc = invinterpolate(pu, icc_x, icc_y, icc_size);

        /* Inverse ParaBoLa */
        ipbl = invparabola(icc, ipbl_base_gain, ipbl_hgc, ipbl_one_div_a, ipbl_one_div_a_shift, ipbl_min_b_div_2a, ipbl_lb_b2_min_4ac_rb_div_4a2, ipbl_lb_b2_min_4ac_rb_div_4a2_shift, ipbl_ylow, ipbl_yhigh);

        /* Inverse Black & White Stretch */
        ibws = invbwstretch(ipbl, ibws_black_stretch, ibws_white_stretch);

        /* Inverse Black Gain Limiter */
        P_LUT[i] = invbglimiter(pu, ibws, ibgl_is_bypassed, ibgl_alpha);
      }
    }
    else { /* HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) */
      ST2084toOETF_initialize(sl_hdr_metadata, &pu_max_e_brightness_input, &pu_alpha_low, &pu_alpha_mid, &pu_alpha_high, &pu_lower_idx, &pu_upper_idx);

      for (i = 0; i < 65; ++i) {
        /* Perceptual Uniform from ST2084 */
        P_LUT[i] = ST2084toOETF(i, pu_max_e_brightness_input, pu_alpha_low, pu_alpha_mid, pu_alpha_high, pu_lower_idx, pu_upper_idx);
      }
    }

    if (sl_hdr_metadata->partID == 2 || /* HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) */
        TargetDisplayLuminance != sl_hdr_metadata->hdrDisplayMaxLuminance) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
      bwstretch_initialize(sl_hdr_metadata, TargetDisplayLuminance, &bws_black_stretch, &bws_white_stretch);
      parabola_initialize(sl_hdr_metadata, TargetDisplayLuminance, &pbl_base_gain, &pbl_hgc, &pbl_pa, &pbl_pb, &pbl_pc4, &pbl_xlow, &pbl_xhigh);
      interpolate_initialize(sl_hdr_metadata, TargetDisplayLuminance, cc_x, cc_y, &cc_size);
      bglimiter_initialize(sl_hdr_metadata, &bgl_alpha, &bgl_is_bypassed);

      for (i = 0; i < 65; ++i) {
        /* Perceptual Uniform */
        pu = P_LUT[i];

        /* Black & white Stretch */
        bws = bwstretch(pu, bws_black_stretch, bws_white_stretch);

        /* ParaBoLa */
        pbl = parabola(bws, pbl_base_gain, pbl_hgc, pbl_pa, pbl_pb, pbl_pc4, pbl_xlow, pbl_xhigh);

        /* Custom Curve */
        cc = interpolate(pbl, cc_x, cc_y, cc_size);

        /* Black Gain Limiter */
        P_LUT[i] = bglimiter(pu, cc, bgl_is_bypassed, bgl_alpha);
      }
    }

    if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
      if (sl_hdr_metadata->kCoefficient[0] == 0 && sl_hdr_metadata->kCoefficient[1] == 0 && sl_hdr_metadata->kCoefficient[2] == 0) { /* EOTF and Gamma 2.4 */
        EOTFtoGamma_initialize(TargetDisplayLuminance, &gammaY_alpha);
        for (i = 0; i < 65; ++i)
          P_LUT[i] = EOTFtoGamma(P_LUT[i], gammaY_alpha);
      }
      else { /* EOTF and Gamma 2.0 */
        EOTFtoSqrtGamma_initialize(sl_hdr_metadata, TargetDisplayLuminance, &modFactor, &sqrtY_alpha, &gammaY_alpha);
        for (i = 0; i < 65; ++i)
          P_LUT[i] = EOTFtoSqrtGamma(P_LUT[i], modFactor, sqrtY_alpha, gammaY_alpha);
      }
    }
    else { /* HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) */
      EOTFtoPQ_initialize(TargetDisplayLuminance, &pqY_max_e_brightness_input, &pqY_max_e_brightness_output, &pqY_alpha_low, &pqY_alpha_mid, &pqY_alpha_high, &pqY_lower_idx, &pqY_upper_idx);

      for (i = 0; i < 65; ++i) {
        /* EOTF and PQ */
        P_LUT[i] = EOTFtoPQ(P_LUT[i], pqY_max_e_brightness_input, pqY_max_e_brightness_output, pqY_alpha_low, pqY_alpha_mid, pqY_alpha_high, pqY_lower_idx, pqY_upper_idx);
      }
    }
  }
  else { /* payloadMode = 1 (Table-based) */
    if ((sl_hdr_metadata->partID == 1 && TargetDisplayLuminance != sl_hdr_metadata->hdrDisplayMaxLuminance) ||
        (sl_hdr_metadata->partID == 2 && TargetDisplayLuminance != sdrDisplayLuminance)) {
      return;
    }

    for (i = 0; i < 65; i++) {
      P_LUT[i] = sl_hdr_metadata->u.tables.luminanceMappingY[i];
      P_LUT[i] = CLAMP((short)P_LUT[i], 0, (1 << 13) - 1);
    }
  }
}
