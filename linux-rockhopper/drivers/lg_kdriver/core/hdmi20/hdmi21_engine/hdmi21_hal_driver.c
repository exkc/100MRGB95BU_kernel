/*
   SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
   Copyright(c) 2016 by LG Electronics Inc.

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
 *  @author		Won Hur (won.hur@lge.com)
 *  @version	1.0
 *  @date		2019-03-20
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_OVI
#define HDMI21_PORT5_USE_HW_OPTION
#endif

/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <asm/io.h>

#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/div64.h>
#include <linux/kthread.h>
#include <linux/seq_file.h>

#include "hdmi21_hal_driver.h"
#include "hdmi21_rx_audio.h"
#include "hdmi21_earc_driver.h"

#include "os_util.h"
#include "sys_regs.h"
#include "sys_io.h"

/* Linux Driver Method Interface */
#include "../hdmi20_module.h" 
#include "../hdmi20_drv.h"

#ifdef HDMI21_PORT5_USE_HW_OPTION
/* HW Options */
#include "ovi_hal.h"
#endif

/* HDMI2.1 Codes */
#include "hdmi21_rx_misc.h"
#include "hdmi21_rx_disland.h"
#include "hdmi21_rx_phy.h"
#include "hdmi21_rx_irq.h"
#include "hdmi21_rx_snps_isrunit.h"
#include "hdmi21_rx_snps_deframer.h"
#include "hdmi21_rx_snps_pfifo.h"
#include "hdmi21_rx_snps_pextract.h"
#include "hdmi21_rx_snps_pdec.h"
#include "hdmi21_rx_snps_misc.h"
#include "hdmi21_rx_snps_hdcp.h"
#include "hdmi21_rx_snps_vproc.h"
#include "hdmi21_rx_snps_vpgen.h"
#include "hdmi21_rx_snps_scdc.h"
#include "hdmi21_rx_snps_vmon.h"
#include "hdmi21_rx_dsc.h"
#include "hdmi21_rx_ddcmon.h"

/* DBG purpose */
#include "../hdmi20_kwarp.h"


/* 2025/04/29 won.hur : From SJ.YOUM */
#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif
/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
#define HDMI21_KERNEL_DRIVER_DATE 20250930
#define HDMI21_KERNEL_DRIVER_VER 0x234

#ifndef ON
#define ON	1
#endif

#ifndef OFF
#define OFF 0
#endif

#undef HDMI21_USE_SWWA_FLTUPDATE_LINKDATAPATH_RST
/*----------------------------------------------------------------------------------------
  Macro Definitions
 ----------------------------------------------------------------------------------------*/


#define HDMI21_REG_WR(address,data)   \
	__sMapped_address=(UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(__sMapped_address == NULL) break;\
	*__sMapped_address = data;\
	iounmap((void *)__sMapped_address);\
}while(0);\

#define HDMI21_REG_RD(address,data)   \
	__sMapped_address = (UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(__sMapped_address == NULL) {data = 0; break;}\
	data = (unsigned int)*__sMapped_address;\
	iounmap((void *)__sMapped_address);\
}while(0);\

#define TBL_NUM(X)						(sizeof(X) /sizeof((X)[0]))
#define u32CHK_RANGE(X,Y,offset)		((((int)X - (int)Y) <= (int)offset) && (((int)X - (int)Y) >= -(int)offset))
#define E_TO_S(x) #x	/* Converts ENUM to String */

#ifndef MAKE_PTID
#define MAKE_PTID(pid,tid)  ((((pid)&0xffff)<<16)|((tid)&0xffff))
#endif
/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dfeA01_ch0;
	UINT32 dfeA11_ch0;
	UINT32 dfeB1_ch0;
	UINT32 dfeB2_ch0;
	UINT32 dfeB3_ch0;
	UINT32 dfeB4_ch0;
	UINT32 dfeB5_ch0;
	UINT32 ced_error_ch0;
	UINT32 tmds_error_ch0;

	UINT32 dfeA01_ch1;
	UINT32 dfeA11_ch1;
	UINT32 dfeB1_ch1;
	UINT32 dfeB2_ch1;
	UINT32 dfeB3_ch1;
	UINT32 dfeB4_ch1;
	UINT32 dfeB5_ch1;
	UINT32 ced_error_ch1;
	UINT32 tmds_error_ch1;

	UINT32 dfeA01_ch2;
	UINT32 dfeA11_ch2;
	UINT32 dfeB1_ch2;
	UINT32 dfeB2_ch2;
	UINT32 dfeB3_ch2;
	UINT32 dfeB4_ch2;
	UINT32 dfeB5_ch2;
	UINT32 ced_error_ch2;
	UINT32 tmds_error_ch2;

	UINT32 dfeA01_ch3;
	UINT32 dfeA11_ch3;
	UINT32 dfeB1_ch3;
	UINT32 dfeB2_ch3;
	UINT32 dfeB3_ch3;
	UINT32 dfeB4_ch3;
	UINT32 dfeB5_ch3;
	UINT32 ced_error_ch3;
	UINT32 tmds_error_ch3;
} HDMI21_PHY_DBG_DFE_DATA_T;

typedef struct
{
	UINT32 se_os_ch0;
	UINT32 so_os_ch0;
	UINT32 te_os_ch0;
	UINT32 to_os_ch0;
	UINT32 dep_os_ch0;
	UINT32 den_os_ch0;
	UINT32 dop_os_ch0;
	UINT32 don_os_ch0;
	UINT32 eq_os_ch0;

	UINT32 se_os_ch1;
	UINT32 so_os_ch1;
	UINT32 te_os_ch1;
	UINT32 to_os_ch1;
	UINT32 dep_os_ch1;
	UINT32 den_os_ch1;
	UINT32 dop_os_ch1;
	UINT32 don_os_ch1;
	UINT32 eq_os_ch1;

	UINT32 se_os_ch2;
	UINT32 so_os_ch2;
	UINT32 te_os_ch2;
	UINT32 to_os_ch2;
	UINT32 dep_os_ch2;
	UINT32 den_os_ch2;
	UINT32 dop_os_ch2;
	UINT32 don_os_ch2;
	UINT32 eq_os_ch2;

	UINT32 se_os_ch3;
	UINT32 so_os_ch3;
	UINT32 te_os_ch3;
	UINT32 to_os_ch3;
	UINT32 dep_os_ch3;
	UINT32 den_os_ch3;
	UINT32 dop_os_ch3;
	UINT32 don_os_ch3;
	UINT32 eq_os_ch3;
} HDMI21_PHY_DBG_OFFSET_DATA_T;


/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/
#ifdef ENABLE_HDMI_CEC
extern int hdmicec_init(void);
#endif

/* 2020/12/29 : Justine Jeong told me to extern this function to get VRR Frame Rate Info */
extern int vsc_check_vrr_freq(unsigned int *p);

#ifdef BUILD_FEATURE_audio_board
int vsc_check_vrr_freq(unsigned int *p)
{
	return -1;
}
#endif
/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
extern char *saved_command_line;
/* Chip Reg setting Handler */
extern HDMI21_MODULE_CHIP_ADDR_DATA_T gHDMI21ChipRegHandler;
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21DevEARCControler[HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM];

/* Number of Max operable ports */
extern int		g_hdmi20_number_of_ports;

extern HDMI21_FEC_IPC_DATA_T gF20ChipIdData;

extern dma_addr_t gEsm_Dma_codebase;
extern dma_addr_t gEsm_Dma_database;

extern UINT8 *pEsm_codeVirtAddr;
extern UINT8 *pEsm_dataVirtAddr;
/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
/* 2023/01/16 */
char gHdmi21ScdcDeviceID_H;
char gHdmi21ScdcDeviceID_L;

/* 2023/08/18 */
UINT8 gDolbyUniqueDRM[HDMI21_RX_DOLBY_UNIQUE_DRM_COUNT] = {
	HDMI21_RX_DOLBY_UNIQUE_DRM_0,  HDMI21_RX_DOLBY_UNIQUE_DRM_1,  HDMI21_RX_DOLBY_UNIQUE_DRM_2,  HDMI21_RX_DOLBY_UNIQUE_DRM_3,\
	HDMI21_RX_DOLBY_UNIQUE_DRM_4,  HDMI21_RX_DOLBY_UNIQUE_DRM_5,  HDMI21_RX_DOLBY_UNIQUE_DRM_6,  HDMI21_RX_DOLBY_UNIQUE_DRM_7,\
	HDMI21_RX_DOLBY_UNIQUE_DRM_8,  HDMI21_RX_DOLBY_UNIQUE_DRM_9,  HDMI21_RX_DOLBY_UNIQUE_DRM_10, HDMI21_RX_DOLBY_UNIQUE_DRM_11,\
	HDMI21_RX_DOLBY_UNIQUE_DRM_12, HDMI21_RX_DOLBY_UNIQUE_DRM_13, HDMI21_RX_DOLBY_UNIQUE_DRM_14, HDMI21_RX_DOLBY_UNIQUE_DRM_15,\
	HDMI21_RX_DOLBY_UNIQUE_DRM_16, HDMI21_RX_DOLBY_UNIQUE_DRM_17, HDMI21_RX_DOLBY_UNIQUE_DRM_18, HDMI21_RX_DOLBY_UNIQUE_DRM_19,\
	HDMI21_RX_DOLBY_UNIQUE_DRM_20, HDMI21_RX_DOLBY_UNIQUE_DRM_21, HDMI21_RX_DOLBY_UNIQUE_DRM_22, HDMI21_RX_DOLBY_UNIQUE_DRM_23,\
	HDMI21_RX_DOLBY_UNIQUE_DRM_24, HDMI21_RX_DOLBY_UNIQUE_DRM_25};


/* 2020/08/04 */
int gHdmi21LaneLockLossFlag[HDMI21_NUM_OF_MAX_PORTS] = {0, };

UINT32 gHdmi21InputChgCnt = 0;

/* DSC/FEC DBG */
int gFecDbgRegOvrRide = 0;
UINT32 gFecDbgDataSet[HDMI21_DSC_F20_MAXNUM];

/* Low Power Mode */
int gLowPowerState1Tick = 6;
int gLowPowerState2Tick = 10;
int gLowPowerState3Tick = 15;
int gLowPowerState4Tick = 20;
int gLowPowerState5Tick = 25;
int gLowPowerStateMidTick = 5;
int gTop300ResetCnt = 3;

/* Model Info */
int gIsHDMI8KModel = 0;
LX_HDMI20_PLATFORM_TYPE_T gHDMI20PlatformType  = LX_HDMI20_PLATFORM_WEBOS;

/* SWWA for RxID */
unsigned char gHDMI21RepeaterRxID[32][5] = {{0x25, 0x1E, 0x1F, 0x27, 0x4B},};
int gHDMI21RepeaterCount = 0;
int gHDMI21RepeaterDepth = 0;

/* Global Variable for device Opened/Initialized information */
int gIsHDMI21KdrvOpen = -1;
unsigned int gHdmi21KdrvOpenCnt = 0;
int gIsHDMI21KdrvInitialized = -1;

/* Store i2c_dfe_level_a_01,11_mode temporary for PrintEye*/
UINT32 gHDMI21DfeLevelAMode = 0;

HDMI21_HAL_MEMORY_MAPPING_T sPqeHdrMem;	
HDMI21_HAL_MEMORY_MAPPING_T sAledTopHdmi21; 
HDMI21_HAL_MEMORY_MAPPING_T sDscTopHdmi21; 
HDMI21_HAL_MEMORY_MAPPING_T sDscCoreHdmi21; 
HDMI21_HAL_MEMORY_MAPPING_T sFecTopHdmi21; 

HDMI21_HAL_MEMORY_MAPPING_T sAledTopHdmi21P23;	/* For M23 Only : M23 has different ALED top for Port 3,4 */

/* Main Thread */
HDMI21_THREAD_CONTROLLER_T gHDMI21Thread = {NULL, 0, 0, HDMI21_HAL_INITIAL_THREAD_SLEEP_MS};

/* Device handlers : Needs each for each link */
HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];


/* All global variables which determines HW behavior should be inside either HDMI21_DEV_XXXX_CONTROL_T 
 * or HDMI21_DEV_PHY_CONTROL_T. Everything has to have an debug entry to make debugging efficient.
 * On-The-Fly debugging is essential.*/

/* Device controler : This contols the behavior of the Link */
HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM]=
{
	{E_TO_S(HDMI21__DBG_SYNC_MONITOR_RUN_MODE),	0,  " 0:SYNC Monitor prints everytime / 1:SYNC Monitor prints diff value only"},
	{E_TO_S(HDMI21__STABLE_CHECK_CNT), 			HDMI21_HAL_VIDEO_CHECK_CNT, " HDMI2.0 Stable Check Counter"},		
	{E_TO_S(HDMI21__CLEAR_AVMUTE_BY_TIMER), 	1,	" Enable Timeouts for when the AVMUTE OFF was not received by the source device"},
	{E_TO_S(HDMI21__AVMUTE_HOLD_TIME), 			800, 	" Some devices send only AVMUTE ON, not OFF... this is a time-out for AVMUTE ON"},
	{E_TO_S(HDMI21__LOCAL_MUTE_HOLD_TIME), 		900,	" Local Mute hold time"},
	{E_TO_S(HDMI21__LOCAL_MUTE_HOLD_INIT_TIME), 900,	" Local Mute hold time : initial state"},
	{E_TO_S(HDMI21__LOCAL_MUTE_HOLD_ORIGIN_TIME), 	500," Local Mute hold time : Normal case"},
	{E_TO_S(HDMI21__DISABLE_DCM_UPDATE_FOR_LINK), 	0,	" Do not update DCM info on GCP ISR"},
	{E_TO_S(HDMI21__ADJUST_DETECTED_4K_SYNC_WITH_HTOTAL), 1," Compenstate vfreq detection for 4K manual sync by using HTOTAL values"},
	{E_TO_S(HDMI21__LINK_RESET_DELAY_TIME), 	0,	" Delay time(ms) for LINK MAIN reset"},
	{E_TO_S(HDMI21__VERBOSE_FOR_ABNORMAL_SYNC), 0,	" Verbose for when synopsys API refuses to update timing information"},
	{E_TO_S(HDMI21__TIMEOUT_FOR_PHY_LOCK_WAIT), 	250,	" Timeout print for when the PHY is not being locked"},
	{E_TO_S(HDMI21__TIMEOUT_FOR_HPD_REQUEST), 		30,	" (Only operate when Timeout value for the HPD not getting high after requested"},
	{E_TO_S(HDMI21__VIDEO_LINE_DEBUGGER), 		0,	" The value for activating specific conditions for VIDEO codes"},
	{E_TO_S(HDMI21__NUMBER_OF_ACTIVATED_LINK), 	0,	" # of running HDMI ports"},	
	{E_TO_S(HDMI21__HOLD_TIME_5V_DETECTION), 	0, " A hold time for detecting 5V for MW purpose only"},
	{E_TO_S(HDMI21__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY), 500, " A mute off hold time for HDCP1.4 stability"},
	{E_TO_S(HDMI21__COUNT_OF_RESUME), 			0,	" Accumulate counter for resumes"},
	{E_TO_S(HDMI21__FORCE_5V_UP), 				0,	" Force driver to think 5V is always UP"},
	{E_TO_S(HDMI21__FORCE_ORIGIN_TIME_FOR_3D),	1,	" Force driver to upload original timing for 3D signal"},
	{E_TO_S(HDMI21__FORCE_SCDC_MODE),			0,  " Force driver phy mode to stay in 3G/6G/FRL mode. OverMax val would be Fixed 3G"},
	{E_TO_S(HDMI21__FORCE_DOLBY_DETECT_ON), 		1,  " [0]:Dolby Detection OFF / [1]: Auto / [2]:Force Dolby HDR / [3]:V2 / [4]:V2_Low"},
	{E_TO_S(HDMI21__PDB_LOW_ON_DISCONNECT), 		1, 		" Power Down Phy PDB on cable disconnect ISR"},
	{E_TO_S(HDMI21__TIME_OF_HPD_DOWN_ON_RESTART_HPD), 700, "msec value of HPD down on RestartHPD"},
	{E_TO_S(HDMI21__FORCE_HDR10_SAMPLE_PACKET),	0, "0:Auto, 1~3,11~14,101~103(drv)SDR,H10,HLG,(f/w)SDR,H4,H10,HLG,(all)SDR,H10,HLG"},
	{E_TO_S(HDMI21__DBG_PACKET_TYPE),		0x0, 	" DBG : Set Data Packet Type to enable diff printer(0:Off)"},
	{E_TO_S(HDMI21__DBG_PACKET_LOCATION),	0x0,	" DBG : Set Data Packet diff location"},
	{E_TO_S(HDMI21__DATAPACKET_USE_CHSUM_FILTER),	0x1, "0:Do not use SW CheckSum Filter, 1:Use Filter, 2:Type2 Filter"},
	{E_TO_S(HDMI21__FORCE_DCM_8_BIT_ON_594),		0x1, "Set to 1 to force deepcolor mode to 8bit on 594MHz with Hsync over 3800"},
	{E_TO_S(HDMI21__HPD_TG_ON_6G_297),	0x0, "Set count HPD SW WA where over 200MHz is detected but SCDC is 6G"},
	{E_TO_S(HDMI21__HPD_TG_ON_6G_297_TMDS_CLK),	20000, "TMDS Threshold value for -200MHz- over 6G SW WA"},
	{E_TO_S(HDMI21__LINK_AMD_FREESYNC_MODE), 		1,  " [0]:Detection OFF(Force Off) / [1]: Auto / [2]:Force ON  "},
	{E_TO_S(HDMI21__LINK_HPD_DELAY_TIME),			0, " Delay for HPD ON"},
	{E_TO_S(HDMI21__FORCE_COLOR_SAMPLE_PACKET),	0, "0:Auto, 1~3:BT601,BT709,BT2020(NCL)"},
	{E_TO_S(HDMI21__USE_MW_HOSTERROR_CTRL), 		0x0,	"Set 1 to enable MW control for Error Thres"},
	{E_TO_S(HDMI21__ENABLE_ISR_PROFILER),			0x0, "Set value for ISR profiler base iteration value"},
	{E_TO_S(HDMI21__ISR_PROFILER_TYPE),	HDMI21_ISR_MAXNUM, "Value for ISR Profiler ISR Type"},
	{E_TO_S(HDMI21__LINK_ALLM_TIMEOUT), 500, "ALLM Timeout(msec), if 0, then no timeout"},
	{E_TO_S(HDMI21__LINK_DISABLE_APB_ACCESS), 	0x0, "Set(BIT0~4) to mask Link/Top/Phy/Aled APB access"},
	{E_TO_S(HDMI21__LINK_H_TOTAL_DIFF_THRES),	40, "Threshold value of SW H TOTAL difference"},
	{E_TO_S(HDMI21__LINK_H_ACTIVE_DIFF_THRES),	2, "Threshold value of SW H ACTIVE difference"},
	{E_TO_S(HDMI21__LINK_V_TOTAL_DIFF_THRES),	0x20,  "Threshold value of SW V TOTAL difference"},
	{E_TO_S(HDMI21__LINK_V_ACTIVE_DIFF_THRES),	2,  "Threshold value of SW V ACTIVE difference"},
	{E_TO_S(HDMI21__LINK_LOWEST_H_TOTAL),	200,	"Lowest H Total that we should handle"},
	{E_TO_S(HDMI21__LINK_LOWEST_H_ACTIVE),	200,	"Lowest H Active that we should handle"},
	{E_TO_S(HDMI21__LINK_LOWEST_V_TOTAL),	200,	"Lowest V Total that we should handle"},
	{E_TO_S(HDMI21__LINK_LOWEST_V_ACTIVE),	200,	"Lowest V Active that we should handle"},
	{E_TO_S(HDMI21__LINK_HIGHEST_H_TOTAL),	15000,	"Highest H Total that we should handle"},
	{E_TO_S(HDMI21__LINK_HIGHEST_H_ACTIVE),	11000,	"Highest H Active that we should handle"},
	{E_TO_S(HDMI21__LINK_HIGHEST_V_TOTAL),	6000,	"Highest V Total that we should handle"},
	{E_TO_S(HDMI21__LINK_HIGHEST_V_ACTIVE),	4500,	"Highest V Active that we should handle"},
	{E_TO_S(HDMI21__LINK_ENABLE_SCDC_POLL_TRIG),1,  "Set 1 to enable SCDC change watchDog"},
	{E_TO_S(HDMI21__VIDEO_CHG_PRINT_INTERVAL), 500, "Msec value for video change print interval"},
	{E_TO_S(HDMI21__LINK_ENABLE_VIC_CORRECTION), 0x1, "Set 1 to enable VIC HTotal/Active correction"},
	{E_TO_S(HDMI21__FLT_RESTART_ON_CHG),	0x0, "Set FLT_Restart on video changes"},
	{E_TO_S(HDMI21__VIDEO_VIC_HTOTAL_COMP_THRES), 100, "Htotal correction based on VIC will only work within this val"},
	{E_TO_S(HDMI21__VIDEO_VIC_HACTIVE_COMP_THRES), 100, "Hactive correction based on VIC will only work within this val"},
	{E_TO_S(HDMI21__VIDEO_VIC_VACTIVE_COMP_THRES), 100, "Vactive correction based on VIC will only work within this val"},
	{E_TO_S(HDMI21__VIDEO_CHANGE_DETECTOR_WATCHDOG), 1, "Set this to 1 to activate Video Change watchdog on stable video"},
	{E_TO_S(HDMI21__VIDEO_UPDATE_PHY_DFE_RESULT),	1, "Enable DFE A/B value update"},
	{E_TO_S(HDMI21__CHECK_VIDEO_CHG_ON_AVI_ISR), 	0, "Enable Video CHG Check on AVI ISR"},
	{E_TO_S(HDMI21__VIDEO_ENABLE_VPGEN_TOGGLE),		1, "Enable VPGEN mode toggle on Mutes"},
	{E_TO_S(HDMI21__FORCE_5V_DOWN), 			0,	"Force driver to think 5V is always Down"},
	{E_TO_S(HDMI21__VIDEO_PCB_FORCE_8K_MODEL),	0, "Set to 1 for force 8K Model(H5D/Redriver)"},
	{E_TO_S(HDMI21__VIDEO_PCB_IS_ONBOARD_PORT0),	0, "Port0 : Set 1 for Onboard HDMI connection on 8K Model"},
	{E_TO_S(HDMI21__VIDEO_PCB_IS_ONBOARD_PORT1),	0, "Port1 : Set 1 for Onboard HDMI connection on 8K Model"},
	{E_TO_S(HDMI21__VIDEO_PCB_IS_ONBOARD_PORT2),	1, "Port2 : Set 1 for Onboard HDMI connection on 8K Model"},
	{E_TO_S(HDMI21__VIDEO_PCB_IS_ONBOARD_PORT3),	1, "Port3 : Set 1 for Onboard HDMI connection on 8K Model"},
	{E_TO_S(HDMI21__VIDEO_PCB_IS_ONBOARD_PORT4),	1, "Port4 : Set 1 for Onboard HDMI connection on 8K Model"},
	{E_TO_S(HDMI21__VIDEO_VRR_EM_TIMEOUT),	200, "EM VRR Timeout(msec), if 0, then no timeout"},
	{E_TO_S(HDMI21__VIDEO_H5D_LN_LOCK_RET),	1, "Set 1 to Sent Retrain on LaneLock Loss on H5D"},
	{E_TO_S(HDMI21__VIDEO_FRL_NO_READY_SWWA), 1, "Set 1 to activate NO_READY flag on Valid Video"},
	{E_TO_S(HDMI21__VIDEO_FORCE_FRL_CTS_MODE), 1, "2: Force CTS mode/ 1: Auto / 0: Force NOT CTS mode"},
	{E_TO_S(HDMI21__VIDEO_FORCE_PROGRES_HIGH_V), 1300, "0:Off, Value : Vactive over this value will force to prog"},
	{E_TO_S(HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT), 100, " Msec of HPD low duration on Boot event"},
	{E_TO_S(HDMI21__VIDEO_PKTERR_DETECT_THRES), 0x100, " Threshold value to detect snow noise"},
	{E_TO_S(HDMI21__VIDEO_PKTERR_DETECT_CNT), 0x1, " Cnt value for detecting snow noise. Set 0 to off"},
	{E_TO_S(HDMI21__VIDEO_H5D_8K_CHECK_HPD_SWWA), 0x1, " Set 1 to activate HPD Toggle SWWA on non 8K res for H5D port"},
	{E_TO_S(HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER), 10000, " Tick threshold for entering low power mode(1tick : 30msec)"},
	{E_TO_S(HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23), 0, "Set 1 to enable low power mode for HDCP2.3"},
	{E_TO_S(HDMI21__VIDEO_ENABLE_PIXEL_PACKING_WATCHDOG), 1, "Set 0 to disable PixelPackingPhase watchdog. GCP!=Link"},
	{E_TO_S(HDMI21__VIDEO_DSC_8K5060_NUM_OF_ACITVE_C), 2, "Number of DSC core for video over 8K 50Hz"},
	{E_TO_S(HDMI21__VIDEO_DSC_8K30_NUM_OF_ACTIVE_C), 1, "Number of DSC core for video under 8K 30Hz"},
	{E_TO_S(HDMI21__VIDEO_DSC_NUM_OF_SS_OVERRIDE), 0, "Set non-0 value to override Num of SoftSlice DSC"},
	{E_TO_S(HDMI21__VIDEO_AUTO_SCRAMBLE_FOR_HDMI20), 0, "Set 1 to Auto Run Scrambleing for HDMI2.0"},
	{E_TO_S(HDMI21__VIDEO_LOWPOWER_LIMIT_CNT), 1, "Set Limit Cnt for Low Power Mode entry"},
	{E_TO_S(HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT), 1, "Set 1 to Limit All lowpower entry, when atleast one port has been activated"},
	{E_TO_S(HDMI21__VIDEO_LOWPOWER_LOWEST_TMDSCLK),  80000, "TMDS CLK(Unit:10K) Lower than this would not enter LowPowerMode"},
	{E_TO_S(HDMI21__VIDEO_DOVI_PACKET_MS_TIMEOUT), 200, "Time limit for DOVI buff timeout(ms) regarding packet reception. 0:OFF"},
	{E_TO_S(HDMI21__VIDEO_DDCMON_ADDR_SEL),	0x0, "DDC Monitor => 0:ALL, 1:EDID Only, 2: SCDC Only, 3:HDCP Only"},
	{E_TO_S(HDMI21__VIDEO_LOWPOWER_O22_32C_VAL), 0x01036000, "(O22) Value of 0x32C for Low Power mode"},
	{E_TO_S(HDMI21__VIDEO_LOWPOWER_O22_PHY_DBG), 0x0, "(O22) Set DBG values for LowPower Mode"},
	{E_TO_S(HDMI21__VIDEO_DSC_CVI_HSYNC_PULSE_WIDTH), 0x0, "(O22) If not zero, override to this value(hsync pulse)"},
	{E_TO_S(HDMI21__VIDEO_DSC_CORE_HSYNC_DELAY_0), 0x0, "(O22) If not zero, override to this value(Hsync Delay for Core0"},
	{E_TO_S(HDMI21__VIDEO_DSC_USE_GREAT_LIM_FORMULA), 0, "If not zero, use the famous Lim's DSC solution"},
	{E_TO_S(HDMI21__VIDEO_DISCARD_SPECIFIC_CHANGES), 0x0, "Mask out difference by this value on Change Detector"},
	{E_TO_S(HDMI21__VIDEO_TRIGGER_SCDC_CHG_WATCHDOG), 0, "(Write Only) Write non-zero val to trigger SCDC CHG WatchDog"},
	{E_TO_S(HDMI21__VIDEO_FS_CONSIDER_HDCP2X_CASE), 0, "(O22) Set to 1 to differenticate HDCP2x cases for FS"},
	{E_TO_S(HDMI21__LINK_FORCE_QMS_MODE),	1, "2:Force On, 1:Auto, 0: Force Off"},
	{E_TO_S(HDMI21__VIDEO_QMS_EM_TIMEOUT),	100, "QMS-VRR Timeout(msec), if 0, then no timeout"},
	{E_TO_S(HDMI21__VIDEO_DBG_VFREQ_OVERRIDE), 0, "Override value for Vfreq"},
	{E_TO_S(HDMI21__VIDEO_DSC_712M_MODE),	0, "Set to non zero to make DSC work on 712MHz domain"},
	{E_TO_S(HDMI21__VIDEO_FILTER_STUCK_SWWA_THRES), 0, "Set thres value for filter sel stuck detect. 0 for OFF"},
	{E_TO_S(HDMI21__VIDEO_FILTER_CONSECUTIVE_STUCK),3, "Set thres value for detecting consecutive Filter Stuck SWWA"},
	{E_TO_S(HDMI21__VIDEO_HPD_TOGGLE_ON_FRL_TCS_LOW), 0, "0:Off, 1:HPD Toggle on FRL LTS:P TCS_LOW state"},
	{E_TO_S(HDMI21__VIDEO_FILTER_STUCK_CLOCK_CONDITION), 54000, "Stuck condition"},
	{E_TO_S(HDMI21__VIDEO_DSC_RESET_CORE_CLOCK), 1, "0:Off, 1:on DSC reset core clock"},
	{E_TO_S(HDMI21__VIDEO_DSC_165_REWRITE), 1, "0:Off, 1:on DSC 165hz PPS rewrite before stable"},
	{E_TO_S(HDMI21__VIDEO_DSC_USE_CAL_VALUE), 1, "0:Off, 1:on DSC use calculate delay value by dk.choi"},
	{E_TO_S(HDMI21__VIDEO_DSC_USE_CAL_NUM_OF_SS), 1, "0:Off, 1:on DSC use calculated num of ss value"},
	{E_TO_S(HDMI21__VIDEO_VERBOSE_DOLBY_UNIQUE_DRM), 0, "0:Silence mode, 1:Verbose, ..."}
};


HDMI20_DEV_CONTROL_T	gHDMI21RxDevPhyControler[HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM]=
{
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE0),				0x6,    "PHY RS Gain value for TMDS 3G/6G mode"}, 
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE1), 			0x6,	"PHY RS Gain value for FRL1~4 mode"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE2), 			0x8,	"PHY RS Gain value for FRL5 mode."},
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE3), 			0x8,	"PHY RS Gain value for FRL6 mode."},
	{E_TO_S(HDMI21__PHY_TMDS_EXCEPTIONRANGE_LOW), 	0, 	" Exception Case for PHY MODE Sel TMDS LOW Threshold"},
	{E_TO_S(HDMI21__PHY_TMDS_EXCEPTIONRANGE_HIGH), 	16000, 	" Exception Case for PHY MODE Sel TMDS HIGH Threshold"},
	{E_TO_S(HDMI21__PHY_TCS_ENABLE_RANGE_EQ),		0x1, "Enable Fixed EQ on lower Freq Range(3G : 0,1)"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_3G),			0x9B, "TCS Error Sel value for 3G"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_6G),			0x9B, "TCS Error Sel value for 6G"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_FRL_3G),		0xCB, "TCS Error Sel value for FRL Rate 1"},	
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE1),	0x9B, "TCS Error Sel value for FRL Rate 2~4"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE2),	0x9B, "TCS Error Sel value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE3),	0x9B, "TCS Error Sel value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_MODE_1_0),	0x97, "TCS Error Sel for 3G Mode 0~1"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_MODE_2),		0x97, "TCS Error Sel for 3G Mode 2"},
	{E_TO_S(HDMI21__PHY_TCS_ERROR_SEL_MODE_3),		0x97, "TCS_Error Sel for 3G Mode 3"},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL),				0x6, "Delta mode 1 add val : Do not touch "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL12G),		0x2, "Delta Scan Add Val : For FRL 4L12G~ "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL10G),		0x2, "Delta Scan Add Val : For FRL 4L10G "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL3G),		0x2, "Delta Scan Add Val : For FRL 3L3G~4L8G"},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_TMDS6G),		0x2, "Delta Scan Add Val : For TMDS 6G~ "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_TMDS3G),		0x2, "Delta Scan Add Val : For TMDS ~3G"},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL12G_CTS),	0x0, "(CTS Mode)Delta Scan Add Val : For FRL 4L12G~ "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL10G_CTS),	0x1, "(CTS Mode)Delta Scan Add Val : For FRL 4L10G "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL12G_ONB),	0x0, "(Onboard)Delta Scan Add Val : For FRL 4L12G~ "},
	{E_TO_S(HDMI21__PHY_DELTA_ADD_VAL_FRL10G_ONB),	0x1, "(Onboard)Delta Scan Add Val : For FRL 4L10G "},
	{E_TO_S(HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE),	0x0, "Enable PHY Exception Case"},
	{E_TO_S(HDMI21__PHY_TCS_PERIOD_S_FRL12G_CTS),	0x1, "(CTS)TCS Speed for FRL(TCS Period Value) 12G"},
	{E_TO_S(HDMI21__PHY_TCS_PERIOD_S_FRL_CTS),	0x2, "(CTS)TCS Speed for FRL(TCS Period Value) 6G3L ~ 10G4L"},
	{E_TO_S(HDMI21__PHY_TCS_PERIOD_S_FRL3G_CTS), 0x1, "(CTS)TCS Speed for FRL(TCS Period Value) 3G3L"},	
	{E_TO_S(HDMI21__PHY_TCS_PERIOD_S_FRL12G),	0x0, "TCS Speed for FRL(TCS Period Value) 12G"},
	{E_TO_S(HDMI21__PHY_TCS_PERIOD_S_FRL),		0x0, "TCS Speed for FRL(TCS Period Value) 3G3L ~ 10G4L"},
	{E_TO_S(HDMI21__PHY_TCS_PERIOD_S_TMDS),		0x2, "TCS Speed for TMDS(TCS Period Value)"},
	{E_TO_S(HDMI21__PHY_TCS_SCOPE_SEL_FRL),			0x1, "TCS Speed for FRL(TCS Scope Value)"},
	{E_TO_S(HDMI21__PHY_TCS_SCOPE_SEL_TMDS),		0x1, "TCS Speed for TMDS(TCS Scope Value)"},
	{E_TO_S(HDMI21__PHY_I2C_ODT_VAL),				0x1C,"PHY ODT value"},
	{E_TO_S(HDMI21__PHY_DISABLE_PHYINITIATE_API),	0x0, "Set 1 to disable PHY_INITIATE API"},
	{E_TO_S(HDMI21__PHY_ERROR_PERIOD_SEL),			0x2, "PHY period for collecting Error"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_3G),				0x4, "Value of 0x28:0x70 ctrl_vref for TMDS 3G"},		
	{E_TO_S(HDMI21__PHY_CTRL_VREF_6G),				0x4, "Value of 0x28:0x70 ctrl_vref for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_FRL_TYPE1),		0x4, "Value of 0x28:0x70 ctrl_vref for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_FRL_TYPE2),		0x6, "Value of 0x28:0x70 ctrl_vref for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_FRL_TYPE3),		0x6, "Value of 0x28:0x70 ctrl_vref for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_3G),			0x3, "Value of 0x28:0x70 ctrl_vreg14 for TMDS 3G"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_6G),			0x3, "Value of 0x28:0x70 ctrl_vreg14 for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE1),	0x3, "Value of 0x28:0x70 ctrl_vreg14 for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE2),	0x3, "Value of 0x28:0x70 ctrl_vreg14 for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE3),	0x3, "Value of 0x28:0x70 ctrl_vreg14 for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_CTS_TYPE2),	0x3, "Value of 0x28:0x70 ctrl_vreg14 for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_REG_VOUT_CTS_TYPE3),	0x3, "Value of 0x28:0x70 ctrl_vreg14 for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_3G),				0x4, "Value of 0x28:0x24 eq_ictrl for TMDS 3G"},		
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_6G),				0x4, "Value of 0x28:0x24 eq_ictrl for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE1),		0x4, "Value of 0x28:0x24 eq_ictrl for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE2),		0x4, "Value of 0x28:0x24 eq_ictrl for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE3),		0x7, "Value of 0x28:0x24 eq_ictrl for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_CTS_TYPE2),		0x4, "(CTS) Value of 0x28:0x24 eq_ictrl for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_CTRL_EQICTRL_CTS_TYPE3),		0x5, "(CTS) Value of 0x28:0x24 eq_ictrl for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_EQ_FREQ_DIV),				0x6, "Value of 0x38:0xED eq_freq_div"},
	{E_TO_S(HDMI21__PHY_DELTA_FULL_CHECK),				0x1, "Set On(1)/Off(0) Delta_Full_CHK"},
	{E_TO_S(HDMI21__PHY_DELTA_CHK_NSIDE),				0x0, "Set value for Delta CHK N Side"},
	{E_TO_S(HDMI21__PHY_DELTA_CHK_PSIDE),				0x0, "Set value for Delta CHK P Side"},
	{E_TO_S(HDMI21__PHY_ANA_CDR_SEL_MODE_2_0),			0x0, "Set Value for 0x38:0x5A ana_cdr_sel TMDS Mode0~2"},		
	{E_TO_S(HDMI21__PHY_ANA_CDR_SEL_MODE_3),			0x1, "Set Value for 0x38:0x5A ana_cdr_sel TMDS Mode3"},
	{E_TO_S(HDMI21__PHY_ANA_CDR_SEL_6G),				0x1, "Set Value for 0x38:0x5A ana_cdr_sel TMDS 6G"},
	{E_TO_S(HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE1),	0x1, "Set Value for 0x38:0x5A ana_cdr_sel FRL1~4"},
	{E_TO_S(HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE2),	0x1, "Set Value for 0x38:0x5A ana_cdr_sel FRL5"},
	{E_TO_S(HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE3),	0x1, "Set Value for 0x38:0x5A ana_cdr_sel FRL6"},
	{E_TO_S(HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0),		0x0, "Set Value for 0x38:0x5A ana_cdr_sel TMDS Mode0~2"},
	{E_TO_S(HDMI21__PHY_CDR_FLTR_CTRL_MODE_3),			0x1, "Set Value for 0x38:0x5A ana_cdr_sel TMDS Mode3"},
	{E_TO_S(HDMI21__PHY_CDR_FLTR_CTRL_6G),			0x1, "Set Value for 0x38:0x5A ana_cdr_sel TMDS 6G"},
	{E_TO_S(HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE1),	0x1, "Set Value for 0x38:0x5A ana_cdr_sel FRL1~4"},
	{E_TO_S(HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE2),	0x1, "Set Value for 0x38:0x5A ana_cdr_sel FRL5"},
	{E_TO_S(HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE3),	0x1, "Set Value for 0x38:0x5A ana_cdr_sel FRL6"},
	{E_TO_S(HDMI21__PHY_DFE_NOT_OFF),				0x0, "Set Value for DFE_NOT_OFF"}, 
	{E_TO_S(HDMI21__PHY_TCS_BOUND_0),				0x4, "TCS BOUND 0 : TCSMin=>(0 ~ B0)"},
	{E_TO_S(HDMI21__PHY_TCS_BOUND_1),				0x4, "TCS BOUND 1 : TCSMin=>(B0 ~ B0+B1"},
	{E_TO_S(HDMI21__PHY_TCS_BOUND_2),				0x4, "TCS BOUND 2 : TCSMin=>(B0+B1 ~ B0+B1+B2"},
	{E_TO_S(HDMI21__PHY_TCS_BOUND_3),				0x4, "TCS BOUND 3 : TCSMin=>(B0+B1+B2 ~ B0+B1+B2+B3"},
	{E_TO_S(HDMI21__PHY_TCS_ADD_VAL_BOUND0),		0xC, "TCS Add Val for TCS MIN ~ B0"},
	{E_TO_S(HDMI21__PHY_TCS_ADD_VAL_BOUND1),		0xA, "TCS Add Val for TCS MIN B0 ~ B0+B1"},
	{E_TO_S(HDMI21__PHY_TCS_ADD_VAL_BOUND2),		0xA, "TCS Add Val for TCS MIN B0+B1 ~ B0+B1+B2"},
	{E_TO_S(HDMI21__PHY_TCS_ADD_VAL_BOUND3),		0xA, "TCS Add Val for TCS MIN B0+B1+B2 ~ B0+B1+B2+B3"},
	{E_TO_S(HDMI21__PHY_TCS_ADD_VAL_BOUND4),		0x4, "TCS Add Val for TCS MIN B0+B1+B2+B3 ~"},
	{E_TO_S(HDMI21__PHY_EQ_AUTO_PLL_0),				0x1, "EQ Auto PLL selection val for PLL Range 0"}, 
	{E_TO_S(HDMI21__PHY_EQ_AUTO_PLL_1),				0x1, "EQ Auto PLL selection val for PLL Range 1"},
	{E_TO_S(HDMI21__PHY_EQ_AUTO_PLL_2),				0x0, "EQ Auto PLL selection val for PLL Range 2"},
	{E_TO_S(HDMI21__PHY_EQ_AUTO_PLL_3),				0x0, "EQ Auto PLL selection val for PLL Range 3"},
	{E_TO_S(HDMI21__PHY_DFE_DIG_ON),				0x1, "(O20~E60A) PHY dfe_dig_on(Set 0 to disable DFE) set value for All Range"},
	{E_TO_S(HDMI21__PHY_DFE_EVERY_CS),				0x0, "(E60B0 only) PHY dfe_every_cs value"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_ON_MODE),			0x0, "PHY i2c_dfe_on_mode set value for TMDS Mode"},
	{E_TO_S(HDMI21__PHY_EQ_DOHG_3G),				0x1, "EQ_DOHG value for TMDS 3G Mode"},
	{E_TO_S(HDMI21__PHY_EQ_DOHG_6G),				0x1, "EQ_DOHG value for TMDS 3G Mode"},
	{E_TO_S(HDMI21__PHY_EQ_DOHG_FRL_TYPE1),			0x1, "EQ_DOHG value for FRL Rate 1~4 Mode"},
	{E_TO_S(HDMI21__PHY_EQ_DOHG_FRL_TYPE2),			0x1, "EQ_DOHG value for FRL Rate 5 Mode"},
	{E_TO_S(HDMI21__PHY_EQ_DOHG_FRL_TYPE3),			0x1, "EQ_DOHG value for FRL Rate 6 Mode"},
	{E_TO_S(HDMI21__PHY_RETRAIN_ON_NO_LANELOCK),	2, "FLT Retrain on No LN Lock after stable vid"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_VAL_3G),				0x0, "Value of 0x28:0x23 eq_hdmi20_val for TMDS 3G"},		
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_VAL_6G),				0x0, "Value of 0x28:0x23 eq_hdmi20_val for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE1),		0x0, "Value of 0x28:0x23 eq_hdmi20_val for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE2),		0x0, "Value of 0x28:0x23 eq_hdmi20_val for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3),		0x1, "Value of 0x28:0x23 eq_hdmi20_val for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3_OB),	0x0, "(Onboard)Value of 0x28:0x23 eq_hdmi20_val for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_MAN_3G),				0x0, "Value of 0x28:0x23 eq_hdmi20_man for TMDS 3G"},		
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_MAN_6G),				0x0, "Value of 0x28:0x23 eq_hdmi20_man for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE1),		0x1, "Value of 0x28:0x23 eq_hdmi20_man for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE2),		0x1, "Value of 0x28:0x23 eq_hdmi20_man for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE3),		0x1, "Value of 0x28:0x23 eq_hdmi20_man for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_PLL_MANUAL_MODE),		0x0, "PLL Mode. 0:Auto Mode, 1:Manual Mode"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_FB_10L_20H),		0x1, "Only works in PLL Manual : val for MAN_CTRL_FB_10L_20H"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_DIV2H_BPL),		0x1, "Only works in PLL Manual : val for MAN_CTRL_DIV2H_BPL"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_RDIV),			0x1, "Only works in PLL Manual : val for MAN_CTRL_RDIV"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_REFCLK),		0x1, "Only works in PLL Manual : val for MAN_CTRL_REFCLK"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_ICP),			0x5, "Only works in PLL Manual : val for MAN_CTRL_ICP"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_FDIV),			0x2, "Only works in PLL Manual : val for MAN_CTRL_FDIV"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_PDR_5L_9H),	0x0, "Only works in PLL Manual : val for MAN_CTRL_PDR_5L_9H"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_LFR2),			0x0, "Only works in PLL Manual : val for MAN_CTRL_LFR2"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_LFC2),			0x3, "Only works in PLL Manual : val for MAN_CTRL_LFC2"},
	{E_TO_S(HDMI21__PHY_MAN_CTRL_LFC1),			0x3, "Only works in PLL Manual : val for MAN_CTRL_LFC1"},
	{E_TO_S(HDMI21__PHY_EQ_DHFG_FRL_TYPE1),		0x0, "EQ DHFG value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQ_DHFG_FRL_TYPE2),		0x0, "EQ DHFG value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQ_DHFG_FRL_TYPE3),		0x1, "EQ DHFG value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_DHFG_FRL_TYPE3_ONB),	0x0, "(Onboard) EQ DHFG value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_FILTER_SEL_3G),		0x1, "EQ Filter Sel value for 3G"},
	{E_TO_S(HDMI21__PHY_EQ_FILTER_SEL_6G),		0x1, "EQ Filter Sel value for 6G"},
	{E_TO_S(HDMI21__PHY_EQ_FILTER_SEL_FRL_TYPE1),0x1, "EQ Filter Sel value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQ_FILTER_SEL_FRL_TYPE2),0x1, "EQ Filter Sel value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQ_FILTER_SEL_FRL_TYPE3),0x1, "EQ Filter Sel value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_G1_SEL_3G),			0x3, "EQ G1 Sel value for 3G"},
	{E_TO_S(HDMI21__PHY_EQ_G1_SEL_6G),			0x3, "EQ G1 Sel value for 6G"},
	{E_TO_S(HDMI21__PHY_EQ_G1_SEL_FRL_TYPE1),	0x3, "EQ G1 Sel value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQ_G1_SEL_FRL_TYPE2),	0x3, "EQ G1 Sel value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQ_G1_SEL_FRL_TYPE3),	0x3, "EQ G1 Sel value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_EQ_G2_SEL_3G),			0x0, "EQ G2 Sel value for 6G"},
	{E_TO_S(HDMI21__PHY_EQ_G2_SEL_6G),			0x0, "EQ G2 Sel value for 3G"},
	{E_TO_S(HDMI21__PHY_EQ_G2_SEL_FRL_TYPE1),	0x0, "EQ G2 Sel value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQ_G2_SEL_FRL_TYPE2),	0x0, "EQ G2 Sel value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQ_G2_SEL_FRL_TYPE3),	0x0, "EQ G2 Sel value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CED_OPEN_LENGTH_TMDS),		0x4, "CED Open Length for TMDS mode"},
	{E_TO_S(HDMI21__PHY_CED_OPEN_LENGTH_FRL),		0x2, "CED Open Length for FRL mode"},
	{E_TO_S(HDMI21__PHY_TMDS_OPEN_LENGTH),		0x3, "TMDS Open Length"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_3G),			0x3, "EQ SumBias value for 6G"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_6G),			0x3, "EQ SumBias value for 3G"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_FRL_TYPE1),	0x3, "EQ SumBias value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_FRL_TYPE2),	0x3, "EQ SumBias value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_FRL_TYPE3),	0x3, "EQ SumBias value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DAC_BIAS_3G),			0x3, "EQ DACBias value for 6G"},
	{E_TO_S(HDMI21__PHY_DAC_BIAS_6G),			0x3, "EQ DACBias value for 3G"},
	{E_TO_S(HDMI21__PHY_DAC_BIAS_FRL_TYPE1),	0x3, "EQ DACBias value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DAC_BIAS_FRL_TYPE2),	0x3, "EQ DACBias value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DAC_BIAS_FRL_TYPE3),	0x3, "EQ DACBias value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PERIOD_3G),			0xC, "EQ DAC_BIAS value for 6G"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PERIOD_6G),			0xC, "EQ DAC_BIAS value for 3G"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE1),	0xC, "EQ DAC_BIAS value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE2),	0xF, "EQ DAC_BIAS value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE3),	0xF, "EQ DAC_BIAS value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DFE_A_ON_FRL_TYPE2),		0x1, "DFE A ON Value for FRL Rate 5~6"},
	{E_TO_S(HDMI21__PHY_DFE_B1_ON_FRL_TYPE2),		0x1, "DFE B1 ON Value for FRL Rate 5~6"},
	{E_TO_S(HDMI21__PHY_DFE_B2_ON_FRL_TYPE2),		0x1, "DFE B2 ON Value for FRL Rate 5~6"},
	{E_TO_S(HDMI21__PHY_DFE_B3_ON_FRL_TYPE2),		0x1, "DFE B3 ON Value for FRL Rate 5~6"},
	{E_TO_S(HDMI21__PHY_DFE_B4_ON_FRL_TYPE2),		0x1, "DFE B4 ON Value for FRL Rate 5~6"},
	{E_TO_S(HDMI21__PHY_DFE_B5_ON_FRL_TYPE2),		0x1, "DFE B5 ON Value for FRL Rate 5~6"},
	{E_TO_S(HDMI21__PHY_DFE_A_ON_FRL_TYPE1),		0x1, "DFE A ON Value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_B1_ON_FRL_TYPE1),		0x1, "DFE B1 ON Value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_B2_ON_FRL_TYPE1),		0x0, "DFE B2 ON Value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_B3_ON_FRL_TYPE1),		0x0, "DFE B3 ON Value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_B4_ON_FRL_TYPE1),		0x0, "DFE B4 ON Value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_B5_ON_FRL_TYPE1),		0x0, "DFE B5 ON Value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_LEV_B1_MODE_FRL10), 0x0, "(O20/E60A0) Set 1 to override I2C DFE LEVEL Manual B1 on FRL10"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_LEVEL_B1_MODE),		0x0, "(O20/E60A0)DBG : Set 1 to use I2C DFE LEVEL Manual B1"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_LEVEL_B2_MODE),		0x0, "(O20/E60A0)DBG : Set 1 to use I2C DFE LEVEL Manual B2"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_LEVEL_B3_MODE),		0x0, "(O20/E60A0)DBG : Set 1 to use I2C DFE LEVEL Manual B3"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_LEVEL_B4_MODE),		0x0, "(O20/E60A0)DBG : Set 1 to use I2C DFE LEVEL Manual B4"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_LEVEL_B5_MODE),		0x0, "(O20/E60A0)DBG : Set 1 to use I2C DFE LEVEL Manual B5"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B1_LEVEL_LN0), 0x0, "DBG : Value of LN0 Manual DFE B1 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B2_LEVEL_LN0), 0x0, "DBG : Value of LN0 Manual DFE B2 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B3_LEVEL_LN0), 0x0, "DBG : Value of LN0 Manual DFE B3 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B4_LEVEL_LN0), 0x0, "DBG : Value of LN0 Manual DFE B4 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B5_LEVEL_LN0), 0x0, "DBG : Value of LN0 Manual DFE B5 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B1_LEVEL_LN1), 0x0, "DBG : Value of LN1 Manual DFE B1 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B2_LEVEL_LN1), 0x0, "DBG : Value of LN1 Manual DFE B2 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B3_LEVEL_LN1), 0x0, "DBG : Value of LN1 Manual DFE B3 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B4_LEVEL_LN1), 0x0, "DBG : Value of LN1 Manual DFE B4 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B5_LEVEL_LN1), 0x0, "DBG : Value of LN1 Manual DFE B5 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B1_LEVEL_LN2), 0x0, "DBG : Value of LN2 Manual DFE B1 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B2_LEVEL_LN2), 0x0, "DBG : Value of LN2 Manual DFE B2 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B3_LEVEL_LN2), 0x0, "DBG : Value of LN2 Manual DFE B3 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B4_LEVEL_LN2), 0x0, "DBG : Value of LN2 Manual DFE B4 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B5_LEVEL_LN2), 0x0, "DBG : Value of LN2 Manual DFE B5 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B1_LEVEL_LN3), 0x0, "DBG : Value of LN3 Manual DFE B1 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B2_LEVEL_LN3), 0x0, "DBG : Value of LN3 Manual DFE B2 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B3_LEVEL_LN3), 0x0, "DBG : Value of LN3 Manual DFE B3 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B4_LEVEL_LN3), 0x0, "DBG : Value of LN3 Manual DFE B4 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_I2C_DFE_B5_LEVEL_LN3), 0x0, "DBG : Value of LN3 Manual DFE B5 when Manual mode is ON"},
	{E_TO_S(HDMI21__PHY_FLT_TIMER_2000_11_8),  0x7, " Value for 0x48:0x5E FLT_TIMER_2000[11:8]"},
	{E_TO_S(HDMI21__PHY_FLT_TIMER_2000_7_0),   0x8, " Value for 0x48:0x5F FLT_TIMER_2000[7:0]"},
	{E_TO_S(HDMI21__PHY_I2C_DELTA_EN_MODE),	   0x1, "(O20~E60A0 Only) Value for I2C delta scan en mode"},
	{E_TO_S(HDMI21__PHY_I2C_DELTA_EN_VAL),	   0x1, "(O20~E60A0 Only) Value for I2c delta en val"},
	{E_TO_S(HDMI21__PHY_DELTA_SCAN2_MODE),	   0x1, " Value for Delta_Scan2_mode on non mode0-2 tmds case"},
	{E_TO_S(HDMI21__PHY_ADAPTIVE_PERIOD_3GTMDS),		   0x1,	" Value for Adaptive period for 3G TMDS Mode"}, 
	{E_TO_S(HDMI21__PHY_ADAPTIVE_PERIOD_SEL_3GTMDS),    0x1,	" Value for Adaptive period sel for 3G TMDS Mode"},
	{E_TO_S(HDMI21__PHY_ADAPTIVE_PERIOD_6G_FRL),	   0x1,	" Value for Adaptive period for TMDS6G/FRL Mode"}, 
	{E_TO_S(HDMI21__PHY_ADAPTIVE_PERIOD_SEL_6G_FRL),  0x5,	" Value for Adaptive period sel for TMDS6G/FRL Mode"},
	{E_TO_S(HDMI21__PHY_DFE_N1_3G),			0x0, "DFE N1 value for 6G"},
	{E_TO_S(HDMI21__PHY_DFE_N1_6G),			0x0, "DFE N1 value for 3G"},
	{E_TO_S(HDMI21__PHY_DFE_N1_FRL_TYPE1),	0x0, "DFE N1 value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_N1_FRL_TYPE2),	0x4, "DFE N1 value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DFE_N1_FRL_TYPE3),	0x4, "DFE N1 value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DFE_N2_3G),			0x0, "DFE N2 value for 6G"},
	{E_TO_S(HDMI21__PHY_DFE_N2_6G),			0x0, "DFE N2 value for 3G"},
	{E_TO_S(HDMI21__PHY_DFE_N2_FRL_TYPE1),	0x0, "DFE N2 value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_N2_FRL_TYPE2),	0x0, "DFE N2 value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DFE_N2_FRL_TYPE3),	0x0, "DFE N2 value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DFE_N2_ON_3G),			0x0, "DFE N2_ON value for 6G"},
	{E_TO_S(HDMI21__PHY_DFE_N2_ON_6G),			0x0, "DFE N2_ON value for 3G"},
	{E_TO_S(HDMI21__PHY_DFE_N2_ON_FRL_TYPE1),	0x0, "DFE N2_ON value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_N2_ON_FRL_TYPE2),	0x0, "DFE N2_ON value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DFE_N2_ON_FRL_TYPE3),	0x0, "DFE N2_ON value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PRE_3G),			0x3, "DFE UPDN Period Pre value for 6G"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PRE_6G),			0x3, "DFE UPDN Period Pre value for 3G"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE1),	0x3, "DFE UPDN Period Pre value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE2),	0x4, "DFE UPDN Period Pre value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE3),	0x4, "DFE UPDN Period Pre value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DFE_IDR_ADJ_3G),			0x1, "IDR Adj value for 6G"},
	{E_TO_S(HDMI21__PHY_DFE_IDR_ADJ_6G),			0x0, "IDR Adj value for 3G"},
	{E_TO_S(HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE1),	0x1, "IDR Adj value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE2),	0x1, "IDR Adj value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE3),	0x1, "IDR Adj value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_3G),			0x2, "DFE N1 value for 6G"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_6G),			0x2, "DFE N1 value for 3G"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_FRL_TYPE1),	0x1, "DFE N1 value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_FRL_TYPE2),	0x1, "DFE N1 value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_FRL_TYPE3),	0x1, "DFE N1 value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_CTS_TYPE1),	0x0, "DFE N1 value for FRL Rate 1~4 on CTS Mode"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_CTS_TYPE2),	0x0, "DFE N1 value for FRL Rate 5 on CTS Mode"},
	{E_TO_S(HDMI21__PHY_DELTA_M_AD_CTS_TYPE3),	0x0, "DFE N1 value for FRL Rate 6 on CTS Mode"},
	{E_TO_S(HDMI21__PHY_TCS_STATE_HIST_DEPTH), 0x4, "FRL Mode, TCS State History Depth(Max:10)"},
	{E_TO_S(HDMI21__PHY_TCS_STATE_HIST_MATCH), 	0x2, "FRL Mode, TCS State History Match Val"},
	{E_TO_S(HDMI21__PHY_FLT_STATE_MATCH), 	0x1, "FRL Mode, FLT State Match Val"},
	{E_TO_S(HDMI21__PHY_CH0_SSB_CHECK_ON), 0x1, "Set to 1 to detected RS33(ChSrSsb)"},
	{E_TO_S(HDMI21__PHY_FRL_EQ_SWWA_OPTION_1), 	0x2, "Option Value for FRL SWWA FLT_STATE==1 YES case"},
	{E_TO_S(HDMI21__PHY_FRL_EQ_SWWA_OPTION_2),  24, "Option Value for FRL SWWA FLT_STATE==1 No  case"},
	{E_TO_S(HDMI21__PHY_FRL_EQ_SWWA_OPTION_3), 0x0, "Option Value for ChSrSsb exception"},
	{E_TO_S(HDMI21__PHY_DFE_CENTER_SWWA), 			0x0, "Set 1 to enable DFE Center SW WA for FRL"},
	{E_TO_S(HDMI21__PHY_DFE_CENTER_SWWA_ROUND_UP),  0x0, "Option for rounding UP on DFE Center calcuation"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE0_ONBOARD),		0x8, "Onboard PHY RS Gain value for TMDS 3G/6G mode"}, 
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE1_ONBOARD), 	0x8, "Onboard PHY RS Gain value for FRL1~4 mode"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE2_ONBOARD), 	0x8, "Onboard PHY RS Gain value for FRL5 mode."},
	{E_TO_S(HDMI21__PHY_RS_GAIN_TYPE3_ONBOARD), 	0x8, "Onboard PHY RS Gain value for FRL6 mode."},
	{E_TO_S(HDMI21__PHY_EQICTRL_3G_ONBOARD),		0x4, "Onboard Value of 0x28:0x24 eq_ictrl for TMDS 3G"},		
	{E_TO_S(HDMI21__PHY_EQICTRL_6G_ONBOARD),		0x4, "Onboard Value of 0x28:0x24 eq_ictrl for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_EQICTRL_FRL_TYPE1_ONBOARD),	0x4, "Onboard Value of 0x28:0x24 eq_ictrl for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_EQICTRL_FRL_TYPE2_ONBOARD),	0x4, "Onboard Value of 0x28:0x24 eq_ictrl for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_EQICTRL_FRL_TYPE3_ONBOARD),	0x4, "Onboard Value of 0x28:0x24 eq_ictrl for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_3G_ONBOARD),			0x4, "Onboard Value of 0x28:0x70 ctrl_vref for TMDS 3G"},		
	{E_TO_S(HDMI21__PHY_CTRL_VREF_6G_ONBOARD),			0x4, "Onboard Value of 0x28:0x70 ctrl_vref for TMDS 6G"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_FRL_TYPE1_ONBOARD),	0x4, "Onboard Value of 0x28:0x70 ctrl_vref for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_FRL_TYPE2_ONBOARD),	0x5, "Onboard Value of 0x28:0x70 ctrl_vref for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_CTRL_VREF_FRL_TYPE3_ONBOARD),	0x5, "Onboard Value of 0x28:0x70 ctrl_vref for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_3G_ONBOARD),			0x3, "Onboard EQ SumBias value for 6G"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_6G_ONBOARD),			0x3, "Onboard EQ SumBias value for 3G"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_FRL_TYPE1_ONBOARD),	0x3, "Onboard EQ SumBias value for FRL Rate 1~4"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_FRL_TYPE2_ONBOARD),	0x3, "Onboard EQ SumBias value for FRL Rate 5"},
	{E_TO_S(HDMI21__PHY_SUM_BIAS_FRL_TYPE3_ONBOARD),	0x3, "Onboard EQ SumBias value for FRL Rate 6"},
	{E_TO_S(HDMI21__PHY_CTRL_RBIAS_FRL_TYPE3),	0xF, "RBIAS on FRL_TYPE3"},
	{E_TO_S(HDMI21__PHY_CTRL_RBIAS_FRL_TYPE2),	0xF, "RBIAS on FRL_TYPE2"},
	{E_TO_S(HDMI21__PHY_CTRL_RBIAS),				0xF, "Phy Ctrl RBias Value"},
	{E_TO_S(HDMI21__PHY_CTRL_RBIAS_CTS_MODE),		0xF, "Phy Ctrl RBias Value for FRL CTS Mode"},
	{E_TO_S(HDMI21__PHY_PHANTOM_MAN_VAL),			0x1, "Phy Phantom Man Val"},
	{E_TO_S(HDMI21__PHY_PHANTOM_FIXED_MODE),		0x1, "Phy Phantom Fixed Mode value"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH0),		0x6, "RS Gain on CTS mode FRL Rate 1~4 Ch0"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH1),		0x6, "RS Gain on CTS mode FRL Rate 1~4 Ch1"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH2),		0x6, "RS Gain on CTS mode FRL Rate 1~4 Ch2"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH3),		0x6, "RS Gain on CTS mode FRL Rate 1~4 Ch3"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH0),		0x2, "RS Gain on CTS mode FRL Rate 5 Ch0"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH1),		0x2, "RS Gain on CTS mode FRL Rate 5 Ch1"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH2),		0x2, "RS Gain on CTS mode FRL Rate 5 Ch2"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH3),		0x2, "RS Gain on CTS mode FRL Rate 5 Ch3"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH0),		0x6, "RS Gain on CTS mode FRL Rate 6 Ch0"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH1),		0x6, "RS Gain on CTS mode FRL Rate 6 Ch1"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH2),		0x6, "RS Gain on CTS mode FRL Rate 6 Ch2"},
	{E_TO_S(HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH3),		0x6, "RS Gain on CTS mode FRL Rate 6 Ch3"},
	{E_TO_S(HDMI21__PHY_DFE_ADD_VAL_ON_CTS),		0x0, "DFE mode set to Add val on FRL CTS Mode"},
	{E_TO_S(HDMI21__PHY_P0_ENABLE_MANUAL_EQ),		0x0, "PORT 0 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI21__PHY_P0_MANUAL_CS_VAL_CH0),  0xA, "PORT 0 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI21__PHY_P0_MANUAL_CS_VAL_CH1),  0xA, "PORT 0 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI21__PHY_P0_MANUAL_CS_VAL_CH2),  0xA, "PORT 0 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI21__PHY_P0_MANUAL_CS_VAL_CH3),  0xA, "PORT 0 : If Manual EQ is enable, value of TCS CH3"},
	{E_TO_S(HDMI21__PHY_P1_ENABLE_MANUAL_EQ),		0x0, "PORT 1 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI21__PHY_P1_MANUAL_CS_VAL_CH0),  0xA, "PORT 1 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI21__PHY_P1_MANUAL_CS_VAL_CH1),  0xA, "PORT 1 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI21__PHY_P1_MANUAL_CS_VAL_CH2),  0xA, "PORT 1 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI21__PHY_P1_MANUAL_CS_VAL_CH3),  0xA, "PORT 1 : If Manual EQ is enable, value of TCS CH3"},
	{E_TO_S(HDMI21__PHY_P2_ENABLE_MANUAL_EQ),		0x0, "PORT 2 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI21__PHY_P2_MANUAL_CS_VAL_CH0),  0xA, "PORT 2 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI21__PHY_P2_MANUAL_CS_VAL_CH1),  0xA, "PORT 2 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI21__PHY_P2_MANUAL_CS_VAL_CH2),  0xA, "PORT 2 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI21__PHY_P2_MANUAL_CS_VAL_CH3),  0xA, "PORT 2 : If Manual EQ is enable, value of TCS CH3"},
	{E_TO_S(HDMI21__PHY_P3_ENABLE_MANUAL_EQ),		0x0, "PORT 3 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI21__PHY_P3_MANUAL_CS_VAL_CH0),  0xA, "PORT 3 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI21__PHY_P3_MANUAL_CS_VAL_CH1),  0xA, "PORT 3 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI21__PHY_P3_MANUAL_CS_VAL_CH2),  0xA, "PORT 3 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI21__PHY_P3_MANUAL_CS_VAL_CH3),  0xA, "PORT 3 : If Manual EQ is enable, value of TCS CH3"},
	{E_TO_S(HDMI21__PHY_P4_ENABLE_MANUAL_EQ),		0x0, "PORT 4 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI21__PHY_P4_MANUAL_CS_VAL_CH0),  0xA, "PORT 4 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI21__PHY_P4_MANUAL_CS_VAL_CH1),  0xA, "PORT 4 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI21__PHY_P4_MANUAL_CS_VAL_CH2),  0xA, "PORT 4 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI21__PHY_P4_MANUAL_CS_VAL_CH3),  0xA, "PORT 4 : If Manual EQ is enable, value of TCS CH3"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_MODE_CH0), 0x0, "(E60 Only) 0x38:0x82 I2C_Data_Delta_Mode_Ch0"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_MODE_CH1), 0x0, "(E60 Only) 0x38:0x82 I2C_Data_Delta_Mode_Ch1"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_MODE_CH2), 0x0, "(E60 Only) 0x38:0x82 I2C_Data_Delta_Mode_Ch2"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_MODE_CH3), 0x0, "(E60 Only) 0x38:0x82 I2C_Data_Delta_Mode_Ch3"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_CH0), 0x0, "(E60 Only) 0x38:0x83 I2C_Data_Delta_Ch0"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_CH1), 0x0, "(E60 Only) 0x38:0x83 I2C_Data_Delta_Ch1"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_CH2), 0x0, "(E60 Only) 0x38:0x84 I2C_Data_Delta_Ch2"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DDELTA_CH3), 0x0, "(E60 Only) 0x38:0x84 I2C_Data_Delta_Ch3"},
	{E_TO_S(HDMI21__PHY_E60_I2C_DATA_SIGN), 0x1, "(E60 Only) 0x38:0x7B bit[6] I2C_DATA_SIGN"},
	{E_TO_S(HDMI21__PHY_E60_PAT_FILTER_SEL), 0x0, "(E60 Only) 0x38:0xF3 bit[6] PAT_FILTER_SEL"},
	{E_TO_S(HDMI21__PHY_E60_CED_CHK_BYPASS), 0x0, "(E60 Only) 0x38:0xAB bit[4] CED CHK BYPASS"},
	{E_TO_S(HDMI21__PHY_E60_DFE_DELTA_ON), 0x0, "(E60 Only) 0x38:0x63 bit[0] DFE_DELTA_ON"},
	{E_TO_S(HDMI21__PHY_E60_DFE_NEW_M),	0x0, "(E60 Only) 0x38:0x50 bit[0] DFE_NEW_MODE"},
	{E_TO_S(HDMI21__PHY_E60_DFE_NEW_CHAR), 0x1E, "(E60 Only) 0x38:0x51 bit[5:0] dfe_new_char_num"},
	//E60B0 
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_CTS_TYPE3), 0x4, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(FRL_Rate6)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_CTS_TYPE3), 0x4, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(FRL_Rate6)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_CTS_TYPE3), 0x4, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(FRL_Rate6)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_CTS_TYPE3), 0x4, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(FRL_Rate6)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_CTS_TYPE2), 0x3, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(FRL_Rate5)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_CTS_TYPE2), 0x3, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(FRL_Rate5)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_CTS_TYPE2), 0x3, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(FRL_Rate5)"},
    {E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_CTS_TYPE2), 0x3, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(FRL_Rate5)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_FRL_TYPE3), 0x4, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(FRL_Rate6)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_FRL_TYPE3), 0x4, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(FRL_Rate6)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_FRL_TYPE3), 0x4, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(FRL_Rate6)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_FRL_TYPE3), 0x4, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(FRL_Rate6)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_FRL_TYPE2), 0x3, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(FRL_Rate5)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_FRL_TYPE2), 0x3, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(FRL_Rate5)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_FRL_TYPE2), 0x3, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(FRL_Rate5)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_FRL_TYPE2), 0x3, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(FRL_Rate5)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_FRL_TYPE1), 0x2, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(FRL_Rate1)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_FRL_TYPE1), 0x2, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(FRL_Rate1)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_FRL_TYPE1), 0x2, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(FRL_Rate1)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_FRL_TYPE1), 0x2, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(FRL_Rate1)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_6G), 0x2, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(6G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_6G), 0x2, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(6G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_6G), 0x2, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(6G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_6G), 0x2, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(6G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH0_3G), 0x2, "(E60B0 Only) 0x48:0x16 bit[3:0] eq_rs_man_ch0(3G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH1_3G), 0x2, "(E60B0 Only) 0x48:0x17 bit[3:0] eq_rs_man_ch1(3G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH2_3G), 0x2, "(E60B0 Only) 0x48:0x18 bit[3:0] eq_rs_man_ch2(3G)"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MAN_CH3_3G), 0x2, "(E60B0 Only) 0x48:0x19 bit[3:0] eq_rs_man_ch3(3G)"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_HDMI20), 0x0, "(E60B0 Only) 0x68:0x2a bit[4] Manual HDMI21 Mode Selection"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_HDMI20_6G), 0x1, "(E60B0 Only) 0x68:0x2a bit[4] Manual HDMI21 Mode Selection(6G)"},
	{E_TO_S(HDMI21__PHY_E60_CR_I2C_HDMI21_MODE), 0x1, "(E60B0 Only) 0x68:0x26 bit[4] Manual HDMI21 Mode Selection(All)"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_HDMI21_FRL), 0x1, "(E60B0 Only) 0x68:0x26 bit[0] cr_man_hdmi21(FRL)"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_HDMI21_TMDS), 0x0, "(E60B0 Only) 0x68:0x26 bit[0] cr_man_hdmi21(TMDS)"},
	{E_TO_S(HDMI21__PHY_E60_SCR_MAN_MODE), 0x1, "(E60B0 Only) 0x48:0x88 [1] 1:SCR Manual 0:SCR AUTO"},
	{E_TO_S(HDMI21__PHY_E60_SCR_MAN_VAL), 0x1, "(E60B0 Only) 0x48:0x88"},
	{E_TO_S(HDMI21__PHY_E60_SCR_MAN_VAL_3G), 0x0, "(E60B0 Only) 0x48:0x88"},
	{E_TO_S(HDMI21__PHY_E60_DR_CLKGEN_CAPENB_HDMI14), 0x0, "(E60B0 Only) 0x48:0x01 [4] 0:cap enable for low clock speed"},
	{E_TO_S(HDMI21__PHY_E60_DR_CLKGEN_CAPENB_HDMI20), 0x1, "(E60B0 Only) 0x48:0x01 [4] 1:cap disable for high clock speed"},
	{E_TO_S(HDMI21__PHY_E60_DR_CLKGEN_CAPENB_FRL_RATE1), 0x0, "(E60B0 Only) 0x48:0x01 [4] 1:cap disable for high clock speed"},
	{E_TO_S(HDMI21__PHY_E60_DR_CLKGEN_CAPENB_FRL_RATE2_4), 0x1, "(E60B0 Only) 0x48:0x01 [4] 1:cap disable for high clock speed"},
	{E_TO_S(HDMI21__PHY_E60_DR_CLKGEN_CAPENB_FRL_RATE5), 0x1, "(E60B0 Only) 0x48:0x01 [4] 1:cap disable for high clock speed"},
	{E_TO_S(HDMI21__PHY_E60_DR_CLKGEN_CAPENB_FRL_RATE6), 0x1, "(E60B0 Only) 0x48:0x01 [4] 1:cap disable for high clock speed"},
	{E_TO_S(HDMI21__PHY_E60_EQ_RS_MODE_SEL), 0x1, "(E60B0 Only) 0x48:0x15 [1:0] 00:ck mode, 01:rs manual val, 10:tcs path "},
	{E_TO_S(HDMI21__PHY_E60_RS_SCAN_MODE), 0x0, "(E60B0 Only) 0x48:0x70 [0] rs_scan_mode "},
	{E_TO_S(HDMI21__PHY_E60_RS_SCAN_CAL_NUM), 0x5, "(E60B0 Only) 0x48:0x6f [3:0] rs_scan_cal_num"},
	{E_TO_S(HDMI21__PHY_E60_RS_DATA_NUM), 0x64, "(E60B0 Only) 0x48:0x74 [7:0] rs_data_num"},
	{E_TO_S(HDMI21__PHY_E60_EQ_CAL_RS_TARGET), 0x0, "(E60B0 Only) 0x38:0xdb [7:4] eq_cal_rs_target"},
	{E_TO_S(HDMI21__PHY_E60_EQ_CAL_RS_MODE), 0x0, "(E60B0 Only) 0x38:0xdb [0] cal_rs_mode"},
	{E_TO_S(HDMI21__PHY_E60_RS_SCAN_PRE), 0x5, "(E60B0 Only) 0x48:0x72 [7:4] rs_scan_pre"},
	{E_TO_S(HDMI21__PHY_E60_RS_SCAN_MEAS_11_8), 0x0, "(E60B0 Only) 0x48:0x72 [3:0] rs_scan_meas_11_8 "},
	{E_TO_S(HDMI21__PHY_E60_RS_SCAN_MEAS_7_0), 0x96, "(E60B0 Only) 0x48:0x73 [7:0] rs_scan_meas_7_0 "},
	{E_TO_S(HDMI21__PHY_E60_RS_SCAN_LEVEL_A_11), 0x20, "(E60B0 Only) 0x48:0x75 [6:0] rs_scan_level_a_11 "},
	{E_TO_S(HDMI21__PHY_E60_DFE_B1_FILTER_SEL), 0x0, "(E60B0 Only) 0x38:0x5c [7] dfe_b1_filter_sel "},
	{E_TO_S(HDMI21__PHY_E60_DFE_MINUS_ON), 0x0, "(E60B0 Only) 0x38:0x5c [6] dfe_minus_on"},
	{E_TO_S(HDMI21__PHY_E60_DFE_B1_MINUS), 0x0, "(E60B0 Only) 0x38:0x50 [1] dfe_b1_minus"},
	{E_TO_S(HDMI21__PHY_E60_DFE_ALPHA_MIN_CAL), 0x1, "(E60B0 Only) 0x38:0x57 [0] dfe_b1_minus"},
	{E_TO_S(HDMI21__PHY_E60_SIGN_PATH_B1_ON), 0x0, "(E60B0 Only) 0x38:0x57 [0] dfe_b1_minus"},
	{E_TO_S(HDMI21__PHY_E60_CR_I2C_PLL_MODE_M), 0x0, "(E60B0 Only) 0x68:0x19 [4] cr_i2c_pll_mode_m"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_PLL_MODE_M), 0x0, "(E60B0 Only) 0x68:0x19 [1:0] cr_man_pll_mode_m"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_REFCLK), 0x0, "(E60B0 Only) 0x68:0x68 [0] cr_man_ctrl_refclk"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_RDIV), 0x0, "(E60B0 Only) 0x68:0x6a [0] cr_man_ctrl_rdiv"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_DIV2H_BPL), 0x0, "(E60B0 Only) 0x68:0x6c [0] cr_man_ctrl_div2h_bpl"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_FB_10L_20H), 0x0, "(E60B0 Only) 0x68:0x6e [0] cr_man_ctrl_fb_10l_20h"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_FDIV), 0x0, "(E60B0 Only) 0x68:0x70 [0] cr_man_ctrl_fdiv"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_ICP), 0x0, "(E60B0 Only) 0x68:0x72 [0] cr_man_ctrl_icp"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_LFC1), 0x0, "(E60B0 Only) 0x68:0x74 [0] cr_man_ctrl_lfc1"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_LFC2), 0x0, "(E60B0 Only) 0x68:0x76 [0] cr_man_ctrl_lfc2"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_LFR2), 0x0, "(E60B0 Only) 0x68:0x78 [0] cr_man_ctrl_lfr2"},
	{E_TO_S(HDMI21__PHY_E60_CR_MAN_CTRL_PDR_5L_9H), 0x0, "(E60B0 Only) 0x68:0x7A [0] cr_man_ctrl_pdr_5l_9h"},
	{E_TO_S(HDMI21__PHY_E60_CTRL_SEL_CRREF), 0x1, "(E60B0 Only) 0x68:0x7d [4] ctrl_sel_crref"},
	{E_TO_S(HDMI21__PHY_E60_ERR_OPTION), 0x1, "(E60B0 Only) 0x48:0xA4 [2:1] err_option"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_REPEAT_MODE), 0x5, "(E60B0 Only) 0x38:0x92 [2:0] delta_repeat_mode"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_REPEAT_NONE), 0x0, "(E60B0 Only) 0x38:0x92 [2:0] delta_repeat_mode disable"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_DOWN_GAP), 0x6, "(E60B0 Only) 0x38:0x93 [7:4] delta_down_gap"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_PEREAT_MAX), 0x4, "(E60B0 Only) 0x38:0x93 [3:0] delta_pereat_max"},
	{E_TO_S(HDMI21__PHY_E60_VIDEO_DATA_CNT),		0xA, "(E60B0 Only) Video Data CNT value for 0x38:0xA9"},
	{E_TO_S(HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG),		0x2, "(E60B0 Only) Set Value for SWWA ChoiJinWoo Bug"},
	{E_TO_S(HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR),  0x20, "(E60B0 Only) CHOIJINWOO SWWA Method 1 Thres Val"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_CUTLINE_TYPE3),		0x0, "(E60B0 Only) delta_cutline"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_CUTLINE_TYPE2),		0x0, "(E60B0 Only) delta_cutline"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_CUTLINE_TYPE1),		0x3, "(E60B0 Only) delta_cutline"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_CUTLINE_6G),		0x3, "(E60B0 Only) delta_cutline"},
	{E_TO_S(HDMI21__PHY_E60_DELTA_CUTLINE_3G),		0x3, "(E60B0 Only) delta_cutline"},
	{E_TO_S(HDMI21__PHY_E60_FLT_PRE_CHK_MODE),		0x0, "(E60B0 Only) flt_pre_chk_mode"},
	{E_TO_S(HDMI21__PHY_E60_G2_RESET_OPTION),		0x3, "(E60B0 Only) g2_reset_option"},
	{E_TO_S(HDMI21__PHY_E60_DFE_DELTA_OPTION),		0x0, "(E60B0 Only) dfe_delta_option"},
	{E_TO_S(HDMI21__PHY_E60_DFE_DELTA_ON_M_M),		0x0, "(E60B0 Only) DFE_DELTA_ON_MAN_MODE 0x38:0x63"},
	{E_TO_S(HDMI21__PHY_E60_DFE_DELTA_ON_MAN),		0x0, "(E60B0 Only) DFE_DELTA_ON_MAN 0x38:0x63"},
	{E_TO_S(HDMI21__PHY_E60_DFE_DELTA_SCOPE2),		0x0, "(E60B0 Only) DFE_DELTA_SCOPE2 0x38:0x63"},
	{E_TO_S(HDMI21__PHY_E60_DFE_DONE_BYPASS),		0x0, "(E60B0 Only) DFE_DONE_BYPASS 0x38:0x63"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_MODE_FRL_TYPE3),		0x1, "(E60B0 Only) pi_set_man_mode(12G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_VAL_FRL_TYPE3),		0x0, "(E60B0 Only) dfe_delta_option(12G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_MODE_FRL_TYPE2),		0x1, "(E60B0 Only) pi_set_man_mode(10G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_VAL_FRL_TYPE2),		0x0, "(E60B0 Only) dfe_delta_option(10G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_MODE_FRL_TYPE1),		0x0, "(E60B0 Only) pi_set_man_mode(3G~8G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_VAL_FRL_TYPE1),		0x0, "(E60B0 Only) dfe_delta_option(3G~8G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_MODE_6G),		0x0, "(E60B0 Only) pi_set_man_mode(6G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_VAL_6G),		0x0, "(E60B0 Only) dfe_delta_option(6G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_MODE_3G),		0x0, "(E60B0 Only) pi_set_man_mode(3G)"},
	{E_TO_S(HDMI21__PHY_E60_PI_SET_MAN_VAL_3G),		0x0, "(E60B0 Only) dfe_delta_option(3G)"},
	{E_TO_S(HDMI21__PHY_TCS_ERR_LIMIT_BASIC_FRL_TYPE3_CTS),	0x0, "TCS ERR LIMIT BASIC"},
	{E_TO_S(HDMI21__PHY_TCS_ERR_LIMIT_BASIC_FRL_TYPE2_CTS),	0x0, "TCS ERR LIMIT BASIC"},
	{E_TO_S(HDMI21__PHY_TCS_ERR_LIMIT_BASIC_FRL_TYPE3),	0xA, "TCS ERR LIMIT BASIC"},
	{E_TO_S(HDMI21__PHY_TCS_ERR_LIMIT_BASIC_FRL_TYPE2),	0xA, "TCS ERR LIMIT BASIC"},
	{E_TO_S(HDMI21__PHY_TCS_ERR_LIMIT_BASIC),	0x0, "TCS ERR LIMIT BASIC"},
	{E_TO_S(HDMI21__PHY_TCS_ERR_LIMIT_LOOSE),	0x0, "TCS ERR LIMIT LOOSE"},
	{E_TO_S(HDMI21__PHY_E60_CTRL_EQ_DT_RANGE), 0x0, "(E60B0 Only) EQ DT RANGE"},
	{E_TO_S(HDMI21__PHY_O22_STUDY),				0x0, "(O22 Study) Mode for checking EQ CAL DONE"},
	{E_TO_S(HDMI21__PHY_ONBOARD_MAN_TCS_VAL_MINUS), 0x2, "(O20 Onboard) Minus value for TCS Manual/Add Val"},
	{E_TO_S(HDMI21__PHY_RETRAIN_NO_LANELOCK_TCSLOW), 0x1, "(O20) LaneLock Loss checking on TCS low triggered"},
	{E_TO_S(HDMI21__PHY_FRL_CAL_CLOCK_SPEED_UP), 0x0, "(E60B0) Adjust Cal clock speed(0x0: disable, 0x1: enable)"},
	{E_TO_S(HDMI21__PHY_RS_SCAN_RETRY_DISABLE), 0x0, "RS Scan Retry disable"},
	{E_TO_S(HDMI21__PHY_RS_SCAN_RETRY_COUNT), 0x5, "RS Scan Retry cont"},
	{E_TO_S(HDMI21__PHY_RS_SCAN_RETRY_DIFF), 0x5, "RS Scan Retry Each Channel Max differnece"},
	{E_TO_S(HDMI21__PHY_EQ_SUCCESS_SEL_VAL), 0x7, "Default Value of EQ_SUCCESS_SEL. Only from O26 SoCs"}
};

HDMI20_DEV_CONTROL_T	gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM]=
{
	{E_TO_S(HDMI21__LINK_VMON_SOURCE_TYPE_TMDS),0x0, 	" VMON source(TMDS):  0:PVO/1:HDCPout/2:Deframer/3:VPG/4:VPROC"},
	{E_TO_S(HDMI21__LINK_VMON_SOURCE_TYPE_FRL),	0x4, 	" VMON source(FRL): 0:PVO/1:HDCPout/2:Deframer/3:VPG/4:VPROC"},
	{E_TO_S(HDMI21__LINK_VMON_IRQ_THR_MODE),	0x0, 	" Link 0x1560 [24:24] value. Set 1 increase senitivity "},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_HDCP_1_INTVEC),	0x0,	" ISR Mask for HDCP 1 Unit"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_HDCP_INTVEC),	0x3F0077,	" ISR Mask for HDCP Unit"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_SCDC_INTVEC),	0xD,	" ISR Mask for SCDC Unit"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_PKT_2_INTVEC),	0x0,	" ISR Mask for PKT Unit 2"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_PKT_1_INTVEC),	0x7F,	" ISR Mask for PKT Unit 1"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_PKT_0_INTVEC),	0xE13813,	" ISR Mask for PKT Unit 0"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_2_INTVEC),	0x0,	" ISR Mask for AVPUnit 2"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_T),	0x0005F302,	" ISR Mask for AVPUnit 1 TMDS Mode(default)"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_F),	0x0005F302,	" ISR Mask for AVPUnit 1 FRL Mode(default)"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_T_A),	0x0005E302,	" ISR Mask for AVPUnit 1 TMDS Mode(Audio Ex)"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_F_A),	0x0005E302,	" ISR Mask for AVPUnit 1 FRL Mode(Audio Ex)"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_0_INTVEC),	0x700010,	" ISR Mask for AVPUnit 0"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_2_INTVEC),	0xB,	" ISR Mask for MainUnit2"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_1_INTVEC),	0x0,	" ISR Mask for MainUnit1"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_0_INTVEC),	0xC2E00022,	" ISR Mask for MainUnit0"},
	{E_TO_S(HDMI21__LINK_ISRUNIT_ISRVAL_EARC_INTVEC),		0x3,	" ISR Mask for eARC"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP_1), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_SCDC), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_2), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_1), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_0), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_2), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_1), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_0), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_2), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_1), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_0), 0x0, "Mask Value for triggering VideoChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_HDCP_1), 			0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_HDCP), 			0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_SCDC), 			0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_PKT_2), 			0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_PKT_1), 			0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_PKT_0), 			0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_AVPUNIT_2), 		0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_AVPUNIT_1), 		0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_AVPUNIT_0), 		0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_MAINUNIT_2), 		0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_MAINUNIT_1), 		0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_VIDMUTE_ISRMASK_MAINUNIT_0), 		0x0, "Mask Value for triggering Instant VideoMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP_1), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_SCDC), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_2), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_1), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_0), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_2), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_1), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_0), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_2), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_1), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_0), 0x0, "Mask Value for triggering AudioChange Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_HDCP_1), 			0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_HDCP), 			0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_SCDC), 			0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_PKT_2), 			0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_PKT_1), 			0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_PKT_0), 			0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_AVPUNIT_2), 		0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_AVPUNIT_1), 		0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_AVPUNIT_0), 		0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_MAINUNIT_2), 		0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_MAINUNIT_1), 		0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_AUDMUTE_ISRMASK_MAINUNIT_0), 		0x0, "Mask Value for triggering Instant AudioMute Flag on ISR"},
	{E_TO_S(HDMI21__LINK_PFIFO_ENABLE_MASK),		0x81,	"PFIFO Enable Mask Value"},
	{E_TO_S(HDMI21__LINK_PFIFO_PASS_THRESHOLD),		0x32,	"PFIFO pass(50%) level"},
	{E_TO_S(HDMI21__LINK_PFIFO_LOW_THRESHOLD),		0x04, 	"PFIFO Low ISR Alert Level"},
	{E_TO_S(HDMI21__LINK_PFIFO_HIGH_THRESHOLD),		0x60,	"PFIFO High ISR Alert Level"},
	{E_TO_S(HDMI21__LINK_HDCP_HDCP14DELAY_VAL), 	0x0, 	"HDCP1.4 Path Delay. Val Range : 0~3"},
	{E_TO_S(HDMI21__LINK_MISC_MAIN_HARD_RESET_VAL),	0x3E,	"Link Hard Reset vector"},
	{E_TO_S(HDMI21__LINK_MISC_MAIN_SOFT_RESET_VAL),	0x20, 	"Link Soft Reset vector"},
	{E_TO_S(HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE),	0x24,  	"LInk Reset Value on TCS Toggle"},
	{E_TO_S(HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL), 0x4,	"LInk Reset Value on TCS Done"},
	{E_TO_S(HDMI21__LINK_PDEC_USE_PKT_SNAPSHOT),	0x0,	"Set 1 to enable PKT Decoder Snapshot"},
	{E_TO_S(HDMI21__LINK_VPROC_FRLSYNC_HSYNC_4L),		0xFF0,	"Hsync Value when FRL->VideoSync gen for 4L FRL"},
	{E_TO_S(HDMI21__LINK_VPROC_FRLSYNC_HFRONT_4L),		0xFF0,	"Hfront Value when FRL->VideoSync gen for 4L FRL"},
	{E_TO_S(HDMI21__LINK_VPROC_FRLSYNC_HSYNC_3L),		0xFF0,	"Hsync Value when FRL->VideoSync gen for 3L FRL"},
	{E_TO_S(HDMI21__LINK_VPROC_FRLSYNC_HFRONT_3L),		0x30,	"Hfront Value when FRL->VideoSync gen for 3L FRL"},
	{E_TO_S(HDMI21__LINK_VPROC_FRLSYNC_VSYNC),		0x2,	"Vsync Value when FRL->VideoSync gen"},
	{E_TO_S(HDMI21__LINK_VPROC_FRLSYNC_VFRONT),		0x2,	"Vfront Value when FRL->VideoSync gen"},
	{E_TO_S(HDMI21__LINK_FRL_START_CHK_SB_QST), 	0x0,    "Value for SNPS 0x580 reg bit field [8]"},
	{E_TO_S(HDMI21__LINK_HDMI_TO_DVI_THRESHOLD), 	0x2, 	"Threshold Value for HDMI->DVI detection"},
	{E_TO_S(HDMI21__LINK_DVI_TO_HDMI_THRESHOLD), 	0x1, 	"Threshold Value for DVI->DVI detection"},
	{E_TO_S(HDMI21__LINK_FRL_DEFRAMER_PREAMBLE_LOCK), 0x8, " Value of Preamble Lock on FRL Modes"},
	{E_TO_S(HDMI21__LINK_CRG_FIFO_RESET_HIGH_VAL), 	0xB,	" Reset High value of HDMI TOP CRG FIFO Reset"},
	{E_TO_S(HDMI21__LINK_CRG_FIFO_RESET_LOW_VAL), 	0xA,	" Reset Low value of HDMI TOP CRG FIFO Reset"},
	{E_TO_S(HDMI21__LINK_TOP_SCDC_ISR_MASK),		0x0, 	" Link Top ISR Mask value for SCDC ISR"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVRRIDE_EN),	0x0, 	" Set to 1, to Override SyncGen setting to DBG values"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVR_VIDCONFIG1), 0x0, 	"OverRide Value for 0x428 VPROC_VIDEO_CONFIG_1 Register"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG1),	0x0, 	" OvrRide Value for SyncGen VIDEO_CONFIG_1 Register"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG2),	0x0, 	" OvrRide Value for SyncGen VIDEO_CONFIG_2 Register"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG3),	0x0, 	" OvrRide Value for SyncGen VIDEO_CONFIG_3 Register"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG4),	0x0, 	" OvrRide Value for SyncGen VIDEO_CONFIG_4 Register"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OVR_CONFIG5),	0x0, 	" OvrRide Value for SyncGen VIDEO_CONFIG_5 Register"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_FOR_DSC),		0x1, 	" SyncGen mode for DSC signals"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_VS_ZERO_FOR_DSC), 0x1, 	" Set to 1, to Set VFrontVSync=0 Syncgen in DSC modes"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_VS_ZERO_FOR_GEN1), 0x1, " Set to 1, to set VFrontVSync=0 SyncGen 1"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE),	1, "Set Default Sync Gen Mode"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_HS_ZERO_FOR_GEN1), 1, " Set to 1, to set HfrontHSync=0 SyncGen 1"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_OFF_FOR_UNDER), 0, " 0 is off. Set FRLSYNC Gen to 0 on under set value"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_GENVAL_OVR),	1, "Set 1 to enable SYncGen1 CalFunc Override for 4K/8K"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_VBCONST_HACT),	5500, "below this hactive size will use VBConst=0 for SyncGen"},
	{E_TO_S(HDMI21__LINK_O22_FRLSYNCGEN_VFRONTSYNC), 0x0, "(O22) Values for VFrontVSync Sync Gen"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_DSC_REDUCE_HBACK), 0, "Set this value to non zero to reduce HBACK for DSC SYncGen"},
	{E_TO_S(HDMI21__LINK_FRLSYNCGEN_VBCONST_ZERO_FORCE), 0, "Non zero to always keep VBConst to 0 for Non DSC Signals"},
	{E_TO_S(HDMI21__LINK_DSC_LIMS_HSYNCDELAY0_FACTOR), 20, "(Lim's Method. Factor of HsyncDelay DIV value"},
	{E_TO_S(HDMI21__LINK_DSC_LIMS_ALLOW_EXCEPTION), 1, "(Lim's Method) Allow some exceptions for Lim's method"},
	{E_TO_S(HDMI21__LINK_PDEC_AVMUTE_AUTO_CLEAR_TIME), 2, "0:5sec, 1:2sec, 2:1sec, 3:500msec, 4:250msec"},
	{E_TO_S(HDMI21__LINK_PDEC_AVMUTE_AUTO_CLEAR_ENABLE), 1, "0:Off, else:On"},
	{E_TO_S(HDMI21__LINK_MISC_DATAPATH_RST_ON_UNSTABLE), 1, "1:DataPath Reset on Unstable detection, 0:Off"},
	{E_TO_S(HDMI21__LINK_DATAPATH_ONLY_RST_ON_REAUTH), 1, "1:DataPath Only Reset on HDCP2x Reauth, 0:Off"},
	{E_TO_S(HDMI21__LINK_USE_LINK_VFREQ_COUNTER), 0, "(From O26) 0:Calculate through TMDS Clk(old), 1~100..: Resolution)"},
	{E_TO_S(HDMI21__LINK_DELAY_TO_EQ_SUCCESS_SEL), 130, "(From O26) In TCS Done ISR, delay factor to eq-success-sel 7->8"},
	{E_TO_S(HDMI21__LINK_RST_HDMI_SYN_FOR_CLK_LOSS), 1, "(Only for O26) 1:On, 0:Off"},
	{E_TO_S(HDMI21__LINK_FAULT_INJECTION_VFREQ_COUNT), 0, "(From O26) Fault injection to VFreq HW counter for testing"},
	{E_TO_S(HDMI21__LINK_FRL12G4L_480P_12B_FORCE_WA), 1, "0:Off, FRL_Rate#:12BIT override for 12BIT FRL signls"},
	{E_TO_S(HDMI21__LINK_TEST_SCDC_ERROR_FLAT_ENJECT), 0, "0:Off, 1:Force enject error=0 on SCDC registers"},
	{E_TO_S(HDMI21__LINK_DSC_RESTORE_SYNC_GEN_MODE), 0, "0:Off, 1:Only for issued-case, else:VIC override"},
	{E_TO_S(HDMI21__LINK_WATCHDOG_VRR_VFREQ_WITH_MEASURE), 1, "0:Off, else:check VRR_Base Rate info with real_vfreq"}
};

LX_HDMI20_ERROR_SETTING_T kdrvHDMI21ErrorThres[LX_HDMI20_ERROR_MAXNUM] =
{
	{0x1, 1, 5},
	{0x2, 5, 2},
	{0x4, 2, 3},
	{0x8, 5, 0},
	{0x10, 3, 0},
	{0x20, 2, 5},
	{0x40, 5, 90},
	{0x80, 4, 2}
};

HDMI21_HOST_DIAGNOSIS_ERROR_T gHDMI21hostError[HDMI21_NUM_OF_MAX_PORTS];

/* For Offset Repeatation Experiment */
int		gHdmi21OffsetRepeatIteration[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21OffsetRepeatIndex[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21OffsetRepeatTest[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21OffsetRepeatState[HDMI21_NUM_OF_MAX_PORTS] = {0, };

/* For DFE Repeatation Experiment */
int		gHdmi21DfeRepeatIteration[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21DfeRepeatIndex[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21DfeRepeatTest[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21DfeRepeatState[HDMI21_NUM_OF_MAX_PORTS] = {0, };
UINT32  gHdmi21DfeRepeatErrorCntState[HDMI21_NUM_OF_MAX_PORTS] = {0, };


/* For Eye Measurement */
int		gHdmi21EyePrintMode = 0;
int 	gHdmi21EyeYPrintScale = 3;
int 	gHdmi21EyeMeasure[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int 	gHdmi21EyeXaxis[4] = {1, 0, 1, 0};
int 	gHdmi21EyeYaxis[4] = {1, 1, 0, 0};
int		gHdmi21EyeXposition[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int		gHdmi21EyeYposition[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int 	gHdmi21EyeStage[HDMI21_NUM_OF_MAX_PORTS] = {0, };
UINT32	gHdmi21EyeDataCh0[HDMI21_NUM_OF_MAX_PORTS][127][31];
UINT32	gHdmi21EyeDataCh1[HDMI21_NUM_OF_MAX_PORTS][127][31];
UINT32	gHdmi21EyeDataCh2[HDMI21_NUM_OF_MAX_PORTS][127][31];
UINT32	gHdmi21EyeDataCh3[HDMI21_NUM_OF_MAX_PORTS][127][31];

/* CS eye width */
UINT32 gHdmi21CsEyeWidthCh0[HDMI21_NUM_OF_MAX_PORTS][32];
UINT32 gHdmi21CsEyeWidthCh1[HDMI21_NUM_OF_MAX_PORTS][32];
UINT32 gHdmi21CsEyeWidthCh2[HDMI21_NUM_OF_MAX_PORTS][32];
UINT32 gHdmi21CsEyeWidthCh3[HDMI21_NUM_OF_MAX_PORTS][32];


/* For FRL position search DBG */
int 	gHdmi21FrlErrMeasure[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int 	gHdmi21FrlErrState[HDMI21_NUM_OF_MAX_PORTS] = {0, };
int 	gHdmi21FrlErrDone[HDMI21_NUM_OF_MAX_PORTS][4] = {0, };
int 	gHdmi21FrlValue[HDMI21_NUM_OF_MAX_PORTS][4] = {0, };

/* Cal Test */
HDMI21_PHY_DBG_OFFSET_DATA_T gHdmi21CalTestData[HDMI21_NUM_OF_MAX_PORTS][101] = {0,};
HDMI21_PHY_DBG_DFE_DATA_T gHdmi21DfeTestData[HDMI21_NUM_OF_MAX_PORTS][101] = {0,};

int	gHdmi21WarmMode = 0;
/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
/* Function for IOCTL */
static int __HDMI21_HAL_Rx_DBG_GetHDMIMiscInfo(UINT8 port, LX_HDMI20_RX_HDMI_MISC_T *pData, int size);
static int	__HDMI21_HAL_Rx_DBG_PrintDevVideoController(HDMI21_DEV_VIDEO_CONTROL_LIST_T index);
static int	__HDMI21_HAL_Rx_DBG_PrintDevPhyController(HDMI21_DEV_PHY_CONTROL_LIST_T index);
static int	__HDMI21_HAL_Rx_DBG_PrintDevLinkController(HDMI21_DEV_LINK_CONTROL_LIST_T index);
static int	__HDMI21_HAL_Rx_DBG_PrintDevAudioController(HDMI21_DEV_AUDIO_CONTROL_LIST_T index);

static int __HDMI21_HAL_Rx_Set_PioneerMode(void);
static int __HDMI21_HAL_Rx_Set_UnInitialize(void);
static int __HDMI21_HAL_Rx_Set_HPD(UINT8 port ,UINT8 onOff, UINT8 force);
static int __HDMI21_HAL_Rx_Set_EnableEDID(UINT8 port, UINT8 onOff);
static int __HDMI21_HAL_Rx_Set_HDCP14_KSVList(UINT8 port, LX_HDMI20_HDCP14_RP_T *pData, int size);

//static int __HDMI21_HAL_Rx_Set_HDMIFactor(LX_HDMI20_SETTING_FACTOR_T *pData, int size);
static int __HDMI21_HAL_Rx_Set_HDMIHostErrorThres(LX_HDMI20_ERROR_SETTING_T *pData, int size);
static int __HDMI21_HAL_Rx_Set_DisableHDMI(UINT8 port, int isDisable);
static int __HDMI21_HAL_Rx_Set_InverseHPDControl(UINT8 port, int isInverse);

static int __HDMI21_HAL_Rx_Get_HDCP14(UINT8 port, UINT32 *pData, int size);
static int __HDMI21_HAL_Rx_Get_HDMIState(UINT8 port, LX_HDMI_STATUS_T *pHdmiStatus, int size);
static int __HDMI21_HAL_Rx_Get_HDMIHostError(UINT8 port, UINT32 *pData, int size);
/* End of Static IOCTL Function */


/* Main Thread */
static void __HDMI21_HAL_Rx_MainThread(void);

/* Internal static usage functions : Mostly in Main Thread */
static UINT32 __attribute__((unused)) __HDMI21_HAL_Rx_ALED_TOP_Read(UINT32 addr);					/* Read  Access of ALED Top */ 
static void   __HDMI21_HAL_Rx_ALED_TOP_Write(UINT32 addr, UINT32 data);		/* Write Access of ALED Top */

static __attribute__((unused)) UINT32 __HDMI21_HAL_Rx_ALED_TOP_Read_P23(UINT32 addr);					/* Read  Access of ALED Top */ 
static void   __HDMI21_HAL_Rx_ALED_TOP_Write_P23(UINT32 addr, UINT32 data);		/* Write Access of ALED Top */

static void __HDMI21_HAL_Rx_WatchDog_FilterSelStuck(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_WatchDog_PixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_WatchDog_PhyPdb(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int is5vHigh);
static void __HDMI21_HAL_Rx_WatchDog_PhyConfig(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);	/* Check Current Phy settings with SCDC status*/
static void __HDMI21_HAL_Rx_WatchDog_AVMuteHoldTime(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Get_CheckLocalVideoMuteColor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Get_UpdateClockVfreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet);
static int	__HDMI21_HAL_Rx_Get_IsHwInDVIState(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);	/* Return Value : DVI=1, HDMI=0 */
static int	__HDMI21_HAL_Rx_Get_IsStableTimingInfoEmpty(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static HDMI21_HAL_PHY_INITIATED_MODE_T __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static int __HDMI21_HAL_Rx_Get_VsiHdmiFormatToViC(UINT8 hdmiFormat);

static int __attribute__((unused)) __HDMI21_HAL_Rx_Get_CEDError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 channel);
static int	__HDMI21_HAL_Rx_Get_ListOfNotSupportingVideo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static int	__HDMI21_HAL_Rx_Get_IsPC(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static int	__HDMI21_HAL_Rx_Check_RSScanResult(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static int 	__HDMI21_HAL_Rx_Get_IsVideoStable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static LX_HDMI_EXT_FORMAT_INFO_T __HDMI21_HAL_Rx_Get_Convert3DtoLG3DFormat(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI_VSI_3D_STRUCTURE_T vsi3Ddata);
static int  __HDMI21_HAL_Rx_Get_CheckChangeFlag(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Set_LocalVideoMuteColor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 isYCbCr444or422);
static void __HDMI21_HAL_Rx_Set_ResetLink(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int mode);
static void __HDMI21_HAL_Rx_Set_InitDevHandler(UINT8 isResume);	/* Resets almost all data in Dev Handler */
static void __HDMI21_HAL_Rx_Set_TopColorSpaceConversion(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Get_CheckTopColorSpaceConversion(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

static void __HDMI21_HAL_Rx_Set_PutHDMIHostError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI20_ERROR_TYPE_T type, int errorStatus);
static void __HDMI21_HAL_Rx_Set_ClearHDMIHostError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI20_ERROR_TYPE_T type);
static void __HDMI21_HAL_Rx_Set_ResetHandlerData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isCablePlug);
static void __HDMI21_HAL_Rx_Set_Video_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Set_TMDS_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isforceSet);
static void __HDMI21_HAL_Rx_Set_Audio_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Set_HDCP_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Set_CompensateStableHVactiveTotal(LX_HDMI_TIMING_INFO_T *_pData);
static void __HDMI21_HAL_Rx_Set_CompensateWithVicCode(LX_HDMI_TIMING_INFO_T *_pData, UINT32 vicCode, HDMI21_HAL_PHY_INITIATED_MODE_T mode, int isVrr);
static void __HDMI21_HAL_Rx_Set_PixelRepetitionMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isRepetition);
static void __HDMI21_HAL_Rx_Set_IsrProfiler(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, unsigned int *counter);
static int	__HDMI21_HAL_Rx_Set_MapHwMemory(int isClear);		/* Ioremap of HW address : LINK/TOP/ALED/PHY */
static int	__HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int clear);
static int __HDMI21_HAL_Rx_Set_Compensate3DTimingInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI_TIMING_INFO_T *_pData, LX_HDMI_EXT_FORMAT_INFO_T lg3DData);
static void __HDMI21_HAL_Rx_Get_PollCvtemStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static int __HDMI21_HAL_Rx_Set_IdleTick(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int is5VHigh);
static void __HDMI21_HAL_Rx_Set_LowPowerSettingStep0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static void __HDMI21_HAL_Rx_Set_LowPowerSettingStep1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static void __HDMI21_HAL_Rx_Set_LowPowerSettingStep2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static void __HDMI21_HAL_Rx_Set_LowPowerSettingStep3(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static void __HDMI21_HAL_Rx_Set_LowPowerSettingStep4(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static void __HDMI21_HAL_Rx_Set_LowPowerSettingStep5(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static int  __HDMI21_HAL_Rx_Get_IsCurrentIdleState(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_Set_CheckDoviClearTimer(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __attribute__((unused)) __HDMI21_HAL_Rx_Set_LowPowerSettingStepMid(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower);
static int __HDMI21_HAL_Rx_Get_CheckDolbyUniqueDRM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 verbose);
static int __HDMI21_HAL_Rx_Get_LinkTopVfreqCounter(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool highRes);
static void __HDMI21_HAL_Rx_Set_LinkTopVfreqCounter(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isProgressive, bool enable);

/* DBG */
static void __HDMI21_HAL_Rx_DBG_PrintSync(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 diffmode);
static void __HDMI21_HAL_Rx_DBG_PrintSavedEDID(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_DBG_PrintVideo(int port);
static void __HDMI21_HAL_Rx_DBG_PrintPhySetting(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_DBG_PrintIRQ(int port);
static void 	__HDMI21_HAL_Rx_Get_PrintDscCvtemPpsData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
char *__isr_type_to_str(HDMI21_ISR_TYPE_T type);
char *__deepcolor_to_str(HDMI21_HAL_VIDEO_DEEPCOLOR_MODE_T type);
char *__tfr_to_str(int type);

static void __HDMI21_HAL_Rx_DBG_CalculateFrlPosition(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_DBG_CalculatePhyEyeDiagrame(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static UINT32 __HDMI21_HAL_Rx_DBG_SetEyeCalPosition(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isXPositive, bool isYpositive, UINT32 x, UINT32 y);
static UINT32 __HDMI21_HAL_Rx_DBG_GetDeltaError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 ch);
static void __HDMI21_HAL_Rx_DBG_PrintEyeDiagramChr(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_HAL_Rx_DBG_PrintEyeDiagramHex(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static char *__val_to_graphic(UINT32 val);
static char *__val_to_hex(UINT32 val);
static char *__csc_to_str(int type);
static char *phymode_type_to_str(HDMI21_HAL_PHY_INITIATED_MODE_T type);
static char *__val_to_CsWidthGraphicPositive(UINT32 val);
static char *__val_to_CsWidthGraphicNegative(UINT32 val);

static void __HDMI21_HAL_Rx_DBG_CalculateOffsetRepeat(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_PHY_DBG_OFFSET_DATA_T *pVal);
static void __HDMI21_HAL_Rx_DBG_CalculateDfeRepeat(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_PHY_DBG_DFE_DATA_T *pVal);
static int __HDMI21_HAL_Rx_Reset_AsyncBridge(int port);
static void __HDMI21_HAL_Rx_Reset_ChipHdmiSynTop(int port, bool ResetOnTrue);


/* 2025/04/29 won.hur : From SJ.YOUM */
#ifdef INCLUDE_KDRV_PQE_PM
static int __HDMI21_HAL_Rx_CB_PqePmRunTimeCallback(int action);
#endif
/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/
/* 2025/04/29 won.hur : From SJ.YOUM */
#ifdef INCLUDE_KDRV_PQE_PM
static struct pqe_pm_config __pqe_pm_config =
{
	.name	= "hdmi20_pm",
	.opt	= PQE_PM_OPT_MONITOR,
	.order	= 0,
	.callback = __HDMI21_HAL_Rx_CB_PqePmRunTimeCallback,
};
#endif

static unsigned int *__sMapped_address; // For DBG: REG Read/Write macro

/* For Data comparision with 0 data */
UINT8 __sZero19bytes[19] = {0,};

/* 2018/01/18 : Check Power only mode through /proc/cmdline which is symbolic saved to Linux kernel : saved_command_line */
char *pwrModeSymbol = "pwrOnly";
char *factoryModeSymbol = "factory";
char *soCtsSymbolHdmi = "socts";

/* For device supporitng 3D without VSI */
static  HDMI21_NON_VSI_3D_TIMING_T __sTBL_EXT_INFO[ ] =
{	/// hAct_info	vAct_info	scan_info	hAct_buf	vAct_buf	scan_buf	extInfo_buf
	{	1280,	1470,	1,		1280, 	720, 	1,		LX_HDMI_EXT_3D_FRAMEPACK }, 		//720p FP
	{	1920,	2205,	1,		1920, 	1080, 	1,		LX_HDMI_EXT_3D_FRAMEPACK },		//1080p FP
	{	1920,	2228,	1,		1920, 	1080, 	0,		LX_HDMI_EXT_3D_FRAMEPACK },		//1080i FP

	{	2560,	720,	1,		1280, 	720, 	1,		LX_HDMI_EXT_3D_SBSFULL }, 			//720p SSF
	{	3840,	1080,	1,		1920, 	1080, 	1,		LX_HDMI_EXT_3D_SBSFULL },			//1080p SSF
	{	3840,	1080,	0,		1920, 	1080, 	0,		LX_HDMI_EXT_3D_SBSFULL },			//1080i SSF

	{	1280,	1440,	1,		1280, 	720, 	1,		LX_HDMI_EXT_3D_LINE_ALTERNATIVE }, 	//720p LA
	{	1920,	2160,	1,		1920, 	1080, 	1,		LX_HDMI_EXT_3D_LINE_ALTERNATIVE },	//1080p LA

	{	1920,	1103,	1,		1920, 	1080, 	0,		LX_HDMI_EXT_3D_FIELD_ALTERNATIVE },	//1080i FA
};

HDMI21_VMON_VIDEO_SYNC_T gPrevSync[HDMI21_NUM_OF_MAX_PORTS]; /* For HDMI21_HAL_Rx_DBG_PrintSync History */

static DEFINE_MUTEX(__DSC_mutex);
/*========================================================================================
  Implementation Group
  ========================================================================================*/


/*========================================================================================
  Implementation Group
  ========================================================================================*/
void HDMI21_Set_PreInit(int isReset)
{
	UINT32 data;

	HDMI20_PRINT("HDMI20 Module : [%s]. \n", isReset?"Reset":"Enable");

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){

		/* Block PSLVERROR */
		HDMI21_REG_WR(0xC8000018, 0x1); /* APB2_CPU, address for O26 (same with O24) */
		HDMI21_REG_WR(0xCC200018, 0x1); /* PMCU_CPU, address for O26 (same with O24) */

		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xCA433200 */
		HDMI21_REG_RD(0xCA3A7018, data); // CTOP_SYN -> CRG_TOP_WOC -> NISOL_R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xCA3A7018, data);
	

		#if 0 /* 2025/03/24 won.hur : This part does not exist in O26. Maybe because of ION chipset */
		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xC8863200, data); // CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0xF); 
		HDMI21_REG_WR(0xC8863200, data);
		#endif

		/* 2022/05/02 : DPMS should be disabled from init */
		HDMI21_REG_RD(0xCA3A4004, data); // CTOP_MIP_Adapter -> MIP_Adapter_DPM -> MIP_HDMI_DPM01 -> reg_phy_tx_det_disable
		data |= (0x1F);
		HDMI21_REG_WR(0xCA3A4004, data);
	
	
		/* 2023/01/16 won.hur : SCDC Chip Idx*/
		gHdmi21ScdcDeviceID_H = HDMI20_SCDC_CHIP_CHARACTER_O26_H;
		gHdmi21ScdcDeviceID_L = HDMI20_SCDC_CHIP_CHARACTER_O26_L;
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){

		/* Test  : Block PSLVERROR */
		HDMI21_REG_WR(0xC8000018, 0x1); /* APB2_CPU */
		HDMI21_REG_WR(0xCC200018, 0x1); /* PMCU_CPU */

		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xCA433200 */
		HDMI21_REG_RD(0xF33F4018, data); // CTOP_SYN -> CRG_TOP_WOC -> NISOL_R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xF33F4018, data);
		
		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xC8863200, data); // CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0xF); 
		HDMI21_REG_WR(0xC8863200, data);

		// Confirm!!!!
		/* 2022/05/02 : DPMS should be disabled from init */
		HDMI21_REG_RD(0xC8864004, data); // CTOP_MIP_Adapter -> MIP_Adapter_DPM -> MIP_HDMI_DPM01 -> reg_phy_tx_det_disable
		data |= (0x1F);
		HDMI21_REG_WR(0xC8864004, data);
	
	
		/* 2023/01/16 won.hur : SCDC Chip Idx*/
		gHdmi21ScdcDeviceID_H = HDMI20_SCDC_CHIP_CHARACTER_O24_H;
		gHdmi21ScdcDeviceID_L = HDMI20_SCDC_CHIP_CHARACTER_O24_L;
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xC61B3200/0xC8515200 */
		HDMI21_REG_RD(0xF3514018, data); // CTOP_SYN -> CRG_TOP_WOC -> NISOL_R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xF3514018, data);
	

		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xC61B3200, data); 
		data &= (~0x3); 
		HDMI21_REG_WR(0xC61B3200, data);
	
		HDMI21_REG_RD(0xC8515200, data); 
		data &= (~0x3); 
		HDMI21_REG_WR(0xC8515200, data);
	
		/* 2023/01/16 won.hur : SCDC Chip Idx*/
		gHdmi21ScdcDeviceID_H = HDMI20_SCDC_CHIP_CHARACTER_M23_H;
		gHdmi21ScdcDeviceID_L = HDMI20_SCDC_CHIP_CHARACTER_M23_L;

	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xCA433200 */
		HDMI21_REG_RD(0xF30D6120, data); // CTOP_SYN -> BND_AON -> AON POR R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xF30D6120, data);
		
		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xCA433200, data); // CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0xF); 
		HDMI21_REG_WR(0xCA433200, data);

		/* 2022/05/02 : DPMS should be disabled from init */
		HDMI21_REG_RD(0xCA432060, data); // CTOP_SYN -> BND_EDID -> DPM_0
		data |= (0xF0);
		HDMI21_REG_WR(0xCA432060, data);
	
		/* 2023/01/16 won.hur : SCDC Chip Idx*/
		gHdmi21ScdcDeviceID_H = HDMI20_SCDC_CHIP_CHARACTER_O22_H;
		gHdmi21ScdcDeviceID_L = HDMI20_SCDC_CHIP_CHARACTER_O22_L;

	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		/* Nothing */
		if(isReset) {
			/* GPIO_17_7 set */
			HDMI21_REG_RD(0xFD510400, data); 
			data |= 0x80; 
			HDMI21_REG_WR(0xFD510400, data);

			HDMI21_REG_RD(0xFD5103FC, data); 
			data |= 0x80; 
			HDMI21_REG_WR(0xFD5103FC, data);

			/* EDID_NISOL PAD MUX SELECT */
			HDMI21_REG_RD(0xC93B847C, data); 
			data &= (~0x0F000000); data |= (0x01000000);
			HDMI21_REG_WR(0xC93B847C, data);

			/* HDMI_LINK soft reset */
			HDMI21_REG_RD(0xC3320004, data); 
			data |= 0x00040200; 
			HDMI21_REG_WR(0xC3320004, data);

			HDMI21_REG_RD(0xC3320008, data); 
			data |= 0x00080800; 
			HDMI21_REG_WR(0xC3320008, data);

			/* HPD output enable */
			HDMI21_REG_WR(0xC98A2400, 0x0);

			#if 0 // Set this before HPD */
			HDMI21_REG_RD(0xC98A2404, data);
			data &= (~0x1F1F);
			HDMI21_REG_WR(0xC98A2404, data);
			#endif

			/* EARC PLL Set */
			#if 0	 /* 2020/03/13 : JongSang Oh, WonChang Shin told me to get rid of this */
			HDMI21_REG_WR(0xC98A2448, 0x41808800); /* EARCPLL PDB OFF */
			HDMI21_REG_WR(0xC98A244C, 0x639D5E05);
			HDMI21_REG_WR(0xC98A2454, 0xBF000000);
			HDMI21_REG_WR(0xC98A2448, 0x4180C800); /* EARCPLL PDB ON */
			#endif

			/* APB Clock Mux Select */
			HDMI21_REG_WR(0xC98A2014, 0x40000000); /* 400 -> XTAL */
		}

		/* 2023/01/16 won.hur : SCDC Chip Idx*/
		gHdmi21ScdcDeviceID_H = HDMI20_SCDC_CHIP_CHARACTER_E60_H;
		gHdmi21ScdcDeviceID_L = HDMI20_SCDC_CHIP_CHARACTER_E60_L;

	}
	else { 
		HDMI21_REG_RD(0xC9306008, data);
		HDMI21_REG_WR(0xC9306000, 0x0);

		if(isReset){
			HDMI21_REG_WR(0xC9306008, 0x90);
			HDMI21_REG_WR(0xC930600C, 0x00900090);
			HDMI21_REG_WR(0xC9306010, 0x00900090);
		}
		else{
			HDMI21_REG_WR(0xC9306008, 0x80);
			HDMI21_REG_WR(0xC930600C, 0x00800080);
			HDMI21_REG_WR(0xC9306010, 0x00800080);
		}
	
		/* 2023/01/16 won.hur : SCDC Chip Idx*/
		gHdmi21ScdcDeviceID_H = HDMI20_SCDC_CHIP_CHARACTER_O20_H;
		gHdmi21ScdcDeviceID_L = HDMI20_SCDC_CHIP_CHARACTER_O20_L;
	}

	HDMI20_PRINT("HDMI20 Module : PreInit Done!\n");
}

int HDMI21_HAL_Rx_Set_V4l2PortActivate(UINT8 port, int isActive)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = -1;

	do {
		/* Port defence */
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Set Handler Flag */
		if(isActive > 0)	{ 
			_p->isV4l2Activated = true; 
			ret = 1;
		}
		else { 
			_p->isV4l2Activated = false; 
			ret = 0;
		}

		/* 2020/07/29 */
		gHdmi21InputChgCnt++;
		if(gHdmi21InputChgCnt == 0) gHdmi21InputChgCnt = 1; // Overflow protection code
	
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_Get_IsV4l2PortActivated(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = -1;

	do {
		/* Port defence */
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Set Handler Flag */
		if(_p->isV4l2Activated)	{ ret = 1; }
		else 					{ ret = 0; }
	
	} while(0);

	return ret;
}

int HDMI21_Version(void)
{
	int ret = HDMI21_KERNEL_DRIVER_VER;
	return ret;
}


void HDMI21_Set_Line_Debugger(UINT32 value)
{
	gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value = value;
	return;
}

UINT32 HDMI21_Get_Line_Debugger(void)
{
	return gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value ;
}


void HDMI21_Set_Audio_Line_Debugger(UINT32 value)
{
	gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = value;
	return;
}

UINT32 HDMI21_Get_Audio_Line_Debugger(void)
{
	return gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value; 
}

/* Function that will be called before initialization */
int HDMI21_Open(void)
{
	int i;
	UINT32 data;
	UINT32 hpd_port[5];

	#ifdef HDMI21_PORT5_USE_HW_OPTION 
	/* HW Option */
	LX_OVI_HW_DISPLAY_INFO_T hwOpt;
	#endif

	gHdmi21KdrvOpenCnt++;
	if(gHdmi21KdrvOpenCnt == 0)  gHdmi21KdrvOpenCnt = 1;


	HDMI20_INFO("[%s:%d] Called. Current Open Status[%d]. Max Available Ports[%d]\n", __F__, __L__, gIsHDMI21KdrvOpen, g_hdmi20_number_of_ports);

	if(gIsHDMI21KdrvOpen >= 0){
		HDMI20_INFO("Ignore Multiple Open\n");
		return 0;
	}

	/* Just to be sure */
	memset(&__sZero19bytes, 0, 19);

	/* Read HW Opt */
	#ifdef HDMI21_PORT5_USE_HW_OPTION
	OVI_HAL_GetHWDisplayOption(&hwOpt);
	if(hwOpt.frcChipType > LX_OVI_FRC_CHIP_INTERNAL) {
		gIsHDMI8KModel = 1;	
	}
	else
	{	
		gIsHDMI8KModel = 0;	
	}
	#else
	gIsHDMI8KModel = 0;
	#endif

	/* Step 0. Clear Reset Bits */
	HDMI21_Set_PreInit(1);
	HDMI21_Set_PreInit(0);


	/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
	if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
		/* 2025/09/02 won.hur : Q980B 64bit */
		gHDMI21RxDevLinkControler[HDMI21__LINK_DSC_LIMS_ALLOW_EXCEPTION].value = 0;

		/* 2025/07/21 won.hur : consider this SW WA for only O26 */
		gHDMI21RxDevLinkControler[HDMI21__LINK_DSC_RESTORE_SYNC_GEN_MODE].value = 1;

		/* 2025/04/08 won.hur : To be changed to '1' once O26-Vfreq counter has been verified. */
		gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value = 1000;


		/* 2023/06/01 */
		gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value = 2;
		//gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_FOR_DSC].value = 2;

		/* DSC Configures */
		gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DSC_REDUCE_HBACK].value = 2;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_DSC_USE_GREAT_LIM_FORMULA].value = 1;	// O22 vs M23

		/* Low Power : Enabled with 3 sec configuration */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 3000;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT].value  = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23].value = 1;

		/* 2022/08/31 : SICDTV-11647 */
		/* 2023/05/28 : Do not implement this SW WA from O24 and on... */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_STUCK_SWWA_THRES].value = 0;

		#if 0 /* 2025/03/24 won.hur : Does not exist in O26 (Probably due to ION chipset) */
		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC8863000, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863000, data);

		HDMI21_REG_RD(0xC8863004, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863004, data);

		HDMI21_REG_RD(0xC8863008, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863008, data);

		HDMI21_REG_RD(0xC886300C, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc886300C, data);
		#endif

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC870E808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC870E80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC870E810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC870E814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC870E818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC870E81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC870E820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC870E824, 0x33221100); // esm_id_duk_4
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV(O24, A0)) {
		/* 2023/06/01 */
		gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value = 2;
		//gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_FOR_DSC].value = 2;

		/* DSC Configures */
		gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DSC_REDUCE_HBACK].value = 2;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_DSC_USE_GREAT_LIM_FORMULA].value = 1;	// O22 vs M23

		/* Low Power : Enables with 3 sec configuration */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 3000;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT].value  = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23].value = 1;

		/* 2022/08/31 : SICDTV-11647 */
		/* 2023/05/28 : Do not implement this SW WA from O24 and on... */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_STUCK_SWWA_THRES].value = 0;

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC8863000, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863000, data);

		HDMI21_REG_RD(0xC8863004, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863004, data);

		HDMI21_REG_RD(0xC8863008, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863008, data);

		HDMI21_REG_RD(0xC886300C, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc886300C, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC8D0E808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC8D0E80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC8D0E810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC8D0E814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC8D0E818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC8D0E81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC8D0E820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC8D0E824, 0x33221100); // esm_id_duk_4
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV(M23, A0)) {
		/* Not Yet */
		gLowPowerState1Tick = 2;
		gLowPowerState2Tick = 5;

		/* Low Power : Disabled for now.. */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT].value  = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23].value = 1;

		/* 2022/08/31 : SICDTV-11647 */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_STUCK_SWWA_THRES].value = 3;

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC61B3000, data);
		data &= (~0x000f000f); 
		data |= (0x00090009); 
		HDMI21_REG_WR(0xC61B3000, data);

		HDMI21_REG_RD(0xC851501C, data);
		data &= (~0x0f000f00); 
		data |= (0x09000900); 
		HDMI21_REG_WR(0xC851501C, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC47CE808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC47CE80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC47CE810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC47CE814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC47CE818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC47CE81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC47CE820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC47CE824, 0x33221100); // esm_id_duk_4
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)) {
		/* DSC Configures */
		//gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DSC_REDUCE_HBACK].value = 1;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_DSC_USE_GREAT_LIM_FORMULA].value = 1;

		/* No Low Power Mode for O20 */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value = 0;
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT].value  = 0;

		/* Incase low power is enable for O22, HDCP23 should be on */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23].value = 1;

		/* Need to update */

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xCA433000, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA433000, data);

		HDMI21_REG_RD(0xCA433004, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA433004, data);

		HDMI21_REG_RD(0xCA433008, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA433008, data);

		HDMI21_REG_RD(0xCA43300C, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA43300C, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC890E808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC890E80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC890E810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC890E814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC890E818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC890E81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC890E820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC890E824, 0x33221100); // esm_id_duk_4
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0)) {
		/* DSC Clock set to 600MHz : Not nessessary, E60 default CRG setting 0xC93B8014 [13:12] is set to 0x0 for 594MHz */

		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC98A2430, data);
		data &= (~0x7878F138); 
		data |= (0x48489108); 
		HDMI21_REG_WR(0xC98A2430, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC3410008, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC341000C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC3410010, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC3410014, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC3410018, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC341001C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC3410020, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC3410024, 0x33221100); // esm_id_duk_4
	}
	else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		/* No Low Power Mode for O20 */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 0;
		
		/* DSC Clock set to 600MHz */
		HDMI21_REG_WR(HDMI21_CHIP_O20_CRG_SETTING_REG  , 0x00000800);

		HDMI21_REG_RD(0xC903500C,data);
		data |= 0x00007777;
		HDMI21_REG_WR(0xC903500C, data);

		/* O20 B0 HPD */
		HDMI21_REG_WR(0xC3300048, 0x7C000000);
	
		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
		HDMI21_REG_RD(0xC330004C, data);
		data &= (~0x1F1F0000);
		data |= (0x1F1F0000);
		HDMI21_REG_WR(0xC330004C, data);

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC3300844, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300844, data);

		HDMI21_REG_RD(0xC3300854, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300854, data);

		HDMI21_REG_RD(0xC3300864, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300864, data);

		HDMI21_REG_RD(0xC3300874, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300874, data);

		HDMI21_REG_RD(0xC3300884, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300884, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC91E0008, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC91E000C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC91E0010, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC91E0014, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC91E0018, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC91E001C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC91E0020, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC91E0024, 0x33221100); // esm_id_duk_4
		//HDMI21_REG_WR(0xC91E0028, 0xdeadbeef); // esm_id_devnum

		/* ESM Mem Blocking OFF */
		HDMI21_REG_WR(0xC9306930, 0x00000011); // CTOP SYN HDMI

		/* Set Current Driver to MAX */
		HDMI21_REG_WR(0xC330080C, 0x07110711);
	}

	/* Step 1. Init Rx Device handler */
	__HDMI21_HAL_Rx_Set_InitDevHandler(0);
	
	/* Step 2. Ioremap HW to memory */
	if(__HDMI21_HAL_Rx_Set_MapHwMemory(0) != RET_OK)
	{
		HDMI20_ERROR("Failed to map HW memory! Abort HDMI2.1 Driver Open\n");
		return -1;
	}

	/* check warm boot condition */
	if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
		gHdmi21WarmMode = 0;
		for(i = 0; i<g_hdmi20_number_of_ports; i++)
		{
			hpd_port[i] = gHDMI21RxHandler[i].top_read(HDMI21_TOP_REG_AD_MAIN_HPD_DDC_SET);
			HDMI20_PRINT("%s:%d warm mode check : HPD_Port[%d] = [0x%x]\n",__func__,__LINE__, i, hpd_port[i]);
			if( (hpd_port[i] & 0x11) == 0x11) {
				HDMI20_PRINT("HPD_Port[%d] = [0x%x] : Maybe warm stanby mode !!!\n", i, hpd_port[i]);
				gHdmi21WarmMode = 1;
				break;
			}
		}
	}

	/* PSLV ERROR */
	if(lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
		/* APB2_CPU, PMCU_CPU -> Mask PSLAVERROR */
		HDMI21_REG_WR(0xC8000018, 0x1); /* APB2_CPU : Same address for O26 and O24 */
		HDMI21_REG_WR(0xCC200018, 0x1); /* PMCU_CPU : Same address for O26 and O24 */

		for(i=0; i<g_hdmi20_number_of_ports; i++) {
			gHDMI21RxHandler[i].top_write(HDMI21_TOP_REG_AD_REG_MON_SEL, HDMI21_TOP_FIELD_REG_PSLVERR_OFF_O24);	
		}
	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
		/* Test  : Block PSLAVERROR */
		HDMI21_REG_WR(0xC8000018, 0x1);
		HDMI21_REG_WR(0xCC200018, 0x1);

		for(i=0; i<g_hdmi20_number_of_ports; i++) {
			gHDMI21RxHandler[i].top_write(HDMI21_TOP_REG_AD_REG_MON_SEL, HDMI21_TOP_FIELD_REG_PSLVERR_OFF_O24);	
		}
	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		for(i=0; i<g_hdmi20_number_of_ports; i++) {
			gHDMI21RxHandler[i].top_write(HDMI21_TOP_REG_AD_REG_MON_SEL, HDMI21_TOP_FIELD_REG_PSLVERR_OFF);	
		}
	}
	/* End of PSLV ERROR */

	
	/* DSC Shawdow Init */
	HDMI21_DSC_Rx_Set_Initialize();

	/* Step 2-1. Initiate for each ports */
	for(i = 0; i<g_hdmi20_number_of_ports; i++)
	{
		HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl(i);

		/* Initiate Host Error memory */
		memset((void *)&gHDMI21hostError[i], 0, sizeof(HDMI21_HOST_DIAGNOSIS_ERROR_T));

		/* Clear Space for EDID memory */
		HDMI20_INFO("RX[%d] : Initiate Internal EDID space\n", i);
		gHDMI21RxHandler[i].wasEdidWritten = 0;
		memset((void *)&gHDMI21RxHandler[i].edidData, 0, HDMI21_HAL_SIZE_OF_EDID);

		/* Clear Packet Buffer */
		__HDMI21_HAL_Rx_Set_ResetHandlerData(&gHDMI21RxHandler[i], 1);
		gHDMI21RxHandler[i].restartHpdFlagUp = 0;

		/* 2019/04/02 : memset 0 to Sync Monitor History data */
		memset((void *)&gPrevSync[i], 0, sizeof(HDMI21_VMON_VIDEO_SYNC_T));

		/* ALED TOP : Set HPD Mux */
		data = gHDMI21RxHandler[i].aled_read(HDMI21_ALED_RC_REG_AD_HPD);
		data |= (HDMI21_ALED_RC_FIELD_O_REG_HPD);
		gHDMI21RxHandler[i].aled_write(HDMI21_ALED_RC_REG_AD_HPD, data);

		data = gHDMI21RxHandler[i].aled_read(HDMI21_ALED_RC_AD_EDDC_0);
		data &= (~HDMI21_ALED_RC_FIELD_EDDC_DISABLE);
		gHDMI21RxHandler[i].aled_write(HDMI21_ALED_RC_AD_EDDC_0, data);

		/* Set HDCP video path to non-ESM(2.2) */
		gHDMI21RxHandler[i].top_write(0xFB0, 0x1);

		if(lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
			/* Initiate Low Power Module */
			HDMI21_HAL_Rx_Set_LowPowerMode(i, 0, 1, 0);
		}
	}

	/* ALED TOP : Set I2C driver clock sel : LG Tapbook DVI Issue at End of 2016 */
	/* Need to figure this out before chip bring up */
	__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0x6);
	if(lx_chip() == LX_CHIP_M23) {
		__HDMI21_HAL_Rx_ALED_TOP_Write_P23(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0x6);
	}


	if ( lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)) {
		/* Do nothing */
		HDMI21_Rx_Audio_Path_Init();
		HDMI21_Rx_Audio_RequestIrq();
		HDMI21_Rx_Audio_Path_Irq_Enable(); 
	}
	else {
		HDMI21_Rx_Audio_Path_Init();
		HDMI21_Rx_Audio_RequestIrq();
		HDMI21_Rx_Audio_Path_Irq_Enable(); 
	}
	HDMI21_Tx_EARC_InitializeMemAccess();
	HDMI21_Tx_eARC_Open();

	/* 2018/01/18 : Check Power only mode through /proc/cmdline which is symbolic saved to Linux kernel : saved_command_line */
	if(saved_command_line != NULL){
		if(strstr(saved_command_line, pwrModeSymbol) != NULL){
			HDMI20_INFO("Detected Power Only Mode. Disable 3G 4K 10M SW WA");
		}
		else if(strstr(saved_command_line, factoryModeSymbol) != NULL){
			HDMI20_INFO("Detected Factory Mode. Disable 3G 4K 10M SW WA");
		}

		if(strstr(saved_command_line, soCtsSymbolHdmi) != NULL){
			HDMI20_INFO("Detected SoCTS Mode. Disable PKTERR SW WA");
			gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_CNT].value = 0;
		}
		else {
			HDMI20_INFO("Detected Normal Mode(Not SoCTS)");
		}
	}

	/* 2019/09/18 : O20B0 has different settings compared to O20A0 */
	if(lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		/* LINK ISR : PKTFIFO, PKTDEC */
		/* Do not use PKT FIFO on O20B0. PKTDEC is better*/
		/* 2020/11/25 : Use PFIFO for VSIF, regarding issues with Dolby Negative Certificate test */
		gHDMI21RxDevLinkControler[HDMI21__LINK_PFIFO_ENABLE_MASK].value = 0x81;
		gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_PKT_1_INTVEC].value = 0x7F;

		/* Instead, use PKT_2 INT for AVI/VSI/DRM/VSI */
		gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_PKT_2_INTVEC].value = 0x00C13800;
		gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_0_INTVEC].value = 0xC2E00022;
		
		/* Disable the PKT_0 INT for AVI/VSI/DRM/VSI */
		gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_PKT_0_INTVEC].value &= (~0x00C13800);


		if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
			gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VBCONST_ZERO_FORCE].value = 1; /* 2021/06/02 Hong Yong Vin  O22 vs M23 */
			gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value = 2;
			//gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_FOR_DSC].value = 2;
	
			/* 2022/04/15 */
			gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_LOW_VAL].value = 0xA0A;
			gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_HIGH_VAL].value = 0xB0B;

			/* DATA PATH RESET SPLIT */
			//gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x24; /* 2022/04/28 : JINWOO CHOI.... CTS issue */
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x404; // O22 vs M23
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL].value = 0x404;

			gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value = 0; // O22 vs M23
			gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value = 0x1; // O22 vs M23

			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value = 0x7;

			//Disable E60B0 2SCOMPLIMENT SW WA 
			gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value = 0x0; // O22 vs M23
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV(O24, A0)) {
			gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VBCONST_ZERO_FORCE].value = 1; /* 2021/06/02 Hong Yong Vin  O22 vs M23 */
			gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value = 2;
			//gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_FOR_DSC].value = 2;
	
			/* 2022/04/15 */
			gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_LOW_VAL].value = 0xA0A;
			gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_HIGH_VAL].value = 0xB0B;

			/* DATA PATH RESET SPLIT */
			//gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x24; /* 2022/04/28 : JINWOO CHOI.... CTS issue */
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x404; // O22 vs M23
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL].value = 0x404;

			gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value = 0; // O22 vs M23
			gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value = 0x1; // O22 vs M23

			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value = 0x7;

			//Disable E60B0 2SCOMPLIMENT SW WA 
			gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value = 0x0; // O22 vs M23
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV(M23, A0)) {
			/* 2022/04/15 */
			gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_LOW_VAL].value = 0xA0A;
			gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_HIGH_VAL].value = 0xB0B;

			/* DATA PATH RESET SPLIT */
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x24; /* 2022/04/28 : JINWOO CHOI.... CTS issue */
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL].value = 0x404;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value = 0x7;
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)) {
			gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_VBCONST_ZERO_FORCE].value = 1; /* 2021/06/02 Hong Yong Vin */

			/* DATA PATH RESET SPLIT */
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x404;
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL].value = 0x404;

			/* No more LN Lock Retrain SW WA for E60 B0 */
			gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value = 0;
			gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value = 0x1;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value = 0x7;

			//Disable E60B0 2SCOMPLIMENT SW WA 
			gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value = 0x0;
		
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)) {
			/* 2020/08/24 : JangSilverLight */
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE2].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3].value = 0xA;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE3].value = 0x7;

			/* DATA PATH RESET SPLIT */
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value = 0x404;
			gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL].value = 0x404;

			//E60B0-Phy additional setting
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_RBIAS_FRL_TYPE2].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_RBIAS_FRL_TYPE3].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_RBIAS_CTS_MODE].value = 0x4;

			gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE3].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE2].value = 0x0;
			
			/* No more LN Lock Retrain SW WA for E60 B0 */
			gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value = 0;
			gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value = 0x1;

			//E60B0 Phy-DevCtrl setting
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value = 0x7;

			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value = 0x7;

			//E60B0-PHY ANA_CDR_SEL
			//E60B0-PHY CDR_FLTR_CTRL
			gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0].value = 0x1;
			//E60B0-PHY DELTA_ADD_VAL
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL3G].value  = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL10G].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL12G].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL12G_CTS].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL10G_CTS].value = 0x1;


			//E60B0-PHY TCS_ERR_SEL
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE3].value = 0x9B;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE2].value = 0x9B;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE1].value = 0x9B;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_3G].value = 0xCB;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_6G].value = 0xDB;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_3G].value = 0x93;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_3].value = 0x93;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_2].value = 0x93;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_1_0].value = 0x93;
			//E60B0-PHY IDR_ADJ
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_3G].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE1].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE2].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE3].value = 0x1;
			//EQICTRL
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_CTS_TYPE2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_CTS_TYPE3].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE3].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE2].value = 0x7;
			//SUM_BIAS
			gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE3].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE2].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE1].value = 0x3;
			//CTRL_VREF
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE3_ONBOARD].value = 0x6;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE3].value = 0x6;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE2_ONBOARD].value = 0x6;
			gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE2].value = 0x6;
			//DHFG
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE3_ONB].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE2].value = 0x1;
			//EQ_HDMI20_VAL
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3].value = 0x0;
			//EQ_HDMI20_MAN
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE3].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE2].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE1].value = 0x0;
			//EQ_HDMI20_VAL
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3].value = 0x0;
			//EQ_HDMI20_MAN
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE3].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE2].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE1].value = 0x0;
			//TCS_PERIOD_SEL
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL12G].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL12G_CTS].value = 0x2;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL_CTS].value = 0x2;

			//DELTA_MAX_ADJUST
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE1].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_FRL_TYPE1].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE2].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_FRL_TYPE2].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE3].value = 0x0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_FRL_TYPE3].value = 0x0;

			//DFE_B2 ~ B5
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B2_ON_FRL_TYPE1].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B3_ON_FRL_TYPE1].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B4_ON_FRL_TYPE1].value = 0x1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B5_ON_FRL_TYPE1].value = 0x1;
			//DFE_N1
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_FRL_TYPE1].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_6G].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_3G].value = 0x4;
			//DFE_UPDN_PERIOD
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE1].value = 0xF;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_6G].value = 0xF;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_3G].value = 0xF;
			//DFE_UPDN_PRE
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_6G].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_3G].value = 0x7;

			//3G6G Set end
			//TCS_ADD_VAL0~4
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND0].value = 0x8;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND1].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND2].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND3].value = 0x7;
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND4].value = 0x3;

			//2020.06.16 se.kim 
			//DFE_UPDN_PERIOD
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE3].value = 0x3f;
			//DFE_N1
			gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_FRL_TYPE3].value = 0x0;
			//delta-cutline
			gHDMI21RxDevPhyControler[HDMI21__PHY_E60_DELTA_CUTLINE_TYPE3].value = 0x1;
			//tcs_err_limit_basic
			gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERR_LIMIT_BASIC].value = 0x0;
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
			/* 2020/01/14 : CastleSliver 
			   22  HDMI21__PHY_DELTA_ADD_VAL_FRL12G_CTS 1
			   96  HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3 0
			   116 HDMI21__PHY_EQ_DHFG_FRL_TYPE3 0
			   230 HDMI21__PHY_DELTA_M_AD_CTS_TYPE3 0
			   270 HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH0 3
			   271 HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH1 3
			   272 HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH2 3
			   273 HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH3 3
			   */

			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL12G_CTS].value = 1;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3].value = 0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE3].value = 0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE3].value = 0;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH0].value = 2;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH1].value = 2;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH2].value = 2;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH3].value = 2;


			/*2020/03/12 : Kwon O-Gyu & DG KIM told me to set this */
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH0].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH1].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH2].value = 0x4;
			gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH3].value = 0x4;

			gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE2].value = 0x0;


			/* 2020/02/24 : For E60A0, lets say HDMI port2,3 would be redriver IC */
			if(lx_chip_rev( ) == LX_CHIP_REV( E60, A0) )
			{
				gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_FORCE_8K_MODEL].value = 1;
				gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3].value = 0x2;
			}
		}
	}

	/* 2025/04/29 won.hur : From SJ.YOUM */
	#ifdef INCLUDE_KDRV_PQE_PM
	if  ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		if(pqe_pm_register(&__pqe_pm_config) < 0) {
			HDMI20_ERROR("[%s:%d] Error returned by pqe_pm_register()\n", __F__, __L__);
		}
	}
	#endif


	/* Inidicator that the driver module is opened */
	gIsHDMI21KdrvOpen = 1;

	/* 2019/08/26 : Set Default FRL 10G EDID for port 4 */
	if  ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		HDMI21_HAL_Rx_Set_EDID(4, (UINT8 *)&gHdmi21webOs22_4K_Off, sizeof(gHdmi21webOs22_4K_Off), 1);
	}
	else {
		HDMI21_HAL_Rx_Set_EDID(4, (UINT8 *)&gHdmi21TestEDID_FRL10G_Jang, sizeof(gHdmi21TestEDID_FRL10G_Jang), 1);
	}

	#ifdef ENABLE_HDMI_CEC
	if  ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		hdmicec_init();
	#endif
	
	return RET_OK;
}



int HDMI21_Suspend(void)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_OK;
	UINT32 data;
	int i;
	int cnt = HDMI21_HAL_DRIVER_SUSPEND_TRY_COUNT;	

	HDMI20_INFO("HDMI2.1 Kernel Driver Suspend Start\n");

	/*Audio CSD change interrupt disable*/
	HDMI21_Rx_Audio_Path_Irq_Disable();

	/* Kill Main Thread & wait for it to end */
	gHDMI21Thread.isAlive = 0;
	while(1)
	{
		if(gHDMI21Thread.stamp == 0){
			HDMI20_INFO("Success closing HDMI2.1 Main thread. [%d]/[%d]\n", cnt, HDMI21_HAL_DRIVER_SUSPEND_TRY_COUNT);
			ret = RET_OK;
			break;
		}

		if(cnt <= 0)
		{
			HDMI20_INFO("Failed to exit HDMI2.1 Main thread\n");
			break;
		}
		cnt--;
		msleep(gHDMI21Thread.mSleep);
	}

	HDMI21_Tx_eARC_Suspend();

	for(i=0;i<g_hdmi20_number_of_ports;i++){
		_p = &gHDMI21RxHandler[i];

		if(_p->gWasHDCP22Written > 0) {
			HDMI21_HDCP23_Module_Set_Close();
		}
		
		HDMI21_HAL_Rx_Set_AudioReset(i);
		HDMI21_HAL_Rx_Set_Audio_Configure(i, 0);	/* 2018/11/16 */

		/* ESM keys will be cleared once DC power is off. Need to set flag down */
		HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(_p, OFF);

		/* HPD control : JangSilverLight told us to not set this to low*/
		//__HDMI21_HAL_Rx_Set_HPD(_p->port, 0, 0);

		/* Disable Top IRQ */
		_p->control_top_irq(0);

		/* Clear Device Driver Handler HDMI Data */
		__HDMI21_HAL_Rx_Set_ResetHandlerData(_p, 1);
	}

	if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
		HDMI21_REG_RD(0xCA3A6004, data);	// CTOP_SYN -> EDID_SYN -> EDID_SYN_01
		data &= (~0x1F1F);
		data |= (0x1F00);
		HDMI21_REG_WR(0xCA3A6004, data);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
		HDMI21_REG_RD(0xC8862004, data);	// CTOP_SYN -> EDID_SYN -> EDID_SYN_01
		data &= (~0x1F1F);
		data |= (0x1F00);
		HDMI21_REG_WR(0xC8862004, data);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
		HDMI21_REG_RD(0xC61B2004, data);
		data &= (~0x1F1F);
		data |= (0x1F00);
		HDMI21_REG_WR(0xC61B2004, data);	
	
		HDMI21_REG_RD(0xF3512004, data);
		data &= (~0x1F1F);
		data |= (0x1F00);
		HDMI21_REG_WR(0xF3512004, data);	
	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
		HDMI21_REG_RD(0xCA432004, data);	// CTOP_SYN -> BND_EDID -> SYN_EDID001
		data &= (~0x1F1F);
		data |= (0x1F00);
		HDMI21_REG_WR(0xCA432004, data);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
		
		/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
		HDMI21_REG_RD(0xC98A2404, data);
		data &= (~0x1F1F);
		data |= (0x1F00);
		HDMI21_REG_WR(0xC98A2404, data);	

		#if 0 
		/* sXTAL enable */
		HDMI21_REG_WR(0xC98A2464, 0x108);

		/* GPIO_17_7_enable '0' -> '1' */
		HDMI21_REG_RD(0xFD510400, data);
		data &= (~0x80);
		HDMI21_REG_WR(0xFD510400, data);
		#endif
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		/* Set DDC Clock gating to avoid joints */
		HDMI21_REG_RD(0xC330004C, data);
		data &= (~0x1F1F0000);
		data |= (0x1F000000);
		HDMI21_REG_WR(0xC330004C, data);
	}

	/* Clear. Will be set When MW calls EnableHPD */
	gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = 0;

	return ret;
}


int HDMI21_Resume(void)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i;
	UINT32 data;
	UINT32 __data;
	UINT32 hpd_port[5];

	HDMI20_INFO("HDMI2.1 Kernel Driver Resume Start\n");

	if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xC61B3200/0xC8515200 */
		HDMI21_REG_RD(0xCA3A7018, data); 	// CTOP_SYN -> CRG_TOP_WOC -> NISOL_R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xCA3A7018, data);

		/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
		HDMI21_REG_RD(0xCA3A6004, data);	// CTOP_SYN -> WOC_SYN -> WOC_SYN_01
		data |= (0x1F1F);
		HDMI21_REG_WR(0xCA3A6004, data);

		#if 0 /* 2025/03/24 won.hur : This part does not exist in O26. Maybe because of ION chipset */
		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xC8863200, data); 	// CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0xF); 
		HDMI21_REG_WR(0xC8863200, data);
		#endif

		#if 0 /* 2025/03/24 won.hur : Does not exist in O26 (Probably due to ION chipset) */
		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC8863000, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863000, data);

		HDMI21_REG_RD(0xC8863004, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863004, data);

		HDMI21_REG_RD(0xC8863008, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863008, data);

		HDMI21_REG_RD(0xC886300C, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc886300C, data);
		#endif

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC870E808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC870E80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC870E810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC870E814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC870E818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC870E81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC870E820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC870E824, 0x33221100); // esm_id_duk_4
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xC61B3200/0xC8515200 */
		HDMI21_REG_RD(0xF33F4018, data); 	// CTOP_SYN -> CRG_TOP_WOC -> NISOL_R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xF33F4018, data);

		/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
		HDMI21_REG_RD(0xC8862004, data);	// CTOP_SYN -> EDID_SYN -> EDID_SYN_01
		data |= (0x1F1F);
		HDMI21_REG_WR(0xC8862004, data);

		HDMI21_REG_RD(0xF33F2004, data);	// CTOP_SYN -> WOO_SYN -> WOO_SYN_01
		data |= (0x1F1F);
		HDMI21_REG_WR(0xF33F2004, data);

		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xC8863200, data); 	// CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0xF); 
		HDMI21_REG_WR(0xC8863200, data);

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC8863000, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863000, data);

		HDMI21_REG_RD(0xC8863004, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863004, data);

		HDMI21_REG_RD(0xC8863008, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc8863008, data);

		HDMI21_REG_RD(0xC886300C, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xc886300C, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC8D0E808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC8D0E80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC8D0E810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC8D0E814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC8D0E818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC8D0E81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC8D0E820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC8D0E824, 0x33221100); // esm_id_duk_4
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xC61B3200/0xC8515200 */
		HDMI21_REG_RD(0xF3514018, data); 	// CTOP_SYN -> CRG_TOP_WOC -> NISOL_R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xF3514018, data);

		/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
		HDMI21_REG_RD(0xC61B2004, data); 	// CTOP_SYN -> EDID_SYN -> EDID_SYN_01
		data |= (0x1F1F);
		HDMI21_REG_WR(0xC61B2004, data);

		HDMI21_REG_RD(0xF3512004, data);	// CTOP_SYN -> WOO_SYN -> WOO_SYN_01
		data |= (0x1F1F);
		HDMI21_REG_WR(0xF3512004, data);


		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xC61B3200, data); 	// CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0x3); 
		HDMI21_REG_WR(0xC61B3200, data);
		
		HDMI21_REG_RD(0xC8515200, data); 	// CTOP_PAD -> PAD_WOC -> PAD_WOC128
		data &= (~0x3); 
		HDMI21_REG_WR(0xC8515200, data);

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC61B3000, data);
		data &= (~0x000f000f); 
		data |= (0x00090009); 
		HDMI21_REG_WR(0xC61B3000, data);

		HDMI21_REG_RD(0xC851501C, data);
		data &= (~0x0f000f00); 
		data |= (0x09000900); 
		HDMI21_REG_WR(0xC851501C, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC47CE808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC47CE80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC47CE810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC47CE814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC47CE818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC47CE81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC47CE820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC47CE824, 0x33221100); // esm_id_duk_4
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
		/* Temp : Micom cannot disable ISOL : Need to do this before controlling 0xCA433200 */
		HDMI21_REG_RD(0xF30D6120, data); 	// CTOP_SYN -> BND_AON -> AON POR R00
		data &= (~0x1); 
		HDMI21_REG_WR(0xF30D6120, data);
		
		/* IO PAD : HPD Output Enable. This is set to be default HPD OFF. Need to enable HPD Output for every power cycle */
		HDMI21_REG_RD(0xCA433200, data); 	// CTOP_PAD -> PAD_EDID -> PAD_EDID128
		data &= (~0xF); 
		HDMI21_REG_WR(0xCA433200, data);

		/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
		HDMI21_REG_RD(0xCA432004, data);	// CTOP_SYN -> BND_EDID -> SYN_EDID_01
		data |= (0x1F1F);
		HDMI21_REG_WR(0xCA432004, data);

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xCA433000, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA433000, data);

		HDMI21_REG_RD(0xCA433004, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA433004, data);

		HDMI21_REG_RD(0xCA433008, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA433008, data);

		HDMI21_REG_RD(0xCA43300C, data);
		data &= (~0x0000000f); 
		data |= (0x00000009); 
		HDMI21_REG_WR(0xCA43300C, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC890E808, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC890E80C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC890E810, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC890E814, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC890E818, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC890E81C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC890E820, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC890E824, 0x33221100); // esm_id_duk_4
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		HDMI21_Set_PreInit(1);
		
		/* GPIO_17_7 set */
		//HDMI21_REG_RD(0xFD510400, data); 
		//data |= 0x80; 
		//HDMI21_REG_WR(0xFD510400, data);

		//HDMI21_REG_RD(0xFD5103FC, data); 
		//data |= 0x80; 
		//HDMI21_REG_WR(0xFD5103FC, data);

		/* EDID_NISOL PAD MUX SELECT */
		//HDMI21_REG_RD(0xC93B847C, data); 
		//data &= (~0x0F000000); data |= (0x01000000);
		//HDMI21_REG_WR(0xC93B847C, data);

		/* Adapter Soft Reset Release */
		//HDMI21_REG_RD(0xC93B8494, data);
		//data &= (~0x3);
		//HDMI21_REG_WR(0xC93B8494, data);

		/* HDMI_LINK soft reset */
		HDMI21_REG_RD(0xC3320004, data); 
		data |= 0x00040200; 
		HDMI21_REG_WR(0xC3320004, data);

		/* Adapter Soft Reset */
		//HDMI21_REG_RD(0xC93B8494, data);
		//data |= 0x3;
		//HDMI21_REG_WR(0xC93B8494, data);

		/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
		HDMI21_REG_RD(0xC98A2404, data);
		data |= (0x1F1F);
		HDMI21_REG_WR(0xC98A2404, data);
		
		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC98A2430, data);
		data &= (~0x7878F138); 
		data |= (0x48489108); 
		HDMI21_REG_WR(0xC98A2430, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC3410008, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC341000C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC3410010, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC3410014, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC3410018, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC341001C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC3410020, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC3410024, 0x33221100); // esm_id_duk_4

		/* sXTAL disable */
		//HDMI21_REG_WR(0xC98A2464, 0x40);

		/* DSC Clock set to 600MHz : Not nessessary, E60 default CRG setting 0xC93B8014 [13:12] is set to 0x0 for 594MHz */
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		/* Reset Bit HIGH */
		HDMI21_Set_PreInit(1);

		if( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ){
			/* O20 B0 HPD */
			HDMI21_REG_WR(0xC3300048, 0x7C000000);
		}

		/* SET DDC GPIO mode off, Set BusGating Off for TOP/HDMI/HDCP2.2 */
		HDMI21_REG_RD(0xC330004C, data);
		data &= (~0x1F1F0000);
		data |= (0x1F1F0000);
		HDMI21_REG_WR(0xC330004C, data);

		/* HDMI DDC SDA Pad Strength : 0x3(3.9mA) => 0x9(8.5mA) (TVCSISSUE-36288)  */
		HDMI21_REG_RD(0xC3300844, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300844, data);

		HDMI21_REG_RD(0xC3300854, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300854, data);

		HDMI21_REG_RD(0xC3300864, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300864, data);

		HDMI21_REG_RD(0xC3300874, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300874, data);

		HDMI21_REG_RD(0xC3300884, data);
		data &= (~0x01111000); 
		data |= (0x01001000); 
		HDMI21_REG_WR(0xC3300884, data);

		/* ESM PK/DUK */
		HDMI21_REG_WR(0xC91E0008, 0x00112233); // esm_id_kpf_1
		HDMI21_REG_WR(0xC91E000C, 0x44556677); // esm_id_kpf_2
		HDMI21_REG_WR(0xC91E0010, 0x8899aabb); // esm_id_kpf_3
		HDMI21_REG_WR(0xC91E0014, 0xccddeeff); // esm_id_kpf_4
		HDMI21_REG_WR(0xC91E0018, 0xffeeddcc); // esm_id_duk_1
		HDMI21_REG_WR(0xC91E001C, 0xbbaa9988); // esm_id_duk_2
		HDMI21_REG_WR(0xC91E0020, 0x77665544); // esm_id_duk_3
		HDMI21_REG_WR(0xC91E0024, 0x33221100); // esm_id_duk_4
		//HDMI21_REG_WR(0xC91E0028, 0xdeadbeef); // esm_id_devnum

		/* ESM Mem Blocking OFF */
		HDMI21_REG_WR(0xC9306930, 0x00000011); // CTOP SYN HDMI

		/* Set Current Driver to MAX */
		HDMI21_REG_WR(0xC330080C, 0x07110711);

		/* DSC */
		HDMI21_REG_WR(HDMI21_CHIP_O20_CRG_SETTING_REG, 0x00000800);
		HDMI21_REG_RD(0xC903500C,data);
		data |= 0x00000007;
		HDMI21_REG_WR(0xC903500C, data);
	
		/* Reset Bit Low */
		HDMI21_Set_PreInit(0);
	}

	/* Clear Dev Handler */
	__HDMI21_HAL_Rx_Set_InitDevHandler(1);

	/* check warm boot condition */
	if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
		gHdmi21WarmMode = 0;
		for(i = 0; i<g_hdmi20_number_of_ports; i++)
		{
			hpd_port[i] = gHDMI21RxHandler[i].top_read(HDMI21_TOP_REG_AD_MAIN_HPD_DDC_SET);
			HDMI20_PRINT("%s:%d warm mode check : HPD_Port[%d] = [0x%x]\n",__func__,__LINE__, i, hpd_port[i]);
			if( (hpd_port[i] & 0x11) == 0x11) {
				HDMI20_PRINT("HPD_Port[%d] = [0x%x] : Maybe warm stanby mode !!!\n", i, hpd_port[i]);
				gHdmi21WarmMode = 1;
				break;
			}
		}
	}

	for(i=0;i<g_hdmi20_number_of_ports;i++){
		/* 2021/05/07 : O22 Pslv Error Off */
		if(lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
			gHDMI21RxHandler[i].top_write(HDMI21_TOP_REG_AD_REG_MON_SEL, HDMI21_TOP_FIELD_REG_PSLVERR_OFF_O24);
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			gHDMI21RxHandler[i].top_write(HDMI21_TOP_REG_AD_REG_MON_SEL, HDMI21_TOP_FIELD_REG_PSLVERR_OFF_O24);
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			gHDMI21RxHandler[i].top_write(HDMI21_TOP_REG_AD_REG_MON_SEL, HDMI21_TOP_FIELD_REG_PSLVERR_OFF);
		}

		/* ALED HPD MUX */
		data = gHDMI21RxHandler[i].aled_read(HDMI21_ALED_RC_REG_AD_HPD);
		data |= (HDMI21_ALED_RC_FIELD_O_REG_HPD);
		gHDMI21RxHandler[i].aled_write(HDMI21_ALED_RC_REG_AD_HPD, data);

		/* Set HDCP video path to non-ESM(2.2) */
		gHDMI21RxHandler[i].top_write(0xFB0, 0x1);
	}

	/* I2C Clock Delay */
	/* ALED TOP : Set I2C driver clock sel : LG Tapbook DVI Issue at End of 2016 */
	if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(gHDMI21RxHandler[i].disableAledEdid > 0) {
				__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xFF0006);
				HDMI21_REG_RD(0xCA36000C, __data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn)
			}
		}

		/* Set value */
		//__data = 0x00FF0006; 	/* LG TapBook Issue */
		if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
		else __data &= (~0x4);
		
		if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
		else __data &= (~0x10);

		if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x40;
		else __data &= (~0x40);

		if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x100;
		else __data &= (~0x100);

		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(gHDMI21RxHandler[i].disableAledEdid > 0) {
				HDMI21_REG_WR(0xCA36000C, __data);	
			}
		}
		
		
	}else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(gHDMI21RxHandler[i].disableAledEdid > 0) {
				__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xFF0006);
				HDMI21_REG_RD(0xC883000C, __data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn)
			}
		}

		/* Set value */
		//__data = 0x00FF0006; 	/* LG TapBook Issue */
		if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
		else __data &= (~0x4);
		
		if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
		else __data &= (~0x10);

		if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x40;
		else __data &= (~0x40);

		if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x100;
		else __data &= (~0x100);

		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(gHDMI21RxHandler[i].disableAledEdid > 0) {
				HDMI21_REG_WR(0xC883000C, __data);	
			}
		}
		
		
	}else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(gHDMI21RxHandler[i].disableAledEdid > 0) {
				__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xF0006);
				__HDMI21_HAL_Rx_ALED_TOP_Write_P23(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xF0006);
			}
		}
		HDMI21_REG_RD(0xC619000C, __data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn)
		if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
		else __data &= (~0x4);
		
		if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
		else __data &= (~0x10);
		HDMI21_REG_WR(0xC619000C, __data);
		
		HDMI21_REG_RD(0xF311000C, __data);
		if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x4;
		else __data &= (~0x4);

		if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x10;
		else __data &= (~0x10);

		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(gHDMI21RxHandler[i].disableAledEdid > 0) {
				HDMI21_REG_WR(0xF311000C, __data);
			}
		}
	}

	/* SET DDC GPIO mode off */
	if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		/* Set BusGating Off for HDCP2.2 engine */
	}
	
	/* Reset HDCP22 initiated info */
	for(i = 0; i<g_hdmi20_number_of_ports; i++)
	{
		_p = &gHDMI21RxHandler[i];

		/* Set VFreq counter ref clock */
		_p->top_write(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK, 0x1E0);

		/* Clear Device Driver Handler HDMI Data */
		__HDMI21_HAL_Rx_Set_ResetHandlerData(_p, 1);

		/* Reset Link Engine */
		__HDMI21_HAL_Rx_Set_ResetLink(_p, 1);

		/* Initiate ESM Flags & PK/DUK */
		HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(_p, 0);

		/* Enable 5V IRQ */
		_p->control_top_irq(1);

		if(lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
			/* Initiate Low Power Module */
			HDMI21_HAL_Rx_Set_LowPowerMode(i, 0, 1, 0);
		}
	}

	/* 2019/08/26 : Set Default FRL 10G EDID for port 4 */
	HDMI21_HAL_Rx_Set_EDID(4, (UINT8 *)&gHdmi21TestEDID_FRL10G_Jang, sizeof(gHdmi21TestEDID_FRL10G_Jang), 1);

	/* Restore HDMI Thread */
	if(gHDMI21Thread.isAlive <= 0){
		gHDMI21Thread.isAlive = 1;
		gHDMI21Thread.pThread= kthread_create( (void *)__HDMI21_HAL_Rx_MainThread, 0, "hdmi21_rx_engine");
		if(gHDMI21Thread.pThread){
			HDMI20_INFO("Initialing HDMI2.1 Engine thread\n");
			wake_up_process(gHDMI21Thread.pThread);
		}else HDMI20_ERROR("Cannot create HDMI2.1 Engine  thread\n");
	}
	else{
		HDMI20_INFO("Warning! : Will not create HDMI2.1 Engine thread due to it is already ALIVE!\n");
	}

	HDMI21_Tx_eARC_Resume();

	/* Accumulate HDMI count of resume */
	gHDMI21RxDevVideoControler[HDMI21__COUNT_OF_RESUME].value++;

	/*Audio CSD change interrupt Enable*/
	HDMI21_Rx_Audio_Path_Irq_Enable();

	HDMI20_INFO("HDMI2.1 Kernel Driver Resume End. Accumulated Resume cnt[%d]\n", gHDMI21RxDevVideoControler[HDMI21__COUNT_OF_RESUME].value);
	
	return RET_OK;
}

int HDMI21_Process_Cmd(LX_HDMI20_CMD_T* cmd)
{
	int ret = RET_OK;
	UINT32 data;
	int cmd_result = HDMI20_CMD_STATUS_CMD_ERROR;

	#ifdef HDMI21_PORT5_USE_HW_OPTION 
	/* HW Option */
	LX_OVI_HW_DISPLAY_INFO_T hwOpt;
	#endif

	do{
		/* Step 1. pharse cmd */
		switch(cmd->command)
		{
			case HDMI20_CMD_RX_INITIALIZE:
				{
					cmd_result = HDMI21_HAL_Rx_Set_Initialize((LX_HDMI20_INIT_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_UNINITIALIZE	:
				{
					cmd_result = __HDMI21_HAL_Rx_Set_UnInitialize();
				}
				break;

			case HDMI20_CMD_RX_GET_TIMINGINFO:
				{
					cmd_result = HDMI21_HAL_Rx_Get_StableTimingInfo((UINT8)cmd->attributes, (LX_HDMI_TIMING_INFO_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_AVIINFO:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_AVIInfo((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_SPDINFO:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_SPDInfo((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_VSIINFO:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_VSIInfo((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size, 0, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_COLORINFO:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_COLORInfo((UINT8)cmd->attributes, (LX_HDMI_COLOR_DOMAIN_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_PHYSTATUS:
				{
					cmd_result = HDMI21_PHY_Rx_Get_PhyStatus((LX_HDMI_PHY_INFORM_T *)cmd->handle, (int)cmd->size, (int)cmd->attributes, 0);
				}
				break;

			case HDMI20_CMD_RX_SET_EDID	:
				{
					cmd_result = HDMI21_HAL_Rx_Set_EDID((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_EDID	:
				{
					cmd_result = HDMI21_HAL_Rx_Get_EDID((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_SET_HDCP14:
				{
					cmd_result = HDMI21_HAL_Rx_Set_HDCP14((UINT8)cmd->attributes, (UINT32 *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_HDCP14:
				{
					cmd_result = __HDMI21_HAL_Rx_Get_HDCP14((UINT8)cmd->attributes, (UINT32 *)cmd->handle, (int)cmd->size);
				}
				break;

			case HDMI20_CMD_RX_SET_ENABLEHPD:
				{
					cmd_result = __HDMI21_HAL_Rx_Set_HPD((UINT8)cmd->attributes, (UINT8)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_SET_ENABLEEDID:
				{
					cmd_result = __HDMI21_HAL_Rx_Set_EnableEDID((UINT8)cmd->attributes,(UINT8)cmd->attributes);
				}
				break;

			case HDMI20_CMD_RX_DBG_TOOL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_Tool((int)cmd->compat_handle, (UINT8)cmd->attributes, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_GET_AUDIOINFO:
				{
					cmd_result = HDMI21_HAL_Rx_GetAudioInfo((UINT8)cmd->attributes, (LX_HDMI_AUDIO_INFO_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_GET_AUDIOCOPYINFO:
				{
					cmd_result = HDMI21_HAL_Rx_GetAudioCopyInfo((UINT8)cmd->attributes, (LX_HDMI_AUDIO_COPY_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_SET_HDMIARC:
				{
					if(cmd->handle == NULL) data = 0;
					else data = 1;

					//cmd_result = HDMI21_HAL_Rx_Set_HDMIARC((UINT8)cmd->attributes, (BOOLEAN)data);
				}
				break;
			case  HDMI20_CMD_RX_SET_MUTE:
				{
					cmd_result = HDMI21_HAL_Rx_Set_AudioMute((UINT8)cmd->attributes, (LX_HDMI_MUTE_CTRL_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_GET_AUDIODBGINFO:
				{
					cmd_result = HDMI21_HAL_Rx_Get_DebugAudioInfo((UINT8)cmd->attributes, (LX_HDMI_DEBUG_AUDIO_INFO_T *)cmd->handle, (int)cmd->size);
				}
				break;

			case HDMI20_CMD_RX_GET_ASPECTRATIO:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_AspectRatio((UINT8)cmd->attributes, (LX_HDMI_ASPECTRATIO_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_GET_HDMISTATE:
				{
					cmd_result = __HDMI21_HAL_Rx_Get_HDMIState((UINT8)cmd->attributes, (LX_HDMI_STATUS_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_HDCP22INFO:
				{
					cmd_result = HDMI21_HAL_Rx_Set_HDCP22Info((UINT8)cmd->attributes, 1);
				}
				break;
			case HDMI20_CMD_RX_SET_PHY_ACCESS:
				{
					cmd_result = HDMI21_PHY_Rx_Set_AccessPhy((UINT8)cmd->attributes, (LX_HDMI20_PHY_ACCESS_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_OPEN:
				{
					cmd_result = HDMI21_Open();
				}
				break;
			case HDMI20_CMD_RX_SET_ENABLE_OPERATION:
				{
					/* 2023/06/27 won.hur : For DOSA, implementing SET_DISABLE_OPERATION */
					HDMI20_PRINT("SET_ENABLE_OPERATION:HPD\n");
					if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
						gHDMI21RxDevVideoControler[HDMI21__FORCE_5V_DOWN].value = 0;
						gHdmi21WarmMode = 2;	// ecscape from warm mode
					}
					
					if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
						gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);
					}
					else {
						#ifdef HDMI21_PORT5_USE_HW_OPTION 
						/* HW Option */
						OVI_HAL_GetHWDisplayOption(&hwOpt);
						if(hwOpt.frcChipType > LX_OVI_FRC_CHIP_INTERNAL) {
							gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);
						}
						else
						{	
							gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports - 1);	
						}
						#else
						gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);
						#endif
					}
					cmd_result = RET_OK;
				}
				break;
			case HDMI20_CMD_RX_SET_DISABLE_OPERATION:
				{
					/* 2023/06/27 won.hur : For DOSA, implementing SET_DISABLE_OPERATION */
					HDMI20_PRINT("SET_DISABLE_OPERATION:HPD\n");
					if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
						gHDMI21RxDevVideoControler[HDMI21__FORCE_5V_DOWN].value = 0x1F;
						gHdmi21WarmMode = 2;	// ecscape from warm mode
					}
					
					cmd_result = RET_OK;
				}
				break;	
			case HDMI20_CMD_RX_ACCESS_DEV_CTRL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_AccessDevVideoController((HDMI21_DEV_VIDEO_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_CTRL:
				{
					cmd_result = __HDMI21_HAL_Rx_DBG_PrintDevVideoController((HDMI21_DEV_VIDEO_CONTROL_LIST_T)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_ACCESS_DEV_AUD_CTRL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_AccessDevAudioController((HDMI21_DEV_AUDIO_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_AUD_CTRL:
				{
					cmd_result = __HDMI21_HAL_Rx_DBG_PrintDevAudioController((HDMI21_DEV_AUDIO_CONTROL_LIST_T)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_SET_REVERSE_HPD:
				{
					if(cmd->handle != NULL) data = 1;
					else data = 0;

					cmd_result =  __HDMI21_HAL_Rx_Set_InverseHPDControl((UINT8)cmd->attributes ,data);
				}
				break;
			case HDMI20_CMD_RX_SET_PIONEER_PLAT:
				{
					cmd_result = __HDMI21_HAL_Rx_Set_PioneerMode();
				}
				break;
			case HDMI20_CMD_RX_GET_DRMINFO:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_DRMInfo((UINT8)cmd->attributes, (LX_HDMI20_RX_DRM_PACKET_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_SET_RESTARTHPD:
				{
					cmd_result = HDMI21_HAL_Rx_Set_RestartHPD((UINT8)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_SET_POWEROFF:
				{
					HDMI20_INFO("Notice : HDMI2.1 Power Down Called! Suspend Driver\n");
					cmd_result = HDMI21_Suspend();

				}
				break;
			case HDMI20_CMD_RX_SET_DISABLE_HDMI:
				{
					if(cmd->handle != NULL) data = 1;
					else data = 0;

					cmd_result = __HDMI21_HAL_Rx_Set_DisableHDMI((UINT8)cmd->attributes, data);
				}
				break;
			case HDMI20_CMD_RX_GET_DEV_CTRL_CNT :
				{
					cmd_result = HDMI21_HAL_Rx_DBG_GetDevControllerCnt((HDMI20_DEV_CONTROL_TYPE_T)cmd->attributes, (int *)cmd->handle, 0);

				}
				break;
			case HDMI20_CMD_RX_GET_DEV_CTRL :
				{
					cmd_result = HDMI21_HAL_Rx_DBG_GetDevController((HDMI20_DEV_CONTROL_TYPE_T)cmd->attributes, (HDMI20_DEV_CONTROL_T *)cmd->handle, (int)cmd->size, 0);

				}
				break;
			case HDMI20_CMD_RX_GET_HDMI_MISC:
				{
					cmd_result = __HDMI21_HAL_Rx_DBG_GetHDMIMiscInfo((UINT8)cmd->attributes, (LX_HDMI20_RX_HDMI_MISC_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_HDCP14KSVLIST:
				{
					cmd_result = __HDMI21_HAL_Rx_Set_HDCP14_KSVList((UINT8)cmd->attributes, (LX_HDMI20_HDCP14_RP_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_HDMIFACTOR:
				{
					cmd_result = HDMI21_HAL_Rx_Set_HDMIFactor((LX_HDMI20_SETTING_FACTOR_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_SET_ERROR_THRES:
				{
					cmd_result = __HDMI21_HAL_Rx_Set_HDMIHostErrorThres((LX_HDMI20_ERROR_SETTING_T *)cmd->handle, (int)cmd->size);

				}
				break;
			case HDMI20_CMD_RX_GET_ERROR:
				{
					cmd_result = __HDMI21_HAL_Rx_Get_HDMIHostError((UINT8)cmd->attributes, (UINT32 *)cmd->handle, (int)cmd->size); 
				}
				break;
			case HDMI20_CMD_RX_GET_MULTIPLE_VSI:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_MultipleVSIPacket((UINT8)cmd->attributes, (LX_HDMI20_MULTIPLE_VSI_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_GET_CURRENT_VRR_FREQ:
				{
					cmd_result = HDMI21_HAL_Rx_Get_VrrCurrentVfreq((UINT8)cmd->attributes, (UINT16 *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_GET_EMPACKET:
				{
					cmd_result = HDMI21_DISLAND_Rx_Get_EMPInfo((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (LX_HDMI20_EMP_TYPE_T)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_ACCESS_DEV_LINK_CTRL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_AccessDevLinkController((HDMI21_DEV_LINK_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_LINK_CTRL:
				{
					cmd_result = __HDMI21_HAL_Rx_DBG_PrintDevLinkController((HDMI21_DEV_LINK_CONTROL_LIST_T)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_ACCESS_DEV_PHY_CTRL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_AccessDevPhyController((HDMI21_DEV_PHY_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_PHY_CTRL:
				{
					cmd_result = __HDMI21_HAL_Rx_DBG_PrintDevPhyController((HDMI21_DEV_PHY_CONTROL_LIST_T)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_ACCESS_DEV_EARC_CTRL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_AccessDevEARCController((HDMI21_DEV_EARC_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_EARC_CTRL:
				{
					cmd_result = HDMI21_HAL_Rx_DBG_PrintDevEARCController((HDMI21_DEV_EARC_CONTROL_LIST_T)cmd->attributes);
				}
				break;	

			default :
				{
					HDMI20_ERROR("Unknown IOCTL or Not supported CMD[%d]\n", cmd->command);
					cmd_result = HDMI20_CMD_STATUS_IOCTL_ERROR;
					break;
				}
		}

		/* Last Step : Update CMD status*/
		cmd->status = cmd_result;

	} while(0);

	return ret;
}


/* IOCTL / V4L2 */
int HDMI21_HAL_Rx_Get_StableTimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int size, int isInternalCall)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	LX_HDMI_TIMING_INFO_T userdata;
	LX_HDMI_VSI_3D_STRUCTURE_T	vsi3DData = LX_HDMI_VSI_3D_STRUCTURE_MAX;
	int vfreq,hfreq;
	UINT8	__vsifHead[3];


	do{
		/* Step 1. Defence : Null Pointer Check */
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			return RET_ERROR;
		}

		/* Step 2. Defence : Pointer Size Check */
		if(size != sizeof(LX_HDMI_TIMING_INFO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_TIMING_INFO_T), size);
			return RET_ERROR;
		}

		/* Step 3. Memset */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_TIMING_INFO_T));

		/* Step 4. Check port validity */
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Step 5. Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Step 5-1. 2020/03/26 : DSC Info must be delievered regardless of stable timing */
		userdata.isDSC = _p->isDSC;

		/* Step 6. Do not provide information on unstable conditions */
		if(	__HDMI21_HAL_Rx_Get_IsVideoStable(_p) <= 0) {
			if( lx_board_opt() & LX_BOARD_OPT_SLT) {
				HDMI20_INFO("DBG[%d] No Stable[%d] to provide StableVideo information\n", _p->port, __HDMI21_HAL_Rx_Get_IsVideoStable(_p));
			}
			else {
				HDMI21_LINE_DBG(1068, "DBG[%d] No Stable to provide StableVideo information\n", _p->port);
			}
			break;
		}

		/* Step 7. Block Not-supported videos */
		if( __HDMI21_HAL_Rx_Get_ListOfNotSupportingVideo(_p) < 0){
			if( lx_board_opt() & LX_BOARD_OPT_SLT) {
				HDMI20_INFO("DBG[%d] : Timing info to Zero due to Not supporting Timing spec\n", _p->port);
			}
			else{ 
				HDMI21_LINE_DBG(1074, "DBG[%d] : Timing info to Zero due to Not supporting Timing spec\n", _p->port);
			}
			break;
		}

		/* Step 8. Calculate Frequency to fit LGE MW */
		if((_p->real_pixel_clk == 0)||(_p->video.htotal == 0)){
			hfreq = 0;	/* Defence Code. This is actually a logical dead code */
		}
		else{
			hfreq = ((_p->real_pixel_clk * 1000) / _p->video.htotal); ///< Horizontal frequency(100 Hz unit)
		}

		/* Step 9. Update Phy Mode */
		userdata.phyMode = _p->phyInitiatedMode;

		/* Step 10. Compensate Vfreq, and set to MW wanted format */
		vfreq = (UINT16)_p->video.vfreq;

		/* SW WA. 28 is 30Hz, 14Hz is 15Hz */
		if(vfreq == 28) vfreq = 30;
		else if(vfreq == 14) vfreq = 15;

		if(vfreq%2){
			/* Always give oppertunity for originally odd vfreqs.. 23.97, 25, 59,97 */
			if(vfreq == 23) vfreq = 24;
			else if(vfreq == 25) vfreq = 25;
			else if(vfreq == 59) vfreq = 60;
			else if(u32CHK_RANGE(vfreq, 60, 2)) vfreq = 60;
			else if(u32CHK_RANGE(vfreq, 50, 2)) vfreq = 50;
			else if(u32CHK_RANGE(vfreq, 30, 2)) vfreq = 30;
			//else if(u32CHK_RANGE(vfreq, 25, 1)) vfreq = 25;
			else if(u32CHK_RANGE(vfreq, 24, 1)) vfreq = 24;
		}

		HDMI21_LINE_DBG(1144, "DBG[%d] : [%s] Vfreq[%d]->PostVfreq[%d]\n", _p->port, __FUNCTION__ ,_p->video.vfreq, vfreq);

		/* Step 11. Copy Timing to User data structure */
		/* Convert Vfreq to a scale that the MW & DE FW wants(Multiply by 10) */
		vfreq = vfreq * 10;
		//userdata.hFreq = (UINT16)hfreq;
		userdata.hFreq = 0;
		userdata.vFreq = (UINT16)vfreq; 					///< Veritical frequency(1/10 Hz unit)
		userdata.hTotal = (UINT16)_p->video.htotal; 		///< Horizontal total pixels
		userdata.vTotal = (UINT16)_p->video.vtotal; 		///< Vertical total lines
		userdata.hStart = (UINT16)_p->video.hoffset; 		///< Horizontal start pixel
		userdata.vStart = (UINT16)_p->video.voffset;		///< Vertical start lines
		if(_p->isDSC > 0) {
			userdata.hActive = (UINT16)_p->pps.pic_width;	
			userdata.vActive = (UINT16)_p->pps.pic_height;
		}
		else {
			userdata.hActive = (UINT16)_p->video.hactive;		///< Horizontal active pixel
			userdata.vActive = (UINT16)_p->video.vactive; 		///< Vertical active lines
		}
		userdata.state = 0; /* Do not know what "STATE" does... */
		userdata.pixelClock = _p->real_pixel_clk;
		if((UINT16)_p->video.interlaced) { userdata.scanType = 0; }
		else { userdata.scanType = 1; }

		/* SW WA for F20 */
		if(userdata.scanType == 0) {
			/* Always Progressive for video having larger size than 1300?? */
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_PROGRES_HIGH_V].value > 0) {
				if(userdata.vActive >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_PROGRES_HIGH_V].value) {
					HDMI21_LINE_DBG(1707, "DBG[%d] : force progressive for video[%d] Vactive over [%d]\n",\
							port, userdata.vActive, gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_PROGRES_HIGH_V].value);
					userdata.scanType = 1;
				}
			}
		}

		/* Step Post 11. Check Range : pixel Clk, video sync data from HW is not accurate.. 
		 * So i need to calucate the approperiate value for MW */
		__HDMI21_HAL_Rx_Set_CompensateStableHVactiveTotal(&userdata);


		/* Step 12. Update VRR releated Detection */
		if(gHDMI21RxDevVideoControler[HDMI21__LINK_AMD_FREESYNC_MODE].value == 0) {
			userdata.isFreeSyncMode = 0;
			userdata.vFreqMin = userdata.vFreq;
			userdata.vFreqMax = userdata.vFreq;
		}
		else if(gHDMI21RxDevVideoControler[HDMI21__LINK_AMD_FREESYNC_MODE].value == 2){
			userdata.isFreeSyncMode = 1;
			userdata.vFreqMin = userdata.vFreq;
			userdata.vFreqMax = userdata.vFreq;
		}
		else{
			if(_p->isFreeSyncMode > 0)	userdata.isFreeSyncMode = 1;
			else userdata.isFreeSyncMode = 0;
			userdata.vFreqMin = _p->vfreq_min;
			userdata.vFreqMax = _p->vfreq_max;
		}

		/* Step 12-2. Update FVA/MConst/QMSMode */
		userdata.isFvaMode	= _p->isFvaMode;
		userdata.isMConst	= _p->isMConst;

		if(gHDMI21RxDevVideoControler[HDMI21__LINK_FORCE_QMS_MODE].value == 0) {
			userdata.isQmsMode	= 0;
		}
		else if(gHDMI21RxDevVideoControler[HDMI21__LINK_FORCE_QMS_MODE].value == 2) {
			userdata.isQmsMode	= 1;
		}
		else {
			userdata.isQmsMode	= _p->isQmsMode;
		}

		if(userdata.isQmsMode > 0) {
			userdata.qmsTFR = _p->em_qms_tfr;
			userdata.qmsBaseRate = _p->em_qms_baseRate;
		}
		
		/* Step 13. Update ALLM Mode */
		userdata.isAllmMode = _p->isAllmMode;

		/* Step 14. Update Dolby HDR Flag */
		userdata.isDolbyHDR = HDMI21_HAL_Rx_Get_IsDolbyHDR(_p->port);

		/* Keep History of Dolby HDR : This needs to be cleared when timing info is not stable.. only for the ones that is being saved from this function routine!!! */
		_p->isDolbyHDR = userdata.isDolbyHDR;


		/* Step 15. Proceed 3D Sigs. Decide lge3DData with vsi3DData */
		/* Get Header */
		__vsifHead[0] = _p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][4];
		__vsifHead[1] = _p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][5];
		__vsifHead[2] = _p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][6];
		
		if((_p->isDolbyHDR <= HDMI_DOLBY_STD_OLDVSI) &&(__vsifHead[0] == 0x03) && (__vsifHead[1] == 0x0C) && (__vsifHead[2] == 0x00)){
			/* Update VSI based on Field 8 */
			if((_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][7] & 0xE0) == 0x40){
				vsi3DData = (0x0F & ((_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][8] & 0xF0) >> 4));
			}
		}

		/* Update overall-3D format to user data sturcture */
		userdata.extInfo = __HDMI21_HAL_Rx_Get_Convert3DtoLG3DFormat(_p, vsi3DData);

		/* Step 16. Check 3D video without VSI information  & Compensate Sync value*/
		__HDMI21_HAL_Rx_Set_Compensate3DTimingInfo(_p, &userdata, userdata.extInfo);

		/* Step 17. Double Vfreq for Interlaced signals.*/ 
		/* 2019/05/13 : Deleted for O20. This is done on UpdateClockVfreq function */

		/* Step 18. Compensate for Pixel Repetition signals */
		if(_p->video.pixel_repetition > 0)
		{
			HDMI21_LINE_DBG(129, "DBG[%d] : Pixel Repitition mode[%d] Htotal[%d] HActive[%d] HStart[%d]\n", _p->port, _p->video.pixel_repetition,userdata.hTotal, userdata.hActive, userdata.hStart);

			userdata.PixelRepeat = _p->video.pixel_repetition;
			
			userdata.hTotal = userdata.hTotal >> 1;
			userdata.hActive = userdata.hActive >> 1;
			userdata.hStart = userdata.hStart >> 1;
		}

		/* Step 19. Compensate if VIC Code exists in non-DVI mode */
		if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(_p) == 0){
			if(gHDMI21RxDevVideoControler[HDMI21__LINK_ENABLE_VIC_CORRECTION].value > 0){
				__HDMI21_HAL_Rx_Set_CompensateWithVicCode(&userdata, _p->video.vicCode, _p->phyInitiatedMode, _p->isFreeSyncMode);
			}
		}

		if (_p->audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value) {
			_p->audioStandByCnt++;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_AUDIO("Audio stand by cnt : %d",_p->audioStandByCnt);
		}

		/* Step 20. Add HDCP version Info */
		userdata.hdcpVer = HDMI21_HAL_Rx_Get_HDCPStatus(_p->port);

		/* Step 21. Add DVI Info */
		userdata.isDVI = _p->video.dvi; 

		/* Step 22. Add Deep Color Info */
		userdata.deepColorMode = _p->video.deep_color_mode;
	
		/* Step 23. CSC INfo */
		userdata.csc = _p->video.video_format;
	} while(0);

	/* Step 21. Notify PQE FW that this is PVO. Legacy code from SNPS HDMI2.0/PQE MCU */
	userdata.isPVOMode = 1;	/* HDMI2.1 HW has only PVO output. CEA does not exist */

	/* Step 22. Copy Data To User */
	if(isInternalCall > 0){
		memcpy((LX_HDMI_TIMING_INFO_T *)pData, &userdata, sizeof(LX_HDMI_TIMING_INFO_T));
		ret = RET_OK;
	}
	else{
		ret = copy_to_user((LX_HDMI_TIMING_INFO_T *)pData, &userdata, sizeof(LX_HDMI_TIMING_INFO_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "TIMING" ,port);
		}
	}

	return ret;
}

int HDMI21_HAL_Rx_Get_HDCPStatus(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	/*  Check port validity */
	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return -1;
	}

	_p = &gHDMI21RxHandler[port];

	if(HDMI21_HDCP_Rx_Get_IsCurrentHDCP23(_p) > 0) 		return 23;
	else if(HDMI21_HDCP_Rx_Get_IsCurrentHDCP14(_p) > 0)	return 14;
	else return 0;
}


int HDMI21_HAL_Rx_Get_IsHpdUp(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 hpd;

	/*  Check port validity */
	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return 0;
	}

	_p = &gHDMI21RxHandler[port];
		
	hpd  = gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_HPD_DDC_SET);
	hpd &= (HDMI21_TOP_FIELD_O_REG_HPD);
	
	if(hpd != 0) hpd = 1;

	if(_p->isHPDInverseMode){
		if(hpd) hpd = 0;
		else hpd = 1;
	}
	else{
		if(hpd) hpd = 1;
		else hpd = 0;
	}

	HDMI21_LINE_DBG(1717,"DBG [%d] : hpd[%d], HW Reg=>[0x%08x]\n", _p->port, hpd, 0x0);

	return hpd;
}


int HDMI21_HAL_Rx_Set_LocalVideoMute(UINT8 port, int onOff, int useTimer)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	UINT32 __cJiffiesMsec = 0;


	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* DBG : Disable Mute Control on specific debug status */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1352){
			ret = RET_OK;
			break;
		}

		/* Timer to disable infinite Mute */
		if(useTimer) __cJiffiesMsec = jiffies_to_msecs(jiffies);

		if(onOff){

			if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
				HDMI20_VIDEO("Notice [%d] : Set Local Video Mute[%s]/Mode[%s]/Caller[%pS]\n", _p->port, onOff?"On":"Off", useTimer?"Timer":"Force", __builtin_return_address(0));

				if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_VPGEN_TOGGLE].value > 0) {
					if(_p->lowPowerMode != HDMI21_HAL_POWER_LOWPOWER) {
						HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_VPROC);
					}
				}
			
			}
			else{
				HDMI21_LINE_DBG(1300, "DBG[%d] : Local Mute Timer Update. Caller[%pS]\n", _p->port, __builtin_return_address(0));
			}

			if(useTimer) { 
				_p->localmutetimer = __cJiffiesMsec;
			}

			/* Set Mute */
			HDMI21_VPROC_Rx_Set_Mute(_p, 1);
		}
		else{
			if(useTimer){
				if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 1350){
					if(__cJiffiesMsec - _p->localmutetimer >= gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_TIME].value){
						HDMI20_VIDEO("Notice [%d] : LocalMute release by hold time pass. Caller[%pS]\n", _p->port, __builtin_return_address(0));
						if(gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_TIME].value == gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_INIT_TIME].value){
							gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_TIME].value = gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_ORIGIN_TIME].value;
							HDMI20_VIDEO("Notice [%d] :  First LocalMute release. Decrease Local Mute hold Thres\n", _p->port);
							_p->localmutetimer  = 0;
						}

						/* Clear Mute */
						HDMI21_VPROC_Rx_Set_Mute(_p, 0);
					}
					else{
						if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 208) {
							HDMI20_DBG("NOTICE [%d] : LocalMute Hold [0x%x]-[0x%x] < [0x%x]. Caller[%pS]\n",_p->port,__cJiffiesMsec, _p->localmutetimer, gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_TIME].value, __builtin_return_address(0));
						}
					}
				}
			}
			else{
				HDMI20_VIDEO("Notice [%d] : LocalMute release by force. Caller[%pS]\n", _p->port, __builtin_return_address(0));
				/* Clear Mute */
				HDMI21_VPROC_Rx_Set_Mute(_p, 0);
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


/* Returns -1:Error / 1:Local Mute ON / 0:Local Mute Off */
int HDMI21_HAL_Rx_Get_IsLocalMuteOn(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = 0;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return -1;
	}

	/* Get Handler */
	_p = &gHDMI21RxHandler[port];

	/* Get Value */
	ret = HDMI21_VPROC_Rx_Get_IsMute(_p);

	return ret;
}


LX_HDMI_DOLBY_STATE_T HDMI21_HAL_Rx_Get_IsDolbyHDR(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	LX_HDMI_DOLBY_STATE_T ret = HDMI_DOLBY_STATE_OFF;
	LX_HDMI_VSI_3D_STRUCTURE_T	vsi3DData = LX_HDMI_VSI_3D_STRUCTURE_MAX;
	UINT32	__vsifLen = 0;
	UINT8	__vsifHead[3];
	int __dolbyOnIndication = 0;
	UINT8 __doviVsiPb5 = 0;
	int __isUniqueDolbyDRM = 0;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return -1;
	}

	/* Get Handler */
	_p = &gHDMI21RxHandler[port];

	#if 0
	/* Step 0. Dolby OFF when video is not stable */
	if(	__HDMI21_HAL_Rx_Get_IsVideoStable(_p) == 0) {
		return ret;
	}
	#endif

	/* Step 1. Check VSI info frame version */
	/* Step 1-1 : Check Dolby VSIF first... */
	__vsifHead[0] = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][4];
	__vsifHead[1] = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][5];
	__vsifHead[2] = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][6];

	HDMI21_LINE_DBG(191, "DBG[%d] : Header[0x%x][0x%x][0x%x]\n", _p->port, __vsifHead[0], __vsifHead[1], __vsifHead[2]);

	/* 2023/08/18 : Check Dolby Unique DRM */
	__isUniqueDolbyDRM = __HDMI21_HAL_Rx_Get_CheckDolbyUniqueDRM(_p, gHDMI21RxDevVideoControler[HDMI21__VIDEO_VERBOSE_DOLBY_UNIQUE_DRM].value);


	if((__vsifHead[0] == 0x46) && (__vsifHead[1] == 0xD0) && (__vsifHead[2] == 0x00))
	{
		/* Dolby Ver 2 Detection */
		__vsifLen  = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][2];
		__dolbyOnIndication = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][7];

		HDMI21_LINE_DBG(191, "DBG[%d] : Legnth[%d]\n", _p->port, __vsifLen);

		if(__dolbyOnIndication & 0x2) {
			/* Get PB5 */
			__doviVsiPb5 = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][8];
			__doviVsiPb5 = __doviVsiPb5 & 0x90;
			
			/*check if LL mode or not. if PB4 lsb is 1 it is LL mode VSIF*/
			if(__dolbyOnIndication & 0x1) {
				if(__doviVsiPb5 == 0x10) {
					HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby PC Mode !!\n", _p->port);
					ret = (UINT8)HDMI_DOLBY_LL_PC;
				}
				else {
					HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby LL New VSI\n", _p->port);
					ret = (UINT8)HDMI_DOLBY_LL_422_12B;
				}
			}
			else{
				/*Standard Dolby with New VSI*/
				HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby Standard New VSI\n", _p->port);
				ret = (UINT8)HDMI_DOLBY_STD_NEWVSI;
			}
		}
		else{
			/* This is Not Dolby */
			HDMI21_LINE_DBG(1207,"DBG[%d] : Dolby VSI verification. Dolby OFF indicated.\n", _p->port);
		}
	}
	else if( __isUniqueDolbyDRM > 0){
		HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby PC Mode !!\n", _p->port);
		ret = (UINT8)HDMI_DOLBY_LL_PC;

		if((_p->isDolbyHDR == (int)HDMI_DOLBY_STATE_OFF)\
				&&(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value != 0)\
				&&(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value != 2))
		{
			HDMI20_PRINT("Notice %d : Detected Dolby PC Mode ^^!\n", _p->port);
		}
	}
	else {
		if((__vsifHead[0] == 0x03) && (__vsifHead[1] == 0x0C) && (__vsifHead[2] == 0x00)) 	/* Dolby HDR ver 1 detection */
		{
			/* Update VSI based on Field 8 */
			if((_p->dataPacket[HDMI21_DISLAND_DATA__DOVI][7] & 0xE0) == 0x40){
				vsi3DData = (0x0F & ((_p->dataPacket[HDMI21_DISLAND_DATA__DOVI][8] & 0xF0) >> 4));
			}
			/* Is Dolby HDR ? */
			/* PB4[7:5] == 0x0 or 0x1?? */
			else if(((_p->dataPacket[HDMI21_DISLAND_DATA__DOVI][7] & 0xE0) == 0x20)||((_p->dataPacket[HDMI21_DISLAND_DATA__DOVI][7] & 0xE0) == 0x00)){
				/* Legnth == 0x18? */
				__vsifLen  = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][2];

				HDMI21_LINE_DBG(191, " DBG[%d] : Length[%d]\n", _p->port, __vsifLen);

				if(__vsifLen  == 0x18){
					/* PB6 == 0x0 ? */
					if(memcmp((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOVI][9], (void *)&__sZero19bytes[0], 19) == 0){
						/* AVI RGB ?  && Q1-Q0 == FULL Range */
						if(((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][4]&0x60)>>5) == 0x0){
							if((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][6] & 0x0C) == 0x08){

								HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby Standard Old VSI\n", _p->port);
								ret = (UINT8)HDMI_DOLBY_STD_OLDVSI;

								if((_p->isDolbyHDR == (int)HDMI_DOLBY_STATE_OFF)\
										&&(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value != 0)\
										&&(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value != 2))
								{
									HDMI20_PRINT("Notice %d : Detected Dolby VSI. Pattern ON!\n", _p->port);
									HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
								}
								else{
									/* Mute off will be done at main thread mute-watchdog */	
								}
							}
							else{
								/* This is Not Dolby */
								HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby VSI verification. Not Full Quan Range!\n", _p->port);
							}
						}
						else{
							/* This is Not Dolby */
							HDMI21_LINE_DBG(1207, "DBG %d : Dolby VSI verification. Not RGB AVI!!!\n", _p->port);
						}
					}
					else{
						/* This is Not Dolby */
						HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby VSI verification. PB06~PB24 are not all zeros!\n", _p->port);
					}
				}
				else{
					/* This is Not Dolby */
					HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby VSI verification. VSI length error for dolby\n", _p->port);
				}
			} // End of DOLBY Detection */
			else{
				HDMI21_LINE_DBG(1207, "DBG[%d] : Dolby VSI verification. VSI 4K part non-spec\n", _p->port);
			}
		}
	}


	/* If DBG is enabled, override detected result */
	if(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value == 0){
		ret = (UINT8)HDMI_DOLBY_STATE_OFF;
	}
	else if(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value == 2){
		ret = (UINT8)HDMI_DOLBY_STD_OLDVSI;
	}
	else if(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value == 3){
		ret = (UINT8)HDMI_DOLBY_STD_NEWVSI;
	}
	else if(gHDMI21RxDevVideoControler[HDMI21__FORCE_DOLBY_DETECT_ON].value == 4){
		ret = (UINT8)HDMI_DOLBY_LL_422_12B;
	}


	return ret;
}

LX_HDMI_HDR_MODE_T HDMI21_HAL_Rx_Get_HDR_Mode(UINT8 port)
{
       HDMI21_HAL_RX_DEVICE_DATA *_p;
       LX_HDMI_HDR_MODE_T ret = LX_HDMI_HDR_MODE_SDR;

       UINT8 type = 0x0;
       UINT8 version = 0x0;
       UINT8 length = 0x0;
       UINT8 eotf_type = 0x0;
       UINT8 is_dolby_hdr = 0x0;

       if( port >= g_hdmi20_number_of_ports ){
               HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
               return LX_HDMI_HDR_MODE_MAX;
       }

       //get handler
       _p = &gHDMI21RxHandler[port];

       is_dolby_hdr = HDMI21_HAL_Rx_Get_IsDolbyHDR(port);

       if( is_dolby_hdr != HDMI_DOLBY_STATE_OFF ){
               ret = LX_HDMI_HDR_MODE_DOLBY;
               return ret;
       }

       //get drm packet info
       type = _p->dataPacket[HDMI21_DISLAND_DATA__DRM][0];
       version = _p->dataPacket[HDMI21_DISLAND_DATA__DRM][1];
       length = _p->dataPacket[HDMI21_DISLAND_DATA__DRM][2];
       eotf_type = (_p->dataPacket[HDMI21_DISLAND_DATA__DRM][4] & 0x7);

       if( (type == 0x87) && (version == 0x1)){
               if( eotf_type == 0x2 ) {
                       ret = LX_HDMI_HDR_MODE_HDR10;
               } else if (eotf_type == 0x3 ){
                       ret = LX_HDMI_HDR_MODE_HLG;
               } else {
                       ret = LX_HDMI_HDR_MODE_SDR;
               }
       } else {
               //ret = LX_HDMI_HDR_MODE_MAX;
       			ret = LX_HDMI_HDR_MODE_SDR;
	   }
       return ret;
}

void HDMI21_HAL_Rx_Set_ScdcMode(UINT8 port, int force)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret;
	UINT8 lowFreqGain;
	UINT32 isScrambling;
	int isOnboard = 0;


	/* Port Defence */
	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	/* Get Handler */
	_p = &gHDMI21RxHandler[port];

	/* Defence Code : Handler function pointer is about to be called */
	if(!_p->initiated) {
		HDMI20_ERROR("[%s:%d] Error! HDMI21 device Handler not initiated!\n", __F__, __L__);
		return;
	}

	if(force > 0) { _p->frlRateRcv = 0;}

	/* Check On Board HDMI Source */
	if(((gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_FORCE_8K_MODEL].value == 0) && (gHDMI21RxHandler[port].is8KModel > 0)) || \
			(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_FORCE_8K_MODEL].value > 0)) {
		if(port == 0) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT0].value > 0) {
				isOnboard = 1;
			}
		}
		else if(port == 1) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT1].value > 0) {
				isOnboard = 1;
			}
		}
		else if(port == 2) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT2].value > 0) {
				isOnboard = 1;
			}
		}
		else if(port == 3) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT3].value > 0) {
				isOnboard = 1;
			}
		}
		else if(port == 4) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT4].value > 0) {
				isOnboard = 1;
			}
		}

	}

	/* Incase debug mode is ON, execute if there was a difference compared to current setting */
	if((gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value == 0) || (gHDMI21RxDevVideoControler[HDMI21__VIDEO_TRIGGER_SCDC_CHG_WATCHDOG].value > 0)){

		/* DBG Flag */
		if( gHDMI21RxDevVideoControler[HDMI21__VIDEO_TRIGGER_SCDC_CHG_WATCHDOG].value != 0) {
			gHDMI21RxDevVideoControler[HDMI21__VIDEO_TRIGGER_SCDC_CHG_WATCHDOG].value = 0;
		}

		if((_p->phyInitiatedMode != __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p))|| ((force > 0) && (__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)))
		{
			if(force > 0) {
				HDMI20_VIDEO("Notice [%d] :  ReInit Phy to [%s] \n",\
						_p->port, phymode_type_to_str(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p)));
			}
			else {
				HDMI20_VIDEO("Notice [%d] : ReInit Phy due to SCDC change from [%s] to SCDC[%s] \n",\
						_p->port, phymode_type_to_str(_p->phyInitiatedMode), phymode_type_to_str(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p)));
			}

			/* 2020/08/04 : NVidia O20 */
			gHdmi21LaneLockLossFlag[_p->port] = 0;

			/* PHY : Get Scrambling Information & Get RS Gain */
			isScrambling = __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p);

			if(isOnboard > 0) {
				if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3_ONBOARD].value;
				}
				else if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE2_ONBOARD].value;
				}
				else if (__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE1_ONBOARD].value;
				}
				else {
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE0_ONBOARD].value;
				}
			}
			else {
				if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3].value;
				}
				else if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE2].value;
				}
				else if (__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE1].value;
				}
				else {
					lowFreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE0].value;
				}
			}

			/* Set PHY To appropreiate Mode */
			ret = HDMI21_PHY_Rx_Set_3g6gMode(_p->port, gHDMI21RxDevVideoControler[HDMI21__VIDEO_AUTO_SCRAMBLE_FOR_HDMI20].value, __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p), isScrambling, lowFreqGain);
			if(ret<0){
				HDMI20_ERROR("Port[%d] : Cannot change Phy mode. Return error from Phy API[%d]\n", _p->port, ret);
			}

			/* Clear All Information */
			__HDMI21_HAL_Rx_Set_ResetHandlerData(_p, 0);

			/* Reset Link Engine */
			__HDMI21_HAL_Rx_Set_ResetLink(_p, 0);

			/* If HLC API's are called in ISR routines.. linux will crash */
			/* HDCP2.2 */
			if(_p->gWasHDCP22Written > 0) {
				HDMI21_HDCP23_Module_Set_HlcReset(_p->port, 1); 
			}

			/* SNPS BUG : SW WA for O20  */
			if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				HDMI21_DEFRAMER_Rx_Set_NumOfPreambleLock(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_FRL_DEFRAMER_PREAMBLE_LOCK].value);
				/* VMONITOR */
				HDMI21_VMON_Rx_Set_Initiate(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_VMON_SOURCE_TYPE_FRL].value);
			}
			else{
				HDMI21_DEFRAMER_Rx_Set_NumOfPreambleLock(_p, 8);
				/* VMONITOR */
				HDMI21_VMON_Rx_Set_Initiate(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_VMON_SOURCE_TYPE_TMDS].value);
			}

			HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_MUTE);
			_p->isAudioMute = HDMI21_AUDIO_MUTE;
			/* Soft reset for iaudclk domain(dmi_sw_rst.aud_swreset) */
			_p->audioStableCnt = 0;

			/* 2019/05/23 */
			__HDMI21_HAL_Rx_Set_Audio_Change(_p);
		}
		else {
			HDMI20_VIDEO("Notice [%d] : SCDC Change Func called without any TMDS config changes\n", _p->port);
		}

		_p->scdc_change  = false;

	}
	else{
		_p->scdc_change  = false;

	}
}

int HDMI21_HAL_Rx_DBG_GetDevControllerCnt(HDMI20_DEV_CONTROL_TYPE_T type, int *pCnt, int isInternalCall)
{
	int ret = RET_ERROR;
	int cnt = 0;

	do{
		if(type >= HDMI20_DEV_CONTROL_MAXNUM){
			HDMI20_ERROR("ERR : Unknown type[%d]\n", type);
			break;
		}

		if(pCnt == NULL){
			HDMI20_ERROR("ERR : Provided pCnt is NULL\n");
			break;
		}

		switch(type)
		{
			case HDMI20_DEV_CONTROL_VIDEO :
				cnt = HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM;
				break;
			case HDMI20_DEV_CONTROL_AUDIO : 
				cnt = HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM;
				break;
			case HDMI20_DEV_CONTROL_PHY :
				cnt = HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM;
				break;
			case HDMI20_DEV_CONTROL_LINK :
				cnt = HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM;
				break;
			case HDMI20_DEV_CONTROL_EARC :
				cnt = HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM;
				break;
			default :
				/* Do nothing */
				break;
		}

		if(isInternalCall) {
			memcpy((int *)pCnt, &cnt, sizeof(int));
			ret = RET_OK;
		}
		else{
			ret = copy_to_user((int *)pCnt, &cnt, sizeof(int));
		}
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_DBG_GetDevController(HDMI20_DEV_CONTROL_TYPE_T type, HDMI20_DEV_CONTROL_T *pDevCon, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	int cnt = 0;
	int sizeOfDevCon = 0;
	HDMI20_DEV_CONTROL_T *pKdriverDevCon = NULL;

	do{
		if(type >= HDMI20_DEV_CONTROL_MAXNUM){
			HDMI20_ERROR("ERR : Unknown type[%d]\n", type);
			break;
		}

		if(pDevCon == NULL){
			HDMI20_ERROR("ERR : Provided pCnt is NULL\n");
			break;
		}

		/* Get Size */
		switch(type)
		{
			case HDMI20_DEV_CONTROL_VIDEO :

				cnt = HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI21RxDevVideoControler;
				break;
			case HDMI20_DEV_CONTROL_AUDIO : 
				cnt = HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI21RxDevAudioControler;
				break;
			case HDMI20_DEV_CONTROL_PHY :
				cnt = HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI21RxDevPhyControler;
				break;
			case HDMI20_DEV_CONTROL_LINK :
				cnt = HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI21RxDevLinkControler;
				break;
			case HDMI20_DEV_CONTROL_EARC :
				cnt = HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI21DevEARCControler;
				break;
			default :
				/* Do nothing */
				break;
		}

		/* Check if size is valid for copying data */
		sizeOfDevCon = cnt * sizeof(HDMI20_DEV_CONTROL_T);

		if(sizeOfDevCon != size){
			HDMI20_ERROR("ERR : size of type[%d] devCon[%d] does not equal to provided size[%d]\n", type, sizeOfDevCon, size);
			break;
		}

		if(isInternalCall){
			memcpy((HDMI20_DEV_CONTROL_T *)pDevCon, pKdriverDevCon, size);
			ret = RET_OK;
		}
		else{
			ret = copy_to_user((HDMI20_DEV_CONTROL_T *)pDevCon, pKdriverDevCon, size); 
		}
	} while(0);

	return ret;
}


int HDMI21_HAL_Rx_DBG_AccessDevVideoController(HDMI21_DEV_VIDEO_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){

			if(isInternalCall) {
				memcpy((void *)&gHDMI21RxDevVideoControler[index].value, (void *)data, sizeof(UINT32));
			}
			else{
				if(copy_from_user((void *)&gHDMI21RxDevVideoControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI21RxDevVideoControler from user\n");
					break;
				}
			}

			if(index == HDMI21__FORCE_HDR10_SAMPLE_PACKET) {
				/* SJ Youm */
				for(i=0;i<g_hdmi20_number_of_ports;i++) { HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(i);}
			}
		}
		else{
			if(isInternalCall) {
				memcpy((void *)data, (void *)&gHDMI21RxDevVideoControler[index].value, sizeof(UINT32));
			}
			else{
				ret = copy_to_user((void __user *)data, (void *)&gHDMI21RxDevVideoControler[index].value, sizeof(UINT32));
				if(ret) {
					HDMI20_ERROR("Copy Error to USER space for AccessDevController .\n");
					break;
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_HAL_Rx_DBG_AccessDevLinkController(HDMI21_DEV_LINK_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;

	do{
		if(index >= HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){
			if(isInternalCall) {
				memcpy((void *)&gHDMI21RxDevLinkControler[index].value, (void  *)data, sizeof(UINT32));
			}
			else{
				if(copy_from_user((void *)&gHDMI21RxDevLinkControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI21RxDevLinkControler from user\n");
					break;
				}
			}
		}
		else{
			if(isInternalCall) {
				memcpy((void *)data, (void *)&gHDMI21RxDevLinkControler[index].value, sizeof(UINT32));
			}
			else{
				ret = copy_to_user((void __user *)data, (void *)&gHDMI21RxDevLinkControler[index].value, sizeof(UINT32));
				if(ret) {
					HDMI20_ERROR("Copy Error to USER space for AccessDevController .\n");
					break;
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_DBG_AccessDevPhyController(HDMI21_DEV_PHY_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;

	do{
		if(index >= HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){
			if(isInternalCall) {
				memcpy((void *)&gHDMI21RxDevPhyControler[index].value, (void *)data, sizeof(UINT32));
			}
			else{
				if(copy_from_user((void *)&gHDMI21RxDevPhyControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI21RxDevPhyControler from user\n");
					break;
				}
			}
		}
		else{
			if(isInternalCall){
				memcpy((void *)data, (void *)&gHDMI21RxDevPhyControler[index].value, sizeof(UINT32));
			}
			else{
				ret = copy_to_user((void __user *)data, (void *)&gHDMI21RxDevPhyControler[index].value, sizeof(UINT32));
				if(ret) {
					HDMI20_ERROR("Copy Error to USER space for AccessDevController .\n");
					break;
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_DBG_AccessDevAudioController(HDMI21_DEV_AUDIO_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;

	do{
		if(index >= HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){
			if(isInternalCall) {
				memcpy((void *)&gHDMI21RxDevAudioControler[index].value, (void  *)data, sizeof(UINT32));
			}
			else{
				if(copy_from_user((void *)&gHDMI21RxDevAudioControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI21RxDevAudioControler from user\n");
					break;
				}
			}
		}
		else{
			if(isInternalCall) {
				memcpy((void *)data, (void *)&gHDMI21RxDevAudioControler[index].value, sizeof(UINT32));
			}
			else{
				ret = copy_to_user((void __user *)data, (void *)&gHDMI21RxDevAudioControler[index].value, sizeof(UINT32));
				if(ret) {
					HDMI20_ERROR("Copy Error to USER space for AccessDevController .\n");
					break;
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


void HDMI21_HAL_Rx_PROC_ExternalInputStatus(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	LX_HDMI_PHY_INFORM_T  __c;
	LX_HDMI20_OP_STATUS_T __s;
	LX_HDMI_TIMING_INFO_T __t;
	LX_HDMI20_RX_DRM_PACKET_T __h;
	LX_HDMI_INFO_PACKET_T __p;
	UINT32 __a = 0;
	unsigned int __pid;

	int __data = 0;
	UINT32 __uD;
	UINT16 __d16 = 0;
	unsigned char __ucD[32] = {0,};

	int ret = 0;
	unsigned short __short = 0;

	HDMI21_SNPS_LINK_REG_0X584_T _r0;
	HDMI21_SNPS_LINK_REG_0X588_T _r1;
	HDMI21_SNPS_LINK_REG_0X58C_T _r2;
	HDMI21_SNPS_LINK_REG_0X590_T _r3;
	HDMI21_SNPS_LINK_REG_0X594_T _r4;
	HDMI21_SNPS_LINK_REG_0X598_T _r5;
	HDMI21_SNPS_LINK_REG_0X59C_T _r6;
	HDMI21_SNPS_LINK_REG_0X5A0_T _r7;

	/* Get PID */
	__pid = MAKE_PTID((int)task_tgid_nr(current), (int)task_pid_nr(current));

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	memset((void *)&__ucD[0], 0, (sizeof(unsigned char) * 32));

	/* Get Handler for Port */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

	/* Head */
	seq_printf(m, "===== HDMI STATUS =====\n");

	/* Open Status */
	seq_printf(m, "open:%u\n", gHdmi21KdrvOpenCnt);


	/* Connection Status */
	ret = HDMI21_PHY_Rx_Get_PhyStatus(&__c, sizeof(LX_HDMI_PHY_INFORM_T), 0, 1);
	seq_printf(m, "connection_state:%u\n", __pid);

	/* hpd status */
	ret = HDMI21_HAL_Rx_Get_OperationStatus(port, &__s);
	if(__s.isRestartState == true) {
		__data = 2;
	}
	else {
		if(gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value > 0) {
			__data = 1;
		}
		else {
			__data = 0;
		}
	}
	seq_printf(m, "hpd_state:%d\n", __data);

	/* Timing Info */
	ret = HDMI21_HAL_Rx_Get_StableTimingInfo(port, &__t, sizeof(LX_HDMI_TIMING_INFO_T) ,1);
	seq_printf(m,"hwport:%d\n", port);
	seq_printf(m,"timing_h_freq:%d\n", __t.hFreq);
	seq_printf(m,"timing_v_freq:%d\n", __t.vFreq );
	seq_printf(m,"timing_h_total:%d\n", __t.hTotal );
	seq_printf(m,"timing_v_total:%d\n", __t.vTotal);
	seq_printf(m,"timing_active_w:%d\n", __t.hActive);
	seq_printf(m,"timing_active_h:%d\n", __t.vActive);
	seq_printf(m,"timing_scan_type:%d\n", __t.scanType );
	if(_p->is5Vconnected == 0) {
		__data = 0;
	}
	else {
		if(__t.isDVI > 0) __data = 0;
		else __data = 1;
	}
	seq_printf(m,"dvi_hdmi:%d\n", __data);
	if((__t.deepColorMode == 0) || (__t.deepColorMode == 4)) __data = 0; 
	else if(__t.deepColorMode == 5)	__data = 1; 
	else if(__t.deepColorMode == 6)	__data = 2; 
	else if(__t.deepColorMode == 7)	__data = 3; 			
	else __data = 0; 
	seq_printf(m,"color_depth:%d\n", __data );
	if(__t.isAllmMode > 0) __data = 1;
	else __data = 0;
	seq_printf(m,"allm_mode:%d\n", __data);


	/* DRM INFO */
	ret = HDMI21_DISLAND_Rx_Get_DRMInfo(port, &__h, sizeof(LX_HDMI20_RX_DRM_PACKET_T), 1);

	seq_printf(m,"drm_version:%d\n", __h.nVersion);
	seq_printf(m,"drm_length:%d\n", __h.nLength);
	seq_printf(m,"drm_eotf_type:%d\n", (int)(__h.metaData[4]));
	seq_printf(m,"drm_meta_desc:%d\n", (int)(__h.metaData[5]));

	memcpy((void *)&__short, (void *)&__h.metaData[6], sizeof(unsigned short));
	seq_printf(m,"drm_display_primaries_x0:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[8], sizeof(unsigned short));
	seq_printf(m,"drm_display_primaries_y0:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[10], sizeof(unsigned short));
	seq_printf(m,"drm_display_primaries_x1:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[12], sizeof(unsigned short));
	seq_printf(m,"drm_display_primaries_y1:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[14], sizeof(unsigned short));
	seq_printf(m,"drm_display_primaries_x2:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[16], sizeof(unsigned short));
	seq_printf(m,"drm_display_primaries_y2:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[18], sizeof(unsigned short));
	seq_printf(m,"drm_white_point_x:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[20], sizeof(unsigned short));
	seq_printf(m,"drm_white_point_y:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[22], sizeof(unsigned short));
	seq_printf(m,"drm_max_display_mastering_luminance:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[24], sizeof(unsigned short));
	seq_printf(m,"drm_min_display_mastering_luminance:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[26], sizeof(unsigned short));
	seq_printf(m,"drm_maximum_content_light_level:%u\n", __short);
	memcpy((void *)&__short, (void *)&__h.metaData[28], sizeof(unsigned short));
	seq_printf(m,"drm_maximum_frame_average_light_level:%u\n\n", __short);

	/* VSI INFO */
	ret = HDMI21_DISLAND_Rx_Get_VSIInfo( port, &__p,  sizeof(LX_HDMI_INFO_PACKET_T), 1, LX_HDMI20_VSI_H14B_VSIF);

	__data 	= ((__p.dataBytes[1] &0xff))>> 5;
	seq_printf(m, "vsi_video_format:%d\n", __data);

	__data	= ((__p.dataBytes[1] &0xff0000)>>16)>> 4;
	seq_printf(m, "vsi_st_3d:%d\n", __data);

	__data	= ((__p.dataBytes[1] &0xff0000)>>16)>> 4;
	seq_printf(m, "vsi_ext_data_3d:%d\n", __data);

	__data	= (__p.dataBytes[1] &0xff00)>>8;
	seq_printf(m, "vsi_vic:%d\n", __data);
					 
	__ucD[0]  = (unsigned char)((__p.dataBytes[0] &0xff00)>>8);
	__ucD[1] =  (unsigned char)((__p.dataBytes[0] &0xff0000)>>16);
	__ucD[2] =  (unsigned char)((__p.dataBytes[0] &0xff000000)>>24);

	seq_printf(m, "vsi_regid:0x%02x,0x%02x,0x%02x\n", __ucD[0], __ucD[1], __ucD[2]);

	memcpy((void *)&__ucD[0], (void *)&__p.dataBytes[1], sizeof(unsigned char) * 23);
	seq_printf(m, "vsi_payload:0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x\n",\
			__ucD[0],__ucD[1],__ucD[2],__ucD[3],__ucD[4],__ucD[5],__ucD[6],__ucD[7],__ucD[8],__ucD[9],\
			__ucD[10],__ucD[11],__ucD[12],__ucD[13],__ucD[14],__ucD[15],__ucD[16],__ucD[17],__ucD[18],__ucD[19],\
			__ucD[20], __ucD[21], __ucD[22]);



	/* SPD INFO */
	seq_printf(m, "\n");
	ret = HDMI21_DISLAND_Rx_Get_SPDInfo(port, &__p,  sizeof(LX_HDMI_INFO_PACKET_T), 1);

	memcpy((void *)&__ucD[0], (void *)&__p.dataBytes[0], sizeof(unsigned char) * 8); __ucD[8] = 0x0;
	seq_printf(m, "spd_vendor_name:\"%s\"\n", __ucD);

	memcpy((void *)&__ucD[0], (void *)&__p.dataBytes[0], sizeof(unsigned char) * 16); __ucD[16] = 0x0;
	seq_printf(m, "spd_product_description:\"%s\"\n", __ucD);

	__data = (__p.dataBytes[6] &0xff00)>>8;
	seq_printf(m, "spd_source_device_info:%d\n", __data );
		
	/* AVI INFO */
	seq_printf(m, "\n");
	ret = HDMI21_DISLAND_Rx_Get_AVIInfo(port, &__p,  sizeof(LX_HDMI_INFO_PACKET_T), 1);

	if(_p->is5Vconnected == 0) {
		__data = 0;
	}
	else {
		if(_p->hwVideo.dvi) __data = 0;
		else __data = 1;
	}
	seq_printf(m, "avi_mode:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff00)>>8) &0x60)>>5;		// Y1Y0
	seq_printf(m, "avi_pixel_encoding:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff00)>>8) &0x10)>>4;		// A0
	seq_printf(m, "avi_active_info:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff00)>>8) &0x0c)>>2;		// B1B0
	seq_printf(m, "avi_bar_info:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff00)>>8) &0x03);			// S1S0
	seq_printf(m, "avi_scan_info:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff0000)>>16) &0xc0)>>6;	// C1C0
	seq_printf(m, "avi_colorimetry:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff0000)>>16) &0x30)>>4;	// M1M0
	seq_printf(m, "avi_picture_aspect_ratio:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff0000)>>16) &0x0f);		// R3R2R1R0
	seq_printf(m, "avi_active_format_aspect_ratio:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff000000)>>24) &0x03);					// SC1SC0
	seq_printf(m, "avi_scaling:%d\n", __data);

	__data = (((__p.dataBytes[1] &0xff)) &0x7f);				// VIC6~VIC0
	seq_printf(m, "avi_vic:%d\n", __data);

	__data = (((__p.dataBytes[1] &0xff00)>>8) &0x0f);
	seq_printf(m, "avi_pixel_repeat:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff000000)>>24) &0x80)>>7;			// ITC
	seq_printf(m, "avi_it_content:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff000000)>>24) &0x70)>>4;
	seq_printf(m, "avi_extended_colorimetry:%d\n", __data);

	__data = (((__p.dataBytes[0] &0xff000000)>>24) &0x0c)>>2;	// Q1Q0
	seq_printf(m, "avi_rgb_quantization_range:%d\n", __data);

	__data = (((__p.dataBytes[1] &0xff00)>>8) &0xc0)>>6;			// YQ1YQ0
	seq_printf(m, "avi_ycc_quantization_range:%d\n", __data);

	__data = (((__p.dataBytes[1] &0xff00)>>8) &0x30)>>4;
	seq_printf(m, "avi_content_type:%d\n", __data);

	__data = ((__p.dataBytes[1] &0xffff0000)>>16);
	seq_printf(m, "avi_top_bar_end_line_number:%d\n", __data);
	
	__data = ((__p.dataBytes[2] &0xffff));
	seq_printf(m, "avi_bottom_bar_start_line_number:%d\n", __data);
					
	__data = ((__p.dataBytes[2] &0xffff0000)>>16);
	seq_printf(m, "avi_left_bar_end_pixel_number:%d\n", __data);

	__data = ((__p.dataBytes[3] &0xffff));	
	seq_printf(m, "avi_right_bar_end_pixel_number:%d\n", __data);
					 
	seq_printf(m, "packet_status:2\n");
	seq_printf(m, "packet_type:130\n");

	__data = (__p.header & 0xff);
	seq_printf(m, "packet_version:%d\n", __data);

	__data = (__p.header &0xff00 )>>8;
	seq_printf(m, "packet_length:%d\n", __data);

	memcpy((void *)&__ucD[0], (void *)&_p->dataPacket[HDMI21_DISLAND_DATA__AVI][0],  HDMI21_MAX_DATA_PACKET_LENGTH);

	seq_printf(m, "packet_data_bytes:0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x\n",\
		__ucD[0],__ucD[1],__ucD[2],__ucD[3],__ucD[4],__ucD[5],__ucD[6],__ucD[7],__ucD[8],__ucD[9],\
		__ucD[10],__ucD[11],__ucD[12],__ucD[13],__ucD[14],__ucD[15],__ucD[16],__ucD[17],__ucD[18],__ucD[19],\
		__ucD[20],__ucD[21],__ucD[22],__ucD[23],__ucD[24],__ucD[25],__ucD[26],__ucD[27],__ucD[28],__ucD[29],\
		__ucD[30],__ucD[31] );

	/* Dolby */
	seq_printf(m, "\n");
	seq_printf(m, "dolby_hdr_type:%d\n", _p->isDolbyHDR);

	/* VRR Freq */
	seq_printf(m, "\n");
	ret = HDMI21_HAL_Rx_Get_VrrCurrentVfreq(port, &__d16, sizeof(UINT16), 1);
	seq_printf(m, "vrr_frequency:%u\n", __d16);

	/* EMP Info : Not supported */		
	seq_printf(m, "\n");
	seq_printf(m, "emp_type: not implemented\n");
	seq_printf(m, "emp_total_packet_number: not implemented\n");
	seq_printf(m, "emp_data: not implemented\n");


	/* PHY */
	seq_printf(m, "\n");
	seq_printf(m, "phy_lock_status:%d\n", _p->isPhyLocked);
	seq_printf(m, "phy_tmds_clk_khz:%llu\n", _p->phy_tmds_clk);
	
	if(_p->phyInitiatedMode >=HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) __data = 1;
	else __data = 0;
	seq_printf(m, "phy_link_type:%d\n", __data);

	if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L) __data = 3;
	else __data = 4;
	seq_printf(m, "phy_link_lane:%d\n", __data);

	if((_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_3G)||(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)) __data = 3;
	else if((_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_6G)
			||(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_6G_3L)||(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_6G_4L)) __data = 6;
	else if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) __data = 8;
	else if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) __data = 10;
	else __data = 12;
	seq_printf(m, "phy_link_rate:%d\n", __data);

	__ucD[0] = (unsigned char)_p->phyTCSMin[0]; 	__ucD[1] = (unsigned char)_p->phyTCSMin[1];
	__ucD[2] = (unsigned char)_p->phyTCSMin[2];		__ucD[3] = (unsigned char)_p->phyTCSMin[3];
	seq_printf(m, "phy_ctle_eq_min_range:0x%02x, 0x%02x, 0x%02x, 0x%02x\n", __ucD[0], __ucD[1], __ucD[2], __ucD[3]);

	__ucD[0] = (unsigned char)_p->phyTCSMax[0]; 	__ucD[1] = (unsigned char)_p->phyTCSMax[1];
	__ucD[2] = (unsigned char)_p->phyTCSMax[2];		__ucD[3] = (unsigned char)_p->phyTCSMax[3];
	seq_printf(m, "phy_ctle_eq_max_range:0x%02x, 0x%02x, 0x%02x, 0x%02x\n", __ucD[0], __ucD[1], __ucD[2], __ucD[3]);
	
	__ucD[0] = (unsigned char)_p->phyTCSResult[0]; 	__ucD[1] = (unsigned char)_p->phyTCSResult[1];
	__ucD[2] = (unsigned char)_p->phyTCSResult[2];		__ucD[3] = (unsigned char)_p->phyTCSResult[3];
	seq_printf(m, "phy_ctle_eq_result:0x%02x, 0x%02x, 0x%02x, 0x%02x\n", __ucD[0], __ucD[1], __ucD[2], __ucD[3]);
					
	__ucD[0] = (unsigned char)_p->phyCEDError[0]; 	__ucD[1] = (unsigned char)_p->phyCEDError[1];
	__ucD[2] = (unsigned char)_p->phyCEDError[2];		__ucD[3] = (unsigned char)_p->phyCEDError[3];
	seq_printf(m, "phy_error(ced):0x%02x, 0x%02x, 0x%02x, 0x%02x\n", __ucD[0], __ucD[1], __ucD[2], __ucD[3]);
	
	/* Link */
	seq_printf(m, "\n");
	seq_printf(m, "link_hpd:%d\n", _p->isHPD );
	seq_printf(m, "link_hdmi_5v:%d\n", _p->is5Vconnected);
	seq_printf(m, "link_rx_sense:%d\n", _p->is5Vconnected);
	seq_printf(m, "link_frame_rate_x100_hz:%d\n", _p->real_vfreq);
	if(_p->hwVideo.dvi > 0) __data = 0;
	else __data = 1;
	seq_printf(m, "link_dvi_hdmi_mode:%d\n",__data);
	seq_printf(m, "link_video_width:%d\n", _p->hwVideo.hactive);
	seq_printf(m, "link_video_height:%d\n", _p->hwVideo.vactive);
	seq_printf(m, "link_color_space:%d\n", _p->hwVideo.video_format);
	seq_printf(m, "link_color_depth:%d\n", _p->hwVideo.deep_color_mode);
	//seq_printf(m, "link_colorimetry:%d\n", _p->hwVideo.colorimetry);
	//seq_printf(m, "link_ext_colorimetry:%d\n", );
	//seq_printf(m, "link_additional_colorimetry:%d\n", );
	//seq_printf(m, "link_hdr_type:%d\n", );
	seq_printf(m, "link_audio_format:not implemented\n");
	seq_printf(m, "link_audio_sampling_freq:not implemented\n");
	seq_printf(m, "link_audio_channel_number:not implemented\n");
					 
	#if 0			
	video_width_real:1920
	video_htotal_real:2200
 	video_height_real:1080
	video_vtotal_real:1125
	pixel_clock_khz:148500
	current_vrr_refresh_rate:60

	audio_pcm_N:0
	audio_pcm_CTS:73729080
	audio_LayoutBitValue:20
	audio_ChannelStatusBits:68

	hdcp_version:0
	hdcp_auth_status:3
	hdcp_encEn:1
	hdcp14_status.port:60
	hdcp14_status.An:0x53 0xb0 0x9a 0xd9 0x53 0xb0 0x9a 0xd9
	hdcp14_status.Aksv:0xdf 0x63 0x49 0x4c 0x98
	hdcp14_status.Bksv:0x3c 0xa0 0xf4 0x66 0xf4
	hdcp14_status.Ri:0xfe 0xff
	hdcp14_status.Bcaps:129
	hdcp14_status.Bstatus:0x0 0x0
	hdcp22_status.port:0
	hdcp22_status.ake_init_count_since_5v:0
	hdcp22_status.reauth_req_count_since_5v:0
	#endif			

	/* 2019/06/24 : Get SCDC Info */
	seq_printf(m, "\n");

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		__a = 0x4;
	}
	else {
		__a = 0;
	}
	__uD = _p->link_read(0x584 + __a);	memcpy((void *)&_r0, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));
	__uD = _p->link_read(0x588 + __a);	memcpy((void *)&_r1, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X588_T));
	__uD = _p->link_read(0x58C + __a);	memcpy((void *)&_r2, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
	__uD = _p->link_read(0x590 + __a);	memcpy((void *)&_r3, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X590_T));
	__uD = _p->link_read(0x594 + __a);	memcpy((void *)&_r4, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X594_T));
	__uD = _p->link_read(0x598 + __a);	memcpy((void *)&_r5, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X598_T));
	__uD = _p->link_read(0x59C + __a);	memcpy((void *)&_r6, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X59C_T));
	__uD = _p->link_read(0x5A0 + __a);	memcpy((void *)&_r7, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X5A0_T));


	seq_printf(m, "scdc_source_version:%d\n", _r0.SCDC_SOURCEVERSION);
	seq_printf(m, "scdc_sink_version:1\n");
	seq_printf(m, "scdc_rsed_update:%d\n", _r0.SCDC_RSED_UPDATE);
	seq_printf(m, "scdc_flt_update:%d\n", _r0.SCDC_FLT_UPDATE);
	seq_printf(m, "scdc_frl_start:%d\n", _r0.FRL_START_STS);
	seq_printf(m, "scdc_source_test_update:%d\n", _r0.SCDC_SOURCE_TEST_UPDATE);
	seq_printf(m, "scdc_rr_test:%d\n", _r0.SCDC_RRTEST);
	seq_printf(m, "scdc_ced_update:%d\n", _r0.SCDC_CEDUPDATE);
	seq_printf(m, "scdc_status_update:%d\n", _r0.SCDC_STATUSUPDATE);
	seq_printf(m, "scdc_tmds_bit_clock_ratio:%d\n", _r1.SCDC_TMDSBITCLKRATIO);
	seq_printf(m, "scdc_scrambling_enable:%d\n", _r1.SCDC_SCRAMB_STATUS);
	seq_printf(m, "scdc_tmds_scrambler_status:%d\n", _r1.SCDC_SCRAMB_STATUS);
	seq_printf(m, "scdc_flt_no_retrain:%d\n", _r1.SCDC_SCRAMB_STATUS);
	seq_printf(m, "scdc_rr_enable:%d\n", _r2.SCDC_RRENABLE);
	seq_printf(m, "scdc_ffe_levels:%d\n", _r1.SCDC_SCRAMB_STATUS);
	seq_printf(m, "scdc_frl_rate:%d\n", _r1.SCDC_SCRAMB_STATUS);
	seq_printf(m, "scdc_dsc_decode_fail: not implemented\n");
	seq_printf(m, "scdc_flt_ready: not implemented\n");
	seq_printf(m, "scdc_clk_detect:%d\n", _r3.SCDC_CLOCKDETECTED);
	seq_printf(m, "scdc_ch0_locked:%d\n", _r3.SCDC_CH0LOCKED);
	seq_printf(m, "scdc_ch1_locked:%d\n", _r3.SCDC_CH1LOCKED);
	seq_printf(m, "scdc_ch2_locked:%d\n", _r3.SCDC_CH2LOCKED);
	seq_printf(m, "scdc_ch3_locked:%d\n", _r3.SCDC_LN0LOCKED);
	seq_printf(m, "scdc_lane0_ltp_request:%d\n", _r3.SCDC_FLT_LN0_LTP_REQ);
	seq_printf(m, "scdc_lane1_ltp_request:%d\n", _r3.SCDC_FLT_LN1_LTP_REQ);
	seq_printf(m, "scdc_lane2_ltp_request:%d\n", _r3.SCDC_FLT_LN2_LTP_REQ);
	seq_printf(m, "scdc_lane3_ltp_request:%d\n", _r3.SCDC_FLT_LN3_LTP_REQ);

	if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)
	{
		seq_printf(m, "scdc_ch0_ced_valid:%d\n", _r5.SCDC_ERDET_LANE0_VALID);
		seq_printf(m, "scdc_ch1_ced_valid:%d\n", _r6.SCDC_ERDET_LANE1_VALID);
		seq_printf(m, "scdc_ch2_ced_valid:%d\n", _r6.SCDC_ERDET_LANE2_VALID);
		seq_printf(m, "scdc_ch3_ced_valid:%d\n", _r7.SCDC_ERDET_LANE3_VALID);
		seq_printf(m, "scdc_ch0_ced:%d\n", _r5.SCDC_ERDET_LANE0);
		seq_printf(m, "scdc_ch1_ced:%d\n", _r6.SCDC_ERDET_LANE1);
		seq_printf(m, "scdc_ch2_ced:%d\n", _r6.SCDC_ERDET_LANE2);
		seq_printf(m, "scdc_ch3_ced:%d\n", _r7.SCDC_ERDET_LANE3);
	}
	else {
		seq_printf(m, "scdc_ch0_ced_valid:%d\n", _r4.SCDC_ERR_DET0_VALID);
		seq_printf(m, "scdc_ch1_ced_valid:%d\n", _r4.SCDC_ERR_DET1_VALID);
		seq_printf(m, "scdc_ch2_ced_valid:%d\n", _r5.SCDC_ERR_DET2_VALID);
		seq_printf(m, "scdc_ch0_ced:%d\n", _r4.SCDC_ERR_DET0);
		seq_printf(m, "scdc_ch1_ced:%d\n", _r4.SCDC_ERR_DET1);
		seq_printf(m, "scdc_ch2_ced:%d\n", _r5.SCDC_ERR_DET2);
	}
	
	return;
}



void HDMI21_HAL_Rx_PROC_PrintEyeMonitor(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int x,y;

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	/* Get Handler for Port */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];


	if(gHdmi21EyeMeasure[port] == 1) {
		seq_printf(m, "Cannot show results. Eye Measure is in Progress\n");
		return;
	}
	else if(gHdmi21EyeMeasure[port] == 0) {
		seq_printf(m, "Measurement was not initiated\n");
		return;
	}

	seq_printf(m, "Port[%d] Delta Eye Diagram\n", _p->port);

	for(y=0;y<127;y=y+gHdmi21EyeYPrintScale)
	{
		if(y == 63) seq_printf(m, "*");
		else seq_printf(m, "| ");
		for(x=0;x<31;x++)	{
			if(gHdmi21EyePrintMode == 0) seq_printf(m, "%s", __val_to_graphic(gHdmi21EyeDataCh0[_p->port][y][x]));	
			else seq_printf(m, "%s", __val_to_hex(gHdmi21EyeDataCh0[_p->port][y][x]));
		}
		seq_printf(m, " | ");
		for(x=0;x<31;x++)	{
			if(gHdmi21EyePrintMode == 0) seq_printf(m, "%s", __val_to_graphic(gHdmi21EyeDataCh1[_p->port][y][x]));	
			else seq_printf(m, "%s", __val_to_hex(gHdmi21EyeDataCh1[_p->port][y][x]));
		}
		seq_printf(m, " | ");
		for(x=0;x<31;x++)	{
			if(gHdmi21EyePrintMode == 0) seq_printf(m, "%s", __val_to_graphic(gHdmi21EyeDataCh2[_p->port][y][x]));	
			else seq_printf(m, "%s", __val_to_hex(gHdmi21EyeDataCh2[_p->port][y][x]));
		}
		seq_printf(m, " | ");
		for(x=0;x<31;x++)	{
			if(gHdmi21EyePrintMode == 0) seq_printf(m, "%s", __val_to_graphic(gHdmi21EyeDataCh3[_p->port][y][x]));	
			else seq_printf(m, "%s", __val_to_hex(gHdmi21EyeDataCh3[_p->port][y][x]));
		}
	
		seq_printf(m, "\n");
	}

	return;
}




void HDMI21_HAL_Rx_PROC_PrintPhySetting(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 __data = 0;
	UINT32 __reg  = 0;

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	/* Get Handler for Port */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];



	
	/* Connection */
	seq_printf(m, "[Connection Setting]\n");
	
	__reg = 0x38; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t1) MAN_CON_SEL        [0x28]:[0x38] => [0x%02x]\n", __data);		

	/* HDMI Mode */
	seq_printf(m, "[HDMI Mode Setting]\n");
	
	__reg = 0x2a; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t1) Manual HDMI20_MODE [0x28]:[0x2A] => [0x%02x]\n", __data);	
	
	__reg = 0x26; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t2) Manual HDMI21_MODE [0x28]:[0x26] => [0x%02x]\n", __data);
	
	__reg = 0x88; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t3) SCR_MAN_OFF        [0x48]:[0x88] => [0x%02x]\n", __data);
	
	__reg = 0x23; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t4) EQ_HDMI20_VAL      [0x28]:[0x23] => [0x%02x]\n", __data);

	__reg = 0xa8; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t5) EQ_DHFG            [0x38]:[0xa8] => [0x%02x]\n", __data);

	/* PHY DC */
	seq_printf(m, "[PHY DC Setting]\n");

	__reg = 0x70; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t1) VBGR               [0x28]:[0x70] => [0x%02x]\n", __data);

	__reg = 0x39; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t2) EQ_DOGH            [0x28]:[0x39] => [0x%02x]\n", __data);

	__reg = 0x5D; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t3) ODT_FREQ_DIV       [0x28]:[0x5D] => [0x%02x]\n", __data);
		
	__reg = 0x24; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t4) EQ_ICTRL           [0x28]:[0x24] => [0x%02x]\n", __data);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, b0) ) {
		__reg = 0x73; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
		seq_printf(m, "\t5) IDR                [0x38]:[0x73] => [0x%02x]\n", __data);
	}
	else {
		__reg = 0x45; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
		seq_printf(m, "\t5) IDR                [0x38]:[0x45] => [0x%02x]\n", __data);
	}
	__reg = 0x59; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t6) ISUM/IDAC          [0x38]:[0x59] => [0x%02x]\n", __data);
		
	__reg = 0x05; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t7) CH0_RW_AUTO_MODE=  [0x38]:[0x05] => [0x%02x]\n", __data);

	__reg = 0x41; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t8) PI_SET_MAN_MODE    [0x28]:[0x41] => [0x%02x]\n", __data);


	/* EQ */
	seq_printf(m, "[EQ Setting]\n");
	
	__reg = 0x15; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t1) EQ RS_MAN_SEL      [0x48]:[0x15] => [0x%02x]\n", __data);

	__reg = 0x16; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t2) EQ_RS_MAN_CH0      [0x48]:[0x16] => [0x%02x]\n", __data);

	__reg = 0x17; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t3) EQ_RS_MAN_CH1      [0x48]:[0x17] => [0x%02x]\n", __data);

	__reg = 0x18; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t4) EQ_RS_MAN_CH2      [0x48]:[0x18] => [0x%02x]\n", __data);

	__reg = 0x19; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t5) EQ_RS_MAN_CH3      [0x48]:[0x19] => [0x%02x]\n", __data);

	__reg = 0xA2; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t6) EQ_CS_MAN_CH0      [0x38]:[0xA2] => [0x%02x]\n", __data);

	__reg = 0xA3; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t7) EQ_CS_MAN_CH1      [0x38]:[0xA3] => [0x%02x]\n", __data);

	__reg = 0xA4; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t8) EQ_CS_MAN_CH2      [0x38]:[0xA4] => [0x%02x]\n", __data);

	__reg = 0xA5; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t9) EQ_CS_MAN_CH3      [0x38]:[0xA5] => [0x%02x]\n", __data);

	/* CDR */
	seq_printf(m, "[CDR Setting]\n");

	__reg = 0x5A; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t1) CDR ANA_CDR_SEL    [0x38]:[0x5A] => [0x%02x]\n", __data);

	__reg = 0xF3; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t2) FILTER_SEL/G1_SEL  [0x38]:[0xF3] => [0x%02x]\n", __data);

	__reg = 0xF4; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t3) G2_SEL             [0x38]:[0xF4] => [0x%02x]\n", __data);

	__reg = 0x75; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t4) PHANTOM_MAN_VAL    [0x38]:[0x75] => [0x%02x]\n", __data);

	__reg = 0x74; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t5) PHANTOM_FIX_MODE   [0x38]:[0x74] => [0x%02x]\n", __data);

	__reg = 0x70; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t6) DR_FILTER          [0x38]:[0x70] => [0x%02x]\n", __data);

	/* CS SCAN*/
	seq_printf(m, "[CS SCAN Setting]\n");

	__reg = 0x93; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	
	seq_printf(m, "\t1) DEL_SCAN2/ADD_VAL  [0x38]:[0x93] => [0x%02x]\n", __data);

	__reg = 0x92; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t2) DEL_ADD/I2C_DEL    [0x38]:[0x92] => [0x%02x]\n", __data);

	__reg = 0x8d; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t3) DELTA_SCOPE2       [0x38]:[0x8D] => [0x%02x]\n", __data);

	__reg = 0x9a; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t4) DEL_SCOPE_PLL_M3   [0x38]:[0x9A] => [0x%02x]\n", __data);

	__reg = 0x98; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t5) DELTA_MAX_ADJUST   [0x38]:[0x98] => [0x%02x]\n", __data);

	__reg = 0xB9; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t6) TCS_RE_OFF/TCS_D_M [0x38]:[0xB9] => [0x%02x]\n", __data);

	__reg = 0xB8; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t7) TCS_ERR_SEL        [0x38]:[0xB8] => [0x%02x]\n", __data);

	__reg = 0x76; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t8) DR_N2              [0x38]:[0x76] => [0x%02x]\n", __data);

	/* DFE SCAN*/
	seq_printf(m, "[DFE Setting]\n");

	__reg = 0x5C; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t1) DFE_A,B1~B5        [0x38]:[0x5C] => [0x%02x]\n", __data);

	__reg = 0x5D; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t2) DFE_N1             [0x38]:[0x5D] => [0x%02x]\n", __data);

	__reg = 0x5E; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t3) DFE_UPDN_PERIOD    [0x38]:[0x5E] => [0x%02x]\n", __data);

	__reg = 0x58; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t4) I2C_DFE_ON_MODE_ON [0x38]:[0x58] => [0x%02x]\n", __data);

	__reg = 0x52; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t5) I2C_DFE_LEVEL_B1_MO[0x38]:[0x52] => [0x%02x]\n", __data);

	__reg = 0x89; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t6) I2C_DELTA_CDR      [0x38]:[0x89] => [0x%02x]\n", __data);


	/* COMMON*/
	seq_printf(m, "[COMMON Setting]\n");

	__reg = 0x72; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t1) EQ_EVAL_TIME2      [0x38]:[0x72] => [0x%02x]\n", __data);

	__reg = 0xB3; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
  	seq_printf(m, "\t2) TCS_SCDT/MAN_P_OP  [0x38]:[0xB3] => [0x%02x]\n", __data);
   
	__reg = 0xBA; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t3) TCS_BOUNDARY       [0x38]:[0xBA] => [0x%02x]\n", __data);
	
	__reg = 0xB7; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t4) TCS_P_SEL/TCS_SCO  [0x38]:[0xB7] => [0x%02x]\n", __data);
	
	__reg = 0xBD; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t5) TCS_ER_LIMIT_BASIC [0x38]:[0xBD] => [0x%02x]\n", __data);

	if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		__reg = 0x06; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
		seq_printf(m, "\t6) FIFO_MODE          [0x48]:[0x06] => [0x%02x]\n", __data);
	}
	else {
		__reg = 0x6E; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
		seq_printf(m, "\t6) FIFO_MODE          [0x38]:[0x6E] => [0x%02x]\n", __data);
	}

	__reg = 0xA4; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t7) ERROR_UNIT_SEL     [0x48]:[0xA4] => [0x%02x]\n", __data);

	__reg = 0xB4; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t8) REG_TCS_MAN_PRE    [0x38]:[0xB4] => [0x%02x]\n", __data);
   
	__reg = 0xB5; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t9) REG_TCS_MAN_MEA_1  [0x38]:[0xB5] => [0x%02x]\n", __data);
   
	__reg = 0xB6; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tA) REG_TCS_MAN_MEA_2  [0x38]:[0xB6] => [0x%02x]\n", __data);
   
	__reg = 0xAC; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tB) CED_OPEN_LENGTH    [0x38]:[0xAC] => [0x%02x]\n", __data);
  
	__reg = 0xAD; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tC) CHK_INFINITE_MODE  [0x38]:[0xAD] => [0x%02x]\n", __data);
   
	__reg = 0xAB; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tD) CED_CHECK_MODE     [0x38]:[0xAB] => [0x%02x]\n", __data);
   
	__reg = 0xBC; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tE) CED_ADAPTIVE_PER   [0x38]:[0xBC] => [0x%02x]\n", __data);

	__reg = 0xED; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tF) EQ_FREQ_DIV        [0x38]:[0xED] => [0x%02x]\n", __data);
   
	__reg = 0xEF; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tG) CAL_INTEVAL        [0x38]:[0xEF] => [0x%02x]\n", __data);
  
	__reg = 0x8B; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tH) DELTA_MODE_PLL0~3  [0x38]:[0x8B] => [0x%02x]\n", __data);

	__reg = 0x8A; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tI) FRL_MATCH_MAN_VAL  [0x48]:[0x8A] => [0x%02x]\n", __data);

	__reg = 0x60; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\tJ) HDMI21_SYM_LOCK_SE [0x48]:[0x60] => [0x%02x]\n", __data);

	/* ODT*/
	seq_printf(m, "[ODT Setting]\n");

	__reg = 0x58; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t1) ODT MAN_ODT50      [0x28]:[0x58] => [0x%02x]\n", __data);
   
	__reg = 0x59; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t2) I2C_ODT_HDMI50     [0x28]:[0x59] => [0x%02x]\n", __data);

	/* RESET, PDB*/
	seq_printf(m, "[RESET/PDB Setting]\n");

	__reg = 0x00; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t1) RESET/PDB RESETB   [0x28]:[0x00] => [0x%02x]\n", __data);
   
	__reg = 0x48; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	seq_printf(m, "\t2) ODT_PDB            [0x28]:[0x48] => [0x%02x]\n", __data);

	seq_printf(m, "[ETC]\n");

	__reg = 0x8A; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	seq_printf(m, "\t1) DELTA SCAN MANMODE [0x38]:[0x8A] => [0x%02x]\n", __data);

	return;
}

/* DBG function for proc status */
void HDMI21_HAL_Rx_PROC_PrintVideo(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_SNPS_LINK_REG_0X584_T _r0;
	HDMI21_SNPS_LINK_REG_0X588_T _r1;
	HDMI21_SNPS_LINK_REG_0X58C_T _r2;
	HDMI21_SNPS_LINK_REG_0X590_T _r3;
	HDMI21_SNPS_LINK_REG_0X594_T _r4;
	HDMI21_SNPS_LINK_REG_0X598_T _r5;
	HDMI21_SNPS_LINK_REG_0X59C_T _r6;
	HDMI21_SNPS_LINK_REG_0X5A0_T _r7;
	UINT32 __data;
	UINT32 __a = 0;
	int i =1;


	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	/* 2020/07/14 : Thanks & Sorry to Beau of Microsoft */
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {	__a = 0x4; }
	else {	__a = 0; }

	/* Get Handler for Port */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

	/* 2019/06/24 : Get SCDC Info */
	__data = _p->link_read(0x584 + __a);	memcpy((void *)&_r0, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));
	__data = _p->link_read(0x588 + __a);	memcpy((void *)&_r1, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X588_T));
	__data = _p->link_read(0x58C + __a);	memcpy((void *)&_r2, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
	__data = _p->link_read(0x590 + __a);	memcpy((void *)&_r3, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X590_T));
	__data = _p->link_read(0x594 + __a);	memcpy((void *)&_r4, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X594_T));
	__data = _p->link_read(0x598 + __a);	memcpy((void *)&_r5, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X598_T));
	__data = _p->link_read(0x59C + __a);	memcpy((void *)&_r6, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X59C_T));
	__data = _p->link_read(0x5A0 + __a);	memcpy((void *)&_r7, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X5A0_T));

	seq_printf(m, "----------------------------------------------------------------\n");
	seq_printf(m, "Ver[%d][0x%02x] Port[%d] HDMI2.0 Module Status [%d]th Video | Platform[%d]\n", HDMI21_KERNEL_DRIVER_DATE, HDMI21_KERNEL_DRIVER_VER,_p->port, _p->stableHist, gHDMI20PlatformType);
	seq_printf(m, "----------------------------------------------------------------\n");
	seq_printf(m, "\t[%d]  Initated[%d] / Link IRQ[%d] / Top IRQ[%d] / 8K[%d]\n", i++, _p->initiated, _p->irq, _p->top_irq, _p->is8KModel);
	seq_printf(m, "\t[%d]  PHY   TMDS[%08llu] / Real TMDS[%08llu]\n", i++, _p->phy_tmds_clk, _p->real_tmds_clk);
	seq_printf(m, "\t[%d]  Pixel Clk[%08llu]  / Real Vreq[%d]\n", i++, _p->real_pixel_clk, _p->real_vfreq); 
	seq_printf(m, "\t[%d]  HDCP1.4 Key[%d] / HDCP2.3 Key[%d]\n", i++, _p->gWasHDCP14Written, _p->gWasHDCP22Written);  
	seq_printf(m, "\t[%d]  Dolby HDR Info[%d] / ZombieMode[%d]\n", i++, _p->isDolbyHDR, _p->zombieMode);
	seq_printf(m, "\t[%d]  Stable CNT[%d] / VideoChangeCount[%d] / vidChgTime[%d]\n", i++, _p->stable_cnt, _p->videoChgCount, _p->vidChgTime);
	seq_printf(m, "[RAW Sync Info]\n");
	seq_printf(m, "\t[%d]  TMDS Clk[%010d] / Pixel Clk[%010d]\n", i++, _p->hwVideo.tmds_clk, _p->hwVideo.pixel_clk);
	seq_printf(m, "\t[%d]  DVI[%d] / Interlaced[%d] / Pixel Repetition[%d]\n", i++, _p->hwVideo.dvi, _p->hwVideo.interlaced, _p->hwVideo.pixel_repetition);
	seq_printf(m, "\t[%d]  Sig:[%d](%d)x[%d](%d)@[%d]Hz (%d). vo/ho:(%d)/(%d)\n", i++, _p->hwVideo.hactive, _p->hwVideo.htotal, _p->hwVideo.vactive, _p->hwVideo.vtotal,\
			_p->hwVideo.vfreq, _p->hwVideo.refresh_rate, _p->hwVideo.voffset, _p->hwVideo.hoffset );
	seq_printf(m, "\t[%d] Video Format[%s]\n", i++,__csc_to_str(_p->hwVideo.video_format));
	seq_printf(m, "\t[%d] VIC Code[%d] / DeepColorMode[%s]\n", i++,  _p->hwVideo.vicCode, __deepcolor_to_str(_p->hwVideo.deep_color_mode));
	if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value == 0) {
		seq_printf(m, "\t[%d] cvi_vfreq[%d]\n", i++,  _p->cvi_vfreq);
	}	
	seq_printf(m, "[Stable Sync Info]\n");
	seq_printf(m, "\t[%d] TMDS Clk[%010d] / Pixel Clk[%010d]\n", i++, _p->video.tmds_clk, _p->video.pixel_clk);
	seq_printf(m, "\t[%d] DVI[%d] / Interlaced[%d] / Pixel Repetition[%d]\n", i++, _p->video.dvi, _p->video.interlaced, _p->video.pixel_repetition);
	seq_printf(m, "\t[%d] Sig:[%d](%d)x[%d](%d)@[%d]Hz (%d). vo/ho:(%d)/(%d)\n", i++, _p->video.hactive, _p->video.htotal, _p->video.vactive, _p->video.vtotal,\
			_p->video.vfreq, _p->video.refresh_rate, _p->video.voffset, _p->video.hoffset );
	seq_printf(m, "\t[%d] Video Format[%s]\n", i++, __csc_to_str(_p->video.video_format));
	seq_printf(m, "\t[%d] VIC Code[%d] / VIC Vfreq[%d] / DeepColorMode[%s]\n", i++,  _p->video.vicCode, HDMI21_HAL_Rx_Get_VICtoVfreq(_p->video.vicCode) ,__deepcolor_to_str(_p->video.deep_color_mode));
	seq_printf(m, "----------------------------------------------------------------\n");
	seq_printf(m, "[PHY Info]=> PHY Lock[%d] TCS Done[%d] | CR Done[%d] | TCS Status[0x%08x]\n", _p->isPhyLocked, _p->phyTCSDone, _p->phyCrDone, _p->phyTCSState);
	seq_printf(m, "\t[%d] PHY Mode[%s] | FRL CTS Mode[%d] \n", i++, phymode_type_to_str(_p->phyInitiatedMode), _p->isPhyFrlCtsMode);
	seq_printf(m, "\t[%d] TCS Result Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyTCSResult[0], _p->phyTCSResult[1], _p->phyTCSResult[2], _p->phyTCSResult[3]);
	seq_printf(m, "\t[%d] RS  Result Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyRsResult[0], _p->phyRsResult[1], _p->phyRsResult[2], _p->phyRsResult[3]);
	seq_printf(m, "\t[%d] Delta Eye- Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDeltaMinus[0], _p->phyDeltaMinus[1], _p->phyDeltaMinus[2], _p->phyDeltaMinus[3]);
	seq_printf(m, "\t[%d] Delta Eye+ Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			 _p->phyDeltaPlus[0], _p->phyDeltaPlus[1], _p->phyDeltaPlus[2], _p->phyDeltaPlus[3]);
	seq_printf(m, "\t[%d] %s Min Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++, (_p->phyCurrentTMDSExceptionRange >= 0)?"TCS   ":" Delta",\
			_p->phyTCSMin[0], _p->phyTCSMin[1], _p->phyTCSMin[2], _p->phyTCSMin[3]);
	seq_printf(m, "\t[%d] %s Max Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,(_p->phyCurrentTMDSExceptionRange >= 0)?  "TCS   ":" Delta",\
			_p->phyTCSMax[0], _p->phyTCSMax[1], _p->phyTCSMax[2], _p->phyTCSMax[3]);
	seq_printf(m, "\t[%d] DFE A_01   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeA01Result[0], _p->phyDfeA01Result[1], _p->phyDfeA01Result[2], _p->phyDfeA01Result[3]);
	seq_printf(m, "\t[%d] DFE A_11   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeA11Result[0], _p->phyDfeA11Result[1], _p->phyDfeA11Result[2], _p->phyDfeA11Result[3]);
	seq_printf(m, "\t[%d] DFE B_1    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB1Result[0], _p->phyDfeB1Result[1], _p->phyDfeB1Result[2], _p->phyDfeB1Result[3]);	
	seq_printf(m, "\t[%d] DFE B_2    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB2Result[0], _p->phyDfeB2Result[1], _p->phyDfeB2Result[2], _p->phyDfeB2Result[3]);		
	seq_printf(m, "\t[%d] DFE B_3    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB3Result[0], _p->phyDfeB3Result[1], _p->phyDfeB3Result[2], _p->phyDfeB3Result[3]);		
	seq_printf(m, "\t[%d] DFE B_4    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB4Result[0], _p->phyDfeB4Result[1], _p->phyDfeB4Result[2], _p->phyDfeB4Result[3]);		
	seq_printf(m, "\t[%d] DFE B_5    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB5Result[0], _p->phyDfeB5Result[1], _p->phyDfeB5Result[2], _p->phyDfeB5Result[3]);		
	seq_printf(m, "----------------------------------------------------------------\n");
	seq_printf(m, "[PHY Error Count : %d][PHY Error collecting Period : 10^%d BER]\n", _p->phyErrCounter, (12 - gHDMI21RxDevPhyControler[HDMI21__PHY_ERROR_PERIOD_SEL].value));
	seq_printf(m, "\t[%d]  CED Err   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyCEDError[0], _p->phyCEDError[1], _p->phyCEDError[2], _p->phyCEDError[3]);
	seq_printf(m, "\t[%d] TMDS Err   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyTMDSError[0], _p->phyTMDSError[1], _p->phyTMDSError[2], _p->phyTMDSError[3]);
	seq_printf(m, "\t[%d] Recovery   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phySyncRecovery[0], _p->phySyncRecovery[1], _p->phySyncRecovery[2], _p->phySyncRecovery[3]);
	seq_printf(m, "\t[%d] Delta Er   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyDeltaError[0], _p->phyDeltaError[1], _p->phyDeltaError[2], _p->phyDeltaError[3]);
	seq_printf(m, "\t[%d] Is PHY Mode [0~2]? =>[%d] / Exception State[%d] / Eye Measure State[%d]\n", i++, _p->phyCurrentTMDSExceptionRange, _p->phyExceptionState, gHdmi21EyeMeasure[_p->port]); 
	seq_printf(m, "----------------------------------------------------------------\n");
	seq_printf(m, "[Flag Info]\n");
	seq_printf(m, "\t[%d] RestartHPDFlag[%d], HPDInverse[%d], LinkInit[%d], FVA[%d]\n", i++, _p->restartHpdFlagUp, _p->isHPDInverseMode, _p->isLinkInitiated, _p->isFvaMode);
	seq_printf(m, "\t[%d] Change Flag:SCDC[%d] VIDEO[%d] AUDIO[%d] TMDS[%d] HDCP[%d] DCM[%d]\n", i++, _p->scdc_change, _p->video_change,\
			_p->audio_change, _p->tmds_change, _p->hdcp_change, _p->dcm_change);
	seq_printf(m, "\t[%d] is5Vconnected[%d], isHPD[%d], isHDCP22[%d], isHDCP14[%d], MConst[%d] QMSMode[%d]\n", i++, _p->is5Vconnected, _p->isHPD, _p->isHDCP22, _p->isHDCP14, _p->isMConst, _p->isQmsMode);
	seq_printf(m, "\t[%d] hpd_request[%d], fsm_phy_lock[%d], main_thread_init_request[%d]\n", i++, _p->hpd_request, _p->fsm_phy_lock, _p-> main_thread_init_request);
	seq_printf(m, "\t[%d] wasEDID[%d], Disabled[%d], isFreeSync[%d], isAllm[%d], isMute[%d]\n", i++, _p->wasEdidWritten, _p->hdmiDisabled,\
			_p->isFreeSyncMode, _p->isAllmMode, _p->isMute);
	seq_printf(m, "\t[%d] VRR Min[%d]/Max[%d], RepeaterHPD[%d], isSleepMode[%d], DDCMon[%d]\n", i++, _p->vfreq_min, _p->vfreq_max, _p->repeaterHpd, (int)_p->isSleepMode, _p->isDdcMonEnabled);
	seq_printf(m, "[Misc Info]\n");
	seq_printf(m, "\t[%d] Allm Recieved time[%d] / AVMute On Time[%d] / phyFrlSwWaState[%d] / DoviTime[%u]\n", i++, _p->allm_recieve_time, _p->avmute_on_time, _p->phyFrlSwWaState, _p->doviTimeStamp);
	seq_printf(m, "\t[%d] Cable Connected Time[%d] / LocalMuteTimer[%d] / EM VrrRcvTime[%d] / QMSTime[%d] /DolbyVSITime[%u]\n", i++, _p->cable_connect_time, _p->localmutetimer, _p->em_vrr_recieve_time, _p->em_qms_recieve_time, _p->dolbyVsiTimeStamp);
	seq_printf(m, "\t[%d] Stable Time Updated[%d] / RestartHPDStamp[%d] / UI HdrOverride[%d]\n", i++, _p->updateTimingTime, _p->restartHPDTimeStamp, _p->hdrOverRide); 
	seq_printf(m, "\t[%d] 5V connected Time[%d] / Locking Time[%d] / HDCP14Stable Time[%d] / EM VRR VFREQ[%d]\n", i++, _p->connected5Vtime, _p->locking_time, _p->stablehdcp14time, _p->em_vrr_baseRate);
	seq_printf(m, "\t[%d] DSC[%d] / PKTErr[%d] / Current HDCP Auth Version => HDCP%d (csm :%d)\n", i++, _p->isDSC, _p->pktErrStateCnt, HDMI21_HAL_Rx_Get_HDCPStatus(_p->port), _p->hdcp23_csm);
	seq_printf(m, "[SCDC Info]\n");
	seq_printf(m, "\t[%d] Source Version[0x%x] StatusUpdate[%d] CedUpdate[%d] RRTest[%d]\n", i++,\
			_r0.SCDC_SOURCEVERSION, _r0.SCDC_STATUSUPDATE, _r0.SCDC_CEDUPDATE, _r0.SCDC_RRTEST);
	seq_printf(m, "\t[%d] Source TestUpdate[%d] FrlStart[%d] FltUpdate[%d] RsedUpdate[%d] FrlStateSts[%d]\n", i++,\
			_r0.SCDC_SOURCE_TEST_UPDATE, _r0.SCDC_FRL_START,_r0.SCDC_FLT_UPDATE,_r0.SCDC_RSED_UPDATE, _r0.FRL_START_STS);
	seq_printf(m, "\t[%d] ScrambleEn[%d] bitRatio    [%d] ScramStatus [%d] \n", i++,\
			_r1.SCDC_SCRAMB_EN,_r1.SCDC_TMDSBITCLKRATIO,_r1.SCDC_SCRAMB_STATUS);
	seq_printf(m, "\t[%d] RrEnable  [%d] FltNoRetrain[%d] FrlRate     [0x%x]  FfeLevel [0x%x] \n", i++,\
			_r2.SCDC_RRENABLE, _r2.SCDC_FLT_NO_RETRAIN,_r2.SCDC_FRL_RATE,_r2.SCDC_FFE_LEVELS);
	seq_printf(m, "\t[%d] ClkDetect[%d] Ch0~2Locked[%d][%d][%d] LN0~3Locked[%d][%d][%d][%d]\n", i++,\
			_r3.SCDC_CLOCKDETECTED,_r3.SCDC_CH0LOCKED,_r3.SCDC_CH1LOCKED,_r3.SCDC_CH2LOCKED,_r3.SCDC_LN0LOCKED,\
			_r3.SCDC_LN1LOCKED,_r3.SCDC_LN2LOCKED,_r3.SCDC_LN3LOCKED);
	seq_printf(m, "\t[%d] FltLn0~3    LTPReq        [0x%04x]      [0x%04x]      [0x%04x]    [0x%04x]\n", i++,\
			_r3.SCDC_FLT_LN0_LTP_REQ, _r3.SCDC_FLT_LN1_LTP_REQ, _r3.SCDC_FLT_LN2_LTP_REQ, _r3.SCDC_FLT_LN3_LTP_REQ);
	seq_printf(m, "\t[%d] TMDS CED Valid/Error : Ch0[%d][0x%x] Ch1[%d][0x%x] Ch2[%d][0x%x]\n", i++,\
			_r4.SCDC_ERR_DET0_VALID, _r4.SCDC_ERR_DET0, _r4.SCDC_ERR_DET1_VALID, _r4.SCDC_ERR_DET1, _r5.SCDC_ERR_DET2_VALID, _r5.SCDC_ERR_DET2);
	seq_printf(m, "\t[%d] FRL CED Valid/Error :  L0 [%d][0x%x] L1 [%d][0x%x] L2 [%d][0x%x] L3 [%d][0x%x]\n", i++,\
			_r5.SCDC_ERDET_LANE0_VALID,_r5.SCDC_ERDET_LANE0,_r6.SCDC_ERDET_LANE1_VALID,_r6.SCDC_ERDET_LANE1,\
			_r6.SCDC_ERDET_LANE2_VALID,_r6.SCDC_ERDET_LANE2,_r7.SCDC_ERDET_LANE3_VALID,_r7.SCDC_ERDET_LANE3);
	seq_printf(m, "\t[%d] Reed Solomon Corrections Valid/Count : [%d][0x%x]\n", i++,\
			_r7.SCDC_RSFEC_CERDET_VALID, _r7.SCDC_RSFEC_CERDET);
	seq_printf(m, "[LOW POWER INFO]\n");
	seq_printf(m, "\t[%d] V4L2Activated[%d] / Mode[%d] / idleTick[%d]/ThreshTick[%d] / Cnt[%d] / InputChgCnt[%d]\n", i++,\
			_p->isV4l2Activated, _p->lowPowerMode, _p->idleTick,  gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value, _p->lowPowerAccumCnt, gHdmi21InputChgCnt);
	seq_printf(m, "\t[%d] LowPowerTimeStamp [%u] msec / AccumulatedPowerSaveTime [%u] msec\n", i++, \
			_p->lowPowerTimeStamp, _p->accumulatedLowPowerTime);
	seq_printf(m, "\t[%d] QMS BaseRate[%d] / QMS Next TFR[idx:%d][%s]\n", i++, _p->em_qms_baseRate, _p->em_qms_tfr, __tfr_to_str(_p->em_qms_tfr));
	seq_printf(m, "\t[%d] FilterSelSwWaCnt[%d] / ConsecutiveFilterSelSwWa[%d]\n", i++, _p->filterSelSwWaCnt, _p->consecutiveFilStuckCnt);
	seq_printf(m, "\t[%d] warmMode[%d], isPqeSuspend[%d], isFrl480pDcmForceSwWa[%d]\n", i++, gHdmi21WarmMode, _p->isPqeSuspend, _p->isFrl480pDcmForceSwWa);
	
	return;
}

/* DBG function */
void HDMI21_HAL_Rx_PROC_PrintIRQ(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i;

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	_p = &gHDMI21RxHandler[port];

	for(i=0;i<HDMI21_ISR_MAXNUM;i++){
			seq_printf(m, "Port [%d] : ISR TYPE[%02d] [%s] = [%d]\n", _p->port, i, __isr_type_to_str(i), _p->isr_count0[i]);  
	}

	return;
}

/* DBG function */
void HDMI21_HAL_Rx_PROC_PrintSavedEDID(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int size = HDMI21_HAL_SIZE_OF_EDID;
	int i = 0;
	UINT8 edid_data[HDMI21_HAL_SIZE_OF_EDID] = {0,};

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	_p = &gHDMI21RxHandler[port];

	memcpy((void *)&edid_data, (void *)&_p->edidData, HDMI21_HAL_SIZE_OF_EDID);

	seq_printf(m, "=========================================================================================================================\n");
	seq_printf(m, "[0x00] |  [0x00] [0x01] [0x02] [0x03] [0x04] [0x05] [0x06] [0x07] [0x08] [0x09] [0x0A] [0x0B] [0x0C] [0x0D] [0x0E] [0x0F]\n");
	seq_printf(m, "=========================================================================================================================\n");

	for (i = 0; i < (size/16); i++) {
		if((i%8) == 0){
			seq_printf(m, "-------------------------------------------------------------------------------------------------------------------------\n");
			seq_printf(m, "EDID Block %d, Bytes %d-%d [%02xH-%02xH]\n",  i/8, (128*(i/8)), (128*((i/8)+1) -1), (128*(i/8)), (128*((i/8)+1) -1));
			seq_printf(m, "-------------------------------------------------------------------------------------------------------------------------\n");
		}
		seq_printf(m, "[0x%02x] | [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x]\n",\
				i, edid_data[(i*16) + 0], edid_data[(i*16) + 1], edid_data[(i*16) + 2], edid_data[(i*16) + 3], edid_data[(i*16) + 4],\
				edid_data[(i*16) + 5], edid_data[(i*16) + 6], edid_data[(i*16) + 7], edid_data[(i*16) + 8],\
				edid_data[(i*16) + 9], edid_data[(i*16) + 10],edid_data[(i*16) + 11], edid_data[(i*16) + 12],\
				edid_data[(i*16) + 13], edid_data[(i*16) + 14],edid_data[(i*16) + 15]);
	}
}

int HDMI21_HAL_Rx_Get_Check5VLevelInfo(int port, int *pValue, int isReal)
{
	int ret = 0;
	UINT32 reg5Vvalue = 0;
	UINT32 currentTime;
	UINT32 totalDownTime = gHDMI21RxDevVideoControler[HDMI21__TIME_OF_HPD_DOWN_ON_RESTART_HPD].value;


	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			*pValue = 0;
			break;
		}


		if((((gHDMI21RxDevVideoControler[HDMI21__FORCE_5V_UP].value >> port) & 0x1) > 0) && (isReal <=0)){
			*pValue = 1;
			ret = RET_OK;

			HDMI21_LINE_DBG(2606, "DBG %d : 5V force UP\n",port);	
			break;
		}

		if((((gHDMI21RxDevVideoControler[HDMI21__FORCE_5V_DOWN].value >> port) & 0x1) > 0) && (isReal <=0)){
			*pValue = 0;
			ret = RET_OK;

			HDMI21_LINE_DBG(2606, "DBG %d : 5V force DOWN\n",port);	
			break;
		}
		
		if((gHDMI21RxHandler[port].zombieMode > 0) && (isReal <= 0)) {
		
			*pValue = 0;
			ret = RET_OK;

			HDMI21_LINE_DBG(2606, "DBG %d : 5V force DOWN due to Zombie Mode activated\n",port);	
			break;
		}

		/* Read Reg */
		reg5Vvalue= gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_5V_DETECT);
		reg5Vvalue &= HDMI21_TOP_FIELD_I_REG_HDMI5V_STATUS;

		/* Normalize Value */
		if(reg5Vvalue == 0x0) 	{	reg5Vvalue = 0; }
		else 					{	reg5Vvalue = 1;	}

		if(isReal > 0 ){
			*pValue = (int)reg5Vvalue;
			ret = RET_OK;
			break;
		}
		else { /* 2020/09/21 : If case added for isReal Exception for Repeater models */

			if(gHDMI21RxHandler[port].isSleepMode > 0) {
				HDMI21_LINE_DBG(2606, "DBG %d : Currently in Sleep Mode\n",port);	
				*pValue = 0;
				ret = RET_OK;
				break;
			}
			else{
				if(gHDMI21RxHandler[port].gWasHDCP22Written > 0) {
					if((HDMI21_HDCP23_Module_Get_IsRepeater() > 0) && (gHDMI21RxHandler[port].repeaterHpd == 0)) {
						HDMI21_LINE_DBG(2606, "DBG %d : HDCP Repeater HPD value is zero\n",port);	
						*pValue = 0;
						ret = RET_OK;
						break;
					}
				}
			}
		}

		/* Update Restart HPD flag based on time stamps */
		currentTime = jiffies_to_msecs(jiffies);

		if((currentTime - gHDMI21RxHandler[port].restartHPDTimeStamp <= totalDownTime)\
				&& (gHDMI21RxHandler[port].restartHpdFlagUp == true)){

			HDMI21_LINE_DBG(1450, "DBG %d : Force 5V down to make HPD/Rxsense Down from MW request. Stamp[%d]/CurrTime[%d]\n",port, gHDMI21RxHandler[port].restartHPDTimeStamp, currentTime);	
		}
		else{
			if(gHDMI21RxHandler[port].restartHpdFlagUp == true){
				if((currentTime - gHDMI21RxHandler[port].restartHPDTimeStamp > totalDownTime)){
					HDMI20_INFO("Notice %d : Finish Force 5V down for HPD/Rxsense Down. Stamp[%d]/CurrTime[%d]\n",port,  gHDMI21RxHandler[port].restartHPDTimeStamp, currentTime);
					gHDMI21RxHandler[port].restartHpdFlagUp  = false;

				}
				else{
					HDMI20_ERROR("ERROR %d : Critical! Un-expected state!!! Please contact won.hur@lge.com for this issue!!!!!!\n", port);
					HDMI20_ERROR("ERROR %d : currTime[%d]/stamp[%d]/flag[%d]/5V[%d]\n", port, currentTime, gHDMI21RxHandler[port].restartHPDTimeStamp, gHDMI21RxHandler[port].restartHpdFlagUp, reg5Vvalue);
				}
			}
		}


		/* Return differently based on time stamps */
		if(gHDMI21RxHandler[port].hdmiDisabled > 0){
			HDMI21_LINE_DBG(1450, "DBG %d : HDMI Disabled\n", port);	

			*pValue = 0;
		}
		else{
			if(gHDMI21RxHandler[port].restartHpdFlagUp == true){
				*pValue = 0;
			}
			else{
				*pValue = reg5Vvalue;
			}
		}

		ret = RET_OK;
	} while(0);

	HDMI21_LINE_DBG(1451, "DBG %d : 5V Level => [%s]\n",port, *pValue?"HIGH":"LOW");	
	if(isReal > 0) {
		HDMI21_LINE_DBG(2609, "DBG %d : Real 5V Level => [%s]\n",port, *pValue?"HIGH":"LOW");	
	}

	return ret;
}


/* IOCTL */
int HDMI21_HAL_Rx_Set_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	UINT32 edidData[(HDMI21_HAL_SIZE_OF_EDID >> 2)];
	int i;
	UINT32 addr = 0;
	UINT32 dbgData;

	do{
		HDMI20_INFO("NOTI %d : Set Internal EDID from MW\n", port);

		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size > HDMI21_HAL_SIZE_OF_EDID){
			HDMI20_ERROR("Error! Size is over limie!([%d] < [%d]) \n", HDMI21_HAL_SIZE_OF_EDID, size);
			break;
		}

		if (size%8) {
			HDMI20_ERROR("Error! Does not allow non-8byte aligned mem access. Size[%d]\n", size);
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		memset((void *)&edidData, 0, HDMI21_HAL_SIZE_OF_EDID);

		if(isInternalCall > 0){
			memcpy((void *)&edidData, (void *)pData, size);
		}
		else{
			if( copy_from_user(&edidData, (void __user *)pData, size)){
				HDMI20_ERROR("Cannot copy EDID data structure from user\n");
				break;
			}
		}

		/* Store EDID data from above */
		memcpy((void *)&gHDMI21RxHandler[port].edidData, (void *)edidData, HDMI21_HAL_SIZE_OF_EDID);


		for(i=0; i<(HDMI21_HAL_SIZE_OF_EDID >> 2); i++){
			gHDMI21RxHandler[port].aled_write(addr, edidData[i]);

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1016){
				dbgData = gHDMI21RxHandler[port].aled_read(addr);
				HDMI20_DBG("Internal EDID[%d] : BYTE [%d] =  [0x%x]<=[0x%08x] (0x%08x)\n", port, i, addr, edidData[i],dbgData);
			}
			addr += 4;
		}

		/* Save history */
		gHDMI21RxHandler[port].wasEdidWritten = true;

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_HAL_Rx_Set_EDID_Enable(UINT8 port, BOOLEAN enable)
{
	int ret = RET_ERROR;
	UINT32 __data = 0;

	HDMI20_INFO("Notice %d : Internal EDID is [%s]\n", port, enable?"Enabled":"Disabled");
 
 	do{
 
		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Set Flag */
		if(enable == 0) {
			gHDMI21RxHandler[port].disableAledEdid = 1;
		}
		else {
			gHDMI21RxHandler[port].disableAledEdid = 0;
		}	


		if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
			__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xFF0006); // M23: 0xC6180800, O24: 0xC8821000
			
			HDMI21_REG_RD(0xCA36000C, __data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn), O26:CRG_SUB > EDID(woc_syn)

			/* Set value */
			//__data = 0x00FF0006; 	/* LG TapBook Issue */
			if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
			else __data &= (~0x4);
			
			if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
			else __data &= (~0x10);

			if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x40;
			else __data &= (~0x40);

			if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x100;
			else __data &= (~0x100);

			HDMI21_REG_WR(0xCA36000C, __data);	
			
		}else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
			__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xFF0006); // M23: 0xC6180800, O24: 0xC8821000
			
			HDMI21_REG_RD(0xC883000C, __data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn)

			/* Set value */
			//__data = 0x00FF0006; 	/* LG TapBook Issue */
			if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
			else __data &= (~0x4);
			
			if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
			else __data &= (~0x10);

			if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x40;
			else __data &= (~0x40);

			if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x100;
			else __data &= (~0x100);

			HDMI21_REG_WR(0xC883000C, __data);	
			
		}else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
			__HDMI21_HAL_Rx_ALED_TOP_Write(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xF0006); // M23: 0xC6180800, O24: 0xC8821000
			__HDMI21_HAL_Rx_ALED_TOP_Write_P23(HDMI21_ALED_TOP_REG_AD_APB_5V_SEL, 0xF0006); // M23: 0xF3100800
			
			HDMI21_REG_RD(0xC619000C, __data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn)
			if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
			else __data &= (~0x4);
			
			if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
			else __data &= (~0x10);
			HDMI21_REG_WR(0xC619000C, __data);
			
			HDMI21_REG_RD(0xF311000C, __data);
			if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x4;
			else __data &= (~0x4);

			if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x10;
			else __data &= (~0x10);
			HDMI21_REG_WR(0xF311000C, __data);
		}

		HDMI20_INFO("Notice %d :  EDID Enable reg value 0xC8821050 > [0x%x],  0xC883000C > [0x%x]\n", port, __HDMI21_HAL_Rx_ALED_TOP_Read(0x50), __data);
	
		/* Set APB */
		//__HDMI21_HAL_Rx_ALED_TOP_Write(0x50, __data);

		ret = RET_OK;
 	} while(0);

	return ret;

}


/* IOCTL */
int HDMI21_HAL_Rx_Get_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall)
{
	int i;
	int ret = RET_ERROR;
	UINT32 edidData[(HDMI21_HAL_SIZE_OF_EDID >> 2)];
	UINT32 addr;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size > HDMI21_HAL_SIZE_OF_EDID){
			HDMI20_ERROR("Error! Size is over limie!([%d] < [%d]) \n", HDMI21_HAL_SIZE_OF_EDID, size);
			break;
		}

		if (size%8) {
			HDMI20_ERROR("Error! Does not allow non-8byte aligned mem access. Size[%d]\n", size);
		}


		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		addr = 	0x0;

		for(i=0; i<(HDMI21_HAL_SIZE_OF_EDID >>2); i++){
			edidData[i] = gHDMI21RxHandler[port].aled_read(addr);

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1016){
				HDMI20_DBG("Internal EDID[%d] : BYTE [%d] -- [0x%x]<=[0x%08x]\n", port, i, addr, edidData[i]);
			}
			addr += 4;
		}

		if(isInternalCall > 0){
			memcpy((UINT8 *)pData, (UINT8 *)&edidData, size);
		}
		else{
			ret = copy_to_user((UINT8 *)pData, (UINT8 *)&edidData, size);
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "Internal EDID", port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI21_HAL_Rx_Set_HDCP14(UINT8 port, UINT32 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	int i;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_HDCP14_DATA_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_HDCP14_DATA_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* TV lab wants us to set HDCP1.4 keys/history for all ports even it was called for only a specific port */
		for(i=0;i<g_hdmi20_number_of_ports;i++){
			if(isInternalCall > 0){
				memcpy((void *)&gHDMI21RxHandler[i].hdcp, (void *)pData, sizeof( LX_HDMI20_HDCP14_DATA_T));
			}
			else{
				if( copy_from_user((void *)&gHDMI21RxHandler[i].hdcp, (void __user *)pData, sizeof( LX_HDMI20_HDCP14_DATA_T))){
					HDMI20_ERROR("Error[%d] : Cannot copy HDCP1.4 data structure from user\n", i);
					break;
				}
			}

			/* Turn off HDCP1.4 bypass mode (double check) */
			gHDMI21RxHandler[i].gWasHDCP14Written = 1;

			HDMI20_INFO("Info[%d] : Writing HDCP1.4 key(%s) - KSV[0x%x][0x%x]\n",\
					i, isInternalCall?"Internal":"External", gHDMI21RxHandler[i].hdcp.bksv[0], gHDMI21RxHandler[i].hdcp.bksv[1]);
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_HAL_ConnectCable(int port, int bOnOff)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_OK;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return RET_ERROR;
	}

	if(gHDMI21Thread.stamp == 0){
		HDMI20_WARN("Warning %d : Connect Cable was called without MAIN THREAD operation\n", port);
		return RET_ERROR;
	}

	if(gHDMI21RxHandler[port].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return RET_ERROR;
	}

	/* Get Handler */
	_p = &gHDMI21RxHandler[port];

	/* Repeater SW WA */
	if(HDMI21_HDCP23_Module_Get_IsRepeater() > 0) {
		HDMI21_HDCP23_Module_Set_RxId(&gHDMI21RepeaterRxID[0][0], 5, gHDMI21RepeaterCount, gHDMI21RepeaterDepth);
	}

	/* Clear HDMI Host Diagnosis Error */
	__HDMI21_HAL_Rx_Set_ClearHDMIHostError(_p, LX_HDMI20_ERROR_MAXNUM);
	/* Clear Link Initiated Flag */
	gHDMI21RxHandler[port].isLinkInitiated = 0;
	/* Clear Handler Data : This will clear Stable Timing Info as well */
	__HDMI21_HAL_Rx_Set_ResetHandlerData(_p, 1);


	/* 2020/06/29 : Reset Lowpower Mode state */
	gHDMI21RxHandler[port].lowPowerMode = HDMI21_HAL_POWER_NORMAL;

	/* SW WA for EARC */
	if(port == 2) {
		if(lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)){
			gHDMI21RxHandler[2].link_write(0x5304, gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_EARC_INTVEC].value);
		}
		else {
			gHDMI21RxHandler[0].link_write(0x5304, gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_EARC_INTVEC].value);
		}
	}

	/* Set VFreq counter ref clock */
	if((_p->top_read(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK)& 0xFFFF) != 0x1E0){
		_p->top_write(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK, 0x1E0);
	}

	if(bOnOff){
		HDMI20_INFO("HDMI2.0 Port[%d] Cable Connect sequence. \n", port);

		/* Audio Mute */
		HDMI21_HAL_Rx_Set_AudioReset(_p->port);
		_p->isAudioMute = 1;
		_p->isAudioMuteControl = 1;
		_p->audioIrqFifoErrCnt = 0;

		gHDMI21RxHandler[port].cable_connect_time = jiffies_to_msecs(jiffies);
		gHDMI21RxHandler[port].is5Vconnected = 1;
		gHDMI21RxHandler[port].main_thread_init_request = 1;
	}
	else{
		HDMI20_INFO("HDMI2.0 Port[%d] Cable Dis-connect sequence. \n", port);

		gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_TIME].value = gHDMI21RxDevVideoControler[HDMI21__LOCAL_MUTE_HOLD_INIT_TIME].value;
		HDMI21_HAL_Rx_Set_LocalVideoMute(port, 1, 0);

		/* Audio Mute */
		HDMI21_HAL_Rx_Set_AudioReset(port);
		HDMI21_Rx_Audio_Path_InthwUnmask(port);

		/* Set HPD Low */
		__HDMI21_HAL_Rx_Set_HPD(port ,0, 1);

		/* Link Reset */
		HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_MAIN_HARD_RESET_VAL].value);

		/* Set SCDC HPDLOW/STANDBY flag, Set Low SCDC POWERPROVIDED Flag */
		HDMI21_SCDC_Rx_Set_ScdcConfig(_p, 0);

	}

	return ret;
}


int HDMI21_HAL_Rx_Set_RestartHPD(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 totalDownTime = gHDMI21RxDevVideoControler[HDMI21__TIME_OF_HPD_DOWN_ON_RESTART_HPD].value;

	HDMI20_INFO("Notice %d : Restart HPD for [%d] msec\n", port, totalDownTime);

	do{
		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(gHDMI21RxHandler[port].restartHpdFlagUp == true){
			HDMI20_WARN("Warning %d :  Restart HPD is in progress. This will increase HPD low time for amount of unit time(%d)\n", port, totalDownTime);
		}

		#if 0
		HDMI21_HAL_ConnectCable(port, OFF);
		#endif

		gHDMI21RxHandler[port].restartHpdFlagUp = true;
		gHDMI21RxHandler[port].restartHPDTimeStamp = jiffies_to_msecs(jiffies);

		/* 2020/06/29 : Set Low Power flag to normal */
		gHDMI21RxHandler[port].lowPowerMode = HDMI21_HAL_POWER_NORMAL;

		ret = RET_OK;
	} while(0);

	return ret;

}

/* DBG function */
int HDMI21_HAL_Rx_DBG_Tool(int type, UINT8 port, int data)
{
	int i,y;
	UINT32 __d;
	char *pData;
	int size = 0;
	int idx = 0;

	HDMI21_HAL_RX_DEVICE_DATA *_p;

	if(port> g_hdmi20_number_of_ports){
		HDMI20_ERROR("Wrong Port selected[%d]\n", port);
		return RET_ERROR;
	}

	/* Dev Handler */
	_p = &gHDMI21RxHandler[port];

	/* Type 80000 and over is used for special purpose */
	if(type >= 80000) {
		idx = type - 80000;

		if(idx >= HDMI21_DSC_F20_MAXNUM){
			printk("Unknown type[%d]\n", type);
		}
		else {
			if(gFecDbgRegOvrRide > 0) {
				gFecDbgDataSet[idx] = data;
				printk("DSC/FEC override idx[%d] : Addr[0x%08x] <= [0x%08x]\n", idx, gF20ChipIdData.f20Data[idx].addr, gFecDbgDataSet[idx]);
			}
			else {
				printk("DSC/FEC override menu can only be adjusted once override mode is enabled\n");
			}
		}
	}

	switch(type)
	{
		case 0:
			__HDMI21_HAL_Rx_DBG_PrintVideo(port);
			break;
		case 1:
			__HDMI21_HAL_Rx_DBG_PrintPhySetting(&gHDMI21RxHandler[port]);
			break;
		case 2:			__HDMI21_HAL_Rx_DBG_PrintIRQ(port);
						break;
		case 3:
			__HDMI21_HAL_Rx_DBG_PrintSavedEDID(&gHDMI21RxHandler[port]);
			break;
		case 4:
			__HDMI21_HAL_Rx_Get_PrintDscCvtemPpsData(&gHDMI21RxHandler[port]);
			break;
		case 5:
			HDMI21_HAL_Rx_Set_Initialize(NULL, 0, 1);
			break;
		case 6:
			y = 0;
			for(i=0;i<sizeof(HDMI21_HAL_DSC_PPS_O20A0_T);i=i+4)
			{
				__d = (UINT32)(*((UINT32 *)&gHDMI21RxHandler[port].pps + y));
				printk(" PPS[%d]<=[0x%08x]\n", y, __d);
				y++;
			}
			break;
		case 7 :
			size = data;
			pData = (char *)kmalloc(size, GFP_KERNEL);
			if(pData == NULL) {
				printk("Failed to Kmalloc for ESM LogDump[Size : %d]\n", size);
				break;
			}
			printk("[Execute ESM_LogDump with max log size %d bytes]\n", size);
			HDMI21_HDCP23_Module_SetLogDump(pData, &size);
			printk("[ESM Log Start : Recieved log of %d bytes]\n", size);
			for(i=0;i<size;i++) {
				printk("%c\n", pData[i]);
			}
			printk("[ESM Log END]\n");
			kfree(pData);
			break;
		case 8:
			{	
				if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
					HDMI21_REG_RD(0XCC500000, __d);
					printk(" 0XCC500000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500400, __d);
					printk(" 0XCC500400= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500410, __d);
					printk(" 0XCC500410= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500010, __d);
					printk(" 0XCC500010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500100, __d);
					printk(" 0XCC500100= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500108, __d);
					printk(" 0XCC500108= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500110, __d);
					printk(" 0XCC500110= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500114, __d);
					printk(" 0XCC500114= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC500300, __d);
					printk(" 0XCC500300= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505010, __d);
					printk(" 0XCC505010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505000, __d);
					printk(" 0XCC505000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505010, __d);
					printk(" 0XCC505010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505014, __d);
					printk(" 0XCC505014= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505000, __d);
					printk(" 0XCC505000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505030, __d);
					printk(" 0XCC505030= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505034, __d);
					printk(" 0XCC505034= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505038, __d);
					printk(" 0XCC505038= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC50503C, __d);
					printk(" 0XCC50503C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505040, __d);
					printk(" 0XCC505040= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505044, __d);
					printk(" 0XCC505044= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505048, __d);
					printk(" 0XCC505048= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC50504C, __d);
					printk(" 0XCC50504C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505050, __d);
					printk(" 0XCC505050= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505054, __d);
					printk(" 0XCC505054= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505058, __d);
					printk(" 0XCC505058= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC50505C, __d);
					printk(" 0XCC50505C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505060, __d);
					printk(" 0XCC505060= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505064, __d);
					printk(" 0XCC505064= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XCC505068, __d);
					printk(" 0XCC505068= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC50506c, __d);
					printk(" 0XCC50506C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505070, __d);
					printk(" 0XCC505070= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505074, __d);
					printk(" 0XCC505074= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505078, __d);
					printk(" 0XCC505078= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC50507c, __d);
					printk(" 0XCC50507C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505080, __d);
					printk(" 0XCC505080= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505084, __d);
					printk(" 0XCC505084= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505088, __d);
					printk(" 0XCC505088= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC50508c, __d);
					printk(" 0XCC50508C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505090, __d);
					printk(" 0XCC505090= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505094, __d);
					printk(" 0XCC505094= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC505098, __d);
					printk(" 0XCC505098= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC500020, __d);
					printk(" 0XCC500020= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC500000, __d);
					printk(" 0XCC500000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xCC500440, __d);
					printk(" 0XCC500440= [0x%08x]\n", __d);


				}
				else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
					HDMI21_REG_RD(0XC8CE0000, __d);
					printk(" 0XC8CE0000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0400, __d);
					printk(" 0XC8CE0400= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0410, __d);
					printk(" 0XC8CE0410= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0010, __d);
					printk(" 0XC8CE0010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0100, __d);
					printk(" 0XC8CE0100= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0108, __d);
					printk(" 0XC8CE0108= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0110, __d);
					printk(" 0XC8CE0110= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0114, __d);
					printk(" 0XC8CE0114= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE0300, __d);
					printk(" 0XC8CE0300= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5010, __d);
					printk(" 0XC8CE5010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5000, __d);
					printk(" 0XC8CE5000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5010, __d);
					printk(" 0XC8CE5010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5014, __d);
					printk(" 0XC8CE5014= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5000, __d);
					printk(" 0XC8CE5000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5030, __d);
					printk(" 0XC8CE5030= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5034, __d);
					printk(" 0XC8CE5034= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5038, __d);
					printk(" 0XC8CE5038= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE503C, __d);
					printk(" 0XC8CE503C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5040, __d);
					printk(" 0XC8CE5040= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5044, __d);
					printk(" 0XC8CE5044= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5048, __d);
					printk(" 0XC8CE5048= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE504C, __d);
					printk(" 0XC8CE504C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5050, __d);
					printk(" 0XC8CE5050= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5054, __d);
					printk(" 0XC8CE5054= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5058, __d);
					printk(" 0XC8CE5058= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE505C, __d);
					printk(" 0XC8CE505C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5060, __d);
					printk(" 0XC8CE5060= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5064, __d);
					printk(" 0XC8CE5064= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC8CE5068, __d);
					printk(" 0XC8CE5068= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE506c, __d);
					printk(" 0XC8CE506C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5070, __d);
					printk(" 0XC8CE5070= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5074, __d);
					printk(" 0XC8CE5074= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5078, __d);
					printk(" 0XC8CE5078= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE507c, __d);
					printk(" 0XC8CE507C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5080, __d);
					printk(" 0XC8CE5080= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5084, __d);
					printk(" 0XC8CE5084= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5088, __d);
					printk(" 0XC8CE5088= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE508c, __d);
					printk(" 0XC8CE508C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5090, __d);
					printk(" 0XC8CE5090= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5094, __d);
					printk(" 0XC8CE5094= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE5098, __d);
					printk(" 0XC8CE5098= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE0020, __d);
					printk(" 0XC8CE0020= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE0000, __d);
					printk(" 0XC8CE0000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC8CE0440, __d);
					printk(" 0XC8CE0440= [0x%08x]\n", __d);


				}
				else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
					/* Not Yet */	
				}
				else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
					HDMI21_REG_RD(0XC88A0000, __d);
					printk(" 0XC88A0000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0400, __d);
					printk(" 0XC88A0400= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0410, __d);
					printk(" 0XC88A0410= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0010, __d);
					printk(" 0XC88A0010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0100, __d);
					printk(" 0XC88A0100= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0108, __d);
					printk(" 0XC88A0108= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0110, __d);
					printk(" 0XC88A0110= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0114, __d);
					printk(" 0XC88A0114= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A0300, __d);
					printk(" 0XC88A0300= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5010, __d);
					printk(" 0XC88A5010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5000, __d);
					printk(" 0XC88A5000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5010, __d);
					printk(" 0XC88A5010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5014, __d);
					printk(" 0XC88A5014= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5000, __d);
					printk(" 0XC88A5000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5030, __d);
					printk(" 0XC88A5030= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5034, __d);
					printk(" 0XC88A5034= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5038, __d);
					printk(" 0XC88A5038= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A503C, __d);
					printk(" 0XC88A503C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5040, __d);
					printk(" 0XC88A5040= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5044, __d);
					printk(" 0XC88A5044= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5048, __d);
					printk(" 0XC88A5048= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A504C, __d);
					printk(" 0XC88A504C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5050, __d);
					printk(" 0XC88A5050= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5054, __d);
					printk(" 0XC88A5054= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5058, __d);
					printk(" 0XC88A5058= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A505C, __d);
					printk(" 0XC88A505C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5060, __d);
					printk(" 0XC88A5060= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5064, __d);
					printk(" 0XC88A5064= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC88A5068, __d);
					printk(" 0XC88A5068= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A506c, __d);
					printk(" 0XC88A506C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5070, __d);
					printk(" 0XC88A5070= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5074, __d);
					printk(" 0XC88A5074= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5078, __d);
					printk(" 0XC88A5078= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A507c, __d);
					printk(" 0XC88A507C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5080, __d);
					printk(" 0XC88A5080= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5084, __d);
					printk(" 0XC88A5084= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5088, __d);
					printk(" 0XC88A5088= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A508c, __d);
					printk(" 0XC88A508C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5090, __d);
					printk(" 0XC88A5090= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5094, __d);
					printk(" 0XC88A5094= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A5098, __d);
					printk(" 0XC88A5098= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A0020, __d);
					printk(" 0XC88A0020= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A0000, __d);
					printk(" 0XC88A0000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC88A0440, __d);
					printk(" 0XC88A0440= [0x%08x]\n", __d);
				}
				else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
					HDMI21_REG_RD(0XC9090000, __d);
					printk(" 0XC9090000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090400, __d);
					printk(" 0XC9090400= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090410, __d);
					printk(" 0XC9090410= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090010, __d);
					printk(" 0XC9090010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090100, __d);
					printk(" 0XC9090100= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090108, __d);
					printk(" 0XC9090108= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090110, __d);
					printk(" 0XC9090110= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090114, __d);
					printk(" 0XC9090114= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9090300, __d);
					printk(" 0XC9090300= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095010, __d);
					printk(" 0XC9095010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095000, __d);
					printk(" 0XC9095000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095010, __d);
					printk(" 0XC9095010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095014, __d);
					printk(" 0XC9095014= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095000, __d);
					printk(" 0XC9095000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095030, __d);
					printk(" 0XC9095030= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095034, __d);
					printk(" 0XC9095034= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095038, __d);
					printk(" 0XC9095038= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC909503C, __d);
					printk(" 0XC909503C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095040, __d);
					printk(" 0XC9095040= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095044, __d);
					printk(" 0XC9095044= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095048, __d);
					printk(" 0XC9095048= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC909504C, __d);
					printk(" 0XC909504C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095050, __d);
					printk(" 0XC9095050= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095054, __d);
					printk(" 0XC9095054= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095058, __d);
					printk(" 0XC9095058= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC909505C, __d);
					printk(" 0XC909505C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095060, __d);
					printk(" 0XC9095060= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095064, __d);
					printk(" 0XC9095064= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9095068, __d);
					printk(" 0XC9095068= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc909506c, __d);
					printk(" 0XC909506C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095070, __d);
					printk(" 0XC9095070= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095074, __d);
					printk(" 0XC9095074= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095078, __d);
					printk(" 0XC9095078= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc909507c, __d);
					printk(" 0XC909507C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095080, __d);
					printk(" 0XC9095080= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095084, __d);
					printk(" 0XC9095084= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095088, __d);
					printk(" 0XC9095088= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc909508c, __d);
					printk(" 0XC909508C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095090, __d);
					printk(" 0XC9095090= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095094, __d);
					printk(" 0XC9095094= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9095098, __d);
					printk(" 0XC9095098= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9090020, __d);
					printk(" 0XC9090020= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9090000, __d);
					printk(" 0XC9090000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xc9090440, __d);
					printk(" 0XC9090440= [0x%08x]\n", __d);
				}
				else {
					HDMI21_REG_RD(0XC9060000, __d);
					printk(" 0XC9060000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060400, __d);
					printk(" 0XC9060400= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060410, __d);
					printk(" 0XC9060410= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060010, __d);
					printk(" 0XC9060010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060100, __d);
					printk(" 0XC9060100= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060108, __d);
					printk(" 0XC9060108= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060110, __d);
					printk(" 0XC9060110= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060114, __d);
					printk(" 0XC9060114= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9060300, __d);
					printk(" 0XC9060300= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065010, __d);
					printk(" 0XC9065010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065000, __d);
					printk(" 0XC9065000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065010, __d);
					printk(" 0XC9065010= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065014, __d);
					printk(" 0XC9065014= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065000, __d);
					printk(" 0XC9065000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065030, __d);
					printk(" 0XC9065030= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065034, __d);
					printk(" 0XC9065034= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065038, __d);
					printk(" 0XC9065038= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC906503C, __d);
					printk(" 0XC906503C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065040, __d);
					printk(" 0XC9065040= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065044, __d);
					printk(" 0XC9065044= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065048, __d);
					printk(" 0XC9065048= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC906504C, __d);
					printk(" 0XC906504C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065050, __d);
					printk(" 0XC9065050= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065054, __d);
					printk(" 0XC9065054= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065058, __d);
					printk(" 0XC9065058= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC906505C, __d);
					printk(" 0XC906505C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065060, __d);
					printk(" 0XC9065060= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065064, __d);
					printk(" 0XC9065064= [0x%08x]\n", __d);

					HDMI21_REG_RD(0XC9065068, __d);
					printk(" 0XC9065068= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC906506c, __d);
					printk(" 0XC906506C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065070, __d);
					printk(" 0XC9065070= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065074, __d);
					printk(" 0XC9065074= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065078, __d);
					printk(" 0XC9065078= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC906507c, __d);
					printk(" 0XC906507C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065080, __d);
					printk(" 0XC9065080= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065084, __d);
					printk(" 0XC9065084= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065088, __d);
					printk(" 0XC9065088= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC906508c, __d);
					printk(" 0XC906508C= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065090, __d);
					printk(" 0XC9065090= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065094, __d);
					printk(" 0XC9065094= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9065098, __d);
					printk(" 0XC9065098= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9060020, __d);
					printk(" 0XC9060020= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9060000, __d);
					printk(" 0XC9060000= [0x%08x]\n", __d);

					HDMI21_REG_RD(0xC9060440, __d);
					printk(" 0XC9060440= [0x%08x]\n", __d);
				}
				break;
			}
		case 10:
			__HDMI21_HAL_Rx_Set_ResetLink(&gHDMI21RxHandler[port], 1);
			break;
		case 11:
			HDMI21_MISC_Rx_Set_ResetCore(&gHDMI21RxHandler[port], data);
			break;
		case 12:
			printk("KWARP_HDMI20_Open() = [%d]\n", KWARP_HDMI20_Open());
			printk("KWARP_HDMI20_RX_HDCP14_TestMode(0) = [%d]\n", KWARP_HDMI20_RX_HDCP14_TestMode(data));
			break;
		case 13 :
			printk("gHdmi21InputChgCnt =[%d]\n", gHdmi21InputChgCnt);	
			break;
		case 14:
			gHdmi21InputChgCnt = data;
			break;
		case 15:
			HDMI21_HAL_Rx_Set_V4l2PortActivate(port, data);
			break;		
		case 16:
			printk("gLowPowerState1Tick=[%d] gLowPowerState2Tick=[%d] gLowPowerState3Tick=[%d] gLowPowerState4Tick=[%d] gLowPowerState5Tick=[%d]\n", gLowPowerState1Tick, gLowPowerState2Tick, gLowPowerState3Tick, gLowPowerState4Tick, gLowPowerState5Tick);
			break;
		case 17:
			gLowPowerState1Tick = data;
			break;
		case 18:
			gLowPowerState2Tick = data;
			break;
		case 19:
			printk("HDMI21_HDCP23_Module_Get_ContentType = [%d]\n",  HDMI21_HDCP23_Module_Get_ContentType(port));
			break;
		case 20:
			HDMI21_HAL_Rx_Set_Audio_Configure(port, __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(&gHDMI21RxHandler[port]));
			break;
		case 21:
			if(gHDMI21RxHandler[port].is5Vconnected > 0) {
				HDMI20_INFO("Cable Must be desserted for re calibration\n");
				break;
			}

			/* 2020/06/08 : SWWA for E60B0, JW Choi, DK KIM */
			/* EQ CAL before HPD UP */
			HDMI20_INFO("SWWA : EQ CAL Start for Port[%d]\n", i);	
			/* PHY PDB HIGH */
			gHDMI21RxHandler[port].top_write(0xB0, 0x21000000);


			/* Flag needs to be UP for PHY APB control API */
			gHDMI21RxHandler[port].is5Vconnected = 1;
			HDMI21_PHY_Rx_Set_ControlPhyPdb(port, 1);

			HDMI21_PHY_Rx_Set_Initiate_Phy(port,  HDMI21_HAL_PHY_INITIATED_3G);
			HDMI21_PHY_Rx_Set_3g6gMode(port, gHDMI21RxDevVideoControler[HDMI21__VIDEO_AUTO_SCRAMBLE_FOR_HDMI20].value,\
					HDMI21_HAL_PHY_INITIATED_FRL_12G_4L, 1, gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3].value);

			msleep(gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value);

			if(HDMI21_PHY_Rx_Get_CheckEqCalDone(port) > 0) {
				HDMI20_INFO("SWWA : EQ Cal Done Success for Port[%d]. Gather Calibration Data\n", port);
				HDMI21_PHY_Rx_Get_SaffValue(port);
			}
			else {
				HDMI20_INFO("SWWA : Error! Critical Issue. EQ Calibration was not done for Port[%d]!!\n", port);
			}

			/* Flag needs to be Restored for PHY APB control API */
			gHDMI21RxHandler[port].is5Vconnected = 0;

			gHDMI21RxHandler[port].top_write(0xB0, 0x0);
			/* PHY PDB LOW */
			HDMI21_PHY_Rx_Set_ControlPhyPdb(port, 0);
			break;
		case 22:
			printk("Offset Cal Test Start : Port[%d] / Count[%d]\n",port,  data);
			gHdmi21OffsetRepeatIteration[port] = data;

			gHdmi21OffsetRepeatIndex[port] = 0;
			gHdmi21OffsetRepeatTest[port] = 0;
			gHdmi21OffsetRepeatState[port] = 0;

			break;
		case 23 :
			if(gHdmi21OffsetRepeatIteration[port] != 0) {
				printk("Test is currently active. Iteration Count [%d]. State[%d]\n", gHdmi21OffsetRepeatIteration[port], gHdmi21OffsetRepeatState[port]);
			}
			else {
				for(i=0; i<gHdmi21OffsetRepeatIndex[port]; i++) {
					printk("ch0 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21CalTestData[port][i].se_os_ch0, gHdmi21CalTestData[port][i].so_os_ch0, gHdmi21CalTestData[port][i].te_os_ch0, gHdmi21CalTestData[port][i].to_os_ch0,\
							gHdmi21CalTestData[port][i].dep_os_ch0, gHdmi21CalTestData[port][i].den_os_ch0, gHdmi21CalTestData[port][i].dop_os_ch0, gHdmi21CalTestData[port][i].don_os_ch0,\
							gHdmi21CalTestData[port][i].eq_os_ch0);
				}
				for(i=0; i<gHdmi21OffsetRepeatIndex[port]; i++) {
					printk("ch1 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21CalTestData[port][i].se_os_ch1, gHdmi21CalTestData[port][i].so_os_ch1, gHdmi21CalTestData[port][i].te_os_ch1, gHdmi21CalTestData[port][i].to_os_ch1,\
							gHdmi21CalTestData[port][i].dep_os_ch1, gHdmi21CalTestData[port][i].den_os_ch1, gHdmi21CalTestData[port][i].dop_os_ch1, gHdmi21CalTestData[port][i].don_os_ch1,\
							gHdmi21CalTestData[port][i].eq_os_ch1);
				}
				for(i=0; i<gHdmi21OffsetRepeatIndex[port]; i++) {
					printk("ch2 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21CalTestData[port][i].se_os_ch2, gHdmi21CalTestData[port][i].so_os_ch2, gHdmi21CalTestData[port][i].te_os_ch2, gHdmi21CalTestData[port][i].to_os_ch2,\
							gHdmi21CalTestData[port][i].dep_os_ch2, gHdmi21CalTestData[port][i].den_os_ch2, gHdmi21CalTestData[port][i].dop_os_ch2, gHdmi21CalTestData[port][i].don_os_ch2,\
							gHdmi21CalTestData[port][i].eq_os_ch2);
				}
				for(i=0; i<gHdmi21OffsetRepeatIndex[port]; i++) {
					printk("ch3 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21CalTestData[port][i].se_os_ch3, gHdmi21CalTestData[port][i].so_os_ch3, gHdmi21CalTestData[port][i].te_os_ch3, gHdmi21CalTestData[port][i].to_os_ch3,\
							gHdmi21CalTestData[port][i].dep_os_ch3, gHdmi21CalTestData[port][i].den_os_ch3, gHdmi21CalTestData[port][i].dop_os_ch3, gHdmi21CalTestData[port][i].don_os_ch3,\
							gHdmi21CalTestData[port][i].eq_os_ch3);
				}

			}
			break;
		case 24:
			printk("Dfe Cal Test Start : Port[%d] / Count[%d]\n",port,  data);
			gHdmi21DfeRepeatIteration[port] = data;

			gHdmi21DfeRepeatIndex[port] = 0;
			gHdmi21DfeRepeatTest[port] = 0;
			gHdmi21DfeRepeatState[port] = 0;
			break;
		case 25:
			if(gHdmi21DfeRepeatIteration[port] != 0) {
				printk("Test is currently active. Iteration Count [%d]. State[%d]\n", gHdmi21DfeRepeatIteration[port], gHdmi21DfeRepeatState[port]);
			}
			else {
				for(i=0; i<gHdmi21DfeRepeatIndex[port]; i++) {
					printk("ch0 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21DfeTestData[port][i].dfeA01_ch0, gHdmi21DfeTestData[port][i].dfeA11_ch0, gHdmi21DfeTestData[port][i].dfeB1_ch0, gHdmi21DfeTestData[port][i].dfeB2_ch0,\
							gHdmi21DfeTestData[port][i].dfeB3_ch0, gHdmi21DfeTestData[port][i].dfeB4_ch0, gHdmi21DfeTestData[port][i].dfeB5_ch0,\
							gHdmi21DfeTestData[port][i].ced_error_ch0, gHdmi21DfeTestData[port][i].tmds_error_ch0);
				}
				for(i=0; i<gHdmi21DfeRepeatIndex[port]; i++) {
					printk("ch1 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21DfeTestData[port][i].dfeA01_ch1, gHdmi21DfeTestData[port][i].dfeA11_ch1, gHdmi21DfeTestData[port][i].dfeB1_ch1, gHdmi21DfeTestData[port][i].dfeB2_ch1,\
							gHdmi21DfeTestData[port][i].dfeB3_ch1, gHdmi21DfeTestData[port][i].dfeB4_ch1, gHdmi21DfeTestData[port][i].dfeB5_ch1,\
							gHdmi21DfeTestData[port][i].ced_error_ch1, gHdmi21DfeTestData[port][i].tmds_error_ch1);
				}
				for(i=0; i<gHdmi21DfeRepeatIndex[port]; i++) {
					printk("ch2 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21DfeTestData[port][i].dfeA01_ch2, gHdmi21DfeTestData[port][i].dfeA11_ch2, gHdmi21DfeTestData[port][i].dfeB1_ch2, gHdmi21DfeTestData[port][i].dfeB2_ch2,\
							gHdmi21DfeTestData[port][i].dfeB3_ch2, gHdmi21DfeTestData[port][i].dfeB4_ch2, gHdmi21DfeTestData[port][i].dfeB5_ch2,\
							gHdmi21DfeTestData[port][i].ced_error_ch2, gHdmi21DfeTestData[port][i].tmds_error_ch2);
				}
				for(i=0; i<gHdmi21DfeRepeatIndex[port]; i++) {
					printk("ch3 : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
							gHdmi21DfeTestData[port][i].dfeA01_ch3, gHdmi21DfeTestData[port][i].dfeA11_ch3, gHdmi21DfeTestData[port][i].dfeB1_ch3, gHdmi21DfeTestData[port][i].dfeB2_ch3,\
							gHdmi21DfeTestData[port][i].dfeB3_ch3, gHdmi21DfeTestData[port][i].dfeB4_ch3, gHdmi21DfeTestData[port][i].dfeB5_ch3,\
							gHdmi21DfeTestData[port][i].ced_error_ch3, gHdmi21DfeTestData[port][i].tmds_error_ch3);
				}
			}
			break;
		case 30:
			HDMI21_HAL_Rx_Get_IsVideoSyncChanged(&gHDMI21RxHandler[port], &gHDMI21RxHandler[port].hwVideo);
			break;
		case 35:
			HDMI21_ISRUNIT_Rx_Set_ForceIsrSet(&gHDMI21RxHandler[port], HDMI21_IRQ_SNPS_SCDC_INTVEC, data);
			break;
		case 36:
			HDMI21_ISRUNIT_Rx_Set_ForceIsrSet(&gHDMI21RxHandler[port], HDMI21_IRQ_SNPS_PKT_0_INTVEC, data);
			break;
		case 40:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi214BlockEDID_O26_EEODE_144_165, sizeof(gHdmi214BlockEDID_O26_EEODE_144_165), 1);
			break;
		case 41:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi214BlockEDID_O26_EEODE_144_165_DOLBY, sizeof(gHdmi214BlockEDID_O26_EEODE_144_165_DOLBY), 1);
			break;
		case 42:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Frl8G, sizeof(gHdmi21TestEDID_Frl8G), 1);
			break;
		case 43:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Frl6G, sizeof(gHdmi21TestEDID_Frl6G), 1);
			break;
		case 44:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Frl3L6G, sizeof(gHdmi21TestEDID_Frl3L6G), 1);
			break;
		case 45:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Frl3L3G, sizeof(gHdmi21TestEDID_Frl3L3G), 1);
			break;
		case 46:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Frl12G, sizeof(gHdmi21TestEDID_Frl12G), 1);
			break;
		case 47:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi214BlockEDID_Zero, sizeof(gHdmi214BlockEDID_Zero), 1);
			break;
		case 48:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi214BlockEDID, sizeof(gHdmi214BlockEDID), 1);
			break;
		case 49:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_FRL12G_Jang, sizeof(gHdmi21TestEDID_FRL12G_Jang), 1);
			break;
		case 50:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_FRL10G_Jang, sizeof(gHdmi21TestEDID_FRL12G_Jang), 1);
			break;
		case 51:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_FRL8G_Jang, sizeof(gHdmi21TestEDID_FRL12G_Jang), 1);
			break;
		case 52:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Jang_4kVrrOffFreeOff, sizeof(gHdmi21TestEDID_Jang_4kVrrOffFreeOff), 1);
			break;
		case 53:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Jang_4kVrrOffFreeOn, sizeof(gHdmi21TestEDID_Jang_4kVrrOffFreeOn), 1);
			break;
		case 54:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Jang_4kVrrOnFreeOff, sizeof(gHdmi21TestEDID_Jang_4kVrrOnFreeOff), 1);
			break;
		case 55:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Jang_4kVrrOnFreeOn, sizeof(gHdmi21TestEDID_Jang_4kVrrOnFreeOn), 1);
			break;
		case 56:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Jang_EDIDOff, sizeof(gHdmi21TestEDID_Jang_EDIDOff), 1);
			break;
		case 57:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21TestEDID_Jang_4kVrrOnFreeOn12G4L, sizeof(gHdmi21TestEDID_Jang_4kVrrOnFreeOn12G4L), 1);
			break;
		case 58:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21webOs22_4K_On, sizeof(gHdmi21webOs22_4K_On), 1);
			break;
		case 59:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi214BlockEDID_165Hz, sizeof(gHdmi214BlockEDID_165Hz), 1);
			break;
		case 60:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi214BlockEDID_165Hz_QFT, sizeof(gHdmi214BlockEDID_165Hz_QFT), 1);
			break;
		case 61:
			HDMI21_HAL_Rx_Set_EDID(port, (UINT8 *)&gHdmi21webOs22_8K_On, sizeof(gHdmi21webOs22_8K_On), 1);
			break;
		case 62:
			HDMI21_HAL_Rx_DBG_GetCsEyeWidth(port);
			break;
		case 63:
			HDMI21_HAL_Rx_DBG_PrintCsEyeWidth(port);
			break;
		case 66:
			HDMI21_PHY_Rx_Set_ToggleTCSEn(port, 0);
			printk("Toggle TCS EN for port[%d]\n", port);
			HDMI21_PHY_Rx_Set_ToggleTCSEn(port, 1);
			break;
		case 69:
			HDMI21_SCDC_Rx_Set_CedCountRst(&gHDMI21RxHandler[port], 1);
			HDMI21_SCDC_Rx_Set_CedCountRst(&gHDMI21RxHandler[port], 0);
			break;
		case 70:
			HDMI21_HAL_Rx_DBG_ActivateEyeMonitor(port, 1, 0, data);
			break;
		case 71:
			gHdmi21EyeYPrintScale = data;
			break;
		case 72:
			HDMI21_HAL_Rx_DBG_ActivateEyeMonitor(port, 2, 0, data);
			break;
		case 73:
			__HDMI21_HAL_Rx_DBG_PrintEyeDiagramChr(&gHDMI21RxHandler[port]);
			break;
		case 74:
			__HDMI21_HAL_Rx_DBG_PrintEyeDiagramHex(&gHDMI21RxHandler[port]);
			break;
		case 80:
			gHdmi21FrlErrMeasure[port] = 1;
			gHdmi21FrlErrState[port] = -1;
			gHdmi21FrlErrDone[port][0] = 0;
			gHdmi21FrlErrDone[port][1] = 0;
			gHdmi21FrlErrDone[port][2] = 0;
			gHdmi21FrlErrDone[port][3] = 0;
			gHdmi21FrlValue[port][0] = 0;
			gHdmi21FrlValue[port][1] = 0;
			gHdmi21FrlValue[port][2] = 0;
			gHdmi21FrlValue[port][3] = 0;
			break;
		case 81:
			if(data > 0) {
				gHDMI21RxHandler[port].isSleepMode = true;
			}
			else {
				gHDMI21RxHandler[port].isSleepMode = false;
			}
			break;
		case 82:
			HDMI21_HAL_Rx_Set_HDCP22Info(port, 1);
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
				HDMI21_HDCP23_Module_TestApp(6, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
				HDMI21_HDCP23_Module_TestApp(5, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
				HDMI21_HDCP23_Module_TestApp(4, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
				HDMI21_HDCP23_Module_TestApp(3, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
				HDMI21_HDCP23_Module_TestApp(2, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
				HDMI21_HDCP23_Module_TestApp(1, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			else{
				HDMI21_HDCP23_Module_TestApp(0, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
			}
			break;
		case 83:
			for(i=0;i<g_hdmi20_number_of_ports;i++) {
				gHDMI21RxHandler[i].repeaterHpd = 1;
			}
			HDMI21_HDCP23_Module_Set_IsRepeater(data);
			break;
		case 90:
			printk(" DSC = %d\n", 	HDMI21_DSC_Rx_Set_ExecuteDscModule(&gHDMI21RxHandler[port]));
			break;
		case 95:
			HDMI21_HAL_Rx_Set_ZombieMode(port, data);
			break;
		case 96:
			printk("Port[%d] -> ZombieMode is [%d]\n", port, gHDMI21RxHandler[port].zombieMode);
			break;
		case 100:
			if(data >= g_hdmi20_number_of_ports)
			{
				gHDMI21RxDevVideoControler[HDMI21__FORCE_5V_DOWN].value = 1;
				msleep(data);
				gHDMI21RxDevVideoControler[HDMI21__FORCE_5V_DOWN].value = 0;

				for(i=0;i<gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value;i++)
				{
					HDMI21_HAL_ConnectCable(i, 1);
				}
			}
			else {
				HDMI21_HAL_ConnectCable(port, data);
			}
			break;
		case 102:
			{
				gLowPowerStateMidTick = data;
			}
			break;
		case 103:
			{
				printk("gLowPowerStateMidTick = %d\n", gLowPowerStateMidTick);
			}
			break;
		case 104:
			printk("gLowPowerState3Tick=[%d] gLowPowerState4Tick=[%d] gLowPowerState5Tick=[%d]\n", gLowPowerState3Tick, gLowPowerState4Tick, gLowPowerState5Tick);
			break;
		case 105:
			gLowPowerState3Tick = data;
			break;
		case 106:
			gLowPowerState4Tick = data;
			break;
		case 107:
			gLowPowerState5Tick = data;
			break;
		case 120:
			if(_p->pDdcBuf == NULL){
				_p->pDdcBuf = (HDMI21_HAL_DDC_HW_UNITDATA_T *)kmalloc(sizeof(HDMI21_HAL_DDC_HW_UNITDATA_T) * data, GFP_KERNEL);

				if(_p->pDdcBuf != NULL) {
					_p->ddcBufCnt = data;
					_p->ddcBufPnt = 0;

					/* Clear Buffer */
					memset((void *)_p->pDdcBuf, 0, sizeof(HDMI21_HAL_DDC_HW_UNITDATA_T) * data);

					printk("DDCMon[%d] : Successfully allocated Buf[%p] with count [%d]\n", _p->port, (void *)_p->pDdcBuf, _p->ddcBufCnt);
				}
			}
			else {
				printk("Cannot newly allocate due to already being allocated. Addr[%p]/Cnt[%d]\n", (void *)_p->pDdcBuf, _p->ddcBufCnt);
			}
			break;
		case 121:
			{
				if(_p->pDdcBuf != NULL) {
					kfree(_p->pDdcBuf);
					printk("Successfully free DDCMON mem\n");
					_p->pDdcBuf = NULL;
					_p->ddcBufCnt = 0;
					_p->ddcBufPnt = 0;
				}
				else {
					printk("Cannot free of what is already free\n");
				}
			}
			break;
		case 122:
			{
				HDMI21_DDCMON_Rx_Set_Initialize(&gHDMI21RxHandler[port]);
			}
			break;
		case 123:
			{
				HDMI21_DDCMON_Rx_Set_ClearMonitor(_p, 1);
				HDMI21_DDCMON_Rx_Set_ClearMonitor(_p, 0);

				if(_p->pDdcBuf != NULL) {
					_p->ddcBufPnt = 0;
					memset((void *)_p->pDdcBuf, 0, sizeof(HDMI21_HAL_DDC_HW_UNITDATA_T) * _p->ddcBufCnt);
				}

				HDMI21_DDCMON_Rx_Set_EnableMonitor(&gHDMI21RxHandler[port], data);
			}
			break;
		case 124:
			{
				int i,y;
				UINT8 __data[4];
				
				printk("DDCbufCnt[%d], DDCbufPnt[%d]\n", _p->ddcBufCnt, _p->ddcBufPnt);

				for(i=0;i<_p->ddcBufPnt;i++) {
					printk("#[%d]|[%u]msec (Bank:%d) => %02x:%02x(%s) - ",\
							i, _p->pDdcBuf[i].msec, _p->pDdcBuf[i].bank, _p->pDdcBuf[i].dev_addr, _p->pDdcBuf[i].sub_addr, _p->pDdcBuf[i].op_mode?"R":"W");	

					memcpy((void *)&__data[0], (void *)&_p->pDdcBuf[i].data, sizeof(UINT32));

					for(y=0; y<_p->pDdcBuf[i].cap_length; y++) {
						printk("%02x ", __data[3-y]);
					}
					
					printk("(length:%d) %s%s%s%s\n", _p->pDdcBuf[i].cap_length, _p->pDdcBuf[i].finish?"(Finish)":"",\
							_p->pDdcBuf[i].scdc_short_rd?"(SCDC Short)":"", _p->pDdcBuf[i].hdcp_short_rd?"(HDCP Short)":"", _p->pDdcBuf[i].nack?"(NACK)":"");	
				}
			}
			break;
		case 125:
			{
				HDMI21_DDCMON_Rx_Get_ProcessIsr(_p);
			}
			break;
		case 150:
			{
				HDMI21_HDCP23_Module_Set_HlcAuthenticate(port, data);
			}
			break;
		case 180:
			{
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep0(&gHDMI21RxHandler[port], data);
			}
			break;
		case 181 :
			{
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(&gHDMI21RxHandler[port], data);
			}
			break;
		case 182:
			{
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(&gHDMI21RxHandler[port], data);
			}
			break;
		case 183:
			{
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep3(&gHDMI21RxHandler[port], data);
			}
			break;	
		case 199:
			{
				__HDMI21_HAL_Rx_Reset_AsyncBridge(port);
			}
			break;	
		case 200:
			__HDMI21_HAL_Rx_Set_InverseHPDControl(port, data);
			break;
		case 600:
			printk("DSC/FEC Override [%d]\n", gFecDbgRegOvrRide );
			break;
		case 601:
			gFecDbgRegOvrRide = data;
			break;
		case 602:
			for(i=0;i<HDMI21_DSC_F20_MAXNUM;i++) {
				if(gFecDbgRegOvrRide > 0) {
					printk(" Idx[%02d](OvrRide) : Addr[0x%08x] <= [0x%08x]\n", i, gF20ChipIdData.f20Data[i].addr, 	gFecDbgDataSet[i]);
				}
				else {
					printk(" Idx[%02d] : Addr[0x%08x] <= [0x%08x]\n", i, gF20ChipIdData.f20Data[i].addr, 	gF20ChipIdData.f20Data[i].value);
				}
			}
			break;
		case 603:
			if(gFecDbgRegOvrRide > 0) {
				for(i=0;i<HDMI21_DSC_F20_MAXNUM;i++) {
					gFecDbgDataSet[i] = gF20ChipIdData.f20Data[i].value;
					printk(" Idx[%02d](OvrRide) : Addr[0x%08x] <= [0x%08x]\n", i, gF20ChipIdData.f20Data[i].addr, 	gFecDbgDataSet[i]);
				}
			}
			else {
				printk("Copy FEC driver data to DBG mem only works when DBG is enabled!\n");
			}
			break;
		case 604:
			printk("Force Update DSC/FEC F20 data\n");
			HDMI21_DSC_Rx_Set_F20IpcData( &gHDMI21RxHandler[port], &gF20ChipIdData);
			break;
		case 666:
			HDMI21_PHY_Rx_Set_ControlPhyPdb(port, data);
			break;
		case 777:
			gHDMI21RxHandler[port].hdrOverRide = data;
			break;
		case 800:
			{
				LX_HDMI20_CMD_T cmd;
				if(data > 0) {
					cmd.command = HDMI20_CMD_RX_SET_ENABLE_OPERATION;
					cmd.size = 1;
				}
				else {
					cmd.command = HDMI20_CMD_RX_SET_DISABLE_OPERATION;
					cmd.size = 0;
				}

				HDMI21_Process_Cmd(&cmd);
			}
			break;
		case 811:
			gHDMI21Thread.mSleep = data;
			break;
		case 812:
			printk("Current Main thread sleep time is [%d]\n", gHDMI21Thread.mSleep);
			break;
		case 813:
			printk("Current Main thread status is [%d]\n", gHDMI21Thread.isAlive);
			break;
		case 814:
			gHDMI21Thread.isAlive = data;
			break;
		case 815 :
			gHDMI21RxHandler[port].is5Vconnected = data;
			break;
		case 887 :
			printk("gTop300ResetCnt = %d\n", gTop300ResetCnt);
			break;
		case 888:
			gTop300ResetCnt = data;
			break;
		case 1001:
			gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value = data;
			break;
		case 2000:
			HDMI21_HDCP_Rx_Set_HDCP14Keys(&gHDMI21RxHandler[port], &gHDMI21RxHandler[port].hdcp);
			break;
		case 3000:
			printk(" Was HDCP 1.4 port[%d] written? [%d]\n",port, gHDMI21RxHandler[port].gWasHDCP14Written);
			break;
		case 3001:
			printk(" Was HDCP 2.2 port[%d] written? [%d]\n",port, gHDMI21RxHandler[port].gWasHDCP22Written);
			break;
		case 3002:
			gHDMI21RxHandler[port].gWasHDCP14Written = data;
			break;
		case 3003:
			gHDMI21RxHandler[port].gWasHDCP22Written = data;
			break;
		case 5000:
			gHDMI21RxHandler[port].hdmiDisabled = data;
			break;
		case 6500:
			__HDMI21_HAL_Rx_Set_HPD(port ,data, 0);
			break;
		case 6666:
			HDMI21_DISLAND_Rx_Get_PrintPktBuf(data, port);
			break;
		case 6667:
			HDMI21_DISLAND_Rx_Set_ResetPktBuf(data, port);
			break;
		case 6668:
			HDMI21_DISLAND_Rx_Get_PrintEmPkttBuf(data, port);
			break;
		case 6669:
			HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(data, port);
			break;
		case 66666:
			printk("Force Suspend on HDMI2.0\n");
			HDMI21_Suspend();
			break;
		case 66667:
			printk("Force Resume on HDMI2.0\n");
			HDMI21_Resume();
			break;
		case 66668:
			HDMI21_HDCP23_Module_Set_Close();
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
				/* None */
			}
			else if  ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
				HDMI21_REG_RD(0xC3320004, __d); 
				__d |= 0x10; 
				HDMI21_REG_WR(0xC3320004, __d);
			}
			else {
				HDMI21_REG_RD(0xC9306008, __d); 
				__d |= 0x10000; 
				HDMI21_REG_WR(0xC9306008, __d);
			}		
			break;
		case 66669:
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
				/* None */
			}
			else if  ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
				HDMI21_REG_RD(0xC3320004, __d); 
				__d &= (~0x10); 
				HDMI21_REG_WR(0xC3320004, __d);
			}
			else {
				HDMI21_REG_RD(0xC9306008, __d); 
				__d &= (~0x10000); 
				HDMI21_REG_WR(0xC9306008, __d);
			}		
			printk("ESM Griffin is reset Low!\n");
			break;
		case 75000:
			gHDMI21RxHandler[port].isAudioARCMode = data;	
			break;
		case 75001:
			printk("gEnableARCControl[%d] = %d\n" ,port, gHDMI21RxHandler[port].isAudioARCMode);
			break;
		default :
			break;
	}

	return RET_OK;
}

int	HDMI21_HAL_Rx_Get_OperationStatus(UINT8 port, LX_HDMI20_OP_STATUS_T *pData)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	LX_HDMI20_OP_STATUS_T data;

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		memset((LX_HDMI20_OP_STATUS_T *)&data, 0, sizeof(LX_HDMI20_OP_STATUS_T));

		if(_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) {
			data.isSteady = true;	
		}
		else {
			data.isSteady = false;	
		}

		if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(_p) > 0)	{		data.isDVI = true;  }
		else											{		data.isDVI = false; }

		if(_p->restartHpdFlagUp > 0) 					{		data.isRestartState = true; }
		else 											{		data.isRestartState = false;}

		data.numOfActivePort = (UINT32)gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value;

		/* copy data */
		memcpy((LX_HDMI20_OP_STATUS_T *)pData, (LX_HDMI20_OP_STATUS_T *)&data, sizeof(LX_HDMI20_OP_STATUS_T));

		ret = RET_OK;
	} while(0);

	return ret;


}

/* RET = 1 if sync has changed, RET = 0 if not changed over threshold */
int HDMI21_HAL_Rx_Get_IsVideoSyncChanged(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_HAL_VIDEO_TIMING_T *pComp)
{
	int ret = 0;
	UINT32 currentJiffies = 0;
	int __temp = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 _diff = 0;
	HDMI21_HAL_VIDEO_TIMING_T v; 
	UINT32 _vact_low;
	UINT32 _vtot_low;
	UINT32 _hact_low;
	UINT32 _htot_low;
	UINT32 _vact_high;
	UINT32 _vtot_high;
	UINT32 _hact_high;
	UINT32 _htot_high;

	_vact_low = gHDMI21RxDevVideoControler[HDMI21__LINK_LOWEST_V_ACTIVE].value;
	_vtot_low = gHDMI21RxDevVideoControler[HDMI21__LINK_LOWEST_V_TOTAL].value;
	_hact_low = gHDMI21RxDevVideoControler[HDMI21__LINK_LOWEST_H_ACTIVE].value;
	_htot_low = gHDMI21RxDevVideoControler[HDMI21__LINK_LOWEST_H_TOTAL].value;

	_vact_high = gHDMI21RxDevVideoControler[HDMI21__LINK_HIGHEST_V_ACTIVE].value;
	_vtot_high = gHDMI21RxDevVideoControler[HDMI21__LINK_HIGHEST_V_TOTAL].value;
	_hact_high = gHDMI21RxDevVideoControler[HDMI21__LINK_HIGHEST_H_ACTIVE].value;
	_htot_high = gHDMI21RxDevVideoControler[HDMI21__LINK_HIGHEST_H_TOTAL].value;

	do {
		/* Step 1. Check Pointer */
		if (_p == 0) {
			ret = RET_ERROR;
			break;
		}

		/* Step 2. Wait for stablization */
		if(_p->tmds_change != 0){
			if( lx_board_opt() & LX_BOARD_OPT_SLT) {
				HDMI20_INFO("Check [%d] : Will not check on unstable TMDS\n", _p->port);
			}
			else{
				HDMI21_LINE_DBG(2480, "Check [%d] : Will not check on unstable TMDS\n", _p->port);
			}
			break;
		}

		if(_p->isMute != 0){
			if( lx_board_opt() & LX_BOARD_OPT_SLT) {
				HDMI20_INFO("Check [%d] : Will not check on AVMute\n", _p->port);
			}
			else {
				HDMI21_LINE_DBG(2480, "Check [%d] : Will not check on AVMute\n", _p->port);
			}
			break;
		}

		if(_p->isPhyLocked == 0) {
			if( lx_board_opt() & LX_BOARD_OPT_SLT) {
				HDMI20_INFO("Check [%d] : Will not check on AVMute\n", _p->port);
			}
			else {
				HDMI21_LINE_DBG(2480, "Check [%d] : Will not check on AVMute\n", _p->port);
			}
			break;
		}

		/* Step 3. Get Video sync param */
		memset((HDMI21_HAL_VIDEO_TIMING_T *)&v, 0, sizeof(HDMI21_HAL_VIDEO_TIMING_T));
		HDMI21_HAL_Rx_Get_VideoInfo(_p, &v);


		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 164) {
			HDMI20_DBG("DBG[%d] : Origin [%ux%u%c@%uHz: %s, DCM %ub, VIC:%u] -> Current[%ux%u%c@%uHz: %s, DCM %ub, VIC:%u]\n",\
					_p->port, pComp->hactive, pComp->vactive, pComp->interlaced? 'i' : 'p',pComp->vfreq, pComp->dvi? "DVI" : "HDMI", pComp->deep_color_mode, pComp->vicCode,\
					v.hactive,v.vactive,v.interlaced? 'i' : 'p',v.vfreq,v.dvi? "DVI" : "HDMI",v.deep_color_mode, v.vicCode);

			return 0;
		}

		/* Check Range : There are too many garbage interrupts from HW. Need to limit false alarm.
		 *               ISR will held up video_change flag to high, which will result a video_stable cnt to be zero.
		 *               The only side-effects that could happen is that the hwVideo handler data will keep its previous values.*/
		/* Check #1. HV Total/Active Range */
		if(((_p->isFreeSyncMode > 0) && (gHDMI21RxDevVideoControler[HDMI21__LINK_AMD_FREESYNC_MODE].value != 0))\
				||(gHDMI21RxDevVideoControler[HDMI21__LINK_AMD_FREESYNC_MODE].value == 2)){
			/* Do not do this on VRR */
			/* Blink issue on GSYNC : 2019/12/04 */
		}
		else if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G){
			if(		   (v.hactive < _hact_low) || (v.hactive > _hact_high)\
					|| (v.htotal  < _htot_low) || (v.htotal  > _htot_high)\
					|| (v.vactive < _vact_low) || (v.vactive > _vact_high)\
					|| (v.vtotal  < _vtot_low) || (v.vtotal  > _vtot_high)) {
				if( lx_board_opt() & LX_BOARD_OPT_SLT) {
					HDMI20_INFO("DBG[%d] Over limit [%d]([%d])x[%d]([%d])\n", _p->port, v.hactive, v.htotal, v.vactive, v.vtotal);

				}
				else{
					HDMI21_LINE_DBG(2623, "DBG[%d] Over limit [%d]([%d])x[%d]([%d])\n", _p->port, v.hactive, v.htotal, v.vactive, v.vtotal);
				}
				ret = 1;
				break;
			}
		}


		if((pComp->hactive + gHDMI21RxDevVideoControler[HDMI21__LINK_H_ACTIVE_DIFF_THRES].value) < (v.hactive)) 							_diff |= 0x1;
		//if(_diff != 0) HDMI20_VIDEO("[%d] < [%d]\n", (pComp->hactive + gHDMI21RxDevVideoControler[HDMI21__LINK_H_ACTIVE_DIFF_THRES].value), v.hactive);
		if((pComp->hactive >= _hact_low) && ((pComp->hactive - gHDMI21RxDevVideoControler[HDMI21__LINK_H_ACTIVE_DIFF_THRES].value) > (v.hactive))) 	_diff |= 0x2; 
		if(((pComp->vactive + gHDMI21RxDevVideoControler[HDMI21__LINK_V_ACTIVE_DIFF_THRES].value)) < (v.vactive)) 							_diff |= 0x4; 
		if((pComp->vactive >= _vact_low) && ((pComp->vactive - gHDMI21RxDevVideoControler[HDMI21__LINK_V_ACTIVE_DIFF_THRES].value) > (v.vactive))) 	_diff |= 0x8;
		//if((pComp->htotal + gHDMI21RxDevVideoControler[HDMI21__LINK_H_TOTAL_DIFF_THRES].value < (v.htotal))) 								_diff |= 0x10;
		//if((pComp->htotal >= _htot_low) && ((pComp->htotal - gHDMI21RxDevVideoControler[HDMI21__LINK_H_TOTAL_DIFF_THRES].value) > (v.htotal))) 		_diff |= 0x20; 
		if((pComp->vtotal + gHDMI21RxDevVideoControler[HDMI21__LINK_V_TOTAL_DIFF_THRES].value) < (v.vtotal)) 								_diff |= 0x40; 
		if((pComp->vtotal >= _vtot_low) && ((pComp->vtotal - gHDMI21RxDevVideoControler[HDMI21__LINK_V_TOTAL_DIFF_THRES].value) > (v.vtotal))) 		_diff |= 0x80;
		if(pComp->dvi != v.dvi) 								_diff |= 0x100; 	
		if(pComp->interlaced != v.interlaced) 					_diff |= 0x200;
		if(pComp->pixel_repetition != v.pixel_repetition) 		_diff |= 0x400;
		if(pComp->video_format != v.video_format) 				_diff |= 0x800; 
		if(pComp->deep_color_mode != v.deep_color_mode) 		_diff |= 0x1000; 
		if(pComp->vfreq != v.vfreq) 							_diff |= 0x2000;
		if(pComp->vicCode != v.vicCode) 						_diff |= 0x4000;

		/* 2019/05/24: In FRL Mode, discard HActive changes */
		if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			_diff &= (~0xF0);
		}

		/* 2020/04/08 : If in low Power Mode do not consider DVI/HDMI, vicCode changes */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value > 0) {
			if(_p->lowPowerMode >=HDMI21_HAL_POWER_LOWPOWER) {
				/* Discard DVI/HDMI changes */
				_diff &= (~0x100);
			
				/* Discard VIC Code changes */
				_diff &= (~0x4000);

				/* Discard ColorDepth Changes */
				_diff &= (~0x1000);

				/* Discard HActive changes */
				_diff &= (~0x3);

				/* 2020/06/29 : Discard VActive/Total changes */
				_diff &= (~0xCC);
			}
		}

		/* 2021/06/02 : Discard HActive changes in DSC Modes */
		if(_p->isDSC > 0) {
			/* Discard HActive changes */
				_diff &= (~0x3);

				/* 2020/06/29 : Discard VActive/Total changes */
				_diff &= (~0xCC);
		}

		/* Step 4. Do not consider Video ISR on VRR/FVA/FreeSync/GSync mode  */
		if(((_p->isFreeSyncMode > 0) && (gHDMI21RxDevVideoControler[HDMI21__LINK_AMD_FREESYNC_MODE].value != 0))\
				||(gHDMI21RxDevVideoControler[HDMI21__LINK_AMD_FREESYNC_MODE].value == 2)\
				||((_p->isQmsMode > 0) && (gHDMI21RxDevVideoControler[HDMI21__LINK_FORCE_QMS_MODE].value != 0))\
				||(gHDMI21RxDevVideoControler[HDMI21__LINK_FORCE_QMS_MODE].value == 2)){
			if(pComp->hactive != 0)		_diff &= ( ~0x3);
			if(pComp->vactive != 0)		_diff &= ( ~0xC);
			if(pComp->htotal  != 0)		_diff &= ( ~0x30);
			if(pComp->vtotal  != 0)		_diff &= ( ~0xC0);

			/* 2020/09/22 : NVidia 3090/3080/... breaks VSync Field so sink devices observes Interlaced/Progress changes on TMDS VRR modes..
			 * 			  : Would have to discard this changes on VRR modes */
			_diff &= (~0x2200);
		}


		/* Discard VFreq changes under value of 2 */
		if( (_diff == 0x2000) && (abs(pComp->vfreq - v.vfreq) < 2) ) {
			_diff &= (~0x2000);
		}

		/* 2025/07/10 : No blink on Q980B HF2-12 480P FRL 12BIT issue*/
		if(_p->isFrl480pDcmForceSwWa > 0) {
			_diff &= (~0x8);
		}

		/* DBG */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_DISCARD_SPECIFIC_CHANGES].value > 0) {
			_diff &= (~gHDMI21RxDevVideoControler[HDMI21__VIDEO_DISCARD_SPECIFIC_CHANGES].value);
		}

		/* Step 5. If video change, save status & set PHY */
		if(_diff != 0){
			/* To decide whether to show prints on Video Changes(to avoid many prints on unstable situation */
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_CHG_PRINT_INTERVAL].value > 0){	
				currentJiffies = jiffies_to_msecs(jiffies);

				if((_p->videoChgCount < 10)|| ( _p->stable_cnt > 0)) __temp = 1;
				else if(currentJiffies - _p->vidChgTime >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_CHG_PRINT_INTERVAL].value){
					__temp = 1;
				}
				else {
					__temp = 0;
				}
			}
			else {
				__temp = 1;
			}

			if( __temp > 0) {
				HDMI20_INFO("Port[%d][0x%04x]:Video[%d][%04ux%04u%c@%03uHz:%s,DCM%s,VIC:%u]->[%04ux%04u%c@%03uHz:%s,DCM%s,VIC:%u][real_vfreq:%d][hwVideo.vfreq:%d][%pS]\n",\
						_p->port, _diff, _p->videoChgCount,\
						pComp->hactive, pComp->vactive, pComp->interlaced? 'i' : 'p',pComp->vfreq, pComp->dvi? " DVI" : "HDMI", __deepcolor_to_str(pComp->deep_color_mode), pComp->vicCode,\
						v.hactive,       v.vactive,     v.interlaced? 'i' : 'p',     v.vfreq,      v.dvi? " DVI" : "HDMI", __deepcolor_to_str(v.deep_color_mode),           v.vicCode, _p->real_vfreq, _p->hwVideo.vfreq,\
						__builtin_return_address(0));

				_p->vidChgTime = currentJiffies;
			}

			HDMI21_LINE_DBG(2623, "DBG[%d]=> HTotal/VTotal [0x%08x]/[0x%08x] ---> [0x%08x]/[0x%08x]\n",\
					_p->port, 	pComp->htotal, pComp->vtotal, v.htotal,       v.vtotal);

			/* Update Change Counter : Doesn't matter if it overflows */
			_p->videoChgCount++;

			/* Insert Data to mem */
			memcpy((HDMI21_HAL_VIDEO_TIMING_T *)pComp, (HDMI21_HAL_VIDEO_TIMING_T *)&v, sizeof(HDMI21_HAL_VIDEO_TIMING_T));
		
			ret = 1;
		}
		else{
			HDMI21_LINE_DBG(2541, "DBG[%d] : No change within torrerence\n", _p->port);
		}

	} while(0);

	return ret;
}

void HDMI21_HAL_Rx_Get_VideoInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_HAL_VIDEO_TIMING_T *pDest)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_VMON_VIDEO_SYNC_T _vmon;
	HDMI21_RX_VPROC_CD_TYPE_T _cd = HDMI21_RX_VPROC_CD_NONE;
	int vfreq = 0;

	if(_p 		== NULL) 	return;
	if(pDest 	== NULL)	 return;

	/* Read Sync Info From VMON */
	HDMI21_VMON_Rx_Get_VideoSync(_p, &_vmon);
	HDMI21_VMON_Rx_Set_InsertVideoSyncToHandler(&_vmon, pDest);

	/* 2025/04/14 won.hur : For O26 */
	if(gHDMI21RxDevVideoControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value > 0) {
		vfreq = __HDMI21_HAL_Rx_Get_LinkTopVfreqCounter(_p, 1);
	}
	else {
		vfreq = _p->cvi_vfreq;
	}

	HDMI21_LINE_DBG(164, "DBG[%d] :  From Vmon [%d](%d) x [%d](%d)\n", _p->port,  _vmon.hactive, _vmon.htotal, _vmon.vactive, _vmon.vtotal);


	/* Update  : pixel Repetition / VIC Code/ CSC */
	/* #1). Color Space Conversioni(CSC) Info */
	pDest->video_format 			= ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][4]) & 0x60)>>5;
	/* #2). pDestixel RepDestetition */
	pDest->pixel_repetition		= ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][8]) & 0x0F);
	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 3217) {
		pDest->vicCode = 0;
	}
	else if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 3216) {
		pDest->vicCode = 199;
	}
	else{
		/* #3). Video Format Identification Code(VIC) Info */
		pDest->vicCode					= ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][7]) & 0xFF);
	
		/* 2020/11/13 : If no VIC code in AVI Info frame, refer to H14B VSIF */
		if(pDest->vicCode == 0) {
			/* If ((OUI == 0x000C03) && (PB4 == 0x20)) then refer to PB5 */
			if((_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][4] == 0x03) \
					&& (_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][5] == 0x0C) \
					&& (_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][6] == 0x00) \
					&& (_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][7] == 0x20) \
					&& (vfreq < 3500) ){   /* 2025/04/07 won.hur/wonsik.do --> need to discard values for 35Hz and above...QEVENTTF-7752(wonsik.do) */
			
				pDest->vicCode = (UINT32)__HDMI21_HAL_Rx_Get_VsiHdmiFormatToViC(_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][8]);
			}
		}

	}

	/* Update : DVI/HDMI */ 
	pDest->dvi 		= __HDMI21_HAL_Rx_Get_IsHwInDVIState(_p);
	
	/* Update : Phy */
	pDest->tmds_clk = _p->real_tmds_clk;

	/* Update Vfreq */
	pDest->vfreq = _p->real_vfreq;

	/* MISC */
	pDest->refresh_rate = 0;

	/* Update From GCP parsing result : Never get it from GCP RAW Packet. Get it from Decision HW unit */
	//HDMI21_HAL_VIDEO_DEEPCOLOR_MODE_T deep_color_mode; --> Need to be added;
	_cd = HDMI21_VPROC_Rx_Get_ColorDepth(_p);
	switch(_cd)
	{
		case HDMI21_RX_VPROC_CD_NONE:
			{
				pDest->deep_color_mode = HDMI21_HAL_VIDEO_DEEPCOLOR_NONE;
			}
			break;
		case HDMI21_RX_VPROC_CD_8BIT:
			{
				pDest->deep_color_mode = HDMI21_HAL_VIDEO_DEEPCOLOR_8_BIT;
			}
			break;
		case HDMI21_RX_VPROC_CD_10BIT:
			{
				pDest->deep_color_mode = HDMI21_HAL_VIDEO_DEEPCOLOR_10_BIT;
			}
			break;
		case HDMI21_RX_VPROC_CD_12BIT:
			{
				pDest->deep_color_mode = HDMI21_HAL_VIDEO_DEEPCOLOR_12_BIT;
			}
			break;
		case HDMI21_RX_VPROC_CD_16BIT:
			{
				pDest->deep_color_mode = HDMI21_HAL_VIDEO_DEEPCOLOR_16_BIT;
			}
			break;
		default:
			{
				pDest->deep_color_mode = HDMI21_HAL_VIDEO_DEEPCOLOR_NONE;
			}
			break;
	}


	/* SW modification */
	/* 1) On 4:2:0, HTotal is half of its original video size. */
	if(pDest->video_format == 0x3){
		pDest->hactive = pDest->hactive << 1;
		pDest->htotal = pDest->htotal << 1;
	}

	/* 2) On Interlaced, V value is half.. so this needs to be X2 */
	if(pDest->interlaced > 0) {
		pDest->vtotal = pDest->vtotal << 1;
		pDest->vactive = pDest->vactive << 1;

		/* Link Top Vfreq Counter Initialization */
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value > 0) {
			/* 2025/08/20 won.hur : In DSC signals.. there is no such thing as interlaced.
			 * 						Sometimes the hardware malfunctions..as detecting interlaced for DSC signals.
			 * 						Need to SW workaround such situations..*/
			if(_p->isDSC > 0) {
				__HDMI21_HAL_Rx_Set_LinkTopVfreqCounter(_p, 1, 1); /* Set to progressive counter mode */
			}
			else {
				__HDMI21_HAL_Rx_Set_LinkTopVfreqCounter(_p, 0, 1); /* Set to interlaced counter mode */
			}
		}
	}
	else {
		/* Link Top Vfreq Counter Initialization */
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value > 0) {
			__HDMI21_HAL_Rx_Set_LinkTopVfreqCounter(_p, 1, 1); /* Set to progressive counter mode */
		}
	}

	HDMI21_LINE_DBG(164, "DBG[%d] :  To Handler [%d](%d) x [%d](%d)\n", _p->port,  pDest->hactive, pDest->htotal, pDest->vactive, pDest->vtotal);
	return;
}

void HDMI21_HAL_Rx_Set_PqeHdrInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 data, bool isClear)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	volatile UINT32 *dest = NULL;
	UINT32 __d = 0;
	UINT32 addr = 0;

	if(_p == NULL) return;

	/* 2025/04/29 won.hur : From SJ.YOUM */
	if(_p->isPqeSuspend > 0) {
		return;
	}

	switch(_p->port)
	{
		case HDMI21_HAL_LINK_DEVICE_ID_PORT0:
			{
				addr = 0x0;
			}
			break;		
		case HDMI21_HAL_LINK_DEVICE_ID_PORT1:
			{
				addr = 0x4;
			}
			break;		
		case HDMI21_HAL_LINK_DEVICE_ID_PORT2:
			{
				addr = 0x8;
			}
			break;		
		case HDMI21_HAL_LINK_DEVICE_ID_PORT3:
			{
				addr = 0xC;
			}
			break;		
		case HDMI21_HAL_LINK_DEVICE_ID_PORT4:
			{
				addr = 0x10;
			}
			break;
		default:
			{
				return;
			}
			break;
	}


	/* Set it to promise land */
	if(isClear) {
		__d =  0;
	}
	else {
		__d = data;
	}

	if(sPqeHdrMem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)sPqeHdrMem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}

	return;
}

void HDMI21_HAL_Rx_Get_TopReg(UINT8 port, UINT32 addr, UINT32 count)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	UINT32 __addr = 0;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0x1000) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(addr%4 != 0x0) {
			printk("Error. Must be access 4-byte aligned. Access[%d]\n", addr%4);
			break;
		}
		
		__addr = addr;

		for(i=0;i<count;i++) {
			__addr = addr + (i * 4);
			if(__addr >= 0x1000) break;

			printk("[0x%08x] => [0x%08x]\n", (_p->topMem.hwAddr + __addr), _p->top_read(__addr));
		}
	} while(0);

	return;
}

void HDMI21_HAL_Rx_Set_TopReg(UINT8 port, UINT32 addr, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0x1000) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(addr%4 != 0x0) {
			printk("Error. Must be access 4-byte aligned. Access[%d]\n", addr%4);
			break;
		}

		_p->top_write(addr, value);

		printk("[0x%08x] <= [0x%08x]\n", (_p->topMem.hwAddr + addr), value);
	} while(0);

	return;
}

void HDMI21_HAL_Rx_Get_LinkReg(UINT8 port, UINT32 addr, UINT32 count)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	UINT32 __addr = 0;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0x10000) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(addr%4 != 0x0) {
			printk("Error. Must be access 4-byte aligned. Access[%d]\n", addr%4);
			break;
		}

		__addr = addr;

		for(i=0;i<count;i++) {
			__addr = addr + (i * 4);

			if(__addr >= 0x10000) break;
			printk("[0x%08x] => [0x%08x]\n", (_p->linkMem.hwAddr + __addr), _p->link_read(__addr));
		}
	} while(0);

	return;
}

void HDMI21_HAL_Rx_Set_LinkReg(UINT8 port, UINT32 addr, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0x10000) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(addr%4 != 0x0) {
			printk("Error. Must be access 4-byte aligned. Access[%d]\n", addr%4);
			break;
		}

		_p->link_write(addr, value);

		printk("[0x%08x] <= [0x%08x]\n", (_p->linkMem.hwAddr + addr), value);
	} while(0);

	return;
}

void HDMI21_HAL_Rx_Get_AledReg(UINT8 port, UINT32 addr, UINT32 count)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	UINT32 __addr = 0;
	
	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0x400) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(addr%4 != 0x0) {
			printk("Error. Must be access 4-byte aligned. Access[%d]\n", addr%4);
			break;
		}

		__addr = addr;

		for(i=0;i<count;i++) {
			__addr = addr + (i * 4);
			
			if(__addr >= 0x400) break;

			printk("[0x%08x] => [0x%08x]\n", (_p->aledMem.hwAddr + __addr), _p->aled_read(__addr));
		}
	} while(0);

	return;
}

void HDMI21_HAL_Rx_Set_AledReg(UINT8 port, UINT32 addr, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0x400) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(addr%4 != 0x0) {
			printk("Error. Must be access 4-byte aligned. Access[%d]\n", addr%4);
			break;
		}

		_p->aled_write(addr, value);

		printk("[0x%08x] <= [0x%08x]\n", (_p->aledMem.hwAddr + addr), value);
	} while(0);

	return;
}

void HDMI21_HAL_Rx_Get_PhyReg(UINT8 port, UINT8 regBank, UINT32 addr, UINT32 count)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 __data = 0;
	UINT32 __reg  = 0;
	int i = 0;
	UINT32 __addr = 0;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr >= 0xFF) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		__addr = addr;

		for(i=0;i<count;i++) {

			__addr = addr + i;

			if(__addr >= 0xFF) break;

			if(regBank == 0x28) {
				__reg = __addr; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
			}
			else if(regBank == 0x38) {
				__reg = __addr; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
			}
			else if(regBank == 0x48) {
				__reg = __addr; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
			}
			else {
				printk("Unknown RegBank[0x%x]\n", regBank);
				break;
			}

			printk("I2C[0x%x][0x%08x] => [0x%08x]\n", regBank,  __addr, __data);
		}

	} while(0);

	return;
}

void HDMI21_HAL_Rx_Set_PhyReg(UINT8 port, UINT8 regBank, UINT32 addr, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 __reg  = 0;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(addr > 0xFF) {
			printk("Exceeds mapped region[0x%x]\n", addr);
			break;
		}

		if(regBank == 0x28) {
			__reg = addr; __reg = __reg << 2; _p->phyPDC_write(__reg, value);
		}
		else if(regBank == 0x38) {
			__reg = addr; __reg = __reg << 2; _p->phyDR_write(__reg, value);
		}
		else if(regBank == 0x48) {
			__reg = addr; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, value);
		}
		else {
			printk("Unknown RegBank[0x%x]\n", regBank);
			break;
		}

		printk("I2C[0x%x][0x%08x] <= [0x%08x]\n", regBank,  addr, value);

	} while(0);

	return;
}

void HDMI21_HAL_Rx_DBG_ActivateEyeMonitor(UINT8 port, int mode, int printMode, int scaleMode)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		if(mode == 1){
			if(gHdmi21EyeMeasure[port] == 1) {
				printk("Port[%d] : Eye measure ment in progress. Progress %d percent.\n", port, 100/(gHdmi21EyeStage[port] + 1));
				break;
			}
			else {
				memset((void *)&gHdmi21EyeDataCh0[port], 0, sizeof(UINT32) * 127 * 31);
				memset((void *)&gHdmi21EyeDataCh1[port], 0, sizeof(UINT32) * 127 * 31);
				memset((void *)&gHdmi21EyeDataCh2[port], 0, sizeof(UINT32) * 127 * 31);
				memset((void *)&gHdmi21EyeDataCh3[port], 0, sizeof(UINT32) * 127 * 31);
				gHdmi21EyeXposition[port] = 0;
				gHdmi21EyeYposition[port] = 0;
				gHdmi21EyeStage[port] = 0;
				gHdmi21EyeMeasure[port] = 1;
				if(scaleMode > 0) gHdmi21EyeYPrintScale = 1;
				else gHdmi21EyeYPrintScale = 3;

				printk("Port[%d] : Eye measurement start! Scale 1/%d mode. About 1 min, or more\n", port, gHdmi21EyeYPrintScale);
			}

		}
		else if(mode == 2){
			if(gHdmi21EyeMeasure[port] == 1) {
				printk("Port[%d] : Abort Eye Measurement", port);
				gHdmi21EyeMeasure[port] = 0;
			}
			else {
				printk("Port[%d] : Nothing to abort. Status[%s]\n", port, gHdmi21EyeMeasure[port]?"Already Done":"Not performed");
			}
		}

		gHdmi21EyePrintMode = printMode;

	} while(0);

	return;
}

void HDMI21_HAL_Rx_DBG_GetCsEyeWidth(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	UINT32 __data = 0;
	UINT32 __reg  = 0;
	
	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		memset((void *)&gHdmi21CsEyeWidthCh0[port], 0, sizeof(UINT32) * 32);
		memset((void *)&gHdmi21CsEyeWidthCh1[port], 0, sizeof(UINT32) * 32);
		memset((void *)&gHdmi21CsEyeWidthCh2[port], 0, sizeof(UINT32) * 32);
		memset((void *)&gHdmi21CsEyeWidthCh3[port], 0, sizeof(UINT32) * 32);

		/* Ch 0 */
		__reg = 0x02; __reg = (__reg << 2); __data =  0x0; _p->phyDR_write(__reg, __data);
		for(i=0; i<32; i++){
			__reg = 0xD0 + i;
			__reg = (__reg << 2) + 0x400; gHdmi21CsEyeWidthCh0[port][i] = _p->phyDR_read(__reg);
		}

		/* Ch 1 */
		__reg = 0x02; __reg = (__reg << 2); __data =  0x1; _p->phyDR_write(__reg, __data);
		for(i=0; i<32; i++){
			__reg = 0xD0 + i;
			__reg = (__reg << 2) + 0x400; gHdmi21CsEyeWidthCh1[port][i] = _p->phyDR_read(__reg);
		}

		/* Ch 2 */
		__reg = 0x02; __reg = (__reg << 2); __data =  0x2; _p->phyDR_write(__reg, __data);
		for(i=0; i<32; i++){
			__reg = 0xD0 + i;
			__reg = (__reg << 2) + 0x400; gHdmi21CsEyeWidthCh2[port][i] = _p->phyDR_read(__reg);
		}

		/* Ch 3 */
		__reg = 0x02; __reg = (__reg << 2); __data =  0x3; _p->phyDR_write(__reg, __data);
		for(i=0; i<32; i++){
			__reg = 0xD0 + i;
			__reg = (__reg << 2) + 0x400; gHdmi21CsEyeWidthCh3[port][i] = _p->phyDR_read(__reg);
		}

	} while(0);

	return;
}

void HDMI21_HAL_Rx_DBG_PrintCsEyeWidth(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	
	do{
		if(port >= g_hdmi20_number_of_ports){
			printk("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		printk("   ========|========+++========|========+++========|========+++========|========\n");
		for(i=31; i>=0; i--)
		{
			printk("%02d %s|%s | %s|%s | %s|%s | %s|%s\n", i,\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh0[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh0[port][i] & 0x0F),\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh1[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh1[port][i] & 0x0F),\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh2[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh2[port][i] & 0x0F),\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh3[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh3[port][i] & 0x0F));
		}


	} while(0);

	return;
}

void HDMI21_HAL_Rx_PROC_PrintCsEyeWidth(UINT8 port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	
	do{
		if(port >= g_hdmi20_number_of_ports){
			seq_printf(m, "Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		_p = &gHDMI21RxHandler[port];

		seq_printf(m, "   ================================+++================================+++================================+++================================\n");
		for(i=31; i>=0; i--)
		{
			seq_printf(m, "%02d %s%s | %s%s | %s%s | %s%s\n", i,\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh0[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh0[port][i] & 0x0F),\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh1[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh1[port][i] & 0x0F),\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh2[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh2[port][i] & 0x0F),\
					__val_to_CsWidthGraphicNegative((gHdmi21CsEyeWidthCh3[port][i] & 0xF0)>> 4),\
					__val_to_CsWidthGraphicPositive(gHdmi21CsEyeWidthCh3[port][i] & 0x0F));
		}


	} while(0);

	return;
}

int HDMI21_HAL_Rx_Set_Initialize(LX_HDMI20_INIT_T *pData, int size, int isInternalCall)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p; 
	int i;
	int ret = RET_ERROR;

	HDMI20_INFO("Function called \n");

	do{
		if(gIsHDMI21KdrvOpen < 0){
			HDMI20_INFO("HDMI20 Not Opened yet.\n");
			break;
		}

		if(gIsHDMI21KdrvInitialized >= 0){
			HDMI20_ERROR("Ignore Multiple Initialize\n");
			ret = RET_OK;
			break;
		}

		/* Step 1. Check given args to proceed */
		if(isInternalCall > 0){
			/* Nothing to Check */
		}

		/* Step 2. Get User data to kernel*/
		if(isInternalCall > 0){
			/* Nothing to do */
		}

		/* Step 3. Open Rx */
		for(i = 0; i<g_hdmi20_number_of_ports; i++)
		{
			/* Step 3-1. Get Handler */
			_p = &gHDMI21RxHandler[i];
			HDMI20_INFO("Initialize LGE SIC HDMI2.1 Device Driver - Port[%d] \n", _p->port);
			/* Step 3-2. ESM Write DK/PUK */
		
			/* Step 3.3. Set SNPS Core/ISR unit settings */
			HDMI21_ISRUNIT_Rx_Initiate(_p);

			/* Step 3-3. Register Top IRQ */
			ret = HDMI21_IRQ_Rx_RequestTopIrq(_p);
			if( ret <0 ) { HDMI20_ERROR("Failed[%d] to request IRQ[%d] port[%d] Top Control\n", ret, _p->top_irq, _p->port); }
			else { HDMI20_INFO("Successfully requested IRQ[%d] for Port[%d] Top Control\n", _p->top_irq, _p->port);}

			/* Step 3-4. Register Link IRQ */
			ret = HDMI21_IRQ_Rx_RequestLinkIrq(_p);
			if( ret <0 ) { HDMI20_ERROR("Failed[%d] to request IRQ[%d] port[%d] Top Control\n", ret, _p->irq, _p->port); }
			else { HDMI20_INFO("Successfully requested IRQ[%d] for Port[%d] Top Control\n", _p->irq, _p->port);}

			/* Enable 5V IRQ */
			gHDMI21RxHandler[i].control_top_irq(1);

			/* Reset Link Engine */
			__HDMI21_HAL_Rx_Set_ResetLink(_p, 1);

			/* HPD Down */
			__HDMI21_HAL_Rx_Set_HPD(i, 0, 1);
		}

		/* Start HDMI Main thread(Checking video information on video transtion state) */
		gHDMI21Thread.isAlive = 1;
		gHDMI21Thread.pThread= kthread_create( (void *)__HDMI21_HAL_Rx_MainThread, 0, "hdmi21_rx_engine");
		if(gHDMI21Thread.pThread){
			HDMI20_INFO("Initialing VIDEO Stable checker thread\n");
			wake_up_process(gHDMI21Thread.pThread);
		}else HDMI20_ERROR("Cannot initiate Video stablizor thread\n");

		gIsHDMI21KdrvInitialized = 1;

		ret = RET_OK;
	} while(0);

	return ret;

}



int HDMI21_HAL_Rx_Set_HDCP22Info(UINT8 port, int isInitiated)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	int i;

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* TV lab wants us to set HDCP2.3 keys/history for all ports even it was called for only a specific port */
		for(i=0;i<g_hdmi20_number_of_ports;i++){
			/* Get Handler */
			_p = &gHDMI21RxHandler[i];

			HDMI20_INFO("Info[%d](called for [%d]) : HDCP2.3 path [%s]. Mode[%s]\n", _p->port, port, isInitiated?"Enabled":"Disabled", HDMI21_HDCP23_Module_Get_IsRepeater()?"Repeater":"Reciever");

			/* Set Flag */
			if(isInitiated > 0) {
				if(HDMI21_HDCP23_Module_Get_IsRepeater() > 0) {
					HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(_p, 2);
				}
				else {
					HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(_p, 1);
				}
			}
			else {
				HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(_p, isInitiated);
			}

			if(isInitiated > 0) {
				/* HDCP2.2 path : This will force HDCP2.2 engine to take ownership of data path */
				_p->top_write(0xFB0, 0x0);

			}
			else{
				_p->top_write(0xFB0, 0x1);
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_HAL_Rx_Set_EnableDscModule(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	UINT32 addr;
	UINT32 data;
	UINT32  __d = 0;

	mutex_lock(&__DSC_mutex);

	HDMI20_INFO("DSC : EnableDSC called for HDMI Port[%d]\n", port);

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Dev Handler */
		_p = &gHDMI21RxHandler[port];

		if (lx_chip_rev( ) >= LX_CHIP_REV( O26, A0)) {
			/* Address for O26 was the same with O24 */
			HDMI21_REG_WR(0xCC200018, 0x1); /* Defence Code : For PSLVERROR (PMCU_CPU)*/
		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)) {
			HDMI21_REG_WR(0xCC200018, 0x1); /* Defence Code : For PSLVERROR (PMCU_CPU) */
		}

		/* Set CTOP Clock setting per port */
		if  ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
			addr =	HDMI21_CHIP_O26_CRG_SETTING_REG;
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
			addr =	HDMI21_CHIP_O24_CRG_SETTING_REG;
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
			HDMI20_ERROR("Error! No DSC support for M23!\n");
			break;
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
			addr =	HDMI21_CHIP_O22_CRG_SETTING_REG;
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
			addr =	HDMI21_CHIP_E60_CRG_SETTING_REG;
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
			addr =	HDMI21_CHIP_O20_CRG_SETTING_REG;
		}
		else{ 
			/* TBA */
			break;
		}


		/* Start of DSC setting for HDMI Link */
		/* Below API will force FRL DSC sync width to const */
		HDMI21_VPROC_Rx_Set_LinkBypassForDSC(_p, 1, 1);

		/* Read CRG register */
		HDMI21_REG_RD(addr, data);

		/* Set data per port */
		switch(_p->port)
		{
			case 0:
				__d = 0x0;
				break;
			case 1:
				__d = 0x1;
				break;
			case 2:
				__d = 0x2;
				break;
			case 3:
				__d = 0x3;
				break;
			case 4:
				__d = 0x4;
				break;
			default:
				__d = 0x0;
				break;
		}

		if  ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
			data &= (0xFFFFFCEC);

			__d  = __d << 8;
			__d  &= (0x300);

			data |= __d;

			/* 2021/04/30 : Need to confirm this with DSC IP engineer */
			if(_p->hwVideo.video_format == 3) {
				data |= 0x11;
			}
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
			data &= (0xFFFFFCEC);

			__d  = __d << 8;
			__d  &= (0x300);

			data |= __d;

			/* 2021/04/30 : Need to confirm this with DSC IP engineer */
			if(_p->hwVideo.video_format == 3) {
				data |= 0x11;
			}
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
			data &= (0xFFFFCFEE);

			__d  = __d << 12;
			__d  &= (0x3000);

			data |= __d;

			/* 2021/04/30 : Need to confirm this with DSC IP engineer */
			if(_p->hwVideo.video_format == 3) {
				data |= 0x11;
			}
		}
		else if  ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
			/* E60 case : bit [11:10] at CRG register is clock selection for HDMI port 
			 * 			  Refer to share.lge.com O20 CVI_SYN register manual for further info*/
			/* 2020/03/09 : Choi.D.K : make sure that when in DSC mode, 17:14 has to be a value of 0 */

			data &= 0xFFFC33FF;
		
			__d  = __d << 10;
			__d &=  (~0xFFFFF3FF);

			data |= __d;

			/*2020/06/02 */
			if(_p->hwVideo.video_format == 3) {
				data |= 0x80004000;
			}
		}
		else {
			/* O20 case : bit [2:0] at CRG register is clock selection for HDMI port 
			 * 			  Refer to share.lge.com O20 CVI_SYN register manual for further info*/
			data &= 0xFFFFFFF8;
		
			data |= __d;
			data |= 0x200;

			#if 1 /* 2020/06/25 : Dont do this on O20 --> 2020/08/18 : Do this on O20...*/
			/*2020/06/02 */
			if(_p->hwVideo.video_format == 3) {
				data |= 0x00000010;
			}
			#endif
		}

		/* Write to CRG register */
		HDMI21_REG_WR(addr, data);


		/* 2020/06/22 : CRG2 setting */
		if((_p->hwVideo.video_format == 3) && (_p->isPqeSuspend == false) ) {
			if  ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
				addr = HDMI21_CHIP_O26_CRG2_SETTING_REG;
				HDMI21_REG_RD(addr, data);

				/* Clear for CVI A,D only. CVI D is for capture path purpose */
				/* 2021/07/15 : For F22, CVI A,B,C,D,E are all required to be set to 1 on 4:2:0's */
				data &= (~0x0000FFFF);
				data |= ( 0x00001111);

				HDMI21_REG_WR(addr, data);
			}
			else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
				addr = HDMI21_CHIP_O24_CRG2_SETTING_REG;
				HDMI21_REG_RD(addr, data);

				/* Clear for CVI A,D only. CVI D is for capture path purpose */
				/* 2021/07/15 : For F22, CVI A,B,C,D,E are all required to be set to 1 on 4:2:0's */
				data &= (~0x000FFFFF);
				data |= ( 0x00011111);

				HDMI21_REG_WR(addr, data);
			}
			else if  ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
				addr = HDMI21_CHIP_O22_CRG2_SETTING_REG;
				HDMI21_REG_RD(addr, data);

				/* Clear for CVI A,D only. CVI D is for capture path purpose */
				/* 2021/07/15 : For F22, CVI A,B,C,D,E are all required to be set to 1 on 4:2:0's */
				data &= (~0x000FFFFF);
				data |= ( 0x00011111);

				HDMI21_REG_WR(addr, data);
			}
			else if  ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
				addr = HDMI21_CHIP_E60_CRG2_SETTING_REG;
				HDMI21_REG_RD(addr, data);

				data &= (~0x60);
				data |= (0x40);
				HDMI21_REG_WR(addr, data);
			}
			else {
				addr = HDMI21_CHIP_O20_CRG2_SETTING_REG;
				HDMI21_REG_RD(addr, data);

				data &=(~0xF000F);
				data |=( 0x80008);

				HDMI21_REG_WR(addr, data);
			}
		}

		ret = HDMI21_DSC_Rx_Set_ExecuteDscModule(_p);

	} while(0);

	mutex_unlock(&__DSC_mutex);
	return ret;
}

//Return VFreq
int HDMI21_HAL_Rx_Get_VICtoVfreq(UINT32 vicCode){
	int ret = RET_ERROR;
	int _vc;

	do{
		/* Get VIC Code */
		_vc = vicCode;


		if((_vc == 60)||(_vc == 65)|| (_vc == 32)||(_vc == 72)||(_vc == 79)||(_vc == 86)||(_vc == 93)||(_vc == 103)||(_vc == 98)||(_vc == 121)\
				||(_vc == 194)||(_vc == 202)||(_vc == 210)){
			/* Field Rate Low : 24Hz */
			ret = 240;
		}
		else if((_vc == 61)||(_vc == 66)|| (_vc == 33)||(_vc == 73)||(_vc == 80)||(_vc == 87)||(_vc == 94)||(_vc == 104)||(_vc == 99)||(_vc==122)\
				||(_vc==195)||(_vc==203)||(_vc==211)){
			/* Field Rate Low : 25Hz */
			ret = 250;
		}
		else if((_vc == 62)||(_vc == 67)|| (_vc == 34)||(_vc == 74)||(_vc == 81)||(_vc == 88)||(_vc == 95)||(_vc == 105)||(_vc == 100)||(_vc == 123)\
				||(_vc==196)||(_vc==204)||(_vc==212)){
			/* Field Rate Low : 30Hz */
			ret = 300;
		}
		else if((_vc == 108)||(_vc == 109)||(_vc == 111)||(_vc == 112)||(_vc == 110)||(_vc == 113)||(_vc == 114)||(_vc == 116)||(_vc == 115)||(_vc == 124)\
				||(_vc==197)||(_vc==205)||(_vc==213)) {
			ret = 480;
		}
		else if((_vc == 17)||(_vc == 18)|| (_vc == 19)||(_vc == 68)||(_vc == 20)||(_vc == 21)||(_vc == 22)||(_vc == 23)||(_vc == 24)||(_vc == 25)||(_vc == 26)||\
				(_vc == 27)||(_vc == 28)||(_vc == 29)||(_vc == 30)||(_vc == 31)||(_vc == 75)||(_vc == 37)||(_vc == 38)||(_vc == 39)||(_vc == 82)||(_vc == 89)||\
				(_vc == 96)||(_vc == 106)||(_vc == 101)||(_vc==125)||(_vc==198)||(_vc==206)||(_vc==214)){
			
			/* Field Rate Low : 50Hz */
			ret = 500;
		}
		else if((_vc == 1)||(_vc == 2)|| (_vc == 3)||(_vc == 4)||(_vc == 69)||(_vc == 5)||(_vc == 6)||(_vc == 7)||(_vc == 8)||(_vc == 9)||(_vc == 10)||\
				(_vc == 11)||(_vc == 12)||(_vc == 13)||(_vc == 14)||(_vc == 15)||(_vc == 16)||(_vc == 76)||(_vc == 35)||(_vc == 36)||(_vc == 83)||(_vc == 90)||\
				(_vc == 97)||(_vc == 107)||(_vc == 102)||(_vc==126)||(_vc==199)||(_vc==207)||(_vc==215)){
			
			/* Field Rate Low : 50Hz */
			ret = 600;
		}
		else if( (_vc ==40)||(_vc ==41)||(_vc ==70)||(_vc ==42)||(_vc ==43)||(_vc ==44)||(_vc ==45)||(_vc ==64)||(_vc ==77)||(_vc ==84)||(_vc ==91)||\
				(_vc ==117)||(_vc ==119)||(_vc ==127)||(_vc ==200)||(_vc ==208)||(_vc ==216)||(_vc ==218)){
			ret = 1000;
		}
		else if( (_vc ==46)||(_vc ==47)||(_vc ==71)||(_vc ==48)||(_vc ==49)||(_vc ==50)||(_vc ==51)||(_vc ==63)||(_vc ==78)||(_vc ==85)||(_vc ==92)||\
				(_vc ==118)||(_vc ==120)||(_vc ==193)||(_vc ==201)||(_vc ==209)||(_vc ==217)||(_vc ==219)){
			ret = 1200;
		}		
		else if( (_vc == 52)||(_vc == 53)||(_vc==54)||(_vc==55)){
			ret = 2000;
		}
		else if((_vc == 56)||(_vc == 57)||(_vc == 58)||(_vc == 59)){
			ret = 2400;
		}
		else {
			ret = 0;
		}
	} while(0);

	return ret;
}

UINT32 HDMI21_HAL_Rx_Get_CompensateDignosticsVfreq(UINT32 tmds_clk, UINT32 vtotal, UINT32 htotal, bool interaced, UINT32 video_format)
{
	UINT32 __hvtotal = 0;
	UINT32 __vfreq = 0;
	UINT32 __is420 = 0;
	UINT32  __precision = 0;
	UINT32 __temp_vfreq = 0;
	UINT32 __temp_float = 0;

	if( video_format == 0x3 )
		__is420 = 1;
	
	//Calculate hvtotal
	if( interaced == true) {
		__hvtotal = ((vtotal >> 1)*(htotal >> __is420));
	} else {
		__hvtotal = (vtotal*(htotal >> __is420));
	}


	//Calculate Frame rate
	if( (__hvtotal != 0) && (__hvtotal > 100) ){
		__temp_vfreq = (tmds_clk * 1000) / __hvtotal; 
		__precision = ((tmds_clk * 1000)/(__hvtotal/100))%100;
		
		if( __temp_vfreq == 59 ){
			if( __precision > 94 ){
				__temp_vfreq = 60;	
			} else {
				__temp_vfreq = 59;
				__temp_float = 94;
			}
		} else if ( __temp_vfreq == 47 ) {
			if( __precision > 95 ){
				__temp_vfreq = 48;
			} else {
				__temp_vfreq = 47;
				__temp_float = 95;
			}
		} else if ( __temp_vfreq == 29 ) {
			if( __precision > 97 ){
				__temp_vfreq = 30;
			} else {
				__temp_vfreq = 29;
				__temp_float = 97;
			}
		} else if ( __temp_vfreq == 23 ) {
			if( __precision > 97 ){
				__temp_vfreq = 24;
			} else {
				__temp_vfreq = 23;
				__temp_float = 97;
			}
		}

		__vfreq = (__temp_vfreq * 100) + (__temp_float);
		HDMI21_LINE_DBG(1081, "V[%d], H[%d], HVT[%d], TMDS_CLK[%d], TEMP_VFREQ[%d], TEMP_FLOT[%d], VFREQ[%d]\n",
				vtotal, htotal, __hvtotal, tmds_clk, __temp_vfreq, __temp_float, __vfreq);
	} else {
		__vfreq = 0;
		HDMI21_LINE_DBG(1081, "VFREQ is zero.!\n");
	
	}


	return __vfreq;
}

int HDMI21_HAL_Rx_Get_VfreqFromHdmiRegForFRL(UINT8 port)
{
	int ret = -1;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 vfreq = 0;
	UINT32 vfreq_mon = 0;
	UINT32 vfreq_mon_nor = 0;

	int __t = 0;
	UINT32 vfreq_cvi = 0;
	UINT32 vfreq_cvi_nor = 0;

	HDMI21_VMON_VIDEO_SYNC_T _curr;
	UINT64 hvtotal;
	UINT64 vtotal;
	UINT64 htotal;
	UINT64 pixel_clk;
	UINT32 vfreq_cal = 0;

	do {
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0) ) {
			/* Only supported register from E60B0... */
			break;
		}

		/* 2025/04/08 : From O26.. we will use our new counter hardware..*/
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value >= 1) {
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		if(_p->phyInitiatedMode < HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			/* This API is for only FRL modes */
			break;
		}

		
		/* Read From register */
		vfreq_mon = (_p->top_read(0x600) & 0x0000FFFF);
		if((_p->top_read(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK)& 0xFFFF) == 0x30){
			if((vfreq_mon >= 15) && (vfreq_mon <= 18)){
				vfreq_mon_nor = 165;
			}
			else if((vfreq_mon >= 13) && (vfreq_mon <= 15)){
				vfreq_mon_nor = 144;
			}
			else if((vfreq_mon >= 11) && (vfreq_mon < 13)) {
				vfreq_mon_nor = 120;
			}
		}else if((_p->top_read(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK)& 0xFFFF) == 0x1E0){
			if((vfreq_mon >= 150) && (vfreq_mon <= 180)){
				vfreq_mon_nor = 165;
			}
			else if((vfreq_mon >= 130) && (vfreq_mon <= 150)){
				vfreq_mon_nor = 144;
			}
			else if((vfreq_mon >= 110) && (vfreq_mon < 130)) {
				vfreq_mon_nor = 120;
			}
		}

		/* Normalize */
		/* Case : 24/25/30/48/50/60/75/80/90/95/100/120/130/144/160/200/240 */
		/* Set VFreq counter ref clock */

		/* 1st : From CVI */
		__t = HDMI21_HAL_Rx_Get_FrameRateFromCVI_2nd(port);
		if(__t > 0) {
			vfreq_cvi = ((UINT64)__t) / 100;

			if((vfreq_cvi > 280) && (vfreq_cvi < 295)){
				vfreq_cvi_nor = 288;
				ret = 288 ;
			} else if((vfreq_cvi > 230) && (vfreq_cvi < 250)){
				vfreq_cvi_nor = 240;
				ret = 240 ;
			}else if((vfreq_cvi > 190) && (vfreq_cvi < 210)){
				vfreq_cvi_nor = 200;
				ret = 200 ;
			}else if((vfreq_cvi > 155) && (vfreq_cvi < 175)){
				vfreq_cvi_nor = 165;
				ret = 165 ;
			}else if((vfreq_cvi > 135) && (vfreq_cvi < 155)){
				vfreq_cvi_nor = 144;
				ret = 144 ;
			}else if((vfreq_cvi > 110) && (vfreq_cvi < 130)){
				vfreq_cvi_nor = 120;
				ret = 120 ;
			}else if((vfreq_cvi > 90) && (vfreq_cvi < 110)){
				vfreq_cvi_nor = 100;
				ret = 100 ;
			}else if((vfreq_cvi > 55) && (vfreq_cvi < 65)){
				vfreq_cvi_nor = 60;
				ret = 60 ;
			}else if((vfreq_cvi > 45) && (vfreq_cvi < 55)){
				vfreq_cvi_nor = 50;
				ret = 50 ;
			}else if((vfreq_cvi > 20) && (vfreq_cvi < 300)){
				vfreq_cvi_nor = vfreq_cvi;
				ret = vfreq_cvi ;
			}
			HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d(mon:%d, cvi:%d).\n",_p->port, ret, vfreq_mon, vfreq_cvi); 
		}

		if(ret < 0){
			/* 2nd : From monitor */
			ret = vfreq_mon_nor;
			HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d(mon:%d, cvi:%d).\n",_p->port, ret, vfreq_mon, vfreq_cvi); 
		}

		if(ret < 0){
			/* 3rd : From cal */
			HDMI21_VMON_Rx_Get_VideoSync(_p, &_curr);

			vtotal = (UINT64)_curr.vtotal; 
			htotal = (UINT64)_curr.htotal; 
			hvtotal = vtotal * htotal;
			
			if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) { /* FRL mode */
				if((hvtotal != 0)&&(gHDMI21RxHandler[port].isPhyLocked > 0)){
					pixel_clk = (_p->link_read(0x98)) * 1000 * 8;
					if(_p->hwVideo.video_format == 3){ // YcBcR420
						vfreq_cal = ( (pixel_clk + hvtotal) / (hvtotal*2));	//rounding
					}else{
						vfreq_cal = ((pixel_clk + (hvtotal >> 1))/ hvtotal);	//rounding
					}
				}else{
					vfreq = _p->hwVideo.vfreq;
					HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d.\n",_p->port, vfreq); 
				}

				if((vfreq_cal >= 150) && (vfreq_cal <= 180)){
					vfreq = 165;	
					HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d, vfreq_cal = %d(read_clk=%d, vt=%llu, ht=%llu), vfreq_mon = %d.\n",_p->port, vfreq, vfreq_cal, (_p->link_read(0x98)), vtotal, htotal, vfreq_mon); 
				}else if((vfreq_cal >= 130) && (vfreq_cal <= 150)){
					vfreq = 144;	
					HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d, vfreq_cal = %d(read_clk=%d, vt=%llu, ht=%llu), vfreq_mon = %d.\n",_p->port, vfreq, vfreq_cal, (_p->link_read(0x98)), vtotal, htotal, vfreq_mon); 
				}else if((vfreq_cal >= 110) && (vfreq_cal < 130)) {
					vfreq = 120;
					HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d, vfreq_cal = %d(read_clk=%d, vt=%llu, ht=%llu), vfreq_mon = %d.\n",_p->port, vfreq, vfreq_cal, (_p->link_read(0x98)), vtotal, htotal, vfreq_mon); 
				}else{
					vfreq = _p->hwVideo.vfreq;
				}
			}
			else { /* TMDS mode */
				if((hvtotal != 0)&&(gHDMI21RxHandler[port].isPhyLocked > 0)){
					vfreq_cal = (( ((UINT64)gHDMI21RxHandler[port].real_tmds_clk * 100000) + (hvtotal >> 1) ) / hvtotal);	//rounding
					vfreq = vfreq_cal;
				}
				else{
					vfreq = _p->hwVideo.vfreq;
				}
				HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d, vfreq_cal = %d(read_clk=%d, vt=%llu, ht=%llu).\n",_p->port, vfreq, vfreq_cal, (_p->link_read(0x98)), vtotal, htotal); 
			}
			
			ret = vfreq;
			//HDMI21_LINE_DBG(8461, "Notice [%d] : vfreq = %d, vfreq_cvi = %d.\n",_p->port, vfreq, vfreq_cvi); 
		}

		/* stable cnt initialize condition*/
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 9848){
			if(_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) {
				if((_p->video.vfreq != vfreq_cvi_nor) && (vfreq_cvi_nor >= 20)){
					HDMI20_INFO("Notice [%d] : Vfreq change after Stable(%d -> %d(cvi:%d)).\n",_p->port, _p->video.vfreq, vfreq_cvi_nor, vfreq_cvi); 
					_p->stable_cnt = 0;
					_p->video.vfreq = vfreq_cvi_nor;
				}else if((_p->video.vfreq != vfreq_mon_nor) && (vfreq_mon_nor >= 20) && (__t<=0)){
					HDMI20_INFO("Notice [%d] : Vfreq change after Stable(%d -> %d(mon:%d)).\n",_p->port, _p->video.vfreq, vfreq_mon_nor, vfreq_mon); 
					_p->stable_cnt = 0;
					_p->video.vfreq = vfreq_mon_nor;
				}
			}
		}
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_Get_VrrCurrentVfreq(UINT8 port, UINT16 *pData, int size, int isInternalCall)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	HDMI21_VMON_VIDEO_SYNC_T _curr;
	int __t = 0;
	UINT64 hvtotal;
	UINT64 vfreq;
	UINT64 vtotal;
	UINT64 htotal;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(UINT16)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(UINT32), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value >= 1) {
			vfreq = (UINT64)__HDMI21_HAL_Rx_Get_LinkTopVfreqCounter(_p, 1);
		}
		else {
			/* 1st priority is to get this from CVI */
			__t = HDMI21_HAL_Rx_Get_FrameRateFromCVI(port);
			if(__t <= 0) __t = HDMI21_HAL_Rx_Get_FrameRateFromCVI_2nd(port);

			if(__t > 0) {
				vfreq = (UINT64)__t;
			}
			else {
				if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) { /* FRL mode */
					/* O20 cannot support VRR freq counter for FRL */
					if(lx_chip_rev( ) >= LX_CHIP_REV( E60, B0) ) {
						vfreq = (UINT64)((_p->top_read(0x600) & 0x0000FFFF) * 100);
					}
					else {
						vfreq = (UINT64)(_p->real_vfreq * 100);
					}
				}
				else { /* TMDS mode */
					/* Get from VMON */
					HDMI21_VMON_Rx_Get_VideoSync(_p, &_curr);

					vtotal = (UINT64)_curr.vtotal; 
					htotal = (UINT64)_curr.htotal; 

					hvtotal = vtotal * htotal;

					if((hvtotal != 0)&&(gHDMI21RxHandler[port].isPhyLocked > 0)){
						vfreq = ((((UINT64)gHDMI21RxHandler[port].real_tmds_clk * 100000) + (hvtotal >> 1)) / hvtotal);
					}
					else{
						vfreq = 0;
					}
				}
			}

			HDMI21_LINE_DBG(8460, "DBG %d : Vfreq[%llu] / CVI Response[%d]\n", port, vfreq, __t);
		}

		if(isInternalCall) {
			memcpy((void *)pData, (void *)&vfreq, size);
		}
		else{
			ret = copy_to_user((void __user *)pData, (void *)&vfreq, size);
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "Vrr Vfreq", port);
				break;
			}
		}
		
		ret = RET_OK;
	} while(0);

	return ret;
}

void	HDMI21_HAL_Rx_Get_UpdateVrrMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 *pData)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT8 __t;

	do{
		/* Device Handler NULL defence */
		if(_p == NULL) {
			HDMI20_ERROR("Error : NULL Handler\n");
			break;
		}

		/* Null data defence */
		if(pData == NULL) {
			HDMI20_ERROR("Error[%d] : NULL pData\n", _p->port);
			break;
		}

		if(pData[1] == 0xC0){ 		// HB1: First/Last + Rsvd[5:0]
			/* Single EM Packet : VTEM */
			if(pData[2] == 0x00){	// HB2:Sequence Index
				
				/* PB0 : pData[3] -> PB0 = New / End / DS_Type / AFR / VFR / Sync / Rsvd(0) */
				/* PB1 : pData[4] -> Rsvd(0) */
				/* PB2 : pData[5] -> Organization ID a(0:Vendor Specific, 1:HDMI2.1 Spec, 2:CTA-861, 3:VESA)*/
				/* PB3 : pData[6] -> Data_Set_Tag(MSB) */
				/* PB4 : pData[7] -> Data_Set_Tag(LSB) */
				/* PB5 : pData[8] -> Data_Set_Length(MSB) */
				/* PB6 : pData[9] -> Data_Set_Length(LSB) */
				/* PB7(MD0) : pData[10] .... */
				/* Check VTEM */
				if((pData[5] == 0x01) && (pData[6] == 0x00) && (pData[7] == 0x01) && (pData[8] == 0x00) && (pData[9] == 0x04)){

					if((pData[3] & 0x3F) == 0x6) {	/* VTEM CLASS 1 */
						/* Keep track of VTEM Receive time */
						_p->em_qms_recieve_time = jiffies_to_msecs(jiffies);

						/* QMS Detection */
						if((pData[10] & 0x04) == 0x04){
							if(_p->isQmsMode == 0){
								/* Clear MConst Counter */
								_p->em_qms_mconst_zero_cnt = 0;

								HDMI21_LINE_DBG(5025, "ISR[%d] : EM QMS Mode[On]. MD1[0x%02x] MD2[0x%02x] MD3[0x%02x] MConst_Zero_Counter[%u]\n",\
										_p->port, (int)pData[11], (int)pData[12] ,(int)pData[13], _p->em_qms_mconst_zero_cnt); 
							}

							_p->isQmsMode = 1;
							_p->em_qms_tfr = (UINT32)(((pData[12] & 0xF8) >> 3) & 0x1F);
							
							_p->em_qms_baseRate = (UINT32)(((pData[12] & 0x3)<<6) & 0xC0);
							_p->em_qms_baseRate = (((_p->em_qms_baseRate << 2) & 0x300) | (UINT32)((pData[13]) & 0xFF));

							/* Make sure to reset VRR flag to zero */
							_p->isFreeSyncMode  = 0;
							_p->em_vrr_baseRate = 0;

							/* Get MConst */
							if((pData[10] & 0x2) == 0x2) {
								if(_p->isMConst == 0){
									HDMI20_ISR_PRINT("ISR[%d] : QMS MConst[On]. BaseRate[0x%02x] TFR[idx:%d][%s] MConst_Zero_Counter[%u]\n",\
											_p->port, _p->em_qms_baseRate, _p->em_qms_tfr, __tfr_to_str(_p->em_qms_tfr),_p->em_qms_mconst_zero_cnt); 
								}

								HDMI21_LINE_DBG(5026, "ISR[%d] : QMS MConst[On]. BaseRate[0x%02x] TFR[idx:%d][%s] MConst_Zero_Counter[%u]\n",\
										_p->port, _p->em_qms_baseRate, _p->em_qms_tfr, __tfr_to_str(_p->em_qms_tfr),_p->em_qms_mconst_zero_cnt); 

								_p->isMConst = 1;

								/* 2022/05/29 : Clear MConst Zero Counter */
								_p->em_qms_mconst_zero_cnt = 0;
							}
							else {
								/* 2022/05/29 : A favor for Apple TV team */
								_p->em_qms_mconst_zero_cnt++;

								if(_p->isMConst > 0){
									HDMI20_ISR_PRINT("ISR[%d] : QMS MConst[Off]. BaseRate[0x%02x] TFR[idx:%d][%s] MConst_Zero_Counter[%u]\n",\
											_p->port, _p->em_qms_baseRate, _p->em_qms_tfr, __tfr_to_str(_p->em_qms_tfr), _p->em_qms_mconst_zero_cnt); 
								}

								HDMI21_LINE_DBG(5026, "ISR[%d] : QMS MConst[Off]. BaseRate[0x%02x] TFR[idx:%d][%s] MConst_Zero_Counter[%u]\n",\
										_p->port, _p->em_qms_baseRate, _p->em_qms_tfr,  __tfr_to_str(_p->em_qms_tfr), _p->em_qms_mconst_zero_cnt); 

								_p->isMConst = 0;
							}
						}
						else{
							if(_p->isQmsMode > 0){
								HDMI20_ISR_PRINT("ISR[%d] : EM QMS Mode[Off]. MConst_Zero_Counter Val[%u]\n", _p->port, _p->em_qms_mconst_zero_cnt); 
								_p->isQmsMode = 0;
							}
							
							HDMI21_LINE_DBG(5026, "ISR[%d] : EM QMS Mode[Off] MConst_Zero_Counter Val[%u]\n", _p->port, _p->em_qms_mconst_zero_cnt); 
							
							_p->em_qms_mconst_zero_cnt = 0;
							_p->em_qms_baseRate = 0;
							_p->em_qms_tfr = 0;
							_p->isMConst = 0;
						}
					}
					else if((pData[3] & 0x3F) == 0x4) {	/* VTEM CLASS 0 */ 
						/* Keep track of VTEM Receive time */
						_p->em_vrr_recieve_time = jiffies_to_msecs(jiffies);

						/* VRR Detection */
						if((pData[10] & 0x01) == 0x01){
							if(_p->isFreeSyncMode == 0){
								HDMI20_ISR_PRINT("ISR[%d] : EM VRR Mode[On]. BaseVfront[0x%02x], BaseRate[0x%02x]\n", _p->port, (int)pData[11], (int)pData[13]); 
							}

							_p->isFreeSyncMode = 2;
							_p->em_vrr_baseRate = (((UINT32)(pData[12] & 0x03) << 8) | (UINT32)pData[13]);


							/* 2025/09/09 won.hur : Work around for SDOSTE-279 issue */
							if(gHDMI21RxDevLinkControler[HDMI21__LINK_WATCHDOG_VRR_VFREQ_WITH_MEASURE].value > 0 ) {
								if(HDMI21_HAL_Rx_Get_CheckVfreqBaseWithStableVfreq(_p) > 0) {
									HDMI20_INFO("Notice [%d] : Vfreq changed due to VRR base rate difference with vfreq_real\n", _p->port);
									_p->stable_cnt = 0;
								}
							}

						}
						else{
							if(_p->isFreeSyncMode == 2){
								HDMI20_ISR_PRINT("ISR[%d] : EM VRR Mode[Off]\n", _p->port); 
								_p->isFreeSyncMode = 0;
							}
							_p->em_vrr_baseRate = 0;

						}

						/* FVA Detection */
						if((pData[10] & 0xF0) != 0x0) {
							__t = (pData[10] & 0xF0);
							__t = (__t >> 4) & 0x0F;
							
							if(_p->isFvaMode == 0){
								HDMI20_ISR_PRINT("ISR[%d] : FVA Mode[On]. Value [%d] \n", _p->port, ((int)__t + 1)); 
							}

							_p->isFvaMode = (int)__t + 1;
						}
						else {

							if(_p->isFvaMode > 0){
								HDMI20_ISR_PRINT("ISR[%d] : FVA Mode[OFF]\n", _p->port); 
							}

							_p->isFvaMode = 0;
						}

						/* MConst Detection */
						if((pData[10] & 0x02) != 0x0) {
							_p->isMConst = 1;
						}
						else {
							_p->isMConst = 0;
						}

						/* QMSMode Detection : 2021/03/05 --> bit definition is not decided yet */
						#if 0
						if((pData[10] & 0x00) != 0x0) {
							_p->isQmsMode = 1;
						}
						else {
							_p->isQmsMode = 0;
						}
						#endif
					}
				}
			}
		}

	} while(0);

	return;
}

void 	HDMI21_HAL_Rx_Get_UpdateDscCvtemPpsData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	static UINT8 packet_data_save[HDMI21_NUM_OF_MAX_PORTS][13];				/* emp_cvtemPacket[13] ~ [25] */
	UINT32 __d = 0;
	UINT16 __c = 0;
	UINT8  __v = 0;
	UINT8  __f[2];

	do{
		/* Device Handler NULL defence */
		if(_p == NULL) {
			HDMI20_ERROR("Error : NULL Handler\n");
			break;
		}

		if(_p->isDSC == 1) 
		{
			if (_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value)
			{
				if((memcmp((UINT8 *)packet_data_save[_p->port], (UINT8 *)&_p->emp_cvtemPacket[13], 13)) != 0) {

					HDMI20_INFO("DSC[%d] : Detected CVTEM changed. From %13phC to  %13phC\n", _p->port,  packet_data_save[_p->port], &_p->emp_cvtemPacket[13]);

					_p->stable_cnt = 0;
					_p->stablehdcp14time = 0;
				}
			}

			memcpy((UINT8 *)packet_data_save[_p->port], (UINT8 *)&_p->emp_cvtemPacket[13], (13 * sizeof(UINT8)));
		}

		_p->pps.bits_per_component		=	((_p->emp_cvtemPacket[13] >> 4 ) & 0x0F);
		_p->pps.convert_rgb				=	((_p->emp_cvtemPacket[14] >> 4 ) & 0x01);
		_p->pps.simple_422				=	((_p->emp_cvtemPacket[14] >> 3 ) & 0x01);
		_p->pps.linebuf_depth			=	((_p->emp_cvtemPacket[13] >> 0 ) & 0x0F);
		__d = _p->emp_cvtemPacket[14] & 0x00000003; __d = __d << 8; __d |= _p->emp_cvtemPacket[15];
		_p->pps.bits_per_pixel			=	__d;
		_p->pps._block_pred_enable		=	((_p->emp_cvtemPacket[14] >> 5 ) & 0x01);
		_p->pps.native_420				=	((_p->emp_cvtemPacket[98] >> 1 ) & 0x01);
		_p->pps.native_422				=	((_p->emp_cvtemPacket[98] >> 0 ) & 0x01);
		_p->pps.dsc_version_minor		=	((_p->emp_cvtemPacket[10] >> 0 ) & 0x0F);

		__c = (UINT16)_p->emp_cvtemPacket[18]; __c = __c << 8; __c |= _p->emp_cvtemPacket[19];
		_p->pps.pic_width = __c;
		__c = (UINT16)_p->emp_cvtemPacket[16]; __c = __c << 8; __c |= _p->emp_cvtemPacket[17];
		_p->pps.pic_height = __c;
		__c = (UINT16)_p->emp_cvtemPacket[22]; __c = __c << 8; __c |= _p->emp_cvtemPacket[23];	
		_p->pps.slice_width = __c;
		__c = (UINT16)_p->emp_cvtemPacket[20]; __c = __c << 8; __c |= _p->emp_cvtemPacket[21];
		_p->pps.slice_height = __c;
		__c = (UINT16)_p->emp_cvtemPacket[24]; __c = __c << 8; __c |= _p->emp_cvtemPacket[25];
		_p->pps.chunk_size = __c;

		/* initial_xmit_delay */
		__d = _p->emp_cvtemPacket[26] & 0x00000003; __d = __d << 8; __d |= _p->emp_cvtemPacket[27];
		_p->pps.initial_xmit_delay		=	__d;

		__c = (UINT16)_p->emp_cvtemPacket[28]; __c = __c << 8; __c |= _p->emp_cvtemPacket[29];
		_p->pps.initial_dec_delay = __c;
		_p->pps.initial_scale_value		=	((_p->emp_cvtemPacket[31] ) & 0x3F);
		__c = (UINT16)_p->emp_cvtemPacket[32]; __c = __c << 8; __c |= _p->emp_cvtemPacket[33];
		_p->pps.scale_increment_interval = __c;
		
		/* scale_decrement_interval */
		__d = _p->emp_cvtemPacket[34] & 0x000000FF; __d = __d << 8; __d |=  _p->emp_cvtemPacket[35];
		_p->pps.scale_decrement_interval=	__d;

		_p->pps.first_line_bpg_offset	=	((_p->emp_cvtemPacket[37]) & 0x1F);
		_p->pps.second_line_bpg_offset	=	((_p->emp_cvtemPacket[99]) & 0x1F);

		__c = (UINT16)_p->emp_cvtemPacket[38]; __c = __c << 8; __c |= _p->emp_cvtemPacket[39];		
		_p->pps.nfl_bpg_offset = __c;
		__c = (UINT16)_p->emp_cvtemPacket[40]; __c = __c << 8; __c |= _p->emp_cvtemPacket[41];
		_p->pps.slice_bpg_offset = __c;
		__c = (UINT16)_p->emp_cvtemPacket[42]; __c = __c << 8; __c |= _p->emp_cvtemPacket[43];		
		_p->pps.initial_offset = __c;
		__c = (UINT16)_p->emp_cvtemPacket[44]; __c = __c << 8; __c |= _p->emp_cvtemPacket[45];	
		_p->pps.final_offset = __c;
		__c = (UINT16)_p->emp_cvtemPacket[100]; __c = __c << 8; __c |= _p->emp_cvtemPacket[101];		
		_p->pps.nsl_bpg_offset = __c;
		__c = (UINT16)_p->emp_cvtemPacket[102]; __c = __c << 8; __c |= _p->emp_cvtemPacket[103];
		_p->pps.second_line_offset_adj = __c;

		_p->pps.flatness_min_qp			=	((_p->emp_cvtemPacket[46]) & 0x1F);		
		_p->pps.flatness_max_qp			=	((_p->emp_cvtemPacket[47]) & 0x1F);		
		//_p->pps.flatness_det_thresh		=	((_p->emp_cvtemPacket[] >> ) & 0x00);
		_p->pps.flatness_det_thresh		=	0; /* 2019/07/01 : there is no such thing in DSC PPS spec */
		__c = (UINT16)_p->emp_cvtemPacket[48]; __c = __c << 8; __c |= _p->emp_cvtemPacket[49];		
		_p->pps.rc_model_size = __c;
		
		_p->pps.rc_edge_factor			=	((_p->emp_cvtemPacket[50]) & 0x0F);		
		_p->pps.rc_quant_incr_limit0	=	((_p->emp_cvtemPacket[51]) & 0x1F);
		_p->pps.rc_quant_incr_limit1	=	((_p->emp_cvtemPacket[52]) & 0x1F);
		_p->pps.rc_tgt_offset_hi		=	((_p->emp_cvtemPacket[53] >> 4) & 0x0F);		
		_p->pps.rc_tgt_offset_lo		=	(_p->emp_cvtemPacket[53]);		
		_p->pps.rc_buf_thresh_0			=	(_p->emp_cvtemPacket[54]);		
		_p->pps.rc_buf_thresh_1			=	(_p->emp_cvtemPacket[55]);		
		_p->pps.rc_buf_thresh_2			=	(_p->emp_cvtemPacket[56]);		
		_p->pps.rc_buf_thresh_3			=	(_p->emp_cvtemPacket[57]);		
		_p->pps.rc_buf_thresh_4			=	(_p->emp_cvtemPacket[58]);		
		_p->pps.rc_buf_thresh_5			=	(_p->emp_cvtemPacket[59]);		
		_p->pps.rc_buf_thresh_6			=	(_p->emp_cvtemPacket[60]);		
		_p->pps.rc_buf_thresh_7			=	(_p->emp_cvtemPacket[61]);		
		_p->pps.rc_buf_thresh_8			=	(_p->emp_cvtemPacket[62]);		
		_p->pps.rc_buf_thresh_9			=	(_p->emp_cvtemPacket[63]);		
		_p->pps.rc_buf_thresh_10		=	(_p->emp_cvtemPacket[64]);		
		_p->pps.rc_buf_thresh_11		=	(_p->emp_cvtemPacket[65]);		
		_p->pps.rc_buf_thresh_12		=	(_p->emp_cvtemPacket[66]);		
		_p->pps.rc_buf_thresh_13		=	(_p->emp_cvtemPacket[67]);		
		_p->pps.rc_range_parameters_0_range_min_qp		=	((_p->emp_cvtemPacket[68] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_1_range_min_qp		=	((_p->emp_cvtemPacket[70] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_2_range_min_qp		=	((_p->emp_cvtemPacket[72] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_3_range_min_qp		=	((_p->emp_cvtemPacket[74] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_4_range_min_qp		=	((_p->emp_cvtemPacket[76] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_5_range_min_qp		=	((_p->emp_cvtemPacket[78] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_6_range_min_qp		=	((_p->emp_cvtemPacket[80] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_7_range_min_qp		=	((_p->emp_cvtemPacket[82] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_8_range_min_qp		=	((_p->emp_cvtemPacket[84] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_9_range_min_qp		=	((_p->emp_cvtemPacket[86] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_10_range_min_qp		=	((_p->emp_cvtemPacket[88] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_11_range_min_qp		=	((_p->emp_cvtemPacket[90] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_12_range_min_qp		=	((_p->emp_cvtemPacket[92] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_13_range_min_qp		=	((_p->emp_cvtemPacket[94] >> 3) & 0x1F);		
		_p->pps.rc_range_parameters_14_range_min_qp		=	((_p->emp_cvtemPacket[96] >> 3) & 0x1F);		


		__f[1] = _p->emp_cvtemPacket[68]; __f[0] = _p->emp_cvtemPacket[69]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_0_range_max_qp		=	__v;	
		__f[1] = _p->emp_cvtemPacket[70]; __f[0] = _p->emp_cvtemPacket[71]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_1_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[72]; __f[0] = _p->emp_cvtemPacket[73]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_2_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[74]; __f[0] = _p->emp_cvtemPacket[75]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_3_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[76]; __f[0] = _p->emp_cvtemPacket[77]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_4_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[78]; __f[0] = _p->emp_cvtemPacket[79]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_5_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[80]; __f[0] = _p->emp_cvtemPacket[81]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_6_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[82]; __f[0] = _p->emp_cvtemPacket[83]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_7_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[84]; __f[0] = _p->emp_cvtemPacket[85]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_8_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[86]; __f[0] = _p->emp_cvtemPacket[87]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_9_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[88]; __f[0] = _p->emp_cvtemPacket[89]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_10_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[90]; __f[0] = _p->emp_cvtemPacket[91]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_11_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[92]; __f[0] = _p->emp_cvtemPacket[93]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_12_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[94]; __f[0] = _p->emp_cvtemPacket[95]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_13_range_max_qp		=	__v;		
		__f[1] = _p->emp_cvtemPacket[96]; __f[0] = _p->emp_cvtemPacket[97]; memcpy((void *)&__d, (void *)&__f, sizeof(UINT8) * 2); __d = __d >> 6; __d &= 0x1F; __v = (UINT8)__d; 
		_p->pps.rc_range_parameters_14_range_max_qp		=	__v;	

		_p->pps.rc_range_parameters_0_range_bpg_offset	=	((_p->emp_cvtemPacket[69]) & 0x3F);	
		_p->pps.rc_range_parameters_1_range_bpg_offset	=	((_p->emp_cvtemPacket[71]) & 0x3F);	
		_p->pps.rc_range_parameters_2_range_bpg_offset	=	((_p->emp_cvtemPacket[73]) & 0x3F);	
		_p->pps.rc_range_parameters_3_range_bpg_offset	=	((_p->emp_cvtemPacket[75]) & 0x3F);	
		_p->pps.rc_range_parameters_4_range_bpg_offset	=	((_p->emp_cvtemPacket[77]) & 0x3F);	
		_p->pps.rc_range_parameters_5_range_bpg_offset	=	((_p->emp_cvtemPacket[79]) & 0x3F);	
		_p->pps.rc_range_parameters_6_range_bpg_offset	=	((_p->emp_cvtemPacket[81]) & 0x3F);	
		_p->pps.rc_range_parameters_7_range_bpg_offset	=	((_p->emp_cvtemPacket[83]) & 0x3F);	
		_p->pps.rc_range_parameters_8_range_bpg_offset	=	((_p->emp_cvtemPacket[85]) & 0x3F);	
		_p->pps.rc_range_parameters_9_range_bpg_offset	=	((_p->emp_cvtemPacket[87]) & 0x3F);	
		_p->pps.rc_range_parameters_10_range_bpg_offset	=	((_p->emp_cvtemPacket[89]) & 0x3F);	
		_p->pps.rc_range_parameters_11_range_bpg_offset	=	((_p->emp_cvtemPacket[91]) & 0x3F);	
		_p->pps.rc_range_parameters_12_range_bpg_offset	=	((_p->emp_cvtemPacket[93]) & 0x3F);	
		_p->pps.rc_range_parameters_13_range_bpg_offset	=	((_p->emp_cvtemPacket[95]) & 0x3F);	
		_p->pps.rc_range_parameters_14_range_bpg_offset	=	((_p->emp_cvtemPacket[97]) & 0x3F);	
	} while(0);

	return;

}


void	HDMI21_HAL_Rx_Get_UpdateAllmMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 *pData)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int i;

	do{
		/* Device Handler NULL defence */
		if(_p == NULL) {
			HDMI20_ERROR("Error : NULL Handler\n");
			break;
		}

		/* Null data defence */
		if(pData == NULL) {
			HDMI20_ERROR("Error[%d] : NULL pData\n", _p->port);
			break;
		}

		/* For Debug Purpose. Print Packet */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 3904){
			for(i=0;i<3;i++){
				HDMI20_DBG("[HB%02d] - [  0x%02x  ]\n",i, pData[i]);
			}

			for(i=3;i<(HDMI21_MAX_DATA_PACKET_LENGTH - 3); i++){
				HDMI20_DBG("[ B%02d] - [  0x%02x  ]\n",(i-3), pData[i]);
			}
		}

		/* Check */
		if((pData[4] == 0xD8) && (pData[5] == 0x5D) && (pData[6] == 0xC4)){
			if(pData[7] == 0x01){
				if((pData[8] & 0x02) == 0x02) {
					if(_p->isAllmMode == 0){
						HDMI20_INFO("Notice [%d] : Detected ALLM Mode[On].\n",_p->port); 
					}
					_p->isAllmMode = 1;
					_p->allm_recieve_time = jiffies_to_msecs(jiffies);
				}
				else{
					if(_p->isAllmMode == 1){
						HDMI20_INFO("Notice [%d] : Detected ALLM Mode[Off]\n", _p->port); 
					}
					_p->isAllmMode = 0;
					_p->allm_recieve_time = 0;
				}
			}
		}
		else{
			/* Not a HF-VSIF */
			HDMI21_LINE_DBG(3904, "DBG[%d] : Checked, but not ALLM VSIF\n", _p->port); 
		}
	} while(0);

	return;
}


/* IOCTL */
int HDMI21_HAL_Rx_Set_HDMIFactor(LX_HDMI20_SETTING_FACTOR_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI20_SETTING_FACTOR_T data;
	UINT32 temp;

	HDMI20_VIDEO("[%s] called\n", __F__);

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_SETTING_FACTOR_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_SETTING_FACTOR_T), size);
			break;
		}

		if(isInternalCall) {
			memcpy((void *)&data, (void *)pData, sizeof(LX_HDMI20_SETTING_FACTOR_T));
		}
		else {
			if( copy_from_user(&data, (void __user *)pData, sizeof(LX_HDMI20_SETTING_FACTOR_T))){
				HDMI20_ERROR("Cannot copy HDMI Factor data structure from user\n");
				break;
			}
		}

		HDMI20_VIDEO("[%s] : Factor[%d], value[%d][%d][%d]\n", __F__, data.type, data.value1, data.value2, data.value3);
		
		ret = RET_OK;
		
		switch(data.type)
		{
			case LX_HDMI20_SETTING_HPD_LOW_DURATION :
				{
					/* Do Nothing */
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_MODE :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH0 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH1 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH2 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_EQ_PERIOD :
				{
					/* No such thing in O20 */
				}
				break;
			case LX_HDMI20_SETTING_VIDEO_STABLE_COUNT :
				{
					if(data.value1 >= 50){
						temp = data.value1 - 50;
					}
					else{
						temp = 50 - data.value1;
					}

					if(data.value1 == 50){
						gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value = HDMI21_HAL_VIDEO_CHECK_CNT;
					}
					else if(data.value1 > 50){
						gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value += (temp / (HDMI21_HAL_INITIAL_THREAD_SLEEP_MS / 10));
					}
					else if(data.value1 < 50){
						if(gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value >= (temp / (HDMI21_HAL_INITIAL_THREAD_SLEEP_MS / 10))){
							gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value -= (temp / (HDMI21_HAL_INITIAL_THREAD_SLEEP_MS / 10));
						}
						else{
							gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value = 0;
						}
					}
				}
				break;
			case LX_HDMI20_SETTING_AUDIO_STABLE_COUNT :
				{
					if(data.value1 >= 50){
						temp = data.value1 - 50;
					}
					else{
						temp = 50 - data.value1;
					}

					if(data.value1 == 50){
						gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value = HDMI21_AUDIO_STABLE_CNT_INITIAL;
						gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE].value = (HDMI21_AUDIO_STABLE_CNT_INITIAL - 1);
					}
					else if(data.value1 > 50){
						gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value += (temp / (HDMI21_HAL_INITIAL_THREAD_SLEEP_MS / 10));
						gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE].value = gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value - 1;

					}
					else if(data.value1 < 50){
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value >= ((temp / (HDMI21_HAL_INITIAL_THREAD_SLEEP_MS / 10)) + 2)){
							gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value -= (temp / (HDMI21_HAL_INITIAL_THREAD_SLEEP_MS / 10));
							gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE].value = gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value - 1;
						}
						else{
							gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value = 2;
							gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE].value = 1;
						}
						
					}
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT0 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI21RxHandler[0].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI21RxHandler[0].gWasHDCP22FuncCalled > 0){
							gHDMI21RxHandler[0].gWasHDCP22Written = gHDMI21RxHandler[0].gWasHDCP22FuncCalled; 
						}
					} 
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT1 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI21RxHandler[1].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI21RxHandler[1].gWasHDCP22FuncCalled > 0){
							gHDMI21RxHandler[1].gWasHDCP22Written = gHDMI21RxHandler[1].gWasHDCP22FuncCalled; 
						}
					} 
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT2 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI21RxHandler[2].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI21RxHandler[2].gWasHDCP22FuncCalled > 0){
							gHDMI21RxHandler[2].gWasHDCP22Written = gHDMI21RxHandler[2].gWasHDCP22FuncCalled; 
						}
					} 
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT3 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI21RxHandler[3].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI21RxHandler[3].gWasHDCP22FuncCalled > 0){
							gHDMI21RxHandler[3].gWasHDCP22Written = gHDMI21RxHandler[3].gWasHDCP22FuncCalled; 
						}
					}
				}
				break;
			case LX_HDMI20_SETTING_ON_TO_RXSENSE_TIME :
				{
					/* Not implemented */
				}
				break;
			case LX_HDMI20_SETTING_RXSENSE_TO_HPD_TIME :
				{
					gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_MODE :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH0 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH1 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH2 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_MODE :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P1_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH0 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH1 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH2 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_MODE :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P2_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH0 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH1 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH2 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_MODE :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P3_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH0 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH1 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH2 :
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH3:
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH3:
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH3:
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH3:
				{
					gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value = data.value1;
				}
				break;
			default :
				ret = RET_ERROR;
				break;
		}

	} while(0);

	return ret;
}


void HDMI21_HAL_Rx_Set_CoreResetWithMask(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 mask)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	__data = mask;

	/* Defence */
	if(_p == NULL) return;

	HDMI21_LINE_DBG(7166, "DBG %d : Core Reset with Mask[0x%08x].Caller[%pS]\n", _p->port, mask, __builtin_return_address(0));

	if( (__data & HDMI21_SNPS_RST_MAIN) != 0) 		HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_MAIN);
	if( (__data & HDMI21_SNPS_RST_AVPUNIT) != 0) 	HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_AVPUNIT);
	if( (__data & HDMI21_SNPS_RST_AUDIO) != 0) {
		HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_AUDIO);
		/* 2020/06/29 : Request from Taejun.Lee */
		HDMI21_HAL_Rx_Set_AudioReset(_p->port);
	}
	if( (__data & HDMI21_SNPS_RST_HDCP) != 0) 		HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_HDCP);
	if( (__data & HDMI21_SNPS_RST_PKTFIFO) != 0) 	HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_PKTFIFO);
	if( (__data & HDMI21_SNPS_RST_DATAPATH) != 0) 	{
		/* Reset INPUT FIFO */
		_p->top_write(0xa00, gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_HIGH_VAL].value);
		_p->top_write(0xa00, gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_LOW_VAL].value);	
		HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_DATAPATH);
	}
	if( (__data & HDMI21_SNPS_RST_CEC) != 0) 	HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_CEC);
	if( (__data & HDMI21_SNPS_RST_APB) != 0) 	HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_APB);
	if( (__data & HDMI21_SNPS_RST_PHYCTRL) != 0) 	HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_PHYCTRL);
	if( (__data & HDMI21_SNPS_RST_EARCTX) != 0) 	HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_EARCTX);
	if( (__data & HDMI21_SNPS_RST_DATAPATHONLY) != 0) HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_DATAPATHONLY);
	if( (__data & HDMI21_SNPS_RST_HDCPQP) != 0)  HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_HDCPQP);

}

int HDMI21_HAL_Rx_Set_LowPowerMode(UINT8 port, bool isLowPower, bool isReset, int step)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	UINT32 __cJiffiesMsec = 0;
	UINT32 __timeSaved = 0;
	UINT32 __data, __reg;
	UINT32 __r3c, __r3d, __d3c, __d3d;
	UINT32 __t300;
	UINT32 __r8b, __d8b;
	UINT32 __rf, __r10, __r11, __r12,  __r18, __r19, __r1a, __r1b;
	UINT32 __df, __d10, __d11, __d12,  __d18, __d19, __d1a, __d1b;
	UINT32 __r6, __d6;
	
	int __isError = 0;

	do {
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Reset Case */
		if(isReset) {		
			/* Same for O26 */
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){ /* For O26 & O24 */
				HDMI20_INFO("INFO[%d] : Initialize Low Power Functionals\n", port);	

				/* FS Module Sync Setting */
				_p->top_write(0x32C, gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value);
				_p->top_write(0x328, 0x0);

				_p->lowPowerMode = HDMI21_HAL_POWER_NORMAL;
				_p->lowPowerTimeStamp = 0;
				_p->isLowPowerTransState = 0;
				_p->isForceRestore = FALSE;
				_p->accumulatedLowPowerTime = 0;
				ret = RET_OK;
				break;
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
				HDMI20_INFO("INFO[%d] : Initialize Low Power Functionals\n", port);	

				/* FS Module Sync Setting */
				_p->top_write(0x32C, gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value);
				_p->top_write(0x328, 0x0);


				_p->lowPowerMode = HDMI21_HAL_POWER_NORMAL;
				_p->lowPowerTimeStamp = 0;
				_p->isLowPowerTransState = 0;
				_p->accumulatedLowPowerTime = 0;
				ret = RET_OK;
				break;
			}
			else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				HDMI20_INFO("INFO[%d] : Initialize Low Power Functionals\n", port);	

				/* FS Module Sync Setting */
				_p->top_write(0x32C, gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value);
				_p->top_write(0x328, 0x0);


				/* 2021/11/15 : Jinwoo Choi */
				_p->top_write(0x334, 0x2200200);

				_p->lowPowerMode = HDMI21_HAL_POWER_NORMAL;
				_p->lowPowerTimeStamp = 0;
				_p->isLowPowerTransState = 0;
				_p->accumulatedLowPowerTime = 0;
				ret = RET_OK;
				break;
			}
			else {
				/* FS Module Sync Setting */
				_p->top_write(HDMI21_TOP_REG_AD_FS_3, 0x707);
				_p->top_write(HDMI21_TOP_REG_AD_FS_4, 0x023001E0);

				/* Reset FS module : Set High*/
				__data = HDMI21_TOP_FIELD_AD_FS_1_MODULE_RESET;
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);

				HDMI20_INFO("INFO[%d] : Initialize Low Power Functionals\n", port);	

				/* Reset FS module : Set Low */
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, 0);

				_p->lowPowerMode = HDMI21_HAL_POWER_NORMAL;
				_p->lowPowerTimeStamp = 0;
				_p->isLowPowerTransState = 0;
				_p->accumulatedLowPowerTime = 0;
				ret = RET_OK;
				break;
			}
		}

		/* Defence Case */
		if(_p->lowPowerMode <= HDMI21_HAL_POWER_UNINITIATED)
		{
			HDMI20_ERROR("Error! Port[%d] needs to initiate Low Power mode\n", port);
			break;
		}

		/* Set */
		if(step == 0) {
			if(isLowPower)  {
				if(_p->lowPowerMode == HDMI21_HAL_POWER_NORMAL) {
					/* For O26 & O24 : Address for PHY TMDS/CED Error registers are identical among those two SoCs */
					if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){ 
						__r18 = 0x18; __r18 = __r18 << 2; __d18 = _p->phyDR_read(__r18);
						__r19 = 0x19; __r19 = __r19 << 2; __d19 = _p->phyDR_read(__r19);
						__r1a = 0x1a; __r1a = __r1a << 2; __d1a = _p->phyDR_read(__r1a);
						__r1b = 0x1b; __r1b = __r1b << 2; __d1b = _p->phyDR_read(__r1b);
						
						if(((_p->top_read(0x300) & 0xF) != 0xF) && ((_p->top_read(0x324) & 0x80000000) != 0x80000000) && ((__d18 == 0) && (__d19 == 0) && (__d1a == 0) && (__d1b == 0) )) {
							HDMI20_INFO("INFO[%d] : LowPower Step0 is being stalled. [0x300] : [0x%08x], [0x324] : [0x%08x], Phy0x38 [0x18] : [0x%08x], [0x19] : [0x%08x], [0x1A] : [0x%08x], [0x1B] : [0x%08x] \n", \
							_p->port, _p->top_read(0x300), _p->top_read(0x324), __d18, __d19, __d1a, __d1b);
						}
						else{
							HDMI20_INFO("INFO[%d] : Low Power Mode activated Sequence.\n", port);

							if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 8291){
								/* Set override for GCP Color Depth, because FS module cannot replicate data packets */
								HDMI21_VPROC_Rx_Set_OverRideColorDepth(_p, 1,(HDMI21_RX_VPROC_CD_TYPE_T)_p->hwVideo.deep_color_mode);
							}

							__HDMI21_HAL_Rx_Set_LowPowerSettingStep0(_p, 1);
							_p->isLowPowerTransState++;
						}						
					}else{
						HDMI20_INFO("INFO[%d] : Low Power Mode activated Sequence.\n", port);

						if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 8291){
							/* Set override for GCP Color Depth, because FS module cannot replicate data packets */
							HDMI21_VPROC_Rx_Set_OverRideColorDepth(_p, 1, (HDMI21_RX_VPROC_CD_TYPE_T)_p->hwVideo.deep_color_mode);
						}

						__HDMI21_HAL_Rx_Set_LowPowerSettingStep0(_p, 1);
						_p->isLowPowerTransState++;
					}
				}
				else {
					/* Already in low power mode */
					__cJiffiesMsec = jiffies_to_msecs(jiffies);
					__timeSaved = __cJiffiesMsec - _p->lowPowerTimeStamp;
					HDMI20_WARN("WARN[%d] : Already in low power mode. Power-saved time [%u] msec. Total [%u] msec saved\n",\
							port, __timeSaved, (_p->accumulatedLowPowerTime + __timeSaved));
				}
			}
			else {
				if(_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER) {
					/* Calculate Power save time */
					__cJiffiesMsec = jiffies_to_msecs(jiffies);
					__timeSaved = __cJiffiesMsec - _p->lowPowerTimeStamp;
					_p->accumulatedLowPowerTime += (__cJiffiesMsec - _p->lowPowerTimeStamp);
					
					HDMI20_INFO("INFO[%d] : Low Power Mode Deactivate Sequence. Saved Time [%u] msec.\n", port, __timeSaved);
					
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep0(_p, 0);

					/* For O26 & O24 : Address for PHY TMDS/CED Error registers and Retimer registers are identical among those two SoCs */
					if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){ 

						/* PHY status check*/
						
						__rf  = 0x0f; __rf	= (__rf  << 2); __df  = _p->phyDR_read(__rf); // 0x38
						__r10 = 0x10; __r10 = (__r10 << 2); __d10 = _p->phyDR_read(__r10); // 0x38 
						__r11 = 0x11; __r11 = (__r11 << 2); __d11 = _p->phyDR_read(__r11); // 0x38
						__r12 = 0x12; __r12 = (__r12 << 2); __d12 = _p->phyDR_read(__r12); // 0x38

						__r18 = 0x18; __r18 = __r18 << 2; __d18 = _p->phyDR_read(__r18); // 0x38
						__r19 = 0x19; __r19 = __r19 << 2; __d19 = _p->phyDR_read(__r19); // 0x38
						__r1a = 0x1a; __r1a = __r1a << 2; __d1a = _p->phyDR_read(__r1a); // 0x38
						__r1b = 0x1b; __r1b = __r1b << 2; __d1b = _p->phyDR_read(__r1b); // 0x38

						if(_p->isForceRestore == FALSE){
							if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L){
								if((((__df & 0xF0) >= 0x30) && ((__df & 0xF0) < 0x70)) && (((__d10 & 0xF0) >= 0x30) && ((__d10 & 0xF0) < 0x70))\
									&& (((__d11 & 0xF0) >= 0x30) && ((__d11 & 0xF0) < 0x70))){
									HDMI20_INFO("Info[%d] : Lowpower Restore Step0 -> Step1 Success. PHY0x38 0xF <= [0x%08x], 0x10 <= [0x%08x], 0x11 <= [0x%08x]\n", _p->port, __df, __d10, __d11);
									_p->isLowPowerTransState++;
								}
								else{
									__r6 = 0x6; __r6 = (__r6 << 2) + 0x400; __d6 = _p->phyDR_read(__r6);	// 0x48
									//__d6 = (__d6  & 0x70);
									if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
										__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x80) );	// 0x48
										__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6) );			// 0x48
									}else{ /* FRL Modes */
										__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x8) );	// 0x48
										__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x88) );	// 0x48
										__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x8) );	// 0x48
										__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6) );			// 0x48
									}
									HDMI20_INFO("Info[%d] : Lowpower Restore Step0 -> Step1 Fail. PHY reset! PHY0x38 0xF <= [0x%08x], 0x10 <= [0x%08x], 0x11 <= [0x%08x]\n", _p->port, __df, __d10, __d11);
								}
							}
							else if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_6G_4L){
								if((((__df & 0xF0) >= 0x30) && ((__df & 0xF0) < 0x70)) && (((__d10 & 0xF0) >= 0x30) && ((__d10 & 0xF0) < 0x70))\
									&& (((__d11 & 0xF0) >= 0x30) && ((__d11 & 0xF0) < 0x70))&& (((__d12 & 0xF0) >= 0x30) && ((__d12 & 0xF0) < 0x70))){
									HDMI20_INFO("Info[%d] : Lowpower Restore Step0 -> Step1 Success. PHY0x38 0xF <= [0x%08x], 0x10 <= [0x%08x], 0x11 <= [0x%08x], 0x12 <= [0x%08x]\n", _p->port, __df, __d10, __d11, __d12);
									_p->isLowPowerTransState++;
								}
								else{
									__r6 = 0x6; __r6 = (__r6 << 2) + 0x400; __d6 = _p->phyDR_read(__r6);	// 0x48
									//__d6 = (__d6  & 0x70);
									__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x8) );	// 0x48
									__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x88) );	// 0x48
									__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6 | 0x8) );	// 0x48
									__reg = 0x6; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, (__d6) );			// 0x48
									HDMI20_INFO("Info[%d] : Lowpower Restore Step0 -> Step1 Fail. PHY reset! PHY0x38 0xF <= [0x%08x], 0x10 <= [0x%08x], 0x11 <= [0x%08x], 0x12 <= [0x%08x]\n", _p->port, __df, __d10, __d11, __d12);
								}
							}
						}else{
							HDMI20_INFO("Info[%d] : Force Lowpower Restore Step0 -> Step1 Success.\n", _p->port);
							_p->isLowPowerTransState++;
						}
						
					}else{
						_p->isLowPowerTransState++;
					}

				}
				else {
					/* Already in Normal Mode */
					HDMI20_WARN("WARN[%d] : Already in normal mode\n", port);
				}
			}
		}
		else if(step == 1) {
			if(isLowPower)  {			
				/* For O26 & O24 : Identical for those two SoCs with Low Power settings */
				if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 1);
					_p->isLowPowerTransState++;
				}
				else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){			
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 1);
					_p->isLowPowerTransState++;
				}
				else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					if(((_p->top_read(0x300) & 0xF) != 0xF) && ( HDMI21_HAL_Rx_Get_HDCPStatus(_p->port) > 0)) {
						HDMI20_INFO("INFO[%d] : LowPower Step1 is being stalled due to REG[0x300] not in condition[0x%08x]\n", _p->port, _p->top_read(0x300));
					}
					else {
						/* Check for Sync Error only for TMDS Modes */
						if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
							/* Check Sync Err Status */
							if(((_p->top_read(0x30C) & 0xFFFF0000) != 0x0) && ((_p->top_read(0x310) == 0x0))){
								HDMI20_INFO("INFO[%d] : LowPower Step1 is being stalled due to 0x30C[0x%08x]/0x310[0x%08x] not in condition\n",\
										_p->port, _p->top_read(0x30C), _p->top_read(0x310)); 

								/* Start from begining */
								HDMI20_INFO("INFO[%d] : Go back to Step 1\n", _p->port);
								_p->lowPowerMode = HDMI21_HAL_POWER_LOWPOWER;
								_p->isLowPowerTransState = 0;
								_p->idleTick = 0;
							}
							else {
								__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 1);
								_p->isLowPowerTransState++;
							}
						}
						else { /* FRL Modes */
							__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 1);
							_p->isLowPowerTransState++;
						}
					}
				}
				else {
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 1);
					_p->isLowPowerTransState++;
				}
			}
			else {		
				/* For O26 & O24 : Identical for those two SoCs with Low Power settings */
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
					/* Do Nothing */	

					__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 0);
					_p->isLowPowerTransState++;
				}
				else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
					/* Do Nothing */	

					__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 0);
					_p->isLowPowerTransState++;
				}
				else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					/* Read Video Status */
					__r3c = 0x3c; __r3c = (__r3c << 2); __d3c = _p->phyDR_read(__r3c);
					__r3d = 0x3d; __r3d = (__r3d << 2); __d3d = _p->phyDR_read(__r3d);
					__r8b = 0x8b; __r8b = (__r8b << 2) + 0x400; __d8b = _p->phyDR_read(__r8b);

					__rf  = 0x0f; __rf  = (__rf  << 2); __df  = _p->phyDR_read(__rf); 
					__r10 = 0x10; __r10 = (__r10 << 2); __d10 = _p->phyDR_read(__r10); 
					__r11 = 0x11; __r11 = (__r11 << 2); __d11 = _p->phyDR_read(__r11); 

					__df = ((__df >> 4) & 0xF);
					__d10 = ((__d10 >> 4) & 0xF);
					__d11 = ((__d11 >> 4) & 0xF);

					__isError = 0;

					if((__df == 0x0) || (__df == 0x1) || (__df == 0x7))
					{
						__isError |= 0x1;
					}

					if((__d10 == 0x0) || (__d10 == 0x1) || (__d10 == 0x7))
					{
						__isError |= 0x10;
					}


					if((__d11 == 0x0) || (__d11 == 0x1) || (__d11 == 0x7))
					{
						__isError |= 0x100;
					}

					/* Read Link Status */
					__data = _p->link_read(0x594);

					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
						__data &= 0xF;
					}
					else {
						__data = __data >> 9; __data &= 0xF;

						if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_6G_4L) {
							/* Do Nothing */	
						}
						else if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
							__data |= 0x8;
						}
						else {
							__data = 0xF;
						}
					}

					if( (HDMI21_HAL_Rx_Get_HDCPStatus(_p->port) >= 20 ) && (gHDMI21RxDevVideoControler[HDMI21__VIDEO_FS_CONSIDER_HDCP2X_CASE].value > 0)){
						if((__data == 0xF) && ((__d3d != 0) && (__d3c != 0)) && ((__d8b & 0x40) == 0x40) && (__isError == 0) ) {
							HDMI20_INFO("INFO[%d] : Link is stable proceed Step 1 for low power deactivation. PHY 3C[0x%x] 3D[0x%x] 48:8B[0x%x]\n", _p->port, __d3c, __d3d, __d8b);

							if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
								/* 2021/11/15 : JIN WOO CHOI */
								//_p->top_write(0x32c, 0x0);
								HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_DISCONNECT);
							}

							__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 0);
							_p->isLowPowerTransState++;
						}
						else {
							HDMI20_INFO("INFO[%d] : Link Not Stable for Step1 of deactivation. Link[0x594]=[0x%08x] PHY 3C[0x%x] 3D[0x%x] 48:8B[0x%x] __isError[0x%x]\n", _p->port, _p->link_read(0x594), __d3c, __d3d, __d8b, __isError);
							if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
								HDMI21_LINE_DBG(12001, "INFO[%d] : Reset PHY due to restore from Low Power Mode.[0x28]:[0x1] 01->11\n", _p->port);
								__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

								__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);

								HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #2 : PHY[0x28]:[0x6] 11->01->11\n", _p->port);
								__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

								HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #3 : PHY[0x28]:[0x1] 11->01\n", _p->port);
								__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
							}
							else {
								/* DR ANALOG CH0-3 Reset */
								__reg = 0x01; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
								__data &= (~0x80); _p->phyDR_write(__reg, __data);
								HDMI20_INFO("INFO[%d] : PHY DR Reset for CH0~3\n", _p->port);
								__data |= (0x80); _p->phyDR_write(__reg, __data);
							}
						}
					}
					else {
						__t300 = _p->top_read(0x300);

						if((__data == 0xF) && ((__d3d != 0) && (__d3c != 0)) && ((__t300 & 0xF) == 0xF) && ((__d8b & 0x40) == 0x40) && (__isError == 0)) {
							HDMI20_INFO("INFO[%d] : Link is stable proceed Step 1 for low power deactivation. PHY 3C[0x%x] 3D[0x%x] T0x300[0x%08x] 48:8B[0x%x]\n",_p->port, __d3c, __d3d, __t300, __d8b);
							if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
								/* 2021/11/15 : JIN WOO CHOI */
								//_p->top_write(0x32c, 0x0);
							HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_DISCONNECT);
							}

							__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 0);
							_p->isLowPowerTransState++;
						}
						else {
							HDMI20_INFO("INFO[%d] : Link Not Stable for Step1 of deactivation. Link[0x594]=[0x%08x] PHY 3C[0x%x] 3D[0x%x] T0x300[0x%08x]  48:8B[0x%x] isError[0x%x]\n", _p->port, _p->link_read(0x594), __d3c, __d3d, __t300, __d8b, __isError);
							_p->top300Count++;

							if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */

								if(_p->top300Count > gTop300ResetCnt) {
									#if 0
									__reg = 0x01; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
									__data &= (~0x80); _p->phyDR_write(__reg, __data);
									
									HDMI20_INFO("INFO[%d] : PHY DR ANR Reset \n", _p->port);
									__data |= (0x80); _p->phyDR_write(__reg, __data);
									#endif

									/* 2021/11/18 */
									__reg = 0x06; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xD3);
									__reg = 0x06; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x53);

									_p->top300Count = 0;
								}
								else {
									HDMI20_INFO("INFO[%d] : Waiting Top 0x300 register! Count=%d\n", _p->port, _p->top300Count);
								}
							}
							else {
								/* DR ANALOG CH0-3 Reset */
								__reg = 0x01; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
								__data &= (~0x80); _p->phyDR_write(__reg, __data);
								HDMI20_INFO("INFO[%d] : PHY DR Reset for CH0~3\n", _p->port);
								__data |= (0x80); _p->phyDR_write(__reg, __data);
							}
						}
					}

				}
				else {
					if((_p->link_read(0x594) & 0xF) != 0xF) {
						HDMI20_WARN("WARN[%d] : Low Power Release Step 1 will not be called due to Link 0x594 [3:0] status[0x%x]\n", _p->port, _p->link_read(0x594));
						#if 0
						/* PHY RESET Sequence */
						HDMI21_LINE_DBG(6400, "DBG[%d] : Reset PHY due to restore from Low Power Mode.[0x28]:[0x1] 01->11\n", _p->port);
						__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);


						__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
						HDMI21_LINE_DBG(6400, "DBG[%d] : PHY Reset #2 : PHY [0x28]:[0x6] 11->01->11\n", _p->port);
						__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

						HDMI21_LINE_DBG(6400, "DBG[%d] : PHY Reset #3 : PHY[0x28]:[0x1] 11->01\n", _p->port);
						__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
						#else
						HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
						#endif
					}
					else {
						__HDMI21_HAL_Rx_Set_LowPowerSettingStep1(_p, 0);
						_p->isLowPowerTransState++;
					}
				}
			}
		}
		else if(step == 2) {
			if(isLowPower) {
				/* For O26 & O24 : Identical for those two SoCs with Low Power settings */
				if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
					HDMI20_INFO("INFO[%d] : Low Power Mode activated. \n", port);
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
						if((_p->top_read(0x300) & 0x8F) != 0x8F){
							HDMI20_INFO("INFO[%d] : LowPower Step2 is being stalled due to REG[0x300] not in condition[0x%08x]\n", _p->port, _p->top_read(0x300));
						}else{
							__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 1);
							//_p->isLowPowerTransState = 0;
							_p->isLowPowerTransState++;
						}
					}else{	/* FRL Modes */
						__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 1);
						//_p->isLowPowerTransState = 0;
						_p->isLowPowerTransState++;
					}
				
				}	
				else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){			
					if((_p->top_read(0x300) & 0x700) >= 0x300) {
						HDMI20_INFO("INFO[%d] : Low Step1 is good to proceed. 0x300[0x%08x]\n", _p->port, _p->top_read(0x300));
						
						HDMI20_INFO("INFO[%d] : Low Power Mode activated. \n", port);
						__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 1);
						_p->isLowPowerTransState = 0;
					}
					else {
						HDMI20_INFO("INFO[%d] : LowPower Step1 is being stalled due to 0x300[0x%08x] not in condition\n",\
								_p->port, _p->top_read(0x300)); 
					}
				}	
				else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
						if(((_p->top_read(0x300) & 0xF) != 0xF) || ((_p->isHDCP22 > 0) && ((_p->top_read(0x324) & 0x2) != 0x2))){
							HDMI20_INFO("INFO[%d] : Low Power Mode Step2(TMDS) condition not met! 0x300[0x%08x] isHDCP22[%d] 0x324[0x%08x]\n",\
									_p->port, _p->top_read(0x300), _p->isHDCP22, _p->top_read(0x324));

							HDMI20_INFO("INFO[%d] : Start from beginning\n", _p->port);
							/* Start from begining */
							_p->lowPowerMode = HDMI21_HAL_POWER_LOWPOWER;
							_p->isLowPowerTransState = 0;
							_p->idleTick = 0;
						}
						else {
							HDMI20_INFO("INFO[%d] : Low Power Mode activated. \n", port);
							__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 1);
							_p->isLowPowerTransState = 0;
						}
					}
					else { /* FRL Modes */
						/* Get 31:16 of 0x31C */
						__data = _p->top_read(0x31C); __data = ((__data >> 16) & 0xFFFF);

						if((__data == (_p->top_read(0x31C) & 0xFFFF)) || ( __data == ((_p->top_read(0x31C) & 0xFFFF) + 1))){
							HDMI20_INFO("INFO[%d] : Low Power Mode activated. 0x31C[0x%08x]\n", port, _p->top_read(0x31C));
							__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 1);
							_p->isLowPowerTransState = 0;
						}
						else {
							HDMI20_INFO("INFO[%d] : Low Power Mode Step2 Condition not met!! 0x31C[0x%08x]\n", port, _p->top_read(0x31C)); 

							/* Start from begining */
							_p->lowPowerMode = HDMI21_HAL_POWER_LOWPOWER;
							_p->isLowPowerTransState = 0;
							_p->idleTick = 0;
						}
					}

				}
				else {
					/* Time stamp of when low power mode was activated */
					_p->lowPowerTimeStamp = jiffies_to_msecs(jiffies);

					__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 1);

					HDMI20_INFO("INFO[%d] : Low Power Mode activated.\n", port);
					_p->isLowPowerTransState = 0;
					_p->isForceRestore = FALSE;
				}
			}
			else {

				/* Calculate Power save time */
				__cJiffiesMsec = jiffies_to_msecs(jiffies);
				__timeSaved = __cJiffiesMsec - _p->lowPowerTimeStamp;
				_p->accumulatedLowPowerTime += (__cJiffiesMsec - _p->lowPowerTimeStamp);
				HDMI20_INFO("INFO[%d] : Low Power Mode Deactivated. Saved Time [%u] msec. Total Accumulated save time [%u] msec\n",\
						port, __timeSaved, _p->accumulatedLowPowerTime);

				/* For O26 & O24 : Identical for those two SoCs with Low Power settings */
				if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
						__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 0);
						_p->isLowPowerTransState++;
					}else{	/* FRL Modes */	
						if(((_p->top_read(0x300) & 0xF) != 0xF) && ((_p->top_read(0x324) & 0x80000000) != 0x80000000) && (_p->isForceRestore == FALSE)) {
							HDMI20_INFO("INFO[%d] : Restore to Normal mode Step2 is being stalled due to REG[0x300] not in condition[0x%08x]\n", _p->port, _p->top_read(0x300));
						}else{
							__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 0);
							_p->isLowPowerTransState++;
						}
					}
				}else{
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep2(_p, 0);
					_p->isLowPowerTransState = 0;
				}

				/* Restore GCP Color Depth Override */
				HDMI21_VPROC_Rx_Set_OverRideColorDepth(_p, 0, 0);
			}
		}
		else if(step == 3) {
			if(isLowPower) {	
				if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep3(_p, 1);
					_p->isLowPowerTransState++;
				}else{	/* FRL Modes */
					if((_p->top_read(0x300) & 0x40) != 0x40){
						HDMI20_INFO("Info[%d] : Lowpower Step2 -> Step3 Fail. Top 0x300 <= [0x%08x]\n", _p->port, _p->top_read(0x300));
					}
					else{
							__HDMI21_HAL_Rx_Set_LowPowerSettingStep3(_p, 1);
							_p->isLowPowerTransState++;
					}
				}
			}else{
				if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
					__HDMI21_HAL_Rx_Set_LowPowerSettingStep3(_p, 0);
					_p->isLowPowerTransState++;
				}else{	/* FRL Modes */
					if(((_p->top_read(0x300) & 0xF) != 0xF) && (_p->isForceRestore == FALSE)){
						HDMI20_INFO("Info[%d] : Restore to Normal mode Step2 -> Step3 Fail. Top 0x300 <= [0x%08x]\n", _p->port, _p->top_read(0x300));
					}
					else{
						__HDMI21_HAL_Rx_Set_LowPowerSettingStep3(_p, 0);
						_p->isLowPowerTransState++;
					}
				}
			}
		}
		else if(step == 4) {
			if(isLowPower) {			
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep4(_p, 1);
			}else{
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep4(_p, 0);
			}
			_p->isLowPowerTransState++;
		}
		else if(step == 5) {
			if(isLowPower) {			
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep5(_p, 1);
			}else{
				__HDMI21_HAL_Rx_Set_LowPowerSettingStep5(_p, 0);
			}
			_p->isLowPowerTransState = 0;
			_p->isForceRestore = FALSE;
		}
		
		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_Get_IsMyPortMainWindow(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 __t;

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(lx_chip_rev( ) >= LX_CHIP_REV( O26, A0)){
		/* Read CVI Reg */
			HDMI21_REG_RD(HDMI21_PQE_O26_SRC_INPUT_SEL, __t);

			/* Bit select for CVI SRC SEL */
			__t &= (HDMI21_PQE_O26_SRC_INPUT_SEL_BIT);
			__t = __t >> 14;
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)){
		/* Read CVI Reg */
			HDMI21_REG_RD(HDMI21_PQE_O24_SRC_INPUT_SEL, __t);

			/* Bit select for CVI SRC SEL */
			__t &= (HDMI21_PQE_O24_SRC_INPUT_SEL_BIT);
			__t = __t >> 14;
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV( M23, A0)){
			/* Not Yet */
			break;
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV( O22, A0)){
		/* Read CVI Reg */
			HDMI21_REG_RD(HDMI21_PQE_O22_SRC_INPUT_SEL, __t);

			/* Bit select for CVI SRC SEL */
			__t &= (HDMI21_PQE_O22_SRC_INPUT_SEL_BIT);
			__t = __t >> 14;
		}
		else {
			/* O20 & E60 */
			/* Read CVI Reg */
			HDMI21_REG_RD(HDMI21_PQE_O20_SRC_INPUT_SEL, __t);

			/* Bit select for CVI SRC SEL */
			__t &= (HDMI21_PQE_O20_SRC_INPUT_SEL_BIT);
			__t = __t >> 14;
		}

		switch(port)
		{
			case 0:
				if(__t == 0x0) { ret = RET_OK;}
				break;
			case 1:
				if(__t == 0x2) { ret = RET_OK;}
				break;
			case 2:
				if(__t == 0x4) { ret = RET_OK;}
				break;
			case 3:
				if(__t == 0x6) { ret = RET_OK;}
				break;
			case 4:
				if(__t == 0xA) { ret = RET_OK;}
				break;
			default:
				break;
		}

	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_Get_FrameRateFromCVI(UINT8 port)
{
	int ret = -1;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	unsigned int __t;

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* 2025/04/29 won.hur : From SJ.YOUM */
		if(_p->isPqeSuspend > 0) {
			break;
		}

		/* Check whether current port is main or not*/
		if(HDMI21_HAL_Rx_Get_IsMyPortMainWindow(port) != RET_OK) {
			break;
		}

		/* Check Whether Current port is in VRR mode */
		if(_p->isFreeSyncMode <= 0) {
			break;
		}

		/* Get Vfreq from DE */
		if(vsc_check_vrr_freq(&__t) < 0) {
			break;
		}

		/* Convert to Int */
		ret = (int)__t;

	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_Set_ZombieMode(UINT8 port, bool isZombie)
{
	int ret = -1;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		HDMI20_INFO("Info[%d] : [%s] Zombie Mode\n", port, isZombie?"Enable":"Disable");	

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Set Value */
		if(isZombie)	{	_p->zombieMode = 1;}
		else 			{	_p->zombieMode = 0;}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_Get_ZombieMode(UINT8 port)
{
	int ret = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Set Value */
		if(_p->zombieMode != 0)	{	
			ret = 1;
		}
	} while(0);

	return ret;
}


int HDMI21_HAL_Rx_Get_CheckVfreqBaseWithStableVfreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;

	do {
		/* Null pointer check */
		if(_p == NULL) break;

		/* Only Check when stable video */
		if(_p->stable_cnt <= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) break;

		/* Only check when in FRL modes */
		if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) <= HDMI21_HAL_PHY_INITIATED_6G) break;

		/* Only with non-VIC signals to prevent side-effects */
		if(_p->hwVideo.vicCode != 0) break;

		/* Let this code only work on VRR modes. isFreeSync=0 means that this is not VRR signal */
		if(_p->isFreeSyncMode == 0) break;

		/* Check and ring the alarm when real_vfreq does not match with vrr base vfreq info */
		if((_p->isFreeSyncMode == 2) && (_p->em_vrr_baseRate != 0)) {
			/* EM VRR/GSync Case */
			if( _p->real_vfreq != _p->em_vrr_baseRate) ret = 1;
		}
		else if((_p->isFreeSyncMode == 1) && (_p->vfreq_max != 0)) {
			if( _p->real_vfreq != _p->vfreq_max) ret = 1;
		}

		if(ret > 0) {
			HDMI20_ISR_PRINT("ISR[%d] : Warning! real_vfreq[%u] differs with VRR_Base[%u]\n", _p->port, _p->real_vfreq, _p->em_vrr_baseRate); 
		}

	} while(0);

	return ret;
}


/* -------------------------------------------------------------------------------
 * Static Function below this line
 * ------------------------------------------------------------------------------- */
static int __HDMI21_HAL_Rx_Set_PioneerMode(void)
{
	/* For PIONEER Platform, send up original timing info */
	HDMI20_INFO(" Set HDMI21 Driver to PIONEER Mode\n");

	/* FLAG update */
	gHDMI20PlatformType = LX_HDMI20_PLATFORM_PIONEER;

	/* No Low Power Mode for Pioneer */
	gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 0;

	if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
		/* O24 */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 3000;
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(6, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ) {
		/* O24 */
		gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value = 3000;
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(5, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ) {
		/* M23 */
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(4, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
		/* E60/O22... */
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(3, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);	
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ) {
		/* E60/O22... */
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(2, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports);	
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(1, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports - 1);	
	}
	else{
		HDMI21_HAL_Rx_Set_HDCP22Info(0, 1);
		HDMI21_HDCP23_Module_TestApp(0, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
		gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value = (g_hdmi20_number_of_ports - 1);	
	}


	return RET_OK;
}

static void __HDMI21_HAL_Rx_WatchDog_PixelPackingPhase(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_RX_VPROC_PP_PHASE_TYPE_T __linkPpValue;
	HDMI21_RX_VPROC_PP_PHASE_TYPE_T __gcpPpValue;
	UINT8 __gcp;

	do{
		/* Run Only for FRL modes.. because this issue was only found on FRL modes */
		if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
			HDMI21_LINE_DBG(6538, "DBG[%d] : PixelPackingPhase SWWA would not work on TMDS modes\n", _p->port);
			break;
		}

		/* Do not run watchdog on non-HDMI modes */
		if(_p->hwVideo.dvi) {
			HDMI21_LINE_DBG(6538, "DBG[%d] : PixelPackingPhase SWWA would not work on DVI modes\n", _p->port);
			break;
		}

		/* Do not run watchdog on override status */
		if(HDMI21_VPROC_Rx_Get_OverRidePixelPackingPhase(_p) > 0) {
			HDMI21_LINE_DBG(6538, "DBG[%d] : PixelPackingPhase SWWA would not work on DVI modes\n", _p->port);
			break;
		}

		/* Only operate SWWA if DefaultPhase is active in GCP packet */
 		__gcp  = _p->dataPacket[HDMI21_DISLAND_DATA__GCP][5];
 		__gcp &= (0x01); 

		if(__gcp != 0) {
			/* Check Link PixelPacking Phase Value */
			__linkPpValue = HDMI21_VPROC_Rx_Get_PixelPackingPhase(_p);

			/* Check GCP PixelPacking Phase Value */
			__gcp  = _p->dataPacket[HDMI21_DISLAND_DATA__GCP][4];
			__gcp &= (0xF0); __gcp = __gcp >> 4;

			if(__gcp == 0) 			__gcpPpValue = HDMI21_RX_VPROC_PP_PHASE_4;
			else if(__gcp == 1)		__gcpPpValue = HDMI21_RX_VPROC_PP_PHASE_1;
			else if(__gcp == 2)		__gcpPpValue = HDMI21_RX_VPROC_PP_PHASE_2;
			else if(__gcp == 3)		__gcpPpValue = HDMI21_RX_VPROC_PP_PHASE_3;
			else {
				/* Unknwon GCP Packet PP value type : Abort */
				break;
			}

			if(__gcpPpValue != __linkPpValue) {
				HDMI20_INFO("Warning [%d] : PixelPackingType misMatch! Link[%d] != GCP[%d]. Set to Override!\n", _p->port, __linkPpValue, __gcpPpValue);
				HDMI21_VPROC_Rx_Set_OverRidePixelPackingPhase(_p, 1, __gcpPpValue);
			}
			else {
				HDMI21_LINE_DBG(6538, "DBG[%d] : PixelPackingPhase SWWA would not work on normal conditions. link[%d]/GCP[%d]\n", _p->port, __linkPpValue, __gcpPpValue);
			}
		}

	} while(0);

	return;
}


static void __HDMI21_HAL_Rx_WatchDog_PhyConfig(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_HAL_PHY_INITIATED_MODE_T _mode;
	
	if((gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value > 0) && gHDMI21RxDevVideoControler[HDMI21__VIDEO_TRIGGER_SCDC_CHG_WATCHDOG].value == 0){
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 3939){
			HDMI20_DBG(" Disable Update SCDC on Port[%d]\n", _p->port);
		}

		_p->scdc_change = false;
		return;
	}

	if(gHDMI21RxDevVideoControler[HDMI21__LINK_ENABLE_SCDC_POLL_TRIG].value > 0){
		_mode = __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p);

		HDMI21_LINE_DBG(2734, "DBG[%d] : Phy Mode[%d] SCDCTmdsMode[%d]\n", _p->port, _p->phyInitiatedMode, _mode);

		if((_p->frlRateRcv > 0) && (_mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)) {
			HDMI20_INFO("WATCHDOG[%d] : Detect SCDC FRL Rate Transaction. Previous[%s] => Current[%s]\n",\
					_p->port, phymode_type_to_str(_p->phyInitiatedMode), phymode_type_to_str(_mode));
			HDMI21_HAL_Rx_Set_ScdcMode(_p->port, 1);
		}
		
		if(_p->phyInitiatedMode != _mode ){
			if(_p->frlRateRcv > 0) {
				HDMI20_INFO("WATCHDOG[%d] : Detected SCDC Rate Transaction. Previous[%s] => Current[%s]\n",\
						_p->port, phymode_type_to_str(_p->phyInitiatedMode), phymode_type_to_str(_mode));
				HDMI21_HAL_Rx_Set_ScdcMode(_p->port, 1);
			}
			else {
				HDMI20_INFO("WATCHDOG[%d] : Detected SCDC mode change by Polling. Previous[%s] => Current[%s]\n",\
						_p->port, phymode_type_to_str(_p->phyInitiatedMode), phymode_type_to_str(_mode));
				HDMI21_HAL_Rx_Set_ScdcMode(_p->port, 0);
			}
		}
	
		/* 20210914 : Make sure to clean up _p->frlRateRcv due to prventing unnessessary duplicate PHY API calls */
		_p->frlRateRcv = 0;
	}
}




static int __HDMI21_HAL_Rx_Set_InverseHPDControl(UINT8 port, int isInverse)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return ret;
	}

	_p = &gHDMI21RxHandler[port];

	HDMI20_VIDEO("Notice %d : Set HPD Polarity [%s]\n", _p->port, isInverse?"Inverse":"Normal");

	do{
		if(isInverse) { _p->isHPDInverseMode = true;  }
		else 		  { _p->isHPDInverseMode = false; }

		ret = RET_OK;
	} while(0);

	return ret;
}

static void __HDMI21_HAL_Rx_DBG_PrintSync(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler,  UINT8 diffmode)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_VMON_VIDEO_SYNC_T _curr;
	
	memset((UINT32 *)&_curr, 0, (sizeof(HDMI21_VMON_VIDEO_SYNC_T)));

	/* Read Current Sync from VIDEO MONITOR */
	HDMI21_VMON_Rx_Get_VideoSync(_p, &_curr);

	/* Do not compare isEvenFrame, isField1 */
	_curr.isEvenFrame = 0;
	_curr.isField1 = 0;

	if(diffmode >=1 ){

		if(memcmp((void *)&gPrevSync[_p->port],  (void *)&_curr, sizeof(HDMI21_VMON_VIDEO_SYNC_T))!= 0){

			HDMI20_DBG(" DBG[%d] Prev : Inter[%d] H(S[%d]F[%d]BLANK[%d]BACK[%d]T[%d]A[%d]) == V(S[%d]F[%d]BLANK[%d]BACK[%d]T[%d]A[%d])\n",\
					_p->port, gPrevSync[_p->port].isInterlaced,\
					gPrevSync[_p->port].hsync, gPrevSync[_p->port].hfront, gPrevSync[_p->port].hblank, gPrevSync[_p->port].hback,\
					gPrevSync[_p->port].htotal,gPrevSync[_p->port].hactive,\
					gPrevSync[_p->port].vsync, gPrevSync[_p->port].vfront, gPrevSync[_p->port].vblank,gPrevSync[_p->port].vback,\
					gPrevSync[_p->port].vtotal,gPrevSync[_p->port].vactive);
			HDMI20_DBG(" DBG[%d] Current : Inter[%d] H(S[%d]F[%d]BLANK[%d]BACK[%d]T[%d]A[%d]) == V(S[%d]F[%d]BLANK[%d]BACK[%d]T[%d]A[%d])\n",\
					_p->port, _curr.isInterlaced,\
					_curr.hsync, _curr.hfront, _curr.hblank, _curr.hback, _curr.htotal,_curr.hactive,\
					_curr.vsync,_curr.vfront,_curr.vblank,_curr.vback, _curr.vtotal, _curr.vactive);
		}
		
		/* Save current sync data to gPrevSync history */
		memcpy((void *)&gPrevSync[_p->port], (void *)&_curr, sizeof(HDMI21_VMON_VIDEO_SYNC_T));
	
	}
	else{
		HDMI20_DBG(" DBG[%d]-Inter[%d] H(S[%d]F[%d]BLANK[%d]BACK[%d]T[%d]A[%d]) ==  V(S[%d]F[%d]BLANK[%d]BACK[%d]T[%d]A[%d])\n",\
				_p->port, _curr.isInterlaced,\
				_curr.hsync, _curr.hfront, _curr.hblank, _curr.hback, _curr.htotal,_curr.hactive,\
				_curr.vsync,_curr.vfront,_curr.vblank,_curr.vback, _curr.vtotal, _curr.vactive);
	}		
}



static void __HDMI21_HAL_Rx_MainThread(void)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_SNPS_LINK_REG_0X58C_T _r4;
	HDMI21_SNPS_LINK_REG_0X590_T _r3;
	int i,ret;
	int __tx5Vconnected;	/* Internal variable to check 5V status */
	unsigned int __counter_isr_profile[HDMI21_NUM_OF_MAX_PORTS];		/* variable to operate ISR profiler */
	#ifdef HDMI21_USE_SWWA_FLTUPDATE_LINKDATAPATH_RST
	unsigned int __fltUpdateResetSwWaFlag[HDMI21_NUM_OF_MAX_PORTS];		/* variable to operate ISR profiler */
	#endif
	UINT32 currentTime = 0;
	UINT32 __a = 0;

	UINT32 __r = 0;	// FRL Astro SW WA
	UINT32 __d = 0;	// FRL Astro SW WA

	/* Get FRL_NO_RETRAIN */
	UINT32 __uD;
	HDMI21_SNPS_LINK_REG_0X58C_T _r2;

	HDMI20_INFO("HDMI2.1 Main Thread Start \n");

	/* chip */
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		__a = 0x4;
	}
	else {
		__a = 0;
	}
	/* Pre-Step 0. Set Stamp to Zero */
	gHDMI21Thread.stamp = 0;

	//in warm mode, wait here until mode changes to hot mode
	if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
		HDMI20_PRINT("check warm mode in thread : [%d] \n", gHdmi21WarmMode);
		for(;;) {
			if(gHdmi21WarmMode == 1)
				msleep(10);
			else
				break;
		}
		if(gHdmi21WarmMode > 1)
			HDMI20_PRINT("escaped from warm mode : [%d] \n", gHdmi21WarmMode);
	}

	/* Pre-Step 1. Important to sleep at least for (600msec + a) with HPD down */
	for(i=0;i<g_hdmi20_number_of_ports;i++){
		/* Get Handler */
		_p = &gHDMI21RxHandler[i];

		if(gHDMI21RxDevVideoControler[HDMI21__COUNT_OF_RESUME].value > 0) {
			HDMI20_INFO("HDMI2.1 MainThread Port[%d] Detected Resume. Force HPD down for [%d]msec\n", _p->port, gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value);
		}

		/* Set HPD Down */
		__HDMI21_HAL_Rx_Set_HPD(_p->port ,0, 1);
	
		/* Check if EDID was written before Main Thread operation */
		if(_p->wasEdidWritten == 1){
			HDMI20_INFO("NOTI MainThread Port[%d] : EDID was written before MainThread start\n", _p->port); 
		}
		else{
			HDMI20_INFO("WARNING MainThread Port[%d] : EDID was NOT written before Main Thread Start\n", _p->port);
		}

		/* Reset ISR Counter */
		__counter_isr_profile[i] = 0;
	
		/* Link Top Vfreq Counter Initialization */
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value > 0) {
			__HDMI21_HAL_Rx_Set_LinkTopVfreqCounter(_p, 1, 1);
		}
	}

	/* 2020/06/08 : SWWA for E60B0, JW Choi, DK KIM */
	if(lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)){
		/* Nothing for O22 */
	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)){
		for(i=0;i<g_hdmi20_number_of_ports;i++) {
			/* 2020/06/30 : JinwWoo Test */
			__r = 0x60; __r = (__r << 2) + 0x400;  __d = 0x20; gHDMI21RxHandler[i].phyDR_write(__r, __d);

			/* EQ CAL before HPD UP */
			HDMI20_INFO("SWWA : EQ CAL Start for Port[%d]\n", i);	
			/* PHY PDB HIGH */
			gHDMI21RxHandler[i].top_write(0xB0, 0x21000000);


			/* Flag needs to be UP for PHY APB control API */
			gHDMI21RxHandler[i].is5Vconnected = 1;
			HDMI21_PHY_Rx_Set_ControlPhyPdb(i, 1);

			HDMI21_PHY_Rx_Set_Initiate_Phy(i,  HDMI21_HAL_PHY_INITIATED_3G);
			HDMI21_PHY_Rx_Set_3g6gMode(i, gHDMI21RxDevVideoControler[HDMI21__VIDEO_AUTO_SCRAMBLE_FOR_HDMI20].value,\
					HDMI21_HAL_PHY_INITIATED_FRL_12G_4L, 1, gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3].value);
		}
	}

	/* Pre-Step 1-1. Msleep */
	if(lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)){
		if(	gHDMI21RxDevVideoControler[HDMI21__COUNT_OF_RESUME].value > 0) {
			msleep(gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value);
		}
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)){
		if(	gHDMI21RxDevVideoControler[HDMI21__COUNT_OF_RESUME].value > 0) {
			msleep(gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value);
		}
		else {
			msleep(300); /* 2020/06/25 : need to optimize this as there is no profiling result for the time of Offset Calibration */
		}
	}
	else {
		if(	gHDMI21RxDevVideoControler[HDMI21__COUNT_OF_RESUME].value > 0) {
			msleep(gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value);
		}
	}

	/* 2020/06/08 : SWWA for E60B0, JW Choi, DK KIM */
	if(lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)){
		/* Nothing for O22 */
	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)) {
		for(i=0;i<g_hdmi20_number_of_ports;i++) {
			if(HDMI21_PHY_Rx_Get_CheckEqCalDone(i) > 0) {
				HDMI20_INFO("SWWA : EQ Cal Done Success for Port[%d]. Gather Calibration Data\n", i);
				HDMI21_PHY_Rx_Get_SaffValue(i);
			}
			else {
				HDMI20_INFO("SWWA : Error! Critical Issue. EQ Calibration was not done for Port[%d]!!\n", i);
			}

			/* Flag needs to be Restored for PHY APB control API */
			gHDMI21RxHandler[i].is5Vconnected = 0;

			gHDMI21RxHandler[i].top_write(0xB0, 0x0);
			/* PHY PDB LOW */
			HDMI21_PHY_Rx_Set_ControlPhyPdb(i, 0);

			/* 2020/06/30 : JinwWoo Test */
			__r = 0x60; __r = (__r << 2) + 0x400;  __d = 0x0; gHDMI21RxHandler[i].phyDR_write(__r, __d);

			HDMI21_SCDC_Rx_Set_ScdcConfig(&gHDMI21RxHandler[i], 0);
		}
	}

	/* Main Thread Operation */
	while(1)
	{
		/* Step 1.  Check Force Kill Flag */
		if(gHDMI21Thread.isAlive <= 0){ HDMI20_INFO("Kill Thread\n"); break; }

		/* Step 2. Run each ports iterative */
		for(i=0;i<gHDMI21RxDevVideoControler[HDMI21__NUMBER_OF_ACTIVATED_LINK].value;i++){

			/* Get Handler */
			_p = &gHDMI21RxHandler[i];
			
			/* Step 2-1. Check 5V : Thread will not operate for ports having non-5V status */
			HDMI21_HAL_Rx_Get_Check5VLevelInfo(_p->port, &__tx5Vconnected, 0);

			/* Step 2-1-1. Watch Dog for PHY PDB. This should already be high when 5V HIGH ISR was called 
			 * Sometimes, Main Thread Catches 5V high before 5V ISR, or 5V ISR was never called due to HW fault */
			__HDMI21_HAL_Rx_WatchDog_PhyPdb(_p, __tx5Vconnected);

			if(__tx5Vconnected){
				/* Step 2-1-2. Increase Counter for 5V hold timer feature */
				if(_p->connected5Vtime < gHDMI21RxDevVideoControler[HDMI21__HOLD_TIME_5V_DETECTION].value){
					_p->connected5Vtime += gHDMI21Thread.mSleep;
				}

				/* DBG : View sync status */
				if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1919)) { 
					__HDMI21_HAL_Rx_DBG_PrintSync(_p, gHDMI21RxDevVideoControler[HDMI21__DBG_SYNC_MONITOR_RUN_MODE].value);
				}

				/* DBG : View sync status */
				if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 727)) { 
					__d = _p->link_read(0x588);
					__d &= (0x00001000);

					if(__d != 0) {
						HDMI20_PRINT("DBG[%d] : Detected CED Error cnt is : 0x59C[0x%08x] 0x5A0[0x%08x] 0x5A4[0x%08x]\n", _p->port, _p->link_read(0x59C), _p->link_read(0x5A0), _p->link_read(0x5A4));
					}
				}
		
				/* Step 2-1-3. Local Mute Color Detection : Check Packet Decoder First, incase of RGB, must check Packet FIFO as well.
				 * 			   HW Packet decoder may not be trusted.*/
				__HDMI21_HAL_Rx_Get_CheckLocalVideoMuteColor(_p);
				/* Only For O20 B0 */
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
					__HDMI21_HAL_Rx_Get_CheckTopColorSpaceConversion(_p);
				}
				
				/* Step 2-1-4. Main FSM #1. Check if 5V sequence was taken */
				if(_p->is5Vconnected == 0){
					/* Step 2-1-4-1. If Connect Sequence was not called, call it */
					HDMI20_VIDEO("Notice [%d] : MainThread : 5V High, but without Con-Sequence. Call Sequence\n", _p->port);
					HDMI21_HAL_ConnectCable(_p->port, ON);
				}
				else{
					/* Step 2-1-4-2. Knowing that connect sequence was called, Execute main thread features */
					
					/* Step 2-1-4-2-1. Execute if HPD need to be high */
					if(_p->main_thread_init_request) {
						HDMI20_VIDEO("Notice [%d] : MainThread : Detected cable attachment. \n", i);
						
						/* Set Flag Down */
						_p->main_thread_init_request = 0;  		

						/* Reset Phy */
						ret = HDMI21_PHY_Rx_Set_Initiate_Phy(i,  0/*__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p)*/);  
						if(ret<0) { HDMI20_ERROR("Error MainThread Phy[%d]. Return error from Phy Init[%d]\n", i, ret); }
						
						/* Reset Link */
						__HDMI21_HAL_Rx_Set_ResetLink(_p, 0); 	
					
						/* Reset HDCP2.2 Engine & Start HDCP2.2 Auth  */
						if(_p->gWasHDCP22Written > 0) {
							/* HDCP2.2 */
							HDMI21_HDCP23_Module_Set_HlcReset(_p->port, 1);
						}

						/* 2019/12/09 : G6 Device */
						/* Make sure to Clear clock gate DDC-Link to enable DDC access to link when HPD is being Set to High */
						 if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
							HDMI21_REG_RD(0xCA3A6004, __d);
							__d &= (~0x1F1F);
							HDMI21_REG_WR(0xCA3A6004, __d);
						}
						else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
							HDMI21_REG_RD(0xC8862004, __d);
							__d &= (~0x1F1F);
							HDMI21_REG_WR(0xC8862004, __d);
						}
						else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
							HDMI21_REG_RD(0xC61B2004, __d);
							__d &= (~0x1F1F);
							HDMI21_REG_WR(0xC61B2004, __d);

							HDMI21_REG_RD(0xF3512004, __d);
							__d &= (~0x1F1F);
							HDMI21_REG_WR(0xF3512004, __d);

						}
						else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
							HDMI21_REG_RD(0xCA432004, __d);
							__d &= (~0x1F1F);
							HDMI21_REG_WR(0xCA432004, __d);
						}
						else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
							HDMI21_REG_RD(0xC98A2404, __d);
							__d &= (~0x1F1F);
							HDMI21_REG_WR(0xC98A2404, __d);
						}
						else {
							HDMI21_REG_RD(0xC330004C, __d);	 // CTOP WOV register for DDC/Link clock gating
							__d &= (~0x1F1F0000);
							HDMI21_REG_WR(0xC330004C, __d);
						}

						/* Set HPD High */
						__HDMI21_HAL_Rx_Set_HPD(i, 1, 1); 

						HDMI21_Tx_eARC_Init(_p->port);
						
						/* Import to set fsm_phy_lock flag */
						_p->fsm_phy_lock = 0;
					}

					/* Step 2-1-4-2-2. Update Phy Lock Flag */
					HDMI21_PHY_Rx_Get_UpdatePhyLockFlag(_p->port);	
		
					
					/* Step 2-1-4-2-3. Update Phy TMDS Flag */
					HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock(_p->port);		
					
					/* Step 2-1-4-2-4. SCDC Watch Dog. Checks if PHY setting is not correct with SCDC info */
					__HDMI21_HAL_Rx_WatchDog_PhyConfig(_p);	


					/* Step 2-1-4-2-5. Calculate/Update Real TMDS, PIXEL CLK, Vfreq*/
					__HDMI21_HAL_Rx_Get_UpdateClockVfreq(_p, 1);
					if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1747){
						HDMI20_DBG("DBG %d : Polling TMDS CLK[%llu]KHz, PIXEL CLK[%llu]KHz, VFREQ[%d]\n", _p->port, _p->real_tmds_clk, _p->real_pixel_clk, _p->real_vfreq);
					}

					/* Step 2-1-4-2-6. (Optional) Check MUTE HOLD TIME, clear Mute if time has passed */
					if(gHDMI21RxDevVideoControler[HDMI21__CLEAR_AVMUTE_BY_TIMER].value >0){
						__HDMI21_HAL_Rx_WatchDog_AVMuteHoldTime(_p);
					}

					if((HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) > 0) && (_p->lowPowerMode <=  HDMI21_HAL_POWER_NORMAL)){
						/* Call SetMute API with Mute clear/timer ON to check if time has passed for unmuteing */
						HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 0, 1);
					}

					/* Step 2-1-4-2-7. Check Phy Lock */
					if(_p->isPhyLocked){
						if(!_p->fsm_phy_lock){	/* First Detection of a PLL Lock */
							#ifdef HDMI21_USE_SWWA_FLTUPDATE_LINKDATAPATH_RST
							/* FLT Update, Data Reset SW WA Flag */
							__fltUpdateResetSwWaFlag[_p->port] = 0;
							#endif
							
							/* Set Flag Up */
							_p->fsm_phy_lock = 1;

							/* Priority #1. From Document, SNPS Core DataPath Reset must be asserted after PHY LOCK */
							/* Moved to ISR MainUnit2 [1] routine*/	

							/* Notify */
							HDMI20_PRINT("Notice [%d] : %s Done([%u]msec) TMDS[%5llu] Done[%d] State[0x%08x] TCS[%d][%d][%d][%d]/[%d][%d][%d][%d]/[%d][%d][%d][%d]\n",\
									i,(_p->phyCurrentTMDSExceptionRange>= 0)?"TCS":"Delta", \
									(_p->locking_time * gHDMI21Thread.mSleep), _p->phy_tmds_clk, _p->phyTCSDone, _p->phyTCSState\
									,_p->phyTCSMin[0], _p->phyTCSMin[1],_p->phyTCSMin[2],_p->phyTCSMin[3]\
									,_p->phyTCSMax[0], _p->phyTCSMax[1],_p->phyTCSMax[2],_p->phyTCSMax[3]\
									,_p->phyTCSResult[0], _p->phyTCSResult[1],_p->phyTCSResult[2], _p->phyTCSResult[3]);

							if(_p->phyTCSFailed != 0) {
								HDMI20_ERROR("ERR [%d] : TCS Fail Detected!! [0x%04x]\n", _p->port, _p->phyTCSFailed);
							}

							/* PHY DFE Center SW WA */
							if((_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)&&( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0))){
								if( HDMI21_PHY_Rx_Get_CheckDfeDone(_p->port) <= 0) {
									HDMI20_ERROR("Warning[%d] : Warning! DFE did not finish!!\n", _p->port);
								}
							}

							/* Reset HDCP2.2 Engine & Start HDCP2.2 Auth  */
							if(_p->gWasHDCP22Written > 0) {
								if((gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value > 0) \
										&&(_p->phyInitiatedMode >=  HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && ( lx_chip_rev( ) >= LX_CHIP_REV(E60, B0))) {
									/* Do Nothing */
								}
								else {
									/* HDCP2.2?? */
									//HDMI21_HDCP23_Module_Set_HlcReset(_p->port); // Moved to Phy
									HDMI21_HDCP23_Module_Set_HlcAuthenticate(_p->port, 0);
								}
							}

							/* Set Local Mute with TIMER alert */	
							HDMI21_HAL_Rx_Set_LocalVideoMute(i, 1, 1);
						
							/* Just in Case : Set Stable CNT to ZERO */
							_p->stable_cnt = 0;

							/* Should Get rid of VRR/FreeSync/QMS history */
							_p->isFreeSyncMode = 0;
							_p->isMConst = 0;
							_p->isQmsMode = 0;

							/* Should Get rid of FVA history */
							_p->isFvaMode = 0;

							/* Reset Handler's DataPacket Memory */
							HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA_MAXNUM ,i);
							HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_VTEM, i);

							/* Audio Reset */
							HDMI21_HAL_Rx_Set_AudioReset(i);
						
							/* Reset HDCP DDC History */
							_p->isHDCP14 = 0;
							_p->isHDCP22 = 0;
						}

						/* DBG : Eye Diagram */
						if(gHdmi21EyeMeasure[_p->port] == 1) {
							__HDMI21_HAL_Rx_DBG_CalculatePhyEyeDiagrame(_p);
						}

						/* FRL : Manual FRL match value search */
						if(gHdmi21FrlErrMeasure[_p->port] == 1) {
							__HDMI21_HAL_Rx_DBG_CalculateFrlPosition(_p);
						}
					}
					else{
						/* Notify case-by-case : TMDS CLK/No-TMDS CLK */
						if(_p->phy_tmds_clk > 0){
							HDMI20_VIDEO("Notice [%d] : Waiting %s(%s) [%u] CLK[%5llu] TCSDone[%d]. CRDone[%d] State[0x%08x] Min[%d][%d][%d][%d]/Max[%d][%d][%d][%d]\n",\
									i, (_p->phyCurrentTMDSExceptionRange>= 0)?"TCS":"Delta", phymode_type_to_str(_p->phyInitiatedMode),\
									(_p->locking_time * gHDMI21Thread.mSleep), _p->phy_tmds_clk, _p->phyTCSDone,\
									_p->phyCrDone, _p->phyTCSState,\
									_p->phyTCSMin[0], _p->phyTCSMin[1],_p->phyTCSMin[2],_p->phyTCSMin[3],\
									_p->phyTCSMax[0], _p->phyTCSMax[1],_p->phyTCSMax[2],_p->phyTCSMax[3]);

							/* Inform with Lower debug Logs in cases where PHY does not get locked within T time */
							if(_p->locking_time >= gHDMI21RxDevVideoControler[HDMI21__TIMEOUT_FOR_PHY_LOCK_WAIT].value){
								HDMI20_PRINT("Warning [%d] : Waited %s(%s) for [%d] msec(C) TMDS[%5llu] State[0x08%x] TCS[%d][%d][%d][%d]/[%d][%d][%d][%d]/[%d][%d][%d][%d]/[%d][%d][%d][%d]. SCDC[%d]\n",\
										i, (_p->phyCurrentTMDSExceptionRange>= 0)?"TCS":"Delta", phymode_type_to_str(_p->phyInitiatedMode),\
										(_p->locking_time * gHDMI21Thread.mSleep), _p->phy_tmds_clk,_p->phyTCSState,\
										_p->phyTCSMin[0], _p->phyTCSMin[1], _p->phyTCSMin[2], _p->phyTCSMin[3],\
										_p->phyTCSMax[0], _p->phyTCSMax[1], _p->phyTCSMax[2], _p->phyTCSMax[3],\
										_p->phyTCSResult[0],_p->phyTCSResult[1], _p->phyTCSResult[2], _p->phyTCSResult[3],\
										_p->phyTMDSError[0], _p->phyTMDSError[1], _p->phyTMDSError[2], _p->phyTMDSError[3],\
										_p->phyInitiatedMode);

								_p->locking_time = 0;

								/* 2022/12/06 : For the sake of XBox's customers.. */
								if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_TOGGLE_ON_FRL_TCS_LOW].value >0) {
									/* Work only on FRL Modes & And not on CTS Test Mode */
									if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {

										__uD = _p->link_read(0x590);	
										memcpy((void *)&_r2, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));

										if(_r2.SCDC_FLT_NO_RETRAIN == 0) {
											HDMI20_PRINT("Warning [%d] : Detected XBox-Series-X fail case! HPD Toggle!!\n", _p->port);
											HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
										}
									}

								}
							}
						}
						else {
							HDMI20_VIDEO("Notice [%d] : No TMDS Clk(C)[%5llu] CRDone[%d] PHYMode[%s]\n", i, _p->phy_tmds_clk, _p->phyCrDone, phymode_type_to_str(_p->phyInitiatedMode));
						}

						/* Increase Phy Lock Timer */
						_p->locking_time++;
					}

					/* 2025/06/12 won.hur : O26 HF2-17 CTS issue (from Jinwoo.Choi) */
					if(gHDMI21RxDevLinkControler[HDMI21__LINK_RST_HDMI_SYN_FOR_CLK_LOSS].value > 0) {
						/* Lets hope that this W/A is only for O26 and non for future chips... */
						if(lx_chip() == LX_CHIP_O26) {
							if(_p->isPhyLockLoss == true) {
								if((_p->isPhyLocked == 0) && (_p->phy_tmds_clk == 0) && (_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G)) {
									__HDMI21_HAL_Rx_Reset_ChipHdmiSynTop(_p->port, 1);
									__HDMI21_HAL_Rx_Reset_ChipHdmiSynTop(_p->port, 0);
								}

								_p->isPhyLockLoss = false;
							}
						}
					}

					HDMI21_LINE_DBG(6177, "DBG[%d] SCDC flag [0x594]=>[0x%08x]\n", _p->port, _p->link_read(0x594));

					/* 2022/08/31 */
					if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_STUCK_SWWA_THRES].value > 0) {
						__HDMI21_HAL_Rx_WatchDog_FilterSelStuck(_p);
					}
		
					#if 0 
					/* EXT : Check HDCP2.3 result */
					if(((_p->isPhyLocked)&&(_p->fsm_phy_lock))&&((_p->gWasHDCP22Written > 1)|| (gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 5035))){
						if(HDMI21_HDCP23_Module_Get_HlcMonitor(_p->port) == -135) {
							HDMI20_INFO("HDCP[%d] : Detected SKE. Send RepeaterAuthInfo\n", _p->port);
							HDMI21_HDCP23_Module_Set_HlcSendRepeaterAuth(_p->port);
						}
						
					}
					#endif

					/* Step 2-1-4-2-8. Check Signal Stablility only when change flag is not active */
					if((_p->isPhyLocked)&&(_p->fsm_phy_lock)&&(__HDMI21_HAL_Rx_Get_CheckChangeFlag(_p) == 0)) {
					
						if(_p->stable_cnt < gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value)
						{
							HDMI21_LINE_DBG(1859, "DBG[%d] Waiting Stable[%d]. 0x2B8[0x%08x] 0x2F4[0x%08x] 0x2F0[0x%08x] 0x7CC[0x%08x] 0x270[0x%08x]\n",\
									_p->port, _p->stable_cnt, _p->link_read(0x2b8), _p->link_read(0x2f4), _p->link_read(0x2f0), _p->link_read(0x7cc), _p->link_read(0x270));
							_p->stable_cnt++;

							/* H5D SW WA */
							/* Stick is too slow, will set this to all ports */
							if(/*_p->port == 4*/ 1) {
								HDMI21_HAL_Rx_Get_VideoInfo(_p, &_p->hwVideo);
							}

							/* 2025/07/01 won.hur : SW WA for Q980B CTS for FRL 12G4L + 480P + 12BIT */
							if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRL12G4L_480P_12B_FORCE_WA].value > 0) {
								if(_p->isFrl480pDcmForceSwWa == true) {
									if(HDMI21_VPROC_Rx_Get_OverRideColorDepth(_p) > 0) {
										HDMI20_PRINT("Notice [%d] : Recover force DCM 12BIT for FRL12G4L + 480P + 12DCM\n", _p->port);
										HDMI21_VPROC_Rx_Set_OverRideColorDepth(_p, 0, 0);
									}

									_p->isFrl480pDcmForceSwWa = false;
								}
							}
						}
						else if(_p->stable_cnt == gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value)
						{
							HDMI21_LINE_DBG(1859, "DBG[%d] Stabled[%d]. 0x2B8[0x%08x] 0x2F4[0x%08x]  0x2F0[0x%08x] 0x7CC[0x%08x] 0x270[0x%08x]\n",\
									_p->port, _p->stable_cnt, _p->link_read(0x2b8), _p->link_read(0x2f4), _p->link_read(0x2f0), _p->link_read(0x7cc), _p->link_read(0x270));

							/* SW workaround : incase Link did not trigger any interrupts */
							if(HDMI21_HAL_Rx_Get_IsVideoSyncChanged(_p, &_p->hwVideo) > 0) {

								HDMI20_PRINT("Warning [%d] : Main Threaded Detected signal change before stability release\n", _p->port);


								if(gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_DATAPATH_RST_ON_UNSTABLE].value > 0) {
									/* 2022/10/20 : Johnny Park SLT Issue for O22 */
									HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_DATAPATHONLY);
								}

								if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_VPGEN_TOGGLE].value > 0) {
									HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_VPROC);
								
									/* H5D SW WA */
									if(_p->port == 4) {
										if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_H5D_8K_CHECK_HPD_SWWA].value > 0) {
											HDMI20_PRINT("Warning [%d] : Detected invalid resolution on H5D Port! HPD Toggle!\n", _p->port);
											HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
										}
										else{
											HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
										}
									}
								}
								_p->stable_cnt = 0;
								_p->stablehdcp14time = 0;
							}
							else { 
								/* Look for DSC */
								__HDMI21_HAL_Rx_Get_PollCvtemStatus(_p);

								if(HDMI21_HDCP_Rx_Get_IsCurrentHDCP14(_p) > 0) {
									/* HDCP1.4 stable check */
									HDMI21_HDCP_Rx_Set_UpdateHDCP14StableFlag(_p, 0); /* This increments stablehdcp14time value */

									if(_p->stablehdcp14time < gHDMI21RxDevVideoControler[HDMI21__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY].value){
										HDMI21_LINE_DBG(14, "DBG[%d] : MainThread : Stable Video but wait until HDCP1.4 is stable[%d]\n", _p->port,_p->stablehdcp14time);
									}
									else{
										HDMI20_PRINT("Notics [%d] : MainThread :  HDCP1.4 Stable for [%d] msec. \n", _p->port, _p->stablehdcp14time);
										_p->stable_cnt++;
										/* Import to Update Stable Timing Info when stable_cnt reached stable threshold */
										__HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(_p, 0);
									}
								}
								else{
									HDMI20_PRINT("Notice [%d] : MainThread : Video stable for [%d]msec(%s)\n"\
											, _p->port, (_p->stable_cnt * gHDMI21Thread.mSleep), phymode_type_to_str(_p->phyInitiatedMode));

									_p->stable_cnt++;
									/* Import to Update Stable Timing Info when stable_cnt reached stable threshold */
									__HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(_p, 0);

									/* 2020/08/04 : NVidia O20 */
									gHdmi21LaneLockLossFlag[_p->port] = 0;

									/* Update History */
									_p->stableHist++;
								}

								if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_FRL_NO_READY_SWWA].value > 0) && (_p->port != 4) && (gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value > 0)){
									if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
										/* Set FLT_READY to LOW */
										__r = 0x60; __r = (__r << 2) + 0x400;  __d = 0x20; _p->phyDR_write(__r, __d);
									}
								}

								/* for HDMI Host diagnosis error detection */
								__HDMI21_HAL_Rx_Set_PutHDMIHostError(_p, LX_HDMI20_ERROR_PHY_LOW_RANGE, 0);
								__HDMI21_HAL_Rx_Set_PutHDMIHostError(_p, LX_HDMI20_ERROR_PHY_ABNORMAL, 0);
							}
						}
						else{
							/* This part will run always on steady state
							 * Insert code as wishing that it would always be called when on steady video */
							/* Look for DSC */
							__HDMI21_HAL_Rx_Get_PollCvtemStatus(_p);

							/* DBG */
							HDMI21_LINE_DBG(1859, "DBG[%d] Stabled[%d]. 0x2B8[0x%08x] 0x2F4[0x%08x]  0x2F0[0x%08x] 0x7CC[0x%08x] 0x270[0x%08x]\n",\
									_p->port, _p->stable_cnt, _p->link_read(0x2b8), _p->link_read(0x2f4), _p->link_read(0x2f0), _p->link_read(0x7cc), _p->link_read(0x270));

							if(__HDMI21_HAL_Rx_Get_IsStableTimingInfoEmpty(_p) > 0){
								/* This print should never be seen. If printed, one must do debugging to figure out why */
								HDMI20_VIDEO("Warning [%d] : MainThread : Stable Video but TimingInfo is Empty. Refresh Timing Info!\n", _p->port);
								__HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(_p, 0);
							}

							if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_CNT].value > 0) {
								/* Only for HDMI1.4 & HDMI2.0 */
								if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) <= HDMI21_HAL_PHY_INITIATED_6G){
									/* Only For HDCP1.4?? */
									__d = _p->link_read(0x7CC);
									__d &= (0x0000FFFF);

									if(__d >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_THRES].value) { 
										HDMI21_LINE_DBG(6365, "DBG[%d] : PKT Error met over Thres[0x%x]. Val[0x%x]. Cnt[%d]\n", _p->port, gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_THRES].value, __d,  _p->pktErrStateCnt);
										_p->pktErrStateCnt++; 
									}
									else {
										HDMI21_LINE_DBG(6365, "DBG[%d] : PKT Error Under Thres[0x%x]. Val[0x%x].\n", _p->port, gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_THRES].value, __d);
										_p->pktErrStateCnt = 0;
									}

									if(_p->pktErrStateCnt > gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_CNT].value) {
										HDMI20_INFO("Error[%d] : Detected PKT error(Snow-Noise). Cnt[%d]/Thres[0x%x]. DataPath Reset!\n", _p->port, _p->pktErrStateCnt, gHDMI21RxDevVideoControler[HDMI21__VIDEO_PKTERR_DETECT_THRES].value);	
										if(HDMI21_HDCP23_Module_Get_IsRepeater() > 0){
											if((_p->dataPacket[HDMI21_DISLAND_DATA__SPD][12] == 0x4d) && (_p->dataPacket[HDMI21_DISLAND_DATA__SPD][13] == 0x42) && (_p->dataPacket[HDMI21_DISLAND_DATA__SPD][14] == 0x6f) && (_p->dataPacket[HDMI21_DISLAND_DATA__SPD][15] == 0x78)){
												HDMI20_INFO("Info[%d] : Detected PKT error(Snow-Noise). But Reapeater mode + MBox Source \n", _p->port);	
											}else{
												HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
											}
										}else if(_p->lowPowerMode == HDMI21_HAL_POWER_LOWPOWER){
											HDMI20_INFO("Info[%d] : Detected PKT error(Snow-Noise). But LowPower mode!! \n", _p->port);	
										}else{
											HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
										}
									}
								}
							}

							if((gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value > 0)&&((_p->port != 4)||(gHDMI21RxDevVideoControler[HDMI21__VIDEO_H5D_LN_LOCK_RET].value > 0))){
								/* Detect new FRL Rate from/to same FRL Rate */
								/* Read Lane Lock */
								if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {

									/* Get FLT NO retrain */
									__d = _p->link_read(0x58c + __a);	memcpy((void *)&_r4, &__d, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));

									if(_r4.SCDC_FLT_NO_RETRAIN == 0) {
										__d = _p->link_read(0x590 + __a);	memcpy((void *)&_r3, &__d, sizeof(HDMI21_SNPS_LINK_REG_0X590_T));

										if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L) {
											_r3.SCDC_LN3LOCKED = 0;
										}

										if( (_r3.SCDC_LN0LOCKED == 0) && (_r3.SCDC_LN1LOCKED == 0) && (_r3.SCDC_LN2LOCKED == 0) && (_r3.SCDC_LN3LOCKED == 0)){
										
											if(_p->port == 4) __d = 10;
											else __d = gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value;

											if(_p->lnLockLossCnt >= __d ) {
												/* Reset Lane Lock Counter */
												_p->lnLockLossCnt = 0;
											
												if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_FRL_NO_READY_SWWA].value > 0) && (_p->port != 4)){
													/* Clear SCDC registers */
													HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, HDMI21_SNPS_RST_AVPUNIT);

													HDMI20_VIDEO("Notice[%d] : Detected LN lock down SW Condition! Set FLT_READY to HIGH.  LNLock[%d][%d][%d][%d] TCSError[0x%x][0x%x][0x%x][0x%x]\n",\
															_p->port, _r3.SCDC_LN0LOCKED,_r3.SCDC_LN1LOCKED,_r3.SCDC_LN2LOCKED,_r3.SCDC_LN3LOCKED,\
															_p->phyCEDError[0], _p->phyCEDError[1],_p->phyCEDError[2],_p->phyCEDError[3]);

													/* Set FLT_READY to HIGH*/
													__r = 0x60; __r = (__r << 2) + 0x400;  __d = 0x0; _p->phyDR_write(__r, __d);

													/* Set FRL SW WA flag to 0 */
													_p->phyFrlSwWaState = 0;
						
													/* 2020/08/04 : NVidia O20 */
													gHdmi21LaneLockLossFlag[_p->port] = 1;
												}
												else {
													/* Set TCS Manual Mode to Off */
													__r  = 0x99; __r = (__r << 2);  __d = _p->phyDR_read(__r);
													__d &= 0x0E;  _p->phyDR_write(__r, __d);

													__r = 0x66; __r = (__r << 2) + 0x400;  __d = _p->phyDR_read(__r);
													__d |= ( 0x80); _p->phyDR_write(__r, __d);

													/* Set FRL SW WA flag to 0 */
													_p->phyFrlSwWaState = 0;

													HDMI20_VIDEO("Notice[%d] : Detected LN lock down SW Condition! Request FLT_RESTART!  LNLock[%d][%d][%d][%d] TCSError[0x%x][0x%x][0x%x][0x%x]\n",\
															_p->port, _r3.SCDC_LN0LOCKED,_r3.SCDC_LN1LOCKED,_r3.SCDC_LN2LOCKED,_r3.SCDC_LN3LOCKED,\
															_p->phyCEDError[0], _p->phyCEDError[1],_p->phyCEDError[2],_p->phyCEDError[3]);
													__d &= (~0x80); _p->phyDR_write(__r, __d);

													HDMI21_PHY_Rx_Set_ToggleTCSEn(_p->port, 0);
													HDMI21_PHY_Rx_Set_ToggleTCSEn(_p->port, 1);

													/* 2020/08/04 : NVidia O20 */
													gHdmi21LaneLockLossFlag[_p->port] = 1;
												}
											}
											else {
												HDMI20_VIDEO("Warning[%d] : LaneOut Loss on FRL. Curr LaneLockLossCnt[%d] / Threshold[%d]\n", _p->port,\
														_p->lnLockLossCnt, gHDMI21RxDevPhyControler[HDMI21__PHY_RETRAIN_ON_NO_LANELOCK].value);
												_p->lnLockLossCnt++;
											}
										}
									}
								}
							}

							/* Watch Dog since, H meas ISR is such a ASS Pain */
							if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_CHANGE_DETECTOR_WATCHDOG].value > 0){
								if(HDMI21_HAL_Rx_Get_IsVideoSyncChanged(_p, &_p->video) > 0) {

									HDMI20_PRINT("Notice [%d] : Main Thread Detected VideoChange. Reset Stable CNT to 0 \n", _p->port);
									_p->stable_cnt = 0;
									_p->stablehdcp14time = 0;

									if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_VPGEN_TOGGLE].value > 0) {
										HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_VPROC);
									}

									/* 2020/04/16 : To Restore PixelPacking Phase software workaround */
									if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_PIXEL_PACKING_WATCHDOG].value > 0) {
										if(HDMI21_VPROC_Rx_Get_OverRidePixelPackingPhase(_p) > 0) {
											HDMI21_VPROC_Rx_Set_OverRidePixelPackingPhase(_p, 0, 0);
										}
									}
								}
							}

							/* for HDMI Host diagnosis error detection */
							__HDMI21_HAL_Rx_Set_PutHDMIHostError(_p, LX_HDMI20_ERROR_TMDS_ERROR, 0);
							__HDMI21_HAL_Rx_Set_PutHDMIHostError(_p, LX_HDMI20_ERROR_CED_ERROR, 0);

							/* HDMI1.4 Legacy Pixel Repetition mode configuration */
							__HDMI21_HAL_Rx_Set_PixelRepetitionMode(_p, _p->hwVideo.pixel_repetition);
							
							/* 2018 Taejun Lee/Baek-Gi Ho high school audio issue */
							__HDMI21_HAL_Rx_Get_IsPC(_p);
							
							HDMI21_HAL_Rx_Get_AudioACRParam(i, 0);
							HDMI21_HAL_Rx_Get_AudioInfo(i);
						}

					}

					/* Step 2-1-4-2-9. Timeout ALLM/VRR Mode if not recieved within time interval */
					if((_p->isAllmMode > 0)&&(gHDMI21RxDevVideoControler[HDMI21__LINK_ALLM_TIMEOUT].value > 0)){
						if(_p->allm_recieve_time > 0) {
							currentTime = jiffies_to_msecs(jiffies);
							if(currentTime - _p->allm_recieve_time <= gHDMI21RxDevVideoControler[HDMI21__LINK_ALLM_TIMEOUT].value){
								HDMI21_LINE_DBG(4355, "DBG[%d] : ALLM in time! Stamp[%u]/Now[%u]\n", _p->port,  _p->allm_recieve_time, currentTime);
							}
							else
							{
								HDMI20_INFO("INFO[%d] : ALLM TIME-OUT! Stamp[%u]/Now[%u]\n", _p->port,  _p->allm_recieve_time, currentTime);
								_p->allm_recieve_time = 0;
								_p->isAllmMode = 0;

								/* 2022/09/26 : Need to refresh HF VSIF buffer */
								HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__HFVSI, _p->port);
							}
						}
						else {
							_p->isAllmMode = 0;
						}
					}

					if((_p->isFreeSyncMode == 2)&&(gHDMI21RxDevVideoControler[HDMI21__VIDEO_VRR_EM_TIMEOUT].value > 0)) {
						if(_p->em_vrr_recieve_time > 0) {
							currentTime = jiffies_to_msecs(jiffies);
							if(currentTime - _p->em_vrr_recieve_time <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_VRR_EM_TIMEOUT].value){
								HDMI21_LINE_DBG(4355, "DBG[%d] : VVRR in time! Stamp[%u]/Now[%u]\n", _p->port,  _p->em_vrr_recieve_time, currentTime);
							}
							else
							{
								HDMI20_INFO("INFO[%d] : EM VRR Timeout! Stamp[%u]/Now[%u]\n", _p->port,  _p->em_vrr_recieve_time, currentTime);
								_p->em_vrr_recieve_time = 0;
								_p->isFreeSyncMode = 0;
								_p->isFvaMode = 0;

								/* 2025/05/20 : RTings */
								HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_VTEM, _p->port);

							}
						}
						else {
							_p->isFreeSyncMode = 0;
							_p->isFvaMode = 0;
						}
					}

					if((_p->isQmsMode > 0)&&(gHDMI21RxDevVideoControler[HDMI21__VIDEO_QMS_EM_TIMEOUT].value > 0)) {
						if(_p->em_qms_recieve_time > 0) {
							currentTime = jiffies_to_msecs(jiffies);
							if(currentTime - _p->em_qms_recieve_time <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_QMS_EM_TIMEOUT].value){
								HDMI21_LINE_DBG(4355, "DBG[%d] : QMS EM in time! Stamp[%u]/Now[%u]\n", _p->port,  _p->em_qms_recieve_time, currentTime);
							}
							else
							{
								HDMI20_INFO("INFO[%d] : EM QMS Timeout! Stamp[%u]/Now[%u]\n", _p->port,  _p->em_qms_recieve_time, currentTime);
								_p->em_qms_recieve_time = 0;
								_p->isMConst = 0;
								_p->isQmsMode = 0;
							}
						}
						else {
							_p->isMConst = 0;
							_p->isQmsMode = 0;
						}
					}

					/* SW WA for VPROC BUFFER stall issue */
					if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_VPGEN_TOGGLE].value > 0) {
						if(_p->lowPowerMode != HDMI21_HAL_POWER_LOWPOWER) {
							if(HDMI21_VPROC_Rx_Get_VPGenConnection(_p) != HDMI21_RX_VPGEN_CONN_DISCONNECT) {
								HDMI21_LINE_DBG(8786, "DBG[%d] : Found VPGEN on non-Disconnect state[%d]. Set to Disconnect\n",\
										_p->port, HDMI21_VPROC_Rx_Get_VPGenConnection(_p));
								HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_DISCONNECT);
							}
						}
					}

					/* DK Kim Calibrate Test Code */
					if(gHdmi21OffsetRepeatIteration[_p->port] > 0) {
						__HDMI21_HAL_Rx_DBG_CalculateOffsetRepeat(_p, &gHdmi21CalTestData[_p->port][gHdmi21OffsetRepeatIndex[_p->port]] );
						
						/* When Test is Done! */
						if(gHdmi21OffsetRepeatTest[_p->port] == 1) {
							gHdmi21OffsetRepeatTest[_p->port] = 0;
							gHdmi21OffsetRepeatIteration[_p->port]--;
							gHdmi21OffsetRepeatIndex[_p->port]++;

							if(gHdmi21OffsetRepeatIteration[_p->port] == 0) {
								printk("DBG[%d] : Offset Repeatation Test Done!\n", _p->port);
							}
						}
					}

					/* DK Kim DFE Test Code */
					if(gHdmi21DfeRepeatIteration[_p->port] > 0) {
						__HDMI21_HAL_Rx_DBG_CalculateDfeRepeat(_p, &gHdmi21DfeTestData[_p->port][gHdmi21DfeRepeatIndex[_p->port]] );
						
						/* When Test is Done! */
						if(gHdmi21DfeRepeatTest[_p->port] == 1) {
							gHdmi21DfeRepeatTest[_p->port] = 0;
							gHdmi21DfeRepeatIteration[_p->port]--;
							gHdmi21DfeRepeatIndex[_p->port]++;

							if(gHdmi21DfeRepeatIteration[_p->port] == 0) {
								printk("DBG[%d] : Dfe Repeatation Test Done!\n", _p->port);
							}
						}
					}

					#ifdef HDMI21_USE_SWWA_FLTUPDATE_LINKDATAPATH_RST
					/* JINWOO CHOI Test Code */
					if((_p->isPhyLocked)&&(_p->fsm_phy_lock)&&(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)) {
						if( __fltUpdateResetSwWaFlag[_p->port] == 0) {
							__d = _p->link_read(0x588);
							HDMI21_LINE_DBG(5914, "DBG[%d] : 0x588<=[0x%08x]\n", _p->port, __d);

							if((__d & 0x2000) == 0) {
								HDMI20_INFO("INFO[%d] : JINWOO CHOI! Bit[13] got to zero!\n", _p->port);
								__fltUpdateResetSwWaFlag[_p->port] = 1;

								HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
							}
						}
					}
					#endif

					/* 2020/11/25 : Dovi Time-out feature */
					__HDMI21_HAL_Rx_Set_CheckDoviClearTimer(_p);

					/* 2025/05/30 : isFLT can be only set in O22/O24 PHY codes. O26 phy codes does not set isFLT */
					if(_p->isFLT){
						if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){							
							__HDMI21_HAL_Rx_Check_RSScanResult(_p);
						}
					}
				
				} // End of if(gHDMI21RxHandler[i].is5Vconnected == 0)

				/* Step 2-1-5. Run ISR Profiler */
				if(gHDMI21RxDevVideoControler[HDMI21__ENABLE_ISR_PROFILER].value > 0){
					__HDMI21_HAL_Rx_Set_IsrProfiler(_p, &__counter_isr_profile[i]);
				}

			} // End of if(tx5Vconnected)
			else{
				/* Step 2-2. 5V is not connected */
				/* Step 2-2-1. Overwrite 5V timer for 5V Hold time feature */
				_p->connected5Vtime = 0;

				/* Step 2-2-2. Check RestartHPD Status */
				if(_p->restartHpdFlagUp == true){
					/* Step 2-2-2-1. In-case in RestartHPD operation, Notify user and perform nessessary things. */
					if(HDMI21_HAL_Rx_Get_IsHpdUp(_p->port) != 0){
						HDMI20_VIDEO("Notice %d : Found RestartHPD on Main Thread. Initiate Timing and PDB Down\n", _p->port);
						
						__HDMI21_HAL_Rx_Set_ResetHandlerData(_p, 1);		/* Clear Handler Information */
						__HDMI21_HAL_Rx_Set_HPD(_p->port ,0, 1); 	/* Set HPD Low */
						HDMI21_HAL_Rx_Set_AudioReset(i);			/* Audio Mute */
						HDMI21_HAL_ConnectCable(_p->port, 0);		/* Important : This will HARD reset Link */
					}
					else{
						/* Step 2-2-2-2. This will be called when waiting for RestartHPD to end */
						// DBG Print here
					}
				}
				else{
					/* Step 2-2-3. 5V Low without any operation */
					/* Step 2-2-3-1.  In case HPD high/5V Low. This could happen when 5V got low without TOP ISR notification */
					if(HDMI21_HAL_Rx_Get_IsHpdUp(_p->port) != 0){
						HDMI20_INFO("Warning [%d] : HPD was UP even though 5V is Low. Set HPD LOW\n", _p->port);
					
						__HDMI21_HAL_Rx_Set_ResetHandlerData(_p, 1);		/* Clear Handler Information */
						__HDMI21_HAL_Rx_Set_HPD(_p->port ,0, 1); 	/* Set HPD Low */
						HDMI21_HAL_Rx_Set_AudioReset(i);			/* Audio Mute */
						HDMI21_HAL_ConnectCable(_p->port, 0);		/* Important : This will HARD reset Link */
					}
					else
					{
						/* Step 2-2-3-2. This place should be called when without 5V/No operation */
					}
				}
			}

			/* Step 2-3. Tick for Checking Idel mode */
			ret = __HDMI21_HAL_Rx_Set_IdleTick(_p, _p->is5Vconnected);
			if((ret < 0)&& (_p->is5Vconnected > 0)) {
				HDMI21_LINE_DBG(7081, "DBG [%d] : Not Idle state. Return val[%d]\n", _p->port, ret);
			}

			/* Step 2-4. Check for low power mode */
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value > 0) {
				if(__HDMI21_HAL_Rx_Get_IsCurrentIdleState(_p)) {
					if(_p->lowPowerMode == HDMI21_HAL_POWER_NORMAL) {
						HDMI20_INFO("Info[%d] : Detected idle condition. CurrTick[%d]/Thres[%d]([%d] msec)\n", _p->port,\
								_p->idleTick, gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value,\
								(_p->idleTick * gHDMI21Thread.mSleep));
						HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 1, 0, 0);
					}
					else if((_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER)&&(_p->isLowPowerTransState == gLowPowerState1Tick)) {
						HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 1, 0, 1); 
					}
					else if((_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER)&&(_p->isLowPowerTransState == gLowPowerState2Tick)) {
						HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 1, 0, 2); 
					}
					else if((_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER)&&(_p->isLowPowerTransState == gLowPowerState3Tick)) {
						HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 1, 0, 3); 
					}
					else if((_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER)&&(_p->isLowPowerTransState == gLowPowerState4Tick)) {
						HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 1, 0, 4); 
					}
					else if((_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER)&&(_p->isLowPowerTransState == gLowPowerState5Tick)) {
						HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 1, 0, 5); 
					}
					else if(_p->isLowPowerTransState > 0) {
						HDMI21_LINE_DBG(9830, "DBG[%d] : Monitor Top 0x300 <= [0x%08x]\n", _p->port, _p->top_read(0x300));
						_p->isLowPowerTransState++;
					}
				}
				else {
					/* Exit Low power mode */
					if(_p->lowPowerMode >= HDMI21_HAL_POWER_LOWPOWER) {
						if(_p->isLowPowerTransState == 0) {
							/* Enter low power mode */
							HDMI20_INFO("Info[%d] : Detected Exit-LowPower-Mode. Reason[%d]\n", _p->port, ret);
							HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 0, 0, 0); 
						}
						#if 0
						else if(_p->isLowPowerTransState == gLowPowerStateMidTick) {
							/* 2021/08/23 : Unexpectly added.. */
							__HDMI21_HAL_Rx_Set_LowPowerSettingStepMid(_p, 0);
						
						}
						#endif
						else if(_p->isLowPowerTransState == gLowPowerState1Tick) {
							HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 0, 0, 1); 
						}
						else if(_p->isLowPowerTransState == gLowPowerState2Tick) {
							HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 0, 0, 2); 
						}
						else if(_p->isLowPowerTransState == gLowPowerState3Tick) {
							HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 0, 0, 3); 
						}
						else if(_p->isLowPowerTransState == gLowPowerState4Tick) {
							HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 0, 0, 4); 
						}
						else if(_p->isLowPowerTransState == gLowPowerState5Tick) {
							HDMI21_HAL_Rx_Set_LowPowerMode(_p->port, 0, 0, 5); 
						}
						else if(_p->isLowPowerTransState > 0) {
							HDMI21_LINE_DBG(9830, "DBG[%d] : Monitor Top 0x300 <= [0x%08x]\n", _p->port, _p->top_read(0x300));
							_p->isLowPowerTransState++;
						}
					}
				}
			}
		} // End of for(i=0;i<1;i++)

		/* Step 3. Update Main Thread Stamp every Iteration */
		gHDMI21Thread.stamp = 1;

		/* Step 4. Msleep to return to scheduler */
		msleep(gHDMI21Thread.mSleep);
	} // End of While(1)

	/* Step 5. Always Set Stamp/Alive Flag to Zero when exiting Thread */
	gHDMI21Thread.stamp = 0;
	gHDMI21Thread.isAlive = 0;
}

static int __HDMI21_HAL_Rx_Get_HDMIState(UINT8 port, LX_HDMI_STATUS_T *pHdmiStatus, int size)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = RET_ERROR;
	LX_HDMI_STATUS_T userdata;

	do{
		if(pHdmiStatus == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_STATUS_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_STATUS_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_STATUS_T));

		/* Step 2. Copy data */
		if(_p->hwVideo.dvi){
			userdata.bHdmiMode = 0;
		}
		else{
			userdata.bHdmiMode = 1;
		}

		/* CSC : RGB/YCbCr 444/422/420 */
		userdata.csc = _p->hwVideo.video_format;
		
		/* 2016/06/30 won.hur : Defence code for DVI CSC */
		if(userdata.csc > 0){
			if(_p->hwVideo.dvi){
				HDMI21_LINE_DBG(1987, "DBG[%d] : DVI CSC YCbCr detected. SW WA activated\n",_p->port);

				/* Overwrite CSC to RGB */
				userdata.csc = 0;
			}
		}

		userdata.eHotPlug = _p->isHPD;
		
		/* Update DCM for MW */
		switch(_p->hwVideo.deep_color_mode){
			case 0x0:
			case 0x4:
				userdata.eColorDepth = LX_HDMI_COLOR_DEPTH_8;
				break;
			case 0x5:
				userdata.eColorDepth =LX_HDMI_COLOR_DEPTH_10;
				break;
			case 0x6:
				userdata.eColorDepth =LX_HDMI_COLOR_DEPTH_12;
				break;
			case 0x7:
				userdata.eColorDepth =LX_HDMI_COLOR_DEPTH_16;
				break;
			default:
				userdata.eColorDepth =LX_HDMI_COLOR_DEPTH_8;
				break;
		}
			
		userdata.pixelRepet = _p->hwVideo.pixel_repetition;
		
		ret = copy_to_user((LX_HDMI_STATUS_T *)pHdmiStatus, &userdata, sizeof(LX_HDMI_STATUS_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "HDMI_STATE", port);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}




static void __HDMI21_HAL_Rx_Set_InitDevHandler(UINT8 isResume)
{
	int i;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	HDMI20_INFO("Initiating HDMI21 device handler. IsResume[%d], Called[%pS]\n", isResume, __builtin_return_address(0));

	if(isResume == 0){
		for(i=0; i<g_hdmi20_number_of_ports; i++) {
			memset((void *)&gHDMI21RxHandler[i], 0, sizeof(HDMI21_HAL_RX_DEVICE_DATA));

			_p = &gHDMI21RxHandler[i];

			_p->initiated 	= true;
			_p->port 		= i;
			_p->irq 		= gHDMI21ChipRegHandler.irq_LINK[i];
			_p->top_irq 	= gHDMI21ChipRegHandler.irq_TOP[i];
	
			_p->topMem.hwAddr = gHDMI21ChipRegHandler.top_ADDR[i];
			_p->topMem.size = gHDMI21ChipRegHandler.top_SIZE[i];
			_p->topMem.pSwAddr = NULL;

			_p->linkMem.hwAddr = gHDMI21ChipRegHandler.ctrl_ADDR[i];
			_p->linkMem.size = gHDMI21ChipRegHandler.ctrl_SIZE[i];
			_p->linkMem.pSwAddr = NULL;
			
			_p->aledMem.hwAddr = gHDMI21ChipRegHandler.aled_ADDR[i];
			_p->aledMem.size = gHDMI21ChipRegHandler.aled_SIZE[i];
			_p->aledMem.pSwAddr = NULL;

			_p->phyPdcMem.hwAddr = gHDMI21ChipRegHandler.phyPdc_ADDR[i];
			_p->phyPdcMem.size = gHDMI21ChipRegHandler.phyPdc_SIZE[i];
			_p->phyPdcMem.pSwAddr = NULL;

			_p->phyPostDrMem.hwAddr = gHDMI21ChipRegHandler.phyPostDr_ADDR[i];
			_p->phyPostDrMem.size = gHDMI21ChipRegHandler.phyPostDr_SIZE[i];
			_p->phyPostDrMem.pSwAddr = NULL;

			memset((void *)&_p->isr_count0, 0, (sizeof(UINT32) * HDMI21_ISR_MAXNUM));
			memset((void *)&_p->isr_count1, 0, (sizeof(UINT32) * HDMI21_ISR_MAXNUM));
		
			_p->repeaterHpd = 0;
			_p->is8KModel = gIsHDMI8KModel;
			_p->hdrOverRide = 0; 

			/* 2020/03/30 : Low Power Mode */
			_p->isV4l2Activated = 0;

			/* 2021/04/30 : Sleep Mode */
			_p->isSleepMode = 0;
		
			/* 2021/05/02 : DDC Mon */
			_p->isDdcMonEnabled = 0;
			_p->pDdcBuf = NULL;
			_p->ddcBufCnt = 0;
			_p->ddcBufPnt = 0;
			_p->ddcBufPrevBank = 0;
		
			/* 2021/06/16 */
			_p->zombieMode = 0;

			/* 2022/09/14 */
			_p->filterSelSwWaCnt = 0;

			/* 2025/04/29 */
			_p->isPqeSuspend = false;
			_p->disableAledEdid = 0;
		}

		gHDMI21RxHandler[0].irq_link_handler = HDMI21_HAL_RX0_Link_IRQ_Handler;
		gHDMI21RxHandler[1].irq_link_handler = HDMI21_HAL_RX1_Link_IRQ_Handler;
		gHDMI21RxHandler[2].irq_link_handler = HDMI21_HAL_RX2_Link_IRQ_Handler;
		gHDMI21RxHandler[3].irq_link_handler = HDMI21_HAL_RX3_Link_IRQ_Handler;
		gHDMI21RxHandler[4].irq_link_handler = HDMI21_HAL_RX4_Link_IRQ_Handler;

		gHDMI21RxHandler[0].irq_top_handler = HDMI21_HAL_RX0_Top_IRQ_Handler;
		gHDMI21RxHandler[1].irq_top_handler = HDMI21_HAL_RX1_Top_IRQ_Handler;
		gHDMI21RxHandler[2].irq_top_handler = HDMI21_HAL_RX2_Top_IRQ_Handler;
		gHDMI21RxHandler[3].irq_top_handler = HDMI21_HAL_RX3_Top_IRQ_Handler;
		gHDMI21RxHandler[4].irq_top_handler = HDMI21_HAL_RX4_Top_IRQ_Handler;

		gHDMI21RxHandler[0].control_link_irq = HDMI21_HAL_RX0_Enable_Link_IRQ;
		gHDMI21RxHandler[1].control_link_irq = HDMI21_HAL_RX1_Enable_Link_IRQ;
		gHDMI21RxHandler[2].control_link_irq = HDMI21_HAL_RX2_Enable_Link_IRQ;
		gHDMI21RxHandler[3].control_link_irq = HDMI21_HAL_RX3_Enable_Link_IRQ;
		gHDMI21RxHandler[4].control_link_irq = HDMI21_HAL_RX4_Enable_Link_IRQ;

		gHDMI21RxHandler[0].control_top_irq = HDMI21_HAL_RX0_Enable_Top_IRQ;
		gHDMI21RxHandler[1].control_top_irq = HDMI21_HAL_RX1_Enable_Top_IRQ;
		gHDMI21RxHandler[2].control_top_irq = HDMI21_HAL_RX2_Enable_Top_IRQ;
		gHDMI21RxHandler[3].control_top_irq = HDMI21_HAL_RX3_Enable_Top_IRQ;
		gHDMI21RxHandler[4].control_top_irq = HDMI21_HAL_RX4_Enable_Top_IRQ;

		gHDMI21RxHandler[0].link_write = HDMI21_HAL_Rx_LINK_Write_Port0;
		gHDMI21RxHandler[1].link_write = HDMI21_HAL_Rx_LINK_Write_Port1;
		gHDMI21RxHandler[2].link_write = HDMI21_HAL_Rx_LINK_Write_Port2;
		gHDMI21RxHandler[3].link_write = HDMI21_HAL_Rx_LINK_Write_Port3;
		gHDMI21RxHandler[4].link_write = HDMI21_HAL_Rx_LINK_Write_Port4;

		gHDMI21RxHandler[0].link_read = HDMI21_HAL_Rx_LINK_Read_Port0;
		gHDMI21RxHandler[1].link_read = HDMI21_HAL_Rx_LINK_Read_Port1;
		gHDMI21RxHandler[2].link_read = HDMI21_HAL_Rx_LINK_Read_Port2;
		gHDMI21RxHandler[3].link_read = HDMI21_HAL_Rx_LINK_Read_Port3;
		gHDMI21RxHandler[4].link_read = HDMI21_HAL_Rx_LINK_Read_Port4;

		gHDMI21RxHandler[0].top_write = HDMI21_HAL_Rx_TOP_Write_Port0;
		gHDMI21RxHandler[1].top_write = HDMI21_HAL_Rx_TOP_Write_Port1;
		gHDMI21RxHandler[2].top_write = HDMI21_HAL_Rx_TOP_Write_Port2;
		gHDMI21RxHandler[3].top_write = HDMI21_HAL_Rx_TOP_Write_Port3;
		gHDMI21RxHandler[4].top_write = HDMI21_HAL_Rx_TOP_Write_Port4;

		gHDMI21RxHandler[0].top_read = HDMI21_HAL_Rx_TOP_Read_Port0;
		gHDMI21RxHandler[1].top_read = HDMI21_HAL_Rx_TOP_Read_Port1;
		gHDMI21RxHandler[2].top_read = HDMI21_HAL_Rx_TOP_Read_Port2;
		gHDMI21RxHandler[3].top_read = HDMI21_HAL_Rx_TOP_Read_Port3;
		gHDMI21RxHandler[4].top_read = HDMI21_HAL_Rx_TOP_Read_Port4;

		gHDMI21RxHandler[0].aled_write = HDMI21_HAL_Rx_ALED_Write_Port0;
		gHDMI21RxHandler[1].aled_write = HDMI21_HAL_Rx_ALED_Write_Port1;
		gHDMI21RxHandler[2].aled_write = HDMI21_HAL_Rx_ALED_Write_Port2;
		gHDMI21RxHandler[3].aled_write = HDMI21_HAL_Rx_ALED_Write_Port3;
		gHDMI21RxHandler[4].aled_write = HDMI21_HAL_Rx_ALED_Write_Port4;

		gHDMI21RxHandler[0].aled_read = HDMI21_HAL_Rx_ALED_Read_Port0;
		gHDMI21RxHandler[1].aled_read = HDMI21_HAL_Rx_ALED_Read_Port1;
		gHDMI21RxHandler[2].aled_read = HDMI21_HAL_Rx_ALED_Read_Port2;
		gHDMI21RxHandler[3].aled_read = HDMI21_HAL_Rx_ALED_Read_Port3;
		gHDMI21RxHandler[4].aled_read = HDMI21_HAL_Rx_ALED_Read_Port4;

		gHDMI21RxHandler[0].phyPDC_write = HDMI21_HAL_Rx_PhyPDC_Write_Port0;
		gHDMI21RxHandler[1].phyPDC_write = HDMI21_HAL_Rx_PhyPDC_Write_Port1;
		gHDMI21RxHandler[2].phyPDC_write = HDMI21_HAL_Rx_PhyPDC_Write_Port2;
		gHDMI21RxHandler[3].phyPDC_write = HDMI21_HAL_Rx_PhyPDC_Write_Port3;
		gHDMI21RxHandler[4].phyPDC_write = HDMI21_HAL_Rx_PhyPDC_Write_Port4;

		gHDMI21RxHandler[0].phyPDC_read = HDMI21_HAL_Rx_PhyPDC_Read_Port0;
		gHDMI21RxHandler[1].phyPDC_read = HDMI21_HAL_Rx_PhyPDC_Read_Port1;
		gHDMI21RxHandler[2].phyPDC_read = HDMI21_HAL_Rx_PhyPDC_Read_Port2;
		gHDMI21RxHandler[3].phyPDC_read = HDMI21_HAL_Rx_PhyPDC_Read_Port3;
		gHDMI21RxHandler[4].phyPDC_read = HDMI21_HAL_Rx_PhyPDC_Read_Port4;

		gHDMI21RxHandler[0].phyDR_write = HDMI21_HAL_Rx_PhyDR_Write_Port0;
		gHDMI21RxHandler[1].phyDR_write = HDMI21_HAL_Rx_PhyDR_Write_Port1;
		gHDMI21RxHandler[2].phyDR_write = HDMI21_HAL_Rx_PhyDR_Write_Port2;
		gHDMI21RxHandler[3].phyDR_write = HDMI21_HAL_Rx_PhyDR_Write_Port3;
		gHDMI21RxHandler[4].phyDR_write = HDMI21_HAL_Rx_PhyDR_Write_Port4;

		gHDMI21RxHandler[0].phyDR_read = HDMI21_HAL_Rx_PhyDR_Read_Port0;
		gHDMI21RxHandler[1].phyDR_read = HDMI21_HAL_Rx_PhyDR_Read_Port1;
		gHDMI21RxHandler[2].phyDR_read = HDMI21_HAL_Rx_PhyDR_Read_Port2;
		gHDMI21RxHandler[3].phyDR_read = HDMI21_HAL_Rx_PhyDR_Read_Port3;
		gHDMI21RxHandler[4].phyDR_read = HDMI21_HAL_Rx_PhyDR_Read_Port4;

		/* Not in Device Handler, but this should be set as well on the same sequence */
		sDscTopHdmi21.pSwAddr = NULL;
		sDscTopHdmi21.hwAddr  = gHDMI21ChipRegHandler.dsc_top_ADDR;
		sDscTopHdmi21.size	  = gHDMI21ChipRegHandler.dsc_top_SIZE;

		/* Not in Device Handler, but this should be set as well on the same sequence */
		sDscCoreHdmi21.pSwAddr = NULL;
		sDscCoreHdmi21.hwAddr  = gHDMI21ChipRegHandler.dsc_core_ADDR;
		sDscCoreHdmi21.size	   = gHDMI21ChipRegHandler.dsc_core_SIZE;

		/* Not in Device Handler, but this should be set as well on the same sequence */
		sFecTopHdmi21.pSwAddr = NULL;
		sFecTopHdmi21.hwAddr  = gHDMI21ChipRegHandler.fec_top_ADDR;
		sFecTopHdmi21.size	  = gHDMI21ChipRegHandler.fec_top_SIZE;

		/* Not in Device Handler, but this should be set as well on the same sequence */
		sAledTopHdmi21.pSwAddr = NULL;
		sAledTopHdmi21.hwAddr = gHDMI21ChipRegHandler.aled_top_ADDR;
		sAledTopHdmi21.size = gHDMI21ChipRegHandler.aled_top_SIZE;


		/* Temporal code for M23 use only */
		if(lx_chip() == LX_CHIP_M23) {
			sAledTopHdmi21P23.pSwAddr	= NULL;
			sAledTopHdmi21P23.hwAddr	= gHDMI21ChipRegHandler.aled_top_P23_ADDR;
			sAledTopHdmi21P23.size		= gHDMI21ChipRegHandler.aled_top_P23_SIZE;
		}		

		/* Not in Device Handler, but this should be set as well on the same sequence */
		sPqeHdrMem.pSwAddr = NULL;
		#ifdef BUILD_FEATURE_audio_board
		sPqeHdrMem.hwAddr = 0x0;
		sPqeHdrMem.size = 0x0;
		#else
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, a0) ) {
			sPqeHdrMem.hwAddr = HDMI21_PQE_O26_HDR_INFO_ADDR;
			sPqeHdrMem.size = HDMI21_PQE_O26_HDR_INFO_SIZE;
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, a0) ) {
			sPqeHdrMem.hwAddr = HDMI21_PQE_O24_HDR_INFO_ADDR;
			sPqeHdrMem.size = HDMI21_PQE_O24_HDR_INFO_SIZE;
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, a0) ) {
			sPqeHdrMem.hwAddr = HDMI21_PQE_M23_HDR_INFO_ADDR;
			sPqeHdrMem.size = HDMI21_PQE_M23_HDR_INFO_SIZE;
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, a0) ) {
			sPqeHdrMem.hwAddr = HDMI21_PQE_O22_HDR_INFO_ADDR;
			sPqeHdrMem.size = HDMI21_PQE_O22_HDR_INFO_SIZE;
		}
		else {
			sPqeHdrMem.hwAddr = HDMI21_PQE_O20_HDR_INFO_ADDR;
			sPqeHdrMem.size = HDMI21_PQE_O20_HDR_INFO_SIZE;
		}
		#endif
	}

	/* For AC/DC Case */
	for(i=0; i<g_hdmi20_number_of_ports; i++) {
		_p = &gHDMI21RxHandler[i];

		/* Low Power Mode Cnt */
		_p->lowPowerAccumCnt = 0;
	}

	/* Reset Input Chg Cng */
	gHdmi21InputChgCnt = 0;
}



static void __HDMI21_HAL_Rx_Set_LocalVideoMuteColor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 isYCbCr444or422)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	HDMI21_LINE_DBG(1351, "DBG %d : Local Video Mute Color->isYCbCr444or422[%d]\n", _p->port, isYCbCr444or422);

	/* DBG : Do not enter on specific DBG condition */
	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1350){
		return;
	}

	HDMI21_VPROC_Rx_Set_MuteColor(_p, isYCbCr444or422);

	return;
}


static int __HDMI21_HAL_Rx_Get_IsStableTimingInfoEmpty(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	int _cmpResult = 0;

	_cmpResult = memcmp((void *)&_p->video, (char[sizeof(HDMI21_HAL_VIDEO_TIMING_T)]){0}, sizeof(HDMI21_HAL_VIDEO_TIMING_T));

	if(_cmpResult == 0){
		/* If Empty return 1 */
		ret = 1;
	}

	return ret;
}

static int __HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int clear)
{
	int ret = RET_ERROR;
	UINT32 __data;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	if(clear){
		HDMI20_PRINT("Port[%d] : Clear Video timing info, Caller[%pS]\n", _p->port, __builtin_return_address(0));
		
		memset((void *)&_p->video, 0, sizeof(HDMI21_HAL_VIDEO_TIMING_T));
		HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA_MAXNUM,_p->port );
		HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_MAXNUM, _p->port);


		/* TEMPDBG:JINWOO Choi reverse */
		HDMI21_VPROC_Rx_Set_SyncGenSel(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value);

		_p->hdcp23_csm = 0;
		_p->idleTick = 0;
		_p->videoChgCount = 0;
		_p->stablehdcp14time = 0;
		_p->allm_recieve_time = 0;
		_p->doviTimeStamp = 0;
		_p->dolbyVsiTimeStamp = 0;
		_p->em_vrr_recieve_time = 0;
		_p->em_qms_recieve_time = 0;
		_p->isAllmMode = 0;
		_p->lnLockLossCnt = 0;
		_p->pktErrStateCnt = 0;
		_p->stable_cnt = 0;	// 2018/08/09 : Sometimes, stable cnt are not reseted to 0. need to add more lines for this
		_p->real_vfreq = 0;
		_p->isDolbyHDR = (int)HDMI_DOLBY_STATE_OFF;
		_p->isFreeSyncMode = 0;
		_p->isMConst = 0;
		_p->isQmsMode = 0;
		_p->em_qms_mconst_zero_cnt = 0;
		_p->isFvaMode = 0;
		_p->isDSC = 0;

		/* Set VFreq counter ref clock */
		if((_p->top_read(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK)& 0xFFFF) != 0x1E0){
			_p->top_write(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK, 0x1E0);
		}

		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_DCM_8_BIT_ON_594].value >0){
			/* Need to consider whether to have this for O20 */
		}

		ret = RET_OK;
	}
	else{
		/* 2020/04/02 : For Low power module */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value > 0) {
			/* Reset FS module : Set High*/
			__data = HDMI21_TOP_FIELD_AD_FS_1_MODULE_RESET;
			_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);
		}

		__HDMI21_HAL_Rx_Reset_AsyncBridge(_p->port);

		HDMI20_PRINT("Port[%d] Update Timing :[%ux%u%c@%03uHz %s %s VIC:%u %s] Clk[%llu] %s[%d][%d][%d][%d]/[%d][%d][%d][%d]/[%d][%d][%d][%d]/[%d][%d][%d][%d]. SCDC[%d]\n", _p->port,\
				_p->hwVideo.hactive, _p->hwVideo.vactive, _p->hwVideo.interlaced? 'i' : 'p', _p->hwVideo.vfreq, _p->hwVideo.dvi? "DVI" : "HDMI",\
				__deepcolor_to_str(_p->hwVideo.deep_color_mode), _p->hwVideo.vicCode, __csc_to_str(_p->hwVideo.video_format),\
				_p->phy_tmds_clk, (_p->phyCurrentTMDSExceptionRange>=0)?"TCS":" Delta",\
				_p->phyTCSMin[0], _p->phyTCSMin[1],_p->phyTCSMin[2],_p->phyTCSMin[3],\
				_p->phyTCSMax[0],_p->phyTCSMax[1],_p->phyTCSMax[2],_p->phyTCSMax[3],\
				_p->phyTCSResult[0],_p->phyTCSResult[1],_p->phyTCSResult[2],_p->phyTCSResult[3],\
				_p->phyTMDSError[0],_p->phyTMDSError[1],_p->phyTMDSError[2],_p->phyTMDSError[3],\
				_p->phyInitiatedMode);


		if((_p->link_read(0x2f4) & 0x100) == 0x0) {
			HDMI20_PRINT("WARN[%d] : AVMute status is HIGH\n", _p->port);
		}

		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_DCM_8_BIT_ON_594].value >0){
			/* Need to consider whether to have this for O20 */
		}
		_p->updateTimingTime = jiffies_to_msecs(jiffies);

		/* Copy hwVideo data to Video */
		memcpy((void *)&_p->video, (void *)&_p->hwVideo, sizeof(HDMI21_HAL_VIDEO_TIMING_T));

		if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(_p)){
			/* SW defence code for DVi */
			_p->video.pixel_repetition = 0;
		}

		/* 2020/04/02 : For Low power module */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value > 0) {
			if(_p->lowPowerMode <= HDMI21_HAL_POWER_NORMAL) {
				/* Reset FS module : Set Low */
				HDMI21_LINE_DBG(12001, "INFO[%d] : LowPower FakeSync Module R[0x314]<=[0x0]\n", _p->port);
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, 0);
			}
		}

		/* 2020/04/16 : Software Workaround for PixelPacking Phase Issue */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_PIXEL_PACKING_WATCHDOG].value > 0) {
			__HDMI21_HAL_Rx_WatchDog_PixelPackingPhase(_p);
		}

		/* 2019/11/20 : Lane Lock count loss counter should be reseted */
		_p->lnLockLossCnt = 0;

		/* 2020/01/23 : this should be reset on timing update */
		_p->pktErrStateCnt = 0;

		/* 2020/03/25 : Reset idle Timer from this point */
		_p->idleTick = 0;

		/* 2020/01/31 H5D SWWA */
		if((_p->port == 4)&&(gHDMI21RxDevVideoControler[HDMI21__VIDEO_H5D_8K_CHECK_HPD_SWWA].value > 0)){
			if(( _p->video.vactive < 4310) || (_p->video.vactive > 4330) || (_p->video.hactive > 7690) || (_p->video.hactive < 7670)){
				if(( _p->video.vactive < 2150) || (_p->video.vactive > 2170) || (_p->video.hactive > 3850) || (_p->video.hactive < 3830)) {
					HDMI20_PRINT("Warning [%d] : Detected overlimit resolution(%xx%x on H5D Port! HPD Toggle!\n", _p->port, _p->video.hactive, _p->video.vactive);
					HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
				}
			}
		}

		/* TEMPDBG:jinwoo choi request */
		if(( __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L)\
				&& (_p->video.vactive <= 500) && (_p->isDSC == 0)){
			HDMI20_PRINT("Notice [%d] : Detected V480 video on FRL10/12G. Set SyncGenMode to 1\n", _p->port);
			HDMI21_VPROC_Rx_Set_SyncGenSel(_p, 1);
		
			/* 2025/07/01 won.hur : SW WA for Q980B CTS for FRL 12G4L + 480P + 12BIT */
			if(gHDMI21RxDevLinkControler[HDMI21__LINK_FRL12G4L_480P_12B_FORCE_WA].value > 0) {
				if((_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) && (_p->video.deep_color_mode == 0x6)) {
					HDMI20_PRINT("Notice [%d] : Set DCM 12BIT Override for FRL 12G4L + 480P + 12BPC\n", _p->port);
					HDMI21_VPROC_Rx_Set_OverRideColorDepth(_p, 1, HDMI21_RX_VPROC_CD_12BIT);
					
					/* Set History */
					_p->isFrl480pDcmForceSwWa = true;
				}
			}
	
		}
		else if(( __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L)\
				&& ((_p->video.vactive >= 1078) && _p->video.vactive <= 1082) && ( _p->hwVideo.vfreq <= 24) && (_p->isDSC == 0)){
			HDMI20_PRINT("Notice [%d] : Detected V1080 video on FRL10/12G. Set SyncGenMode to 1\n", _p->port);
			/* 2025/03/25 won.hur : I guess this code should remain for O26 as well, since I do not know the history for O24.*/
			if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
				HDMI21_VPROC_Rx_Set_SyncGenSel(_p, 1);
			}
		}
		else {
			if(_p->isDSC > 0) {
				HDMI21_LINE_DBG(6649, "DBG [%d] : Detected DSC, set SyncGenMode to %d\n", _p->port, \
						gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_FOR_DSC].value);
				HDMI21_VPROC_Rx_Set_SyncGenSel(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_FOR_DSC].value);
			
				if(_p->hwVideo.vfreq >= 130) {
					HDMI21_LINE_DBG(6650, "DBG[%d] : Detected Over 130Hz on DSC\n", _p->port);	
					_p->link_write(0x42C, 0xC0000);
				}
				else {
					HDMI21_LINE_DBG(6650, "DBG[%d] : Detected Under 130Hz on DSC. Vfreq[%d]\n", _p->port, _p->hwVideo.vfreq);	
				}
			}
			else {
				if((gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OFF_FOR_UNDER].value > 0) && (_p->hwVideo.vfreq <= gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_OFF_FOR_UNDER].value)){
					HDMI21_VPROC_Rx_Set_SyncGenSel(_p, 0);
				}
				else if(_p->hwVideo.interlaced > 0) {
					HDMI21_LINE_DBG(6649, "DBG [%d] : Detected Interlaced, set SyncGenMode to 0\n", _p->port);
							HDMI21_VPROC_Rx_Set_SyncGenSel(_p, 0);
				}
				else {
					HDMI21_VPROC_Rx_Set_SyncGenSel(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value);
				}
			}
		}

		/* 2020/11/02 : Clear CED Counters*/
		if( __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) <= HDMI21_HAL_PHY_INITIATED_6G){
			HDMI21_SCDC_Rx_Set_CedCountRst(_p, 1);
			HDMI21_SCDC_Rx_Set_CedCountRst(_p, 0);
		}

		/* 2019/12/27 won.hur : Incase roll back from DSC */
		if(_p->isDSC == 0) {
			/* Some values are being override opposed to API control. Need to get this organinzed */
			HDMI21_VPROC_Rx_Set_LinkBypassForDSC(_p, 0, 0);
		}

		if(HDMI21_HDCP23_Module_Get_IsRepeater() > 0) {
			_p->hdcp23_csm = HDMI21_HDCP23_Module_Get_ContentType(_p->port);
		}

		ret = RET_OK;
	}

	return ret;
}

static int __HDMI21_HAL_Rx_Get_IsHwInDVIState(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler )
{
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;


	if(HDMI21_DEFRAMER_Rx_Get_IsDVIMode(_p) == true) ret = 1;
	else ret = 0;



	return ret;
}


static int __HDMI21_HAL_Rx_Set_UnInitialize(void)
{
	int ret = RET_OK;

	do{

	} while(0);

	return ret;

}

static int __HDMI21_HAL_Rx_Get_ListOfNotSupportingVideo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;

		/* DSC Defence */
		if(_p->isDSC > 0) {
			ret = RET_OK;
			break;
		}

		/* No support on Pixel repition over 1 */
		if(_p->video.pixel_repetition >1){
			//HDMI20_VIDEO("ERROR %d : Does not support pixel repetition more than 1. PR[%d]\n", port, _p->video.pixel_repetition);
			break;
		}

		/* Invalid Format Check */
		if((_p->video.hactive < 320) || (_p->video.vactive < 240) )
		{
			HDMI21_LINE_DBG(3423, "ERROR %d : InValid Format for Active Size,  hActive[%d] vActive [%d]\n", _p->port,\
					_p->video.hactive, _p->video.vactive);
			break;
		}

		/* Support 2D 1280x1024i@86  by 20120202
		 * Not support Master #333 - because MASTER timing issue */
		if (_p->video.hactive == 1280 && \
				_p->video.vactive == 512 &&\
				_p->video.interlaced == 0)
		{
			HDMI20_VIDEO("ERROR %d : not support 2D 1280x1024!@86 of Master #333\n", _p->port);
			break;
		}

		//* Support 2D 1920x1080i@50 of EIA-861D  for any PC Card  by 20111010
		//* Not support Master #840 - because MASTER timing issue
		if (_p->video.htotal == 2304)// && gHDMI21RxHandler[port].timing_info.hActive == 1920 && gHDMI21RxHandler[port].timing_info.scanType == 1)
		{
			if (_p->video.vtotal == 1250)
			{
				HDMI20_VIDEO("NOTI [%d] : Support 2D 1920x1080!@50 of EIA-861D \n",_p->port);

			}
			else
			{
				HDMI20_VIDEO("ERROR %d : not support 2D 1920x1080!@50 of EIA-861D Master #840\n",_p->port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}





/* IOCTL */
static int __HDMI21_HAL_Rx_Set_HDCP14_KSVList(UINT8 port, LX_HDMI20_HDCP14_RP_T *pData, int size)
{
	int ret = RET_ERROR;
	LX_HDMI20_HDCP14_RP_T __data;
	int i,y;
	int retryCount = 30; 

	HDMI20_VIDEO("[%s] called\n", __F__);

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_HDCP14_RP_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_HDCP14_RP_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if( copy_from_user(&__data, (void __user *)pData, sizeof(LX_HDMI20_HDCP14_RP_T))){
			HDMI20_ERROR("Cannot copy HDCP1.4 Repeater data structure from user\n");
			break;
		}

		if(__data.count >= 32){
			HDMI20_ERROR("Error! Count exceeded max count(%d)[32]\n", __data.count);
			break;
		}

		HDMI20_VIDEO("Recieved HDCP1.4 KSV data, Depth[%d]/Count[%d]/AddrKSV[0x%p]\n", __data.depth, __data.count, (void *)__data.ksvList);

		y = 0;
		for(i=0;i<__data.count;i++){
			HDMI20_DBG("DBG [%d] : [%d] <= [0x%08x] [0x%08x]\n", port, i, __data.ksvList[y], __data.ksvList[y+1]);
			y = y+2;
		}

		while(1){
			ret = HDMI21_HDCP_Rx_Set_HDCP14RptKsvList(&gHDMI21RxHandler[port], (UINT32 *)&__data.ksvList, __data.count, __data.depth);
			if(((ret < 0)&&(ret != -EAGAIN)) || (ret >= 0)){

				if(ret < 0) HDMI20_WARN("Warning [%d] : HDCP1.4 KSV List Process Error[%d]\n", port, ret);
				else HDMI20_VIDEO("Notice [%d] : Success HDCP1.4 KSV List Process[%d]\n", port, ret);
				break;
			}

			if(retryCount <= 0){
				HDMI20_WARN("Warning [%d] : Waited but timeout on KSV List Process on RX side[%d]\n", port, ret);
				break;
			}

			HDMI20_WARN("Warning [%d] : Not yet for KSV List Process in Link. ksvListRet[%d]  RetryCnt[%d]\n", port,  ret ,retryCount);
			retryCount--;
			msleep(10);
		};

		if(ret < 0){
			HDMI20_ERROR("Error [%d] : Error code[%d] on KSV process\n", port, ret);	
		}
		else{
			HDMI20_VIDEO("Notice [%d] : Success on KSV Process[%d]\n", port, ret);
		}

	} while(0);

	return ret;
}

/* IOCTL */
static int __HDMI21_HAL_Rx_DBG_GetHDMIMiscInfo(UINT8 port, LX_HDMI20_RX_HDMI_MISC_T *pData, int size)
{
	int ret = RET_ERROR;
	LX_HDMI20_RX_HDMI_MISC_T userdata;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_RX_HDMI_MISC_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_RX_HDMI_MISC_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI20_RX_HDMI_MISC_T));
		#if 0

		/* Step 2. Copy data */
		userdata.kdrvVer = HDMI20_KERNEL_DRIVER_VER;
		userdata.avMute = gHDMI21RxHandler[port].ctrl.isMute;
		userdata.phyLockTime = (gHDMI21RxHandler[port].locking_time * gHDMI21Thread.mSleep);
		
		if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(port) == 0){
			userdata.n_param = gHDMI21RxHandler[port].ctrl.n_param;
			userdata.cts_param = gHDMI21RxHandler[port].ctrl.cts_param;
		}

		/* SCDC Info */
		tempData = gHDMI21RxHandler[port].ctrl.link_read(0x860);
		tempData &= 0x000000FF;
		userdata.scdcInfo.sink_version = (UINT8)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0x820);
		tempData &= 0x000000FF;
		userdata.scdcInfo.source_version = (UINT8)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0x820);
		if((tempData & 0x00020000) != 0) { userdata.scdcInfo.bit_ratio = 1; }
		if((tempData & 0x00010000) != 0) { userdata.scdcInfo.scramble_enable = 1; }
		if((tempData & 0x01000000) != 0) { userdata.scdcInfo.scramble_status = 1; }

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0x824);
		if((tempData & 0x00000100) != 0) { userdata.scdcInfo.clock_detect = 1; }
		if((tempData & 0x00000200) != 0) { userdata.scdcInfo.ch_locked[0] = 1; }
		if((tempData & 0x00000400) != 0) { userdata.scdcInfo.ch_locked[1] = 1; }
		if((tempData & 0x00000800) != 0) { userdata.scdcInfo.ch_locked[2] = 1; }

		tempData &= 0x7FFF0000;
		tempData = tempData >> 16; tempData &= 0x0000FFFF;
		userdata.scdcInfo.ch_error_count[0] = (UINT16)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0x828);
		tempData &= 0x00007FFF;
		userdata.scdcInfo.ch_error_count[1] = (UINT16)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0x828);
		tempData &= 0x7FFF0000;
		tempData = tempData >> 16; tempData &= 0x0000FFFF;
		userdata.scdcInfo.ch_error_count[2] = (UINT16)tempData;

		/* HDCP1.4 Info */
		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xE0);
		tempData &= 0x003F0000; tempData = tempData >> 16; tempData &= 0x0000003F;
		userdata.hdcpInfo.status = (UINT8)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xE0);
		tempData &= 0x000000FF;
		userdata.hdcpInfo.Ri[0] = (UINT8)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xE0);
		tempData &= 0x0000FF00; tempData = tempData >> 8; 
		userdata.hdcpInfo.Ri[1] = (UINT8)tempData;

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xE4);
		tempData &= 0x000000FF;
		userdata.hdcpInfo.Aksv[0] = (UINT8)(tempData);

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xE8);
		userdata.hdcpInfo.Aksv[1] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.Aksv[2] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.Aksv[3] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.Aksv[4] = (UINT8)(tempData & 0x000000FF);

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xEC);
		userdata.hdcpInfo.An[0] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.An[1] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.An[2] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.An[3] = (UINT8)(tempData & 0x000000FF);

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xF0);
		userdata.hdcpInfo.An[4] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.An[5] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.An[6] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.An[7] = (UINT8)(tempData & 0x000000FF);

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xCC);
		tempData &= 0x000000FF;
		userdata.hdcpInfo.Bksv[0] = (UINT8)(tempData);

		tempData = gHDMI21RxHandler[port].ctrl.link_read(0xD0);
		userdata.hdcpInfo.Bksv[1] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.Bksv[2] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.Bksv[3] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.Bksv[4] = (UINT8)(tempData & 0x000000FF);

		userdata.hdcpInfo.Bcaps = 0x81;

		if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(port) == 0){
			userdata.hdcpInfo.Bstatus[1] = 0x10;
			userdata.hdcpInfo.Bstatus[0] = 0x00;
		}

		/* Step x. Copy to User */
		ret = copy_to_user((LX_HDMI20_RX_HDMI_MISC_T *)pData, &userdata, sizeof(LX_HDMI20_RX_HDMI_MISC_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for HDMI MISC data on Port[%d].\n", port);
			break;
		}
		#endif
		ret = RET_OK;
	} while(0);

	return ret;
}


/* IOCTL */
static int __HDMI21_HAL_Rx_Get_HDCP14(UINT8 port, UINT32 *pData, int size)
{
	int ret = RET_ERROR;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_HDCP14_DATA_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_HDCP14_DATA_T), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		ret = copy_to_user((void __user *)pData, (void *)&gHDMI21RxHandler[port].hdcp, sizeof(LX_HDMI20_HDCP14_DATA_T));
		if(ret) {
			HDMI20_ERROR("Error on attempting to copy HDCP1.4 data to USER for Port[%d]\n", port);
			break;
		}
		else{
			HDMI20_INFO("Success copy HDCP1.4 data to USER for Port[%d]\n", port);
			ret = RET_OK;
		}

		ret = RET_OK;

	} while(0);

	return ret;

}

static int __HDMI21_HAL_Rx_Set_DisableHDMI(UINT8 port, int isDisable)
{
	int ret = RET_ERROR;

	do{
		HDMI20_INFO("Notice %d : Set Disable HDMI => [%s]\n", port, isDisable?"Disable":"Enable");

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(isDisable){
			gHDMI21RxHandler[port].hdmiDisabled = true;

			if(gHDMI21RxHandler[port].is5Vconnected > 0){
				HDMI21_HAL_ConnectCable(port, 0);
			}
		}
		else{
			gHDMI21RxHandler[port].hdmiDisabled = false;
			HDMI21_HAL_ConnectCable(port, 1);
		}

		ret = RET_OK;
	} while(0);

	return ret;
}



/* IOCTL */
static int __HDMI21_HAL_Rx_Set_HPD(UINT8 port ,UINT8 onOff, UINT8 force)
{
	int ret = RET_ERROR;
	UINT32 data;
	
	if(gHDMI21RxHandler[port].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return RET_ERROR;
	}

	if(force == 0){
		HDMI20_INFO("Port[%d] : HPD[%s]. Caller[%pS]\n", port, onOff?"UP":"DOWN", __builtin_return_address(0));

	}
	else{
		HDMI20_INFO("Port[%d] : Force HPD[%s]. Caller[%pS]\n", port, onOff?"UP":"DOWN", __builtin_return_address(0));
	}

	/* 2025/03/25 won.hur : This should remain for O26 as well ...*/
	if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
		if( gHdmi21WarmMode == 1) {
			HDMI20_PRINT("\n!!! In WarmMode : bypass HPD control !!!\n");
			return 0;
		}
	}

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		data = gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_HPD_DDC_SET);

		if(gHDMI21RxHandler[port].isHPDInverseMode){
			if(onOff){
				gHDMI21RxHandler[port].isHPD = 1;
				data &= (~HDMI21_TOP_FIELD_O_REG_HPD);
				//HDMI21_HAL_Rx_Set_AudioEnable(port, 0);
			}
			else{
				if(gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value > 0){
					HDMI20_INFO(" Delay requested for HPD Up [%d]msec\n", gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value);
					msleep(gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value);
				}
				gHDMI21RxHandler[port].isHPD = 0;
 				HDMI21_Tx_eARC_Disconnect(port);
				data |= (HDMI21_TOP_FIELD_O_REG_HPD);
			}
		}
		else {
			if(onOff){
				if(gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value > 0){
					HDMI20_INFO(" Delay requested for HPD Up [%d]msec\n", gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value);
					msleep(gHDMI21RxDevVideoControler[HDMI21__LINK_HPD_DELAY_TIME].value);
				}
				gHDMI21RxHandler[port].isHPD = 1;
				data |= (HDMI21_TOP_FIELD_O_REG_HPD);
				//HDMI21_HAL_Rx_Set_AudioEnable(port, 0);
			}
			else{
				gHDMI21RxHandler[port].isHPD = 0;
				HDMI21_Tx_eARC_Disconnect(port);
				data &= (~HDMI21_TOP_FIELD_O_REG_HPD);
			}
		}

		//gHDMI21RxHandler[port].hpd_request = 0;

		data |= (HDMI21_TOP_FIELD_O_REG_HPD_PORT_SELECT_VAL);
		gHDMI21RxHandler[port].top_write(HDMI21_TOP_REG_AD_MAIN_HPD_DDC_SET, data);

		if(gHDMI21RxHandler[port].hdmiDisabled > 0){
			if(gHDMI21RxDevVideoControler[HDMI21__PDB_LOW_ON_DISCONNECT].value > 0){
				HDMI20_INFO("Notice [%d] : HDMI disabled detected on HPD Down. Rxsense down also\n", port);
				HDMI21_PHY_Rx_Set_ControlPhyPdb(port, 0);
			}
		}

		ret = RET_OK;

	} while(0);

	return ret;
}

/* IOCTL */
static int __HDMI21_HAL_Rx_Set_EnableEDID(UINT8 port, UINT8 onOff)
{
	int ret = RET_ERROR;
	#if 0
	UINT32 __data = 0;
	UINT32 __data2 = 0;
	#endif

	HDMI20_INFO("Notice %d : Internal EDID is [%s]\n", port, onOff?"Enabled":"Disabled");
 
 	do{
 
		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

#if 0
		/* Set Flag */
		if(onOff == 0) {
			gHDMI21RxHandler[port].disableAledEdid = 1;
		}
		else {
			gHDMI21RxHandler[port].disableAledEdid = 0;
		}

		/* Set value */
		__data2 = 0x00FF0000;	
		/* Set APB */
		__HDMI21_HAL_Rx_ALED_TOP_Write(0x50, __data2); // 0xC8821050
		

		HDMI21_REG_RD(0xC883000C, __data);

		/* Set value */
		//__data = 0x00FF0006; 	/* LG TapBook Issue */
		if(gHDMI21RxHandler[0].disableAledEdid > 0) __data |= 0x4; 
		else __data &= (~0x4);
		
		if(gHDMI21RxHandler[1].disableAledEdid > 0) __data |= 0x10;
		else __data &= (~0x10);

		if(gHDMI21RxHandler[2].disableAledEdid > 0) __data |= 0x40;
		else __data &= (~0x40);

		if(gHDMI21RxHandler[3].disableAledEdid > 0) __data |= 0x100;
		else __data &= (~0x100);

		HDMI21_REG_WR(0xC883000C, __data);
		
	
		/* Set APB */
		//__HDMI21_HAL_Rx_ALED_TOP_Write(0x50, __data);
#endif
		ret = RET_OK;
 	} while(0);

	return ret;

}


static void __HDMI21_HAL_Rx_Set_ResetHandlerData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isCablePlug)
{
	int i;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;


	/* First step should always to clear Stable Timing Info to mute TV */
	__HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(_p, 1);

	if(isCablePlug)
	{
		/* AUX */
		_p->stableHist = 0;
		/* Link */
		_p->em_vrr_recieve_time = 0;
		_p->em_qms_recieve_time = 0;
		_p->allm_recieve_time = 0;	
		_p->doviTimeStamp = 0;
		_p->dolbyVsiTimeStamp = 0;
		_p->cable_connect_time = 0;		
		_p->connected5Vtime = 0;
		_p->hpd_request = 0;
		_p->fsm_phy_lock = 0; 
		_p->main_thread_init_request = 0; 
		_p->countOf6GHpdTgSwWa = gHDMI21RxDevVideoControler[HDMI21__HPD_TG_ON_6G_297].value;
		_p->is5Vconnected = 0;
		_p->isHPD = 0;
		_p->scdcTmdsMode = 0;
		_p->isPhyLocked = 0; 
		_p->scdc_change = 0; 
		_p->frlRateRcv = 0;

		/* PHY : All information should be initated on cable plug */
		_p->phyInitiatedMode = 0;	
		_p->phyCurrentTMDSExceptionRange = 0;
		_p->phyPrevTMDSExceptionRange = 0;
		_p->phyDcBalanceCounter = 0;
		_p->locking_time = 0;
		_p->phyTCSDone = 0;	
		_p->phyCrDone = 0;
		_p->real_tmds_clk = 0;
		_p->real_pixel_clk = 0;
		_p->real_vfreq = 0;
		_p->phyTCSState = 0;
		_p->phyTCSFailed = 0;
		_p->phyErrCounter = 0;
		for(i=0; i<HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY; i++)
		{
			_p->phyTCSDiff[i] = 0;
			_p->phyTCSMin[i] = 0;
			_p->phyTCSMax[i] = 0;
			_p->phyTCSResult[i] = 0;
			_p->phyTMDSError[i] = 0;
			_p->phySyncRecovery[i] = 0;
			_p->phyCEDError[i] = 0;
			_p->phyDeltaError[i] = 0;
			_p->phyDeltaPlus[i] = 0;
			_p->phyDeltaMinus[i] = 0;
			_p->phyDfeA01Result[i] = 0;
			_p->phyDfeA11Result[i] = 0;
			_p->phyDfeB1Result[i] = 0;
			_p->phyDfeB2Result[i] = 0;
			_p->phyDfeB3Result[i] = 0;
			_p->phyDfeB4Result[i] = 0;
			_p->phyDfeB5Result[i] = 0;
		}

		memset((void *)&_p->phyExceptionState, 0, sizeof(HDMI21_HAL_PHY_EXCEPTION_CASE_T));

		/* FRL CTS Mode */
		_p->isPhyFrlCtsMode = 0;
	}

	/* Link */
	_p->isMute = 0;
	_p->stable_cnt = 0;
	_p->isDolbyHDR = 0;	
	_p->isDSC	= 0;
	_p->vfreq_min = 0; 
	_p->vfreq_max = 0;
	_p->isFreeSyncMode = 0;
	_p->isMConst = 0;
	_p->isQmsMode = 0;
	_p->isFvaMode = 0;
	_p->isAllmMode = 0;
	_p->avmute_on_time = 0;	
	_p->localmutetimer = 0;	
	_p->stablehdcp14time = 0;
	_p->video_change = 0;
	_p->audio_change = 0;
	_p->tmds_change = 0;
	_p->hdcp_change = 0;
	_p->dcm_change = 0;	
	_p->isHDCP22 = 0;
	_p->isHDCP14 = 0;
	_p->isTimingInvalid = 0;
	_p->videoChgCount = 0;
	_p->vidChgTime = 0;
	_p->filterSelStuck = 0;
	_p->consecutiveFilStuckCnt = 0;
	_p->phyStuckVal = 0;

	/* Set VFreq counter ref clock */
	if((_p->top_read(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK)& 0xFFFF) != 0x1E0){
		_p->top_write(HDMI21_TOP_REG_VFREQ_COUNTER_REF_CLK, 0x1E0);
	}

	/* Initiate HDMI21 Video timing Info */
	memset((void *)&_p->video, 0, sizeof(HDMI21_HAL_VIDEO_TIMING_T));
	memset((void *)&_p->hwVideo, 0, sizeof(HDMI21_HAL_VIDEO_TIMING_T));

	/* Reset Data Packet Buffer */
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA_MAXNUM, _p->port);
	
	/* Reset EM Data Packet Buffer */
	HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_MAXNUM, _p->port);

	/* Reset PPS Data */
	memset((HDMI21_HAL_DSC_PPS_O20A0_T *)&_p->pps, 0, sizeof(HDMI21_HAL_DSC_PPS_O20A0_T));

	/* Initiate handlers' audio data */
	_p->isAudioARCMode = 0;
	_p->isAudioMute = 0;
	_p->isAudioMuteControl = 0;
	_p->isAudioTypeChangeIrq = 0;
	_p->isAudioRegReady = 0;
	_p->isHBRaudio = 0;
	_p->isPC = 0;
	_p->isAstroFRLSwWa = 0;
	_p->lnLockLossCnt = 0;

	/* FRL State SW WA */
	_p->phyFrlSwWaState = 0;

	_p->em_vrr_baseRate = 0;
	_p->em_qms_baseRate = 0;
	_p->em_qms_tfr = 0;

	/* HDCP2.3 Repeater */
	_p->hdcp23_csm = 0;
}

/* DBG function */
static void __HDMI21_HAL_Rx_DBG_PrintPhySetting(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	
	UINT32 __data = 0;
	UINT32 __reg  = 0;

	
	/* Connection */
	printk("[Connection Setting]\n");
	
	__reg = 0x38; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t1) MAN_CON_SEL        [0x28]:[0x38] => [0x%02x]\n", __data);		

	/* HDMI Mode */
	printk("[HDMI Mode Setting]\n");
	
	__reg = 0x2a; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t1) Manual HDMI20_MODE [0x28]:[0x2A] => [0x%02x]\n", __data);	
	
	__reg = 0x26; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t2) Manual HDMI21_MODE [0x28]:[0x26] => [0x%02x]\n", __data);
	
	__reg = 0x88; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t3) SCR_MAN_OFF        [0x48]:[0x88] => [0x%02x]\n", __data);
	
	__reg = 0x23; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t4) EQ_HDMI20_VAL      [0x28]:[0x23] => [0x%02x]\n", __data);

	__reg = 0xa8; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t5) EQ_DHFG            [0x38]:[0xa8] => [0x%02x]\n", __data);

	/* PHY DC */
	printk("[PHY DC Setting]\n");

	__reg = 0x70; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t1) VBGR               [0x28]:[0x70] => [0x%02x]\n", __data);

	__reg = 0x39; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t2) EQ_DOGH            [0x28]:[0x39] => [0x%02x]\n", __data);

	__reg = 0x5D; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t3) ODT_FREQ_DIV       [0x28]:[0x5D] => [0x%02x]\n", __data);
		
	__reg = 0x24; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t4) EQ_ICTRL           [0x28]:[0x24] => [0x%02x]\n", __data);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, b0) ) {
		__reg = 0x73; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
		printk("\t5) IDR                [0x38]:[0x73] => [0x%02x]\n", __data);
	}
	else{
		__reg = 0x45; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
		printk("\t5) IDR                [0x38]:[0x45] => [0x%02x]\n", __data);
	}


	__reg = 0x59; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t6) ISUM/IDAC          [0x38]:[0x59] => [0x%02x]\n", __data);
		
	__reg = 0x05; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t7) CH0_RW_AUTO_MODE=  [0x38]:[0x05] => [0x%02x]\n", __data);

	__reg = 0x41; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t8) PI_SET_MAN_MODE    [0x28]:[0x41] => [0x%02x]\n", __data);

	/* EQ */
	printk("[EQ Setting]\n");
	
	__reg = 0x15; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t1) EQ RS_MAN_SEL      [0x48]:[0x15] => [0x%02x]\n", __data);

	__reg = 0x16; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t2) EQ_RS_MAN_CH0      [0x48]:[0x16] => [0x%02x]\n", __data);

	__reg = 0x17; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t3) EQ_RS_MAN_CH1      [0x48]:[0x17] => [0x%02x]\n", __data);

	__reg = 0x18; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t4) EQ_RS_MAN_CH2      [0x48]:[0x18] => [0x%02x]\n", __data);

	__reg = 0x19; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t5) EQ_RS_MAN_CH3      [0x48]:[0x19] => [0x%02x]\n", __data);

	__reg = 0xA2; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t6) EQ_CS_MAN_CH0      [0x38]:[0xA2] => [0x%02x]\n", __data);

	__reg = 0xA3; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t7) EQ_CS_MAN_CH1      [0x38]:[0xA3] => [0x%02x]\n", __data);

	__reg = 0xA4; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t8) EQ_CS_MAN_CH2      [0x38]:[0xA4] => [0x%02x]\n", __data);

	__reg = 0xA5; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t9) EQ_CS_MAN_CH3      [0x38]:[0xA5] => [0x%02x]\n", __data);

	/* CDR */
	printk("[CDR Setting]\n");

	__reg = 0x5A; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t1) CDR ANA_CDR_SEL    [0x38]:[0x5A] => [0x%02x]\n", __data);

	__reg = 0xF3; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t2) FILTER_SEL/G1_SEL  [0x38]:[0xF3] => [0x%02x]\n", __data);

	__reg = 0xF4; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t3) G@_SEL             [0x38]:[0xF4] => [0x%02x]\n", __data);

	__reg = 0x75; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t4) PHANTOM_MAN_VAL    [0x38]:[0x75] => [0x%02x]\n", __data);

	__reg = 0x74; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t5) PHANTOM_FIX_MODE   [0x38]:[0x74] => [0x%02x]\n", __data);

	__reg = 0x70; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t6) DR_FILTER          [0x38]:[0x70] => [0x%02x]\n", __data);

	/* CS SCAN*/
	printk("[CS SCAN Setting]\n");

	__reg = 0x93; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t1) DEL_SCAN2/ADD_VAL  [0x38]:[0x93] => [0x%02x]\n", __data);

	__reg = 0x92; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t2) DEL_ADD/I2C_DEL    [0x38]:[0x92] => [0x%02x]\n", __data);

	__reg = 0x8d; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t3) DELTA_SCOPE2       [0x38]:[0x8D] => [0x%02x]\n", __data);

	__reg = 0x9a; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t4) DEL_SCOPE_PLL_M3   [0x38]:[0x9A] => [0x%02x]\n", __data);

	__reg = 0x98; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t5) DELTA_MAX_ADJUST   [0x38]:[0x98] => [0x%02x]\n", __data);

	__reg = 0xB9; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t6) TCS_RE_OFF/TCS_D_M [0x38]:[0xB9] => [0x%02x]\n", __data);

	__reg = 0xB8; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t7) TCS_ERR_SEL        [0x38]:[0xB8] => [0x%02x]\n", __data);

	__reg = 0x76; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t8) DR_N2              [0x38]:[0x76] => [0x%02x]\n", __data);

	/* DFE SCAN*/
	printk("[DFE Setting]\n");
	
	__reg = 0x5C; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t1) DFE_A,B1~B5        [0x38]:[0x5C] => [0x%02x]\n", __data);

	__reg = 0x5D; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t2) DFE_N1             [0x38]:[0x5D] => [0x%02x]\n", __data);

	__reg = 0x5E; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t3) DFE_UPDN_PERIOD    [0x38]:[0x5E] => [0x%02x]\n", __data);

	__reg = 0x58; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t4) I2C_DFE_ON_MODE_ON [0x38]:[0x58] => [0x%02x]\n", __data);

	__reg = 0x52; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t5) I2C_DFE_LEVEL_B1_MO[0x38]:[0x52] => [0x%02x]\n", __data);

	__reg = 0x89; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t6) I2C_DELTA_CDR      [0x38]:[0x89] => [0x%02x]\n", __data);

	/* COMMON*/
	printk("[COMMON Setting]\n");

	__reg = 0x72; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t1) EQ_EVAL_TIME2      [0x38]:[0x72] => [0x%02x]\n", __data);

	__reg = 0xB3; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
  	printk("\t2) TCS_SCDT/MAN_P_OP  [0x38]:[0xB3] => [0x%02x]\n", __data);
   
	__reg = 0xBA; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t3) TCS_BOUNDARY       [0x38]:[0xBA] => [0x%02x]\n", __data);
	
	__reg = 0xB7; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t4) TCS_P_SEL/TCS_SCO  [0x38]:[0xB7] => [0x%02x]\n", __data);
	
	__reg = 0xBD; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t5) TCS_ER_LIMIT_BASIC [0x38]:[0xBD] => [0x%02x]\n", __data);

	if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		__reg = 0x06; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
		printk("\t6) FIFO_MODE          [0x48]:[0x06] => [0x%02x]\n", __data);
	}
	else {
		__reg = 0x6E; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
		printk("\t6) FIFO_MODE          [0x38]:[0x6E] => [0x%02x]\n", __data);
	}

	__reg = 0xA4; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\t7) ERROR_UNIT_SEL     [0x48]:[0xA4] => [0x%02x]\n", __data);

	__reg = 0xB4; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t8) REG_TCS_MAN_PRE    [0x38]:[0xB4] => [0x%02x]\n", __data);
   
	__reg = 0xB5; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t9) REG_TCS_MAN_MEA_1  [0x38]:[0xB5] => [0x%02x]\n", __data);
   
	__reg = 0xB6; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tA) REG_TCS_MAN_MEA_2  [0x38]:[0xB6] => [0x%02x]\n", __data);
   
	__reg = 0xAC; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tB) CED_OPEN_LENGTH    [0x38]:[0xAC] => [0x%02x]\n", __data);
  
	__reg = 0xAD; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tC) CHK_INFINITE_MODE  [0x38]:[0xAD] => [0x%02x]\n", __data);
   
	__reg = 0xAB; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tD) CED_CHECK_MODE     [0x38]:[0xAB] => [0x%02x]\n", __data);
   
	__reg = 0xBC; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tE) CED_ADAPTIVE_PER   [0x38]:[0xBC] => [0x%02x]\n", __data);

	__reg = 0xED; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tF) EQ_FREQ_DIV        [0x38]:[0xED] => [0x%02x]\n", __data);
   
	__reg = 0xEF; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tG) CAL_INTEVAL        [0x38]:[0xEF] => [0x%02x]\n", __data);
  
	__reg = 0x8B; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\tH) DELTA_MODE_PLL0~3  [0x38]:[0x8B] => [0x%02x]\n", __data);

	__reg = 0x8A; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\tI) FRL_MATCH_MAN_VAL  [0x48]:[0x8A] => [0x%02x]\n", __data);

	__reg = 0x60; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
	printk("\tJ) HDMI21_SYM_LOCK_SE [0x48]:[0x60] => [0x%02x]\n", __data);



	/* ODT*/
	printk("[ODT Setting]\n");

	__reg = 0x58; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t1) ODT MAN_ODT50      [0x28]:[0x58] => [0x%02x]\n", __data);
   
	__reg = 0x59; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t2) I2C_ODT_HDMI50     [0x28]:[0x59] => [0x%02x]\n", __data);

	/* RESET, PDB*/
	printk("[RESET/PDB Setting]\n");

	__reg = 0x00; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t1) RESET/PDB RESETB   [0x28]:[0x00] => [0x%02x]\n", __data);
   
	__reg = 0x48; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
	printk("\t2) ODT_PDB            [0x28]:[0x48] => [0x%02x]\n", __data);

	printk("[ETC]\n");

	__reg = 0x8A; __reg = __reg << 2; __data = _p->phyDR_read(__reg);
	printk("\t1) DELTA SCAN MANMODE [0x38]:[0x8A] => [0x%02x]\n", __data);

	return;
}




/* DBG function */
static void __HDMI21_HAL_Rx_DBG_PrintSavedEDID(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int size = HDMI21_HAL_SIZE_OF_EDID;
	int i = 0;

	UINT8 edid_data[HDMI21_HAL_SIZE_OF_EDID] = {0,};

	memcpy((void *)&edid_data, (void *)&_p->edidData, HDMI21_HAL_SIZE_OF_EDID);

	printk("=========================================================================================================================\n");
	printk("[0x00] |  [0x00] [0x01] [0x02] [0x03] [0x04] [0x05] [0x06] [0x07] [0x08] [0x09] [0x0A] [0x0B] [0x0C] [0x0D] [0x0E] [0x0F]\n");
	printk("=========================================================================================================================\n");

	for (i = 0; i < (size/16); i++) {
		if((i%8) == 0){
			printk("-------------------------------------------------------------------------------------------------------------------------\n");
			printk("EDID Block %d, Bytes %d-%d [%02xH-%02xH]\n",  i/8, (128*(i/8)), (128*((i/8)+1) -1), (128*(i/8)), (128*((i/8)+1) -1));
			printk("-------------------------------------------------------------------------------------------------------------------------\n");
		}
		printk("[0x%02x] | [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x]\n",\
				i, edid_data[(i*16) + 0], edid_data[(i*16) + 1], edid_data[(i*16) + 2], edid_data[(i*16) + 3], edid_data[(i*16) + 4],\
				edid_data[(i*16) + 5], edid_data[(i*16) + 6], edid_data[(i*16) + 7], edid_data[(i*16) + 8],\
				edid_data[(i*16) + 9], edid_data[(i*16) + 10],edid_data[(i*16) + 11], edid_data[(i*16) + 12],\
				edid_data[(i*16) + 13], edid_data[(i*16) + 14],edid_data[(i*16) + 15]);
	}
}

static void __HDMI21_HAL_Rx_Set_Audio_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Step 1. Port defence code */
	if(_p->port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", _p->port);
		return;
	}
#if 1	
	gHDMI21RxHandler[_p->port].audio_change = 0;
#else
	if((_p->link_read(HDMI21_RX_CMU_STATUS) & HDMI21_RX_CMU_STATUS__AUDCLK_LOCKED_ST) ||
		(_p->audio_change == 0)){
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x1000)HDMI20_AUDIO("Notice [%d] : Audio PLL Lock Ok\n", _p->port);
		HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_AUDIO);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
		/* SW Workaround for ACR pll mode */
		_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
		HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 1);
		HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 0);
		_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x1 );
		HDMI21_HAL_Rx_Set_Audio_Configure(_p->port, __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p));
		/* Re-initialize Audio FIFO */
		//HDMI21_HAL_Rx_Set_AudioReset(_p->port);
		//HDMI21_HAL_Rx_Set_AudioFIFOReset(_p->port);
		gHDMI21RxHandler[_p->port].audio_change = 0;

		//HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 1);

		/* Added 2014/08/04 taejun.lee */
		HDMI21_HAL_Rx_Get_AudioInfo(_p->port);
	}
	else{
		HDMI20_AUDIO("Notice [%d] : Waiting for AUDIO CLOCK Lock\n", _p->port);
	}
#endif	
}

static void __HDMI21_HAL_Rx_Set_HDCP_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;


	HDMI20_VIDEO("Notice [%d] : MainThread HDCP Change detected\n", _p->port);

	/* Reset Flag */
	_p->hdcp_change = 0;

	/* Audio */
	HDMI21_HAL_Rx_Set_AudioReset(_p->port);
}

static void __HDMI21_HAL_Rx_Set_Video_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	HDMI20_VIDEO("Notice [%d] : MainThread VIDEO Change detected. stable_cnt[%d]\n", _p->port, _p->stable_cnt);

	/* 2020/04/16 : To Restore PixelPacking Phase software workaround */
	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_PIXEL_PACKING_WATCHDOG].value > 0) {
		if(HDMI21_VPROC_Rx_Get_OverRidePixelPackingPhase(_p) > 0) {
			HDMI21_VPROC_Rx_Set_OverRidePixelPackingPhase(_p, 0, 0);
		}
	}

	/* TEMPDBG:JINWOO Choi reverse */
	HDMI21_VPROC_Rx_Set_SyncGenSel(_p,  gHDMI21RxDevLinkControler[HDMI21__LINK_FRLSYNCGEN_DEFAULT_MODE].value);
	
	/* Reset Flag */
	_p->video_change = false;

	/* Reset Stable CNT */
	_p->stable_cnt = 0;

	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__VSI, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__H14VSI, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__DOLBYVSI, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__HFVSI, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__DOVI, _p->port);


	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__AVI, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__DRM, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_VTEM, _p->port);

	//HDMI21_HAL_Rx_Set_AudioReset(_p->port);
}



static void __HDMI21_HAL_Rx_Set_TMDS_Change(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isforceSet)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	HDMI20_VIDEO("Notice [%d] : MainThread TMDS Change detected. Stable cnt[%d]\n", _p->port,_p->stable_cnt);

	/* This should be called with 1st prioity : Clear Timing Info */
	__HDMI21_HAL_Rx_Set_UpdateStableTimingInfo(_p, 1);

	/* Reset Flag for both TMDS/VIDEO */
	_p->video_change = 0; 
	_p->tmds_change = 0;

	/* Reset Stable CNT */
	_p->stable_cnt = 0;

	/* Link Reset when this was firstly detected */
	if((_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) || (isforceSet)){
		HDMI20_VIDEO("Notice [%d] : TMDS Change on stable Video Cnt.\n", _p->port);

		/* Perform Link Reset */
		__HDMI21_HAL_Rx_Set_ResetLink(_p, 0);
	}

	/* Audio Reset */
	HDMI21_HAL_Rx_Set_AudioReset(_p->port);
}

static int __HDMI21_HAL_Rx_DBG_PrintDevVideoController(HDMI21_DEV_VIDEO_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI21RxDevVideoControler[i].index, gHDMI21RxDevVideoControler[i].value, gHDMI21RxDevVideoControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI21RxDevVideoControler[index].index, gHDMI21RxDevVideoControler[index].value, gHDMI21RxDevVideoControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

static int __HDMI21_HAL_Rx_DBG_PrintDevAudioController(HDMI21_DEV_AUDIO_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Aud Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI21RxDevAudioControler[i].index, gHDMI21RxDevAudioControler[i].value, gHDMI21RxDevAudioControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Aud Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI21RxDevAudioControler[index].index, gHDMI21RxDevAudioControler[index].value, gHDMI21RxDevAudioControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);
	
	return ret;
}

static int __HDMI21_HAL_Rx_DBG_PrintDevLinkController(HDMI21_DEV_LINK_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI21RxDevLinkControler[i].index, gHDMI21RxDevLinkControler[i].value, gHDMI21RxDevLinkControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI21RxDevLinkControler[index].index, gHDMI21RxDevLinkControler[index].value, gHDMI21RxDevLinkControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


static int __HDMI21_HAL_Rx_DBG_PrintDevPhyController(HDMI21_DEV_PHY_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI21RxDevPhyControler[i].index, gHDMI21RxDevPhyControler[i].value, gHDMI21RxDevPhyControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI21RxDevPhyControler[index].index, gHDMI21RxDevPhyControler[index].value, gHDMI21RxDevPhyControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

static void __HDMI21_HAL_Rx_Set_ResetLink(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int mode)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;


	HDMI20_INFO("LINK[%d] : [%s]Reset. HDCP2.3[%d]/HDCP1.4[%d] (Caller[%pS])\n", _p->port, mode?"Main":"Soft",\
			_p->gWasHDCP22Written, _p->gWasHDCP14Written, __builtin_return_address(0));

	/* Mute Video */
	HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);

	/* Core Reset */
	if(mode) 	{ __data = gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_MAIN_HARD_RESET_VAL].value; }
	else		{ __data = gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_MAIN_SOFT_RESET_VAL].value; }
	HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, __data);

	/* 2025/03/25 won.hur : Same for O26 on low power modes..*/
	/* Low Power Mode Reset for TOP Layer */
	if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		_p->top_write(0x328, 0x0);
		_p->top_write(0x32C, 0x0);
	}

	/*Core Ref Clock */
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
		HDMI21_MISC_Rx_Set_RefClkValue(_p,  0x1C9C3800);
	}
	else{
		HDMI21_MISC_Rx_Set_RefClkValue(_p,  0x0BEBC200);
	}

	/* Core HPD Config */
	HDMI21_MISC_Rx_Set_CoreHpdConfig(_p, 0);

	/* Core TMDS QP/Audio/FRL BP CLK Margin */
	HDMI21_MISC_Rx_Set_CoreCmuTmdsQpClkMargin(_p, 0);
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		HDMI21_MISC_Rx_Set_CoreCmuAudioClkMargin(_p, 1);
	}else{
		HDMI21_MISC_Rx_Set_CoreCmuAudioClkMargin(_p, 0);
	}

	HDMI21_MISC_Rx_Set_CoreCmuFlrClkMargin(_p, 0);

	/* Core CMU Enable */
	HDMI21_MISC_Rx_Set_CoreCmuEnable(_p, true);

	/* PEXTRACT */
	HDMI21_PEXTRACT_Rx_Set_Initiate(_p);

	/* PFIFO : Use this for only VSI packets due to VSI(ALLM)*/
	HDMI21_PFIFO_Rx_Set_Initialize(_p, true);

	/* VPROC */
	HDMI21_VPROC_Rx_Set_Initialize(_p);
	/* Request FROM CVI andy.lim@lge.com 
	 * --> Always Send Positive H/V Sync */
	HDMI21_VPROC_Rx_Set_HVSyncPolarity(_p, 1, 1, 1);

	/* PDEC */
	HDMI21_PDEC_Rx_Set_Initialize(_p);
	
	/* HDCP */
	if(_p->gWasHDCP14Written >= 1){
		HDMI21_HDCP_Rx_Set_Initialize(_p);
		HDMI21_HDCP_Rx_Set_HDCP14Keys(_p, &_p->hdcp);
	}
	else {
		/* Should Set TMDS bypass */
	}

	/* Initiate Data Packet Buffer */
	HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA_MAXNUM, _p->port);
	HDMI21_DISLAND_Rx_Set_ResetEmPktBuf(HDMI21_EMPACKET_MAXNUM, _p->port);

	/* Init Deframer */
	HDMI21_DEFRAMER_Rx_Set_Initialize(_p);

	/* Init ISR Unit */
	HDMI21_ISRUNIT_Rx_Initiate(_p);

	/* Init SCDC */
	HDMI21_SCDC_Rx_Set_Initiate(_p);
	HDMI21_SCDC_Rx_Set_ScdcConfig(_p, 1);

	/* VMONITOR */
	HDMI21_VMON_Rx_Set_Initiate(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_VMON_SOURCE_TYPE_TMDS].value);

	/* 2019/05/23 : Audio */
	if(_p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT){
		__HDMI21_HAL_Rx_Set_Audio_Change(_p);
	}

	//HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 0);
	
	/* Keep History */
	_p->isLinkInitiated = 1;

	return;
}


static UINT32 __attribute__((unused)) __HDMI21_HAL_Rx_ALED_TOP_Read(UINT32 addr)
{
	UINT32 ret;

	if(sAledTopHdmi21.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)sAledTopHdmi21.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI21_HAL_Rx_ALED_TOP_Write(UINT32 addr, UINT32 data)
{
	volatile UINT32* dest;

	if(sAledTopHdmi21.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)sAledTopHdmi21.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}

static __attribute__((unused)) UINT32 __HDMI21_HAL_Rx_ALED_TOP_Read_P23(UINT32 addr)
{
	UINT32 ret;

	if(lx_chip() != LX_CHIP_M23) {
		return 0;
	}

	if(sAledTopHdmi21P23.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)sAledTopHdmi21P23.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI21_HAL_Rx_ALED_TOP_Write_P23(UINT32 addr, UINT32 data)
{
	volatile UINT32* dest;

	if(lx_chip() != LX_CHIP_M23) {
		return;
	}

	if(sAledTopHdmi21P23.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)sAledTopHdmi21P23.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}


static int	__HDMI21_HAL_Rx_Get_IsPC(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;

	if(_p->dataPacket[HDMI21_DISLAND_DATA__SPD][28] == 0x9){
		if(_p->isPC == false){
			HDMI20_VIDEO(" Notice [%d] : Detected PC\n", _p->port);
		}

		_p->isPC = true;
		ret = 1;
	}
	else{
		if(_p->isPC == true){
			HDMI20_VIDEO(" Notice [%d] : Lost Detection of PC\n", _p->port);
		}

		_p->isPC = false;
		ret = 0;
	}

	return ret;
}


static int	__HDMI21_HAL_Rx_Check_RSScanResult(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;
	int diff = 0;
	UINT32 __reg  = 0;
	UINT32 __data  = 0;
	UINT32 __update  = 0;

	if(_p->isFLT == 1){
		HDMI21_PHY_Rx_Get_UpdatePhyLockFlag(_p->port);

		if(_p->phyRsDone == TRUE){
			HDMI20_PRINT("DBG[%d] RS Scan Complete(cnt:%d)!\n", _p->port, _p->isFLT);
			// RS Scan value compare
			if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_6G_4L){ // 4L
				if(_p->phyRsResult[0] > _p->phyRsResult[1]){
					diff = _p->phyRsResult[0] - _p->phyRsResult[1];
				}else{
					diff = _p->phyRsResult[1] - _p->phyRsResult[0];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[0] > _p->phyRsResult[2]){
					diff = _p->phyRsResult[0] - _p->phyRsResult[2];
				}else{
					diff = _p->phyRsResult[2] - _p->phyRsResult[0];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[0] > _p->phyRsResult[3]){
					diff = _p->phyRsResult[0] - _p->phyRsResult[3];
				}else{
					diff = _p->phyRsResult[3] - _p->phyRsResult[0];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[1] > _p->phyRsResult[2]){
					diff = _p->phyRsResult[1] - _p->phyRsResult[2];
				}else{
					diff = _p->phyRsResult[2] - _p->phyRsResult[1];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[1] > _p->phyRsResult[3]){
					diff = _p->phyRsResult[1] - _p->phyRsResult[3];
				}else{
					diff = _p->phyRsResult[3] - _p->phyRsResult[1];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[2] > _p->phyRsResult[3]){
					diff = _p->phyRsResult[2] - _p->phyRsResult[3];
				}else{
					diff = _p->phyRsResult[3] - _p->phyRsResult[2];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;
				
			}else{ // 3L
				if(_p->phyRsResult[0] > _p->phyRsResult[1]){
					diff = _p->phyRsResult[0] - _p->phyRsResult[1];
				}else{
					diff = _p->phyRsResult[1] - _p->phyRsResult[0];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[0] > _p->phyRsResult[2]){
					diff = _p->phyRsResult[0] - _p->phyRsResult[2];
				}else{
					diff = _p->phyRsResult[2] - _p->phyRsResult[0];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;

				if(_p->phyRsResult[1] > _p->phyRsResult[2]){
					diff = _p->phyRsResult[1] - _p->phyRsResult[2];
				}else{
					diff = _p->phyRsResult[2] - _p->phyRsResult[1];
				}
				if(diff > gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value) ret =RET_ERROR;
			}
			
			if((ret == RET_ERROR) && (gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_COUNT].value >= _p->isFLT)){
				HDMI20_PRINT("DBG[%d] RS Scan Error(%d), diff:%d, ! Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", _p->port, _p->isFLT ,gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value, \
				_p->phyRsResult[0], _p->phyRsResult[1], _p->phyRsResult[2], _p->phyRsResult[3]);

				/* PDC 0x6 bit4 DR_RESETB 1 -> 0 -> 1
				__reg = 0x6; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
				__update = __data & (~0x10);
				__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, __update);

				__reg = 0x6; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
				__update = __data | (0x10);
				__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, __update);
				*/

				// PDC 0x1 bit4  -> 0 
				__reg = 0x1; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
				__update = __data & (~0x10);
				__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, __update);

				// PDC 0x46 bit0  -> 1
				__reg = 0x46; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
				__update = __data | (0x1);
				__reg = 0x46; __reg = __reg << 2; _p->phyPDC_write(__reg, __update);

				// PDC 0x47 bit4  -> 0 -> 1
				__reg = 0x47; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
				__update = __data & (~0x1);
				__reg = 0x47; __reg = __reg << 2; _p->phyPDC_write(__reg, __update);

				__reg = 0x47; __reg = __reg << 2; __data = _p->phyPDC_read(__reg);
				__update = __data | (0x1);
				__reg = 0x47; __reg = __reg << 2; _p->phyPDC_write(__reg, __update);

				_p->isFLT++;
			}else{
				_p->isFLT = 0;
				HDMI20_PRINT("DBG[%d] RS Scan OK(%d) diff:%d,! Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", _p->port, _p->isFLT, gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DIFF].value, \
				_p->phyRsResult[0], _p->phyRsResult[1], _p->phyRsResult[2], _p->phyRsResult[3]);

				__reg = 0x5a; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);	// 0x48
				__update = __data & (0x10);
				__reg = 0x5a; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, __update);	// 0x48				
			}
				
		}else{
			HDMI21_LINE_DBG(595, "DBG[%d] RS Scan Wait!\n", _p->port);
		}
	}

	return ret;
}



static int __HDMI21_HAL_Rx_Set_HDMIHostErrorThres(LX_HDMI20_ERROR_SETTING_T *pData, int size)
{
	int ret = RET_ERROR;
	
	do{
		#if 0
		if(gHDMI21RxDevVideoControler[HDMI21__USE_MW_HOSTERROR_CTRL].value > 0){
			if(pData == NULL) {
				HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
				break;
			}

			if(size > (sizeof(LX_HDMI20_ERROR_SETTING_T) * LX_HDMI20_ERROR_MAXNUM)) {
				HDMI20_ERROR("Error! Size[%d] is over limit[%zu]\n", size, (sizeof(LX_HDMI20_ERROR_SETTING_T) * LX_HDMI20_ERROR_MAXNUM));
				break;
			}

			/* Get Data */
			if( copy_from_user(&kdrvHDMI21ErrorThres, (void __user *)pData, size)){
				HDMI20_ERROR("Cannot copy HDMI20 Error Init thres data structure from user\n");
				break;
			}
		}
		#endif
		/* OK */
		ret = RET_OK;
	} while(0);

	return ret;
}

static int __HDMI21_HAL_Rx_Get_HDMIHostError(UINT8 port, UINT32 *pData, int size)
{
	int ret = RET_ERROR;

	do{
		#if 0
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(UINT32)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(UINT32), size);
			break;
		}

		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		ret = copy_to_user((void __user *)pData, (void *)&gHDMI21hostError[port].errorStatus, sizeof(UINT32));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "HDMI_Error", port);
			break;
		}

		/* Clear Error After sending it to user layer */
		gHDMI21hostError[port].errorStatus = 0;
		#endif
		ret = RET_OK;
	} while(0);

	return ret;

}

static void __HDMI21_HAL_Rx_Set_ClearHDMIHostError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI20_ERROR_TYPE_T type)
{
		
	#if 0
	volatile HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_HOST_DIAGNOSIS_ERROR_T *_pDe;
	int i;

	/* Get Handler */
	_pDe = &gHDMI21hostError[_p->port];

	if(type >= LX_HDMI20_ERROR_MAXNUM){
		memset((void *)_pDe, 0, sizeof(HDMI21_HOST_DIAGNOSIS_ERROR_T));
	}
	else{
		_pDe->errorStatus &= (~kdrvHDMI21ErrorThres[type].errorVal);
		_pDe->counter[type] = 0;
		_pDe->startTick[type] = 0;
		_pDe->isActive[type] = false;

		if(type == LX_HDMI20_ERROR_CED_ERROR){
			for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				_pDe->cedError[i] = 0;
			}
		}
	}
	#endif
}

static void __HDMI21_HAL_Rx_Set_PutHDMIHostError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI20_ERROR_TYPE_T type, int errorStatus)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_HOST_DIAGNOSIS_ERROR_T *_pDe;
	UINT32 currentJiffies = 0;

	/* Get Handler */
	_pDe = &gHDMI21hostError[_p->port];

	if(kdrvHDMI21ErrorThres[type].errorVal == 0){
		/* Do nothing */
		return;
	}

	if((_pDe->errorStatus & kdrvHDMI21ErrorThres[type].errorVal) != 0){
		/* Do nothing if Error flag is already UP*/
		return;
	}

	currentJiffies = jiffies_to_msecs(jiffies);

	switch(type)
	{
		case LX_HDMI20_ERROR_GCP_ERROR:
		{
			#if 0
			if(errorStatus){
				_pDe->counter[type]++;
				
				if(_pDe->isActive[type] == false){
					_pDe->startTick[type] = jiffies_to_msecs(jiffies);
					_pDe->isActive[type] = true;
				}

				/* Check Error Threshold */
				if(kdrvHDMI21ErrorThres[type].param_B <= 1){
					_pDe->errorStatus |= kdrvHDMI21ErrorThres[type].errorVal;
				}
				else{
					if((currentJiffies - _pDe->startTick[type]) >= kdrvHDMI21ErrorThres[type].param_A * 1000){
						__HDMI21_HAL_Rx_Set_ClearHDMIHostError(_p, type);
					}
					else{
						if(_pDe->counter[type] >= kdrvHDMI21ErrorThres[type].param_B){
							_pDe->errorStatus |= kdrvHDMI21ErrorThres[type].errorVal;
						}
					}
				}
			}
			#endif
		}
		break;
		#if 0 /* HDCP2.2 is proceeded on KADP layer */
		case LX_HDMI20_ERROR_HDCP22_REAUTH;
		{

		}
		break;
		#endif
		case LX_HDMI20_ERROR_TMDS_ERROR:
		{
		
		}
		break;
		case LX_HDMI20_ERROR_PHY_LOW_RANGE:
		{
			#if 0
			for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				if(abs(_p->phyTCSMax[i] - _p->phyTCSMin[i]) <= kdrvHDMI21ErrorThres[type].param_A){
					_pDe->errorStatus |= kdrvHDMI21ErrorThres[type].errorVal;
				}
			}
			#endif
		}
		break;
		case LX_HDMI20_ERROR_PHY_ABNORMAL:
		{
			#if 0
			for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				
				if(_p->phyInitiatedMode){
					if(abs(_p->phyTCSResult[i] - gHDMI21RxDevVideoControler[HDMI21__PHY_6G_TCS_ADD_VAL].value ) >= kdrvHDMI21ErrorThres[type].param_A){
						_pDe->errorStatus |= kdrvHDMI21ErrorThres[type].errorVal;
					}
				}
				else{
					if(abs(_p->phyTCSResult[i] - gHDMI21RxDevVideoControler[HDMI21__PHY_3G_TCS_ADD_VAL].value ) >= kdrvHDMI21ErrorThres[type].param_A){
						_pDe->errorStatus |= kdrvHDMI21ErrorThres[type].errorVal;
					}
				}
			}
			#endif
		}
		break;
		case LX_HDMI20_ERROR_CED_ERROR:
		{
			#if 0
			if(_pDe->isActive[type] == false){
					_pDe->startTick[type] = jiffies_to_msecs(jiffies);
					_pDe->isActive[type] = true;

					for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
						_pDe->cedError[i] = __HDMI21_HAL_Rx_Get_CEDError(_p, i);
					}

			}
			else{
				if((currentJiffies - _pDe->startTick[type]) >= kdrvHDMI21ErrorThres[type].param_A * 1000){
					for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
						if(__HDMI21_HAL_Rx_Get_CEDError(_p, i)>= kdrvHDMI21ErrorThres[type].param_B){
							_pDe->errorStatus |= kdrvHDMI21ErrorThres[type].errorVal;
						}
					}

					__HDMI21_HAL_Rx_Set_ClearHDMIHostError(_p, type);
				}
				else{
					for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
						_pDe->cedError[i] += HDMI20_HAL_Rx_Get_CEDError(_p, i);
					}
				}
			}
			#endif
		}
		break;
		case LX_HDMI20_ERROR_AUDIO_BUFFER:
		{
			/* For Taejun.lee */
		}
		break;
		case LX_HDMI20_ERROR_UNSTABLE_SYNC:
		{
			/* Not Defined Yet*/
		}
		break;
		
		default :
		break;
	}

	return;
}

static int __attribute__((unused)) __HDMI21_HAL_Rx_Get_CEDError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 channel)
{
	UINT32 cedError = 0;

	switch(channel)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default :
			break;
	}
	
	
	return cedError;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
#define __hdmi21_ioremap(a,b)	ioremap(a,b)
#else
#define __hdmi21_ioremap(a,b)	ioremap_nocache(a,b)
#endif

static int __HDMI21_HAL_Rx_Set_MapHwMemory(int isClear)
{
	int i;
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do {
		HDMI20_INFO("Map HDMI21 device HW to memory\n");
		
		if(isClear) {
			/* ALED TOP (Always On EDID TOP) */
			iounmap((void *)sAledTopHdmi21.pSwAddr);
			sAledTopHdmi21.pSwAddr = NULL;

		}
		else {
			/* #0. Map PQE HDR Mem */
			#ifdef BUILD_FEATURE_audio_board
			HDMI20_INFO(" 0) Discard PQE HDR TOP MAPPING (Maybe SoundBar project)\n");
			#else
			if(sPqeHdrMem.hwAddr == 0) {
				HDMI20_INFO("Error! ALED TOP HW memory value NULL. Abort memory allocation\n");
				break;
			}

			if(sPqeHdrMem.pSwAddr == NULL) {
				sPqeHdrMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sPqeHdrMem.hwAddr, sPqeHdrMem.size);
			}
			else {
				iounmap((void *)sPqeHdrMem.pSwAddr);
				sPqeHdrMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sPqeHdrMem.hwAddr, sPqeHdrMem.size);
			}

			HDMI20_INFO(" 0) PQE HDR TOP MAPPING : ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sPqeHdrMem.hwAddr, (void *)sPqeHdrMem.pSwAddr, (unsigned int)sPqeHdrMem.size);
			#endif

			/* #1. Map ALED TOP(Always On EDID TOP) */
			if(sAledTopHdmi21.hwAddr == 0) {
				HDMI20_INFO("Error! ALED TOP HW memory value NULL. Abort memory allocation\n");
				break;
			}

			if(sAledTopHdmi21.pSwAddr == NULL) {
				sAledTopHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sAledTopHdmi21.hwAddr, sAledTopHdmi21.size);
			}
			else {
				iounmap((void *)sAledTopHdmi21.pSwAddr);
				sAledTopHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sAledTopHdmi21.hwAddr, sAledTopHdmi21.size);
			}

			if(lx_chip() == LX_CHIP_M23) {
				/* #1-2. (M23 ONLY) Map ALED TOP(Always On EDID TOP) for Port 2/3 */
				if(sAledTopHdmi21P23.hwAddr == 0) {
					HDMI20_INFO("Error! ALED TOP HW(Port 2/3) memory value NULL. Abort memory allocation\n");
					break;
				}

				if(sAledTopHdmi21P23.pSwAddr == NULL) {
					sAledTopHdmi21P23.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sAledTopHdmi21P23.hwAddr, sAledTopHdmi21P23.size);
				}
				else {
					iounmap((void *)sAledTopHdmi21P23.pSwAddr);
					sAledTopHdmi21P23.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sAledTopHdmi21P23.hwAddr, sAledTopHdmi21P23.size);
				}

				HDMI20_INFO(" 1) ALED TOP MAPPING : [Port 0,1] ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sAledTopHdmi21.hwAddr, (void *)sAledTopHdmi21.pSwAddr, (unsigned int)sAledTopHdmi21.size);
				HDMI20_INFO("                     : [Port 2,3] ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sAledTopHdmi21P23.hwAddr, (void *)sAledTopHdmi21P23.pSwAddr, (unsigned int)sAledTopHdmi21P23.size);
			}
			else {
				HDMI20_INFO(" 1) ALED TOP MAPPING : ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sAledTopHdmi21.hwAddr, (void *)sAledTopHdmi21.pSwAddr, (unsigned int)sAledTopHdmi21.size);
			}

			/* #2. For each Port, LinkMem/TopMem/Aled/PhyPDCMem/PhyPostDRMem */
			for(i=0; i<g_hdmi20_number_of_ports; i++)
			{
				_p = &gHDMI21RxHandler[i];

				/* Memory Map : Link HW */
				if(_p->linkMem.hwAddr == 0) {
					HDMI20_INFO("Error! Link HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(_p->linkMem.pSwAddr == NULL) {
					_p->linkMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->linkMem.hwAddr, _p->linkMem.size);
				}
				else {
					iounmap((void *)_p->linkMem.pSwAddr);
					_p->linkMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->linkMem.hwAddr, _p->linkMem.size);
				}

				/* Memory Map : HDMI TOP HW */
				if(_p->topMem.hwAddr == 0) {
					HDMI20_INFO("Error! TOP HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(_p->topMem.pSwAddr == NULL) {
					_p->topMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->topMem.hwAddr, _p->topMem.size);
				}
				else {
					iounmap((void *)_p->topMem.pSwAddr);
					_p->topMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->topMem.hwAddr, _p->topMem.size);
				}

				/* Memory Map : ALED HW */
				if(_p->aledMem.hwAddr == 0) {
					HDMI20_INFO("Error! ALED HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(_p->aledMem.pSwAddr == NULL) {
					_p->aledMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->aledMem.hwAddr, _p->aledMem.size);
				}
				else {
					iounmap((void *)_p->aledMem.pSwAddr);
					_p->aledMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->aledMem.hwAddr, _p->aledMem.size);
				}

				/* Memory Map : PHY PDC */
				if(_p->phyPdcMem.hwAddr == 0) {
					HDMI20_INFO("Error! ALED HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(_p->phyPdcMem.pSwAddr == NULL) {
					_p->phyPdcMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->phyPdcMem.hwAddr, _p->phyPdcMem.size);
				}
				else {
					iounmap((void *)_p->phyPdcMem.pSwAddr);
					_p->phyPdcMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->phyPdcMem.hwAddr, _p->phyPdcMem.size);
				}

				/* Memory Map : Post Dr HW */
				if(_p->phyPostDrMem.hwAddr == 0) {
					HDMI20_INFO("Error! ALED HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(_p->phyPostDrMem.pSwAddr == NULL) {
					_p->phyPostDrMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->phyPostDrMem.hwAddr, _p->phyPostDrMem.size);
				}
				else {
					iounmap((void *)_p->phyPostDrMem.pSwAddr);
					_p->phyPostDrMem.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(_p->phyPostDrMem.hwAddr, _p->phyPostDrMem.size);
				}

				HDMI20_INFO(" %d Port[%d] Memory MAPPING\n", (i+1), i);
				HDMI20_INFO("   ORIGIN RX[%d] : CTRL[0x%08x] / TOP[0x%08x] / ALED[0x%08x] PDC[0x%08x] / PostDr[0x%08x]  \n", i, (unsigned int)_p->linkMem.hwAddr,  (unsigned int)_p->topMem.hwAddr,  (unsigned int)_p->aledMem.hwAddr, (unsigned int)_p->phyPdcMem.hwAddr, (unsigned int)_p->phyPostDrMem.hwAddr);
				HDMI20_INFO("   MAPPED RX[%d] : CTRL[0x%p] / TOP[0x%p] / ALED[0x%p] / PDC[0x%p] / PostDr[0x%p] \n", i, (void *)_p->linkMem.pSwAddr,  (void *)_p->topMem.pSwAddr,  (void *)_p->aledMem.pSwAddr, (void *)_p->phyPdcMem.pSwAddr, (void *)_p->phyPostDrMem.pSwAddr);

				/* Check for Error */
				if(i == (g_hdmi20_number_of_ports - 1)) ret = RET_OK; 
			}

			if(lx_chip() != LX_CHIP_M23) {	
				/* #3. DSC Top Mem */
				if(sDscTopHdmi21.hwAddr == 0) {
					HDMI20_INFO("Error! DSC TOP HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(sDscTopHdmi21.pSwAddr == NULL) {
					sDscTopHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sDscTopHdmi21.hwAddr, sDscTopHdmi21.size);
				}
				else {
					iounmap((void *)sDscTopHdmi21.pSwAddr);
					sDscTopHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sDscTopHdmi21.hwAddr, sDscTopHdmi21.size);
				}

				HDMI20_INFO("   DSC TOP MAPPING : ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sDscTopHdmi21.hwAddr, (void *)sDscTopHdmi21.pSwAddr, (unsigned int)sDscTopHdmi21.size);

				/* #4. DSC Top Mem */
				if(sDscCoreHdmi21.hwAddr == 0) {
					HDMI20_INFO("Error! DSC TOP HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(sDscCoreHdmi21.pSwAddr == NULL) {
					sDscCoreHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sDscCoreHdmi21.hwAddr, sDscCoreHdmi21.size);
				}
				else {
					iounmap((void *)sDscCoreHdmi21.pSwAddr);
					sDscCoreHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sDscCoreHdmi21.hwAddr, sDscCoreHdmi21.size);
				}

				HDMI20_INFO("   DSC Core MAPPING : ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sDscCoreHdmi21.hwAddr, (void *)sDscCoreHdmi21.pSwAddr, (unsigned int)sDscCoreHdmi21.size);

				/* #5. Fec Top Mem */
				if(sFecTopHdmi21.hwAddr == 0) {
					HDMI20_INFO("Error! ALED TOP HW memory value NULL. Abort memory allocation\n");
					break;
				}

				if(sFecTopHdmi21.pSwAddr == NULL) {
					sFecTopHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sFecTopHdmi21.hwAddr, sFecTopHdmi21.size);
				}
				else {
					iounmap((void *)sFecTopHdmi21.pSwAddr);
					sFecTopHdmi21.pSwAddr = (volatile UINT32 *)__hdmi21_ioremap(sFecTopHdmi21.hwAddr, sFecTopHdmi21.size);
				}

				HDMI20_INFO("   FEC TOP MAPPING : ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sFecTopHdmi21.hwAddr, (void *)sFecTopHdmi21.pSwAddr, (unsigned int)sFecTopHdmi21.size);
			}
		}

	} while(0);

	return ret;
}

static void __HDMI21_HAL_Rx_WatchDog_FilterSelStuck(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __totalCedErrorCnt = 0;
	int __am_i_stuck = 0;
	UINT32 __data = 0;
	UINT32 __reg  = 0;

	do {
		if(_p->isPhyLocked != 0) break; 
		
		if(_p->phy_tmds_clk <= 0) break;
		if(_p->phy_tmds_clk <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_STUCK_CLOCK_CONDITION].value){
			break;
		}
		
		if(_p->phyCrDone <= 0) break;
		
		if(_p->phyTCSState == 0) break;

		/* Check CED Counts */
		__totalCedErrorCnt = _p->phyCEDError[0] + _p->phyCEDError[1] + _p->phyCEDError[2] + _p->phyCEDError[3];
		if(__totalCedErrorCnt == 0) break; 
		
		if(_p->filterSelStuck == 0) {
			_p->phyStuckVal = _p->phyTCSState;

			/* Flag */
			__am_i_stuck = 1;
			break;
		}		
		

		if(_p->phyStuckVal != _p->phyTCSState) {
			break;
		}

		/* If you came this far.. your surely stuck! */
		__am_i_stuck = 1;

	} while(0);

	if(__am_i_stuck == 0) {
		/* If your not stuck... clear counter and previous history */
		_p->filterSelStuck = 0;
		_p->consecutiveFilStuckCnt = 0;
		_p->phyStuckVal = 0;
	}
	else {
		_p->filterSelStuck++;

		HDMI20_PRINT("WATCHDOG[%d] : Warning! Signs of Filter Sel Stuck Case. TCS_State[0x%x]/StuckCnt[%d]",\
		 _p->port, _p->phyStuckVal, _p->filterSelStuck);
	}

	if(_p->filterSelStuck >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_STUCK_SWWA_THRES].value) {
		/* ANA CDR DR Resetb for O22/M23 */
		__reg = 0x01; __reg = (__reg << 2) + 0x400; __data = _p->phyDR_read(__reg);
		__data &= (~0x80); 
		_p->phyDR_write(__reg, __data);

		HDMI20_PRINT("WATCHDOG[%d] : DR_ANA_RESETB Toggle!\n", _p->port);

		__data |= (0x80);
		_p->phyDR_write(__reg, __data);

		/* Filter Sel : 0x38:0xF3 BIT[4] for O20/E60/O22/M23 */
		__reg = 0xF3; __reg = (__reg << 2); __data = _p->phyDR_read(__reg);

		/* Set to zero */
		__data &= (~0x10);
		_p->phyDR_write(__reg, __data);

		HDMI20_PRINT("WATCHDOG[%d] : Filter Sel Stuck Detection. Toggle FilterSel. TCS_State[0x%x]/StuckCnt[%d]",\
		 _p->port, _p->phyStuckVal, _p->filterSelStuck);

		/* Accumulate SW WA counts */
		_p->filterSelSwWaCnt++;

		/* Set to 1 */
		__data |= (0x10);
		_p->phyDR_write(__reg, __data);

		/* TCS Toggle */
		__reg  = 0x03; __reg = (__reg << 2); __data = _p->phyDR_read(__reg);
		//__data &= (~0x3); __data |= (0x2);
		__data = 0x34;
		_p->phyDR_write(__reg, __data);

		//__data |= (0x1);
		__data = 0x36;
		_p->phyDR_write(__reg, __data);


		/* Clear History */
		_p->filterSelStuck = 0;
		_p->phyStuckVal = 0;

		/* Accumulate consecutive counter */
		_p->consecutiveFilStuckCnt++;
	}

	if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_CONSECUTIVE_STUCK].value != 0) \
			&& ( _p->consecutiveFilStuckCnt >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_FILTER_CONSECUTIVE_STUCK].value)) {
		
		HDMI20_PRINT("WATCHDOG[%d] : Detected consecutive [%d] FilterSel Toggle SWWA. Restart HPD\n", _p->port, _p->consecutiveFilStuckCnt);
		
		HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
		_p->consecutiveFilStuckCnt = 0;
	}

	return;
}

static void __HDMI21_HAL_Rx_WatchDog_PhyPdb(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int is5vHigh)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	if(is5vHigh){
		if(HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn(_p->port) < 0) {

			HDMI20_VIDEO("Notice[%d] : Phy PDB was Low but 5V High. Set PHY PDB to HIGH\n", _p->port);
			
			HDMI21_PHY_Rx_Set_ControlPhyPdb(_p->port, 1);
		}
		else{
			/* Safe Condition */
		}
	}
	else{
		if(gHDMI21RxDevVideoControler[HDMI21__PDB_LOW_ON_DISCONNECT].value > 0){
			if(HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn(_p->port) >= 0) {
				HDMI20_VIDEO("Notice %d : Phy PDB is High, But 5V Low. Set PHY PDB to Low\n", _p->port);
				HDMI21_PHY_Rx_Set_ControlPhyPdb(_p->port, 0);
			}
			else{
				/* Safe Condition */
			}
		}
	}

}

static void __HDMI21_HAL_Rx_Get_CheckLocalVideoMuteColor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __video_format;

	/* Local Mute Color Detection : Check Packet Decoder First, incase of RGB, must check Packet FIFO as well.
	 * 								HW Packet decoder may not be trusted.*/
	if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(_p)){
		/* SW Defence code for DVI CSC */
		__video_format = 0;
	}
	else{
		__video_format = _p->hwVideo.video_format;
	}

	/* Need to override RGB mode on YCbCr */
	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 1244) {

		HDMI21_LINE_DBG(5485, "DBG[%d] : Dolby[%d] Vformat[%d]\n", _p->port, _p->isDolbyHDR,  __video_format);

		if(((_p->isDolbyHDR > 0)&& (_p->isDolbyHDR < HDMI_DOLBY_LL_PC)) || ((_p->isDolbyHDR == HDMI_DOLBY_LL_PC) && (__video_format == 1)) || (__video_format == 2) || (_p->isDSC > 0))  {
			HDMI21_VPROC_Rx_Set_RGB444OverRide(_p, 1);
		}
		else {
			HDMI21_VPROC_Rx_Set_RGB444OverRide(_p, 0);
		}
	}

	/* VIDEO PROCESSOR MUTE color set */
	if(__video_format == 0){
		__HDMI21_HAL_Rx_Set_LocalVideoMuteColor(_p, 0);
	}
	else{
		__HDMI21_HAL_Rx_Set_LocalVideoMuteColor(_p, 1);
	}

	HDMI21_LINE_DBG(1211, "DBG[%d] : DVI[%d], Video Format Value[0x%x]\n", _p->port, __HDMI21_HAL_Rx_Get_IsHwInDVIState(_p), __video_format);

	return;
}

static void __HDMI21_HAL_Rx_Get_UpdateClockVfreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __divider = 0;
	UINT32 __hvtotal, vfreq_tmp;
	UINT32 __is420 = 0;
	UINT64 pixel_clk;

	if(isSet){
		/* This Function Reads PHY TMDS Clock / Deep Color Mode,
		 *               Updates Handler's real_tmds_clk, real_pixel_clk, real_vfreq */
		/* Read From PHY clock */

		if(_p->phy_tmds_clk != 0){

			/* Incase SCDC BitRatio is HIGH, need to multiple by 4 */
			if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) ==  HDMI21_HAL_PHY_INITIATED_6G)
				_p->real_tmds_clk = _p->phy_tmds_clk * 40;
			else
				_p->real_tmds_clk = _p->phy_tmds_clk * 10;

			/* Divide Factor Due to Deep Color */
			if(_p->hwVideo.deep_color_mode== 0x5) { __divider = 125;	}
			else if(_p->hwVideo.deep_color_mode== 0x6) { __divider = 150;}
			else if(_p->hwVideo.deep_color_mode== 0x7) { __divider = 200;}
			else { __divider =  100; }


			/* Check if it is 4:2:0 format */
			if(_p->hwVideo.video_format == 0x3) __is420 = 1;

			/* Calculate Pixel Clock with divider */
			_p->real_pixel_clk = (_p->real_tmds_clk * 100 + (__divider>>1)) / __divider;	//rounding


			HDMI21_LINE_DBG(5539, "DBG[%d] : V[%d] H[%d] Interlaced[%d] TMDS[%llu]. Is420[%d]\n",\
					_p->port, _p->hwVideo.vtotal, _p->hwVideo.htotal, _p->hwVideo.interlaced, _p->real_tmds_clk, __is420);

			if(_p->hwVideo.interlaced > 0)	{ __hvtotal = ((_p->hwVideo.vtotal >> 1) * (_p->hwVideo.htotal >> __is420));}
			else 							{ __hvtotal = ( _p->hwVideo.vtotal       * (_p->hwVideo.htotal >> __is420));}

			/* FRL Modes */
			if(__HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(_p) >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
				/* HW Limitation : Only available from VIC codes */
				/* 2020/08/12 : JangSilverLight asked for this */
				if ( HDMI21_HAL_Rx_Get_VICtoVfreq(_p->hwVideo.vicCode) != 0) {		
					_p->real_vfreq = HDMI21_HAL_Rx_Get_VICtoVfreq(_p->hwVideo.vicCode) / 10;
				}
				else {
					if((_p->isFreeSyncMode == 2) && (_p->em_vrr_baseRate != 0)) {
						_p->real_vfreq = _p->em_vrr_baseRate;
					}
					else if((_p->isFreeSyncMode == 1) && (_p->vfreq_max != 0)) {
						_p->real_vfreq = _p->vfreq_max;
					}
					else if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value >= 1) {
						_p->real_vfreq = __HDMI21_HAL_Rx_Get_LinkTopVfreqCounter(_p, 0);
					}
					else if( (vfreq_tmp = HDMI21_HAL_Rx_Get_VfreqFromHdmiRegForFRL(_p->port)) > 0) {
						_p->real_vfreq = vfreq_tmp;
					}
					else {
						/* FRL mode : vfreq calculation using FRL pixel clock */						
						if(_p->hwVideo.hactive >= 2400) {
							_p->real_vfreq = 120;
						}else {
							_p->real_vfreq = 60;
						}
					

						/* For HFR adjustments.. */
						if((_p->real_vfreq >= 150) && (_p->real_vfreq <= 180)){
							_p->real_vfreq = 165;	
						}else if((_p->real_vfreq >= 130) && (_p->real_vfreq <= 150)){
							_p->real_vfreq = 144;	
						}else if((_p->real_vfreq >= 110) && (_p->real_vfreq < 130)) {
							_p->real_vfreq = 120;
						}	
					}
					HDMI21_LINE_DBG(8461, "Notice [%d] :  _p->real_vfreq = %d(read_clk=%d, vt=%d, ht=%d, hvt=%d, div=%d)\n",_p->port, _p->real_vfreq, (_p->link_read(0x98)), _p->hwVideo.vtotal, _p->hwVideo.htotal, __hvtotal, __divider); 
				}
			}
			else{ /* TMDS Modes */
				if((_p->isFreeSyncMode > 0) && (HDMI21_HAL_Rx_Get_VICtoVfreq(_p->hwVideo.vicCode) != 0)) {
					/* 2021/10/01 : Issue with Q980B HF 2-61 ITER-03. Defence Code.
					 * 				Q980B does not send VTEM at early stage, thus some times our driver locks the changing Vfreq without knowing its VRR*/
					_p->real_vfreq = HDMI21_HAL_Rx_Get_VICtoVfreq(_p->hwVideo.vicCode) / 10;
				}
				else if((_p->isFreeSyncMode > 0) && (_p->em_vrr_baseRate != 0)) { 
					/* 2025/06/24 won.hur : Q980B HF2-61 Iter-39 2560x1440 issue */
					_p->real_vfreq = _p->em_vrr_baseRate;	
				}
				else {
					if(__hvtotal != 0) { 
						if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value >= 1) {
							_p->real_vfreq = __HDMI21_HAL_Rx_Get_LinkTopVfreqCounter(_p, 0);
						}
						else {
							_p->real_vfreq = ((_p->real_tmds_clk * 1000 + (__hvtotal>>1) ) / __hvtotal); //rounding
						}	
					}
					else { 
						_p->real_vfreq = 0; 
					}

					HDMI21_LINE_DBG(8461, "[%d] : hwVideo.vfreq = (%d) => real_vfreq = (%d), (real_tmds_clk=%llu, read_clk=%u, vt=%d, ht=%d, hvt=%d, div=%d).\n",_p->port,_p->hwVideo.vfreq,  _p->real_vfreq, _p->real_tmds_clk, (_p->link_read(0x98)), _p->hwVideo.vtotal, _p->hwVideo.htotal, __hvtotal, __divider); 
				}
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_DBG_VFREQ_OVERRIDE].value > 0) {
				_p->real_vfreq = gHDMI21RxDevVideoControler[HDMI21__VIDEO_DBG_VFREQ_OVERRIDE].value;
			}
		}
		else{
			_p->real_tmds_clk = 0;
			_p->real_pixel_clk = 0;
			_p->real_vfreq = 0;
		}

		if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value == 0) {
			_p->cvi_vfreq = HDMI21_HAL_Rx_Get_FrameRateFromCVI_2nd(_p->port);
		}
	}
	else{
		_p->real_tmds_clk = 0;
		_p->real_pixel_clk = 0;
		_p->real_vfreq = 0;
		_p->cvi_vfreq = 0;
	}

	/* Update Handler Video data */
	_p->hwVideo.tmds_clk 	= _p->real_tmds_clk;
	_p->hwVideo.pixel_clk	= _p->real_pixel_clk;
	_p->hwVideo.vfreq 		= _p->real_vfreq;

}

static void __HDMI21_HAL_Rx_WatchDog_AVMuteHoldTime(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler ;
	UINT32 currentJiffiesMsec = 0;

	if(_p->isMute != 0){
		currentJiffiesMsec = jiffies_to_msecs(jiffies);
		if(currentJiffiesMsec - _p->avmute_on_time >= gHDMI21RxDevVideoControler[HDMI21__AVMUTE_HOLD_TIME].value){
			HDMI20_VIDEO("NOTICE [%d] : AV Mute released by hold time! [0x%x]-[0x%x] >= [0x%x]\n",_p->port,currentJiffiesMsec, _p->avmute_on_time, gHDMI21RxDevVideoControler[HDMI21__AVMUTE_HOLD_TIME].value);

			_p->isMute = 0;
			HDMI21_HAL_Rx_Set_AudioReset(_p->port);
		}
		else{
			HDMI20_VIDEO("NOTICE [%d] : AVMute Hold [0x%x]-[0x%x] < [0x%x]\n"\
					,_p->port,currentJiffiesMsec, _p->avmute_on_time, gHDMI21RxDevVideoControler[HDMI21__AVMUTE_HOLD_TIME].value);
			
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value !=  741) {
				_p->stable_cnt = 0;
			}
		}
	}
}

static void __HDMI21_HAL_Rx_Set_IsrProfiler(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, unsigned int *counter)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int i;


	if(*counter == 0){
		for(i=0;i<HDMI21_ISR_MAXNUM;i++){
			
			_p->isr_count1[i] = _p->isr_count0[i];
		}
		*counter = *counter + 1;
	}
	else if( *counter >= gHDMI21RxDevVideoControler[HDMI21__ENABLE_ISR_PROFILER].value){
		/* Calculate Data */
		for(i=0;i<HDMI21_ISR_MAXNUM;i++){
			_p->isr_count1[i] = _p->isr_count0[i] - _p->isr_count1[i];
		}

		/* Print */	
		if(gHDMI21RxDevVideoControler[HDMI21__ISR_PROFILER_TYPE].value >= HDMI21_ISR_MAXNUM){
			for(i=0;i<HDMI21_ISR_MAXNUM;i++){
				if(_p->isr_count1[i] != 0){
					HDMI20_DBG("DBG[%d] : ISR TYPE[%02d] [%s] = [%d]\n", _p->port, i, __isr_type_to_str(i), _p->isr_count1[i]);  
				}
			}
		}
		else{
			HDMI20_DBG("DBG[%d] : ISR TYPE[%02d] [%s] = [%d]\n", _p->port, i, \
					__isr_type_to_str(gHDMI21RxDevVideoControler[HDMI21__ISR_PROFILER_TYPE].value),\
					_p->isr_count1[gHDMI21RxDevVideoControler[HDMI21__ISR_PROFILER_TYPE].value]);
		}
		*counter = 0;
	}
	else{
		*counter = *counter + 1;
	}

}

static int 	__HDMI21_HAL_Rx_Get_IsVideoStable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;

	do{
		/* Condition 1. 5V? */
		if(_p->is5Vconnected == 0) {
			ret = -1;
			break;
		}

		/* Condition 2. HPD? */
		if(HDMI21_HAL_Rx_Get_IsHpdUp(_p->port) == 0){
			ret = -2;
			break;
		}

		/* Condition 3. Stable CNT? */
		if(_p->stable_cnt <= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value){
			ret = -3;
			break;
		}

		/* Condition 4. Changed status? */
		if((_p->scdc_change != 0) || (_p->video_change != 0) || (_p->tmds_change != 0) ){
			ret = -4;
			break;	
		}

		/* Condition 5. PHY OK?? */
		if((_p->phy_tmds_clk == 0)||(_p->fsm_phy_lock == 0)||(_p->isPhyLocked == 0)){
			ret = -5;
			break;
		}

		/* Condition 6. During Main Thread Init request ?? */
		if(_p->main_thread_init_request){
			ret = -6;
			break;
		}

		/* Condition 7. Is V/A active zero ?? */
		if(_p->isDSC == 0) {
			if((_p->video.vactive == 0) ||(_p->video.hactive == 0))
			{
				ret = -7;
				break;
			}
		}

		/* Condition 8. Is isMute Flag is up?? */
		if(_p->isMute != 0)
		{
			ret = -8;
			break;
		}

		/* If you got this far.. must be stable condition */
		ret = 1;
	} while(0);

	return ret;
}


static void  __HDMI21_HAL_Rx_Set_CompensateStableHVactiveTotal(LX_HDMI_TIMING_INFO_T *_pData)
{
	LX_HDMI_TIMING_INFO_T *_pT = _pData;

	HDMI21_LINE_DBG(1017, "[%d] %s : Got [%d](%d)x[%d](%d)\n", __L__, __F__, _pT->hActive, _pT->hTotal, _pT->vActive, _pT->vTotal);

	/* 2019/08/29 : For 5K/8K/10K Vtotal : Over V:2460*/
	if(_pT->vTotal > 2460){	
		if(u32CHK_RANGE(_pT->vTotal, 2475, 2)) _pT->vTotal = 2475;
		else if(u32CHK_RANGE(_pT->vTotal, 4400, 2)) _pT->vTotal = 4400;
		else if(u32CHK_RANGE(_pT->vTotal, 4500, 2)) _pT->vTotal = 4500;
		else if(u32CHK_RANGE(_pT->vTotal, 4950, 2)) _pT->vTotal = 4950;
	}

	/* Compenstate V Total Value : Under V:2400 */
	if(_pT->vTotal <= 2400) {
		if(_pT->vTotal > 820){
			if(_pT->vTotal > 1120){			
				if(u32CHK_RANGE(_pT->vTotal, 2250, 2)) _pT->vTotal = 2250;
				else if(u32CHK_RANGE(_pT->vTotal, 2200, 2)) _pT->vTotal = 2200;		
				else if(u32CHK_RANGE(_pT->vTotal, 1500, 2)) _pT->vTotal = 1500;				
				else if(u32CHK_RANGE(_pT->vTotal, 1235, 2)) _pT->vTotal = 1235;//1235,1240
				else if(u32CHK_RANGE(_pT->vTotal, 1125, 2)) _pT->vTotal = 1125;				
			}
			else{ 
				if(u32CHK_RANGE(_pT->vTotal, 1100, 2)) _pT->vTotal = 1100;//1099,1100				
				else if(u32CHK_RANGE(_pT->vTotal, 1090, 2)) _pT->vTotal = 1090;//1089,1090				
				else if(u32CHK_RANGE(_pT->vTotal, 1000, 2)) _pT->vTotal = 1000;//996,1000			
				else if(u32CHK_RANGE(_pT->vTotal, 925, 2)) _pT->vTotal = 925;//926			
				else if(u32CHK_RANGE(_pT->vTotal, 825, 2)) _pT->vTotal = 825;//823
			}
		}
		else{
			if(_pT->vTotal > 660){
				if(u32CHK_RANGE(_pT->vTotal, 805, 2)) _pT->vTotal = 805;//806,804,805
				else if(u32CHK_RANGE(_pT->vTotal, 800, 2)) _pT->vTotal = 800;//798,802				
				else if(u32CHK_RANGE(_pT->vTotal, 790, 2)) _pT->vTotal = 790;//791,790,795				
				else if(u32CHK_RANGE(_pT->vTotal, 750, 2)) _pT->vTotal = 750;//755,748			
				else if(u32CHK_RANGE(_pT->vTotal, 666, 2)) _pT->vTotal = 666;//666,667
			}
			else{
				if(u32CHK_RANGE(_pT->vTotal, 625, 2)) _pT->vTotal = 625;//625
				else if(u32CHK_RANGE(_pT->vTotal, 530, 2)) _pT->vTotal = 530;//529
				else if(u32CHK_RANGE(_pT->vTotal, 525, 2)) _pT->vTotal = 525;//526,524,525
				else if(u32CHK_RANGE(_pT->vTotal, 505, 2)) _pT->vTotal = 505;//504
				else if(u32CHK_RANGE(_pT->vTotal, 495, 2)) _pT->vTotal = 495;//494			
			}
		}
	}

	/* 2019/08/29 : For 5K/8K/10K hActive : Over H:4100*/
	if(_pT->hActive > 4100){	
		if(u32CHK_RANGE(_pT->hActive, 5120, 2)) 		_pT->hActive = 5120;
		else if(u32CHK_RANGE(_pT->hActive, 7680, 2))	_pT->hActive = 7680;
		else if(u32CHK_RANGE(_pT->hActive, 10240, 2))	_pT->hActive = 10240;
	}

	/* Compenstate H Active Value : Under 4110*/
	if(_pT->hActive < 4110){
		if(_pT->hActive > 1360){
			if(_pT->hActive > 1900){
				if(u32CHK_RANGE(_pT->hActive, 4096, 5)) _pT->hActive= 4096;
				else if(u32CHK_RANGE(_pT->hActive, 3840, 5)) _pT->hActive= 3840;		
				else if(u32CHK_RANGE(_pT->hActive, 2560, 5)) _pT->hActive= 2560;
				else if(u32CHK_RANGE(_pT->hActive, 1920, 5)) _pT->hActive= 1920;
			}
			else{							
				if(u32CHK_RANGE(_pT->hActive, 1440, 2)) _pT->hActive= 1440;			
				else if(u32CHK_RANGE(_pT->hActive, 1366, 2)) _pT->hActive= 1366;
			}
		}
		else{
			if(_pT->hActive > 1020){
				if(u32CHK_RANGE(_pT->hActive, 1280, 2)) _pT->hActive= 1280;
				else if(u32CHK_RANGE(_pT->hActive, 1024, 2)) _pT->hActive= 1024;
			}
			else{					
				if(u32CHK_RANGE(_pT->hActive, 720, 2)) _pT->hActive= 720;
				else if(u32CHK_RANGE(_pT->hActive, 640, 2)) _pT->hActive= 640;
			}
		}	
	}

	/* 2019/08/29 : For 5K/8K/10K V Active : Over V:2180*/
	if(_pT->vActive > 2180){	
		if(_pT->vActive == 4320) _pT->vActive = 4320;
	}

	/* Compensate V Active : Under 2170 */
	if(_pT->vActive < 2170){	
		if(_pT->vActive > 700){	
			if(_pT->vActive > 1000){
				if(_pT->vActive == 1201) _pT->vActive = 1201;
				else if(u32CHK_RANGE(_pT->vActive, 2160, 5)) _pT->vActive = 2160;				
				else if(u32CHK_RANGE(_pT->vActive, 1600, 5)) _pT->vActive = 1600; 
				else if(u32CHK_RANGE(_pT->vActive, 1440, 5)) _pT->vActive = 1440; 
				else if(u32CHK_RANGE(_pT->vActive, 1200, 2)) _pT->vActive = 1200; 
				else if(u32CHK_RANGE(_pT->vActive, 1080, 2)) _pT->vActive = 1080;			
				else if(u32CHK_RANGE(_pT->vActive, 1050, 2)) _pT->vActive = 1050; 
				else if(u32CHK_RANGE(_pT->vActive, 1035, 2)) _pT->vActive = 1035;
				else if(u32CHK_RANGE(_pT->vActive, 1024, 2)) _pT->vActive = 1024; 

			}
			else{		
				if(u32CHK_RANGE(_pT->vActive, 960, 2)) _pT->vActive = 960;
				else if(u32CHK_RANGE(_pT->vActive, 900, 2)) _pT->vActive = 900;				
				else if(u32CHK_RANGE(_pT->vActive, 870, 2)) _pT->vActive = 870;
				else if(u32CHK_RANGE(_pT->vActive, 864, 2)) _pT->vActive = 864;
				else if(u32CHK_RANGE(_pT->vActive, 800, 2)) _pT->vActive = 800;				
				else if(u32CHK_RANGE(_pT->vActive, 768, 2)) _pT->vActive= 768;
				else if(u32CHK_RANGE(_pT->vActive, 720, 2)) _pT->vActive = 720;	
			}
		}
		else{
			if(_pT->vActive > 490){					
				if(u32CHK_RANGE(_pT->vActive, 624, 2)) _pT->vActive = 624;
				else if(u32CHK_RANGE(_pT->vActive, 600, 2)) _pT->vActive = 600;
				else if(u32CHK_RANGE(_pT->vActive, 584, 2)) _pT->vActive = 584;
				else if(u32CHK_RANGE(_pT->vActive, 576, 2)) _pT->vActive = 576;
				else if(u32CHK_RANGE(_pT->vActive, 496, 2)) _pT->vActive = 496;
			}
			else{
				if(u32CHK_RANGE(_pT->vActive, 480, 2)) _pT->vActive = 480;
				else if(u32CHK_RANGE(_pT->vActive, 483, 2)) _pT->vActive = 483;					
				else if(u32CHK_RANGE(_pT->vActive, 400, 2)) _pT->vActive = 400;
				else if(u32CHK_RANGE(_pT->vActive, 350, 2)) _pT->vActive = 350;
				else if(u32CHK_RANGE(_pT->vActive, 288, 2)) _pT->vActive = 288;
				else if(u32CHK_RANGE(_pT->vActive, 240, 2)) _pT->vActive = 240;
			}
		}
	}

	/* Timing Value Check : Always place this part on the last part before copying timing info to MW */
	if (_pT->hActive %4 != 0)	//150209 : OTT STB 1080P 50Hz Flickering (1920x1078)
	{
		HDMI21_LINE_DBG(1017, "%s : hActive modification [%d]\n", __F__, _pT->hActive);
		if ( u32CHK_RANGE(_pT->hActive, 10240, 2) )		_pT->hActive = 10240;
		else if ( u32CHK_RANGE(_pT->hActive, 7680, 2) )	_pT->hActive = 7680;
		else if ( u32CHK_RANGE(_pT->hActive, 4096, 2) )	_pT->hActive = 4096;
		else if ( u32CHK_RANGE(_pT->hActive, 3840, 2) )	_pT->hActive = 3840;
		else if ( u32CHK_RANGE(_pT->hActive, 2880, 2) )	_pT->hActive = 2880;
		else if ( u32CHK_RANGE(_pT->hActive, 2560, 2) )	_pT->hActive = 2560;
		else if ( u32CHK_RANGE(_pT->hActive, 1920, 2) )	_pT->hActive = 1920;
		else if ( u32CHK_RANGE(_pT->hActive, 1440, 2) )	_pT->hActive = 1440;
		else if ( u32CHK_RANGE(_pT->hActive, 1280, 2) )	_pT->hActive = 1280;
		else if ( u32CHK_RANGE(_pT->hActive, 720, 2) )		_pT->hActive = 720;
		else if ( u32CHK_RANGE(_pT->hActive, 640, 2) )		_pT->hActive = 640;
	}

	if (_pT->vActive %4 != 0)	//150209 : OTT STB 1080P 50Hz Flickering (1920x1078)
	{
		HDMI21_LINE_DBG(1017, "[%d] %s : vActive modification [%d]\n", __L__, __F__, _pT->vActive);
		if ( u32CHK_RANGE(_pT->vActive, 4320, 2) )			_pT->vActive = 4320;
		else if ( u32CHK_RANGE(_pT->vActive, 2160, 2) )		_pT->vActive = 2160;
		else if ( u32CHK_RANGE(_pT->vActive, 1600, 2) )		_pT->vActive = 1600;
		else if ( u32CHK_RANGE(_pT->vActive, 1440, 2) )		_pT->vActive = 1440;
		else if ( u32CHK_RANGE(_pT->vActive, 1080, 2) )		_pT->vActive = 1080;
		else if ( u32CHK_RANGE(_pT->vActive, 720, 2) )		_pT->vActive = 720;
		else if ( u32CHK_RANGE(_pT->vActive, 576, 2) )		_pT->vActive = 576;
		else if ( u32CHK_RANGE(_pT->vActive, 480, 2) )		_pT->vActive = 480;
		else if ( u32CHK_RANGE(_pT->vActive, 288, 2) )		_pT->vActive = 288;
		else if ( u32CHK_RANGE(_pT->vActive, 240, 2) )		_pT->vActive = 240;
		else if ( _pT->vActive == 483)	_pT->vActive = 483;
	}

	return;
}


/* Return 0:when nothing has been compensated, 1:Something has changed */
static int __HDMI21_HAL_Rx_Set_Compensate3DTimingInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI_TIMING_INFO_T *_pData, LX_HDMI_EXT_FORMAT_INFO_T lg3DData)
{
	int ret = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	LX_HDMI_TIMING_INFO_T *_pT = _pData;
	int i;
	UINT32 fix_offset;
	const HDMI21_NON_VSI_3D_TIMING_T *pTbl;
	UINT32 __actual_vActive_of_3DFA;

	/* Defence Code */
	if(_pT == NULL) return 0;

	/* Some devices sends 3D data, without 3D VSIF */
	if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value == 0){
		if(lg3DData == LX_HDMI_EXT_2D_FORMAT)
		{
			pTbl = &__sTBL_EXT_INFO[0];
			for (i = 0; i < TBL_NUM(__sTBL_EXT_INFO) ; i++, pTbl++)
			{
				if ((_pT->hActive == pTbl->hAct_info) && (_pT->vActive == pTbl->vAct_info) && (_pT->scanType== pTbl->scan_info) )
				{
					HDMI21_LINE_DBG(3401, "DBG[%d] : Detected 3D video without VSI info T[%d], [%d]x[%d] [%d] => [%d]x[%d] [%d][%d]\n",\
							_p->port, i, _pT->hActive, _pT->vActive, _pT->scanType, pTbl->hAct_info, pTbl->vAct_buf,\
							pTbl->scan_buf, pTbl->extInfo_buf);

					_pT->hActive 		= pTbl->hAct_buf;
					_pT->vActive 		= pTbl->vAct_buf;
					_pT->scanType	= pTbl->scan_buf;
					_pT->extInfo		= pTbl->extInfo_buf;
					lg3DData = _pT->extInfo;
					
					ret = 1;
					break;
				}
			}
		} 
	}


	/*  Need to modifiy Video sync params for MW, because some values must be divided by 2 for 3D videos*/
	switch(lg3DData)
	{
		case LX_HDMI_EXT_3D_FRAMEPACK:
			/* From Old issues from HDMI1.4
			 * Russia  STB Issue :VSI Info is 3D F/P and Source is 2D*/
			if ( ((_pT->hActive == 640) && (_pT->vActive == 480)) \
					|| ((_pT->hActive == 720) && (_pT->vActive == 480)) \
					|| ((_pT->hActive == 720) && (_pT->vActive == 576)) \
					|| ((_pT->hActive == 1280) && (_pT->vActive == 720)) \
					|| ((_pT->hActive == 1920) && (_pT->vActive == 1080)) )
			{
				HDMI21_LINE_DBG(4224, "DBG[%d] : 3D VSI info is F/P, but Timing Info is 2D format for Russia STB Issue \n", _p->port);
				_pT->extInfo = LX_HDMI_EXT_2D_FORMAT;
				ret = 1;
			}
			else if ( (_pT->vActive == 2228) ||(_pT->vActive == 1028) )		//1080i & 480i
			{

				if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
					_pT->scanType = 0;
				}
				else{
					/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
					_pT->scanType = 0;
					_pT->vActive = (_pT->vActive - 68) >> 1;	//68 : 23+22+23
				}
				ret = 1;
			}
			else if (_pT->vActive == 1226)		//576i
			{
				if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
					_pT->scanType = 0;
				}
				else{
					/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
					_pT->scanType = 0;
					_pT->vActive = (_pT->vActive - 74) >> 1;	//74 : 25+24+25
				}
				ret = 1;
			}
			else if (_pT->vActive == 1103)		// interace
			{
				/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
				_pT->scanType = 0;
				_pT->vActive = _pT->vActive - 23;
				ret = 1;
			}
			else			//progressive
			{
				if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
					/* Do not change value*/
				}
				else{
					/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
					_pT->vActive = (_pT->vActive - _pT->vTotal + _pT->vActive) >> 1;
					ret = 1;
				}
			}
			break;
		case LX_HDMI_EXT_3D_FIELD_ALTERNATIVE:
			/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
			_pT->scanType = 0;

			if (_pT->vActive == 1103)		fix_offset = 23; //1080! - 22.5
			else if (_pT->vActive == 601) 	fix_offset = 25; //576! - 24.5
			else if (_pT->vActive == 503)	fix_offset = 23; //480! - 22.5
			else 								fix_offset = 0;
			__actual_vActive_of_3DFA = _pT->vActive;
			_pT->vActive = _pT->vActive - fix_offset;
			_pT->vFreq = _pT->vFreq >> 1;

			if( gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
				_pT->vActive = __actual_vActive_of_3DFA;
			}
			ret = 1;
			break;
		case LX_HDMI_EXT_3D_LINE_ALTERNATIVE:
			if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
				/* Do not change value*/
			}
			else{
				_pT->vTotal = _pT->vTotal >> 1;
				_pT->vActive = _pT->vActive >> 1;
				_pT->vStart = _pT->vStart >> 1;
				ret = 1;
			}
			break;
		case LX_HDMI_EXT_3D_SBSFULL:
			if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
				/* Do not change value*/
			}
			else{
				_pT->hTotal = _pT->hTotal >> 1;
				_pT->hActive = _pT->hActive >> 1;
				_pT->hStart = _pT->hStart >> 1;
				ret = 1;

			}
			break;
		case LX_HDMI_EXT_3D_TNB:
			break;
		case LX_HDMI_EXT_3D_SBS:
			break;
		case LX_HDMI_EXT_3D_L_DEPTH:
		case LX_HDMI_EXT_3D_L_GRAPHICS:
		case LX_HDMI_EXT_2D_FORMAT:
		default :
			break;
	}

	return ret;
}

static LX_HDMI_EXT_FORMAT_INFO_T __HDMI21_HAL_Rx_Get_Convert3DtoLG3DFormat(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI_VSI_3D_STRUCTURE_T vsi3Ddata)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	LX_HDMI_EXT_FORMAT_INFO_T ret = LX_HDMI_EXT_2D_FORMAT;

	switch(vsi3Ddata)
	{
		case LX_HDMI_VSI_3D_STRUCTURE_FRAME_PACKING:
			ret = LX_HDMI_EXT_3D_FRAMEPACK;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE:
			ret = LX_HDMI_EXT_3D_FIELD_ALTERNATIVE;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_LINE_ALTERNATIVE:
			ret = LX_HDMI_EXT_3D_LINE_ALTERNATIVE;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_FULL:
			ret = LX_HDMI_EXT_3D_SBSFULL;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM:
			ret = LX_HDMI_EXT_3D_TNB;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_HALF:
			ret = LX_HDMI_EXT_3D_SBS;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_L_DEPTH:
			ret = LX_HDMI_EXT_3D_L_DEPTH;
			break;
		case LX_HDMI_VSI_3D_STRUCTURE_L_DEPTH_GRAPHICS:
			ret = 	LX_HDMI_EXT_3D_L_GRAPHICS;
			break;
		default :
			if((_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI][8] & 0xF0) == 0x20){
				ret = LX_HDMI_EXT_4K_2K;
			}
			else{
				ret = LX_HDMI_EXT_2D_FORMAT;
			}
			break;
	}

	return ret;
}

static void __HDMI21_HAL_Rx_Set_PixelRepetitionMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isRepetition)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __d = 0;

	__d = _p->top_read(HDMI21_TOP_REG_AD_MAIN_422TO444);

	/* This will not work until O20 B0 revision */
	if(isRepetition){
		__d |= (HDMI21_TOP_FIELD_REG_PIX_REP_MODE);
	}
	else{
		__d &= (~HDMI21_TOP_FIELD_REG_PIX_REP_MODE);
	}

	_p->top_write(HDMI21_TOP_REG_AD_MAIN_422TO444, __d);

	return;
}

static void __HDMI21_HAL_Rx_Set_CompensateWithVicCode(LX_HDMI_TIMING_INFO_T *_pData, UINT32 vicCode, HDMI21_HAL_PHY_INITIATED_MODE_T mode, int isVrr)
{
	LX_HDMI_TIMING_INFO_T *_pT = _pData;
	UINT16 hTotal  = 0;
	UINT16 hActive = 0;
	UINT16 vActive = 0;
	UINT16 diff = 0;

	UINT32 __data;

	/* SW WA : HTotal/Acitve : Fix UPlus+ 2880 issue on 1080p 24/25/30 */
	if((vicCode == 32)||(vicCode == 72)){
		hTotal = 2750;
		hActive = 1920;
	}
	else if((vicCode == 33)||(vicCode == 73)\
			||(vicCode == 20)||(vicCode == 31 )
			||(vicCode == 75)){
		hTotal = 2640;
		hActive = 1920;
	}
	else if((vicCode == 34 )||(vicCode == 74 )\
			||(vicCode == 16 )||(vicCode == 76 )
			||(vicCode == 5)){
		hTotal = 2200;
		hActive = 1920;
	}
	else if(vicCode == 39){
		hTotal = 2304;
		hActive = 1920;
	}

	/* SW WA :  HActive, VActive, HTotal, VFreq for 3D SBS Full issue */
	if(( vicCode == 22)&&(_pT->PixelRepeat == 0)){
		vActive = 576; 
		hActive = 1440;
		if(_pT->extInfo == LX_HDMI_EXT_3D_SBSFULL){
			if(gHDMI21RxDevVideoControler[HDMI21__FORCE_ORIGIN_TIME_FOR_3D].value){
				/* Do not change value : Restore*/
				hActive = 2880; 
			}
			hTotal = 3456;
		}
	}

	/* 4K 3840x2160 resolution correction */
	if((vicCode == 93)||(vicCode == 103)|| (vicCode == 114)|| (vicCode == 116)){
		hTotal = 5500;
		hActive = 3840;
		vActive = 2160;
	}
	else if((vicCode == 94)||(vicCode == 104)||(vicCode == 96 )||(vicCode == 106)||(vicCode == 117)||(vicCode == 119)) {
		hTotal = 5280;
		hActive = 3840;
		vActive = 2160;
	}
	else if((vicCode == 95 )||(vicCode == 105 )||(vicCode == 97 )||(vicCode == 107 )||(vicCode == 118 )||(vicCode == 120 )){
		hTotal = 4400;
		hActive = 3840;
		vActive = 2160;
	}


	/* 4K 4096x2160 resolution correction */
	if((vicCode == 98)||(vicCode == 115)){
		hTotal = 5500;
		hActive = 4096;
		vActive = 2160;
	}
	else if((vicCode == 99)||(vicCode == 101)||(vicCode == 218)) {
		hTotal = 5280;
		hActive = 4096;
		vActive = 2160;
	}
	else if((vicCode == 100 )||(vicCode == 102)||(vicCode == 219)){
		hTotal = 4400;
		hActive = 4096;
		vActive = 2160;
	}

	/* 5K 5120x2160 resolution correction */
	if(vicCode == 121){
		hTotal = 7500;
		hActive = 5120;
		vActive = 2160;
	}
	else if(vicCode == 122) {
		hTotal = 7200;
		hActive = 5120;
		vActive = 2160;
	}
	else if((vicCode ==  125)||(vicCode == 127)){
		hTotal = 6600;
		hActive = 5120;
		vActive = 2160;
	}
	else if(vicCode ==  124){
		hTotal = 6250;
		hActive = 5120;
		vActive = 2160;
	}
	else if(vicCode ==  123){
		hTotal = 6000;
		hActive = 5120;
		vActive = 2160;
	}
	else if((vicCode ==  126)||(vicCode == 193)){
		hTotal = 5500;
		hActive = 5120;
		vActive = 2160;
	}


	/* 8K 7680x4320 resolution correction */
	if((vicCode == 194)||(vicCode == 202)||(vicCode == 197)||(vicCode == 205)){
		hTotal = 11000;
		hActive = 7680;
		vActive = 4320;
	}
	else if((vicCode == 195)||(vicCode == 203)||(vicCode == 198)||(vicCode == 206)) {
		hTotal = 10800;
		hActive = 7680;
		vActive = 4320;
	}
	else if((vicCode == 200)||(vicCode == 208)) {
		hTotal = 10560;
		hActive = 7680;
		vActive = 4320;
	}
	else if((vicCode == 196 )||(vicCode == 204)||(vicCode == 199 )||(vicCode == 207)){
		hTotal = 9000;
		hActive = 7680;
		vActive = 4320;
	}
	else if((vicCode == 201)||(vicCode == 209)) {
		hTotal = 8800;
		hActive = 7680;
		vActive = 4320;
	}

	/* 8K 10240x4320 resolution correction */
	if((vicCode == 210)||(vicCode == 213)){
		hTotal = 12500;
		hActive = 10240;
		vActive = 4320;
	}
	else if(vicCode == 211) {
		hTotal = 13500;
		hActive = 10240;
		vActive = 4320;
	}
	else if(vicCode == 216) {
		hTotal = 13200;
		hActive = 10240;
		vActive = 4320;
	}
	else if((vicCode == 212)||(vicCode == 215)||(vicCode == 217)) {
		hTotal = 11000;
		hActive = 10240;
		vActive = 4320;
	}
	else if(vicCode == 214 ){
		hTotal = 13500;
		hActive = 10240;
		vActive = 4320;
	}

	/* Check whether value is reasonable */
	if(hTotal != 0) {
		if(hTotal >= _pT->hTotal )	{	diff = hTotal - _pT->hTotal;}
		else 						{	diff = _pT->hTotal - hTotal;}
	
		if(diff != 0) {
			if(diff <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_VIC_HTOTAL_COMP_THRES].value) {
				_pT->hTotal = hTotal;
				HDMI21_LINE_DBG(8608, "DBG : hTotal correction[%d]->[%d] (diff:%d)(VIC:%d)\n", _pT->hTotal, hTotal, diff, vicCode);
			}
			else {
				HDMI21_LINE_DBG(8609, "DBG : hTotal without Range(%d, %d) (diff:%d)(VIC:%d)\n", _pT->hTotal, hTotal, diff, vicCode);
			}
		}
	}

	if(hActive != 0) {
		if(hActive >= _pT->hActive )	{	diff = hActive - _pT->hActive;}
		else 							{	diff = _pT->hActive - hActive;}
	
		if(diff != 0) {
			if(diff <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_VIC_HACTIVE_COMP_THRES].value) {
				_pT->hActive = hActive;
				HDMI21_LINE_DBG(8608, "DBG : hActive correction[%d]->[%d] (diff:%d)(VIC:%d)\n", _pT->hActive, hActive, diff, vicCode);
			}
			else {
				HDMI21_LINE_DBG(8609, "DBG : hActive without Range(%d, %d) (diff:%d)(VIC:%d)\n", _pT->hActive, hActive, diff, vicCode);
			}
		}
	}

	if(vActive != 0) {
		if(vActive >= _pT->vActive )	{	diff = vActive - _pT->vActive;}
		else 							{	diff = _pT->vActive - vActive;}
	
		if(diff != 0) {
			if(diff <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_VIC_VACTIVE_COMP_THRES].value) {
				_pT->vActive = vActive;
				HDMI21_LINE_DBG(8608, "DBG : vActive correction[%d]->[%d] (diff:%d)(VIC:%d)\n", _pT->vActive, vActive, diff, vicCode);
			}
			else {
				HDMI21_LINE_DBG(8609, "DBG : vActive without Range(%d, %d) (diff:%d)(VIC:%d)\n", _pT->vActive, vActive, diff, vicCode);
			}
		}
	}

	/* SW WA :  Vfreq compenstate for VIC codes 
	 * 20191015 : only do this on FRL new devices, old TMDS source devices sometimes have wrong VIC */
	/* 2021/06/15 : VIC Correction for 24/25/48 Hz only. Some Old devices have wrong VIC */
	if((mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) || (isVrr > 0) || (_pT->vFreq < 500)){
		__data = (UINT32)HDMI21_HAL_Rx_Get_VICtoVfreq(vicCode);
		if( __data > 0){
			if( __data != _pT->vFreq){
				HDMI21_LINE_DBG(1747, "Warning!  Vfreq[%d] does not match VIC code[%d] vfreq[%d]\n", _pT->vFreq, vicCode, __data);
				_pT->vFreq = __data;
			}
		}
	}

	return;
}


static int  __HDMI21_HAL_Rx_Get_CheckChangeFlag(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;

	if((_p->scdc_change != 0) || (_p->video_change != 0) || (_p->tmds_change != 0) ) {
		/* SCDC Change should only be called when polling mode for SCDC is enabled */
		if(_p->scdc_change != 0){
			HDMI21_HAL_Rx_Set_ScdcMode(_p->port, 0);
		}
		else if(_p->tmds_change != 0){
			/* When SetSCDCMode function detected a SCDC mode change, it will clear tmds_change/video_change/aksv_chage
			 * Therefore, it would be meaningless to call change functions*/
			__HDMI21_HAL_Rx_Set_TMDS_Change(_p, 0);
		}
		else if(_p->video_change != 0){
			/* When on TMDS Change, it would be meaningless for video change to be called. This flag will get reseted on TMDS Change */
			__HDMI21_HAL_Rx_Set_Video_Change(_p);
		}
		/* Return non-zero value when something changed */
		ret = 1;


		HDMI21_HAL_Rx_Set_AudioReset(_p->port);
	}
	else if(_p->hdcp_change != 0) {
		__HDMI21_HAL_Rx_Set_HDCP_Change(_p);
		ret = 0; /* HDCP change should not trigger any change alert */
	}

	if(_p->audio_change != 0){
		__HDMI21_HAL_Rx_Set_Audio_Change(_p);
	}

	if(_p->audio_state == HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV){
		HDMI21_HAL_Rx_Set_AudioState(_p->port);
	}
	
	return ret;
}

static HDMI21_HAL_PHY_INITIATED_MODE_T __HDMI21_HAL_Rx_Get_CheckHwSCDCtmdsMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_HAL_PHY_INITIATED_MODE_T ret = HDMI21_HAL_PHY_INITIATED_ERROR;
	HDMI21_SCDC_FRL_MODE_T __hwStatus;

	/* Defence Code : Handler function pointer is about to be called */
	if(!_p->initiated) {
		HDMI20_ERROR("[%s:%d] Error! HDMI21 device Handler not initiated!\n", __F__, __L__);
		return HDMI21_HAL_PHY_INITIATED_ERROR;
	}

	/* Check if current SCDC mode is in FRL */
	__hwStatus = HDMI21_SCDC_Rx_Get_ScdcMode(_p);

	/* Map HDMI21_HAL_PHY_INITIATED_MODE structure */
	ret = (HDMI21_HAL_PHY_INITIATED_MODE_T)__hwStatus;
	
	/* Force mode override */
	if(	gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value > 0){
		
		/* Force SCDC PHY mode debugger */
		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value > HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
			ret = HDMI21_HAL_PHY_INITIATED_3G;
		}
		else {
			
			ret = (HDMI21_HAL_PHY_INITIATED_MODE_T)gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value;	
		}
	}

	/* Keep history */
	_p->scdcTmdsMode = ret;

	HDMI21_LINE_DBG(3939, "DBG[%d] : SCDC return is [%d].\n", _p->port, ret);

	return ret;
}

/* DBG function */
static void __HDMI21_HAL_Rx_DBG_PrintIRQ(int port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int i;

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		HDMI20_INFO("not supported for port[%d]\n", port);
		return;
	}

	_p = &gHDMI21RxHandler[port];

	for(i=0;i<HDMI21_ISR_MAXNUM;i++){
		HDMI20_INFO("Port [%d] : ISR TYPE[%02d] [%s] = [%d]\n", _p->port, i, __isr_type_to_str(i), _p->isr_count0[i]);  
	}

	return;
}

/* DBG function for Video status */
static void __HDMI21_HAL_Rx_DBG_PrintVideo(int port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_SNPS_LINK_REG_0X584_T _r0;
	HDMI21_SNPS_LINK_REG_0X588_T _r1;
	HDMI21_SNPS_LINK_REG_0X58C_T _r2;
	HDMI21_SNPS_LINK_REG_0X590_T _r3;
	HDMI21_SNPS_LINK_REG_0X594_T _r4;
	HDMI21_SNPS_LINK_REG_0X598_T _r5;
	HDMI21_SNPS_LINK_REG_0X59C_T _r6;
	HDMI21_SNPS_LINK_REG_0X5A0_T _r7;
	UINT32 __data;
	UINT32 __a = 0;
	int i = 1;

	if(((unsigned int)port)>= g_hdmi20_number_of_ports){
		printk("not supported for port[%d]\n", port);
		return;
	}

	/* Get Handler for Port */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];


	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) { __a = 0x4; }
	else { __a = 0; }

	/* 2019/06/24 : Get SCDC Info */
	__data = _p->link_read(0x584 + __a);	memcpy((void *)&_r0, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));
	__data = _p->link_read(0x588 + __a);	memcpy((void *)&_r1, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X588_T));
	__data = _p->link_read(0x58C + __a);	memcpy((void *)&_r2, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
	__data = _p->link_read(0x590 + __a);	memcpy((void *)&_r3, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X590_T));
	__data = _p->link_read(0x594 + __a);	memcpy((void *)&_r4, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X594_T));
	__data = _p->link_read(0x598 + __a);	memcpy((void *)&_r5, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X598_T));
	__data = _p->link_read(0x59C + __a);	memcpy((void *)&_r6, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X59C_T));
	__data = _p->link_read(0x5A0 + __a);	memcpy((void *)&_r7, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X5A0_T));

	printk("----------------------------------------------------------------\n");
	printk("Ver[%d][0x%02x] Port[%d] HDMI2.0 Module Status [%d]th Video | Platform[%d]\n", HDMI21_KERNEL_DRIVER_DATE, HDMI21_KERNEL_DRIVER_VER,_p->port, _p->stableHist, gHDMI20PlatformType);
	printk("----------------------------------------------------------------\n");
	printk("\t[%d]  Initated[%d] / Link IRQ[%d] / Top IRQ[%d] / 8K[%d] \n", i++, _p->initiated, _p->irq, _p->top_irq, _p->is8KModel);
	printk("\t[%d]  PHY   TMDS[%08llu] / Real TMDS[%08llu]\n", i++, _p->phy_tmds_clk, _p->real_tmds_clk);
	printk("\t[%d]  Pixel Clk[%08llu]  / Real Vfreq[%d]\n", i++, _p->real_pixel_clk, _p->real_vfreq); 
	printk("\t[%d]  HDCP1.4 Key[%d] / HDCP2.3 Key[%d]\n", i++, _p->gWasHDCP14Written, _p->gWasHDCP22Written);  
	printk("\t[%d]  Dolby HDR Info[%d] / ZombieMode[%d]\n", i++, _p->isDolbyHDR, _p->zombieMode);
	printk("\t[%d]  Stable CNT[%d] / VideoChangeCount[%d] / vidChgTime[%d]\n", i++, _p->stable_cnt, _p->videoChgCount, _p->vidChgTime);
	printk("[RAW Sync Info]\n");
	printk("\t[%d]  TMDS Clk[%010d] / Pixel Clk[%010d]\n", i++, _p->hwVideo.tmds_clk, _p->hwVideo.pixel_clk);
	printk("\t[%d]  DVI[%d] / Interlaced[%d] / Pixel Repetition[%d]\n", i++, _p->hwVideo.dvi, _p->hwVideo.interlaced, _p->hwVideo.pixel_repetition);
	printk("\t[%d]  Sig:[%d](%d)x[%d](%d)@[%d]Hz (%d). vo/ho:(%d)/(%d)\n", i++, _p->hwVideo.hactive, _p->hwVideo.htotal, _p->hwVideo.vactive, _p->hwVideo.vtotal,\
			_p->hwVideo.vfreq, _p->hwVideo.refresh_rate, _p->hwVideo.voffset, _p->hwVideo.hoffset );
	printk("\t[%d] Video Format[%s]\n", i++, __csc_to_str(_p->hwVideo.video_format));
	printk("\t[%d] VIC Code[%d] / DeepColorMode[%s]\n", i++,  _p->hwVideo.vicCode, __deepcolor_to_str(_p->hwVideo.deep_color_mode));
	if(gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value == 0) {
		printk("\t[%d] cvi_vfreq[%d]\n", i++,  _p->cvi_vfreq);
	}
	printk("[Stable Sync Info]\n");
	printk("\t[%d] TMDS Clk[%010d] / Pixel Clk[%010d]\n", i++, _p->video.tmds_clk, _p->video.pixel_clk);
	printk("\t[%d] DVI[%d] / Interlaced[%d] / Pixel Repetition[%d]\n", i++, _p->video.dvi, _p->video.interlaced, _p->video.pixel_repetition);
	printk("\t[%d] Sig:[%d](%d)x[%d](%d)@[%d]Hz (%d). vo/ho:(%d)/(%d)\n", i++, _p->video.hactive, _p->video.htotal, _p->video.vactive, _p->video.vtotal,\
			_p->video.vfreq, _p->video.refresh_rate, _p->video.voffset, _p->video.hoffset );
	printk("\t[%d] Video Format[%d] (0:RGB|1:YCbCr422|2:YCbcr444|3:YCbCr420\n", i++, _p->video.video_format);
	printk("\t[%d] VIC Code[%d] / VIC Vfreq[%d] / DeepColorMode[%s]\n", i++,  _p->video.vicCode, HDMI21_HAL_Rx_Get_VICtoVfreq(_p->video.vicCode), __deepcolor_to_str(_p->video.deep_color_mode));
	printk("----------------------------------------------------------------\n");
	printk("[PHY Info]=> PHY Lock[%d] TCS Done[%d] | CR Done[%d] | TCS Status[0x%08x]\n", _p->isPhyLocked, _p->phyTCSDone, _p->phyCrDone, _p->phyTCSState);
	printk("\t[%d] PHY Mode[%s] | FRL CTS Mode[%d] \n", i++, phymode_type_to_str(_p->phyInitiatedMode), _p->isPhyFrlCtsMode);
	printk("\t[%d] TCS Result Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyTCSResult[0], _p->phyTCSResult[1], _p->phyTCSResult[2], _p->phyTCSResult[3]);
	printk("\t[%d] RS  Result Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyRsResult[0], _p->phyRsResult[1], _p->phyRsResult[2], _p->phyRsResult[3]);
	printk("\t[%d] Delta Eye- Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDeltaMinus[0], _p->phyDeltaMinus[1], _p->phyDeltaMinus[2], _p->phyDeltaMinus[3]);
	printk("\t[%d] Delta Eye+ Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDeltaPlus[0], _p->phyDeltaPlus[1], _p->phyDeltaPlus[2], _p->phyDeltaPlus[3]);
	printk("\t[%d] %s Min Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++, (_p->phyCurrentTMDSExceptionRange>=0)?"TCS   ":" Delta",\
			_p->phyTCSMin[0], _p->phyTCSMin[1], _p->phyTCSMin[2], _p->phyTCSMin[3]);
	printk("\t[%d] %s Max Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,(_p->phyCurrentTMDSExceptionRange>=0)? "TCS   ":" Delta",\
			_p->phyTCSMax[0], _p->phyTCSMax[1], _p->phyTCSMax[2], _p->phyTCSMax[3]);
	printk("\t[%d] DFE A_01   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeA01Result[0], _p->phyDfeA01Result[1], _p->phyDfeA01Result[2], _p->phyDfeA01Result[3]);
	printk("\t[%d] DFE A_11   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeA11Result[0], _p->phyDfeA11Result[1], _p->phyDfeA11Result[2], _p->phyDfeA11Result[3]);
	printk("\t[%d] DFE B_1    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB1Result[0], _p->phyDfeB1Result[1], _p->phyDfeB1Result[2], _p->phyDfeB1Result[3]);		
	printk("\t[%d] DFE B_2    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB2Result[0], _p->phyDfeB2Result[1], _p->phyDfeB2Result[2], _p->phyDfeB2Result[3]);		
	printk("\t[%d] DFE B_3    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB3Result[0], _p->phyDfeB3Result[1], _p->phyDfeB3Result[2], _p->phyDfeB3Result[3]);		
	printk("\t[%d] DFE B_4    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB4Result[0], _p->phyDfeB4Result[1], _p->phyDfeB4Result[2], _p->phyDfeB4Result[3]);		
	printk("\t[%d] DFE B_5    Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] Ch3[0x%02x]\n", i++,\
			_p->phyDfeB5Result[0], _p->phyDfeB5Result[1], _p->phyDfeB5Result[2], _p->phyDfeB5Result[3]);		
	printk("----------------------------------------------------------------\n");
	printk("[PHY Error Count : %d][PHY Error collecting Period : 10^%d BER]\n", _p->phyErrCounter, (12 - gHDMI21RxDevPhyControler[HDMI21__PHY_ERROR_PERIOD_SEL].value));
	printk("\t[%d]  CED Err   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyCEDError[0], _p->phyCEDError[1], _p->phyCEDError[2], _p->phyCEDError[3]);
	printk("\t[%d] TMDS Err   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyTMDSError[0], _p->phyTMDSError[1], _p->phyTMDSError[2], _p->phyTMDSError[3]);
	printk("\t[%d] Recovery   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phySyncRecovery[0], _p->phySyncRecovery[1], _p->phySyncRecovery[2], _p->phySyncRecovery[3]);
	printk("\t[%d] Delta Er   Ch0[0x%02x] Ch1[0x%02x] Ch2[0x%02x] ch3[0x%02x]\n", i++,\
			_p->phyDeltaError[0], _p->phyDeltaError[1], _p->phyDeltaError[2], _p->phyDeltaError[3]);
	printk("\t[%d] Is PHY Mode [0~2]? =>[%d] / Exception State[%d] / Eye Measure State[%d]\n", i++, _p->phyCurrentTMDSExceptionRange, _p->phyExceptionState, gHdmi21EyeMeasure[_p->port]); 
	printk("----------------------------------------------------------------\n");
	printk("[Flag Info]\n");
	printk("\t[%d] RestartHPDFlag[%d], HPDInverse[%d], LinkInit[%d], FVA[%d]\n", i++, _p->restartHpdFlagUp, _p->isHPDInverseMode, _p->isLinkInitiated, _p->isFvaMode);
	printk("\t[%d] Change Flag:SCDC[%d] VIDEO[%d] AUDIO[%d] TMDS[%d] HDCP[%d] DCM[%d]\n", i++, _p->scdc_change, _p->video_change,\
			_p->audio_change, _p->tmds_change, _p->hdcp_change, _p->dcm_change);
	printk("\t[%d] is5Vconnected[%d], isHPD[%d], isHDCP22[%d], isHDCP14[%d], MConst[%d] QMSMode[%d]\n", i++, _p->is5Vconnected, _p->isHPD, _p->isHDCP22, _p->isHDCP14, _p->isMConst, _p->isQmsMode);
	printk("\t[%d] hpd_request[%d], fsm_phy_lock[%d], main_thread_init_request[%d]\n", i++, _p->hpd_request, _p->fsm_phy_lock, _p-> main_thread_init_request);
	printk("\t[%d] wasEDID[%d], Disabled[%d], isFreeSync[%d], isAllm[%d], isMute[%d]\n", i++, _p->wasEdidWritten, _p->hdmiDisabled,\
			_p->isFreeSyncMode, _p->isAllmMode, _p->isMute);
	printk("\t[%d] VRR Min[%d]/Max[%d], RepeaterHPD[%d], isSleepMode[%d], DDCMON[%d]\n", i++, _p->vfreq_min, _p->vfreq_max, _p->repeaterHpd, (int)_p->isSleepMode, _p->isDdcMonEnabled);
	printk("[Misc Info]\n");
	printk("\t[%d] Allm Recieved time[%d] / AVMute On Time[%d] / phyFrlSwWaState[%d] / DoviTime[%u]\n", i++, _p->allm_recieve_time, _p->avmute_on_time, _p->phyFrlSwWaState, _p->doviTimeStamp);
	printk("\t[%d] Cable Connected Time[%d] / LocalMuteTimer[%d] / EM VrrRcvTime[%d] / QMSTime[%d] / DolbyVSITime[%u]\n", i++, _p->cable_connect_time, _p->localmutetimer, _p->em_vrr_recieve_time, _p->em_qms_recieve_time,  _p->dolbyVsiTimeStamp);
	printk("\t[%d] Stable Time Updated[%d] / RestartHPDStamp[%d] / UI HdrOverride[%d] \n", i++, _p->updateTimingTime, _p->restartHPDTimeStamp, _p->hdrOverRide); 
	printk("\t[%d] 5V connected Time[%d] / Locking Time[%d] / HDCP14Stable Time[%d] / EM VRR VFREQ[%d]\n", i++, _p->connected5Vtime, _p->locking_time, _p->stablehdcp14time, _p->em_vrr_baseRate);
	printk("\t[%d] DSC[%d] / PKTErr[%d] / Current HDCP Auth Version => HDCP%d (csm :%d)\n", i++, _p->isDSC, _p->pktErrStateCnt, HDMI21_HAL_Rx_Get_HDCPStatus(_p->port), _p->hdcp23_csm);
	printk("[SCDC Info]\n");
	printk("\t[%d] Source Version[0x%x] StatusUpdate[%d] CedUpdate[%d] RRTest[%d]\n", i++,\
			_r0.SCDC_SOURCEVERSION, _r0.SCDC_STATUSUPDATE, _r0.SCDC_CEDUPDATE, _r0.SCDC_RRTEST);
	printk("\t[%d] Source TestUpdate[%d] FrlStart[%d] FltUpdate[%d] RsedUpdate[%d] FrlStateSts[%d]\n", i++,\
			_r0.SCDC_SOURCE_TEST_UPDATE, _r0.SCDC_FRL_START,_r0.SCDC_FLT_UPDATE,_r0.SCDC_RSED_UPDATE, _r0.FRL_START_STS);
	printk("\t[%d] ScrambleEn[%d] bitRatio[%d] ScramStatus[%d] \n", i++,\
			_r1.SCDC_SCRAMB_EN,_r1.SCDC_TMDSBITCLKRATIO,_r1.SCDC_SCRAMB_STATUS);
	printk("\t[%d] RrEnable[%d] FltNoRetrain[%d] FrlRate[0x%x]  FfeLevel[0x%x] \n", i++,\
			_r2.SCDC_RRENABLE, _r2.SCDC_FLT_NO_RETRAIN,_r2.SCDC_FRL_RATE,_r2.SCDC_FFE_LEVELS);
	printk("\t[%d] ClkDetect[%d] Ch0~2Locked[%d][%d][%d] LN0~3Locked[%d][%d][%d][%d]\n", i++,\
			_r3.SCDC_CLOCKDETECTED,_r3.SCDC_CH0LOCKED,_r3.SCDC_CH1LOCKED,_r3.SCDC_CH2LOCKED,_r3.SCDC_LN0LOCKED,\
			_r3.SCDC_LN1LOCKED,_r3.SCDC_LN2LOCKED,_r3.SCDC_LN3LOCKED);
	printk("\t[%d] FltLn0~3   LTPReq         [0x%04x]      [0x%04x]      [0x%04x]    [0x%04x]\n", i++,\
			_r3.SCDC_FLT_LN0_LTP_REQ, _r3.SCDC_FLT_LN1_LTP_REQ, _r3.SCDC_FLT_LN2_LTP_REQ, _r3.SCDC_FLT_LN3_LTP_REQ);
	printk("\t[%d] TMDS CED Valid/Error : Ch0[%d][0x%x] Ch1[%d][0x%x] Ch2[%d][0x%x]\n", i++,\
			_r4.SCDC_ERR_DET0_VALID, _r4.SCDC_ERR_DET0, _r4.SCDC_ERR_DET1_VALID, _r4.SCDC_ERR_DET1, _r5.SCDC_ERR_DET2_VALID, _r5.SCDC_ERR_DET2);
	printk("\t[%d] FRL CED Valid/Error :  L0 [%d][0x%x] L1 [%d][0x%x] L2 [%d][0x%x] L3 [%d][0x%x]\n", i++,\
			_r5.SCDC_ERDET_LANE0_VALID,_r5.SCDC_ERDET_LANE0,_r6.SCDC_ERDET_LANE1_VALID,_r6.SCDC_ERDET_LANE1,\
			_r6.SCDC_ERDET_LANE2_VALID,_r6.SCDC_ERDET_LANE2,_r7.SCDC_ERDET_LANE3_VALID,_r7.SCDC_ERDET_LANE3);
	printk("\t[%d] Reed Solomon Corrections Valid/Count : [%d][0x%x]\n", i++,\
			_r7.SCDC_RSFEC_CERDET_VALID, _r7.SCDC_RSFEC_CERDET);
	printk("[LOW POWER INFO]\n");
	printk("\t[%d] V4L2Activated[%d] / Mode[%d] / idleTick[%d]/ThreshTick[%d] / Cnt[%d] / InputChgCnt[%d]\n", i++, \
			_p->isV4l2Activated, _p->lowPowerMode, _p->idleTick,  gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value, _p->lowPowerAccumCnt, gHdmi21InputChgCnt);
	printk("\t[%d] LowPowerTimeStamp [%u] msec / AccumulatedPowerSaveTime [%u] msec\n", i++, \
			_p->lowPowerTimeStamp, _p->accumulatedLowPowerTime);
	printk("\t[%d] QMS BaseRate[%d] / QMS Next TFR[idx:%d][%s]\n", i++, _p->em_qms_baseRate, _p->em_qms_tfr, __tfr_to_str(_p->em_qms_tfr));
	printk("\t[%d] FilterSelSwWaCnt[%d] / ConsecutiveFilterSelSwWa[%d]\n", i++, _p->filterSelSwWaCnt, _p->consecutiveFilStuckCnt);
	printk("\t[%d] warmMode[%d], isPqeSuspend[%d], isFrl480pDcmForceSwWa[%d]\n", i++, gHdmi21WarmMode, _p->isPqeSuspend, _p->isFrl480pDcmForceSwWa);
	return;
}

static void __HDMI21_HAL_Rx_Get_PollCvtemStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Defence */
	if(_p == NULL) return;

	/* DSC is only prohibited on FRL modes */
	if(_p->phyInitiatedMode < HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) return;

	/* Store Packet */
	/* 2025/05/07 won.hur : Reading CVTEM without ISR can cause issues. 
	 * 						Reading the first byte of PKT's would snapshot/block incoming packets.
	 * 						DO NOT UN-ANNOTATE HDMI21_PDEC_Rx_Get_PktDataCVTEM() function!! */
	//HDMI21_PDEC_Rx_Get_PktDataCVTEM(_p); 
	
	/* Store to PPS data structure */
	HDMI21_HAL_Rx_Get_UpdateDscCvtemPpsData(_p);

	if(((_p->pps.dsc_version_minor == 1)||(_p->pps.dsc_version_minor == 2))&&(_p->pps.pic_width != 0) && (_p->pps.pic_height != 0))
	{
		if(_p->isDSC == 0) {
			HDMI20_INFO("DSC[%d] : Detected DSC Mode[Ver:1.%d] Video(%dx%d@%dHz) chunk size(%d) bps(%d)\n", _p->port, (int)_p->pps.dsc_version_minor,\
					_p->pps.pic_width, _p->pps.pic_height, _p->hwVideo.vfreq, _p->pps.chunk_size, _p->pps.bits_per_component);
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_DSC_USE_CAL_VALUE].value == 1) {
				HDMI21_VMON_Rx_Set_Initiate(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_VMON_SOURCE_TYPE_TMDS].value);
				HDMI20_INFO("VMON_SOURCE_SEL to 0x%x\n", gHDMI21RxDevLinkControler[HDMI21__LINK_VMON_SOURCE_TYPE_TMDS].value);
			}
		}
		_p->isDSC = 1;
	}
	else {
		if(_p->isDSC > 0) {
			HDMI20_INFO("DSC[%d] : Abort DSC mode detected\n", _p->port);
		}
		_p->isDSC = 0;
	}

}


static void __HDMI21_HAL_Rx_DBG_CalculateFrlPosition(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg  = 0; 
	UINT32 __data = 0;
	int i;

	if(gHdmi21FrlErrState[_p->port] == -1){
		/* First Stage */
		HDMI20_INFO("DBG[%d] : Detected FRL position Measure Operation.\n", _p->port);

		/* Activate Settings for measurement */
		__reg = 0x90; __reg = (__reg << 2) + 0x400; __data = 0x0F; _p->phyDR_write(__reg, __data);
		
		gHdmi21FrlErrState[_p->port]++;

		__reg = 0x8C; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data);
		__reg = 0x8D; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data);	
		__reg = 0x8E; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data);
		__reg = 0x8F; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data);
	}
	else {
		for(i=0;i<4;i++) {
			if(gHdmi21FrlErrDone[_p->port][i] == 0) {
				if(_p->phyCEDError[i] == 0) {
					HDMI20_INFO("DBG[%d] : Found match value[0x%x] for ch[%d]\n", _p->port, gHdmi21FrlErrState[_p->port], i);
					gHdmi21FrlValue[_p->port][i] = gHdmi21FrlErrState[_p->port];
					gHdmi21FrlErrDone[_p->port][i] = 1;
				}
			}
		}

		if((gHdmi21FrlErrDone[_p->port][0] >= 1) && (gHdmi21FrlErrDone[_p->port][1] >= 1)\
				&&(gHdmi21FrlErrDone[_p->port][2] >= 1) &&(gHdmi21FrlErrDone[_p->port][3] >= 1)){
			/* Update Flag */
			gHdmi21FrlErrMeasure[_p->port] = 2;

			HDMI20_INFO("DBG[%d] : FRL position Measure Done! [0x%x][0x%x][0x%x][0x%x]\n",\
					_p->port, gHdmi21FrlValue[_p->port][0], gHdmi21FrlValue[_p->port][1],\
					gHdmi21FrlValue[_p->port][2],gHdmi21FrlValue[_p->port][3]);
			return;
		}

		gHdmi21FrlErrState[_p->port]++;

		if(gHdmi21FrlErrState[_p->port] >= 0x1F) {
			HDMI20_INFO("DBG[%d] : Error! Could not complete due to full error! [%d][%d][%d][%d]\n", \
					_p->port, gHdmi21FrlErrDone[_p->port][0], gHdmi21FrlErrDone[_p->port][1],\
					gHdmi21FrlErrDone[_p->port][2], gHdmi21FrlErrDone[_p->port][3]);

			/* Update Flag */
			gHdmi21FrlErrMeasure[_p->port] = 3;

			return;
		}

		if(gHdmi21FrlErrDone[_p->port][0] == 0) {
			__reg = 0x8C; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data);}

		if(gHdmi21FrlErrDone[_p->port][1] == 0) {
			__reg = 0x8D; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data);	}

		if(gHdmi21FrlErrDone[_p->port][2] == 0) {
			__reg = 0x8E; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data); }

		if(gHdmi21FrlErrDone[_p->port][3] == 0) {
			__reg = 0x8F; __reg = (__reg << 2) + 0x400;  __data = gHdmi21FrlErrState[_p->port]; _p->phyDR_write(__reg, __data); }
	}
}


static void __HDMI21_HAL_Rx_DBG_CalculatePhyEyeDiagrame(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	static UINT32 __ret[HDMI21_NUM_OF_MAX_PORTS] = {0,};
	UINT32 __reg  = 0; 
	UINT32 __data = 0;
	UINT32 store_dr1_89 = 0;
	UINT32 y, x, i, __temp;
	/* X : -15~ +15 => 31
	 * Y : -63~ +63 => 127 */

	if((gHdmi21EyeStage[_p->port] == 0) && (gHdmi21EyeXposition[_p->port] == 0)\
			&& (gHdmi21EyeYposition[_p->port] == 0)){
		/* First Stage */
		HDMI20_INFO("DBG[%d] : Detected Eye Measure Operation.\n", _p->port);

		/* Reset return values */
		__ret[_p->port] = 0;

		/* Activate Settings for measurement */
		/* 2025/03/25 won.hur : 38:0x8C is identical among O22/O24/O26 */
		if(lx_chip_rev() >= LX_CHIP_REV(O22, A0) ){
			//i2c_delta_en_mode, i2c_delta_en_val, i2c_alpha_off_mode	
			__reg = 0x8C; __reg = __reg << 2; __data = 0x07;
		} else if( lx_chip_rev() >= LX_CHIP_REV(E60, B0) ) {
			//i2c_delta_en_mode, i2c_delta_en_val
			__reg = 0x8C; __reg = __reg << 2; __data = 0x03;
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
			__reg = 0x89; __reg = __reg<<2; 	store_dr1_89 = _p->phyDR_read(__reg);
			store_dr1_89 &= 0x3;
			__data = (store_dr1_89 | 0x30);
		}
		else{
			__reg = 0x89; __reg = __reg << 2; __data = 0x03;
		}
		_p->phyDR_write(__reg, __data);

		if( lx_chip_rev() >= LX_CHIP_REV(E60,B0) ) {
			//I2C_DATA_DELTA_MODE_CH0 ~ CH3
			//sign path enable
			__reg = 0x82; __reg = __reg <<2; __data = 0xAA;
			_p->phyDR_write(__reg, __data);
		} else {
			__reg = 0x7C; __reg = __reg << 2; __data = 0xAA;
			_p->phyDR_write(__reg, __data);
		}

		__temp = 0;
		if(lx_chip_rev() >= LX_CHIP_REV(E60, B0)){
			//E60B0 
			__reg = 0x81, __reg = __reg<<2; gHDMI21DfeLevelAMode = _p->phyDR_read(__reg);
			//i2c_dfe_level_a_01_mode:1
			//i2c_dfe_level_a_11_mode:1
			__reg = 0x81; __reg = __reg<<2; __data = (gHDMI21DfeLevelAMode | 0x60);
			_p->phyDR_write(__reg, __data);
		} else {
			for(i=0;i<4;i++)
			{
				__reg = 0x3B; __reg = __reg << 2; __data = __temp; __temp++;
				_p->phyDR_write(__reg, __data);

				__reg = 0x52; __reg = __reg << 2; __data = 0xE0;
				_p->phyDR_write(__reg, __data);
			}
		}

		if( lx_chip_rev() >= LX_CHIP_REV(E60, B0)){
			//E60B0 manual alpha value of i2c_dfe_level_a_ch0
			__reg = 0x6D; __reg=__reg <<2; __data = 0x0;
			_p->phyDR_write(__reg, __data);
			//E60B0 manual alpha value of i2c_dfe_level_a_ch1
			__reg = 0x72; __reg=__reg <<2; __data = 0x0;
			_p->phyDR_write(__reg, __data);
			//E60B0 manual alpha value of i2c_dfe_level_a_ch2
			__reg = 0x77; __reg=__reg <<2; __data = 0x0;
			_p->phyDR_write(__reg, __data);
			//E60B0 manual alpha value of i2c_dfe_level_a_ch3
			__reg = 0x7C; __reg=__reg <<2; __data = 0x0;
			_p->phyDR_write(__reg, __data);

		} else {
			// alpha value of i2c_dfe_level_a
			__reg = 0x53; __reg = __reg << 2; __data = 0x00;
			_p->phyDR_write(__reg, __data);
		}

	

		gHdmi21EyeXposition[_p->port] = 1;

		__ret[_p->port] = __HDMI21_HAL_Rx_DBG_SetEyeCalPosition(_p,\
				gHdmi21EyeXaxis[gHdmi21EyeStage[_p->port]], gHdmi21EyeYaxis[gHdmi21EyeStage[_p->port]], \
				gHdmi21EyeXposition[_p->port], gHdmi21EyeYposition[_p->port]);
	}
	else {
		/* Calculate X,Y */
		if(gHdmi21EyeXaxis[gHdmi21EyeStage[_p->port]] > 0) { x = 15 + gHdmi21EyeXposition[_p->port]; }
		else { x = 15 - gHdmi21EyeXposition[_p->port]; }

		if(gHdmi21EyeYaxis[gHdmi21EyeStage[_p->port]] > 0) { y = 63 + gHdmi21EyeYposition[_p->port]; }
		else { y = 63 - gHdmi21EyeYposition[_p->port]; }

		if((__ret[_p->port] & 0x1) == 0) gHdmi21EyeDataCh0[_p->port][y][x] = __HDMI21_HAL_Rx_DBG_GetDeltaError(_p, 0);
		else gHdmi21EyeDataCh0[_p->port][y][x] = 16;

		if((__ret[_p->port] & 0x2) == 0) gHdmi21EyeDataCh1[_p->port][y][x] = __HDMI21_HAL_Rx_DBG_GetDeltaError(_p, 1);
		else gHdmi21EyeDataCh1[_p->port][y][x] = 16;

		if((__ret[_p->port] & 0x4) == 0) gHdmi21EyeDataCh2[_p->port][y][x] = __HDMI21_HAL_Rx_DBG_GetDeltaError(_p, 2);
		else gHdmi21EyeDataCh2[_p->port][y][x] = 16;

		if((__ret[_p->port] & 0x8) == 0) gHdmi21EyeDataCh3[_p->port][y][x] = __HDMI21_HAL_Rx_DBG_GetDeltaError(_p, 3);
		else gHdmi21EyeDataCh3[_p->port][y][x] = 16;

		HDMI21_LINE_DBG(7711, "DBG[%d] : X[%d]/Y[%d] -> [%02d][%02d][%02d][%02d]\n", _p->port,\
				x,y,gHdmi21EyeDataCh0[_p->port][y][x],gHdmi21EyeDataCh1[_p->port][y][x],gHdmi21EyeDataCh2[_p->port][y][x],gHdmi21EyeDataCh3[_p->port][y][x]);

		gHdmi21EyeXposition[_p->port]++;

		if(gHdmi21EyeXposition[_p->port] > 15) {
			gHdmi21EyeXposition[_p->port] = 0;
			gHdmi21EyeYposition[_p->port] += gHdmi21EyeYPrintScale;

			if(gHdmi21EyeYposition[_p->port] > 63) {
				gHdmi21EyeYposition[_p->port] = 0;
				gHdmi21EyeStage[_p->port] ++;

				if(gHdmi21EyeStage[_p->port] > 3) {
					HDMI20_INFO("DBG[%d] : Finish Eye measurement\n", _p->port);
					
					/* Activate Settings for measurement */
					//E60B0 address change (0x38:0x89 -> 0x38:0x8c)
					if(lx_chip_rev() >= LX_CHIP_REV(E60,B0)){
						__reg = 0x8C; __reg = __reg << 2; __data = 0x00;
					} else if (lx_chip_rev() >= LX_CHIP_REV(O20,B0)) {
						//Restore DR1_0x89
						__reg = 0x89, __reg = __reg<<2; _p->phyDR_write(__reg,store_dr1_89);
					} else {
						__reg = 0x89; __reg = __reg << 2; __data = 0x00;
					}
					_p->phyDR_write(__reg, __data);
					//E60B0 address changed or removed
					if(lx_chip_rev() >= LX_CHIP_REV(E60,B0)){
						__reg = 0x82; __reg = __reg <<2; __data = 0x00;
					} else {
						__reg = 0x7C; __reg = __reg << 2; __data = 0x00;
					}
					_p->phyDR_write(__reg, __data);

					gHdmi21EyeMeasure[_p->port] = 2;
					//Restore Eye measurement PHY setting
					__reg = 0x81, __reg = __reg<<2; _p->phyDR_write(__reg, gHDMI21DfeLevelAMode);
				}
			}
		}

		if(gHdmi21EyeMeasure[_p->port] != 2) {
			/* Calculate X,Y */
			if(gHdmi21EyeXaxis[gHdmi21EyeStage[_p->port]] > 0) { x = 15 + gHdmi21EyeXposition[_p->port]; }
			else { x = 15 - gHdmi21EyeXposition[_p->port]; }

			if(gHdmi21EyeYaxis[gHdmi21EyeStage[_p->port]] > 0) { y = 63 + gHdmi21EyeYposition[_p->port]; }
			else { y = 63 - gHdmi21EyeYposition[_p->port]; }

			HDMI21_LINE_DBG(7730, "DBG[%d] : XAxis[%d]/YAxis[%d]/X[%d]/Y[%d]\n", _p->port,\
					gHdmi21EyeXaxis[gHdmi21EyeStage[_p->port]], gHdmi21EyeYaxis[gHdmi21EyeStage[_p->port]],x,y);
					
			__ret[_p->port] = __HDMI21_HAL_Rx_DBG_SetEyeCalPosition(_p,\
					gHdmi21EyeXaxis[gHdmi21EyeStage[_p->port]], gHdmi21EyeYaxis[gHdmi21EyeStage[_p->port]],\
					gHdmi21EyeXposition[_p->port], gHdmi21EyeYposition[_p->port]);
		}
	}
	
	return;
}

static UINT32 __HDMI21_HAL_Rx_DBG_SetEyeCalPosition(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isXPositive, bool isYpositive, UINT32 x, UINT32 y)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 ret = 0;
	UINT32 __reg  = 0; 
	UINT32 __data = 0;
	int i=0;
	UINT32 __answer, __verify0, __verify1;
	int __attemp;

	if(_p == NULL) return 0;

	/* Direction */
	if( lx_chip_rev() >= LX_CHIP_REV(E60, B0)) { 
		//E60B0 address update
		//[6] i2c_d_delta_sign
		//[5] i2c_s_delta_sign_mode
		//[4] i2c_s_delta_sign
		//[2:0] dr_phase_interval
		__reg = 0x8B; __reg = __reg << 2;
	} else {
		__reg = 0x7B; __reg = __reg << 2; 
	}

	if(isXPositive)	__data = 0x21;	//i2c_s_delta_sign: 0
	else			__data = 0x31; 	//i2c_s_delta_sign: 1
	_p->phyDR_write(__reg, __data);


	/* X axis */
	if( lx_chip_rev() >= LX_CHIP_REV(E60,B0)){
		//E60B0 
		//i2c_s_delta
		__reg = 0x85; __reg = __reg << 2; 
		__data = x;
		_p->phyDR_write(__reg, __data);
	} else {
		//dr_phsel 
		__reg = 0x7A; __reg = __reg << 2; 
		__data = x;
		_p->phyDR_write(__reg, __data);
	}

	/* Y axis */
	if( lx_chip_rev() >= LX_CHIP_REV(E60, B0)){

		if(isYpositive) {
			__data = y;
		} else {
			__data = 0x80-y;
		}

		//E60B0 manual alpha value of i2c_dfe_level_a_ch0
		__reg = 0x6D; __reg=__reg <<2; 
		_p->phyDR_write(__reg, __data);
		//E60B0 manual alpha value of i2c_dfe_level_a_ch1
		__reg = 0x72; __reg=__reg <<2; 
		_p->phyDR_write(__reg, __data);
		//E60B0 manual alpha value of i2c_dfe_level_a_ch2
		__reg = 0x77; __reg=__reg <<2; 
		_p->phyDR_write(__reg, __data);
		//E60B0 manual alpha value of i2c_dfe_level_a_ch3
		__reg = 0x7C; __reg=__reg <<2; 
		_p->phyDR_write(__reg, __data);
	} else { 
		// i2c_def_level_a
		__reg = 0x53; __reg = __reg << 2; 
		if(isYpositive) {__data = y;}
		else { __data = 0x80 - y;}
		_p->phyDR_write(__reg, __data);
	}
	__answer = __data;

	if(__answer == 0x80) __answer = 0;
	else if(__answer == 0x0) __answer = 0x80;

	if(lx_chip_rev() >= LX_CHIP_REV(E60,B0)) {

		__attemp = 10;
		while(__attemp > 0 )
		{
			//E60B0 
			//i2c_dfe_level_a_01_mode:1
			//i2c_dfe_level_a_11_mode:1
			__reg = 0x81; __reg = __reg<<2; __data = (gHDMI21DfeLevelAMode | 0x60);
			_p->phyDR_write(__reg, __data);

			//Read i2c_dfe_level_a_01, i2c_dfe_level_a_11;
			__reg = 0x35; __reg = __reg<<2; __verify0 = _p->phyDR_read(__reg);
			__reg = 0x36; __reg = __reg<<2; __verify1 = _p->phyDR_read(__reg);

			if( (__verify0 == __answer) && (__verify1 == __answer)) {
				ret &= 0;
				 HDMI21_LINE_DBG(7979, "OK[%d] : Attemp[%d]  X[%d]Y[%d] Ch[%d] [%d] but value was 0x35[%d] 0x36[%d]\n",\
				 _p->port, __attemp, x, y, i, __answer, __verify0, __verify1);

				break;
			} else {
				HDMI21_LINE_DBG(7979, "WARNING[%d] : Attemp[%d]  X[%d]Y[%d] Ch[%d] set error! Try to set[%d] but value was 0x35[%d] 0x36[%d]\n",\
						_p->port, __attemp, x, y, i, __answer, __verify0, __verify1);
				if((__verify0 != __answer) && (__verify1 != __answer)) {
					ret |= 0x1;
				}
				__attemp--;
			}
		}

	} else {
		for(i=0;i<4;i++)
		{
			__attemp = 10;

			while(__attemp > 0){

				//dfe_result_ch_sel
				__reg = 0x3B; __reg = __reg << 2; __data = i;
				_p->phyDR_write(__reg, __data);

				//dfe_man_val_en:1 
				//i2c_dfe_level_a_01_mode:1 
				//i2c_dfe_level_a_11_mode:1 
				__reg = 0x52; __reg = __reg << 2; __data = 0xE0;
				_p->phyDR_write(__reg, __data);

				__reg = 0x35; __reg = __reg << 2; __verify0 = _p->phyDR_read(__reg);
				__reg = 0x36; __reg = __reg << 2; __verify1 = _p->phyDR_read(__reg);

				if((__verify0 == __answer) && (__verify1 == __answer)) {
					ret &= (~(0x1<<i));
					break;
				}
				else {
					HDMI21_LINE_DBG(7979, "WARNING[%d] : Attemp[%d]  X[%d]Y[%d] Ch[%d] set error! Try to set[%d] but value was 0x35[%d] 0x36[%d]\n",\
							_p->port, __attemp, x, y, i, __answer, __verify0, __verify1);
					if((__verify0 != __answer) && (__verify1 != __answer)) {
						ret |= (0x1 << i);
					}
					__attemp--;
				}
			}
		}
	}

	return ret;
}

static UINT32 __HDMI21_HAL_Rx_DBG_GetDeltaError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 ch)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 ret = 0;
	UINT32 __reg  = 0; 
	UINT32 __data = 0;

	if(_p == NULL) return 0;

	if(ch == 0) __reg = 0x14;
	else if(ch == 1) __reg = 0x15;
	else if(ch == 2) __reg = 0x16;
	else __reg = 0x17;
	
	__reg = __reg << 2; 
	__data = _p->phyDR_read(__reg);
	
	ret = ((__data & 0x000000F0) >> 4);

	return ret;
}

static void __HDMI21_HAL_Rx_DBG_PrintEyeDiagramChr(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int x,y;
	UINT8 idx = 0;

	if(gHdmi21EyeMeasure[_p->port] == 1) {
		printk("Cannot show results. Eye Measure is in Progress\n");
		return;
	}
	else if(gHdmi21EyeMeasure[_p->port] == 0) {
		printk("Measurement was not initiated\n");
		return;
	}

	printk(KERN_CONT "Port[%d] Delta Eye Diagram\n", _p->port);
	printk(KERN_CONT "      | ");
	for(x=0;x<31;x++) {  if((x==14)||(x==15)) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT " | ");
	for(x=0;x<31;x++) {  if((x==14)||(x==15)) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT " | ");
	for(x=0;x<31;x++) {  if((x==14)||(x==15)) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT " | ");
	for(x=0;x<31;x++) {  if((x==14)||(x==15)) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT "\n");

	for(y=0;y<127;y=y+gHdmi21EyeYPrintScale)
	{
		if(y == 63){ 
			printk(KERN_CONT "AL000 * "); 
		} else {
			if( y < 63 ){
				idx = 63-y;
			} else {
				idx = (y-63)+100;
			}
			printk(KERN_CONT "AL%03d | ", idx);
		}

		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_graphic(gHdmi21EyeDataCh0[_p->port][y][x]));	
		printk(KERN_CONT " | ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_graphic(gHdmi21EyeDataCh1[_p->port][y][x]));
		printk(KERN_CONT " | ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_graphic(gHdmi21EyeDataCh2[_p->port][y][x]));
		printk(KERN_CONT " | ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_graphic(gHdmi21EyeDataCh3[_p->port][y][x]));
	
		printk(KERN_CONT "\n");
	}

	return;
}

static void __HDMI21_HAL_Rx_DBG_PrintEyeDiagramHex(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int x,y;

	if(gHdmi21EyeMeasure[_p->port] == 1) {
		printk("Cannot show results. Eye Measure is in Progress\n");
		return;
	}
	else if(gHdmi21EyeMeasure[_p->port] == 0) {
		printk("Measurement was not initiated\n");
		return;
	}

	printk(KERN_CONT "Port[%d] Delta Eye Diagram\n", _p->port);
	printk(KERN_CONT "-");
	for(x=0;x<31;x++) {  if(x==16) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT " | ");
	for(x=0;x<31;x++) {  if(x==16) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT " | ");
	for(x=0;x<31;x++) {  if(x==16) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT " | ");
	for(x=0;x<31;x++) {  if(x==16) printk(KERN_CONT "*"); else printk(KERN_CONT "-"); }
	printk(KERN_CONT "\n");

	for(y=0;y<127;y=y+gHdmi21EyeYPrintScale)
	{
		if(y == 63) printk(KERN_CONT "*");
		else printk(KERN_CONT "| ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_hex(gHdmi21EyeDataCh0[_p->port][y][x]));	
		printk(KERN_CONT " | ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_hex(gHdmi21EyeDataCh1[_p->port][y][x]));
		printk(KERN_CONT " | ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_hex(gHdmi21EyeDataCh2[_p->port][y][x]));
		printk(KERN_CONT " | ");
		for(x=0;x<31;x++)	printk(KERN_CONT "%s", __val_to_hex(gHdmi21EyeDataCh3[_p->port][y][x]));
	
		printk(KERN_CONT "\n");
	}

	return;
}


static void 	__HDMI21_HAL_Rx_Get_PrintDscCvtemPpsData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int __bpp = 0;

	do{
		/* Device Handler NULL defence */
		if(_p == NULL) {
			HDMI20_ERROR("Error : NULL Handler\n");
			break;
		}
	
		/* 2020/07/14 : actual bpp calculation */
		__bpp = (int)_p->pps.bits_per_pixel;
		__bpp = __bpp >> 4;
		if((_p->hwVideo.video_format == 1) || (_p->hwVideo.video_format == 3)) { __bpp = __bpp >> 1;}

		printk("Port[%d] : DSC PPS from CVTEM \n", _p->port);
		printk("bits_per_component                      = 0x%x\n",_p->pps.bits_per_component);
		printk("convert_rgb                             = 0x%x\n",_p->pps.convert_rgb);
		printk("simple_422                              = 0x%x\n",_p->pps.simple_422);
		printk("linebuf_depth                           = 0x%x\n",_p->pps.linebuf_depth);
		printk("bits_per_pixel                          = 0x%x (calculated bpp : %d)\n", _p->pps.bits_per_pixel, __bpp);
		printk("_block_pred_enable                      = 0x%x\n", _p->pps._block_pred_enable);
		printk("native_420                              = 0x%x\n", _p->pps.native_420);
		printk("native_422                              = 0x%x\n", _p->pps.native_422);
		printk("dsc_version_minor                       = 0x%x\n", _p->pps.dsc_version_minor);
		printk("pic_width                               = 0x%x(%d)\n", _p->pps.pic_width, _p->pps.pic_width);
		printk("pic_height                              = 0x%x(%d)\n", _p->pps.pic_height, _p->pps.pic_height);	
		printk("slice_width                             = 0x%x(%d)\n", _p->pps.slice_width,_p->pps.slice_width);	
		printk("slice_height                            = 0x%x(%d)\n", _p->pps.slice_height, _p->pps.slice_height);
		printk("chunk_size                              = 0x%x\n", _p->pps.chunk_size);	
		printk("initial_xmit_delay                      = 0x%x\n", _p->pps.initial_xmit_delay);
		printk("initial_dec_delay                       = 0x%x\n", _p->pps.initial_dec_delay);
		printk("initial_scale_value                     = 0x%x\n", _p->pps.initial_scale_value);
		printk("scale_increment_interval                = 0x%x\n", _p->pps.scale_increment_interval);
		printk("scale_decrement_interval                = 0x%x\n", _p->pps.scale_decrement_interval);
		printk("first_line_bpg_offset                   = 0x%x\n", _p->pps.first_line_bpg_offset);
		printk("second_line_bpg_offset                  = 0x%x\n", _p->pps.second_line_bpg_offset);
		printk("nfl_bpg_offset                          = 0x%x\n", _p->pps.nfl_bpg_offset);		
		printk("slice_bpg_offset                        = 0x%x\n", _p->pps.slice_bpg_offset);
		printk("initial_offset                          = 0x%x\n", _p->pps.initial_offset);		
		printk("final_offset                            = 0x%x\n", _p->pps.final_offset);	
		printk("nsl_bpg_offset                          = 0x%x\n", _p->pps.nsl_bpg_offset);		
		printk("second_line_offset_adj                  = 0x%x\n", _p->pps.second_line_offset_adj);
		printk("flatness_min_qp                         = 0x%x\n", _p->pps.flatness_min_qp);		
		printk("flatness_max_qp                         = 0x%x\n", _p->pps.flatness_max_qp);		
		printk("flatness_det_thresh                     = 0x%x\n", _p->pps.flatness_det_thresh);
		printk("rc_model_size                           = 0x%x\n", _p->pps.rc_model_size);		
		printk("rc_edge_factor                          = 0x%x\n", _p->pps.rc_edge_factor);		
		printk("rc_quant_incr_limit0                    = 0x%x\n", _p->pps.rc_quant_incr_limit0);
		printk("rc_quant_incr_limit1                    = 0x%x\n", _p->pps.rc_quant_incr_limit1);
		printk("rc_tgt_offset_hi                        = 0x%x\n", _p->pps.rc_tgt_offset_hi);	
		printk("rc_tgt_offset_lo                        = 0x%x\n", _p->pps.rc_tgt_offset_lo);	
		printk("rc_buf_thresh_0                         = 0x%x\n", _p->pps.rc_buf_thresh_0);		
		printk("rc_buf_thresh_1                         = 0x%x\n", _p->pps.rc_buf_thresh_1);		
		printk("rc_buf_thresh_2                         = 0x%x\n", _p->pps.rc_buf_thresh_2);		
		printk("rc_buf_thresh_3                         = 0x%x\n", _p->pps.rc_buf_thresh_3);		
		printk("rc_buf_thresh_4                         = 0x%x\n", _p->pps.rc_buf_thresh_4);		
		printk("rc_buf_thresh_5                         = 0x%x\n", _p->pps.rc_buf_thresh_5);		
		printk("rc_buf_thresh_6                         = 0x%x\n", _p->pps.rc_buf_thresh_6);		
		printk("rc_buf_thresh_7                         = 0x%x\n", _p->pps.rc_buf_thresh_7);		
		printk("rc_buf_thresh_8                         = 0x%x\n", _p->pps.rc_buf_thresh_8);		
		printk("rc_buf_thresh_9                         = 0x%x\n", _p->pps.rc_buf_thresh_9);		
		printk("rc_buf_thresh_10                        = 0x%x\n", _p->pps.rc_buf_thresh_10);	
		printk("rc_buf_thresh_11                        = 0x%x\n", _p->pps.rc_buf_thresh_11);	
		printk("rc_buf_thresh_12                        = 0x%x\n", _p->pps.rc_buf_thresh_12);	
		printk("rc_buf_thresh_13                        = 0x%x\n", _p->pps.rc_buf_thresh_13);	
		printk("rc_range_parameters_range min/max/offset[00] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_0_range_min_qp, _p->pps.rc_range_parameters_0_range_max_qp, _p->pps.rc_range_parameters_0_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[01] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_1_range_min_qp, _p->pps.rc_range_parameters_1_range_max_qp, _p->pps.rc_range_parameters_1_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[02] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_2_range_min_qp, _p->pps.rc_range_parameters_2_range_max_qp, _p->pps.rc_range_parameters_2_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[03] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_3_range_min_qp, _p->pps.rc_range_parameters_3_range_max_qp, _p->pps.rc_range_parameters_3_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[04] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_4_range_min_qp, _p->pps.rc_range_parameters_4_range_max_qp, _p->pps.rc_range_parameters_4_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[05] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_5_range_min_qp, _p->pps.rc_range_parameters_5_range_max_qp, _p->pps.rc_range_parameters_5_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[06] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_6_range_min_qp, _p->pps.rc_range_parameters_6_range_max_qp, _p->pps.rc_range_parameters_6_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[07] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_7_range_min_qp, _p->pps.rc_range_parameters_7_range_max_qp, _p->pps.rc_range_parameters_7_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[08] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_8_range_min_qp, _p->pps.rc_range_parameters_8_range_max_qp, _p->pps.rc_range_parameters_8_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[09] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_9_range_min_qp, _p->pps.rc_range_parameters_9_range_max_qp, _p->pps.rc_range_parameters_9_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[10] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_10_range_min_qp, _p->pps.rc_range_parameters_10_range_max_qp, _p->pps.rc_range_parameters_10_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[11] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_11_range_min_qp, _p->pps.rc_range_parameters_11_range_max_qp, _p->pps.rc_range_parameters_11_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[12] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_12_range_min_qp, _p->pps.rc_range_parameters_12_range_max_qp, _p->pps.rc_range_parameters_12_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[13] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_13_range_min_qp, _p->pps.rc_range_parameters_13_range_max_qp, _p->pps.rc_range_parameters_13_range_bpg_offset);
		printk("rc_range_parameters_range min/max/offset[14] : Min[0x%02x] Max[0x%02x] BPG Offset[0x%02x]\n",\
				_p->pps.rc_range_parameters_14_range_min_qp, _p->pps.rc_range_parameters_14_range_max_qp, _p->pps.rc_range_parameters_14_range_bpg_offset);

	} while(0);

	return;

}

static char *__val_to_CsWidthGraphicPositive(UINT32 val)
{
	switch(val)
	{
		case 0:
			return "@@@@@@@@";
		case 1:
			return " @@@@@@@";
		case 2:
			return "  @@@@@@";
		case 3:
			return "   @@@@@";
		case 4:
			return "    @@@@";
		case 5:
			return "     @@@";
		case 6:
			return "      @@";
		case 7:
			return "       @";
		case 8:
			return "        ";
		default :
			return "????????";
	}
}

static char *__val_to_CsWidthGraphicNegative(UINT32 val)
{
	switch(val)
	{
		case 0:
			return "@@@@@@@@";
		case 1:
			return "@@@@@@@ ";
		case 2:
			return "@@@@@@  ";
		case 3:
			return "@@@@@   ";
		case 4:
			return "@@@@    ";
		case 5:
			return "@@@     ";
		case 6:
			return "@@      ";
		case 7:
			return "@       ";
		case 8:
			return "        ";
		default :
			return "????????";
	}
}


static char *__val_to_graphic(UINT32 val)
{
	switch(val)
	{
		case 0:
			return " ";
		case 1:
			return ".";
		case 2:
			return ",";
		case 3:
			return "`";
		case 4:
			return "-";
		case 5:
			return "~";
		case 6:
			return "+";
		case 7:
			return "=";
		case 8:
			return "l";
		case 9:
			return "L";
		case 10:
			return "0";
		case 11:
			return "%";
		case 12:
			return "$";
		case 13:
			return "&";
		case 14:
			return "#";
		case 15:
			return "@";
		default :
			return "?";
	}
}

static char *__val_to_hex(UINT32 val)
{
	switch(val)
	{
		case 0:
			return "0";
		case 1:
			return "1";
		case 2:
			return "2";
		case 3:
			return "3";
		case 4:
			return "4";
		case 5:
			return "5";
		case 6:
			return "6";
		case 7:
			return "7";
		case 8:
			return "8";
		case 9:
			return "9";
		case 10:
			return "A";
		case 11:
			return "B";
		case 12:
			return "C";
		case 13:
			return "D";
		case 14:
			return "E";
		case 15:
			return "F";
		default :
			return "?";
	}
}


char *__tfr_to_str(int type)
{
	/* Based on HDMI2.1a 2022/08/29 latest */
	switch(type)
	{
		case 0:
			{
				return "QMS NOT ACTIVE";
			}
			break;
		case 1:
			{
				return "24Hz/1.001";
			}
			break;
		case 2:
			{
				return "24Hz";
			}
			break;
		case 3:
			{
				return "25Hz";
			}
			break;
		case 4:
			{
				return "30Hz/1.001";
			}
			break;
		case 5:
			{
				return "30Hz";
			}		
			break;
		case 6:
			{
				return "48Hz/1.001";
			}
			break;
		case 7:
			{
				return "48Hz";
			}
			break;
		case 8:
			{
				return "50Hz";
			}
			break;
		case 9:
			{
				return "60Hz/1.001";
			}
			break;
		case 10:
			{
				return "60Hz";
			}
			break;
		case 11:
			{
				return "100Hz";
			}
			break;
		case 12:
			{
				return "120Hz/1.001";
			}
			break;
		case 13:
			{
				return "120Hz";
			}
			break;
		default:	
			{
				return "Reserved";
			}
			break;
	}
	return "ERROR";
}

static char *__csc_to_str(int type)
{
	switch(type)
	{
		case 0:
			{
				return "R444";
			}
			break; 
		case 1:
			{
				return "Y422";
			}
			break; 
		case 2:
			{
				return "Y444";
			}
			break;
		case 3:
			{
				return "Y420";
			}
			break;
		default :
			{
				return "ERROR";
			}
			break;
	}
	return "ERROR";
}



char *__deepcolor_to_str(HDMI21_HAL_VIDEO_DEEPCOLOR_MODE_T type)
{
	switch(type)
	{
		case HDMI21_HAL_VIDEO_DEEPCOLOR_NONE:
			{
				return ".8BIT";
			}
			break; 
		case HDMI21_HAL_VIDEO_DEEPCOLOR_8_BIT:
			{
				return " 8BIT";
			}
			break; 
		case HDMI21_HAL_VIDEO_DEEPCOLOR_10_BIT:
			{
				return "10BIT";
			}
			break;
		case HDMI21_HAL_VIDEO_DEEPCOLOR_12_BIT:
			{
				return "12BIT";
			}
			break;
		case HDMI21_HAL_VIDEO_DEEPCOLOR_16_BIT:
			{
				return "16BIT";
			}
			break;
		default :
			{
				return "  BIT";
			}
			break;
	}
	return "ERROR";
}

static void __HDMI21_HAL_Rx_Get_CheckTopColorSpaceConversion(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 video_format = 0;
	UINT32 value_of_reg14 = 0;
	UINT32 value_of_reg18 = 0;
	UINT32 invalid = 0;

	if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(_p)){
		/* SW Defence code for DVI CSC */
		video_format = 0;
	}
	else{
		video_format = _p->hwVideo.video_format;
	}

	/* Dolby LL should always be treated as RGB 444 format */
	if(_p->isDolbyHDR == HDMI_DOLBY_LL_422_12B){
		video_format = 0;
	}

	/* 2023/08/18 won.hur : BoyeonNim told me to do this */
	if((_p->isDolbyHDR == HDMI_DOLBY_LL_PC) && (_p->hwVideo.video_format == 1) ) {
		video_format = 0;
	}

	/* 2020/06/02 : Won Hur/Dongkyu Choi ->This Should be treated as RGB 444 format on DSC input */
	if(_p->isDSC > 0) {
		video_format = 0;
	}

	/* Read Register */
	value_of_reg14 = _p->top_read(HDMI21_TOP_REG_AD_MAIN_COLOR_COMPONENT_ALIGN);
	value_of_reg18 = _p->top_read(HDMI21_TOP_REG_AD_MAIN_422TO444);
	value_of_reg18 &= 0x0000FFFF;

	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 659){
		HDMI20_DBG("DBG %d : Color Domain 0x14[0x%08x]/0x18[0x%08x]\n", _p->port, value_of_reg14, value_of_reg18);
	}

	if(video_format == 0){ /* RGB 444*/
		if(value_of_reg14 != 0x10006) invalid++;
		if(value_of_reg18 != 0x0) invalid++;
	}
	if(video_format == 1){ /* YUV 422*/
		if(value_of_reg14 != 0x122) invalid++;
		if(value_of_reg18 != 0x1) invalid++;

	}
	else if(video_format == 2){ /*  YUV 444 */
		if(value_of_reg14 != 0x10006) invalid++;
		if(value_of_reg18 != 0x0) invalid++;

	}
	else if(video_format == 3) { /* YUV 420 */
		if(value_of_reg14 != 0x06) invalid++;
		if(value_of_reg18 != 0x0) invalid++;
	}

	if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1244){
		return;
	}

	/* Alarm */
	if(invalid >0){
		HDMI20_WARN("Warning [%d] : Found wrong CSC setting for [%d] domain. Invalid[%d]\n", _p->port, video_format, invalid);
		__HDMI21_HAL_Rx_Set_TopColorSpaceConversion(_p);
	}
}

static void __HDMI21_HAL_Rx_Set_TopColorSpaceConversion(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 video_format = 0;

	if(__HDMI21_HAL_Rx_Get_IsHwInDVIState(_p)){
		/* SW Defence code for DVI CSC */
		video_format = 0;
	}
	else{
		video_format = _p->hwVideo.video_format;
	}

	/* Dolby LL should always be treated as RGB 444 format */
	if(_p->isDolbyHDR == HDMI_DOLBY_LL_422_12B){
		video_format = 0;
	}

	/* 2023/08/18 won.hur : BoyeonNim told me to do this */
	if((_p->isDolbyHDR == HDMI_DOLBY_LL_PC) && (_p->hwVideo.video_format == 1) ) {
		video_format = 0;
	}

	/* 2020/06/02 : Won Hur/Dongkyu Choi ->This Should be treated as RGB 444 format on DSC input */
	if(_p->isDSC > 0) {
		video_format = 0;
	}

	/* Proceed */
	if(video_format == 0){ /* RGB 444*/
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_422TO444, 0x0);
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_COLOR_COMPONENT_ALIGN, 0x10006);
	}
	if(video_format == 1){ /* YUV 422*/
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_422TO444, 0x1);
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_COLOR_COMPONENT_ALIGN, 0x122);
	}
	else if(video_format == 2){ /*  YUV 444 */
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_422TO444, 0x0);
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_COLOR_COMPONENT_ALIGN, 0x10006);
	}
	else if(video_format == 3) { /* YUV 420 */
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_422TO444, 0x0);
		_p->top_write(HDMI21_TOP_REG_AD_MAIN_COLOR_COMPONENT_ALIGN, 0x06);
	}
}


char *__isr_type_to_str(HDMI21_ISR_TYPE_T type)
{
	switch(type)
	{
		/* Main Unit 0 */
		case HDMI21_IRQ_LINK_REGBANK_READY_IRQ:
			return "REGBANK_READY_IRQ";

		case HDMI21_IRQ_LINK_APB_IF_READY_IRQ:
			return "APB_IF_READY_IRQ";

		case HDMI21_IRQ_CDSENSE_CHG_MASK_N:
			return "HDMI21_IRQ_CDSENSE_CHG_MASK_N";

		case HDMI21_IRQ_LINK_TIMER_BASE_LOCKED_IRQ:
			return "TIMER_BASE_LOCKED_IRQ";

		case HDMI21_IRQ_LINK_EARC_BPCLK_OFF_CHG_IRQ:
			return "EARC_BPCLK_OFF_CHG_IRQ";

		case HDMI21_IRQ_LINK_EARC_BPCLK_LOCKED_CHG_IRQ:
			return "EARC_BPCLK_LOCKED_CHG_IRQ";

		case HDMI21_IRQ_LINK_EARC_AUDCLK_OFF_CHG_IRQ:
			return "EARC_AUDCLK_OFF_CHG_IRQ";

		case HDMI21_IRQ_LINK_EARC_AUDCLK_LOCKED_CHG_IRQ:
			return "EARC_AUDCLK_LOCKED_CHG_IRQ";

		case HDMI21_IRQ_LINK_FRLCLK_OFF_CHG_IRQ:
			return "FRLCLK_OFF_CHG_IRQ";

		case HDMI21_IRQ_LINK_FRLCLK_LOCKED_CHG_IRQ:
			return "FRLCLK_LOCKED_CHG_IRQ";

		case HDMI21_IRQ_LINK_TMDSQPCLK_OFF_CHG_IRQ:
			return "TMDSQPCLK_OFF_CHG_IRQ";

		case HDMI21_IRQ_LINK_TMDSQPCLK_LOCKED_CHG_IRQ:
			return "TMDSQPCLK_LOCKED_CHG_IRQ";

		case HDMI21_IRQ_LINK_AUDCLK_OFF_CHG_IRQ:
			return "AUDCLK_OFF_CHG_IRQ";

		case HDMI21_IRQ_LINK_AUDCLK_LOCKED_CHG_IRQ:
			return "AUDCLK_LOCKED_CHG_IRQ";

			/* Main Unit 1 */
		case HDMI21_IRQ_LINK_DDC_SCDC_ACTIVITY_IRQ:
			return "DDC_SCDC_ACTIVITY_IRQ";

		case HDMI21_IRQ_LINK_DDC_HDCP_ACTIVITY_IRQ:
			return "DDC_HDCP_ACTIVITY_IRQ";

		case HDMI21_IRQ_LINK_EARCTX_POWERED_DOWN_IRQ:
			return "EARCTX_POWERED_DOWN_IRQ";

		case HDMI21_IRQ_LINK_EARCTX_POWERED_UP_IRQ:
			return "EARCTX_POWERED_UP_IRQ";

		case HDMI21_IRQ_LINK_CEC_POWERED_DOWN_IRQ:
			return "CEC_POWERED_DOWN_IRQ";

		case HDMI21_IRQ_LINK_CEC_POWERED_UP_IRQ:
			return "CEC_POWERED_UP_IRQ";

		case HDMI21_IRQ_LINK_AVPUNIT_POWERED_DOWN_IRQ:
			return "AVPUNIT_POWERED_DOWN_IRQ";

		case HDMI21_IRQ_LINK_AVPUNIT_POWERED_UP_IRQ:
			return "AVPUNIT_POWERED_UP_IRQ";

			/* Main Unit 2 */
		case HDMI21_IRQ_LINK_PHYCREG_CR_TIMEOUT_IRQ:
			return "PHYCREG_CR_TIMEOUT_IRQ";

		case HDMI21_IRQ_LINK_PHYCREG_CR_READ_DONE_IRQ:
			return "PHYCREG_CR_READ_DONE_IRQ";

		case HDMI21_IRQ_LINK_PHYCREG_CR_WRITE_DONE_IRQ:
			return "PHYCREG_CR_WRITE_DONE_IRQ";

		case HDMI21_IRQ_LINK_PHYCREG_CR_SELECTOR_DONE_IRQ:
			return "PHYCREG_CR_SELECTOR_DONE_IRQ";

		case HDMI21_IRQ_LINK_PHYCREG_CR_SELECTIONMODE_DONE_IRQ:
			return "PHYCREG_CR_SELECTIONMODE_DONE_IRQ";

		case HDMI21_IRQ_LINK_EARC_BPCLK_VALID_STABLE_CHG_IRQ:
			return "EARC_BPCLK_VALID_STABLE_CHG_IRQ";

		case HDMI21_IRQ_LINK_TMDSVALID_STABLE_CHG_IRQ:
			return "TMDSVALID_STABLE_CHG_IRQ";

		case HDMI21_IRQ_LINK_AUDPLL_LOCK_STABLE_CHG_IRQ:
			return "AUDPLL_LOCK_STABLE_CHG_IRQ";

			/* AVP Unit 0 */
		case HDMI21_IRQ_LINK_CED_DYN_CNT_CH2_IRQ:
			return "CED_DYN_CNT_CH2_IRQ";

		case HDMI21_IRQ_LINK_CED_DYN_CNT_CH1_IRQ:
			return "CED_DYN_CNT_CH1_IRQ";

		case HDMI21_IRQ_LINK_CED_DYN_CNT_CH0_IRQ:
			return "CED_DYN_CNT_CH0_IRQ";

		case HDMI21_IRQ_LINK_DESCRAND_SYNC_SEQ_ERR_IRQ:
			return "DESCRAND_SYNC_SEQ_ERR_IRQ";

		case HDMI21_IRQ_LINK_DESCRAND_SYNC_IRQ:
			return "DESCRAND_SYNC_IRQ";

			/* AVP Unit 1 */
		case HDMI21_IRQ_LINK_VMON_VMEAS_IRQ:
			return "VMON_VMEAS_IRQ";

		case HDMI21_IRQ_LINK_VMON_HMEAS_IRQ:
			return "VMON_HMEAS_IRQ";

		case HDMI21_IRQ_LINK_AUD_CHSTATUS_SP3_IRQ:
			return "AUD_CHSTATUS_SP3_IRQ";

		case HDMI21_IRQ_LINK_AUD_CHSTATUS_SP2_IRQ:
			return "AUD_CHSTATUS_SP2_IRQ";

		case HDMI21_IRQ_LINK_AUD_CHSTATUS_SP1_IRQ:
			return "AUD_CHSTATUS_SP1_IRQ";

		case HDMI21_IRQ_LINK_AUD_CHSTATUS_SP0_IRQ:
			return "AUD_CHSTATUS_SP0_IRQ";

		case HDMI21_IRQ_LINK_AUD_MUTE_IRQ	:
			return "AUD_MUTE_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_UNDERFLOW_IRQ:
			return "AFIFO_UNDERFLOW_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_OVERFLOW_IRQ:
			return "AFIFO_OVERFLOW_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_THR_MUTE_LOW_IRQ:
			return "AFIFO_THR_MUTE_LOW_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_THR_MUTE_HIGH_IRQ:
			return "AFIFO_THR_MUTE_HIGH_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_THR_LOW_IRQ:
			return "AFIFO_THR_LOW_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_THR_HIGH_IRQ:
			return "AFIFO_THR_HIGH_IRQ";

		case HDMI21_IRQ_LINK_AFIFO_THR_PASS_IRQ:
			return "AFIFO_THR_PASS_IRQ";

		case HDMI21_IRQ_LINK_AUD_FMT_CHG_IRQ:
			return "AUD_FMT_CHG_IRQ";

		case HDMI21_IRQ_LINK_VPROC_SYNCGEN_IRQ:
			return "VPROC_SYNCGEN_IRQ";

		case HDMI21_IRQ_LINK_VPROC_PP_DIFF_IRQ:
			return "VPROC_PP_DIFF_IRQ";

		case HDMI21_IRQ_LINK_VPROC_CD_TIMEOUT_IRQ:
			return "VPROC_CD_TIMEOUT_IRQ";

		case HDMI21_IRQ_LINK_VPROC_CD_CHG_IRQ:
			return "VPROC_CD_CHG_IRQ";

		case HDMI21_IRQ_LINK_VSTREAM_FIFO_OVERFLOW_IRQ:
			return "VSTREAM_FIFO_OVERFLOW_IRQ";

		case HDMI21_IRQ_LINK_VSTREAM_FIFO_UNDERFLOW_IRQ:
			return "VSTREAM_FIFO_UNDERFLOW_IRQ";

		case HDMI21_IRQ_LINK_VSTREAM_FIFO_ALMOST_FULL_IRQ:
			return "VSTREAM_FIFO_ALMOST_FULL_IRQ";
		
		case HDMI21_IRQ_LINK_VSTREAM_FIFO_ALMOST_EMPTY_IRQ:
			return "VSTREAM_FIFO_ALMOST_EMPTY_IRQ";

		case HDMI21_IRQ_LINK_DEFRAMER_DVIHDMI_CHG_IRQ:
			return "DEFRAMER_DVIHDMI_CHG_IRQ";

		case HDMI21_IRQ_LINK_DEFRAMER_GBDET_ERR_IRQ:
			return "DEFRAMER_GBDET_ERR_IRQ";

		case HDMI21_IRQ_LINK_DEFRAMER_VSYNC_THR_REACHED_IRQ:
			return "DEFRAMER_VSYNC_THR_REACHED_IRQ";

		case HDMI21_IRQ_LINK_DEFRAMER_VSYNC_IRQ:
			return "DEFRAMER_VSYNC_IRQ";

			/* AVP Unit 2 */
		case HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE3_IRQ:
			return "FRL_CED_DYN_ERRCNT_THR_LANE3_IRQ";

		case HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE2_IRQ:
			return "FRL_CED_DYN_ERRCNT_THR_LANE2_IRQ";

		case HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE1_IRQ:
			return "FRL_CED_DYN_ERRCNT_THR_LANE1_IRQ";

		case HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE0_IRQ:
			return "FRL_CED_DYN_ERRCNT_THR_LANE0_IRQ";

		case HDMI21_IRQ_LINK_UNPACKER_TYPE_ERR_CNT_IRQ:
			return "UNPACKER_TYPE_ERR_CNT_IRQ";

		case HDMI21_IRQ_LINK_UNPACKER_LENGTH_ERR_CNT_IRQ:
			return "UNPACKER_LENGTH_ERR_CNT_IRQ";

		case HDMI21_IRQ_LINK_UNPACKER_FIFO_UNDERFLOW_IRQ:
			return "UNPACKER_FIFO_UNDERFLOW_IRQ";

		case HDMI21_IRQ_LINK_UNPACKER_FIFO_OVERFLOW_IRQ:
			return "UNPACKER_FIFO_OVERFLOW_IRQ";

		case HDMI21_IRQ_LINK_FRL_DESCRAMB_SYNC_IRQ:
			return "FRL_DESCRAMB_SYNC_IRQ";

		case HDMI21_IRQ_LINK_MARKER_SB_SIZE_IRQ:
			return "MARKER_SB_SIZE_IRQ";

		case HDMI21_IRQ_LINK_MARKER_SB_COUNT_IRQ:
			return "MARKER_SB_COUNT_IRQ";

			/* PKT Unit 0 */
		case HDMI21_IRQ_LINK_PKTDEC_VTEM_CHG_IRQ:
			return "PKTDEC_VTEM_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_CVTEM_CHG_IRQ:
			return "PKTDEC_CVTEM_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_EMD_CHG_IRQ:
			return "PKTDEC_EMD_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GENPKT1_CHG_IRQ:
			return "PKTDEC_GENPKT1_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GENPKT0_CHG_IRQ:
			return "PKTDEC_GENPKT0_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_DRMIF_CHG_IRQ:
			return "PKTDEC_DRMIF_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_NTSCVBIIF_CHG_IRQ:
			return "PKTDEC_NTSCVBIIF_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_AUDIF_CHG_IRQ:
			return "PKTDEC_AUDIF_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_SRCPDIF_CHG_IRQ:
			return "PKTDEC_SRCPDIF_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_AVIIF_CHG_IRQ:
			return "PKTDEC_AVIIF_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_VSIF_CHG_IRQ:
			return "PKTDEC_VSIF_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_AMD_CHG_IRQ:
			return "PKTDEC_AMD_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GMD_CHG_IRQ:
			return "PKTDEC_GMD_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ISRC2_CHG_IRQ:
			return "PKTDEC_ISRC2_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ISRC1_CHG_IRQ:
			return "PKTDEC_ISRC1_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACP_CHG_IRQ:
			return "PKTDEC_ACP_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GCP_CHG_IRQ:
			return "PKTDEC_GCP_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACR_CHG_IRQ:
			return "PKTDEC_ACR_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACP_TIMEOUT_IRQ:
			return "PKTDEC_ACP_TIMEOUT_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACR_N_CHG_IRQ:
			return "PKTDEC_ACR_N_CHG_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACR_CTS_CHG_IRQ:
			return "PKTDEC_ACR_CTS_CHG_IRQ";

			/* PKT Unit 1 */
		case HDMI21_IRQ_LINK_PKTFIFO_NEW_ENTRY_IRQ:
			return "PKTFIFO_NEW_ENTRY_IRQ";

		case HDMI21_IRQ_LINK_PKTFIFO_OVERFLOW_IRQ:
			return "PKTFIFO_OVERFLOW_IRQ";

		case HDMI21_IRQ_LINK_PKTFIFO_UNDERFLOW_IRQ:
			return "PKTFIFO_UNDERFLOW_IRQ";

		case HDMI21_IRQ_LINK_PKTFIFO_THR_HIGH_IRQ:
			return "PKTFIFO_THR_HIGH_IRQ";

		case HDMI21_IRQ_LINK_PKTFIFO_THR_PASS_IRQ:
			return "PKTFIFO_THR_PASS_IRQ";

		case HDMI21_IRQ_LINK_PKTFIFO_THR_LOW_IRQ:
			return "PKTFIFO_THR_LOW_IRQ";

			/* PKT Unit 2 */
		case HDMI21_IRQ_LINK_PKTDEC_VTEM_RCV_IRQ:
			return "PKTDEC_VTEM_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_CVTEM_RCV_IRQ:
			return "PKTDEC_CVTEM_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_EMD_RCV_IRQ:
			return "PKTDEC_EMD_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GENPKT1_RCV_IRQ:
			return "PKTDEC_GENPKT1_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GENPKT0_RCV_IRQ:
			return "PKTDEC_GENPKT0_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_DRMIF_RCV_IRQ:
			return "PKTDEC_DRMIF_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_NTSCVBIIF_RCV_IRQ:
			return "PKTDEC_NTSCVBIIF_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_AUDIF_RCV_IRQ:
			return "PKTDEC_AUDIF_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_SRCPDIF_RCV_IRQ:
			return "PKTDEC_SRCPDIF_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_AVIIF_RCV_IRQ:
			return "PKTDEC_AVIIF_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_VSIF_RCV_IRQ:
			return "PKTDEC_VSIF_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_AMD_RCV_IRQ:
			return "PKTDEC_AMD_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GMD_RCV_IRQ:
			return "PKTDEC_GMD_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ISRC2_RCV_IRQ:
			return "PKTDEC_ISRC2_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ISRC1_RCV_IRQ:
			return "PKTDEC_ISRC1_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACP_RCV_IRQ:
			return "PKTDEC_ACP_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_GCP_RCV_IRQ:
			return "PKTDEC_GCP_RCV_IRQ";

		case HDMI21_IRQ_LINK_PKTDEC_ACR_RCV_IRQ:
			return "PKTDEC_ACR_RCV_IRQ";
			
			/* SCDC Unit */
		case HDMI21_IRQ_LINK_FRL_START_TIMEOUT_IRQ:
			return "FRL_START_TIMEOUT_IRQ";

		case HDMI21_IRQ_LINK_SCDCTMDSCCFG_CHG_IRQ:
			return "SCDCTMDSCCFG_CHG_IRQ";

		case HDMI21_IRQ_LINK_SCDCSCSTATUS_CHG_IRQ:
			return "SCDCSCSTATUS_CHG_IRQ";

		case HDMI21_IRQ_LINK_SCDCCFG_CHG_IRQ:
			return "SCDCCFG_CHG_IRQ";

			/* HDCP Unit */
		case HDMI21_IRQ_LINK_HDCP2_DECRYPTED_CHG_IRQ:
			return "HDCP2_DECRYPTED_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_AUTHENTICATION_FAIL_IRQ:
			return "HDCP2_AUTHENTICATION_FAIL_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_AUTHENTICATED_IRQ:
			return "HDCP2_AUTHENTICATED_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_AUTHENTICATION_LOST_IRQ:
			return "HDCP2_AUTHENTICATION_LOST_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_NOT_CAPABLE_IRQ:
			return "HDCP2_NOT_CAPABLE_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_CAPABLE_IRQ:
			return "HDCP2_CAPABLE_IRQ";

		case HDMI21_IRQ_LINK_HDCP_DKSET_DONE_IRQ:
			return "HDCP_DKSET_DONE_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_OESS_EESS_CHG_IRQ:
			return "HDCP14_OESS_EESS_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_ENCDIS_IRQ:
			return "HDCP14_ENCDIS_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_ENCEN_IRQ:
			return "HDCP14_ENCEN_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_AUTH_IRQ:
			return "HDCP14_AUTH_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_BSTATUS_READ_IRQ:
			return "HDCP14_BSTATUS_READ_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_BCAPS_READ_IRQ:
			return "HDCP14_BCAPS_READ_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_RI_READ_IRQ:
			return "HDCP14_RI_READ_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_BKSV_READ_IRQ:
			return "HDCP14_BKSV_READ_IRQ";

		case HDMI21_IRQ_LINK_HDCP14_AKSV_RCV_IRQ:
			return "HDCP14_AKSV_RCV_IRQ";

			/* HDCP 1 Unit */
		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_15_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_15_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_14_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_14_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_13_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_13_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_12_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_12_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_11_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_11_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_10_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_10_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_9_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_9_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_8_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_8_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_7_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_7_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_6_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_6_CHG_IRQ";

		case HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_5_CHG_IRQ:
			return "HDCP2_ESM_P0_GPIO_OUT_5_CHG_IRQ";

		case HDMI21_ISR_LINK_UNKNOWN:
			return "HDMI21_ISR_LINK_UNKNOWN";

		case HDMI21_ISR_TOPLINK_SCDC_FRL_RATE_RCV:
			return "HDMI21_ISR_TOPLINK_SCDC_FRL_RATE_RCV";

		case HDMI21_ISR_TOPLINK_SCDC_FRL_RATE_SAME:
			return "HDMI21_ISR_TOPLINK_SCDC_FRL_RATE_SAME";

		case HDMI21_ISR_TOPLINK_SCDC_SCRAMBLE_RCV:
			return "HDMI21_ISR_TOPLINK_SCDC_SCRAMBLE_RCV";

		case HDMI21_ISR_TOPLINK_SCDC_FRL_START_UP:
			return "HDMI21_ISR_TOPLINK_SCDC_FRL_START_UP";

		case HDMI21_ISR_TOPLINK_SCDC_FRL_START_DN:
			return "HDMI21_ISR_TOPLINK_SCDC_FRL_START_DN";

		case HDMI21_ISR_TOPLINK_SCDC_FRL_UPDATE_UP:
			return "HDMI21_ISR_TOPLINK_SCDC_FRL_UPDATE_UP";

		case HDMI21_ISR_TOPLINK_SCDC_FRL_UPDATE_DN:
			return "HDMI21_ISR_TOPLINK_SCDC_FRL_UPDATE_DN";

			/* LG HDMI Top */
		case HDMI21_ISR_TOP_5V_UP:
			return "HDMI21_ISR_TOP_5V_UP";

		case HDMI21_ISR_TOP_5V_DOWN:
			return "HDMI21_ISR_TOP_5V_DOWN";

		case HDMI21_ISR_TOP_PC:
			return "HDMI21_ISR_TOP_PC";

		case HDMI21_ISR_TOP_PD:
			return "HDMI21_ISR_TOP_PD";

		case HDMI21_ISR_TOP_CHSTS_EN:
			return "HDMI21_ISR_TOP_CHSTS_EN";

		case HDMI21_ISR_TOP_EARCTX_CMDC_XACT_DONE_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_XACT_DONE_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADPAR_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADPAR_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADECC_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADECC_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_INCOMPLETE_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_INCOMPLETE_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADSYNC_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADSYNC_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADPREAMBLE_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADPREAMBLE_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_CAP_CHNG_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_CAP_CHNG_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_STAT_CHNG_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_STAT_CHNG_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_LOST_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_LOST_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_DISCOVERY_TIMEOUT_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_DISCOVERY_TIMEOUT_IRQ";

		case HDMI21_ISR_TOP_EARCTX_CMDC_DISCOVERY_DONE_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_CMDC_DISCOVERY_DONE_IRQ";

		case HDMI21_ISR_TOP_EARCTX_DMAC_MUTE_REQUEST_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_DMAC_MUTE_REQUEST_IRQ";

		case HDMI21_ISR_TOP_EARCTX_DMAC_AUDIO_FIFO_OVERFLOW_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_DMAC_AUDIO_FIFO_OVERFLOW_IRQ";

		case HDMI21_ISR_TOP_EARCTX_DMAC_AUDIO_FIFO_UNDERFLOW_IRQ:
			return "HDMI21_ISR_TOP_EARCTX_DMAC_AUDIO_FIFO_UNDERFLOW_IRQ";
		
		case HDMI21_ISR_TOP_DDCMON_DDC1_IRQ:
			return "HDMI21_ISR_TOP_DDCMON_DDC1_IRQ";
		
		case HDMI21_ISR_TOP_DDCMON_DDC2_IRQ:
			return "HDMI21_ISR_TOP_DDCMON_DDC2_IRQ";
		
		case HDMI21_ISR_TOP_DDCMON_DDC3_IRQ:
			return "HDMI21_ISR_TOP_DDCMON_DDC3_IRQ";
		
		case HDMI21_ISR_TOP_DDCMON_DDC4_IRQ:
			return "HDMI21_ISR_TOP_DDCMON_DDC4_IRQ";
		
		case HDMI21_ISR_TOP_UNKNOWN:
			return "HDMI21_ISR_TOP_UNKNOWN";

		default :
			return "Unknown";
	} 
}

static char *phymode_type_to_str(HDMI21_HAL_PHY_INITIATED_MODE_T type)
{
	switch (type)
	{
		case HDMI21_HAL_PHY_INITIATED_ERROR:
		case HDMI21_HAL_PHY_INITIATED_3G:
			return "3G";
		case HDMI21_HAL_PHY_INITIATED_6G:
			return "6G";
		case HDMI21_HAL_PHY_INITIATED_FRL_3G_3L:
			return "FRL 3G 3L(R1)";
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_3L:
			return "FRL 6G 3L(R2)";
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_4L:
			return "FRL 6G 4L(R3)";
		case HDMI21_HAL_PHY_INITIATED_FRL_8G_4L:
			return "FRL 8G 4L(R4)";
		case HDMI21_HAL_PHY_INITIATED_FRL_10G_4L:
			return "FRL 10G 4L(R5)";
		case HDMI21_HAL_PHY_INITIATED_FRL_12G_4L:
			return "FRL 12G 4L(R6)";
		default :
				return "Unknown";
	}
}



static void __HDMI21_HAL_Rx_DBG_CalculateOffsetRepeat(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_PHY_DBG_OFFSET_DATA_T *pVal)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	
	UINT32 __reg  = 0; 
	UINT32 __data = 0;


	if(gHdmi21OffsetRepeatState[_p->port] == 0) {
		__reg = 0x47; __reg = __reg << 2; __data = 0x0; _p->phyPDC_write(__reg, __data);
		gHdmi21OffsetRepeatState[_p->port]++;
	}
	else if(gHdmi21OffsetRepeatState[_p->port] == 1) {
		__reg = 0x47; __reg = __reg << 2; __data = 0x1; _p->phyPDC_write(__reg, __data);
		gHdmi21OffsetRepeatState[_p->port]++;
	}
	else if(gHdmi21OffsetRepeatState[_p->port] == 2) {
		/* Memset */
		memset((void *)pVal, 0, sizeof(HDMI21_PHY_DBG_OFFSET_DATA_T));

		__reg = 0xF0; __reg = __reg << 2; __data = _p->phyDR_read(__reg);

		if(lx_chip() == LX_CHIP_M23) {
			__data |= 0x8; /* M23 has only CH0~2 */
		}

		if((__data & 0x0F) == 0xF) {
			/* Set to Ch 0 */
			__reg = 0xD9; __reg = __reg << 2; __data = 0;  _p->phyDR_write(__reg, __data);
		
			/* Read offset value */
			__reg = 0xC8; __reg = __reg << 2; pVal->se_os_ch0  = _p->phyDR_read(__reg);
			__reg = 0xC9; __reg = __reg << 2; pVal->so_os_ch0  = _p->phyDR_read(__reg);
			__reg = 0xCA; __reg = __reg << 2; pVal->te_os_ch0  = _p->phyDR_read(__reg);
			__reg = 0xCB; __reg = __reg << 2; pVal->to_os_ch0  = _p->phyDR_read(__reg);
			__reg = 0xCC; __reg = __reg << 2; pVal->dep_os_ch0 = _p->phyDR_read(__reg);
			__reg = 0xCD; __reg = __reg << 2; pVal->den_os_ch0 = _p->phyDR_read(__reg);
			__reg = 0xCE; __reg = __reg << 2; pVal->dop_os_ch0 = _p->phyDR_read(__reg);
			__reg = 0xCF; __reg = __reg << 2; pVal->don_os_ch0 = _p->phyDR_read(__reg);
			__reg = 0xD0; __reg = __reg << 2; pVal->eq_os_ch0  = _p->phyDR_read(__reg);

			/* Set to Ch 1 */
			__reg = 0xD9; __reg = __reg << 2; __data = 1;  _p->phyDR_write(__reg, __data);
		
			/* Read offset value */
			__reg = 0xC8; __reg = __reg << 2; pVal->se_os_ch1  = _p->phyDR_read(__reg);
			__reg = 0xC9; __reg = __reg << 2; pVal->so_os_ch1  = _p->phyDR_read(__reg);
			__reg = 0xCA; __reg = __reg << 2; pVal->te_os_ch1  = _p->phyDR_read(__reg);
			__reg = 0xCB; __reg = __reg << 2; pVal->to_os_ch1  = _p->phyDR_read(__reg);
			__reg = 0xCC; __reg = __reg << 2; pVal->dep_os_ch1 = _p->phyDR_read(__reg);
			__reg = 0xCD; __reg = __reg << 2; pVal->den_os_ch1 = _p->phyDR_read(__reg);
			__reg = 0xCE; __reg = __reg << 2; pVal->dop_os_ch1 = _p->phyDR_read(__reg);
			__reg = 0xCF; __reg = __reg << 2; pVal->don_os_ch1 = _p->phyDR_read(__reg);
			__reg = 0xD0; __reg = __reg << 2; pVal->eq_os_ch1  = _p->phyDR_read(__reg);

			/* Set to Ch 0 */
			__reg = 0xD9; __reg = __reg << 2; __data = 2;  _p->phyDR_write(__reg, __data);
		
			/* Read offset value */
			__reg = 0xC8; __reg = __reg << 2; pVal->se_os_ch2  = _p->phyDR_read(__reg);
			__reg = 0xC9; __reg = __reg << 2; pVal->so_os_ch2  = _p->phyDR_read(__reg);
			__reg = 0xCA; __reg = __reg << 2; pVal->te_os_ch2  = _p->phyDR_read(__reg);
			__reg = 0xCB; __reg = __reg << 2; pVal->to_os_ch2  = _p->phyDR_read(__reg);
			__reg = 0xCC; __reg = __reg << 2; pVal->dep_os_ch2 = _p->phyDR_read(__reg);
			__reg = 0xCD; __reg = __reg << 2; pVal->den_os_ch2 = _p->phyDR_read(__reg);
			__reg = 0xCE; __reg = __reg << 2; pVal->dop_os_ch2 = _p->phyDR_read(__reg);
			__reg = 0xCF; __reg = __reg << 2; pVal->don_os_ch2 = _p->phyDR_read(__reg);
			__reg = 0xD0; __reg = __reg << 2; pVal->eq_os_ch2  = _p->phyDR_read(__reg);


			/* Set to Ch 0 */
			__reg = 0xD9; __reg = __reg << 2; __data = 3;  _p->phyDR_write(__reg, __data);
		
			/* Read offset value */
			__reg = 0xC8; __reg = __reg << 2; pVal->se_os_ch3  = _p->phyDR_read(__reg);
			__reg = 0xC9; __reg = __reg << 2; pVal->so_os_ch3  = _p->phyDR_read(__reg);
			__reg = 0xCA; __reg = __reg << 2; pVal->te_os_ch3  = _p->phyDR_read(__reg);
			__reg = 0xCB; __reg = __reg << 2; pVal->to_os_ch3  = _p->phyDR_read(__reg);
			__reg = 0xCC; __reg = __reg << 2; pVal->dep_os_ch3 = _p->phyDR_read(__reg);
			__reg = 0xCD; __reg = __reg << 2; pVal->den_os_ch3 = _p->phyDR_read(__reg);
			__reg = 0xCE; __reg = __reg << 2; pVal->dop_os_ch3 = _p->phyDR_read(__reg);
			__reg = 0xCF; __reg = __reg << 2; pVal->don_os_ch3 = _p->phyDR_read(__reg);
			__reg = 0xD0; __reg = __reg << 2; pVal->eq_os_ch3  = _p->phyDR_read(__reg);

			gHdmi21OffsetRepeatState[_p->port]++;
		}
	}
	else if(gHdmi21OffsetRepeatState[_p->port] == 3) {
		gHdmi21OffsetRepeatState[_p->port] = 0;
		gHdmi21OffsetRepeatTest[_p->port]++;
	}
	
	return;
}

static int __HDMI21_HAL_Rx_Set_IdleTick(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int is5vHigh)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int __isIdle = 0;
	int ret = 0;

	/* E60 */
	UINT32 __fsSyncDetected = (HDMI21_TOP_FIELD_AD_FS_MON_1_DE_CNT_VALID | HDMI21_TOP_FIELD_AD_FS_MON_1_DE_LEN_VALID \
			| HDMI21_TOP_FIELD_AD_FS_MON_1_VSYNC_VALID | HDMI21_TOP_FIELD_AD_FS_MON_1_HSYNC_VALID);


	if(lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
		/* O22 */
		do{
			/* When 5V is low.. it is not idle mode */
			if(is5vHigh <= 0) {
				ret = -1;
				break;
			}

			/* If this port is being displayed, it is not idle mode */
			if( HDMI21_HAL_Rx_Get_IsV4l2PortActivated(_p->port) ) {
				ret = -2;
				break;
			}

			/* If no PHY lock(TCS Done), it is not idle mode */
			if(_p->isPhyLocked == 0) {
				ret = -3;
				_p->isForceRestore = TRUE;
				break;
			}

			/* If signal is not stable, it is not idle mode */
			if(_p->lowPowerMode <= HDMI21_HAL_POWER_NORMAL) {
				if(_p->stable_cnt <= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value){
					ret = -4;
					break;
				}

				/* Check Timing */
				if(__HDMI21_HAL_Rx_Get_IsStableTimingInfoEmpty(_p) > 0) {
					ret = -5;
					break;
				}
			}

			if(_p->isDSC > 0) {
				ret = -6;
				break;
			}

			if( (gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23].value == 0) && ( HDMI21_HAL_Rx_Get_HDCPStatus(_p->port) >= 20)) {
				ret = -7;
				break;
			}

			/* 2020/07/24 : Do not enter on VRR modes */
			if(_p->isFreeSyncMode > 0) {
				ret = -8;
				break;
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value != 0) {
				if(_p->lowPowerMode < HDMI21_HAL_POWER_LOWPOWER) {
					if(_p->lowPowerAccumCnt >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value) {
						ret = -9;
						break;
					}
				}
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT].value > 0 ) {
				if(gHdmi21InputChgCnt > 0) {
					ret = -10;
					break;
				}
			}

			/* If you come this far.. u are stable enough */
			__isIdle = 1;

		} while(0);
	}
	else {
		/* E60 */
		do {
			/* When 5V is low.. it is not idle mode */
			if(is5vHigh <= 0) {
				ret = -1;
				break;
			}

			/* If this port is being displayed, it is not idle mode */
			if( HDMI21_HAL_Rx_Get_IsV4l2PortActivated(_p->port) ) {
				ret = -2;
				break;
			}

			/* If no PHY lock(TCS Done), it is not idle mode */
			if(_p->isPhyLocked == 0) {
				ret = -3;
				break;
			}

			/* Will only consider TMDS modes */
			if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				ret = -4;
				break;
			}

			/* If signal is not stable, it is not idle mode */
			if(_p->lowPowerMode <= HDMI21_HAL_POWER_NORMAL) {
				if(_p->stable_cnt <= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value){
					ret = -5;
					break;
				}

				/* Check Timing */
				if(__HDMI21_HAL_Rx_Get_IsStableTimingInfoEmpty(_p) > 0) {
					ret = -6;
					break;
				}
			}

			/* Check if Low Power Module detected safe sync */
			if( (_p->top_read(HDMI21_TOP_REG_AD_FS_MONITOR_1) & 0xF) != __fsSyncDetected) {
				HDMI21_LINE_DBG(11910, "DBG[%d] : FS monitor thinks its not safe[0x%x]\n", _p->port, _p->top_read(HDMI21_TOP_REG_AD_FS_MONITOR_1));
				ret = -7;
				break;
			}

			if( (gHDMI21RxDevVideoControler[HDMI21__VIDEO_ENABLE_LOWPOWER_FOR_HDCP23].value == 0) && ( HDMI21_HAL_Rx_Get_HDCPStatus(_p->port) >= 20)) {
				ret = -8;
				break;
			}

			/* 2020/07/21 : Do Not Enter if SCDC CH Lock is not valid */
			if(_p->lowPowerMode < HDMI21_HAL_POWER_LOWPOWER) {
				if((_p->link_read(0x594) & 0xF) != 0xF) {
					ret = -9;
					break;
				}
			}

			if( (_p->top_read(HDMI21_TOP_REG_AD_FS_MONITOR_4) & 0xFFFF0000) != 0) {
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, 0x800);
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, 0);
				ret = -10;
				break;
			}

			if(_p->top_read(HDMI21_TOP_REG_AD_FS_MONITOR_5) != 0)  {
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, 0x800);
				_p->top_write(HDMI21_TOP_REG_AD_FS_1, 0);
				ret = -11;
				break;
			}

			/* 2020/07/24 : Do not enter on VRR modes */
			if(_p->isFreeSyncMode > 0) {
				ret = -12;
				break;
			}

			if(_p->hwVideo.deep_color_mode >= 5) {
				ret = -13;
				break;
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value != 0) {
				if(_p->lowPowerMode < HDMI21_HAL_POWER_LOWPOWER) {
					if(_p->lowPowerAccumCnt >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_CNT].value) {
						ret = -14;
						break;
					}
				}
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LIMIT_ALLPORT].value > 0 ) {
				if(gHdmi21InputChgCnt > 0) {
					ret = -15;
					break;
				}
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LOWEST_TMDSCLK].value > 0) {
				if(_p->real_tmds_clk <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_LOWEST_TMDSCLK].value) {
					ret = -16;
					break;
				}
			}

			__isIdle = 1;
		} while(0);
	}

	/* Update Handler */
	if(__isIdle > 0) { 
		if(_p->idleTick <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value) 
		{
			_p->idleTick++; 
		} 
	}
	else {
		_p->idleTick = 0; 
	}

	return ret;
}

static void  __HDMI21_HAL_Rx_Set_LowPowerSettingStep0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;
	UINT32 __reg  = 0;

	if(isLowPower) {
		/* Set to Low Power Mode */

		HDMI20_INFO("INFO[%d] : LowPower Mode Step #0 has been set\n", _p->port);

		/* 2020/07/29 : Increase LowPower Accum Cnt */
		_p->lowPowerAccumCnt++;

		/* 2025/03/25 won.hur : Checked that 48:0xa, 28:0x10 is identical among O26 and O24 */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			/* Step 1 */
			//_p->top_write(0x32c,  gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value );
			/* ?? */
			if ( lx_chip_rev( ) == LX_CHIP_REV( O24, A0) ){
				HDMI21_REG_WR(0xC8D0E834, 0x9fa21510);
			}

			_p->top_write(0x33C, 0x640f10);
			_p->top_write(0x328, 0x80000);
			_p->top_write(0x32C, 0x1014000);

			__reg = 0xa; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x40);	// 0x48
			__reg = 0x10; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x0);				// 0x28

			if(_p->phyInitiatedMode > HDMI21_HAL_PHY_INITIATED_6G) { /* FRL Modes */
				_p->top_write(0x330, 0xFFFF);
			}else{	 /* TMDS Modes */
				_p->top_write(0x330, 0x0F0F);
			}

		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			/* Step 1 */
			_p->top_write(0x32c,  gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value );
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			/* Step 1 */
			_p->top_write(0x32c,  gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value );
			
			/* Step 2*/
			_p->top_write(0x328, 0x80000);
			HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to 0x0 from 0x80000\n", _p->port);
			_p->top_write(0x328, 0x0);
		}
		else {

			/* Fake DE/VSYNC/HSYNC set to ON */
			__data = (HDMI21_TOP_FIELD_AD_FS_1_BLOCK_SYNC_DE | HDMI21_TOP_FIELD_AD_FS_1_BLOCK_SYNC_VSYNC | HDMI21_TOP_FIELD_AD_FS_1_BLOCK_SYNC_HSYNC);
			_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);
			HDMI21_LINE_DBG(12001, "INFO[%d] : Fake DE/VSYNC/HSYNC ON! R314<=[0x%08x]\n", _p->port, _p->top_read(HDMI21_TOP_REG_AD_FS_1));

		}
		_p->lowPowerMode = HDMI21_HAL_POWER_LOWPOWER;
	}
	else {
		/* Set to Normal Mode */
		HDMI20_INFO("INFO[%d] : Restore to Normal Power Mode(Step 0)\n", _p->port);
		/* 2025/03/25 won.hur : 28:0x11 and 48:0x2 is identical among O24 and O26 */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x0);			// 0x28
			__reg = 0x2; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x0);	// 0x48
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			if(_p->is5Vconnected > 0){
				/* EQ ON */
				__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x0);
				HDMI20_INFO("INFO[%d] : EQ is ON\n", _p->port);

				/* DR ON */
				__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x0);
				HDMI20_INFO("INFO[%d] : DR is ON\n", _p->port);

				__reg = 0x06; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xD3);
				__reg = 0x06; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x53);
			}
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if(_p->is5Vconnected > 0){
				if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_PHY_DBG].value & 0x1) != 0x0) {
					/* Do Nothing */
					HDMI20_INFO("INFO[%d] : Set DBG Mode. Discard PHY OFF for Low Power\n", _p->port);
				}
				else {
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */

						/* EQ ON */
						__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x0);
						HDMI20_INFO("INFO[%d] : EQ is ON\n", _p->port);

						/* DR ON */
						__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x0);
						HDMI20_INFO("INFO[%d] : DR is ON\n", _p->port);

						__reg = 0x06; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xD3);
						__reg = 0x06; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x53);

						

						//if(  HDMI21_HAL_Rx_Get_HDCPStatus(_p->port) >= 20) {
						if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 11018) {
							if((HDMI21_HAL_Rx_Get_HDCPStatus(_p->port) >= 20) && (gHDMI21RxDevVideoControler[HDMI21__VIDEO_FS_CONSIDER_HDCP2X_CASE].value > 0)){	
								HDMI21_LINE_DBG(12001, "INFO[%d] : Reset PHY due to restore from Low Power Mode.[0x28]:[0x1] 01->11\n", _p->port);
								__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

								__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);

								HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #2 : PHY[0x28]:[0x6] 11->01->11\n", _p->port);
								__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

								HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #3 : PHY[0x28]:[0x1] 11->01\n", _p->port);
								__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
							}
						}
					}
					else { /* FRL Modes */
						/* DR ON */
						__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x0);

						/* PDC ON */
						__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x0);
					}
				}
			}
		}
		else {
			/* 2020/04/01 : Lock Up defence code */
			if(_p->is5Vconnected > 0){
				/* DR ON */
				__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x0);

				/* EQ ON */
				__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x0);

				#if 1 
				/* PHY RESET Sequence */
				HDMI21_LINE_DBG(12001, "INFO[%d] : Reset PHY due to restore from Low Power Mode.[0x28]:[0x1] 01->11\n", _p->port);
				__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);


				__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
				HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #2 : PHY[0x28]:[0x6] 11->01->11\n", _p->port);
				__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

				HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #3 : PHY[0x28]:[0x1] 11->01\n", _p->port);
				__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
				#endif
			}
		}
	}

	return;
}


static void  __HDMI21_HAL_Rx_Set_LowPowerSettingStep1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;

	if(_p->isLowPowerTransState == 0) {
		HDMI20_ERROR("ERROR[%d] : Fatal Error![Code:0] Maybe memory failiure\n", _p->port);
		return;
	}

	if(isLowPower) {
		HDMI20_INFO("INFO[%d] : LowPower Mode Step#1 has been set\n", _p->port);

		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			_p->top_write(0x328, 0x0);
			
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			_p->top_write(0x328, 0x81000002);
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			/* Step 1 */
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				_p->top_write(0x328, 0x00070000);
				HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to [0x00070000](PreCondition)\n", _p->port);

				_p->top_write(0x328, 0x80070000);
				HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to [0x80070000](FakeModule On)\n", _p->port);
		
				/* 2021/11/25 : JW CHOI */
				_p->link_write(0x700, 0x1);
			}
			else { /* FRL Mode */
				_p->top_write(0x328, 0x81000000);
				HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to [0x81100000] from [0x81000000]\n", _p->port);
				_p->top_write(0x328, 0x81100000);
			}

		}
		else {
			/* Read Current Value */
			__data = _p->top_read(HDMI21_TOP_REG_AD_FS_1);

			__data |= (HDMI21_TOP_FIELD_AD_FS_1_E60B0_NEW | HDMI21_TOP_FIELD_AD_FS_1_SEND_FAKE_ECC_ESM);
			_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);
			HDMI21_LINE_DBG(12001, "INFO[%d] : GEN Fake Sync to HDCP modules! R314<=[0x%08x]\n", _p->port, _p->top_read(HDMI21_TOP_REG_AD_FS_1));
		}
	}
	else {
		HDMI20_INFO("INFO[%d] : Restore to Normal Mode Step#1 has been set\n", _p->port);

		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(_p->phyInitiatedMode > HDMI21_HAL_PHY_INITIATED_6G) { /* FRL Modes */
				_p->top_write(0x330, 0x505);
				_p->top_write(0x32c, 0x1014000);
			}else{
				/* Do Nothing */
				//__reg = 0x89; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x20);	// 0x48
				//_p->top_write(0x328, 0x81070001);
			}
				
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			_p->top_write(0x328, 0x81000000);
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */

				if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 11017) {
					_p->top_write(0x328, 0x81070000);
					HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to [0x81070000](Restore Data)\n", _p->port);
				}

			}
			else { /* FRL Modes */
				/* Step 1 */
				_p->top_write(0x32c,  gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value );

				/* Step 2 */
				_p->top_write(0x328, 0x81000001);
			}
		}
		else {
			/* Read Current Value */
			__data = _p->top_read(HDMI21_TOP_REG_AD_FS_1);

			/* Free ECC err going to ESM */
			__data &= (~HDMI21_TOP_FIELD_AD_FS_1_SEND_FAKE_ECC_ESM);
			_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);
			HDMI21_LINE_DBG(12001, "INFO[%d] : Restore ECC Error connection to ESM Module! R314<=[0x%08x]\n", _p->port, _p->top_read(HDMI21_TOP_REG_AD_FS_1));
		}

	}

	return;
}

static void  __HDMI21_HAL_Rx_Set_LowPowerSettingStep2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;
	UINT32 __reg  = 0;

	if(_p->isLowPowerTransState == 0) {
		HDMI20_ERROR("ERROR[%d] : Fatal Error![Code:0] Maybe memory failiure\n", _p->port);
		return;
	}

	if(isLowPower) {
		HDMI20_INFO("INFO[%d] : LowPower Mode Step#2 has been set\n", _p->port);

		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			/* DR OFF */
			//__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xAA);

			/* PDC OFF */
			//__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0xA);
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 16241) {
				HDMI20_INFO("INFO[%d] Top 0x300 <= [0x%08x], 0x304 <= [0x%08x], 0x308 <= [0x%08x], 0x30C <= [0x%08x]\n", _p->port, _p->top_read(0x300), _p->top_read(0x304), _p->top_read(0x308), _p->top_read(0x30c));
				HDMI20_INFO("INFO[%d] Top 0x310 <= [0x%08x], 0x314 <= [0x%08x], 0x318 <= [0x%08x], 0x31C <= [0x%08x]\n", _p->port, _p->top_read(0x310), _p->top_read(0x314), _p->top_read(0x318), _p->top_read(0x31c));
				HDMI20_INFO("INFO[%d] Top 0x320 <= [0x%08x], 0x324 <= [0x%08x], 0x328 <= [0x%08x], 0x32C <= [0x%08x]\n", _p->port, _p->top_read(0x320), _p->top_read(0x324), _p->top_read(0x328), _p->top_read(0x32c));
				HDMI20_INFO("INFO[%d] Top 0x330 <= [0x%08x], 0x334 <= [0x%08x], 0x338 <= [0x%08x], 0x33C <= [0x%08x]\n", _p->port, _p->top_read(0x330), _p->top_read(0x334), _p->top_read(0x338), _p->top_read(0x33c));
				HDMI20_INFO("INFO[%d] Top 0x340 <= [0x%08x], 0x344 <= [0x%08x], 0x348 <= [0x%08x], 0x34C <= [0x%08x]\n", _p->port, _p->top_read(0x340), _p->top_read(0x344), _p->top_read(0x348), _p->top_read(0x34c));
				HDMI20_INFO("INFO[%d] Top 0x350 <= [0x%08x], 0x354 <= [0x%08x], 0x358 <= [0x%08x], 0x35C <= [0x%08x]\n", _p->port, _p->top_read(0x350), _p->top_read(0x354), _p->top_read(0x358), _p->top_read(0x35c));
			}
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				_p->top_write(0x328, 0x81070000);
			}else{	/* FRL modes */
				_p->top_write(0x328, 0x81100000);
			}
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 16241) {
				HDMI20_INFO("INFO[%d] Top 0x300 <= [0x%08x], 0x304 <= [0x%08x], 0x308 <= [0x%08x], 0x30C <= [0x%08x]\n", _p->port, _p->top_read(0x300), _p->top_read(0x304), _p->top_read(0x308), _p->top_read(0x30c));
				HDMI20_INFO("INFO[%d] Top 0x310 <= [0x%08x], 0x314 <= [0x%08x], 0x318 <= [0x%08x], 0x31C <= [0x%08x]\n", _p->port, _p->top_read(0x310), _p->top_read(0x314), _p->top_read(0x318), _p->top_read(0x31c));
				HDMI20_INFO("INFO[%d] Top 0x320 <= [0x%08x], 0x324 <= [0x%08x], 0x328 <= [0x%08x], 0x32C <= [0x%08x]\n", _p->port, _p->top_read(0x320), _p->top_read(0x324), _p->top_read(0x328), _p->top_read(0x32c));
				HDMI20_INFO("INFO[%d] Top 0x330 <= [0x%08x], 0x334 <= [0x%08x], 0x338 <= [0x%08x], 0x33C <= [0x%08x]\n", _p->port, _p->top_read(0x330), _p->top_read(0x334), _p->top_read(0x338), _p->top_read(0x33c));
				HDMI20_INFO("INFO[%d] Top 0x340 <= [0x%08x], 0x344 <= [0x%08x], 0x348 <= [0x%08x], 0x34C <= [0x%08x]\n", _p->port, _p->top_read(0x340), _p->top_read(0x344), _p->top_read(0x348), _p->top_read(0x34c));
				HDMI20_INFO("INFO[%d] Top 0x350 <= [0x%08x], 0x354 <= [0x%08x], 0x358 <= [0x%08x], 0x35C <= [0x%08x]\n", _p->port, _p->top_read(0x350), _p->top_read(0x354), _p->top_read(0x358), _p->top_read(0x35c));
			}

		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){	
			/* DR OFF */
			__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xAA);

			/* PDC OFF */
			__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0xA);

		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){

			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to [0x81070000] from [0x81070001]\n", _p->port);
				_p->top_write(0x328, 0x81070001);
			}
			else {
				HDMI20_INFO("INFO[%d] TOP(0x328) is being setting to [0x81100001] from [0x81100000]\n", _p->port);
				_p->top_write(0x328, 0x81100001);
			}

			if(_p->is5Vconnected > 0){
				
				if((gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_PHY_DBG].value & 0x1) != 0x0) {
					/* Do Nothing */
					HDMI20_INFO("INFO[%d] : Set DBG Mode. Discard PHY OFF for Low Power\n", _p->port);
				}
				else {
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */

						/* 2021/11/15 : JIW WOO CHOI */
						//_p->top_write(0x32c, 0x1);
						HDMI21_VPROC_Rx_Set_VPGenConnection(_p, HDMI21_RX_VPGEN_CONN_HDCP);

						/* 2021/11/01 : ChoiJinWoo Request */
						/* DR OFF */
						__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xAA);

						/* PDC OFF */
						__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0xA);
					}
					else {
						/* Step 1 */
						_p->top_write(0x32C, (gHDMI21RxDevVideoControler[HDMI21__VIDEO_LOWPOWER_O22_32C_VAL].value + 0x1));

						/* DR OFF */
						__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x2A);

						/* PDC OFF */
						__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x2A);
					}
				}
			}
			else {
				HDMI20_INFO("INFO[%d] : Could not turn off phy due to 5V Low\n", _p->port);
			}
		}
		else {
			/* 2020/04/01 : Lock Up defence code */
			if(_p->is5Vconnected > 0){
				/* DR OFF */
				__reg = 0x02; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xA8);

				/* EQ OFF */
				__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0xAA);
			}
		}

		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 8291){
			/* 2020/06/29 : Mute */
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 0);
		}
	}
	else {
		HDMI20_INFO("INFO[%d] : Restore to Normal Mode Step#2 has been set\n", _p->port);

		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				_p->top_write(0x328, 0x81270001);
			}
			else {	/* FRL modes */
				_p->top_write(0x328, 0x81000001);
			}
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			_p->top_write(0x328, 0x0);
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 11017) {
				/* Step 1 */
				_p->top_write(0x328, 0x81000000);

				/* Step 2 */
				_p->top_write(0x328, 0x0);
			}
		}
		else {
			/* Read Current Value */
			__data = _p->top_read(HDMI21_TOP_REG_AD_FS_1);

			/* Free BCH Packet ERR to ESM */
			__data &= (~HDMI21_TOP_FIELD_AD_FS_1_E60B0_NEW);
			_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);
			HDMI21_LINE_DBG(12001, "INFO[%d] : Restore BIT12! R314<=[0x%08x]\n", _p->port, _p->top_read(HDMI21_TOP_REG_AD_FS_1));

			/* Free DE/VSYNC/HSYNC to Normal */
			__data &= (~HDMI21_TOP_FIELD_AD_FS_1_BLOCK_SYNC_DE);
			__data &= (~HDMI21_TOP_FIELD_AD_FS_1_BLOCK_SYNC_VSYNC);
			__data &= (~HDMI21_TOP_FIELD_AD_FS_1_BLOCK_SYNC_HSYNC);
			_p->top_write(HDMI21_TOP_REG_AD_FS_1, __data);
			HDMI21_LINE_DBG(12001, "INFO[%d] : Free DE/VSYNC/HSYNC ON! R314<=[0x%08x]\n", _p->port, __data);

			__data = _p->top_read(HDMI21_TOP_REG_AD_FS_1);
			if(__data != 0x0) {
				HDMI20_WARN("WARN[%d] : Low Power deactivate set detected warning! FS Reg[0x%08x]\n",_p->port, _p->top_read(HDMI21_TOP_REG_AD_FS_1));
			}

		}
	}

	return;
}
static void  __HDMI21_HAL_Rx_Set_LowPowerSettingStep3(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	if(_p->isLowPowerTransState == 0) {
		HDMI20_ERROR("ERROR[%d] : Fatal Error![Code:0] Maybe memory failiure\n", _p->port);
		return;
	}

	if(isLowPower) {
		HDMI20_INFO("INFO[%d] : LowPower Mode Step#3 has been set\n", _p->port);
		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				_p->top_write(0x328, 0x81070001);
			}else{	/* FRL modes */
				_p->top_write(0x328, 0x81100001);
			}

			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 16241) {
				HDMI20_INFO("INFO[%d] Top 0x300 <= [0x%08x], 0x304 <= [0x%08x], 0x308 <= [0x%08x], 0x30C <= [0x%08x]\n", _p->port, _p->top_read(0x300), _p->top_read(0x304), _p->top_read(0x308), _p->top_read(0x30c));
				HDMI20_INFO("INFO[%d] Top 0x310 <= [0x%08x], 0x314 <= [0x%08x], 0x318 <= [0x%08x], 0x31C <= [0x%08x]\n", _p->port, _p->top_read(0x310), _p->top_read(0x314), _p->top_read(0x318), _p->top_read(0x31c));
				HDMI20_INFO("INFO[%d] Top 0x320 <= [0x%08x], 0x324 <= [0x%08x], 0x328 <= [0x%08x], 0x32C <= [0x%08x]\n", _p->port, _p->top_read(0x320), _p->top_read(0x324), _p->top_read(0x328), _p->top_read(0x32c));
				HDMI20_INFO("INFO[%d] Top 0x330 <= [0x%08x], 0x334 <= [0x%08x], 0x338 <= [0x%08x], 0x33C <= [0x%08x]\n", _p->port, _p->top_read(0x330), _p->top_read(0x334), _p->top_read(0x338), _p->top_read(0x33c));
				HDMI20_INFO("INFO[%d] Top 0x340 <= [0x%08x], 0x344 <= [0x%08x], 0x348 <= [0x%08x], 0x34C <= [0x%08x]\n", _p->port, _p->top_read(0x340), _p->top_read(0x344), _p->top_read(0x348), _p->top_read(0x34c));
				HDMI20_INFO("INFO[%d] Top 0x350 <= [0x%08x], 0x354 <= [0x%08x], 0x358 <= [0x%08x], 0x35C <= [0x%08x]\n", _p->port, _p->top_read(0x350), _p->top_read(0x354), _p->top_read(0x358), _p->top_read(0x35c));
			}
		}
	}else{
		HDMI20_INFO("INFO[%d] : Restore to Normal Mode Step#3 has been set\n", _p->port);
		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				_p->top_write(0x328, 0x81270000);
			}
			else {	/* FRL modes */
				_p->top_write(0x328, 0x81000000);
			}
		}
	}
	return;
}
static void  __HDMI21_HAL_Rx_Set_LowPowerSettingStep4(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	if(_p->isLowPowerTransState == 0) {
		HDMI20_ERROR("ERROR[%d] : Fatal Error![Code:0] Maybe memory failiure\n", _p->port);
		return;
	}

	if(isLowPower) {
		HDMI20_INFO("INFO[%d] : LowPower Mode Step#4 has been set\n", _p->port);
		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				/* Do Nothing */
				_p->top_write(0x328, 0x81070801);
				//__reg = 0x89; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x22);	// 0x48
			}
			else {	/* FRL modes */
				_p->top_write(0x32c, 0x1014001);
			}
		}
	}else{
		HDMI20_INFO("INFO[%d] : Restore to Normal Mode Step#4 has been set\n", _p->port);
		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 16241) {
				HDMI20_INFO("INFO[%d] Top 0x300 <= [0x%08x], 0x304 <= [0x%08x], 0x308 <= [0x%08x], 0x30C <= [0x%08x]\n", _p->port, _p->top_read(0x300), _p->top_read(0x304), _p->top_read(0x308), _p->top_read(0x30c));
				HDMI20_INFO("INFO[%d] Top 0x310 <= [0x%08x], 0x314 <= [0x%08x], 0x318 <= [0x%08x], 0x31C <= [0x%08x]\n", _p->port, _p->top_read(0x310), _p->top_read(0x314), _p->top_read(0x318), _p->top_read(0x31c));
				HDMI20_INFO("INFO[%d] Top 0x320 <= [0x%08x], 0x324 <= [0x%08x], 0x328 <= [0x%08x], 0x32C <= [0x%08x]\n", _p->port, _p->top_read(0x320), _p->top_read(0x324), _p->top_read(0x328), _p->top_read(0x32c));
				HDMI20_INFO("INFO[%d] Top 0x330 <= [0x%08x], 0x334 <= [0x%08x], 0x338 <= [0x%08x], 0x33C <= [0x%08x]\n", _p->port, _p->top_read(0x330), _p->top_read(0x334), _p->top_read(0x338), _p->top_read(0x33c));
				HDMI20_INFO("INFO[%d] Top 0x340 <= [0x%08x], 0x344 <= [0x%08x], 0x348 <= [0x%08x], 0x34C <= [0x%08x]\n", _p->port, _p->top_read(0x340), _p->top_read(0x344), _p->top_read(0x348), _p->top_read(0x34c));
				HDMI20_INFO("INFO[%d] Top 0x350 <= [0x%08x], 0x354 <= [0x%08x], 0x358 <= [0x%08x], 0x35C <= [0x%08x]\n", _p->port, _p->top_read(0x350), _p->top_read(0x354), _p->top_read(0x358), _p->top_read(0x35c));
			}
			_p->top_write(0x328, 0x0);
		}
	}
	return;
}

static void  __HDMI21_HAL_Rx_Set_LowPowerSettingStep5(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg  = 0;
	UINT32 __rf, __r10, __r11, __r12, __r18, __r19, __r1a, __r1b;
	UINT32 __df, __d10, __d11, __d12, __d18, __d19, __d1a, __d1b;

	if(_p->isLowPowerTransState == 0) {
		HDMI20_ERROR("ERROR[%d] : Fatal Error![Code:0] Maybe memory failiure\n", _p->port);
		return;
	}

	if(isLowPower) {
		HDMI20_INFO("INFO[%d] : LowPower Mode Step#5 has been set\n", _p->port);
		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */
				/* Do Nothing */
				__reg = 0x2; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0xaa);	// 0x48
				__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0xaa);			// 0x28
			}
			else {	/* FRL modes */
				__reg = 0x2; __reg = (__reg << 2) + 0x400; _p->phyDR_write(__reg, 0x2a);	// 0x48
				__reg = 0x11; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x2a);			// 0x28
			}
		}
	}else{	
		/* 2025/03/25 won.hur : O26/O24, identical codes for low power */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			if ( lx_chip_rev( ) == LX_CHIP_REV( O24, A0) ){
				HDMI21_REG_WR(0xC8D0E834, 0x1fa21510);
			}
			__rf = 0xf; __rf = __rf << 2; __df = _p->phyDR_read(__rf);
			__r10 = 0xf; __r10 = __r10 << 2; __d10 = _p->phyDR_read(__r10);
			__r11 = 0x11; __r11 = __r11 << 2; __d11 = _p->phyDR_read(__r11);
			__r12 = 0x12; __r12 = __r12 << 2; __d12 = _p->phyDR_read(__r12);
			__r18 = 0x18; __r18 = __r18 << 2; __d18 = _p->phyDR_read(__r18);
			__r19 = 0x19; __r19 = __r19 << 2; __d19 = _p->phyDR_read(__r19);
			__r1a = 0x1a; __r1a = __r1a << 2; __d1a = _p->phyDR_read(__r1a);
			__r1b = 0x1b; __r1b = __r1b << 2; __d1b = _p->phyDR_read(__r1b);

			HDMI20_INFO("INFO[%d] : Restore to Normal Mode Step#5 has been set. Top 0x324 <=[0x%08x], Link 0x594 <=[0x%08x], 0x59C <=[0x%08x], 0x5A0 <=[0x%08x], 0x5A4 <=[0x%08x]\n",_p->port, _p->top_read(0x324),_p->link_read(0x594), _p->link_read(0x59c), _p->link_read(0x5a0), _p->link_read(0x5a4));
			HDMI20_INFO("INFO[%d] : Restore to Normal Mode. 0x38 0xF <=[0x%08x], 0x10 <=[0x%08x], 0x11 <=[0x%08x], 0x12 <=[0x%08x], 0x18 <=[0x%08x], 0x19 <=[0x%08x], 0x1A <=[0x%08x], 0x1B <=[0x%08x]\n",_p->port, __df, __d10, __d11, __d12, __d18, __d19, __d1a, __d1b);

			if((_p->top_read(0x324) & 0x40000000) == 0x40000000){
				HDMI20_INFO("\n INFO[%d] : Restore to Normal Mode is FAIL !!!!!!!! \n\n\n",_p->port);
				//HDMI21_HAL_Rx_Set_RestartHPD(_p->port);
			}

		}

		HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 0, 0);
		_p->lowPowerMode = HDMI21_HAL_POWER_NORMAL;
	}
	return;
}

static int __HDMI21_HAL_Rx_Get_IsCurrentIdleState(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	int ret = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	do {
		if(_p->idleTick <= gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value) {
			/* Not enough tick to enter idle mode */
			break;
		}

		ret = 1;
	} while(0);

	return ret;
}

static void __HDMI21_HAL_Rx_DBG_CalculateDfeRepeat(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_PHY_DBG_DFE_DATA_T *pVal)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	
	UINT32 __reg  = 0; 
	UINT32 __data = 0;
	UINT32 __dfeDone = 0;
	int errCnt = 0;

	if(gHdmi21DfeRepeatState[_p->port] == 0) {
		__reg = 0x58; __reg = __reg << 2; __data = 0x0; _p->phyDR_write(__reg, __data);
		gHdmi21DfeRepeatState[_p->port]++;
	}
	else if(gHdmi21DfeRepeatState[_p->port] == 1) {
		__reg = 0x58; __reg = __reg << 2; __data = 0x1; _p->phyDR_write(__reg, __data);
		gHdmi21DfeRepeatState[_p->port]++;
	}
	else if(gHdmi21DfeRepeatState[_p->port] == 2) {
		__reg = 0x5F; __reg = __reg << 2; __dfeDone  = _p->phyDR_read(__reg);

		if((__dfeDone & 0xF) == 0xF) {
			gHdmi21DfeRepeatState[_p->port]++;
			/* Get Current Error Cnt */
			gHdmi21DfeRepeatErrorCntState[_p->port] = _p->phyErrCounter;
		}
	}
	else if(gHdmi21DfeRepeatState[_p->port] == 3) {
		if(_p->phyErrCounter >= gHdmi21DfeRepeatErrorCntState[_p->port] ) {
			errCnt = (int)_p->phyErrCounter - (int)gHdmi21DfeRepeatErrorCntState[_p->port];
		}
		else {
			errCnt = (int)_p->phyErrCounter - (15 - (int)gHdmi21DfeRepeatErrorCntState[_p->port] );
		}
	
		if(errCnt >= 3) {
			/* If Err Cnt changed */
			gHdmi21DfeRepeatState[_p->port]++;
		}
	}
	else if(gHdmi21DfeRepeatState[_p->port] == 4) {
		/* Memset */
		memset((void *)pVal, 0, sizeof(HDMI21_PHY_DBG_DFE_DATA_T));

		/* Set to Ch 0 */
		__reg = 0x3B; __reg = __reg << 2; __data = 0;  _p->phyDR_write(__reg, __data);

		/* Read Dfe value */
		__reg = 0x35; __reg = __reg << 2; pVal->dfeA01_ch0  = _p->phyDR_read(__reg);
		__reg = 0x36; __reg = __reg << 2; pVal->dfeA11_ch0  = _p->phyDR_read(__reg);
		__reg = 0x37; __reg = __reg << 2; pVal->dfeB1_ch0  = _p->phyDR_read(__reg);
		__reg = 0x38; __reg = __reg << 2; pVal->dfeB2_ch0  = _p->phyDR_read(__reg);
		__reg = 0x39; __reg = __reg << 2; pVal->dfeB3_ch0 = _p->phyDR_read(__reg);
		__reg = 0x3A; __reg = __reg << 2; pVal->dfeB4_ch0 = _p->phyDR_read(__reg);
		__reg = 0xCE; __reg = __reg << 2; pVal->dfeB5_ch0 = _p->phyDR_read(__reg);
		pVal->ced_error_ch0  = _p->phyCEDError[0];
		pVal->tmds_error_ch0 = _p->phyTMDSError[0];

		/* Set to Ch 1 */
		__reg = 0x3B; __reg = __reg << 2; __data = 1;  _p->phyDR_write(__reg, __data);

		/* Read Dfe value */
		__reg = 0x35; __reg = __reg << 2; pVal->dfeA01_ch1  = _p->phyDR_read(__reg);
		__reg = 0x36; __reg = __reg << 2; pVal->dfeA11_ch1  = _p->phyDR_read(__reg);
		__reg = 0x37; __reg = __reg << 2; pVal->dfeB1_ch1  = _p->phyDR_read(__reg);
		__reg = 0x38; __reg = __reg << 2; pVal->dfeB2_ch1  = _p->phyDR_read(__reg);
		__reg = 0x39; __reg = __reg << 2; pVal->dfeB3_ch1 = _p->phyDR_read(__reg);
		__reg = 0x3A; __reg = __reg << 2; pVal->dfeB4_ch1 = _p->phyDR_read(__reg);
		__reg = 0xCE; __reg = __reg << 2; pVal->dfeB5_ch1 = _p->phyDR_read(__reg);
		pVal->ced_error_ch1  = _p->phyCEDError[1];
		pVal->tmds_error_ch1 = _p->phyTMDSError[1];


		/* Set to Ch 0 */
		__reg = 0x3B; __reg = __reg << 2; __data = 2;  _p->phyDR_write(__reg, __data);

		/* Read Dfe value */
		__reg = 0x35; __reg = __reg << 2; pVal->dfeA01_ch2  = _p->phyDR_read(__reg);
		__reg = 0x36; __reg = __reg << 2; pVal->dfeA11_ch2  = _p->phyDR_read(__reg);
		__reg = 0x37; __reg = __reg << 2; pVal->dfeB1_ch2  = _p->phyDR_read(__reg);
		__reg = 0x38; __reg = __reg << 2; pVal->dfeB2_ch2  = _p->phyDR_read(__reg);
		__reg = 0x39; __reg = __reg << 2; pVal->dfeB3_ch2 = _p->phyDR_read(__reg);
		__reg = 0x3A; __reg = __reg << 2; pVal->dfeB4_ch2 = _p->phyDR_read(__reg);
		__reg = 0xCE; __reg = __reg << 2; pVal->dfeB5_ch2 = _p->phyDR_read(__reg);
		pVal->ced_error_ch2  = _p->phyCEDError[2];
		pVal->tmds_error_ch2 = _p->phyTMDSError[2];



		/* Set to Ch 0 */
		__reg = 0x3B; __reg = __reg << 2; __data = 3;  _p->phyDR_write(__reg, __data);

		/* Read Dfe value */
		__reg = 0x35; __reg = __reg << 2; pVal->dfeA01_ch3  = _p->phyDR_read(__reg);
		__reg = 0x36; __reg = __reg << 2; pVal->dfeA11_ch3  = _p->phyDR_read(__reg);
		__reg = 0x37; __reg = __reg << 2; pVal->dfeB1_ch3  = _p->phyDR_read(__reg);
		__reg = 0x38; __reg = __reg << 2; pVal->dfeB2_ch3  = _p->phyDR_read(__reg);
		__reg = 0x39; __reg = __reg << 2; pVal->dfeB3_ch3 = _p->phyDR_read(__reg);
		__reg = 0x3A; __reg = __reg << 2; pVal->dfeB4_ch3 = _p->phyDR_read(__reg);
		__reg = 0xCE; __reg = __reg << 2; pVal->dfeB5_ch3 = _p->phyDR_read(__reg);
		pVal->ced_error_ch3  = _p->phyCEDError[3];
		pVal->tmds_error_ch3 = _p->phyTMDSError[3];


		gHdmi21DfeRepeatState[_p->port]++;
	}
	else if(gHdmi21DfeRepeatState[_p->port] == 5) {
		gHdmi21DfeRepeatState[_p->port] = 0;
		gHdmi21DfeRepeatTest[_p->port]++;
	}
	
	return;
}

static int __HDMI21_HAL_Rx_Get_VsiHdmiFormatToViC(UINT8 hdmiFormat)
{
	int ret = 0;

	switch(hdmiFormat) 
	{
		case 0:
			ret = 0; /* reserved as non-defined in spec*/
			break;
		case 1:
			ret = 95; /* Refer to CTA-861-G for 3840x2160 30Hz*/
			break;
		case 2:
			ret = 94; /* Refer to CTA-861-G for 3840x2160 25Hz*/
			break;
		case 3:
			ret = 93; /* Refer to CTA-861-G for 3840x2160 24Hz*/
			break;
		case 4:
			ret = 98; /* Refer to CTA-861-G for 4096x2160 24Hz*/
			break;
		default :

			break;
	}

	return ret;
}

static void __HDMI21_HAL_Rx_Set_CheckDoviClearTimer(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __cJiffiesMsec = 0;
	UINT8 __vsifHead[3];

	do {
		/* Step 0. Only Operate when in DOVI mode */
		if(_p->isDolbyHDR <= 0) {
			break;
		}

		/* Step 1.  Only Operate when debug feature in ON */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_DOVI_PACKET_MS_TIMEOUT].value <= 0) {
			break;
		}

		/* Step 2. Only operate when the DoviTimestamp is bigger than current time stamp */ 
		if(_p->doviTimeStamp == 0) {
			break;
		}

		/* Step 3. Get current Time */
		__cJiffiesMsec = jiffies_to_msecs(jiffies);

		/* Step 4. Check time diff for errors */
		if(_p->doviTimeStamp > __cJiffiesMsec) {
			HDMI21_LINE_DBG(13864, "DBG[%d] : Error. DoviTime[%d] > Current[%d]. Reset TimeStamp\n", _p->port, _p->doviTimeStamp, __cJiffiesMsec);
			_p->doviTimeStamp = 0;
			break;
		}

		/* Step 5. If current time is equal to time stamp, something is wrong.. just ignore) */
		if(_p->doviTimeStamp == __cJiffiesMsec) {
			break;
		}

		/* Step 6. Check Timeout */
		if((__cJiffiesMsec - _p->doviTimeStamp) <  gHDMI21RxDevVideoControler[HDMI21__VIDEO_DOVI_PACKET_MS_TIMEOUT].value) {
			break;
		}

		/* Step 7. check buffer status*/
		__vsifHead[0] = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][4];
		__vsifHead[1] = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][5];
		__vsifHead[2] = _p->dataPacket[HDMI21_DISLAND_DATA__DOVI][6];
		if((__vsifHead[0] == 0) && (__vsifHead[0] == 0) && (__vsifHead[0] == 0)) {
			HDMI21_LINE_DBG(13864, "DBG[%d] : Already clear DOVI buufer \n", _p->port);
			break;
		}

		/* Step 8. If you came this far.. it must be timeout */
		HDMI20_PRINT("Dovi[%d] : Timeout for DOVI. DoviTime[%d]  Current[%d].", _p->port, _p->doviTimeStamp, __cJiffiesMsec);
		/* Reset PKT Buf */
		HDMI21_DISLAND_Rx_Set_ResetPktBuf(HDMI21_DISLAND_DATA__DOVI, _p->port);
	} while(0);

	return;
}

static void __attribute__((unused)) __HDMI21_HAL_Rx_Set_LowPowerSettingStepMid(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isLowPower)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg  = 0;

	if(_p->isLowPowerTransState == 0) {
		HDMI20_ERROR("ERROR[%d] : Fatal Error![Code:0] Maybe memory failiure\n", _p->port);
		return;
	}

	HDMI20_INFO("INFO[%d] : LowPower Mode Step#Mid has been set\n", _p->port);

	if(isLowPower) {
		/* Do Nothing */
		_p->isLowPowerTransState++;
	}
	else {
		if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) { /* TMDS Modes */		
				/* PHY RESET Sequence */

				HDMI21_LINE_DBG(12001, "INFO[%d] : Reset PHY due to restore from Low Power Mode.[0x28]:[0x1] 01->11\n", _p->port);
				__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

				__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);

				HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #2 : PHY[0x28]:[0x6] 11->01->11\n", _p->port);
				__reg = 0x6; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x11);

				HDMI21_LINE_DBG(12001, "INFO[%d] : PHY Reset #3 : PHY[0x28]:[0x1] 11->01\n", _p->port);
				__reg = 0x1; __reg = __reg << 2; _p->phyPDC_write(__reg, 0x1);
			}
		}
		else {
			/* Do Nothing */
		}

		_p->isLowPowerTransState++;
	}

	return;
}

static void _read32(unsigned int addr, unsigned int *data)
{
	int ret = 0;
	ret = SYS_IO_ReadRegArray(addr, 4, (void *)data);
}

int HDMI21_HAL_Rx_Get_FrameRateFromCVI_2nd(UINT8 port)
{
	int ret = -1;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int lock = 0;
//	unsigned int __t;
	unsigned int sd_one_field,cvi_size_detect_ctrl_offset, crg_cvi_addr, data_in_sel, hdmi_port_num, vfreq, cvi_base, cvi_reg_offset, cvi_num, reg_read_tmp, cvi_port_cnt, cvi_top_offset, cvi_size_detect_read_offset, cvi_size_status5_offset, dsc_hdmi_enable, dsc_hdmi_cfg_0, dsc_hdmi_port_sel, dsc_enabled;
	

	do{
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];


		/* 2025/04/29 won.hur : From SJ.YOUM */
		if(_p->isPqeSuspend > 0) {
			break;
		}

		#if 0
		/* Check whether current port is main or not*/
		if(HDMI21_HAL_Rx_Get_IsMyPortMainWindow(port) != RET_OK) {
			break;
		}

		/* Check Whether Current port is in VRR mode */
		if(_p->isFreeSyncMode <= 0) {
			break;
		}

		/* Get Vfreq from DE */
		if(vsc_check_vrr_freq(&__t) < 0) {
			break;
		}

		/* Convert to Int */
		ret = (int)__t;
		#endif
		cvi_top_offset = 0;
		cvi_size_detect_read_offset = 0xc4;
		cvi_size_detect_ctrl_offset = 0xc0;
		cvi_size_status5_offset = 0xcc;

		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
			cvi_base = 0xcc4e0200;
			cvi_reg_offset = 0x100;
			cvi_port_cnt = 4;
			dsc_hdmi_enable = 0xcc500000;
			dsc_hdmi_cfg_0 = 0xcc500010;
			crg_cvi_addr = 0xcc4f0010;
		  }
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			cvi_base = 0xcccc0200;
			cvi_reg_offset = 0x100;
			cvi_port_cnt = 5;
			dsc_hdmi_enable = 0xc8ce0000;
			dsc_hdmi_cfg_0 = 0xc8ce0010;
			crg_cvi_addr = 0xcccd0010;
		  }
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			cvi_base = 0xcc690200;
			cvi_reg_offset = 0x100;
			cvi_port_cnt = 2;
			dsc_hdmi_enable = 0;
			dsc_hdmi_cfg_0 = 0;
			crg_cvi_addr = 0xcc6a0010;
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			cvi_base = 0xcc840200;
			cvi_reg_offset = 0x100;
			cvi_port_cnt = 5;
			dsc_hdmi_enable = 0xc88a0000;
			dsc_hdmi_cfg_0 = 0xc88a0010;
			crg_cvi_addr = 0xcc850010;
		}
		else
			return -1;

		hdmi_port_num = port;

		dsc_enabled = 0;
		if(dsc_hdmi_enable !=0) {
			_read32(dsc_hdmi_enable, &reg_read_tmp);	// DSC Enable
			if(reg_read_tmp == 0x00000707) {	//FEC_HDMI_FIFO_EN,FEC_ENCODER_EN,FEC_CVI_FORMATER_EN,DSC_HDMI_FIFO_EN,DSC_CVI_FORMATER_EN
				_read32(dsc_hdmi_cfg_0, &reg_read_tmp);	// DSC HDMI_CFG_0
				dsc_hdmi_port_sel = reg_read_tmp & 0x1f; // 1:port0, 2:port1, 4:port2, 8:port3, 16:port4
				if(dsc_hdmi_port_sel == (1<<hdmi_port_num))
					dsc_enabled = 1;
			}
		}
		if(_p->isDSC > 0)	{ // DSC condition

			if(mutex_trylock(&__DSC_mutex)) {	// success lock mutex
				lock = 1;
			}
			else {
				return 0;
			}
		}

		for (cvi_num = 0; cvi_num < cvi_port_cnt; cvi_num++) {
			_read32(cvi_base + (cvi_reg_offset*cvi_num) + cvi_top_offset, &reg_read_tmp);	// TOP_CTRL
			data_in_sel = (reg_read_tmp >> 14) & 0xf;
			if( (hdmi_port_num == (data_in_sel>>1)) || ( (dsc_enabled == 1) && (data_in_sel == 0xc))) {
				//_read32(cvi_base + (cvi_reg_offset*cvi_num) + cvi_size_detect_read_offset, &reg_read_tmp);	// SIZE_DETECT_READ
				//reg_read_tmp = reg_read_tmp & 0xffff;
				_read32(cvi_base + (cvi_reg_offset*cvi_num) + cvi_size_status5_offset, &reg_read_tmp);	// SIZE_STATUS5
				reg_read_tmp = reg_read_tmp & 0x0fffffff;
				if(reg_read_tmp == 0) {
					HDMI21_LINE_DBG(8461, "port[%d] : reg zero\n",_p->port); 
					ret = 0;
					break;
				}
				_read32(cvi_base + (cvi_reg_offset*cvi_num) + cvi_size_detect_ctrl_offset, &sd_one_field);	// SIZE_DETECT_CTRL
																											//
				sd_one_field &= 0x00800000;

				if(sd_one_field == 0)
					reg_read_tmp = reg_read_tmp >> 1;

				//vfreq = 40000000000/( reg_read_tmp * 2048);
				//rounding
				vfreq = (40000000000 + (reg_read_tmp >> 1) ) /reg_read_tmp; 	//rounding
				ret = vfreq;
				break;
			}
		}

	} while(0);

	if(lock)
		mutex_unlock(&__DSC_mutex);

	HDMI21_LINE_DBG(8461, "port[%d] : ret[%d]\n",_p->port, ret); 

	return ret;
}


static int __HDMI21_HAL_Rx_Reset_AsyncBridge(int port)
{
	int ret = -1;
	#if defined(INCLUDE_O24_CHIP_KDRV) || defined(INCLUDE_O22_CHIP_KDRV) || defined(INCLUDE_E60_CHIP_KDRV) || defined(INCLUDE_O26_CHIP_KDRV)
	int data;
	#endif

	if(port >= g_hdmi20_number_of_ports){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return ret;
	}
	else
		ret = 0;

	if(0){}
	#ifdef INCLUDE_O26_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )
	{
		HDMI20_VIDEO("Port[%d] reset async bridge\n", port);

		HDMI21_REG_RD(0xC8741010, data); // IPW_Register -> IPW_HDMI_004 
		data |= (0x1<<port); 
		HDMI21_REG_WR(0xC8741010, data); // IPW_Register -> IPW_HDMI_004

		udelay(10);

		HDMI21_REG_RD(0xC8741010, data); // IPW_Register -> IPW_HDMI_004
		data &= ~(0x1<<port); 
		HDMI21_REG_WR(0xC8741010, data); // IPW_Register -> IPW_HDMI_004
	}
	#endif
	#ifdef INCLUDE_O24_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )
	{
		HDMI20_VIDEO("Port[%d] reset async bridge\n", port);

		CTOP_CTRL_O24Ax_RdFL(IP_CTRL_HDMI, ipw_hdmi_004);
		data = CTOP_CTRL_O24Ax_Rd(IP_CTRL_HDMI, ipw_hdmi_004);
		data |= (0x1<<port); 
		CTOP_CTRL_O24Ax_Wr(IP_CTRL_HDMI, ipw_hdmi_004, data); // assert reset
		CTOP_CTRL_O24Ax_WrFL(IP_CTRL_HDMI, ipw_hdmi_004);

		//udelay(10);

		CTOP_CTRL_O24Ax_RdFL(IP_CTRL_HDMI, ipw_hdmi_004);
		data = CTOP_CTRL_O24Ax_Rd(IP_CTRL_HDMI, ipw_hdmi_004);
		data &= ~(0x1<<port); 
		CTOP_CTRL_O24Ax_Wr(IP_CTRL_HDMI, ipw_hdmi_004, data); // deassert reset
		CTOP_CTRL_O24Ax_WrFL(IP_CTRL_HDMI, ipw_hdmi_004);
	}
	#endif
	#ifdef INCLUDE_O22_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
	{
		HDMI20_VIDEO("Port[%d] reset async bridge\n", port);

		CTOP_CTRL_O22Ax_RdFL(HDMI_IPW_TOP, ipw_hdmi_001);
		data = CTOP_CTRL_O22Ax_Rd(HDMI_IPW_TOP, ipw_hdmi_001);
		data |= (0x1<<port); 
		CTOP_CTRL_O22Ax_Wr(HDMI_IPW_TOP, ipw_hdmi_001, data); // assert reset
		CTOP_CTRL_O22Ax_WrFL(HDMI_IPW_TOP, ipw_hdmi_001);

		//udelay(10);

		CTOP_CTRL_O22Ax_RdFL(HDMI_IPW_TOP, ipw_hdmi_001);
		data = CTOP_CTRL_O22Ax_Rd(HDMI_IPW_TOP, ipw_hdmi_001);
		data &= ~(0x1<<port); 
		CTOP_CTRL_O22Ax_Wr(HDMI_IPW_TOP, ipw_hdmi_001, data); // deassert reset
		CTOP_CTRL_O22Ax_WrFL(HDMI_IPW_TOP, ipw_hdmi_001);
	}
	#endif
	#ifdef INCLUDE_E60_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		HDMI20_VIDEO("Port[%d] reset async bridge\n", port);

		HDMI21_REG_RD(0xC3321004, data); // HDMI_SYN
		data |= (0x1<<(port<<2)); 
		HDMI21_REG_WR(0xC3321004, data);

//		udelay(10);

		HDMI21_REG_RD(0xC3321004, data); // HDMI_SYN
		data &= ~(0x1<<(port<<2)); 
		HDMI21_REG_WR(0xC3321004, data);
	}
	#endif
	return ret;
}


/* Returns postitive-non-zero values for matching case, and zero value if the Packet does not match */
static int __HDMI21_HAL_Rx_Get_CheckDolbyUniqueDRM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 verbose)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT8 __DrmData[HDMI21_RX_DOLBY_UNIQUE_DRM_COUNT];
	int ret = -1;
	int i;

	do {
		/* Step #2. Set return value */
		ret = 0;

		// 2024.01.10 [QEVENTTF-6766] Dolby Vision supports up to 3840x2160, so larger resolutions are not valid.
		if((_p->video.hactive > 3840) && (_p->video.vactive >= 2160)){
			if(verbose) {
				HDMI20_PRINT("DBG[%d] : Dolby Unique DRM not True! Exceeds 4K Resolution!\n", _p->port);
			}
	
			/* Return as 0 : Non-Dolby-Unique DRM */
			break;
		}

		/* Step #3. Get DRM Data */
		memcpy((UINT8 *)&__DrmData[0], &_p->dataPacket[HDMI21_DISLAND_DATA__DRM][4], HDMI21_RX_DOLBY_UNIQUE_DRM_COUNT);


		/* Step #4. Compare data : PSEUDO Code mentions that we should check from 0 th ~ 17 th but exclude 15 th. 
		 * 						   From SCDCR-5823, detection logic should exclude from [18] (till [25]).
		 *
		 * 						   One more thing.. existing code checks ([18]==0&&[19]==0) then Non-Dolby. */
		/* Step #4-1. Check [18]==0 && [19]== 0 */
		if((__DrmData[18] == 0x0) && (__DrmData[19] == 0x0)){
			if(verbose) {
				HDMI20_PRINT("DBG[%d] : Dolby Unique DRM not True! [18] AND [19] both Zero case!", _p->port);	
			}

			/* Return as 0 : Non-Dolby-Unique DRM */
			break;
		}

		/* Step #4-2. Check through 0~17th */
		for(i=0;i<HDMI21_RX_DOLBY_UNIQUE_DRM_COUNT;i++) 
		{
			if(__DrmData[i] != gDolbyUniqueDRM[i]) {
				
				if(verbose){
					HDMI20_PRINT("DBG[%d] : Dolby Unique DRM not True! Fault on [%d]th (Answer[0x%02x] != Data[0x%02x]).\n", _p->port, i, gDolbyUniqueDRM[i], __DrmData[i]);
				}
				/* Return as 0 : Non-Dolby-Unique DRM */
				break;
			}

			/* If you made it this far... Your definitly Dolby Unique DRM !*/
			if(i >= 18) { 
				/* Set Return value as 1 : Dolby-Unique DRM */
				ret = 1;
				break; 
			}
		}
	
	} while(0);

	return ret;
}

static int __HDMI21_HAL_Rx_Get_LinkTopVfreqCounter(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool highRes)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int isInterlaced = 0;
	UINT64 __sysClock = HDMI21_TOP_VFREQ_COUNTER_SYS_CLOCK; /* 480MHz */	
	UINT64 __vfreq = 0;
	UINT64 __counterValue = 0;

	int ret = -1;

	do {
		/* Step 1. Only works from O26 */
		if(lx_chip_rev( ) < LX_CHIP_REV( O26, A0) ){
			break;
		}

		/* Step 2. Check for Divide by zero */
		if((gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value <= 0) || (__sysClock == 0)) {
			break;
		}

		/* Step 3. Get counter value */
		__counterValue = (UINT64)_p->top_read(HDMI21_TOP_REG_AD_VFREQ_VALUE);

		/* Step 4. Check Interlaced/Progressive mode */
		if( (_p->top_read(HDMI21_TOP_REG_AD_VFREQ_OPT) & HDMI21_TOP_FIELD_AD_VFREQ_OPT_ONE_FIELD) == 0) {
			__counterValue = __counterValue >> 1;
			isInterlaced = 1;
		}

		/* Step 5. Incase counter value is zero.. */
		if(__counterValue == 0) {
			ret = 0;
			break;
		}

		/* Step 6. Calculate Vfreq */
		__sysClock *=  (UINT64)gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value;
	
		/* Fault Test Mode : For test purpose*/
		if(gHDMI21RxDevLinkControler[HDMI21__LINK_FAULT_INJECTION_VFREQ_COUNT].value > 0) {
			__sysClock = __sysClock + (__sysClock *  gHDMI21RxDevLinkControler[HDMI21__LINK_FAULT_INJECTION_VFREQ_COUNT].value);

			gHDMI21RxDevLinkControler[HDMI21__LINK_FAULT_INJECTION_VFREQ_COUNT].value -= 1;
		}


		/* Step 7. For high Res */
		if(highRes) {
			__sysClock *= 100;
		}

		/* Step 8. Division */
		__vfreq = ((__sysClock / __counterValue) / (UINT64)gHDMI21RxDevLinkControler[HDMI21__LINK_USE_LINK_VFREQ_COUNTER].value);
		
		/* Step 9. Set return value */
		__vfreq &= 0x0FFFFFFF;
		ret = (int)__vfreq;

		
		/* DBG. Print */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1748){
			HDMI20_DBG("DBG[%d] : Interlaced[%d] Counter Val[%lld] HighRes[%d] Vfreq[%lld]\n", _p->port, isInterlaced, __counterValue, highRes, __vfreq);
		}

	} while(0);

	return ret;
}

static void __HDMI21_HAL_Rx_Set_LinkTopVfreqCounter(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isProgressive, bool enable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;

	do {
		/* Step 1. Set enable/disable */
		if(enable) {
			__data |= HDMI21_TOP_FIELD_AD_VFERQ_OPT_VFREQ_CHK_EN;	
		}

		/* Step 2. Set Interlaced/Progressive */
		if(isProgressive) {
			__data |= HDMI21_TOP_FIELD_AD_VFREQ_OPT_ONE_FIELD;
		}

		/* Step 3. Set value to register */
		_p->top_write(HDMI21_TOP_REG_AD_VFREQ_OPT, __data);

	} while(0);

	return;
}


/* 2025/04/29 won.hur : From SJ.YOUM */
#ifdef INCLUDE_KDRV_PQE_PM
static int __HDMI21_HAL_Rx_CB_PqePmRunTimeCallback(int action)
{
	int i;

	HDMI20_INFO("[%s:%d] with [%d]\n", __F__, __L__, action);

	if(action <= PQE_PM_DEVICE_RESUME) {
		for(i=0; i<g_hdmi20_number_of_ports; i++) {
			gHDMI21RxHandler[i].isPqeSuspend = true;	
		}
	}
	else {
		for(i=0; i<g_hdmi20_number_of_ports; i++) {
			gHDMI21RxHandler[i].isPqeSuspend = false;	
		}
	}

	return 0;
}
#endif

static void __HDMI21_HAL_Rx_Reset_ChipHdmiSynTop(int port, bool ResetOnTrue)
{
	UINT32 __mask, __apbAddr, __data = 0;

	/* 2025/06/12 won.hur : This function is to cover chip-bug related to O26-HDMI-SCDC from not flushing from  DATAPATHONLY reset.
	 * 						I don't expect this would have to be called for future SoCs.. so I am not going to put efforts and use raw register address values */

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
	
		HDMI20_INFO("INFO[%d] : (SW WA-O26) HDMI-SYN reset pin %s\n", port, ResetOnTrue? "High":"Low");

		/* Set addr, mask */
		if(port == 0) {
			__apbAddr = 0xC874000C;
			__mask = BIT(12);
		}
		else if(port == 1) {
			__apbAddr = 0xC874000C;
			__mask = BIT(25);
		}
		else if(port == 2) {
			__apbAddr = 0xC8740010;
			__mask = BIT(6);
		}
		else if(port == 3) {
			__apbAddr = 0xC8740010;
			__mask = BIT(19);
		}

		/* Read Reg */
		HDMI21_REG_RD(__apbAddr, __data);

		if(ResetOnTrue) {
			__data |= __mask;
		}
		else {
			__data &= (~__mask);
		}

		/* Write Reg */
		HDMI21_REG_WR(__apbAddr, __data);
	}

	return;
}



