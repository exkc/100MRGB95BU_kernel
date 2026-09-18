/* SIC I2C Reg CSV File to Header File transfer scripte by won.hur(won.hur@lge.com) */ 
/* Version = 0.70 */ 
/* File Build Date : Thu, 27 Jun 2019 05:27:49 +0000  */

/* IP_INFO_O20A0 */
#define	ip_info_O20A0_REG_ADDR	0x0000

/* FENC_DCGEN_CTRL_O20A0 */
#define	fenc_dcgen_ctrl_O20A0_REG_ADDR	0x0010

/* FENC_CLKEN_STATUS_O20A0 */
#define	fenc_clken_status_O20A0_REG_ADDR	0x0014

/* FENC_CONFIG_CTRL_O20A0 */
#define	fenc_config_ctrl_O20A0_REG_ADDR	0x001C

/* FENC_INTR_MASK_O20A0 */
#define	fenc_intr_mask_O20A0_REG_ADDR	0x0020

/* FENC_INTR_CLEAR_O20A0 */
#define	fenc_intr_clear_O20A0_REG_ADDR	0x0024

/* FENC_INTR_STATUS_O20A0 */
#define	fenc_intr_status_O20A0_REG_ADDR	0x0028

/* END OF ADDR DEFINITION */


typedef struct
{
	UINT32
		info:32;		// 31:0
} IP_INFO_O20A0_T;



typedef struct
{
	UINT32
		rsenc_dcgen:1,		// 0:0
		syncctrl_dcgen:1,		// 1:1
		regwrap_sys_dcgen:1,		// 2:2
		regwrap_apb_dcgen:1,		// 3:3
		reserved:28;		// 31:4
} FENC_DCGEN_CTRL_O20A0_T;



typedef struct
{
	UINT32
		rsenc_clken:1,		// 0:0
		syncctrl_clken:1,		// 1:1
		regwrap_sys_clken:1,		// 2:2
		regwrap_apb_clken:1,		// 3:3
		reserved:28;		// 31:4
} FENC_CLKEN_STATUS_O20A0_T;



typedef struct
{
	UINT32
		cfg_datasize:6,		// 5:0
		reserved0:2,		// 7:6
		cfg_datasize_last:6,		// 13:8
		reserved1:2,		// 15:14
		cfg_hactive_splnum:6,		// 21:16
		reserved2:9,		// 30:22
		core_enable:1;		//31
} FENC_CONFIG_CTRL_O20A0_T;



typedef struct
{
	UINT32
		rsenc_intr_mask:2,		// 1:0
		syncctrl_intr_mask:1,		// 2:2
		reserved:29;		// 31:3
} FENC_INTR_MASK_O20A0_T;



typedef struct
{
	UINT32
		rsenc_intr_clear:2,		// 1:0
		syncctrl_intr_clear:1,		// 2:2
		reserved:29;		// 31:3
} FENC_INTR_CLEAR_O20A0_T;



typedef struct
{
	UINT32
		rsenc_intr:2,		// 1:0
		syncctrl_intr:1,		// 2:2
		reserved:29;		// 31:3
} FENC_INTR_STATUS_O20A0_T;


typedef struct {
	IP_INFO_O20A0_T		ip_info;
	FENC_DCGEN_CTRL_O20A0_T		fenc_dcgen_ctrl;
	FENC_CLKEN_STATUS_O20A0_T		fenc_clken_status;
	FENC_CONFIG_CTRL_O20A0_T		fenc_config_ctrl;
	FENC_INTR_MASK_O20A0_T		fenc_intr_mask;
	FENC_INTR_CLEAR_O20A0_T		fenc_intr_clear;
	FENC_INTR_STATUS_O20A0_T		fenc_intr_status;
} HDMI21_FEC_TOP_REG_O20A0_T;
