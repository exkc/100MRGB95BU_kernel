#ifndef __CTOP_CTRL_REG_M23_A0_H__
#define __CTOP_CTRL_REG_M23_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

// ipw
#include "m23a0/ip_ctrl_aud_m23a0_reg.h"
#include "m23a0/ip_ctrl_cco_m23a0_reg.h"
#include "m23a0/ip_ctrl_cpu_m23a0_reg.h"
#include "m23a0/ip_ctrl_cvi_m23a0_reg.h"
#include "m23a0/ip_ctrl_dbb_m23a0_reg.h"
#include "m23a0/ip_ctrl_dne_m23a0_reg.h"
#include "m23a0/ip_ctrl_edid0_m23a0_reg.h"
#include "m23a0/ip_ctrl_edid1_m23a0_reg.h"
#include "m23a0/ip_ctrl_fmc_m23a0_reg.h"
#include "m23a0/ip_ctrl_fms_m23a0_reg.h"
#include "m23a0/ip_ctrl_gsc_m23a0_reg.h"
#include "m23a0/ip_ctrl_hdmi_m23a0_reg.h"
#include "m23a0/ip_ctrl_hdr_m23a0_reg.h"
#include "m23a0/ip_ctrl_imx_m23a0_reg.h"
#include "m23a0/ip_ctrl_led_m23a0_reg.h"
#include "m23a0/ip_ctrl_me_m23a0_reg.h"
#include "m23a0/ip_ctrl_nd_m23a0_reg.h"
#include "m23a0/ip_ctrl_sre_m23a0_reg.h"
#include "m23a0/ip_ctrl_tcon_m23a0_reg.h"
#include "m23a0/ip_ctrl_te_m23a0_reg.h"
#include "m23a0/ip_ctrl_vdo_m23a0_reg.h"
#include "m23a0/ip_ctrl_vsd_m23a0_reg.h"

// syn
#include "m23a0/bnd_ctrl_aud_m23a0_reg.h"
#include "m23a0/bnd_ctrl_bmc_m23a0_reg.h"
#include "m23a0/bnd_ctrl_cpu_m23a0_reg.h"
#include "m23a0/bnd_ctrl_cvi_m23a0_reg.h"
#include "m23a0/bnd_ctrl_edid_m23a0_reg.h"
#include "m23a0/bnd_ctrl_fmc_m23a0_reg.h"
#include "m23a0/bnd_ctrl_fms_m23a0_reg.h"
#include "m23a0/bnd_ctrl_m0_m23a0_reg.h"
#include "m23a0/bnd_ctrl_me0_m23a0_reg.h"
#include "m23a0/bnd_ctrl_nd0_m23a0_reg.h"

#include "m23a0/micom_power_ctrl_m23a0_reg.h"
#include "m23a0/crg_top_ctrl_m23a0_reg.h"
#include "m23a0/pvmcon_cpu_m23a0_reg.h"

#include "m23a0/tmux_ctrl_m23a0_reg.h"
#include "m23a0/mip_tsadc_ctrl_m23a0_reg.h"

// pad
#include "m23a0/cpu_iomux_ctrl_woc_m23a0_reg.h"
#include "m23a0/iomux_ctrl_bmc_m23a0_reg.h"
#include "m23a0/iomux_ctrl_edid_m23a0_reg.h"
#include "m23a0/iomux_ctrl_vd0_m23a0_reg.h"
#include "m23a0/iomux_ctrl_vd1_m23a0_reg.h"


// mip
#include "m23a0/mip_acodec_ctrl_bmc_m23a0_reg.h"
#include "m23a0/mip_adc_ctrl_bmc_m23a0_reg.h"
#include "m23a0/mip_ctrl_c4tx_m23a0_reg.h"
#include "m23a0/mip_ctrl_earc_m23a0_reg.h"
#include "m23a0/mip_ctrl_dpm_m23a0_reg.h"

// crg_sub
#include "m23a0/bcrg_ctrl_aud_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_bmc_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_bus_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_cpu_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_cvi_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_dpe_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_edid_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_fmc_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_fms_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_m0_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_me0_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_nd0_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_vd0_m23a0_reg.h"
#include "m23a0/bcrg_ctrl_vd1_m23a0_reg.h"

#include "m23a0/cpu_bcrg_ctrl_woc_m23a0_reg.h"
#include "m23a0/cpu_mcrg_ctrl_woc_m23a0_reg.h"
#include "m23a0/cpu_scrg_ctrl_micom_m23a0_reg.h"
#include "m23a0/cpu_scrg_ctrl_pmcu_m23a0_reg.h"
#include "m23a0/cpu_scrg_ctrl_vmcu_m23a0_reg.h"

#include "m23a0/mcrg_ctrl_aud_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_bmc_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_bus_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_cpu_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_cvi_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_dpe_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_edid_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_fms_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_m0_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_me0_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_nd0_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_vd0_m23a0_reg.h"
#include "m23a0/mcrg_ctrl_vd1_m23a0_reg.h"

#include "m23a0/micom_bnd_ctrl_woc_m23a0_reg.h"
#include "m23a0/micom_crg_top_woc_ctrl_m23a0_reg.h"

