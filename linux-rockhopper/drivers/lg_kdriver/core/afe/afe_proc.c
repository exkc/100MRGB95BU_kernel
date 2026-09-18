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
 *  Linux proc interface for afe device.
 *	afe device will teach you how to make device driver with new platform.
 *
 *  author		wonsik.do (wonsik.do@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_afe
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include "afe_drv.h"
#include "proc_util.h"
#include "debug_util.h"
#include "os_util.h"
#include "sys_io.h"

#include "cvd_module.h"
#include "afe_kwrap.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_CVD_STATUS,
	PROC_ID_CVD_INIT,
	PROC_ID_CVD_INIT_MODULE,
	PROC_ID_CVD_CONN_MODULE,
	PROC_ID_CVD_SOURCE_TYPE,
	PROC_ID_CVD_PROG_COLOR_SYSTEM,
	PROC_ID_CVD_SET_COLOR_SYSTEM,
	PROC_ID_CVD_TIMER,
	PROC_ID_CVD_PDB,
	PROC_ID_CVD_TUNNING_MODE,
	PROC_ID_CVD_BLUE_MODE,
	PROC_ID_CVD_YC_BLEND,
	PROC_ID_CVD_CLAMP_UP_DOWN,
	PROC_ID_CVD_CLAMP_MODE,
	PROC_ID_CVD_SYNC_TUNNING_MODE,
	PROC_ID_COMMAND,
	PROC_ID_AFE_DEBUG,
	PROC_ID_CVD_TIMING,
	PROC_ID_SYS_REG_READ,
	PROC_ID_SYS_REG_WRITE,
	PROC_ID_CVD_REG_READ,
	PROC_ID_CVD_REG_WRITE,
	PROC_ID_CVD_WA,
	PROC_ID_AFE_TEST,
	PROC_ID_PM_TEST,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int avd_update_device_info(void);

extern int v4l2_avd_pm_runtime_help(char* buffer);
extern int v4l2_avd_pm_runtime_test(char* command);
void	AFE_PROC_Init (void);
void	AFE_PROC_Cleanup (void);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern UINT32 g_CVD_HW_DRV_REV;
extern UINT32 g_CVD_CONTROL_DRV_REV;
extern UINT32 g_CVD_TASK_DRV_REV;
extern UINT32 g_CVD_HAL_REV;

extern BOOLEAN gCVDInitStatus;

extern UINT32 	g_CVD_status_to_check_ATV_Search;
extern AVD_DEV_INFO_T avd_device_info;

extern BOOLEAN gADCSupport;

extern BOOLEAN g_CVD_CMA_POOL;
extern BOOLEAN g_CVD_USE_TE_SHARED_POOL;
extern BOOLEAN gCVD_2d_mode;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _afe_proc_test_read(struct seq_file *m);
static ssize_t _afe_proc_test_write(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _afe_proc_cvd_set_colorsystem_read(struct seq_file *m);
static ssize_t _afe_proc_cvd_set_colorsystem_write(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _afe_proc_cvd_prog_colorsystem_read(struct seq_file *m);
static ssize_t _afe_proc_cvd_prog_colorsystem_write(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _afe_proc_afe_debug_read(struct seq_file *m);
static ssize_t _afe_proc_afe_debug_write(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _afe_proc_cvd_status_read(struct seq_file *m, void* data);
static void _afe_proc_cvd_timing_read(struct seq_file *m, void* data);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRW_DEFINE_EX(_afe_proc_afe_test_fops, _afe_proc_test_read, _afe_proc_test_write)
OS_PROC_SEQRD_DEFINE_EX(_afe_proc_cvd_status_fops, _afe_proc_cvd_status_read, 0)
OS_PROC_SEQRW_DEFINE_EX(_afe_proc_cvd_set_colorsystem_fops, _afe_proc_cvd_set_colorsystem_read, _afe_proc_cvd_set_colorsystem_write)
OS_PROC_SEQRW_DEFINE_EX(_afe_proc_cvd_prog_colorsystem_fops, _afe_proc_cvd_prog_colorsystem_read, _afe_proc_cvd_prog_colorsystem_write)
OS_PROC_SEQRW_DEFINE_EX(_afe_proc_afe_debug_fops, _afe_proc_afe_debug_read, _afe_proc_afe_debug_write)
OS_PROC_SEQRD_DEFINE_EX(_afe_proc_cvd_timing_fops, _afe_proc_cvd_timing_read, 0)

static OS_PROC_DESC_TABLE_T	_g_afe_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "cvd_status",		PROC_ID_CVD_STATUS,     OS_PROC_FLAG_SEQRD, (void*)&_afe_proc_cvd_status_fops},
	{ "cvd_init",		PROC_ID_CVD_INIT    , OS_PROC_FLAG_WRITE },
	{ "cvd_init_module",		PROC_ID_CVD_INIT_MODULE    , OS_PROC_FLAG_WRITE },
	{ "cvd_conn_module",		PROC_ID_CVD_CONN_MODULE    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_timer",		PROC_ID_CVD_TIMER    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_source_type",		PROC_ID_CVD_SOURCE_TYPE    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_prog_color_system",              PROC_ID_CVD_PROG_COLOR_SYSTEM,     OS_PROC_FLAG_SEQRW, (void*)&_afe_proc_cvd_prog_colorsystem_fops},
	{ "cvd_set_color_system",               PROC_ID_CVD_SET_COLOR_SYSTEM,     OS_PROC_FLAG_SEQRW, (void*)&_afe_proc_cvd_set_colorsystem_fops},
	{ "cvd_pdb",		PROC_ID_CVD_PDB    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_tunning_mode",		PROC_ID_CVD_TUNNING_MODE    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_blue_mode",		PROC_ID_CVD_BLUE_MODE    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_yc_blend",		PROC_ID_CVD_YC_BLEND    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_clamp_up_down",		PROC_ID_CVD_CLAMP_UP_DOWN    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_clamp_mode",		PROC_ID_CVD_CLAMP_MODE    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_sync_tunning_mode",		PROC_ID_CVD_SYNC_TUNNING_MODE    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "afe_debug",		PROC_ID_AFE_DEBUG,     OS_PROC_FLAG_SEQRW, (void*)&_afe_proc_afe_debug_fops},
	{ "cvd_timing",		PROC_ID_CVD_TIMING,     OS_PROC_FLAG_SEQRD, (void*)&_afe_proc_cvd_timing_fops},
	{ "sys_reg_read",		PROC_ID_SYS_REG_READ,     OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "sys_reg_write",		PROC_ID_SYS_REG_WRITE,     OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_reg_read",		PROC_ID_CVD_REG_READ,     OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_reg_write",		PROC_ID_CVD_REG_WRITE,     OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cvd_wa",		PROC_ID_CVD_WA,     OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "command",	PROC_ID_COMMAND , OS_PROC_FLAG_WRITE },
	{ "afe_test",		PROC_ID_AFE_TEST,     OS_PROC_FLAG_SEQRW, (void*)&_afe_proc_afe_test_fops},
	{ "pm_test",    PROC_ID_PM_TEST, OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _afe_proc_cvd_status_read(struct seq_file *m, void* data)
{
	LX_AFE_CVD_STATES_DETAIL_T	cvd_states_detail_t = {0,};
	LX_AFE_CVD_TIMING_INFO_T	cvd_timing_info = {0,};
	BOOLEAN cvd_sync;
	UINT32 isLine625;
	UINT32 ck_vbi_detection, number_of_cs;

	if(gCVDInitStatus == FALSE)
	{
		seq_printf(m, "CVD Not Initialized !!!!!\n");
		return;
	}

	CVD_Get_States_Detail(&cvd_states_detail_t);
	CVD_Get_Timing_Info(&cvd_timing_info);

	seq_printf(m, "[CVD Debug] CVD Timing Info \n");
	afe_kwrap_cvd_sync_exist(LX_CVD_MAIN, &cvd_sync);
	if(cvd_sync)
		seq_printf(m, "[CVD Debug] CVD Sync Exist \n");
	else
		seq_printf(m, "[CVD Debug] CVD NO SIGNAL !!!!! \n");

	seq_printf(m, "[CVD Debug] Color System= %d (1:NTSC_M, 2:NTSC_J, 3:NTSC_443, 4:PAL_BG, 5:PAL_N, 6:PAL_M, 7:PAL_Cn, 8:PAL60, 9:SECAM, 10:Non Standard) \n", cvd_timing_info.cvd_standard);

//	seq_printf(m, "[CVD Debug]  hFreq= %d (* 100Hz) \n", cvd_timing_info.u16_HFreq);
	seq_printf(m, "[CVD Debug]  vFreq= %d (* 0.1Hz) \n", cvd_timing_info.u16_VFreq);
	seq_printf(m, "[CVD Debug]  hActive= %d \n", cvd_timing_info.u16_HSize);
	seq_printf(m, "[CVD Debug]  vActive= %d \n", cvd_timing_info.u16_VSize);
	seq_printf(m, "[CVD Debug]  VFreq_Stable= %d \n", cvd_timing_info.u16_VFreq_Stable);

	afe_kwrap_cvd_read_vfreq(LX_CVD_MAIN, &isLine625); // reg_625line == 1
	if(isLine625) // reg_625line ==1 : 50Hz system
		seq_printf(m, "[CVD Debug] Field Rate is 50Hz\n ");
	else
		seq_printf(m, "[CVD Debug] Field Rate is 60Hz\n ");

	seq_printf(m, "[CVD Debug] CVD Detailed States \n");
	seq_printf(m, "CVD Driver Version : CVD_Hal[0x%x], CVD_HW[0x%x], CVD_CONTROL[0x%x], CVD_TASK[0x%x] \n", g_CVD_HAL_REV, g_CVD_HW_DRV_REV, g_CVD_CONTROL_DRV_REV, g_CVD_TASK_DRV_REV);
	seq_printf(m, "[CVD Debug] CVD_CMA_POOL = [%d], CVD_USE_TE_SHARED_POOL = [%d], CVD_2d_mode = [%d] \n", g_CVD_CMA_POOL, g_CVD_USE_TE_SHARED_POOL, gCVD_2d_mode);
	seq_printf(m, "[CVD Debug] CVBS_INSEL = [0x%x], CVBS_CP = [0x%x], CVBS_PDB = [0x%x] , CVBS_ICON = [0x%x] \n", cvd_states_detail_t.cvbs_insel, cvd_states_detail_t.cvbs_cp, cvd_states_detail_t.cvbs_pdb, cvd_states_detail_t.cvbs_icon);
	seq_printf(m, "[CVD Debug] BUF_YCM = [0x%x], BUF_SEL1 = [0x%x], BUF_PDB1 = [0x%x], VDAC_PDB= [0x%x] \n", cvd_states_detail_t.buf_ycm, cvd_states_detail_t.buf_sel1, cvd_states_detail_t.buf_pdb1, cvd_states_detail_t.vdac_pdb);
	seq_printf(m, "[CVD Debug] BUF_SEL1[0] = [0:DTV, 1,ATV], BUF_SEL1[1] = [0:Buf Clamp ON, 1:Buf Clamp Off], BUF_SEL1[2] = [0]\n");
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");
	seq_printf(m, "[CVD Debug] Color System= [%d] (1:NT_M, 2:NT_J, 3:NT_443, 4:PAL_BG, 5:PAL_N, 6:PAL_M, 7:PAL_Nc, 8:PAL60, 9:SECAM, 10:Non Standard) \n", cvd_timing_info.cvd_standard);
	seq_printf(m, "[CVD Debug] No Signal = [%d], HLock = [%d], VLock = [%d]\n", cvd_states_detail_t.No_Signal_Flag, cvd_states_detail_t.HLock_Flag, cvd_states_detail_t.VLock_Flag);
	seq_printf(m, "[CVD Debug] VLine 625 = [%d], PAL = [%d], Secam = [%d]\n", cvd_states_detail_t.VLine_625_Flag, cvd_states_detail_t.Pal_Flag, cvd_states_detail_t.Secam_Flag);
	seq_printf(m, "[CVD Debug] Chromalock = [%d], No Burst = [%d] \n", cvd_states_detail_t.Chromalock_Flag, cvd_states_detail_t.NoBurst_Flag);
	seq_printf(m, "[CVD Debug] FC Flag(0:Less, 1:Same, 2:More) = [%d], Cordic Freq = [%d]  \n", cvd_states_detail_t.FC_Flag, cvd_states_detail_t.cvd_cordic_freq);
	seq_printf(m, "[CVD Debug] Status Noise = [%d] \n", cvd_states_detail_t.status_noise);
	//				seq_printf(m, "[CVD Debug] HFcnt = [%d], LFcnt = [%d] \n", cvd_states_detail_t.hfcnt_value, cvd_states_detail_t.lfcnt_value);
	seq_printf(m, "[CVD Debug] Current State = [%d], Next State = [%d] \n", cvd_states_detail_t.Current_State, cvd_states_detail_t.Next_State);

	seq_printf(m, "[CVD Debug] hnon_standard = [%d], vnon_standard = [%d], vdetect_vcount = [%d] \n", cvd_states_detail_t.hnon_standard, cvd_states_detail_t.vnon_standard, cvd_states_detail_t.vdetect_vcount);
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");
	seq_printf(m, "[CVD Debug] CS0 PAL = [%d] ,CS0 Secam = [%d], CS0 Chromalock = [%d] \n"\
			, cvd_states_detail_t.Pal_Flag_CS0, cvd_states_detail_t.Secam_Flag_CS0, cvd_states_detail_t.Chromalock_Flag_CS0);
	seq_printf(m, "[CVD Debug] CS0 FC Flag(0:Less, 1:Same, 2:More) = [%d], CS0 Cordic Freq = [%d] \n"\
			, cvd_states_detail_t.FC_Flag_CS0, cvd_states_detail_t.cvd_cordic_freq_CS0);
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");

	seq_printf(m, "[CVD Debug] CS1 PAL = [%d] ,CS1 Secam = [%d], CS1 Chromalock = [%d] \n"\
			, cvd_states_detail_t.Pal_Flag_CS1, cvd_states_detail_t.Secam_Flag_CS1, cvd_states_detail_t.Chromalock_Flag_CS1);
	seq_printf(m, "[CVD Debug] CS1 FC Flag(0:Less, 1:Same, 2:More) = [%d], CS1 Cordic Freq = [%d] \n"\
			, cvd_states_detail_t.FC_Flag_CS1, cvd_states_detail_t.cvd_cordic_freq_CS1);
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");
	seq_printf(m, "[CVD Debug] CVD Color Standard = [%d], CS0 = [%d], CS1 = [%d]\n"\
			, cvd_states_detail_t.CVD_Color_System, cvd_states_detail_t.CS0_Color_System, cvd_states_detail_t.CS1_Color_System);
	seq_printf(m, "[CVD Debug] System Supported = [0x%x] \n", cvd_states_detail_t.color_system_support);
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");
	seq_printf(m, "[CVD Debug] tnr_x = [0x%x], tnr_s = [0x%x], s_status = [0x%x] \n", cvd_states_detail_t.tnr_x, cvd_states_detail_t.tnr_s, cvd_states_detail_t.s_status);
	seq_printf(m, "[CVD Debug] motion_diff = [%d], global_motioin = [0x%x], pattern_found = [%d] , static_pattern_found = [%d]\n", cvd_states_detail_t.motion_diff, cvd_states_detail_t.motion_value, cvd_states_detail_t.pattern_found, cvd_states_detail_t.static_pattern_found);
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");
	seq_printf(m, "[CVD Debug] agc_gain = [0x%x], agc_peak_en = [%d], agc_bypass = [%d] \n", cvd_states_detail_t.agc_gain, cvd_states_detail_t.agc_peak_en, cvd_states_detail_t.agc_bypass);
	seq_printf(m, "[CVD Debug] burst_mag = [0x%x], cagc = [0x%x], saturation = [0x%x] \n", cvd_states_detail_t.burst_mag, cvd_states_detail_t.cagc, cvd_states_detail_t.saturation);
	seq_printf(m, "[CVD Debug] tunning_mode = [0x%x], stable_count =[%d], no_signal_count = [%d] \n", cvd_states_detail_t.tunning_mode, cvd_states_detail_t.lock_stable_count, cvd_states_detail_t.no_signal_count);
	seq_printf(m, "[CVD Debug] black level = [%d], no_color_detected =[%d] \n", cvd_states_detail_t.black_level, cvd_states_detail_t.no_color_detected);
	seq_printf(m, "[CVD Debug] colorbar diff = [%d] , colorbar 75_100[%d]\n", cvd_states_detail_t.colorbar_diff, cvd_states_detail_t.colorbar_75_100);
	seq_printf(m, "[CVD Debug] Internal_Demod = [%d]\n", cvd_states_detail_t.analog_demod_type);
	seq_printf(m, "[CVD Debug] Status Clamp Up/Down  = [0x%x]\n", cvd_states_detail_t.status_clamp_updn);
	seq_printf(m, "[CVD Debug] --------------------------------------- \n");

	afe_kwrap_cvd_get_crunky_status(&ck_vbi_detection, &number_of_cs);

	seq_printf(m, "[CVD Debug] Crunky PSP	 = [%d] \n", ck_vbi_detection);
	seq_printf(m, "[CVD Debug] Number of CS = [%d] \n", number_of_cs);

	seq_printf(m, "[CVD Debug] End of CVD Timing Info \n");

	return;
}

static void _afe_proc_test_read(struct seq_file *m)
{
	if (!m)	return;

	seq_printf(m, "echo test_num test_param > afe_test\n");
	seq_printf(m, "- test_num : 1 (cve test pattern)\n");
	seq_printf(m, "-- test_param : 0(off), 1(NTSC), 2(PAL)\n");

	return;
}

static void _afe_proc_cvd_prog_colorsystem_read(struct seq_file *m)
{
	if (!m)	return;

	seq_printf(m, "0:Default, 1:NT, 2:NT_J, 3:NT_443, 4:PAL, 5:PAL_N\n");
	seq_printf(m, "6:PAL_M, 7:PAL_CN, 8:PAL_60, 9:SECAM\n");
	seq_printf(m, "echo (0~9) > cvd_prog_color_system\n");

	return;
}

static void _afe_proc_afe_debug_read(struct seq_file *m)
{
	if (!m)	return;

	seq_printf(m, "echo item(number) off/on(0/1) > afe_debug \n");
	seq_printf(m, "AFE_PRINT	[%d] \n", LX_LOGM_LEVEL_NOTI);
	seq_printf(m, "CVD_DEBUG	[%d] \n", LX_LOGM_LEVEL_TRACE);
	seq_printf(m, "AFE_TRACE	[%d] \n", LX_LOGM_LEVEL_TRACE+2);
	seq_printf(m, "AFE_ERROR	[%d] \n", LX_LOGM_LEVEL_ERROR);
	seq_printf(m, "CVD_CSD_DEBUG	[%d] \n", LX_LOGM_LEVEL_TRACE+3);
	seq_printf(m, "CVD_WA_DEBUG	[%d] \n", LX_LOGM_LEVEL_TRACE+4);
	seq_printf(m, "CVD_THREAD_DEBUG[%d] \n", LX_LOGM_LEVEL_TRACE+8);

	return;
}

static ssize_t _afe_proc_afe_debug_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	UINT32 type, onoff;
	int ret;
	__attribute__((unused)) static int count = 0;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "%d %d", &type, &onoff)) != 2) {
		printk("Wrong usage. ret = %d\n", ret);
		return size;
	}

	if(onoff == 0)
	{
		OS_DEBUG_DisableModuleByIndex(g_afe_debug_fd, type);
		printk("AFE_PRINT_TYPE[%d] is disabled.\n", type);
	}
	else
	{
		OS_DEBUG_EnableModuleByIndex(g_afe_debug_fd, type, 0);
		printk("AFE_PRINT_TYPE[%d] is enabled .\n", type);
	}

	return size;
}

static ssize_t _afe_proc_cvd_prog_colorsystem_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	UINT32 value;
	int ret;
	__attribute__((unused)) static int count = 0;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "0x%x", &value)) != 1) {
		if( (ret = sscanf(cmdbuf, "%d", &value)) != 1) {
			printk("Wrong usage. Usage => [0x1234 or 1234](value) : ret = %d\n", ret);
			return size;
		}
	}

	afe_kwrap_cvd_program_color_system(LX_CVD_MAIN, value);
	printk("Program CVD Color System to [%d] .........\n", value);

	return size;
}
static ssize_t _afe_proc_test_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	int index = 0;
	UINT32 value;
	int ret;
	static int count = 0;

	printk("afe_proc_test write [%d] !!! \n", count);
	count ++;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}
	else 
		printk("[%s:%d] size is %zu \n", __F__, __L__, size);

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	printk("[%s:%d] cmdbuf:%s", __F__, __L__, cmdbuf);

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "%d 0x%x", &index, &value)) != 2) {
		if( (ret = sscanf(cmdbuf, "%d %d", &index, &value)) != 2) {
			printk("Wrong usage. Usage => [2](index) [0x1234 or 1234](value) : ret = %d\n", ret);
			return size;
		}
	}

	printk("%s:%d %d 0x%x\n", __func__, __LINE__, index, value);

	//CVD CVE Test Pattern Generation
	if(index == 1) {

		UINT32 top_ctrl_base_addr, data;
		UINT32 reg_cvi0_clk_sel = 0; 

		//PQE_TopCTRL : CVI_CTRL
		if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) ) {
			reg_cvi0_clk_sel = 0xcc4f0010;
			top_ctrl_base_addr = 0xcc4e0000;
		} else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) ) {
			reg_cvi0_clk_sel = 0xCCCD0010;
			top_ctrl_base_addr = 0xcccc0000;
		} else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
			reg_cvi0_clk_sel = 0xCC6A0010;
			top_ctrl_base_addr = 0xcc690000;
		}
		else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
			top_ctrl_base_addr = 0xcc840000;
		else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
			top_ctrl_base_addr = 0xc9000000;
		else 
			return size;

		if(reg_cvi0_clk_sel !=0) {
			SYS_IO_ReadRegArray(reg_cvi0_clk_sel, 4, &data);
			data &= 0xfffffff8; //clear bit [2:0]
			data |= 0x00000006; //set bit [2:0]
			SYS_IO_WriteRegArray(reg_cvi0_clk_sel, 4, &data);
		}

		SYS_IO_ReadRegArray(top_ctrl_base_addr + 0x80, 4, &data);

		if(value == 0) {
			data &= 0xfeffffff; //clear bit [24]
			SYS_IO_WriteRegArray(top_ctrl_base_addr + 0x80, 4, &data);

			SYS_IO_ReadRegArray(top_ctrl_base_addr + 0x84, 4, &data);
			data |= 0x00000007; //set bit [2:0]
			SYS_IO_WriteRegArray(top_ctrl_base_addr + 0x84, 4, &data);
		}
		else if(value == 1) { // NTSC
			data |= 0x01000000; //set bit [24]
			SYS_IO_WriteRegArray(top_ctrl_base_addr + 0x80, 4, &data);

			SYS_IO_ReadRegArray(top_ctrl_base_addr + 0x84, 4, &data);
			data &= 0xfffffff8; //clear bit [2:0]
			SYS_IO_WriteRegArray(top_ctrl_base_addr + 0x84, 4, &data);
		}
		else if(value == 2) { // PAL-BG
			data |= 0x01000000; //set bit [24]
			SYS_IO_WriteRegArray(top_ctrl_base_addr + 0x80, 4, &data);

			SYS_IO_ReadRegArray(top_ctrl_base_addr + 0x84, 4, &data);
			data &= 0xfffffff8; //clear bit [2:0]
			data |= 0x00000001; //set bit [0]
			SYS_IO_WriteRegArray(top_ctrl_base_addr + 0x84, 4, &data);
		}

	}

	return size;
}

