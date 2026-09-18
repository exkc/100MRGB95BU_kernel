#ifndef __CTOP_CTRL_REG_O26_A0_H__
#define __CTOP_CTRL_REG_O26_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
// TODO: O26_Adapter_Register_Manual

#include "o26a0/ctop_syn/bnd_ctrl_hdmi.h"
#include "o26a0/ctop_syn/bnd_ctrl_lnx1.h"
#include "o26a0/ctop_syn/bnd_ctrl_cpu.h"
#include "o26a0/ctop_syn/micom_pw_ctrl.h"
#include "o26a0/ctop_syn/bnd_ctrl_hdr.h"
#include "o26a0/ctop_syn/bnd_ctrl_aud.h"
#include "o26a0/ctop_syn/bnd_ctrl_lnx0.h"
#include "o26a0/ctop_syn/trg_ctrl.h"
#include "o26a0/ctop_syn/bnd_ctrl_fmc.h"
#include "o26a0/ctop_syn/bnd_ctrl_emmc.h"
#include "o26a0/ctop_syn/bnd_ctrl_m0.h"
#include "o26a0/ctop_syn/bnd_ctrl_nd1.h"
#include "o26a0/ctop_syn/bnd_ctrl_lnx2.h"
#include "o26a0/ctop_syn/bnd_ctrl_sre.h"
#include "o26a0/ctop_syn/bnd_ctrl_nd0.h"
#include "o26a0/ctop_syn/bnd_ctrl_m1.h"
#include "o26a0/ctop_syn/drg_ctrl.h"
#include "o26a0/ctop_syn/bnd_ctrl_gsc.h"
#include "o26a0/ctop_syn/bnd_ctrl_lbm.h"
#include "o26a0/ctop_syn/bnd_ctrl_me0.h"
#include "o26a0/ctop_syn/bnd_ctrl_vd0.h"
#include "o26a0/ctop_syn/bnd_ctrl_imx.h"
#include "o26a0/ctop_syn/micom_crg_top_woc_ctrl.h"
#include "o26a0/ctop_syn/bnd_ctrl_me1.h"
#include "o26a0/ctop_syn/bnd_ctrl_cco.h"
#include "o26a0/ctop_syn/bnd_ctrl_dnsr.h"
#include "o26a0/ctop_syn/bnd_ctrl_venc.h"
#include "o26a0/ctop_syn/bnd_ctrl_dpe.h"
#include "o26a0/ctop_syn/bnd_ctrl_bmc.h"
#include "o26a0/ctop_syn/bnd_ctrl_fms.h"
#include "o26a0/ctop_syn/tmux_ctrl.h"
#include "o26a0/ctop_syn/bnd_ctrl_woc.h"
#include "o26a0/ctop_syn/mip_dig_ctrl.h"

#include "o26a0/ctop_crc/crc_tout.h"
#include "o26a0/ctop_crc/crc_vout.h"

#include "o26a0/ctop_mip/mip_ctrl_c4tx16.h"
#include "o26a0/ctop_mip/mip_ctrl_hdmi1.h"
#include "o26a0/ctop_mip/mip_ctrl_admd_mip.h"
#include "o26a0/ctop_mip/mip_ctrl_cvbsafe.h"
#include "o26a0/ctop_mip/mip_ctrl_hdmi3.h"
#include "o26a0/ctop_mip/mip_ctrl_hdmi2.h"
#include "o26a0/ctop_mip/mip_ctrl_acodec.h"
#include "o26a0/ctop_mip/mip_ctrl_hdmi_earc.h"
#include "o26a0/ctop_mip/mip_ctrl_tsadc.h"
#include "o26a0/ctop_mip/mip_ctrl_hdmi_dpm.h"
#include "o26a0/ctop_mip/mip_ctrl_hdmi4.h"

#include "o26a0/ctop_pad/iomux_ctrl_woc.h"
#include "o26a0/ctop_pad/iomux_ctrl_dpe.h"
#include "o26a0/ctop_pad/iomux_ctrl_me1.h"
#include "o26a0/ctop_pad/iomux_ctrl_hdmi.h"
#include "o26a0/ctop_pad/iomux_ctrl_aud.h"
#include "o26a0/ctop_pad/iomux_ctrl_lnx2.h"

#include "o26a0/ctop_ipw/ip_ctrl_hdr.h"
#include "o26a0/ctop_ipw/ip_ctrl_aud.h"
#include "o26a0/ctop_ipw/ip_ctrl_fmc.h"
#include "o26a0/ctop_ipw/ip_ctrl_npp.h"
#include "o26a0/ctop_ipw/ip_ctrl_dbb.h"
#include "o26a0/ctop_ipw/ip_ctrl_cpu.h"
#include "o26a0/ctop_ipw/ip_ctrl_cvi.h"
#include "o26a0/ctop_ipw/ip_ctrl_dsc.h"
#include "o26a0/ctop_ipw/ip_ctrl_lnx1.h"
#include "o26a0/ctop_ipw/ip_ctrl_nd0.h"
#include "o26a0/ctop_ipw/ip_ctrl_hdmi.h"
#include "o26a0/ctop_ipw/ip_ctrl_nd1.h"
#include "o26a0/ctop_ipw/ip_ctrl_lbus.h"
#include "o26a0/ctop_ipw/ip_ctrl_lnx0.h"
#include "o26a0/ctop_ipw/ip_ctrl_edptx.h"
#include "o26a0/ctop_ipw/ip_ctrl_sre.h"
#include "o26a0/ctop_ipw/ip_ctrl_me1.h"
#include "o26a0/ctop_ipw/ip_ctrl_cco.h"
#include "o26a0/ctop_ipw/ip_ctrl_gsc.h"
#include "o26a0/ctop_ipw/ip_ctrl_led.h"
#include "o26a0/ctop_ipw/ip_ctrl_me0.h"
#include "o26a0/ctop_ipw/ip_ctrl_tcon.h"
#include "o26a0/ctop_ipw/ip_ctrl_imx.h"
#include "o26a0/ctop_ipw/ip_ctrl_fms.h"
#include "o26a0/ctop_ipw/cpu_ip_ctrl_edid.h"
#include "o26a0/ctop_ipw/ip_ctrl_vdo.h"
#include "o26a0/ctop_ipw/ip_ctrl_vsd.h"
#include "o26a0/ctop_ipw/ip_ctrl_te.h"

#include "o26a0/fsc_con/fsc_ctrl_aud_o26a0.h"

