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

/*****************************************************************************
**
**  Name:DBB_DEMOD_L0_Connection.c
**
**  Description:    .
**
**  Functions
**  Implemented:
**
**  References:
**
**  Exports:
**
**  Dependencies:
**
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   20-01-2016  Jeongpil Yun    Initial draft.
**
*****************************************************************************/

#include "DBB_DEMOD_typedefs.h"
#include "DBB_DEMOD_L0_API.h"

#ifndef __EVAL_GUI__
	#include <linux/kthread.h>
	#include <linux/delay.h>
	#ifndef __KERNEL__
		#include "tu_ext_drivers.h"
	#endif
#else
	#include "../LG_IIC_Interface.h"
#endif

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __EVAL_GUI__
LX_DEMOD_L0_Context  rawI2C_context;
LX_DEMOD_L0_Context *rawI2C;
#endif

#if 0
#define  SIMULATOR_SCOPE 0xffff
int      Byte[SIMULATOR_SCOPE];
#endif

UINT8  registerDataBuffer[8];
UINT8 *pucAddressBuffer;
UINT8 *pucBuffer;
UINT8  ucAddressBuffer[4];
UINT8  ucBuffer[1000];
UINT8  cypress_checks_done    = 0;

char          *stored_error_message;
char          *DEMOD_L0_error_message;



#if 0
#endif

#ifndef __EVAL_GUI__
static OS_SEM_T chip_dev_mtx;
#endif

/** lock demod device */
void DEMOD_L0_LockDevice (void)
{
#ifndef __EVAL_GUI__
	OS_LockMutex( &chip_dev_mtx );
#endif
}

/** unlock demod device */
void DEMOD_L0_UnlockDevice (void)
{
#ifndef __EVAL_GUI__
	OS_UnlockMutex( &chip_dev_mtx );
#endif
}

void DEMOD_L0_InitDevice(void)
{
#ifndef __EVAL_GUI__
	OS_InitMutex(&chip_dev_mtx, OS_SEM_ATTR_DEFAULT);
#endif
}



/************************************************************************************************************************
  NAME: DEMOD_L0_system_wait
  DESCRIPTION:	Delay for time_ms (milliseconds)
  Parameter:  time in milliseconds
  Porting:		Replace with embedded system delay function
  Returns:		nothing
************************************************************************************************************************/
UINT32 DEMOD_L0_system_wait(int time_ms)
{
	// add a delay of time_ms based on you embedded system delay
#if 1

	#ifdef __EVAL_GUI__
		MSG msg;
		int dwStart;
		dwStart = (int) GetTickCount64(); //win7
		while(GetTickCount64() - dwStart < time_ms)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		return time_ms;

		#if 0 //winxp
		MSG msg;
		DWORD dwStart;
		dwStart = (DWORD) GetTickCount(); //winxp

		while(GetTickCount() - dwStart < dwMillisecond)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		return time_ms;
		#endif
	#else
		#ifdef __KERNEL__
//			return (UINT32)OS_MsecSleep(time_ms);
			usleep_range(time_ms*1000,(time_ms+1)*1000);
			return NO_DEMOD_ERROR;
		#else
			return (UINT32)TU_DELAY_MS(time_ms);
		#endif
	#endif
#else
	return NO_DEMOD_ERROR;
#endif

}

/************************************************************************************************************************
  DEMOD_L0_system_time function
  Use:        current system time retrieval function
              Used to retrieve the current system time in milliseconds
  Returns:    The current system time in milliseconds
  Porting:    Needs to use the final system call
************************************************************************************************************************/

UINT32 DEMOD_L0_system_time   (void)
{
	UINT32 sysTime;

#if 1

    #ifdef __EVAL_GUI__
		sysTime = (UINT32) GetTickCount64(); //win7
		return sysTime;
    #else
		#ifdef __KERNEL__
			sysTime = (UINT32)jiffies_to_msecs(jiffies);
		#else
			sysTime = (UINT32)TU_CURRENT_TIME();
		#endif

	#endif

#else
  sysTime = 0;

#endif

	return sysTime;

}

