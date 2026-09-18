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
#include "de_cfg_o26.h"

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
int g_de_cfg_o26_pqe_map = 0;//0:FPGA,1:ASIC,2:ASIC_96b
#elif defined BUILD_FEATURE_ddr_96bit
int g_de_cfg_o26_pqe_map = 2;//0:FPGA,1:ASIC,2:ASIC_96b
#else
int g_de_cfg_o26_pqe_map = 1;//0:FPGA,1:ASIC,2:ASIC_96b
#endif
module_param_named(o26_pqe_map, g_de_cfg_o26_pqe_map, int, 0644);

static uint _g_de_cfg_o26_pqe_se_map = 0;//0:normal,1:non-secure,2:secure
module_param_named(o26_pqe_se_map, _g_de_cfg_o26_pqe_se_map, uint, 0644);

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
void de_cfg_o26_print_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LX_DE_IPC_SYSTEM_MODEL_T _g_de_cfg_o26_system = {.u32Data = 0,};
static struct de_cfg_map_entry *_gp_map_entry = NULL;
static UINT32 g_de_svp_m0_size_org = 0;

/************************************************************/
/* O26 */
/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_o26[] = {
	&g_fw_mcu0,
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_o26[] = {
	&g_be_fpp,
	&g_de_nsvp_m1,
	&g_de_hdr,
	&g_be_wcg,
	&g_be_led,
	&g_be_phdr,
	&g_mcu0_dbg,
	&g_mcu1_dbg,
	&g_chipinfo,
	&g_pe_db,
	&g_pe_hdr,
	&g_fw_dnn,
	&g_fw_shared,
	&g_m0_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m0_usr_o26[] = {
	&g_de_vt_m1,
	&g_m0_pqe_usr_end
};
static LX_MEMCFG_T *_gp_group_m1_svp_o26[] = {
	&g_fw_mcu1,
	&g_m1_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m1_nsv_o26[] = {
	&g_be_frc0,
	&g_de_nsvp_m2,
	&g_m1_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m1_usr_o26[] = {
	&g_de_vt_m2,
	&g_m1_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_o26[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_o26,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_o26,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_o26,g_m0_pqe_usr),
	DE_CFG_ENTRY(_gp_group_m1_svp_o26,g_m1_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m1_nsv_o26,g_m1_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m1_usr_o26,g_m1_pqe_usr),
	DE_CFG_ENTRY_END
};

#if 0	//not used
/************************************************************/
/* O26 SLT */
/************************************************************/
static LX_MEMCFG_T *_gp_group_m0_svp_o26_slt[] = {
	&g_m0_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m0_nsv_o26_slt[] = {
	&g_be_fpp,
	&g_fw_mcu0,
	&g_de_nsvp_m1,
	&g_de_hdr,
	&g_be_wcg,
	&g_be_led,
	&g_be_phdr,
	&g_mcu0_dbg,
	&g_mcu1_dbg,
	&g_chipinfo,
	&g_pe_db,
	&g_pe_hdr,
	&g_fw_dnn,
	&g_fw_shared,
	&g_m0_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m0_usr_o26_slt[] = {
	&g_de_vt_m1,
	&g_m0_pqe_usr_end
};
static LX_MEMCFG_T *_gp_group_m1_svp_o26_slt[] = {
	&g_m1_pqe_svp_end
};
static LX_MEMCFG_T *_gp_group_m1_nsv_o26_slt[] = {
	&g_be_frc0,
	&g_fw_mcu1,
	&g_de_nsvp_m2,
	&g_m1_pqe_nsv_end
};
static LX_MEMCFG_T *_gp_group_m1_usr_o26_slt[] = {
	&g_de_vt_m2,
	&g_m1_pqe_usr_end
};

static struct de_cfg_map_entry _g_map_entry_o26_slt[] = {
	DE_CFG_ENTRY(_gp_group_m0_svp_o26_slt,g_m0_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m0_nsv_o26_slt,g_m0_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m0_usr_o26_slt,g_m0_pqe_usr),
	DE_CFG_ENTRY(_gp_group_m1_svp_o26_slt,g_m1_pqe_svp),
	DE_CFG_ENTRY(_gp_group_m1_nsv_o26_slt,g_m1_pqe_nsv),
	DE_CFG_ENTRY(_gp_group_m1_usr_o26_slt,g_m1_pqe_usr),
	DE_CFG_ENTRY_END
};
/************************************************************/
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_cfg_o26_get_hw_opt(UINT32 *opt, UINT32 number)
{
#ifdef INCLUDE_KDRV_BE
	LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
	LX_DE_IPC_SYSTEM_MODEL_T m0 = {.u32Data=0};
	LX_DE_IPC_SYSTEM_MODEL1_T m1 = {.u32Data=0};
	int ret = RET_OK;

	if (!opt || number < 4) {
		DE_ERROR("null opt, or wrong number(%d)\n",number);
		return -1;
	}

	ret = OVI_HAL_GetHWDisplayOption(&ovi_opt);
	if (ret == RET_OK)
	{
		if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
		{
			m1.panel_frame_rate4 = m0.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz;
		}
		else if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ_FIXED)
		{
			m1.panel_frame_rate4 = m0.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz_FIXED;
		}
		else if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_144Hz)
		{
			m1.panel_frame_rate4 = m0.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_144Hz;
		}
		else if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_165Hz)
		{
			m0.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_144Hz;
			m1.panel_frame_rate4 = LX_DE_IPC_PANEL_FRAME_RATE_165Hz;
		}

		if (ovi_opt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
		{
			m0.panel_type = LX_DE_IPC_PANEL_TYPE_OLED;
		}
		else if (ovi_opt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_NONE)
		{
			m0.panel_type = LX_DE_IPC_PANEL_TYPE_BOX;
		}

		if (ovi_opt.isVx15Byte)
		{
			m0.vx1_byte  = LX_DE_IPC_PANEL_VX1_5BYTE;
		}

		if (ovi_opt.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
		{
			if (ovi_opt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_KLD) {
				m0.external_chip  = LX_DE_IPC_EXTERNAL_CHIP_KLD;
			} else {
				m0.external_chip  = LX_DE_IPC_EXTERNAL_CHIP_USE;
			}
		}

		if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
		{
			m0.panel_resolution = LX_DE_IPC_PANEL_RESOLUTION_1920x1080;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1366X768)
		{
			m0.panel_resolution = LX_DE_IPC_PANEL_RESOLUTION_1366x768;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1280X720)
		{
			m0.panel_resolution = LX_DE_IPC_PANEL_RESOLUTION_1280x720;
		}

		if (ovi_opt.ovi_in_bit == 11)
		{
			m1.pqe_out_bit = LX_DE_IPC_PQE_OUT_BIT_11;
		}
		else if (ovi_opt.ovi_in_bit == 12)
		{
			m1.pqe_out_bit = LX_DE_IPC_PQE_OUT_BIT_12;
		}
		else if (ovi_opt.ovi_in_bit == 13)
		{
			m1.pqe_out_bit = LX_DE_IPC_PQE_OUT_BIT_13;
		}

		if (ovi_opt.oled_boost_x4 == 1)
		{
			m1.oled_boost_x4 = 1;
		}

		if (ovi_opt.wirelessAV)
		{
			m0.ext_wireless_chip = LX_DE_IPC_EXT_WIRELESS_CHIP_USE;
		}
	}

	opt[0] = m0.u32Data;
	opt[1] = m1.u32Data;
	opt[2] = opt[3] = 0;

#else
	if (opt || num >= 4) {
		opt[0] = opt[1] = opt[2] = opt[3] = 0
	}
#endif

	return RET_OK;
}

int de_cfg_o26_preinit(void)
{
	UINT32 i, size, number, opt[4];
	struct de_cfg_map_entry *p_entry;
	LX_MEMCFG_T *p_group, *p_map;

	de_cfg_o26_get_hw_opt(opt,4);
	_g_de_cfg_o26_system.u32Data = opt[0];

	DE_NOTI("opt:0x%08x,0x%08x,b_opt:0x%08x,map:%d\n",opt[0],opt[1],lx_board_opt(),g_de_cfg_o26_pqe_map);

	/* http://jira.lge.com/issue/browse/AVTASK-1521 : bringup map */
	if (g_de_cfg_o26_pqe_map >= 1)
	{
		/* PQE_BWB_SVP = g_de_svp_m0 + g_de_svp_m1 + g_de_svp_m2 */
		g_de_svp_m0.size  = 132*1024*1024;//bwb_share,20250813,gav8->4(-56)(SICDTV-15916)
		g_de_svp_m1.size  =  63*1024*1024;
		g_de_svp_m2.size  = 109*1024*1024;
		g_be_fpp.size     =  21*1024*1024;//continuously with g_de_svp_m1
		g_be_frc0.size    =  36*1024*1024;//continuously with g_de_svp_m2
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_de_nsvp_m1.size =   0*1024*1024;//non svp(dnnsqm,dnnsr)
		g_de_nsvp_m2.size =   3*1024*1024;//non svp(dnnsqm,dnnsr)
		g_de_vt_m1.size   =   8*1024*1024;//vtg
		g_de_vt_m2.size   =   4*1024*1024;//vtg
		g_de_hdr.size     =   3*1024*1024;//dolby hdr frame buffer(pre-metadaata,pre-lut)
		g_be_wcg.size     =     1536*1024;
		g_be_led.size     =      128*1024;
		g_be_phdr.size    =      128*1024;//2M align(org:32k)
		g_mcu0_dbg.size   =      128*1024;//mcu0 debug info
		g_mcu1_dbg.size   =      128*1024;//mcu1 debug info
		g_chipinfo.size   =   1*1024*1024;//for wireless model
		g_pe_db.size      =   2*1024*1024;//pq
		g_pe_hdr.size     =   1*1024*1024;//hdr10
		g_fw_dnn.size     =   6*1024*1024;
		g_fw_mcu0.size    =   4*1024*1024;//svp_m0
		g_fw_mcu1.size    =   4*1024*1024;//svp_m1
		g_fw_mcu2.size    =   0*1024*1024;
		g_fw_mcu3.size    =   0*1024*1024;
		g_fw_mcu4.size    =   0*1024*1024;
		g_fw_shared.size  =   2*1024*1024;//fpp info, video delay info, vtg,vtv,gav share
		g_de_dbg_m1.size  =  25*1024*1024;
		g_de_dbg_m2.size  =  50*1024*1024;

		g_de_vt_m1_cma_size = g_de_vt_m1.size;//Y: VTG:4K420 x1(8MB)
		g_de_vt_m2_cma_size = g_de_vt_m2.size;//C: VTG:4K420 x1(4MB)
		g_de_pqe_bwb_size = g_de_vdec_shared_size = 160*1024*1024;//cvi input 148MB, dolby_c_2b 12MB

		_gp_map_entry = _g_map_entry_o26;
	}
	else//FPGA (AVTASK-1475)(SICDTV-14638),xls242229
	{
		g_de_svp_m0.size  = 160*1024*1024;
		g_de_svp_m1.size  =  57*1024*1024;
		g_de_svp_m2.size  = 100*1024*1024;
		g_be_fpp.size     =  19*1024*1024;
		g_be_frc0.size    =  31*1024*1024;
		g_be_frc1.size    =   0*1024*1024;
		g_be_frc2.size    =   0*1024*1024;
		g_de_nsvp_m1.size =   3*1024*1024;
		g_de_nsvp_m2.size =   0*1024*1024;
		g_de_vt_m1.size   =  24*1024*1024;
		g_de_vt_m2.size   =  12*1024*1024;
		g_de_hdr.size     =   3*1024*1024;
		g_be_wcg.size     =     1536*1024;
		g_be_led.size     =      128*1024;
		g_be_phdr.size    =      128*1024;//2M align(org:32k)
		g_mcu0_dbg.size   =      128*1024;
		g_mcu1_dbg.size   =      128*1024;
		g_chipinfo.size   =   1*1024*1024;
		g_pe_db.size      =   2*1024*1024;
		g_pe_hdr.size     =   1*1024*1024;
		g_fw_dnn.size     =   6*1024*1024;
		g_fw_mcu0.size    =   4*1024*1024;
		g_fw_mcu1.size    =   4*1024*1024;
		g_fw_mcu2.size    =   0*1024*1024;
		g_fw_mcu3.size    =   0*1024*1024;
		g_fw_mcu4.size    =   0*1024*1024;
		g_fw_shared.size  =   2*1024*1024;
		g_de_dbg_m1.size  =  25*1024*1024;
		g_de_dbg_m2.size  =  50*1024*1024;

		g_de_vt_m1_cma_size = 8*1024*1024;
		g_de_vt_m2_cma_size = 4*1024*1024;
		g_de_pqe_bwb_size = g_de_vdec_shared_size = g_de_svp_m0.size;

		_gp_map_entry = _g_map_entry_o26;
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

int de_cfg_o26_init(void)
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

	if ( 0 == hma_pool_info("pqe-bwb-svp",(phys_addr_t *)&hma_addr,&hma_size) )
	{
		LX_MEMCFG_T *p0 = &g_de_svp_m0;
		LX_MEMCFG_T *p1 = &g_de_svp_m1;
		LX_MEMCFG_T *p2 = &g_de_svp_m2;

		if (hma_size >= (p0->size + p1->size + p2->size)) {
			/* req. order : m1,m2,m0 */
			p1->base = (UINT32)(hma_addr & 0xFFFFFFFF);
			DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p1->name,p1->base,p1->size>>20);
			p2->base = p1->base + p1->size;
			DE_NOTI("%-15s = base:0x%08x, size:%4d MB\n",p2->name,p2->base,p2->size>>20);
			p0->base = p2->base + p2->size;
			g_de_svp_m0_size_org = p0->size;
			p0->size = hma_size - p1->size - p2->size;
			DE_NOTI("%-15s = base:0x%08x, size:%4d MB (org:%4d MB)\n",p0->name,p0->base,p0->size>>20,g_de_svp_m0_size_org>>20);
		}
		else {
			DE_NOTI("not enough pqe-bwb-svp : hma_size:%4d MB, de_svp:%4d MB\n",hma_size>>20,(p0->size + p1->size + p2->size)>>20);
		}
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

	if ( 0 == hma_pool_info("debug1",(phys_addr_t *)&hma_addr,&hma_size) )
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

int de_cfg_o26_cleanup(void)
{
	//TODO:
	return 0;
}

int de_cfg_o26_is_mcu_se_map(int mcu_idx)
{
	int ret = 0;
	UINT32 mcu_s, mcu_e, svp_s, svp_e;
	LX_MEMCFG_T **pp, *p;
	LX_MEMCFG_T *p_mcu = NULL;
	LX_MEMCFG_T *p_svp[] = {&g_m0_pqe_svp,&g_m1_pqe_svp,&g_m2_pqe_svp,NULL};

	if (g_de_cfg_o26_pqe_map == 0) {
		return 0;//FPGA non-secure only
	}
	else if (_g_de_cfg_o26_pqe_se_map > 0) {
		return (_g_de_cfg_o26_pqe_se_map - 1);
	}
	else if (lx_board_opt() & LX_BOARD_OPT_SLT) {
		return 0;//SLT non-secure only
	}
	else if (mcu_idx == 0) {
		p_mcu = &g_fw_mcu0;
	}
	else if (mcu_idx == 1) {
		p_mcu = &g_fw_mcu1;
	}
	else {
		DE_NOTI("not support(idx:%d)\n",mcu_idx);
		return -1;
	}

	pp = p_svp;
	p = *pp;
	while (p) {
		if (p->base && p->size && p_mcu->base && p_mcu->size) {
			mcu_s = p_mcu->base;
			mcu_e = p_mcu->base + p_mcu->size;
			svp_s = p->base;
			svp_e = p->base + p->size;
			if (mcu_s >= svp_s && mcu_e <= svp_e) {
				DE_NOTI("[%d] mcu:%08x~%08x, svp:%08x~%08x\n",mcu_idx,mcu_s,mcu_e,svp_s,svp_e);
				ret = 1;
				break;
			}
		}
		p = *(++pp);
	}

	return ret;
}

/* check condition : see AVTASK-1227 */
static int de_cfg_o26_check_valid(UINT32 addr)
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

static void de_cfg_o26_print_check_valid(struct seq_file *m)
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
			ret_s = de_cfg_o26_check_valid(start);
			ret_e = de_cfg_o26_check_valid(end);
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
			ret_s = de_cfg_o26_check_valid(start);
			ret_e = de_cfg_o26_check_valid(end);
			seq_printf(m, "%-20s = 0x%08x ~ 0x%08x (valid:%s)\n",name,start,end,(ret_s+ret_e)? "ng":"ok");
		}
		pool = *(++ppool);
	}
}

extern LX_MEMCFG_T de_reg_o26_getmeminfo(char* str);
void de_cfg_o26_print_status(struct seq_file *m)
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
	seq_printf(m, "%-20s\n", "pqe-bwb-svp");
	seq_printf(m, "----------------------------------------------------------\n");
	name = g_de_svp_m0.name;
	base = g_de_svp_m0.base;
	size = g_de_svp_m0.size;
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
	name = g_de_svp_m1.name;
	base = g_de_svp_m1.base;
	size = g_de_svp_m1.size;
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
	name = g_de_svp_m2.name;
	base = g_de_svp_m2.base;
	size = g_de_svp_m2.size;
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, base, size/1024/1024, size);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_svp_m0_size_org", g_de_svp_m0_size_org>>20);
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "fw_shared");
	seq_printf(m, "----------------------------------------------------------\n");
	name = "vtm";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_VTM;
	size = VIDEO_O26_FW_SHARED_SIZE_VTM;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "vtv";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_VTV;
	size = VIDEO_O26_FW_SHARED_SIZE_VTV;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "gps";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_GPS;
	size = VIDEO_O26_FW_SHARED_SIZE_GPS;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "dly";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_DLY;
	size = VIDEO_O26_FW_SHARED_SIZE_DLY;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "fpp";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_FPP;
	size = VIDEO_O26_FW_SHARED_SIZE_FPP;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "mvi";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_MVI;
	size = VIDEO_O26_FW_SHARED_SIZE_MVI;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "ctop_mcu2cpu";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_CTOP_M2C;
	size = VIDEO_O26_FW_SHARED_SIZE_CTOP_M2C;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	name = "ctop_cpu2mcu";
	base = g_fw_shared.base+VIDEO_O26_FW_SHARED_OFST_CTOP_C2M;
	size = VIDEO_O26_FW_SHARED_SIZE_CTOP_C2M;
	seq_printf(m, "%-20s = 0x%08x, %4d KB\n", name, base, size>>10);
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "etc");
	seq_printf(m, "----------------------------------------------------------\n");
	name = "vdec_pool_0";
	meminfo = de_reg_o26_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	name = "vdec_pool_1";
	meminfo = de_reg_o26_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	name = "lne_pool";
	meminfo = de_reg_o26_getmeminfo(name);
	seq_printf(m, "%-20s = 0x%08x, %4d MB (%10d B)\n", name, meminfo.base, meminfo.size>>20, meminfo.size);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vt_m1_cma_size", g_de_vt_m1_cma_size>>20);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_vt_m2_cma_size", g_de_vt_m2_cma_size>>20);
	seq_printf(m, "%-20s = %4d MB\n", "g_de_pqe_bwb_size", g_de_pqe_bwb_size>>20);
	seq_printf(m, "==========================================================\n");
	seq_printf(m, "%-20s\n", "check mem");
	seq_printf(m, "----------------------------------------------------------\n");
	hma_pool_status("debug0", hma_pool_status_total_size, &size_m0);
	hma_pool_status("debug1", hma_pool_status_total_size, &size_m1);
	name = "de-vtvrbuf_m0";
	meminfo = de_reg_o26_getmeminfo(name);
	seq_printf(m, "%-20s = %4d MB (vs. %2d MB) (reserved:%s)\n", name, meminfo.size>>20, size_m0>>20, (meminfo.size>size_m0)? "ng":"ok");
	name = "de-vtvrbuf_m1";
	meminfo = de_reg_o26_getmeminfo(name);
	seq_printf(m, "%-20s = %4d MB (vs. %2d MB) (reserved:%s)\n", name, meminfo.size>>20, size_m1>>20, (meminfo.size>size_m1)? "ng":"ok");
	diff = g_m0_pqe_nsv.base - g_m0_pqe_svp.base - g_m0_pqe_svp.size;
	seq_printf(m, "%-20s = %4d MB (continuity:%s)\n", "m0 nsv_s-svp_e diff", diff>>20, (diff == 0)? "ok":"ng");
	diff = g_m1_pqe_nsv.base - g_m1_pqe_svp.base - g_m1_pqe_svp.size;
	seq_printf(m, "%-20s = %4d MB (continuity:%s)\n", "m1 nsv_s-svp_e diff", diff>>20, (diff == 0)? "ok":"ng");
	diff = g_m2_pqe_nsv.base - g_m2_pqe_svp.base - g_m2_pqe_svp.size;
	seq_printf(m, "%-20s = %4d MB (continuity:%s)\n", "m2 nsv_s-svp_e diff", diff>>20, (diff == 0)? "ok":"ng");
	de_cfg_o26_print_check_valid(m);
	seq_printf(m, "==========================================================\n");
}

