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

/*! \file DEMOD_module.c
 * \brief DEMOD module control Drivers linux module
 */
#define DEMOD_TAG "[CORE.MD] "

/**
 *	Necessary includes for device drivers
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/printk.h>   /**< For print_hex_dump */
#include <linux/delay.h>
#include <linux/mutex.h> //220927

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "os_util.h"
//#include "base_dev_cfg.h"
#include "base_device.h"
//#include "sys_regs.h"
#include "ctop_regs.h"  //chungiii fpga
#include "demod_drv.h"
#include "demod_module.h"
#include "demod_impl.h"
#include "sys_regs.h"  //chungiii fpga
#include "i2c_core.h"


/******************************************************************************
 *				DEFINES
 *****************************************************************************/
#if defined(DEMOD_CONFIG_EXT)
#define I2C_TRY_MAX_CNT 2

#define I2C_CLK_800KHZ    0x0008
#define I2C_CLK_400KHZ    0x0006
#endif

/**
 *	Global variables of the driver
 */
#include <linux/spinlock.h>
static DEFINE_SPINLOCK(_demod_apb_lock);

//static int DEMOD_exit (void);


static LX_DEMOD_I2C_DESCRIPT_T	_demod_i2c = {0, 0, 0}; //jeongpil.yun
static volatile struct i2c_adapter * _demod_i2c_adap = NULL;

extern DEMOD_HAL_T	g_demod_hal;

extern BOOLEAN 		_gIsFWDn;
extern BOOLEAN 		_gIs_ioremap;

volatile UINT32 *	gpDEMOD_APB = NULL;
volatile UINT32		szDEMOD_APB = 0;

#if defined(DEMOD_CONFIG_LGDBB)
extern void DEMOD_M16P_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_L18F_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_O18_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_M19_InitHAL (DEMOD_HAL_T* hal);
#endif

#if defined(DEMOD_CONFIG_LGDBB_IPC)
extern void DEMOD_O20_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_E60_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_O22_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_M23_InitHAL (DEMOD_HAL_T* hal);
extern void DEMOD_O24_InitHAL (DEMOD_HAL_T* hal); //!//
extern void DEMOD_O26_InitHAL (DEMOD_HAL_T* hal); //chungiii


#endif

BOOLEAN		gPanama = FALSE;

#define AUTO_INCREMENT	(0x40) // bit 6: 1- Auto increment, 0- Poll

/******************************************************************************
 *				DATA STRUCTURES
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */

/******************************************************************************
 *				Local function
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */

int DEMOD_APB_Read(UINT32 addr, UINT32 *pval)
{
	UINT32 reg_wsize = 0;
	UINT32 reg_waddr = addr >> 2;
	
	unsigned long irq_flags;

	if(gpDEMOD_APB == NULL)
	{
		DEMOD_ERROR("gpDEMOD_APB is NULL\n");
		return RET_ERROR;
	}

	reg_wsize = szDEMOD_APB >> 2;

	if (reg_waddr > (reg_wsize)) {
		DEMOD_ERROR("memory addr out of range 0x%08x > 0x%08x\n", reg_waddr, reg_wsize);
		return RET_ERROR;
	}

	spin_lock_irqsave(&_demod_apb_lock, irq_flags);
	*pval = *(gpDEMOD_APB + reg_waddr);
	spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);
	return RET_OK;
}


