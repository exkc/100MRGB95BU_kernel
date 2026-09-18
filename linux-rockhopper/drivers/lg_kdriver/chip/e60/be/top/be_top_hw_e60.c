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
#define BE_TOP_HW_E60_USE_VX1_CHIP_INFO 1

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
#include "../fwi/ipc_def_e60.h"
#include "ipc_drv.h"
#include "be_top_hw_e60.h"

// For Video InputLag Test
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>

#include "../gpio/gpio_drv.h"
#include "../gpio/gpio_core.h"


// For CTOP/DPE register access
#include "../../../core/sys/sys_regs.h"
#include "../reg/be_reg_dpe_e60.h"

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

#if BE_TOP_HW_E60_USE_VX1_CHIP_INFO
#include "ovi_hal.h"
#include "../../ovi/ovi_hw_e60.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define BE_TOP_HW_E60_LSR_TABLE_OFFSET 0x800
#define BE_TOP_HW_E60_GSR_TABLE_OFFSET (BE_TOP_HW_E60_LSR_TABLE_OFFSET + 0x800)
#define BE_TOP_HW_E60_OSD_ALPHA_TABLE_OFFSET (BE_TOP_HW_E60_GSR_TABLE_OFFSET + 0x800)
#define BE_TOP_HW_E60_GSR2_TABLE_OFFSET (BE_TOP_HW_E60_OSD_ALPHA_TABLE_OFFSET + 0x800)

#define BE_TOP_HW_E60_TEST_INPUT_LAG
#ifdef BE_TOP_HW_E60_TEST_INPUT_LAG
#define	BE_TOP_HW_E60_IPP_LAG_CTRL0_BASE		(0xC9014490) //o18: 0xC9014448, m16p3: 0xC9014448
#define	BE_TOP_HW_E60_IPP_PIXEL_ACTIVE_RIGING	(0xC901405C) // AVTASK-371

#define	BE_TOP_HW_E60_IPP_LAG_CTRL1_BASE	(0xC9014494) //SCDCR-2484
#define	BE_TOP_HW_E60_IPP_LAG_CTRL2_BASE	(0xC9014498)
#define BE_TOP_HW_E60_PATTE

#define BE_TOP_HW_E60_PATTERN_OFF		(0)
#define BE_TOP_HW_E60_PATTERN_ON		(1)
#define BE_TOP_HW_E60_PATTERN_BLACK		(0) //0x88080200
#define BE_TOP_HW_E60_PATTERN_WHITE		(1) //0xBFF80200

#define BE_TOP_HW_E60_PIN_MUX_PORT		(119)
#define BE_TOP_HW_E60_PIN_NORMAL		(0)
#define BE_TOP_HW_E60_PIN_GPIO			(1)
#endif

#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
#define BE_OSD_HW_F20_REG_OSD_GSR_CTRL 0xF035A5B0

#define _B2L32(data) ((((data) >> 24) & 0x000000ff) |   \
         			(((data) >>  8) & 0x0000ff00) |   \
         			(((data) <<  8) & 0x00ff0000) |   \
         			(((data) << 24) & 0xff000000))
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
typedef struct {
	LX_BE_ORBIT_T 	orbitInfo;
	UINT32			  lsrSize;
	UINT32			  gsrSize;
	UINT32			   osdLvl;
	UINT32 				  cpc;
#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
	void *pVx1ChipInfoVMapAddr;
	BE_OVI_HW_E60_VX1_CHIP_INFO_T *pVx1ChipInfo[BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_NUM];
#endif
	UINT32 			frcStatus;
} BE_TOP_HW_E60_INFO_T;

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
#ifdef BE_TOP_HW_E60_TEST_INPUT_LAG
extern BE_MEM_CFG_T *gpBeMem;
extern DPE_LED_REG_E60_T gDPE_LED_E60;
#endif
extern DPE_OLED_REG_E60_T gDPE_OLED_E60;
extern PE_OSD_REG_E60_T gPE_OSD_E60;

//#if 0
struct gpio_desc *gpiod_de_e60;
struct device de_gpio_dev_e60 = { .init_name = "gpio_kerneltable", }; //GPIO INIT CONTROL
//#endif
//extern struct gpio_desc *gpiod_de_e60;
//extern struct device de_gpio_dev_e60;

