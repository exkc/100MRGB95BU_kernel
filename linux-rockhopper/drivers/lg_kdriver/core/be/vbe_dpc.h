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

/** @file vbe_dpc.h
 *
 *  It is the header file for controling v4l2 BE driver.
 *
 *  @author
 *  @version 1.0
 *  @date  2025.03.12
 *  @see
 */

#ifndef _VBE_DPC_H
#define _VBE_DPC_H

#include "be_kapi.h"

extern int vbe_dpc_init(void);
extern int vbe_dpc_sync_handler(void);
extern int vbe_dpc_noti_chg_clk_wait(void);
extern int vbe_dpc_noti_chg_clk_done(unsigned int clk);

#endif  /* _VBE_DPC_H */

