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
 *	OVI module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
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
#include <linux/seq_file.h>
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/vmalloc.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hal.h"
#include "ovi_hw_m23.h"
#include "ovi_reg_def_m23.h"
#include "ovi_reg_m23.h"

#include "../be/reg/be_reg_dpe_m23.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

#include "ovi_output_format_m23a0.h"

#if 0
#include "be_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_M23_PQE_PM_DEVICE_SUSPEND_PREPARE	0
//fw stall
#define OVI_HW_M23_PQE_PM_DEVICE_SUSPEND			1
//cg on
#define OVI_HW_M23_PQE_PM_DEVICE_SUSPEND_COMPLETED	2
#define OVI_HW_M23_PQE_PM_DEVICE_RESUME_PREPARE		3
//cg off
#define OVI_HW_M23_PQE_PM_DEVICE_RESUME				4
//fw restart
#define OVI_HW_M23_PQE_PM_DEVICE_RESUME_COMPLETED	5

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#if 0
#else
#define OVI_HW_M23_GAMMA_TABLE_SIZENUM 1024
#endif
#if 1
#define OVI_HW_M23_INPUT_OD_SIZENUM (1089) // 33*33
#define OVI_HW_M23_INPUT_OD_INDEX_SIZENUM (31)
#define	OVI_HW_M23_INPUT_OD_TOTAL_SIZE (OVI_HW_M23_INPUT_OD_SIZENUM*3 + OVI_HW_M23_INPUT_OD_INDEX_SIZENUM*2) // *3(r,g,b) + *2(x,y)
#define OVI_HW_M23_INPUT_LOD_SIZENUM (19*19*10)
#define OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM (17)
#define OVI_HW_M23_INPUT_LOD_TOTAL_SIZENUM (OVI_HW_M23_INPUT_LOD_SIZENUM + OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM*2) // *2(x,y)
#define OVI_HW_M23_INPUT_POD2_SIZENUM (1848)
#define OVI_HW_M23_INPUT_TSCIC_CTRL_SIZENUM (43)
#define OVI_HW_M23_INPUT_TSCIC_DATA_SIZE (377612)
#define OVI_HW_M23_INPUT_PCLRC_DATA_SIZE (4352)
#define OVI_HW_M23_INPUT_PCLRC_CTRL_DATA_SIZE (22)
#endif
#define OVI_HW_M23_INPUT_VCOM_PAT_DATA_SIZE (96)
#define OVI_HW_M23_WB_GAIN_STEP1 26	// 0.26% step per w/b gain 1
#define OVI_HW_M23_WB_GAIN_STEP2 38	// 0.38% step per w/b gain 1
#define OVI_HW_M23_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_M23_WB_DEFAULT_GAIN 16384

#define OVI_HW_M23_DEMURA_MEM_OFFSET 0x500000
#define OVI_HW_M23_DEMURA_MEM_SIZE 0x100000
#define OVI_HW_M23_INPUT_DEMURA_CFG_DATA_SIZE (47)
#if 0
#define OVI_HW_F22_REG_DPG_LUT_WDATA 0xF4080A08
#define OVI_HW_F22_REG_DPG_LUT_WR_DONE 0xF4080A04
#define OVI_HW_F22_REG_DPG_EN 0xF4080A00
#define OVI_HW_F22_REG_WB_EN 0xF4080AC0
#define OVI_HW_F22_REG_WB_R_GAIN 0xF4080AC4
#define OVI_HW_F22_REG_WB_G_GAIN 0xF4080AC8
#define OVI_HW_F22_REG_WB_B_GAIN 0xF4080ACC
#define OVI_HW_F22_REG_WB_R_OFFSET 0xF4080AD0
#define OVI_HW_F22_REG_WB_G_OFFSET 0xF4080AD4
#define OVI_HW_F22_REG_WB_B_OFFSET 0xF4080AD8
#endif

#define _B2L32(data) ((((UINT32)(data&0xff000000) >> 24) & 0x000000ff) |   \
					(((UINT32)(data&0x00ff0000) >>  8) & 0x0000ff00) |   \
					(((UINT32)(data&0x0000ff00) <<  8) & 0x00ff0000) |   \
					(((UINT32)(data&0x000000ff) << 24) & 0xff000000))

#define OVI_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define OVI_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\


#define OVI_HW_M23_CH_POWER_REG_MASK	0x00000FFF

#define OVI_HW_M23_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_M23_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_M23_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_M23_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_M23_REG_PARAM_OP_MASK		0x3

#define OVI_HW_M23_REG_SET_A0_START		0x000000A0
#define OVI_HW_M23_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_M23_REG_READ_START		0x00000001
#define OVI_HW_M23_REG_CHECK_END		0x00000000

#define OVI_HW_M23_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_M23_BOE_FW_SIZE 32256

/* GET_RESULT_RF *10 */
#define GET_RESULT_RF(ACCURACY) \
({ \
	UINT32 v = 0; \
	if(ACCURACY == 3) v = 10; \
	if(ACCURACY == 2) v = 10; \
	if(ACCURACY == 1) v = 20; \
	if(ACCURACY == 0 || ACCURACY >= 4) v = 40; \
	v; \
})

/* SPREAD_RATIO_OUT * 1000 */
#define SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF) \
		( (UPDN_MAX)*1000 * 50 * RESULT_RF / (60*((4*NPC)+NSC)) )

#define MOD_FREQ_OUT(FIN, M, MOD_FREQ, UPDN_MAX) \
		( (FIN/M) * 1000000 / ((MOD_FREQ+1)*((4*UPDN_MAX)+2)) )

#define FIN_DISP		(54) //DISP FIN
#define GETBIT_M(reg,bit) ((reg >> (bit)) & 1)
#define SETBIT_M(reg,bit) ((reg)|=((0x1)<<(bit)))
#define CLRBIT_M(reg,bit) ((reg)&=~((0x1)<<(bit)))

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct{
	UINT8 pemp[12];
	UINT8 itune[12];
} OVI_HW_M23_PEMP_ITUNE_DATA_T;

typedef struct {
	struct delayed_work dlyWork;
	UINT32 *pu32LutR;
	UINT32 *pu32LutG;
	UINT32 *pu32LutB;
} OVI_HW_M23_DLY_RGB_GAMMA_T;

typedef struct {
	UINT32 chPowerOnRegValue1;
	UINT32 chPowerOnRegValue2;
	UINT32 tconBaseAddress;

	UINT32 spreadSpectrumRegValue1;
	UINT32 spreadSpectrumRegValue2;

	BOOLEAN wbEn;
	BOOLEAN wbBypassEn;
	BOOLEAN dgaEn;
	BOOLEAN dgaBypassEn;
	BOOLEAN mleModeOff;
	BOOLEAN odcBypassEn;
	
	UINT32 odcBypassRegFieldValue;
	UINT32 lodcBypassRegFieldValue;

	UINT32 horReverseRegFieldValue;	// Value for non-reverse

	LX_OVI_DISP_OUTPUT_MODE_T dispOutputMode;
	BOOLEAN isDispOutDisabled;

	UINT32 pllMuxSelRegValue;

	UINT32 tconClkGatingRegValue;

	LX_OVI_DISPLAY_INFO_T dispOption; // use only for display resume
	LX_OVI_HW_DISPLAY_INFO_T hwDispOption;

	BOOLEAN mute;
	UINT32 mirrorV;
	UINT32 mirrorH;

	struct task_struct* tscicThread;
	BOOLEAN tscicWritingFlag;
	UINT32 tscicSize;
	UINT32 *tscicU32Tbl;
	UINT32 tscicCtrlSizeNum;
	UINT8 *tscicU8CtrlData;
	OVI_HW_M23_PEMP_ITUNE_DATA_T pempItuneData;
	UINT8 dcVal[24];
	UINT32 patType;
	UINT32 rGamma[1024];
	UINT32 gGamma[1024];
	UINT32 bGamma[1024];
	UINT8 pclrcData[OVI_HW_M23_INPUT_PCLRC_DATA_SIZE];

	struct task_struct* demuraThread;
	BOOLEAN demuraWritingFlag;
	UINT32 demuraSize;
	UINT8 *demuraU8Tbl;
	UINT32 demuraConfigSize;
	UINT8 *demuraU8ConfigData;

	BOOLEAN useSpecialDgaFlag;
	UINT32 converterCheckVal;

#if 0
	void *pVx1ChipInfoVMapAddr;
	BE_OVI_HW_M23_VX1_CHIP_INFO_T *pVx1ChipInfo[BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM];
#endif

	OVI_HW_M23_DLY_RGB_GAMMA_T delayedRGBGamma;

	UINT32 pm_status;
	UINT32 pm_suspend;
} OVI_HW_M23_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_M23_OUTPUT_MODES_T;

#if 0
/*-----------------------------------------------------------------------------------------
    0xC930_E400    disp_aiopll0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    rsv0                      :  1,    //      0 reserved
    reg_aiopll_fine_div       :  1,    //      1
    reg_aiopll_dss            :  1,    //      2
    reg_aiopll_accuracy       :  2,    //   4: 3
    reg_aiopll_updn_max       :  7,    //  11: 5
    reg_aiopll_mod_freq_max   :  9,    //  20:12
    reg_aiopll_m              :  6,    //  26:21
    rsv1                      :  1,    //     27 reserved
    reg_aiopll_cih            :  4;    //  31:28
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E404    disp_aiopll1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_lock           :  1,    //      0
    rsv0                      :  3,    //   3: 1 reserved
    reg_aiopll_offset_mode    :  1,    //      4
    reg_aiopll_fout3_post_od  :  3,    //   7: 5
    reg_aiopll_fout2_post_od  :  3,    //  10: 8
    reg_aiopll_fout_od        :  2,    //  12:11
    reg_aiopll_fout3_pre_od   :  3,    //  15:13
    reg_aiopll_fout2_pre_od   :  3,    //  18:16
    reg_aiopll_nsc            :  4,    //  22:19
    reg_aiopll_npc            :  6,    //  28:23
    reg_aiopll_fine_control   :  3;    //  31:29
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E408    disp_aiopll2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_freq_update    :  1,    //      0
    rsv0                      :  3,    //   3: 1 reserved
    reg_aiopll_sync_on        :  1,    //      4
    rsv1                      :  3,    //   7: 5 reserved
    reg_aiopll_in_sel         :  1,    //      8
    rsv2                      :  3,    //  11: 9 reserved
    reg_aiopll_pdb            :  1,    //     12
    rsv3                      :  9,    //  21:13 reserved
    reg_aiopll_wake_bypass    :  1,    //     22
    reg_aiopll_ddr_mode       :  1,    //     23
    reg_aiopll_offset         :  8;    //  31:24
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_M23A0_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;
extern DPE_LED_REG_M23_T gDPE_LED_M23;
#if 0
extern BE_FRM_MEM_CFG_T *gpBeChInfMem;
#endif

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_M23_T gOVI_TCON_M23;
#if 0
OVI_TCON_LODC_REG_M23_T gOVI_TCON_LODC_M23;
OVI_TCON_CAD_REG_M23_T gOVI_TCON_CAD_M23;
OVI_OIF_REG_M23_T gOVI_OIF_M23;
#endif


static volatile unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_M23Ax[] =
{
	{"Disp-M23 4k60Hz Vx1\n",  ovi_m23a0_disp_4k60_vx1_8lane, sizeof(ovi_m23a0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M23 4k120Hz Vx1\n",  ovi_m23a0_disp_4k120_vx1_16lane, sizeof(ovi_m23a0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M23 4k120Hz Vx1 5Byte\n",  ovi_m23a0_disp_4k120_vx1_16lane_5byte, sizeof(ovi_m23a0_disp_4k120_vx1_16lane_5byte)/sizeof(LX_OVI_REG_T)},
	{"Disp-M23 4k120Hz Vx1 24LANE 5Byte\n",  ovi_m23a0_disp_4k120_vx1_24lane_5byte, sizeof(ovi_m23a0_disp_4k120_vx1_24lane_5byte)/sizeof(LX_OVI_REG_T)}
};

OVI_HW_M23_OUTPUT_MODES_T _gOVIOutputModes_M23 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

#if 0
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_M23A0_T *gOVI_HW_M23_SS_CTRL1 = NULL;
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_M23A0_T *gOVI_HW_M23_SS_CTRL2 = NULL;
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_M23A0_T *gOVI_HW_M23_SS_CTRL3 = NULL;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_M23_GetGain(UINT32 gain);
static SINT16 _OVI_M23_GetOffset(UINT32 offset);
static void _OVI_M23_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
__attribute__((unused)) static void _OVI_M23_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
__attribute__((unused)) static void _OVI_M23_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

static void _OVI_M23_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams, BOOLEAN useHWopt);
static void _OVI_M23_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_M23_DispSetC4TX(void);
static void _OVI_M23_DispOutputEnable(BOOLEAN bParam);
static void _OVI_M23_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
static void _OVI_M23_DispSpreadSpectrumInit(void);

static void _OVI_M23_CallbackDelayedGamma(struct work_struct *work);
static void _OVI_M23_InitDGA(void);

#if 0
static int _OVI_M23_Vx1ChipInfoMemInit(void);
static void _OVI_M23_Vx1ChipInfoMemFill(void);
static void _OVI_M23_UpdateChipInfoHeader(void);
#endif

static int _OVI_M23_GetPempItuneData(OVI_HW_M23_PEMP_ITUNE_DATA_T *pstParams);
static int _OVI_M23_SetPempItuneData(OVI_HW_M23_PEMP_ITUNE_DATA_T *pstParams);
static void _OVI_M23_Set_DC_Cal(UINT8 *data);
static void _OVI_M23_Get_DC_Cal(UINT8 *data);
static void _OVI_M23_Draw_Pat(int num);

static void _ConvertEndian32(UINT32 *data,UINT32 size);

static int _OVI_HW_M23_GetCfgs(void);
/*----------------------------------------------------------------------------------------
	Internal Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int OVI_M23_TscicWriteThread(void* data);
int OVI_M23_DemuraWriteThread(void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_M23_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_M23_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_M23_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static LX_OVI_TCON_COLOR_TEMP_T _gColTemp;

static OVI_HW_M23_INFO_T _gOviHwM23Info;

static UINT32 m23a0_pclrc_ctrl_table[OVI_HW_M23_INPUT_PCLRC_CTRL_DATA_SIZE] =
{
	0x00,
	0x01,
	0x05,
	0x12,
	0x07,
	0x11,
	0x06,
	0x13,
	0x09,
	0x12,
	0x0B,
	0x11,
	0x0A,
	0x13,
	0x14,
	0x15,
	0x15,
	0x15,
	0x15,
	0x15,
	0x15,
	0x11
};

static uint _g_ovi_hw_m23_ptype = 0x0;//see LX_OVI_PANEL_INTERFACE_T
module_param_named(ovi_m23_ptype, _g_ovi_hw_m23_ptype, uint, 0644);

struct ovi_hw_m23_pmaker_entry {
	char *name;
	UINT16 idx;
};

#define OVI_HW_M23_PMAKER_NONE  0
#define OVI_HW_M23_PMAKER_F     1
#define OVI_HW_M23_PMAKER_G     2
#define OVI_HW_M23_PMAKER_S     3
#define OVI_HW_M23_PMAKER_U     4
#define OVI_HW_M23_PMAKER_M     5
#define OVI_HW_M23_PMAKER_N     6
#define OVI_HW_M23_PMAKER_C     7
#define OVI_HW_M23_PMAKER_J     8
#define OVI_HW_M23_PMAKER_X     9
static struct ovi_hw_m23_pmaker_entry _g_ovi_hw_m23_pmaker_entry[] = {
	{.name="F",   .idx=OVI_HW_M23_PMAKER_F},
	{.name="G",   .idx=OVI_HW_M23_PMAKER_G},
	{.name="S",   .idx=OVI_HW_M23_PMAKER_S},
	{.name="U",   .idx=OVI_HW_M23_PMAKER_U},
	{.name="M",   .idx=OVI_HW_M23_PMAKER_M},
	{.name="N",   .idx=OVI_HW_M23_PMAKER_N},
	{.name="C",   .idx=OVI_HW_M23_PMAKER_C},
	{.name="J",   .idx=OVI_HW_M23_PMAKER_J},
	{.name="X",   .idx=OVI_HW_M23_PMAKER_X},
	{.name=NULL}
};

static uint _g_ovi_hw_m23_pmaker = 0x0;//see _g_ovi_hw_m23_pmaker_entry
module_param_named(ovi_m23_pmaker, _g_ovi_hw_m23_pmaker, uint, 0644);

static uint _g_ovi_hw_m23_pinch = 0x0;
module_param_named(ovi_m23_pinch, _g_ovi_hw_m23_pinch, uint, 0644);

static uint _g_ovi_hw_m23_od_en = 0x0;
module_param_named(ovi_m23_od_en, _g_ovi_hw_m23_od_en, uint, 0644);

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _OVI_M23_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_M23_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(M23, B0))
		{
			if (regParamVal != OVI_HW_M23_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_M23_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_M23_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

__attribute__((unused)) static void _OVI_M23_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_M23_REG_PARAM_OP_MASK)
		{
			case OVI_HW_M23_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_M23_REG_PARAM_OP_CHECK:	// check
				_OVI_M23_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_M23_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_M23_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_M23_REG_PARAM_OP_WRITE
				if (!ignore)
				{
					OVI_REG_WR((param->addr + addrOffset), param->value);
				}
				OVI_DEBUG("REG_WRITE( 0x%08x, 0x%08x);\n", (param->addr + addrOffset), param->value);
				break;
		}
		
		param++;
	}
}

__attribute__((unused)) static void _OVI_M23_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_M23_REG_PARAM_OP_MASK)
		{
			case OVI_HW_M23_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_M23_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_M23_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_M23_REG_PARAM_OP_WRITE
				if (readReg)
				{
					OVI_REG_RD((param->addr + addrOffset), param->value);
					if ( (param->addr + addrOffset) == 0xcc470004) // clear demura,od,wb for instant boot
					{
						param->value = param->value & (~0x103);
					}
				}
				OVI_DEBUG("REG_READ( 0x%08x, 0x%08x);\n", (param->addr + addrOffset), param->value);
				break;
		}
		
		param++;
	}
}
static void _ConvertEndian32(UINT32 *data,UINT32 size)
{
	int i = 0;
	UINT32 sizeNum = size/4;

	for (i = 0; i < sizeNum; i++)
	{
		data[i] = _B2L32(data[i]);
	}
}

static void _OVI_M23_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams, BOOLEAN useHWopt)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	//OVI_REG_RD(0xCC922018, _gOviHwM23Info.pllMuxSelRegValue);

	if (useHWopt == TRUE)
	{
		if (_gOviHwM23Info.hwDispOption.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
		{
			stDispParams.panelInterface = LX_OVI_PANEL_VX1;
		}
		else
		{
			stDispParams.panelInterface = _gOviHwM23Info.hwDispOption.panelInterface;
		}
		stDispParams.panelFramerate = _gOviHwM23Info.hwDispOption.dispFramerate;
	}
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
#if 0
					_OVI_M23_RegParamRead(ovi_m23a0_disp_2k60_lvds_12lane,
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_2k60_lvds_12lane), 0);
#endif
					break;
				case LX_OVI_PANEL_EPI:
					_OVI_M23_RegParamRead(ovi_m23a0_disp_4k60_epi_tcon,
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_epi_tcon), 0);
					break;
				case LX_OVI_PANEL_CEDS:
					_OVI_M23_RegParamRead(ovi_m23a0_disp_4k60_ceds_tcon,
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_ceds_tcon), 0);
					break;
				case LX_OVI_PANEL_VX1:
				default :
					_OVI_M23_RegParamRead(ovi_m23a0_disp_4k60_vx1_8lane,
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_vx1_8lane), 0);
					//_gOviHwM23Info.chPowerOnRegValue1 = 0x00000FF0;
					break;
			}
			break;
#if 0
		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					#if 0 // block for bringup
					_OVI_M23_RegParamRead(ovi_m23a0_disp_2k120_lvds_4link, 
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_2k120_lvds_4link), 0);
					#endif
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
					{
						_OVI_M23_RegParamRead(ovi_m23a0_disp_4k120_vx1_24lane_5byte, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k120_vx1_24lane_5byte), 0);
						//_gOviHwM23Info.chPowerOnRegValue1 = 0x00FFFFFF;
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_M23_RegParamRead(ovi_m23a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k120_vx1_16lane_5byte), 0);
						//_gOviHwM23Info.chPowerOnRegValue1 = 0x000FFFF0;
					}	
					else
					{
						_OVI_M23_RegParamRead(ovi_m23a0_disp_4k120_vx1_16lane, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k120_vx1_16lane), 0);
						//_gOviHwM23Info.chPowerOnRegValue1 = 0x000FFFF0;
					}
					break;
			}
			break;
#endif

		default :
			_OVI_M23_RegParamRead(ovi_m23a0_disp_4k60_vx1_8lane, 
									OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_vx1_8lane), 0);
			break;
	}
	
	return;
}

static void _OVI_M23_DispSetC4TX(void)
{
	if ((_gOviHwM23Info.chPowerOnRegValue1 & OVI_HW_M23_CH_POWER_REG_MASK) == 0xFFF) // 12 lane
	{
		_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_c4tx_12lane,
			OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_c4tx_12lane), 0);
	}
	else if ((_gOviHwM23Info.chPowerOnRegValue1 & OVI_HW_M23_CH_POWER_REG_MASK) == 0x3FC) // 8 lane
	{
		_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_c4tx_8lane,
			OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_c4tx_8lane), 0);
	}
	else if ((_gOviHwM23Info.chPowerOnRegValue1 & OVI_HW_M23_CH_POWER_REG_MASK) == 0x1F8) // 6 lane
	{
		_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_c4tx_6lane,
			OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_c4tx_6lane), 0);
	}
	else // default 12 lane
	{
		_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_c4tx_12lane,
			OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_c4tx_12lane), 0);
	}

	return;
}

static void _OVI_M23_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	__attribute__((unused)) char hw_opt[32];

	OVI_PRINT("\n[_OVI_M23_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	// Display Spread Spectrum
	_OVI_M23_DispSpreadSpectrumInit();

	// Display PLL MUX setting for DCO FCW control
	OVI_REG_RD(0xCC922018, _gOviHwM23Info.pllMuxSelRegValue);
	_gOviHwM23Info.pllMuxSelRegValue = (_gOviHwM23Info.pllMuxSelRegValue & 0xFFFFFFCC) | (1 << 4) | (1);
	OVI_REG_WR(0xCC922018, _gOviHwM23Info.pllMuxSelRegValue);

	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			if (stDispParams.panelResolution == LX_OVI_PANEL_RESOLUTION_1366X768)
			{
				// do not set sync in hd
			}
			else
			{
				_OVI_M23_RegParamSet(pqe_sync_4k60_blend,
									OVI_HW_M23_ARRAY_SIZE(pqe_sync_4k60_blend), 0); // set sync for lod error
			}
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					if (stDispParams.panelResolution == LX_OVI_PANEL_RESOLUTION_1366X768)
					{
						if (_gOviHwM23Info.converterCheckVal == 0x34)
						{
							_OVI_M23_RegParamSet(ovi_m23a0_disp_hd60_lvds_converter,
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_hd60_lvds_converter), 0);
						}
						else
						{
							_OVI_M23_RegParamSet(ovi_m23a0_disp_hd60_lvds,
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_hd60_lvds), 0);
						}
					}
					else
					{
						_OVI_M23_RegParamSet(ovi_m23a0_disp_2k60_lvds_12lane,
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_2k60_lvds_12lane), 0);
					}
					break;
				case LX_OVI_PANEL_EPI:
					_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_epi_tcon,
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_epi_tcon), 0);
					_OVI_M23_DispSetC4TX();
					break;
				case LX_OVI_PANEL_CEDS:
					_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_ceds_tcon,
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_ceds_tcon), 0);
					_OVI_M23_DispSetC4TX();
					break;
				case LX_OVI_PANEL_VX1:
				default :
					_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_vx1_8lane,
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_vx1_8lane), 0);
					break;
			}
			break;

#if 0
		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					#if 0 // block for bringup
					_OVI_M23_RegParamSet(ovi_m23a0_disp_2k120_lvds_4link, 
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_2k120_lvds_4link), 0);
					#endif
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
					{
						_OVI_M23_RegParamSet(ovi_m23a0_disp_4k120_vx1_24lane_5byte, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k120_vx1_24lane_5byte), 0);
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_M23_RegParamSet(ovi_m23a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k120_vx1_16lane_5byte), 0);
					}	
					else
					{
						_OVI_M23_RegParamSet(ovi_m23a0_disp_4k120_vx1_16lane, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k120_vx1_16lane), 0);
					}
					break;
			}
			break;
#endif

		default :
			_OVI_M23_RegParamSet(ovi_m23a0_disp_4k60_vx1_8lane, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_4k60_vx1_8lane), 0);
			break;
	}

	#if 0 // not support
	_OVI_M23_RegParamSet(ovi_m23a0_disp_preEmp_swiLvl, 
												OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_preEmp_swiLvl), 0);
	#endif

	/*
	if (RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
	{
		if (!strncmp(hw_opt,"oled",4)) // LCD H/W option -> forced OLED option
		{
			// PWM forced high
			OVI_REG_WR(0xCC460110, 0x1);
			OVI_REG_WR(0xCC46011C, 0x1);
			OVI_REG_WR(0xCC460118, 0x40000000);
			OVI_REG_WR(0xCC460124, 0x40000000);
		}
	}*/ //not support
	
	return;
}

