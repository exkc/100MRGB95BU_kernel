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
#include "de_ver_def.h"
#include "de_def.h"
#include "de_kapi.h"
#include "de_cfg.h"
#include "de_cfg_o20.h"

#ifdef INCLUDE_KDRV_BE
#include "ovi_hal.h"
#endif
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 3GB:o20, 2GB:o20t_nmrm */
#define DE_CFG_O20_DDR_3GB	(0)
#define DE_CFG_O20_DDR_2GB	(1)

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

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LX_DE_IPC_SYSTEM_MODEL_T _g_de_cfg_o20_system = {.u32Data = 0,};
static struct de_cfg_map_entry *_gp_map_entry = NULL;

/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_o20[] = {
	&g_de_svp_m0,
	&g_de_svp_m1,
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_o20[] = {
	&g_fw_mcu0,
	&g_fw_mcu2,
	&g_fw_mcu3,
	&g_fw_mcu4,
	&g_de_nsvp_m1,
	&g_be_fpp,
	&g_de_hdr,
	&g_fw_shared,
	&g_be_wcg,
	&g_be_led,
	&g_be_phdr,
	&g_pe_db,
	&g_pe_hdr,
	&g_m0_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m0_usr_o20[] = {
	&g_de_vt_m1,
	&g_m0_pqe_usr_end
};
static LX_MEMCFG_T *_gp_group_m1_svp_o20[] = {
	&g_de_svp_m2,
	&g_m1_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m1_nsv_o20[] = {
	&g_fw_mcu1,
	&g_de_nsvp_m2,
	&g_be_frc0,
	&g_be_frc1,
	&g_be_frc2,
	&g_fw_dnn,
	&g_chipinfo,
	&g_m1_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m1_usr_o20[] = {
	&g_de_vt_m2,
	&g_m1_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_o20[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_o20,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_o20,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_o20,g_m0_pqe_usr),
	DE_CFG_ENTRY(_gp_group_m1_svp_o20,g_m1_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m1_nsv_o20,g_m1_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m1_usr_o20,g_m1_pqe_usr),
	DE_CFG_ENTRY_END
};

/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_o20_2GB[] = {
	&g_de_svp_m0,
	&g_de_svp_m1,
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_o20_2GB[] = {
	&g_fw_mcu0,
	&g_fw_mcu2,
	&g_fw_mcu3,
	&g_fw_mcu4,
	&g_de_nsvp_m1,
	&g_be_fpp,
	&g_de_hdr,
	&g_fw_shared,
	&g_be_wcg,
	&g_be_led,
	&g_be_phdr,
	&g_pe_db,
	&g_pe_hdr,
	&g_m0_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m0_usr_o20_2GB[] = {
	&g_de_vt_m1,
	&g_m0_pqe_usr_end
};
static LX_MEMCFG_T *_gp_group_m1_svp_o20_2GB[] = {
	&g_de_svp_m2,
	&g_m1_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m1_nsv_o20_2GB[] = {
	&g_fw_mcu1,
	&g_de_nsvp_m2,
	&g_be_frc0,
	&g_be_frc1,
	&g_be_frc2,
	&g_fw_dnn,
	&g_chipinfo,
	&g_m1_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m1_usr_o20_2GB[] = {
	&g_de_vt_m2,
	&g_m1_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_o20_2GB[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_o20_2GB,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_o20_2GB,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_o20_2GB,g_m0_pqe_usr),
	DE_CFG_ENTRY(_gp_group_m1_svp_o20_2GB,g_m1_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m1_nsv_o20_2GB,g_m1_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m1_usr_o20_2GB,g_m1_pqe_usr),
	DE_CFG_ENTRY_END
};
/************************************************************/

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_KDRV_BE
int de_cfg_o20_get_hw_opt(UINT32 *opt)
{
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

	return RET_OK;
}
#endif

int de_cfg_o20_preinit(void)
{
	UINT32 i, size, number, ddr_type = DE_CFG_O20_DDR_3GB;
	struct de_cfg_map_entry *p_entry;
	LX_MEMCFG_T *p_group, *p_map;

#ifdef INCLUDE_KDRV_BE
	de_cfg_o20_get_hw_opt(&_g_de_cfg_o20_system.u32Data);
	DE_NOTI("hw_opt:0x%08x\n",_g_de_cfg_o20_system.u32Data);
#endif

#ifdef SUPPORT_NMRM_PLATFORM
	if (_g_de_cfg_o20_system.panel_resolution == LX_DE_IPC_PANEL_RESOLUTION_1920x1080)
	{
		ddr_type = DE_CFG_O20_DDR_2GB;
	}
#endif

	if (ddr_type == DE_CFG_O20_DDR_2GB)
	{
		g_fw_mcu0.size    =   4*1024*1024;
		g_de_svp_m0.size  =   0*1024*1024;
		g_de_svp_m1.size  =   5*1024*1024;
		g_de_svp_m2.size  =   5*1024*1024;
		g_de_nsvp_m1.size =  50*1024*1024;
		g_de_nsvp_m2.size =  58*1024*1024;
		g_de_vt_m1.size   =  35*1024*1024;
		g_de_vt_m2.size   =  12*1024*1024;
		g_de_hdr.size     =   3*1024*1024;
		g_be_fpp.size     =  14*1024*1024;
		g_be_frc0.size    =  69*1024*1024;
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =  24*1024*1024;
		g_fw_mcu1.size    =   4*1024*1024;
		g_fw_mcu2.size    =  22*1024*1024;
		g_fw_mcu3.size    =   2*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_fw_mcu4.size    =   2*1024*1024;
		g_be_led.size     =       96*1024;
		g_be_phdr.size    =       16*1024;
		g_chipinfo.size   =   1*1024*1024;
		g_de_dbg_m1.size  =   2*1024*1024;
		g_de_dbg_m2.size  =   1*1024*1024;

		g_de_vt_m1_cma_size = 8*1024*1024;
		g_de_vt_m2_cma_size = 4*1024*1024;

		_gp_map_entry = _g_map_entry_o20_2GB;
	}
	else
	{
		g_fw_mcu0.size    =   4*1024*1024;
		g_de_svp_m0.size  =   0*1024*1024;
		g_de_svp_m1.size  =  20*1024*1024;
		g_de_svp_m2.size  =  20*1024*1024;
		g_de_nsvp_m1.size = 214*1024*1024;
		g_de_nsvp_m2.size = 210*1024*1024;
		g_de_vt_m1.size   =  35*1024*1024;
		g_de_vt_m2.size   =  12*1024*1024;
		g_de_hdr.size     =   3*1024*1024;
		g_be_fpp.size     =  30*1024*1024;
		g_be_frc0.size    =  82*1024*1024;
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =  24*1024*1024;
		g_fw_mcu1.size    =   4*1024*1024;
		g_fw_mcu2.size    =  22*1024*1024;
		g_fw_mcu3.size    =   2*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_fw_mcu4.size    =   2*1024*1024;
		g_be_led.size     =       96*1024;
		g_be_phdr.size    =       16*1024;
		g_chipinfo.size   =   1*1024*1024;
		g_de_dbg_m1.size  =   2*1024*1024;
		g_de_dbg_m2.size  =   1*1024*1024;

		g_de_vt_m1_cma_size = 8*1024*1024;
		g_de_vt_m2_cma_size = 4*1024*1024;

		_gp_map_entry = _g_map_entry_o20;
	}

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

int de_cfg_o20_init(void)
{
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

	return 0;
}

int de_cfg_o20_cleanup(void)
{
	//TODO:
	return 0;
}

void de_cfg_o20_print_status(struct seq_file *m)
{
	char *name;
	UINT32 i, base, size;
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
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vt_m1_cma_size", g_de_vt_m1_cma_size/1024/1024);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vt_m2_cma_size", g_de_vt_m2_cma_size/1024/1024);
	seq_printf(m, "==========================================================\n");
}

