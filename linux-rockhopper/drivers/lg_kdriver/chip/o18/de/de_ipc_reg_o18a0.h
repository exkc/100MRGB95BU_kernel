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

#ifndef _IPC_REG_O18A0_H_
#define _IPC_REG_O18A0_H_

/*-----------------------------------------------------------------------------
		0xC9026000L set_reg_ctrl0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 run_stall						: 1; // 0  = run 1 := stall
	UINT32 start_vector_sel 				: 1; //select reset vector	0  = SROM	1 := IRAM
	UINT32 p_debug_enable					: 1; //Trace output port enable 0 := disable	1  = enable
	UINT32 resvd0							: 1;
	UINT32 flush_rst_ctrl_status			: 4; //Only Debug
	UINT32 soft_reset_without_fdone 		: 1; //MCU Software Reset without flush done 0 := disable	1  = Reset
	UINT32 uart0_mux						: 1; //0 : = uart0	1	= uart1
	UINT32 uart1_mux						: 1; //0 : = uart1	1	= uart0
	UINT32 resvd1							: 5;
	UINT32 run_stall1						: 1; //0  = run 1 := stall
	UINT32 start_vector_sel1				: 1; //select reset vector	0  = SROM	1 := IRAM
	UINT32 p_debug_enable1					: 1; //Trace output port enable 0 := disable	1  = enable
	UINT32 resvd2							: 9;
	UINT32 soft_reset						: 1; //MCU Software Reset	0 := disable	1  = Reset
	UINT32 resvd3							: 3;  
} O18A0_SET_REG_CTRL0_T;

/*-----------------------------------------------------------------------------
		0xC9026004L set_reg_ctrl1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 prid                             :16;	//15:0	//	
	UINT32 prid1                            :16;	//31:16
} O18A0_SET_REG_CTRL1_T;

/*-----------------------------------------------------------------------------
		0xC9026008L ext_intr_event ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_event_arm            : 31;  // 30: 0     
	UINT32 wdg_interrupt_event                : 1 ;  //    31     
} O18A0_EXT_INTR_EVENT_T;

/*-----------------------------------------------------------------------------
		0xC902600cL ext_intr_enable ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_enable_arm           : 31;  // 30: 0     
	UINT32 wdg_interrupt_enable               : 1 ;  //    31     
} O18A0_EXT_INTR_ENABLE_T;

/*-----------------------------------------------------------------------------
		0xC9026010L ext_intr_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_status_arm           : 31;  // 30: 0     
	UINT32 wdg_interrupt_status               : 1 ;  //    31     
} O18A0_EXT_INTR_STATUS_T;

/*-----------------------------------------------------------------------------
		0xC9026014L ext_intr_clear ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_clear_arm            : 31;  // 30: 0     
	UINT32 wdg_interrupt_clear                : 1 ;  //    31     
} O18A0_EXT_INTR_CLEAR_T;

/*-----------------------------------------------------------------------------
		0xC9026018L int_intr_event ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_event_mcu            : 30;  // 29: 0     
	UINT32 edma_interrupt_event_mcu           : 1 ;  //    30     
} O18A0_INT_INTR_EVENT_T;

/*-----------------------------------------------------------------------------
		0xC902601cL int_intr_enable ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_enable_mcu           : 30;  // 29: 0     
	UINT32 edma_interrupt_enable_mcu          : 1 ;  //    30     
} O18A0_INT_INTR_ENABLE_T;

/*-----------------------------------------------------------------------------
		0xC9026020L int_intr_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_staus_mcu            : 30;  // 29: 0     
	UINT32 edma_interrupt_status_mcu          : 1 ;  //    30     
} O18A0_INT_INTR_STATUS_T;

/*-----------------------------------------------------------------------------
		0xC9026024L int_intr_clear ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_interrupt_clear_mcu            : 30;  // 29: 0     
	UINT32 edma_interrupt_clear_mcu           : 1 ;  //    30     
} O18A0_INT_INTR_CLEAR_T;

/*-----------------------------------------------------------------------------
		0xC9026028L srom_boot_map1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 boot_img_map1                      : 32;  // 31: 0     
} O18A0_SROM_BOOT_MAP1_T;

/*-----------------------------------------------------------------------------
		0xC902602cL srom_boot_map2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 boot_img_map2                      : 32;  // 31: 0     
} O18A0_SROM_BOOT_MAP2_T;

/*-----------------------------------------------------------------------------
		0xC9026030L sram_port_sel ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram0_port_sel                     : 4 ;  //  3: 0     
	UINT32 sram1_port_sel                     : 4 ;  //  7: 4     
	UINT32 sram2_port_sel                     : 4 ;  // 11: 8     
	UINT32 sram3_port_sel                     : 4 ;  // 15:12     
	UINT32 reserved                           : 1 ;  //    16     
} O18A0_SRAM_PORT_SEL_T;

/*-----------------------------------------------------------------------------
		0xC9026034L pdebug_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_status                      : 8 ;  //  7: 0     
} O18A0_PDEBUG_STATUS_T;

/*-----------------------------------------------------------------------------
		0xC9026038L pdebug_data ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_data                        : 32;  // 31: 0     
} O18A0_PDEBUG_DATA_T;

/*-----------------------------------------------------------------------------
		0xC902603cL pdebug_pc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_pc                          : 32;  // 31: 0     
} O18A0_PDEBUG_PC_T;

/*-----------------------------------------------------------------------------
		0xC9026040L axi_user_id ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aw_user_id                         : 4 ;  //  3: 0     
	UINT32 ar_user_id                         : 4 ;  //  7: 4     
} O18A0_AXI_USER_ID_T;

/*-----------------------------------------------------------------------------
		0xC9026044L sram0_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram0_offset                       : 32;  // 31: 0     
} O18A0_SRAM0_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xC9026048L sram1_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram1_offset                       : 32;  // 31: 0     
} O18A0_SRAM1_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xC902604cL sram2_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram2_offset                       : 32;  // 31: 0     
} O18A0_SRAM2_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xC9026050L sram3_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sram3_offset                       : 32;  // 31: 0        
} O18A0_SRAM3_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xC9026054 PDEBUG_DATA1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pdebug_data1                     :32;	//31:0	//
} O18A0_PDEBUG_DATA1_T;

/*-----------------------------------------------------------------------------
		0xC9026058 PDEBUG_PC1 ''
-----------------------------------------------------------------------------*/
typedef union {
	UINT32 pdebug_pc1                       :32;	//31:0	//
} O18A0_PDEBUG_PC1_T;

