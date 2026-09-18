/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-10-12
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_PVR_H_
#define	_LG1K_TE_PVR_H_

#include <lg1k/te/te.h>
#include <lg1k/te/buffer.h>

#include "te_pvr_kapi.h"

#define TS_PACKET_SIZE		188
#define TIME_TS_PACKET_SIZE	192

struct pvr_device;
struct pvr_dn;
struct pvr_up;

struct pvr_device *pvr_get_device(struct te_device *dev);
bool pvr_is_shared_mem(struct pvr_device *dev);

struct pvr_dn *pvr_dn_open(struct pvr_device *dev, int idx);
int pvr_dn_init(struct pvr_dn *dn, u32 src, u8 pkt_len, struct te_hwbuf *buf);
int pvr_dn_start(struct pvr_dn *dn);
int pvr_dn_stop(struct pvr_dn *dn);
void pvr_dn_close(struct pvr_dn *dn);
int pvr_dn_get_index(struct pvr_dn *dn);
int pvr_dn_write_data(struct pvr_dn *dn, u8 *data, int size);

struct pvr_up *pvr_up_open(struct pvr_device *dev, int idx);
int pvr_up_get_index(struct pvr_up *up);
int pvr_up_init(struct pvr_up *up, struct te_hwbuf *buf, u8 pkt_len,
		enum lx_pvr_up_dest dest);
int pvr_up_start(struct pvr_up *up);
int pvr_up_reset(struct pvr_up *up);
int pvr_up_pause(struct pvr_up *up);
int pvr_up_resume(struct pvr_up *up);
int pvr_up_set_mode(struct pvr_up *up, enum lx_pvr_up_mode mode);
int pvr_up_set_speed(struct pvr_up *up, u32 speed);
int pvr_up_set_tlv(struct pvr_up *up, bool enable);
int pvr_up_stop(struct pvr_up *up);
void pvr_up_close(struct pvr_up *up);

#endif				/* _LG1K_TE_PVR_H_ */