/************************************************************************************************************************
  DEMOD_L0_Init function
  Use:        layer 0 initialization function
              Used to set the layer 0 context parameters to startup values.
              It must be called first and once per Layer 1 instance (i.e. once for the tuner and once for the demodulator).
              It is automatically called by the Layer 1 init function.
  Parameters: mustReadWithoutStop has been added to manage the case when some components do not allow a stop in a 'read'.
              i2c usually allows 'write 0xc8 0x01 0x02' followed by 'read 0xc9 1' to read the byte at index 0x0102.
              This should return the same data as 'read 0xc8 0x01 0x02 1'.
              If this is not allowed, set mustReadWithoutStop at 1.
              NB: at the date of writing, this behavior has only been detected in the RDA5812 satellite tuner.
  Returns:    void
  Porting:    If some members of the LX_DEMOD_L0_Context structure are removed, they need to be removed from here too
************************************************************************************************************************/
void    DEMOD_L0_Init              (LX_DEMOD_L0_Context* i2c)
{
	(i2c)->slvAddr		= 0;
	(i2c)->indexSize		= 0;

}

/************************************************************************************************************************
  DEMOD_L0_SetAddress function
  Use:        function to set the device address
              Used to set the I2C address of the component.
              It must be called only once at startup per Layer 1 instance, as the addresses are not expected to change over time.
  Returns:    1 if OK, 0 otherwise
************************************************************************************************************************/
UINT8   DEMOD_L0_SetAddress			(LX_DEMOD_L0_Context* i2c, UINT32 add, UINT8 addSize)
{
 	(i2c)->slvAddr   	= (UINT8)add;
  	(i2c)->indexSize	= addSize;

  return NO_DEMOD_ERROR;
}

/************************************************************************************************************************
  DEMOD_L0_ReadBytes function
  Use:        lowest layer read function
              Used to read a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c read function
************************************************************************************************************************/
UINT8     DEMOD_L0_ReadBytes (LX_DEMOD_L0_Context*  i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	UINT8 subAddr[2];
	//UINT8 y;
	subAddr[0] = (UINT8)((Addr >> 8) & 0xFF);
	subAddr[1] = (UINT8)(Addr & 0xFF);
#if 1
	#ifdef __EVAL_GUI__
		UINT8 err=0;
		err = LG_IIC_ReadType2HS((i2c->slvAddr)>>1, subAddr[0], subAddr[1], iNbBytes, pucDataBuffer);
		return NO_DEMOD_ERROR;
	#else

		#ifdef __KERNEL__
			  if (RET_OK != DEMOD_I2C_Read(Addr, iNbBytes, pucDataBuffer))
			  {
				DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Read - retry !!!\n", __F__, __L__);

				if (RET_OK != DEMOD_I2C_Read(Addr, iNbBytes, pucDataBuffer))
				{
					DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Read - retry !!!\n", __F__, __L__);
					return ERROR_DEMOD_READ;
				}
			  }

		#else

			if (TU_RET_OK != TU_I2C_Read(i2c->handle, i2c->indexSize, subAddr, iNbBytes, pucDataBuffer))
			{
		  		TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Read H[0x%0x] - retry !!!\n", __F__, __L__, i2c->handle);

		  		if (TU_RET_OK != TU_I2C_Read(i2c->handle, i2c->indexSize, subAddr, iNbBytes, pucDataBuffer))
		  		{
			  		TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Read H[0x%0x] !!!\n", __F__, __L__, i2c->handle);
					return ERROR_DEMOD_READ;
		  		}
			}
		#endif
	#endif

	#if 0
		DBB_PRINT("  %s i2c->slvAddr = 0x%x....\n", __F__,i2c->slvAddr);
		DBB_PRINT("  %s i2c->handle = 0x%x....\n", __F__,i2c->handle);
		DBB_PRINT("  %s Addr = 0x%x....\n", __F__,(subAddr[0] << 8)+ subAddr[1]);
		DBB_PRINT("  %s iNbBytes = 0x%x....\n", __F__,iNbBytes);
		for(y=0;y<iNbBytes;y++)
		{
			DBB_PRINT("  %s pucDataBuffer[%d] = 0x%x....\n", __F__, y, *(pucDataBuffer+y));
		}
	#endif
#endif
  return  NO_DEMOD_ERROR;

}

