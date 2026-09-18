#ifndef _PE_SRE_REG_O18A0_H_
#define _PE_SRE_REG_O18A0_H_
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
}PE_O18_SHP_CHR_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009804L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_O18_SHP_CHR_CORE_CTRL_01_T;
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
}PE_O18_SHP_CHR_CORE_CTRL_02_T;
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
}PE_O18_SHP_CDJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c04L shp_cdj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_level_th                   :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_cdj_n_avg_gain                 :8 ;	// 23:16
}PE_O18_SHP_CDJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c08L shp_cdj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_g0_cnt_min                 :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_cdj_g0_mul                     :5 ;	// 12:8
}PE_O18_SHP_CDJ_CTRL_02_T;
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
}PE_O18_SHP_CDJ_CTRL_03_T;
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
}PE_O18_SHP_CDJ_CTRL_04_T;
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
}PE_O18_SHP_CDJ_CTRL_05_T;
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
}PE_O18_SHP_CDJ_CTRL_06_T;
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
}PE_O18_SHP_CDJ_CTRL_07_T;
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
}PE_O18_SHP_CDJ_CTRL_08_T;
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
}PE_O18_SHP_CDJ_CTRL_09_T;
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
}PE_O18_SHP_CDJ_CTRL_0A_T;
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
}PE_O18_SHP_CDJ_CTRL_0B_T;
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
}PE_O18_SHP_CDJ_CTRL_0C_T;
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
}PE_O18_SHP_CDJ_CTRL_0D_T;
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
}PE_O18_SHP_CDJ_CTRL_0E_T;
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
}PE_O18_SHP_CDJ_CTRL_0F_T;
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
}PE_O18_SHP_CDJ_CTRL_10_T;
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
}PE_O18_SHP_CDJ_CTRL_11_T;
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
}PE_O18_SHP_CDJ_CTRL_12_T;
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
}PE_O18_SHP_CDJ_CTRL_13_T;
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
}PE_O18_SHP_CDJ_CTRL_14_T;
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
}PE_O18_SHP_CDJ_CTRL_15_T;
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
}PE_O18_SHP_CDJ_CTRL_16_T;
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
}PE_O18_SHP_CDJ_CTRL_17_T;
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
}PE_O18_SHP_CDJ_CTRL_18_T;
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
}PE_O18_SHP_CDJ_CTRL_19_T;
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
}PE_O18_SHP_CDJ_CTRL_1A_T;
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
}PE_O18_SHP_CDJ_CTRL_1B_T;
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
}PE_O18_SHP_CDJ_CTRL_1C_T;
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
}PE_O18_SHP_CDJ_CTRL_1D_T;
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
}PE_O18_SHP_CDJ_CTRL_1E_T;
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
}PE_O18_SHP_CDJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9009c80L shp_cdj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_base                  :8 ,	// 7:0
	reg_cdj_soft_sel_1357_gain         :8 ,	// 15:8
	reg_cdj_soft_single_match_en       :1 ;	// 16:16
}PE_O18_SHP_CDJ_CTRL_20_T;
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
}PE_O18_SHP_CDIR_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c94L shp_cdir_blur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdir_blur_base                 :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_cdir_blur_gain                 :8 ;	// 23:16
}PE_O18_SHP_CDIR_BLUR_CTRL_01_T;
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
}PE_O18_SHP_CDJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca4L shp_cdj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w0_y0              :12;	// 27:16
}PE_O18_SHP_CDJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca8L shp_cdj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w0_y1              :12;	// 27:16
}PE_O18_SHP_CDJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009cacL shp_cdj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w1_y0              :12;	// 27:16
}PE_O18_SHP_CDJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009cb0L shp_cdj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w1_y1              :12;	// 27:16
}PE_O18_SHP_CDJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009e00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O18_SHP_CHR_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009e04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O18_SHP_CHR_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009e08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O18_SHP_CHR_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009e0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O18_SHP_CHR_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009e10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O18_SHP_CHR_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009e14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O18_SHP_CHR_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_CHR_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_CHR_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_CHR_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009efcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_CHR_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc9009000L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :6 ,	// reserved
	reg_top_mode_3d                    :1 ;	// 12:12
}PE_O18_SHP_2K_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009004L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_O18_SHP_2K_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009008L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O18_SHP_2K_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009100L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_O18_SHP_2K_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009110L shp_fd_ctrl_00                             
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
}PE_O18_SHP_2K_FD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009114L shp_fd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mul_base_t                  :8 ,	// 7:0
	reg_fd_mul_base_e                  :8 ;	// 15:8
}PE_O18_SHP_2K_FD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009118L shp_fd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900911cL shp_fd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009120L shp_fd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009124L shp_fd_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009128L shp_fd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900912cL shp_fd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009130L shp_fd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009134L shp_fd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_O18_SHP_2K_FD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009138L shp_fd_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_fd_mnr_s2_ratio_max            :8 ;	// 23:16
}PE_O18_SHP_2K_FD_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900913cL shp_fd_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_x0                 :8 ,	// 7:0
	reg_fd_mnr_gain_x1                 :8 ,	// 15:8
	reg_fd_mnr_gain_y0                 :8 ,	// 23:16
	reg_fd_mnr_gain_y1                 :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009140L shp_fd_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y0                :8 ,	// 7:0
	reg_fd_dct_t_lut_x0                :8 ,	// 15:8
	reg_fd_dct_t_lut_y1                :8 ,	// 23:16
	reg_fd_dct_t_lut_x1                :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009144L shp_fd_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y2                :8 ,	// 7:0
	reg_fd_dct_t_lut_x2                :8 ,	// 15:8
	reg_fd_dct_t_lut_y3                :8 ,	// 23:16
	reg_fd_dct_t_lut_x3                :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9009148L shp_fd_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y4                :8 ,	// 7:0
	reg_fd_dct_t_lut_x4                :8 ,	// 15:8
	reg_fd_dct_t_lut_y5                :8 ,	// 23:16
	reg_fd_dct_t_lut_x5                :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900914cL shp_fd_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_gain_e_en              :1 ,	// 0:0
	reg_fd_soft_gain_t_en              :1 ;	// 1:1
}PE_O18_SHP_2K_FD_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9009150L shp_fd_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_ratio                  :8 ,	// 7:0
	reg_fd_soft_offset                 :8 ;	// 15:8
}PE_O18_SHP_2K_FD_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9009154L shp_fd_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_x0               :8 ,	// 7:0
	reg_fd_soft_score_x1               :8 ,	// 15:8
	reg_fd_soft_score_x2               :8 ,	// 23:16
	reg_fd_soft_score_x3               :8 ;	// 31:24
}PE_O18_SHP_2K_FD_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9009158L shp_fd_ctrl_12                             
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
}PE_O18_SHP_2K_FD_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9009160L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ;	// 0:0
}PE_O18_SHP_2K_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009164L shp_mp_ctrl_01                             
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
}PE_O18_SHP_2K_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009168L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_lap_weight                  :8 ;	// 15:8
}PE_O18_SHP_2K_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900916cL shp_mp_ctrl_03                             
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
}PE_O18_SHP_2K_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009170L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ;	// 11:8
}PE_O18_SHP_2K_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009174L shp_mp_ctrl_05                             
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
}PE_O18_SHP_2K_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009178L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_O18_SHP_2K_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900917cL shp_mp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_O18_SHP_2K_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009180L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_O18_SHP_2K_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009184L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_O18_SHP_2K_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009188L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_O18_SHP_2K_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900918cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_en                   :1 ,	// 0:0
	reg_mp_coring_mode                 :2 ;	// 2:1
}PE_O18_SHP_2K_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009190L shp_mp_ctrl_0c                             
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
}PE_O18_SHP_2K_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009194L shp_apl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_apl_iir_en                     :1 ,	// 0:0
	reserved01                         :7 ,	// reserved
	reg_apl_iir_gain                   :8 ;	// 15:8
}PE_O18_SHP_2K_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90091a0L shp_lc_ctrl_00                             
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
}PE_O18_SHP_2K_LC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90091a4L shp_lc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_O18_SHP_2K_LC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90091a8L shp_lc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_O18_SHP_2K_LC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90091acL shp_lc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_coring_mode                 :2 ;	// 2:1
}PE_O18_SHP_2K_LC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90091b0L shp_lc_ctrl_04                             
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
}PE_O18_SHP_2K_LC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90091c0L shp_der_ctrl_00                             
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
}PE_O18_SHP_2K_DER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90091c4L shp_der_ctrl_01                             
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
}PE_O18_SHP_2K_DER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90091c8L shp_der_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ;	// 21:16
}PE_O18_SHP_2K_DER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90091ccL shp_der_ctrl_03                             
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
}PE_O18_SHP_2K_DER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90091d0L shp_der_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_O18_SHP_2K_DER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90091d4L shp_der_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_O18_SHP_2K_DER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90091d8L shp_der_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y0                   :8 ,	// 7:0
	reg_der_a_lut_x0                   :8 ,	// 15:8
	reg_der_a_lut_y1                   :8 ,	// 23:16
	reg_der_a_lut_x1                   :8 ;	// 31:24
}PE_O18_SHP_2K_DER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90091dcL shp_der_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y2                   :8 ,	// 7:0
	reg_der_a_lut_x2                   :8 ,	// 15:8
	reg_der_a_lut_y3                   :8 ,	// 23:16
	reg_der_a_lut_x3                   :8 ;	// 31:24
}PE_O18_SHP_2K_DER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90091e0L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ;	// 0:0
}PE_O18_SHP_2K_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90091e4L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ;	// 23:16
}PE_O18_SHP_2K_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90091e8L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_lap_weight                  :8 ;	// 15:8
}PE_O18_SHP_2K_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90091ecL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_O18_SHP_2K_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90091f0L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ;	// 11:8
}PE_O18_SHP_2K_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90091f4L shp_sp_ctrl_05                             
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
}PE_O18_SHP_2K_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90091f8L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_O18_SHP_2K_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90091fcL shp_sp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_O18_SHP_2K_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009200L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_O18_SHP_2K_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009204L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_O18_SHP_2K_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009208L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_O18_SHP_2K_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900920cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_en                   :1 ,	// 0:0
	reg_sp_coring_mode                 :2 ;	// 2:1
}PE_O18_SHP_2K_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009210L shp_sp_ctrl_0c                             
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
}PE_O18_SHP_2K_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009220L shp_pti_ctrl_00                             
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
}PE_O18_SHP_2K_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009224L shp_pti_ctrl_01                             
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
}PE_O18_SHP_2K_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009228L shp_pti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_en                  :1 ,	// 0:0
	reg_pti_coring_mode                :2 ;	// 2:1
}PE_O18_SHP_2K_PTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900922cL shp_pti_ctrl_03                             
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
}PE_O18_SHP_2K_PTI_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009230L shp_sti_ctrl_00                             
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
}PE_O18_SHP_2K_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009240L shp_tgen_ctrl_00                             
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
}PE_O18_SHP_2K_TGEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009244L shp_tgen_ctrl_01                             
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
}PE_O18_SHP_2K_TGEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009248L shp_tgen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rnd_th                    :8 ,	// 7:0
	reg_tgen_delta_wcurr               :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_tgen_lc_ldr_th                 :6 ;	// 21:16
}PE_O18_SHP_2K_TGEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900924cL shp_tgen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_x0;	// 31:0
}PE_O18_SHP_2K_TGEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009254L shp_tgen_ctrl_04                             
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
}PE_O18_SHP_2K_TGEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009258L shp_tgen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_tgen_gs_rnd                    :5 ,	// 20:16
	reserved02                         :3 ,	// reserved
	reg_tgen_gs_mm                     :5 ;	// 28:24
}PE_O18_SHP_2K_TGEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900925cL shp_tgen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_x2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_x1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_x0              :6 ;	// 29:24
}PE_O18_SHP_2K_TGEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9009260L shp_tgen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_y2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_y1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_y0              :6 ;	// 29:24
}PE_O18_SHP_2K_TGEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009264L shp_tgen_ctrl_08                             
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
}PE_O18_SHP_2K_TGEN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009268L shp_tgen_ctrl_09                             
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
}PE_O18_SHP_2K_TGEN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900926cL shp_tgen_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_en                 :1 ,	// 0:0
	reg_tgen_coring_mode               :2 ;	// 2:1
}PE_O18_SHP_2K_TGEN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9009270L shp_tgen_ctrl_0b                             
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
}PE_O18_SHP_2K_TGEN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009274L shp_snr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ;	// 15:8
}PE_O18_SHP_2K_SNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009280L shp_dctp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_en                        :1 ;	// 0:0
}PE_O18_SHP_2K_DCTP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009284L shp_dctp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_1              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009288L shp_dctp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_3              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900928cL shp_dctp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_5              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009290L shp_dctp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_7              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009294L shp_dctp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_1              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009298L shp_dctp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_3              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900929cL shp_dctp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_5              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90092a0L shp_dctp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_7              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90092a4L shp_dctp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_1              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90092a8L shp_dctp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_3              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90092acL shp_dctp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_5              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90092b0L shp_dctp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_7              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90092b4L shp_dctp_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_1              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90092b8L shp_dctp_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_3              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90092bcL shp_dctp_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_5              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90092c0L shp_dctp_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_7              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90092c4L shp_dctp_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_1              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90092c8L shp_dctp_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_3              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90092ccL shp_dctp_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_5              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90092d0L shp_dctp_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_7              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90092d4L shp_dctp_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_1              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90092d8L shp_dctp_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_3              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90092dcL shp_dctp_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_5              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90092e0L shp_dctp_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_7              :12;	// 27:16
}PE_O18_SHP_2K_DCTP_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90092e4L shp_dctp_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x0               :8 ,	// 7:0
	reg_dctp_text_lut_x1               :8 ,	// 15:8
	reg_dctp_text_lut_x2               :8 ,	// 23:16
	reg_dctp_text_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_2K_DCTP_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90092e8L shp_dctp_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x4               :8 ,	// 7:0
	reg_dctp_text_lut_x5               :8 ;	// 15:8
}PE_O18_SHP_2K_DCTP_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc90092ecL shp_dctp_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y0               :8 ,	// 7:0
	reg_dctp_edge_lut_x0               :8 ,	// 15:8
	reg_dctp_edge_lut_y1               :8 ,	// 23:16
	reg_dctp_edge_lut_x1               :8 ;	// 31:24
}PE_O18_SHP_2K_DCTP_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc90092f0L shp_dctp_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y2               :8 ,	// 7:0
	reg_dctp_edge_lut_x2               :8 ,	// 15:8
	reg_dctp_edge_lut_y3               :8 ,	// 23:16
	reg_dctp_edge_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_2K_DCTP_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc90092f4L shp_dctp_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_gain                      :8 ;	// 7:0
}PE_O18_SHP_2K_DCTP_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc90092f8L shp_dctp_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_en                 :1 ,	// 0:0
	reg_dctp_coring_mode               :2 ;	// 2:1
}PE_O18_SHP_2K_DCTP_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc90092fcL shp_dctp_ctrl_1f                             
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
}PE_O18_SHP_2K_DCTP_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9009300L shp_nntg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_en                        :1 ,	// 0:0
	reserved01                         :3 , // reserved
	reg_nntg_debug_mode                :2 ;	// 5:4
}PE_O18_SHP_2K_NNTG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009304L shp_nntg_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st;	// 31:0
}PE_O18_SHP_2K_NNTG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009308L shp_nntg_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd;	// 31:0
}PE_O18_SHP_2K_NNTG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900930cL shp_nntg_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd;	// 31:0
}PE_O18_SHP_2K_NNTG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009310L shp_nntg_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th;	// 31:0
}PE_O18_SHP_2K_NNTG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009314L shp_nntg_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th;	// 31:0
}PE_O18_SHP_2K_NNTG_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900932cL shp_nntg_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_ratio                :8 ,	// 7:0
	reg_nntg_rand_max                  :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_nntg_rand_sum_max              :8 ;	// 23:16
}PE_O18_SHP_2K_NNTG_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9009330L shp_nntg_ctrl_07                             
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
}PE_O18_SHP_2K_NNTG_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009334L shp_nntg_ctrl_08                             
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
}PE_O18_SHP_2K_NNTG_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009338L shp_nntg_ctrl_09                             
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
}PE_O18_SHP_2K_NNTG_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900933cL shp_nntg_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y0               :8 ,	// 7:0
	reg_nntg_diff_lut_x0               :8 ,	// 15:8
	reg_nntg_diff_lut_y1               :8 ,	// 23:16
	reg_nntg_diff_lut_x1               :8 ;	// 31:24
}PE_O18_SHP_2K_NNTG_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9009340L shp_nntg_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y2               :8 ,	// 7:0
	reg_nntg_diff_lut_x2               :8 ,	// 15:8
	reg_nntg_diff_lut_y3               :8 ,	// 23:16
	reg_nntg_diff_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_2K_NNTG_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009344L shp_nntg_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y0               :8 ,	// 7:0
	reg_nntg_edge_lut_x0               :8 ,	// 15:8
	reg_nntg_edge_lut_y1               :8 ,	// 23:16
	reg_nntg_edge_lut_x1               :8 ;	// 31:24
}PE_O18_SHP_2K_NNTG_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009348L shp_nntg_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y2               :8 ,	// 7:0
	reg_nntg_edge_lut_x2               :8 ,	// 15:8
	reg_nntg_edge_lut_y3               :8 ,	// 23:16
	reg_nntg_edge_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_2K_NNTG_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900934cL shp_nntg_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_random_gain               :8 ,	// 7:0
	reg_nntg_pattern_gain              :8 ,	// 15:8
	reg_nntg_local_gain                :8 ,	// 23:16
	reg_nntg_denoise_gain              :8 ;	// 31:24
}PE_O18_SHP_2K_NNTG_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9009350L shp_nntg_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_en                 :1 ,	// 0:0
	reg_nntg_coring_mode               :2 ;	// 2:1
}PE_O18_SHP_2K_NNTG_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9009354L shp_nntg_ctrl_10                             
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
}PE_O18_SHP_2K_NNTG_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9009360L shp_dp_sum_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ;	// 7:0
}PE_O18_SHP_2K_DP_SUM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90093a0L shp_dp_win_ctrl_00                             
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
}PE_O18_SHP_2K_DP_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90093a4L shp_dp_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0               :12;	// 27:16
}PE_O18_SHP_2K_DP_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90093a8L shp_dp_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1               :12;	// 27:16
}PE_O18_SHP_2K_DP_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90093acL shp_dp_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0               :12;	// 27:16
}PE_O18_SHP_2K_DP_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90093b0L shp_dp_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1               :12;	// 27:16
}PE_O18_SHP_2K_DP_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009400L shp_dj_ctrl_00                             
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
}PE_O18_SHP_2K_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009404L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_O18_SHP_2K_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009408L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_O18_SHP_2K_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900940cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_O18_SHP_2K_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009410L shp_dj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_dir_sel_c1                  :1 ,	// 0:0
	reg_dj_dir_sel_c2                  :1 ,	// 1:1
	reg_dj_dir_sel_c3                  :1 ,	// 2:2
	reg_dj_dir_sel_c4                  :1 ;	// 3:3
}PE_O18_SHP_2K_DJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009414L shp_dj_ctrl_05                             
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
}PE_O18_SHP_2K_DJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009418L shp_dj_ctrl_06                             
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
}PE_O18_SHP_2K_DJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900941cL shp_dj_ctrl_07                             
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
}PE_O18_SHP_2K_DJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009420L shp_dj_ctrl_08                             
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
}PE_O18_SHP_2K_DJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009424L shp_dj_ctrl_09                             
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
}PE_O18_SHP_2K_DJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009428L shp_dj_ctrl_0a                             
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
}PE_O18_SHP_2K_DJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900942cL shp_dj_ctrl_0b                             
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
}PE_O18_SHP_2K_DJ_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009430L shp_dj_ctrl_0c                             
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
}PE_O18_SHP_2K_DJ_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009434L shp_dj_ctrl_0d                             
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
}PE_O18_SHP_2K_DJ_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9009438L shp_dj_ctrl_0e                             
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
}PE_O18_SHP_2K_DJ_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900943cL shp_dj_ctrl_0f                             
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
}PE_O18_SHP_2K_DJ_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9009440L shp_dj_ctrl_10                             
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
}PE_O18_SHP_2K_DJ_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9009444L shp_dj_ctrl_11                             
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
}PE_O18_SHP_2K_DJ_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9009448L shp_dj_ctrl_12                             
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
}PE_O18_SHP_2K_DJ_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900944cL shp_dj_ctrl_13                             
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
}PE_O18_SHP_2K_DJ_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9009450L shp_dj_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_flip0_h            :1 ,	// 0:0
	reg_dj_pattern1_flip0_v            :1 ,	// 1:1
	reg_dj_pattern1_flip1_h            :1 ,	// 2:2
	reg_dj_pattern1_flip1_v            :1 ;	// 3:3
}PE_O18_SHP_2K_DJ_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9009454L shp_dj_ctrl_15                             
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
}PE_O18_SHP_2K_DJ_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9009458L shp_dj_ctrl_16                             
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
}PE_O18_SHP_2K_DJ_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900945cL shp_dj_ctrl_17                             
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
}PE_O18_SHP_2K_DJ_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9009460L shp_dj_ctrl_18                             
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
}PE_O18_SHP_2K_DJ_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9009464L shp_dj_ctrl_19                             
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
}PE_O18_SHP_2K_DJ_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9009468L shp_dj_ctrl_1a                             
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
}PE_O18_SHP_2K_DJ_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc900946cL shp_dj_ctrl_1b                             
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
}PE_O18_SHP_2K_DJ_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc9009470L shp_dj_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_flip0_h            :1 ,	// 0:0
	reg_dj_pattern2_flip0_v            :1 ,	// 1:1
	reg_dj_pattern2_flip1_h            :1 ,	// 2:2
	reg_dj_pattern2_flip1_v            :1 ;	// 3:3
}PE_O18_SHP_2K_DJ_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc9009474L shp_dj_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g0_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g0_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g0_max                 :8 ;	// 23:16
}PE_O18_SHP_2K_DJ_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc9009478L shp_dj_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g1_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g1_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g1_max                 :8 ;	// 23:16
}PE_O18_SHP_2K_DJ_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc900947cL shp_dj_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g2_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g2_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g2_max                 :8 ;	// 23:16
}PE_O18_SHP_2K_DJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9009480L shp_dj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_base                   :8 ,	// 7:0
	reg_dj_soft_sel_1357_gain          :8 ,	// 15:8
	reg_dj_soft_single_match_en        :1 ;	// 16:16
}PE_O18_SHP_2K_DJ_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9009490L shp_dir_blur_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_detour                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_dir_blur_buf_detour            :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_dir_blur_en                    :1 ;	// 8:8
}PE_O18_SHP_2K_DIR_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009494L shp_dir_blur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_base                  :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dir_blur_gain                  :8 ;	// 23:16
}PE_O18_SHP_2K_DIR_BLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90094a0L shp_dj_win_ctrl_00                             
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
}PE_O18_SHP_2K_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90094a4L shp_dj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_O18_SHP_2K_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90094a8L shp_dj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_O18_SHP_2K_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90094acL shp_dj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_O18_SHP_2K_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90094b0L shp_dj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_O18_SHP_2K_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009600L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O18_SHP_2K_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009604L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O18_SHP_2K_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009608L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O18_SHP_2K_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900960cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O18_SHP_2K_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009610L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O18_SHP_2K_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009614L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O18_SHP_2K_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009660L shp_core_fd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_CORE_FD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009664L shp_core_fd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_CORE_FD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009668L shp_core_fd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_CORE_FD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900966cL shp_core_fd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_CORE_FD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc90096f0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cvd_pattern_detect                 :1 ,	//reserved
	color_bar                          :1 ,	//reserved
	vfy_glb_en                         :1 ;	//VFILTER_CTRL_01, reg_glb_vflt_en
}PE_O18_SHP_2K_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90096f4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90096f8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90096fcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_2K_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc900a400L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :6 ,	// reserved
	reg_top_mode_3d                    :1 ;	// 12:12
}PE_O18_SHP_4K_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a404L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_O18_SHP_4K_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a408L shp_core0_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width_c0                   :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height_c0                  :12;	// 27:16
}PE_O18_SHP_4K_CORE0_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a40cL shp_core1_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width_c1                   :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height_c1                  :12;	// 27:16
}PE_O18_SHP_4K_CORE1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a410L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O18_SHP_4K_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a420L shp_split_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_split_l_max                    :13,	// 12:0
	reserved01                         :18,	// reserved
	reg_split_detour_en                :1 ;	// 31:31
}PE_O18_SHP_4K_SPLIT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a424L shp_split_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_split_r_max                    :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_split_r_min                    :13;	// 28:16
}PE_O18_SHP_4K_SPLIT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a428L shp_split_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_split_padding_st_pos           :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_split_padding_ed_pos           :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_split_padding_st_en            :1 ,	// 30:30
	reg_split_padding_ed_en            :1 ;	// 31:31
}PE_O18_SHP_4K_SPLIT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a430L shp_merg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_merg_line_end_pos              :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_merg_boundary_size             :8 ,	// 23:16
	reserved02                         :7 ,	// reserved
	reg_merg_detour_en                 :1 ;	// 31:31
}PE_O18_SHP_4K_MERG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a4a0L shp_esf_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_detour_mode                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_esf_en                         :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_esf_dbg_en                     :1 ;	// 8:8
}PE_O18_SHP_4K_ESF_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a4a4L shp_esf_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_min_ratio                  :8 ,	// 7:0
	reg_esf_base                       :8 ,	// 15:8
	reg_esf_max_clip                   :8 ,	// 23:16
	reg_esf_master_gain                :8 ;	// 31:24
}PE_O18_SHP_4K_ESF_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a4a8L shp_esf_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_ltv_offset                 :8 ,	// 7:0
	reg_esf_ltv_mul                    :8 ;	// 15:8
}PE_O18_SHP_4K_ESF_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a4b0L shp_core0_esf_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win0_en_c0             :1 ,	// 0:0
	reg_win_esf_win1_en_c0             :1 ,	// 1:1
	reg_win_esf_win01_en_c0            :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_esf_win_outside_c0         :1 ,	// 6:6
	reg_win_esf_win_en_c0              :1 ,	// 7:7
	reg_win_esf_bdr_alpha_c0           :5 ,	// 12:8
	reg_win_esf_bdr_wid_c0             :2 ,	// 14:13
	reg_win_esf_bdr_en_c0              :1 ,	// 15:15
	reg_win_esf_cr5_c0                 :5 ,	// 20:16
	reg_win_esf_cb5_c0                 :5 ,	// 25:21
	reg_win_esf_yy6_c0                 :6 ;	// 31:26
}PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a4b4L shp_core0_esf_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w0_x0_c0           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w0_y0_c0           :12;	// 27:16
}PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a4b8L shp_core0_esf_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w0_x1_c0           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w0_y1_c0           :12;	// 27:16
}PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a4bcL shp_core0_esf_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w1_x0_c0           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w1_y0_c0           :12;	// 27:16
}PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a4c0L shp_core0_esf_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w1_x1_c0           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w1_y1_c0           :12;	// 27:16
}PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a4d0L shp_core1_esf_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win0_en_c1             :1 ,	// 0:0
	reg_win_esf_win1_en_c1             :1 ,	// 1:1
	reg_win_esf_win01_en_c1            :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_esf_win_outside_c1         :1 ,	// 6:6
	reg_win_esf_win_en_c1              :1 ,	// 7:7
	reg_win_esf_bdr_alpha_c1           :5 ,	// 12:8
	reg_win_esf_bdr_wid_c1             :2 ,	// 14:13
	reg_win_esf_bdr_en_c1              :1 ,	// 15:15
	reg_win_esf_cr5_c1                 :5 ,	// 20:16
	reg_win_esf_cb5_c1                 :5 ,	// 25:21
	reg_win_esf_yy6_c1                 :6 ;	// 31:26
}PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a4d4L shp_core1_esf_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w0_x0_c1           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w0_y0_c1           :12;	// 27:16
}PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a4d8L shp_core1_esf_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w0_x1_c1           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w0_y1_c1           :12;	// 27:16
}PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a4dcL shp_core1_esf_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w1_x0_c1           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w1_y0_c1           :12;	// 27:16
}PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a4e0L shp_core1_esf_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w1_x1_c1           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w1_y1_c1           :12;	// 27:16
}PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a500L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_O18_SHP_4K_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a510L shp_fd_ctrl_00                             
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
}PE_O18_SHP_4K_FD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a514L shp_fd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mul_base_t                  :8 ,	// 7:0
	reg_fd_mul_base_e                  :8 ;	// 15:8
}PE_O18_SHP_4K_FD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a518L shp_fd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a51cL shp_fd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a520L shp_fd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a524L shp_fd_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a528L shp_fd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a52cL shp_fd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a530L shp_fd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900a534L shp_fd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_O18_SHP_4K_FD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900a538L shp_fd_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_fd_mnr_s2_ratio_max            :8 ;	// 23:16
}PE_O18_SHP_4K_FD_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900a53cL shp_fd_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_x0                 :8 ,	// 7:0
	reg_fd_mnr_gain_x1                 :8 ,	// 15:8
	reg_fd_mnr_gain_y0                 :8 ,	// 23:16
	reg_fd_mnr_gain_y1                 :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900a540L shp_fd_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y0                :8 ,	// 7:0
	reg_fd_dct_t_lut_x0                :8 ,	// 15:8
	reg_fd_dct_t_lut_y1                :8 ,	// 23:16
	reg_fd_dct_t_lut_x1                :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900a544L shp_fd_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y2                :8 ,	// 7:0
	reg_fd_dct_t_lut_x2                :8 ,	// 15:8
	reg_fd_dct_t_lut_y3                :8 ,	// 23:16
	reg_fd_dct_t_lut_x3                :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900a548L shp_fd_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y4                :8 ,	// 7:0
	reg_fd_dct_t_lut_x4                :8 ,	// 15:8
	reg_fd_dct_t_lut_y5                :8 ,	// 23:16
	reg_fd_dct_t_lut_x5                :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900a54cL shp_fd_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_gain_e_en              :1 ,	// 0:0
	reg_fd_soft_gain_t_en              :1 ;	// 1:1
}PE_O18_SHP_4K_FD_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900a550L shp_fd_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_ratio                  :8 ,	// 7:0
	reg_fd_soft_offset                 :8 ;	// 15:8
}PE_O18_SHP_4K_FD_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900a554L shp_fd_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_x0               :8 ,	// 7:0
	reg_fd_soft_score_x1               :8 ,	// 15:8
	reg_fd_soft_score_x2               :8 ,	// 23:16
	reg_fd_soft_score_x3               :8 ;	// 31:24
}PE_O18_SHP_4K_FD_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900a558L shp_fd_ctrl_12                             
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
}PE_O18_SHP_4K_FD_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900a560L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ;	// 0:0
}PE_O18_SHP_4K_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a564L shp_mp_ctrl_01                             
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
}PE_O18_SHP_4K_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a568L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_lap_weight                  :8 ;	// 15:8
}PE_O18_SHP_4K_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a56cL shp_mp_ctrl_03                             
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
}PE_O18_SHP_4K_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a570L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ;	// 11:8
}PE_O18_SHP_4K_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a574L shp_mp_ctrl_05                             
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
}PE_O18_SHP_4K_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a578L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_O18_SHP_4K_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a57cL shp_mp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_O18_SHP_4K_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a580L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_O18_SHP_4K_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900a584L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_O18_SHP_4K_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900a588L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_O18_SHP_4K_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900a58cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_en                   :1 ,	// 0:0
	reg_mp_coring_mode                 :2 ;	// 2:1
}PE_O18_SHP_4K_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900a590L shp_mp_ctrl_0c                             
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
}PE_O18_SHP_4K_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900a594L shp_apl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_apl_iir_en                     :1 ,	// 0:0
	reserved01                         :7 ,	// reserved
	reg_apl_iir_gain                   :8 ;	// 15:8
}PE_O18_SHP_4K_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a5a0L shp_lc_ctrl_00                             
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
}PE_O18_SHP_4K_LC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a5a4L shp_lc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_O18_SHP_4K_LC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a5a8L shp_lc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_O18_SHP_4K_LC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a5acL shp_lc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_coring_mode                 :2 ;	// 2:1
}PE_O18_SHP_4K_LC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a5b0L shp_lc_ctrl_04                             
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
}PE_O18_SHP_4K_LC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a5c0L shp_der_ctrl_00                             
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
}PE_O18_SHP_4K_DER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a5c4L shp_der_ctrl_01                             
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
}PE_O18_SHP_4K_DER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a5c8L shp_der_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ;	// 21:16
}PE_O18_SHP_4K_DER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a5ccL shp_der_ctrl_03                             
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
}PE_O18_SHP_4K_DER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a5d0L shp_der_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_O18_SHP_4K_DER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a5d4L shp_der_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_O18_SHP_4K_DER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a5d8L shp_der_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y0                   :8 ,	// 7:0
	reg_der_a_lut_x0                   :8 ,	// 15:8
	reg_der_a_lut_y1                   :8 ,	// 23:16
	reg_der_a_lut_x1                   :8 ;	// 31:24
}PE_O18_SHP_4K_DER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a5dcL shp_der_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y2                   :8 ,	// 7:0
	reg_der_a_lut_x2                   :8 ,	// 15:8
	reg_der_a_lut_y3                   :8 ,	// 23:16
	reg_der_a_lut_x3                   :8 ;	// 31:24
}PE_O18_SHP_4K_DER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a5e0L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ;	// 0:0
}PE_O18_SHP_4K_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a5e4L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ;	// 23:16
}PE_O18_SHP_4K_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a5e8L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_lap_weight                  :8 ;	// 15:8
}PE_O18_SHP_4K_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a5ecL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_O18_SHP_4K_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a5f0L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ;	// 11:8
}PE_O18_SHP_4K_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a5f4L shp_sp_ctrl_05                             
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
}PE_O18_SHP_4K_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a5f8L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_O18_SHP_4K_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a5fcL shp_sp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_O18_SHP_4K_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a600L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_O18_SHP_4K_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900a604L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_O18_SHP_4K_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900a608L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_O18_SHP_4K_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900a60cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_en                   :1 ,	// 0:0
	reg_sp_coring_mode                 :2 ;	// 2:1
}PE_O18_SHP_4K_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900a610L shp_sp_ctrl_0c                             
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
}PE_O18_SHP_4K_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900a620L shp_pti_ctrl_00                             
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
}PE_O18_SHP_4K_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a624L shp_pti_ctrl_01                             
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
}PE_O18_SHP_4K_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a628L shp_pti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_en                  :1 ,	// 0:0
	reg_pti_coring_mode                :2 ;	// 2:1
}PE_O18_SHP_4K_PTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a62cL shp_pti_ctrl_03                             
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
}PE_O18_SHP_4K_PTI_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a630L shp_sti_ctrl_00                             
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
}PE_O18_SHP_4K_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a640L shp_tgen_ctrl_00                             
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
}PE_O18_SHP_4K_TGEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a644L shp_tgen_ctrl_01                             
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
}PE_O18_SHP_4K_TGEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a648L shp_tgen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rnd_th                    :8 ,	// 7:0
	reg_tgen_delta_wcurr               :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_tgen_lc_ldr_th                 :6 ;	// 21:16
}PE_O18_SHP_4K_TGEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a64cL shp_core0_tgen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_init_val_c0;	// 31:0
}PE_O18_SHP_4K_CORE0_TGEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a650L shp_core1_tgen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_init_val_c1;	// 31:0
}PE_O18_SHP_4K_CORE1_TGEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a654L shp_tgen_ctrl_04                             
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
}PE_O18_SHP_4K_TGEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a658L shp_tgen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_tgen_gs_rnd                    :5 ,	// 20:16
	reserved02                         :3 ,	// reserved
	reg_tgen_gs_mm                     :5 ;	// 28:24
}PE_O18_SHP_4K_TGEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a65cL shp_tgen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_x2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_x1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_x0              :6 ;	// 29:24
}PE_O18_SHP_4K_TGEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a660L shp_tgen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_y2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_y1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_y0              :6 ;	// 29:24
}PE_O18_SHP_4K_TGEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a664L shp_tgen_ctrl_08                             
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
}PE_O18_SHP_4K_TGEN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900a668L shp_tgen_ctrl_09                             
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
}PE_O18_SHP_4K_TGEN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900a66cL shp_tgen_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_en                 :1 ,	// 0:0
	reg_tgen_coring_mode               :2 ;	// 2:1
}PE_O18_SHP_4K_TGEN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900a670L shp_tgen_ctrl_0b                             
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
}PE_O18_SHP_4K_TGEN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900a674L shp_snr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ;	// 15:8
}PE_O18_SHP_4K_SNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a680L shp_dctp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_en                        :1 ;	// 0:0
}PE_O18_SHP_4K_DCTP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a684L shp_dctp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_1              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a688L shp_dctp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_3              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a68cL shp_dctp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_5              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a690L shp_dctp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_7              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a694L shp_dctp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_1              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a698L shp_dctp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_3              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a69cL shp_dctp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_5              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a6a0L shp_dctp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_7              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900a6a4L shp_dctp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_1              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900a6a8L shp_dctp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_3              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900a6acL shp_dctp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_5              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900a6b0L shp_dctp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_7              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900a6b4L shp_dctp_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_1              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900a6b8L shp_dctp_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_3              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900a6bcL shp_dctp_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_5              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900a6c0L shp_dctp_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_7              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900a6c4L shp_dctp_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_1              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900a6c8L shp_dctp_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_3              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900a6ccL shp_dctp_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_5              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900a6d0L shp_dctp_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_7              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900a6d4L shp_dctp_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_1              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900a6d8L shp_dctp_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_3              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900a6dcL shp_dctp_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_5              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900a6e0L shp_dctp_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_7              :12;	// 27:16
}PE_O18_SHP_4K_DCTP_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900a6e4L shp_dctp_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x0               :8 ,	// 7:0
	reg_dctp_text_lut_x1               :8 ,	// 15:8
	reg_dctp_text_lut_x2               :8 ,	// 23:16
	reg_dctp_text_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_4K_DCTP_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc900a6e8L shp_dctp_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x4               :8 ,	// 7:0
	reg_dctp_text_lut_x5               :8 ;	// 15:8
}PE_O18_SHP_4K_DCTP_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc900a6ecL shp_dctp_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y0               :8 ,	// 7:0
	reg_dctp_edge_lut_x0               :8 ,	// 15:8
	reg_dctp_edge_lut_y1               :8 ,	// 23:16
	reg_dctp_edge_lut_x1               :8 ;	// 31:24
}PE_O18_SHP_4K_DCTP_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc900a6f0L shp_dctp_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y2               :8 ,	// 7:0
	reg_dctp_edge_lut_x2               :8 ,	// 15:8
	reg_dctp_edge_lut_y3               :8 ,	// 23:16
	reg_dctp_edge_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_4K_DCTP_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc900a6f4L shp_dctp_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_gain                      :8 ;	// 7:0
}PE_O18_SHP_4K_DCTP_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc900a6f8L shp_dctp_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_en                 :1 ,	// 0:0
	reg_dctp_coring_mode               :2 ;	// 2:1
}PE_O18_SHP_4K_DCTP_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc900a6fcL shp_dctp_ctrl_1f                             
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
}PE_O18_SHP_4K_DCTP_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc900a700L shp_nntg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_en                        :1 ,	// 0:0
	reserved01                         :3 , // reserved
	reg_nntg_debug_mode                :2 ;	// 5:4
}PE_O18_SHP_4K_NNTG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a704L shp_core0_nntg_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st_c0;	// 31:0
}PE_O18_SHP_4K_CORE0_NNTG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a708L shp_core0_nntg_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd_c0;	// 31:0
}PE_O18_SHP_4K_CORE0_NNTG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a70cL shp_core0_nntg_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd_c0;	// 31:0
}PE_O18_SHP_4K_CORE0_NNTG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a710L shp_core0_nntg_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th_c0;	// 31:0
}PE_O18_SHP_4K_CORE0_NNTG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a714L shp_core0_nntg_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th_c0;	// 31:0
}PE_O18_SHP_4K_CORE0_NNTG_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a718L shp_core1_nntg_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st_c1;	// 31:0
}PE_O18_SHP_4K_CORE1_NNTG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a71cL shp_core1_nntg_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd_c1;	// 31:0
}PE_O18_SHP_4K_CORE1_NNTG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a720L shp_core1_nntg_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd_c1;	// 31:0
}PE_O18_SHP_4K_CORE1_NNTG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a724L shp_core1_nntg_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th_c1;	// 31:0
}PE_O18_SHP_4K_CORE1_NNTG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a728L shp_core1_nntg_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th_c1;	// 31:0
}PE_O18_SHP_4K_CORE1_NNTG_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900a72cL shp_nntg_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_ratio                :8 ,	// 7:0
	reg_nntg_rand_max                  :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_nntg_rand_sum_max              :8 ;	// 23:16
}PE_O18_SHP_4K_NNTG_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900a730L shp_nntg_ctrl_07                             
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
}PE_O18_SHP_4K_NNTG_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900a734L shp_nntg_ctrl_08                             
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
}PE_O18_SHP_4K_NNTG_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900a738L shp_nntg_ctrl_09                             
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
}PE_O18_SHP_4K_NNTG_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900a73cL shp_nntg_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y0               :8 ,	// 7:0
	reg_nntg_diff_lut_x0               :8 ,	// 15:8
	reg_nntg_diff_lut_y1               :8 ,	// 23:16
	reg_nntg_diff_lut_x1               :8 ;	// 31:24
}PE_O18_SHP_4K_NNTG_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900a740L shp_nntg_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y2               :8 ,	// 7:0
	reg_nntg_diff_lut_x2               :8 ,	// 15:8
	reg_nntg_diff_lut_y3               :8 ,	// 23:16
	reg_nntg_diff_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_4K_NNTG_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900a744L shp_nntg_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y0               :8 ,	// 7:0
	reg_nntg_edge_lut_x0               :8 ,	// 15:8
	reg_nntg_edge_lut_y1               :8 ,	// 23:16
	reg_nntg_edge_lut_x1               :8 ;	// 31:24
}PE_O18_SHP_4K_NNTG_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900a748L shp_nntg_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y2               :8 ,	// 7:0
	reg_nntg_edge_lut_x2               :8 ,	// 15:8
	reg_nntg_edge_lut_y3               :8 ,	// 23:16
	reg_nntg_edge_lut_x3               :8 ;	// 31:24
}PE_O18_SHP_4K_NNTG_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900a74cL shp_nntg_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_random_gain               :8 ,	// 7:0
	reg_nntg_pattern_gain              :8 ,	// 15:8
	reg_nntg_local_gain                :8 ,	// 23:16
	reg_nntg_denoise_gain              :8 ;	// 31:24
}PE_O18_SHP_4K_NNTG_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900a750L shp_nntg_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_en                 :1 ,	// 0:0
	reg_nntg_coring_mode               :2 ;	// 2:1
}PE_O18_SHP_4K_NNTG_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900a754L shp_nntg_ctrl_10                             
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
}PE_O18_SHP_4K_NNTG_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900a760L shp_dp_sum_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ;	// 7:0
}PE_O18_SHP_4K_DP_SUM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a7a0L shp_core0_dp_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win0_en_c0              :1 ,	// 0:0
	reg_win_dp_win1_en_c0              :1 ,	// 1:1
	reg_win_dp_win01_en_c0             :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_win_outside_c0          :1 ,	// 6:6
	reg_win_dp_win_en_c0               :1 ,	// 7:7
	reg_win_dp_bdr_alpha_c0            :5 ,	// 12:8
	reg_win_dp_bdr_wid_c0              :2 ,	// 14:13
	reg_win_dp_bdr_en_c0               :1 ,	// 15:15
	reg_win_dp_cr5_c0                  :5 ,	// 20:16
	reg_win_dp_cb5_c0                  :5 ,	// 25:21
	reg_win_dp_yy6_c0                  :6 ;	// 31:26
}PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a7a4L shp_core0_dp_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0_c0            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0_c0            :12;	// 27:16
}PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a7a8L shp_core0_dp_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1_c0            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1_c0            :12;	// 27:16
}PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a7acL shp_core0_dp_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0_c0            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0_c0            :12;	// 27:16
}PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a7b0L shp_core0_dp_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1_c0            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1_c0            :12;	// 27:16
}PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900a7c0L shp_core1_dp_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win0_en_c1              :1 ,	// 0:0
	reg_win_dp_win1_en_c1              :1 ,	// 1:1
	reg_win_dp_win01_en_c1             :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_win_outside_c1          :1 ,	// 6:6
	reg_win_dp_win_en_c1               :1 ,	// 7:7
	reg_win_dp_bdr_alpha_c1            :5 ,	// 12:8
	reg_win_dp_bdr_wid_c1              :2 ,	// 14:13
	reg_win_dp_bdr_en_c1               :1 ,	// 15:15
	reg_win_dp_cr5_c1                  :5 ,	// 20:16
	reg_win_dp_cb5_c1                  :5 ,	// 25:21
	reg_win_dp_yy6_c1                  :6 ;	// 31:26
}PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900a7c4L shp_core1_dp_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0_c1            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0_c1            :12;	// 27:16
}PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900a7c8L shp_core1_dp_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1_c1            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1_c1            :12;	// 27:16
}PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900a7ccL shp_core1_dp_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0_c1            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0_c1            :12;	// 27:16
}PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900a7d0L shp_core1_dp_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1_c1            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1_c1            :12;	// 27:16
}PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900aa00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900aa04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O18_SHP_4K_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900aa08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O18_SHP_4K_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900aa0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O18_SHP_4K_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900aa10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O18_SHP_4K_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900aa14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O18_SHP_4K_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900aa20L shp_core0_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O18_SHP_4K_CORE0_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900aa24L shp_core0_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O18_SHP_4K_CORE0_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900aa28L shp_core0_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O18_SHP_4K_CORE0_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900aa2cL shp_core0_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O18_SHP_4K_CORE0_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900aa30L shp_core0_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O18_SHP_4K_CORE0_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900aa34L shp_core0_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O18_SHP_4K_CORE0_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900aa40L shp_core1_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O18_SHP_4K_CORE1_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900aa44L shp_core1_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O18_SHP_4K_CORE1_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900aa48L shp_core1_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O18_SHP_4K_CORE1_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900aa4cL shp_core1_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O18_SHP_4K_CORE1_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900aa50L shp_core1_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O18_SHP_4K_CORE1_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900aa54L shp_core1_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O18_SHP_4K_CORE1_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900aa60L shp_core0_fd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE0_FD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900aa64L shp_core0_fd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE0_FD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900aa68L shp_core0_fd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE0_FD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900aa6cL shp_core0_fd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE0_FD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900aa70L shp_core1_fd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE1_FD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900aa74L shp_core1_fd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE1_FD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900aa78L shp_core1_fd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE1_FD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900aa7cL shp_core1_fd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_CORE1_FD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900aaf0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900aaf4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900aaf8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900aafcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_4K_FSW_CTRL_03_T;


