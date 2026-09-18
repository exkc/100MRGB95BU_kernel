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
#include "de_cfg_o22.h"

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
int g_de_cfg_o22_pqe_map = 1;//0:FPGA,1:ASIC,2:FHD
module_param_named(o22_pqe_map, g_de_cfg_o22_pqe_map, int, 0644);

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
void de_cfg_o22_print_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LX_DE_IPC_SYSTEM_MODEL_T _g_de_cfg_o22_system = {.u32Data = 0,};
static struct de_cfg_map_entry *_gp_map_entry = NULL;

/************************************************************/
/* O22 only */
/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_o22[] = {
	&g_de_svp_m0,
	&g_de_svp_m1,
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_o22[] = {
	&g_fw_mcu0,
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
static LX_MEMCFG_T *_gp_group_m0_usr_o22[] = {
	&g_de_vt_m1,
	&g_m0_pqe_usr_end
};
static LX_MEMCFG_T *_gp_group_m1_svp_o22[] = {
	&g_de_svp_m2,
	&g_m1_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m1_nsv_o22[] = {
	&g_fw_mcu1,
	&g_fw_mcu2,
	&g_de_nsvp_m2,
	&g_be_frc0,
	&g_be_frc1,
	&g_be_frc2,
	&g_fw_dnn,
	&g_chipinfo,
	&g_m1_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m1_usr_o22[] = {
	&g_de_vt_m2,
	&g_m1_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_o22[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_o22,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_o22,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_o22,g_m0_pqe_usr),
	DE_CFG_ENTRY(_gp_group_m1_svp_o22,g_m1_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m1_nsv_o22,g_m1_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m1_usr_o22,g_m1_pqe_usr),
	DE_CFG_ENTRY_END
};

/************************************************************/
/* O22 + F22 */
/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_o22_8K[] = {
	&g_de_svp_m0,
	&g_de_svp_m1,
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_o22_8K[] = {
	&g_fw_mcu1,
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
static LX_MEMCFG_T *_gp_group_m0_usr_o22_8K[] = {
	&g_de_vt_m1,
	&g_m0_pqe_usr_end
};
static LX_MEMCFG_T *_gp_group_m1_svp_o22_8K[] = {
	&g_de_svp_m2,
	&g_m1_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m1_nsv_o22_8K[] = {
	&g_fw_mcu0,
	&g_fw_mcu2,
	&g_de_nsvp_m2,
	&g_be_frc0,
	&g_be_frc1,
	&g_be_frc2,
	&g_fw_dnn,
	&g_chipinfo,
	&g_m1_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m1_usr_o22_8K[] = {
	&g_de_vt_m2,
	&g_m1_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_o22_8K[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_o22_8K,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_o22_8K,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_o22_8K,g_m0_pqe_usr),
	DE_CFG_ENTRY(_gp_group_m1_svp_o22_8K,g_m1_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m1_nsv_o22_8K,g_m1_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m1_usr_o22_8K,g_m1_pqe_usr),
	DE_CFG_ENTRY_END
};
/************************************************************/

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_cfg_o22_get_hw_opt(UINT32 *opt)
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
		else if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_144Hz)
		{
			panel_mode.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_144Hz;
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

		panel_mode.panel_fr_option = ovi_opt.panel_fr_option;
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

int de_cfg_o22_preinit(void)
{
	UINT32 i, size, number;
	struct de_cfg_map_entry *p_entry;
	LX_MEMCFG_T *p_group, *p_map;

	de_cfg_o22_get_hw_opt(&_g_de_cfg_o22_system.u32Data);

	DE_NOTI("hw_opt:0x%08x\n",_g_de_cfg_o22_system.u32Data);

	#if 0	//20221206, AVTASK-971
	if (_g_de_cfg_o22_system.panel_resolution == LX_DE_IPC_PANEL_RESOLUTION_1920x1080 || _g_de_cfg_o22_system.panel_resolution == LX_DE_IPC_PANEL_RESOLUTION_1366x768)
	{
		g_de_cfg_o22_pqe_map = 2;
	}
	#endif

	if (_g_de_cfg_o22_system.external_chip == LX_DE_IPC_EXTERNAL_CHIP_USE)
	{
		g_fw_mcu0.size    =   4*1024*1024;
		g_de_svp_m0.size  =   0*1024*1024;
		g_de_svp_m1.size  =  38*1024*1024;//20220112, 28 -> 38(AVTASK-704)
		g_de_svp_m2.size  =  61*1024*1024;//20220112, 59 -> 61(AVTASK-704)
		g_de_nsvp_m1.size =   3*1024*1024;
		g_de_nsvp_m2.size =   0*1024*1024;
		g_de_vt_m1.size   =  24*1024*1024;
		g_de_vt_m2.size   =  12*1024*1024;
		g_de_hdr.size     =   3*1024*1024;
		g_be_fpp.size     =   2*1024*1024;
		g_be_frc0.size    =   0*1024*1024;
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =   8*1024*1024;
		g_fw_mcu1.size    =   4*1024*1024;
		g_fw_mcu2.size    =  13*1024*1024;
		g_fw_mcu3.size    =   0*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_fw_mcu4.size    =   0*1024*1024;
		g_be_led.size     =      128*1024;
		g_be_phdr.size    =       32*1024;
		g_chipinfo.size   =   1*1024*1024;
		g_de_dbg_m1.size  =  64*1024*1024;//20210803, 64 <- 32 (AVTASK-554)
		g_de_dbg_m2.size  =  32*1024*1024;//20210803, 32 <- 58 <- 64 (AVTASK-554)

		g_de_vt_m1_cma_size = 8*1024*1024;
		g_de_vt_m2_cma_size = 4*1024*1024;
		g_de_vpb8k_cma_size = 256*1024*1024;

		_gp_map_entry = _g_map_entry_o22_8K;
	}
	else
	{
		if (g_de_cfg_o22_pqe_map >= 1)//ASIC
		{
			g_fw_mcu0.size    =   4*1024*1024;
			g_de_svp_m0.size  =   0*1024*1024;
			g_de_svp_m1.size  =  54*1024*1024;//20230918,AVTASK-1318:50->54(+4)BT2->3(SCDCR-6523)DolbyBT+1,20220112,40->50(AVTASK-704)
			g_de_svp_m2.size  =  83*1024*1024;//20220112, 81 -> 83(AVTASK-704)
			g_de_nsvp_m1.size =   3*1024*1024;
			g_de_nsvp_m2.size =   0*1024*1024;
			g_de_vt_m1.size   =  24*1024*1024;
			g_de_vt_m2.size   =  12*1024*1024;
			g_de_hdr.size     =   3*1024*1024;
			g_be_fpp.size     =  19*1024*1024;
			g_be_frc0.size    =  33*1024*1024;//20210610, 27 -> 33(AVTASK-554)
			g_be_frc1.size    =   0*1024*1024;
			g_be_frc2.size    =   0*1024*1024;
			g_be_wcg.size     =     1536*1024;
			g_pe_db.size      =   2*1024*1024;
			g_pe_hdr.size     =   1*1024*1024;
			g_fw_dnn.size     =   8*1024*1024;
			g_fw_mcu1.size    =   4*1024*1024;
			g_fw_mcu2.size    =  13*1024*1024;
			g_fw_mcu3.size    =   0*1024*1024;
			g_fw_shared.size  =   2*1024*1024;
			g_fw_mcu4.size    =   0*1024*1024;
			g_be_led.size     =      128*1024;
			g_be_phdr.size    =       32*1024;
			g_chipinfo.size   =   0*1024*1024;
			g_de_dbg_m1.size  =  64*1024*1024;//20210803, 64 <- 32 (AVTASK-554)
			g_de_dbg_m2.size  =  32*1024*1024;//20210803, 32 <- 58 <- 64 (AVTASK-554)
		}
		else//FPGA
		{
			g_fw_mcu0.size    =   8*1024*1024;
			g_de_svp_m0.size  =   0*1024*1024;
			g_de_svp_m1.size  = 128*1024*1024;
			g_de_svp_m2.size  = 128*1024*1024;
			g_de_nsvp_m1.size =   4*1024*1024;
			g_de_nsvp_m2.size =   9*1024*1024;
			g_de_vt_m1.size   =  24*1024*1024;
			g_de_vt_m2.size   =  12*1024*1024;
			g_de_hdr.size     =   3*1024*1024;
			g_be_fpp.size     =  35*1024*1024;
			g_be_frc0.size    =  35*1024*1024;
			g_be_frc1.size    =   0*1024*1024;
			g_be_frc2.size    =   0*1024*1024;
			g_be_wcg.size     =     1536*1024;
			g_pe_db.size      =   2*1024*1024;
			g_pe_hdr.size     =   1*1024*1024;
			g_fw_dnn.size     =  24*1024*1024;
			g_fw_mcu1.size    =   4*1024*1024;
			g_fw_mcu2.size    =   8*1024*1024;
			g_fw_mcu3.size    =   0*1024*1024;
			g_fw_shared.size  =   2*1024*1024;
			g_fw_mcu4.size    =   0*1024*1024;
			g_be_led.size     =      128*1024;
			g_be_phdr.size    =       32*1024;
			g_chipinfo.size   =   1*1024*1024;
			g_de_dbg_m1.size  =  32*1024*1024;
			g_de_dbg_m2.size  =  64*1024*1024;
		}

		g_de_vt_m1_cma_size = 8*1024*1024;
		g_de_vt_m2_cma_size = 4*1024*1024;
		g_de_vpb8k_cma_size = 146*1024*1024;//20230918,AVTASK-1318:128->146(+18)BT2->3(SCDCR-6523)Prew+1,20211019,AVTASK-679:105->128,AVTASK-554

		_gp_map_entry = _g_map_entry_o22;
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

int de_cfg_o22_init(void)
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

	if (g_de_cfg_o22_pqe_map == 2)
	{
		p_map = &g_fw_mcu3;
		size = 5*1024*1024;
		base = hma_alloc("debug1", size, (1<<14));//align:16k
		if ((base > 0) && (0 == hma_pool_register_type("ai-segment",base,size,HMA_POOL)))
		{
			p_map->base = base;
			p_map->size = size;
			DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p_map->name,base,size>>20);
		}
	}

	if ( 0 == hma_pool_info("de-dbg-m1",(phys_addr_t *)&hma_addr,&hma_size) )
	{
		p_map = &g_de_dbg_m1;
		p_map->base = (UINT32)(hma_addr & 0xFFFFFFFF);
		if (p_map->size > hma_size)	p_map->size = hma_size;

		base = p_map->base;
		size = p_map->size/1024/1024;
		DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p_map->name,base,size);
	}

	if ( 0 == hma_pool_info("de-dbg-m2",(phys_addr_t *)&hma_addr,&hma_size) )
	{
		p_map = &g_de_dbg_m2;
		p_map->base = (UINT32)(hma_addr & 0xFFFFFFFF);
		if (p_map->size > hma_size)	p_map->size = hma_size;

		base = p_map->base;
		size = p_map->size/1024/1024;
		DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p_map->name,base,size);
	}

	return 0;
}

int de_cfg_o22_cleanup(void)
{
	//TODO:
	return 0;
}

/* check condition : see AVTASK-1227 */
static int de_cfg_o22_check_valid(UINT32 addr)
{
	int ret = 0;

	if ((addr&3) != 0)	ret = 1;
	else if (addr < 0x50400000)	ret = 2;
	else if (addr > 0xC0000000)	ret = 3;
	//else if (addr == 0)	ret = 4;
	//else if (addr >= 0x50000000 && addr < 0x50400000)	ret = 5;
	//else if (addr < 0x10000000)	ret = 6;

	return ret;
}

static void de_cfg_o22_print_check_valid(struct seq_file *m)
{
	int ret_s, ret_e;
	UINT64 addr = 0;
	UINT32 start, size, end;
	LX_MEMCFG_T **ppqe, *pqe;
	char **ppool, *pool, *name;
	LX_MEMCFG_T *pqe_list[] = {&g_m0_pqe_nsv,&g_m0_pqe_usr,&g_m1_pqe_nsv,&g_m1_pqe_usr,&g_m2_pqe_nsv,&g_m2_pqe_usr,NULL};
	char *pool_list[] = {"vdec","debug0","debug1","debug2",NULL};

	ppqe = pqe_list;
	pqe = *ppqe;
	while (pqe) {
		if (pqe->size > 0) {
			name = pqe->name;
			start = pqe->base;
			size = pqe->size;
			end = start + size;
			ret_s = de_cfg_o22_check_valid(start);
			ret_e = de_cfg_o22_check_valid(end);
			seq_printf(m, "%-20s = 0x%08x ~ 0x%08x (valid:%s)\n",name,start,end,(ret_s+ret_e)? "ng":"ok");
		}
		pqe = *(++ppqe);
	}

	ppool = pool_list;
	pool = *ppool;
	while (pool) {
		if (0 == hma_pool_info (pool, (phys_addr_t *)&addr, &size)) {
			name = pool;
			start = (UINT32)(addr & 0xFFFFFFFF);
			end = start + size;
			ret_s = de_cfg_o22_check_valid(start);
			ret_e = de_cfg_o22_check_valid(end);
			seq_printf(m, "%-20s = 0x%08x ~ 0x%08x (valid:%s)\n",name,start,end,(ret_s+ret_e)? "ng":"ok");
		}
		pool = *(++ppool);
	}
}

extern LX_MEMCFG_T de_reg_o22_getmeminfo(char* str);
void de_cfg_o22_print_status(struct seq_file *m)
{
	char *name;
	int size_m0, size_m1, diff;
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
	seq_printf(m, "%-20s\n", "fw_shared");
	seq_printf(m, "----------------------------------------------------------\n");
	name = "vtm";
	base = g_fw_shared.base+VIDEO_O22_FW_SHARED_OFST_VTM;
	size = VIDEO_O22_FW_SHARED_SIZE_VTM;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "vtv";
	base = g_fw_shared.base+VIDEO_O22_FW_SHARED_OFST_VTV;
	size = VIDEO_O22_FW_SHARED_SIZE_VTV;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "gps";
	base = g_fw_shared.base+VIDEO_O22_FW_SHARED_OFST_GPS;
	size = VIDEO_O22_FW_SHARED_SIZE_GPS;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "dly";
	base = g_fw_shared.base+VIDEO_O22_FW_SHARED_OFST_DLY;
	size = VIDEO_O22_FW_SHARED_SIZE_DLY;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "fpp";
	base = g_fw_shared.base+VIDEO_O22_FW_SHARED_OFST_FPP;
	size = VIDEO_O22_FW_SHARED_SIZE_FPP;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "mvi";
	base = g_fw_shared.base+VIDEO_O22_FW_SHARED_OFST_MVI;
	size = VIDEO_O22_FW_SHARED_SIZE_MVI;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "etc");
	seq_printf(m, "----------------------------------------------------------\n");
	name = "vdec_pool_0";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	name = "vdec_pool_1";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	name = "lne_pool";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vt_m1_cma_size", g_de_vt_m1_cma_size/1024/1024);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vt_m2_cma_size", g_de_vt_m2_cma_size/1024/1024);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vpb8k_cma_size", g_de_vpb8k_cma_size/1024/1024);
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "check mem");
	seq_printf(m, "----------------------------------------------------------\n");
	hma_pool_status("debug0", hma_pool_status_total_size, &size_m0);
	hma_pool_status("debug1", hma_pool_status_total_size, &size_m1);
	name = "de-vrbuf_m0";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = %4d MB (vs. %2d MB) (reserved:%s)\n", name, meminfo.size>>20, size_m0>>20, (meminfo.size>size_m0)? "ng":"ok");
	name = "de-vrbuf_m1";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = %4d MB (vs. %2d MB) (reserved:%s)\n", name, meminfo.size>>20, size_m1>>20, (meminfo.size>size_m1)? "ng":"ok");
	name = "de-vtvrbuf_m0";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = %4d MB (vs. %2d MB) (reserved:%s)\n", name, meminfo.size>>20, size_m0>>20, (meminfo.size>size_m0)? "ng":"ok");
	name = "de-vtvrbuf_m1";
	meminfo = de_reg_o22_getmeminfo(name);
	seq_printf(m, "%-20s = %4d MB (vs. %2d MB) (reserved:%s)\n", name, meminfo.size>>20, size_m1>>20, (meminfo.size>size_m1)? "ng":"ok");
	diff = g_m0_pqe_nsv.base - g_m0_pqe_svp.base - g_m0_pqe_svp.size;
	seq_printf(m, "%-20s = %4d MB (continuity:%s)\n", "m0 nsv_s-svp_e diff", diff>>20, (diff == 0)? "ok":"ng");
	diff = g_m1_pqe_nsv.base - g_m1_pqe_svp.base - g_m1_pqe_svp.size;
	seq_printf(m, "%-20s = %4d MB (continuity:%s)\n", "m1 nsv_s-svp_e diff", diff>>20, (diff == 0)? "ok":"ng");
	diff = g_m2_pqe_nsv.base - g_m2_pqe_svp.base - g_m2_pqe_svp.size;
	seq_printf(m, "%-20s = %4d MB (continuity:%s)\n", "m2 nsv_s-svp_e diff", diff>>20, (diff == 0)? "ok":"ng");
	de_cfg_o22_print_check_valid(m);
	seq_printf(m, "==========================================================\n");
}
