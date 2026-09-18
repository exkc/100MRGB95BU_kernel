#ifndef _PVMCON_REG_H_
#define _PVMCON_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  HEADER_2 : Use Another Header Structure
---------------------------------------------------------------------------------------*/

#ifndef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xCAA3_2000    int_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_int_en                :  1,    //      0
                              : 31;    //   31:1 reserved
}PVMCON_INT_CTRL_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2004    int_clr ''

   (노트) SYN_HPM_CPU 탭의 INT_CLR 는 bit field 관련 내용은 아래와 같이 메모 남겨 두었습니다.
          업무 진행하시는데 참고하시면 될 것 같습니다.
          http://share.lge.com/sites/sic/O22/207_SW/1.%20Register%20Manual/O22_CTOP_SYN_Register_Manual.xlsx
-----------------------------------------------------------------------------------------*/
typedef union {
	struct {
   		UINT32
    	reg_int_st            :  1,    //      0
                              : 31;    //   31:1 reserved
	};
	struct {
   		UINT32
   		reg_int_cl            :  1,    //      0
                              : 31;    //   31:1 reserved
	};
}PVMCON_INT_CLR_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2030    hpm_con ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_rstn                  :  1,    //      0
    hpm_pdb                   :  1,    //      1
                              :  2,    //   3: 2 reserved
    pvm_rstn                  :  1,    //      4
    pvm_pdb                   :  1,    //      5
                              : 26;    //   31:6 reserved
}PVMCON_HPM_CON_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2034    pvm_con ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cnt_pulse_vm              :  7,    //   6: 0
                              :  1,    //      7 reserved
    cnt_ro_vm                 :  3,    //  10: 8
                              :  1,    //     11 reserved
    cnt_out_vm                :  1,    //     12
                              : 19;    //  31:13 reserved
}PVMCON_PVM_CON_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2040    clk_cnt ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_ext_clk_cnt           : 14,    //  13: 0
                              :  2,    //  15:14 reserved
    cnt_digi_vm               : 16;    //  31:16
}PVMCON_CLK_CNT_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2044    sel_div ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_sel_div               :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}PVMCON_SEL_DIV_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2048    hpm_mode ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_mode                  :  4,    //   3: 0
    vm_mode                   :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}PVMCON_HPM_MODE_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_204C    hpm_cnt ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_dout_latch            : 14,    //  13: 0
                              :  2,    //  15:14 reserved
    pvm_dout_latch            : 14,    //  29:16
                              :  2;    //  31:30 reserved
}PVMCON_HPM_CNT_O22A0_T;

/*-----------------------------------------------------------------------------------------
    hpm_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PVMCON_INT_CTRL_O22A0_T           int_ctrl   ;             // 0xCAA3_2000
    PVMCON_INT_CLR_O22A0_T            int_clr    ;             // 0xCAA3_2004
    UINT32                             _rsvd_00[10];            // 0xCAA3_2008 ~ 0xCAA3_202C
    PVMCON_HPM_CON_O22A0_T            hpm_con    ;             // 0xCAA3_2030
    PVMCON_PVM_CON_O22A0_T            pvm_con    ;             // 0xCAA3_2034
    UINT32                             _rsvd_01[2];             // 0xCAA3_2038 ~ 0xCAA3_203C
    PVMCON_CLK_CNT_O22A0_T            clk_cnt    ;             // 0xCAA3_2040
    PVMCON_SEL_DIV_O22A0_T            sel_div    ;             // 0xCAA3_2044
    PVMCON_HPM_MODE_O22A0_T           hpm_mode   ;             // 0xCAA3_2048
    PVMCON_HPM_CNT_O22A0_T            hpm_cnt    ;             // 0xCAA3_204C
}PVMCON_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif

/*----------------------------------------------------------------------------------------
  Reference Header (Another Header Structure)
---------------------------------------------------------------------------------------*/

#ifdef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

#define BASEADDRESS 0

#define PVMCON_INT_CTRL_O22A0_T_OFF                        (BASEADDRESS+0x0000)
#define PVMCON_INT_CLR_O22A0_T_OFF                         (BASEADDRESS+0x0004)
#define PVMCON_HPM_CON_O22A0_T_OFF                         (BASEADDRESS+0x0030)
#define PVMCON_PVM_CON_O22A0_T_OFF                         (BASEADDRESS+0x0034)
#define PVMCON_CLK_CNT_O22A0_T_OFF                         (BASEADDRESS+0x0040)
#define PVMCON_SEL_DIV_O22A0_T_OFF                         (BASEADDRESS+0x0044)
#define PVMCON_HPM_MODE_O22A0_T_OFF                        (BASEADDRESS+0x0048)
#define PVMCON_HPM_CNT_O22A0_T_OFF                         (BASEADDRESS+0x004C)

/*-----------------------------------------------------------------------------------------
    0xCAA3_2000    int_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_int_en         :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}PVMCON_INT_CTRL_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2004    int_clr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_int_cl         :  1;    //      0
    UINT32 reg_int_st         :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}PVMCON_INT_CLR_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2030    hpm_con ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_rstn           :  1;    //      0
    UINT32 hpm_pdb            :  1;    //      1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 pvm_rstn           :  1;    //      4
    UINT32 pvm_pdb            :  1;    //      5
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}PVMCON_HPM_CON_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2034    pvm_con ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 cnt_pulse_vm       :  7;    //   6: 0
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 cnt_ro_vm          :  3;    //  10: 8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 cnt_out_vm         :  1;    //     12
    UINT32 resvd02            : 19;    //  31:13 reserved
    };
}PVMCON_PVM_CON_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2040    clk_cnt ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_ext_clk_cnt    : 14;    //  13: 0
    UINT32 resvd00            :  2;    //  15:14 reserved
    UINT32 cnt_digi_vm        : 16;    //  31:16
    };
}PVMCON_CLK_CNT_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2044    sel_div ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_sel_div        :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}PVMCON_SEL_DIV_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_2048    hpm_mode ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_mode           :  4;    //   3: 0
    UINT32 vm_mode            :  3;    //   6: 4
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}PVMCON_HPM_MODE_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_204C    hpm_cnt ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_dout_latch     : 14;    //  13: 0
    UINT32 resvd00            :  2;    //  15:14 reserved
    UINT32 pvm_dout_latch     : 14;    //  29:16
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}PVMCON_HPM_CNT_O22A0_T;

/*-----------------------------------------------------------------------------------------
    hpm_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PVMCON_INT_CTRL_O22A0_T           int_ctrl   ;             // 0xCAA3_2000
    PVMCON_INT_CLR_O22A0_T            int_clr    ;             // 0xCAA3_2004
    UINT32                             _rsvd_00[10];            // 0xCAA3_2008 ~ 0xCAA3_202C
    PVMCON_HPM_CON_O22A0_T            hpm_con    ;             // 0xCAA3_2030
    PVMCON_PVM_CON_O22A0_T            pvm_con    ;             // 0xCAA3_2034
    UINT32                             _rsvd_01[2];             // 0xCAA3_2038 ~ 0xCAA3_203C
    PVMCON_CLK_CNT_O22A0_T            clk_cnt    ;             // 0xCAA3_2040
    PVMCON_SEL_DIV_O22A0_T            sel_div    ;             // 0xCAA3_2044
    PVMCON_HPM_MODE_O22A0_T           hpm_mode   ;             // 0xCAA3_2048
    PVMCON_HPM_CNT_O22A0_T            hpm_cnt    ;             // 0xCAA3_204C
}PVMCON_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_PVMCON_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