#include "o26a0/crg_sub/scrg_ctrl_dbb.h"
#include "o26a0/crg_sub/mcrg_ctrl_nd0.h"
#include "o26a0/crg_sub/scrg_ctrl_tcon.h"
#include "o26a0/crg_sub/bcrg_ctrl_nd1.h"
#include "o26a0/crg_sub/bcrg_ctrl_lnx0.h"
#include "o26a0/crg_sub/scrg_ctrl_lb0sb.h"
#include "o26a0/crg_sub/bcrg_ctrl_m1.h"
#include "o26a0/crg_sub/scrg_ctrl_cvi.h"
#include "o26a0/crg_sub/scrg_ctrl_usbsb.h"
#include "o26a0/crg_sub/scrg_ctrl_icod.h"
#include "o26a0/crg_sub/scrg_ctrl_cpu.h"
#include "o26a0/crg_sub/bcrg_ctrl_sre.h"
#include "o26a0/crg_sub/scrg_ctrl_aud.h"
#include "o26a0/crg_sub/mcrg_ctrl_sre.h"
#include "o26a0/crg_sub/mcrg_ctrl_venc.h"
#include "o26a0/crg_sub/mcrg_ctrl_dnsr.h"
#include "o26a0/crg_sub/bcrg_ctrl_hdmi.h"
#include "o26a0/crg_sub/scrg_ctrl_hdr.h"
#include "o26a0/crg_sub/scrg_ctrl_dnsr.h"
#include "o26a0/crg_sub/scrg_ctrl_venc.h"
#include "o26a0/crg_sub/scrg_ctrl_npp.h"
#include "o26a0/crg_sub/bcrg_ctrl_m0.h"
#include "o26a0/crg_sub/scrg_ctrl_tivvmsb.h"
#include "o26a0/crg_sub/scrg_ctrl_iommu.h"
#include "o26a0/crg_sub/scrg_ctrl_fmc.h"
#include "o26a0/crg_sub/pmcu_scrg_ctrl_pmcu.h"
#include "o26a0/crg_sub/bcrg_ctrl_lnx1.h"
#include "o26a0/crg_sub/scrg_ctrl_dmcu.h"
#include "o26a0/crg_sub/scrg_ctrl_te.h"
#include "o26a0/crg_sub/bcrg_ctrl_nd0.h"
#include "o26a0/crg_sub/mcrg_ctrl_nd1.h"
#include "o26a0/crg_sub/mcrg_ctrl_fmc.h"
#include "o26a0/crg_sub/scrg_ctrl_fmesb.h"
#include "o26a0/crg_sub/mcrg_ctrl_m1.h"
#include "o26a0/crg_sub/scrg_ctrl_nd1.h"
#include "o26a0/crg_sub/scrg_ctrl_gfx.h"
#include "o26a0/crg_sub/scrg_ctrl_lb1sb.h"
#include "o26a0/crg_sub/mcrg_ctrl_hdr.h"
#include "o26a0/crg_sub/mcrg_ctrl_aud.h"
#include "o26a0/crg_sub/scrg_ctrl_sre.h"
#include "o26a0/crg_sub/bcrg_ctrl_cpu.h"
#include "o26a0/crg_sub/vmcu_scrg_ctrl_vmcu.h"
#include "o26a0/crg_sub/mcrg_ctrl_cpu.h"
#include "o26a0/crg_sub/bcrg_ctrl_aud.h"
#include "o26a0/crg_sub/bcrg_ctrl_hdr.h"
#include "o26a0/crg_sub/bcrg_ctrl_emmc.h"
#include "o26a0/crg_sub/scrg_ctrl_dsc.h"
#include "o26a0/crg_sub/micom_scrg_ctrl_ion0.h"
#include "o26a0/crg_sub/scrg_ctrl_usb_ss.h"
#include "o26a0/crg_sub/scrg_ctrl_nd0.h"
#include "o26a0/crg_sub/mcrg_ctrl_m0.h"
#include "o26a0/crg_sub/bcrg_ctrl_lnx2.h"
#include "o26a0/crg_sub/bcrg_ctrl_fmc.h"
#include "o26a0/crg_sub/scrg_ctrl_me0.h"
#include "o26a0/crg_sub/scrg_ctrl_vd0.h"
#include "o26a0/crg_sub/scrg_ctrl_led.h"
#include "o26a0/crg_sub/scrg_ctrl_emusb.h"
#include "o26a0/crg_sub/scrg_ctrl_gsc.h"
#include "o26a0/crg_sub/bcrg_ctrl_dpe.h"
#include "o26a0/crg_sub/mcrg_ctrl_fms.h"
#include "o26a0/crg_sub/scrg_ctrl_imx.h"
#include "o26a0/crg_sub/scrg_ctrl_ddr0sb.h"
#include "o26a0/crg_sub/scrg_ctrl_ddr1sb.h"
#include "o26a0/crg_sub/micom_bcrg_ctrl_woc.h"
#include "o26a0/crg_sub/bcrg_ctrl_bmc.h"
#include "o26a0/crg_sub/mcrg_ctrl_bmc.h"
#include "o26a0/crg_sub/mcrg_ctrl_emmc.h"
#include "o26a0/crg_sub/micom_mcrg_ctrl_woc.h"
#include "o26a0/crg_sub/bcrg_ctrl_fms.h"
#include "o26a0/crg_sub/scrg_ctrl_emmc.h"
#include "o26a0/crg_sub/scrg_ctrl_cco.h"
#include "o26a0/crg_sub/mcrg_ctrl_dpe.h"
#include "o26a0/crg_sub/mcrg_ctrl_lnx2.h"
#include "o26a0/crg_sub/scrg_ctrl_vd1.h"
#include "o26a0/crg_sub/scrg_ctrl_me1.h"
#include "o26a0/crg_sub/scrg_ctrl_lnx2.h"
#include "o26a0/crg_sub/scrg_ctrl_lbus.h"
#include "o26a0/crg_sub/scrg_ctrl_lnx0.h"
#include "o26a0/crg_sub/scrg_ctrl_tivsb.h"
#include "o26a0/crg_sub/bcrg_ctrl_me0.h"
#include "o26a0/crg_sub/bcrg_ctrl_lbm.h"
#include "o26a0/crg_sub/mcrg_ctrl_vd1.h"
#include "o26a0/crg_sub/mcrg_ctrl_me1.h"
#include "o26a0/crg_sub/bcrg_ctrl_vd0.h"
#include "o26a0/crg_sub/scrg_ctrl_vsd.h"
#include "o26a0/crg_sub/mcrg_ctrl_lnx0.h"
#include "o26a0/crg_sub/mcrg_ctrl_cco.h"
#include "o26a0/crg_sub/bcrg_ctrl_gsc.h"
#include "o26a0/crg_sub/scrg_ctrl_srcosb.h"
#include "o26a0/crg_sub/bcrg_ctrl_imx.h"
#include "o26a0/crg_sub/scrg_ctrl_ion1.h"
#include "o26a0/crg_sub/scrg_ctrl_m1.h"
#include "o26a0/crg_sub/micom_scrg_ctrl_ephy.h"
#include "o26a0/crg_sub/scrg_ctrl_m0.h"
#include "o26a0/crg_sub/mcrg_ctrl_hdmi.h"
#include "o26a0/crg_sub/bcrg_ctrl_dnsr.h"
#include "o26a0/crg_sub/bcrg_ctrl_venc.h"
#include "o26a0/crg_sub/scrg_ctrl_hdmi.h"
#include "o26a0/crg_sub/micom_scrg_ctrl_micom.h"
#include "o26a0/crg_sub/scrg_ctrl_fms.h"
#include "o26a0/crg_sub/scrg_ctrl_edptx.h"
#include "o26a0/crg_sub/mcrg_ctrl_imx.h"
#include "o26a0/crg_sub/micom_scrg_ctrl_edid.h"
#include "o26a0/crg_sub/scrg_ctrl_vdo.h"
#include "o26a0/crg_sub/mcrg_ctrl_gsc.h"
#include "o26a0/crg_sub/scrg_ctrl_usb_hs3.h"
#include "o26a0/crg_sub/scrg_ctrl_usb_hs2.h"
#include "o26a0/crg_sub/scrg_ctrl_usb_hs1.h"
#include "o26a0/crg_sub/bcrg_ctrl_cco.h"
#include "o26a0/crg_sub/mcrg_ctrl_lnx1.h"
#include "o26a0/crg_sub/mcrg_ctrl_me0.h"
#include "o26a0/crg_sub/bcrg_ctrl_vd1.h"
#include "o26a0/crg_sub/mcrg_ctrl_lbm.h"
#include "o26a0/crg_sub/bcrg_ctrl_me1.h"
#include "o26a0/crg_sub/mcrg_ctrl_vd0.h"
#include "o26a0/crg_sub/scrg_ctrl_gpu.h"
#include "o26a0/crg_sub/scrg_ctrl_lnx1.h"
#include "o26a0/ion/ion_top_ctrl.h"
#include "o26a0/ion/func_iomux_ion0_core.h"
#include "o26a0/ion/func_iomux_ion0_pad.h"
#include "o26a0/ion/func_iomux_ion1_core.h"
#include "o26a0/ion/func_iomux_ion1_pad.h"
#include "o26a0/ion/srds12to3.h"
#include "o26a0/ion/srds32to1.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    BND_CTRL_HDMI_REG_O26A0_T*       BND_CTRL_HDMI;
    BND_CTRL_LNX1_REG_O26A0_T*       BND_CTRL_LNX1;
    BND_CTRL_CPU_REG_O26A0_T*        BND_CTRL_CPU;
    MICOM_PW_CTRL_REG_O26A0_T*       CPU_PW_CTRL;   // CPU
    MICOM_PW_CTRL_REG_O26A0_T*       PMCU_PW_CTRL;  // PMCU
    MICOM_PW_CTRL_REG_O26A0_T*       VMCU_PW_CTRL;  // VMCU
    MICOM_PW_CTRL_REG_O26A0_T*       MICOM_PW_CTRL; // MICOM
    BND_CTRL_HDR_REG_O26A0_T*        BND_CTRL_HDR;
    BND_CTRL_AUD_REG_O26A0_T*        BND_CTRL_AUD;
    BND_CTRL_LNX0_REG_O26A0_T*       BND_CTRL_LNX0;
    TRG_CTRL_REG_O26A0_T*            TRG_CTRL;
    BND_CTRL_FMC_REG_O26A0_T*        BND_CTRL_FMC;
    BND_CTRL_EMMC_REG_O26A0_T*       BND_CTRL_EMMC;
    BND_CTRL_M0_REG_O26A0_T*         BND_CTRL_M0;
    BND_CTRL_ND1_REG_O26A0_T*        BND_CTRL_ND1;
    BND_CTRL_LNX2_REG_O26A0_T*       BND_CTRL_LNX2;
    BND_CTRL_SRE_REG_O26A0_T*        BND_CTRL_SRE;
    BND_CTRL_ND0_REG_O26A0_T*        BND_CTRL_ND0;
    BND_CTRL_M1_REG_O26A0_T*         BND_CTRL_M1;
    DRG_CTRL_REG_O26A0_T*            DRG_CTRL;
    BND_CTRL_GSC_REG_O26A0_T*        BND_CTRL_GSC;
    BND_CTRL_LBM_REG_O26A0_T*        BND_CTRL_LBM;
    BND_CTRL_ME0_REG_O26A0_T*        BND_CTRL_ME0;
    BND_CTRL_VD0_REG_O26A0_T*        BND_CTRL_VD0;
    BND_CTRL_IMX_REG_O26A0_T*        BND_CTRL_IMX;
    MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T* CPU_CRG_TOP_WOC_CTRL;   // CPU
    MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T* PMCU_CRG_TOP_WOC_CTRL;  // PMCU
    MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T* VMCU_CRG_TOP_WOC_CTRL;  // VMCU
    MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T* MICOM_CRG_TOP_WOC_CTRL; // MICOM
    BND_CTRL_ME1_REG_O26A0_T*        BND_CTRL_ME1;
    BND_CTRL_CCO_REG_O26A0_T*        BND_CTRL_CCO;
    BND_CTRL_DNSR_REG_O26A0_T*       BND_CTRL_DNSR;
    BND_CTRL_VENC_REG_O26A0_T*       BND_CTRL_VENC;
    BND_CTRL_DPE_REG_O26A0_T*        BND_CTRL_DPE;
    BND_CTRL_BMC_REG_O26A0_T*        BND_CTRL_BMC;
    BND_CTRL_FMS_REG_O26A0_T*        BND_CTRL_FMS;
    TMUX_CTRL_REG_O26A0_T*           TMUX_CTRL;
    BND_CTRL_WOC_REG_O26A0_T*        CPU_BND_CTRL_WOC;  // CPU
    BND_CTRL_WOC_REG_O26A0_T*        PMCU_BND_CTRL_WOC; // PMCU
    BND_CTRL_WOC_REG_O26A0_T*        VMCU_BND_CTRL_WOC; // VMCU
    BND_CTRL_WOC_REG_O26A0_T*        MICOM_BND_CTRL_WOC;// MICOM
    MIP_DIG_CTRL_REG_O26A0_T*        MIP_DIG_CTRL;

    CRC_TOUT_REG_O26A0_T*            CRC_TOUT;
    CRC_VOUT_REG_O26A0_T*            CRC_VOUT;

    MIP_CTRL_C4TX16_REG_O26A0_T*     MIP_CTRL_C4TX16;
    MIP_CTRL_HDMI1_REG_O26A0_T*      MIP_CTRL_HDMI1;
    MIP_CTRL_ADMD_MIP_REG_O26A0_T*   MIP_CTRL_ADMD_MIP;
    MIP_CTRL_CVBSAFE_REG_O26A0_T*    MIP_CTRL_CVBSAFE;
    MIP_CTRL_HDMI3_REG_O26A0_T*      MIP_CTRL_HDMI3;
    MIP_CTRL_HDMI2_REG_O26A0_T*      MIP_CTRL_HDMI2;
    MIP_CTRL_ACODEC_REG_O26A0_T*     MIP_CTRL_ACODEC;
    MIP_CTRL_HDMI_EARC_REG_O26A0_T*  MIP_CTRL_HDMI_EARC;
    MIP_CTRL_TSADC_REG_O26A0_T*      MIP_CTRL_TSADC;
    MIP_CTRL_HDMI_DPM_REG_O26A0_T*   CPU_MIP_CTRL_HDMI_DPM;   // CPU
    MIP_CTRL_HDMI_DPM_REG_O26A0_T*   PMCU_MIP_CTRL_HDMI_DPM;  // PMCU
    MIP_CTRL_HDMI_DPM_REG_O26A0_T*   VMCU_MIP_CTRL_HDMI_DPM;  // VMCU
    MIP_CTRL_HDMI_DPM_REG_O26A0_T*   MICOM_MIP_CTRL_HDMI_DPM; // MICOM
    MIP_CTRL_HDMI4_REG_O26A0_T*      MIP_CTRL_HDMI4;

    IOMUX_CTRL_WOC_REG_O26A0_T*      CPU_IOMUX_CTRL_WOC;    // CPU
    IOMUX_CTRL_WOC_REG_O26A0_T*      PMCU_IOMUX_CTRL_WOC;   // PMCU
    IOMUX_CTRL_WOC_REG_O26A0_T*      VMCU_IOMUX_CTRL_WOC;   // VMCU
    IOMUX_CTRL_WOC_REG_O26A0_T*      MICOM_IOMUX_CTRL_WOC;  // MICOM
    IOMUX_CTRL_DPE_REG_O26A0_T*      IOMUX_CTRL_DPE;
    IOMUX_CTRL_ME1_REG_O26A0_T*      IOMUX_CTRL_ME1;
    IOMUX_CTRL_HDMI_REG_O26A0_T*     IOMUX_CTRL_HDMI;
    IOMUX_CTRL_AUD_REG_O26A0_T*      IOMUX_CTRL_AUD;
    IOMUX_CTRL_LNX2_REG_O26A0_T*     IOMUX_CTRL_LNX2;
    IP_CTRL_HDR_REG_O26A0_T*         IP_CTRL_HDR;
    IP_CTRL_AUD_REG_O26A0_T*         IP_CTRL_AUD;
    IP_CTRL_FMC_REG_O26A0_T*         IP_CTRL_FMC;
    IP_CTRL_NPP_REG_O26A0_T*         IP_CTRL_NPP;
    IP_CTRL_DBB_REG_O26A0_T*         IP_CTRL_DBB;
    IP_CTRL_CPU_REG_O26A0_T*         IP_CTRL_CPU;
    IP_CTRL_CVI_REG_O26A0_T*         IP_CTRL_CVI;
    IP_CTRL_DSC_REG_O26A0_T*         IP_CTRL_DSC;
    IP_CTRL_LNX1_REG_O26A0_T*        IP_CTRL_LNX1;
    IP_CTRL_ND0_REG_O26A0_T*         IP_CTRL_ND0;
    IP_CTRL_HDMI_REG_O26A0_T*        IP_CTRL_HDMI;
    IP_CTRL_ND1_REG_O26A0_T*         IP_CTRL_ND1;
    IP_CTRL_LBUS_REG_O26A0_T*        IP_CTRL_LBUS;
    IP_CTRL_LNX0_REG_O26A0_T*        IP_CTRL_LNX0;
    IP_CTRL_EDPTX_REG_O26A0_T*       IP_CTRL_EDPTX;
    IP_CTRL_SRE_REG_O26A0_T*         IP_CTRL_SRE;
    IP_CTRL_ME1_REG_O26A0_T*         IP_CTRL_ME1;
    IP_CTRL_CCO_REG_O26A0_T*         IP_CTRL_CCO;
    IP_CTRL_GSC_REG_O26A0_T*         IP_CTRL_GSC;
    IP_CTRL_LED_REG_O26A0_T*         IP_CTRL_LED;
    IP_CTRL_ME0_REG_O26A0_T*         IP_CTRL_ME0;
    IP_CTRL_TCON_REG_O26A0_T*        IP_CTRL_TCON;
    IP_CTRL_IMX_REG_O26A0_T*         IP_CTRL_IMX;
    IP_CTRL_FMS_REG_O26A0_T*         IP_CTRL_FMS;
    CPU_IP_CTRL_EDID_REG_O26A0_T*    CPU_IP_CTRL_EDID;   // CPU
    CPU_IP_CTRL_EDID_REG_O26A0_T*    MICOM_IP_CTRL_EDID; // MICOM
    IP_CTRL_VDO_REG_O26A0_T*         IP_CTRL_VDO;
    IP_CTRL_VSD_REG_O26A0_T*         IP_CTRL_VSD;
    IP_CTRL_TE_REG_O26A0_T*          IP_CTRL_TE;

    FSC_CTRL_AUD_REG_O26A0_T*        FSC_CTRL_AUD;

    SCRG_CTRL_DBB_REG_O26A0_T*       SCRG_CTRL_DBB;
    MCRG_CTRL_ND0_REG_O26A0_T*       MCRG_CTRL_ND0;
    SCRG_CTRL_TCON_REG_O26A0_T*      SCRG_CTRL_TCON;
    BCRG_CTRL_ND1_REG_O26A0_T*       BCRG_CTRL_ND1;
    BCRG_CTRL_LNX0_REG_O26A0_T*      BCRG_CTRL_LNX0;
    SCRG_CTRL_LB0SB_REG_O26A0_T*     SCRG_CTRL_LB0SB;
    BCRG_CTRL_M1_REG_O26A0_T*        BCRG_CTRL_M1;
    SCRG_CTRL_CVI_REG_O26A0_T*       SCRG_CTRL_CVI;
    SCRG_CTRL_USBSB_REG_O26A0_T*     SCRG_CTRL_USBSB;
    SCRG_CTRL_ICOD_REG_O26A0_T*      SCRG_CTRL_ICOD;
    SCRG_CTRL_CPU_REG_O26A0_T*       SCRG_CTRL_CPU;
    BCRG_CTRL_SRE_REG_O26A0_T*       BCRG_CTRL_SRE;
    SCRG_CTRL_AUD_REG_O26A0_T*       SCRG_CTRL_AUD;
    MCRG_CTRL_SRE_REG_O26A0_T*       MCRG_CTRL_SRE;
    MCRG_CTRL_VENC_REG_O26A0_T*      MCRG_CTRL_VENC;
    MCRG_CTRL_DNSR_REG_O26A0_T*      MCRG_CTRL_DNSR;
    BCRG_CTRL_HDMI_REG_O26A0_T*      BCRG_CTRL_HDMI;
    SCRG_CTRL_HDR_REG_O26A0_T*       SCRG_CTRL_HDR;
    SCRG_CTRL_DNSR_REG_O26A0_T*      SCRG_CTRL_DNSR0;
    SCRG_CTRL_DNSR_REG_O26A0_T*      SCRG_CTRL_DNSR1;
    SCRG_CTRL_VENC_REG_O26A0_T*      SCRG_CTRL_VENC;
    SCRG_CTRL_NPP_REG_O26A0_T*       SCRG_CTRL_NPP;
    BCRG_CTRL_M0_REG_O26A0_T*        BCRG_CTRL_M0;
    SCRG_CTRL_TIVVMSB_REG_O26A0_T*   SCRG_CTRL_TIVVMSB;
    SCRG_CTRL_IOMMU_REG_O26A0_T*     SCRG_CTRL_IOMMU;
    SCRG_CTRL_FMC_REG_O26A0_T*       SCRG_CTRL_FMC;
    PMCU_SCRG_CTRL_PMCU_REG_O26A0_T* PMCU_SCRG_CTRL_PMCU;
    BCRG_CTRL_LNX1_REG_O26A0_T*      BCRG_CTRL_LNX1;
    SCRG_CTRL_DMCU_REG_O26A0_T*      SCRG_CTRL_DMCU;
    SCRG_CTRL_TE_REG_O26A0_T*        SCRG_CTRL_TE;
    BCRG_CTRL_ND0_REG_O26A0_T*       BCRG_CTRL_ND0;
    MCRG_CTRL_ND1_REG_O26A0_T*       MCRG_CTRL_ND1;
    MCRG_CTRL_FMC_REG_O26A0_T*       MCRG_CTRL_FMC;
    SCRG_CTRL_FMESB_REG_O26A0_T*     SCRG_CTRL_FMESB;
    MCRG_CTRL_M1_REG_O26A0_T*        MCRG_CTRL_M1;
    SCRG_CTRL_ND1_REG_O26A0_T*       SCRG_CTRL_ND1;
    SCRG_CTRL_GFX_REG_O26A0_T*       SCRG_CTRL_GFX;
    SCRG_CTRL_LB1SB_REG_O26A0_T*     SCRG_CTRL_LB1SB;
    MCRG_CTRL_HDR_REG_O26A0_T*       MCRG_CTRL_HDR;
    MCRG_CTRL_AUD_REG_O26A0_T*       MCRG_CTRL_AUD;
    SCRG_CTRL_SRE_REG_O26A0_T*       SCRG_CTRL_SRE;
    BCRG_CTRL_CPU_REG_O26A0_T*       BCRG_CTRL_CPU;
    VMCU_SCRG_CTRL_VMCU_REG_O26A0_T* VMCU_SCRG_CTRL_VMCU;
    MCRG_CTRL_CPU_REG_O26A0_T*       MCRG_CTRL_CPU;
    BCRG_CTRL_AUD_REG_O26A0_T*       BCRG_CTRL_AUD;
    BCRG_CTRL_HDR_REG_O26A0_T*       BCRG_CTRL_HDR;
    BCRG_CTRL_EMMC_REG_O26A0_T*      BCRG_CTRL_EMMC;
    SCRG_CTRL_DSC_REG_O26A0_T*       SCRG_CTRL_DSC;
    MICOM_SCRG_CTRL_ION0_REG_O26A0_T* CPU_SCRG_CTRL_ION0;  // CPU
    MICOM_SCRG_CTRL_ION0_REG_O26A0_T* MICOM_SCRG_CTRL_ION0;// MICOM
    SCRG_CTRL_USB_SS_REG_O26A0_T*    SCRG_CTRL_USB_SS;
    SCRG_CTRL_ND0_REG_O26A0_T*       SCRG_CTRL_ND0;
    MCRG_CTRL_M0_REG_O26A0_T*        MCRG_CTRL_M0;
    BCRG_CTRL_LNX2_REG_O26A0_T*      BCRG_CTRL_LNX2;
    BCRG_CTRL_FMC_REG_O26A0_T*       BCRG_CTRL_FMC;
    SCRG_CTRL_ME0_REG_O26A0_T*       SCRG_CTRL_ME0;
    SCRG_CTRL_VD0_REG_O26A0_T*       SCRG_CTRL_VD0;
    SCRG_CTRL_LED_REG_O26A0_T*       SCRG_CTRL_LED;
    SCRG_CTRL_EMUSB_REG_O26A0_T*     SCRG_CTRL_EMUSB;
    SCRG_CTRL_GSC_REG_O26A0_T*       SCRG_CTRL_GSC;
    BCRG_CTRL_DPE_REG_O26A0_T*       BCRG_CTRL_DPE;
    MCRG_CTRL_FMS_REG_O26A0_T*       MCRG_CTRL_FMS;
    SCRG_CTRL_IMX_REG_O26A0_T*       SCRG_CTRL_IMX;
    //SCRG_CTRL_DDR_REG_O26A0_T*     SCRG_CTRL_DDR;
    SCRG_CTRL_DDR0SB_REG_O26A0_T*    SCRG_CTRL_DDR0SB;
    SCRG_CTRL_DDR1SB_REG_O26A0_T*    SCRG_CTRL_DDR1SB;
    MICOM_BCRG_CTRL_WOC_REG_O26A0_T* CPU_BCRG_CTRL_WOC;   // CPU
    MICOM_BCRG_CTRL_WOC_REG_O26A0_T* PMCU_BCRG_CTRL_WOC;  // PMCU
    MICOM_BCRG_CTRL_WOC_REG_O26A0_T* VMCU_BCRG_CTRL_WOC;  // VMCU
    MICOM_BCRG_CTRL_WOC_REG_O26A0_T* MICOM_BCRG_CTRL_WOC; // MICOM
    BCRG_CTRL_BMC_REG_O26A0_T*       BCRG_CTRL_BMC;
    MCRG_CTRL_BMC_REG_O26A0_T*       MCRG_CTRL_BMC;
    MCRG_CTRL_EMMC_REG_O26A0_T*      MCRG_CTRL_EMMC;
    MICOM_MCRG_CTRL_WOC_REG_O26A0_T* CPU_MCRG_CTRL_WOC;   // CPU
    MICOM_MCRG_CTRL_WOC_REG_O26A0_T* PMCU_MCRG_CTRL_WOC;  // PMCU
    MICOM_MCRG_CTRL_WOC_REG_O26A0_T* VMCU_MCRG_CTRL_WOC;  // VMCU
    MICOM_MCRG_CTRL_WOC_REG_O26A0_T* MICOM_MCRG_CTRL_WOC; // MICOM
    BCRG_CTRL_FMS_REG_O26A0_T*       BCRG_CTRL_FMS;
    SCRG_CTRL_EMMC_REG_O26A0_T*      SCRG_CTRL_EMMC;
    SCRG_CTRL_CCO_REG_O26A0_T*       SCRG_CTRL_CCO;
    MCRG_CTRL_DPE_REG_O26A0_T*       MCRG_CTRL_DPE;
    MCRG_CTRL_LNX2_REG_O26A0_T*      MCRG_CTRL_LNX2;
    SCRG_CTRL_VD1_REG_O26A0_T*       SCRG_CTRL_VD1;
    SCRG_CTRL_ME1_REG_O26A0_T*       SCRG_CTRL_ME1;
    SCRG_CTRL_LNX2_REG_O26A0_T*      SCRG_CTRL_LNX2;
    SCRG_CTRL_LBUS_REG_O26A0_T*      SCRG_CTRL_LBUS;
    SCRG_CTRL_LNX0_REG_O26A0_T*      SCRG_CTRL_LNX0;
    SCRG_CTRL_TIVSB_REG_O26A0_T*     SCRG_CTRL_TIVSB;
    BCRG_CTRL_ME0_REG_O26A0_T*       BCRG_CTRL_ME0;
    BCRG_CTRL_LBM_REG_O26A0_T*       BCRG_CTRL_LBM;
    MCRG_CTRL_VD1_REG_O26A0_T*       MCRG_CTRL_VD1;
    MCRG_CTRL_ME1_REG_O26A0_T*       MCRG_CTRL_ME1;
    BCRG_CTRL_VD0_REG_O26A0_T*       BCRG_CTRL_VD0;
    SCRG_CTRL_VSD_REG_O26A0_T*       SCRG_CTRL_VSD;
    MCRG_CTRL_LNX0_REG_O26A0_T*      MCRG_CTRL_LNX0;
    MCRG_CTRL_CCO_REG_O26A0_T*       MCRG_CTRL_CCO;
    BCRG_CTRL_GSC_REG_O26A0_T*       BCRG_CTRL_GSC;
    SCRG_CTRL_SRCOSB_REG_O26A0_T*    SCRG_CTRL_SRCOSB;
    BCRG_CTRL_IMX_REG_O26A0_T*       BCRG_CTRL_IMX;
    SCRG_CTRL_ION1_REG_O26A0_T*      SCRG_CTRL_ION1;
    SCRG_CTRL_M1_REG_O26A0_T*        SCRG_CTRL_M1;
    MICOM_SCRG_CTRL_EPHY_REG_O26A0_T* CPU_SCRG_CTRL_EPHY;      // CPU
    MICOM_SCRG_CTRL_EPHY_REG_O26A0_T* MICOM_SCRG_CTRL_EPHY;    // MICOM
    SCRG_CTRL_M0_REG_O26A0_T*        SCRG_CTRL_M0;
    MCRG_CTRL_HDMI_REG_O26A0_T*      MCRG_CTRL_HDMI;
    BCRG_CTRL_DNSR_REG_O26A0_T*      BCRG_CTRL_DNSR;
    BCRG_CTRL_VENC_REG_O26A0_T*      BCRG_CTRL_VENC;
    SCRG_CTRL_HDMI_REG_O26A0_T*      SCRG_CTRL_HDMI;
    MICOM_SCRG_CTRL_MICOM_REG_O26A0_T* CPU_SCRG_CTRL_MICOM;    // CPU
    MICOM_SCRG_CTRL_MICOM_REG_O26A0_T* MICOM_SCRG_CTRL_MICOM;  // MICOM
    SCRG_CTRL_FMS_REG_O26A0_T*       SCRG_CTRL_FMS;
    SCRG_CTRL_EDPTX_REG_O26A0_T*     SCRG_CTRL_EDPTX;
    MCRG_CTRL_IMX_REG_O26A0_T*       MCRG_CTRL_IMX;
    MICOM_SCRG_CTRL_EDID_REG_O26A0_T* CPU_SCRG_CTRL_EDID;      // CPU
    MICOM_SCRG_CTRL_EDID_REG_O26A0_T* MICOM_SCRG_CTRL_EDID;    // MICOM
    SCRG_CTRL_VDO_REG_O26A0_T*       SCRG_CTRL_VDO;
    MCRG_CTRL_GSC_REG_O26A0_T*       MCRG_CTRL_GSC;
    //SCRG_CTRL_USB_HS_REG_O26A0_T*  SCRG_CTRL_USB_HS;
    SCRG_CTRL_USB_HS1_REG_O26A0_T*   SCRG_CTRL_USB_HS1;
    SCRG_CTRL_USB_HS2_REG_O26A0_T*   SCRG_CTRL_USB_HS2;
    SCRG_CTRL_USB_HS3_REG_O26A0_T*   SCRG_CTRL_USB_HS3;
    BCRG_CTRL_CCO_REG_O26A0_T*       BCRG_CTRL_CCO;
    MCRG_CTRL_LNX1_REG_O26A0_T*      MCRG_CTRL_LNX1;
    MCRG_CTRL_ME0_REG_O26A0_T*       MCRG_CTRL_ME0;
    BCRG_CTRL_VD1_REG_O26A0_T*       BCRG_CTRL_VD1;
    MCRG_CTRL_LBM_REG_O26A0_T*       MCRG_CTRL_LBM;
    BCRG_CTRL_ME1_REG_O26A0_T*       BCRG_CTRL_ME1;
    MCRG_CTRL_VD0_REG_O26A0_T*       MCRG_CTRL_VD0;
    SCRG_CTRL_GPU_REG_O26A0_T*       SCRG_CTRL_GPU;
    SCRG_CTRL_LNX1_REG_O26A0_T*      SCRG_CTRL_LNX1;

    /* ION RX */
    ION_TOP_CTRL_REG_O26A0_T*        ION0_TOP_CTRL;
    ION_TOP_CTRL_REG_O26A0_T*        ION1_TOP_CTRL;
    FUNC_IOMUX_ION0_PAD_REG_O26A0_T* ION0_IOMUX_PAD;
    FUNC_IOMUX_ION0_CORE_REG_O26A0_T* ION0_IOMUX_CORE;
    FUNC_IOMUX_ION1_PAD_REG_O26A0_T* ION1_IOMUX_PAD;
    FUNC_IOMUX_ION1_CORE_REG_O26A0_T* ION1_IOMUX_CORE;

    SRDS12TO3_REG_O26A0_T*          ION0_SRDS12TO3;
    SRDS32TO1_REG_O26A0_T*          ION0_SRDS32TO1_0;
    SRDS32TO1_REG_O26A0_T*          ION0_SRDS32TO1_1;
    SRDS12TO3_REG_O26A0_T*          ION1_SRDS12TO3;
    SRDS32TO1_REG_O26A0_T*          ION1_SRDS32TO1_0;
}
CTOP_REG_O26A0_T;

