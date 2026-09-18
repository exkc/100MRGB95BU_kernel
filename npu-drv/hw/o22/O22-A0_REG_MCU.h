//#include <COMMON/option.h>
#ifndef _REG_MCU_h
#define _REG_MCU_h
//Header File for MCU in \PQE\O22-A0_PQE_MCU_reg_man.xls

#define REG_MCU_SET_REG_CTRL0                                                   (APB_MCU_BASE+0x0000)
#define REG_MCU_SET_REG_CTRL1                                                   (APB_MCU_BASE+0x0004)
#define REG_MCU_EXT_INTR_EVENT                                                  (APB_MCU_BASE+0x0008)
#define REG_MCU_EXT_INTR_ENABLE                                                 (APB_MCU_BASE+0x000C)
#define REG_MCU_EXT_INTR_STATUS                                                 (APB_MCU_BASE+0x0010)
#define REG_MCU_EXT_INTR_CLEAR                                                  (APB_MCU_BASE+0x0014)
#define REG_MCU_INT_INTR_EVENT                                                  (APB_MCU_BASE+0x0018)
#define REG_MCU_INT_INTR_ENABLE                                                 (APB_MCU_BASE+0x001C)
#define REG_MCU_INT_INTR_STATUS                                                 (APB_MCU_BASE+0x0020)
#define REG_MCU_INT_INTR_CLEAR                                                  (APB_MCU_BASE+0x0024)
#define REG_MCU_SROM_BOOT_MAP1                                                  (APB_MCU_BASE+0x0028)
#define REG_MCU_SROM_BOOT_MAP2                                                  (APB_MCU_BASE+0x002C)
#define REG_MCU_SRAM_PORT_SEL                                                   (APB_MCU_BASE+0x0030)
#define REG_MCU_PDEBUG_STATUS                                                   (APB_MCU_BASE+0x0034)
#define REG_MCU_PDEBUG_DATA                                                     (APB_MCU_BASE+0x0038)
#define REG_MCU_PDEBUG_PC                                                       (APB_MCU_BASE+0x003C)
#define REG_MCU_AXI_USER_ID                                                     (APB_MCU_BASE+0x0040)
#define REG_MCU_SRAM0_OFFSET                                                    (APB_MCU_BASE+0x0044)
#define REG_MCU_SRAM1_OFFSET                                                    (APB_MCU_BASE+0x0048)
#define REG_MCU_SRAM2_OFFSET                                                    (APB_MCU_BASE+0x004C)
#define REG_MCU_SRAM3_OFFSET                                                    (APB_MCU_BASE+0x0050)
#define REG_MCU_PDEBUG_DATA1                                                    (APB_MCU_BASE+0x0054)
#define REG_MCU_PDEBUG_PC1                                                      (APB_MCU_BASE+0x0058)
#define REG_MCU_SPP_MCU_VERSION                                                 (APB_MCU_BASE+0x005C)
#define REG_MCU_INTR_MCU_FLAG                                                   (APB_MCU_BASE+0x0060)
#define REG_MCU_INTR_MCU_FLAG_EN                                                (APB_MCU_BASE+0x0064)
#define REG_MCU_INTR_CPU_FLAG                                                   (APB_MCU_BASE+0x0068)
#define REG_MCU_INTR_CPU_FLAG_EN                                                (APB_MCU_BASE+0x006C)
#define REG_MCU_GLOBAL_STCC0                                                    (APB_MCU_BASE+0x0070)
#define REG_MCU_GLOBAL_STCC1                                                    (APB_MCU_BASE+0x0074)
#define REG_MCU_GLOBAL_STCC2                                                    (APB_MCU_BASE+0x0078)
#define REG_MCU_GLOBAL_STCC3                                                    (APB_MCU_BASE+0x007C)
#define REG_MCU_LIVE_STCC0                                                      (APB_MCU_BASE+0x0080)
#define REG_MCU_LIVE_STCC1                                                      (APB_MCU_BASE+0x0084)
#define REG_MCU_AD_APB_TOUT_CTRL                                                (APB_MCU_BASE+0x0088)
#define REG_MCU_AD_APB_TOUT_CNT                                                 (APB_MCU_BASE+0x008C)
#define REG_MCU_APB_TOUT_CTRL_CH0_ADR                                           (APB_MCU_BASE+0x0090)
#define REG_MCU_APB_TOUT_CTRL_CH0_PW                                            (APB_MCU_BASE+0x0094)
#define REG_MCU_APB_TOUT_CTRL_CH0_PWDATA                                        (APB_MCU_BASE+0x0098)
#define REG_MCU_APB_TOUT_CTRL_CH1_ADR                                           (APB_MCU_BASE+0x009C)
#define REG_MCU_APB_TOUT_CTRL_CH1_PW                                            (APB_MCU_BASE+0x00A0)
#define REG_MCU_APB_TOUT_CTRL_CH1_PWDATA                                        (APB_MCU_BASE+0x00A4)
#define REG_MCU_APB_TOUT_CTRL_CH2_ADR                                           (APB_MCU_BASE+0x00A8)
#define REG_MCU_APB_TOUT_CTRL_CH2_PW                                            (APB_MCU_BASE+0x00AC)
#define REG_MCU_APB_TOUT_CTRL_CH2_PWDATA                                        (APB_MCU_BASE+0x00B0)
#define REG_MCU_APB_TOUT_CTRL_CH3_ADR                                           (APB_MCU_BASE+0x00B4)
#define REG_MCU_APB_TOUT_CTRL_CH3_PW                                            (APB_MCU_BASE+0x00B8)
#define REG_MCU_APB_TOUT_CTRL_CH3_PWDATA                                        (APB_MCU_BASE+0x00BC)
#define REG_MCU_AD_MASK_START_ADDR                                              (APB_MCU_BASE+0x00C0)
#define REG_MCU_AD_MASK_END_ADDR                                                (APB_MCU_BASE+0x00C4)
#define REG_MCU_AD_MASK_READ_ADDR                                               (APB_MCU_BASE+0x00C8)
#define REG_MCU_AD_INTR_PRIORITY                                                (APB_MCU_BASE+0x00CC)
#define REG_MCU_AD_UP_COUNTER                                                   (APB_MCU_BASE+0x00D0)
#define REG_MCU_RST_ASYNC_BRIDGE                                                (APB_MCU_BASE+0x00D4)
#define REG_MCU_PFAULT_STATUS0                                                  (APB_MCU_BASE+0x00D8)
#define REG_MCU_PFAULT_STATUS1                                                  (APB_MCU_BASE+0x00DC)
#define REG_MCU_PFAULT_STATUS2                                                  (APB_MCU_BASE+0x00E0)
#define REG_MCU_SRAM4_OFFSET                                                    (APB_MCU_BASE+0x00E4)
#define REG_MCU_SRAM5_OFFSET                                                    (APB_MCU_BASE+0x00E8)
#define REG_MCU_INTR_MCU1_FLAG                                                  (APB_MCU_BASE+0x00EC)
#define REG_MCU_INTR_MCU1_FLAG_EN                                               (APB_MCU_BASE+0x00F0)
#define REG_MCU_SROM_BOOT_MAP3                                                  (APB_MCU_BASE+0x00F4)
#define REG_MCU_SROM_BOOT_MAP4                                                  (APB_MCU_BASE+0x00F8)