int DEMOD_APB_Write(UINT32 addr, UINT32 *pval)
{
	UINT32 reg_wsize = 0;
	UINT32 reg_waddr = addr >> 2;

	unsigned long irq_flags;


	if(gpDEMOD_APB == NULL)
	{
		DEMOD_ERROR("gpDEMOD_APB is NULL\n");
		return RET_ERROR;
	}

	reg_wsize = szDEMOD_APB >> 2;

	if (reg_waddr > (reg_wsize)) {
		DEMOD_ERROR("memory addr out of range 0x%08x > 0x%08x\n", reg_waddr, reg_wsize);
		return RET_ERROR;
	}

	spin_lock_irqsave(&_demod_apb_lock, irq_flags);
	*(gpDEMOD_APB + reg_waddr) = *pval;
	spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_open.
 * Open I2C device
 *
 * @param portI2C [IN] I2C channel index
 * @param deviceID [IN] GBB chip address
 * @param *pHandle [OUT] handle
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
#include <linux/delay.h>
#endif

int DEMOD_I2C_open(UINT8 portI2C, UINT16 deviceID)
{
#if defined(INCLUDE_KDRV_I2C)
	if (_demod_i2c.handle == 0) {
#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
		_demod_i2c.portI2C = DEMOD_I2C_PORT;
		_demod_i2c.slvAddr = DEMOD_I2C_ADDR;
#else
		_demod_i2c.portI2C = portI2C;
		_demod_i2c.slvAddr = deviceID;
#endif
		_demod_i2c.handle = I2C_DevOpen(_demod_i2c.portI2C - 1);

		I2C_DevSetClock(_demod_i2c.handle, I2C_CLOCK_400KHZ);

		_demod_i2c_adap = i2c_get_adapter(_demod_i2c.portI2C - 1);

		DEMOD_INFO("opened port %u, slave 0x%02x, adap %p\n", _demod_i2c.portI2C, _demod_i2c.slvAddr, _demod_i2c_adap);

	} else {
		DEMOD_INFO("already opened, port %u, slave 0x%02x\n", _demod_i2c.portI2C, _demod_i2c.slvAddr);
	}
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif
	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_I2C_open);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Close.
 * Close I2C device
 *
 * @param none [IN] void
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_Close(void)
{
#if defined(INCLUDE_KDRV_I2C)
	i2c_put_adapter((struct i2c_adapter *)_demod_i2c_adap);
	_demod_i2c_adap = NULL;
	
	_demod_i2c.slvAddr	  = 0;
	I2C_DevClose(_demod_i2c.handle);
	_demod_i2c.handle = 0;

	DEMOD_INFO("close, port %u, slave 0x%02x\n", _demod_i2c.portI2C, _demod_i2c.slvAddr);
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Raw_Lock.
 * i2c adapter lock 
 */

void DEMOD_I2C_Raw_Lock(void)
{
#if defined(INCLUDE_KDRV_I2C)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	_demod_i2c_adap->lock_ops->lock_bus((struct i2c_adapter *)_demod_i2c_adap, 0);
#else
	i2c_lock_adapter((struct i2c_adapter *)_demod_i2c_adap);
#endif
	
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Raw_Unlock.
 * i2c adapter unlock 
 */

void DEMOD_I2C_Raw_Unlock(void)
{
#if defined(INCLUDE_KDRV_I2C)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	_demod_i2c_adap->lock_ops->unlock_bus((struct i2c_adapter *)_demod_i2c_adap, 0);
#else
	i2c_unlock_adapter((struct i2c_adapter *)_demod_i2c_adap);
#endif	
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Raw_Read
 * i2c read without i2c_adpater lock
 *
 * @param slvaddr [IN]  UINT8 , slave device address
 * @param address [IN]  UINT16, slave device register address
 * @param nBytes  [IN]  UINT16, read bytes
 * @param pData   [OUT] UINT8*, read data 
 */

int DEMOD_I2C_Raw_Read(UINT8 slvaddr, UINT16 address, UINT16 nBytes, UINT8 *pData)
{
#if defined(INCLUDE_KDRV_I2C)
#if defined(DEMOD_CONFIG_EXT)
	int i = 0, ret;
	struct i2c_msg msgs[2];
	u8 buf[2];

	int left = nBytes;

	for (i = 0; left > 0; i++) {
		buf[0] = (u8) (((address + i) >> 8) & 0xff);
		buf[1] = (u8) ((address + i) & 0xff);

		msgs[0].addr =	slvaddr;
		msgs[0].flags = I2C_CLK_400KHZ;
		msgs[0].len = 2;
		msgs[0].buf = buf;

		msgs[1].addr = msgs[0].addr;
		msgs[1].flags = I2C_M_RD | I2C_CLK_400KHZ;
		msgs[1].len = (left > 4) ? 4 : left;	// DEMOD I2C limitation
		msgs[1].buf = pData + (i << 2);

		ret = __i2c_transfer((struct i2c_adapter *)_demod_i2c_adap, msgs, 2);
		if (ret < 0)
		{
			DEMOD_ERROR("FAIL, i2c_transfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x], nBytes[%d])\n",
						_demod_i2c.portI2C, _demod_i2c.slvAddr, address + i, *(pData + (i << 2)), nBytes);
			return RET_ERROR;
		}

		left -= 4;
	}

	if (ret < 0)
	{
		DEMOD_ERROR("FAIL, i2c_transfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x], nBytes[%d])\n",
						_demod_i2c.portI2C, _demod_i2c.slvAddr, address, *pData, nBytes);

		return RET_ERROR;
	}
	DEMOD_DEBUG("SUCCESS, i2c_transfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x], nBytes[%d])\n",
					_demod_i2c.portI2C, _demod_i2c.slvAddr, address, *pData, nBytes);
#endif
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Raw_Write
 * i2c write without i2c_adpater lock
 *
 * @param slvaddr [IN]  UINT8 , slave device address
 * @param address [IN]  UINT16, slave device register address
 * @param nBytes  [IN]  UINT16, write bytes
 * @param pData   [OUT] UINT8*, write data 
 */
int DEMOD_I2C_Raw_Write(UINT8 slvaddr, UINT16 address, UINT16 nBytes, UINT8 *pData)
{
#if defined(INCLUDE_KDRV_I2C)
#if defined(DEMOD_CONFIG_EXT)
	int i = 0, ret;
	unsigned char buffers[300];

	struct i2c_msg msg;

	memset(buffers, 0, sizeof(buffers));

	buffers[0] = (u8) ((address >> 8) & 0x00ff);
	buffers[1] = (u8) (address & 0x00ff);

	for (i = 0; i < nBytes; i++) {
		buffers[i+2] = pData[i];
	}

	msg.addr = slvaddr;
	msg.flags = I2C_CLK_400KHZ;
	msg.len = nBytes + 2;
	msg.buf = (char *)buffers;

	ret = __i2c_transfer((struct i2c_adapter *)_demod_i2c_adap, &msg, 1);

	if (ret < 0)
	{
		DEMOD_ERROR("FAIL, i2c_transfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x], nBytes[%d])\n",
						_demod_i2c.portI2C, _demod_i2c.slvAddr, address, *pData, nBytes);

		return RET_ERROR;
	}
	DEMOD_DEBUG("SUCCESS, i2c_transfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x], nBytes[%d])\n",
					_demod_i2c.portI2C, _demod_i2c.slvAddr, address, *pData, nBytes);
#endif
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Read.
 * Read the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_Read( UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	int ret;

	DEMOD_I2C_Raw_Lock();
	ret = DEMOD_I2C_Raw_Read((_demod_i2c.slvAddr >> 1), address, nBytes, pData);
	DEMOD_I2C_Raw_Unlock();

	return ret;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_I2C_Write.
 * Write the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - register data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_I2C_Write( UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	int ret;

	DEMOD_I2C_Raw_Lock();
	ret = DEMOD_I2C_Raw_Write((_demod_i2c.slvAddr >> 1), address, nBytes, pData);
	DEMOD_I2C_Raw_Unlock();

	return ret;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Test_I2C_Read.
 * Read the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int ADC_Test_I2C_Read (UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData)
{
#if defined(INCLUDE_KDRV_I2C)
	LX_I2C_RW_DATA_T data;

#if 0
	typedef struct LX_I2C_RW_DATA
	{
		UINT8	slaveAddr;		// Device slave ID
		UINT8	subAddrSize;	// Address length in bytes
		UINT8	subAddr[4]; 	// Starting address inside the device
		UINT8	*buf;			// buffer
		UINT32	bufSize;		// size of buffer
		UINT32	clock;			// Clock
		UINT32	flag;
	} LX_I2C_RW_DATA_T;
#endif
	data.slaveAddr		= slvAddr;
	data.subAddrSize	= 1;
	data.subAddr[0]		= address;
	data.buf			= pData;
	data.bufSize 		= nBytes;
	data.clock			= I2C_CLOCK_100KHZ;
	data.flag			= 0;

	if (nBytes != I2C_DevTransfer(_demod_i2c.handle, &data, I2C_READ_MODE))
	{
		DEMOD_PRINT("FAIL, I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  \n",
					_demod_i2c.portI2C,slvAddr, address, *pData);
		return RET_ERROR;
	}	
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Test_I2C_Write.
 * Write the GBB register value throuth IIC
 *
 * @param address [IN] 	UINT16 - Slave address
 * @param nBytes  [IN] 	UINT16 - data length
 * @param pData   [OUT] UINT8  - register data
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int ADC_Test_I2C_Write (UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData)
{
#if defined(INCLUDE_KDRV_I2C)
	LX_I2C_RW_DATA_T data;
#if 0
	typedef struct LX_I2C_RW_DATA
	{
		UINT8	slaveAddr;		// Device slave ID
		UINT8	subAddrSize;	// Address length in bytes
		UINT8	subAddr[4]; 	// Starting address inside the device
		UINT8	*buf;			// buffer
		UINT32	bufSize;		// size of buffer
		UINT32	clock;			// Clock
		UINT32	flag;
	} LX_I2C_RW_DATA_T;
#endif
	data.slaveAddr		= slvAddr;
	data.subAddrSize	= 1;
	data.subAddr[0]		= address;
//	data.subAddr[1]		= (UINT8)(address & 0xFF);
	data.buf			= pData;
	data.bufSize 		= nBytes;
	data.clock			= I2C_CLOCK_100KHZ;
	data.flag			= 0;

	if (nBytes != I2C_DevTransfer(_demod_i2c.handle, &data, I2C_WRITE_MODE))
	{
		DEMOD_PRINT("FAIL, I2C_DevTransfer(Port[0x%0x, 0x%x] A[0x%0x] D[0x%0x])  \n",
					_demod_i2c.portI2C,slvAddr, address, *pData);
		return RET_ERROR;
	}	
#else
	DEMOD_NOTI("I2C deactivated\n");
#endif

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ADC_Control.
 * Select the adc voltage range.
 *
 * @param address [IN] 	votageSel - LX_DEMOD_ADC_VOLTAGE_SEL_T (1V or 2V)
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_ADC_Control (LX_DEMOD_ADC_VOLTAGE_SEL_T votageSel)
{
#if 1
	UINT8 	subaddress;
	UINT8 	wrdata;
	UINT8 	slaveAddr;
	UINT16 	nbyte;

	if( LX_DEMOD_ADC_SEL_1V == votageSel)
	{
		subaddress 	= 0x1b;
		wrdata 		= 0x9;
		slaveAddr 	= 0x80;
		nbyte 		= 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("FAIL, ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
						_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;
		}
		DEMOD_PRINT("SUCCESS ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
					_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);
		subaddress 	= 0x1c;
		wrdata 		= 0xa9;
		slaveAddr 	= 0x80;
		nbyte 		= 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("FAIL, ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
						_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);
//			return RET_ERROR;
		}
		DEMOD_PRINT("SUCCESS ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
					_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);

		subaddress 	= 0x1d;
		wrdata 		= 0x3;
		slaveAddr 	= 0x80;
		nbyte 		= 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("FAIL, ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
						_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("SUCCESS ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
					_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);


		subaddress 	= 0x1e;
		wrdata 		= 0x19;
		slaveAddr 	= 0x80;
		nbyte 		= 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("FAIL, ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
						_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
		DEMOD_PRINT("SUCCESS ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
					_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);


		subaddress 	= 0x1f;
		wrdata 		= 0x00;
		slaveAddr 	= 0x80;
		nbyte 		= 1;

		if(nbyte != ADC_Test_I2C_Write(slaveAddr, subaddress, 1, &wrdata))
		{
			DEMOD_PRINT("FAIL, ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
						_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);

//			return RET_ERROR;

		}
//		DEMOD_PRINT("^Y^[KDRV_DEMOD] SUCCESS ADC_Test_I2C_Write(H[0x%0x, 0x%x] A[0x%0x] D[0x%0x]) \n",
//					_demod_i2c.portI2C, slaveAddr, subaddress, wrdata);
	}
	else
	{

	}
#endif
	return RET_OK;

}

int DEMOD_DBB_I2C_Read (UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DBB_I2C_Read)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DBB_I2C_Read(address, nBytes,pData))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_DBB_I2C_Write (UINT16 address, UINT16 nBytes, UINT8 *pData)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DBB_I2C_Write)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DBB_I2C_Write(address, nBytes,pData))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_DBB_APB_DEBUG_Read (UINT16 address, UINT32 *pData)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DBB_APB_DEBUG_Read)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DBB_APB_DEBUG_Read(address, pData))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_DBB_APB_Read (UINT16 address, UINT32 *pData)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DBB_APB_Read)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DBB_APB_Read(address, pData))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_DBB_APB_Write (UINT16 address, UINT32 *pData)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DBB_APB_Write)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DBB_APB_Write(address, pData))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_DBB_PDB_Write (UINT32 value)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DBB_PDB_Write)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DBB_PDB_Write(value))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ResetHW.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ResetHW (void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.ResetHW)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.ResetHW())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ResetHW);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_OperModeReset.
 * Reset GBB demod ID.
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_OperModeReset (LX_DEMOD_OPER_MODE_T operMode)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.OperModeReset)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.OperModeReset(operMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_OperModeReset);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_SetI2C.
 * select normal mode
 *
 * @param none  [IN/OUT]
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_SetI2C (void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.SetI2C)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SetI2C())
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");
	return RET_OK;
}


