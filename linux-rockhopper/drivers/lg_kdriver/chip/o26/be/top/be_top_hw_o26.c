/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define BE_TOP_HW_O26_USE_VX1_CHIP_INFO 1

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
#include <linux/platform_device.h>

#include "be_dbg.h"
#include "be_cfg.h"
#include "be_def.h"
#include "../fwi/ipc_def_o26.h"
#include "ipc_drv.h"
#include "be_top_hw_o26.h"
#include "../led/be_led_hw_o26.h"

// For Video InputLag Test
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>

#include "../gpio/gpio_drv.h"
#include "../gpio/gpio_core.h"


// For CTOP/DPE register access
//#include "../../../core/sys/sys_regs.h"
#include "../reg/be_reg_dpe_o26.h"

#ifdef INCLUDE_KDRV_DE
#include "ipc_cmd_header.h"
#else
#define TOP_PACK_CMD(cmd) cmd
#define DE_PACK_CMD(cmd) cmd
#define DE_IPC_SET_IF_CONFIG 0
#endif

// For Status Management
#include "../../../core/be/video_status_keeper.h"

#ifdef INCLUDE_KDRV_DE
#include "../../../core/de/de_sync.h"
#include "../../../core/de/hal/ipc_phys_hal.h"
#endif
#include "../../../core/gpio/gpio_drv.h"
#include "../../../core/gpio/gpio_core.h"

#if BE_TOP_HW_O26_USE_VX1_CHIP_INFO
#include "ovi_hal.h"
#include "../../ovi/ovi_hw_o26.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define BE_TOP_HW_O26_MAGIC_NUM ((UINT32)0x1234ABCD)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define BE_TOP_HW_O26_LSR_TABLE_OFFSET 0x800
#define BE_TOP_HW_O26_GSR_TABLE_OFFSET (BE_TOP_HW_O26_LSR_TABLE_OFFSET + 0x800)
#define BE_TOP_HW_O26_OSD_ALPHA_TABLE_OFFSET (BE_TOP_HW_O26_GSR_TABLE_OFFSET + 0x800)
#define BE_TOP_HW_O26_PATTERN_INFO_OFFSET (BE_TOP_HW_O26_OSD_ALPHA_TABLE_OFFSET + 0x1000)
#define BE_TOP_HW_O26_GSR2_TABLE_OFFSET (BE_TOP_HW_O26_PATTERN_INFO_OFFSET + 0x800)
#define BE_TOP_HW_O26_IRR_ALUM_TABLE_OFFSET (BE_TOP_HW_O26_GSR2_TABLE_OFFSET + 0x800)
#define BE_TOP_HW_O26_IRR_DATA_OFFSET (BE_TOP_HW_O26_IRR_ALUM_TABLE_OFFSET + 0x400)
#define BE_TOP_HW_O26_TPC_PARAM_OFFSET (BE_TOP_HW_O26_IRR_DATA_OFFSET + 0x2000)
#define BE_TOP_HW_O26_TPC_STATUS_OFFSET (BE_TOP_HW_O26_TPC_PARAM_OFFSET + 0x80)

#ifdef BE_TOP_HW_O26_TEST_INPUT_LAG
#define	BE_TOP_HW_O26_IPP_LAG_CTRL0_BASE		(0xC9014490) //o18: 0xC9014448, m16p3: 0xC9014448
#define	BE_TOP_HW_O26_IPP_PIXEL_ACTIVE_RIGING	(0xC901405C) // AVTASK-371

#define	BE_TOP_HW_O26_IPP_LAG_CTRL1_BASE	(0xC9014494) //SCDCR-2484
#define	BE_TOP_HW_O26_IPP_LAG_CTRL2_BASE	(0xC9014498)
#define BE_TOP_HW_O26_PATTE

#define BE_TOP_HW_O26_PATTERN_OFF		(0)
#define BE_TOP_HW_O26_PATTERN_ON		(1)
#define BE_TOP_HW_O26_PATTERN_BLACK		(0) //0x88080200
#define BE_TOP_HW_O26_PATTERN_WHITE		(1) //0xBFF80200

#define BE_TOP_HW_O26_PIN_MUX_PORT		(119)
#define BE_TOP_HW_O26_PIN_NORMAL		(0)
#define BE_TOP_HW_O26_PIN_GPIO			(1)
#endif

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
#define BE_OSD_HW_F22_REG_OSD_GSR_CTRL 0xF40715C0

#define _B2L32(data) ((((UINT32)(data&0xff000000) >> 24) & 0x000000ff) |   \
					(((UINT32)(data&0x00ff0000) >>  8) & 0x0000ff00) |   \
					(((UINT32)(data&0x0000ff00) <<  8) & 0x00ff0000) |   \
					(((UINT32)(data&0x000000ff) << 24) & 0xff000000))
#endif

#define BE_TOP_HW_O26_PQE_PM_DEVICE_SUSPEND_PREPARE		0
//fw stall
#define BE_TOP_HW_O26_PQE_PM_DEVICE_SUSPEND				1
//cg on
#define BE_TOP_HW_O26_PQE_PM_DEVICE_SUSPEND_COMPLETED	2
#define BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_PREPARE		3
//cg off
#define BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME				4
//fw restart
#define BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED	5

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
typedef struct {
	LX_BE_ORBIT_T 	orbitInfo;
	UINT32			  lsrSize;
	UINT32			  gsrSize;
	UINT32			   osdLvl;
	UINT32 				  cpc;
	UINT32 			  osdGain;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
	void *pVx1ChipInfoVMapAddr;
	BE_OVI_HW_O26_VX1_CHIP_INFO_T *pVx1ChipInfo[BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM];
#endif
	UINT32 			frcStatus;
	BOOLEAN			isIrrInit;
	UINT32			pmStatus;

	LX_OVI_HW_DISPLAY_INFO_T dispInfo;

	BE_IPC_DISP_MODE_T disp_mode;
} BE_TOP_HW_O26_INFO_T;

enum v4l2_ext_vbe_dclk_mode {
	V4L2_EXT_VBE_DCLK_MODE_BASIC,  // DCLK when power on (ex: 74.25MHz for 120Hz module or 84.24MHz for 144Hz module)
	V4L2_EXT_VBE_DCLK_MODE_165HZ,  // DCLK for 165Hz output
	V4L2_EXT_VBE_DCLK_MODE_MAX
};

