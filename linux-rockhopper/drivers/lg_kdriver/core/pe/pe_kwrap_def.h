/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file pe_kwrap_def.h
 *
 *  application interface header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

#ifndef	_PE_KWRAP_DEF_H_
#define	_PE_KWRAP_DEF_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

typedef struct
{
	int 					dev_fd;
//	typedef void*	LX_OSA_OBJECT_T;
	void					*dev_mtx;	/* mutex(semaphore) for PE */
	int						ref_cnt;	/* refrence count */
}
LX_PE_CXT_T;


/**
 *	pe kwrap default param type enumeration
 */
typedef enum
{
	PE_KWRAP_DFLT_PARAM_TNR_CMN,		///< tnr common
	PE_KWRAP_DFLT_PARAM_TNR_DTL,		///< tnr detail
	PE_KWRAP_DFLT_PARAM_DNR_CMN,		///< dnr common
	PE_KWRAP_DFLT_PARAM_DNR_DTL,		///< dnr detail
	PE_KWRAP_DFLT_PARAM_REN_CMN,		///< ren common
	PE_KWRAP_DFLT_PARAM_REN_HOR,		///< ren hor
	PE_KWRAP_DFLT_PARAM_REN_VER,		///< ren hor
	PE_KWRAP_DFLT_PARAM_REN_MIS,		///< ren misc
	PE_KWRAP_DFLT_PARAM_REN_EDG,		///< ren edge
	PE_KWRAP_DFLT_PARAM_REN_DTL,		///< ren detail
	PE_KWRAP_DFLT_PARAM_SRS_CMN,		///< sre ren common
	PE_KWRAP_DFLT_PARAM_SRS_HOR,		///< sre ren hor
	PE_KWRAP_DFLT_PARAM_SRS_VER,		///< sre ren hor
	PE_KWRAP_DFLT_PARAM_SRS_MIS,		///< sre ren misc
	PE_KWRAP_DFLT_PARAM_SRS_EDG,		///< sre ren edge
	PE_KWRAP_DFLT_PARAM_SRS_DTL,		///< sre ren detail
	PE_KWRAP_DFLT_PARAM_CSC_GMT,		///< csc gamutcsc
	PE_KWRAP_DFLT_PARAM_2KS_CMN,		///< sre ren common
	PE_KWRAP_DFLT_PARAM_2KS_HOR,		///< sre ren hor
	PE_KWRAP_DFLT_PARAM_2KS_VER,		///< sre ren hor
	PE_KWRAP_DFLT_PARAM_2KS_MIS,		///< sre ren misc
	PE_KWRAP_DFLT_PARAM_2KS_EDG,		///< sre ren edge
	PE_KWRAP_DFLT_PARAM_2KS_DTL,		///< sre ren detail
	PE_KWRAP_DFLT_PARAM_NUM			///< max num
}
PE_KWRAP_DFLT_PARAM_TYPE;

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
extern LX_PE_CXT_T	_g_pe_ctx;
extern int _g_pe_kwrap_dbg_fd;

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_KWRAP_LOGM_ERRO			(LX_LOGM_LEVEL_ERROR)
#define PE_KWRAP_LOGM_WARN			(LX_LOGM_LEVEL_WARNING)
#define PE_KWRAP_LOGM_NOTI			(LX_LOGM_LEVEL_NOTI)
#define PE_KWRAP_LOGM_INFO			(LX_LOGM_LEVEL_INFO)
#define PE_KWRAP_LOGM_DBUG			(LX_LOGM_LEVEL_DEBUG)
#define PE_KWRAP_LOGM_TRAC			(LX_LOGM_LEVEL_TRACE)
#define PE_KWRAP_LOGM_TASK			(LX_LOGM_LEVEL_TRACE+1)
#define PE_KWRAP_LOGM_PRIME9			(22)
#define PE_KWRAP_LOGM_PRIME8			(23)
#define PE_KWRAP_LOGM_PRIME7			(24)
#define PE_KWRAP_LOGM_PRIME6			(25)
#define PE_KWRAP_LOGM_PRIME5			(26)
#define PE_KWRAP_LOGM_PRIME4			(27)
#define PE_KWRAP_LOGM_PRIME3			(28)
#define PE_KWRAP_LOGM_PRIME2			(29)
#define PE_KWRAP_LOGM_PRIME1			(30)
#define PE_KWRAP_LOGM_PRIME0			(31)
#define PE_KWRAP_LOGM_MAX			(PE_KWRAP_LOGM_PRIME0)

