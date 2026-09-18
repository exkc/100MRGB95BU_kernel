#ifndef _REG_DPG0_M0_h
#define _REG_DPG0_M0_h
//Header File for DPG0_M0 in \O24\O24_DRAM_M0_Register_Manual.xls

#define REG_DPG0_M0_DPG_ENABLE                                              (APB_DPG0_M0_BASE+0x0100)
#define REG_DPG0_M0_DPG_INF_CTRL                                            (APB_DPG0_M0_BASE+0x0104)
#define REG_DPG0_M0_DPG_ID_INC                                              (APB_DPG0_M0_BASE+0x0108)
#define REG_DPG0_M0_DPG_SW_RESET                                            (APB_DPG0_M0_BASE+0x010C)
#define REG_DPG0_M0_DPG_WR_PATTERN                                          (APB_DPG0_M0_BASE+0x0110)
#define REG_DPG0_M0_CMD_DLY_CTRL                                            (APB_DPG0_M0_BASE+0x0114)
#define REG_DPG0_M0_RND_AXI_LENGTH                                          (APB_DPG0_M0_BASE+0x0118)
#define REG_DPG0_M0_AXI_TR_STATUS                                           (APB_DPG0_M0_BASE+0x011C)
#define REG_DPG0_M0_DPG_MO_STATUS                                           (APB_DPG0_M0_BASE+0x0120)
#define REG_DPG0_M0_DPG_BCH_ERR_STATUS                                      (APB_DPG0_M0_BASE+0x0124)
#define REG_DPG0_M0_DPG_RDATA_ERR_STATUS                                    (APB_DPG0_M0_BASE+0x0128)
#define REG_DPG0_M0_DPG_RCH_ERR_STATUS                                      (APB_DPG0_M0_BASE+0x012C)
#define REG_DPG0_M0_IP_GATING                                               (APB_DPG0_M0_BASE+0x0130)
#define REG_DPG0_M0_DPG_GATING                                              (APB_DPG0_M0_BASE+0x0134)
#define REG_DPG0_M0_FLUSH_EN                                                (APB_DPG0_M0_BASE+0x0138)
#define REG_DPG0_M0_FLUSH_DONE                                              (APB_DPG0_M0_BASE+0x013C)
#define REG_DPG0_M0_GRP0_START_ADDR                                         (APB_DPG0_M0_BASE+0x0140)
#define REG_DPG0_M0_GPR0_ADDR_INC_BND                                       (APB_DPG0_M0_BASE+0x0144)
#define REG_DPG0_M0_GRP1_START_ADDR                                         (APB_DPG0_M0_BASE+0x0148)
#define REG_DPG0_M0_GPR1_ADDR_INC_BND                                       (APB_DPG0_M0_BASE+0x014C)
#define REG_DPG0_M0_ADDR_INC_VAL                                            (APB_DPG0_M0_BASE+0x0150)
#define REG_DPG0_M0_ROW_BANK_ADDR_MODE                                      (APB_DPG0_M0_BASE+0x0154)
#define REG_DPG0_M0_RDATA_ERR_ADDR                                          (APB_DPG0_M0_BASE+0x015C)
#define REG_DPG0_M0_RDATA_EXP_DATA_127_96                                   (APB_DPG0_M0_BASE+0x0160)
#define REG_DPG0_M0_RDATA_EXP_DATA_95_64                                    (APB_DPG0_M0_BASE+0x0164)
#define REG_DPG0_M0_RDATA_EXP_DATA_63_32                                    (APB_DPG0_M0_BASE+0x0168)
#define REG_DPG0_M0_RDATA_EXP_DATA_31_0                                     (APB_DPG0_M0_BASE+0x016C)
#define REG_DPG0_M0_RDATA_IN_DATA_127_96                                    (APB_DPG0_M0_BASE+0x0170)
#define REG_DPG0_M0_RDATA_IN_DATA_95_64                                     (APB_DPG0_M0_BASE+0x0174)
#define REG_DPG0_M0_RDATA_IN_DATA_63_32                                     (APB_DPG0_M0_BASE+0x0178)
#define REG_DPG0_M0_RDATA_IN_DATA_31_0                                      (APB_DPG0_M0_BASE+0x017C)
#define REG_DPG0_M0_USER_CMD_REG0                                           (APB_DPG0_M0_BASE+0x0180)
#define REG_DPG0_M0_USER_CMD_REG1                                           (APB_DPG0_M0_BASE+0x0184)
#define REG_DPG0_M0_START_MODE                                              (APB_DPG0_M0_BASE+0x0190)
#define REG_DPG0_M0_LP_CTRL                                                 (APB_DPG0_M0_BASE+0x0198)
#define REG_DPG0_M0_DIRECT_MODE                                             (APB_DPG0_M0_BASE+0x01A0)
#define REG_DPG0_M0_FIXED_MODE0                                             (APB_DPG0_M0_BASE+0x01A4)
#define REG_DPG0_M0_FIXED_MODE1                                             (APB_DPG0_M0_BASE+0x01A8)

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04100 RW
	UINT32 rf_DPG_en                        :1;	//0 //External AXI source selection MUX. selection singal.
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_DPG_ENABLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04104 RW
	UINT32 rf_inf_sw                        :1;	//0 //infinite axi traffic generation mode on/off swtich
	UINT32 resvd0                           :3;  
	UINT32 rf_inf_mode                      :1;	//4 //infinite axi traffic generation mode option(0: axi_cmd0, 1: axi_cmd1)
	UINT32 resvd1                           :11; 
	UINT32 rf_iter_mo_tr_cnt                :10;	//25:16	//no. of axi traffic.(in this counter base axi traffic generation mode)
	UINT32 resvd2                           :6;  
	};
}REG_DPG0_M0_DPG_INF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04108 RW
	UINT32 rf_id_inc_en                     :1;	//0 //ID linear increasing on/off switch
	UINT32 resvd0                           :15; 
	UINT32 rf_id_inc_step                   :4;	//19:16	//ID linear increasing step
	UINT32 resvd1                           :12; 
	};
}REG_DPG0_M0_DPG_ID_INC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0410C RW
	UINT32 rf_sw_reset                      :1;	//0 //positive s/w reset signal
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_DPG_SW_RESET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04110 RW
	UINT32 rf_wdata_pt_mode0                :2;	//1:0	//AXI WDATA Pattern	0: 0x5A5A5A5A / 0xA5A5A5A5	1: 0xA5A5A5A5 / 0x5A5A5A5A	2: WDATA --> ADDRESS Pattern	3: AxADDR --> PWDATA / WDATA --> PWDATA+BURST
	UINT32 resvd0                           :6;  
	UINT32 rf_wdata_pt_mode1                :2;	//9:8	//AXI WDATA Pattern	0: 0x5A5A5A5A / 0xA5A5A5A5	1: 0xA5A5A5A5 / 0x5A5A5A5A	2: WDATA --> ADDRESS Pattern	3: AxADDR --> PWDATA / WDATA --> PWDATA+BURST
	UINT32 resvd1                           :22; 
	};
}REG_DPG0_M0_DPG_WR_PATTERN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04114 RW
	UINT32 rf_dly_step_mode0                :4;	//3:0	//delay step	0: 0 cycle	1: 64 cycle	2: 128 cycle	3: 256 cycle	4: 384 cycle	5: 512 cycle	6: 768 cycle	7: 1024 cycle	8: 1536 cycle	9: 2048 cycle	10: 3072 cycle	11: 4096 cycle	12: 8192 cycle	13: 16384 cycle	14: 32768 cycle	15: 49152 cycle
	UINT32 resvd0                           :4;  
	UINT32 rf_dly_zero0                     :1;	//8 //zero command generation delay in infinite axi traffic generation mode
	UINT32 resvd1                           :7;  
	UINT32 rf_dly_step_mode1                :4;	//19:16	//delay step	0: 0 cycle	1: 64 cycle	2: 128 cycle	3: 256 cycle	4: 384 cycle	5: 512 cycle	6: 768 cycle	7: 1024 cycle	8: 1536 cycle	9: 2048 cycle	10: 3072 cycle	11: 4096 cycle	12: 8192 cycle	13: 16384 cycle	14: 32768 cycle	15: 49152 cycle
	UINT32 resvd2                           :8;  
	UINT32 rf_dly_zero1                     :1;	//28 //zero command generation delay in infinite axi traffic generation mode
	UINT32 resvd3                           :3;  
	};
}REG_DPG0_M0_CMD_DLY_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04118 RW
	UINT32 rf_rnd_alen_en                   :1;	//0 //AXI Random Burst Length Enable
	UINT32 resvd0                           :3;  
	UINT32 rf_lfsr_seed                     :8;	//11:4	//LFSR SEED for Psuedo Random AXI Burst length,
	UINT32 resvd1                           :4;  
	UINT32 rf_auto_step_addr_en             :1;	//16 //In AXI Burst Transaction, Step Address auto calculation
	UINT32 resvd2                           :15; 
	};
}REG_DPG0_M0_RND_AXI_LENGTH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0411C RO
	UINT32 BREADY                           :1;	//0 //
	UINT32 BVALID                           :1;	//1 //
	UINT32 resvd0                           :2;  
	UINT32 WLAST                            :1;	//4 //
	UINT32 WREADY                           :1;	//5 //
	UINT32 WVALID                           :1;	//6 //
	UINT32 resvd1                           :1;  
	UINT32 AWREADY                          :1;	//8 //
	UINT32 AWVALID                          :1;	//9 //
	UINT32 resvd2                           :2;  
	UINT32 RREADY                           :1;	//12 //
	UINT32 RVALID                           :1;	//13 //
	UINT32 resvd3                           :2;  
	UINT32 ARREADY                          :1;	//16 //
	UINT32 ARVALID                          :1;	//17 //
	UINT32 resvd4                           :14; 
	};
}REG_DPG0_M0_AXI_TR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04120 RW/RO
	UINT32 resvd0                           :8;  
	UINT32 rf_emptied_multi_out             :1;	//8 //current multiple outstanding is smaller than setting value
	UINT32 resvd1                           :7;  
	UINT32 acmd_under_operating0            :1;	//16 //DPG FSM is under operating ( No response )
	UINT32 resvd2                           :3;  
	UINT32 acmd_under_operating1            :1;	//20 //DPG FSM is under operating ( No response )
	UINT32 resvd3                           :3;  
	UINT32 adata_under_operating            :1;	//24 //DPG FSM is under operating ( No response )
	UINT32 resvd4                           :7;  
	};
}REG_DPG0_M0_DPG_MO_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04124 RO
	UINT32 rf_bid_err_flag                  :10;	//9:0	//BID isn't same AWID
	UINT32 resvd0                           :2;  
	UINT32 rf_bid_err_flag_clr              :1;	//12 //bid_err_flag clear
	UINT32 resvd1                           :3;  
	UINT32 rf_bresp_err_flag                :1;	//16 //BRESP is 2'b00
	UINT32 resvd2                           :11; 
	UINT32 rf_bresp_err_flag_clr            :1;	//28 //bresp_err_flag clear
	UINT32 resvd3                           :3;  
	};
}REG_DPG0_M0_DPG_BCH_ERR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04128 RW
	UINT32 rf_rdata_err_flag                :1;	//0 //rdata isn't same wdata
	UINT32 resvd0                           :27; 
	UINT32 rf_rdata_err_flag_clr            :1;	//28 //rdata_err_flag clear
	UINT32 resvd1                           :3;  
	};
}REG_DPG0_M0_DPG_RDATA_ERR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0412C RO
	UINT32 rf_rid_err_flag                  :10;	//9:0	//RID isn't same AWID
	UINT32 resvd0                           :2;  
	UINT32 rf_rid_err_flag_clr              :1;	//12 //rid_err_flag clear
	UINT32 resvd1                           :3;  
	UINT32 rf_rresp_err_flag                :1;	//16 //RRESP is 2'b00
	UINT32 resvd2                           :11; 
	UINT32 rf_rresp_err_flag_clr            :1;	//28 //rresp_err_flag clear
	UINT32 resvd3                           :3;  
	};
}REG_DPG0_M0_DPG_RCH_ERR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04130 RO/RW
	UINT32 rf_bus_gating_en_r               :1;	//0 //
	UINT32 resvd0                           :3;  
	UINT32 rf_bus_gating_en_w               :1;	//4 //
	UINT32 resvd1                           :3;  
	UINT32 rf_bus_cmd_vio_r                 :1;	//8 //
	UINT32 resvd2                           :3;  
	UINT32 rf_bus_cmd_vio_w                 :1;	//12 //
	UINT32 resvd3                           :3;  
	UINT32 rf_bus_data_vio_r                :1;	//16 //
	UINT32 resvd4                           :3;  
	UINT32 rf_bus_data_vio_w                :1;	//20 //
	UINT32 resvd5                           :11; 
	};
}REG_DPG0_M0_IP_GATING_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04134 RO/RW
	UINT32 rf_DPG_gating_en_r               :1;	//0 //
	UINT32 resvd0                           :3;  
	UINT32 rf_DPG_gating_en_w               :1;	//4 //
	UINT32 resvd1                           :3;  
	UINT32 rf_DPG_cmd_vio_r                 :1;	//8 //
	UINT32 resvd2                           :3;  
	UINT32 rf_DPG_cmd_vio_w                 :1;	//12 //
	UINT32 resvd3                           :3;  
	UINT32 rf_DPG_data_vio_r                :1;	//16 //
	UINT32 resvd4                           :3;  
	UINT32 rf_DPG_data_vio_w                :1;	//20 //
	UINT32 resvd5                           :11; 
	};
}REG_DPG0_M0_DPG_GATING_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04138 RW
	UINT32 rf_flush_en                      :1;	//0:0	//
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_FLUSH_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0413C RO
	UINT32 rf_flush_done                    :1;	//0:0	//
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_FLUSH_DONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04140 RW
	UINT32 rf_start_addr0                   :12;	//11:0	//START ADDRESS for ACMD0
	UINT32 resvd                            :20; 
	};
}REG_DPG0_M0_GRP0_START_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04144 RW
	UINT32 rf_end_addr0                     :12;	//11:0	//END ADDRESS for ACMD0
	UINT32 resvd                            :20; 
	};
}REG_DPG0_M0_GPR0_ADDR_INC_BND_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04148 RW
	UINT32 rf_start_addr1                   :12;	//11:0	//START ADDRESS for ACMD1
	UINT32 resvd                            :20; 
	};
}REG_DPG0_M0_GRP1_START_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0414C RW
	UINT32 rf_end_addr1                     :12;	//11:0	//END ADDRESS for ACMD1
	UINT32 resvd                            :20; 
	};
}REG_DPG0_M0_GPR1_ADDR_INC_BND_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04150 RW
	UINT32 rf_step_addr0                    :8;	//7:0	//STEP ADDRESS for ACMD0
	UINT32 resvd0                           :8;  
	UINT32 rf_step_addr1                    :8;	//23:16	//STEP ADDRESS for ACMD1
	UINT32 resvd1                           :8;  
	};
}REG_DPG0_M0_ADDR_INC_VAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04154 RW
	UINT32 rf_row_inc_en0                   :1;	//0 //
	UINT32 resvd0                           :3;  
	UINT32 rf_bank_inc_en0                  :1;	//4 //
	UINT32 resvd1                           :3;  
	UINT32 rf_bg_inc_en0                    :1;	//8 //
	UINT32 rf_bg_set0                       :3;	//11:9	//
	UINT32 rf_ddr4_en0                      :1;	//12 //
	UINT32 rf_row_width0                    :2;	//14:13	//
	UINT32 resvd2                           :1;  
	UINT32 rf_row_inc_en1                   :1;	//16 //
	UINT32 resvd3                           :3;  
	UINT32 rf_bank_inc_en1                  :1;	//20 //
	UINT32 resvd4                           :3;  
	UINT32 rf_bg_inc_en1                    :1;	//24 //
	UINT32 rf_bg_set1                       :3;	//27:25	//
	UINT32 rf_ddr4_en1                      :1;	//28 //
	UINT32 rf_row_width1                    :2;	//30:29	//
	UINT32 resvd5                           :1;  
	};
}REG_DPG0_M0_ROW_BANK_ADDR_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0415C RO
	UINT32 rf_rdata_err_addr                :32;	//31:0	//At RDATA compare error, captured Error Address
	};
}REG_DPG0_M0_RDATA_ERR_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04160 RO
	UINT32 rf_rdata_err_exp_data            :32;	//31:0	//At RDATA compare error, captured Expected DATA [127:96]
	};
}REG_DPG0_M0_RDATA_EXP_DATA_127_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04164 RO
	UINT32 rf_rdata_err_exp_data            :32;	//31:0	//At RDATA compare error, captured Expected DATA [95:64]
	};
}REG_DPG0_M0_RDATA_EXP_DATA_95_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04168 RO
	UINT32 rf_rdata_err_exp_data            :32;	//31:0	//At RDATA compare error, captured Expected DATA [63:32]
	};
}REG_DPG0_M0_RDATA_EXP_DATA_63_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0416C RO
	UINT32 rf_rdata_err_exp_data            :32;	//31:0	//At RDATA compare error, captured Expected DATA [31:0]
	};
}REG_DPG0_M0_RDATA_EXP_DATA_31_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04170 RO
	UINT32 rf_rdata_err_in_data             :32;	//31:0	//At RDATA compare error, captured In DATA [127:96]
	};
}REG_DPG0_M0_RDATA_IN_DATA_127_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04174 RO
	UINT32 rf_rdata_err_in_data             :32;	//31:0	//At RDATA compare error, captured In DATA [95:64]
	};
}REG_DPG0_M0_RDATA_IN_DATA_95_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04178 RO
	UINT32 rf_rdata_err_in_data             :32;	//31:0	//At RDATA compare error, captured In DATA [63:32]
	};
}REG_DPG0_M0_RDATA_IN_DATA_63_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0417C RO
	UINT32 rf_rdata_err_in_data             :32;	//31:0	//At RDATA compare error, captured In DATA [31:0]
	};
}REG_DPG0_M0_RDATA_IN_DATA_31_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04180 RW
	UINT32 rf_aid0                          :8;	//7:0	//AXI ID of ACMD0
	UINT32 rf_auser0                        :8;	//15:8	//AXI USER of ACMD0
	UINT32 rf_multi_out0                    :6;	//21:16	//AXI multiple outstanding of ACMD0
	UINT32 resvd                            :2;  
	UINT32 rf_alen0                         :4;	//27:24	//AXI Burst Length of ACMD0
	UINT32 rf_asize0                        :3;	//30:28	//AXI Size for DATA WIDTH (128 : 4 / 64 : 3 / 32 : 2) of ACMD0
	UINT32 rf_rw_sel0                       :1;	//31 //AXI Read/Write select of ACMD0	0: Write	1: Read
	};
}REG_DPG0_M0_USER_CMD_REG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04184 RW
	UINT32 rf_aid1                          :8;	//7:0	//AXI ID of ACMD1
	UINT32 rf_auser1                        :8;	//15:8	//AXI USER of ACMD1
	UINT32 rf_multi_out1                    :6;	//21:16	//AXI multiple outstanding of ACMD1
	UINT32 resvd                            :2;  
	UINT32 rf_alen1                         :4;	//27:24	//AXI Burst Length of ACMD1
	UINT32 rf_asize1                        :3;	//30:28	//AXI Size for DATA WIDTH (128 : 4 / 64 : 3 / 32 : 2) of ACMD1
	UINT32 rf_rw_sel1                       :1;	//31 //AXI Read/Write select of ACMD1	0: Write	1: Read
	};
}REG_DPG0_M0_USER_CMD_REG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04190 RW
	UINT32 rf_FAST_pready_mode              :1;	//0 //FAST Pready mode	0 : PREADY 0 (wating under AXI Transaction End)	1 : PREADY 1 (Always PREADY is 1)
	UINT32 resvd0                           :15; 
	UINT32 rf_org_start_en                  :1;	//16 //DPG original start enable	0 : APB WRITE --> AXI READ/WRITE (rf_rw_sel)	1 : APB READ --> AXI READ	    APB WRITE --> AXI WRITE
	UINT32 resvd1                           :15; 
	};
}REG_DPG0_M0_START_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D04198 RW
	UINT32 rf_lp_ctrl                       :1;	//0 //0: CLK_EN = 1'b1	1: CLK_EN = rf_DPG_en
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_LP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D041A0 RW
	UINT32 rf_direct_mode0                  :1;	//0 //DPG AXI cmd group0 Address Fixed mode enable
	UINT32 resvd0                           :15; 
	UINT32 rf_direct_mode1                  :1;	//16 //DPG AXI cmd group1 Address Fixed mode enable
	UINT32 resvd1                           :15; 
	};
}REG_DPG0_M0_DIRECT_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D041A4 RW
	UINT32 rf_aaddr_fixed_mode0             :1;	//0 //AXI cmd group 0 Address Fixed bit enable	ex) if) rf_aaddr_fixed_mode = 0x00007000 Last PWDATA = 0x5A5A5A5A	 output AxAddr [14:12] = 0x5
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_FIXED_MODE0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D041A8 RW
	UINT32 rf_aaddr_fixed_mode1             :1;	//0 //AXI cmd group 1 Address Fixed bit enable	ex) if) rf_aaddr_fixed_mode = 0x00007000 Last PWDATA = 0x5A5A5A5A	 output AxAddr [14:12] = 0x5
	UINT32 resvd                            :31; 
	};
}REG_DPG0_M0_FIXED_MODE1_T;

