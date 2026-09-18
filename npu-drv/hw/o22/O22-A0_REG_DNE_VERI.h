#ifndef _REG_DNE_VERI_h
#define _REG_DNE_VERI_h
//Header File for DNE_VERI in \PQE\O22-A0_PQE_VERI_reg_man.xls

#define REG_DNE_VERI_SYS_VERI_0                                            (APB_DNE_VERI_BASE+0x0000)
#define REG_DNE_VERI_SYS_VERI_1                                            (APB_DNE_VERI_BASE+0x0004)
#define REG_DNE_VERI_SYS_VERI_2                                            (APB_DNE_VERI_BASE+0x0008)
#define REG_DNE_VERI_SYS_VERI_3                                            (APB_DNE_VERI_BASE+0x000C)

typedef union {
	UINT32 udata32;
	struct {						//0xCC880200 RW 0x0000_0000
	UINT32 reg_sys_veri_0                   :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_DNE_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880204 RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_DNE_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
    struct {
    UINT32 updateCnt    : 8; // [7:0] update_count of CPU to check system lock up or running, rolling on every function run of AI platform(master)
    UINT32 statusOfCpu  : 8; // [15:8] status of CPU : t.b.d
    UINT32 request2Mcu  :16; // [31:16] Magic code : 0x5BD0(MCU handling permitted), the other cases are not permittied to MCU handling
    };
}REG_DNE_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
    struct {
    UINT32 updateCnt   : 8; // [7:0] update_count of MCU to check system lock up or running, rolling on every pic init/start by MCU
    UINT32 statusOfMcu : 8; // [15:8] Magic code : t.b.d
    UINT32 response2Cpu :16;// [31:16] Magic code : 0x5BD0 (MCU handling), 0x05BD (Wait Done), 0x0000 (quit handling), the other cases are unknown.
    };
}REG_DNE_VERI_SYS_VERI_3_T;

typedef struct {
	REG_DNE_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCC880200
	REG_DNE_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xCC880204
	REG_DNE_VERI_SYS_VERI_2_T                                run_dne;		//0xCC880208
	REG_DNE_VERI_SYS_VERI_3_T                                run_cnt;		//0xCC88020C
}REG_DNE_VERI_T;

extern volatile REG_DNE_VERI_T*                    gpREG_DNE_VERI;

#endif
