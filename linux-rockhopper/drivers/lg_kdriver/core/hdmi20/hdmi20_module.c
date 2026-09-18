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
 *  @author		won.hur
 *  @version	1.0 
 *  @date		2014-05-07
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#if defined(CONFIG_ARM64) && LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0)
#include <linux/of_device.h>
#endif
#include <linux/seq_file.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/dma-mapping.h>
#include "hdmi20_module.h"
#include "hdmi20_drv.h"

#include "./hdmi21_engine/hdmi21_hal_driver.h"
#include "./hdmi21_engine/hdmi21_rx_disland.h"
#include "./hdmi21_engine/hdmi21_rx_phy.h"
#include "./hdmi21_engine/hdmi21_earc_driver.h"

#include "../../chip/o20/hdmi20/hdmi21_cfg_o20.h"
#include "../../chip/e60/hdmi20/hdmi21_cfg_e60.h"
#include "../../chip/o22/hdmi20/hdmi21_cfg_o22.h"
#include "../../chip/m23/hdmi20/hdmi21_cfg_m23.h"
#include "../../chip/o24/hdmi20/hdmi21_cfg_o24.h"
#include "../../chip/o26/hdmi20/hdmi21_cfg_o26.h"


#include "../../chip/o22/hdmi20/o22a0_table_header.h"
#include "../../chip/m23/hdmi20/m23a0_table_header.h"
#include "../../chip/o24/hdmi20/o24a0_table_header.h"
#include "../../chip/o26/hdmi20/o26a0_table_header.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 2020/05/28 : PHY SETTING TABLE for reference
 * 			  : Ver 1.00 
 * 			  : (won.hur) 
 */
#define HDMI20_MODULE_PHY_SET_TABLE_E60B0_VER100_IDX_CNT	(82)

