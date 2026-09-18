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
 * @file SL_static_LUT_fill.c
 *
 * @section DESCRIPTION
 * Fill D_LUT<br>
*/

#include "SL_common.h"

#ifdef PE_PRIME_V142
#else
#include <stdio.h>
#include <string.h>
#endif

#include "SL_static_LUT_fill.h"

/* S_LUT */
static unsigned short S_LUT[65] = {
  #include "S_LUT.lut"
};

/* I_LUT */
static unsigned short I_LUT[65] = {
  #include "I_LUT.lut"
};

/* D_LUT BT1886 */
static unsigned short D_LUT_SDRCL2HDR_BT1886[65] = {
  #include "D_LUT_SDRCL2HDR_BT1886.lut"
};
static unsigned short D_LUT_SDRCL2HDR_BT1886_STEP[4] = {
  #include "D_LUT_SDRCL2HDR_BT1886_STEP.lut"
};
static unsigned short D_LUT_SDRCL2HDR_BT1886_THRESHOLD[3] = {
  #include "D_LUT_SDRCL2HDR_BT1886_THRESHOLD.lut"
};

static unsigned short D_LUT_SDRNCL2HDR_BT1886[65] = {
  #include "D_LUT_SDRNCL2HDR_BT1886.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_BT1886_STEP[4] = {
  #include "D_LUT_SDRNCL2HDR_BT1886_STEP.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_BT1886_THRESHOLD[3] = {
  #include "D_LUT_SDRNCL2HDR_BT1886_THRESHOLD.lut"
};

static unsigned short D_LUT_HDR2MDR_BT1886_100[65] = {
  #include "D_LUT_HDR2MDR_BT1886_100.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_150[65] = {
  #include "D_LUT_HDR2MDR_BT1886_150.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_250[65] = {
  #include "D_LUT_HDR2MDR_BT1886_250.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_400[65] = {
  #include "D_LUT_HDR2MDR_BT1886_400.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_550[65] = {
  #include "D_LUT_HDR2MDR_BT1886_550.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_700[65] = {
  #include "D_LUT_HDR2MDR_BT1886_700.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_850[65] = {
  #include "D_LUT_HDR2MDR_BT1886_700.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_1000[65] = {
  #include "D_LUT_HDR2MDR_BT1886_1000.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_1250[65] = {
  #include "D_LUT_HDR2MDR_BT1886_1250.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_1500[65] = {
  #include "D_LUT_HDR2MDR_BT1886_1500.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_1750[65] = {
  #include "D_LUT_HDR2MDR_BT1886_1750.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_2000[65] = {
  #include "D_LUT_HDR2MDR_BT1886_2000.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_2500[65] = {
  #include "D_LUT_HDR2MDR_BT1886_2500.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_3000[65] = {
  #include "D_LUT_HDR2MDR_BT1886_3000.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_3500[65] = {
  #include "D_LUT_HDR2MDR_BT1886_3500.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_4000[65] = {
  #include "D_LUT_HDR2MDR_BT1886_4000.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_5000[65] = {
  #include "D_LUT_HDR2MDR_BT1886_5000.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_STEP[4] = {
  #include "D_LUT_HDR2MDR_BT1886_STEP.lut"
};
static unsigned short D_LUT_HDR2MDR_BT1886_THRESHOLD[3] = {
  #include "D_LUT_HDR2MDR_BT1886_THRESHOLD.lut"
};

