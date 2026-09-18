#ifndef __CTOP_CTRL_REG_M17_A0_H__
#define __CTOP_CTRL_REG_M17_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#include "m17a0/ctop_fme0_m17a0_reg.h"
#include "m17a0/gfx_syn_m17a0_reg.h"
#include "m17a0/m1_syn_m17a0_reg.h"
#include "m17a0/fms_syn_m17a0_reg.h"
#include "m17a0/mip_syn_m17a0_reg.h"
#include "m17a0/peri_syn_m17a0_reg.h"
#include "m17a0/sre_syn_m17a0_reg.h"
#include "m17a0/ctop_dpe_m17a0_reg.h"
#include "m17a0/aud_syn_m17a0_reg.h"
#include "m17a0/vdec0_syn_m17a0_reg.h"
#include "m17a0/tiv_syn_m17a0_reg.h"
#include "m17a0/dpe_syn_m17a0_reg.h"
#include "m17a0/ctop_fms_m17a0_reg.h"
#include "m17a0/ctop_sr_m17a0_reg.h"
#include "m17a0/emmc_syn_m17a0_reg.h"
#include "m17a0/nd0_syn_m17a0_reg.h"
#include "m17a0/fmc_syn_m17a0_reg.h"
#include "m17a0/fme0_syn_m17a0_reg.h"
#include "m17a0/ctop_fmc_m17a0_reg.h"
#include "m17a0/gpu_syn_m17a0_reg.h"
#include "m17a0/cvi_syn_m17a0_reg.h"
#include "m17a0/gem_syn_m17a0_reg.h"
#include "m17a0/cco_syn_m17a0_reg.h"
#include "m17a0/m0_syn_m17a0_reg.h"
#include "m17a0/lbm_syn_m17a0_reg.h"
#include "m17a0/ctop_gfx_m17a0_reg.h"
#include "m17a0/imx_syn_m17a0_reg.h"
#include "m17a0/vdec1_syn_m17a0_reg.h"
#include "m17a0/gbus_syn_m17a0_reg.h"
#include "m17a0/vsd_syn_m17a0_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct {
	CTOP_DPE_REG_M17_A0    * DPE;
	CTOP_FMC_REG_M17_A0    * FMC;
	CTOP_FME0_REG_M17_A0   * FME0;
	CTOP_FMS_REG_M17_A0    * FMS;
	CTOP_GFX_REG_M17_A0    * GFX;
	CTOP_SR_REG_M17_A0     * SR;
	AUD_SYN_REG_M17_A0     * AUD_SYN;
	CCO_SYN_REG_M17_A0     * CCO_SYN;
	CVI_SYN_REG_M17_A0     * CVI_SYN;
	DPE_SYN_REG_M17_A0     * DPE_SYN;
	EMMC_SYN_REG_M17_A0    * EMMC_SYN;
	FMC_SYN_REG_M17_A0     * FMC_SYN;
	FME0_SYN_REG_M17_A0    * FME0_SYN;
	FMS_SYN_REG_M17_A0     * FMS_SYN;
	GBUS_SYN_REG_M17_A0    * GBUS_SYN;
	GEM_SYN_REG_M17_A0     * GEM_SYN;
	GFX_SYN_REG_M17_A0     * GFX_SYN;
	GPU_SYN_REG_M17_A0     * GPU_SYN;
	IMX_SYN_REG_M17_A0     * IMX_SYN;
	LBM_SYN_REG_M17_A0     * LBM_SYN;
	M0_SYN_REG_M17_A0      * M0_SYN;
	M1_SYN_REG_M17_A0      * M1_SYN;
	MIP_SYN_REG_M17_A0     * MIP_SYN;
	ND0_SYN_REG_M17_A0		* ND0_SYN;
	PERI_SYN_REG_M17_A0    * PERI_SYN;
	SRE_SYN_REG_M17_A0     * SRE_SYN;
	TIV_SYN_REG_M17_A0     * TIV_SYN;
	VDEC0_SYN_REG_M17_A0   * VDEC0_SYN;
	VDEC1_SYN_REG_M17_A0   * VDEC1_SYN;
	VSD_SYN_REG_M17_A0     * VSD_SYN;
} CTOP_REG_M17A0_T;

//CTOP
#define M17_A0_CTOP_DPE_BASE	0xC930A400			//0xC930_A400
#define M17_A0_CTOP_DPE_TYPE	CTOP_DPE_REG_M17_A0

#define M17_A0_CTOP_FMC_BASE	0xC9309400			//0xC930_9400
#define M17_A0_CTOP_FMC_TYPE	CTOP_FMC_REG_M17_A0

#define M17_A0_CTOP_FME0_BASE	0xC9308800			//0xC930_8800
#define M17_A0_CTOP_FME0_TYPE	CTOP_FME0_REG_M17_A0

#define M17_A0_CTOP_FMS_BASE	0xC930C400			//0xC930_C400
#define M17_A0_CTOP_FMS_TYPE	CTOP_FMS_REG_M17_A0

#define M17_A0_CTOP_GFX_BASE	0xC9C10400			//0xC9C1_0400
#define M17_A0_CTOP_GFX_TYPE	CTOP_GFX_REG_M17_A0

#define M17_A0_CTOP_SR_BASE	0xC9305400			//0xC930_5400
#define M17_A0_CTOP_SR_TYPE	CTOP_SR_REG_M17_A0

