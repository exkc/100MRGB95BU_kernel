/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *	memory configuration for L18F driver
 *
 *  author		raxis.lim@lge.com
 *  version		1.0
 *  date		2016.09.23
 *
 *  @addtogroup lg1150_base
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
#include <linux/uaccess.h>
#include <linux/ctype.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/delay.h>

#include "base_types.h"
#include "base_device.h"
#include "debug_util.h"
#include "os_util.h"

#include "hma_alloc.h"

#define INCLUDE_KDRV_AUDIO
#ifdef INCLUDE_KDRV_AUDIO
#include "audio/audio_cfg.h"
#endif
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif
#ifdef INCLUDE_KDRV_FBDEV
#include "fbdev_cfg.h"
#endif
#ifdef INCLUDE_KDRV_GFX
#include "gfx_cfg.h"
#endif
#ifdef INCLUDE_KDRV_TE
#include "te_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VBI
#include "vbi_cfg.h"
#endif
#ifdef INCLUDE_KDRV_OVI
#include "ovi_cfg.h"
#endif
#ifdef INCLUDE_KDRV_BE
#include "be_cfg.h"
#endif
#ifdef INCLUDE_KDRV_SE
#include "se_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VENC
#include "venc_cfg.h"
#endif
#ifdef INCLUDE_KDRV_PNG
#include "png_cfg.h"
#endif
#ifdef INCLUDE_KDRV_AFE
#include "afe_cfg.h"
#endif
#ifdef INCLUDE_KDRV_MJPEG
#include "mjpeg_cfg.h"
#endif
#ifdef INCLUDE_KDRV_DEMOD
#include "demod_cfg.h"
#endif

#ifdef INCLUDE_KDRV_LGBUS
#include "lgbus_cfg.h"
#endif

#include "platform_mem_map.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define LX_MEMCFG_ENTRY(item)				{ .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T) }
#define LX_MEMCFG_ENTRY_EX(item,alias)		{ .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T), .flag=LX_MEMCFG_FLAG_ALIAS, .pAlias=&alias }
#define LX_MEMCFG_ENTRY_END					{ .name="Total", .pM=NULL, .nM=0}

#define	__L_BUS__			0

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	DDR_RGN_LBUS_DEV 		= 0,
	DDR_RGN_MAX,
}
DDR_RGN_T;

typedef enum
{
	MEM_DESC_ID_GFX = 0,
	MEM_DESC_ID_MJPEG,
	MEM_DESC_ID_VENC,
	MEM_DESC_ID_AUDIO,
	MEM_DESC_ID_FBDEV,
	MEM_DESC_ID_DE_FW,
	MEM_DESC_ID_DE_PREW,
	MEM_DESC_ID_VDEC0,
	MEM_DESC_ID_VDEC1,
	MEM_DESC_ID_VDEC_HFR,
	MEM_DESC_ID_SYS,
	MEM_DESC_ID_SE,
	MEM_DESC_ID_SE_TZFW,
	MEM_DESC_ID_TE,
	MEM_DESC_ID_DEMOD,
	MEM_DESC_ID_TCON,
	MEM_DESC_ID_DE,
	MEM_DESC_ID_BT,
	MEM_DESC_ID_VT,
	MEM_DESC_ID_HDR,
	MEM_DESC_ID_VBI,
	MEM_DESC_ID_CVD,
	MEM_DESC_ID_DEMOD_FW,
	MEM_DESC_ID_BE,
	MEM_DESC_ID_BE_FRC,
	MEM_DESC_ID_CALIB,
	MEM_DESC_ID_MAX,
}
MEM_DESC_ID_T;

typedef struct
{
#define	MEMCFG_DESC_FLAG_NONE		0x00000000	/* device such as SE/TZ should keep memory content from the booting stage */
#define	MEMCFG_DESC_FLAG_CMA		0x4F434D41	/* device will manage dedicated memory according to its own policy */
#define	MEMCFG_DESC_FLAG_NO_CMA		0x4E434D41	/* device requires the pre-allocated device memory */
	UINT32		flag;
	LX_MEMCFG_T	m;
}
LX_MEMCFG_DESC_T;

