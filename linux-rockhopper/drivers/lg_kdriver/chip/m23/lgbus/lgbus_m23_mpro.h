#ifndef __LGBUS_M23_MPRO_H__
#define __LGBUS_M23_MPRO_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
//#undef	SUPPORT_M23_MPRO_CHIP_KDRV		/* driver is not ready */
#define		SUPPORT_M23_MPRO_CHIP_KDRV		1

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/* memory protector */
typedef enum
{
	M23_MPRO_PORT_START = 0x70000,
	M23_MPRO_PORT_CORE = 0x70000,
	M23_MPRO_PORT_FAST		    ,
	M23_MPRO_PORT_AXI_PERI	    ,
	M23_MPRO_PORT_AHB_PERI	    ,
	M23_MPRO_PORT_LZMA		    ,
	M23_MPRO_PORT_GPU			,//00
	M23_MPRO_PORT_GFX			,//01
	M23_MPRO_PORT_TIV			,//02
	M23_MPRO_PORT_DBB			,//03
	M23_MPRO_PORT_TCON			,//04
	M23_MPRO_PORT_LNE			,//05
	M23_MPRO_PORT_PQE_MCU		,//06
	M23_MPRO_PORT_FMC0			,//07
	M23_MPRO_PORT_FMC1			,//08
	M23_MPRO_PORT_CCO0			,//09
	M23_MPRO_PORT_SRE			,//10
	M23_MPRO_PORT_ND0			,//11
	M23_MPRO_PORT_ME0			,//12
	M23_MPRO_PORT_FMS			,//13
	M23_MPRO_PORT_CVD			,//14
	M23_MPRO_PORT_VDO0			,//15
	M23_MPRO_PORT_VDO1			,//16
	M23_MPRO_PORT_SMX0			,//17
	M23_MPRO_PORT_SMX1			,//18
	M23_MPRO_PORT_DNE0			,//19
	M23_MPRO_PORT_AUD0			,//20
	M23_MPRO_PORT_AUD1			,//21
	M23_MPRO_PORT_VDEC0_M0		,//22
	M23_MPRO_PORT_VDEC0_M1		,//23
	M23_MPRO_PORT_VDEC1_M0		,//24
	M23_MPRO_PORT_VDEC1_M1		,//25
	M23_MPRO_PORT_VDEC_MCU		,//26
	M23_MPRO_PORT_MAX,

}lgbus_M23_port_t;

typedef struct
{
	u32	enable;
	u32 range[M23_MPRO_RANGE_SLOT_CNT*2];
}lgbus_m23_mpro_reg_save_t;

typedef struct
{
	char					*name;
	ulong					base_addr_phy;
	ulong					base_addr;
	u64						vio_addr;
	u32						vio_type;
	u32						isr_cnt;
	lgbus_mpro_add_t		range[M23_MPRO_RANGE_SLOT_CNT];
	lgbus_m23_mpro_reg_save_t 	reg_save;
}lgbus_m23_mpro_t;

typedef struct
{
	int (*init)(void);
	int (*cleanup)(void);
	int (*suspend)(void);
	int (*resume)(void);
}lgbus_m23_mpro_func_t;

/* don't call below functions */
extern int LGBUS_M23_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_M23_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern u64 lgbus_m23_get_ddr_addr(u64 phy_addr);

#endif

