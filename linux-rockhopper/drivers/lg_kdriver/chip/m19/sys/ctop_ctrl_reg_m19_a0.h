#ifndef __CTOP_CTRL_REG_M19_A0_H__
#define __CTOP_CTRL_REG_M19_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "m19a0/ctop_fme0_m19a0_reg.h"
#include "m19a0/ctop_gbm_m19a0_reg.h"
#include "m19a0/ctop_aud_m19a0_reg.h"
#include "m19a0/ctop_edid_m19a0_reg.h"
#include "m19a0/ctop_bmc_m19a0_reg.h"
#include "m19a0/ctop_gfx_m19a0_reg.h"
#include "m19a0/ctop_fms_m19a0_reg.h"
#include "m19a0/ctop_dpe_m19a0_reg.h"
#include "m19a0/ctop_nd0_m19a0_reg.h"
#include "m19a0/ctop_imx_m19a0_reg.h"
#include "m19a0/gfx_syn_m19a0_reg.h"
#include "m19a0/m1_syn_m19a0_reg.h"
#include "m19a0/fms_syn_m19a0_reg.h"
#include "m19a0/mip_syn_m19a0_reg.h"
#include "m19a0/peri_syn_m19a0_reg.h"
#include "m19a0/aud_syn_m19a0_reg.h"
#include "m19a0/vdec0_syn_m19a0_reg.h"
#include "m19a0/tiv_syn_m19a0_reg.h"
#include "m19a0/dpe_syn_m19a0_reg.h"
#include "m19a0/nd1_syn_m19a0_reg.h"
#include "m19a0/emmc_syn_m19a0_reg.h"
#include "m19a0/nd0_syn_m19a0_reg.h"
#include "m19a0/fmc_syn_m19a0_reg.h"
#include "m19a0/fme0_syn_m19a0_reg.h"
#include "m19a0/gpu_syn_m19a0_reg.h"
#include "m19a0/cvi_syn_m19a0_reg.h"
#include "m19a0/gem_syn_m19a0_reg.h"
#include "m19a0/cco_syn_m19a0_reg.h"
#include "m19a0/m0_syn_m19a0_reg.h"
#include "m19a0/gsc_syn_m19a0_reg.h"
#include "m19a0/lbm_syn_m19a0_reg.h"
#include "m19a0/edid_syn_m19a0_reg.h"
#include "m19a0/gbm_syn_m19a0_reg.h"
#include "m19a0/imx_syn_m19a0_reg.h"
#include "m19a0/vdec1_syn_m19a0_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct {
/* CTOP */
	CTOP_FME0_REG_M19A0_T        * CTOP_FME0;
	CTOP_GBM_REG_M19A0_T         * CTOP_GBM;
	CTOP_CTRL_AUD_REG_M19A0_T    * CTOP_AUD;
	CTOP_EDID_REG_M19A0_T        * CTOP_EDID;
	CTOP_CTRL_BMC_REG_M19A0_T    * CTOP_BMC;
	CTOP_CTRL_GFX_REG_M19A0_T    * CTOP_GFX;
	CTOP_CTRL_FMS_REG_M19A0_T    * CTOP_FMS;
	CTOP_CTRL_DPE_REG_M19A0_T    * CTOP_DPE;
	CTOP_CTRL_ND0_REG_M19A0_T    * CTOP_ND0;
	CTOP_CTRL_IMX_REG_M19A0_T    * CTOP_IMX;

/* CTOP_SYN */
	VDEC1_SYN_REG_M19A0_T * VDEC1_SYN;
	VDEC0_SYN_REG_M19A0_T * VDEC0_SYN;
	AUD_SYN_REG_M19A0_T   * AUD_SYN;
	M1_SYN_REG_M19A0_T    * M1_SYN;
	M0_SYN_REG_M19A0_T    * M0_SYN;
	GFX_SYN_REG_M19A0_T   * GFX_SYN;
