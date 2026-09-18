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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     Taejun Lee (taejun.lee@lge.com) 
 *  @version    1.0
 *  @date       2019-04-05
 *  @note       Additional information.
 */

#ifndef	_HDMI21_TX_EARC_H_
#define	_HDMI21_TX_EARC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"
	
#ifdef	__cplusplus
	extern "C"
	{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI21_EARC_PORT				0
#define HDMI21_EARC_OUTPUT_PORT			2
#define HDMI21_EARC_M23_OUTPUT_PORT		1
#define HDMI21_EARC_SIZE_OF_CAPS		256
#define HDMI21_EARC_SUSPEND_TRY_COUNT	50

#define HDMI21_TX_EARC_PHY_REG_ADDRESS	0xC331A000						// need confirm
#define HDMI21_TX_EARC_O22_PHY_REG_ADDRESS	0xC8940000					// need confirm
#define HDMI21_TX_EARC_M23_PHY_REG_ADDRESS	0xC4B40000
#define HDMI21_TX_EARC_O24_PHY_REG_ADDRESS	0xC8D50000
#define HDMI21_TX_EARC_O26_PHY_REG_ADDRESS	0xC8750000

#define HDMI21_TX_EARC_PHY_REG_SIZE		0x180							// need confirm

/* ESM(0xC91E0000) */
#define HDMI21_TX_EARC__I2C_RESET					0xC91E0034
#define HDMI21_TX_EARC__I2C_B0_RESET				0xC3410034
#define HDMI21_TX_EARC__I2C_O22_RESET				0xC890E834
#define HDMI21_TX_EARC__I2C_M23_RESET				0xCC751010			// ??
#define HDMI21_TX_EARC__I2C_RESET_ENABLE			0x0
#define HDMI21_TX_EARC__I2C_RESET_DISABLE			0x111
#define HDMI21_TX_EARC__I2C_M23_RESET_ENABLE		0x1
#define HDMI21_TX_EARC__I2C_M23_RESET_DISABLE		0x0


/* PHY(0xC331A000) */
#define HDMI21_TX_EARC_PHY_DMAC_PDB						0x4
#define HDMI21_TX_EARC_PHY_DMAC_PDB__8PHASE_EN			0x11 // PDB ON,8PHASE_ENABLE
#define HDMI21_TX_EARC_PHY_DMAC_PDB__8PHASE_OFF			0x00 // PDB ON,8PHASE_ENABLE

#define HDMI21_TX_EARC_PHY_CMDC_DRV_ICON				0xC
#define HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_ARC		0x43 // USER_APHY_CMDC_DRV_ICON USER_APHY_CMDC_TR_CTL
#define HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_SEL		0x41 // USER_APHY_CMDC_DRV_ICON USER_APHY_CMDC_TR_CTL

#define HDMI21_TX_EARC_PHY_CMDC_ODT_CTL						0x10
#define HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB			0xD5 //0xC5 // ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB  
#define HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__NON_ODT_MODE		0xD1 //0xB1 // ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB  
#define HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_PLL_RSTB		0xC1 //0xC5 // ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB  
#define HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_NON_ODT_MODE	0xD0 //0xB1 // ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB  


#define HDMI21_TX_EARC_PHY_CMDC_ARC_SEL					0x40
#define HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC			0x1 // USER_EARC_ARC_SEL
#define HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC			0x2 // USER_EARC_ARC_SEL
#define HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__OFF			0x3 // USER_EARC_ARC_SEL

#define HDMI21_TX_EARC_PHY_CMDC_BP_MODE					0x78
#define HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_SEL		0x10 // USER_CMDC_BP_MODE USER_CMDC_OUT_SEL
#define HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF		0x12 // USER_CMDC_BP_MODE USER_CMDC_OUT_SEL
#define HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_SEL	0x0  // USER_CMDC_BP_MODE USER_CMDC_OUT_SEL
#define HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_OFF	0x2  // USER_CMDC_BP_MODE USER_CMDC_OUT_SEL

#define HDMI21_TX_EARC_PHY_CMDC_EXTR_RCTRL				0x18
#define HDMI21_TX_EARC_PHY_IREF_RBIAS					0x1C
#define HDMI21_TX_EARC_PHY_VREG_VREF					0x20
#define HDMI21_TX_EARC_PHY_CMDC_DEBUGGING_DATA			0x24

/* LINK(0xC9110000) */
//   wr_ns(0xc9114120,0xd1d07400 );  // HEART BEAT addr and data setting   
//   PAD HPD ON
//   wr_ns(0xc9114124,0x0000000E );  // HPD ON, discovery   
//	 wr_ns(0xc9114124, 0x0000000E );  // HPD ON, discovery   
//   wr_ns(0xc9114130, 0x0000ba00 ); // sw write 
//   wr_ns(0xc911412c, 0x00d37401 ); // sw write 
#define HDMI21_TX_EARC_CMDC_CONFIG							0x4120
#define HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE				0x0			// off //0x4			// bit2 0x1
#define HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE				0x4			// off //0x4			// bit2 0x1
#define HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_46	0x40		// bit 4~7 (0x00 = 42ms)
#define HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50	0x80		// bit 4~7 (0x00 = 42ms)
#define HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID		0x7400		// bit8~15 0x74
#define HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET		0xD00000	// bit16~23 0x1D
#define HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET		0xD1000000	// bit24~31 0x74

#define HDMI21_TX_EARC_CMDC_CONTROL							0x4124
#if defined(CHIP_NAME_o22) || defined(CHIP_NAME_m23)|| defined(CHIP_NAME_o24)|| defined(CHIP_NAME_o26)
#define HDMI21_TX_EARC_CMDC_CONTROL__RESET					0x0
#define HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON					0x1E			// bit1~3 0b1110
#define HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON				0x1A			// bit1~3 0b1110
#define HDMI21_TX_EARC_CMDC_CONTROL__HPD_OFF				0xFFFFFFF1	// bit1~3 0b0001
#define HDMI21_TX_EARC_CMDC_CONTROL__H14BARC_ACTIVE			0x11			// bit0
#define HDMI21_TX_EARC_CMDC_CONTROL__CONNECTOR_HPD			0x12			// bit1
#define HDMI21_TX_EARC_CMDC_CONTROL__SOFT_HDMI_HPD			0x14			// bit2
#define HDMI21_TX_EARC_CMDC_CONTROL__CMDC_DISCOVERY_EN		0x18			// bit3
#else
#define HDMI21_TX_EARC_CMDC_CONTROL__RESET					0x0
#define HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON					0xE			// bit1~3 0b1110
#define HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON				0xA			// bit1~3 0b1110
#define HDMI21_TX_EARC_CMDC_CONTROL__HPD_OFF				0xFFFFFFF1	// bit1~3 0b0001
#define HDMI21_TX_EARC_CMDC_CONTROL__H14BARC_ACTIVE			0x1			// bit0
#define HDMI21_TX_EARC_CMDC_CONTROL__CONNECTOR_HPD			0x2			// bit1
#define HDMI21_TX_EARC_CMDC_CONTROL__SOFT_HDMI_HPD			0x4			// bit2
#define HDMI21_TX_EARC_CMDC_CONTROL__CMDC_DISCOVERY_EN		0x8			// bit3
#endif


#define HDMI21_TX_EARC_CMDC_STATUS							0x4128
#define HDMI21_TX_EARC_CMDC_STATUS__DISCOVERY_STATE			0xE			// bit1~3
#define HDMI21_TX_EARC_CMDC_STATUS__DISCOVERY_STATE__EARC	0xA			// bit1~3:0b101(5)
#define HDMI21_TX_EARC_CMDC_STATUS__DISCOVERY_STATE__ARC	0xC			// bit1~3:0b110(6)
#define HDMI21_TX_EARC_CMDC_STATUS__XACT_FINISHED			0x100		// bit8
#define HDMI21_TX_EARC_CMDC_STATUS__XACT_SUCCESSFUL			0x200		// bit9
#define HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_MASK		0x1C00		// bit10~12
#define HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_UNEXPRESP	0x400		// bit10
#define HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_UNCORRECTER	0x800		// bit11
#define HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_RESPTIMEOUT	0x1000		// bit12
#define HDMI21_TX_EARC_CMDC_STATUS__STAT_CAP_CHNG			0x8000000	// bit27
#define HDMI21_TX_EARC_CMDC_STATUS__STAT_STAT_CHNG			0x10000000	// bit28

#define HDMI21_TX_EARC_CMDC_STATUS__HB_STAT_EARC_VALID		0x80000000	// bit31

#define HDMI21_TX_EARC_CMDC_XACT_CTRL						0x412C
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__TYPE__READ			0x0			// bit0 0b0
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__TYPE__WRITE			0x1			// bit0 0b1
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__EDNMARKER__EN		0x2			// bit1 0b1
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__DEVICEID__LATENCY	0x7400		// bit8~15:0x74
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__DEVICEID__CAP		0xA000		// bit8~15:0xA0
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__TX_LATENCY	0xD30000	// bit16~23:0xD3
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__RX_LATENCY	0xD20000	// bit16~23:0xD2
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__TX			0xD10000	// bit16~23:0xD3
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__CAP			0x000000	// bit16~23:0x02
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__SIZE__LATENCY		0x00000000	// bit24~31:0x01
#define HDMI21_TX_EARC_CMDC_XACT_CTRL__SIZE__CAP			0xFF000000	// bit24~31:0x01

#define HDMI21_TX_EARC_CMDC_XACT_WR0						0x4130
#define HDMI21_TX_EARC_CMDC_XACT_WR0__HPD_BIT_ON			0x8000
#define HDMI21_TX_EARC_CMDC_XACT_WR0__HPD_BIT_OFF			0x8100
#define HDMI21_TX_EARC_CMDC_XACT_RD0						0x4234
#define HDMI21_TX_EARC_CMDC_XACT_LATENCY					0xFF00

/* IRQ */
//earctx_cmdc_discovery_done_irq
//earctx_cmdc_discovery_timeout_irq
//earctx_cmdc_xact_done_irq 

/* -------------------------------------------------------------------------------------*/
/* Do not change below definition, unless if the LINK architecture has changed          */
/* -------------------------------------------------------------------------------------*/

/* eARC prediction */
#define HDMI21_EARC_INITIAL_THREAD_SLEEP_MS			30 /* Must be greater than 10, or seg fault due to div */

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	BOOLEAN isEarcDetectEn;
	BOOLEAN isArcOutEn;
	BOOLEAN isArcOut;
} HDMI21_EARC_DEVICE_DATA;

