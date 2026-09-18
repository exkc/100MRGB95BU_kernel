/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2023 by LG Electronics Inc.
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

#if defined BUILD_FEATURE_ddr_96bit
#include "ddr_96bit/platform_init.c"
#elif defined BUILD_FEATURE_audio_board
#include "audio_board/platform_init.c"
#else
#include "ddr_64bit/platform_init.c"
#endif