typedef enum
{
	MODEL_OPT_DDR_256MB			= 0x1,		/* 60Hz panel OR HDMI Tx */
	MODEL_OPT_DDR_512MB			= 0x2,		/* 60Hz panel OR HDMI Tx */

	MODEL_OPT_NO_FRC			= 0x1,
	MODEL_OPT_INT_FRC			= 0x2,

	MODEL_OPT_USR				= 0x1,		/* enable USR option */
}
MODEL_OPT_T;

typedef struct
{
	MODEL_OPT_T	ddr_size;
	MODEL_OPT_T frc_conn;

	MODEL_OPT_T usr0;
	MODEL_OPT_T usr1;					/* if defined, we try to setup test environment for 4K120 video decoder */
	MODEL_OPT_T usr2;
	MODEL_OPT_T usr3;
}
MODEL_OPT_CTX_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern 	char*	simple_strtok(char *s, const char *delim, char **save_ptr);
extern	int     BASE_DEVMEM_InitDevMem( LX_MEMCFG_ENTRY_T* pEntry );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
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
static int 	fpga_hwopt_probe = 1;
module_param_named(fpga_hwopt_probe, fpga_hwopt_probe, int, 0644 );

static MODEL_OPT_CTX_T	g_model_ctx = { .ddr_size	= MODEL_OPT_DDR_256MB,	/* 2GB by default */
										.frc_conn	= MODEL_OPT_NO_FRC,		/* INT_FRC default */
										.usr0		= 0,
										.usr1		= 0,
										.usr2		= 0,
										.usr3		= 0 };


static LX_MEMCFG_T	gMemCfgHdr[DDR_RGN_MAX+1]={{.name = "[header] DDR0",.base = 0x0, .size = 0 },	/* mem header */
											   {.name = NULL, 			.base = 0x0, .size = 0 }};	/* NA */

