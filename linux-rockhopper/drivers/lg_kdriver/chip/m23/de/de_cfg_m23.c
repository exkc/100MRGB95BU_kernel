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
 *  @author		justine.jeong
 *  @version	1.0
 *  @date		2018-05-29
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include "os_util.h"
#include "hma_alloc.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "de_kapi.h"
#include "de_cfg.h"
#include "de_cfg_m23.h"

#ifdef INCLUDE_KDRV_BE
#include "ovi_hal.h"
#endif
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define DE_CFG_ENTRY(_g,_m)	{.number=(sizeof(_g)/sizeof(_g[0])),.group=(_g),.map=&(_m)}
#define DE_CFG_ENTRY_END	{.number=0,.group=NULL,.map=NULL}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct de_cfg_map_entry
{
	UINT32 number;
	LX_MEMCFG_T **group;
	LX_MEMCFG_T *map;
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
#ifdef USE_VIDEO_FOR_FPGA
int g_de_cfg_m23_pqe_map = 0;//0:FPGA,1:ASIC
#else
int g_de_cfg_m23_pqe_map = 1;//0:FPGA,1:ASIC
#endif
module_param_named(m23_pqe_map, g_de_cfg_m23_pqe_map, int, 0644);

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
void de_cfg_m23_print_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LX_DE_IPC_SYSTEM_MODEL_T _g_de_cfg_m23_system = {.u32Data = 0,};
static struct de_cfg_map_entry *_gp_map_entry = NULL;

/************************************************************/
/* M23 */
/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_m23[] = {
	&g_de_svp_m0,
	&g_de_svp_m1,
	&g_de_svp_m2,
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_m23[] = {
	&g_be_fpp,
	&g_be_frc0,
	&g_be_frc1,
	&g_be_frc2,
	&g_de_nsvp_m1,
	&g_de_nsvp_m2,
	&g_de_hdr,
	&g_be_wcg,
	&g_be_led,
	&g_be_phdr,
	&g_chipinfo,
	&g_pe_db,
	&g_pe_hdr,
	&g_fw_dnn,
	&g_fw_mcu0,
	&g_fw_mcu1,
	&g_fw_mcu2,
	&g_fw_mcu3,
	&g_fw_mcu4,
	&g_fw_shared,
	&g_m0_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m0_usr_m23[] = {
	&g_de_vt_m1,
	&g_de_vt_m2,
	&g_m0_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_m23[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_m23,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_m23,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_m23,g_m0_pqe_usr),
	DE_CFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_cfg_m23_get_hw_opt(UINT32 *opt)
{
#ifdef INCLUDE_KDRV_BE
	LX_DE_IPC_SYSTEM_MODEL_T panel_mode;
	LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
	int ret = RET_OK;

	panel_mode.u32Data = 0;

	ret = OVI_HAL_GetHWDisplayOption(&ovi_opt);
	if (ret == RET_OK)
	{
		if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
		{
			panel_mode.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz;
		}
		else if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ_FIXED)
		{
			panel_mode.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz_FIXED;
		}

		if (ovi_opt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
		{
			panel_mode.panel_type = LX_DE_IPC_PANEL_TYPE_OLED;
		}
		else if (ovi_opt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_NONE)
		{
			panel_mode.panel_type = LX_DE_IPC_PANEL_TYPE_BOX;
		}

		if (ovi_opt.isVx15Byte)
		{
			panel_mode.vx1_byte  = LX_DE_IPC_PANEL_VX1_5BYTE;
		}

		if (ovi_opt.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
		{
			panel_mode.external_chip  = LX_DE_IPC_EXTERNAL_CHIP_USE;
		}

		if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
		{
			panel_mode.panel_resolution = LX_DE_IPC_PANEL_RESOLUTION_1920x1080;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1366X768)
		{
			panel_mode.panel_resolution = LX_DE_IPC_PANEL_RESOLUTION_1366x768;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1280X720)
		{
			panel_mode.panel_resolution = LX_DE_IPC_PANEL_RESOLUTION_1280x720;
		}
	}

	if (RET_OK == OS_ScanKernelCmdlineToken("WirelessAV"))
	{
		panel_mode.ext_wireless_chip = LX_DE_IPC_EXT_WIRELESS_CHIP_USE;
	}
	
	*opt = panel_mode.u32Data;
#else
	*opt = 0;
#endif

	return RET_OK;
}

int de_cfg_m23_preinit(void)
{
	UINT32 i, size, number;
	struct de_cfg_map_entry *p_entry;
	LX_MEMCFG_T *p_group, *p_map;

	de_cfg_m23_get_hw_opt(&_g_de_cfg_m23_system.u32Data);

	DE_NOTI("hw_opt:0x%08x\n",_g_de_cfg_m23_system.u32Data);

	if (_g_de_cfg_m23_system.panel_resolution == LX_DE_IPC_PANEL_RESOLUTION_1920x1080 || _g_de_cfg_m23_system.panel_resolution == LX_DE_IPC_PANEL_RESOLUTION_1366x768)
	{
		DE_NOTI("map : FHD\n");
		g_de_cfg_m23_pqe_map = 2;
	}

	if (g_de_cfg_m23_pqe_map == 2)//ASIC (AVTASK-885)(M23_wo_MEMC (1GB))
	{
		g_de_svp_m0.size  =   0*1024*1024;
		g_de_svp_m1.size  =   6*1024*1024;
		g_de_svp_m2.size  =  18*1024*1024;
		g_be_fpp.size     =   0*1024*1024;
		g_be_frc0.size    =   0*1024*1024;
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_de_nsvp_m1.size =   0*1024*1024;
		g_de_nsvp_m2.size =   0*1024*1024;
		g_de_vt_m1.size   =  10*1024*1024;//Y: VTG:720p420 x3(2.6MB), GAV:720p420 x2 x4 (7.4MB)
		g_de_vt_m2.size   =   5*1024*1024;//C: VTG:720p420 x3(1.5MB), GAV:720p420 x2 x4 (3.5MB)
		g_de_hdr.size     =   0*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_be_led.size     =      128*1024;
		g_be_phdr.size    =       32*1024;
		g_chipinfo.size   =   0*1024*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =   0*1024*1024;
		g_fw_mcu0.size    =   4*1024*1024;
		g_fw_mcu1.size    =   0*1024*1024;
		g_fw_mcu2.size    =   0*1024*1024;
		g_fw_mcu3.size    =   0*1024*1024;
		g_fw_mcu4.size    =   0*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_de_dbg_m1.size  =  23*1024*1024;
		g_de_dbg_m2.size  =   0*1024*1024;

		g_de_vt_m1_cma_size = 2700*1024;//Y: VTG:720p420 x3(2.6MB)
		g_de_vt_m2_cma_size = 1350*1024;//C: VTG:720p420 x3(1.5MB)
		g_de_vdec_shared_size = 16*1024*1024;
	}
	else if (g_de_cfg_m23_pqe_map == 1)//ASIC (AVTASK-769)(M23 (Capture) (220321))
	{
		g_de_svp_m0.size  =   0*1024*1024;
		g_de_svp_m1.size  =  19*1024*1024;//0502,22->19,0419,27->22(AVTASK-786)
		g_de_svp_m2.size  =  55*1024*1024;//0502,61->55,0419,74->61(AVTASK-786)
		g_be_fpp.size     =  15*1024*1024;//0502,17->15,0419,19->17(AVTASK-786)
		g_be_frc0.size    =  25*1024*1024;//0502,30->25,0419,34->30(AVTASK-786)
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_de_nsvp_m1.size =   0*1024*1024;
		g_de_nsvp_m2.size =   0*1024*1024;
		g_de_vt_m1.size   =  16*1024*1024;//Y: VTG:4K420 x1(8MB), GAV:720p420 x2 x4 (8MB)
		g_de_vt_m2.size   =   8*1024*1024;//C: VTG:4K420 x1(4MB), GAV:720p420 x2 x4 (4MB)
		g_de_hdr.size     =   0*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_be_led.size     =      128*1024;
		g_be_phdr.size    =       32*1024;
		g_chipinfo.size   =   0*1024*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =   0*1024*1024;//FRC share : 0MB
		g_fw_mcu0.size    =   4*1024*1024;
		g_fw_mcu1.size    =   0*1024*1024;
		g_fw_mcu2.size    =   0*1024*1024;
		g_fw_mcu3.size    =   0*1024*1024;
		g_fw_mcu4.size    =   0*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_de_dbg_m1.size  =  91*1024*1024;
		g_de_dbg_m2.size  =   0*1024*1024;

		g_de_vt_m1_cma_size = 8*1024*1024;//Y: VTG:4K420 x1(8MB)
		g_de_vt_m2_cma_size = 4*1024*1024;//C: VTG:4K420 x1(4MB)
		g_de_vdec_shared_size = 64*1024*1024;
	}
	else//FPGA (AVTASK-722)
	{
		g_de_svp_m0.size  =  64*1024*1024;
		g_de_svp_m1.size  =  27*1024*1024;
		g_de_svp_m2.size  =  74*1024*1024;
		g_be_fpp.size     =  19*1024*1024;
		g_be_frc0.size    =  34*1024*1024;
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_de_nsvp_m1.size =   0*1024*1024;
		g_de_nsvp_m2.size =   0*1024*1024;
		g_de_vt_m1.size   =  24*1024*1024;
		g_de_vt_m2.size   =  12*1024*1024;
		g_de_hdr.size     =   0*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_be_led.size     =      128*1024;
		g_be_phdr.size    =       32*1024;
		g_chipinfo.size   =   0*1024*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =   8*1024*1024;
		g_fw_mcu0.size    =   4*1024*1024;
		g_fw_mcu1.size    =   0*1024*1024;
		g_fw_mcu2.size    =   0*1024*1024;
		g_fw_mcu3.size    =   0*1024*1024;
		g_fw_mcu4.size    =   0*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_de_dbg_m1.size  =  91*1024*1024;
		g_de_dbg_m2.size  =   0*1024*1024;

		g_de_vt_m1_cma_size = 8*1024*1024;
		g_de_vt_m2_cma_size = 4*1024*1024;
		g_de_vdec_shared_size = 0;
	}

	_gp_map_entry = _g_map_entry_m23;

	/* collect size's from members */
	p_entry = _gp_map_entry;
	while (p_entry && p_entry->number>0 && p_entry->group && p_entry->map)
	{
		number = p_entry->number;
		p_map = p_entry->map;

		for (i=0,size=0; i<number; i++)
		{
			p_group = p_entry->group[i];
			size += LX_CALC_ALIGNED_VALUE(p_group->size,DE_CFG_ALIGN_VALUE);
			//DE_NOTI("%-15s = num:%2d, size:%4d MB\n",p_group->name,i,p_group->size/1024/1024);
		}

		p_map->size = size;
		DE_NOTI("%-15s = num:%2d, size:%4d MB\n",p_map->name,number,size/1024/1024);

		p_entry++;
	}

	return 0;
}

int de_cfg_m23_init(void)
{
	UINT64 hma_addr = 0;
	UINT32 hma_size = 0;
	UINT32 i, number, prev_base, prev_size, base, size;
	struct de_cfg_map_entry *p_entry = _gp_map_entry;
	LX_MEMCFG_T *p_group, *p_map;

	/* distribute address's to the members */
	while (p_entry && p_entry->number>0 && p_entry->group && p_entry->map)
	{
		number = p_entry->number;
		p_map = p_entry->map;

		prev_base = p_map->base;
		for (i=0,prev_size=0; i<number; i++) {
			p_group = p_entry->group[i];
			p_group->base = prev_base+prev_size;
			prev_base = p_group->base;
			prev_size = LX_CALC_ALIGNED_VALUE(p_group->size,DE_CFG_ALIGN_VALUE);
		}

		base = p_map->base;
		size = p_map->size/1024/1024;
		DE_NOTI("%-15s = num:%2d, base:0x%08x, size:%4d MB\n",p_map->name,number,base,size);

		p_entry++;
	}

	if ( 0 == hma_pool_info("debug0",(phys_addr_t *)&hma_addr,&hma_size) )
	{
		p_map = &g_de_dbg_m1;
		p_map->base = (UINT32)(hma_addr & 0xFFFFFFFF);
		if (p_map->size > hma_size)	p_map->size = hma_size;

		base = p_map->base;
		size = p_map->size/1024/1024;
		DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p_map->name,base,size);
	}

	#if 0	//not support
	if ( 0 == hma_pool_info("debug1",(phys_addr_t *)&hma_addr,&hma_size) )
	{
		p_map = &g_de_dbg_m2;
		p_map->base = (UINT32)(hma_addr & 0xFFFFFFFF);
		if (p_map->size > hma_size)	p_map->size = hma_size;

		base = p_map->base;
		size = p_map->size/1024/1024;
		DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p_map->name,base,size);
	}
	#endif

	return 0;
}

int de_cfg_m23_cleanup(void)
{
	//TODO:
	return 0;
}

extern LX_MEMCFG_T de_reg_m23_getmeminfo(char* str);
void de_cfg_m23_print_status(struct seq_file *m)
{
	char *name;
	UINT32 i, base, size;
	LX_MEMCFG_T meminfo;
	struct de_cfg_map_entry *p_entry = _gp_map_entry;

	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s = %-10s, %7s\n", "name", "base", "size");

	while (p_entry && p_entry->number>0 && p_entry->group && p_entry->map)
	{
		name = p_entry->map->name;
		base = p_entry->map->base;
		size = p_entry->map->size;
		seq_printf(m, "==========================================================\n");
		seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
		seq_printf(m, "----------------------------------------------------------\n");

		for (i=0; i<p_entry->number; i++)
		{
			name = p_entry->group[i]->name;
			base = p_entry->group[i]->base;
			size = p_entry->group[i]->size;
			seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
		}

		p_entry++;
	}
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "dbg");
	seq_printf(m, "----------------------------------------------------------\n");
	name = g_de_dbg_m1.name;
	base = g_de_dbg_m1.base;
	size = g_de_dbg_m1.size;
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
	name = g_de_dbg_m2.name;
	base = g_de_dbg_m2.base;
	size = g_de_dbg_m2.size;
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "etc");
	seq_printf(m, "----------------------------------------------------------\n");
	name = "vdec_pool_0";
	meminfo = de_reg_m23_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	name = "vdec_pool_1";
	meminfo = de_reg_m23_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	name = "lne_pool";
	meminfo = de_reg_m23_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	seq_printf(m, "%-20s = %4d MB (%10d B)\n", "g_de_vt_m1_cma_size", g_de_vt_m1_cma_size/1024/1024, g_de_vt_m1_cma_size);
	seq_printf(m, "%-20s = %4d MB (%10d B)\n", "g_de_vt_m2_cma_size", g_de_vt_m2_cma_size/1024/1024, g_de_vt_m2_cma_size);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vdec_shared_size", g_de_vdec_shared_size/1024/1024);
	seq_printf(m, "==========================================================\n");
}

