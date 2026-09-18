#ifndef __LGBUS_M19_MPRO_H__
#define __LGBUS_M19_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_M19_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_M19_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	M19_MPRO_PORT_START = 0x20000,
	M19_MPRO_PORT_CPU = 0x20000,
	M19_MPRO_PORT_PERI,
	M19_MPRO_PORT_LZMA,

	M19_MPRO_PORT_GPU,
	M19_MPRO_PORT_GFX,
	M19_MPRO_PORT_TI,
	M19_MPRO_PORT_AUD,
	M19_MPRO_PORT_VDEC0_M0,
	M19_MPRO_PORT_VDEC0_M1,
	M19_MPRO_PORT_VDEC1_M0,
	M19_MPRO_PORT_VDEC1_M1,
	M19_MPRO_PORT_MCU,
	M19_MPRO_PORT_CCO,
	M19_MPRO_PORT_FMC0,
	M19_MPRO_PORT_FMC1,
	M19_MPRO_PORT_TCON,
	M19_MPRO_PORT_ME0,
	M19_MPRO_PORT_FMS0,
	M19_MPRO_PORT_CVI,
	M19_MPRO_PORT_VDM0,
	M19_MPRO_PORT_SRE,
	M19_MPRO_PORT_VDM1,
	M19_MPRO_PORT_SMX0,
	M19_MPRO_PORT_SMX1,
	M19_MPRO_PORT_ND0,
	M19_MPRO_PORT_ND1,
	M19_MPRO_PORT_GSC0,
	M19_MPRO_PORT_GSC1,
	M19_MPRO_PORT_ME1,
	M19_MPRO_PORT_DBB,
	M19_MPRO_PORT_VENC,

	M19_MPRO_PORT_MAX,
}lgbus_m19_port_t;

typedef struct
{
	u32	enable;
	u32 range[M19_MPRO_RANGE_SLOT_CNT*2];
}lgbus_m19_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	ulong					vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	lgbus_mpro_add_t		range[M19_MPRO_RANGE_SLOT_CNT];
	lgbus_m19_mpro_reg_save_t 	reg_save;
}lgbus_m19_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_m19_mpro_func_t;

/* don't call below functions */
extern int LGBUS_M19_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_M19_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_m19_get_ddr_addr(u64 phy_addr);

#endif

