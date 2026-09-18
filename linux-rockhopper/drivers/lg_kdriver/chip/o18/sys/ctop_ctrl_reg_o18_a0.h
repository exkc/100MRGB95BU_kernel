#ifndef __CTOP_CTRL_REG_O18_A0_H__
#define __CTOP_CTRL_REG_O18_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "o18a0/ctop_meu_a0_reg.h"
#include "o18a0/dpe_crc_a0_reg.h"
#include "o18a0/ctop_sre_a0_reg.h"
#include "o18a0/bnd_ctrl_emmc_a0_reg.h"
#include "o18a0/bnd_ctrl_me1_a0_reg.h"
#include "o18a0/bnd_ctrl_imx_a0_reg.h"
#include "o18a0/bnd_ctrl_nd1_a0_reg.h"
#include "o18a0/ctop_cco_a0_reg.h"
#include "o18a0/bnd_ctrl_cco_a0_reg.h"
#include "o18a0/bnd_ctrl_vdec1_a0_reg.h"
#include "o18a0/bnd_ctrl_edid_a0_reg.h"
#include "o18a0/bnd_ctrl_vd0_a0_reg.h"
#include "o18a0/bmc_syn_a0_reg.h"
#include "o18a0/ctop_dpe_a0_reg.h"
#include "o18a0/bnd_ctrl_tiv_a0_reg.h"
#include "o18a0/bnd_ctrl_gsc_a0_reg.h"
#include "o18a0/ctop_imx_a0_reg.h"
#include "o18a0/bnd_ctrl_bmc_a0_reg.h"
#include "o18a0/reg_bridge_a0_reg.h"
#include "o18a0/bnd_ctrl_gfx_a0_reg.h"
#include "o18a0/vsd_crc_a0_reg.h"
#include "o18a0/bnd_ctrl_mcu_a0_reg.h"
#include "o18a0/bnd_ctrl_cpu_a0_reg.h"
#include "o18a0/bnd_ctrl_tcon_a0_reg.h"
#include "o18a0/ctop_tivg_a0_reg.h"
#include "o18a0/bnd_ctrl_nd0_a0_reg.h"
#include "o18a0/bnd_ctrl_vsd_a0_reg.h"
#include "o18a0/ctop_nd0_a0_reg.h"
#include "o18a0/bnd_ctrl_led_a0_reg.h"
#include "o18a0/bnd_ctrl_gem_a0_reg.h"
#include "o18a0/bnd_ctrl_me0_a0_reg.h"
#include "o18a0/bnd_ctrl_cvi_a0_reg.h"
#include "o18a0/bnd_ctrl_fms_a0_reg.h"
#include "o18a0/bnd_ctrl_sre_a0_reg.h"
#include "o18a0/ctop_me1_a0_reg.h"
#include "o18a0/bnd_ctrl_aud_a0_reg.h"
#include "o18a0/bnd_ctrl_fmc_a0_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct {
/////////////////
	CTOP_MEU_REG_O18_A0       * CTOP_MEU;
	CTOP_SRE_REG_O18_A0       * CTOP_SRE;
	CTOP_CCO_REG_O18_A0       * CTOP_CCO;
	BMC_SYN_REG_O18_A0        * BMC_SYN;
	CTOP_DPE_REG_O18_A0       * CTOP_DPE;
	CTOP_IMX_REG_O18_A0       * CTOP_IMX;
	CTOP_TIVG_REG_O18_A0      * CTOP_TIVG;
	CTOP_ND0_REG_O18_A0       * CTOP_ND0;
	CTOP_ME1_REG_O18_A0       * CTOP_ME1;

