
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


/** @file spi_kapi.h
 *
 *  application interface header for spi device
 *
 *  @author		ingyu.yang (ingyu.yang@lge.com)
 *  @version		1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_spi
 *	@{
 */

#ifndef	_SPI_KAPI_H_
#define	_SPI_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	SPIKDRV_IOC_MAGIC		'S'
/**
@name SPI IOCTL List
ioctl list for spi device.

@{
@def LXDRV_SPI_INIT
SPI initialization.
When spi device receives above IOCTL,
then set the clock speed and enable the spi.
Also,Called only once at system initialization.

@def LXDRV_SPI_CLOCK
SPI clock selection.
Before read, write operation, This IOCTL is always called for data transmission speed.
This IOCTL is set up just one channel that wish to use.

@def LXDRV_SPI_ENABLE
SW SPI initialization
When spi device receives above IOCTL,
then enable gpio pin to SW SPI.
This IOCLL is set up just one channel that wish to use.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define LXDRV_SPI_INIT				_IO(SPIKDRV_IOC_MAGIC, 0)
#define LXDRV_SPI_SET_CONFIG        _IOW(SPIKDRV_IOC_MAGIC, 1, LX_SPI_CONFIG_T)
#define LXDRV_SPI_SET_CLOCK			_IOW(SPIKDRV_IOC_MAGIC, 2, UINT8)
#define LXDRV_SPI_ENABLE			_IOW(SPIKDRV_IOC_MAGIC, 3, UINT8)
#define LXDRV_SPI_TRANSMIT			_IOWR(SPIKDRV_IOC_MAGIC, 4, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_GET_STATUS        _IOR(SPIKDRV_IOC_MAGIC, 5, LX_SPI_STATUS_T)
//#define LXDRV_SPI_ENABLE_PRINT		_IOWR(SPI_IOC_MAGIC, 6, UINT32)



#define LXDRV_SPI_KDRV_IF_INIT			_IOW(SPIKDRV_IOC_MAGIC, 6, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_WRITE			_IOW(SPIKDRV_IOC_MAGIC, 7, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_READ			_IOWR(SPIKDRV_IOC_MAGIC, 8, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_BURSTWRITE		_IOW(SPIKDRV_IOC_MAGIC, 9, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_CHANGEPARAM	_IOW(SPIKDRV_IOC_MAGIC, 10, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_POLLINKDRV		_IOW(SPIKDRV_IOC_MAGIC, 11, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_WWR	_IOW(SPIKDRV_IOC_MAGIC, 12, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_RRD	_IOWR(SPIKDRV_IOC_MAGIC, 13, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_WR	_IOW(SPIKDRV_IOC_MAGIC, 14, LX_SPI_RW_DATA_T)
#define LXDRV_SPI_KDRV_IF_RD	_IOWR(SPIKDRV_IOC_MAGIC, 15, LX_SPI_RW_DATA_T)


// for debugging

#define SPI_IOC_MAXNR				20
#define SPI_KDRV_HW_NUM			2
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define SPI_POLL 1
#define GPIO_INTR 2
#define SPI_OTHER 3
#define SPI_INTR 4
#define SHOW_RXBUF 5
#define REGISTER_ISR 6
#define DMA_MODE 7
#define SPIDRV_EMUL 8
#define SPIDRV_DMAKDRV 9
#define SPIDRV_TX 10
#define SPIDRV_RX 11
#define SPIDRV_DMADISABLE 12
#define SPIDRV_DMAENABLE 13
//#define ENABLE_16BIT_TRANSFER
typedef struct
{
	UINT8	buf;
	UINT32	bufsize;
	UINT32	command;
	UINT32	data;
	UINT32	addr;

} LX_SPI_PARAM_T;

#define SPI_CLOCK_PHASE_FIRST_EDGE      0
#define SPI_CLOCK_PHASE_SECOND_EDGE     1

#define SPI_CLOCK_POLARITY_LOW          0
#define SPI_CLOCK_POLARITY_HIGH         1
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * spi ioctl and read/write operation parameter.
 * useful when complex parameter should be passed to spi kernel driver.
 */
 //* @see SPI_IOW_WRITE_STRUCT
 //*/
typedef struct LX_SPI_RW_DATA
{
	UINT8	subAddrSize;	// Address length in bytes
	UINT8	subAddr[4];		// Starting address inside the device
	UINT32	bufsize;		// size of buffer
	UINT32	addr;			// Clock
	UINT32	data;
	UINT8	ch;
	UINT8	csnum;
	UINT32   rxsize;
	UINT32   mode;
	UINT32   period;
	UINT32   len;
	UINT32	registerkdrvisr;
	UINT32	masterslave;
	UINT32	clock;
	UINT32	sendgpio;
	UINT32	ackgpio;
	union
	{
		UINT8	*buf;			// buffer
		UINT32	compat_buf;
		UINT64	sizer;
	};

} LX_SPI_RW_DATA_T;

typedef struct LX_SPI_STATUS
{
	UINT8	isBusy;
	UINT8	isReceiveFIFOFull;
	UINT8	isReceiveFIFONotEmpty;
	UINT8	isTransmitFIFONotFull;
	UINT8	isTransmitFIFOEmpty;
} LX_SPI_STATUS_T;

typedef struct LX_SPI_CONFIG
{
    UINT8   slave;
	UINT8	phase;
	UINT8	polarity;
    UINT8   clock;
    //UINT8   dataSize;
} LX_SPI_CONFIG_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _SPI_DRV_H_ */

/** @} */