int DEMOD_Get_I2C_Handle (UINT8 portI2C, UINT16 deviceID)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.Get_I2C_Handle)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.Get_I2C_Handle(portI2C, deviceID))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_FW_Initialize (void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.FW_Initialize)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.FW_Initialize())
	{
		_gIsFWDn = FALSE;
		DEMOD_RETURN_FAIL(__F__);
	}
	_gIsFWDn = TRUE;
	DEMOD_PRINT("End \n");

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_FW_Initialize);

int DEMOD_SAT_FW_Initialize (void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.SAT_FW_Initialize)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SAT_FW_Initialize())
	{
		_gIsFWDn = FALSE;
		DEMOD_RETURN_FAIL(__F__);
	}
	_gIsFWDn = TRUE;
	DEMOD_PRINT("End \n");

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_SAT_FW_Initialize);

int DEMOD_DVB_C_reset (void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.DVB_C_reset)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DVB_C_reset())
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVB_C_reset);

BOOLEAN KHAL_DEMOD_FWdn (void)
{
	int retry = 300;
	while((_gIsFWDn == FALSE) && (retry--)) {
		usleep_range(10000,10000);
	}
	DEMOD_NOTI("fwdn %d, retry %d\n", _gIsFWDn, 300 - retry);

	if (_gIsFWDn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
EXPORT_SYMBOL(KHAL_DEMOD_FWdn);

void KHAL_DEMOD_Init_gIsFWDn (BOOLEAN done)
{
	if ( done == TRUE)
	{
		_gIsFWDn = FALSE;
	}
	else
	{
		_gIsFWDn = TRUE;
	}
}
EXPORT_SYMBOL(KHAL_DEMOD_Init_gIsFWDn);

BOOLEAN KHAL_DEMOD_Ioremap (void)
{
	int retry = 300;
	while((_gIs_ioremap == FALSE) && (retry--)) {
		usleep_range(10000,10000);
	}
	DEMOD_NOTI("ioremap %d, retry %d\n", _gIs_ioremap, 300 - retry);

	if (_gIs_ioremap == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
EXPORT_SYMBOL(KHAL_DEMOD_Ioremap);

void KHAL_DEMOD_Init_gIs_ioremap (BOOLEAN done)
{
	if ( done == TRUE)
	{
		_gIs_ioremap = FALSE;
	}
	else
	{
		_gIs_ioremap = TRUE;
	}
}
EXPORT_SYMBOL(KHAL_DEMOD_Init_gIs_ioremap);

int DEMOD_FW_Configuration_Initialize (LX_DEMOD_OPER_MODE_T operMode)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.FW_Configuration_Initialize)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.FW_Configuration_Initialize(operMode))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("Received operMode = 0x%x \n", operMode);
	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_API_Suspend(void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.API_Suspend)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.API_Suspend())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_DVB_SW_Init (void)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	if(NULL == g_demod_hal.DVB_SW_Init)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DVB_SW_Init())
		DEMOD_RETURN_FAIL(__F__);

	pDemodDev->sw_type = DEMOD_SW_TYPE_DVB;
	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVB_SW_Init);

