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
 *  @author     won.hur (won.hur@lge.com) 
 *  @version    1.0
 *  @date       2016-05-02
 *  @note       Additional information.
 */

#ifndef	_HDMI20_HAL_DRIVER_H_
#define	_HDMI20_HAL_DRIVER_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "./synopsys_api/hdmi_rx_ctrl_hdcp.h"

#include "../../../chip/o18/hdmi20/hdmi20_cfg_o18.h"
#include "../../../chip/o18/hdmi20/hdmi20_rx_phy_o18.h"

#include "../../../chip/m17/hdmi20/hdmi20_cfg_m17.h"
#include "../../../chip/m17/hdmi20/hdmi20_rx_phy_m17a0.h"
#include "../../../chip/m17/hdmi20/hdmi20_rx_phy_m17c0.h"

#include "../../../chip/m19/hdmi20/hdmi20_cfg_m19.h"
#include "../../../chip/m19/hdmi20/hdmi20_rx_phy_m19a0.h"


#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "hdmi20_rx_audio.h"

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


/* -------------------------------------------------------------------------------------*/
/* Do not change below definition, unless if the LINK architecture has changed          */
/* -------------------------------------------------------------------------------------*/
#define HDMI20_HAL_LINK_DEVICE_ID_PORT0	0
#define HDMI20_HAL_LINK_DEVICE_ID_PORT1	1
#define HDMI20_HAL_LINK_DEVICE_ID_PORT2	2	
#define HDMI20_HAL_LINK_DEVICE_ID_PORT3	3	


/* Phy TCS History Buffer Size */
#define HDMI20_RX_PHY_TCS_HIST_SIZE	10	

#define HDMI20_RX_CTRL_VSI_ST1		(0x3E4)
#define HDMI20_RX_CTRL_VSI_ST0		(0x3E0)
#define HDMI20_RX_CTRL_VSI_PAYLOAD0 (0x368)
#define HDMI20_TOP_CSC_BYPASS_ADDR	(0xF30)

#define HDMI20_HAL_INITIAL_THREAD_SLEEP_MS			20 /* Must be greater than 10, or seg fault due to div */
#define HDMI20_HAL_VIDEO_CHECK_CNT					0x17
#define HDMI20_HAL_NUMBER_OF_PHY_FOR_LINK			1	/* M17/O18 :  Each Link has one PHY */
#define HDMI20_HAL_RX_INTERNAL_EDID_OFFSET			0x1000
#define HDMI20_HAL_SIZE_OF_EDID						512	
#define HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY	3

/* Deep Color Mode */
#define HDMI20_HAL_RX_STATUS_REG			0x0BC
#define HDMI20_HAL_RX_CURRENT_DCM_MASK		0xF0000000


/* SW Workaround for ACR pll mode */
#define HDMI20_RX_ACR_PLL_MODE				0x2C//0x28
#define HDMI20_RX_ACR_PLL_V					0x40//0x3C
#define HDMI20_RX_ACR_CTS					0x34//0x30
#define HDMI20_RX_ACR_N						0x30//0x2C

/* Clock */
#define HDMI20_RX_CLOCK_CONFIG_KHZ			198000	// 198MHz
#define HDMI20_RX_CLOCK_MODE_DETECTION_KHZ	49500	// 49.5MHz

/* PHY TMDS Clock APB Connection to LINK : From M19A0 */
#define HDMI20_RX_AD_CLK_MEAS_HDMI_REF_MEAS_CLK	(0x95C)
#define HDMI20_RX_AD_CLK_MEAS_HDMI_REF_BASE_CLK (0x958)

/* HDMI20 LINK Top CTRL Registers */
/* ISR Registers for 5V detection */
#define HDMI20_RX_AD_MAIN_PVO_CTRL			(0xC0)
#define HDMI20_RX_AD_MAIN_I2C_DELAY			(0x24)

#define HDMI20_RX_AD_INTR_EN				(0x110)
#define HDMI20_RX_AD_INTR_MASK				(0x114)
#define HDMI20_RX_AD_INTR_CLR				(0x118)
#define HDMI20_RX_AD_INTR_DATA				(0x120)
#define HDMI20_RX_AD_INTR_FLAG_OUT_DE		BIT(0)
#define HDMI20_RX_AD_INTR_FLAG_OUT_HS		BIT(1)
#define HDMI20_RX_AD_INTR_FLAG_OUT_VS		BIT(2)
#define HDMI20_RX_AD_INTR_FLAG_CTL_DE		BIT(3)
#define HDMI20_RX_AD_INTR_FLAG_CTL_HS		BIT(4)
#define HDMI20_RX_AD_INTR_FLAG_CTL_VS		BIT(5)
#define HDMI20_RX_AD_INTR_FLAG_TMDS_DE		BIT(6)
#define HDMI20_RX_AD_INTR_FLAG_TMDS_HS		BIT(7)
#define HDMI20_RX_AD_INTR_FLAG_TMDS_VS		BIT(8)
#define HDMI20_RX_AD_INTR_FLAG_5V_FEDGE		BIT(9)
#define HDMI20_RX_AD_INTR_FLAG_5V_REDGE		BIT(10)
//#define HDMI20_RX_AD_INTR_FLAG_TIMER		BIT(11)
#define HDMI20_RX_AD_INTR_FLAG_PCD		BIT(11)


