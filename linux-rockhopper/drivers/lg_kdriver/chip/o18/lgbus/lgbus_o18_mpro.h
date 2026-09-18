#ifndef __LGBUS_O18_MPRO_H__
#define __LGBUS_O18_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_O18_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_O18_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	O18_MPRO_PORT_START = 0x30000,
	O18_MPRO_PORT_CORE = 0x30000,
	O18_MPRO_PORT_AXI_PERI,
	O18_MPRO_PORT_AHB_PERI,
	O18_MPRO_PORT_LZMA,
	O18_MPRO_PORT_GFX,
	O18_MPRO_PORT_AUD,
	O18_MPRO_PORT_TCON,
	O18_MPRO_PORT_TIV,
	O18_MPRO_PORT_VDEC0_M0,
	O18_MPRO_PORT_VDEC0_M1,
	O18_MPRO_PORT_VDEC1_M0,
	O18_MPRO_PORT_VDEC1_M1,
	O18_MPRO_PORT_FMS,
	O18_MPRO_PORT_ME0,
	O18_MPRO_PORT_SSD,
	O18_MPRO_PORT_ME1,
	O18_MPRO_PORT_MCU,
	O18_MPRO_PORT_GPU,
	O18_MPRO_PORT_FMC0,
	O18_MPRO_PORT_FMC1,
	O18_MPRO_PORT_FMC2,
	O18_MPRO_PORT_FMC3,
	O18_MPRO_PORT_CCO,
	O18_MPRO_PORT_GSC0,
	O18_MPRO_PORT_GSC1,
	O18_MPRO_PORT_VDM0,
	O18_MPRO_PORT_SRE_VDM1,
	O18_MPRO_PORT_SMX0,
	O18_MPRO_PORT_SMX1,
	O18_MPRO_PORT_SMX2,
	O18_MPRO_PORT_SMX3,
	O18_MPRO_PORT_ND0,
	O18_MPRO_PORT_ND1,
	O18_MPRO_PORT_CVD,
	O18_MPRO_PORT_DBB,
	O18_MPRO_PORT_MAX,
}lgbus_o18_port_t;

typedef struct
{
	u32	enable;
	u32 range[O18_MPRO_RANGE_SLOT_CNT*2];
}lgbus_o18_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	u64						vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	lgbus_mpro_add_t		range[O18_MPRO_RANGE_SLOT_CNT];
	lgbus_o18_mpro_reg_save_t 	reg_save;
}lgbus_o18_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_o18_mpro_func_t;

/* don't call below functions */
extern int LGBUS_O18_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_O18_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_o18_get_ddr_addr(u64 phy_addr);

#endif