typedef struct
{ 
	PE_O18_SHP_CHR_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O18_SHP_CHR_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O18_SHP_CHR_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	UINT32                                            reserved3[253];	//0xc-0x3fc
	PE_O18_SHP_CDJ_CTRL_00_T                          shp_cdj_ctrl_00;	//0x0400
	PE_O18_SHP_CDJ_CTRL_01_T                          shp_cdj_ctrl_01;	//0x0404
	PE_O18_SHP_CDJ_CTRL_02_T                          shp_cdj_ctrl_02;	//0x0408
	PE_O18_SHP_CDJ_CTRL_03_T                          shp_cdj_ctrl_03;	//0x040C
	PE_O18_SHP_CDJ_CTRL_04_T                          shp_cdj_ctrl_04;	//0x0410
	PE_O18_SHP_CDJ_CTRL_05_T                          shp_cdj_ctrl_05;	//0x0414
	PE_O18_SHP_CDJ_CTRL_06_T                          shp_cdj_ctrl_06;	//0x0418
	PE_O18_SHP_CDJ_CTRL_07_T                          shp_cdj_ctrl_07;	//0x041C
	PE_O18_SHP_CDJ_CTRL_08_T                          shp_cdj_ctrl_08;	//0x0420
	PE_O18_SHP_CDJ_CTRL_09_T                          shp_cdj_ctrl_09;	//0x0424
	PE_O18_SHP_CDJ_CTRL_0A_T                          shp_cdj_ctrl_0a;	//0x0428
	PE_O18_SHP_CDJ_CTRL_0B_T                          shp_cdj_ctrl_0b;	//0x042C
	PE_O18_SHP_CDJ_CTRL_0C_T                          shp_cdj_ctrl_0c;	//0x0430
	PE_O18_SHP_CDJ_CTRL_0D_T                          shp_cdj_ctrl_0d;	//0x0434
	PE_O18_SHP_CDJ_CTRL_0E_T                          shp_cdj_ctrl_0e;	//0x0438
	PE_O18_SHP_CDJ_CTRL_0F_T                          shp_cdj_ctrl_0f;	//0x043C
	PE_O18_SHP_CDJ_CTRL_10_T                          shp_cdj_ctrl_10;	//0x0440
	PE_O18_SHP_CDJ_CTRL_11_T                          shp_cdj_ctrl_11;	//0x0444
	PE_O18_SHP_CDJ_CTRL_12_T                          shp_cdj_ctrl_12;	//0x0448
	PE_O18_SHP_CDJ_CTRL_13_T                          shp_cdj_ctrl_13;	//0x044C
	PE_O18_SHP_CDJ_CTRL_14_T                          shp_cdj_ctrl_14;	//0x0450
	PE_O18_SHP_CDJ_CTRL_15_T                          shp_cdj_ctrl_15;	//0x0454
	PE_O18_SHP_CDJ_CTRL_16_T                          shp_cdj_ctrl_16;	//0x0458
	PE_O18_SHP_CDJ_CTRL_17_T                          shp_cdj_ctrl_17;	//0x045C
	PE_O18_SHP_CDJ_CTRL_18_T                          shp_cdj_ctrl_18;	//0x0460
	PE_O18_SHP_CDJ_CTRL_19_T                          shp_cdj_ctrl_19;	//0x0464
	PE_O18_SHP_CDJ_CTRL_1A_T                          shp_cdj_ctrl_1a;	//0x0468
	PE_O18_SHP_CDJ_CTRL_1B_T                          shp_cdj_ctrl_1b;	//0x046C
	PE_O18_SHP_CDJ_CTRL_1C_T                          shp_cdj_ctrl_1c;	//0x0470
	PE_O18_SHP_CDJ_CTRL_1D_T                          shp_cdj_ctrl_1d;	//0x0474
	PE_O18_SHP_CDJ_CTRL_1E_T                          shp_cdj_ctrl_1e;	//0x0478
	PE_O18_SHP_CDJ_CTRL_1F_T                          shp_cdj_ctrl_1f;	//0x047C
	PE_O18_SHP_CDJ_CTRL_20_T                          shp_cdj_ctrl_20;	//0x0480
	UINT32                                            reserved36[3];	//0x484-0x48c
	PE_O18_SHP_CDIR_BLUR_CTRL_00_T                    shp_cdir_blur_ctrl_00;	//0x0490
	PE_O18_SHP_CDIR_BLUR_CTRL_01_T                    shp_cdir_blur_ctrl_01;	//0x0494
	UINT32                                            reserved38[2];	//0x498-0x49c
	PE_O18_SHP_CDJ_WIN_CTRL_00_T                      shp_cdj_win_ctrl_00;	//0x04A0
	PE_O18_SHP_CDJ_WIN_CTRL_01_T                      shp_cdj_win_ctrl_01;	//0x04A4
	PE_O18_SHP_CDJ_WIN_CTRL_02_T                      shp_cdj_win_ctrl_02;	//0x04A8
	PE_O18_SHP_CDJ_WIN_CTRL_03_T                      shp_cdj_win_ctrl_03;	//0x04AC
	PE_O18_SHP_CDJ_WIN_CTRL_04_T                      shp_cdj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved43[83];	//0x4b4-0x5fc
	PE_O18_SHP_CHR_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_O18_SHP_CHR_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_O18_SHP_CHR_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_O18_SHP_CHR_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_O18_SHP_CHR_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_O18_SHP_CHR_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved49[54];	//0x618-0x6ec
	PE_O18_SHP_CHR_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x06F0
	PE_O18_SHP_CHR_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x06F4
	PE_O18_SHP_CHR_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x06F8
	PE_O18_SHP_CHR_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x06FC
}PE_SR_CHR_SHP_REG_O18_T;