static void _afe_proc_cvd_set_colorsystem_read(struct seq_file *m)
{
	if (!m)	return;

	seq_printf(m, "Set Analog Color System \n");
	seq_printf(m, "NTSC:0x1,PAL:0x2,PAL_NC:0x4,PAL_M:0x8 \n");
	seq_printf(m, "SECAM:0x10,NTSC_443:0x20,PAL_60:0x40  \n");
	seq_printf(m, "(0x7F to support all color system)\n ");
	seq_printf(m, "echo (0x1~0x7f) > cvd_set_color_system \n");

	return;
}

static ssize_t _afe_proc_cvd_set_colorsystem_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	UINT32 value;
	int ret;
	__attribute__((unused)) static int count = 0;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "0x%x", &value)) != 1) {
		if( (ret = sscanf(cmdbuf, "%d", &value)) != 1) {
			printk("Wrong usage. Usage => [0x1234 or 1234](value) : ret = %d\n", ret);
			return size;
		}
	}

	afe_kwrap_set_analog_color_system(LX_CVD_MAIN, value);
	printk("Set CVD Color System to [0x%x] .........\n", value);

	return size;
}

static void _afe_proc_cvd_timing_read(struct seq_file *m, void* data)
{
	__attribute__((unused)) int ret = 0;
	LX_AFE_CVD_TIMING_INFO_T cvd_timing_info;
	int sync, isLine625;

	if (!m)	return;

	afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN,&cvd_timing_info);
	afe_kwrap_cvd_sync_exist(LX_CVD_MAIN, &sync);
	if(sync)
		seq_printf(m, "CVD Sync Exist \n");
	else
		seq_printf(m, "CVD NO SIGNAL !!!!! \n");

	seq_printf(m, "Color System= %d (1:NTSC_M, 2:NTSC_J, 3:NTSC_443, 4:PAL_BG, 5:PAL_N, 6:PAL_M, 7:PAL_Cn, 8:PAL60, 9:SECAM, 10:Non Standard) \n", cvd_timing_info.cvd_standard);

