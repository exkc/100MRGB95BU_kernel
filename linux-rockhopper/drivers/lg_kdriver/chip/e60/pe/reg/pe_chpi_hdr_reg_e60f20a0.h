#ifndef _PE_CHPI_HDR_REG_E60F20A0_H_
#define _PE_CHPI_HDR_REG_E60F20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A14 RW
	UINT32 hif_llut0_wdata_x_33rd           :32;	//31:0	//X coordinate of 33rd control point
	};
	};
}PE_E60F20_HDR_LLUT0_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A18 RW
	UINT32 hif_llut0_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_HDR_LLUT0_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A20 RW
	UINT32 hif_llut0_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_HDR_LLUT0_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A24 RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_HDR_LLUT0_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A44 RW
	UINT32 hif_llut1_wdata_x_33rd           :32;	//31:0	//X coordinate of 33rd control point
	};
	};
}PE_E60F20_HDR_LLUT1_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A48 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_HDR_LLUT1_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A50 RW
	UINT32 hif_llut1_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut1_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut1_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut1_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut1_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut1_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_HDR_LLUT1_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A54 RW
	UINT32 hif_llut1_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_HDR_LLUT1_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A74 RW
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
	};
}PE_E60F20_HDR_LLUT2_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A78 RW
	UINT32 hif_llut2_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
	};
}PE_E60F20_HDR_LLUT2_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A80 RW
	UINT32 hif_llut2_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut2_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut2_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut2_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut2_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_HDR_LLUT2_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205A84 RW
	UINT32 hif_llut2_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_HDR_LLUT2_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205CE4 RW
	UINT32 hif_llut0_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut0_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
	};
}PE_E60F20_SDR2HDR_LLUT0_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205CE8 RW
	UINT32 hif_llut0_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_SDR2HDR_LLUT0_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205CEC RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_SDR2HDR_LLUT0_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205D04 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut1_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
	};
}PE_E60F20_SDR2HDR_LLUT1_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205D08 RW
	UINT32 hif_llut1_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut1_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut1_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut1_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut1_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut1_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_SDR2HDR_LLUT1_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205D0C RW
	UINT32 hif_llut1_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_SDR2HDR_LLUT1_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205D64 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut0_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
	};
}PE_E60F20_SDR2HDR_FBSLUT_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205D68 RW
	UINT32 hif_llut0_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
	};
}PE_E60F20_SDR2HDR_FBSLUT_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205D6C RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_HDR_FBS_LUT_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B34 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//15:0	//Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//31:16	//X coordinate of 33rd control point (Default : 65535)
	};
	};
}PE_E60F20_HDR_YGAIN_LUT_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B38 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
	};
}PE_E60F20_HDR_YGAIN_LUT_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B3C RW
	UINT32 hif_ygain_lut_wdata_y            :16;	//15:0	//Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//31:16	//X coordinate of control point
	};
	};
}PE_E60F20_HDR_YGAIN_LUT_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02058D0 RW
	UINT32 reg_hue_prsv_en                  :1;	//0 //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//1 //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//13:4	//0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//25:16	//0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
	};
}PE_E60F20_HDR_HUE_SAT_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B60 RW
	UINT32 lgain_lut_y0                     :8;	//7:0	//y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//31:16	//x value of LGAIN LUT point 0
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B64 RW
	UINT32 lgain_lut_y1                     :8;	//7:0	//y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//31:16	//x value of LGAIN LUT point 1
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B68 RW
	UINT32 lgain_lut_y2                     :8;	//7:0	//y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//31:16	//x value of LGAIN LUT point 2
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B6C RW
	UINT32 lgain_lut_y3                     :8;	//7:0	//y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//31:16	//x value of LGAIN LUT point 3
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B70 RW
	UINT32 lgain_lut_y4                     :8;	//7:0	//y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//31:16	//x value of LGAIN LUT point 4
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B74 RW
	UINT32 lgain_lut_y5                     :8;	//7:0	//y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//31:16	//x value of LGAIN LUT point 5
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B78 RW
	UINT32 lgain_lut_y6                     :8;	//7:0	//y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//31:16	//x value of LGAIN LUT point 6
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B7C RW
	UINT32 lgain_lut_y7                     :8;	//7:0	//y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//31:16	//x value of LGAIN LUT point 7
	};
	};
}PE_E60F20_HDR_LGAIN_LUT_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B80 RW
	UINT32 sgain_lut_y0                     :8;	//7:0	//y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//31:16	//x value of SGAIN LUT point 0
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF0205B84 RW
	UINT32 sgain_lut_y1                     :8;	//7:0	//y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//31:16	//x value of SGAIN LUT point 1
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	 union {
	UINT32 udata32;
	struct {						//0xF0205B88 RW
	UINT32 sgain_lut_y2                     :8;	//7:0	//y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//31:16	//x value of SGAIN LUT point 2
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B8C RW
	UINT32 sgain_lut_y3                     :8;	//7:0	//y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//31:16	//x value of SGAIN LUT point 3
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B90 RW
	UINT32 sgain_lut_y4                     :8;	//7:0	//y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//31:16	//x value of SGAIN LUT point 4
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B94 RW
	UINT32 sgain_lut_y5                     :8;	//7:0	//y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//31:16	//x value of SGAIN LUT point 5
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B98 RW
	UINT32 sgain_lut_y6                     :8;	//7:0	//y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//31:16	//x value of SGAIN LUT point 6
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0205B9C RW
	UINT32 sgain_lut_y7                     :8;	//7:0	//y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//31:16	//x value of SGAIN LUT point 7
	};
	};
}PE_E60F20_HDR_SGAIN_LUT_CTRL_07_T;


typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02058A4 RW
	UINT32 r_pcc_coef1                      :15;	//14:0	//PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//30:16	//PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
	};
}PE_E60F20_HDR_PCC_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02058A8 RW
	UINT32 r_pcc_coef3                      :15;	//14:0	//PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//30:16	//PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
	};
}PE_E60F20_HDR_PCC_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02058AC RW
	UINT32 r_pcc_coef5                      :15;	//14:0	//PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//30:16	//PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
	};
}PE_E60F20_HDR_PCC_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02058B0 RW
	UINT32 r_pcc_coef7                      :15;	//14:0	//PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//30:16	//PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
	};
}PE_E60F20_HDR_PCC_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF02058B4 RW
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//30:16	//PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
	};
}PE_E60F20_HDR_PCC_CTRL_05_T;

#ifdef PE_CHPI_DEF_E60F20_USE_REG
typedef struct
{
	PE_E60F20_HDR_LLUT0_IA_CTRL_T                 hdr_llut0_ia_ctrl_x;	//0xF0205A20
	PE_E60F20_HDR_LLUT1_IA_CTRL_T                 hdr_llut1_ia_ctrl_x;	//0xF0205A50
	PE_E60F20_HDR_LLUT2_IA_CTRL_T                 hdr_llut2_ia_ctrl_x;	//0xF0205A80
	PE_E60F20_HDR_LLUT0_IA_DATA_T                 hdr_llut0_ia_data_x[32];	//0xF0205A24
	PE_E60F20_HDR_LLUT1_IA_DATA_T                 hdr_llut1_ia_data_x[32];	//0xF0205A54
	PE_E60F20_HDR_LLUT2_IA_DATA_T                 hdr_llut2_ia_data_x[32];	//0xF0205A84
	PE_E60F20_HDR_LLUT0_CTRL_05_T                 hdr_llut0_ctrl_05;	//0xF0205A14
	PE_E60F20_HDR_LLUT1_CTRL_05_T                 hdr_llut1_ctrl_05;	//0xF0205A44
	PE_E60F20_HDR_LLUT2_CTRL_05_T                 hdr_llut2_ctrl_05;	//0xF0205A74
	PE_E60F20_HDR_LLUT0_IA_CTRL_T                 hdr_llut0_ia_ctrl_y;	//0xF0205A20
	PE_E60F20_HDR_LLUT1_IA_CTRL_T                 hdr_llut1_ia_ctrl_y;	//0xF0205A50
	PE_E60F20_HDR_LLUT2_IA_CTRL_T                 hdr_llut2_ia_ctrl_y;	//0xF0205A80
	PE_E60F20_HDR_LLUT0_IA_DATA_T                 hdr_llut0_ia_data_y[32];	//0xF0205A24
	PE_E60F20_HDR_LLUT1_IA_DATA_T                 hdr_llut1_ia_data_y[32];	//0xF0205A54
	PE_E60F20_HDR_LLUT2_IA_DATA_T                 hdr_llut2_ia_data_y[32];	//0xF0205A84
	PE_E60F20_HDR_LLUT0_CTRL_06_T                 hdr_llut0_ctrl_06;	//0xF0205A18
	PE_E60F20_HDR_LLUT1_CTRL_06_T                 hdr_llut1_ctrl_06;	//0xF0205A48
	PE_E60F20_HDR_LLUT2_CTRL_06_T                 hdr_llut2_ctrl_06;	//0xF0205A78
	PE_E60F20_HDR_LLUT0_IA_CTRL_T                 hdr_llut0_ia_ctrl_e;	//0xF0205A20
	PE_E60F20_HDR_LLUT1_IA_CTRL_T                 hdr_llut1_ia_ctrl_e;	//0xF0205A50
	PE_E60F20_HDR_LLUT2_IA_CTRL_T                 hdr_llut2_ia_ctrl_e;	//0xF0205A80
}PE_CHPI_HDR_TM_E60F20_T;

