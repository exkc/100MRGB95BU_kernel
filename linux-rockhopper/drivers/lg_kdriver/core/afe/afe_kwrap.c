/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   COPYRIGHT(c) 1998-2010 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work covered by this copyright hereon
 *   may be reproduced, stored in a retrieval system, in any form
 *   or by any means, electronic, mechanical, photocopying, recording
 *   or otherwise, without the prior written  permission of LG Electronics.
 ******************************************************************************/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		root
 *  @version	1.0
 *  @date		2010-01-03
 *  @note		Additional information.
 */

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	File Inclusions
------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */

#include "os_util.h"

#include "afe_kapi.h"
#include "afe_drv.h"
#include "afe_kwrap.h"
#include "cvd_module.h"

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/
#define AFE_CHECK_CODE(__checker,__if_action,fmt,args...)   \
						__CHECK_IF_ERROR(__checker, AFE_ERROR, __if_action , fmt, ##args )
#define L8_HSTART_SHIFT_DUE_TO_DE_CROP	1

#define	VS_WIDTH_MSPG_209	0x141c
#define	VS_WIDTH_MSPG_227	0x2838

/*------------------------------------------------------------------------------
	Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Variables
------------------------------------------------------------------------------*/
extern BOOLEAN gADCSupport;

/*------------------------------------------------------------------------------
	global Variables
------------------------------------------------------------------------------*/
int g_afe_kwrap_revision = 0x21071200;

int 	_gAFE_Enable_SCART_RGB_WA = 0;
LX_AFE_CVD_SOURCE_ATTRIBUTE_T _gSource_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF;

LX_AFE_CVD_BYPASS_CONTROL_T	_g_cvd_bypass_control_t;

LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	_g_support_color_system = LX_COLOR_SYSTEM_MULTI;

LX_AFE_CVD_SOURCE_ATTRIBUTE_T _g_kwrap_cvd_source_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_NUM;
LX_AFE_CVD_INPUT_PORT_T _g_kwrap_cvd_input_port = LX_AFE_CVBS_NONE;
/*------------------------------------------------------------------------------
	Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
	Static Variables
------------------------------------------------------------------------------*/
typedef enum {
	CVD_NO_SIGNAL,
	CVD_HLOCK,
	CVD_VLOCK,
	CVD_HLOCK_OR_VLOCK,
	CVD_HLOCK_AND_VLOCK,
	CVD_HLOCK_OR_VLOCK_AND_SIGNAL,
	CVD_HLOCK_AND_VLOCK_AND_SIGNAL,
	CVD_HLOCK_AND_VLOCK_AND_REPEAT,
} LX_AFE_CVD_SYNC_STATUS_TO_CHECK;

//111122 wonsik.do
//static UINT32 	g_CVD_status_to_check = CVD_HLOCK_OR_VLOCK;
static UINT32 	g_CVD_status_to_check = CVD_VLOCK;
//UINT32 	g_CVD_status_to_check_ATV_Search = CVD_HLOCK_AND_VLOCK;
UINT32 	g_CVD_status_to_check_ATV_Search = CVD_VLOCK;	//141210 : To Fix channel skip(Philippine NTSC C30)
//static LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	g_support_color_system = LX_COLOR_SYSTEM_MULTI;

LX_AFE_PCMODE_MODETABLE_T *pLX_Default_ModeTable;

// Resolution of PC Mode (VGA / YPbPr)
__attribute__((unused)) static kwrap_afe_resolution_t LX_Default_Resolution[LX_RES_MAXIMUM] =
{
    { 640,  350}, // 00: LX_RES_640X350
    { 640,  400}, // 01: LX_RES_640X400
    { 720,  400}, // 02: LX_RES_720X400
    { 640,  480}, // 03: LX_RES_640X480
    { 800,  600}, // 04: LX_RES_800X600
    { 832,  624}, // 05: LX_RES_832X624
    {1024,  768}, // 06: LX_RES_1024X768
    {1280, 1024}, // 07: LX_RES_1280X1024
    {1600, 1200}, // 08: LX_RES_1600X1200
    {1152,  864}, // 09: LX_RES_1152X864
    {1152,  870}, // 10: LX_RES_1152X870
    {1280,  768}, // 11: LX_RES_1280x768
    {1280,  960}, // 12: LX_RES_1280X960
    { 720,  480}, // 13: LX_RES_720X480
    {1920, 1080}, // 14: LX_RES_1920X1080

    {1280,  720}, // 15: LX_RES_1280X720
    { 720,  576}, // 16: LX_RES_720X576

    {1920, 1200}, // 17: LX_RES_1920X1200

    {1400, 1050}, // 18: LX_RES_1400X1050
    {1440,  900}, // 19: LX_RES_1440X900
    {1680, 1050}, // 20: LX_RES_1680X1050

    {1280,  800}, // 21: LX_RES_1280X800
    {1600, 1024}, // 22: LX_RES_1600X1024
    {1600,  900}, // 23: LX_RES_1600X900
    {1360,  768}, // 24: LX_RES_1360X768
    { 848,  480}, // 25: LX_RES_848X480
    {1920, 1080}, // 26: LX_RES_1920X1080P

    {1366,  768}, // 27: LX_RES_1366X768,
    { 864,  648}, // 28: LX_RES_864X648,
	{1152, 900},	// 29: LX_RES_1152X900,
	{1152, 720},	// 30: LX_RES_1152X720,
	{1728, 1080},	// 31: LX_RES_1728X1080,
};

#define LX_DEFAULT_MODE_TABLE_COUNT (sizeof(E60Ax_Default_ModeTable)/sizeof(LX_AFE_PCMODE_MODETABLE_T))

static LX_AFE_CVD_TIMING_INFO_T LX_Default_CVD_Table[] =
{  /* 0	system			hfreq	vfreq	htotal	hstart	vstart	hsize	vsize */
	{0,	LX_DEFAULT,		157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_NTSC_M,		157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_NTSC_J,		157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_NTSC_443,	157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_PAL_BG,		156,	500,	864,	243-150,		22,		704,	576},
	{0,	LX_PAL_N,		156,	500,	864,	243-150,		22,		704,	576},
	{0,	LX_PAL_M,		157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_PAL_CN,		156,	500,	864,	243-150,		22,		704,	576},
	{0,	LX_PAL_60,		157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_SECAM,		156,	500,	864,	243-150,		22,		704,	576},
//	{0,	LX_NON_STANDARD,	0,	0,	0,	0,	0,			0,		0},
//	{0,	LX_NON_STANDARD,		157,	599,	858,	246-150,		18,		704,	480},
	{0,	LX_NON_STANDARD,		156,	500,	864,	238-150,		22,		704,	576},
};
/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef SEETV_BRINGUP
int afe_kwrap_open(void)
{
	int 	dev_fd;
	int 	ret = RET_ERROR;

	KADP_InitSystem(); /* initialize kadp system if necessary */

	//AFE_CHECK_CODE( g_afe_ctx.dev_fd >= 0, return RET_OK, "[afe] %s : ignore multiple initialization\n", __F__ );
	/* if device is already opened, just increase ref_cnt and exit */
	if ( g_afe_ctx.dev_fd >= 0)
	{
		AFE_LOCK();
		g_afe_ctx.ref_cnt++;
		AFE_ERROR("[kadp_afe] %s : ignore multiple initialization\n", __F__ );
		AFE_UNLOCK();
		return RET_OK;
	}


	AFE_INIT_LOCK();

	AFE_LOCK();
	AFE_TRACE_BEGIN();

	dev_fd = open( AFE_DEVICE, O_RDWR );
	AFE_CHECK_CODE( dev_fd < 0, goto func_exit, "[afe] %s : can't open AFE device (%s)\n", __F__, AFE_DEVICE );
	g_afe_ctx.dev_fd = dev_fd;
	g_afe_ctx.ref_cnt = 1;

	AFE_PRINT("[afe] device is opened\n" );
	ret = RET_OK; /* all work done */

func_exit:
	AFE_TRACE_END();
	AFE_UNLOCK();

	return ret;

}
#endif

int afe_kwrap_isopen(void)
{
#ifdef SEETV_BRINGUP
	if(g_afe_ctx.dev_fd < 0)
		return	RET_ERROR;
	else
#endif
		return	RET_OK;
}

#ifdef SEETV_BRINGUP
/**
 *	AFE device clode
 *
 */
int afe_kwrap_close(void)
{
	int	ret = RET_ERROR;

	AFE_LOCK();
	AFE_TRACE_BEGIN();

	/* check AFE ref_cnt before closing the real device */
	if ( --g_afe_ctx.ref_cnt > 0 )
	{
		ret = RET_OK; goto func_exit;
	}

	ret = close( g_afe_ctx.dev_fd );
	AFE_CHECK_CODE( ret<0, goto func_exit, "[afe] %s : can't close AFE device (%s)\n", __F__, AFE_DEVICE );

	/* [TODO] any post clean up ? */
	g_afe_ctx.dev_fd = -1;
	g_afe_ctx.dev_init_cvd = 0;
	g_afe_ctx.dev_init_adc = 0;
	g_afe_ctx.ref_cnt = 0;

	AFE_PRINT("[afe] device is closed\n" );

func_exit:
	AFE_TRACE_END();
	AFE_UNLOCK();

	/* osa resource destroyed */
	if ( g_afe_ctx.ref_cnt <= 0 )
	{
		KADP_OSA_CloseSema( g_afe_ctx.dev_mtx );

		g_afe_ctx.dev_mtx 	= NULL;
	}

	return ret;
}
#endif

int afe_kwrap_cvd_initializemodule(void)
{
	int	ret = RET_ERROR;

#ifdef SEETV_BRINGUP
	if(RET_ERROR == afe_kwrap_isopen())
		afe_kwrap_open();
#endif

	AFE_PRINT("[%s] entered \n", __func__);

	ret = afe_kwrap_cvd_init(LX_CVD_MAIN);
	AFE_CHECK_CODE( ret != RET_OK, goto func_exit, "[afe] %s : error in afe_kwrap_cvd_init() call\n", __F__ );

#ifdef PIONEER_PLATFORM
	// moved to pdl_vbe_ave.c
//	afe_kwrap_cvd_vdac_power_control(TRUE);
#endif
func_exit:
	return ret;
}

int afe_kwrap_cvd_uninitializemodule(void)
{
	int	ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	ret = afe_kwrap_isopen();
	return ret;
}

int afe_kwrap_cvd_enablemodule(void)
{
	int	ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	ret = afe_kwrap_isopen();
	//ret = afe_kwrap_cvd_power_control(1);
	return ret;
}

int afe_kwrap_cvd_disablemodule(void)
{
	int	ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	ret = afe_kwrap_isopen();
	//ret = afe_kwrap_cvd_power_control(0);
	return ret;
}

int afe_kwrap_cvd_connectmodule(LX_AFE_CVD_SOURCE_ATTRIBUTE_T select_source_attribute, LX_AFE_CVD_INPUT_PORT_T select_cvbs_input_port)
{
	int	ret = RET_ERROR;

	__attribute__((unused)) LX_AFE_LVDS_SELECT_T lvds_sel = LX_AFE_LVDS0_SEL;
	__attribute__((unused)) LX_AFE_LVDS_PDB_T lvds_power = LX_AFE_LVDS_POWER_ON;
	__attribute__((unused)) LX_AFE_LVDS_DATA_TYPE_T lvds_type = LX_AFE_LVDS_TYPE_VESA;
	__attribute__((unused)) LX_AFE_LVDS_SOURCE_T lvds_source = LX_AFE_LVDS_SOURCE_CVD;
	__attribute__((unused)) LX_AFE_LVDS_MODE_T lvds_mode = LX_AFE_LVDS_MODE_NORMAL;

	AFE_PRINT("[%s] entered attr[%d],port[%d]\n", __func__, select_source_attribute, select_cvbs_input_port);

	if (0) //lx_chip_rev() == LX_CHIP_REV(O22, A0))
	{
		AFE_PRINT("O22 A0 cvd disabled !!! \n");
		return 0;
	}

	_g_kwrap_cvd_source_attribute = select_source_attribute;
	_g_kwrap_cvd_input_port = select_cvbs_input_port;

	ret = afe_kwrap_isopen();

	// LVDS path not used
	/*
	if(select_source_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_SCART)
		afe_kwrap_lvds_src_control(lvds_sel, lvds_power, lvds_type, lvds_source, LX_AFE_LVDS_MODE_SCART_MIX);
	else
		afe_kwrap_lvds_src_control(lvds_sel, lvds_power, lvds_type, lvds_source, lvds_mode);
		*/

	ret = afe_kwrap_cvd_power_control(1);

	if(ret != RET_OK)
	{
		AFE_ERROR("!!! CVD Power Control Failed !!! %d\n", ret);
		return ret;
	}

	afe_kwrap_cvd_set_source_type(LX_CVD_MAIN, LX_CVD_INPUT_SOURCE_CVBS, select_cvbs_input_port, LX_AFE_CVBS_NONE, select_source_attribute);

	if(select_source_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF)
	{
	}
	else if(select_source_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_AV)
	{
		afe_kwrap_cvd_setsyncdetectionfortuning(FALSE);	//130206 : DTV only tunning
	}
	else
	{
		afe_kwrap_cvd_setsyncdetectionfortuning(FALSE);	//130206 : DTV only tunning
	}

	afe_kwrap_cvd_start_timer(LX_CVD_MAIN, 0);

	return ret;
}

int afe_kwrap_cvd_disconnectmodule(void)
{
	int	ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	ret = afe_kwrap_isopen();

	afe_kwrap_cvd_power_control(0);
	afe_kwrap_cvd_stop_timer(LX_CVD_MAIN);

	_g_kwrap_cvd_source_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_NUM;
	_g_kwrap_cvd_input_port = LX_AFE_CVBS_NONE;

	return ret;
}


int afe_kwrap_cvd_init(LX_AFE_CVD_SELECT_T select_main_sub)
{
	int ret = RET_ERROR;
	static int cvd_is_initialized = 0;

	AFE_PRINT("[%s] entered : ver[%x] \n", __func__, g_afe_kwrap_revision);

	if (select_main_sub == LX_CVD_MAIN)
	{
//		AFE_PRINT("Main ");
		if(cvd_is_initialized == 0)
		{
			CVD_Init(select_main_sub);
			cvd_is_initialized = 1;
			AFE_PRINT("CVD init\n");
			ret = 0;
		}
		else
		{
			AFE_ERROR("CVD Already Initialzed\n");
			ret = 0;
		}
	}
	else if (select_main_sub == LX_CVD_SUB)
	{
		ADC_DEBUG("Sub ");
		ret = -1;
	}
	else
		ret = -1;


	return ret;
}

int afe_kwrap_cvd_set_source_type(LX_AFE_CVD_SELECT_T select_main_sub, LX_AFE_CVD_SOURCE_TYPE_T select_cvbs_svideo, LX_AFE_CVD_INPUT_PORT_T select_cvbs_input_port, LX_AFE_CVD_INPUT_PORT_T select_chroma_input_port, LX_AFE_CVD_SOURCE_ATTRIBUTE_T select_source_attribute)
{
	LX_AFE_CVD_SET_INPUT_T	CVD_Input_Info;
	int ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	CVD_Input_Info.cvd_main_sub = select_main_sub;
	CVD_Input_Info.cvd_input_source_type = select_cvbs_svideo;
	CVD_Input_Info.cvbs_input_port	= select_cvbs_input_port;
	CVD_Input_Info.chroma_input_port = select_chroma_input_port;
	CVD_Input_Info.cvd_input_source_attribute = select_source_attribute;
	_gSource_attribute = CVD_Input_Info.cvd_input_source_attribute;

	ret = CVD_Set_Source_Type_Control(CVD_Input_Info);

	return ret;
}

int afe_kwrap_set_analog_color_system(LX_AFE_CVD_SELECT_T select_main_sub, LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T 	color_system)
{
	LX_AFE_VIDEO_SYSTEM_INFO_T	CVD_Video_System_Info;
	int ret = RET_ERROR;

	AFE_PRINT("[%s] entered color_system [0x%x]\n", __func__, color_system);

	CVD_Video_System_Info.cvd_main_sub = select_main_sub;
	CVD_Video_System_Info.cvd_video_system = color_system;

	_g_support_color_system = color_system;

	ret = CVD_Set_Color_System(CVD_Video_System_Info);

	return ret;

}

int afe_kwrap_cvd_setsyncdetectionfortuning(BOOLEAN bEnable)
{
	int ret = RET_ERROR;

	AFE_PRINT("%s Entered width value %d \n",__func__, bEnable);

	if(bEnable == TRUE)	// For ATV Tunning
	{
		g_CVD_status_to_check = g_CVD_status_to_check_ATV_Search;
		AFE_PRINT("status to check in ATV searching [0x%x] \n", g_CVD_status_to_check);
//		g_CVD_status_to_check = CVD_HLOCK_AND_VLOCK_AND_REPEAT;
	}
	else
		g_CVD_status_to_check = CVD_VLOCK;
		//g_CVD_status_to_check = CVD_HLOCK_OR_VLOCK;

	ret = CVD_Set_for_Tunning(bEnable);

	return ret;
}

int afe_kwrap_cvd_sync_exist(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN *cvd_sync)
{
	LX_AFE_CVD_STATES_INFO_T	CVD_States_Info;
	__attribute__((unused)) UINT32						status_to_check;
	UINT32						cvd_lock_status;
	UINT8						check_count;
	int ret = RET_ERROR;

	AFE_CHECK_CODE(cvd_sync == NULL, goto func_exit, "[afe] %s : Null Pointer in parameters\n", __F__ );

	CVD_States_Info.cvd_main_sub = select_main_sub;

	ret = CVD_Get_States(&CVD_States_Info);

	cvd_lock_status = CVD_States_Info.cvd_status;

	if(select_main_sub != LX_CVD_MAIN)
	{
		*cvd_sync = FALSE;
		AFE_CHECK_CODE( ret != RET_OK, goto func_exit, "[afe] %s : No Sub CVD support\n", __F__ );
	}
	//if(CVD_States_Info.cvd_status & LX_NO_SIGNAL)
	//dbgprint("g_CVD_status_to_check = %d\n", g_CVD_status_to_check);
	switch (g_CVD_status_to_check)
	{
		case CVD_HLOCK_AND_VLOCK_AND_REPEAT:

			for (check_count = 0; check_count < 5; check_count++)
			{
				cvd_lock_status &= CVD_States_Info.cvd_status;
			}

			if ( (cvd_lock_status & (LX_HLOCK | LX_VLOCK)) == (LX_HLOCK | LX_VLOCK) ) // If HLock AND VLock occures
				*cvd_sync = TRUE;
			else
				*cvd_sync = FALSE;
			break;

		case CVD_HLOCK_AND_VLOCK:

			if ( (cvd_lock_status & (LX_HLOCK | LX_VLOCK)) == (LX_HLOCK | LX_VLOCK) ) // If HLock AND VLock occures
			{
				*cvd_sync = TRUE;
				//AFE_PRINT("$ CVD H/V Locked : status[0x%x] $\n", cvd_lock_status);
			}
			else if ( ( (cvd_lock_status & LX_VLOCK) == LX_VLOCK ) \
					&& ( (cvd_lock_status & LX_NO_SIGNAL) != LX_NO_SIGNAL) \
					&& ( (cvd_lock_status & LX_VNON_STANDARD) == LX_VNON_STANDARD ) )
			{
				*cvd_sync = TRUE;
				AFE_PRINT("$$$$$ CVD [%s] in HDCT workaround ? : status[0x%x] $$$$$\n", __func__, cvd_lock_status);
			}
			else
				*cvd_sync = FALSE;
			break;

		case CVD_VLOCK:

			if ( (cvd_lock_status & LX_VLOCK) == LX_VLOCK ) // If VLock occures
				*cvd_sync = TRUE;
			else
				*cvd_sync = FALSE;
			break;


		case CVD_HLOCK_OR_VLOCK:
		default:
			if ( (cvd_lock_status & (LX_HLOCK | LX_VLOCK)) > 0)  // If HLock OR VLock occures
				*cvd_sync = TRUE;
			else
				*cvd_sync = FALSE;
			break;
	}
func_exit:

	return ret;
}

int afe_kwrap_cvd_get_lock_states(LX_AFE_CVD_SELECT_T select_main_sub, UINT32 *Cvd_Lock_States)
{
	LX_AFE_CVD_STATES_INFO_T	CVD_States_Info;
	int ret = RET_ERROR;

	if(Cvd_Lock_States == NULL)
		return RET_ERROR;

	CVD_States_Info.cvd_main_sub = select_main_sub;

	ret = CVD_Get_States(&CVD_States_Info);

	*Cvd_Lock_States = CVD_States_Info.cvd_status;

	return ret;
}


/* Read reg_line625_detected, and determine 50Hz or 60Hz
   * return 1(reg_line625 set) : 50Hz
   * return 0(reg_line625 unset) : 60Hz
   */
int	afe_kwrap_cvd_read_vfreq(LX_AFE_CVD_SELECT_T select_main_sub, UINT32 *is_line625)
{
	LX_AFE_CVD_STATES_INFO_T	CVD_States_Info;
	int ret = RET_ERROR;

	if(is_line625 == NULL)
		return RET_ERROR;

	CVD_States_Info.cvd_main_sub = select_main_sub;

	ret = CVD_Get_States(&CVD_States_Info);

	if(CVD_States_Info.cvd_status & LX_625LINES_DETECTED)
		*is_line625 = 1;
	else
		*is_line625 = 0;

	return ret;
}

int afe_kwrap_cvd_get_timing_info(LX_AFE_CVD_SELECT_T select_main_sub, LX_AFE_CVD_TIMING_INFO_T *cvd_timing_info)
{
	int ret = RET_OK;
	static LX_AFE_VIDEO_SYSTEM_T	prev_cvd_standard = LX_DEFAULT;	///< cvd video standard
	static LX_AFE_VIDEO_SYSTEM_T	locked_cvd_standard = LX_DEFAULT;	///< cvd video standard
	static int	prev_vfreq = 0;
	LX_AFE_CVD_STATES_INFO_T	CVD_States_Info;

	int cvd_chromalock;
	int cvd_pal_detected;
	int cvd_secam_detected;
	int cs0_chromalock;
	int cs0_pal_detected;
	int cs0_secam_detected;
	int cvd_color_system_lock;
	int stable_count = 3;

	AFE_CHECK_CODE(cvd_timing_info == NULL, goto func_exit, "[afe] %s : Null Pointer in parameters\n", __F__ );

	cvd_timing_info->cvd_main_sub = select_main_sub;

	CVD_Get_Timing_Info(cvd_timing_info);

	CVD_States_Info.cvd_main_sub = select_main_sub;

	ret |= CVD_Get_States(&CVD_States_Info);

	cvd_chromalock = CVD_States_Info.cvd_status & LX_CHROMALOCK;
	cvd_pal_detected = CVD_States_Info.cvd_status & LX_PAL_DETECTED;
	cvd_secam_detected = CVD_States_Info.cvd_status & LX_SECAM_DETECTED;
	cs0_chromalock = CVD_States_Info.cvd_status & LX_CS0_CHROMALOCK;
	cs0_pal_detected = CVD_States_Info.cvd_status & LX_CS0_PAL_DETECTED;
	cs0_secam_detected = CVD_States_Info.cvd_status & LX_CS0_SECAM_DETECTED;

	// enlarge stable_count when PAL/SECAM both detected !!!
	if( (cvd_timing_info->cvd_standard == LX_PAL_BG) && cs0_chromalock && cs0_secam_detected)
	{
		if(cvd_timing_info->cvd_lock_stable_count == 3)
			AFE_PRINT("### CVD GetTiming : PAL/SECAM both lock !!! : lock_count[%d],chroma[%d],pal[%d],secam[%d] ,cs0_chroma[%d],cs0_pal[%d],cs0_secam[%d]###\n",\
				cvd_timing_info->cvd_lock_stable_count, cvd_chromalock, cvd_pal_detected, cvd_secam_detected, cs0_chromalock, cs0_pal_detected, cs0_secam_detected);
		stable_count = 8;
	}
	else if ( _g_support_color_system == LX_COLOR_SYSTEM_NTSC_M )
		stable_count = 1;

	cvd_color_system_lock = ( (cvd_timing_info->cvd_standard >= LX_NTSC_M) && (cvd_timing_info->cvd_standard <= LX_NTSC_443) && cvd_chromalock ) \
							|| ( (cvd_timing_info->cvd_standard >= LX_PAL_BG) && (cvd_timing_info->cvd_standard <= LX_PAL_60) && cvd_chromalock && cvd_pal_detected ) \
							|| ( (cvd_timing_info->cvd_standard == LX_SECAM) && cvd_secam_detected );

	if(cvd_color_system_lock && (cvd_timing_info->cvd_lock_stable_count >= stable_count) )
	{
	}
	else if ( (cvd_timing_info->cvd_standard >= LX_NON_STANDARD) || (cvd_timing_info->cvd_standard < LX_NTSC_M) )
	{
		cvd_timing_info->cvd_standard = LX_NON_STANDARD;
	}
	else if ( ( (cvd_timing_info->cvd_lock_stable_count < stable_count) && (_gSource_attribute != LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF) ) 	// added to remove transition color system
			|| ( (cvd_timing_info->cvd_lock_stable_count < stable_count) && (_gSource_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF) ) )	// added to remove transition color system
		cvd_timing_info->cvd_standard = prev_cvd_standard;

	if(prev_cvd_standard != cvd_timing_info->cvd_standard)
	{
		AFE_PRINT("### CVD GetTiming : Standard Changed [%d] => [%d] : lock_count[%d],chroma[%d],pal[%d],secam[%d] ,cs0_chroma[%d],cs0_pal[%d],cs0_secam[%d]###\n",\
				prev_cvd_standard ,cvd_timing_info->cvd_standard, cvd_timing_info->cvd_lock_stable_count, cvd_chromalock, cvd_pal_detected, cvd_secam_detected, cs0_chromalock, cs0_pal_detected, cs0_secam_detected);
		prev_cvd_standard = cvd_timing_info->cvd_standard;
		if(prev_cvd_standard < LX_NON_STANDARD)
			locked_cvd_standard = prev_cvd_standard;
	}

	// for 576i detection in NTSC only system
	/*
	if(cvd_timing_info->cvd_standard < LX_NON_STANDARD)
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_HFreq;
		//cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_VFreq;
		cvd_timing_info->u16_VFreq = cvd_timing_info->u16_VFreq_Stable;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[cvd_timing_info->cvd_standard].u16_VSize;
	}
	// For 50Hz Only System
	else if (( g_support_color_system & (LX_COLOR_SYSTEM_NTSC_M |LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_443 | LX_COLOR_SYSTEM_PAL_60)) == 0 )
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_HFreq;
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_VFreq;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[LX_PAL_BG].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[LX_PAL_BG].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[LX_PAL_BG].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[LX_PAL_BG].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[LX_PAL_BG].u16_VSize;
	}
	// For 60Hz Only System
	else if ((  g_support_color_system & (LX_COLOR_SYSTEM_PAL_G |LX_COLOR_SYSTEM_PAL_NC | LX_COLOR_SYSTEM_SECAM)) == 0 )
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_HFreq;
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_VFreq;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[LX_NTSC_M].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[LX_NTSC_M].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[LX_NTSC_M].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[LX_NTSC_M].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[LX_NTSC_M].u16_VSize;
	}
	*/

	// Use stable VFreq to reduce 60Hz transition when channel change
	/*
	if(cvd_timing_info->u16_VFreq_Stable > 550)
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_VFreq;
	else
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_VFreq;
		*/
#if 1

	if(cvd_timing_info->u16_VFreq > 550)
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_HFreq;
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_VFreq;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[LX_NTSC_M].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[LX_NTSC_M].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[LX_NTSC_M].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[LX_NTSC_M].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[LX_NTSC_M].u16_VSize;
	}
	else
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_HFreq;
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_VFreq;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[LX_PAL_BG].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[LX_PAL_BG].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[LX_PAL_BG].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[LX_PAL_BG].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[LX_PAL_BG].u16_VSize;
	}

	if( (locked_cvd_standard == LX_PAL_BG) || (locked_cvd_standard == LX_PAL_N)\
			|| (locked_cvd_standard == LX_PAL_CN) || (locked_cvd_standard == LX_SECAM) )
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_VFreq;
	else
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_VFreq;
#else
	if( (locked_cvd_standard == LX_PAL_BG) || (locked_cvd_standard == LX_PAL_N)\
			|| (locked_cvd_standard == LX_PAL_CN) || (locked_cvd_standard == LX_SECAM) )
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_HFreq;
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_PAL_BG].u16_VFreq;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[LX_PAL_BG].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[LX_PAL_BG].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[LX_PAL_BG].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[LX_PAL_BG].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[LX_PAL_BG].u16_VSize;
	}
	else
	{
		cvd_timing_info->u16_HFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_HFreq;
		cvd_timing_info->u16_VFreq = LX_Default_CVD_Table[LX_NTSC_M].u16_VFreq;
		cvd_timing_info->u16_HTotal = LX_Default_CVD_Table[LX_NTSC_M].u16_HTotal;
		cvd_timing_info->u16_HStart = LX_Default_CVD_Table[LX_NTSC_M].u16_HStart;
		cvd_timing_info->u16_VStart = LX_Default_CVD_Table[LX_NTSC_M].u16_VStart;
		cvd_timing_info->u16_HSize = LX_Default_CVD_Table[LX_NTSC_M].u16_HSize;
		cvd_timing_info->u16_VSize = LX_Default_CVD_Table[LX_NTSC_M].u16_VSize;
	}