int DEMOD_DTMB_SW_Init (void)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	if(NULL == g_demod_hal.DTMB_SW_Init)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.DTMB_SW_Init())
		DEMOD_RETURN_FAIL(__F__);

	pDemodDev->sw_type  = DEMOD_SW_TYPE_DTMB;
	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DTMB_SW_Init);

int DEMOD_ATSC_SW_Init (void)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	if(NULL == g_demod_hal.ATSC_SW_Init)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.ATSC_SW_Init())
		DEMOD_RETURN_FAIL(__F__);

	pDemodDev->sw_type  = DEMOD_SW_TYPE_ATSC;
	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC_SW_Init);

int DEMOD_VSB_SetDemod_Simple (void)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	if(NULL == g_demod_hal.VSB_SetDemod_Simple)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.VSB_SetDemod_Simple())
		DEMOD_RETURN_FAIL(__F__);

	pDemodDev->sw_type  = DEMOD_SW_TYPE_ATSC;
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_SetInclk.
 * select inclk mode
 *
 * @param inclk  [IN] LX_DEMOD_INCLK_SEL_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_SetInclk (LX_DEMOD_INCLK_SEL_T *inclk)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.SetInclk)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SetInclk(inclk))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_AdcInit (void)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.AdcInit)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.AdcInit())
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_SetPll (LX_DEMOD_OPER_MODE_T operMode)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.SetPll)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SetPll(operMode))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");
	return RET_OK;
}