////////////////
	DPE_CRC_REG_O18_A0        * DPE_CRC;
	BND_CTRL_EMMC_REG_O18_A0  * CTRL_EMMC;
	BND_CTRL_ME1_REG_O18_A0   * CTRL_ME1;
	BND_CTRL_IMX_REG_O18_A0   * CTRL_IMX;
	BND_CTRL_ND1_REG_O18_A0   * CTRL_ND1;
	BND_CTRL_CCO_REG_O18_A0   * CTRL_CCO;
	BND_CTRL_VDEC1_REG_O18_A0 * CTRL_VDEC1;
	BND_CTRL_EDID_REG_O18_A0  * CTRL_EDID;
	BND_CTRL_VD0_REG_O18_A0   * CTRL_VD0;
	BND_CTRL_TIV_REG_O18_A0   * CTRL_TIV;
	BND_CTRL_GSC_REG_O18_A0   * CTRL_GSC;
	BND_CTRL_BMC_REG_O18_A0   * CTRL_BMC;
	REG_BRIDGE_REG_O18_A0     * REG_BRIDGE;
	BND_CTRL_GFX_REG_O18_A0   * CTRL_GFX;
	VSD_CRC_REG_O18_A0        * VSD_CRC;
	BND_CTRL_MCU_REG_O18_A0   * CTRL_MCU;
	BND_CTRL_CPU_REG_O18_A0   * CTRL_CPU;
	BND_CTRL_TCON_REG_O18_A0  * CTRL_TCON;
	BND_CTRL_ND0_REG_O18_A0   * CTRL_ND0;
	BND_CTRL_VSD_REG_O18_A0   * CTRL_VSD;
	BND_CTRL_LED_REG_O18_A0   * CTRL_LED;
	BND_CTRL_GEM_REG_O18_A0   * CTRL_GEM;
	BND_CTRL_ME0_REG_O18_A0   * CTRL_ME0;
	BND_CTRL_CVI_REG_O18_A0   * CTRL_CVI;
	BND_CTRL_FMS_REG_O18_A0   * CTRL_FMS;
	BND_CTRL_SRE_REG_O18_A0   * CTRL_SRE;
	BND_CTRL_AUD_REG_O18_A0   * CTRL_AUD;
	BND_CTRL_FMC_REG_O18_A0   * CTRL_FMC;


} CTOP_REG_O18A0_T;

/* CTOP */

#define O18_A0_CTOP_MEU_BASE    0xC5FE0000            // 0xC5FE_0000
#define O18_A0_CTOP_MEU_TYPE    CTOP_MEU_REG_O18_A0

#define O18_A0_CTOP_SRE_BASE    0xC97F8000            // 0xC97F_8000
#define O18_A0_CTOP_SRE_TYPE    CTOP_SRE_REG_O18_A0

#define O18_A0_CTOP_CCO_BASE    0xC97D0000            // 0xC97D_0000
#define O18_A0_CTOP_CCO_TYPE    CTOP_CCO_REG_O18_A0

#define O18_A0_BMC_SYN_BASE     0xC7FC0000            // 0xC7FC_0000
#define O18_A0_BMC_SYN_TYPE     BMC_SYN_REG_O18_A0

#define O18_A0_CTOP_DPE_BASE    0xC97C8000            // 0xC97C_8000
#define O18_A0_CTOP_DPE_TYPE    CTOP_DPE_REG_O18_A0

#define O18_A0_CTOP_IMX_BASE    0xC7FD0000            // 0xC7FD_0000
#define O18_A0_CTOP_IMX_TYPE    CTOP_IMX_REG_O18_A0

#define O18_A0_CTOP_TIVG_BASE   0xC987C000            // 0xC987_C000
#define O18_A0_CTOP_TIVG_TYPE   CTOP_TIVG_REG_O18_A0

#define O18_A0_CTOP_ND0_BASE    0xC7FE0000            // 0xC7FE_0000
#define O18_A0_CTOP_ND0_TYPE    CTOP_ND0_REG_O18_A0

#define O18_A0_CTOP_ME1_BASE    0xC5FF0000            // 0xC5FF_0000
#define O18_A0_CTOP_ME1_TYPE    CTOP_ME1_REG_O18_A0


/* CTOP SYNC */
#define O18_A0_DPE_CRC_BASE      0xC917D600            // 0xC917_D600
#define O18_A0_DPE_CRC_TYPE      DPE_CRC_REG_O18_A0

#define O18_A0_CTRL_EMMC_BASE    0xC5FE1000            // 0xC5FE_1000
#define O18_A0_CTRL_EMMC_TYPE    BND_CTRL_EMMC_REG_O18_A0

#define O18_A0_CTRL_ME1_BASE     0xC907E000            // 0xC907_E000
#define O18_A0_CTRL_ME1_TYPE     BND_CTRL_ME1_REG_O18_A0

#define O18_A0_CTRL_IMX_BASE     0xC90FE000            // 0xC90F_E000
#define O18_A0_CTRL_IMX_TYPE     BND_CTRL_IMX_REG_O18_A0

#define O18_A0_CTRL_ND1_BASE     0xC9089000           // 0xC908_9000
#define O18_A0_CTRL_ND1_TYPE     BND_CTRL_ND1_REG_O18_A0

#define O18_A0_CTRL_CCO_BASE     0xC910F000            // 0xC910_F000
#define O18_A0_CTRL_CCO_TYPE     BND_CTRL_CCO_REG_O18_A0