#endif

	if( prev_vfreq != cvd_timing_info->u16_VFreq )
	{
		AFE_PRINT("### CVD GetTiming : VFreq Changed [%d] => [%d] : color_system[%d] lock_count[%d] ###\n",\
				prev_vfreq, cvd_timing_info->u16_VFreq ,cvd_timing_info->cvd_standard, cvd_timing_info->cvd_lock_stable_count);
		prev_vfreq = cvd_timing_info->u16_VFreq ;
	}

func_exit:

	return ret;
}

/* Not Used */
#if 0
int afe_kwrap_ttx_set_video_standard(LX_AFE_VIDEO_SYSTEM_T cvd_standard)
{
	int ret = RET_ERROR;

	ret = ioctl(g_afe_ctx.dev_fd, AFE_IOW_SET_TTX_VIDEO_STANDARD, cvd_standard);

	AFE_CHECK_CODE( ret != RET_OK, goto func_exit, "[afe] %s : error in ioctl call\n", __F__ );

func_exit:
	AFE_TRACE_END();
	AFE_UNLOCK();

	return ret;
}
#endif

int afe_kwrap_vport_reg_read(UINT32 addr, UINT32 *data)
{
	int ret = RET_ERROR;

	LX_AFE_REG_RW_T	reg_addr_data_t;

	if(data == NULL)
		return RET_ERROR;

	reg_addr_data_t.addr = addr;
	reg_addr_data_t.data = 0;

	ret = CVD_Vport_Reg_Read(&reg_addr_data_t);

	*data = reg_addr_data_t.data;
	return 0;
}

