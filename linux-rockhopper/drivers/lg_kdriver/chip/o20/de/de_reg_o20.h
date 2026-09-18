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
#ifndef  DE_REG_O20_INC
#define  DE_REG_O20_INC

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
	HDMI_O20_PORT_0 = 0,
	HDMI_O20_PORT_1 = 1,
	HDMI_O20_PORT_2 = 2,
	HDMI_O20_PORT_3 = 3,
	HDMI_O20_PORT_4 = 4,
	HDMI_O20_PORT_DSC = 5,
	HDMI_O20_PORT_FEC = 6,
} HDMI_PORT_NUM_O20;

typedef enum {
	CLK_HDA_O20 = 0,
	CLK_HDB_O20 = 1,
	CLK_HDC_O20 = 2,
	CLK_HDD_O20 = 3,
	CLK_HDE_O20 = 4,
	CLK_ADC_O20 = 5,
	CLK_CVD_O20 = 6,
	CLK_DSC_O20 = 7, // disp_pll    (594MHz)
	CLK_FEC_O20 = 8, // disp_pll/2 (297MHz)
	CLK_NONE_O20  = 0xFF
} CVI_SEL_ENUM_O20;

typedef enum {
	CVI_HDMI_O20_A,
	CVI_HDMI_O20_B,
	CVI_HDMI_O20_C,
	CVI_HDMI_O20_D,
	CVI_CVD_O20,
	CVI_ADC_O20,
	CVI_HDMI_O20_E   = 6,
	CVI_HDMI_O20_DSC = 7,
	CVI_HDMI_O20_FEC = 8,
	CVI_NONE_O20     = 0xFF
} CVI_DATA_IN_SEL_O20;

typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_O20_CVD_ADC,
	SRC_O20_CVD_HDA,
	SRC_O20_CVD_HDC,
	SRC_O20_CVD_CVD,
	SRC_O20_ADC_CVD,
	SRC_O20_ADC_HDA,
	SRC_O20_ADC_HDC,
	SRC_O20_ADC_ADC,
	SRC_O20_HDA_CVD,
	SRC_O20_HDA_ADC,
	SRC_O20_HDA_HDC,
	SRC_O20_HDA_HDA,
	SRC_O20_HDC_CVD,
	SRC_O20_HDC_ADC,
	SRC_O20_HDC_HDA,
	SRC_O20_HDC_HDC,
	SRC_O20_MAP_MAX
} SRC_O20_MAP_DATA;


typedef enum {
	CG_O20_CVI,
	CG_O20_IMX,
	CG_O20_ND0,
	CG_O20_VSD,
	CG_O20_CCO,
	CG_O20_SRE,
	CG_O20_FMC,
	CG_O20_FME0,
	CG_O20_FME1,
	CG_O20_DPE
} CTOP_PQE_CG_O20_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_O20_InitPHY2VIRT(void);
int DE_REG_O20_FreePHY2VIRT(void);
int DE_REG_O20_InitAddrSwitch(void);
int DE_IPC_O20_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_O20_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_REG_O20_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status);
int DE_REG_O20_CheckFwStatus(UINT32 win_id, void *status);
int DE_IPC_O20_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_O20_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_O20_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_O20_RD(void *addr);
int DE_REG_O20_WD(void *addr, UINT32 value);
int DE_REG_O20_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_O20_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_O20_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_O20_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_O20_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_O20_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_O20_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_O20_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_O20_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_O20_GPIO_Init(void);
int DE_REG_O20_HDMI_Init(void);
int DE_REG_O20_LVDS_Init(void);
int DE_REG_O20_MISC_Init(void);
int DE_REG_O20_OSD_Init(void);
int DE_REG_O20_Uart0_Switch(int whichUart);
int DE_REG_O20_VSPMute(BOOLEAN turnOn);

int DE_REG_O20_ViewInfo(int type);
int DE_REG_O20_FW_GetMaxNum(UINT32 *pMaxNum);
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_O20_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O20_FW_DumpStatus(void);
#endif

int DE_REG_O20_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_O20_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_O20_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_O20_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_O20_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_O20_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_O20_IPCisAlive(void);
int DE_REG_O20_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_O20_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_O20_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_O20_SetUdMode(BOOLEAN *pstParams);
int DE_REG_O20_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O20_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_O20_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_O20_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_O20_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_O20_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_O20_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_O20_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_O20_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_O20_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_O20_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_O20_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_O20_FW_Verify(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_O20_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_O20_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_O20_GetLocalMute(UINT32 *pstParams);
int DE_REG_O20_SetMemByCma(char* mem_name);
int DE_REG_O20_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag);
int DE_REG_O20_SetMultiWin(UINT32 *pstParams);
int DE_REG_O20_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_O20_SetClockPath(BOOLEAN onOff);
int DE_REG_O20_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_O20_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_O20_PreInit(void);
int DE_REG_O20_GetFPPInfo(UINT32 *start_address);
int DE_REG_O20_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams);
int DE_REG_O20_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_REG_O20_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_O20_INC  ----- */
/**  @} */