HDMI20_MODULE_PHY_DEFAULT_TABLE_T gHdmi20ModuleE60B0PhyDefaultTable[HDMI20_MODULE_PHY_SET_TABLE_E60B0_VER100_IDX_CNT] =
{
	{"CR_PLL_PDB",0x68,0x02,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{"MAN_CON_SEL",0x68,0x38,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30},
	{"Manual HDMI20_MODE",0x68,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"Manual HDMI21_MODE",0x68,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"SCR_MAN_OFF",0x48,0x88,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08},
	{"EQ_HDMI20_VAL",0x68,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"EQ_DHFG",0x38,0xA8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40},
	{"VBGR",0x68,0x7D,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x16},
	{"EQ_DOHG",0x68,0x39,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{"ODT_FREQ_DIV",0x68,0x5D,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04},
	{"EQ_ICTRL",0x68,0x24,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x61},
	{"IDR",0x48,0x2C,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00},
	{"SUM_DAC_BIAS",0x38,0x59,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33},
	{"PI_SET_MAN_MODE_VAL",0x68,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10},
	{"DR_CLKGEN_CAPENB",0x48,0x01,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10},
	{"RS_MAN_SEL",0x48,0x15,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"EQ_RS_MAN_CH0",0x48,0x16,0x02,0x02,0x02,0x02,0x02,0x02,0x05,0x05},
	{"EQ_RS_MAN_CH1",0x48,0x17,0x02,0x02,0x02,0x02,0x02,0x02,0x05,0x05},
	{"EQ_RS_MAN_CH2",0x48,0x18,0x02,0x02,0x02,0x02,0x02,0x02,0x05,0x05},
	{"EQ_RS_MAN_CH3",0x48,0x19,0x02,0x02,0x02,0x02,0x02,0x02,0x05,0x05},
	{"RS_SCAN_MODE",0x48,0x70,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02},
	{"RS_SCAN_CAL_NUM",0x48,0x6F,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05},
	{"RS_DATA_NUM",0x48,0x74,0x64,0x64,0x64,0x64,0x64,0x64,0x64,0x64},
	{"EQ_CAL_RS_TARGET",0x38,0xDB,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41},
	{"RS_SCAN_PRE",0x48,0x72,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50},
	{"RS_SCAN_MEAS",0x48,0x73,0x96,0x96,0x96,0x96,0x96,0x96,0x96,0x96},
	{"RS_SCAN_LEVEL_A_11",0x48,0x75,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20},
	{"EQ_CS_MAN_CH0",0x38,0xA2,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"EQ_CS_MAN_CH1",0x38,0xA3,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"EQ_CS_MAN_CH2",0x38,0xA4,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"EQ_CS_MAN_CH3",0x38,0xA5,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"ANA_CDR_SEL",0x38,0x5A,0x10,0x10,0x90,0x90,0x90,0x90,0x90,0x90},
	{"FILTER_SEL G1_SEL",0x38,0xF3,0x13,0x13,0x13,0x13,0x13,0x13,0x13,0x13},
	{"G2_SEL",0x38,0xF4,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C},
	{"PHANTOM_MAN_VAL",0x48,0x2E,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"PHANTOM_FIX_MODE",0x48,0x2D,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83},
	{"DR_FILTER",0x48,0x29,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"DR_CLK_INV",0x48,0x04,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00},
	{"I2C_DELTA_CDR_MODE VAL",0x38,0x8C,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00},
	{"DELTA_SCAN2_ADD_VAL",0x38,0x9C,0x06,0x06,0x16,0x16,0x16,0x16,0x16,0x16},
	{"DELTA_ADD_VAL_20 I2C_DELTA_SAM",0x38,0x9B,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x00},
	{"DELTA_SCOPE2",0x38,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90},
	{"DELTA_SCOPE_PLL_MODE2_3",0x38,0x9A,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0x02},
	{"DELTA_MAX_ADJUST",0x38,0x98,0x32,0x32,0x32,0x32,0x32,0x32,0x01,0x01},
	{"TCS_REPEAT_OFF",0x38,0xB9,0x43,0x43,0x40,0x40,0x40,0x40,0x40,0x40},
	{"TCS_ERR_SEL",0x38,0xB8,0xD7,0xD7,0xD7,0xDF,0xDF,0xDF,0xDF,0xDF},
	{"DR_N2",0x48,0x2F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"TCS_ADD_VAL0",0x38,0xBE,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08},
	{"TCS_ADD_VAL1",0x38,0xBF,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"TCS_ADD_VAL2",0x38,0xC0,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"TCS_ADD_VAL3",0x38,0xC1,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
	{"TCS_ADD_VAL4",0x38,0xC2,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03},
	{"DFE_A_B1_B5",0x38,0x5C,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
	{"DFE_N1",0x38,0x5D,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41},
	{"DFE_UPDN_PERIOD",0x38,0x5E,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F},
	{"DFE_UPDN_PERIOD_PRE",0x38,0x5F,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70},
	{"I2C_DFE_ON_MODE_ON DFE_DIG_ON",0x38,0x58,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"SIGN_PATH_B1_ON",0x38,0x57,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"DFE_B1_MINUS DFE_NEW_MODE",0x38,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"EQ_EVAL_TIME2",0x48,0x2B,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"TCS_SCDT MAN_PRE_OPTION",0x38,0xB3,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06},
	{"TCS_BOUNDARY",0x38,0xBA,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{"TCS_PREIOD_SEL TCS_SCOPE",0x38,0xB7,0x81,0x81,0x81,0x81,0x41,0x41,0x41,0x41},
	{"TCS_ERR_LIMIT_BASIC",0x38,0xBD,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0},
	{"FIFO_MODE",0x48,0x06,0x53,0x53,0x53,0x53,0x53,0x53,0x53,0x53},
	{"ERROR_UNIT_SEL",0x48,0xA4,0xA9,0xA9,0xA9,0xA9,0xA9,0xA9,0xA9,0xA9},
	{"REG_TCS_MAN_PRE",0x38,0xB4,0x60,0x60,0x60,0x60,0xFF,0xFF,0xFF,0xFF},
	{"REG_TCS_MAN_MEA_1",0x38,0xB5,0x00,0x00,0x00,0x00,0x0A,0x0A,0x0A,0x0A},
	{"REG_TCS_MAN_MEA_2",0x38,0xB6,0x0A,0x0A,0x0A,0x0A,0xD2,0xD2,0xD2,0xD2},
	{"CED_OPEN_LENGTH",0x38,0xAC,0x43,0x43,0x43,0x43,0x23,0x23,0x23,0x23},
	{"CHK_INFINITE_MODE",0x38,0xAD,0x8F,0x8F,0x8F,0x8F,0x8F,0x8F,0x8F,0x8F},
	{"CED_CHECK_MODE",0x38,0xAB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"CED_ADAPTIVE_PERIOD",0x38,0xBC,0x09,0x09,0x09,0x0D,0x0D,0x0D,0x0D,0x0D},
	{"EQ_FREQ_DIV",0x38,0xED,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06},
	{"CAL_INTEVAL",0x38,0xEF,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50},
	{"DELTA_MODE_PLL0_3",0x38,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{"FRL_MATCH_MAN_VAL",0x48,0x8A,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F},
	{"MAN_ODT50",0x68,0x58,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{"I2C_ODT_HDMI50",0x68,0x59,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C},
	{"RESETB_ALL",0x68,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{"ODT_PDB",0x68,0x48,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11},
	{"CR_PLL_PDB",0x68,0x02,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11},

};



/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern     char*   simple_strtok(char *s, const char *delim, char **save_ptr);
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

extern void v4l2_hdmi20_header_ver_print(struct seq_file *m);

extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];



/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern PHY_REG_TABLE_O22A0 o22a0_phy_reg_table[PHY_REG_MAX_NUM_O22A0];
extern PHY_REG_TABLE_M23A0 m23a0_phy_reg_table[PHY_REG_MAX_NUM_M23A0];
extern PHY_REG_TABLE_O24A0 o24a0_phy_reg_table[PHY_REG_MAX_NUM_O24A0];
extern PHY_REG_TABLE_O26A0 o26a0_phy_reg_table[PHY_REG_MAX_NUM_O26A0];

extern char *hdmi_phy_reg_ver_o22a0;
extern char *hdmi_phy_reg_ver_m23a0;
extern char *hdmi_phy_reg_ver_o24a0;
extern char *hdmi_phy_reg_ver_o26a0;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
char *hdmi_phy_reg_ver = NULL; 


HDMI20_MODULE_CHIP_ADDR_DATA_T gHDMI20ChipRegHandler;
HDMI21_MODULE_CHIP_ADDR_DATA_T gHDMI21ChipRegHandler;


int 	(*HDMI20_Chip_Process_Cmd)(LX_HDMI20_CMD_T* cmd);
int 	(*HDMI20_Chip_Suspend)(void);
int 	(*HDMI20_Chip_Resume)(void);
int 	(*HDMI20_Chip_SwVersion)(void);
void 	(*HDMI20_Chip_Set_Line_Debugger)(UINT32 value);
UINT32	(*HDMI20_Chip_Get_Line_Debugger)(void);
void 	(*HDMI20_Chip_Set_Audio_Line_Debugger)(UINT32 value);
UINT32	(*HDMI20_Chip_Get_Audio_Line_Debugger)(void);
int 	(*HDMI20_Chip_Get_DevConCnt)(HDMI20_DEV_CONTROL_TYPE_T type, int *pCnt, int isInternalCall);
int 	(*HDMI20_Chip_Get_DevCon)(HDMI20_DEV_CONTROL_TYPE_T type, HDMI20_DEV_CONTROL_T *pDevCon, int size, int isInternalCall);

/* Add */
// V4L2
int 	(*HDMI20_Chip_Get_DRMInfo)(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Get_VSIInfo)(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type);
int 	(*HDMI20_Chip_Get_AVIInfo)(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Get_SPDInfo)(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Get_EDID)(UINT8 port, UINT8 *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Set_EDID)(UINT8 port, UINT8 *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Set_EDID_Enable)(UINT8 port, BOOLEAN enable);
int 	(*HDMI20_Chip_Get_PHYStatus)(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);
int 	(*HDMI20_Chip_Set_RestartHPD)(UINT8 port);
int 	(*HDMI20_Chip_Set_HDCP14)(UINT8 port, UINT32 *pData, int size, int isInternalCall);
// KWRP
int 	(*HDMI20_Chip_Open)(void);
int 	(*HDMI20_Chip_Initialize)(LX_HDMI20_INIT_T *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Get_TimingInfo)(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Get_COLORInfo)(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall);
int 	(*HDMI20_Chip_Get_AspectRatio)(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall);

LX_HDMI_DOLBY_STATE_T (*HDMI20_Chip_Get_IsDolbyHDR)(UINT8 port);
int	(*HDMI20_Chip_Get_OperationStatus)(UINT8 port, LX_HDMI20_OP_STATUS_T *pData);


HDMI21_HDCP23_MODULE_FUNC_POINTER_T gHDMI21HDCP23FuncPointer;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void __HDMI20_Module_Get_ComparePhySettingValues(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI20_MODULE_PHY_DEFAULT_TABLE_T *pTable, struct seq_file* m);
static char *phymode_type_to_str(HDMI21_HAL_PHY_INITIATED_MODE_T type, int exceptionMode);
static void Print_RegTableIndex(struct seq_file *m);
static HDMI_PHY_INIT_MODE_T Get_PhyInitMode(char *mode_buf, int mode_num);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

int HDMI20_Module_InitChipRev(void)
{
	int ret = RET_ERROR;

	do{
		HDMI20_INFO("%s entered \n" , __func__);

		/* Memset 0 to chip reg handler */
		memset((void *)&gHDMI20ChipRegHandler, 0, sizeof(HDMI20_MODULE_CHIP_ADDR_DATA_T));
		memset((void *)&gHDMI21ChipRegHandler, 0, sizeof(HDMI21_MODULE_CHIP_ADDR_DATA_T));


		if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			/* Linux Method Layer Call */
			HDMI20_Chip_Process_Cmd = HDMI21_Process_Cmd;
			HDMI20_Chip_Suspend = HDMI21_Suspend;
			HDMI20_Chip_Resume = HDMI21_Resume;
			HDMI20_Chip_SwVersion = HDMI21_Version;
			HDMI20_Chip_Set_Line_Debugger = HDMI21_Set_Line_Debugger; 
			HDMI20_Chip_Get_Line_Debugger = HDMI21_Get_Line_Debugger;
			HDMI20_Chip_Set_Audio_Line_Debugger = HDMI21_Set_Audio_Line_Debugger;
			HDMI20_Chip_Get_Audio_Line_Debugger = HDMI21_Get_Audio_Line_Debugger;
			HDMI20_Chip_Get_DevConCnt = HDMI21_HAL_Rx_DBG_GetDevControllerCnt;
			HDMI20_Chip_Get_DevCon = HDMI21_HAL_Rx_DBG_GetDevController;
			/* Add */
			// V4L2
			HDMI20_Chip_Get_DRMInfo = HDMI21_DISLAND_Rx_Get_DRMInfo;
			HDMI20_Chip_Get_VSIInfo = HDMI21_DISLAND_Rx_Get_VSIInfo;
			HDMI20_Chip_Get_AVIInfo = HDMI21_DISLAND_Rx_Get_AVIInfo;
			HDMI20_Chip_Get_SPDInfo = HDMI21_DISLAND_Rx_Get_SPDInfo;
			HDMI20_Chip_Get_EDID = HDMI21_HAL_Rx_Get_EDID;
			HDMI20_Chip_Set_EDID = HDMI21_HAL_Rx_Set_EDID;
			HDMI20_Chip_Set_EDID_Enable = HDMI21_HAL_Rx_Set_EDID_Enable;
			HDMI20_Chip_Get_PHYStatus = HDMI21_PHY_Rx_Get_PhyStatus;
			HDMI20_Chip_Set_RestartHPD =  HDMI21_HAL_Rx_Set_RestartHPD;
			HDMI20_Chip_Set_HDCP14 = HDMI21_HAL_Rx_Set_HDCP14;
			// KWRP
			HDMI20_Chip_Open = HDMI21_Open;
			HDMI20_Chip_Initialize = HDMI21_HAL_Rx_Set_Initialize;
			HDMI20_Chip_Get_TimingInfo = HDMI21_HAL_Rx_Get_StableTimingInfo;
			HDMI20_Chip_Get_COLORInfo = HDMI21_DISLAND_Rx_Get_COLORInfo;
			HDMI20_Chip_Get_AspectRatio = HDMI21_DISLAND_Rx_Get_AspectRatio;
			HDMI20_Chip_Get_IsDolbyHDR  = HDMI21_HAL_Rx_Get_IsDolbyHDR;
			HDMI20_Chip_Get_OperationStatus = HDMI21_HAL_Rx_Get_OperationStatus;
			HDMI21_PHY_Rx_Set_InitFunctionPointer();
		}
		else {
			HDMI20_ERROR("[%s:%d] Error! Unknown chip revision \n", __F__, __L__);
			break;
		}

		if (lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		{
			HDMI20_INFO("[%s:%d] Link chip revision is set to [O26A0] \n", __F__, __L__);
			hdmi_phy_reg_ver 						= hdmi_phy_reg_ver_o26a0; 

			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_O26_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_O26_TOP_ALED_SIZE;

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_O26_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_O26_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_O26_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_O26_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_O26_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_O26_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_O26_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_O26_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_O26_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_O26_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_O26_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_O26_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_O26_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_O26_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_O26_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_O26_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_O26_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_O26_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_O26_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_O26_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_O26_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_O26_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_O26_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_O26_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_O26_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_O26_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_O26_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_O26_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_O26_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_O26_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_O26_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_O26_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_O26_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_O26_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_O26_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_O26_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_O26_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_O26_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_O26_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_O26_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_O26_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_O26_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_O26_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_O26_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_O26_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_O26_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_O26_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_O26_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_O26_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_O26_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_O26_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_O26_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_O26_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_O26_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.top_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.top_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= 0;
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = (__UINT32)(uintptr_t)NULL;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = 0;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= 0; 
			gHDMI21ChipRegHandler.irq_LINK[4] 		= 0;
		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		{
			HDMI20_INFO("[%s:%d] Link chip revision is set to [O24A0] \n", __F__, __L__);
			hdmi_phy_reg_ver 						= hdmi_phy_reg_ver_o24a0; 

			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_O24_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_O24_TOP_ALED_SIZE;

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_O24_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_O24_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_O24_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_O24_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_O24_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_O24_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_O24_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_O24_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_O24_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_O24_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_O24_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_O24_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_O24_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_O24_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_O24_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_O24_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_O24_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_O24_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_O24_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_O24_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_O24_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_O24_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_O24_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_O24_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_O24_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_O24_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_O24_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_O24_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_O24_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_O24_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_O24_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_O24_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_O24_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_O24_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_O24_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_O24_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_O24_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_O24_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_O24_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_O24_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_O24_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_O24_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_O24_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_O24_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_O24_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_O24_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_O24_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_O24_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_O24_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_O24_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_O24_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_O24_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_O24_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_O24_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.top_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.top_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= 0;
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = (__UINT32)(uintptr_t)NULL;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = 0;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= 0; 
			gHDMI21ChipRegHandler.irq_LINK[4] 		= 0;
		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		{	
			HDMI20_INFO("[%s:%d] Link chip revision is set to [M23A0] \n", __F__, __L__);
			hdmi_phy_reg_ver 						= hdmi_phy_reg_ver_m23a0;
			
			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_M23_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_M23_TOP_ALED_SIZE;

			/* M23 Only */
			gHDMI21ChipRegHandler.aled_top_P23_ADDR 	= HDMI21_HAL_M23_TOP_ALED_P23_ADDR;
			gHDMI21ChipRegHandler.aled_top_P23_SIZE 	= HDMI21_HAL_M23_TOP_ALED_P23_SIZE;
			/* End of M23 Only */

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_M23_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_M23_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_M23_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_M23_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_M23_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_M23_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_M23_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_M23_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_M23_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_M23_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_M23_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_M23_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_M23_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_M23_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_M23_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_M23_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_M23_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_M23_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_M23_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_M23_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_M23_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_M23_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_M23_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_M23_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_M23_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_M23_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_M23_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_M23_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_M23_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_M23_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_M23_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_M23_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_M23_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_M23_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_M23_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_M23_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_M23_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_M23_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_M23_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_M23_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_M23_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_M23_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_M23_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_M23_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_M23_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_M23_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_M23_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_M23_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_M23_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_M23_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_M23_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_M23_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_M23_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_M23_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.top_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.top_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= 0;
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = (__UINT32)(uintptr_t)NULL;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = 0;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= 0; 
			gHDMI21ChipRegHandler.irq_LINK[4] 		= 0;

		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		{
			HDMI20_INFO("[%s:%d] Link chip revision is set to [O22A0] \n", __F__, __L__);
			hdmi_phy_reg_ver 						= hdmi_phy_reg_ver_o22a0;

			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_O22_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_O22_TOP_ALED_SIZE;

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_O22_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_O22_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_O22_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_O22_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_O22_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_O22_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_O22_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_O22_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_O22_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_O22_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_O22_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_O22_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_O22_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_O22_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_O22_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_O22_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_O22_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_O22_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_O22_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_O22_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_O22_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_O22_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_O22_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_O22_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_O22_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_O22_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_O22_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_O22_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_O22_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_O22_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_O22_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_O22_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_O22_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_O22_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_O22_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_O22_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_O22_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_O22_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_O22_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_O22_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_O22_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_O22_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_O22_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_O22_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_O22_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_O22_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_O22_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_O22_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_O22_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_O22_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_O22_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_O22_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_O22_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_O22_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.top_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.top_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= 0;
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = (__UINT32)(uintptr_t)NULL;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = 0;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= 0; 
			gHDMI21ChipRegHandler.irq_LINK[4] 		= 0;
		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		{
			HDMI20_INFO("[%s:%d] Link chip revision is set to [E60A0] \n", __F__, __L__);
			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_E60_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_E60_TOP_ALED_SIZE;

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_E60_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_E60_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_E60_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_E60_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_E60_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_E60_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_E60_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_E60_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_E60_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_E60_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_E60_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_E60_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_E60_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_E60_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_E60_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_E60_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_E60_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_E60_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_E60_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_E60_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_E60_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_E60_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_E60_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_E60_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_E60_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_E60_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_E60_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_E60_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_E60_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_E60_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_E60_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_E60_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_E60_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_E60_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_E60_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_E60_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_E60_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_E60_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_E60_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_E60_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_E60_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_E60_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_E60_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_E60_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_E60_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_E60_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_E60_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_E60_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_E60_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_E60_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_E60_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_E60_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_E60_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_E60_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.top_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.top_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= 0;
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= (__UINT32)(uintptr_t)NULL;
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= 0;
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = (__UINT32)(uintptr_t)NULL;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = 0;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= 0; 
			gHDMI21ChipRegHandler.irq_LINK[4] 		= 0;
		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) )
		{
			HDMI20_INFO("[%s:%d] Link chip revision is set to [O20B0] \n", __F__, __L__);
			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_O20_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_O20_TOP_ALED_SIZE;

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_O20_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_O20_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_O20_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_O20_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_O20_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_O20_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_O20_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_O20_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_O20B0_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_O20B0_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_O20_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_O20_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_O20_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_O20_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_O20_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_O20_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_O20_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_O20_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_O20_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_O20_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_O20B0_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_O20B0_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_O20_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_O20_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_O20_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_O20_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_O20_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_O20_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_O20_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_O20_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_O20_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_O20_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_O20B0_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_O20B0_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_O20_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_O20_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_O20_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_O20_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_O20_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_O20_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_O20_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_O20_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_O20_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_O20_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_O20B0_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_O20B0_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_O20_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_O20_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_O20_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_O20_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_O20_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_O20_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_O20_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_O20_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= HDMI21_HAL_O20_RX4_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= HDMI21_HAL_O20_RX4_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[4] 		= HDMI21_HAL_O20B0_RX4_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[4] 		= HDMI21_HAL_O20B0_RX4_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= HDMI21_HAL_O20_RX4_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= HDMI21_HAL_O20_RX4_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= HDMI21_HAL_O20_RX4_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= HDMI21_HAL_O20_RX4_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = HDMI21_HAL_O20_RX4_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = HDMI21_HAL_O20_RX4_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= HDMI21_RX_O20_IRQ_TOP_PORT4;	
			gHDMI21ChipRegHandler.irq_LINK[4] 		= HDMI21_RX_O20_IRQ_LINK_PORT4;
		}
		else if (lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
		{
			HDMI20_INFO("[%s:%d] Link chip revision is set to [O20A0] \n", __F__, __L__);
			gHDMI21ChipRegHandler.aled_top_ADDR 	= HDMI21_HAL_O20_TOP_ALED_ADDR;
			gHDMI21ChipRegHandler.aled_top_SIZE 	= HDMI21_HAL_O20_TOP_ALED_SIZE;

			gHDMI21ChipRegHandler.dsc_top_ADDR		= HDMI21_HAL_O20_DSC_TOP_ADDR;
			gHDMI21ChipRegHandler.dsc_top_SIZE		= HDMI21_HAL_O20_DSC_TOP_SIZE;

			gHDMI21ChipRegHandler.dsc_core_ADDR		= HDMI21_HAL_O20_DSC_CORE_ADDR;
			gHDMI21ChipRegHandler.dsc_core_SIZE		= HDMI21_HAL_O20_DSC_CORE_SIZE;

			gHDMI21ChipRegHandler.fec_top_ADDR		= HDMI21_HAL_O20_FEC_TOP_ADDR;
			gHDMI21ChipRegHandler.fec_top_SIZE		= HDMI21_HAL_O20_FEC_TOP_SIZE;

			gHDMI21ChipRegHandler.ctrl_ADDR[0] 		= HDMI21_HAL_O20_RX0_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[0] 		= HDMI21_HAL_O20_RX0_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[0] 		= HDMI21_HAL_O20A0_RX0_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[0] 		= HDMI21_HAL_O20A0_RX0_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[0] 		= HDMI21_HAL_O20_RX0_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[0] 		= HDMI21_HAL_O20_RX0_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[0] 	= HDMI21_HAL_O20_RX0_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[0] 	= HDMI21_HAL_O20_RX0_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[0] = HDMI21_HAL_O20_RX0_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[0] = HDMI21_HAL_O20_RX0_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[0] 		= HDMI21_RX_O20_IRQ_TOP_PORT0;	
			gHDMI21ChipRegHandler.irq_LINK[0] 		= HDMI21_RX_O20_IRQ_LINK_PORT0;

			gHDMI21ChipRegHandler.ctrl_ADDR[1] 		= HDMI21_HAL_O20_RX1_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[1] 		= HDMI21_HAL_O20_RX1_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[1] 		= HDMI21_HAL_O20A0_RX1_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[1] 		= HDMI21_HAL_O20A0_RX1_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[1] 		= HDMI21_HAL_O20_RX1_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[1] 		= HDMI21_HAL_O20_RX1_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[1] 	= HDMI21_HAL_O20_RX1_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[1] 	= HDMI21_HAL_O20_RX1_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[1] = HDMI21_HAL_O20_RX1_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[1] = HDMI21_HAL_O20_RX1_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[1] 		= HDMI21_RX_O20_IRQ_TOP_PORT1;	
			gHDMI21ChipRegHandler.irq_LINK[1] 		= HDMI21_RX_O20_IRQ_LINK_PORT1;


			gHDMI21ChipRegHandler.ctrl_ADDR[2] 		= HDMI21_HAL_O20_RX2_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[2] 		= HDMI21_HAL_O20_RX2_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[2] 		= HDMI21_HAL_O20A0_RX2_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[2] 		= HDMI21_HAL_O20A0_RX2_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[2] 		= HDMI21_HAL_O20_RX2_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[2] 		= HDMI21_HAL_O20_RX2_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[2] 	= HDMI21_HAL_O20_RX2_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[2] 	= HDMI21_HAL_O20_RX2_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[2] = HDMI21_HAL_O20_RX2_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[2] = HDMI21_HAL_O20_RX2_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[2] 		= HDMI21_RX_O20_IRQ_TOP_PORT2;	
			gHDMI21ChipRegHandler.irq_LINK[2] 		= HDMI21_RX_O20_IRQ_LINK_PORT2;

			gHDMI21ChipRegHandler.ctrl_ADDR[3] 		= HDMI21_HAL_O20_RX3_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[3] 		= HDMI21_HAL_O20_RX3_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[3] 		= HDMI21_HAL_O20A0_RX3_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[3] 		= HDMI21_HAL_O20A0_RX3_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[3] 		= HDMI21_HAL_O20_RX3_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[3] 		= HDMI21_HAL_O20_RX3_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[3] 	= HDMI21_HAL_O20_RX3_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[3] 	= HDMI21_HAL_O20_RX3_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[3] = HDMI21_HAL_O20_RX3_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[3] = HDMI21_HAL_O20_RX3_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[3] 		= HDMI21_RX_O20_IRQ_TOP_PORT3;	
			gHDMI21ChipRegHandler.irq_LINK[3] 		= HDMI21_RX_O20_IRQ_LINK_PORT3;

			gHDMI21ChipRegHandler.ctrl_ADDR[4] 		= HDMI21_HAL_O20_RX4_CTRL_ADDR;	
			gHDMI21ChipRegHandler.ctrl_SIZE[4] 		= HDMI21_HAL_O20_RX4_CTRL_SIZE;	
			gHDMI21ChipRegHandler.top_ADDR[4] 		= HDMI21_HAL_O20A0_RX4_TOP_ADDR;	
			gHDMI21ChipRegHandler.top_SIZE[4] 		= HDMI21_HAL_O20A0_RX4_TOP_SIZE;	
			gHDMI21ChipRegHandler.aled_ADDR[4] 		= HDMI21_HAL_O20_RX4_ALED_ADDR;	
			gHDMI21ChipRegHandler.aled_SIZE[4] 		= HDMI21_HAL_O20_RX4_ALED_SIZE;	
			gHDMI21ChipRegHandler.phyPdc_ADDR[4] 	= HDMI21_HAL_O20_RX4_PDC_ADDR;	
			gHDMI21ChipRegHandler.phyPdc_SIZE[4] 	= HDMI21_HAL_O20_RX4_PDC_SIZE;	
			gHDMI21ChipRegHandler.phyPostDr_ADDR[4] = HDMI21_HAL_O20_RX4_POSTDR_ADDR;	
			gHDMI21ChipRegHandler.phyPostDr_SIZE[4] = HDMI21_HAL_O20_RX4_POSTDR_SIZE;	
			gHDMI21ChipRegHandler.irq_TOP[4] 		= HDMI21_RX_O20_IRQ_TOP_PORT4;	
			gHDMI21ChipRegHandler.irq_LINK[4] 		= HDMI21_RX_O20_IRQ_LINK_PORT4;
		}
		else
		{
			HDMI20_ERROR("[%s:%d] Error! Unknown chip revision \n", __F__, __L__);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI20_Module_Suspend(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Suspend == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Suspend();

	} while(0);

	return ret;

}

int HDMI20_Module_Resume(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Resume == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Resume();

	} while(0);

	return ret;
}

void HDMI20_Module_PreInit(void)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_Set_PreInit(1);
	}
	else {
		/* Nothing */
	}

	return;
}

// V4L2
int 	HDMI20_Module_Get_TimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_TimingInfo == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_TimingInfo(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_DRMInfo(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_DRMInfo == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_DRMInfo(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_VSIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_VSIInfo == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_VSIInfo(port, pData, size, isInternalCall, type);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_AVIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_AVIInfo == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_AVIInfo(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_SPDInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_SPDInfo == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_SPDInfo(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_EDID == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_EDID(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Set_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Set_EDID == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Set_EDID(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Set_EDID_Enable(UINT8 port, BOOLEAN enable)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Set_EDID_Enable == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Set_EDID_Enable(port, enable);

	} while(0);

	return ret;
}


int 	HDMI20_Module_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_PHYStatus == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_PHYStatus(pData, size, updatePhyI2C, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Set_RestartHPD(UINT8 port)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Set_RestartHPD == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Set_RestartHPD(port);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Set_HDCP14(UINT8 port, UINT32 *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Set_HDCP14 == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Set_HDCP14(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

// KWRP
int 	HDMI20_Module_Open(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Open == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Open();

	} while(0);

	return ret;
}

int 	HDMI20_Module_Initialize(LX_HDMI20_INIT_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Initialize == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Initialize(pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_COLORInfo(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_COLORInfo == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_COLORInfo(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_AspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_AspectRatio == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_AspectRatio(port, pData, size, isInternalCall);

	} while(0);

	return ret;
}


LX_HDMI_DOLBY_STATE_T HDMI20_Module_Get_IsDolbyHDR(UINT8 port)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_IsDolbyHDR == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_IsDolbyHDR(port);

	} while(0);

	return ret;
}

int	HDMI20_Module_Get_OperationStatus(UINT8 port, LX_HDMI20_OP_STATUS_T *pData)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Get_OperationStatus == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_OperationStatus(port, pData);

	} while(0);

	return ret;
}

int HDMI20_Module_SwVersion(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_SwVersion == NULL) {
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_ERROR;
			break;
		}

		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_SwVersion();

	} while(0);

	return ret;
}


int HDMI20_Module_Process_Cmd(LX_HDMI20_CMD_T* cmd)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(HDMI20_Chip_Process_Cmd == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			ret = RET_ERROR;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Process_Cmd((LX_HDMI20_CMD_T *)cmd);

	} while(0);

	return ret;
}

int 	HDMI20_Module_ProcHandler_ReadLGTVStatus(int port, struct seq_file* m)
{
	v4l2_hdmi20_header_ver_print(m);
	
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HAL_Rx_PROC_ExternalInputStatus(port, m);
	}
	else {
		/* None */
	}

	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadPhy28(int port, struct seq_file* m)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadPhy38(int port, struct seq_file* m)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadPhy48(int port, struct seq_file* m)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadLinkAPB(int port, struct seq_file* m)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadTopAPB(int port, struct seq_file* m)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadAledAPB(int port, struct seq_file* m)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadPhyDefault(int port, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI20_MODULE_PHY_DEFAULT_TABLE_T *_pT;
	int i;

	if(lx_chip_rev( ) >= LX_CHIP_REV( E60, B0) ) {
		if((port >= HDMI21_NUM_OF_MAX_PORTS)|| (port < 0)){
			printk("[%s:%d] Unsupported Port[%d]\n", __F__, __L__, port);
			return -1;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];


		i = HDMI20_MODULE_PHY_SET_TABLE_E60B0_VER100_IDX_CNT;
		for(i=0; i<HDMI20_MODULE_PHY_SET_TABLE_E60B0_VER100_IDX_CNT; i++) {
			_pT = &gHdmi20ModuleE60B0PhyDefaultTable[i];

			__HDMI20_Module_Get_ComparePhySettingValues(_p, _pT, m);
		}

	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HAL_Rx_PROC_PrintPhySetting(port, m);
	}
	else {
		/* None */
	}

	return 0;
}


int 	HDMI20_Module_ProcHandler_ESM_GetVersion(struct seq_file* m)
{
	unsigned char __rxId[5] = {0,};
	int size = 5;
	memset((void *)&__rxId, 0, sizeof(unsigned char) * 5 );


	seq_printf(m, "HostLib Function Pointer Status\n");
	seq_printf(m, "HDMI21_HDCP23_FP_Set_HlcReset = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcReset );
	seq_printf(m, "HDMI21_HDCP23_FP_Set_HlcAuthenticate = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcAuthenticate );
	seq_printf(m, "HDMI21_HDCP23_FP_Set_Close = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Close );
	seq_printf(m, "HDMI21_HDCP23_FP_Set_Open = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Open );
	seq_printf(m, "HDMI21_HDCP23_FP_Get_IsRepeater = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_IsRepeater );
	seq_printf(m, "HDMI21_HDCP23_FP_Set_IsRepeater = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_IsRepeater );
	seq_printf(m, "HDMI21_HDCP23_FP_Get_RxId = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_RxId );
	seq_printf(m, "HDMI21_HDCP23_FP_Set_RxId = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_RxId );
	seq_printf(m, "HDMI21_HDCP23_FP_TestApp = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_TestApp );
	seq_printf(m, "HDMI21_HDCP23_FP_Get_HlcMonitor = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_HlcMonitor );
	seq_printf(m, "HDMI21_HDCP23_FP_SetLogDump = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_SetLogDump );
	seq_printf(m, "HDMI21_HDCP23_FP_PROC_GetEsmLog  = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_PROC_GetEsmLog );
	seq_printf(m, "HDMI21_HDCP23_FP_GetContentType = 0x%p\n", gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_GetContentType );

	if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_RxId != NULL) {
		gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_RxId((unsigned char *)&__rxId, size);
		seq_printf(m, "Provided RxID : [0x%x][0x%x][0x%x][0x%x][0x%x]\n", __rxId[0], __rxId[1], __rxId[2], __rxId[3], __rxId[4]);
	}

	return 0;
}

int 	HDMI20_Module_ProcHandler_ESM_GetLog(struct seq_file* m)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HDCP23_Module_PROC_GetEsmLog(m);
	}
	else {
		/* None */
	}

	return 0;
}


int HDMI20_Module_ProcHandler_ESM_SetVersion(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}

int HDMI20_Module_ProcHandler_ESM_SetLog(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadEye(int port, struct seq_file* m)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HAL_Rx_PROC_PrintEyeMonitor(port, m);
	}
	else {
		/* None */
	}

	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadIsr(int port, struct seq_file* m)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HAL_Rx_PROC_PrintIRQ(port, m);
	}
	else {
		/* None */
	}

	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadPkt(int port, struct seq_file* m)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_DISLAND_Rx_PROC_PrintPktBuf(port, m);
	}
	else {
	}

	return 0;
}

int 	HDMI20_Module_ProcHandler_ReadEmPkt(int port, struct seq_file* m)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_DISLAND_Rx_PROC_PrintEmPkttBuf(port, m);
	}
	else {
	}

	return 0;
}


int 	HDMI20_Module_ProcHandler_ReadEDID(int port, struct seq_file* m)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HAL_Rx_PROC_PrintSavedEDID(port, m);
	}
	else {
	}

	return 0;
}

int		HDMI20_Module_ProcHandler_FILE_ReadEDID(int port, struct seq_file* m)
{
	int ret = RET_ERROR;
	UINT8 edid_data[HDMI21_HAL_SIZE_OF_EDID] = {0,};
	
	int size = HDMI21_HAL_SIZE_OF_EDID;
	int edid_row = (HDMI21_HAL_SIZE_OF_EDID >> 4);	// 512/16 = 32
	int i = 0;

	//1. get copy of edid data
	if( lx_chip_rev() >= LX_CHIP_REV( O20, A0) )
	{
		ret = HDMI21_HAL_Rx_Get_EDID(port, edid_data, size, 1);
	} else {
	}

	if( ret != RET_OK )
	{
		HDMI20_ERROR("Failed to get EDID data! \n");
		return ret;
	}

	//2. print edid_data
	for( i=0; i<edid_row; i++ )
	{
		seq_printf(m, "0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",\
		edid_data[(i*16)+0], edid_data[(i*16)+1], edid_data[(i*16)+2], edid_data[(i*16)+3], \
		edid_data[(i*16)+4], edid_data[(i*16)+5], edid_data[(i*16)+6], edid_data[(i*16)+7], \
		edid_data[(i*16)+8], edid_data[(i*16)+9], edid_data[(i*16)+10], edid_data[(i*16)+11], \
		edid_data[(i*16)+12], edid_data[(i*16)+13], edid_data[(i*16)+14], edid_data[(i*16)+15]);
	}
	
	ret = RET_OK;
	return ret;
}

int HDMI20_Module_ProcHandler_ReadPort(struct seq_file* m, int port)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		HDMI21_HAL_Rx_PROC_PrintVideo(port, m);
	}
	else {
	}

	return 0;
}

int HDMI20_Module_ProcHandler_ReadHDCPStatus(int port, struct seq_file* m)
{
	int version;
	
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
		version = HDMI21_HAL_Rx_Get_HDCPStatus(port);
	
		if(version) { seq_printf(m, "HDCP Status => HDCP[%d]\n", version); }
		else 		{ seq_printf(m, "Non Encrypted. Clear Video\n"); }
	}
	else {
		/* Supports from O20A0 */
	}

	return 0;
}

int HDMI20_Module_ProcHandler_WriteHDCPStatus(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}


int HDMI20_Module_ProcHandler_ReadDevCon(struct seq_file* m, HDMI20_DEV_CONTROL_TYPE_T	type)
{
	int 	i;
	int 	cnt = 0;
	int		size = 0;
	HDMI20_DEV_CONTROL_T 		*pDev = NULL;

	do{
		if(HDMI20_Module_Get_DevConCnt(type, &cnt) < 0) {
			seq_printf(m, "Return error getting dev con size\n");
			break;
		}

		size = cnt * sizeof(HDMI20_DEV_CONTROL_T);

		/* Malloc */
		pDev = (HDMI20_DEV_CONTROL_T *)kmalloc(size, GFP_KERNEL);

		/* Get Dev Con */
		if(HDMI20_Module_Get_DevCon(type, pDev, size) < 0) {
			seq_printf(m, "Return error getting dev con\n");
			kfree(pDev);
			break;
		}

		seq_printf(m, "----------------------------------------------------------\n");
		seq_printf(m,  "[HDMI2.0 Dev Controller]\n");
		seq_printf(m, "----------------------------------------------------------\n");
		for(i=0;i<cnt;i++){
			seq_printf(m, "[#%2d]. [%-54s] => [0x%08x] : %s \n", i,pDev[i].index, pDev[i].value, pDev[i].description);
		}
		seq_printf(m, "---------------------------------------------------------\n");
	} while(0);

	return 0;
}


int		HDMI20_Module_ProcHandler_WriteEmPkt(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int index = 0;
	int ret;
	UINT32 value;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;


	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value)\n");
			return 0;
		}
	}

	//printk("Index [%d] decimal[%d] hex[0x%08x]\n", index, value, value);
	printk("Not Implemented yet\n");
	return 0;

}

int		HDMI20_Module_ProcHandler_WriteEye(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int index = 0;
	int ret;
	UINT32 value[2];

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;


	if( (ret = sscanf(cmdbuf, "%d %d %d", &index, &value[0], &value[1])) != 3) {
		printk("Wrong usage. Usage => 0(1:start, 2:abort) 0(printmode 0:Graphic 1:Digit) 0(0:1/3 1:1/1)\n");
		return 0;
	}

	HDMI21_HAL_Rx_DBG_ActivateEyeMonitor(port, index, value[0], value[1]);

	return 0;
}


int		HDMI20_Module_ProcHandler_WritePhyDefault(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int ret = -1;

	HDMI20_MODULE_PHY_DEFAULT_TABLE_T __t;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do {
		if ( lx_chip_rev( ) < LX_CHIP_REV( O20, A0) ) {
			printk("[%s:%d] No support for old chips. Support from O20A0 and Up\n", __F__, __L__);
			break;
		}

		if((port >= HDMI21_NUM_OF_MAX_PORTS)|| (port < 0)){
			printk("[%s:%d] Unsupported Port[%d]\n", __F__, __L__, port);
			break;
		}

		/* Size Check */
		if( size == 0) {
			printk("[%s:%d] size is 0\n", __F__, __L__);
			break;
		} 

		if(*off != 0) {
			printk("[%s:%d] Do not support multi write\n", __F__, __L__);
			break;
		}

		if(size>sizeof(cmdbuf)-1) {
			printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
			break;
		}

		if(copy_from_user(cmdbuf, buf, size)>0) {
			printk("[%s:%d] copy from user error\n", __F__, __L__);
			break;
		}

		/* Make sure last word is NULL to proceed string print*/
		cmdbuf[size-1]= 0;

		if( (ret = sscanf(cmdbuf, "%s 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x", __t.index,\
						&__t.regAddr, &__t.subAddr, &__t.h14Mode01, &__t.h14Mode2, &__t.h14Mode3, &__t.h20Mode,\
						&__t.h21Frl1, &__t.h21Frl24, &__t.h21Frl5, &__t.h21Frl6)) != 11) {
			printk("Invalid Arg. Cnt:[%d]\n", ret);
			break;
		}

		/* Get Handler */
		_p = &gHDMI21RxHandler[port];


		/* API Call */
		__HDMI20_Module_Get_ComparePhySettingValues(_p, &__t, NULL);
		

		ret = 1;
	} while(0);


	return ret;
}

int		HDMI20_Module_ProcHandler_WriteAledAPB(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int mode = 0;
	int ret;
	UINT32 value[2] = {0,0};

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	ret = sscanf(cmdbuf, "%d 0x%x 0x%x", &mode, &value[0], &value[1]);

	if(ret != 3) {
		printk("Wrong usage. Usage => [0 or 1](0:Read 1:Write) [0x1234](addr) [0x1234](data or count) (value)\n");
		return 0;
	}

	if(mode == 0) {
		HDMI21_HAL_Rx_Get_AledReg(port, value[0], value[1]);
	} 
	else if(mode == 1) {
		HDMI21_HAL_Rx_Set_AledReg(port, value[0], value[1]);
	}
	else {
		printk("Unknown mode[%d]. 0:Read, 1:Write \n", mode);
	}

	return 0;

}

int		HDMI20_Module_ProcHandler_WriteTopAPB(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int mode = 0;
	int ret;
	UINT32 value[2] = {0,0};

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	ret = sscanf(cmdbuf, "%d 0x%x 0x%x", &mode, &value[0], &value[1]);

	if(ret != 3) {
		printk("Wrong usage. Usage => [0 or 1](0:Read 1:Write) [0x1234](addr) [0x1234](data or count) (value)\n");
		return 0;
	}

	if(mode == 0) {
		HDMI21_HAL_Rx_Get_TopReg(port, value[0], value[1]);
	} 
	else if(mode == 1) {
		HDMI21_HAL_Rx_Set_TopReg(port, value[0], value[1]);
	}
	else {
		printk("Unknown mode[%d]. 0:Read, 1:Write \n", mode);
	}

	return 0;

}

int		HDMI20_Module_ProcHandler_WriteLinkAPB(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int ret;
	int mode = 0;
	UINT32 value[2] = {0,0};

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	ret = sscanf(cmdbuf, "%d 0x%x 0x%x", &mode, &value[0], &value[1]);

	if(ret != 3) {
		printk("Wrong usage. Usage => [0 or 1](0:Read 1:Write) [0x1234](addr) [0x1234](data or count) (value)\n");
		return 0;
	}

	if(mode == 0) {
		HDMI21_HAL_Rx_Get_LinkReg(port, value[0], value[1]);
	} 
	else if(mode == 1) {
		HDMI21_HAL_Rx_Set_LinkReg(port, value[0], value[1]);
	}
	else {
		printk("Unknown mode[%d]. 0:Read, 1:Write \n", mode);
	}

	return 0;

}

int		HDMI20_Module_ProcHandler_WritePhy28(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int ret;
	int mode = 0;
	UINT32 value[2] = {0,0};

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	ret = sscanf(cmdbuf, "%d 0x%x 0x%x", &mode, &value[0], &value[1]);

	if(ret != 3) {
		printk("Wrong usage. Usage => [0 or 1](0:Read 1:Write) [0x1234](addr) [0x1234](data or count) (value)\n");
		return 0;
	}

	if(mode == 0) {
		HDMI21_HAL_Rx_Get_PhyReg(port, 0x28, value[0], value[1]);
	} 
	else if(mode == 1) {
		HDMI21_HAL_Rx_Set_PhyReg(port, 0x28, value[0], value[1]);
	}
	else {
		printk("Unknown mode[%d]. 0:Read, 1:Write \n", mode);
	}

	return 0;
}

int		HDMI20_Module_ProcHandler_WritePhy38(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int ret;
	int mode = 0;
	UINT32 value[2] = {0,0};

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	ret = sscanf(cmdbuf, "%d 0x%x 0x%x", &mode, &value[0], &value[1]);

	if(ret != 3) {
		printk("Wrong usage. Usage => [0 or 1](0:Read 1:Write) [0x1234](addr) [0x1234](data or count) (value)\n");
		return 0;
	}

	if(mode == 0) {
		HDMI21_HAL_Rx_Get_PhyReg(port, 0x38, value[0], value[1]);
	} 
	else if(mode == 1) {
		HDMI21_HAL_Rx_Set_PhyReg(port, 0x38, value[0], value[1]);
	}
	else {
		printk("Unknown mode[%d]. 0:Read, 1:Write \n", mode);
	}

	return 0;
}

int		HDMI20_Module_ProcHandler_WritePhy48(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int ret;
	int mode = 0;
	UINT32 value[2] = {0,0};

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	ret = sscanf(cmdbuf, "%d 0x%x 0x%x", &mode, &value[0], &value[1]);

	if(ret != 3) {
		printk("Wrong usage. Usage => [0 or 1](0:Read 1:Write) [0x1234](addr) [0x1234](data or count) (value)\n");
		return 0;
	}

	if(mode == 0) {
		HDMI21_HAL_Rx_Get_PhyReg(port, 0x48, value[0], value[1]);
	} 
	else if(mode == 1) {
		HDMI21_HAL_Rx_Set_PhyReg(port, 0x48, value[0], value[1]);
	}
	else {
		printk("Unknown mode[%d]. 0:Read, 1:Write \n", mode);
	}

	return 0;
}

int		HDMI20_Module_ProcHandler_WriteIsr(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int index = 0;
	int ret;
	UINT32 value;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;


	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value)\n");
			return 0;
		}
	}

	//printk("Index [%d] decimal[%d] hex[0x%08x]\n", index, value, value);
	printk("Not Implemented yet\n");
	return 0;

}



int		HDMI20_Module_ProcHandler_WritePkt(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int index = 0;
	int ret;
	UINT32 value;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;


	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value)\n");
			return 0;
		}
	}

	//printk("Index [%d] decimal[%d] hex[0x%08x]\n", index, value, value);
	printk("Not Implemented yet\n");
	return 0;

}


int		HDMI20_Module_ProcHandler_WriteEDID(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[512];
	int index = 0;
	int ret;
	UINT32 value;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;


	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value)\n");
			return 0;
		}
	}

	//printk("Index [%d] decimal[%d] hex[0x%08x]\n", index, value, value);
	printk("Not Implemented yet\n");
	return 0;

}
int		HDMI20_Module_ProcHandler_FILE_WriteEDID(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	int ret = RET_ERROR;
	int line_size = 80;
	int i = 0;
	int j = 0;
	UINT8 edid_data[HDMI21_HAL_SIZE_OF_EDID] = {0,};
	char read_buf[5] = {'\0',};
	unsigned int cvt_temp = 0;

	char *cmd_buf = NULL;
	char temp[80] = {'\0',};
	int edid_size = 0;
	int edid_row_size = 0;

	cmd_buf = (char *)kmalloc( (sizeof(char)*size)+1, GFP_KERNEL);
	if( cmd_buf == NULL )
	{
		HDMI20_ERROR("cmd_buf memory alloc failed! \n");
		return ret;
	} else {
		memset(cmd_buf, '\0', sizeof(char)*size+1);
	}
	
	//Size Check
	if( size == 0) {
		HDMI20_ERROR("user-buf size is 0 \n");
		goto failed;
	} 

	//edid-size check
	edid_size = size / 5;		// in user-buffer, 1 edid-data = 5bytes (0xXX\t)
	edid_row_size = (edid_size >> 4);
	if ( edid_size != 512 && edid_size != 128 )
	{
		HDMI20_ERROR("edid size is not 512 or 128 byte \n");
		goto failed;
	}

	if(*off != 0) {
		HDMI20_ERROR("Do not support multi write \n");
		goto failed;
	}

	if( copy_from_user( cmd_buf, buf, size ) > 0 ) {
		HDMI20_ERROR("copy from user error\n");
		goto failed;
	}

	//Make sure last word is NULL to processed string print
	cmd_buf[size] = '\0';

	//Get edid data
	for(i=0 ; i<edid_row_size; i++)
	{
		memcpy(temp, cmd_buf+(i*line_size), line_size);
		for(j=0; j<16; j++)
		{
			memcpy(read_buf, temp+(j*5), sizeof(char)*5);
			read_buf[4] = '\0';
			sscanf(read_buf, "0x%02x", &cvt_temp);
			edid_data[(i*16)+j] = (UINT8)(cvt_temp &= 0xFF);
		}
	}

	//set edid data
	if( lx_chip_rev() >= LX_CHIP_REV( O20, A0) )
	{
		ret = HDMI21_HAL_Rx_Set_EDID(port, edid_data, edid_size, 1);
	} else {
	}

	if( ret == RET_OK)
	{
		printk("Updating port[%02d]'s edid is done!\n", port);
	} else {
		printk("Updating port[%02d]'s edid is failed!\n", port);
	}

failed:
	//mem free
	kfree(cmd_buf);
	return ret;
}

