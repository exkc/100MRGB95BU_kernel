/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  main driver implementation for sys device.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2010.12.13
 *  note		Additional information.
 *
 *  @addtogroup lg1150_sys
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
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "sys_io.h"
#include "sys_drv.h"
#include "sys_log.h"
#include "sys_regs.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef MIN
#undef MIN
#define MIN(a,b)	(a) < (b) ? (a) : (b)
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
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

/*========================================================================================
	Implementation Group
========================================================================================*/
int SYS_IO_ReadMemArray(UINT32 addr, UINT32 size, void *data)
{
	UINT32 *io_addr;
	io_addr = (UINT32*)vmap_phys(addr, size);
	if(io_addr != NULL)
	{
		memcpy(data, io_addr, size);
		vunmap_phys(io_addr);
		return 0;
	}
	return -1;
}

int SYS_IO_WriteMemArray(UINT32 addr, UINT32 size, const void *data)
{
	UINT32 *io_addr;
	io_addr = (UINT32*)vmap_phys(addr, size);
	if(io_addr != NULL)
	{
		memcpy(io_addr, data, size);
		vunmap_phys(io_addr);
		return 0;
	}
	return -1;
}


int SYS_IO_ReadRegArray(UINT32 addr, UINT32 size, void *data)
{
	UINT32 *io_addr, *aio_addr;
	int rc = 0;

	//io_addr = (UINT32*)ioremap_nocache(addr, size);
	io_addr = (UINT32*)ioremap(addr, size);
	if(io_addr != NULL)
	{
		int i;
		UINT32 temp;
		uintptr_t remainder;
		UINT8 *v = (UINT8*)data;

		do {
			aio_addr = (UINT32*)((uintptr_t)io_addr & ~0x03);
			if(aio_addr != io_addr)	/* Address is not aligned to 4 bytes */
			{
				int ulen;
				UINT8 *s = (UINT8*)&temp;

				remainder = (uintptr_t)io_addr & 0x03;
				temp = SYS_READ32(aio_addr);
				s += remainder;
				ulen = MIN(size, 4-remainder);
				for(i=0; i<ulen; i++)
				{
					*v++ = s[i];
				}

				aio_addr++;
				size -= ulen;
				if(size == 0) break;
			}

			remainder = (uintptr_t)size%4;
			if((uintptr_t)v&0x03)	/* Data is not aligned to 4 bytes */
			{
				UINT8 *s = (UINT8*)&temp;
				for(i=0; i<size/4; i++)
				{
					temp = SYS_READ32(aio_addr);
					*v++ = s[0];
					*v++ = s[1];
					*v++ = s[2];
					*v++ = s[3];
					aio_addr++;
				}
			}
			else
			{
				for(i=0; i<size/4; i++)
				{
					*((volatile UINT32*)v) = SYS_READ32(aio_addr);
					v += 4;
					aio_addr++;
				}
			}

			if(remainder)
			{
				UINT8 *s = (UINT8*)&temp;
				temp = SYS_READ32(aio_addr);
				for(i=0; i<remainder; i++)
				{
					*v++ = s[i];
				}
			}
		} while(0);

		iounmap(io_addr);
	}
	else
	{
		SYS_ERROR("Can't ioremap !!!\n");
		rc = -1;
	}

	return rc;
}

int SYS_IO_WriteRegArray(UINT32 addr, UINT32 size, const void *data)
{
	UINT32 *io_addr, *aio_addr;

	//io_addr = (UINT32*)ioremap_nocache(addr, size);
	io_addr = (UINT32*)ioremap(addr, size);
	if(io_addr != NULL)
	{
		int i;
		UINT32 temp;
		uintptr_t remainder;
		UINT8 *v = (UINT8*)data;

		do {
			aio_addr = (UINT32*)((uintptr_t)io_addr & ~0x03);
			if(aio_addr != io_addr)	/* Address is not aligned to 4 bytes */
			{
				int ulen;
				UINT8 *s = (UINT8*)&temp;

				remainder = (uintptr_t)io_addr & 0x03;
				temp = SYS_READ32(aio_addr);
				s += remainder;
				ulen = MIN(size, 4-remainder);
				for(i=0; i<ulen; i++)
				{
					s[i] = *v++;
				}
				SYS_WRITE32(aio_addr, temp);

				aio_addr++;
				size -= ulen;
				if(size == 0) break;
			}

			remainder = (uintptr_t)size%4;
			if((uintptr_t)v&0x03)	/* Data is not aligned to 4 bytes */
			{
				//UINT32 pv, nv;	// will modify next time. read one time
				UINT8 *s = (UINT8*)&temp;
				for(i=0; i<size/4; i++)
				{
					s[0] = *v++;
					s[1] = *v++;
					s[2] = *v++;
					s[3] = *v++;
					SYS_WRITE32(aio_addr, temp);
					aio_addr++;
				}
			}
			else
			{
				for(i=0; i<size/4; i++)
				{
					SYS_WRITE32(aio_addr, *((volatile UINT32*)v));
					v += 4;
					aio_addr++;
				}
			}

			if(remainder)
			{
				UINT8 *s = (UINT8*)&temp;
				temp = SYS_READ32(aio_addr);
				for(i=0; i<remainder; i++)
				{
					s[i] = *v++;
				}
				SYS_WRITE32(aio_addr, temp);
			}
		} while(0);

		iounmap(io_addr);
	}

	return 0;

}

#ifdef INCLUDE_M14_CHIP_KDRV
// TODO: Move these functions to chip directory
static int SYS_M14A0_SetSpreadSpectrum(LX_SPREAD_SPECTRUM_T *ss)
{
	struct ss_display_pll
	{
		LX_SS_RATIO_T ratio;
		UINT32	udex_ctrl;
		UINT32	msex_ctrl;
	};

	const struct ss_display_pll ss_display_pll[] =
	{
		{LX_SS_RATIO__OFF, 0x0, 0x00},
		{LX_SS_RATIO_0_75, 0x3, 0x17},
		{LX_SS_RATIO_1_00, 0x4, 0x12},
		{LX_SS_RATIO_1_25, 0x7, 0x0a},
		{LX_SS_RATIO_1_50, 0x6, 0x0c},
	};
	int i;
	int rc = -1;

	if(ss->pll == LX_SS_DISPLAY)
	{
		SYS_DEBUG("set ss disp pll, ratio %d\n", ss->ratio);
		for(i=0; i<sizeof(ss_display_pll)/sizeof(struct ss_display_pll); i++)
		{
			const struct ss_display_pll *pll = &ss_display_pll[i];
			if(ss->ratio == pll->ratio)
			{
				CTOP_CTRL_M14A0_RdFL(ctr83);
				CTOP_CTRL_M14A0_Wr01(ctr83, disp_udex_ctrl, pll->udex_ctrl);
				CTOP_CTRL_M14A0_Wr01(ctr83, disp_msex_ctrl, pll->msex_ctrl);
				CTOP_CTRL_M14A0_WrFL(ctr83);
				rc = 0;
				break;
			}
		}
	}

	return rc;
}

