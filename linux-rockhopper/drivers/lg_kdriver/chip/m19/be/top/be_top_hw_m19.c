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
 *	BE TOP module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/vmalloc.h>
#include "os_util.h"

#include "be_dbg.h"
#include "be_cfg.h"
#include "be_def.h"
#include "../fwi/ipc_def_m19.h"
#include "ipc_drv.h"
#include "be_top_hw_m19.h"

// For CTOP/DPE register access
#include "../../../core/sys/sys_regs.h"
#include "../reg/be_reg_dpe_m19.h"

#include "ipc_cmd_header.h"

// For Video InputLag Test
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>

#include "../gpio/gpio_drv.h"
#include "../gpio/gpio_core.h"

// For Status Management
#include "../../../core/be/video_status_keeper.h"

#include "../../../core/de/de_sync.h"
#include "../../../core/gpio/gpio_drv.h"
#include "../../../core/gpio/gpio_core.h"
#include "../../../core/de/hal/ipc_phys_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define BE_TOP_HW_M19_LSR_TABLE_OFFSET 0x0
#define BE_TOP_HW_M19_GSR_TABLE_OFFSET (BE_TOP_HW_M19_LSR_TABLE_OFFSET + 0x800)
#define BE_TOP_HW_M19_OSD_ALPHA_TABLE_OFFSET (BE_TOP_HW_M19_GSR_TABLE_OFFSET + 0x800)

#define BE_TOP_HW_M19_TEST_INPUT_LAG
#ifdef BE_TOP_HW_M19_TEST_INPUT_LAG
#define	BE_TOP_HW_M19_IPP_PIXEL_CTRL_BASE		(0xC9014448)
#define	BE_TOP_HW_M19_CVI_WIN_X_CTRL_BASE		(0xC9000268)
#define	BE_TOP_HW_M19_CVI_WIN_Y_CTRL_BASE		(0xC900026C)
#define	BE_TOP_HW_M19_CVI_PIXEL_CTRL_BASE		(0xC9000284)
#define	BE_TOP_HW_M19_CVI_OFFSET_BASE			(0xC9000248)
#define	BE_TOP_HW_M19_CVI_CSC_OFFSET_BASE		(0xC900023C)
#define BE_TOP_HW_M19_PATTERN_OFF		(0)
#define BE_TOP_HW_M19_PATTERN_ON		(1)
#define BE_TOP_HW_M19_PATTERN_BLACK		(0)
#define BE_TOP_HW_M19_PATTERN_WHITE		(1)
//#define BE_TOP_HW_M19_PATTERN_OFF		(0)
//#define BE_TOP_HW_M19_PATTERN_WHITE		(1)
//#define BE_TOP_HW_M19_PATTERN_BLACK		(2)
//#define BE_TOP_HW_M19_PIN_MUX_PORT		(119)
//#define BE_TOP_HW_M19_PIN_NORMAL		(0)
//#define BE_TOP_HW_M19_PIN_GPIO			(1)
#endif

/* For register direct access
 * 2013-10-14 chobits : Need to change this ...*/

static volatile unsigned int *gMapped_address;
#define BE_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define BE_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                             0xc9000268L pix_sum_ctrl0
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	start_pos_x                        :13,	// 12:0
	reserved01                         :2 ,	// reserved
	pix_sum_enable                     :1 ,	// 15
	end_pos_x                          :13,	// 28:16
	field_selection                    :2 ,	// 30:29
	debug_enable                       :1 ;	// 31
}BE_TOP_HW_M19_PIX_SUM_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900026cL pix_sum_ctrl1
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	start_pos_y                        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	end_pos_y                          :13;	// 28:16
}BE_TOP_HW_M19_PIX_SUM_CTRL1_T;