static void _OVI_M23_DispOutputEnable(BOOLEAN bParam)
{

	if (_gOviHwM23Info.dispOption.panelInterface == LX_OVI_PANEL_EPI
		|| _gOviHwM23Info.dispOption.panelInterface == LX_OVI_PANEL_CEDS)
	{
		if(bParam)
		{
			OVI_TCON_M23_RdFL(tcon_gclk_control);
			OVI_TCON_M23_RdFL(tcon_mclk_control);
			OVI_TCON_M23_RdFL(tcon_gst_control);
			OVI_TCON_M23_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_M23_Wr01(tcon_mclk_control, mclk_en, 0x1);
			OVI_TCON_M23_Wr01(tcon_gst_control, gst_en, 0x1);
			OVI_TCON_M23_WrFL(tcon_gclk_control);
			OVI_TCON_M23_WrFL(tcon_mclk_control);
			OVI_TCON_M23_WrFL(tcon_gst_control);

			OVI_REG_WR(0xcc48000c, 0x00000000); // vst reset=0
			OS_MsecSleep(25);
		}
		else
		{
//			OVI_REG_WR(0xcc470320, 0x0); // vst off
			OVI_TCON_M23_RdFL(tcon_gst_control);
			OVI_TCON_M23_Wr01(tcon_gst_control, gst_en, 0x0);
			OVI_TCON_M23_WrFL(tcon_gst_control);
			OS_UsecDelay(26);
			OVI_TCON_M23_RdFL(tcon_gclk_control);
			OVI_TCON_M23_Wr01(tcon_gclk_control, gclk_en, 0x0); // ON_CLK
			OVI_TCON_M23_WrFL(tcon_gclk_control);
			OS_UsecDelay(26);
			OVI_TCON_M23_RdFL(tcon_mclk_control);
			OVI_TCON_M23_Wr01(tcon_mclk_control, mclk_en, 0x0); // OFF_CLK
			OVI_TCON_M23_WrFL(tcon_mclk_control);
			OS_UsecDelay(20);
		}
	}

#if 1
	CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_08);
	CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_00);
	if(bParam)// display output on
	{
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_08, _gOviHwM23Info.chPowerOnRegValue1);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_00, _gOviHwM23Info.chPowerOnRegValue2);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_08);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_00);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");

		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_02, 0x00000030);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_02);

			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_02, 0x00000020);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_02);
		}
	}
	else // display output off
	{
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_08, _gOviHwM23Info.chPowerOnRegValue1 & (~OVI_HW_M23_CH_POWER_REG_MASK));
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_00, _gOviHwM23Info.chPowerOnRegValue2 & (~0x1));
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_08);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_00);
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}

	_gOviHwM23Info.isDispOutDisabled = bParam ? FALSE : TRUE;
#endif
	return;
}

/* Notice!! : 
Cannot use block register macro(ex. CTOP_CTRL_..., OVI_TCON_...) - because of the function call timing */
static void _OVI_M23_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	__attribute__((unused)) char hw_opt[32];
	LX_OVI_HW_DISPLAY_INFO_T dispOpt;

	dispOpt.panelInterface = LX_OVI_PANEL_VX1;
	dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_3840X2160;
	dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_3840X2160;
	dispOpt.frcChipType = LX_OVI_FRC_CHIP_INTERNAL;
	dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_EDGE_LED;
	dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	dispOpt.isVx15Byte = FALSE;
	dispOpt.isDispForceFreerun = FALSE;

	if(RET_OK==OS_ScanKernelCmdline("hwopt=%s", hw_opt))
	{
		/*if (hw_opt[1] == '1') // PMIC type
		{
			dispOpt.isVx15Byte = TRUE;
		}*/

		if (hw_opt[2] == '0') // EPI
		{
			dispOpt.panelInterface = LX_OVI_PANEL_EPI;
		}
		else if (hw_opt[2] == '1') // LVDS
		{
			dispOpt.panelInterface = LX_OVI_PANEL_LVDS;
		}
		else if (hw_opt[2] == '3') // CEDS
		{
			dispOpt.panelInterface = LX_OVI_PANEL_CEDS;
		}
		else if (hw_opt[2] == '4') // EPI_QSAC
		{
			dispOpt.panelInterface = LX_OVI_PANEL_EPI_QSAC;
		}

		if (hw_opt[3] == '0') // HD resolution
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
		}
		else if (hw_opt[3] == '1') // FHD resolution
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
		}
		else if ((hw_opt[3] == '3') || (hw_opt[17] == '9')) // 8k 
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_7680X4320;
		}

		if (hw_opt[4] == '0') // NO FRC(main SoC)
		{
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}

		if (hw_opt[9] == '0') // panel output framerate 60HZ
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}

		if (hw_opt[12] == '1') // OLED
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
		}

		if (hw_opt[17] == '9') // FRC type F22
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F22;
		}
	}
	else
	{
		__attribute__((unused)) UINT32 regVal;

		/*
		pix2_clk Clock Selection
		0 => disp594_d2 (297.0MHz) 4k 60Hz
		1 => disp594_d4 (148.5MHz) 2k 120Hz
		2 => disp594_d8 (74.25MHz) 2k 60Hz
		3 => disp594_d16 (37.125MHz)
		*/
		/* 2k/4k model 0xCC480010[17:16] CRG TCON dpe_syn */ 
		OVI_REG_RD(0xCC480010, regVal);
		regVal = (regVal >> 16) & 0x3;
		if (regVal == 1)
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;

			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
	
		}
		
		//OVI_REG_RD(0xCC490010, regVal); bringup-check
		/*if (regVal & 0x1)
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F22;
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_7680X4320;
		}*/
	}

	if (RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
	{
		if ((!strncmp(hw_opt,"hdmi60",6))
				&& (dispOpt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22))
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ_FIXED; // Ext. FRC freerun + 60Hz fixed frame rate
		}
		else if ((!strncmp(hw_opt,"hdmi5060",8))
				&& (dispOpt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22))
		{
			dispOpt.isDispForceFreerun = TRUE; // Main SoC/Ext. FRC freerun
		}
		else if (!strncmp(hw_opt,"hdmi",4))
		{
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;

			if (!strncmp(hw_opt,"hdmi60",6))
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ_FIXED;
				dispOpt.isDispForceFreerun = TRUE;
			}
			else if (!strncmp(hw_opt,"hdmi5060",8))
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
				dispOpt.isDispForceFreerun = TRUE;
			}
			else
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			}
		}

		if (!strncmp(hw_opt,"4byte",5))
		{
			dispOpt.isVx15Byte = FALSE;
		}
		else if (!strncmp(hw_opt,"5byte",5))
		{
			dispOpt.isVx15Byte = TRUE;
		}
	}

	if(RET_OK==OS_ScanKernelCmdline("dispopts=%s", hw_opt))
	{
		if(strstr(hw_opt,"1920x1080"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
		}
		else if (strstr(hw_opt,"1366x768"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
		}
		else if (strstr(hw_opt,"1280x720"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1280X720;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1280X720;
		}

		if (strstr(hw_opt,"stb"))
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_NONE;
		}
	}

	memcpy((void *)pstParams, (void *)&dispOpt, sizeof(LX_OVI_HW_DISPLAY_INFO_T));
	
	return;
}

static void _OVI_M23_DispSpreadSpectrumInit(void)
{
	#if 0 // bringup-check //need to check when apply ss
	if (_gOviHwM23Info.spreadSpectrumRegValue2 & (1<<23)) // DSS OFF
	{
		OVI_REG_WR(0xCC43205C, _gOviHwM23Info.spreadSpectrumRegValue2);
	}
	else // 0.5%, 30KHz
	{
		OVI_REG_WR(0xC603306C, 0x00000FF7); //Power Down for DISP PLL setting (not for DISP SS setting)

		OVI_REG_WR(0xCC432058, _gOviHwM23Info.spreadSpectrumRegValue1);
		OVI_REG_WR(0xCC43205C, _gOviHwM23Info.spreadSpectrumRegValue2 | (1<<23));
		OVI_REG_WR(0xCC432060, 0x00111042);

		OVI_REG_WR(0xC603306C, 0x00000FFF); //Power On

		OS_UsecDelay(100);

		OVI_REG_WR(0xCC43205C, _gOviHwM23Info.spreadSpectrumRegValue2);
	}
	#endif

	OVI_REG_WR(0xCC922000, (_gOviHwM23Info.spreadSpectrumRegValue1 | 0x4));
	OVI_REG_WR(0xCC922004, _gOviHwM23Info.spreadSpectrumRegValue2);
	OVI_REG_WR(0xCC922008, 0x01000000);
	OVI_REG_WR(0xCC922000, _gOviHwM23Info.spreadSpectrumRegValue1);

	return;
}


static void _OVI_M23_CallbackDelayedGamma(struct work_struct *work)
{
	int i;
	__attribute__((unused)) UINT32 regField;

	if (_gOviHwM23Info.pm_suspend == 1)
	{
		OVI_PRINT("skip (in suspend)(%d)\n",_gOviHwM23Info.pm_status);
		return;
	}

	if ((_gOviHwM23Info.delayedRGBGamma.pu32LutR == NULL)
		|| (_gOviHwM23Info.delayedRGBGamma.pu32LutG == NULL)
		|| (_gOviHwM23Info.delayedRGBGamma.pu32LutB == NULL)) return;

	OVI_DEBUG("\n\nRetry Gamma setting!\n\n\r");

	DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
	DPE_LED_M23_Rd01(led_dpg_lut_wr_done, dpg_lut_cpy_status, regField);

	if (regField)
	{
		schedule_delayed_work(&_gOviHwM23Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
	}
	else
	{
		DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
		DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_wstart_o, 0x1);
		DPE_LED_M23_WrFL(led_dpg_lut_wr_done);

		DPE_LED_M23_RdFL(led_dpg_lut_wdata);

		/* Setting Red Gamma Table */
		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwM23Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_M23_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Green Gamma Table */
		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwM23Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_M23_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Blue Gamma Table */
		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwM23Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_M23_WrFL(led_dpg_lut_wdata);
		}

		DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
		DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_wdone_o, 0x1);
		DPE_LED_M23_WrFL(led_dpg_lut_wr_done);

		DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
		DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_lut_update, 0x1);
		DPE_LED_M23_WrFL(led_dpg_lut_wr_done);

		vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutR);
		vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutG);
		vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutB);
		_gOviHwM23Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwM23Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwM23Info.delayedRGBGamma.pu32LutB = NULL;
	}

}

static void _OVI_M23_InitDGA(void)
{
	volatile UINT32 *reg_rstart = NULL;
	volatile UINT32 *reg_gstart = NULL;
	volatile UINT32 *reg_bstart = NULL;
	volatile int i;
	UINT32 prev;

	do {

		reg_rstart = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE+offsetof(OVI_TCON_REG_M23A0_T, tcon_dga_low_rs), 
											OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_rstart == NULL)
		{
			OVI_ERROR("[OVI] Error in reg_rstart ioremap! \n");
			break;
		}

		reg_gstart = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE+offsetof(OVI_TCON_REG_M23A0_T, tcon_dga_low_gs), 
											OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_gstart == NULL)
		{
			OVI_ERROR("[OVI] Error in reg_gstart ioremap! \n");
			break;
		}
		reg_bstart = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE+offsetof(OVI_TCON_REG_M23A0_T, tcon_dga_low_bs), 
											OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_bstart == NULL)
		{
			OVI_ERROR("[OVI] Error in reg_bstart ioremap! \n");
			break;
		}

		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Wr01(tcon_control, dga_en, 0x0);
		OVI_TCON_M23_WrFL(tcon_control);

		prev = 0;
		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			if (_gOviHwM23Info.useSpecialDgaFlag == 0x1)
			{
				if(prev > (ovi_sdga_boe_55[i]<<3) )
				{
					reg_rstart[i] = prev;
				}
				else
				{
					reg_rstart[i] = ovi_sdga_boe_55[i]<<3;
					prev = ovi_sdga_boe_55[i]<<3;
				}
			}
			else
			{
				reg_rstart[i] = i<<3;
			}
		}

		prev = 0;
		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			if (_gOviHwM23Info.useSpecialDgaFlag == 0x1)
			{
				if(prev > (ovi_sdga_boe_55[i]<<3) )
				{
					reg_gstart[i] = prev;
				}
				else
				{
					reg_gstart[i] = ovi_sdga_boe_55[i]<<3;
					prev = ovi_sdga_boe_55[i]<<3;
				}
			}
			else
			{
				reg_gstart[i] = i<<3;
			}
		}

		prev = 0;
		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			if (_gOviHwM23Info.useSpecialDgaFlag == 0x1)
			{
				if(prev > (ovi_sdga_boe_55[i]<<3))
				{
					reg_bstart[i] = prev;
				}
				else
				{
					reg_bstart[i] = ovi_sdga_boe_55[i]<<3;
					prev = ovi_sdga_boe_55[i]<<3;
				}
			}
			else
			{
				reg_bstart[i] = i<<3;
			}
		}

		OVI_REG_RD(0xCC471008,i);
		OVI_REG_RD(0xCC47100C,i);
		OVI_REG_RD(0xCC472008,i);
		OVI_REG_RD(0xCC47200C,i);
		OVI_REG_RD(0xCC473008,i);
		OVI_REG_RD(0xCC47300C,i);

		// gamma table upload
		OVI_TCON_M23_RdFL(tcon_dga_mode);
		OVI_TCON_M23_Wr01(tcon_dga_mode, dga_up_mode, 0x1);	// dga_up_mode : 1 -> force update
		OVI_TCON_M23_WrFL(tcon_dga_mode);
		OVI_TCON_M23_RdFL(tcon_dga_mode);
		OVI_TCON_M23_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
		OVI_TCON_M23_WrFL(tcon_dga_mode);

		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_rstart[i] = i<<3;
		}

		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_gstart[i] = i<<3;
		}

		for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_bstart[i] = i<<3;
		}

		OVI_REG_RD(0xCC471008,i);
		OVI_REG_RD(0xCC47100C,i);
		OVI_REG_RD(0xCC472008,i);
		OVI_REG_RD(0xCC47200C,i);
		OVI_REG_RD(0xCC473008,i);
		OVI_REG_RD(0xCC47300C,i);

		// gamma table upload
		OVI_TCON_M23_RdFL(tcon_dga_mode);
		OVI_TCON_M23_Wr01(tcon_dga_mode, dga_up_mode, 0x0); // dga_up_mode : 1 -> sync update
		OVI_TCON_M23_WrFL(tcon_dga_mode);
		OVI_TCON_M23_RdFL(tcon_dga_mode);
		OVI_TCON_M23_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
		OVI_TCON_M23_WrFL(tcon_dga_mode);

		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Wr01(tcon_control, dga_en, 0x1);
		OVI_TCON_M23_WrFL(tcon_control);

		iounmap((void *)reg_rstart); reg_rstart = NULL;
		iounmap((void *)reg_gstart); reg_gstart = NULL;
		iounmap((void *)reg_bstart); reg_bstart = NULL;

	} while(0);

	if (reg_rstart != NULL)
		iounmap((void *)reg_rstart);
	if (reg_gstart != NULL)
		iounmap((void *)reg_gstart);
	if (reg_bstart != NULL)
		iounmap((void *)reg_bstart);
	
	return;
}


#if 0
static int _OVI_M23_Vx1ChipInfoMemInit(void)
{
	int ret = RET_OK;
	BE_FRM_MEM_CFG_T *pChInfMem = gpBeChInfMem;
	int i;
		
	do {
		_gOviHwM23Info.pVx1ChipInfoVMapAddr = NULL;

		if (_gOviHwM23Info.hwDispOption.frcChipType != LX_OVI_FRC_CHIP_UD_BE_F22) break;
		
		if (pChInfMem == NULL 
			|| !pChInfMem->frame_base)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		if ((pChInfMem->frame_size != BE_OVI_HW_M23_VX1_CHIP_INFO_TOTAL_MEM_SIZE)
			|| (sizeof(BE_OVI_HW_M23_VX1_CHIP_INFO_T) != BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE))
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwM23Info.pVx1ChipInfoVMapAddr = vmap_phys(pChInfMem->frame_base, pChInfMem->frame_size);
		if (_gOviHwM23Info.pVx1ChipInfoVMapAddr == NULL)
		{
			OVI_ERROR("[OVI] pVMapAddr is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		for (i=0; i<BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
		{
			if (pChInfMem->frame_size < ((BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
											+BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET \
											+sizeof(BE_OVI_HW_M23_VX1_CHIP_INFO_T))) break;
			
			_gOviHwM23Info.pVx1ChipInfo[i] = (BE_OVI_HW_M23_VX1_CHIP_INFO_T *)(_gOviHwM23Info.pVx1ChipInfoVMapAddr \
																			+(BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
																			+BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
		}
		if (i != BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_OVI_M23_Vx1ChipInfoMemFill();
	} while(0);

	if (ret && (_gOviHwM23Info.pVx1ChipInfoVMapAddr != NULL))
	{
		vunmap_phys(_gOviHwM23Info.pVx1ChipInfoVMapAddr);
		_gOviHwM23Info.pVx1ChipInfoVMapAddr = NULL;
	}

	return ret;
}

static void _OVI_M23_Vx1ChipInfoMemFill(void)
{
	int i;
	UINT32 *addr;
	
	if (_gOviHwM23Info.pVx1ChipInfoVMapAddr == NULL) return;

	// Fill in HDR/CRC with default value for BUFF
	for (i=0; i<BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_TOTAL_NUM; i++)
	{
		addr = (UINT32 *)(_gOviHwM23Info.pVx1ChipInfoVMapAddr+ \
							(i*BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_SIZE)+BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
#ifdef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
		addr[0] = _B2L32(BE_OVI_HW_M23_VX1_CHIP_INFO_HDR|BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_DATA_SIZE);
		addr[1] = 0;
#else
		*addr = _B2L32(0x0EE00000|BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_DATA_SIZE);
#endif
	}

	for (i=0; i<BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
		// Fill in HDR/CRC for BUFF0,3
#ifdef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.info.maxNum = BE_OVI_HW_M23_VX1_CHIP_INFO_APB_NUM;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.info.bufIdx0 = 0;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.info.bufIdx1 = 3;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.info.version = 0;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.info.u32Data = _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.info.u32Data);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = 0;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.cnt1.u32Data = 0;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data = 0;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.cnt3.u32Data = 0;
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_DPG].offset = 0xFFFF & offsetof(BE_OVI_HW_M23_VX1_CHIP_INFO_T, dpg);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_DPG].size = 0xFFFF & sizeof(_gOviHwM23Info.pVx1ChipInfo[i]->dpg);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_DPG].u32Data \
													= _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_DPG].u32Data);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_CLR_TMP].offset = 0xFFFF & offsetof(BE_OVI_HW_M23_VX1_CHIP_INFO_T, colorTemp);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_CLR_TMP].size = 0xFFFF & sizeof(_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_CLR_TMP].u32Data \
													= _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_M23_VX1_CHIP_INFO_CLR_TMP].u32Data);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_LED_CTRL].offset = 0xFFFF & offsetof(BE_OVI_HW_M23_VX1_CHIP_INFO_T, ledSpiCtrl);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_LED_CTRL].size = 0xFFFF & sizeof(_gOviHwM23Info.pVx1ChipInfo[i]->ledSpiCtrl);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_LED_CTRL].u32Data \
													= _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_LED_CTRL].u32Data);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_PCC].offset = 0xFFFF & offsetof(BE_OVI_HW_M23_VX1_CHIP_INFO_T, pcc);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_PCC].size = 0xFFFF & sizeof(_gOviHwM23Info.pVx1ChipInfo[i]->pcc);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_PCC].u32Data \
													= _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_PCC].u32Data);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_OSD_LVL].offset = 0xFFFF & offsetof(BE_OVI_HW_M23_VX1_CHIP_INFO_T, osdLvCtrl);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_OSD_LVL].size = 0xFFFF & sizeof(_gOviHwM23Info.pVx1ChipInfo[i]->osdLvCtrl);
		_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_OSD_LVL].u32Data \
													= _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_M23_VX1_CHIP_INFO_OSD_LVL].u32Data);
		_gOviHwM23Info.pVx1ChipInfo[i]->hwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->endPacket = _B2L32(BE_OVI_HW_M23_VX1_CHIP_INFO_EP);