/************************************************************************************************************************
  DEMOD_L0_WriteBytes function
  Use:        lowest layer write function
              Used to write a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to write.
              iNbBytes, the number of bytes to write.
              *pbtDataBuffer, a pointer to a buffer containing the bytes to write.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c write function
************************************************************************************************************************/
UINT8     DEMOD_L0_WriteBytes        (LX_DEMOD_L0_Context* i2c,  UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	UINT8 subAddr[2];
	//UINT8 y;
	subAddr[0] = (UINT8)((Addr >> 8) & 0xFF);
	subAddr[1] = (UINT8)(Addr & 0xFF);

#if 1
	#ifdef __EVAL_GUI__
		UINT8 err=0;
		err = LG_IIC_WriteType2HS((i2c->slvAddr)>>1, subAddr[0], subAddr[1], iNbBytes, pucDataBuffer);

		//DBB_PRINT("  i2c->slvAddr = 0x%x....\n",i2c->slvAddr);
		//DBB_PRINT("  i2c->handle = 0x%x....\n", i2c->handle);
		//DBB_PRINT("  Addr = 0x%x....\n", (subAddr[0] << 8)+ subAddr[1]);
		//DBB_PRINT("  iNbBytes = 0x%x....\n", iNbBytes);
		//DBB_PRINT("  err = 0x%x....\n", err);
		return NO_DEMOD_ERROR;
	#else

		#ifdef __KERNEL__  // For SoC internal demod

			if (RET_OK != DEMOD_I2C_Write(Addr, iNbBytes, pucDataBuffer))
			{
				DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Write - retry !!!\n", __F__, __L__);

				if (RET_OK != DEMOD_I2C_Write(Addr, iNbBytes, pucDataBuffer))
				{
					DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Write - retry !!!\n", __F__, __L__);
					return ERROR_DEMOD_WRITE;
				}
			}

		#else  // for external demod in LG DTV platform.

			if (TU_RET_OK != TU_I2C_Write(i2c->handle, i2c->indexSize, subAddr,  iNbBytes, pucDataBuffer))
			{
				TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Write H[0x%0x] - retry !!!\n", __F__, __L__, i2c->handle);

				if (TU_RET_OK != TU_I2C_Write(i2c->handle, i2c->indexSize, subAddr, iNbBytes, pucDataBuffer))
				{
					TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Write H[0x%0x] !!!\n", __F__, __L__, i2c->handle);
					return ERROR_DEMOD_WRITE;
				}
			}
		#endif
	#endif

	#if 0
		DBB_PRINT("  %s i2c->slvAddr = 0x%x....\n", __F__,i2c->slvAddr);
		DBB_PRINT("  %s i2c->handle = 0x%x....\n", __F__,i2c->handle);
		DBB_PRINT("  %s Addr = 0x%x....\n", __F__,(subAddr[0] << 8)+ subAddr[1]);
		DBB_PRINT("  %s iNbBytes = 0x%x....\n", __F__,iNbBytes);
		for(y=0;y<iNbBytes;y++)
		{
			DBB_PRINT("  %s pucDataBuffer[%d] = 0x%x....\n", __F__, y, *(pucDataBuffer+y));
		}
	#endif

#endif
	return NO_DEMOD_ERROR;

}

/************************************************************************************************************************
  DEMOD_L0_Fast_ReadBytes function
  Use:        lowest layer fast read function
              Used to read a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c read function
************************************************************************************************************************/
UINT8     DEMOD_L0_Fast_ReadBytes (LX_DEMOD_L0_Context*  i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	UINT8 subAddr[2];
//	UINT8 y;

	subAddr[0] = (UINT8)((Addr >> 8) & 0xFF);
	subAddr[1] = (UINT8)(Addr & 0xFF);

#if 1
	#ifdef __EVAL_GUI__
		UINT8 err=0;
		err = LG_IIC_ReadType2HS((i2c->slvAddr)>>1, subAddr[0], subAddr[1], iNbBytes, pucDataBuffer);
		//printf("read i2c->slvAddr = %x / pucDataBuffer = %x", i2c->slvAddr, pucDataBuffer[0]);
		return NO_DEMOD_ERROR;
	#else

		#ifdef __KERNEL__
			  if (RET_OK != DEMOD_I2C_Read(Addr, iNbBytes, pucDataBuffer))
			  {
				DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Read - retry !!!\n", __F__, __L__);

				if (RET_OK != DEMOD_I2C_Read(Addr, iNbBytes, pucDataBuffer))
				{
					DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Read - retry !!!\n", __F__, __L__);
					return ERROR_DEMOD_READ;
				}
			  }

		#else

			if (TU_RET_OK != TU_I2C_FastRead(i2c->handle, i2c->indexSize, subAddr, iNbBytes, pucDataBuffer))
			{
		  		TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Read H[0x%0x] - retry !!!\n", __F__, __L__, i2c->handle);

		  		if (TU_RET_OK != TU_I2C_FastRead(i2c->handle, i2c->indexSize, subAddr, iNbBytes, pucDataBuffer))
		  		{
			  		TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Read H[0x%0x] !!!\n", __F__, __L__, i2c->handle);
					return ERROR_DEMOD_READ;
		  		}
			}
		#endif
	#endif

	#if 0
		DBB_PRINT("  %s i2c->slvAddr = 0x%x....\n", __F__,i2c->slvAddr);
		DBB_PRINT("  %s i2c->handle = 0x%x....\n", __F__,i2c->handle);
		DBB_PRINT("  %s Addr = 0x%x....\n", __F__,(subAddr[0] << 8)+ subAddr[1]);
		DBB_PRINT("  %s iNbBytes = 0x%x....\n", __F__,iNbBytes);
		for(y=0;y<iNbBytes;y++)
		{
			DBB_PRINT("  %s pucDataBuffer[%d] = 0x%x....\n", __F__, y, *(pucDataBuffer+y));
		}
	#endif
#endif

  return  NO_DEMOD_ERROR;

}