/*-----------------------------------------------------------------------------
                             0xC9014494 pix_sum_ctrl0
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lag_x_end                          :13,	// 12:0
	reserved01                         :3 ,	// reserved
	lag_x_start	                       :13;	// 16:28
}LAG_CTRL1;
/*-----------------------------------------------------------------------------
                             0xC9014498 pix_sum_ctrl0
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lag_y_end                          :13,	// 12:0
	reserved01                         :3 ,	// reserved
	lag_y_start	                       :13;	// 16:28
}LAG_CTRL2;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern BE_MEM_CFG_T *gpBeMem;
extern BE_LED_REG_O26_T gBE_LED_O26;
extern BE_OLED_REG_O26_T gBE_OLED_O26;
extern BE_OSD_REG_O26_T gBE_OSD_O26;

#if 0 // block for bringup
struct gpio_desc *gpiod_de;
struct device de_gpio_dev = { .init_name = "gpio_kerneltable", }; //GPIO INIT CONTROL
#endif
//extern struct gpio_desc *gpiod_de;
//extern struct device de_gpio_dev;

extern BE_FRM_MEM_CFG_T *gpBeChInfMem;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile LAG_CTRL1 *gBE_TOP_HW_O26_LAG_CTRL1 = NULL;
volatile LAG_CTRL2 *gBE_TOP_HW_O26_LAG_CTRL2 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef BE_TOP_HW_O26_TEST_INPUT_LAG
static int BE_TOP_HW_O26_InitLagPattern(void);
int BE_TOP_HW_O26_InputLagHandler(void);
static int BE_TOP_HW_O26_SetPattern(UINT32 bOnOff);
static int BE_TOP_HW_O26_SetGpioValue(UINT32 value);
static int BE_TOP_HW_O26_SetGpioMux(UINT32 value);
#endif

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
static int _BE_TOP_O26_InitVx1ChipInfoMem(void);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static UINT32 g_be_top_hw_O26_pattern_init = 0;
__attribute__((unused)) static LX_BE_INPUT_LAG_PATTERN_T gCurPatternParam;
__attribute__((unused)) static LX_BE_INPUT_LAG_PATTERN_T gPrePatternParam;
__attribute__((unused)) static UINT32 gInputLagCnt = 0;
__attribute__((unused)) static volatile UINT32 *gIPP_LAG_CTRL0 = NULL;
__attribute__((unused)) static volatile UINT32 *gIPP_PIXEL_CTRL_ACTIVE_RIGING = NULL;

static BE_TOP_HW_O26_INFO_T gTopHwO26Info;
/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
static int _BE_TOP_O26_InitVx1ChipInfoMem(void)
{
	int ret = RET_OK;
	BE_FRM_MEM_CFG_T *pChInfMem = gpBeChInfMem;
	int i;
		
	do {
		gTopHwO26Info.pVx1ChipInfoVMapAddr = NULL;

		if (gTopHwO26Info.dispInfo.frcChipType != LX_OVI_FRC_CHIP_UD_BE_F22) break;
		
		CHECK_NULL(pChInfMem);
		CHECK_NULL(pChInfMem->frame_base);
		
		if ((pChInfMem->frame_size != BE_OVI_HW_O26_VX1_CHIP_INFO_TOTAL_MEM_SIZE)
			|| (sizeof(BE_OVI_HW_O26_VX1_CHIP_INFO_T) != BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE))
		{
			BE_ERROR("[BE] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		gTopHwO26Info.pVx1ChipInfoVMapAddr = vmap_phys(pChInfMem->frame_base, pChInfMem->frame_size);
		CHECK_NULL(gTopHwO26Info.pVx1ChipInfoVMapAddr);

		for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
		{
			if (pChInfMem->frame_size < ((BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
											+BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET \
											+sizeof(BE_OVI_HW_O26_VX1_CHIP_INFO_T))) break;
			
			gTopHwO26Info.pVx1ChipInfo[i] = (BE_OVI_HW_O26_VX1_CHIP_INFO_T *)(gTopHwO26Info.pVx1ChipInfoVMapAddr \
																			+(BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
																			+BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
		}
		if (i != BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM)
		{
			BE_ERROR("[BE] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}
	} while(0);

	if (ret && (gTopHwO26Info.pVx1ChipInfoVMapAddr != NULL))
	{
		vunmap_phys(gTopHwO26Info.pVx1ChipInfoVMapAddr);
		gTopHwO26Info.pVx1ChipInfoVMapAddr = NULL;
	}

	return ret;
}
#endif

int BE_TOP_HW_O26_Initialize(void)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;

	do {
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_WR(0xCC88102C, pFwMem->fw_base + BE_TOP_HW_O26_OSD_ALPHA_TABLE_OFFSET);

		BE_REG_WR(0xCC88045C, 0x0); // init OSD0_GSR_CTRL03, crnt gain LUT
		BE_REG_WR(0xCC880468, 0x0); // init OSD0_GSR_CTRL06, value gain LUT
		BE_REG_WR(0xCC880474, 0x0); // init OSD0_GSR_CTRL09, sat gain LUT

		ret = OVI_HAL_GetHWDisplayOption(&gTopHwO26Info.dispInfo);
		if (ret) BREAK_WRONG(ret);

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		ret = _BE_TOP_O26_InitVx1ChipInfoMem();
		if (ret) BREAK_WRONG(ret);
#endif
		gTopHwO26Info.frcStatus = 0;
		gTopHwO26Info.isIrrInit = FALSE;
		gTopHwO26Info.pmStatus = BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED;

		gTopHwO26Info.disp_mode.uDispResolutionWidth = 3840;
		gTopHwO26Info.disp_mode.uDispResolutionHeight = 1080;
		gTopHwO26Info.disp_mode.uFrameRate = 120;
		gTopHwO26Info.disp_mode.uHighSpeedClock = 0;
		gTopHwO26Info.disp_mode.uBoostMode = 0;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_Resume(void)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;

	do {
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_WR(0xCC88102C, pFwMem->fw_base + BE_TOP_HW_O26_OSD_ALPHA_TABLE_OFFSET);

		BE_REG_WR(0xCC88045C, 0x0); // init OSD0_GSR_CTRL23, crnt gain LUT
		BE_REG_WR(0xCC880468, 0x0); // init OSD0_GSR_CTRL26, value gain LUT
		BE_REG_WR(0xCC880474, 0x0); // init OSD0_GSR_CTRL29, sat gain LUT

		gTopHwO26Info.isIrrInit = FALSE;
		gTopHwO26Info.pmStatus = BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_Close(void)
{
	int ret = RET_OK;

	do {
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		if (gTopHwO26Info.pVx1ChipInfoVMapAddr != NULL)
		{
			vunmap_phys(gTopHwO26Info.pVx1ChipInfoVMapAddr);
			gTopHwO26Info.pVx1ChipInfoVMapAddr = NULL;
		}
#endif
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLOCK_BYPASS_T, stHwParams);

		if (pstParams->bLEDBypass <= 1)
		{
			BE_LED_O26_RdFL(ad_led_detour);
			if (pstParams->bLEDBypass)
			{
				BE_LED_O26_Wr01(ad_led_detour, led_detour, 0x1);
			}
			else
			{
				BE_LED_O26_Wr01(ad_led_detour, led_detour, 0x0);
			}
			BE_LED_O26_WrFL(ad_led_detour);
		}
		
		/* change value LX_BE to BE_IPC */
		stHwParams.uFRCBypass = (pstParams->bFRCBypass > 1) ? 0xFFFFFFFF : pstParams->bFRCBypass;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLOCK_BYPASS), (void*)&stHwParams, sizeof(BE_IPC_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetOrbit(LX_BE_ORBIT_T *pstParams)
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

		memcpy(&gTopHwO26Info.orbitInfo, pstParams, sizeof(LX_BE_ORBIT_T));
	} while(0);

	return ret;
}

#ifdef BE_TOP_HW_O26_TEST_INPUT_LAG
static int BE_TOP_HW_O26_InitLagPattern(void)
{
	gIPP_LAG_CTRL0 = (volatile UINT32 *)ioremap(BE_TOP_HW_O26_IPP_LAG_CTRL0_BASE, sizeof(UINT32));
	gIPP_PIXEL_CTRL_ACTIVE_RIGING = (volatile UINT32 *)ioremap(BE_TOP_HW_O26_IPP_PIXEL_ACTIVE_RIGING, sizeof(UINT32));

	gBE_TOP_HW_O26_LAG_CTRL1 = (volatile LAG_CTRL1 *)ioremap(BE_TOP_HW_O26_IPP_LAG_CTRL1_BASE, sizeof(LAG_CTRL1));
	gBE_TOP_HW_O26_LAG_CTRL2 = (volatile LAG_CTRL2 *)ioremap(BE_TOP_HW_O26_IPP_LAG_CTRL2_BASE, sizeof(LAG_CTRL2));

	/* move to below line to init(to get gpiod_de only one time */
	gpiod_de = gpiod_get(&de_gpio_dev, "119", GPIOD_OUT_HIGH);

	gPrePatternParam.enable = BE_TOP_HW_O26_PATTERN_OFF;
	gPrePatternParam.type = 0xff;
	gPrePatternParam.hoffset = 0;
	gPrePatternParam.voffset = 0;
	gPrePatternParam.hsize = 0;
	gPrePatternParam.vsize = 0;

	return RET_OK;
}