#define O18_A0_CTRL_VDEC1_BASE   0xC9FF0400            // 0xC9FF_0400
#define O18_A0_CTRL_VDEC1_TYPE   BND_CTRL_VDEC1_REG_O18_A0

#define O18_A0_CTRL_EDID_BASE    0xC68F0000            // 0xC68F_0000
#define O18_A0_CTRL_EDID_TYPE    BND_CTRL_EDID_REG_O18_A0

#define O18_A0_CTRL_VD0_BASE     0xC9FF8400            // 0xC9FF_8400
#define O18_A0_CTRL_VD0_TYPE     BND_CTRL_VD0_REG_O18_A0

#define O18_A0_CTRL_TIV_BASE     0xC9878000            // 0xC987_8000
#define O18_A0_CTRL_TIV_TYPE     BND_CTRL_TIV_REG_O18_A0

#define O18_A0_CTRL_GSC_BASE     0xC917E200            // 0xC917_E200
#define O18_A0_CTRL_GSC_TYPE     BND_CTRL_GSC_REG_O18_A0

#define O18_A0_CTRL_BMC_BASE     0xC7FC1000            // 0xC7FC_1000
#define O18_A0_CTRL_BMC_TYPE     BND_CTRL_BMC_REG_O18_A0

#define O18_A0_REG_BRIDGE_BASE   0xC6900000            // 0xC690_0000
#define O18_A0_REG_BRIDGE_TYPE   REG_BRIDGE_REG_O18_A0

#define O18_A0_CTRL_GFX_BASE     0xC987A000            // 0xC987_A000
#define O18_A0_CTRL_GFX_TYPE     BND_CTRL_GFX_REG_O18_A0

#define O18_A0_VSD_CRC_BASE      0xC917E800            // 0xC917_E800
#define O18_A0_VSD_CRC_TYPE      VSD_CRC_REG_O18_A0

#define O18_A0_CTRL_MCU_BASE     0xC97B0000            // 0xC97B_0000
#define O18_A0_CTRL_MCU_TYPE     BND_CTRL_MCU_REG_O18_A0

#define O18_A0_CTRL_CPU_BASE     0xC7FF0000            // 0xC7FF_0000
#define O18_A0_CTRL_CPU_TYPE     BND_CTRL_CPU_REG_O18_A0

#define O18_A0_CTRL_TCON_BASE    0xC917D000            // 0xC917_D000
#define O18_A0_CTRL_TCON_TYPE    BND_CTRL_TCON_REG_O18_A0

#define O18_A0_CTRL_ND0_BASE     0xC9084000            // 0xC908_4000
#define O18_A0_CTRL_ND0_TYPE     BND_CTRL_ND0_REG_O18_A0

#define O18_A0_CTRL_VSD_BASE     0xC917E000           // 0xC917_E000
#define O18_A0_CTRL_VSD_TYPE     BND_CTRL_VSD_REG_O18_A0

#define O18_A0_CTRL_LED_BASE     0xC917D200            // 0xC917_D200
#define O18_A0_CTRL_LED_TYPE     BND_CTRL_LED_REG_O18_A0

#define O18_A0_CTRL_GEM_BASE     0xC7501000           // 0xC750_1000
#define O18_A0_CTRL_GEM_TYPE     BND_CTRL_GEM_REG_O18_A0

#define O18_A0_CTRL_ME0_BASE     0xC907D000           // 0xC907_D000
#define O18_A0_CTRL_ME0_TYPE     BND_CTRL_ME0_REG_O18_A0

#define O18_A0_CTRL_CVI_BASE     0xC90FD000           // 0xC90F_D000
#define O18_A0_CTRL_CVI_TYPE     BND_CTRL_CVI_REG_O18_A0

#define O18_A0_CTRL_FMS_BASE     0xC917F000           // 0xC917_F000
#define O18_A0_CTRL_FMS_TYPE     BND_CTRL_FMS_REG_O18_A0

#define O18_A0_CTRL_SRE_BASE     0xC907F000           // 0xC907_F000
#define O18_A0_CTRL_SRE_TYPE     BND_CTRL_SRE_REG_O18_A0

#define O18_A0_CTRL_AUD_BASE     0xC9870000           // 0xC987_0000
#define O18_A0_CTRL_AUD_TYPE     BND_CTRL_AUD_REG_O18_A0

#define O18_A0_CTRL_FMC_BASE     0xC90FF000           // 0xC90F_F000
#define O18_A0_CTRL_FMC_TYPE     BND_CTRL_FMC_REG_O18_A0

#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_O18_A0_H__ */