typedef struct {
	REG_DPG0_M0_DPG_ENABLE_T                                 dpg_enable;	//0xC4D04100
	REG_DPG0_M0_DPG_INF_CTRL_T                             dpg_inf_ctrl;	//0xC4D04104
	REG_DPG0_M0_DPG_ID_INC_T                                 dpg_id_inc;	//0xC4D04108
	REG_DPG0_M0_DPG_SW_RESET_T                             dpg_sw_reset;	//0xC4D0410C
	REG_DPG0_M0_DPG_WR_PATTERN_T                         dpg_wr_pattern;	//0xC4D04110
	REG_DPG0_M0_CMD_DLY_CTRL_T                             cmd_dly_ctrl;	//0xC4D04114
	REG_DPG0_M0_RND_AXI_LENGTH_T                         rnd_axi_length;	//0xC4D04118
	REG_DPG0_M0_AXI_TR_STATUS_T                           axi_tr_status;	//0xC4D0411C
	REG_DPG0_M0_DPG_MO_STATUS_T                           dpg_mo_status;	//0xC4D04120
	REG_DPG0_M0_DPG_BCH_ERR_STATUS_T                 dpg_bch_err_status;	//0xC4D04124
	REG_DPG0_M0_DPG_RDATA_ERR_STATUS_T             dpg_rdata_err_status;	//0xC4D04128
	REG_DPG0_M0_DPG_RCH_ERR_STATUS_T                 dpg_rch_err_status;	//0xC4D0412C
	REG_DPG0_M0_IP_GATING_T                                   ip_gating;	//0xC4D04130
	REG_DPG0_M0_DPG_GATING_T                                 dpg_gating;	//0xC4D04134
	REG_DPG0_M0_FLUSH_EN_T                                     flush_en;	//0xC4D04138
	REG_DPG0_M0_FLUSH_DONE_T                                 flush_done;	//0xC4D0413C
	REG_DPG0_M0_GRP0_START_ADDR_T                       grp0_start_addr;	//0xC4D04140
	REG_DPG0_M0_GPR0_ADDR_INC_BND_T                   gpr0_addr_inc_bnd;	//0xC4D04144
	REG_DPG0_M0_GRP1_START_ADDR_T                       grp1_start_addr;	//0xC4D04148
	REG_DPG0_M0_GPR1_ADDR_INC_BND_T                   gpr1_addr_inc_bnd;	//0xC4D0414C
	REG_DPG0_M0_ADDR_INC_VAL_T                             addr_inc_val;	//0xC4D04150
	REG_DPG0_M0_ROW_BANK_ADDR_MODE_T                 row_bank_addr_mode;	//0xC4D04154
	UINT32                                                    reserved0;	//0xC4D04158
	REG_DPG0_M0_RDATA_ERR_ADDR_T                         rdata_err_addr;	//0xC4D0415C
	REG_DPG0_M0_RDATA_EXP_DATA_127_96_T           rdata_exp_data_127_96;	//0xC4D04160
	REG_DPG0_M0_RDATA_EXP_DATA_95_64_T             rdata_exp_data_95_64;	//0xC4D04164
	REG_DPG0_M0_RDATA_EXP_DATA_63_32_T             rdata_exp_data_63_32;	//0xC4D04168
	REG_DPG0_M0_RDATA_EXP_DATA_31_0_T               rdata_exp_data_31_0;	//0xC4D0416C
	REG_DPG0_M0_RDATA_IN_DATA_127_96_T             rdata_in_data_127_96;	//0xC4D04170
	REG_DPG0_M0_RDATA_IN_DATA_95_64_T               rdata_in_data_95_64;	//0xC4D04174
	REG_DPG0_M0_RDATA_IN_DATA_63_32_T               rdata_in_data_63_32;	//0xC4D04178
	REG_DPG0_M0_RDATA_IN_DATA_31_0_T                 rdata_in_data_31_0;	//0xC4D0417C
	REG_DPG0_M0_USER_CMD_REG0_T                           user_cmd_reg0;	//0xC4D04180
	REG_DPG0_M0_USER_CMD_REG1_T                           user_cmd_reg1;	//0xC4D04184
	UINT32                                                    reserved1;	//0xC4D04188
	UINT32                                                    reserved2;	//0xC4D0418C
	REG_DPG0_M0_START_MODE_T                                 start_mode;	//0xC4D04190
	UINT32                                                    reserved3;	//0xC4D04194
	REG_DPG0_M0_LP_CTRL_T                                       lp_ctrl;	//0xC4D04198
	UINT32                                                    reserved4;	//0xC4D0419C
	REG_DPG0_M0_DIRECT_MODE_T                               direct_mode;	//0xC4D041A0
	REG_DPG0_M0_FIXED_MODE0_T                               fixed_mode0;	//0xC4D041A4
	REG_DPG0_M0_FIXED_MODE1_T                               fixed_mode1;	//0xC4D041A8
}REG_DPG0_M0_T;

extern volatile REG_DPG0_M0_T*                     gpREG_DPG0_M0;
  
#endif