int BE_TOP_HW_O26_SetLagParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams)
{
	int ret = RET_OK;
	UINT32 cur_enable,pre_enable;
	LAG_CTRL1	pix_lag_ctrl1;	//0xC9014494
	LAG_CTRL2	pix_lag_ctrl2;	//0xC9014498

	if (pstParams == NULL)
	{
		BE_ERROR("pstParams is NULL");
		return RET_ERROR;
	}

	BE_NOTI("init:%d, bOnOff[%d] bPatternType[%d] rect[%d/%d/%d/%d]\n",\
		g_be_top_hw_O26_pattern_init,pstParams->enable,pstParams->type,\
		pstParams->hoffset,pstParams->voffset,pstParams->hsize,pstParams->vsize);

	if (!g_be_top_hw_O26_pattern_init)
	{
		BE_TOP_HW_O26_InitLagPattern();
		g_be_top_hw_O26_pattern_init = 1;
	}

	gCurPatternParam = *pstParams;
	cur_enable = gCurPatternParam.enable;
	pre_enable = gPrePatternParam.enable;

	do {
		CHECK_KNULL(gBE_TOP_HW_O26_LAG_CTRL1);
		CHECK_KNULL(gBE_TOP_HW_O26_LAG_CTRL2);

		if (pre_enable == cur_enable)		break;
		if (cur_enable == BE_TOP_HW_O26_PATTERN_ON)
		{
			/* interrupt enable */
#ifdef INCLUDE_KDRV_DE
			ipc_phys_hal_InitInterrupt(0, TRUE);
#endif
			gPrePatternParam.type = 0xff;
			*gIPP_PIXEL_CTRL_ACTIVE_RIGING = 0x84002000;

			pix_lag_ctrl1 = *gBE_TOP_HW_O26_LAG_CTRL1;
			pix_lag_ctrl1.lag_x_start = pstParams->hoffset;
			pix_lag_ctrl1.lag_x_end = pstParams->hoffset + pstParams->hsize;
			*gBE_TOP_HW_O26_LAG_CTRL1 = pix_lag_ctrl1;

			pix_lag_ctrl2 = *gBE_TOP_HW_O26_LAG_CTRL2;
			pix_lag_ctrl2.lag_y_start = pstParams->voffset;
			pix_lag_ctrl2.lag_y_end = pstParams->voffset + pstParams->vsize;
			*gBE_TOP_HW_O26_LAG_CTRL2 = pix_lag_ctrl2;
			BE_NOTI("SetLagParam_Position rect[%d/%d/%d/%d]\n",pix_lag_ctrl1.lag_x_start,pix_lag_ctrl1.lag_x_end,pix_lag_ctrl2.lag_y_start, 
			pix_lag_ctrl2.lag_y_end);
			/* register handle */
#ifdef INCLUDE_KDRV_DE
			de_srcsync_register(TRUE, BE_TOP_HW_O26_InputLagHandler, "inputLag_handler");
#endif
			BE_NOTI("START\n");
		}
		else
		{
			/* unregister handle */
			*gIPP_LAG_CTRL0 = 0x00008080;
			*gIPP_PIXEL_CTRL_ACTIVE_RIGING = 0x00000000;
			pix_lag_ctrl1.lag_x_start = 0;
			pix_lag_ctrl1.lag_x_end = 0;
			*gBE_TOP_HW_O26_LAG_CTRL1 = pix_lag_ctrl1;
			pix_lag_ctrl2.lag_y_start = 0;
			pix_lag_ctrl2.lag_y_end = 0;
			*gBE_TOP_HW_O26_LAG_CTRL2 = pix_lag_ctrl2;
#ifdef INCLUDE_KDRV_DE
			de_srcsync_register(FALSE, BE_TOP_HW_O26_InputLagHandler, "inputLag_handler");
#endif
			/* interrupt disable */
#ifdef INCLUDE_KDRV_DE
			ipc_phys_hal_InitInterrupt(0, FALSE);
#endif
			BE_NOTI("END\n");
		}
		gPrePatternParam.enable = gCurPatternParam.enable;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_InputLagHandler(void)
{
	int ret = RET_OK;
	UINT32 cur_enable,cur_type,pre_type;
	static UINT64 prev_msec_tick = 0;
	UINT64 curr_msec_tick = 0, tick_diff = 0;
	LX_GPIO_VALUE_T gpio_value = LX_GPIO_VALUE_INVALID;

	cur_enable = gCurPatternParam.enable;
	cur_type = gCurPatternParam.type;
	pre_type = gPrePatternParam.type;

	static UINT32 gpio_cnt = 0;

	if (cur_enable != BE_TOP_HW_O26_PATTERN_ON)
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
		CHECK_KNULL(gpiod_de);
		if (pre_type == cur_type)		break;

		if (cur_type == BE_TOP_HW_O26_PATTERN_WHITE) //white pattern
		{
			BE_TOP_HW_O26_SetPattern(BE_TOP_HW_O26_PATTERN_WHITE); //White
		}
		else	//black pattern
		{
			BE_TOP_HW_O26_SetPattern(BE_TOP_HW_O26_PATTERN_BLACK); //Black
		}

		gPrePatternParam.type = gCurPatternParam.type;
		gpio_cnt = 5;
		BE_NOTI("type changed:%d <- %d, gpio:%d, tick diff:%llu (%llu <- %llu)",\
			cur_type,pre_type,gpio_value,tick_diff,curr_msec_tick,prev_msec_tick);
	} while(0);

	if (gpio_cnt == 4)
	{
		gpiod_set_raw_value(gpiod_de, (cur_type == BE_TOP_HW_O26_PATTERN_WHITE)? 1:0);
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

	return 0;
}

static int BE_TOP_HW_O26_SetPattern(UINT32 bOnOff)
{
	if (bOnOff == BE_TOP_HW_O26_PATTERN_WHITE)
	{
		*gIPP_LAG_CTRL0 = 0xBFF80200;
	}
	else if (bOnOff == BE_TOP_HW_O26_PATTERN_BLACK)
	{
		*gIPP_LAG_CTRL0 = 0x88080200;
	}
	return 0;
}
#if 0 // not used
static int BE_TOP_HW_O26_SetGpioValue(UINT32 value)
{
//	GPIO_DevSetValue(BE_TOP_HW_O26_PIN_MUX_PORT, value);

	return 0;
}

static int BE_TOP_HW_O26_SetGpioMux(UINT32 value)
{
//	GPIO_DevSetPinMux(BE_TOP_HW_O26_PIN_MUX_PORT, value);
//	GPIO_DevSetMode(TEST_GPIO_CONTROL, LX_GPIO_MODE_OUTPUT);
	
	return 0;
}
#endif
#endif

int BE_TOP_HW_O26_SetLSRParam(LX_BE_LSR_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	int lsrTblVer = 0x3; // SICREQ-1185 0x2 -> 0x3
	char *pBuffer = NULL;
	char *pAddr = NULL;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_LSR_T, stHwParams);

		CHECK_NULL(pstParams);
		CHECK_NULL(pstParams->lsrTbl.pu32Data);

		inSizeNum = pstParams->lsrTbl.u32SizeNum; 

		inSize = inSizeNum * sizeof(pstParams->lsrTbl.pu32Data[0]);
		gTopHwO26Info.lsrSize = inSize;
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_O26_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_LSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bLSRMode = (pstParams->u32LsrMode) >= 0xFF ? 0xFFFFFFFF : (pstParams->u32LsrMode);
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_LSR_TABLE_OFFSET;
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

int BE_TOP_HW_O26_SetGSR(LX_BE_GSR_T *pstParams)
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
		gTopHwO26Info.gsrSize = inSize;
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_O26_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_GSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bGSRMode = 1;
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_GSR_TABLE_OFFSET;
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

int BE_TOP_HW_O26_SetGSR2(LX_BE_GSR_T *pstParams)
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
		gTopHwO26Info.gsrSize = inSize;
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_O26_GSR2_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_GSR2_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bGSRMode = 1;
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_GSR2_TABLE_OFFSET;
		stHwParams.uDbtype = (gsrTblVer << 16) | inSizeNum;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_GSR2), (void *)&stHwParams, sizeof(BE_IPC_GSR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}
	
	return ret;
}

