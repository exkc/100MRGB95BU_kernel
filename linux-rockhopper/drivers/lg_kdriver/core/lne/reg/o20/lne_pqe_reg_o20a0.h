/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  lne device driver header
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.06.18
 *
 */

#ifndef _LNE_PQE_REG_O20A0_H_
#define _LNE_PQE_REG_O20A0_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include "lne_tile_o20a0.h"
#include "lne_tilelet_o20a0.h"
#include "lne_sysreg_o20a0.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define LNE_PQE_REG_O20A0_TILE_BASE           0xC901E000
#define LNE_PQE_REG_O20A0_TILELET_BASE        0xC901F000
#define LNE_PQE_REG_O20A0_SYSREG_BASE         0xC901F800

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef struct {
    LNE_TILE_O20A0_REG          *tile;
    LNE_SYSREG_O20A0_REG        *tilelet;
    LNE_SYSREG_O20A0_REG        *sysreg;
} LNE_PQE_REG_O20A0_T;

#endif /* _LNE_REG_O20A0_H_ */
