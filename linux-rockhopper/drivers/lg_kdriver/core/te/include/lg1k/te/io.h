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

#ifndef	_LG1K_TE_IO_H_
#define	_LG1K_TE_IO_H_

#include <lg1k/te/te.h>
#include <lg1k/te/debug.h>

#include "te_kapi.h"

#define te_get_input_port_type(p)	((p)&0xF0)

/* TPI */
int te_config_tpi(struct te_device *dev, enum lx_te_input_port port,
		  struct lx_te_tpi_cfg *param);
int te_get_tpi_status(struct te_device *dev, LX_TE_INPUT_PORT_T port,
		      LX_TE_TPI_STATUS_T *status);

int te_connect_input_port(struct te_device *dev, LX_TE_INPUT_PORT_T port,
			  LX_TE_INPUT_PORT_T src);
int te_notify_ci_src_port(struct te_device *dev, enum lx_te_input_src);

struct lx_te_tpi_status *te_debug_get_tpi_status(struct te_device *dev);
void te_debug_show_tpi_status(struct te_device *dev, struct seq_file *m,
			      struct lx_te_tpi_status *old);
void te_debug_free_tpi_status(struct lx_te_tpi_status *status);

/* ATSC3/ARIB2 Mode Selection */
int te_set_engine_mode(struct te_device *dev, LX_TE_STREAM_TYPE_T stream_type);
LX_TE_STREAM_TYPE_T te_get_engine_mode(struct te_device *dev);

/* type to string */
const char *te_input_source_to_str(LX_TE_INPUT_SRC_T src);
const char *te_input_mode_to_str(LX_TE_INPUT_MODE_T mode);
const char *te_input_port_to_str(LX_TE_INPUT_PORT_T port);
const char *te_stream_type_to_str(LX_TE_STREAM_TYPE_T type);
const char *te_sync_type_to_str(LX_TE_SYNC_TYPE_T type);
const char *te_sync_type_to_short_str(LX_TE_SYNC_TYPE_T type);
const char *te_ci_src_type_to_str(enum te_reg_ci_input src);
const char *te_ch_src_type_to_str(enum te_reg_channel_src src);

/* string to type */
LX_TE_INPUT_SRC_T te_str_to_input_source(const char *str);
LX_TE_INPUT_PORT_T te_str_to_input_port(const char *str);
LX_TE_INPUT_MODE_T te_str_to_input_mode(const char *str);
LX_TE_STREAM_TYPE_T te_str_to_stream_type(const char *str);
LX_TE_SYNC_TYPE_T te_str_to_sync_type(const char *str);

/***** type conversion *****/

/* LX_TE_INPUT_SRC_T <=> enum te_reg_tpi_port */
enum te_reg_tpi_port te_input_src_to_reg_tpi_port(LX_TE_INPUT_SRC_T src);
LX_TE_INPUT_SRC_T te_reg_tpi_port_to_input_src(enum te_reg_tpi_port port);

/* LX_TE_INPUT_SRC_T <=> enum te_reg_ci_input */
enum te_reg_ci_input te_input_src_to_reg_ci_input(LX_TE_INPUT_SRC_T src);
LX_TE_INPUT_SRC_T te_reg_ci_input_to_input_src(enum te_reg_ci_input input);

/* LX_TE_INPUT_PORT_T <=> enum te_reg_tpi_port */
enum te_reg_tpi_port te_input_port_to_reg_tpi_port(LX_TE_INPUT_PORT_T port);
LX_TE_INPUT_PORT_T te_reg_tpi_port_to_input_port(enum te_reg_tpi_port port);

/* LX_TE_INPUT_PORT_T <=> enum te_reg_channel_src */
enum te_reg_channel_src te_input_port_to_reg_ch_src(LX_TE_INPUT_PORT_T port);
LX_TE_INPUT_PORT_T te_reg_ch_src_to_input_port(enum te_reg_channel_src src);

/* LX_TE_SYNC_TYPE_T <=> enum te_reg_tpi_sync */
enum te_reg_tpi_sync te_sync_type_to_reg_tpi_sync(LX_TE_SYNC_TYPE_T type);
LX_TE_SYNC_TYPE_T te_reg_tpi_sync_to_sync_type(enum te_reg_tpi_sync sync);

#endif				/* _LG1K_TE_IO_H_ */