#define HDMI20_RX_AD_INTR_PHY_INFO			BIT(22)
/* Sync Monitor Register */
#define HDMI20_RX_AD_INFO_CLR				(0x11C)
#define HDMI20_RX_INFO_CLR_DATA				(0x7)

#define HDMI20_RX_MAIN_PHY_CTRL				(0x090)
#define HDMI20_RX_MAIN_PHY_CTRL_PHYPDB		BIT(0)

#define HDMI20_RX_PHY_I2C					(0x094)
#define HDMI20_RX_PHY_I2C_I2C_RSTN			BIT(0)

#define HDMI20_RX_HPD_DDC_SET				(0x008)
#define HDMI20_RX_HPD_DDC_SET_HPD			BIT(4)
#define HDMI20_RX_HPD_DDC_SET_HPD_SEL		0x00000004	


#define HDMI20_RX_ALED_AD_HPD				(0x254)
#define HDMI20_RX_ALED_AD_HPD_SET_HPD		BIT(0)

#define HDMI20_RX_ALED_AD_EDID_OFFSET		(0x0)

/* HDMI 2.0 Device Characteristic Params */
#define HDMI20_RX_TMDS_TOLERANCE			(100)	/* 100Khz */

/* Data Packets */
#define MAX_DATA_PACKET_LENGTH				32

/* HDCP2.2 PUK, DUK */
#define HDMI20_PUK_ADDR_1					(0xF00)
#define HDMI20_PUK_ADDR_2					(0xF04)
#define HDMI20_PUK_ADDR_3					(0xF08)
#define HDMI20_PUK_ADDR_4					(0xF0C)

#define HDMI20_DUK_ADDR_1					(0xF10)
#define HDMI20_DUK_ADDR_2					(0xF14)
#define HDMI20_DUK_ADDR_3					(0xF18)
#define HDMI20_DUK_ADDR_4					(0xF1C)

#define HDMI20_PUK_1						(0x00112233)
#define HDMI20_PUK_2						(0x44556677)
#define HDMI20_PUK_3						(0x8899aabb)
#define HDMI20_PUK_4						(0xccddeeff)

#define HDMI20_RX_DUK_1						(0x00EEDDCC)
#define HDMI20_RX_DUK_2						(0xBBAA9988)
#define HDMI20_RX_DUK_3						(0x77665544)
#define HDMI20_RX_DUK_4						(0x33221100)

/* 5V detector inside of LINK */
#define HDMI20_RX_5V_ADDR					(0x10)	
#define HDMI20_RX_5V_BIT					(0x00100000)

#define HDMI20_RX_VSI_TYPE_H14B_OUI_0		(0x03)
#define HDMI20_RX_VSI_TYPE_H14B_OUI_1		(0x0C)
#define HDMI20_RX_VSI_TYPE_H14B_OUI_2		(0x00)

#define HDMI20_RX_VSI_TYPE_HF_OUI_0			(0xD8)
#define HDMI20_RX_VSI_TYPE_HF_OUI_1			(0x5D)
#define HDMI20_RX_VSI_TYPE_HF_OUI_2			(0xC4)

#define HDMI20_RX_VSI_TYPE_DOLBY_OUI_0		(0x46)
#define HDMI20_RX_VSI_TYPE_DOLBY_OUI_1		(0xD0)
#define HDMI20_RX_VSI_TYPE_DOLBY_OUI_2		(0x00)
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HDMI20_CHIP_M17 = 0,
	HDMI20_CHIP_O18,
	HDMI20_CHIP_MAXNUM
} HDMI20_MODULE_CHIP_TYPE_T;
		