int		HDMI20_Module_ProcHandler_WritePort(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[64];
	int index = 0;
	int ret;
	UINT32 value;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;


	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value)\n");
			return 0;
		}
	}

	printk("Index [%d] decimal[%d] hex[0x%08x]\n", index, value, value);

	return 0;
}

int 	HDMI20_Module_ProcHandler_WriteDevCon(HDMI20_DEV_CONTROL_TYPE_T	type, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[64];
	int index = 0;
	UINT32 value;
	int ret;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	if(type >= HDMI20_DEV_CONTROL_MAXNUM) {
		printk("[%s:%d] type error[%d]\n", __F__, __L__, type);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value)\n");
			return 0;
		}
	}

	ret = HDMI20_Module_Set_DevCon(type, index, value);

	return ret;
}

int 	HDMI20_Module_ProcHandler_ReadDdcMon(int port, struct seq_file *m)
{
	int ret = RET_OK;
	int i,y;
	UINT8 __data[4];
	int num_of_ports = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p = NULL;

	if(lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{

		num_of_ports = HDMI21_NUM_OF_PORTS_E60; /* O22 has the same port num of E60 */


		if(port >= num_of_ports ){
			seq_printf(m, "not supported for port[%d]\n", port);
			return -1;
		}

		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];


		for(i=0;i<_p->ddcBufPnt;i++) {
			seq_printf(m, "#[%d]|[%u]msec (Bank:%d) => %02x:%02x(%s) - ",\
					i, _p->pDdcBuf[i].msec, _p->pDdcBuf[i].bank, _p->pDdcBuf[i].dev_addr, _p->pDdcBuf[i].sub_addr, _p->pDdcBuf[i].op_mode?"R":"W");	

			memcpy((void *)&__data[0], (void *)&_p->pDdcBuf[i].data, sizeof(UINT32));

			for(y=0; y<_p->pDdcBuf[i].cap_length; y++) {
				seq_printf(m, "%02x ", __data[3-y]);
			}

			seq_printf(m, "(length:%d) %s%s%s%s\n", _p->pDdcBuf[i].cap_length, _p->pDdcBuf[i].finish?"(Finish)":"",\
					_p->pDdcBuf[i].scdc_short_rd?"(SCDC Short)":"", _p->pDdcBuf[i].hdcp_short_rd?"(HDCP Short)":"", _p->pDdcBuf[i].nack?"(NACK)":"");	
		}
	}
	return ret;
}