int DEMOD_SetADC (LX_DEMOD_OPER_MODE_T operMode)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.SetADC)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SetADC(operMode))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}

int DEMOD_SAT_DiSeqContol (BOOLEAN OnOff)
{
	DEMOD_PRINT("Start \n");

	if(NULL == g_demod_hal.SAT_DiSeqContol)
		DEMOD_NOT_SUPPORTED(__F__);

	if( RET_OK != g_demod_hal.SAT_DiSeqContol(OnOff))
		DEMOD_RETURN_FAIL(__F__);

	DEMOD_PRINT("End \n");

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_SAT_DiSeqContol);

/** initialize HAL function list
 *
 */
static void DEMOD_InitHAL (void )
{
	DEMOD_PRINT("Start \n");
	memset( &g_demod_hal, 0x0, sizeof(DEMOD_HAL_T));

    /* initialize HAL (Hardware Abstraction Layer) */
	if(0)
	{
	}
#if defined(DEMOD_CONFIG_LGDBB)
#ifdef INCLUDE_M16P_CHIP_KDRV
	else if( lx_chip() == LX_CHIP_M16P )
	{
		DEMOD_M16P_InitHAL( &g_demod_hal );
		DEMOD_PRINT_ALWAYS("M16P DEMOD_InitHAL \n");
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip() == LX_CHIP_O18 )
	{
		DEMOD_O18_InitHAL( &g_demod_hal );
		DEMOD_PRINT_ALWAYS("O18 DEMOD_InitHAL \n");
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip() == LX_CHIP_M19 )
	{
		DEMOD_M19_InitHAL( &g_demod_hal );
		DEMOD_PRINT_ALWAYS("M19 DEMOD_InitHAL \n");
	}
#endif
#endif //if defined(DEMOD_CONFIG_LGDBB)

#if defined(DEMOD_CONFIG_LGDBB_IPC)
#if defined(DEMOD_CHIP_NAME_o20)
	else if( lx_chip() == LX_CHIP_O20 )
	{
		DEMOD_O20_InitHAL( &g_demod_hal );
		DEMOD_INFO("O20 DEMOD_InitHAL \n");
	}
#endif
#if defined(DEMOD_CHIP_NAME_e60)
	else if( lx_chip() == LX_CHIP_E60 )
	{
		DEMOD_E60_InitHAL( &g_demod_hal );
		DEMOD_INFO("E60 DEMOD_InitHAL \n");
	}
#endif
#if defined(DEMOD_CHIP_NAME_o22)
	else if( lx_chip() == LX_CHIP_O20 )	// for platform test box (cpbox)
	{
		DEMOD_O22_InitHAL( &g_demod_hal );
		DEMOD_INFO("O22 DEMOD_InitHAL \n");
	}
	else if( lx_chip() == LX_CHIP_O22 )
	{
		DEMOD_O22_InitHAL( &g_demod_hal );
		DEMOD_INFO("O22 DEMOD_InitHAL \n");
	}
#endif
#if defined(DEMOD_CHIP_NAME_m23)
	else if( lx_chip() == LX_CHIP_O20 )	// for platform test box (cpbox)
	{
		DEMOD_M23_InitHAL( &g_demod_hal );
		DEMOD_INFO("O22 DEMOD_InitHAL \n");
	}
	else if( lx_chip() == LX_CHIP_M23 )
	{
		DEMOD_M23_InitHAL( &g_demod_hal );
		DEMOD_INFO("M23 DEMOD_InitHAL \n");
	}
#endif
#if defined(DEMOD_CHIP_NAME_o24) //!//
	else if( lx_chip() == LX_CHIP_O20 )	// for platform test box (cpbox)
	{
		DEMOD_O24_InitHAL( &g_demod_hal );
		DEMOD_INFO("O22 DEMOD_InitHAL \n");
	}
	else if( lx_chip() == LX_CHIP_O24 )
	{
		DEMOD_O24_InitHAL( &g_demod_hal );
		DEMOD_INFO("O24 DEMOD_InitHAL \n");
	}
#endif
#if defined(DEMOD_CHIP_NAME_o26) //chungiii
	else if( lx_chip() == LX_CHIP_O26 )
	{
		DEMOD_O26_InitHAL( &g_demod_hal );
		DEMOD_INFO("O26 DEMOD_InitHAL \n");
	}
#endif

#endif //#if defined(DEMOD_CONFIG_LGDBB_IPC)
	else
	{
		DEMOD_PRINT_ALWAYS("DEMOD_InitHAL FAIL CHECK CHIP REV \n");
	}
	DEMOD_PRINT("DEMOD_InitHAL End \n");
}