#include "m23a0/scrg_ctrl_aud_m23a0_reg.h"
#include "m23a0/scrg_ctrl_cco_m23a0_reg.h"
#include "m23a0/scrg_ctrl_cpu_m23a0_reg.h"
#include "m23a0/scrg_ctrl_cvbsb_m23a0_reg.h"
#include "m23a0/scrg_ctrl_cvi_m23a0_reg.h"
#include "m23a0/scrg_ctrl_dbb_m23a0_reg.h"
#include "m23a0/scrg_ctrl_ddrsb_m23a0_reg.h"
#include "m23a0/scrg_ctrl_dne_m23a0_reg.h"
#include "m23a0/scrg_ctrl_edid0_m23a0_reg.h"
#include "m23a0/scrg_ctrl_edid1_m23a0_reg.h"
#include "m23a0/scrg_ctrl_emmc_m23a0_reg.h"
#include "m23a0/scrg_ctrl_emusb_m23a0_reg.h"
#include "m23a0/scrg_ctrl_ephy_m23a0_reg.h"
#include "m23a0/scrg_ctrl_epusb_m23a0_reg.h"
#include "m23a0/scrg_ctrl_fmc_m23a0_reg.h"
#include "m23a0/scrg_ctrl_fms_m23a0_reg.h"
#include "m23a0/scrg_ctrl_gfx_m23a0_reg.h"
#include "m23a0/scrg_ctrl_gsc_m23a0_reg.h"
#include "m23a0/scrg_ctrl_hdmi_m23a0_reg.h"
#include "m23a0/scrg_ctrl_hdr_m23a0_reg.h"
#include "m23a0/scrg_ctrl_icod_m23a0_reg.h"
#include "m23a0/scrg_ctrl_imx_m23a0_reg.h"
#include "m23a0/scrg_ctrl_lbus_m23a0_reg.h"
#include "m23a0/scrg_ctrl_led_m23a0_reg.h"
#include "m23a0/scrg_ctrl_lne_m23a0_reg.h"
#include "m23a0/scrg_ctrl_m0_m23a0_reg.h"
#include "m23a0/scrg_ctrl_me_m23a0_reg.h"
#include "m23a0/scrg_ctrl_nd_m23a0_reg.h"
#include "m23a0/scrg_ctrl_pdm_m23a0_reg.h"
#include "m23a0/scrg_ctrl_sre_m23a0_reg.h"
#include "m23a0/scrg_ctrl_tcon_m23a0_reg.h"
#include "m23a0/scrg_ctrl_te_m23a0_reg.h"
#include "m23a0/scrg_ctrl_tivsb_m23a0_reg.h"
#include "m23a0/scrg_ctrl_usb_hs1_m23a0_reg.h"
#include "m23a0/scrg_ctrl_usb_hs2_m23a0_reg.h"
#include "m23a0/scrg_ctrl_usb_hs3_m23a0_reg.h"
#include "m23a0/scrg_ctrl_vd0_m23a0_reg.h"
#include "m23a0/scrg_ctrl_vd1_m23a0_reg.h"
#include "m23a0/scrg_ctrl_vdo_m23a0_reg.h"
#include "m23a0/scrg_ctrl_venc_m23a0_reg.h"
#include "m23a0/scrg_ctrl_vsd_m23a0_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct
{
	// ipw
	IP_CTRL_AUD_REG_M23A0_T                  *IP_CTRL_AUD;            // ip_ctrl_aud_m23a0_reg.h
	IP_CTRL_CCO_REG_M23A0_T                  *IP_CTRL_CCO;            // ip_ctrl_cco_m23a0_reg.h
	IP_CTRL_CPU_REG_M23A0_T                  *IP_CTRL_CPU;            // ip_ctrl_cpu_m23a0_reg.h
	IP_CTRL_CVI_REG_M23A0_T                  *IP_CTRL_CVI;            // ip_ctrl_cvi_m23a0_reg.h
	IP_CTRL_DBB_REG_M23A0_T                  *IP_CTRL_DBB;            // ip_ctrl_dbb_m23a0_reg.h
	IP_CTRL_DNE_REG_M23A0_T                  *IP_CTRL_DNE;            // ip_ctrl_dne_m23a0_reg.h
	IP_CTRL_EDID0_REG_M23A0_T                *IP_CTRL_EDID0;          // ip_ctrl_edid0_m23a0_reg.h
	IP_CTRL_EDID1_REG_M23A0_T                *IP_CTRL_EDID1;          // ip_ctrl_edid1_m23a0_reg.h
	IP_CTRL_FMC_REG_M23A0_T                  *IP_CTRL_FMC;            // ip_ctrl_fmc_m23a0_reg.h
	IP_CTRL_FMS_REG_M23A0_T                  *IP_CTRL_FMS;            // ip_ctrl_fms_m23a0_reg.h
	IP_CTRL_GSC_REG_M23A0_T                  *IP_CTRL_GSC;            // ip_ctrl_gsc_m23a0_reg.h
	IP_CTRL_HDMI_REG_M23A0_T                 *IP_CTRL_HDMI;           // ip_ctrl_hdmi_m23a0_reg.h
	IP_CTRL_HDR_REG_M23A0_T                  *IP_CTRL_HDR;            // ip_ctrl_hdr_m23a0_reg.h
	IP_CTRL_IMX_REG_M23A0_T                  *IP_CTRL_IMX;            // ip_ctrl_imx_m23a0_reg.h
	IP_CTRL_LED_REG_M23A0_T                  *IP_CTRL_LED;            // ip_ctrl_led_m23a0_reg.h
	IP_CTRL_ME_REG_M23A0_T                   *IP_CTRL_ME;             // ip_ctrl_me_m23a0_reg.h
	IP_CTRL_ND_REG_M23A0_T                   *IP_CTRL_ND;             // ip_ctrl_nd_m23a0_reg.h
	IP_CTRL_SRE_REG_M23A0_T                  *IP_CTRL_SRE;            // ip_ctrl_sre_m23a0_reg.h
	IP_CTRL_TCON_REG_M23A0_T                 *IP_CTRL_TCON;           // ip_ctrl_tcon_m23a0_reg.h
	IP_CTRL_TE_REG_M23A0_T                   *IP_CTRL_TE;             // ip_ctrl_te_m23a0_reg.h
	IP_CTRL_VDO_REG_M23A0_T                  *IP_CTRL_VDO;            // ip_ctrl_vdo_m23a0_reg.h
	IP_CTRL_VSD_REG_M23A0_T                  *IP_CTRL_VSD;            // ip_ctrl_vsd_m23a0_reg.h

	// syn
	BND_CTRL_AUD_REG_M23A0_T                 *BND_CTRL_AUD;           // bnd_ctrl_aud_m23a0_reg.h
	BND_CTRL_BMC_REG_M23A0_T                 *BND_CTRL_BMC;           // bnd_ctrl_bmc_m23a0_reg.h
	BND_CTRL_CPU_REG_M23A0_T                 *BND_CTRL_CPU;           // bnd_ctrl_cpu_m23a0_reg.h
	BND_CTRL_CVI_REG_M23A0_T                 *BND_CTRL_CVI;           // bnd_ctrl_cvi_m23a0_reg.h
	BND_CTRL_EDID_REG_M23A0_T                *BND_CTRL_EDID;          // bnd_ctrl_edid_m23a0_reg.h
	BND_CTRL_FMC_REG_M23A0_T                 *BND_CTRL_FMC;           // bnd_ctrl_fmc_m23a0_reg.h
	BND_CTRL_FMS_REG_M23A0_T                 *BND_CTRL_FMS;           // bnd_ctrl_fms_m23a0_reg.h
	BND_CTRL_M0_REG_M23A0_T                  *BND_CTRL_M0;            // bnd_ctrl_m0_m23a0_reg.h
	BND_CTRL_ME0_REG_M23A0_T                 *BND_CTRL_ME0;           // bnd_ctrl_me0_m23a0_reg.h
	BND_CTRL_ND0_REG_M23A0_T                 *BND_CTRL_ND0;           // bnd_ctrl_nd0_m23a0_reg.h

	MICOM_POWER_CTRL_REG_M23A0_T             *CPU_POWER_CTRL;         // micom_power_ctrl_m23a0_reg.h
	MICOM_POWER_CTRL_REG_M23A0_T             *MICOM_POWER_CTRL;       // micom_power_ctrl_m23a0_reg.h
	CRG_TOP_CTRL_REG_M23A0_T                 *CRG_TOP_CTRL;           // crg_top_ctrl_m23a0_reg.h
	PVMCON_CPU_REG_M23A0_T                   *PVMCON_CPU;             // pvmcon_cpu_m23a0_reg.h

	TMUX_CTRL_REG_M23A0_T                    *TMUX_CTRL;              // tmux_ctrl_m23a0_reg.h
	MIP_TSADC_CTRL_REG_M23A0_T               *MIP_TSADC_CTRL;         // mip_tsadc_ctrl_m23a0_reg.h

	// pad
	CPU_IOMUX_CTRL_WOC_REG_M23A0_T           *CPU_IOMUX_CTRL_WOC;     // cpu_iomux_ctrl_woc_m23a0_reg.h
	CPU_IOMUX_CTRL_WOC_REG_M23A0_T           *MICOM_IOMUX_CTRL_WOC;   // cpu_iomux_ctrl_woc_m23a0_reg.h
	IOMUX_CTRL_BMC_REG_M23A0_T               *IOMUX_CTRL_BMC;         // iomux_ctrl_bmc_m23a0_reg.h
	IOMUX_CTRL_EDID_REG_M23A0_T              *IOMUX_CTRL_EDID;        // iomux_ctrl_edid_m23a0_reg.h
	IOMUX_CTRL_VD0_REG_M23A0_T               *IOMUX_CTRL_VD0;         // iomux_ctrl_vd0_m23a0_reg.h
	IOMUX_CTRL_VD1_REG_M23A0_T               *IOMUX_CTRL_VD1;         // iomux_ctrl_vd1_m23a0_reg.h

	// mip
	MIP_ACODEC_CTRL_BMC_REG_M23A0_T          *MIP_ACODEC_CTRL_BMC;    // mip_acodec_ctrl_bmc_m23a0_reg.h
	MIP_ADC_CTRL_BMC_REG_M23A0_T             *MIP_ADC_CTRL_BMC;       // mip_adc_ctrl_bmc_m23a0_reg.h
	MIP_CTRL_C4TX_REG_M23A0_T                *MIP_CTRL_C4TX;          // mip_ctrl_c4tx_m23a0_reg.h
	MIP_CTRL_EARC_REG_M23A0_T                *MIP_CTRL_EARC;          // mip_ctrl_earc_m23a0_reg.h
	MIP_CTRL_DPM_REG_M23A0_T                 *MIP_CTRL_DPM;           // mip_ctrl_dpm_m23a0_reg.h

	// crg_sub
	BCRG_CTRL_AUD_REG_M23A0_T                *BCRG_CTRL_AUD;          // bcrg_ctrl_aud_m23a0_reg.h
	BCRG_CTRL_BMC_REG_M23A0_T                *BCRG_CTRL_BMC;          // bcrg_ctrl_bmc_m23a0_reg.h
	BCRG_CTRL_BUS_REG_M23A0_T                *BCRG_CTRL_BUS;          // bcrg_ctrl_bus_m23a0_reg.h
	BCRG_CTRL_CPU_REG_M23A0_T                *BCRG_CTRL_CPU;          // bcrg_ctrl_cpu_m23a0_reg.h
	BCRG_CTRL_CVI_REG_M23A0_T                *BCRG_CTRL_CVI;          // bcrg_ctrl_cvi_m23a0_reg.h
	BCRG_CTRL_DPE_REG_M23A0_T                *BCRG_CTRL_DPE;          // bcrg_ctrl_dpe_m23a0_reg.h
	BCRG_CTRL_EDID_REG_M23A0_T               *BCRG_CTRL_EDID;         // bcrg_ctrl_edid_m23a0_reg.h
	BCRG_CTRL_FMC_REG_M23A0_T                *BCRG_CTRL_FMC;          // bcrg_ctrl_fmc_m23a0_reg.h
	BCRG_CTRL_FMS_REG_M23A0_T                *BCRG_CTRL_FMS;          // bcrg_ctrl_fms_m23a0_reg.h
	BCRG_CTRL_M0_REG_M23A0_T                 *BCRG_CTRL_M0;           // bcrg_ctrl_m0_m23a0_reg.h
	BCRG_CTRL_ME0_REG_M23A0_T                *BCRG_CTRL_ME0;          // bcrg_ctrl_me0_m23a0_reg.h
	BCRG_CTRL_ND0_REG_M23A0_T                *BCRG_CTRL_ND0;          // bcrg_ctrl_nd0_m23a0_reg.h
	BCRG_CTRL_VD0_REG_M23A0_T                *BCRG_CTRL_VD0;          // bcrg_ctrl_vd0_m23a0_reg.h
	BCRG_CTRL_VD1_REG_M23A0_T                *BCRG_CTRL_VD1;          // bcrg_ctrl_vd1_m23a0_reg.h
	CPU_BCRG_CTRL_WOC_REG_M23A0_T            *CPU_BCRG_CTRL_WOC;      // cpu_bcrg_ctrl_woc_m23a0_reg.h
	CPU_BCRG_CTRL_WOC_REG_M23A0_T            *MICOM_BCRG_CTRL_WOC;    // cpu_bcrg_ctrl_woc_m23a0_reg.h

	CPU_MCRG_CTRL_WOC_REG_M23A0_T            *CPU_MCRG_CTRL_WOC;      // cpu_mcrg_ctrl_woc_m23a0_reg.h
	CPU_MCRG_CTRL_WOC_REG_M23A0_T            *MICOM_MCRG_CTRL_WOC;    // cpu_mcrg_ctrl_woc_m23a0_reg.h
	MCRG_CTRL_AUD_REG_M23A0_T                *MCRG_CTRL_AUD;          // mcrg_ctrl_aud_m23a0_reg.h
	MCRG_CTRL_BMC_REG_M23A0_T                *MCRG_CTRL_BMC;          // mcrg_ctrl_bmc_m23a0_reg.h
	MCRG_CTRL_BUS_REG_M23A0_T                *MCRG_CTRL_BUS;          // mcrg_ctrl_bus_m23a0_reg.h
	MCRG_CTRL_CPU_REG_M23A0_T                *MCRG_CTRL_CPU;          // mcrg_ctrl_cpu_m23a0_reg.h
	MCRG_CTRL_CVI_REG_M23A0_T                *MCRG_CTRL_CVI;          // mcrg_ctrl_cvi_m23a0_reg.h
	MCRG_CTRL_DPE_REG_M23A0_T                *MCRG_CTRL_DPE;          // mcrg_ctrl_dpe_m23a0_reg.h
	MCRG_CTRL_EDID_REG_M23A0_T               *MCRG_CTRL_EDID;         // mcrg_ctrl_edid_m23a0_reg.h
	MCRG_CTRL_FMS_REG_M23A0_T                *MCRG_CTRL_FMS;          // mcrg_ctrl_fms_m23a0_reg.h
	MCRG_CTRL_M0_REG_M23A0_T                 *MCRG_CTRL_M0;           // mcrg_ctrl_m0_m23a0_reg.h
	MCRG_CTRL_ME0_REG_M23A0_T                *MCRG_CTRL_ME0;          // mcrg_ctrl_me0_m23a0_reg.h
	MCRG_CTRL_ND0_REG_M23A0_T                *MCRG_CTRL_ND0;          // mcrg_ctrl_nd0_m23a0_reg.h
	MCRG_CTRL_VD0_REG_M23A0_T                *MCRG_CTRL_VD0;          // mcrg_ctrl_vd0_m23a0_reg.h
	MCRG_CTRL_VD1_REG_M23A0_T                *MCRG_CTRL_VD1;          // mcrg_ctrl_vd1_m23a0_reg.h

	CPU_SCRG_CTRL_MICOM_REG_M23A0_T          *CPU_SCRG_CTRL_MICOM;    // cpu_scrg_ctrl_micom_m23a0_reg.h
	CPU_SCRG_CTRL_PMCU_REG_M23A0_T           *CPU_SCRG_CTRL_PMCU;     // cpu_scrg_ctrl_pmcu_m23a0_reg.h
	CPU_SCRG_CTRL_VMCU_REG_M23A0_T           *CPU_SCRG_CTRL_VMCU;     // cpu_scrg_ctrl_vmcu_m23a0_reg.h
	SCRG_CTRL_AUD_REG_M23A0_T                *SCRG_CTRL_AUD;          // scrg_ctrl_aud_m23a0_reg.h
	SCRG_CTRL_CCO_REG_M23A0_T                *SCRG_CTRL_CCO;          // scrg_ctrl_cco_m23a0_reg.h
	SCRG_CTRL_CPU_REG_M23A0_T                *SCRG_CTRL_CPU;          // scrg_ctrl_cpu_m23a0_reg.h
	SCRG_CTRL_CVBSB_REG_M23A0_T              *SCRG_CTRL_CVBSB;        // scrg_ctrl_cvbsb_m23a0_reg.h
	SCRG_CTRL_CVI_REG_M23A0_T                *SCRG_CTRL_CVI;          // scrg_ctrl_cvi_m23a0_reg.h
	SCRG_CTRL_DBB_REG_M23A0_T                *SCRG_CTRL_DBB;          // scrg_ctrl_dbb_m23a0_reg.h
	SCRG_CTRL_DDRSB_REG_M23A0_T              *SCRG_CTRL_DDRSB;        // scrg_ctrl_ddrsb_m23a0_reg.h
	SCRG_CTRL_DNE_REG_M23A0_T                *SCRG_CTRL_DNE;          // scrg_ctrl_dne_m23a0_reg.h
	SCRG_CTRL_EDID0_REG_M23A0_T              *SCRG_CTRL_EDID0;        // scrg_ctrl_edid0_m23a0_reg.h
	SCRG_CTRL_EDID1_REG_M23A0_T              *SCRG_CTRL_EDID1;        // scrg_ctrl_edid1_m23a0_reg.h
	SCRG_CTRL_EMMC_REG_M23A0_T               *SCRG_CTRL_EMMC;         // scrg_ctrl_emmc_m23a0_reg.h
	SCRG_CTRL_EMUSB_REG_M23A0_T              *SCRG_CTRL_EMUSB;        // scrg_ctrl_emusb_m23a0_reg.h
	SCRG_CTRL_EPHY_REG_M23A0_T               *SCRG_CTRL_EPHY;         // scrg_ctrl_ephy_m23a0_reg.h
	SCRG_CTRL_EPUSB_REG_M23A0_T              *SCRG_CTRL_EPUSB;        // scrg_ctrl_epusb_m23a0_reg.h
	SCRG_CTRL_FMC_REG_M23A0_T                *SCRG_CTRL_FMC;          // scrg_ctrl_fmc_m23a0_reg.h
	SCRG_CTRL_FMS_REG_M23A0_T                *SCRG_CTRL_FMS;          // scrg_ctrl_fms_m23a0_reg.h
	SCRG_CTRL_GFX_REG_M23A0_T                *SCRG_CTRL_GFX;          // scrg_ctrl_gfx_m23a0_reg.h
	SCRG_CTRL_GSC_REG_M23A0_T                *SCRG_CTRL_GSC;          // scrg_ctrl_gsc_m23a0_reg.h
	SCRG_CTRL_HDMI_REG_M23A0_T               *SCRG_CTRL_HDMI;         // scrg_ctrl_hdmi_m23a0_reg.h
	SCRG_CTRL_HDR_REG_M23A0_T                *SCRG_CTRL_HDR;          // scrg_ctrl_hdr_m23a0_reg.h
	SCRG_CTRL_ICOD_REG_M23A0_T               *SCRG_CTRL_ICOD;         // scrg_ctrl_icod_m23a0_reg.h
	SCRG_CTRL_IMX_REG_M23A0_T                *SCRG_CTRL_IMX;          // scrg_ctrl_imx_m23a0_reg.h
	SCRG_CTRL_LBUS_REG_M23A0_T               *SCRG_CTRL_LBUS;         // scrg_ctrl_lbus_m23a0_reg.h
	SCRG_CTRL_LED_REG_M23A0_T                *SCRG_CTRL_LED;          // scrg_ctrl_led_m23a0_reg.h
	SCRG_CTRL_LNE_REG_M23A0_T                *SCRG_CTRL_LNE;          // scrg_ctrl_lne_m23a0_reg.h
	SCRG_CTRL_M0_REG_M23A0_T                 *SCRG_CTRL_M0;           // scrg_ctrl_m0_m23a0_reg.h
	SCRG_CTRL_ME_REG_M23A0_T                 *SCRG_CTRL_ME;           // scrg_ctrl_me_m23a0_reg.h
	SCRG_CTRL_ND_REG_M23A0_T                 *SCRG_CTRL_ND;           // scrg_ctrl_nd_m23a0_reg.h
	SCRG_CTRL_PDM_REG_M23A0_T                *SCRG_CTRL_PDM;          // scrg_ctrl_pdm_m23a0_reg.h
	SCRG_CTRL_SRE_REG_M23A0_T                *SCRG_CTRL_SRE;          // scrg_ctrl_sre_m23a0_reg.h
	SCRG_CTRL_TCON_REG_M23A0_T               *SCRG_CTRL_TCON;         // scrg_ctrl_tcon_m23a0_reg.h
	SCRG_CTRL_TE_REG_M23A0_T                 *SCRG_CTRL_TE;           // scrg_ctrl_te_m23a0_reg.h
	SCRG_CTRL_TIVSB_REG_M23A0_T              *SCRG_CTRL_TIVSB;        // scrg_ctrl_tivsb_m23a0_reg.h
	SCRG_CTRL_USB_HS1_REG_M23A0_T            *SCRG_CTRL_USB_HS1;      // scrg_ctrl_usb_hs1_m23a0_reg.h
	SCRG_CTRL_USB_HS2_REG_M23A0_T            *SCRG_CTRL_USB_HS2;      // scrg_ctrl_usb_hs2_m23a0_reg.h
	SCRG_CTRL_USB_HS3_REG_M23A0_T            *SCRG_CTRL_USB_HS3;      // scrg_ctrl_usb_hs3_m23a0_reg.h
	SCRG_CTRL_VD0_REG_M23A0_T                *SCRG_CTRL_VD0;          // scrg_ctrl_vd0_m23a0_reg.h
	SCRG_CTRL_VD1_REG_M23A0_T                *SCRG_CTRL_VD1;          // scrg_ctrl_vd1_m23a0_reg.h
	SCRG_CTRL_VDO_REG_M23A0_T                *SCRG_CTRL_VDO;          // scrg_ctrl_vdo_m23a0_reg.h
	SCRG_CTRL_VENC_REG_M23A0_T               *SCRG_CTRL_VENC;         // scrg_ctrl_venc_m23a0_reg.h
	SCRG_CTRL_VSD_REG_M23A0_T                *SCRG_CTRL_VSD;          // scrg_ctrl_vsd_m23a0_reg.h

	MICOM_BND_CTRL_WOC_REG_M23A0_T           *CPU_BND_CTRL_WOC;       // micom_bnd_ctrl_woc_m23a0_reg.h
	MICOM_BND_CTRL_WOC_REG_M23A0_T           *MICOM_BND_CTRL_WOC;     // micom_bnd_ctrl_woc_m23a0_reg.h
	MICOM_CRG_TOP_WOC_CTRL_REG_M23A0_T       *CPU_CRG_TOP_WOC_CTRL;   // micom_crg_top_woc_ctrl_m23a0_reg.h
	MICOM_CRG_TOP_WOC_CTRL_REG_M23A0_T       *MICOM_CRG_TOP_WOC_CTRL; // micom_crg_top_woc_ctrl_m23a0_reg.h
}
CTOP_REG_M23A0_T;