int 	HDMI20_Module_ProcHandler_WriteDdcMon(int port, struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	int ret = RET_OK;
	char cmdbuf[64];
	int index = 0;
	UINT32 value;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if(lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
			if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
				printk("Wrong usage. Usage => [0](Menu) [0x1234 or 1234](value)\n");
				return 0;
			}
		}

		if(index == 0) {
			HDMI21_HAL_Rx_DBG_Tool(120, port, value);
			HDMI21_HAL_Rx_DBG_Tool(122, port, value);
		}
		else if(index == 1) {
			HDMI21_HAL_Rx_DBG_Tool(123, port, value);
		}
		else if(index == 2) {
			HDMI21_HAL_Rx_DBG_Tool(121, port, value);
		}

	}
	return ret;
}



int		HDMI20_Module_ProcHandler_ReadCalOS(int port, struct seq_file *m)
{
	int ret = RET_OK;
	int num_of_ports = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p = NULL;
	UINT32 cal_os[4][9] = {{0,},};
	UINT32 ch_sel_addr = 0x0;
	UINT32 reg_addr = 0x0;
	UINT32 temp = 0x0;
	int i, j;

	if(lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		num_of_ports = HDMI21_NUM_OF_PORTS_E60;
	} else if (lx_chip_rev() >= LX_CHIP_REV(O20, A0)){
		num_of_ports = HDMI21_NUM_OF_PORTS_O20;
	} else {
		seq_printf(m, "This feature is only supported for O20, E60.\n");
		return -1; 
	}
	
	if(port >= num_of_ports ){
		seq_printf(m, "not supported for port[%d]\n", port);
		return -1;
	}

	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

	//Store 0x38:0xd9 value
	ch_sel_addr = 0xd9; ch_sel_addr = ch_sel_addr << 2; temp = _p->phyDR_read(ch_sel_addr);

	//Get Offset value
	for(i=0; i<4; i++)
	{
		ch_sel_addr = 0xd9; ch_sel_addr = ch_sel_addr << 2;
		_p->phyDR_write(ch_sel_addr, i);
		for(j=0; j<9; j++)
		{
			reg_addr = 0xc8 + j; reg_addr = reg_addr << 2;
			cal_os[i][j] = _p->phyDR_read(reg_addr);
		}
	}

	//Restore 0xd9 value
	ch_sel_addr = 0xd9; ch_sel_addr = ch_sel_addr << 2; _p->phyDR_write(ch_sel_addr, temp);

	seq_printf(m, " ===================================== \n");
	seq_printf(m, " |       | ch0  | ch1  | ch2  | ch3  | \n");
	seq_printf(m, " |===================================| \n");
	seq_printf(m, " |se_os  | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][0], cal_os[1][0], cal_os[2][0], cal_os[3][0]);
	seq_printf(m, " |so_os  | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][1], cal_os[1][1], cal_os[2][1], cal_os[3][1]);
	seq_printf(m, " |te_os  | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][2], cal_os[1][2], cal_os[2][2], cal_os[3][2]);
	seq_printf(m, " |to_os  | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][3], cal_os[1][3], cal_os[2][3], cal_os[3][3]);
	seq_printf(m, " |dep_os | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][4], cal_os[1][4], cal_os[2][4], cal_os[3][4]);
	seq_printf(m, " |den_os | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][5], cal_os[1][5], cal_os[2][5], cal_os[3][5]);
	seq_printf(m, " |dop_os | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][6], cal_os[1][6], cal_os[2][6], cal_os[3][6]);
	seq_printf(m, " |don_os | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][7], cal_os[1][7], cal_os[2][7], cal_os[3][7]);
	seq_printf(m, " |eq_os  | 0x%02x | 0x%02x | 0x%02x | 0x%02x | \n", cal_os[0][8], cal_os[1][8], cal_os[2][8], cal_os[3][8]);
	seq_printf(m, " ======================================\n");

	return ret;
}

int		HDMI20_Module_Set_Calculate_EDID_CheckSum(int port, bool *isChanged)
{
	int ret = RET_ERROR;
	UINT8 edid_data[HDMI21_HAL_SIZE_OF_EDID] = {0,};
	int edid_row = (HDMI21_HAL_SIZE_OF_EDID >> 4);
	int edid_size = HDMI21_HAL_SIZE_OF_EDID;
	int edid_block_align = 16;
	UINT32 temp = 0;
	UINT32 check_sum_temp = 0;
	UINT8 check_sum_result = 0;
	int i,j = 0;
	
	//1. Get Hdmi port edid
	if( lx_chip_rev() >= LX_CHIP_REV(O20,A0))
	{ 
		ret = HDMI21_HAL_Rx_Get_EDID(port, edid_data, edid_size, 1);
	} else {
	}
	
	if( ret != RET_OK )
	{
		HDMI20_ERROR("Failed to get EDID data!\n");
		return ret;
	}

	//2. Calculate edid check sum
	for( i=0; i<edid_row; i++ )
	{
		for( j=0; j<edid_block_align; j++)
		{
			//Check-sum byte
			if( ((i-7)%8==0) && j == (edid_block_align-1))
			{
				check_sum_temp = temp;
				check_sum_temp &= 0xFF;
				check_sum_temp = ~(check_sum_temp);
				check_sum_temp += 1;
				check_sum_result = (UINT8)(check_sum_temp & 0xFF);
				temp = 0;

				if( edid_data[(i*edid_block_align)+j] != check_sum_result )
				{
					edid_data[(i*edid_block_align)+j] = check_sum_result;
					*isChanged = true;
				}

			} else {
				temp += edid_data[(i*edid_block_align)+j];
			}
		}
	}

	//3. Set Hdmi port edid
	//set edid data
	if ( *isChanged )
	{	
		if( lx_chip_rev() >= LX_CHIP_REV( O20, A0) )
		{
			ret = HDMI21_HAL_Rx_Set_EDID(port, edid_data, edid_size, 1);
		} else {
		}

		if( ret == RET_OK)
		{
			HDMI20_PRINT("Updating port[%02d]'s edid check-sum is done!\n", port);
		} else {
			HDMI20_ERROR("Updating port[%02d]'s edid check-sum is failed!\n", port);
			return ret;
		}

	} else {
		printk("port[%02d] EDID and check-sum are not changed!\n",port);
	}

	return ret;
}

void 	HDMI20_Module_Set_Line_Debugger(UINT32 value)
{
	do{
		/* Step 1. Check if Function pointer is NULL */
		if( HDMI20_Chip_Set_Line_Debugger == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		HDMI20_Chip_Set_Line_Debugger(value);

	} while(0);

	return;
}

UINT32	HDMI20_Module_Get_Line_Debugger(void)
{
	UINT32 ret = 0;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if( HDMI20_Chip_Get_Line_Debugger == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_Line_Debugger();

	} while(0);

	return ret;
}

void 	HDMI20_Module_Set_Audio_Line_Debugger(UINT32 value)
{
	do{
		/* Step 1. Check if Function pointer is NULL */
		if( HDMI20_Chip_Set_Audio_Line_Debugger == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		HDMI20_Chip_Set_Audio_Line_Debugger(value);

	} while(0);

	return;
}


UINT32	HDMI20_Module_Get_Audio_Line_Debugger(void)
{
	UINT32 ret = 0;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if( HDMI20_Chip_Get_Audio_Line_Debugger == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_Audio_Line_Debugger();

	} while(0);

	return ret;
}

int 	HDMI20_Module_Get_DevConCnt(HDMI20_DEV_CONTROL_TYPE_T type, int *pCnt)
{
	UINT32 ret = 0;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if( HDMI20_Chip_Get_DevConCnt == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_DevConCnt(type, pCnt, 1);

	} while(0);

	return (int)ret;
}

int 	HDMI20_Module_Get_DevCon(HDMI20_DEV_CONTROL_TYPE_T type, HDMI20_DEV_CONTROL_T *pDevCon, int size)
{
	UINT32 ret = 0;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if( HDMI20_Chip_Get_DevCon == NULL){
			HDMI20_ERROR("[%s:%d] Error! HDMI20 chip ID was not selected!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = HDMI20_Chip_Get_DevCon(type, pDevCon, size, 1);

	} while(0);

	return (int)ret;

}

int		HDMI20_Module_Set_DevCon(HDMI20_DEV_CONTROL_TYPE_T type, UINT32 index, UINT32 data)
{
	int ret = 0;
	UINT32 value;

	value = data;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		switch(type)
		{
			case HDMI20_DEV_CONTROL_VIDEO:
				{
					ret = HDMI21_HAL_Rx_DBG_AccessDevVideoController((HDMI21_DEV_VIDEO_CONTROL_LIST_T)index, 1, &value, 1);
				}
				break;
			case HDMI20_DEV_CONTROL_AUDIO:
				{
					ret = HDMI21_HAL_Rx_DBG_AccessDevAudioController((HDMI21_DEV_AUDIO_CONTROL_LIST_T)index, 1, &value, 1);
				}
				break;
			case HDMI20_DEV_CONTROL_PHY:
				{
					ret = HDMI21_HAL_Rx_DBG_AccessDevPhyController((HDMI21_DEV_PHY_CONTROL_LIST_T)index, 1, &value, 1);
				}
				break;
			case HDMI20_DEV_CONTROL_LINK:
				{
					ret = HDMI21_HAL_Rx_DBG_AccessDevLinkController((HDMI21_DEV_LINK_CONTROL_LIST_T)index, 1, &value, 1);
				}
				break;
			case HDMI20_DEV_CONTROL_EARC:
				{
					ret = HDMI21_HAL_Rx_DBG_AccessDevEARCController((HDMI21_DEV_EARC_CONTROL_LIST_T)index, 1, &value, 1);
				}
				break;

			default :
				break;
		}
	}
	else{
	}

	return ret;
}

int		HDMI20_Module_Set_DBGTool(int type, UINT8 port, int data)
{

	int ret = 0;


	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		ret = HDMI21_HAL_Rx_DBG_Tool(type, port, data);
	}
	else{
	}

	return ret;
}


UINT32		HDMI20_Module_Get_VrrFrequency(UINT8 port)
{
	UINT32 freq = 0;
	UINT16 data = 0;
	int ret;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		ret = HDMI21_HAL_Rx_Get_VrrCurrentVfreq(port, &data, sizeof(UINT16), 1);
	}
	else{
	}

	if(ret >= 0) {
		freq = (UINT32)data; 
	}
	else {
		freq = 0;
	}

	return freq;
}

int HDMI20_Module_Get_EMPInfo(UINT8 port, UINT8 *pData, LX_HDMI20_EMP_TYPE_T type, int isInternalCall)
{
	int ret;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		ret = HDMI21_DISLAND_Rx_Get_EMPInfo(port, pData, type, isInternalCall);
	}
	else{
	}

	return ret;
}


int		HDMI20_Module_Set_ExecuteDscMode(UINT8 port)
{
	int ret = RET_ERROR;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		ret = HDMI21_HAL_Rx_Set_EnableDscModule(port);
	}

	return ret;


}


int 	HDMI21_HDCP23_Module_Set_HlcReset(unsigned int port, int isPllLocked)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcReset == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcReset(port, isPllLocked);

	} while(0);

	return ret;
}

int 	HDMI21_HDCP23_Module_Set_HlcAuthenticate(unsigned int port, int reauth)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcAuthenticate == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcAuthenticate(port, reauth);

	} while(0);

	return ret;
}

int 	HDMI21_HDCP23_Module_Set_Close(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Close == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			ret = RET_OK;
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Close();

	} while(0);

	return ret;


}

int 	HDMI21_HDCP23_Module_Set_Open(UINT8 *pData, int size, int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Open == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Open(pData, size, chipType, codebase, codeVirtAddr, database, dataVirtAddr);

	} while(0);

	return ret;

}