int afe_kwrap_vport_reg_write(UINT32 addr, UINT32 data)
{
	int ret = RET_ERROR;

	LX_AFE_REG_RW_T	reg_addr_data_t;

	reg_addr_data_t.addr = addr;
	reg_addr_data_t.data = data;

	ret = CVD_Vport_Reg_Write(&reg_addr_data_t);

	return ret;
}

int afe_kwrap_cvd_stop_timer(LX_AFE_CVD_SELECT_T select_main_sub)
{
	LX_AFE_CVD_TIMER_T cvd_timer_t;
	int ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	cvd_timer_t.cvd_main_sub = select_main_sub;
	cvd_timer_t.timeout = 0;

	ret = CVD_Stop_Timer((unsigned long)&cvd_timer_t);

	return ret;
}

int afe_kwrap_cvd_start_timer(LX_AFE_CVD_SELECT_T select_main_sub, UINT32 timeout)
{
	LX_AFE_CVD_TIMER_T cvd_timer_t;
	int ret = RET_ERROR;

	AFE_PRINT("[%s] entered \n", __func__);

	cvd_timer_t.cvd_main_sub = select_main_sub;
	cvd_timer_t.timeout = timeout;

	ret = CVD_Start_Timer((unsigned long)&cvd_timer_t);

	return ret;
}

