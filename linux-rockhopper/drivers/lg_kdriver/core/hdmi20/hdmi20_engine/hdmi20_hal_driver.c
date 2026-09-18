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
 *  @date		2016-05-02
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/

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

#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>
#include "../hdmi20_module.h"

#include "hdmi20_hal_driver.h"

#include "hdmi20_rx_disland.h" /* Data island control */
#include "hdmi20_rx_irq.h"     /* IRQ control */
#include "hdmi20_rx_audio.h"   /* Audio control */

#include "hdmi20_rx_port.h"

#include "hdmi20_rx_phy.h"

#include "os_util.h"

#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"
#include "hdmi20_drv.h"

#include "sys_regs.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
#define HDMI20_KERNEL_DRIVER_DATE 20190613
#define HDMI20_KERNEL_DRIVER_VER 0x4D

#ifndef ON
#define ON	1
#endif

#ifndef OFF
#define OFF 0
#endif

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/
#define HDMI20_REG_WR(address,data)   \
	gMapped_address=(UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(gMapped_address == NULL) break;\
	*gMapped_address = data;\
	iounmap((void *)gMapped_address);\
}while(0);\

#define HDMI20_REG_RD(address,data)   \
	gMapped_address = (UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(gMapped_address == NULL) {data = 0; break;}\
	data = (unsigned int)*gMapped_address;\
	iounmap((void *)gMapped_address);\
}while(0);\

#define TBL_NUM(X)						(sizeof(X) /sizeof((X)[0]))
#define ENUM_TO_STR(x) #x

#define u32CHK_RANGE(X,Y,offset)		((((int)X - (int)Y) <= (int)offset) && (((int)X - (int)Y) >= -(int)offset))

#define E_TO_S(x) #x	
/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/

typedef enum
{
	HDMI20_MANUAL_2D_3G_3840_2160_24 = 0,
	HDMI20_MANUAL_2D_3G_3840_2160_25,
	HDMI20_MANUAL_2D_3G_3840_2160_30,
	HDMI20_MANUAL_2D_3G_3840_2160_420_50,
	HDMI20_MANUAL_2D_3G_3840_2160_420_60,
	HDMI20_MANUAL_2D_3G_4096_2160_24,
	HDMI20_MANUAL_2D_3G_4096_2160_25,
	HDMI20_MANUAL_2D_3G_4096_2160_30,
	HDMI20_MANUAL_2D_6G_3840_2160_50,
	HDMI20_MANUAL_2D_6G_3840_2160_60,
	HDMI20_MANUAL_2D_6G_4096_2160_50,
	HDMI20_MANUAL_2D_6G_4096_2160_60,
	HDMI20_MANUAL_2D_4K_SYNC_PARAM_MAXNUM
} HDMI20_MANUAL_2D_4K_SYNC_PARAM_T;

typedef enum
{
	HDMI20_MANUAL_3D_3G_1920_1080_50_FA = 0,
	HDMI20_MANUAL_3D_3G_1440_576_50_FA,
	HDMI20_MANUAL_3D_3G_1920_1080_60_FA,
	HDMI20_MANUAL_3D_3G_1440_480_60_FA,
	HDMI20_MANUAL_3D_3G_2880_480_60_FA,
	HDMI20_MANUAL_3D_3G_2880_600_50_FA,
	HDMI20_MANUAL_3D_3G_1440_600_50_FA,
	HDMI20_MANUAL_3D_SYNC_PARAM_FA_MAXNUM
} HDMI20_MANUAL_3D_SYNC_PARAM_FA_T;

typedef enum
{
	HDMI20_MANUAL_SYNC_VIC22 = 0,
	HDMI20_MANUAL_SYNC_VIC18,
	HDMI20_MANUAL_SYNC_VIC7,
	HDMI20_MANUAL_SYNC_VIC14,
	HDMI20_MANUAL_SYNC_VIC16,
	HDMI20_MANUAL_SYNC_VIC4,
	HDMI20_MANUAL_2D_2K_SYNC_PARAM_MAXNUM
} HDMI20_MANUAL_2D_2K_SYNC_PARAM_T;

typedef enum
{
	HDMI20_MANUAL_3D_3G_2880_576_50_SBSFULL = 0,	// Master 683
	HDMI20_MANUAL_3D_SYNC_PARAM_SBSFULL_MAXNUM
} HDMI20_MANUAL_3D_SYNC_PARAM_SBSFULL_T;

typedef enum
{
	HDMI20_SYNOPSYS_CEA_RST_FULL = 0,
	HDMI20_SYNOPSYS_CEA_RST_PIN_UP,
	HDMI20_SYNOPSYS_CEA_RST_PIN_DOWN,
	HDMI20_SYNOPSYS_CEA_RST_MAXNUM
} HDMI20_SYNOPSYS_CEA_RST_MODE_T;

typedef struct
{
	UINT32 phyInitiatedMode;	
	UINT32 hactive;
	UINT32 vactive;
	UINT32 vfreq;

	UINT32 hBlankHactive;	//0x408
	UINT32 hFrontHsync;		//0x40C
	UINT32 vFrontVsync;		//0x414
	UINT32 vBlankVactive;	//0x410
} HDMI20_MANUAL_SYNC_PARAM_VALUE_T;

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
/* Chip Reg setting Handler */
extern HDMI20_MODULE_CHIP_ADDR_DATA_T gHDMI20ChipRegHandler;

extern int dataPacketNum[PACKET_MAXNUM];
extern char sPacketName[hdmi_rx_ctrl_packet_cnt][PACKET_MAXNUM];

extern HDMI20_DEV_CONTROL_T	gHDMI20RxDevAudControler[HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
struct gpio_desc *gpiod_hdmi20;

struct device hdmi_gpio_dev = { .init_name = "gpio_kerneltable", };

UINT8 gZero19bytes[19] = {0,};
UINT8 gZero23bytes[23] = {0,};

int gIsALEDIssueSolved = 0;

volatile UINT32 *pISol_Addr0 = NULL;
volatile UINT32 *pISol_Addr1 = NULL;
volatile UINT32 *pISol_Addr2 = NULL;

HDMI20_HAL_MEMORY_MAPPING_T sAledTop; 

int gIsHDMI20KdrvOpen = -1;
int gIsHDMI20KdrvInitialized = -1;

/* For 3G 4K video display enable signal HW bug, SW W/A */
HDMI20_MANUAL_SYNC_PARAM_VALUE_T g2DManualSyncLUT[HDMI20_MANUAL_2D_4K_SYNC_PARAM_MAXNUM] =
{
	{0, 3840, 2160, 240, 0x67C0F00, 0x4FC0058, 0x8000A, 0x5A0870},
	{0, 3840, 2160, 250, 0x5A00F00, 0x4200058, 0x8000A, 0x5A0870},
	{0, 3840, 2160, 300, 0x2300F00, 0xB00058,  0x8000A, 0x5A0870},
	{0, 3840, 2160, 500, 0x02D00780, 0x210002C, 0x8000A, 0x5A0870},
	{0, 3840, 2160, 600, 0x1180780, 0x0058002C, 0x0008000A, 0x005A0870},
	{0, 4096, 2160, 240, 0x57C1000, 0x3FC0058, 0x8000A, 0x5A0870},
	{0, 4096, 2160, 250, 0x4A01000, 0x3C80058, 0x8000A, 0x5A0870},
	{0, 4096, 2160, 300, 0x1301000, 0x580058,  0x8000A, 0x5A0870},
	{1, 3840, 2160, 500, 0x5A00F00, 0x4200058, 0x8000A, 0x5A0870},
	{1, 3840, 2160, 600, 0x2300F00, 0xB00058,  0x8000A, 0x5A0870},
	{1, 4096, 2160, 500, 0x4A01000, 0x3C80058, 0x8000A, 0x5A0870},
	{1, 4096, 2160, 600, 0x1301000, 0x580058,  0x8000A, 0x5A0870}
};

HDMI20_MANUAL_SYNC_PARAM_VALUE_T g3D_FA_ManualSyncLUT[HDMI20_MANUAL_3D_SYNC_PARAM_FA_MAXNUM] =
{
	{0, 1920, 1080, 500, 0x02d00780, 0x0210002c, 0x00020005, 0x0016021c},	// Master 508
	{0, 1440, 576,  500, 0x012005a0, 0x0018007c, 0x00010003, 0x00180120},	// Master 518
	{0, 1920, 1080, 600, 0x01180780, 0x0058002c, 0x00020005, 0x0016021c},	// Master 605
	{0, 1440, 480,  600, 0x011405a0, 0x0026007b, 0x00020003, 0x001600f0},	// Master 655
	{0, 2880, 480,  600, 0x02280B40, 0x004C00F8, 0x00040003, 0x001600F0},	// Master 596
	{0, 2880, 600,  500, 0x02400B40, 0x003000FC, 0x00020003, 0x00180120},	// Master 803, 856
	{0, 1440, 600,  500, 0x012005A0, 0x0018007E, 0x00020003, 0x00180120}	// Master 518 
};

HDMI20_MANUAL_SYNC_PARAM_VALUE_T g2D_2K_ManualSyncLUT[HDMI20_MANUAL_2D_2K_SYNC_PARAM_MAXNUM] = 
{
	{0, 1440, 576,  500, 0x12005A0, 0x18007E,  0x20003,	0x180120},
	{0, 720,  576,  500, 0x9002D0,  0xC0040,   0x50005, 0x310240},
	{0, 1440, 480,  600, 0x11405A0, 0x26007C,  0x40003, 0x1600F0},
	{0, 1440, 480,  600, 0x11405A0, 0x20007C,  0x90006, 0x2D01E0},
	{0, 1920, 1080, 600, 0x1180780, 0x58002C,  0x40005, 0x2d0438},
	{0, 1280, 720,  600, 0x1720500, 0x6E0028,  0x50005, 0x1E02D0}
};

/* Device handlers : Needs each for each link */
volatile HDMI20_HAL_RX_DEVICE_DATA gHDMI20RxHandler[HDMI20_NUM_OF_RX_PORTS];

/* Main Thread */
volatile HDMI20_THREAD_CONTROLLER_T gHDMI20Thread = {NULL, 1, 0, HDMI20_HAL_INITIAL_THREAD_SLEEP_MS};

/* Device controler : This contols the behavior of the Driver */
volatile HDMI20_DEV_CONTROL_T	gHDMI20RxDevControler[HDMI20__DEV_CONTROL_LIST_MAXNUM]=
{
	{E_TO_S(HDMI20__PHY_STABLE_THRESHOLD),		0x2, 	" Threshold for validating PHY LOCK for MCS phy"},
	{E_TO_S(HDMI20__PHY_TCS_THRESHOLD),			0x3, 	" TCS valid threshold. TCS diff must be larger than value"},
	{E_TO_S(HDMI20__SURGE_H_THRESHOLD),			0x40000, " Surge detect threshold for V-change detection"},
	{E_TO_S(HDMI20__SURGE_V_THRESHOLD),			0x80000, " Surge detect threshold for V-change detection"},
	{E_TO_S(HDMI20__VFREQ_SUPPORT_MIN),			15, " The lowest Vfreq value that the LINK can support"},
	{E_TO_S(HDMI20__VFREQ_SUPPORT_MAX),			125, " The highest Vfreq value that the LINK can support"},
	{E_TO_S(HDMI20__DBG_SYNC_MONITOR_RUN_MODE),	0,  " 0:SYNC Monitor prints everytime / 1:SYNC Monitor prints diff value only"},
	{E_TO_S(HDMI20__DBG_CRC_MONITOR_RUN_MODE),	0,  " 0:CRC Monitor prints everytime / 1:CRC Monitor prints diff value only"},
	{E_TO_S(HDMI20__STABLE_CHECK_CNT), 			HDMI20_HAL_VIDEO_CHECK_CNT, " HDMI2.0 Stable Check Counter"},		
	{E_TO_S(HDMI20__PHY_LOST_TIMEOUT), 			10, " Timeout value for when the PHY lock was loss in a Healthy PHY LOCK OK situation"},
	{E_TO_S(HDMI20__CLEAR_AVMUTE_BY_TIMER), 	1,	" Enable Timeouts for when the AVMUTE OFF was not received by the source device"},
	{E_TO_S(HDMI20__AVMUTE_HOLD_TIME), 			1000, 	" Some devices send only AVMUTE ON, not OFF... this is a time-out for AVMUTE ON"},
	{E_TO_S(HDMI20__LOCAL_MUTE_HOLD_TIME), 		1600,	" Local Mute hold time"},
	{E_TO_S(HDMI20__LOCAL_MUTE_HOLD_INIT_TIME), 1600,	" Local Mute hold time : initial state"},
	{E_TO_S(HDMI20__LOCAL_MUTE_HOLD_ORIGIN_TIME), 	500," Local Mute hold time : Normal case"},
	{E_TO_S(HDMI20__FORCE_FULL_RESET_ON_CEA_VIDEO_RST), 1,	" 0:Always do a FULL CEA video reset(300msec)/1:CEA video reset simualtaneously with video transition range"},
	{E_TO_S(HDMI20__DISABLE_AVMUTE_BY_POLLING), 1,	" Synopsys GCP packet AVMute interrupt does not work often"},
	{E_TO_S(HDMI20__HPD_UP_ON_5V), 				1,	" 0 : HDCP2.2 Reset and then HPD UP / 1: HPD Up and then HDCP2.2 reset"},
	{E_TO_S(HDMI20__SURGE_DETECTOR_ON), 		0,	" Surge Monitor On/Off"},
	{E_TO_S(HDMI20__DISABLE_DCM_UPDATE_FOR_LINK), 	0,	" Do not update DCM info on GCP ISR"},
	{E_TO_S(HDMI20__RESET_MANUAL_SYNC_ON_VFREQ_CHANGE), 1,	" When Vfreq changes within specific range, disable manual sync register to enter manual sync setting again"},
	{E_TO_S(HDMI20__SET_MANUAL_SYNC_FOR_ALL_FHD),0,	" 1: Set every under FHD resolution to manual sync mode calucated by values from link"},
	{E_TO_S(HDMI20__DELAY_TIME_BEFORE_SETTING_2D_MANUAL_SYNC), 0,	" Delay value before setting 2D manual sync value only for only automatic 2D manual sync mode"},
	{E_TO_S(HDMI20__USE_SCDC_ISR), 				0,	" 0:Read SCDC by polling / 1:Read SCDC value from the ISR routine"},
	{E_TO_S(HDMI20__ADJUST_DETECTED_4K_SYNC_WITH_HTOTAL), 1," Compenstate vfreq detection for 4K manual sync by using HTOTAL values"},
	{E_TO_S(HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC), 20," Threshold tolerence for compensating vfreq detection for 4K manual sync"},
	{E_TO_S(HDMI20__TOLERENCE_FOR_VFREQ_UPDATE), 4,	" Threshold for updating the VFREQ information"},
	{E_TO_S(HDMI20__ENABLE_MANUAL_SYNC), 		0,	" 0:Disable any manual sync set operation/1:Enable any enabled manual sync SW WAs"},
	{E_TO_S(HDMI20__TOLERENCE_FOR_TMDS_UPDATE), HDMI20_RX_TMDS_TOLERANCE,	" Threshold for updating TMDS clk inside the TMDS ISR"},
	{E_TO_S(HDMI20__LINK_RESET_DELAY_TIME), 	0,	" Delay time(ms) for LINK MAIN reset"},
	{E_TO_S(HDMI20__USE_POLLING_MODE_FOR_DATAPACKET), 1," 0: Only get DataPackets using the ISR / 1: Polling mode for gathering Datapackes"},
	{E_TO_S(HDMI20__PERIOD_FOR_DATAPACKET_POLLING), 1," Time interval(x50msec) for DataPacket Polling operation, only useful when it is in polling mode"},
	{E_TO_S(HDMI20__CEA_VIDEO_RESET_DELAY), 	50," CEA Video Reset delay time(ms)"},
	{E_TO_S(HDMI20__VERBOSE_FOR_ABNORMAL_SYNC), 0,	" Verbose for when synopsys API refuses to update timing information"},
	{E_TO_S(HDMI20__DISABLE_SYNOPSYS_BSP_ACCESS), 	0,	" Block synopsys API from using BSP writes"},
	{E_TO_S(HDMI20__TIMEOUT_FOR_PHY_LOCK_WAIT), 	250,	" Timeout print for when the PHY is not being locked"},
	{E_TO_S(HDMI20__TIMEOUT_FOR_HPD_REQUEST), 		30,	" (Only operate when Timeout value for the HPD not getting high after requested"},
	{E_TO_S(HDMI20__LINK_REG_0XFF0_RESET_VALUE_0), 	0xFEFE,	" Reset value for LINK reset register on case #0"},
	{E_TO_S(HDMI20__THRESHOLD_FOR_ABNORMAL_PHY_DETECTION), 100," A Timeout for a FULL reset once the PHY lock was lost"},
	{E_TO_S(HDMI20__REINIT_PHY_ON_LOCK_LOSS_BY_DETECTION), 0,	" On/Off the timeout phy reset on phy lost"},
	{E_TO_S(HDMI20__VIDEO_LINE_DEBUGGER), 		0,	" The value for activating specific conditions for VIDEO codes"},
	{E_TO_S(HDMI20__PHY_RS_GAIN_FOR_3G), 			8,	" PHY RS Gain value for 3G mode."},
	{E_TO_S(HDMI20__PHY_RS_GAIN_FOR_6G), 			10,	" PHY RS Gain value for 6G mode."},
	{E_TO_S(HDMI20__FORCE_SCDC_INSERTION), 		0,	" Fix the SCDC value"},
	{E_TO_S(HDMI20__FORCE_PLL_RANGE_DETECTED_RESULT), 0," The Fix value for PLL TMDS clock range detection"},
	{E_TO_S(HDMI20__NUMBER_OF_ACTIVATED_LINK), 	0,	" # of running HDMI ports"},	
	{E_TO_S(HDMI20__DELAY_TIME_FOR_PHY_RESET), 	10,	" Delay value for PHY reset"},
	{E_TO_S(HDMI20__LINK_REG_0XA8_GCP_CTRL), 	0x40414," The Value for Link 0xA8 register on link reset"},
	{E_TO_S(HDMI20__LINK_REG_0XC4_HDCP_BCAP), 	0x12174," The Value for Link 0xC4 register on link reset"},
	{E_TO_S(HDMI20__HOLD_TIME_5V_DETECTION), 	0, " A hold time for detecting 5V for MW purpose only"},
	{E_TO_S(HDMI20__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY), 500, " A mute off hold time for HDCP1.4 stability"},
	{E_TO_S(HDMI20__LINK_REG_0X80_HDMI_MODE_RECOVER), 0x3001000C," The Value for Link 0x80 register on link reset"},
	{E_TO_S(HDMI20__LINK_REG_0X16C_HDMI_VERTICAL_TIMING), 0x00000852 ," The Value for Link 0x16C register on link reset"},
	{E_TO_S(HDMI20__COUNT_OF_RESUME), 			0,	" Accumulate counter for resumes"},
	{E_TO_S(HDMI20__FORCE_5V_UP), 				0,	" Force driver to think 5V is always UP"},
	{E_TO_S(HDMI20__FORCE_ORIGIN_TIME_FOR_3D),	1,	" Force driver to upload original timing for 3D signal"},
	{E_TO_S(HDMI20__FORCE_SCDC_6G),				0,  " Force driver phy mode to stay in 6G mode"},
	{E_TO_S(HDMI20__TCS_ERR_SELECT),			0x0,  " TCS Period Err Sel, 0x80 [2:0] value"},
	{E_TO_S(HDMI20__PHY_TMDS_CHANGE_TRESHOLD),	300,  " TMDS diff threshold for PHY STABLE CHECKING Algorithm"},
	{E_TO_S(HDMI20__USE_PHY_LOCK_ONLY_LINK),	0,  " Phy Lock condition only using LINK PHY Lock signal"},
	{E_TO_S(HDMI20__USE_PHY_TCS_PERIOD_SEL),	0x2,  " Phy TCS Period Selection(0x3~0x0)"},
	{E_TO_S(HDMI20__USE_MANUAL_SYNC_FOR_4K),	0x0,  " Use manual sync for 4K Video. Only work with ENABLE_MANUAL_SYNC is HIGH"},
	{E_TO_S(HDMI20__USE_MANUAL_SYNC_FOR_2K),	0x0,  " Use manual sync for selected 2K Video. Only work with ENABLE_MANUAL_SYNC is HIGH"},
	{E_TO_S(HDMI20__USE_MANUAL_SYNC_FOR_FA),	0x1,  " Use manual sync for selected 3D FA. Only work with ENABLE_MANUAL_SYNC is HIGH"},
	{E_TO_S(HDMI20__USE_MANUAL_SYNC_FOR_SSF),	0x0,  " Use manual sync for selected 3D SSF. Only work with ENABLE_MANUAL_SYNC is HIGH"},
	{E_TO_S(HDMI20__USE_MANUAL_SYNC_FOR_DVI), 	0x1,	" Use manual sync for selected DVI Videos. Only work with ENABLE_MANUAL_SYNC is HIGH."},
	{E_TO_S(HDMI20__PHY_3G_TCS_ADD_VAL), 		0x8,	" PHY 3G TCS ADD Val value."},
	{E_TO_S(HDMI20__PHY_6G_TCS_ADD_VAL), 		0x6,	" PHY 6G TCS ADD Val value."},
	{E_TO_S(HDMI20__PHY_MINMAX_ERROR_THRES), 	0x2, 	" PHY TCS Min/Max same error detect threshold"},
	{E_TO_S(HDMI20__PHY_TCSMIN_HIGH_THRES), 	0x8, 	" Exception Case Threshold : TCS MIN Low value"},
	{E_TO_S(HDMI20__PHY_TCSMIN_LOW_TMDS_CLK), 	20000, " Exception Case Threshold : TMDS HIGH value"},
	{E_TO_S(HDMI20__PHY_MIN_HIGH_TCSVAL), 		0x4, 	" Exception Case MIN Threshold : TCS Add value"},
	{E_TO_S(HDMI20__PHY_PDB_TCS_HIST_THRESHOLD),	4,		" Phy TCS Variation Threshold "},
	{E_TO_S(HDMI20__PHY_TCS_RERUN_TMDS_THRESHOLD),	0xFFFF,	" Will rerun TCS over this TMDS Clock "},
	{E_TO_S(HDMI20__PHY_TCS_REPEAT_OFF),			0,		" Set to 1 for TCS Repeat OFF "},
	{E_TO_S(HDMI20__PHY_TCS_ENABLE_RANGE_EQ),		1,		" This enables range EQ"},
	{E_TO_S(HDMI20__PHY_TMDS_EXCEPTIONRANGE_LOW), 	0, 	" Exception Case for PHY MODE Sel TMDS LOW Threshold"},
	{E_TO_S(HDMI20__PHY_TMDS_EXCEPTIONRANGE_HIGH), 	8000, 	" Exception Case for PHY MODE Sel TMDS HIGH Threshold"},
	{E_TO_S(HDMI20__PHY_TCS_MANUAL_EQ_MODE_0),		8,		" If range EQ enable, EQ value for TMDS Range 25-40Mhz"},
	{E_TO_S(HDMI20__PHY_TCS_MANUAL_EQ_MODE_1),		8,		" If rnage EQ enable, EQ value for TMDS Range 40-80Mhz"},
	{E_TO_S(HDMI20__PHY_TCS_MANUAL_EQ_MODE_2),		8,		" If range EQ enable, EQ value for TMDS Range 80-160Mhz"},
	{E_TO_S(HDMI20__PHY_TCS_MANUAL_EQ_MODE_3),		8,		" If range EQ enable, EQ value for TMDS Range 160-340Mhz"},
	{E_TO_S(HDMI20__PHY_DATA_OFF_ON_UNSTABLE),		0, 		" If set to 1, PHY will not transfer data to link on unstable"},
	{E_TO_S(HDMI20__PHY_SCRAMBLE_MANUAL_DETECT),	1, 	" If set to 1, PHY will manualy set TMDS Scrambling status by SCDC on 6G"},
	{E_TO_S(HDMI20__FORCE_DOLBY_DETECT_ON), 		1,  " [0]:Dolby Detection OFF / [1]: Auto / [2]:Force Dolby HDR / [3]:V2 / [4]:V2_Low"},
	{E_TO_S(HDMI20__CEA_RECOVERY_VALUE), 	0x00020000,  " Value of reset value of reg 0x400 for CEA Video Reset"},
	{E_TO_S(HDMI20__USE_ALWAYS_EDID),			1,	" On/Off mode for Always EDID mode"},
	{E_TO_S(HDMI20__ENABLE_WA_MODESEL_STUCKCASE),	1,	" Use SW watch case for MODESEL WATCH DOG malfunction case"},
	{E_TO_S(HDMI20__ENABLE_VSI_HW_REG_MODE), 0,  " Use Physical VSI registers for VSI detection\n"},
	{E_TO_S(HDMI20__ENABLE_DCO_GAME_TEST_MODE), 	0,  " Use DCO Game Test Mode for test"},
	{E_TO_S(HDMI20__ENABLE_PDB_CONTROL_ON_CONNECT), 1, " Enable PDB control on cable connect/disconnect"},
	{E_TO_S(HDMI20__RESET_PHY_STABLE_ON_TMDS_CHANGE), 0, "Re Run TCS on TMDS change over tolerence"},
	{E_TO_S(HDMI20__THRESHOLD_OF_DC_BALANCE_OVERRUN), 2, "DC balance overrun threshold"},
	{E_TO_S(HDMI20__TIME_OF_HPD_DOWN_ON_RESTART_HPD), 1500, "msec value of HPD down on RestartHPD"},
	{E_TO_S(HDMI20__USE_PVO_MODE_FOR_LINK),			1, "Enable PVO mode for HDMI Link"},
	{E_TO_S(HDMI20__LINK_REG_FOR_0X81C_HDCP_OVERRID),	0x00410000, "Value for 0x81C on HDMI Link Reg"},
	{E_TO_S(HDMI20__FORCE_OESS_COUNTRY_VAL), 		0xFFFF, "Country Value for FORCE OESS mode"},
	{E_TO_S(HDMI20__FORCE_HDR10_SAMPLE_PACKET),	0, "0:Auto, 1~3,11~14,101~103(drv)SDR,H10,HLG,(f/w)SDR,H4,H10,HLG,(all)SDR,H10,HLG"},
	{E_TO_S(HDMI20__PHY_TCS_ALLMIN_THRES),	0, "Exception Case : All TCS MIN value for exception approach "},
	{E_TO_S(HDMI20__PHY_TCS_ALLMIN_TMDS_THRES),	20000, "Excepation Case : All TCS MIN value exception TMDS thresh "},
	{E_TO_S(HDMI20__PHY_TCS_ALLMIN_ADDVAL),	0xc, "Exception Case : ALL TCS MIN value exception Add val "},
	{E_TO_S(HDMI20__VIDEOCON_DETECT_THRES),	0x5, "VideoCon Detection Threshold. Works for specific country "},
	{E_TO_S(HDMI20__FORCE_CEA_TMDS_VALUE),	1, "Will go CEA mode under this TMDS Clock"},
	{E_TO_S(HDMI20__CED_CHECK_MODE),		0x0, "Set to 0x2 for disabling CED detection"},
	{E_TO_S(HDMI20__PHY_ADAPTIVE_PERIOD),	0x2, " Set Phy Adaptive period "},
	{E_TO_S(HDMI20__PHY_SW_WA_FOR_PHASE),    0x1, " 1 for activate PHY PHASE SW BUG"},
	{E_TO_S(HDMI20__PHY_ENABLE_PHY_EXCEPTION_CASE),    0x1, " 1 for activate PHY exception detector"},
	{E_TO_S(HDMI20__PHY_PHASE_SWWA_3G_VAL),	 0xA,	" Value for Phy Phase SW WA EQ CS MAN 3G Val"},
	{E_TO_S(HDMI20__PHY_PHASE_SWWA_6G_VAL),	 0x8,	" Value for Phy Phase SW WA EQ CS MAN 6G Val"},
	{E_TO_S(HDMI20__PHY_DELTA_MODE),		0x0, 	" Set 1 for DELTA MODE 1 ON"},
	{E_TO_S(HDMI20__PHY_SET_DFE),			0x1,	" Set 1 for Enabling DFE"},
	{E_TO_S(HDMI20__DBG_PACKET_TYPE),		0x0, 	" DBG : Set Data Packet Type to enable diff printer(0:Off)"},
	{E_TO_S(HDMI20__DBG_PACKET_LOCATION),	0x0,	" DBG : Set Data Packet diff location"},
	{E_TO_S(HDMI20__DATAPACKET_USE_CHSUM_FILTER),	0x1, "0:Do not use SW CheckSum Filter, 1:Use Filter, 2:Type2 Filter"},
	{E_TO_S(HDMI20__SCDT_CHK_BYPASS),		0x0, "0:SCDT_CHK, 1:SCDC_CHECK_BYPASS"},
	{E_TO_S(HDMI20__PHY_TCS_MODESEL_WEIRD), 0x1, "1:Modesel RST on weird TCS min/max, 0:Off"},
	{E_TO_S(HDMI20__LINK_RST_CNT),		0x0, "Num of Link reset after signal recall"},
	{E_TO_S(HDMI20__PHY_TCS_6G_ALLMIN_THRES),	0x1, "Exception Case : For 6G, All TCS MIN value for exception approach "},
	{E_TO_S(HDMI20__PHY_TCS_6G_ALLMIN_ADDVAL),	0x8, "Exception Case : For 6G, ALL TCS MIN value exception Add val "},
	{E_TO_S(HDMI20__PHY_TCS_6G_ALLMAX_THRES),	0x1E, "Exception Case : For 6G, ALL TCS MIN value exception Add val "},
	{E_TO_S(HDMI20__PHY_EQ_BIAS_CURRENT),	0x4, "Value for EQ Bias Current Setting, Refer to reg-manual for specific"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_BOUNDARY), 0x10, "Value of TCS boundary on 3G domain "},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_BOUNDARY), 0x10,  "Value of TCS boundary on 6G domain "},
	{E_TO_S(HDMI20__PHY_EQ_TCS_BOUND0),		0x8, "Value of TCS Boundary #0"},
	{E_TO_S(HDMI20__PHY_EQ_TCS_BOUND1),		0x6, "Value of TCS Boundary #1"},
	{E_TO_S(HDMI20__PHY_EQ_TCS_BOUND2),		0x6, "Value of TCS Boundary #2"},
	{E_TO_S(HDMI20__PHY_EQ_TCS_BOUND3),		0x4, "Value of TCS Boundary #3"},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_BOUND_MAN),  0x0, "Set to 1 to manually set TCS Add val for 6G  boundary"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_BOUND_MAN),  0x0, "Set to 1 to manually set TCS Add val for 3G  boundary"},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_ADD_BOUND0),	0x6, "Value of 6G TCS manual Addval on  Boundary #0"},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_ADD_BOUND1),	0x2, "Value of 6G TCS manual Addval on Boundary #1"},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_ADD_BOUND2),	0x2, "Value of 6G TCS manual Addval on Boundary #2"},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_ADD_BOUND3),	0x2, "Value of 6G TCS manual Addval on Boundary #3"},
	{E_TO_S(HDMI20__PHY_EQ_6G_TCS_ADD_BOUND4),	0x2, "Value of 6G TCS manual Addval on Boundary #4"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_ADD_BOUND0),	0x8, "Value of 3G TCS manual Addval on Boundary #0"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_ADD_BOUND1),	0x8, "Value of 3G TCS manual Addval on Boundary #1"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_ADD_BOUND2),	0x8, "Value of 3G TCS manual Addval on Boundary #2"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_ADD_BOUND3),	0x8, "Value of 3G TCS manual Addval on Boundary #3"},
	{E_TO_S(HDMI20__PHY_EQ_3G_TCS_ADD_BOUND4),	0x8, "Value of 3G TCS manual Addval on Boundary #4"},
	{E_TO_S(HDMI20__PHY_ENABLE_MANUAL_EQ),		0x0, "PORT 0 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI20__PHY_MANUAL_TCS_ADDVAL_CH0), 0x6, "PORT 0 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI20__PHY_MANUAL_TCS_ADDVAL_CH1), 0x6, "PORT 0 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI20__PHY_MANUAL_TCS_ADDVAL_CH2), 0x6, "PORT 0 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI20__PHY_TCS_SOM_MIN_OVER_THRES),	0x4, "Exception Case #5 : Set DFE B level to active when atleast on tcs min high"},
	{E_TO_S(HDMI20__FORCE_DCM_8_BIT_ON_594),		0x1, "Set to 1 to force deepcolor mode to 8bit on 594MHz with Hsync over 3800"},
	{E_TO_S(HDMI20__HPD_TG_ON_6G_297),	0x0, "Set count HPD SW WA where over 200MHz is detected but SCDC is 6G"},
	{E_TO_S(HDMI20__HPD_TG_ON_6G_297_TMDS_CLK),	20000, "TMDS Threshold value for -200MHz- over 6G SW WA"},
	{E_TO_S(HDMI20__LINK_REG_0XFF0_RESET_VALUE_1), 	0xFEFA,	" Reset value for LINK reset register on case #1"},
	{E_TO_S(HDMI20__PHY_CHARGE_PUMP_ADJ_0), 	0x3, " Phy Charge Pump ADJ #0"},
	{E_TO_S(HDMI20__PHY_CHARGE_PUMP_ADJ_1), 	0x3, " Phy Charge Pump ADJ #1"},
	{E_TO_S(HDMI20__PHY_CHARGE_PUMP_ADJ_2), 	0x3, " Phy Charge Pump ADJ #2"},
	{E_TO_S(HDMI20__PHY_CHARGE_PUMP_ADJ_3), 	0x5, " Phy Charge Pump ADJ #3"},
	{E_TO_S(HDMI20__LINK_AMD_FREESYNC_MODE), 		1,  " [0]:Detection OFF(Force Off) / [1]: Auto / [2]:Force ON  "},
	{E_TO_S(HDMI20__PHY_PDB_ON_DELAY_TIME),			0, " Delay for PHY PDB ON"},
	{E_TO_S(HDMI20__LINK_HPD_DELAY_TIME),			0, " Delay for HPD ON"},
	{E_TO_S(HDMI20__PHY_TCS_NEW_ADD_VAL),			0x3, "New TCS Add Val"},
	{E_TO_S(HDMI20__LINK_USE_TCS_DONE_APB),			0, "1:Use TCS Done from Link APB, 0:Use from Phy I2C"},
	{E_TO_S(HDMI20__LINK_USE_TMDS_CLK_APB),			1, "1:USE TMDS CLK from Link APB, 0:Use from PHY I2C"},
	{E_TO_S(HDMI20__LINK_PHY_TMDS_CLOCK_MEAS),		0x960, "TMDS Clk sample base clock setting"},
	{E_TO_S(HDMI20__PHY_DELTA_MODE2),				0x0, 	" Set 1 for DELTA MODE 2 ON"},
	{E_TO_S(HDMI20__FORCE_COLOR_SAMPLE_PACKET),	0, "0:Auto, 1~3:BT601,BT709,BT2020(NCL)"},
	{E_TO_S(HDMI20__PHY_CH0_DFE_B1_BEFORE_TCS),		0x0, "DFE B1 level CH0 before TCS Done"},
	{E_TO_S(HDMI20__PHY_CH1_DFE_B1_BEFORE_TCS),		0x0, "DFE B1 level CH1 before TCS Done"},
	{E_TO_S(HDMI20__PHY_CH2_DFE_B1_BEFORE_TCS),		0x0, "DFE B1 level CH2 before TCS Done"},
	{E_TO_S(HDMI20__PHY_CH0_DFE_B1_AFTER_TCS),		0x0, "DFE B1 level CH0 after TCS Done"},
	{E_TO_S(HDMI20__PHY_CH1_DFE_B1_AFTER_TCS),		0x0, "DFE B1 level CH0 after TCS Done"},
	{E_TO_S(HDMI20__PHY_CH2_DFE_B1_AFTER_TCS),		0x0, "DFE B1 level CH0 after TCS Done"},
	{E_TO_S(HDMI20__PHY_TMDS_EXCEPTION_2_LOW), 		8000, 	" Exception Case 2 for PHY MODE Sel TMDS LOW Threshold"},
	{E_TO_S(HDMI20__PHY_TMDS_EXCEPTION_2_HIGH), 	16000, 	" Exception Case 2 for PHY MODE Sel TMDS HIGH Threshold"},
	{E_TO_S(HDMI20__PHY_TMDS_EXCEPTION_2_ADDVAL),	0x0,    "Delta Scan 2 mode +alpha val"},
	{E_TO_S(HDMI20__USE_MW_HOSTERROR_CTRL), 		0x0,	"Set 1 to enable MW control for Error Thres"},
	{E_TO_S(HDMI20__ENABLE_RESERVE_PDEC_PARSE), 	0x1, 	"Set 1 to enable PDEC Parsing on Reserved"},
	{E_TO_S(HDMI20__RESERVE_PDEC_PARSE_HEADER), 	0x7F, 	"PDEC Reserved Parse Header Value"},
	{E_TO_S(HDMI20__PHY_SWWA_DELTASCAN2_ADD_MANUALEQ),	0x6, "Add Value on TCS Result(DeltaScan2)"},
	{E_TO_S(HDMI20__PHY_P1_ENABLE_MANUAL_EQ),		0x0, "PORT 1 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH0),  0x6, "PORT 1 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH1),  0x6, "PORT 1 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH2),  0x6, "PORT 1 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI20__PHY_P2_ENABLE_MANUAL_EQ),		0x0, "PORT 2 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH0),  0x6, "PORT 2 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH1),  0x6, "PORT 2 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH2),  0x6, "PORT 2 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI20__PHY_P3_ENABLE_MANUAL_EQ),		0x0, "PORT 3 : Set to 1 to manually set the TCS add val"},
	{E_TO_S(HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH0),  0x6, "PORT 3 : If Manual_EQ is enable, value of TCS CH0"},
	{E_TO_S(HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH1),  0x6, "PORT 3 : If Manual EQ is enable, value of TCS CH1"},
	{E_TO_S(HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH2),  0x6, "PORT 3 : If Manual EQ is enable, value of TCS CH2"},
	{E_TO_S(HDMI20__ENABLE_ISR_PROFILER),			0x0, "Set value for ISR profiler base iteration value"},
	{E_TO_S(HDMI20__ISR_PROFILER_TYPE),	HDMI20_ISR_MAXNUM, "Value for ISR Profiler ISR Type"},
	{E_TO_S(HDMI20__LINK_REG_0X140_HA_THRESHOLD), 0x00000110 ," The Value for Link 0x140 register on link reset"},
	{E_TO_S(HDMI20__PHY_CED_CHECK_LENGTH), 0x2 ," if CED is Enabled, legnth of CED Checking"},
	{E_TO_S(HDMI20__LINK_ALLM_TIMEOUT), 1000, "ALLM Timeout(msec), if 0, then no timeout"},
	{E_TO_S(HDMI20__PHY_TCS_WAIT_PAK_CHK_ON), 0x0, " Turn this to 0x1, with SCDT_ON. Wait TCS until DataPacket"}
};

LX_HDMI20_ERROR_SETTING_T kdrvHDMI20ErrorThres[LX_HDMI20_ERROR_MAXNUM] =
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

UINT32 gAdditionalHpdLowDuration = 0; // Request from TV Lab. Jihoon Lee

HDMI20_HOST_DIAGNOSIS_ERROR_T gHDMIhostError[HDMI20_NUM_OF_RX_PORTS];
/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
/* Function needed inside for HDMI20 HAL */
static int __HDMI20_HAL_IsHwInDVIState(UINT8 port);
static void __HDMI20_HAL_Rx_Init_Dev_Handler(UINT8 isResume);
static int __HDMI20_HAL_SetPVOMode(UINT8 port, UINT8 isPVO);
static int __HDMI20_HAL_IsPVOMode(UINT8 port);

/* System Function wrapper */
static int __HDMI20_Spin_Init(void *handler);
static int __HDMI20_Spin_IRQ_Lock(void *handler, unsigned long *flags);
static int __HDMI20_Spin_IRQ_UnLock(void *handler, unsigned long flags);
static int __HDMI20_Destory_Spinlock(void *handler);


/* Function for IOCTL */
static int __HDMI20_HAL_Rx_UnInitialize(void);
static int __HDMI20_HAL_Rx_Get_AKSVData(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size);
static int __HDMI20_HAL_Rx_Get_SrcDeviceInfo(UINT8 port, LX_HDMI20_SRCINFO_T *pData, int size);
static int __HDMI20_HAL_Rx_Set_ResetTimingInfo(void);
static int __HDMI20_HAL_Rx_Get_HDCP14(UINT8 port, UINT32 *pData, int size);
static int __HDMI20_HAL_Rx_Set_EnableHPD(UINT8 port ,UINT8 onOff, UINT8 force, UINT32 callerId);
static int __HDMI20_HAL_Rx_Set_EnableEDID(UINT8 onOff);

static int __HDMI20_HAL_SetPioneerMode(void);
static int __HDMI20_HAL_DBG_GetHDMIMiscInfo(UINT8 port, LX_HDMI20_RX_HDMI_MISC_T *pData, int size);
static int __HDMI20_HAL_Rx_Set_HDCP14_KSVList(UINT8 port, LX_HDMI20_HDCP14_RP_T *pData, int size);

static int __HDMI20_HAL_Rx_GetHDMIState(UINT8 port, LX_HDMI_STATUS_T *pHdmiStatus, int size);
static int __HDMI20_HAL_Rx_Set_HDCP22Info(UINT8 port, int isInitiated);
static int __HDMI20_HAL_Set_HDMI_Factor(LX_HDMI20_SETTING_FACTOR_T *pData, int size);
static int __HDMI20_HAL_Set_HDMI_HostErrorThres(LX_HDMI20_ERROR_SETTING_T *pData, int size);
static int __HDMI20_HAL_Get_HDMI_HostError(UINT8 port, UINT32 *pData, int size);

/* DBG */
static void __HDMI20_HAL_Rx_DBG_PrintHandler(HDMI20_HAL_RX_DEVICE_DATA *handler);
static void __HDMI20_HAL_Rx_DBG_PrintVideo(HDMI20_HAL_RX_DEVICE_DATA *handler);
static void __HDMI20_HAL_DBG_PrintPixelCRCMonitor(UINT8 port, UINT8 diffmode);
static void __HDMI20_HAL_DBG_PrintECCMonitor(UINT8 port);
static void __HDMI20_HAL_Rx_DBG_PrintSavedEDID(UINT8 port);

static int __HDMI20_HAL_DBG_PrintDevController(HDMI20_DEV_CONTROL_LIST_T index);
static int __HDMI20_HAL_DBG_PrintDevAudController(HDMI20_DEV_AUD_CONTROL_LIST_T index);


/* Main Thread */
static void __HDMI20_HAL_MainThread(void);



/* Internal static usage functions */
static void __HDMI20_HAL_DBG_PrintSyncMonitor(UINT8 port, UINT8 diffmode);
static void __HDMI20_HAL_UpdateSCDC(UINT8 port);
static void __HDMI20_HAL_SetVideoColorDomain(UINT8 port);
static void __HDMI20_HAL_TestPattern(UINT8 port, int isUD, int isOn);
static void __HDMI20_HAL_Rx_ResetSyncPosition(UINT8 port, HDMI20_SYNOPSYS_CEA_RST_MODE_T mode, UINT32 caller_id);
static void __HDMI20_HAL_Rx_CheckSCDC(UINT8 port);
static int __HDMI20_HAL_Rx_ListOfNotSupportingVideo(UINT8 port);
static void __HDMI20_HAL_CheckVideoColorDomain(UINT8 port);
static void __HDMI20_HAL_Rx_InitiateHDMI20Data(UINT8 port, int isCablePlug);
static int __HDMI20_HAL_Set_InverseHPDControl(UINT8 port, int isInverse);
static UINT32 __HDMI20_HAL_Rx_VICcodeToVfreqConversion(UINT32 vicCode);
static void __HDMI20_HAL_Rx_Operation_Video_Change(UINT8 port);
static void __HDMI20_HAL_Rx_Operation_TMDS_Change(UINT8 port, int isforceSet);
static void __HDMI20_HAL_Rx_Operation_Audio_Change(UINT8 port);
static void __HDMI20_HAL_Rx_Operation_AKSV_Change(UINT8 port);
static int __HDMI20_HAL_Rx_Set_CountryInfo(UINT8 port, UINT8 *pData, int size);

static UINT32 __HDMI20_HAL_Rx_ALED_TOP_Read(UINT32 addr);
static void   __HDMI20_HAL_Rx_ALED_TOP_Write(UINT32 addr, UINT32 data);

static int	__HDMI20_HAL_Rx_CatchPC(UINT8 port);
/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/
static unsigned int *gMapped_address; // For DBG: REG Read/Write macro

/* For device supporitng 3D without VSI */
static const HDMI20_NON_VSI_3D_TIMING_T TBL_EXT_INFO[ ] =
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

/*========================================================================================
  Implementation Group
  ========================================================================================*/

/*========================================================================================
  Implementation Group
  ========================================================================================*/
void HDMI20_Set_Line_Debugger(UINT32 value)
{
	gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value = value;
	return;
}

UINT32 HDMI20_Get_Line_Debugger(void)
{
	return gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value ;
}


void HDMI20_Set_Audio_Line_Debugger(UINT32 value)
{
	gHDMI20RxDevAudControler[HDMI20__VIDEO_LINE_DEBUGGER].value = value;
	return;
}

UINT32 HDMI20_Get_Audio_Line_Debugger(void)
{
	return gHDMI20RxDevAudControler[HDMI20__VIDEO_LINE_DEBUGGER].value;
}

int HDMI20_Version(void)
{
	int ret = HDMI20_KERNEL_DRIVER_DATE;
	return ret;
}

int HDMI20_Open(void)
{
	/* Function that will be called before initialization */
	/* Important */
	int i, ret;
	UINT32 data;

	char *pwrModeSymbol = "pwrOnly";
	char *factoryModeSymbol = "factory";

	/* 2018/01/18 : Check Power only mode through /proc/cmdline which is symbolic saved to Linux kernel : saved_command_line */
	extern char *saved_command_line;

	if(gIsHDMI20KdrvOpen >= 0){
		HDMI20_INFO("Ignore Multiple Open\n");
		return 0;
	}


	/* Just to be sure */
	memset(&gZero19bytes, 0, 19);

	/* Step 1. Init Rx Device handler */
	HDMI20_INFO("Initiating HDMI20 device handler \n");
	__HDMI20_HAL_Rx_Init_Dev_Handler(0);

	/* Step 2. Ioremap HW to memory */
	HDMI20_INFO("Remapping HDMI20 device HW to memory \n");

	if(pISol_Addr0 == NULL){
		pISol_Addr0 = (volatile UINT32 *)ioremap(gHDMI20ChipRegHandler.isol_1_ADDR, sizeof(UINT32));
	}
	else{
		iounmap((void *)pISol_Addr0);
		pISol_Addr0 = (volatile UINT32 *)ioremap(gHDMI20ChipRegHandler.isol_1_ADDR, sizeof(UINT32));
	}

	if(pISol_Addr1 == NULL){
		pISol_Addr1 = (volatile UINT32 *)ioremap(gHDMI20ChipRegHandler.isol_2_ADDR, sizeof(UINT32));
	}
	else{
		iounmap((void *)pISol_Addr1);
		pISol_Addr1 = (volatile UINT32 *)ioremap(gHDMI20ChipRegHandler.isol_2_ADDR, sizeof(UINT32));
	}

	if(pISol_Addr2 == NULL){
		pISol_Addr2 = (volatile UINT32 *)ioremap(gHDMI20ChipRegHandler.isol_3_ADDR, sizeof(UINT32));
	}
	else{
		iounmap((void *)pISol_Addr2);
		pISol_Addr2 = (volatile UINT32 *)ioremap(gHDMI20ChipRegHandler.isol_3_ADDR, sizeof(UINT32));
	}


	if(sAledTop.pSwAddr == NULL) {
		sAledTop.pSwAddr = (volatile UINT32 *)ioremap(sAledTop.hwAddr, sAledTop.size);
	}
	else {
		iounmap((void *)sAledTop.pSwAddr);
		sAledTop.pSwAddr = (volatile UINT32 *)ioremap(sAledTop.hwAddr, sAledTop.size);
	}

	HDMI20_INFO("ALED TOP MAPPING : ORIGIN[0x%08x] / MAPPED[0x%p] / SIZE[0x%x] \n", (unsigned int)sAledTop.hwAddr, (void *)sAledTop.pSwAddr, (unsigned int)sAledTop.size);

	/* Step 2-1. Memory IO Remap for ALL Link & PHY */
	for(i = 0; i<HDMI20_NUM_OF_RX_PORTS; i++)
	{
		HDMI20_PHY_InitiatePhySystemCtrl(i);

		if(gHDMI20RxHandler[i].linkmem.pSwAddr == NULL) {
			gHDMI20RxHandler[i].linkmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].linkmem.hwAddr, gHDMI20RxHandler[i].linkmem.size);
		}
		else {
			iounmap((void *)gHDMI20RxHandler[i].linkmem.pSwAddr);
			gHDMI20RxHandler[i].linkmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].linkmem.hwAddr, gHDMI20RxHandler[i].linkmem.size);
		}

		if(gHDMI20RxHandler[i].topmem.pSwAddr == NULL) {
			gHDMI20RxHandler[i].topmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].topmem.hwAddr, gHDMI20RxHandler[i].topmem.size);
		}
		else {
			iounmap((void *)gHDMI20RxHandler[i].topmem.pSwAddr);
			gHDMI20RxHandler[i].topmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].topmem.hwAddr, gHDMI20RxHandler[i].topmem.size);
		}

		if(gHDMI20RxHandler[i].aledmem.pSwAddr == NULL) {
			gHDMI20RxHandler[i].aledmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].aledmem.hwAddr, gHDMI20RxHandler[i].aledmem.size);
		}
		else {
			iounmap((void *)gHDMI20RxHandler[i].aledmem.pSwAddr);
			gHDMI20RxHandler[i].aledmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].aledmem.hwAddr, gHDMI20RxHandler[i].aledmem.size);
		}

		HDMI20_INFO("ORIGIN RX[%d] : CTRL[0x%08x] / TOP[0x%08x] / ALED[0x%08x]  \n", i, (unsigned int)gHDMI20RxHandler[i].linkmem.hwAddr,  (unsigned int)gHDMI20RxHandler[i].topmem.hwAddr,  (unsigned int)gHDMI20RxHandler[i].aledmem.hwAddr);
		HDMI20_INFO("MAPPED RX[%d] : CTRL[0x%p] / TOP[0x%p] / ALED[0x%p]  \n", i, (void *)gHDMI20RxHandler[i].linkmem.pSwAddr,  (void *)gHDMI20RxHandler[i].topmem.pSwAddr,  (void *)gHDMI20RxHandler[i].aledmem.pSwAddr);

	
		memset((void *)&gHDMIhostError[i], 0, sizeof(HDMI20_HOST_DIAGNOSIS_ERROR_T));
	}

	HDMI20_Rx_Audio_Path_Init();
	HDMI20_Rx_Audio_RequestIrq();
	HDMI20_Rx_Audio_Path_Irq_Enable();


	/* O18 Only : Disable Clock for veri-purpose LG-HDMI-LINK, Only for HDMI port 0*/
	if (( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0)) && (lx_chip_rev ( ) < LX_CHIP_REV(M19, A0))) {
		HDMI20_INFO("Disabling Clock for LG-HDMI-LINK\n");
		HDMI20_REG_RD(0xC90FD000, data);
		data |= (0x00000780);
		HDMI20_REG_WR(0xC90FD000, data);
	}

	/* EDID */
	for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){
		HDMI20_INFO("Initiate Internal EDID Data for port[%d]\n", i);
		gHDMI20RxHandler[i].wasEdidWritten = 0;
		memset((void *)&gHDMI20RxHandler[i].edidData, 0, HDMI20_HAL_SIZE_OF_EDID);
	}


	/* SET DDC GPIO mode off */
	if  ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
		HDMI20_REG_RD(0xC9302018, data);
		data |= 0x00000090;
		HDMI20_REG_WR(0xC9302018, data);


		/* Set BusGating Off for HDCP2.2 engine */
		HDMI20_REG_RD(0xC930209C, data);
		data |= (0x000003FC);
		HDMI20_REG_WR(0xC930209C, data);

		HDMI20_INFO("Detected M17 C1 or higher. Turn Off Phy Phase SW WA\n");
		gHDMI20RxDevControler[HDMI20__PHY_SW_WA_FOR_PHASE].value = 0;

	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
		HDMI20_REG_RD(0xC7FE0010, data);
		data &= (~0x00000FC0);
		HDMI20_REG_WR(0xC7FE0010, data);

		if( lx_chip_rev( ) >= LX_CHIP_REV( O18, B0) ){
			HDMI20_INFO("Detected O18 B0 or higher. Turn Off Phy Phase SW WA\n");
			gHDMI20RxDevControler[HDMI20__PHY_SW_WA_FOR_PHASE].value = 0;

			HDMI20_INFO("Detected O18+Hwak2. Turn Off force 8 bit SW WA\n");
			gHDMI20RxDevControler[HDMI20__FORCE_DCM_8_BIT_ON_594].value = 0;
		}

		gHDMI20RxDevControler[HDMI20__LINK_USE_TMDS_CLK_APB].value = 0;
		gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value = 0;
		gHDMI20RxDevControler[HDMI20__PHY_DELTA_MODE].value = 0;
		gHDMI20RxDevControler[HDMI20__PHY_6G_TCS_ADD_VAL].value = 8;
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) ){
		HDMI20_REG_RD(0xC930C42C, data);
		data &= (~0x0007E000);
		HDMI20_REG_WR(0xC930C42C, data);

		if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C1) ){
			HDMI20_INFO("Detected M17 C1 or higher. Turn Off Phy Phase SW WA\n");
			gHDMI20RxDevControler[HDMI20__PHY_SW_WA_FOR_PHASE].value = 0;
		}

		gHDMI20RxDevControler[HDMI20__LINK_USE_TMDS_CLK_APB].value = 0;
		gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value = 0;
		gHDMI20RxDevControler[HDMI20__PHY_DELTA_MODE].value = 0;
		gHDMI20RxDevControler[HDMI20__PHY_6G_TCS_ADD_VAL].value = 8;
	}


	if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
		/* ISOL Release */
		gpiod_hdmi20 = gpiod_get(&hdmi_gpio_dev, "140", GPIOD_OUT_HIGH);  
		HDMI20_INFO(" GPIOD = [0x%p]\n", gpiod_hdmi20);
		gpiod_set_raw_value(gpiod_hdmi20 ,1);	
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
		/* ISOL Release */
		data = *pISol_Addr1;
		data |= gHDMI20ChipRegHandler.isol_2_VAL;
		*pISol_Addr1 = data;

		data = *pISol_Addr2;
		data |= gHDMI20ChipRegHandler.isol_3_VAL;
		*pISol_Addr2 = data;

		data = *pISol_Addr0;
		data |= gHDMI20ChipRegHandler.isol_1_VAL;
		*pISol_Addr0 = data;	
		/* End of ISOL Release */
	}
	else {
		if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C0) ){
			/* M17 C0 */
			gpiod_hdmi20 = gpiod_get(&hdmi_gpio_dev, "39", GPIOD_OUT_HIGH);  
			HDMI20_INFO(" GPIOD = [0x%p]\n", gpiod_hdmi20);
			gpiod_set_raw_value(gpiod_hdmi20 ,1);	
		}
		else{
			/* M17 A0 */
			/* ISOL Release */
			data = *pISol_Addr1;
			data |= gHDMI20ChipRegHandler.isol_2_VAL;
			*pISol_Addr1 = data;

			data = *pISol_Addr2;
			data |= gHDMI20ChipRegHandler.isol_3_VAL;
			*pISol_Addr2 = data;

			data = *pISol_Addr0;
			data |= gHDMI20ChipRegHandler.isol_1_VAL;
			*pISol_Addr0 = data;	
			/* End of ISOL Release */
		}
	}
	
	/* ALED TOP : Set I2C driver clock sel : LG Tapbook DVI Issue at End of 2016 */
	HDMI20_INFO("<><><><><><> Before ALED 0x50 => [0x%08x]\n", __HDMI20_HAL_Rx_ALED_TOP_Read(0x50));
	__HDMI20_HAL_Rx_ALED_TOP_Write(0x50, 0x6);
	HDMI20_INFO("<><><><><><> After ALED 0x50 => [0x%08x]\n", __HDMI20_HAL_Rx_ALED_TOP_Read(0x50));


	/* I2C Clock Delay & PVO Setting */
	for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){
		/* I2C Clock Delay & PVO Setting */
		gHDMI20RxHandler[i].top_write(HDMI20_RX_AD_MAIN_I2C_DELAY, 0x00000001);
		__HDMI20_HAL_SetPVOMode(i, gHDMI20RxDevControler[HDMI20__USE_PVO_MODE_FOR_LINK].value);

		if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
			/* PHY TMDS Clock LINK APB Connection, Clock sampling Clock configuration */
			gHDMI20RxHandler[i].top_write(HDMI20_RX_AD_CLK_MEAS_HDMI_REF_BASE_CLK,gHDMI20RxDevControler[HDMI20__LINK_PHY_TMDS_CLOCK_MEAS].value);
			
			//data = gHDMI20RxHandler[i].top_read(HDMI20_RX_AD_INTR_EN);
			//data |=  HDMI20_RX_AD_INTR_PHY_INFO;
			//gHDMI20RxHandler[i].top_write(HDMI20_RX_AD_INTR_EN, data);
		}
	}


	/* Write Phy I2C Address for dev */
	data = gHDMI20RxHandler[1].top_read(HDMI20_RX_PHY_I2C);
	data |= 0x00000100;
	gHDMI20RxHandler[1].top_write(HDMI20_RX_PHY_I2C, data);

	data = gHDMI20RxHandler[2].top_read(HDMI20_RX_PHY_I2C);
	data |= 0x00000200;
	gHDMI20RxHandler[2].top_write(HDMI20_RX_PHY_I2C, data);

	data = gHDMI20RxHandler[3].top_read(HDMI20_RX_PHY_I2C);
	data |= 0x00000300;
	gHDMI20RxHandler[3].top_write(HDMI20_RX_PHY_I2C, data);

	HDMI20_INFO("Notice : Disabled PLL Stuck SW WA for  B0");
	gHDMI20RxDevControler[HDMI20__ENABLE_WA_MODESEL_STUCKCASE].value = 0;

	/* 2018/01/18 : Check Power only mode through /proc/cmdline which is symbolic saved to Linux kernel : saved_command_line */
	if(saved_command_line != NULL){
		if(strstr(saved_command_line, pwrModeSymbol) != NULL){
			HDMI20_INFO("Detected Power Only Mode. Disable 3G 4K 10M SW WA");
			gHDMI20RxDevControler[HDMI20__PHY_TCS_ALLMIN_TMDS_THRES].value = 99999;
		}
		else if(strstr(saved_command_line, factoryModeSymbol) != NULL){
			HDMI20_INFO("Detected Factory Mode. Disable 3G 4K 10M SW WA");
			gHDMI20RxDevControler[HDMI20__PHY_TCS_ALLMIN_TMDS_THRES].value = 99999;
		}
	}

	gIsHDMI20KdrvOpen = 1;
	ret = RET_OK;

	return ret;
}



int HDMI20_Suspend(void)
{
	int ret = RET_ERROR;
	UINT32 data;
	int i;
	int cnt = 50;	

	HDMI20_INFO("HDMI2.0 Kernel Driver Suspend Start\n");

	/*Audio CSD change interrupt disable*/
	HDMI20_Rx_Audio_Path_Irq_Disable();

	/* Kill Main Thread & wait for it to end */
	gHDMI20Thread.isAlive = 0;
	while(1)
	{
		if(gHDMI20Thread.stamp == 0){
			HDMI20_INFO("Success closing HDMI2.0 Main thread\n");
			ret = RET_OK;
			break;
		}

		if(cnt <= 0)
		{
			HDMI20_INFO("Failed to exit HDMI2.0 Main thread\n");
			break;
		}
		cnt--;
		msleep(gHDMI20Thread.mSleep);
	}

	for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){
		HDMI20_HAL_Rx_Set_AudioReset(i);
	
		gHDMI20RxHandler[i].gWasHDCP22Written = 0;
		gHDMI20RxHandler[i].gWasHDCP22FuncCalled = 0;

		/* HPD control */
		HDMI20_INFO(" Pull down HPD for HDMI2.0 port[%d]\n", i);
		__HDMI20_HAL_Rx_Set_EnableHPD(i, 0, 0, __L__);

		/* webos 5V popup sign control */
		gHDMI20RxHandler[i].connected5Vtime = 0;
		gHDMI20RxHandler[i].stablehdcp14time = 0;

		__HDMI20_HAL_Rx_InitiateHDMI20Data(i, 0);

		/* Clear Timing Info */
		HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 1, __L__);
		
		/* 2018/11/16 */
		HDMI20_HAL_Rx_Set_Audio_Configure(i, 0);
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
		/* Need to fill in */
		gpiod_set_raw_value(gpiod_hdmi20 ,0);	
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
		/* ISOL */
		/* Do nothing for ISOL 1, because its just GPIO/SPI setting */
		/* Do not change GPIO mode to input, or ISOL can fail to HW reasons */
		data = *pISol_Addr2;
		data &= (~gHDMI20ChipRegHandler.isol_3_VAL);
		*pISol_Addr2 = data;	
		/* end of ISOL */
	}
	else {
		if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C0) ){
			/* M17 C0 */
			gpiod_set_raw_value(gpiod_hdmi20 ,0);	
		}
		else{
			data = *pISol_Addr2;
			data &= (~gHDMI20ChipRegHandler.isol_3_VAL);
			*pISol_Addr2 = data;	
		}
	}

	gHDMI20RxDevControler[HDMI20__NUMBER_OF_ACTIVATED_LINK].value = 0;

	return ret;
}


int HDMI20_Resume(void)
{
	int i;
	UINT32 data;

	HDMI20_INFO("HDMI2.0 Kernel Driver Resume Start\n");


	if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
		HDMI20_REG_RD(0xC9302018, data);
		data |= 0x00000090;
		HDMI20_REG_WR(0xC9302018, data);
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
/* O18 Only : Disable Clock for veri-purpose LG-HDMI-LINK, Only for HDMI port 0*/
		HDMI20_INFO("Disabling Clock for LG-HDMI-LINK\n");
		HDMI20_REG_RD(0xC90FD000, data);
		data |= (0x00000780);
		HDMI20_REG_WR(0xC90FD000, data);

		HDMI20_INFO("Detected O18+Hwak2. Turn Off force 8 bit SW WA\n");
		gHDMI20RxDevControler[HDMI20__FORCE_DCM_8_BIT_ON_594].value = 0;
	}

	if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ){
		/* M17 C0 */
		gpiod_set_raw_value(gpiod_hdmi20 ,1);	
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
		/* ISOL Release */
		data = *pISol_Addr1;
		data |= gHDMI20ChipRegHandler.isol_2_VAL;
		*pISol_Addr1 = data;

		data = *pISol_Addr2;
		data |= gHDMI20ChipRegHandler.isol_3_VAL;
		*pISol_Addr2 = data;

		data = *pISol_Addr0;
		data |= gHDMI20ChipRegHandler.isol_1_VAL;
		*pISol_Addr0 = data;	
		/* End of ISOL Release */
	}
	else {
		if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C0) ){
			/* M17 C0 */
			gpiod_set_raw_value(gpiod_hdmi20 ,1);	
		}
		else{
			/* M17 A0 */
			/* ISOL Release */
			data = *pISol_Addr1;
			data |= gHDMI20ChipRegHandler.isol_2_VAL;
			*pISol_Addr1 = data;

			data = *pISol_Addr2;
			data |= gHDMI20ChipRegHandler.isol_3_VAL;
			*pISol_Addr2 = data;

			data = *pISol_Addr0;
			data |= gHDMI20ChipRegHandler.isol_1_VAL;
			*pISol_Addr0 = data;	
			/* End of ISOL Release */
		}
	}

	__HDMI20_HAL_Rx_Init_Dev_Handler(1);

	/* I2C Clock Delay */
	for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){
		gHDMI20RxHandler[i].top_write(HDMI20_RX_AD_MAIN_I2C_DELAY, 0x00000001);
		__HDMI20_HAL_SetPVOMode(i, gHDMI20RxDevControler[HDMI20__USE_PVO_MODE_FOR_LINK].value);
	}

	/* SET DDC GPIO mode off */
	if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ){


		/* Set BusGating Off for HDCP2.2 engine */
		HDMI20_REG_RD(0xC930209C, data);
		data |= (0x000003FC);
		HDMI20_REG_WR(0xC930209C, data);
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
		HDMI20_REG_RD(0xC7FE0010, data);
		data &= (~0x00000FC0);
		HDMI20_REG_WR(0xC7FE0010, data);

		if( lx_chip_rev( ) >= LX_CHIP_REV( O18, B0) ){
			HDMI20_INFO("Detected O18 B0 or higher. Turn Off Phy Phase SW WA\n");
			gHDMI20RxDevControler[HDMI20__PHY_SW_WA_FOR_PHASE].value = 0;
		}
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) ){
		HDMI20_REG_RD(0xC930C42C, data);
		data &= (~0x0007E000);
		HDMI20_REG_WR(0xC930C42C, data);

		if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C1) ){
			HDMI20_INFO("Detected M17 C1 or higher. Turn Off Phy Phase SW WA\n");
			gHDMI20RxDevControler[HDMI20__PHY_SW_WA_FOR_PHASE].value = 0;
		}
	}

	/* ALED TOP : Set I2C driver clock sel : LG Tapbook DVI Issue at End of 2016 */
	/* Reactivate Watch dog on DC ON */
	gIsALEDIssueSolved = 0;

	HDMI20_INFO("<><><><><><> Before ALED 0x50 => [0x%08x]\n", __HDMI20_HAL_Rx_ALED_TOP_Read(0x50));
	__HDMI20_HAL_Rx_ALED_TOP_Write(0x50, 0x6);
	HDMI20_INFO("<><><><><><> After ALED 0x50 => [0x%08x]\n", __HDMI20_HAL_Rx_ALED_TOP_Read(0x50));

	data = gHDMI20RxHandler[1].top_read(HDMI20_RX_PHY_I2C);
	data |= 0x00000100;
	gHDMI20RxHandler[1].top_write(HDMI20_RX_PHY_I2C, data);

	data = gHDMI20RxHandler[2].top_read(HDMI20_RX_PHY_I2C);
	data |= 0x00000200;
	gHDMI20RxHandler[2].top_write(HDMI20_RX_PHY_I2C, data);

	data = gHDMI20RxHandler[3].top_read(HDMI20_RX_PHY_I2C);
	data |= 0x00000300;
	gHDMI20RxHandler[3].top_write(HDMI20_RX_PHY_I2C, data);

	/* Reset HDCP22 initiated info */
	for(i = 0; i<HDMI20_NUM_OF_RX_PORTS; i++)
	{
		gHDMI20RxHandler[i].gWasHDCP22Written = 0;
		gHDMI20RxHandler[i].gWasHDCP22FuncCalled = 0;
	
		/* HDCP2.2 Write PUK*/
		gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_1, HDMI20_PUK_1);
		gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_2, HDMI20_PUK_2);
		gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_3, HDMI20_PUK_3);
		gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_4, HDMI20_PUK_4);

		gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_1, HDMI20_RX_DUK_1);
		gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_2, HDMI20_RX_DUK_2);
		gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_3, HDMI20_RX_DUK_3);
		gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_4, HDMI20_RX_DUK_4);

		/* SW Workaround for ACR pll mode */
		gHDMI20RxHandler[i].top_write(HDMI20_RX_ACR_PLL_MODE, 0x10001 );
	
		/* Enable 5V IRQ */
		gHDMI20RxHandler[i].control_top_irq(1);

		/* Check 5V status for both port due to unknown state */
		gHDMI20RxHandler[i].resetSyncMonitor();

		/* 6G TG HPD over 200MHz Initiate value */
		gHDMI20RxHandler[i].countOf6GHpdTgSwWa = gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value;
	
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
			/* PHY TMDS Clock LINK APB Connection, Clock sampling Clock configuration */
			gHDMI20RxHandler[i].top_write(HDMI20_RX_AD_CLK_MEAS_HDMI_REF_BASE_CLK,gHDMI20RxDevControler[HDMI20__LINK_PHY_TMDS_CLOCK_MEAS].value);
		}
	}

	/* Restore HDMI Thread */
	if(gHDMI20Thread.isAlive <= 0){
		gHDMI20Thread.isAlive = 1;
		gHDMI20Thread.pThread= kthread_create( (void *)__HDMI20_HAL_MainThread, 0, "hdmi20_rx_video_stable_checker");
		if(gHDMI20Thread.pThread){
			HDMI20_INFO("Initialing VIDEO Stable checker thread\n");
			wake_up_process(gHDMI20Thread.pThread);
		}else HDMI20_ERROR("Cannot initiate Video stablizor thread\n");
	}
	else{
		HDMI20_INFO("Warning! : Will not create HDMI Stable checker thread due to it is already ALIVE!\n");
	}

	/* Accumulate HDMI count of resume */
	gHDMI20RxDevControler[HDMI20__COUNT_OF_RESUME].value++;

	/*Audio CSD change interrupt Enable*/
	HDMI20_Rx_Audio_Path_Irq_Enable();
	
	HDMI20_INFO("HDMI2.0 Kernel Driver Resume End. Accumulated Resume cnt[%d]\n", gHDMI20RxDevControler[HDMI20__COUNT_OF_RESUME].value);
	
	return RET_OK;
}

int HDMI20_Process_Cmd(LX_HDMI20_CMD_T* cmd)
{
	int ret = RET_OK;
	int i;
	UINT32 data;
	int cmd_result = HDMI20_CMD_STATUS_CMD_ERROR;

	do{
		/* Step 1. pharse cmd */
		switch(cmd->command)
		{
			case HDMI20_CMD_RX_INITIALIZE:
				{
					cmd_result = HDMI20_HAL_Rx_Initialize((LX_HDMI20_INIT_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_UNINITIALIZE	:
				{
					cmd_result = __HDMI20_HAL_Rx_UnInitialize();
				}
				break;

			case HDMI20_CMD_RX_GET_TIMINGINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_TimingInfo((UINT8)cmd->attributes, (LX_HDMI_TIMING_INFO_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_AVIINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_AVIInfo((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_SPDINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_SPDInfo((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_VSIINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_VSIInfo((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size, 0, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_COLORINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_COLORInfo((UINT8)cmd->attributes, (LX_HDMI_COLOR_DOMAIN_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_AKSVDATA	:
				{
					cmd_result = __HDMI20_HAL_Rx_Get_AKSVData((UINT8)cmd->attributes, (LX_HDMI_INFO_PACKET_T *)cmd->handle, (int)cmd->size);
				}
				break;

			case HDMI20_CMD_RX_GET_PHYSTATUS:
				{
					cmd_result = HDMI20_PHY_Rx_Get_PHYStatus((LX_HDMI_PHY_INFORM_T *)cmd->handle, (int)cmd->size, (int)cmd->attributes, 0);
				}
				break;

			case HDMI20_CMD_RX_SET_RESETTIMINGINFO:
				{
					cmd_result = __HDMI20_HAL_Rx_Set_ResetTimingInfo();
				}
				break;

			case HDMI20_CMD_RX_SET_EDID	:
				{
					cmd_result = HDMI20_HAL_Rx_Set_EDID((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_EDID	:
				{
					cmd_result = HDMI20_HAL_Rx_Get_EDID((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_SET_HDCP14:
				{
					cmd_result = HDMI20_HAL_Rx_Set_HDCP14((UINT8)cmd->attributes, (UINT32 *)cmd->handle, (int)cmd->size, 0);
				}
				break;

			case HDMI20_CMD_RX_GET_HDCP14:
				{
					cmd_result = __HDMI20_HAL_Rx_Get_HDCP14((UINT8)cmd->attributes, (UINT32 *)cmd->handle, (int)cmd->size);
				}
				break;

			case HDMI20_CMD_RX_SET_ENABLEHPD:
				{
					cmd_result = __HDMI20_HAL_Rx_Set_EnableHPD((UINT8)cmd->attributes, (UINT8)cmd->size, 0, __L__);
				}
				break;

			case HDMI20_CMD_RX_SET_ENABLEEDID:
				{
					cmd_result = __HDMI20_HAL_Rx_Set_EnableEDID((UINT8)cmd->attributes);
				}
				break;

			case HDMI20_CMD_RX_DBG_TOOL:
				{
					cmd_result = HDMI20_HAL_Rx_DBG_Tool((int)cmd->compat_handle, (UINT8)cmd->attributes, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_GET_AUDIOINFO:
				{
					cmd_result = HDMI20_HAL_Rx_GetAudioInfo((UINT8)cmd->attributes, (LX_HDMI_AUDIO_INFO_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_GET_AUDIOCOPYINFO:
				{
					cmd_result = HDMI20_HAL_Rx_GetAudioCopyInfo((UINT8)cmd->attributes, (LX_HDMI_AUDIO_COPY_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_SET_HDMIARC:
				{
					if(cmd->handle == NULL) data = 0;
					else data = 1;

					cmd_result = HDMI20_HAL_Rx_Set_HDMIARC((UINT8)cmd->attributes, (BOOLEAN)data);
				}
				break;
			case  HDMI20_CMD_RX_SET_MUTE:
				{
					cmd_result = HDMI20_HAL_Rx_Set_AudioMute((UINT8)cmd->attributes, (LX_HDMI_MUTE_CTRL_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case  HDMI20_CMD_RX_GET_AUDIODBGINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_DebugAudioInfo((UINT8)cmd->attributes, (LX_HDMI_DEBUG_AUDIO_INFO_T *)cmd->handle, (int)cmd->size);
				}
				break;

			case HDMI20_CMD_RX_GET_ASPECTRATIO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_AspectRatio((UINT8)cmd->attributes, (LX_HDMI_ASPECTRATIO_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_GET_HDMISTATE:
				{
					cmd_result = __HDMI20_HAL_Rx_GetHDMIState((UINT8)cmd->attributes, (LX_HDMI_STATUS_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_HDCP22INFO:
				{
					cmd_result = __HDMI20_HAL_Rx_Set_HDCP22Info((UINT8)cmd->attributes, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_GET_SRCINFO:
				{
					cmd_result = __HDMI20_HAL_Rx_Get_SrcDeviceInfo((UINT8)cmd->attributes, (LX_HDMI20_SRCINFO_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_PHY_ACCESS:
				{
					cmd_result = HDMI20_PHY_Rx_AccessPhy((UINT8)cmd->attributes, (LX_HDMI20_PHY_ACCESS_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_OPEN:
				{
					cmd_result = HDMI20_Open();
				}
				break;
			case HDMI20_CMD_RX_SET_ENABLE_OPERATION:
				{
					if (lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
						gpiod_set_raw_value(gpiod_hdmi20 ,1);	
					}
					else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
						/* ISOL Release */
						data = *pISol_Addr1;
						data |= gHDMI20ChipRegHandler.isol_2_VAL;
						*pISol_Addr1 = data;

						data = *pISol_Addr2;
						data |= gHDMI20ChipRegHandler.isol_3_VAL;
						*pISol_Addr2 = data;

						data = *pISol_Addr0;
						data |= gHDMI20ChipRegHandler.isol_1_VAL;
						*pISol_Addr0 = data;	
						/* End of ISOL Release */
					}
					else {
						if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C0) ){
							/* M17 C0 */
							gpiod_set_raw_value(gpiod_hdmi20 ,1);	
						}
						else{
							/* M17 A0 */
							/* ISOL Release */
							data = *pISol_Addr1;
							data |= gHDMI20ChipRegHandler.isol_2_VAL;
							*pISol_Addr1 = data;

							data = *pISol_Addr2;
							data |= gHDMI20ChipRegHandler.isol_3_VAL;
							*pISol_Addr2 = data;

							data = *pISol_Addr0;
							data |= gHDMI20ChipRegHandler.isol_1_VAL;
							*pISol_Addr0 = data;	
							/* End of ISOL Release */
						}
					}

					gHDMI20RxDevControler[HDMI20__NUMBER_OF_ACTIVATED_LINK].value = HDMI20_NUM_OF_RX_PORTS;	
					/* ALED HPD SET UP */
					for(i = 0; i<HDMI20_NUM_OF_RX_PORTS; i++)
					{
						data = gHDMI20RxHandler[i].aled_read(HDMI20_RX_ALED_AD_HPD);
						data |= (HDMI20_RX_ALED_AD_HPD_SET_HPD);
						gHDMI20RxHandler[i].aled_write(HDMI20_RX_ALED_AD_HPD, data);
					}


					cmd_result = RET_OK;
				}
				break;
			case HDMI20_CMD_RX_ACCESS_DEV_CTRL:
				{
					cmd_result = HDMI20_HAL_DBG_AccessDevController((HDMI20_DEV_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_CTRL:
				{
					cmd_result = __HDMI20_HAL_DBG_PrintDevController((HDMI20_DEV_CONTROL_LIST_T)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_ACCESS_DEV_AUD_CTRL:
				{
					cmd_result = HDMI20_HAL_DBG_AccessDevAudController((HDMI20_DEV_AUD_CONTROL_LIST_T)cmd->attributes, (UINT8)cmd->size, (UINT32 *)cmd->handle, 0);
				}
				break;
			case HDMI20_CMD_RX_PRINT_DEV_AUD_CTRL:
				{
					cmd_result = __HDMI20_HAL_DBG_PrintDevAudController((HDMI20_DEV_AUD_CONTROL_LIST_T)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_SET_REVERSE_HPD:
				{
					if(cmd->handle != NULL) data = 1;
					else data = 0;

					cmd_result =  __HDMI20_HAL_Set_InverseHPDControl((UINT8)cmd->attributes ,data);
				}
				break;
			case HDMI20_CMD_RX_SET_PIONEER_PLAT:
				{
					cmd_result = __HDMI20_HAL_SetPioneerMode();
				}
				break;
			case HDMI20_CMD_RX_GET_DRMINFO:
				{
					cmd_result = HDMI20_HAL_Rx_Get_DRMInfo((UINT8)cmd->attributes, (LX_HDMI20_RX_DRM_PACKET_T *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_SET_RESTARTHPD:
				{
					cmd_result = HDMI20_HAL_Rx_Set_RestartHPD((UINT8)cmd->attributes);
				}
				break;
			case HDMI20_CMD_RX_SET_POWEROFF:
				{
					HDMI20_INFO("Notice : HDMI2.0 Power Down Called! Suspend Driver\n");
					cmd_result = HDMI20_Suspend();

				}
				break;
			case HDMI20_CMD_RX_SET_DISABLE_HDMI:
				{
					if(cmd->handle != NULL) data = 1;
					else data = 0;

					cmd_result = HDMI20_HAL_Rx_Set_DisableHDMI((UINT8)cmd->attributes, data);
				}
				break;
			case HDMI20_CMD_RX_SET_COUNTRYINFO:
				{
					cmd_result = __HDMI20_HAL_Rx_Set_CountryInfo((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (int)cmd->size );
				}
				break;
			case HDMI20_CMD_RX_GET_DEV_CTRL_CNT :
				{
					cmd_result = HDMI20_HAL_DVG_GetDevControllerCnt((HDMI20_DEV_CONTROL_TYPE_T)cmd->attributes, (int *)cmd->handle, 0);

				}
				break;
			case HDMI20_CMD_RX_GET_DEV_CTRL :
				{
					cmd_result = HDMI20_HAL_DVG_GetDevController((HDMI20_DEV_CONTROL_TYPE_T)cmd->attributes, (HDMI20_DEV_CONTROL_T *)cmd->handle, (int)cmd->size, 0);

				}
				break;
			case HDMI20_CMD_RX_GET_HDMI_MISC:
				{
					cmd_result = __HDMI20_HAL_DBG_GetHDMIMiscInfo((UINT8)cmd->attributes, (LX_HDMI20_RX_HDMI_MISC_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_HDCP14KSVLIST:
				{
					cmd_result = __HDMI20_HAL_Rx_Set_HDCP14_KSVList((UINT8)cmd->attributes, (LX_HDMI20_HDCP14_RP_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_HDMIFACTOR:
				{
					cmd_result = __HDMI20_HAL_Set_HDMI_Factor((LX_HDMI20_SETTING_FACTOR_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_SET_ERROR_THRES:
				{
					cmd_result = __HDMI20_HAL_Set_HDMI_HostErrorThres((LX_HDMI20_ERROR_SETTING_T *)cmd->handle, (int)cmd->size);

				}
				break;
			case HDMI20_CMD_RX_GET_ERROR:
				{
					cmd_result = __HDMI20_HAL_Get_HDMI_HostError((UINT8)cmd->attributes, (UINT32 *)cmd->handle, (int)cmd->size); 
				}
				break;
			case HDMI20_CMD_RX_GET_MULTIPLE_VSI:
				{
					cmd_result = HDMI20_HAL_Get_MultipleVSIPacket((UINT8)cmd->attributes, (LX_HDMI20_MULTIPLE_VSI_T *)cmd->handle, (int)cmd->size);
				}
				break;
			case HDMI20_CMD_RX_GET_CURRENT_VRR_FREQ:
				{
					cmd_result = HDMI20_HAL_Get_VrrCurrentVfreq((UINT8)cmd->attributes, (UINT16 *)cmd->handle, (int)cmd->size, 0);
				}
				break;
			case HDMI20_CMD_RX_GET_EMPACKET:
				{
					cmd_result = HDMI20_HAL_Rx_Get_EMPInfo((UINT8)cmd->attributes, (UINT8 *)cmd->handle, (LX_HDMI20_EMP_TYPE_T)cmd->size, 0);
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

int HDMI20_HAL_DVG_GetDevControllerCnt(HDMI20_DEV_CONTROL_TYPE_T type, int *pCnt, int isInternalCall)
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

				cnt = HDMI20__DEV_CONTROL_LIST_MAXNUM;
				break;
			case HDMI20_DEV_CONTROL_AUDIO : 
				cnt = HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM;
				break;
			default :
				/* Do nothing */
				break;
		}

		if(isInternalCall){
			memcpy((int *)pCnt, (int *)&cnt, sizeof(int));
			ret = RET_OK;
		}
		else{
			ret = copy_to_user((int *)pCnt, &cnt, sizeof(int));
		}

	} while(0);

	return ret;
}

int HDMI20_HAL_DVG_GetDevController(HDMI20_DEV_CONTROL_TYPE_T type, HDMI20_DEV_CONTROL_T *pDevCon, int size, int isInternalCall)
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

				cnt = HDMI20__DEV_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI20RxDevControler;
				break;
			case HDMI20_DEV_CONTROL_AUDIO : 
				cnt = HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM;
				pKdriverDevCon = (HDMI20_DEV_CONTROL_T *)&gHDMI20RxDevAudControler;
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


int HDMI20_HAL_DBG_AccessDevAudController(HDMI20_DEV_AUD_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;

	do{
		if(index >= HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){
			if(isInternalCall){
				memcpy((void *)&gHDMI20RxDevAudControler[index].value, (void *)data, sizeof(UINT32));
			}
			else{
				if(copy_from_user((void *)&gHDMI20RxDevAudControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI20RxDevAudControler from user\n");
					break;
				}
			}

		}
		else{
			if(isInternalCall) {
				memcpy((void *)data, (void *)&gHDMI20RxDevAudControler[index].value, sizeof(UINT32));
			}
			else{
				ret = copy_to_user((void __user *)data, (void *)&gHDMI20RxDevAudControler[index].value, sizeof(UINT32));
				if(ret) {
					HDMI20_ERROR("Copy Error to USER space for AccessDevAudController .\n");
					break;
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI20_HAL_DBG_AccessDevController(HDMI20_DEV_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;

	do{
		if(index >= HDMI20__DEV_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){
			if(isInternalCall){
				memcpy((void *)&gHDMI20RxDevControler[index].value, (void *)data, sizeof(UINT32));	
			}
			else{
				if(copy_from_user((void *)&gHDMI20RxDevControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI20RxDevControler from user\n");
					break;
				}
			}
		}
		else{
			if(isInternalCall) {
				memcpy((void *)data, (void *)&gHDMI20RxDevControler[index].value, sizeof(UINT32));
			}
			else {
				ret = copy_to_user((void __user *)data, (void *)&gHDMI20RxDevControler[index].value, sizeof(UINT32));
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


/* DBG function */
int HDMI20_HAL_Rx_DBG_Tool(int type, UINT8 port, int data)
{
	int temp0, i;
	
	if(port> HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Wrong Port selected[%d]\n", port);
		return RET_ERROR;
	}

	switch(type)
	{
		case 0:
			__HDMI20_HAL_Rx_DBG_PrintHandler(&gHDMI20RxHandler[port]);
			break;
		case 1:
			__HDMI20_HAL_Rx_DBG_PrintVideo(&gHDMI20RxHandler[port]);
			break;
		case 2:
			if(port < HDMI20_NUM_OF_RX_PORTS) {
				printk(" SYNOPSYS CTRL DBG : %d\n", hdmi_rx_ctrl_debug((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl));
			}
			break;
		case 3:
			__HDMI20_HAL_Rx_DBG_PrintSavedEDID(port);
			break;
		case 4:
			__HDMI20_HAL_DBG_PrintDevController(data);
			break;
		case 5:
			for(i=0;i<HDMI20_ISR_MAXNUM;i++){
				printk("ISR TYPE [%s] = [%d]\n", isr_type_to_str(i), gHDMI20RxHandler[port].ctrl.isr_count[i]);  
			}
			break;
		case 11:
			__HDMI20_HAL_Rx_Init_Dev_Handler(data);
			break;
		case 14:
			printk(" gAdditionalHpdLowDuration = %d\n", gAdditionalHpdLowDuration);
			break;
		case 15:
			gAdditionalHpdLowDuration = data;
			break;
		case 200:
			__HDMI20_HAL_Set_InverseHPDControl(port, data);
			break;
		case 811:
			gHDMI20Thread.mSleep = data;
			break;
		case 812:
			printk("Current Main thread sleep time is [%d]\n", gHDMI20Thread.mSleep);
			break;
		case 813:
			printk("Current Main thread status is [%d]\n", gHDMI20Thread.isAlive);
			break;
		case 814:
			gHDMI20Thread.isAlive = data;
			break;
		case 1001:
			gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value = data;
			break;
		case 1500:
			hdmi_rx_ctrl_packet_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);
			break;
		case 2000:
			HDMI20_HAL_ClearManualSyncSetting(port);
			break;
		case 3000:
			printk(" Was HDCP 1.4 port[%d] written? [%d]\n",port, gHDMI20RxHandler[port].gWasHDCP14Written);
			break;
		case 3001:
			printk(" Was HDCP 2.2 port[%d] written? [%d]\n",port, gHDMI20RxHandler[port].gWasHDCP22Written);
			break;
		case 3002:
			gHDMI20RxHandler[port].gWasHDCP14Written = data;
			break;
		case 3003:
			gHDMI20RxHandler[port].gWasHDCP22Written = data;
			break;
		case 5000:
			HDMI20_HAL_Packet_Store((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, data, 1);
			break;
		case 5001:
			HDMI20_HAL_Packet_Store((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, data, 0);
			break;
		case 6500:
			__HDMI20_HAL_Rx_Set_EnableHPD(port ,data, 0, __L__);
			break;
		case 6666:
			HDMI20_PrintDataPacketBuffer(data, port);
			break;
		case 6667:
			HDMI20_ResetDataPacketBuffer(data, port);
			break;
		case 6668:
			HDMI20_PrintEMPacketBuffer(data, port);
			break;
		case 6669:
			HDMI20_HAL_Rx_ResetEMPacketBuffer(data, port);
			break;
		case 8282:
			__HDMI20_HAL_Rx_ResetSyncPosition(port, data, __L__);
			break;
		case 8283:
			HDMI20_PHY_Reset_ModeSel(port, 1, __L__);
			HDMI20_PHY_Reset_ModeSel(port, 0, __L__);
			break;
		case 8384:
			HDMI20_PHY_ControlPhyPDB(port, data);
			break;
		case 8500:
			HDMI20_HAL_UpdateDCMMode(port, data, 1);
			break;
		case 9992:
			printk("HDMI1.4 PWR down and UP\n");
			hdmi_rx_ctrl_hdcp_reset((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, (const struct hdmi_rx_ctrl_hdcp *)&gHDMI20RxHandler[port].hdcp);
			hdmi_rx_ctrl_hdcp_config((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, (const struct hdmi_rx_ctrl_hdcp *)&gHDMI20RxHandler[port].hdcp);
			break;
		case 9997:
			hdmi_rx_ctrl_hdcp_config((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, (const struct hdmi_rx_ctrl_hdcp *)&gHDMI20RxHandler[port].hdcp);
			break;
		case 9998:
			if(data) { temp0 = 0xC; }
			else     { temp0 = 0x6; }
			printk("Change 3G/6G EQ mode = %d\n", HDMI20_PHY_Set_3G6G_Mode(port, 0, data, data, temp0));
			break;
		case 9999:
			printk("Reset LinkVideo\n");
			HDMI20_HAL_Rx_LinkVideoReset(port, data, __L__);
			break;
		case 20000:
			HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, data, __L__);
			if(data == 0)__HDMI20_HAL_SetVideoColorDomain(port);

			break;
		case 20001:
			HDMI20_HAL_Rx_Update_AudioCtsNparam(port, data);
			break;
		case 66666:
			printk("Force Suspend on HDMI2.0\n");
			HDMI20_Suspend();
			break;
		case 66667:
			printk("Force Resume on HDMI2.0\n");
			HDMI20_Resume();
			break;
		case 75000:
			gHDMI20RxHandler[port].isAudioARCMode = data;	
			break;
		case 75001:
			printk("gEnableARCControl[%d] = %d\n" ,port, gHDMI20RxHandler[port].isAudioARCMode);
			break;
		case 77777:
			__HDMI20_HAL_TestPattern(port, 0, data);
			break;
		case 77778:
			__HDMI20_HAL_TestPattern(port, 1, data);
			break;
		case 79998:
			HDMI20_HAL_Rx_Set_Audio_Configure(port, data);
			break;

		case 79999:
			hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);
			break;

		case 99999:
			if(port < HDMI20_NUM_OF_RX_PORTS) HDMI20_HAL_ClearChangeFlags(port);
			break;

		default :
			break;
	}

	return RET_OK;
}

/* DBG function */
void HDMI20_HAL_Rx_PROC_PrintSavedEDID(int port, struct seq_file* m)
{
	volatile HDMI20_HAL_RX_DEVICE_DATA *_p;
	int i = 0;
	UINT8 edid_data[HDMI20_HAL_SIZE_OF_EDID] = {0,};

	if(((unsigned int)port)>= HDMI20_NUM_OF_RX_PORTS){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}


	/* Get Handler */
	_p = &gHDMI20RxHandler[port];

	memcpy((void *)&edid_data, (void *)&_p->edidData, HDMI20_HAL_SIZE_OF_EDID);

	seq_printf(m, "=========================================================================================================================\n");
	seq_printf(m, "[0x00] |  [0x00] [0x01] [0x02] [0x03] [0x04] [0x05] [0x06] [0x07] [0x08] [0x09] [0x0A] [0x0B] [0x0C] [0x0D] [0x0E] [0x0F]\n");
	seq_printf(m, "=========================================================================================================================\n");

	for (i = 0; i < 16; i++) {
		if((i==0)||(i==8)){
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

int	HDMI20_HAL_Rx_Get_OperationStatus(UINT8 port, LX_HDMI20_OP_STATUS_T *pData)
{
	int ret = RET_ERROR;
	LX_HDMI20_OP_STATUS_T data;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		memset((LX_HDMI20_OP_STATUS_T *)&data, 0, sizeof(LX_HDMI20_OP_STATUS_T));

		if(gHDMI20RxHandler[port].ctrl.stable_cnt >= gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value) {
			data.isSteady = true;	
		}
		else {
			data.isSteady = false;	
		}


		if(gHDMI20RxHandler[port].timing_info.dvi > 0)	{		data.isDVI = true;  }
		else											{		data.isDVI = false; }

		if(gHDMI20RxHandler[port].restartHpdFlagUp > 0) {		data.isRestartState = true; }
		else 											{		data.isRestartState = false;}

		data.numOfActivePort = (UINT32)gHDMI20RxDevControler[HDMI20__NUMBER_OF_ACTIVATED_LINK].value;

		ret = RET_OK;
	} while(0);

	return ret;


}

LX_HDMI_DOLBY_STATE_T HDMI20_HAL_Rx_Get_IsDolbyHDR(UINT8 port)
{
	LX_HDMI_DOLBY_STATE_T ret = HDMI_DOLBY_STATE_OFF;

	do{

		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		ret =(LX_HDMI_DOLBY_STATE_T)gHDMI20RxHandler[port].isDolbyHDR;

	} while(0);

	return ret;
}


/* -------------------------------------------------------------------------------
 * Static Function below this line
 * ------------------------------------------------------------------------------- */
static int __HDMI20_HAL_IsPVOMode(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 data;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port(%d)]\n", port);
			break;
		}

		data = gHDMI20RxHandler[port].top_read(HDMI20_RX_AD_MAIN_PVO_CTRL);
		data &= (0x0000000F);

		if(data == 0x00000005){
			ret = RET_OK;
		}

	} while(0);

	return ret;
}

static int __HDMI20_HAL_SetPVOMode(UINT8 port, UINT8 isPVO)
{
	int ret = RET_ERROR;

	do{
		HDMI20_VIDEO("Notice %d : Set Link Output to PVO/CEA Mode => [%s]\n", port, isPVO?"PVO":"CEA");

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(isPVO){
			gHDMI20RxHandler[port].top_write(HDMI20_RX_AD_MAIN_PVO_CTRL, 0x00000015);
		}
		else{
			gHDMI20RxHandler[port].top_write(HDMI20_RX_AD_MAIN_PVO_CTRL, 0x00000006);
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

void HDMI20_HAL_ClearChangeFlags(UINT8 port)
{
	gHDMI20RxHandler[port].scdc_change = 0;
	gHDMI20RxHandler[port].video_change = 0;
	gHDMI20RxHandler[port].dcm_change = 0;
	gHDMI20RxHandler[port].audio_change = 0;
	gHDMI20RxHandler[port].tmds_change = 0;
	gHDMI20RxHandler[port].aksv_change = 0;
	gHDMI20RxHandler[port].hdcp22_auth_change = 0;
	gHDMI20RxHandler[port].hdcp22_ists_change = 0;
	gHDMI20RxHandler[port].stopedBetweenStablize = 0;
}

static int __HDMI20_HAL_SetPioneerMode(void)
{
	/* For PIONEER Platform, send up original timing info */
	HDMI20_INFO(" Set HDMI20 Driver to PIONEER Mode\n");
	//gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value = 0;

	return RET_OK;
}



static void __HDMI20_HAL_UpdateSCDC(UINT8 port)
{
	if(gHDMI20RxDevControler[HDMI20__FORCE_SCDC_INSERTION].value > 0){
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3939){
			HDMI20_DBG(" Disable Update SCDC on Port[%d]\n", port);
		}
		
		gHDMI20RxHandler[port].scdc_change = false;
		return;
	}

	if(gHDMI20RxHandler[port].phyInitiatedMode){
		if(HDMI20_HAL_IsSCDCvalueUD(port) == 0){
			gHDMI20RxHandler[port].scdc_change = true;
		}
	}
	else{
		if(HDMI20_HAL_IsSCDCvalueUD(port)){
			gHDMI20RxHandler[port].scdc_change = true;
		}
	}
}

int HDMI20_HAL_IsSCDCvalueUD(UINT8 port)
{
	int ret = 0;
	UINT32 scdc_value;

	if(gHDMI20RxHandler[port].ctrl.bsp_read == NULL)
	{
		HDMI20_ERROR("[%s:%d] Warning! HDMI20 device handler is NULL\n", __F__, __L__);
		scdc_value = 0;
	}
	else
	{
		if(gHDMI20RxDevControler[HDMI20__USE_SCDC_ISR].value > 0){
			scdc_value = gHDMI20RxHandler[port].isScdcUD;
		}
		else{
			scdc_value = gHDMI20RxHandler[port].ctrl.bsp_read(0x820);
			scdc_value &= 0x00020000;
		}
	}

	if(scdc_value) {ret = 1;}
	else {
		if(	gHDMI20RxDevControler[HDMI20__FORCE_SCDC_6G].value > 0){
			/* Force SCDC 6G mode debugger */
			ret = 1;	
		}
		else{ 
			ret = 0;
		}
	}


	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3939){
		HDMI20_DBG(" Current SCDC return is [%d]. Scdc was [0x%08x]\n", ret, scdc_value);
	}

	return ret;
}

static void __HDMI20_HAL_Rx_CheckSCDC(UINT8 port)
{
	int ret = 0;
	UINT8 lowFreqGain;
	UINT32 isScrambling;

	if(gHDMI20RxHandler[port].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return;
	}

	if(gHDMI20RxDevControler[HDMI20__FORCE_SCDC_INSERTION].value == 0){
		if(gHDMI20RxHandler[port].phyInitiatedMode != HDMI20_HAL_IsSCDCvalueUD(port))
		{
			HDMI20_VIDEO("Notice [%d] : ReInit Phy due to SCDC change from [%d] to SCDC[%d] \n", port,gHDMI20RxHandler[port].phyInitiatedMode,  HDMI20_HAL_IsSCDCvalueUD(port));

			HDMI20_ResetDataPacketBuffer(HDR, port);
			HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, port);

			if(gHDMI20RxHandler[port].phyInitiatedMode){
				HDMI20_VIDEO("Notice [%d] : SCDC 6G -> 3G operation activated\n", port);
			
				if((gHDMI20RxHandler[port].isHDCP22)&&(gHDMI20RxHandler[port].gWasHDCP22Written > 0)){
					HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
				}

				/* Clear Timing Info */
				HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 1, __L__);
				
				gHDMI20RxHandler[port].locking_time = 0;
				gHDMI20RxHandler[port].phyLostCnt = 0;
				gHDMI20RxHandler[port].phy_rst_request = 1;
				gHDMI20RxHandler[port].ctrl.stable_cnt = 0;
				HDMI20_HAL_Rx_LinkVideoReset(port, 0, __L__);

				__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);

				isScrambling = HDMI20_HAL_IsSCDCvalueUD(port);
				if(HDMI20_HAL_IsSCDCvalueUD(port)) lowFreqGain = gHDMI20RxDevControler[HDMI20__PHY_RS_GAIN_FOR_6G].value;
				else lowFreqGain = gHDMI20RxDevControler[HDMI20__PHY_RS_GAIN_FOR_3G].value;

				//ret = HDMI20_HAL_Rx_Initiate_Phy(port, HDMI20_HAL_IsSCDCvalueUD(port));
				ret = HDMI20_PHY_Set_3G6G_Mode(port, 0, HDMI20_HAL_IsSCDCvalueUD(port), isScrambling, lowFreqGain);
				if(ret<0){
					HDMI20_ERROR("Cannot change Phy mode[%d]. Return error from Phy change[%d]\n", port, ret);
				}
				__HDMI20_HAL_Rx_InitiateHDMI20Data(port, 0);
				
			}
			else{
				HDMI20_VIDEO("Notice [%d] : SCDC 3G -> 6G operation activated\n", port);

				if((gHDMI20RxHandler[port].isHDCP22)&&(gHDMI20RxHandler[port].gWasHDCP22Written > 0)){
					HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
				}

				gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
				if(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value > 0){
					msleep(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value);
				}

				isScrambling = HDMI20_HAL_IsSCDCvalueUD(port);
				if(HDMI20_HAL_IsSCDCvalueUD(port)) lowFreqGain = gHDMI20RxDevControler[HDMI20__PHY_RS_GAIN_FOR_6G].value;
				else lowFreqGain = gHDMI20RxDevControler[HDMI20__PHY_RS_GAIN_FOR_3G].value;

				//ret = HDMI20_HAL_Rx_Initiate_Phy(port, HDMI20_HAL_IsSCDCvalueUD(port));
				ret = HDMI20_PHY_Set_3G6G_Mode(port, 0, HDMI20_HAL_IsSCDCvalueUD(port), isScrambling, lowFreqGain);
				if(ret<0){
					HDMI20_ERROR("Cannot change Phy mode[%d]. Return error from Phy change[%d]\n", port, ret);
				}

				__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);

				gHDMI20RxHandler[port].ctrl.stable_cnt = 0;
				gHDMI20RxHandler[port].phyLostCnt = 0;
				gHDMI20RxHandler[port].phy_rst_request = 1;
				gHDMI20RxHandler[port].locking_time = 0;
			}

			gHDMI20RxHandler[port].audio_change = 1;
			HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
			gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
			/* Soft reset for iaudclk domain(dmi_sw_rst.aud_swreset) */
			gHDMI20RxHandler[port].ctrl.bsp_write(0xff0, 0x00000010);
			gHDMI20RxHandler[port].audioStableCnt = 0;
		}

		gHDMI20RxHandler[port].scdc_change  = false;

	}
	else{
		gHDMI20RxHandler[port].scdc_change  = false;

	}
}


static int __HDMI20_HAL_Set_InverseHPDControl(UINT8 port, int isInverse)
{
	int ret = RET_ERROR;

	do{
		HDMI20_VIDEO("Notice %d : Set HPD Polarity [%s]\n", port, isInverse?"Inverse":"Normal");

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(isInverse){
			gHDMI20RxHandler[port].isHPDInverseMode = true;
		}
		else{
			gHDMI20RxHandler[port].isHPDInverseMode = false;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI20_HAL_IsHPD_Up(UINT8 port)
{
	UINT32 hpd;

	hpd = gHDMI20RxHandler[port].ctrl.bsp_read(0x0) & 0x00000001;

	if(gHDMI20RxHandler[port].isHPDInverseMode){
		if(hpd) hpd = 0;
		else hpd = 1;
	}
	else{
		if(hpd) hpd = 1;
		else hpd = 0;
	}

	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1717){
		HDMI20_DBG("DBG [%d] : hpd[%d], Link0x0=>[0x%08x]\n", port, hpd, gHDMI20RxHandler[port].ctrl.bsp_read(0x0));
	}

	return hpd;
}

static void __HDMI20_HAL_DBG_PrintECCMonitor(UINT8 port)
{
	UINT32 data0;
	UINT32 data1;

	UINT32 ch0 = 0;
	UINT32 ch1 = 0 ;
	UINT32 ch2 = 0;

	data0 = gHDMI20RxHandler[port].ctrl.bsp_read(0x824);
	data1 = gHDMI20RxHandler[port].ctrl.bsp_read(0x828);

	if((data0 & 0x80000000) != 0){ ch0 = (data0 & 0x7FFF0000)>>16; }
	
	if((data1 & 0x00008000) != 0){ ch1 = (data1 & 0x00007FFF); }
	
	if((data1 & 0x80000000) != 0){ ch2 = (data1 & 0x7FFF0000)>>16; }

	HDMI20_DBG("DBG %d : CRC CH0[%d] CH1[%d] CH2[%d] | Data0[0x%08x] Data1[0x%08x]\n", port ,ch0, ch1, ch2, data0, data1);

}

static void __HDMI20_HAL_DBG_PrintSyncMonitor(UINT8 port, UINT8 diffmode)
{
	int i;
	static UINT32 __sPrevSyncData[HDMI20_NUM_OF_RX_PORTS][8];
	UINT32 currData[HDMI20_NUM_OF_RX_PORTS][8];
	int diff = 0;

	memset((UINT32 *)&currData, 0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS * 8));

	if(diffmode >=1 ){
		currData[port][0] = gHDMI20RxHandler[port].top_read(0x208);
		currData[port][1] = gHDMI20RxHandler[port].top_read(0x20C);
		currData[port][2] = gHDMI20RxHandler[port].top_read(0x210);
		currData[port][3] = gHDMI20RxHandler[port].top_read(0x214);
		currData[port][4] = gHDMI20RxHandler[port].top_read(0x408);
		currData[port][5] = gHDMI20RxHandler[port].top_read(0x40C);
		currData[port][6] = gHDMI20RxHandler[port].top_read(0x410);
		currData[port][7] = gHDMI20RxHandler[port].top_read(0x414);

		for(i=0; i<=7; i++){
			if(currData[port][i] != __sPrevSyncData[port][i]){
				diff++;	
			}
		}

		if(diff >= 1){
			HDMI20_DBG(" Rx[%d] Sync Changed[%d]. From  [0x%08x] / HS[0x%08x] / H[0x%08x] / [0x%08x] / [0x%08x] /  [0x%08x] / [0x%08x] / [0x%08x]\n",\
					port, diff, __sPrevSyncData[port][0], __sPrevSyncData[port][1], __sPrevSyncData[port][2], __sPrevSyncData[port][3], __sPrevSyncData[port][4], __sPrevSyncData[port][5], \
					__sPrevSyncData[port][6], __sPrevSyncData[port][7]); 
			HDMI20_DBG(" Rx[%d] Sync Changed[%d]. To  [0x%08x] / HS[0x%08x] / H[0x%08x] / [0x%08x] / [0x%08x] /  [0x%08x] / [0x%08x] / [0x%08x]\n",\
					port, diff , currData[port][0], currData[port][1], currData[port][2], currData[port][3], currData[port][4], currData[port][5], \
					currData[port][6], currData[port][7]); 

		}

		for(i=0; i<=7; i++){
			__sPrevSyncData[port][i] = currData[port][i];
		}
	}
	else{
		HDMI20_DBG(" Rx[%d] => [0x%08x] / HS[0x%08x] / H[0x%08x] / [0x%08x] / [0x%08x] /  [0x%08x] / [0x%08x] / [0x%08x]\n",port,\
				gHDMI20RxHandler[port].top_read(0x208),  gHDMI20RxHandler[port].top_read(0x20C),\
				gHDMI20RxHandler[port].top_read(0x210),  gHDMI20RxHandler[port].top_read(0x214),\
				gHDMI20RxHandler[port].top_read(0x408),  gHDMI20RxHandler[port].top_read(0x40C), gHDMI20RxHandler[port].top_read(0x410),\
				gHDMI20RxHandler[port].top_read(0x414));
	}		
	/* Reset Sync monitors */
	gHDMI20RxHandler[port].top_write(0x20C, 0);
	gHDMI20RxHandler[port].top_write(0x210, 0);
}


static void __HDMI20_HAL_DBG_PrintPixelCRCMonitor(UINT8 port, UINT8 diffmode)
{
	static UINT32 __sPrevCrcData[HDMI20_NUM_OF_RX_PORTS];

	UINT32 currData = 0;

	if(port >= HDMI20_NUM_OF_RX_PORTS)
	{
		HDMI20_ERROR(" ERR %d : Unsupported Port[%d]\n", port, port);
		return;
	}

	if(diffmode == 0){
		HDMI20_DBG(" Rx[%d] CRC => [0x%08x]\n", port,  gHDMI20RxHandler[port].top_read(0x1840));
	}
	else{
		currData = gHDMI20RxHandler[port].top_read(0x1840);
		if(currData != __sPrevCrcData[port]){
			HDMI20_DBG(" Rx[%d] CRC Monitor changed from [0x%08x] => [0x%08x]\n", port,  __sPrevCrcData[port], currData);
			__sPrevCrcData[port] = currData;
		}
	}
}


static void __HDMI20_HAL_MainThread(void)
{
	static UINT32 __sVideoSurgeCnt[HDMI20_NUM_OF_RX_PORTS];

	static UINT32 __sVideoSurgeHFlag[HDMI20_NUM_OF_RX_PORTS];
	static UINT32 __sVideoSurgeVFlag[HDMI20_NUM_OF_RX_PORTS];
	static UINT32 __sVideoSurgeVResult[HDMI20_NUM_OF_RX_PORTS];
	static UINT32 __sVideoSurgeHResult[HDMI20_NUM_OF_RX_PORTS];
	static UINT32 __sVideoSurgeMonitor[HDMI20_NUM_OF_RX_PORTS][10];
	static UINT32 __sVideoSurgeMonitor2[HDMI20_NUM_OF_RX_PORTS][10];

	int i,y,ret;
	int tx5Vconnected;
	//UINT32 tmdsVal;
	UINT32 data;
	UINT32 hpdWaitCnt[HDMI20_NUM_OF_RX_PORTS] = {0,};
	UINT32 datapacketUpdateTimer[HDMI20_NUM_OF_RX_PORTS] = {0,};
	UINT32 divider = 0;
	UINT32 hvtotal;
	UINT32 dbg_vfreq;
	UINT32 vtotal;
	UINT32 video_format;
	uintptr_t pEdidAddress = 0;
	UINT32 gcpCnt[HDMI20_NUM_OF_RX_PORTS] = {0,};
	unsigned int __t_counter_isr_profile = 0;

	UINT32 addr;
	UINT32 currentJiffiesMsec = 0;

	HDMI20_INFO("HDMI2.0 Main Thread Start \n");

	memset((UINT32 *)&__sVideoSurgeHFlag,	0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS));
	memset((UINT32 *)&__sVideoSurgeCnt, 	0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS));
	memset((UINT32 *)&__sVideoSurgeVResult, 0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS));
	memset((UINT32 *)&__sVideoSurgeHResult, 0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS));
	memset((UINT32 *)&__sVideoSurgeMonitor, 0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS * 10));
	memset((UINT32 *)&__sVideoSurgeMonitor2,0, (sizeof(UINT32) * HDMI20_NUM_OF_RX_PORTS * 10));
	
	gHDMI20Thread.stamp = 0;
	/* Important to sleep at least for 600msec with HPD down */
	for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){
		HDMI20_INFO("Force HPD down for 600msec on HDMI2.0 port [%d] \n", i);
		__HDMI20_HAL_Rx_Set_EnableHPD(i ,0, 1, __L__);
	}
	

	for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){

		__sVideoSurgeCnt[i] = 0;

		pEdidAddress = (uintptr_t)gHDMI20RxHandler[i].topmem.pSwAddr + (uintptr_t)HDMI20_HAL_RX_INTERNAL_EDID_OFFSET;
		if((unsigned int *)pEdidAddress != NULL){
			if(gHDMI20RxHandler[i].wasEdidWritten == 1){
				HDMI20_INFO("NOTI %d : Internal EDID was written before MainThread start\n", i); 
				ret = memcmp((void *)&gHDMI20RxHandler[i].edidData, (void*)pEdidAddress, HDMI20_HAL_SIZE_OF_EDID);
				if(ret == 0){
					HDMI20_INFO("NOTI %d : Current internal EDID is same as the written EDID\n", i);
				}
				else{
					HDMI20_INFO("NOTI %d : Current internal EDID is different as the written EDID[%d]\n", i, ret);
					addr = 	(UINT32)HDMI20_HAL_RX_INTERNAL_EDID_OFFSET;
					for(y=0; y<(HDMI20_HAL_SIZE_OF_EDID >> 2); y++){
						gHDMI20RxHandler[i].top_write(addr, gHDMI20RxHandler[i].edidData[y]);
						addr += 4;
					}
					HDMI20_INFO("NOTI %d : Update Internal EDID Data from the MW complete\n", i);
				}
			}
			else{
				HDMI20_INFO("NOTI %d : No EDID data was delivered to driver before Main Thread Start\n", i);
				memset_io((void *)pEdidAddress, 0, HDMI20_HAL_SIZE_OF_EDID);
			}
		}
		else{
			HDMI20_INFO("WARN %d :SKIP EDID verification due to NULL address pointer\n",i);
		}

		gHDMI20RxHandler[i].connected5Vtime = 0;
		gHDMI20RxHandler[i].stablehdcp14time = 0;

	}
	msleep(600 + gAdditionalHpdLowDuration);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
		gpiod_set_raw_value(gpiod_hdmi20 ,1);	
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
		/* ISOL Release */
		data = *pISol_Addr1;
		data |= gHDMI20ChipRegHandler.isol_2_VAL;
		*pISol_Addr1 = data;

		data = *pISol_Addr2;
		data |= gHDMI20ChipRegHandler.isol_3_VAL;
		*pISol_Addr2 = data;

		data = *pISol_Addr0;
		data |= gHDMI20ChipRegHandler.isol_1_VAL;
		*pISol_Addr0 = data;	
		/* End of ISOL Release */
	}
	else {
		if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C0) ){
			/* M17 C0 */
			gpiod_set_raw_value(gpiod_hdmi20 ,1);	
		}
		else{
			/* M17 A0 */
			/* ISOL Release */
			data = *pISol_Addr1;
			data |= gHDMI20ChipRegHandler.isol_2_VAL;
			*pISol_Addr1 = data;

			data = *pISol_Addr2;
			data |= gHDMI20ChipRegHandler.isol_3_VAL;
			*pISol_Addr2 = data;

			data = *pISol_Addr0;
			data |= gHDMI20ChipRegHandler.isol_1_VAL;
			*pISol_Addr0 = data;	
			/* End of ISOL Release */
		}
	}

	while(1)
	{
		/* Force Kill Thread */
		if(gHDMI20Thread.isAlive <= 0){ HDMI20_INFO("Kill Thread\n"); break; }



		/* 2018.07.20 : M16PP Factory HPD Low specific chip issue. Watch Dog ALED HPD Reset PIN */
		if(gIsALEDIssueSolved <= 0){
			if(  __HDMI20_HAL_Rx_ALED_TOP_Read(0x50) != 0x6){
				HDMI20_INFO("HDMI20 WARN : ALED(0x50) is not 0x6! Watch Dog Activated. Value[0x%08x]\n", __HDMI20_HAL_Rx_ALED_TOP_Read(0x50));
				__HDMI20_HAL_Rx_ALED_TOP_Write(0x50, 0x6);

				/* Read After Write */
				if(  __HDMI20_HAL_Rx_ALED_TOP_Read(0x50) != 0x6){
					HDMI20_INFO("HDMI20 ERROR : After write, ALED(0x50) is still not 0x6!. Value[0x%08x]\n", __HDMI20_HAL_Rx_ALED_TOP_Read(0x50));
				}
				else{
					HDMI20_INFO("HDMI20 INFO : ALED 0x50 value is 0x6. Thanks to WatchDog\n");
					gIsALEDIssueSolved = 1;
				}
			}
			else{
				HDMI20_INFO("HDMI20 INFO : WatchDog => This chip is OKAY! \n");
				gIsALEDIssueSolved = 1;
			}
		}

		for(i=0;i<gHDMI20RxDevControler[HDMI20__NUMBER_OF_ACTIVATED_LINK].value;i++){
			/* Step 1. Check Required Information */
			HDMI20_HAL_Check5VLevelInfo(i, &tx5Vconnected, 0); // Check 5V

			if(tx5Vconnected){

				if(HDMI20_PHY_IsPhyPdbPowerOn(i) < 0){
					HDMI20_VIDEO("Notice %d : Phy PDB was Low but 5V High. Set PHY PDB to HIGH\n", i);
					if( gHDMI20RxDevControler[HDMI20__PHY_PDB_ON_DELAY_TIME].value > 0){
						HDMI20_VIDEO("Notice %d : Delay requested from Debugger[%d]msec\n",i, gHDMI20RxDevControler[HDMI20__PHY_PDB_ON_DELAY_TIME].value);
						msleep(gHDMI20RxDevControler[HDMI20__PHY_PDB_ON_DELAY_TIME].value);
					}
					HDMI20_PHY_ControlPhyPDB(i, 1);
				}

				/* DBG : View sync status */
				if((gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1919)||(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1921)){ __HDMI20_HAL_DBG_PrintSyncMonitor(i, gHDMI20RxDevControler[HDMI20__DBG_SYNC_MONITOR_RUN_MODE].value);}
				if((gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1920)||(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1921)){__HDMI20_HAL_DBG_PrintPixelCRCMonitor(i, gHDMI20RxDevControler[HDMI20__DBG_CRC_MONITOR_RUN_MODE].value);}
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 2002){HDMI20_DBG(" DBG %d : Current 5V stable time=>%u msec\n", i,  (int)gHDMI20RxHandler[i].connected5Vtime);}
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1132){HDMI20_DBG(" DBG %d : 8FC[0x%08x] / 0xFC[0x%08x] / 0xE0[0x%08x] / 0x600[0x%08x] /stable[%u]\n",\
						i, gHDMI20RxHandler[i].ctrl.bsp_read(0x8fc), gHDMI20RxHandler[i].ctrl.bsp_read(0xfc), gHDMI20RxHandler[i].ctrl.bsp_read(0xe0), gHDMI20RxHandler[i].ctrl.bsp_read(0x600),gHDMI20RxHandler[i].stablehdcp14time);
				}
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 2929){HDMI20_DBG(" DBG %d : [0x360] => [0x%08x], [0x380] => [0x%08x] [0xF80] => [0x%08x]\n", i,\
						gHDMI20RxHandler[i].ctrl.bsp_read(0x360), gHDMI20RxHandler[i].ctrl.bsp_read(0x380) , gHDMI20RxHandler[i].ctrl.bsp_read(0xF80));}
		
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 7979){HDMI20_DBG(" DBG %d : Current HSurge Lflag[%u], VSurge Flag[%u]\n", i, __sVideoSurgeHFlag[i], __sVideoSurgeVFlag[i]);}

				/* Set Pixel Auto Repetition based on PVO/CEA setting */
				if(__HDMI20_HAL_IsPVOMode(i) >= 0){
					/* Turn off Automatic de-repeate for pixel repetition signal on PVO modes */
					data = gHDMI20RxHandler[i].ctrl.bsp_read(0xa4);
					data &= (~0x00000001);
					gHDMI20RxHandler[i].ctrl.bsp_write(0xa4, data);
				}

				/* Surge Monitor */
				__sVideoSurgeVResult[i] = 0;
				__sVideoSurgeHResult[i] = 0;

				if( gHDMI20RxDevControler[HDMI20__SURGE_DETECTOR_ON].value >0){
					__sVideoSurgeMonitor[i][__sVideoSurgeCnt[i]%10] =  gHDMI20RxHandler[i].top_read(0x20C);
					__sVideoSurgeMonitor2[i][__sVideoSurgeCnt[i]%10] =  gHDMI20RxHandler[i].top_read(0x214);


					__sVideoSurgeCnt[i] += 1;
					for(y=0;y<10;y=y+2){
						if(__sVideoSurgeMonitor[i][y] >= __sVideoSurgeMonitor[i][y+1]){
							if(__sVideoSurgeMonitor[i][y] - __sVideoSurgeMonitor[i][y+1] >=  gHDMI20RxDevControler[HDMI20__SURGE_V_THRESHOLD].value){
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1225){
									HDMI20_DBG("DBG %d : Surge tick V [y]=[0x%08x], [y+1]=[0x%08x]\n", i, __sVideoSurgeMonitor[i][y], __sVideoSurgeMonitor[i][y+1]);
								}
								__sVideoSurgeVResult[i]++;
							}
						}
						else{
							if(__sVideoSurgeMonitor[i][y+1] - __sVideoSurgeMonitor[i][y] >=  gHDMI20RxDevControler[HDMI20__SURGE_V_THRESHOLD].value){
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1225){
									HDMI20_DBG("DBG %d : Surge tick H [y]=[0x%08x], [y+1]=[0x%08x]\n", i, __sVideoSurgeMonitor[i][y], __sVideoSurgeMonitor[i][y+1]);
								}
								__sVideoSurgeVResult[i]++;
							}
						}
					}
					for(y=0;y<10;y=y+2){
						if(__sVideoSurgeMonitor2[i][y] >= __sVideoSurgeMonitor2[i][y+1]){
							if(__sVideoSurgeMonitor2[i][y] - __sVideoSurgeMonitor2[i][y+1] >=  gHDMI20RxDevControler[HDMI20__SURGE_H_THRESHOLD].value){
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1225){
									HDMI20_DBG("DBG %d : Surge tick2 [y]=[0x%08x], [y+1]=[0x%08x]\n", i, __sVideoSurgeMonitor2[i][y], __sVideoSurgeMonitor2[i][y+1]);
								}
								__sVideoSurgeHResult[i]++;
							}
						}
						else{
							if(__sVideoSurgeMonitor2[i][y+1] - __sVideoSurgeMonitor2[i][y] >=  gHDMI20RxDevControler[HDMI20__SURGE_H_THRESHOLD].value){
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1225){
									HDMI20_DBG("DBG %d : Surge tick2 [y]=[0x%08x], [y+1]=[0x%08x]\n", i, __sVideoSurgeMonitor2[i][y], __sVideoSurgeMonitor2[i][y+1]);
								}
								__sVideoSurgeHResult[i]++;
							}
						}
					}
				}
				/* End of Surge Monitor */

				/* Local Mute Color Detection */
				video_format = gHDMI20RxHandler[i].ctrl.bsp_read(0x3A4);
				video_format = (video_format & 0x60); video_format = video_format>>5;
				video_format = video_format & 0x3;

				if(__HDMI20_HAL_IsHwInDVIState(i)){
					/* SW Defence code for DVI CSC */
					video_format = 0;
				}

				/* Auto AVmute color select */
				if(video_format == 0){
					HDMI20_HAL_Rx_SetLocalVideoMuteColor(i,  (UINT32)((gHDMI20RxHandler[i].dataPacket[AVI][5]&0x60)>>5));
				}
				else{
					HDMI20_HAL_Rx_SetLocalVideoMuteColor(i,  video_format);
				}

				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1211){
					HDMI20_DBG("DBG %d : Video Format register[0x%x], Datapacket[0x%x]\n", i, video_format, (UINT32)((gHDMI20RxHandler[i].dataPacket[AVI][5]&0x60)>>5));
				}

				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1112){
					HDMI20_DBG(" DBG %d : DCM mode [0x%08x] \n", i, (HDMI20_HAL_RX_CURRENT_DCM_MASK & gHDMI20RxHandler[i].ctrl.bsp_read(HDMI20_HAL_RX_STATUS_REG)));
				}
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1923){ __HDMI20_HAL_DBG_PrintECCMonitor(i);}

				/* Keep in track of Htotal value incase of interlaced */
				vtotal = (gHDMI20RxHandler[i].top_read(0x20C) & 0xFFFF0000)>>16;

				if(gHDMI20RxHandler[i].vtotalbuffer >= vtotal){
					gHDMI20RxHandler[i].vtotalbuffer = vtotal;
				}
				else{
					if(gHDMI20RxHandler[i].vtotalbuffer == 0){
						gHDMI20RxHandler[i].vtotalbuffer = vtotal;
					}
					else if(vtotal - gHDMI20RxHandler[i].vtotalbuffer >= 2){
						gHDMI20RxHandler[i].vtotalbuffer = vtotal;
					}
					else{
						/* DO NOT UPDATE */
					}
				}


				if(gHDMI20RxHandler[i].is5Vconnected == 0){
					HDMI20_VIDEO("Notice [%d] : 5V was up without connection function\n", i);
					HDMI20_HAL_ConnectCable(i, ON);
				}
				else{
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 1802){
						HDMI20_PHY_UpdatePhyTMDSclock(i);	/* Update Phy TMDS Clock */
						HDMI20_PHY_UpdatePhyLockFlag(i);	/* Update Phy Lock Flag */
						if(gHDMI20RxDevControler[HDMI20__ENABLE_WA_MODESEL_STUCKCASE].value > 0) {
							HDMI20_PHY_UpdateModeSelStatus(i);	/* Update Phy Mode Sel Status */
						}
					}

					__HDMI20_HAL_UpdateSCDC(i);			/* Update SCDC always */


					/* AV Mute */
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1052){
						HDMI20_DBG("DBG %d : GCP AVMute[0x%x]\n", i, gHDMI20RxHandler[i].dataPacket[GCP][4]);
					}

					/* Calculate Real TMDS, PIXEL CLK */
					gHDMI20RxHandler[i].real_tmds_clk = gHDMI20RxHandler[i].phy_tmds_clk;

					if(gHDMI20RxHandler[i].real_tmds_clk != 0){
						gHDMI20RxHandler[i].real_tmds_clk = (gHDMI20RxHandler[i].real_tmds_clk * 10);
						if(HDMI20_HAL_IsSCDCvalueUD(i)){
							gHDMI20RxHandler[i].real_tmds_clk = gHDMI20RxHandler[i].real_tmds_clk<<2;
						}

						if(gHDMI20RxHandler[i].currentDCMMode== 0x5){
							divider = 125;			
						}
						else if(gHDMI20RxHandler[i].currentDCMMode== 0x6){
							divider = 150;	
						}
						else if(gHDMI20RxHandler[i].currentDCMMode== 0x7){
							divider = 200;
						}
						else{
							divider =  100;
						}

						gHDMI20RxHandler[i].real_pixel_clk = (gHDMI20RxHandler[i].real_tmds_clk * 100) / divider;

					}
					else{
						gHDMI20RxHandler[i].real_tmds_clk = 0;
						gHDMI20RxHandler[i].real_pixel_clk = 0;
					}

					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1747){
						hvtotal = (gHDMI20RxHandler[i].timing_info.vtotal * gHDMI20RxHandler[i].timing_info.htotal);

						if(hvtotal != 0){
							dbg_vfreq = ((gHDMI20RxHandler[i].real_pixel_clk * 1000) / hvtotal);
						}
						else{
							dbg_vfreq = 0;
						}

						HDMI20_DBG("DBG %d : Polling TMDS CLK[%d]KHz, PIXEL CLK[%d]KHz, VFREQ[%d]/INFO[%d]\n", i, gHDMI20RxHandler[i].real_tmds_clk, gHDMI20RxHandler[i].real_pixel_clk, dbg_vfreq, gHDMI20RxHandler[i].real_vfreq);
					}

					hvtotal = (gHDMI20RxHandler[i].timing_info.vtotal * gHDMI20RxHandler[i].timing_info.htotal);

					hvtotal = (gHDMI20RxHandler[i].timing_info.vtotal * gHDMI20RxHandler[i].timing_info.htotal);
					
					if((hvtotal != 0)&&(gHDMI20RxHandler[i].isPhyLocked > 0)){
						dbg_vfreq = ((gHDMI20RxHandler[i].real_pixel_clk * 1000) / hvtotal);

						if(abs(dbg_vfreq - gHDMI20RxHandler[i].real_vfreq) >= gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_VFREQ_UPDATE].value){
							HDMI20_VIDEO("Warning %d : Vfreq diff is over [%d]. Change Vfreq to [%d]\n", i, (dbg_vfreq - gHDMI20RxHandler[i].real_vfreq), dbg_vfreq);
							gHDMI20RxHandler[i].real_vfreq = dbg_vfreq;


							if((HDMI20_HAL_IsManualSyncSet(i) > 0)&&(gHDMI20RxDevControler[HDMI20__RESET_MANUAL_SYNC_ON_VFREQ_CHANGE].value > 0)){
								HDMI20_HAL_ClearManualSyncSetting(i);
							}
						}

						if(gHDMI20RxHandler[i].real_vfreq != dbg_vfreq){

							if( (gHDMI20RxHandler[i].real_vfreq <= gHDMI20RxDevControler[HDMI20__VFREQ_SUPPORT_MIN].value )||(gHDMI20RxHandler[i].real_vfreq >=   gHDMI20RxDevControler[HDMI20__VFREQ_SUPPORT_MAX].value)){
								HDMI20_VIDEO("Notice %d : Update Vfreq even diff threshold in under[%d] due to min[%d]/max[%d] condition\n", i, gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_VFREQ_UPDATE].value, gHDMI20RxDevControler[HDMI20__VFREQ_SUPPORT_MIN].value,gHDMI20RxDevControler[HDMI20__VFREQ_SUPPORT_MAX].value);
								gHDMI20RxHandler[i].real_vfreq = dbg_vfreq;
							}
							else{
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value ==  841){
									HDMI20_DBG("DBG %d : Real Vfreq and Signed Vfreq is different! TimingInfo[%d] != Calculated[%d]\n", i, gHDMI20RxHandler[i].real_vfreq, dbg_vfreq);
								gHDMI20RxHandler[i].real_vfreq = dbg_vfreq;
								}
								
							}
						}
					}
					else{
						dbg_vfreq = 0;
					}

					/* AV MUTE HOLD TIME */
					if(gHDMI20RxDevControler[HDMI20__CLEAR_AVMUTE_BY_TIMER].value >0){
						if(gHDMI20RxHandler[i].ctrl.isMute != 0){
							currentJiffiesMsec = jiffies_to_msecs(jiffies);
							if(currentJiffiesMsec - gHDMI20RxHandler[i].avmute_on_time >= gHDMI20RxDevControler[HDMI20__AVMUTE_HOLD_TIME].value){
								HDMI20_VIDEO("NOTICE [%d] : AV Mute released by hold time! [0x%x]-[0x%x] >= [0x%x]\n",i,currentJiffiesMsec, gHDMI20RxHandler[i].avmute_on_time, gHDMI20RxDevControler[HDMI20__AVMUTE_HOLD_TIME].value);
								gHDMI20RxHandler[i].ctrl.isMute = 0;
								__HDMI20_HAL_SetVideoColorDomain(i);

								__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
								gHDMI20RxHandler[i].ctrl.bsp_write(0xFB8, 0x1F);

								hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);
							}
							else{
								HDMI20_VIDEO("NOTICE [%d] : AVMute Hold [0x%x]-[0x%x] < [0x%x]\n"\
										,i,currentJiffiesMsec, gHDMI20RxHandler[i].avmute_on_time, gHDMI20RxDevControler[HDMI20__AVMUTE_HOLD_TIME].value);
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value !=  741) {
									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
								}

								if(gHDMI20RxDevControler[HDMI20__DISABLE_AVMUTE_BY_POLLING].value  > 0){
									if(gHDMI20RxHandler[i].ctrl.bsp_read(0x380) & 0x00000001){
										HDMI20_VIDEO("NOTICE [%d] : AVMute Clear by polling read. \n", i);
										gHDMI20RxHandler[i].ctrl.isMute = 0;
										__HDMI20_HAL_SetVideoColorDomain(i);
										hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);
									}
								}
							}
						}
					}

					if(gHDMI20RxHandler[i].connect_request){
						if(gHDMI20RxHandler[i].hpd_request == 0){
							if((HDMI20_HAL_IsHPD_Up(i) == 0)||(gHDMI20RxHandler[i].isLinkInitiated == 0)){
								HDMI20_VIDEO("Notice [%d] : Main Thread received from Connection Request\n", i);
								gHDMI20RxHandler[i].hpd_request = 1;
								gHDMI20RxHandler[i].locking_time = 0;
								gHDMI20RxHandler[i].phy_rst_request = 1;
								HDMI20_HAL_Rx_LinkVideoReset(i, 1, __L__);

								ret = HDMI20_PHY_Rx_Initiate_Phy(i,  HDMI20_HAL_IsSCDCvalueUD(i));
								if(ret<0){
									HDMI20_ERROR("Cannot Initiate Phy[%d]. Return error from Phy write[%d]\n", i, ret);
								}

								if(gHDMI20RxDevControler[HDMI20__HPD_UP_ON_5V].value > 0){
									if(gHDMI20RxHandler[i].gWasHDCP22Written > 0){
										HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
									}
									__HDMI20_HAL_Rx_Set_EnableHPD(i, 1, 1, __L__);
								}
								else{
									HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_REQUEST_HPD ,i);
								}
							}
							else{
								if(gHDMI20RxHandler[i].isPhyLocked){
									gHDMI20RxHandler[i].locking_time++;

									HDMI20_VIDEO("Notice [%d] : Phy Locked(C)[%u]msec =>TCS Done[%d] LinkPhy[%d] TCS Min[%d][%d][%d], TCS Max[%d][%d][%d]\n", i,\
											gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep,\
											gHDMI20RxHandler[i].phyTCSDone, gHDMI20RxHandler[i].linkPhyLocked,\
											gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
											gHDMI20RxHandler[i].phyTCSMax[0], gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2]);

									if(gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value == 0){
										/* Inform HDCP2.2 that video is stable */
										if(gHDMI20RxHandler[i].gWasHDCP22Written > 0){
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, i);
										}
									}
									
									HDMI20_HAL_Rx_SetLocalVideoMute(i, 1, 1, __L__);

									HDMI20_ResetDataPacketBuffer(VSI ,i);
									HDMI20_ResetDataPacketBuffer(H14VSI ,i);
									HDMI20_ResetDataPacketBuffer(HFVSI ,i);
									HDMI20_ResetDataPacketBuffer(DOLBYVSI ,i);

									HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, i);
									
									/* Packet Fifo reset */
									hdmi_rx_ctrl_packet_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);

									gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_1].value);
									
									if(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value > 0){
										msleep(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value);
									}
									gHDMI20RxHandler[i].isManualSyncMode = 0;

									/* Important to clear ManualSYnc value */
									HDMI20_HAL_ClearManualSyncSetting(i);

									/* Audio Output Enable, Audio FIFO reset */
									hdmi_rx_ctrl_audio_cfg((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);
									gHDMI20RxHandler[i].ctrl.bsp_write(0xFB8, 0x1F);
									hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);


									/* Update Video*/
									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
									gHDMI20RxHandler[i].phyLostCnt = 0;
									HDMI20_HAL_Rx_Get_AudioInfo(i);

									/* Clear Connect Step flag */
									gHDMI20RxHandler[i].connect_request = 0;
									gHDMI20RxHandler[i].phy_rst_request = 0;

								}
								else{
									if(gHDMI20RxHandler[i].scdc_change != 0){
										__HDMI20_HAL_Rx_CheckSCDC(i);
									}
									else if(gHDMI20RxHandler[i].phy_tmds_clk > 0){
										gHDMI20RxHandler[i].prevPhyModeSelStatus = 0;

										HDMI20_VIDEO("Notice [%d] : Waiting TCS(C) => [%u]. TMDS[%5d] TCS Done[%d]. CRDone[%d] LinkPhy[%d] TCS Min[%d][%d][%d],TCS Max[%d][%d][%d]. Stable[%d]\n",\
												i,(gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep), gHDMI20RxHandler[i].phy_tmds_clk, gHDMI20RxHandler[i].phyTCSDone,\
												gHDMI20RxHandler[i].phyCrDone, gHDMI20RxHandler[i].linkPhyLocked,\
												gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
												gHDMI20RxHandler[i].phyTCSMax[0], gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2], gHDMI20RxHandler[i].phy_stable_cnt);
										gHDMI20RxHandler[i].locking_time++;


										if(gHDMI20RxHandler[i].locking_time >= gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_PHY_LOCK_WAIT].value){
											HDMI20_PRINT("Warning [%d] : Phy Not locked for [%d] msec(C) Check Phy TMDS [%5d] .TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
													i, (gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep), gHDMI20RxHandler[i].phy_tmds_clk,\
													gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
													gHDMI20RxHandler[i].phyTCSMax[0],gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2],\
													gHDMI20RxHandler[i].phyTCSResult[0],gHDMI20RxHandler[i].phyTCSResult[1],gHDMI20RxHandler[i].phyTCSResult[2],\
													gHDMI20RxHandler[i].phyTCSError[0],gHDMI20RxHandler[i].phyTCSError[1],gHDMI20RxHandler[i].phyTCSError[2],\
													gHDMI20RxHandler[i].isScdcUD);

											gHDMI20RxHandler[i].locking_time = 0;
										}

										HDMI20_HAL_Rx_Update_AudioCtsNparam(i, 1);
									}
									else{
										HDMI20_VIDEO("Notice [%d] : No TMDS Clk(C)[%5d].CRDone[%d] MST[%d]/PrevMST[%d]\n", i, gHDMI20RxHandler[i].phy_tmds_clk, gHDMI20RxHandler[i].phyCrDone, gHDMI20RxHandler[i].phyModeSelStatus, gHDMI20RxHandler[i].prevPhyModeSelStatus);
										gHDMI20RxHandler[i].locking_time++;

										if(gHDMI20RxDevControler[HDMI20__ENABLE_WA_MODESEL_STUCKCASE].value > 0){
											if((gHDMI20RxHandler[i].prevPhyModeSelStatus == gHDMI20RxHandler[i].phyModeSelStatus) &&((gHDMI20RxHandler[i].phyModeSelStatus == 0x1)||(gHDMI20RxHandler[i].phyModeSelStatus == 0x2))){
												HDMI20_SWWA("Warning [%d] : Detected ModeSel WatchDog Stuck case! Reset PHY PLL ModeSel\n", i);
												HDMI20_PHY_Reset_ModeSel(i, 1, __L__);
												HDMI20_PHY_Reset_ModeSel(i, 0, __L__);
												gHDMI20RxHandler[i].prevPhyModeSelStatus = 0;
											}
											else{
												gHDMI20RxHandler[i].prevPhyModeSelStatus = gHDMI20RxHandler[i].phyModeSelStatus;
											}
										}

										if(gHDMI20RxHandler[i].locking_time >= gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_PHY_LOCK_WAIT].value){
											HDMI20_PRINT("Warning [%d] : No TMDS Clk for [%d] msec(C) Check Phy TMDS [%5d] .TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
													i, (gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep), gHDMI20RxHandler[i].phy_tmds_clk,\
													gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
													gHDMI20RxHandler[i].phyTCSMax[0],gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2],\
													gHDMI20RxHandler[i].phyTCSResult[0],gHDMI20RxHandler[i].phyTCSResult[1],gHDMI20RxHandler[i].phyTCSResult[2],\
													gHDMI20RxHandler[i].phyTCSError[0],gHDMI20RxHandler[i].phyTCSError[1],gHDMI20RxHandler[i].phyTCSError[2],\
													gHDMI20RxHandler[i].isScdcUD);

											gHDMI20RxHandler[i].locking_time = 0;
										}
									}
								}
							}
						}
						else{
							if(HDMI20_HAL_IsHPD_Up(i)){
								HDMI20_VIDEO("Notice [%d] : Got HPD Up from connection(Connections Steps)\n", i);
								gHDMI20RxHandler[i].hpd_request = 0;
							}
							else{
								HDMI20_VIDEO("Notice [%d] : Waiting HPD UP(Connection Steps)\n", i);
								hpdWaitCnt[i]++;
								if(hpdWaitCnt[i] >= gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_HPD_REQUEST].value){
									HDMI20_VIDEO("Notice [%d] : Call HPD request one more time.[%d]/[%d]\n", i, hpdWaitCnt[i], 	gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_HPD_REQUEST].value);
									
									if(gHDMI20RxDevControler[HDMI20__HPD_UP_ON_5V].value > 0){
										if((gHDMI20RxHandler[i].gWasHDCP22Written > 0)){ 
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
										}
										__HDMI20_HAL_Rx_Set_EnableHPD(i, 1, 1, __L__);
									}
									else{
										HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_REQUEST_HPD ,i);
									}

									hpdWaitCnt[i] = 0;
								}
							}
						}
					}
					else{
						if(gHDMI20RxHandler[i].phy_rst_request)
						{
							if(gHDMI20RxHandler[i].isPhyLocked){
								if((gHDMI20RxHandler[i].isManualSyncMode == 1) &&(gHDMI20RxHandler[i].phyInitiatedMode == 0)){
									HDMI20_VIDEO("Notice [%d] : Recover from 3D manual Sync mode. Reset Link TMDS\n", i);

									if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1219){
										gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
										gHDMI20RxHandler[i].isManualSyncMode = 0;
									}
									else {
										if(gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value == 0){
											if((gHDMI20RxHandler[i].isHDCP22)&&(gHDMI20RxHandler[i].gWasHDCP22Written > 0)){
												HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
											}
										}

										HDMI20_HAL_Rx_LinkVideoReset(i, 0, __L__);
										gHDMI20RxHandler[i].isManualSyncMode = 0;
									}
								}
								else{
									gHDMI20RxHandler[i].locking_time++;
									HDMI20_VIDEO("Notice [%d] : Phy Locked(N)[%u]msec =>TCS Done[%d] LinkPhy[%d] TCS Min[%d][%d][%d], TCS Max[%d][%d][%d]\n", i,\
											gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep,\
											gHDMI20RxHandler[i].phyTCSDone, gHDMI20RxHandler[i].linkPhyLocked,\
											gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
											gHDMI20RxHandler[i].phyTCSMax[0], gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2]);

									if(gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value == 0){
										if(gHDMI20RxHandler[i].gWasHDCP22Written > 0){
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, i);
										}
									}

									HDMI20_ResetDataPacketBuffer(VSI ,i);
									HDMI20_ResetDataPacketBuffer(H14VSI ,i);
									HDMI20_ResetDataPacketBuffer(HFVSI ,i);
									HDMI20_ResetDataPacketBuffer(DOLBYVSI ,i);
									HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, i);

									/* Packet Fifo reset */
									hdmi_rx_ctrl_packet_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);

									HDMI20_HAL_Rx_SetLocalVideoMute(i, 1, 1, __L__);

									/* Clear Timing Info */
									HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 1, __L__);

									gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_1].value);
									if(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value > 0){
										msleep(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value);
									}
								
									gcpCnt[i] = 0;

									if(gHDMI20RxDevControler[HDMI20__LINK_RST_CNT].value > 0){
										while(1)
										{
											data = gHDMI20RxHandler[i].ctrl.bsp_read(0x380); 

											if((data & 0x000000F0) == 0){
												HDMI20_VIDEO("DBG %d : 0x380 reg [7:4] got Zero, Cnt[%d]\n", i, gcpCnt[i]);
												break;
											}
											else{
												HDMI20_VIDEO("DBG %d : 0x380 reg [7:4] is not Zero[0x%08x], Cnt[%d]\n", i, data, gcpCnt[i]);
												gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0,  gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
											}

											if(gcpCnt[i] >= gHDMI20RxDevControler[HDMI20__LINK_RST_CNT].value){
												HDMI20_VIDEO("DBG %d : timeout on gcpCnt[%d]\n", i, gcpCnt[i]);
												break;
											}
											gcpCnt[i]++;
										}
									}


									gHDMI20RxHandler[i].isManualSyncMode = 0;
									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;

									/* Important to clear ManualSYnc value */
									HDMI20_HAL_ClearManualSyncSetting(i);

									/* Audio Output Enable, Audio FIFO reset */
									hdmi_rx_ctrl_audio_cfg((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);
									gHDMI20RxHandler[i].ctrl.bsp_write(0xFB8, 0x1F);
									hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);


									/* Update Video*/
									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
									gHDMI20RxHandler[i].phyLostCnt = 0;

									HDMI20_HAL_Rx_Get_AudioInfo(i);
									gHDMI20RxHandler[i].phy_rst_request = 0;
								}
							}
							else{
								if(gHDMI20RxHandler[i].scdc_change != 0){
									__HDMI20_HAL_Rx_CheckSCDC(i);
								}
								else if(gHDMI20RxHandler[i].phy_tmds_clk > 0){
									gHDMI20RxHandler[i].prevPhyModeSelStatus = 0;
									
									/* 2018/11/01 : PS4 Pro */
									gHDMI20RxHandler[i].phy_rst_request = 1;

									HDMI20_VIDEO("Notice [%d] : Waiting TCS(N) =>[%u].MST[%d] TMDS[%5d] TCS Done[%d]. CRDone[%d] LinkPhy[%d] TCS Min[%d][%d][%d], TCS Max[%d][%d][%d]. Stable[%d]\n", \
											i, (gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep), gHDMI20RxHandler[i].phyModeSelStatus, gHDMI20RxHandler[i].phy_tmds_clk,gHDMI20RxHandler[i].phyTCSDone,\
											gHDMI20RxHandler[i].phyCrDone, gHDMI20RxHandler[i].linkPhyLocked,\
											gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
											gHDMI20RxHandler[i].phyTCSMax[0], gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2], gHDMI20RxHandler[i].phy_stable_cnt);
									gHDMI20RxHandler[i].locking_time++;

									if(gHDMI20RxHandler[i].locking_time >= gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_PHY_LOCK_WAIT].value){
										HDMI20_PRINT("Warning [%d] : Phy Not locked for [%d] msec(N) Check Phy TMDS [%5d] .TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
												i, (gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep), gHDMI20RxHandler[i].phy_tmds_clk,\
												gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
												gHDMI20RxHandler[i].phyTCSMax[0],gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2],\
												gHDMI20RxHandler[i].phyTCSResult[0],gHDMI20RxHandler[i].phyTCSResult[1],gHDMI20RxHandler[i].phyTCSResult[2],\
												gHDMI20RxHandler[i].phyTCSError[0],gHDMI20RxHandler[i].phyTCSError[1],gHDMI20RxHandler[i].phyTCSError[2],\
												gHDMI20RxHandler[i].isScdcUD);

										gHDMI20RxHandler[i].locking_time = 0;
									}

									HDMI20_HAL_Rx_Update_AudioCtsNparam(i, 1);
								}
								else{
									HDMI20_VIDEO("Notice [%d] : No TMDS Clk(C)[%5d]. CRDone[%d]  MST[%d]/PrevMST[%d]\n", i, gHDMI20RxHandler[i].phy_tmds_clk, gHDMI20RxHandler[i].phyCrDone,gHDMI20RxHandler[i].phyModeSelStatus, gHDMI20RxHandler[i].prevPhyModeSelStatus);
								
									/* 2018/11/01 : PS4 Pro */
									gHDMI20RxHandler[i].phy_rst_request = 1;
									
									if(gHDMI20RxDevControler[HDMI20__ENABLE_WA_MODESEL_STUCKCASE].value > 0){
										if((gHDMI20RxHandler[i].prevPhyModeSelStatus == gHDMI20RxHandler[i].phyModeSelStatus) &&((gHDMI20RxHandler[i].phyModeSelStatus == 0x1)||(gHDMI20RxHandler[i].phyModeSelStatus == 0x2))){
											HDMI20_SWWA("Warning [%d] : Detected ModeSel WatchDog Stuck case! Reset PHY PLL ModeSel\n", i);
											HDMI20_PHY_Reset_ModeSel(i, 1, __L__);
											HDMI20_PHY_Reset_ModeSel(i, 0, __L__);
											gHDMI20RxHandler[i].prevPhyModeSelStatus = 0;
										}
										else{
											gHDMI20RxHandler[i].prevPhyModeSelStatus = gHDMI20RxHandler[i].phyModeSelStatus;
										}
									}

									if(gHDMI20RxHandler[i].locking_time >= gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_PHY_LOCK_WAIT].value){
										HDMI20_VIDEO("Warning [%d] : No TMDS Clk for [%d] msec(N) Check Phy TMDS [%5d] .TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
												i, (gHDMI20RxHandler[i].locking_time * gHDMI20Thread.mSleep), gHDMI20RxHandler[i].phy_tmds_clk,\
												gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
												gHDMI20RxHandler[i].phyTCSMax[0],gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2],\
												gHDMI20RxHandler[i].phyTCSResult[0],gHDMI20RxHandler[i].phyTCSResult[1],gHDMI20RxHandler[i].phyTCSResult[2],\
												gHDMI20RxHandler[i].phyTCSError[0],gHDMI20RxHandler[i].phyTCSError[1],gHDMI20RxHandler[i].phyTCSError[2],\
												gHDMI20RxHandler[i].isScdcUD);

										gHDMI20RxHandler[i].locking_time = 0;
									}
								}
							}
						}
						else
						{
							if(HDMI20_HAL_IsHPD_Up(i)&&( gHDMI20RxHandler[i].isPhyLocked)){
								if(gHDMI20RxHandler[i].phyLostCnt > 0){
									HDMI20_VIDEO("Notice %d : Recover from phy lock loss[%d]\n", i, gHDMI20RxHandler[i].phyLostCnt); 
									gHDMI20RxHandler[i].phyLostCnt = 0;
							
									gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0,  gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_1].value);

									/* Apple TV */
									HDMI20_ResetDataPacketBuffer(VSI, i);
									HDMI20_ResetDataPacketBuffer(H14VSI ,i);
									HDMI20_ResetDataPacketBuffer(HFVSI ,i);
									HDMI20_ResetDataPacketBuffer(DOLBYVSI ,i);
									HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, i);

									if(gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value == 0){
										if((gHDMI20RxHandler[i].isHDCP22)&&(gHDMI20RxHandler[i].gWasHDCP22Written > 0)){
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, i);
										}
										else if(gHDMI20RxHandler[i].gWasHDCP22Written){
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, i);
										}
									}
									/* Apple TV */
									HDMI20_ResetDataPacketBuffer(VSI, i);
									HDMI20_ResetDataPacketBuffer(H14VSI ,i);
									HDMI20_ResetDataPacketBuffer(HFVSI ,i);
									HDMI20_ResetDataPacketBuffer(DOLBYVSI ,i);
									HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, i);
								}

								hpdWaitCnt[i] = 0;


								if((gHDMI20RxHandler[i].scdc_change != 0) || (gHDMI20RxHandler[i].video_change != 0) ||\
										/*(gHDMI20RxHandler[i].audio_change != 0) ||*/ (gHDMI20RxHandler[i].tmds_change != 0))
								{
									/* Clear VideoCon detect on any Change detect operations*/
									gHDMI20RxHandler[i].videoConDetectCnt = 0;
									
									HDMI20_HAL_Rx_Set_AudioReset(i);
									HDMI20_VIDEO("Notice [%d] : Flag change => SCDC[%d] / VC[%d] / AC[%d] / TC[%d] / AKSV[%d]\n", i,\
											gHDMI20RxHandler[i].scdc_change, gHDMI20RxHandler[i].video_change,\
											gHDMI20RxHandler[i].audio_change, gHDMI20RxHandler[i].tmds_change, gHDMI20RxHandler[i].aksv_change);
								}

								/* Debug : To discard change-routine */
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3040){ gHDMI20RxHandler[i].scdc_change = 0; gHDMI20RxHandler[i].video_change = 0; gHDMI20RxHandler[i].tmds_change = 0; gHDMI20RxHandler[i].aksv_change = 0;}
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3041){ gHDMI20RxHandler[i].audio_change = 0;}

								if((gHDMI20RxHandler[i].scdc_change != 0) || (gHDMI20RxHandler[i].video_change != 0) ||\
										(gHDMI20RxHandler[i].tmds_change != 0) || (gHDMI20RxHandler[i].aksv_change != 0))
								{
									if(gHDMI20RxHandler[i].scdc_change != 0){
										__HDMI20_HAL_Rx_CheckSCDC(i);
									}
									else if(gHDMI20RxHandler[i].tmds_change != 0){
										__HDMI20_HAL_Rx_Operation_TMDS_Change(i, 0);
									}
									else if(gHDMI20RxHandler[i].video_change != 0){
										__HDMI20_HAL_Rx_Operation_Video_Change(i);
									}

									if(gHDMI20RxHandler[i].aksv_change != 0){
										__HDMI20_HAL_Rx_Operation_AKSV_Change(i);
									}

									/* DVI to HDMI cable, audio noise issue */
									gHDMI20RxHandler[i].ctrl.bsp_write(0xFB8, 0x1F);
									hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);
								}

								if(gHDMI20RxHandler[i].audio_change != 0){
									__HDMI20_HAL_Rx_Operation_Audio_Change(i);
								}

								if(gHDMI20RxHandler[i].ctrl.stable_cnt < gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value)
								{
									gHDMI20RxHandler[i].ctrl.stable_cnt++;
									gHDMI20RxHandler[i].hdcp22_auth_change = 0;
									gHDMI20RxHandler[i].hdcp22_ists_change = 0;
									__sVideoSurgeHFlag[i] = 0;
									__sVideoSurgeVFlag[i] = 0;
								}
								else if(gHDMI20RxHandler[i].ctrl.stable_cnt == gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value)
								{
									HDMI20_VIDEO("Notice [%d] : Video was stable for [%d] msec\n", i, gHDMI20RxHandler[i].ctrl.stable_cnt * gHDMI20Thread.mSleep);

									if((gHDMI20RxHandler[i].isHDCP14 > 0)&&(gHDMI20RxHandler[i].ctrl.bsp_read(0x8FC) != 0x4011)) {

										if(gHDMI20RxHandler[i].stablehdcp14time < gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY].value){
											HDMI20_VIDEO("Notice [%d] : Stable Video but wait until HDCP1.4 is stable[%d]\n", i,gHDMI20RxHandler[i].stablehdcp14time);
										}
										else{
											HDMI20_VIDEO("Notice [%d] : HDCP1.4 encrypted signal, and HDCP1.4 status is stable!\n", i);
											gHDMI20RxHandler[i].ctrl.stable_cnt++;
											__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_DOWN, __L__);
											HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 0, __L__);
										}
									}
									else{
										gHDMI20RxHandler[i].ctrl.stable_cnt++;
										__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_DOWN, __L__);
										HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 0, __L__);
									}
								
									/* for HDMI Host diagnosis error detection */
									HDMI20_HAL_PutHDMIHostError(i, LX_HDMI20_ERROR_PHY_LOW_RANGE, 0);
									HDMI20_HAL_PutHDMIHostError(i, LX_HDMI20_ERROR_PHY_ABNORMAL, 0);
								}
								else{
									/* This part will run always on steady state
									 * Insert code as wishing that it would always be called when on steady video */
									if(HDMI20_HAL_IsTimingInfoEmpty(i) > 0){
										HDMI20_VIDEO("Warning [%d] : Stable Video but TimingInfo was Empty. Refresh Timing Info!\n", i);
										HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 0, __L__);
									}
								
									/* for HDMI Host diagnosis error detection */
									HDMI20_HAL_PutHDMIHostError(i, LX_HDMI20_ERROR_TMDS_ERROR, 0);
									HDMI20_HAL_PutHDMIHostError(i, LX_HDMI20_ERROR_CED_ERROR, 0);

									__HDMI20_HAL_CheckVideoColorDomain(i);
									__HDMI20_HAL_Rx_CatchPC(i);

									if( gHDMI20RxDevControler[HDMI20__SURGE_DETECTOR_ON].value >0){
										if(gHDMI20RxHandler[i].hdcp22_ists_change != 0){
											HDMI20_VIDEO("Warning %d : Surge insertion on HDCP22 RESET detected!\n", i);
											if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 2889){

												if(gHDMI20RxHandler[i].gWasHDCP22Written > 0){
													HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
													HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, i);
												}
											}
											gHDMI20RxHandler[i].hdcp22_ists_change = 0;
											gHDMI20RxHandler[i].hdcp22_auth_change = 0;

											__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);

											gHDMI20RxHandler[i].ctrl.bsp_write(0xff0, 0x10);
										}
										else if((__sVideoSurgeVResult[i] != 0)&&(__sVideoSurgeVFlag[i] == 0)){
											HDMI20_VIDEO("Warning %d : Surge insertion on Vertical Total detected!\n", i);
											__sVideoSurgeVFlag[i] = 1;
											__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);

											gHDMI20RxHandler[i].ctrl.bsp_write(0xff0, 0x10);
										}
										else if((__sVideoSurgeHResult[i] != 0)&&(__sVideoSurgeHFlag[i] == 0)){
											HDMI20_VIDEO("Warning %d : Surge insertion on Horizontal Total detected!\n", i);
											__sVideoSurgeHFlag[i] = 1;
											__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);

											gHDMI20RxHandler[i].ctrl.bsp_write(0xff0, 0x10);
										}

										else if(gHDMI20RxHandler[i].hdcp22_auth_change != 0){
											HDMI20_VIDEO("Warning %d : Surge insertion on HDCP22 detected!\n", i);
											gHDMI20RxHandler[i].hdcp22_auth_change = 0;
											__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);

											gHDMI20RxHandler[i].ctrl.bsp_write(0xff0, 0x10);
										}
										else{
											if((__sVideoSurgeHResult[i] != 0)&&(__sVideoSurgeHFlag[i] != 0)){
												if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 247){
													HDMI20_VIDEO("Warning %d : Surge on Horizontal Total detected but H FLag is Up !\n", i);
												}
											}else if(__sVideoSurgeHFlag[i] != 0){
												HDMI20_VIDEO("Notice %d : Release Surge flag on Horizontal\n", i);
												__sVideoSurgeHFlag[i] = 0;
											}

											if((__sVideoSurgeVResult[i] != 0)&&(__sVideoSurgeVFlag[i] != 0)){
												if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 247){
													HDMI20_VIDEO("Warning %d : Surge on Vertical Total detected but V FLag is Up !\n", i);
												}
											}else if(__sVideoSurgeVFlag[i] != 0){
												HDMI20_VIDEO("Notice %d : Release Surge flag on Vertical\n", i);
												__sVideoSurgeVFlag[i] = 0;
											}
										}

										if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1227){
											HDMI20_VIDEO(" DBG %d Result[%d] : Surge 1 [0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x]\n",\
													i, __sVideoSurgeVResult[i],\
													__sVideoSurgeMonitor[i][0],__sVideoSurgeMonitor[i][1],__sVideoSurgeMonitor[i][2],__sVideoSurgeMonitor[i][3],__sVideoSurgeMonitor[i][4],\
													__sVideoSurgeMonitor[i][5],__sVideoSurgeMonitor[i][6],__sVideoSurgeMonitor[i][7],__sVideoSurgeMonitor[i][8],__sVideoSurgeMonitor[i][9]);
											HDMI20_VIDEO(" DBG %d Result[%d] : Surge 2 [0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x]\n",\
													i, __sVideoSurgeHResult[i],\
													__sVideoSurgeMonitor2[i][0],__sVideoSurgeMonitor2[i][1],__sVideoSurgeMonitor2[i][2],__sVideoSurgeMonitor2[i][3],__sVideoSurgeMonitor2[i][4],\
													__sVideoSurgeMonitor2[i][5],__sVideoSurgeMonitor2[i][6],__sVideoSurgeMonitor2[i][7],__sVideoSurgeMonitor2[i][8],__sVideoSurgeMonitor2[i][9]);
										}

										if(gHDMI20RxHandler[i].isHDCP22Ncap != 0){
											HDMI20_VIDEO("Warning [%d] : Detected HDCP22 NCAP on stable video\n", i);
											__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
										}
									}

									HDMI20_HAL_Rx_Update_AudioCtsNparam(i, 0);
									/* Added 2014/10/19 : Update data packets every gHDMI20RxDevControler[HDMI20__PERIOD_FOR_DATAPACKET_POLLING].value * sleep msecs*/
									if(gHDMI20RxDevControler[HDMI20__USE_POLLING_MODE_FOR_DATAPACKET].value > 0){	
										if(datapacketUpdateTimer[i] >  gHDMI20RxDevControler[HDMI20__PERIOD_FOR_DATAPACKET_POLLING].value){
											datapacketUpdateTimer[i] = 0;
											for(y=0;y<PACKET_MAXNUM;y++){
												/* Even though this was opened, it will eventually be closed on Data packet ISR */
												HDMI20_HAL_Packet_Store((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, dataPacketNum[y], 1);
											}
										}
										else{
											datapacketUpdateTimer[i]++;
										}
									}
									HDMI20_HAL_Rx_Get_AudioInfo(i);
								}

							}
							else if(HDMI20_HAL_IsHPD_Up(i)&&(gHDMI20RxHandler[i].phy_tmds_clk == 0)&&( gHDMI20RxHandler[i].isPhyLocked == 0)&&(gHDMI20RxHandler[i].ctrl.isMute == 0)){
								/* 2018/11/01 : PS4 Pro */
								gHDMI20RxHandler[i].phy_rst_request = 1;

								if(gHDMI20RxHandler[i].tmds_change){
									
									/* Reset Link(HDCP14)/HDCP22/everything.. */	
									//__HDMI20_HAL_Rx_Operation_TMDS_Change(i, 1);	// Playstation4 kills TMDS clock after EDID read
									__HDMI20_HAL_Rx_Operation_TMDS_Change(i, 0);
								}
								else{
									HDMI20_VIDEO("Notice [%d] : No TMDS Clk(C)[%5d]. MST[%d]/PrevMST[%d]\n", i, gHDMI20RxHandler[i].phy_tmds_clk, gHDMI20RxHandler[i].phyModeSelStatus, gHDMI20RxHandler[i].prevPhyModeSelStatus);
									if(gHDMI20RxDevControler[HDMI20__ENABLE_WA_MODESEL_STUCKCASE].value > 0){
										if((gHDMI20RxHandler[i].prevPhyModeSelStatus == gHDMI20RxHandler[i].phyModeSelStatus) &&((gHDMI20RxHandler[i].phyModeSelStatus == 0x1)||(gHDMI20RxHandler[i].phyModeSelStatus == 0x2))){
											HDMI20_SWWA("Warning [%d] : Detected ModeSel WatchDog Stuck case! Reset PHY PLL ModeSel\n", i);
											HDMI20_PHY_Reset_ModeSel(i, 1, __L__);
											HDMI20_PHY_Reset_ModeSel(i, 0, __L__);
											gHDMI20RxHandler[i].prevPhyModeSelStatus = 0;
										}
										else{
											gHDMI20RxHandler[i].prevPhyModeSelStatus = gHDMI20RxHandler[i].phyModeSelStatus;
										}
									}
								}
								
								/* 2016/12/08 : Annotated this part to fix PSPRO Final Fantasy 15 HDR issue */
								//gHDMI20RxHandler[i].phyLostCnt = 0;
							}
							else if(HDMI20_HAL_IsHPD_Up(i)&&( gHDMI20RxHandler[i].isPhyLocked == 0)&&(gHDMI20RxHandler[i].ctrl.isMute == 0)){
								/* 2018/11/01 : PS4 Pro */
								gHDMI20RxHandler[i].phy_rst_request = 1;

								/* Check  PhyLock when on good video */
								HDMI20_VIDEO("Notice [%d] : Lost TCS on Stable[%u] Video. Cnt[%d]. PHY=> TMDS[%5d] TCS Done[%d]. LinkPhy[%d] TCS Min[%d][%d][%d],TCS Min[%d][%d][%d]. PhyStable[%d]\n",\
												i, gHDMI20RxHandler[i].ctrl.stable_cnt, gHDMI20RxHandler[i].phyLostCnt, gHDMI20RxHandler[i].phy_tmds_clk, gHDMI20RxHandler[i].phyTCSDone, gHDMI20RxHandler[i].linkPhyLocked,\
												gHDMI20RxHandler[i].phyTCSMin[0], gHDMI20RxHandler[i].phyTCSMin[1],gHDMI20RxHandler[i].phyTCSMin[2],\
												gHDMI20RxHandler[i].phyTCSMax[0], gHDMI20RxHandler[i].phyTCSMax[1],gHDMI20RxHandler[i].phyTCSMax[2], gHDMI20RxHandler[i].phy_stable_cnt);

								if(gHDMI20RxHandler[i].phyLostCnt == 0){
									HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);

									if(gHDMI20RxDevControler[HDMI20__FORCE_DCM_8_BIT_ON_594].value >0){
										data = gHDMI20RxHandler[i].ctrl.bsp_read(0x0A8);
										data &= 0x00001000;

										if(data != 0x0){
											HDMI20_VIDEO("Port[%d] Notice : Founded Force DCM to 8bit mode, Reset to automatic\n",i);
											gHDMI20RxHandler[i].ctrl.bsp_write(0x0A8, gHDMI20RxDevControler[HDMI20__LINK_REG_0XA8_GCP_CTRL].value);
										}
									}
								}

								gHDMI20RxHandler[i].phyLostCnt++;

								__HDMI20_HAL_Rx_CheckSCDC(i);

								if(gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value >0){
									if(gHDMI20RxHandler[i].countOf6GHpdTgSwWa > 0){
										if((HDMI20_HAL_IsSCDCvalueUD(i) > 0) && (gHDMI20RxHandler[i].phy_tmds_clk >= gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297_TMDS_CLK].value)){
											HDMI20_PRINT("Port[%d] Warning : Founded over [%d] TMDS Clock on 6G SCDC. Restart HPD\n",i, gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297_TMDS_CLK].value);
											HDMI20_HAL_Rx_Set_RestartHPD(i);

											/* 2018/01/08 : Execute this SW WA only once per Device plug */
											gHDMI20RxHandler[i].countOf6GHpdTgSwWa--;
										}
									}
								}

								if((gHDMI20RxHandler[i].isManualSyncMode == 2) &&(gHDMI20RxHandler[i].phyInitiatedMode == 0)){
									/* Clear Timing Info */
									HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 1, __L__);
									HDMI20_SWWA("Notice [%d] : Recover from 3D manual Sync mode.\n", i);

									gHDMI20RxHandler[i].locking_time = 0;
									gHDMI20RxHandler[i].phy_rst_request = 1;

									gHDMI20RxHandler[i].isManualSyncMode = 1;
									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
									HDMI20_HAL_Rx_LinkVideoReset(i, 0, __L__);
									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);


									__HDMI20_HAL_Rx_InitiateHDMI20Data(i, 0);
								}
								else if((gHDMI20RxHandler[i].ctrl.stable_cnt >= gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value)&&(gHDMI20RxHandler[i].phyInitiatedMode == 0) &&( gHDMI20RxHandler[i].isHDCP22 == 0)){
									HDMI20_VIDEO("Notice [%d] : Reset Link on ONLY for 3G signals\n", i);

									/* Clear Timing Info */
									HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 1, __L__);

									gHDMI20RxHandler[i].locking_time = 0;
									gHDMI20RxHandler[i].phy_rst_request = 1;

									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
									HDMI20_HAL_Rx_LinkVideoReset(i, 1, __L__);
									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);

									if((gHDMI20RxHandler[i].isHDCP22)&&(gHDMI20RxHandler[i].gWasHDCP22Written > 0)){
										HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
									}

									__HDMI20_HAL_Rx_InitiateHDMI20Data(i, 0);
								}
								else if(gHDMI20RxHandler[i].ctrl.stable_cnt >= gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value){
									/* Important to clear ManualSYnc value */
									HDMI20_HAL_ClearManualSyncSetting(i);
									
									gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0,  gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
								}
								else if((gHDMI20RxHandler[i].phyLostCnt >= gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_ABNORMAL_PHY_DETECTION].value)&&(gHDMI20RxDevControler[HDMI20__REINIT_PHY_ON_LOCK_LOSS_BY_DETECTION].value >= 1)){
									HDMI20_VIDEO("NOTICE [%d] : Reset Link due to lock signal loss. Cnt[%d]/Thres[%d]\n", i, gHDMI20RxHandler[i].phyLostCnt, gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_ABNORMAL_PHY_DETECTION].value);

									gHDMI20RxHandler[i].locking_time = 0;
									gHDMI20RxHandler[i].phy_rst_request = 1;

									gHDMI20RxHandler[i].isManualSyncMode = 1;
									gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
									
									if(gHDMI20RxHandler[i].phyInitiatedMode == 0){
										HDMI20_HAL_Rx_LinkVideoReset(i, 0, __L__);
									}
									else{
										HDMI20_VIDEO("Notice [%d] : SCDC 6G, All but main reset\n", i);
										gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
									}

									__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);

									__HDMI20_HAL_Rx_InitiateHDMI20Data(i, 0);
								}

								/* Important to Reset Video stable count */
								__HDMI20_HAL_Rx_ResetSyncPosition(i, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
								gHDMI20RxHandler[i].ctrl.stable_cnt = 0;
							}
							else if(HDMI20_HAL_IsHPD_Up(i)&&( gHDMI20RxHandler[i].isPhyLocked == 0)&&(gHDMI20RxHandler[i].ctrl.isMute != 0)){
								HDMI20_VIDEO("Warning [%d] : Lost Phylock, But AVMUTE. stableCnt[%d] Lost Cnt[%d]\n",i, gHDMI20RxHandler[i].ctrl.stable_cnt, gHDMI20RxHandler[i].phyLostCnt);
								gHDMI20RxHandler[i].phyLostCnt++;
								
								if((gHDMI20RxHandler[i].phyLostCnt >= gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_ABNORMAL_PHY_DETECTION].value)&&(gHDMI20RxDevControler[HDMI20__REINIT_PHY_ON_LOCK_LOSS_BY_DETECTION].value >= 1)){
									HDMI20_VIDEO("NOTICE [%d] : Reset Link due to lock signal loss(First time). Cnt[%d]/Thres[%d]\n", i, gHDMI20RxHandler[i].phyLostCnt, gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_ABNORMAL_PHY_DETECTION].value);

									//gHDMI20RxDevControler[HDMI20__REINIT_PHY_ON_LOCK_LOSS_BY_DETECTION].value = 0;

									gHDMI20RxHandler[i].locking_time = 0;
									gHDMI20RxHandler[i].phy_rst_request = 1;

									gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);

									__HDMI20_HAL_Rx_InitiateHDMI20Data(i, 0);
								}
							}
							else{
								if(gHDMI20RxHandler[i].hpd_request == 1){
									HDMI20_VIDEO("Notice [%d] : Waiting for request response of HPD up[%d]\n", i, hpdWaitCnt[i]);
									hpdWaitCnt[i]++;
									if(hpdWaitCnt[i] >= gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_HPD_REQUEST].value){
										HDMI20_VIDEO("Notice [%d] : Call HPD request one more time.[%d]/[%d]\n", i, hpdWaitCnt[i], 	gHDMI20RxDevControler[HDMI20__TIMEOUT_FOR_HPD_REQUEST].value);
										if(gHDMI20RxDevControler[HDMI20__HPD_UP_ON_5V].value > 0){
											if(gHDMI20RxHandler[i].gWasHDCP22Written > 0){
												HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, i);
											}
											__HDMI20_HAL_Rx_Set_EnableHPD(i, 1, 1, __L__);
										}
										else{
											HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_REQUEST_HPD ,i);
										}

										hpdWaitCnt[i] = 0;
									}
								}
								else{
									HDMI20_VIDEO("Notice [%d] : HPD down even without connect_request\n", i);
									if(HDMI20_HAL_IsSCDCvalueUD(i)){
										HDMI20_VIDEO("Notice [%d] Just HPD up due to SCDC is high\n", i);
										__HDMI20_HAL_Rx_Set_EnableHPD(i, 1, 1, __L__);
									}
									else{
										HDMI20_HAL_ConnectCable(i, ON);
									}
								}
							} // End of if(HDMI20_HAL_IsHPD_Up

						}
					}

					if(gHDMI20RxHandler[i].connected5Vtime < gHDMI20RxDevControler[HDMI20__HOLD_TIME_5V_DETECTION].value){
						gHDMI20RxHandler[i].connected5Vtime += gHDMI20Thread.mSleep;
					}

					/* HDCP1.4 stable check */
					if(( ((gHDMI20RxHandler[i].ctrl.bsp_read(0xe0) & 0x003F0000)>>16) >= 0x06)|| gHDMI20RxHandler[i].ctrl.bsp_read(0xFC) == 0x101) {
						if(gHDMI20RxHandler[i].stablehdcp14time <= gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY].value){
							gHDMI20RxHandler[i].stablehdcp14time += gHDMI20Thread.mSleep;
						}
					}
					else{
						gHDMI20RxHandler[i].stablehdcp14time = 0;
					}

				} // End of if(gHDMI20RxHandler[i].is5Vconnected == 0)

				if(gHDMI20RxDevControler[HDMI20__ENABLE_ISR_PROFILER].value > 0){
					if(__t_counter_isr_profile == 0){
						for(y=0;y<HDMI20_ISR_MAXNUM;y++){
							gHDMI20RxHandler[i].isr_count[y] = gHDMI20RxHandler[i].ctrl.isr_count[y];
						}
						__t_counter_isr_profile++;
					}
					else if( __t_counter_isr_profile >= gHDMI20RxDevControler[HDMI20__ENABLE_ISR_PROFILER].value){
						/* Calculate Data */
						for(y=0;y<HDMI20_ISR_MAXNUM;y++){
							gHDMI20RxHandler[i].isr_count[y] = gHDMI20RxHandler[i].ctrl.isr_count[y] - gHDMI20RxHandler[i].isr_count[y];
						}

						/* Print */	
						if(gHDMI20RxDevControler[HDMI20__ISR_PROFILER_TYPE].value >= HDMI20_ISR_MAXNUM){
							for(y=0;y<HDMI20_ISR_MAXNUM;y++){
								if(gHDMI20RxHandler[i].isr_count[y] != 0){
									HDMI20_DBG("DBG %d : ISR TYPE[%02d] [%s] = [%d]\n", i, y, isr_type_to_str(y), gHDMI20RxHandler[i].isr_count[y]);  
								}
							}
						}
						else{
							HDMI20_DBG("DBG %d : ISR TYPE[%02d] [%s] = [%d]\n", i, y, isr_type_to_str(gHDMI20RxDevControler[HDMI20__ISR_PROFILER_TYPE].value),\
									gHDMI20RxHandler[i].isr_count[gHDMI20RxDevControler[HDMI20__ISR_PROFILER_TYPE].value]);
						}
						__t_counter_isr_profile = 0;
					}
					else{
						__t_counter_isr_profile++;
					}
				}
			} // End of if(tx5Vconnected)
			else{
				/* 5V is not connected */
				gHDMI20RxHandler[i].connected5Vtime = 0;

				if(gHDMI20RxHandler[i].restartHpdFlagUp == true){
					if(HDMI20_HAL_IsHPD_Up(i) != 0){
						HDMI20_VIDEO("Notice %d : Found RestartHPD on Main Thread. Initiate Timing and PDB Down\n", i);
						HDMI20_PHY_InitiateTCSHist(i);

						/* Clear Dolby HDR */
						gHDMI20RxHandler[i].isDolbyHDR = (int)HDMI_DOLBY_STATE_OFF;
						
						/* Clear VRR releated mode */
						gHDMI20RxHandler[i].isFreeSyncMode = 0;

						gHDMI20RxHandler[i].isAllmMode = 0;
						gHDMI20RxHandler[i].allm_recieve_time = 0;

						/* Clear TCS data */
						HDMI20_PHY_Update_TMDS_TCS_Value(i, 1);

						gHDMI20RxHandler[i].isLinkInitiated = 0;
						gHDMI20RxHandler[i].ctrl.isMute = 0;

						gHDMI20RxHandler[i].isHDCP14 = 0;
						gHDMI20RxHandler[i].isHDCP22 = 0;
						gHDMI20RxHandler[i].isHDCP22Ncap = 0;

						gHDMI20RxHandler[i].isScdcUD = 0;

						gHDMI20RxHandler[i].ctrl.stable_cnt = 0;

						HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, 1, __L__);
						__HDMI20_HAL_Rx_InitiateHDMI20Data(i, 1);
						HDMI20_HAL_ClearChangeFlags(i);

						
						data = gHDMI20RxHandler[i].ctrl.bsp_read(0xb4);
						data |= (0x00010000);
						gHDMI20RxHandler[i].ctrl.bsp_write(0xb4, data);

						/* Audio Mute */
						HDMI20_HAL_Rx_Set_AudioReset(i);

						/* Reset HDCP */
						gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0,  gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
						__HDMI20_HAL_Rx_Set_EnableHPD(i ,0, 1, __L__);

						gHDMI20RxHandler[i].ctrl.bsp_write(0x808, 0x0);

						gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0,  gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);

						gHDMI20RxHandler[i].is5Vconnected = 0;

						gHDMI20RxHandler[i].phyLostCnt = 0;
						gHDMI20RxHandler[i].isTimingInvalid = 0;


						HDMI20_PHY_ControlPhyPDB(i, 0);
					}
				}
				else{
					if(HDMI20_HAL_IsHPD_Up(i) != 0){
						HDMI20_VIDEO("Notice [%d] : HPD was UP even though 5V is Low. Set HPD LOW\n", i);
						__HDMI20_HAL_Rx_Set_EnableHPD(i, 0, 1, __L__);
					}
				}
			}
		} // End of for(i=0;i<1;i++)

		gHDMI20Thread.stamp = 1;
		msleep(gHDMI20Thread.mSleep);
	} // End of While(1)

	gHDMI20Thread.stamp = 0;
	gHDMI20Thread.isAlive = 0;
}

static int __HDMI20_HAL_Rx_GetHDMIState(UINT8 port, LX_HDMI_STATUS_T *pHdmiStatus, int size)
{
	int ret = RET_ERROR;
	UINT32 video_format;
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

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_STATUS_T));

		/* Step 2. Copy data */
		if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
			userdata.bHdmiMode = 0;
		}
		else{
			userdata.bHdmiMode = 1;
		}

		video_format = gHDMI20RxHandler[port].ctrl.bsp_read(0x3A4);
		video_format = (video_format & 0x60); video_format = video_format>>5;
		video_format = video_format & 0x3;

		if(video_format == 0){
			video_format = (UINT32)((gHDMI20RxHandler[port].dataPacket[AVI][5]&0x60)>>5);
		}


		userdata.csc =(UINT16)video_format;
		
		/* 2016/06/30 won.hur : Defence code for DVI CSC */
		if(userdata.csc > 0){
			if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1450){
					HDMI20_DBG("DBG %d : Warning! DVI CSC YCbCr detected. SW WA activated\n", port);
				}

				/* Overwrite CSC to RGB */
				userdata.csc = 0;
			}
		}

		userdata.eHotPlug = gHDMI20RxHandler[port].isHPD;
		
		/* Update DCM for MW */
		switch(gHDMI20RxHandler[port].currentDCMMode){
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
			
		userdata.pixelRepet = gHDMI20RxHandler[port].timing_info.pixel_repetition;
		//userdata.pixelRepet = 0; 
		
		ret = copy_to_user((LX_HDMI_STATUS_T *)pHdmiStatus, &userdata, sizeof(LX_HDMI_STATUS_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "HDMI_STATE", port);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


static int __HDMI20_HAL_Rx_Set_HDCP22Info(UINT8 port, int isInitiated)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		gHDMI20RxHandler[port].gWasHDCP22Written = isInitiated ;
		gHDMI20RxHandler[port].gWasHDCP22FuncCalled = isInitiated;

		ret = RET_OK;
	} while(0);

	return ret;
}

static void __HDMI20_HAL_Rx_Init_Dev_Handler(UINT8 isResume)
{
	/* Initiate handler */

	if(isResume == 0){
		sAledTop.pSwAddr = NULL;
		sAledTop.hwAddr = gHDMI20ChipRegHandler.aled_top_ADDR;
		sAledTop.size = gHDMI20ChipRegHandler.aled_top_SIZE;
	}

	/* Step 1. Init hdmi20 port[0] device data */
	if(isResume == 0){
		gHDMI20RxHandler[0].port = (HDMI20_HAL_NUMBER_OF_PHY_FOR_LINK - 1 );
		gHDMI20RxHandler[0].phyI2CSlaveAddr = gHDMI20ChipRegHandler.phyI2CSlaveAddr[0];
		gHDMI20RxHandler[0].phyI2CSlaveAddr_B1 = gHDMI20ChipRegHandler.phyI2CSlaveAddr_B1[0];
		gHDMI20RxHandler[0].irq_5V_handler = HDMI20_HAL_RX0_TOP_IRQ_Handler;
		gHDMI20RxHandler[0].top_write = HDMI20_HAL_Rx_TOP_Write_Port0;
		gHDMI20RxHandler[0].top_read = HDMI20_HAL_Rx_TOP_Read_Port0;
		gHDMI20RxHandler[0].aled_write = HDMI20_HAL_Rx_ALED_Write_Port0;
		gHDMI20RxHandler[0].aled_read = HDMI20_HAL_Rx_ALED_Read_Port0;
		gHDMI20RxHandler[0].control_top_irq = HDMI20_HAL_RX0_Enable_TOP_IRQ;
		gHDMI20RxHandler[0].resetSyncMonitor = HDMI20_HAL_RX0_Reset_TOP_SyncInfo;
		gHDMI20RxHandler[0].irq = gHDMI20ChipRegHandler.irq_LINK[0];
		gHDMI20RxHandler[0].top_irq = gHDMI20ChipRegHandler.irq_TOP[0];
		gHDMI20RxHandler[0].linkmem.hwAddr = gHDMI20ChipRegHandler.ctrl_ADDR[0];
		gHDMI20RxHandler[0].linkmem.size = gHDMI20ChipRegHandler.ctrl_SIZE[0];
		gHDMI20RxHandler[0].linkmem.pSwAddr = NULL;
		gHDMI20RxHandler[0].topmem.hwAddr = gHDMI20ChipRegHandler.top_ADDR[0];
		gHDMI20RxHandler[0].topmem.size = gHDMI20ChipRegHandler.top_SIZE[0];
		gHDMI20RxHandler[0].topmem.pSwAddr = NULL;
		gHDMI20RxHandler[0].aledmem.hwAddr = gHDMI20ChipRegHandler.aled_ADDR[0];
		gHDMI20RxHandler[0].aledmem.size = gHDMI20ChipRegHandler.aled_SIZE[0];
		gHDMI20RxHandler[0].aledmem.pSwAddr = NULL;
		gHDMI20RxHandler[0].ipcmem.hwAddr = 0;
		gHDMI20RxHandler[0].ipcmem.size = 0;
		gHDMI20RxHandler[0].ipcmem.pSwAddr = NULL;
		gHDMI20RxHandler[0].locking_time  = 0;
		gHDMI20RxHandler[0].isHPD = 0;
		gHDMI20RxHandler[0].phyInitiatedMode = 0;
		gHDMI20RxHandler[0].scdc_change = 0;
		gHDMI20RxHandler[0].video_change = 0;
		gHDMI20RxHandler[0].real_tmds_clk = 0;
		gHDMI20RxHandler[0].real_pixel_clk = 0;
		gHDMI20RxHandler[0].dcm_change = 0;
		gHDMI20RxHandler[0].aksv_change = 0;
		gHDMI20RxHandler[0].audio_change = 0;
		gHDMI20RxHandler[0].tmds_change = 0;
		gHDMI20RxHandler[0].isScdcUD = 0;
		gHDMI20RxHandler[0].phyLostCnt = 0;
		gHDMI20RxHandler[0].isTimingInvalid = 0;
		/* Step 1-1. Init Link handler settings */
		gHDMI20RxHandler[0].ctrl.tmds_clock_old = 0;
		gHDMI20RxHandler[0].ctrl.status = 0;
		gHDMI20RxHandler[0].vtotalbuffer = 0;
		gHDMI20RxHandler[0].updateTimingTime = 0;
		gHDMI20RxHandler[0].isHDCP22 = 0;
		gHDMI20RxHandler[0].isHDCP22Ncap = 0;
		gHDMI20RxHandler[0].isHDCP14 = 0;
		gHDMI20RxHandler[0].isMHLMode = 0;
		gHDMI20RxHandler[0].isHPDInverseMode = 0;	
	}
	gHDMI20RxHandler[0].hdmiDisabled = 0;
	gHDMI20RxHandler[0].restartHPDTimeStamp = 0;
	gHDMI20RxHandler[0].restartHpdFlagUp = false;
	gHDMI20RxHandler[0].audioStableCnt = 0;
	gHDMI20RxHandler[0].audioChMapCnt = 0;
	gHDMI20RxHandler[0].audioChMapStandByCnt = 0;
	gHDMI20RxHandler[0].audioForceMuteCnt = 0;
	gHDMI20RxHandler[0].audioDbgPrintCnt = 0;
	gHDMI20RxHandler[0].isAudioTypeChangeIrq = 0;
	gHDMI20RxHandler[0].isAudioRegReady = 0;
	gHDMI20RxHandler[0].isHBRaudio = 0;
	gHDMI20RxHandler[0].audioFifoErrMuteCnt = 0;
	gHDMI20RxHandler[0].audioAcrResetCnt = 0;
	gHDMI20RxHandler[0].audioIrqFifoErrCnt = 0;
	gHDMI20RxHandler[0].audioInfo.linkNumber = 0;
	gHDMI20RxHandler[0].audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
	gHDMI20RxHandler[0].audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
	gHDMI20RxHandler[0].isLinkInitiated = 0;
	gHDMI20RxHandler[0].localmutetimer = 0;
	gHDMI20RxHandler[0].isAudioARCMode = 0;
	gHDMI20RxHandler[0].isPhyLocked = 0;
	gHDMI20RxHandler[0].phyTCSDone = 0;
	gHDMI20RxHandler[0].linkPhyLocked = 0;
	gHDMI20RxHandler[0].hpd_request = 0;
	gHDMI20RxHandler[0].connect_request = 0;
	gHDMI20RxHandler[0].phy_rst_request = 0;
	gHDMI20RxHandler[0].is5Vconnected  = 0;
	gHDMI20RxHandler[0].audioStandByCnt = 0;
	gHDMI20RxHandler[0].ctrl.isMute = 0;
	gHDMI20RxHandler[0].isAudioMute = 1;
	gHDMI20RxHandler[0].isAudioMuteControl = 1;
	gHDMI20RxHandler[0].currentDCMMode = 0;
	gHDMI20RxHandler[0].connected5Vtime = 0;
	gHDMI20RxHandler[0].ctrl.device_id = HDMI20_HAL_LINK_DEVICE_ID_PORT0;
	gHDMI20RxHandler[0].ctrl.log_error = HDMI20_HAL_Log_Error;
	gHDMI20RxHandler[0].ctrl.log_info = HDMI20_HAL_Log_Info;
	gHDMI20RxHandler[0].ctrl.bsp_read = HDMI20_HAL_BSP_Read_Port0;
	gHDMI20RxHandler[0].ctrl.bsp_write = HDMI20_HAL_BSP_Write_Port0;
	gHDMI20RxHandler[0].ctrl.spin_init = __HDMI20_Spin_Init;
	gHDMI20RxHandler[0].ctrl.spin_destroy =  __HDMI20_Destory_Spinlock;
	gHDMI20RxHandler[0].ctrl.spin_lock_irq_save = __HDMI20_Spin_IRQ_Lock;
	gHDMI20RxHandler[0].ctrl.spin_unlock_irq_restore = __HDMI20_Spin_IRQ_UnLock;
	gHDMI20RxHandler[0].ctrl.cfg_clk = HDMI20_RX_CLOCK_CONFIG_KHZ;
	gHDMI20RxHandler[0].ctrl.md_clk = HDMI20_RX_CLOCK_MODE_DETECTION_KHZ;
	gHDMI20RxHandler[0].ctrl.stable_cnt = 0;
	gHDMI20RxHandler[0].countOf6GHpdTgSwWa = gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value;
	
	/* Step 2. Init hdmi20 port1 device data */
	if(isResume == 0){
		gHDMI20RxHandler[1].port = (HDMI20_HAL_NUMBER_OF_PHY_FOR_LINK - 1 );
		gHDMI20RxHandler[1].phyI2CSlaveAddr = gHDMI20ChipRegHandler.phyI2CSlaveAddr[1];
		gHDMI20RxHandler[1].phyI2CSlaveAddr_B1 = gHDMI20ChipRegHandler.phyI2CSlaveAddr_B1[1];
		gHDMI20RxHandler[1].irq_5V_handler = HDMI20_HAL_RX1_TOP_IRQ_Handler;
		gHDMI20RxHandler[1].top_write = HDMI20_HAL_Rx_TOP_Write_Port1;
		gHDMI20RxHandler[1].top_read = HDMI20_HAL_Rx_TOP_Read_Port1;
		gHDMI20RxHandler[1].aled_write = HDMI20_HAL_Rx_ALED_Write_Port1;
		gHDMI20RxHandler[1].aled_read = HDMI20_HAL_Rx_ALED_Read_Port1;
		gHDMI20RxHandler[1].control_top_irq = HDMI20_HAL_RX1_Enable_TOP_IRQ;
		gHDMI20RxHandler[1].resetSyncMonitor = HDMI20_HAL_RX1_Reset_TOP_SyncInfo;
		gHDMI20RxHandler[1].irq = gHDMI20ChipRegHandler.irq_LINK[1];
		gHDMI20RxHandler[1].top_irq = gHDMI20ChipRegHandler.irq_TOP[1];
		gHDMI20RxHandler[1].linkmem.hwAddr = gHDMI20ChipRegHandler.ctrl_ADDR[1];
		gHDMI20RxHandler[1].linkmem.size = gHDMI20ChipRegHandler.ctrl_SIZE[1];
		gHDMI20RxHandler[1].linkmem.pSwAddr = NULL;
		gHDMI20RxHandler[1].topmem.hwAddr = gHDMI20ChipRegHandler.top_ADDR[1];
		gHDMI20RxHandler[1].topmem.size = gHDMI20ChipRegHandler.top_SIZE[1];
		gHDMI20RxHandler[1].topmem.pSwAddr = NULL;
		gHDMI20RxHandler[1].aledmem.hwAddr = gHDMI20ChipRegHandler.aled_ADDR[1];
		gHDMI20RxHandler[1].aledmem.size = gHDMI20ChipRegHandler.aled_SIZE[1];
		gHDMI20RxHandler[1].aledmem.pSwAddr = NULL;
		gHDMI20RxHandler[1].ipcmem.hwAddr = 0;
		gHDMI20RxHandler[1].ipcmem.size = 0;
		gHDMI20RxHandler[1].ipcmem.pSwAddr = NULL;
		gHDMI20RxHandler[1].locking_time  = 0;
		gHDMI20RxHandler[1].isHPD = 0;
		gHDMI20RxHandler[1].real_tmds_clk = 0;
		gHDMI20RxHandler[1].real_pixel_clk = 0;
		gHDMI20RxHandler[1].phyInitiatedMode = 0;
		gHDMI20RxHandler[1].scdc_change = 0;
		gHDMI20RxHandler[1].video_change = 0;
		gHDMI20RxHandler[1].dcm_change = 0;
		gHDMI20RxHandler[1].aksv_change = 0;
		gHDMI20RxHandler[1].audio_change = 0;
		gHDMI20RxHandler[1].tmds_change = 0;
		gHDMI20RxHandler[1].isScdcUD = 0;
		gHDMI20RxHandler[1].phyLostCnt = 0;
		gHDMI20RxHandler[1].isTimingInvalid = 0;

		/* Step 2-1. Init Link handler settings */
		gHDMI20RxHandler[1].ctrl.tmds_clock_old = 0;
		gHDMI20RxHandler[1].ctrl.status = 0;
		gHDMI20RxHandler[1].vtotalbuffer = 0;
		gHDMI20RxHandler[1].updateTimingTime = 0;
		gHDMI20RxHandler[1].isHDCP22 = 0;
		gHDMI20RxHandler[1].isHDCP22Ncap = 0;
		gHDMI20RxHandler[1].isHDCP14 = 0;
		gHDMI20RxHandler[1].isMHLMode = 0;
		gHDMI20RxHandler[1].isHPDInverseMode = 0;
	}
	gHDMI20RxHandler[1].hdmiDisabled = 0;
	gHDMI20RxHandler[1].restartHPDTimeStamp = 0;
	gHDMI20RxHandler[1].restartHpdFlagUp = false;
	gHDMI20RxHandler[1].audioStableCnt = 0;
	gHDMI20RxHandler[1].audioChMapCnt = 0;
	gHDMI20RxHandler[1].audioChMapStandByCnt = 0;
	gHDMI20RxHandler[1].audioForceMuteCnt = 0;
	gHDMI20RxHandler[1].audioDbgPrintCnt = 0;
	gHDMI20RxHandler[1].isAudioTypeChangeIrq = 0;
	gHDMI20RxHandler[1].isAudioRegReady = 0;
	gHDMI20RxHandler[1].isHBRaudio = 0;
	gHDMI20RxHandler[1].audioFifoErrMuteCnt = 0;
	gHDMI20RxHandler[1].audioAcrResetCnt = 0;
	gHDMI20RxHandler[1].audioIrqFifoErrCnt = 0;
	gHDMI20RxHandler[1].audioInfo.linkNumber = 1;
	gHDMI20RxHandler[1].audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
	gHDMI20RxHandler[1].audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
	gHDMI20RxHandler[1].isLinkInitiated = 0;
	gHDMI20RxHandler[1].localmutetimer = 0;
	gHDMI20RxHandler[1].isAudioARCMode = 0;
	gHDMI20RxHandler[1].isPhyLocked = 0;
	gHDMI20RxHandler[1].phyTCSDone = 0;
	gHDMI20RxHandler[1].linkPhyLocked = 0;
	gHDMI20RxHandler[1].hpd_request = 0;
	gHDMI20RxHandler[1].connect_request = 0;
	gHDMI20RxHandler[1].phy_rst_request = 0;
	gHDMI20RxHandler[1].is5Vconnected  = 0;
	gHDMI20RxHandler[1].audioStandByCnt = 0;
	gHDMI20RxHandler[1].ctrl.isMute = 0;
	gHDMI20RxHandler[1].isAudioMute = 1;
	gHDMI20RxHandler[1].isAudioMuteControl = 1;
	gHDMI20RxHandler[1].currentDCMMode = 0;
	gHDMI20RxHandler[1].connected5Vtime = 0;
	gHDMI20RxHandler[1].ctrl.device_id = HDMI20_HAL_LINK_DEVICE_ID_PORT1;
	gHDMI20RxHandler[1].ctrl.log_error = HDMI20_HAL_Log_Error;
	gHDMI20RxHandler[1].ctrl.log_info = HDMI20_HAL_Log_Info;
	gHDMI20RxHandler[1].ctrl.bsp_read = HDMI20_HAL_BSP_Read_Port1;
	gHDMI20RxHandler[1].ctrl.bsp_write = HDMI20_HAL_BSP_Write_Port1;
	gHDMI20RxHandler[1].ctrl.spin_init = __HDMI20_Spin_Init;
	gHDMI20RxHandler[1].ctrl.spin_destroy = __HDMI20_Destory_Spinlock;
	gHDMI20RxHandler[1].ctrl.spin_lock_irq_save =  __HDMI20_Spin_IRQ_Lock;
	gHDMI20RxHandler[1].ctrl.spin_unlock_irq_restore = __HDMI20_Spin_IRQ_UnLock;
	gHDMI20RxHandler[1].ctrl.cfg_clk = HDMI20_RX_CLOCK_CONFIG_KHZ;
	gHDMI20RxHandler[1].ctrl.md_clk = HDMI20_RX_CLOCK_MODE_DETECTION_KHZ;
	gHDMI20RxHandler[1].ctrl.stable_cnt = 0;
	gHDMI20RxHandler[1].countOf6GHpdTgSwWa = gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value;

	/* Step 3. Init hdmi20 port2 device data */
	if(isResume == 0){
		gHDMI20RxHandler[2].port = (HDMI20_HAL_NUMBER_OF_PHY_FOR_LINK - 1 );
		gHDMI20RxHandler[2].phyI2CSlaveAddr = gHDMI20ChipRegHandler.phyI2CSlaveAddr[2];
		gHDMI20RxHandler[2].phyI2CSlaveAddr_B1 = gHDMI20ChipRegHandler.phyI2CSlaveAddr_B1[2];
		gHDMI20RxHandler[2].irq_5V_handler = HDMI20_HAL_RX2_TOP_IRQ_Handler;
		gHDMI20RxHandler[2].top_write = HDMI20_HAL_Rx_TOP_Write_Port2;
		gHDMI20RxHandler[2].top_read = HDMI20_HAL_Rx_TOP_Read_Port2;
		gHDMI20RxHandler[2].aled_write = HDMI20_HAL_Rx_ALED_Write_Port2;
		gHDMI20RxHandler[2].aled_read = HDMI20_HAL_Rx_ALED_Read_Port2;
		gHDMI20RxHandler[2].control_top_irq = HDMI20_HAL_RX2_Enable_TOP_IRQ;
		gHDMI20RxHandler[2].resetSyncMonitor = HDMI20_HAL_RX2_Reset_TOP_SyncInfo;
		gHDMI20RxHandler[2].irq = gHDMI20ChipRegHandler.irq_LINK[2];
		gHDMI20RxHandler[2].top_irq = gHDMI20ChipRegHandler.irq_TOP[2];
		gHDMI20RxHandler[2].linkmem.hwAddr = gHDMI20ChipRegHandler.ctrl_ADDR[2];
		gHDMI20RxHandler[2].linkmem.size = gHDMI20ChipRegHandler.ctrl_SIZE[2];
		gHDMI20RxHandler[2].linkmem.pSwAddr = NULL;
		gHDMI20RxHandler[2].topmem.hwAddr = gHDMI20ChipRegHandler.top_ADDR[2];
		gHDMI20RxHandler[2].topmem.size = gHDMI20ChipRegHandler.top_SIZE[2];
		gHDMI20RxHandler[2].topmem.pSwAddr = NULL;
		gHDMI20RxHandler[2].aledmem.hwAddr = gHDMI20ChipRegHandler.aled_ADDR[2];
		gHDMI20RxHandler[2].aledmem.size = gHDMI20ChipRegHandler.aled_SIZE[2];
		gHDMI20RxHandler[2].aledmem.pSwAddr = NULL;
		gHDMI20RxHandler[2].ipcmem.hwAddr = 0;
		gHDMI20RxHandler[2].ipcmem.size = 0;
		gHDMI20RxHandler[2].ipcmem.pSwAddr = NULL;
		gHDMI20RxHandler[2].locking_time  = 0;
		gHDMI20RxHandler[2].isHPD = 0;
		gHDMI20RxHandler[2].real_tmds_clk = 0;
		gHDMI20RxHandler[2].real_pixel_clk = 0;
		gHDMI20RxHandler[2].phyInitiatedMode = 0;
		gHDMI20RxHandler[2].scdc_change = 0;
		gHDMI20RxHandler[2].video_change = 0;
		gHDMI20RxHandler[2].dcm_change = 0;
		gHDMI20RxHandler[2].aksv_change = 0;
		gHDMI20RxHandler[2].audio_change = 0;
		gHDMI20RxHandler[2].tmds_change = 0;
		gHDMI20RxHandler[2].isScdcUD = 0;
		gHDMI20RxHandler[2].phyLostCnt = 0;
		gHDMI20RxHandler[2].isTimingInvalid = 0;

		/* Step 3-1. Init Link handler settings */
		gHDMI20RxHandler[2].ctrl.tmds_clock_old = 0;
		gHDMI20RxHandler[2].ctrl.status = 0;
		gHDMI20RxHandler[2].vtotalbuffer = 0;
		gHDMI20RxHandler[2].updateTimingTime = 0;
		gHDMI20RxHandler[2].isHDCP22 = 0;
		gHDMI20RxHandler[2].isHDCP22Ncap = 0;
		gHDMI20RxHandler[2].isHDCP14 = 0;
		gHDMI20RxHandler[2].isMHLMode = 0;
		gHDMI20RxHandler[2].isHPDInverseMode = 0;
	}
	gHDMI20RxHandler[2].hdmiDisabled = 0;
	gHDMI20RxHandler[2].restartHPDTimeStamp = 0;
	gHDMI20RxHandler[2].restartHpdFlagUp = false;
	gHDMI20RxHandler[2].audioStableCnt = 0;
	gHDMI20RxHandler[2].audioChMapCnt = 0;
	gHDMI20RxHandler[2].audioChMapStandByCnt = 0;
	gHDMI20RxHandler[2].audioForceMuteCnt = 0;
	gHDMI20RxHandler[2].audioDbgPrintCnt = 0;
	gHDMI20RxHandler[2].isAudioTypeChangeIrq = 0;
	gHDMI20RxHandler[2].isAudioRegReady = 0;
	gHDMI20RxHandler[2].isHBRaudio = 0;
	gHDMI20RxHandler[2].audioFifoErrMuteCnt = 0;
	gHDMI20RxHandler[2].audioAcrResetCnt = 0;
	gHDMI20RxHandler[2].audioIrqFifoErrCnt = 0;
	gHDMI20RxHandler[2].audioInfo.linkNumber = 1;
	gHDMI20RxHandler[2].audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
	gHDMI20RxHandler[2].audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
	gHDMI20RxHandler[2].isLinkInitiated = 0;
	gHDMI20RxHandler[2].localmutetimer = 0;
	gHDMI20RxHandler[2].isAudioARCMode = 0;
	gHDMI20RxHandler[2].isPhyLocked = 0;
	gHDMI20RxHandler[2].phyTCSDone = 0;
	gHDMI20RxHandler[2].linkPhyLocked = 0;
	gHDMI20RxHandler[2].hpd_request = 0;
	gHDMI20RxHandler[2].connect_request = 0;
	gHDMI20RxHandler[2].phy_rst_request = 0;
	gHDMI20RxHandler[2].is5Vconnected  = 0;
	gHDMI20RxHandler[2].audioStandByCnt = 0;
	gHDMI20RxHandler[2].ctrl.isMute = 0;
	gHDMI20RxHandler[2].isAudioMute = 1;
	gHDMI20RxHandler[2].isAudioMuteControl = 1;
	gHDMI20RxHandler[2].currentDCMMode = 0;
	gHDMI20RxHandler[2].connected5Vtime = 0;
	gHDMI20RxHandler[2].ctrl.device_id = HDMI20_HAL_LINK_DEVICE_ID_PORT2;
	gHDMI20RxHandler[2].ctrl.log_error = HDMI20_HAL_Log_Error;
	gHDMI20RxHandler[2].ctrl.log_info = HDMI20_HAL_Log_Info;
	gHDMI20RxHandler[2].ctrl.bsp_read = HDMI20_HAL_BSP_Read_Port2;
	gHDMI20RxHandler[2].ctrl.bsp_write = HDMI20_HAL_BSP_Write_Port2;
	gHDMI20RxHandler[2].ctrl.spin_init = __HDMI20_Spin_Init;
	gHDMI20RxHandler[2].ctrl.spin_destroy = __HDMI20_Destory_Spinlock;
	gHDMI20RxHandler[2].ctrl.spin_lock_irq_save =  __HDMI20_Spin_IRQ_Lock;
	gHDMI20RxHandler[2].ctrl.spin_unlock_irq_restore = __HDMI20_Spin_IRQ_UnLock;
	gHDMI20RxHandler[2].ctrl.cfg_clk = HDMI20_RX_CLOCK_CONFIG_KHZ;
	gHDMI20RxHandler[2].ctrl.md_clk = HDMI20_RX_CLOCK_MODE_DETECTION_KHZ;
	gHDMI20RxHandler[2].ctrl.stable_cnt = 0;
	gHDMI20RxHandler[2].countOf6GHpdTgSwWa = gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value;

	/* Step 4. Init hdmi20 port3 device data */
	if(isResume == 0){
		gHDMI20RxHandler[3].port = (HDMI20_HAL_NUMBER_OF_PHY_FOR_LINK - 1 );
		gHDMI20RxHandler[3].phyI2CSlaveAddr = gHDMI20ChipRegHandler.phyI2CSlaveAddr[3];
		gHDMI20RxHandler[3].phyI2CSlaveAddr_B1 = gHDMI20ChipRegHandler.phyI2CSlaveAddr_B1[3];
		gHDMI20RxHandler[3].irq_5V_handler = HDMI20_HAL_RX3_TOP_IRQ_Handler;
		gHDMI20RxHandler[3].top_write = HDMI20_HAL_Rx_TOP_Write_Port3;
		gHDMI20RxHandler[3].top_read = HDMI20_HAL_Rx_TOP_Read_Port3;
		gHDMI20RxHandler[3].aled_write = HDMI20_HAL_Rx_ALED_Write_Port3;
		gHDMI20RxHandler[3].aled_read = HDMI20_HAL_Rx_ALED_Read_Port3;
		gHDMI20RxHandler[3].control_top_irq = HDMI20_HAL_RX3_Enable_TOP_IRQ;
		gHDMI20RxHandler[3].resetSyncMonitor = HDMI20_HAL_RX3_Reset_TOP_SyncInfo;
		gHDMI20RxHandler[3].irq = gHDMI20ChipRegHandler.irq_LINK[3];
		gHDMI20RxHandler[3].top_irq = gHDMI20ChipRegHandler.irq_TOP[3];
		gHDMI20RxHandler[3].linkmem.hwAddr = gHDMI20ChipRegHandler.ctrl_ADDR[3];
		gHDMI20RxHandler[3].linkmem.size = gHDMI20ChipRegHandler.ctrl_SIZE[3];
		gHDMI20RxHandler[3].linkmem.pSwAddr = NULL;
		gHDMI20RxHandler[3].topmem.hwAddr = gHDMI20ChipRegHandler.top_ADDR[3];
		gHDMI20RxHandler[3].topmem.size = gHDMI20ChipRegHandler.top_SIZE[3];
		gHDMI20RxHandler[3].topmem.pSwAddr = NULL;
		gHDMI20RxHandler[3].aledmem.hwAddr = gHDMI20ChipRegHandler.aled_ADDR[3];
		gHDMI20RxHandler[3].aledmem.size = gHDMI20ChipRegHandler.aled_SIZE[3];
		gHDMI20RxHandler[3].aledmem.pSwAddr = NULL;
		gHDMI20RxHandler[3].ipcmem.hwAddr = 0;
		gHDMI20RxHandler[3].ipcmem.size = 0;
		gHDMI20RxHandler[3].ipcmem.pSwAddr = NULL;
		gHDMI20RxHandler[3].locking_time  = 0;
		gHDMI20RxHandler[3].isHPD = 0;
		gHDMI20RxHandler[3].real_tmds_clk = 0;
		gHDMI20RxHandler[3].real_pixel_clk = 0;
		gHDMI20RxHandler[3].phyInitiatedMode = 0;
		gHDMI20RxHandler[3].scdc_change = 0;
		gHDMI20RxHandler[3].video_change = 0;
		gHDMI20RxHandler[3].dcm_change = 0;
		gHDMI20RxHandler[3].aksv_change = 0;
		gHDMI20RxHandler[3].audio_change = 0;
		gHDMI20RxHandler[3].tmds_change = 0;
		gHDMI20RxHandler[3].isScdcUD = 0;
		gHDMI20RxHandler[3].phyLostCnt = 0;
		gHDMI20RxHandler[3].isTimingInvalid = 0;

		/* Step 2-1. Init Link handler settings */
		gHDMI20RxHandler[3].ctrl.tmds_clock_old = 0;
		gHDMI20RxHandler[3].ctrl.status = 0;
		gHDMI20RxHandler[3].vtotalbuffer = 0;
		gHDMI20RxHandler[3].updateTimingTime = 0;
		gHDMI20RxHandler[3].isHDCP22 = 0;
		gHDMI20RxHandler[3].isHDCP22Ncap = 0;
		gHDMI20RxHandler[3].isHDCP14 = 0;
		gHDMI20RxHandler[3].isMHLMode = 0;
		gHDMI20RxHandler[3].isHPDInverseMode = 0;
	}
	gHDMI20RxHandler[3].hdmiDisabled = 0;
	gHDMI20RxHandler[3].restartHPDTimeStamp = 0;
	gHDMI20RxHandler[3].restartHpdFlagUp = false;
	gHDMI20RxHandler[3].audioStableCnt = 0;
	gHDMI20RxHandler[3].audioChMapCnt = 0;
	gHDMI20RxHandler[3].audioChMapStandByCnt = 0;
	gHDMI20RxHandler[3].audioForceMuteCnt = 0;
	gHDMI20RxHandler[3].audioDbgPrintCnt = 0;
	gHDMI20RxHandler[3].isAudioTypeChangeIrq = 0;
	gHDMI20RxHandler[3].isAudioRegReady = 0;
	gHDMI20RxHandler[3].isHBRaudio = 0;
	gHDMI20RxHandler[3].audioFifoErrMuteCnt = 0;
	gHDMI20RxHandler[3].audioAcrResetCnt = 0;
	gHDMI20RxHandler[3].audioIrqFifoErrCnt = 0;
	gHDMI20RxHandler[3].audioInfo.linkNumber = 1;
	gHDMI20RxHandler[3].audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
	gHDMI20RxHandler[3].audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
	gHDMI20RxHandler[3].isLinkInitiated = 0;
	gHDMI20RxHandler[3].localmutetimer = 0;
	gHDMI20RxHandler[3].isAudioARCMode = 0;
	gHDMI20RxHandler[3].isPhyLocked = 0;
	gHDMI20RxHandler[3].phyTCSDone = 0;
	gHDMI20RxHandler[3].linkPhyLocked = 0;
	gHDMI20RxHandler[3].hpd_request = 0;
	gHDMI20RxHandler[3].connect_request = 0;
	gHDMI20RxHandler[3].phy_rst_request = 0;
	gHDMI20RxHandler[3].is5Vconnected  = 0;
	gHDMI20RxHandler[3].audioStandByCnt = 0;
	gHDMI20RxHandler[3].ctrl.isMute = 0;
	gHDMI20RxHandler[3].isAudioMute = 1;
	gHDMI20RxHandler[3].isAudioMuteControl = 1;
	gHDMI20RxHandler[3].currentDCMMode = 0;
	gHDMI20RxHandler[3].connected5Vtime = 0;
	gHDMI20RxHandler[3].ctrl.device_id = HDMI20_HAL_LINK_DEVICE_ID_PORT3;
	gHDMI20RxHandler[3].ctrl.log_error = HDMI20_HAL_Log_Error;
	gHDMI20RxHandler[3].ctrl.log_info = HDMI20_HAL_Log_Info;
	gHDMI20RxHandler[3].ctrl.bsp_read = HDMI20_HAL_BSP_Read_Port3;
	gHDMI20RxHandler[3].ctrl.bsp_write = HDMI20_HAL_BSP_Write_Port3;
	gHDMI20RxHandler[3].ctrl.spin_init = __HDMI20_Spin_Init;
	gHDMI20RxHandler[3].ctrl.spin_destroy = __HDMI20_Destory_Spinlock;
	gHDMI20RxHandler[3].ctrl.spin_lock_irq_save =  __HDMI20_Spin_IRQ_Lock;
	gHDMI20RxHandler[3].ctrl.spin_unlock_irq_restore = __HDMI20_Spin_IRQ_UnLock;
	gHDMI20RxHandler[3].ctrl.cfg_clk = HDMI20_RX_CLOCK_CONFIG_KHZ;
	gHDMI20RxHandler[3].ctrl.md_clk = HDMI20_RX_CLOCK_MODE_DETECTION_KHZ;
	gHDMI20RxHandler[3].ctrl.stable_cnt = 0;
	gHDMI20RxHandler[3].countOf6GHpdTgSwWa = gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value;

	/* Initiate Flag */
	gHDMI20RxHandler[0].initiated = 1;
	gHDMI20RxHandler[1].initiated = 1;
	gHDMI20RxHandler[2].initiated = 1;
	gHDMI20RxHandler[3].initiated = 1;
}




static int __HDMI20_Destory_Spinlock(void *handler)
{
	HDMI20_VIDEO("Function called [0x%08x]\n", (UINT32)handler);

	return 0;
}


int HDMI20_HAL_Rx_SetLocalVideoMute(UINT8 port, int onOff, int useTimer, UINT32 caller_id)
{
	int ret = RET_ERROR;
	UINT32 data;
	UINT32 currentJiffiesMsec = 0;


	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1352){
			ret = RET_OK;
			break;
		}

		if(useTimer) currentJiffiesMsec = jiffies_to_msecs(jiffies);

		if(onOff){
			__HDMI20_HAL_SetVideoColorDomain(port);

			HDMI20_VIDEO("Notice [%d] : Set Local Video Mute => [%s]. Mode => [%s]. Caller =>[%d]\n", port, onOff?"On":"Off", useTimer?"Timer":"Force", caller_id);

			if(useTimer) { 
				gHDMI20RxHandler[port].localmutetimer = currentJiffiesMsec;
			}


			data = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);
			data |= (0x00010000);
			gHDMI20RxHandler[port].ctrl.bsp_write(0xb4, data);

		}
		else{
			if(useTimer){
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 1350){
					if(currentJiffiesMsec - gHDMI20RxHandler[port].localmutetimer >= gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_TIME].value){
						HDMI20_VIDEO("Notice [%d] : LocalMute release by hold time pass. Caller ID[%d]\n", port, caller_id);
						if(gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_TIME].value == gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_INIT_TIME].value){
							gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_TIME].value = gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_ORIGIN_TIME].value;
							HDMI20_VIDEO("Notice [%d] : Video stable for the first connection. Change Local Mute hold Thres\n", port);
							gHDMI20RxHandler[port].localmutetimer  = 0;
						}
						data = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);
						data &= (~0x00010000);
						gHDMI20RxHandler[port].ctrl.bsp_write(0xb4, data);
					}
					else{
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 208) HDMI20_DBG("NOTICE [%d] : LocalMute Hold [0x%x]-[0x%x] < [0x%x]. Caller ID[%d]\n",port,currentJiffiesMsec, gHDMI20RxHandler[port].localmutetimer, gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_TIME].value, caller_id);
					}
				}
			}
			else{
				HDMI20_VIDEO("Notice [%d] : LocalMute release by force. Caller_Id[%d]\n", port, caller_id);
				data = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);
				data &= (~0x00010000);
				gHDMI20RxHandler[port].ctrl.bsp_write(0xb4, data);
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI20_HAL_Rx_IsLocalMuteOn(UINT8 port)
{
	int ret = 0;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return 0;
	}

	if( gHDMI20RxHandler[port].ctrl.bsp_read(0xb4) & 0x00010000){
		ret = 1;
	}
	else{
		ret = 0;
	}

	return ret;
}

int HDMI20_HAL_Rx_SetLocalVideoMuteColor(UINT8 port, UINT32 isYCbCr)
{
	int ret = RET_ERROR;
	UINT32 data;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1351){
			HDMI20_DBG("DBG %d : Local Video Mute Color->isYCbCr[%d]\n", port, isYCbCr);
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1350){
			ret = RET_OK;
			break;
		}

		if(isYCbCr){
			data  = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);
			data &= (0x00010000);
			if(isYCbCr != 3) { data |= (0x00008000); }
			gHDMI20RxHandler[port].ctrl.bsp_write(0xB0, 0x8000);
			gHDMI20RxHandler[port].ctrl.bsp_write(0xB4, data);
		}
		else{
			data  = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);
			data &= (0x00010000);
			gHDMI20RxHandler[port].ctrl.bsp_write(0xB0, 0x0);
			gHDMI20RxHandler[port].ctrl.bsp_write(0xB4, data);
		}

		ret = RET_OK;
	} while(0);

	return ret;
}




int HDMI20_HAL_Rx_Initialize(LX_HDMI20_INIT_T *pData, int size, int isInternalCall)
{
	int i;
	int ret = RET_ERROR;
	LX_HDMI20_INIT_T	userData;

	HDMI20_INFO("Function called \n");

	do{
		if(gIsHDMI20KdrvOpen < 0){
			HDMI20_INFO("HDMI20 Not Opened yet.\n");
			break;
		}

		if(gIsHDMI20KdrvInitialized >= 0){
			HDMI20_ERROR("Ignore Multiple Initialize\n");
			ret = RET_OK;
			break;
		}

		/* Step 1. Check given args to proceed */
		if(isInternalCall > 0){
			/* Nothing to Check */
		}
		else{
			if(pData == NULL){
				HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
				break;
			}

			if(size != sizeof(LX_HDMI20_INIT_T)){
				HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_INIT_T), size);
				break;
			}
		}

		/* Step 2. Get User data to kernel*/
		if(isInternalCall > 0){
			for(i = 0; i<HDMI20_NUM_OF_RX_PORTS; i++)
			{
				userData.ipc_address[i] = gHDMI20ChipRegHandler.top_ADDR[i];
			}
			userData.number_of_ports = HDMI20_NUM_OF_RX_PORTS;
		}
		else{
			if( copy_from_user(&userData, (void __user *)pData, sizeof(LX_HDMI20_INIT_T))){
				HDMI20_ERROR("Cannot copy HDMI20 Initd ata structure from user\n");
				break;
			}
		}

		/* Step 3. Open Rx */
		for(i = 0; i<HDMI20_NUM_OF_RX_PORTS; i++)
		{
			/* Set Elliptic <-> Synopsys IPC address */
			gHDMI20RxHandler[i].ipcmem.hwAddr = userData.ipc_address[i];
			gHDMI20RxHandler[i].ipcmem.size = sizeof(UINT32);

			if(gHDMI20RxHandler[i].ipcmem.pSwAddr == NULL) {
				gHDMI20RxHandler[i].ipcmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].ipcmem.hwAddr, gHDMI20RxHandler[i].ipcmem.size);
			}
			else {
				iounmap((void *)gHDMI20RxHandler[i].ipcmem.pSwAddr);
				gHDMI20RxHandler[i].ipcmem.pSwAddr = (volatile UINT32 *)ioremap(gHDMI20RxHandler[i].ipcmem.hwAddr, gHDMI20RxHandler[i].ipcmem.size);
			}

			/* Step 3-1. Open Rx port [i] */
			HDMI20_INFO("Opening Synopsys Rx[%d] device\n", i);
			/* Link */
			ret = hdmi_rx_ctrl_open((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl);
			if( ret <0 ) { HDMI20_ERROR("Error opening HDMI20 port[%d] ctrl[%d]\n", i, ret); }
			/* HDCP */
			ret = hdmi_rx_ctrl_hdcp_config((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, (const struct hdmi_rx_ctrl_hdcp *)&gHDMI20RxHandler[i].hdcp);

			if( ret <0 ) { HDMI20_ERROR("Error opening HDMI20 port[%d] hdcp 1.4[%d]\n", i, ret); }
			/* Config Link Settings */
			ret = hdmi_rx_ctrl_config((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[i].ctrl, gHDMI20RxHandler[i].port);
			if( ret <0 ) { HDMI20_ERROR("Error on HDMI20 port[%d] initial configuration[%d]\n",i, ret); }
			/* HDMI MODE Recover */
			gHDMI20RxHandler[i].ctrl.bsp_write(0x080, gHDMI20RxDevControler[HDMI20__LINK_REG_0X80_HDMI_MODE_RECOVER].value);
			gHDMI20RxHandler[i].ctrl.bsp_write(0x16C, gHDMI20RxDevControler[HDMI20__LINK_REG_0X16C_HDMI_VERTICAL_TIMING].value);
			gHDMI20RxHandler[i].ctrl.bsp_write(0x140, gHDMI20RxDevControler[HDMI20__LINK_REG_0X140_HA_THRESHOLD].value);	
			gHDMI20RxHandler[i].ctrl.bsp_write(0xFF0, 0xFFFF);
		
			/* Register Link IRQ */
			ret = HDMI20_HAL_RequestIrq(i);
			if( ret <0 ) { HDMI20_ERROR("Failed to request HDMI20 port0 interrupt[%d]\n", ret); }

			ret = HDMI20_HAL_Register_IRQ_to_handler(i);
			if( ret <0 ) { HDMI20_ERROR("Failed to register IRQ handler to event handler[%d]\n", ret); }

			/* Initiate Audio data */
			memset((void *)&gHDMI20RxHandler[i].audio, 0, sizeof(struct hdmi_rx_ctrl_audio));
			memset((void *)&gHDMI20RxHandler[i].timing_info, 0, sizeof(struct hdmi_rx_ctrl_video));
			memset((void *)&gHDMI20RxHandler[i].sync_info, 0, sizeof(HDMI20_HAL_DBG_SYNC_INFO_T));

			/* Initiate Data Packet Buffer */
			HDMI20_ResetDataPacketBuffer(hdmi_rx_ctrl_packet_cnt, i);
			HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_MAXNUM, i);

			/* HDCP2.2 Write PUK*/
			gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_1, HDMI20_PUK_1);
			gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_2, HDMI20_PUK_2);
			gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_3, HDMI20_PUK_3);
			gHDMI20RxHandler[i].top_write(HDMI20_PUK_ADDR_4, HDMI20_PUK_4);

			gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_1, HDMI20_RX_DUK_1);
			gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_2, HDMI20_RX_DUK_2);
			gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_3, HDMI20_RX_DUK_3);
			gHDMI20RxHandler[i].top_write(HDMI20_DUK_ADDR_4, HDMI20_RX_DUK_4);

			/* SW Workaround for ACR pll mode */
			gHDMI20RxHandler[i].top_write(HDMI20_RX_ACR_PLL_MODE, 0x10001 );
		
			/* Check 5V status for both port due to unknown state */
			gHDMI20RxHandler[i].resetSyncMonitor(); 

			/* : Register 5V IRQ */
			ret = request_irq( gHDMI20RxHandler[i].top_irq, (irq_handler_t)gHDMI20RxHandler[i].irq_5V_handler, 0, "HDMI20_TOP", (void *)&gHDMI20RxHandler[i]);
			if( ret <0 ) { HDMI20_ERROR("Failed to request 5V interrupt[%d] for Port[%d]\n", ret, i); }
			else { HDMI20_INFO("Successfully requested IRQ[%d] for Port[%d] Top IRQ\n", gHDMI20RxHandler[i].top_irq, i);}

			/* Enable 5V IRQ */
			gHDMI20RxHandler[i].control_top_irq(1);

			/* HPD Down */
			__HDMI20_HAL_Rx_Set_EnableHPD(i, 0, 1, __L__);
		}

		/* Start HDMI Main thread(Checking video information on video transtion state) */
		gHDMI20Thread.isAlive = 1;
		gHDMI20Thread.pThread= kthread_create( (void *)__HDMI20_HAL_MainThread, 0, "hdmi20_rx_video_stable_checker");
		if(gHDMI20Thread.pThread){
			HDMI20_INFO("Initialing VIDEO Stable checker thread\n");
			wake_up_process(gHDMI20Thread.pThread);
		}else HDMI20_ERROR("Cannot initiate Video stablizor thread\n");

		gIsHDMI20KdrvInitialized = 1;

		ret = RET_OK;
	} while(0);

	return ret;

}

int HDMI20_HAL_IsTimingInfoEmpty(UINT8 port)
{
	int ret = RET_ERROR;
	int _cmpResult = 0;

	do{
		/* Step 1. Port defence code */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(gHDMI20RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		_cmpResult = memcmp((void *)&gHDMI20RxHandler[port].timing_info, (char[sizeof(struct hdmi_rx_ctrl_video)]){0}, sizeof(struct hdmi_rx_ctrl_video));

		if(_cmpResult == 0){
			/* If Empty return 1 */
			ret = 1;
		}
		else{
			/* If not Empty return 0 */
			ret = 0;
		}

	} while(0);

	return ret;
}

int HDMI20_HAL_UpdateTimingInfo(struct hdmi_rx_ctrl *ctx, int clear, int caller_id)
{
	int ret = RET_ERROR;
	struct hdmi_rx_ctrl_video v = {0};
	UINT32 hvtotal;
	UINT32 vactive;
	UINT32 vtotal;
	UINT32 hactive;
	UINT32 htotal;
	UINT32 hblank;
	UINT32 vblank;
	UINT32 hfront;
	UINT32 vfront;
	UINT32 hsync;
	UINT32 vsync;

	UINT32 hBlankHactive;
	UINT32 hFrontHsync;
	UINT32 vFrontVsync;
	UINT32 vBlankVactive;

	UINT32 divider;
	UINT32 data;

	/* Clear VideoCon detect on any timinginfo update operations*/
	gHDMI20RxHandler[ctx->device_id].videoConDetectCnt = 0;

	if(clear){
		HDMI20_PRINT("Port[%d] : Clear Video timing info, Caller_id[%d]\n", ctx->device_id, caller_id);
		memset((void *)&gHDMI20RxHandler[ctx->device_id].timing_info, 0, sizeof(struct hdmi_rx_ctrl_video));
		memset((void *)&gHDMI20RxHandler[ctx->device_id].sync_info, 0, sizeof(HDMI20_HAL_DBG_SYNC_INFO_T));

		HDMI20_ResetDataPacketBuffer(HDR, ctx->device_id);
		HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_MAXNUM, ctx->device_id);

		gHDMI20RxHandler[ctx->device_id].stablehdcp14time = 0;
		gHDMI20RxHandler[ctx->device_id].allm_recieve_time = 0;
		gHDMI20RxHandler[ctx->device_id].isAllmMode = 0;

		gHDMI20RxHandler[ctx->device_id].isHDCP14 = 0;
		
		gHDMI20RxHandler[ctx->device_id].ctrl.stable_cnt = 0;	// 2018/08/09 : Sometimes, stable cnt are not reseted to 0. need to add more lines for this
		
		gHDMI20RxHandler[ctx->device_id].real_vfreq = 0;

		gHDMI20RxHandler[ctx->device_id].isDolbyHDR = (int)HDMI_DOLBY_STATE_OFF;
		gHDMI20RxHandler[ctx->device_id].isFreeSyncMode = 0;

		HDMI20_HAL_ClearManualSyncSetting(ctx->device_id);

		if(gHDMI20RxDevControler[HDMI20__FORCE_DCM_8_BIT_ON_594].value >0){
			data = gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(0x0A8);
			data &= 0x00001000;

			if(data != 0x0){
				HDMI20_VIDEO("Port[%d] Notice : Founded Force DCM to 8bit mode, Reset to automatic\n",ctx->device_id);
				gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(0x0A8, gHDMI20RxDevControler[HDMI20__LINK_REG_0XA8_GCP_CTRL].value);
			}
		}

		ret = RET_OK;
	}
	else{
		ret = hdmi_rx_ctrl_get_video(ctx, &v, gHDMI20RxDevControler[HDMI20__VERBOSE_FOR_ABNORMAL_SYNC].value);

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 5959){
			HDMI20_VIDEO("Port[%d] Warning : Forced Update Video Timing Info\n", ctx->device_id);
			memcpy((void *)&gHDMI20RxHandler[ctx->device_id].timing_info, (void *)&v, sizeof(struct hdmi_rx_ctrl_video));
			ret = RET_OK;
		}
		else if((ret < 0) || (gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 5949) ) {
			HDMI20_PRINT("Port[%d] : Cannot update. Bad Video[%ux%u%c: %s, DCM %ub, VIC:%u]. TMDS Clk[%d] TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n", ctx->device_id,\
					v.hactive, v.vactive, v.interlaced? 'i' : 'p', v.dvi? "DVI" : "HDMI", v.deep_color_mode, v.video_mode, gHDMI20RxHandler[ctx->device_id].phy_tmds_clk,\
					gHDMI20RxHandler[ctx->device_id].phyTCSMin[0], gHDMI20RxHandler[ctx->device_id].phyTCSMin[1],gHDMI20RxHandler[ctx->device_id].phyTCSMin[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSMax[0],gHDMI20RxHandler[ctx->device_id].phyTCSMax[1],gHDMI20RxHandler[ctx->device_id].phyTCSMax[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSResult[0],gHDMI20RxHandler[ctx->device_id].phyTCSResult[1],gHDMI20RxHandler[ctx->device_id].phyTCSResult[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSError[0],gHDMI20RxHandler[ctx->device_id].phyTCSError[1],gHDMI20RxHandler[ctx->device_id].phyTCSError[2],\
					gHDMI20RxHandler[ctx->device_id].isScdcUD);
			memset((void *)&gHDMI20RxHandler[ctx->device_id].timing_info, 0, sizeof(struct hdmi_rx_ctrl_video));
			gHDMI20RxHandler[ctx->device_id].isTimingInvalid = 1;

			HDMI20_PHY_PowerControl_PLLPDB(ctx->device_id, 1, __L__);
			HDMI20_PHY_Reset_PLLPDB(ctx->device_id, 1, __L__);
			HDMI20_PHY_PowerControl_PLLPDB(ctx->device_id, 0, __L__);
			HDMI20_PHY_Reset_PLLPDB(ctx->device_id, 0, __L__);

			gHDMI20RxHandler[ctx->device_id].phy_rst_request = 1;
			
			if(gHDMI20RxHandler[ctx->device_id].gWasHDCP22Written > 0){
				HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, ctx->device_id);
				HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, ctx->device_id);
			}


			gHDMI20RxHandler[ctx->device_id].ctrl.stable_cnt = 0;

			ret = RET_ERROR;
		}
		else{
			HDMI20_PRINT("Port[%d] Notice : Update Timing. [%ux%u%c: %s, DCM %ub, VIC:%u] TMDS Clk[%d] TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n", ctx->device_id,\
					v.hactive, v.vactive, v.interlaced? 'i' : 'p', v.dvi? "DVI" : "HDMI", v.deep_color_mode, v.video_mode,\
					gHDMI20RxHandler[ctx->device_id].phy_tmds_clk,\
					gHDMI20RxHandler[ctx->device_id].phyTCSMin[0], gHDMI20RxHandler[ctx->device_id].phyTCSMin[1],gHDMI20RxHandler[ctx->device_id].phyTCSMin[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSMax[0],gHDMI20RxHandler[ctx->device_id].phyTCSMax[1],gHDMI20RxHandler[ctx->device_id].phyTCSMax[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSResult[0],gHDMI20RxHandler[ctx->device_id].phyTCSResult[1],gHDMI20RxHandler[ctx->device_id].phyTCSResult[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSError[0],gHDMI20RxHandler[ctx->device_id].phyTCSError[1],gHDMI20RxHandler[ctx->device_id].phyTCSError[2],\
					gHDMI20RxHandler[ctx->device_id].isScdcUD);

			/* 2017/03/27 : CEA mode for under specific V.active */
			if(gHDMI20RxHandler[ctx->device_id].real_tmds_clk <= gHDMI20RxDevControler[HDMI20__FORCE_CEA_TMDS_VALUE].value){
				HDMI20_PRINT("Port[%d] Notice : Found TMDS Lower then [%d]. Change to CEA mode.\n",\
						ctx->device_id, gHDMI20RxDevControler[HDMI20__FORCE_CEA_TMDS_VALUE].value);

				HDMI20_PRINT("Port[%d] Notice : Current [%s] Mode \n", ctx->device_id, __HDMI20_HAL_IsPVOMode(ctx->device_id)?"PVO":"CEA");
				
				if(__HDMI20_HAL_IsPVOMode(ctx->device_id) == RET_OK){
					__HDMI20_HAL_SetPVOMode(ctx->device_id, 0); //CEA Mode
				}
				else{
					HDMI20_PRINT("Port[%d] Notice : Will not perform CEA/PVO mode change since it is already CEA mode\n", ctx->device_id);
				}
			}
			else{
				if(gHDMI20RxDevControler[HDMI20__USE_PVO_MODE_FOR_LINK].value > 0){
					if(__HDMI20_HAL_IsPVOMode(ctx->device_id) != RET_OK){
						HDMI20_PRINT("Port[%d] : Notice : CEA/PVO Mode miss-match. Change Mode\n", ctx->device_id);
						__HDMI20_HAL_SetPVOMode(ctx->device_id, gHDMI20RxDevControler[HDMI20__USE_PVO_MODE_FOR_LINK].value); //PVO Mode
					}
				}
				else{
					if(__HDMI20_HAL_IsPVOMode(ctx->device_id) == RET_OK){
						HDMI20_PRINT("Port[%d] : Notice : CEA/PVO Mode miss-match. Change Mode\n", ctx->device_id);
						__HDMI20_HAL_SetPVOMode(ctx->device_id, gHDMI20RxDevControler[HDMI20__USE_PVO_MODE_FOR_LINK].value); //CEA Mode
					}
				}
			}

			if(gHDMI20RxDevControler[HDMI20__FORCE_DCM_8_BIT_ON_594].value >0){
				if(((gHDMI20RxHandler[ctx->device_id].real_tmds_clk >= 590000) && (v.hactive >= 2560) && (v.vactive >= 2000))\
						||(((gHDMI20RxHandler[ctx->device_id].real_tmds_clk >= 290000) && (v.hactive >= 3800) && (v.vactive >= 2000) && ( gHDMI20RxHandler[ctx->device_id].phyInitiatedMode == 0)))){
					/* MSPG 7800 422<->452 timing, 452 no video issue : added 297Hz 4K case */
					HDMI20_PRINT("Port[%d] Notice : Found over 290Mhz(3G)/590MHz(6G) with 4K. Force DCM to 8bit.\n",ctx->device_id);
					data = gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(0x0A8);
					data |= 0x00001000;
					gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(0x0A8, data);
				}
			}


			/* 2015/09/07 : For devices where they change resolution without any trace */
			HDMI20_HAL_ClearManualSyncSetting(ctx->device_id);

			gHDMI20RxHandler[ctx->device_id].isTimingInvalid = 0;
			gHDMI20RxHandler[ctx->device_id].real_vfreq = 0;

			/* Annotated due to inverse function call */
			HDMI20_HAL_UpdateDCMMode(ctx->device_id, 0, v.deep_color_mode);

			gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(0xFB8, 0x1F);
			hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[ctx->device_id].ctrl);
			__HDMI20_HAL_SetVideoColorDomain(ctx->device_id);

			/* Update Manual Sync*/
			if(gHDMI20RxDevControler[HDMI20__SET_MANUAL_SYNC_FOR_ALL_FHD].value >0) {
				hactive = gHDMI20RxHandler[ctx->device_id].top_read(0x210) & 0x0000FFFF;
				htotal  = (gHDMI20RxHandler[ctx->device_id].top_read(0x210) & 0xFFFF0000)>>16;
				vactive = gHDMI20RxHandler[ctx->device_id].top_read(0x20C) & 0x0000FFFF;
				vtotal  = (gHDMI20RxHandler[ctx->device_id].top_read(0x20C) & 0xFFFF0000)>>16;

				if(gHDMI20RxHandler[ctx->device_id].currentDCMMode== 0x5)		{ divider = 125; }
				else if(gHDMI20RxHandler[ctx->device_id].currentDCMMode== 0x6)	{ divider = 150; }
				else if(gHDMI20RxHandler[ctx->device_id].currentDCMMode== 0x7)	{ divider = 200; }
				else	{ divider =  100; }

				if(v.interlaced) {	vtotal = gHDMI20RxHandler[ctx->device_id].vtotalbuffer; }


				if(vtotal >= 600){
					if(vtotal%2 != 0){
						if(vtotal%5 != 0){
							if(vtotal%10 == 1) vactive -= 1;
							else if(vtotal%10 == 9) vactive += 1;
							else if(vtotal%8 == 1) vactive -= 1;
							else if(vtotal%8 == 7) vactive += 1;
							else if(vtotal%4 == 1) vtotal -= 1;
							else if(vtotal%4 == 3) vtotal += 1;
						}
					}
				}

				hactive = (hactive * 100)/divider;
				htotal = (htotal * 100)/divider;

				hblank = htotal - hactive;
				vblank = vtotal - vactive;

				if(hblank%2 != 0){
					if(hblank%10 == 1) hblank -= 1;
					else if(hblank%10 == 9) hblank += 1;
					else if(hblank%8 == 1) hblank -= 1;
					else if(hblank%8 == 7) hblank += 1;
					else if(hblank%4 == 1) hblank -= 1;
					else if(hblank%4 == 3) hblank += 1;
				}

				if(hactive%2 != 0){
					if(hactive%10 == 1) hactive -= 1;
					else if(hactive%10 == 9) hactive += 1;
					else if(hactive%8 == 1) hactive -= 1;
					else if(hactive%8 == 7) hactive += 1;
					else if(hactive%4 == 1) hactive -= 1;
					else if(hactive%4 == 3) hactive += 1;
				}
				if(htotal%2 != 0){
					if(htotal%10 == 1) htotal -= 1;
					else if(htotal%10 == 9) htotal += 1;
					else if(htotal%8 == 1) htotal -= 1;
					else if(htotal%8 == 7) htotal += 1;
					else if(htotal%4 == 1) htotal -= 1;
					else if(htotal%4 == 3) htotal += 1;
				}

				if(hblank){
					//hfront = (hblank * 30)/100;
					//hsync = (hblank * 15)/100;
					hfront = 2;
					hsync = 2;
				}
				else {
					hfront = 0;
					hsync = 0;
				}

				if(vblank){
					//vfront = (vblank * 30)/100;
					//vsync = (vblank * 15)/100;
					vfront = 2;
					vsync = 2;
				}
				else{
					vfront = 0;
					vsync = 0;
				}

				if((hactive == 0)||(htotal == 0)||(vactive == 0)||(vtotal == 0)||(vblank == 0)||(hblank == 0)){
					hBlankHactive = 0;
					hFrontHsync = 0;
					vFrontVsync = 0;
					vBlankVactive = 0;
					HDMI20_PRINT("Notice %d : Manual Sync zero. [%d][%d][%d][%d][%d][%d]\n", ctx->device_id,\
							hactive, htotal, vactive, vtotal, vblank, hblank);
				}
				else{
					hBlankHactive = hblank; hBlankHactive = hBlankHactive << 16; hBlankHactive |= hactive;
					hFrontHsync = hfront; hFrontHsync = hFrontHsync << 16; hFrontHsync |= hsync;
					vFrontVsync = vfront; vFrontVsync = vFrontVsync << 16; vFrontVsync |= vsync;
					vBlankVactive = vblank; vBlankVactive = vBlankVactive << 16; vBlankVactive |= vactive;

					HDMI20_PRINT("Manual Sync value ready.. hBlankHactive[0x%08x], hFrontHsync[0x%08x] vFrontVsync[0x%08x] vBlankVactive[0x%08x]\n", hBlankHactive, hFrontHsync, vFrontVsync, vBlankVactive);
				}

				gHDMI20RxHandler[ctx->device_id].ctrl.hBlankHactive = hBlankHactive;
				gHDMI20RxHandler[ctx->device_id].ctrl.hFrontHsync = hFrontHsync;
				gHDMI20RxHandler[ctx->device_id].ctrl.vFrontVsync = vFrontVsync;
				gHDMI20RxHandler[ctx->device_id].ctrl.vBlankVactive = vBlankVactive;
			}

			gHDMI20RxHandler[ctx->device_id].updateTimingTime = jiffies_to_msecs(jiffies);
		
			if(__HDMI20_HAL_IsHwInDVIState(ctx->device_id)){
				/* SW defence code for DVi */
				v.pixel_repetition = 0;
			}

			memcpy((void *)&gHDMI20RxHandler[ctx->device_id].timing_info, (void *)&v, sizeof(struct hdmi_rx_ctrl_video));
			
			hvtotal = (gHDMI20RxHandler[ctx->device_id].timing_info.vtotal * gHDMI20RxHandler[ctx->device_id].timing_info.htotal);

			if(hvtotal != 0){
				gHDMI20RxHandler[ctx->device_id].real_vfreq = ((gHDMI20RxHandler[ctx->device_id].real_pixel_clk * 1000) / hvtotal);
			}
			else{
				gHDMI20RxHandler[ctx->device_id].real_vfreq = 0;
			}

			ret = RET_OK;
		}
	}

	return ret;
}

static int __HDMI20_HAL_IsHwInDVIState(UINT8 port)
{
	int ret = RET_ERROR;

	UINT32 regData = 0;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		regData = gHDMI20RxHandler[port].ctrl.bsp_read(0x360);
		regData &= (0x10000000);

		if(regData) ret = 1;
		else ret = 0;

	}while(0);

	return ret;
}

static void __HDMI20_HAL_CheckVideoColorDomain(UINT8 port)
{
	UINT32 video_format = 0;
	UINT32 value_of_reg14 = 0;
	UINT32 value_of_reg18 = 0;
	UINT32 invalid = 0;

	#if 0
	if(video_format == 0){
		video_format = (UINT32)((gHDMI20RxHandler[port].dataPacket[AVI][5]&0x60)>>5);
	}
	#endif
	video_format = gHDMI20RxHandler[port].ctrl.bsp_read(0x3A4);
	video_format = (video_format & 0x60); video_format = video_format>>5;
	video_format = video_format & 0x3;

	if(__HDMI20_HAL_IsHwInDVIState(port)){
		video_format = 0;
	}
	if(gHDMI20RxHandler[port].isDolbyHDR == HDMI_DOLBY_LL_422_12B){
		video_format = 0;
	}

	value_of_reg14 = gHDMI20RxHandler[port].top_read(0x14);
	value_of_reg18 = gHDMI20RxHandler[port].top_read(0x18);
	value_of_reg18 &= 0x0000FFFF;

	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 659){
		HDMI20_DBG("DBG %d : Color Domain 0x14[0x%08x]/0x18[0x%08x]\n", port, value_of_reg14, value_of_reg18);
	}

	if(video_format == 0){ /* RGB 444*/
		if(value_of_reg14 != 0x10006) invalid++;
		if(value_of_reg18 != 0x0) invalid++;
	}
	if(video_format == 1){ /* YUV 422*/
		if(value_of_reg14 != 0x21) invalid++;
		if(value_of_reg18 != 0x1) invalid++;

	}
	else if(video_format == 2){ /*  YUV 444 */
		if(value_of_reg14 != 0x21) invalid++;
		if(value_of_reg18 != 0x0) invalid++;

	}
	else if(video_format == 3) { /* YUV 420 */
		if(value_of_reg14 != 0x06) invalid++;
		if(value_of_reg18 != 0x0) invalid++;
	}

	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1244){
		return;
	}

	if(invalid >0){
		HDMI20_WARN("Warning [%d] : Found wrong CSC setting for [%d] domain. Invalid[%d]\n", port, video_format, invalid);
		__HDMI20_HAL_SetVideoColorDomain(port);
	}
}

static void __HDMI20_HAL_SetVideoColorDomain(UINT8 port)
{
	UINT32 video_format = 0;

	video_format = gHDMI20RxHandler[port].ctrl.bsp_read(0x3A4);
	video_format = (video_format & 0x60); video_format = video_format>>5;
	video_format = video_format & 0x3;

	if(__HDMI20_HAL_IsHwInDVIState(port)){
		video_format = 0;
	}
	if(gHDMI20RxHandler[port].isDolbyHDR == HDMI_DOLBY_LL_422_12B){
		video_format = 0;
	}

	#if 0
	if(video_format == 0){
		video_format = (UINT32)((gHDMI20RxHandler[port].dataPacket[AVI][5]&0x60)>>5);
	}
	#endif

	if(video_format == 0){ /* RGB 444*/
		gHDMI20RxHandler[port].top_write(0x18, 0x0);
		gHDMI20RxHandler[port].top_write(0x14, 0x10006);
	}
	if(video_format == 1){ /* YUV 422*/
		gHDMI20RxHandler[port].top_write(0x18, 0x1);
		gHDMI20RxHandler[port].top_write(0x14, 0x21);
	}
	else if(video_format == 2){ /*  YUV 444 */
		gHDMI20RxHandler[port].top_write(0x18, 0x0);
		gHDMI20RxHandler[port].top_write(0x14, 0x21);
	}
	else if(video_format == 3) { /* YUV 420 */
		gHDMI20RxHandler[port].top_write(0x18, 0x0);
		gHDMI20RxHandler[port].top_write(0x14, 0x06);
	}
}


static int __HDMI20_HAL_Rx_UnInitialize(void)
{
	int ret = RET_OK;

	do{

	} while(0);

	return ret;

}

static void __HDMI20_HAL_TestPattern(UINT8 port, int isUD, int isOn)
{
	if(isOn){
		gHDMI20RxHandler[port].top_write(0x4, 0x6);
		if(isUD){
			gHDMI20RxHandler[port].top_write(0x0508, 0x08CA1130); //Vtotal = 2250, Htotal = 4400
			gHDMI20RxHandler[port].top_write(0x050C, 0x087C0886); //Vs_srt = 2172, Vs_end = 2182
			gHDMI20RxHandler[port].top_write(0x0510, 0x00040874); //Va_srt =    4, Va_end = 2164
			gHDMI20RxHandler[port].top_write(0x0514, 0x005800B0); //Hs_srt =   88, Hs_end =  176
			gHDMI20RxHandler[port].top_write(0x0518, 0x01D810D8); //Ha_srt =  472, Ha_end = 4312

		}
		else{
			gHDMI20RxHandler[port].top_write(0x0508, 0x04650898); // Vtotal = 1125 Htotal = 2200
			gHDMI20RxHandler[port].top_write(0x050C, 0x04400445); // VS SRT = 1088 VS END = 1093
			gHDMI20RxHandler[port].top_write(0x0510, 0x0004043C);// VA SRT =    4 VA END = 1084
			gHDMI20RxHandler[port].top_write(0x0514, 0x002C0058); // HS SRT =   44 HS END =   88
			gHDMI20RxHandler[port].top_write(0x0518, 0x00EC086C); // HA SRT =  236 HA END = 2156

		}
		gHDMI20RxHandler[port].top_write(0x0600, 0x00000011); // PATTERN EN
		gHDMI20RxHandler[port].top_write(0x0500, 0x00000020); // Sync gen Load Setting
		gHDMI20RxHandler[port].top_write(0x0500, 0x00000120); //
		gHDMI20RxHandler[port].top_write(0x0500, 0x00000080); //
	}
	else{
		gHDMI20RxHandler[port].top_write(0x4, 5);
		gHDMI20RxHandler[port].top_write(0x600, 0);
	}
}

static int __HDMI20_HAL_Rx_ListOfNotSupportingVideo(UINT8 port)
{
	int ret = RET_ERROR;

	do{
		/* No support on Pixel repition over 1 */
		if(gHDMI20RxHandler[port].timing_info.pixel_repetition >1){
			//HDMI20_VIDEO("ERROR %d : Does not support pixel repetition more than 1. PR[%d]\n", port, gHDMI20RxHandler[port].timing_info.pixel_repetition);
			break;
		}

		/* Invalid Format Check */
		if((gHDMI20RxHandler[port].timing_info.hactive < 320) || (gHDMI20RxHandler[port].timing_info.vactive < 240) )
		{
			HDMI20_VIDEO("ERROR %d : InValid Format for Active Size,  hActive[%d] vActive [%d]\n", port,\
					gHDMI20RxHandler[port].timing_info.hactive, gHDMI20RxHandler[port].timing_info.vactive);
			break;
		}

		/* Support 2D 1280x1024i@86  by 20120202
		 * Not support Master #333 - because MASTER timing issue */
		if (gHDMI20RxHandler[port].timing_info.hactive == 1280 && \
				gHDMI20RxHandler[port].timing_info.vactive == 512 &&\
				gHDMI20RxHandler[port].timing_info.interlaced == 0)
		{
			HDMI20_VIDEO("ERROR %d : not support 2D 1280x1024!@86 of Master #333\n", port);
			break;
		}

		//* Support 2D 1920x1080i@50 of EIA-861D  for any PC Card  by 20111010
		//* Not support Master #840 - because MASTER timing issue
		if (gHDMI20RxHandler[port].timing_info.htotal == 2304)// && gHDMI20RxHandler[port].timing_info.hActive == 1920 && gHDMI20RxHandler[port].timing_info.scanType == 1)
		{
			if (gHDMI20RxHandler[port].timing_info.vtotal == 1250)
			{
				HDMI20_VIDEO("NOTI [%d] : Support 2D 1920x1080!@50 of EIA-861D \n",port);

			}
			else
			{
				HDMI20_VIDEO("ERROR %d : not support 2D 1920x1080!@50 of EIA-861D Master #840\n", port);
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
static int __HDMI20_HAL_Set_HDMI_Factor(LX_HDMI20_SETTING_FACTOR_T *pData, int size)
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

		if( copy_from_user(&data, (void __user *)pData, sizeof(LX_HDMI20_SETTING_FACTOR_T))){
			HDMI20_ERROR("Cannot copy HDMI Factor data structure from user\n");
			break;
		}

		HDMI20_VIDEO("[%s] : Factor[%d], value[%d][%d][%d]\n", __F__, data.type, data.value1, data.value2, data.value3);
		
		ret = RET_OK;
		
		switch(data.type)
		{
			case LX_HDMI20_SETTING_HPD_LOW_DURATION :
				{
					gAdditionalHpdLowDuration = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_MODE :
				{
					gHDMI20RxDevControler[HDMI20__PHY_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH0 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_MANUAL_TCS_ADDVAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH1 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_MANUAL_TCS_ADDVAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH2 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_MANUAL_TCS_ADDVAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_TMDS_EQ_PERIOD :
				{
					gHDMI20RxDevControler[HDMI20__USE_PHY_TCS_PERIOD_SEL].value = data.value1;
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
						gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value = HDMI20_HAL_VIDEO_CHECK_CNT;
					}
					else if(data.value1 > 50){
						gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value += (temp / (HDMI20_HAL_INITIAL_THREAD_SLEEP_MS / 10));
					}
					else if(data.value1 < 50){
						if(gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value >= (temp / (HDMI20_HAL_INITIAL_THREAD_SLEEP_MS / 10))){
							gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value -= (temp / (HDMI20_HAL_INITIAL_THREAD_SLEEP_MS / 10));
						}
						else{
							gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value = 0;
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
						gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value = HDMI20_AUDIO_STABLE_CNT_INITIAL;
						gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value = (HDMI20_AUDIO_STABLE_CNT_INITIAL - 1);
					}
					else if(data.value1 > 50){
						gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value += (temp / (HDMI20_HAL_INITIAL_THREAD_SLEEP_MS / 10));
						gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value = gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value - 1;

					}
					else if(data.value1 < 50){
						if(gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value >= ((temp / (HDMI20_HAL_INITIAL_THREAD_SLEEP_MS / 10)) + 2)){
							gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value -= (temp / (HDMI20_HAL_INITIAL_THREAD_SLEEP_MS / 10));
							gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value = gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value - 1;
						}
						else{
							gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value = 2;
							gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value = 1;
						}
						
					}
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT0 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI20RxHandler[0].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI20RxHandler[0].gWasHDCP22FuncCalled > 0){
							gHDMI20RxHandler[0].gWasHDCP22Written = 1; 
						}
					} 
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT1 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI20RxHandler[1].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI20RxHandler[1].gWasHDCP22FuncCalled > 0){
							gHDMI20RxHandler[1].gWasHDCP22Written = 1; 
						}
					} 
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT2 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI20RxHandler[2].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI20RxHandler[2].gWasHDCP22FuncCalled > 0){
							gHDMI20RxHandler[2].gWasHDCP22Written = 1; 
						}
					} 
				}
				break;
			case LX_HDMI20_SETTING_DISABLE_HDCP22_PORT3 :
				{
					/* 2018/04/11 won.hur :  Dangerous : When Key is not written, this could force the driver to key written state. May malfunction. */
					if(data.value1) { gHDMI20RxHandler[3].gWasHDCP22Written = 0; }
					else { 
						if(gHDMI20RxHandler[3].gWasHDCP22FuncCalled > 0){
							gHDMI20RxHandler[3].gWasHDCP22Written = 1; 
						}
					}
				}
				break;
			case LX_HDMI20_SETTING_ON_TO_RXSENSE_TIME :
				{
					gHDMI20RxDevControler[HDMI20__PHY_PDB_ON_DELAY_TIME].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_RXSENSE_TO_HPD_TIME :
				{
					gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_MODE :
				{
					gHDMI20RxDevControler[HDMI20__PHY_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH0 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_MANUAL_TCS_ADDVAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH1 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_MANUAL_TCS_ADDVAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH2 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_MANUAL_TCS_ADDVAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_MODE :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P1_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH0 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH1 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH2 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P1_MANUAL_TCS_ADDVAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_MODE :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P2_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH0 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH1 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH2 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P2_MANUAL_TCS_ADDVAL_CH2].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_MODE :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P3_ENABLE_MANUAL_EQ].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH0 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH0].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH1 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH1].value = data.value1;
				}
				break;
			case LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH2 :
				{
					gHDMI20RxDevControler[HDMI20__PHY_P3_MANUAL_TCS_ADDVAL_CH2].value = data.value1;
				}
				break;
			default :
				ret = RET_ERROR;
				break;
		}

	} while(0);

	return ret;
}




/* IOCTL */
static int __HDMI20_HAL_Rx_Set_HDCP14_KSVList(UINT8 port, LX_HDMI20_HDCP14_RP_T *pData, int size)
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

		if(port >= HDMI20_NUM_OF_RX_PORTS){
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
			ret = hdmi_rx_ctrl_hdcp_ksv_list((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, (uint32_t *)&__data.ksvList, __data.count, __data.depth);
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
static int __HDMI20_HAL_DBG_GetHDMIMiscInfo(UINT8 port, LX_HDMI20_RX_HDMI_MISC_T *pData, int size)
{
	int ret = RET_ERROR;
	LX_HDMI20_RX_HDMI_MISC_T userdata;
	UINT32 tempData = 0;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_RX_HDMI_MISC_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_RX_HDMI_MISC_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI20_RX_HDMI_MISC_T));


		/* Step 2. Copy data */
		userdata.kdrvVer = HDMI20_KERNEL_DRIVER_VER;
		userdata.avMute = gHDMI20RxHandler[port].ctrl.isMute;
		userdata.phyLockTime = (gHDMI20RxHandler[port].locking_time * gHDMI20Thread.mSleep);
		
		if(__HDMI20_HAL_IsHwInDVIState(port) == 0){
			userdata.n_param = gHDMI20RxHandler[port].ctrl.n_param;
			userdata.cts_param = gHDMI20RxHandler[port].ctrl.cts_param;
		}

		/* SCDC Info */
		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0x860);
		tempData &= 0x000000FF;
		userdata.scdcInfo.sink_version = (UINT8)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0x820);
		tempData &= 0x000000FF;
		userdata.scdcInfo.source_version = (UINT8)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0x820);
		if((tempData & 0x00020000) != 0) { userdata.scdcInfo.bit_ratio = 1; }
		if((tempData & 0x00010000) != 0) { userdata.scdcInfo.scramble_enable = 1; }
		if((tempData & 0x01000000) != 0) { userdata.scdcInfo.scramble_status = 1; }

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0x824);
		if((tempData & 0x00000100) != 0) { userdata.scdcInfo.clock_detect = 1; }
		if((tempData & 0x00000200) != 0) { userdata.scdcInfo.ch_locked[0] = 1; }
		if((tempData & 0x00000400) != 0) { userdata.scdcInfo.ch_locked[1] = 1; }
		if((tempData & 0x00000800) != 0) { userdata.scdcInfo.ch_locked[2] = 1; }

		tempData &= 0x7FFF0000;
		tempData = tempData >> 16; tempData &= 0x0000FFFF;
		userdata.scdcInfo.ch_error_count[0] = (UINT16)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0x828);
		tempData &= 0x00007FFF;
		userdata.scdcInfo.ch_error_count[1] = (UINT16)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0x828);
		tempData &= 0x7FFF0000;
		tempData = tempData >> 16; tempData &= 0x0000FFFF;
		userdata.scdcInfo.ch_error_count[2] = (UINT16)tempData;

		/* HDCP1.4 Info */
		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xE0);
		tempData &= 0x003F0000; tempData = tempData >> 16; tempData &= 0x0000003F;
		userdata.hdcpInfo.status = (UINT8)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xE0);
		tempData &= 0x000000FF;
		userdata.hdcpInfo.Ri[0] = (UINT8)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xE0);
		tempData &= 0x0000FF00; tempData = tempData >> 8; 
		userdata.hdcpInfo.Ri[1] = (UINT8)tempData;

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xE4);
		tempData &= 0x000000FF;
		userdata.hdcpInfo.Aksv[0] = (UINT8)(tempData);

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xE8);
		userdata.hdcpInfo.Aksv[1] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.Aksv[2] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.Aksv[3] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.Aksv[4] = (UINT8)(tempData & 0x000000FF);

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xEC);
		userdata.hdcpInfo.An[0] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.An[1] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.An[2] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.An[3] = (UINT8)(tempData & 0x000000FF);

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xF0);
		userdata.hdcpInfo.An[4] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.An[5] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.An[6] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.An[7] = (UINT8)(tempData & 0x000000FF);

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xCC);
		tempData &= 0x000000FF;
		userdata.hdcpInfo.Bksv[0] = (UINT8)(tempData);

		tempData = gHDMI20RxHandler[port].ctrl.bsp_read(0xD0);
		userdata.hdcpInfo.Bksv[1] = (UINT8)((tempData & 0xFF000000)>>24);
		userdata.hdcpInfo.Bksv[2] = (UINT8)((tempData & 0x00FF0000)>>16);
		userdata.hdcpInfo.Bksv[3] = (UINT8)((tempData & 0x0000FF00)>>8);
		userdata.hdcpInfo.Bksv[4] = (UINT8)(tempData & 0x000000FF);

		userdata.hdcpInfo.Bcaps = 0x81;

		if(__HDMI20_HAL_IsHwInDVIState(port) == 0){
			userdata.hdcpInfo.Bstatus[1] = 0x10;
			userdata.hdcpInfo.Bstatus[0] = 0x00;
		}

		/* Step x. Copy to User */
		ret = copy_to_user((LX_HDMI20_RX_HDMI_MISC_T *)pData, &userdata, sizeof(LX_HDMI20_RX_HDMI_MISC_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for HDMI MISC data on Port[%d].\n", port);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}



/* IOCTL */
int HDMI20_HAL_Rx_Get_TimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	int i;
	LX_HDMI_TIMING_INFO_T userdata;
	LX_HDMI_VSI_3D_STRUCTURE_T	vsi3DData = LX_HDMI_VSI_3D_STRUCTURE_MAX;
	LX_HDMI_EXT_FORMAT_INFO_T	lg3DData = LX_HDMI_EXT_2D_FORMAT;
	int vfreq,hfreq;
	UINT32 data, data1, actual_vActive_of_3DFA;
	UINT32 vsyncTime = 0;
	UINT32 hsyncTime = 0;
	//int hvtotal = 0;
	UINT32 fix_offset;
	UINT32 vsiPacketLength = 0;
	UINT8 vsiPacketHeader[3];
	UINT32 vsiHWPacketHeader;
	//UINT32 ctop_hdmi_clk_div;
	const HDMI20_NON_VSI_3D_TIMING_T *pTbl;
	int device3DvideoWithoutVSI = 0;
	UINT32 phyInitiatedMode = 0;
	UINT32 currentTime = 0;

	do{
		/* Step 0. Memset */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_TIMING_INFO_T));

		/* Step 0. Check port validity */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		/* Step 0-1. Break if not connected */
		if(gHDMI20RxHandler[port].is5Vconnected == 0){
			ret = RET_OK;
			break;
		}

		/* Step 0-2. Break if HPD is down */
		if(HDMI20_HAL_IsHPD_Up(port) == 0){
			ret = RET_OK;
			break;
		}

		/* Step 1. Check given pointer */
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		/* Step 2. Check given data size */
		if(size != sizeof(LX_HDMI_TIMING_INFO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_TIMING_INFO_T), size);
			break;
		}

		/* Step 3-0. Block timing info on non video stable cnt */
		if(gHDMI20RxHandler[port].ctrl.stable_cnt <= gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value){
			ret = RET_OK;
			break;
		}

		if((gHDMI20RxHandler[port].scdc_change != 0) || (gHDMI20RxHandler[port].video_change != 0) ||\
				(gHDMI20RxHandler[port].tmds_change != 0) ){
			ret = RET_OK;
			break;	
		}

		if(gHDMI20RxHandler[port].phy_tmds_clk == 0){
			ret = RET_OK;
			break;
		}

		/* Step 3-1. Block operation on Phy Lock & non-steady state */
		if((gHDMI20RxHandler[port].timing_info.vactive == 0) ||(gHDMI20RxHandler[port].timing_info.hactive == 0))
		{
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
			break;
		}

		if((gHDMI20RxHandler[port].ctrl.isMute == 0) &&(HDMI20_HAL_Rx_IsLocalMuteOn(port)!=0)){
			if(gHDMI20RxHandler[port].isPhyLocked != 0){
				HDMI20_HAL_Rx_SetLocalVideoMute(port, 0, 1, __L__);
			}
		}


		/* Step 3-2. Block Not-supported videos */
		if( __HDMI20_HAL_Rx_ListOfNotSupportingVideo(port) < 0){
			//HDMI20_VIDEO("Error %d : Timing info to Zero due to Not supporting Timing spec\n", port);
			
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

			__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
			gHDMI20RxHandler[port].ctrl.stable_cnt = 0;

			ret = RET_OK;
			break;
		}


		/* Step 4. Calculate Frequency to fit LGE MW */
		if((gHDMI20RxHandler[port].real_pixel_clk == 0)||(gHDMI20RxHandler[port].timing_info.htotal == 0)){
			hfreq = 0;
		}
		else{
			hfreq = ((gHDMI20RxHandler[port].real_pixel_clk * 1000) / gHDMI20RxHandler[port].timing_info.htotal); 					///< Horizontal frequency(100 Hz unit)
		}



		/* Step 5. Check Range : pixel Clk, video sync data from HW is not accurate.. So i need to calucate the approperiate value for MW */
		if((gHDMI20RxHandler[port].real_pixel_clk == 0)||(gHDMI20RxHandler[port].timing_info.vtotal == 0)||(gHDMI20RxHandler[port].timing_info.htotal == 0)){
			vfreq = 0;
		}
		else{
			/* Check vTotal Range : Update this case statement through development process */
			if(gHDMI20RxHandler[port].timing_info.vtotal > 820){
				if(gHDMI20RxHandler[port].timing_info.vtotal > 1120){			
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 2250, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 2250;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 1500, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 1500;				
				    else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 1235, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 1235;//1235,1240
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 1125, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 1125;				
				}
				else{ 
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 1100, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 1100;//1099,1100				
				    else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 1090, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 1090;//1089,1090				
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 1000, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 1000;//996,1000			
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 925, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 925;//926			
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 825, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 825;//823
				}
			}
			else{
				if(gHDMI20RxHandler[port].timing_info.vtotal > 660){
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 805, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 805;//806,804,805
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 800, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 800;//798,802				
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 790, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 790;//791,790,795				
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 750, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 750;//755,748			
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 666, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 666;//666,667
				}
				else{
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 625, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 625;//625
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 530, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 530;//529
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 525, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 525;//526,524,525
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 505, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 505;//504
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 495, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 495;//494			
				}
			}
				//else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vtotal, 900, 2)) gHDMI20RxHandler[port].timing_info.vtotal = 900;//905,

			//hvtotal = (gHDMI20RxHandler[port].timing_info.vtotal * gHDMI20RxHandler[port].timing_info.htotal);
			//vfreq = (UINT16)((gHDMI20RxHandler[port].real_pixel_clk * 1000) / hvtotal);
			vfreq = gHDMI20RxHandler[port].real_vfreq;

			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1144){
				HDMI20_DBG("DBG %d : current Vfreq [%d]\n", port, vfreq);
			}

			/* SW WA */
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

			if(gHDMI20RxHandler[port].timing_info.video_format == 0x3){
				vfreq = vfreq << 1;
			}

			//check hActive Range : need to update the below case
			if(gHDMI20RxHandler[port].timing_info.hactive > 1360){
				if(gHDMI20RxHandler[port].timing_info.hactive > 1900){
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 4096, 5)) gHDMI20RxHandler[port].timing_info.hactive= 4096;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 3840, 5)) gHDMI20RxHandler[port].timing_info.hactive= 3840;			
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 1920, 5)) gHDMI20RxHandler[port].timing_info.hactive= 1920;
				}
				else{							
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 1440, 2)) gHDMI20RxHandler[port].timing_info.hactive= 1440;			
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 1366, 2)) gHDMI20RxHandler[port].timing_info.hactive= 1366;
				}
			}
			else{
				if(gHDMI20RxHandler[port].timing_info.hactive > 1020){
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 1280, 2)) gHDMI20RxHandler[port].timing_info.hactive= 1280;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 1024, 2)) gHDMI20RxHandler[port].timing_info.hactive= 1024;
				}
				else{					
				 	if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 720, 2)) gHDMI20RxHandler[port].timing_info.hactive= 720;
				 	else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.hactive, 640, 2)) gHDMI20RxHandler[port].timing_info.hactive= 640;
				}
			}	
		    if(gHDMI20RxHandler[port].timing_info.vactive > 700){	
				if(gHDMI20RxHandler[port].timing_info.vactive > 1000){
					if(gHDMI20RxHandler[port].timing_info.vactive == 1201) gHDMI20RxHandler[port].timing_info.vactive = 1201;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 2160, 5)) gHDMI20RxHandler[port].timing_info.vactive = 2160;						
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 1200, 2)) gHDMI20RxHandler[port].timing_info.vactive = 1200; 
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 1080, 2)) gHDMI20RxHandler[port].timing_info.vactive = 1080;			
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 1050, 2)) gHDMI20RxHandler[port].timing_info.vactive = 1050; 
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 1035, 2)) gHDMI20RxHandler[port].timing_info.vactive = 1035;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 1024, 2)) gHDMI20RxHandler[port].timing_info.vactive = 1024; 
					
				}
				else{		
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 960, 2)) gHDMI20RxHandler[port].timing_info.vactive = 960;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 900, 2)) gHDMI20RxHandler[port].timing_info.vactive = 900;				
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 870, 2)) gHDMI20RxHandler[port].timing_info.vactive = 870;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 864, 2)) gHDMI20RxHandler[port].timing_info.vactive = 864;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 800, 2)) gHDMI20RxHandler[port].timing_info.vactive = 800;				
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 768, 2)) gHDMI20RxHandler[port].timing_info.vactive= 768;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 720, 2)) gHDMI20RxHandler[port].timing_info.vactive = 720;	
		    	}
		    }
			else{
				if(gHDMI20RxHandler[port].timing_info.vactive > 490){					
				 	if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 624, 2)) gHDMI20RxHandler[port].timing_info.vactive = 624;
				 	else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 600, 2)) gHDMI20RxHandler[port].timing_info.vactive = 600;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 584, 2)) gHDMI20RxHandler[port].timing_info.vactive = 584;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 576, 2)) gHDMI20RxHandler[port].timing_info.vactive = 576;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 496, 2)) gHDMI20RxHandler[port].timing_info.vactive = 496;
				}
				else{
					if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 480, 2)) gHDMI20RxHandler[port].timing_info.vactive = 480;
			    	else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 483, 2)) gHDMI20RxHandler[port].timing_info.vactive = 483;					
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 400, 2)) gHDMI20RxHandler[port].timing_info.vactive = 400;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 350, 2)) gHDMI20RxHandler[port].timing_info.vactive = 350;
			   		else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 288, 2)) gHDMI20RxHandler[port].timing_info.vactive = 288;
					else if(u32CHK_RANGE(gHDMI20RxHandler[port].timing_info.vactive, 240, 2)) gHDMI20RxHandler[port].timing_info.vactive = 240;
		    	}
			}
		}

		/* Step 5-1. Convert Vfreq to a scale that the MW & DE FW wants(Multiply by 10) */
		vfreq = vfreq * 10;


		/* Step 6. Update VSI info to Timing Info operation..
		 * Weird that VSI information is sent through this path...*/
		/* Step 6-1. Check VSI info frame version */
		
		if(gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value >0){
			vsiHWPacketHeader = gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_CTRL_VSI_ST0);
			
			vsiPacketHeader[0] = (UINT8)(vsiHWPacketHeader & 0x000000FF);
			vsiPacketHeader[1] = (UINT8)((vsiHWPacketHeader & 0x0000FF00) >> 8);
			vsiPacketHeader[2] = (UINT8)((vsiHWPacketHeader & 0x00FF0000) >> 16);
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 191){
			HDMI20_DBG(" DBG %d : VSI Mode[%s] -> Header[0x%x][0x%x][0x%x]\n", port, gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value?"REG":"FIFO", vsiPacketHeader[0], vsiPacketHeader[1], vsiPacketHeader[2]);
		}

		/* VRR releated Detection */
		if(gHDMI20RxDevControler[HDMI20__LINK_AMD_FREESYNC_MODE].value == 0) {
			userdata.isFreeSyncMode = 0;
		}
		else if(gHDMI20RxDevControler[HDMI20__LINK_AMD_FREESYNC_MODE].value == 2){
			userdata.isFreeSyncMode = 1;
		}
		else{
			userdata.isFreeSyncMode = gHDMI20RxHandler[port].isFreeSyncMode;
		}

		/* ALLM Mode */
		if(gHDMI20RxHandler[port].allm_recieve_time > 0) {
			currentTime = jiffies_to_msecs(jiffies);
			if(currentTime - gHDMI20RxHandler[port].allm_recieve_time <= gHDMI20RxDevControler[HDMI20__LINK_ALLM_TIMEOUT].value){
				userdata.isAllmMode = gHDMI20RxHandler[port].isAllmMode;
			}
			else
			{
				HDMI20_DBG("DBG %d : ALLM TIME OUT Stamp[%d]/Now[%d]\n", port,  gHDMI20RxHandler[port].allm_recieve_time, currentTime);
				userdata.isAllmMode = 0;
				gHDMI20RxHandler[port].allm_recieve_time = 0;
			}
		}
		else {
			userdata.isAllmMode = 0;
		}

		/* Dolby HDR detection */
		if((gHDMI20RxHandler[port].dataPacket[DOLBYVSI][5]== 0x46)\
				&& (gHDMI20RxHandler[port].dataPacket[DOLBYVSI][6] == 0xD0)\
				&& (gHDMI20RxHandler[port].dataPacket[DOLBYVSI][7] == 0x00)){

			int iDolbyOnIndication = 0;
			if(gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value >0){
				iDolbyOnIndication = gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_CTRL_VSI_PAYLOAD0);//VSI Payload 0 register
				iDolbyOnIndication &= 0x3;
			}
			else{
				vsiPacketLength  = gHDMI20RxHandler[port].dataPacket[DOLBYVSI][2];
				iDolbyOnIndication = gHDMI20RxHandler[port].dataPacket[DOLBYVSI][8];
			}

			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 191){
				HDMI20_DBG(" DBG %d : VSI Mode[%s] -> Legnth[%d]\n", port, gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value?"REG":"FIFO", vsiPacketLength);
			}

			if(iDolbyOnIndication & 0x2) {
				/*check if LL mode or not. if PB4 lsb is 1 it is LL mode VSIF*/
				if(iDolbyOnIndication & 0x1) {
					userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_LL_422_12B;
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
						HDMI20_DBG("Dolby LL New VSI\n");
					}
				}
				else{/*Standard Dolby with New VSI*/
					userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_STD_NEWVSI;
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
						HDMI20_DBG("Dolby Standard New VSI\n");
					}
				}

			}
			else{
				/* This is Not Dolby */
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
					HDMI20_DBG("DBG %d : Dolby VSI verification. Dolby OFF indicated.\n", port);
				}
			}
		}

		if((userdata.isDolbyHDR <= HDMI_DOLBY_STD_OLDVSI) \
				&&( gHDMI20RxHandler[port].dataPacket[H14VSI][5] == 0x03) &&\
				( gHDMI20RxHandler[port].dataPacket[H14VSI][6] == 0x0C) &&\
				( gHDMI20RxHandler[port].dataPacket[H14VSI][7] == 0x00)) {
			/* Update VSI based on Field 8 */
			if((gHDMI20RxHandler[port].dataPacket[H14VSI][8] & 0xE0) == 0x40){
				vsi3DData = (0x0F & ((gHDMI20RxHandler[port].dataPacket[H14VSI][9] & 0xF0) >> 4));
			}
			/* Is Dolby HDR ? */
			/* PB4[7:5] == 0x0 or 0x1?? */
			else if(((gHDMI20RxHandler[port].dataPacket[H14VSI][8] & 0xE0) == 0x20)||((gHDMI20RxHandler[port].dataPacket[H14VSI][8] & 0xE0) == 0x00)){
				/* Legnth == 0x18? */
				if(gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value >0){
					vsiPacketLength  = gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_CTRL_VSI_ST1);
					vsiPacketLength &= 0x0000001F;
				}
				else{
					vsiPacketLength  = gHDMI20RxHandler[port].dataPacket[H14VSI][2];
				}
				
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 191){
					HDMI20_DBG(" DBG %d : VSI Mode[%s] -> Legnth[%d]\n", port, gHDMI20RxDevControler[HDMI20__ENABLE_VSI_HW_REG_MODE].value?"REG":"FIFO", vsiPacketLength);
				}

				if(vsiPacketLength  == 0x18){
					/* PB6 == 0x0 ? */
					if(memcmp((void *)&gHDMI20RxHandler[port].dataPacket[H14VSI][10], (void *)&gZero19bytes[0], 19) == 0){
						/* AVI RGB ?  && Q1-Q0 == FULL Range */
						if(((gHDMI20RxHandler[port].dataPacket[AVI][5]&0x60)>>5) == 0x0){
							if((gHDMI20RxHandler[port].dataPacket[AVI][7] & 0x0C) == 0x08){
								userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_STD_OLDVSI;
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
									HDMI20_DBG("Dolby Standard Old VSI\n");
								}
							
								if((gHDMI20RxHandler[port].isDolbyHDR == (int)HDMI_DOLBY_STATE_OFF)&&(gHDMI20RxDevControler[HDMI20__FORCE_DOLBY_DETECT_ON].value != 0)&&(gHDMI20RxDevControler[HDMI20__FORCE_DOLBY_DETECT_ON].value != 2)){
									HDMI20_PRINT("Notice %d : Detected Dolby VSI. Pattern ON!\n", port);
									HDMI20_HAL_Rx_SetLocalVideoMute(port, 1, 1, __L__);
								}
								else{
									/* Add code incase of Mute off */	
								}
							}
							else{
								/* This is Not Dolby */
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
									HDMI20_DBG("DBG %d : Dolby VSI verification. Not Full Quan Range!\n", port);
								}
							}
						}
						else{
							/* This is Not Dolby */
							if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
								HDMI20_DBG("DBG %d : Dolby VSI verification. Not RGB AVI!!!\n", port);
							}
						}
					}
					else{
						/* This is Not Dolby */
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
							HDMI20_DBG("DBG %d : Dolby VSI verification. PB06~PB24 are not all zeros!\n", port);
						}
					}
				}
				else{
					/* This is Not Dolby */
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
						HDMI20_DBG("DBG %d : Dolby VSI verification. VSI length error for dolby\n", port);
					}
				}
			} // End of DOLBY Detection */
			else{
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1207){
					HDMI20_DBG("DBG %d : Dolby VSI verification. VSI 4K part non-spec\n", port);
				}
			}
		}


		if(gHDMI20RxDevControler[HDMI20__FORCE_DOLBY_DETECT_ON].value == 0){
			userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_STATE_OFF;
		}
		else if(gHDMI20RxDevControler[HDMI20__FORCE_DOLBY_DETECT_ON].value == 2){
			userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_STD_OLDVSI;
		}
		else if(gHDMI20RxDevControler[HDMI20__FORCE_DOLBY_DETECT_ON].value == 3){
			userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_STD_NEWVSI;
		}
		else if(gHDMI20RxDevControler[HDMI20__FORCE_DOLBY_DETECT_ON].value == 4){
			userdata.isDolbyHDR = (UINT8)HDMI_DOLBY_LL_422_12B;
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 1244) {
			if(userdata.isDolbyHDR == (UINT8)HDMI_DOLBY_LL_422_12B)
				gHDMI20RxHandler[port].top_write(HDMI20_TOP_CSC_BYPASS_ADDR,0x1);//CSC bypass only for LL mode
			else
				gHDMI20RxHandler[port].top_write(HDMI20_TOP_CSC_BYPASS_ADDR,0x0);
		}

		/* Keep History of Dolby HDR */
		gHDMI20RxHandler[port].isDolbyHDR = userdata.isDolbyHDR;

		/* Defence Code. Block operation on LINK TOP output zero sync */
		
		vsyncTime = gHDMI20RxHandler[port].ctrl.bsp_read(0x15c); vsyncTime &= 0x0000FFFF;
		hsyncTime = gHDMI20RxHandler[port].ctrl.bsp_read(0x148); hsyncTime &= 0x0000FFFF;
		if(vsi3DData == LX_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE){
			if((vsyncTime == 0) || (hsyncTime == 0) || (gHDMI20RxHandler[port].real_pixel_clk == 0)\
					||(gHDMI20RxHandler[port].timing_info.voffset == 0)){

				HDMI20_VIDEO("Error %d : Timing info cannot perform as to prevent zero division\n", port);
				HDMI20_VIDEO(" Value : VS[0x%x] HS[0x%x] PC[0x%x] VO[0x%x]\n", vsyncTime, hsyncTime, gHDMI20RxHandler[port].real_pixel_clk, gHDMI20RxHandler[port].timing_info.voffset);

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
				break;
			}
		}

		/* Decide lge3DData with vsi3DData */
		switch(vsi3DData)
		{
			case LX_HDMI_VSI_3D_STRUCTURE_FRAME_PACKING:
				lg3DData = LX_HDMI_EXT_3D_FRAMEPACK;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE:
				lg3DData = LX_HDMI_EXT_3D_FIELD_ALTERNATIVE;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_LINE_ALTERNATIVE:
				lg3DData = LX_HDMI_EXT_3D_LINE_ALTERNATIVE;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_FULL:
				lg3DData = LX_HDMI_EXT_3D_SBSFULL;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM:
				lg3DData = LX_HDMI_EXT_3D_TNB;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_HALF:
				lg3DData = LX_HDMI_EXT_3D_SBS;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_L_DEPTH:
				lg3DData = LX_HDMI_EXT_3D_L_DEPTH;
				break;
			case LX_HDMI_VSI_3D_STRUCTURE_L_DEPTH_GRAPHICS:
				lg3DData = 	LX_HDMI_EXT_3D_L_GRAPHICS;
				break;
			default :
				if((gHDMI20RxHandler[port].dataPacket[VSI][8] & 0xF0) == 0x20){
					lg3DData = LX_HDMI_EXT_4K_2K;
				}
				else{
					lg3DData = LX_HDMI_EXT_2D_FORMAT;
				}
				break;
		}

		/* Step 7. Insert Timing Info to data structure*/
		//userdata.hFreq = (UINT16)hfreq;
		userdata.hFreq = 0;
		userdata.vFreq = (UINT16)vfreq; 					///< Veritical frequency(1/10 Hz unit)
		userdata.hTotal = (UINT16)gHDMI20RxHandler[port].timing_info.htotal; 			///< Horizontal total pixels
		userdata.vTotal = (UINT16)gHDMI20RxHandler[port].timing_info.vtotal; 			///< Vertical total lines
		userdata.hStart = (UINT16)gHDMI20RxHandler[port].timing_info.hoffset; 		///< Horizontal start pixel
		userdata.vStart = (UINT16)gHDMI20RxHandler[port].timing_info.voffset;			///< Vertical start lines
		userdata.hActive = (UINT16)gHDMI20RxHandler[port].timing_info.hactive;		///< Horizontal active pixel
		userdata.vActive = (UINT16)gHDMI20RxHandler[port].timing_info.vactive; 		///< Vertical active lines

		if(gHDMI20RxHandler[port].isFreeSyncMode > 0){
			userdata.vFreqMin = gHDMI20RxHandler[port].vfreq_min;
			userdata.vFreqMax = gHDMI20RxHandler[port].vfreq_max;
		}
		else{
			userdata.vFreqMin = userdata.vFreq;
			userdata.vFreqMax = userdata.vFreq;
		}

		if((UINT16)gHDMI20RxHandler[port].timing_info.interlaced){
			userdata.scanType = 0;
		}
		else{
			userdata.scanType = 1;
		}

		//userdata.HdmiLock;				///< Sampling phase
		/* Update extInfo*/
		userdata.extInfo = lg3DData;

		/* Do not know what "STATE" does... */
		userdata.state = 0;

		/* Step 8. Check 3D video without VSI information */
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3401){
			HDMI20_DBG("DBG %d : switch(%d)/pixel_repetition(%d)\n", port, lg3DData, gHDMI20RxHandler[port].timing_info.pixel_repetition);
		}

		if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value == 0){
			if(lg3DData == LX_HDMI_EXT_2D_FORMAT)
			{
				pTbl = &TBL_EXT_INFO[0];
				for (i = 0; i < TBL_NUM(TBL_EXT_INFO) ; i++, pTbl++)
				{
					if ((userdata.hActive == pTbl->hAct_info) && (userdata.vActive == pTbl->vAct_info) && (userdata.scanType== pTbl->scan_info) )
					{
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3401){
							HDMI20_DBG("DBG %d : 3D video without VSI info [%d]x[%d] [%d] => [%d]x[%d] [%d][%d]\n",\
									i, userdata.hActive, userdata.vActive, userdata.scanType, pTbl->hAct_info, pTbl->vAct_buf,\
									pTbl->scan_buf, pTbl->extInfo_buf);
						}

						userdata.hActive 		= pTbl->hAct_buf;
						userdata.vActive 		= pTbl->vAct_buf;
						userdata.scanType	= pTbl->scan_buf;
						userdata.extInfo		= pTbl->extInfo_buf;

						lg3DData = userdata.extInfo;
						device3DvideoWithoutVSI = 1;
						break;
					}
				}

				/* Step 8-1. If 3D without VSI condition */
				if(device3DvideoWithoutVSI >0){
					if(isInternalCall > 0){
						memcpy((LX_HDMI_TIMING_INFO_T *)pData, &userdata, sizeof(LX_HDMI_TIMING_INFO_T));
						ret = RET_OK;
					}
					else{
						ret = copy_to_user((LX_HDMI_TIMING_INFO_T *)pData, &userdata, sizeof(LX_HDMI_TIMING_INFO_T));
						if(ret) {
							HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "TIMING" ,port);
							break;
						}
					}
				}
			} 
		}



		if((lg3DData == LX_HDMI_EXT_4K_2K)||(lg3DData == LX_HDMI_EXT_2D_FORMAT)){
			/* SW WA for 3G 4K video DisplayEnable signal bug */
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3840){
				HDMI20_SWWA(" SW WA DBG :phy[%d]  0x400[0x%08x] %dx%d@%d\n", gHDMI20RxHandler[port].phyInitiatedMode, gHDMI20RxHandler[port].ctrl.bsp_read(0x400), userdata.hActive, userdata.vActive, userdata.vFreq);
			}
		
			phyInitiatedMode = HDMI20_HAL_IsSCDCvalueUD(port);

			if((userdata.vActive >= 2160) &&(userdata.hActive >=3840)){
				if((phyInitiatedMode > 0)&&(gHDMI20RxHandler[port].timing_info.video_format == 0x3)){
					// Do not SW WA for U+ 4K 60 4:2:0
					if((userdata.vFreq == 500)||(userdata.vFreq == 600)){
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 454) HDMI20_DBG(" DBG %d : 50Hz or 60Hz detected [%d]. HTotal[%d]\n", port, userdata.vFreq, userdata.hTotal);

						if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 5280)){
							userdata.vFreq = 500;	
						}
						else if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 4400)){
							userdata.vFreq = 600;	
						}

						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 454) HDMI20_DBG(" DBG %d : Result vfreq[%d] / Htotal[%d]\n", port, userdata.vFreq, userdata.hTotal);
					}
				}
				else{ 
					if(gHDMI20RxDevControler[HDMI20__ADJUST_DETECTED_4K_SYNC_WITH_HTOTAL].value > 0){
						if((userdata.vFreq == 240)||(userdata.vFreq == 250)){
							if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 454) HDMI20_DBG(" DBG %d : 24Hz or 25Hz detected on 4K manual sync [%d]. HTotal[%d]\n", port, userdata.vFreq, userdata.hTotal);

							if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 5280)){
								userdata.vFreq = 250;	
							}
							else if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 5500)){
								userdata.vFreq = 240;	
							}
							else if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 4400)){
								userdata.vFreq = 300;	
							}

							if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 454) HDMI20_DBG(" DBG %d : Result vfreq[%d] / Htotal[%d]\n", port, userdata.vFreq, userdata.hTotal);
						}
						else if((userdata.vFreq == 500)||(userdata.vFreq == 600)||(userdata.vFreq == 480)){
							if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 454) HDMI20_DBG(" DBG %d : 50Hz or 60Hz detected [%d]. HTotal[%d]\n", port, userdata.vFreq, userdata.hTotal);

							if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 5280)){
								userdata.vFreq = 500;	
							}
							else if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 5500)){
								userdata.vFreq = 480;	
							}
							else if(gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_HTOTAL_DETECTING_4K_SYNC].value >= abs(userdata.hTotal - 4400)){
								userdata.vFreq = 600;	
							}

							if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 454) HDMI20_DBG(" DBG %d : Result vfreq[%d] / Htotal[%d]\n", port, userdata.vFreq, userdata.hTotal);
						}
					}

					if((HDMI20_HAL_IsManualSyncSet(port) == 0)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)&&(gHDMI20RxHandler[port].ctrl.isMute == 0)&&(gHDMI20RxDevControler[HDMI20__USE_MANUAL_SYNC_FOR_4K].value > 0)){


						for(i=0;i<HDMI20_MANUAL_2D_4K_SYNC_PARAM_MAXNUM;i++){
							if((userdata.vActive == g2DManualSyncLUT[i].vactive)&&(userdata.hActive == g2DManualSyncLUT[i].hactive)\
									&&(userdata.vFreq == g2DManualSyncLUT[i].vfreq)&&(phyInitiatedMode == g2DManualSyncLUT[i].phyInitiatedMode)){
								HDMI20_VIDEO(" Notice %d : Software Workaround for 4K signal\n", port);
								HDMI20_VIDEO(" Notice %d : SW WA for 4K signal %dx%d@%d 3G/6G=%d. Color[0x%x]\n", port, userdata.hActive, userdata.vActive, userdata.vFreq, g2DManualSyncLUT[i].phyInitiatedMode\
										, gHDMI20RxHandler[port].timing_info.video_format);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x408, g2DManualSyncLUT[i].hBlankHactive);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, g2DManualSyncLUT[i].hFrontHsync);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x414, g2DManualSyncLUT[i].vFrontVsync);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x410, g2DManualSyncLUT[i].vBlankVactive);
								//gHDMI20RxHandler[port].isManualSyncMode = 2;

								gHDMI20RxHandler[port].manualSyncVICHist = gHDMI20RxHandler[port].timing_info.video_mode;

								data = 	gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
								data |= 0x0000000F;
								gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);

								gHDMI20RxHandler[port].manualSync4KVfreqHist = userdata.vFreq;
								gHDMI20RxHandler[port].manualSync4KHoriHist = userdata.hActive;

								HDMI20_HAL_Rx_SetLocalVideoMute(port, 0, 0, __L__);
								__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);

								break;
							}
							else if(i == (HDMI20_MANUAL_2D_4K_SYNC_PARAM_MAXNUM -1)){
								if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 6555) HDMI20_DBG(" DBG %d : Could not find table for 4K %dx%d@%d 3G/6G=%d\n", port,userdata.hActive,  userdata.vActive, userdata.vFreq, phyInitiatedMode);
							}
						}
					}
					else if((HDMI20_HAL_IsManualSyncSet(port) > 0)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)&&(gHDMI20RxHandler[port].ctrl.isMute == 0)&&(gHDMI20RxDevControler[HDMI20__USE_MANUAL_SYNC_FOR_4K].value > 0)){
						if(gHDMI20RxHandler[port].manualSync4KVfreqHist != userdata.vFreq){
							HDMI20_WARN("Warning %d : Detected wrong Manual Sync vFreq for 4K. Previous[%d]->Detected[%d]\n", port, gHDMI20RxHandler[port].manualSync4KVfreqHist, userdata.vFreq);
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
						else if(gHDMI20RxHandler[port].manualSync4KHoriHist != userdata.hActive){
							HDMI20_WARN("Warning %d : Detected wrong Manual Sync hActive for 4K. Previous[%d]->Detected[%d]\n", port, gHDMI20RxHandler[port].manualSync4KHoriHist, userdata.vFreq);
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
						else if((HDMI20_HAL_IsManualSyncSet(port) != 0)&&(gHDMI20RxHandler[port].timing_info.video_mode != gHDMI20RxHandler[port].manualSyncVICHist )){
							HDMI20_WARN("Warning %d : Detected wrong Manual Sync. VIC Current[%d]!=Hist[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, gHDMI20RxHandler[port].manualSyncVICHist);
							HDMI20_HAL_ClearManualSyncSetting(port);
						}

					}
				}
			}
		}
		else
		{
			/* Step 9. Need to modifiy Video sync params for MW, because some values must be divided by 2 for 3D videos and pixel Repetition*/
			switch(lg3DData)
			{
				case LX_HDMI_EXT_3D_FRAMEPACK:
					/* From Old issues from HDMI1.4
					 * Russia  STB Issue :VSI Info is 3D F/P and Source is 2D*/
					if ( ((userdata.hActive == 640) && (userdata.vActive == 480)) \
							|| ((userdata.hActive == 720) && (userdata.vActive == 480)) \
							|| ((userdata.hActive == 720) && (userdata.vActive == 576)) \
							|| ((userdata.hActive == 1280) && (userdata.vActive == 720)) \
							|| ((userdata.hActive == 1920) && (userdata.vActive == 1080)) )
					{
						userdata.extInfo = LX_HDMI_EXT_2D_FORMAT;
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 4224) HDMI20_DBG("DBG %d : 3D VSI info is F/P, but Timing Info is 2D format for Russia STB Issue \n",  port);
					}
					else if ( (userdata.vActive == 2228) ||(userdata.vActive == 1028) )		//1080i & 480i
					{

						if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
							userdata.scanType = 0;
						}
						else{
							/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
							userdata.scanType = 0;
							userdata.vActive = (userdata.vActive - 68) >> 1;	//68 : 23+22+23
						}
					}
					else if (userdata.vActive == 1226)		//576i
					{
						if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
							userdata.scanType = 0;
						}
						else{
							/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
							userdata.scanType = 0;
							userdata.vActive = (userdata.vActive - 74) >> 1;	//74 : 25+24+25
						}
					}
					else if (userdata.vActive == 1103)		// interace
					{
						/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
						userdata.scanType = 0;
						userdata.vActive = userdata.vActive - 23;
					}
					else			//progressive
					{
						if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
							/* Do not change value*/
						}
						else{
							/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
							userdata.vActive = (userdata.vActive - userdata.vTotal + userdata.vActive) >> 1;
						}
					}
					break;
				case LX_HDMI_EXT_3D_FIELD_ALTERNATIVE:
					/* To support Master Device.. Old methods came from HDMI1.4 the famous M.S.H */
					userdata.scanType = 0;

					if (userdata.vActive == 1103)		fix_offset = 23; //1080! - 22.5
					else if (userdata.vActive == 601) 	fix_offset = 25; //576! - 24.5
					else if (userdata.vActive == 503)	fix_offset = 23; //480! - 22.5
					else 								fix_offset = 0;
					actual_vActive_of_3DFA = userdata.vActive;
					userdata.vActive = userdata.vActive - fix_offset;
					userdata.vFreq = userdata.vFreq >> 1;

					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1247){
						HDMI20_DBG(" DBG %d : IsManSet[%d] / EnableMSync[%d] / isMute[%d] / v[%d] / h[%d] / vf[%d] / pI[%d]\n",\
								port, HDMI20_HAL_IsManualSyncSet(port), gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value, \
								gHDMI20RxHandler[port].ctrl.isMute, userdata.vActive, userdata.hActive, userdata.vFreq, phyInitiatedMode);
					}

					/* SW Workaround for LINK OUTPUT sync manual mode */
					if(	(HDMI20_HAL_IsManualSyncSet(port) == 0)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0) &&(gHDMI20RxHandler[port].ctrl.isMute == 0)&&(gHDMI20RxDevControler[HDMI20__USE_MANUAL_SYNC_FOR_FA].value > 0)){
						HDMI20_SWWA(" DBG %d : Software Workaround for 3D FA signal\n", port);
						
						gHDMI20RxHandler[port].isManualSyncMode = 2;

						gHDMI20RxHandler[port].ctrl.bsp_write(0x17c, 0x00000004);

						for(i=0;i<HDMI20_MANUAL_3D_SYNC_PARAM_FA_MAXNUM;i++){
							if((userdata.vActive == g3D_FA_ManualSyncLUT[i].vactive)&&(userdata.hActive == g3D_FA_ManualSyncLUT[i].hactive)\
									&&(userdata.vFreq == (g3D_FA_ManualSyncLUT[i].vfreq>>1))&&(phyInitiatedMode == g3D_FA_ManualSyncLUT[i].phyInitiatedMode)){
								HDMI20_SWWA(" DBG %d : SW WA for 3D FA signal %dx%d@%d 3G/6G=%d\n", port, userdata.hActive, userdata.vActive, userdata.vFreq, g3D_FA_ManualSyncLUT[i].phyInitiatedMode);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x408, g3D_FA_ManualSyncLUT[i].hBlankHactive);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, g3D_FA_ManualSyncLUT[i].hFrontHsync);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x414, g3D_FA_ManualSyncLUT[i].vFrontVsync);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x410, g3D_FA_ManualSyncLUT[i].vBlankVactive);

								gHDMI20RxHandler[port].manualSyncVICHist = gHDMI20RxHandler[port].timing_info.video_mode;

								gHDMI20RxHandler[port].ctrl.bsp_write(0x404, 0x00000003);
								
								data = 	gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
								data |= 0x0000003F;
								gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);

								__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
						
								break;	
							}
							else if(i == (HDMI20_MANUAL_3D_SYNC_PARAM_FA_MAXNUM -1)){
								HDMI20_VIDEO(" Notice %d : Could not find table for 3D FA %dx%d@%d 3G/6G=%d\n", port,userdata.hActive,  userdata.vActive, (userdata.vFreq<<1), phyInitiatedMode);
							}
						}
					}
					else{
						if((HDMI20_HAL_IsManualSyncSet(port) != 0)&&(gHDMI20RxHandler[port].timing_info.video_mode != gHDMI20RxHandler[port].manualSyncVICHist )){
							HDMI20_WARN("Warning %d : Detected wrong Manual Sync. VIC Current[%d]!=Hist[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, gHDMI20RxHandler[port].manualSyncVICHist);
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
					}
					
					if( gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
						userdata.vActive = actual_vActive_of_3DFA;
					}
					break;
				case LX_HDMI_EXT_3D_LINE_ALTERNATIVE:
					if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
						/* Do not change value*/
					}
					else{
						userdata.vTotal = userdata.vTotal >> 1;
						userdata.vActive = userdata.vActive >> 1;
						userdata.vStart = userdata.vStart >> 1;
					}
					break;
				case LX_HDMI_EXT_3D_SBSFULL:
					if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
						/* Do not change value*/
					}
					else{
						userdata.hTotal = userdata.hTotal >> 1;
						userdata.hActive = userdata.hActive >> 1;
						userdata.hStart = userdata.hStart >> 1;
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
		}

		/* Step 10. Reduce Horizontal into half on pixel repetition */
		if(gHDMI20RxHandler[port].timing_info.pixel_repetition > 0)
		{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 129){
				HDMI20_DBG("DBG %d : Pixel Repitition mode[%d] Htotal[%d] HActive[%d] HStart[%d]\n", port, gHDMI20RxHandler[port].timing_info.pixel_repetition,userdata.hTotal, userdata.hActive, userdata.hStart);
			}
			
			//if(gHDMI20RxHandler[port].timing_info.video_format == 1)
			userdata.PixelRepeat = gHDMI20RxHandler[port].timing_info.pixel_repetition;
			
			userdata.hTotal = userdata.hTotal >> 1;
			userdata.hActive = userdata.hActive >> 1;
			userdata.hStart = userdata.hStart >> 1;

			/* 2X mode for Pixel Repetition */
			if(gHDMI20RxHandler[port].timing_info.video_format == 1){
				data = 	gHDMI20RxHandler[port].top_read(0x18);
				data |= 0x00010000;
				gHDMI20RxHandler[port].top_write(0x18, data);
			}
		}
		else if(gHDMI20RxHandler[port].timing_info.pixel_repetition == 0)
		{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 129){
				HDMI20_DBG("DBG %d : Pixel Repitition mode[%d] Htotal[%d] HActive[%d] HStart[%d]\n", port, gHDMI20RxHandler[port].timing_info.pixel_repetition,userdata.hTotal, userdata.hActive, userdata.hStart);
			}


			/* 1X mode for non-Pixel Repetition */
			data = 	gHDMI20RxHandler[port].top_read(0x18);
			data &= (~0x000F0000);
			gHDMI20RxHandler[port].top_write(0x18, data);
		}

		/* Step 11. Double Vfreq for Interlaced signals */
		if(userdata.scanType == 0){
			userdata.vFreq = userdata.vFreq * 2;
		}

		/* Step. Fix UPlus+ 2880 issue on 1080p 24/25/30 */
		if(__HDMI20_HAL_IsHwInDVIState(port) == 0){
			if((gHDMI20RxHandler[port].timing_info.video_mode == 32)||(gHDMI20RxHandler[port].timing_info.video_mode == 72)){
				userdata.hTotal = 2750;
				userdata.hActive = 1920;
			}
			else if((gHDMI20RxHandler[port].timing_info.video_mode == 33)||(gHDMI20RxHandler[port].timing_info.video_mode == 73)\
					||(gHDMI20RxHandler[port].timing_info.video_mode == 20)||(gHDMI20RxHandler[port].timing_info.video_mode == 31 )
					||(gHDMI20RxHandler[port].timing_info.video_mode == 75)){
				userdata.hTotal = 2640;
				userdata.hActive = 1920;
			}
			else if((gHDMI20RxHandler[port].timing_info.video_mode == 34 )||(gHDMI20RxHandler[port].timing_info.video_mode == 74 )\
					||(gHDMI20RxHandler[port].timing_info.video_mode == 16 )||(gHDMI20RxHandler[port].timing_info.video_mode == 76 )
					||(gHDMI20RxHandler[port].timing_info.video_mode == 5)){
				userdata.hTotal = 2200;
				userdata.hActive = 1920;
			}
			else if(gHDMI20RxHandler[port].timing_info.video_mode == 39){
				userdata.hTotal = 2304;
				userdata.hActive = 1920;
			}

			/* Fixed wrong resolution bug */
			if((gHDMI20RxHandler[port].timing_info.video_mode == 93)||(gHDMI20RxHandler[port].timing_info.video_mode == 103)){
				userdata.hTotal = 5500;
				userdata.hActive = 3840;
			}
			else if((gHDMI20RxHandler[port].timing_info.video_mode == 94)||(gHDMI20RxHandler[port].timing_info.video_mode == 104)\
					||(gHDMI20RxHandler[port].timing_info.video_mode == 96 )||(gHDMI20RxHandler[port].timing_info.video_mode == 106)) {
				userdata.hTotal = 5280;
				userdata.hActive = 3840;
			}
			else if((gHDMI20RxHandler[port].timing_info.video_mode == 95 )||(gHDMI20RxHandler[port].timing_info.video_mode == 105 )\
					||(gHDMI20RxHandler[port].timing_info.video_mode == 97 )||(gHDMI20RxHandler[port].timing_info.video_mode == 107 )){
				userdata.hTotal = 4400;
				userdata.hActive = 3840;
			}
		}


		/* Step. Vfreq compenstate for VIC codes */
		data = __HDMI20_HAL_Rx_VICcodeToVfreqConversion(gHDMI20RxHandler[port].timing_info.video_mode);
		if( data > 0){

			if(__HDMI20_HAL_IsHwInDVIState(port)){
				/* Do Nothing for DVI */
			}
			else{
				if( data != userdata.vFreq){
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1747){
						HDMI20_DBG("DBG %d : Vfreq[%d] does not match VIC code[%d] vfreq[%d]\n", port, userdata.vFreq, gHDMI20RxHandler[port].timing_info.video_mode, data);
					}
					userdata.vFreq = data;
				}
			}
		}

		/* Step 11-1. SW WA for vfreq on VIC code : 50Hz */
		if((gHDMI20RxHandler[port].timing_info.video_mode >= 20)&&(gHDMI20RxHandler[port].timing_info.video_mode<=31)){
			if(userdata.vFreq != 500){
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 848){
					HDMI20_DBG("DBG %d : VIC code[%d] frame rate is not [%d]. (VIC : 500)\n", port, gHDMI20RxHandler[port].timing_info.video_mode, userdata.vFreq);
				}
				if(userdata.vFreq >= 500){
					if(userdata.vFreq - 500 < 30){
						userdata.vFreq = 500;
						if((userdata.vActive >= 2160) &&(userdata.hActive >=3840)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)){
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
					}
				}
				else{
					if(500 - userdata.vFreq < 30){
						userdata.vFreq = 500;
						if((userdata.vActive >= 2160) &&(userdata.hActive >=3840)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)){
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
					}
				}
				if(userdata.vFreq != 500){
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 848){
						HDMI20_DBG("DBG %d : VIC code[%d] frame rate and Vfreq is not same.[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, userdata.vFreq);
					}
				}
			}
		}

		/* Step 11-2. SW WA for vfreq on VIC code : 60Hz */
		if((gHDMI20RxHandler[port].timing_info.video_mode >= 1)&&(gHDMI20RxHandler[port].timing_info.video_mode<=16)){
			if(userdata.vFreq != 600){
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 848){
					HDMI20_DBG("DBG %d : VIC code[%d] frame rate is not [%d]. (VIC : 600)\n", port, gHDMI20RxHandler[port].timing_info.video_mode, userdata.vFreq);
				}
				if(userdata.vFreq >= 600){
					if(userdata.vFreq - 600 < 30){
						userdata.vFreq = 600;
						if((userdata.vActive >= 2160) &&(userdata.hActive >=3840)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)){
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
					}
				}
				else{
					if(600 - userdata.vFreq < 30){
						userdata.vFreq = 600;
						if((userdata.vActive >= 2160) &&(userdata.hActive >=3840)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)){
							HDMI20_HAL_ClearManualSyncSetting(port);
						}
					}
				}
				if(userdata.vFreq != 600){
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 848){
						HDMI20_DBG("DBG %d : VIC code[%d] frame rate and Vfreq is not same.[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, userdata.vFreq);
					}
				}		
			}
		}

		/* SW WA for VIC 22,18, 7 : Manual Sync */
		if((lg3DData != LX_HDMI_EXT_3D_FIELD_ALTERNATIVE)&&(lg3DData != LX_HDMI_EXT_3D_SBSFULL)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0)&&(gHDMI20RxDevControler[HDMI20__USE_MANUAL_SYNC_FOR_2K].value > 0)){

			if((HDMI20_HAL_IsManualSyncSet(port) != 0)&&(gHDMI20RxHandler[port].timing_info.video_mode != gHDMI20RxHandler[port].manualSyncVICHist )){
				HDMI20_WARN("Warning %d : Detected wrong Manual Sync. VIC Current[%d]!=Hist[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, gHDMI20RxHandler[port].manualSyncVICHist);
				HDMI20_HAL_ClearManualSyncSetting(port);
			}

			if((gHDMI20RxHandler[port].timing_info.video_mode == 22)||(gHDMI20RxHandler[port].timing_info.video_mode == 18)|| (gHDMI20RxHandler[port].timing_info.video_mode == 7)\
					|| (gHDMI20RxHandler[port].timing_info.video_mode == 14)|| (gHDMI20RxHandler[port].timing_info.video_mode == 16)|| (gHDMI20RxHandler[port].timing_info.video_mode == 4)){
				if(( HDMI20_HAL_IsManualSyncSet(port) == 0)&&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0) &&(gHDMI20RxHandler[port].ctrl.isMute == 0)){
					if(gHDMI20RxHandler[port].timing_info.video_mode == 22) data1 = HDMI20_MANUAL_SYNC_VIC22;
					else if(gHDMI20RxHandler[port].timing_info.video_mode == 18) data1 = HDMI20_MANUAL_SYNC_VIC18;
					else if(gHDMI20RxHandler[port].timing_info.video_mode == 7) data1 = HDMI20_MANUAL_SYNC_VIC7;
					else if(gHDMI20RxHandler[port].timing_info.video_mode == 14) data1 = HDMI20_MANUAL_SYNC_VIC14;
					else if(gHDMI20RxHandler[port].timing_info.video_mode == 16) data1 = HDMI20_MANUAL_SYNC_VIC16;
					else if(gHDMI20RxHandler[port].timing_info.video_mode == 4) data1 = HDMI20_MANUAL_SYNC_VIC4;
					else data1 = HDMI20_MANUAL_2D_2K_SYNC_PARAM_MAXNUM;

					if((userdata.hActive == g2D_2K_ManualSyncLUT[data1].hactive)&&(userdata.vActive == g2D_2K_ManualSyncLUT[data1].vactive)){
						gHDMI20RxHandler[port].ctrl.bsp_write(0x408, g2D_2K_ManualSyncLUT[data1].hBlankHactive);
						gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, g2D_2K_ManualSyncLUT[data1].hFrontHsync);
						gHDMI20RxHandler[port].ctrl.bsp_write(0x414, g2D_2K_ManualSyncLUT[data1].vFrontVsync);
						gHDMI20RxHandler[port].ctrl.bsp_write(0x410, g2D_2K_ManualSyncLUT[data1].vBlankVactive);
						gHDMI20RxHandler[port].isManualSyncMode = 2;

						gHDMI20RxHandler[port].manualSyncVICHist = gHDMI20RxHandler[port].timing_info.video_mode;

						data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
						data |= 0xF;
						if(userdata.scanType == 0){
							data |= 0x00000030;
						}

						data1 = 0;
						if((lg3DData != LX_HDMI_EXT_4K_2K)&&(lg3DData != LX_HDMI_EXT_2D_FORMAT)){
							data1 = vsi3DData; data1 = data1 << 1;
							data1 |= 0x00000001;
						}

						gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
						gHDMI20RxHandler[port].ctrl.bsp_write(0x404, data1);
						__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
					}

					if( HDMI20_HAL_IsManualSyncSet(port) != 0){
						if(gHDMI20RxHandler[port].ctrl.bsp_read(0x404) != 0x0){
							HDMI20_SWWA(" SWWA %d : Software Workaround for 3D VIC[%d] signal. 3D[%d]. Interlaced[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, vsi3DData, userdata.scanType);
						}
						else{
							HDMI20_SWWA(" SWWA %d : Software Workaround for 2D VIC[%d] signal. 3D[%d] Interlaced[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, vsi3DData, userdata.scanType);
						}
					}
					else{
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1147){
							HDMI20_DBG(" DBG %d : SW WA for VIC[%d] but hActive[%d]/vActive[%d] is not same as VIC\n", port, gHDMI20RxHandler[port].timing_info.video_mode, userdata.hActive, userdata.vActive);
						}
					}
				}
				else{
					if(gHDMI20RxHandler[port].ctrl.bsp_read(0x404) == 0x0){
						if((lg3DData != LX_HDMI_EXT_4K_2K)&&(lg3DData != LX_HDMI_EXT_2D_FORMAT)){
							HDMI20_VIDEO("Notice %d : Founded 3D after Manual Sync. 3D[%d]\n", port, vsi3DData);

							data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
							data |= 0xF;
							if(userdata.scanType == 0){
								data |= 0x00000030;
							}
							data1 = vsi3DData; data1 = data1 << 1;
							data1 |= 0x00000001;

							gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
							gHDMI20RxHandler[port].ctrl.bsp_write(0x404, data1);
							__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
						}
					}
					else{
						if(((gHDMI20RxHandler[port].ctrl.bsp_read(0x404)>>1)& 0xF ) != vsi3DData){
							HDMI20_VIDEO("Notice %d : Founded wrong 3D after Manual Sync. 3D[0x%x]/Set[0x%x]\n", port, vsi3DData, gHDMI20RxHandler[port].ctrl.bsp_read(0x404));

							data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
							data |= 0xF;
							if(userdata.scanType == 0){
								data |= 0x00000030;
							}

							data1 = vsi3DData; data1 = data1 << 1;
							data1 |= 0x00000001;

							gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
							gHDMI20RxHandler[port].ctrl.bsp_write(0x404, data1);
							__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
						}
					}
				}
			}
			else{
				currentTime = jiffies_to_msecs(jiffies);
				if(currentTime - gHDMI20RxHandler[port].updateTimingTime >= gHDMI20RxDevControler[HDMI20__DELAY_TIME_BEFORE_SETTING_2D_MANUAL_SYNC].value){
					if((gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0) &&(gHDMI20RxHandler[port].ctrl.isMute == 0)&&(lg3DData == LX_HDMI_EXT_2D_FORMAT)&&(gHDMI20RxDevControler[HDMI20__SET_MANUAL_SYNC_FOR_ALL_FHD].value >0)){
						if((userdata.vActive < 2160) && (userdata.hActive < 3840)){

							if((gHDMI20RxHandler[port].ctrl.hBlankHactive != 0) &&(gHDMI20RxHandler[port].ctrl.vFrontVsync != 0) &&\
									(gHDMI20RxHandler[port].ctrl.vFrontVsync != 0) && (gHDMI20RxHandler[port].ctrl.vBlankVactive != 0)){
								if( HDMI20_HAL_IsManualSyncSet(port) == 0){
									
									data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
									data |= 0xF;
									if(userdata.scanType == 0){
										data |= 0x00000030;
									}
							
									HDMI20_VIDEO("Notice %d : 2D Manual sync mode. 3D Flag[%d] \n", port, lg3DData);

									gHDMI20RxHandler[port].ctrl.bsp_write(0x408, gHDMI20RxHandler[port].ctrl.hBlankHactive);
									gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, gHDMI20RxHandler[port].ctrl.hFrontHsync);
									gHDMI20RxHandler[port].ctrl.bsp_write(0x414, gHDMI20RxHandler[port].ctrl.vFrontVsync);
									gHDMI20RxHandler[port].ctrl.bsp_write(0x410, gHDMI20RxHandler[port].ctrl.vBlankVactive);

									gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
									gHDMI20RxHandler[port].manualSyncVICHist = gHDMI20RxHandler[port].timing_info.video_mode;

									if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 334){
										if(gHDMI20RxHandler[port].timing_info.interlaced){
											gHDMI20RxHandler[port].ctrl.bsp_write(0x158, 0x3);
										}
										else{
											gHDMI20RxHandler[port].ctrl.bsp_write(0x158, 0x2);
										}
									}
									__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
								}
							}
						}
					}
					else{
						if((gHDMI20RxHandler[port].timing_info.video_mode == 5)&&(gHDMI20RxHandler[port].ctrl.isMute == 0)&&(lg3DData == LX_HDMI_EXT_2D_FORMAT) ){
							if( HDMI20_HAL_IsManualSyncSet(port) == 0){
								HDMI20_VIDEO("Notice %d : 2D Manual sync mode for VIC5(Master 394). 3D Flag[%d] \n", port, lg3DData);
		
								data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
								data |= 0x37;

								gHDMI20RxHandler[port].manualSyncVICHist = gHDMI20RxHandler[port].timing_info.video_mode;

								gHDMI20RxHandler[port].ctrl.bsp_write(0x408, 0x01180780);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, 0x0058002C);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x414, 0x00020005);
								gHDMI20RxHandler[port].ctrl.bsp_write(0x410, 0x0016021C);

								gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);

								__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
							}
						}
					}
				}
				else{
					HDMI20_VIDEO("Notice %d : Waiting hold time for manual sync entry\n", port);	
				}
			}
		}
		else if((lg3DData == LX_HDMI_EXT_3D_SBSFULL)&&(gHDMI20RxDevControler[HDMI20__USE_MANUAL_SYNC_FOR_SSF].value > 0)){
			if((gHDMI20RxHandler[port].timing_info.video_mode == 22)&& ( HDMI20_HAL_IsManualSyncSet(port) == 0) &&(gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0) &&(gHDMI20RxHandler[port].ctrl.isMute == 0)){
				if(HDMI20_HAL_IsManualSyncSet(port) == 0){
					gHDMI20RxHandler[port].ctrl.bsp_write(0x408, 0x02400B40);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, 0x003000FC);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x414, 0x00020003);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x410, 0x00180120);
					gHDMI20RxHandler[port].isManualSyncMode = 2;

					gHDMI20RxHandler[port].manualSyncVICHist = gHDMI20RxHandler[port].timing_info.video_mode;

					data1 = 0x9;
					data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
					data |= 0x37;
					gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x404, data1);
					__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x158, 3);

					if(HDMI20_HAL_IsManualSyncSet(port) != 0){
						if(gHDMI20RxHandler[port].ctrl.bsp_read(0x404) != 0x0){
							HDMI20_SWWA(" SWWA %d : Software Workaround for 3D VIC[%d] signal. 3D[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, vsi3DData );
						}
						else{
							HDMI20_SWWA(" SWWA %d : Software Workaround for 2D VIC[%d] signal. 3D[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, vsi3DData );
						}

						__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
					}
					else{
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1147){
							HDMI20_DBG(" DBG %d : SW WA for VIC[%d] but hActive[%d]/vActive[%d] is not same as VIC\n", port, gHDMI20RxHandler[port].timing_info.video_mode, userdata.hActive, userdata.vActive);
						}
					}
				}
				else if((HDMI20_HAL_IsManualSyncSet(port) != 0)&&(gHDMI20RxHandler[port].timing_info.video_mode != gHDMI20RxHandler[port].manualSyncVICHist )){
					HDMI20_VIDEO(" Notice %d : Detected wrong Manual Sync. VIC Current[%d]!=Hist[%d]\n", port, gHDMI20RxHandler[port].timing_info.video_mode, gHDMI20RxHandler[port].manualSyncVICHist);
					HDMI20_HAL_ClearManualSyncSetting(port);
				}
			}
		}

		/* Manual Sync for DVI timing info */
		if((gHDMI20RxDevControler[HDMI20__ENABLE_MANUAL_SYNC].value > 0) &&(gHDMI20RxDevControler[HDMI20__SET_MANUAL_SYNC_FOR_ALL_FHD].value == 0) &&\
				(gHDMI20RxDevControler[HDMI20__USE_MANUAL_SYNC_FOR_DVI].value > 0)){

			if((HDMI20_HAL_IsManualSyncSet(port) == 0)&&(gHDMI20RxHandler[port].ctrl.isMute == 0)){
				/* MSPG 114 TIMING INFO */
				if((gHDMI20RxHandler[port].timing_info.video_mode == 0)&&(userdata.hActive == 1600)&&(userdata.vActive == 1024)\
						&&(userdata.vFreq == 600)&&(userdata.hTotal ==1808)){
					HDMI20_VIDEO("Notice %d : 2D Manual sync mode for DVI-1600x1024@60Hz(Master 114/115).\n", port);

					data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
					data |= 0xE;

					gHDMI20RxHandler[port].ctrl.bsp_write(0x408, 0x00D00640);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x40C, 0x00020002);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x414, 0x00020002);
					gHDMI20RxHandler[port].ctrl.bsp_write(0x410, 0x00100400);

					gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
					__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
				}
			}
		}

		/* Detect late 3D on 2D manual sync */
		if((( HDMI20_HAL_IsManualSyncSet(port) != 0x0) && (gHDMI20RxHandler[port].ctrl.bsp_read(0x400) & 0x80000000) == 0x0) &&(gHDMI20RxDevControler[HDMI20__SET_MANUAL_SYNC_FOR_ALL_FHD].value >0)){
			if(((gHDMI20RxHandler[port].ctrl.bsp_read(0x404)>>1) & 0x0000000F ) != vsi3DData){
				if((userdata.vActive < 2160) && (userdata.hActive < 3840)){
					if((vsi3DData == 0)||(vsi3DData == 1)||(vsi3DData == 2)||(vsi3DData == 3)||(vsi3DData == 6)||(vsi3DData == 8)){
						if((lg3DData != LX_HDMI_EXT_2D_FORMAT)&&(lg3DData != LX_HDMI_EXT_3D_FIELD_ALTERNATIVE)&&(lg3DData != LX_HDMI_EXT_3D_SBSFULL)&&(lg3DData != LX_HDMI_EXT_3D_TNB)){
							HDMI20_WARN("Warning %d : Founded different 3D after 2D Manual Sync. vsi[%d] !=reg[%d]\n", port, vsi3DData, ((gHDMI20RxHandler[port].ctrl.bsp_read(0x404)>>1) & 0x0000000F));

							data1 = vsi3DData; data1 = data1 << 1;
							data1 |= 0x00000001;

							gHDMI20RxHandler[port].ctrl.bsp_write(0x404, data1);
							__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);
						}
						else if(lg3DData == LX_HDMI_EXT_3D_TNB){
							HDMI20_WARN("Warning %d : Founded TNB 3D on 2D Manual Sync. Return to AutoSync. vsi[%d]\n", port, vsi3DData);
							HDMI20_HAL_ClearManualSyncSetting(port);
							__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_FULL, __L__);

						}
					}
				}
			}
		}

		/* SW WA */
		if((gHDMI20RxHandler[port].isManualSyncMode == 2)){
			if((userdata.hActive == 2880)&&(userdata.vActive == 600)){
				//userdata.hActive = 720;
				userdata.vActive = 576;
			}
		}

		/* SW WA */
		if(__HDMI20_HAL_IsHwInDVIState(port) == 0){
			if(( gHDMI20RxHandler[port].timing_info.video_mode == 22)&&(gHDMI20RxHandler[port].timing_info.pixel_repetition == 0)){
				userdata.vActive = 576; 
				userdata.hActive = 1440;
				if(lg3DData == LX_HDMI_EXT_3D_SBSFULL){
					if(gHDMI20RxDevControler[HDMI20__FORCE_ORIGIN_TIME_FOR_3D].value){
						/* Do not change value : Restore*/
						userdata.hActive = 2880; 
					}
					userdata.hTotal = 3456;
					userdata.vFreq = 500;
				}
			}
		}

		/* Step 12. Copy Data to user */
		if(gHDMI20RxHandler[port].ctrl.isMute != 0){
			/* Mute */
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 230) {
				memset((void *)&userdata, 0, sizeof(LX_HDMI_TIMING_INFO_T));
			}
			else{
				HDMI20_HAL_Rx_SetLocalVideoMute(port, 1, 1, __L__);
			}

			HDMI20_HAL_Rx_Set_AudioReset(port);
		}
#if 0		
		else{
			if (gHDMI20RxHandler[port].audioStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value) {
				gHDMI20RxHandler[port].audioStandByCnt++;
				if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != 0)HDMI20_AUDIO("Audio stand by cnt : %d",gHDMI20RxHandler[port].audioStandByCnt);
			}
		}
#endif
		/* To block HDCP14 transition noise */
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1134){
			if((gHDMI20RxHandler[port].ctrl.bsp_read(0x8FC) == 0x4000)&&(gHDMI20RxHandler[port].ctrl.bsp_read(0xFC) != 0x201)){
				if((gHDMI20RxHandler[port].ctrl.bsp_read(0xFC) == 0x101)||(gHDMI20RxHandler[port].ctrl.bsp_read(0xFC) == 0x301)){
					if(gHDMI20RxHandler[port].stablehdcp14time < gHDMI20RxDevControler[HDMI20__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY].value)	{
						/* Mute */
						memset((void *)&userdata, 0, sizeof(LX_HDMI_TIMING_INFO_T));
						if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1133){
							HDMI20_VIDEO("Notice %d : MUTE due to TMDS unstable. [%d]\n", port, gHDMI20RxHandler[port].stablehdcp14time);
						}
					}
				}
			}
		}

		if((userdata.vActive == 0) || (userdata.hActive == 0) || (userdata.vFreq == 0)){
			HDMI20_HAL_Rx_Set_AudioReset(port);
		}


		if(gHDMI20RxHandler[port].dcm_change != 0){
			HDMI20_VIDEO("Notice [%d] : Do not update timing info on DCM change\n", port);
			userdata.hActive = 0;
			userdata.vActive = 0;
			userdata.vFreq = 0;
		}


		if(gHDMI20RxHandler[port].ctrl.bsp_read(0x30) & 0x00000001){
			// PLL OK!	
		}
		else{
			userdata.hActive = 0;
			userdata.vActive = 0;
			userdata.vFreq = 0;
		}


		/* Timing Value Check : Always place this part on the last part before copying timing info to MW */
		if (userdata.hActive %4 != 0)	//150209 : OTT STB 1080P 50Hz Flickering (1920x1078)
		{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1017){
				HDMI20_DBG("%s : hActive modification [%d]\n", __F__, userdata.hActive);
			}
			if ( u32CHK_RANGE(userdata.hActive, 4096, 2) )		userdata.hActive = 4096;
			else if ( u32CHK_RANGE(userdata.hActive, 3840, 2) )	userdata.hActive = 3840;
			else if ( u32CHK_RANGE(userdata.hActive, 2880, 2) )	userdata.hActive = 2880;
			else if ( u32CHK_RANGE(userdata.hActive, 1920, 2) )	userdata.hActive = 1920;
			else if ( u32CHK_RANGE(userdata.hActive, 1440, 2) )	userdata.hActive = 1440;
			else if ( u32CHK_RANGE(userdata.hActive, 1280, 2) )	userdata.hActive = 1280;
			else if ( u32CHK_RANGE(userdata.hActive, 720, 2) )		userdata.hActive = 720;
			else if ( u32CHK_RANGE(userdata.hActive, 640, 2) )		userdata.hActive = 640;
		}

		if (userdata.vActive %4 != 0)	//150209 : OTT STB 1080P 50Hz Flickering (1920x1078)
		{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1017){
				HDMI20_DBG("[%d] %s : vActive modification [%d]\n", __L__, __F__, userdata.vActive);
			}
			if ( u32CHK_RANGE(userdata.vActive, 2160, 2) )		userdata.vActive = 2160;
			else if ( u32CHK_RANGE(userdata.vActive, 1080, 2) )	userdata.vActive = 1080;
			else if ( u32CHK_RANGE(userdata.vActive, 720, 2) )		userdata.vActive = 720;
			else if ( u32CHK_RANGE(userdata.vActive, 576, 2) )		userdata.vActive = 576;
			else if ( u32CHK_RANGE(userdata.vActive, 480, 2) )		userdata.vActive = 480;
			else if ( u32CHK_RANGE(userdata.vActive, 288, 2) )		userdata.vActive = 288;
			else if ( u32CHK_RANGE(userdata.vActive, 240, 2) )		userdata.vActive = 240;
			else if ( userdata.vActive == 483)	userdata.vActive = 483;
		}

		userdata.pixelClock = gHDMI20RxHandler[port].real_pixel_clk;

		/* Step 21. Add DVI Info */
		userdata.isDVI = gHDMI20RxHandler[port].timing_info.dvi; 

		/* Step 22. Add Deep Color Info */
		userdata.deepColorMode = gHDMI20RxHandler[port].timing_info.deep_color_mode;

	} while(0);

	if(__HDMI20_HAL_IsPVOMode(port) == RET_OK){
		userdata.isPVOMode = 1;
	}
	else{
		userdata.isPVOMode = 0;
	}

	if(pData != NULL) {
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
	}

	return ret;

}

/* IOCTL */
static int __HDMI20_HAL_Rx_Get_SrcDeviceInfo(UINT8 port, LX_HDMI20_SRCINFO_T *pData, int size)
{
	int ret = RET_ERROR;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		/* THis was used on H15, but will not be used for  */

		ret = RET_OK;
	} while(0);

	return ret;

}


/* IOCTL */
static int __HDMI20_HAL_Rx_Get_AKSVData(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size)
{
	int ret = RET_OK;

	do{
		/* Not Used */
	} while(0);

	return ret;

}

/* IOCTL */
static int __HDMI20_HAL_Rx_Set_ResetTimingInfo(void)
{
	int ret = RET_OK;

	do{
		/* Not used */
	} while(0);

	return ret;

}

 /* IOCTL */
static int __HDMI20_HAL_Rx_Set_CountryInfo(UINT8 port, UINT8 *pData, int size)
{
	int ret = RET_ERROR;
	UINT32 countryData;

	do{
		HDMI20_INFO("NOTI %d : Set Country Code from MW\n", port);

		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(UINT32)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(UINT32), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		memset((void *)&countryData, 0, sizeof(UINT32));

		if( copy_from_user(&countryData, (void __user *)pData, sizeof(UINT32))){
			HDMI20_ERROR("Cannot copy country data structure from user\n");
			break;
		}

		HDMI20_INFO("Notice [%d] : Got Country Data[%d]\n", port, countryData);

		if(countryData == gHDMI20RxDevControler[HDMI20__FORCE_OESS_COUNTRY_VAL].value)
		{
			HDMI20_INFO("Notice [%d] : Detected OESS/EESS WA country\n", port);

			gHDMI20RxDevControler[HDMI20__LINK_REG_0X80_HDMI_MODE_RECOVER].value = 0x30010004;
		}
		else{
			HDMI20_INFO("Notice [%d] : Country code is not for WA\n", port);
		}


		ret = RET_OK;
	} while(0);

	return ret;
}


/* IOCTL */
int HDMI20_HAL_Rx_Set_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	UINT32 edidData[(HDMI20_HAL_SIZE_OF_EDID >> 2)];
	int i;
	UINT32 addr;
	UINT32 dbgData;
	UINT32 data;

	do{
		HDMI20_INFO("NOTI %d : Set Internal EDID from MW\n", port);

		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size > HDMI20_HAL_SIZE_OF_EDID){
			HDMI20_ERROR("Error! Size is over limie!([%d] < [%d]) \n", HDMI20_HAL_SIZE_OF_EDID, size);
			break;
		}

		if (size%8) {
			HDMI20_ERROR("Error! Does not allow non-8byte aligned mem access. Size[%d]\n", size);
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ) {
			gpiod_set_raw_value(gpiod_hdmi20 ,1);	
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ) {
			/* ISOL Release */
			data = *pISol_Addr1;
			data |= gHDMI20ChipRegHandler.isol_2_VAL;
			*pISol_Addr1 = data;

			data = *pISol_Addr2;
			data |= gHDMI20ChipRegHandler.isol_3_VAL;
			*pISol_Addr2 = data;

			data = *pISol_Addr0;
			data |= gHDMI20ChipRegHandler.isol_1_VAL;
			*pISol_Addr0 = data;	
			/* End of ISOL Release */
		}
		else {
			if( lx_chip_rev( ) >= LX_CHIP_REV( M17, C0) ){
				/* M17 C0 */
				gpiod_set_raw_value(gpiod_hdmi20 ,1);	
			}
			else{
				/* M17 A0 */
				/* ISOL Release */
				data = *pISol_Addr1;
				data |= gHDMI20ChipRegHandler.isol_2_VAL;
				*pISol_Addr1 = data;

				data = *pISol_Addr2;
				data |= gHDMI20ChipRegHandler.isol_3_VAL;
				*pISol_Addr2 = data;

				data = *pISol_Addr0;
				data |= gHDMI20ChipRegHandler.isol_1_VAL;
				*pISol_Addr0 = data;	
				/* End of ISOL Release */
			}
		}

		memset((void *)&edidData, 0, HDMI20_HAL_SIZE_OF_EDID);

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
		memcpy((void *)&gHDMI20RxHandler[port].edidData, (void *)edidData, HDMI20_HAL_SIZE_OF_EDID);
		
		gHDMI20RxHandler[port].wasEdidWritten = true;
		
		addr = 	(UINT32)HDMI20_HAL_RX_INTERNAL_EDID_OFFSET;
		
		for(i=0; i<(HDMI20_HAL_SIZE_OF_EDID >> 2); i++){
			gHDMI20RxHandler[port].top_write(addr, edidData[i]);
			dbgData = gHDMI20RxHandler[port].top_read(addr);

			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1016){
				HDMI20_DBG("Internal EDID[%d] : BYTE [%d] =  [0x%x]<=[0x%08x] (0x%08x)\n", port, i, addr, edidData[i],dbgData);
			}
			addr += 4;
		}

		/* Write EDID for ALED */
		addr = 	(UINT32)HDMI20_RX_ALED_AD_EDID_OFFSET;
		
		for(i=0; i<(HDMI20_HAL_SIZE_OF_EDID >> 2); i++){
			gHDMI20RxHandler[port].aled_write(addr, edidData[i]);
			dbgData = gHDMI20RxHandler[port].aled_read(addr);

			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1016){
				HDMI20_DBG("Internal EDID[%d] : BYTE [%d] =  [0x%x]<=[0x%08x] (0x%08x)\n", port, i, addr, edidData[i],dbgData);
			}
			addr += 4;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI20_HAL_Rx_Get_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall)
{
	int i;
	int ret = RET_ERROR;
	UINT32 edidData[(HDMI20_HAL_SIZE_OF_EDID >> 2)];
	UINT32 addr;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size > HDMI20_HAL_SIZE_OF_EDID){
			HDMI20_ERROR("Error! Size is over limie!([%d] < [%d]) \n", HDMI20_HAL_SIZE_OF_EDID, size);
			break;
		}

		if (size%8) {
			HDMI20_ERROR("Error! Does not allow non-8byte aligned mem access. Size[%d]\n", size);
		}


		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__USE_ALWAYS_EDID].value >0){
			addr = 	(UINT32)HDMI20_RX_ALED_AD_EDID_OFFSET;

			for(i=0; i<(HDMI20_HAL_SIZE_OF_EDID >>2); i++){
				edidData[i] = gHDMI20RxHandler[port].aled_read(addr);

				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1016){
					HDMI20_DBG("Internal EDID[%d] : BYTE [%d] -- [0x%x]<=[0x%08x]\n", port, i, addr, edidData[i]);
				}
				addr += 4;
			}

		}
		else{
			addr = 	(UINT32)HDMI20_HAL_RX_INTERNAL_EDID_OFFSET;

			for(i=0; i<(HDMI20_HAL_SIZE_OF_EDID >>2); i++){
				edidData[i] = gHDMI20RxHandler[port].top_read(addr);

				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1016){
					HDMI20_DBG("Internal EDID[%d] : BYTE [%d] -- [0x%x]<=[0x%08x]\n", port, i, addr, edidData[i]);
				}
				addr += 4;
			}
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
int HDMI20_HAL_Rx_Set_HDCP14(UINT8 port, UINT32 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(struct hdmi_rx_ctrl_hdcp)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_TIMING_INFO_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(isInternalCall > 0){
			memcpy((void *)&gHDMI20RxHandler[port].hdcp, (void *)pData, sizeof(struct hdmi_rx_ctrl_hdcp));
		}
		else{
			if( copy_from_user((void *)&gHDMI20RxHandler[port].hdcp, (void __user *)pData, sizeof(struct hdmi_rx_ctrl_hdcp))){
				HDMI20_ERROR("Cannot copy HDCP1.4 data structure from user\n");
				break;
			}
		}

		/* Turn off HDCP1.4 bypass mode (double check) */
		gHDMI20RxHandler[port].gWasHDCP14Written = 1;

		HDMI20_INFO("Writing HDCP1.4 key to HDMI 2.0 Port[%d]\n", port);
		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
static int __HDMI20_HAL_Rx_Get_HDCP14(UINT8 port, UINT32 *pData, int size)
{
	int ret = RET_ERROR;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(struct hdmi_rx_ctrl_hdcp)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_TIMING_INFO_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		ret = copy_to_user((void __user *)pData, (void *)&gHDMI20RxHandler[port].hdcp, sizeof(struct hdmi_rx_ctrl_hdcp));
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

int HDMI20_HAL_Rx_Set_DisableHDMI(UINT8 port, int isDisable)
{
	int ret = RET_ERROR;

	do{
		HDMI20_INFO("Notice %d : Set Disable HDMI => [%s]\n", port, isDisable?"Disable":"Enable");

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(isDisable){
			gHDMI20RxHandler[port].hdmiDisabled = true;

			if(gHDMI20RxHandler[port].is5Vconnected > 0){
				HDMI20_HAL_ConnectCable(port, 0);
			}
		}
		else{
			gHDMI20RxHandler[port].hdmiDisabled = false;
			HDMI20_HAL_ConnectCable(port, 1);
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI20_HAL_Rx_Set_RestartHPD(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 totalDownTime = gHDMI20RxDevControler[HDMI20__TIME_OF_HPD_DOWN_ON_RESTART_HPD].value + gAdditionalHpdLowDuration;


	HDMI20_INFO("Notice %d : Restart HPD for [%d] msec\n", port, totalDownTime);


	do{
		if(gHDMI20RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if(gHDMI20RxHandler[port].restartHpdFlagUp == true){
			HDMI20_WARN("Warning %d :  Restart HPD is in progress. This will increase HPD low time for amount of unit time(%d)\n", port, totalDownTime);
		}

		#if 0
		HDMI20_HAL_ConnectCable(port, OFF);
		#endif
		
		gHDMI20RxHandler[port].restartHpdFlagUp = true;
		gHDMI20RxHandler[port].restartHPDTimeStamp = jiffies_to_msecs(jiffies);



		ret = RET_OK;
	} while(0);

	return ret;

}


/* IOCTL */
static int __HDMI20_HAL_Rx_Set_EnableHPD(UINT8 port ,UINT8 onOff, UINT8 force, UINT32 callerId)
{
	int ret = RET_ERROR;
	UINT32 data;
	
	if(gHDMI20RxHandler[port].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return RET_ERROR;
	}
													
	if(force == 0){
		HDMI20_INFO("HPD Control from KADP Port[%d] <= HPD[%s]. Caller[%u]\n", port, onOff?"UP":"DOWN", callerId);
	}
	else{
		HDMI20_INFO("Force HPD Port[%d] <= HPD[%s]. Caller[%u]\n", port, onOff?"UP":"DOWN", callerId);
	}

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		data = gHDMI20RxHandler[port].top_read(HDMI20_RX_HPD_DDC_SET);

		if(gHDMI20RxHandler[port].isHPDInverseMode){
			if(onOff){
				hdmi_rx_ctrl_hpd((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 0);
				gHDMI20RxHandler[port].isHPD = 1;
				data &= (~HDMI20_RX_HPD_DDC_SET_HPD);
			}
			else{
				if(gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value > 0){
					HDMI20_INFO(" Delay requested for HPD Up [%d]msec\n", gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value);
					msleep(gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value);
				}
				hdmi_rx_ctrl_hpd((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 1);
				gHDMI20RxHandler[port].isHPD = 0;
				data |= (HDMI20_RX_HPD_DDC_SET_HPD);
			}
		}
		else {
			if(onOff){
				if(gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value > 0){
					HDMI20_INFO(" Delay requested for HPD Up [%d]msec\n", gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value);
					msleep(gHDMI20RxDevControler[HDMI20__LINK_HPD_DELAY_TIME].value);
				}
				hdmi_rx_ctrl_hpd((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 1);
				gHDMI20RxHandler[port].isHPD = 1;
				data |= (HDMI20_RX_HPD_DDC_SET_HPD);
			}
			else{
				hdmi_rx_ctrl_hpd((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 0);
				gHDMI20RxHandler[port].isHPD = 0;
				data &= (~HDMI20_RX_HPD_DDC_SET_HPD);
			}
		}

		//gHDMI20RxHandler[port].hpd_request = 0;

		data |= (HDMI20_RX_HPD_DDC_SET_HPD_SEL);
		gHDMI20RxHandler[port].top_write(HDMI20_RX_HPD_DDC_SET, data);

		if(gHDMI20RxHandler[port].hdmiDisabled > 0){
			HDMI20_INFO("Notice [%d] : HDMI disabled detected on HPD Down. Rxsense down also\n", port);
			HDMI20_PHY_ControlPhyPDB(port, 0);
		}

		ret = RET_OK;

	} while(0);

	return ret;
}

/* IOCTL */
static int __HDMI20_HAL_Rx_Set_EnableEDID(UINT8 onOff)
{
	int ret = RET_OK;

	do{

	} while(0);

	return ret;

}


static void __HDMI20_HAL_Rx_InitiateHDMI20Data(UINT8 port, int isCablePlug)
{
	UINT32 previous_dcm = 0;	

	previous_dcm = gHDMI20RxHandler[port].ctrl.previous_video.deep_color_mode;
	/* Initiate handler's video data */
	memset((void *)&gHDMI20RxHandler[port].ctrl.previous_video, 0 , sizeof(struct hdmi_rx_ctrl_video));
	gHDMI20RxHandler[port].ctrl.previous_video.deep_color_mode = previous_dcm;

	/* Due to the fact that, the TMDS_CLK will only be updated when there is a ISR..
	 * Dangerous to clear the TMDS_CLK info */
	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1107){	
		if(isCablePlug){
			gHDMI20RxHandler[port].ctrl.tmds_clk = 0;
			gHDMI20RxHandler[port].ctrl.tmds_clock_old = 0;
		}
	}

	gHDMI20RxHandler[port].real_tmds_clk = 0;
	gHDMI20RxHandler[port].real_pixel_clk = 0;

	gHDMI20RxHandler[port].isFreeSyncMode = 0;
	gHDMI20RxHandler[port].isAllmMode = 0;

	//gHDMI20RxHandler[port].isManualSyncMode = 0;
	//gHDMI20RxHandler[port].phyLostCnt = 0;
	/* Initiate handlers' audio data */
	memset((void *)&gHDMI20RxHandler[port].audio, 0, sizeof(struct hdmi_rx_ctrl_audio));

	/* Reset Data Packet Buffer */
	HDMI20_ResetDataPacketBuffer(hdmi_rx_ctrl_packet_cnt, port);
	HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_MAXNUM, port);

	HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 1, __L__);
}

/* DBG function */
static void __HDMI20_HAL_Rx_DBG_PrintSavedEDID(UINT8 port)
{
	int i = 0;

	UINT8 edid_data[HDMI20_HAL_SIZE_OF_EDID] = {0,};

	memcpy((void *)&edid_data, (void *)gHDMI20RxHandler[port].edidData, HDMI20_HAL_SIZE_OF_EDID);

	printk("=========================================================================================================================\n");
	printk("[0x00] |  [0x00] [0x01] [0x02] [0x03] [0x04] [0x05] [0x06] [0x07] [0x08] [0x09] [0x0A] [0x0B] [0x0C] [0x0D] [0x0E] [0x0F]\n");
	printk("=========================================================================================================================\n");

	for (i = 0; i < 16; i++) {
		if((i==0)||(i==8)){
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

/* DBG function */
static void __HDMI20_HAL_Rx_DBG_PrintHandler(HDMI20_HAL_RX_DEVICE_DATA *handler)
{
	if(handler == 0) {
		HDMI20_ERROR("NULL pointer \n");
		return;
	}
	HDMI20_INFO("Kenerl Driver Date : %d\n", HDMI20_KERNEL_DRIVER_DATE);
	HDMI20_INFO("Port[%d] => Dev initiated[%d]\n", handler->ctrl.device_id, handler->initiated);
	HDMI20_INFO("LINK IRQ GIC[%d], TOP IRQ GIC[%d]\n", handler->irq, handler->top_irq);
	HDMI20_INFO("Deep Color Mode[%d]\n", handler->currentDCMMode);
	HDMI20_INFO(" HDCP14Written[%d]/HDCP22Written[%d]\n",handler->gWasHDCP14Written, handler->gWasHDCP22Written);
	HDMI20_INFO("AVMuteOnTime[%d], CableConnectedTime[%d], AudioMuteEnableCnt[%d]\n", handler->avmute_on_time, handler->cable_connect_time,handler->audioStandByCnt);
	HDMI20_INFO("IsManualSyncMode[%d], RealTMDSCLK[%d], RealPixelCLK[%d]\n", handler->isManualSyncMode, handler->real_tmds_clk, handler->real_pixel_clk);
	HDMI20_INFO("RealVFreq[%d], LocalMuteTimer[%d], VtotalBuffer[%d]\n", handler->real_vfreq, handler->localmutetimer, handler->vtotalbuffer);
	HDMI20_INFO("isMHL[%d], isARC[%d], isAudioMute[%d], isPhyLocked[%d]\n", handler->isMHLMode, handler->isAudioARCMode, handler->isAudioMute, handler->isPhyLocked);
	HDMI20_INFO("is5V[%d], isHPD[%d], isScdcUD[%d], isHDCP22[%d], isHDCP14[%d], isHDCP22Ncap[%d]\n", handler->is5Vconnected, handler->isHPD, handler->isScdcUD, handler->isHDCP22, handler->isHDCP14, handler->isHDCP22Ncap);
	HDMI20_INFO("TimingInvalid[%d], HPD_Request[%d],ConnectRequest[%d], EDIDWritten[%d]\n", handler->isTimingInvalid,handler->hpd_request,handler->connect_request,handler->wasEdidWritten);
	HDMI20_INFO("PhyInitiatedMode[%d], LockingTime[%d]\n", handler->phyInitiatedMode,handler->locking_time);
	HDMI20_INFO("audioStableCnt[%d], audioChMapCnt[%d], audioFifoErrMuteCnt[%d]\n",handler->audioStableCnt,handler->audioChMapCnt,handler->audioFifoErrMuteCnt);
	HDMI20_INFO("5VConnectedTime[%d], StableHDCP14[%d], TCSDone[%d], PhyStableCNT[%d]\n", handler->connected5Vtime, handler->stablehdcp14time, handler->phyTCSDone,handler->phy_stable_cnt); 
	HDMI20_INFO(" TCS DIFF CH0[%d]/CH1[%d]/CH2[%d]\n", handler->phyTCSDiff[0], handler->phyTCSDiff[1],handler->phyTCSDiff[2]);
	HDMI20_INFO(" TCS MIN CH0[%d]/CH1[%d]/CH2[%d]\n", handler->phyTCSMin[0], handler->phyTCSMin[1],handler->phyTCSMin[2]);
	HDMI20_INFO(" TCS Max CH0[%d]/CH1[%d]/CH2[%d]\n", handler->phyTCSMax[0], handler->phyTCSMax[1],handler->phyTCSMax[2]);
	HDMI20_INFO(" HPD INVERSE MODE PORT[%d] => [%d]\n", handler->ctrl.device_id, handler->isHPDInverseMode);
	HDMI20_INFO(" PHY Exception Case[0x%08x]\n", handler->phyExceptionState);
	HDMI20_INFO(" IsTimingInfoEmpty =>[%d]\n", HDMI20_HAL_IsTimingInfoEmpty(handler->ctrl.device_id));
	HDMI20_INFO(" TMDSRangeCurrnet[%d], TMDSRangePrev[%d]\n", gHDMI20RxHandler[handler->ctrl.device_id].phyCurrentTMDSExceptionRange, gHDMI20RxHandler[handler->ctrl.device_id].phyPrevTMDSExceptionRange);
	HDMI20_INFO(" TMDSRangeCurrnet_2[%d], TMDSRangePrev_2[%d]\n", gHDMI20RxHandler[handler->ctrl.device_id].phyCurrentTMDSExceptionRange_2, gHDMI20RxHandler[handler->ctrl.device_id].phyPrevTMDSExceptionRange_2);
	HDMI20_INFO(" isAllmMode[%d], allmRecieveTime[%d]\n", gHDMI20RxHandler[handler->ctrl.device_id].isAllmMode, gHDMI20RxHandler[handler->ctrl.device_id].allm_recieve_time);
}


/* DBG function */
static void __HDMI20_HAL_Rx_DBG_PrintVideo(HDMI20_HAL_RX_DEVICE_DATA *handler)
{
	int ret;
	int vfreq = 0;
	int hfreq = 0;
	struct hdmi_rx_ctrl_video v = {0};
	struct hdmi_rx_ctrl_audio a = {0};

	if(handler == 0) {
		HDMI20_ERROR("NULL pointer \n");
		return;
	}

	if(handler->initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return;
	}

	ret = hdmi_rx_ctrl_get_video(&handler->ctrl, &v, 4);
	if(ret < 0) {
		if( ret != -ERANGE) {
			HDMI20_ERROR("Error when attempting to achieve video data[%d]\n",  ret);
			return;
		}
		else{
			HDMI20_ERROR("Bad video or no signal\n");
		}
	}

	ret = hdmi_rx_ctrl_get_audio(&handler->ctrl, &a);
	if( ret < 0) {
		HDMI20_ERROR("Error when attemting to achieve AUDIO data[%d]\n", ret);
		//return;
	}


	if((v.pixel_clk == 0)||(v.vtotal == 0)||(v.htotal == 0)){
		vfreq = 0;
	}
	else{
		vfreq = (v.pixel_clk * 1000)/(v.vtotal * v.htotal);
	}


	if((v.pixel_clk == 0)||(v.htotal == 0)){
		hfreq = 0;
	}
	else{
		hfreq = ((v.pixel_clk * 1000) / v.htotal); 					///< Horizontal frequency(100 Hz unit)
	}

	HDMI20_INFO("HDMI 2.0 Port [%d] VIDEO Status [%d] Timing Invalid[%d] ManualSync Mode[%d]\n", handler->ctrl.device_id, handler->ctrl.stable_cnt,handler->isTimingInvalid, handler->isManualSyncMode);
	/** DVI detection status: DVI (true) or HDMI (false) */
	HDMI20_INFO("  DVI(1) or HDMI(0)       => [%d]\n",v.dvi);
	/** Deep color mode: 24, 30, 36 or 48 [bits per pixel] */
	HDMI20_INFO("  Deep Color Mode         => [%d]\n",v.deep_color_mode);

	HDMI20_INFO("[Video Status]\n");
	/** Pixel clock frequency [kHz] */
	HDMI20_INFO("  Vertical Freq [Hz]      => [%d]\n",vfreq);
	HDMI20_INFO("  Horizontal Freq [Hz]    => [%d]\n",hfreq);
	HDMI20_INFO("  Pixel Clock Freq [kHz]  => [%d]\n",(unsigned int)v.pixel_clk);
	/** Refresh rate [0.01Hz] */
	HDMI20_INFO("  Refresh Rate [0.01Hz]   => [%d]\n",(unsigned int)v.refresh_rate);
	/** Interlaced */
	HDMI20_INFO("  Is Interlaced           => [%d]\n",v.interlaced);
	/** Vertical offset */
	HDMI20_INFO("  Vertical offset         => [%d]\n",v.voffset);
	/** Vertical active */
	HDMI20_INFO("  Vertical Active         => [%d]\n",v.vactive);
	/** Vertical total */
	HDMI20_INFO("  Vertical Total          => [%d]\n",v.vtotal);
	/** Horizontal offset */
	HDMI20_INFO("  Horizontal Offset       => [%d]\n",v.hoffset);
	/** Horizontal active */
	HDMI20_INFO("  Horizontal Active       => [%d]\n",v.hactive);
	/** Horizontal total */
	HDMI20_INFO("  Horizontal Total        => [%d]\n",v.htotal);
	HDMI20_INFO("[Audio Status]\n");
	HDMI20_INFO("  Coding Type             => [0x%08x]\n", a.coding_type);
	HDMI20_INFO("  Channel Count           => [0x%08x]\n", a.channel_count);
	HDMI20_INFO("  Sample Frequency        => [0x%08x]\n", a.sample_frequency);
	HDMI20_INFO("  Sample Size             => [0x%08x]\n", a.sample_size);
	HDMI20_INFO("  Coding Extension        => [0x%08x]\n", a.coding_extension);
	HDMI20_INFO("  Channel Allocation      => [0x%08x]\n", a.channel_allocation);
	HDMI20_INFO("  Down Mix Inhibit        => [0x%08x]\n", a.down_mix_inhibit);
	HDMI20_INFO("  Level Shift Value       => [0x%08x]\n", a.level_shift_value);

	HDMI20_INFO("[AVI InfoFrame Status]\n");
	/** AVI Y1-0, video format */
	HDMI20_INFO("  [Y1-0] Video format                      => [0x%08x]\n",v.video_format);
	/** AVI A0, active format information present */
	HDMI20_INFO("  [A0] Active Format Information present   => [0x%08x]\n ",v.active_valid);
	/** AVI B1-0, bar valid information */
	HDMI20_INFO("  [B1-0] Bar Valid                         => [0x%08x]\n",v.bar_valid);
	/** AVI S1-0, scan information */
	HDMI20_INFO("  [S1-0] Scan Information                  => [0x%08x]\n ",v.scan_info);
	/** AVI C1-0, colorimetry information */
	HDMI20_INFO("  [C1-0] Colorimetry Information           => [0x%08x]\n ",v.colorimetry);
	/** AVI M1-0, picture aspect ratio */
	HDMI20_INFO("  [M1-0] Picture Aspect ratio              => [0x%08x]\n ",v.picture_ratio);
	/** AVI R3-0, active format aspect ratio */
	HDMI20_INFO("  [R3-0] Active format aspect ratio        => [0x%08x]\n ",v.active_ratio);
	/** AVI ITC, IT content */
	HDMI20_INFO("  [ITC] IT Content                         => [0x%08x]\n",v.it_content);
	/** AVI EC2-0, extended colorimetry */
	HDMI20_INFO("  [EC2-0] Extended Colorimetry             => [0x%08x]\n ",v.ext_colorimetry);
	/** AVI Q1-0, RGB quantization range */
	HDMI20_INFO("  [Q1-0] RGA Quantization Range            => [0x%08x]\n ",v.rgb_quant_range);
	/** AVI SC1-0, non-uniform scaling information */
	HDMI20_INFO("  [SC1-0] Non-uniform scaling information  => [0x%08x]\n ",v.n_uniform_scale);
	/** AVI VIC6-0, video mode identification code */
	HDMI20_INFO("  [VIC6-0] Video mode identification code  => [0x%08x]\n ",v.video_mode);
	/** AVI PR3-0, pixel repetition factor */
	HDMI20_INFO("  [PR3-0] Picel Repetition Factor          => [0x%08x]\n ",v.pixel_repetition);
	/** AVI, line number of end of top bar */
	HDMI20_INFO("  [AVI] Line number of end of top bar      => [0x%08x]\n",v.bar_end_top);
	/** AVI, line number of start of bottom bar */
	HDMI20_INFO("  [AVI] Line number of start of bottom bar => [0x%08x]\n ",v.bar_start_bottom);
	/** AVI, pixel number of end of left bar */
	HDMI20_INFO("  [AVI] Pixel number of end of left bar    => [0x%08x]\n",v.bar_end_left);
	/** AVI, pixel number of start of right bar */
	HDMI20_INFO("  [AVI] Pixel number of start of right bar => [0x%08x]\n ",v.bar_start_right);

}

static int __HDMI20_Spin_Init(void *handler)
{
	//spin_lock_init((spinlock_t *)handler);
	return 0;
}

static int __HDMI20_Spin_IRQ_Lock(void *handler, unsigned long *flags)
{
	//spin_lock_irqsave((spinlock_t *)handler, flags);
	return 0;
}

static int __HDMI20_Spin_IRQ_UnLock(void *handler, unsigned long flags)
{
	//spin_unlock_irqrestore((spinlock_t *)handler, flags);
	return 0;
}



static void __HDMI20_HAL_Rx_Operation_Audio_Change(UINT8 port)
{
	/* Step 1. Port defence code */
	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	if(gHDMI20RxHandler[port].ctrl.bsp_read(0x208) & 0x80000000){
		if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == 0x1000)HDMI20_AUDIO("Notice [%d] : Audio PLL Lock Ok\n", port);

		HDMI20_HAL_Rx_Set_Audio_Configure(port, HDMI20_HAL_IsSCDCvalueUD(port));
		/* Re-initialize Audio FIFO */
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFB8, 0x1F);
		hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);
		gHDMI20RxHandler[port].audio_change = 0;

		HDMI20_HAL_Rx_Update_AudioCtsNparam(port, 0);

		/* Added 2014/08/04 taejun.lee */
		HDMI20_HAL_Rx_Get_AudioInfo(port);
	}
	else{
		HDMI20_AUDIO("Notice [%d] : Waiting for AUDIO PLL Lock\n", port);
	}

}

static void __HDMI20_HAL_Rx_Operation_AKSV_Change(UINT8 port)
{
	/* Step 1. Port defence code */
	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	HDMI20_VIDEO("Notice [%d] : MainThread AKSV Change detected\n", port);
	gHDMI20RxHandler[port].aksv_change = 0;

	/* Reset Audio Clock & FIFO */
	gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, 0x10);
	gHDMI20RxHandler[port].ctrl.bsp_write(0xFB8, 0x1F);
	hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);

	//__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
	//gHDMI20RxHandler[port].ctrl.stable_cnt = 0;

}

static void __HDMI20_HAL_Rx_Operation_Video_Change(UINT8 port)
{
	/* Step 1. Port defence code */
	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	HDMI20_VIDEO("Notice [%d] : VIDEO Change detected. stable_cnt[%d]\n", port, gHDMI20RxHandler[port].ctrl.stable_cnt);
	/* Very Important to put video_change on front of Update Timing Info 
	 * video_change flag might get UP on msleep inside of reset_sync_position*/
	gHDMI20RxHandler[port].video_change = false;

	__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
	gHDMI20RxHandler[port].ctrl.stable_cnt = 0;

	if((gHDMI20RxHandler[port].hdcp22_ists_change != 0)&&( gHDMI20RxDevControler[HDMI20__SURGE_DETECTOR_ON].value >0)){
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 2889){	
			HDMI20_VIDEO("Warning %d : Surge insertion on HDCP22 RESET detected at Video interrupt!\n", port);

			if(gHDMI20RxHandler[port].gWasHDCP22Written > 0){
				HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
				HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, port);
			}
		}
		gHDMI20RxHandler[port].hdcp22_ists_change = 0;
		gHDMI20RxHandler[port].hdcp22_auth_change = 0;
	}

	HDMI20_ResetDataPacketBuffer(VSI, port);
	HDMI20_ResetDataPacketBuffer(H14VSI ,port);
	HDMI20_ResetDataPacketBuffer(HFVSI ,port);
	HDMI20_ResetDataPacketBuffer(DOLBYVSI ,port);
	HDMI20_ResetDataPacketBuffer(AVI, port);
	HDMI20_ResetDataPacketBuffer(HDR, port);
	HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, port);
}



static void __HDMI20_HAL_Rx_Operation_TMDS_Change(UINT8 port, int isforceSet)
{
	int y;

	/* Step 1. Port defence code */
	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	HDMI20_VIDEO("Notice [%d] : TMDS Change detected. Stable cnt[%d]\n", port, gHDMI20RxHandler[port].ctrl.stable_cnt);
	gHDMI20RxHandler[port].video_change = 0; // Disable VideoChange Sequence on TMDS&VIDEO both change
	gHDMI20RxHandler[port].tmds_change = false;

	HDMI20_ResetDataPacketBuffer(HDR, port);
	HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_VTEM, port);

	if((gHDMI20RxHandler[port].ctrl.stable_cnt >= gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value)||(gHDMI20RxHandler[port].phyLostCnt > gHDMI20RxDevControler[HDMI20__PHY_LOST_TIMEOUT].value) ||(isforceSet)){
		HDMI20_VIDEO("Notice [%d] : TMDS Change on stable Video Cnt.\n", port);
		gHDMI20RxHandler[port].locking_time = 0;
		gHDMI20RxHandler[port].phy_rst_request = 1;

		/* Clear Timing Info */
		HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 1, __L__);
		__HDMI20_HAL_Rx_ResetSyncPosition(port, HDMI20_SYNOPSYS_CEA_RST_PIN_UP, __L__);
		gHDMI20RxHandler[port].ctrl.stable_cnt = 0;

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1219){
			gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);

			/* Inform HDCP2.2 to reset */
			if((gHDMI20RxHandler[port].gWasHDCP22Written > 0)){
				HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
			}
		}
		else{
			HDMI20_HAL_Rx_LinkVideoReset(port, 0, __L__);
			gHDMI20RxHandler[port].isManualSyncMode = 0;
			if(gHDMI20RxHandler[port].gWasHDCP22Written > 0){
				HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
			}
		}

		/* Reset Audio Clock & FIFO */
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, 0x10);
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFB8, 0x1F);
		hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);
	}
	else{
		#if 0
		/* Inform HDCP2.2 to reset : CTS Test SW WA */
		if(gHDMI20RxHandler[port].gWasHDCP22Written > 0){
			HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
		}
		#endif

		/* Get New Data Packet */
		hdmi_rx_ctrl_packet_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);
		for(y=0;y<PACKET_MAXNUM;y++){
			/* Even though this was opened, it will eventually be closed on Data packet ISR */
			HDMI20_HAL_Packet_Store((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, dataPacketNum[y], 1);
		}

		/* Reset Audio Clock & FIFO */
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, 0x10);
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFB8, 0x1F);
		hdmi_rx_ctrl_audio_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl);
	}
}

static int __HDMI20_HAL_DBG_PrintDevController(HDMI20_DEV_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI20__DEV_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI20__DEV_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI20RxDevControler[i].index, gHDMI20RxDevControler[i].value, gHDMI20RxDevControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI20RxDevControler[index].index, gHDMI20RxDevControler[index].value, gHDMI20RxDevControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

static int __HDMI20_HAL_DBG_PrintDevAudController(HDMI20_DEV_AUD_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Aud Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI20RxDevAudControler[i].index, gHDMI20RxDevAudControler[i].value, gHDMI20RxDevAudControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev Aud Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI20RxDevAudControler[index].index, gHDMI20RxDevAudControler[index].value, gHDMI20RxDevAudControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI20_HAL_IsManualSyncSet(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 data;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;;
		}

		data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
		data &= (0x000000FF);

		if(data > 0){
			ret = 1;
		}
		else{
			ret = 0;
		}

	}while(0);

	return ret;
}

int HDMI20_HAL_ClearManualSyncSetting(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 data;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;;
		}

		gHDMI20RxHandler[port].manualSync4KVfreqHist = 0;
		gHDMI20RxHandler[port].manualSync4KHoriHist = 0;
		gHDMI20RxHandler[port].manualSyncVICHist = 0;
		
		data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
		data &= (~0x000000FF);
		gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
		gHDMI20RxHandler[port].ctrl.bsp_write(0x404, 0x0);

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI20_HAL_Check5VLevelInfo(int port, int *pValue, int isReal)
{
	int ret = 0;
	UINT32 reg5Vvalue = 0;
	UINT32 currentTime;
	UINT32 totalDownTime = gHDMI20RxDevControler[HDMI20__TIME_OF_HPD_DOWN_ON_RESTART_HPD].value + gAdditionalHpdLowDuration;


	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			*pValue = 0;
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__FORCE_5V_UP].value){
			*pValue = 1;
			ret = RET_OK;
			break;
		}

		currentTime = jiffies_to_msecs(jiffies);


		if((currentTime - gHDMI20RxHandler[port].restartHPDTimeStamp <= totalDownTime)\
				&& (gHDMI20RxHandler[port].restartHpdFlagUp == true)){

			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1450){
				HDMI20_DBG("DBG %d : Force 5V down to make HPD/Rxsense Down from MW request. Stamp[%d]/CurrTime[%d]\n",port, gHDMI20RxHandler[port].restartHPDTimeStamp, currentTime);	
			}
		}
		else{
			if(gHDMI20RxHandler[port].restartHpdFlagUp == true){
				if((currentTime - gHDMI20RxHandler[port].restartHPDTimeStamp > totalDownTime)){
					HDMI20_INFO("Notice %d : Finish Force 5V down for HPD/Rxsense Down. Stamp[%d]/CurrTime[%d]\n",port,  gHDMI20RxHandler[port].restartHPDTimeStamp, currentTime);
					gHDMI20RxHandler[port].restartHpdFlagUp  = false;

				}
				else{
					HDMI20_ERROR("ERROR %d : Critical! Un-expected state!!! Please contact won.hur@lge.com for this issue!!!!!!\n", port);
					HDMI20_ERROR("ERROR %d : currTime[%d]/stamp[%d]/flag[%d]/5V[%d]\n", port, currentTime, gHDMI20RxHandler[port].restartHPDTimeStamp, gHDMI20RxHandler[port].restartHpdFlagUp, reg5Vvalue);
				}
			}
		}

		reg5Vvalue= gHDMI20RxHandler[port].top_read(HDMI20_RX_5V_ADDR);
		reg5Vvalue &= HDMI20_RX_5V_BIT;

		if(isReal == 1){
			*pValue = reg5Vvalue;
		}
		else{
			if(gHDMI20RxHandler[port].hdmiDisabled > 0){
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1450){
					HDMI20_DBG("DBG %d : HDMI Disabled\n", port);	
				}

				*pValue = 0;
			}
			else{
				if(gHDMI20RxHandler[port].restartHpdFlagUp == true){
					*pValue = 0;
				}
				else{
					*pValue = reg5Vvalue;
				}
			}
		}

	} while(0);

	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1451){
		HDMI20_DBG("DBG %d : 5V Level => [%s]\n",port, *pValue?"HIGH":"LOW");	
	}

	return ret;
}

int HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_T type, int port)
{
	int ret = RET_ERROR;
	UINT32 data;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if((unsigned int)gHDMI20RxHandler[port].ipcmem.hwAddr == 0){
			HDMI20_ERROR("User memory not initiated yet\n");
			break;
		}

		if(gHDMI20RxHandler[port].ipcmem.pSwAddr == NULL){
			HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
			break;
		}


		if(type >= HDMI20_HAL_IPC_MAXNUM){
			HDMI20_ERROR("Unknown IPC type [0x%08x] \n", type);
			break;
		}

		HDMI20_INFO("Notice %d : IPC Send to KADP. Type [0x%08x]\n", port, type);

		/* Check User Data */
		data = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].ipcmem.pSwAddr)));	

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1166) {
			HDMI20_DBG("DBG %d : ipcmem.pSwAddr[0x%p] / HW Addr[0x%p] / Size[0x%08x]\n",port, (void *)gHDMI20RxHandler[port].ipcmem.pSwAddr, (void *)gHDMI20RxHandler[port].ipcmem.hwAddr, gHDMI20RxHandler[port].ipcmem.size);

		}

		if((data & type) != type){
			// Initiate ESM

			data |= type;
			*((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].ipcmem.pSwAddr)) = data;
		}

		ret = RET_OK;
	}while(0);

	return ret;
}


int HDMI20_HAL_ConnectCable(int port, int bOnOff)
{
	int ret = RET_OK;
	UINT32 data;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return RET_ERROR;
	}

	if(gHDMI20Thread.stamp == 0){
		HDMI20_WARN("Warning %d : Connect Cable was called without MAIN THREAD operation\n", port);
		return RET_ERROR;
	}

	if(gHDMI20RxHandler[port].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return RET_ERROR;
	}

	#if 0
	if(gHDMI20RxHandler[port].restartHpdFlagUp == true){
		HDMI20_VIDEO("Notice %d : ConnectCable Called, but Restart HPD is in progress. HPD low/RxSense LOW time for amount of unit time(%d)\n", port, gHDMI20RxDevControler[HDMI20__TIME_OF_HPD_DOWN_ON_RESTART_HPD].value);
		gHDMI20RxHandler[port].is5Vconnected = 0;
		return RET_OK;
	}
	#endif

	HDMI20_PHY_InitiateTCSHist(port);

	gHDMI20RxHandler[port].isDolbyHDR = (int)HDMI_DOLBY_STATE_OFF;

	gHDMI20RxHandler[port].allm_recieve_time = 0;
	gHDMI20RxHandler[port].isAllmMode = 0;
	/* Clear TCS data */
	HDMI20_PHY_Update_TMDS_TCS_Value(port, 1);

	/* Clear Link Phy Locked flag */
	HDMI20_PHY_CheckLinkPhyLock(port, 1);

	/* Clear HDMI Host Diagnosis Error */
	HDMI20_HAL_ClearHDMIHostError(port, LX_HDMI20_ERROR_MAXNUM);

	/* Clear Deep Color settings */
	HDMI20_HAL_UpdateDCMMode(port, 1, 1);

	gHDMI20RxHandler[port].isLinkInitiated = 0;

	HDMI20_AUDIO("Cnct cable : port(%d) ARCmode(%d)", port, gHDMI20RxHandler[port].isAudioARCMode);

	/* This was originally in Disconnect sequence, but had to move this to upper part.. because sometimes cable-connect sequence is called
	 * even on cable disconnection */
	gHDMI20RxHandler[port].ctrl.isMute = 0;

	gHDMI20RxHandler[port].isHDCP14 = 0;
	gHDMI20RxHandler[port].isHDCP22 = 0;
	gHDMI20RxHandler[port].isHDCP22Ncap = 0;

	gHDMI20RxHandler[port].isScdcUD = 0;

	gHDMI20RxHandler[port].ctrl.stable_cnt = 0;

	HDMI20_HAL_UpdateTimingInfo((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, 1, __L__);
	__HDMI20_HAL_Rx_InitiateHDMI20Data(port, 1);
	HDMI20_HAL_ClearChangeFlags(port);


	if(bOnOff){
		HDMI20_INFO("HDMI2.0 Port[%d] Cable Connect sequence. \n", port);

		if(gHDMI20RxDevControler[HDMI20__HPD_UP_ON_5V].value > 0){
			__HDMI20_HAL_Rx_Set_EnableHPD(port, 1, 1, __L__);
		}

		gHDMI20RxHandler[port].cable_connect_time = jiffies_to_msecs(jiffies);

		/* Audio Mute */
		HDMI20_HAL_Rx_Set_AudioReset(port);
		
		//__HDMI20_HAL_Rx_InitiateHDMI20Data(port, 1);
		gHDMI20RxHandler[port].tmds_change = 1;

		gHDMI20RxHandler[port].is5Vconnected = 1;
		gHDMI20RxHandler[port].connect_request = 1;
		gHDMI20RxHandler[port].phyLostCnt = 0;
		gHDMI20RxHandler[port].isTimingInvalid = 0;
		
		gHDMI20RxHandler[port].isAudioMute = 1;
		gHDMI20RxHandler[port].isAudioMuteControl = 1;
		gHDMI20RxHandler[port].audioIrqFifoErrCnt = 0;
	}
	else{
		HDMI20_INFO("HDMI2.0 Port[%d] Cable Dis-connect sequence. \n", port);

		data = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);
		data |= (0x00010000);
		gHDMI20RxHandler[port].ctrl.bsp_write(0xb4, data);

		gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_TIME].value = gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_INIT_TIME].value;	

		/* Audio Mute */
		HDMI20_HAL_Rx_Set_AudioReset(port);
		HDMI20_Rx_Audio_Path_InthwUnmask(port);
	
		/* Reset HDCP */
		/* Needs a full reset including HDCP1.4 */
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, 0xFFFF);
		__HDMI20_HAL_Rx_Set_EnableHPD(port ,0, 1, __L__);

		gHDMI20RxHandler[port].ctrl.bsp_write(0x808, 0x0);

		/* Needs a full reset including HDCP1.4 */
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, 0xFFFF);

		gHDMI20RxHandler[port].is5Vconnected = 0;

		gHDMI20RxHandler[port].phyLostCnt = 0;
		gHDMI20RxHandler[port].isTimingInvalid = 0;

		gHDMI20RxHandler[port].phyTCSDone = 0;

		if(gHDMI20RxDevControler[HDMI20__ENABLE_PDB_CONTROL_ON_CONNECT].value > 0){
			HDMI20_PHY_ControlPhyPDB(port, 0);
		}
		
		gHDMI20RxHandler[port].countOf6GHpdTgSwWa = gHDMI20RxDevControler[HDMI20__HPD_TG_ON_6G_297].value;
	}

	return ret;
}


void HDMI20_HAL_Rx_LinkVideoReset(int port, int mode, int callerId)
{
	int ret;
	UINT32 hpd_value = 0;
	UINT32 data = 0;
	UINT32 localVideoMuteColor_B0;
	UINT32 localVideoMuteColor_B4;

	if(mode){
		HDMI20_INFO("Link Video Main-Reset on port[%d], Caller[%d]\n", port, callerId);
	}
	else{
		HDMI20_INFO("Link Video Soft-Reset on port[%d], Caller[%d]\n", port, callerId);
	}

	__HDMI20_HAL_SetPVOMode(port, gHDMI20RxDevControler[HDMI20__USE_PVO_MODE_FOR_LINK].value);

	gHDMI20RxHandler[port].isLinkInitiated = 1;

	HDMI20_HAL_Rx_SetLocalVideoMute(port, 1, 1, __L__);

	/* Audio Mute */
	HDMI20_HAL_Rx_Set_AudioReset(port);

	hpd_value = gHDMI20RxHandler[port].ctrl.bsp_read(0x0);
	/* Save Local Video Mute Color */
	localVideoMuteColor_B0 = gHDMI20RxHandler[port].ctrl.bsp_read(0xb0);
	localVideoMuteColor_B4 = gHDMI20RxHandler[port].ctrl.bsp_read(0xb4);

	if(mode){
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, 0xFFFF);
	}
	else{
		gHDMI20RxHandler[port].ctrl.bsp_write(0xFF0, gHDMI20RxDevControler[HDMI20__LINK_REG_0XFF0_RESET_VALUE_0].value);
	}



	/* Restore Local Video Mute Color */
	gHDMI20RxHandler[port].ctrl.bsp_write(0xb0, localVideoMuteColor_B0);
	gHDMI20RxHandler[port].ctrl.bsp_write(0xb4, localVideoMuteColor_B4);
	
	if(	gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value > 0){
		msleep(gHDMI20RxDevControler[HDMI20__LINK_RESET_DELAY_TIME].value);
	}

	/* HDCP */
	ret = hdmi_rx_ctrl_hdcp_config((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl,(const struct hdmi_rx_ctrl_hdcp *)&gHDMI20RxHandler[port].hdcp);
	if( ret <0 ) { HDMI20_ERROR("Error opening HDMI20 port[%d] hdcp 1.4[%d]\n", port, ret); }

	/* HDCP1.4 Set DDC to 100Khz */
	gHDMI20RxHandler[port].ctrl.bsp_write(0xc4, gHDMI20RxDevControler[HDMI20__LINK_REG_0XC4_HDCP_BCAP].value);


	ret = hdmi_rx_ctrl_config((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, gHDMI20RxHandler[port].port);
	if( ret <0 ) { HDMI20_ERROR("Error on HDMI20 port[%d] initial configuration[%d]\n",port, ret); }

	gHDMI20RxHandler[port].ctrl.bsp_write(0x080, gHDMI20RxDevControler[HDMI20__LINK_REG_0X80_HDMI_MODE_RECOVER].value);
	gHDMI20RxHandler[port].ctrl.bsp_write(0x16C, gHDMI20RxDevControler[HDMI20__LINK_REG_0X16C_HDMI_VERTICAL_TIMING].value);
	gHDMI20RxHandler[port].ctrl.bsp_write(0x140, gHDMI20RxDevControler[HDMI20__LINK_REG_0X140_HA_THRESHOLD].value);	

	/* Auto detect VS, HS polarity : Enable Auto sync detect */
	gHDMI20RxHandler[port].ctrl.bsp_write(0x90, 0x14);

	if(gHDMI20RxHandler[port].gWasHDCP22Written >= 1){
		HDMI20_VIDEO("On link reset with [HDCP2.2 enable][%d]/[%d]\n", gHDMI20RxHandler[port].gWasHDCP14Written, gHDMI20RxHandler[port].gWasHDCP22Written);

		if(gHDMI20RxHandler[port].gWasHDCP14Written >= 1){
			gHDMI20RxHandler[port].ctrl.bsp_write(0xc0, 0x01000001);
		}
		else{
			gHDMI20RxHandler[port].ctrl.bsp_write(0xc0, 0x01000000);
		}
		gHDMI20RxHandler[port].ctrl.bsp_write(0x81c, gHDMI20RxDevControler[HDMI20__LINK_REG_FOR_0X81C_HDCP_OVERRID].value);
	}
	else if(gHDMI20RxHandler[port].gWasHDCP14Written >= 1){
		HDMI20_VIDEO("Link Video reset with [HDCP1.4 enable][%d]/[%d]\n", gHDMI20RxHandler[port].gWasHDCP14Written, gHDMI20RxHandler[port].gWasHDCP22Written);
		gHDMI20RxHandler[port].ctrl.bsp_write(0xc0, 0x01000001);
		/* Make sure to change this value to 0x0 when HDCP2.2 is ready */
		gHDMI20RxHandler[port].ctrl.bsp_write(0x81c, 0x00410002);
	}
	else{
		// Test mode
		gHDMI20RxHandler[port].ctrl.bsp_write(0xc0, 0x01000000);
		gHDMI20RxHandler[port].ctrl.bsp_write(0x81c, 0x2);
	}

	/* Initiate Data Packet Buffer */
	HDMI20_ResetDataPacketBuffer(hdmi_rx_ctrl_packet_cnt, port);
	HDMI20_HAL_Rx_ResetEMPacketBuffer(HDMI20_EMPACKET_MAXNUM, port);

	/* Set DCM Auto Detect */
	gHDMI20RxHandler[port].ctrl.bsp_write(0x0A8, gHDMI20RxDevControler[HDMI20__LINK_REG_0XA8_GCP_CTRL].value);

	/* Restore HPD*/
	gHDMI20RxHandler[port].ctrl.bsp_write(0x0, hpd_value);

	/* Enable AVMute */
	data = gHDMI20RxHandler[port].ctrl.bsp_read(0x300);
	data = data | 0x00008000;
	data &= (~0x00000020); // T7 HDR
	gHDMI20RxHandler[port].ctrl.bsp_write(0x300, data);


	/* EM Packet Parsing for LINK Reserved PDEC */
	if(gHDMI20RxDevControler[HDMI20__ENABLE_RESERVE_PDEC_PARSE].value > 0){
		data = gHDMI20RxHandler[port].ctrl.bsp_read(0x300);
		data = data | 0x40000000;
		gHDMI20RxHandler[port].ctrl.bsp_write(0x300, data);

		gHDMI20RxHandler[port].ctrl.bsp_write(0x900, gHDMI20RxDevControler[HDMI20__RESERVE_PDEC_PARSE_HEADER].value);
	}
	else{
		data = gHDMI20RxHandler[port].ctrl.bsp_read(0x300);
		data = data & (~0x40000000);
		gHDMI20RxHandler[port].ctrl.bsp_write(0x300, data);
	}

	/* 2018/08/16 : Set Audio Configuration */
	HDMI20_HAL_Rx_Set_Audio_Configure(port, HDMI20_HAL_IsSCDCvalueUD(port));

	/* Init SCDC */
	gHDMI20RxHandler[port].ctrl.bsp_write(0x800, 0x1F11);
	gHDMI20RxHandler[port].ctrl.bsp_write(0x860, 0xABCDEF01);
	gHDMI20RxHandler[port].ctrl.bsp_write(0x808, 0x1);
	gHDMI20RxHandler[port].ctrl.bsp_write(0x80C, 0x3FF0C15C);
}

static UINT32 __HDMI20_HAL_Rx_VICcodeToVfreqConversion(UINT32 vicCode)
{
	int ret = RET_ERROR;
	UINT32 _vc;

	do{
		/* Get VIC Code */
		_vc = vicCode;


		if((_vc == 60)||(_vc == 65)|| (_vc == 32)||(_vc == 72)||(_vc == 79)||(_vc == 86)||(_vc == 93)||(_vc == 103)||(_vc == 98)){
			/* Field Rate Low : 24Hz */
			ret = 240;
		}
		else if((_vc == 61)||(_vc == 66)|| (_vc == 33)||(_vc == 73)||(_vc == 80)||(_vc == 87)||(_vc == 94)||(_vc == 104)||(_vc == 99)){
			/* Field Rate Low : 25Hz */
			ret = 250;
		}
		else if((_vc == 62)||(_vc == 67)|| (_vc == 34)||(_vc == 74)||(_vc == 81)||(_vc == 88)||(_vc == 95)||(_vc == 105)||(_vc == 100)){
			/* Field Rate Low : 30Hz */
			ret = 300;
		}
		else if((_vc == 17)||(_vc == 18)|| (_vc == 19)||(_vc == 68)||(_vc == 20)||(_vc == 21)||(_vc == 22)||(_vc == 23)||(_vc == 24)||(_vc == 25)||(_vc == 26)||\
				(_vc == 27)||(_vc == 28)||(_vc == 29)||(_vc == 30)||(_vc == 31)||(_vc == 75)||(_vc == 37)||(_vc == 38)||(_vc == 39)||(_vc == 82)||(_vc == 89)||\
				(_vc == 96)||(_vc == 106)||(_vc == 101)){
			
			/* Field Rate Low : 50Hz */
			ret = 500;
		}
		else if((_vc == 1)||(_vc == 2)|| (_vc == 3)||(_vc == 4)||(_vc == 69)||(_vc == 5)||(_vc == 6)||(_vc == 7)||(_vc == 8)||(_vc == 9)||(_vc == 10)||\
				(_vc == 11)||(_vc == 12)||(_vc == 13)||(_vc == 14)||(_vc == 15)||(_vc == 16)||(_vc == 76)||(_vc == 35)||(_vc == 36)||(_vc == 83)||(_vc == 90)||\
				(_vc == 97)||(_vc == 107)||(_vc == 102)){
			
			/* Field Rate Low : 50Hz */
			ret = 600;
		}
		else {
			ret = 0;
		}
	} while(0);

	return ret;
}


static void __HDMI20_HAL_Rx_ResetSyncPosition(UINT8 port, HDMI20_SYNOPSYS_CEA_RST_MODE_T mode, UINT32 caller_id)
{
	UINT32 data;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("ERR %d : Prevent Error. Non existing port[%d]\n", port, port);
		return;
	}

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("ERR %d : Port [%d] number exceeded [%d].\n", port, port, HDMI20_NUM_OF_RX_PORTS);
		return;
	}


	/* No operation on PVO mode */
	if(__HDMI20_HAL_IsPVOMode(port) >= 0){
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1313){
			HDMI20_DBG("DBG %d : CEA Reset Called but ignore due to Link on PVO mode\n", port);
		}

		gHDMI20RxHandler[port].isHDCP22Ncap = 0;
		
		return;
	}

	if(gHDMI20RxDevControler[HDMI20__FORCE_FULL_RESET_ON_CEA_VIDEO_RST].value > 0){
		if(mode == HDMI20_SYNOPSYS_CEA_RST_PIN_UP){
			return;
		}
		else{
			HDMI20_VIDEO("Notice %d : Forced CEA video full reset\n", port);
			mode = HDMI20_SYNOPSYS_CEA_RST_FULL;
		}
	}

	data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
	data &= (~0x00030000); // [17:16]
	data |= gHDMI20RxDevControler[HDMI20__CEA_RECOVERY_VALUE].value;
	gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);

	switch(mode)
	{
		case HDMI20_SYNOPSYS_CEA_RST_FULL:
			{
				HDMI20_VIDEO("Notice [%d] : CEA Video Reset with [FULL]mode called from [%d]\n", port,caller_id);

				/* HDCP2.2 NCap SW W/A disable */
				gHDMI20RxHandler[port].isHDCP22Ncap = 0;

				data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
				data |= 0x80000000;
				gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);

				HDMI20_VIDEO("Notice [%d] : CEA Video Reset.  Delay[%d] msec\n", port, gHDMI20RxDevControler[HDMI20__CEA_VIDEO_RESET_DELAY].value);
				gHDMI20RxHandler[port].audioFifoErrMuteCnt = 0;
				HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
				gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
				msleep(gHDMI20RxDevControler[HDMI20__CEA_VIDEO_RESET_DELAY].value);
				data &= (~0x80000000);
				gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
			}
			break;

		case HDMI20_SYNOPSYS_CEA_RST_PIN_UP:
			{
				data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);

				if((data & 0x80000000) == 0){
					HDMI20_VIDEO("Notice [%d] : CEA Video Reset with [PIN UP]mode called from [%d]\n", port,caller_id);
					data |= 0x80000000;
					gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
				}
				else{
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3131){
						HDMI20_DBG("Notice %d : No pin up for CEA Video RESET because level is already high[0x%08x]\n", port, data);
					}
				}
			}
			break;
		case HDMI20_SYNOPSYS_CEA_RST_PIN_DOWN:
			{
				/* HDCP2.2 NCap SW W/A disable */
				gHDMI20RxHandler[port].isHDCP22Ncap = 0;

				HDMI20_VIDEO("Notice [%d] : CEA Video Reset with [PIN DOWN]mode called from [%d]\n", port, caller_id);
				data = gHDMI20RxHandler[port].ctrl.bsp_read(0x400);
				data &= (~0x80000000);
				gHDMI20RxHandler[port].ctrl.bsp_write(0x400, data);
			}
			break;
		default :
			break;
	}

	return;
}




/* DBG function for proc status */
void HDMI20_HAL_Rx_PROC_PrintVideo(int port, struct seq_file* m)
{
	int ret;
	int vfreq = 0;
	int hfreq = 0;
	struct hdmi_rx_ctrl_video v = {0};
	struct hdmi_rx_ctrl_audio a = {0};
	HDMI20_HAL_RX_DEVICE_DATA *handler;

	if(((unsigned int)port)>= HDMI20_NUM_OF_RX_PORTS){
		seq_printf(m, "not supported for port[%d]\n", port);
		return;
	}

	handler = (HDMI20_HAL_RX_DEVICE_DATA *)&gHDMI20RxHandler[port];

	if(handler == 0) {
		HDMI20_ERROR("NULL pointer \n");
		return;
	}

	if(handler->initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return;
	}

	ret = hdmi_rx_ctrl_get_video(&handler->ctrl, &v, 4);
	if(ret < 0) {
		if( ret != -ERANGE) {
			HDMI20_ERROR("Error when attempting to achieve video data[%d]\n",  ret);
			return;
		}
		else{
			seq_printf(m, "connected: off (no signal or bad video)\n");
		}
	}
	else
		seq_printf(m, "connected: on\n");

	ret = hdmi_rx_ctrl_get_audio(&handler->ctrl, &a);
	if( ret < 0) {
		HDMI20_AUDIO("Error when attemting to achieve AUDIO data[%d]\n", ret);
		return;
	}


	if((v.pixel_clk == 0)||(v.vtotal == 0)||(v.htotal == 0)){
		vfreq = 0;
	}
	else{
		vfreq = (v.pixel_clk * 1000)/(v.vtotal * v.htotal);
	}

	if((v.pixel_clk == 0)||(v.htotal == 0)){
		hfreq = 0;
	}
	else{
		hfreq = ((v.pixel_clk * 1000) / v.htotal); 					///< Horizontal frequency(100 Hz unit)
	}

	seq_printf(m,
			"device-id: %d\n"
			"stable_cnt: %d (VIDEO Status)\n"
			"timing-invalid: %s (%d)\n"
			"manual-sync-mode: %s (%d)\n\n",
			handler->ctrl.device_id,
			handler->ctrl.stable_cnt,
			(handler->isTimingInvalid)?"yes":"no", handler->isTimingInvalid,
			(handler->isManualSyncMode)?"on":"off", handler->isManualSyncMode
			);

	/** DVI detection status: DVI (true) or HDMI (false) */
	seq_printf(m, "dvi-detection: %s\n", (v.dvi)?"DVI":"HDMI" );

	/** Deep color mode: 24, 30, 36 or 48 [bits per pixel] */
	seq_printf(m, "deep-color-mode: %d bpp\n",v.deep_color_mode);

	/** Pixel clock frequency [kHz] */
	seq_printf(m, "pixel-clock: %d kHz\n",(unsigned int)v.pixel_clk);
	seq_printf(m, "pixel-clock-V: %d Hz\n" ,vfreq);
	seq_printf(m, "pixel-clock-H: %d Hz\n" ,hfreq);

	/** Refresh rate [0.01Hz] */
	seq_printf(m, "refresh-rate: %d (0.01Hz)\n",(unsigned int)v.refresh_rate);

	/** Interlaced */
	seq_printf(m, "interlaced: %s\n\n", (v.interlaced)?"yes":"no");

	/** Vertical offset */
	seq_printf(m, "vertical-offset: %d\n",v.voffset);

	/** Vertical active */
	seq_printf(m, "vertical-active: %d\n",v.vactive);

	/** Vertical total */
	seq_printf(m, "vertical-total: %d\n",v.vtotal);

	/** Horizontal offset */
	seq_printf(m, "horizontal-offset: %d\n",v.hoffset);

	/** Horizontal active */
	seq_printf(m, "horizontal-active: %d\n",v.hactive);

	/** Horizontal total */
	seq_printf(m, "horizontal-total: %d\n\n",v.htotal);


	/* AUDIO Status */
	seq_printf(m, "AIF-CT3-0: 0x%08x (coding type)\n", a.coding_type);
	seq_printf(m, "AIF-CC2-0: 0x%08x (channel count)\n", a.channel_count);
	seq_printf(m, "AIF-SF2-0: 0x%08x (sample frequency)\n", a.sample_frequency);
	seq_printf(m, "AIF-SS1-0: 0x%08x (sample size)\n", a.sample_size);
	seq_printf(m, "AIF-CTX: 0x%08x (coding extension)\n", a.coding_extension);
	seq_printf(m, "AIF-CA7-0: 0x%08x (channel allocation)\n", a.channel_allocation);
	seq_printf(m, "AIF-DM_INH: 0x%08x (down mix inhibit)\n", a.down_mix_inhibit);
	seq_printf(m, "AIF-LSV3-0: 0x%08x (level shift value)\n\n", a.level_shift_value);


	/** AVI Y1-0, video format */
	seq_printf(m, "AVI-Y1-0: 0x%08x (Video format)\n", v.video_format);

	/** AVI A0, active format information present */
	seq_printf(m, "AVI-A0: 0x%08x (Active Format Information present)\n", v.active_valid);

	/** AVI B1-0, bar valid information */
	seq_printf(m, "AVI-B1-0: 0x%08x (Bar Valid)\n", v.bar_valid);

	/** AVI S1-0, scan information */
	seq_printf(m, "AVI-S1-0: 0x%08x (Scan Information)\n", v.scan_info);

	/** AVI C1-0, colorimetry information */
	seq_printf(m, "AVI-C1-0: 0x%08x (Colorimetry Information)\n",v.colorimetry);

	/** AVI M1-0, picture aspect ratio */
	seq_printf(m, "AVI-M1-0: 0x%08x (Picture Aspect ratio)\n", v.picture_ratio);

	/** AVI R3-0, active format aspect ratio */
	seq_printf(m, "AVI-R3-0: 0x%08x (Active format aspect ratio)\n", v.active_ratio);

	/** AVI ITC, IT content */
	seq_printf(m, "AVI-ITC: 0x%08x (IT Content)\n", v.it_content);

	/** AVI EC2-0, extended colorimetry */
	seq_printf(m, "AVI-EC2-0: 0x%08x (Extended Colorimetry)\n", v.ext_colorimetry);

	/** AVI Q1-0, RGB quantization range */
	seq_printf(m, "AVI-Q1-0: 0x%08x (RGA Quantization Range)\n", v.rgb_quant_range);

	/** AVI SC1-0, non-uniform scaling information */
	seq_printf(m, "AVI-SC1-0: 0x%08x (Non-uniform scaling information)\n", v.n_uniform_scale);

	/** AVI VIC6-0, video mode identification code */
	seq_printf(m, "AVI-VIC6-0: 0x%08x (Video mode identification code)\n", v.video_mode);

	/** AVI PR3-0, pixel repetition factor */
	seq_printf(m, "AVI-PR3-0: 0x%08x (Pixel Repetition Factor)\n", v.pixel_repetition);

	/** AVI, line number of end of top bar */
	seq_printf(m, "AVI-LN-END-TB: 0x%08x (Line number of end of top bar)\n", v.bar_end_top);

	/** AVI, line number of start of bottom bar */
	seq_printf(m, "AVI-LN-START-BB: 0x%08x (line number of start of bottom bar)\n", v.bar_start_bottom);

	/** AVI, pixel number of end of left bar */
	seq_printf(m, "AVI-PN-END-LB: 0x%08x (pixel number of end of left bar)\n", v.bar_end_left);

	/** AVI, pixel number of start of right bar */
	seq_printf(m, "AVI-PN-START-RB: 0x%08x (pixel number of start of right bar)\n", v.bar_start_right);

	seq_printf(m, "isDolbyHDR=>[%d]\n", handler->isDolbyHDR);

	seq_printf(m, "Kenerl Driver Date : %d\n", HDMI20_KERNEL_DRIVER_DATE);
	seq_printf(m, "Port[%d] => Dev initiated[%d]\n", handler->ctrl.device_id, handler->initiated);
	seq_printf(m, "LINK IRQ GIC[%d], TOP IRQ GIC[%d]\n", handler->irq, handler->top_irq);
	seq_printf(m, "Deep Color Mode[%d]\n", handler->currentDCMMode);
	seq_printf(m, " HDCP14Written[%d]/HDCP22Written[%d]\n",handler->gWasHDCP14Written, handler->gWasHDCP22Written);
	seq_printf(m, "AVMuteOnTime[%d], CableConnectedTime[%d], AudioMuteEnableCnt[%d]\n", handler->avmute_on_time, handler->cable_connect_time,handler->audioStandByCnt);
	seq_printf(m, "IsManualSyncMode[%d], RealTMDSCLK[%d], RealPixelCLK[%d]\n", handler->isManualSyncMode, handler->real_tmds_clk, handler->real_pixel_clk);
	seq_printf(m, "RealVFreq[%d], LocalMuteTimer[%d], VtotalBuffer[%d]\n", handler->real_vfreq, handler->localmutetimer, handler->vtotalbuffer);
	seq_printf(m, "isMHL[%d], isARC[%d], isAudioMute[%d], isPhyLocked[%d]\n", handler->isMHLMode, handler->isAudioARCMode, handler->isAudioMute, handler->isPhyLocked);
	seq_printf(m, "is5V[%d], isHPD[%d], isScdcUD[%d], isHDCP22[%d], isHDCP14[%d], isHDCP22Ncap[%d]\n", handler->is5Vconnected, handler->isHPD, handler->isScdcUD, handler->isHDCP22, handler->isHDCP14, handler->isHDCP22Ncap);
	seq_printf(m, "TimingInvalid[%d], HPD_Request[%d],ConnectRequest[%d], EDIDWritten[%d]\n", handler->isTimingInvalid,handler->hpd_request,handler->connect_request,handler->wasEdidWritten);
	seq_printf(m, "PhyInitiatedMode[%d], LockingTime[%d]\n", handler->phyInitiatedMode,handler->locking_time);
	seq_printf(m, "audioStableCnt[%d], audioChMapCnt[%d], audioFifoErrMuteCnt[%d]\n",handler->audioStableCnt,handler->audioChMapCnt,handler->audioFifoErrMuteCnt);
	seq_printf(m, "5VConnectedTime[%d], StableHDCP14[%d], TCSDone[%d], PhyStableCNT[%d]\n", handler->connected5Vtime, handler->stablehdcp14time, handler->phyTCSDone,handler->phy_stable_cnt); 
	seq_printf(m, " TCS DIFF CH0[%d]/CH1[%d]/CH2[%d]\n", handler->phyTCSDiff[0], handler->phyTCSDiff[1],handler->phyTCSDiff[2]);
	seq_printf(m, " TCS MIN CH0[%d]/CH1[%d]/CH2[%d]\n", handler->phyTCSMin[0], handler->phyTCSMin[1],handler->phyTCSMin[2]);
	seq_printf(m, " TCS Max CH0[%d]/CH1[%d]/CH2[%d]\n", handler->phyTCSMax[0], handler->phyTCSMax[1],handler->phyTCSMax[2]);
	seq_printf(m, " HPD INVERSE MODE PORT[%d] => [%d]\n", handler->ctrl.device_id, handler->isHPDInverseMode);
	seq_printf(m, " PHY Exception Case[0x%08x]\n", handler->phyExceptionState);
	seq_printf(m, " IsTimingInfoEmpty =>[%d]\n", HDMI20_HAL_IsTimingInfoEmpty(handler->ctrl.device_id));
	seq_printf(m, " TMDSRangeCurrnet[%d], TMDSRangePrev[%d]\n", gHDMI20RxHandler[handler->ctrl.device_id].phyCurrentTMDSExceptionRange, gHDMI20RxHandler[handler->ctrl.device_id].phyPrevTMDSExceptionRange);
	seq_printf(m, " TMDSRangeCurrnet_2[%d], TMDSRangePrev_2[%d]\n", gHDMI20RxHandler[handler->ctrl.device_id].phyCurrentTMDSExceptionRange_2, gHDMI20RxHandler[handler->ctrl.device_id].phyPrevTMDSExceptionRange_2);
	seq_printf(m, " isAllmMode[%d], allmRecieveTime[%d]\n", gHDMI20RxHandler[handler->ctrl.device_id].isAllmMode, gHDMI20RxHandler[handler->ctrl.device_id].allm_recieve_time);



	return;
}

static UINT32 __HDMI20_HAL_Rx_ALED_TOP_Read(UINT32 addr)
{
	UINT32 ret;
	
	if(sAledTop.pSwAddr != NULL){
		ret = (volatile UINT32)(*((UINT32 *)((uintptr_t)sAledTop.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI20_HAL_Rx_ALED_TOP_Write(UINT32 addr, UINT32 data)
{
	volatile UINT32* dest;

	if(sAledTop.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)sAledTop.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}

static int	__HDMI20_HAL_Rx_CatchPC(UINT8 port)
{
	int ret = 0;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_VIDEO("ERR %d : Prevent Error. Non existing port[%d]\n", port, port);
		return ret;
	}

	if(gHDMI20RxHandler[port].dataPacket[SPD][29] == 0x9){
		if(gHDMI20RxHandler[port].isPC == false){
			HDMI20_VIDEO(" Notice [%d] : Detected PC\n", port);
		}

		gHDMI20RxHandler[port].isPC = true;
		ret = 1;
	}
	else{
		if(gHDMI20RxHandler[port].isPC == true){
			HDMI20_VIDEO(" Notice [%d] : Lost Detection of PC\n", port);
		}

		gHDMI20RxHandler[port].isPC = false;
		ret = 0;
	}

	return ret;
}

static int __HDMI20_HAL_Set_HDMI_HostErrorThres(LX_HDMI20_ERROR_SETTING_T *pData, int size)
{
	int ret = RET_ERROR;

	do{
		if(gHDMI20RxDevControler[HDMI20__USE_MW_HOSTERROR_CTRL].value > 0){
			if(pData == NULL) {
				HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
				break;
			}

			if(size > (sizeof(LX_HDMI20_ERROR_SETTING_T) * LX_HDMI20_ERROR_MAXNUM)) {
				HDMI20_ERROR("Error! Size[%d] is over limit[%zu]\n", size, (sizeof(LX_HDMI20_ERROR_SETTING_T) * LX_HDMI20_ERROR_MAXNUM));
				break;
			}

			/* Get Data */
			if( copy_from_user(&kdrvHDMI20ErrorThres, (void __user *)pData, size)){
				HDMI20_ERROR("Cannot copy HDMI20 Error Init thres data structure from user\n");
				break;
			}
		}
		/* OK */
		ret = RET_OK;
	} while(0);

	return ret;
}

static int __HDMI20_HAL_Get_HDMI_HostError(UINT8 port, UINT32 *pData, int size)
{
	int ret = RET_ERROR;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(UINT32)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(UINT32), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		ret = copy_to_user((void __user *)pData, (void *)&gHDMIhostError[port].errorStatus, sizeof(UINT32));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "HDMI_Error", port);
			break;
		}

		/* Clear Error After sending it to user layer */
		gHDMIhostError[port].errorStatus = 0;

		ret = RET_OK;
	} while(0);

	return ret;

}

void HDMI20_HAL_ClearHDMIHostError(UINT8 port, LX_HDMI20_ERROR_TYPE_T type)
{
	int i;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	if(type >= LX_HDMI20_ERROR_MAXNUM){
		memset((void *)&gHDMIhostError[port], 0, sizeof(HDMI20_HOST_DIAGNOSIS_ERROR_T));
	}
	else{
		gHDMIhostError[port].errorStatus &= (~kdrvHDMI20ErrorThres[type].errorVal);
		gHDMIhostError[port].counter[type] = 0;
		gHDMIhostError[port].startTick[type] = 0;
		gHDMIhostError[port].isActive[type] = false;

		if(type == LX_HDMI20_ERROR_CED_ERROR){
			for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				gHDMIhostError[port].cedError[i] = 0;
			}
		}
	}
}

void HDMI20_HAL_PutHDMIHostError(UINT8 port, LX_HDMI20_ERROR_TYPE_T type, int errorStatus)
{
	int ret = 0;
	int i;
	UINT32 currentJiffies = 0;

	if(port >= HDMI20_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
		return;
	}

	if(kdrvHDMI20ErrorThres[type].errorVal == 0){
		/* Do nothing */
		return;
	}

	if((gHDMIhostError[port].errorStatus & kdrvHDMI20ErrorThres[type].errorVal) != 0){
		/* Do nothing if Error flag is already UP*/
		return;
	}

	currentJiffies = jiffies_to_msecs(jiffies);

	switch(type)
	{
		case LX_HDMI20_ERROR_GCP_ERROR:
		{
			if(errorStatus){
				gHDMIhostError[port].counter[type]++;
				
				if(gHDMIhostError[port].isActive[type] == false){
					gHDMIhostError[port].startTick[type] = jiffies_to_msecs(jiffies);
					gHDMIhostError[port].isActive[type] = true;
				}

				/* Check Error Threshold */
				if(kdrvHDMI20ErrorThres[type].param_B <= 1){
					gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
				}
				else{
					if((currentJiffies - gHDMIhostError[port].startTick[type]) >= kdrvHDMI20ErrorThres[type].param_A * 1000){
						HDMI20_HAL_ClearHDMIHostError(port, type);
					}
					else{
						if(gHDMIhostError[port].counter[type] >= kdrvHDMI20ErrorThres[type].param_B){
							gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
						}
					}
				}
			}
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
			if(gHDMIhostError[port].isActive[type] == false){
					gHDMIhostError[port].startTick[type] = jiffies_to_msecs(jiffies);
					gHDMIhostError[port].isActive[type] = true;
			}
			else{
				if((currentJiffies - gHDMIhostError[port].startTick[type]) >= kdrvHDMI20ErrorThres[type].param_A * 1000){
					HDMI20_HAL_ClearHDMIHostError(port, type);
					ret = HDMI20_PHY_Check_TCSError(port);	
				
					if(ret >= 0){
						if(ret >= kdrvHDMI20ErrorThres[type].param_B){
							gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
						}
					}
				}
			}
		}
		break;
		case LX_HDMI20_ERROR_PHY_LOW_RANGE:
		{
			for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				if(abs(gHDMI20RxHandler[port].phyTCSMax[i] - gHDMI20RxHandler[port].phyTCSMin[i]) <= kdrvHDMI20ErrorThres[type].param_A){
					gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
				}
			}
		}
		break;
		case LX_HDMI20_ERROR_PHY_ABNORMAL:
		{
			for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				
				if(gHDMI20RxHandler[port].phyInitiatedMode){
					if(abs(gHDMI20RxHandler[port].phyTCSResult[i] - gHDMI20RxDevControler[HDMI20__PHY_6G_TCS_ADD_VAL].value ) >= kdrvHDMI20ErrorThres[type].param_A){
						gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
					}
				}
				else{
					if(abs(gHDMI20RxHandler[port].phyTCSResult[i] - gHDMI20RxDevControler[HDMI20__PHY_3G_TCS_ADD_VAL].value ) >= kdrvHDMI20ErrorThres[type].param_A){
						gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
					}
				}
			}
		}
		break;
		case LX_HDMI20_ERROR_CED_ERROR:
		{
			if(gHDMIhostError[port].isActive[type] == false){
					gHDMIhostError[port].startTick[type] = jiffies_to_msecs(jiffies);
					gHDMIhostError[port].isActive[type] = true;

					for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
						gHDMIhostError[port].cedError[i] = HDMI20_HAL_Rx_GetCEDError(port, i);
					}

			}
			else{
				if((currentJiffies - gHDMIhostError[port].startTick[type]) >= kdrvHDMI20ErrorThres[type].param_A * 1000){
					for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
						if(HDMI20_HAL_Rx_GetCEDError(port, i)>= kdrvHDMI20ErrorThres[type].param_B){
							gHDMIhostError[port].errorStatus |= kdrvHDMI20ErrorThres[type].errorVal;
						}
					}

					HDMI20_HAL_ClearHDMIHostError(port, type);
				}
				else{
					for(i=0;i<HDMI20_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
						gHDMIhostError[port].cedError[i] += HDMI20_HAL_Rx_GetCEDError(port, i);
					}
				}
			}
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

int HDMI20_HAL_Rx_GetCEDError(UINT8 port, UINT8 channel)
{
	UINT32 cedError = 0;

	switch(channel)
	{
		case 0:
			if(gHDMI20RxHandler[port].ctrl.bsp_read(0x824) & 0x80000000){
				cedError = ((gHDMI20RxHandler[port].ctrl.bsp_read(0x824) & 0x7FFF0000)>> 16) & 0x00007FFF;
			}
			break;
		case 1:
			if(gHDMI20RxHandler[port].ctrl.bsp_read(0x828) & 0x00008000){
				cedError = (gHDMI20RxHandler[port].ctrl.bsp_read(0x828) & 0x00007FFF);
			}
			break;
		case 2:
			if(gHDMI20RxHandler[port].ctrl.bsp_read(0x828) & 0x80000000){
				cedError = ((gHDMI20RxHandler[port].ctrl.bsp_read(0x828) & 0x7FFF0000)>> 16) & 0x00007FFF;
			}
			break;
		default :
			break;
	}
	
	
	return cedError;
}


int HDMI20_HAL_Get_VrrCurrentVfreq(UINT8 port, UINT16 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;
	UINT32 hvtotal;
	UINT32 vfreq;
	UINT32 vtotal;
	UINT32 htotal;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(UINT16)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(UINT32), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		vtotal = gHDMI20RxHandler[port].ctrl.bsp_read(0x170);
		vtotal &= (0x0000FFFF);

		htotal = gHDMI20RxHandler[port].ctrl.bsp_read(0x14C);
		htotal = htotal >> 16;
		htotal &= (0x0000FFFF);
		
		
		hvtotal = vtotal * htotal;
		
		if((hvtotal != 0)&&(gHDMI20RxHandler[port].isPhyLocked > 0)){
			vfreq = ((gHDMI20RxHandler[port].real_tmds_clk * 1000) / hvtotal);
		}
		else{
			vfreq = 0;
		}

		if (gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 8460) {
			HDMI20_DBG("DBG %d : Vfreq[%d]\n", port, vfreq);
		}

		if(isInternalCall){
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
