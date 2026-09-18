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
 *  main configuration file for de device
 *	de device will teach you how to make device driver with new platform.
 *
 *  author		dongho7.park (dongho7.park@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_de
 *	@{
 */

#ifndef	_DE_CFG_H_
#define	_DE_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define O18_PQE_NEW_MEM

/* 20210414, pqe new map(AVTASK-591) */
#define PQE_NEW_MAP

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VIDEO_FIRMWARE_ROW_SIZE          (32)
#define VIDEO_ROW_STRIDE                 (16 * 1024)
#define CONV_ROW2BYTE(_r)                ((_r) * VIDEO_ROW_STRIDE)
#define CONV_BYTE2ROW(_r)				 (((_r) + VIDEO_ROW_STRIDE-1) / VIDEO_ROW_STRIDE)

#define	DE_CFG_ALIGN_VALUE		14		/* 16K align */

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char*	fw_name;	///< name of firmware
	UINT32	fw_base;	///< base address of firmware
	UINT32	fw_size;	///< size of firmware
} LX_DE_CH_MEM_T;

typedef struct
{
	LX_DE_CH_MEM_T	fw[3];
	char*	frame_name;  ///< name of frame memory
	UINT32	frame_base;  ///< base of frame memory
	UINT32	frame_size;  ///< size of frame memory
} LX_DE_MEM_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern int de_cfg_disply(void);
extern int de_cfg_get_sharedmem(UINT32 page_offset, UINT32 *mem0, UINT32 *mem1, UINT32 *size);

extern int de_cfg_preinit(void);
extern int de_cfg_init(void);
extern int de_cfg_cleanup(void);

extern int de_cfg_check_force_hma_pool(const char *pool_name, UINT32 pool_type, UINT32 base_addr, int alloc_size);
void de_cfg_print_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern LX_DE_MEM_CFG_T *gpDeMem, *gpDeMemC, gMemCfgDe[];
extern LX_DE_MEM_CFG_T gMemCfgDeFrameC[];
extern LX_DE_CH_MEM_T gMemCfgDePreW[];
extern LX_DE_CH_MEM_T gMemCfgDeGrap[];
extern LX_DE_CH_MEM_T gMemCfgDeFW[];
extern LX_DE_CH_MEM_T gMemCfgDeFwO20[];
extern LX_DE_CH_MEM_T gMemCfgDeFwE60[];
extern LX_DE_MEM_CFG_T gMemCfgHDR[];
extern LX_DE_MEM_CFG_T gMemCfgBT_CMA[];
extern LX_DE_MEM_CFG_T gMemCfgVT_CMA[];

extern LX_DE_CH_MEM_T gMemCfgO18[];
extern LX_DE_CH_MEM_T gMemCfgM19[];
extern LX_DE_CH_MEM_T gMemCfgO20[];
extern LX_DE_CH_MEM_T gMemCfgO20T[];
extern LX_DE_CH_MEM_T gMemCfgE60[];

extern LX_MEMCFG_T g_m0_pqe_svp;
extern LX_MEMCFG_T g_m0_pqe_svp_end;

extern LX_MEMCFG_T g_m0_pqe_nsv;
extern LX_MEMCFG_T g_m0_pqe_nsv_end;

extern LX_MEMCFG_T g_m0_pqe_usr;
extern LX_MEMCFG_T g_m0_pqe_usr_end;

extern LX_MEMCFG_T g_m1_pqe_svp;
extern LX_MEMCFG_T g_m1_pqe_svp_end;

extern LX_MEMCFG_T g_m1_pqe_nsv;
extern LX_MEMCFG_T g_m1_pqe_nsv_end;

extern LX_MEMCFG_T g_m1_pqe_usr;
extern LX_MEMCFG_T g_m1_pqe_usr_end;

extern LX_MEMCFG_T g_m2_pqe_svp;
extern LX_MEMCFG_T g_m2_pqe_svp_end;

extern LX_MEMCFG_T g_m2_pqe_nsv;
extern LX_MEMCFG_T g_m2_pqe_nsv_end;

extern LX_MEMCFG_T g_m2_pqe_usr;
extern LX_MEMCFG_T g_m2_pqe_usr_end;

extern LX_MEMCFG_T g_fw_mcu0;
extern LX_MEMCFG_T g_de_svp_m0;
extern LX_MEMCFG_T g_de_svp_m1;
extern LX_MEMCFG_T g_de_svp_m2;
extern LX_MEMCFG_T g_de_nsvp_m1;
extern LX_MEMCFG_T g_de_nsvp_m2;
extern LX_MEMCFG_T g_de_vt_m1;
extern LX_MEMCFG_T g_de_vt_m2;
extern LX_MEMCFG_T g_de_hdr;
extern LX_MEMCFG_T g_be_fpp;
extern LX_MEMCFG_T g_be_frc0;
extern LX_MEMCFG_T g_be_frc1;
extern LX_MEMCFG_T g_be_frc2;
extern LX_MEMCFG_T g_be_wcg;
extern LX_MEMCFG_T g_pe_db;
extern LX_MEMCFG_T g_pe_hdr;
extern LX_MEMCFG_T g_fw_dnn;
extern LX_MEMCFG_T g_fw_mcu1;
extern LX_MEMCFG_T g_fw_mcu2;
extern LX_MEMCFG_T g_fw_mcu3;
extern LX_MEMCFG_T g_fw_shared;
extern LX_MEMCFG_T g_fw_mcu4;
extern LX_MEMCFG_T g_be_led;
extern LX_MEMCFG_T g_be_phdr;
extern LX_MEMCFG_T g_chipinfo;
extern LX_MEMCFG_T g_de_dbg_m1;
extern LX_MEMCFG_T g_de_dbg_m2;
extern LX_MEMCFG_T g_mcu0_dbg;
extern LX_MEMCFG_T g_mcu1_dbg;

extern UINT32 g_de_vt_m1_cma_size;
extern UINT32 g_de_vt_m2_cma_size;
extern UINT32 g_de_vpb8k_cma_size;
extern UINT32 g_de_vdec_shared_size;
extern UINT32 g_de_pqe_bwb_size;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_CFG_H_ */

/** @} */