int afe_kwrap_cvd_program_color_system(LX_AFE_CVD_SELECT_T select_main_sub, UINT8 color_system)
{
	LX_AFE_CVD_PROGRAM_COLOR_SYSTEM_T program_color_system_t;
	int ret = RET_ERROR;

	program_color_system_t.cvd_main_sub = select_main_sub;
	program_color_system_t.color_system = color_system;

	ADC_DEBUG("AFE Program Color System\n");
	ret = CVD_Program_Color_System(program_color_system_t);

	return ret;
}

int afe_kwrap_cvd_test(LX_AFE_CVD_TEST_PARAM_T *pCVD_Test_Param_t)
{
	int ret = RET_ERROR;

	ret = CVD_Test_Program(pCVD_Test_Param_t);

	return ret;
}

/* Not Used */
#if 0
int afe_kwrap_cvd_set_sw_3dcomb_control(UINT8 enable, UINT32 hf_thr, UINT32 lf_thr, UINT32 diff_thr, UINT32 region_30_mode)
{
	LX_AFE_CVD_SW_3DCOMB_CONTROL_T	control_value_t;
	int ret = RET_ERROR;

	AFE_CHECK_CODE( g_afe_ctx.dev_init_cvd == 0, return RET_ERROR, "[afe] %s :ignore before initialization\n", __F__ );
	AFE_LOCK();
	AFE_TRACE_BEGIN();

	control_value_t.Enable = enable;
	control_value_t.Hf_thr = hf_thr;
	control_value_t.Lf_thr = lf_thr;
	control_value_t.Diff_thr = diff_thr;
	control_value_t.Region_30_mode = region_30_mode;

	ret = ioctl(g_afe_ctx.dev_fd, AFE_IOW_CVD_SET_SW_3DCOMB_CONTROL, &control_value_t);

	AFE_CHECK_CODE( ret != RET_OK, goto func_exit, "[afe] %s : error in ioctl call\n", __F__ );

func_exit:
	AFE_TRACE_END();
	AFE_UNLOCK();

	return ret;
}
#endif