/**
* ADC Module exit
*
* @parm void
* @return int
*/
#if 0
int DEMOD_exit (void)
{
	int ret = RET_OK;

	return ret;
}
#endif

/**
* ADC Module initialize
*
* @parm void
* @return int
*/

int DEMOD_InitHW (void)
{
	int 		ret = RET_OK;
	UINT32		reg_base = 0;
	UINT32		reg_size = 0;

	unsigned long irq_flags;
	LX_DEMOD_INCLK_SEL_T inclk = LX_DEMOD_ARM_SETTING;

	DEMOD_PRINT("Start\n");
	DEMOD_InitHAL();

	if( RET_OK != DEMOD_ResetHW())
	{
		ret = RET_ERROR;
	}

	
	switch(lx_chip()) {
	case LX_CHIP_O18:
		reg_base = DEMOD_O18_BASE_ADDR;
		reg_size = DEMOD_O18_SYSTEM_REG_SIZE;
		break;
	case LX_CHIP_M19:
		reg_base = DEMOD_M19_BASE_ADDR;
		reg_size = DEMOD_M19_SYSTEM_REG_SIZE;
		break;
	case LX_CHIP_O20:
		reg_base = DEMOD_O20_BASE_ADDR;
		reg_size = DEMOD_O20_SYSTEM_REG_SIZE;
		break;
	case LX_CHIP_E60:
		reg_base = DEMOD_E60_BASE_ADDR;
		reg_size = DEMOD_E60_SYSTEM_REG_SIZE;
		break;
	case LX_CHIP_O22:
	case LX_CHIP_M23:
	case LX_CHIP_O24: //!//
	case LX_CHIP_O26: //chungiii
		reg_base = DEMOD_IP_BASE_ADDR;
		reg_size = DEMOD_IP_SYSTEM_REG_SIZE;
		break;
	default:
		DEMOD_ERROR("not supported chip 0x%02x\n", lx_chip());
		spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);
		return RET_ERROR;
	}

	if (reg_base > 0 && reg_size > 0) {
		if (NULL == gpDEMOD_APB) {
			volatile UINT32 * temp_apb_addr = NULL;
			temp_apb_addr = (volatile UINT32 *)ioremap(reg_base, reg_size);

			if (NULL == temp_apb_addr) {
				spin_lock_irqsave(&_demod_apb_lock, irq_flags);
				_gIs_ioremap = FALSE;
				spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);
				DEMOD_ERROR("failed ioremap, base 0x%x, size 0x%x\n", reg_base, reg_size);
				return RET_ERROR;
			} else {
				spin_lock_irqsave(&_demod_apb_lock, irq_flags);
				gpDEMOD_APB = temp_apb_addr;
				szDEMOD_APB = reg_size;
				_gIs_ioremap = TRUE;
				spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);

				DEMOD_NOTI("succeed ioremap, base 0x%x, ptr %px, size 0x%x\n", reg_base, gpDEMOD_APB, szDEMOD_APB);
			}
		} else {
			spin_lock_irqsave(&_demod_apb_lock, irq_flags);
			_gIs_ioremap = TRUE;
			spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);
			DEMOD_NOTI("already ioremap done, base 0x%x, ptr %px, size 0x%x\n", reg_base, gpDEMOD_APB, szDEMOD_APB);
		}
	}

	DEMOD_PRINT("DEMOD_SetI2C\n");
	if( RET_OK != DEMOD_SetI2C())
	{
		ret = RET_ERROR;
	}

	DEMOD_PRINT("DEMOD_AdcInit\n");
	if( RET_OK != DEMOD_AdcInit())
	{
		ret = RET_ERROR;
	}

	DEMOD_PRINT("DEMOD_SetInclk\n");
	if( RET_OK != DEMOD_SetInclk(&inclk))
	{
		ret = RET_ERROR;
	}

	DEMOD_PRINT("End\n");
	return ret;
}

