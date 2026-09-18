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
 * @file SL_static_LUT_fill.h
 *
 * @section DESCRIPTION
 * Fill D_LUT<br>
*/

#ifndef SL_static_LUT_fill_H
#define SL_static_LUT_fill_H
 
#include "SL_common.h"

void Fill_D_LUT(struct sl_hdr_metadata *sl_hdr_metadata, int curve, int TargetDisplayLuminance, unsigned short *D_LUT, unsigned short *D_LUT_THRESHOLD, unsigned short *D_LUT_STEP);

void Fill_S_LUT(unsigned short *LUT);

void Fill_I_LUT(unsigned short *LUT);

#endif // SL_static_LUT_fill_H