typedef enum 
{
	HDMI21_EARC__VERSION					 = 0,
	HDMI21_EARC__DEBUG,
	HDMI21_EARC__LINE_DBG,
	HDMI21_EARC__INFO,
	HDMI21_EARC__INFO__FUNCTION_CALL,
	HDMI21_EARC__INFO__STATUS,
	HDMI21_EARC__INFO__REG,
	HDMI21_EARC__INFO__CAP,
	HDMI21_EARC__INFO__MODE,
	HDMI21_EARC__INFO__CONNECTION,
	HDMI21_EARC__INFO__GLOBAL,
	HDMI21_EARC__INFO__DEBUGGING_DATA,

	HDMI21_EARC__CNT,
	HDMI21_EARC__CNT__RESTART,
	HDMI21_EARC__CNT__HPD_STABLE,
	HDMI21_EARC__CNT__FORCE_READ,
	HDMI21_EARC__CNT__HPD_BIT_WAIT_ON,
	HDMI21_EARC__CNT__HPD_BIT_WAIT_OFF,
	
	HDMI21_EARC__SET,
	HDMI21_EARC__SET__I2C,
	HDMI21_EARC__SET__PHY,
	HDMI21_EARC__SET__LINK,
	HDMI21_EARC__SET__EARC_MODE,
	HDMI21_EARC__SET__ECC_EN,
	HDMI21_EARC__SET__ENDMARKER_EN,
	HDMI21_EARC__SET__HPDBIT_RESET_EN,
	HDMI21_EARC__SET__ARC,
	HDMI21_EARC__SET__FORCE_READ_EN,
	HDMI21_EARC__SET__PHY_EXTR_RCTRL,
	HDMI21_EARC__SET__PHY_IREF_RBIAS,
	HDMI21_EARC__SET__PHY_VREG_VREF,
		
	HDMI21_EARC__CALL,
	HDMI21_EARC__CALL__TEST,
	HDMI21_EARC__CALL__TEST__IDLE1_REG_RESET,
	HDMI21_EARC__CALL__TEST__NONE_REG_RESET,

	HDMI21_EARC_DBG,
	
	HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM
} HDMI21_DEV_EARC_CONTROL_LIST_T;