//	seq_printf(m, " hFreq= %d (* 100Hz) \n", cvd_timing_info.u16_HFreq);
	seq_printf(m, " vFreq= %d (* 0.1Hz) \n", cvd_timing_info.u16_VFreq);
	seq_printf(m, " hTotal= %d \n", cvd_timing_info.u16_HTotal);
	seq_printf(m, " hStart= %d \n", cvd_timing_info.u16_HStart);
	seq_printf(m, " vStart= %d \n", cvd_timing_info.u16_VStart);
	seq_printf(m, " hActive= %d \n", cvd_timing_info.u16_HSize);
	seq_printf(m, " vActive= %d \n", cvd_timing_info.u16_VSize);
	seq_printf(m, " VFreq_Stable= %d \n", cvd_timing_info.u16_VFreq_Stable);

	afe_kwrap_cvd_read_vfreq(LX_CVD_MAIN, &isLine625); // reg_625line == 1
	if(isLine625) // reg_625line ==1 : 50Hz system
		seq_printf(m, "Field Rate is 50Hz \n");
	else
		seq_printf(m, "Field Rate is 60Hz \n");

	return;
}

static int	AFE_PROC_hex_to_bin(UINT32 hex, UINT32 *binary)
{
	int		number, pow, count, byte;

	if(binary == NULL)
		return -1;

	for (byte =0; byte < 4; byte++)
	{
		binary[byte] = 0;
		for(number = 0; number <8; number++)
		{
			if(hex & (1 << (number + (byte * 8)) ))
			{
				pow = 1;
				for(count=0; count < number; count++)
				{
					pow *= 10;
				}
				binary[byte] += pow;
			}
		}
	}

	return 0;
}