typedef enum 
{
	HDMI20__PHY_STABLE_THRESHOLD = 0,
	HDMI20__PHY_TCS_THRESHOLD,
	HDMI20__SURGE_H_THRESHOLD,
	HDMI20__SURGE_V_THRESHOLD,
	HDMI20__VFREQ_SUPPORT_MIN,
	HDMI20__VFREQ_SUPPORT_MAX,
	HDMI20__DBG_SYNC_MONITOR_RUN_MODE,
	HDMI20__DBG_CRC_MONITOR_RUN_MODE,
	HDMI20__STABLE_CHECK_CNT,
	HDMI20__PHY_LOST_TIMEOUT,
	HDMI20__CLEAR_AVMUTE_BY_TIMER, 
	HDMI20__AVMUTE_HOLD_TIME,
	HDMI20__LOCAL_MUTE_HOLD_TIME,
	HDMI20__LOCAL_MUTE_HOLD_INIT_TIME,
	HDMI20__LOCAL_MUTE_HOLD_ORIGIN_TIME,
	HDMI20__FORCE_FULL_RESET_ON_CEA_VIDEO_RST,
	HDMI20__DISABLE_AVMUTE_BY_POLLING,
	HDMI20__HPD_UP_ON_5V,
	HDMI20__SURGE_DETECTOR_ON,
	HDMI20__DISABLE_DCM_UPDATE_FOR_LINK,
	HDMI20__RESET_MANUAL_SYNC_ON_VFREQ_CHANGE,
	HDMI20__SET_MANUAL_SYNC_FOR_ALL_FHD,
	HDMI20__DELAY_TIME_BEFORE_SETTING_2D_MANUAL_SYNC,
	HDMI20__USE_SCDC_ISR,
	HDMI20__ADJUST_DETECTED_4K_SYNC_WITH_HTOTAL,
	HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC,
	HDMI20__TOLERENCE_FOR_VFREQ_UPDATE,
	HDMI20__ENABLE_MANUAL_SYNC,
	HDMI20__TOLERENCE_FOR_TMDS_UPDATE,
	HDMI20__LINK_RESET_DELAY_TIME,
	HDMI20__USE_POLLING_MODE_FOR_DATAPACKET,
	HDMI20__PERIOD_FOR_DATAPACKET_POLLING,
	HDMI20__CEA_VIDEO_RESET_DELAY,
	HDMI20__VERBOSE_FOR_ABNORMAL_SYNC,
	HDMI20__DISABLE_SYNOPSYS_BSP_ACCESS,
	HDMI20__TIMEOUT_FOR_PHY_LOCK_WAIT,
	HDMI20__TIMEOUT_FOR_HPD_REQUEST,
	HDMI20__LINK_REG_0XFF0_RESET_VALUE_0,
	HDMI20__THRESHOLD_FOR_ABNORMAL_PHY_DETECTION,
	HDMI20__REINIT_PHY_ON_LOCK_LOSS_BY_DETECTION,
	HDMI20__VIDEO_LINE_DEBUGGER,				
	HDMI20__PHY_RS_GAIN_FOR_3G,
	HDMI20__PHY_RS_GAIN_FOR_6G,
	HDMI20__FORCE_SCDC_INSERTION,
	HDMI20__FORCE_PLL_RANGE_DETECTED_RESULT,
	HDMI20__NUMBER_OF_ACTIVATED_LINK,
	HDMI20__DELAY_TIME_FOR_PHY_RESET,
	HDMI20__LINK_REG_0XA8_GCP_CTRL,
	HDMI20__LINK_REG_0XC4_HDCP_BCAP,
	HDMI20__HOLD_TIME_5V_DETECTION,
	HDMI20__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY,
	HDMI20__LINK_REG_0X80_HDMI_MODE_RECOVER,
	HDMI20__LINK_REG_0X16C_HDMI_VERTICAL_TIMING,
	HDMI20__COUNT_OF_RESUME,
	HDMI20__FORCE_5V_UP,
	HDMI20__FORCE_ORIGIN_TIME_FOR_3D,
	HDMI20__FORCE_SCDC_6G,
	HDMI20__TCS_ERR_SELECT, 
	HDMI20__PHY_TMDS_CHANGE_TRESHOLD,
	HDMI20__USE_PHY_LOCK_ONLY_LINK,
	HDMI20__USE_PHY_TCS_PERIOD_SEL,
	HDMI20__USE_MANUAL_SYNC_FOR_4K,
	HDMI20__USE_MANUAL_SYNC_FOR_2K,
	HDMI20__USE_MANUAL_SYNC_FOR_FA,
	HDMI20__USE_MANUAL_SYNC_FOR_SSF,
	HDMI20__USE_MANUAL_SYNC_FOR_DVI,
	HDMI20__PHY_3G_TCS_ADD_VAL,
	HDMI20__PHY_6G_TCS_ADD_VAL,
	HDMI20__PHY_MINMAX_ERROR_THRES,
	HDMI20__PHY_TCSMIN_HIGH_THRES,
	HDMI20__PHY_TCSMIN_LOW_TMDS_CLK,
	HDMI20__PHY_MIN_HIGH_TCSVAL,
	HDMI20__PHY_PDB_TCS_HIST_THRESHOLD,
	HDMI20__PHY_TCS_RERUN_TMDS_THRESHOLD,
	HDMI20__PHY_TCS_REPEAT_OFF,
	HDMI20__PHY_TCS_ENABLE_RANGE_EQ,
	HDMI20__PHY_TMDS_EXCEPTIONRANGE_LOW,
	HDMI20__PHY_TMDS_EXCEPTIONRANGE_HIGH,
	HDMI20__PHY_TCS_MANUAL_EQ_MODE_0,
	HDMI20__PHY_TCS_MANUAL_EQ_MODE_1,
	HDMI20__PHY_TCS_MANUAL_EQ_MODE_2,
	HDMI20__PHY_TCS_MANUAL_EQ_MODE_3,
	HDMI20__PHY_DATA_OFF_ON_UNSTABLE,
	HDMI20__PHY_SCRAMBLE_MANUAL_DETECT,
	HDMI20__FORCE_DOLBY_DETECT_ON,
	HDMI20__CEA_RECOVERY_VALUE,
	HDMI20__USE_ALWAYS_EDID,
	HDMI20__ENABLE_WA_MODESEL_STUCKCASE,
	HDMI20__ENABLE_VSI_HW_REG_MODE,
	HDMI20__ENABLE_DCO_GAME_TEST_MODE,
	HDMI20__ENABLE_PDB_CONTROL_ON_CONNECT,
	HDMI20__RESET_PHY_STABLE_ON_TMDS_CHANGE,
	HDMI20__THRESHOLD_OF_DC_BALANCE_OVERRUN,
	HDMI20__TIME_OF_HPD_DOWN_ON_RESTART_HPD,
	HDMI20__USE_PVO_MODE_FOR_LINK,
	HDMI20__LINK_REG_FOR_0X81C_HDCP_OVERRID,
	HDMI20__FORCE_OESS_COUNTRY_VAL,
	HDMI20__FORCE_HDR10_SAMPLE_PACKET,
	HDMI20__PHY_TCS_ALLMIN_THRES,
	HDMI20__PHY_TCS_ALLMIN_TMDS_THRES,
	HDMI20__PHY_TCS_ALLMIN_ADDVAL,
	HDMI20__VIDEOCON_DETECT_THRES,
	HDMI20__FORCE_CEA_TMDS_VALUE,
	HDMI20__CED_CHECK_MODE,
	HDMI20__PHY_ADAPTIVE_PERIOD,
	HDMI20__PHY_SW_WA_FOR_PHASE,
	HDMI20__PHY_ENABLE_PHY_EXCEPTION_CASE,
	HDMI20__PHY_PHASE_SWWA_3G_VAL,
	HDMI20__PHY_PHASE_SWWA_6G_VAL,
	HDMI20__PHY_DELTA_MODE,
	HDMI20__PHY_SET_DFE,
	HDMI20__DBG_PACKET_TYPE,
	HDMI20__DBG_PACKET_LOCATION,
	HDMI20__DATAPACKET_USE_CHSUM_FILTER,
	HDMI20__SCDT_CHK_BYPASS,
	HDMI20__PHY_TCS_MODESEL_WEIRD,
	HDMI20__LINK_RST_CNT,
	HDMI20__PHY_TCS_6G_ALLMIN_THRES,
	HDMI20__PHY_TCS_6G_ALLMIN_ADDVAL,
	HDMI20__PHY_TCS_6G_ALLMAX_THRES,
	HDMI20__PHY_EQ_BIAS_CURRENT,
	HDMI20__PHY_EQ_3G_TCS_BOUNDARY,
	HDMI20__PHY_EQ_6G_TCS_BOUNDARY,
	HDMI20__PHY_EQ_TCS_BOUND0,
	HDMI20__PHY_EQ_TCS_BOUND1,
	HDMI20__PHY_EQ_TCS_BOUND2,
	HDMI20__PHY_EQ_TCS_BOUND3,
	HDMI20__PHY_EQ_6G_TCS_BOUND_MAN,
	HDMI20__PHY_EQ_3G_TCS_BOUND_MAN,
	HDMI20__PHY_EQ_6G_TCS_ADD_BOUND0,
	HDMI20__PHY_EQ_6G_TCS_ADD_BOUND1,
	HDMI20__PHY_EQ_6G_TCS_ADD_BOUND2,
	HDMI20__PHY_EQ_6G_TCS_ADD_BOUND3,
	HDMI20__PHY_EQ_6G_TCS_ADD_BOUND4,
	HDMI20__PHY_EQ_3G_TCS_ADD_BOUND0,
	HDMI20__PHY_EQ_3G_TCS_ADD_BOUND1,
	HDMI20__PHY_EQ_3G_TCS_ADD_BOUND2,
	HDMI20__PHY_EQ_3G_TCS_ADD_BOUND3,
	HDMI20__PHY_EQ_3G_TCS_ADD_BOUND4,
	HDMI20__PHY_ENABLE_MANUAL_EQ,
	HDMI20__PHY_MANUAL_TCS_ADDVAL_CH0,
	HDMI20__PHY_MANUAL_TCS_ADDVAL_CH1,
	HDMI20__PHY_MANUAL_TCS_ADDVAL_CH2,
	HDMI20__PHY_TCS_SOM_MIN_OVER_THRES,
	HDMI20__FORCE_DCM_8_BIT_ON_594,
	HDMI20__HPD_TG_ON_6G_297,
	HDMI20__HPD_TG_ON_6G_297_TMDS_CLK,
	HDMI20__LINK_REG_0XFF0_RESET_VALUE_1,
	HDMI20__PHY_CHARGE_PUMP_ADJ_0,
	HDMI20__PHY_CHARGE_PUMP_ADJ_1,
	HDMI20__PHY_CHARGE_PUMP_ADJ_2,
	HDMI20__PHY_CHARGE_PUMP_ADJ_3,
	HDMI20__LINK_AMD_FREESYNC_MODE,
	HDMI20__PHY_PDB_ON_DELAY_TIME,
	HDMI20__LINK_HPD_DELAY_TIME,
	HDMI20__PHY_TCS_NEW_ADD_VAL,
	HDMI20__LINK_USE_TCS_DONE_APB,
	HDMI20__LINK_USE_TMDS_CLK_APB,
	HDMI20__LINK_PHY_TMDS_CLOCK_MEAS,
	HDMI20__PHY_DELTA_MODE2,
	HDMI20__FORCE_COLOR_SAMPLE_PACKET,
	HDMI20__PHY_CH0_DFE_B1_BEFORE_TCS,
	HDMI20__PHY_CH1_DFE_B1_BEFORE_TCS,
	HDMI20__PHY_CH2_DFE_B1_BEFORE_TCS,
	HDMI20__PHY_CH0_DFE_B1_AFTER_TCS,
	HDMI20__PHY_CH1_DFE_B1_AFTER_TCS,
	HDMI20__PHY_CH2_DFE_B1_AFTER_TCS,
	HDMI20__PHY_TMDS_EXCEPTION_2_LOW,
	HDMI20__PHY_TMDS_EXCEPTION_2_HIGH,
	HDMI20__PHY_TMDS_EXCEPTION_2_ADDVAL,
	HDMI20__USE_MW_HOSTERROR_CTRL,
	HDMI20__ENABLE_RESERVE_PDEC_PARSE,
	HDMI20__RESERVE_PDEC_PARSE_HEADER,
	HDMI20__PHY_SWWA_DELTASCAN2_ADD_MANUALEQ,
	HDMI20__PHY_P1_ENABLE_MANUAL_EQ,
	HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH0,
	HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH1,
	HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH2,
	HDMI20__PHY_P2_ENABLE_MANUAL_EQ,
	HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH0,
	HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH1,
	HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH2,
	HDMI20__PHY_P3_ENABLE_MANUAL_EQ,
	HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH0,
	HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH1,
	HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH2,
	HDMI20__ENABLE_ISR_PROFILER,
	HDMI20__ISR_PROFILER_TYPE,
	HDMI20__LINK_REG_0X140_HA_THRESHOLD,
	HDMI20__PHY_CED_CHECK_LENGTH,
	HDMI20__LINK_ALLM_TIMEOUT,
	HDMI20__PHY_TCS_WAIT_PAK_CHK_ON,
	HDMI20__DEV_CONTROL_LIST_MAXNUM
} HDMI20_DEV_CONTROL_LIST_T;

