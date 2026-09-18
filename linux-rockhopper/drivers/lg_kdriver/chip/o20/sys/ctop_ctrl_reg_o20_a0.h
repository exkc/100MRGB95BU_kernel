#ifndef __CTOP_CTRL_REG_O20_A0_H__
#define __CTOP_CTRL_REG_O20_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "o20a0/ctop_ctrl_atg_o20a0_reg.h"
#include "o20a0/ctop_ctrl_bmc_o20a0_reg.h"
#include "o20a0/ctop_ctrl_dpe_o20a0_reg.h"
#include "o20a0/ctop_ctrl_fme1_o20a0_reg.h"
#include "o20a0/ctop_ctrl_fms_o20a0_reg.h"
#include "o20a0/ctop_ctrl_lbms_o20a0_reg.h"
#include "o20a0/ctop_ctrl_nd0_o20a0_reg.h"
#include "o20a0/ctop_ctrl_nd1_o20a0_reg.h"
#include "o20a0/ctop_ctrl_por_o20a0_reg.h"
#include "o20a0/ctop_ctrl_vd1_o20a0_reg.h"
#include "o20a0/ctop_ctrl_wov_o20a0_reg.h"

#include "o20a0/atg_syn_o20a0_reg.h"
#include "o20a0/bmc_syn_o20a0_reg.h"
#include "o20a0/cco_syn_o20a0_reg.h"
#include "o20a0/cpu_syn_o20a0_reg.h"
#include "o20a0/cvi_syn_o20a0_reg.h"
#include "o20a0/gsc_syn_o20a0_reg.h"
#include "o20a0/lbm_syn_o20a0_reg.h"
#include "o20a0/wov_syn_o20a0_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct {
/* CTOP */
	CTOP_CTRL_ATG_REG_O20A0_T	*CTOP_ATG;
	CTOP_CTRL_BMC_REG_O20A0_T	*CTOP_BMC;
	CTOP_CTRL_DPE_REG_O20A0_T	*CTOP_DPE;
	CTOP_CTRL_FME1_REG_O20A0_T	*CTOP_FME1;
	CTOP_CTRL_FMS_REG_O20A0_T	*CTOP_FMS;
	CTOP_CTRL_LBM_REG_O20A0_T	*CTOP_LBM;
	CTOP_CTRL_ND0_REG_O20A0_T	*CTOP_ND0;
	CTOP_CTRL_ND1_REG_O20A0_T	*CTOP_ND1;
	CTOP_CTRL_POR_REG_O20A0_T	*CTOP_POR;
	CTOP_CTRL_VD1_REG_O20A0_T	*CTOP_VD1;
	CTOP_CTRL_WOV_REG_O20A0_T	*CTOP_WOV;

/* CTOP_SYN */
	ATG_SYN_REG_O20A0_T			*ATG_SYN;
	BMC_SYN_REG_O20A0_T			*BMC_SYN;
	CCO_SYN_REG_O20A0_T			*CCO_SYN;
	CPU_SYN_REG_O20A0_T			*CPU_SYN;
	CVI_SYN_REG_O20A0_T			*CVI_SYN;
	GSC_SYN_REG_O20A0_T			*GSC_SYN;
	LBM_SYN_REG_O20A0_T			*LBM_SYN;
	WOV_SYN_REG_O20A0_T			*WOV_SYN;
} CTOP_REG_O20A0_T;

/* CTOP */
#define O20_A0_CTOP_ATG_BASE	0xC9301C00
#define O20_A0_CTOP_ATG_TYPE	CTOP_CTRL_ATG_REG_O20A0_T

#define O20_A0_CTOP_BMC_BASE	0xC34E0800
#define O20_A0_CTOP_BMC_TYPE    CTOP_CTRL_BMC_REG_O20A0_T

#define O20_A0_CTOP_DPE_BASE	0xC930F800
#define O20_A0_CTOP_DPE_TYPE	CTOP_CTRL_DPE_REG_O20A0_T

#define O20_A0_CTOP_FME1_BASE	0xC930B400
#define O20_A0_CTOP_FME1_TYPE	CTOP_CTRL_FME1_REG_O20A0_T

#define O20_A0_CTOP_FMS_BASE	0xC930E400
#define O20_A0_CTOP_FMS_TYPE	CTOP_CTRL_FMS_REG_O20A0_T

#define O20_A0_CTOP_LBM_BASE	0xC9300C00
#define O20_A0_CTOP_LBM_TYPE	CTOP_CTRL_LBM_REG_O20A0_T

#define O20_A0_CTOP_ND0_BASE	0xC9307400
#define O20_A0_CTOP_ND0_TYPE	CTOP_CTRL_ND0_REG_O20A0_T

#define O20_A0_CTOP_ND1_BASE	0xC9308400
#define O20_A0_CTOP_ND1_TYPE	CTOP_CTRL_ND1_REG_O20A0_T

#define O20_A0_CTOP_POR_BASE	0xC3300C00
#define O20_A0_CTOP_POR_TYPE	CTOP_CTRL_POR_REG_O20A0_T

#define O20_A0_CTOP_VD1_BASE	0xC9C71600
#define O20_A0_CTOP_VD1_TYPE    CTOP_CTRL_VD1_REG_O20A0_T

#define O20_A0_CTOP_WOV_BASE	0xC3300800
#define O20_A0_CTOP_WOV_TYPE	CTOP_CTRL_WOV_REG_O20A0_T

/* CTOP SYN */
#define O20_A0_ATG_SYN_BASE		0xC9301000
#define O20_A0_ATG_SYN_TYPE		ATG_SYN_REG_O20A0_T

#define O20_A0_BMC_SYN_BASE		0xC34E0000
#define O20_A0_BMC_SYN_TYPE		BMC_SYN_REG_O20A0_T

#define O20_A0_CCO_SYN_BASE		0xC930C000
#define O20_A0_CCO_SYN_TYPE		CCO_SYN_REG_O20A0_T

#define O20_A0_CPU_SYN_BASE		0xC9230000
#define O20_A0_CPU_SYN_TYPE		CPU_SYN_REG_O20A0_T

#define O20_A0_CVI_SYN_BASE		0xC9305000
#define O20_A0_CVI_SYN_TYPE		CVI_SYN_REG_O20A0_T

#define O20_A0_GSC_SYN_BASE		0xC930D000
#define O20_A0_GSC_SYN_TYPE		GSC_SYN_REG_O20A0_T

#define O20_A0_LBM_SYN_BASE		0xC9300000
#define O20_A0_LBM_SYN_TYPE		LBM_SYN_REG_O20A0_T

#define O20_A0_WOV_SYN_BASE		0xC3300000
#define O20_A0_WOV_SYN_TYPE		WOV_SYN_REG_O20A0_T


#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_O20_A0_H__ */

