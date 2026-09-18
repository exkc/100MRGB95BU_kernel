#ifndef __CTOP_CTRL_REG_E60_A0_H__
#define __CTOP_CTRL_REG_E60_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "e60a0/ctop_syn_cvi_e60a0_reg.h"
#include "e60a0/ctop_syn_dbb_e60a0_reg.h"
#include "e60a0/ctop_syn_dpe_e60a0_reg.h"
#include "e60a0/ctop_syn_fmc0_e60a0_reg.h"
#include "e60a0/ctop_syn_fmc1_e60a0_reg.h"
#include "e60a0/ctop_syn_fme0_e60a0_reg.h"
#include "e60a0/ctop_syn_fme1_e60a0_reg.h"
#include "e60a0/ctop_syn_fms_e60a0_reg.h"
#include "e60a0/ctop_syn_sre_e60a0_reg.h"
#include "e60a0/ctop_syn_wov_e60a0_reg.h"
#include "e60a0/ctop_syn_lgsr0_e60a0_reg.h"
#include "e60a0/ctop_syn_edid_e60a0_reg.h"

#include "e60a0/crg_sub_cvi_e60a0_reg.h"
#include "e60a0/crg_sub_dbb_e60a0_reg.h"
#include "e60a0/crg_sub_dpe_e60a0_reg.h"
#include "e60a0/crg_sub_wov_e60a0_reg.h"
#include "e60a0/crg_sub_hdmi_e60a0_reg.h"
#include "e60a0/crg_sub_imx2_e60a0_reg.h"


#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct {
	CTOP_SYN_CVI_REG_E60_A0_T	*CTOP_SYN_CVI;
	CTOP_SYN_DBB_REG_E60_A0_T	*CTOP_SYN_DBB;
	CTOP_SYN_DPE_REG_E60_A0_T	*CTOP_SYN_DPE;
	CTOP_SYN_FMC0_REG_E60_A0_T	*CTOP_SYN_FMC0;
	CTOP_SYN_FMC1_REG_E60_A0_T	*CTOP_SYN_FMC1;
	CTOP_SYN_FME0_REG_E60_A0_T	*CTOP_SYN_FME0;
	CTOP_SYN_FME1_REG_E60_A0_T	*CTOP_SYN_FME1;
	CTOP_SYN_FMS_REG_E60_A0_T	*CTOP_SYN_FMS;
	CTOP_SYN_SRE_REG_E60_A0_T	*CTOP_SYN_SRE;
	CTOP_SYN_WOV_REG_E60_A0_T	*CTOP_SYN_WOV;
	CTOP_SYN_LGSR0_REG_E60_A0_T	*CTOP_SYN_LGSR0;
	CTOP_SYN_EDID_REG_E60_A0_T	*CTOP_SYN_EDID;

	CRG_SUB_CVI_REG_E60_A0_T	*CRG_SUB_CVI;
	CRG_SUB_DPE_REG_E60_A0_T	*CRG_SUB_DPE;

	CRG_SUB_DBB_REG_E60_A0_T	*CRG_SUB_DBB;

	CRG_SUB_WOV_REG_E60_A0_T	*CRG_SUB_WOV;
	CRG_SUB_HDMI_REG_E60_A0_T	*CRG_SUB_HDMI;
	CRG_SUB_IMX2_REG_E60_A0_T	*CRG_SUB_IMX2;
} CTOP_REG_E60A0_T;

/* CTOP SYN */
#define E60_A0_CTOP_SYN_CVI_BASE	0xC93B8400
#define E60_A0_CTOP_SYN_CVI_TYPE	CTOP_SYN_CVI_REG_E60_A0_T

#define E60_A0_CTOP_SYN_DBB_BASE	0xC30C1800
#define E60_A0_CTOP_SYN_DBB_TYPE	CTOP_SYN_DBB_REG_E60_A0_T

#define E60_A0_CTOP_SYN_DPE_BASE	0xC9243400
#define E60_A0_CTOP_SYN_DPE_TYPE	CTOP_SYN_DPE_REG_E60_A0_T

#define E60_A0_CTOP_SYN_FMC0_BASE	0xC9322400
#define E60_A0_CTOP_SYN_FMC0_TYPE	CTOP_SYN_FMC0_REG_E60_A0_T

#define E60_A0_CTOP_SYN_FMC1_BASE	0xC9324400
#define E60_A0_CTOP_SYN_FMC1_TYPE	CTOP_SYN_FMC1_REG_E60_A0_T

#define E60_A0_CTOP_SYN_FME0_BASE	0xC9354400
#define E60_A0_CTOP_SYN_FME0_TYPE	CTOP_SYN_FME0_REG_E60_A0_T

#define E60_A0_CTOP_SYN_FME1_BASE	0xC932A400
#define E60_A0_CTOP_SYN_FME1_TYPE	CTOP_SYN_FME1_REG_E60_A0_T

#define E60_A0_CTOP_SYN_FMS_BASE	0xC9344400
#define E60_A0_CTOP_SYN_FMS_TYPE	CTOP_SYN_FMS_REG_E60_A0_T

#define E60_A0_CTOP_SYN_SRE_BASE	0xC9369400
#define E60_A0_CTOP_SYN_SRE_TYPE	CTOP_SYN_SRE_REG_E60_A0_T

#define E60_A0_CTOP_SYN_WOV_BASE	0xF3011400
#define E60_A0_CTOP_SYN_WOV_TYPE	CTOP_SYN_WOV_REG_E60_A0_T

#define E60_A0_CTOP_SYN_LGSR0_BASE	0xC935F400
#define E60_A0_CTOP_SYN_LGSR0_TYPE	CTOP_SYN_LGSR0_REG_E60_A0_T

#define E60_A0_CTOP_SYN_EDID_BASE	0xC98A2400
#define E60_A0_CTOP_SYN_EDID_TYPE	CTOP_SYN_EDID_REG_E60_A0_T

/* CRG SUB */
#define E60_A0_CRG_SUB_CVI_BASE		0xC93B8000
#define E60_A0_CRG_SUB_CVI_TYPE		CRG_SUB_CVI_REG_E60_A0_T

#define E60_A0_CRG_SUB_DPE_BASE		0xC9243000
#define E60_A0_CRG_SUB_DPE_TYPE		CRG_SUB_DPE_REG_E60_A0_T

/* CRG SUB DBB */
#define E60_A0_CRG_SUB_DBB_BASE		0xC30C1000
#define E60_A0_CRG_SUB_DBB_TYPE		CRG_SUB_DBB_REG_E60_A0_T

/* CRG SUB WOV */
#define E60_A0_CRG_SUB_WOV_BASE		0xF3011000
#define E60_A0_CRG_SUB_WOV_TYPE		CRG_SUB_WOV_REG_E60_A0_T

/* CRG SUB HDMI */
#define E60_A0_CRG_SUB_HDMI_BASE	0xC3320000
#define E60_A0_CRG_SUB_HDMI_TYPE	CRG_SUB_HDMI_REG_E60_A0_T

/* CRG SUB IMX2 */
#define E60_A0_CRG_SUB_IMX2_BASE	0xC93AC000
#define E60_A0_CRG_SUB_IMX2_TYPE	CRG_SUB_IMX2_REG_E60_A0_T


#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_E60_A0_H__ */

