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

#include "SL_math.h"
#include "SL_common.h"

/******************************************************************************
 * Find the most significant bit position
 ******************************************************************************/

int msb32(unsigned int argx)
{
  int val[16] = { 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4 };
  unsigned int x = argx;
  int r = 0;

  if (x & 0xFFFF0000) {
    r += 16 / 1;
    x >>= 16 / 1;
  }
  if (x & 0x0000FF00) {
    r += 16 / 2;
    x >>= 16 / 2;
  }
  if (x & 0x000000F0) {
    r += 16 / 4;
    x >>= 16 / 4;
  }

  return r + val[x];
}

/******************************************************************************
 * Integer square root
 ******************************************************************************/

unsigned int sqrt16(unsigned int argx)
{
  unsigned short op  = 1 << 15;
  unsigned int res = 1 << 15;

  for (;;) {
    if ((res*res) > argx)
      res = res ^ op;

    op >>= 1;

    if (op == 0)
      return res + ((argx - res * res) > res ? 1 : 0);

    res = res | op;
  }

  return res;
}

/******************************************************************************
 * Signed Fixed-point Integer (SFI) math implementation
 * with width W=32 bit and fraction F=15 bit both fixed
 ******************************************************************************/

enum { FIXED_RESOLUTION_SHIFT = 15 };
enum { BIT_DEPTH = 32 };
enum { HALF_BIT_DEPTH = (BIT_DEPTH >> 1) };
enum { HALF_BIT_DEPTH_MASK = (1L << HALF_BIT_DEPTH) - 1 };
enum { MAX_POWER = BIT_DEPTH - 1 - FIXED_RESOLUTION_SHIFT };

/* Multiplication */
int sfi_w32f15_mult(int lhs_arg, int rhs_arg)
{
  unsigned int lhs = lhs_arg >= 0 ? lhs_arg : -lhs_arg;
  unsigned int lhs_high = lhs >> HALF_BIT_DEPTH;
  unsigned int lhs_low = lhs & HALF_BIT_DEPTH_MASK;
  unsigned int rhs = rhs_arg >= 0 ? rhs_arg : -rhs_arg;
  unsigned int rhs_high = rhs >> HALF_BIT_DEPTH;
  unsigned int rhs_low = rhs & HALF_BIT_DEPTH_MASK;
  int negative = (lhs_arg >= 0) ^ (rhs_arg >= 0);
  unsigned int temp, s0, s1, s2, s3, carry, res;

  temp = lhs_low * rhs_low;
  s0 = temp & HALF_BIT_DEPTH_MASK;
  temp = lhs_high * rhs_low + (temp >> HALF_BIT_DEPTH);
  s1 = temp & HALF_BIT_DEPTH_MASK;
  s2 = temp >> HALF_BIT_DEPTH;
  temp = s1 + lhs_low * rhs_high;
  s1 = temp & HALF_BIT_DEPTH_MASK;
  temp = s2 + lhs_high * rhs_high + (temp >> HALF_BIT_DEPTH);
  s2 = temp & HALF_BIT_DEPTH_MASK;
  s3 = temp >> HALF_BIT_DEPTH;
  temp = (s1 << 16) | s0;
  carry = (s3 << 16) | s2;

  res = ((carry & ((1 << FIXED_RESOLUTION_SHIFT) - 1)) << (32 - FIXED_RESOLUTION_SHIFT)) | (temp >> FIXED_RESOLUTION_SHIFT);

  /* Check overflow condition */
  if ((carry & ~((1 << FIXED_RESOLUTION_SHIFT) - 1)) || (res > INT32_MAX))
    return negative ? INT32_MIN : INT32_MAX;
  else {
    /* Apply rounding */
    res += temp & (1 << (FIXED_RESOLUTION_SHIFT - 1)) ? 1 : 0;

    /* Check overflow condition */
    if (res > INT32_MAX)
      return negative ? INT32_MIN : INT32_MAX;
    else
      return negative ? -(int)res : (int)res;
  }
}

