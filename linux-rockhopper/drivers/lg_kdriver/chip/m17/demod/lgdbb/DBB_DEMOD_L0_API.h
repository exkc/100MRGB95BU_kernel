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
**  Name:DBB_DEMOD_L0_API.h
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

#ifndef _DBB_DEMOD_L0_API_H_
#define _DBB_DEMOD_L0_API_H_

#include "DBB_DEMOD_typedefs.h"

#ifndef __KERNEL__
#ifndef __EVAL_GUI__
#include "tu_common.h"
#endif
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


typedef struct LX_DEMOD_L0_Context
{
    UINT8	slvAddr;
    UINT8	indexSize;
	UINT8	inDirect;	
    UINT8 	chipVer;
    UINT8 	chipRev;
    UINT32  handle;
    UINT32  cmdAddr;
    UINT32  rspAddr;
	UINT8	fwDone;
} LX_DEMOD_L0_Context;



/* Layer 1 core types definitions */

typedef struct LX_DEMOD_L0_RDA5815M_CONTEXT_T
{
	LX_DEMOD_L0_Context    *i2c;
	LX_DEMOD_L0_Context 	i2cObj;
	int    RF;
	int    IF;
	int    minRF;
	int    maxRF;
	int    LPF;
	float  rssi;
	unsigned char Status;
	unsigned char bytes[40];
	unsigned int loopthrough;
} LX_DEMOD_L0_RDA5815M_CONTEXT_T;




extern UINT32		DEMOD_L0_system_wait    (int time_ms);
extern UINT32		DEMOD_L0_system_time    (void);
extern void		DEMOD_L0_LockDevice (void);
extern void		DEMOD_L0_UnlockDevice (void);
extern void		DEMOD_L0_InitDevice(void);


extern void	 DEMOD_L0_Init(LX_DEMOD_L0_Context* i2c); /* initialize the Layer 0 DLL. It sets the layer 0 context parameters to startup values. It must be called first. It is automatically called by the Layer 1 init function.*/
extern UINT8   DEMOD_L0_SetAddress(LX_DEMOD_L0_Context* i2c, UINT32 add, UINT8 addSize) ;
extern UINT8   DEMOD_L0_ReadBytes(LX_DEMOD_L0_Context*  i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer) ;/* read  iNbBytes bytes from the IP. A buffer large enough to hold the values needs to be reserved by the upper layer.*/
extern UINT8   DEMOD_L0_WriteBytes(LX_DEMOD_L0_Context* i2c,  UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer); /* write iNbBytes bytes in the IP. The referenced buffer contains the bytes to be written.*/

extern UINT8   DEMOD_L0_Fast_ReadBytes(LX_DEMOD_L0_Context*  i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer) ;/* read  iNbBytes bytes from the IP. A buffer large enough to hold the values needs to be reserved by the upper layer.*/
extern UINT8   DEMOD_L0_Fast_WriteBytes(LX_DEMOD_L0_Context* i2c,  UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer); /* write iNbBytes bytes in the IP. The referenced buffer contains the bytes to be written.*/

extern UINT8   DEMOD_L0_ReadCommandBytes(LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);
extern UINT8   DEMOD_L0_WriteCommandBytes(LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);

extern UINT8   DEMOD_L0_Fast_ReadCommandBytes(LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);
extern UINT8   DEMOD_L0_Fast_WriteCommandBytes(LX_DEMOD_L0_Context* i2c, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);

extern void	DEMOD_L0_WordToByte (UINT32 wordData, UINT8 *wrData);
extern UINT8  DEMOD_L0_ReadWord (LX_DEMOD_L0_Context*  i2c, UINT32 Addr, UINT32 *pucWordData);
extern UINT8  DEMOD_L0_WriteWord (LX_DEMOD_L0_Context* i2c, UINT32 Addr, UINT32 *pucWordData);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DBB_DEMOD_L0_API_H_*/