typedef struct
{ 
	PE_O18_SHP_2K_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O18_SHP_2K_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O18_SHP_2K_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	UINT32                                            reserved3[61];	//0xc-0xfc
	PE_O18_SHP_2K_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	UINT32                                            reserved4[3];	//0x104-0x10c
	PE_O18_SHP_2K_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O18_SHP_2K_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O18_SHP_2K_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O18_SHP_2K_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O18_SHP_2K_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O18_SHP_2K_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O18_SHP_2K_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O18_SHP_2K_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O18_SHP_2K_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O18_SHP_2K_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O18_SHP_2K_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O18_SHP_2K_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O18_SHP_2K_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O18_SHP_2K_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O18_SHP_2K_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O18_SHP_2K_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O18_SHP_2K_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O18_SHP_2K_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O18_SHP_2K_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	UINT32                                            reserved23;	//0x15c
	PE_O18_SHP_2K_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O18_SHP_2K_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O18_SHP_2K_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O18_SHP_2K_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O18_SHP_2K_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O18_SHP_2K_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O18_SHP_2K_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O18_SHP_2K_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O18_SHP_2K_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O18_SHP_2K_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O18_SHP_2K_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O18_SHP_2K_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O18_SHP_2K_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O18_SHP_2K_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	UINT32                                            reserved37[2];	//0x198-0x19c
	PE_O18_SHP_2K_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O18_SHP_2K_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O18_SHP_2K_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O18_SHP_2K_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O18_SHP_2K_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	UINT32                                            reserved42[3];	//0x1b4-0x1bc
	PE_O18_SHP_2K_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O18_SHP_2K_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O18_SHP_2K_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O18_SHP_2K_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O18_SHP_2K_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O18_SHP_2K_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O18_SHP_2K_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O18_SHP_2K_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O18_SHP_2K_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O18_SHP_2K_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O18_SHP_2K_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O18_SHP_2K_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O18_SHP_2K_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O18_SHP_2K_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O18_SHP_2K_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O18_SHP_2K_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O18_SHP_2K_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O18_SHP_2K_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O18_SHP_2K_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O18_SHP_2K_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O18_SHP_2K_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	UINT32                                            reserved63[3];	//0x214-0x21c
	PE_O18_SHP_2K_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O18_SHP_2K_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O18_SHP_2K_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O18_SHP_2K_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O18_SHP_2K_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	UINT32                                            reserved68[3];	//0x234-0x23c
	PE_O18_SHP_2K_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O18_SHP_2K_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O18_SHP_2K_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O18_SHP_2K_TGEN_CTRL_03_T                         shp_tgen_ctrl_03;	//0x024C
	UINT32                                            reserved72;	//0x250
	PE_O18_SHP_2K_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O18_SHP_2K_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O18_SHP_2K_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O18_SHP_2K_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O18_SHP_2K_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O18_SHP_2K_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O18_SHP_2K_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O18_SHP_2K_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O18_SHP_2K_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	UINT32                                            reserved81[2];	//0x278-0x27c
	PE_O18_SHP_2K_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O18_SHP_2K_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O18_SHP_2K_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O18_SHP_2K_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O18_SHP_2K_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O18_SHP_2K_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O18_SHP_2K_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O18_SHP_2K_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O18_SHP_2K_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O18_SHP_2K_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O18_SHP_2K_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O18_SHP_2K_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O18_SHP_2K_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O18_SHP_2K_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O18_SHP_2K_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O18_SHP_2K_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O18_SHP_2K_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O18_SHP_2K_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O18_SHP_2K_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O18_SHP_2K_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O18_SHP_2K_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O18_SHP_2K_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O18_SHP_2K_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O18_SHP_2K_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O18_SHP_2K_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O18_SHP_2K_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O18_SHP_2K_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O18_SHP_2K_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O18_SHP_2K_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O18_SHP_2K_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O18_SHP_2K_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O18_SHP_2K_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O18_SHP_2K_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O18_SHP_2K_NNTG_CTRL_01_T                         shp_nntg_ctrl_01;	//0x0304
	PE_O18_SHP_2K_NNTG_CTRL_02_T                         shp_nntg_ctrl_02;	//0x0308
	PE_O18_SHP_2K_NNTG_CTRL_03_T                         shp_nntg_ctrl_03;	//0x030C
	PE_O18_SHP_2K_NNTG_CTRL_04_T                         shp_nntg_ctrl_04;	//0x0310
	PE_O18_SHP_2K_NNTG_CTRL_05_T                         shp_nntg_ctrl_05;	//0x0314
	UINT32                                            reserved119[5];	//0x318-0x328
	PE_O18_SHP_2K_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O18_SHP_2K_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O18_SHP_2K_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O18_SHP_2K_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O18_SHP_2K_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O18_SHP_2K_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O18_SHP_2K_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O18_SHP_2K_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O18_SHP_2K_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O18_SHP_2K_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O18_SHP_2K_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	UINT32                                            reserved130[2];	//0x358-0x35c
	PE_O18_SHP_2K_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	UINT32                                            reserved131[15];	//0x364-0x39c
	PE_O18_SHP_2K_DP_WIN_CTRL_00_T                       shp_dp_win_ctrl_00;	//0x03A0
	PE_O18_SHP_2K_DP_WIN_CTRL_01_T                       shp_dp_win_ctrl_01;	//0x03A4
	PE_O18_SHP_2K_DP_WIN_CTRL_02_T                       shp_dp_win_ctrl_02;	//0x03A8
	PE_O18_SHP_2K_DP_WIN_CTRL_03_T                       shp_dp_win_ctrl_03;	//0x03AC
	PE_O18_SHP_2K_DP_WIN_CTRL_04_T                       shp_dp_win_ctrl_04;	//0x03B0
	UINT32                                            reserved136[19];	//0x3b4-0x3fc
	PE_O18_SHP_2K_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O18_SHP_2K_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O18_SHP_2K_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O18_SHP_2K_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O18_SHP_2K_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O18_SHP_2K_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O18_SHP_2K_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O18_SHP_2K_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O18_SHP_2K_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O18_SHP_2K_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O18_SHP_2K_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O18_SHP_2K_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O18_SHP_2K_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O18_SHP_2K_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O18_SHP_2K_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O18_SHP_2K_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O18_SHP_2K_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O18_SHP_2K_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O18_SHP_2K_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O18_SHP_2K_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O18_SHP_2K_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O18_SHP_2K_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O18_SHP_2K_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O18_SHP_2K_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O18_SHP_2K_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O18_SHP_2K_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O18_SHP_2K_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O18_SHP_2K_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O18_SHP_2K_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O18_SHP_2K_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O18_SHP_2K_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O18_SHP_2K_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O18_SHP_2K_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	UINT32                                            reserved169[3];	//0x484-0x48c
	PE_O18_SHP_2K_DIR_BLUR_CTRL_00_T                     shp_dir_blur_ctrl_00;	//0x0490
	PE_O18_SHP_2K_DIR_BLUR_CTRL_01_T                     shp_dir_blur_ctrl_01;	//0x0494
	UINT32                                            reserved171[2];	//0x498-0x49c
	PE_O18_SHP_2K_DJ_WIN_CTRL_00_T                       shp_dj_win_ctrl_00;	//0x04A0
	PE_O18_SHP_2K_DJ_WIN_CTRL_01_T                       shp_dj_win_ctrl_01;	//0x04A4
	PE_O18_SHP_2K_DJ_WIN_CTRL_02_T                       shp_dj_win_ctrl_02;	//0x04A8
	PE_O18_SHP_2K_DJ_WIN_CTRL_03_T                       shp_dj_win_ctrl_03;	//0x04AC
	PE_O18_SHP_2K_DJ_WIN_CTRL_04_T                       shp_dj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved176[83];	//0x4b4-0x5fc
	PE_O18_SHP_2K_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_O18_SHP_2K_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_O18_SHP_2K_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_O18_SHP_2K_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_O18_SHP_2K_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_O18_SHP_2K_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved182[18];	//0x618-0x65c
	PE_O18_SHP_2K_CORE_FD_STAT_00_T                      shp_core_fd_stat_00;	//0x0660
	PE_O18_SHP_2K_CORE_FD_STAT_01_T                      shp_core_fd_stat_01;	//0x0664
	PE_O18_SHP_2K_CORE_FD_STAT_02_T                      shp_core_fd_stat_02;	//0x0668
	PE_O18_SHP_2K_CORE_FD_STAT_03_T                      shp_core_fd_stat_03;	//0x066C
	UINT32                                            reserved186[32];	//0x670-0x6ec
	PE_O18_SHP_2K_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x06F0
	PE_O18_SHP_2K_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x06F4
	PE_O18_SHP_2K_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x06F8
	PE_O18_SHP_2K_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x06FC
}PE_SR_2K_SHP_REG_O18_T;