#define O26_A0_BND_CTRL_HDMI_BASE                0xC8772000
#define O26_A0_BND_CTRL_HDMI_TYPE                BND_CTRL_HDMI_REG_O26A0_T
#define O26_A0_BND_CTRL_LNX1_BASE                0xCC5C2000
#define O26_A0_BND_CTRL_LNX1_TYPE                BND_CTRL_LNX1_REG_O26A0_T
#define O26_A0_BND_CTRL_CPU_BASE                 0xCA222000
#define O26_A0_BND_CTRL_CPU_TYPE                 BND_CTRL_CPU_REG_O26A0_T
#define O26_A0_CPU_PW_CTRL_BASE                  0xCA3A2000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_CPU_PW_CTRL_TYPE                  MICOM_PW_CTRL_REG_O26A0_T
#define O26_A0_PMCU_PW_CTRL_BASE                 0xCC3A2000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_PMCU_PW_CTRL_TYPE                 MICOM_PW_CTRL_REG_O26A0_T
#define O26_A0_VMCU_PW_CTRL_BASE                 0xCE3A2000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_VMCU_PW_CTRL_TYPE                 MICOM_PW_CTRL_REG_O26A0_T
#define O26_A0_MICOM_PW_CTRL_BASE                0xF33A2000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_MICOM_PW_CTRL_TYPE                MICOM_PW_CTRL_REG_O26A0_T
#define O26_A0_BND_CTRL_HDR_BASE                 0xCC272000
#define O26_A0_BND_CTRL_HDR_TYPE                 BND_CTRL_HDR_REG_O26A0_T
#define O26_A0_BND_CTRL_AUD_BASE                 0xCE7B2000
#define O26_A0_BND_CTRL_AUD_TYPE                 BND_CTRL_AUD_REG_O26A0_T
#define O26_A0_BND_CTRL_LNX0_BASE                0xCC582000
#define O26_A0_BND_CTRL_LNX0_TYPE                BND_CTRL_LNX0_REG_O26A0_T
#define O26_A0_TRG_CTRL_BASE                     0xCC4C4000 // CRG_TOP_TRG_CTRL_BASE
#define O26_A0_TRG_CTRL_TYPE                     TRG_CTRL_REG_O26A0_T
#define O26_A0_BND_CTRL_FMC_BASE                 0xCCC62000
#define O26_A0_BND_CTRL_FMC_TYPE                 BND_CTRL_FMC_REG_O26A0_T
#define O26_A0_BND_CTRL_EMMC_BASE                0xC6222000
#define O26_A0_BND_CTRL_EMMC_TYPE                BND_CTRL_EMMC_REG_O26A0_T
#define O26_A0_BND_CTRL_M0_BASE                  0xC4932000
#define O26_A0_BND_CTRL_M0_TYPE                  BND_CTRL_M0_REG_O26A0_T
#define O26_A0_BND_CTRL_ND1_BASE                 0xCC2E2000
#define O26_A0_BND_CTRL_ND1_TYPE                 BND_CTRL_ND1_REG_O26A0_T
#define O26_A0_BND_CTRL_LNX2_BASE                0xCC602000
#define O26_A0_BND_CTRL_LNX2_TYPE                BND_CTRL_LNX2_REG_O26A0_T
#define O26_A0_BND_CTRL_SRE_BASE                 0xCCA22000
#define O26_A0_BND_CTRL_SRE_TYPE                 BND_CTRL_SRE_REG_O26A0_T
#define O26_A0_BND_CTRL_ND0_BASE                 0xCC2B2000
#define O26_A0_BND_CTRL_ND0_TYPE                 BND_CTRL_ND0_REG_O26A0_T
#define O26_A0_BND_CTRL_M1_BASE                  0xC4D32000
#define O26_A0_BND_CTRL_M1_TYPE                  BND_CTRL_M1_REG_O26A0_T
#define O26_A0_DRG_CTRL_BASE                     0xCC975000 // CRG_TOP_DRG_CTRL_BASE
#define O26_A0_DRG_CTRL_TYPE                     DRG_CTRL_REG_O26A0_T
#define O26_A0_BND_CTRL_GSC_BASE                 0xCCC92000
#define O26_A0_BND_CTRL_GSC_TYPE                 BND_CTRL_GSC_REG_O26A0_T
#define O26_A0_BND_CTRL_LBM_BASE                 0xC4042000
#define O26_A0_BND_CTRL_LBM_TYPE                 BND_CTRL_LBM_REG_O26A0_T
#define O26_A0_BND_CTRL_ME0_BASE                 0xCCCC2000
#define O26_A0_BND_CTRL_ME0_TYPE                 BND_CTRL_ME0_REG_O26A0_T
#define O26_A0_BND_CTRL_VD0_BASE                 0xCE522000
#define O26_A0_BND_CTRL_VD0_TYPE                 BND_CTRL_VD0_REG_O26A0_T
#define O26_A0_BND_CTRL_IMX_BASE                 0xCCC32000
#define O26_A0_BND_CTRL_IMX_TYPE                 BND_CTRL_IMX_REG_O26A0_T
#define O26_A0_CPU_CRG_TOP_WOC_CTRL_BASE         0xCA3A7000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_CPU_CRG_TOP_WOC_CTRL_TYPE         MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T
#define O26_A0_PMCU_CRG_TOP_WOC_CTRL_BASE        0xCC3A7000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_PMCU_CRG_TOP_WOC_CTRL_TYPE        MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T
#define O26_A0_VMCU_CRG_TOP_WOC_CTRL_BASE        0xCE3A7000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_VMCU_CRG_TOP_WOC_CTRL_TYPE        MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T
#define O26_A0_MICOM_CRG_TOP_WOC_CTRL_BASE       0xF33A7000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_MICOM_CRG_TOP_WOC_CTRL_TYPE       MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T
#define O26_A0_BND_CTRL_ME1_BASE                 0xCCCF2000
#define O26_A0_BND_CTRL_ME1_TYPE                 BND_CTRL_ME1_REG_O26A0_T
#define O26_A0_BND_CTRL_CCO_BASE                 0xCC8A2000
#define O26_A0_BND_CTRL_CCO_TYPE                 BND_CTRL_CCO_REG_O26A0_T
#define O26_A0_BND_CTRL_DNSR_BASE                0xCC4C2000
#define O26_A0_BND_CTRL_DNSR_TYPE                BND_CTRL_DNSR_REG_O26A0_T
#define O26_A0_BND_CTRL_VENC_BASE                0xCE472000
#define O26_A0_BND_CTRL_VENC_TYPE                BND_CTRL_VENC_REG_O26A0_T
#define O26_A0_BND_CTRL_DPE_BASE                 0xCC972000
#define O26_A0_BND_CTRL_DPE_TYPE                 BND_CTRL_DPE_REG_O26A0_T
#define O26_A0_BND_CTRL_BMC_BASE                 0xC8A32000
#define O26_A0_BND_CTRL_BMC_TYPE                 BND_CTRL_BMC_REG_O26A0_T
#define O26_A0_BND_CTRL_FMS_BASE                 0xCC322000
#define O26_A0_BND_CTRL_FMS_TYPE                 BND_CTRL_FMS_REG_O26A0_T
#define O26_A0_TMUX_CTRL_BASE                    0xCCC33000
#define O26_A0_TMUX_CTRL_TYPE                    TMUX_CTRL_REG_O26A0_T
#define O26_A0_CPU_BND_CTRL_WOC_BASE             0xCA3A6000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_CPU_BND_CTRL_WOC_TYPE             BND_CTRL_WOC_REG_O26A0_T
#define O26_A0_PMCU_BND_CTRL_WOC_BASE            0xCC3A6000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_PMCU_BND_CTRL_WOC_TYPE            BND_CTRL_WOC_REG_O26A0_T
#define O26_A0_VMCU_BND_CTRL_WOC_BASE            0xCE3A6000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_VMCU_BND_CTRL_WOC_TYPE            BND_CTRL_WOC_REG_O26A0_T
#define O26_A0_MICOM_BND_CTRL_WOC_BASE           0xF33A6000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_MICOM_BND_CTRL_WOC_TYPE           BND_CTRL_WOC_REG_O26A0_T
#define O26_A0_MIP_DIG_CTRL_BASE                 0xC8A37000
#define O26_A0_MIP_DIG_CTRL_TYPE                 MIP_DIG_CTRL_REG_O26A0_T

