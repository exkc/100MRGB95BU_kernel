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
 *  date		2017.06.07
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
#include "../fwi/ipc_def_o18.h"
#include "ipc_drv.h"
#include "be_top_hw_o18.h"

// For Video InputLag Test
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>

#include "../gpio/gpio_drv.h"
#include "../gpio/gpio_core.h"


// For CTOP/DPE register access
#include "../../../core/sys/sys_regs.h"
#include "../reg/be_reg_dpe_o18.h"

#include "ipc_cmd_header.h"

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
#define BE_TOP_HW_O18_LSR_TABLE_OFFSET 0x800
#define BE_TOP_HW_O18_GSR_TABLE_OFFSET (BE_TOP_HW_O18_LSR_TABLE_OFFSET + 0x800)

#define BE_TOP_HW_O18_TEST_INPUT_LAG
#ifdef BE_TOP_HW_O18_TEST_INPUT_LAG
#define	BE_TOP_HW_O18_IPP_PIXEL_CTRL_BASE		(0xC9014448)
#define	BE_TOP_HW_O18_IPP_PIXEL_ACTIVE_RIGING	(0xC901405C)

#define BE_TOP_HW_O18_PATTERN_OFF		(0)
#define BE_TOP_HW_O18_PATTERN_ON		(1)
#define BE_TOP_HW_O18_PATTERN_BLACK		(0)
#define BE_TOP_HW_O18_PATTERN_WHITE		(1)

#define BE_TOP_HW_O18_PIN_MUX_PORT		(119)
#define BE_TOP_HW_O18_PIN_NORMAL		(0)
#define BE_TOP_HW_O18_PIN_GPIO			(1)
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

} BE_TOP_HW_O18_INFO_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef BE_TOP_HW_O18_TEST_INPUT_LAG
extern BE_MEM_CFG_T *gpBeMem;
extern DPE_LED_REG_O18_T gDPE_LED_O18;
#endif
extern DPE_OLED_REG_O18_T gDPE_OLED_O18;

extern struct gpio_desc *gpiod_de;
extern struct device de_gpio_dev;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 gInputLagCnt = 0; 
volatile UINT32	*gIPP_PIXEL_CTRL = NULL;
volatile UINT32	*gIPP_PIXEL_CTRL_ACTIVE_RIGING = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef BE_TOP_HW_O18_TEST_INPUT_LAG
static int BE_TOP_HW_O18_InitLagPattern(void);
int BE_TOP_HW_O18_InputLagHandler(void);
static int BE_TOP_HW_O18_SetPattern(UINT32 bOnOff);
static int BE_TOP_HW_O18_SetGpioValue(UINT32 value);
static int BE_TOP_HW_O18_SetGpioMux(UINT32 value);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 g_be_top_hw_O18_pattern_init = 0;
static LX_BE_INPUT_LAG_PATTERN_T gCurPatternParam;
static LX_BE_INPUT_LAG_PATTERN_T gPrePatternParam;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_TOP_HW_O18_Initialize(void)
{
	int ret = RET_OK;

	do {

	} while(0);

	return ret;
}

int BE_TOP_HW_O18_Close(void)
{
	int ret = RET_OK;

	do {

	} while(0);

	return ret;
}

