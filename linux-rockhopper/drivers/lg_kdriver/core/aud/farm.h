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

/** @file
 * @ingroup Renderer
 *
 *  driver interface header for audio renderer
 *
 *  @author Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.06.30
 *
 *  @addtogroup Renderer
 *  @{
 *  @}
 */

#ifndef _FARM_H_
#define _FARM_H_

#include "block.h"

void farm_set_master_info (struct aud_block_info *block, struct aud_block_info *block_master);
void farm_initializer (void);
#endif /* _FARM_H_ */