int BE_TOP_HW_O26_GetGSRStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;

	do{
		CHECK_NULL(pbParam);

		BE_REG_RD(0xCC881028, regVal); // CC_PE1_FSW_CTRL_02

		*pbParam = (regVal & 0x40) ? TRUE : FALSE;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_GetGSRStressCount(UINT32 *pu32Param)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;

	do{
		CHECK_NULL(pu32Param);

		BE_REG_RD(0xCC882314, regVal); // CCO_VERI, sys_veri_5

		*pu32Param = regVal;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetCPC(UINT32 u32Param)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_CPC_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uCPCParam = u32Param;
		gTopHwO26Info.cpc = u32Param;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_CPC), (void *)&stHwParams, sizeof(BE_IPC_CPC_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

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

int BE_TOP_HW_O26_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;
	UINT32 arrData[16];
	BE_CH_MEM_T *pFwMem = NULL;
	char *pAddr = NULL;
	char *pBuffer = NULL;
	UINT32 *pBuffer32 = NULL;
	int dataSize = 60*34*sizeof(char);
	UINT32 restSize = 0;
	UINT32 alignedBase = 0;

	UINT32 rowidx;
	UINT32 colidx;

	UINT32 Localalpha_col_size[4+1] = {0,15,30,45,60}; //{0,15,15,15,15}
	UINT32 Localalpha_row_size[4] = {8,16,24,34};	//{8,8,8,10}

	UINT32 Localalpha_col_diff[4] = {15,15,15,15};
	UINT32 Localalpha_row_diff[4] = {8,8,8,10};
	UINT32 ix, iy;

	UINT32 tmpData;

	do{
		CHECK_NULL(pstParams);

		if (pstParams->u32SizeNum != 16 && pstParams->u32SizeNum != 1) BREAK_WRONG(pstParams->u32SizeNum);

		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_RD(0xCC88102C, regVal);

		if (regVal != 0x1)
		{
			BE_DEBUG("%s(%d): break wrong regVal(0x%x)\n", __F__, __L__, regVal);
			ret = RET_ERROR;
			break;
		}

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		restSize = ((pFwMem->fw_base + BE_TOP_HW_O26_OSD_ALPHA_TABLE_OFFSET) & (PAGE_SIZE - 1));
		alignedBase = ((pFwMem->fw_base + BE_TOP_HW_O26_OSD_ALPHA_TABLE_OFFSET) & (~(PAGE_SIZE - 1)));

		pAddr = (char *)vmap_phys(alignedBase, dataSize + restSize);
		CHECK_NULL(pAddr);

		pBuffer = (char *)vmalloc(dataSize);
		CHECK_NULL(pBuffer);

		memcpy(pBuffer, (pAddr + restSize), dataSize);

		rmb();

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

		if (pstParams->u32SizeNum == 1) // update local data for vbe log
		{
			tmpData = 0;

			for(ix=0; ix<16; ix++)
			{
				tmpData += arrData[ix];
			}

			gTopHwO26Info.osdLvl = tmpData/16;

		}
		else
		{
			ret = copy_to_user((void __user *)pstParams->pu32Data, arrData, sizeof(arrData));
			if(ret) BREAK_WRONG(ret);
		}

	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}

	return ret;
}

int BE_TOP_HW_O26_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 arrData[1];

	do{
		CHECK_NULL(pstParams);

		if (pstParams->levelTbl.u32SizeNum != 1) BREAK_WRONG(pstParams->levelTbl.u32SizeNum);

		ret = copy_from_user(arrData, (void __user *)pstParams->levelTbl.pu32Data, sizeof(UINT32)*(pstParams->levelTbl.u32SizeNum));
		if(ret) BREAK_WRONG(ret);

		gTopHwO26Info.osdGain = arrData[0];

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		if (gTopHwO26Info.pVx1ChipInfoVMapAddr != NULL)
		{
			UINT32 dataSize;
			__attribute__((unused)) UINT32 regVal = 0;
			int i;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
			BE_OVI_HW_O26_VX1_CHIP_INFO_APB_CNT2_T count;
#endif

			regVal = regVal | (pstParams->bOnOff ? 0x1 : 0x0);
			if (arrData[0] == 0xFF)
			{
				regVal = regVal | (0x3FF << 16);
			}
			else
			{
				regVal = regVal | ((( arrData[0]) << 2) << 16);
			}

			for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
			{
				dataSize = 0;
				
				gTopHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.osdLvCtrlRegAddr = _B2L32(BE_OSD_HW_F22_REG_OSD_GSR_CTRL); dataSize++;
				gTopHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.osdLvCtrlVal = _B2L32(regVal); dataSize++;
				dataSize = sizeof(UINT32) * dataSize;

#ifndef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
				gTopHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
#endif

				if (dataSize != BE_HW_O26_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE) BREAK_WRONG(dataSize);

				wmb();
				
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
				count.u32Data = _B2L32(gTopHwO26Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data);

				if (count.osdLvCtrl == 0xFF)
				{
					count.osdLvCtrl = 1;
				}
				else
				{
					count.osdLvCtrl++;
				}

				gTopHwO26Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data = _B2L32(count.u32Data);
#else
				gTopHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32((0x0A000000|BE_HW_O26_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE));
#endif

				wmb();

				OVI_HAL_UpdateChipInfoHeader();
			}
			if (ret != RET_OK) break;
		}
		else
		{
#endif
			BE_OSD_O26_RdFL(reg_osd0_gsr_ctrl00);
			BE_OSD_O26_Wr01(reg_osd0_gsr_ctrl00, reg_gsr_blend_en, pstParams->bOnOff ? 0x1 : 0x0);
			if (arrData[0] == 0xFF)
			{
				BE_OSD_O26_Wr01(reg_osd0_gsr_ctrl00, reg_gsr_master_gain, 0x3FF);
			}
			else
			{
				BE_OSD_O26_Wr01(reg_osd0_gsr_ctrl00, reg_gsr_master_gain, (( arrData[0]) << 2));
			}
			BE_OSD_O26_WrFL(reg_osd0_gsr_ctrl00);
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		}
#endif

	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetIrrAdaptedLum(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	char *pBuffer = NULL;
	char *pAddr = NULL;
	char *pOffsetAddr;
	BE_CH_MEM_T *pFwMem = NULL;
	static UINT32 irrUpdateCnt = 0;

	do{ 
		CHECK_NULL(pstParams);
		CHECK_NULL(pstParams->pu32Data);
		if (pstParams->u32SizeNum == 0) BREAK_WRONG(pstParams->u32SizeNum);

		inSizeNum = pstParams->u32SizeNum; 

		inSize = inSizeNum * 4; 
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_O26_IRR_ALUM_TABLE_OFFSET + 4) > pFwMem->fw_size) BREAK_WRONG(inSize); // 4: 4bytes for magic number

		pBuffer = (char *)vmalloc(inSize);
		CHECK_NULL(pBuffer);
		ret = copy_from_user(pBuffer, (void __user *)pstParams->pu32Data, inSize);
		if (ret)
		{
			BREAK_WRONG(ret);
		}

		irrUpdateCnt = (irrUpdateCnt >= 0xFF) ? 1 : (irrUpdateCnt+1);

		((UINT32 *)pBuffer)[0] = (((UINT32 *)pBuffer)[0] & 0xFF00FFFF) | (irrUpdateCnt << 16);

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);

		pOffsetAddr = (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_IRR_ALUM_TABLE_OFFSET);

		// copy data only
		memcpy((char *)&pOffsetAddr[8], (char *)&pBuffer[4], (inSize-4));
		
		wmb();

		// copy header (sizenum|count|rsvd|rsvd)
		((UINT32 *)pOffsetAddr)[1] = ((UINT32 *)pBuffer)[0];
		
		wmb();

		// set magic number
		((UINT32 *)pOffsetAddr)[0] = BE_TOP_HW_O26_MAGIC_NUM;
		
		wmb();

		if (gTopHwO26Info.dispInfo.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
		{
			IPC_SET_DEFAULT_PARAM(BE_IPC_IRR_T, stHwParams);

			stHwParams.bIrrDataLoad = 2;
			stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_IRR_ALUM_TABLE_OFFSET;
			ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_IRR), (void *)&stHwParams, sizeof(BE_IPC_IRR_T));
			if(ret) BREAK_WRONG(ret);
		}

		BE_DEBUG("%s : data[0-8] {0x%x,%d,%d,%d,%d,%d,%d,%d,%d}\n", __F__, ((UINT32 *)pBuffer)[0],
												((UINT32 *)pBuffer)[1], ((UINT32 *)pBuffer)[2],
												((UINT32 *)pBuffer)[3], ((UINT32 *)pBuffer)[4],
												((UINT32 *)pBuffer)[5], ((UINT32 *)pBuffer)[6],
												((UINT32 *)pBuffer)[7], ((UINT32 *)pBuffer)[8]);
	} while(0);

	if (pBuffer != NULL) vfree(pBuffer);
	if (pAddr != NULL) vunmap_phys(pAddr);
	
	return ret;
}