#define M23_A0_SCRG_CTRL_LBUS_BASE               0xC4510000
#define M23_A0_SCRG_CTRL_LBUS_TYPE               SCRG_CTRL_LBUS_REG_M23A0_T

#define M23_A0_SCRG_CTRL_DDRSB_BASE              0xC4550000
#define M23_A0_SCRG_CTRL_DDRSB_TYPE              SCRG_CTRL_DDRSB_REG_M23A0_T

#define M23_A0_SCRG_CTRL_EMUSB_BASE              0xC4580000
#define M23_A0_SCRG_CTRL_EMUSB_TYPE              SCRG_CTRL_EMUSB_REG_M23A0_T

#define M23_A0_SCRG_CTRL_GFX_BASE                0xC4710000
#define M23_A0_SCRG_CTRL_GFX_TYPE                SCRG_CTRL_GFX_REG_M23A0_T

#define M23_A0_SCRG_CTRL_EMMC_BASE               0xC4750000
#define M23_A0_SCRG_CTRL_EMMC_TYPE               SCRG_CTRL_EMMC_REG_M23A0_T

#define M23_A0_SCRG_CTRL_USB_HS1_BASE            0xC4780000
#define M23_A0_SCRG_CTRL_USB_HS1_TYPE            SCRG_CTRL_USB_HS1_REG_M23A0_T

