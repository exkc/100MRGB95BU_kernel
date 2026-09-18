/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2021 by LG Electronics Inc.

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
 *  clock gating header for mjpeg device. ( used only within kdriver )
 *	MJPEG device will teach you how to make device driver with new platform.
 *
 *  @author		Jaeyoun Jung (jaey.jung@lge.com)
 *  @version	1.0
 *  @date		2021.05.10
 *
 */

#ifndef _ICOD_CLOCKGATE_H_
#define _ICOD_CLOCKGATE_H_

typedef enum {
	ICOD_CLOCK_TYPE_ENABLE = 0,
	ICOD_CLOCK_TYPE_DISABLE,
} ICOD_CLOCK_TYPE_T;

void ICOD_ClockInit(void);
void ICOD_ClockResume(void);
void ICOD_ClockOn(void);
void ICOD_ClockOff(void);
int icod_ipw_clk_gate_init(void);
#endif //_ICOD_CLOCKGATE_H_