#define O26_A0_CRC_TOUT_BASE                     0xCC943000
#define O26_A0_CRC_TOUT_TYPE                     CRC_TOUT_REG_O26A0_T
#define O26_A0_CRC_VOUT_BASE                     0xCC942000
#define O26_A0_CRC_VOUT_TYPE                     CRC_VOUT_REG_O26A0_T

#define O26_A0_MIP_CTRL_C4TX16_BASE              0xCC974000 // MIP_CTRL_C4TX_BASE
#define O26_A0_MIP_CTRL_C4TX16_TYPE              MIP_CTRL_C4TX16_REG_O26A0_T
#define O26_A0_MIP_CTRL_HDMI1_BASE               0xC8774000
#define O26_A0_MIP_CTRL_HDMI1_TYPE               MIP_CTRL_HDMI1_REG_O26A0_T
#define O26_A0_MIP_CTRL_ADMD_MIP_BASE            0xC8A35000
#define O26_A0_MIP_CTRL_ADMD_MIP_TYPE            MIP_CTRL_ADMD_MIP_REG_O26A0_T
#define O26_A0_MIP_CTRL_CVBSAFE_BASE             0xC8A34000
#define O26_A0_MIP_CTRL_CVBSAFE_TYPE             MIP_CTRL_CVBSAFE_REG_O26A0_T
#define O26_A0_MIP_CTRL_HDMI3_BASE               0xC8776000
#define O26_A0_MIP_CTRL_HDMI3_TYPE               MIP_CTRL_HDMI3_REG_O26A0_T
#define O26_A0_MIP_CTRL_HDMI2_BASE               0xC8775000
#define O26_A0_MIP_CTRL_HDMI2_TYPE               MIP_CTRL_HDMI2_REG_O26A0_T
#define O26_A0_MIP_CTRL_ACODEC_BASE              0xC8A33000
#define O26_A0_MIP_CTRL_ACODEC_TYPE              MIP_CTRL_ACODEC_REG_O26A0_T
#define O26_A0_MIP_CTRL_HDMI_EARC_BASE           0xC8778000
#define O26_A0_MIP_CTRL_HDMI_EARC_TYPE           MIP_CTRL_HDMI_EARC_REG_O26A0_T
#define O26_A0_MIP_CTRL_TSADC_BASE               0xC4043000
#define O26_A0_MIP_CTRL_TSADC_TYPE               MIP_CTRL_TSADC_REG_O26A0_T
#define O26_A0_CPU_MIP_CTRL_HDMI_DPM_BASE        0xCA3A4000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_CPU_MIP_CTRL_HDMI_DPM_TYPE        MIP_CTRL_HDMI_DPM_REG_O26A0_T
#define O26_A0_PMCU_MIP_CTRL_HDMI_DPM_BASE       0xCC3A4000
#define O26_A0_PMCU_MIP_CTRL_HDMI_DPM_TYPE       MIP_CTRL_HDMI_DPM_REG_O26A0_T
#define O26_A0_VMCU_MIP_CTRL_HDMI_DPM_BASE       0xCE3A4000
#define O26_A0_VMCU_MIP_CTRL_HDMI_DPM_TYPE       MIP_CTRL_HDMI_DPM_REG_O26A0_T
#define O26_A0_MICOM_MIP_CTRL_HDMI_DPM_BASE      0xF33A4000
#define O26_A0_MICOM_MIP_CTRL_HDMI_DPM_TYPE      MIP_CTRL_HDMI_DPM_REG_O26A0_T
#define O26_A0_MIP_CTRL_HDMI4_BASE               0xC8777000
#define O26_A0_MIP_CTRL_HDMI4_TYPE               MIP_CTRL_HDMI4_REG_O26A0_T

