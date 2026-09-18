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
#ifndef  DE_REG_E60_INC
#define  DE_REG_E60_INC

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
	HDMI_E60_PORT_0 = 0,
	HDMI_E60_PORT_1 = 1,
	HDMI_E60_PORT_2 = 2,
	HDMI_E60_PORT_3 = 3,
	HDMI_E60_PORT_4,
	HDMI_E60_PORT_DSC,
	HDMI_E60_PORT_MAX
} HDMI_PORT_NUM_E60;

typedef enum {
	CLK_DSC_E60 = 0,

	CLK_HDA_E60 = 2,
	CLK_HDB_E60 = 3,
	CLK_HDC_E60 = 4,
	CLK_HDD_E60 = 5,
	CLK_CVD_E60 = 6,
	CLK_ADC_E60 = 7,
	CLK_NONE_E60  = 0xFF
} CVI_SEL_ENUM_E60;

typedef enum {
	CVI_HDMI_E60_DSC = 0,
	CVI_HDMI_E60_A = 2,
	CVI_HDMI_E60_B,
	CVI_HDMI_E60_C,
	CVI_HDMI_E60_D = 5,
	CVI_CVD_E60,
	CVI_ADC_E60,
	CVI_NONE_E60     = 0xFF
} CVI_DATA_IN_SEL_E60;

typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_E60_CVD_ADC,
	SRC_E60_CVD_HDA,
	SRC_E60_CVD_HDC,
	SRC_E60_CVD_CVD,
	SRC_E60_ADC_CVD,
	SRC_E60_ADC_HDA,
	SRC_E60_ADC_HDC,
	SRC_E60_ADC_ADC,
	SRC_E60_HDA_CVD,
	SRC_E60_HDA_ADC,
	SRC_E60_HDA_HDC,
	SRC_E60_HDA_HDA,
	SRC_E60_HDC_CVD,
	SRC_E60_HDC_ADC,
	SRC_E60_HDC_HDA,
	SRC_E60_HDC_HDC,
	SRC_E60_MAP_MAX
} SRC_E60_MAP_DATA;


typedef enum {
	CG_E60_CVI,
	CG_E60_IMX,
	CG_E60_ND0,
	CG_E60_VSD,
	CG_E60_CCO,
	CG_E60_SRE,
	CG_E60_FMC,
	CG_E60_FME0,
	CG_E60_FME1,
	CG_E60_DPE
} CTOP_PQE_CG_E60_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_E60_InitPHY2VIRT(void);
int DE_REG_E60_FreePHY2VIRT(void);
int DE_REG_E60_InitAddrSwitch(void);
int DE_IPC_E60_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_E60_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_REG_E60_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status);
int DE_REG_E60_CheckFwStatus(UINT32 win_id, void *status);
int DE_IPC_E60_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_E60_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_E60_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_E60_RD(void *addr);
int DE_REG_E60_WD(void *addr, UINT32 value);
int DE_REG_E60_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_E60_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_E60_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_E60_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_E60_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_E60_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_E60_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_E60_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_E60_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_E60_GPIO_Init(void);
int DE_REG_E60_HDMI_Init(void);
int DE_REG_E60_LVDS_Init(void);
int DE_REG_E60_MISC_Init(void);
int DE_REG_E60_OSD_Init(void);
int DE_REG_E60_Uart0_Switch(int whichUart);
int DE_REG_E60_VSPMute(BOOLEAN turnOn);

int DE_REG_E60_ViewInfo(int type);
int DE_REG_E60_FW_GetMaxNum(UINT32 *pMaxNum);
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_E60_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_E60_FW_DumpStatus(void);
#endif

int DE_REG_E60_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_E60_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_E60_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_E60_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_E60_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_E60_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_E60_IPCisAlive(void);
int DE_REG_E60_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_E60_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_E60_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_E60_SetUdMode(BOOLEAN *pstParams);
int DE_REG_E60_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_E60_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_E60_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_E60_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_E60_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_E60_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_E60_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_E60_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_E60_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_E60_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_E60_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_E60_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_E60_FW_Verify(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_E60_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_E60_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_E60_GetLocalMute(UINT32 *pstParams);
int DE_REG_E60_SetMemByCma(char* mem_name);
int DE_REG_E60_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag);
int DE_REG_E60_SetMultiWin(UINT32 *pstParams);
int DE_REG_E60_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_E60_SetClockPath(BOOLEAN onOff);
int DE_REG_E60_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_E60_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_E60_PreInit(void);
int DE_REG_E60_GetFPPInfo(UINT32 *start_address);
int DE_REG_E60_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams);
int DE_REG_E60_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_REG_E60_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_E60_INC  ----- */
/**  @} */