typedef struct
{
	UINT32 hBlankHactive;
	UINT32 hFrontHsync;
	UINT32 vFrontVsync;
	UINT32 vBlankVactive;
} HDMI20_HAL_DBG_SYNC_INFO_T;

typedef struct
{
	UINT32 hwAddr;
	volatile UINT32 * pSwAddr;
	int size;
} HDMI20_HAL_MEMORY_MAPPING_T;

typedef enum
{
	HDMI20_HAL_PHY_EXCEPTION_CASE_NONE		= 0x00000000,
	HDMI20_HAL_PHY_EXCEPTION_CTS22_23_FIX   = 0x00000001,
	HDMI20_HAL_PHY_EXCEPTION_TCS_MIN_HIGH 	= 0x00000002,
	HDMI20_HAL_PHY_EXCEPTION_TCS_MIN_ALLZERO = 0x00000004,
	HDMI20_HAL_PHY_EXCEPTION_TCS_6G_MIN_LOW = 0x00000008,
	HDMI20_HAL_PHY_EXCEPTION_TCS_SOM_MIN_HIGH  = 0x00000010,
	HDMI20_HAL_PHY_EXCEPTION_CASE_MAXNUM
} HDMI20_HAL_PHY_EXCEPTION_CASE_T;

typedef struct {
	struct task_struct* pThread;
	volatile int isAlive;
	volatile int stamp;
	int mSleep;
} HDMI20_THREAD_CONTROLLER_T;


