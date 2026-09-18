#ifndef __LGBUS_O22_MPRO_H__
#define __LGBUS_O22_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_O22_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_O22_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	O22_MPRO_PORT_START = 0x60000,
	O22_MPRO_PORT_CORE = 0x60000,
	O22_MPRO_PORT_AXI_PERI	,
	O22_MPRO_PORT_AHB_PERI	,
	O22_MPRO_PORT_LZMA		,
	O22_MPRO_PORT_FAST		,
	O22_MPRO_PORT_GPU		,		//00
	O22_MPRO_PORT_GFX		,      //01
	O22_MPRO_PORT_TIV		,      //02
	O22_MPRO_PORT_AUD0		,      //03
	O22_MPRO_PORT_AUD1		,      //04
	O22_MPRO_PORT_DBB		,      //05
	O22_MPRO_PORT_SRNR		,      //06
	O22_MPRO_PORT_LNE		,      //07
	O22_MPRO_PORT_PQE_MCU	,      //08
	O22_MPRO_PORT_FMC0		,      //09
	O22_MPRO_PORT_FMC1		,      //10
	O22_MPRO_PORT_FMC2		,      //11
	O22_MPRO_PORT_FMC3		,      //12
	O22_MPRO_PORT_CCO0		,      //13
	O22_MPRO_PORT_CCO1		,      //14
	O22_MPRO_PORT_SRE		,      //15
	O22_MPRO_PORT_ND0		,      //16
	O22_MPRO_PORT_ND1		,      //17
	O22_MPRO_PORT_ME0		,      //18
	O22_MPRO_PORT_ME1		,      //19
	O22_MPRO_PORT_SSD		,      //20
	O22_MPRO_PORT_FMS		,      //21
	O22_MPRO_PORT_GSC0		,      //22
	O22_MPRO_PORT_GSC1		,      //23
	O22_MPRO_PORT_DNE0		,      //24
	O22_MPRO_PORT_DNE1		,      //25
	O22_MPRO_PORT_CVD		,      //26
	O22_MPRO_PORT_VDO0		,      //27
	O22_MPRO_PORT_VDO1		,      //28
	O22_MPRO_PORT_VDO2		,      //29
	O22_MPRO_PORT_VDO3		,      //30
	O22_MPRO_PORT_SMX0		,      //31
	O22_MPRO_PORT_SMX1		,      //32
	O22_MPRO_PORT_SMX2		,      //33
	O22_MPRO_PORT_SMX3		,      //34
	O22_MPRO_PORT_VDEC0_M0	,      //35
	O22_MPRO_PORT_VDEC0_M1	,      //36
	O22_MPRO_PORT_VDEC1_M0	,      //37
	O22_MPRO_PORT_VDEC1_M1	,      //38
	O22_MPRO_PORT_VDEC2_M0	,      //39
	O22_MPRO_PORT_VDEC2_M1	,      //40
	O22_MPRO_PORT_VDEC3_M0	,      //41
	O22_MPRO_PORT_VDEC3_M1	,      //42
	O22_MPRO_PORT_VDEC_MCU	,      //43
	O22_MPRO_PORT_MAX,

}lgbus_o22_port_t;

typedef struct
{
	u32	enable;
	u32 range[O22_MPRO_RANGE_SLOT_CNT*2];
}lgbus_o22_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	u64						vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	u32						slot_ctrl;
	lgbus_mpro_add_t		range[O22_MPRO_RANGE_SLOT_CNT];
	lgbus_o22_mpro_reg_save_t 	reg_save;
}lgbus_o22_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_o22_mpro_func_t;

/* don't call below functions */
extern int LGBUS_O22_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_O22_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_o22_get_ddr_addr(u64 phy_addr);
extern int lgbus_o22_mpro_stall_ctrl_module(int port, int ctrl);

#endif