int BE_TOP_HW_O26_GetIrrResult(UINT32 *pu32Param)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;
	
	do{
		CHECK_NULL(pu32Param);

		BE_REG_RD(0xCC882378, regVal); //REG_CCO_VERI_SYS_VERI_30_T

		*pu32Param = regVal;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_GetIrrStatus(LX_BE_IRR_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do{
		CHECK_NULL(pstParams);

		pstParams->bIsIrrInitDone = gTopHwO26Info.isIrrInit;
		pstParams->bIsIrrSuspended = (gTopHwO26Info.pmStatus == BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED) ? FALSE : TRUE;
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetIrrData(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	char *pAddr = NULL;
	char *pBuffer;
	BE_CH_MEM_T *pFwMem = NULL;
	
	IPC_SET_DEFAULT_PARAM(BE_IPC_IRR_T, stHwParams);

	do{ 
		CHECK_NULL(pstParams);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);

		pBuffer = (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_IRR_DATA_OFFSET);

		if ((pstParams->pu32Data == NULL) 
			|| (pstParams->u32SizeNum == 0))
		{
			if (pFwMem->fw_size < (BE_TOP_HW_O26_IRR_DATA_OFFSET + 4)) BREAK_WRONG(pFwMem->fw_size);

			((UINT32 *)pBuffer)[0] = 0x1; // set mem data header for updating data to read 

			wmb();
			
			stHwParams.bIrrDataLoad = 0;
		}
		else
		{
			inSizeNum = pstParams->u32SizeNum; 

			inSize = inSizeNum * 4; 

			if ((inSize + BE_TOP_HW_O26_IRR_DATA_OFFSET + 4) > pFwMem->fw_size) BREAK_WRONG(inSize); // 4 : Mem data header

			((UINT32 *)pBuffer)[0] = 0x0; // Clear mem data header 
			
			ret = copy_from_user((void *)&(((UINT32 *)pBuffer)[1]), (void __user *)pstParams->pu32Data, inSize);
			if (ret)
			{
				BREAK_WRONG(ret);
			}

			wmb();

			stHwParams.bIrrDataLoad = 1;
		}

		gTopHwO26Info.isIrrInit = TRUE; // update init flag before sending IPC (to avoid following case : send IPC -> suspend -> resume(update flag to FALSE) -> update flag to TRUE)
		
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_IRR_ALUM_TABLE_OFFSET; // IRR_DATA_OFFSET is not used => Base is IRR_ALUM_TABLE_OFFSET
		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_IRR), (void *)&stHwParams, sizeof(BE_IPC_IRR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	if (pAddr != NULL) vunmap_phys(pAddr);
	
	return ret;
}

int BE_TOP_HW_O26_GetIrrData(LX_BE_IRR_READ_T *pstParams)
{
	int ret = RET_OK;
	int outSizeNum;
	int outSize;
	char *pAddr = NULL;
	char *pBuffer;
	BE_CH_MEM_T *pFwMem = NULL;

	do{ 
		if (gTopHwO26Info.isIrrInit == FALSE) BREAK_WRONG(gTopHwO26Info.isIrrInit);
		
		CHECK_NULL(pstParams);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);

		pBuffer = (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_IRR_DATA_OFFSET);

		if (pstParams->bMemUpdateForRead)
		{
			if (pFwMem->fw_size < (BE_TOP_HW_O26_IRR_DATA_OFFSET + 4)) BREAK_WRONG(pFwMem->fw_size);

			((UINT32 *)pBuffer)[0] = 0x1; // set mem data header for updating data to read 

			wmb();
		}
		else
		{
			CHECK_NULL(pstParams->irrData.pu32Data);
			if (pstParams->irrData.u32SizeNum == 0) BREAK_WRONG(pstParams->irrData.u32SizeNum);

			outSizeNum = pstParams->irrData.u32SizeNum; 

			outSize = outSizeNum * 4; 

			if ((outSize + BE_TOP_HW_O26_IRR_DATA_OFFSET + 4) > pFwMem->fw_size) BREAK_WRONG(outSize); // 4 : Mem data header

			if (((UINT32 *)pBuffer)[0] != 0x0) BREAK_WRONG(((UINT32 *)pBuffer)[0]);

			ret = copy_to_user((void __user *)pstParams->irrData.pu32Data, (void *)&(((UINT32 *)pBuffer)[1]), outSize);
			if (ret)
			{
				BREAK_WRONG(ret);
			}

			rmb();
		}
	} while(0);

	if (pAddr != NULL) vunmap_phys(pAddr);
	
	return ret;
}

int BE_TOP_HW_O26_SetTpcParam(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 inSizeNum;
	UINT32 inSize;
	int ver = 0x1;
	char *pAddr = NULL;
	char *pBuffer;
	BE_CH_MEM_T *pFwMem = NULL;

	IPC_SET_DEFAULT_PARAM(BE_IPC_TPC_T, stHwParams);

	do{
		CHECK_NULL(pstParams);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);

		pBuffer = (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_TPC_PARAM_OFFSET);

		inSizeNum = pstParams->u32SizeNum;

		inSize = inSizeNum * 4;

		if ((inSize + BE_TOP_HW_O26_TPC_PARAM_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

		ret = copy_from_user((void *)pBuffer, (void __user *)pstParams->pu32Data, inSize);
		if (ret)
		{
			BREAK_WRONG(ret);
		}

		wmb();

		stHwParams.uParamBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_TPC_PARAM_OFFSET;
		stHwParams.uParamDbtype = (ver << 16) | inSizeNum;
		stHwParams.uStatusBaseAddr = pFwMem->fw_base + BE_TOP_HW_O26_TPC_STATUS_OFFSET;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_IPC_TPC_T), (void *)&stHwParams, sizeof(BE_IPC_TPC_T));
		if(ret) BREAK_WRONG(ret);

	} while(0);

	if (pAddr != NULL) vunmap_phys(pAddr);

	return ret;
}

int BE_TOP_HW_O26_GetTpcStatus(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 outSizeNum;
	UINT32 outSize;
	UINT32 magicNum;
	char *pAddr = NULL;
	char *pBuffer;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		CHECK_NULL(pstParams);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(pAddr);

		pBuffer = (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_TPC_STATUS_OFFSET);

		magicNum = ((UINT32 *)pBuffer)[0];

		rmb();

		if (magicNum != 0x12345678)
		{
			BREAK_WRONG(magicNum);
		}

		outSizeNum = ((UINT32 *)pBuffer)[1];

		rmb();

		outSize = outSizeNum * 4;

		if (pstParams->u32SizeNum < outSizeNum)
		{
			BREAK_WRONG(outSizeNum);
		}

		if ((outSize + BE_TOP_HW_O26_TPC_STATUS_OFFSET + 8) > pFwMem->fw_size) BREAK_WRONG(outSize); // magic num(4) + size num(4)

		ret = copy_to_user((void __user *)pstParams->pu32Data, (void *)&(((UINT32 *)pBuffer)[2]), outSize);
		if (ret)
		{
			BREAK_WRONG(ret);
		}

		pstParams->u32SizeNum = outSizeNum;

		rmb();

	} while(0);

	if (pAddr != NULL) vunmap_phys(pAddr);

	return ret;
}

int BE_TOP_HW_O26_GetApiForTpc(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	UINT32 aplL,aplR;
	UINT32 naiveApl;
	UINT32 oapl;
	UINT32 winSize;
	UINT32 data[10];

	do{
		CHECK_NULL(pstParams);

		BE_LED_O26_RdFL(ad_apl_dbg_out);
		BE_LED_O26_Rd01(ad_apl_dbg_out, apl_l, aplL);
		BE_LED_O26_Rd01(ad_apl_dbg_out, apl_r, aplR);

		BE_OLED_O26_RdFL(addr_oapl_ctrl_70);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_70, naive_apl_tcon_mux, naiveApl);

		BE_OLED_O26_RdFL(addr_oapl_ctrl_69);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_69, oled_apl_tcon, oapl);

		BE_REG_RD(0xCC291100, winSize); //ND0_VERI_SYS_VERI_0_T

		data[0] = (aplL + aplR) /2;
		data[1] = naiveApl /2;
		data[2] = oapl;
		data[3] = winSize;

		BE_DEBUG("num:%d,aplL:%d,aplL:%d,naiveApl:%d,oapl:%d,data: %d, %d, %d, %d\n", pstParams->u32SizeNum,aplL,aplR,naiveApl,oapl,data[0],data[1],data[2],data[3]);

		ret = copy_to_user((void __user *)pstParams->pu32Data, (void *)data, 4*sizeof(UINT32));
		if(ret) BREAK_WRONG(ret)
	} while(0);

	return ret;
}

int be_top_hw_o26_get_disp_apl(UINT32 *pu32Param)
{
	UINT32 naive_apl = 0;
	if (pu32Param) {
		BE_OLED_O26_RdFL(addr_oapl_ctrl_70);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_70, naive_apl_tcon_mux, naive_apl);
		pu32Param[0] = (naive_apl>>1);
	}
	return 0;
}