//CTOP SYNC
#define M17_A0_CTOP_AUD_SYN_BASE	0xC9C60000		//0xC9C6_0000
#define M17_A0_CTOP_AUD_SYN_TYPE	AUD_SYN_REG_M17_A0

#define M17_A0_CTOP_CCO_SYN_BASE	0xC9307000		//0xC930_7000
#define M17_A0_CTOP_CCO_SYN_TYPE	CCO_SYN_REG_M17_A0

#define M17_A0_CTOP_CVI_SYN_BASE	0xC9302000		//0xC930_2000
#define M17_A0_CTOP_CVI_SYN_TYPE	CVI_SYN_REG_M17_A0

#define M17_A0_CTOP_DPE_SYN_BASE	0xC930A000		//0xC930_A000
#define M17_A0_CTOP_DPE_SYN_TYPE	DPE_SYN_REG_M17_A0

#define M17_A0_CTOP_EMMC_SYN_BASE	0xC3680000		//0xC368_0000
#define M17_A0_CTOP_EMMC_SYN_TYPE	EMMC_SYN_REG_M17_A0

#define M17_A0_CTOP_FMC_SYN_BASE	0xC9309000		//0xC930_9000
#define M17_A0_CTOP_FMC_SYN_TYPE	FMC_SYN_REG_M17_A0

#define M17_A0_CTOP_FME0_SYN_BASE	0xC9308000		//0xC930_8000
#define M17_A0_CTOP_FME0_SYN_TYPE	FME0_SYN_REG_M17_A0

#define M17_A0_CTOP_FMS_SYN_BASE	0xC930C000		//0xC930_C000
#define M17_A0_CTOP_FMS_SYN_TYPE	FMS_SYN_REG_M17_A0

#define M17_A0_CTOP_GBUS_SYN_BASE	0xC9301000		//0xC930_1000
#define M17_A0_CTOP_GBUS_SYN_TYPE	GBUS_SYN_REG_M17_A0

#define M17_A0_CTOP_GEM_SYN_BASE	0xC3501000		//0xC350_1000
#define M17_A0_CTOP_GEM_SYN_TYPE	GEM_SYN_REG_M17_A0

#define M17_A0_CTOP_GFX_SYN_BASE	0xC9C10000		//0xC9C1_0000
#define M17_A0_CTOP_GFX_SYN_TYPE	GFX_SYN_REG_M17_A0

#define M17_A0_CTOP_GPU_SYN_BASE	0xC9205000		//0xC920_5000
#define M17_A0_CTOP_GPU_SYN_TYPE	GPU_SYN_REG_M17_A0

#define M17_A0_CTOP_IMX_SYN_BASE	0xC9303000		//0xC930_3000
#define M17_A0_CTOP_IMX_SYN_TYPE	IMX_SYN_REG_M17_A0

#define M17_A0_CTOP_LBM_SYN_BASE	0xC9300000		//0xC930_0000
#define M17_A0_CTOP_LBM_SYN_TYPE	LBM_SYN_REG_M17_A0

#define M17_A0_CTOP_M0_SYN_BASE		0xC9C30000		//0xC9C3_0000
#define M17_A0_CTOP_M0_SYN_TYPE		M0_SYN_REG_M17_A0

#define M17_A0_CTOP_M1_SYN_BASE		0xC9C40000		//0xC9C4_0000
#define M17_A0_CTOP_M1_SYN_TYPE		M1_SYN_REG_M17_A0

#define M17_A0_CTOP_MIP_SYN_BASE	0xC930E000		//0xC930_E000
#define M17_A0_CTOP_MIP_SYN_TYPE	MIP_SYN_REG_M17_A0

#define M17_A0_CTOP_ND0_SYN_BASE	0xC9304000		//0xC930_4000
#define M17_A0_CTOP_ND0_SYN_TYPE	ND0_SYN_REG_M17_A0

#define M17_A0_CTOP_PERI_SYN_BASE	0xC9230000		//0xC923_0000
#define M17_A0_CTOP_PERI_SYN_TYPE	PERI_SYN_REG_M17_A0

#define M17_A0_CTOP_SRE_SYN_BASE	0xC9305000		//0xC930_5000
#define M17_A0_CTOP_SRE_SYN_TYPE	SRE_SYN_REG_M17_A0

#define M17_A0_CTOP_TIV_SYN_BASE	0xC9C50000		//0xC9C5_0000
#define M17_A0_CTOP_TIV_SYN_TYPE	TIV_SYN_REG_M17_A0

#define M17_A0_CTOP_VDEC0_SYN_BASE	0xC9C701C0		//0xC9C7_01C0
#define M17_A0_CTOP_VDEC0_SYN_TYPE	VDEC0_SYN_REG_M17_A0

#define M17_A0_CTOP_VDEC1_SYN_BASE	0xC9C711C0		//0xC9C7_11C0
#define M17_A0_CTOP_VDEC1_SYN_TYPE	VDEC1_SYN_REG_M17_A0

#define M17_A0_CTOP_VSD_SYN_BASE	0xC9306000		//0xC930_6000
#define M17_A0_CTOP_VSD_SYN_TYPE	VSD_SYN_REG_M17_A0


#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_M17_A0_H__ */

