#ifndef _PE_GSC_REG_M23A0_1_H_
#define _PE_GSC_REG_M23A0_1_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC830500 RW 0x0000_0000
	UINT32 reg_mif_rd_on_g0                 :1;	//(0,NA,0x0) //'0' : MIF pre-read off (= select FMC direct source)	    '1' : MIF pre-read on  (= select MIF RD source )
	UINT32 resvd0                           :2;
	UINT32 reg_vsc_mode_g0                  :1;	//(3,NA,0x0) //Don't used
	UINT32 resvd1                           :1;
	UINT32 reg_bilinear_on_g0               :1;	//(5,NA,0x0) //Don't used
	UINT32 resvd2                           :8;
	UINT32 reg_blur_flag_debug_g0           :1;	//(14,NA,0x0) //for debug	1:data MSB flag swap out
	UINT32 reg_blur_flag_bypass_g0          :1;	//(15,NA,0x0) //'0' : normal operation 	     '1' : LSB 1bit blur flag enable mode
	UINT32 resvd3                           :9;
	UINT32 reg_v_reverse_sm_g0              :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd4                           :4;
	UINT32 reg_mode_32p_g0                  :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g0             :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_M23_GSC_Y_GSC_G0_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830504 RW 0x0000_0000
	UINT32 reg_hsize_g0                     :14;	//(13:0,NA,0x0) //G0 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g0                     :14;	//(29:16,NA,0x0) //G0 MRd size info. V
	UINT32 reg_vinc_g0                      :2;	//(31:30,NA,0x0) //V increment for G0 MRD
	};
}PE_M23_GSC_Y_GSC_G0_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830508 RW 0x0870_0F00
	UINT32 reg_hosize_g0                    :13;	//(12:0,NA,0xF00) //width
	UINT32 resvd0                           :3;
	UINT32 reg_vosize_g0                    :13;	//(28:16,NA,0x870) //height
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830510 RW VNA
	UINT32 lmux_sel                         :1;	//(0,NA,0x0) //Left input mux select	    '0': G0 MIF RD 	    '1': Disp FMC
	UINT32 rmux_sel                         :1;	//(1,NA,0x0) //Right input mux select	    '0': G1 MIF RD 	    '1': Disp FMC
	UINT32 inverse_en                       :1;	//(2,NA,0x0) //Input Switch reverse ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC1   /   Right MUX -> GSC0
	UINT32 l_share_en                       :1;	//(3,NA,0x0) //Input Switch share ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC0   /   Left  MUX -> GSC1
	UINT32 r_share_en                       :1;	//(4,NA,0x0) //Input Switch share ctrl	    '0': Left  MUX -> GSC0   /   Right MUX -> GSC1	    '1': Right MUX -> GSC0   /   Right MUX -> GSC1
	UINT32 share_flow_ctrl_en               :1;	//(5,NA,0x0) //flow control enable for share mode
	UINT32 lmux_sel2                        :1;	//(6,NA,0x0) //Left input mux2 select	    '0': output of lmux	    '1': gpd0
	UINT32 rmux_sel2                        :1;	//(7,NA,0x0) //Right input mux2 select	    '0': output of rmux	    '1': gpd1
	UINT32 resvd                            :24;
	};
}PE_M23_GSC_Y_GSC_G0_Y_INPUT_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830514 RW 0x0000_0000
	UINT32 reg_hoffset_g0                   :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset_g0                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830518 RW 0x0870_0F00
	UINT32 reg_hactive_g0                   :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive_g0                   :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC83051C RW 0x0870_0F00
	UINT32 reg_hisize_g0                    :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize_g0                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830520 RW 0x0000_0000
	UINT32 reg_phase_off_v_g0               :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g0               :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_M23_GSC_Y_GSC_G0_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830524 RW 0x0000_0000
	UINT32 reg_denominator_h_g0             :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830528 RW 0x0000_0000
	UINT32 reg_denominator_v_g0             :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC83052C RW 0x0000_0000
	UINT32 reg_post_hoffset_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en_g0              :1;	//(31,NA,0x0) //output crop enable
	};
}PE_M23_GSC_Y_GSC_G0_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830530 RW 0x0000_0000
	UINT32 reg_post_hactive_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830534 RW 0x0000_0000
	UINT32 reg_post_hisize_g0               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize_g0               :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830538 RW 0x0000_0000
	UINT32 reg_mif_rd_hoffset_g0            :13;	//(12:0,NA,0x0) //MRD H offset
	UINT32 resvd0                           :3;
	UINT32 reg_mif_rd_voffset_g0            :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_Y_GSC_G0_Y_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC83053C RW 0x0000_0000
	UINT32 reg_frc_fail_timer_g0            :32;	//(31:0,NA,0x0) //0 : fail timer off
	};
}PE_M23_GSC_Y_GSC_G0_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8306E0 RO 0x0000_0000
	UINT32 vcnt_in_g0                       :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_M23_GSC_Y_GSC_G0_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8306E4 RO 0x0000_0000
	UINT32 vcnt_out_g0                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_M23_GSC_Y_GSC_G0_VCNT_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8306E8 RO 0x0000_0000
	UINT32 fmc_timer_g0                     :32;	//(31:0,NA,0x0) //clk count from GSC picinit to FMC first valid
	};
}PE_M23_GSC_Y_GSC_G0_FMC_TIMER_CNT_T;