#else
		_gOviHwM23Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE); 
		_gOviHwM23Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_DPG_CTRL_SIZE); 
		_gOviHwM23Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_COLOR_TEMP_SIZE); 
		_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE); 
		_gOviHwM23Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_PCC_SIZE); 
		_gOviHwM23Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
		_gOviHwM23Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->phdr.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_PHDR_SIZE);
		_gOviHwM23Info.pVx1ChipInfo[i]->phdr.hwCrc = 0xFFFFFFFF;
		_gOviHwM23Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_RSVD_SIZE);
		_gOviHwM23Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF; 
#endif
	}

	wmb();

	return;
}

static void _OVI_M23_UpdateChipInfoHeader(void)
{
	int i;
	UINT32 hdrVal;

	if (_gOviHwM23Info.pVx1ChipInfoVMapAddr == NULL) return;

	for (i=0; i<BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
		// Check HDR error
		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->dpg.dataHwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE))
			&& (hdrVal != _B2L32(0x0A010000|OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader dpg data: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_DPG_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|OVI_HW_M23_VX1_CHIP_INFO_DPG_CTRL_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_DPG_CTRL_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader dpg ctrl: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_COLOR_TEMP_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|OVI_HW_M23_VX1_CHIP_INFO_COLOR_TEMP_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_M23_VX1_CHIP_INFO_COLOR_TEMP_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader colrtmp: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_M23_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader ledspi: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->pcc.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_PCC_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_M23_VX1_CHIP_INFO_PCC_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_PCC_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader pcc: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_M23_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader osd rgblv: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->phdr.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_PHDR_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_M23_VX1_CHIP_INFO_PHDR_SIZE)))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->phdr.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_PHDR_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->phdr.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader phdr: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwM23Info.pVx1ChipInfo[i]->rsvd.hwHdr;
		rmb();
		if (hdrVal != _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_RSVD_SIZE))
		{
			_gOviHwM23Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_M23_VX1_CHIP_INFO_RSVD_SIZE);
			_gOviHwM23Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("M23A0 OVI HW UpdateChipInfoHeader rsvd: 0x%x \n",hdrVal);
		}
	}

	wmb();

	return;
}
#endif

int OVI_M23_TscicWriteThread(void* data)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr = NULL;
	UINT32 tscicSizeNum;
	UINT32 tscicCtrlSizeNum;

	#if 1
	do {

		if (_gOviHwM23Info.tscicWritingFlag == TRUE)
		{
			OVI_ERROR("[OVI] already running!\n");
			ret = RET_ERROR;
			return ret;
		}

		_gOviHwM23Info.tscicWritingFlag = TRUE;

		// check input table size
		if ((_gOviHwM23Info.tscicCtrlSizeNum != OVI_HW_M23_INPUT_TSCIC_CTRL_SIZENUM) || (_gOviHwM23Info.tscicU8CtrlData == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((_gOviHwM23Info.tscicSize != OVI_HW_M23_INPUT_TSCIC_DATA_SIZE) || (_gOviHwM23Info.tscicU32Tbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		tscicSizeNum = _gOviHwM23Info.tscicSize / sizeof(UINT32);
		tscicCtrlSizeNum = _gOviHwM23Info.tscicCtrlSizeNum;

		// FCIC data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_fcic_data_a), 
											sizeof(UINT32));
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		OVI_TCON_M23_RdFL(tcon_fcic_ctrl);
		OVI_TCON_M23_Wr01(tcon_fcic_ctrl, checksum_clr, 0x0);
		OVI_TCON_M23_Wr01(tcon_fcic_ctrl, flash_done, 0x0);
		OVI_TCON_M23_WrFL(tcon_fcic_ctrl);

		OVI_TCON_M23_RdFL(tcon_fcic_addr);
		OVI_TCON_M23_Wr01(tcon_fcic_addr, flash_addr, 0x0);
		OVI_TCON_M23_WrFL(tcon_fcic_addr);

		for (i=0; i<tscicSizeNum; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwM23Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwM23Info.tscicU8CtrlData);
					_gOviHwM23Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwM23Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwM23Info.tscicU32Tbl);
					_gOviHwM23Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwM23Info.tscicThread = NULL;
				_gOviHwM23Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwM23Info.tscicU32Tbl[i], &regAddr[0]);
		}

		OVI_TCON_M23_RdFL(tcon_fcic_ctrl);
		OVI_TCON_M23_Wr01(tcon_fcic_ctrl, flash_done, 0x1);
		OVI_TCON_M23_WrFL(tcon_fcic_ctrl);

		iounmap((void *)regAddr);
		regAddr = NULL;

		// FCIC CTRL data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_cic_reg000), 
											sizeof(UINT32)*OVI_HW_M23_INPUT_TSCIC_CTRL_SIZENUM);
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0; i<tscicCtrlSizeNum; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwM23Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwM23Info.tscicU8CtrlData);
					_gOviHwM23Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwM23Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwM23Info.tscicU32Tbl);
					_gOviHwM23Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwM23Info.tscicThread = NULL;
				_gOviHwM23Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwM23Info.tscicU8CtrlData[i], &regAddr[i]);
		}

		OVI_TCON_M23_RdFL(tcon_init_test);
		OVI_TCON_M23_Wr01(tcon_init_test, init1_test, 0x1);
		OVI_TCON_M23_Wr01(tcon_init_test, init2_test, 0x1);
		OVI_TCON_M23_WrFL(tcon_init_test);
	} while(0);

	if(_gOviHwM23Info.tscicU8CtrlData != NULL)
	{
		vfree(_gOviHwM23Info.tscicU8CtrlData);
		_gOviHwM23Info.tscicU8CtrlData = NULL;
	}
	if (_gOviHwM23Info.tscicU32Tbl != NULL)
	{
		vfree(_gOviHwM23Info.tscicU32Tbl);
		_gOviHwM23Info.tscicU32Tbl = NULL;
	}
	if (regAddr != NULL)
		iounmap((void *)regAddr);

	_gOviHwM23Info.tscicThread = NULL;
	_gOviHwM23Info.tscicWritingFlag = FALSE;

	#endif
	return ret;
}

int OVI_M23_DemuraWriteThread(void* data)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr = NULL;
	UINT32 demuraSize;
	UINT32 demuraConfigSize;
	__attribute__((unused)) UINT32 regVal;
	char *pAddr = NULL;

	#if 1 //
	do {

		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG(gpOviTconMem->base);
		}

		OVI_TCON_M23_RdFL(tcon_base_address1);
		OVI_TCON_M23_Rd01(tcon_base_address1, demura_base_address, regVal);

		if (regVal != _gOviHwM23Info.tconBaseAddress + OVI_HW_M23_DEMURA_MEM_OFFSET)
		{
			OVI_ERROR("[WARN][OVI] demura addr setting error!\n");
			OVI_BREAK_WRONG(regVal);
		}

		if (_gOviHwM23Info.demuraWritingFlag == TRUE)
		{
			OVI_ERROR("[OVI] already running!\n");
			ret = RET_ERROR;
			return ret;
		}

		_gOviHwM23Info.demuraWritingFlag = TRUE;

		// check input table size
		if ((_gOviHwM23Info.demuraConfigSize > OVI_HW_M23_INPUT_DEMURA_CFG_DATA_SIZE) || (_gOviHwM23Info.demuraU8ConfigData == NULL))
		{
			OVI_ERROR("[OVI] Input DEMURA Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((_gOviHwM23Info.demuraSize > OVI_HW_M23_DEMURA_MEM_SIZE) || (_gOviHwM23Info.demuraU8Tbl == NULL))
		{
			OVI_ERROR("[OVI] Input DEMURA Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		demuraSize = _gOviHwM23Info.demuraSize;
		demuraConfigSize = _gOviHwM23Info.demuraConfigSize;

		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_demura_reg_start),
											demuraConfigSize*sizeof(UINT32));
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		// DEMURA disable setting
		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Wr01(tcon_control, demu_en, 0x0);
		OVI_TCON_M23_WrFL(tcon_control);

		OVI_TCON_M23_RdFL(demura_main);
		OVI_TCON_M23_Wr01(demura_main, spoc_mode, 0x0);
		OVI_TCON_M23_WrFL(demura_main);

		for (i=0; i<demuraConfigSize; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwM23Info.demuraU8ConfigData != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8ConfigData);
					_gOviHwM23Info.demuraU8ConfigData = NULL;
				}
				if (_gOviHwM23Info.demuraU8Tbl != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8Tbl);
					_gOviHwM23Info.demuraU8Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwM23Info.demuraThread = NULL;
				_gOviHwM23Info.demuraWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwM23Info.demuraU8ConfigData[i], &regAddr[i]);
		}

		iounmap((void *)regAddr);
		regAddr = NULL;

		OVI_REG_WR(0xCC47A0C0,_gOviHwM23Info.demuraU8Tbl[_gOviHwM23Info.demuraSize-4]); // TCON_DEMURA_IReg_START
		OVI_REG_WR(0xCC47A0C4,_gOviHwM23Info.demuraU8Tbl[_gOviHwM23Info.demuraSize-3]);
		OVI_REG_WR(0xCC47A0C8,_gOviHwM23Info.demuraU8Tbl[_gOviHwM23Info.demuraSize-2]);
		OVI_REG_WR(0xCC47A0CC,_gOviHwM23Info.demuraU8Tbl[_gOviHwM23Info.demuraSize-1]);

		pAddr = (char *)vmap_phys(gpOviTconMem->base + OVI_HW_M23_DEMURA_MEM_OFFSET, OVI_HW_M23_DEMURA_MEM_SIZE);
		if(pAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in vmap_phys! \n");
			ret = RET_ERROR;
			break;
		}

		_ConvertEndian32((UINT32 *)_gOviHwM23Info.demuraU8Tbl, _gOviHwM23Info.demuraSize);
		memcpy(pAddr, (void *)_gOviHwM23Info.demuraU8Tbl, _gOviHwM23Info.demuraSize);

		wmb();

		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Wr01(tcon_control, demu_en, 0x1);
		OVI_TCON_M23_WrFL(tcon_control);

		OVI_TCON_M23_RdFL(tcon_odc_opt2);
		OVI_TCON_M23_Wr01(tcon_odc_opt2, dga_in_sel, 0x1);
		OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_in_sel, 0x1);
		OVI_TCON_M23_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x1);
		OVI_TCON_M23_WrFL(tcon_odc_opt2);

		vunmap_phys(pAddr);
		pAddr = NULL;

	} while(0);

	if(_gOviHwM23Info.demuraU8ConfigData != NULL)
	{
		vfree(_gOviHwM23Info.demuraU8ConfigData);
		_gOviHwM23Info.demuraU8ConfigData = NULL;
	}
	if (_gOviHwM23Info.demuraU8Tbl != NULL)
	{
		vfree(_gOviHwM23Info.demuraU8Tbl);
		_gOviHwM23Info.demuraU8Tbl = NULL;
	}
	if (regAddr != NULL)
		iounmap((void *)regAddr);
	if (pAddr != NULL)
		vunmap_phys(pAddr);

	_gOviHwM23Info.demuraThread = NULL;
	_gOviHwM23Info.demuraWritingFlag = FALSE;

	#endif

	return ret;
}


void OVI_HW_M23_HWDisplayOptionInit(void)
{
	OVI_PRINT("M23A0 OVI HW display option init!\n");

	_OVI_M23_GetHWDispOption(&_gOviHwM23Info.hwDispOption);
}

int OVI_HW_M23_PreInitialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("M23A0 OVI pre init!\n");

		_OVI_M23_GetHWDispOption(&_gOviHwM23Info.hwDispOption);
	} while(0);

	return ret;
}

static int _OVI_HW_M23_GetCfgs(void)
{
	char *tok, *sav_tok;
	char delim[] = ":";
	char ovi_opt[32];
	UINT32 panel_inch;
	struct ovi_hw_m23_pmaker_entry *pmaker_entry = _g_ovi_hw_m23_pmaker_entry;
	LX_OVI_HW_DISPLAY_INFO_T *p_hwopt = &_gOviHwM23Info.hwDispOption;

	//if (p_hwopt->panelFramerate != LX_OVI_PANEL_FRAMERATE_60HZ)	return 0;

	memset(ovi_opt,0,32);
	if (RET_OK==OS_ScanKernelCmdline("ovi_opt=%s", ovi_opt))
	{
		tok=simple_strtok(ovi_opt, delim, &sav_tok);
		while (pmaker_entry->name != NULL) {
			if (!strncmp(pmaker_entry->name,tok,strlen(pmaker_entry->name))) {
				_g_ovi_hw_m23_pmaker = pmaker_entry->idx;
				break;
			}
			pmaker_entry++;
		}

		tok=simple_strtok(NULL, delim, &sav_tok);
		if(1 != sscanf(tok, "%d", &panel_inch))
		{
			OVI_PRINT("no support inch : %s\n", tok);
		}
		_g_ovi_hw_m23_pinch = panel_inch;
	}

	_g_ovi_hw_m23_ptype = p_hwopt->panelInterface;

	if (_g_ovi_hw_m23_ptype == LX_OVI_PANEL_EPI || _g_ovi_hw_m23_ptype == LX_OVI_PANEL_EPI_QSAC)
	{
		_g_ovi_hw_m23_od_en = 1;
	}
	else if (_g_ovi_hw_m23_ptype == LX_OVI_PANEL_CEDS)
	{
		if (_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_F || _g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_G)
		{
			if (_g_ovi_hw_m23_pinch == 50)
			{
				_g_ovi_hw_m23_od_en = 1;
			}
		}
		else if (_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_S || \
			_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_U || \
			_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_M || \
			_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_N || \
			_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_C || \
			_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_J || \
			_g_ovi_hw_m23_pmaker == OVI_HW_M23_PMAKER_X)
		{
			_g_ovi_hw_m23_od_en = 1;
		}
	}

	return 0;
}

int OVI_HW_M23_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to M23 A0\n");

		_OVI_HW_M23_GetCfgs();

		_gOviHwM23Info.pm_status = 0xff;
		_gOviHwM23Info.pm_suspend = 0;

		/* Set configuration of Output mode presets, for mode change on run time */
		_gOVIOutputModes_M23.pOVIOutputModes = _gOVIOutputModes_M23Ax;
		_gOVIOutputModes_M23.number_of_modes	 = sizeof(_gOVIOutputModes_M23Ax)/sizeof(LX_OVI_OUTPUT_MODE_T);

		gOVI_TCON_M23.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_M23A0_T));
		#if 0 // not support
		gOVI_TCON_LODC_M23.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_M23A0_T));
		gOVI_TCON_CAD_M23.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_CAD_REG_M23A0_T));
		gOVI_OIF_M23.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_M23A0_T));
		#endif

		gOVI_TCON_M23.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE, sizeof(OVI_TCON_REG_M23A0_T));
		#if 0 // not support
		gOVI_TCON_LODC_M23.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M23A0_BASE, sizeof(OVI_TCON_LODC_REG_M23A0_T));
		gOVI_TCON_CAD_M23.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_M23A0_BASE, sizeof(OVI_TCON_CAD_REG_M23A0_T));
		gOVI_OIF_M23.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_M23A0_BASE, sizeof(OVI_OIF_REG_M23A0_T));
		#endif
		
		/* for copying value used in channel power on/off function */ 
		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_08); // reuse(no active stanby)
		_gOviHwM23Info.chPowerOnRegValue1 = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_08);
		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_00);
		_gOviHwM23Info.chPowerOnRegValue2 = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_00);
		//_gOviHwM23Info.chPowerOnRegValue1 = 0x00FFFFFF;
		//_gOviHwM23Info.chPowerOnRegValue2 = 0x10000011;

		/* for copying value used in H-Reverse on/off function */
		OVI_TCON_M23_RdFL(tcon_hor_mode);
		OVI_TCON_M23_Rd01(tcon_hor_mode, hor_reverse, _gOviHwM23Info.horReverseRegFieldValue);

		/* for copying value used in spread spectrum on/off & display resume function */
		CTOP_CTRL_M23Ax_RdFL(CRG_TOP_CTRL, disp_aiopll_00); //bringup-check // need to check when apply ss
		_gOviHwM23Info.spreadSpectrumRegValue1 = CTOP_CTRL_M23Ax_Rd(CRG_TOP_CTRL, disp_aiopll_00);
		CTOP_CTRL_M23Ax_RdFL(CRG_TOP_CTRL, disp_aiopll_01);
		_gOviHwM23Info.spreadSpectrumRegValue2 = CTOP_CTRL_M23Ax_Rd(CRG_TOP_CTRL, disp_aiopll_01);

		#if 0
		gOVI_HW_M23_SS_CTRL1 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_M23A0_T *)ioremap(0xC930E400, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_M23A0_T));
		gOVI_HW_M23_SS_CTRL2 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_M23A0_T *)ioremap(0xC930E404, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_M23A0_T));
		gOVI_HW_M23_SS_CTRL3 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_M23A0_T *)ioremap(0xC930E408, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_M23A0_T));

		/* for copying value used in display resume function */
		OVI_REG_RD(0xC930F000, _gOviHwM23Info.tconClkGatingRegValue);
		#endif

#if 0
		/* for copying value used in display resume function */
		CTOP_CTRL_M23Ax_RdFL(DPE_SYN, crg_dpe00);
		_gOviHwM23Info.tconClkGatingRegValue = CTOP_CTRL_M23Ax_Rd(DPE_SYN, crg_dpe00);
#endif

		#if 1 //
		/* for copying value used in bypass function */
		OVI_TCON_M23_RdFL(tcon_odc_opt2);
		OVI_TCON_M23_Rd01(tcon_odc_opt2, odc_bypass, _gOviHwM23Info.odcBypassRegFieldValue); 
		OVI_TCON_M23_Rd01(tcon_odc_opt2, lodc_bypass, _gOviHwM23Info.lodcBypassRegFieldValue);

		#endif

		OVI_TCON_M23_RdFL(tcon_odc_opt2);
		OVI_TCON_M23_Rd01(tcon_odc_opt2, wb_in_sel, _gOviHwM23Info.useSpecialDgaFlag);

		OVI_TCON_M23_RdFL(oif_lvds_config0);
		_gOviHwM23Info.converterCheckVal = OVI_TCON_M23_Rd(oif_lvds_config0);

		#if 0
		/* Update pre-emphasis & swing level value used in display resume */
		_OVI_M23_RegParamRead(ovi_m23a0_disp_preEmp_swiLvl, 
											OVI_HW_M23_ARRAY_SIZE(ovi_m23a0_disp_preEmp_swiLvl), 0);
		#endif

		_gOviHwM23Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_gOviHwM23Info.tscicWritingFlag = FALSE;
		_gOviHwM23Info.tscicThread = NULL;
		_gOviHwM23Info.tscicU32Tbl = NULL;
		_gOviHwM23Info.tscicU8CtrlData = NULL;

		_gOviHwM23Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwM23Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwM23Info.delayedRGBGamma.pu32LutB = NULL;

		_gColTemp.bIsGet = 0;
		_gColTemp.r_gain = OVI_HW_M23_WB_DEFAULT_GAIN;
		_gColTemp.g_gain = OVI_HW_M23_WB_DEFAULT_GAIN;
		_gColTemp.b_gain = OVI_HW_M23_WB_DEFAULT_GAIN;
		_gColTemp.r_offset = 0;
		_gColTemp.g_offset = 0;
		_gColTemp.b_offset = 0;

		INIT_DELAYED_WORK(&_gOviHwM23Info.delayedRGBGamma.dlyWork, _OVI_M23_CallbackDelayedGamma);

#if 0
		ret = _OVI_M23_Vx1ChipInfoMemInit();
		if (ret)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory init is failed!\n");
			OVI_BREAK_WRONG(ret);
		}
#endif

		_OVI_M23_GetPempItuneData(&_gOviHwM23Info.pempItuneData);
		_OVI_M23_Get_DC_Cal(_gOviHwM23Info.dcVal);
		_OVI_M23_InitDGA();
		_OVI_M23_DispRegDataInit(&_gOviHwM23Info.dispOption,TRUE);
		
		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_02, 0x00000030);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_02);

			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_02, 0x00000020);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_02);
		}

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! M23 ODC will be disabled!\n");

			_gOviHwM23Info.tconBaseAddress = 0;
		}
		else
		{
			_gOviHwM23Info.tconBaseAddress = gpOviTconMem->base;

			#if 1 //
			OVI_TCON_M23_RdFL(tcon_base_address0);
			OVI_TCON_M23_Wr(tcon_base_address0, _gOviHwM23Info.tconBaseAddress);
			OVI_TCON_M23_WrFL(tcon_base_address0);

			if (_g_ovi_hw_m23_od_en == 1)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_M23_WrFL(tcon_control);
			}

			if (gpOviTconMem->size >= OVI_HW_M23_DEMURA_MEM_OFFSET+OVI_HW_M23_DEMURA_MEM_SIZE )
			{
				OVI_TCON_M23_RdFL(tcon_base_address1);
				OVI_TCON_M23_Wr(tcon_base_address1, _gOviHwM23Info.tconBaseAddress + OVI_HW_M23_DEMURA_MEM_OFFSET);
				OVI_TCON_M23_WrFL(tcon_base_address1);
			}
			#endif
		}
	} while(0);

	return ret;
}