typedef struct
{
	PE_E60F20_SDR2HDR_LLUT0_IA_CTRL_T             sdr2hdr_llut0_ia_ctrl_s;	//0xF0205CE8
	PE_E60F20_SDR2HDR_LLUT1_IA_CTRL_T             sdr2hdr_llut1_ia_ctrl_s;	//0xF0205D08
	PE_E60F20_SDR2HDR_FBSLUT_IA_CTRL_T            sdr2hdr_fbslut_ia_ctrl_s;	//0xF0205D68
	PE_E60F20_SDR2HDR_LLUT1_IA_DATA_T             sdr2hdr_llut1_ia_data[32];	//0xF0205D0C
	PE_E60F20_SDR2HDR_LLUT0_IA_DATA_T             sdr2hdr_llut0_ia_data[32];	//0xF0205CEC
	PE_E60F20_HDR_FBS_LUT_IA_DATA_T               hdr_fbs_lut_ia_data[32];	//0xF0205D6C
	PE_E60F20_SDR2HDR_LLUT0_IA_CTRL_T             sdr2hdr_llut0_ia_ctrl_e;	//0xF0205CE8
	PE_E60F20_SDR2HDR_LLUT1_IA_CTRL_T             sdr2hdr_llut1_ia_ctrl_e;	//0xF0205D08
	PE_E60F20_SDR2HDR_FBSLUT_IA_CTRL_T            sdr2hdr_fbslut_ia_ctrl_e;	//0xF0205D68
	PE_E60F20_SDR2HDR_LLUT0_CTRL_05_T             sdr2hdr_llut0_ctrl_05;	//0xF0205CE4
	PE_E60F20_SDR2HDR_LLUT1_CTRL_05_T             sdr2hdr_llut1_ctrl_05;	//0xF0205D04
	PE_E60F20_SDR2HDR_FBSLUT_CTRL_05_T            sdr2hdr_fbslut_ctrl_05;	//0xF0205D64
}PE_CHPI_HDR_S2H_E60F20_T;

typedef struct
{
	PE_E60F20_HDR_YGAIN_LUT_IA_CTRL_T             hdr_ygain_lut_ia_ctrl_s;	//0xF0205B38
	PE_E60F20_HDR_YGAIN_LUT_IA_DATA_T             hdr_ygain_lut_ia_data[32];	//0xF0205B3C
	PE_E60F20_HDR_YGAIN_LUT_IA_CTRL_T             hdr_ygain_lut_ia_ctrl_e;	//0xF0205B38
	PE_E60F20_HDR_YGAIN_LUT_CTRL_05_T             hdr_ygain_lut_ctrl_05;	//0xF0205B34
}PE_CHPI_HDR_YG_E60F20_T;