static LX_MEMCFG_T	ddr0_static_rgn_start 	= {.name = "static(DDR0)",	.base = 0x0, .size = 0 };	/* mem separator */
static LX_MEMCFG_T	pqe_static_rgn_start 	= {.name = "static(pqe)",	.base = 0x0, .size = 0 };	/* mem separator */
static LX_MEMCFG_T	vdec0_hma				= {.name = "vdec0_hma",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T	gMemCfgSYS				= {.name = "system",		.base = 0x0, .size = SYS_MEM_SZ };

/* memory alias list for CMA processing */
#define MEM_DESC(n)				(mem_desc[MEM_DESC_ID_##n].m)
#define MEM_DESC_NAME(n)		(mem_desc[MEM_DESC_ID_##n].m.name)
#define MEM_DESC_BASE(n)		(mem_desc[MEM_DESC_ID_##n].m.base)
#define MEM_DESC_SIZE(n)		(mem_desc[MEM_DESC_ID_##n].m.size)
#define MEM_DESC_FLAG(n)		(mem_desc[MEM_DESC_ID_##n].flag)

#define DEFINE_MEM_DESC(n,f)	[MEM_DESC_ID_##n] = { .m={ .name = #n"_cma", .base = 0x0, .size = 0 }, .flag=f }

static LX_MEMCFG_DESC_T mem_desc[MEM_DESC_ID_MAX]	= {
	DEFINE_MEM_DESC(GFX		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(MJPEG	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VENC	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(AUDIO	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(FBDEV	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_PREW	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC0	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(TE		,MEMCFG_DESC_FLAG_CMA),

	DEFINE_MEM_DESC(SYS		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SE		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SE_TZFW	,MEMCFG_DESC_FLAG_NONE),

	DEFINE_MEM_DESC(DEMOD	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(TCON	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BT		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(VT		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(HDR		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VBI		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(CVD		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DEMOD_FW,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(CALIB	,MEMCFG_DESC_FLAG_NO_CMA),
};

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;

/* DDR 256MB */
static LX_MEMCFG_ENTRY_T g_mem_desc_table_256MB[] =	/* default map */
{
	//-----------------------------------------------------------------------------------
	//	DDR (LBUS_DEV)
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_LBUS_DEV]),

#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY_EX(gMemCfgGfx.surface[0], MEM_DESC(GFX)),	/* GFX */
#endif

#ifdef INCLUDE_KDRV_MJPEG
	LX_MEMCFG_ENTRY_EX(gMemCfgMjpeg, MEM_DESC(MJPEG)),		/* MJPEG */
#endif

#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY_EX(gMemCfgVenc, MEM_DESC(VENC)),		/* VENC */
#endif

#ifdef INCLUDE_KDRV_AUDIO
	LX_MEMCFG_ENTRY_EX(gMemCfgAud[0], MEM_DESC(AUDIO)),		/* AUDIO */
#endif

#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),		/* FBDEV */
#endif

#ifdef INCLUDE_KDRV_DE
//	LX_MEMCFG_ENTRY_EX(gMemCfgDeFW[7], MEM_DESC(DE_FW)),	/* DE FW(2MB) */
#endif

#ifdef INCLUDE_KDRV_TE
	LX_MEMCFG_ENTRY_EX(gMemCfgTE,	MEM_DESC(TE)),			/* SDEC/TE */
#endif

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec0_hma, 	 MEM_DESC(VDEC0)),		/* VDEC HMA */
#endif

#ifdef INCLUDE_KDRV_DEMOD
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD, MEM_DESC(DEMOD)),		/* DEMOD */
#endif

#ifdef INCLUDE_KDRV_OVI
    LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[0], MEM_DESC(TCON)),	/* OVI TCON */
#endif

	LX_MEMCFG_ENTRY(pqe_static_rgn_start),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(gMemCfgDe[2], MEM_DESC(DE)),		/* DE (FW+FRAME) for 60Hz Display */
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),/* VBI Buffer */
#endif

#ifdef INCLUDE_KDRV_AFE
    LX_MEMCFG_ENTRY_EX(gCvdMemCfg, MEM_DESC(CVD)),			/* CVD (3DComb H/W Memory) */
#endif

#ifdef INCLUDE_KDRV_DEMOD
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),/* DEMOD_FW */
#endif

#ifdef INCLUDE_KDRV_BE
    LX_MEMCFG_ENTRY_EX(gMemCfgBe[4], MEM_DESC(BE)),			/* BE */
#endif

	LX_MEMCFG_ENTRY(ddr0_static_rgn_start),
	LX_MEMCFG_ENTRY_EX(gMemCfgSYS, MEM_DESC(SYS)),

#ifdef INCLUDE_KDRV_SE
	LX_MEMCFG_ENTRY_EX(gMemCfgSE[1], MEM_DESC(SE)),				/* SE */
	LX_MEMCFG_ENTRY_EX(gMemCfgSE_TZFW[1], MEM_DESC(SE_TZFW)),	/* SE/TZ */
#endif

	LX_MEMCFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void BASE_PLT_SetupCommon(void)
{
	/* setup static mem region - 16MB @ L_BUS */
	ddr0_static_rgn_start.base = gMemCfgHdr[DDR_RGN_LBUS_DEV].base
								+ gMemCfgHdr[DDR_RGN_LBUS_DEV].size
								- M0_SYSTEM_RGN_SZ;
	/* setup GFX */
#ifdef INCLUDE_KDRV_GFX
    gMemCfgGfx.surface[0].size    = GFXOSD_MEM_SZ;
    gMemCfgGfx.surface[0].base      = 0xb000000;
#endif

	/* setup VDEC */
#ifdef INCLUDE_KDRV_VDEC
	vdec0_hma.base = 0x07000000;
	vdec0_hma.size = VDEC0_MEM_SZ;
#endif

    pqe_static_rgn_start.base = 0x0D000000;

}

static void BASE_PLT_Setup_256MB(void)
{
	printk("configure L18F(%2X) kdriver memory (256MB)\n", lx_chip_rev() & 0xff);

    gMemCfgHdr[DDR_RGN_LBUS_DEV].base   = M0_256M_DEV_RGN_BASE;
    gMemCfgHdr[DDR_RGN_LBUS_DEV].size   = M0_256M_DEV_RGN_SZ;

	BASE_PLT_SetupCommon();

	g_mem_desc_table = g_mem_desc_table_256MB;
}

static void BASE_PLT_Setup_512MB(void)
{
	printk("configure L18F(%2X) kdriver memory (512MB)\n", lx_chip_rev() & 0xff);

	BASE_PLT_SetupCommon();

	g_mem_desc_table = g_mem_desc_table_256MB;	/* same layout */
}

/* run the post memory layout after memory allocation
 *
 */
static void BASE_PLT_DoPostMemoryLayout(void)
{
	int i;
	int	a;
	int ret;

	struct
	{
		const char *name;
		int size;
	}
	ddr0_section[] =
	{
		{ "dpb",  __MB(52) },
		{ "vdec", -1 },
	};

	/* if memory region is set to NO_CMA, get device region from kernel to device driver with help of HMA */
	for (i=0; i<MEM_DESC_ID_MAX; i++)
	{
		switch(mem_desc[i].flag)
		{
			case MEMCFG_DESC_FLAG_NO_CMA:
			{
				if( mem_desc[i].m.base != 0x0 && mem_desc[i].m.size != 0x0)
				{
					ret = hma_pool_register_type (mem_desc[i].m.name, mem_desc[i].m.base, mem_desc[i].m.size, CMA_POOL);

					if(ret==0)
					{
						printk("(x) CMA(%s) is disabled\n", mem_desc[i].m.name);
						hma_alloc(mem_desc[i].m.name, mem_desc[i].m.size, 1<<12);
					}
				}
				else
				{
					printk("(x) CMA(%s) can't be disabled\n", mem_desc[i].m.name);
				}
			}
			break;

			case MEMCFG_DESC_FLAG_CMA:
			{
				/* do nothing */ printk("(o) CMA(%s) is enabled\n", mem_desc[i].m.name);
			}
			break;

			default:
			{
				/* do nothing */ printk("(/) CMA(%s) is skiped\n", mem_desc[i].m.name);
			}
			break;
		}
	}

	ret = hma_pool_register ("ddr0", vdec0_hma.base, vdec0_hma.size);
	if (ret < 0)
	{
		printk (KERN_ERR "hma_pool_register(ddr0) failed\n");
		return;
	}

	for (a=0; a<ARRAY_SIZE(ddr0_section); a++)
	{
		phys_addr_t base;
		const char *name;
		int size;

		name = ddr0_section[a].name;
		size = ddr0_section[a].size;

		if (size < 0)
		{
			hma_pool_status ("ddr0", hma_pool_status_max_available_size, &size);
			printk (KERN_DEBUG "remaining size for %s, %d\n", name, size);
		}

		base = hma_alloc_user ("ddr0", size, 1<<12, name);

		if (base == 0)
		{
			printk (KERN_ERR "no memory for \"%s\", %d\n", name, size);
			break;
		}

		ret = hma_pool_register_type (name, base, size, HMA_POOL);

		if (ret < 0)
		{
			printk (KERN_ERR "cannot register \"%s\" pool\n", name);
			break;
		}
	}
	hma_pool_fallback ("dpb", "surface");
}

/** main function for kdriver platform initialization
 *
 *  this function is called from base_drv.c after core initialization, chip rev detection
 * 	(including chip probe), debug initialization and pre-initialization of each driver.
 *
 */
void	BASE_PLT_Init (void)
{
	int ret;

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_DDR_512MB:	BASE_PLT_Setup_512MB(); break;
		default:					BASE_PLT_Setup_256MB(); break;
	}

	ret = BASE_DEVMEM_InitDevMem(g_mem_desc_table);
	if (ret != RET_OK) DBG_PRINT_ERROR("fatal error during making kdriver memory layout\n");

	BASE_PLT_DoPostMemoryLayout();
}

/** main function for kdriver platform probing process
 *
 *  this function is called from base_drv.c after core initialization and chip rev detection.
 *
 */
void  BASE_PLT_Probe (UINT32* plt, UINT32* board_opt)
{
	int		i;

	UINT32	hdmi_tx_output = 0;
	UINT32	plt_val = 0x0;
	UINT32	board_opt_val = 0x0;

	char	optstr[80];
	const char* pioneer_board_fmtstr[2] = {"pioneer.board=%s", "pioneer.boardopts=%s"};

	/* check HDMI Tx environment */
	if (RET_OK == OS_ScanKernelCmdline("disp=%s", optstr))
	{
		if(!strncmp(optstr, "hdmi",4))
		{
			hdmi_tx_output = 1;
		}
	}

	/* check additional configuration for the test only */
	for (i=0; i<NELEMENTS(pioneer_board_fmtstr); i++)
	{
		if (RET_OK == OS_ScanKernelCmdline(pioneer_board_fmtstr[i], optstr))
		{
			char *tok, *sav_tok;
			char delim[] = ",\t\n";

			tok = simple_strtok(optstr, delim, &sav_tok);

			while(tok)
			{
				if(!strncasecmp(tok, "256MB",5))	g_model_ctx.ddr_size    = MODEL_OPT_DDR_256MB;
				if(!strncasecmp(tok, "512MB",5))	g_model_ctx.ddr_size    = MODEL_OPT_DDR_512MB;
				if(!strncasecmp(tok, "USR0",4))		g_model_ctx.usr0	 	= MODEL_OPT_USR;
				if(!strncasecmp(tok, "USR1",4))		g_model_ctx.usr1 		= MODEL_OPT_USR;
				if(!strncasecmp(tok, "USR2",4))		g_model_ctx.usr2 		= MODEL_OPT_USR;
				if(!strncasecmp(tok, "USR3",4))		g_model_ctx.usr3 		= MODEL_OPT_USR;

				tok = simple_strtok(NULL, delim, &sav_tok);
			}
		}
	}

	/* dump board option */
	printk("\n++ BOARD OPTION ++\n");
	printk("MODEL: %s\n",	"FHD");
	printk("SOC  : %s\n", 	"L18F");
    printk("DDR  : %s\n", 	(g_model_ctx.ddr_size == MODEL_OPT_DDR_512MB)? "512MB":
                            (g_model_ctx.ddr_size == MODEL_OPT_DDR_256MB)? "256MB": "n/a");
	printk("FRC  : %s\n",	(g_model_ctx.frc_conn  == MODEL_OPT_NO_FRC)?  "NONE":
							(g_model_ctx.frc_conn  == MODEL_OPT_INT_FRC)? "INTERNAL": "n/a");
	printk("HDMI : %s\n",	(hdmi_tx_output)? "HDMI_TX" : "n/a");

	printk("USR  : 0x%02x 0x%02x 0x%02x 0x%02x\n", g_model_ctx.usr0, g_model_ctx.usr1, g_model_ctx.usr2, g_model_ctx.usr3);

	/* make board_opt variable */
	if(g_model_ctx.usr0==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR0;
	if(g_model_ctx.usr1==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR1;
	if(g_model_ctx.usr2==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR2;
	if(g_model_ctx.usr3==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR3;

	plt_val	|= (LX_CHIP_PLT_FHD|LX_BOARD_OPT_STD);

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_DDR_512MB: board_opt_val |= (LX_BOARD_OPT_DDR_512MB); break;
		case MODEL_OPT_DDR_256MB: board_opt_val |= (LX_BOARD_OPT_DDR_256MB); break;
		default: /* none */ break;
	}

	switch(g_model_ctx.frc_conn)
	{
		case MODEL_OPT_NO_FRC:		board_opt_val |= LX_BOARD_OPT_NO_FRC; break;
		case MODEL_OPT_INT_FRC:		board_opt_val |= LX_BOARD_OPT_INT_FRC; break;
		default: /* none */ break;
	}

	if(g_model_ctx.usr0==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR0;
	if(g_model_ctx.usr1==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR1;
	if(g_model_ctx.usr2==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR2;
	if(g_model_ctx.usr3==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR3;

#ifdef INCLUDE_KDRV_VER_FPGA
	board_opt_val |= LX_BOARD_OPT_FPGA;
#else
	board_opt_val |= LX_BOARD_OPT_SYSTEM;
#endif

	*plt		= plt_val;
	*board_opt	= board_opt_val;
}

/** @} */