#define M23_A0_SCRG_CTRL_HDMI_BASE               0xC47B0000
#define M23_A0_SCRG_CTRL_HDMI_TYPE               SCRG_CTRL_HDMI_REG_M23A0_T

#define M23_A0_IP_CTRL_HDMI_BASE                 0xC47B1000
#define M23_A0_IP_CTRL_HDMI_TYPE                 IP_CTRL_HDMI_REG_M23A0_T


#define M23_A0_SCRG_CTRL_M0_BASE                 0xC4F60000
#define M23_A0_SCRG_CTRL_M0_TYPE                 SCRG_CTRL_M0_REG_M23A0_T


#define M23_A0_MCRG_CTRL_M0_BASE                 0xC4F70000
#define M23_A0_MCRG_CTRL_M0_TYPE                 MCRG_CTRL_M0_REG_M23A0_T

#define M23_A0_BCRG_CTRL_M0_BASE                 0xC4F71000
#define M23_A0_BCRG_CTRL_M0_TYPE                 BCRG_CTRL_M0_REG_M23A0_T

#define M23_A0_BND_CTRL_M0_BASE                  0xC4F72000
#define M23_A0_BND_CTRL_M0_TYPE                  BND_CTRL_M0_REG_M23A0_T

#define M23_A0_SCRG_CTRL_DBB_BASE                0xC6110000
#define M23_A0_SCRG_CTRL_DBB_TYPE                SCRG_CTRL_DBB_REG_M23A0_T

