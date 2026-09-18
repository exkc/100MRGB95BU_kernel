#ifndef __LGBUS_O26_MPRO_H__
#define __LGBUS_O26_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_O26_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_O26_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	O26_MPRO_PORT_START = 0x90000,
	O26_MPRO_PORT_CORE = 0x90000,
	O26_MPRO_PORT_FAST		,
	O26_MPRO_PORT_AXI_PERI	,
	O26_MPRO_PORT_AHB_PERI	,
	O26_MPRO_PORT_LZMA		,
	O26_MPRO_PORT_GPU0		,
	O26_MPRO_PORT_GPU1		,
	O26_MPRO_PORT_GFX		,
	O26_MPRO_PORT_LOWBW		,
	O26_MPRO_PORT_TIVVMCU	,
	O26_MPRO_PORT_ME3X1		,
	O26_MPRO_PORT_FMC0		,
	O26_MPRO_PORT_FMC1		,
	O26_MPRO_PORT_FMC2		,
	O26_MPRO_PORT_FMC3		,
	O26_MPRO_PORT_FMS		,
	O26_MPRO_PORT_SRE0		,
	O26_MPRO_PORT_SRE1CCO	,
	O26_MPRO_PORT_ND0		,
	O26_MPRO_PORT_ND1		,
	O26_MPRO_PORT_IMX0		,
	O26_MPRO_PORT_IMX1		,
	O26_MPRO_PORT_IMX2		,
	O26_MPRO_PORT_IMX3		,
	O26_MPRO_PORT_VDO0		,
	O26_MPRO_PORT_VDO1		,
	O26_MPRO_PORT_GSC0		,
	O26_MPRO_PORT_GSC1		,
	O26_MPRO_PORT_GSC2		,
	O26_MPRO_PORT_GSC3		,
	O26_MPRO_PORT_AUD		,
	O26_MPRO_PORT_NPPTCU	,
	O26_MPRO_PORT_LNX0		,
	O26_MPRO_PORT_LNX1		,
	O26_MPRO_PORT_LNX2		,
	O26_MPRO_PORT_VD0A		,
	O26_MPRO_PORT_VD0B		,
	O26_MPRO_PORT_VD1A		,
    O26_MPRO_PORT_VD1B		,
	O26_MPRO_PORT_MAX		,
}lgbus_o26_port_t;

typedef struct
{
	u32	enable;
	u32 range[O26_MPRO_RANGE_SLOT_CNT*2];
}lgbus_o26_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	u64						vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	u32						slot_ctrl;
	lgbus_mpro_add_t		range[O26_MPRO_RANGE_SLOT_CNT];
	lgbus_o26_mpro_reg_save_t 	reg_save;
}lgbus_o26_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_o26_mpro_func_t;

/* don't call below functions */
extern int LGBUS_O26_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_O26_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_o26_get_ddr_addr(u64 phy_addr);
extern int lgbus_o26_mpro_stall_ctrl_module(int port, int ctrl);

#endif