#if 1
/* debug message */
#define PE_ERROR(format, args...)	\
	(void)0
#define PE_WARN(format, args...)	\
	(void)0
#define PE_NOTI(format, args...)	\
	(void)0
#define PE_INFO(format, args...)	\
	(void)0
#define PE_DEBUG(format, args...)	\
	(void)0
#define PE_TRACE(format, args...)	\
	(void)0
#define PE_TASK(format, args...)	\
	(void)0

/* debug message(prime) */
#define PE_PRIME0(format, args...)	\
	(void)0
#define PE_PRIME1(format, args...)	\
	(void)0
#define PE_PRIME2(format, args...)	\
	(void)0
#define PE_PRIME3(format, args...)	\
	(void)0
#define PE_PRIME4(format, args...)	\
	(void)0
#define PE_PRIME5(format, args...)	\
	(void)0
#define PE_PRIME6(format, args...)	\
	(void)0
#define PE_PRIME7(format, args...)	\
	(void)0
#define PE_PRIME8(format, args...)	\
	(void)0
#define PE_PRIME9(format, args...)	\
	(void)0

#define PE_TRACE_BEGIN()	(void)0
#define PE_TRACE_END()		(void)0
#define PE_TRACE_MARK()		(void)0
#define PE_TASK_BEGIN()		(void)0
#define PE_TASK_END()		(void)0
#else
/* debug message */
#define PE_ERROR(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_ERRO, format, ##args)
#define PE_WARN(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_WARN, format, ##args)
#define PE_NOTI(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_NOTI, format, ##args)
#define PE_INFO(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_INFO, format, ##args)
#define PE_DEBUG(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_DBUG, format, ##args)
#define PE_TRACE(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_TRAC, format, ##args)
#define PE_TASK(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_TASK, format, ##args)