typedef struct EXT_TIMING_ENUM {
	UINT16 hAct_info;		///< Horizontal active pixel
	UINT16 vAct_info; 		///< Vertical active lines
	UINT16 scan_info;		///< Scan type (0 : interlace, 1 : progressive)

	UINT16 hAct_buf;			///< Horizontal active pixel
	UINT16 vAct_buf; 		///< Vertical active lines
	UINT16 scan_buf; 		///< Scan type (0 : interlace, 1 : progressive)
	LX_HDMI_EXT_FORMAT_INFO_T  extInfo_buf;		///< Ext format Information (3D, 4Kx2K)
} HDMI20_NON_VSI_3D_TIMING_T;

typedef struct {
	UINT32 errorStatus;
	UINT32 startTick[LX_HDMI20_ERROR_MAXNUM];
	UINT32 counter[LX_HDMI20_ERROR_MAXNUM];	
	bool isActive[LX_HDMI20_ERROR_MAXNUM];

	/* For CED Error Accumlate */
	UINT32 cedError[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
} HDMI20_HOST_DIAGNOSIS_ERROR_T;

/* Device Handler for Each Link */
typedef struct
{
	bool initiated;				/* Flag indicating that the Driver was initiated */
	HDMI20_HAL_MEMORY_MAPPING_T topmem;	/* HDMI2.0 RX Top ctrl memory mapping */
	HDMI20_HAL_MEMORY_MAPPING_T linkmem;/* HDMI2.0 RX Link ctrl memory mapping */
	HDMI20_HAL_MEMORY_MAPPING_T ipcmem;/* HDMI2.0 RX Link ctrl memory mapping */
	HDMI20_HAL_MEMORY_MAPPING_T aledmem;/* HDMI2.0 RX Always EDID memory mapping */
	HDMI20_PHY_REG_CTRL_O18A0_T	phyReg_o18a0;
	void (*aled_write)(UINT32 addr, UINT32 data);	/* Function for Always-EDID register write access */
	UINT32 (*aled_read)(UINT32 addr);			/* Function for Always-EDID register write access */
	void (*top_write)(UINT32 addr, UINT32 data);	/* Function for TOP register write access */
	UINT32 (*top_read)(UINT32 addr);		/* Function for TOP register write access */
	void (*control_top_irq)(int bOnOff);/* Control Interrupt disable/enable for 5V signal */
	void (*resetSyncMonitor)(void);		/* Reset Sync monitor on TOP layer */
	irqreturn_t (*irq_5V_handler)(int irq, void *dev_id, struct pt_regs *regs); /* 5V Interrupt IRQ */ 
	int currentDCMMode;			/* The current Deep Color mode of the Link */
	int gWasHDCP14Written;		/* Flag indicating that the HDCP1.4 key was written by MW*/
	int gWasHDCP22Written;		/* Flag indicating that the HDCP2.2 should be operating*/
	int gWasHDCP22FuncCalled;	/* Flag idicating that the HDCP2.2 key was written from MW */
	UINT32 allm_recieve_time;
	UINT32 avmute_on_time;		/* The time when the AVMUTE(GCP) was indicated */
	UINT32 cable_connect_time;	/* The Jiffies time when the cable was connected */		
	UINT32 phyI2CSlaveAddr;		/* Phy I2C slave addr Block #0 */
	UINT32 phyI2CSlaveAddr_B1;	/* Phy I2C slave addr Block #1 */
	UINT32 isManualSyncMode;	/* Indicator if the link's output is a manual sync fixed mode*/
	UINT32 phy_tmds_clk;		/* Phy TMDS clock */
	UINT32 real_tmds_clk;		/* LINK : Actual tmds clock on real time */
	UINT32 real_pixel_clk;		/* LINK : Actual pixel clock on real time */
	UINT32 real_vfreq;			/* Actual vfreq value on real time */
	UINT32 vfreq_min;			/* For VRR/FVA/FreeSync/Gsync case */
	UINT32 vfreq_max;			/* For VRR/FVA/FreeSync/Gsync case */
	UINT32 localmutetimer;		/* Record of when the local mute was called */
	UINT32 vtotalbuffer;		/* VTotal value for sending to MW */
	UINT32 updateTimingTime;	/* The time stamp of when the timinginfo was updated */
	UINT32 restartHPDTimeStamp; /* The Time stamp for Restart HPD feature */
	bool restartHpdFlagUp;		/* The flag for indiciating Restart HPD */
	bool isHPDInverseMode;		/* HPD Inverse mode */
	bool isMHLMode;				/* Flag indicating that current mode is MHL */
	bool isLinkInitiated;		/* A Flag inidicating that the link was initiated after cable connection */
	bool isAudioARCMode;		/* A Flag inidication that the ARC mode has been enabled from MW(CEC) */
	bool isAudioMute;
	bool isAudioMuteControl;
	bool isPhyLocked;			/* A Flag inidicating that the PHY is LOCKED */
	bool hdcp22_auth_change;	/* A Flag indicating that the HDCP2.2 auth change interrupt has been up */
	bool hdcp22_ists_change;	/* A Flag indicating that the HDCP2.2 ists interrupt has been up */
	bool scdc_change;			/* Flag indicating that the SCDC status have been changed */
	bool video_change;			/* Flag indicating that the Link status have been changed */
	bool audio_change;			/* Flag indicating that the Audio status have been changed */
	bool tmds_change;			/* Flag indicating that the TMDS status have been changed */
	bool aksv_change;			/* Flag indicating that the AKSV status have been changed */
	bool dcm_change;			/* Flag indicating that the GCP DCM status have been changed */
	bool is5Vconnected;			/* Flag indicating that the 5V is inserted from the source device */
	bool isHPD;					/* Flag indicating that the HPD is Up */
	bool isScdcUD;				/* Flag indicating that the source is sending a 6G signal */
	bool isHDCP22;				/* Flag indicating that current source is HDCP2.2 encrypted */
	bool isHDCP14;				/* Flag indicating that current source is HDCP1.4 encrypted */	
	bool isHDCP22Ncap;			/* Flag indicating that the current source is not HDCP2.2 */	
	bool isTimingInvalid;		/* Flag indicating that the currently detected signal is invalid timing*/
	bool hpd_request;			/* Flag indicating that the driver is waiting a HPD UP request from upper layer */
	bool phy_rst_request;		/* Flag indicating that the driver is on a phy reset sequence */
	bool connect_request;		/* Flag indicating that the driver is on a connection request */
	bool wasEdidWritten;		/* Flag indicating the the EDID was written from MW */
	bool stopedBetweenStablize;	/* Flag indicating that Phy Stable check was stopped */
	bool hdmiDisabled;
	bool isFreeSyncMode;		/* Flag indicating that current mode is AMD FreeSync Mode */
	bool isAllmMode;			/* Flag indicating that current mode is ALLM mode */
	int isDolbyHDR;
	int phyInitiatedMode;		/* The mode PHY was reseted... 0:3G, 1:6G */
	int locking_time;			/* The actual lock time from phy reset to phy lock */
	int phyLostCnt;				/* A counter of the PHY LOCK Loss count from a healthy PHY lock */
	LX_HDMI_AUDIO_INFO_T audioInfo;	/* Audio Type Info */
	UINT32 audioStandByCnt;
	UINT32 audioStableCnt;					/* No Audio Count */
	UINT32 audioChMapStandByCnt;			/* Audio Channel Mapping Count */
	UINT32 audioChMapCnt;					/* Fifo Error count */
	UINT32 audioFifoErrMuteCnt;			/* I2S Mute Cnt */
	UINT32 audioAcrErrorCnt;	
	UINT32 audioAcrResetCnt;
	UINT32 audioIrqFifoErrCnt;
	UINT32 audioForceMuteCnt;
	UINT32 audioDbgPrintCnt;
	bool isAudioTypeChangeIrq;
	bool isAudioRegReady;
	bool isHBRaudio;
	bool isPC;
	unsigned int gpio_hpd_real;	/* GPIO number for detecting the HPD : NEW PCB*/
	unsigned int connected5Vtime;/*The timestamp when the cable was connected */
	unsigned int stablehdcp14time;/*The accumulated time for HDCp1.4 stable condition */
	unsigned int i2cDoneSignal;	/* LINK<->PHY I2C Done signal */
	unsigned int i2cNackSignal;	/* LINK<->PHY I2C NACK signal */
	unsigned int port;					/* HDMI2.0 RX Number of input port */
	unsigned int irq;					/* HDMI2.0 Rx LINK IRQ */
	unsigned int top_irq;				/* HDMI2.0 Rx TOP IRQ */
	HDMI20_HAL_DBG_SYNC_INFO_T sync_info;
	struct hdmi_rx_ctrl_video timing_info;	/* The timing data for MW to reference */
	struct hdmi_rx_ctrl ctrl;			/* HDMI2.0 RX CTRL Data */
	struct hdmi_rx_ctrl_hdcp hdcp;		/* HDMI2.0 RX HDCP Data */
	struct hdmi_rx_ctrl_audio audio;	/* HDMI2.0 RX Audio Data */
	UINT8 dataPacket[hdmi_rx_ctrl_packet_cnt][MAX_DATA_PACKET_LENGTH];	/* HDMI Data Island Packet storage */
	UINT8 emp_vtemPacket[MAX_DATA_PACKET_LENGTH];	/* HDMI Extended Meta : VTEM */
	UINT32 edidData[HDMI20_HAL_SIZE_OF_EDID>>2];						/* EDID Data storage for reference */
	bool phyTCSDone;
	bool phyCrDone;
	bool linkPhyLocked;
	bool isPhyTMDSDataBlock;
	int phyModeSelStatus;
	int prevPhyModeSelStatus;
	int phyTCSMinHist[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY][HDMI20_RX_PHY_TCS_HIST_SIZE];
	int phyTCSMaxHist[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY][HDMI20_RX_PHY_TCS_HIST_SIZE];
	int phyTCSDiff[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
	int phyTCSMin[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
	int phyTCSMax[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
	int phyTCSResult[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
	int phyTCSError[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
	int phyTCSRecovery[HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY];
	int phy_stable_cnt;
	HDMI20_HAL_PHY_EXCEPTION_CASE_T phyExceptionState;
	int phyCurrentTMDSExceptionRange;
	int phyPrevTMDSExceptionRange;
	int phyCurrentTMDSExceptionRange_2;
	int phyPrevTMDSExceptionRange_2;
	int phyTCSMinMaxDiffZeroAccumCount;
	UINT32 phyPDBResetCounter;
	UINT32 phyDcBalanceCounter;
	unsigned int countOf6GHpdTgSwWa;
	unsigned int manualSync4KVfreqHist;
	unsigned int manualSync4KHoriHist;
	unsigned int manualSyncVICHist;
	unsigned int videoConDetectCnt;
	unsigned int isr_count[HDMI20_ISR_MAXNUM];
} HDMI20_HAL_RX_DEVICE_DATA;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int HDMI20_Version(void);
int HDMI20_Open(void);
int HDMI20_Process_Cmd(LX_HDMI20_CMD_T* cmd);
int HDMI20_Suspend(void);
int HDMI20_Resume(void);

int HDMI20_HAL_Rx_Initialize(LX_HDMI20_INIT_T *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Get_TimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Set_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Get_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall);
int HDMI20_HAL_Rx_Set_HDCP14(UINT8 port, UINT32 *pData, int size, int isInternalCall);

void HDMI20_HAL_Rx_LinkVideoReset(int port, int mode, int calledId);
int HDMI20_HAL_ConnectCable(int port, int bOnOff);

void HDMI20_ResetDataPacketBuffer(int type ,UINT8 port);
void HDMI20_PrintDataPacketBuffer(int type ,UINT8 port);

int HDMI20_HAL_Check5VLevelInfo(int port, int *pValue, int isReal);
int HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_T type, int port);

int HDMI20_HAL_Rx_SetLocalVideoMute(UINT8 port, int onOff, int useTimer, UINT32 caller_id);
int HDMI20_HAL_Rx_SetLocalVideoMuteColor(UINT8 port, UINT32 isYCbCr);
int HDMI20_HAL_Rx_IsLocalMuteOn(UINT8 port);
int HDMI20_HAL_ClearManualSyncSetting(UINT8 port);
void HDMI20_HAL_ClearChangeFlags(UINT8 port);
int HDMI20_HAL_IsSCDCvalueUD(UINT8 port);
int HDMI20_HAL_IsManualSyncSet(UINT8 port);
int HDMI20_HAL_Rx_Set_RestartHPD(UINT8 port);

void HDMI20_HAL_Rx_PROC_PrintVideo(int port, struct seq_file* m);
void HDMI20_HAL_Rx_PROC_PrintSavedEDID(int port, struct seq_file* m);

int HDMI20_HAL_UpdateTimingInfo(struct hdmi_rx_ctrl *ctx, int clear, int caller_id);
int HDMI20_HAL_IsTimingInfoEmpty(UINT8 port);
int HDMI20_HAL_IsHPD_Up(UINT8 port);
int HDMI20_HAL_Rx_Set_DisableHDMI(UINT8 port, int isDisable);

void HDMI20_HAL_ClearHDMIHostError(UINT8 port, LX_HDMI20_ERROR_TYPE_T type);
void HDMI20_HAL_PutHDMIHostError(UINT8 port, LX_HDMI20_ERROR_TYPE_T type, int errorStatus);

int HDMI20_HAL_Rx_GetCEDError(UINT8 port, UINT8 channel);

void 	HDMI20_Set_Line_Debugger(UINT32 value);
UINT32	HDMI20_Get_Line_Debugger(void);
void 	HDMI20_Set_Audio_Line_Debugger(UINT32 value);
UINT32	HDMI20_Get_Audio_Line_Debugger(void);

int HDMI20_HAL_DVG_GetDevControllerCnt(HDMI20_DEV_CONTROL_TYPE_T type, int *pCnt, int isInternalCall);
int HDMI20_HAL_DVG_GetDevController(HDMI20_DEV_CONTROL_TYPE_T type, HDMI20_DEV_CONTROL_T *pDevCon, int size, int isInternalCall);
int HDMI20_HAL_DBG_AccessDevController(HDMI20_DEV_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall);
int HDMI20_HAL_DBG_AccessDevAudController(HDMI20_DEV_AUD_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall);
int HDMI20_HAL_Rx_DBG_Tool(int type, UINT8 port, int data);

LX_HDMI_DOLBY_STATE_T HDMI20_HAL_Rx_Get_IsDolbyHDR(UINT8 port);
int	HDMI20_HAL_Rx_Get_OperationStatus(UINT8 port, LX_HDMI20_OP_STATUS_T *pData);
int HDMI20_HAL_Get_VrrCurrentVfreq(UINT8 port, UINT16 *pData, int size, int isInternalCall);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