int afe_kwrap_cvd_power_control(UINT32 enable)
{
	int ret = RET_ERROR;

	ret = CVD_Channel_Power_Control(enable);

	return ret;
}

/* Not Used */
#if 0
int afe_kwrap_cvd_enable_detection_interrupt(UINT32 enable)
{
	int ret = RET_ERROR;

	AFE_CHECK_CODE( g_afe_ctx.dev_init_cvd == 0, return RET_ERROR, "[afe] %s :ignore before initialization\n", __F__ );
	AFE_LOCK();
	AFE_TRACE_BEGIN();

	ret = ioctl(g_afe_ctx.dev_fd, AFE_IOW_CVD_ENABLE_DETECTION_INTERRUPT, &enable);

	AFE_CHECK_CODE( ret != RET_OK, goto func_exit, "[afe] %s : error in ioctl call\n", __F__ );

func_exit:
	AFE_TRACE_END();
	AFE_UNLOCK();

	return ret;
}
#endif

int afe_kwrap_cvd_get_states_detail(LX_AFE_CVD_STATES_DETAIL_T *pcvd_states_detail_t)
{
	int ret = RET_ERROR;

	ret = CVD_Get_States_Detail(pcvd_states_detail_t);

	return ret;
}

int afe_kwrap_cvd_set_pq_value(LX_AFE_CVD_PQ_MODE_T	cvd_pq_mode)
{
	int ret = RET_ERROR;

	if(cvd_pq_mode >= LX_CVD_PQ_NUM)
	{
		ret = -1;
		return ret;
	}

	ret = CVD_Set_PQ_Mode(cvd_pq_mode);

	return ret;
}

