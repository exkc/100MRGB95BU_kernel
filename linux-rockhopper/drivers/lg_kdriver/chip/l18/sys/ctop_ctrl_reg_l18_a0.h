#ifndef __CTOP_CTRL_REG_L18_A0_H__
#define __CTOP_CTRL_REG_L18_A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "l18f/ctop_pqe_syn_a0_reg.h"
#include "l18f/ctop_bmc_syn_a0_reg.h"
#include "l18f/ctop_micom_syn_a0_reg.h"
#include "l18f/ctop_cpu_syn_a0_reg.h"
#include "l18f/ctop_edid_syn_a0_reg.h"
#include "l18f/ctop_vdec_syn_a0_reg.h"
#include "l18f/ctop_syn_dpe_crc_a0_reg.h"
#include "l18f/ctop_syn_codec_syn_a0_reg.h"
#include "l18f/ctop_syn_mip_syn_a0_reg.h"
#include "l18f/ctop_syn_pqe_syn_a0_reg.h"
#include "l18f/ctop_syn_vdec0_syn_a0_reg.h"
#include "l18f/ctop_syn_m0_syn_a0_reg.h"
#include "l18f/ctop_syn_cpu_syn_a0_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* below was added, manually. */

typedef struct {
	BMC_SYN_REG_L18F_A0        * BMC;
	CPU_SYN_REG_L18F_A0        * CPU;
	EDID_SYN_REG_L18F_A0       * EDID;
	MICOM_SYN_REG_L18F_A0      * MICOM;
	PQE_SYN_REG_L18F_A0        * PQE;
	VDEC_SYN_REG_L18F_A0       * VDEC;

	SYN_CODEC_SYN_REG_L18F_A0  * CODEC_SYN;
	SYN_CPU_SYN_REG_L18F_A0    * CPU_SYN;
	SYN_DPE_CRC_REG_L18F_A0    * DPE_CRC;
	SYN_M0_SYN_REG_L18F_A0     * M0_SYN;
	SYN_MIP_SYN_REG_L18F_A0    * MIP_SYN;
	SYN_PQE_SYN_REG_L18F_A0    * PQE_SYN;
	SYN_VDEC0_SYN_REG_L18F_A0  * VDEC0_SYN;

} CTOP_REG_L18A0_T;

/* CTOP */
#define L18_A0_CTOP_BMC_BASE    0xC930E400            //0xC930_E400
#define L18_A0_CTOP_BMC_TYPE    BMC_SYN_REG_L18F_A0

#define L18_A0_CTOP_CPU_BASE    0xC9230400            //0xC923_0400
#define L18_A0_CTOP_CPU_TYPE    CPU_SYN_REG_L18F_A0

#define L18_A0_CTOP_EDID_BASE   0xC9303000            //0xC930_3000
#define L18_A0_CTOP_EDID_TYPE   EDID_SYN_REG_L18F_A0

#define L18_A0_CTOP_MICOM_BASE  0xC930C400            //0xC930_C400
#define L18_A0_CTOP_MICOM_TYPE  MICOM_SYN_REG_L18F_A0

#define L18_A0_CTOP_PQE_BASE    0xC9300100            //0xC930_0100
#define L18_A0_CTOP_PQE_TYPE    PQE_SYN_REG_L18F_A0

#define L18_A0_CTOP_VDEC_BASE   0xC9C70400            //0xC9C7_0400
#define L18_A0_CTOP_VDEC_TYPE   VDEC_SYN_REG_L18F_A0

/* CTOP SYNC */
#define L18_A0_CTOP_CODEC_SYN_BASE   0xC9C50000            //0xC9C5_0000
#define L18_A0_CTOP_CODEC_SYN_TYPE   SYN_CODEC_SYN_REG_L18F_A0

#define L18_A0_CTOP_CPU_SYN_BASE     0xC9230000            //0xC923_0000
#define L18_A0_CTOP_CPU_SYN_TYPE     SYN_CPU_SYN_REG_L18F_A0

#define L18_A0_CTOP_DPE_CRC_BASE     0xC930AC00            //0xC930_AC00
#define L18_A0_CTOP_DPE_CRC_TYPE     SYN_DPE_CRC_REG_L18F_A0

#define L18_A0_CTOP_M0_SYN_BASE      0xC9908000            //0xC990_8000
#define L18_A0_CTOP_M0_SYN_TYPE      SYN_M0_SYN_REG_L18F_A0

#define L18_A0_CTOP_MIP_SYN_BASE     0xC930E000            //0xC930_E000
#define L18_A0_CTOP_MIP_SYN_TYPE     SYN_MIP_SYN_REG_L18F_A0

#define L18_A0_CTOP_PQE_SYN_BASE     0xC9300000            //0xC930_0000
#define L18_A0_CTOP_PQE_SYN_TYPE     SYN_PQE_SYN_REG_L18F_A0

#define L18_A0_CTOP_VDEC0_SYN_BASE   0xC9C70000            //0xC9C7_0000
#define L18_A0_CTOP_VDEC0_SYN_TYPE   SYN_VDEC0_SYN_REG_L18F_A0


#ifdef __cplusplus
}
#endif

#endif	/* __CTOP_CTRL_REG_L18_A0_H__ */