static int SYS_M14B0_SetSpreadSpectrum(LX_SPREAD_SPECTRUM_T *ss)
{
	struct main_pll
	{
		LX_SS_RATIO_T ratio;
		UINT32	value[2];
	};

	struct ss_display_pll
	{
		LX_SS_RATIO_T ratio;
		UINT32	udex_ctrl;
		UINT32	msex_ctrl;
	};

	const struct main_pll main_pll[] =
	{
		{LX_SS_RATIO__OFF, {0x01000000, 0x981D4000}},
		{LX_SS_RATIO_0_25, {0xC12E0000, 0x80244001}},
		{LX_SS_RATIO_0_50, {0x812E0000, 0x80244001}},
		{LX_SS_RATIO_0_75, {0x43220000, 0x80243C01}},
		{LX_SS_RATIO_1_00, {0x432E0000, 0x80243C01}},
	};

	const struct ss_display_pll ss_display_pll[] =
	{
		{LX_SS_RATIO__OFF, 0x0, 0x00},
		{LX_SS_RATIO_0_75, 0x3, 0x17},
		{LX_SS_RATIO_1_00, 0x4, 0x12},
		{LX_SS_RATIO_1_25, 0x7, 0x0a},
		{LX_SS_RATIO_1_50, 0x6, 0x0c},
	};

	int i;
	int rc = -1;

	if(ss->pll == LX_SS_MAIN_PLL_1 || ss->pll == LX_SS_MAIN_PLL_2)
	{
		SYS_DEBUG("set ss main pll %d, ratio %d\n", ss->pll - 1, ss->ratio);
		for(i=0; i<sizeof(main_pll)/sizeof(struct main_pll); i++)
		{
			const struct main_pll *pll = &main_pll[i];
			if(ss->ratio == pll->ratio)
			{
				if(ss->pll == LX_SS_MAIN_PLL_1)
				{
					CTOP_CTRL_M14B0_Wr(TOP, ctr02, pll->value[0]);
					CTOP_CTRL_M14B0_Wr(TOP, ctr03, pll->value[1]);
					CTOP_CTRL_M14B0_WrFL(TOP, ctr02);
					CTOP_CTRL_M14B0_WrFL(TOP, ctr03);
				}
				else
				{
					CTOP_CTRL_M14B0_Wr(TOP, ctr04, pll->value[0]);
					CTOP_CTRL_M14B0_Wr(TOP, ctr05, pll->value[1]);
					CTOP_CTRL_M14B0_WrFL(TOP, ctr04);
					CTOP_CTRL_M14B0_WrFL(TOP, ctr05);
				}
				rc = 0;
				break;
			}
		}
	}
	else if(ss->pll == LX_SS_DISPLAY)
	{
		SYS_DEBUG("set ss disp pll, ratio %d\n", ss->ratio);
		for(i=0; i<sizeof(ss_display_pll)/sizeof(struct ss_display_pll); i++)
		{
			const struct ss_display_pll *pll = &ss_display_pll[i];
			if(ss->ratio == pll->ratio)
			{
				CTOP_CTRL_M14B0_RdFL(LEFT, ctr93);
				CTOP_CTRL_M14B0_Wr01(LEFT, ctr93, disp_udex_ctrl, pll->udex_ctrl);
				CTOP_CTRL_M14B0_Wr01(LEFT, ctr93, disp_msex_ctrl, pll->msex_ctrl);
				CTOP_CTRL_M14B0_WrFL(LEFT, ctr93);
				rc = 0;
				break;
			}
		}
	}

	return rc;
}
#endif

#ifdef INCLUDE_H15_CHIP_KDRV
static int SYS_H15A0_SetSpreadSpectrum(LX_SPREAD_SPECTRUM_T *ss)
{
	int rc = -1;

	if(ss->pll == LX_SS_CPU_PLL)
	{
		SYS_DEBUG("set ss cpu pll, ratio %d\n", ss->ratio);
		rc = 0;
	}
	else if(ss->pll == LX_SS_MAIN_PLL_0 ||
			ss->pll == LX_SS_MAIN_PLL_1 ||
			ss->pll == LX_SS_MAIN_PLL_2)
	{
		SYS_DEBUG("set ss main pll %d, ratio %d\n", ss->pll - 1, ss->ratio);
		rc = 0;
	}
	else if(ss->pll == LX_SS_DISPLAY)
	{
		SYS_DEBUG("set ss disp pll, ratio %d\n", ss->ratio);
		rc = 0;
	}
	else
	{

	}

	return rc;
}
#endif

/********************************************************************************************/
int SYS_IO_SetSpreadSpectrum(LX_SPREAD_SPECTRUM_T *ss)
{

	if(unlikely(ss == NULL))
		return -1;

	if(0){}
#ifdef INCLUDE_H15_CHIP_KDRV
	else if(lx_chip_rev() >= LX_CHIP_REV(H15,A0))
	{
		return SYS_H15A0_SetSpreadSpectrum(ss);
	}
#endif
#ifdef INCLUDE_H14_CHIP_KDRV
	else if (lx_chip_rev() >= LX_CHIP_REV(H14,A0))
	{

	}
#endif
#ifdef INCLUDE_M14_CHIP_KDRV
	else if (lx_chip_rev() >= LX_CHIP_REV(M14,A0))
	{
		if (lx_chip_rev() >= LX_CHIP_REV(M14,B0))
		{
			return SYS_M14B0_SetSpreadSpectrum(ss);
		}
		else
		{
			return SYS_M14A0_SetSpreadSpectrum(ss);
		}
	}
#endif

	return -1;
}


/********************************************************************************************/
#define KHZ			(1000)
#define MHZ			(1000*KHZ)
#define GHZ			(1000*MHZ)

#define DEBUG(fmt, args...)		do{}while(0)
//#define DEBUG(fmt, args...) 	printk(fmt, ##args)
#define ERROR(fmt, args...) 	printk(fmt, ##args)

#define	REG_OFFSET(x)			(4*x)

#define FIN_CMN 				(24)
#define FIN_DISP				(27)

/* GET_RESULT_RF *10 */
#define GET_RESULT_RF(ACCURACY) \
({ \
	 u32 v = 0; \
	 if(ACCURACY == 3) v = 5; \
	 if(ACCURACY == 2) v = 10; \
	 if(ACCURACY == 1) v = 20; \
	 if(ACCURACY == 0 || ACCURACY >= 4) v = 40; \
	 v; \
})

/* SPREAD_RATIO_OUT * 1000 */
#define SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF) \
	( (UPDN_MAX)*1000 * 50 * RESULT_RF / (60*((4*NPC)+NSC)) )

#define MOD_FREQ_OUT(FIN, M, MOD_FREQ, UPDN_MAX) \
	( (FIN/M) * 1000000 / ((MOD_FREQ+1)*(UPDN_MAX+2)) )