int afe_kwrap_cvd_bypass_control(LX_AFE_CVD_BYPASS_SOURCE_T buf_out_1_sel,  LX_AFE_CVD_BYPASS_SOURCE_T buf_out_2_sel,  LX_AFE_CVD_BYPASS_CVBS_SOURCE_T	cvbs_source_sel)
{
	int ret = RET_ERROR;
	LX_AFE_CVD_BYPASS_CONTROL_T	cvd_bypass_control_t;

	AFE_PRINT("[%s] entered buf1[%d], buf2[%d], source[%d]\n", __func__, buf_out_1_sel, buf_out_2_sel, cvbs_source_sel);

	cvd_bypass_control_t.buf_out_1_sel = buf_out_1_sel;
	cvd_bypass_control_t.buf_out_2_sel = buf_out_2_sel;
	cvd_bypass_control_t.cvbs_source_sel = cvbs_source_sel;

	memcpy(&_g_cvd_bypass_control_t, &cvd_bypass_control_t, sizeof(LX_AFE_CVD_BYPASS_CONTROL_T) );

	ret =	CVD_Bypass_Control(&cvd_bypass_control_t);

	return ret;
}

int afe_kwrap_cvd_vdac_power_control(BOOLEAN bOnOff)
{
	int ret = RET_ERROR;

	ret =	CVD_OnOff_VDAC(bOnOff);

	return ret;
}

