#ifndef __LGBUS_O24_MPRO_H__
#define __LGBUS_O24_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_O24_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_O24_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	O24_MPRO_PORT_START = 0x80000,
	O24_MPRO_PORT_CORE = 0x80000,
	O24_MPRO_PORT_FAST		,
	O24_MPRO_PORT_AXI_PERI  ,
	O24_MPRO_PORT_AHB_PERI  ,
	O24_MPRO_PORT_LZMA      ,
	O24_MPRO_PORT_GPU0      ,
	O24_MPRO_PORT_GPU1      ,
	O24_MPRO_PORT_GFX       ,
	O24_MPRO_PORT_LOWBW     ,
	O24_MPRO_PORT_ICODVENC  ,
	O24_MPRO_PORT_MEFMS     ,
	O24_MPRO_PORT_FMC0_R    ,
	O24_MPRO_PORT_FMC0_W    ,
	O24_MPRO_PORT_FMC1_R    ,
	O24_MPRO_PORT_FMC1_W    ,
	O24_MPRO_PORT_FMGSSR    ,
	O24_MPRO_PORT_CCO0      ,
	O24_MPRO_PORT_CCO1      ,
	O24_MPRO_PORT_ND0       ,
	O24_MPRO_PORT_ND1       ,
	O24_MPRO_PORT_VDOIMXW0  ,
	O24_MPRO_PORT_VDOIMXW1  ,
	O24_MPRO_PORT_VDOIMXW2  ,
	O24_MPRO_PORT_VDOIMXW3  ,
	O24_MPRO_PORT_IMXR01    ,
	O24_MPRO_PORT_IMXR23    ,
	O24_MPRO_PORT_TCON      ,
	O24_MPRO_PORT_AUD       ,
	O24_MPRO_PORT_LNX0      ,
	O24_MPRO_PORT_LNX1      ,
	O24_MPRO_PORT_LNX2      ,
	O24_MPRO_PORT_VD0A      ,
	O24_MPRO_PORT_VD0B      ,
	O24_MPRO_PORT_VD1A      ,
	O24_MPRO_PORT_VD1B      ,
	O24_MPRO_PORT_VD2VMCU   ,
	O24_MPRO_PORT_VD2B      ,
	O24_MPRO_PORT_MAX,

}lgbus_o24_port_t;

typedef struct
{
	u32	enable;
	u32 range[O24_MPRO_RANGE_SLOT_CNT*2];
}lgbus_o24_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	u64						vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	u32						slot_ctrl;
	lgbus_mpro_add_t		range[O24_MPRO_RANGE_SLOT_CNT];
	lgbus_o24_mpro_reg_save_t 	reg_save;
}lgbus_o24_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_o24_mpro_func_t;

/* don't call below functions */
extern int LGBUS_O24_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_O24_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_o24_get_ddr_addr(u64 phy_addr);
extern int lgbus_o24_mpro_stall_ctrl_module(int port, int ctrl);

#endif