int DEMOD_Reg_Close (void)
{
	unsigned long irq_flags;
	volatile UINT32 * temp_apb_addr = gpDEMOD_APB;
	
	if (NULL != temp_apb_addr) {
		iounmap((void *)temp_apb_addr);
		spin_lock_irqsave(&_demod_apb_lock, irq_flags);
		gpDEMOD_APB = NULL;
		szDEMOD_APB = 0;
		spin_unlock_irqrestore(&_demod_apb_lock, irq_flags);
		
		DEMOD_NOTI("iounmap done\n");
	}

	return RET_OK;
}

void KHAL_DEMOD_PanamaOn (BOOLEAN On)
{
	if (On == TRUE)
	{
		gPanama = TRUE;
		DEMOD_PRINT_ALWAYS("[panama] [%d] ON \n", gPanama);
	}
	else
	{
		gPanama = FALSE;
		DEMOD_PRINT_ALWAYS("[panama][%d] OFF \n", gPanama);
	}
}
EXPORT_SYMBOL(KHAL_DEMOD_PanamaOn);


const char * DEMOD_Get_OPER_MODE_Name (LX_DEMOD_OPER_MODE_T oper_mode)
{
	switch (oper_mode) {
		case LX_DEMOD_DVBT:			return "DVBT";
		case LX_DEMOD_DVBT2:			return "DVBT2";
		case LX_DEMOD_ATSC:			return "ATSC";
		case LX_DEMOD_ISDBT:			return "ISDBT";
		case LX_DEMOD_DTMB:			return "DTMB";
		case LX_DEMOD_DVBC:			return "DVBC";
		case LX_DEMOD_DVBC2:			return "DVBC2";
		case LX_DEMOD_QAM:			return "QAM";
		case LX_DEMOD_ISDBC:			return "ISDBC";
		case LX_DEMOD_DVBS:			return "DVBS";
		case LX_DEMOD_DVBS2:			return "DVBS2";
		case LX_DEMOD_BS:			return "BS";
		case LX_DEMOD_CS:			return "CS";
		case LX_DEMOD_ANALOG:			return "Analog";
		case LX_DEMOD_ANALOG_Sleep:		return "AnalogSleep";
		case LX_DEMOD_DIGITAL_Sleep:		return "DigitalSleep";
		case LX_DEMOD_ALWAYSREADY:		return "AlwaysReady";
		case LX_DEMOD_ATSC3:			return "ATSC3";
		case LX_DEMOD_UNKOWN_OPMODE:		return "Unknown";
		default :							return "Invalid";
	}
}
EXPORT_SYMBOL(DEMOD_Get_OPER_MODE_Name);