int 	HDMI21_HDCP23_Module_Get_IsRepeater(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_IsRepeater == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_IsRepeater();

	} while(0);

	return ret;

}

int 	HDMI21_HDCP23_Module_Set_IsRepeater(int isRepeater)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_IsRepeater == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_IsRepeater(isRepeater);

	} while(0);

	return ret;

}

int 	HDMI21_HDCP23_Module_Get_RxId(unsigned char* pData, int size)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_RxId == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_RxId(pData, size);

	} while(0);

	return ret;

}

int 	HDMI21_HDCP23_Module_Set_RxId(unsigned char* pData, int size, int count, int depth)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_RxId == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_RxId(pData, size, count, depth);

	} while(0);

	return ret;

}

int 	HDMI21_HDCP23_Module_TestApp(int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_TestApp == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}

		/* Step 2. Execute Chip driver */
		gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_TestApp(chipType, codebase, codeVirtAddr, database, dataVirtAddr);
	
		ret = RET_OK;
	} while(0);

	return ret;

}

int 	HDMI21_HDCP23_Module_Get_HlcMonitor(unsigned int port)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_HlcMonitor == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_HlcMonitor(port);

	} while(0);

	return ret;

}

void 	HDMI21_HDCP23_Module_SetLogDump(char *pData, int *pSize)
{
	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_SetLogDump == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_SetLogDump(pData, pSize);

	} while(0);

	return;
}

