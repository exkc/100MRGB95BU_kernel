/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 

#ifndef _IPC_REG_M17A0_H_
#define _IPC_REG_M17A0_H_

/*-----------------------------------------------------------------------------
		0xc8026000L set_reg_ctrl0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 run_stall                          : 1 ;  //     0     
	UINT32 start_vector_sel                   : 1 ;  //     1     
	UINT32 p_debug_enable                     : 1 ;  //     2     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 external_interrupt_en              : 1 ;  //     4     
} M17A0_SET_REG_CTRL0_T;

/*-----------------------------------------------------------------------------
		0xc8026004L set_reg_ctrl1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 prid                               : 16;  // 15: 0     
} M17A0_SET_REG_CTRL1_T;

/*-----------------------------------------------------------------------------
		0xc8026008L ext_intr_event ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_event_arm            : 31;  // 30: 0     
	UINT32 wdg_interrupt_event                : 1 ;  //    31     
} M17A0_EXT_INTR_EVENT_T;

/*-----------------------------------------------------------------------------
		0xc802600cL ext_intr_enable ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_enable_arm           : 31;  // 30: 0     
	UINT32 wdg_interrupt_enable               : 1 ;  //    31     
} M17A0_EXT_INTR_ENABLE_T;

/*-----------------------------------------------------------------------------
		0xc8026010L ext_intr_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_status_arm           : 31;  // 30: 0     
	UINT32 wdg_interrupt_status               : 1 ;  //    31     
} M17A0_EXT_INTR_STATUS_T;

/*-----------------------------------------------------------------------------
		0xc8026014L ext_intr_clear ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_clear_arm            : 31;  // 30: 0     
	UINT32 wdg_interrupt_clear                : 1 ;  //    31     
} M17A0_EXT_INTR_CLEAR_T;

/*-----------------------------------------------------------------------------
		0xc8026018L int_intr_event ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_event_mcu            : 30;  // 29: 0     
	UINT32 edma_interrupt_event_mcu           : 1 ;  //    30     
} M17A0_INT_INTR_EVENT_T;

/*-----------------------------------------------------------------------------
		0xc802601cL int_intr_enable ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_enable_mcu           : 30;  // 29: 0     
	UINT32 edma_interrupt_enable_mcu          : 1 ;  //    30     
} M17A0_INT_INTR_ENABLE_T;

/*-----------------------------------------------------------------------------
		0xc8026020L int_intr_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_staus_mcu            : 30;  // 29: 0     
	UINT32 edma_interrupt_status_mcu          : 1 ;  //    30     
} M17A0_INT_INTR_STATUS_T;

/*-----------------------------------------------------------------------------
		0xc8026024L int_intr_clear ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_clear_mcu            : 30;  // 29: 0     
	UINT32 edma_interrupt_clear_mcu           : 1 ;  //    30     
} M17A0_INT_INTR_CLEAR_T;

/*-----------------------------------------------------------------------------
		0xc8026028L srom_boot_map1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 boot_img_map1                      : 32;  // 31: 0     
} M17A0_SROM_BOOT_MAP1_T;

/*-----------------------------------------------------------------------------
		0xc802602cL srom_boot_map2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 boot_img_map2                      : 32;  // 31: 0     
} M17A0_SROM_BOOT_MAP2_T;

/*-----------------------------------------------------------------------------
		0xc8026030L sram_port_sel ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram0_port_sel                     : 4 ;  //  3: 0     
	UINT32 sram1_port_sel                     : 4 ;  //  7: 4     
	UINT32 sram2_port_sel                     : 4 ;  // 11: 8     
	UINT32 sram3_port_sel                     : 4 ;  // 15:12     
	UINT32 reserved                           : 1 ;  //    16     
} M17A0_SRAM_PORT_SEL_T;

/*-----------------------------------------------------------------------------
		0xc8026034L pdebug_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_status                      : 8 ;  //  7: 0     
} M17A0_PDEBUG_STATUS_T;

/*-----------------------------------------------------------------------------
		0xc8026038L pdebug_data ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_data                        : 32;  // 31: 0     
} M17A0_PDEBUG_DATA_T;

/*-----------------------------------------------------------------------------
		0xc802603cL pdebug_pc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_pc                          : 32;  // 31: 0     
} M17A0_PDEBUG_PC_T;

/*-----------------------------------------------------------------------------
		0xc8026040L axi_user_id ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aw_user_id                         : 4 ;  //  3: 0     
	UINT32 ar_user_id                         : 4 ;  //  7: 4     
} M17A0_AXI_USER_ID_T;

/*-----------------------------------------------------------------------------
		0xc8026044L sram0_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram0_offset                       : 32;  // 31: 0     
} M17A0_SRAM0_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xc8026048L sram1_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram1_offset                       : 32;  // 31: 0     
} M17A0_SRAM1_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xc802604cL sram2_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram2_offset                       : 32;  // 31: 0     
} M17A0_SRAM2_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xc8026050L sram3_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram3_offset                       : 32;  // 31: 0        
} M17A0_SRAM3_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xc802605cL spp_mcu_version ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mcu_version                        : 32;  // 31: 0     
} M17A0_SPP_MCU_VERSION_T;

/*-----------------------------------------------------------------------------
		0xc8026060L intr_mcu_flag ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_intr_mcu                       : 1 ;  //     0     
	UINT32 imx_intr_mcu                       : 1 ;  //     1     
	UINT32 nd1_mcu_intr_mcu                   : 1 ;  //     2     
	UINT32 fme_mcu_intr_mcu                   : 1 ;  //     3     
	UINT32 fmc_mcu_intr_mcu                   : 1 ;  //     4     
	UINT32 gsc_mcu_intr_mcu                   : 1 ;  //     5     
	UINT32 sre_mcu_intr_mcu                   : 1 ;  //     6     
	UINT32 vsd_mcu_intr0_mcu                  : 1 ;  //     7     
	UINT32 vsd_mcu_intr1_mcu                  : 1 ;  //     8     
	UINT32 vsd_mcu_intr2_mcu                  : 1 ;  //     9     
	UINT32 cco_mcu_intr_mcu                   : 1 ;  //    10     
	UINT32 dpe_mcu_intr_mcu                   : 1 ;  //    11     
	UINT32 sub_mcu_intr_mcu                   : 1 ;  //    12     
	UINT32 reserved                           : 19;  // 31:13     
} M17A0_INTR_MCU_FLAG_T;

/*-----------------------------------------------------------------------------
		0xc8026064L intr_mcu_flag_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_intr_mcu_en                    : 1 ;  //     0     
	UINT32 imx_intr_mcu_en                    : 1 ;  //     1     
	UINT32 nd1_mcu_intr_mcu_en                : 1 ;  //     2     
	UINT32 fme_mcu_intr_mcu_en                : 1 ;  //     3     
	UINT32 fmc_mcu_intr_mcu_en                : 1 ;  //     4     
	UINT32 gsc_mcu_intr_mcu_en                : 1 ;  //     5     
	UINT32 sre_mcu_intr_mcu_en                : 1 ;  //     6     
	UINT32 vsd_mcu_intr0_mcu_en               : 1 ;  //     7     
	UINT32 vsd_mcu_intr1_mcu_en               : 1 ;  //     8     
	UINT32 vsd_mcu_intr2_mcu_en               : 1 ;  //     9     
	UINT32 cco_mcu_intr_mcu_en                : 1 ;  //    10     
	UINT32 dpe_mcu_intr_mcu_en                : 1 ;  //    11     
	UINT32 sub_mcu_intr_mcu_en                : 1 ;  //    12     
	UINT32 reserved                           : 19;  // 31:13     
} M17A0_INTR_MCU_FLAG_EN_T;

/*-----------------------------------------------------------------------------
		0xc8026068L intr_cpu_flag ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_mcu_intr_cpu                 :1;	//0 //
	UINT32 imx_mcu_intr_cpu                 :1;	//1 //
	UINT32 hdr_mcu_intr_cpu                 :1;	//2 //
	UINT32 nd0_mcu_intr_cpu                 :1;	//3 //
	UINT32 me0_mcu_intr_cpu                 :1;	//4 //
	UINT32 me1_mcu_intr_cpu                 :1;	//5 //
	UINT32 fmc_mcu_intr_cpu                 :1;	//6 //
	UINT32 fms_mcu_intr_cpu                 :1;	//7 //
	UINT32 gsc_mcu_intr_cpu                 :1;	//8 //
	UINT32 sre_mcu_intr_cpu                 :1;	//9 //
	UINT32 vsd_mcu_intr_cpu                 :1;	//10 //
	UINT32 cco_mcu_intr_cpu                 :1;	//11 //
	UINT32 dpe_mcu_intr_cpu                 :1;	//12 //
	UINT32 vdec_mcu_intr_cpu                :1;	//13 //VDEC to MCU interrupt
	UINT32 mcu_vdec_intr_cpu                :1;	//14 //MCU to VDEC interrupt
	UINT32 reserved                         :17;	//31:15	//
} M17A0_INTR_CPU_FLAG_T;

/*-----------------------------------------------------------------------------
		0xc802606cL intr_cpu_flag_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_mcu_intr_cpu_en              :1;	//0 //
	UINT32 imx_mcu_intr_cpu_en              :1;	//1 //
	UINT32 hdr_mcu_intr_cpu_en              :1;	//2 //
	UINT32 nd0_mcu_intr_cpu_en              :1;	//3 //
	UINT32 me0_mcu_intr_cpu_en              :1;	//4 //
	UINT32 me1_mcu_intr_cpu_en              :1;	//5 //
	UINT32 fmc_mcu_intr_cpu_en              :1;	//6 //
	UINT32 fms_mcu_intr_cpu_en              :1;	//7 //
	UINT32 gsc_mcu_intr_cpu_en              :1;	//8 //
	UINT32 sre_mcu_intr_cpu_en              :1;	//9 //
	UINT32 vsd_mcu_intr_cpu_en              :1;	//10 //
	UINT32 cco_mcu_intr_cpu_en              :1;	//11 //
	UINT32 dpe_mcu_intr_cpu_en              :1;	//12 //
	UINT32 vdec_mcu_intr_cpu_en             :1;	//13 //
	UINT32 mcu_vdec_intr_cpu_en             :1;	//14 //
	UINT32 reserved                         :17;	//31:15	//
} M17A0_INTR_CPU_FLAG_EN_T;

/*-----------------------------------------------------------------------------
		0xc8026100L cpu_ipc0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc                                : 32;  // 31: 0     
} M17A0_CPU_IPC0_T;

/*-----------------------------------------------------------------------------
		0xc80261fcL cpu_ipc63 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc                                : 32;  // 31: 0     
} M17A0_CPU_IPC63_T;

/*-----------------------------------------------------------------------------
		0xc80262fcL vdec_intr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vdec_interrupt                     : 1 ;  //     0     
} M17A0_VDEC_INTR_T;

/*-----------------------------------------------------------------------------
		0xc8026400L tx_locked_id ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_locked_id                       : 32;  // 31: 0     
} M17A0_TX_LOCKED_ID_T;

/*-----------------------------------------------------------------------------
		0xc8026404L tx_src_addr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_src_addr                        : 32;  // 31: 0     
} M17A0_TX_SRC_ADDR_T;

/*-----------------------------------------------------------------------------
		0xc8026408L tx_dst_addr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_dst_addr                        : 32;  // 31: 0     
} M17A0_TX_DST_ADDR_T;

/*-----------------------------------------------------------------------------
		0xc802640cL tx_nxt_addr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_nxt_addr                        : 32;  // 31: 0     
} M17A0_TX_NXT_ADDR_T;

/*-----------------------------------------------------------------------------
		0xc8026410L tx_length ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_length                          : 32;  // 31: 0     
} M17A0_TX_LENGTH_T;

/*-----------------------------------------------------------------------------
		0xc8026414L edma_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_start                           : 1 ;  //     0     
	UINT32 tx_dir                             : 3 ;  //  3: 1     
	UINT32 tx_nxt_dir                         : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 tx_done                            : 1 ;  //     8     
	UINT32 tx_locked                          : 1 ;  //     9     
	UINT32 tx_switch_en                       : 1 ;  //    10     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 tx_atomic_size                     : 2 ;  // 13:12     
} M17A0_EDMA_CTRL_T;

typedef struct {
	M17A0_SET_REG_CTRL0_T              	set_reg_ctrl0;                //0xc8026000L
	M17A0_SET_REG_CTRL1_T              	set_reg_ctrl1;                //0xc8026004L
	M17A0_EXT_INTR_EVENT_T             	ext_intr_event;               //0xc8026008L
	M17A0_EXT_INTR_ENABLE_T            	ext_intr_enable;              //0xc802600cL
	M17A0_EXT_INTR_STATUS_T            	ext_intr_status;              //0xc8026010L
	M17A0_EXT_INTR_CLEAR_T             	ext_intr_clear;               //0xc8026014L
	M17A0_INT_INTR_EVENT_T             	int_intr_event;               //0xc8026018L
	M17A0_INT_INTR_ENABLE_T            	int_intr_enable;              //0xc802601cL
	M17A0_INT_INTR_STATUS_T            	int_intr_status;              //0xc8026020L
	M17A0_INT_INTR_CLEAR_T             	int_intr_clear;               //0xc8026024L
	M17A0_SROM_BOOT_MAP1_T             	srom_boot_map1;               //0xc8026028L
	M17A0_SROM_BOOT_MAP2_T             	srom_boot_map2;               //0xc802602cL
	M17A0_SRAM_PORT_SEL_T              	sram_port_sel;                //0xc8026030L
	M17A0_PDEBUG_STATUS_T              	pdebug_status;                //0xc8026034L
	M17A0_PDEBUG_DATA_T                	pdebug_data;                  //0xc8026038L
	M17A0_PDEBUG_PC_T                  	pdebug_pc;                    //0xc802603cL
	M17A0_AXI_USER_ID_T                	axi_user_id;                  //0xc8026040L
	M17A0_SRAM0_OFFSET_T               	sram0_offset;                 //0xc8026044L
	M17A0_SRAM1_OFFSET_T               	sram1_offset;                 //0xc8026048L
	M17A0_SRAM2_OFFSET_T               	sram2_offset;                 //0xc802604cL
	M17A0_SRAM3_OFFSET_T               	sram3_offset;                 //0xc8026050L
	UINT32                             	reserved00[2];                //0xc8026054L~0xc8026058L
	M17A0_SPP_MCU_VERSION_T            	spp_mcu_version;              //0xc802605cL
	M17A0_INTR_MCU_FLAG_T              	intr_mcu_flag;                //0xc8026060L
	M17A0_INTR_MCU_FLAG_EN_T           	intr_mcu_flag_en;             //0xc8026064L
	M17A0_INTR_CPU_FLAG_T              	intr_cpu_flag;                //0xc8026068L
	M17A0_INTR_CPU_FLAG_EN_T            intr_cpu_flag_en;             //0xc802606cL
	UINT32                             	reserved01[36];               //0xc8026070L~0xc80260fcL
	M17A0_CPU_IPC0_T                   	cpu_ipc0;                     //0xc8026100L
	UINT32                             	reserved02[62];               //0xc8026104L~0xc80261f8L
	M17A0_CPU_IPC63_T                  	cpu_ipc63;                    //0xc80261fcL
	UINT32                             	reserved03[63];               //0xc8026200L~0xc80262f8L
	M17A0_VDEC_INTR_T                  	vdec_intr;                    //0xc80262fcL
	UINT32                             	reserved04[64];               //0xc8026300L~0xc80263fcL
	M17A0_TX_LOCKED_ID_T               	tx_locked_id;                 //0xc8026400L
	M17A0_TX_SRC_ADDR_T                	tx_src_addr;                  //0xc8026404L
	M17A0_TX_DST_ADDR_T                	tx_dst_addr;                  //0xc8026408L
	M17A0_TX_NXT_ADDR_T                	tx_nxt_addr;                  //0xc802640cL
	M17A0_TX_LENGTH_T                  	tx_length;                    //0xc8026410L
	M17A0_EDMA_CTRL_T                  	edma_ctrl;                    //0xc8026414L
} DE_IPC_REG_M17A0_T;

#endif