int OVI_HW_M23_Close(void)
{
	int ret = RET_OK;

	cancel_delayed_work_sync(&_gOviHwM23Info.delayedRGBGamma.dlyWork);
	if (_gOviHwM23Info.delayedRGBGamma.pu32LutR != NULL) 
	{
		vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutR);
		_gOviHwM23Info.delayedRGBGamma.pu32LutR = NULL;
	}
	if (_gOviHwM23Info.delayedRGBGamma.pu32LutG != NULL) 
	{
		vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutG);
		_gOviHwM23Info.delayedRGBGamma.pu32LutG = NULL;
	}
	if (_gOviHwM23Info.delayedRGBGamma.pu32LutB != NULL) 
	{
		vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutB);
		_gOviHwM23Info.delayedRGBGamma.pu32LutB = NULL;
	}

	if(gOVI_TCON_M23.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_M23.shdw.addr);
		gOVI_TCON_M23.shdw.addr = NULL;
	}
	#if 0 // not support
	if(gOVI_TCON_LODC_M23.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_LODC_M23.shdw.addr);
		gOVI_TCON_LODC_M23.shdw.addr = NULL;
	}
	if(gOVI_TCON_CAD_M23.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_CAD_M23.shdw.addr);
		gOVI_TCON_CAD_M23.shdw.addr = NULL;
	}
	if(gOVI_OIF_M23.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_M23.shdw.addr);
		gOVI_OIF_M23.shdw.addr = NULL;
	}
	#endif

	if (gOVI_TCON_M23.phys.addr)
	{
		iounmap((void *)gOVI_TCON_M23.phys.addr);
		gOVI_TCON_M23.phys.addr = NULL;
	}
	#if 0 // not support
	if (gOVI_TCON_LODC_M23.phys.addr)
	{
		iounmap((void *)gOVI_TCON_LODC_M23.phys.addr);
		gOVI_TCON_LODC_M23.phys.addr = NULL;
	}
	if (gOVI_TCON_CAD_M23.phys.addr)
	{
		iounmap((void *)gOVI_TCON_CAD_M23.phys.addr);
		gOVI_TCON_CAD_M23.phys.addr = NULL;
	}
	if (gOVI_OIF_M23.phys.addr)
	{
		iounmap((void *)gOVI_OIF_M23.phys.addr);
		gOVI_OIF_M23.phys.addr = NULL;
	}
	#endif
	#if 0 // not support
	if (gOVI_HW_M23_SS_CTRL1)
	{
		iounmap((void *)gOVI_HW_M23_SS_CTRL1);
		gOVI_HW_M23_SS_CTRL1 = NULL;
	}
	if (gOVI_HW_M23_SS_CTRL2)
	{
		iounmap((void *)gOVI_HW_M23_SS_CTRL2);
		gOVI_HW_M23_SS_CTRL2 = NULL;
	}
	if (gOVI_HW_M23_SS_CTRL3)
	{
		iounmap((void *)gOVI_HW_M23_SS_CTRL3);
		gOVI_HW_M23_SS_CTRL3 = NULL;
	}
	#endif
	
#if 0
	if (_gOviHwM23Info.pVx1ChipInfoVMapAddr != NULL)
	{
		vunmap_phys(_gOviHwM23Info.pVx1ChipInfoVMapAddr);
		_gOviHwM23Info.pVx1ChipInfoVMapAddr = NULL;
	}
#endif

	return ret;
}

int OVI_HW_M23_Suspend(void)
{
	int ret = RET_OK;

	do {
		cancel_delayed_work_sync(&_gOviHwM23Info.delayedRGBGamma.dlyWork);
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutR);
			_gOviHwM23Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutG);
			_gOviHwM23Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutB);
			_gOviHwM23Info.delayedRGBGamma.pu32LutB = NULL;
		}
	} while(0);

	return ret;
}

int OVI_HW_M23_EarlyResume(void)
{
	int ret = RET_OK;

	do {

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_08);
		if (!(CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_08) & OVI_HW_M23_CH_POWER_REG_MASK)) // Instant boot
		{
			_OVI_M23_DispInit(&_gOviHwM23Info.dispOption);
		}

#if 0
		else
		{
			_OVI_M23_Vx1ChipInfoMemFill();
		}
#endif
	} while(0);

	return ret;
}

int OVI_HW_M23_Resume(void)
{
	int ret = RET_OK;

	do {
		#if 1
		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_08);
		if (!(CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_08) & OVI_HW_M23_CH_POWER_REG_MASK)) // Instant boot
		{
			if (_gOviHwM23Info.tscicWritingFlag == TRUE)
			{
				if (_gOviHwM23Info.tscicThread != NULL)
				{
					kthread_stop(_gOviHwM23Info.tscicThread);
					_gOviHwM23Info.tscicThread = NULL;
				}

				_gOviHwM23Info.tscicWritingFlag = FALSE;
			}

			if (_gOviHwM23Info.demuraWritingFlag == TRUE)
			{
				if (_gOviHwM23Info.demuraThread != NULL)
				{
					kthread_stop(_gOviHwM23Info.demuraThread);
					_gOviHwM23Info.demuraThread = NULL;
				}

				_gOviHwM23Info.demuraWritingFlag = FALSE;
			}

			_gOviHwM23Info.isDispOutDisabled = TRUE;
		}
		#endif

		_gOviHwM23Info.wbEn = FALSE;
		_gOviHwM23Info.wbBypassEn = FALSE;
		_gOviHwM23Info.dgaEn = FALSE;
		_gOviHwM23Info.dgaBypassEn = FALSE;
		_gOviHwM23Info.mleModeOff = FALSE;
		_gOviHwM23Info.odcBypassEn = FALSE;

		cancel_delayed_work_sync(&_gOviHwM23Info.delayedRGBGamma.dlyWork);
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutR);
			_gOviHwM23Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutG);
			_gOviHwM23Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutB);
			_gOviHwM23Info.delayedRGBGamma.pu32LutB = NULL;
		}
		
		_gPrevRedGain = OVI_HW_M23_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_M23_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_M23_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0;

		_gOviHwM23Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_OVI_M23_SetPempItuneData(&_gOviHwM23Info.pempItuneData);
		_OVI_M23_Set_DC_Cal(_gOviHwM23Info.dcVal);
		_OVI_M23_InitDGA();

		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_02, 0x00000030);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_02);

			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_02, 0x00000020);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_02);
		}

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! M23 ODC will be disabled!\n");

			_gOviHwM23Info.tconBaseAddress = 0;
		}
		else
		{
			_gOviHwM23Info.tconBaseAddress = gpOviTconMem->base;

			#if 1 //
			OVI_TCON_M23_RdFL(tcon_base_address0);
			OVI_TCON_M23_Wr(tcon_base_address0, _gOviHwM23Info.tconBaseAddress);
			OVI_TCON_M23_WrFL(tcon_base_address0);

			if (_g_ovi_hw_m23_od_en == 1)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_M23_WrFL(tcon_control);
			}

			if (gpOviTconMem->size >= OVI_HW_M23_DEMURA_MEM_OFFSET+OVI_HW_M23_DEMURA_MEM_SIZE )
			{
				OVI_TCON_M23_RdFL(tcon_base_address1);
				OVI_TCON_M23_Wr(tcon_base_address1, _gOviHwM23Info.tconBaseAddress + OVI_HW_M23_DEMURA_MEM_OFFSET);
				OVI_TCON_M23_WrFL(tcon_base_address1);
			}
			#endif
		}
	} while(0);

	return ret;
}

#define OVI_HW_M23_OPT_BIT_MASK_STB (1<<0)
int OVI_HW_M23_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_PRINT("\n[OVI_HW_M23_SetDisplayOption] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
			pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
			pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
			pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
			pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

		memcpy((void *)&_gOviHwM23Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		if (!_gOviHwM23Info.dispOption.userSpecificOption.flags.SocOptionBIT31) // SocOptionBIT31 : 1 -> setDisplayOption debug mode
		{
			__attribute__((unused)) char hw_opt[32];
			
			// Forced settings by HW option(or boot option)
			if (_gOviHwM23Info.hwDispOption.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
			{
				_gOviHwM23Info.dispOption.panelInterface = LX_OVI_PANEL_VX1;
			}
			else
			{
				_gOviHwM23Info.dispOption.panelInterface = _gOviHwM23Info.hwDispOption.panelInterface;
			}

			_gOviHwM23Info.dispOption.panelFramerate = _gOviHwM23Info.hwDispOption.dispFramerate;
			_gOviHwM23Info.dispOption.panelResolution = _gOviHwM23Info.hwDispOption.dispResolution;
			if (_gOviHwM23Info.hwDispOption.isVx15Byte)
			{
				_gOviHwM23Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
			}
			else
			{
				_gOviHwM23Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
			}
			_gOviHwM23Info.dispOption.frcChipType = _gOviHwM23Info.hwDispOption.frcChipType;

			if (_gOviHwM23Info.hwDispOption.panelInterface == LX_OVI_PANEL_LVDS)
			{
				if ((RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
					&& (!strncmp(hw_opt,"hdmi",4)))
				{
					_gOviHwM23Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_JEIDA;
				}
				else
				{
					_gOviHwM23Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_VESA;
				}
			}
		}

		_OVI_M23_DispRegDataInit(&_gOviHwM23Info.dispOption,FALSE);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		OVI_PRINT("\n[OVI_HW_M23_SetBypass] En[%d], Mask[0x%x]\n\r", pstParams->bEnable, pstParams->u32BlockMask);

		#if 0 // not support
		if ((pstParams->u32BlockMask & LX_OVI_TCON_BOE_RGBW)
			|| (pstParams->u32BlockMask & LX_OVI_TCON_LGD_RGBW))
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M23_RdFL(tcon_odc_opt2);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_M23_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwM23Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M23_RdFL(tcon_odc_opt2);
					OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwM23Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_M23_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwM23Info.odcBypassEn = pstParams->bEnable;
		}	
		#endif

		if (pstParams->u32BlockMask & LX_OVI_TCON_GAMMA)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, dga_en, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, dga_en, _gOviHwM23Info.dgaEn ? 0x1 : 0x0);
				OVI_TCON_M23_WrFL(tcon_control);
			}
			_gOviHwM23Info.dgaBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_WB)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, wb_en, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, wb_en, _gOviHwM23Info.wbEn ? 0x1 : 0x0);
				OVI_TCON_M23_WrFL(tcon_control);
			}
			_gOviHwM23Info.wbBypassEn = pstParams->bEnable;
		}

		#if 1 // not support
		if (pstParams->u32BlockMask & LX_OVI_TCON_LODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M23_RdFL(tcon_odc_opt2);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, lodc_bypass, 0x1);
				OVI_TCON_M23_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwM23Info.lodcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M23_RdFL(tcon_odc_opt2);
					OVI_TCON_M23_Wr01(tcon_odc_opt2, lodc_bypass, 0x0);
					OVI_TCON_M23_WrFL(tcon_odc_opt2);
				}
			}
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_ODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M23_RdFL(tcon_odc_opt2);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_M23_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwM23Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M23_RdFL(tcon_odc_opt2);
					OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwM23Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_M23_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwM23Info.odcBypassEn = pstParams->bEnable;
		}
		#endif
	} while(0);

	return ret;
}

int OVI_HW_M23_SetCombination(UINT32 param)
{
	int ret = RET_ERROR;
	int i,count;
	volatile LX_OVI_REG_T	*regs;
	char	*index;
	unsigned int read_data, same;
	BOOLEAN ignore = FALSE;

	do {
		/* Step 1. Check whether paramater is valid */
		if(param == 119) {	// Magic keyword to print available output modes...
			printk("\n[OVI] Display all register-set-presets ...\n");
			for(i=0; i<_gOVIOutputModes_M23.number_of_modes;i++)
			{
				printk("  Index[%d] : %s", i,_gOVIOutputModes_M23.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(param >= 10000)
		{
			param = param - 10000;
			printk("\n[OVI] Compare register values regarding to register-set index[%d]", param);

			if(param > _gOVIOutputModes_M23.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]", param);
				break;
			}

			regs  = _gOVIOutputModes_M23.pOVIOutputModes[param].regs;
			count = _gOVIOutputModes_M23.pOVIOutputModes[param].count;
			index = _gOVIOutputModes_M23.pOVIOutputModes[param].index;

			printk("\n[OVI] Register Index[%d] => %s",param, (char *)index);
			for(i=0; i<count; i++){
				if (regs[i].addr == OVI_HW_M23_REG_PARAM_OP_WAIT) continue;

				if (regs[i].addr == OVI_HW_M23_REG_PARAM_OP_CHECK)
				{
					_OVI_M23_IgnoreRegSet(regs[i].value, &ignore);
					continue;
				}

				if (ignore) continue;
				
				OVI_REG_RD(regs[i].addr, read_data);
				if(read_data == regs[i].value) same = 1;
				else same = 0;

				printk("\n[%03d] Current value of [0x%08x] => [0x%08x] / index value [0x%08x] (%s)", i, regs[i].addr, read_data, regs[i].value, same ? "SAME":"DIFFER");
			}
			printk("\n[OVI] Register read complete!\n");

			ret = RET_OK;
			break;
		}
		else if(param > _gOVIOutputModes_M23.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", param);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_M23.pOVIOutputModes[param].regs;
		count = _gOVIOutputModes_M23.pOVIOutputModes[param].count;
		index = _gOVIOutputModes_M23.pOVIOutputModes[param].index;

		printk("\n[OVI] Setting to registers to register-set-index => %s", (char *)index);
		for(i=0; i<count; i++){
			if (regs[i].addr == OVI_HW_M23_REG_PARAM_OP_WAIT)
			{
				printk("\n[%03d] Delay... %dms", i, regs[i].value/1000);
				OS_UsecDelay(regs[i].value);
			}

			if (regs[i].addr == OVI_HW_M23_REG_PARAM_OP_CHECK)
			{
				_OVI_M23_IgnoreRegSet(regs[i].value, &ignore);
				continue;
			}

			if (ignore) continue;
			
			printk("\n[%03d] Writing... [0x%08x] <= [0x%08x]", i, regs[i].addr, regs[i].value);
			OVI_REG_WR(regs[i].addr, regs[i].value);
		}
		printk("\n[OVI] Setting preset complete!\n");

		ret = RET_OK;
	} while(0);

	return ret;
}

int OVI_HW_M23_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal = 0;
#if 0 // bringup-check //need to check when apply ss 
	OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_M23A0_T ss_ctrl0;
	OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_M23A0_T ss_ctrl1;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (_gOviHwM23Info.spreadSpectrumRegValue1 & 0x4) break; // default DSS OFF

		if(pstParams->bEnable)
		{
			if (pstParams->eSpreadRatio == 0 || pstParams->u16Period == 0)
			{
				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwM23Info.spreadSpectrumRegValue1 | 0x4);
				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll0);

				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll1, _gOviHwM23Info.spreadSpectrumRegValue2);
				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll2, 0x01400000);

				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll1);
				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll2);

				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwM23Info.spreadSpectrumRegValue1);
				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll0);

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("Enable DSS with initial value. register val: 0x%x\n", regVal);
			}
			else
			{
				UINT32 M, NPC, NSC;
				UINT32 ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF;

				UINT32 spread_ratio, disp_mod_freq;

				ss_ctrl0 = *gOVI_HW_M23_SS_CTRL1;
				ss_ctrl1 = *gOVI_HW_M23_SS_CTRL2;

				M = ss_ctrl0.reg_aiopll_m;
				NPC = ss_ctrl1.reg_aiopll_npc;
				NSC = ss_ctrl1.reg_aiopll_nsc;

				if(!M) M = 1;

				ACCURACY = ss_ctrl0.reg_aiopll_accuracy;
				UPDN_MAX = ss_ctrl0.reg_aiopll_updn_max;
				MOD_FREQ = ss_ctrl0.reg_aiopll_mod_freq_max;
				RESULT_RF = GET_RESULT_RF(ACCURACY);

				if (UPDN_MAX == 0 || RESULT_RF == 0 || (NPC == 0 && NSC == 0))
				{
					OVI_PRINT("error! wrong value\n");
					ret = RET_ERROR;
					break;
				}

				spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
				disp_mod_freq = MOD_FREQ_OUT(FIN_DISP, M, MOD_FREQ, UPDN_MAX);
				OVI_PRINT("current ==> M: %u, NPC: %u, NSC: %u\n",
				M, NPC, NSC);
				OVI_PRINT("disp accracy: %u, updn_max: %u, mod_freq_max: %u, result_rt: %u\n",
				ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
				OVI_PRINT("disp spread_ratio  : %u.%4u, mod_freq : %uHz\n",
				spread_ratio/10000, spread_ratio%10000, disp_mod_freq);

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("register val: 0x%x\n", regVal);

				{ // calc SS
					UINT32 in_spread_ratio = pstParams->eSpreadRatio * 100;  // ?.?% * 1000
					UINT32 in_mod_freq = pstParams->u16Period * 100; // hz ( not khz)

					UINT32 div_result_val;
					UINT32 rating_factor;
					UINT32 result_rf;
					UINT32 calc_updn_max;
					UINT32 result_freq_max;

					div_result_val = (4 * NPC) + NSC;
					rating_factor = (in_spread_ratio * div_result_val) / 50;

					if(rating_factor <= 2000)
					{
						ACCURACY = 1;
						result_rf = 2;
					}
					else
					{
						ACCURACY = 0;
						result_rf = 4;
					}

					calc_updn_max = (((in_spread_ratio * 60) * div_result_val)
									/ ((result_rf * 50) * M));

					if (calc_updn_max > 60000)
					{
						OVI_PRINT("error! over max spread ratio\n");
						ret = RET_ERROR;
						break;
					}

					UPDN_MAX = (calc_updn_max + 500) / 1000;

					if(GETBIT_M(UPDN_MAX, 6) == 0x1)
					{
						OVI_PRINT("error! 6 bit, over max spread ratio\n");
						ret = RET_ERROR;
						break;
					}

					if((GETBIT_M(UPDN_MAX, 1) == 0x1)) {
						UPDN_MAX = UPDN_MAX + 0x4;
					}
					CLRBIT_M(UPDN_MAX, 0);
					CLRBIT_M(UPDN_MAX, 1);

					result_freq_max = ((((FIN_DISP * 1000000) / M) * 10)
									/ ((in_mod_freq) * ((4 * UPDN_MAX ) + 2))) - 10;

					MOD_FREQ = (result_freq_max + 5) / 10;

					RESULT_RF = GET_RESULT_RF(ACCURACY);

					if (UPDN_MAX == 0 || RESULT_RF == 0)
					{
						OVI_PRINT("error! wrong parameter\n");
						ret = RET_ERROR;
						break;
					}

					spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
					disp_mod_freq = MOD_FREQ_OUT(FIN_DISP, M, MOD_FREQ, UPDN_MAX);
					OVI_PRINT("changed ==> M: %u, NPC: %u, NSC: %u\n",
					M, NPC, NSC);
					OVI_PRINT("disp accracy: %u, updn_max: %u, mod_freq_max: %u, result_rt: %u\n",
					ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
					OVI_PRINT("disp spread_ratio  : %u.%4u, mod_freq : %uHz\n",
					spread_ratio/10000, spread_ratio%10000, disp_mod_freq);
				}

				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwM23Info.spreadSpectrumRegValue1 | 0x4);
				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll0);

				ss_ctrl0 = *gOVI_HW_M23_SS_CTRL1;
				ss_ctrl0.reg_aiopll_accuracy = ACCURACY;
				ss_ctrl0.reg_aiopll_updn_max = UPDN_MAX;
				ss_ctrl0.reg_aiopll_mod_freq_max = MOD_FREQ;
				*gOVI_HW_M23_SS_CTRL1 = ss_ctrl0;

				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll1, _gOviHwM23Info.spreadSpectrumRegValue2);
				CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll2, 0x01400000);

				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll1);
				CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll2);

				//CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwM23Info.spreadSpectrumRegValue1);
				//CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll0);
				ss_ctrl0 = *gOVI_HW_M23_SS_CTRL1;
				ss_ctrl0.reg_aiopll_dss = 0;
				*gOVI_HW_M23_SS_CTRL1 = ss_ctrl0;

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("register val: 0x%x\n", regVal);
			}
		}
		else
		{
			CTOP_CTRL_M23Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwM23Info.spreadSpectrumRegValue1 | 0x4);
			CTOP_CTRL_M23Ax_WrFL(CTOP_FMS, disp_aiopll0);
		}
	} while(0);
#endif
	return ret;
}