int 	HDMI21_HDCP23_Module_Get_ContentType(unsigned int port)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_GetContentType == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}
		
		/* Step 2. Execute Chip driver */
		ret = gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_GetContentType(port);

	} while(0);

	return ret;

}

void 	HDMI21_HDCP23_Module_PROC_GetEsmLog(struct seq_file* m)
{
	do{
		/* Step 1. Check if Function pointer is NULL */
		if(gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_PROC_GetEsmLog == NULL){
			HDMI21_LINE_DBG(2128, "[%s:%d] Error! Function Pointer for ESM call was not initiated!\n", __F__, __L__);
			break;
		}

		/* Step 2. Execute Chip driver */
		gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_PROC_GetEsmLog(m);
	} while(0);
}

void 	HDMI21_Module_Set_RegisterCB_HlcReset(int (*function)(unsigned int port, int isPllLocked))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcReset = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_HlcAuthenticate(int (*function)(unsigned int port, int reauth))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_HlcAuthenticate = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_Close(int (*function)(void))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Close = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_Open(int (*function)(UINT8 *pData, int size, int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_Open = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_GetRepeater(int (*function)(void))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_IsRepeater = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_SetRepeater(int (*function)(int isRepeater))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_IsRepeater = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_GetRxId(int (*function)(unsigned char* pData, int size))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_RxId = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_SetRxId(int (*function)(unsigned char* pData, int size, int count, int depth))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Set_RxId = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_TestApp(void (*function)(int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_TestApp = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_HlcMonitor(int (*function)(unsigned int port))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_Get_HlcMonitor = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_LogDump(void (*function)(char *pData, int *pSize))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_SetLogDump = function;
	return;
}

void 	HDMI21_Module_Set_RegisterCB_GetEsmLog(void (*function)(struct seq_file* m))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_PROC_GetEsmLog = function;
	return;
}

void	HDMI21_Module_Set_RegisterCB_GetContentType(int (*function)(unsigned int port))
{
	gHDMI21HDCP23FuncPointer.HDMI21_HDCP23_FP_GetContentType = function;
}

void   HDMI21_Module_Set_EsmOfDmaConfigure(struct device *dev, struct device_node *np)
{
	#if defined(CONFIG_ARM64) && LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0)
	dev->coherent_dma_mask = DMA_BIT_MASK(32);
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,18,0)
	of_dma_configure(dev, np, true);
	#else
	of_dma_configure(dev, np);
	#endif
	#endif
	return;
}

static void __HDMI20_Module_Get_ComparePhySettingValues(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI20_MODULE_PHY_DEFAULT_TABLE_T *pTable, struct seq_file* m)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI20_MODULE_PHY_DEFAULT_TABLE_T *_pT = pTable;
	UINT32 value = 0;
	UINT32 regValue = 0;
	UINT32 __reg  = 0;
	int isSame = 0;

	if(_p == NULL) {
		printk("[%s:%d] Null Dev handler pointer\n", __F__, __L__);
		return;
	}

	if(_pT == NULL) {
		printk("[%s:%d] Null Table pointer\n", __F__, __L__);
		return;
	}

	/* Check Current Phy Mode */
		if(_p->phyInitiatedMode == 	HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
			value = _pT->h21Frl6;
		}
		else if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
			value = _pT->h21Frl5;
		}
		else if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_6G_3L) {
			value = _pT->h21Frl24;
		}
		else if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			value = _pT->h21Frl1;
		}
		else if(_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_6G) {
			value = _pT->h20Mode; 
		}
		else {
			if(_p->phyCurrentTMDSExceptionRange == 2) {
				/* MODE 2 */
				value = _pT->h14Mode2;	
			}
			else if(_p->phyCurrentTMDSExceptionRange == 1) {
				/* MODE 1 */
				value = _pT->h14Mode01;
			}
			else {
				/* MODE 3 */
				value = _pT->h14Mode3;
			}
		}

		/* Check Reg Bank */
		if((_pT->regAddr == 0x68) || (_pT->regAddr == 0x28)) {
			__reg = _pT->subAddr; __reg = __reg << 2; regValue = _p->phyPDC_read(__reg);
		}
		else if(_pT->regAddr == 0x38) {
			__reg = _pT->subAddr; __reg = __reg << 2; regValue = _p->phyDR_read(__reg);
		}
		else if(_pT->regAddr == 0x48) {
			__reg = _pT->subAddr; __reg = (__reg << 2) + 0x400; regValue = _p->phyDR_read(__reg);
		}
		else {
			printk("[%s:%d] Unknown reg bank type[0x%x]\n", __F__, __L__, _pT->regAddr);
			return;
		}

		/* Compare */
		if(regValue == value) isSame = 1;
		else isSame = 0;

		if(m == NULL) {
		/* Print out Result */
		printk("[%-30s] [0x%02x]:[0x%02x] => [0x%02x] (%s) (Table Value : 0x%02x) [PHY Mode : %s]\n",\
				_pT->index, _pT->regAddr, _pT->subAddr, regValue, isSame?"OK":"NG", value,\
				phymode_type_to_str(_p->phyInitiatedMode, _p->phyCurrentTMDSExceptionRange));
		}
		else {
			seq_printf(m, "[%-30s] [0x%02x]:[0x%02x] => [0x%02x] (%s) (Table Value : 0x%02x) [PHY Mode : %s]\n",\
				_pT->index, _pT->regAddr, _pT->subAddr, regValue, isSame?"OK":"NG", value,\
				phymode_type_to_str(_p->phyInitiatedMode, _p->phyCurrentTMDSExceptionRange));
		}

		return;
}

