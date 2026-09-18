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

/** @file vbe_dpc_algo.h
 *
 *  It is the header file for controling v4l2 BE driver.
 *
 *  @author
 *  @version 1.0
 *  @date  2025.03.12
 *  @see
 */

#ifndef _VBE_DPC_ALGO_H
#define _VBE_DPC_ALGO_H

#define DPC_LUT_NUM 16

struct vbe_dpc_algo_param {
    int run;
    int prerun;
    int fixapl;
    int fixduty;
    int cur2pre;
    unsigned int interval;
    unsigned int readapl;
    unsigned int preapl;
    unsigned int curapl;
    unsigned int finalapl;
    unsigned int preduty;
    unsigned int curduty;
    unsigned int finalduty;
    unsigned int iirgain;
    unsigned int dbgprint;
    unsigned int lutx[DPC_LUT_NUM];
    unsigned int luty[DPC_LUT_NUM];
};

extern int vbe_dpc_algo_update(struct vbe_dpc_algo_param *p);

#endif  /* _VBE_DPC_ALGO_H */