typedef struct {
	PE_M23_GSC_Y_GSC_G0_Y_CTRL_T                             gsc_g0_y_ctrl;	//0xCC830500
	PE_M23_GSC_Y_GSC_G0_Y_MIF_RD_SIZE_T               gsc_g0_y_mif_rd_size;	//0xCC830504
	PE_M23_GSC_Y_GSC_G0_Y_OUTSIZE_T                       gsc_g0_y_outsize;	//0xCC830508
	UINT32                                                    reserved0;	//0xCC83050C
	PE_M23_GSC_Y_GSC_G0_Y_INPUT_MUX_T                   gsc_g0_y_input_mux;	//0xCC830510
	PE_M23_GSC_Y_GSC_G0_Y_CROP_PARAM1_T               gsc_g0_y_crop_param1;	//0xCC830514
	PE_M23_GSC_Y_GSC_G0_Y_CROP_PARAM2_T               gsc_g0_y_crop_param2;	//0xCC830518
	PE_M23_GSC_Y_GSC_G0_Y_CROP_PARAM3_T               gsc_g0_y_crop_param3;	//0xCC83051C
	PE_M23_GSC_Y_GSC_G0_Y_PHASE_OFFSET_T             gsc_g0_y_phase_offset;	//0xCC830520
	PE_M23_GSC_Y_GSC_G0_Y_SAMPLING_H_T                 gsc_g0_y_sampling_h;	//0xCC830524
	PE_M23_GSC_Y_GSC_G0_Y_SAMPLING_V_T                 gsc_g0_y_sampling_v;	//0xCC830528
	PE_M23_GSC_Y_GSC_G0_Y_POST_CROP_PARAM1_T     gsc_g0_y_post_crop_param1;	//0xCC83052C
	PE_M23_GSC_Y_GSC_G0_Y_POST_CROP_PARAM2_T     gsc_g0_y_post_crop_param2;	//0xCC830530
	PE_M23_GSC_Y_GSC_G0_Y_POST_CROP_PARAM3_T     gsc_g0_y_post_crop_param3;	//0xCC830534
	PE_M23_GSC_Y_GSC_G0_Y_MIF_RD_HOFFSET_T         gsc_g0_y_mif_rd_hoffset;	//0xCC830538
	PE_M23_GSC_Y_GSC_G0_FRC_FAIL_TIMER_T             gsc_g0_frc_fail_timer;	//0xCC83053C
	UINT32                                                    reserved1;	//0xCC830540
	UINT32                                                    reserved2;	//0xCC830544
	UINT32                                                    reserved3;	//0xCC830548
	UINT32                                                    reserved4;	//0xCC83054C
	UINT32                                                    reserved5;	//0xCC830550
	UINT32                                                    reserved6;	//0xCC830554
	UINT32                                                    reserved7;	//0xCC830558
	UINT32                                                    reserved8;	//0xCC83055C
	UINT32                                                    reserved9;	//0xCC830560
	UINT32                                                   reserved10;	//0xCC830564
	UINT32                                                   reserved11;	//0xCC830568
	UINT32                                                   reserved12;	//0xCC83056C
	UINT32                                                   reserved13;	//0xCC830570
	UINT32                                                   reserved14;	//0xCC830574
	UINT32                                                   reserved15;	//0xCC830578
	UINT32                                                   reserved16;	//0xCC83057C
	UINT32                                                   reserved17;	//0xCC830580
	UINT32                                                   reserved18;	//0xCC830584
	UINT32                                                   reserved19;	//0xCC830588
	UINT32                                                   reserved20;	//0xCC83058C
	UINT32                                                   reserved21;	//0xCC830590
	UINT32                                                   reserved22;	//0xCC830594
	UINT32                                                   reserved23;	//0xCC830598
	UINT32                                                   reserved24;	//0xCC83059C
	UINT32                                                   reserved25;	//0xCC8305A0
	UINT32                                                   reserved26;	//0xCC8305A4
	UINT32                                                   reserved27;	//0xCC8305A8
	UINT32                                                   reserved28;	//0xCC8305AC
	UINT32                                                   reserved29;	//0xCC8305B0
	UINT32                                                   reserved30;	//0xCC8305B4
	UINT32                                                   reserved31;	//0xCC8305B8
	UINT32                                                   reserved32;	//0xCC8305BC
	UINT32                                                   reserved33;	//0xCC8305C0
	UINT32                                                   reserved34;	//0xCC8305C4
	UINT32                                                   reserved35;	//0xCC8305C8
	UINT32                                                   reserved36;	//0xCC8305CC
	UINT32                                                   reserved37;	//0xCC8305D0
	UINT32                                                   reserved38;	//0xCC8305D4
	UINT32                                                   reserved39;	//0xCC8305D8
	UINT32                                                   reserved40;	//0xCC8305DC
	UINT32                                                   reserved41;	//0xCC8305E0
	UINT32                                                   reserved42;	//0xCC8305E4
	UINT32                                                   reserved43;	//0xCC8305E8
	UINT32                                                   reserved44;	//0xCC8305EC
	UINT32                                                   reserved45;	//0xCC8305F0
	UINT32                                                   reserved46;	//0xCC8305F4
	UINT32                                                   reserved47;	//0xCC8305F8
	UINT32                                                   reserved48;	//0xCC8305FC
	UINT32                                                   reserved49;	//0xCC830600
	UINT32                                                   reserved50;	//0xCC830604
	UINT32                                                   reserved51;	//0xCC830608
	UINT32                                                   reserved52;	//0xCC83060C
	UINT32                                                   reserved53;	//0xCC830610
	UINT32                                                   reserved54;	//0xCC830614
	UINT32                                                   reserved55;	//0xCC830618
	UINT32                                                   reserved56;	//0xCC83061C
	UINT32                                                   reserved57;	//0xCC830620
	UINT32                                                   reserved58;	//0xCC830624
	UINT32                                                   reserved59;	//0xCC830628
	UINT32                                                   reserved60;	//0xCC83062C
	UINT32                                                   reserved61;	//0xCC830630
	UINT32                                                   reserved62;	//0xCC830634
	UINT32                                                   reserved63;	//0xCC830638
	UINT32                                                   reserved64;	//0xCC83063C
	UINT32                                                   reserved65;	//0xCC830640
	UINT32                                                   reserved66;	//0xCC830644
	UINT32                                                   reserved67;	//0xCC830648
	UINT32                                                   reserved68;	//0xCC83064C
	UINT32                                                   reserved69;	//0xCC830650
	UINT32                                                   reserved70;	//0xCC830654
	UINT32                                                   reserved71;	//0xCC830658
	UINT32                                                   reserved72;	//0xCC83065C
	UINT32                                                   reserved73;	//0xCC830660
	UINT32                                                   reserved74;	//0xCC830664
	UINT32                                                   reserved75;	//0xCC830668
	UINT32                                                   reserved76;	//0xCC83066C
	UINT32                                                   reserved77;	//0xCC830670
	UINT32                                                   reserved78;	//0xCC830674
	UINT32                                                   reserved79;	//0xCC830678
	UINT32                                                   reserved80;	//0xCC83067C
	UINT32                                                   reserved81;	//0xCC830680
	UINT32                                                   reserved82;	//0xCC830684
	UINT32                                                   reserved83;	//0xCC830688
	UINT32                                                   reserved84;	//0xCC83068C
	UINT32                                                   reserved85;	//0xCC830690
	UINT32                                                   reserved86;	//0xCC830694
	UINT32                                                   reserved87;	//0xCC830698
	UINT32                                                   reserved88;	//0xCC83069C
	UINT32                                                   reserved89;	//0xCC8306A0
	UINT32                                                   reserved90;	//0xCC8306A4
	UINT32                                                   reserved91;	//0xCC8306A8
	UINT32                                                   reserved92;	//0xCC8306AC
	UINT32                                                   reserved93;	//0xCC8306B0
	UINT32                                                   reserved94;	//0xCC8306B4
	UINT32                                                   reserved95;	//0xCC8306B8
	UINT32                                                   reserved96;	//0xCC8306BC
	UINT32                                                   reserved97;	//0xCC8306C0
	UINT32                                                   reserved98;	//0xCC8306C4
	UINT32                                                   reserved99;	//0xCC8306C8
	UINT32                                                  reserved100;	//0xCC8306CC
	UINT32                                                  reserved101;	//0xCC8306D0
	UINT32                                                  reserved102;	//0xCC8306D4
	UINT32                                                  reserved103;	//0xCC8306D8
	UINT32                                                  reserved104;	//0xCC8306DC
	PE_M23_GSC_Y_GSC_G0_VCNT_IN_T                           gsc_g0_vcnt_in;	//0xCC8306E0
	PE_M23_GSC_Y_GSC_G0_VCNT_OUT_T                         gsc_g0_vcnt_out;	//0xCC8306E4
	PE_M23_GSC_Y_GSC_G0_FMC_TIMER_CNT_T               gsc_g0_fmc_timer_cnt;	//0xCC8306E8
}PE_GSC_Y_REG_M23_T;



