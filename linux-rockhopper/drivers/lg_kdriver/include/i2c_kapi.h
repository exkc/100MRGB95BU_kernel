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


/** @file i2c_kapi.h
 *
 *  application interface header for i2c device
 *
 *  @author		ingyu.yang (ingyu.yang@lge.com)
 *  @version		1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_i2c
 *	@{
 */

#ifndef	_I2C_KAPI_H_
#define	_I2C_KAPI_H_

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
#define	I2C_IOC_MAGIC		'u'
/**
@name I2C IOCTL List
ioctl list for i2c device.

@{

@def I2C_IOW_SET_CLOCK
IIC clock selection.
Before read, write operation, This IOCTL is always called for data transmission speed.
This IOCTL is set up just one channel that wish to use.

@def I2C_IOW_SET_GPIO_PORT
SW IIC initialization
When i2c device receives above IOCTL,
then enable gpio pin to SW IIC.
This IOCLL is set up just one channel that wish to use.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define I2C_IOW_SET_CLOCK			_IOW(I2C_IOC_MAGIC,		0, LX_I2C_CLOCK_T)
#define I2C_IOW_WRITE				_IOW(I2C_IOC_MAGIC,		1, LX_I2C_RW_DATA_T)
#define I2C_IORW_READ				_IOWR(I2C_IOC_MAGIC,	2, LX_I2C_RW_DATA_T)
#define I2C_IOW_SET_GPIO_PORT		_IOW(I2C_IOC_MAGIC,		3, LX_I2C_GPIO_MAP_T)

#define I2C_IOC_MAXNR				10


/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum LX_I2C_CLOCK
{
	I2C_CLOCK_50KHZ = 0,
	I2C_CLOCK_100KHZ,
	I2C_CLOCK_200KHZ,
	I2C_CLOCK_400KHZ,
	I2C_CLOCK_700KHZ,
	I2C_CLOCK_800KHZ,
	I2C_CLOCK_1MHZ,
	I2C_CLOCK_2MHZ,
	I2C_CLOCK_4MHZ,
	I2C_CLOCK_8MHZ,

	I2C_CLOCK_INVALID = 0xFF,

} LX_I2C_CLOCK_T;


/**
 * i2c ioctl and read/write operation parameter.
 * useful when complex parameter should be passed to i2c kernel driver.
 */
 //* @see I2C_IOW_WRITE_STRUCT
 //*/
typedef struct LX_I2C_RW_DATA
{
	UINT8	slaveAddr;		// Device slave ID
	UINT8	subAddrSize;	// Address length in bytes
	UINT8	subAddr[8];		// Starting address inside the device
	UINT32	bufSize;		// size of buffer
	UINT32	clock;			// Clock
	UINT32	flag;
	union
	{
		UINT8	*buf;			// buffer
		UINT32	compat_buf;
		UINT64	sizer;
	};
} LX_I2C_RW_DATA_T;

/**
 * i2c ioctl and read/write operation parameter.
 * useful when complex parameter should be passed to i2c kernel driver.
 */
 //* @see I2C_IOW_WRITE_STRUCT
 //*/
typedef struct LX_I2C_GPIO_MAP
{
	UINT8	sda;
	UINT8	scl;
} LX_I2C_GPIO_MAP_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Configuration
----------------------------------------------------------------------------------------*/
#define	LX_I2C_CFG_NONE			0x00000000
#define	LX_I2C_CFG_LEGACY_MODE	0x00000001

extern UINT32	lx_i2c_cfg(void);

/*----------------------------------------------------------------------------------------
	Kernel API extention
----------------------------------------------------------------------------------------*/
#include <linux/i2c.h>
#define I2C_VALID_SIZE		0x100  /* read data, from slave to master */
#define I2C_M_RD			0x0001  /* read data, from slave to master */

#define I2C_M_CLK_DEAFULT	0x0000
#define I2C_M_CLK__50KHZ	0x0002
#define I2C_M_CLK_100KHZ	0x0004
#define I2C_M_CLK_400KHZ	0x0006
#define I2C_M_CLK_800KHZ	0x0008
#define I2C_M_CLK_MASK		0x000e

#define SUBADDR_MAX_SIZE	8	/* sub address max size */
#define SBUF_SIZE			32	/* static buf size */
#define I2C_HW_CH_NUM		10

extern struct i2c_adapter *i2c_get_adapter(int nr);
extern int i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num);
extern void i2c_put_adapter(struct i2c_adapter *adap);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _I2C_DRV_H_ */

/** @} */
