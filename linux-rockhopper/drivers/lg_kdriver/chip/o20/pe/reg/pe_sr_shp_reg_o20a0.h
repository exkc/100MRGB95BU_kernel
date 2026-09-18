#ifndef _PE_SRE_REG_O20A0_H_
#define _PE_SRE_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9009800L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :6 ,	// reserved
	reg_top_mode_3d                    :1 ;	// 12:12
}PE_O20_SHP_CHR_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009804L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_O20_SHP_CHR_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009808L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O20_SHP_CHR_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c00L shp_cdj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_edf_en                     :1 ,	// 0:0
	reg_cdj_hv_filter_en               :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_cdj_edge_adaptive_en           :1 ,	// 3:3
	reg_cdj_line_variation_mode        :1 ,	// 4:4
	reg_cdj_l_type_protection          :1 ,	// 5:5
	reg_cdj_soft_en                    :1 ,	// 6:6
	reserved02                         :1 ,	// reserved
	reg_cdj_count_diff_th              :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_cdj_output_mux                 :3 ,	// 18:16
	reg_cdj_buffer_detour_en           :1 ,	// 19:19
	reg_cdj_center_blur_mode           :2 ,	// 21:20
	reg_cdj_n_avg_mode                 :1 ,	// 22:22
	reg_cdj_detour_en                  :1 ,	// 23:23
	reg_cdj_line_variation_diff_th     :8 ;	// 31:24
}PE_O20_SHP_CDJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c04L shp_cdj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_level_th                   :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_cdj_n_avg_gain                 :8 ;	// 23:16
}PE_O20_SHP_CDJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c08L shp_cdj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_g0_cnt_min                 :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_cdj_g0_mul                     :5 ;	// 12:8
}PE_O20_SHP_CDJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c0cL shp_cdj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_g1_protect_min             :8 ,	// 7:0
	reg_cdj_g1_mul                     :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_cdj_edge_min                   :8 ,	// 23:16
	reg_cdj_edge_mul                   :8 ;	// 31:24
}PE_O20_SHP_CDJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009c10L shp_cdj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_dir_sel_c1                 :1 ,	// 0:0
	reg_cdj_dir_sel_c2                 :1 ,	// 1:1
	reg_cdj_dir_sel_c3                 :1 ,	// 2:2
	reg_cdj_dir_sel_c4                 :1 ;	// 3:3
}PE_O20_SHP_CDJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009c14L shp_cdj_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_0_00              :2 ,	// 1:0
	reg_cdj_pattern0_0_01              :2 ,	// 3:2
	reg_cdj_pattern0_0_02              :2 ,	// 5:4
	reg_cdj_pattern0_0_03              :2 ,	// 7:6
	reg_cdj_pattern0_0_04              :2 ,	// 9:8
	reg_cdj_pattern0_0_05              :2 ,	// 11:10
	reg_cdj_pattern0_0_06              :2 ,	// 13:12
	reg_cdj_pattern0_0_07              :2 ,	// 15:14
	reg_cdj_pattern0_0_08              :2 ,	// 17:16
	reg_cdj_pattern0_0_09              :2 ,	// 19:18
	reg_cdj_pattern0_0_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009c18L shp_cdj_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_1_00              :2 ,	// 1:0
	reg_cdj_pattern0_1_01              :2 ,	// 3:2
	reg_cdj_pattern0_1_02              :2 ,	// 5:4
	reg_cdj_pattern0_1_03              :2 ,	// 7:6
	reg_cdj_pattern0_1_04              :2 ,	// 9:8
	reg_cdj_pattern0_1_05              :2 ,	// 11:10
	reg_cdj_pattern0_1_06              :2 ,	// 13:12
	reg_cdj_pattern0_1_07              :2 ,	// 15:14
	reg_cdj_pattern0_1_08              :2 ,	// 17:16
	reg_cdj_pattern0_1_09              :2 ,	// 19:18
	reg_cdj_pattern0_1_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9009c1cL shp_cdj_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_2_00              :2 ,	// 1:0
	reg_cdj_pattern0_2_01              :2 ,	// 3:2
	reg_cdj_pattern0_2_02              :2 ,	// 5:4
	reg_cdj_pattern0_2_03              :2 ,	// 7:6
	reg_cdj_pattern0_2_04              :2 ,	// 9:8
	reg_cdj_pattern0_2_05              :2 ,	// 11:10
	reg_cdj_pattern0_2_06              :2 ,	// 13:12
	reg_cdj_pattern0_2_07              :2 ,	// 15:14
	reg_cdj_pattern0_2_08              :2 ,	// 17:16
	reg_cdj_pattern0_2_09              :2 ,	// 19:18
	reg_cdj_pattern0_2_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009c20L shp_cdj_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_3_00              :2 ,	// 1:0
	reg_cdj_pattern0_3_01              :2 ,	// 3:2
	reg_cdj_pattern0_3_02              :2 ,	// 5:4
	reg_cdj_pattern0_3_03              :2 ,	// 7:6
	reg_cdj_pattern0_3_04              :2 ,	// 9:8
	reg_cdj_pattern0_3_05              :2 ,	// 11:10
	reg_cdj_pattern0_3_06              :2 ,	// 13:12
	reg_cdj_pattern0_3_07              :2 ,	// 15:14
	reg_cdj_pattern0_3_08              :2 ,	// 17:16
	reg_cdj_pattern0_3_09              :2 ,	// 19:18
	reg_cdj_pattern0_3_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009c24L shp_cdj_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_4_00              :2 ,	// 1:0
	reg_cdj_pattern0_4_01              :2 ,	// 3:2
	reg_cdj_pattern0_4_02              :2 ,	// 5:4
	reg_cdj_pattern0_4_03              :2 ,	// 7:6
	reg_cdj_pattern0_4_04              :2 ,	// 9:8
	reg_cdj_pattern0_4_05              :2 ,	// 11:10
	reg_cdj_pattern0_4_06              :2 ,	// 13:12
	reg_cdj_pattern0_4_07              :2 ,	// 15:14
	reg_cdj_pattern0_4_08              :2 ,	// 17:16
	reg_cdj_pattern0_4_09              :2 ,	// 19:18
	reg_cdj_pattern0_4_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009c28L shp_cdj_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_5_00              :2 ,	// 1:0
	reg_cdj_pattern0_5_01              :2 ,	// 3:2
	reg_cdj_pattern0_5_02              :2 ,	// 5:4
	reg_cdj_pattern0_5_03              :2 ,	// 7:6
	reg_cdj_pattern0_5_04              :2 ,	// 9:8
	reg_cdj_pattern0_5_05              :2 ,	// 11:10
	reg_cdj_pattern0_5_06              :2 ,	// 13:12
	reg_cdj_pattern0_5_07              :2 ,	// 15:14
	reg_cdj_pattern0_5_08              :2 ,	// 17:16
	reg_cdj_pattern0_5_09              :2 ,	// 19:18
	reg_cdj_pattern0_5_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9009c2cL shp_cdj_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_6_00              :2 ,	// 1:0
	reg_cdj_pattern0_6_01              :2 ,	// 3:2
	reg_cdj_pattern0_6_02              :2 ,	// 5:4
	reg_cdj_pattern0_6_03              :2 ,	// 7:6
	reg_cdj_pattern0_6_04              :2 ,	// 9:8
	reg_cdj_pattern0_6_05              :2 ,	// 11:10
	reg_cdj_pattern0_6_06              :2 ,	// 13:12
	reg_cdj_pattern0_6_07              :2 ,	// 15:14
	reg_cdj_pattern0_6_08              :2 ,	// 17:16
	reg_cdj_pattern0_6_09              :2 ,	// 19:18
	reg_cdj_pattern0_6_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009c30L shp_cdj_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_flip0_h           :1 ,	// 0:0
	reg_cdj_pattern0_flip0_v           :1 ,	// 1:1
	reg_cdj_pattern0_flip1_h           :1 ,	// 2:2
	reg_cdj_pattern0_flip1_v           :1 ,	// 3:3
	reg_cdj_pattern0_flip2_h           :1 ,	// 4:4
	reg_cdj_pattern0_flip2_v           :1 ,	// 5:5
	reg_cdj_pattern0_flip3_h           :1 ,	// 6:6
	reg_cdj_pattern0_flip3_v           :1 ;	// 7:7
}PE_O20_SHP_CDJ_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009c34L shp_cdj_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_0_00              :2 ,	// 1:0
	reg_cdj_pattern1_0_01              :2 ,	// 3:2
	reg_cdj_pattern1_0_02              :2 ,	// 5:4
	reg_cdj_pattern1_0_03              :2 ,	// 7:6
	reg_cdj_pattern1_0_04              :2 ,	// 9:8
	reg_cdj_pattern1_0_05              :2 ,	// 11:10
	reg_cdj_pattern1_0_06              :2 ,	// 13:12
	reg_cdj_pattern1_0_07              :2 ,	// 15:14
	reg_cdj_pattern1_0_08              :2 ,	// 17:16
	reg_cdj_pattern1_0_09              :2 ,	// 19:18
	reg_cdj_pattern1_0_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9009c38L shp_cdj_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_1_00              :2 ,	// 1:0
	reg_cdj_pattern1_1_01              :2 ,	// 3:2
	reg_cdj_pattern1_1_02              :2 ,	// 5:4
	reg_cdj_pattern1_1_03              :2 ,	// 7:6
	reg_cdj_pattern1_1_04              :2 ,	// 9:8
	reg_cdj_pattern1_1_05              :2 ,	// 11:10
	reg_cdj_pattern1_1_06              :2 ,	// 13:12
	reg_cdj_pattern1_1_07              :2 ,	// 15:14
	reg_cdj_pattern1_1_08              :2 ,	// 17:16
	reg_cdj_pattern1_1_09              :2 ,	// 19:18
	reg_cdj_pattern1_1_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9009c3cL shp_cdj_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_2_00              :2 ,	// 1:0
	reg_cdj_pattern1_2_01              :2 ,	// 3:2
	reg_cdj_pattern1_2_02              :2 ,	// 5:4
	reg_cdj_pattern1_2_03              :2 ,	// 7:6
	reg_cdj_pattern1_2_04              :2 ,	// 9:8
	reg_cdj_pattern1_2_05              :2 ,	// 11:10
	reg_cdj_pattern1_2_06              :2 ,	// 13:12
	reg_cdj_pattern1_2_07              :2 ,	// 15:14
	reg_cdj_pattern1_2_08              :2 ,	// 17:16
	reg_cdj_pattern1_2_09              :2 ,	// 19:18
	reg_cdj_pattern1_2_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9009c40L shp_cdj_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_3_00              :2 ,	// 1:0
	reg_cdj_pattern1_3_01              :2 ,	// 3:2
	reg_cdj_pattern1_3_02              :2 ,	// 5:4
	reg_cdj_pattern1_3_03              :2 ,	// 7:6
	reg_cdj_pattern1_3_04              :2 ,	// 9:8
	reg_cdj_pattern1_3_05              :2 ,	// 11:10
	reg_cdj_pattern1_3_06              :2 ,	// 13:12
	reg_cdj_pattern1_3_07              :2 ,	// 15:14
	reg_cdj_pattern1_3_08              :2 ,	// 17:16
	reg_cdj_pattern1_3_09              :2 ,	// 19:18
	reg_cdj_pattern1_3_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9009c44L shp_cdj_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_4_00              :2 ,	// 1:0
	reg_cdj_pattern1_4_01              :2 ,	// 3:2
	reg_cdj_pattern1_4_02              :2 ,	// 5:4
	reg_cdj_pattern1_4_03              :2 ,	// 7:6
	reg_cdj_pattern1_4_04              :2 ,	// 9:8
	reg_cdj_pattern1_4_05              :2 ,	// 11:10
	reg_cdj_pattern1_4_06              :2 ,	// 13:12
	reg_cdj_pattern1_4_07              :2 ,	// 15:14
	reg_cdj_pattern1_4_08              :2 ,	// 17:16
	reg_cdj_pattern1_4_09              :2 ,	// 19:18
	reg_cdj_pattern1_4_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9009c48L shp_cdj_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_5_00              :2 ,	// 1:0
	reg_cdj_pattern1_5_01              :2 ,	// 3:2
	reg_cdj_pattern1_5_02              :2 ,	// 5:4
	reg_cdj_pattern1_5_03              :2 ,	// 7:6
	reg_cdj_pattern1_5_04              :2 ,	// 9:8
	reg_cdj_pattern1_5_05              :2 ,	// 11:10
	reg_cdj_pattern1_5_06              :2 ,	// 13:12
	reg_cdj_pattern1_5_07              :2 ,	// 15:14
	reg_cdj_pattern1_5_08              :2 ,	// 17:16
	reg_cdj_pattern1_5_09              :2 ,	// 19:18
	reg_cdj_pattern1_5_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9009c4cL shp_cdj_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_6_00              :2 ,	// 1:0
	reg_cdj_pattern1_6_01              :2 ,	// 3:2
	reg_cdj_pattern1_6_02              :2 ,	// 5:4
	reg_cdj_pattern1_6_03              :2 ,	// 7:6
	reg_cdj_pattern1_6_04              :2 ,	// 9:8
	reg_cdj_pattern1_6_05              :2 ,	// 11:10
	reg_cdj_pattern1_6_06              :2 ,	// 13:12
	reg_cdj_pattern1_6_07              :2 ,	// 15:14
	reg_cdj_pattern1_6_08              :2 ,	// 17:16
	reg_cdj_pattern1_6_09              :2 ,	// 19:18
	reg_cdj_pattern1_6_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9009c50L shp_cdj_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_flip0_h           :1 ,	// 0:0
	reg_cdj_pattern1_flip0_v           :1 ,	// 1:1
	reg_cdj_pattern1_flip1_h           :1 ,	// 2:2
	reg_cdj_pattern1_flip1_v           :1 ;	// 3:3
}PE_O20_SHP_CDJ_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9009c54L shp_cdj_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_0_00              :2 ,	// 1:0
	reg_cdj_pattern2_0_01              :2 ,	// 3:2
	reg_cdj_pattern2_0_02              :2 ,	// 5:4
	reg_cdj_pattern2_0_03              :2 ,	// 7:6
	reg_cdj_pattern2_0_04              :2 ,	// 9:8
	reg_cdj_pattern2_0_05              :2 ,	// 11:10
	reg_cdj_pattern2_0_06              :2 ,	// 13:12
	reg_cdj_pattern2_0_07              :2 ,	// 15:14
	reg_cdj_pattern2_0_08              :2 ,	// 17:16
	reg_cdj_pattern2_0_09              :2 ,	// 19:18
	reg_cdj_pattern2_0_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9009c58L shp_cdj_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_1_00              :2 ,	// 1:0
	reg_cdj_pattern2_1_01              :2 ,	// 3:2
	reg_cdj_pattern2_1_02              :2 ,	// 5:4
	reg_cdj_pattern2_1_03              :2 ,	// 7:6
	reg_cdj_pattern2_1_04              :2 ,	// 9:8
	reg_cdj_pattern2_1_05              :2 ,	// 11:10
	reg_cdj_pattern2_1_06              :2 ,	// 13:12
	reg_cdj_pattern2_1_07              :2 ,	// 15:14
	reg_cdj_pattern2_1_08              :2 ,	// 17:16
	reg_cdj_pattern2_1_09              :2 ,	// 19:18
	reg_cdj_pattern2_1_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9009c5cL shp_cdj_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_2_00              :2 ,	// 1:0
	reg_cdj_pattern2_2_01              :2 ,	// 3:2
	reg_cdj_pattern2_2_02              :2 ,	// 5:4
	reg_cdj_pattern2_2_03              :2 ,	// 7:6
	reg_cdj_pattern2_2_04              :2 ,	// 9:8
	reg_cdj_pattern2_2_05              :2 ,	// 11:10
	reg_cdj_pattern2_2_06              :2 ,	// 13:12
	reg_cdj_pattern2_2_07              :2 ,	// 15:14
	reg_cdj_pattern2_2_08              :2 ,	// 17:16
	reg_cdj_pattern2_2_09              :2 ,	// 19:18
	reg_cdj_pattern2_2_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9009c60L shp_cdj_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_3_00              :2 ,	// 1:0
	reg_cdj_pattern2_3_01              :2 ,	// 3:2
	reg_cdj_pattern2_3_02              :2 ,	// 5:4
	reg_cdj_pattern2_3_03              :2 ,	// 7:6
	reg_cdj_pattern2_3_04              :2 ,	// 9:8
	reg_cdj_pattern2_3_05              :2 ,	// 11:10
	reg_cdj_pattern2_3_06              :2 ,	// 13:12
	reg_cdj_pattern2_3_07              :2 ,	// 15:14
	reg_cdj_pattern2_3_08              :2 ,	// 17:16
	reg_cdj_pattern2_3_09              :2 ,	// 19:18
	reg_cdj_pattern2_3_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9009c64L shp_cdj_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_4_00              :2 ,	// 1:0
	reg_cdj_pattern2_4_01              :2 ,	// 3:2
	reg_cdj_pattern2_4_02              :2 ,	// 5:4
	reg_cdj_pattern2_4_03              :2 ,	// 7:6
	reg_cdj_pattern2_4_04              :2 ,	// 9:8
	reg_cdj_pattern2_4_05              :2 ,	// 11:10
	reg_cdj_pattern2_4_06              :2 ,	// 13:12
	reg_cdj_pattern2_4_07              :2 ,	// 15:14
	reg_cdj_pattern2_4_08              :2 ,	// 17:16
	reg_cdj_pattern2_4_09              :2 ,	// 19:18
	reg_cdj_pattern2_4_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9009c68L shp_cdj_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_5_00              :2 ,	// 1:0
	reg_cdj_pattern2_5_01              :2 ,	// 3:2
	reg_cdj_pattern2_5_02              :2 ,	// 5:4
	reg_cdj_pattern2_5_03              :2 ,	// 7:6
	reg_cdj_pattern2_5_04              :2 ,	// 9:8
	reg_cdj_pattern2_5_05              :2 ,	// 11:10
	reg_cdj_pattern2_5_06              :2 ,	// 13:12
	reg_cdj_pattern2_5_07              :2 ,	// 15:14
	reg_cdj_pattern2_5_08              :2 ,	// 17:16
	reg_cdj_pattern2_5_09              :2 ,	// 19:18
	reg_cdj_pattern2_5_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc9009c6cL shp_cdj_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_6_00              :2 ,	// 1:0
	reg_cdj_pattern2_6_01              :2 ,	// 3:2
	reg_cdj_pattern2_6_02              :2 ,	// 5:4
	reg_cdj_pattern2_6_03              :2 ,	// 7:6
	reg_cdj_pattern2_6_04              :2 ,	// 9:8
	reg_cdj_pattern2_6_05              :2 ,	// 11:10
	reg_cdj_pattern2_6_06              :2 ,	// 13:12
	reg_cdj_pattern2_6_07              :2 ,	// 15:14
	reg_cdj_pattern2_6_08              :2 ,	// 17:16
	reg_cdj_pattern2_6_09              :2 ,	// 19:18
	reg_cdj_pattern2_6_10              :2 ;	// 21:20
}PE_O20_SHP_CDJ_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc9009c70L shp_cdj_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_flip0_h           :1 ,	// 0:0
	reg_cdj_pattern2_flip0_v           :1 ,	// 1:1
	reg_cdj_pattern2_flip1_h           :1 ,	// 2:2
	reg_cdj_pattern2_flip1_v           :1 ;	// 3:3
}PE_O20_SHP_CDJ_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc9009c74L shp_cdj_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_g0_mul                :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_cdj_soft_g0_offset             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_cdj_soft_g0_max                :8 ;	// 23:16
}PE_O20_SHP_CDJ_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc9009c78L shp_cdj_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_g1_mul                :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_cdj_soft_g1_offset             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_cdj_soft_g1_max                :8 ;	// 23:16
}PE_O20_SHP_CDJ_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc9009c7cL shp_cdj_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_g2_mul                :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_cdj_soft_g2_offset             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_cdj_soft_g2_max                :8 ;	// 23:16
}PE_O20_SHP_CDJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9009c80L shp_cdj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_base                  :8 ,	// 7:0
	reg_cdj_soft_sel_1357_gain         :8 ,	// 15:8
	reg_cdj_soft_single_match_en       :1 ;	// 16:16
}PE_O20_SHP_CDJ_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9009c90L shp_cdir_blur_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdir_blur_detour               :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cdir_blur_buf_detour           :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_cdir_blur_en                   :1 ;	// 8:8
}PE_O20_SHP_CDIR_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c94L shp_cdir_blur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdir_blur_base                 :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_cdir_blur_gain                 :8 ;	// 23:16
}PE_O20_SHP_CDIR_BLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca0L shp_cdj_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win0_en                :1 ,	// 0:0
	reg_win_cdj_win1_en                :1 ,	// 1:1
	reg_win_cdj_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_cdj_win_outside            :1 ,	// 6:6
	reg_win_cdj_win_en                 :1 ,	// 7:7
	reg_win_cdj_bdr_alpha              :5 ,	// 12:8
	reg_win_cdj_bdr_wid                :2 ,	// 14:13
	reg_win_cdj_bdr_en                 :1 ,	// 15:15
	reg_win_cdj_cr5                    :5 ,	// 20:16
	reg_win_cdj_cb5                    :5 ,	// 25:21
	reg_win_cdj_yy6                    :6 ;	// 31:26
}PE_O20_SHP_CDJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca4L shp_cdj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w0_y0              :12;	// 27:16
}PE_O20_SHP_CDJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca8L shp_cdj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w0_y1              :12;	// 27:16
}PE_O20_SHP_CDJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009cacL shp_cdj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w1_y0              :12;	// 27:16
}PE_O20_SHP_CDJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009cb0L shp_cdj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w1_y1              :12;	// 27:16
}PE_O20_SHP_CDJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009e00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O20_SHP_CHR_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009e04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O20_SHP_CHR_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009e08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O20_SHP_CHR_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009e0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O20_SHP_CHR_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009e10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O20_SHP_CHR_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009e14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O20_SHP_CHR_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CHR_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CHR_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CHR_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009efcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CHR_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc9008700L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_protocol_type              :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_mode_3d                    :1 ;	// 12:12
}PE_O20_SHP_2K_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008704L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_O20_SHP_2K_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008708L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O20_SHP_2K_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900870cL shp_core_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_prefetch_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_flush_cnt                  :12;	// 27:16
}PE_O20_SHP_2K_CORE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008740L shp_pat_gen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pat_en                         :1 ,	// 0:0
	reg_pat_thickness                  :2 ,	// 2:1
	reserved01                         :5 ,	// reserved
	reg_pat_pix_val_yy                 :8 ;	// 15:8
}PE_O20_SHP_2K_PAT_GEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90087f0L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_O20_SHP_2K_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008800L shp_fd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_map_h_size                :2 ,	// 1:0
	reg_fd_a_nomalize_en               :1 ,	// 2:2
	reg_fd_t_nomalize_en               :1 ,	// 3:3
	reg_fd_t_cut_resolution            :2 ,	// 5:4
	reserved01                         :2 ,	// reserved
	reg_fd_a_map_post_filter_en        :1 ,	// 8:8
	reg_fd_t_cross_check               :1 ,	// 9:9
	reserved02                         :6 ,	// reserved
	reg_fd_pre_a_map_h_size            :3 ,	// 18:16
	reg_fd_pre_a_map_v_size            :2 ,	// 20:19
	reg_fd_pre_a_cut_resolution        :3 ,	// 23:21
	reg_fd_cross_th                    :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008804L shp_fd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mul_base_t                  :8 ,	// 7:0
	reg_fd_mul_base_e                  :8 ;	// 15:8
}PE_O20_SHP_2K_FD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008808L shp_fd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900880cL shp_fd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008810L shp_fd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008814L shp_fd_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008818L shp_fd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900881cL shp_fd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008820L shp_fd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y2              :8 ,	// 7:0
	reg_fd_edge_minmax_x2              :8 ,	// 15:8
	reg_fd_edge_minmax_y3              :8 ,	// 23:16
	reg_fd_edge_minmax_x3              :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008824L shp_fd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008828L shp_fd_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y2            :8 ,	// 7:0
	reg_fd_detail_minmax_x2            :8 ,	// 15:8
	reg_fd_detail_minmax_y3            :8 ,	// 23:16
	reg_fd_detail_minmax_x3            :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900882cL shp_fd_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_O20_SHP_2K_FD_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008830L shp_fd_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_fd_mnr_s2_ratio_max            :8 ;	// 23:16
}PE_O20_SHP_2K_FD_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008834L shp_fd_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_x0                 :8 ,	// 7:0
	reg_fd_mnr_gain_x1                 :8 ,	// 15:8
	reg_fd_mnr_gain_y0                 :8 ,	// 23:16
	reg_fd_mnr_gain_y1                 :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9008838L shp_fd_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y0                :8 ,	// 7:0
	reg_fd_dct_t_lut_x0                :8 ,	// 15:8
	reg_fd_dct_t_lut_y1                :8 ,	// 23:16
	reg_fd_dct_t_lut_x1                :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900883cL shp_fd_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y2                :8 ,	// 7:0
	reg_fd_dct_t_lut_x2                :8 ,	// 15:8
	reg_fd_dct_t_lut_y3                :8 ,	// 23:16
	reg_fd_dct_t_lut_x3                :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9008840L shp_fd_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y4                :8 ,	// 7:0
	reg_fd_dct_t_lut_x4                :8 ,	// 15:8
	reg_fd_dct_t_lut_y5                :8 ,	// 23:16
	reg_fd_dct_t_lut_x5                :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008844L shp_fd_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_gain_e_en              :1 ,	// 0:0
	reg_fd_soft_gain_t_en              :1 ;	// 1:1
}PE_O20_SHP_2K_FD_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008848L shp_fd_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_ratio                  :8 ,	// 7:0
	reg_fd_soft_offset                 :8 ;	// 15:8
}PE_O20_SHP_2K_FD_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900884cL shp_fd_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_x0               :8 ,	// 7:0
	reg_fd_soft_score_x1               :8 ,	// 15:8
	reg_fd_soft_score_x2               :8 ,	// 23:16
	reg_fd_soft_score_x3               :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9008850L shp_fd_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_y0               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_fd_soft_score_y1               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_fd_soft_score_y2               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_fd_soft_score_y3               :6 ;	// 29:24
}PE_O20_SHP_2K_FD_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9008854L shp_fd_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_flat_input_sel              :2 ,	// 1:0
	reserved01                         :2 ,	// reserved
	reg_fd_flat_protect_e_en           :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_fd_flat_protect_t_en           :1 ;	// 8:8
}PE_O20_SHP_2K_FD_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9008858L shp_fd_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_flat_lut_y0                 :8 ,	// 7:0
	reg_fd_flat_lut_x0                 :8 ,	// 15:8
	reg_fd_flat_lut_y1                 :8 ,	// 23:16
	reg_fd_flat_lut_x1                 :8 ;	// 31:24
}PE_O20_SHP_2K_FD_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9008860L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ;	// 0:0
}PE_O20_SHP_2K_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008864L shp_mp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_im_gain_h                   :8 ,	// 23:16
	reg_mp_im_gain_v                   :8 ;	// 31:24
}PE_O20_SHP_2K_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008868L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_lap_weight                  :8 ;	// 15:8
}PE_O20_SHP_2K_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900886cL shp_mp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_mp_lap_gain_v_7                :4 ,	// 7:4
	reg_mp_lap_gain_v_5                :4 ,	// 11:8
	reg_mp_lap_gain_v_3                :4 ,	// 15:12
	reserved02                         :4 ,	// reserved
	reg_mp_lap_gain_h_7                :4 ,	// 23:20
	reg_mp_lap_gain_h_5                :4 ,	// 27:24
	reg_mp_lap_gain_h_3                :4 ;	// 31:28
}PE_O20_SHP_2K_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008870L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ;	// 11:8
}PE_O20_SHP_2K_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008874L shp_mp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_mp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_mp_gb_x1                       :8 ,	// 15:8
	reg_mp_gb_y1                       :8 ;	// 23:16
}PE_O20_SHP_2K_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008878L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_O20_SHP_2K_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900887cL shp_mp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_O20_SHP_2K_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008880L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_O20_SHP_2K_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008884L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_O20_SHP_2K_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008888L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_O20_SHP_2K_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900888cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_en                   :1 ,	// 0:0
	reg_mp_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_mp_coring_input_sel            :2 ;	// 5:4
}PE_O20_SHP_2K_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008890L shp_mp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_mp_coring_gain_t_w             :7 ;	// 30:24
}PE_O20_SHP_2K_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008894L shp_apl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_apl_iir_en                     :1 ,	// 0:0
	reserved01                         :7 ,	// reserved
	reg_apl_iir_gain                   :8 ;	// 15:8
}PE_O20_SHP_2K_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088a0L shp_lc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_shp_en                      :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_lc_gb_en                       :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_lc_center_target               :8 ,	// 15:8
	reg_lc_center_gain                 :8 ,	// 23:16
	reg_lc_local_gain                  :8 ;	// 31:24
}PE_O20_SHP_2K_LC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088a4L shp_lc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_O20_SHP_2K_LC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90088a8L shp_lc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_O20_SHP_2K_LC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90088acL shp_lc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_lc_coring_input_sel            :2 ;	// 5:4
}PE_O20_SHP_2K_LC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90088b0L shp_lc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lc_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_lc_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_lc_coring_gain_t_w             :7 ;	// 30:24
}PE_O20_SHP_2K_LC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90088c0L shp_der_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_csft_gain                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_th_gain_edge              :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_derh_th_manual_th              :7 ,	// 30:24
	reg_derh_th_manual_en              :1 ;	// 31:31
}PE_O20_SHP_2K_DER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088c4L shp_der_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_bflt_tap_size             :3 ,	// 2:0
	reserved01                         :21,	// reserved
	reg_derh_amean_en                  :1 ,	// 24:24
	reserved02                         :1 ,	// reserved
	reg_derh_edge_filter_v_tap         :2 ,	// 27:26
	reserved03                         :3 ,	// reserved
	reg_derh_edge_y_filter_en          :1 ;	// 31:31
}PE_O20_SHP_2K_DER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90088c8L shp_der_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ;	// 21:16
}PE_O20_SHP_2K_DER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90088ccL shp_der_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_en                        :1 ,	// 0:0
	reserved01                         :2 ,	// reserved
	reg_derv_bif_en                    :1 ,	// 3:3
	reg_derv_output_mux                :4 ,	// 7:4
	reg_derv_bif_manual_th             :8 ,	// 15:8
	reg_derv_th_gain                   :6 ,	// 21:16
	reserved02                         :2 ,	// reserved
	reg_derv_th_mode                   :1 ;	// 24:24
}PE_O20_SHP_2K_DER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90088d0L shp_der_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_O20_SHP_2K_DER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90088d4L shp_der_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_O20_SHP_2K_DER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90088d8L shp_der_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y0                   :8 ,	// 7:0
	reg_der_a_lut_x0                   :8 ,	// 15:8
	reg_der_a_lut_y1                   :8 ,	// 23:16
	reg_der_a_lut_x1                   :8 ;	// 31:24
}PE_O20_SHP_2K_DER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90088dcL shp_der_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y2                   :8 ,	// 7:0
	reg_der_a_lut_x2                   :8 ,	// 15:8
	reg_der_a_lut_y3                   :8 ,	// 23:16
	reg_der_a_lut_x3                   :8 ;	// 31:24
}PE_O20_SHP_2K_DER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90088e0L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ;	// 0:0
}PE_O20_SHP_2K_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088e4L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ;	// 23:16
}PE_O20_SHP_2K_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90088e8L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_lap_weight                  :8 ;	// 15:8
}PE_O20_SHP_2K_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90088ecL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_O20_SHP_2K_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90088f0L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ;	// 11:8
}PE_O20_SHP_2K_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90088f4L shp_sp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_sp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_sp_gb_x1                       :8 ,	// 15:8
	reg_sp_gb_y1                       :8 ;	// 23:16
}PE_O20_SHP_2K_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90088f8L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_O20_SHP_2K_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90088fcL shp_sp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_O20_SHP_2K_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008900L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_O20_SHP_2K_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008904L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_O20_SHP_2K_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008908L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_O20_SHP_2K_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900890cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_en                   :1 ,	// 0:0
	reg_sp_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_sp_coring_input_sel            :2 ;	// 5:4
}PE_O20_SHP_2K_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008910L shp_sp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_sp_coring_gain_t_w             :7 ;	// 30:24
}PE_O20_SHP_2K_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008920L shp_pti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptiv_enable                    :1 ,	// 0:0
	reg_ptiv_debug_map_en              :1 ,	// 1:1
	reg_ptiv_mm_tap_size               :2 ,	// 3:2
	reg_ptiv_avg_tap_size              :2 ,	// 5:4
	reg_ptiv_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptiv_master_gain               :8 ;	// 15:8
}PE_O20_SHP_2K_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008924L shp_pti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptih_enable                    :1 ,	// 0:0
	reg_ptih_debug_map_en              :1 ,	// 1:1
	reg_ptih_mm_tap_size               :2 ,	// 3:2
	reg_ptih_avg_tap_size              :2 ,	// 5:4
	reg_ptih_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptih_master_gain               :8 ;	// 15:8
}PE_O20_SHP_2K_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008928L shp_pti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_en                  :1 ,	// 0:0
	reg_pti_coring_mode                :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_pti_coring_input_sel           :2 ;	// 5:4
}PE_O20_SHP_2K_PTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900892cL shp_pti_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_gain_e_b            :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_pti_coring_gain_e_w            :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_pti_coring_gain_t_b            :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_pti_coring_gain_t_w            :7 ;	// 30:24
}PE_O20_SHP_2K_PTI_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008930L shp_sti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sti_enable                     :1 ,	// 0:0
	reg_sti_debug_map_en               :1 ,	// 1:1
	reg_sti_mm_tap_size                :2 ,	// 3:2
	reg_sti_avg_tap_size               :2 ,	// 5:4
	reg_sti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_sti_master_gain                :8 ,	// 15:8
	reg_sti_texture_gain               :8 ,	// 23:16
	reg_sti_edge_gain                  :8 ;	// 31:24
}PE_O20_SHP_2K_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008940L shp_tgen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_on_off                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tgen_initial_seed_mode         :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tgen_dbg_en                    :1 ,	// 8:8
	reserved03                         :7 ,	// reserved
	reg_tgen_table_sel                 :4 ,	// 19:16
	reserved04                         :4 ,	// reserved
	reg_tgen_master_gain               :8 ;	// 31:24
}PE_O20_SHP_2K_TGEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008944L shp_tgen_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_delta_h_bound             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_delta_l_bound             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_delta_max                 :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_delta_scale               :3 ;	// 26:24
}PE_O20_SHP_2K_TGEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008948L shp_tgen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rnd_th                    :8 ,	// 7:0
	reg_tgen_delta_wcurr               :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_tgen_lc_ldr_th                 :6 ;	// 21:16
}PE_O20_SHP_2K_TGEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900894cL shp_tgen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_x0;	// 31:0
}PE_O20_SHP_2K_TGEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008954L shp_tgen_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_dr_ratio                  :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_tgen_dr_th                     :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_tgen_mm_offset                 :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	reg_tgen_mm_sel_mode               :2 ;	// 25:24
}PE_O20_SHP_2K_TGEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008958L shp_tgen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_tgen_gs_rnd                    :5 ,	// 20:16
	reserved02                         :3 ,	// reserved
	reg_tgen_gs_mm                     :5 ;	// 28:24
}PE_O20_SHP_2K_TGEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900895cL shp_tgen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_x2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_x1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_x0              :6 ;	// 29:24
}PE_O20_SHP_2K_TGEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008960L shp_tgen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_y2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_y1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_y0              :6 ;	// 29:24
}PE_O20_SHP_2K_TGEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008964L shp_tgen_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_map_edge_gain             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_map_detail_gain           :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_map_offset                :8 ,	// 23:16
	reg_tgen_gs_noise                  :6 ;	// 29:24
}PE_O20_SHP_2K_TGEN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008968L shp_tgen_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_gain7                     :4 ,	// 3:0
	reg_tgen_gain6                     :4 ,	// 7:4
	reg_tgen_gain5                     :4 ,	// 11:8
	reg_tgen_gain4                     :4 ,	// 15:12
	reg_tgen_gain3                     :4 ,	// 19:16
	reg_tgen_gain2                     :4 ,	// 23:20
	reg_tgen_gain1                     :4 ,	// 27:24
	reg_tgen_gain0                     :4 ;	// 31:28
}PE_O20_SHP_2K_TGEN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900896cL shp_tgen_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_en                 :1 ,	// 0:0
	reg_tgen_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_tgen_coring_input_sel          :2 ;	// 5:4
}PE_O20_SHP_2K_TGEN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008970L shp_tgen_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_tgen_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_tgen_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_coring_gain_t_w           :7 ;	// 30:24
}PE_O20_SHP_2K_TGEN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008974L shp_snr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ,	// 15:8
	reg_snr_blur_mode                  :3 ;	// 18:16
}PE_O20_SHP_2K_SNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008980L shp_dctp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_en                        :1 ;	// 0:0
}PE_O20_SHP_2K_DCTP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008984L shp_dctp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_1              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008988L shp_dctp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_3              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900898cL shp_dctp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_5              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008990L shp_dctp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_7              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008994L shp_dctp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_1              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008998L shp_dctp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_3              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900899cL shp_dctp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_5              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90089a0L shp_dctp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_7              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90089a4L shp_dctp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_1              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90089a8L shp_dctp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_3              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90089acL shp_dctp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_5              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90089b0L shp_dctp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_7              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90089b4L shp_dctp_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_1              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90089b8L shp_dctp_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_3              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90089bcL shp_dctp_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_5              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90089c0L shp_dctp_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_7              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90089c4L shp_dctp_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_1              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90089c8L shp_dctp_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_3              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90089ccL shp_dctp_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_5              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90089d0L shp_dctp_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_7              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90089d4L shp_dctp_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_1              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90089d8L shp_dctp_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_3              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90089dcL shp_dctp_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_5              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90089e0L shp_dctp_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_7              :12;	// 27:16
}PE_O20_SHP_2K_DCTP_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90089e4L shp_dctp_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x0               :8 ,	// 7:0
	reg_dctp_text_lut_x1               :8 ,	// 15:8
	reg_dctp_text_lut_x2               :8 ,	// 23:16
	reg_dctp_text_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_2K_DCTP_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90089e8L shp_dctp_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x4               :8 ,	// 7:0
	reg_dctp_text_lut_x5               :8 ;	// 15:8
}PE_O20_SHP_2K_DCTP_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc90089ecL shp_dctp_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y0               :8 ,	// 7:0
	reg_dctp_edge_lut_x0               :8 ,	// 15:8
	reg_dctp_edge_lut_y1               :8 ,	// 23:16
	reg_dctp_edge_lut_x1               :8 ;	// 31:24
}PE_O20_SHP_2K_DCTP_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc90089f0L shp_dctp_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y2               :8 ,	// 7:0
	reg_dctp_edge_lut_x2               :8 ,	// 15:8
	reg_dctp_edge_lut_y3               :8 ,	// 23:16
	reg_dctp_edge_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_2K_DCTP_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc90089f4L shp_dctp_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_gain                      :8 ;	// 7:0
}PE_O20_SHP_2K_DCTP_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc90089f8L shp_dctp_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_en                 :1 ,	// 0:0
	reg_dctp_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_dctp_coring_input_sel          :2 ;	// 5:4
}PE_O20_SHP_2K_DCTP_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc90089fcL shp_dctp_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_dctp_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_dctp_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_dctp_coring_gain_t_w           :7 ;	// 30:24
}PE_O20_SHP_2K_DCTP_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9008a00L shp_nntg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_en                        :1 ,	// 0:0
	reserved01                         :3 , // reserved
	reg_nntg_debug_mode                :2 ;	// 5:4
}PE_O20_SHP_2K_NNTG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008a04L shp_nntg_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st;	// 31:0
}PE_O20_SHP_2K_NNTG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008a08L shp_nntg_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd;	// 31:0
}PE_O20_SHP_2K_NNTG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008a0cL shp_nntg_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd;	// 31:0
}PE_O20_SHP_2K_NNTG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008a10L shp_nntg_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th;	// 31:0
}PE_O20_SHP_2K_NNTG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008a14L shp_nntg_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th;	// 31:0
}PE_O20_SHP_2K_NNTG_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008a2cL shp_nntg_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_ratio                :8 ,	// 7:0
	reg_nntg_rand_max                  :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_nntg_rand_sum_max              :8 ;	// 23:16
}PE_O20_SHP_2K_NNTG_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008a30L shp_nntg_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_coef_g00             :4 ,	// 3:0
	reg_nntg_rand_coef_g01             :4 ,	// 7:4
	reg_nntg_rand_coef_g02             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_rand_coef_g10             :4 ,	// 19:16
	reg_nntg_rand_coef_g11             :4 ,	// 23:20
	reg_nntg_rand_coef_g12             :4 ;	// 27:24
}PE_O20_SHP_2K_NNTG_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008a34L shp_nntg_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_coef_g20             :4 ,	// 3:0
	reg_nntg_rand_coef_g21             :4 ,	// 7:4
	reg_nntg_rand_coef_g22             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_nano_coef_g00             :4 ,	// 19:16
	reg_nntg_nano_coef_g01             :4 ,	// 23:20
	reg_nntg_nano_coef_g02             :4 ;	// 27:24
}PE_O20_SHP_2K_NNTG_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008a38L shp_nntg_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_nano_coef_g10             :4 ,	// 3:0
	reg_nntg_nano_coef_g11             :4 ,	// 7:4
	reg_nntg_nano_coef_g12             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_nano_coef_g20             :4 ,	// 19:16
	reg_nntg_nano_coef_g21             :4 ,	// 23:20
	reg_nntg_nano_coef_g22             :4 ;	// 27:24
}PE_O20_SHP_2K_NNTG_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008a3cL shp_nntg_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y0               :8 ,	// 7:0
	reg_nntg_diff_lut_x0               :8 ,	// 15:8
	reg_nntg_diff_lut_y1               :8 ,	// 23:16
	reg_nntg_diff_lut_x1               :8 ;	// 31:24
}PE_O20_SHP_2K_NNTG_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008a40L shp_nntg_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y2               :8 ,	// 7:0
	reg_nntg_diff_lut_x2               :8 ,	// 15:8
	reg_nntg_diff_lut_y3               :8 ,	// 23:16
	reg_nntg_diff_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_2K_NNTG_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008a44L shp_nntg_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y0               :8 ,	// 7:0
	reg_nntg_edge_lut_x0               :8 ,	// 15:8
	reg_nntg_edge_lut_y1               :8 ,	// 23:16
	reg_nntg_edge_lut_x1               :8 ;	// 31:24
}PE_O20_SHP_2K_NNTG_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008a48L shp_nntg_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y2               :8 ,	// 7:0
	reg_nntg_edge_lut_x2               :8 ,	// 15:8
	reg_nntg_edge_lut_y3               :8 ,	// 23:16
	reg_nntg_edge_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_2K_NNTG_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9008a4cL shp_nntg_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_random_gain               :8 ,	// 7:0
	reg_nntg_pattern_gain              :8 ,	// 15:8
	reg_nntg_local_gain                :8 ,	// 23:16
	reg_nntg_denoise_gain              :8 ;	// 31:24
}PE_O20_SHP_2K_NNTG_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9008a50L shp_nntg_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_en                 :1 ,	// 0:0
	reg_nntg_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_nntg_coring_input_sel          :2 ;	// 5:4
}PE_O20_SHP_2K_NNTG_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9008a54L shp_nntg_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_nntg_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_nntg_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_nntg_coring_gain_t_w           :7 ;	// 30:24
}PE_O20_SHP_2K_NNTG_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008a60L shp_dp_sum_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ,	// 7:0
	reg_dp_sum_lut_mode                :2 ;	// 9:8
}PE_O20_SHP_2K_DP_SUM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008a64L shp_dp_sum_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_lut_y0                  :8 ,	// 7:0
	reg_dp_sum_lut_x0                  :8 ,	// 15:8
	reg_dp_sum_lut_y1                  :8 ,	// 23:16
	reg_dp_sum_lut_x1                  :8 ;	// 31:24
}PE_O20_SHP_2K_DP_SUM_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008a68L shp_dp_sum_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_lut_y2                  :8 ,	// 7:0
	reg_dp_sum_lut_x2                  :8 ,	// 15:8
	reg_dp_sum_lut_y3                  :8 ,	// 23:16
	reg_dp_sum_lut_x3                  :8 ;	// 31:24
}PE_O20_SHP_2K_DP_SUM_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008aa0L shp_dp_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win0_en                 :1 ,	// 0:0
	reg_win_dp_win1_en                 :1 ,	// 1:1
	reg_win_dp_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_win_outside             :1 ,	// 6:6
	reg_win_dp_win_en                  :1 ,	// 7:7
	reg_win_dp_bdr_alpha               :5 ,	// 12:8
	reg_win_dp_bdr_wid                 :2 ,	// 14:13
	reg_win_dp_bdr_en                  :1 ,	// 15:15
	reg_win_dp_cr5                     :5 ,	// 20:16
	reg_win_dp_cb5                     :5 ,	// 25:21
	reg_win_dp_yy6                     :6 ;	// 31:26
}PE_O20_SHP_2K_DP_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008aa4L shp_dp_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0               :12;	// 27:16
}PE_O20_SHP_2K_DP_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008aa8L shp_dp_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1               :12;	// 27:16
}PE_O20_SHP_2K_DP_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008aacL shp_dp_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0               :12;	// 27:16
}PE_O20_SHP_2K_DP_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008ab0L shp_dp_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1               :12;	// 27:16
}PE_O20_SHP_2K_DP_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008ac0L shp_fd_region_text_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_en                 :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_region_text_cutres             :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_region_text_add_offset         :8 ,	// 15:8
	reg_region_text_add_max            :8 ,	// 23:16
	reg_region_text_cuthif             :3 ;	// 26:24
}PE_O20_SHP_2K_FD_REGION_TEXT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ac4L shp_fd_region_text_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_lut_y0             :8 ,	// 7:0
	reg_region_text_lut_x0             :8 ,	// 15:8
	reg_region_text_lut_y1             :8 ,	// 23:16
	reg_region_text_lut_x1             :8 ;	// 31:24
}PE_O20_SHP_2K_FD_REGION_TEXT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ac8L shp_fd_region_text_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_lut_y2             :8 ,	// 7:0
	reg_region_text_lut_x2             :8 ,	// 15:8
	reg_region_text_lut_y3             :8 ,	// 23:16
	reg_region_text_lut_x3             :8 ;	// 31:24
}PE_O20_SHP_2K_FD_REGION_TEXT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008accL shp_fd_tmap_temp_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_en               :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tmap_temp_init_en              :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tmap_temp_init_val             :8 ,	// 15:8
	reserved03                         :8 ,	// reserved
	reg_tmap_stat_sel                  :1 ;	// 24:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ad0L shp_fd_tmap_temp_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_prev_lut_y0          :8 ,	// 7:0
	reg_tmap_temp_prev_lut_x0          :8 ,	// 15:8
	reg_tmap_temp_prev_lut_y1          :8 ,	// 23:16
	reg_tmap_temp_prev_lut_x1          :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ad4L shp_fd_tmap_temp_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_prev_lut_y2          :8 ,	// 7:0
	reg_tmap_temp_prev_lut_x2          :8 ,	// 15:8
	reg_tmap_temp_prev_lut_y3          :8 ,	// 23:16
	reg_tmap_temp_prev_lut_x3          :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008ad8L shp_fd_tmap_temp_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y0       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x0       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y1       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x1       :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008adcL shp_fd_tmap_temp_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y2       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x2       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y3       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x3       :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008ae0L shp_fd_tmap_temp_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y4       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x4       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y5       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x5       :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008ae4L shp_fd_tmap_temp_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y0       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x0       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y1       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x1       :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008ae8L shp_fd_tmap_temp_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y2       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x2       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y3       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x3       :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008aecL shp_fd_tmap_temp_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y4       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x4       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y5       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x5       :8 ;	// 31:24
}PE_O20_SHP_2K_FD_TMAP_TEMP_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008af0L shp_fd_tmap_temp_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win0_start_x         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win0_start_y         :12;	// 27:16
}PE_O20_SHP_2K_FD_TMAP_TEMP_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008af4L shp_fd_tmap_temp_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win0_end_x           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win0_end_y           :12;	// 27:16
}PE_O20_SHP_2K_FD_TMAP_TEMP_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008af8L shp_fd_tmap_temp_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win1_start_x         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win1_start_y         :12;	// 27:16
}PE_O20_SHP_2K_FD_TMAP_TEMP_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008afcL shp_fd_tmap_temp_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win1_end_x           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win1_end_y           :12;	// 27:16
}PE_O20_SHP_2K_FD_TMAP_TEMP_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008b00L shp_dj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_edf_en                      :1 ,	// 0:0
	reg_dj_hv_filter_en                :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_dj_edge_adaptive_en            :1 ,	// 3:3
	reg_dj_line_variation_mode         :1 ,	// 4:4
	reg_dj_l_type_protection           :1 ,	// 5:5
	reg_dj_soft_en                     :1 ,	// 6:6
	reserved02                         :1 ,	// reserved
	reg_dj_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_dj_output_mux                  :3 ,	// 18:16
	reg_dj_buffer_detour_en            :1 ,	// 19:19
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reg_dj_detour_en                   :1 ,	// 23:23
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_O20_SHP_2K_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008b04L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_O20_SHP_2K_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008b08L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_O20_SHP_2K_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008b0cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_O20_SHP_2K_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008b10L shp_dj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_dir_sel_c1                  :1 ,	// 0:0
	reg_dj_dir_sel_c2                  :1 ,	// 1:1
	reg_dj_dir_sel_c3                  :1 ,	// 2:2
	reg_dj_dir_sel_c4                  :1 ;	// 3:3
}PE_O20_SHP_2K_DJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008b14L shp_dj_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_0_00               :2 ,	// 1:0
	reg_dj_pattern0_0_01               :2 ,	// 3:2
	reg_dj_pattern0_0_02               :2 ,	// 5:4
	reg_dj_pattern0_0_03               :2 ,	// 7:6
	reg_dj_pattern0_0_04               :2 ,	// 9:8
	reg_dj_pattern0_0_05               :2 ,	// 11:10
	reg_dj_pattern0_0_06               :2 ,	// 13:12
	reg_dj_pattern0_0_07               :2 ,	// 15:14
	reg_dj_pattern0_0_08               :2 ,	// 17:16
	reg_dj_pattern0_0_09               :2 ,	// 19:18
	reg_dj_pattern0_0_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008b18L shp_dj_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_1_00               :2 ,	// 1:0
	reg_dj_pattern0_1_01               :2 ,	// 3:2
	reg_dj_pattern0_1_02               :2 ,	// 5:4
	reg_dj_pattern0_1_03               :2 ,	// 7:6
	reg_dj_pattern0_1_04               :2 ,	// 9:8
	reg_dj_pattern0_1_05               :2 ,	// 11:10
	reg_dj_pattern0_1_06               :2 ,	// 13:12
	reg_dj_pattern0_1_07               :2 ,	// 15:14
	reg_dj_pattern0_1_08               :2 ,	// 17:16
	reg_dj_pattern0_1_09               :2 ,	// 19:18
	reg_dj_pattern0_1_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008b1cL shp_dj_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_2_00               :2 ,	// 1:0
	reg_dj_pattern0_2_01               :2 ,	// 3:2
	reg_dj_pattern0_2_02               :2 ,	// 5:4
	reg_dj_pattern0_2_03               :2 ,	// 7:6
	reg_dj_pattern0_2_04               :2 ,	// 9:8
	reg_dj_pattern0_2_05               :2 ,	// 11:10
	reg_dj_pattern0_2_06               :2 ,	// 13:12
	reg_dj_pattern0_2_07               :2 ,	// 15:14
	reg_dj_pattern0_2_08               :2 ,	// 17:16
	reg_dj_pattern0_2_09               :2 ,	// 19:18
	reg_dj_pattern0_2_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008b20L shp_dj_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_3_00               :2 ,	// 1:0
	reg_dj_pattern0_3_01               :2 ,	// 3:2
	reg_dj_pattern0_3_02               :2 ,	// 5:4
	reg_dj_pattern0_3_03               :2 ,	// 7:6
	reg_dj_pattern0_3_04               :2 ,	// 9:8
	reg_dj_pattern0_3_05               :2 ,	// 11:10
	reg_dj_pattern0_3_06               :2 ,	// 13:12
	reg_dj_pattern0_3_07               :2 ,	// 15:14
	reg_dj_pattern0_3_08               :2 ,	// 17:16
	reg_dj_pattern0_3_09               :2 ,	// 19:18
	reg_dj_pattern0_3_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008b24L shp_dj_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_4_00               :2 ,	// 1:0
	reg_dj_pattern0_4_01               :2 ,	// 3:2
	reg_dj_pattern0_4_02               :2 ,	// 5:4
	reg_dj_pattern0_4_03               :2 ,	// 7:6
	reg_dj_pattern0_4_04               :2 ,	// 9:8
	reg_dj_pattern0_4_05               :2 ,	// 11:10
	reg_dj_pattern0_4_06               :2 ,	// 13:12
	reg_dj_pattern0_4_07               :2 ,	// 15:14
	reg_dj_pattern0_4_08               :2 ,	// 17:16
	reg_dj_pattern0_4_09               :2 ,	// 19:18
	reg_dj_pattern0_4_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008b28L shp_dj_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_5_00               :2 ,	// 1:0
	reg_dj_pattern0_5_01               :2 ,	// 3:2
	reg_dj_pattern0_5_02               :2 ,	// 5:4
	reg_dj_pattern0_5_03               :2 ,	// 7:6
	reg_dj_pattern0_5_04               :2 ,	// 9:8
	reg_dj_pattern0_5_05               :2 ,	// 11:10
	reg_dj_pattern0_5_06               :2 ,	// 13:12
	reg_dj_pattern0_5_07               :2 ,	// 15:14
	reg_dj_pattern0_5_08               :2 ,	// 17:16
	reg_dj_pattern0_5_09               :2 ,	// 19:18
	reg_dj_pattern0_5_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008b2cL shp_dj_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_6_00               :2 ,	// 1:0
	reg_dj_pattern0_6_01               :2 ,	// 3:2
	reg_dj_pattern0_6_02               :2 ,	// 5:4
	reg_dj_pattern0_6_03               :2 ,	// 7:6
	reg_dj_pattern0_6_04               :2 ,	// 9:8
	reg_dj_pattern0_6_05               :2 ,	// 11:10
	reg_dj_pattern0_6_06               :2 ,	// 13:12
	reg_dj_pattern0_6_07               :2 ,	// 15:14
	reg_dj_pattern0_6_08               :2 ,	// 17:16
	reg_dj_pattern0_6_09               :2 ,	// 19:18
	reg_dj_pattern0_6_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008b30L shp_dj_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_flip0_h            :1 ,	// 0:0
	reg_dj_pattern0_flip0_v            :1 ,	// 1:1
	reg_dj_pattern0_flip1_h            :1 ,	// 2:2
	reg_dj_pattern0_flip1_v            :1 ,	// 3:3
	reg_dj_pattern0_flip2_h            :1 ,	// 4:4
	reg_dj_pattern0_flip2_v            :1 ,	// 5:5
	reg_dj_pattern0_flip3_h            :1 ,	// 6:6
	reg_dj_pattern0_flip3_v            :1 ;	// 7:7
}PE_O20_SHP_2K_DJ_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008b34L shp_dj_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_0_00               :2 ,	// 1:0
	reg_dj_pattern1_0_01               :2 ,	// 3:2
	reg_dj_pattern1_0_02               :2 ,	// 5:4
	reg_dj_pattern1_0_03               :2 ,	// 7:6
	reg_dj_pattern1_0_04               :2 ,	// 9:8
	reg_dj_pattern1_0_05               :2 ,	// 11:10
	reg_dj_pattern1_0_06               :2 ,	// 13:12
	reg_dj_pattern1_0_07               :2 ,	// 15:14
	reg_dj_pattern1_0_08               :2 ,	// 17:16
	reg_dj_pattern1_0_09               :2 ,	// 19:18
	reg_dj_pattern1_0_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9008b38L shp_dj_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_1_00               :2 ,	// 1:0
	reg_dj_pattern1_1_01               :2 ,	// 3:2
	reg_dj_pattern1_1_02               :2 ,	// 5:4
	reg_dj_pattern1_1_03               :2 ,	// 7:6
	reg_dj_pattern1_1_04               :2 ,	// 9:8
	reg_dj_pattern1_1_05               :2 ,	// 11:10
	reg_dj_pattern1_1_06               :2 ,	// 13:12
	reg_dj_pattern1_1_07               :2 ,	// 15:14
	reg_dj_pattern1_1_08               :2 ,	// 17:16
	reg_dj_pattern1_1_09               :2 ,	// 19:18
	reg_dj_pattern1_1_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9008b3cL shp_dj_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_2_00               :2 ,	// 1:0
	reg_dj_pattern1_2_01               :2 ,	// 3:2
	reg_dj_pattern1_2_02               :2 ,	// 5:4
	reg_dj_pattern1_2_03               :2 ,	// 7:6
	reg_dj_pattern1_2_04               :2 ,	// 9:8
	reg_dj_pattern1_2_05               :2 ,	// 11:10
	reg_dj_pattern1_2_06               :2 ,	// 13:12
	reg_dj_pattern1_2_07               :2 ,	// 15:14
	reg_dj_pattern1_2_08               :2 ,	// 17:16
	reg_dj_pattern1_2_09               :2 ,	// 19:18
	reg_dj_pattern1_2_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9008b40L shp_dj_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_3_00               :2 ,	// 1:0
	reg_dj_pattern1_3_01               :2 ,	// 3:2
	reg_dj_pattern1_3_02               :2 ,	// 5:4
	reg_dj_pattern1_3_03               :2 ,	// 7:6
	reg_dj_pattern1_3_04               :2 ,	// 9:8
	reg_dj_pattern1_3_05               :2 ,	// 11:10
	reg_dj_pattern1_3_06               :2 ,	// 13:12
	reg_dj_pattern1_3_07               :2 ,	// 15:14
	reg_dj_pattern1_3_08               :2 ,	// 17:16
	reg_dj_pattern1_3_09               :2 ,	// 19:18
	reg_dj_pattern1_3_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008b44L shp_dj_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_4_00               :2 ,	// 1:0
	reg_dj_pattern1_4_01               :2 ,	// 3:2
	reg_dj_pattern1_4_02               :2 ,	// 5:4
	reg_dj_pattern1_4_03               :2 ,	// 7:6
	reg_dj_pattern1_4_04               :2 ,	// 9:8
	reg_dj_pattern1_4_05               :2 ,	// 11:10
	reg_dj_pattern1_4_06               :2 ,	// 13:12
	reg_dj_pattern1_4_07               :2 ,	// 15:14
	reg_dj_pattern1_4_08               :2 ,	// 17:16
	reg_dj_pattern1_4_09               :2 ,	// 19:18
	reg_dj_pattern1_4_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008b48L shp_dj_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_5_00               :2 ,	// 1:0
	reg_dj_pattern1_5_01               :2 ,	// 3:2
	reg_dj_pattern1_5_02               :2 ,	// 5:4
	reg_dj_pattern1_5_03               :2 ,	// 7:6
	reg_dj_pattern1_5_04               :2 ,	// 9:8
	reg_dj_pattern1_5_05               :2 ,	// 11:10
	reg_dj_pattern1_5_06               :2 ,	// 13:12
	reg_dj_pattern1_5_07               :2 ,	// 15:14
	reg_dj_pattern1_5_08               :2 ,	// 17:16
	reg_dj_pattern1_5_09               :2 ,	// 19:18
	reg_dj_pattern1_5_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9008b4cL shp_dj_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_6_00               :2 ,	// 1:0
	reg_dj_pattern1_6_01               :2 ,	// 3:2
	reg_dj_pattern1_6_02               :2 ,	// 5:4
	reg_dj_pattern1_6_03               :2 ,	// 7:6
	reg_dj_pattern1_6_04               :2 ,	// 9:8
	reg_dj_pattern1_6_05               :2 ,	// 11:10
	reg_dj_pattern1_6_06               :2 ,	// 13:12
	reg_dj_pattern1_6_07               :2 ,	// 15:14
	reg_dj_pattern1_6_08               :2 ,	// 17:16
	reg_dj_pattern1_6_09               :2 ,	// 19:18
	reg_dj_pattern1_6_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9008b50L shp_dj_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_flip0_h            :1 ,	// 0:0
	reg_dj_pattern1_flip0_v            :1 ,	// 1:1
	reg_dj_pattern1_flip1_h            :1 ,	// 2:2
	reg_dj_pattern1_flip1_v            :1 ;	// 3:3
}PE_O20_SHP_2K_DJ_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9008b54L shp_dj_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_0_00               :2 ,	// 1:0
	reg_dj_pattern2_0_01               :2 ,	// 3:2
	reg_dj_pattern2_0_02               :2 ,	// 5:4
	reg_dj_pattern2_0_03               :2 ,	// 7:6
	reg_dj_pattern2_0_04               :2 ,	// 9:8
	reg_dj_pattern2_0_05               :2 ,	// 11:10
	reg_dj_pattern2_0_06               :2 ,	// 13:12
	reg_dj_pattern2_0_07               :2 ,	// 15:14
	reg_dj_pattern2_0_08               :2 ,	// 17:16
	reg_dj_pattern2_0_09               :2 ,	// 19:18
	reg_dj_pattern2_0_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9008b58L shp_dj_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_1_00               :2 ,	// 1:0
	reg_dj_pattern2_1_01               :2 ,	// 3:2
	reg_dj_pattern2_1_02               :2 ,	// 5:4
	reg_dj_pattern2_1_03               :2 ,	// 7:6
	reg_dj_pattern2_1_04               :2 ,	// 9:8
	reg_dj_pattern2_1_05               :2 ,	// 11:10
	reg_dj_pattern2_1_06               :2 ,	// 13:12
	reg_dj_pattern2_1_07               :2 ,	// 15:14
	reg_dj_pattern2_1_08               :2 ,	// 17:16
	reg_dj_pattern2_1_09               :2 ,	// 19:18
	reg_dj_pattern2_1_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9008b5cL shp_dj_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_2_00               :2 ,	// 1:0
	reg_dj_pattern2_2_01               :2 ,	// 3:2
	reg_dj_pattern2_2_02               :2 ,	// 5:4
	reg_dj_pattern2_2_03               :2 ,	// 7:6
	reg_dj_pattern2_2_04               :2 ,	// 9:8
	reg_dj_pattern2_2_05               :2 ,	// 11:10
	reg_dj_pattern2_2_06               :2 ,	// 13:12
	reg_dj_pattern2_2_07               :2 ,	// 15:14
	reg_dj_pattern2_2_08               :2 ,	// 17:16
	reg_dj_pattern2_2_09               :2 ,	// 19:18
	reg_dj_pattern2_2_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9008b60L shp_dj_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_3_00               :2 ,	// 1:0
	reg_dj_pattern2_3_01               :2 ,	// 3:2
	reg_dj_pattern2_3_02               :2 ,	// 5:4
	reg_dj_pattern2_3_03               :2 ,	// 7:6
	reg_dj_pattern2_3_04               :2 ,	// 9:8
	reg_dj_pattern2_3_05               :2 ,	// 11:10
	reg_dj_pattern2_3_06               :2 ,	// 13:12
	reg_dj_pattern2_3_07               :2 ,	// 15:14
	reg_dj_pattern2_3_08               :2 ,	// 17:16
	reg_dj_pattern2_3_09               :2 ,	// 19:18
	reg_dj_pattern2_3_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9008b64L shp_dj_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_4_00               :2 ,	// 1:0
	reg_dj_pattern2_4_01               :2 ,	// 3:2
	reg_dj_pattern2_4_02               :2 ,	// 5:4
	reg_dj_pattern2_4_03               :2 ,	// 7:6
	reg_dj_pattern2_4_04               :2 ,	// 9:8
	reg_dj_pattern2_4_05               :2 ,	// 11:10
	reg_dj_pattern2_4_06               :2 ,	// 13:12
	reg_dj_pattern2_4_07               :2 ,	// 15:14
	reg_dj_pattern2_4_08               :2 ,	// 17:16
	reg_dj_pattern2_4_09               :2 ,	// 19:18
	reg_dj_pattern2_4_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9008b68L shp_dj_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_5_00               :2 ,	// 1:0
	reg_dj_pattern2_5_01               :2 ,	// 3:2
	reg_dj_pattern2_5_02               :2 ,	// 5:4
	reg_dj_pattern2_5_03               :2 ,	// 7:6
	reg_dj_pattern2_5_04               :2 ,	// 9:8
	reg_dj_pattern2_5_05               :2 ,	// 11:10
	reg_dj_pattern2_5_06               :2 ,	// 13:12
	reg_dj_pattern2_5_07               :2 ,	// 15:14
	reg_dj_pattern2_5_08               :2 ,	// 17:16
	reg_dj_pattern2_5_09               :2 ,	// 19:18
	reg_dj_pattern2_5_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc9008b6cL shp_dj_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_6_00               :2 ,	// 1:0
	reg_dj_pattern2_6_01               :2 ,	// 3:2
	reg_dj_pattern2_6_02               :2 ,	// 5:4
	reg_dj_pattern2_6_03               :2 ,	// 7:6
	reg_dj_pattern2_6_04               :2 ,	// 9:8
	reg_dj_pattern2_6_05               :2 ,	// 11:10
	reg_dj_pattern2_6_06               :2 ,	// 13:12
	reg_dj_pattern2_6_07               :2 ,	// 15:14
	reg_dj_pattern2_6_08               :2 ,	// 17:16
	reg_dj_pattern2_6_09               :2 ,	// 19:18
	reg_dj_pattern2_6_10               :2 ;	// 21:20
}PE_O20_SHP_2K_DJ_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc9008b70L shp_dj_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_flip0_h            :1 ,	// 0:0
	reg_dj_pattern2_flip0_v            :1 ,	// 1:1
	reg_dj_pattern2_flip1_h            :1 ,	// 2:2
	reg_dj_pattern2_flip1_v            :1 ;	// 3:3
}PE_O20_SHP_2K_DJ_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc9008b74L shp_dj_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g0_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g0_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g0_max                 :8 ;	// 23:16
}PE_O20_SHP_2K_DJ_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc9008b78L shp_dj_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g1_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g1_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g1_max                 :8 ;	// 23:16
}PE_O20_SHP_2K_DJ_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc9008b7cL shp_dj_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g2_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g2_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g2_max                 :8 ;	// 23:16
}PE_O20_SHP_2K_DJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9008b80L shp_dj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_base                   :8 ,	// 7:0
	reg_dj_soft_sel_1357_gain          :8 ,	// 15:8
	reg_dj_soft_single_match_en        :1 ;	// 16:16
}PE_O20_SHP_2K_DJ_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9008b90L shp_db_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_detour                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_dir_blur_buf_detour            :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_dir_blur_en                    :1 ;	// 8:8
}PE_O20_SHP_2K_DB_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008b94L shp_db_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_base                  :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dir_blur_gain                  :8 ;	// 23:16
}PE_O20_SHP_2K_DB_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ba0L shp_dj_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win0_en                 :1 ,	// 0:0
	reg_win_dj_win1_en                 :1 ,	// 1:1
	reg_win_dj_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dj_win_outside             :1 ,	// 6:6
	reg_win_dj_win_en                  :1 ,	// 7:7
	reg_win_dj_bdr_alpha               :5 ,	// 12:8
	reg_win_dj_bdr_wid                 :2 ,	// 14:13
	reg_win_dj_bdr_en                  :1 ,	// 15:15
	reg_win_dj_cr5                     :5 ,	// 20:16
	reg_win_dj_cb5                     :5 ,	// 25:21
	reg_win_dj_yy6                     :6 ;	// 31:26
}PE_O20_SHP_2K_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ba4L shp_dj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_O20_SHP_2K_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ba8L shp_dj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_O20_SHP_2K_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008bacL shp_dj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_O20_SHP_2K_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008bb0L shp_dj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_O20_SHP_2K_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008d00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O20_SHP_2K_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008d04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O20_SHP_2K_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008d08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O20_SHP_2K_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008d0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O20_SHP_2K_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008d10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O20_SHP_2K_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008d14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O20_SHP_2K_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008d60L shp_core_fd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_CORE_FD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008d64L shp_core_fd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_CORE_FD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008d68L shp_core_fd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_CORE_FD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008d6cL shp_core_fd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_CORE_FD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008e00L shp_core_tmap_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_window0;	// 31:0
}PE_O20_SHP_2K_CORE_TMAP_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008e04L shp_core_tmap_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_window1;	// 31:0
}PE_O20_SHP_2K_CORE_TMAP_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008e08L shp_core_tmap_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_0                   :16,	// 15:0
	ro_tmap_status_1                   :16;	// 31:16
}PE_O20_SHP_2K_CORE_TMAP_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008e0cL shp_core_tmap_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_2                   :16,	// 15:0
	ro_tmap_status_3                   :16;	// 31:16
}PE_O20_SHP_2K_CORE_TMAP_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008e10L shp_core_tmap_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_4                   :16,	// 15:0
	ro_tmap_status_5                   :16;	// 31:16
}PE_O20_SHP_2K_CORE_TMAP_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008e14L shp_core_tmap_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_6                   :16,	// 15:0
	ro_tmap_status_7                   :16;	// 31:16
}PE_O20_SHP_2K_CORE_TMAP_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008e18L shp_core_tmap_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_8                   :16,	// 15:0
	ro_tmap_status_9                   :16;	// 31:16
}PE_O20_SHP_2K_CORE_TMAP_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008e1cL shp_core_tmap_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_10                  :16,	// 15:0
	ro_tmap_status_11                  :16;	// 31:16
}PE_O20_SHP_2K_CORE_TMAP_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008ef0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cvd_pattern_detect                 :1 ,	//reserved
	color_bar                          :1 ,	//reserved
	vfy_glb_en                         :1 ;	//VFILTER_CTRL_01, reg_glb_vflt_en
}PE_O20_SHP_2K_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ef4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ef8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008efcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_2K_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc9009c00L sr_merge_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_sr_merge_demo_mode_en          :1 ,	// 4:4
	reg_sr_merge_demo_mode             :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_sr_merge_master_gain           :8 ,	// 15:8
	reg_sr_merge_ti_en                 :1 ,	// 16:16
	reserved03                         :3 ,	// reserved
	reg_sr_merge_ti_gain               :8 ,	// 27:20
	reg_sr_merge_debug_mode            :3 ;	// 30:28
}SRE_O20_SR_MERGE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c04L sr_merge_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_width                 :16,	// 15:0
	reg_sr_merge_height                :16;	// 31:16
}SRE_O20_SR_MERGE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c08L sr_merge_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_demo_start_pts_x0     :16,	// 15:0
	reg_sr_merge_demo_start_pts_y0     :16;	// 31:16
}SRE_O20_SR_MERGE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c0cL sr_merge_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_demo_end_pts_x1       :16,	// 15:0
	reg_sr_merge_demo_end_pts_y1       :16;	// 31:16
}SRE_O20_SR_MERGE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009c10L sr_merge_spatial_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_residual_blur_en               :1 ;	// 0:0
}SRE_O20_SR_MERGE_SPATIAL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c14L sr_merge_spatial_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_residual_blur_filt_00          :4 ,	// 3:0
	reg_residual_blur_filt_01          :4 ,	// 7:4
	reg_residual_blur_filt_02          :4 ,	// 11:8
	reg_residual_blur_filt_10          :4 ,	// 15:12
	reg_residual_blur_filt_11          :4 ,	// 19:16
	reg_residual_blur_filt_12          :4 ;	// 23:20
}SRE_O20_SR_MERGE_SPATIAL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c20L sr_merge_mmd_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_en                         :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_mmd_tap_size                   :4 ;	// 7:4
}SRE_O20_SR_MERGE_MMD_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c24L sr_merge_mmd_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y0                :8 ,	// 7:0
	reg_mmd_diff_lut_x0                :8 ,	// 15:8
	reg_mmd_diff_lut_y1                :8 ,	// 23:16
	reg_mmd_diff_lut_x1                :8 ;	// 31:24
}SRE_O20_SR_MERGE_MMD_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c28L sr_merge_mmd_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y2                :8 ,	// 7:0
	reg_mmd_diff_lut_x2                :8 ,	// 15:8
	reg_mmd_diff_lut_y3                :8 ,	// 23:16
	reg_mmd_diff_lut_x3                :8 ;	// 31:24
}SRE_O20_SR_MERGE_MMD_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c2cL sr_merge_mmd_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y4                :8 ,	// 7:0
	reg_mmd_diff_lut_x4                :8 ,	// 15:8
	reg_mmd_diff_lut_y5                :8 ,	// 23:16
	reg_mmd_diff_lut_x5                :8 ;	// 31:24
}SRE_O20_SR_MERGE_MMD_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009c30L sr_merge_mmd_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y6                :8 ,	// 7:0
	reg_mmd_diff_lut_x6                :8 ,	// 15:8
	reg_mmd_diff_lut_y7                :8 ,	// 23:16
	reg_mmd_diff_lut_x7                :8 ;	// 31:24
}SRE_O20_SR_MERGE_MMD_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009c34L sr_merge_mmd_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ti_gain_lut_y0                 :8 ,	// 7:0
	reg_ti_gain_lut_x0                 :8 ,	// 15:8
	reg_ti_gain_lut_y1                 :8 ,	// 23:16
	reg_ti_gain_lut_x1                 :8 ;	// 31:24
}SRE_O20_SR_MERGE_MMD_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009c38L sr_merge_mmd_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ti_gain_lut_y2                 :8 ,	// 7:0
	reg_ti_gain_lut_x2                 :8 ,	// 15:8
	reg_ti_gain_lut_y3                 :8 ,	// 23:16
	reg_ti_gain_lut_x3                 :8 ;	// 31:24
}SRE_O20_SR_MERGE_MMD_06_T;
/*-----------------------------------------------------------------------------
                             0xc9009c50L sr_merge_sobel_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sobel_mode                     :4 ;	// 3:0
}SRE_O20_SR_MERGE_SOBEL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c54L sr_merge_sobel_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sobel_lut_y0                   :8 ,	// 7:0
	reg_sobel_lut_x0                   :8 ,	// 15:8
	reg_sobel_lut_y1                   :8 ,	// 23:16
	reg_sobel_lut_x1                   :8 ;	// 31:24
}SRE_O20_SR_MERGE_SOBEL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c58L sr_merge_sobel_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sobel_lut_y2                   :8 ,	// 7:0
	reg_sobel_lut_x2                   :8 ,	// 15:8
	reg_sobel_lut_y3                   :8 ,	// 23:16
	reg_sobel_lut_x3                   :8 ;	// 31:24
}SRE_O20_SR_MERGE_SOBEL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c70L sr_merge_nr_gain_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nr_gain_en                     :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_nr_gain_th                     :10;	// 13:4
}SRE_O20_SR_MERGE_NR_GAIN_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c74L sr_merge_nr_gain_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nr_gain_lut_y0                 :8 ,	// 7:0
	reg_nr_gain_lut_x0                 :8 ,	// 15:8
	reg_nr_gain_lut_y1                 :8 ,	// 23:16
	reg_nr_gain_lut_x1                 :8 ;	// 31:24
}SRE_O20_SR_MERGE_NR_GAIN_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c78L sr_merge_nr_gain_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nr_gain_lut_y2                 :8 ,	// 7:0
	reg_nr_gain_lut_x2                 :8 ,	// 15:8
	reg_nr_gain_lut_y3                 :8 ,	// 23:16
	reg_nr_gain_lut_x3                 :8 ;	// 31:24
}SRE_O20_SR_MERGE_NR_GAIN_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c90L sr_merge_blend_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_en                   :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_blend_flat_threshold           :4 ,	// 7:4
	reserved02                         :12,	// reserved
	reg_blend_amp_weight               :12;	// 31:20
}SRE_O20_SR_MERGE_BLEND_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c94L sr_merge_blend_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y1                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x1                   :10;	// 25:16
}SRE_O20_SR_MERGE_BLEND_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c98L sr_merge_blend_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y0                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x0                   :10;	// 25:16
}SRE_O20_SR_MERGE_BLEND_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c9cL sr_merge_blend_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y3                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x3                   :10;	// 25:16
}SRE_O20_SR_MERGE_BLEND_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca0L sr_merge_blend_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y2                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x2                   :10;	// 25:16
}SRE_O20_SR_MERGE_BLEND_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009d00L sr_merge_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_O20_SR_MERGE_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009d04L sr_merge_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :16,	// 15:0
	reg_mon_in_hori_cnt                :16;	// 31:16
}SRE_O20_SR_MERGE_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009d08L sr_merge_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :16,	// 15:0
	reg_mon_out_hori_cnt               :16;	// 31:16
}SRE_O20_SR_MERGE_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009d0cL sr_merge_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :16,	// 15:0
	reg_mon_fin_in_vert_cnt            :16;	// 31:16
}SRE_O20_SR_MERGE_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009d10L sr_merge_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}SRE_O20_SR_MERGE_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009d14L sr_merge_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}SRE_O20_SR_MERGE_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009df0L sr_merge_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_O20_SR_MERGE_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009df4L sr_merge_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_O20_SR_MERGE_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009df8L sr_merge_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_O20_SR_MERGE_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009dfcL sr_merge_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_O20_SR_MERGE_FSW_CTRL_03_T;

typedef struct
{ 
	PE_O20_SHP_CHR_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O20_SHP_CHR_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O20_SHP_CHR_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	UINT32                                            reserved3[253];	//0xc-0x3fc
	PE_O20_SHP_CDJ_CTRL_00_T                          shp_cdj_ctrl_00;	//0x0400
	PE_O20_SHP_CDJ_CTRL_01_T                          shp_cdj_ctrl_01;	//0x0404
	PE_O20_SHP_CDJ_CTRL_02_T                          shp_cdj_ctrl_02;	//0x0408
	PE_O20_SHP_CDJ_CTRL_03_T                          shp_cdj_ctrl_03;	//0x040C
	PE_O20_SHP_CDJ_CTRL_04_T                          shp_cdj_ctrl_04;	//0x0410
	PE_O20_SHP_CDJ_CTRL_05_T                          shp_cdj_ctrl_05;	//0x0414
	PE_O20_SHP_CDJ_CTRL_06_T                          shp_cdj_ctrl_06;	//0x0418
	PE_O20_SHP_CDJ_CTRL_07_T                          shp_cdj_ctrl_07;	//0x041C
	PE_O20_SHP_CDJ_CTRL_08_T                          shp_cdj_ctrl_08;	//0x0420
	PE_O20_SHP_CDJ_CTRL_09_T                          shp_cdj_ctrl_09;	//0x0424
	PE_O20_SHP_CDJ_CTRL_0A_T                          shp_cdj_ctrl_0a;	//0x0428
	PE_O20_SHP_CDJ_CTRL_0B_T                          shp_cdj_ctrl_0b;	//0x042C
	PE_O20_SHP_CDJ_CTRL_0C_T                          shp_cdj_ctrl_0c;	//0x0430
	PE_O20_SHP_CDJ_CTRL_0D_T                          shp_cdj_ctrl_0d;	//0x0434
	PE_O20_SHP_CDJ_CTRL_0E_T                          shp_cdj_ctrl_0e;	//0x0438
	PE_O20_SHP_CDJ_CTRL_0F_T                          shp_cdj_ctrl_0f;	//0x043C
	PE_O20_SHP_CDJ_CTRL_10_T                          shp_cdj_ctrl_10;	//0x0440
	PE_O20_SHP_CDJ_CTRL_11_T                          shp_cdj_ctrl_11;	//0x0444
	PE_O20_SHP_CDJ_CTRL_12_T                          shp_cdj_ctrl_12;	//0x0448
	PE_O20_SHP_CDJ_CTRL_13_T                          shp_cdj_ctrl_13;	//0x044C
	PE_O20_SHP_CDJ_CTRL_14_T                          shp_cdj_ctrl_14;	//0x0450
	PE_O20_SHP_CDJ_CTRL_15_T                          shp_cdj_ctrl_15;	//0x0454
	PE_O20_SHP_CDJ_CTRL_16_T                          shp_cdj_ctrl_16;	//0x0458
	PE_O20_SHP_CDJ_CTRL_17_T                          shp_cdj_ctrl_17;	//0x045C
	PE_O20_SHP_CDJ_CTRL_18_T                          shp_cdj_ctrl_18;	//0x0460
	PE_O20_SHP_CDJ_CTRL_19_T                          shp_cdj_ctrl_19;	//0x0464
	PE_O20_SHP_CDJ_CTRL_1A_T                          shp_cdj_ctrl_1a;	//0x0468
	PE_O20_SHP_CDJ_CTRL_1B_T                          shp_cdj_ctrl_1b;	//0x046C
	PE_O20_SHP_CDJ_CTRL_1C_T                          shp_cdj_ctrl_1c;	//0x0470
	PE_O20_SHP_CDJ_CTRL_1D_T                          shp_cdj_ctrl_1d;	//0x0474
	PE_O20_SHP_CDJ_CTRL_1E_T                          shp_cdj_ctrl_1e;	//0x0478
	PE_O20_SHP_CDJ_CTRL_1F_T                          shp_cdj_ctrl_1f;	//0x047C
	PE_O20_SHP_CDJ_CTRL_20_T                          shp_cdj_ctrl_20;	//0x0480
	UINT32                                            reserved36[3];	//0x484-0x48c
	PE_O20_SHP_CDIR_BLUR_CTRL_00_T                    shp_cdir_blur_ctrl_00;	//0x0490
	PE_O20_SHP_CDIR_BLUR_CTRL_01_T                    shp_cdir_blur_ctrl_01;	//0x0494
	UINT32                                            reserved38[2];	//0x498-0x49c
	PE_O20_SHP_CDJ_WIN_CTRL_00_T                      shp_cdj_win_ctrl_00;	//0x04A0
	PE_O20_SHP_CDJ_WIN_CTRL_01_T                      shp_cdj_win_ctrl_01;	//0x04A4
	PE_O20_SHP_CDJ_WIN_CTRL_02_T                      shp_cdj_win_ctrl_02;	//0x04A8
	PE_O20_SHP_CDJ_WIN_CTRL_03_T                      shp_cdj_win_ctrl_03;	//0x04AC
	PE_O20_SHP_CDJ_WIN_CTRL_04_T                      shp_cdj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved43[83];	//0x4b4-0x5fc
	PE_O20_SHP_CHR_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_O20_SHP_CHR_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_O20_SHP_CHR_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_O20_SHP_CHR_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_O20_SHP_CHR_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_O20_SHP_CHR_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved49[54];	//0x618-0x6ec
	PE_O20_SHP_CHR_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x06F0
	PE_O20_SHP_CHR_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x06F4
	PE_O20_SHP_CHR_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x06F8
	PE_O20_SHP_CHR_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x06FC
}PE_SR_CHR_SHP_REG_O20_T;

typedef struct
{ 
	PE_O20_SHP_2K_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O20_SHP_2K_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O20_SHP_2K_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	PE_O20_SHP_2K_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0x000C
	UINT32                                            reserved4[12];	//0x10-0x3c
	PE_O20_SHP_2K_PAT_GEN_CTRL_00_T                      shp_pat_gen_ctrl_00;	//0x0040
	UINT32                                            reserved5[43];	//0x44-0xec
	PE_O20_SHP_2K_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x00F0
	UINT32                                            reserved6[3];	//0xf4-0xfc
	PE_O20_SHP_2K_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0100
	PE_O20_SHP_2K_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0104
	PE_O20_SHP_2K_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0108
	PE_O20_SHP_2K_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x010C
	PE_O20_SHP_2K_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0110
	PE_O20_SHP_2K_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0114
	PE_O20_SHP_2K_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0118
	PE_O20_SHP_2K_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x011C
	PE_O20_SHP_2K_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0120
	PE_O20_SHP_2K_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0124
	PE_O20_SHP_2K_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0128
	PE_O20_SHP_2K_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x012C
	PE_O20_SHP_2K_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0130
	PE_O20_SHP_2K_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0134
	PE_O20_SHP_2K_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0138
	PE_O20_SHP_2K_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x013C
	PE_O20_SHP_2K_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0140
	PE_O20_SHP_2K_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0144
	PE_O20_SHP_2K_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0148
	PE_O20_SHP_2K_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O20_SHP_2K_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O20_SHP_2K_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O20_SHP_2K_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	UINT32                                            reserved29;	//0x15c
	PE_O20_SHP_2K_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O20_SHP_2K_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O20_SHP_2K_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O20_SHP_2K_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O20_SHP_2K_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O20_SHP_2K_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O20_SHP_2K_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O20_SHP_2K_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O20_SHP_2K_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O20_SHP_2K_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O20_SHP_2K_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O20_SHP_2K_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O20_SHP_2K_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O20_SHP_2K_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	UINT32                                            reserved43[2];	//0x198-0x19c
	PE_O20_SHP_2K_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O20_SHP_2K_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O20_SHP_2K_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O20_SHP_2K_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O20_SHP_2K_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	UINT32                                            reserved48[3];	//0x1b4-0x1bc
	PE_O20_SHP_2K_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O20_SHP_2K_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O20_SHP_2K_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O20_SHP_2K_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O20_SHP_2K_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O20_SHP_2K_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O20_SHP_2K_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O20_SHP_2K_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O20_SHP_2K_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O20_SHP_2K_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O20_SHP_2K_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O20_SHP_2K_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O20_SHP_2K_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O20_SHP_2K_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O20_SHP_2K_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O20_SHP_2K_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O20_SHP_2K_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O20_SHP_2K_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O20_SHP_2K_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O20_SHP_2K_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O20_SHP_2K_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	UINT32                                            reserved69[3];	//0x214-0x21c
	PE_O20_SHP_2K_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O20_SHP_2K_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O20_SHP_2K_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O20_SHP_2K_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O20_SHP_2K_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	UINT32                                            reserved74[3];	//0x234-0x23c
	PE_O20_SHP_2K_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O20_SHP_2K_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O20_SHP_2K_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O20_SHP_2K_TGEN_CTRL_03_T                         shp_tgen_ctrl_03;	//0x024C
	UINT32                                            reserved78;	//0x250
	PE_O20_SHP_2K_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O20_SHP_2K_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O20_SHP_2K_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O20_SHP_2K_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O20_SHP_2K_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O20_SHP_2K_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O20_SHP_2K_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O20_SHP_2K_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O20_SHP_2K_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	UINT32                                            reserved87[2];	//0x278-0x27c
	PE_O20_SHP_2K_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O20_SHP_2K_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O20_SHP_2K_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O20_SHP_2K_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O20_SHP_2K_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O20_SHP_2K_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O20_SHP_2K_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O20_SHP_2K_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O20_SHP_2K_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O20_SHP_2K_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O20_SHP_2K_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O20_SHP_2K_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O20_SHP_2K_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O20_SHP_2K_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O20_SHP_2K_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O20_SHP_2K_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O20_SHP_2K_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O20_SHP_2K_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O20_SHP_2K_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O20_SHP_2K_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O20_SHP_2K_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O20_SHP_2K_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O20_SHP_2K_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O20_SHP_2K_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O20_SHP_2K_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O20_SHP_2K_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O20_SHP_2K_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O20_SHP_2K_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O20_SHP_2K_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O20_SHP_2K_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O20_SHP_2K_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O20_SHP_2K_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O20_SHP_2K_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O20_SHP_2K_NNTG_CTRL_01_T                         shp_nntg_ctrl_01;	//0x0304
	PE_O20_SHP_2K_NNTG_CTRL_02_T                         shp_nntg_ctrl_02;	//0x0308
	PE_O20_SHP_2K_NNTG_CTRL_03_T                         shp_nntg_ctrl_03;	//0x030C
	PE_O20_SHP_2K_NNTG_CTRL_04_T                         shp_nntg_ctrl_04;	//0x0310
	PE_O20_SHP_2K_NNTG_CTRL_05_T                         shp_nntg_ctrl_05;	//0x0314
	UINT32                                            reserved125[5];	//0x318-0x328
	PE_O20_SHP_2K_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O20_SHP_2K_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O20_SHP_2K_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O20_SHP_2K_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O20_SHP_2K_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O20_SHP_2K_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O20_SHP_2K_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O20_SHP_2K_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O20_SHP_2K_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O20_SHP_2K_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O20_SHP_2K_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	UINT32                                            reserved136[2];	//0x358-0x35c
	PE_O20_SHP_2K_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O20_SHP_2K_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O20_SHP_2K_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	UINT32                                            reserved139[13];	//0x36c-0x39c
	PE_O20_SHP_2K_DP_WIN_CTRL_00_T                       shp_dp_win_ctrl_00;	//0x03A0
	PE_O20_SHP_2K_DP_WIN_CTRL_01_T                       shp_dp_win_ctrl_01;	//0x03A4
	PE_O20_SHP_2K_DP_WIN_CTRL_02_T                       shp_dp_win_ctrl_02;	//0x03A8
	PE_O20_SHP_2K_DP_WIN_CTRL_03_T                       shp_dp_win_ctrl_03;	//0x03AC
	PE_O20_SHP_2K_DP_WIN_CTRL_04_T                       shp_dp_win_ctrl_04;	//0x03B0
	UINT32                                            reserved144[3];	//0x3b4-0x3bc
	PE_O20_SHP_2K_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O20_SHP_2K_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x3C4
	PE_O20_SHP_2K_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x3C8
	PE_O20_SHP_2K_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O20_SHP_2K_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x3D0
	PE_O20_SHP_2K_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x3D4
	PE_O20_SHP_2K_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x3D8
	PE_O20_SHP_2K_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x3DC
	PE_O20_SHP_2K_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x3E0
	PE_O20_SHP_2K_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x3E4
	PE_O20_SHP_2K_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x3E8
	PE_O20_SHP_2K_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x3EC
	PE_O20_SHP_2K_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O20_SHP_2K_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O20_SHP_2K_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O20_SHP_2K_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O20_SHP_2K_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O20_SHP_2K_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O20_SHP_2K_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O20_SHP_2K_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O20_SHP_2K_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O20_SHP_2K_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O20_SHP_2K_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O20_SHP_2K_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O20_SHP_2K_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O20_SHP_2K_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O20_SHP_2K_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O20_SHP_2K_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O20_SHP_2K_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O20_SHP_2K_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O20_SHP_2K_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O20_SHP_2K_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O20_SHP_2K_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O20_SHP_2K_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O20_SHP_2K_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O20_SHP_2K_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O20_SHP_2K_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O20_SHP_2K_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O20_SHP_2K_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O20_SHP_2K_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O20_SHP_2K_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O20_SHP_2K_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O20_SHP_2K_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O20_SHP_2K_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O20_SHP_2K_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O20_SHP_2K_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O20_SHP_2K_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O20_SHP_2K_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O20_SHP_2K_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	UINT32                                            reserved193[3];	//0x484-0x48c
	PE_O20_SHP_2K_DB_CTRL_00_T                           shp_db_ctrl_00;	//0x0490
	PE_O20_SHP_2K_DB_CTRL_01_T                           shp_db_ctrl_01;	//0x0494
	UINT32                                            reserved195[2];	//0x498-0x49c
	PE_O20_SHP_2K_DJ_WIN_CTRL_00_T                       shp_dj_win_ctrl_00;	//0x04A0
	PE_O20_SHP_2K_DJ_WIN_CTRL_01_T                       shp_dj_win_ctrl_01;	//0x04A4
	PE_O20_SHP_2K_DJ_WIN_CTRL_02_T                       shp_dj_win_ctrl_02;	//0x04A8
	PE_O20_SHP_2K_DJ_WIN_CTRL_03_T                       shp_dj_win_ctrl_03;	//0x04AC
	PE_O20_SHP_2K_DJ_WIN_CTRL_04_T                       shp_dj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved200[83];	//0x4b4-0x5fc
	PE_O20_SHP_2K_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_O20_SHP_2K_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_O20_SHP_2K_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_O20_SHP_2K_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_O20_SHP_2K_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_O20_SHP_2K_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved206[18];	//0x618-0x65c
	PE_O20_SHP_2K_CORE_FD_STAT_00_T                      shp_core_fd_stat_00;	//0x0660
	PE_O20_SHP_2K_CORE_FD_STAT_01_T                      shp_core_fd_stat_01;	//0x0664
	PE_O20_SHP_2K_CORE_FD_STAT_02_T                      shp_core_fd_stat_02;	//0x0668
	PE_O20_SHP_2K_CORE_FD_STAT_03_T                      shp_core_fd_stat_03;	//0x066C
	UINT32                                            reserved210[36];	//0x670-0x6fc
	PE_O20_SHP_2K_CORE_TMAP_STAT_00_T                    shp_core_tmap_stat_00;	//0x0700
	PE_O20_SHP_2K_CORE_TMAP_STAT_01_T                    shp_core_tmap_stat_01;	//0x0704
	PE_O20_SHP_2K_CORE_TMAP_STAT_02_T                    shp_core_tmap_stat_02;	//0x0708
	PE_O20_SHP_2K_CORE_TMAP_STAT_03_T                    shp_core_tmap_stat_03;	//0x070C
	PE_O20_SHP_2K_CORE_TMAP_STAT_04_T                    shp_core_tmap_stat_04;	//0x0710
	PE_O20_SHP_2K_CORE_TMAP_STAT_05_T                    shp_core_tmap_stat_05;	//0x0714
	PE_O20_SHP_2K_CORE_TMAP_STAT_06_T                    shp_core_tmap_stat_06;	//0x0718
	PE_O20_SHP_2K_CORE_TMAP_STAT_07_T                    shp_core_tmap_stat_07;	//0x071C
	UINT32                                            reserved218[52];	//0x720-0x7ec
	PE_O20_SHP_2K_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x07F0
	PE_O20_SHP_2K_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x07F4
	PE_O20_SHP_2K_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x07F8
	PE_O20_SHP_2K_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x07FC
}PE_SR_2K_SHP_REG_O20_T;

typedef struct
{ 
	SRE_O20_SR_MERGE_CTRL_00_T                        sr_merge_ctrl_00;	//0x0000
	SRE_O20_SR_MERGE_CTRL_01_T                        sr_merge_ctrl_01;	//0x0004
	SRE_O20_SR_MERGE_CTRL_02_T                        sr_merge_ctrl_02;	//0x0008
	SRE_O20_SR_MERGE_CTRL_03_T                        sr_merge_ctrl_03;	//0x000C
	SRE_O20_SR_MERGE_SPATIAL_00_T                     sr_merge_spatial_00;	//0x0010
	SRE_O20_SR_MERGE_SPATIAL_01_T                     sr_merge_spatial_01;	//0x0014
	UINT32                                            reserved6[2];	//0x18-0x1c
	SRE_O20_SR_MERGE_MMD_00_T                         sr_merge_mmd_00;	//0x0020
	SRE_O20_SR_MERGE_MMD_01_T                         sr_merge_mmd_01;	//0x0024
	SRE_O20_SR_MERGE_MMD_02_T                         sr_merge_mmd_02;	//0x0028
	SRE_O20_SR_MERGE_MMD_03_T                         sr_merge_mmd_03;	//0x002C
	SRE_O20_SR_MERGE_MMD_04_T                         sr_merge_mmd_04;	//0x0030
	SRE_O20_SR_MERGE_MMD_05_T                         sr_merge_mmd_05;	//0x0034
	SRE_O20_SR_MERGE_MMD_06_T                         sr_merge_mmd_06;	//0x0038
	UINT32                                            reserved13[5];	//0x3c-0x4c
	SRE_O20_SR_MERGE_SOBEL_00_T                       sr_merge_sobel_00;	//0x0050
	SRE_O20_SR_MERGE_SOBEL_01_T                       sr_merge_sobel_01;	//0x0054
	SRE_O20_SR_MERGE_SOBEL_02_T                       sr_merge_sobel_02;	//0x0058
	UINT32                                            reserved16[5];	//0x5c-0x6c
	SRE_O20_SR_MERGE_NR_GAIN_00_T                     sr_merge_nr_gain_00;	//0x0070
	SRE_O20_SR_MERGE_NR_GAIN_01_T                     sr_merge_nr_gain_01;	//0x0074
	SRE_O20_SR_MERGE_NR_GAIN_02_T                     sr_merge_nr_gain_02;	//0x0078
	UINT32                                            reserved19[5];	//0x7c-0x8c
	SRE_O20_SR_MERGE_BLEND_00_T                       sr_merge_blend_00;	//0x0090
	SRE_O20_SR_MERGE_BLEND_01_T                       sr_merge_blend_01;	//0x0094
	SRE_O20_SR_MERGE_BLEND_02_T                       sr_merge_blend_02;	//0x0098
	SRE_O20_SR_MERGE_BLEND_03_T                       sr_merge_blend_03;	//0x009C
	SRE_O20_SR_MERGE_BLEND_04_T                       sr_merge_blend_04;	//0x00A0
	UINT32                                            reserved24[23];	//0xa4-0xfc
	SRE_O20_SR_MERGE_CORE_STAT_00_T                   sr_merge_core_stat_00;	//0x0100
	SRE_O20_SR_MERGE_CORE_STAT_01_T                   sr_merge_core_stat_01;	//0x0104
	SRE_O20_SR_MERGE_CORE_STAT_02_T                   sr_merge_core_stat_02;	//0x0108
	SRE_O20_SR_MERGE_CORE_STAT_03_T                   sr_merge_core_stat_03;	//0x010C
	SRE_O20_SR_MERGE_CORE_STAT_04_T                   sr_merge_core_stat_04;	//0x0110
	SRE_O20_SR_MERGE_CORE_STAT_05_T                   sr_merge_core_stat_05;	//0x0114
	UINT32                                            reserved30[54];	//0x118-0x1ec
	SRE_O20_SR_MERGE_FSW_CTRL_00_T                    sr_merge_fsw_ctrl_00;	//0x01F0
	SRE_O20_SR_MERGE_FSW_CTRL_01_T                    sr_merge_fsw_ctrl_01;	//0x01F4
	SRE_O20_SR_MERGE_FSW_CTRL_02_T                    sr_merge_fsw_ctrl_02;	//0x01F8
	SRE_O20_SR_MERGE_FSW_CTRL_03_T                    sr_merge_fsw_ctrl_03;	//0x01FC
}PE_SR_MERG_REG_O20_T;

#endif
