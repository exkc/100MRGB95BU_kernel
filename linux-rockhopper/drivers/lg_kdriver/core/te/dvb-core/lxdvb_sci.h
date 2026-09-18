/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
 *
 * Parts of this file were based on sources as follows:
 *
 * dmxdev.h
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *                    for convergence integrated media GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LXDVB_SCI_H_
#define _LXDVB_SCI_H_

#include <linux/dvbv5-ext/dvbv5-ext-acas.h>
#include <lg1k/te/sci.h>

struct lxdvb_sci {
	struct dvb_device *dvbdev;
	struct sci_dev *dev;
	struct mutex ioctl_mutex;
	struct te_debug_dir *debug_dir;
	u8 *tx;
	u8 *rx;
};

struct lxdvb_sci_fh {
	struct lxdvb_sci *sci;
};

#endif				/* _LXDVB_SCI_H_ */