#define M23_A0_IP_CTRL_DBB_BASE                  0xC6111000
#define M23_A0_IP_CTRL_DBB_TYPE                  IP_CTRL_DBB_REG_M23A0_T

#define M23_A0_MCRG_CTRL_BMC_BASE                0xC6150000
#define M23_A0_MCRG_CTRL_BMC_TYPE                MCRG_CTRL_BMC_REG_M23A0_T

#define M23_A0_BCRG_CTRL_BMC_BASE                0xC6151000
#define M23_A0_BCRG_CTRL_BMC_TYPE                BCRG_CTRL_BMC_REG_M23A0_T

#define M23_A0_BND_CTRL_BMC_BASE                 0xC6152000
#define M23_A0_BND_CTRL_BMC_TYPE                 BND_CTRL_BMC_REG_M23A0_T

#define M23_A0_IOMUX_CTRL_BMC_BASE               0xC6153000
#define M23_A0_IOMUX_CTRL_BMC_TYPE               IOMUX_CTRL_BMC_REG_M23A0_T

#define M23_A0_MIP_ACODEC_CTRL_BMC_BASE          0xC6154000
#define M23_A0_MIP_ACODEC_CTRL_BMC_TYPE          MIP_ACODEC_CTRL_BMC_REG_M23A0_T

#define M23_A0_MIP_ADC_CTRL_BMC_BASE             0xC6155000
#define M23_A0_MIP_ADC_CTRL_BMC_TYPE             MIP_ADC_CTRL_BMC_REG_M23A0_T

#define M23_A0_SCRG_CTRL_EDID0_BASE              0xC6190000
#define M23_A0_SCRG_CTRL_EDID0_TYPE              SCRG_CTRL_EDID0_REG_M23A0_T

#define M23_A0_IP_CTRL_EDID0_BASE                0xC6191000
#define M23_A0_IP_CTRL_EDID0_TYPE                IP_CTRL_EDID0_REG_M23A0_T

#define M23_A0_MCRG_CTRL_EDID_BASE               0xC61B0000
#define M23_A0_MCRG_CTRL_EDID_TYPE               MCRG_CTRL_EDID_REG_M23A0_T

#define M23_A0_BCRG_CTRL_EDID_BASE               0xC61B1000
#define M23_A0_BCRG_CTRL_EDID_TYPE               BCRG_CTRL_EDID_REG_M23A0_T

#define M23_A0_BND_CTRL_EDID_BASE                0xC61B2000
#define M23_A0_BND_CTRL_EDID_TYPE                BND_CTRL_EDID_REG_M23A0_T

#define M23_A0_IOMUX_CTRL_EDID_BASE              0xC61B3000
#define M23_A0_IOMUX_CTRL_EDID_TYPE              IOMUX_CTRL_EDID_REG_M23A0_T

#define M23_A0_SCRG_CTRL_USB_HS2_BASE            0xC8110000
#define M23_A0_SCRG_CTRL_USB_HS2_TYPE            SCRG_CTRL_USB_HS2_REG_M23A0_T

#define M23_A0_SCRG_CTRL_USB_HS3_BASE            0xC8140000
#define M23_A0_SCRG_CTRL_USB_HS3_TYPE            SCRG_CTRL_USB_HS3_REG_M23A0_T

#define M23_A0_SCRG_CTRL_EPUSB_BASE              0xC8170000
#define M23_A0_SCRG_CTRL_EPUSB_TYPE              SCRG_CTRL_EPUSB_REG_M23A0_T