#define O26_A0_CPU_IOMUX_CTRL_WOC_BASE           0xCA3A3000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_CPU_IOMUX_CTRL_WOC_TYPE           IOMUX_CTRL_WOC_REG_O26A0_T
#define O26_A0_PMCU_IOMUX_CTRL_WOC_BASE          0xCC3A3000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_PMCU_IOMUX_CTRL_WOC_TYPE          IOMUX_CTRL_WOC_REG_O26A0_T
#define O26_A0_VMCU_IOMUX_CTRL_WOC_BASE          0xCE3A3000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_VMCU_IOMUX_CTRL_WOC_TYPE          IOMUX_CTRL_WOC_REG_O26A0_T
#define O26_A0_MICOM_IOMUX_CTRL_WOC_BASE         0xF33A3000 // CPU, PMCU, VMCU, MICOM
#define O26_A0_MICOM_IOMUX_CTRL_WOC_TYPE         IOMUX_CTRL_WOC_REG_O26A0_T

#define O26_A0_IOMUX_CTRL_DPE_BASE               0xCC973000
#define O26_A0_IOMUX_CTRL_DPE_TYPE               IOMUX_CTRL_DPE_REG_O26A0_T
#define O26_A0_IOMUX_CTRL_ME1_BASE               0xCCCF3000
#define O26_A0_IOMUX_CTRL_ME1_TYPE               IOMUX_CTRL_ME1_REG_O26A0_T
#define O26_A0_IOMUX_CTRL_HDMI_BASE              0xC8773000
#define O26_A0_IOMUX_CTRL_HDMI_TYPE              IOMUX_CTRL_HDMI_REG_O26A0_T
#define O26_A0_IOMUX_CTRL_AUD_BASE               0xCE7B3000
#define O26_A0_IOMUX_CTRL_AUD_TYPE               IOMUX_CTRL_AUD_REG_O26A0_T
#define O26_A0_IOMUX_CTRL_LNX2_BASE              0xCC603000
#define O26_A0_IOMUX_CTRL_LNX2_TYPE              IOMUX_CTRL_LNX2_REG_O26A0_T
#define O26_A0_IP_CTRL_HDR_BASE                  0xCC241000
#define O26_A0_IP_CTRL_HDR_TYPE                  IP_CTRL_HDR_REG_O26A0_T
#define O26_A0_IP_CTRL_AUD_BASE                  0xCE7C1000
#define O26_A0_IP_CTRL_AUD_TYPE                  IP_CTRL_AUD_REG_O26A0_T
#define O26_A0_IP_CTRL_FMC_BASE                  0xCCC51000
#define O26_A0_IP_CTRL_FMC_TYPE                  IP_CTRL_FMC_REG_O26A0_T
#define O26_A0_IP_CTRL_NPP_BASE                  0xCCD31000
#define O26_A0_IP_CTRL_NPP_TYPE                  IP_CTRL_NPP_REG_O26A0_T
#define O26_A0_IP_CTRL_DBB_BASE                  0xC8A11000
#define O26_A0_IP_CTRL_DBB_TYPE                  IP_CTRL_DBB_REG_O26A0_T
#define O26_A0_IP_CTRL_CPU_BASE                  0xCA211000
#define O26_A0_IP_CTRL_CPU_TYPE                  IP_CTRL_CPU_REG_O26A0_T
#define O26_A0_IP_CTRL_CVI_BASE                  0xCC4F1000
#define O26_A0_IP_CTRL_CVI_TYPE                  IP_CTRL_CVI_REG_O26A0_T
#define O26_A0_IP_CTRL_DSC_BASE                  0xCC511000
#define O26_A0_IP_CTRL_DSC_TYPE                  IP_CTRL_DSC_REG_O26A0_T
#define O26_A0_IP_CTRL_LNX1_BASE                 0xCC5B1000
#define O26_A0_IP_CTRL_LNX1_TYPE                 IP_CTRL_LNX1_REG_O26A0_T
#define O26_A0_IP_CTRL_ND0_BASE                  0xCC2A1000
#define O26_A0_IP_CTRL_ND0_TYPE                  IP_CTRL_ND0_REG_O26A0_T
#define O26_A0_IP_CTRL_HDMI_BASE                 0xC8741000
#define O26_A0_IP_CTRL_HDMI_TYPE                 IP_CTRL_HDMI_REG_O26A0_T
#define O26_A0_IP_CTRL_ND1_BASE                  0xCC2D1000
#define O26_A0_IP_CTRL_ND1_TYPE                  IP_CTRL_ND1_REG_O26A0_T
#define O26_A0_IP_CTRL_LBUS_BASE                 0xC4221000
#define O26_A0_IP_CTRL_LBUS_TYPE                 IP_CTRL_LBUS_REG_O26A0_T
#define O26_A0_IP_CTRL_LNX0_BASE                 0xCC551000
#define O26_A0_IP_CTRL_LNX0_TYPE                 IP_CTRL_LNX0_REG_O26A0_T
#define O26_A0_IP_CTRL_EDPTX_BASE                0xC6BB1000
#define O26_A0_IP_CTRL_EDPTX_TYPE                IP_CTRL_EDPTX_REG_O26A0_T
#define O26_A0_IP_CTRL_SRE_BASE                  0xCCA11000
#define O26_A0_IP_CTRL_SRE_TYPE                  IP_CTRL_SRE_REG_O26A0_T
#define O26_A0_IP_CTRL_ME1_BASE                  0xCCCE1000
#define O26_A0_IP_CTRL_ME1_TYPE                  IP_CTRL_ME1_REG_O26A0_T
#define O26_A0_IP_CTRL_CCO_BASE                  0xCC891000
#define O26_A0_IP_CTRL_CCO_TYPE                  IP_CTRL_CCO_REG_O26A0_T
#define O26_A0_IP_CTRL_GSC_BASE                  0xCCC81000
#define O26_A0_IP_CTRL_GSC_TYPE                  IP_CTRL_GSC_REG_O26A0_T
#define O26_A0_IP_CTRL_LED_BASE                  0xCC921000
#define O26_A0_IP_CTRL_LED_TYPE                  IP_CTRL_LED_REG_O26A0_T
#define O26_A0_IP_CTRL_ME0_BASE                  0xCCCB1000
#define O26_A0_IP_CTRL_ME0_TYPE                  IP_CTRL_ME0_REG_O26A0_T
#define O26_A0_IP_CTRL_TCON_BASE                 0xCC941000
#define O26_A0_IP_CTRL_TCON_TYPE                 IP_CTRL_TCON_REG_O26A0_T
#define O26_A0_IP_CTRL_IMX_BASE                  0xCCC21000
#define O26_A0_IP_CTRL_IMX_TYPE                  IP_CTRL_IMX_REG_O26A0_T
#define O26_A0_IP_CTRL_FMS_BASE                  0xCC311000
#define O26_A0_IP_CTRL_FMS_TYPE                  IP_CTRL_FMS_REG_O26A0_T
#define O26_A0_CPU_IP_CTRL_EDID_BASE             0xCA361000 // CPU,MICOM
#define O26_A0_CPU_IP_CTRL_EDID_TYPE             CPU_IP_CTRL_EDID_REG_O26A0_T
#define O26_A0_MICOM_IP_CTRL_EDID_BASE           0xF3361000 // CPU,MICOM
#define O26_A0_MICOM_IP_CTRL_EDID_TYPE           CPU_IP_CTRL_EDID_REG_O26A0_T
#define O26_A0_IP_CTRL_VDO_BASE                  0xCC261000
#define O26_A0_IP_CTRL_VDO_TYPE                  IP_CTRL_VDO_REG_O26A0_T
#define O26_A0_IP_CTRL_VSD_BASE                  0xCC961000
#define O26_A0_IP_CTRL_VSD_TYPE                  IP_CTRL_VSD_REG_O26A0_T
#define O26_A0_IP_CTRL_TE_BASE                   0xCE7E1000
#define O26_A0_IP_CTRL_TE_TYPE                   IP_CTRL_TE_REG_O26A0_T

