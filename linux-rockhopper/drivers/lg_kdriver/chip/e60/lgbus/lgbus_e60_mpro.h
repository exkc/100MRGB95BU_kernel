#ifndef __LGBUS_E60_MPRO_H__
#define __LGBUS_E60_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_E60_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_E60_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	E60_MPRO_PORT_START = 0x50000,
	E60_MPRO_PORT_CORE = 0x50000,
	E60_MPRO_PORT_AXI_PERI,
	E60_MPRO_PORT_AHB_PERI,
	E60_MPRO_PORT_LZMA,
	E60_MPRO_PORT_FAST,
	E60_MPRO_PORT_GPU,
	E60_MPRO_PORT_GFX,
	E60_MPRO_PORT_TIV,
	E60_MPRO_PORT_AUD,
	E60_MPRO_PORT_WOV,
	E60_MPRO_PORT_DBB,
	E60_MPRO_PORT_LGSR,				//#define		E60_MPRO_PORT_SMX3			0xC9823C00 , common address (read only + write only)
	E60_MPRO_PORT_OASR,
	E60_MPRO_PORT_LNE,
	E60_MPRO_PORT_VDEC0_M0,
	E60_MPRO_PORT_VDEC0_M1,
	E60_MPRO_PORT_VDEC1_M0,
	E60_MPRO_PORT_VDEC1_M1,
	E60_MPRO_PORT_VDEC2A_M0,
	E60_MPRO_PORT_VDEC2A_M1,
	E60_MPRO_PORT_VDEC2B_M0,
	E60_MPRO_PORT_VDEC2B_M1,
	E60_MPRO_PORT_VDEC3A_M0,
	E60_MPRO_PORT_VDEC3A_M1,
	E60_MPRO_PORT_VDEC3B_M0,
	E60_MPRO_PORT_VDEC3B_M1,
	E60_MPRO_PORT_MCU,
	E60_MPRO_PORT_FMC0,
	E60_MPRO_PORT_FMC1,
	E60_MPRO_PORT_FMC2,
	E60_MPRO_PORT_FMC3,
	E60_MPRO_PORT_FMC4,
	E60_MPRO_PORT_FMC5,
	E60_MPRO_PORT_FMC6,
	E60_MPRO_PORT_FMC7,
	E60_MPRO_PORT_GSC0,
	E60_MPRO_PORT_GSC1,
	E60_MPRO_PORT_GSC2,
	E60_MPRO_PORT_GSC3,
	E60_MPRO_PORT_GSC4,				//#define		E60_MPRO_PORT_SRE0			0xC9827800 , common address (read only + write only)
	E60_MPRO_PORT_GSC5,				//#define		E60_MPRO_PORT_SRE1			0xC9827A00 , common address (read only + write only)
	E60_MPRO_PORT_CCO0,
	E60_MPRO_PORT_CCO1,
	E60_MPRO_PORT_SMX0,
	E60_MPRO_PORT_SMX1,
	E60_MPRO_PORT_SMX2,
	E60_MPRO_PORT_SMX4,
	E60_MPRO_PORT_SMX5,				//#define		E60_MPRO_PORT_ND2			0xC9829800 , common address (read only + write only)
	E60_MPRO_PORT_SMX6,
	E60_MPRO_PORT_SMX7,
	E60_MPRO_PORT_VDM0,
	E60_MPRO_PORT_VDM1,
	E60_MPRO_PORT_VDM2,
	E60_MPRO_PORT_VDM3,
	E60_MPRO_PORT_ND0,
	E60_MPRO_PORT_ND1,
	E60_MPRO_PORT_ME0,
	E60_MPRO_PORT_SSD,
	E60_MPRO_PORT_ME1,
	E60_MPRO_PORT_FMS0,
	E60_MPRO_PORT_FMS1,
	E60_MPRO_PORT_CVD,
	E60_MPRO_PORT_OBD,
	E60_MPRO_PORT_MAX,
}lgbus_e60_port_t;

typedef struct
{
	u32	enable;
	u32 range[E60_MPRO_RANGE_SLOT_CNT*2];
}lgbus_e60_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	u64						vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	lgbus_mpro_add_t		range[E60_MPRO_RANGE_SLOT_CNT];
	lgbus_e60_mpro_reg_save_t 	reg_save;
}lgbus_e60_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_e60_mpro_func_t;

/* don't call below functions */
extern int LGBUS_E60_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_E60_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_e60_get_ddr_addr(u64 phy_addr);

#endif

