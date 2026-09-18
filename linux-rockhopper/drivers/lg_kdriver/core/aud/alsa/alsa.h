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



/** @file
 *
 *  alsa platform driver main header
 *
 *  @author     Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.07.01
 *
 *  @{
 */

#ifndef _ALSA_H_
#define _ALSA_H_

#include "log.h"

#define trace(fmt,args...)	logm_trace(alsa,fmt,##args)
#define debug(fmt,args...)	logm_debug(alsa,fmt,##args)
#define info(fmt,args...)	logm_info(alsa,fmt,##args)
#define noti(fmt,args...)	logm_noti(alsa,fmt,##args)
#define error(fmt,args...)	logm_error(alsa,fmt,##args)

#endif /* _ALSA_H_ */

