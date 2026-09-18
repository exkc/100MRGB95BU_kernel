/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  CI Driver for linux dvb_ca(DEMUX&CA)
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2018-02-09
 *  @note		Additional information.
 */

/* Original Copyright */
/*
 * dvb_ca.h: generic DVB functions for EN50221 CA interfaces
 *
 * Copyright (C) 2004 Andrew de Quincey
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 */

#ifndef _LXDVB_CA_H_
#define _LXDVB_CA_H_

#include <linux/version.h>
#include <linux/dvb/ca.h>
#include <linux/dvbv5-ext/dvbv5-ext-ca.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <media/dvbdev.h>
#else
#include "dvbdev.h"
#endif

#define DVB_CA_POLL_CAM_PRESENT		1
#define DVB_CA_POLL_CAM_CHANGED		2
#define DVB_CA_POLL_CAM_READY		4

#define DVB_CA_FLAG_IRQ_CAMCHANGE	1
#define DVB_CA_FLAG_IRQ_FR			2
#define DVB_CA_FLAG_IRQ_DA			4

#define DVB_CA_CAMCHANGE_REMOVED	0
#define DVB_CA_CAMCHANGE_INSERTED	1

#endif				//_LXDVB_CA_H_