int OVI_HW_M23_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) int i;
	__attribute__((unused)) volatile UINT32 *regAddr1 = NULL;
	__attribute__((unused)) UINT8 *u8odLutData = NULL;
	__attribute__((unused)) UINT16 *u16lodLutData = NULL;
	__attribute__((unused)) UINT32 odLutSizeNum;
	#if 1
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
			odLutSizeNum = pstParams->odLut.sizeNum;

			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				// check input table size
				if((odLutSizeNum != (OVI_HW_M23_INPUT_OD_TOTAL_SIZE)) || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_odc_start), 
													sizeof(UINT32)*OVI_HW_M23_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_sts);
				OVI_TCON_M23_Wr01(tcon_sts, pix2_lock, 0x1);
				OVI_TCON_M23_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_sts);
				OVI_TCON_M23_Wr01(tcon_sts, pix2_lock, 0x0);
				OVI_TCON_M23_WrFL(tcon_sts);
				break;
			}

			if (pstParams->eMode != LX_OVI_TCON_LINEOD_PCID)
			{
				u8odLutData = (UINT8 *)vmalloc(odLutSizeNum);
				if(u8odLutData == NULL)
				{
					OVI_ERROR("[OVI] memory allocate failed! \n");
					ret = RET_ERROR;
					break;
				}

				ret = copy_from_user(u8odLutData, (void __user *)pstParams->odLut.pData, odLutSizeNum);
				if(ret)
				{
					OVI_ERROR("[OVI] Error in copying from user! \n");
					ret = RET_ERROR;
					break;
				}
			}

			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				__attribute__((unused)) UINT32 regVal = 0;
				UINT32 rData = 0;
				UINT32 gData = 0;
				UINT32 bData = 0;

				for(i=0; i<OVI_HW_M23_INPUT_OD_SIZENUM; i++)
				{
					rData = u8odLutData[i] & 0xFF;
					gData = u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*1)+i] & 0xFF;
					bData = u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*2)+i] & 0xFF;

					regVal = rData | (gData << 8) | (bData << 16);
					
					writel_relaxed(regVal, &regAddr1[i]);
				}

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg0);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg0, lut_index1, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+0]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg0, lut_index2, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+1]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg0, lut_index3, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+2]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg0);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg1);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg1, lut_index4, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+3]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg1, lut_index5, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+4]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg1, lut_index6, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+5]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg1, lut_index7, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+6]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg1);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg2);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg2, lut_index8, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+7]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg2, lut_index9, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+8]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg2, lut_index10, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+9]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg2, lut_index11, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+10]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg2);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg3);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg3, lut_index12, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+11]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg3, lut_index13, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+12]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg3, lut_index14, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+13]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg3, lut_index15, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+14]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg3);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg4);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg4, lut_index16, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+15]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg4, lut_index17, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+16]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg4, lut_index18, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+17]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg4, lut_index19, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+18]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg4);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg5);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg5, lut_index20, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+19]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg5, lut_index21, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+20]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg5, lut_index22, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+21]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg5, lut_index23, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+22]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg5);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg6);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg6, lut_index24, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+23]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg6, lut_index25, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+24]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg6, lut_index26, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+25]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg6, lut_index27, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+26]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg6);

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg7);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg7, lut_index28, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+27]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg7, lut_index29, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+28]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg7, lut_index30, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+29]);
				OVI_TCON_M23_Wr01(tcon_odc_lut_idx_reg7, lut_index31, u8odLutData[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+30]);
				OVI_TCON_M23_WrFL(tcon_odc_lut_idx_reg7);
			}

			if(pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				__attribute__((unused)) UINT32 regVal;

				OVI_TCON_M23_RdFL(tcon_odc_lut_upload);
				OVI_TCON_M23_Wr01(tcon_odc_lut_upload, odc_upload, 0x0);
				OVI_TCON_M23_WrFL(tcon_odc_lut_upload);
				OVI_TCON_M23_RdFL(tcon_odc_lut_upload);
				OVI_TCON_M23_Wr01(tcon_odc_lut_upload, odc_upload, 0x1);
				OVI_TCON_M23_WrFL(tcon_odc_lut_upload);

				OVI_TCON_M23_RdFL(tcon_odc_opt2);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
				OVI_TCON_M23_WrFL(tcon_odc_opt2);

			}

		}
		else
		{
			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				UINT32 buff;
				UINT8 rData;
				UINT8 gData;
				UINT8 bData;
				UINT8 regVal;

				// check input table size
				if (pstParams->odLut.sizeNum != (OVI_HW_M23_INPUT_OD_TOTAL_SIZE))
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_odc_start), 
													sizeof(UINT32)*OVI_HW_M23_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				for (i = 0; i < OVI_HW_M23_INPUT_OD_SIZENUM; i++)
				{
					buff = readl_relaxed(&regAddr1[i]);
					rData = buff & 0xFF;
					gData = (buff >> 8) & 0xFF;
					bData = (buff >> 16) & 0xFF;
					
					put_user(rData, &(((UINT8 *)pstParams->odLut.pData)[i]));
					put_user(gData, &(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*1)+i]));
					put_user(bData, &(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*2)+i]));
				}

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg0);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg0, lut_index1, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+0]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+0]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg0, lut_index2, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+1]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+1]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg0, lut_index3, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+2]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+2]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg1);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg1, lut_index4, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+3]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+3]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg1, lut_index5, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+4]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+4]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg1, lut_index6, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+5]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+5]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg1, lut_index7, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+6]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+6]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg2);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg2, lut_index8, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+7]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+7]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg2, lut_index9, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+8]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+8]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg2, lut_index10, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+9]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+9]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg2, lut_index11, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+10]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+10]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg3);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg3, lut_index12, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+11]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+11]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg3, lut_index13, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+12]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+12]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg3, lut_index14, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+13]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+13]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg3, lut_index15, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+14]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+14]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg4);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg4, lut_index16, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+15]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+15]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg4, lut_index17, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+16]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+16]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg4, lut_index18, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+17]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+17]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg4, lut_index19, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+18]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+18]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg5);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg5, lut_index20, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+19]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+19]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg5, lut_index21, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+20]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+20]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg5, lut_index22, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+21]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+21]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg5, lut_index23, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+22]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+22]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg6);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg6, lut_index24, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+23]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+23]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg6, lut_index25, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+24]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+24]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg6, lut_index26, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+25]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+25]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg6, lut_index27, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+26]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+26]));

				OVI_TCON_M23_RdFL(tcon_odc_lut_idx_reg7);
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg7, lut_index28, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+27]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+27]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg7, lut_index29, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+28]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+28]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg7, lut_index30, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+29]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+29]));
				OVI_TCON_M23_Rd01(tcon_odc_lut_idx_reg7, lut_index31, regVal);
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+30]));
				put_user(regVal,&(((UINT8 *)pstParams->odLut.pData)[(OVI_HW_M23_INPUT_OD_SIZENUM*3)+OVI_HW_M23_INPUT_OD_INDEX_SIZENUM+30]));

			}

		}
	} while(0);
	
	if(u8odLutData != NULL)
		vfree(u8odLutData);
	if(u16lodLutData != NULL)
		vfree(u16lodLutData);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);
	#endif
	return ret;
}

int OVI_HW_M23_SetLodLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) int i;
	__attribute__((unused)) volatile UINT32 *regAddr1 = NULL;
	__attribute__((unused)) UINT8 *u8odLutData = NULL;
	__attribute__((unused)) UINT16 *u16lodLutData = NULL;
	__attribute__((unused)) UINT32 odLutSizeNum;
	#if 1
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
			odLutSizeNum = pstParams->odLut.sizeNum;

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				// check input table size
				if(odLutSizeNum != (OVI_HW_M23_INPUT_LOD_TOTAL_SIZENUM*sizeof(UINT16)) || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_lodc_table_data), 
													sizeof(UINT32));
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_sts);
				OVI_TCON_M23_Wr01(tcon_sts, pix2_lock, 0x1);
				OVI_TCON_M23_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_sts);
				OVI_TCON_M23_Wr01(tcon_sts, pix2_lock, 0x0);
				OVI_TCON_M23_WrFL(tcon_sts);
				break;
			}

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				u16lodLutData = (UINT16 *)vmalloc(odLutSizeNum*sizeof(UINT16));
				if(u16lodLutData == NULL)
				{
					OVI_ERROR("[OVI] memory allocate failed! \n");
					ret = RET_ERROR;
					break;
				}

				ret = copy_from_user(u16lodLutData, (void __user *)pstParams->odLut.pData, odLutSizeNum*sizeof(UINT16));
				if(ret)
				{
					OVI_ERROR("[OVI] Error in copying from user! \n");
					ret = RET_ERROR;
					break;
				}
			}

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID) // LOD
			{
				__attribute__((unused)) int k;
				__attribute__((unused)) UINT32 regVal;
				__attribute__((unused)) UINT32 idx = 0;

				OVI_TCON_M23_RdFL(tcon_lodc_table_addr);
				OVI_TCON_M23_Wr01(tcon_lodc_table_addr, lut_addr, 0x0);
				OVI_TCON_M23_WrFL(tcon_lodc_table_addr);
				OVI_TCON_M23_RdFL(tcon_lodc_table_index);
				OVI_TCON_M23_Wr01(tcon_lodc_table_index, lut_index, 0x0);
				OVI_TCON_M23_WrFL(tcon_lodc_table_index);

				/*for (k = 0; k < 10; k++)
				{
					regVal = k;
					OVI_TCON_M23_RdFL(tcon_lodc_table_addr);
					OVI_TCON_M23_Wr01(tcon_lodc_table_addr, lut_addr, 0x0);
					OVI_TCON_M23_WrFL(tcon_lodc_table_addr);
					OVI_TCON_M23_RdFL(tcon_lodc_table_index);
					OVI_TCON_M23_Wr01(tcon_lodc_table_index, lut_index, regVal);
					OVI_TCON_M23_WrFL(tcon_lodc_table_index);

					for (i = 0; i < 19*19; i++)
					{
						writel_relaxed((u16lodLutData[idx++] & 0xFFF), &regAddr1[0]);
					}
				}*/

				OVI_TCON_M23_RdFL(tcon_lodc_lut_mode);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_mode, addr_trans_on, 0x1);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_mode);

				for (i = 0; i < OVI_HW_M23_INPUT_LOD_SIZENUM; i++)
				{
					writel_relaxed((u16lodLutData[i] & 0xFFF), &regAddr1[0]);
				}

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg0);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg0, lodc_lut_index1, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+0]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg0, lodc_lut_index2, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+1]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg0);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg1);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg1, lodc_lut_index3, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+2]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg1, lodc_lut_index4, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+3]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg1);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg2);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg2, lodc_lut_index5, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+4]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg2, lodc_lut_index6, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+5]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg2);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg3);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg3, lodc_lut_index7, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+6]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg3, lodc_lut_index8, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+7]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg3);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg4);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg4, lodc_lut_index9, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+8]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg4, lodc_lut_index10, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+9]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg4);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg5);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg5, lodc_lut_index11, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+10]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg5, lodc_lut_index12, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+11]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg5);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg6);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg6, lodc_lut_index13, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+12]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg6, lodc_lut_index14, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+13]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg6);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg7);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg7, lodc_lut_index15, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+14]);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg7, lodc_lut_index16, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+15]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg7);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg8);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_idx_reg8, lodc_lut_index17, u16lodLutData[OVI_HW_M23_INPUT_LOD_SIZENUM+16]);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_idx_reg8);
			}

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID) // LOD
			{
				__attribute__((unused)) UINT32 regVal;
				__attribute__((unused)) UINT32 regVal2;

				OVI_TCON_M23_RdFL(tcon_odc_opt2);
				regVal = OVI_TCON_M23_Rd(tcon_odc_opt2);

				OVI_TCON_M23_Wr01(tcon_odc_opt2, dga_in_sel, 0x1); // set path for reset
				OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_in_sel, 0x1);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_M23_WrFL(tcon_odc_opt2);

				OVI_TCON_M23_RdFL(tcon_cad_reg_main);
				OVI_TCON_M23_Wr01(tcon_cad_reg_main, cad_on, 0x0);
				OVI_TCON_M23_WrFL(tcon_cad_reg_main);

				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, mem_sel, 0x1);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_odc_lut1_opt);
				OVI_TCON_M23_Wr01(tcon_odc_lut1_opt, lut1_add_opt, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_lut1_opt, lut1_full_opt, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_lut1_opt, lut1_zero_opt, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_lut1_opt, lut1_same_opt, 0x0);
				OVI_TCON_M23_WrFL(tcon_odc_lut1_opt);

				OVI_TCON_M23_RdFL(tcon_lodc_lut_upload);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_upload, odc_upload, 0x0);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_upload);
				OVI_TCON_M23_RdFL(tcon_lodc_lut_upload);
				OVI_TCON_M23_Wr01(tcon_lodc_lut_upload, odc_upload, 0x1);
				OVI_TCON_M23_WrFL(tcon_lodc_lut_upload);

				OS_MsecSleep(17);

				OVI_REG_RD(0xcc48000c, regVal2);
				OVI_REG_WR(0xcc48000c, regVal2 | 0x10000); // tcon reset ,CRG
				OVI_REG_WR(0xcc48000c, regVal2);

				OS_MsecSleep(50);

				OVI_TCON_M23_Wr(tcon_odc_opt2, regVal); // restore reg value
				OVI_TCON_M23_WrFL(tcon_odc_opt2);

				OVI_TCON_M23_RdFL(tcon_odc_opt2);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, lodc_bypass, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
				OVI_TCON_M23_WrFL(tcon_odc_opt2);

				OVI_TCON_M23_RdFL(tcon_odc_opt1);
				OVI_TCON_M23_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_M23_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_opt1, pcid_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_odc_opt1, pcid20_en, 0x1);
				OVI_TCON_M23_WrFL(tcon_odc_opt1);
			}

		}
		else
		{

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				UINT16 buff;
				int k = 0;
				int index = 0;
				__attribute__((unused)) UINT32 regVal = 0;

				// check input table size
				if(pstParams->odLut.sizeNum != (OVI_HW_M23_INPUT_LOD_TOTAL_SIZENUM*sizeof(UINT16)))
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_M23_INPUT_LOD_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				OVI_TCON_M23_RdFL(tcon_lodc_table_addr);
				OVI_TCON_M23_Wr01(tcon_lodc_table_addr, lut_addr, 0x0);
				OVI_TCON_M23_WrFL(tcon_lodc_table_addr);
				OVI_TCON_M23_RdFL(tcon_lodc_table_index);
				OVI_TCON_M23_Wr01(tcon_lodc_table_index, lut_index, 0x0);
				OVI_TCON_M23_WrFL(tcon_lodc_table_index);

				for (k = 0; k < 10; k++)
				{
					regVal = k;
					OVI_TCON_M23_RdFL(tcon_lodc_table_addr);
					OVI_TCON_M23_Wr01(tcon_lodc_table_addr, lut_addr, 0x0);
					OVI_TCON_M23_WrFL(tcon_lodc_table_addr);
					OVI_TCON_M23_RdFL(tcon_lodc_table_index);
					OVI_TCON_M23_Wr01(tcon_lodc_table_index, lut_index, regVal);
					OVI_TCON_M23_WrFL(tcon_lodc_table_index);

					for (i = 0; i < 19*19; i++)
					{
						buff = readw_relaxed(&regAddr1[i]);
						buff = buff & 0xFFF;
						put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index++]));
					}
				}

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg0);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg0, lodc_lut_index1, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg0, lodc_lut_index2, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg1);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg1, lodc_lut_index3, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg1, lodc_lut_index4, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg2);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg2, lodc_lut_index5, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg2, lodc_lut_index6, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg3);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg3, lodc_lut_index7, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg3, lodc_lut_index8, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg4);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg4, lodc_lut_index9, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg4, lodc_lut_index10, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg5);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg5, lodc_lut_index11, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg5, lodc_lut_index12, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg6);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg6, lodc_lut_index13, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg6, lodc_lut_index14, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg7);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg7, lodc_lut_index15, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg7, lodc_lut_index16, buff);
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

				OVI_TCON_M23_RdFL(tcon_lodc_lut_idx_reg8);
				OVI_TCON_M23_Rd01(tcon_lodc_lut_idx_reg8, lodc_lut_index17, buff);
				buff = buff >> 4;
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index]));
				put_user(buff, &(((UINT16 *)pstParams->odLut.pData)[index+OVI_HW_M23_INPUT_LOD_INDEX_SIZENUM]));
				index++;

			}

		}
	} while(0);
	
	if(u8odLutData != NULL)
		vfree(u8odLutData);
	if(u16lodLutData != NULL)
		vfree(u16lodLutData);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);
	#endif
	return ret;
}

int OVI_HW_M23_SetPodLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) int i;
	__attribute__((unused)) volatile UINT32 *regAddr1 = NULL;
	__attribute__((unused)) UINT8 *u8odLutData = NULL;
	__attribute__((unused)) UINT16 *u16lodLutData = NULL;
	__attribute__((unused)) UINT32 odLutSizeNum;
	#if 1
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
			odLutSizeNum = pstParams->odLut.sizeNum;

			if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_sts);
				OVI_TCON_M23_Wr01(tcon_sts, pix2_lock, 0x1);
				OVI_TCON_M23_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_sts);
				OVI_TCON_M23_Wr01(tcon_sts, pix2_lock, 0x0);
				OVI_TCON_M23_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				// check input table size
				if(odLutSizeNum != OVI_HW_M23_INPUT_POD2_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_M23_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}

			if (pstParams->eMode != LX_OVI_TCON_LINEOD_PCID)
			{
				u8odLutData = (UINT8 *)vmalloc(odLutSizeNum);
				if(u8odLutData == NULL)
				{
					OVI_ERROR("[OVI] memory allocate failed! \n");
					ret = RET_ERROR;
					break;
				}

				ret = copy_from_user(u8odLutData, (void __user *)pstParams->odLut.pData, odLutSizeNum);
				if(ret)
				{
					OVI_ERROR("[OVI] Error in copying from user! \n");
					ret = RET_ERROR;
					break;
				}
			}

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD) // CAD (LGD)
			{
				for(i=0; i<OVI_HW_M23_INPUT_POD2_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}
			}

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD) // CAD (LGD)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, mem_sel, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);

				OVI_TCON_M23_RdFL(tcon_cad_reg_main);
				OVI_TCON_M23_Wr01(tcon_cad_reg_main, cad_on, 0x1);
				OVI_TCON_M23_WrFL(tcon_cad_reg_main);
			}
		}
		else
		{

			if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD) //cad lgd
			{
				UINT8 buff;

				// check input table size
				if(pstParams->odLut.sizeNum != OVI_HW_M23_INPUT_POD2_SIZENUM)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_M23_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				for (i = 0; i < OVI_HW_M23_INPUT_POD2_SIZENUM; i++)
				{
					buff = readb_relaxed(&regAddr1[i]);
					put_user(buff, &(((UINT8 *)pstParams->odLut.pData)[i]));
				}
			}
		}
	} while(0);
	
	if(u8odLutData != NULL)
		vfree(u8odLutData);
	if(u16lodLutData != NULL)
		vfree(u16lodLutData);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);
	#endif
	return ret;
}




int OVI_HW_M23_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	#if 1 // 
	do {
		// check TCON base address
		if (bParam && !(_gOviHwM23Info.tconBaseAddress))
		{
			OVI_ERROR("[OVI] TCON base address is Null!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_M23_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x1);

			OVI_TCON_M23_RdFL(tcon_odc_opt2);
			OVI_TCON_M23_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
			OVI_TCON_M23_WrFL(tcon_odc_opt2);

		}
		else
			OVI_TCON_M23_Wr01(tcon_control, odc_en, 0x0);
		OVI_TCON_M23_WrFL(tcon_control);
	} while (0);
	#endif
	return ret;
}

int OVI_HW_M23_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_M23_RdFL(led_wb2p_en);
		if(bParam)
			DPE_LED_M23_Wr01(led_wb2p_en, wb2p_en, 0x1);
		else
			DPE_LED_M23_Wr01(led_wb2p_en, wb2p_en, 0x0);
		DPE_LED_M23_WrFL(led_wb2p_en);
	} while (0);

	return ret;
}

int OVI_HW_M23_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_M23_RdFL(led_dpg_en);
		if(bParam)
			DPE_LED_M23_Wr01(led_dpg_en, dpg_en, 0x1);
		else
			DPE_LED_M23_Wr01(led_dpg_en, dpg_en, 0x0);
		DPE_LED_M23_WrFL(led_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_M23_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M23_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_M23_Wr01(tcon_control, pre_dither_en, 0x1);
			OVI_TCON_M23_Wr01(tcon_control, post_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_M23_Wr01(tcon_control, pre_dither_en, 0x0);
			OVI_TCON_M23_Wr01(tcon_control, post_dither_en, 0x0);
		}
		OVI_TCON_M23_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_M23_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		/* Do Nothing */
	} while(0);

	return ret;
}