int BE_TOP_HW_O26_SetOledAplCtrlParam(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	UINT32 sel_apl_hdr;
	UINT32 sel_apl_tcon;
	UINT32 out_mode_tcon;
	UINT32 out_mode_hdr;

	UINT32 pBuffer[4]={0};

//			memcpy((void *)p, (void *)param, sizeof(struct v4l2_ext_vbe_panel_apl_control_param_info));
//			BE_ERROR("*******************************************************d:0x%08x,0x%08x,0x%08x,0x%08x (%d,%d,%d,%d)\n",p[0],p[1],p[2],p[3],p[0],p[1],p[2],p[3]);

	if(copy_from_user((void *)pBuffer, (void __user *)pstParams->pu32Data, sizeof(unsigned int)*4))
	{
		BE_ERROR("copy_from_user error\n");
	}

	do{
		CHECK_NULL(pstParams);
		BE_OLED_O26_RdFL(addr_oapl_ctrl_01);
		BE_OLED_O26_Wr01(addr_oapl_ctrl_01, reg_eotf_en, 0x1);
		BE_OLED_O26_WrFL(addr_oapl_ctrl_01);

		BE_OLED_O26_RdFL(addr_oapl_ctrl_00);
		BE_OLED_O26_Wr01(addr_oapl_ctrl_00, reg_in_sel_apl_hdr, pBuffer[0]);
		BE_OLED_O26_Wr01(addr_oapl_ctrl_00, reg_in_sel_apl_tcon, pBuffer[1]);
		BE_OLED_O26_Wr01(addr_oapl_ctrl_00, reg_apl_out_mode_tcon, pBuffer[2]);
		BE_OLED_O26_Wr01(addr_oapl_ctrl_00, reg_apl_out_mode_hdr, pBuffer[3]);
		BE_OLED_O26_WrFL(addr_oapl_ctrl_00);

		BE_OLED_O26_RdFL(addr_oapl_ctrl_00);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_00, reg_in_sel_apl_hdr, sel_apl_hdr);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_00, reg_in_sel_apl_tcon, sel_apl_tcon);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_00, reg_apl_out_mode_hdr, out_mode_hdr);
		BE_OLED_O26_Rd01(addr_oapl_ctrl_00, reg_apl_out_mode_tcon, out_mode_tcon);

		BE_DEBUG("sel_apl_hdr:%d,sel_apl_tcon:%d,out_mode_hdr:%d,out_mode_tcon:%d\n", sel_apl_hdr,sel_apl_tcon,out_mode_hdr,out_mode_tcon);

		if(ret) BREAK_WRONG(ret)
	} while(0);
	return ret;
}

int BE_TOP_HW_O26_SetDispMode(LX_BE_DISP_MODE_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_DISP_MODE_T, stHwParams);
		
		CHECK_NULL(pstParams);

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		if (gTopHwO26Info.pVx1ChipInfoVMapAddr != NULL)
		{
			pstParams->dispResolution = LX_BE_DISP_RESOLUTION_7680;
		}
