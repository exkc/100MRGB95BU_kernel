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
#ifndef  DE_REG_M17_INC
#define  DE_REG_M17_INC

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
	HDMI_M17_PORT_0 = 0,
	HDMI_M17_PORT_1 = 1,
	HDMI_M17_PORT_2 = 2,
	HDMI_M17_PORT_3 = 3,
} HDMI_PORT_NUM_M17;

typedef enum {
	CLK_HDA_M17 = 0,
	CLK_HDB_M17 = 1,
	CLK_HDC_M17 = 2,
	CLK_HDD_M17 = 3,
	CLK_ADC_M17 = 4,
	CLK_CVD_M17 = 5,
	CLK_NONE_M17  = 0xFF
} CVI_SEL_ENUM_M17;

typedef enum {
	CVI_HDMI_M17_A_L = 0,
	CVI_HDMI_M17_A_R,
	CVI_HDMI_M17_B_L,
	CVI_HDMI_M17_B_R,
	CVI_HDMI_M17_C_L,
	CVI_HDMI_M17_C_R,
	CVI_HDMI_M17_D_L,
	CVI_HDMI_M17_D_R,
	CVI_CVD_M17      = 8,	
	CVI_ADC_M17,
	CVI_NONE_M17     = 0xFF
} CVI_DATA_IN_SEL_M17;

typedef enum { // HDA = HDMI_A/B , HDC = HDMI_C
	SRC_M17_CVD_ADC,
	SRC_M17_CVD_HDA,
	SRC_M17_CVD_HDC,
	SRC_M17_CVD_CVD,
	SRC_M17_ADC_CVD,
	SRC_M17_ADC_HDA,
	SRC_M17_ADC_HDC,
	SRC_M17_ADC_ADC,
	SRC_M17_HDA_CVD,
	SRC_M17_HDA_ADC,
	SRC_M17_HDA_HDC,
	SRC_M17_HDA_HDA,
	SRC_M17_HDC_CVD,
	SRC_M17_HDC_ADC,
	SRC_M17_HDC_HDA,
	SRC_M17_HDC_HDC,
	SRC_M17_MAP_MAX
} SRC_M17_MAP_DATA;


typedef enum {
	CG_M17_CVI,
	CG_M17_IMX,
	CG_M17_ND0,
	CG_M17_VSD,
	CG_M17_CCO,
	CG_M17_SRE,
	CG_M17_FMC,
	CG_M17_FME0,
	CG_M17_FME1,
	CG_M17_DPE
} CTOP_PQE_CG_M17_MODULE;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_M17_InitPHY2VIRT(void);
int DE_REG_M17_FreePHY2VIRT(void);
int DE_REG_M17_InitAddrSwitch(void);
int DE_IPC_M17_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_M17_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_REG_M17_CheckMuteStatus(UINT32 *mute_status);
int DE_IPC_M17_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_M17_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn);
int DE_DMA_M17_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_M17_RD(void *addr);
int DE_REG_M17_WD(void *addr, UINT32 value);
int DE_REG_M17_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_M17_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_M17_CheckIrq4Vsync(UINT32 mcu_id);
int DE_REG_M17_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_M17_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_M17_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_M17_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_M17_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_M17_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);
int DE_REG_M17_GPIO_Init(void);
int DE_REG_M17_HDMI_Init(void);
int DE_REG_M17_LVDS_Init(void);
int DE_REG_M17_MISC_Init(void);
int DE_REG_M17_OSD_Init(void);
int DE_REG_M17_Uart0_Switch(int whichUart);
int DE_REG_M17_VSPMute(BOOLEAN turnOn);


#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_M17_FW_Download(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_M17_FW_DumpStatus(void);
#endif

int DE_REG_M17_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_M17_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_M17_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_M17_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_M17_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_M17_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_M17_IPCisAlive(void);
int DE_REG_M17_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_M17_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams, LX_DE_CVI_RW_PREW_FRAME_T *prewInfo);
int DE_REG_M17_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_M17_SetUdMode(BOOLEAN *pstParams);
int DE_REG_M17_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_M17_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams);
int DE_REG_M17_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams);

int DE_REG_M17_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en);
int DE_REG_M17_GetIrqNum(UINT32 mcu_id,      \
                         UINT32 *ipc_irq_num,\
                         UINT32 *sync_irq_num);
int DE_REG_M17_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_M17_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_M17_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_M17_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_M17_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_M17_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);
int DE_REG_M17_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir);
int DE_REG_M17_FW_Verify(LX_DE_FW_DWLD_T *pstParams);
int DE_REG_M17_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams);
int DE_REG_M17_GetCapacity(LX_DE_CAPACITY_T *pstParams);
int DE_REG_M17_GetLocalMute(UINT32 *pstParams);
int DE_REG_M17_SetMemByCma(char* mem_name);
int DE_REG_M17_GetMemFromCma(char *mem_name, BOOLEAN flag);
int DE_REG_M17_SetMultiWin(UINT32 *pstParams);
int DE_REG_M17_SetLowDelayClock(UINT32 *pstParams);
int DE_REG_M17_SetClockPath(BOOLEAN onOff);
int DE_REG_M17_GetLowDelayClock(UINT32 *pstParams);
int DE_REG_M17_GetSharedMem(UINT32 page_offset, UINT32 **mem_info);
int DE_REG_M17_PreInit(void);
int DE_REG_M17_GetFPPInfo(UINT32 *start_address);
int DE_REG_M17_GetMEMInfo(LX_DE_IPC_SYSTEM_NEW_T *pstParams);
int DE_REG_M17_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d);
int DE_REG_M17_SetSysTime(UINT32 *sec, UINT32 *msec, UINT32 *usec);
int DE_REG_M17_GetTimeDiff(UINT32 *diff);
int DE_REG_M17_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_M17_INC  ----- */
/**  @} */
