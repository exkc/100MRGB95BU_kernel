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
**  Name:DBB_DEMOD_L1_API.h
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

#ifndef    _DBB_DEMOD_L1_API_H_
#define    _DBB_DEMOD_L1_API_H_

#include "DBB_DEMOD_typedefs.h"
#include "DBB_DEMOD_L0_API.h"
#include "DBB_DEMOD_L1_Properties.h"
#include "DBB_DEMOD_L1_Commands.h"


typedef struct
{
  LX_DEMOD_L0_Context          *i2c;
  LX_DEMOD_L0_Context          i2cObj;
  LX_DEMOD_L1_CmdObj           *cmd;
  LX_DEMOD_L1_CmdObj            cmdObj;
  LX_DEMOD_L1_CmdReplyObj      *rsp;
  LX_DEMOD_L1_CmdReplyObj       rspObj;
  LX_DEMOD_L1_PropObj          *prop;
  LX_DEMOD_L1_PropObj           propObj;
  LX_DEMOD_L1_PropObj          *propShadow;
  LX_DEMOD_L1_PropObj           propShadowObj;
  LX_DEMOD_COMMON_REPLY_struct *status;
  LX_DEMOD_COMMON_REPLY_struct  statusObj;
  UINT8 						bIsStandby; //lgit
  UINT8                         standard;
  UINT8                         media;
  UINT8							propertyWriteMode;                 // Selection of DOWNLOAD_ALWAYS/DOWNLOAD_ON_CHANGE
  UINT8 command;
  UINT8 cmdByte;
  UINT8 rspByte;
  UINT32 handle;
  UINT32 cmdAddr;
  UINT32 rspAddr;
  UINT32 valid_symrate;  
} LX_DEMOD_L1_Context;


extern UINT8  DEMOD_L1_API_Init   (LX_DEMOD_L1_Context *api, UINT32 add);
extern UINT8  DEMOD_L1_API_Patch_I     (LX_DEMOD_L1_Context *api, UINT16 addr, UINT32 iNbBytes, UINT8 *pucDataBuffer);
extern UINT8  DEMOD_L1_API_Patch_D     (LX_DEMOD_L1_Context *api, UINT16 addr, UINT32 iNbBytes, UINT8 *pucDataBuffer);
extern UINT8  DEMOD_L1_API_LoadFirmware_IRAM	(LX_DEMOD_L1_Context *api, LX_DEMOD_FIRMWARE_STRUCT fw_table[], UINT8 nbLines);
extern UINT8  DEMOD_L1_API_LoadFirmware_DRAM(LX_DEMOD_L1_Context *api, LX_DEMOD_FIRMWARE_STRUCT fw_table[], UINT8 nbLines);
extern UINT8  DEMOD_L1_API_InitFirmware(LX_DEMOD_L1_Context *api);
extern UINT8  DEMOD_L1_API_StartFirmware(LX_DEMOD_L1_Context *api);
extern char*  DEMOD_L1_API_Error_Text(UINT8  error_code);
extern char*  DEMOD_L1_API_StandardName (UINT8  standard);
extern void  DEMOD_L0_WordToByte (UINT32 wordData, UINT8 *wrData);
#ifndef LG3307_API
extern UINT8  DEMOD_L1_API_LoadFirmware_MEM	(LX_DEMOD_L1_Context *api, UINT32 baseAddr);
extern UINT8  DEMOD_L1_API_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr);
extern UINT8  DEMOD_L1_API_Emergency_Alarm	(LX_DEMOD_L1_Context *api, UINT8 *eAlarm);
extern UINT8  DEMOD_L1_API_DVBT2_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2);
extern UINT8  DEMOD_L1_API_DVB_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3);
extern UINT8  DEMOD_L1_API_DTMB_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr);
#endif

#endif //_DBB_DEMOD_L1_API_H_ //