int OVI_HW_M23_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;

	do {
		//Dither Enable
		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Wr01(tcon_control, pre_dither_en, 0x1);
		OVI_TCON_M23_Wr01(tcon_control, post_dither_en, 0x1);
		OVI_TCON_M23_WrFL(tcon_control);
		
		OVI_TCON_M23_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_M23_Wr01(tcon_dither_carry, pre_dither_sel, 0x4 | 0x0);
				OVI_TCON_M23_Wr01(tcon_dither_carry, post_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_M23_Wr01(tcon_dither_carry, pre_dither_sel, 0x4 | 0x1);
				OVI_TCON_M23_Wr01(tcon_dither_carry, post_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_M23_Wr01(tcon_dither_carry, pre_dither_sel, 0x4 | 0x2);
				OVI_TCON_M23_Wr01(tcon_dither_carry, post_dither_sel, 0x2);
				break;
		}
		OVI_TCON_M23_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_M23_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;
	UINT32 rangeOpt;

	rangeOpt = (gain >> 31) & 0x1;
	gain &= (~(1 << 31));

	if ((rangeOpt == 0)
		|| ((rangeOpt == 1) && (gain >= 192)))
	{
		temp = 10000 + (gain - 192) * OVI_HW_M23_WB_GAIN_STEP1;
	}
	else
	{
		temp = 10000 + (gain - 192) * OVI_HW_M23_WB_GAIN_STEP2;
	}
	ret_gain = (temp * OVI_HW_M23_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_M23_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_M23_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_M23_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
{
	int ret = RET_OK;
	UINT32 r_gain, g_gain, b_gain;
	SINT16 rOffset, gOffset, bOffset;
	
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
#if 0
			if (_gOviHwM23Info.pVx1ChipInfoVMapAddr != NULL)		
			{
				UINT32 dataSize;
				int i;
#ifdef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_M23_VX1_CHIP_INFO_APB_CNT0_T count;
#endif
				
				r_gain = _OVI_M23_GetGain(pstParams->r_gain);
				g_gain = _OVI_M23_GetGain(pstParams->g_gain);
				b_gain = _OVI_M23_GetGain(pstParams->b_gain);

				rOffset = _OVI_M23_GetOffset(pstParams->r_offset);
				gOffset = _OVI_M23_GetOffset(pstParams->g_offset);
				bOffset = _OVI_M23_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				for (i=0; i<BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
				{
					dataSize = 0;
					
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbEnRegAddr = _B2L32(OVI_HW_F22_REG_WB_EN); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbEnVal = _B2L32(0x1); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbRGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_R_GAIN); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbRGainVal = _B2L32(r_gain); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbROffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_R_OFFSET); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbROffsetVal = _B2L32(rOffset); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbGGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_G_GAIN); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbGGainVal = _B2L32(g_gain); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_G_OFFSET); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetVal = _B2L32(gOffset); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbBGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_B_GAIN); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbBGainVal = _B2L32(b_gain); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_B_OFFSET); dataSize++;
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetVal = _B2L32(bOffset); dataSize++;
					dataSize = sizeof(UINT32) * dataSize;

#ifndef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
#endif

					if (dataSize != OVI_HW_M23_VX1_CHIP_INFO_COLOR_TEMP_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();

#ifdef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
					count.u32Data = _B2L32(_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data);

					if (count.colorTemp == 0xF)
					{
						count.colorTemp = 1;
					}
					else
					{
						count.colorTemp++;
					}

					_gOviHwM23Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
#else
					_gOviHwM23Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32((0x0A000000|OVI_HW_M23_VX1_CHIP_INFO_COLOR_TEMP_SIZE));
#endif

					wmb();
					_OVI_M23_UpdateChipInfoHeader();
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				// W/B Enable
				DPE_LED_M23_RdFL(led_wb2p_en);
				DPE_LED_M23_Wr01(led_wb2p_en, wb2p_en, 0x1);
				DPE_LED_M23_WrFL(led_wb2p_en);
			
				r_gain = _OVI_M23_GetGain(pstParams->r_gain);
				g_gain = _OVI_M23_GetGain(pstParams->g_gain);
				b_gain = _OVI_M23_GetGain(pstParams->b_gain);

				rOffset = _OVI_M23_GetOffset(pstParams->r_offset);
				gOffset = _OVI_M23_GetOffset(pstParams->g_offset);
				bOffset = _OVI_M23_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
					&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
				{
					return RET_OK;
				}

				// Set red gain
				DPE_LED_M23_RdFL(led_wb2p_r_gain);
				DPE_LED_M23_Wr(led_wb2p_r_gain, r_gain);
				DPE_LED_M23_WrFL(led_wb2p_r_gain);

				// Set red offset
				DPE_LED_M23_RdFL(led_wb2p_r_offset);
				DPE_LED_M23_Wr(led_wb2p_r_offset, rOffset);
				DPE_LED_M23_WrFL(led_wb2p_r_offset);

				// Set green gain
				DPE_LED_M23_RdFL(led_wb2p_g_gain);
				DPE_LED_M23_Wr(led_wb2p_g_gain, g_gain);
				DPE_LED_M23_WrFL(led_wb2p_g_gain);

				// Set green offset
				DPE_LED_M23_RdFL(led_wb2p_g_offset);
				DPE_LED_M23_Wr(led_wb2p_g_offset, gOffset);
				DPE_LED_M23_WrFL(led_wb2p_g_offset);

				// Set blue gain
				DPE_LED_M23_RdFL(led_wb2p_b_gain);
				DPE_LED_M23_Wr(led_wb2p_b_gain, b_gain);
				DPE_LED_M23_WrFL(led_wb2p_b_gain);

				// Set blue offset
				DPE_LED_M23_RdFL(led_wb2p_b_offset);
				DPE_LED_M23_Wr(led_wb2p_b_offset, bOffset);
				DPE_LED_M23_WrFL(led_wb2p_b_offset);

				_gPrevRedGain = r_gain;
				_gPrevGreenGain = g_gain;
				_gPrevBlueGain = b_gain;
				_gPrevRedOffset = rOffset;
				_gPrevGreenOffset = gOffset;
				_gPrevBlueOffset = bOffset;
#if 0
			}		
#endif
		}
		else
		{
			*pstParams = _gColTemp;
		}

	} while(0);

	return ret;
}

int OVI_HW_M23_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *rGammaTable = NULL;
	UINT32 *gGammaTable = NULL;
	UINT32 *bGammaTable = NULL;
	__attribute__((unused)) UINT32 regField;
	int i;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		cancel_delayed_work_sync(&_gOviHwM23Info.delayedRGBGamma.dlyWork);
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutR);
			_gOviHwM23Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutG);
			_gOviHwM23Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwM23Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwM23Info.delayedRGBGamma.pu32LutB);
			_gOviHwM23Info.delayedRGBGamma.pu32LutB = NULL;
		}

		if (!pstParams->bIsGet)
		{
			if((pstParams->rGammaLut.sizeNum != OVI_HW_M23_GAMMA_TABLE_SIZENUM)
			|| (pstParams->gGammaLut.sizeNum != OVI_HW_M23_GAMMA_TABLE_SIZENUM)
			|| (pstParams->bGammaLut.sizeNum != OVI_HW_M23_GAMMA_TABLE_SIZENUM))
			{
				OVI_ERROR("[OVI] Gamma table size is not correct! \n");
				ret = RET_ERROR;
				break;
			}

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user((void *)rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user((void *)gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user((void *)bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			memcpy((void *)&_gOviHwM23Info.rGamma, (void *)rGammaTable, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			memcpy((void *)&_gOviHwM23Info.gGamma, (void *)gGammaTable, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			memcpy((void *)&_gOviHwM23Info.bGamma, (void *)bGammaTable, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));

#if 0
			if (_gOviHwM23Info.pVx1ChipInfoVMapAddr != NULL)
			{
				UINT32 dataSize;
#ifdef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_M23_VX1_CHIP_INFO_APB_CNT0_T count;
#else
				UINT32 ctrlSize;
#endif
				int idx;

				for (idx=0; idx<BE_OVI_HW_M23_VX1_CHIP_INFO_MEM_BUFF_NUM; idx++)
				{
					dataSize = 0;
#ifndef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
					ctrlSize= 0;
#endif

					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.wDataRegAddr = _B2L32(OVI_HW_F22_REG_DPG_LUT_WDATA); dataSize++;
					/* Setting Red Gamma Table */
					for (i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.wdata[i] = _B2L32(((0x4<<28)|(i<<16)|(rGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_M23_GAMMA_TABLE_SIZENUM;
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.wdata[i+OVI_HW_M23_GAMMA_TABLE_SIZENUM] = _B2L32(((0x2<<28)|(i<<16)|(gGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_M23_GAMMA_TABLE_SIZENUM;
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.wdata[i+(OVI_HW_M23_GAMMA_TABLE_SIZENUM*2)] = _B2L32(((0x1<<28)|(i<<16)|(bGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_M23_GAMMA_TABLE_SIZENUM;
					dataSize = sizeof(UINT32) * dataSize;

#ifdef BE_OVI_HW_M23_USE_VX1_CHIP_INFO_APB_SLAVE
					if (dataSize != OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();
					
					count.u32Data = _B2L32(_gOviHwM23Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data);
					
					if (count.dpg == 0xF)
					{
						count.dpg = 1;
					}
					else
					{
						count.dpg++;
					}

					_gOviHwM23Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
					wmb();
#else
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.dataHwCrc = 0xFFFFFFFF;

					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.wrDoneRegAddr = _B2L32(OVI_HW_F22_REG_DPG_LUT_WR_DONE); ctrlSize++;
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.wrDoneVal = _B2L32(0x1); ctrlSize++;
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.enRegAddr = _B2L32(OVI_HW_F22_REG_DPG_EN); ctrlSize++;
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.enVal = _B2L32(0x1); ctrlSize++;
					ctrlSize = sizeof(UINT32) * ctrlSize;
					
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.ctrlHwCrc = 0xFFFFFFFF;

					if ((dataSize != OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE)
						|| (ctrlSize != OVI_HW_M23_VX1_CHIP_INFO_DPG_CTRL_SIZE))
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();
					
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.dataHwHdr = _B2L32((0x0A010000|OVI_HW_M23_VX1_CHIP_INFO_DPG_DATA_SIZE));
					wmb();
					_gOviHwM23Info.pVx1ChipInfo[idx]->dpg.ctrlHwHdr = _B2L32((0x0A000000|OVI_HW_M23_VX1_CHIP_INFO_DPG_CTRL_SIZE));
					wmb();
					_OVI_M23_UpdateChipInfoHeader();
#endif
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
				DPE_LED_M23_Rd01(led_dpg_lut_wr_done, dpg_lut_cpy_status, regField);

				if (regField)
				{
					_gOviHwM23Info.delayedRGBGamma.pu32LutR = rGammaTable;
					_gOviHwM23Info.delayedRGBGamma.pu32LutG = gGammaTable;
					_gOviHwM23Info.delayedRGBGamma.pu32LutB = bGammaTable;
					
					schedule_delayed_work(&_gOviHwM23Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
				}
				else
				{
					DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
					DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_wstart_o, 0x1);
					DPE_LED_M23_WrFL(led_dpg_lut_wr_done);

					DPE_LED_M23_RdFL(led_dpg_lut_wdata);

					/* Setting Red Gamma Table */
					for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
						DPE_LED_M23_WrFL(led_dpg_lut_wdata);
					}
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
						DPE_LED_M23_WrFL(led_dpg_lut_wdata);
					}
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_M23_Wr01(led_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
						DPE_LED_M23_WrFL(led_dpg_lut_wdata);
					}

					DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
					DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_wdone_o, 0x1);
					DPE_LED_M23_WrFL(led_dpg_lut_wr_done);

					DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
					DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_lut_update, 0x1);
					DPE_LED_M23_WrFL(led_dpg_lut_wr_done);

					// Gamma Enable
					DPE_LED_M23_RdFL(led_dpg_en);
					DPE_LED_M23_Wr01(led_dpg_en, dpg_en, 0x1);
					DPE_LED_M23_WrFL(led_dpg_en);
				}
#if 0
			}
#endif
		}
		else
		{
#if 0
			rGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			#if 0
			DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
			DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_M23_WrFL(led_dpg_lut_wr_done);
			#endif
			OS_UsecDelay(25000);

			/* Setting Red Gamma Table */
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M23_RdFL(led_dpg_lut_rdata);
				DPE_LED_M23_Wr01(led_dpg_lut_rdata, dpg_re, 0x4);
				DPE_LED_M23_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_M23_WrFL(led_dpg_lut_rdata);
				DPE_LED_M23_RdFL(led_dpg_lut_rdata);
				DPE_LED_M23_Rd01(led_dpg_lut_rdata, dpg_rdata, rGammaTable[i]);
			}
			/* Setting Green Gamma Table */
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M23_RdFL(led_dpg_lut_rdata);
				DPE_LED_M23_Wr01(led_dpg_lut_rdata, dpg_re, 0x2);
				DPE_LED_M23_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_M23_WrFL(led_dpg_lut_rdata);
				DPE_LED_M23_RdFL(led_dpg_lut_rdata);
				DPE_LED_M23_Rd01(led_dpg_lut_rdata, dpg_rdata, gGammaTable[i]);
			}
			/* Setting Blue Gamma Table */
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M23_RdFL(led_dpg_lut_rdata);
				DPE_LED_M23_Wr01(led_dpg_lut_rdata, dpg_re, 0x1);
				DPE_LED_M23_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_M23_WrFL(led_dpg_lut_rdata);
				DPE_LED_M23_RdFL(led_dpg_lut_rdata);
				DPE_LED_M23_Rd01(led_dpg_lut_rdata, dpg_rdata, bGammaTable[i]);
			}

			#if 0
			DPE_LED_M23_RdFL(led_dpg_lut_wr_done);
			DPE_LED_M23_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_M23_WrFL(led_dpg_lut_wr_done);
			#endif
#endif

			pstParams->rGammaLut.sizeNum = OVI_HW_M23_GAMMA_TABLE_SIZENUM;
			pstParams->gGammaLut.sizeNum = OVI_HW_M23_GAMMA_TABLE_SIZENUM;
			pstParams->bGammaLut.sizeNum = OVI_HW_M23_GAMMA_TABLE_SIZENUM;

			ret = copy_to_user(pstParams->rGammaLut.pData, (void __user *)&_gOviHwM23Info.rGamma, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->gGammaLut.pData, (void __user *)&_gOviHwM23Info.gGamma, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->bGammaLut.pData, (void __user *)&_gOviHwM23Info.bGamma, OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

		}
	} while(0);

	if((rGammaTable != NULL) && (_gOviHwM23Info.delayedRGBGamma.pu32LutR == NULL))
		vfree((const void *)rGammaTable);
	if((gGammaTable != NULL) && (_gOviHwM23Info.delayedRGBGamma.pu32LutG == NULL))
		vfree((const void *)gGammaTable);
	if((bGammaTable != NULL) && (_gOviHwM23Info.delayedRGBGamma.pu32LutB == NULL))
		vfree((const void *)bGammaTable);

	return ret;
}

int OVI_HW_M23_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams)
{
	int ret = RET_OK;
	volatile UINT32 *rGammaTable = NULL;
	volatile UINT32 *gGammaTable = NULL;
	volatile UINT32 *bGammaTable = NULL;
	volatile UINT32 *reg_rstart = NULL;
	volatile UINT32 *reg_gstart = NULL;
	volatile UINT32 *reg_bstart = NULL;
	volatile int i;
	volatile UINT32 preVal = 0;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if((pstParams->rGammaLut.sizeNum != OVI_HW_M23_GAMMA_TABLE_SIZENUM)
		|| (pstParams->gGammaLut.sizeNum != OVI_HW_M23_GAMMA_TABLE_SIZENUM)
		|| (pstParams->bGammaLut.sizeNum != OVI_HW_M23_GAMMA_TABLE_SIZENUM))
		{
			OVI_ERROR("[OVI] Gamma table size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		//OVI_TCON_M23_RdFL(tcon_control);
		//OVI_TCON_M23_Wr01(tcon_control, dga_en, 0x0);
		//OVI_TCON_M23_WrFL(tcon_control);

		rGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		gGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		bGammaTable = (UINT32 *)vmalloc(OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		/* Setting Red Gamma Table */
		ret = copy_from_user((void *)rGammaTable, (void __user *)pstParams->rGammaLut.pData,
							OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		/* Setting Green Gamma Table */
		ret = copy_from_user((void *)gGammaTable, (void __user *)pstParams->gGammaLut.pData,
							OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		/* Setting Blue Gamma Table */
		ret = copy_from_user((void *)bGammaTable, (void __user *)pstParams->bGammaLut.pData,
							OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		reg_rstart = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE+offsetof(OVI_TCON_REG_M23A0_T, tcon_dga_low_rs),
											OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		reg_gstart = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE+offsetof(OVI_TCON_REG_M23A0_T, tcon_dga_low_gs),
											OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		reg_bstart = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE+offsetof(OVI_TCON_REG_M23A0_T, tcon_dga_low_bs),
											OVI_HW_M23_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_rstart == NULL || reg_gstart == NULL || reg_bstart == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		if (_gOviHwM23Info.useSpecialDgaFlag == 0x1)
		{
			// gamma table upload, change table not to write special dga
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_up_mode, 0x0);	// dga_up_mode : 0 -> sync update
			OVI_TCON_M23_WrFL(tcon_dga_mode);
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
			OVI_TCON_M23_WrFL(tcon_dga_mode);

			OS_MsecSleep(17);

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > rGammaTable[i])
				{
					reg_rstart[i] = preVal << 3;
				}
				else
				{
					reg_rstart[i] = rGammaTable[i] << 3;
					preVal = rGammaTable[i];
				}
			}

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > gGammaTable[i])
				{
					reg_gstart[i] = preVal << 3;
				}
				else
				{
					reg_gstart[i] = gGammaTable[i] << 3;
					preVal = gGammaTable[i];
				}
			}

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > bGammaTable[i])
				{
					reg_bstart[i] = preVal << 3;
				}
				else
				{
					reg_bstart[i] = bGammaTable[i] << 3;
					preVal = bGammaTable[i];
				}
			}

			// gamma table upload
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_up_mode, 0x0);	// dga_up_mode : 0 -> sync update
			OVI_TCON_M23_WrFL(tcon_dga_mode);
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
			OVI_TCON_M23_WrFL(tcon_dga_mode);
		}
		else
		{
			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > rGammaTable[i])
				{
					reg_rstart[i] = preVal << 3;
				}
				else
				{
					reg_rstart[i] = rGammaTable[i] << 3;
					preVal = rGammaTable[i];
				}
			}

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > gGammaTable[i])
				{
					reg_gstart[i] = preVal << 3;
				}
				else
				{
					reg_gstart[i] = gGammaTable[i] << 3;
					preVal = gGammaTable[i];
				}
			}

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > bGammaTable[i])
				{
					reg_bstart[i] = preVal << 3;
				}
				else
				{
					reg_bstart[i] = bGammaTable[i] << 3;
					preVal = bGammaTable[i];
				}
			}

			// gamma table upload
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_up_mode, 0x0);	// dga_up_mode : 0 -> sync update
			OVI_TCON_M23_WrFL(tcon_dga_mode);
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
			OVI_TCON_M23_WrFL(tcon_dga_mode);

			OS_MsecSleep(17);

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > rGammaTable[i])
				{
					reg_rstart[i] = preVal << 3;
				}
				else
				{
					reg_rstart[i] = rGammaTable[i] << 3;
					preVal = rGammaTable[i];
				}
			}

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > gGammaTable[i])
				{
					reg_gstart[i] = preVal << 3;
				}
				else
				{
					reg_gstart[i] = gGammaTable[i] << 3;
					preVal = gGammaTable[i];
				}
			}

			preVal = 0;
			for(i=0; i<OVI_HW_M23_GAMMA_TABLE_SIZENUM; i++)
			{
				if (preVal > bGammaTable[i])
				{
					reg_bstart[i] = preVal << 3;
				}
				else
				{
					reg_bstart[i] = bGammaTable[i] << 3;
					preVal = bGammaTable[i];
				}
			}

			// gamma table upload
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_up_mode, 0x0);	// dga_up_mode : 0 -> sync update
			OVI_TCON_M23_WrFL(tcon_dga_mode);
			OVI_TCON_M23_RdFL(tcon_dga_mode);
			OVI_TCON_M23_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
			OVI_TCON_M23_WrFL(tcon_dga_mode);
		}

		iounmap((void *)reg_rstart); reg_rstart = NULL;
		iounmap((void *)reg_gstart); reg_gstart = NULL;
		iounmap((void *)reg_bstart); reg_bstart = NULL;

		// Gamma Enable
		if (!_gOviHwM23Info.dgaBypassEn)
		{
			OVI_TCON_M23_RdFL(tcon_control);
			OVI_TCON_M23_Wr01(tcon_control, dga_en, 0x1);
			OVI_TCON_M23_WrFL(tcon_control);
		}
		_gOviHwM23Info.dgaEn = TRUE;
	} while(0);

	if (rGammaTable != NULL)
		vfree((const void *)rGammaTable);
	if (gGammaTable != NULL)
		vfree((const void *)gGammaTable);
	if (bGammaTable != NULL)
		vfree((const void *)bGammaTable);

	if (reg_rstart != NULL)
		iounmap((void *)reg_rstart);
	if (reg_gstart != NULL)
		iounmap((void *)reg_gstart);
	if (reg_bstart != NULL)
		iounmap((void *)reg_bstart);
	
	return ret;
}

int OVI_HW_M23_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 u32odcAddr=0;
	__attribute__((unused)) volatile UINT32 *pMappedAddr = NULL;
	#if 0 // not used
	do {
		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_FRAMEOD:
				u32odcAddr = OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_odc_start_2d);
				break;
			case LX_OVI_TCON_LINEOD_PCID:
				u32odcAddr = OVI_TCON_LODC_REG_M23A0_BASE + offsetof(OVI_TCON_LODC_REG_M23A0_T, tcon_lodc_start);
				break;
			default:
				break;
		}

		pstParams->odLut.sizeNum = OVI_HW_M23_INPUT_OD_SIZENUM;

		pMappedAddr = (volatile UINT32 *)ioremap(u32odcAddr, sizeof(UINT32)*OVI_HW_M23_INPUT_OD_SIZENUM);
		if(pMappedAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			break;
		}

		ret = copy_to_user((void __user *)pstParams->odLut.pData, (void*)pMappedAddr, sizeof(UINT32)*OVI_HW_M23_INPUT_OD_SIZENUM);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying to user! \n");
			ret = RET_ERROR;
			break;
		}
	}while(0);

	if(pMappedAddr != NULL)
		iounmap((void *)pMappedAddr);
	#endif
	return ret;
}