#define M23_A0_CPU_SCRG_CTRL_MICOM_BASE          0xC8500000
#define M23_A0_CPU_SCRG_CTRL_MICOM_TYPE          CPU_SCRG_CTRL_MICOM_REG_M23A0_T

#define M23_A0_CPU_MCRG_CTRL_WOC_BASE            0xC8510000
#define M23_A0_CPU_MCRG_CTRL_WOC_TYPE            CPU_MCRG_CTRL_WOC_REG_M23A0_T
#define M23_A0_MICOM_MCRG_CTRL_WOC_BASE          0xF3510000
#define M23_A0_MICOM_MCRG_CTRL_WOC_TYPE          CPU_MCRG_CTRL_WOC_REG_M23A0_T

#define M23_A0_CPU_BCRG_CTRL_WOC_BASE            0xC8511000
#define M23_A0_CPU_BCRG_CTRL_WOC_TYPE            CPU_BCRG_CTRL_WOC_REG_M23A0_T
#define M23_A0_MICOM_BCRG_CTRL_WOC_BASE          0xF3511000
#define M23_A0_MICOM_BCRG_CTRL_WOC_TYPE          CPU_BCRG_CTRL_WOC_REG_M23A0_T

#define M23_A0_CPU_IOMUX_CTRL_WOC_BASE           0xC8515000
#define M23_A0_CPU_IOMUX_CTRL_WOC_TYPE           CPU_IOMUX_CTRL_WOC_REG_M23A0_T
#define M23_A0_MICOM_IOMUX_CTRL_WOC_BASE         0xF3515000
#define M23_A0_MICOM_IOMUX_CTRL_WOC_TYPE         CPU_IOMUX_CTRL_WOC_REG_M23A0_T

#define M23_A0_SCRG_CTRL_CPU_BASE                0xCA210000
#define M23_A0_SCRG_CTRL_CPU_TYPE                SCRG_CTRL_CPU_REG_M23A0_T

#define M23_A0_IP_CTRL_CPU_BASE                  0xCA211000
#define M23_A0_IP_CTRL_CPU_TYPE                  IP_CTRL_CPU_REG_M23A0_T

#define M23_A0_MCRG_CTRL_CPU_BASE                0xCA220000
#define M23_A0_MCRG_CTRL_CPU_TYPE                MCRG_CTRL_CPU_REG_M23A0_T

#define M23_A0_BCRG_CTRL_CPU_BASE                0xCA221000
#define M23_A0_BCRG_CTRL_CPU_TYPE                BCRG_CTRL_CPU_REG_M23A0_T

#define M23_A0_BND_CTRL_CPU_BASE                 0xCA222000
#define M23_A0_BND_CTRL_CPU_TYPE                 BND_CTRL_CPU_REG_M23A0_T

#define M23_A0_PVMCON_CPU_BASE                   0xCA223000
#define M23_A0_PVMCON_CPU_TYPE                   PVMCON_CPU_REG_M23A0_T

#define M23_A0_CPU_SCRG_CTRL_VMCU_BASE           0xCABF0000
#define M23_A0_CPU_SCRG_CTRL_VMCU_TYPE           CPU_SCRG_CTRL_VMCU_REG_M23A0_T

#define M23_A0_CPU_SCRG_CTRL_PMCU_BASE           0xCAD00000
#define M23_A0_CPU_SCRG_CTRL_PMCU_TYPE           CPU_SCRG_CTRL_PMCU_REG_M23A0_T

#define M23_A0_SCRG_CTRL_LED_BASE                0xCC440000
#define M23_A0_SCRG_CTRL_LED_TYPE                SCRG_CTRL_LED_REG_M23A0_T

#define M23_A0_IP_CTRL_LED_BASE                  0xCC441000
#define M23_A0_IP_CTRL_LED_TYPE                  IP_CTRL_LED_REG_M23A0_T

#define M23_A0_SCRG_CTRL_TCON_BASE               0xCC480000
#define M23_A0_SCRG_CTRL_TCON_TYPE               SCRG_CTRL_TCON_REG_M23A0_T

#define M23_A0_IP_CTRL_TCON_BASE                 0xCC481000
#define M23_A0_IP_CTRL_TCON_TYPE                 IP_CTRL_TCON_REG_M23A0_T

#define M23_A0_SCRG_CTRL_CCO_BASE                0xCC4C0000
#define M23_A0_SCRG_CTRL_CCO_TYPE                SCRG_CTRL_CCO_REG_M23A0_T

#define M23_A0_IP_CTRL_CCO_BASE                  0xCC4C1000
#define M23_A0_IP_CTRL_CCO_TYPE                  IP_CTRL_CCO_REG_M23A0_T

#define M23_A0_SCRG_CTRL_VSD_BASE                0xCC500000
#define M23_A0_SCRG_CTRL_VSD_TYPE                SCRG_CTRL_VSD_REG_M23A0_T

#define M23_A0_IP_CTRL_VSD_BASE                  0xCC501000
#define M23_A0_IP_CTRL_VSD_TYPE                  IP_CTRL_VSD_REG_M23A0_T

#define M23_A0_MCRG_CTRL_DPE_BASE                0xCC530000
#define M23_A0_MCRG_CTRL_DPE_TYPE                MCRG_CTRL_DPE_REG_M23A0_T

#define M23_A0_BCRG_CTRL_DPE_BASE                0xCC531000
#define M23_A0_BCRG_CTRL_DPE_TYPE                BCRG_CTRL_DPE_REG_M23A0_T

#define M23_A0_MIP_CTRL_C4TX_BASE                0xCC532000
#define M23_A0_MIP_CTRL_C4TX_TYPE                MIP_CTRL_C4TX_REG_M23A0_T

#define M23_A0_SCRG_CTRL_SRE_BASE                0xCC580000
#define M23_A0_SCRG_CTRL_SRE_TYPE                SCRG_CTRL_SRE_REG_M23A0_T

#define M23_A0_IP_CTRL_SRE_BASE                  0xCC581000
#define M23_A0_IP_CTRL_SRE_TYPE                  IP_CTRL_SRE_REG_M23A0_T

#define M23_A0_SCRG_CTRL_ND_BASE                 0xCC5C0000
#define M23_A0_SCRG_CTRL_ND_TYPE                 SCRG_CTRL_ND_REG_M23A0_T

#define M23_A0_IP_CTRL_ND_BASE                   0xCC5C1000
#define M23_A0_IP_CTRL_ND_TYPE                   IP_CTRL_ND_REG_M23A0_T

#define M23_A0_SCRG_CTRL_CVBSB_BASE              0xCC5E0000
#define M23_A0_SCRG_CTRL_CVBSB_TYPE              SCRG_CTRL_CVBSB_REG_M23A0_T

#define M23_A0_SCRG_CTRL_HDR_BASE                0xCC630000
#define M23_A0_SCRG_CTRL_HDR_TYPE                SCRG_CTRL_HDR_REG_M23A0_T

