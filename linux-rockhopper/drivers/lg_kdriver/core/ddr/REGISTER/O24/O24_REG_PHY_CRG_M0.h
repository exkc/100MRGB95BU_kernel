#ifndef _REG_PHY_CRG_M0_h
#define _REG_PHY_CRG_M0_h
//Header File for PHY_CRG_M0 in \O24\O24_DRAM_M0_Register_Manual.xls

#define REG_PHY_CRG_M0_PHY_CLK_EN                                        (APB_PHY_CRG_M0_BASE+0x7000)
#define REG_PHY_CRG_M0_PHY_RST_EN                                        (APB_PHY_CRG_M0_BASE+0x7004)
#define REG_PHY_CRG_M0_PAD_CAL_CLK_DIV                                   (APB_PHY_CRG_M0_BASE+0x7008)
#define REG_PHY_CRG_M0_PHY_CLK_SRC_SEL                                   (APB_PHY_CRG_M0_BASE+0x700C)
#define REG_PHY_CRG_M0_PLL_PDB_CTRL                                      (APB_PHY_CRG_M0_BASE+0x7010)
#define REG_PHY_CRG_M0_DMODE_CTRL                                        (APB_PHY_CRG_M0_BASE+0x7014)
#define REG_PHY_CRG_M0_IBIAS_BGRBUF                                      (APB_PHY_CRG_M0_BASE+0x7018)
#define REG_PHY_CRG_M0_RX_PDB                                            (APB_PHY_CRG_M0_BASE+0x701C)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_0                            (APB_PHY_CRG_M0_BASE+0x7050)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_1                            (APB_PHY_CRG_M0_BASE+0x7054)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_2                            (APB_PHY_CRG_M0_BASE+0x7058)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_3                            (APB_PHY_CRG_M0_BASE+0x705C)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_4                            (APB_PHY_CRG_M0_BASE+0x7060)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_5                            (APB_PHY_CRG_M0_BASE+0x7064)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_6                            (APB_PHY_CRG_M0_BASE+0x7068)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_7                            (APB_PHY_CRG_M0_BASE+0x706C)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_8                            (APB_PHY_CRG_M0_BASE+0x7070)
#define REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_9                            (APB_PHY_CRG_M0_BASE+0x7074)
#define REG_PHY_CRG_M0_APHY_CTRL_SW_RSTB_DQS                             (APB_PHY_CRG_M0_BASE+0x7078)
#define REG_PHY_CRG_M0_APHY_CTRL_SW_RSTB_CK                              (APB_PHY_CRG_M0_BASE+0x707C)
#define REG_PHY_CRG_M0_APHY_PAD_CKE_DDR4                                 (APB_PHY_CRG_M0_BASE+0x7080)
#define REG_PHY_CRG_M0_APHY_PAD_ODT_DDR4                                 (APB_PHY_CRG_M0_BASE+0x7084)
#define REG_PHY_CRG_M0_APHY_PAD_CKE_ODT_LPD4                             (APB_PHY_CRG_M0_BASE+0x7088)
#define REG_PHY_CRG_M0_PLL_CTRL_STATUS                                   (APB_PHY_CRG_M0_BASE+0x7100)
#define REG_PHY_CRG_M0_DFS_CTRL_STATUS                                   (APB_PHY_CRG_M0_BASE+0x7104)
#define REG_PHY_CRG_M0_LP_CTRL_STATUS                                    (APB_PHY_CRG_M0_BASE+0x7108)
#define REG_PHY_CRG_M0_RTE_STATUS                                        (APB_PHY_CRG_M0_BASE+0x710C)
#define REG_PHY_CRG_M0_CAL_STATUS                                        (APB_PHY_CRG_M0_BASE+0x7110)
#define REG_PHY_CRG_M0_RTE_CAL_STATUS                                    (APB_PHY_CRG_M0_BASE+0x7114)
#define REG_PHY_CRG_M0_SPARE                                             (APB_PHY_CRG_M0_BASE+0x7118)

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F000 RW
	UINT32 phy_reg_clk_ena                  :1;	//0 //PHY register clock enable
	UINT32 resvd0                           :3;  
	UINT32 phy_clk_ena                      :1;	//4 //PHY core clock enable
	UINT32 resvd1                           :27; 
	};
}REG_PHY_CRG_M0_PHY_CLK_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F004 RW
	UINT32 phy_reg_sw_resetn                :1;	//0 //PHY register software reset
	UINT32 resvd0                           :3;  
	UINT32 phy_sw_resetn                    :1;	//4 //PHY core software reset
	UINT32 resvd1                           :27; 
	};
}REG_PHY_CRG_M0_PHY_RST_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F008 
	UINT32 pad_cal_clk_src_en               :1;	//0 //Calibration pad clock source enable
	UINT32 resvd0                           :3;  
	UINT32 pad_cal_update_req               :1;	//4 //Calibration pad clock update request
	UINT32 resvd1                           :3;  
	UINT32 pad_cal_div_value                :8;	//15:8	//Calibration pad clock divider value	If this parameter value is set as 'h0, the divider operates the "bypass mode".
	UINT32 pad_cal_update_ack               :1;	//16 //Calibration pad clock update acknowledgement
	UINT32 resvd2                           :15; 
	};
}REG_PHY_CRG_M0_PAD_CAL_CLK_DIV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F00C RW
	UINT32 phy_clk_src_sel_dfs0             :2;	//1:0	//Select dmc clock source for DFS0 shadow register	- 2'b00 : APB_CLK	- 2'b01 : AIOPLL_FOUT (FAST)	- 2'b1X : AIOPLL_FOUT2 (SLOW)
	UINT32 resvd0                           :2;  
	UINT32 phy_clk_src_sel_dfs1             :2;	//5:4	//Select dmc clock source for DFS1 shadow register	- 2'b00 : APB_CLK	- 2'b01 : AIOPLL_FOUT (FAST)	- 2'b1X : AIOPLL_FOUT2 (SLOW)
	UINT32 resvd1                           :2;  
	UINT32 phy_clk_src_sel_dfs2             :2;	//9:8	//Select dmc clock source for DFS2 shadow register	- 2'b00 : APB_CLK	- 2'b01 : AIOPLL_FOUT	- 2'b1X : AIOPLL_FOUT2	This parameter value are applied when the "emergency_pll_auto_src_sel" parameter is disabled
	UINT32 resvd2                           :2;  
	UINT32 phy_clk_src_sel_pclk             :1;	//12 //Select dmc clock source by using APB_CLK regardless of PLL	- 1'b0 : AIOPLL_FOUT or AIOPLL_FOUT2	- 1'b1 : APB_CLK
	UINT32 resvd3                           :19; 
	};
}REG_PHY_CRG_M0_PHY_CLK_SRC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F010 RW
	UINT32 dfs_pll_auto_pdb_enable          :1;	//0 //Not used
	UINT32 resvd0                           :3;  
	UINT32 emergency_pll_auto_src_sel       :1;	//4 //Automatic PLL source selection when applying emergency DFS operation.	- 1'b0 : Disable	- 1'b1 : Enable	When this parameter is disabled, the phy_clk_src_sel_dfs2 parameter value are applied during emergency DFS exit.
	UINT32 resvd1                           :3;  
	UINT32 aiopll_lock_wait_sel             :1;	//8 //PLL locking done selection	- 1'b0 : By handshaking	- 1'b1 : By waiting pre-defined time
	UINT32 resvd2                           :7;  
	UINT32 aiopll_lock_wait_time            :16;	//31:16	//Waiting time for PLL locking done
	};
}REG_PHY_CRG_M0_PLL_PDB_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F014 RW
	UINT32 reg_dmode                        :1;	//0 //DRAM device type selection	- 1'b0 : LPDDR4	- 1'b1 : DDR4
	UINT32 resvd0                           :3;  
	UINT32 reg_dmode_x                      :1;	//4 //DRAM device type selection	- 1'b0 : LPDDR4	- 1'b1 : LPDDR4x
	UINT32 resvd1                           :27; 
	};
}REG_PHY_CRG_M0_DMODE_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F018 RW
	UINT32 reg_ibias_bgrbuf                 :6;	//5:0	//IBIAS BGR buffer control	- [5] : Tx DRV mode (1'b0 : RET, 1'b1 : STBY)	- [4:3] : Not used	- [2] : BGR PDB (1'b0 : power-off, 1'b1 : power-on)	- [1:0] : Tx VREF control (2'b00 : weak, ¡¦, 2'b11 : strong)
	UINT32 resvd0                           :2;  
	UINT32 reg_ibias_bgrbuf_ds0             :6;	//13:8	//IBIAS BGR buffer control for PHY deep-sleep mode0	- [5] : Tx DRV mode (1'b0 : RET, 1'b1 : STBY)	- [4:3] : Not used	- [2] : BGR PDB (1'b0 : power-off, 1'b1 : power-on)	- [1:0] : Tx VREF control (2'b00 : weak, ¡¦, 2'b11 : strong)
	UINT32 resvd1                           :2;  
	UINT32 reg_ibias_bgrbuf_ds1             :6;	//21:16	//IBIAS BGR buffer control for PHY deep-sleep mode0	- [5] : Tx DRV mode (1'b0 : RET, 1'b1 : STBY)	- [4:3] : Not used	- [2] : BGR PDB (1'b0 : power-off, 1'b1 : power-on)	- [1:0] : Tx VREF control (2'b00 : weak, ¡¦, 2'b11 : strong)
	UINT32 resvd2                           :10; 
	};
}REG_PHY_CRG_M0_IBIAS_BGRBUF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F01C RW
	UINT32 reg_v_ctr                        :3;	//2:0	//
	UINT32 resvd0                           :1;  
	UINT32 reg_rx_pdb                       :1;	//4 //
	UINT32 resvd1                           :3;  
	UINT32 reg_rx_pdb_ds0                   :1;	//8 //
	UINT32 resvd2                           :3;  
	UINT32 reg_rx_pdb_ds1                   :1;	//12 //
	UINT32 resvd3                           :19; 
	};
}REG_PHY_CRG_M0_RX_PDB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F050 RW
	UINT32 aphy_dq_pwrup_rstb_byte0_bit0    :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit1    :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit2    :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit3    :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit4    :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit5    :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit6    :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte0_bit7    :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F054 RW
	UINT32 aphy_dq_pwrup_rstb_byte1_bit0    :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit1    :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit2    :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit3    :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit4    :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit5    :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit6    :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte1_bit7    :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F058 RW
	UINT32 aphy_dq_pwrup_rstb_byte2_bit0    :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit1    :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit2    :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit3    :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit4    :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit5    :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit6    :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte2_bit7    :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F05C RW
	UINT32 aphy_dq_pwrup_rstb_byte3_bit0    :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit1    :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit2    :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit3    :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit4    :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit5    :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit6    :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_dq_pwrup_rstb_byte3_bit7    :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F060 RW
	UINT32 aphy_dqs_pwrup_rstb_byte0        :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_dqs_pwrup_rstb_byte1        :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_dqs_pwrup_rstb_byte2        :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_dqs_pwrup_rstb_byte3        :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_dmi_pwrup_rstb_byte0        :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_dmi_pwrup_rstb_byte1        :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_dmi_pwrup_rstb_byte2        :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_dmi_pwrup_rstb_byte3        :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F064 RW
	UINT32 aphy_AC0_pwrup_rstb              :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_AC1_pwrup_rstb              :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_AC2_pwrup_rstb              :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_AC3_pwrup_rstb              :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_AC4_pwrup_rstb              :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_AC5_pwrup_rstb              :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_AC6_pwrup_rstb              :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_AC7_pwrup_rstb              :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F068 RW
	UINT32 aphy_AC8_pwrup_rstb              :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_AC9_pwrup_rstb              :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_AC10_pwrup_rstb             :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_AC11_pwrup_rstb             :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_AC12_pwrup_rstb             :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_AC13_pwrup_rstb             :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_AC14_pwrup_rstb             :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_AC15_pwrup_rstb             :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F06C RW
	UINT32 aphy_AC16_pwrup_rstb             :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_AC17_pwrup_rstb             :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_AC18_pwrup_rstb             :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_AC19_pwrup_rstb             :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_AC20_pwrup_rstb             :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_AC21_pwrup_rstb             :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_AC22_pwrup_rstb             :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_AC23_pwrup_rstb             :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F070 RW
	UINT32 aphy_AC24_pwrup_rstb             :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_AC25_pwrup_rstb             :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_AC26_pwrup_rstb             :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_AC27_pwrup_rstb             :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_cal_pwrup_rstb              :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_rst_n_pwrup_rstb            :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :3;  
	UINT32 aphy_CK_U_pwrup_rstb             :1;	//24 //Power down signal for power saving
	UINT32 resvd6                           :3;  
	UINT32 aphy_CK_L_pwrup_rstb             :1;	//28 //Power down signal for power saving
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F074 RW
	UINT32 aphy_vref_pwrup_rstb_byte3       :1;	//0 //Power down signal for power saving
	UINT32 resvd0                           :3;  
	UINT32 aphy_vref_pwrup_rstb_byte2       :1;	//4 //Power down signal for power saving
	UINT32 resvd1                           :3;  
	UINT32 aphy_vref_pwrup_rstb_byte1       :1;	//8 //Power down signal for power saving
	UINT32 resvd2                           :3;  
	UINT32 aphy_vref_pwrup_rstb_byte0       :1;	//12 //Power down signal for power saving
	UINT32 resvd3                           :3;  
	UINT32 aphy_cke_l_pwrup_rstb            :1;	//16 //Power down signal for power saving
	UINT32 resvd4                           :3;  
	UINT32 aphy_cke_u_pwrup_rstb            :1;	//20 //Power down signal for power saving
	UINT32 resvd5                           :11; 
	};
}REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F078 RW
	UINT32 aphy_sw_rstb_byte0               :1;	//0 //aphy dqs0 pin software reset
	UINT32 resvd0                           :3;  
	UINT32 aphy_sw_rstb_con_byte0           :1;	//4 //aphy dqs0 pin software reset delay control
	UINT32 resvd1                           :3;  
	UINT32 aphy_sw_rstb_byte1               :1;	//8 //aphy dqs1 pin software reset
	UINT32 resvd2                           :3;  
	UINT32 aphy_sw_rstb_con_byte1           :1;	//12 //aphy dqs1 pin software reset delay control
	UINT32 resvd3                           :3;  
	UINT32 aphy_sw_rstb_byte2               :1;	//16 //aphy dqs2 pin software reset
	UINT32 resvd4                           :3;  
	UINT32 aphy_sw_rstb_con_byte2           :1;	//20 //aphy dqs2 pin software reset delay control
	UINT32 resvd5                           :3;  
	UINT32 aphy_sw_rstb_byte3               :1;	//24 //aphy dqs3 pin software reset
	UINT32 resvd6                           :3;  
	UINT32 aphy_sw_rstb_con_byte3           :1;	//28 //aphy dqs3 pin software reset delay control
	UINT32 resvd7                           :3;  
	};
}REG_PHY_CRG_M0_APHY_CTRL_SW_RSTB_DQS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F07C RW
	UINT32 aphy_sw_rstb_ck_l                :1;	//0 //aphy ck_l pin software reset
	UINT32 resvd0                           :3;  
	UINT32 aphy_sw_rstb_con_ck_l            :1;	//4 //aphy ck_l pin software reset delay control
	UINT32 resvd1                           :11; 
	UINT32 aphy_sw_rstb_ck_u                :1;	//16 //aphy ck_u pin software reset
	UINT32 resvd2                           :3;  
	UINT32 aphy_sw_rstb_con_ck_u            :1;	//20 //aphy ck_u pin software reset delay control
	UINT32 resvd3                           :11; 
	};
}REG_PHY_CRG_M0_APHY_CTRL_SW_RSTB_CK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F080 RW
	UINT32 aphy_pad_cke_ddr4                :28;	//27:0	//This register indicates which ac PADS are CKE0, CKE1 for device mode DDR4	When AC0 : CKE0 and AC21 : CKE1, aphy_pad_cke_ddr4 has 0x00200001	aphy_pad_cke_ddr4[0] is related to PWRUP_RSTB at AC0	aphy_pad_cke_ddr4[1] is related to PWRUP_RSTB at AC1	.	.	.	aphy_pad_cke_ddr4[26] = PWRUP_RSTB at AC26		when lp_ds0_req, lp_ds1_req, lp_ls_req is asserted, registers which have ¡®0¡¯ will be turned off related AC PAD.
	UINT32 resvd                            :4;  
	};
}REG_PHY_CRG_M0_APHY_PAD_CKE_DDR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F084 RW
	UINT32 aphy_pad_odt_ddr4                :28;	//27:0	//This register indicates which ac PADS are ODT0, ODT1 for device mode DDR4	When AC2 : ODT0 and AC20 : ODT1, aphy_pad_odt_ddr4 has 0x00100004	aphy_pad_odt_ddr4[0] is related to PWRUP_RSTB at AC0	aphy_pad_odt_ddr4[1] is related to PWRUP_RSTB at AC1	.	.	.	aphy_pad_odt_ddr4[26] is related to PWRUP_RSTB at AC26	when lp_ds0_req, lp_ds1_req asserted, registers which have ¡®0¡¯ will be turned off related AC PAD.
	UINT32 resvd                            :4;  
	};
}REG_PHY_CRG_M0_APHY_PAD_ODT_DDR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F088 RW
	UINT32 aphy_pad_cke_odt_lpd4            :28;	//27:0	//This register indicates which ac PADS are CKE0, CKE1, ODT0, ODT1 for device mode LPDDR4	When AC7 : ODT0, AC9 : CKE0, AC18 : CKE1 and, aphy_pad_cke_odt_lpd4 has 0x00240280	aphy_pad_cke_odt_lpd4 [0] is related to PWRUP_RSTB at AC0	aphy_pad_cke_odt_lpd4 [1] is related to PWRUP_RSTB at AC1	.	.	.	aphy_pad_cke_odt_lpd4 [26] is related to PWRUP_RSTB at AC26	when lp_ds0_req, lp_ds1_req, lp_ls_req is asserted, registers which have ¡®0¡¯ will be turned off related AC PAD.
	UINT32 aphy_pad_dqs_dq_dmi_ds0          :1;	//28 //Power-up reset control for PHY deep-sleep mode0 (DQS/DQ/DMI)	- 1'b0 : Power-off	- 1'b1 : Power-on
	UINT32 aphy_pad_dqs_dq_dmi_ds1          :1;	//29 //Power-up reset control for PHY deep-sleep mode1 (DQS/DQ/DMI)	- 1'b0 : Power-off	- 1'b1 : Power-on
	UINT32 aphy_pad_vref_cal_ds0            :1;	//30 //Power-up reset control for PHY deep-sleep mode0 (VREF/CAL)	- 1'b0 : Power-off	- 1'b1 : Power-on
	UINT32 aphy_pad_vref_cal_ds1            :1;	//31 //Power-up reset control for PHY deep-sleep mode1 (VREF/CAL)	- 1'b0 : Power-off	- 1'b1 : Power-on
	};
}REG_PHY_CRG_M0_APHY_PAD_CKE_ODT_LPD4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F100 RO
	UINT32 GFMRBGEN_SEL_APBCLK              :1;	//0 //Glitch-free mux source clock selection	- 1'b0 : Depending on SEL_FAST	- 1'b1 : APBCLK
	UINT32 GFMRBGEN_SEL_FAST                :1;	//1 //Glitch-free mux source clock selection	- 1'b0 : PLL1	- 1'b1 : PLL0
	UINT32 resvd0                           :2;  
	UINT32 PLL0_LOCKD                       :1;	//4 //PLL lock detector out	- 1'b0 : Locking is not done	- 1'b1 : Locking is done
	UINT32 PLL1_LOCKD                       :1;	//5 //PLL lock detector out	- 1'b0 : Locking is not done	- 1'b1 : Locking is done
	UINT32 resvd1                           :2;  
	UINT32 GFMRBGEN_UPDATE_LOCKD            :1;	//8 //Clock change request from dPHY	- 1'b0 : Stand-by	- 1'b1 : Update
	UINT32 GFMRBGEN_LOCKHOLD_LOCKD          :1;	//9 //Clock change done signal for dPHY
	UINT32 resvd2                           :2;  
	UINT32 WAIT_TIME_LOCKD                  :1;	//12 //When aiopll_lock_wait_sel==1'b1, This parameter is set if pre-defined time in "aiopll_lock_wait_time" parameter is passed.
	UINT32 resvd3                           :3;  
	UINT32 PLL0_LOCK_DROP_CNT               :4;	//19:16	//Detecting pll1 lockd signal to low
	UINT32 PLL1_LOCK_DROP_CNT               :4;	//23:20	//Detecting pll0 lockd signal to low
	UINT32 resvd4                           :8;  
	};
}REG_PHY_CRG_M0_PLL_CTRL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F104 RO
	UINT32 dc_clk_change_req                :1;	//0 //Clock change request for DFS
	UINT32 resvd0                           :3;  
	UINT32 es_clk_change_done               :1;	//4 //Clock change done for DFS
	UINT32 resvd1                           :3;  
	UINT32 dc_clk_change_type               :5;	//12:8	//Clock change request type for DFS
	UINT32 resvd2                           :3;  
	UINT32 dc_shadow_reg_sel                :3;	//18:16	//Currently used DFS group information
	UINT32 resvd3                           :1;  
	UINT32 emergency_pll_init_req           :1;	//20 //Emergency DFS request from DMC
	UINT32 emergency_pll_init_ack           :1;	//21 //GPLL ready for emergency DFS to DMC
	UINT32 resvd4                           :2;  
	UINT32 emergency_gpll0_flag             :1;	//24 //Emergency DFS flag for GPLL0
	UINT32 emergency_gpll1_flag             :1;	//25 //Emergency DFS flag for GPLL1
	UINT32 resvd5                           :6;  
	};
}REG_PHY_CRG_M0_DFS_CTRL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F108 RO
	UINT32 lp_op_flag                       :1;	//0 //PHY LP mode flag
	UINT32 lp_dfi_lp_ls_req                 :1;	//1 //PHY light-sleep mode request
	UINT32 lp_dfi_lp_ds0_req                :1;	//2 //PHY deep-sleep mode request
	UINT32 lp_dfi_lp_ds1_req                :1;	//3 //PHY deep-sleep mode request
	UINT32 lp_dfi_lp_reboot_req             :1;	//4 //PHY reboot request when exit deep-sleep mode
	UINT32 lp_dfi_lp_ds0_req_latch          :1;	//5 //Detection flag for exit deep-sleep mode
	UINT32 lp_dfi_lp_ds1_req_latch          :1;	//6 //Detection flag for exit deep-sleep mode
	UINT32 lp_dfi_lp_ds0_exit               :1;	//7 //Detection flag of GPLL locking for deep-sleep mode
	UINT32 lp_dfi_lp_ds1_exit               :1;	//8 //Detection flag of GPLL locking for deep-sleep mode
	UINT32 resvd0                           :3;  
	UINT32 es_pll_ready                     :1;	//12 //Clock change done for PHY low-power mode
	UINT32 resvd1                           :19; 
	};
}REG_PHY_CRG_M0_LP_CTRL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F10C RO
	UINT32 mon_rte_dq0                      :1;	//0 //This bit has an information the retention pad's value at dq0 pad
	UINT32 mon_rte_dq1                      :1;	//1 //This bit has an information the retention pad's value at dq1 pad
	UINT32 mon_rte_dq2                      :1;	//2 //This bit has an information the retention pad's value at dq2 pad
	UINT32 mon_rte_dq3                      :1;	//3 //This bit has an information the retention pad's value at dq3 pad
	UINT32 mon_rte_dq4                      :1;	//4 //This bit has an information the retention pad's value at dq4 pad
	UINT32 mon_rte_dq5                      :1;	//5 //This bit has an information the retention pad's value at dq5 pad
	UINT32 mon_rte_dq6                      :1;	//6 //This bit has an information the retention pad's value at dq6 pad
	UINT32 mon_rte_dq7                      :1;	//7 //This bit has an information the retention pad's value at dq7 pad
	UINT32 mon_rte_dq8                      :1;	//8 //This bit has an information the retention pad's value at dq8 pad
	UINT32 mon_rte_dq9                      :1;	//9 //This bit has an information the retention pad's value at dq9 pad
	UINT32 mon_rte_dq10                     :1;	//10 //This bit has an information the retention pad's value at dq10 pad
	UINT32 mon_rte_dq11                     :1;	//11 //This bit has an information the retention pad's value at dq11 pad
	UINT32 mon_rte_dq12                     :1;	//12 //This bit has an information the retention pad's value at dq12 pad
	UINT32 mon_rte_dq13                     :1;	//13 //This bit has an information the retention pad's value at dq13 pad
	UINT32 mon_rte_dq14                     :1;	//14 //This bit has an information the retention pad's value at dq14 pad
	UINT32 mon_rte_dq15                     :1;	//15 //This bit has an information the retention pad's value at dq15 pad
	UINT32 mon_rte_dq16                     :1;	//16 //This bit has an information the retention pad's value at dq16 pad
	UINT32 mon_rte_dq17                     :1;	//17 //This bit has an information the retention pad's value at dq17 pad
	UINT32 mon_rte_dq18                     :1;	//18 //This bit has an information the retention pad's value at dq18 pad
	UINT32 mon_rte_dq19                     :1;	//19 //This bit has an information the retention pad's value at dq19 pad
	UINT32 mon_rte_dq20                     :1;	//20 //This bit has an information the retention pad's value at dq20 pad
	UINT32 mon_rte_dq21                     :1;	//21 //This bit has an information the retention pad's value at dq21 pad
	UINT32 mon_rte_dq22                     :1;	//22 //This bit has an information the retention pad's value at dq22 pad
	UINT32 mon_rte_dq23                     :1;	//23 //This bit has an information the retention pad's value at dq23 pad
	UINT32 mon_rte_dq24                     :1;	//24 //This bit has an information the retention pad's value at dq24 pad
	UINT32 mon_rte_dq25                     :1;	//25 //This bit has an information the retention pad's value at dq25 pad
	UINT32 mon_rte_dq26                     :1;	//26 //This bit has an information the retention pad's value at dq26 pad
	UINT32 mon_rte_dq27                     :1;	//27 //This bit has an information the retention pad's value at dq27 pad
	UINT32 mon_rte_dq28                     :1;	//28 //This bit has an information the retention pad's value at dq28 pad
	UINT32 mon_rte_dq29                     :1;	//29 //This bit has an information the retention pad's value at dq29 pad
	UINT32 mon_rte_dq30                     :1;	//30 //This bit has an information the retention pad's value at dq30 pad
	UINT32 mon_rte_dq31                     :1;	//31 //Retention monitoring parameter. This bit has an information the retention pad's value at dq31 pad	- 1'b1 : retention states
	};
}REG_PHY_CRG_M0_RTE_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F110 RO
	UINT32 mon_calcode_dq0                  :1;	//0 //This bit has an information the calibration pad's value at dq0 pad
	UINT32 mon_calcode_dq1                  :1;	//1 //This bit has an information the calibration pad's value at dq1 pad
	UINT32 mon_calcode_dq2                  :1;	//2 //This bit has an information the calibration pad's value at dq2 pad
	UINT32 mon_calcode_dq3                  :1;	//3 //This bit has an information the calibration pad's value at dq3 pad
	UINT32 mon_calcode_dq4                  :1;	//4 //This bit has an information the calibration pad's value at dq4 pad
	UINT32 mon_calcode_dq5                  :1;	//5 //This bit has an information the calibration pad's value at dq5 pad
	UINT32 mon_calcode_dq6                  :1;	//6 //This bit has an information the calibration pad's value at dq6 pad
	UINT32 mon_calcode_dq7                  :1;	//7 //This bit has an information the calibration pad's value at dq7 pad
	UINT32 mon_calcode_dq8                  :1;	//8 //This bit has an information the calibration pad's value at dq8 pad
	UINT32 mon_calcode_dq9                  :1;	//9 //This bit has an information the calibration pad's value at dq9 pad
	UINT32 mon_calcode_dq10                 :1;	//10 //This bit has an information the calibration pad's value at dq10 pad
	UINT32 mon_calcode_dq11                 :1;	//11 //This bit has an information the calibration pad's value at dq11 pad
	UINT32 mon_calcode_dq12                 :1;	//12 //This bit has an information the calibration pad's value at dq12 pad
	UINT32 mon_calcode_dq13                 :1;	//13 //This bit has an information the calibration pad's value at dq13 pad
	UINT32 mon_calcode_dq14                 :1;	//14 //This bit has an information the calibration pad's value at dq14 pad
	UINT32 mon_calcode_dq15                 :1;	//15 //This bit has an information the calibration pad's value at dq15 pad
	UINT32 mon_calcode_dq16                 :1;	//16 //This bit has an information the calibration pad's value at dq16 pad
	UINT32 mon_calcode_dq17                 :1;	//17 //This bit has an information the calibration pad's value at dq17 pad
	UINT32 mon_calcode_dq18                 :1;	//18 //This bit has an information the calibration pad's value at dq18 pad
	UINT32 mon_calcode_dq19                 :1;	//19 //This bit has an information the calibration pad's value at dq19 pad
	UINT32 mon_calcode_dq20                 :1;	//20 //This bit has an information the calibration pad's value at dq20 pad
	UINT32 mon_calcode_dq21                 :1;	//21 //This bit has an information the calibration pad's value at dq21 pad
	UINT32 mon_calcode_dq22                 :1;	//22 //This bit has an information the calibration pad's value at dq22 pad
	UINT32 mon_calcode_dq23                 :1;	//23 //This bit has an information the calibration pad's value at dq23 pad
	UINT32 mon_calcode_dq24                 :1;	//24 //This bit has an information the calibration pad's value at dq24 pad
	UINT32 mon_calcode_dq25                 :1;	//25 //This bit has an information the calibration pad's value at dq25 pad
	UINT32 mon_calcode_dq26                 :1;	//26 //This bit has an information the calibration pad's value at dq26 pad
	UINT32 mon_calcode_dq27                 :1;	//27 //This bit has an information the calibration pad's value at dq27 pad
	UINT32 mon_calcode_dq28                 :1;	//28 //This bit has an information the calibration pad's value at dq28 pad
	UINT32 mon_calcode_dq29                 :1;	//29 //This bit has an information the calibration pad's value at dq29 pad
	UINT32 mon_calcode_dq30                 :1;	//30 //This bit has an information the calibration pad's value at dq30 pad
	UINT32 mon_calcode_dq31                 :1;	//31 //Calcode connection test monitoring parameter. This bit has an information the retention pad's value at dq31 pad	- 1'b1 : passed
	};
}REG_PHY_CRG_M0_CAL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F114 RO
	UINT32 mon_rte_dm0                      :1;	//0 //This bit has an information the retention pad's value at dm0 pad
	UINT32 mon_rte_dm1                      :1;	//1 //This bit has an information the retention pad's value at dm1 pad
	UINT32 mon_rte_dm2                      :1;	//2 //This bit has an information the retention pad's value at dm2 pad
	UINT32 mon_rte_dm3                      :1;	//3 //This bit has an information the retention pad's value at dm3 pad
	UINT32 mon_rte_cke_l                    :1;	//4 //This bit has an information the retention pad's value at cke_l pad
	UINT32 mon_rte_cke_u                    :1;	//5 //This bit has an information the retention pad's value at cke_u pad
	UINT32 mon_rte_rst_n                    :1;	//6 //This bit has an information the retention pad's value at rst_n pad
	UINT32 resvd0                           :9;  
	UINT32 mon_calcode_dm0                  :1;	//16 //This bit has an information the calibration pad's value at dm0 pad
	UINT32 mon_calcode_dm1                  :1;	//17 //This bit has an information the calibration pad's value at dm1 pad
	UINT32 mon_calcode_dm2                  :1;	//18 //This bit has an information the calibration pad's value at dm2 pad
	UINT32 mon_calcode_dm3                  :1;	//19 //This bit has an information the calibration pad's value at dm3 pad
	UINT32 resvd1                           :12; 
	};
}REG_PHY_CRG_M0_RTE_CAL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0F118 
	UINT32 spare_rw                         :16;	//15:0	//Spare RW register for lpddr4_phy_env_set block	[0] : GFMRBGEN_UPDATE_LOCKD reset (the positive edge is used as reset)
	UINT32 spare_ro                         :16;	//31:16	//Spare RO register for lpddr4_phy_env_set block
	};
}REG_PHY_CRG_M0_SPARE_T;

