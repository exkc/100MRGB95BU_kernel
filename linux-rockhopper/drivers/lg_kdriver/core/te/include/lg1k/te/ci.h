/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2019 by LG Electronics Inc.
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
 *  CA API header for linux dvb_ca(DEMUX&CA)
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2019-01-16
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

#ifndef _LG1K_TE_CI_H_
#define _LG1K_TE_CI_H_

#include "te_kapi.h"

struct ci_device;

enum ci_mode_speed {
	CI_PCMCIA_SPEED_LOW = 0,
	CI_PCMCIA_SPEED_HIGH,
};

enum ci_mode_datarate {
	CI_DATARATE_72 = 0,
	CI_DATARATE_97,
};

enum ci_mode_error {
	CI_ERROR_CHECK_FULL = 0,
	CI_ERROR_CHECK_SIMPLE,
};

enum cam_ready_status {
	CAM_READY_WAIT = 0,
	CAM_READY_SUCCESS,
	CAM_READY_FAIL,
};

struct ci_callback {
	void (*camchange_irq)(void *arg, int slot, bool detect);
	void (*camready_callback)(void *arg, int slot, bool ready);

	void *arg;	//-> lxdvb_ca
};

void ci_hw_init(struct ci_device *dev);

int ci_hw_ion_reset(struct ci_device *dev);
int ci_hw_ion_init_tp_checker(struct ci_device *dev, u16 pkt_cnt);
int ci_hw_ion_start_tp_checker(struct ci_device *dev, u16 pkt_cnt);

int ci_read_attribute_mem(struct ci_device *dev, int address);
int ci_write_attribute_mem(struct ci_device *dev, int address, u8 value);

int ci_read_cam_control(struct ci_device *dev, u8 address);
int ci_write_cam_control(struct ci_device *dev, u8 address, u8 value);

int ci_read_io_data(struct ci_device *dev, u8 *buf, u32 len);
int ci_write_io_data(struct ci_device *dev, u8 *buf, u32 len);

int ci_slot_reset(struct ci_device *dev);
int ci_slot_shutdown(struct ci_device *dev);
void ci_poll_slot_status(struct ci_device *dev, bool *changed, bool *present,
			enum cam_ready_status *status);
bool ci_check_card_detect(struct ci_device *dev);
int ci_get_slot_status(struct ci_device *dev, enum cam_ready_status *cam_ready);

/* New interface */
struct ci_device *ci_get_device(struct te_device *dev);
int ci_register_callback_funcs(struct ci_device *dev,
				    struct ci_callback *cb);

int ci_slot_initialize(struct ci_device *dev, bool use_intr);
void ci_slot_finalize(struct ci_device *dev);
int ci_read_iir_register(struct ci_device *dev);
int ci_set_input(struct ci_device *dev, enum lx_te_input_src src);
int ci_get_input(struct ci_device *dev, enum lx_te_input_src *src);

int ci_set_speed_mode(struct ci_device *dev, enum ci_mode_speed speed);
int ci_get_speed_mode(struct ci_device *dev, enum ci_mode_speed *speed);
int ci_set_rate_mode(struct ci_device *dev, enum ci_mode_datarate rate);
int ci_get_rate_mode(struct ci_device *dev, enum ci_mode_datarate *rate);
int ci_set_error_mode(struct ci_device *dev, enum ci_mode_error err);
int ci_get_error_mode(struct ci_device *dev, enum ci_mode_error *err);

#endif				//_LG1K_TE_CI_H_
