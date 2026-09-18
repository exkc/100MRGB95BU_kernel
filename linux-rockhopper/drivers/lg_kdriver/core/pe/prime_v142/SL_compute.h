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
 * @file SL_compute.h
 *
 * @section DESCRIPTION
 * Fill metadata with recovery mode values
 * Compute C_LUT, P_LUT, Range, mu0 / mu1 and OCT<br>
*/

#ifndef SL_compute_H
#define SL_compute_H
 
#include "SL_common.h"

void Fill_MetadataRecovery(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int colour_primaries, int transfer_characteristics);
void Compute_LUTs(struct sl_hdr_metadata *sl_hdr_metadata, int TargetDisplayLuminance, int yuv_range, unsigned short *mu0, unsigned short *mu1, int *OCT, unsigned short *C_LUT, unsigned short *P_LUT, int *inv_y_ratio, int *inv_chroma_ratio, int *footroom, int *l_headroom, int *c_headroom);

#endif /* SL_compute_H */