#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
extern BE_FRM_MEM_CFG_T *gpBeChInfMem;
#endif

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile LAG_CTRL1 *gBE_TOP_HW_E60_LAG_CTRL1 = NULL;
volatile LAG_CTRL2 *gBE_TOP_HW_E60_LAG_CTRL2 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef BE_TOP_HW_E60_TEST_INPUT_LAG
static int BE_TOP_HW_E60_InitLagPattern(void);
int BE_TOP_HW_E60_InputLagHandler(void);
static int BE_TOP_HW_E60_SetPattern(UINT32 bOnOff);
static int BE_TOP_HW_E60_SetGpioValue(UINT32 value);
static int BE_TOP_HW_E60_SetGpioMux(UINT32 value);
#endif

#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
static int _BE_TOP_E60_InitVx1ChipInfoMem(void);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 g_be_top_hw_E60_pattern_init = 0;
static LX_BE_INPUT_LAG_PATTERN_T gCurPatternParam;
static LX_BE_INPUT_LAG_PATTERN_T gPrePatternParam;

static UINT32 gInputLagCnt = 0;
static volatile UINT32	*gIPP_LAG_CTRL0 = NULL;
static volatile UINT32	*gIPP_PIXEL_CTRL_ACTIVE_RIGING = NULL;

