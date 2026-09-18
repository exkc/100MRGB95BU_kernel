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

#ifndef	_LG1K_TE_SCI_H_
#define	_LG1K_TE_SCI_H_

#include <lg1k/te/te.h>
#include <lg1k/te/buffer.h>

#include "sci_kapi.h"

/* we don't support chaining mode.
   rx len is cannot bigger than IFSD(254)
   tx data len is cannot bigger than IFSC(254)*/

#define APDU_HEADER_LEN	3
#define MAX_APDU_DATA_LEN	254
/* consider case 4(ISO/IEC 7816-3 Phase 12) */
#define MAX_CMD_APDU_LEN	(MAX_APDU_DATA_LEN + APDU_HEADER_LEN + 1)

struct sci_dev;
struct acas_ext_transfer_apdu;

struct sci_transmit {
	u8 *buf;
	u32 len;
};

struct sci_transmit_param {
	struct sci_transmit tx;
	struct sci_transmit rx;
};

struct sci_dev *sci_get_device(struct te_device *dev);
int sci_open(struct sci_dev *dev);
int sci_close(struct sci_dev *dev);
int sci_activate(struct sci_dev *dev);
void sci_deactivate(struct sci_dev *dev);
int sci_dev_transfer_apdu(struct sci_dev *dev,
			  struct sci_transmit_param *param);
int sci_get_reset_time(struct sci_dev *dev, s64 *param);

#endif				/* _LG1K_TE_SCI_H_ */