#define M23_A0_IP_CTRL_HDR_BASE                  0xCC631000
#define M23_A0_IP_CTRL_HDR_TYPE                  IP_CTRL_HDR_REG_M23A0_T

#define M23_A0_MCRG_CTRL_ND0_BASE                0xCC660000
#define M23_A0_MCRG_CTRL_ND0_TYPE                MCRG_CTRL_ND0_REG_M23A0_T

#define M23_A0_BCRG_CTRL_ND0_BASE                0xCC661000
#define M23_A0_BCRG_CTRL_ND0_TYPE                BCRG_CTRL_ND0_REG_M23A0_T

#define M23_A0_BND_CTRL_ND0_BASE                 0xCC662000
#define M23_A0_BND_CTRL_ND0_TYPE                 BND_CTRL_ND0_REG_M23A0_T

#define M23_A0_SCRG_CTRL_CVI_BASE                0xCC6A0000
#define M23_A0_SCRG_CTRL_CVI_TYPE                SCRG_CTRL_CVI_REG_M23A0_T

#define M23_A0_IP_CTRL_CVI_BASE                  0xCC6A1000
#define M23_A0_IP_CTRL_CVI_TYPE                  IP_CTRL_CVI_REG_M23A0_T

#define M23_A0_SCRG_CTRL_IMX_BASE                0xCC6E0000
#define M23_A0_SCRG_CTRL_IMX_TYPE                SCRG_CTRL_IMX_REG_M23A0_T

#define M23_A0_IP_CTRL_IMX_BASE                  0xCC6E1000
#define M23_A0_IP_CTRL_IMX_TYPE                  IP_CTRL_IMX_REG_M23A0_T

#define M23_A0_SCRG_CTRL_VDO_BASE                0xCC720000
#define M23_A0_SCRG_CTRL_VDO_TYPE                SCRG_CTRL_VDO_REG_M23A0_T

#define M23_A0_IP_CTRL_VDO_BASE                  0xCC721000
#define M23_A0_IP_CTRL_VDO_TYPE                  IP_CTRL_VDO_REG_M23A0_T

#define M23_A0_MCRG_CTRL_CVI_BASE                0xCC750000
#define M23_A0_MCRG_CTRL_CVI_TYPE                MCRG_CTRL_CVI_REG_M23A0_T

#define M23_A0_BCRG_CTRL_CVI_BASE                0xCC751000
#define M23_A0_BCRG_CTRL_CVI_TYPE                BCRG_CTRL_CVI_REG_M23A0_T

#define M23_A0_BND_CTRL_CVI_BASE                 0xCC752000
#define M23_A0_BND_CTRL_CVI_TYPE                 BND_CTRL_CVI_REG_M23A0_T

#define M23_A0_MIP_CTRL_EARC_BASE                0xCC753000
#define M23_A0_MIP_CTRL_EARC_TYPE                MIP_CTRL_EARC_REG_M23A0_T

#define M23_A0_SCRG_CTRL_DNE_BASE                0xCC780000
#define M23_A0_SCRG_CTRL_DNE_TYPE                SCRG_CTRL_DNE_REG_M23A0_T

#define M23_A0_IP_CTRL_DNE_BASE                  0xCC781000
#define M23_A0_IP_CTRL_DNE_TYPE                  IP_CTRL_DNE_REG_M23A0_T

#define M23_A0_MCRG_CTRL_BUS_BASE                0xCC7A0000
#define M23_A0_MCRG_CTRL_BUS_TYPE                MCRG_CTRL_BUS_REG_M23A0_T

#define M23_A0_BCRG_CTRL_BUS_BASE                0xCC7A1000
#define M23_A0_BCRG_CTRL_BUS_TYPE                BCRG_CTRL_BUS_REG_M23A0_T

#define M23_A0_SCRG_CTRL_GSC_BASE                0xCC840000
#define M23_A0_SCRG_CTRL_GSC_TYPE                SCRG_CTRL_GSC_REG_M23A0_T

#define M23_A0_IP_CTRL_GSC_BASE                  0xCC841000
#define M23_A0_IP_CTRL_GSC_TYPE                  IP_CTRL_GSC_REG_M23A0_T

#define M23_A0_SCRG_CTRL_LNE_BASE                0xCC880000
#define M23_A0_SCRG_CTRL_LNE_TYPE                SCRG_CTRL_LNE_REG_M23A0_T

#define M23_A0_SCRG_CTRL_FMC_BASE                0xCC8F0000
#define M23_A0_SCRG_CTRL_FMC_TYPE                SCRG_CTRL_FMC_REG_M23A0_T

#define M23_A0_IP_CTRL_FMC_BASE                  0xCC8F1000
#define M23_A0_IP_CTRL_FMC_TYPE                  IP_CTRL_FMC_REG_M23A0_T

#define M23_A0_MCRG_CTRL_FMC_BASE                0xCC920000
#define M23_A0_MCRG_CTRL_FMC_TYPE                MCRG_CTRL_FMC_REG_M23A0_T

#define M23_A0_BCRG_CTRL_FMC_BASE                0xCC921000
#define M23_A0_BCRG_CTRL_FMC_TYPE                BCRG_CTRL_FMC_REG_M23A0_T

#define M23_A0_CRG_TOP_CTRL_BASE                 0xCC922000
#define M23_A0_CRG_TOP_CTRL_TYPE                 CRG_TOP_CTRL_REG_M23A0_T

#define M23_A0_BND_CTRL_FMC_BASE                 0xCC923000
#define M23_A0_BND_CTRL_FMC_TYPE                 BND_CTRL_FMC_REG_M23A0_T

#define M23_A0_MIP_TSADC_CTRL_BASE               0xCC924000
#define M23_A0_MIP_TSADC_CTRL_TYPE               MIP_TSADC_CTRL_REG_M23A0_T

#define M23_A0_SCRG_CTRL_FMS_BASE                0xCC960000
#define M23_A0_SCRG_CTRL_FMS_TYPE                SCRG_CTRL_FMS_REG_M23A0_T

#define M23_A0_IP_CTRL_FMS_BASE                  0xCC961000
#define M23_A0_IP_CTRL_FMS_TYPE                  IP_CTRL_FMS_REG_M23A0_T

#define M23_A0_MCRG_CTRL_FMS_BASE                0xCC990000
#define M23_A0_MCRG_CTRL_FMS_TYPE                MCRG_CTRL_FMS_REG_M23A0_T

#define M23_A0_BCRG_CTRL_FMS_BASE                0xCC991000
#define M23_A0_BCRG_CTRL_FMS_TYPE                BCRG_CTRL_FMS_REG_M23A0_T

#define M23_A0_BND_CTRL_FMS_BASE                 0xCC992000
#define M23_A0_BND_CTRL_FMS_TYPE                 BND_CTRL_FMS_REG_M23A0_T

#define M23_A0_SCRG_CTRL_ME_BASE                 0xCC9D0000
#define M23_A0_SCRG_CTRL_ME_TYPE                 SCRG_CTRL_ME_REG_M23A0_T

#define M23_A0_IP_CTRL_ME_BASE                   0xCC9D1000
#define M23_A0_IP_CTRL_ME_TYPE                   IP_CTRL_ME_REG_M23A0_T

