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


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.02.19
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

#ifndef _DE_IO_h
#define _DE_IO_h
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_IO_SetMcuSuspend(UINT32 arg);
int DE_IO_Resume(unsigned long arg);
int DE_IO_IPC_Init(unsigned long arg);
int DE_IO_IPC_Cleanup(unsigned long arg);
int DE_IO_SupportInitData(void);
int DE_IO_SetInitData(void);
int DE_IO_Init(unsigned long arg,unsigned int nFlag);
int DE_IO_GetFirmwareInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_GetInputWin(unsigned long arg,unsigned int nFlag);
int DE_IO_GetOutWin(unsigned long arg,unsigned int nFlag);
int DE_IO_SetInputWin(unsigned long arg,unsigned int nFlag);
int DE_IO_SetOutWin(unsigned long arg,unsigned int nFlag);
int DE_IO_SetWinInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_GetWinInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_SetDisOut(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCviSrcType(unsigned long arg,unsigned int nFlag);
int DE_IO_GetMviColorimetry(unsigned long arg,unsigned int nFlag);
int DE_IO_SetZList(unsigned long arg,unsigned int nFlag);
int DE_IO_SetDisFmt(unsigned long arg,unsigned int nFlag);
int DE_IO_SetFrRate(unsigned long arg,unsigned int nFlag);
int DE_IO_SetBgColor(unsigned long arg,unsigned int nFlag);
int DE_IO_SetWinBlank(unsigned long arg,unsigned int nFlag);
int DE_IO_MultiWinEnable(unsigned long arg,unsigned int nFlag);
int DE_IO_RegRd(unsigned long arg,unsigned int nFlag);
int DE_IO_RegWr(unsigned long arg,unsigned int nFlag);
int DE_IO_GetOutFrRate(unsigned long arg,unsigned int nFlag);
int DE_IO_SetDeinterlace(unsigned long arg,unsigned int nFlag);
int DE_IO_SetUDMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCve(unsigned long arg,unsigned int nFlag);
int DE_IO_SetVcs(unsigned long arg,unsigned int nFlag);
int DE_IO_SetUart4MCU(unsigned long arg,unsigned int nFlag);

#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_IO_FW_Download(unsigned long arg,unsigned int nFlag);
#endif
int DE_IO_SetCviFir(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCviTpg(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCviCsampleMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetDvrFmtCtrl(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSubScFreeze(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCviVideoFrameBuffer(unsigned long arg,unsigned int nFlag);
int DE_IO_SelectMultiWinSrc(unsigned long arg,unsigned int nFlag);
int DE_IO_SetScartRGBBypassMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCviFreeze(unsigned long arg,unsigned int nFlag);
int DE_IO_GetDebug(unsigned long arg,unsigned int nFlag);
int DE_IO_SetDebug(unsigned long arg,unsigned int nFlag);
int DE_IO_SetLowDelay(unsigned long arg,unsigned int nFlag);
int DE_IO_GetLowDelay(unsigned long arg,unsigned int nFlag);
int DE_IO_Set3DInOutCtrl(unsigned long arg,unsigned int nFlag);

int DE_IO_SetInterfaceConfig(unsigned long arg,unsigned int nFlag);
int DE_IO_GetSystemStatus(unsigned long arg,unsigned int nFlag);
int DE_IO_GetSourceStatus(unsigned long arg,unsigned int nFlag);
int DE_IO_SetOperation(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSubOperation(unsigned long arg,unsigned int nFlag);
int DE_IO_SetCaptureControl(unsigned long arg,unsigned int nFlag);
int DE_IO_SetMultiVision(unsigned long arg,unsigned int nFlag);
int DE_IO_SetVTM(unsigned long arg,unsigned int nFlag);
int DE_IO_ResetVTM(unsigned long arg,unsigned int nFlag);
int DE_IO_GetVTM(unsigned long arg,unsigned int nFlag);
int DE_IO_SetVTMBlockState(unsigned long arg,unsigned int nFlag);
int DE_IO_GetScalerInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_SetInnerPattern(unsigned long arg,unsigned int nFlag);
int DE_IO_SetWinPortSrc(unsigned long arg,unsigned int nFlag);
int DE_IO_SetWinFreeze(unsigned long arg,unsigned int nFlag);
int DE_IO_VerifyFirmware(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSrcMirror(unsigned long arg,unsigned int nFlag);
int DE_IO_SetActFmtDetect(unsigned long arg,unsigned int nFlag);
int DE_IO_SetHDMIPort(unsigned long arg,unsigned int nFlag);
int DE_IO_GetCapacity(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSubWindow(unsigned long arg,unsigned int nFlag);
int DE_IO_GetLocalMuteValue(unsigned long arg,unsigned int nFlag);
int DE_IO_SetFrameDelay(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSubMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSubShape(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSignageMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetHDMITXInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_SetGeneralCapturePath(unsigned long arg,unsigned int nFlag);
int DE_IO_SetSourceSizeWin(unsigned long arg,unsigned int nFlag);
int DE_IO_InitFCW(unsigned long arg,unsigned int nFlag);
int DE_IO_DualModeEnable(unsigned long arg,unsigned int nFlag);
int DE_IO_SetIPCHDRMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetIPCPDMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetLowDelayBySourceSync(unsigned long arg,unsigned int nFlag);
int DE_IO_SetHighFrameRate(unsigned long arg,unsigned int nFlag);
int DE_IO_GetDisplayType(UINT32 *disp_type);
int DE_IO_SetRotate(unsigned long arg,unsigned int nFlag);
int DE_IO_SetTestPattern(unsigned long arg,unsigned int nFlag);
int DE_IO_SetLatencyMeasure(unsigned long arg,unsigned int nFlag);
int DE_IO_GetFPPInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_GetMEMInfo(unsigned long arg,unsigned int nFlag);
int DE_IO_GetPQE_DNNResult(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_IO_GetTimeDiff(unsigned long arg, unsigned int nFlag);
int DE_IO_SetDftMode(UINT32 mode);
int DE_IO_SetNetworkSync(unsigned long arg);
int DE_IO_SetVTVInputPosition(unsigned long arg);
int DE_IO_GetVideoDelay(unsigned long arg,unsigned int nFlag);
int DE_IO_GetSharedMem(unsigned long arg);
int DE_IO_SetSharedMem(unsigned long arg);
int DE_IO_SetGPSControl(unsigned long arg);
int DE_IO_ReleaseVTM(unsigned long arg);
int DE_IO_SetOrbit(unsigned long arg,unsigned int nFlag);
int DE_IO_SetGPSDMA(unsigned long arg);
int DE_IO_UserSetGPSDMA(unsigned long arg, unsigned int nFlag);
int DE_IO_SetScanMode(unsigned long arg,unsigned int nFlag);
int DE_IO_SetPixelToPixel(unsigned long arg,unsigned int nFlag);
int DE_IO_GetHistoBufferRange(UINT32 *start,UINT32 *end);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif
/**  @} */
