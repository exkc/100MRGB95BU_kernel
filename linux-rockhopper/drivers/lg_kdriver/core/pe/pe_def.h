/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_def.h
 *
 *  driver definition header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef _PE_DEF_H_
#define _PE_DEF_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#ifdef INCLUDE_M17_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_M17
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_O18
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_M19
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_O20
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_E60
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_O22
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_M23
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_O24
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_O26
#endif

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
/* kdrv version bit */
#define PE_KDRV_VER_BIT_NONE		0x00000000
#define PE_KDRV_VER_BIT_M17AX		0x00000001
#define PE_KDRV_VER_BIT_M17BX		0x00000002
#define PE_KDRV_VER_BIT_M17CX		0x00000004
#define PE_KDRV_VER_BIT_O18AX		0x00000008
#define PE_KDRV_VER_BIT_O18BX		0x00000010
#define PE_KDRV_VER_BIT_M19AX		0x00000020
#define PE_KDRV_VER_BIT_M19BX		0x00000040
#define PE_KDRV_VER_BIT_O20AX		0x00000080
#define PE_KDRV_VER_BIT_O20BX		0x00000100
#define PE_KDRV_VER_BIT_E60AX		0x00000200
#define PE_KDRV_VER_BIT_E60BX		0x00000400
#define PE_KDRV_VER_BIT_E60CX		0x00000800
#define PE_KDRV_VER_BIT_O22AX		0x00001000
#define PE_KDRV_VER_BIT_O22BX		0x00004000
#define PE_KDRV_VER_BIT_M23AX		0x00008000
#define PE_KDRV_VER_BIT_M23BX		0x00010000
#define PE_KDRV_VER_BIT_O24AX		0x00020000
#define PE_KDRV_VER_BIT_O24BX		0x00040000
#define PE_KDRV_VER_BIT_O26AX		0x00080000
#define PE_KDRV_VER_BIT_O26BX		0x00100000

#define PE_KDRV_VER_BIT_M17			(PE_KDRV_VER_BIT_M17AX|PE_KDRV_VER_BIT_M17BX|PE_KDRV_VER_BIT_M17CX)
#define PE_KDRV_VER_BIT_O18			(PE_KDRV_VER_BIT_O18AX|PE_KDRV_VER_BIT_O18BX)
#define PE_KDRV_VER_BIT_M19			(PE_KDRV_VER_BIT_M19AX|PE_KDRV_VER_BIT_M19BX)
#define PE_KDRV_VER_BIT_O20			(PE_KDRV_VER_BIT_O20AX|PE_KDRV_VER_BIT_O20BX)
#define PE_KDRV_VER_BIT_E60			(PE_KDRV_VER_BIT_E60AX|PE_KDRV_VER_BIT_E60BX|PE_KDRV_VER_BIT_E60CX)
#define PE_KDRV_VER_BIT_O22			(PE_KDRV_VER_BIT_O22AX|PE_KDRV_VER_BIT_O22BX)
#define PE_KDRV_VER_BIT_M23			(PE_KDRV_VER_BIT_M23AX|PE_KDRV_VER_BIT_M23BX)
#define PE_KDRV_VER_BIT_O24			(PE_KDRV_VER_BIT_O24AX|PE_KDRV_VER_BIT_O24BX)
#define PE_KDRV_VER_BIT_O26			(PE_KDRV_VER_BIT_O26AX|PE_KDRV_VER_BIT_O26BX)

/* define for use spd function */
#undef PE_KDRV_USE_SPD_FUNC

