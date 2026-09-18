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
#ifndef  DE_REG_O22_INC
#define  DE_REG_O22_INC

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
	HDMI_O22_PORT_0 = 0,
	HDMI_O22_PORT_1 = 1,
	HDMI_O22_PORT_2 = 2,
	HDMI_O22_PORT_3 = 3,
	HDMI_O22_PORT_4,
	HDMI_O22_PORT_DSC,
	HDMI_O22_PORT_MAX
} HDMI_PORT_NUM_O22;

typedef enum {
	CLK_DSC_O22 = 0,

	CLK_HDA_O22 = 2,
	CLK_HDB_O22 = 3,
	CLK_HDC_O22 = 4,
	CLK_HDD_O22 = 5,
	CLK_CVD_O22 = 6,
	CLK_ADC_O22 = 7,
	CLK_NONE_O22  = 0xFF
} CVI_SEL_ENUM_O22;

typedef enum {
	CVI_HDMI_O22_DSC = 0,
	CVI_HDMI_O22_A = 2,
	CVI_HDMI_O22_B,
	CVI_HDMI_O22_C,
	CVI_HDMI_O22_D = 5,
	CVI_CVD_O22,
	CVI_ADC_O22,
	CVI_NONE_O22     = 0xFF
} CVI_DATA_IN_SEL_O22;

typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_O22_CVD_ADC,
	SRC_O22_CVD_HDA,
	SRC_O22_CVD_HDC,
	SRC_O22_CVD_CVD,
	SRC_O22_ADC_CVD,
	SRC_O22_ADC_HDA,
	SRC_O22_ADC_HDC,
	SRC_O22_ADC_ADC,
	SRC_O22_HDA_CVD,
	SRC_O22_HDA_ADC,
	SRC_O22_HDA_HDC,
	SRC_O22_HDA_HDA,
	SRC_O22_HDC_CVD,
	SRC_O22_HDC_ADC,
	SRC_O22_HDC_HDA,
	SRC_O22_HDC_HDC,
	SRC_O22_MAP_MAX
} SRC_O22_MAP_DATA;


typedef enum {
	CG_O22_CVI,
	CG_O22_IMX,
	CG_O22_ND0,
	CG_O22_VSD,
	CG_O22_CCO,
	CG_O22_SRE,
	CG_O22_FMC,
	CG_O22_FME0,
	CG_O22_FME1,
	CG_O22_DPE
} CTOP_PQE_CG_O22_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_O22_InitPHY2VIRT(void);
int DE_REG_O22_FreePHY2VIRT(void);
int DE_REG_O22_InitAddrSwitch(void);
int DE_IPC_O22_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_O22_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_REG_O22_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status);
int DE_REG_O22_CheckFwStatus(UINT32 win_id, void *status);
int DE_IPC_O22_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_O22_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_O22_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_O22_RD(void *addr);
int DE_REG_O22_WD(void *addr, UINT32 value);
int DE_REG_O22_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_O22_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_O22_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_O22_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_O22_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_O22_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_O22_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_O22_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_O22_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_O22_GPIO_Init(void);
int DE_REG_O22_HDMI_Init(void);
int DE_REG_O22_LVDS_Init(void);
int DE_REG_O22_MISC_Init(void);
int DE_REG_O22_OSD_Init(void);
int DE_REG_O22_Uart0_Switch(int whichUart);
int DE_REG_O22_VSPMute(BOOLEAN turnOn);

int DE_REG_O22_ViewInfo(int type);
int DE_REG_O22_FW_GetMaxNum(UINT32 *pMaxNum);
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_O22_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O22_FW_DumpStatus(void);
#endif

int DE_REG_O22_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_O22_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_O22_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_O22_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_O22_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_O22_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_O22_IPCisAlive(void);
int DE_REG_O22_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_O22_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_O22_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_O22_SetUdMode(BOOLEAN *pstParams);
int DE_REG_O22_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O22_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O22_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_O22_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_O22_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_O22_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_O22_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_O22_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_O22_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_O22_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_O22_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_O22_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_O22_FW_Verify(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O22_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_O22_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_O22_GetLocalMute(UINT32 *pstParams);
int DE_REG_O22_SetMemByCma(char* mem_name);
int DE_REG_O22_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag);
int DE_REG_O22_SetMultiWin(UINT32 *pstParams);
int DE_REG_O22_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_O22_SetClockPath(BOOLEAN onOff);
int DE_REG_O22_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_O22_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_O22_PreInit(void);
int DE_REG_O22_GetFPPInfo(UINT32 *start_address);
int DE_REG_O22_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams);
int DE_REG_O22_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_REG_O22_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_MEM_T *pstParams);

int DE_REG_O22_GetInitData(LX_DE_IPC_INIT_DATA_T *pstParams);
int DE_REG_O22_GetHistoBufferRange(UINT32 *start,UINT32 *end);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_O22_INC  ----- */
/**  @} */