#endif

		/* change value LX_BE to BE_IPC */
		switch(pstParams->dispResolution)
		{
			case LX_BE_DISP_RESOLUTION_3840:
				stHwParams.uDispResolutionWidth = 3840;  // 4K
				stHwParams.uDispResolutionHeight = 2160; // 4K
				break;

			case LX_BE_DISP_RESOLUTION_7680:
				stHwParams.uDispResolutionWidth = 7680;  // 8K
				stHwParams.uDispResolutionHeight = 4320; // 8K
				break;

			default:
				BE_ERROR("Invalid resolution: %d\n", pstParams->dispResolution);
				ret = RET_INVALID_PARAMS;
				return ret;
		}

		switch(pstParams->dispFrameRate)
		{
			case LX_BE_DISP_FRAME_RATE_30:
				stHwParams.uBoostMode = 2; // 30Hz
				stHwParams.uHighSpeedClock = 0;
				stHwParams.uFrameRate = 30;
				break;
			case LX_BE_DISP_FRAME_RATE_60:
				stHwParams.uBoostMode = 0; // 60Hz
				stHwParams.uHighSpeedClock = 0;
				stHwParams.uFrameRate = 60;
				break;
			case LX_BE_DISP_FRAME_RATE_120:
				stHwParams.uBoostMode = 1; // 120Hz
				stHwParams.uHighSpeedClock = 0;
				stHwParams.uFrameRate = 120;
				break;
			case LX_BE_DISP_FRAME_RATE_VRR:
				stHwParams.uBoostMode = 3; // VRR(120Hz)
				stHwParams.uHighSpeedClock = 1;
				stHwParams.uFrameRate = 120;
				break;
			case LX_BE_DISP_FRAME_RATE_165:
				stHwParams.uBoostMode = 1;
				stHwParams.uHighSpeedClock = 1;
				stHwParams.uFrameRate = 165;
				break;

			default:
				BE_ERROR("Invalid frame rate: %d\n", pstParams->dispFrameRate);
				ret = RET_INVALID_PARAMS;
				return ret;
		}

		if (stHwParams.uHighSpeedClock == 1)
			stHwParams.uFrameRate = 165;
		else if (stHwParams.uBoostMode == 1)
			stHwParams.uFrameRate = 120;
		else if (stHwParams.uBoostMode == 0)
			stHwParams.uFrameRate = 60;
		else if (stHwParams.uBoostMode == 2)
			stHwParams.uFrameRate = 30;
		else if (stHwParams.uBoostMode == 3)
			stHwParams.uFrameRate = 120;

		gTopHwO26Info.disp_mode.uDispResolutionWidth = stHwParams.uDispResolutionWidth;
		gTopHwO26Info.disp_mode.uDispResolutionHeight = stHwParams.uDispResolutionHeight;
		gTopHwO26Info.disp_mode.uFrameRate = stHwParams.uFrameRate;
		gTopHwO26Info.disp_mode.uBoostMode = stHwParams.uBoostMode;
		gTopHwO26Info.disp_mode.uHighSpeedClock = stHwParams.uHighSpeedClock;

		BE_NOTI("uDispResolutionWidth:%d, uDispResolutionHeight:%d, uFrameRate:%d, uBoostMode:%d, uHighSpeedClock:%d\n",
				stHwParams.uDispResolutionWidth, stHwParams.uDispResolutionHeight,
				stHwParams.uFrameRate, stHwParams.uBoostMode, stHwParams.uHighSpeedClock);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DISP_MODE), (void *)&stHwParams, sizeof(BE_IPC_DISP_MODE_T));
		if (ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

/* 20240617, (SICREQ-847)(SICREQ-566)(AVTASK-1433) */
int BE_TOP_HW_O26_SetDClock(UINT32 *pu32Param)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_DISP_MODE_T, stHwParams);

		CHECK_NULL(pu32Param);

		switch (*pu32Param)
		{
			case V4L2_EXT_VBE_DCLK_MODE_BASIC:
				stHwParams.uHighSpeedClock = 0; // 144Hz or lower
				break;
			case V4L2_EXT_VBE_DCLK_MODE_165HZ:
				stHwParams.uHighSpeedClock = 1; // 165Hz
				break;
			default:
				BE_ERROR("Invalid DCLK mode: %d\n", *pu32Param);
				ret = RET_INVALID_PARAMS;
				break;
		}
		if (ret) break;

		if (stHwParams.uHighSpeedClock == 1){
			stHwParams.uFrameRate = 165; // uHighSpeedClock = 1: 165Hz
			stHwParams.uBoostMode = 1;
		}
		else if (gTopHwO26Info.disp_mode.uBoostMode == 1){
			stHwParams.uFrameRate = 120; // uBoostMode = 1: 120Hz
		}
		else if (gTopHwO26Info.disp_mode.uBoostMode == 0){
			stHwParams.uFrameRate = 60;  // uBoostMode = 0 : 60Hz
		}
		else{
			stHwParams.uFrameRate = gTopHwO26Info.disp_mode.uFrameRate;
		}
		gTopHwO26Info.disp_mode.uDispResolutionWidth = stHwParams.uDispResolutionWidth;
		gTopHwO26Info.disp_mode.uDispResolutionHeight = stHwParams.uDispResolutionHeight;
		gTopHwO26Info.disp_mode.uBoostMode = stHwParams.uBoostMode;

		gTopHwO26Info.disp_mode.uHighSpeedClock = stHwParams.uHighSpeedClock;
		gTopHwO26Info.disp_mode.uFrameRate = stHwParams.uFrameRate;

		BE_NOTI("uDispResolutionWidth:%d, uDispResolutionHeight:%d, uFrameRate:%d, uBoostMode:%d, uHighSpeedClock:%d\n",
					   stHwParams.uDispResolutionWidth, stHwParams.uDispResolutionHeight,
					   stHwParams.uFrameRate, stHwParams.uBoostMode, stHwParams.uHighSpeedClock);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DISP_MODE), (void *)&stHwParams, sizeof(BE_IPC_DISP_MODE_T));
		if (ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

#include "de_kapi.h"
int BE_TOP_HW_O26_SetVideoVReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	LX_DE_IF_CONFIG_T stHwParams;

	do{
#ifdef INCLUDE_KDRV_FBDEV
		/* see http://clm.lge.com/issue/browse/SCDCR-4730 */
		{
			extern int FBDEV_O26_CMN_MirrorCtrl(BOOLEAN v_mirror_en);

			FBDEV_O26_CMN_MirrorCtrl(bParam);
		}
#endif
		stHwParams.config_type = LX_DE_CONFIG_TYPE_DISPLAY_MIRROR;
		stHwParams.display_mirror = bParam ? LX_DE_DIS_MIRROR_Y : LX_DE_DIS_MIRROR_OFF;
		stHwParams.display_type = LX_DE_DIS_DEV_MAX;
		stHwParams.frc_type = LX_DE_FRC_PATH_MAX;
		stHwParams.trid_type = LX_DE_3D_CTRL_MAX;

		ret = BE_KIPC_SetData(DE_PACK_CMD(DE_IPC_SET_IF_CONFIG), (void *)&stHwParams, sizeof(LX_DE_IF_CONFIG_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	
	return ret;
}

int BE_TOP_HW_O26_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_DEBUG_DISPLAY_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uLEDDebugDisplay = pstParams->u8LEDDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8LEDDebugDisplay;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DEBUG_DISPLAY), (void *)&stHwParams, sizeof(BE_IPC_DEBUG_DISPLAY_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetFRCStatus(UINT32 u32Param)
{
	int ret = RET_OK;
	
	do{
		if (gTopHwO26Info.frcStatus != u32Param)
		{
			BE_NOTI("FRC status. prev: 0x%x, curr: 0x%x\n", gTopHwO26Info.frcStatus, u32Param);
			BE_REG_WR(0xCC882300, u32Param); //REG_CCO_VERI_SYS_VERI_0_T
			gTopHwO26Info.frcStatus = u32Param;
		}

	} while(0);
	
	return ret;
}

int BE_TOP_HW_O26_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;
//	BE_NOTI(" %d (0:S_PREPARE,1:SUSPEND,2:S_COMPLETED,3:R_PREPARE,4:RESUME,5:R_COMPLETED)\n",u32Param);

	switch (u32Param)
	{
		case BE_TOP_HW_O26_PQE_PM_DEVICE_SUSPEND_PREPARE:
			break;
		case BE_TOP_HW_O26_PQE_PM_DEVICE_SUSPEND:
			break;
		case BE_TOP_HW_O26_PQE_PM_DEVICE_SUSPEND_COMPLETED:
			break;
		case BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_PREPARE:
			break;
		case BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME:
			break;
		case BE_TOP_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED:
			break;
		default:
			break;
	}

	gTopHwO26Info.pmStatus = u32Param;

	BE_LED_HW_O26_SetPmMode(u32Param);

	return ret;
}

int BE_TOP_HW_O26_SetOaplMaxWeight(int Param)
{
	int ret = RET_OK;
	int nParam;
	nParam = Param+100;

	do{
		CHECK_NULL(nParam);

		BE_OLED_O26_RdFL(addr_oapl_ctrl_04);
		BE_OLED_O26_Wr01(addr_oapl_ctrl_04, reg_w_crnt_wgt, nParam);
		BE_OLED_O26_WrFL(addr_oapl_ctrl_04);

		if(ret) BREAK_WRONG(ret)
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;

	BE_NOTI("FBDEV status bFbdevInitDone: %d, bOsdVReverseOn : %d, bEStreamerOn : %d, bOsdSharpnessWAOn : %d\n", 
																							pstParams->bFbdevInitDone,
																							pstParams->bOsdVReverseOn,
																							pstParams->bEStreamerOn,
																							pstParams->bOsdSharpnessWAOn);
	
	do{
		CHECK_NULL(pstParams);
		
		regVal = (pstParams->bOsdSharpnessWAOn << 20) | (pstParams->b4kOSDResolution << 12) | (pstParams->bEStreamerOn << 8) \
				| (pstParams->bOsdVReverseOn << 4) | pstParams->bFbdevInitDone;
		BE_REG_WR(0xCC882308, regVal); //REG_CCO_VERI->SYS_VERI_2

	} while(0);

	return ret;
}

int BE_TOP_HW_O26_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;

	do{
		CHECK_NULL(pstParams);

		// REG_CCO_VERI->SYS_VERI_3
		BE_REG_RD(0xCC88230C, regVal);
		
		pstParams->bFwOsdOrbitInitDone = regVal & 0x1;
		pstParams->bFwOsdSrInitDone = (regVal >> 4) & 0x1;
		pstParams->bFwEstreamerOn = (regVal >> 8) & 0x1;
		
	} while(0);

	return ret;
}

/** BE/TOP O26 proc handler */
int BE_TOP_HW_O26_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	switch(proc_id)
	{
		case BE_TOP_PROC_ID_DETAIL_INFO:
		{
			seq_printf(m, "uDispResolutionWidth:%d, uDispResolutionHeight:%d, uFrameRate:%d, uHighSpeedClock:%d, uBoostMode:%d\n",
					   gTopHwO26Info.disp_mode.uDispResolutionWidth,
					   gTopHwO26Info.disp_mode.uDispResolutionHeight,
					   gTopHwO26Info.disp_mode.uFrameRate,
					   gTopHwO26Info.disp_mode.uHighSpeedClock,
					   gTopHwO26Info.disp_mode.uBoostMode);
		}
		break;
		case BE_TOP_PROC_ID_ORBIT_INFO:
		{
			seq_printf(m, "vbe_orbit_on=%d\n", gTopHwO26Info.orbitInfo.bOnOff);
			seq_printf(m, "vbe_orbit_set_mode=%d\n", gTopHwO26Info.orbitInfo.bStoreMode ? 2 : gTopHwO26Info.orbitInfo.bAutoMode);
		}
		break;
		case BE_TOP_PROC_ID_LSR_INFO:
		{
			BE_CH_MEM_T *pFwMem = NULL;
			char *pBuffer = NULL;
			char *pAddr = NULL;
			int i = 0;

			seq_printf(m, "vbe_lsr_tbl=");
			do{
				if (gTopHwO26Info.lsrSize > 0)
				{
					pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
					CHECK_NULL(pFwMem);
					CHECK_NULL(pFwMem->fw_base);

					if ((gTopHwO26Info.lsrSize + BE_TOP_HW_O26_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(gTopHwO26Info.lsrSize);

					pBuffer = (char *)vmalloc(gTopHwO26Info.lsrSize);
				 	CHECK_NULL(pBuffer);

					pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
					CHECK_NULL(pAddr);

					memcpy(pBuffer, (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_LSR_TABLE_OFFSET), gTopHwO26Info.lsrSize);

					rmb();

					vunmap_phys(pAddr);

					for(i=0; i < (gTopHwO26Info.lsrSize/sizeof(UINT32)); i++)
					{
						seq_printf(m, "0x%x", ((UINT32 *)pBuffer)[i]);

						if (i+1 < (gTopHwO26Info.lsrSize/sizeof(UINT32)))
							seq_printf(m, ", ");
					}
				}
			} while(0);

			seq_printf(m, "\n");
			if (pBuffer != NULL)
			{
				vfree(pBuffer);
			}
		}
		break;
		case BE_TOP_PROC_ID_GSR_INFO:
		{
			BE_CH_MEM_T *pFwMem = NULL;
			char *pBuffer = NULL;
			char *pAddr = NULL;
			int i = 0;

			seq_printf(m, "vbe_gsr_tbl=");
			do{
				if (gTopHwO26Info.gsrSize > 0)
				{
					pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
					CHECK_NULL(pFwMem);
					CHECK_NULL(pFwMem->fw_base);

					if ((gTopHwO26Info.gsrSize + BE_TOP_HW_O26_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(gTopHwO26Info.gsrSize);

					pBuffer = (char *)vmalloc(gTopHwO26Info.gsrSize);
				 	CHECK_NULL(pBuffer);

					pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
					CHECK_NULL(pAddr);

					memcpy(pBuffer, (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O26_GSR_TABLE_OFFSET), gTopHwO26Info.gsrSize);

					rmb();

					vunmap_phys(pAddr);

					for(i=0; i < (gTopHwO26Info.gsrSize/sizeof(UINT32)); i++)
					{
						seq_printf(m, "0x%x", ((UINT32 *)pBuffer)[i]);

						if (i+1 < (gTopHwO26Info.gsrSize/sizeof(UINT32)))
							seq_printf(m, ", ");
					}
				}
			} while(0);

			seq_printf(m, "\n");
			if (pBuffer != NULL)
			{
				vfree(pBuffer);
			}
		}
		break;
		case BE_TOP_PROC_ID_OSDLVL_INFO:
		{
			LX_BE_LUT_T pstParams;
			pstParams.u32SizeNum = 1;

			BE_TOP_HW_O26_GetOSDAlphaAPL(&pstParams);
			seq_printf(m, "vbe_osd_alpha_val=%d\n", gTopHwO26Info.osdLvl);
			seq_printf(m, "vbe_osd_gain=%d\n", gTopHwO26Info.osdGain);
		}
		break;
		case BE_TOP_PROC_ID_CPC_INFO:
		{
			seq_printf(m, "vbe_cpc=%d\n", gTopHwO26Info.cpc);
			{
				BE_CH_MEM_T *pFwMem = NULL;

				pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
				CHECK_NULL(pFwMem);
				CHECK_NULL(pFwMem->fw_base);
				seq_printf(m, "vbe_mem_base=0x%x\n", pFwMem->fw_base);
				seq_printf(m, "vbe_mem_tpc_param_addr=0x%x\n", pFwMem->fw_base + BE_TOP_HW_O26_TPC_PARAM_OFFSET);
				seq_printf(m, "vbe_mem_tpc_status_addr=0x%x\n", pFwMem->fw_base + BE_TOP_HW_O26_TPC_STATUS_OFFSET);
			}
		}
		break;

		default: break;
	}

	return ret;
}

// only for +W22 AV wireless model W/A(SCDCR-3962)
// 20250508, W26, moved to chipinfo (SICDTV-15633)
int BE_TOP_HW_O26_GetPatternInfo(void *pParam, UINT32 *size)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 readSize;
	__attribute__((unused)) char *pAddr = NULL;
	__attribute__((unused)) UINT32 *rdPtr;
	__attribute__((unused)) UINT32 bufSize = *size;

	do{
		CHECK_NULL(pParam);
		CHECK_NULL(size);
		if (bufSize > 1024) BREAK_WRONG(bufSize);

		CHECK_NULL(gpBeChInfMem);
		CHECK_NULL(gpBeChInfMem->frame_base);
		if (gpBeChInfMem->frame_size < 2048) BREAK_WRONG(gpBeChInfMem->frame_size);

		pAddr = (char *)vmap_phys(gpBeChInfMem->frame_base, 2048);
		CHECK_NULL(pAddr);

		rdPtr = (UINT32 *)((char *)pAddr);

		if (rdPtr[0] != 0x12346789) // rdPtr[0] -> magic number
		{
			*size = 0;
			break;
		}

		rdPtr++;

		if (rdPtr[0] > bufSize) BREAK_WRONG(bufSize); // rdPtr[0] -> data size

		ret = copy_to_user((void __user *)pParam, (void *)rdPtr, rdPtr[0]);
		if(ret) BREAK_WRONG(ret);

		*size = rdPtr[0];
		BE_TRACE1("size:%d\n",*size);

		rmb();	
	} while(0);

	if (pAddr != NULL) vunmap_phys(pAddr);
	
	return ret;
}

int BE_TOP_HW_O26_SetGenlock(LX_BE_SET_GENLOCK_T *pstParams)
{

	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_GENLOCK_MODE_T, stHwParams);

		CHECK_NULL(pstParams);
//		BE_REG_WR(0xcec8210c, 0x20000220); //genlock port setting
		stHwParams.bOnOff  = pstParams->genlock & 0x1;
		stHwParams.mode = (pstParams->genlock & 0x1FFE) >> 1;
		stHwParams.phase = 0;

		/* change value LX_BE to BE_IPC */
		BE_PRINT("SetGenlock :%d %d %d\n",stHwParams.bOnOff,stHwParams.mode,stHwParams.phase);
		ret = BE_KIPC_SetData(DE_PACK_CMD(0x0000006B), (void *)&stHwParams, sizeof(BE_IPC_GENLOCK_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetPcce(LX_BE_IPC_PCCE_T *pstParams)
{
	int ret = RET_OK;

	do{
		CHECK_NULL(pstParams);
		// printk("[MHLEE] %s(), pstParams->d0.enable[%d]\n", __func__, pstParams->d0.enable);
		BE_PRINT("SetPcce : %d\n", pstParams->d0.enable);
		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_PCCE), (void *)pstParams, sizeof(LX_BE_IPC_PCCE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_O26_SetOutputTiming(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams)
{
	int ret = RET_OK;

	do {
		IPC_SET_DEFAULT_PARAM(BE_IPC_DISP_MODE_T, stHwParams);
		CHECK_NULL(pstParams);

		if (pstParams->hResolution != 3840)
		{
			BE_ERROR("Invalid hResolution: %d (only 3840 allowed)\n", pstParams->hResolution);
			ret = RET_INVALID_PARAMS;
			break;
		}

		switch (pstParams->vResolution)
		{
			case 1080:
				stHwParams.uDispResolutionWidth = 3840;
				stHwParams.uDispResolutionHeight = 1080;
				break;
			case 2160:
				stHwParams.uDispResolutionWidth = 3840;
				stHwParams.uDispResolutionHeight = 2160;
				break;
			default:
				BE_ERROR("Invalid vResolution: %d (only 1080 or 2160 allowed)\n", pstParams->vResolution);
				ret = RET_INVALID_PARAMS;
				break;
		}
		if (ret) break;

		switch (pstParams->frameRate)
		{
			case 120:
				stHwParams.uFrameRate = 120;
				stHwParams.uBoostMode = 1;
				stHwParams.uHighSpeedClock = 0;
				break;
			case 144:
				stHwParams.uFrameRate = 144;
				stHwParams.uBoostMode = 1;
				stHwParams.uHighSpeedClock = 1;
				break;
			case 165:
				stHwParams.uFrameRate = 165;
				stHwParams.uBoostMode = 3;
				stHwParams.uHighSpeedClock = 1;
				break;
			case 240:
				stHwParams.uFrameRate = 240;
				stHwParams.uBoostMode = 3;
				stHwParams.uHighSpeedClock = 0;
				break;
			case 288:
				stHwParams.uFrameRate = 288;
				stHwParams.uBoostMode = 3;
				stHwParams.uHighSpeedClock = 1;
				break;
			case 330:
				stHwParams.uFrameRate = 330;
				stHwParams.uBoostMode = 3;
				stHwParams.uHighSpeedClock = 1;
				break;
			default:
				BE_ERROR("Invalid frameRate: %d (only 120, 144, 165, 240, 288, 330 allowed)\n", pstParams->frameRate);
				ret = RET_INVALID_PARAMS;
				break;
		}
		if (ret) break;
//		stHwParams.uBoostMode = 0;
//		stHwParams.uHighSpeedClock = 0;

		gTopHwO26Info.disp_mode.uDispResolutionWidth = stHwParams.uDispResolutionWidth;
		gTopHwO26Info.disp_mode.uDispResolutionHeight = stHwParams.uDispResolutionHeight;
		gTopHwO26Info.disp_mode.uBoostMode = stHwParams.uBoostMode;
		gTopHwO26Info.disp_mode.uHighSpeedClock = stHwParams.uHighSpeedClock;
		gTopHwO26Info.disp_mode.uFrameRate = stHwParams.uFrameRate;

		BE_NOTI("uDispResolutionWidth:%d, uDispResolutionHeight:%d, uFrameRate:%d, uBoostMode:%d, uHighSpeedClock:%d\n",
				stHwParams.uDispResolutionWidth, stHwParams.uDispResolutionHeight,
				stHwParams.uFrameRate, stHwParams.uBoostMode, stHwParams.uHighSpeedClock);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DISP_MODE), (void *)&stHwParams, sizeof(BE_IPC_DISP_MODE_T));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

/** @} */