/* Division */
int sfi_w32f15_div(int lhs_arg, int rhs_arg)
{
  unsigned int lhs = lhs_arg < 0 ? -lhs_arg : lhs_arg;
  unsigned int rhs = rhs_arg < 0 ? -rhs_arg : rhs_arg;
  int negative = (lhs_arg > 0) ^ (rhs_arg > 0);
  unsigned int remainder, r, quotient, q, res, i = FIXED_RESOLUTION_SHIFT;

  if (!rhs_arg)
    return lhs_arg > 0 ? INT32_MAX : INT32_MIN;
  else if (!lhs_arg)
    return 0;
  else {
    if (lhs < rhs) {
      quotient = 0;
      remainder = lhs;
    }
    else {
      quotient = lhs / rhs;
      remainder = lhs % rhs;

      if (quotient >= (1 << (8 * sizeof(int) - FIXED_RESOLUTION_SHIFT-1)))
        return negative ? INT32_MIN : INT32_MAX;
    }

    r = remainder;
    q = 0;
    res = quotient << FIXED_RESOLUTION_SHIFT;

    for (; i > 0; --i) {
      q <<= 1;
      if (r) {
        r <<= 1;
        if ((int)(r - rhs) >= 0) {
          q |= 1;
          r = r - rhs;
        }
      }
    }

    res |= q;

    if ((int)((r << 1) - rhs) >= 0)
      ++res;

    return negative ? -(int)res : (int)res;
  }
}

static const int log_two_power_n_reversed_[MAX_POWER] = { 363409, 340696, 317983, 295270, 272557, 249844, 227130, 204417, 181704, 158991, 136278, 113565, 90852, 68139, 45426, 22713 };
static const int log_one_plus_two_power_minus_n_[FIXED_RESOLUTION_SHIFT] = { 13286, 7312, 3860, 1987, 1008, 508, 255, 128, 64, 32, 16, 8, 4, 2, 1 };
static const int log_one_over_one_minus_two_power_minus_n_[FIXED_RESOLUTION_SHIFT] = { 22713, 9427, 4376, 2115, 1040, 516, 257, 128, 64, 32, 16, 8, 4, 2, 1 };

/* Exponential function */
int sfi_w32f15_exp (int argx)
{
  int x = argx;
  short power;
  const int *log_entry;
  int res = 1L << FIXED_RESOLUTION_SHIFT;

  if (x >= log_two_power_n_reversed_[0])
    return INT32_MAX;

  if (x < -log_two_power_n_reversed_[BIT_DEPTH - 1 - 2 * FIXED_RESOLUTION_SHIFT])
    return 0;

  if (!x)
    return res;

  if (x > 0) {
    power = MAX_POWER;
    log_entry = log_two_power_n_reversed_;

    while (x && power > (-(short)FIXED_RESOLUTION_SHIFT)) {
      while (!power || (x < *log_entry)) {
        if (!power)
          log_entry = log_one_plus_two_power_minus_n_;
        else
          ++log_entry;
        --power;
      }

      x -= *log_entry;

      if (power < 0)
        res += (res >> (-power));
      else
        res <<= power;
    }
  }
  else {
    power = FIXED_RESOLUTION_SHIFT;
    log_entry = log_two_power_n_reversed_ + (MAX_POWER - power);

    while (x && power > -FIXED_RESOLUTION_SHIFT) {
      while(!power || (x > (-*log_entry))) {
        if (!power)
          log_entry = log_one_over_one_minus_two_power_minus_n_;
        else
          ++log_entry;
        --power;
      }

      x += *log_entry;

      if (power < 0)
        res -= (res >> (-power));
      else
        res >>= power;
    }
  }

  return res;
}

/* Natural logarithm function */
int sfi_w32f15_log (int argx)
{
  unsigned int x = argx;
  unsigned int shift_x;
  unsigned int scale_position = 0x80000000;
  short left_shift = 0;
  unsigned int right_shift = 1;
  int res;

  if (x <= 0)
    return (INT32_MIN+1);

  if (x == 1L << FIXED_RESOLUTION_SHIFT)
    return 0;

  while (x < scale_position) {
    ++left_shift;
    x <<= 1;
  }

  shift_x = x >> 1;

  if (left_shift < MAX_POWER)
    res = log_two_power_n_reversed_[left_shift];
  else if (left_shift > MAX_POWER)
    res = -log_two_power_n_reversed_[2 * MAX_POWER - left_shift];
  else
    res = 0;

  while (x && (right_shift < FIXED_RESOLUTION_SHIFT)) {
    while ((right_shift < FIXED_RESOLUTION_SHIFT) && (x < (shift_x + scale_position))) {
      shift_x >>= 1;
      ++right_shift;
    }

    x -= shift_x;
    shift_x = x >> right_shift;
    res += log_one_over_one_minus_two_power_minus_n_[right_shift - 1];
  }

  return res;
}
