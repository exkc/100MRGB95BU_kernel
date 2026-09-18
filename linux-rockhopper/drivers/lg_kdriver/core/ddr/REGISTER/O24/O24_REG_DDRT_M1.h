#ifndef _REG_DDRT_M1_h
#define _REG_DDRT_M1_h
//Header File for DDRT_M1 in \O24\O24_DRAM_M1_Register_Manual.xls

#define REG_DDRT_M1_TZC_NSAID_0                                             (APB_DDRT_M1_BASE+0x7100)
#define REG_DDRT_M1_TZC_NSAID_1                                             (APB_DDRT_M1_BASE+0x7104)
#define REG_DDRT_M1_TZC_NSAID_2                                             (APB_DDRT_M1_BASE+0x7108)
#define REG_DDRT_M1_TZC_NSAID_3                                             (APB_DDRT_M1_BASE+0x710C)
#define REG_DDRT_M1_TZC_NSAID_4                                             (APB_DDRT_M1_BASE+0x7110)
#define REG_DDRT_M1_TZC_NSAID_5                                             (APB_DDRT_M1_BASE+0x7114)
#define REG_DDRT_M1_TZC_NSAID_6                                             (APB_DDRT_M1_BASE+0x7118)
#define REG_DDRT_M1_TZC_NSAID_7                                             (APB_DDRT_M1_BASE+0x711C)
#define REG_DDRT_M1_TZC_PATH_ON                                             (APB_DDRT_M1_BASE+0x7130)
#define REG_DDRT_M1_APB_SECURE_CONFIG                                       (APB_DDRT_M1_BASE+0x7200)