#ifdef INCLUDE_O18_CHIP_KDRV
static void _o18_get_clk_info(SYS_SOC_CLK_T *clk_param, struct seq_file *m)
{
#undef PLL_CLK_OUT
#define PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN) \
	((((4 * NPC + NSC) * (ulong)(FIN*MHZ)) + \
	  ((ulong)FINE_DIV * FINE_CTRL * 125 * FIN * MHZ / 1000))/ (M))

	typedef struct
	{
		uint32_t cpu_pll_out;
		uint32_t m0_pll_out;
		uint32_t m1_pll_out;
		uint32_t m2_pll_out;
		uint32_t core_pll_out;
		uint32_t codec_pll_out;
		uint32_t gpu_pll_out;
		uint32_t disp_pll_out;

		uint32_t cpu_core_clk;
		uint32_t peri_bus_clk;
		uint32_t m0_ddr_clk;
		uint32_t m1_ddr_clk;
		uint32_t m2_ddr_clk;
		uint32_t gpu_clk;

		uint32_t cpu_pll_ss;
		uint32_t m0_pll_ss;
		uint32_t m1_pll_ss;
		uint32_t m2_pll_ss;
		uint32_t core_pll_ss;
		uint32_t codec_pll_ss;
		uint32_t gpu_pll_ss;
		uint32_t disp_pll_ss;

		uint32_t cpu_spread_ratio;
		uint32_t cpu_mod_freq;
		uint32_t m0_spread_ratio;
		uint32_t m0_mod_freq;
		uint32_t m1_spread_ratio;
		uint32_t m1_mod_freq;
		uint32_t m2_spread_ratio;
		uint32_t m2_mod_freq;
		uint32_t core_spread_ratio;
		uint32_t core_mod_freq;
		uint32_t codec_spread_ratio;
		uint32_t codec_mod_freq;
		uint32_t gpu_spread_ratio;
		uint32_t gpu_mod_freq;
		uint32_t disp_spread_ratio;
		uint32_t disp_mod_freq;
	} clk_detect_t;

	clk_detect_t clk = {0,};

	u32 M, NPC, NSC, out_div, pre_div;
	u32 ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF;
	u32 FINE_DIV, FINE_CTRL;

	{
		/* read cpu pll */
		CTOP_ME1_CTR01_O18_A0	ctop_me1_ctr01;
		CTOP_ME1_CTR02_O18_A0	ctop_me1_ctr02;

		*(u32*)(&ctop_me1_ctr01) = CTOP_CTRL_O18A0_READ(CTOP_ME1, REG_OFFSET(1));
		*(u32*)(&ctop_me1_ctr02) = CTOP_CTRL_O18A0_READ(CTOP_ME1, REG_OFFSET(2));

		M = ctop_me1_ctr01.reg_aiopll_m_5_0_;
		NPC = ctop_me1_ctr02.reg_aiopll_npc_5_0_;
		NSC = ctop_me1_ctr02.reg_aiopll_nsc_3_0_;
		out_div = ctop_me1_ctr02.reg_aiopll_fout_od_1_0_;
		FINE_DIV = ctop_me1_ctr01.reg_aiopll_fine_div;
		FINE_CTRL = ctop_me1_ctr02.reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.cpu_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.cpu_pll_ss = ctop_me1_ctr01.reg_aiopll_dss ? 0 : 1;

		DEBUG("cpu pll m : %u, npc : %u, nsc : %u ,out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("cpu pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("cpu pll out : %u\n", clk.cpu_pll_out);
		DEBUG("cpu pll ss : %s\n", clk.cpu_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_me1_ctr01.reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_me1_ctr01.reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_me1_ctr01.reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.cpu_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.cpu_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("cpu accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read m0 pll */
		CTOP_TIVG_CTR13_O18_A0	ctop_tivg_ctr13;
		CTOP_TIVG_CTR14_O18_A0	ctop_tivg_ctr14;

		*(u32*)(&ctop_tivg_ctr13) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(13));
		*(u32*)(&ctop_tivg_ctr14) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(14));

		M = ctop_tivg_ctr13.m0_reg_aiopll_m_5_0_;
		NPC = ctop_tivg_ctr14.m0_reg_aiopll_npc_5_0_;
		NSC = ctop_tivg_ctr14.m0_reg_aiopll_nsc_3_0_;
		out_div = ctop_tivg_ctr14.m0_reg_aiopll_fout_od_1_0_;
		FINE_DIV = ctop_tivg_ctr13.m0_reg_aiopll_fine_div;
		FINE_CTRL = ctop_tivg_ctr14.m0_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.m0_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.m0_pll_ss = ctop_tivg_ctr13.m0_reg_aiopll_dss ? 0 : 1;

		DEBUG("m0 pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("m0 pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("m0 pll out : %u\n", clk.m0_pll_out);
		DEBUG("m0 pll ss : %s\n", clk.m0_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_tivg_ctr13.m0_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_tivg_ctr13.m0_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_tivg_ctr13.m0_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.m0_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.m0_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("m0 accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read m1 pll */
		CTOP_TIVG_CTR16_O18_A0	ctop_tivg_ctr16;
		CTOP_TIVG_CTR17_O18_A0	ctop_tivg_ctr17;

		*(u32*)(&ctop_tivg_ctr16) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(16));
		*(u32*)(&ctop_tivg_ctr17) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(17));

		M = ctop_tivg_ctr16.m1_reg_aiopll_m_5_0_;
		NPC = ctop_tivg_ctr17.m1_reg_aiopll_npc_5_0_;
		NSC = ctop_tivg_ctr17.m1_reg_aiopll_nsc_3_0_;
		out_div = ctop_tivg_ctr17.m1_reg_aiopll_fout_od_1_0_;
		FINE_DIV = ctop_tivg_ctr16.m1_reg_aiopll_fine_div;
		FINE_CTRL = ctop_tivg_ctr17.m1_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.m1_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.m1_pll_ss = ctop_tivg_ctr16.m1_reg_aiopll_dss ? 0 : 1;

		DEBUG("m1 pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("m1 pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("m1 pll out : %u\n", clk.m1_pll_out);
		DEBUG("m1 pll ss : %s\n", clk.m1_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_tivg_ctr16.m1_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_tivg_ctr16.m1_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_tivg_ctr16.m1_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.m1_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.m1_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("m1 accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read m2 pll */
		CTOP_ME1_CTR05_O18_A0	ctop_me1_ctr05;
		CTOP_ME1_CTR06_O18_A0	ctop_me1_ctr06;

		*(u32*)(&ctop_me1_ctr05) = CTOP_CTRL_O18A0_READ(CTOP_ME1, REG_OFFSET(5));
		*(u32*)(&ctop_me1_ctr06) = CTOP_CTRL_O18A0_READ(CTOP_ME1, REG_OFFSET(6));

		M = ctop_me1_ctr05.m2_reg_aiopll_m_5_0_;
		NPC = ctop_me1_ctr06.m2_reg_aiopll_npc_5_0_;
		NSC = ctop_me1_ctr06.m2_reg_aiopll_nsc_3_0_;
		out_div = ctop_me1_ctr06.m2_reg_aiopll_fout_od_1_0_;
		FINE_DIV = ctop_me1_ctr05.m2_reg_aiopll_fine_div;
		FINE_CTRL = ctop_me1_ctr06.m2_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.m2_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.m2_pll_ss = ctop_me1_ctr05.m2_reg_aiopll_dss ? 0 : 1;

		DEBUG("m2 pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("m2 pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("m2 pll out : %u\n", clk.m2_pll_out);
		DEBUG("m2 pll ss : %s\n", clk.m2_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_me1_ctr05.m2_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_me1_ctr05.m2_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_me1_ctr05.m2_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.m2_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.m2_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("m2 accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read core pll */
		CTOP_TIVG_CTR10_O18_A0	ctop_tivg_ctr10;
		CTOP_TIVG_CTR11_O18_A0	ctop_tivg_ctr11;

		*(u32*)(&ctop_tivg_ctr10) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(10));
		*(u32*)(&ctop_tivg_ctr11) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(11));

		M = ctop_tivg_ctr10.core_reg_aiopll_m_5_0_;
		NPC = ctop_tivg_ctr11.core_reg_aiopll_npc_5_0_;
		NSC = ctop_tivg_ctr11.core_reg_aiopll_nsc_3_0_;
		out_div = ctop_tivg_ctr11.core_reg_aiopll_fout_od_1_0_;
		FINE_DIV = ctop_tivg_ctr10.core_reg_aiopll_fine_div;
		FINE_CTRL = ctop_tivg_ctr11.core_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.core_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.core_pll_ss = ctop_tivg_ctr10.core_reg_aiopll_dss ? 0 : 1;

		DEBUG("core pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("core pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("core pll out : %u\n", clk.core_pll_out);
		DEBUG("core pll ss : %s\n", clk.core_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_tivg_ctr10.core_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_tivg_ctr10.core_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_tivg_ctr10.core_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.core_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.core_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("core accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read codec pll */
		CTOP_TIVG_CTR07_O18_A0	ctop_tivg_ctr07;
		CTOP_TIVG_CTR08_O18_A0	ctop_tivg_ctr08;

		*(u32*)(&ctop_tivg_ctr07) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(7));
		*(u32*)(&ctop_tivg_ctr08) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(8));

		M = ctop_tivg_ctr07.codec_reg_aiopll_m_5_0_;
		NPC = ctop_tivg_ctr08.codec_reg_aiopll_npc_5_0_;
		NSC = ctop_tivg_ctr08.codec_reg_aiopll_nsc_3_0_;
		out_div = ctop_tivg_ctr08.codec_reg_aiopll_fout_od_1_0_;
		FINE_DIV = ctop_tivg_ctr07.codec_reg_aiopll_fine_div;
		FINE_CTRL = ctop_tivg_ctr08.codec_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.codec_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.codec_pll_ss = ctop_tivg_ctr07.codec_reg_aiopll_dss ? 0 : 1;

		DEBUG("codec pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("codec pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("codec pll out : %u\n", clk.codec_pll_out);
		DEBUG("codec pll ss : %s\n", clk.codec_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_tivg_ctr07.codec_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_tivg_ctr07.codec_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_tivg_ctr07.codec_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.codec_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.codec_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("codec accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);

		DEBUG("\n");
	}

	{
		/* read gpu pll */
		CTOP_CCO_CTR04_O18_A0	ctop_cco_ctr04;
		CTOP_CCO_CTR05_O18_A0	ctop_cco_ctr05;

		*(u32*)(&ctop_cco_ctr04) = CTOP_CTRL_O18A0_READ(CTOP_CCO, REG_OFFSET(4));
		*(u32*)(&ctop_cco_ctr05) = CTOP_CTRL_O18A0_READ(CTOP_CCO, REG_OFFSET(5));

		M = ctop_cco_ctr04.gpu_reg_aiopll_m_5_0_;
		NPC = ctop_cco_ctr05.gpu_reg_aiopll_npc_5_0_;
		NSC = ctop_cco_ctr05.gpu_reg_aiopll_nsc_3_0_;
		out_div = ctop_cco_ctr05.gpu_reg_aiopll_fout2_od_2_0_;  // 018, (fout2_od * fout2_div = 3)
		pre_div = ctop_cco_ctr05.gpu_reg_aiopll_pre_fout2_div_2_0_;
		FINE_DIV = ctop_cco_ctr04.gpu_reg_aiopll_fine_div;
		FINE_CTRL = ctop_cco_ctr05.gpu_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.gpu_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_CMN) >> out_div;
		clk.gpu_pll_ss = ctop_cco_ctr04.gpu_reg_aiopll_dss ? 0 : 1;

		switch(pre_div)
		{
			case 0:
				pre_div = 2;
				break;
			case 1:
				pre_div = 3; // default
				break;
			case 2:
				pre_div = 4;
				break;
			case 3:
				pre_div = 5;
				break;
			default:
				pre_div = 1;
				break;
		}
		clk.gpu_pll_out = clk.gpu_pll_out / pre_div;

		DEBUG("gpu pll m : %u, npc : %u, nsc : %u, out_div : %u, pre_div : %u\n",
				M, NPC, NSC, out_div, pre_div);
		DEBUG("gpu pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("gpu pll out : %u\n", clk.gpu_pll_out);
		DEBUG("gpu pll ss : %s\n", clk.gpu_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_cco_ctr04.gpu_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_cco_ctr04.gpu_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_cco_ctr04.gpu_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.gpu_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.gpu_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("gpu accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read disp pll */
		CTOP_CCO_CTR01_O18_A0	ctop_cco_ctr01;
		CTOP_CCO_CTR02_O18_A0	ctop_cco_ctr02;

		*(u32*)(&ctop_cco_ctr01) = CTOP_CTRL_O18A0_READ(CTOP_CCO, REG_OFFSET(1));
		*(u32*)(&ctop_cco_ctr02) = CTOP_CTRL_O18A0_READ(CTOP_CCO, REG_OFFSET(2));

		M = ctop_cco_ctr01.disp_reg_aiopll_m_5_0_;
		NPC = ctop_cco_ctr02.disp_reg_aiopll_npc_5_0_;
		NSC = ctop_cco_ctr02.disp_reg_aiopll_nsc_3_0_;
		out_div = ctop_cco_ctr02.disp_reg_aiopll_fout2_od_2_0_;  // 018, (fout2_od * fout2_div = 4)
		pre_div = ctop_cco_ctr02.disp_reg_aiopll_pre_fout2_div_2_0_;
		FINE_DIV = ctop_cco_ctr01.disp_reg_aiopll_fine_div;
		FINE_CTRL = ctop_cco_ctr02.disp_reg_aiopll_fine_control_2_0_;

		if(!M) M = 1;

		clk.disp_pll_out = PLL_CLK_OUT(M, NPC, NSC, FINE_DIV, FINE_CTRL, FIN_DISP) >> out_div;	// disp FIN is 27MHz
		clk.disp_pll_ss = ctop_cco_ctr01.disp_reg_aiopll_dss ? 0 : 1;

		switch(pre_div)
		{
			case 0:
				pre_div = 2;
				break;
			case 1:
				pre_div = 3;
				break;
			case 2:
				pre_div = 4;
				break;
			case 3:
				pre_div = 5;
				break;
			default:
				pre_div = 1; // default
				break;
		}
		clk.disp_pll_out = clk.disp_pll_out / pre_div;

		DEBUG("disp pll m : %u, npc : %u, nsc : %u, out_div : %u, pre_div : %u\n",
				M, NPC, NSC, out_div, pre_div);
		DEBUG("disp pll fine div : %u, fine_ctrl : %u\n", FINE_DIV, FINE_CTRL);
		DEBUG("disp pll out : %u\n", clk.disp_pll_out);
		DEBUG("disp pll ss : %s\n", clk.disp_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_cco_ctr01.disp_reg_aiopll_accuracy_1_0_;
		UPDN_MAX = ctop_cco_ctr01.disp_reg_aiopll_updn_max_6_0_;
		MOD_FREQ = ctop_cco_ctr01.disp_reg_aiopll_mod_freq_8_0_;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.disp_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.disp_mod_freq = MOD_FREQ_OUT(FIN_DISP, M, MOD_FREQ, UPDN_MAX);
		DEBUG("disp accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	/* cpu clock */
	clk.cpu_core_clk = clk.cpu_pll_out >> 1;

	/* pll mux */
	CTOP_TIVG_CTR06_O18_A0	ctop_tivg_ctr06;
	*(u32*)(&ctop_tivg_ctr06) = CTOP_CTRL_O18A0_READ(CTOP_TIVG, REG_OFFSET(6));

	/* m0 clk */
	if(!ctop_tivg_ctr06.pll_sel_m0)//m0 pll -> m0 ddr
		clk.m0_ddr_clk = clk.m0_pll_out >> 1;
	else//m1 pll -> m0 ddr
		clk.m0_ddr_clk = clk.m1_pll_out >> 1;

	/* m1 clk */
	if(!ctop_tivg_ctr06.pll_sel_m1)//m0 pll -> m1 ddr
		clk.m1_ddr_clk = clk.m0_pll_out >> 1;
	else//m1 pll -> m1 ddr
		clk.m1_ddr_clk = clk.m1_pll_out >> 1;

	/* m2 clk */
	clk.m2_ddr_clk = clk.m2_pll_out >> 1;

	/* peri clk (core) */
	if(ctop_tivg_ctr06.pll_sel_core == 0)
		clk.peri_bus_clk = clk.core_pll_out >> 2;
	else if(ctop_tivg_ctr06.pll_sel_core == 1)
		clk.peri_bus_clk = clk.codec_pll_out / 6;
	else if(ctop_tivg_ctr06.pll_sel_core == 2)
		clk.peri_bus_clk = clk.m1_pll_out >> 2;

	clk.peri_bus_clk = clk.peri_bus_clk >> 1;//peri_bus_clk = core clk/2

	/* gpu clk */
	clk.gpu_clk = clk.gpu_pll_out;


	/* MHz */
	clk_param->cpu_clk = clk.cpu_core_clk/MHZ;
	clk_param->peri_clk = clk.peri_bus_clk/MHZ;
	clk_param->gpu_clk = clk.gpu_pll_out/MHZ;
	clk_param->ddr_clk[0] = clk.m0_ddr_clk/MHZ;
	clk_param->ddr_clk[1] = clk.m1_ddr_clk/MHZ;
	clk_param->ddr_clk[2] = clk.m2_ddr_clk/MHZ;
	clk_param->ss = clk.m0_pll_ss | clk.m1_pll_ss | clk.m2_pll_ss;

	/* print PLL OUT, SS, CLK SRC */
	if(m)
	{
		seq_printf(m, "\n============ PLL OUT =============\n");
		seq_printf(m, "cpu pll out      : %10u\n", clk.cpu_pll_out);
		seq_printf(m, "m0 pll out       : %10u\n", clk.m0_pll_out);
		seq_printf(m, "m1 pll out       : %10u\n", clk.m1_pll_out);
		seq_printf(m, "m2 pll out       : %10u\n", clk.m2_pll_out);
		seq_printf(m, "core pll out     : %10u\n", clk.core_pll_out);
		seq_printf(m, "codec pll out    : %10u\n", clk.codec_pll_out);
		seq_printf(m, "gpu pll out      : %10u\n", clk.gpu_pll_out);
		seq_printf(m, "disp pll out     : %10u\n", clk.disp_pll_out);
		seq_printf(m, "\n============ SS  =============\n");
		seq_printf(m, "cpu pll ss      : %s\n", clk.cpu_pll_ss ? "ON" : "OFF");
		seq_printf(m, "m0 pll ss       : %s\n", clk.m0_pll_ss ? "ON" : "OFF");
		seq_printf(m, "m1 pll ss       : %s\n", clk.m1_pll_ss ? "ON" : "OFF");
		seq_printf(m, "m2 pll ss       : %s\n", clk.m2_pll_ss ? "ON" : "OFF");
		seq_printf(m, "core pll ss     : %s\n", clk.core_pll_ss ? "ON" : "OFF");
		seq_printf(m, "codec pll ss    : %s\n", clk.codec_pll_ss ? "ON" : "OFF");
		seq_printf(m, "gpu pll ss      : %s\n", clk.gpu_pll_ss ? "ON" : "OFF");
		seq_printf(m, "disp pll ss     : %s\n", clk.disp_pll_ss ? "ON" : "OFF");
		seq_printf(m, "\n============ CLK SRC  =============\n");
		seq_printf(m, "M0 CLK SRC   : %s\n", !ctop_tivg_ctr06.pll_sel_m0 ? "M0 PLL" : "M1 PLL");
		seq_printf(m, "M1 CLK SRC   : %s\n", !ctop_tivg_ctr06.pll_sel_m1 ? "M0 PLL" : "M1 PLL");
		seq_printf(m, "M2 CLK SRC   : %s\n", "M2 PLL");
		seq_printf(m, "PERI CLK SRC : %s\n", !ctop_tivg_ctr06.pll_sel_core ? "CORE PLL" :
				ctop_tivg_ctr06.pll_sel_core==1 ? "CODEC PLL" : "M1 PLL");

		seq_printf(m, "\n============ SPREAD RATIO =============\n");
		if(clk.cpu_pll_ss)
			seq_printf(m, "cpu spread_ratio   : %u.%4u, mod_freq : %uHz\n",
					clk.cpu_spread_ratio/10000, clk.cpu_spread_ratio%10000, clk.cpu_mod_freq);
		if(clk.m0_pll_ss)
			seq_printf(m, "m0 spread_ratio    : %u.%4u, mod_freq : %uHz\n",
					clk.m0_spread_ratio/10000, clk.m0_spread_ratio%10000, clk.m0_mod_freq);
		if(clk.m1_pll_ss)
			seq_printf(m, "m1 spread_ratio    : %u.%4u, mod_freq : %uHz\n",
				clk.m1_spread_ratio/10000, clk.m1_spread_ratio%10000, clk.m1_mod_freq);
		if(clk.m2_pll_ss)
			seq_printf(m, "m2 spread_ratio    : %u.%4u, mod_freq : %uHz\n",
				clk.m2_spread_ratio/10000, clk.m2_spread_ratio%10000, clk.m2_mod_freq);
		if(clk.core_pll_ss)
			seq_printf(m, "core spread_ratio  : %u.%4u, mod_freq : %uHz\n",
				clk.core_spread_ratio/10000, clk.core_spread_ratio%10000, clk.core_mod_freq);
		if(clk.codec_pll_ss)
			seq_printf(m, "codec spread_ratio : %u.%4u, mod_freq : %uHz\n",
				clk.codec_spread_ratio/10000, clk.codec_spread_ratio%10000, clk.codec_mod_freq);
		if(clk.gpu_pll_ss)
			seq_printf(m, "gpu spread_ratio   : %u.%4u, mod_freq : %uHz\n",
				clk.gpu_spread_ratio/10000, clk.gpu_spread_ratio%10000, clk.gpu_mod_freq);
		if(clk.disp_pll_ss)
			seq_printf(m, "disp spread_ratio  : %u.%4u, mod_freq : %uHz\n",
				clk.disp_spread_ratio/10000, clk.disp_spread_ratio%10000, clk.disp_mod_freq);
		seq_printf(m, "\n");
	}
}
#endif //#ifdef INCLUDE_O18_CHIP_KDRV


#ifdef INCLUDE_M17_CHIP_KDRV
static void _m17_get_clk_info(SYS_SOC_CLK_T *clk_param, struct seq_file *m)
{
#undef PLL_CLK_OUT
#define PLL_CLK_OUT(M, NPC, NSC, FIN) \
				(((4 * NPC + NSC) * (ulong)(FIN*MHZ))/ (M))

	typedef struct
	{
		uint32_t cpu_pll_out;
		uint32_t m0_pll_out;
		uint32_t m1_pll_out;
		uint32_t core_pll_out;
		uint32_t codec_pll_out;
		uint32_t gpu_pll_out;
		uint32_t disp_pll_out;

		uint32_t cpu_core_clk;
		uint32_t peri_bus_clk;
		uint32_t lm_ddr_clk;
		uint32_t gm_ddr_clk;
		uint32_t gpu_clk;

		uint32_t cpu_pll_ss;
		uint32_t m0_pll_ss;
		uint32_t m1_pll_ss;
		uint32_t core_pll_ss;
		uint32_t codec_pll_ss;
		uint32_t gpu_pll_ss;
		uint32_t disp_pll_ss;

		uint32_t cpu_spread_ratio;
		uint32_t cpu_mod_freq;
		uint32_t m0_spread_ratio;
		uint32_t m0_mod_freq;
		uint32_t m1_spread_ratio;
		uint32_t m1_mod_freq;
		uint32_t core_spread_ratio;
		uint32_t core_mod_freq;
		uint32_t codec_spread_ratio;
		uint32_t codec_mod_freq;
		uint32_t gpu_spread_ratio;
		uint32_t gpu_mod_freq;
		uint32_t disp_spread_ratio;
		uint32_t disp_mod_freq;
	} clk_detect_t;

	clk_detect_t clk = {0,};

	u32 M, NPC, NSC, out_div, pre_div;
	u32 ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF;

	{
		/* read cpu pll */
		CTOP_FME0_CTOP_FME0_R13_M17_A0 	ctop_fme0_r13;
		CTOP_FME0_CTOP_FME0_R14_M17_A0 	ctop_fme0_r14;

		*(u32*)(&ctop_fme0_r13) = CTOP_CTRL_M17A0_READ(FME0, REG_OFFSET(13));
		*(u32*)(&ctop_fme0_r14) = CTOP_CTRL_M17A0_READ(FME0, REG_OFFSET(14));

		M = ctop_fme0_r13.cpupll_m;
		NPC = ctop_fme0_r14.cpupll_npc;
		NSC = ctop_fme0_r14.cpupll_nsc;
		out_div = ctop_fme0_r14.cpupll_fout_od;

		if(!M) M = 1;

		clk.cpu_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_CMN) >> out_div;
		clk.cpu_pll_ss = ctop_fme0_r13.cpupll_dss ? 0 : 1;

		DEBUG("cpu pll m : %u, npc : %u, nsc : %u , out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("cpu pll out : %u\n", clk.cpu_pll_out);
		DEBUG("cpu pll ss : %s\n", clk.cpu_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_fme0_r13.cpupll_accuracy;
		UPDN_MAX = ctop_fme0_r13.cpupll_updn_max;
		MOD_FREQ = ctop_fme0_r13.cpupll_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.cpu_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.cpu_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("cpu accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read m0 pll */
		CTOP_GFX_CTOP_GFX_R16_M17_A0 	ctop_gfx_r16;
		CTOP_GFX_CTOP_GFX_R17_M17_A0 	ctop_gfx_r17;

		*(u32*)(&ctop_gfx_r16) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(16));
		*(u32*)(&ctop_gfx_r17) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(17));

		M = ctop_gfx_r16.m0pll_m;
		NPC = ctop_gfx_r17.m0pll_npc;
		NSC = ctop_gfx_r17.m0pll_nsc;
		out_div = ctop_gfx_r17.m0pll_fout_od;

		if(!M) M = 1;

		clk.m0_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_CMN) >> out_div;
		clk.m0_pll_ss = ctop_gfx_r16.m0pll_dss ? 0 : 1;

		DEBUG("m0 pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("m0 pll out : %u\n", clk.m0_pll_out);
		DEBUG("m0 pll ss : %s\n", clk.m0_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_gfx_r16.m0pll_accuracy;
		UPDN_MAX = ctop_gfx_r16.m0pll_updn_max;
		MOD_FREQ = ctop_gfx_r16.m0pll_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.m0_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.m0_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("m0 accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read m1 pll */
		CTOP_GFX_CTOP_GFX_R00_M17_A0	ctop_gfx_r00;
		CTOP_GFX_CTOP_GFX_R01_M17_A0	ctop_gfx_r01;

		*(u32*)(&ctop_gfx_r00) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(0));
		*(u32*)(&ctop_gfx_r01) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(1));

		M = ctop_gfx_r00.m1pll_m;
		NPC = ctop_gfx_r01.m1pll_npc;
		NSC = ctop_gfx_r01.m1pll_nsc;
		out_div = ctop_gfx_r01.m1pll_fout_od;

		if(!M) M = 1;

		clk.m1_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_CMN) >> out_div;
		clk.m1_pll_ss = ctop_gfx_r00.m1pll_dss ? 0 : 1;

		DEBUG("m1 pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("m1 pll out : %u\n", clk.m1_pll_out);
		DEBUG("m1 pll ss : %s\n", clk.m1_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_gfx_r00.m1pll_accuracy;
		UPDN_MAX = ctop_gfx_r00.m1pll_updn_max;
		MOD_FREQ = ctop_gfx_r00.m1pll_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.m1_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.m1_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("m1 accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read core(m2) pll */
		CTOP_GFX_CTOP_GFX_R03_M17_A0	ctop_gfx_r03;
		CTOP_GFX_CTOP_GFX_R04_M17_A0	ctop_gfx_r04;

		*(u32*)(&ctop_gfx_r03) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(3));
		*(u32*)(&ctop_gfx_r04) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(4));

		M = ctop_gfx_r03.m2pll_m;
		NPC = ctop_gfx_r04.m2pll_npc;
		NSC = ctop_gfx_r04.m2pll_nsc;
		out_div = ctop_gfx_r04.m2pll_fout_od;

		if(!M) M = 1;

		clk.core_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_CMN) >> out_div;
		clk.core_pll_ss = ctop_gfx_r03.m2pll_dss ? 0 : 1;

		DEBUG("core pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("core pll out : %u\n", clk.core_pll_out);
		DEBUG("core pll ss : %s\n", clk.core_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_gfx_r03.m2pll_accuracy;
		UPDN_MAX = ctop_gfx_r03.m2pll_updn_max;
		MOD_FREQ = ctop_gfx_r03.m2pll_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.core_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.core_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("core accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read codec pll */
		CTOP_GFX_CTOP_GFX_R06_M17_A0	ctop_gfx_r06;
		CTOP_GFX_CTOP_GFX_R07_M17_A0	ctop_gfx_r07;

		*(u32*)(&ctop_gfx_r06) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(6));
		*(u32*)(&ctop_gfx_r07) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(7));

		M = ctop_gfx_r06.codecpll_m;
		NPC = ctop_gfx_r07.codecpll_npc;
		NSC = ctop_gfx_r07.codecpll_nsc;
		out_div = ctop_gfx_r07.codecpll_fout_od;

		if(!M) M = 1;

		clk.codec_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_CMN) >> out_div;
		clk.codec_pll_ss = ctop_gfx_r06.codecpll_dss ? 0 : 1;

		DEBUG("codec pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("codec pll out : %u\n", clk.codec_pll_out);
		DEBUG("codec pll ss : %s\n", clk.codec_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_gfx_r06.codecpll_accuracy;
		UPDN_MAX = ctop_gfx_r06.codecpll_updn_max;
		MOD_FREQ = ctop_gfx_r06.codecpll_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.codec_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.codec_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("codec accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read gpu pll */
		CTOP_FMC_CTOP_FMC_R08_M17_A0	ctop_fmc_r08;
		CTOP_FMC_CTOP_FMC_R09_M17_A0	ctop_fmc_r09;

		*(u32*)(&ctop_fmc_r08) = CTOP_CTRL_M17A0_READ(FMC, REG_OFFSET(8));
		*(u32*)(&ctop_fmc_r09) = CTOP_CTRL_M17A0_READ(FMC, REG_OFFSET(9));

		M = ctop_fmc_r08.gpupll_m;
		NPC = ctop_fmc_r09.gpupll_npc;
		NSC = ctop_fmc_r09.gpupll_nsc;
		out_div = ctop_fmc_r09.gpupll_fout_od;

		if(!M) M = 1;

		clk.gpu_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_CMN) >> out_div;
		clk.gpu_pll_ss = ctop_fmc_r08.gpupll_dss ? 0 : 1;

		DEBUG("gpu pll m : %u, npc : %u, nsc : %u, out_div : %u\n", M, NPC, NSC, out_div);
		DEBUG("gpu pll out : %u\n", clk.gpu_pll_out);
		DEBUG("gpu pll ss : %s\n", clk.gpu_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_fmc_r08.gpupll_accuracy;
		UPDN_MAX = ctop_fmc_r08.gpupll_updn_max;
		MOD_FREQ = ctop_fmc_r08.gpupll_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.gpu_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.gpu_mod_freq = MOD_FREQ_OUT(FIN_CMN, M, MOD_FREQ, UPDN_MAX);
		DEBUG("gpu accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	{
		/* read disp pll */
		CTOP_DPE_CTOP_DPE_R28_M17_A0	ctop_dpe_r28;
		CTOP_DPE_CTOP_DPE_R29_M17_A0	ctop_dpe_r29;

		*(u32*)(&ctop_dpe_r28) = CTOP_CTRL_M17A0_READ(DPE, REG_OFFSET(28));
		*(u32*)(&ctop_dpe_r29) = CTOP_CTRL_M17A0_READ(DPE, REG_OFFSET(29));

		M = ctop_dpe_r28.displl_m;
		NPC = ctop_dpe_r29.displl_npc;
		NSC = ctop_dpe_r29.displl_nsc;
		out_div = ctop_dpe_r29.displl_fout2_od;
		pre_div = ctop_dpe_r29.displl_pre_fout2_div;

		if(!M) M = 1;

		clk.disp_pll_out = PLL_CLK_OUT(M, NPC, NSC, FIN_DISP) >> out_div;
		clk.disp_pll_ss = ctop_dpe_r28.displl_dss ? 0 : 1;

		switch(pre_div)
		{
			case 0:
				pre_div = 2;
				break;
			case 1:
				pre_div = 3;
				break;
			case 2:
				pre_div = 4;
				break;
			case 3:
				pre_div = 5;
				break;
			default:
				pre_div = 1;
				break;
		}
		clk.disp_pll_out = clk.disp_pll_out / pre_div;

		DEBUG("disp pll m : %u, npc : %u, nsc : %u, out_div : %u, pre_div : %u\n"
				, M, NPC, NSC, out_div, pre_div);
		DEBUG("disp pll out : %u\n", clk.disp_pll_out);
		DEBUG("disp pll ss : %s\n", clk.disp_pll_ss ? "ON" : "OFF");

		ACCURACY = ctop_dpe_r28.displl_accuracy;
		UPDN_MAX = ctop_dpe_r28.displl_updn_max;
		MOD_FREQ = ctop_dpe_r28.displl_mod_freq;
		RESULT_RF = GET_RESULT_RF(ACCURACY);

		clk.disp_spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
		clk.disp_mod_freq = MOD_FREQ_OUT(FIN_DISP, M, MOD_FREQ, UPDN_MAX);
		DEBUG("disp accracy : %u, updn_max : %u, mod_freq : %u , result_rt : %u\n", ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
		DEBUG("\n");
	}

	/* cpu clock */
	clk.cpu_core_clk = clk.cpu_pll_out >> 1;

	/* pll mux */
	CTOP_GFX_CTOP_GFX_R10_M17_A0	ctop_gfx_r10;
	*(u32*)(&ctop_gfx_r10) = CTOP_CTRL_M17A0_READ(GFX, REG_OFFSET(10));

	/* lm clk */
	if(!ctop_gfx_r10.ck_mux_pll_sel_m0)//m0 pll -> m0 ddr(lm)
		clk.lm_ddr_clk = clk.m0_pll_out >> 1;
	else//m1 pll -> m0 ddr(gm)
		clk.lm_ddr_clk = clk.m1_pll_out >> 1;

	/* gm clk */
	if(!ctop_gfx_r10.ck_mux_pll_sel_m1)//m0 pll -> m1 ddr(lm)
		clk.gm_ddr_clk = clk.m0_pll_out >> 1;
	else//m1 pll -> m1 ddr(gm)
		clk.gm_ddr_clk = clk.m1_pll_out >> 1;

	/* peri clk */
	if(ctop_gfx_r10.ck_mux_pll_sel_core == 0)
		clk.peri_bus_clk = clk.core_pll_out >> 2;
	else if(ctop_gfx_r10.ck_mux_pll_sel_core == 1)
		clk.peri_bus_clk = clk.codec_pll_out / 6;
	else if(ctop_gfx_r10.ck_mux_pll_sel_core == 2)
		clk.peri_bus_clk = clk.m1_pll_out >> 2;

	clk.peri_bus_clk = clk.peri_bus_clk >> 1;//peri_bus_clk = core clk/2

	/* gpu clk */
	if(lx_chip_rev() >= LX_CHIP_REV(M17, C0)) {
		// M16++ LG1313C0
		CTOP_DPE_CTOP_DPE_R33_M17_A0	ctop_dpe_r33;
		*(u32*)(&ctop_dpe_r33) = CTOP_CTRL_M17A0_READ(DPE, REG_OFFSET(33));

		if(!ctop_dpe_r33.gpu_clk_sel)//use gpu pll
			clk.gpu_clk = clk.gpu_pll_out;
		else
		{
			if(!ctop_gfx_r10.pll_sel_gpu_ddr)
				clk.gpu_clk = clk.m0_pll_out >> 2;
			else
				clk.gpu_clk = clk.m1_pll_out >> 2;
		}
	}
	else {
		clk.gpu_clk = clk.gpu_pll_out;
	}

	/* MHz */
	clk_param->cpu_clk = clk.cpu_core_clk/MHZ;
	clk_param->peri_clk = clk.peri_bus_clk/MHZ;
	clk_param->gpu_clk = clk.gpu_clk/MHZ;
	clk_param->ddr_clk[0] = clk.lm_ddr_clk/MHZ;
	clk_param->ddr_clk[1] = clk.gm_ddr_clk/MHZ;
	clk_param->ss = clk.m0_pll_ss | clk.m1_pll_ss;

	/* print PLL OUT, SS, CLK SRC */
	if(m)
	{
		seq_printf(m, "\n============= PLL OUT ============\n");
		seq_printf(m, "cpu pll out      : %10u\n", clk.cpu_pll_out);
		seq_printf(m, "m0 pll out       : %10u\n", clk.m0_pll_out);
		seq_printf(m, "m1 pll out       : %10u\n", clk.m1_pll_out);
		seq_printf(m, "core(m2) pll out : %10u\n", clk.core_pll_out);
		seq_printf(m, "codec pll out    : %10u\n", clk.codec_pll_out);
		seq_printf(m, "gpu pll out      : %10u\n", clk.gpu_pll_out);
		seq_printf(m, "disp pll out     : %10u\n", clk.disp_pll_out);
		seq_printf(m, "\n============= SS ============\n");
		seq_printf(m, "cpu pll ss      : %s\n", clk.cpu_pll_ss ? "ON" : "OFF");
		seq_printf(m, "m0 pll ss       : %s\n", clk.m0_pll_ss ? "ON" : "OFF");
		seq_printf(m, "m1 pll ss       : %s\n", clk.m1_pll_ss ? "ON" : "OFF");
		seq_printf(m, "core(m2) pll ss : %s\n", clk.core_pll_ss ? "ON" : "OFF");
		seq_printf(m, "codec pll ss    : %s\n", clk.codec_pll_ss ? "ON" : "OFF");
		seq_printf(m, "gpu pll ss      : %s\n", clk.gpu_pll_ss ? "ON" : "OFF");
		seq_printf(m, "disp pll ss     : %s\n", clk.disp_pll_ss ? "ON" : "OFF");
		seq_printf(m, "\n============= CLK SRC ============\n");
		seq_printf(m, "LM CLK SRC   : %s\n", !ctop_gfx_r10.ck_mux_pll_sel_m0 ? "M0 PLL" : "M1 PLL");
		seq_printf(m, "GM CLK SRC   : %s\n", !ctop_gfx_r10.ck_mux_pll_sel_m1 ? "M0 PLL" : "M1 PLL");
		seq_printf(m, "PERI CLK SRC : %s\n", !ctop_gfx_r10.ck_mux_pll_sel_core ? "CORE PLL" :
					ctop_gfx_r10.ck_mux_pll_sel_core==1 ? "CODEC PLL" : "M1 PLL");

		seq_printf(m, "\n============ SPREAD RATIO =============\n");
		if(clk.cpu_pll_ss)
			seq_printf(m, "cpu spread_ratio   : %u.%4u, mod_freq : %uHz\n",
						clk.cpu_spread_ratio/10000, clk.cpu_spread_ratio%10000, clk.cpu_mod_freq);
		if(clk.m0_pll_ss)
			seq_printf(m, "m0 spread_ratio    : %u.%4u, mod_freq : %uHz\n",
						clk.m0_spread_ratio/10000, clk.m0_spread_ratio%10000, clk.m0_mod_freq);
		if(clk.m1_pll_ss)
			seq_printf(m, "m1 spread_ratio    : %u.%4u, mod_freq : %uHz\n",
						clk.m1_spread_ratio/10000, clk.m1_spread_ratio%10000, clk.m1_mod_freq);
		if(clk.core_pll_ss)
			seq_printf(m, "core spread_ratio  : %u.%4u, mod_freq : %uHz\n",
						clk.core_spread_ratio/10000, clk.core_spread_ratio%10000, clk.core_mod_freq);
		if(clk.codec_pll_ss)
			seq_printf(m, "codec spread_ratio : %u.%4u, mod_freq : %uHz\n",
					clk.codec_spread_ratio/10000, clk.codec_spread_ratio%10000, clk.codec_mod_freq);
		if(clk.gpu_pll_ss)
			seq_printf(m, "gpu spread_ratio   : %u.%4u, mod_freq : %uHz\n",
						clk.gpu_spread_ratio/10000, clk.gpu_spread_ratio%10000, clk.gpu_mod_freq);
		if(clk.disp_pll_ss)
			seq_printf(m, "disp spread_ratio  : %u.%4u, mod_freq : %uHz\n",
						clk.disp_spread_ratio/10000, clk.disp_spread_ratio%10000, clk.disp_mod_freq);
		seq_printf(m, "\n");
	}
}
#endif //#ifdef INCLUDE_M17_CHIP_KDRV

#ifdef INCLUDE_M19_CHIP_KDRV
static void _m19_get_clk_info(SYS_SOC_CLK_T *clk_param, struct seq_file *m)
{
	return;
}
#endif //#ifdef INCLUDE_M19_CHIP_KDRV

/* scan(detect) clock related information.
 * this function's main role is to return the brief SYS_SOC_CLK_T information.
 * if caller wants to print more detail information, pass the seq_file object.
 *
 */
void    SYS_IO_ScanClock( SYS_SOC_CLK_T* clk, void* seq_file_obj)
{
	switch(lx_chip())
	{
#ifdef INCLUDE_M17_CHIP_KDRV
		case LX_CHIP_M17:
		{
			struct seq_file* m = (struct seq_file*)seq_file_obj;
			_m17_get_clk_info(clk, m);
		}
		break;
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
		case LX_CHIP_M19:
		{
			struct seq_file* m = (struct seq_file*)seq_file_obj;
			_m19_get_clk_info(clk, m);
		}
		break;
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
		case LX_CHIP_O18:
		{
			struct seq_file* m = (struct seq_file*)seq_file_obj;
			_o18_get_clk_info(clk, m);
		}
		break;
#endif
		default:
		{
			/* do nothing. not supported */
		}
		break;
	}
}

int SYS_IO_RunTimeSuspend(struct device* dev)
{
	return RET_OK;
}

int SYS_IO_RunTimeResume(struct device* dev)
{
	return RET_OK;
}

/** @} */