static BE_TOP_HW_E60_INFO_T gTopHwE60Info;
/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
static int _BE_TOP_E60_InitVx1ChipInfoMem(void)
{
	int ret = RET_OK;
	BE_FRM_MEM_CFG_T *pChInfMem = gpBeChInfMem;
	LX_OVI_HW_DISPLAY_INFO_T dispInfo;
	int i;
		
	do {
		gTopHwE60Info.pVx1ChipInfoVMapAddr = NULL;

		ret = OVI_HAL_GetHWDisplayOption(&dispInfo);
		if (ret) BREAK_WRONG(ret);

		if (dispInfo.frcChipType != LX_OVI_FRC_CHIP_UD_BE_F20) break;
		
		CHECK_NULL(pChInfMem);
		CHECK_NULL(pChInfMem->frame_base);
		
		if ((pChInfMem->frame_size != BE_OVI_HW_E60_VX1_CHIP_INFO_TOTAL_MEM_SIZE)
			|| (sizeof(BE_OVI_HW_E60_VX1_CHIP_INFO_T) != BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE))
		{
			BE_ERROR("[BE] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		gTopHwE60Info.pVx1ChipInfoVMapAddr = vmap_phys(pChInfMem->frame_base, pChInfMem->frame_size);
		CHECK_NULL(gTopHwE60Info.pVx1ChipInfoVMapAddr);

		for (i=0; i<BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
		{
			if (pChInfMem->frame_size < ((BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
											+BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET \
											+sizeof(BE_OVI_HW_E60_VX1_CHIP_INFO_T))) break;
			
			gTopHwE60Info.pVx1ChipInfo[i] = (BE_OVI_HW_E60_VX1_CHIP_INFO_T *)(gTopHwE60Info.pVx1ChipInfoVMapAddr \
																			+(BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
																			+BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
		}
		if (i != BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_NUM)
		{
			BE_ERROR("[BE] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}
	} while(0);

	if (ret && (gTopHwE60Info.pVx1ChipInfoVMapAddr != NULL))
	{
		vunmap_phys(gTopHwE60Info.pVx1ChipInfoVMapAddr);
		gTopHwE60Info.pVx1ChipInfoVMapAddr = NULL;
	}

	return ret;
}
#endif

int BE_TOP_HW_E60_Initialize(void)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;

	do {
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_WR(0xC902E52C, pFwMem->fw_base + BE_TOP_HW_E60_OSD_ALPHA_TABLE_OFFSET);

#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
		ret = _BE_TOP_E60_InitVx1ChipInfoMem();
		if (ret) BREAK_WRONG(ret);
#endif
		gTopHwE60Info.frcStatus = 0;
	} while(0);

	return ret;
}

int BE_TOP_HW_E60_Resume(void)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;

	do {
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_WR(0xC902E52C, pFwMem->fw_base + BE_TOP_HW_E60_OSD_ALPHA_TABLE_OFFSET);

	} while(0);

	return ret;
}

int BE_TOP_HW_E60_Close(void)
{
	int ret = RET_OK;

	do {
#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
		if (gTopHwE60Info.pVx1ChipInfoVMapAddr != NULL)
		{
			vunmap_phys(gTopHwE60Info.pVx1ChipInfoVMapAddr);
			gTopHwE60Info.pVx1ChipInfoVMapAddr = NULL;
		}
#endif
	} while(0);

	return ret;
}

int BE_TOP_HW_E60_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLOCK_BYPASS_T, stHwParams);

		if (pstParams->bLEDBypass <= 1)
		{
			DPE_LED_E60_RdFL(led_led_detour);
			if (pstParams->bLEDBypass)
			{
				DPE_LED_E60_Wr01(led_led_detour, led_detour, 0x1);
			}
			else
			{
				DPE_LED_E60_Wr01(led_led_detour, led_detour, 0x0);
			}
			DPE_LED_E60_WrFL(led_led_detour);
		}
		
		/* change value LX_BE to BE_IPC */
		stHwParams.uFRCBypass = (pstParams->bFRCBypass > 1) ? 0xFFFFFFFF : pstParams->bFRCBypass;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLOCK_BYPASS), (void*)&stHwParams, sizeof(BE_IPC_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_E60_SetOrbit(LX_BE_ORBIT_T *pstParams)
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

		memcpy(&gTopHwE60Info.orbitInfo, pstParams, sizeof(LX_BE_ORBIT_T));
	} while(0);

	return ret;
}

#ifdef BE_TOP_HW_E60_TEST_INPUT_LAG
static int BE_TOP_HW_E60_InitLagPattern(void)
{
	gIPP_LAG_CTRL0 = (volatile UINT32 *)ioremap(BE_TOP_HW_E60_IPP_LAG_CTRL0_BASE, sizeof(UINT32));
	gIPP_PIXEL_CTRL_ACTIVE_RIGING = (volatile UINT32 *)ioremap(BE_TOP_HW_E60_IPP_PIXEL_ACTIVE_RIGING, sizeof(UINT32));

	gBE_TOP_HW_E60_LAG_CTRL1 = (volatile LAG_CTRL1 *)ioremap(BE_TOP_HW_E60_IPP_LAG_CTRL1_BASE, sizeof(LAG_CTRL1));
	gBE_TOP_HW_E60_LAG_CTRL2 = (volatile LAG_CTRL2 *)ioremap(BE_TOP_HW_E60_IPP_LAG_CTRL2_BASE, sizeof(LAG_CTRL2));

	/* move to below line to init(to get gpiod_de_e60 only one time */
	gpiod_de_e60 = gpiod_get(&de_gpio_dev_e60, "119", GPIOD_OUT_HIGH);

	gPrePatternParam.enable = BE_TOP_HW_E60_PATTERN_OFF;
	gPrePatternParam.type = 0xff;
	gPrePatternParam.hoffset = 0;
	gPrePatternParam.voffset = 0;
	gPrePatternParam.hsize = 0;
	gPrePatternParam.vsize = 0;

	return RET_OK;
}

int BE_TOP_HW_E60_SetLagParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams)
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
		g_be_top_hw_E60_pattern_init,pstParams->enable,pstParams->type,\
		pstParams->hoffset,pstParams->voffset,pstParams->hsize,pstParams->vsize);

	if (!g_be_top_hw_E60_pattern_init)
	{
		BE_TOP_HW_E60_InitLagPattern();
		g_be_top_hw_E60_pattern_init = 1;
	}

	gCurPatternParam = *pstParams;
	cur_enable = gCurPatternParam.enable;
	pre_enable = gPrePatternParam.enable;

	do {
		CHECK_KNULL(gBE_TOP_HW_E60_LAG_CTRL1);
		CHECK_KNULL(gBE_TOP_HW_E60_LAG_CTRL2);

		if (pre_enable == cur_enable)		break;
		if (cur_enable == BE_TOP_HW_E60_PATTERN_ON)
		{
			/* interrupt enable */
#ifdef INCLUDE_KDRV_DE
			ipc_phys_hal_InitInterrupt(0, TRUE);
#endif
			gPrePatternParam.type = 0xff;
			*gIPP_PIXEL_CTRL_ACTIVE_RIGING = 0x84002000;

			pix_lag_ctrl1 = *gBE_TOP_HW_E60_LAG_CTRL1;
			pix_lag_ctrl1.lag_x_start = pstParams->hoffset;
			pix_lag_ctrl1.lag_x_end = pstParams->hoffset + pstParams->hsize;
			*gBE_TOP_HW_E60_LAG_CTRL1 = pix_lag_ctrl1;

			pix_lag_ctrl2 = *gBE_TOP_HW_E60_LAG_CTRL2;
			pix_lag_ctrl2.lag_y_start = pstParams->voffset;
			pix_lag_ctrl2.lag_y_end = pstParams->voffset + pstParams->vsize;
			*gBE_TOP_HW_E60_LAG_CTRL2 = pix_lag_ctrl2;
			BE_NOTI("SetLagParam_Position rect[%d/%d/%d/%d]\n",pix_lag_ctrl1.lag_x_start,pix_lag_ctrl1.lag_x_end,pix_lag_ctrl2.lag_y_start, 
			pix_lag_ctrl2.lag_y_end);
			/* register handle */
#ifdef INCLUDE_KDRV_DE
			de_srcsync_register(TRUE, BE_TOP_HW_E60_InputLagHandler, "inputLag_handler");
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
			*gBE_TOP_HW_E60_LAG_CTRL1 = pix_lag_ctrl1;
			pix_lag_ctrl2.lag_y_start = 0;
			pix_lag_ctrl2.lag_y_end = 0;
			*gBE_TOP_HW_E60_LAG_CTRL2 = pix_lag_ctrl2;
#ifdef INCLUDE_KDRV_DE
			de_srcsync_register(FALSE, BE_TOP_HW_E60_InputLagHandler, "inputLag_handler");
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

int BE_TOP_HW_E60_InputLagHandler(void)
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

	if (cur_enable != BE_TOP_HW_E60_PATTERN_ON)
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
		CHECK_KNULL(gpiod_de_e60);
		if (pre_type == cur_type)		break;

		if (cur_type == BE_TOP_HW_E60_PATTERN_WHITE) //white pattern
		{
			BE_TOP_HW_E60_SetPattern(BE_TOP_HW_E60_PATTERN_WHITE); //White
		}
		else	//black pattern
		{
			BE_TOP_HW_E60_SetPattern(BE_TOP_HW_E60_PATTERN_BLACK); //Black
		}

		gPrePatternParam.type = gCurPatternParam.type;
		gpio_cnt = 5;
		BE_NOTI("type changed:%d <- %d, gpio:%d, tick diff:%llu (%llu <- %llu)",\
			cur_type,pre_type,gpio_value,tick_diff,curr_msec_tick,prev_msec_tick);
	} while(0);

	if (gpio_cnt == 4)
	{
		gpiod_set_raw_value(gpiod_de_e60, (cur_type == BE_TOP_HW_E60_PATTERN_WHITE)? 1:0);
		gpio_value = gpiod_get_raw_value(gpiod_de_e60);
		BE_NOTI("GPIO_Set --> gpio_cnt: %d",gpio_cnt);
		#if 0	//legacy
		if (cur_type == 0) //Blck pattern
		{
			BE_NOTI("gpiod_de_e60 return %d", gpiod_de_e60);
			gpiod_set_raw_value(gpiod_de_e60 ,(cur_type == 0)? 0:1);
			gpio_value = gpiod_get_raw_value(gpiod_de_e60);
			//BE_NOTI("SET_GPIO %d ", gpio_value?"HIGH":"LOW");
		}
		else	//white pattern
		{
			BE_NOTI("gpiod_de_e60 return %d", gpiod_de_e60);
			gpiod_set_raw_value(gpiod_de_e60 ,1);
			gpio_value = gpiod_get_raw_value(gpiod_de_e60);
			//BE_NOTI("SET_GPIO %d ", gpio_value?"HIGH":"LOW");
		}
		#endif
	}

	if (gpio_cnt > 0) gpio_cnt--;

	return 0;
}

static int BE_TOP_HW_E60_SetPattern(UINT32 bOnOff)
{
	if (bOnOff == BE_TOP_HW_E60_PATTERN_WHITE)
	{
		*gIPP_LAG_CTRL0 = 0xBFF80200;
	}
	else if (bOnOff == BE_TOP_HW_E60_PATTERN_BLACK)
	{
		*gIPP_LAG_CTRL0 = 0x88080200;
	}
	return 0;
}
#if 0 // not used
static int BE_TOP_HW_E60_SetGpioValue(UINT32 value)
{
//	GPIO_DevSetValue(BE_TOP_HW_E60_PIN_MUX_PORT, value);

	return 0;
}

static int BE_TOP_HW_E60_SetGpioMux(UINT32 value)
{
//	GPIO_DevSetPinMux(BE_TOP_HW_E60_PIN_MUX_PORT, value);
//	GPIO_DevSetMode(TEST_GPIO_CONTROL, LX_GPIO_MODE_OUTPUT);
	
	return 0;
}
#endif
#endif

int BE_TOP_HW_E60_SetLSRParam(LX_BE_LSR_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	int lsrTblVer = 0x2;
	char *pBuffer = NULL;
	char *pAddr = NULL;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_LSR_T, stHwParams);

		CHECK_NULL(pstParams);
		CHECK_NULL(pstParams->lsrTbl.pu32Data);

		inSizeNum = pstParams->lsrTbl.u32SizeNum;

		// E60 TEMP
		if (inSizeNum == 0)
		{
			inSizeNum = 35;
			lsrTblVer = 0x1;
		}

		inSize = inSizeNum * sizeof(pstParams->lsrTbl.pu32Data[0]);
		gTopHwE60Info.lsrSize = inSize;
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_E60_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_E60_LSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bLSRMode = (pstParams->u32LsrMode) >= 0xFF ? 0xFFFFFFFF : (pstParams->u32LsrMode);
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_E60_LSR_TABLE_OFFSET;
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

int BE_TOP_HW_E60_SetGSR(LX_BE_GSR_T *pstParams)
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

		// E60 TEMP
		if (inSizeNum == 0) inSizeNum = 16;

		inSize = inSizeNum * sizeof(pstParams->gsrTbl.pu32Data[0]);
		gTopHwE60Info.gsrSize = inSize;
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_E60_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_E60_GSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bGSRMode = 1;
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_E60_GSR_TABLE_OFFSET;
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

int BE_TOP_HW_E60_SetGSR2(LX_BE_GSR_T *pstParams)
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

		// E60 TEMP
		if (inSizeNum == 0) inSizeNum = 16;

		inSize = inSizeNum * sizeof(pstParams->gsrTbl.pu32Data[0]);
		gTopHwE60Info.gsrSize = inSize;
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_E60_GSR2_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_E60_GSR2_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bGSRMode = 1;
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_E60_GSR2_TABLE_OFFSET;
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

int BE_TOP_HW_E60_GetGSRStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;
	UINT32 regVal;

	do{
		CHECK_NULL(pbParam);

		BE_REG_RD(0xC902E528, regVal);

		*pbParam = (regVal & 0x40) ? TRUE : FALSE;
	} while(0);
	
	return ret;
}