int afe_kwrap_cvd_vdac_mute_control(int Enable)
{
	int ret = RET_ERROR;

	ret =	CVD_VDAC_mute_control(Enable);

	return ret;
}

int afe_kwrap_cvd_set_hstate_max(UINT32 hstate_max_value)
{
	int ret = RET_ERROR;

	ret = CVD_Set_Hstate_Max(hstate_max_value);

	return ret;
}

/**
 * @brief Read kernel memory configuration of CVD driver(Test only)
 *
 * @param mem_base_comb_buffer
 * @param mem_size_comb_buffer
 * @param mem_base_cvd_reg
 * @param mem_size_cvd_reg
 *
 * @return
 */
int afe_kwrap_cvd_get_mem_cfg(UINT32* mem_base_comb_buffer, UINT32* mem_size_comb_buffer, UINT32* mem_base_cvd_reg, UINT32* mem_size_cvd_reg)
{
	int ret = RET_OK;
	LX_AFE_CVD_MEM_CFG_T	cvd_mem_cfg_t;

	if ( (mem_base_comb_buffer == NULL) || (mem_size_comb_buffer == NULL) || (mem_base_cvd_reg == NULL) \
		|| (mem_size_cvd_reg == NULL) )
		return RET_ERROR;

	AFE_GetMemCfg(&cvd_mem_cfg_t.mem_base_comb_buffer, &cvd_mem_cfg_t.mem_size_comb_buffer, &cvd_mem_cfg_t.mem_base_cvd_reg, &cvd_mem_cfg_t.mem_size_cvd_reg );

	*mem_base_comb_buffer = cvd_mem_cfg_t.mem_base_comb_buffer;
	*mem_size_comb_buffer = cvd_mem_cfg_t.mem_size_comb_buffer;

	*mem_base_cvd_reg = cvd_mem_cfg_t.mem_base_cvd_reg;
	*mem_size_cvd_reg = cvd_mem_cfg_t.mem_size_cvd_reg;

	return ret;
}