typedef struct
{ 
	PE_O18_SHP_4K_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O18_SHP_4K_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O18_SHP_4K_CORE0_CTRL_01_T                        shp_core0_ctrl_01;	//0x0008
	PE_O18_SHP_4K_CORE1_CTRL_01_T                        shp_core1_ctrl_01;	//0x000C
	PE_O18_SHP_4K_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0010
	UINT32                                            reserved5[3];	//0x14-0x1c
	PE_O18_SHP_4K_SPLIT_CTRL_00_T                        shp_split_ctrl_00;	//0x0020
	PE_O18_SHP_4K_SPLIT_CTRL_01_T                        shp_split_ctrl_01;	//0x0024
	PE_O18_SHP_4K_SPLIT_CTRL_02_T                        shp_split_ctrl_02;	//0x0028
	UINT32                                            reserved8;	//0x2c
	PE_O18_SHP_4K_MERG_CTRL_00_T                         shp_merg_ctrl_00;	//0x0030
	UINT32                                            reserved9[27];	//0x34-0x9c
	PE_O18_SHP_4K_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_O18_SHP_4K_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_O18_SHP_4K_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	UINT32                                            reserved12;	//0xac
	PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_00_T                shp_core0_esf_win_ctrl_00;	//0x00B0
	PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_01_T                shp_core0_esf_win_ctrl_01;	//0x00B4
	PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_02_T                shp_core0_esf_win_ctrl_02;	//0x00B8
	PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_03_T                shp_core0_esf_win_ctrl_03;	//0x00BC
	PE_O18_SHP_4K_CORE0_ESF_WIN_CTRL_04_T                shp_core0_esf_win_ctrl_04;	//0x00C0
	UINT32                                            reserved17[3];	//0xc4-0xcc
	PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_00_T                shp_core1_esf_win_ctrl_00;	//0x00D0
	PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_01_T                shp_core1_esf_win_ctrl_01;	//0x00D4
	PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_02_T                shp_core1_esf_win_ctrl_02;	//0x00D8
	PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_03_T                shp_core1_esf_win_ctrl_03;	//0x00DC
	PE_O18_SHP_4K_CORE1_ESF_WIN_CTRL_04_T                shp_core1_esf_win_ctrl_04;	//0x00E0
	UINT32                                            reserved22[7];	//0xe4-0xfc
	PE_O18_SHP_4K_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x0100
	UINT32                                            reserved23[3];	//0x104-0x10c
	PE_O18_SHP_4K_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0110
	PE_O18_SHP_4K_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0114
	PE_O18_SHP_4K_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0118
	PE_O18_SHP_4K_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x011C
	PE_O18_SHP_4K_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0120
	PE_O18_SHP_4K_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0124
	PE_O18_SHP_4K_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0128
	PE_O18_SHP_4K_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x012C
	PE_O18_SHP_4K_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0130
	PE_O18_SHP_4K_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0134
	PE_O18_SHP_4K_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0138
	PE_O18_SHP_4K_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x013C
	PE_O18_SHP_4K_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0140
	PE_O18_SHP_4K_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0144
	PE_O18_SHP_4K_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0148
	PE_O18_SHP_4K_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x014C
	PE_O18_SHP_4K_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0150
	PE_O18_SHP_4K_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0154
	PE_O18_SHP_4K_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0158
	UINT32                                            reserved42;	//0x15c
	PE_O18_SHP_4K_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O18_SHP_4K_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O18_SHP_4K_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O18_SHP_4K_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O18_SHP_4K_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O18_SHP_4K_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O18_SHP_4K_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O18_SHP_4K_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O18_SHP_4K_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O18_SHP_4K_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O18_SHP_4K_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O18_SHP_4K_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O18_SHP_4K_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O18_SHP_4K_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	UINT32                                            reserved56[2];	//0x198-0x19c
	PE_O18_SHP_4K_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O18_SHP_4K_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O18_SHP_4K_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O18_SHP_4K_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O18_SHP_4K_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	UINT32                                            reserved61[3];	//0x1b4-0x1bc
	PE_O18_SHP_4K_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O18_SHP_4K_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O18_SHP_4K_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O18_SHP_4K_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O18_SHP_4K_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O18_SHP_4K_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O18_SHP_4K_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O18_SHP_4K_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O18_SHP_4K_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O18_SHP_4K_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O18_SHP_4K_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O18_SHP_4K_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O18_SHP_4K_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O18_SHP_4K_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O18_SHP_4K_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O18_SHP_4K_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O18_SHP_4K_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O18_SHP_4K_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O18_SHP_4K_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O18_SHP_4K_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O18_SHP_4K_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	UINT32                                            reserved82[3];	//0x214-0x21c
	PE_O18_SHP_4K_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O18_SHP_4K_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O18_SHP_4K_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O18_SHP_4K_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O18_SHP_4K_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	UINT32                                            reserved87[3];	//0x234-0x23c
	PE_O18_SHP_4K_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O18_SHP_4K_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O18_SHP_4K_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O18_SHP_4K_CORE0_TGEN_CTRL_03_T                   shp_core0_tgen_ctrl_03;	//0x024C
	PE_O18_SHP_4K_CORE1_TGEN_CTRL_03_T                   shp_core1_tgen_ctrl_03;	//0x0250
	PE_O18_SHP_4K_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O18_SHP_4K_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O18_SHP_4K_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O18_SHP_4K_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O18_SHP_4K_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O18_SHP_4K_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O18_SHP_4K_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O18_SHP_4K_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O18_SHP_4K_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	UINT32                                            reserved101[2];	//0x278-0x27c
	PE_O18_SHP_4K_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O18_SHP_4K_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O18_SHP_4K_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O18_SHP_4K_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O18_SHP_4K_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O18_SHP_4K_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O18_SHP_4K_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O18_SHP_4K_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O18_SHP_4K_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O18_SHP_4K_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O18_SHP_4K_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O18_SHP_4K_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O18_SHP_4K_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O18_SHP_4K_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O18_SHP_4K_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O18_SHP_4K_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O18_SHP_4K_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O18_SHP_4K_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O18_SHP_4K_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O18_SHP_4K_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O18_SHP_4K_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O18_SHP_4K_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O18_SHP_4K_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O18_SHP_4K_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O18_SHP_4K_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O18_SHP_4K_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O18_SHP_4K_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O18_SHP_4K_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O18_SHP_4K_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O18_SHP_4K_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O18_SHP_4K_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O18_SHP_4K_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O18_SHP_4K_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O18_SHP_4K_CORE0_NNTG_CTRL_01_T                   shp_core0_nntg_ctrl_01;	//0x0304
	PE_O18_SHP_4K_CORE0_NNTG_CTRL_02_T                   shp_core0_nntg_ctrl_02;	//0x0308
	PE_O18_SHP_4K_CORE0_NNTG_CTRL_03_T                   shp_core0_nntg_ctrl_03;	//0x030C
	PE_O18_SHP_4K_CORE0_NNTG_CTRL_04_T                   shp_core0_nntg_ctrl_04;	//0x0310
	PE_O18_SHP_4K_CORE0_NNTG_CTRL_05_T                   shp_core0_nntg_ctrl_05;	//0x0314
	PE_O18_SHP_4K_CORE1_NNTG_CTRL_01_T                   shp_core1_nntg_ctrl_01;	//0x0318
	PE_O18_SHP_4K_CORE1_NNTG_CTRL_02_T                   shp_core1_nntg_ctrl_02;	//0x031C
	PE_O18_SHP_4K_CORE1_NNTG_CTRL_03_T                   shp_core1_nntg_ctrl_03;	//0x0320
	PE_O18_SHP_4K_CORE1_NNTG_CTRL_04_T                   shp_core1_nntg_ctrl_04;	//0x0324
	PE_O18_SHP_4K_CORE1_NNTG_CTRL_05_T                   shp_core1_nntg_ctrl_05;	//0x0328
	PE_O18_SHP_4K_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O18_SHP_4K_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O18_SHP_4K_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O18_SHP_4K_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O18_SHP_4K_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O18_SHP_4K_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O18_SHP_4K_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O18_SHP_4K_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O18_SHP_4K_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O18_SHP_4K_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O18_SHP_4K_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	UINT32                                            reserved155[2];	//0x358-0x35c
	PE_O18_SHP_4K_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	UINT32                                            reserved156[15];	//0x364-0x39c
	PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_00_T                 shp_core0_dp_win_ctrl_00;	//0x03A0
	PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_01_T                 shp_core0_dp_win_ctrl_01;	//0x03A4
	PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_02_T                 shp_core0_dp_win_ctrl_02;	//0x03A8
	PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_03_T                 shp_core0_dp_win_ctrl_03;	//0x03AC
	PE_O18_SHP_4K_CORE0_DP_WIN_CTRL_04_T                 shp_core0_dp_win_ctrl_04;	//0x03B0
	UINT32                                            reserved161[3];	//0x3b4-0x3bc
	PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_00_T                 shp_core1_dp_win_ctrl_00;	//0x03C0
	PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_01_T                 shp_core1_dp_win_ctrl_01;	//0x03C4
	PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_02_T                 shp_core1_dp_win_ctrl_02;	//0x03C8
	PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_03_T                 shp_core1_dp_win_ctrl_03;	//0x03CC
	PE_O18_SHP_4K_CORE1_DP_WIN_CTRL_04_T                 shp_core1_dp_win_ctrl_04;	//0x03D0
	UINT32                                            reserved166[139];	//0x3d4-0x5fc
	PE_O18_SHP_4K_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_O18_SHP_4K_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_O18_SHP_4K_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_O18_SHP_4K_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_O18_SHP_4K_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_O18_SHP_4K_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved172[2];	//0x618-0x61c
	PE_O18_SHP_4K_CORE0_STAT_00_T                        shp_core0_stat_00;	//0x0620
	PE_O18_SHP_4K_CORE0_STAT_01_T                        shp_core0_stat_01;	//0x0624
	PE_O18_SHP_4K_CORE0_STAT_02_T                        shp_core0_stat_02;	//0x0628
	PE_O18_SHP_4K_CORE0_STAT_03_T                        shp_core0_stat_03;	//0x062C
	PE_O18_SHP_4K_CORE0_STAT_04_T                        shp_core0_stat_04;	//0x0630
	PE_O18_SHP_4K_CORE0_STAT_05_T                        shp_core0_stat_05;	//0x0634
	UINT32                                            reserved178[2];	//0x638-0x63c
	PE_O18_SHP_4K_CORE1_STAT_00_T                        shp_core1_stat_00;	//0x0640
	PE_O18_SHP_4K_CORE1_STAT_01_T                        shp_core1_stat_01;	//0x0644
	PE_O18_SHP_4K_CORE1_STAT_02_T                        shp_core1_stat_02;	//0x0648
	PE_O18_SHP_4K_CORE1_STAT_03_T                        shp_core1_stat_03;	//0x064C
	PE_O18_SHP_4K_CORE1_STAT_04_T                        shp_core1_stat_04;	//0x0650
	PE_O18_SHP_4K_CORE1_STAT_05_T                        shp_core1_stat_05;	//0x0654
	UINT32                                            reserved184[2];	//0x658-0x65c
	PE_O18_SHP_4K_CORE0_FD_STAT_00_T                     shp_core0_fd_stat_00;	//0x0660
	PE_O18_SHP_4K_CORE0_FD_STAT_01_T                     shp_core0_fd_stat_01;	//0x0664
	PE_O18_SHP_4K_CORE0_FD_STAT_02_T                     shp_core0_fd_stat_02;	//0x0668
	PE_O18_SHP_4K_CORE0_FD_STAT_03_T                     shp_core0_fd_stat_03;	//0x066C
	PE_O18_SHP_4K_CORE1_FD_STAT_00_T                     shp_core1_fd_stat_00;	//0x0670
	PE_O18_SHP_4K_CORE1_FD_STAT_01_T                     shp_core1_fd_stat_01;	//0x0674
	PE_O18_SHP_4K_CORE1_FD_STAT_02_T                     shp_core1_fd_stat_02;	//0x0678
	PE_O18_SHP_4K_CORE1_FD_STAT_03_T                     shp_core1_fd_stat_03;	//0x067C
	UINT32                                            reserved192[28];	//0x680-0x6ec
	PE_O18_SHP_4K_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x06F0
	PE_O18_SHP_4K_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x06F4
	PE_O18_SHP_4K_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x06F8
	PE_O18_SHP_4K_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x06FC
}PE_SR_4K_SHP_REG_O18_T;
#endif