/*-----------------------------------------------------------------------------
                             0xc9000284L pix_sum_ctrl2
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fill_color_r                       :10,	// 9:0
	fill_color_b                       :10,	// 19:10
	fill_color_g                       :10,	// 29:20
	reserved01                         :1 ,	// reserved
	fill_en                            :1 ;	// 31
}BE_TOP_HW_M19_PIX_SUM_CTRL2_T;

/*-----------------------------------------------------------------------------
                             0xc9000248L offset_read
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset_read                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	voffset_read                       :13;	// 28:16
}BE_TOP_HW_M19_OFFSET_READ_T;

/*-----------------------------------------------------------------------------
                             0xc900023cL csc_ctrl6
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_offset4                        :11,	// 10:0
	reserved01                         :5 ,	// reserved
	csc_offset3                        :11;	// 26:16
}BE_TOP_HW_M19_PIX_SUM_CTRL6_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern BE_MEM_CFG_T *gpBeMem;
extern DPE_LED_REG_M19_T gDPE_LED_M19;
extern PE_OSD_REG_M19_T gPE_OSD_M19;

extern struct gpio_desc *gpiod_de;
extern struct device de_gpio_dev;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 gInputLagCnt_M19 = 0;
volatile UINT32 *gIPP_PIXEL_CTRL_M19 = NULL;

volatile BE_TOP_HW_M19_PIX_SUM_CTRL0_T *gBE_TOP_HW_M19_PIX_SUM_CTRL0 = NULL;
volatile BE_TOP_HW_M19_PIX_SUM_CTRL1_T *gBE_TOP_HW_M19_PIX_SUM_CTRL1 = NULL;
volatile BE_TOP_HW_M19_PIX_SUM_CTRL2_T *gBE_TOP_HW_M19_PIX_SUM_CTRL2 = NULL;
volatile BE_TOP_HW_M19_PIX_SUM_CTRL6_T *gBE_TOP_HW_M19_PIX_SUM_CTRL6 = NULL;
volatile BE_TOP_HW_M19_OFFSET_READ_T   *gBE_TOP_HW_M19_OFFSET_READ   = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef BE_TOP_HW_M19_TEST_INPUT_LAG
int BE_TOP_HW_M19_InputLagHandler(void);
//static int BE_TOP_HW_M19_SetPattern(UINT32 bOnOff);
//static int BE_TOP_HW_M19_SetGpioValue(UINT32 value);
//static int BE_TOP_HW_M19_SetGpioMux(UINT32 value);
static int BE_TOP_HW_M19_InitLagPattern(void);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 g_be_top_hw_m19_pattern_init = 0;
static LX_BE_INPUT_LAG_PATTERN_T gCurPatternParam;
static LX_BE_INPUT_LAG_PATTERN_T gPrePatternParam;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_TOP_HW_M19_Initialize(void)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;

	do {
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_WR(0xC901102C, pFwMem->fw_base + BE_TOP_HW_M19_OSD_ALPHA_TABLE_OFFSET);

	} while(0);

	return ret;
}

int BE_TOP_HW_M19_Resume(void)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;

	do {
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_WR(0xC901102C, pFwMem->fw_base + BE_TOP_HW_M19_OSD_ALPHA_TABLE_OFFSET);

	} while(0);

	return ret;
}


int BE_TOP_HW_M19_Close(void)
{
	int ret = RET_OK;

	do {

	} while(0);

	return ret;
}

int BE_TOP_HW_M19_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLOCK_BYPASS_T, stHwParams);

		if (pstParams->bLEDBypass <= 1)
		{
			DPE_LED_M19_RdFL(led_led_detour);
			if (pstParams->bLEDBypass)
			{
				DPE_LED_M19_Wr01(led_led_detour, led_detour, 0x1);
			}
			else
			{
				DPE_LED_M19_Wr01(led_led_detour, led_detour, 0x0);
			}
			DPE_LED_M19_WrFL(led_led_detour);
		}

		/* change value LX_BE to BE_IPC */
		stHwParams.uH3DBypass = (pstParams->bH3DBypass > 1) ? 0xFFFFFFFF : pstParams->bH3DBypass;
		stHwParams.uFRCBypass = (pstParams->bFRCBypass > 1) ? 0xFFFFFFFF : pstParams->bFRCBypass;
		stHwParams.uWCGBypass = (pstParams->bWCGBypass > 1) ? 0xFFFFFFFF : pstParams->bWCGBypass;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLOCK_BYPASS), (void*)&stHwParams, sizeof(BE_IPC_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M19_Toggle3DLR(LX_BE_3D_LR_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_3D_LR_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bOutLR = (pstParams->bOutLR == 0xFFFF) ? 0xFFFFFFFF : pstParams->bOutLR;

		/* Video Status */
		status = stHwParams.bOutLR;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_LR_TOGGLE, status);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_TOGGLE_3D_LR), (void*)&stHwParams, sizeof(BE_IPC_3D_LR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M19_Set3DConvergence(LX_BE_3D_CONVERGENCE_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_3D_CONVERGENCE_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bTDConvEnable = pstParams->u16ConvergenceEnable == 0xFFFF ? 0xFFFFFFFF : pstParams->u16ConvergenceEnable;
		stHwParams.uTDConvVal = pstParams->u16ConvergenceVal == 0xFFFF ? 0xFFFFFFFF : pstParams->u16ConvergenceVal;

		/* Video Status */
		status = (0xFFFF0000&(stHwParams.bTDConvEnable <<16))|(0x0000FFFF&(stHwParams.uTDConvVal));
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_CONVERGENCE, status);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_3D_CONVERGENCE), (void *)&stHwParams, sizeof(BE_IPC_3D_CONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M19_SetBlackBar(LX_BE_BLACK_BAR_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLACK_BAR_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uTDBlackBarEnable = pstParams->u8BarOn == 0xFF ? 0xFFFFFFFF : pstParams->u8BarOn;
		stHwParams.uTDBlackBarVal = pstParams->u8BarVal == 0xFF ? 0xFFFFFFFF : pstParams->u8BarVal;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLACK_BAR), (void *)&stHwParams, sizeof(BE_IPC_BLACK_BAR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M19_SetRealCinema(LX_BE_REAL_CINEMA_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_REAL_CINEMA_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uRealCinemaEnable = pstParams->u32RealCinemaEnable;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_REAL_CINEMA), (void *)&stHwParams, sizeof(BE_IPC_REAL_CINEMA_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M19_SetOrbit(LX_BE_ORBIT_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_ORBIT_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bOrbitEnable = pstParams->bOnOff >= 0xFF ? 0xFFFFFFFF : pstParams->bOnOff;
		stHwParams.bAutoMode = pstParams->bAutoMode >= 0xFF ? 0xFFFFFFFF : pstParams->bAutoMode;
		stHwParams.bOsdOverscan = pstParams->bOsdOverscan >= 0xFF ? 0xFF : pstParams->bOsdOverscan;
		stHwParams.bStoreMode = pstParams->bStoreMode >= 0xFF ? 0xFF : pstParams->bStoreMode;
		stHwParams.bPartialFrameMode = pstParams->bPartialFrameMode >= 0xFF ? 0xFF : pstParams->bPartialFrameMode;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_ORBIT), (void *)&stHwParams, sizeof(BE_IPC_ORBIT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

#ifdef BE_TOP_HW_M19_TEST_INPUT_LAG
static int BE_TOP_HW_M19_InitLagPattern(void)
{
	gBE_TOP_HW_M19_PIX_SUM_CTRL0 = (volatile BE_TOP_HW_M19_PIX_SUM_CTRL0_T *)ioremap(BE_TOP_HW_M19_CVI_WIN_X_CTRL_BASE, sizeof(BE_TOP_HW_M19_PIX_SUM_CTRL0_T));
	gBE_TOP_HW_M19_PIX_SUM_CTRL1 = (volatile BE_TOP_HW_M19_PIX_SUM_CTRL1_T *)ioremap(BE_TOP_HW_M19_CVI_WIN_Y_CTRL_BASE, sizeof(BE_TOP_HW_M19_PIX_SUM_CTRL1_T));
	gBE_TOP_HW_M19_PIX_SUM_CTRL2 = (volatile BE_TOP_HW_M19_PIX_SUM_CTRL2_T *)ioremap(BE_TOP_HW_M19_CVI_PIXEL_CTRL_BASE, sizeof(BE_TOP_HW_M19_PIX_SUM_CTRL2_T));
	gBE_TOP_HW_M19_PIX_SUM_CTRL2 = (volatile BE_TOP_HW_M19_PIX_SUM_CTRL2_T *)ioremap(BE_TOP_HW_M19_CVI_PIXEL_CTRL_BASE, sizeof(BE_TOP_HW_M19_PIX_SUM_CTRL2_T));
	gBE_TOP_HW_M19_OFFSET_READ   = (volatile BE_TOP_HW_M19_OFFSET_READ_T *)ioremap(BE_TOP_HW_M19_CVI_OFFSET_BASE, sizeof(BE_TOP_HW_M19_OFFSET_READ_T));
	gBE_TOP_HW_M19_PIX_SUM_CTRL6 = (volatile BE_TOP_HW_M19_PIX_SUM_CTRL6_T *)ioremap(BE_TOP_HW_M19_CVI_CSC_OFFSET_BASE, sizeof(BE_TOP_HW_M19_PIX_SUM_CTRL6_T));

	/* move to below line to init(to get gpiod_de only one time */
	gpiod_de = gpiod_get(&de_gpio_dev, "119", GPIOD_OUT_HIGH);

	gPrePatternParam.enable = BE_TOP_HW_M19_PATTERN_OFF;
	gPrePatternParam.type = 0xff;
	gPrePatternParam.hoffset = 0;
	gPrePatternParam.voffset = 0;
	gPrePatternParam.hsize = 0;
	gPrePatternParam.vsize = 0;

	return RET_OK;
}
int BE_TOP_HW_M19_SetLagPatternParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams)
{
	int ret = RET_OK;
	UINT32 cur_enable,pre_enable;
	BE_TOP_HW_M19_PIX_SUM_CTRL0_T	pix_sum_ctrl0;	//0x0068
	BE_TOP_HW_M19_PIX_SUM_CTRL1_T	pix_sum_ctrl1;	//0x006C
	BE_TOP_HW_M19_OFFSET_READ_T		offset_read;	//0x0048

	if (pstParams == NULL)
	{
		BE_ERROR("pstParams is NULL");
		return RET_ERROR;
	}

	BE_NOTI("init:%d, bOnOff[%d] bPatternType[%d] rect[%d/%d/%d/%d]\n",\
		g_be_top_hw_m19_pattern_init,pstParams->enable,pstParams->type,\
		pstParams->hoffset,pstParams->voffset,pstParams->hsize,pstParams->vsize);

	if (!g_be_top_hw_m19_pattern_init)
	{
		BE_TOP_HW_M19_InitLagPattern();
		g_be_top_hw_m19_pattern_init = 1;
	}

	gCurPatternParam = *pstParams;
	cur_enable = gCurPatternParam.enable;
	pre_enable = gPrePatternParam.enable;

	do {
		if (pre_enable == cur_enable)		break;
		if (cur_enable == BE_TOP_HW_M19_PATTERN_ON)
		{
			/* interrupt enable */
			ipc_phys_hal_InitInterrupt(0, TRUE);
			gPrePatternParam.type = 0xff;
			/* register handle */
			de_srcsync_register(TRUE, BE_TOP_HW_M19_InputLagHandler, "inputLag_handler");
			BE_NOTI("START\n");
		}
		else
		{
			/* unregister handle */
			de_srcsync_register(FALSE, BE_TOP_HW_M19_InputLagHandler, "inputLag_handler");
			/* interrupt disable */
			ipc_phys_hal_InitInterrupt(0, FALSE);
			BE_NOTI("END\n");
		}
		gPrePatternParam.enable = gCurPatternParam.enable;
	} while(0);

	do {
		CHECK_KNULL(gBE_TOP_HW_M19_OFFSET_READ);
		CHECK_KNULL(gBE_TOP_HW_M19_PIX_SUM_CTRL0);
		CHECK_KNULL(gBE_TOP_HW_M19_PIX_SUM_CTRL1);

		if (cur_enable == BE_TOP_HW_M19_PATTERN_ON)
		{
			offset_read = *gBE_TOP_HW_M19_OFFSET_READ;

			pix_sum_ctrl0 = *gBE_TOP_HW_M19_PIX_SUM_CTRL0;
			pix_sum_ctrl0.pix_sum_enable = 1;
			pix_sum_ctrl0.debug_enable = 1;
			pix_sum_ctrl0.start_pos_x = pstParams->hoffset + offset_read.hoffset_read;
			pix_sum_ctrl0.end_pos_x = pstParams->hoffset + pstParams->hsize + offset_read.hoffset_read;
			*gBE_TOP_HW_M19_PIX_SUM_CTRL0 = pix_sum_ctrl0;

			pix_sum_ctrl1 = *gBE_TOP_HW_M19_PIX_SUM_CTRL1;
			pix_sum_ctrl1.start_pos_y = pstParams->voffset + offset_read.voffset_read;
			pix_sum_ctrl1.end_pos_y = pstParams->voffset + pstParams->vsize + offset_read.voffset_read;
			*gBE_TOP_HW_M19_PIX_SUM_CTRL1 = pix_sum_ctrl1;

			BE_NOTI("1. %d = %d + %d\n",pix_sum_ctrl0.start_pos_x, pstParams->hoffset,offset_read.hoffset_read);
			BE_NOTI("1. %x = %x + %x\n",pix_sum_ctrl0.start_pos_x, pstParams->hoffset,offset_read.hoffset_read);
			BE_NOTI("2. %d = %d + %d + %d\n",pix_sum_ctrl0.end_pos_x,pstParams->hoffset,pstParams->hsize,offset_read.hoffset_read);
			BE_NOTI("2. %x = %x + %x + %x\n",pix_sum_ctrl0.end_pos_x,pstParams->hoffset,pstParams->hsize,offset_read.hoffset_read);
			BE_NOTI("3. %d = %d + %d\n",pix_sum_ctrl1.start_pos_y,pstParams->voffset,offset_read.voffset_read);
			BE_NOTI("3. %x = %x + %x\n",pix_sum_ctrl1.start_pos_y,pstParams->voffset,offset_read.voffset_read);
			BE_NOTI("4. %d = %d + %d + %d\n",pix_sum_ctrl1.end_pos_y,pstParams->voffset,pstParams->vsize,offset_read.voffset_read);
			BE_NOTI("4. %x = %x + %x + %x\n",pix_sum_ctrl1.end_pos_y,pstParams->voffset,pstParams->vsize,offset_read.voffset_read);
		}
		else
		{
			pix_sum_ctrl0 = *gBE_TOP_HW_M19_PIX_SUM_CTRL0;
			pix_sum_ctrl0.pix_sum_enable = 0;
			pix_sum_ctrl0.debug_enable = 0;
			*gBE_TOP_HW_M19_PIX_SUM_CTRL0 = pix_sum_ctrl0;
		}
	} while(0);

	return ret;
}

int BE_TOP_HW_M19_InputLagHandler(void)
{
	int ret = RET_OK;
	UINT32 cur_enable,cur_type,pre_type;
	static UINT64 prev_msec_tick = 0;
	UINT64 curr_msec_tick = 0, tick_diff = 0;
	BE_TOP_HW_M19_PIX_SUM_CTRL2_T	pix_sum_ctrl2;	//0x0084
	BE_TOP_HW_M19_PIX_SUM_CTRL6_T	csc_offset;		//0x003C
	LX_GPIO_VALUE_T gpio_value = LX_GPIO_VALUE_INVALID;
	static UINT32 gpio_cnt = 0;

	cur_enable = gCurPatternParam.enable;
	cur_type = gCurPatternParam.type;
	pre_type = gPrePatternParam.type;

	if (cur_enable != BE_TOP_HW_M19_PATTERN_ON)
	{
		BE_NOTI("en:%d, type:%d <- %d return",cur_enable,cur_type,pre_type);
		return RET_OK;
	}

	curr_msec_tick = OS_GetMsecTicks();
	tick_diff = curr_msec_tick - prev_msec_tick;

	BE_TRACE1("type:%d <- %d, tick diff:%llu (%llu <- %llu)",\
		cur_type,pre_type,tick_diff,curr_msec_tick,prev_msec_tick);

	if (tick_diff < 5)
	{
		BE_NOTI("type:%d <- %d, tick diff:%llu (%llu <- %llu) return",\
			cur_type,pre_type,tick_diff,curr_msec_tick,prev_msec_tick);
		return RET_OK;
	}

	prev_msec_tick = curr_msec_tick;

	do {
		CHECK_KNULL(gBE_TOP_HW_M19_PIX_SUM_CTRL6);
		CHECK_KNULL(gBE_TOP_HW_M19_PIX_SUM_CTRL2);
		CHECK_KNULL(gpiod_de);
		if (pre_type == cur_type)		break;

		csc_offset = *gBE_TOP_HW_M19_PIX_SUM_CTRL6;
		pix_sum_ctrl2 = *gBE_TOP_HW_M19_PIX_SUM_CTRL2;
		pix_sum_ctrl2.fill_en = 1;
		if (cur_type == BE_TOP_HW_M19_PATTERN_WHITE) //white pattern
		{
			if (csc_offset.csc_offset4 == 0)
			{
				pix_sum_ctrl2.fill_color_g = 1023;
				pix_sum_ctrl2.fill_color_b = 512;
				pix_sum_ctrl2.fill_color_r = 512;
			}
			else
			{
				pix_sum_ctrl2.fill_color_g = 1023;
				pix_sum_ctrl2.fill_color_b = 1023;
				pix_sum_ctrl2.fill_color_r = 1023;
			}
		}
		else	//black pattern
		{
			if (csc_offset.csc_offset4 == 0)
			{
				pix_sum_ctrl2.fill_color_g = 1;
				pix_sum_ctrl2.fill_color_b = 512;
				pix_sum_ctrl2.fill_color_r = 512;
			}
			else
			{
				pix_sum_ctrl2.fill_color_g = 0;
				pix_sum_ctrl2.fill_color_b = 0;
				pix_sum_ctrl2.fill_color_r = 0;
			}
		}
		*gBE_TOP_HW_M19_PIX_SUM_CTRL2 = pix_sum_ctrl2;
		gPrePatternParam.type = gCurPatternParam.type;
		gpio_cnt = 5;
		BE_NOTI("type changed:%d <- %d, gpio:%d, tick diff:%llu (%llu <- %llu), gpio_cnt: %d",\
			cur_type,pre_type,gpio_value,tick_diff,curr_msec_tick,prev_msec_tick,gpio_cnt);
	} while(0);

	if (gpio_cnt == 4)
	{
		gpiod_set_raw_value(gpiod_de, (cur_type == BE_TOP_HW_M19_PATTERN_WHITE)? 1:0);
		gpio_value = gpiod_get_raw_value(gpiod_de);
		BE_NOTI("GPIO_Set --> gpio_cnt: %d",gpio_cnt);
		#if 0	//legacy
		if (cur_type == 0) //Blck pattern
		{
			BE_NOTI("gpiod_de return %d", gpiod_de);
			gpiod_set_raw_value(gpiod_de ,(cur_type == 0)? 0:1);
			gpio_value = gpiod_get_raw_value(gpiod_de);
			//BE_NOTI("SET_GPIO %d ", gpio_value?"HIGH":"LOW");
		}
		else	//white pattern
		{
			BE_NOTI("gpiod_de return %d", gpiod_de);
			gpiod_set_raw_value(gpiod_de ,1);
			gpio_value = gpiod_get_raw_value(gpiod_de);
			//BE_NOTI("SET_GPIO %d ", gpio_value?"HIGH":"LOW");
		}
		#endif
	}

	if (gpio_cnt > 0) gpio_cnt--;

	return RET_OK;
}
#endif

#if 0	//not used
// bOnOff: 0:off, 1:white, 2. black
static int BE_TOP_HW_M19_SetPattern(UINT32 bOnOff)
{
	if (bOnOff == BE_TOP_HW_M19_PATTERN_WHITE)
	{
		*gIPP_PIXEL_CTRL_M19 = 0x80FF8080;
	}
	else if (bOnOff == BE_TOP_HW_M19_PATTERN_BLACK)
	{
		*gIPP_PIXEL_CTRL_M19 = 0x80008080;
	}
	else //OFF BE_TOP_HW_M19_PATTERN_OFF
	{
		*gIPP_PIXEL_CTRL_M19 = 0x00008080;
	}
	return 0;
}

static int BE_TOP_HW_M19_SetGpioValue(UINT32 value)
{
//	GPIO_DevSetValue(BE_TOP_HW_M19_PIN_MUX_PORT, value);
//	GPIO_DevExSetValue(BE_TOP_HW_M19_PIN_MUX_PORT, value);

	return 0;
}

static int BE_TOP_HW_M19_SetGpioMux(UINT32 value)
{
//	GPIO_DevSetPinMux(BE_TOP_HW_M19_PIN_MUX_PORT, value);
//	GPIO_DevSetMode(TEST_GPIO_CONTROL, LX_GPIO_MODE_OUTPUT);
//	GPIO_DevExSetPinMux(BE_TOP_HW_M19_PIN_MUX_PORT, value);
	return 0;
}
#endif

int BE_TOP_HW_M19_SetLSRParam(LX_BE_LSR_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	int lsrTblVer = 0x1;
	char *pBuffer = NULL;
	char *pAddr = NULL;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_LSR_T, stHwParams);

		CHECK_NULL(pstParams);
		CHECK_NULL(pstParams->lsrTbl.pu32Data);

		inSizeNum = pstParams->lsrTbl.u32SizeNum;

		inSize = inSizeNum * sizeof(pstParams->lsrTbl.pu32Data[0]);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_M19_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

		pBuffer = (char *)vmalloc(inSize);
	 	CHECK_NULL(pBuffer);
	    ret = copy_from_user(pBuffer, (void __user *)pstParams->lsrTbl.pu32Data, inSize);
	    if (ret)
		{
			BREAK_WRONG(ret);
	    }

		((UINT32 *)pBuffer)[0] = ((UINT32 *)pBuffer)[0] & 0x00FFFFFF; // clear sizenum info

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_M19_LSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bLSRMode = (pstParams->u32LsrMode) >= 0xFF ? 0xFFFFFFFF : (pstParams->u32LsrMode);
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_M19_LSR_TABLE_OFFSET;
		stHwParams.uDbtype = (lsrTblVer << 16) | inSizeNum;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_LSR), (void *)&stHwParams, sizeof(BE_IPC_LSR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}

	return ret;
}

int BE_TOP_HW_M19_SetGSR(LX_BE_GSR_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	int gsrTblVer = 0x1;
	char *pBuffer = NULL;
	char *pAddr = NULL;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_GSR_T, stHwParams);

		CHECK_NULL(pstParams);
		CHECK_NULL(pstParams->gsrTbl.pu32Data);

		inSizeNum = pstParams->gsrTbl.u32SizeNum;

		inSize = inSizeNum * sizeof(pstParams->gsrTbl.pu32Data[0]);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_M19_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

		pBuffer = (char *)vmalloc(inSize);
		CHECK_NULL(pBuffer);
		ret = copy_from_user(pBuffer, (void __user *)pstParams->gsrTbl.pu32Data, inSize);
		if (ret)
		{
			BREAK_WRONG(ret);
		}

		((UINT32 *)pBuffer)[0] = ((UINT32 *)pBuffer)[0] & 0x00FFFFFF; // clear sizenum info

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_M19_GSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bGSRMode = 1;
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_M19_GSR_TABLE_OFFSET;
		stHwParams.uDbtype = (gsrTblVer << 16) | inSizeNum;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_GSR), (void *)&stHwParams, sizeof(BE_IPC_GSR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}

	return ret;
}