static char *phymode_type_to_str(HDMI21_HAL_PHY_INITIATED_MODE_T type, int exceptionMode)
{
	switch (type)
	{
		case HDMI21_HAL_PHY_INITIATED_6G:
			return "HDMI2.0   ";
		case HDMI21_HAL_PHY_INITIATED_FRL_3G_3L:
			return "FRL 3G 3L ";
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_3L:
			return "FRL 6G 3L ";
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_4L:
			return "FRL 6G 4L ";
		case HDMI21_HAL_PHY_INITIATED_FRL_8G_4L:
			return "FRL 8G 4L ";
		case HDMI21_HAL_PHY_INITIATED_FRL_10G_4L:
			return "FRL 10G 4L";
		case HDMI21_HAL_PHY_INITIATED_FRL_12G_4L:
			return "FRL 12G 4L";
		case HDMI21_HAL_PHY_INITIATED_ERROR:
		case HDMI21_HAL_PHY_INITIATED_3G:
		default :
			if(exceptionMode == 2) {
				return "HDMI1.4 M2";
			}
			else if(exceptionMode == 1) {
				return "HDMI1.4 M1";
			}
			else {
				return "HDMI1.4 M3";
			}
	}
}

static void Print_RegTableIndex(struct seq_file *m)
{
	seq_printf(m, "=========================================================================================================================================================================\n");
	seq_printf(m, "[Reg Table Ver:%s]                                                             |  FRL1 |  FRL2 |  FRL3 |  FRL4 |  FRL5 |  FRL6 | 10GCTS| 12GCTS| \n",hdmi_phy_reg_ver);
	seq_printf(m, "[ idx]. [%-30s] : |  3GM0 |  3GM1 |  3GM2 |  3GM3 |   6G  |  3G3L |  6G3L |  6G4L |  8G4L | 10G4L | 12G4L | 10GCTS| 12GCTS| [desc] \n", \
			"reg_name");
	seq_printf(m, "=========================================================================================================================================================================\n");
}

static HDMI_PHY_INIT_MODE_T Get_PhyInitMode(char *mode_buf, int mode_num)
{
	HDMI_PHY_INIT_MODE_T ret = 0;
	if( !strcmp(mode_buf,"3gm0") ||
		!strcmp(mode_buf,"3GM0") ||
		!strcmp(mode_buf,"0"))
	{
		ret = HDMI_PHY_INITIATED_3G_M0;
	}
	else if( !strcmp(mode_buf,"3gm1") ||
			 !strcmp(mode_buf,"3GM1") ||
			 !strcmp(mode_buf,"1"))
	{
		ret = HDMI_PHY_INITIATED_3G_M1;
	}
	else if( !strcmp(mode_buf,"3gm2") ||
			 !strcmp(mode_buf,"3GM2") ||
			 !strcmp(mode_buf,"2") )
	{
		ret = HDMI_PHY_INITIATED_3G_M2;
	}
	else if( !strcmp(mode_buf,"3gm3") ||
			 !strcmp(mode_buf,"3GM3") ||
			 !strcmp(mode_buf,"3"))
	{
		ret = HDMI_PHY_INITIATED_3G_M3;
	}
	else if( !strcmp(mode_buf,"6g") ||
			 !strcmp(mode_buf,"6G") ||
			 !strcmp(mode_buf,"4"))
	{
		ret = HDMI_PHY_INITIATED_6G;
	}
	else if( !strcmp(mode_buf,"3g3l") ||
			 !strcmp(mode_buf,"3G3L") ||
			 !strcmp(mode_buf,"5"))
	{
		ret = HDMI_PHY_INITIATED_FRL_3G_3L;
	}
	else if( !strcmp(mode_buf,"6g3l") ||
			 !strcmp(mode_buf,"6G3L") ||
			 !strcmp(mode_buf,"6"))
	{
		ret = HDMI_PHY_INITIATED_FRL_6G_3L;
	}
	else if( !strcmp(mode_buf,"6g4l") ||
			 !strcmp(mode_buf,"6G4L") ||
			 !strcmp(mode_buf,"7"))
	{
		ret = HDMI_PHY_INITIATED_FRL_6G_4L;
	}
	else if( !strcmp(mode_buf,"8g4l") ||
			 !strcmp(mode_buf,"8G4L") ||
			 !strcmp(mode_buf,"8"))
	{
		ret = HDMI_PHY_INITIATED_FRL_8G_4L;
	}
	else if( !strcmp(mode_buf,"10g4l") ||
			 !strcmp(mode_buf,"10G4L") ||
			 !strcmp(mode_buf,"9"))
	{
		ret = HDMI_PHY_INITIATED_FRL_10G_4L;
	}
	else if( !strcmp(mode_buf,"12g4l") ||
			 !strcmp(mode_buf,"12G4L") ||
			 !strcmp(mode_buf,"10"))
	{
		ret = HDMI_PHY_INITIATED_FRL_12G_4L;
	}
	else if( !strcmp(mode_buf,"10gcts") ||
			 !strcmp(mode_buf,"10GCTS") ||
			 !strcmp(mode_buf,"11")){
		ret = HDMI_PHY_INITIATED_FRL_10G_CTS;
	}
	else if( !strcmp(mode_buf,"12gcts") ||
			 !strcmp(mode_buf,"12GCTS") ||
			 !strcmp(mode_buf,"12")){
		ret = HDMI_PHY_INITIATED_FRL_12G_CTS;
	}
	else if( !strcmp(mode_buf,"a") ||
			 !strcmp(mode_buf, "A") ||
			 !strcmp(mode_buf, "all") ||
			 !strcmp(mode_buf, "ALL") ||
			 !strcmp(mode_buf, "13"))
	{
		ret = HDMI_PHY_INITIATED_MAXNUM;
	}
	else
	{
		ret = HDMI_PHY_INITIATED_ERROR;
	}
	return ret;
}

//TODO: need to determine soc
int		HDMI20_DevCtrl_PrintPhyRegTable(struct seq_file *m)
{
	int ret = 0;

	int i,j;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
		for(i=I2C_CON_SEL_MODE_O26A0; i<PHY_REG_MAX_NUM_O26A0;i++)
		{
			if(i%50 == 0)
				Print_RegTableIndex(m);
			seq_printf(m, "[#%03d]. [%-30s] : ", i, o26a0_phy_reg_table[i].index);
			for(j=HDMI_PHY_INITIATED_3G_M0; j<HDMI_PHY_INITIATED_MAXNUM; j++){
				seq_printf(m, "|  0x%02x ", o26a0_phy_reg_table[i].reg_val[j]);
			}
			seq_printf(m, "| %s\n", o26a0_phy_reg_table[i].desc);
		}
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
		for(i=I2C_CON_SEL_MODE_O24A0; i<PHY_REG_MAX_NUM_O24A0;i++)
		{
			if(i%50 == 0)
				Print_RegTableIndex(m);
			seq_printf(m, "[#%03d]. [%-30s] : ", i, o24a0_phy_reg_table[i].index);
			for(j=HDMI_PHY_INITIATED_3G_M0; j<HDMI_PHY_INITIATED_MAXNUM; j++){
				seq_printf(m, "|  0x%02x ", o24a0_phy_reg_table[i].reg_val[j]);
			}
			seq_printf(m, "| %s\n", o24a0_phy_reg_table[i].desc);
		}
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		for(i=I2C_CON_SEL_MODE_M23A0; i<PHY_REG_MAX_NUM_M23A0;i++)
		{
			if(i%50 == 0)
				Print_RegTableIndex(m);
			seq_printf(m, "[#%03d]. [%-30s] : ", i, m23a0_phy_reg_table[i].index);
			for(j=HDMI_PHY_INITIATED_3G_M0; j<HDMI_PHY_INITIATED_FRL_3G_3L; j++){
				seq_printf(m, "|  0x%02x ", m23a0_phy_reg_table[i].reg_val[j]);
			}
			seq_printf(m, "| %s\n", m23a0_phy_reg_table[i].desc);
		}
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)){
		for(i=I2C_CON_SEL_MODE_O22A0; i<PHY_REG_MAX_NUM_O22A0;i++)
		{
			if(i%50 == 0)
				Print_RegTableIndex(m);
			seq_printf(m, "[#%03d]. [%-30s] : ", i, o22a0_phy_reg_table[i].index);
			for(j=HDMI_PHY_INITIATED_3G_M0; j<HDMI_PHY_INITIATED_MAXNUM; j++){
				seq_printf(m, "|  0x%02x ", o22a0_phy_reg_table[i].reg_val[j]);
			}
			seq_printf(m, "| %s\n", o22a0_phy_reg_table[i].desc);
		}
	}
	return ret;
}