/* NOTE:
	A member name is 'BMC_SYN', because this is in 'BMC_SYN' sheet in manual.
    But, the catagory name is 'mip_syn' in 'BMC_SYN' sheet.
    So, the header file name is from 'mip_syn'.
*/
	MIP_SYN_REG_M19A0_T   * BMC_SYN;
	FMS_SYN_REG_M19A0_T   * FMS_SYN;
	DPE_SYN_REG_M19A0_T   * DPE_SYN;
	FMC_SYN_REG_M19A0_T   * FMC_SYN;
	CCO_SYN_REG_M19A0_T   * CCO_SYN;
	GSC_SYN_REG_M19A0_T   * GSC_SYN;
	FME0_SYN_REG_M19A0_T  * FME0_SYN;
	ND1_SYN_REG_M19A0_T   * ND1_SYN;
	ND0_SYN_REG_M19A0_T   * ND0_SYN;
	IMX_SYN_REG_M19A0_T   * IMX_SYN;
	CVI_SYN_REG_M19A0_T   * CVI_SYN;
	GBM_SYN_REG_M19A0_T   * GBM_SYN;
	LBM_SYN_REG_M19A0_T   * LBM_SYN;
	PERI_SYN_REG_M19A0_T  * PERI_SYN;
	GPU_SYN_REG_M19A0_T   * GPU_SYN;
	EDID_SYN_REG_M19A0_T  * EDID_SYN;
	EMMC_SYN_REG_M19A0_T  * EMMC_SYN;
	GEM_SYN_REG_M19A0_T   * GEM_SYN;
/* NOTE:
	A member name is 'TI_SYN', because this is in 'TI_SYN' sheet in manual.
	But, the catagory name is 'tiv_syn' in 'TI_SYN' sheet.
*/
	TIV_SYN_REG_M19A0_T   * TI_SYN;
} CTOP_REG_M19A0_T;



/* CTOP SYN */
#define M19_A0_VDEC1_SYN_BASE     0xC9C71200            // 0xC9C7_1200
#define M19_A0_VDEC1_SYN_TYPE     VDEC1_SYN_REG_M19A0_T

#define M19_A0_VDEC0_SYN_BASE     0xC9C70200            // 0xC9C7_0200
#define M19_A0_VDEC0_SYN_TYPE     VDEC0_SYN_REG_M19A0_T

#define M19_A0_AUD_SYN_BASE       0xC9C60000            // 0xC9C6_0000
#define M19_A0_AUD_SYN_TYPE       AUD_SYN_REG_M19A0_T

#define M19_A0_M1_SYN_BASE        0xC9C40000            // 0xC9C4_0000
#define M19_A0_M1_SYN_TYPE        M1_SYN_REG_M19A0_T

#define M19_A0_M0_SYN_BASE        0xC9C30000            // 0xC9C3_0000
#define M19_A0_M0_SYN_TYPE        M0_SYN_REG_M19A0_T

#define M19_A0_GFX_SYN_BASE       0xC9C10000            // 0xC9C1_0000
#define M19_A0_GFX_SYN_TYPE       GFX_SYN_REG_M19A0_T

#define M19_A0_BMC_SYN_BASE       0xC930E000            // 0xC930_E000
#define M19_A0_BMC_SYN_TYPE       MIP_SYN_REG_M19A0_T

#define M19_A0_FMS_SYN_BASE       0xC930C000            // 0xC930_C000
#define M19_A0_FMS_SYN_TYPE       FMS_SYN_REG_M19A0_T

#define M19_A0_DPE_SYN_BASE       0xC930A800            // 0xC930_A800
#define M19_A0_DPE_SYN_TYPE       DPE_SYN_REG_M19A0_T

#define M19_A0_FMC_SYN_BASE       0xC9309000            // 0xC930_9000
#define M19_A0_FMC_SYN_TYPE       FMC_SYN_REG_M19A0_T

/*#>10*/
#define M19_A0_CCO_SYN_BASE       0xC9308000            // 0xC930_8000
#define M19_A0_CCO_SYN_TYPE       CCO_SYN_REG_M19A0_T

#define M19_A0_GSC_SYN_BASE       0xC9307000            // 0xC930_7000
#define M19_A0_GSC_SYN_TYPE       GSC_SYN_REG_M19A0_T

#define M19_A0_FME0_SYN_BASE      0xC9306000            // 0xC930_6000
#define M19_A0_FME0_SYN_TYPE      FME0_SYN_REG_M19A0_T

#define M19_A0_ND1_SYN_BASE       0xC9305000            // 0xC930_5000
#define M19_A0_ND1_SYN_TYPE       ND1_SYN_REG_M19A0_T