typedef union {
	UINT32 udata32;
	struct {						//0xC4907100 RW
	UINT32 reg_master0_nsaid                :4;	//3:0	//NSAID of Master ID 0
	UINT32 reg_master1_nsaid                :4;	//7:4	//NSAID of Master ID 1
	UINT32 reg_master2_nsaid                :4;	//11:8	//NSAID of Master ID 2
	UINT32 reg_master3_nsaid                :4;	//15:12	//NSAID of Master ID 3
	UINT32 reg_master4_nsaid                :4;	//19:16	//NSAID of Master ID 4
	UINT32 reg_master5_nsaid                :4;	//23:20	//NSAID of Master ID 5
	UINT32 reg_master6_nsaid                :4;	//27:24	//NSAID of Master ID 6
	UINT32 reg_master7_nsaid                :4;	//31:28	//NSAID of Master ID 7
	};
}REG_DDRT_M1_TZC_NSAID_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907104 RW
	UINT32 reg_master8_nsaid                :4;	//3:0	//NSAID of Master ID 8
	UINT32 reg_master9_nsaid                :4;	//7:4	//NSAID of Master ID 9
	UINT32 reg_master10_nsaid               :4;	//11:8	//NSAID of Master ID 10
	UINT32 reg_master11_nsaid               :4;	//15:12	//NSAID of Master ID 11
	UINT32 reg_master12_nsaid               :4;	//19:16	//NSAID of Master ID 12
	UINT32 reg_master13_nsaid               :4;	//23:20	//NSAID of Master ID 13
	UINT32 reg_master14_nsaid               :4;	//27:24	//NSAID of Master ID 14
	UINT32 reg_master15_nsaid               :4;	//31:28	//NSAID of Master ID 15
	};
}REG_DDRT_M1_TZC_NSAID_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907108 RW
	UINT32 reg_master16_nsaid               :4;	//3:0	//NSAID of Master ID 16
	UINT32 reg_master17_nsaid               :4;	//7:4	//NSAID of Master ID 17
	UINT32 reg_master18_nsaid               :4;	//11:8	//NSAID of Master ID 18
	UINT32 reg_master19_nsaid               :4;	//15:12	//NSAID of Master ID 19
	UINT32 reg_master20_nsaid               :4;	//19:16	//NSAID of Master ID 20
	UINT32 reg_master21_nsaid               :4;	//23:20	//NSAID of Master ID 21
	UINT32 reg_master22_nsaid               :4;	//27:24	//NSAID of Master ID 22
	UINT32 reg_master23_nsaid               :4;	//31:28	//NSAID of Master ID 23
	};
}REG_DDRT_M1_TZC_NSAID_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490710C RW
	UINT32 reg_master24_nsaid               :4;	//3:0	//NSAID of Master ID 24
	UINT32 reg_master25_nsaid               :4;	//7:4	//NSAID of Master ID 25
	UINT32 reg_master26_nsaid               :4;	//11:8	//NSAID of Master ID 26
	UINT32 reg_master27_nsaid               :4;	//15:12	//NSAID of Master ID 27
	UINT32 reg_master28_nsaid               :4;	//19:16	//NSAID of Master ID 28
	UINT32 reg_master29_nsaid               :4;	//23:20	//NSAID of Master ID 29
	UINT32 reg_master30_nsaid               :4;	//27:24	//NSAID of Master ID 30
	UINT32 reg_master31_nsaid               :4;	//31:28	//NSAID of Master ID 31
	};
}REG_DDRT_M1_TZC_NSAID_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907110 RW
	UINT32 reg_master32_nsaid               :4;	//3:0	//NSAID of Master ID 32
	UINT32 reg_master33_nsaid               :4;	//7:4	//NSAID of Master ID 33
	UINT32 reg_master34_nsaid               :4;	//11:8	//NSAID of Master ID 34
	UINT32 reg_master35_nsaid               :4;	//15:12	//NSAID of Master ID 35
	UINT32 reg_master36_nsaid               :4;	//19:16	//NSAID of Master ID 36
	UINT32 reg_master37_nsaid               :4;	//23:20	//NSAID of Master ID 37
	UINT32 reg_master38_nsaid               :4;	//27:24	//NSAID of Master ID 38
	UINT32 reg_master39_nsaid               :4;	//31:28	//NSAID of Master ID 39
	};
}REG_DDRT_M1_TZC_NSAID_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907114 RW
	UINT32 reg_master40_nsaid               :4;	//3:0	//NSAID of Master ID 40
	UINT32 reg_master41_nsaid               :4;	//7:4	//NSAID of Master ID 41
	UINT32 reg_master42_nsaid               :4;	//11:8	//NSAID of Master ID 42
	UINT32 reg_master43_nsaid               :4;	//15:12	//NSAID of Master ID 43
	UINT32 reg_master44_nsaid               :4;	//19:16	//NSAID of Master ID 44
	UINT32 reg_master45_nsaid               :4;	//23:20	//NSAID of Master ID 45
	UINT32 reg_master46_nsaid               :4;	//27:24	//NSAID of Master ID 46
	UINT32 reg_master47_nsaid               :4;	//31:28	//NSAID of Master ID 47
	};
}REG_DDRT_M1_TZC_NSAID_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907118 RW
	UINT32 reg_master48_nsaid               :4;	//3:0	//NSAID of Master ID 48
	UINT32 reg_master49_nsaid               :4;	//7:4	//NSAID of Master ID 49
	UINT32 reg_master50_nsaid               :4;	//11:8	//NSAID of Master ID 50
	UINT32 reg_master51_nsaid               :4;	//15:12	//NSAID of Master ID 51
	UINT32 reg_master52_nsaid               :4;	//19:16	//NSAID of Master ID 52
	UINT32 reg_master53_nsaid               :4;	//23:20	//NSAID of Master ID 53
	UINT32 reg_master54_nsaid               :4;	//27:24	//NSAID of Master ID 54
	UINT32 reg_master55_nsaid               :4;	//31:28	//NSAID of Master ID 55
	};
}REG_DDRT_M1_TZC_NSAID_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490711C RW
	UINT32 reg_master56_nsaid               :4;	//3:0	//NSAID of Master ID 56
	UINT32 reg_master57_nsaid               :4;	//7:4	//NSAID of Master ID 57
	UINT32 reg_master58_nsaid               :4;	//11:8	//NSAID of Master ID 58
	UINT32 reg_master59_nsaid               :4;	//15:12	//NSAID of Master ID 59
	UINT32 reg_master60_nsaid               :4;	//19:16	//NSAID of Master ID 60
	UINT32 reg_master61_nsaid               :4;	//23:20	//NSAID of Master ID 61
	UINT32 reg_master62_nsaid               :4;	//27:24	//NSAID of Master ID 62
	UINT32 reg_master63_nsaid               :4;	//31:28	//NSAID of Master ID 63
	};
}REG_DDRT_M1_TZC_NSAID_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907130 RW
	UINT32 reg_pid_0_asc_on                 :1;	//0 //TZC path enable signal of pid 0
	UINT32 resvd0                           :3;  
	UINT32 reg_pid_1_asc_on                 :1;	//4 //TZC path enable signal of pid 1
	UINT32 resvd1                           :3;  
	UINT32 reg_pid_2_asc_on                 :1;	//8 //TZC path enable signal of pid 2
	UINT32 resvd2                           :3;  
	UINT32 reg_pid_3_asc_on                 :1;	//12 //TZC path enable signal of pid 3
	UINT32 resvd3                           :3;  
	UINT32 reg_pid_4_asc_on                 :1;	//16 //TZC path enable signal of pid 4
	UINT32 resvd4                           :3;  
	UINT32 reg_pid_5_asc_on                 :1;	//20 //TZC path enable signal of pid 5
	UINT32 resvd5                           :3;  
	UINT32 reg_pid_6_asc_on                 :1;	//24 //TZC path enable signal of pid 6
	UINT32 resvd6                           :3;  
	UINT32 reg_pid_7_asc_on                 :1;	//28 //TZC path enable signal of pid 7
	UINT32 resvd7                           :3;  
	};
}REG_DDRT_M1_TZC_PATH_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4907200 RW
	UINT32 reg_bus_resp_error               :1;	//0 //0x0 : PSLVERR disable 0x1 : PSLVERR enable
	UINT32 resvd0                           :3;  
	UINT32 reg_dramc_sec                    :1;	//4 //0x1 : allow only security access (0x00_00~0x70_FF)
	UINT32 resvd1                           :3;  
	UINT32 reg_tzc_sec                      :1;	//8 //0x1 : allow only security access (0x71_00~0x71_FF)
	UINT32 resvd2                           :3;  
	UINT32 reg_phy_sec                      :1;	//12 //0x1 : allow only security access (0x80_00~0xFF_FF)
	UINT32 resvd3                           :19; 
	};
}REG_DDRT_M1_APB_SECURE_CONFIG_T;