typedef union {
	UINT32 udata32;
	struct {						//0xCC830800 RW 0x0000_0000
	UINT32 reg_mif_rd_on_g0                 :1;	//(0,NA,0x0) //1이면 M1 MRd_2pel on & select mrd path (size 정보 필요)
	UINT32 resvd0                           :2;
	UINT32 reg_vsc_mode_g0                  :2;	//(4:3,NA,0x0) //Don't used
	UINT32 reg_bilinear_on_g0               :1;	//(5,NA,0x0) //Don't used
	UINT32 reg_mode_32p_g0                  :1;	//(6,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 resvd1                           :18;
	UINT32 reg_v_reverse_g0                 :1;	//(25,NA,0x0) //
	UINT32 resvd2                           :5;
	UINT32 reg_sampling_mode_g0             :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_M23_GSC_C_GSC_G0_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830804 RW 0x0000_0000
	UINT32 reg_hsize_g0                     :14;	//(13:0,NA,0x0) //G0 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g0                     :14;	//(29:16,NA,0x0) //G0 MRd size info. V
	UINT32 reg_vinc_g0                      :2;	//(31:30,NA,0x0) //V increment for G0 MRD
	};
}PE_M23_GSC_C_GSC_G0_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830808 RW 0x0870_0F00
	UINT32 reg_hosize_g0                    :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vosize_g0                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830810 RW VNA
	UINT32 lmux_sel                         :1;	//(0,NA,0x0) //Left input mux select	    '0': G0 MIF RD 	    '1': Disp FMC
	UINT32 rmux_sel                         :1;	//(1,NA,0x0) //Right input mux select	    '0': G1 MIF RD 	    '1': Disp FMC
	UINT32 inverse_en                       :1;	//(2,NA,0x0) //Input Switch reverse ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC1   /   Right MUX -> GSC0
	UINT32 l_share_en                       :1;	//(3,NA,0x0) //Input Switch share ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC0   /   Left  MUX -> GSC1
	UINT32 r_share_en                       :1;	//(4,NA,0x0) //Input Switch share ctrl	    '0': Left  MUX -> GSC0   /   Right MUX -> GSC1	    '1': Right MUX -> GSC0   /   Right MUX -> GSC1
	UINT32 share_flow_ctrl_en               :1;	//(5,NA,0x0) //flow control enable for share mode
	UINT32 lmux_sel2                        :1;	//(6,NA,0x0) //Left input mux2 select	    '0': output of lmux	    '1': gpd0
	UINT32 rmux_sel2                        :1;	//(7,NA,0x0) //Right input mux2 select	    '0': output of rmux	    '1': gpd1
	UINT32 resvd                            :24;
	};
}PE_M23_GSC_C_GSC_G0_C_INPUT_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830814 RW 0x0000_0000
	UINT32 reg_hoffset_g0                   :13;	//(12:0,NA,0x0) //오프셋
	UINT32 resvd0                           :3;
	UINT32 reg_voffset_g0                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830818 RW 0x0870_0F00
	UINT32 reg_hactive_g0                   :13;	//(12:0,NA,0xF00) //액티브
	UINT32 resvd0                           :3;
	UINT32 reg_vactive_g0                   :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC83081C RW 0x0870_0F00
	UINT32 reg_hisize_g0                    :13;	//(12:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :3;
	UINT32 reg_visize_g0                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830820 RW 0x0000_0000
	UINT32 reg_phase_off_v_g0               :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g0               :9;	//(24:16,NA,0x0) //-
	UINT32 resvd1                           :7;
	};
}PE_M23_GSC_C_GSC_G0_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830824 RW 0x0000_0000
	UINT32 reg_denominator_h_g0             :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830828 RW 0x0000_0000
	UINT32 reg_denominator_v_g0             :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC83082C RW 0x0000_0000
	UINT32 reg_post_hoffset_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en_g0              :1;	//(31,NA,0x0) //output crop enable
	};
}PE_M23_GSC_C_GSC_G0_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830830 RW 0x0000_0000
	UINT32 reg_post_hactive_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830834 RW 0x0000_0000
	UINT32 reg_post_hisize_g0               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize_g0               :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC830838 RW 0x0000_0000
	UINT32 reg_mif_rd_hoffset_g0            :13;	//(12:0,NA,0x0) //MRD H offset
	UINT32 resvd0                           :3;
	UINT32 reg_mif_rd_voffset_g0            :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :3;
	};
}PE_M23_GSC_C_GSC_G0_C_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC83083C RW 0x0000_0000
	UINT32 reg_frc_fail_timer_g0            :32;	//(31:0,NA,0x0) //0 : fail timer off
	};
}PE_M23_GSC_C_GSC_G0_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8309E0 RO 0x0000_0000
	UINT32 vcnt_in_g0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd                            :19;
	};
}PE_M23_GSC_C_GSC_G0_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8309E4 RO 0x0000_0000
	UINT32 vcnt_out_g0                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd                            :19;
	};
}PE_M23_GSC_C_GSC_G0_VCNT_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8309E8 RO 0x0000_0000
	UINT32 fmc_timer_g0                     :32;	//(31:0,NA,0x0) //clk count from GSC picinit to FMC first valid
	};
}PE_M23_GSC_C_GSC_G0_FMC_TIMER_CNT_T;

