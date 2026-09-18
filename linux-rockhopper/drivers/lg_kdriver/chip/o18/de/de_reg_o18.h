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
#ifndef  DE_REG_O18_INC
#define  DE_REG_O18_INC

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
	HDMI_O18_PORT_0 = 0,
	HDMI_O18_PORT_1 = 1,
	HDMI_O18_PORT_2 = 2,
	HDMI_O18_PORT_3 = 3,
} HDMI_PORT_NUM_O18;

typedef enum {
	CLK_HDA_O18 = 0,
	CLK_HDB_O18 = 1,
	CLK_HDC_O18 = 2,
	CLK_HDD_O18 = 3,
	CLK_ADC_O18 = 4,
	CLK_CVD_O18 = 5,
	CLK_NONE_O18  = 0xFF
} CVI_SEL_ENUM_O18;

typedef enum {
	CVI_HDMI_O18_A_L = 0,
	CVI_HDMI_O18_A_R,
	CVI_HDMI_O18_B_L,
	CVI_HDMI_O18_B_R,
	CVI_HDMI_O18_C_L,
	CVI_HDMI_O18_C_R,
	CVI_HDMI_O18_D_L,
	CVI_HDMI_O18_D_R,
	CVI_CVD_O18      = 8,	
	CVI_ADC_O18,
	CVI_NONE_O18     = 0xFF
} CVI_DATA_IN_SEL_O18;

typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_O18_CVD_ADC,
	SRC_O18_CVD_HDA,
	SRC_O18_CVD_HDC,
	SRC_O18_CVD_CVD,
	SRC_O18_ADC_CVD,
	SRC_O18_ADC_HDA,
	SRC_O18_ADC_HDC,
	SRC_O18_ADC_ADC,
	SRC_O18_HDA_CVD,
	SRC_O18_HDA_ADC,
	SRC_O18_HDA_HDC,
	SRC_O18_HDA_HDA,
	SRC_O18_HDC_CVD,
	SRC_O18_HDC_ADC,
	SRC_O18_HDC_HDA,
	SRC_O18_HDC_HDC,
	SRC_O18_MAP_MAX
} SRC_O18_MAP_DATA;

typedef enum {
	CG_O18_CVI,
	CG_O18_IMX,
	CG_O18_ND0,
	CG_O18_VSD,
	CG_O18_CCO,
	CG_O18_SRE,
	CG_O18_FMC,
	CG_O18_FME0,
	CG_O18_FME1,
	CG_O18_DPE
} CTOP_PQE_CG_O18_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_O18_InitPHY2VIRT(void);
int DE_REG_O18_FreePHY2VIRT(void);
int DE_REG_O18_InitAddrSwitch(void);
int DE_IPC_O18_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_O18_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_REG_O18_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status);
int DE_IPC_O18_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_O18_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_O18_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_O18_RD(void *addr);
int DE_REG_O18_WD(void *addr, UINT32 value);
int DE_REG_O18_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_O18_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_O18_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_O18_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_O18_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_O18_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_O18_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_O18_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_O18_GPIO_Init(void);
int DE_REG_O18_HDMI_Init(void);
int DE_REG_O18_LVDS_Init(void);
int DE_REG_O18_MISC_Init(void);
int DE_REG_O18_OSD_Init(void);
int DE_REG_O18_Uart0_Switch(int whichUart);
int DE_REG_O18_VSPMute(BOOLEAN turnOn);


#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_O18_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O18_FW_DumpStatus(void);
#endif

int DE_REG_O18_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_O18_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_O18_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_O18_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_O18_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_O18_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_O18_IPCisAlive(void);
int DE_REG_O18_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_O18_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_O18_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_O18_SetUdMode(BOOLEAN *pstParams);
int DE_REG_O18_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O18_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O18_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_O18_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_O18_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_O18_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_O18_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_O18_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_O18_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_O18_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_O18_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_O18_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_O18_FW_Verify(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O18_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_O18_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_O18_GetLocalMute(UINT32 *pstParams);
int DE_REG_O18_SetMemByCma(char* mem_name);
int DE_REG_O18_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag);
int DE_REG_O18_SetMultiWin(UINT32 *pstParams);
int DE_REG_O18_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_O18_SetClockPath(BOOLEAN onOff);
int DE_REG_O18_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_O18_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_O18_GetFPPInfo(UINT32 *start_address);
int DE_REG_O18_GetMEMInfo(LX_DE_IPC_SYSTEM_NEW_T *pstParams);
int DE_REG_O18_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_REG_O18_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_O18_INC  ----- */
/**  @} */
