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
 *  sdec driver
 *
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#ifndef _TE_REG_DUMPER_H_
#define _TE_REG_DUMPER_H_

#include <lg1k/te/reg.h>

/************ ATSC3.0 ************/
int TE_REG_ATSC3_Init(void);
int TE_REG_ATSC3_SetDemodType(u8 ch, enum te_reg_atsc3_demod_type type);
int TE_REG_ATSC3_SetChannelMode(u8 ch, enum te_reg_dumper_mode mode);
int TE_REG_ATSC3_SetChannelEnable(u8 ch, bool en);
int TE_REG_ATSC3_SetDecoderLayer(u8 ch, enum te_reg_atsc3_layer layer);
int TE_REG_ATSC3_SetPLPFilter(u8 ch, bool en, u8 id);

int TE_REG_ATSC3_SetMetaBuffer(u8 ch, u32 sptr, u32 eptr);
int TE_REG_ATSC3_GetMetaWptr(u8 ch, u32 *wptr);
int TE_REG_ATSC3_SetMetaRptr(u8 ch, u32 rptr);
int TE_REG_ATSC3_SetMetaUnitBufferSize(u8 ch, u32 size);
int TE_REG_ATSC3_SetMetaAlmostFullLevel(u8 ch, u32 size);

int TE_REG_ATSC3_SetDataBuffer(u8 ch, u32 sptr, u32 eptr);
int TE_REG_ATSC3_GetDataWptr(u8 ch, u32 *wptr);
int TE_REG_ATSC3_SetDataRptr(u8 ch, u32 rptr);
int TE_REG_ATSC3_SetDataUnitBufferSize(u8 ch, u32 size);
int TE_REG_ATSC3_SetDataAlmostFullLevel(u8 ch, u32 size);

int TE_REG_ATSC3_GetTimeStamp(u8 ch, struct te_reg_atsc3_timestamp *timestamp);

int TE_REG_ATSC3_SetIntrEnable(u32 val, bool en);
int TE_REG_ATSC3_GetIntrStatus(u32 *val);
int TE_REG_ATSC3_ClearIntr(u32 val);

int TE_REG_ATSC3_SetTimeSource(u8 ch, u8 src);
int TE_REG_ATSC3_SetGmauAwUser(u8 val);
int TE_REG_ATSC3_SetTimestampLatchEnable(u8 ch, bool en);

/************ ARIB2.0 ************/
int TE_REG_ARIB2_init(void);
int TE_REG_ARIB2_SetIntrEnable(u32 val, bool en);
int TE_REG_ARIB2_GetIntrStatus(u32 *val);
int TE_REG_ARIB2_ClearIntr(u32 val);

int TE_REG_ARIB2_SetLatchEnable(u8 ch, bool en);
int TE_REG_ARIB2_SetNTPConf(u8 ch, bool len_check, bool swreset);
int TE_REG_ARIB2_SetNTPSrcAddress(u8 ch, u32 *val, u32 *mask);
int TE_REG_ARIB2_SetNTPDstAddress(u8 ch, u32 *val, u32 *mask);
int TE_REG_ARIB2_SetUDPPortValue(u8 ch, u32 src, u32 dst);
int TE_REG_ARIB2_SetUDPPortMask(u8 ch, u32 src, u32 dst);

int TE_REG_ARIB2_GetNTPInfo(u8 ch, struct te_reg_arib2_ntp_info *info);
int TE_REG_ARIB2_SetChannelMode(u8 ch, enum te_reg_dumper_mode mode);
int TE_REG_ARIB2_SetChannelEnable(u8 ch, bool en);

int TE_REG_ARIB2_SetDataBuffer(u8 ch, u32 sptr, u32 eptr);
int TE_REG_ARIB2_GetDataWptr(u8 ch, u32 *wptr);
int TE_REG_ARIB2_SetDataRptr(u8 ch, u32 rptr);

int TE_REG_ARIB2_SetMetaBuffer(u8 ch, u32 sptr, u32 eptr);
int TE_REG_ARIB2_GetMetaWptr(u8 ch, u32 *wptr);
int TE_REG_ARIB2_SetMetaRptr(u8 ch, u32 rptr);

int TE_REG_ARIB2_SetDataFullLevel(u8 ch, u32 level);
int TE_REG_ARIB2_SetDataUnitBufferSize(u8 ch, u32 size);
int TE_REG_ARIB2_SetMetaFullLevel(u8 ch, u32 level);
int TE_REG_ARIB2_SetMetaUnitBufferSize(u8 ch, u32 size);

int TE_REG_ARIB2_SetGmauAwUser(u8 val);
int TE_REG_ARIB2_SetTimeSource(u8 ch, u8 idx);

#endif
