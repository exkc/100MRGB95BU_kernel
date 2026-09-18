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
 *
 *  driver interface header for audio device. ( used only within kdriver )
 *  audio device will teach you how to make device driver with new platform.
 *
 *  @author Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.06.30
 *
 *  @addtogroup base
 *  @{
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "pipeline.h"

struct aud_block_info
{
    const char *block_type;
    bool isOpened;

    struct apipeline *pipeline;
};

#ifdef PORT_OUT
#undef PORT_OUT
#endif

#define PORT_OUT false

#ifdef PORT_IN
#undef PORT_IN
#endif
#define PORT_IN true

#define BYPASS_PORT 0x100

#endif /* _BLOCK_H_ */

/** @} */
