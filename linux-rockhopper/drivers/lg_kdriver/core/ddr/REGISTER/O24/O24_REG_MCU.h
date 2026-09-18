#ifndef _REG_MCU_h
#define _REG_MCU_h
//Header File for MCU in \O24\O24_DRAM_MCU_Register_Manual.xls

#define REG_MCU_RUNSTALL                                                        (APB_MCU_BASE+0x0000)
#define REG_MCU_STATVECTORSEL                                                   (APB_MCU_BASE+0x0004)
#define REG_MCU_IPCI2EINTEN                                                     (APB_MCU_BASE+0x00E0)
#define REG_MCU_IPCI2EINTSTS                                                    (APB_MCU_BASE+0x00E4)
#define REG_MCU_IPCI2EINTRAWSTS                                                 (APB_MCU_BASE+0x00E8)
#define REG_MCU_IPCI2EINTCLR                                                    (APB_MCU_BASE+0x00EC)
#define REG_MCU_IPCE2IINTEN                                                     (APB_MCU_BASE+0x00F0)
#define REG_MCU_IPCE2IINTSTS                                                    (APB_MCU_BASE+0x00F4)
#define REG_MCU_IPCE2IINTRAWSTS                                                 (APB_MCU_BASE+0x00F8)
#define REG_MCU_IPCE2IINTCLR                                                    (APB_MCU_BASE+0x00FC)
#define REG_MCU_IPCREG0                                                         (APB_MCU_BASE+0x0100)
#define REG_MCU_IPCREG1                                                         (APB_MCU_BASE+0x0104)
#define REG_MCU_IPCREG2                                                         (APB_MCU_BASE+0x0108)
#define REG_MCU_IPCREG3                                                         (APB_MCU_BASE+0x010C)
#define REG_MCU_IPCREG4                                                         (APB_MCU_BASE+0x0110)
#define REG_MCU_IPCREG5                                                         (APB_MCU_BASE+0x0114)
#define REG_MCU_IPCREG6                                                         (APB_MCU_BASE+0x0118)
#define REG_MCU_IPCREG7                                                         (APB_MCU_BASE+0x011C)
#define REG_MCU_IPCREG8                                                         (APB_MCU_BASE+0x0120)
#define REG_MCU_IPCREG9                                                         (APB_MCU_BASE+0x0124)
#define REG_MCU_IPCREG10                                                        (APB_MCU_BASE+0x0128)
#define REG_MCU_IPCREG11                                                        (APB_MCU_BASE+0x012C)
#define REG_MCU_IPCREG12                                                        (APB_MCU_BASE+0x0130)
#define REG_MCU_IPCREG13                                                        (APB_MCU_BASE+0x0134)
#define REG_MCU_IPCREG14                                                        (APB_MCU_BASE+0x0138)
#define REG_MCU_IPCREG15                                                        (APB_MCU_BASE+0x013C)
#define REG_MCU_IPCREG16                                                        (APB_MCU_BASE+0x0140)
#define REG_MCU_IPCREG17                                                        (APB_MCU_BASE+0x0144)
#define REG_MCU_IPCREG18                                                        (APB_MCU_BASE+0x0148)
#define REG_MCU_IPCREG19                                                        (APB_MCU_BASE+0x014C)
#define REG_MCU_IPCREG20                                                        (APB_MCU_BASE+0x0150)
#define REG_MCU_IPCREG21                                                        (APB_MCU_BASE+0x0154)
#define REG_MCU_IPCREG22                                                        (APB_MCU_BASE+0x0158)
#define REG_MCU_IPCREG23                                                        (APB_MCU_BASE+0x015C)
#define REG_MCU_IPCREG24                                                        (APB_MCU_BASE+0x0160)
#define REG_MCU_IPCREG25                                                        (APB_MCU_BASE+0x0164)
#define REG_MCU_IPCREG26                                                        (APB_MCU_BASE+0x0168)
#define REG_MCU_IPCREG27                                                        (APB_MCU_BASE+0x016C)
#define REG_MCU_IPCREG28                                                        (APB_MCU_BASE+0x0170)
#define REG_MCU_IPCREG29                                                        (APB_MCU_BASE+0x0174)
#define REG_MCU_IPCREG30                                                        (APB_MCU_BASE+0x0178)
#define REG_MCU_IPCREG31                                                        (APB_MCU_BASE+0x017C)

