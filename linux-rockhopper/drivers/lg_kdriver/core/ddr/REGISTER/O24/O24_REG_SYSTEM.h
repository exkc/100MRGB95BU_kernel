#ifndef _REG_SYSTEM_h
#define _REG_SYSTEM_h
//Header File for SYSTEM in \O24\O24_DRAM_MCU_Register_Manual.xls

#define REG_SYSTEM_MCUVERSION                                                (APB_SYSTEM_BASE+0x0000)
#define REG_SYSTEM_APBTOUTEN                                                 (APB_SYSTEM_BASE+0x0060)
#define REG_SYSTEM_APBTOUTCNT                                                (APB_SYSTEM_BASE+0x0064)
#define REG_SYSTEM_APBTOUTSLVERR                                             (APB_SYSTEM_BASE+0x0068)
#define REG_SYSTEM_APBTOUTINTREN                                             (APB_SYSTEM_BASE+0x0070)
#define REG_SYSTEM_APBTOUTMIS                                                (APB_SYSTEM_BASE+0x0074)
#define REG_SYSTEM_APBTOUTRIS                                                (APB_SYSTEM_BASE+0x0078)
#define REG_SYSTEM_APBTOUTINTRCLR                                            (APB_SYSTEM_BASE+0x007C)
#define REG_SYSTEM_MCUP0FLUSHEN                                              (APB_SYSTEM_BASE+0x0080)
#define REG_SYSTEM_MCUP1FLUSHEN                                              (APB_SYSTEM_BASE+0x0084)
#define REG_SYSTEM_DDRMFLUSHEN                                               (APB_SYSTEM_BASE+0x0088)
#define REG_SYSTEM_MCUP0FLUSHDONE                                            (APB_SYSTEM_BASE+0x0090)
#define REG_SYSTEM_MCUP1FLUSHDONE                                            (APB_SYSTEM_BASE+0x0094)
#define REG_SYSTEM_DDRMFLUSHDONE                                             (APB_SYSTEM_BASE+0x0098)
#define REG_SYSTEM_DDRMASCADDR0MSB                                           (APB_SYSTEM_BASE+0x00B0)
#define REG_SYSTEM_DDRMASCADDR1MSB                                           (APB_SYSTEM_BASE+0x00B4)
#define REG_SYSTEM_DDRMASCADDR2MSB                                           (APB_SYSTEM_BASE+0x00B8)
#define REG_SYSTEM_DDRMASCADDR3MSB                                           (APB_SYSTEM_BASE+0x00BC)
#define REG_SYSTEM_DDRMASCADDR0                                              (APB_SYSTEM_BASE+0x00C0)
#define REG_SYSTEM_DDRMASCADDR1                                              (APB_SYSTEM_BASE+0x00C4)
#define REG_SYSTEM_DDRMASCADDR2                                              (APB_SYSTEM_BASE+0x00C8)
#define REG_SYSTEM_DDRMASCADDR3                                              (APB_SYSTEM_BASE+0x00CC)
#define REG_SYSTEM_EXTMASCADDR0                                              (APB_SYSTEM_BASE+0x00D0)
#define REG_SYSTEM_EXTMASCADDR1                                              (APB_SYSTEM_BASE+0x00D4)
#define REG_SYSTEM_EXTMASCADDR2                                              (APB_SYSTEM_BASE+0x00D8)
#define REG_SYSTEM_EXTMASCADDR3                                              (APB_SYSTEM_BASE+0x00DC)
#define REG_SYSTEM_RV0ASCADDR0                                               (APB_SYSTEM_BASE+0x00E0)
#define REG_SYSTEM_RV0ASCADDR1                                               (APB_SYSTEM_BASE+0x00E4)
#define REG_SYSTEM_RV0ASCADDR2                                               (APB_SYSTEM_BASE+0x00E8)
#define REG_SYSTEM_RV0ASCADDR3                                               (APB_SYSTEM_BASE+0x00EC)
#define REG_SYSTEM_RV0ASCADDR4                                               (APB_SYSTEM_BASE+0x00F0)
#define REG_SYSTEM_RV0ASCADDR5                                               (APB_SYSTEM_BASE+0x00F4)
#define REG_SYSTEM_RV0ASCADDR6                                               (APB_SYSTEM_BASE+0x00F8)
#define REG_SYSTEM_RV0ASCADDR7                                               (APB_SYSTEM_BASE+0x00FC)
#define REG_SYSTEM_RV1ASCADDR0                                               (APB_SYSTEM_BASE+0x0100)
#define REG_SYSTEM_RV1ASCADDR1                                               (APB_SYSTEM_BASE+0x0104)
#define REG_SYSTEM_RV1ASCADDR2                                               (APB_SYSTEM_BASE+0x0108)
#define REG_SYSTEM_RV1ASCADDR3                                               (APB_SYSTEM_BASE+0x010C)
#define REG_SYSTEM_SYSGP0                                                    (APB_SYSTEM_BASE+0x0110)
#define REG_SYSTEM_SYSGP1                                                    (APB_SYSTEM_BASE+0x0114)
#define REG_SYSTEM_SYSGP2                                                    (APB_SYSTEM_BASE+0x0118)
#define REG_SYSTEM_SYSGP3                                                    (APB_SYSTEM_BASE+0x011C)
#define REG_SYSTEM_SYSGP4                                                    (APB_SYSTEM_BASE+0x0120)
#define REG_SYSTEM_SYSGP5                                                    (APB_SYSTEM_BASE+0x0124)
#define REG_SYSTEM_SYSGP6                                                    (APB_SYSTEM_BASE+0x0128)
#define REG_SYSTEM_SYSGP7                                                    (APB_SYSTEM_BASE+0x012C)
#define REG_SYSTEM_SYSGP8                                                    (APB_SYSTEM_BASE+0x0130)
#define REG_SYSTEM_SYSGP9                                                    (APB_SYSTEM_BASE+0x0134)
#define REG_SYSTEM_SYSGP10                                                   (APB_SYSTEM_BASE+0x0138)
#define REG_SYSTEM_SYSGP11                                                   (APB_SYSTEM_BASE+0x013C)
#define REG_SYSTEM_APBTOUTM0ADDR                                             (APB_SYSTEM_BASE+0x0140)
#define REG_SYSTEM_APBTOUTM0WRITE                                            (APB_SYSTEM_BASE+0x0144)
#define REG_SYSTEM_APBTOUTM0PROT                                             (APB_SYSTEM_BASE+0x0148)
#define REG_SYSTEM_APBTOUTM0WDATA                                            (APB_SYSTEM_BASE+0x014C)
#define REG_SYSTEM_APBTOUTM1ADDR                                             (APB_SYSTEM_BASE+0x0150)
#define REG_SYSTEM_APBTOUTM1WRITE                                            (APB_SYSTEM_BASE+0x0154)
#define REG_SYSTEM_APBTOUTM1PROT                                             (APB_SYSTEM_BASE+0x0158)
#define REG_SYSTEM_APBTOUTM1WDATA                                            (APB_SYSTEM_BASE+0x015C)
#define REG_SYSTEM_APBTOUTM2ADDR                                             (APB_SYSTEM_BASE+0x0160)
#define REG_SYSTEM_APBTOUTM2WRITE                                            (APB_SYSTEM_BASE+0x0164)
#define REG_SYSTEM_APBTOUTM2PROT                                             (APB_SYSTEM_BASE+0x0168)
#define REG_SYSTEM_APBTOUTM2WDATA                                            (APB_SYSTEM_BASE+0x016C)
#define REG_SYSTEM_RVAXUSER                                                  (APB_SYSTEM_BASE+0x018C)
#define REG_SYSTEM_APBPSLVERR                                                (APB_SYSTEM_BASE+0x01BC)
#define REG_SYSTEM_APBM0PSLVERR                                              (APB_SYSTEM_BASE+0x01C0)
#define REG_SYSTEM_APBM1PSLVERR                                              (APB_SYSTEM_BASE+0x01C4)
#define REG_SYSTEM_APBM2PSLVERR                                              (APB_SYSTEM_BASE+0x01C8)