/************************************************************************************************************************
  DEMOD_L0_Fast_WriteBytes function
  Use:        lowest layer fast write function
              Used to write a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to write.
              iNbBytes, the number of bytes to write.
              *pbtDataBuffer, a pointer to a buffer containing the bytes to write.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c write function
************************************************************************************************************************/
UINT8     DEMOD_L0_Fast_WriteBytes        (LX_DEMOD_L0_Context* i2c,  UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	UINT8 subAddr[2];
//	UINT8 y;
	subAddr[0] = (UINT8)((Addr >> 8) & 0xFF);
	subAddr[1] = (UINT8)(Addr & 0xFF);

#if 1
	#ifdef __EVAL_GUI__
		UINT8 err=0;
		err = LG_IIC_WriteType2HS((i2c->slvAddr)>>1, subAddr[0], subAddr[1], iNbBytes, pucDataBuffer);
		return NO_DEMOD_ERROR;
	#else

		#ifdef __KERNEL__

			if (RET_OK != DEMOD_I2C_Write(Addr, iNbBytes, pucDataBuffer))
			{
				DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Write - retry !!!\n", __F__, __L__);

				if (RET_OK != DEMOD_I2C_Write(Addr, iNbBytes, pucDataBuffer))
				{
					DEMOD_PRINT("[DBB I2C] FAIL (%s:%d) DEMOD_I2C_Write - 2nd !!!\n", __F__, __L__);
					return ERROR_DEMOD_WRITE;
				}
			}

		#else

			if (TU_RET_OK != TU_I2C_FastWrite(i2c->handle, i2c->indexSize, subAddr,  iNbBytes, pucDataBuffer))
			{
				TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Write H[0x%0x] - retry !!!\n", __F__, __L__, i2c->handle);

				if (TU_RET_OK != TU_I2C_FastWrite(i2c->handle, i2c->indexSize, subAddr, iNbBytes, pucDataBuffer))
				{
					TU_PRINT(PRN_CRI, "^r^[T_  I2C] FAIL (%s:%d) TU_I2C_Write H[0x%0x] - 2nd !!!\n", __F__, __L__, i2c->handle);
					return ERROR_DEMOD_WRITE;
				}
			}
		#endif
	#endif

	#if 0
		DBB_PRINT("  %s i2c->slvAddr = 0x%x....\n", __F__,i2c->slvAddr);
		DBB_PRINT("  %s i2c->handle = 0x%x....\n", __F__,i2c->handle);
		DBB_PRINT("  %s Addr = 0x%x....\n", __F__,(subAddr[0] << 8)+ subAddr[1]);
		DBB_PRINT("  %s iNbBytes = 0x%x....\n", __F__,iNbBytes);
		for(y=0;y<iNbBytes;y++)
		{
			DBB_PRINT("  %s pucDataBuffer[%d] = 0x%x....\n", __F__, y, *(pucDataBuffer+y));
		}
	#endif
#endif
	return  NO_DEMOD_ERROR;

}