#define PE_PRINT_COUNT_NUM		512
#define PE_TRACE_STR_SIZE		128

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* kdrv version define */
#define PE_KDRV_VER_NONE		PE_KDRV_VER_BIT_NONE
#define PE_KDRV_VER_M17AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M17AX)
#define PE_KDRV_VER_M17BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M17BX)
#define PE_KDRV_VER_M17CX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M17CX)
#define PE_KDRV_VER_M17			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M17)
#define PE_KDRV_VER_O18AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O18AX)
#define PE_KDRV_VER_O18BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O18BX)
#define PE_KDRV_VER_O18			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O18)
#define PE_KDRV_VER_M19AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M19AX)
#define PE_KDRV_VER_M19BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M19BX)
#define PE_KDRV_VER_M19			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M19)
#define PE_KDRV_VER_O20AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O20AX)
#define PE_KDRV_VER_O20BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O20BX)
#define PE_KDRV_VER_O20			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O20)
#define PE_KDRV_VER_E60AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_E60AX)
#define PE_KDRV_VER_E60BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_E60BX)
#define PE_KDRV_VER_E60CX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_E60CX)
#define PE_KDRV_VER_E60			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_E60)
#define PE_KDRV_VER_O22AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O22AX)
#define PE_KDRV_VER_O22BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O22BX)
#define PE_KDRV_VER_O22			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O22)
#define PE_KDRV_VER_M23AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M23AX)
#define PE_KDRV_VER_M23BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M23BX)
#define PE_KDRV_VER_M23			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_M23)
#define PE_KDRV_VER_O24AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O24AX)
#define PE_KDRV_VER_O24BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O24BX)
#define PE_KDRV_VER_O24			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O24)
#define PE_KDRV_VER_O26AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O26AX)
#define PE_KDRV_VER_O26BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O26BX)
#define PE_KDRV_VER_O26			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_O26)

#define PE_CHIP_VER				lx_chip_rev( )

#define PE_KDRV_CHK_VER_BIT(_from,_to,_target)	\
	((lx_chip_rev()>=(_from) && lx_chip_rev()<(_to))? (_target):0x0)

#define PE_PRINT_ERROR(format, args...)		DBG_PRINT(g_pe_debug_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define PE_PRINT_WARN(format, args...)		DBG_PRINT(g_pe_debug_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define PE_PRINT_NOTI(format, args...)		DBG_PRINT(g_pe_debug_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define PE_PRINT_INFO(format, args...)		DBG_PRINT(g_pe_debug_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define PE_PRINT_DEBUG(format, args...)		DBG_PRINT(g_pe_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define PE_PRINT_TRACE(format, args...)		DBG_PRINT(g_pe_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)

#define PE_PRINT_VPQ_CMN(format, args...)	DBG_PRINT(g_pe_debug_fd, 6, format, ##args)
#define PE_PRINT_VPQ_PE(format, args...)	DBG_PRINT(g_pe_debug_fd, 7, format, ##args)
#define PE_PRINT_VPQ_BE(format, args...)	DBG_PRINT(g_pe_debug_fd, 8, format, ##args)
#define PE_PRINT_VPQ_HDR(format, args...)	DBG_PRINT(g_pe_debug_fd, 9, format, ##args)

/* debug message(pe) */
#define PE_PRINT_ETC(format, args...)		DBG_PRINT(g_pe_debug_fd, 10, format, ##args)
#define PE_PRINT_NRD(format, args...)		DBG_PRINT(g_pe_debug_fd, 11, format, ##args)
#define PE_PRINT_SHP(format, args...)		DBG_PRINT(g_pe_debug_fd, 12, format, ##args)
#define PE_PRINT_CMG(format, args...)		DBG_PRINT(g_pe_debug_fd, 13, format, ##args)
#define PE_PRINT_DCM(format, args...)		DBG_PRINT(g_pe_debug_fd, 14, format, ##args)
#define PE_PRINT_DCM_LUT(format, args...)	DBG_PRINT(g_pe_debug_fd, 15, format, ##args)
#define PE_PRINT_OBC_LUT(format, args...)	DBG_PRINT(g_pe_debug_fd, 16, format, ##args)
/* echo 1 17 1 > /proc/lg/pe/dbg_kdrv_func */
#define PE_PRINT_CMN(format, args...)		DBG_PRINT(g_pe_debug_fd, 17, format, ##args)
#define PE_PRINT_DTM(format, args...)		DBG_PRINT(g_pe_debug_fd, 18, format, ##args)
#define PE_PRINT_OBC(format, args...)		DBG_PRINT(g_pe_debug_fd, 19, format, ##args)
#define PE_PRINT_DSE(format, args...)		DBG_PRINT(g_pe_debug_fd, 20, format, ##args)
#define PE_PRINT_HST(format, args...)		DBG_PRINT(g_pe_debug_fd, 21, format, ##args)
#define PE_PRINT_CMG_GAIN(format, args...)	DBG_PRINT(g_pe_debug_fd, 22, format, ##args)
#define PE_PRINT_OBC_DATA(format, args...)	DBG_PRINT(g_pe_debug_fd, 23, format, ##args)

