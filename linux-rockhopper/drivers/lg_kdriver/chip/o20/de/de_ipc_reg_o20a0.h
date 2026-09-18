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

#ifndef _IPC_REG_O20A0_H_
#define _IPC_REG_O20A0_H_

typedef union {
	UINT32 udata32;
	struct {						//0xC9026000 RW/RO
	UINT32 run_stall                        :1;	//0 //0  = run	1 := stall
	UINT32 start_vector_sel                 :1;	//1 //select reset vector	0  = SROM	1 := IRAM
	UINT32 p_debug_enable                   :1;	//2 //Trace output port enable	0 := disable	1  = enable
	UINT32 resvd0                           :1;
	UINT32 flush_rst_ctrl_status            :4;	//7:4	//Only Debug
	UINT32 soft_reset_without_fdone         :1;	//8 //MCU Software Reset without flush done	0 := disable	1  = Reset
	UINT32 uart0_mux                        :1;	//9 //0 : = uart0	1   = uart1
	UINT32 uart1_mux                        :1;	//10 //0 : = uart1	1   = uart0
	UINT32 resvd1                           :5;
	UINT32 run_stall1                       :1;	//16 //0  = run	1 := stall
	UINT32 start_vector_sel1                :1;	//17 //select reset vector	0  = SROM	1 := IRAM
	UINT32 p_debug_enable1                  :1;	//18 //Trace output port enable	0 := disable	1  = enable
	UINT32 resvd2                           :9;
	UINT32 soft_reset                       :1;	//28 //MCU Software Reset	0 := disable	1  = Reset
	UINT32 resvd3                           :2;
	UINT32 ipu_axi_gating                   :1;	//31 //IPU's AXI gating	0 := disable	1  = Reset
	};
}O20A0_SET_REG_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026004 RW
	UINT32 prid                             :16;	//15:0	//
	UINT32 prid1                            :16;	//31:16	//
	};
}O20A0_SET_REG_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026008 RW
	UINT32 ipc_interrupt_event_arm          :30;//29:0
	UINT32 wdg_interrupt_event_mcu1         :1;	//30 //MCU1 watch dog interrupt event
	UINT32 wdg_interrupt_event              :1;	//31 //MCU watch dog interrupt event
	};
}O20A0_EXT_INTR_EVENT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902600C RW
	UINT32 ipc_interrupt_enable_arm         :30;//29:0
	UINT32 wdg_interrupt_enable_mcu1        :1;	//30 //MCU1 watch dog interrupt enable
	UINT32 wdg_interrupt_enable             :1;	//31 //MCU watch dog interrupt enable
	};
}O20A0_EXT_INTR_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026010 RO
	UINT32 ipc_interrupt_status_arm         :30;//29:0
	UINT32 wdg_interrupt_status_mcu1        :1;	//30 //MCU1 watch dog interrupt status
	UINT32 wdg_interrupt_status             :1;	//31 //MCU watch dog interrupt status
	};
}O20A0_EXT_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026014 WO
	UINT32 ipc_interrupt_clear_arm          :30;//29:0
	UINT32 wdg_interrupt_clear_mcu1         :1;	//30 //MCU1 watch dog interrupt enable
	UINT32 wdg_interrupt_clear              :1;	//31 //MCU watch dog interrupt enable - This register is auto cleared after set 1
	};
}O20A0_EXT_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026018 RO
	UINT32 ipc_interrupt_event_mcu          :29;//28:0
	UINT32 edma_interrupt_event_mcu         :1;	//29 //eDMA interrupt event for MCU
	UINT32 resvd                            :2;
	};
}O20A0_INT_INTR_EVENT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902601C RW
	UINT32 ipc_interrupt_enable_mcu         :29;//28:0
	UINT32 edma_interrupt_enable_mcu        :1;	//29 //eDMA interrupt enable for MCU
	UINT32 resvd                            :2;
	};
}O20A0_INT_INTR_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026020 RO
	UINT32 ipc_interrupt_staus_mcu          :29;//28:0
	UINT32 edma_interrupt_status_mcu        :1;	//29 //eDMA interrupt status for MCU
	UINT32 resvd                            :2;
	};
}O20A0_INT_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026024 WO
	UINT32 ipc_interrupt_clear_mcu          :29;//28:0
	UINT32 edma_interrupt_clear_mcu         :1;	//29 //eDMA interrupt clear for MCU - This register is auto cleared after set 1
	UINT32 resvd                            :2;
	};
}O20A0_INT_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026028 RW
	UINT32 boot_img_map1                    :32;	//31:0	//when AXI address of PL301 output is 0x5000_0000 ~ 0x501F_FFFF	physical image address in DDR region is 0x0000_0000 + boot_img_map1	Default : 0x5000_0000 ~ 0x501F_FFFF	(real write region : 0x5000_0000 ~ 0x501F_FFFF => 0x5000_0000 ~ 0x501F_FFFF
	};
}O20A0_SROM_BOOT_MAP1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902602C RW
	UINT32 boot_img_map2                    :32;	//31:0	//when AXI address of PL301 output is 0x5020_0000 ~ 0x503F_FFFF	physical image address in DDR region is 0x0020_0000 + boot_img_map2	Default : 0x5020_0000 ~ 0x503F_FFFF	(real write region : 0x5020_0000 ~ 0x503F_FFFF => 0x5020_0000 ~ 0x503F_FFFF
	};
}O20A0_SROM_BOOT_MAP2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026030 RW
	UINT32 sram0_port_sel                   :4;	//3:0	//when AXI address of PL301 output is 0x8000_0000 ~ 0x8FFF_FFFF	select sram0_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0x8000_0000 ~ 0x8FFF_FFFF => 0x8000_0000 ~ 0x8FFF_FFFF
	UINT32 sram1_port_sel                   :4;	//7:4	//when AXI address of PL301 output is 0x9000_0000 ~ 0x9FFF_FFFF	select sram1_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0x9000_0000 ~ 0x9FFF_FFFF => 0x9000_0000 ~ 0x9FFF_FFFF
	UINT32 sram2_port_sel                   :4;	//11:8	//when AXI address of PL301 output is 0xA000_0000 ~ 0xAFFF_FFFF	select sram2_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0xA000_0000 ~ 0xAFFF_FFFF => 0xA000_0000 ~ 0xAFFF_FFFF
	UINT32 sram3_port_sel                   :4;	//15:12	//when AXI address of PL301 output is 0xB000_0000 ~ 0xBFFF_FFFF	select sram0_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0xB000_0000 ~ 0xBFFF_FFFF => 0xB000_0000 ~ 0xBFFF_FFFF
	UINT32 reserved                         :1;	//16 //
	UINT32 resvd                            :15;
	};
}O20A0_SRAM_PORT_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026034 RO
	UINT32 pdebug_status                    :8;	//7:0	//
	UINT32 pdebug_status1                   :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}O20A0_PDEBUG_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026038 RO
	UINT32 pdebug_data                      :32;	//31:0	//
	};
}O20A0_PDEBUG_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902603C RO
	UINT32 pdebug_pc                        :32;	//31:0	//
	};
}O20A0_PDEBUG_PC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026040 RW
	UINT32 s0_aw_user_id                    :4;	//3:0	//
	UINT32 s0_ar_user_id                    :4;	//7:4	//
	UINT32 s1_aw_user_id                    :4;	//11:8	//
	UINT32 s1_ar_user_id                    :4;	//15:12	//
	UINT32 resvd                            :16;
	};
}O20A0_AXI_USER_ID_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026044 RW
	UINT32 sram0_offset                     :32;	//31:0	//when AXI address of PL301 output is 0x8000_0000 ~ 0x8FFF_FFFF	{sram0_port_sel[3:0],AXI_ADDR[27:0] + sram0_offset}
	};
}O20A0_SRAM0_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026048 RW
	UINT32 sram1_offset                     :32;	//31:0	//when AXI address of PL301 output is 0x9000_0000 ~ 0x9FFF_FFFF	{sram1_port_sel[3:0],AXI_ADDR[27:0] + sram1_offset}
	};
}O20A0_SRAM1_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902604C RW
	UINT32 sram2_offset                     :32;	//31:0	//when AXI address of PL301 output is 0xA000_0000 ~ 0xAFFF_FFFF	{sram2_port_sel[3:0],AXI_ADDR[27:0] + sram2_offset}
	};
}O20A0_SRAM2_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026050 RW
	UINT32 sram3_offset                     :32;	//31:0	//when AXI address of PL301 output is 0xB000_0000 ~ 0xBFFF_FFFF	{sram3_port_sel[3:0],AXI_ADDR[27:0] + sram3_offset}
	};
}O20A0_SRAM3_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026054 RO
	UINT32 pdebug_data1                     :32;	//31:0	//
	};
}O20A0_PDEBUG_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026058 RO
	UINT32 pdebug_pc1                       :32;	//31:0	//
	};
}O20A0_PDEBUG_PC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902605C RO
	UINT32 mcu_version                      :32;	//31:0	//
	};
}O20A0_SPP_MCU_VERSION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026060 RO
	UINT32 cvi_mcu_intr_mcu                 :1;	//0 //
	UINT32 imx_mcu_intr_mcu                 :1;	//1 //
	UINT32 hdr_mcu_intr_mcu                 :1;	//2 //
	UINT32 nd0_mcu_intr_mcu                 :1;	//3 //
	UINT32 nd1_mcu_intr_mcu                 :1;	//4 //
	UINT32 me0_mcu_intr_mcu                 :1;	//5 //
	UINT32 me1_mcu_intr_mcu                 :1;	//6 //
	UINT32 fmc_mcu_intr_mcu                 :1;	//7 //
	UINT32 fms_mcu_intr_mcu                 :1;	//8 //
	UINT32 gsc_mcu_intr_mcu                 :1;	//9 //
	UINT32 sre_mcu_intr_mcu                 :1;	//10 //
	UINT32 vsd_mcu_intr_mcu                 :1;	//11 //
	UINT32 cco_mcu_intr_mcu                 :1;	//12 //
	UINT32 led_mcu_intr_mcu                 :1;	//13 //
	UINT32 ldm_mcu_intr_mcu                 :1;	//14 //
	UINT32 vdec_mcu_intr_mcu                :1;	//15 //
	UINT32 dpe_mcu_intr_mcu                 :1;	//16 //
	UINT32 tra_mcu_intr_mcu                 :1;	//17 //
	UINT32 inf_mcu_intr_mcu                 :1;	//18 //
	UINT32 lne_mcu_intr_mcu                 :1;	//19 //
	UINT32 gav_mcu_intr_mcu                 :1;	//20 //
	UINT32 ipu_mcu_intr_mcu                 :1;	//21 //
	UINT32 mcu0_mcu_intr_mcu                :1;	//22 //
	UINT32 mcu1_mcu_intr_mcu                :1;	//23 //
	UINT32 reserved                         :8;	//31:24	//
	};
}O20A0_INTR_MCU_FLAG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026064 RW
	UINT32 cvi_mcu_intr_mcu_en              :1;	//0 //
	UINT32 imx_mcu_intr_mcu_en              :1;	//1 //
	UINT32 hdr_mcu_intr_mcu_en              :1;	//2 //
	UINT32 nd0_mcu_intr_mcu_en              :1;	//3 //
	UINT32 nd1_mcu_intr_mcu_en              :1;	//4 //
	UINT32 me0_mcu_intr_mcu_en              :1;	//5 //
	UINT32 me1_mcu_intr_mcu_en              :1;	//6 //
	UINT32 fmc_mcu_intr_mcu_en              :1;	//7 //
	UINT32 fms_mcu_intr_mcu_en              :1;	//8 //
	UINT32 gsc_mcu_intr_mcu_en              :1;	//9 //
	UINT32 sre_mcu_intr_mcu_en              :1;	//10 //
	UINT32 vsd_mcu_intr_mcu_en              :1;	//11 //
	UINT32 cco_mcu_intr_mcu_en              :1;	//12 //
	UINT32 led_mcu_intr_mcu_en              :1;	//13 //
	UINT32 ldm_mcu_intr_mcu_en              :1;	//14 //
	UINT32 vdec_mcu_intr_mcu_en             :1;	//15 //
	UINT32 dpe_mcu_intr_mcu_en              :1;	//16 //
	UINT32 tra_mcu_intr_mcu_en              :1;	//17 //
	UINT32 inf_mcu_intr_mcu_en              :1;	//18 //
	UINT32 lne_mcu_intr_mcu_en              :1;	//19 //
	UINT32 gav_mcu_intr_mcu_en              :1;	//20 //
	UINT32 ipu_mcu_intr_mcu_en              :1;	//21 //
	UINT32 mcu0_mcu_intr_mcu_en             :1;	//22 //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 mcu1_mcu_intr_mcu_en             :1;	//23 //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 reserved                         :8;	//31:24	//
	};
}O20A0_INTR_MCU_FLAG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026068 RO
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
	UINT32 led_mcu_intr_cpu                 :1;	//13 //
	UINT32 vdec_mcu_intr_cpu                :1;	//14 //VDEC to MCU interrupt
	UINT32 mcu_vdec_intr_cpu                :1;	//15 //MCU to VDEC interrupt
	UINT32 dpe_mcu_intr_cpu                 :1;	//16 //
	UINT32 tra_mcu_intr_cpu                 :1;	//17 //
	UINT32 inf_mcu_intr_cpu                 :1;	//18 //
	UINT32 lne_mcu_intr_cpu                 :1;	//19 //
	UINT32 gav_mcu_intr_cpu                 :1;	//20 //
	UINT32 ipu_mcu_intr_cpu                 :1;	//21 //
	UINT32 reserved                         :10;	//31:22	//
	};
}O20A0_INTR_CPU_FLAG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902606C RW
	UINT32 cvi_mcu_intr_cpu_en              :1;	//0 //
	UINT32 imx_mcu_intr_cpu_en              :1;	//1 //
	UINT32 hdr_mcu_intr_cpu_en              :1;	//2 //
	UINT32 nd0_mcu_intr_cpu_en              :1;	//3 //
	UINT32 nd1_mcu_intr_cpu_en              :1;	//4 //
	UINT32 me0_mcu_intr_cpu_en              :1;	//5 //
	UINT32 me1_mcu_intr_cpu_en              :1;	//6 //
	UINT32 fmc_mcu_intr_cpu_en              :1;	//7 //
	UINT32 fms_mcu_intr_cpu_en              :1;	//8 //
	UINT32 gsc_mcu_intr_cpu_en              :1;	//9 //
	UINT32 sre_mcu_intr_cpu_en              :1;	//10 //
	UINT32 vsd_mcu_intr_cpu_en              :1;	//11 //
	UINT32 cco_mcu_intr_cpu_en              :1;	//12 //
	UINT32 led_mcu_intr_cpu_en              :1;	//13 //
	UINT32 vdec_mcu_intr_cpu_en             :1;	//14 //
	UINT32 mcu_vdec_intr_cpu_en             :1;	//15 //
	UINT32 dpe_mcu_intr_cpu_en              :1;	//16 //
	UINT32 tra_mcu_intr_cpu_en              :1;	//17 //
	UINT32 inf_mcu_intr_cpu_en              :1;	//18 //
	UINT32 lne_mcu_intr_cpu_en              :1;	//19 //
	UINT32 gav_mcu_intr_cpu_en              :1;	//20 //
	UINT32 ipu_mcu_intr_cpu_en              :1;	//21 //
	UINT32 reserved                         :10;	//31:22	//
	};
}O20A0_INTR_CPU_FLAG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026070 RO
	UINT32 global_stcco0                    :32;	//31:0	//
	};
}O20A0_GLOBAL_STCC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026074 RO
	UINT32 global_stcco1                    :32;	//31:0	//
	};
}O20A0_GLOBAL_STCC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026078 RO
	UINT32 global_stcco2                    :32;	//31:0	//
	};
}O20A0_GLOBAL_STCC2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902607C RO
	UINT32 global_stcco3                    :32;	//31:0	//
	};
}O20A0_GLOBAL_STCC3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026080 RO
	UINT32 live_stcco0                      :32;	//31:0	//
	};
}O20A0_LIVE_STCC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026084 RO
	UINT32 live_stcco0                      :32;	//31:0	//
	};
}O20A0_LIVE_STCC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026088 RW
	UINT32 cpu_debug_reg0                   :32;	//31:0	//CPU Debug REG0
	};
}O20A0_AD_GEN_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902608C RW
	UINT32 cpu_debug_reg1                   :32;	//31:0	//CPU Debug REG1
	};
}O20A0_AD_GEN_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026090 RW
	UINT32 cpu_debug_reg2                   :32;	//31:0	//CPU Debug REG2
	};
}O20A0_AD_GEN_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026094 RW
	UINT32 cpu_debug_reg3                   :32;	//31:0	//CPU Debug REG3
	};
}O20A0_AD_GEN_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026098 RW
	UINT32 cpu_debug_reg4                   :32;	//31:0	//CPU Debug REG4
	};
}O20A0_AD_GEN_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902609C RW
	UINT32 cpu_debug_reg5                   :32;	//31:0	//CPU Debug REG5
	};
}O20A0_AD_GEN_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260A0 RW
	UINT32 reg_s0_wait_time                 :8;	//7:0	//timeout count 0~255
	UINT32 reg_s1_wait_time                 :8;	//15:8	//timeout count 0~255
	UINT32 resvd0                           :8;
	UINT32 s0_timeout_en                    :1;	//24 //timeout control enable for s0 (MCU)
	UINT32 s1_timeout_en                    :1;	//25 //timeout control enable for s1 (CPU)
	UINT32 resvd1                           :1;
	UINT32 reg_timeout_en                   :1;	//27 //timeout control enable
	UINT32 s0_catch                         :1;	//28 //abnormal address catch reset (debug)
	UINT32 s1_catch                         :1;	//29 //abnormal address catch reset (debug)
	UINT32 resvd2                           :2;
	};
}O20A0_TIMEOUT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260A4 RO
	UINT32 s0_paddr_read                    :32;	//31:0	//
	};
}O20A0_S0_ADDR_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260A8 RO
	UINT32 s1_paddr_read                    :32;	//31:0	//
	};
}O20A0_S1_ADDR_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260B0 RW
	UINT32 mask_start_addr                  :23;	//22:0	//
	UINT32 resvd                            :9;
	};
}O20A0_MASK_START_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260B4 RW
	UINT32 mask_end_addr                    :23;	//22:0	//
	UINT32 resvd                            :8;
	UINT32 mask_addr_mode_en                :1;	//31 //
	};
}O20A0_MASK_END_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260B8 RO
	UINT32 mask_read_addr                   :23;	//22:0	//
	UINT32 resvd                            :9;
	};
}O20A0_MASK_READ_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260BC RW
	UINT32 interuppt_2                      :4;	//3:0	//priority 1 level
	UINT32 interuppt_3                      :4;	//7:4	//priority 1 level
	UINT32 interuppt_4                      :4;	//11:8	//priority 1 level
	UINT32 interuppt_5                      :4;	//15:12	//priority 1 level
	UINT32 interuppt_6                      :4;	//19:16	//priority 2 level
	UINT32 interuppt_7                      :4;	//23:20	//priority 3 level
	UINT32 interuppt_8                      :4;	//27:24	//priority 4 level	"0000" : not connected	"0001" : CPU IPC interrupt	"0010" : Local Top interrupt
	UINT32 reserved                         :4;	//31:28	//for debug : interrupt_9 (edge)
	};
}O20A0_AD_INTR_PRIORITY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260C0 RW/RO
	UINT32 up_count                         :31;	//30:0	//up counter with 198Mhz clock
	UINT32 up_count_en                      :1;	//31 //reset and enable
	};
}O20A0_AD_UP_COUNTER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260C4 RW
	UINT32 rst_async_bridge                 :32;	//31:0	//
	};
}O20A0_RST_ASYNC_BRIDGE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260C8 RW
	UINT32 cpu_debug_reg6                   :32;	//31:0	//
	};
}O20A0_AD_GEN_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260CC RW
	UINT32 cpu_debug_reg7                   :32;	//31:0	//
	};
}O20A0_AD_GEN_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260D0 RW
	UINT32 cpu_debug_reg8                   :32;	//31:0	//
	};
}O20A0_AD_GEN_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260D4 RW
	UINT32 cpu_debug_reg9                   :32;	//31:0	//
	};
}O20A0_AD_GEN_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260D8 RW
	UINT32 cpu_debug_reg10                  :32;	//31:0	//
	};
}O20A0_AD_GEN_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260DC RW
	UINT32 cpu_debug_reg11                  :32;	//31:0	//
	};
}O20A0_AD_GEN_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260E0 RW
	UINT32 cpu_debug_reg12                  :32;	//31:0	//
	};
}O20A0_AD_GEN_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260E4 RW
	UINT32 cpu_debug_reg13                  :32;	//31:0	//
	};
}O20A0_AD_GEN_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260E8 RW
	UINT32 cpu_debug_reg14                  :32;	//31:0	//
	};
}O20A0_AD_GEN_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260EC RW
	UINT32 cpu_debug_reg15                  :32;	//31:0	//
	};
}O20A0_AD_GEN_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260F0 RO
	UINT32 cvi_mcu_intr_mcu                 :1;	//0 //
	UINT32 imx_mcu_intr_mcu                 :1;	//1 //
	UINT32 hdr_mcu_intr_mcu                 :1;	//2 //
	UINT32 nd0_mcu_intr_mcu                 :1;	//3 //
	UINT32 nd1_mcu_intr_mcu                 :1;	//4 //
	UINT32 me0_mcu_intr_mcu                 :1;	//5 //
	UINT32 me1_mcu_intr_mcu                 :1;	//6 //
	UINT32 fmc_mcu_intr_mcu                 :1;	//7 //
	UINT32 fms_mcu_intr_mcu                 :1;	//8 //
	UINT32 gsc_mcu_intr_mcu                 :1;	//9 //
	UINT32 sre_mcu_intr_mcu                 :1;	//10 //
	UINT32 vsd_mcu_intr_mcu                 :1;	//11 //
	UINT32 cco_mcu_intr_mcu                 :1;	//12 //
	UINT32 led_mcu_intr_mcu                 :1;	//13 //
	UINT32 ldm_mcu_intr_mcu                 :1;	//14 //
	UINT32 vdec_mcu_intr_mcu                :1;	//15 //
	UINT32 dpe_mcu_intr_mcu                 :1;	//16 //
	UINT32 tra_mcu_intr_mcu                 :1;	//17 //
	UINT32 inf_mcu_intr_mcu                 :1;	//18 //
	UINT32 lne_mcu_intr_mcu                 :1;	//19 //
	UINT32 gav_mcu_intr_mcu                 :1;	//20 //
	UINT32 ipu_mcu_intr_mcu                 :1;	//21 //
	UINT32 mcu0_mcu_intr_mcu                :1;	//22 //
	UINT32 mcu1_mcu_intr_mcu                :1;	//23 //
	UINT32 reserved                         :8;	//31:24	//
	};
}O20A0_INTR_MCU1_FLAG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260F4 RW
	UINT32 cvi_mcu_intr_mcu_en              :1;	//0 //
	UINT32 imx_mcu_intr_mcu_en              :1;	//1 //
	UINT32 hdr_mcu_intr_mcu_en              :1;	//2 //
	UINT32 nd0_mcu_intr_mcu_en              :1;	//3 //
	UINT32 nd1_mcu_intr_mcu_en              :1;	//4 //
	UINT32 me0_mcu_intr_mcu_en              :1;	//5 //
	UINT32 me1_mcu_intr_mcu_en              :1;	//6 //
	UINT32 fmc_mcu_intr_mcu_en              :1;	//7 //
	UINT32 fms_mcu_intr_mcu_en              :1;	//8 //
	UINT32 gsc_mcu_intr_mcu_en              :1;	//9 //
	UINT32 sre_mcu_intr_mcu_en              :1;	//10 //
	UINT32 vsd_mcu_intr_mcu_en              :1;	//11 //
	UINT32 cco_mcu_intr_mcu_en              :1;	//12 //
	UINT32 led_mcu_intr_mcu_en              :1;	//13 //
	UINT32 ldm_mcu_intr_mcu_en              :1;	//14 //
	UINT32 vdec_mcu_intr_mcu_en             :1;	//15 //
	UINT32 dpe_mcu_intr_mcu_en              :1;	//16 //
	UINT32 tra_mcu_intr_mcu_en              :1;	//17 //
	UINT32 inf_mcu_intr_mcu_en              :1;	//18 //
	UINT32 lne_mcu_intr_mcu_en              :1;	//19 //
	UINT32 gav_mcu_intr_mcu_en              :1;	//20 //
	UINT32 ipu_mcu_intr_mcu_en              :1;	//21 //
	UINT32 mcu0_mcu_intr_mcu_en             :1;	//22 //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 mcu1_mcu_intr_mcu_en             :1;	//23 //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 reserved                         :8;	//31:24	//
	};
}O20A0_INTR_MCU1_FLAG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260F8 RW
	UINT32 boot_img_map3                    :32;	//31:0	//when AXI address of PL301 output is 0x5040_0000 ~ 0x505F_FFFF	physical image address in DDR region is 0x0040_0000 + boot_img_map3	Default : 0x5040_0000 ~ 0x505F_FFFF	(real write region : 0x5040_0000 ~ 0x505F_FFFF => 0x5040_0000 ~ 0x505F_FFFF
	};
}O20A0_SROM_BOOT_MAP3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90260FC RW
	UINT32 boot_img_map4                    :32;	//31:0	//when AXI address of PL301 output is 0x5060_0000 ~ 0x507F_FFFF	physical image address in DDR region is 0x0060_0000 + boot_img_map4	Default : 0x5060_0000 ~ 0x507F_FFFF	(real write region : 0x5060_0000 ~ 0x507F_FFFF => 0x5060_0000 ~ 0x507F_FFFF
	};
}O20A0_SROM_BOOT_MAP4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026100 RW
	UINT32 ipc                              :32;	//31:0	//
	};
}O20A0_CPU_IPC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90261FC RW
	UINT32 ipc                              :32;	//31:0	//
	};
}O20A0_CPU_IPC63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026200 RW
	UINT32 ipc                              :32;	//31:0	//
	};
}O20A0_VDEC_VENC_IPC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90262FC RW
	UINT32 ipc                              :32;	//31:0	//
	};
}O20A0_VDEC_VENC_IPC63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026300 RW
	UINT32 ipc                              :32;	//31:0	//
	};
}O20A0_VDEC_VENC_IPC64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263DC RW
	UINT32 ipc                              :32;	//31:0	//
	};
}O20A0_VDEC_VENC_IPC119_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263E0 WO
	UINT32 ipc_interrupt_event_vdec         :32;	//31:0	//IPC interrupt event for VDEC
	};
}O20A0_PQE_INTR_EVENT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263E4 RW
	UINT32 ipc_interrupt_enable_vdec        :32;	//31:0	//IPC interrupt enable for VDEC
	};
}O20A0_PQE_INTR_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263E8 RO
	UINT32 ipc_interrupt_status_vdec        :32;	//31:0	//IPC interrupt enable for VDEC
	};
}O20A0_PQE_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263EC WO
	UINT32 ipc_interrupt_clear_vdec         :32;	//31:0	//IPC interrupt clear for VDEC - This register is auto cleared after set 1
	};
}O20A0_PQE_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263F0 WO
	UINT32 ipc_interrupt_event_pqe          :32;	//31:0	//IPC interrupt event for PQE
	};
}O20A0_VDEC_INTR_EVENT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263F4 RW
	UINT32 ipc_interrupt_enable_pqe         :32;	//31:0	//IPC interrupt enable for PQE
	};
}O20A0_VDEC_INTR_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263F8 RO
	UINT32 ch0:1;
	UINT32 ch1:1;
	UINT32 ch2:1;
	UINT32 ch3:1;
	UINT32 ipc_interrupt_staus_pqe          :28;	//31:0	//IPC interrupt enable for PQE
	};
}O20A0_VDEC_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90263FC WO
	UINT32 ipc_interrupt_clear_pqe          :32;	//31:0	//IPC interrupt clear for PQE - This register is auto cleared after set 1
	};
}O20A0_VDEC_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026400 RW
	UINT32 ipc                              :32;	//31:0	//general purpose IPC
	};
}O20A0_GEN_IPC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90265FC RW
	UINT32 ipc                              :32;	//31:0	//general purpose IPC
	};
}O20A0_GEN_IPC127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026600 RW
	UINT32 tx_locked_id                     :32;	//31:0	//to which access permission is granted For Scatter-Gather, txSrcAddr should be the first field that DMA engine will read
	};
}O20A0_TX_LOCKED_ID_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026604 RW
	UINT32 tx_src_addr                      :32;	//31:0	//
	};
}O20A0_TX_SRC_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026608 RW
	UINT32 tx_dst_addr                      :32;	//31:0	//
	};
}O20A0_TX_DST_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902660C RW
	UINT32 tx_nxt_addr                      :32;	//31:0	//
	};
}O20A0_TX_NXT_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026610 RW
	UINT32 tx_length                        :32;	//31:0	//
	};
}O20A0_TX_LENGTH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9026614 RW/RO
	UINT32 tx_start                         :1;	//0 //triggerring a transaction when a writing one happens on this register. This address is shared between registers; txStart, txBusy a write goes on txStart, a read return txBusy
	UINT32 tx_dir                           :3;	//3:1	//direction of the traction (portA: DDR, portB : In-bound PIF)	000 := Port A -> Port A	001  = Port A -> Port B	010  = Port B -> Port A	011  = Port B -> Port B	100  = Pattern -> Port A	101  = Pattern -> Port B
	UINT32 tx_nxt_dir                       :1;	//4 //Indicating which port the next descriptor exists 0: Port A, 1: Port B
	UINT32 resvd0                           :3;
	UINT32 tx_done                          :1;	//8 //A DMA transaction completes not a read-only register could be written if and only if txState == IDLE_STATE
	UINT32 tx_locked                        :1;	//9 //indicating whether DMA engine is locked, txLockedID is valid if and if only while this is high
	UINT32 tx_switch_en                     :1;	//10 //Endian-switching is enabled when this is high
	UINT32 resvd1                           :1;
	UINT32 tx_atomic_size                   :2;	//13:12	//Atomic size for endian switching
	UINT32 resvd2                           :18;
	};
}O20A0_EDMA_CTRL_T;