/*
 * read_proc implementation of afe device
 *
*/
static int	_AFE_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer, 96, "%s\n", "wonsik.do (wonsik.do@lge.com) : 24013000" );
		}
		break;

		case PROC_ID_CVD_CONN_MODULE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo port(1~2) type(0:rf, 1:av) > cvd_conn_module");
		}
		break;

		case PROC_ID_CVD_SOURCE_TYPE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo port(1~2) type(0:rf, 1:av) > cvd_source_type");
		}
		break;

		case PROC_ID_CVD_PDB:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0:off, 1:on) > cvd_pdb");
		}
		break;
		case PROC_ID_CVD_TIMER:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0:off, 1:on) > cvd_timer");
		}
		break;
		case PROC_ID_CVD_TUNNING_MODE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0:off, 1:on) > cvd_tunning_mode");
		}
		break;
		case PROC_ID_CVD_BLUE_MODE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0:Disable, 1:Enable, 2:Auto) > cvd_blue_mode");
		}
		break;
		case PROC_ID_CVD_YC_BLEND:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0x0:2DComb, 0x5:3D Only, 0xF:Blend Mode) > cvd_yc_blend");
		}
		break;
		case PROC_ID_CVD_CLAMP_UP_DOWN:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0x0:Normal Clamping, 0x10:Clamp Off, 0x11:Clamp Dn, 0x12:Clamp Up) > cvd_clamp_up_down");
		}
		break;
		case PROC_ID_CVD_CLAMP_MODE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (0x0:auto, 0x1:backporch only, 0x2:synctip only, 0x3:off) > cvd_clamp_mode");
		}
		break;
		case PROC_ID_CVD_SYNC_TUNNING_MODE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo (1 : HLock, 2:VLock, 3:HLock or Vlock, 4:HLock AND VLock) > cvd_sync_tunning_mode");
		}
		break;

		case PROC_ID_SYS_REG_READ:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo addr(hex) > sys_reg_read");
		}
		break;

		case PROC_ID_SYS_REG_WRITE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo addr(hex) data(hex) > sys_reg_write");
		}
		break;

		case PROC_ID_CVD_REG_READ:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo offset addr(hex) > sys_reg_read");
		}
		break;

		case PROC_ID_CVD_REG_WRITE:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo offset addr(hex) data(hex) > sys_reg_write");
		}
		break;

		case PROC_ID_CVD_WA:
		{
			ret = snprintf( buffer, 96, "%s\n", "echo wa_number 0/1 > cvd_wa");
		}
		break;

		case PROC_ID_PM_TEST :
		{
			ret = v4l2_avd_pm_runtime_help(buffer);
		}break;


		default:
		{
			ret = snprintf( buffer, 96, "%s(%d)\n", "unimplemented read proc", procId );
		}
		break;
	}

	return ret;
}