/* D_LUT PQ */
static unsigned short D_LUT_SDRCL2HDR_PQ_100[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_100.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_150[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_150.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_250[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_250.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_400[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_400.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_550[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_550.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_700[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_700.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_850[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_850.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_1000[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_1000.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_1250[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_1250.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_1500[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_1500.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_1750[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_1750.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_2000[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_2000.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_2500[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_2500.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_3000[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_3000.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_3500[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_3500.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_4000[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_4000.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_5000[65] = {
  #include "D_LUT_SDRCL2HDR_PQ_5000.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_STEP[4] = {
  #include "D_LUT_SDRCL2HDR_PQ_STEP.lut"
};
static unsigned short D_LUT_SDRCL2HDR_PQ_THRESHOLD[3] = {
  #include "D_LUT_SDRCL2HDR_PQ_THRESHOLD.lut"
};

static unsigned short D_LUT_SDRNCL2HDR_PQ_100[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_100.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_150[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_150.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_250[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_250.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_400[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_400.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_550[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_550.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_700[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_700.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_850[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_850.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_1000[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_1000.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_1250[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_1250.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_1500[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_1500.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_1750[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_1750.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_2000[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_2000.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_2500[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_2500.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_3000[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_3000.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_3500[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_3500.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_4000[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_4000.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_5000[65] = {
  #include "D_LUT_SDRNCL2HDR_PQ_5000.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_STEP[4] = {
  #include "D_LUT_SDRNCL2HDR_PQ_STEP.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_PQ_THRESHOLD[3] = {
  #include "D_LUT_SDRNCL2HDR_PQ_THRESHOLD.lut"
};

static unsigned short D_LUT_HDR2MDR_PQ_100[65] = {
  #include "D_LUT_HDR2MDR_PQ_100.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_150[65] = {
  #include "D_LUT_HDR2MDR_PQ_150.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_250[65] = {
  #include "D_LUT_HDR2MDR_PQ_250.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_400[65] = {
  #include "D_LUT_HDR2MDR_PQ_400.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_550[65] = {
  #include "D_LUT_HDR2MDR_PQ_550.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_700[65] = {
  #include "D_LUT_HDR2MDR_PQ_700.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_850[65] = {
  #include "D_LUT_HDR2MDR_PQ_850.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_1000[65] = {
  #include "D_LUT_HDR2MDR_PQ_1000.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_1250[65] = {
  #include "D_LUT_HDR2MDR_PQ_1250.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_1500[65] = {
  #include "D_LUT_HDR2MDR_PQ_1500.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_1750[65] = {
  #include "D_LUT_HDR2MDR_PQ_1750.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_2000[65] = {
  #include "D_LUT_HDR2MDR_PQ_2000.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_2500[65] = {
  #include "D_LUT_HDR2MDR_PQ_2500.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_3000[65] = {
  #include "D_LUT_HDR2MDR_PQ_3000.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_3500[65] = {
  #include "D_LUT_HDR2MDR_PQ_3500.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_4000[65] = {
  #include "D_LUT_HDR2MDR_PQ_4000.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_5000[65] = {
  #include "D_LUT_HDR2MDR_PQ_5000.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_STEP[4] = {
  #include "D_LUT_HDR2MDR_PQ_STEP.lut"
};
static unsigned short D_LUT_HDR2MDR_PQ_THRESHOLD[3] = {
  #include "D_LUT_HDR2MDR_PQ_THRESHOLD.lut"
};

/* D_LUT LINEAR */
static unsigned short D_LUT_SDRCL2HDR_LINEAR[65] = {
  #include "D_LUT_SDRCL2HDR_LINEAR.lut"
};
static unsigned short D_LUT_SDRCL2HDR_LINEAR_STEP[4] = {
  #include "D_LUT_SDRCL2HDR_LINEAR_STEP.lut"
};
static unsigned short D_LUT_SDRCL2HDR_LINEAR_THRESHOLD[3] = {
  #include "D_LUT_SDRCL2HDR_LINEAR_THRESHOLD.lut"
};

static unsigned short D_LUT_SDRNCL2HDR_LINEAR[65] = {
  #include "D_LUT_SDRNCL2HDR_LINEAR.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_LINEAR_STEP[4] = {
  #include "D_LUT_SDRNCL2HDR_LINEAR_STEP.lut"
};
static unsigned short D_LUT_SDRNCL2HDR_LINEAR_THRESHOLD[3] = {
  #include "D_LUT_SDRNCL2HDR_LINEAR_THRESHOLD.lut"
};

static unsigned short D_LUT_HDR2MDR_LINEAR_100[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_100.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_150[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_150.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_250[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_250.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_400[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_400.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_550[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_550.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_700[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_700.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_850[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_850.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_1000[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_1000.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_1250[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_1250.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_1500[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_1500.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_1750[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_1750.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_2000[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_2000.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_2500[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_2500.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_3000[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_3000.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_3500[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_3500.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_4000[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_4000.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_5000[65] = {
  #include "D_LUT_HDR2MDR_LINEAR_5000.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_STEP[4] = {
  #include "D_LUT_HDR2MDR_LINEAR_STEP.lut"
};
static unsigned short D_LUT_HDR2MDR_LINEAR_THRESHOLD[3] = {
  #include "D_LUT_HDR2MDR_LINEAR_THRESHOLD.lut"
};

/**
 * @brief Filling method for the D_LUT depending on the screen Gamma characteristic
 *
 * @param sl_hdr_metadata[in] : current metadata
 * @param curve[in] : OETF
 * @param TargetDisplayLuminance[in] : display brightness
 * @param D_LUT[out] : pointer to the computed D_LUT
 * @param D_LUT_THRESHOLD[out] : pointer to the D_LUT_THRESHOLD
 * @param D_LUT_STEP[out] : pointer to the D_LUT_STEP
 *
 * @return Void
*/
void Fill_D_LUT(struct sl_hdr_metadata *sl_hdr_metadata, int curve, int TargetDisplayLuminance, unsigned short *D_LUT, unsigned short *D_LUT_THRESHOLD, unsigned short *D_LUT_STEP)
{
  int i, mapy_cl, modFactor;
  unsigned short D_LUT_LOW[65], D_LUT_HIGH[65];

  if (sl_hdr_metadata->kCoefficient[0] == 0 && sl_hdr_metadata->kCoefficient[1] == 0 && sl_hdr_metadata->kCoefficient[2] == 0)
    mapy_cl = 0;
  else
    mapy_cl = 1;

  switch (curve) {
    case BT1886:
      if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
        if (mapy_cl) {
          memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_BT1886, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_BT1886, 65 * sizeof(unsigned short));
          if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance) {
            modFactor = (((TargetDisplayLuminance - 100) << 8) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
            for (i = 0; i < 65; i++)
              D_LUT[i] = D_LUT_LOW[i] + ((modFactor * (D_LUT_HIGH[i] - D_LUT_LOW[i]) + 128) >> 8);
          }
          else {
            for (i = 0; i < 65; i++)
              D_LUT[i] = D_LUT_HIGH[i];
          }
          memcpy(D_LUT_STEP, D_LUT_SDRCL2HDR_BT1886_STEP, 4 * sizeof(unsigned short));
          memcpy(D_LUT_THRESHOLD, D_LUT_SDRCL2HDR_BT1886_THRESHOLD, 3 * sizeof(unsigned short));
        }
        else {
          memcpy(D_LUT, D_LUT_SDRNCL2HDR_BT1886, 65 * sizeof(unsigned short));
          memcpy(D_LUT_STEP, D_LUT_SDRNCL2HDR_BT1886_STEP, 4 * sizeof(unsigned short));
          memcpy(D_LUT_THRESHOLD, D_LUT_SDRNCL2HDR_BT1886_THRESHOLD, 3 * sizeof(unsigned short));
        }
      }
      else {
        switch (TargetDisplayLuminance) {
          case 100: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_100, 65 * sizeof(unsigned short)); break;
          case 150: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_150, 65 * sizeof(unsigned short)); break;
          case 250: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_250, 65 * sizeof(unsigned short)); break;
          case 400: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_400, 65 * sizeof(unsigned short)); break;
          case 550: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_550, 65 * sizeof(unsigned short)); break;
          case 700: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_700, 65 * sizeof(unsigned short)); break;
          case 850: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_850, 65 * sizeof(unsigned short)); break;
          case 1000: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_1000, 65 * sizeof(unsigned short)); break;
          case 1250: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_1250, 65 * sizeof(unsigned short)); break;
          case 1500: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_1500, 65 * sizeof(unsigned short)); break;
          case 1750: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_1750, 65 * sizeof(unsigned short)); break;
          case 2000: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_2000, 65 * sizeof(unsigned short)); break;
          case 2500: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_2500, 65 * sizeof(unsigned short)); break;
          case 3000: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_3000, 65 * sizeof(unsigned short)); break;
          case 3500: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_3500, 65 * sizeof(unsigned short)); break;
          case 4000: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_4000, 65 * sizeof(unsigned short)); break;
          case 5000: memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_5000, 65 * sizeof(unsigned short)); break;
          default:
		  	memcpy(D_LUT, D_LUT_HDR2MDR_BT1886_850, 65 * sizeof(unsigned short));
            PE_PRINT_NOTI("0.Can only handle peak luminance from 100 to 5000 nits(%d)\n",TargetDisplayLuminance);
            break;
        }
        memcpy(D_LUT_STEP, D_LUT_HDR2MDR_BT1886_STEP, 4 * sizeof(unsigned short));
        memcpy(D_LUT_THRESHOLD, D_LUT_HDR2MDR_BT1886_THRESHOLD, 3 * sizeof(unsigned short));
      }
      break;
    case PQ:
      if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
        if (mapy_cl) {
          switch (TargetDisplayLuminance) {
            case 100: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_100, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_100, 65 * sizeof(unsigned short)); break;
            case 150: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_150, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_150, 65 * sizeof(unsigned short)); break;
            case 250: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_250, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_250, 65 * sizeof(unsigned short)); break;
            case 400: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_400, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_400, 65 * sizeof(unsigned short)); break;
            case 550: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_550, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_550, 65 * sizeof(unsigned short)); break;
            case 700: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_700, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_700, 65 * sizeof(unsigned short)); break;
            case 850: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_850, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_850, 65 * sizeof(unsigned short)); break;
            case 1000: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_1000, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_1000, 65 * sizeof(unsigned short)); break;
            case 1250: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_1250, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_1250, 65 * sizeof(unsigned short)); break;
            case 1500: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_1500, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_1500, 65 * sizeof(unsigned short)); break;
            case 1750: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_1750, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_1750, 65 * sizeof(unsigned short)); break;
            case 2000: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_2000, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_2000, 65 * sizeof(unsigned short)); break;
            case 2500: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_2500, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_2500, 65 * sizeof(unsigned short)); break;
            case 3000: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_3000, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_3000, 65 * sizeof(unsigned short)); break;
            case 3500: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_3500, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_3500, 65 * sizeof(unsigned short)); break;
            case 4000: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_4000, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_4000, 65 * sizeof(unsigned short)); break;
            case 5000: memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_5000, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_5000, 65 * sizeof(unsigned short)); break;
            default:
			  memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_PQ_850, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_PQ_850, 65 * sizeof(unsigned short));
              PE_PRINT_NOTI("1.Can only handle peak luminance from 100 to 5000 nits(%d)\n",TargetDisplayLuminance);
              break;
          }
          if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance) {
            modFactor = (((TargetDisplayLuminance - 100) << 8) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
            for (i = 0; i < 65; i++)
              D_LUT[i] = D_LUT_LOW[i] + ((modFactor * (D_LUT_HIGH[i] - D_LUT_LOW[i]) + 128) >> 8);
          }
          else {
            for (i = 0; i < 65; i++)
              D_LUT[i] = D_LUT_HIGH[i];
          }
          memcpy(D_LUT_STEP, D_LUT_SDRCL2HDR_PQ_STEP, 4 * sizeof(unsigned short));
          memcpy(D_LUT_THRESHOLD, D_LUT_SDRCL2HDR_PQ_THRESHOLD, 3 * sizeof(unsigned short));
        }
        else {
          switch (TargetDisplayLuminance) {
            case 100: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_100, 65 * sizeof(unsigned short)); break;
            case 150: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_150, 65 * sizeof(unsigned short)); break;
            case 250: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_250, 65 * sizeof(unsigned short)); break;
            case 400: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_400, 65 * sizeof(unsigned short)); break;
            case 550: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_550, 65 * sizeof(unsigned short)); break;
            case 700: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_700, 65 * sizeof(unsigned short)); break;
            case 850: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_850, 65 * sizeof(unsigned short)); break;
            case 1000: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_1000, 65 * sizeof(unsigned short)); break;
            case 1250: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_1250, 65 * sizeof(unsigned short)); break;
            case 1500: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_1500, 65 * sizeof(unsigned short)); break;
            case 1750: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_1750, 65 * sizeof(unsigned short)); break;
            case 2000: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_2000, 65 * sizeof(unsigned short)); break;
            case 2500: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_2500, 65 * sizeof(unsigned short)); break;
            case 3000: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_3000, 65 * sizeof(unsigned short)); break;
            case 3500: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_3500, 65 * sizeof(unsigned short)); break;
            case 4000: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_4000, 65 * sizeof(unsigned short)); break;
            case 5000: memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_5000, 65 * sizeof(unsigned short)); break;
            default:
			  memcpy(D_LUT, D_LUT_SDRNCL2HDR_PQ_850, 65 * sizeof(unsigned short));
              PE_PRINT_NOTI("2.Can only handle peak luminance from 100 to 5000 nits(%d)\n",TargetDisplayLuminance);
              break;
          }
          memcpy(D_LUT_STEP, D_LUT_SDRNCL2HDR_PQ_STEP, 4 * sizeof(unsigned short));
          memcpy(D_LUT_THRESHOLD, D_LUT_SDRNCL2HDR_PQ_THRESHOLD, 3 * sizeof(unsigned short));
        }
      }
      else {
        switch (TargetDisplayLuminance) {
          case 100: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_100, 65 * sizeof(unsigned short)); break;
          case 150: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_150, 65 * sizeof(unsigned short)); break;
          case 250: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_250, 65 * sizeof(unsigned short)); break;
          case 400: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_400, 65 * sizeof(unsigned short)); break;
          case 550: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_550, 65 * sizeof(unsigned short)); break;
          case 700: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_700, 65 * sizeof(unsigned short)); break;
          case 850: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_850, 65 * sizeof(unsigned short)); break;
          case 1000: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_1000, 65 * sizeof(unsigned short)); break;
          case 1250: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_1250, 65 * sizeof(unsigned short)); break;
          case 1500: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_1500, 65 * sizeof(unsigned short)); break;
          case 1750: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_1750, 65 * sizeof(unsigned short)); break;
          case 2000: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_2000, 65 * sizeof(unsigned short)); break;
          case 2500: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_2500, 65 * sizeof(unsigned short)); break;
          case 3000: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_3000, 65 * sizeof(unsigned short)); break;
          case 3500: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_3500, 65 * sizeof(unsigned short)); break;
          case 4000: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_4000, 65 * sizeof(unsigned short)); break;
          case 5000: memcpy(D_LUT, D_LUT_HDR2MDR_PQ_5000, 65 * sizeof(unsigned short)); break;
          default:
		  	memcpy(D_LUT, D_LUT_HDR2MDR_PQ_850, 65 * sizeof(unsigned short));
            PE_PRINT_NOTI("3.Can only handle peak luminance from 100 to 5000 nits(%d)\n",TargetDisplayLuminance);
            break;
        }
        memcpy(D_LUT_STEP, D_LUT_HDR2MDR_PQ_STEP, 4 * sizeof(unsigned short));
        memcpy(D_LUT_THRESHOLD, D_LUT_HDR2MDR_PQ_THRESHOLD, 3 * sizeof(unsigned short));
      }
      break;
    case LINEAR:
      if (sl_hdr_metadata->partID == 1) { /* SDR2MDR (VUI transfer_characteristics = ITU-R BT.709) */
        if (mapy_cl) {
          memcpy(D_LUT_LOW, D_LUT_SDRNCL2HDR_LINEAR, 65 * sizeof(unsigned short)); memcpy(D_LUT_HIGH, D_LUT_SDRCL2HDR_LINEAR, 65 * sizeof(unsigned short));
          if (TargetDisplayLuminance <= sl_hdr_metadata->hdrDisplayMaxLuminance) {
            modFactor = (((TargetDisplayLuminance - 100) << 8) + ((sl_hdr_metadata->hdrDisplayMaxLuminance - 100) >> 1)) / (sl_hdr_metadata->hdrDisplayMaxLuminance - 100);
            for (i = 0; i < 65; i++)
              D_LUT[i] = D_LUT_LOW[i] + ((modFactor * (D_LUT_HIGH[i] - D_LUT_LOW[i]) + 128) >> 8);
          }
          else {
            for (i = 0; i < 65; i++)
              D_LUT[i] = D_LUT_HIGH[i];
          }
          memcpy(D_LUT_STEP, D_LUT_SDRCL2HDR_LINEAR_STEP, 4 * sizeof(unsigned short));
          memcpy(D_LUT_THRESHOLD, D_LUT_SDRCL2HDR_LINEAR_THRESHOLD, 3 * sizeof(unsigned short));
        }
        else {
          memcpy(D_LUT, D_LUT_SDRNCL2HDR_LINEAR, 65 * sizeof(unsigned short));
          memcpy(D_LUT_STEP, D_LUT_SDRNCL2HDR_LINEAR_STEP, 4 * sizeof(unsigned short));
          memcpy(D_LUT_THRESHOLD, D_LUT_SDRNCL2HDR_LINEAR_THRESHOLD, 3 * sizeof(unsigned short));
        }
      }
      else {
        switch (TargetDisplayLuminance) {
          case 100: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_100, 65 * sizeof(unsigned short)); break;
          case 150: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_150, 65 * sizeof(unsigned short)); break;
          case 250: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_250, 65 * sizeof(unsigned short)); break;
          case 400: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_400, 65 * sizeof(unsigned short)); break;
          case 550: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_550, 65 * sizeof(unsigned short)); break;
          case 700: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_700, 65 * sizeof(unsigned short)); break;
          case 850: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_850, 65 * sizeof(unsigned short)); break;
          case 1000: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_1000, 65 * sizeof(unsigned short)); break;
          case 1250: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_1250, 65 * sizeof(unsigned short)); break;
          case 1500: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_1500, 65 * sizeof(unsigned short)); break;
          case 1750: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_1750, 65 * sizeof(unsigned short)); break;
          case 2000: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_2000, 65 * sizeof(unsigned short)); break;
          case 2500: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_2500, 65 * sizeof(unsigned short)); break;
          case 3000: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_3000, 65 * sizeof(unsigned short)); break;
          case 3500: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_3500, 65 * sizeof(unsigned short)); break;
          case 4000: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_4000, 65 * sizeof(unsigned short)); break;
          case 5000: memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_5000, 65 * sizeof(unsigned short)); break;
          default:
		  	memcpy(D_LUT, D_LUT_HDR2MDR_LINEAR_850, 65 * sizeof(unsigned short));
            PE_PRINT_NOTI("4.Can only handle peak luminance from 100 to 5000 nits(%d)\n",TargetDisplayLuminance);
            break;
        }
        memcpy(D_LUT_STEP, D_LUT_HDR2MDR_LINEAR_STEP, 4 * sizeof(unsigned short));
        memcpy(D_LUT_THRESHOLD, D_LUT_HDR2MDR_LINEAR_THRESHOLD, 3 * sizeof(unsigned short));
      }
      break;
    default:
      PE_PRINT_NOTI("curve not handled(%d)\n",curve);
      break;
  }
}

/**
* @brief Load content of the S_LUT.lut file into the memory.
*
* @param LUT : pointer to the LUT
*
* @return void
*
*/
void Fill_S_LUT(unsigned short *LUT)
{
  memcpy(LUT, S_LUT, 65 * sizeof(unsigned short));
}

/**
* @brief Load content of the I_LUT.lut file into the memory.
*
* @param LUT : pointer to the LUT
*
* @return void
*
*/
void Fill_I_LUT(unsigned short *LUT)
{
  memcpy(LUT, I_LUT, 65 * sizeof(unsigned short));
}
