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
#ifndef  DE_REG_M23_INC
#define  DE_REG_M23_INC

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
	HDMI_M23_PORT_0 = 0,
	HDMI_M23_PORT_1 = 1,
	HDMI_M23_PORT_2 = 2,
	HDMI_M23_PORT_3 = 3,
	HDMI_M23_PORT_4,
	HDMI_M23_PORT_DSC,
	HDMI_M23_PORT_MAX
} HDMI_PORT_NUM_M23;

typedef enum {
	CLK_DSC_M23 = 0,

	CLK_HDA_M23 = 2,
	CLK_HDB_M23 = 3,
	CLK_HDC_M23 = 4,
	CLK_HDD_M23 = 5,
	CLK_CVD_M23 = 6,
	CLK_ADC_M23 = 7,
	CLK_NONE_M23  = 0xFF
} CVI_SEL_ENUM_M23;

typedef enum {
	CVI_HDMI_M23_DSC = 0,
	CVI_HDMI_M23_A = 2,
	CVI_HDMI_M23_B,
	CVI_HDMI_M23_C,
	CVI_HDMI_M23_D = 5,
	CVI_CVD_M23,
	CVI_ADC_M23,
	CVI_NONE_M23     = 0xFF
} CVI_DATA_IN_SEL_M23;

#if 0	//not used
typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_M23_CVD_ADC,
	SRC_M23_CVD_HDA,
	SRC_M23_CVD_HDC,
	SRC_M23_CVD_CVD,
	SRC_M23_ADC_CVD,
	SRC_M23_ADC_HDA,
	SRC_M23_ADC_HDC,
	SRC_M23_ADC_ADC,
	SRC_M23_HDA_CVD,
	SRC_M23_HDA_ADC,
	SRC_M23_HDA_HDC,
	SRC_M23_HDA_HDA,
	SRC_M23_HDC_CVD,
	SRC_M23_HDC_ADC,
	SRC_M23_HDC_HDA,
	SRC_M23_HDC_HDC,
	SRC_M23_MAP_MAX
} SRC_M23_MAP_DATA;
#endif

typedef enum {
	CG_M23_CVI,
	CG_M23_IMX,
	CG_M23_ND0,
	CG_M23_VSD,
	CG_M23_CCO,
	CG_M23_SRE,
	CG_M23_FMC,
	CG_M23_FME0,
	CG_M23_FME1,
	CG_M23_DPE
} CTOP_PQE_CG_M23_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_M23_InitPHY2VIRT(void);
int DE_REG_M23_FreePHY2VIRT(void);
int DE_REG_M23_InitAddrSwitch(void);
int DE_IPC_M23_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_M23_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_REG_M23_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status);
int DE_REG_M23_CheckFwStatus(UINT32 win_id, void *status);
int DE_IPC_M23_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_M23_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_M23_WakeUpReg(BOOLEAN turnOn);
int DE_REG_M23_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_M23_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_M23_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_M23_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_M23_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_M23_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_M23_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_M23_GPIO_Init(void);
int DE_REG_M23_HDMI_Init(void);
int DE_REG_M23_LVDS_Init(void);
int DE_REG_M23_MISC_Init(void);
int DE_REG_M23_OSD_Init(void);
int DE_REG_M23_Uart0_Switch(int whichUart);
int DE_REG_M23_VSPMute(BOOLEAN turnOn);

int DE_REG_M23_ViewInfo(int type);
int DE_REG_M23_FW_GetMaxNum(UINT32 *pMaxNum);
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_M23_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_M23_FW_DumpStatus(void);
#endif

int DE_REG_M23_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_M23_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_M23_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_M23_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_M23_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_M23_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_M23_IPCisAlive(void);
int DE_REG_M23_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_M23_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_M23_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_M23_SetUdMode(BOOLEAN *pstParams);
int DE_REG_M23_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_M23_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_M23_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_M23_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_M23_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_M23_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_M23_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_M23_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_M23_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_M23_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_M23_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_M23_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_M23_FW_Verify(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_M23_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_M23_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_M23_GetLocalMute(UINT32 *pstParams);
int DE_REG_M23_SetMemByCma(char* mem_name);
int DE_REG_M23_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag);
int DE_REG_M23_SetMultiWin(UINT32 *pstParams);
int DE_REG_M23_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_M23_SetClockPath(BOOLEAN onOff);
int DE_REG_M23_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_M23_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_M23_PreInit(void);
int DE_REG_M23_GetFPPInfo(UINT32 *start_address);
int DE_REG_M23_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams);
int DE_REG_M23_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f);
int DE_REG_M23_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_MEM_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_M23_INC  ----- */
/**  @} */