/*
 * write_proc implementation of afe device
 *
*/
static int _AFE_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("command string : %s\n", command );
		}
		break;

		case PROC_ID_CVD_INIT:
		{
			UINT32 offON = 0; // 0:off, 1:on
			sscanf( command, "%d", &offON);

			if(offON == 1)
			{
				printk("INIT CVD .........\n");
				CVD_Init(LX_CVD_MAIN);
			}
			else
			{
				printk("UnInit CVD .........\n");
				CVD_UnInit();
			}
		}
		break;
		case PROC_ID_CVD_INIT_MODULE:
		{
			UINT32 offON = 0; // 0:off, 1:on
			sscanf( command, "%d", &offON);

			if(offON == 1)
			{
				printk("INIT CVD module .........\n");
				afe_kwrap_cvd_initializemodule();
			}
			else
			{
				printk("UnInit CVD module .........\n");
				afe_kwrap_cvd_uninitializemodule();
			}
		}
		break;
		case PROC_ID_CVD_CONN_MODULE:
		{
			UINT32 port = 0; // 0:off, 1:on
			UINT32 type = 0; // 0:off, 1:on

			sscanf( command, "%d %d", &port, &type);

			printk("CVD connect module port[%d] type [%d]\n", port, type);

			afe_kwrap_cvd_connectmodule(type, port);
		}
		break;
		case PROC_ID_CVD_SOURCE_TYPE:
		{
			UINT32 port = 0; // 0:off, 1:on
			UINT32 type = 0; // 0:off, 1:on
			LX_AFE_CVD_SET_INPUT_T	cvd_input_info;

			sscanf( command, "%d %d", &port, &type);

			cvd_input_info.cvd_main_sub = LX_CVD_MAIN;
			cvd_input_info.cvd_input_source_type = LX_CVD_INPUT_SOURCE_CVBS;
			cvd_input_info.cvbs_input_port	= port;
			cvd_input_info.chroma_input_port = 0;
			cvd_input_info.cvd_input_source_attribute = type;

			printk("CVD port[%d] type [%d]\n", port, type);

			CVD_Set_Source_Type_Control(cvd_input_info);
		}
		break;

		case PROC_ID_CVD_PDB:
		{
			UINT32 offON = 0; // 0:off, 1:on
			sscanf( command, "%d", &offON);

			if(offON == 1)
			{
				printk("Turning on CVBS.........\n");
				CVD_Channel_Power_Control(1);
			}
			else
			{
				printk("Turning off CVBS.........\n");
				CVD_Channel_Power_Control(0);
			}
		}
		break;

		case PROC_ID_CVD_TIMER:
		{
			UINT32 offON = 0; // 0:off, 1:on
			sscanf( command, "%d", &offON);

			if(offON == 1)
			{
				printk("Turning on CVD Thread .........\n");
				afe_kwrap_cvd_start_timer(LX_CVD_MAIN, 0);
			}
			else
			{
				printk("Turning off CVD Thread .........\n");
				afe_kwrap_cvd_stop_timer(LX_CVD_MAIN);
			}
		}
		break;

		case PROC_ID_CVD_TUNNING_MODE:
		{
			UINT32 offON = 0; // 0:off, 1:on
			sscanf( command, "%d", &offON);

			if(offON == 1)
			{
				printk("CVD set tunning mode .........\n");
				afe_kwrap_cvd_setsyncdetectionfortuning(TRUE);
			}
			else
			{
				printk("CVD exit from tunning mode .........\n");
				afe_kwrap_cvd_setsyncdetectionfortuning(FALSE);
			}
		}
		break;

		case PROC_ID_CVD_BLUE_MODE:
		{
			UINT32 mode = 0;
			sscanf( command, "%d", &mode);

			CVD_Set_Blue_Mode(mode);
			printk("CVD set blue mode [%d] .........\n", mode );
		}
		break;
		case PROC_ID_CVD_YC_BLEND:
		{
			UINT32 mode = 0;
			sscanf( command, "%x", &mode);

			CVD_Set_ycsep_Blend(mode);
			printk("CVD set YC blend mode [0x%x] .........\n", mode );
		}
		break;
		case PROC_ID_CVD_CLAMP_UP_DOWN:
		{
			UINT32 mode = 0;
			sscanf( command, "%x", &mode);

			CVD_Set_clampagc_updn(mode);
			printk("CVD set clampagc updn [0x%x] .........\n", mode );
		}
		break;
		case PROC_ID_CVD_CLAMP_MODE:
		{
			UINT32 mode = 0;
			sscanf( command, "%x", &mode);

			CVD_Set_dc_clamp_mode(mode);
			printk("CVD set DC Clamp mode [0x%x] .........\n", mode );
		}
		break;
		case PROC_ID_CVD_SYNC_TUNNING_MODE:
		{
			UINT32 mode = 0;
			sscanf( command, "%d", &mode);

			printk("Sync Check in ATV Auto Search [%d]=>[%d] \n", g_CVD_status_to_check_ATV_Search, mode);

			g_CVD_status_to_check_ATV_Search = mode;
		}
		break;

		case PROC_ID_SYS_REG_READ:
		{
			UINT32 addr, data, binary[4];
			sscanf( command, "%x", &addr);
			SYS_IO_ReadRegArray(addr, 4, &data);
//			printk("\nsys read addr:0x%x data:0x%x\n", addr, data);
			AFE_PROC_hex_to_bin(data, binary);
			printk("\n                    [addr] = [  32211000] [33222222|22221111|11111100|00000000]\n");
			printk("                             [  14365870] [10987654|32109876|54321098|76543210]\n");
			printk("Sys Read Data [0x%08x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, data, binary[3], binary[2], binary[1], binary[0]);
		}
		break;

		case PROC_ID_SYS_REG_WRITE:
		{
			UINT32 addr, data, read_data, binary[4];
			sscanf( command, "%x %x", &addr, &data);
			SYS_IO_ReadRegArray(addr, 4, &read_data);
//			printk("\nsys before addr:0x%x data:0x%x\n", addr, read_data);
			AFE_PROC_hex_to_bin(read_data, binary);
			printk("\n                    [addr] = [  32211000] [33222222|22221111|11111100|00000000]\n");
			printk("                             [  14365870] [10987654|32109876|54321098|76543210]\n");
			printk("Sys BeforeData[0x%08x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, read_data, binary[3], binary[2], binary[1], binary[0]);
			SYS_IO_WriteRegArray(addr, 4, &data);
//			printk("sys write addr:0x%x data:0x%x\n", addr, data);
			AFE_PROC_hex_to_bin(data, binary);
			printk("Sys WriteData [0x%08x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, data, binary[3], binary[2], binary[1], binary[0]);
			SYS_IO_ReadRegArray(addr, 4, &read_data);
//			printk("sys check addr:0x%x data:0x%x\n", addr, read_data);
			AFE_PROC_hex_to_bin(read_data, binary);
			printk("Sys After Data[0x%08x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, read_data, binary[3], binary[2], binary[1], binary[0]);
		}
		break;

		case PROC_ID_CVD_REG_READ:
		{
			UINT32 addr, binary[4];
			LX_AFE_REG_RW_T reg_addr_data_t;
			sscanf( command, "%x", &addr);

			reg_addr_data_t.addr = addr;

			CVD_Vport_Reg_Read(&reg_addr_data_t);

			//printk("\ncvd read addr:0x%x data:0x%x\n", addr, reg_addr_data_t.data);
			AFE_PROC_hex_to_bin(reg_addr_data_t.data, binary);
			printk("\n                [addr] = [  32211000] [33222222|22221111|11111100|00000000]\n");
			printk("                         [  14365870] [10987654|32109876|54321098|76543210]\n");
			printk("CVD Read Data [0x%04x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, reg_addr_data_t.data, binary[3], binary[2], binary[1], binary[0]);
		}
		break;

		case PROC_ID_CVD_REG_WRITE:
		{
			UINT32 addr, data, binary[4];
			LX_AFE_REG_RW_T reg_addr_data_t;
			sscanf( command, "%x %x", &addr, &data);

			reg_addr_data_t.addr = addr;

			CVD_Vport_Reg_Read(&reg_addr_data_t);
			//printk("\ncvd before addr:0x%x data:0x%x\n", addr, reg_addr_data_t.data);
			AFE_PROC_hex_to_bin(reg_addr_data_t.data, binary);
			printk("\n                [addr] = [  32211000] [33222222|22221111|11111100|00000000]\n");
			printk("                         [  14365870] [10987654|32109876|54321098|76543210]\n");
			printk("CVD BeforeData[0x%04x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, reg_addr_data_t.data, binary[3], binary[2], binary[1], binary[0]);
			reg_addr_data_t.data = data;
			CVD_Vport_Reg_Write(&reg_addr_data_t);
//			printk("cvd write addr:0x%x data:0x%x\n", addr, reg_addr_data_t.data);
			AFE_PROC_hex_to_bin(reg_addr_data_t.data, binary);
			printk("CVD WriteData [0x%04x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, reg_addr_data_t.data, binary[3], binary[2], binary[1], binary[0]);
			CVD_Vport_Reg_Read(&reg_addr_data_t);
			//printk("cvd check addr:0x%x data:0x%x\n", addr, reg_addr_data_t.data);
			AFE_PROC_hex_to_bin(reg_addr_data_t.data, binary);
			printk("CVD After Data[0x%04x] = [0x%08x] [%08d|%08d|%08d|%08d]\n", addr, reg_addr_data_t.data, binary[3], binary[2], binary[1], binary[0]);
		}
		break;

		case PROC_ID_CVD_WA:
		{
			LX_AFE_CVD_TEST_PARAM_T CVD_Test_Param;

			sscanf( command, "%d %d", &CVD_Test_Param.workaround_number, &CVD_Test_Param.workaround_on_off);

			CVD_Test_Param.item_to_test = CVD_TEST_WORKAROUND_CONTROL;

			CVD_Test_Program(&CVD_Test_Param);
		}
		break;

		case PROC_ID_PM_TEST:
		{
			v4l2_avd_pm_runtime_test(command);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

static int afe_proc_show_version(struct seq_file *m, void *v)
{
    char chip_name[8];

	if (!m)	return 0;

	memset(chip_name,0,8);
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )			snprintf(chip_name, 8, "o26");
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )			snprintf(chip_name, 8, "o24");
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) )			snprintf(chip_name, 8, "m23");
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )			snprintf(chip_name, 8, "o22");
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )			snprintf(chip_name, 8, "e60");
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )			snprintf(chip_name, 8, "o20");
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M19) )	snprintf(chip_name, 8, "m16p3");
	seq_printf(m, "chip_name=%s\n",chip_name);

	return 0;
}