/**
 * @brief Read CVD Crunky Detection Status
 *
 * @param ck_vbi_detected
 * @param number_of_cs
 *
 * @return
 */
int afe_kwrap_cvd_get_crunky_status(UINT32 *ck_vbi_detected, UINT32 *number_of_cs)
{
	int ret = RET_OK;

	LX_AFE_CVD_CK_T ck_detection_t;

	if ( (ck_vbi_detected == NULL) || (number_of_cs == NULL) )
		return RET_ERROR;

	/* ioctl function call */
	ret = CVD_Get_Crunky_Status(&ck_detection_t);

	*ck_vbi_detected = ck_detection_t.ck_vbi_detected;
	*number_of_cs 	 = ck_detection_t.ck_colorstrip_detected;

	return ret;
}

/**
 * Control Kdrv Debug Print of AFE
 *
 * @param 	printType			[in]  kdrvier afe debug type
 * @param 	printColor		[in]  kdriver afe debug color
 * @return 	if succeeded - OK, else - RET_ERROR.
 * @see	 .
 */

/* Debug Only */
#if 0
 int afe_kwrap_debugprintctrl(unsigned int printType, unsigned int printColor, unsigned int printEnable)
{
	int ret = RET_ERROR;

	LX_AFE_DEBUG_CTRL_T debugCtrl;

	debugCtrl.printType  = printType;
	debugCtrl.printColor = printColor;
	debugCtrl.printEnable = printEnable;

	AFE_LOCK();
	AFE_TRACE_BEGIN();

	AFE_PRINT( "[AFE] %s is started.\n", __FUNCTION__ );

	/* ioctl function call */
	ret = ioctl ( g_afe_ctx.dev_fd, AFE_IOW_DEBUG_PRINT_CTRL, &debugCtrl );
	AFE_CHECK_CODE( ret != RET_OK, goto func_exit, "[adec] %s : error in ioctl call\n", __F__ );

func_exit:
	AFE_TRACE_END();
	AFE_UNLOCK();

	return ret;
}
#endif


/**
 * @brief Set Current Black Level to CVD Kernel Driver
 *
 * @param black_level (0:low, 1:high, 2:auto)
 *
 * @return
 */
int afe_kwrap_cvd_set_blacklevel(UINT32 black_level)
{
	int ret = RET_OK;

	LX_AFE_CVD_BLACK_LEVEL_T cvd_black_level_t;

	AFE_PRINT("[%s] entered black_level[%d] \n", __func__, black_level);

	if(black_level == 0)
		cvd_black_level_t = LX_AFE_CVD_BLACK_LEVEL_LOW;
	else if(black_level == 1)
		cvd_black_level_t = LX_AFE_CVD_BLACK_LEVEL_HIGH;
	else if(black_level == 2)
		cvd_black_level_t = LX_AFE_CVD_BLACK_LEVEL_AUTO;
	else
	{
		ret = RET_INVALID_PARAMS;
		return ret;
	}

	ret = CVD_Set_Black_Level(cvd_black_level_t);

	return ret;
}

int afe_kwrap_cvd_atv_channel_change(BOOLEAN bChannel_Change)
{
	int ret = RET_ERROR;

	AFE_PRINT("[%s] entered bChannel_Change[%d] \n", __func__, bChannel_Change);

	ret = CVD_Channel_Change_Control(bChannel_Change);

	return ret;
}

int afe_kwrap_cvd_get_noise_status(UINT32 *pCVD_Noise_Status)
{
	int ret = RET_ERROR;

	*pCVD_Noise_Status = CVD_Get_Noise_Status();

	return ret;
}

/**
* @brief Set Internal/External Demod Mode to CVD
*
* @param internal_mode
*
* @return
*/
int afe_kwrap_set_internal_demod_mode(BOOLEAN internal_mode)
{
	int ret = RET_ERROR;

	AFE_PRINT("[%s] entered internal_mode[%d] \n", __func__, internal_mode);

	ret = CVD_Set_Use_Internal_Demod(internal_mode);

	return ret;
}
