/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2013 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or 
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
    GNU General Public License for more details.
*/ 



/** @file alsa_machine.h
 *
 *  alsa platform driver.
 *
 *  @author     Won Chang Shin(wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2013.03.20
 *
 *  @{
 */

#ifndef _lg115x_ALSA_MACHINE_H_
#define _lg115x_ALSA_MACHINE_H_

int ALSA_MACHINE_Init(void);
void ALSA_MACHINE_Cleanup(void);

#endif /* _lg115x_ALSA_MACHINE_H_ */