int BE_TOP_HW_O18_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLOCK_BYPASS_T, stHwParams);

		if (pstParams->bLEDBypass <= 1)
		{
			DPE_LED_O18_RdFL(led_led_detour);
			if (pstParams->bLEDBypass)
			{
				DPE_LED_O18_Wr01(led_led_detour, led_detour, 0x1);
			}
			else
			{
				DPE_LED_O18_Wr01(led_led_detour, led_detour, 0x0);
			}
			DPE_LED_O18_WrFL(led_led_detour);
		}
		
		/* change value LX_BE to BE_IPC */
		stHwParams.uFRCBypass = (pstParams->bFRCBypass > 1) ? 0xFFFFFFFF : pstParams->bFRCBypass;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLOCK_BYPASS), (void*)&stHwParams, sizeof(BE_IPC_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_O18_SetOrbit(LX_BE_ORBIT_T *pstParams)
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

#ifdef BE_TOP_HW_O18_TEST_INPUT_LAG
static int BE_TOP_HW_O18_InitLagPattern(void)
{
	gIPP_PIXEL_CTRL = (volatile UINT32 *)ioremap(BE_TOP_HW_O18_IPP_PIXEL_CTRL_BASE, sizeof(UINT32));
	gIPP_PIXEL_CTRL_ACTIVE_RIGING = (volatile UINT32 *)ioremap(BE_TOP_HW_O18_IPP_PIXEL_ACTIVE_RIGING, sizeof(UINT32));

	/* move to below line to init(to get gpiod_de only one time */
	gpiod_de = gpiod_get(&de_gpio_dev, "119", GPIOD_OUT_HIGH);

	gPrePatternParam.enable = BE_TOP_HW_O18_PATTERN_OFF;
	gPrePatternParam.type = 0xff;
	gPrePatternParam.hoffset = 0;
	gPrePatternParam.voffset = 0;
	gPrePatternParam.hsize = 0;
	gPrePatternParam.vsize = 0;

	return RET_OK;
}

int BE_TOP_HW_O18_SetLagParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams)
{
	int ret = RET_OK;
	UINT32 cur_enable,pre_enable;

	if (pstParams == NULL)
	{
		BE_ERROR("pstParams is NULL");
		return RET_ERROR;
	}

	BE_NOTI("init:%d, bOnOff[%d] bPatternType[%d] rect[%d/%d/%d/%d]\n",\
		g_be_top_hw_O18_pattern_init,pstParams->enable,pstParams->type,\
		pstParams->hoffset,pstParams->voffset,pstParams->hsize,pstParams->vsize);

	if (!g_be_top_hw_O18_pattern_init)
	{
		BE_TOP_HW_O18_InitLagPattern();
		g_be_top_hw_O18_pattern_init = 1;
	}

	gCurPatternParam = *pstParams;
	cur_enable = gCurPatternParam.enable;
	pre_enable = gPrePatternParam.enable;

	do {
		if (pre_enable == cur_enable)		break;
		if (cur_enable == BE_TOP_HW_O18_PATTERN_ON)
		{
			/* interrupt enable */
			ipc_phys_hal_InitInterrupt(0, TRUE);
			gPrePatternParam.type = 0xff;
			*gIPP_PIXEL_CTRL_ACTIVE_RIGING = 0x84002000;
			/* register handle */
			de_srcsync_register(TRUE, BE_TOP_HW_O18_InputLagHandler, "inputLag_handler");
			BE_NOTI("START\n");
		}
		else
		{
			/* unregister handle */
			*gIPP_PIXEL_CTRL = 0x00008080;
			*gIPP_PIXEL_CTRL_ACTIVE_RIGING = 0x00000000;
			de_srcsync_register(FALSE, BE_TOP_HW_O18_InputLagHandler, "inputLag_handler");
			/* interrupt disable */
			ipc_phys_hal_InitInterrupt(0, FALSE);
			BE_NOTI("END\n");
		}
		gPrePatternParam.enable = gCurPatternParam.enable;
	} while(0);

	return ret;
}