typedef union {
	UINT32 udata32;
	struct {						//0xCC080000 RW/RO 0x0003_0003
	UINT32 run_stall                        :1;	//(0,RW,0x01) //0  = run	1 := stall
	UINT32 start_vector_sel                 :1;	//(1,RW,0x01) //select reset vector	0  = SROM	1 := IRAM
	UINT32 p_debug_enable                   :1;	//(2,RW,0x00) //Trace output port enable	0 := disable	1  = enable
	UINT32 tmode_clkgate_override           :1;	//(3,RW,0x00) //1: ClkGateDisable in test mode
	UINT32 flush_rst_ctrl_status            :4;	//(7:4,RO,0x00) //Only Debug
	UINT32 soft_reset_without_fdone         :1;	//(8,RW,0x00) //MCU Software Reset without flush done	0 := disable	1  = Reset
	UINT32 uart0_mux                        :1;	//(9,RW,0x0) //0 : = uart0	1   = uart1
	UINT32 uart1_mux                        :1;	//(10,RW,0x0) //0 : = uart1	1   = uart0
	UINT32 reg_i2c_sel                      :1;	//(11,RW,0x0) //0 : = I2C vhdl	1   = I2C verilog(W22)
	UINT32 resvd0                           :4;
	UINT32 run_stall1                       :1;	//(16,RW,0x01) //0  = run	1 := stall
	UINT32 start_vector_sel1                :1;	//(17,RW,0x01) //select reset vector	0  = SROM	1 := IRAM
	UINT32 p_debug_enable1                  :1;	//(18,RW,0x00) //Trace output port enable	0 := disable	1  = enable
	UINT32 tmode_clkgate_override1          :1;	//(19,RW,0x00) //1: ClkGateDisable in test mode
	UINT32 resvd1                           :8;
	UINT32 soft_reset                       :1;	//(28,RW,0x00) //MCU Software Reset	0 := disable	1  = Reset
	UINT32 resvd2                           :3;
	};
}REG_MCU_SET_REG_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080004 RW 0x0000_0000
	UINT32 prid                             :16;	//(15:0,RW,0x0) //
	UINT32 prid1                            :16;	//(31:16,RW,0x0) //
	};
}REG_MCU_SET_REG_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080008 RW 0x0000_0000
	UINT32 reserved0                        :19;//18:0
	UINT32 gps_interrupt            		:1; //19 //MCU gps interrupt enable
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt event
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt event
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt event
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt event
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt event
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt event
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt event
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt event
	UINT32 reserved1						:1; //29 reserved
	UINT32 wdg_interrupt_event_mcu1         :1;	//30 //MCU1 watch dog interrupt event
	UINT32 wdg_interrupt_event              :1;	//31 //MCU watch dog interrupt event
	};
}REG_MCU_EXT_INTR_EVENT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08000C RW 0x0000_0000
	UINT32 reserved0                        :19;//19:0
	UINT32 gps_interrupt            		:1; //19 //MCU gps interrupt enable
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt enable
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt enable
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt enable
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt enable
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt enable
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt enable
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt enable
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt enable
	UINT32 reserved1						:1; //29 reserved
	UINT32 wdg_interrupt_enable_mcu1        :1;	//(30,RO,0x00) //MCU1 watch dog interrupt enable
	UINT32 wdg_interrupt_enable             :1;	//(31,RO,0x00) //MCU watch dog interrupt enable
	};
}REG_MCU_EXT_INTR_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080010 RO 0x0000_0000
	UINT32 reserved0                        :19;//18:0
	UINT32 gps_interrupt            		:1; //19 //MCU gps interrupt enable
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt status
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt status
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt status
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt status
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt status
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt status
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt status
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt status
	UINT32 reserved1						:1; //29 reserved
	UINT32 wdg_interrupt_status_mcu1        :1;	//(30,RO,0x00) //MCU1 watch dog interrupt status
	UINT32 wdg_interrupt_status             :1;	//(31,RO,0x00) //MCU watch dog interrupt status
	};
}REG_MCU_EXT_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080014 WO 0x0000_0000
	UINT32 reserved0                        :20;//19:0
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt clear
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt clear
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt clear
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt clear
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt clear
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt clear
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt clear
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt clear
	UINT32 reserved1						:1; //29 reserved
	UINT32 wdg_interrupt_clear_mcu1         :1;	//(30,RO,0x00) //MCU1 watch dog interrupt clear
	UINT32 wdg_interrupt_clear              :1;	//(31,RO,0x00) //MCU watch dog interrupt clear
	};
}REG_MCU_EXT_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080018 RO 0x0000_0000
	UINT32 reserved0                        :20;//19:0
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt event
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt event
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt event
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt event
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt event
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt event
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt event
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt event
	UINT32 edma_interrupt_event_mcu         :1;	//(29,RO,0x00) //eDMA interrupt event for MCU
	UINT32 resvd                            :2;
	};
}REG_MCU_INT_INTR_EVENT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08001C RW 0x0000_0000
	UINT32 reserved0                        :20;//19:0
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt enable
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt enable
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt enable
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt enable
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt enable
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt enable
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt enable
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt enable
	UINT32 edma_interrupt_enable_mcu        :1;	//(29,RW,0x00) //eDMA interrupt enable for MCU
	UINT32 resvd                            :2;
	};
}REG_MCU_INT_INTR_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080020 RO 0x0000_0000
	UINT32 reserved0                        :20;//19:0
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt status
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt status
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt status
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt status
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt status
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt status
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt status
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt status
	UINT32 edma_interrupt_status_mcu        :1;	//(29,RO,0x00) //eDMA interrupt enable for MCU
	UINT32 resvd                            :2;
	};
}REG_MCU_INT_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080024 WO 0x0000_0000
	UINT32 reserved0                        :20;//19:0
	UINT32 video_delay_interrupt            :1; //20
	UINT32 ipc_interrupt                    :1;	//21 //MCU ipc interrupt clear
	UINT32 dhdr_interrupt                   :1; //22 //MCU wer interrupt clear
	UINT32 tnr_interrupt                    :1; //23 //MCU tnr interrupt clear
	UINT32 disp_interrupt                   :1;	//24 //MCU disp interrupt clear
	UINT32 vtg_interrupt                    :1;	//25 //MCU vtg interrupt clear
	UINT32 vr360_interrupt                  :1;	//26 //MCU usb interrupt clear
	UINT32 jpg_interrupt                    :1;	//27 //MCU jpg interrupt clear
	UINT32 ack_interrupt                    :1;	//28 //MCU ack interrupt clear
	UINT32 edma_interrupt_clear_mcu         :1;	//(29,WO,0x00) //eDMA interrupt enable for MCU - This register is auto cleared after set 1
	UINT32 resvd                            :2;
	};
}REG_MCU_INT_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080028 RW 0x5000_0000
	UINT32 boot_img_map1                    :32;	//(31:0,RW,0x5000_0000) //when AXI address of PL301 output is 0x5000_0000 ~ 0x501F_FFFF	physical image address in DDR region is 0x0000_0000 + boot_img_map1	Default : 0x5000_0000 ~ 0x501F_FFFF	(real write region : 0x5000_0000 ~ 0x501F_FFFF => 0x5000_0000 ~ 0x501F_FFFF
	};
}REG_MCU_SROM_BOOT_MAP1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08002C RW 0x5000_0000
	UINT32 boot_img_map2                    :32;	//(31:0,RW,0x5000_0000) //when AXI address of PL301 output is 0x5020_0000 ~ 0x503F_FFFF	physical image address in DDR region is 0x0020_0000 + boot_img_map2	Default : 0x5020_0000 ~ 0x503F_FFFF	(real write region : 0x5020_0000 ~ 0x503F_FFFF => 0x5020_0000 ~ 0x503F_FFFF
	};
}REG_MCU_SROM_BOOT_MAP2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080030 RW 0x0000_BA98
	UINT32 sram0_port_sel                   :4;	//(3:0,RW,0x08) //when AXI address of PL301 output is 0x8000_0000 ~ 0x8FFF_FFFF	select sram0_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0x8000_0000 ~ 0x8FFF_FFFF => 0x8000_0000 ~ 0x8FFF_FFFF
	UINT32 sram1_port_sel                   :4;	//(7:4,RW,0x09) //when AXI address of PL301 output is 0x9000_0000 ~ 0x9FFF_FFFF	select sram1_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0x9000_0000 ~ 0x9FFF_FFFF => 0x9000_0000 ~ 0x9FFF_FFFF
	UINT32 sram2_port_sel                   :4;	//(11:8,RW,0x0A) //when AXI address of PL301 output is 0xA000_0000 ~ 0xAFFF_FFFF	select sram2_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0xA000_0000 ~ 0xAFFF_FFFF => 0xA000_0000 ~ 0xAFFF_FFFF
	UINT32 sram3_port_sel                   :4;	//(15:12,RW,0x0B) //when AXI address of PL301 output is 0xB000_0000 ~ 0xBFFF_FFFF	select sram0_atlas_port_sel[3:0] = addr[31:28] , 256MB unit	default : 0xB000_0000 ~ 0xBFFF_FFFF => 0xB000_0000 ~ 0xBFFF_FFFF
	UINT32 reserved                         :1;	//(16,Rsvd,0x00) //
	UINT32 resvd                            :15;
	};
}REG_MCU_SRAM_PORT_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080034 RO 0x0000_0000
	UINT32 pdebug_status                    :8;	//(7:0,RO,0x0) //
	UINT32 pdebug_status1                   :8;	//(15:8,RO,0x0) //
	UINT32 resvd                            :16;
	};
}REG_MCU_PDEBUG_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080038 RO 0x0000_0000
	UINT32 pdebug_data                      :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_MCU_PDEBUG_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08003C RO 0x0000_0000
	UINT32 pdebug_pc                        :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_MCU_PDEBUG_PC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080040 RW 0x0000_0000
	UINT32 s0_aw_user_id                    :4;	//(3:0,RW,0x00) //
	UINT32 s0_ar_user_id                    :4;	//(7:4,RW,0x00) //
	UINT32 s1_aw_user_id                    :4;	//(11:8,RW,0x00) //
	UINT32 s1_ar_user_id                    :4;	//(15:12,RW,0x00) //
	UINT32 resvd                            :16;
	};
}REG_MCU_AXI_USER_ID_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080044 RW 0x0000_0000
	UINT32 sram0_offset                     :32;	//(31:0,RW,0x0000_0000) //when AXI address of PL301 output is 0x8000_0000 ~ 0x8FFF_FFFF	{sram0_port_sel[3:0],AXI_ADDR[27:0] + sram0_offset}
	};
}REG_MCU_SRAM0_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080048 RW 0x0000_0000
	UINT32 sram1_offset                     :32;	//(31:0,RW,0x0000_0000) //when AXI address of PL301 output is 0x9000_0000 ~ 0x9FFF_FFFF	{sram1_port_sel[3:0],AXI_ADDR[27:0] + sram1_offset}
	};
}REG_MCU_SRAM1_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08004C RW 0x0000_0000
	UINT32 sram2_offset                     :32;	//(31:0,RW,0x0000_0000) //when AXI address of PL301 output is 0xA000_0000 ~ 0xAFFF_FFFF	{sram2_port_sel[3:0],AXI_ADDR[27:0] + sram2_offset}
	};
}REG_MCU_SRAM2_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080050 RW 0x0000_0000
	UINT32 sram3_offset                     :32;	//(31:0,RW,0x0000_0000) //when AXI address of PL301 output is 0xB000_0000 ~ 0xBFFF_FFFF	{sram3_port_sel[3:0],AXI_ADDR[27:0] + sram3_offset}
	};
}REG_MCU_SRAM3_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080054 RO 0x0000_0000
	UINT32 pdebug_data1                     :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_MCU_PDEBUG_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080058 RO 0x0000_0000
	UINT32 pdebug_pc1                       :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_MCU_PDEBUG_PC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08005C RO 0x2020_0301
	UINT32 mcu_version                      :32;	//(31:0,RO,0x2020_0301) //
	};
}REG_MCU_SPP_MCU_VERSION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080060 RO 0x0000_0000
	UINT32 cvi_mcu_intr_mcu                 :1;	//(0,RO,0x00) //
	UINT32 imx_mcu_intr_mcu                 :1;	//(1,RO,0x00) //
	UINT32 hdr_mcu_intr_mcu                 :1;	//(2,RO,0x00) //
	UINT32 nd0_mcu_intr_mcu                 :1;	//(3,RO,0x00) //
	UINT32 nd1_mcu_intr_mcu                 :1;	//(4,RO,0x00) //
	UINT32 me0_mcu_intr_mcu                 :1;	//(5,RO,0x00) //
	UINT32 me1_mcu_intr_mcu                 :1;	//(6,RO,0x00) //
	UINT32 fmc_mcu_intr_mcu                 :1;	//(7,RO,0x00) //
	UINT32 fms_mcu_intr_mcu                 :1;	//(8,RO,0x00) //
	UINT32 gsc_mcu_intr_mcu                 :1;	//(9,RO,0x00) //
	UINT32 sre_mcu_intr_mcu                 :1;	//(10,RO,0x00) //
	UINT32 vsd_mcu_intr_mcu                 :1;	//(11,RO,0x00) //
	UINT32 cco_mcu_intr_mcu                 :1;	//(12,RO,0x00) //
	UINT32 led_mcu_intr_mcu                 :1;	//(13,RO,0x00) //
	UINT32 ldm_mcu_intr_mcu                 :1;	//(14,RO,0x00) //
	UINT32 vdec_mcu_intr_mcu                :1;	//(15,RO,0x00) //
	UINT32 dpe_mcu_intr_mcu                 :1;	//(16,RO,0x00) //
	UINT32 sr_mcu_intr_mcu                  :1;	//(17,RO,0x00) //
	UINT32 dne_mcu_intr_mcu                 :1;	//(18,RO,0x00) //
	UINT32 gav_mcu_intr_mcu                 :1;	//(19,RO,0x00) //
	UINT32 lne0_mcu_intr_mcu                :1;	//(20,RO,0x00) //
	UINT32 lne1_mcu_intr_mcu                :1;	//(21,RO,0x00) //
	UINT32 vdo_mcu_intr_mcu                 :1;	//(22,RO,0x00) //
	UINT32 i2c_mcu_intr_mcu                 :1;	//(23,RO,0x00) //
	UINT32 mcu0_mcu_intr_mcu                :1;	//(24,RO,0x00) //
	UINT32 mcu1_mcu_intr_mcu                :1;	//(25,RO,0x00) //
	UINT32 reserved                         :6;	//(31:26,Rsvd,0x0) //
	};
}REG_MCU_INTR_MCU_FLAG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080064 RW 0x0000_0000
	UINT32 cvi_mcu_intr_mcu_en              :1;	//(0,RW,0x00) //
	UINT32 imx_mcu_intr_mcu_en              :1;	//(1,RW,0x00) //
	UINT32 hdr_mcu_intr_mcu_en              :1;	//(2,RW,0x00) //
	UINT32 nd0_mcu_intr_mcu_en              :1;	//(3,RW,0x00) //
	UINT32 nd1_mcu_intr_mcu_en              :1;	//(4,RW,0x00) //
	UINT32 me0_mcu_intr_mcu_en              :1;	//(5,RW,0x00) //
	UINT32 me1_mcu_intr_mcu_en              :1;	//(6,RW,0x00) //
	UINT32 fmc_mcu_intr_mcu_en              :1;	//(7,RW,0x00) //
	UINT32 fms_mcu_intr_mcu_en              :1;	//(8,RW,0x00) //
	UINT32 gsc_mcu_intr_mcu_en              :1;	//(9,RW,0x00) //
	UINT32 sre_mcu_intr_mcu_en              :1;	//(10,RW,0x00) //
	UINT32 vsd_mcu_intr_mcu_en              :1;	//(11,RW,0x00) //
	UINT32 cco_mcu_intr_mcu_en              :1;	//(12,RW,0x00) //
	UINT32 led_mcu_intr_mcu_en              :1;	//(13,RW,0x00) //
	UINT32 ldm_mcu_intr_mcu_en              :1;	//(14,RW,0x00) //
	UINT32 vdec_mcu_intr_mcu_en             :1;	//(15,RW,0x00) //
	UINT32 dpe_mcu_intr_mcu_en              :1;	//(16,RW,0x00) //
	UINT32 sr_mcu_intr_mcu_en               :1;	//(17,RW,0x00) //
	UINT32 dne_mcu_intr_mcu_en              :1;	//(18,RW,0x00) //
	UINT32 gav_mcu_intr_mcu_en              :1;	//(19,RW,0x00) //
	UINT32 lne0_mcu_intr_mcu_en             :1;	//(20,RW,0x00) //
	UINT32 lne1_mcu_intr_mcu_en             :1;	//(21,RO,0x00) //
	UINT32 vdo_mcu_intr_mcu_en              :1;	//(22,RO,0x00) //
	UINT32 i2c_mcu_intr_mcu_en              :1;	//(23,RW,0x00) //
	UINT32 mcu0_mcu_intr_mcu_en             :1;	//(24,RW,0x00) //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 mcu1_mcu_intr_mcu_en             :1;	//(25,RW,0x00) //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 reserved                         :6;	//(31:26,Rsvd,0x0) //
	};
}REG_MCU_INTR_MCU_FLAG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080068 RO 0x0000_0000
	UINT32 cvi_mcu_intr_cpu                 :1;	//(0,RO,0x00) //
	UINT32 imx_mcu_intr_cpu                 :1;	//(1,RO,0x00) //
	UINT32 hdr_mcu_intr_cpu                 :1;	//(2,RO,0x00) //
	UINT32 nd0_mcu_intr_cpu                 :1;	//(3,RO,0x00) //
	UINT32 nd1_mcu_intr_cpu                 :1;	//(4,RO,0x00) //
	UINT32 me0_mcu_intr_cpu                 :1;	//(5,RO,0x00) //
	UINT32 me1_mcu_intr_cpu                 :1;	//(6,RO,0x00) //
	UINT32 fmc_mcu_intr_cpu                 :1;	//(7,RO,0x00) //
	UINT32 fms_mcu_intr_cpu                 :1;	//(8,RO,0x00) //
	UINT32 gsc_mcu_intr_cpu                 :1;	//(9,RO,0x00) //
	UINT32 sre_mcu_intr_cpu                 :1;	//(10,RO,0x00) //
	UINT32 vsd_mcu_intr_cpu                 :1;	//(11,RO,0x00) //
	UINT32 cco_mcu_intr_cpu                 :1;	//(12,RO,0x00) //
	UINT32 led_mcu_intr_cpu                 :1;	//(13,RO,0x00) //
	UINT32 vdec_mcu_intr_cpu                :1;	//(14,RO,0x00) //VDEC to MCU interrupt
	UINT32 mcu_vdec_intr_cpu                :1;	//(15,RO,0x00) //MCU to VDEC interrupt
	UINT32 dpe_mcu_intr_cpu                 :1;	//(16,RO,0x00) //
	UINT32 sr_mcu_intr_cpu                  :1;	//(17,RO,0x00) //
	UINT32 dne_mcu_intr_cpu                 :1;	//(18,RO,0x00) //
	UINT32 gav_mcu_intr_cpu                 :1;	//(19,RO,0x00) //
	UINT32 lne0_mcu_intr_cpu                :1;	//(20,RO,0x00) //
	UINT32 lne1_mcu_intr_cpu                :1;	//(21,RO,0x00) //
	UINT32 vdo_mcu_intr_cpu                 :1;	//(22,RO,0x00) //
	UINT32 i2c_mcu_intr_cpu                 :1;	//(23,RO,0x00) //
	UINT32 reserved                         :8;	//(31:24,Rsvd,0x0000_0000) //
	};
}REG_MCU_INTR_CPU_FLAG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08006C RW 0x0000_0000
	UINT32 cvi_mcu_intr_cpu_en              :1;	//(0,RW,0x00) //
	UINT32 imx_mcu_intr_cpu_en              :1;	//(1,RW,0x00) //
	UINT32 hdr_mcu_intr_cpu_en              :1;	//(2,RW,0x00) //
	UINT32 nd0_mcu_intr_cpu_en              :1;	//(3,RW,0x00) //
	UINT32 nd1_mcu_intr_cpu_en              :1;	//(4,RW,0x00) //
	UINT32 me0_mcu_intr_cpu_en              :1;	//(5,RW,0x00) //
	UINT32 me1_mcu_intr_cpu_en              :1;	//(6,RW,0x00) //
	UINT32 fmc_mcu_intr_cpu_en              :1;	//(7,RW,0x00) //
	UINT32 fms_mcu_intr_cpu_en              :1;	//(8,RW,0x00) //
	UINT32 gsc_mcu_intr_cpu_en              :1;	//(9,RW,0x00) //
	UINT32 sre_mcu_intr_cpu_en              :1;	//(10,RW,0x00) //
	UINT32 vsd_mcu_intr_cpu_en              :1;	//(11,RW,0x00) //
	UINT32 cco_mcu_intr_cpu_en              :1;	//(12,RW,0x00) //
	UINT32 led_mcu_intr_cpu_en              :1;	//(13,RW,0x00) //
	UINT32 vdec_mcu_intr_cpu_en             :1;	//(14,RW,0x00) //
	UINT32 mcu_vdec_intr_cpu_en             :1;	//(15,RW,0x00) //
	UINT32 dpe_mcu_intr_cpu_en              :1;	//(16,RW,0x00) //
	UINT32 sr_mcu_intr_cpu_en               :1;	//(17,RW,0x00) //
	UINT32 dne_mcu_intr_cpu_en              :1;	//(18,RW,0x00) //
	UINT32 gav_mcu_intr_cpu_en              :1;	//(19,RW,0x00) //
	UINT32 lne0_mcu_intr_cpu_en             :1;	//(20,RW,0x00) //
	UINT32 lne1_mcu_intr_cpu_en             :1;	//(21,RW,0x00) //
	UINT32 vdo_mcu_intr_cpu_en              :1;	//(22,RO,0x00) //
	UINT32 i2c_mcu_intr_cpu_en              :1;	//(23,RO,0x00) //
	UINT32 reserved                         :8;	//(31:24,Rsvd,0x0) //
	};
}REG_MCU_INTR_CPU_FLAG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080070 RO 0x0000_0000
	UINT32 global_stcco0                    :32;	//(31:0,RO,0x0) //
	};
}REG_MCU_GLOBAL_STCC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080074 RO 0x0000_0000
	UINT32 global_stcco1                    :32;	//(31:0,RO,0x0) //
	};
}REG_MCU_GLOBAL_STCC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080078 RO 0x0000_0000
	UINT32 global_stcco2                    :32;	//(31:0,RO,0x0) //
	};
}REG_MCU_GLOBAL_STCC2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08007C RO 0x0000_0000
	UINT32 global_stcco3                    :32;	//(31:0,RO,0x0) //
	};
}REG_MCU_GLOBAL_STCC3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080080 RO 0x0000_0000
	UINT32 live_stcco0                      :32;	//(31:0,RO,0x0) //
	};
}REG_MCU_LIVE_STCC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080084 RO 0x0000_0000
	UINT32 live_stcco0                      :32;	//(31:0,RO,0x0) //
	};
}REG_MCU_LIVE_STCC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080088 RW 0x0000_0000
	UINT32 apb_tout_intr_clr                :4;	//(3:0,RW,0x0) //apb timeout intrrupt clear
	UINT32 apb_tout_intr_ris                :4;	//(7:4,RO,0x0) //apb timeout read interrupt ris
	UINT32 apb_tout_intr_mis                :4;	//(11:8,RO,0x0) //apb timeout read interrupt mis
	UINT32 apb_tout_intr_en                 :4;	//(15:12,RW,0x0) //apb timeout intrrupt en
	UINT32 apb_tout_pslverr                 :4;	//(19:16,RW,0x0) //apb timeout pslverr
	UINT32 apb_tout_en                      :4;	//(23:20,RW,0x0) //apb timeout countrol enable
	UINT32 reserved                         :8;	//(31:24,Rsvd,0x0) //
	};
}REG_MCU_AD_APB_TOUT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08008C RW 0x0000_0000
	UINT32 apb_tout_ctrl_counter            :32;	//(31:0,RW,VNA) //apb timeout countrol counter
	};
}REG_MCU_AD_APB_TOUT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080090 RW 0x0000_0000
	UINT32 apb_tout_ch0_address             :32;	//(31:0,RO,VNA) //read ma paddr
	};
}REG_MCU_APB_TOUT_CTRL_CH0_ADR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080094 RW 0x0000_0000
	UINT32 apb_tout_ch0_pwrite              :32;	//(31:0,RO,VNA) //read ma pwrite
	};
}REG_MCU_APB_TOUT_CTRL_CH0_PW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC080098 RW 0x0000_0000
	UINT32 apb_tout_ch0_pwdata              :32;	//(31:0,RO,VNA) //read ma pwdata
	};
}REG_MCU_APB_TOUT_CTRL_CH0_PWDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC08009C RW 0x0000_0000
	UINT32 apb_tout_ch1_address             :32;	//(31:0,RO,VNA) //read mb paddr
	};
}REG_MCU_APB_TOUT_CTRL_CH1_ADR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800A0 RW 0x0000_0000
	UINT32 apb_tout_ch1_pwrite              :32;	//(31:0,RO,VNA) //read mb pwrite
	};
}REG_MCU_APB_TOUT_CTRL_CH1_PW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800A4 RW 0x0000_0000
	UINT32 apb_tout_ch1_pwdata              :32;	//(31:0,RO,VNA) //read mb pwdata
	};
}REG_MCU_APB_TOUT_CTRL_CH1_PWDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800A8 RW 0x0000_0000
	UINT32 apb_tout_ch2_address             :32;	//(31:0,RO,VNA) //read mc paddr
	};
}REG_MCU_APB_TOUT_CTRL_CH2_ADR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800AC RW 0x0000_0000
	UINT32 apb_tout_ch2_pwrite              :32;	//(31:0,RO,VNA) //read mc pwrite
	};
}REG_MCU_APB_TOUT_CTRL_CH2_PW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800B0 RW 0x0000_0000
	UINT32 apb_tout_ch2_pwdata              :32;	//(31:0,RO,VNA) //read mc pwdata
	};
}REG_MCU_APB_TOUT_CTRL_CH2_PWDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800B4 RW 0x0000_0000
	UINT32 apb_tout_ch3_address             :32;	//(31:0,RO,VNA) //read md paddr
	};
}REG_MCU_APB_TOUT_CTRL_CH3_ADR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800B8 RW 0x0000_0000
	UINT32 apb_tout_ch3_pwrite              :32;	//(31:0,RO,VNA) //read md pwrite
	};
}REG_MCU_APB_TOUT_CTRL_CH3_PW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800BC RW 0x0000_0000
	UINT32 apb_tout_ch3_pwdata              :32;	//(31:0,RO,VNA) //read md pwdata
	};
}REG_MCU_APB_TOUT_CTRL_CH3_PWDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800C0 RW 0x0000_0000
	UINT32 mask_start_addr                  :23;	//(22:0,RW,0x0) //
	UINT32 resvd                            :9;
	};
}REG_MCU_AD_MASK_START_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800C4 RW 0x0000_0000
	UINT32 mask_end_addr                    :23;	//(22:0,NA,0x0) //
	UINT32 resvd                            :8;
	UINT32 mask_addr_mode_en                :1;	//(31,RW,0x0) //
	};
}REG_MCU_AD_MASK_END_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800C8 RO 0x0000_0000
	UINT32 mask_read_addr                   :23;	//(22:0,RO,0x0) //
	UINT32 resvd                            :9;
	};
}REG_MCU_AD_MASK_READ_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800CC RW 0x0000_0021
	UINT32 interuppt_2                      :4;	//(3:0,NA,0x1) //priority 1 level
	UINT32 interuppt_3                      :4;	//(7:4,NA,0x2) //priority 1 level
	UINT32 interuppt_4                      :4;	//(11:8,NA,0x0) //priority 1 level
	UINT32 interuppt_5                      :4;	//(15:12,NA,0x0) //priority 1 level
	UINT32 interuppt_6                      :4;	//(19:16,NA,0x0) //priority 2 level
	UINT32 interuppt_7                      :4;	//(23:20,NA,0x0) //priority 3 level
	UINT32 interuppt_8                      :4;	//(27:24,NA,0x0) //priority 4 level	"0000" : not connected	"0001" : CPU IPC interrupt	"0010" : Local Top interrupt
	UINT32 reserved                         :4;	//(31:28,RW,0x0) //for debug : interrupt_9 (edge)
	};
}REG_MCU_AD_INTR_PRIORITY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800D0 RW/RO 0x0000_0000
	UINT32 up_count                         :31;	//(30:0,RO,0x0) //up counter with 198Mhz clock
	UINT32 up_count_en                      :1;	//(31,RW,0x0) //reset and enable
	};
}REG_MCU_AD_UP_COUNTER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800D4 RW 0x0000_0000
	UINT32 rst_async_bridge                 :32;	//(31:0,RW,0x0) //
	};
}REG_MCU_RST_ASYNC_BRIDGE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800D8 RO 0x0000_0000
	UINT32 pfault_info                      :32;	//(31:0,RO,0x0) //MCU0's PFaultInfo
	};
}REG_MCU_PFAULT_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800DC RO 0x0000_0000
	UINT32 pfault_info1                     :32;	//(31:0,RO,0x0) //MCU1's PFaultInfo
	};
}REG_MCU_PFAULT_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800E0 RO 0x0000_0000
	UINT32 pfault_info_valid                :1;	//(0,RO,0x0) //MCU0's PFaultInfoValid
	UINT32 pfatal_error                     :1;	//(1,RO,0x0) //MCU0's PFatalError
	UINT32 double_exception_error           :1;	//(2,RO,0x0) //MCU0's DoubleExceptionError
	UINT32 resvd0                           :1;
	UINT32 pfault_info_valid1               :1;	//(4,RO,0x0) //MCU1's PFaultInfoValid
	UINT32 pfatal_error1                    :1;	//(5,RO,0x0) //MCU1's PFatalError
	UINT32 double_exception_error1          :1;	//(6,RO,0x0) //MCU1's DoubleExceptionError
	UINT32 resvd1                           :25;
	};
}REG_MCU_PFAULT_STATUS2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800E4 RW 0x0000_0000
	UINT32 sram4_offset                     :32;	//(31:0,RW,0x0000_0000) //when AXI address of PL301 output is 0x6000_0000 ~ 0x6FFF_FFFF	{sram4_port_sel[3:0],AXI_ADDR[27:0] + sram4_offset}
	};
}REG_MCU_SRAM4_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800E8 RW 0x0000_0000
	UINT32 sram5_offset                     :32;	//(31:0,RW,0x0000_0000) //when AXI address of PL301 output is 0x7000_0000 ~ 0x7FFF_FFFF	{sram5_port_sel[3:0],AXI_ADDR[27:0] + sram5_offset}
	};
}REG_MCU_SRAM5_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800EC RO 0x0000_0000
	UINT32 cvi_mcu_intr_mcu                 :1;	//(0,RO,0x00) //
	UINT32 imx_mcu_intr_mcu                 :1;	//(1,RO,0x00) //
	UINT32 hdr_mcu_intr_mcu                 :1;	//(2,RO,0x00) //
	UINT32 nd0_mcu_intr_mcu                 :1;	//(3,RO,0x00) //
	UINT32 nd1_mcu_intr_mcu                 :1;	//(4,RO,0x00) //
	UINT32 me0_mcu_intr_mcu                 :1;	//(5,RO,0x00) //
	UINT32 me1_mcu_intr_mcu                 :1;	//(6,RO,0x00) //
	UINT32 fmc_mcu_intr_mcu                 :1;	//(7,RO,0x00) //
	UINT32 fms_mcu_intr_mcu                 :1;	//(8,RO,0x00) //
	UINT32 gsc_mcu_intr_mcu                 :1;	//(9,RO,0x00) //
	UINT32 sre_mcu_intr_mcu                 :1;	//(10,RO,0x00) //
	UINT32 vsd_mcu_intr_mcu                 :1;	//(11,RO,0x00) //
	UINT32 cco_mcu_intr_mcu                 :1;	//(12,RO,0x00) //
	UINT32 led_mcu_intr_mcu                 :1;	//(13,RO,0x00) //
	UINT32 ldm_mcu_intr_mcu                 :1;	//(14,RO,0x00) //
	UINT32 vdec_mcu_intr_mcu                :1;	//(15,RO,0x00) //
	UINT32 dpe_mcu_intr_mcu                 :1;	//(16,RO,0x00) //
	UINT32 sr_mcu_intr_mcu                  :1;	//(17,RO,0x00) //
	UINT32 dne_mcu_intr_mcu                 :1;	//(18,RO,0x00) //
	UINT32 gav_mcu_intr_mcu                 :1;	//(19,RO,0x00) //
	UINT32 lne0_mcu_intr_mcu                :1;	//(20,RO,0x00) //
	UINT32 lne1_mcu_intr_mcu                :1;	//(21,RO,0x00) //
	UINT32 vdo_mcu_intr_mcu                 :1;	//(22,RO,0x00) //
	UINT32 i2c_mcu_intr_mcu                 :1;	//(23,RO,0x00) //
	UINT32 mcu0_mcu_intr_mcu                :1;	//(24,RO,0x00) //
	UINT32 mcu1_mcu_intr_mcu                :1;	//(25,RO,0x00) //
	UINT32 reserved                         :6;	//(31:26,Rsvd,0x0) //
	};
}REG_MCU_INTR_MCU1_FLAG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800F0 RW 0x0000_0000
	UINT32 cvi_mcu_intr_mcu_en              :1;	//(0,RW,0x00) //
	UINT32 imx_mcu_intr_mcu_en              :1;	//(1,RW,0x00) //
	UINT32 hdr_mcu_intr_mcu_en              :1;	//(2,RW,0x00) //
	UINT32 nd0_mcu_intr_mcu_en              :1;	//(3,RW,0x00) //
	UINT32 nd1_mcu_intr_mcu_en              :1;	//(4,RW,0x00) //
	UINT32 me0_mcu_intr_mcu_en              :1;	//(5,RW,0x00) //
	UINT32 me1_mcu_intr_mcu_en              :1;	//(6,RW,0x00) //
	UINT32 fmc_mcu_intr_mcu_en              :1;	//(7,RW,0x00) //
	UINT32 fms_mcu_intr_mcu_en              :1;	//(8,RW,0x00) //
	UINT32 gsc_mcu_intr_mcu_en              :1;	//(9,RW,0x00) //
	UINT32 sre_mcu_intr_mcu_en              :1;	//(10,RW,0x00) //
	UINT32 vsd_mcu_intr_mcu_en              :1;	//(11,RW,0x00) //
	UINT32 cco_mcu_intr_mcu_en              :1;	//(12,RW,0x00) //
	UINT32 led_mcu_intr_mcu_en              :1;	//(13,RW,0x00) //
	UINT32 ldm_mcu_intr_mcu_en              :1;	//(14,RW,0x00) //
	UINT32 vdec_mcu_intr_mcu_en             :1;	//(15,RW,0x00) //
	UINT32 dpe_mcu_intr_mcu_en              :1;	//(16,RW,0x00) //
	UINT32 sr_mcu_intr_mcu_en               :1;	//(17,RW,0x00) //
	UINT32 dne_mcu_intr_mcu_en              :1;	//(18,RW,0x00) //
	UINT32 gav_mcu_intr_mcu_en              :1;	//(19,RW,0x00) //
	UINT32 lne0_mcu_intr_mcu_en             :1;	//(20,RW,0x00) //
	UINT32 lne1_mcu_intr_mcu_en             :1;	//(21,RW,0x00) //
	UINT32 vdo_mcu_intr_mcu_en              :1;	//(22,RW,0x00) //
	UINT32 i2c_mcu_intr_mcu_en              :1;	//(23,RW,0x00) //
	UINT32 mcu0_mcu_intr_mcu_en             :1;	//(24,RW,0x00) //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 mcu1_mcu_intr_mcu_en             :1;	//(25,RW,0x00) //write 1하면 직접 interrupt 발생, clear 하기 위해 write 0
	UINT32 reserved                         :6;	//(31:26,Rsvd,0x0) //
	};
}REG_MCU_INTR_MCU1_FLAG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800F4 RW 0x5000_0000
	UINT32 boot_img_map3                    :32;	//(31:0,RW,0x5000_0000) //when AXI address of PL301 output is 0x5040_0000 ~ 0x505F_FFFF	physical image address in DDR region is 0x0040_0000 + boot_img_map3	Default : 0x5040_0000 ~ 0x505F_FFFF	(real write region : 0x5040_0000 ~ 0x505F_FFFF => 0x5040_0000 ~ 0x505F_FFFF
	};
}REG_MCU_SROM_BOOT_MAP3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0800F8 RW 0x5000_0000
	UINT32 boot_img_map4                    :32;	//(31:0,RW,0x5000_0000) //when AXI address of PL301 output is 0x5060_0000 ~ 0x507F_FFFF	physical image address in DDR region is 0x0060_0000 + boot_img_map4	Default : 0x5060_0000 ~ 0x507F_FFFF	(real write region : 0x5060_0000 ~ 0x507F_FFFF => 0x5060_0000 ~ 0x507F_FFFF
	};
}REG_MCU_SROM_BOOT_MAP4_T;