int OVI_HW_M23_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regField;
	#if 1 // 
	do {

		if ((pstParams == NULL) || (_gOviHwM23Info.tscicWritingFlag == TRUE))
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! or already running!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->u32TscicSize == 0) // TSCIC disable for debug
		{
			// [NOTE] FCIC function enable/disable : 0xC90750A8 [3:0] - 0x0/0xC
			// FCIC disable setting
			OVI_TCON_M23_RdFL(tcon_control);
			OVI_TCON_M23_Wr01(tcon_control, fcic_en, 0x0);
			OVI_TCON_M23_WrFL(tcon_control);

			// FCIC Clock gating ON
			//CTOP_CTRL_M23Ax_RdFL(DPE_SYN, crg_dpe00);
			//CTOP_CTRL_M23Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 1);
			//CTOP_CTRL_M23Ax_WrFL(DPE_SYN, crg_dpe00);
			//OVI_REG_RD(0xC930F000,regField);
			//regField = (regField | 0x00000040);
			//OVI_REG_WR(0xC930F000,regField);

			return RET_OK;
		}

		// check input table size
		if ((pstParams->u32Ctrlsize != OVI_HW_M23_INPUT_TSCIC_CTRL_SIZENUM) || (pstParams->pu8ControlTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL! %d\n",pstParams->u32Ctrlsize);
			ret = RET_ERROR;
			break;
		}

		if ((pstParams->u32TscicSize != OVI_HW_M23_INPUT_TSCIC_DATA_SIZE) || (pstParams->pu32TscicTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL! %d\n",pstParams->u32TscicSize);
			ret = RET_ERROR;
			break;
		}

		_gOviHwM23Info.tscicSize = pstParams->u32TscicSize;
		_gOviHwM23Info.tscicCtrlSizeNum = pstParams->u32Ctrlsize;

		_gOviHwM23Info.tscicU8CtrlData = (UINT8 *)vmalloc(_gOviHwM23Info.tscicCtrlSizeNum);
		if(_gOviHwM23Info.tscicU8CtrlData == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(_gOviHwM23Info.tscicU8CtrlData, (void __user *)pstParams->pu8ControlTbl, _gOviHwM23Info.tscicCtrlSizeNum);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwM23Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM23Info.tscicU8CtrlData);
				_gOviHwM23Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		_gOviHwM23Info.tscicU32Tbl = (UINT32 *)vmalloc(_gOviHwM23Info.tscicSize);
		if(_gOviHwM23Info.tscicU32Tbl == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			if(_gOviHwM23Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM23Info.tscicU8CtrlData);
				_gOviHwM23Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		ret = copy_from_user(_gOviHwM23Info.tscicU32Tbl, (void __user *)pstParams->pu32TscicTbl, _gOviHwM23Info.tscicSize);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwM23Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM23Info.tscicU8CtrlData);
				_gOviHwM23Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwM23Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwM23Info.tscicU32Tbl);
				_gOviHwM23Info.tscicU32Tbl = NULL;
			}
			break;
		}

		// FCIC Clock gating OFF
		//CTOP_CTRL_M23Ax_RdFL(DPE_SYN, crg_dpe00);
		//CTOP_CTRL_M23Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 0);
		//CTOP_CTRL_M23Ax_WrFL(DPE_SYN, crg_dpe00);
		//OVI_REG_RD(0xC930F000,regField);
		//regField = (regField & 0xFFFFFFBF);
		//OVI_REG_WR(0xC930F000,regField);

		// FCIC enable setting
		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Wr01(tcon_control, fcic_en, 0x1);
		OVI_TCON_M23_WrFL(tcon_control);

		_gOviHwM23Info.tscicThread = kthread_run(OVI_M23_TscicWriteThread, NULL, "ovi_tscic");
		if (IS_ERR(_gOviHwM23Info.tscicThread))
		{
			OVI_ERROR("[OVI] Error in starting thread! \n");
			ret = RET_ERROR;
			if(_gOviHwM23Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM23Info.tscicU8CtrlData);
				_gOviHwM23Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwM23Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwM23Info.tscicU32Tbl);
				_gOviHwM23Info.tscicU32Tbl = NULL;
			}
			break;
		}
	} while(0);
	#endif
	return ret;
}

int OVI_HW_M23_SetDemura(LX_OVI_TCON_DEMURA_T *pstParams)
{
	int ret = RET_OK;

	__attribute__((unused)) UINT32 regField;
	#if 1 //
	do {

		if ((pstParams == NULL) || (_gOviHwM23Info.demuraWritingFlag == TRUE))
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! or already running!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{

			if (pstParams->bEnable == FALSE)
			{
				OVI_TCON_M23_RdFL(tcon_control);
				OVI_TCON_M23_Wr01(tcon_control, demu_en, 0x0);
				OVI_TCON_M23_WrFL(tcon_control);

				return RET_OK;
			}

			// check input table size
			if ((pstParams->u32ConfigSize > OVI_HW_M23_INPUT_DEMURA_CFG_DATA_SIZE) || (pstParams->pu8Config == NULL))
			{
				OVI_ERROR("[OVI] Input DEMURA Config size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			if ((pstParams->u32DataSize > OVI_HW_M23_DEMURA_MEM_SIZE) || (pstParams->pu8Data == NULL))
			{
				OVI_ERROR("[OVI] Input DEMURA Table size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			_gOviHwM23Info.demuraSize = pstParams->u32DataSize;
			_gOviHwM23Info.demuraConfigSize = pstParams->u32ConfigSize;

			_gOviHwM23Info.demuraU8ConfigData = (UINT8 *)vmalloc(_gOviHwM23Info.demuraConfigSize);
			if(_gOviHwM23Info.demuraU8ConfigData == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(_gOviHwM23Info.demuraU8ConfigData, (void __user *)pstParams->pu8Config, _gOviHwM23Info.demuraConfigSize);
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				if(_gOviHwM23Info.demuraU8ConfigData != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8ConfigData);
					_gOviHwM23Info.demuraU8ConfigData = NULL;
				}
				break;
			}

			_gOviHwM23Info.demuraU8Tbl = (UINT8 *)vmalloc(_gOviHwM23Info.demuraSize);
			if(_gOviHwM23Info.demuraU8Tbl == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				if(_gOviHwM23Info.demuraU8ConfigData != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8ConfigData);
					_gOviHwM23Info.demuraU8ConfigData = NULL;
				}
				break;
			}

			ret = copy_from_user(_gOviHwM23Info.demuraU8Tbl, (void __user *)pstParams->pu8Data, _gOviHwM23Info.demuraSize);
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				if(_gOviHwM23Info.demuraU8ConfigData != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8ConfigData);
					_gOviHwM23Info.demuraU8ConfigData = NULL;
				}
				if(_gOviHwM23Info.demuraU8Tbl != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8Tbl);
					_gOviHwM23Info.demuraU8Tbl = NULL;
				}
				break;
			}

			_gOviHwM23Info.demuraThread = kthread_run(OVI_M23_DemuraWriteThread, NULL, "ovi_demura");
			if (IS_ERR(_gOviHwM23Info.demuraThread))
			{
				OVI_ERROR("[OVI] Error in starting thread! \n");
				ret = RET_ERROR;
				if(_gOviHwM23Info.demuraU8ConfigData != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8ConfigData);
					_gOviHwM23Info.demuraU8ConfigData = NULL;
				}
				if(_gOviHwM23Info.demuraU8Tbl != NULL)
				{
					vfree(_gOviHwM23Info.demuraU8Tbl);
					_gOviHwM23Info.demuraU8Tbl = NULL;
				}
				break;
			}

		}
		else
		{
			volatile UINT32 *regAddr = NULL;
			volatile __attribute__((unused)) UINT32 regVal = 0;
			char *pAddr = NULL;
			char *tmp = NULL;
			UINT8 buff[OVI_HW_M23_INPUT_DEMURA_CFG_DATA_SIZE];
			UINT32 i;

			if (!gpOviTconMem)
			{
				OVI_ERROR("[OVI] TCON memory is not configured!\n");
				OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
			}

			if ((!gpOviTconMem->base)
				|| (!gpOviTconMem->size))
			{
				OVI_ERROR("[WARN][OVI] TCON memory is not configured!\n");
				OVI_BREAK_WRONG(gpOviTconMem->base);
			}

			OVI_TCON_M23_RdFL(tcon_base_address1);
			OVI_TCON_M23_Rd01(tcon_base_address1, demura_base_address, regVal);

			if (regVal != _gOviHwM23Info.tconBaseAddress + OVI_HW_M23_DEMURA_MEM_OFFSET)
			{
				OVI_ERROR("[WARN][OVI] demura addr setting error!\n");
				OVI_BREAK_WRONG(regVal);
			}

			// check input table size
			if ((pstParams->u32ConfigSize > OVI_HW_M23_INPUT_DEMURA_CFG_DATA_SIZE) || (pstParams->pu8Config == NULL))
			{
				OVI_ERROR("[OVI] Input DEMURA Config size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			if ((pstParams->u32DataSize > OVI_HW_M23_DEMURA_MEM_SIZE) || (pstParams->pu8Data == NULL))
			{
				OVI_ERROR("[OVI] Input DEMURA Table size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_demura_reg_start),
											pstParams->u32ConfigSize*sizeof(UINT32));
			if (regAddr == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}

			for (i = 0; i < pstParams->u32ConfigSize; i++)
			{
				buff[i] = readb_relaxed(&regAddr[i]);
			}

			ret = copy_to_user(pstParams->pu8Config, (void __user *)&buff[0], pstParams->u32ConfigSize);
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				iounmap((void *)regAddr);
				regAddr = NULL;
				ret = RET_ERROR;
				break;
			}

			iounmap((void *)regAddr);
			regAddr = NULL;

			pAddr = (char *)vmap_phys(gpOviTconMem->base + OVI_HW_M23_DEMURA_MEM_OFFSET, OVI_HW_M23_DEMURA_MEM_SIZE);
			if(pAddr == NULL)
			{
				OVI_ERROR("[OVI] Error in vmap_phys! \n");
				ret = RET_ERROR;
				break;
			}

			tmp = (char *)vmalloc(pstParams->u32DataSize);
			if(tmp == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				vunmap_phys(pAddr);
				pAddr = NULL;
				ret = RET_ERROR;
				break;
			}

			memcpy((void *)tmp, (void *)pAddr, pstParams->u32DataSize);
			_ConvertEndian32((UINT32 *)tmp, pstParams->u32DataSize);

			ret = copy_to_user(pstParams->pu8Data, (void __user *)tmp, pstParams->u32DataSize);
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				vunmap_phys(pAddr);
				pAddr = NULL;
				vfree(tmp);
				tmp = NULL;
				ret = RET_ERROR;
				break;
			}

			rmb();

			vunmap_phys(pAddr);
			pAddr = NULL;
			vfree(tmp);
			tmp = NULL;

			OVI_TCON_M23_RdFL(tcon_control);
			OVI_TCON_M23_Rd01(tcon_control, demu_en, regVal);

			pstParams->bEnable = regVal;

		}
	} while(0);
	#endif
	return ret;
}

int OVI_HW_M23_SetTconHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regField;

	#if 1
	do {

		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Rd01(tcon_control, epi_out, regField);
		if (!regField) break;

		#if 1
		OVI_TCON_M23_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_M23_Wr01(tcon_hor_mode, hor_reverse, _gOviHwM23Info.horReverseRegFieldValue ? 0 : 1);
		}
		else {
			OVI_TCON_M23_Wr01(tcon_hor_mode, hor_reverse, _gOviHwM23Info.horReverseRegFieldValue);
		}
		OVI_TCON_M23_WrFL(tcon_hor_mode);

		_gOviHwM23Info.mirrorH = bParam;
		#endif

		#if 0
		OVI_TCON_M23_RdFL(tcon_ddiv_mode);
		OVI_TCON_M23_RdFL(tcon_ddiv_hblank);
		if(bParam) {
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, rd_mode, 0x0);
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, line_delay, 0x1);
			OVI_TCON_M23_Wr01(tcon_ddiv_hblank, hb_width, 0xA);
		}
		else {
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, rd_mode, 0x1);
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, line_delay, _gOviHwM23Info.horReverseRegFieldValue);
			OVI_TCON_M23_Wr01(tcon_ddiv_hblank, hb_width, 0x4);
		}
		OVI_TCON_M23_WrFL(tcon_ddiv_mode);
		OVI_TCON_M23_WrFL(tcon_ddiv_hblank);
		#endif
	} while(0);
	#endif

	return ret;
}

int OVI_HW_M23_SetLvdsHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regField;

	do {
		OVI_TCON_M23_RdFL(tcon_control);
		OVI_TCON_M23_Rd01(tcon_control, epi_out, regField);
		if (regField) break;

		#if 0
		OVI_TCON_M23_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_M23_Wr01(tcon_hor_mode, hor_reverse, 0x1);
		}
		else {
			OVI_TCON_M23_Wr01(tcon_hor_mode, hor_reverse, 0x0);
		}
		OVI_TCON_M23_WrFL(tcon_hor_mode);
		#endif

		OVI_TCON_M23_RdFL(tcon_ddiv_mode);
		if(bParam) {
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, rd_mode, 0x0);
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, line_delay, 0x1);
		}
		else {
			OVI_TCON_M23_Wr01(tcon_ddiv_mode, rd_mode, 0x1);
			if (_gOviHwM23Info.converterCheckVal != 0x34)
			{
				OVI_TCON_M23_Wr01(tcon_ddiv_mode, line_delay, 0x0);
			}
		}
		OVI_TCON_M23_WrFL(tcon_ddiv_mode);

		_gOviHwM23Info.mirrorH = bParam;

	} while(0);

	return ret;
}

int OVI_HW_M23_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_M23_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_M23_RdFL(tcon_pgen_agpr1);
		OVI_TCON_M23_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_M23_WrFL(tcon_pgen_agpr1);

		OVI_TCON_M23_RdFL(tcon_pgen_agpg1);
		OVI_TCON_M23_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_M23_WrFL(tcon_pgen_agpg1);

		OVI_TCON_M23_RdFL(tcon_pgen_agpb1);
		OVI_TCON_M23_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_M23_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_M23_Wr(tcon_pgen_ctl, 0x0);
				_gOviHwM23Info.mute = 0;
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				_gOviHwM23Info.mute = 1;
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_M23_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_M23_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M23_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_TCON_M23_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_TCON_M23_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_TCON_M23_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M23_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_TCON_M23_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_TCON_M23_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_TCON_M23_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M23_RdFL(oif_lvds_config1);
		OVI_TCON_M23_RdFL(oif_lvds_config2);
		OVI_TCON_M23_RdFL(oif_vx1_config3);
		OVI_TCON_M23_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_TCON_M23_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_TCON_M23_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_TCON_M23_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_TCON_M23_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_TCON_M23_Wr01(oif_lvds_config1, lvds_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_TCON_M23_Wr01(oif_lvds_config2, lvds_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);

			OVI_TCON_M23_Wr01(oif_vx1_config3, vx1_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_TCON_M23_Wr01(oif_vx1_config4, vx1_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);
		}
		OVI_TCON_M23_WrFL(oif_lvds_config1);
		OVI_TCON_M23_WrFL(oif_lvds_config2);
		OVI_TCON_M23_WrFL(oif_vx1_config3);
		OVI_TCON_M23_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;
	#if 1
	do {
		OVI_TCON_M23_RdFL(tcon_gclk_control);
		OVI_TCON_M23_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_M23_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_M23_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_M23_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_M23_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_M23_WrFL(tcon_gclk_control);
		OVI_TCON_M23_WrFL(tcon_mclk_control);
	} while(0);
	#endif
	return ret;
}

int OVI_HW_M23_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;
	#if 1
	do {
		OVI_TCON_M23_RdFL(tcon_epi_mode);

		if(bParam)
		{
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_en, 0x1);
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_lfsr_mode, 0x1);
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_fr_mode, 0x1);
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_fr_rst, 0x1);
		}
		else
		{
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_en, 0x0);
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_lfsr_mode, 0x0);
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_fr_mode, 0x0);
			OVI_TCON_M23_Wr01(tcon_epi_mode, scr_fr_rst, 0x0);
		}

		OVI_TCON_M23_WrFL(tcon_epi_mode);
	} while(0);
	#endif
	return ret;
}

int OVI_HW_M23_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		//OVI_TCON_M23_RdFL(a10_ctrl);
		OVI_TCON_M23_RdFL(tcon_odc_opt2);

		if(bParam)
		{
			//OVI_TCON_M23_Wr01(a10_ctrl, a10_on, 0x1);
			OVI_TCON_M23_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x1);
		}
		else
		{
			//OVI_TCON_M23_Wr01(a10_ctrl, a10_on, 0x0);
			OVI_TCON_M23_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x0);
		}

		//OVI_TCON_M23_WrFL(a10_ctrl);
		OVI_TCON_M23_WrFL(tcon_odc_opt2);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
{
	int ret = RET_OK;
	UINT16 *u16vcomPatData = NULL;
	int i,k,idx;

	do {
		UINT32 patData[4] = {0,0,0,0};
		UINT32 level = 0;

		if (pstParam == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! \n");
			ret = RET_ERROR;
			break;
		}

		if (OVI_HW_M23_INPUT_VCOM_PAT_DATA_SIZE != pstParam->sizeNum)
		{
			OVI_ERROR("[OVI] Pattern Data size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		u16vcomPatData = (UINT16 *)vmalloc(sizeof(UINT16)*(pstParam->sizeNum));

		if (u16vcomPatData == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(u16vcomPatData, (void __user *)pstParam->pu16vcomPattern, sizeof(UINT16)*(pstParam->sizeNum));

		if (ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0,idx=0; i<4; i++)
		{
			for(k=0; k<24; k++)
			{
				if (u16vcomPatData[idx] > 0)
				{
					patData[i] = patData[i] + (0x1 << k);

					if ((level == 0) && (u16vcomPatData[idx] > 1)) // u16vcomPatData[idx] = 1: on, 0: off, value > 1: on with pixel level
					{
						level = u16vcomPatData[idx];
					}
				}
				idx++;
			}
		}

		OVI_TCON_M23_RdFL(tcon_pgen_vcomp0);
		OVI_TCON_M23_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, patData[0]);
		OVI_TCON_M23_WrFL(tcon_pgen_vcomp0);

		OVI_TCON_M23_RdFL(tcon_pgen_vcomp1);
		OVI_TCON_M23_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, patData[1]);
		OVI_TCON_M23_WrFL(tcon_pgen_vcomp1);

		OVI_TCON_M23_RdFL(tcon_pgen_vcomp2);
		OVI_TCON_M23_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, patData[2]);
		OVI_TCON_M23_WrFL(tcon_pgen_vcomp2);

		OVI_TCON_M23_RdFL(tcon_pgen_vcomp3);
		OVI_TCON_M23_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, patData[3]);
		OVI_TCON_M23_WrFL(tcon_pgen_vcomp3);

		if (level > 0)
		{
			OVI_TCON_M23_RdFL(tcon_pgen_agpr1);
			OVI_TCON_M23_Wr01(tcon_pgen_agpr1, pgen_color_r1, level);
			OVI_TCON_M23_WrFL(tcon_pgen_agpr1);

			OVI_TCON_M23_RdFL(tcon_pgen_agpg1);
			OVI_TCON_M23_Wr01(tcon_pgen_agpg1, pgen_color_g1, level);
			OVI_TCON_M23_WrFL(tcon_pgen_agpg1);

			OVI_TCON_M23_RdFL(tcon_pgen_agpb1);
			OVI_TCON_M23_Wr01(tcon_pgen_agpb1, pgen_color_b1, level);
			OVI_TCON_M23_WrFL(tcon_pgen_agpb1);
		}
	} while(0);

	if(u16vcomPatData != NULL)
		vfree(u16vcomPatData);

	return ret;
}

int OVI_HW_M23_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M23_RdFL(tcon_pgen_ctl);

		switch(enParam)
		{
			case LX_OVI_TCON_VCOM_PAT_CTRL_OFF:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x0);

				OVI_TCON_M23_RdFL(tcon_pgen_vcomp0);
				OVI_TCON_M23_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, 0x0);
				OVI_TCON_M23_WrFL(tcon_pgen_vcomp0);

				OVI_TCON_M23_RdFL(tcon_pgen_vcomp1);
				OVI_TCON_M23_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, 0x0);
				OVI_TCON_M23_WrFL(tcon_pgen_vcomp1);

				OVI_TCON_M23_RdFL(tcon_pgen_vcomp2);
				OVI_TCON_M23_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, 0x0);
				OVI_TCON_M23_WrFL(tcon_pgen_vcomp2);

				OVI_TCON_M23_RdFL(tcon_pgen_vcomp3);
				OVI_TCON_M23_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, 0x0);
				OVI_TCON_M23_WrFL(tcon_pgen_vcomp3);

				OVI_TCON_M23_RdFL(tcon_pgen_agpr1);
				OVI_TCON_M23_Wr01(tcon_pgen_agpr1, pgen_color_r1, 0x3FF);
				OVI_TCON_M23_WrFL(tcon_pgen_agpr1);

				OVI_TCON_M23_RdFL(tcon_pgen_agpg1);
				OVI_TCON_M23_Wr01(tcon_pgen_agpg1, pgen_color_g1, 0x3FF);
				OVI_TCON_M23_WrFL(tcon_pgen_agpg1);

				OVI_TCON_M23_RdFL(tcon_pgen_agpb1);
				OVI_TCON_M23_Wr01(tcon_pgen_agpb1, pgen_color_b1, 0x3FF);
				OVI_TCON_M23_WrFL(tcon_pgen_agpb1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_ON:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x1E);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x16);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x17);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x18);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x19);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x1A);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x1B);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x1C);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8:
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_mode, 0x1D);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M23_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default:
				break;
		}

		OVI_TCON_M23_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_M23_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam)
{
	int ret = RET_OK;
#if 0 // not support
	do {
		if ((_gOviHwM23Info.hwDispOption.frcChipType == LX_OVI_FRC_CHIP_INTERNAL)
			&& (_gOviHwM23Info.hwDispOption.panelResolution == LX_OVI_PANEL_RESOLUTION_3840X2160)
			&& (_gOviHwM23Info.hwDispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_120HZ))
		{
			switch(enParam)
			{
				case LX_OVI_DISP_OUTPUT_MODE_4K60:
					OVI_TCON_M23_RdFL(tcon_ddiv_mode);
					OVI_OIF_M23_RdFL(oif_vx1_lane_sel3);
					OVI_OIF_M23_RdFL(oif_vx1_lane_sel4);
					OVI_TCON_M23_Wr01(tcon_ddiv_mode, lane_num, 0x8);
					OVI_OIF_M23_Wr(oif_vx1_lane_sel3, 0x00010203);
					OVI_OIF_M23_Wr(oif_vx1_lane_sel4, 0x04050607);
					OVI_TCON_M23_WrFL(tcon_ddiv_mode);
					OVI_OIF_M23_WrFL(oif_vx1_lane_sel3);
					OVI_OIF_M23_WrFL(oif_vx1_lane_sel4);

					// M23 TCON clock
					OVI_REG_WR(0xCC450010, 0x00000011);
					// M23 LED clock
					OVI_REG_WR(0xCC420010, 0x00000011);
					// M23 CCO clock
					OVI_REG_WR(0xCC490010, 0x00111100);
					// M23 VSD clock
					OVI_REG_WR(0xCC470010, 0x00001120);
					break;
					
				case LX_OVI_DISP_OUTPUT_MODE_4K120:
				default:
					OVI_TCON_M23_RdFL(tcon_ddiv_mode);
					OVI_OIF_M23_RdFL(oif_vx1_lane_sel3);
					OVI_OIF_M23_RdFL(oif_vx1_lane_sel4);
					OVI_TCON_M23_Wr01(tcon_ddiv_mode, lane_num, 0x10);
					OVI_OIF_M23_Wr(oif_vx1_lane_sel3, 0x08090A0B);
					OVI_OIF_M23_Wr(oif_vx1_lane_sel4, 0x0C0D0E0F);
					OVI_TCON_M23_WrFL(tcon_ddiv_mode);
					OVI_OIF_M23_WrFL(oif_vx1_lane_sel3);
					OVI_OIF_M23_WrFL(oif_vx1_lane_sel4);

					// M23 TCON clock
					OVI_REG_WR(0xCC450010, 0x00000000);
					// M23 LED clock
					OVI_REG_WR(0xCC420010, 0x00000000);
					// M23 CCO clock
					OVI_REG_WR(0xCC490010, 0x00000000);
					// M23 VSD clock
					OVI_REG_WR(0xCC470010, 0x00000000);
					break;
			}

			_gOviHwM23Info.dispOutputMode = enParam;
		}
	} while(0);
#endif
	
	return ret;
}

