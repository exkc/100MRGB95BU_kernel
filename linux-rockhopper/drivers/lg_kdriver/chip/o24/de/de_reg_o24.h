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
 * date       2011.02.17
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef  DE_REG_O24_INC
#define  DE_REG_O24_INC

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
typedef enum {
	HDMI_O24_PORT_0 = 0,
	HDMI_O24_PORT_1 = 1,
	HDMI_O24_PORT_2 = 2,
	HDMI_O24_PORT_3 = 3,
	HDMI_O24_PORT_4,
	HDMI_O24_PORT_DSC,
	HDMI_O24_PORT_MAX
} HDMI_PORT_NUM_O24;

typedef enum {
	CLK_DSC_O24 = 0,

	CLK_HDA_O24 = 2,
	CLK_HDB_O24 = 3,
	CLK_HDC_O24 = 4,
	CLK_HDD_O24 = 5,
	CLK_CVD_O24 = 6,
	CLK_ADC_O24 = 7,
	CLK_NONE_O24  = 0xFF
} CVI_SEL_ENUM_O24;

typedef enum {
	CVI_HDMI_O24_DSC = 0,
	CVI_HDMI_O24_A = 2,
	CVI_HDMI_O24_B,
	CVI_HDMI_O24_C,
	CVI_HDMI_O24_D = 5,
	CVI_CVD_O24,
	CVI_ADC_O24,
	CVI_NONE_O24     = 0xFF
} CVI_DATA_IN_SEL_O24;

#if 0	//not used
typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_O24_CVD_ADC,
	SRC_O24_CVD_HDA,
	SRC_O24_CVD_HDC,
	SRC_O24_CVD_CVD,
	SRC_O24_ADC_CVD,
	SRC_O24_ADC_HDA,
	SRC_O24_ADC_HDC,
	SRC_O24_ADC_ADC,
	SRC_O24_HDA_CVD,
	SRC_O24_HDA_ADC,
	SRC_O24_HDA_HDC,
	SRC_O24_HDA_HDA,
	SRC_O24_HDC_CVD,
	SRC_O24_HDC_ADC,
	SRC_O24_HDC_HDA,
	SRC_O24_HDC_HDC,
	SRC_O24_MAP_MAX
} SRC_O24_MAP_DATA;
#endif

typedef enum {
	CG_O24_CVI,
	CG_O24_IMX,
	CG_O24_ND0,
	CG_O24_VSD,
	CG_O24_CCO,
	CG_O24_SRE,
	CG_O24_FMC,
	CG_O24_FME0,
	CG_O24_FME1,
	CG_O24_DPE
} CTOP_PQE_CG_O24_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_O24_InitPHY2VIRT(void);
int DE_REG_O24_FreePHY2VIRT(void);
int DE_REG_O24_InitAddrSwitch(void);
int DE_IPC_O24_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_O24_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_IPC_O24_CleanupStatus(UINT32 mcu_id);
int DE_REG_O24_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status);
int DE_REG_O24_CheckFwStatus(UINT32 win_id, void *status);
int DE_IPC_O24_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_O24_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_O24_WakeUpReg(BOOLEAN turnOn);
int DE_REG_O24_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_O24_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_O24_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_O24_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_O24_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_O24_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_O24_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_O24_GPIO_Init(void);
int DE_REG_O24_HDMI_Init(void);
int DE_REG_O24_LVDS_Init(void);
int DE_REG_O24_MISC_Init(void);
int DE_REG_O24_OSD_Init(void);
int DE_REG_O24_Uart0_Switch(int whichUart);
int DE_REG_O24_VSPMute(BOOLEAN turnOn);

int DE_REG_O24_ViewInfo(int type);
int DE_REG_O24_FW_GetMaxNum(UINT32 *pMaxNum);
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_O24_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O24_FW_DumpStatus(void);
#endif

int DE_REG_O24_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_O24_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_O24_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_O24_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_O24_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_O24_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_O24_IPCisAlive(void);
int DE_REG_O24_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_O24_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_O24_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_O24_SetUdMode(BOOLEAN *pstParams);
int DE_REG_O24_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O24_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O24_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_O24_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_O24_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_O24_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_O24_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_O24_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_O24_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_O24_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_O24_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_O24_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_O24_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_O24_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_O24_GetLocalMute(UINT32 *pstParams);
int DE_REG_O24_SetMemByCma(char* mem_name);
int DE_REG_O24_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag);
int DE_REG_O24_SetMultiWin(UINT32 *pstParams);
int DE_REG_O24_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_O24_SetClockPath(BOOLEAN onOff);
int DE_REG_O24_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_O24_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_O24_PreInit(void);
int DE_REG_O24_GetFPPInfo(UINT32 *start_address);
int DE_REG_O24_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams);
int DE_REG_O24_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_REG_O24_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_MEM_T *pstParams);

int DE_REG_O24_FW_DownloadFromHead(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O24_FW_Verify(void);

int DE_REG_O24_GetInitData(LX_DE_IPC_INIT_DATA_T *pstParams);
int DE_REG_O24_GetHistoBufferRange(UINT32 *start,UINT32 *end);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_O24_INC  ----- */
/**  @} */