typedef struct {
	REG_MCU_SET_REG_CTRL0_T                               set_reg_ctrl0;	//0xCC080000
	REG_MCU_SET_REG_CTRL1_T                               set_reg_ctrl1;	//0xCC080004
	REG_MCU_EXT_INTR_EVENT_T                             ext_intr_event;	//0xCC080008
	REG_MCU_EXT_INTR_ENABLE_T                           ext_intr_enable;	//0xCC08000C
	REG_MCU_EXT_INTR_STATUS_T                           ext_intr_status;	//0xCC080010
	REG_MCU_EXT_INTR_CLEAR_T                             ext_intr_clear;	//0xCC080014
	REG_MCU_INT_INTR_EVENT_T                             int_intr_event;	//0xCC080018
	REG_MCU_INT_INTR_ENABLE_T                           int_intr_enable;	//0xCC08001C
	REG_MCU_INT_INTR_STATUS_T                           int_intr_status;	//0xCC080020
	REG_MCU_INT_INTR_CLEAR_T                             int_intr_clear;	//0xCC080024
	REG_MCU_SROM_BOOT_MAP1_T                             srom_boot_map1;	//0xCC080028
	REG_MCU_SROM_BOOT_MAP2_T                             srom_boot_map2;	//0xCC08002C
	REG_MCU_SRAM_PORT_SEL_T                               sram_port_sel;	//0xCC080030
	REG_MCU_PDEBUG_STATUS_T                               pdebug_status;	//0xCC080034
	REG_MCU_PDEBUG_DATA_T                                   pdebug_data;	//0xCC080038
	REG_MCU_PDEBUG_PC_T                                       pdebug_pc;	//0xCC08003C
	REG_MCU_AXI_USER_ID_T                                   axi_user_id;	//0xCC080040
	REG_MCU_SRAM0_OFFSET_T                                 sram0_offset;	//0xCC080044
	REG_MCU_SRAM1_OFFSET_T                                 sram1_offset;	//0xCC080048
	REG_MCU_SRAM2_OFFSET_T                                 sram2_offset;	//0xCC08004C
	REG_MCU_SRAM3_OFFSET_T                                 sram3_offset;	//0xCC080050
	REG_MCU_PDEBUG_DATA1_T                                 pdebug_data1;	//0xCC080054
	REG_MCU_PDEBUG_PC1_T                                     pdebug_pc1;	//0xCC080058
	REG_MCU_SPP_MCU_VERSION_T                           spp_mcu_version;	//0xCC08005C
	REG_MCU_INTR_MCU_FLAG_T                               intr_mcu_flag;	//0xCC080060
	REG_MCU_INTR_MCU_FLAG_EN_T                         intr_mcu_flag_en;	//0xCC080064
	REG_MCU_INTR_CPU_FLAG_T                               intr_cpu_flag;	//0xCC080068
	REG_MCU_INTR_CPU_FLAG_EN_T                         intr_cpu_flag_en;	//0xCC08006C
	REG_MCU_GLOBAL_STCC0_T                                 global_stcc0;	//0xCC080070
	REG_MCU_GLOBAL_STCC1_T                                 global_stcc1;	//0xCC080074
	REG_MCU_GLOBAL_STCC2_T                                 global_stcc2;	//0xCC080078
	REG_MCU_GLOBAL_STCC3_T                                 global_stcc3;	//0xCC08007C
	REG_MCU_LIVE_STCC0_T                                     live_stcc0;	//0xCC080080
	REG_MCU_LIVE_STCC1_T                                     live_stcc1;	//0xCC080084
	REG_MCU_AD_APB_TOUT_CTRL_T                         ad_apb_tout_ctrl;	//0xCC080088
	REG_MCU_AD_APB_TOUT_CNT_T                           ad_apb_tout_cnt;	//0xCC08008C
	REG_MCU_APB_TOUT_CTRL_CH0_ADR_T               apb_tout_ctrl_ch0_adr;	//0xCC080090
	REG_MCU_APB_TOUT_CTRL_CH0_PW_T                 apb_tout_ctrl_ch0_pw;	//0xCC080094
	REG_MCU_APB_TOUT_CTRL_CH0_PWDATA_T         apb_tout_ctrl_ch0_pwdata;	//0xCC080098
	REG_MCU_APB_TOUT_CTRL_CH1_ADR_T               apb_tout_ctrl_ch1_adr;	//0xCC08009C
	REG_MCU_APB_TOUT_CTRL_CH1_PW_T                 apb_tout_ctrl_ch1_pw;	//0xCC0800A0
	REG_MCU_APB_TOUT_CTRL_CH1_PWDATA_T         apb_tout_ctrl_ch1_pwdata;	//0xCC0800A4
	REG_MCU_APB_TOUT_CTRL_CH2_ADR_T               apb_tout_ctrl_ch2_adr;	//0xCC0800A8
	REG_MCU_APB_TOUT_CTRL_CH2_PW_T                 apb_tout_ctrl_ch2_pw;	//0xCC0800AC
	REG_MCU_APB_TOUT_CTRL_CH2_PWDATA_T         apb_tout_ctrl_ch2_pwdata;	//0xCC0800B0
	REG_MCU_APB_TOUT_CTRL_CH3_ADR_T               apb_tout_ctrl_ch3_adr;	//0xCC0800B4
	REG_MCU_APB_TOUT_CTRL_CH3_PW_T                 apb_tout_ctrl_ch3_pw;	//0xCC0800B8
	REG_MCU_APB_TOUT_CTRL_CH3_PWDATA_T         apb_tout_ctrl_ch3_pwdata;	//0xCC0800BC
	REG_MCU_AD_MASK_START_ADDR_T                     ad_mask_start_addr;	//0xCC0800C0
	REG_MCU_AD_MASK_END_ADDR_T                         ad_mask_end_addr;	//0xCC0800C4
	REG_MCU_AD_MASK_READ_ADDR_T                       ad_mask_read_addr;	//0xCC0800C8
	REG_MCU_AD_INTR_PRIORITY_T                         ad_intr_priority;	//0xCC0800CC
	REG_MCU_AD_UP_COUNTER_T                               ad_up_counter;	//0xCC0800D0
	REG_MCU_RST_ASYNC_BRIDGE_T                         rst_async_bridge;	//0xCC0800D4
	REG_MCU_PFAULT_STATUS0_T                             pfault_status0;	//0xCC0800D8
	REG_MCU_PFAULT_STATUS1_T                             pfault_status1;	//0xCC0800DC
	REG_MCU_PFAULT_STATUS2_T                             pfault_status2;	//0xCC0800E0
	REG_MCU_SRAM4_OFFSET_T                                 sram4_offset;	//0xCC0800E4
	REG_MCU_SRAM5_OFFSET_T                                 sram5_offset;	//0xCC0800E8
	REG_MCU_INTR_MCU1_FLAG_T                             intr_mcu1_flag;	//0xCC0800EC
	REG_MCU_INTR_MCU1_FLAG_EN_T                       intr_mcu1_flag_en;	//0xCC0800F0
	REG_MCU_SROM_BOOT_MAP3_T                             srom_boot_map3;	//0xCC0800F4
	REG_MCU_SROM_BOOT_MAP4_T                             srom_boot_map4;	//0xCC0800F8
}REG_MCU_T;

extern volatile REG_MCU_T*                         gpREG_MCU;

#endif