//useage: echo index value mode > table
//TODO: need to determine soc
int		HDMI20_DevCtrl_WritePhyRegTable(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	int ret = 0;
	char cmd_buf[64];
	int index = 0;
	HDMI_PHY_INIT_MODE_T mode = 0;
	char mode_buf[10]={'\0',};
	int  mode_num = -1;
	UINT32 value;
	int i;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmd_buf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmd_buf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	cmd_buf[size-1] = 0;

#if 0
	if( ret = sscanf(cmd_buf, "%d 0x%x %s", &index, &value, mode_buf) != 3 ){
		if( ret = sscanf(cmd_buf, "%d 0x%x %d", &index, &value, &mode_num) != 3 ) {
			memset(mode_buf, 0x0, sizeof(mode_buf));
			printk("\nUsage: echo [index] [value] [mode] > devctrl/table\n");
			return 0;
		}
	}
#endif
	if( (ret = sscanf(cmd_buf, "%s %d 0x%x", mode_buf, &index,  &value)) != 3 ){
		if( (ret = sscanf(cmd_buf, "%d %d 0x%x", &mode_num, &index, &value)) != 3 ) {
			memset(mode_buf, 0x0, sizeof(mode_buf));
			printk("\nUsage: echo [mode] [index] [value] > table\n");
			return 0;
		}
	}

	if(lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {

		if( index < I2C_CON_SEL_MODE_O26A0 || index > PHY_REG_MAX_NUM_O26A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}

		mode = Get_PhyInitMode(mode_buf, mode_num);
		if( mode != HDMI_PHY_INITIATED_ERROR )
		{
			if( mode == HDMI_PHY_INITIATED_MAXNUM )
			{
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_MAXNUM; i++)
				{
					o26a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else
			{
				o26a0_phy_reg_table[index].reg_val[mode] = value;
			}
		}
		else
		{
			printk("Invalid phy-initiated mode..!\n");
		}

	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV(O24, A0)) {

		if( index < I2C_CON_SEL_MODE_O24A0 || index > PHY_REG_MAX_NUM_O24A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}

		mode = Get_PhyInitMode(mode_buf, mode_num);
		if( mode != HDMI_PHY_INITIATED_ERROR )
		{
			if( mode == HDMI_PHY_INITIATED_MAXNUM )
			{
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_MAXNUM; i++)
				{
					o24a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else
			{
				o24a0_phy_reg_table[index].reg_val[mode] = value;
			}
		}
		else
		{
			printk("Invalid phy-initiated mode..!\n");
		}

	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV(M23, A0)) {
		if( index < I2C_CON_SEL_MODE_M23A0 || index > PHY_REG_MAX_NUM_M23A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}

		mode = Get_PhyInitMode(mode_buf, mode_num);
		if( mode != HDMI_PHY_INITIATED_ERROR )
		{
			if( mode == HDMI_PHY_INITIATED_MAXNUM )
			{
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_FRL_3G_3L; i++)
				{
					m23a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else
			{
				m23a0_phy_reg_table[index].reg_val[mode] = value;
			}
		}
		else
		{
			printk("Invalid phy-initiated mode..!\n");
		}
	}
	else if(lx_chip_rev( ) >= LX_CHIP_REV(O22, A0)) {

		if( index < I2C_CON_SEL_MODE_O22A0 || index > PHY_REG_MAX_NUM_O22A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}

		mode = Get_PhyInitMode(mode_buf, mode_num);
		if( mode != HDMI_PHY_INITIATED_ERROR )
		{
			if( mode == HDMI_PHY_INITIATED_MAXNUM )
			{
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_MAXNUM; i++)
				{
					o22a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else
			{
				o22a0_phy_reg_table[index].reg_val[mode] = value;
			}
		}
		else
		{
			printk("Invalid phy-initiated mode..!\n");
		}

	}

	return ret;
}

int		HDMI20_DevCtrl_ReadPhyRegTableMode(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	int ret = 0;
	char cmd_buf[64];
	char mode_buf[10]={'\0',};

	HDMI_PHY_INIT_MODE_T mode = 0;
	int  mode_num = -1;
	int i;

	//Sanity Check
	if( size == 0 || *off != 0 || size>sizeof(cmd_buf)-1 ){
		printk("[%d:%s] Invalid parameter..!\n", __LINE__, __func__);
		return -1;
	}

	if( copy_from_user(cmd_buf, buf, size) > 0 ){
		printk("[%d:%s] cpy_from_user error.!\n", __LINE__, __func__);
		return -1;
	}

	cmd_buf[size-1] = 0;

	ret = sscanf(cmd_buf, "%s", mode_buf);
	if(ret != 1 ) {
		printk("\n Usage: echo [Mode] > read_table \n");
		printk("e.g.,) echo 10g4l > read_table \n");
	}

	mode = Get_PhyInitMode(mode_buf, mode_num);
	if( mode != HDMI_PHY_INITIATED_ERROR && mode != HDMI_PHY_INITIATED_MAXNUM ){
		if(lx_chip_rev( ) >= LX_CHIP_REV(O26,A0)) {
			for(i=I2C_CON_SEL_MODE_O26A0; i<PHY_REG_MAX_NUM_O26A0;i++)
			{
				if( i%50 == 0)
				{
					printk("==============================================================================\n");
					printk("[ idx]. [%-30s] : [%-6s] | [desc] \n", "reg_name", mode_buf);
					printk("==============================================================================\n");

				}
				printk( "[#%03d]. [%-30s] : ", i, o26a0_phy_reg_table[i].index);
				printk( "|  0x%02x ", o26a0_phy_reg_table[i].reg_val[mode]);
				printk("| %s\n", o26a0_phy_reg_table[i].desc);
			}
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV(O24,A0)) {
			for(i=I2C_CON_SEL_MODE_O24A0; i<PHY_REG_MAX_NUM_O24A0;i++)
			{
				if( i%50 == 0)
				{
					printk("==============================================================================\n");
					printk("[ idx]. [%-30s] : [%-6s] | [desc] \n", "reg_name", mode_buf);
					printk("==============================================================================\n");

				}
				printk( "[#%03d]. [%-30s] : ", i, o24a0_phy_reg_table[i].index);
				printk( "|  0x%02x ", o24a0_phy_reg_table[i].reg_val[mode]);
				printk("| %s\n", o24a0_phy_reg_table[i].desc);
			}
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV(M23,A0)) {
			for(i=I2C_CON_SEL_MODE_M23A0; i<PHY_REG_MAX_NUM_M23A0;i++)
			{
				if( i%50 == 0)
				{
					printk("==============================================================================\n");
					printk("[ idx]. [%-30s] : [%-6s] | [desc] \n", "reg_name", mode_buf);
					printk("==============================================================================\n");

				}
				printk( "[#%03d]. [%-30s] : ", i, m23a0_phy_reg_table[i].index);
				printk( "|  0x%02x ", m23a0_phy_reg_table[i].reg_val[mode]);
				printk("| %s\n", m23a0_phy_reg_table[i].desc);
			}
		}
		else if(lx_chip_rev( ) >= LX_CHIP_REV(O22,A0)) {
			for(i=I2C_CON_SEL_MODE_O22A0; i<PHY_REG_MAX_NUM_O22A0;i++)
			{
				if( i%50 == 0)
				{
					printk("==============================================================================\n");
					printk("[ idx]. [%-30s] : [%-6s] | [desc] \n", "reg_name", mode_buf);
					printk("==============================================================================\n");

				}
				printk( "[#%03d]. [%-30s] : ", i, o22a0_phy_reg_table[i].index);
				printk( "|  0x%02x ", o22a0_phy_reg_table[i].reg_val[mode]);
				printk("| %s\n", o22a0_phy_reg_table[i].desc);
			}
		}
	} else {
		printk("Input phy-mode is error or maxnum.\n");
	}

	return ret;
}

int		HDMI20_DevCtrl_WritePhyRegTableMode(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	int ret = 0;
	char cmd_buf[64];
	char mode_buf[10]={'\0',};

	int index = 0;
	HDMI_PHY_INIT_MODE_T mode = 0;
	int  mode_num = -1;
	UINT32 value;
	int i;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return 0;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return 0;
	}

	if(size>sizeof(cmd_buf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return 0;
	}

	if(copy_from_user(cmd_buf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return 0;
	}

	cmd_buf[size-1] = 0;

	ret = sscanf(cmd_buf, "%s %d 0x%x", mode_buf, &index, &value);
	if(ret != 3) {
		printk("\n Usage: [Mode] [index] [value] \n");
		printk(" e.g.,) echo 10g4l 190  0xXX > write_table \n");
		return 0;
	}

	if( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0) ){
		if( index < I2C_CON_SEL_MODE_O26A0 || index > PHY_REG_MAX_NUM_O26A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O24, A0) ){
		if( index < I2C_CON_SEL_MODE_O24A0 || index > PHY_REG_MAX_NUM_O24A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		if( index < I2C_CON_SEL_MODE_M23A0 || index > PHY_REG_MAX_NUM_M23A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O22, A0) ){
		if( index < I2C_CON_SEL_MODE_O22A0 || index > PHY_REG_MAX_NUM_O22A0 )
		{
			printk("Invalid APB index num..!\n");
			return -1;
		}
	}
	else {
		printk("Unsupported Chip\n");
		return -1;
	}

	mode = Get_PhyInitMode(mode_buf, mode_num);
	if( mode != HDMI_PHY_INITIATED_ERROR ){
		if( mode == HDMI_PHY_INITIATED_MAXNUM )
		{
			if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_MAXNUM; i++)
				{
					o26a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_MAXNUM; i++)
				{
					o24a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_FRL_3G_3L; i++)
				{
					m23a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
			else{ 
				for(i=HDMI_PHY_INITIATED_3G_M0; i<HDMI_PHY_INITIATED_MAXNUM; i++)
				{
					o22a0_phy_reg_table[index].reg_val[i] = value;
				}
			}
		}
		else
		{
			if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
				o26a0_phy_reg_table[index].reg_val[mode] = value;
			}
			else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
				o24a0_phy_reg_table[index].reg_val[mode] = value;
			}
			else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
				m23a0_phy_reg_table[index].reg_val[mode] = value;
			}
			else {
				o22a0_phy_reg_table[index].reg_val[mode] = value;
			}	
		}
		printk("Writing new value is success.!\n");
	} else {
		printk("Invalid phy-initiated mode..!\n");
	}

	return ret;
}


EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_HlcReset);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_HlcAuthenticate);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_Close);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_Open);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_GetRepeater);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_SetRepeater);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_GetRxId);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_SetRxId);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_TestApp);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_HlcMonitor);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_LogDump);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_GetEsmLog);
EXPORT_SYMBOL( HDMI21_Module_Set_EsmOfDmaConfigure);
EXPORT_SYMBOL( HDMI21_Module_Set_RegisterCB_GetContentType);