typedef union {
	UINT32 udata32;
	struct {						//0xF000F000 RO
	UINT32 version                          :32;	//31:0	//MCU Version
	};
}REG_SYSTEM_MCUVERSION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F060 RW
	UINT32 m0_tout_en                       :1;	//0 //M0 APB Time Out Enable
	UINT32 m1_tout_en                       :1;	//1 //M1 APB Time Out Enable
	UINT32 m2_tout_en                       :1;	//2 //M2 APB Time Out Enable
	UINT32 resvd                            :29; 
	};
}REG_SYSTEM_APBTOUTEN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F064 RW
	UINT32 tout_cnt                         :32;	//31:0	//APB Time Out Count Value
	};
}REG_SYSTEM_APBTOUTCNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F068 RW
	UINT32 m0_tout_slverr                   :1;	//0 //M0 APB Time Out slave error
	UINT32 m1_tout_slverr                   :1;	//1 //M1 APB Time Out slave error
	UINT32 m2_tout_slverr                   :1;	//2 //M2 APB Time Out slave error
	UINT32 resvd                            :29; 
	};
}REG_SYSTEM_APBTOUTSLVERR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F070 RW
	UINT32 m0_tout_intr_en                  :1;	//0 //M0 APB Time Out Interrupt Enable
	UINT32 m1_tout_intr_en                  :1;	//1 //M1 APB Time Out Interrupt Enable
	UINT32 m2_tout_intr_en                  :1;	//2 //M2 APB Time Out Interrupt Enable
	UINT32 resvd                            :29; 
	};
}REG_SYSTEM_APBTOUTINTREN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F074 RO
	UINT32 m0_tout_mis                      :1;	//0 //M0 APB Time Out Masked Interrupt Status
	UINT32 m1_tout_mis                      :1;	//1 //M1 APB Time Out Masked Interrupt Status
	UINT32 m2_tout_mis                      :1;	//2 //M2 APB Time Out Masked Interrupt Status
	UINT32 resvd                            :29; 
	};
}REG_SYSTEM_APBTOUTMIS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F078 RO
	UINT32 m0_tout_ris                      :1;	//0 //M0 APB Time Out Raw Interrupt Status
	UINT32 m1_tout_ris                      :1;	//1 //M1 APB Time Out Raw Interrupt Status
	UINT32 m2_tout_ris                      :1;	//2 //M2 APB Time Out Raw Interrupt Status
	UINT32 resvd                            :29; 
	};
}REG_SYSTEM_APBTOUTRIS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F07C RW
	UINT32 m0_tout_clr                      :1;	//0 //M0 APB Time Out Interrupt Clear
	UINT32 m1_tout_clr                      :1;	//1 //M1 APB Time Out Interrupt Clear
	UINT32 m2_tout_clr                      :1;	//2 //M2 APB Time Out Interrupt Clear
	UINT32 resvd                            :29; 
	};
}REG_SYSTEM_APBTOUTINTRCLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F080 RW
	UINT32 mcu_p0_flush_en                  :1;	//0 //MCU Port0 Flush Enable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_MCUP0FLUSHEN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F084 RW
	UINT32 mcu_p1_flush_en                  :1;	//0 //MCU Port1 Flush Enable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_MCUP1FLUSHEN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F088 RW
	UINT32 ddr_flush_en                     :1;	//0 //DDR Memory Port Flush Enable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_DDRMFLUSHEN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F090 RO
	UINT32 mcu_p0_flush_done                :1;	//0 //MCU Port0 Flush Done
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_MCUP0FLUSHDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F094 RO
	UINT32 mcu_p1_flush_done                :1;	//0 //MCU Port1 Flush Done
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_MCUP1FLUSHDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F098 RO
	UINT32 ddr_flush_done                   :1;	//0 //DDR Memory Port Flush Done
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_DDRMFLUSHDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0B0 RW
	UINT32 ddrm_asc_addr0_msb               :1;	//0 //DDRM MSB bits means 33th bit of ASC AXI output address for input range0 (32¡¯h0000_0000 ~ 32'h1FFF_FFF) of which default mapping is 33¡¯h0_0000_0000
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_DDRMASCADDR0MSB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0B4 RW
	UINT32 ddrm_asc_addr1_msb               :1;	//0 //DDRM MSB bits means 33th bit of ASC AXI output address for input range1 (32¡¯h2000_0000 ~ 32'h3FFF_FFF) of which default mapping is 33¡¯h0_8000_0000
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_DDRMASCADDR1MSB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0B8 RW
	UINT32 ddrm_asc_addr2_msb               :1;	//0 //DDRM MSB bits means 33th bit of ASC AXI output address for input range2 (32¡¯h4000_0000 ~ 32'h5FFF_FFF) of which default mapping is 33¡¯h1_0000_0000
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_DDRMASCADDR2MSB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0BC RW
	UINT32 ddrm_asc_addr3_msb               :1;	//0 //DDRM MSB bits means 33th bit of ASC AXI output address for input range3 (32¡¯h6000_0000 ~ 32'h7FFF_FFF) of which default mapping is 33¡¯h1_8000_0000
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_DDRMASCADDR3MSB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0C0 RW
	UINT32 ddrm_asc_addr0                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range0 (32¡¯h0000_0000 ~ 32'h1FFF_FFFF) of which default mapping is 33¡¯h0_0000_0000
	};
}REG_SYSTEM_DDRMASCADDR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0C4 RW
	UINT32 ddrm_asc_addr1                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range1 (32¡¯h2000_0000 ~ 32'h3FFF_FFFF) of which default mapping is 33¡¯h0_8000_0000
	};
}REG_SYSTEM_DDRMASCADDR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0C8 RW
	UINT32 ddrm_asc_addr2                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range2 (32¡¯h4000_0000 ~ 32'h5FFF_FFFF) of which default mapping is 33¡¯h1_0000_0000
	};
}REG_SYSTEM_DDRMASCADDR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0CC RW
	UINT32 ddrm_asc_addr3                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range3 (32¡¯h6000_0000 ~ 32'h7FFF_FFFF) of which default mapping is 33¡¯h1_8000_0000
	};
}REG_SYSTEM_DDRMASCADDR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0D0 RW
	UINT32 extm_asc_addr0                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range0 (20¡¯h0_0000 ~ 20'h3_FFFF) of which default mapping is 32¡¯hD000_0000(SPAD)
	};
}REG_SYSTEM_EXTMASCADDR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0D4 RW
	UINT32 extm_asc_addr1                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range1 (20¡¯h4_0000 ~ 20'h7_FFFF) of which default mapping is 32¡¯hE000_0000(Coreplex)
	};
}REG_SYSTEM_EXTMASCADDR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0D8 RW
	UINT32 extm_asc_addr2                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range2 (20¡¯h8_0000 ~ 20'hB_FFFF) of which default mapping is 32¡¯hE000_0000(Coreplex)
	};
}REG_SYSTEM_EXTMASCADDR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0DC RW
	UINT32 extm_asc_addr3                   :32;	//31:0	//This field indicates 32-bits of ASC AXI output address for input range3 (20¡¯hD_0000 ~ 20'hF_FFFF) of which default mapping is 32¡¯hF000_0000(PERI)
	};
}REG_SYSTEM_EXTMASCADDR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0E0 RW
	UINT32 rv_0_asc_addr0                   :32;	//31:0	//RV-0 ERAM (32¡¯h4000_0000) ASC register Default mapping is DDRM (32¡¯h0000_0000)
	};
}REG_SYSTEM_RV0ASCADDR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0E4 RW
	UINT32 rv_0_asc_addr1                   :32;	//31:0	//RV-0 ERAM (32¡¯h5000_0000) ASC register. Default mapping is DDRM (32¡¯h1000_0000)
	};
}REG_SYSTEM_RV0ASCADDR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0E8 RW
	UINT32 rv_0_asc_addr2                   :32;	//31:0	//RV-0 ERAM (32¡¯h6000_0000) ASC register. Default mapping is DDRM (32¡¯h2000_0000)
	};
}REG_SYSTEM_RV0ASCADDR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0EC RW
	UINT32 rv_0_asc_addr3                   :32;	//31:0	//RV-0 ERAM (32¡¯h7000_0000) ASC register. Default mapping is DDRM (32¡¯h3000_0000)
	};
}REG_SYSTEM_RV0ASCADDR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0F0 RW
	UINT32 rv_0_asc_addr4                   :32;	//31:0	//RV-0 ERAM (32¡¯h8000_0000) ASC register Default mapping is DDRM (32¡¯h4000_0000)
	};
}REG_SYSTEM_RV0ASCADDR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0F4 RW
	UINT32 rv_0_asc_addr5                   :32;	//31:0	//RV-0 ERAM (32¡¯h9000_0000) ASC register. Default mapping is DDRM (32¡¯h5000_0000)
	};
}REG_SYSTEM_RV0ASCADDR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0F8 RW
	UINT32 rv_0_asc_addr6                   :32;	//31:0	//RV-0 ERAM (32¡¯hA000_0000) ASC register. Default mapping is DDRM (32¡¯h6000_0000)
	};
}REG_SYSTEM_RV0ASCADDR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F0FC RW
	UINT32 rv_0_asc_addr7                   :32;	//31:0	//RV-0 ERAM (32¡¯hB000_0000) ASC register. Default mapping is SPAD (32¡¯hD000_0000)
	};
}REG_SYSTEM_RV0ASCADDR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F100 RW
	UINT32 rv_1_asc_addr0                   :32;	//31:0	//RV-0 EDevice (32¡¯hC000_0000) ASC register Default mapping is 32¡¯hC000_0000
	};
}REG_SYSTEM_RV1ASCADDR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F104 RW
	UINT32 rv_1_asc_addr1                   :32;	//31:0	//RV-0 EDevice (32¡¯hD000_0000) ASC register. Default mapping is 32¡¯hD000_0000(SPAD)
	};
}REG_SYSTEM_RV1ASCADDR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F108 RW
	UINT32 rv_1_asc_addr2                   :32;	//31:0	//RV-0 EDevice (32¡¯hE000_0000) ASC register. Default mapping is 32¡¯hE000_0000(Coreplex)
	};
}REG_SYSTEM_RV1ASCADDR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F10C RW
	UINT32 rv_1_asc_addr3                   :32;	//31:0	//RV-0 EDevice (32¡¯hF000_0000) ASC register. Default mapping is 32¡¯hF000_0000(PeripheralAPBRegion)
	};
}REG_SYSTEM_RV1ASCADDR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F110 RW
	UINT32 sys_gp0                          :32;	//31:0	//System General Purpose 0 Register
	};
}REG_SYSTEM_SYSGP0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F114 RW
	UINT32 sys_gp1                          :32;	//31:0	//System General Purpose 1 Register
	};
}REG_SYSTEM_SYSGP1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F118 RW
	UINT32 sys_gp2                          :32;	//31:0	//System General Purpose 2 Register
	};
}REG_SYSTEM_SYSGP2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F11C RW
	UINT32 sys_gp3                          :32;	//31:0	//System General Purpose 3 Register
	};
}REG_SYSTEM_SYSGP3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F120 RW
	UINT32 sys_gp4                          :32;	//31:0	//System General Purpose 4 Register
	};
}REG_SYSTEM_SYSGP4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F124 RW
	UINT32 sys_gp5                          :32;	//31:0	//System General Purpose 5 Register
	};
}REG_SYSTEM_SYSGP5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F128 RW
	UINT32 sys_gp6                          :32;	//31:0	//System General Purpose 6 Register
	};
}REG_SYSTEM_SYSGP6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F12C RW
	UINT32 sys_gp7                          :32;	//31:0	//System General Purpose 7 Register
	};
}REG_SYSTEM_SYSGP7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F130 RW
	UINT32 sys_gp8                          :32;	//31:0	//System General Purpose 8 Register
	};
}REG_SYSTEM_SYSGP8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F134 RW
	UINT32 sys_gp9                          :32;	//31:0	//System General Purpose 9 Register
	};
}REG_SYSTEM_SYSGP9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F138 RW
	UINT32 sys_gp10                         :32;	//31:0	//System General Purpose 10 Register
	};
}REG_SYSTEM_SYSGP10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F13C RW
	UINT32 sys_gp11                         :32;	//31:0	//System General Purpose 11 Register
	};
}REG_SYSTEM_SYSGP11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F140 RO
	UINT32 m0_tout_addr                     :32;	//31:0	//M0 APB Time-Out Address
	};
}REG_SYSTEM_APBTOUTM0ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F144 RO
	UINT32 m0_tout_write                    :1;	//0 //M0 APB Time-Out Write (1'b0: Read, 1'b1: Write)
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBTOUTM0WRITE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F148 RO
	UINT32 m0_tout_prot                     :1;	//0 //M0 APB Time-Out Protection (1'b0: Secure, 1'b1: Non-Secure)
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBTOUTM0PROT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F14C RO
	UINT32 m0_tout_wdata                    :32;	//31:0	//M0 APB Time-Out Write Data
	};
}REG_SYSTEM_APBTOUTM0WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F150 RO
	UINT32 m1_tout_addr                     :32;	//31:0	//M1 APB Time-Out Address
	};
}REG_SYSTEM_APBTOUTM1ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F154 RO
	UINT32 m1_tout_write                    :1;	//0 //M1 APB Time-Out Write (1'b0: Read, 1'b1: Write)
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBTOUTM1WRITE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F158 RO
	UINT32 m1_tout_prot                     :1;	//0 //M1 APB Time-Out Protection (1'b0: Secure, 1'b1: Non-Secure)
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBTOUTM1PROT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F15C RO
	UINT32 m1_tout_wdata                    :32;	//31:0	//M1 APB Time-Out Write Data
	};
}REG_SYSTEM_APBTOUTM1WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F160 RO
	UINT32 m2_tout_addr                     :32;	//31:0	//M2 APB Time-Out Address
	};
}REG_SYSTEM_APBTOUTM2ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F164 RO
	UINT32 m2_tout_write                    :1;	//0 //M2 APB Time-Out Write (1'b0: Read, 1'b1: Write)
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBTOUTM2WRITE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F168 RO
	UINT32 m2_tout_prot                     :1;	//0 //M2 APB Time-Out Protection (1'b0: Secure, 1'b1: Non-Secure)
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBTOUTM2PROT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F16C RO
	UINT32 m2_tout_wdata                    :32;	//31:0	//M2 APB Time-Out Write Data
	};
}REG_SYSTEM_APBTOUTM2WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F18C RW
	UINT32 rv_ar_user                       :4;	//3:0	//RV ARUser Field
	UINT32 resvd0                           :12; 
	UINT32 rv_aw_user                       :4;	//19:16	//RV AWUser Field
	UINT32 resvd1                           :12; 
	};
}REG_SYSTEM_RVAXUSER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F1BC RW
	UINT32 apb_pslverr_dis                  :1;	//0 //APB Slave Error Disable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBPSLVERR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F1C0 RW
	UINT32 m0_pslverr_dis                   :1;	//0 //M0 APB Slave Error Disable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBM0PSLVERR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F1C4 RW
	UINT32 m1_pslverr_dis                   :1;	//0 //M1 APB Slave Error Disable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBM1PSLVERR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000F1C8 RW
	UINT32 m2_pslverr_dis                   :1;	//0 //M2 APB Slave Error Disable
	UINT32 resvd                            :31; 
	};
}REG_SYSTEM_APBM2PSLVERR_T;