int BE_TOP_HW_E60_GetGSRStressCount(UINT32 *pu32Param)
{
	int ret = RET_OK;
	UINT32 regVal;

	do{
		CHECK_NULL(pu32Param);

#if 0 // To Do..
		BE_REG_RD(0xC9012214, regVal); // CCO_VERI, sys_veri_5

		*pu32Param = regVal;
#else
		*pu32Param = 0;
#endif
	} while(0);
	
	return ret;
}

int BE_TOP_HW_E60_SetCPC(UINT32 u32Param)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_CPC_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uCPCParam = u32Param;
		gTopHwE60Info.cpc = u32Param;

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

int BE_TOP_HW_E60_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal;
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

	do{
		CHECK_NULL(pstParams);

		if (pstParams->u32SizeNum != 16) BREAK_WRONG(pstParams->u32SizeNum);

		// REG_CC_E_PE1_FSW_CTRL_03
		BE_REG_RD(0xC902E52C, regVal);
		if (regVal != 0x1) BREAK_WRONG(regVal);

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		restSize = ((pFwMem->fw_base + BE_TOP_HW_E60_OSD_ALPHA_TABLE_OFFSET) & (PAGE_SIZE - 1));
		alignedBase = ((pFwMem->fw_base + BE_TOP_HW_E60_OSD_ALPHA_TABLE_OFFSET) & (~(PAGE_SIZE - 1)));

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

		ret = copy_to_user((void __user *)pstParams->pu32Data, arrData, sizeof(arrData));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}

	return ret;
}