int BE_TOP_HW_O18_InputLagHandler(void)
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

	if (cur_enable != BE_TOP_HW_O18_PATTERN_ON)
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

		if (cur_type == BE_TOP_HW_O18_PATTERN_WHITE) //white pattern
		{
			BE_TOP_HW_O18_SetPattern(BE_TOP_HW_O18_PATTERN_WHITE); //White
		}
		else	//black pattern
		{
			BE_TOP_HW_O18_SetPattern(BE_TOP_HW_O18_PATTERN_BLACK); //Black
		}

		gPrePatternParam.type = gCurPatternParam.type;
		gpio_cnt = 5;
		BE_NOTI("type changed:%d <- %d, gpio:%d, tick diff:%llu (%llu <- %llu)",\
			cur_type,pre_type,gpio_value,tick_diff,curr_msec_tick,prev_msec_tick);
	} while(0);

	if (gpio_cnt == 4)
	{
		gpiod_set_raw_value(gpiod_de, (cur_type == BE_TOP_HW_O18_PATTERN_WHITE)? 1:0);
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

static int BE_TOP_HW_O18_SetPattern(UINT32 bOnOff)
{
	if (bOnOff == BE_TOP_HW_O18_PATTERN_WHITE)
	{
		*gIPP_PIXEL_CTRL = 0x80FF8080;
	}
	else if (bOnOff == BE_TOP_HW_O18_PATTERN_BLACK)
	{
		*gIPP_PIXEL_CTRL = 0x80008080;
	}
	return 0;
}
#if 0 // not used
static int BE_TOP_HW_O18_SetGpioValue(UINT32 value)
{	
//	GPIO_DevSetValue(BE_TOP_HW_O18_PIN_MUX_PORT, value);

	return 0;
}

static int BE_TOP_HW_O18_SetGpioMux(UINT32 value)
{
//	GPIO_DevSetPinMux(BE_TOP_HW_O18_PIN_MUX_PORT, value);
//	GPIO_DevSetMode(TEST_GPIO_CONTROL, LX_GPIO_MODE_OUTPUT);
	
	return 0;
}
#endif
#endif

int BE_TOP_HW_O18_SetLSRParam(LX_BE_LSR_T *pstParams)
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

		// O18 TEMP
		if (inSizeNum == 0)
		{
			inSizeNum = 35;
			lsrTblVer = 0x1;
		}

		inSize = inSizeNum * sizeof(pstParams->lsrTbl.pu32Data[0]);
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_O18_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O18_LSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bLSRMode = (pstParams->u32LsrMode) >= 0xFF ? 0xFFFFFFFF : (pstParams->u32LsrMode);
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O18_LSR_TABLE_OFFSET;
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

int BE_TOP_HW_O18_SetGSR(LX_BE_GSR_T *pstParams)
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

		// O18 TEMP
		if (inSizeNum == 0) inSizeNum = 16;

		inSize = inSizeNum * sizeof(pstParams->gsrTbl.pu32Data[0]);
		
		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if ((inSize + BE_TOP_HW_O18_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

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
		memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_O18_GSR_TABLE_OFFSET), pBuffer, inSize);

		wmb();

		vunmap_phys(pAddr);

		/* change value LX_BE to BE_IPC */
		stHwParams.bGSRMode = 1;
		stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_O18_GSR_TABLE_OFFSET;
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

int BE_TOP_HW_O18_GetGSRStatus(BOOLEAN *pbParam)
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

int BE_TOP_HW_O18_SetCPC(UINT32 u32Param)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_CPC_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uCPCParam = u32Param;

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

int BE_TOP_HW_O18_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal;
	UINT32 arrData[16];

	do{
		CHECK_NULL(pstParams);

		if (pstParams->u32SizeNum != 16) BREAK_WRONG(pstParams->u32SizeNum);
		
		BE_REG_RD(0xC9012000, regVal);
		arrData[0] = (regVal >> 24) & 0xFF;
		arrData[1] = (regVal >> 16) & 0xFF;
		arrData[2] = (regVal >> 8) & 0xFF;
		arrData[3] = (regVal) & 0xFF;

		BE_REG_RD(0xC9012004, regVal);
		arrData[4] = (regVal >> 24) & 0xFF;
		arrData[5] = (regVal >> 16) & 0xFF;
		arrData[6] = (regVal >> 8) & 0xFF;
		arrData[7] = (regVal) & 0xFF;

		BE_REG_RD(0xC9012008, regVal);
		arrData[8] = (regVal >> 24) & 0xFF;
		arrData[9] = (regVal >> 16) & 0xFF;
		arrData[10] = (regVal >> 8) & 0xFF;
		arrData[11] = (regVal) & 0xFF;

		BE_REG_RD(0xC901200C, regVal);
		arrData[12] = (regVal >> 24) & 0xFF;
		arrData[13] = (regVal >> 16) & 0xFF;
		arrData[14] = (regVal >> 8) & 0xFF;
		arrData[15] = (regVal) & 0xFF;
		
		ret = copy_to_user((void __user *)pstParams->pu32Data, arrData, sizeof(arrData));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	
	return ret;
}

int BE_TOP_HW_O18_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal = 0x0;
	UINT32 arrData[16];

	do{
		CHECK_NULL(pstParams);

		if ((pstParams->levelTbl.u32SizeNum != 16) // case 16 -> TEMP (remove later)
			&& (pstParams->levelTbl.u32SizeNum != 1)) BREAK_WRONG(pstParams->levelTbl.u32SizeNum);

		if (pstParams->bOnOff)
		{
			ret = copy_from_user(arrData, (void __user *)pstParams->levelTbl.pu32Data, 
									pstParams->levelTbl.u32SizeNum*sizeof(UINT32));
			if(ret) BREAK_WRONG(ret);

			regVal = 0x80000000 | (arrData[0] & 0x7FFFFFFF);
		}

		DPE_OLED_O18_RdFL(oled_fsw_ctrl_01);
		DPE_OLED_O18_Wr(oled_fsw_ctrl_01, regVal);
		DPE_OLED_O18_WrFL(oled_fsw_ctrl_01);
	} while(0);
	
	return ret;
}

int BE_TOP_HW_O18_SetDispMode(LX_BE_DISP_MODE_T *pstParams)
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

int BE_TOP_HW_O18_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams)
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

/** BE/TOP O18 proc handler */
int BE_TOP_HW_O18_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
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