static int avd_proc_show(struct seq_file *m, void *v)
{
	AVD_DEV_INFO_T *avd_dev = NULL;

	if (!m)	return 0;

	avd_dev = &avd_device_info;

	afe_proc_show_version(m,v);

	if(gCVDInitStatus == FALSE)
	{
		seq_printf(m, "CVD Not Initialized !!!!!\n");
		return 0;
	}

	avd_update_device_info();

	seq_printf(m, "open=%d\n",avd_dev->avd_open);
	seq_printf(m, "input_src=%d\n",avd_dev->avd_input_src);
	seq_printf(m, "hwport=%d\n",avd_dev->hwport);
	seq_printf(m, "timing_h_freq=%d\n",avd_dev->avd_timing_info.u16_HFreq);
	seq_printf(m, "timing_v_freq=%d\n",avd_dev->avd_timing_info.u16_VFreq);
	seq_printf(m, "timing_h_porch=%d\n",avd_dev->avd_timing_info.u16_HStart);
	seq_printf(m, "timing_v_porch=%d\n",avd_dev->avd_timing_info.u16_VStart);
	seq_printf(m, "timing_active_w=%d\n",avd_dev->avd_timing_info.u16_HSize);
	seq_printf(m, "timing_active_h=%d\n",avd_dev->avd_timing_info.u16_VSize);
	seq_printf(m, "timing_active_x=%d\n",0);
	seq_printf(m, "timing_active_y=%d\n",0);
	seq_printf(m, "timing_vd_lock=%d\n",avd_dev->vd_lock);
	seq_printf(m, "timing_v_lock=%d\n",avd_dev->v_lock);
	seq_printf(m, "timing_h_lock=%d\n",avd_dev->h_lock);
	seq_printf(m, "avd_sync=%d\n",avd_dev->avd_sync);
	seq_printf(m, "color_standard=%d\n",avd_dev->color_standard);
	seq_printf(m, "auto_tunning_mode=%d\n",avd_dev->auto_tuning_mode);
	seq_printf(m, "noise_level=%d\n",avd_dev->noise_level);

    return 0;
}


static int avd_proc_open(struct inode *inode, struct file *file)
{
	int ret;

	if (!file)	return 0;

	ret = single_open (file, avd_proc_show, NULL);
	if (ret < 0)
		return ret;

	return ret;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static struct proc_ops avd_proc_fops = {
	.proc_open = avd_proc_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations avd_proc_fops = {
	.open = avd_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
/**
 * initialize proc utility for afe device
 *
 * @see AFE_Init
*/
void	AFE_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( AFE_MODULE, _g_afe_device_proc_table,
											_AFE_ReadProcFunction,
											_AFE_WriteProcFunction );
	{
		struct proc_dir_entry *proc_avd;
		struct proc_dir_entry *proc_entry = OS_PROC_GetLinuxTvEntry();

		if (!proc_entry)
		{
			printk("proc_entry is not ready\n");
			return;
		}

		proc_avd = proc_mkdir("avd-status", proc_entry);

		proc_create_data("avd", 0440, proc_avd, &avd_proc_fops, NULL);
	}
}

/**
 * cleanup proc utility for afe device
 *
 * @see AFE_Cleanup
*/
void	AFE_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( AFE_MODULE );
}


/** @} */