#define PE_PRINT_LATENCY(format, args...)	DBG_PRINT(g_pe_debug_fd, 24, format, ##args)
#define PE_PRINT_FWI(format, args...)		DBG_PRINT(g_pe_debug_fd, 25, format, ##args)

#define PE_PRINT_HDR_HST1(format, args...)	DBG_PRINT(g_pe_debug_fd, 28, format, ##args)
#define PE_PRINT_HDR_FIM(format, args...)	DBG_PRINT(g_pe_debug_fd, 29, format, ##args)
#define PE_PRINT_HDR_HIST(format, args...)	DBG_PRINT(g_pe_debug_fd, 30, format, ##args)
#define PE_PRINT_HDR_LUT(format, args...)	DBG_PRINT(g_pe_debug_fd, 31, format, ##args)

/* chip level dbg */
#define PE_DBG_ERROR(format, args...)		DBG_PRINT(g_pe_dbg_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define PE_DBG_WARN(format, args...)		DBG_PRINT(g_pe_dbg_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define PE_DBG_NOTI(format, args...)		DBG_PRINT(g_pe_dbg_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define PE_DBG_INFO(format, args...)		DBG_PRINT(g_pe_dbg_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define PE_DBG_DEBUG(format, args...)		DBG_PRINT(g_pe_dbg_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define PE_DBG_TRACE(format, args...)		DBG_PRINT(g_pe_dbg_fd, LX_LOGM_LEVEL_TRACE, format, ##args)

#define PE_DBG_CMG(format, args...)			DBG_PRINT(g_pe_dbg_fd, 6, format, ##args)
#define PE_DBG_CMN(format, args...)			DBG_PRINT(g_pe_dbg_fd, 7, format, ##args)
#define PE_DBG_CSC(format, args...)			DBG_PRINT(g_pe_dbg_fd, 8, format, ##args)
#define PE_DBG_DCM(format, args...)			DBG_PRINT(g_pe_dbg_fd, 9, format, ##args)
#define PE_DBG_DNT(format, args...)			DBG_PRINT(g_pe_dbg_fd, 10, format, ##args)
#define PE_DBG_FWI(format, args...)			DBG_PRINT(g_pe_dbg_fd, 11, format, ##args)
#define PE_DBG_HST(format, args...)			DBG_PRINT(g_pe_dbg_fd, 12, format, ##args)
#define PE_DBG_INF(format, args...)			DBG_PRINT(g_pe_dbg_fd, 13, format, ##args)
#define PE_DBG_NRD(format, args...)			DBG_PRINT(g_pe_dbg_fd, 14, format, ##args)
#define PE_DBG_SHP(format, args...)			DBG_PRINT(g_pe_dbg_fd, 15, format, ##args)
#define PE_DBG_TSK(format, args...)			DBG_PRINT(g_pe_dbg_fd, 16, format, ##args)
#define PE_DBG_WIN(format, args...)			DBG_PRINT(g_pe_dbg_fd, 17, format, ##args)
#define PE_DBG_DNR(format, args...)			DBG_PRINT(g_pe_dbg_fd, 18, format, ##args)
#define PE_DBG_DEC(format, args...)			DBG_PRINT(g_pe_dbg_fd, 19, format, ##args)
#define PE_DBG_SRE(format, args...)			DBG_PRINT(g_pe_dbg_fd, 20, format, ##args)
#define PE_DBG_DRC(format, args...)			DBG_PRINT(g_pe_dbg_fd, 21, format, ##args)
#define PE_DBG_OBC(format, args...)			DBG_PRINT(g_pe_dbg_fd, 22, format, ##args)
#define PE_DBG_OBC_LUT(format, args...)		DBG_PRINT(g_pe_dbg_fd, 23, format, ##args)
#define PE_DBG_HDR(format, args...)			DBG_PRINT(g_pe_dbg_fd, 30, format, ##args)