typedef struct {
	O20A0_SET_REG_CTRL0_T                               set_reg_ctrl0;	//0xC9026000
	O20A0_SET_REG_CTRL1_T                               set_reg_ctrl1;	//0xC9026004
	O20A0_EXT_INTR_EVENT_T                             ext_intr_event;	//0xC9026008
	O20A0_EXT_INTR_ENABLE_T                           ext_intr_enable;	//0xC902600C
	O20A0_EXT_INTR_STATUS_T                           ext_intr_status;	//0xC9026010
	O20A0_EXT_INTR_CLEAR_T                             ext_intr_clear;	//0xC9026014
	O20A0_INT_INTR_EVENT_T                             int_intr_event;	//0xC9026018
	O20A0_INT_INTR_ENABLE_T                           int_intr_enable;	//0xC902601C
	O20A0_INT_INTR_STATUS_T                           int_intr_status;	//0xC9026020
	O20A0_INT_INTR_CLEAR_T                             int_intr_clear;	//0xC9026024
	O20A0_SROM_BOOT_MAP1_T                             srom_boot_map1;	//0xC9026028
	O20A0_SROM_BOOT_MAP2_T                             srom_boot_map2;	//0xC902602C
	O20A0_SRAM_PORT_SEL_T                               sram_port_sel;	//0xC9026030
	O20A0_PDEBUG_STATUS_T                               pdebug_status;	//0xC9026034
	O20A0_PDEBUG_DATA_T                                   pdebug_data;	//0xC9026038
	O20A0_PDEBUG_PC_T                                       pdebug_pc;	//0xC902603C
	O20A0_AXI_USER_ID_T                                   axi_user_id;	//0xC9026040
	O20A0_SRAM0_OFFSET_T                                 sram0_offset;	//0xC9026044
	O20A0_SRAM1_OFFSET_T                                 sram1_offset;	//0xC9026048
	O20A0_SRAM2_OFFSET_T                                 sram2_offset;	//0xC902604C
	O20A0_SRAM3_OFFSET_T                                 sram3_offset;	//0xC9026050
	O20A0_PDEBUG_DATA1_T                                 pdebug_data1;	//0xC9026054
	O20A0_PDEBUG_PC1_T                                     pdebug_pc1;	//0xC9026058
	O20A0_SPP_MCU_VERSION_T                           spp_mcu_version;	//0xC902605C
	O20A0_INTR_MCU_FLAG_T                               intr_mcu_flag;	//0xC9026060
	O20A0_INTR_MCU_FLAG_EN_T                         intr_mcu_flag_en;	//0xC9026064
	O20A0_INTR_CPU_FLAG_T                               intr_cpu_flag;	//0xC9026068
	O20A0_INTR_CPU_FLAG_EN_T                         intr_cpu_flag_en;	//0xC902606C
	O20A0_GLOBAL_STCC0_T                                 global_stcc0;	//0xC9026070
	O20A0_GLOBAL_STCC1_T                                 global_stcc1;	//0xC9026074
	O20A0_GLOBAL_STCC2_T                                 global_stcc2;	//0xC9026078
	O20A0_GLOBAL_STCC3_T                                 global_stcc3;	//0xC902607C
	O20A0_LIVE_STCC0_T                                     live_stcc0;	//0xC9026080
	O20A0_LIVE_STCC1_T                                     live_stcc1;	//0xC9026084
	O20A0_AD_GEN_00_T                                       ad_gen_00;	//0xC9026088
	O20A0_AD_GEN_01_T                                       ad_gen_01;	//0xC902608C
	O20A0_AD_GEN_02_T                                       ad_gen_02;	//0xC9026090
	O20A0_AD_GEN_03_T                                       ad_gen_03;	//0xC9026094
	O20A0_AD_GEN_04_T                                       ad_gen_04;	//0xC9026098
	O20A0_AD_GEN_05_T                                       ad_gen_05;	//0xC902609C
	O20A0_TIMEOUT_CTRL_T                                 timeout_ctrl;	//0xC90260A0
	O20A0_S0_ADDR_READ_T                                 s0_addr_read;	//0xC90260A4
	O20A0_S1_ADDR_READ_T                                 s1_addr_read;	//0xC90260A8
	UINT32                                                    reserved0;	//0xC90260AC
	O20A0_MASK_START_ADDR_T                           mask_start_addr;	//0xC90260B0
	O20A0_MASK_END_ADDR_T                               mask_end_addr;	//0xC90260B4
	O20A0_MASK_READ_ADDR_T                             mask_read_addr;	//0xC90260B8
	O20A0_AD_INTR_PRIORITY_T                         ad_intr_priority;	//0xC90260BC
	O20A0_AD_UP_COUNTER_T                               ad_up_counter;	//0xC90260C0
	O20A0_RST_ASYNC_BRIDGE_T                         rst_async_bridge;	//0xC90260C4
	O20A0_AD_GEN_06_T                                       ad_gen_06;	//0xC90260C8
	O20A0_AD_GEN_07_T                                       ad_gen_07;	//0xC90260CC
	O20A0_AD_GEN_08_T                                       ad_gen_08;	//0xC90260D0
	O20A0_AD_GEN_09_T                                       ad_gen_09;	//0xC90260D4
	O20A0_AD_GEN_10_T                                       ad_gen_10;	//0xC90260D8
	O20A0_AD_GEN_11_T                                       ad_gen_11;	//0xC90260DC
	O20A0_AD_GEN_12_T                                       ad_gen_12;	//0xC90260E0
	O20A0_AD_GEN_13_T                                       ad_gen_13;	//0xC90260E4
	O20A0_AD_GEN_14_T                                       ad_gen_14;	//0xC90260E8
	O20A0_AD_GEN_15_T                                       ad_gen_15;	//0xC90260EC
	O20A0_INTR_MCU1_FLAG_T                             intr_mcu1_flag;	//0xC90260F0
	O20A0_INTR_MCU1_FLAG_EN_T                       intr_mcu1_flag_en;	//0xC90260F4
	O20A0_SROM_BOOT_MAP3_T                             srom_boot_map3;	//0xC90260F8
	O20A0_SROM_BOOT_MAP4_T                             srom_boot_map4;	//0xC90260FC
	O20A0_CPU_IPC0_T                                         cpu_ipc0;	//0xC9026100
	UINT32                                                    reserved1;	//0xC9026104
	UINT32                                                    reserved2;	//0xC9026108
	UINT32                                                    reserved3;	//0xC902610C
	UINT32                                                    reserved4;	//0xC9026110
	UINT32                                                    reserved5;	//0xC9026114
	UINT32                                                    reserved6;	//0xC9026118
	UINT32                                                    reserved7;	//0xC902611C
	UINT32                                                    reserved8;	//0xC9026120
	UINT32                                                    reserved9;	//0xC9026124
	UINT32                                                   reserved10;	//0xC9026128
	UINT32                                                   reserved11;	//0xC902612C
	UINT32                                                   reserved12;	//0xC9026130
	UINT32                                                   reserved13;	//0xC9026134
	UINT32                                                   reserved14;	//0xC9026138
	UINT32                                                   reserved15;	//0xC902613C
	UINT32                                                   reserved16;	//0xC9026140
	UINT32                                                   reserved17;	//0xC9026144
	UINT32                                                   reserved18;	//0xC9026148
	UINT32                                                   reserved19;	//0xC902614C
	UINT32                                                   reserved20;	//0xC9026150
	UINT32                                                   reserved21;	//0xC9026154
	UINT32                                                   reserved22;	//0xC9026158
	UINT32                                                   reserved23;	//0xC902615C
	UINT32                                                   reserved24;	//0xC9026160
	UINT32                                                   reserved25;	//0xC9026164
	UINT32                                                   reserved26;	//0xC9026168
	UINT32                                                   reserved27;	//0xC902616C
	UINT32                                                   reserved28;	//0xC9026170
	UINT32                                                   reserved29;	//0xC9026174
	UINT32                                                   reserved30;	//0xC9026178
	UINT32                                                   reserved31;	//0xC902617C
	UINT32                                                   reserved32;	//0xC9026180
	UINT32                                                   reserved33;	//0xC9026184
	UINT32                                                   reserved34;	//0xC9026188
	UINT32                                                   reserved35;	//0xC902618C
	UINT32                                                   reserved36;	//0xC9026190
	UINT32                                                   reserved37;	//0xC9026194
	UINT32                                                   reserved38;	//0xC9026198
	UINT32                                                   reserved39;	//0xC902619C
	UINT32                                                   reserved40;	//0xC90261A0
	UINT32                                                   reserved41;	//0xC90261A4
	UINT32                                                   reserved42;	//0xC90261A8
	UINT32                                                   reserved43;	//0xC90261AC
	UINT32                                                   reserved44;	//0xC90261B0
	UINT32                                                   reserved45;	//0xC90261B4
	UINT32                                                   reserved46;	//0xC90261B8
	UINT32                                                   reserved47;	//0xC90261BC
	UINT32                                                   reserved48;	//0xC90261C0
	UINT32                                                   reserved49;	//0xC90261C4
	UINT32                                                   reserved50;	//0xC90261C8
	UINT32                                                   reserved51;	//0xC90261CC
	UINT32                                                   reserved52;	//0xC90261D0
	UINT32                                                   reserved53;	//0xC90261D4
	UINT32                                                   reserved54;	//0xC90261D8
	UINT32                                                   reserved55;	//0xC90261DC
	UINT32                                                   reserved56;	//0xC90261E0
	UINT32                                                   reserved57;	//0xC90261E4
	UINT32                                                   reserved58;	//0xC90261E8
	UINT32                                                   reserved59;	//0xC90261EC
	UINT32                                                   reserved60;	//0xC90261F0
	UINT32                                                   reserved61;	//0xC90261F4
	UINT32                                                   reserved62;	//0xC90261F8
	O20A0_CPU_IPC63_T                                       cpu_ipc63;	//0xC90261FC
	O20A0_VDEC_VENC_IPC0_T                             vdec_venc_ipc0;	//0xC9026200
	UINT32                                                   reserved63;	//0xC9026204
	UINT32                                                   reserved64;	//0xC9026208
	UINT32                                                   reserved65;	//0xC902620C
	UINT32                                                   reserved66;	//0xC9026210
	UINT32                                                   reserved67;	//0xC9026214
	UINT32                                                   reserved68;	//0xC9026218
	UINT32                                                   reserved69;	//0xC902621C
	UINT32                                                   reserved70;	//0xC9026220
	UINT32                                                   reserved71;	//0xC9026224
	UINT32                                                   reserved72;	//0xC9026228
	UINT32                                                   reserved73;	//0xC902622C
	UINT32                                                   reserved74;	//0xC9026230
	UINT32                                                   reserved75;	//0xC9026234
	UINT32                                                   reserved76;	//0xC9026238
	UINT32                                                   reserved77;	//0xC902623C
	UINT32                                                   reserved78;	//0xC9026240
	UINT32                                                   reserved79;	//0xC9026244
	UINT32                                                   reserved80;	//0xC9026248
	UINT32                                                   reserved81;	//0xC902624C
	UINT32                                                   reserved82;	//0xC9026250
	UINT32                                                   reserved83;	//0xC9026254
	UINT32                                                   reserved84;	//0xC9026258
	UINT32                                                   reserved85;	//0xC902625C
	UINT32                                                   reserved86;	//0xC9026260
	UINT32                                                   reserved87;	//0xC9026264
	UINT32                                                   reserved88;	//0xC9026268
	UINT32                                                   reserved89;	//0xC902626C
	UINT32                                                   reserved90;	//0xC9026270
	UINT32                                                   reserved91;	//0xC9026274
	UINT32                                                   reserved92;	//0xC9026278
	UINT32                                                   reserved93;	//0xC902627C
	UINT32                                                   reserved94;	//0xC9026280
	UINT32                                                   reserved95;	//0xC9026284
	UINT32                                                   reserved96;	//0xC9026288
	UINT32                                                   reserved97;	//0xC902628C
	UINT32                                                   reserved98;	//0xC9026290
	UINT32                                                   reserved99;	//0xC9026294
	UINT32                                                  reserved100;	//0xC9026298
	UINT32                                                  reserved101;	//0xC902629C
	UINT32                                                  reserved102;	//0xC90262A0
	UINT32                                                  reserved103;	//0xC90262A4
	UINT32                                                  reserved104;	//0xC90262A8
	UINT32                                                  reserved105;	//0xC90262AC
	UINT32                                                  reserved106;	//0xC90262B0
	UINT32                                                  reserved107;	//0xC90262B4
	UINT32                                                  reserved108;	//0xC90262B8
	UINT32                                                  reserved109;	//0xC90262BC
	UINT32                                                  reserved110;	//0xC90262C0
	UINT32                                                  reserved111;	//0xC90262C4
	UINT32                                                  reserved112;	//0xC90262C8
	UINT32                                                  reserved113;	//0xC90262CC
	UINT32                                                  reserved114;	//0xC90262D0
	UINT32                                                  reserved115;	//0xC90262D4
	UINT32                                                  reserved116;	//0xC90262D8
	UINT32                                                  reserved117;	//0xC90262DC
	UINT32                                                  reserved118;	//0xC90262E0
	UINT32                                                  reserved119;	//0xC90262E4
	UINT32                                                  reserved120;	//0xC90262E8
	UINT32                                                  reserved121;	//0xC90262EC
	UINT32                                                  reserved122;	//0xC90262F0
	UINT32                                                  reserved123;	//0xC90262F4
	UINT32                                                  reserved124;	//0xC90262F8
	O20A0_VDEC_VENC_IPC63_T                           vdec_venc_ipc63;	//0xC90262FC
	O20A0_VDEC_VENC_IPC64_T                           vdec_venc_ipc64;	//0xC9026300
	UINT32                                                  reserved125;	//0xC9026304
	UINT32                                                  reserved126;	//0xC9026308
	UINT32                                                  reserved127;	//0xC902630C
	UINT32                                                  reserved128;	//0xC9026310
	UINT32                                                  reserved129;	//0xC9026314
	UINT32                                                  reserved130;	//0xC9026318
	UINT32                                                  reserved131;	//0xC902631C
	UINT32                                                  reserved132;	//0xC9026320
	UINT32                                                  reserved133;	//0xC9026324
	UINT32                                                  reserved134;	//0xC9026328
	UINT32                                                  reserved135;	//0xC902632C
	UINT32                                                  reserved136;	//0xC9026330
	UINT32                                                  reserved137;	//0xC9026334
	UINT32                                                  reserved138;	//0xC9026338
	UINT32                                                  reserved139;	//0xC902633C
	UINT32                                                  reserved140;	//0xC9026340
	UINT32                                                  reserved141;	//0xC9026344
	UINT32                                                  reserved142;	//0xC9026348
	UINT32                                                  reserved143;	//0xC902634C
	UINT32                                                  reserved144;	//0xC9026350
	UINT32                                                  reserved145;	//0xC9026354
	UINT32                                                  reserved146;	//0xC9026358
	UINT32                                                  reserved147;	//0xC902635C
	UINT32                                                  reserved148;	//0xC9026360
	UINT32                                                  reserved149;	//0xC9026364
	UINT32                                                  reserved150;	//0xC9026368
	UINT32                                                  reserved151;	//0xC902636C
	UINT32                                                  reserved152;	//0xC9026370
	UINT32                                                  reserved153;	//0xC9026374
	UINT32                                                  reserved154;	//0xC9026378
	UINT32                                                  reserved155;	//0xC902637C
	UINT32                                                  reserved156;	//0xC9026380
	UINT32                                                  reserved157;	//0xC9026384
	UINT32                                                  reserved158;	//0xC9026388
	UINT32                                                  reserved159;	//0xC902638C
	UINT32                                                  reserved160;	//0xC9026390
	UINT32                                                  reserved161;	//0xC9026394
	UINT32                                                  reserved162;	//0xC9026398
	UINT32                                                  reserved163;	//0xC902639C
	UINT32                                                  reserved164;	//0xC90263A0
	UINT32                                                  reserved165;	//0xC90263A4
	UINT32                                                  reserved166;	//0xC90263A8
	UINT32                                                  reserved167;	//0xC90263AC
	UINT32                                                  reserved168;	//0xC90263B0
	UINT32                                                  reserved169;	//0xC90263B4
	UINT32                                                  reserved170;	//0xC90263B8
	UINT32                                                  reserved171;	//0xC90263BC
	UINT32                                                  reserved172;	//0xC90263C0
	UINT32                                                  reserved173;	//0xC90263C4
	UINT32                                                  reserved174;	//0xC90263C8
	UINT32                                                  reserved175;	//0xC90263CC
	UINT32                                                  reserved176;	//0xC90263D0
	UINT32                                                  reserved177;	//0xC90263D4
	UINT32                                                  reserved178;	//0xC90263D8
	O20A0_VDEC_VENC_IPC119_T                         vdec_venc_ipc119;	//0xC90263DC
	O20A0_PQE_INTR_EVENT_T                             pqe_intr_event;	//0xC90263E0
	O20A0_PQE_INTR_ENABLE_T                           pqe_intr_enable;	//0xC90263E4
	O20A0_PQE_INTR_STATUS_T                           pqe_intr_status;	//0xC90263E8
	O20A0_PQE_INTR_CLEAR_T                             pqe_intr_clear;	//0xC90263EC
	O20A0_VDEC_INTR_EVENT_T                           vdec_intr_event;	//0xC90263F0
	O20A0_VDEC_INTR_ENABLE_T                         vdec_intr_enable;	//0xC90263F4
	O20A0_VDEC_INTR_STATUS_T                         vdec_intr_status;	//0xC90263F8
	O20A0_VDEC_INTR_CLEAR_T                           vdec_intr_clear;	//0xC90263FC
	O20A0_GEN_IPC0_T                                         gen_ipc0;	//0xC9026400
	UINT32                                                  reserved179;	//0xC9026404
	UINT32                                                  reserved180;	//0xC9026408
	UINT32                                                  reserved181;	//0xC902640C
	UINT32                                                  reserved182;	//0xC9026410
	UINT32                                                  reserved183;	//0xC9026414
	UINT32                                                  reserved184;	//0xC9026418
	UINT32                                                  reserved185;	//0xC902641C
	UINT32                                                  reserved186;	//0xC9026420
	UINT32                                                  reserved187;	//0xC9026424
	UINT32                                                  reserved188;	//0xC9026428
	UINT32                                                  reserved189;	//0xC902642C
	UINT32                                                  reserved190;	//0xC9026430
	UINT32                                                  reserved191;	//0xC9026434
	UINT32                                                  reserved192;	//0xC9026438
	UINT32                                                  reserved193;	//0xC902643C
	UINT32                                                  reserved194;	//0xC9026440
	UINT32                                                  reserved195;	//0xC9026444
	UINT32                                                  reserved196;	//0xC9026448
	UINT32                                                  reserved197;	//0xC902644C
	UINT32                                                  reserved198;	//0xC9026450
	UINT32                                                  reserved199;	//0xC9026454
	UINT32                                                  reserved200;	//0xC9026458
	UINT32                                                  reserved201;	//0xC902645C
	UINT32                                                  reserved202;	//0xC9026460
	UINT32                                                  reserved203;	//0xC9026464
	UINT32                                                  reserved204;	//0xC9026468
	UINT32                                                  reserved205;	//0xC902646C
	UINT32                                                  reserved206;	//0xC9026470
	UINT32                                                  reserved207;	//0xC9026474
	UINT32                                                  reserved208;	//0xC9026478
	UINT32                                                  reserved209;	//0xC902647C
	UINT32                                                  reserved210;	//0xC9026480
	UINT32                                                  reserved211;	//0xC9026484
	UINT32                                                  reserved212;	//0xC9026488
	UINT32                                                  reserved213;	//0xC902648C
	UINT32                                                  reserved214;	//0xC9026490
	UINT32                                                  reserved215;	//0xC9026494
	UINT32                                                  reserved216;	//0xC9026498
	UINT32                                                  reserved217;	//0xC902649C
	UINT32                                                  reserved218;	//0xC90264A0
	UINT32                                                  reserved219;	//0xC90264A4
	UINT32                                                  reserved220;	//0xC90264A8
	UINT32                                                  reserved221;	//0xC90264AC
	UINT32                                                  reserved222;	//0xC90264B0
	UINT32                                                  reserved223;	//0xC90264B4
	UINT32                                                  reserved224;	//0xC90264B8
	UINT32                                                  reserved225;	//0xC90264BC
	UINT32                                                  reserved226;	//0xC90264C0
	UINT32                                                  reserved227;	//0xC90264C4
	UINT32                                                  reserved228;	//0xC90264C8
	UINT32                                                  reserved229;	//0xC90264CC
	UINT32                                                  reserved230;	//0xC90264D0
	UINT32                                                  reserved231;	//0xC90264D4
	UINT32                                                  reserved232;	//0xC90264D8
	UINT32                                                  reserved233;	//0xC90264DC
	UINT32                                                  reserved234;	//0xC90264E0
	UINT32                                                  reserved235;	//0xC90264E4
	UINT32                                                  reserved236;	//0xC90264E8
	UINT32                                                  reserved237;	//0xC90264EC
	UINT32                                                  reserved238;	//0xC90264F0
	UINT32                                                  reserved239;	//0xC90264F4
	UINT32                                                  reserved240;	//0xC90264F8
	UINT32                                                  reserved241;	//0xC90264FC
	UINT32                                                  reserved242;	//0xC9026500
	UINT32                                                  reserved243;	//0xC9026504
	UINT32                                                  reserved244;	//0xC9026508
	UINT32                                                  reserved245;	//0xC902650C
	UINT32                                                  reserved246;	//0xC9026510
	UINT32                                                  reserved247;	//0xC9026514
	UINT32                                                  reserved248;	//0xC9026518
	UINT32                                                  reserved249;	//0xC902651C
	UINT32                                                  reserved250;	//0xC9026520
	UINT32                                                  reserved251;	//0xC9026524
	UINT32                                                  reserved252;	//0xC9026528
	UINT32                                                  reserved253;	//0xC902652C
	UINT32                                                  reserved254;	//0xC9026530
	UINT32                                                  reserved255;	//0xC9026534
	UINT32                                                  reserved256;	//0xC9026538
	UINT32                                                  reserved257;	//0xC902653C
	UINT32                                                  reserved258;	//0xC9026540
	UINT32                                                  reserved259;	//0xC9026544
	UINT32                                                  reserved260;	//0xC9026548
	UINT32                                                  reserved261;	//0xC902654C
	UINT32                                                  reserved262;	//0xC9026550
	UINT32                                                  reserved263;	//0xC9026554
	UINT32                                                  reserved264;	//0xC9026558
	UINT32                                                  reserved265;	//0xC902655C
	UINT32                                                  reserved266;	//0xC9026560
	UINT32                                                  reserved267;	//0xC9026564
	UINT32                                                  reserved268;	//0xC9026568
	UINT32                                                  reserved269;	//0xC902656C
	UINT32                                                  reserved270;	//0xC9026570
	UINT32                                                  reserved271;	//0xC9026574
	UINT32                                                  reserved272;	//0xC9026578
	UINT32                                                  reserved273;	//0xC902657C
	UINT32                                                  reserved274;	//0xC9026580
	UINT32                                                  reserved275;	//0xC9026584
	UINT32                                                  reserved276;	//0xC9026588
	UINT32                                                  reserved277;	//0xC902658C
	UINT32                                                  reserved278;	//0xC9026590
	UINT32                                                  reserved279;	//0xC9026594
	UINT32                                                  reserved280;	//0xC9026598
	UINT32                                                  reserved281;	//0xC902659C
	UINT32                                                  reserved282;	//0xC90265A0
	UINT32                                                  reserved283;	//0xC90265A4
	UINT32                                                  reserved284;	//0xC90265A8
	UINT32                                                  reserved285;	//0xC90265AC
	UINT32                                                  reserved286;	//0xC90265B0
	UINT32                                                  reserved287;	//0xC90265B4
	UINT32                                                  reserved288;	//0xC90265B8
	UINT32                                                  reserved289;	//0xC90265BC
	UINT32                                                  reserved290;	//0xC90265C0
	UINT32                                                  reserved291;	//0xC90265C4
	UINT32                                                  reserved292;	//0xC90265C8
	UINT32                                                  reserved293;	//0xC90265CC
	UINT32                                                  reserved294;	//0xC90265D0
	UINT32                                                  reserved295;	//0xC90265D4
	UINT32                                                  reserved296;	//0xC90265D8
	UINT32                                                  reserved297;	//0xC90265DC
	UINT32                                                  reserved298;	//0xC90265E0
	UINT32                                                  reserved299;	//0xC90265E4
	UINT32                                                  reserved300;	//0xC90265E8
	UINT32                                                  reserved301;	//0xC90265EC
	UINT32                                                  reserved302;	//0xC90265F0
	UINT32                                                  reserved303;	//0xC90265F4
	UINT32                                                  reserved304;	//0xC90265F8
	O20A0_GEN_IPC127_T                                     gen_ipc127;	//0xC90265FC
	O20A0_TX_LOCKED_ID_T                                 tx_locked_id;	//0xC9026600
	O20A0_TX_SRC_ADDR_T                                   tx_src_addr;	//0xC9026604
	O20A0_TX_DST_ADDR_T                                   tx_dst_addr;	//0xC9026608
	O20A0_TX_NXT_ADDR_T                                   tx_nxt_addr;	//0xC902660C
	O20A0_TX_LENGTH_T                                       tx_length;	//0xC9026610
	O20A0_EDMA_CTRL_T                                       edma_ctrl;	//0xC9026614
} DE_IPC_REG_O20A0_T;

#endif