int BE_TOP_HW_E60_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 arrData[1];

	do{
		CHECK_NULL(pstParams);

		if (pstParams->levelTbl.u32SizeNum != 1) BREAK_WRONG(pstParams->levelTbl.u32SizeNum);

		ret = copy_from_user(arrData, (void __user *)pstParams->levelTbl.pu32Data, sizeof(UINT32)*(pstParams->levelTbl.u32SizeNum));
		if(ret) BREAK_WRONG(ret);

#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
		if (gTopHwE60Info.pVx1ChipInfoVMapAddr != NULL)
		{
			UINT32 dataSize;
			UINT32 regVal = 0;
			int i;
#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO_APB_SLAVE
			BE_OVI_HW_E60_VX1_CHIP_INFO_APB_CNT2_T count;
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

			for (i=0; i<BE_OVI_HW_E60_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
			{
				dataSize = 0;
				
				gTopHwE60Info.pVx1ChipInfo[i]->osdLvCtrl.osdLvCtrlRegAddr = _B2L32(BE_OSD_HW_F20_REG_OSD_GSR_CTRL); dataSize++;
				gTopHwE60Info.pVx1ChipInfo[i]->osdLvCtrl.osdLvCtrlVal = _B2L32(regVal); dataSize++;
				dataSize = sizeof(UINT32) * dataSize;

#ifndef BE_OVI_HW_E60_USE_VX1_CHIP_INFO_APB_SLAVE
				gTopHwE60Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
#endif

				if (dataSize != BE_HW_E60_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE) BREAK_WRONG(dataSize);

				wmb();
				
#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO_APB_SLAVE
				count.u32Data = _B2L32(gTopHwE60Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data);

				if (count.osdLvCtrl == 0xF)
				{
					count.osdLvCtrl = 1;
				}
				else
				{
					count.osdLvCtrl++;
				}

				gTopHwE60Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data = _B2L32(count.u32Data);
#else
				gTopHwE60Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32((0x0A000000|BE_HW_E60_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE));
#endif

				wmb();
			}
			if (ret != RET_OK) break;
		}
		else
		{
#endif
			PE_OSD_E60_RdFL(osd0_gsr_ctrl_0);
			PE_OSD_E60_Wr01(osd0_gsr_ctrl_0, reg_gsr_blend_en, pstParams->bOnOff ? 0x1 : 0x0);
			if (arrData[0] == 0xFF)
			{
				PE_OSD_E60_Wr01(osd0_gsr_ctrl_0, reg_gsr_master_gain, 0x3FF);
			}
			else
			{
				PE_OSD_E60_Wr01(osd0_gsr_ctrl_0, reg_gsr_master_gain, (( arrData[0]) << 2));
			}
			PE_OSD_E60_WrFL(osd0_gsr_ctrl_0);
#ifdef BE_OVI_HW_E60_USE_VX1_CHIP_INFO
		}
#endif

	} while(0);

	return ret;
}

