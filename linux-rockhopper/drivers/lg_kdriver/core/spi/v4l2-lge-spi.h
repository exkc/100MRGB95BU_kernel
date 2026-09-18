/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file v4l2-lge-spi.h
 *
 *  It is the header file for controling v4l2 scaler driver.
 *
 *  @author     Do, Seong-Hoon(seonghoon1128.do@lge.com)
 *  @version    1.0
 *  @date       2018.05.17
 *  @note
 *  @see
 */

#ifndef _V4L2_LGE_SPI_H
#define _V4L2_LGE_SPI_H

#include <linux/v4l2-controls.h>
#include <linux/mutex.h>
#include <linux/io.h>
#include <linux/spi/spi.h>
#include <linux/amba/pl022.h>

#include "base_types.h"
#include "debug_util.h"

#define V4L2_CID_USER_SPI_BASE          (V4L2_CID_USER_BASE + 0x3000)
#define V4L2_CID_SPI_INIT               (V4L2_CID_USER_SPI_BASE + 0)
#define V4L2_CID_SPI_CONF               (V4L2_CID_USER_SPI_BASE + 1)
#define V4L2_CID_SPI_WRITE              (V4L2_CID_USER_SPI_BASE + 2)
#define V4L2_CID_SPI_READ               (V4L2_CID_USER_SPI_BASE + 3)
#define V4L2_CID_SPI               		(V4L2_CID_USER_SPI_BASE + 4)

#define SPI_KDRV_HW_NUM 2
#define SPI_SIZE 30
#define ADDR_SIZE_IN_BYTE 4
#define SPI_MSG_MAX 2048


#define SPI_MODE_MASK       (SPI_CPHA | SPI_CPOL | SPI_CS_HIGH \
					| SPI_LSB_FIRST | SPI_3WIRE | SPI_LOOP \
					| SPI_NO_CS | SPI_READY | SPI_TX_DUAL \
					| SPI_TX_QUAD | SPI_RX_DUAL | SPI_RX_QUAD)

extern struct mutex spikdrv_mutex;
extern struct spi_device *pv4l2_spi_device[SPI_KDRV_HW_NUM];
extern unsigned int v4l2_spi_init[SPI_KDRV_HW_NUM];
extern void __iomem *spi_ctop_base ;

struct 	V4L2_SPI_CFG
{
   UINT8 u8channel;
   UINT8 u8mode;
   UINT32 u32speed;
};

struct 	V4L2_SPI_PARAM
{
   UINT8 u8channel;
   UINT8 u8mode;
   UINT8 u32speed;
   UINT32 u32addr;
   UINT32 u32size;
   UINT8 *u8dataToRead;
   UINT8 *u8dataToWrite;
};

#endif  /* _V4L2_LGE_SPI_H */