#define M19_A0_ND0_SYN_BASE       0xC9304000            // 0xC930_4000
#define M19_A0_ND0_SYN_TYPE       ND0_SYN_REG_M19A0_T

#define M19_A0_IMX_SYN_BASE       0xC9303000            // 0xC930_3000
#define M19_A0_IMX_SYN_TYPE       IMX_SYN_REG_M19A0_T

#define M19_A0_CVI_SYN_BASE       0xC9302000            // 0xC930_2000
#define M19_A0_CVI_SYN_TYPE       CVI_SYN_REG_M19A0_T

#define M19_A0_GBM_SYN_BASE       0xC9301000            // 0xC930_1000
#define M19_A0_GBM_SYN_TYPE       GBM_SYN_REG_M19A0_T

#define M19_A0_LBM_SYN_BASE       0xC9300000            // 0xC930_0000
#define M19_A0_LBM_SYN_TYPE       LBM_SYN_REG_M19A0_T

#define M19_A0_PERI_SYN_BASE      0xC9230000            // 0xC923_0000
#define M19_A0_PERI_SYN_TYPE      PERI_SYN_REG_M19A0_T

/*#>20*/
#define M19_A0_GPU_SYN_BASE       0xC9205000            // 0xC920_5000
#define M19_A0_GPU_SYN_TYPE       GPU_SYN_REG_M19A0_T

#define M19_A0_EDID_SYN_BASE      0xC36C1050            // 0xC36C_1050
#define M19_A0_EDID_SYN_TYPE      EDID_SYN_REG_M19A0_T

#define M19_A0_EMMC_SYN_BASE      0xC3681000            // 0xC368_1000
#define M19_A0_EMMC_SYN_TYPE      EMMC_SYN_REG_M19A0_T

#define M19_A0_GEM_SYN_BASE       0xC3501000            // 0xC350_1000
#define M19_A0_GEM_SYN_TYPE       GEM_SYN_REG_M19A0_T

#define M19_A0_TI_SYN_BASE        0xC9C60400            // 0xC9C6_0400
#define M19_A0_TI_SYN_TYPE        TIV_SYN_REG_M19A0_T


/* CTOP */
#define M19_A0_CTOP_FME0_BASE    0xC9306800            // 0xC930_6800
#define M19_A0_CTOP_FME0_TYPE    CTOP_FME0_REG_M19A0_T

#define M19_A0_CTOP_GBM_BASE     0xC9301C00            // 0xC930_1C00
#define M19_A0_CTOP_GBM_TYPE     CTOP_GBM_REG_M19A0_T

#define M19_A0_CTOP_AUD_BASE     0xC9C60600            // 0xC9C6_0600
#define M19_A0_CTOP_AUD_TYPE     CTOP_CTRL_AUD_REG_M19A0_T

#define M19_A0_CTOP_EDID_BASE    0xC36C8000            // 0xC36C_8000
#define M19_A0_CTOP_EDID_TYPE    CTOP_EDID_REG_M19A0_T

#define M19_A0_CTOP_BMC_BASE     0xC930E400            // 0xC930_E400
#define M19_A0_CTOP_BMC_TYPE     CTOP_CTRL_BMC_REG_M19A0_T

#define M19_A0_CTOP_GFX_BASE     0xC9C10400            // 0xC9C1_0400
#define M19_A0_CTOP_GFX_TYPE     CTOP_CTRL_GFX_REG_M19A0_T

#define M19_A0_CTOP_FMS_BASE     0xC930C400            // 0xC930_C400
#define M19_A0_CTOP_FMS_TYPE     CTOP_CTRL_FMS_REG_M19A0_T

#define M19_A0_CTOP_DPE_BASE     0xC930A000            // 0xC930_A000
#define M19_A0_CTOP_DPE_TYPE     CTOP_CTRL_DPE_REG_M19A0_T

#define M19_A0_CTOP_ND0_BASE     0xC9304C00            // 0xC930_4C00
#define M19_A0_CTOP_ND0_TYPE     CTOP_CTRL_ND0_REG_M19A0_T

#define M19_A0_CTOP_IMX_BASE     0xC9303C00            // 0xC930_3C00
#define M19_A0_CTOP_IMX_TYPE     CTOP_CTRL_IMX_REG_M19A0_T

#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_M19_A0_H__ */