int BE_TOP_HW_E60_SetDispMode(LX_BE_DISP_MODE_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_DISP_MODE_T, stHwParams);
		
		CHECK_NULL(pstParams);

		/* change value LX_BE to BE_IPC */
		switch(pstParams->dispResolution)
		{
			case LX_BE_DISP_RESOLUTION_3840:
				stHwParams.uDispResolution = 0;
				break;

			case LX_BE_DISP_RESOLUTION_7680:
				stHwParams.uDispResolution = 1;
				break;

			default:
				ret = RET_INVALID_PARAMS;
				return ret;
		}
		
		switch(pstParams->dispFrameRate)
		{
			case LX_BE_DISP_FRAME_RATE_30:
				stHwParams.uFrameRate = 2;
				break;

			case LX_BE_DISP_FRAME_RATE_60:
				stHwParams.uFrameRate = 0;
				break;

			case LX_BE_DISP_FRAME_RATE_120:
				stHwParams.uFrameRate = 1;
				break;

			case LX_BE_DISP_FRAME_RATE_VRR:
				stHwParams.uFrameRate = 3;
				break;

			default:
				ret = RET_INVALID_PARAMS;
				return ret;
		}

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DISP_MODE), (void *)&stHwParams, sizeof(BE_IPC_DISP_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	
	return ret;
}

#include "de_kapi.h"
int BE_TOP_HW_E60_SetVideoVReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	LX_DE_IF_CONFIG_T stHwParams;

	do{
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

int BE_TOP_HW_E60_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams)
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