/* debug message(prime) */
#define PE_PRIME0(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME0, format, ##args)
#define PE_PRIME1(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME1, format, ##args)
#define PE_PRIME2(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME2, format, ##args)
#define PE_PRIME3(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME3, format, ##args)
#define PE_PRIME4(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME4, format, ##args)
#define PE_PRIME5(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME5, format, ##args)
#define PE_PRIME6(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME6, format, ##args)
#define PE_PRIME7(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME7, format, ##args)
#define PE_PRIME8(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME8, format, ##args)
#define PE_PRIME9(format, args...)	\
	KWRAP_LOGM_PRINT(_g_pe_kwrap_dbg_fd, PE_KWRAP_LOGM_PRIME9, format, ##args)

#define PE_TRACE_BEGIN()	PE_TRACE("BEGIN\n")
#define PE_TRACE_END()		PE_TRACE("END\n")
#define PE_TRACE_MARK()		PE_TRACE("TRACE !!!\n")
#define PE_TASK_BEGIN()		PE_TASK("BEGIN\n")
#define PE_TASK_END()		PE_TASK("END\n")
#endif

#undef PE_CHECK_CODE
#define PE_CHECK_CODE(__checker, __if_action, fmt, args...)		\
	if (__checker)\
	{\
		PE_PRINT_ERROR(fmt, ##args);\
		__if_action;\
	}

#define PE_CHECK_ACTION(__checker, __if_action)		\
	if (__checker)\
	{\
		__if_action;\
	}

#define PE_GET_BITS(val, nd, wd)	(((val)>>(nd))&(0xFFFFFFFF>>(32-(wd))))
#define PE_SET_BITS(val, nd, wd, set)	\
	val = (( (val) & ~(PE_DATA_MASK((0xFFFFFFFF>>(32-(wd))), nd))) \
			| (PE_LSHIFT_DATA(set, (0xFFFFFFFF>>(32-(wd))), nd)))

#if 1
#define PE_INIT_LOCK()	\
	(void)0
#define PE_LOCK()		\
	(void)0
#define PE_UNLOCK()		\
	(void)0
#define PE_CHECK_KWRAP_FUNC_ON(_modl)	\
	(void)0
#define PE_CHECK_OPENED()	\
	(void)0
#undef CHECK_KNULL
#define CHECK_KNULL(_ret, _param)	\
		PE_CHECK_CODE(!(_param), (_ret)=RET_ERROR;break, \
		"[%s,%d]%s is null.\n", __F__, __L__, #_param)
#define PE_KWRAP_DBG_PRINT(mod, fmt, args...)	\
	if (_g_kwrap_trace) {	\
	KWRAP_PE_DebugPrint(PE_KWRAP_DBG_TYPE_##mod, \
	"[%s,%d][%s]"fmt, __F__, __L__, #mod, ##args); }
#define PE_KWRAP_IOCTL(_st, _p, _rw, _modl)	\
	RET_OK
#else
#define PE_INIT_LOCK()	\
	if (!_g_pe_ctx.dev_mtx)\
	{\
		_g_pe_ctx.dev_mtx = \
			KWRAP_OSA_OpenSema("kwrap-pe-mtx", LX_OSA_GLOBAL_SEMA, 1);\
		PE_NOTI("pe(%s) sema(%d) open.\n", \
			PE_MODULE_NAME, _g_pe_ctx.dev_mtx);\
	}\
	else\
	{\
		PE_NOTI("pe(%s) sema(%d) already opened.\n", \
			PE_MODULE_NAME, _g_pe_ctx.dev_mtx);\
	}
#define PE_LOCK()		\
	(void)KWRAP_OSA_LockSema( _g_pe_ctx.dev_mtx, LX_OSA_INF_WAIT)
#define PE_UNLOCK()		\
	(void)KWRAP_OSA_UnlockSema( _g_pe_ctx.dev_mtx)

/* pe check kwrap function on, to debug each module */
#define PE_CHECK_KWRAP_FUNC_ON(_modl)	\
	PE_CHECK_CODE(!(KWRAP_PE_DBG_GetDebugFunc(PE_KWRAP_DBG_TYPE_##_modl)), \
		return RET_OK, "[%s,%d]func call off.[%s]\n", __F__, __L__, #_modl)

/* pe check opened, to use before pe lock  */
#define PE_CHECK_OPENED()	\
	PE_CHECK_CODE(KWRAP_PE_IsOpened(), \
	return RET_ERROR, "[%s,%d]pe : not opened.\n", __F__, __L__)

/* pe check null input  */
#define CHECK_KNULL(_ret, _param)	\
		PE_CHECK_CODE(!(_param), (_ret)=RET_ERROR;break, \
		"[%s,%d]%s is null.\n", __F__, __L__, #_param)

/* kwrap pe print, see PE_KWRAP_DBG_TYPE_T */
#define PE_KWRAP_DBG_PRINT(mod, fmt, args...)	\
	KWRAP_PE_DebugPrint(PE_KWRAP_DBG_TYPE_##mod, \
	"[%s,%d][%s]"fmt, __F__, __L__, #mod, ##args)

/* kwrap ioctl */
#define PE_KWRAP_IOCTL(_st, _p, _rw, _modl)	\
	_KWRAP_PE_Ioctl(_p, PE_ITEM_PKTRW(_rw), \
	PE_ITEM_PKTMODL(_modl), PE_ITEM_PKTFUNC(_st), sizeof(_st))
#endif

/* kwrap version */
#define PE_KWRAP_CONFIG_VER_MASK()	_KWRAP_PE_ConfigVersionMask()
#define PE_KWRAP_CLEAR_VER_MASK()	_KWRAP_PE_ClearVersionMask()

#define PE_KWRAP_CHK_VER_BIT(_from, _to, _target)	\
	((lx_chip_rev()>=(_from) && lx_chip_rev()<(_to))? (_target):0x0)

#define PE_KWRAP_SHOW_CHK(_type, _id, _chk)		\
	PE_KWRAP_DBG_PRINT(_type, "val_wid:0x%x, check:%d,%d,%d, 0x%x\n", _id, \
		PE_GET_BITS(_chk, 24, 8), \
		PE_GET_BITS(_chk, 16, 8), \
		PE_GET_BITS(_chk, 8, 8), \
		PE_GET_BITS(_chk, 0, 8))
#if 1
#define PE_KWRAP_INTERPOL(_dst, _coeff, _max, _cast, _member)	\
	do {\
		UINT8 i=0;\
		for (i=0;i<(_max);i++)\
		{\
			out_tbl[i] = (UINT8)_coeff[i]._member;\
		}\
		_dst._member = (_cast)\
		(_KWRAP_PE_GetOutValByInterpol(in, in_tbl, out_tbl, 0, (_max)));\
	}while (0)
#else
#define PE_KWRAP_INTERPOL(_dst, _coeff, _max, _cast, _member)	\
	do {\
		UINT8 i=0;\
		for (i=0;i<(_max);i++)\
		{\
			out_tbl[i] = (float)_coeff[i]._member;\
		}\
		_dst._member = (_cast)\
		(_KWRAP_PE_GetOutValByInterpol(in, in_tbl, out_tbl, 0, (_max))+0.5);\
	}while (0)
#endif

/* kwrap not supported print */
#define PE_KWRAP_NOTI_NOT_SUPPORTED()		\
	PE_NOTI("not supported.(ver. chip:0x%X, kwrap:0x%X)\n", \
	lx_chip_rev(), g_pe_kwrap_ver_mask);ret = RET_OK

/* kwrap check state*/
#define PE_KWRAP_CHECK_WINID(_paramtype, _blktype)	\
	{\
		UINT32 chk_size=0, chk_wid=0, chk_i=0;\
		for (chk_i=0;chk_i<LX_PE_WIN_ALL;chk_i++)\
		{\
			prev[chk_i].win_id=pp->win_id;\
		}\
		KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);\
		chk_size = sizeof(_paramtype);\
		chk_wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
			&chk, (void *)prev, (void *)pp, chk_size);\
		PE_KWRAP_SHOW_CHK(_blktype, chk_wid, chk);\
		PE_CHECK_ACTION(chk_wid>LX_PE_WIN_ALL, ret=RET_OK;break);\
		pp->win_id = (LX_PE_WIN_ID)chk_wid;\
	}

/* kwrap check state*/
#define PE_KWRAP_CHECK_CMN_WINID(_paramtype, _blktype)	\
	{\
		UINT32 chk_size=0, chk_wid=0, chk_i=0;\
		for (chk_i=0;chk_i<LX_PE_WIN_ALL;chk_i++)\
		{\
			prev[chk_i].win_id=pp->win_id;\
		}\
		KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);\
		chk_size = sizeof(_paramtype);\
		chk_wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
			&chk, (void *)prev, (void *)pp, chk_size);\
		PE_KWRAP_SHOW_CHK(_blktype, chk_wid, chk);\
		pp->win_id = (LX_PE_WIN_ID)chk_wid;\
	}

/**
*	PE_KWRAP_DBG_TYPE_MAX should be less than 32(<0x20)
*	because it is the shifting value.
*/
typedef enum
{
	PE_KWRAP_DBG_TYPE_NONE		= 0x00,
	PE_KWRAP_DBG_TYPE_INIT		= 0x01,
	PE_KWRAP_DBG_TYPE_DBG		= 0x02,
	PE_KWRAP_DBG_TYPE_CMN		= 0x03,
	PE_KWRAP_DBG_TYPE_CSC		= 0x04,
	PE_KWRAP_DBG_TYPE_CMG		= 0x05,
	PE_KWRAP_DBG_TYPE_NRD		= 0x06,
	PE_KWRAP_DBG_TYPE_DNT		= 0x07,
	PE_KWRAP_DBG_TYPE_SHP		= 0x08,
	PE_KWRAP_DBG_TYPE_CCM		= 0x09,
	PE_KWRAP_DBG_TYPE_DCM		= 0x0a,
	PE_KWRAP_DBG_TYPE_HST		= 0x0b,
	PE_KWRAP_DBG_TYPE_HDR		= 0x0c,
	PE_KWRAP_DBG_TYPE_WIN		= 0x0d,
	PE_KWRAP_DBG_TYPE_ETC		= 0x0e,
	PE_KWRAP_DBG_TYPE_CHK		= 0x0f,
	PE_KWRAP_DBG_TYPE_MAX
}
PE_KWRAP_DBG_TYPE_T;

/* conv default param type to debug type */
#define PE_KWRAP_DFLT_P_TO_DBG_T(_x)		(\
	((_x)==PE_KWRAP_DFLT_PARAM_TNR_CMN)? PE_KWRAP_DBG_TYPE_NRD:\
	((_x)==PE_KWRAP_DFLT_PARAM_TNR_DTL)? PE_KWRAP_DBG_TYPE_NRD:\
	((_x)==PE_KWRAP_DFLT_PARAM_DNR_CMN)? PE_KWRAP_DBG_TYPE_NRD:\
	((_x)==PE_KWRAP_DFLT_PARAM_DNR_DTL)? PE_KWRAP_DBG_TYPE_NRD:\
	((_x)==PE_KWRAP_DFLT_PARAM_REN_CMN)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_REN_HOR)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_REN_VER)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_REN_MIS)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_REN_EDG)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_REN_DTL)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_SRS_CMN)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_SRS_HOR)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_SRS_VER)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_SRS_MIS)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_SRS_EDG)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_SRS_DTL)? PE_KWRAP_DBG_TYPE_SHP:\
	((_x)==PE_KWRAP_DFLT_PARAM_CSC_GMT)? PE_KWRAP_DBG_TYPE_CSC:\
	PE_KWRAP_DBG_TYPE_MAX)


/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/
void 	KWRAP_PE_UpdateCheckState(LX_PE_WIN_ID id, UINT32 *chk, const char *func, int line);
UINT32 	KWRAP_PE_CheckValidWinId(LX_PE_WIN_ID id, UINT32 *chk, void *prev, void *cur, UINT32 size);
void 	_KWRAP_PE_ConfigVersionMask(void);
void 	_KWRAP_PE_ClearVersionMask(void);
int 		KWRAP_PE_SetDefaultParam(PE_KWRAP_CTRL_T *param, UINT32 type, void *ctrl, const char *func, int line);
UINT32 	KWRAP_PE_CheckDoubleSetting(LX_PE_WIN_ID id, UINT32 *chk, void *prev, void *cur, UINT32 size);
#if 0
float _KWRAP_PE_GetOutValByInterpol(float in,
                                          float *in_tbl,
                                          float *out_tbl,
                                          UINT8 min,
                                          UINT8 max);
#endif
UINT8 	_KWRAP_PE_GetOutValByInterpol(UINT8 in, UINT8 *in_tbl, UINT8 *out_tbl, UINT8 min, UINT8 max);

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_KWRAP_DEF_H_ */