/* pq dbg print */
#define PQ_PRINT_ERROR(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define PQ_PRINT_WARN(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define PQ_PRINT_NOTI(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define PQ_PRINT_INFO(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define PQ_PRINT_DEBUG(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define PQ_PRINT_TRACE(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, LX_LOGM_LEVEL_TRACE, format, ##args)
#define PQ_PRINT_TNR(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, 6, format, ##args)
#define PQ_PRINT_DNR(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, 7, format, ##args)
#define PQ_PRINT_DEC(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, 8, format, ##args)
#define PQ_PRINT_SHP(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, 9, format, ##args)
#define PQ_PRINT_SRE(format, args...)		DBG_PRINT(g_pe_dbg_pq_fd, 10, format, ##args)
#define PQ_PRINT_SHP_LUT(format, args...)	DBG_PRINT(g_pe_dbg_pq_fd, 11, format, ##args)

#define PE_SWAP32(_x)	((((_x)>>24)&0xff)|(((_x)<<8)&0xff0000)|(((_x)>>8)&0xff00)|(((_x)<<24)&0xff000000))

#define GET_BM(value, mask) ((value) & (mask))
#define GET_CM(value, mask) (((value) & (mask)) == (mask))
#define GET_MASK(nd,wd)			    (((0xFFFFFFFF)>>(nd))&(0xFFFFFFFF>>(32-(wd))))
#define GET_BITS(val,nd,wd)			(((val)>>(nd))&(0xFFFFFFFF>>(32-(wd))))
#define GET_PVAL(val,nd,wd)			(GET_BITS(val,nd,wd)<<(nd))
#define GET_SVAL(val,nd,wd,sd)		(GET_BITS(val,nd,wd)<<(sd))
#define GET_SEXT(val,nd,wd)		    (((int)(GET_BITS(val,nd,wd)<<(32-(wd))))/(1<<(32-(wd))))
#define GET_PMSK(    nd,wd)			((((0xFFFFFFFF)>>(nd))&(0xFFFFFFFF>>(32-(wd)))) << (nd))
#define GET_RMSK(    nd,wd)			(~GET_PMSK(nd,wd))

#ifndef TO_STR
#define TO_STR(str) #str
#endif
#ifndef CHECK_NULL
#define CHECK_NULL(ptr)  if (!ptr) { ffprintf("%s is Null\n", #ptr); ret = RET_ERROR; break; }
#endif
#ifndef CHECK_KNULL
#define CHECK_KNULL(ptr) if (!ptr) { ffprintk("%s is Null\n", #ptr); ret = RET_ERROR; break; }
#endif
#ifndef BREAK_WRONG
#define BREAK_WRONG(val)           { ffprintk("Wrong %s(0x%x)\n", #val, val); ret = RET_ERROR; break; }
#endif
#define BREAK_SETV(_r, _v) 		   { _r = _v; break; }

#ifndef ffprintk
#define ffprintk(format, arg...)    printk("%s:%d:%s;" format , __FILE__ , __LINE__ , __FUNCTION__, ## arg)
#endif
#ifndef ffprintq
#define ffprintq(format, arg...)    printk("%s:%d:%s;" format , __FILE__ , __LINE__ , __FUNCTION__, ## arg)
#endif
#ifndef ffprintf
#define ffprintf(format, arg...)    printf("%s:%d:%s;" format , __FILE__ , __LINE__ , __FUNCTION__, ## arg)
#endif