int OVI_HW_M23_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;
	
	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		if (memcmp(&_gOviHwM23Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("\n[OVI_HW_M23_DisplayResume] WARN:Disp Option Changed! [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
				pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
				pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
				pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
				pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);
		}
	} while(0);

	return ret;
}

static int _OVI_M23_GetPempItuneData(OVI_HW_M23_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	UINT8* u8pempData;
	UINT8* u8ituneData;
	__attribute__((unused)) UINT32 regVal = 0;
	__attribute__((unused)) int i = 0;
	__attribute__((unused)) int j = 0;

	u8pempData = pstParams->pemp;
	u8ituneData = pstParams->itune;

#if 1
	do {
		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x7); // link on(0~2)
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x3); // itune ch 0,1 addr
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_06);
		regVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_06);

		for (i = 0, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x2); // itune ch 2,3 addr
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_06);
		regVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_06);

		for (i = 2, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x1); // pemp ch 0,1 addr
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_06);
		regVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_06);

		for (i = 0, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8pempData[i] = (regVal >> j) & 0xF;
			u8pempData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x0); // pemp ch 2,3 addr
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_06);
		regVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_06);

		for (i = 2, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8pempData[i] = (regVal >> j) & 0xF;
			u8pempData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x0); // link off
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

	}while(0);
#endif

	return ret;

}

static int _OVI_M23_SetPempItuneData(OVI_HW_M23_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	UINT8* u8pempData;
	UINT8* u8ituneData;

	u8pempData = pstParams->pemp;
	u8ituneData = pstParams->itune;

#if 1
	do {

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x1); // link on
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8ituneData[0] & 0xF) | ((u8ituneData[1] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8ituneData[2] & 0xF) | ((u8ituneData[3] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8pempData[0] & 0xF) | ((u8pempData[1] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8pempData[2] & 0xF) | ((u8pempData[3] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x2); // link on
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8ituneData[4] & 0xF) | ((u8ituneData[5] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8ituneData[6] & 0xF) | ((u8ituneData[7] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8pempData[4] & 0xF) | ((u8pempData[5] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8pempData[6] & 0xF) | ((u8pempData[7] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x4); // link on
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8ituneData[8] & 0xF) | ((u8ituneData[9] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8ituneData[10] & 0xF) | ((u8ituneData[11] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8pempData[8] & 0xF) | ((u8pempData[9] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8pempData[10] & 0xF) | ((u8pempData[11] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x0); // link off
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

	}while(0);
#endif
	return ret;

}

int OVI_HW_M23_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	OVI_HW_M23_PEMP_ITUNE_DATA_T param;
#if 1
	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
			ret = copy_from_user(param.pemp, (void __user *)pstParams->pPemp, 12*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(param.itune, (void __user *)pstParams->pItune, 12*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = _OVI_M23_SetPempItuneData(&param);
		}
		else
		{
			ret = _OVI_M23_GetPempItuneData(&param);

			ret = copy_to_user((void __user *)pstParams->pPemp, (void*)param.pemp, 12*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_to_user((void __user *)pstParams->pItune, (void*)param.itune, 12*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}
		}

	} while(0);
#endif
	return ret;
}

static void _OVI_M23_Get_DC_Cal(UINT8 *data)
{
	UINT8* u8DcData;
	__attribute__((unused)) UINT32 regVal = 0;
	int i = 0;
	int j = 0;

	u8DcData = data;
#if 1
	do {
		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x7); // link on(0~2)
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x8); // itune ch 0,1 addr
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_06);
		regVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_06);

		for (i = 0, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8DcData[i] = (regVal >> j) & 0xF;
			u8DcData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x7); // itune ch 2,3 addr
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_06);
		regVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_06);

		for (i = 2, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8DcData[i] = (regVal >> j) & 0xF;
			u8DcData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x0); // link off
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

	}while(0);
#endif
	return;

}

static void _OVI_M23_Set_DC_Cal(UINT8 *data)
{
	UINT8* u8DcData;

	u8DcData = data;
#if 1
	do {
		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x1); // link on
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8DcData[0] & 0xF) | ((u8DcData[1] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8DcData[2] & 0xF) | ((u8DcData[3] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x2); // link on
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8DcData[4] & 0xF) | ((u8DcData[5] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8DcData[6] & 0xF) | ((u8DcData[7] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x4); // link on
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8DcData[8] & 0xF) | ((u8DcData[9] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wrdata, (u8DcData[10] & 0xF) | ((u8DcData[11] << 4) & 0xF0));
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr01(MIP_CTRL_C4TX, mip_c4tx12_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_04, 0x1000000); // reset
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_04);
		OS_UsecDelay(1);

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_05, 0x0); // link off
		CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_05);
		OS_UsecDelay(1);

	}while(0);
#endif
	return;

}

int OVI_HW_M23_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		*pstParams = _gOviHwM23Info.hwDispOption;
	}while(0);

	return ret;
}

int OVI_HW_M23_GetLockStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;
#if 1 // bringup-check need to check epi type
	do{
		// check structure pointer
		if (pbParam == NULL)
		{
			OVI_ERROR("[OVI] parameter is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_02);
		CTOP_CTRL_M23Ax_Rd01(MIP_CTRL_C4TX, mip_c4tx12_02, reg_c4_vx1_lockn_main_counter, regVal);

		if (regVal == 0x0)
		{
			*pbParam = TRUE;
		}
		else
		{
			*pbParam = FALSE;
		}

	} while(0);
#endif

	return ret;
}

int OVI_HW_M23_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;
	static UINT32 _gARnomalVal = 0;
	static UINT32 _g_odc_en = 0;//[0]
	static UINT32 _g_demu_en = 0;//[8]
//	OVI_PRINT(" %d (0:S_PREPARE,1:SUSPEND,2:S_COMPLETED,3:R_PREPARE,4:RESUME,5:R_COMPLETED)\n",u32Param);

	_gOviHwM23Info.pm_status = u32Param;

	switch (u32Param)
	{
		case OVI_HW_M23_PQE_PM_DEVICE_SUSPEND_PREPARE:
			_gOviHwM23Info.pm_suspend = 1;
			cancel_delayed_work_sync(&_gOviHwM23Info.delayedRGBGamma.dlyWork);

			OVI_TCON_M23_RdFL(tcon_control);
			OVI_TCON_M23_Rd01(tcon_control,odc_en,_g_odc_en);
			OVI_TCON_M23_Rd01(tcon_control,demu_en,_g_demu_en);

			OVI_TCON_M23_Wr01(tcon_control,odc_en,0x0);
			OVI_TCON_M23_Wr01(tcon_control,demu_en,0x0);
			OVI_TCON_M23_WrFL(tcon_control);

			usleep_range(20000, 20000);//20ms
			OVI_PRINT("SUSPEND_PREPARE done(backup odc:%d,demu:%d)\n",_g_odc_en,_g_demu_en);
			break;
		case OVI_HW_M23_PQE_PM_DEVICE_SUSPEND:
			break;
		case OVI_HW_M23_PQE_PM_DEVICE_SUSPEND_COMPLETED:
			//	AIOPLL_DISP 1/16 freq. down
			/*OVI_REG_WR(0xCC432058, 0x010C7001);
			OVI_REG_WR(0xCC43205C, 0x00A10063);
			OVI_REG_WR(0xCC432060, 0x08343032);*/ // bringup-check

			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_08);
			_gARnomalVal = CTOP_CTRL_M23Ax_Rd(MIP_CTRL_C4TX, mip_c4tx12_08);

			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_08, 0x0);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_08);

			OVI_PRINT("SUSPEND_COMPLETED done_%x\n",_gARnomalVal);
			break;
		case OVI_HW_M23_PQE_PM_DEVICE_RESUME_PREPARE:
			// restore AIOPLL_DISP
			/*OVI_REG_WR(0xCC432058, 0x010f6002);
			OVI_REG_WR(0xCC43205C, 0x00a14050);
			OVI_REG_WR(0xCC432060, 0x08111042);*/ // bringup-check
			CTOP_CTRL_M23Ax_RdFL(MIP_CTRL_C4TX, mip_c4tx12_08);
			CTOP_CTRL_M23Ax_Wr(MIP_CTRL_C4TX, mip_c4tx12_08, _gARnomalVal);
			CTOP_CTRL_M23Ax_WrFL(MIP_CTRL_C4TX, mip_c4tx12_08);

			_OVI_M23_DispSpreadSpectrumInit();

			OVI_PRINT("RESUME_PREPARE done_%x\n",_gARnomalVal);
			break;
		case OVI_HW_M23_PQE_PM_DEVICE_RESUME:
			break;
		case OVI_HW_M23_PQE_PM_DEVICE_RESUME_COMPLETED:
			_gOviHwM23Info.pm_suspend = 0;
			usleep_range(20000, 20000);//20ms
			OVI_TCON_M23_RdFL(tcon_control);
			OVI_TCON_M23_Wr01(tcon_control,odc_en,_g_odc_en);
			OVI_TCON_M23_Wr01(tcon_control,demu_en,_g_demu_en);
			OVI_TCON_M23_WrFL(tcon_control);
			OVI_PRINT("RESUME_COMPLETED done(restore odc:%d,demu:%d)\n",_g_odc_en,_g_demu_en);
			break;
		default:
			break;
	}

	return ret;
}

static void _OVI_M23_Draw_Pat(int num)
{
	switch (num)
	{
		case 0: // clear
			OVI_TCON_M23_RdFL(tcon_pgen_ctl);
			OVI_TCON_M23_Wr(tcon_pgen_ctl, 0x00000000);
			OVI_TCON_M23_WrFL(tcon_pgen_ctl);

			OVI_TCON_M23_RdFL(oif_vx1_config3);
			OVI_TCON_M23_Wr(oif_vx1_config3, 0x00000000);
			OVI_TCON_M23_WrFL(oif_vx1_config3);

			OVI_TCON_M23_RdFL(oif_vx1_config4);
			OVI_TCON_M23_Wr(oif_vx1_config4, 0x00000000);
			OVI_TCON_M23_WrFL(oif_vx1_config4);
			break;

		case 1: // tcon exter hvbar
			OVI_TCON_M23_RdFL(tcon_odc_opt2);
			OVI_TCON_M23_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_M23_WrFL(tcon_odc_opt2);

			OVI_TCON_M23_RdFL(tcon_pgen_ctl);
			OVI_TCON_M23_Wr(tcon_pgen_ctl, 0x00000019);
			OVI_TCON_M23_WrFL(tcon_pgen_ctl);
			break;

		case 2: // tcon exter hgradi
			OVI_TCON_M23_RdFL(tcon_odc_opt2);
			OVI_TCON_M23_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_M23_WrFL(tcon_odc_opt2);

			OVI_TCON_M23_RdFL(tcon_pgen_ctl);
			OVI_TCON_M23_Wr(tcon_pgen_ctl, 0x00000029);
			OVI_TCON_M23_WrFL(tcon_pgen_ctl);
			break;

		case 3: // tcon inter hvbar
			OVI_TCON_M23_RdFL(tcon_odc_opt2);
			OVI_TCON_M23_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_M23_WrFL(tcon_odc_opt2);

			OVI_TCON_M23_RdFL(tcon_pgen_ctl);
			OVI_TCON_M23_Wr(tcon_pgen_ctl, 0x0000001b);
			OVI_TCON_M23_WrFL(tcon_pgen_ctl);
			break;

		case 4: // tcon inter hgradi
			OVI_TCON_M23_RdFL(tcon_odc_opt2);
			OVI_TCON_M23_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_M23_WrFL(tcon_odc_opt2);

			OVI_TCON_M23_RdFL(tcon_pgen_ctl);
			OVI_TCON_M23_Wr(tcon_pgen_ctl, 0x0000002b);
			OVI_TCON_M23_WrFL(tcon_pgen_ctl);
			break;

		case 5: // pixel repl
			OVI_TCON_M23_RdFL(oif_vx1_config3);
			OVI_TCON_M23_Wr(oif_vx1_config3, 0x400003ff);
			OVI_TCON_M23_WrFL(oif_vx1_config3);

			OVI_TCON_M23_RdFL(oif_vx1_config4);
			OVI_TCON_M23_Wr(oif_vx1_config4, 0x400003ff);
			OVI_TCON_M23_WrFL(oif_vx1_config4);
			break;

		case 6: // led pat
			break;

		default:
			break;
	}
}

int OVI_HW_M23_UpdateChipInfoHeader(void)
{
	int ret = RET_OK;

	do{
		#if 0
		_OVI_M23_UpdateChipInfoHeader();
		#endif
	} while(0);

	return ret;
}

int OVI_HW_M23_SetPCLRC(LX_OVI_PCLRC_LUT_T *pstParams)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr0 = NULL;
	volatile UINT32 *regAddr1 = NULL;
	UINT8 *u8data = NULL;
	UINT32 dataSizeNum;

	#if 1
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!(pstParams->bIsGet))
		{
			if (pstParams->enable == 1)
			{
				dataSizeNum = pstParams->sizeNum;

				// check input table size
				if((dataSizeNum != OVI_HW_M23_INPUT_PCLRC_DATA_SIZE ) || pstParams->pData == NULL)
				{
					OVI_ERROR("[OVI] Input PCLRC Data size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr0 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_pclrc_reg_start), OVI_HW_M23_INPUT_PCLRC_CTRL_DATA_SIZE*sizeof(UINT32));
				if(regAddr0 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M23A0_BASE + offsetof(OVI_TCON_REG_M23A0_T, tcon_pclrc_table_wrdata), sizeof(UINT32));
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}

				u8data = (UINT8 *)vmalloc(dataSizeNum);
				if(u8data == NULL)
				{
					OVI_ERROR("[OVI] memory allocate failed! \n");
					ret = RET_ERROR;
					break;
				}

				ret = copy_from_user(u8data, (void __user *)pstParams->pData, dataSizeNum);
				if(ret)
				{
					OVI_ERROR("[OVI] Error in copying from user! \n");
					ret = RET_ERROR;
					break;
				}

				memcpy((void *)&_gOviHwM23Info.pclrcData, (void *)u8data, dataSizeNum);

				OVI_TCON_M23_RdFL(tcon_pclrc_main);
				OVI_TCON_M23_Wr01(tcon_pclrc_main, pclrc_on, 0x0);
				OVI_TCON_M23_Wr01(tcon_pclrc_main, pclrc_path, pstParams->path == 0x1 ? 0x0 : 0x1 );
				OVI_TCON_M23_Wr01(tcon_pclrc_main, mem_burst, 0x0);
				OVI_TCON_M23_Wr01(tcon_pclrc_main, burst_reverse, 0x0);
				OVI_TCON_M23_WrFL(tcon_pclrc_main);

				for(i=0; i<OVI_HW_M23_INPUT_PCLRC_CTRL_DATA_SIZE; i++)
				{
					writel_relaxed(m23a0_pclrc_ctrl_table[i], &regAddr0[i]);
				}

				OVI_TCON_M23_RdFL(tcon_pclrc_table_addr);
				OVI_TCON_M23_Wr01(tcon_pclrc_table_addr, sram_addr, 0x2000);
				OVI_TCON_M23_WrFL(tcon_pclrc_table_addr);

				for(i=0; i<OVI_HW_M23_INPUT_PCLRC_DATA_SIZE; i++)
				{
					writeb_relaxed(u8data[i], &regAddr1[0]);
				}

				OVI_TCON_M23_RdFL(tcon_pclrc_main);
				OVI_TCON_M23_Wr01(tcon_pclrc_main, pclrc_on, 0x1);
				OVI_TCON_M23_WrFL(tcon_pclrc_main);
			}
			else
			{
				OVI_TCON_M23_RdFL(tcon_pclrc_main);
				OVI_TCON_M23_Wr01(tcon_pclrc_main, pclrc_on, 0x0);
				OVI_TCON_M23_WrFL(tcon_pclrc_main);
			}
		}
		else
		{
			int regVal;

			dataSizeNum = pstParams->sizeNum;

			// check input table size
			if((dataSizeNum != OVI_HW_M23_INPUT_PCLRC_DATA_SIZE ) || pstParams->pData == NULL)
			{
				OVI_ERROR("[OVI] Input PCLRC Data size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			OVI_TCON_M23_RdFL(tcon_pclrc_main);
			OVI_TCON_M23_Rd01(tcon_pclrc_main, pclrc_on, regVal);

			pstParams->enable = regVal;

			OVI_TCON_M23_Rd01(tcon_pclrc_main, pclrc_path, regVal);

			pstParams->path = (regVal == 0x0 ? 0x1 : 0x0);

			ret = copy_to_user(pstParams->pData, (void __user *)&_gOviHwM23Info.pclrcData, dataSizeNum);
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

		}

	} while(0);

	if(u8data != NULL)
		vfree(u8data);
	if(regAddr0 != NULL)
		iounmap((void *)regAddr0);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);
	#endif
	return ret;
}

int OVI_HW_M23_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	__attribute__((unused)) int	i;
	__attribute__((unused)) UINT32 val;

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			#if 1 //
			OVI_TCON_M23_RdFL(tcon_base_address0);
			val = OVI_TCON_M23_Rd(tcon_base_address0);
			seq_printf(m, "tcon_base_addr: 0x%08x\n", val);
			#endif

			seq_printf(m, "ch_power_on_reg1: 0x%08x\n", _gOviHwM23Info.chPowerOnRegValue1 );

			for (i=0; i<_gOVIOutputModes_M23.number_of_modes; i++)
			{
				seq_printf(m, "output_mode%d: %s", i, _gOVIOutputModes_M23.pOVIOutputModes[i].index + strlen("Display settings for M23"));
			}

			OVI_TCON_M23_RdFL(oif_lvds_config0);

			OVI_TCON_M23_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_TCON_M23_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_TCON_M23_RdFL(oif_lvds_config1);
			OVI_TCON_M23_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			#if 1 //
			OVI_TCON_M23_RdFL(tcon_gclk_control);
			OVI_TCON_M23_Rd01(tcon_gclk_control, gclk_en, val);
			seq_printf(m, "tcon.gclk: %s (0x%x)\n", (val)?"on":"off", val);

			OVI_TCON_M23_RdFL(tcon_mclk_control);
			OVI_TCON_M23_Rd01(tcon_mclk_control, mclk_en, val);
			seq_printf(m, "tcon.mclk: %s (0x%x)\n", (val)?"on":"off", val);
			#endif
		}
		break;
		case OVI_HAL_PROC_ID_DISP_OUTPUT_INFO:
		{
			char *iface[LX_OVI_PANEL_INTERFACE_MAX] = {"LVDS","EPI","EPI_QSAC","Vx1","CEDS"};
			char *lockStatus[3] = {"Locked","Unlocked","Unknown"};
			//UINT32 reverseVal;
			UINT32 lockFlag;
			__attribute__((unused)) UINT32 regVal;

			//OVI_REG_RD(0xC930F030, regVal); // dpe_syn c4tx_ctrl NEED FIX

			if (_gOviHwM23Info.dispOption.panelInterface == LX_OVI_PANEL_VX1)
			{
				BOOLEAN bLock;
				OVI_HW_M23_GetLockStatus(&bLock);
				if (bLock == TRUE)
				{
					lockFlag = 0;
				}
				else
				{
					lockFlag = 1;
				}
			}
			else
			{
				lockFlag = 2;
			}

			#if 0
			OVI_TCON_M23_RdFL(tcon_ddiv_mode);
			OVI_TCON_M23_Rd01(tcon_ddiv_mode, rd_mode, reverseVal);
			#endif

			seq_printf(m, "vbe_lockStatus=%s\n", lockStatus[lockFlag]);
			seq_printf(m, "vbe_displayOutput=%s\n", _gOviHwM23Info.isDispOutDisabled ? "off" : "on");
			seq_printf(m, "vbe_outputFrameRate=%s\n", _gOviHwM23Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ ? "60" : "120");
			seq_printf(m, "vbe_panelInterface=%s\n", iface[_gOviHwM23Info.dispOption.panelInterface]);
			seq_printf(m, "vbe_mute=%s\n", _gOviHwM23Info.mute ? "on" : "off");
			seq_printf(m, "vbe_mirrorH=%s\n", _gOviHwM23Info.mirrorH ? "on" : "off");
			seq_printf(m, "vbe_mirrorV=%s\n", _gOviHwM23Info.mirrorV ? "on" : "off");
			//seq_printf(m, "od size= %d , %d\n", OVI_HW_M23_INPUT_OD_TOTAL_SIZE, (OVI_HW_M23_INPUT_LOD_TOTAL_SIZENUM*sizeof(UINT16)));

		}
		break;
		case OVI_HAL_PROC_ID_MIRROR_VERTICAL_INFO:
		{
			_gOviHwM23Info.mirrorV = *((UINT32 *)data);
		}
		break;
		case OVI_HAL_PROC_ID_DRAW_PATTERN:
		{
			_gOviHwM23Info.patType = *((UINT32 *)data);
			_OVI_M23_Draw_Pat(0);
			_OVI_M23_Draw_Pat(_gOviHwM23Info.patType);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return RET_OK;
}

/** @} */