int BE_TOP_HW_E60_SetFRCStatus(UINT32 u32Param)
{
	int ret = RET_OK;

	do{

		if (gTopHwE60Info.frcStatus != u32Param)
		{
			BE_NOTI("FRC status. prev: 0x%x, curr: 0x%x\n", gTopHwE60Info.frcStatus, u32Param);
			BE_REG_WR(0xC9030300, u32Param); //REG_CCO1_VERI_SYS_VERI_0_T
			gTopHwE60Info.frcStatus = u32Param;
		}

	} while(0);

	return ret;
}

int BE_TOP_HW_E60_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal;

	BE_NOTI("FBDEV status bFbdevInitDone: %d, bOsdVReverseOn : %d, bEStreamerOn : %d\n", pstParams->bFbdevInitDone,
																							pstParams->bOsdVReverseOn,
																							pstParams->bEStreamerOn);
	
	do{
		CHECK_NULL(pstParams);
		
		regVal = (pstParams->b4kOSDResolution << 12) | (pstParams->bEStreamerOn << 8) | (pstParams->bOsdVReverseOn << 4) | pstParams->bFbdevInitDone;
		BE_REG_WR(0xC9030308, regVal); //REG_CCO1_VERI->SYS_VERI_2

	} while(0);

	return ret;
}

int BE_TOP_HW_E60_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal;

	do{
		CHECK_NULL(pstParams);

		// REG_CCO1_VERI->SYS_VERI_3
		BE_REG_RD(0xC903030C, regVal);
		
		pstParams->bFwOsdOrbitInitDone = regVal & 0x1;
		pstParams->bFwOsdSrInitDone = (regVal >> 4) & 0x1;
		
	} while(0);

	return ret;
}

/** BE/TOP E60 proc handler */
int BE_TOP_HW_E60_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	switch(proc_id)
	{
		case BE_TOP_PROC_ID_DETAIL_INFO:
		{

		}
		break;
		case BE_TOP_PROC_ID_ORBIT_INFO:
		{
			seq_printf(m, "vbe_orbit_on=%d\n", gTopHwE60Info.orbitInfo.bOnOff);
			seq_printf(m, "vbe_orbit_set_mode=%d\n", gTopHwE60Info.orbitInfo.bStoreMode ? 2 : gTopHwE60Info.orbitInfo.bAutoMode);
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
				if (gTopHwE60Info.lsrSize > 0)
				{
					pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
					CHECK_NULL(pFwMem);
					CHECK_NULL(pFwMem->fw_base);

					if ((gTopHwE60Info.lsrSize + BE_TOP_HW_E60_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(gTopHwE60Info.lsrSize);

					pBuffer = (char *)vmalloc(gTopHwE60Info.lsrSize);
				 	CHECK_NULL(pBuffer);

					pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
					CHECK_NULL(pAddr);

					memcpy(pBuffer, (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_E60_LSR_TABLE_OFFSET), gTopHwE60Info.lsrSize);

					rmb();

					vunmap_phys(pAddr);

					for(i=0; i < (gTopHwE60Info.lsrSize/sizeof(UINT32)); i++)
					{
						seq_printf(m, "0x%x", ((UINT32 *)pBuffer)[i]);

						if (i+1 < (gTopHwE60Info.lsrSize/sizeof(UINT32)))
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
				if (gTopHwE60Info.gsrSize > 0)
				{
					pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
					CHECK_NULL(pFwMem);
					CHECK_NULL(pFwMem->fw_base);

					if ((gTopHwE60Info.gsrSize + BE_TOP_HW_E60_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(gTopHwE60Info.gsrSize);

					pBuffer = (char *)vmalloc(gTopHwE60Info.gsrSize);
				 	CHECK_NULL(pBuffer);

					pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
					CHECK_NULL(pAddr);

					memcpy(pBuffer, (char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_E60_GSR_TABLE_OFFSET), gTopHwE60Info.gsrSize);

					rmb();

					vunmap_phys(pAddr);

					for(i=0; i < (gTopHwE60Info.gsrSize/sizeof(UINT32)); i++)
					{
						seq_printf(m, "0x%x", ((UINT32 *)pBuffer)[i]);

						if (i+1 < (gTopHwE60Info.gsrSize/sizeof(UINT32)))
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
			seq_printf(m, "vbe_osd_alpha_val=%d\n", gTopHwE60Info.osdLvl);
		}
		break;
		case BE_TOP_PROC_ID_CPC_INFO:
		{
			seq_printf(m, "vbe_cpc=%d\n", gTopHwE60Info.cpc);
		}
		break;

		default: break;
	}

	return ret;
}

/** @} */