#define REG_WD( addr, value )	    ( *( volatile UINT32 * )( addr )) = ( UINT32 )( value )
#define REG_RD( addr )	            ( *( volatile UINT32 * )( addr ))
#define DDR_WD( addr, value )	    ( *( UINT32 * )( addr ) ) = ( UINT32 )( value )
#define DDR_RD( addr )			    ( *( UINT32 * )( addr ) )

#define GET_RDIV(_x,_y)    			(((_x)+(_y)-1)/(_y))
#define GET_HDIV(_x,_y)    			(((_x)+(_y)/2)/(_y))
#define GET_RDUP(_x,_y)    			(GET_RDIV((_x),(_y))*(_y))

#define memset0(_var)		memset( &(_var), 0x00, sizeof(_var))
#define memset_0xff(_var)	memset( &(_var), 0xff, sizeof(_var))

#define PE_CONVHEX2DEC(hex,signbit)		\
	(((hex)&(1<<(signbit)))? ((hex)|(0xffffffff<<(signbit))):((hex)&(0xffffffff>>(31-(signbit)))))
#define PE_GET_MAX(x,y,z)			(((x)>=(y))? (((z)>=(x))? (z):(x)):(((z)>=(y))? (z):(y)))
#define PE_GET_MIN(x,y,z)			(((x)<=(y))? (((z)<=(x))? (z):(x)):(((z)<=(y))? (z):(y)))

#define PE_CHECK_WINID(_win_id)		\
	if ((_win_id)>LX_PE_WIN_NUM)	{ ffprintk("%s(%d) is wrong.\n",#_win_id,(_win_id)); ret = RET_ERROR; break; }
#define PE_CHECK_WIN0(_win_id)		(((_win_id)==LX_PE_WIN_0)||((_win_id)==LX_PE_WIN_ALL))
#define PE_CHECK_WIN1(_win_id)		(((_win_id)==LX_PE_WIN_1)||((_win_id)==LX_PE_WIN_ALL))
#define PE_CHECK_WIN2(_win_id)		(((_win_id)==LX_PE_WIN_2)||((_win_id)==LX_PE_WIN_ALL))
#define PE_CHECK_WIN3(_win_id)		(((_win_id)==LX_PE_WIN_3)||((_win_id)==LX_PE_WIN_ALL))
#define PE_GET_CHECKED_WINID(_win_id)	(((_win_id)==LX_PE_WIN_ALL)? LX_PE_WIN_0:(_win_id))

#define PE_CHECK_CODE(_checker, _action, fmt, args...)	\
	if (_checker){	PE_PRINT_ERROR(fmt, ##args);_action;	}

#define PE_CHECK_DUPLICATE(_paramtype)	\
	{\
		UINT32 chk_size=0, chk_wid=0, chk_i=0;\
		for (chk_i=0;chk_i<LX_PE_WIN_ALL;chk_i++)\
		{\
			prev[chk_i].win_id=pp->win_id;\
		}\
		chk_size = sizeof(_paramtype);\
		chk_wid = PE_CMN_CheckDoubleSetting(pp->win_id, \
			&chk, (void *)prev, (void *)pp, chk_size);\
		pp->win_id = (LX_PE_WIN_ID)chk_wid;\
	}


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
 *	pe cfg control type
 */
typedef struct
{
	UINT32 resume_mode;		///< resume mode, 0:normal, 1:resume
}
PE_CFG_CTRL_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern int	g_pe_debug_fd;
extern int	g_pe_dbg_fd;
extern int	g_pe_dbg_pq_fd;
extern unsigned int g_pe_kdrv_ver_mask;

#endif /* _PE_DEF_H_ */