typedef union {
	UINT32 udata32;
	struct {						//0xF000E000 RW
	UINT32 run_stall                        :1;	//0 //MCU RunStall Register. . This field¡¯s default value is 1¡¯b1 meaning that MCU is stalled after power-on reset. So, in order to let MCU run, this RunStall register should be set to 1¡¯b0 after Firmware Download.
	UINT32 resvd                            :31; 
	};
}REG_MCU_RUNSTALL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E004 RW
	UINT32 stat_vector                      :32;	//31:0	//MCU Reset Vector. This field indicates where MCU fetches instructions from after stall is released. If it¡¯s value is 0x4000_0000, It fetches instructions from DDR memory or SPAD according to the address mapped by MCU20ASCAddr0 SYSTEM register.
	};
}REG_MCU_STATVECTORSEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0E0 RW
	UINT32 ipc_i2e_int0_en                  :1;	//0 //IPC I2E Interrupt 0 Enable
	UINT32 ipc_i2e_int1_en                  :1;	//1 //IPC I2E Interrupt 1 Enable
	UINT32 ipc_i2e_int2_en                  :1;	//2 //IPC I2E Interrupt 2 Enable
	UINT32 ipc_i2e_int3_en                  :1;	//3 //IPC I2E Interrupt 3 Enable
	UINT32 ipc_i2e_int4_en                  :1;	//4 //IPC I2E Interrupt 4 Enable
	UINT32 ipc_i2e_int5_en                  :1;	//5 //IPC I2E Interrupt 5 Enable
	UINT32 ipc_i2e_int6_en                  :1;	//6 //IPC I2E Interrupt 6 Enable
	UINT32 ipc_i2e_int7_en                  :1;	//7 //IPC I2E Interrupt 7 Enable
	UINT32 ipc_i2e_int8_en                  :1;	//8 //IPC I2E Interrupt 8 Enable
	UINT32 ipc_i2e_int9_en                  :1;	//9 //IPC I2E Interrupt 9 Enable
	UINT32 ipc_i2e_int10_en                 :1;	//10 //IPC I2E Interrupt 10 Enable
	UINT32 ipc_i2e_int11_en                 :1;	//11 //IPC I2E Interrupt 11 Enable
	UINT32 ipc_i2e_int12_en                 :1;	//12 //IPC I2E Interrupt 12 Enable
	UINT32 ipc_i2e_int13_en                 :1;	//13 //IPC I2E Interrupt 13 Enable
	UINT32 ipc_i2e_int14_en                 :1;	//14 //IPC I2E Interrupt 14 Enable
	UINT32 ipc_i2e_int15_en                 :1;	//15 //IPC I2E Interrupt 15 Enable
	UINT32 ipc_i2e_int16_en                 :1;	//16 //IPC I2E Interrupt 16 Enable
	UINT32 ipc_i2e_int17_en                 :1;	//17 //IPC I2E Interrupt 17 Enable
	UINT32 ipc_i2e_int18_en                 :1;	//18 //IPC I2E Interrupt 18 Enable
	UINT32 ipc_i2e_int19_en                 :1;	//19 //IPC I2E Interrupt 19 Enable
	UINT32 ipc_i2e_int20_en                 :1;	//20 //IPC I2E Interrupt 20 Enable
	UINT32 ipc_i2e_int21_en                 :1;	//21 //IPC I2E Interrupt 21 Enable
	UINT32 ipc_i2e_int22_en                 :1;	//22 //IPC I2E Interrupt 22 Enable
	UINT32 ipc_i2e_int23_en                 :1;	//23 //IPC I2E Interrupt 23 Enable
	UINT32 ipc_i2e_int24_en                 :1;	//24 //IPC I2E Interrupt 24 Enable
	UINT32 ipc_i2e_int25_en                 :1;	//25 //IPC I2E Interrupt 25 Enable
	UINT32 ipc_i2e_int26_en                 :1;	//26 //IPC I2E Interrupt 26 Enable
	UINT32 ipc_i2e_int27_en                 :1;	//27 //IPC I2E Interrupt 27 Enable
	UINT32 ipc_i2e_int28_en                 :1;	//28 //IPC I2E Interrupt 28 Enable
	UINT32 ipc_i2e_int29_en                 :1;	//29 //IPC I2E Interrupt 29 Enable
	UINT32 ipc_i2e_int30_en                 :1;	//30 //IPC I2E Interrupt 30 Enable
	UINT32 ipc_i2e_int31_en                 :1;	//31 //IPC I2E Interrupt 31 Enable
	};
}REG_MCU_IPCI2EINTEN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0E4 RO
	UINT32 ipc_i2e_int0_sts                 :1;	//0 //IPC I2E Interrupt 0 Status
	UINT32 ipc_i2e_int1_sts                 :1;	//1 //IPC I2E Interrupt 1 Status
	UINT32 ipc_i2e_int2_sts                 :1;	//2 //IPC I2E Interrupt 2 Status
	UINT32 ipc_i2e_int3_sts                 :1;	//3 //IPC I2E Interrupt 3 Status
	UINT32 ipc_i2e_int4_sts                 :1;	//4 //IPC I2E Interrupt 4 Status
	UINT32 ipc_i2e_int5_sts                 :1;	//5 //IPC I2E Interrupt 5 Status
	UINT32 ipc_i2e_int6_sts                 :1;	//6 //IPC I2E Interrupt 6 Status
	UINT32 ipc_i2e_int7_sts                 :1;	//7 //IPC I2E Interrupt 7 Status
	UINT32 ipc_i2e_int8_sts                 :1;	//8 //IPC I2E Interrupt 8 Status
	UINT32 ipc_i2e_int9_sts                 :1;	//9 //IPC I2E Interrupt 9 Status
	UINT32 ipc_i2e_int10_sts                :1;	//10 //IPC I2E Interrupt 10 Status
	UINT32 ipc_i2e_int11_sts                :1;	//11 //IPC I2E Interrupt 11 Status
	UINT32 ipc_i2e_int12_sts                :1;	//12 //IPC I2E Interrupt 12 Status
	UINT32 ipc_i2e_int13_sts                :1;	//13 //IPC I2E Interrupt 13 Status
	UINT32 ipc_i2e_int14_sts                :1;	//14 //IPC I2E Interrupt 14 Status
	UINT32 ipc_i2e_int15_sts                :1;	//15 //IPC I2E Interrupt 15 Status
	UINT32 ipc_i2e_int16_sts                :1;	//16 //IPC I2E Interrupt 16 Status
	UINT32 ipc_i2e_int17_sts                :1;	//17 //IPC I2E Interrupt 17 Status
	UINT32 ipc_i2e_int18_sts                :1;	//18 //IPC I2E Interrupt 18 Status
	UINT32 ipc_i2e_int19_sts                :1;	//19 //IPC I2E Interrupt 19 Status
	UINT32 ipc_i2e_int20_sts                :1;	//20 //IPC I2E Interrupt 20 Status
	UINT32 ipc_i2e_int21_sts                :1;	//21 //IPC I2E Interrupt 21 Status
	UINT32 ipc_i2e_int22_sts                :1;	//22 //IPC I2E Interrupt 22 Status
	UINT32 ipc_i2e_int23_sts                :1;	//23 //IPC I2E Interrupt 23 Status
	UINT32 ipc_i2e_int24_sts                :1;	//24 //IPC I2E Interrupt 24 Status
	UINT32 ipc_i2e_int25_sts                :1;	//25 //IPC I2E Interrupt 25 Status
	UINT32 ipc_i2e_int26_sts                :1;	//26 //IPC I2E Interrupt 26 Status
	UINT32 ipc_i2e_int27_sts                :1;	//27 //IPC I2E Interrupt 27 Status
	UINT32 ipc_i2e_int28_sts                :1;	//28 //IPC I2E Interrupt 28 Status
	UINT32 ipc_i2e_int29_sts                :1;	//29 //IPC I2E Interrupt 29 Status
	UINT32 ipc_i2e_int30_sts                :1;	//30 //IPC I2E Interrupt 30 Status
	UINT32 ipc_i2e_int31_sts                :1;	//31 //IPC I2E Interrupt 31 Status
	};
}REG_MCU_IPCI2EINTSTS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0E8 RO
	UINT32 ipc_i2e_int0_raw_sts             :1;	//0 //IPC I2E Interrupt 0 Raw Status
	UINT32 ipc_i2e_int1_raw_sts             :1;	//1 //IPC I2E Interrupt 1 Raw Status
	UINT32 ipc_i2e_int2_raw_sts             :1;	//2 //IPC I2E Interrupt 2 Raw Status
	UINT32 ipc_i2e_int3_raw_sts             :1;	//3 //IPC I2E Interrupt 3 Raw Status
	UINT32 ipc_i2e_int4_raw_sts             :1;	//4 //IPC I2E Interrupt 4 Raw Status
	UINT32 ipc_i2e_int5_raw_sts             :1;	//5 //IPC I2E Interrupt 5 Raw Status
	UINT32 ipc_i2e_int6_raw_sts             :1;	//6 //IPC I2E Interrupt 6 Raw Status
	UINT32 ipc_i2e_int7_raw_sts             :1;	//7 //IPC I2E Interrupt 7 Raw Status
	UINT32 ipc_i2e_int8_raw_sts             :1;	//8 //IPC I2E Interrupt 8 Raw Status
	UINT32 ipc_i2e_int9_raw_sts             :1;	//9 //IPC I2E Interrupt 9 Raw Status
	UINT32 ipc_i2e_int10_raw_sts            :1;	//10 //IPC I2E Interrupt 10 Raw Status
	UINT32 ipc_i2e_int11_raw_sts            :1;	//11 //IPC I2E Interrupt 11 Raw Status
	UINT32 ipc_i2e_int12_raw_sts            :1;	//12 //IPC I2E Interrupt 12 Raw Status
	UINT32 ipc_i2e_int13_raw_sts            :1;	//13 //IPC I2E Interrupt 13 Raw Status
	UINT32 ipc_i2e_int14_raw_sts            :1;	//14 //IPC I2E Interrupt 14 Raw Status
	UINT32 ipc_i2e_int15_raw_sts            :1;	//15 //IPC I2E Interrupt 15 Raw Status
	UINT32 ipc_i2e_int16_raw_sts            :1;	//16 //IPC I2E Interrupt 16 Raw Status
	UINT32 ipc_i2e_int17_raw_sts            :1;	//17 //IPC I2E Interrupt 17 Raw Status
	UINT32 ipc_i2e_int18_raw_sts            :1;	//18 //IPC I2E Interrupt 18 Raw Status
	UINT32 ipc_i2e_int19_raw_sts            :1;	//19 //IPC I2E Interrupt 19 Raw Status
	UINT32 ipc_i2e_int20_raw_sts            :1;	//20 //IPC I2E Interrupt 20 Raw Status
	UINT32 ipc_i2e_int21_raw_sts            :1;	//21 //IPC I2E Interrupt 21 Raw Status
	UINT32 ipc_i2e_int22_raw_sts            :1;	//22 //IPC I2E Interrupt 22 Raw Status
	UINT32 ipc_i2e_int23_raw_sts            :1;	//23 //IPC I2E Interrupt 23 Raw Status
	UINT32 ipc_i2e_int24_raw_sts            :1;	//24 //IPC I2E Interrupt 24 Raw Status
	UINT32 ipc_i2e_int25_raw_sts            :1;	//25 //IPC I2E Interrupt 25 Raw Status
	UINT32 ipc_i2e_int26_raw_sts            :1;	//26 //IPC I2E Interrupt 26 Raw Status
	UINT32 ipc_i2e_int27_raw_sts            :1;	//27 //IPC I2E Interrupt 27 Raw Status
	UINT32 ipc_i2e_int28_raw_sts            :1;	//28 //IPC I2E Interrupt 28 Raw Status
	UINT32 ipc_i2e_int29_raw_sts            :1;	//29 //IPC I2E Interrupt 29 Raw Status
	UINT32 ipc_i2e_int30_raw_sts            :1;	//30 //IPC I2E Interrupt 30 Raw Status
	UINT32 ipc_i2e_int31_raw_sts            :1;	//31 //IPC I2E Interrupt 31 Raw Status
	};
}REG_MCU_IPCI2EINTRAWSTS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0EC RW
	UINT32 ipc_i2e_int0_clr                 :1;	//0 //IPC I2E Interrupt 0 Clear
	UINT32 ipc_i2e_int1_clr                 :1;	//1 //IPC I2E Interrupt 1 Clear
	UINT32 ipc_i2e_int2_clr                 :1;	//2 //IPC I2E Interrupt 2 Clear
	UINT32 ipc_i2e_int3_clr                 :1;	//3 //IPC I2E Interrupt 3 Clear
	UINT32 ipc_i2e_int4_clr                 :1;	//4 //IPC I2E Interrupt 4 Clear
	UINT32 ipc_i2e_int5_clr                 :1;	//5 //IPC I2E Interrupt 5 Clear
	UINT32 ipc_i2e_int6_clr                 :1;	//6 //IPC I2E Interrupt 6 Clear
	UINT32 ipc_i2e_int7_clr                 :1;	//7 //IPC I2E Interrupt 7 Clear
	UINT32 ipc_i2e_int8_clr                 :1;	//8 //IPC I2E Interrupt 8 Clear
	UINT32 ipc_i2e_int9_clr                 :1;	//9 //IPC I2E Interrupt 9 Clear
	UINT32 ipc_i2e_int10_clr                :1;	//10 //IPC I2E Interrupt 10 Clear
	UINT32 ipc_i2e_int11_clr                :1;	//11 //IPC I2E Interrupt 11 Clear
	UINT32 ipc_i2e_int12_clr                :1;	//12 //IPC I2E Interrupt 12 Clear
	UINT32 ipc_i2e_int13_clr                :1;	//13 //IPC I2E Interrupt 13 Clear
	UINT32 ipc_i2e_int14_clr                :1;	//14 //IPC I2E Interrupt 14 Clear
	UINT32 ipc_i2e_int15_clr                :1;	//15 //IPC I2E Interrupt 15 Clear
	UINT32 ipc_i2e_int16_clr                :1;	//16 //IPC I2E Interrupt 16 Clear
	UINT32 ipc_i2e_int17_clr                :1;	//17 //IPC I2E Interrupt 17 Clear
	UINT32 ipc_i2e_int18_clr                :1;	//18 //IPC I2E Interrupt 18 Clear
	UINT32 ipc_i2e_int19_clr                :1;	//19 //IPC I2E Interrupt 19 Clear
	UINT32 ipc_i2e_int20_clr                :1;	//20 //IPC I2E Interrupt 20 Clear
	UINT32 ipc_i2e_int21_clr                :1;	//21 //IPC I2E Interrupt 21 Clear
	UINT32 ipc_i2e_int22_clr                :1;	//22 //IPC I2E Interrupt 22 Clear
	UINT32 ipc_i2e_int23_clr                :1;	//23 //IPC I2E Interrupt 23 Clear
	UINT32 ipc_i2e_int24_clr                :1;	//24 //IPC I2E Interrupt 24 Clear
	UINT32 ipc_i2e_int25_clr                :1;	//25 //IPC I2E Interrupt 25 Clear
	UINT32 ipc_i2e_int26_clr                :1;	//26 //IPC I2E Interrupt 26 Clear
	UINT32 ipc_i2e_int27_clr                :1;	//27 //IPC I2E Interrupt 27 Clear
	UINT32 ipc_i2e_int28_clr                :1;	//28 //IPC I2E Interrupt 28 Clear
	UINT32 ipc_i2e_int29_clr                :1;	//29 //IPC I2E Interrupt 29 Clear
	UINT32 ipc_i2e_int30_clr                :1;	//30 //IPC I2E Interrupt 30 Clear
	UINT32 ipc_i2e_int31_clr                :1;	//31 //IPC I2E Interrupt 31 Clear
	};
}REG_MCU_IPCI2EINTCLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0F0 RW
	UINT32 ipc_int0_en                      :1;	//0 //IPC Interrupt 0 Enable
	UINT32 ipc_int1_en                      :1;	//1 //IPC Interrupt 1 Enable
	UINT32 ipc_int2_en                      :1;	//2 //IPC Interrupt 2 Enable
	UINT32 ipc_int3_en                      :1;	//3 //IPC Interrupt 3 Enable
	UINT32 ipc_int4_en                      :1;	//4 //IPC Interrupt 4 Enable
	UINT32 ipc_int5_en                      :1;	//5 //IPC Interrupt 5 Enable
	UINT32 ipc_int6_en                      :1;	//6 //IPC Interrupt 6 Enable
	UINT32 ipc_int7_en                      :1;	//7 //IPC Interrupt 7 Enable
	UINT32 ipc_int8_en                      :1;	//8 //IPC Interrupt 8 Enable
	UINT32 ipc_int9_en                      :1;	//9 //IPC Interrupt 9 Enable
	UINT32 ipc_int10_en                     :1;	//10 //IPC Interrupt 10 Enable
	UINT32 ipc_int11_en                     :1;	//11 //IPC Interrupt 11 Enable
	UINT32 ipc_int12_en                     :1;	//12 //IPC Interrupt 12 Enable
	UINT32 ipc_int13_en                     :1;	//13 //IPC Interrupt 13 Enable
	UINT32 ipc_int14_en                     :1;	//14 //IPC Interrupt 14 Enable
	UINT32 ipc_int15_en                     :1;	//15 //IPC Interrupt 15 Enable
	UINT32 ipc_int16_en                     :1;	//16 //IPC Interrupt 16 Enable
	UINT32 ipc_int17_en                     :1;	//17 //IPC Interrupt 17 Enable
	UINT32 ipc_int18_en                     :1;	//18 //IPC Interrupt 18 Enable
	UINT32 ipc_int19_en                     :1;	//19 //IPC Interrupt 19 Enable
	UINT32 ipc_int20_en                     :1;	//20 //IPC Interrupt 20 Enable
	UINT32 ipc_int21_en                     :1;	//21 //IPC Interrupt 21 Enable
	UINT32 ipc_int22_en                     :1;	//22 //IPC Interrupt 22 Enable
	UINT32 ipc_int23_en                     :1;	//23 //IPC Interrupt 23 Enable
	UINT32 ipc_int24_en                     :1;	//24 //IPC Interrupt 24 Enable
	UINT32 ipc_int25_en                     :1;	//25 //IPC Interrupt 25 Enable
	UINT32 ipc_int26_en                     :1;	//26 //IPC Interrupt 26 Enable
	UINT32 ipc_int27_en                     :1;	//27 //IPC Interrupt 27 Enable
	UINT32 ipc_int28_en                     :1;	//28 //IPC Interrupt 28 Enable
	UINT32 ipc_int29_en                     :1;	//29 //IPC Interrupt 29 Enable
	UINT32 ipc_int30_en                     :1;	//30 //IPC Interrupt 30 Enable
	UINT32 ipc_int31_en                     :1;	//31 //IPC Interrupt 31 Enable
	};
}REG_MCU_IPCE2IINTEN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0F4 RO
	UINT32 ipc_int0_sts                     :1;	//0 //IPC Interrupt 0 Status
	UINT32 ipc_int1_sts                     :1;	//1 //IPC Interrupt 1 Status
	UINT32 ipc_int2_sts                     :1;	//2 //IPC Interrupt 2 Status
	UINT32 ipc_int3_sts                     :1;	//3 //IPC Interrupt 3 Status
	UINT32 ipc_int4_sts                     :1;	//4 //IPC Interrupt 4 Status
	UINT32 ipc_int5_sts                     :1;	//5 //IPC Interrupt 5 Status
	UINT32 ipc_int6_sts                     :1;	//6 //IPC Interrupt 6 Status
	UINT32 ipc_int7_sts                     :1;	//7 //IPC Interrupt 7 Status
	UINT32 ipc_int8_sts                     :1;	//8 //IPC Interrupt 8 Status
	UINT32 ipc_int9_sts                     :1;	//9 //IPC Interrupt 9 Status
	UINT32 ipc_int10_sts                    :1;	//10 //IPC Interrupt 10 Status
	UINT32 ipc_int11_sts                    :1;	//11 //IPC Interrupt 11 Status
	UINT32 ipc_int12_sts                    :1;	//12 //IPC Interrupt 12 Status
	UINT32 ipc_int13_sts                    :1;	//13 //IPC Interrupt 13 Status
	UINT32 ipc_int14_sts                    :1;	//14 //IPC Interrupt 14 Status
	UINT32 ipc_int15_sts                    :1;	//15 //IPC Interrupt 15 Status
	UINT32 ipc_int16_sts                    :1;	//16 //IPC Interrupt 16 Status
	UINT32 ipc_int17_sts                    :1;	//17 //IPC Interrupt 17 Status
	UINT32 ipc_int18_sts                    :1;	//18 //IPC Interrupt 18 Status
	UINT32 ipc_int19_sts                    :1;	//19 //IPC Interrupt 19 Status
	UINT32 ipc_int20_sts                    :1;	//20 //IPC Interrupt 20 Status
	UINT32 ipc_int21_sts                    :1;	//21 //IPC Interrupt 21 Status
	UINT32 ipc_int22_sts                    :1;	//22 //IPC Interrupt 22 Status
	UINT32 ipc_int23_sts                    :1;	//23 //IPC Interrupt 23 Status
	UINT32 ipc_int24_sts                    :1;	//24 //IPC Interrupt 24 Status
	UINT32 ipc_int25_sts                    :1;	//25 //IPC Interrupt 25 Status
	UINT32 ipc_int26_sts                    :1;	//26 //IPC Interrupt 26 Status
	UINT32 ipc_int27_sts                    :1;	//27 //IPC Interrupt 27 Status
	UINT32 ipc_int28_sts                    :1;	//28 //IPC Interrupt 28 Status
	UINT32 ipc_int29_sts                    :1;	//29 //IPC Interrupt 29 Status
	UINT32 ipc_int30_sts                    :1;	//30 //IPC Interrupt 30 Status
	UINT32 ipc_int31_sts                    :1;	//31 //IPC Interrupt 31 Status
	};
}REG_MCU_IPCE2IINTSTS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0F8 RO
	UINT32 ipc_int0_raw_sts                 :1;	//0 //IPC nterrupt 0 Raw Status
	UINT32 ipc_int1_raw_sts                 :1;	//1 //IPC nterrupt 1 Raw Status
	UINT32 ipc_int2_raw_sts                 :1;	//2 //IPC nterrupt 2 Raw Status
	UINT32 ipc_int3_raw_sts                 :1;	//3 //IPC nterrupt 3 Raw Status
	UINT32 ipc_int4_raw_sts                 :1;	//4 //IPC nterrupt 4 Raw Status
	UINT32 ipc_int5_raw_sts                 :1;	//5 //IPC nterrupt 5 Raw Status
	UINT32 ipc_int6_raw_sts                 :1;	//6 //IPC nterrupt 6 Raw Status
	UINT32 ipc_int7_raw_sts                 :1;	//7 //IPC nterrupt 7 Raw Status
	UINT32 ipc_int8_raw_sts                 :1;	//8 //IPC nterrupt 8 Raw Status
	UINT32 ipc_int9_raw_sts                 :1;	//9 //IPC nterrupt 9 Raw Status
	UINT32 ipc_int10_raw_sts                :1;	//10 //IPC nterrupt 10 Raw Status
	UINT32 ipc_int11_raw_sts                :1;	//11 //IPC nterrupt 11 Raw Status
	UINT32 ipc_int12_raw_sts                :1;	//12 //IPC nterrupt 12 Raw Status
	UINT32 ipc_int13_raw_sts                :1;	//13 //IPC nterrupt 13 Raw Status
	UINT32 ipc_int14_raw_sts                :1;	//14 //IPC nterrupt 14 Raw Status
	UINT32 ipc_int15_raw_sts                :1;	//15 //IPC nterrupt 15 Raw Status
	UINT32 ipc_int16_raw_sts                :1;	//16 //IPC nterrupt 16 Raw Status
	UINT32 ipc_int17_raw_sts                :1;	//17 //IPC nterrupt 17 Raw Status
	UINT32 ipc_int18_raw_sts                :1;	//18 //IPC nterrupt 18 Raw Status
	UINT32 ipc_int19_raw_sts                :1;	//19 //IPC nterrupt 19 Raw Status
	UINT32 ipc_int20_raw_sts                :1;	//20 //IPC nterrupt 20 Raw Status
	UINT32 ipc_int21_raw_sts                :1;	//21 //IPC nterrupt 21 Raw Status
	UINT32 ipc_int22_raw_sts                :1;	//22 //IPC nterrupt 22 Raw Status
	UINT32 ipc_int23_raw_sts                :1;	//23 //IPC nterrupt 23 Raw Status
	UINT32 ipc_int24_raw_sts                :1;	//24 //IPC nterrupt 24 Raw Status
	UINT32 ipc_int25_raw_sts                :1;	//25 //IPC nterrupt 25 Raw Status
	UINT32 ipc_int26_raw_sts                :1;	//26 //IPC nterrupt 26 Raw Status
	UINT32 ipc_int27_raw_sts                :1;	//27 //IPC nterrupt 27 Raw Status
	UINT32 ipc_int28_raw_sts                :1;	//28 //IPC nterrupt 28 Raw Status
	UINT32 ipc_int29_raw_sts                :1;	//29 //IPC nterrupt 29 Raw Status
	UINT32 ipc_int30_raw_sts                :1;	//30 //IPC nterrupt 30 Raw Status
	UINT32 ipc_int31_raw_sts                :1;	//31 //IPC nterrupt 31 Raw Status
	};
}REG_MCU_IPCE2IINTRAWSTS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E0FC RW
	UINT32 ipc_int0_clr                     :1;	//0 //IPC nterrupt 0 Clear
	UINT32 ipc_int1_clr                     :1;	//1 //IPC nterrupt 1 Clear
	UINT32 ipc_int2_clr                     :1;	//2 //IPC nterrupt 2 Clear
	UINT32 ipc_int3_clr                     :1;	//3 //IPC nterrupt 3 Clear
	UINT32 ipc_int4_clr                     :1;	//4 //IPC nterrupt 4 Clear
	UINT32 ipc_int5_clr                     :1;	//5 //IPC nterrupt 5 Clear
	UINT32 ipc_int6_clr                     :1;	//6 //IPC nterrupt 6 Clear
	UINT32 ipc_int7_clr                     :1;	//7 //IPC nterrupt 7 Clear
	UINT32 ipc_int8_clr                     :1;	//8 //IPC nterrupt 8 Clear
	UINT32 ipc_int9_clr                     :1;	//9 //IPC nterrupt 9 Clear
	UINT32 ipc_int10_clr                    :1;	//10 //IPC nterrupt 10 Clear
	UINT32 ipc_int11_clr                    :1;	//11 //IPC nterrupt 11 Clear
	UINT32 ipc_int12_clr                    :1;	//12 //IPC nterrupt 12 Clear
	UINT32 ipc_int13_clr                    :1;	//13 //IPC nterrupt 13 Clear
	UINT32 ipc_int14_clr                    :1;	//14 //IPC nterrupt 14 Clear
	UINT32 ipc_int15_clr                    :1;	//15 //IPC nterrupt 15 Clear
	UINT32 ipc_int16_clr                    :1;	//16 //IPC nterrupt 16 Clear
	UINT32 ipc_int17_clr                    :1;	//17 //IPC nterrupt 17 Clear
	UINT32 ipc_int18_clr                    :1;	//18 //IPC nterrupt 18 Clear
	UINT32 ipc_int19_clr                    :1;	//19 //IPC nterrupt 19 Clear
	UINT32 ipc_int20_clr                    :1;	//20 //IPC nterrupt 20 Clear
	UINT32 ipc_int21_clr                    :1;	//21 //IPC nterrupt 21 Clear
	UINT32 ipc_int22_clr                    :1;	//22 //IPC nterrupt 22 Clear
	UINT32 ipc_int23_clr                    :1;	//23 //IPC nterrupt 23 Clear
	UINT32 ipc_int24_clr                    :1;	//24 //IPC nterrupt 24 Clear
	UINT32 ipc_int25_clr                    :1;	//25 //IPC nterrupt 25 Clear
	UINT32 ipc_int26_clr                    :1;	//26 //IPC nterrupt 26 Clear
	UINT32 ipc_int27_clr                    :1;	//27 //IPC nterrupt 27 Clear
	UINT32 ipc_int28_clr                    :1;	//28 //IPC nterrupt 28 Clear
	UINT32 ipc_int29_clr                    :1;	//29 //IPC nterrupt 29 Clear
	UINT32 ipc_int30_clr                    :1;	//30 //IPC nterrupt 30 Clear
	UINT32 ipc_int31_clr                    :1;	//31 //IPC nterrupt 31 Clear
	};
}REG_MCU_IPCE2IINTCLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E100 RW
	UINT32 ipc_reg0                         :32;	//31:0	//IPC 0 Register
	};
}REG_MCU_IPCREG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E104 RW
	UINT32 ipc_reg1                         :32;	//31:0	//IPC 1 Register
	};
}REG_MCU_IPCREG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E108 RW
	UINT32 ipc_reg2                         :32;	//31:0	//IPC 2 Register
	};
}REG_MCU_IPCREG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E10C RW
	UINT32 ipc_reg3                         :32;	//31:0	//IPC 3 Register
	};
}REG_MCU_IPCREG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E110 RW
	UINT32 ipc_reg4                         :32;	//31:0	//IPC 4 Register
	};
}REG_MCU_IPCREG4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E114 RW
	UINT32 ipc_reg5                         :32;	//31:0	//IPC 5 Register
	};
}REG_MCU_IPCREG5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E118 RW
	UINT32 ipc_reg6                         :32;	//31:0	//IPC 6 Register
	};
}REG_MCU_IPCREG6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E11C RW
	UINT32 ipc_reg7                         :32;	//31:0	//IPC 7 Register
	};
}REG_MCU_IPCREG7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E120 RW
	UINT32 ipc_reg8                         :32;	//31:0	//IPC 8 Register
	};
}REG_MCU_IPCREG8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E124 RW
	UINT32 ipc_reg9                         :32;	//31:0	//IPC 9 Register
	};
}REG_MCU_IPCREG9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E128 RW
	UINT32 ipc_reg10                        :32;	//31:0	//IPC 10 Register
	};
}REG_MCU_IPCREG10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E12C RW
	UINT32 ipc_reg11                        :32;	//31:0	//IPC 11 Register
	};
}REG_MCU_IPCREG11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E130 RW
	UINT32 ipc_reg12                        :32;	//31:0	//IPC 12 Register
	};
}REG_MCU_IPCREG12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E134 RW
	UINT32 ipc_reg13                        :32;	//31:0	//IPC 13 Register
	};
}REG_MCU_IPCREG13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E138 RW
	UINT32 ipc_reg14                        :32;	//31:0	//IPC 14 Register
	};
}REG_MCU_IPCREG14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E13C RW
	UINT32 ipc_reg15                        :32;	//31:0	//IPC 15 Register
	};
}REG_MCU_IPCREG15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E140 RW
	UINT32 ipc_reg16                        :32;	//31:0	//IPC 16 Register
	};
}REG_MCU_IPCREG16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E144 RW
	UINT32 ipc_reg17                        :32;	//31:0	//IPC 17 Register
	};
}REG_MCU_IPCREG17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E148 RW
	UINT32 ipc_reg18                        :32;	//31:0	//IPC 18 Register
	};
}REG_MCU_IPCREG18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E14C RW
	UINT32 ipc_reg19                        :32;	//31:0	//IPC 19 Register
	};
}REG_MCU_IPCREG19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E150 RW
	UINT32 ipc_reg20                        :32;	//31:0	//IPC 20 Register
	};
}REG_MCU_IPCREG20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E154 RW
	UINT32 ipc_reg21                        :32;	//31:0	//IPC 21 Register
	};
}REG_MCU_IPCREG21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E158 RW
	UINT32 ipc_reg22                        :32;	//31:0	//IPC 22 Register
	};
}REG_MCU_IPCREG22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E15C RW
	UINT32 ipc_reg23                        :32;	//31:0	//IPC 23 Register
	};
}REG_MCU_IPCREG23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E160 RW
	UINT32 ipc_reg24                        :32;	//31:0	//IPC 24 Register
	};
}REG_MCU_IPCREG24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E164 RW
	UINT32 ipc_reg25                        :32;	//31:0	//IPC 25 Register
	};
}REG_MCU_IPCREG25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E168 RW
	UINT32 ipc_reg26                        :32;	//31:0	//IPC 26 Register
	};
}REG_MCU_IPCREG26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E16C RW
	UINT32 ipc_reg27                        :32;	//31:0	//IPC 27 Register
	};
}REG_MCU_IPCREG27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E170 RW
	UINT32 ipc_reg28                        :32;	//31:0	//IPC 28 Register
	};
}REG_MCU_IPCREG28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E174 RW
	UINT32 ipc_reg29                        :32;	//31:0	//IPC 29 Register
	};
}REG_MCU_IPCREG29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E178 RW
	UINT32 ipc_reg30                        :32;	//31:0	//IPC 30 Register
	};
}REG_MCU_IPCREG30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000E17C RW
	UINT32 ipc_reg31                        :32;	//31:0	//IPC 31 Register
	};
}REG_MCU_IPCREG31_T;