#define O26_A0_FSC_CTRL_AUD_BASE                 0xCE7B4000
#define O26_A0_FSC_CTRL_AUD_TYPE                 FSC_CTRL_AUD_REG_O26A0_T

#define O26_A0_SCRG_CTRL_DBB_BASE                0xC8A10000
#define O26_A0_SCRG_CTRL_DBB_TYPE                SCRG_CTRL_DBB_REG_O26A0_T
#define O26_A0_MCRG_CTRL_ND0_BASE                0xCC2B0000
#define O26_A0_MCRG_CTRL_ND0_TYPE                MCRG_CTRL_ND0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_TCON_BASE               0xCC940000
#define O26_A0_SCRG_CTRL_TCON_TYPE               SCRG_CTRL_TCON_REG_O26A0_T
#define O26_A0_BCRG_CTRL_ND1_BASE                0xCC2E1000
#define O26_A0_BCRG_CTRL_ND1_TYPE                BCRG_CTRL_ND1_REG_O26A0_T
#define O26_A0_BCRG_CTRL_LNX0_BASE               0xCC581000
#define O26_A0_BCRG_CTRL_LNX0_TYPE               BCRG_CTRL_LNX0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LB0SB_BASE              0xCC620000
#define O26_A0_SCRG_CTRL_LB0SB_TYPE              SCRG_CTRL_LB0SB_REG_O26A0_T
#define O26_A0_BCRG_CTRL_M1_BASE                 0xC4D31000
#define O26_A0_BCRG_CTRL_M1_TYPE                 BCRG_CTRL_M1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_CVI_BASE                0xCC4F0000
#define O26_A0_SCRG_CTRL_CVI_TYPE                SCRG_CTRL_CVI_REG_O26A0_T
#define O26_A0_SCRG_CTRL_USBSB_BASE              0xC4520000
#define O26_A0_SCRG_CTRL_USBSB_TYPE              SCRG_CTRL_USBSB_REG_O26A0_T
#define O26_A0_SCRG_CTRL_ICOD_BASE               0xCE460000
#define O26_A0_SCRG_CTRL_ICOD_TYPE               SCRG_CTRL_ICOD_REG_O26A0_T
#define O26_A0_SCRG_CTRL_CPU_BASE                0xCA210000
#define O26_A0_SCRG_CTRL_CPU_TYPE                SCRG_CTRL_CPU_REG_O26A0_T
#define O26_A0_BCRG_CTRL_SRE_BASE                0xCCA21000
#define O26_A0_BCRG_CTRL_SRE_TYPE                BCRG_CTRL_SRE_REG_O26A0_T
#define O26_A0_SCRG_CTRL_AUD_BASE                0xCE7C0000
#define O26_A0_SCRG_CTRL_AUD_TYPE                SCRG_CTRL_AUD_REG_O26A0_T
#define O26_A0_MCRG_CTRL_SRE_BASE                0xCCA20000
#define O26_A0_MCRG_CTRL_SRE_TYPE                MCRG_CTRL_SRE_REG_O26A0_T
#define O26_A0_MCRG_CTRL_VENC_BASE               0xCE470000
#define O26_A0_MCRG_CTRL_VENC_TYPE               MCRG_CTRL_VENC_REG_O26A0_T
#define O26_A0_MCRG_CTRL_DNSR_BASE               0xCC4C0000
#define O26_A0_MCRG_CTRL_DNSR_TYPE               MCRG_CTRL_DNSR_REG_O26A0_T
#define O26_A0_BCRG_CTRL_HDMI_BASE               0xC8771000
#define O26_A0_BCRG_CTRL_HDMI_TYPE               BCRG_CTRL_HDMI_REG_O26A0_T
#define O26_A0_SCRG_CTRL_HDR_BASE                0xCC240000
#define O26_A0_SCRG_CTRL_HDR_TYPE                SCRG_CTRL_HDR_REG_O26A0_T
#define O26_A0_SCRG_CTRL_DNSR0_BASE              0xCC490000
#define O26_A0_SCRG_CTRL_DNSR0_TYPE              SCRG_CTRL_DNSR_REG_O26A0_T
#define O26_A0_SCRG_CTRL_DNSR1_BASE              0xCC4B0000
#define O26_A0_SCRG_CTRL_DNSR1_TYPE              SCRG_CTRL_DNSR_REG_O26A0_T
#define O26_A0_SCRG_CTRL_VENC_BASE               0xCE440000
#define O26_A0_SCRG_CTRL_VENC_TYPE               SCRG_CTRL_VENC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_NPP_BASE                0xCCD30000
#define O26_A0_SCRG_CTRL_NPP_TYPE                SCRG_CTRL_NPP_REG_O26A0_T
#define O26_A0_BCRG_CTRL_M0_BASE                 0xC4931000
#define O26_A0_BCRG_CTRL_M0_TYPE                 BCRG_CTRL_M0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_TIVVMSB_BASE            0xCE490000
#define O26_A0_SCRG_CTRL_TIVVMSB_TYPE            SCRG_CTRL_TIVVMSB_REG_O26A0_T
#define O26_A0_SCRG_CTRL_IOMMU_BASE              0xC4110000
#define O26_A0_SCRG_CTRL_IOMMU_TYPE              SCRG_CTRL_IOMMU_REG_O26A0_T
#define O26_A0_SCRG_CTRL_FMC_BASE                0xCCC50000
#define O26_A0_SCRG_CTRL_FMC_TYPE                SCRG_CTRL_FMC_REG_O26A0_T
#define O26_A0_PMCU_SCRG_CTRL_PMCU_BASE          0xCC3D0000
#define O26_A0_PMCU_SCRG_CTRL_PMCU_TYPE          PMCU_SCRG_CTRL_PMCU_REG_O26A0_T
#define O26_A0_BCRG_CTRL_LNX1_BASE               0xCC5C1000
#define O26_A0_BCRG_CTRL_LNX1_TYPE               BCRG_CTRL_LNX1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_DMCU_BASE               0xCA3B0000
#define O26_A0_SCRG_CTRL_DMCU_TYPE               SCRG_CTRL_DMCU_REG_O26A0_T
#define O26_A0_SCRG_CTRL_TE_BASE                 0xCE7E0000
#define O26_A0_SCRG_CTRL_TE_TYPE                 SCRG_CTRL_TE_REG_O26A0_T
#define O26_A0_BCRG_CTRL_ND0_BASE                0xCC2B1000
#define O26_A0_BCRG_CTRL_ND0_TYPE                BCRG_CTRL_ND0_REG_O26A0_T
#define O26_A0_MCRG_CTRL_ND1_BASE                0xCC2E0000
#define O26_A0_MCRG_CTRL_ND1_TYPE                MCRG_CTRL_ND1_REG_O26A0_T
#define O26_A0_MCRG_CTRL_FMC_BASE                0xCCC60000
#define O26_A0_MCRG_CTRL_FMC_TYPE                MCRG_CTRL_FMC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_FMESB_BASE              0xCCD00000
#define O26_A0_SCRG_CTRL_FMESB_TYPE              SCRG_CTRL_FMESB_REG_O26A0_T
#define O26_A0_MCRG_CTRL_M1_BASE                 0xC4D30000
#define O26_A0_MCRG_CTRL_M1_TYPE                 MCRG_CTRL_M1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_ND1_BASE                0xCC2D0000
#define O26_A0_SCRG_CTRL_ND1_TYPE                SCRG_CTRL_ND1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_GFX_BASE                0xC4090000
#define O26_A0_SCRG_CTRL_GFX_TYPE                SCRG_CTRL_GFX_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LB1SB_BASE              0xCA280000
#define O26_A0_SCRG_CTRL_LB1SB_TYPE              SCRG_CTRL_LB1SB_REG_O26A0_T
#define O26_A0_MCRG_CTRL_HDR_BASE                0xCC270000
#define O26_A0_MCRG_CTRL_HDR_TYPE                MCRG_CTRL_HDR_REG_O26A0_T
#define O26_A0_MCRG_CTRL_AUD_BASE                0xCE7B0000
#define O26_A0_MCRG_CTRL_AUD_TYPE                MCRG_CTRL_AUD_REG_O26A0_T
#define O26_A0_SCRG_CTRL_SRE_BASE                0xCCA10000
#define O26_A0_SCRG_CTRL_SRE_TYPE                SCRG_CTRL_SRE_REG_O26A0_T
#define O26_A0_BCRG_CTRL_CPU_BASE                0xCA221000
#define O26_A0_BCRG_CTRL_CPU_TYPE                BCRG_CTRL_CPU_REG_O26A0_T
#define O26_A0_VMCU_SCRG_CTRL_VMCU_BASE          0xCE3C0000
#define O26_A0_VMCU_SCRG_CTRL_VMCU_TYPE          VMCU_SCRG_CTRL_VMCU_REG_O26A0_T
#define O26_A0_MCRG_CTRL_CPU_BASE                0xCA220000
#define O26_A0_MCRG_CTRL_CPU_TYPE                MCRG_CTRL_CPU_REG_O26A0_T
#define O26_A0_BCRG_CTRL_AUD_BASE                0xCE7B1000
#define O26_A0_BCRG_CTRL_AUD_TYPE                BCRG_CTRL_AUD_REG_O26A0_T
#define O26_A0_BCRG_CTRL_HDR_BASE                0xCC271000
#define O26_A0_BCRG_CTRL_HDR_TYPE                BCRG_CTRL_HDR_REG_O26A0_T
#define O26_A0_BCRG_CTRL_EMMC_BASE               0xC6221000
#define O26_A0_BCRG_CTRL_EMMC_TYPE               BCRG_CTRL_EMMC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_DSC_BASE                0xCC510000
#define O26_A0_SCRG_CTRL_DSC_TYPE                SCRG_CTRL_DSC_REG_O26A0_T
#define O26_A0_CPU_SCRG_CTRL_ION0_BASE           0xCA340000
#define O26_A0_CPU_SCRG_CTRL_ION0_TYPE           MICOM_SCRG_CTRL_ION0_REG_O26A0_T
#define O26_A0_MICOM_SCRG_CTRL_ION0_BASE         0xF3340000
#define O26_A0_MICOM_SCRG_CTRL_ION0_TYPE         MICOM_SCRG_CTRL_ION0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_USB_SS_BASE             0xC6110000
#define O26_A0_SCRG_CTRL_USB_SS_TYPE             SCRG_CTRL_USB_SS_REG_O26A0_T
#define O26_A0_SCRG_CTRL_ND0_BASE                0xCC2A0000
#define O26_A0_SCRG_CTRL_ND0_TYPE                SCRG_CTRL_ND0_REG_O26A0_T
#define O26_A0_MCRG_CTRL_M0_BASE                 0xC4930000
#define O26_A0_MCRG_CTRL_M0_TYPE                 MCRG_CTRL_M0_REG_O26A0_T
#define O26_A0_BCRG_CTRL_LNX2_BASE               0xCC601000
#define O26_A0_BCRG_CTRL_LNX2_TYPE               BCRG_CTRL_LNX2_REG_O26A0_T
#define O26_A0_BCRG_CTRL_FMC_BASE                0xCCC61000
#define O26_A0_BCRG_CTRL_FMC_TYPE                BCRG_CTRL_FMC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_ME0_BASE                0xCCCB0000
#define O26_A0_SCRG_CTRL_ME0_TYPE                SCRG_CTRL_ME0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_VD0_BASE                0xCE510000
#define O26_A0_SCRG_CTRL_VD0_TYPE                SCRG_CTRL_VD0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LED_BASE                0xCC920000
#define O26_A0_SCRG_CTRL_LED_TYPE                SCRG_CTRL_LED_REG_O26A0_T
#define O26_A0_SCRG_CTRL_EMUSB_BASE              0xC6180000
#define O26_A0_SCRG_CTRL_EMUSB_TYPE              SCRG_CTRL_EMUSB_REG_O26A0_T
#define O26_A0_SCRG_CTRL_GSC_BASE                0xCCC80000
#define O26_A0_SCRG_CTRL_GSC_TYPE                SCRG_CTRL_GSC_REG_O26A0_T
#define O26_A0_BCRG_CTRL_DPE_BASE                0xCC971000
#define O26_A0_BCRG_CTRL_DPE_TYPE                BCRG_CTRL_DPE_REG_O26A0_T
#define O26_A0_MCRG_CTRL_FMS_BASE                0xCC320000
#define O26_A0_MCRG_CTRL_FMS_TYPE                MCRG_CTRL_FMS_REG_O26A0_T
#define O26_A0_SCRG_CTRL_IMX_BASE                0xCCC20000
#define O26_A0_SCRG_CTRL_IMX_TYPE                SCRG_CTRL_IMX_REG_O26A0_T
#define O26_A0_SCRG_CTRL_DDR0SB_BASE             0xC4500000
#define O26_A0_SCRG_CTRL_DDR0SB_TYPE             SCRG_CTRL_DDR0SB_REG_O26A0_T
#define O26_A0_SCRG_CTRL_DDR1SB_BASE             0xC4510000
#define O26_A0_SCRG_CTRL_DDR1SB_TYPE             SCRG_CTRL_DDR1SB_REG_O26A0_T
#define O26_A0_CPU_BCRG_CTRL_WOC_BASE            0xCA3A1000
#define O26_A0_CPU_BCRG_CTRL_WOC_TYPE            MICOM_BCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_PMCU_BCRG_CTRL_WOC_BASE           0xCC3A1000
#define O26_A0_PMCU_BCRG_CTRL_WOC_TYPE           MICOM_BCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_VMCU_BCRG_CTRL_WOC_BASE           0xCE3A1000
#define O26_A0_VMCU_BCRG_CTRL_WOC_TYPE           MICOM_BCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_MICOM_BCRG_CTRL_WOC_BASE          0xF33A1000
#define O26_A0_MICOM_BCRG_CTRL_WOC_TYPE          MICOM_BCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_BCRG_CTRL_BMC_BASE                0xC8A31000
#define O26_A0_BCRG_CTRL_BMC_TYPE                BCRG_CTRL_BMC_REG_O26A0_T
#define O26_A0_MCRG_CTRL_BMC_BASE                0xC8A30000
#define O26_A0_MCRG_CTRL_BMC_TYPE                MCRG_CTRL_BMC_REG_O26A0_T
#define O26_A0_MCRG_CTRL_EMMC_BASE               0xC6220000
#define O26_A0_MCRG_CTRL_EMMC_TYPE               MCRG_CTRL_EMMC_REG_O26A0_T
#define O26_A0_CPU_MCRG_CTRL_WOC_BASE            0xCA3A0000
#define O26_A0_CPU_MCRG_CTRL_WOC_TYPE            MICOM_MCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_PMCU_MCRG_CTRL_WOC_BASE           0xCC3A0000
#define O26_A0_PMCU_MCRG_CTRL_WOC_TYPE           MICOM_MCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_VMCU_MCRG_CTRL_WOC_BASE           0xCE3A0000
#define O26_A0_VMCU_MCRG_CTRL_WOC_TYPE           MICOM_MCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_MICOM_MCRG_CTRL_WOC_BASE          0xF33A0000
#define O26_A0_MICOM_MCRG_CTRL_WOC_TYPE          MICOM_MCRG_CTRL_WOC_REG_O26A0_T
#define O26_A0_BCRG_CTRL_FMS_BASE                0xCC321000
#define O26_A0_BCRG_CTRL_FMS_TYPE                BCRG_CTRL_FMS_REG_O26A0_T
#define O26_A0_SCRG_CTRL_EMMC_BASE               0xC6210000
#define O26_A0_SCRG_CTRL_EMMC_TYPE               SCRG_CTRL_EMMC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_CCO_BASE                0xCC890000
#define O26_A0_SCRG_CTRL_CCO_TYPE                SCRG_CTRL_CCO_REG_O26A0_T
#define O26_A0_MCRG_CTRL_DPE_BASE                0xCC970000
#define O26_A0_MCRG_CTRL_DPE_TYPE                MCRG_CTRL_DPE_REG_O26A0_T
#define O26_A0_MCRG_CTRL_LNX2_BASE               0xCC600000
#define O26_A0_MCRG_CTRL_LNX2_TYPE               MCRG_CTRL_LNX2_REG_O26A0_T
#define O26_A0_SCRG_CTRL_VD1_BASE                0xCE590000
#define O26_A0_SCRG_CTRL_VD1_TYPE                SCRG_CTRL_VD1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_ME1_BASE                0xCCCE0000
#define O26_A0_SCRG_CTRL_ME1_TYPE                SCRG_CTRL_ME1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LNX2_BASE               0xCC5F0000
#define O26_A0_SCRG_CTRL_LNX2_TYPE               SCRG_CTRL_LNX2_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LBUS_BASE               0xC4220000
#define O26_A0_SCRG_CTRL_LBUS_TYPE               SCRG_CTRL_LBUS_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LNX0_BASE               0xCC550000
#define O26_A0_SCRG_CTRL_LNX0_TYPE               SCRG_CTRL_LNX0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_TIVSB_BASE              0xCE420000
#define O26_A0_SCRG_CTRL_TIVSB_TYPE              SCRG_CTRL_TIVSB_REG_O26A0_T
#define O26_A0_BCRG_CTRL_ME0_BASE                0xCCCC1000
#define O26_A0_BCRG_CTRL_ME0_TYPE                BCRG_CTRL_ME0_REG_O26A0_T
#define O26_A0_BCRG_CTRL_LBM_BASE                0xC4041000
#define O26_A0_BCRG_CTRL_LBM_TYPE                BCRG_CTRL_LBM_REG_O26A0_T
#define O26_A0_MCRG_CTRL_VD1_BASE                0xCE5A0000
#define O26_A0_MCRG_CTRL_VD1_TYPE                MCRG_CTRL_VD1_REG_O26A0_T
#define O26_A0_MCRG_CTRL_ME1_BASE                0xCCCF0000
#define O26_A0_MCRG_CTRL_ME1_TYPE                MCRG_CTRL_ME1_REG_O26A0_T
#define O26_A0_BCRG_CTRL_VD0_BASE                0xCE521000
#define O26_A0_BCRG_CTRL_VD0_TYPE                BCRG_CTRL_VD0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_VSD_BASE                0xCC960000
#define O26_A0_SCRG_CTRL_VSD_TYPE                SCRG_CTRL_VSD_REG_O26A0_T
#define O26_A0_MCRG_CTRL_LNX0_BASE               0xCC580000
#define O26_A0_MCRG_CTRL_LNX0_TYPE               MCRG_CTRL_LNX0_REG_O26A0_T
#define O26_A0_MCRG_CTRL_CCO_BASE                0xCC8A0000
#define O26_A0_MCRG_CTRL_CCO_TYPE                MCRG_CTRL_CCO_REG_O26A0_T
#define O26_A0_BCRG_CTRL_GSC_BASE                0xCCC91000
#define O26_A0_BCRG_CTRL_GSC_TYPE                BCRG_CTRL_GSC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_SRCOSB_BASE             0xCCD10000
#define O26_A0_SCRG_CTRL_SRCOSB_TYPE             SCRG_CTRL_SRCOSB_REG_O26A0_T
#define O26_A0_BCRG_CTRL_IMX_BASE                0xCCC31000
#define O26_A0_BCRG_CTRL_IMX_TYPE                BCRG_CTRL_IMX_REG_O26A0_T
#define O26_A0_SCRG_CTRL_ION1_BASE               0xC4680000
#define O26_A0_SCRG_CTRL_ION1_TYPE               SCRG_CTRL_ION1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_M1_BASE                 0xC4D20000
#define O26_A0_SCRG_CTRL_M1_TYPE                 SCRG_CTRL_M1_REG_O26A0_T
#define O26_A0_CPU_SCRG_CTRL_EPHY_BASE           0xCA380000
#define O26_A0_CPU_SCRG_CTRL_EPHY_TYPE           MICOM_SCRG_CTRL_EPHY_REG_O26A0_T
#define O26_A0_MICOM_SCRG_CTRL_EPHY_BASE         0xF3380000
#define O26_A0_MICOM_SCRG_CTRL_EPHY_TYPE         MICOM_SCRG_CTRL_EPHY_REG_O26A0_T
#define O26_A0_SCRG_CTRL_M0_BASE                 0xC4920000
#define O26_A0_SCRG_CTRL_M0_TYPE                 SCRG_CTRL_M0_REG_O26A0_T
#define O26_A0_MCRG_CTRL_HDMI_BASE               0xC8770000
#define O26_A0_MCRG_CTRL_HDMI_TYPE               MCRG_CTRL_HDMI_REG_O26A0_T
#define O26_A0_BCRG_CTRL_DNSR_BASE               0xCC4C1000
#define O26_A0_BCRG_CTRL_DNSR_TYPE               BCRG_CTRL_DNSR_REG_O26A0_T
#define O26_A0_BCRG_CTRL_VENC_BASE               0xCE471000
#define O26_A0_BCRG_CTRL_VENC_TYPE               BCRG_CTRL_VENC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_HDMI_BASE               0xC8740000
#define O26_A0_SCRG_CTRL_HDMI_TYPE               SCRG_CTRL_HDMI_REG_O26A0_T
#define O26_A0_CPU_SCRG_CTRL_MICOM_BASE          0xCA390000
#define O26_A0_CPU_SCRG_CTRL_MICOM_TYPE          MICOM_SCRG_CTRL_MICOM_REG_O26A0_T
#define O26_A0_MICOM_SCRG_CTRL_MICOM_BASE        0xF3390000
#define O26_A0_MICOM_SCRG_CTRL_MICOM_TYPE        MICOM_SCRG_CTRL_MICOM_REG_O26A0_T
#define O26_A0_SCRG_CTRL_FMS_BASE                0xCC310000
#define O26_A0_SCRG_CTRL_FMS_TYPE                SCRG_CTRL_FMS_REG_O26A0_T
#define O26_A0_SCRG_CTRL_EDPTX_BASE              0xC6BB0000
#define O26_A0_SCRG_CTRL_EDPTX_TYPE              SCRG_CTRL_EDPTX_REG_O26A0_T
#define O26_A0_MCRG_CTRL_IMX_BASE                0xCCC30000
#define O26_A0_MCRG_CTRL_IMX_TYPE                MCRG_CTRL_IMX_REG_O26A0_T
#define O26_A0_CPU_SCRG_CTRL_EDID_BASE           0xCA360000
#define O26_A0_CPU_SCRG_CTRL_EDID_TYPE           MICOM_SCRG_CTRL_EDID_REG_O26A0_T
#define O26_A0_MICOM_SCRG_CTRL_EDID_BASE         0xF3360000
#define O26_A0_MICOM_SCRG_CTRL_EDID_TYPE         MICOM_SCRG_CTRL_EDID_REG_O26A0_T
#define O26_A0_SCRG_CTRL_VDO_BASE                0xCC260000
#define O26_A0_SCRG_CTRL_VDO_TYPE                SCRG_CTRL_VDO_REG_O26A0_T
#define O26_A0_MCRG_CTRL_GSC_BASE                0xCCC90000
#define O26_A0_MCRG_CTRL_GSC_TYPE                MCRG_CTRL_GSC_REG_O26A0_T
#define O26_A0_SCRG_CTRL_USB_HS1_BASE            0xC4610000
#define O26_A0_SCRG_CTRL_USB_HS1_TYPE            SCRG_CTRL_USB_HS1_REG_O26A0_T
#define O26_A0_SCRG_CTRL_USB_HS2_BASE            0xC4630000
#define O26_A0_SCRG_CTRL_USB_HS2_TYPE            SCRG_CTRL_USB_HS2_REG_O26A0_T
#define O26_A0_SCRG_CTRL_USB_HS3_BASE            0xC4650000
#define O26_A0_SCRG_CTRL_USB_HS3_TYPE            SCRG_CTRL_USB_HS3_REG_O26A0_T
#define O26_A0_BCRG_CTRL_CCO_BASE                0xCC8A1000
#define O26_A0_BCRG_CTRL_CCO_TYPE                BCRG_CTRL_CCO_REG_O26A0_T
#define O26_A0_MCRG_CTRL_LNX1_BASE               0xCC5C0000
#define O26_A0_MCRG_CTRL_LNX1_TYPE               MCRG_CTRL_LNX1_REG_O26A0_T
#define O26_A0_MCRG_CTRL_ME0_BASE                0xCCCC0000
#define O26_A0_MCRG_CTRL_ME0_TYPE                MCRG_CTRL_ME0_REG_O26A0_T
#define O26_A0_BCRG_CTRL_VD1_BASE                0xCE5A1000
#define O26_A0_BCRG_CTRL_VD1_TYPE                BCRG_CTRL_VD1_REG_O26A0_T
#define O26_A0_MCRG_CTRL_LBM_BASE                0xC4040000
#define O26_A0_MCRG_CTRL_LBM_TYPE                MCRG_CTRL_LBM_REG_O26A0_T
#define O26_A0_BCRG_CTRL_ME1_BASE                0xCCCF1000
#define O26_A0_BCRG_CTRL_ME1_TYPE                BCRG_CTRL_ME1_REG_O26A0_T
#define O26_A0_MCRG_CTRL_VD0_BASE                0xCE520000
#define O26_A0_MCRG_CTRL_VD0_TYPE                MCRG_CTRL_VD0_REG_O26A0_T
#define O26_A0_SCRG_CTRL_GPU_BASE                0xC6040000
#define O26_A0_SCRG_CTRL_GPU_TYPE                SCRG_CTRL_GPU_REG_O26A0_T
#define O26_A0_SCRG_CTRL_LNX1_BASE               0xCC5B0000
#define O26_A0_SCRG_CTRL_LNX1_TYPE               SCRG_CTRL_LNX1_REG_O26A0_T