int BE_TOP_HW_M19_GetGSRStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;
	UINT32 regVal;

	do{
		CHECK_NULL(pbParam);

		BE_REG_RD(0xC9011028, regVal);

		*pbParam = (regVal & 0x40) ? TRUE : FALSE;
	} while(0);
	
	return ret;
}

int BE_TOP_HW_M19_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal;
	UINT32 arrData[16];
	BE_CH_MEM_T *pFwMem = NULL;
	char *pAddr = NULL;
	char *pBuffer = NULL;
	UINT32 *pBuffer32 = NULL;
	int dataSize = 60*34*sizeof(char);

	UINT32 rowidx;
	UINT32 colidx;

	UINT32 Localalpha_col_size[4+1] = {0,15,30,45,60}; //{0,15,15,15,15}
	UINT32 Localalpha_row_size[4] = {8,16,24,34};	//{8,8,8,10}

	UINT32 Localalpha_col_diff[4] = {15,15,15,15};
	UINT32 Localalpha_row_diff[4] = {8,8,8,10};
	UINT32 ix, iy;

	do{
		CHECK_NULL(pstParams);

		if (pstParams->u32SizeNum != 16) BREAK_WRONG(pstParams->u32SizeNum);

		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_RD(0xC901102C, regVal);
		if (regVal != 0x1) BREAK_WRONG(regVal);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		pAddr = (char *)vmap_phys(pFwMem->fw_base + BE_TOP_HW_M19_OSD_ALPHA_TABLE_OFFSET, dataSize);
		CHECK_NULL(pAddr);

		pBuffer = (char *)vmalloc(dataSize);
		CHECK_NULL(pBuffer);

		memcpy(pBuffer, pAddr, dataSize);

		wmb();

		vunmap_phys(pAddr);

		pBuffer32 = (UINT32 *)pBuffer;

		for(rowidx = 0; rowidx < dataSize/4; rowidx++)
		{
			pBuffer32[rowidx] = ((pBuffer32[rowidx] >> 24) & 0xFF) | ((pBuffer32[rowidx] >> 8) & 0xFF00) |
				((pBuffer32[rowidx] << 8) & 0xFF0000) | ((pBuffer32[rowidx] << 24) & 0xFF000000);
		}

		memset(arrData, 0x0, sizeof(arrData));
		iy = 0;

		for(rowidx = 0; rowidx < 34/*ROW*/; rowidx++)
		{
			for(ix = 0; ix < (sizeof(Localalpha_col_size))/(sizeof(Localalpha_col_size[0]))-1; ix++)
			{
				for(colidx = Localalpha_col_size[ix]; colidx < Localalpha_col_size[ix+1]; colidx++)
				{
					arrData[iy*4 + ix] = arrData[iy*4 + ix] + ((pBuffer[60*rowidx + colidx] & 0x1) * 255);
				}
			}
			if(rowidx == Localalpha_row_size[iy]-1)
				iy++;
		}

		for(iy = 0; iy < 4; iy++)
		{
			for(ix = 0; ix < 4; ix++)
			{
				arrData[iy*4 + ix] = arrData[iy*4 + ix] / (Localalpha_row_diff[iy] * Localalpha_col_diff[ix]);
			}
		}

		ret = copy_to_user((void __user *)pstParams->pu32Data, arrData, sizeof(arrData));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}

	return ret;
}