typedef struct {
	REG_MCU_RUNSTALL_T                                         runstall;	//0xF000E000
	REG_MCU_STATVECTORSEL_T                               statvectorsel;	//0xF000E004
	UINT32                                                    reserved0;	//0xF000E008
	UINT32                                                    reserved1;	//0xF000E00C
	UINT32                                                    reserved2;	//0xF000E010
	UINT32                                                    reserved3;	//0xF000E014
	UINT32                                                    reserved4;	//0xF000E018
	UINT32                                                    reserved5;	//0xF000E01C
	UINT32                                                    reserved6;	//0xF000E020
	UINT32                                                    reserved7;	//0xF000E024
	UINT32                                                    reserved8;	//0xF000E028
	UINT32                                                    reserved9;	//0xF000E02C
	UINT32                                                   reserved10;	//0xF000E030
	UINT32                                                   reserved11;	//0xF000E034
	UINT32                                                   reserved12;	//0xF000E038
	UINT32                                                   reserved13;	//0xF000E03C
	UINT32                                                   reserved14;	//0xF000E040
	UINT32                                                   reserved15;	//0xF000E044
	UINT32                                                   reserved16;	//0xF000E048
	UINT32                                                   reserved17;	//0xF000E04C
	UINT32                                                   reserved18;	//0xF000E050
	UINT32                                                   reserved19;	//0xF000E054
	UINT32                                                   reserved20;	//0xF000E058
	UINT32                                                   reserved21;	//0xF000E05C
	UINT32                                                   reserved22;	//0xF000E060
	UINT32                                                   reserved23;	//0xF000E064
	UINT32                                                   reserved24;	//0xF000E068
	UINT32                                                   reserved25;	//0xF000E06C
	UINT32                                                   reserved26;	//0xF000E070
	UINT32                                                   reserved27;	//0xF000E074
	UINT32                                                   reserved28;	//0xF000E078
	UINT32                                                   reserved29;	//0xF000E07C
	UINT32                                                   reserved30;	//0xF000E080
	UINT32                                                   reserved31;	//0xF000E084
	UINT32                                                   reserved32;	//0xF000E088
	UINT32                                                   reserved33;	//0xF000E08C
	UINT32                                                   reserved34;	//0xF000E090
	UINT32                                                   reserved35;	//0xF000E094
	UINT32                                                   reserved36;	//0xF000E098
	UINT32                                                   reserved37;	//0xF000E09C
	UINT32                                                   reserved38;	//0xF000E0A0
	UINT32                                                   reserved39;	//0xF000E0A4
	UINT32                                                   reserved40;	//0xF000E0A8
	UINT32                                                   reserved41;	//0xF000E0AC
	UINT32                                                   reserved42;	//0xF000E0B0
	UINT32                                                   reserved43;	//0xF000E0B4
	UINT32                                                   reserved44;	//0xF000E0B8
	UINT32                                                   reserved45;	//0xF000E0BC
	UINT32                                                   reserved46;	//0xF000E0C0
	UINT32                                                   reserved47;	//0xF000E0C4
	UINT32                                                   reserved48;	//0xF000E0C8
	UINT32                                                   reserved49;	//0xF000E0CC
	UINT32                                                   reserved50;	//0xF000E0D0
	UINT32                                                   reserved51;	//0xF000E0D4
	UINT32                                                   reserved52;	//0xF000E0D8
	UINT32                                                   reserved53;	//0xF000E0DC
	REG_MCU_IPCI2EINTEN_T                                   ipci2einten;	//0xF000E0E0
	REG_MCU_IPCI2EINTSTS_T                                 ipci2eintsts;	//0xF000E0E4
	REG_MCU_IPCI2EINTRAWSTS_T                           ipci2eintrawsts;	//0xF000E0E8
	REG_MCU_IPCI2EINTCLR_T                                 ipci2eintclr;	//0xF000E0EC
	REG_MCU_IPCE2IINTEN_T                                   ipce2iinten;	//0xF000E0F0
	REG_MCU_IPCE2IINTSTS_T                                 ipce2iintsts;	//0xF000E0F4
	REG_MCU_IPCE2IINTRAWSTS_T                           ipce2iintrawsts;	//0xF000E0F8
	REG_MCU_IPCE2IINTCLR_T                                 ipce2iintclr;	//0xF000E0FC
	REG_MCU_IPCREG0_T                                           ipcreg0;	//0xF000E100
	REG_MCU_IPCREG1_T                                           ipcreg1;	//0xF000E104
	REG_MCU_IPCREG2_T                                           ipcreg2;	//0xF000E108
	REG_MCU_IPCREG3_T                                           ipcreg3;	//0xF000E10C
	REG_MCU_IPCREG4_T                                           ipcreg4;	//0xF000E110
	REG_MCU_IPCREG5_T                                           ipcreg5;	//0xF000E114
	REG_MCU_IPCREG6_T                                           ipcreg6;	//0xF000E118
	REG_MCU_IPCREG7_T                                           ipcreg7;	//0xF000E11C
	REG_MCU_IPCREG8_T                                           ipcreg8;	//0xF000E120
	REG_MCU_IPCREG9_T                                           ipcreg9;	//0xF000E124
	REG_MCU_IPCREG10_T                                         ipcreg10;	//0xF000E128
	REG_MCU_IPCREG11_T                                         ipcreg11;	//0xF000E12C
	REG_MCU_IPCREG12_T                                         ipcreg12;	//0xF000E130
	REG_MCU_IPCREG13_T                                         ipcreg13;	//0xF000E134
	REG_MCU_IPCREG14_T                                         ipcreg14;	//0xF000E138
	REG_MCU_IPCREG15_T                                         ipcreg15;	//0xF000E13C
	REG_MCU_IPCREG16_T                                         ipcreg16;	//0xF000E140
	REG_MCU_IPCREG17_T                                         ipcreg17;	//0xF000E144
	REG_MCU_IPCREG18_T                                         ipcreg18;	//0xF000E148
	REG_MCU_IPCREG19_T                                         ipcreg19;	//0xF000E14C
	REG_MCU_IPCREG20_T                                         ipcreg20;	//0xF000E150
	REG_MCU_IPCREG21_T                                         ipcreg21;	//0xF000E154
	REG_MCU_IPCREG22_T                                         ipcreg22;	//0xF000E158
	REG_MCU_IPCREG23_T                                         ipcreg23;	//0xF000E15C
	REG_MCU_IPCREG24_T                                         ipcreg24;	//0xF000E160
	REG_MCU_IPCREG25_T                                         ipcreg25;	//0xF000E164
	REG_MCU_IPCREG26_T                                         ipcreg26;	//0xF000E168
	REG_MCU_IPCREG27_T                                         ipcreg27;	//0xF000E16C
	REG_MCU_IPCREG28_T                                         ipcreg28;	//0xF000E170
	REG_MCU_IPCREG29_T                                         ipcreg29;	//0xF000E174
	REG_MCU_IPCREG30_T                                         ipcreg30;	//0xF000E178
	REG_MCU_IPCREG31_T                                         ipcreg31;	//0xF000E17C
}REG_MCU_T;

extern volatile REG_MCU_T*                         gpREG_MCU;
      
#endif
