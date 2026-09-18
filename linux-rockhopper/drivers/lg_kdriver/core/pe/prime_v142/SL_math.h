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
 * @file SL_math.h
 *
 * @section DESCRIPTION
 * math functions<br>
*/

#ifndef SL_MATH_H
#define SL_MATH_H


#define ABS(x) ((x >= 0) ? x : -(x))

/******************************************************************************
 * Find the most significant bit position
 ******************************************************************************/

int msb32(unsigned int argx);

/******************************************************************************
 * Integer square root
 ******************************************************************************/

unsigned int sqrt16(unsigned int argx);

/******************************************************************************
 * Signed Fixed-point Integer (SFI) math implementation
 * with width W=32 bit and fraction F=15 bit both fixed
 ******************************************************************************/

/* Multiplication */
int sfi_w32f15_mult(int lhs_arg, int rhs_arg);

/* Division */
int sfi_w32f15_div(int lhs_arg, int rhs_arg);

/* Exponential function */
int sfi_w32f15_exp(int argx);

/* Natural logarithm function */
int sfi_w32f15_log(int argx);

#endif /* SL_MATH_H */
