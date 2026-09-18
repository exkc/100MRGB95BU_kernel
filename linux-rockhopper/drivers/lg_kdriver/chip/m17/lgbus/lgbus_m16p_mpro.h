#ifndef __LGBUS_M16P_MPRO_H__
#define __LGBUS_M16P_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_M16P_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_M16P_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	M16P_MPRO_PORT_START = 0x20000,
	M16P_MPRO_PORT_CPU = 0x20000,
	M16P_MPRO_PORT_PERI,
	M16P_MPRO_PORT_LZMA,
	M16P_MPRO_PORT_FME0,
	M16P_MPRO_PORT_FME1,
	//M16P_MPRO_PORT_CPU_M0,
	M16P_MPRO_PORT_GPU,
	M16P_MPRO_PORT_GFX_M0,
	M16P_MPRO_PORT_VENC_TE,
	M16P_MPRO_PORT_AUD,
	M16P_MPRO_PORT_VDEC0_M0,
	M16P_MPRO_PORT_VDEC0_M1,
	M16P_MPRO_PORT_VDEC1_M0,
	M16P_MPRO_PORT_VDEC1_M1,
	M16P_MPRO_PORT_MCU,
	M16P_MPRO_PORT_CCO,
	M16P_MPRO_PORT_FMC_M0,
	M16P_MPRO_PORT_FMC_M1,
	M16P_MPRO_PORT_TCON,
	//M16P_MPRO_PORT_CPU_M1,
	M16P_MPRO_PORT_CVD,
	M16P_MPRO_PORT_SRE_VDM0,
	M16P_MPRO_PORT_VDM1,
	M16P_MPRO_PORT_SMX0,
	M16P_MPRO_PORT_SMX1,
	M16P_MPRO_PORT_ND0,
	M16P_MPRO_PORT_GSC0,
	M16P_MPRO_PORT_GSC1,
	M16P_MPRO_PORT_FMS0,
	M16P_MPRO_PORT_DBB,
	M16P_MPRO_PORT_VENC,

	M16P_MPRO_PORT_MAX,
}lgbus_m16p_port_t;

typedef struct
{
	u32	enable;
	u32 range[M16P_MPRO_RANGE_SLOT_CNT*2];
}lgbus_m16p_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	ulong					vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	lgbus_mpro_add_t		range[M16P_MPRO_RANGE_SLOT_CNT];
	lgbus_m16p_mpro_reg_save_t 	reg_save;
}lgbus_m16p_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_m16p_mpro_func_t;

/* don't call below functions */
extern int LGBUS_M16P_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_M16P_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_m16p_get_ddr_addr(u64 phy_addr);

#endif

