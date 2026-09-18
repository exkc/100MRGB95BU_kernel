#ifndef __OSD_SHP_REG_O20__
#define __OSD_SHP_REG_O20__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
/* OSD_SHP0 = 0xC901_1C00
   OSD_SHP1 = 0xc901_2300 */

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0000 shp_core_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 4,	//  0: 3 reserved
	reg_top_detour                  : 1,	//     4
	reg_top_bypass                  : 1,	//     5
	                                : 2,	//  6: 7 reserved
	reg_top_protocol_type           : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_top_mode_3d                 : 1,	//    12
	                                :11,	// 13:23 reserved
	reg_osd_size_sel                : 1;	//    24
} SHP_CORE_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0004 shp_core_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_width                   :16,	//  0:15
	reg_top_height                  :16;	// 16:31
} SHP_CORE_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0008 shp_core_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_use_extern_valid        : 1,	//     0
	reg_top_use_blank_preiod_cnt    : 1,	//     1
	                                :14,	//  2:15 reserved
	reg_top_manual_blank_cnt        :16;	// 16:31
} SHP_CORE_CTRL_02;

/*-----------------------------------------------------------------------------
	0x000c shp_core_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_prefetch_cnt            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_top_flush_cnt               :12;	// 16:27
} SHP_CORE_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0010 shp_core_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_update_ctrl             : 5;	//  0: 4
} SHP_CORE_CTRL_04;

/*-----------------------------------------------------------------------------
	0x00a0 shp_lti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lti_2d_en                   : 1,	//     0
	reg_lti_tap_size                : 2,	//  1: 2
	                                : 1,	//     3 reserved
	reg_lti_coring_en               : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_lti_2d_gain                 : 8,	//  8:15
	reg_lti_2d_limit                :10;	// 16:25
} SHP_LTI_CTRL_00;

typedef struct
{
	union
	{
		struct
		{
			SHP_CORE_CTRL_00                	shp_core_ctrl_00                ;	// 0x0000 : ''
			SHP_CORE_CTRL_01                	shp_core_ctrl_01                ;	// 0x0004 : ''
			SHP_CORE_CTRL_02                	shp_core_ctrl_02                ;	// 0x0008 : ''
			SHP_CORE_CTRL_03                	shp_core_ctrl_03                ;	// 0x000c : ''
			SHP_CORE_CTRL_04                	shp_core_ctrl_04                ;	// 0x0010 : ''
			UINT32                          	                 __rsvd_00[  35];	// 0x0014 ~ 0x009c

			/* OSD_SHP(0) only */
			SHP_LTI_CTRL_00                 	shp_lti_ctrl_00                 ;	// 0x00a0 : ''

			/* below data is not used at OSD.. so DO NOT reonvert registers */
		};

		UINT32	__skip[192];		/* total=768Byte */
	};
}
OSD_SHP_O20_REG_T;

#define SHP0_CTRL_RdFL(_r)	SHP_CTRL_RdFL(0,_r)
#define SHP0_CTRL_WrFL(_r)	SHP_CTRL_WrFL(0,_r)
#define SHP0_CTRL_Rd(_r) 	SHP_CTRL_Rd(0,_r)
#define SHP0_CTRL_Wr(_r,_v)	SHP_CTRL_Wr(0,_r,_v)

#define SHP0_CTRL_Rd01(_r,_f01,_v01) 			SHP_CTRL_Rd01(0,_r,_f01,_v01)
#define SHP0_CTRL_Rd02(_r,_f01,_v01,_f02,_v02) 	SHP_CTRL_Rd02(0,_r,_f01,_v01,_f02,_v02)
#define SHP0_CTRL_Wr01(_r,_f01,_v01) 			SHP_CTRL_Wr01(0,_r,_f01,_v01)
#define SHP0_CTRL_Wr02(_r,_f01,_v01,_f02,_v02) 	SHP_CTRL_Wr02(0,_r,_f01,_v01,_f02,_v02)


#define SHP_CTRL_RdFL(idx,_r)			((g_osd_shp_o20_reg_shadow[idx]->_r)=(g_osd_shp_o20_reg[idx]->_r))
#define SHP_CTRL_WrFL(idx,_r)			((g_osd_shp_o20_reg[idx]->_r)=(g_osd_shp_o20_reg_shadow[idx]->_r))

#define SHP_CTRL_Rd(idx,_r)				*((UINT32*)(&(g_osd_shp_o20_reg_shadow[idx]->_r)))
#define SHP_CTRL_Wr(idx,_r,_v)			((SHP_CTRL_Rd(idx,_r))=((UINT32)(_v)))

#define SHP_CTRL_Rd01(idx,_r,_f01,_v01)													\
								do { 											\
									(_v01) = (g_osd_shp_o20_reg_shadow[idx]->_r._f01);				\
								} while(0)

#define SHP_CTRL_Rd02(idx,_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (g_osd_shp_o20_reg_shadow[idx]->_r._f01);				\
									(_v02) = (g_osd_shp_o20_reg_shadow[idx]->_r._f02);				\
								} while(0)


#define SHP_CTRL_Wr01(idx,_r,_f01,_v01)													\
								do { 											\
									(g_osd_shp_o20_reg_shadow[idx]->_r._f01) = (_v01);				\
								} while(0)

#define SHP_CTRL_Wr02(idx,_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(g_osd_shp_o20_reg_shadow[idx]->_r._f01) = (_v01);				\
									(g_osd_shp_o20_reg_shadow[idx]->_r._f02) = (_v02);				\
								} while(0)

/** @} *//* end of macro documentation */

extern volatile OSD_SHP_O20_REG_T*	g_osd_shp_o20_reg[2];
extern OSD_SHP_O20_REG_T*  			g_osd_shp_o20_reg_shadow[2];

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'O20_PQE_OSD_SHP_reg_man.csv' 20170609 18:24:26 KST by getregs v2.9 */