typedef struct {
	REG_PHY_CRG_M0_PHY_CLK_EN_T                              phy_clk_en;	//0xC4D0F000
	REG_PHY_CRG_M0_PHY_RST_EN_T                              phy_rst_en;	//0xC4D0F004
	REG_PHY_CRG_M0_PAD_CAL_CLK_DIV_T                    pad_cal_clk_div;	//0xC4D0F008
	REG_PHY_CRG_M0_PHY_CLK_SRC_SEL_T                    phy_clk_src_sel;	//0xC4D0F00C
	REG_PHY_CRG_M0_PLL_PDB_CTRL_T                          pll_pdb_ctrl;	//0xC4D0F010
	REG_PHY_CRG_M0_DMODE_CTRL_T                              dmode_ctrl;	//0xC4D0F014
	REG_PHY_CRG_M0_IBIAS_BGRBUF_T                          ibias_bgrbuf;	//0xC4D0F018
	REG_PHY_CRG_M0_RX_PDB_T                                      rx_pdb;	//0xC4D0F01C
	UINT32                                                    reserved0;	//0xC4D0F020
	UINT32                                                    reserved1;	//0xC4D0F024
	UINT32                                                    reserved2;	//0xC4D0F028
	UINT32                                                    reserved3;	//0xC4D0F02C
	UINT32                                                    reserved4;	//0xC4D0F030
	UINT32                                                    reserved5;	//0xC4D0F034
	UINT32                                                    reserved6;	//0xC4D0F038
	UINT32                                                    reserved7;	//0xC4D0F03C
	UINT32                                                    reserved8;	//0xC4D0F040
	UINT32                                                    reserved9;	//0xC4D0F044
	UINT32                                                   reserved10;	//0xC4D0F048
	UINT32                                                   reserved11;	//0xC4D0F04C
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_0_T      aphy_ctrl_pwrup_rstb_0;	//0xC4D0F050
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_1_T      aphy_ctrl_pwrup_rstb_1;	//0xC4D0F054
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_2_T      aphy_ctrl_pwrup_rstb_2;	//0xC4D0F058
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_3_T      aphy_ctrl_pwrup_rstb_3;	//0xC4D0F05C
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_4_T      aphy_ctrl_pwrup_rstb_4;	//0xC4D0F060
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_5_T      aphy_ctrl_pwrup_rstb_5;	//0xC4D0F064
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_6_T      aphy_ctrl_pwrup_rstb_6;	//0xC4D0F068
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_7_T      aphy_ctrl_pwrup_rstb_7;	//0xC4D0F06C
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_8_T      aphy_ctrl_pwrup_rstb_8;	//0xC4D0F070
	REG_PHY_CRG_M0_APHY_CTRL_PWRUP_RSTB_9_T      aphy_ctrl_pwrup_rstb_9;	//0xC4D0F074
	REG_PHY_CRG_M0_APHY_CTRL_SW_RSTB_DQS_T        aphy_ctrl_sw_rstb_dqs;	//0xC4D0F078
	REG_PHY_CRG_M0_APHY_CTRL_SW_RSTB_CK_T          aphy_ctrl_sw_rstb_ck;	//0xC4D0F07C
	REG_PHY_CRG_M0_APHY_PAD_CKE_DDR4_T                aphy_pad_cke_ddr4;	//0xC4D0F080
	REG_PHY_CRG_M0_APHY_PAD_ODT_DDR4_T                aphy_pad_odt_ddr4;	//0xC4D0F084
	REG_PHY_CRG_M0_APHY_PAD_CKE_ODT_LPD4_T        aphy_pad_cke_odt_lpd4;	//0xC4D0F088
	UINT32                                                   reserved12;	//0xC4D0F08C
	UINT32                                                   reserved13;	//0xC4D0F090
	UINT32                                                   reserved14;	//0xC4D0F094
	UINT32                                                   reserved15;	//0xC4D0F098
	UINT32                                                   reserved16;	//0xC4D0F09C
	UINT32                                                   reserved17;	//0xC4D0F0A0
	UINT32                                                   reserved18;	//0xC4D0F0A4
	UINT32                                                   reserved19;	//0xC4D0F0A8
	UINT32                                                   reserved20;	//0xC4D0F0AC
	UINT32                                                   reserved21;	//0xC4D0F0B0
	UINT32                                                   reserved22;	//0xC4D0F0B4
	UINT32                                                   reserved23;	//0xC4D0F0B8
	UINT32                                                   reserved24;	//0xC4D0F0BC
	UINT32                                                   reserved25;	//0xC4D0F0C0
	UINT32                                                   reserved26;	//0xC4D0F0C4
	UINT32                                                   reserved27;	//0xC4D0F0C8
	UINT32                                                   reserved28;	//0xC4D0F0CC
	UINT32                                                   reserved29;	//0xC4D0F0D0
	UINT32                                                   reserved30;	//0xC4D0F0D4
	UINT32                                                   reserved31;	//0xC4D0F0D8
	UINT32                                                   reserved32;	//0xC4D0F0DC
	UINT32                                                   reserved33;	//0xC4D0F0E0
	UINT32                                                   reserved34;	//0xC4D0F0E4
	UINT32                                                   reserved35;	//0xC4D0F0E8
	UINT32                                                   reserved36;	//0xC4D0F0EC
	UINT32                                                   reserved37;	//0xC4D0F0F0
	UINT32                                                   reserved38;	//0xC4D0F0F4
	UINT32                                                   reserved39;	//0xC4D0F0F8
	UINT32                                                   reserved40;	//0xC4D0F0FC
	REG_PHY_CRG_M0_PLL_CTRL_STATUS_T                    pll_ctrl_status;	//0xC4D0F100
	REG_PHY_CRG_M0_DFS_CTRL_STATUS_T                    dfs_ctrl_status;	//0xC4D0F104
	REG_PHY_CRG_M0_LP_CTRL_STATUS_T                      lp_ctrl_status;	//0xC4D0F108
	REG_PHY_CRG_M0_RTE_STATUS_T                              rte_status;	//0xC4D0F10C
	REG_PHY_CRG_M0_CAL_STATUS_T                              cal_status;	//0xC4D0F110
	REG_PHY_CRG_M0_RTE_CAL_STATUS_T                      rte_cal_status;	//0xC4D0F114
	REG_PHY_CRG_M0_SPARE_T                                        spare;	//0xC4D0F118
}REG_PHY_CRG_M0_T;

extern volatile REG_PHY_CRG_M0_T*                  gpREG_PHY_CRG_M0;

#endif