typedef struct
{
	PE_E60F20_HDR_HUE_SAT_CTRL_T                  hdr_hue_sat_ctrl;	//0xF02058D0
	PE_E60F20_HDR_LGAIN_LUT_CTRL_00_T             hdr_lgain_lut_ctrl_00;	//0xF0205B60
	PE_E60F20_HDR_LGAIN_LUT_CTRL_01_T             hdr_lgain_lut_ctrl_01;	//0xF0205B64
	PE_E60F20_HDR_LGAIN_LUT_CTRL_02_T             hdr_lgain_lut_ctrl_02;	//0xF0205B68
	PE_E60F20_HDR_LGAIN_LUT_CTRL_03_T             hdr_lgain_lut_ctrl_03;	//0xF0205B6C
	PE_E60F20_HDR_LGAIN_LUT_CTRL_04_T             hdr_lgain_lut_ctrl_04;	//0xF0205B70
	PE_E60F20_HDR_LGAIN_LUT_CTRL_05_T             hdr_lgain_lut_ctrl_05;	//0xF0205B74
	PE_E60F20_HDR_LGAIN_LUT_CTRL_06_T             hdr_lgain_lut_ctrl_06;	//0xF0205B78
	PE_E60F20_HDR_LGAIN_LUT_CTRL_07_T             hdr_lgain_lut_ctrl_07;	//0xF0205B7C
	PE_E60F20_HDR_SGAIN_LUT_CTRL_00_T             hdr_sgain_lut_ctrl_00;	//0xF0205B80
	PE_E60F20_HDR_SGAIN_LUT_CTRL_01_T             hdr_sgain_lut_ctrl_01;	//0xF0205B84
	PE_E60F20_HDR_SGAIN_LUT_CTRL_02_T             hdr_sgain_lut_ctrl_02;	//0xF0205B88
	PE_E60F20_HDR_SGAIN_LUT_CTRL_03_T             hdr_sgain_lut_ctrl_03;	//0xF0205B8C
	PE_E60F20_HDR_SGAIN_LUT_CTRL_04_T             hdr_sgain_lut_ctrl_04;	//0xF0205B90
	PE_E60F20_HDR_SGAIN_LUT_CTRL_05_T             hdr_sgain_lut_ctrl_05;	//0xF0205B94
	PE_E60F20_HDR_SGAIN_LUT_CTRL_06_T             hdr_sgain_lut_ctrl_06;	//0xF0205B98
	PE_E60F20_HDR_SGAIN_LUT_CTRL_07_T             hdr_sgain_lut_ctrl_07;	//0xF0205B9C
}PE_CHPI_HDR_HS_E60F20_T;

typedef struct
{
	PE_E60F20_HDR_PCC_CTRL_01_T                   hdr_pcc_ctrl_01;	//0xF02058A4
	PE_E60F20_HDR_PCC_CTRL_02_T                   hdr_pcc_ctrl_02;	//0xF02058A8
	PE_E60F20_HDR_PCC_CTRL_03_T                   hdr_pcc_ctrl_03;	//0xF02058AC
	PE_E60F20_HDR_PCC_CTRL_04_T                   hdr_pcc_ctrl_04;	//0xF02058B0
	PE_E60F20_HDR_PCC_CTRL_05_T                   hdr_pcc_ctrl_05;	//0xF02058B4
}PE_CHPI_HDR_PCC_E60F20_T;