typedef enum 
{
	HDMI21_EARC_XACT_STATUS__READY			= 0,
	HDMI21_EARC_XACT_STATUS__CHANGE,
	HDMI21_EARC_XACT_STATUS__LOADING,
	HDMI21_EARC_XACT_STATUS__FINISH,
	
	HDMI21_EARC_XACT_STATUS_LIST_MAXNUM
} HDMI21_EARC_XACT_STATUS_T;

typedef enum 
{
	HDMI21_EARC_XACT_RESULT__INIT			= 0,
	HDMI21_EARC_XACT_RESULT__SUCECSS,
	HDMI21_EARC_XACT_RESULT__FAILED_UNEXPRESP,
	HDMI21_EARC_XACT_RESULT__FAILED_UNCORRECTER,
	HDMI21_EARC_XACT_RESULT__FAILED_RESPTIMEOUT,
	
	HDMI21_EARC_XACT_RESULT_LIST_MAXNUM
} HDMI21_EARC_XACT_RESULT_T;

typedef struct {
	struct task_struct* pThread;
	int isAlive;
	int stamp;
	UINT32 mSleep;
} HDMI21_EARC_THREAD_CONTROLLER_T;

typedef struct {
  HDMI21_EARC_OUTPUT_PORT_T		portNum;
  HDMI21_EARC_STATUS_T			earcStatus;
  UINT8							capability[HDMI21_EARC_SIZE_OF_CAPS];
  UINT8							latency_req;
  UINT8							latency;
} HDMI21_EARC_CONNECTION_INFO_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
//int HDMI21_Tx_EARC_Version(void);
//int HDMI21_Tx_EARC_Open(void);
//int HDMI21_Tx_EARC_Process_Cmd(LX_HDMI21_CMD_T* cmd);
//int HDMI21_Tx_EARC_Suspend(void);
//int HDMI21_Tx_EARC_Resume(void);