typedef struct {
	REG_SYSTEM_MCUVERSION_T                                  mcuversion;	//0xF000F000
	UINT32                                                    reserved0;	//0xF000F004
	UINT32                                                    reserved1;	//0xF000F008
	UINT32                                                    reserved2;	//0xF000F00C
	UINT32                                                    reserved3;	//0xF000F010
	UINT32                                                    reserved4;	//0xF000F014
	UINT32                                                    reserved5;	//0xF000F018
	UINT32                                                    reserved6;	//0xF000F01C
	UINT32                                                    reserved7;	//0xF000F020
	UINT32                                                    reserved8;	//0xF000F024
	UINT32                                                    reserved9;	//0xF000F028
	UINT32                                                   reserved10;	//0xF000F02C
	UINT32                                                   reserved11;	//0xF000F030
	UINT32                                                   reserved12;	//0xF000F034
	UINT32                                                   reserved13;	//0xF000F038
	UINT32                                                   reserved14;	//0xF000F03C
	UINT32                                                   reserved15;	//0xF000F040
	UINT32                                                   reserved16;	//0xF000F044
	UINT32                                                   reserved17;	//0xF000F048
	UINT32                                                   reserved18;	//0xF000F04C
	UINT32                                                   reserved19;	//0xF000F050
	UINT32                                                   reserved20;	//0xF000F054
	UINT32                                                   reserved21;	//0xF000F058
	UINT32                                                   reserved22;	//0xF000F05C
	REG_SYSTEM_APBTOUTEN_T                                    apbtouten;	//0xF000F060
	REG_SYSTEM_APBTOUTCNT_T                                  apbtoutcnt;	//0xF000F064
	REG_SYSTEM_APBTOUTSLVERR_T                            apbtoutslverr;	//0xF000F068
	UINT32                                                   reserved23;	//0xF000F06C
	REG_SYSTEM_APBTOUTINTREN_T                            apbtoutintren;	//0xF000F070
	REG_SYSTEM_APBTOUTMIS_T                                  apbtoutmis;	//0xF000F074
	REG_SYSTEM_APBTOUTRIS_T                                  apbtoutris;	//0xF000F078
	REG_SYSTEM_APBTOUTINTRCLR_T                          apbtoutintrclr;	//0xF000F07C
	REG_SYSTEM_MCUP0FLUSHEN_T                              mcup0flushen;	//0xF000F080
	REG_SYSTEM_MCUP1FLUSHEN_T                              mcup1flushen;	//0xF000F084
	REG_SYSTEM_DDRMFLUSHEN_T                                ddrmflushen;	//0xF000F088
	UINT32                                                   reserved24;	//0xF000F08C
	REG_SYSTEM_MCUP0FLUSHDONE_T                          mcup0flushdone;	//0xF000F090
	REG_SYSTEM_MCUP1FLUSHDONE_T                          mcup1flushdone;	//0xF000F094
	REG_SYSTEM_DDRMFLUSHDONE_T                            ddrmflushdone;	//0xF000F098
	UINT32                                                   reserved25;	//0xF000F09C
	UINT32                                                   reserved26;	//0xF000F0A0
	UINT32                                                   reserved27;	//0xF000F0A4
	UINT32                                                   reserved28;	//0xF000F0A8
	UINT32                                                   reserved29;	//0xF000F0AC
	REG_SYSTEM_DDRMASCADDR0MSB_T                        ddrmascaddr0msb;	//0xF000F0B0
	REG_SYSTEM_DDRMASCADDR1MSB_T                        ddrmascaddr1msb;	//0xF000F0B4
	REG_SYSTEM_DDRMASCADDR2MSB_T                        ddrmascaddr2msb;	//0xF000F0B8
	REG_SYSTEM_DDRMASCADDR3MSB_T                        ddrmascaddr3msb;	//0xF000F0BC
	REG_SYSTEM_DDRMASCADDR0_T                              ddrmascaddr0;	//0xF000F0C0
	REG_SYSTEM_DDRMASCADDR1_T                              ddrmascaddr1;	//0xF000F0C4
	REG_SYSTEM_DDRMASCADDR2_T                              ddrmascaddr2;	//0xF000F0C8
	REG_SYSTEM_DDRMASCADDR3_T                              ddrmascaddr3;	//0xF000F0CC
	REG_SYSTEM_EXTMASCADDR0_T                              extmascaddr0;	//0xF000F0D0
	REG_SYSTEM_EXTMASCADDR1_T                              extmascaddr1;	//0xF000F0D4
	REG_SYSTEM_EXTMASCADDR2_T                              extmascaddr2;	//0xF000F0D8
	REG_SYSTEM_EXTMASCADDR3_T                              extmascaddr3;	//0xF000F0DC
	REG_SYSTEM_RV0ASCADDR0_T                                rv0ascaddr0;	//0xF000F0E0
	REG_SYSTEM_RV0ASCADDR1_T                                rv0ascaddr1;	//0xF000F0E4
	REG_SYSTEM_RV0ASCADDR2_T                                rv0ascaddr2;	//0xF000F0E8
	REG_SYSTEM_RV0ASCADDR3_T                                rv0ascaddr3;	//0xF000F0EC
	REG_SYSTEM_RV0ASCADDR4_T                                rv0ascaddr4;	//0xF000F0F0
	REG_SYSTEM_RV0ASCADDR5_T                                rv0ascaddr5;	//0xF000F0F4
	REG_SYSTEM_RV0ASCADDR6_T                                rv0ascaddr6;	//0xF000F0F8
	REG_SYSTEM_RV0ASCADDR7_T                                rv0ascaddr7;	//0xF000F0FC
	REG_SYSTEM_RV1ASCADDR0_T                                rv1ascaddr0;	//0xF000F100
	REG_SYSTEM_RV1ASCADDR1_T                                rv1ascaddr1;	//0xF000F104
	REG_SYSTEM_RV1ASCADDR2_T                                rv1ascaddr2;	//0xF000F108
	REG_SYSTEM_RV1ASCADDR3_T                                rv1ascaddr3;	//0xF000F10C
	REG_SYSTEM_SYSGP0_T                                          sysgp0;	//0xF000F110
	REG_SYSTEM_SYSGP1_T                                          sysgp1;	//0xF000F114
	REG_SYSTEM_SYSGP2_T                                          sysgp2;	//0xF000F118
	REG_SYSTEM_SYSGP3_T                                          sysgp3;	//0xF000F11C
	REG_SYSTEM_SYSGP4_T                                          sysgp4;	//0xF000F120
	REG_SYSTEM_SYSGP5_T                                          sysgp5;	//0xF000F124
	REG_SYSTEM_SYSGP6_T                                          sysgp6;	//0xF000F128
	REG_SYSTEM_SYSGP7_T                                          sysgp7;	//0xF000F12C
	REG_SYSTEM_SYSGP8_T                                          sysgp8;	//0xF000F130
	REG_SYSTEM_SYSGP9_T                                          sysgp9;	//0xF000F134
	REG_SYSTEM_SYSGP10_T                                        sysgp10;	//0xF000F138
	REG_SYSTEM_SYSGP11_T                                        sysgp11;	//0xF000F13C
	REG_SYSTEM_APBTOUTM0ADDR_T                            apbtoutm0addr;	//0xF000F140
	REG_SYSTEM_APBTOUTM0WRITE_T                          apbtoutm0write;	//0xF000F144
	REG_SYSTEM_APBTOUTM0PROT_T                            apbtoutm0prot;	//0xF000F148
	REG_SYSTEM_APBTOUTM0WDATA_T                          apbtoutm0wdata;	//0xF000F14C
	REG_SYSTEM_APBTOUTM1ADDR_T                            apbtoutm1addr;	//0xF000F150
	REG_SYSTEM_APBTOUTM1WRITE_T                          apbtoutm1write;	//0xF000F154
	REG_SYSTEM_APBTOUTM1PROT_T                            apbtoutm1prot;	//0xF000F158
	REG_SYSTEM_APBTOUTM1WDATA_T                          apbtoutm1wdata;	//0xF000F15C
	REG_SYSTEM_APBTOUTM2ADDR_T                            apbtoutm2addr;	//0xF000F160
	REG_SYSTEM_APBTOUTM2WRITE_T                          apbtoutm2write;	//0xF000F164
	REG_SYSTEM_APBTOUTM2PROT_T                            apbtoutm2prot;	//0xF000F168
	REG_SYSTEM_APBTOUTM2WDATA_T                          apbtoutm2wdata;	//0xF000F16C
	UINT32                                                   reserved30;	//0xF000F170
	UINT32                                                   reserved31;	//0xF000F174
	UINT32                                                   reserved32;	//0xF000F178
	UINT32                                                   reserved33;	//0xF000F17C
	UINT32                                                   reserved34;	//0xF000F180
	UINT32                                                   reserved35;	//0xF000F184
	UINT32                                                   reserved36;	//0xF000F188
	REG_SYSTEM_RVAXUSER_T                                      rvaxuser;	//0xF000F18C
	UINT32                                                   reserved37;	//0xF000F190
	UINT32                                                   reserved38;	//0xF000F194
	UINT32                                                   reserved39;	//0xF000F198
	UINT32                                                   reserved40;	//0xF000F19C
	UINT32                                                   reserved41;	//0xF000F1A0
	UINT32                                                   reserved42;	//0xF000F1A4
	UINT32                                                   reserved43;	//0xF000F1A8
	UINT32                                                   reserved44;	//0xF000F1AC
	UINT32                                                   reserved45;	//0xF000F1B0
	UINT32                                                   reserved46;	//0xF000F1B4
	UINT32                                                   reserved47;	//0xF000F1B8
	REG_SYSTEM_APBPSLVERR_T                                  apbpslverr;	//0xF000F1BC
	REG_SYSTEM_APBM0PSLVERR_T                              apbm0pslverr;	//0xF000F1C0
	REG_SYSTEM_APBM1PSLVERR_T                              apbm1pslverr;	//0xF000F1C4
	REG_SYSTEM_APBM2PSLVERR_T                              apbm2pslverr;	//0xF000F1C8
}REG_SYSTEM_T;

extern volatile REG_SYSTEM_T*                      gpREG_SYSTEM;
   
#endif