#else

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	PE_E60F20_HDR_LLUT0_IA_CTRL_T                 hdr_llut0_ia_ctrl_x;	//0xF0205A20
	PE_E60F20_HDR_LLUT1_IA_CTRL_T                 hdr_llut1_ia_ctrl_x;	//0xF0205A50
	PE_E60F20_HDR_LLUT2_IA_CTRL_T                 hdr_llut2_ia_ctrl_x;	//0xF0205A80
	PE_E60F20_HDR_LLUT0_IA_DATA_T                 hdr_llut0_ia_data_x[32];	//0xF0205A24
	PE_E60F20_HDR_LLUT1_IA_DATA_T                 hdr_llut1_ia_data_x[32];	//0xF0205A54
	PE_E60F20_HDR_LLUT2_IA_DATA_T                 hdr_llut2_ia_data_x[32];	//0xF0205A84
	PE_E60F20_HDR_LLUT0_CTRL_05_T                 hdr_llut0_ctrl_05;	//0xF0205A14
	PE_E60F20_HDR_LLUT1_CTRL_05_T                 hdr_llut1_ctrl_05;	//0xF0205A44
	PE_E60F20_HDR_LLUT2_CTRL_05_T                 hdr_llut2_ctrl_05;	//0xF0205A74
	PE_E60F20_HDR_LLUT0_IA_CTRL_T                 hdr_llut0_ia_ctrl_y;	//0xF0205A20
	PE_E60F20_HDR_LLUT1_IA_CTRL_T                 hdr_llut1_ia_ctrl_y;	//0xF0205A50
	PE_E60F20_HDR_LLUT2_IA_CTRL_T                 hdr_llut2_ia_ctrl_y;	//0xF0205A80
	PE_E60F20_HDR_LLUT0_IA_DATA_T                 hdr_llut0_ia_data_y[32];	//0xF0205A24
	PE_E60F20_HDR_LLUT1_IA_DATA_T                 hdr_llut1_ia_data_y[32];	//0xF0205A54
	PE_E60F20_HDR_LLUT2_IA_DATA_T                 hdr_llut2_ia_data_y[32];	//0xF0205A84
	PE_E60F20_HDR_LLUT0_CTRL_06_T                 hdr_llut0_ctrl_06;	//0xF0205A18
	PE_E60F20_HDR_LLUT1_CTRL_06_T                 hdr_llut1_ctrl_06;	//0xF0205A48
	PE_E60F20_HDR_LLUT2_CTRL_06_T                 hdr_llut2_ctrl_06;	//0xF0205A78
	PE_E60F20_HDR_LLUT0_IA_CTRL_T                 hdr_llut0_ia_ctrl_e;	//0xF0205A20
	PE_E60F20_HDR_LLUT1_IA_CTRL_T                 hdr_llut1_ia_ctrl_e;	//0xF0205A50
	PE_E60F20_HDR_LLUT2_IA_CTRL_T                 hdr_llut2_ia_ctrl_e;	//0xF0205A80
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_HDR_TM_E60F20_T;

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	PE_E60F20_SDR2HDR_LLUT0_IA_CTRL_T             sdr2hdr_llut0_ia_ctrl_s;	//0xF0205CE8
	PE_E60F20_SDR2HDR_LLUT1_IA_CTRL_T             sdr2hdr_llut1_ia_ctrl_s;	//0xF0205D08
	PE_E60F20_SDR2HDR_FBSLUT_IA_CTRL_T            sdr2hdr_fbslut_ia_ctrl_s;	//0xF0205D68
	PE_E60F20_SDR2HDR_LLUT1_IA_DATA_T             sdr2hdr_llut1_ia_data[32];	//0xF0205D0C
	PE_E60F20_SDR2HDR_LLUT0_IA_DATA_T             sdr2hdr_llut0_ia_data[32];	//0xF0205CEC
	PE_E60F20_HDR_FBS_LUT_IA_DATA_T               hdr_fbs_lut_ia_data[32];	//0xF0205D6C
	PE_E60F20_SDR2HDR_LLUT0_IA_CTRL_T             sdr2hdr_llut0_ia_ctrl_e;	//0xF0205CE8
	PE_E60F20_SDR2HDR_LLUT1_IA_CTRL_T             sdr2hdr_llut1_ia_ctrl_e;	//0xF0205D08
	PE_E60F20_SDR2HDR_FBSLUT_IA_CTRL_T            sdr2hdr_fbslut_ia_ctrl_e;	//0xF0205D68
	PE_E60F20_SDR2HDR_LLUT0_CTRL_05_T             sdr2hdr_llut0_ctrl_05;	//0xF0205CE4
	PE_E60F20_SDR2HDR_LLUT1_CTRL_05_T             sdr2hdr_llut1_ctrl_05;	//0xF0205D04
	PE_E60F20_SDR2HDR_FBSLUT_CTRL_05_T            sdr2hdr_fbslut_ctrl_05;	//0xF0205D64
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_HDR_S2H_E60F20_T;

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	PE_E60F20_HDR_YGAIN_LUT_IA_CTRL_T             hdr_ygain_lut_ia_ctrl_s;	//0xF0205B38
	PE_E60F20_HDR_YGAIN_LUT_IA_DATA_T             hdr_ygain_lut_ia_data[32];	//0xF0205B3C
	PE_E60F20_HDR_YGAIN_LUT_IA_CTRL_T             hdr_ygain_lut_ia_ctrl_e;	//0xF0205B38
	PE_E60F20_HDR_YGAIN_LUT_CTRL_05_T             hdr_ygain_lut_ctrl_05;	//0xF0205B34
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_HDR_YG_E60F20_T;

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	PE_E60F20_HDR_HUE_SAT_CTRL_T                  hdr_hue_sat_ctrl;	//0xF02058D0
	PE_E60F20_HDR_LGAIN_LUT_CTRL_00_T             hdr_lgain_lut_ctrl_00;	//0xF0205B60
	PE_E60F20_HDR_LGAIN_LUT_CTRL_01_T             hdr_lgain_lut_ctrl_01;	//0xF0205B64
	PE_E60F20_HDR_LGAIN_LUT_CTRL_02_T             hdr_lgain_lut_ctrl_02;	//0xF0205B68
	PE_E60F20_HDR_LGAIN_LUT_CTRL_03_T             hdr_lgain_lut_ctrl_03;	//0xF0205B6C
	PE_E60F20_HDR_LGAIN_LUT_CTRL_04_T             hdr_lgain_lut_ctrl_04;	//0xF0205B70
	PE_E60F20_HDR_LGAIN_LUT_CTRL_05_T             hdr_lgain_lut_ctrl_05;	//0xF0205B74
	PE_E60F20_HDR_LGAIN_LUT_CTRL_06_T             hdr_lgain_lut_ctrl_06;	//0xF0205B78
	PE_E60F20_HDR_LGAIN_LUT_CTRL_07_T             hdr_lgain_lut_ctrl_07;	//0xF0205B7C
	PE_E60F20_HDR_SGAIN_LUT_CTRL_00_T             hdr_sgain_lut_ctrl_00;	//0xF0205B80
	PE_E60F20_HDR_SGAIN_LUT_CTRL_01_T             hdr_sgain_lut_ctrl_01;	//0xF0205B84
	PE_E60F20_HDR_SGAIN_LUT_CTRL_02_T             hdr_sgain_lut_ctrl_02;	//0xF0205B88
	PE_E60F20_HDR_SGAIN_LUT_CTRL_03_T             hdr_sgain_lut_ctrl_03;	//0xF0205B8C
	PE_E60F20_HDR_SGAIN_LUT_CTRL_04_T             hdr_sgain_lut_ctrl_04;	//0xF0205B90
	PE_E60F20_HDR_SGAIN_LUT_CTRL_05_T             hdr_sgain_lut_ctrl_05;	//0xF0205B94
	PE_E60F20_HDR_SGAIN_LUT_CTRL_06_T             hdr_sgain_lut_ctrl_06;	//0xF0205B98
	PE_E60F20_HDR_SGAIN_LUT_CTRL_07_T             hdr_sgain_lut_ctrl_07;	//0xF0205B9C
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_HDR_HS_E60F20_T;

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	PE_E60F20_HDR_PCC_CTRL_01_T                   hdr_pcc_ctrl_01;	//0xF02058A4
	PE_E60F20_HDR_PCC_CTRL_02_T                   hdr_pcc_ctrl_02;	//0xF02058A8
	PE_E60F20_HDR_PCC_CTRL_03_T                   hdr_pcc_ctrl_03;	//0xF02058AC
	PE_E60F20_HDR_PCC_CTRL_04_T                   hdr_pcc_ctrl_04;	//0xF02058B0
	PE_E60F20_HDR_PCC_CTRL_05_T                   hdr_pcc_ctrl_05;	//0xF02058B4
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_HDR_PCC_E60F20_T;
#endif

#endif