#define M23_A0_MCRG_CTRL_ME0_BASE                0xCCA00000
#define M23_A0_MCRG_CTRL_ME0_TYPE                MCRG_CTRL_ME0_REG_M23A0_T

#define M23_A0_BCRG_CTRL_ME0_BASE                0xCCA01000
#define M23_A0_BCRG_CTRL_ME0_TYPE                BCRG_CTRL_ME0_REG_M23A0_T

#define M23_A0_BND_CTRL_ME0_BASE                 0xCCA02000
#define M23_A0_BND_CTRL_ME0_TYPE                 BND_CTRL_ME0_REG_M23A0_T

#define M23_A0_SCRG_CTRL_VD1_BASE                0xCE510000
#define M23_A0_SCRG_CTRL_VD1_TYPE                SCRG_CTRL_VD1_REG_M23A0_T

#define M23_A0_MCRG_CTRL_VD1_BASE                0xCE520000
#define M23_A0_MCRG_CTRL_VD1_TYPE                MCRG_CTRL_VD1_REG_M23A0_T

#define M23_A0_BCRG_CTRL_VD1_BASE                0xCE521000
#define M23_A0_BCRG_CTRL_VD1_TYPE                BCRG_CTRL_VD1_REG_M23A0_T

#define M23_A0_IOMUX_CTRL_VD1_BASE               0xCE522000
#define M23_A0_IOMUX_CTRL_VD1_TYPE               IOMUX_CTRL_VD1_REG_M23A0_T

#define M23_A0_SCRG_CTRL_VD0_BASE                0xCE670000
#define M23_A0_SCRG_CTRL_VD0_TYPE                SCRG_CTRL_VD0_REG_M23A0_T

#define M23_A0_MCRG_CTRL_VD0_BASE                0xCE690000
#define M23_A0_MCRG_CTRL_VD0_TYPE                MCRG_CTRL_VD0_REG_M23A0_T

#define M23_A0_BCRG_CTRL_VD0_BASE                0xCE691000
#define M23_A0_BCRG_CTRL_VD0_TYPE                BCRG_CTRL_VD0_REG_M23A0_T

#define M23_A0_IOMUX_CTRL_VD0_BASE               0xCE692000
#define M23_A0_IOMUX_CTRL_VD0_TYPE               IOMUX_CTRL_VD0_REG_M23A0_T

#define M23_A0_SCRG_CTRL_ICOD_BASE               0xCEC40000
#define M23_A0_SCRG_CTRL_ICOD_TYPE               SCRG_CTRL_ICOD_REG_M23A0_T

#define M23_A0_SCRG_CTRL_VENC_BASE               0xCEC80000
#define M23_A0_SCRG_CTRL_VENC_TYPE               SCRG_CTRL_VENC_REG_M23A0_T

#define M23_A0_MCRG_CTRL_AUD_BASE                0xCECB0000
#define M23_A0_MCRG_CTRL_AUD_TYPE                MCRG_CTRL_AUD_REG_M23A0_T

#define M23_A0_BCRG_CTRL_AUD_BASE                0xCECB1000
#define M23_A0_BCRG_CTRL_AUD_TYPE                BCRG_CTRL_AUD_REG_M23A0_T

#define M23_A0_BND_CTRL_AUD_BASE                 0xCECB2000
#define M23_A0_BND_CTRL_AUD_TYPE                 BND_CTRL_AUD_REG_M23A0_T

#define M23_A0_TMUX_CTRL_BASE                    0xCECB3000
#define M23_A0_TMUX_CTRL_TYPE                    TMUX_CTRL_REG_M23A0_T

#define M23_A0_SCRG_CTRL_AUD_BASE                0xCED10000
#define M23_A0_SCRG_CTRL_AUD_TYPE                SCRG_CTRL_AUD_REG_M23A0_T

#define M23_A0_IP_CTRL_AUD_BASE                  0xCED11000
#define M23_A0_IP_CTRL_AUD_TYPE                  IP_CTRL_AUD_REG_M23A0_T

#define M23_A0_SCRG_CTRL_TE_BASE                 0xCED40000
#define M23_A0_SCRG_CTRL_TE_TYPE                 SCRG_CTRL_TE_REG_M23A0_T

#define M23_A0_IP_CTRL_TE_BASE                   0xCED41000
#define M23_A0_IP_CTRL_TE_TYPE                   IP_CTRL_TE_REG_M23A0_T

#define M23_A0_SCRG_CTRL_TIVSB_BASE              0xCED70000
#define M23_A0_SCRG_CTRL_TIVSB_TYPE              SCRG_CTRL_TIVSB_REG_M23A0_T

#define M23_A0_SCRG_CTRL_EDID1_BASE              0xF3110000
#define M23_A0_SCRG_CTRL_EDID1_TYPE              SCRG_CTRL_EDID1_REG_M23A0_T

#define M23_A0_IP_CTRL_EDID1_BASE                0xF3111000
#define M23_A0_IP_CTRL_EDID1_TYPE                IP_CTRL_EDID1_REG_M23A0_T

#define M23_A0_SCRG_CTRL_EPHY_BASE               0xF3150000
#define M23_A0_SCRG_CTRL_EPHY_TYPE               SCRG_CTRL_EPHY_REG_M23A0_T

#define M23_A0_SCRG_CTRL_PDM_BASE                0xF3170000
#define M23_A0_SCRG_CTRL_PDM_TYPE                SCRG_CTRL_PDM_REG_M23A0_T

#define M23_A0_CPU_BND_CTRL_WOC_BASE             0xC8512000
#define M23_A0_CPU_BND_CTRL_WOC_TYPE             MICOM_BND_CTRL_WOC_REG_M23A0_T
#define M23_A0_MICOM_BND_CTRL_WOC_BASE           0xF3512000
#define M23_A0_MICOM_BND_CTRL_WOC_TYPE           MICOM_BND_CTRL_WOC_REG_M23A0_T

#define M23_A0_CPU_POWER_CTRL_BASE               0xC8513000
#define M23_A0_CPU_POWER_CTRL_TYPE               MICOM_POWER_CTRL_REG_M23A0_T
#define M23_A0_MICOM_POWER_CTRL_BASE             0xF3513000
#define M23_A0_MICOM_POWER_CTRL_TYPE             MICOM_POWER_CTRL_REG_M23A0_T

#define M23_A0_CPU_CRG_TOP_WOC_CTRL_BASE         0xC8514000
#define M23_A0_CPU_CRG_TOP_WOC_CTRL_TYPE         MICOM_CRG_TOP_WOC_CTRL_REG_M23A0_T
#define M23_A0_MICOM_CRG_TOP_WOC_CTRL_BASE       0xF3514000
#define M23_A0_MICOM_CRG_TOP_WOC_CTRL_TYPE       MICOM_CRG_TOP_WOC_CTRL_REG_M23A0_T

#define M23_A0_MIP_CTRL_DPM_BASE                 0xF3516000
#define M23_A0_MIP_CTRL_DPM_TYPE                 MIP_CTRL_DPM_REG_M23A0_T


#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_O22_A0_H__ */