/************************************************************************************************************************
  DEMOD_L0_ReadCommandBytes function
  Use:        'command mode' bytes reading function
              Used to read a given number of bytes from the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to read.
              *pucDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
************************************************************************************************************************/
UINT8     DEMOD_L0_ReadCommandBytes  (LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{

#ifdef __KERNEL__
	//DBB_PRINT("/////////////////////// i2c->chipVer %x \n", i2c->chipVer);
	#ifndef FPGA_CPBOX
		if(i2c->chipVer >= L18F)
		{
			//DBB_PRINT("Read i2c->chipVer == L18F \n");
			UINT32 pucWordData=0;
			UINT8 err=0, i;

			if(i2c->chipVer >= M16P3)
			{
				Addr = Addr - 0x9c00;
			}
		
			err = DEMOD_L0_ReadWord (i2c, Addr, &pucWordData);

			for(i=0;i<iNbBytes;i++)
			{
				*(pucDataBuffer+i) = (pucWordData >> (8*i)) & 0xff;
			}

			return err;
		}
	#else
		if(i2c->chipVer >= L18F)
		{
			UINT8 Addr_Msb, Addr_Lsb, nByte;
			UINT8 extend[4] = {0, 3, 2, 1};

			nByte = iNbBytes;
			Addr_Msb = ((Addr >> 10) | (i2c->inDirect << 7));
			Addr_Lsb = (Addr >> 2);

			Addr = ((Addr_Msb << 8) | Addr_Lsb);
			iNbBytes = nByte + extend[nByte%4];
		}
	#endif

#else

	if(i2c->chipVer >= L18F)
	{
		UINT8 Addr_Msb, Addr_Lsb, nByte;
		UINT8 extend[4] = {0, 3, 2, 1};

		if(i2c->chipVer >= M16P3)
		{
			if(i2c->fwDone == 1)
			{
				Addr = Addr - 0x9c00;
			}
		}
			
		nByte = iNbBytes;
		Addr_Msb = ((Addr >> 10) | (i2c->inDirect << 7));
		Addr_Lsb = (Addr >> 2);

		Addr = ((Addr_Msb << 8) | Addr_Lsb);
		iNbBytes = nByte + extend[nByte%4];
	}
#endif

	return DEMOD_L0_ReadBytes (i2c, Addr, iNbBytes, pucDataBuffer);

}

/************************************************************************************************************************
  DEMOD_L0_WriteCommandBytes function
  Use:        'command mode' bytes writing function
              Used to write a given number of bytes to the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to write.
              *pucDataBuffer, a pointer to a buffer containing the bytes.
  Returns:    the number of bytes written.
************************************************************************************************************************/
UINT8     DEMOD_L0_WriteCommandBytes (LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
#ifdef __KERNEL__
	#ifndef FPGA_CPBOX
		if(i2c->chipVer >= L18F)
		{
			UINT8 iNbWords, i;
			UINT8 err=0;
			UINT8 extend[4] = {0, 1, 1, 1};
			UINT32 pucWordData;

			if(i2c->chipVer >= M16P3)
			{
				Addr = Addr - 0x9c00;
			}
		
			iNbWords = iNbBytes/4 + extend[iNbBytes%4];
			for(i=0;i<iNbWords;i++)
			{
				pucWordData = (*(pucDataBuffer+i*4+3) << 24) | (*(pucDataBuffer+i*4+2) << 16) | (*(pucDataBuffer+i*4+1) << 8) | *(pucDataBuffer+i*4);
				err |= DEMOD_L0_WriteWord(i2c,  Addr+i*4, &pucWordData);
			}

			return err;
		}
	#else
		if(i2c->chipVer >= L18F)
		{
			UINT8 Addr_Msb, Addr_Lsb, nByte;
			UINT8 extend[4] = {0, 3, 2, 1};

			nByte = iNbBytes;
			Addr_Msb = ((Addr >> 10) | (i2c->inDirect << 7));
			Addr_Lsb = (Addr >> 2);

			Addr = ((Addr_Msb << 8) | Addr_Lsb);
			iNbBytes = nByte + extend[nByte%4];
		}
	#endif
#else
	if(i2c->chipVer >= L18F)
	{
		UINT8 Addr_Msb, Addr_Lsb, nByte;
		UINT8 extend[4] = {0, 3, 2, 1};

		if(i2c->chipVer >= M16P3)
		{
			if(i2c->fwDone == 1)
			{
				Addr = Addr - 0x9c00;
			}
		}
			
		nByte = iNbBytes;
		Addr_Msb = ((Addr >> 10) | (i2c->inDirect << 7));
		Addr_Lsb = (Addr >> 2);

		Addr = ((Addr_Msb << 8) | Addr_Lsb);
		iNbBytes = nByte + extend[nByte%4];
	}
#endif

	return DEMOD_L0_WriteBytes(i2c, Addr, iNbBytes, pucDataBuffer);
 }

/************************************************************************************************************************
  DEMOD_L0_Fast_ReadCommandBytes function
  Use:        'command mode' bytes reading function
              Used to read a given number of bytes from the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to read.
              *pucDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
************************************************************************************************************************/
UINT8     DEMOD_L0_Fast_ReadCommandBytes  (LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{

	return DEMOD_L0_Fast_ReadBytes (i2c, Addr, iNbBytes, pucDataBuffer);

}

/************************************************************************************************************************
  DEMOD_L0_Fast_WriteCommandBytes function
  Use:        'command mode' bytes fast writing function for downlaoding firmware
              Used to write a given number of bytes to the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to write.
              *pucDataBuffer, a pointer to a buffer containing the bytes.
  Returns:    the number of bytes written.
************************************************************************************************************************/
UINT8     DEMOD_L0_Fast_WriteCommandBytes (LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	return DEMOD_L0_Fast_WriteBytes(i2c,  Addr, iNbBytes, pucDataBuffer);
 }

/************************************************************************************************************************
  DEMOD_L0_WordToByte function
  Use:        'command mode' bytes fast writing function for downlaoding firmware
              Used to write a given number of bytes to the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to write.
              *pucDataBuffer, a pointer to a buffer containing the bytes.
  Returns:    the number of bytes written.
************************************************************************************************************************/
void	DEMOD_L0_WordToByte (UINT32 wordData, UINT8 *wrData)
{
	wrData[0] = wordData 		 & 0xff;
	wrData[1] = (wordData >> 8   ) & 0xff;
	wrData[2] = (wordData >> 16 ) & 0xff;
	wrData[3] = (wordData >> 24 ) & 0xff;
}


/************************************************************************************************************************
  DEMOD_L0_ReadWord function
  Use:        lowest layer read function
              Used to read a word from the Layer 1 instance.
  Parameters: a pointer to the Layer 0 context.
              *pucWordData, a pointer to a buffer used to store the word.
  Returns:    the number of words read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final apb read function
************************************************************************************************************************/
UINT8     DEMOD_L0_ReadWord (LX_DEMOD_L0_Context*  i2c, UINT32 Addr, UINT32 *pucWordData)
{
#ifdef __KERNEL__
	if(i2c->chipVer >= M16P3)
	{
		Addr = Addr - 0x5400;
	}
	else
	{
		Addr = Addr - 0xF000;
	}
		
	if (RET_OK != DEMOD_APB_Read(Addr, pucWordData))
	{
		DEMOD_PRINT("[DBB APB] FAIL (%s:%d) DEMOD_APB_Read - retry !!!\n", __F__, __L__);

		if (RET_OK != DEMOD_APB_Read(Addr, pucWordData))
		{
			DEMOD_PRINT("[DBB APB] FAIL (%s:%d) DEMOD_APB_Read - retry !!!\n", __F__, __L__);
			return ERROR_DEMOD_READ;
		}
	}

#else

#endif

  return  NO_DEMOD_ERROR;

}

/************************************************************************************************************************
  DEMOD_L0_WriteWords function
  Use:        lowest layer write function
              Used to write a given number of bytes from the Layer 1 instance.
  Parameters: a pointer to the Layer 0 context.
              *pbtDataBuffer, a pointer to a buffer containing the words to write.
  Returns:    the number of words read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final apb write function
************************************************************************************************************************/
UINT8     DEMOD_L0_WriteWord (LX_DEMOD_L0_Context* i2c,  UINT32 Addr, UINT32 *pucWordData)
{
#ifdef __KERNEL__  // For SoC internal demod
	if(i2c->chipVer >= M16P3)
	{
		Addr = Addr - 0x5400;
	}
	else
	{
		Addr = Addr - 0xF000;
	}
		
	if (RET_OK != DEMOD_APB_Write(Addr, pucWordData))
	{
		printk("[DBB APB] FAIL (%s:%d) DEMOD_APB_Write - retry !!!\n", __F__, __L__);

		if (RET_OK != DEMOD_APB_Write(Addr, pucWordData))
		{
			printk("[DBB APB] FAIL (%s:%d) DEMOD_APB_Write - retry !!!\n", __F__, __L__);
			return ERROR_DEMOD_WRITE;
		}
	}

#else  // for external demod in LG DTV platform.

#endif

	return NO_DEMOD_ERROR;

}


#ifdef    __cplusplus
}
#endif /* __cplusplus */