#define O26_A0_ION0_TOP_CTRL_BASE                0xCA330000
#define O26_A0_ION0_TOP_CTRL_TYPE                ION_TOP_CTRL_REG_O26A0_T
#define O26_A0_ION1_TOP_CTRL_BASE                0xC4670000
#define O26_A0_ION1_TOP_CTRL_TYPE                ION_TOP_CTRL_REG_O26A0_T
#define O26_A0_ION0_IOMUX_PAD_BASE               0xCA331000
#define O26_A0_ION0_IOMUX_PAD_TYPE               FUNC_IOMUX_ION0_PAD_REG_O26A0_T
#define O26_A0_ION0_IOMUX_CORE_BASE              0xCA332000
#define O26_A0_ION0_IOMUX_CORE_TYPE              FUNC_IOMUX_ION0_CORE_REG_O26A0_T
#define O26_A0_ION1_IOMUX_PAD_BASE               0xC4671000
#define O26_A0_ION1_IOMUX_PAD_TYPE               FUNC_IOMUX_ION1_PAD_REG_O26A0_T
#define O26_A0_ION1_IOMUX_CORE_BASE              0xC4672000
#define O26_A0_ION1_IOMUX_CORE_TYPE              FUNC_IOMUX_ION1_CORE_REG_O26A0_T
#define O26_A0_ION0_SRDS12TO3_BASE               0xCA336000
#define O26_A0_ION0_SRDS12TO3_TYPE               SRDS12TO3_REG_O26A0_T
#define O26_A0_ION0_SRDS32TO1_0_BASE             0xCA337000
#define O26_A0_ION0_SRDS32TO1_0_TYPE             SRDS32TO1_REG_O26A0_T
#define O26_A0_ION0_SRDS32TO1_1_BASE             0xCA33A000
#define O26_A0_ION0_SRDS32TO1_1_TYPE             SRDS32TO1_REG_O26A0_T
#define O26_A0_ION1_SRDS12TO3_BASE               0xC4676000
#define O26_A0_ION1_SRDS12TO3_TYPE               SRDS12TO3_REG_O26A0_T
#define O26_A0_ION1_SRDS32TO1_0_BASE             0xC4677000
#define O26_A0_ION1_SRDS32TO1_0_TYPE             SRDS32TO1_REG_O26A0_T

#ifdef __cplusplus
}
#endif

#endif  // __CTOP_CTRL_REG_O26_A0_H__