typedef struct {
	PE_M23_GSC_C_GSC_G0_C_CTRL_T                             gsc_g0_c_ctrl;	//0xCC830800
	PE_M23_GSC_C_GSC_G0_C_MIF_RD_SIZE_T               gsc_g0_c_mif_rd_size;	//0xCC830804
	PE_M23_GSC_C_GSC_G0_C_OUTSIZE_T                       gsc_g0_c_outsize;	//0xCC830808
	UINT32                                                    reserved0;	//0xCC83080C
	PE_M23_GSC_C_GSC_G0_C_INPUT_MUX_T                   gsc_g0_c_input_mux;	//0xCC830810
	PE_M23_GSC_C_GSC_G0_C_CROP_PARAM1_T               gsc_g0_c_crop_param1;	//0xCC830814
	PE_M23_GSC_C_GSC_G0_C_CROP_PARAM2_T               gsc_g0_c_crop_param2;	//0xCC830818
	PE_M23_GSC_C_GSC_G0_C_CROP_PARAM3_T               gsc_g0_c_crop_param3;	//0xCC83081C
	PE_M23_GSC_C_GSC_G0_C_PHASE_OFFSET_T             gsc_g0_c_phase_offset;	//0xCC830820
	PE_M23_GSC_C_GSC_G0_C_SAMPLING_H_T                 gsc_g0_c_sampling_h;	//0xCC830824
	PE_M23_GSC_C_GSC_G0_C_SAMPLING_V_T                 gsc_g0_c_sampling_v;	//0xCC830828
	PE_M23_GSC_C_GSC_G0_C_POST_CROP_PARAM1_T     gsc_g0_c_post_crop_param1;	//0xCC83082C
	PE_M23_GSC_C_GSC_G0_C_POST_CROP_PARAM2_T     gsc_g0_c_post_crop_param2;	//0xCC830830
	PE_M23_GSC_C_GSC_G0_C_POST_CROP_PARAM3_T     gsc_g0_c_post_crop_param3;	//0xCC830834
	PE_M23_GSC_C_GSC_G0_C_MIF_RD_HOFFSET_T         gsc_g0_c_mif_rd_hoffset;	//0xCC830838
	PE_M23_GSC_C_GSC_G0_FRC_FAIL_TIMER_T             gsc_g0_frc_fail_timer;	//0xCC83083C
	UINT32                                                    reserved1;	//0xCC830840
	UINT32                                                    reserved2;	//0xCC830844
	UINT32                                                    reserved3;	//0xCC830848
	UINT32                                                    reserved4;	//0xCC83084C
	UINT32                                                    reserved5;	//0xCC830850
	UINT32                                                    reserved6;	//0xCC830854
	UINT32                                                    reserved7;	//0xCC830858
	UINT32                                                    reserved8;	//0xCC83085C
	UINT32                                                    reserved9;	//0xCC830860
	UINT32                                                   reserved10;	//0xCC830864
	UINT32                                                   reserved11;	//0xCC830868
	UINT32                                                   reserved12;	//0xCC83086C
	UINT32                                                   reserved13;	//0xCC830870
	UINT32                                                   reserved14;	//0xCC830874
	UINT32                                                   reserved15;	//0xCC830878
	UINT32                                                   reserved16;	//0xCC83087C
	UINT32                                                   reserved17;	//0xCC830880
	UINT32                                                   reserved18;	//0xCC830884
	UINT32                                                   reserved19;	//0xCC830888
	UINT32                                                   reserved20;	//0xCC83088C
	UINT32                                                   reserved21;	//0xCC830890
	UINT32                                                   reserved22;	//0xCC830894
	UINT32                                                   reserved23;	//0xCC830898
	UINT32                                                   reserved24;	//0xCC83089C
	UINT32                                                   reserved25;	//0xCC8308A0
	UINT32                                                   reserved26;	//0xCC8308A4
	UINT32                                                   reserved27;	//0xCC8308A8
	UINT32                                                   reserved28;	//0xCC8308AC
	UINT32                                                   reserved29;	//0xCC8308B0
	UINT32                                                   reserved30;	//0xCC8308B4
	UINT32                                                   reserved31;	//0xCC8308B8
	UINT32                                                   reserved32;	//0xCC8308BC
	UINT32                                                   reserved33;	//0xCC8308C0
	UINT32                                                   reserved34;	//0xCC8308C4
	UINT32                                                   reserved35;	//0xCC8308C8
	UINT32                                                   reserved36;	//0xCC8308CC
	UINT32                                                   reserved37;	//0xCC8308D0
	UINT32                                                   reserved38;	//0xCC8308D4
	UINT32                                                   reserved39;	//0xCC8308D8
	UINT32                                                   reserved40;	//0xCC8308DC
	UINT32                                                   reserved41;	//0xCC8308E0
	UINT32                                                   reserved42;	//0xCC8308E4
	UINT32                                                   reserved43;	//0xCC8308E8
	UINT32                                                   reserved44;	//0xCC8308EC
	UINT32                                                   reserved45;	//0xCC8308F0
	UINT32                                                   reserved46;	//0xCC8308F4
	UINT32                                                   reserved47;	//0xCC8308F8
	UINT32                                                   reserved48;	//0xCC8308FC
	UINT32                                                   reserved49;	//0xCC830900
	UINT32                                                   reserved50;	//0xCC830904
	UINT32                                                   reserved51;	//0xCC830908
	UINT32                                                   reserved52;	//0xCC83090C
	UINT32                                                   reserved53;	//0xCC830910
	UINT32                                                   reserved54;	//0xCC830914
	UINT32                                                   reserved55;	//0xCC830918
	UINT32                                                   reserved56;	//0xCC83091C
	UINT32                                                   reserved57;	//0xCC830920
	UINT32                                                   reserved58;	//0xCC830924
	UINT32                                                   reserved59;	//0xCC830928
	UINT32                                                   reserved60;	//0xCC83092C
	UINT32                                                   reserved61;	//0xCC830930
	UINT32                                                   reserved62;	//0xCC830934
	UINT32                                                   reserved63;	//0xCC830938
	UINT32                                                   reserved64;	//0xCC83093C
	UINT32                                                   reserved65;	//0xCC830940
	UINT32                                                   reserved66;	//0xCC830944
	UINT32                                                   reserved67;	//0xCC830948
	UINT32                                                   reserved68;	//0xCC83094C
	UINT32                                                   reserved69;	//0xCC830950
	UINT32                                                   reserved70;	//0xCC830954
	UINT32                                                   reserved71;	//0xCC830958
	UINT32                                                   reserved72;	//0xCC83095C
	UINT32                                                   reserved73;	//0xCC830960
	UINT32                                                   reserved74;	//0xCC830964
	UINT32                                                   reserved75;	//0xCC830968
	UINT32                                                   reserved76;	//0xCC83096C
	UINT32                                                   reserved77;	//0xCC830970
	UINT32                                                   reserved78;	//0xCC830974
	UINT32                                                   reserved79;	//0xCC830978
	UINT32                                                   reserved80;	//0xCC83097C
	UINT32                                                   reserved81;	//0xCC830980
	UINT32                                                   reserved82;	//0xCC830984
	UINT32                                                   reserved83;	//0xCC830988
	UINT32                                                   reserved84;	//0xCC83098C
	UINT32                                                   reserved85;	//0xCC830990
	UINT32                                                   reserved86;	//0xCC830994
	UINT32                                                   reserved87;	//0xCC830998
	UINT32                                                   reserved88;	//0xCC83099C
	UINT32                                                   reserved89;	//0xCC8309A0
	UINT32                                                   reserved90;	//0xCC8309A4
	UINT32                                                   reserved91;	//0xCC8309A8
	UINT32                                                   reserved92;	//0xCC8309AC
	UINT32                                                   reserved93;	//0xCC8309B0
	UINT32                                                   reserved94;	//0xCC8309B4
	UINT32                                                   reserved95;	//0xCC8309B8
	UINT32                                                   reserved96;	//0xCC8309BC
	UINT32                                                   reserved97;	//0xCC8309C0
	UINT32                                                   reserved98;	//0xCC8309C4
	UINT32                                                   reserved99;	//0xCC8309C8
	UINT32                                                  reserved100;	//0xCC8309CC
	UINT32                                                  reserved101;	//0xCC8309D0
	UINT32                                                  reserved102;	//0xCC8309D4
	UINT32                                                  reserved103;	//0xCC8309D8
	UINT32                                                  reserved104;	//0xCC8309DC
	PE_M23_GSC_C_GSC_G0_VCNT_IN_T                           gsc_g0_vcnt_in;	//0xCC8309E0
	PE_M23_GSC_C_GSC_G0_VCNT_OUT_T                         gsc_g0_vcnt_out;	//0xCC8309E4
	PE_M23_GSC_C_GSC_G0_FMC_TIMER_CNT_T               gsc_g0_fmc_timer_cnt;	//0xCC8309E8
}PE_GSC_C_REG_M23_T;
#endif
