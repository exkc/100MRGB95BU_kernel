#ifndef _PE_CHPI_CCO_TBL_F20A0_H_
#define _PE_CHPI_CCO_TBL_F20A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0342578 RW
	UINT32 apl_position                     :2;	//1:0	//00 := PE1 input(YC)	'01 = OCSC input(YC)	'10 = OCSC output(RGB)	'11 = PE1 output(RGB)
	UINT32 resvd0                           :6;
	UINT32 act_win_mode                     :1;	//8 //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd1                           :23;
	};
	};
}PE_F20_PE1_APL_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0342720 RW
	UINT32 dynamic_contrast_en              :1;	//0 //0' : disable	'1' : enable
	UINT32 hist_bin_mode                    :2;	//2:1	//00' : 32 bin mode	others : 16 bin mode
	UINT32 hist_clear                       :1;	//3 //Debugging purpose, force deleting for histogram memory.	'1' : clear
	UINT32 window01_enable                  :1;	//4 //1' : window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1' : window0 area only
	UINT32 window1_enable                   :1;	//6 //1' : window1 area only
	UINT32 window_acquire                   :1;	//7 //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 color_region0_sel                :1;	//8 //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//9 //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//10 //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//11 //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//12 //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//13 //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//14 //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//15 //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//16 //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//17 //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//18 //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//19 //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//20 //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//21 //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//22 //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//23 //1' : enable Color Region 15 selection
	UINT32 dce_domain_sel                   :1;	//24 //0' : KTD/QTD(default)(K only)	'1' : YC (Y only)
	UINT32 resvd0                           :1;
	UINT32 window_mode_enable               :1;	//26 //1' : window mode enable
	UINT32 window_inout_sel                 :1;	//27 //0' : selected area by window0, window1	'1' : otherside
	UINT32 histogram_mode                   :2;	//29:28	//00' : Own side's histogram data use	'01' : Other side's histogram data use	'10' : Average between Own and Other side's histogram data use
	UINT32 resvd1                           :2;
	};
	};
}PE_F20_PE1_DCE_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0342770 RW
	UINT32 dynamic_saturation_en            :1;	//0 //0' : disable	'1' : enable
	UINT32 window_mode_enable               :1;	//1 //1' : window mode enable
	UINT32 window_inout_sel                 :1;	//2 //0' : selected area by window0, window1	'1' : otherside
	UINT32 resvd0                           :1;
	UINT32 window01_enable                  :1;	//4 //1' : window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1' : window0 area only
	UINT32 window1_enable                   :1;	//6 //1' : window1 area only
	UINT32 window_acquire                   :1;	//7 //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 color_region0_sel                :1;	//8 //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//9 //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//10 //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//11 //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//12 //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//13 //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//14 //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//15 //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//16 //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//17 //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//18 //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//19 //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//20 //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//21 //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//22 //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//23 //1' : enable Color Region 15 selection
	UINT32 resvd1                           :8;
	};
	};
}PE_F20_PE1_DSE_CTRL_00_T;

typedef struct
{
	PE_F20_PE1_DCE_CTRL_00_T                    pe1_dce_ctrl_00;	//0xF0342720
	PE_F20_PE1_DSE_CTRL_00_T                    pe1_dse_ctrl_00;	//0xF0342770
}PE_CHPI_CCO_TBL_F20_T;

#endif