typedef struct {
	REG_DDRT_M1_TZC_NSAID_0_T                               tzc_nsaid_0;	//0xC4907100
	REG_DDRT_M1_TZC_NSAID_1_T                               tzc_nsaid_1;	//0xC4907104
	REG_DDRT_M1_TZC_NSAID_2_T                               tzc_nsaid_2;	//0xC4907108
	REG_DDRT_M1_TZC_NSAID_3_T                               tzc_nsaid_3;	//0xC490710C
	REG_DDRT_M1_TZC_NSAID_4_T                               tzc_nsaid_4;	//0xC4907110
	REG_DDRT_M1_TZC_NSAID_5_T                               tzc_nsaid_5;	//0xC4907114
	REG_DDRT_M1_TZC_NSAID_6_T                               tzc_nsaid_6;	//0xC4907118
	REG_DDRT_M1_TZC_NSAID_7_T                               tzc_nsaid_7;	//0xC490711C
	UINT32                                                    reserved0;	//0xC4907120
	UINT32                                                    reserved1;	//0xC4907124
	UINT32                                                    reserved2;	//0xC4907128
	UINT32                                                    reserved3;	//0xC490712C
	REG_DDRT_M1_TZC_PATH_ON_T                               tzc_path_on;	//0xC4907130
	UINT32                                                    reserved4;	//0xC4907134
	UINT32                                                    reserved5;	//0xC4907138
	UINT32                                                    reserved6;	//0xC490713C
	UINT32                                                    reserved7;	//0xC4907140
	UINT32                                                    reserved8;	//0xC4907144
	UINT32                                                    reserved9;	//0xC4907148
	UINT32                                                   reserved10;	//0xC490714C
	UINT32                                                   reserved11;	//0xC4907150
	UINT32                                                   reserved12;	//0xC4907154
	UINT32                                                   reserved13;	//0xC4907158
	UINT32                                                   reserved14;	//0xC490715C
	UINT32                                                   reserved15;	//0xC4907160
	UINT32                                                   reserved16;	//0xC4907164
	UINT32                                                   reserved17;	//0xC4907168
	UINT32                                                   reserved18;	//0xC490716C
	UINT32                                                   reserved19;	//0xC4907170
	UINT32                                                   reserved20;	//0xC4907174
	UINT32                                                   reserved21;	//0xC4907178
	UINT32                                                   reserved22;	//0xC490717C
	UINT32                                                   reserved23;	//0xC4907180
	UINT32                                                   reserved24;	//0xC4907184
	UINT32                                                   reserved25;	//0xC4907188
	UINT32                                                   reserved26;	//0xC490718C
	UINT32                                                   reserved27;	//0xC4907190
	UINT32                                                   reserved28;	//0xC4907194
	UINT32                                                   reserved29;	//0xC4907198
	UINT32                                                   reserved30;	//0xC490719C
	UINT32                                                   reserved31;	//0xC49071A0
	UINT32                                                   reserved32;	//0xC49071A4
	UINT32                                                   reserved33;	//0xC49071A8
	UINT32                                                   reserved34;	//0xC49071AC
	UINT32                                                   reserved35;	//0xC49071B0
	UINT32                                                   reserved36;	//0xC49071B4
	UINT32                                                   reserved37;	//0xC49071B8
	UINT32                                                   reserved38;	//0xC49071BC
	UINT32                                                   reserved39;	//0xC49071C0
	UINT32                                                   reserved40;	//0xC49071C4
	UINT32                                                   reserved41;	//0xC49071C8
	UINT32                                                   reserved42;	//0xC49071CC
	UINT32                                                   reserved43;	//0xC49071D0
	UINT32                                                   reserved44;	//0xC49071D4
	UINT32                                                   reserved45;	//0xC49071D8
	UINT32                                                   reserved46;	//0xC49071DC
	UINT32                                                   reserved47;	//0xC49071E0
	UINT32                                                   reserved48;	//0xC49071E4
	UINT32                                                   reserved49;	//0xC49071E8
	UINT32                                                   reserved50;	//0xC49071EC
	UINT32                                                   reserved51;	//0xC49071F0
	UINT32                                                   reserved52;	//0xC49071F4
	UINT32                                                   reserved53;	//0xC49071F8
	UINT32                                                   reserved54;	//0xC49071FC
	REG_DDRT_M1_APB_SECURE_CONFIG_T                   apb_secure_config;	//0xC4907200
}REG_DDRT_M1_T;

extern volatile REG_DDRT_M1_T*                     gpREG_DDRT_M1;
  
#endif