/* Ioremap Initiailize */
void HDMI21_Tx_EARC_InitializeMemAccess(void);

/* Main Thread */
void HDMI21_Tx_EARC_MainThread(void);

/* eARC prediction */
int HDMI21_Tx_eARC_Open(void);
int HDMI21_Tx_eARC_Init(UINT8 port);
int HDMI21_Tx_eARC_Disconnect(UINT8 port);
int HDMI21_Tx_eARC_Suspend(void);
int HDMI21_Tx_eARC_Resume(void);
int HDMI21_Tx_eARC_SetEARCMode(BOOLEAN earcEnable);
int HDMI21_Tx_eARC_SetHpdBitOn(void);
int HDMI21_Tx_eARC_SetVideoLatency(UINT8 latency);
int HDMI21_Tx_eARC_GetConnectionStatus(LX_HDMI_EARC_STATUS_T *pStatus, int size);
int HDMI21_Tx_eARC_GetAMPCapability(UINT8 *pCaps, int size);
int HDMI21_Tx_eARC_GetAMPLatency(UINT8 *pLatency, int size);
int HDMI21_Tx_eARC_GetInfo(LX_HDMI_EARC_CONNECTION_INFO_T *pEARCConnectionInfo, int size, int isInternalCall);

UINT32 HDMI21_EARC_I2cApbRead(UINT32 addr);
void   HDMI21_EARC_I2cApbWrite(UINT32 addr, UINT32 data);

void HDMI21_Set_EARC_Line_Debugger(UINT32 value);	/* Used in Proc */
UINT32 HDMI21_Get_EARC_Line_Debugger(void);			/* Used in Proc */
int HDMI21_HAL_Rx_DBG_AccessDevEARCController(HDMI21_DEV_EARC_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall);
int	HDMI21_HAL_Rx_DBG_PrintDevEARCController(HDMI21_DEV_EARC_CONTROL_LIST_T index);
int HDMI21_Rx_Set_ARC(UINT8 port, BOOLEAN bOnOff);



/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

