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
 * author     LGSI (kanthiraj.s@lge.com)
 * version    1.0
 * date       2015.04.14
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

#ifndef _DE_PROC_CMN_H_
#define _DE_PROC_CMN_H_
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define MAX_CHAR_LENGTH	50
typedef struct DE_FUNCLIST{
	char sName[MAX_CHAR_LENGTH];
	int iFunc_no;
}DE_FUNCLIST;

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define MAX_DBG_FUNC				0x30
#define ENABLE_PROC_FUNCTION 1

#define CALL_IO(func) { \
	if(1){ret = func(arg,1);} /*\
	ret = __push_ioc_buf(cmd, #func, arg);\
	__pop_ioc_buf(0, cmd);*/ }

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef int (*DE_Func_Debugger_ptr_t)( int );
typedef int (*DE_Assign_Debug_Gbl_ptr_t)( int, int, int );

/*----------------------------------------------------------------------------------------
 *   Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_DBG_SetPanelType_Idx1 (int iDefArgs);
int DE_DBG_GetFirmwareInfo_Idx2 (int iDefArgs);
int DE_DBG_GetSystemStatus_Idx3 (int iDefArgs);
int DE_DBG_SetInterfaceConfig_Idx4 (int iDefArgs);
int DE_DBG_SetDisplayFormat_Idx5 (int iDefArgs);
int DE_DBG_SetFrameRate_Idx6 (int iDefArgs);
int DE_DBG_GetFrameRate_Idx7 (int iDefArgs);
int DE_DBG_SetDisplayOut_Idx8 (int iDefArgs);
int DE_DBG_SetWinPortSrc_Idx9 (int iDefArgs);
int DE_DBG_SetCviSrcType_IdxA (int iDefArgs);
int DE_DBG_SetCviFir_IdxB (int iDefArgs);
int DE_DBG_SetCviCsampleMode_IdxC (int iDefArgs);
int DE_DBG_GetScalerInfo_IdxD (int iDefArgs);
int DE_DBG_SetSrcMirror_IdxE (int iDefArgs);
int DE_DBG_GetInputWin_IdxF (int iDefArgs);
int DE_DBG_SetInputWin_Idx10 (int iDefArgs);
int DE_DBG_GetOutWin_Idx11 (int iDefArgs);
int DE_DBG_SetOutWin_Idx12 (int iDefArgs);
int DE_DBG_SetWinBlank_Idx13 (int iDefArgs);
int DE_DBG_SetBgColor_Idx14 (int iDefArgs);
int DE_DBG_SetInnerPattern_Idx15 (int iDefArgs);
int DE_DBG_SetActFmtDetect_Idx16 (int iDefArgs);
int DE_DBG_SetZList_Idx17 (int iDefArgs);
int DE_DBG_SetMultiVision_Idx18 (int iDefArgs);
int DE_DBG_MultiWinEnable_Idx19 (int iDefArgs);
int DE_DBG_GetSourceStatus_Idx1A (int iDefArgs);
int DE_DBG_Set3DInOutCtrl_Idx1B (int iDefArgs);
int DE_DBG_SetLowDelay_Idx1C (int iDefArgs);
int DE_DBG_GetLowDelay_Idx1D (int iDefArgs);
int DE_DBG_SetDvrFmtCtrl_Idx1E (int iDefArgs);
int DE_DBG_SetUDMode_Idx1F (int iDefArgs);
int DE_DBG_SetVTM_Idx20 (int iDefArgs);
int DE_DBG_GetVTM_Idx21 (int iDefArgs);
int DE_DBG_SetWinFreeze_Idx22 (int iDefArgs);
int DE_DBG_SetHDMIPort_Idx23 (int iDefArgs);
int DE_DBG_GetCapacity_Idx24 (int iDefArgs);
int DE_DBG_SetCviTpg_Idx25 (int iDefArgs);
int DE_DBG_SetSubWindow_Idx26 (int iDefArgs);
int DE_DBG_SetCve_Idx27 (int iDefArgs);
int DE_DBG_SetCviFreeze_Idx28 (int iDefArgs);
int DE_DBG_SetCviVideoFrameBuffer_Idx29 (int iDefArgs);
int DE_DBG_SetCaptureControl_Idx2A (int iDefArgs);
int DE_DBG_SetVcs_Idx2B (int iDefArgs);
int DE_DBG_SetOperation_Idx2C (int iDefArgs);
int DE_DBG_RegRd_Idx2D (int iDefArgs);
int DE_DBG_RegWr_Idx2E (int iDefArgs);
int DE_DBG_SetUart4MCU_Idx2F (int iDefArgs);
int DE_DBG_SetSubOperation_Idx30 (int iDefArgs);


int DE_Assign_PanelType_Idx1 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_FirmwareInfo_Idx2 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_SysStatus_Idx3(int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_IFConfig_Idx4(int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_DisFmt_Idx5 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_FrRate_Idx6 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_FrRate_Idx7 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_DisOutOnOff_Idx8 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_InputSource_Idx9 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CviSrcType_IdxA (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CviFir_IdxB (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CSampleMode_IdxC (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_ScalerInfo_IdxD (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_SrcMirror_IdxE (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_WinDimension_IdxF (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_WinDimension_Idx10 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_WinDimension_Idx11 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_WinDimension_Idx12 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_SetWinBlank_Idx13 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_Color_Idx14 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_InnerPattern_Idx15 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_ActFormat_Idx16 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_Zlist_Idx17 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_Rect_Idx18 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_MultiWinOnOff_Idx19 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_SrcStatus_Idx1A (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_3DInOutCtrl_Idx1B (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_LowDelayModeOnOff_Idx1C (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_LowDelay_Idx1D (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_DvrDisFmt_Idx1E (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_UDModeOnOff_Idx1F (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_VTM_FrameInfo_Idx20 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_VTMFrameInfo_Idx21 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_WinFreeze_Idx22 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_HDMIPort_Idx23 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_Capacity_Idx24 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CviTpg_Idx25 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_SetSubWin_Idx26 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CveParam_Idx27 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CviFreezeOnOff_Idx28 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CviRwVideoFrame_Idx29 (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_CaptureCtrl_Idx2A (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_VcsIpc_Idx2B (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_OperationCtrl_Idx2C (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_RegRd_Idx2D (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_RegWr_Idx2E (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_UARTMCUMode_Idx2F (int iFuncNo,int iArgOffset,int iArgvalue);
int DE_Assign_SubOperationCtrl_Idx30 (int iFuncNo,int iArgOffset,int iArgvalue);


/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif /* _DE_PROC_CMN_H_ */
/**  @} */