int BE_TOP_HW_M19_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 arrData[1];

	do{
		CHECK_NULL(pstParams);

		if (pstParams->levelTbl.u32SizeNum != 1) BREAK_WRONG(pstParams->levelTbl.u32SizeNum);

		ret = copy_from_user(arrData, (void __user *)pstParams->levelTbl.pu32Data, sizeof(UINT32)*(pstParams->levelTbl.u32SizeNum));
		if(ret) BREAK_WRONG(ret);

		PE_OSD_M19_RdFL(osd0_vsp_bosd_ctrl_0);
		PE_OSD_M19_Wr01(osd0_vsp_bosd_ctrl_0, reg_vspyc_en, pstParams->bOnOff ? 0x1 : 0x0);
		if (arrData[0] == 0x0)
		{
			PE_OSD_M19_Wr01(osd0_vsp_bosd_ctrl_0, r_contrast, 0x200);
		}
		else
		{
			PE_OSD_M19_Wr01(osd0_vsp_bosd_ctrl_0, r_contrast, ((0xFF - arrData[0]) << 1));
		}
		PE_OSD_M19_WrFL(osd0_vsp_bosd_ctrl_0);

		PE_OSD_M19_RdFL(osd0_vsp_bosd_ctrl_1);
		if (arrData[0] == 0x0)
		{
			PE_OSD_M19_Wr01(osd0_vsp_bosd_ctrl_1, r_saturation, 0x80);
		}
		else
		{
			PE_OSD_M19_Wr01(osd0_vsp_bosd_ctrl_1, r_saturation, ((0xFF - arrData[0]) >> 1));
		}
		PE_OSD_M19_Wr01(osd0_vsp_bosd_ctrl_1, r_offset, 0x200);
		PE_OSD_M19_WrFL(osd0_vsp_bosd_ctrl_1);

	} while(0);

	return ret;
}


int BE_TOP_HW_M19_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_DEBUG_DISPLAY_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uH3DDebugdisplay = pstParams->u8H3DDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8H3DDebugDisplay;
		stHwParams.uPEDebugDisplay = pstParams->u8PEDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8PEDebugDisplay;
		stHwParams.uLEDDebugDisplay = pstParams->u8LEDDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8LEDDebugDisplay;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DEBUG_DISPLAY), (void *)&stHwParams, sizeof(BE_IPC_DEBUG_DISPLAY_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

/** BE/TOP m19 proc handler */
int BE_TOP_HW_M19_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_TOP_PROC_ID_DETAIL_INFO:
		{

		}
		break;

		default: break;
	}

	return RET_OK;
}

/** @} */