/*-----------------------------------------------------------------------------
		0xC902605cL spp_mcu_version ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mcu_version                        : 32;  // 31: 0     
} O18A0_SPP_MCU_VERSION_T;

/*-----------------------------------------------------------------------------
		0xC9026060L intr_mcu_flag ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_intr_mcu                     :1;	//0 //
	UINT32 imx_intr_mcu                     :1;	//1 //
	UINT32 hdr_mcu_intr_mcu                 :1;	//2 //
	UINT32 nd0_mcu_intr_mcu                 :1;	//3 //
	UINT32 nd1_mcu_intr_mcu                 :1;	//4 //
	UINT32 me0_mcu_intr_mcu                 :1;	//5 //
	UINT32 me1_mcu_intr_mcu                 :1;	//6 //
	UINT32 fmc_mcu_intr_mcu                 :1;	//7 //
	UINT32 fms_mcu_intr_mcu                 :1;	//8 //
	UINT32 gsc_mcu_intr_mcu                 :1;	//9 //
	UINT32 sre_mcu_intr_mcu                 :1;	//10 //
	UINT32 vsd_mcu_intr0_mcu                :1;	//11 //
	UINT32 vsd_mcu_intr1_mcu                :1;	//12 //
	UINT32 vsd_mcu_intr2_mcu                :1;	//13 //
	UINT32 cco_mcu_intr_mcu                 :1;	//14 //
	UINT32 led_mcu_intr_mcu                 :1;	//15 //
	UINT32 vdec_mcu_intr_mcu                :1;	//16 //
	UINT32 dpe_mcu_intr_mcu                 :1;	//17 //
	UINT32 mcu0_mcu_intr_mcu                :1;	//18 //
	UINT32 mcu1_mcu_intr_mcu                :1;	//19 //
	UINT32 reserved                         :12;	//31:20	//    
} O18A0_INTR_MCU_FLAG_T;

/*-----------------------------------------------------------------------------
		0xC9026064L intr_mcu_flag_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_intr_mcu_en                  :1;	//0 //
	UINT32 imx_intr_mcu_en                  :1;	//1 //
	UINT32 hdr_mcu_intr_mcu_en              :1;	//2 //
	UINT32 nd0_mcu_intr_mcu_en              :1;	//3 //
	UINT32 nd1_mcu_intr_mcu_en              :1;	//4 //
	UINT32 me0_mcu_intr_mcu_en              :1;	//5 //
	UINT32 me1_mcu_intr_mcu_en              :1;	//6 //
	UINT32 fmc_mcu_intr_mcu_en              :1;	//7 //
	UINT32 fms_mcu_intr_mcu_en              :1;	//8 //
	UINT32 gsc_mcu_intr_mcu_en              :1;	//9 //
	UINT32 sre_mcu_intr_mcu_en              :1;	//10 //
	UINT32 vsd_mcu_intr0_mcu_en             :1;	//11 //
	UINT32 vsd_mcu_intr1_mcu_en             :1;	//12 //
	UINT32 vsd_mcu_intr2_mcu_en             :1;	//13 //
	UINT32 cco_mcu_intr_mcu_en              :1;	//14 //
	UINT32 led_mcu_intr_mcu_en              :1;	//15 //
	UINT32 vdec_mcu_intr_mcu_en             :1;	//16 //
	UINT32 dpe_mcu_intr_mcu_en              :1;	//17 //
	UINT32 mcu0_mcu_intr_mcu_en             :1;	//18 //write 1하면 interrupt 발생, clear 하기 위해 write 0
	UINT32 mcu1_mcu_intr_mcu_en             :1;	//19 //write 1하면 interrupt 발생, clear 하기 위해 write 0
	UINT32 reserved                         :12;	//31:20	//
} O18A0_INTR_MCU_FLAG_EN_T;

/*-----------------------------------------------------------------------------
		0xC9026068L intr_cpu_flag ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvi_mcu_intr_cpu                 :1;	//0 //
	UINT32 imx_mcu_intr_cpu                 :1;	//1 //
	UINT32 hdr_mcu_intr_cpu                 :1;	//2 //
	UINT32 nd0_mcu_intr_cpu                 :1;	//3 //
	UINT32 nd1_mcu_intr_cpu                 :1;	//4 //
	UINT32 me0_mcu_intr_cpu                 :1;	//5 //
	UINT32 me1_mcu_intr_cpu                 :1;	//6 //
	UINT32 fmc_mcu_intr_cpu                 :1;	//7 //
	UINT32 fms_mcu_intr_cpu                 :1;	//8 //
	UINT32 gsc_mcu_intr_cpu                 :1;	//9 //
	UINT32 sre_mcu_intr_cpu                 :1;	//10 //
	UINT32 vsd_mcu_intr_cpu                 :1;	//11 //
	UINT32 cco_mcu_intr_cpu                 :1;	//12 //
	UINT32 dpe_mcu_intr_cpu                 :1;	//13 //
	UINT32 vdec_mcu_intr_cpu                :1;	//14 //VDEC to MCU interrupt
	UINT32 mcu_vdec_intr_cpu                :1;	//15 //MCU to VDEC interrupt
	UINT32 reserved                         :16;	//31:16	// 
} O18A0_INTR_CPU_FLAG_T;

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
} O18A0_INTR_CPU_FLAG_EN_T;

/*-----------------------------------------------------------------------------
		0xC90260F8 boot_img_map3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 boot_img_map3                    :32;	//31:0	//when AXI address of PL301 output is 0x5040_0000 ~ 0x505F_FFFF	physical image address in DDR region is 0x0040_0000 + boot_img_offset3	Default : 0x5040_0000 ~ 0x505F_FFFF	(real write region : 0x5040_0000 ~ 0x505F_FFFF => 0x5040_0000 ~ 0x505F_FFFF
} O18A0_SROM_BOOT_MAP3_T;

/*-----------------------------------------------------------------------------
		0xC90260FC boot_img_map4 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 boot_img_map4                    :32;	//31:0	//when AXI address of PL301 output is 0x5060_0000 ~ 0x507F_FFFF	physical image address in DDR region is 0x0060_0000 + boot_img_offset2	Default : 0x5060_0000 ~ 0x507F_FFFF	(real write region : 0x5060_0000 ~ 0x507F_FFFF => 0x5060_0000 ~ 0x507F_FFFF
} O18A0_SROM_BOOT_MAP4_T;

/*-----------------------------------------------------------------------------
		0xC9026100L cpu_ipc0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc                                : 32;  // 31: 0     
} O18A0_CPU_IPC0_T;

/*-----------------------------------------------------------------------------
		0xC90261fcL cpu_ipc63 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc                                : 32;  // 31: 0     
} O18A0_CPU_IPC63_T;

/*-----------------------------------------------------------------------------
		0xC90262fcL vdec_intr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vdec_interrupt                     : 1 ;  //     0     
} O18A0_VDEC_INTR_T;

/*-----------------------------------------------------------------------------
		0xC9026400L tx_locked_id ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_locked_id                       : 32;  // 31: 0     
} O18A0_TX_LOCKED_ID_T;

/*-----------------------------------------------------------------------------
		0xC9026404L tx_src_addr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_src_addr                        : 32;  // 31: 0     
} O18A0_TX_SRC_ADDR_T;

/*-----------------------------------------------------------------------------
		0xC9026408L tx_dst_addr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_dst_addr                        : 32;  // 31: 0     
} O18A0_TX_DST_ADDR_T;

/*-----------------------------------------------------------------------------
		0xC902640cL tx_nxt_addr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_nxt_addr                        : 32;  // 31: 0     
} O18A0_TX_NXT_ADDR_T;

/*-----------------------------------------------------------------------------
		0xC9026410L tx_length ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 tx_length                          : 32;  // 31: 0     
} O18A0_TX_LENGTH_T;

/*-----------------------------------------------------------------------------
		0xC9026414L edma_ctrl ''
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
} O18A0_EDMA_CTRL_T;

typedef struct {
	O18A0_SET_REG_CTRL0_T              	set_reg_ctrl0;                //0xC9026000L
	O18A0_SET_REG_CTRL1_T              	set_reg_ctrl1;                //0xC9026004L
	O18A0_EXT_INTR_EVENT_T             	ext_intr_event;               //0xC9026008L
	O18A0_EXT_INTR_ENABLE_T            	ext_intr_enable;              //0xC902600cL
	O18A0_EXT_INTR_STATUS_T            	ext_intr_status;              //0xC9026010L
	O18A0_EXT_INTR_CLEAR_T             	ext_intr_clear;               //0xC9026014L
	O18A0_INT_INTR_EVENT_T             	int_intr_event;               //0xC9026018L
	O18A0_INT_INTR_ENABLE_T            	int_intr_enable;              //0xC902601cL
	O18A0_INT_INTR_STATUS_T            	int_intr_status;              //0xC9026020L
	O18A0_INT_INTR_CLEAR_T             	int_intr_clear;               //0xC9026024L
	O18A0_SROM_BOOT_MAP1_T             	srom_boot_map1;               //0xC9026028L
	O18A0_SROM_BOOT_MAP2_T             	srom_boot_map2;               //0xC902602cL
	O18A0_SRAM_PORT_SEL_T              	sram_port_sel;                //0xC9026030L
	O18A0_PDEBUG_STATUS_T              	pdebug_status;                //0xC9026034L
	O18A0_PDEBUG_DATA_T                	pdebug_data;                  //0xC9026038L
	O18A0_PDEBUG_PC_T                  	pdebug_pc;                    //0xC902603cL
	O18A0_AXI_USER_ID_T                	axi_user_id;                  //0xC9026040L
	O18A0_SRAM0_OFFSET_T               	sram0_offset;                 //0xC9026044L
	O18A0_SRAM1_OFFSET_T               	sram1_offset;                 //0xC9026048L
	O18A0_SRAM2_OFFSET_T               	sram2_offset;                 //0xC902604cL
	O18A0_SRAM3_OFFSET_T               	sram3_offset;                 //0xC9026050L
	O18A0_PDEBUG_DATA1_T                pdebug_data1;                 //0xC9026054L
	O18A0_PDEBUG_PC1_T                  pdebug_pc1;                   //0xC9026058L
	O18A0_SPP_MCU_VERSION_T            	spp_mcu_version;              //0xC902605cL
	O18A0_INTR_MCU_FLAG_T              	intr_mcu_flag;                //0xC9026060L
	O18A0_INTR_MCU_FLAG_EN_T           	intr_mcu_flag_en;             //0xC9026064L
	O18A0_INTR_CPU_FLAG_T              	intr_cpu_flag;                //0xC9026068L
	O18A0_INTR_CPU_FLAG_EN_T           	intr_cpu_flag_en;             //0xC902606cL
	UINT32                             	reserved01[34];               //0xC9026070L~0xC90260f4L
	O18A0_SROM_BOOT_MAP3_T              srom_boot_map3;               //0xC90260f8L
	O18A0_SROM_BOOT_MAP4_T              srom_boot_map4;               //0xC90260fCL	
	O18A0_CPU_IPC0_T                   	cpu_ipc0;                     //0xC9026100L
	UINT32                             	reserved02[62];               //0xC9026104L~0xC90261f8L
	O18A0_CPU_IPC63_T                  	cpu_ipc63;                    //0xC90261fcL
	UINT32                             	reserved03[63];               //0xC9026200L~0xC90262f8L
	O18A0_VDEC_INTR_T                  	vdec_intr;                    //0xC90262fcL
	UINT32                             	reserved04[64];               //0xC9026300L~0xC90263fcL
	O18A0_TX_LOCKED_ID_T               	tx_locked_id;                 //0xC9026400L
	O18A0_TX_SRC_ADDR_T                	tx_src_addr;                  //0xC9026404L
	O18A0_TX_DST_ADDR_T                	tx_dst_addr;                  //0xC9026408L
	O18A0_TX_NXT_ADDR_T                	tx_nxt_addr;                  //0xC902640cL
	O18A0_TX_LENGTH_T                  	tx_length;                    //0xC9026410L
	O18A0_EDMA_CTRL_T                  	edma_ctrl;                    //0xC9026414L
} DE_IPC_REG_O18A0_T;

#endif
