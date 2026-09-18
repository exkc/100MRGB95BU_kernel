#ifndef __LGBUS_L18_MPRO_H__
#define __LGBUS_L18_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_L18_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_L18_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	L18_MPRO_PORT_START = 0x20000,
	L18_MPRO_PORT_CPU = 0x20000,
	L18_MPRO_PORT_SIDEKICK,
	L18_MPRO_PORT_PERI,
	L18_MPRO_PORT_GFX,
	L18_MPRO_PORT_TE_ICOD,
	L18_MPRO_PORT_AUD,
	L18_MPRO_PORT_VDEC0_M0,
	L18_MPRO_PORT_VDEC0_M1,
	L18_MPRO_PORT_MCU,
	L18_MPRO_PORT_CCO,
	L18_MPRO_PORT_CVD,
	L18_MPRO_PORT_VDM,
	L18_MPRO_PORT_ND,
	L18_MPRO_PORT_GSC,
	L18_MPRO_PORT_TCON,
	L18_MPRO_PORT_DBB,

	L18_MPRO_PORT_MAX,
}lgbus_l18_port_t;

typedef struct
{
	u32	enable;
	u32 range[L18_MPRO_RANGE_SLOT_CNT*2];
}lgbus_l18_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	ulong					vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	lgbus_mpro_add_t		range[L18_MPRO_RANGE_SLOT_CNT];
	lgbus_l18_mpro_reg_save_t 	reg_save;
}lgbus_l18_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_l18_mpro_func_t;

/* don't call below functions */
extern int LGBUS_L18_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_L18_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_l18_get_ddr_addr(u64 phy_addr);

#endif

