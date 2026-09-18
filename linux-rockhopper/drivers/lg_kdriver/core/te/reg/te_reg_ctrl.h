/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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

/** @file
 *
 *  sdec driver
 *
 *  @author	Kyungseok Hyun
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#ifndef _TE_REG_CTRL_H_
#define _TE_REG_CTRL_H_

#include <linux/types.h>
#include <lg1k/te/te.h>

//#include "sys_reg_base.h"
#include "te_reg_base.h"
#include "te_reg_db.h"

#ifdef TE_EMULATOR

#ifdef TE_REG_RdFL
#undef TE_REG_RdFL
#endif
#define TE_REG_RdFL(_shdw,_phys,_r)		\
do {						\
	u32 _addr_ = (u32)&(_phys)->_r;		\
	u32 *_val_ = (u32*)&(_shdw)->_r;	\
	TE_EMUL_RegRead(_addr_, _val_);		\
} while(0)

#ifdef TE_REG_WrFL
#undef TE_REG_WrFL
#endif
#define TE_REG_WrFL(_shdw,_phys,_r)		\
do {						\
	u32 _addr_ = (u32)&(_phys)->_r;		\
	u32 _val_ = *(u32*)&(_shdw)->_r;	\
	TE_EMUL_RegWrite(_addr_, _val_);	\
} while(0)
#endif

typedef struct {
	union {
		u32 *addr;
		TPI_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile TPI_REG_T *reg;
	} phys;

	u32 size;
} TPI_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		FE_PIDF_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile FE_PIDF_REG_T *reg;
	} phys;

	u32 size;
} FE_PIDF_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		FE_TSBUF_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile FE_TSBUF_REG_T *reg;
	} phys;

	u32 size;
} FE_TSBUF_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		FE_STCC_Y18_REG_T *y18_stcc;
		FE_STCC_Y21_REG_T *y21_stcc;
		FE_STCC_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile FE_STCC_Y18_REG_T *y18_stcc;
		volatile FE_STCC_Y21_REG_T *y21_stcc;
		volatile FE_STCC_REG_T *reg;
	} phys;

	u32 size;
} FE_STCC_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		A3_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile A3_REG_T *reg;
	} phys;

	u32 size;
} A3_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		TOP_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile TOP_REG_T *reg;
	} phys;

	u32 size;
} TOP_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		BE_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile BE_REG_T *reg;
	} phys;

	u32 size;
} BE_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		UPLOAD_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile UPLOAD_REG_T *reg;
	} phys;

	u32 size;
} UPLOAD_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		CIPLUS_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile CIPLUS_REG_T *reg;
	} phys;

	u32 size;
} CIPLUS_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
	} shdw;

	union {
		volatile u32 __iomem *addr;
	} phys;

	u32 size;
} MCU_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		ARIB2_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile ARIB2_REG_T *reg;
	} phys;

	u32 size;
} ARIB2_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		DUMPER_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile DUMPER_REG_T *reg;
	} phys;

	u32 size;
} DUMPER_REG_CTRL_T;

typedef struct {
	union {
		u32 *addr;
		DSC_TOP_REG_T *reg;
	} shdw;

	union {
		volatile u32 __iomem *addr;
		volatile DSC_TOP_REG_T *reg;
	} phys;

	u32 size;
} DSC_REG_CTRL_T;

/* Register access macros
 * Note that only Flush macros can access physical registers */
#define REG_WRITE(addr, val)	__raw_writel(val , (void*)(addr))
#define REG_READ(addr)		__raw_readl((void*)(addr))

/**
 * TOP Reg Access
 **/

#define TOP_REG_SHDW		(g_te_reg_ctrl.top.shdw.reg)
#define TOP_REG_PHYS		(g_te_reg_ctrl.top.phys.reg)

/* For direct access */
#define TOP_REG_READ32(_r)		(*((u32*)(&(TOP_REG_PHYS->_r))))
#define TOP_REG_WRITE32(_r,_v)		(*((u32*)(&(TOP_REG_PHYS->_r))) = _v)

/* For entry */
#define TOP_RdFL(_r)			TE_REG_RdFL(TOP_REG_SHDW, TOP_REG_PHYS, _r)
#define TOP_WrFL(_r)			TE_REG_WrFL(TOP_REG_SHDW, TOP_REG_PHYS, _r)

#define TOP_Rd(_r,_v)			do{ _v = TE_REG_Rd(TOP_REG_SHDW,_r); } while(0)
#define TOP_Wr(_r,_v)			TE_REG_Wr(TOP_REG_SHDW,_r,_v)

#define TOP_Rd01(_r,_f01,_v01)		TE_REG_Rd01(TOP_REG_SHDW,_r,_f01,_v01)
#define TOP_Wr01(_r,_f01,_v01)		TE_REG_Wr01(TOP_REG_SHDW,_r,_f01,_v01)

/**
 * TPI Reg Access
 **/

#define TPI_REG_SHDW		(g_te_reg_ctrl.tpi.shdw.reg)
#define TPI_REG_PHYS		(g_te_reg_ctrl.tpi.phys.reg)

/* For direct access */
#define TPI_REG_READ32(_r)		(*((u32*)(&(TPI_REG_PHYS->_r))))
#define TPI_REG_WRITE32(_r,_v)		(*((u32*)(&(TPI_REG_PHYS->_r))) = _v)

/* For entry */
#define TPI_RdFL(_r)			TE_REG_RdFL(TPI_REG_SHDW, TPI_REG_PHYS, _r)
#define TPI_WrFL(_r)			TE_REG_WrFL(TPI_REG_SHDW, TPI_REG_PHYS, _r)

#define TPI_Rd(_r,_v)			do{ _v = TE_REG_Rd(TPI_REG_SHDW,_r); } while(0)
#define TPI_Wr(_r,_v)			TE_REG_Wr(TPI_REG_SHDW,_r,_v)

#define TPI_Rd01(_r,_f01,_v01)		TE_REG_Rd01(TPI_REG_SHDW,_r,_f01,_v01)
#define TPI_Wr01(_r,_f01,_v01)		TE_REG_Wr01(TPI_REG_SHDW,_r,_f01,_v01)

/**
 * BE TOP Access
 **/

#define BE_REG_SHDW		(g_te_reg_ctrl.be.shdw.reg)
#define BE_REG_PHYS		(g_te_reg_ctrl.be.phys.reg)

/* For direct access */
#define BE_REG_READ32(_r)		(*((u32*)(&(BE_REG_PHYS->_r))))
#define BE_REG_WRITE32(_r,_v)		(*((u32*)(&(BE_REG_PHYS->_r))) = _v)

/* For entry */
#define BE_RdFL(_r)			TE_REG_RdFL(BE_REG_SHDW, BE_REG_PHYS, _r)
#define BE_WrFL(_r)			TE_REG_WrFL(BE_REG_SHDW, BE_REG_PHYS, _r)

#define BE_Rd(_r,_v)			do{ _v = TE_REG_Rd(BE_REG_SHDW,_r); } while(0)
#define BE_Wr(_r,_v)			TE_REG_Wr(BE_REG_SHDW,_r,_v)

#define BE_Rd01(_r,_f01,_v01)		TE_REG_Rd01(BE_REG_SHDW,_r,_f01,_v01)
#define BE_Wr01(_r,_f01,_v01)		TE_REG_Wr01(BE_REG_SHDW,_r,_f01,_v01)

/**
 * UPLOAD Access
 **/

#define UPLOAD_REG_SHDW(i)	(g_te_reg_ctrl.upload[i].shdw.reg)
#define UPLOAD_REG_PHYS(i)	(g_te_reg_ctrl.upload[i].phys.reg)

/* For direct access */
#define UPLOAD_REG_READ32(i,_r)		(*((u32*)(&(UPLOAD_REG_PHYS(i)->_r))))
#define UPLOAD_REG_WRITE32(i,_r,_v)	(*((u32*)(&(UPLOAD_REG_PHYS(i)->_r))) = _v)

/* For entry */
#define UPLOAD_RdFL(i,_r)		TE_REG_RdFL(UPLOAD_REG_SHDW(i), UPLOAD_REG_PHYS(i), _r)
#define UPLOAD_WrFL(i,_r)		TE_REG_WrFL(UPLOAD_REG_SHDW(i), UPLOAD_REG_PHYS(i), _r)

#define UPLOAD_Rd(i,_r,_v)		do{ _v = TE_REG_Rd(UPLOAD_REG_SHDW(i),_r); } while(0)
#define UPLOAD_Wr(i,_r,_v)		TE_REG_Wr(UPLOAD_REG_SHDW(i),_r,_v)

#define UPLOAD_Rd01(i,_r,_f01,_v01)	TE_REG_Rd01(UPLOAD_REG_SHDW(i),_r,_f01,_v01)
#define UPLOAD_Wr01(i,_r,_f01,_v01)	TE_REG_Wr01(UPLOAD_REG_SHDW(i),_r,_f01,_v01)

/**
 * CIPLUS TOP Access
 **/

#define CIPLUS_REG_SHDW		(g_te_reg_ctrl.ciplus.shdw.reg)
#define CIPLUS_REG_PHYS		(g_te_reg_ctrl.ciplus.phys.reg)

/* For direct access */
#define CIPLUS_REG_READ32(_r)		(*((u32*)(&(CIPLUS_REG_PHYS->_r))))
#define CIPLUS_REG_WRITE32(_r,_v)	(*((u32*)(&(CIPLUS_REG_PHYS->_r))) = _v)

/* For entry */
#define CIPLUS_RdFL(_r)			TE_REG_RdFL(CIPLUS_REG_SHDW, CIPLUS_REG_PHYS, _r)
#define CIPLUS_WrFL(_r)			TE_REG_WrFL(CIPLUS_REG_SHDW, CIPLUS_REG_PHYS, _r)

#define CIPLUS_Rd(_r,_v)		do{ _v = TE_REG_Rd(CIPLUS_REG_SHDW,_r); } while(0)
#define CIPLUS_Wr(_r,_v)		TE_REG_Wr(CIPLUS_REG_SHDW,_r,_v)

#define CIPLUS_Rd01(_r,_f01,_v01)	TE_REG_Rd01(CIPLUS_REG_SHDW,_r,_f01,_v01)
#define CIPLUS_Wr01(_r,_f01,_v01)	TE_REG_Wr01(CIPLUS_REG_SHDW,_r,_f01,_v01)

/**
 * FE_PIDF Reg Access
 **/
#define FE_PIDF_REG_SHDW	(g_te_reg_ctrl.pidf.shdw.reg)
#define FE_PIDF_REG_PHYS	(g_te_reg_ctrl.pidf.phys.reg)

/* For direct access */
#define FE_PIDF_REG_READ32(_r)		(*((u32*)(&(FE_PIDF_REG_PHYS->_r))))
#define FE_PIDF_REG_WRITE32(_r,_v)	(*((u32*)(&(FE_PIDF_REG_PHYS->_r))) = _v)

/* For entry */
#define FE_PIDF_RdFL(_r)		TE_REG_RdFL(FE_PIDF_REG_SHDW, FE_PIDF_REG_PHYS, _r)
#define FE_PIDF_WrFL(_r)		TE_REG_WrFL(FE_PIDF_REG_SHDW, FE_PIDF_REG_PHYS, _r)

#define FE_PIDF_Rd(_r,_v)		do{ _v = TE_REG_Rd(FE_PIDF_REG_SHDW,_r); } while(0)
#define FE_PIDF_Wr(_r,_v)		TE_REG_Wr(FE_PIDF_REG_SHDW,_r,_v)

#define FE_PIDF_Rd01(_r,_f01,_v01)	TE_REG_Rd01(FE_PIDF_REG_SHDW,_r,_f01,_v01)
#define FE_PIDF_Wr01(_r,_f01,_v01)	TE_REG_Wr01(FE_PIDF_REG_SHDW,_r,_f01,_v01)

/**
 * FE_TSBUF Reg Access
 **/

#define FE_TSBUF_REG_SHDW	(g_te_reg_ctrl.tsbuf.shdw.reg)
#define FE_TSBUF_REG_PHYS	(g_te_reg_ctrl.tsbuf.phys.reg)

/* For direct access */
#define FE_TSBUF_REG_READ32(_r)		(*((u32*)(&(FE_TSBUF_REG_PHYS->_r))))
#define FE_TSBUF_REG_WRITE32(_r,_v)	(*((u32*)(&(FE_TSBUF_REG_PHYS->_r))) = _v)

/* For entry */
#define FE_TSBUF_RdFL(_r)		TE_REG_RdFL(FE_TSBUF_REG_SHDW, FE_TSBUF_REG_PHYS, _r)
#define FE_TSBUF_WrFL(_r)		TE_REG_WrFL(FE_TSBUF_REG_SHDW, FE_TSBUF_REG_PHYS, _r)

#define FE_TSBUF_Rd(_r,_v)		do{ _v = TE_REG_Rd(FE_TSBUF_REG_SHDW,_r); } while(0)
#define FE_TSBUF_Wr(_r,_v)		TE_REG_Wr(FE_TSBUF_REG_SHDW,_r,_v)

#define FE_TSBUF_Rd01(_r,_f01,_v01)	TE_REG_Rd01(FE_TSBUF_REG_SHDW,_r,_f01,_v01)
#define FE_TSBUF_Wr01(_r,_f01,_v01)	TE_REG_Wr01(FE_TSBUF_REG_SHDW,_r,_f01,_v01)

/**
 * FE_STCC Legacy Reg Access
 **/
#define FE_STCC_Y18_REG_SHDW		(g_te_reg_ctrl.stcc.shdw.y18_stcc)
#define FE_STCC_Y18_REG_PHYS		(g_te_reg_ctrl.stcc.phys.y18_stcc)

/* For direct access */
#define FE_STCC_Y18_REG_READ32(_r)	(*((u32*)(&(FE_STCC_Y18_REG_PHYS->_r))))
#define FE_STCC_Y18_REG_WRITE32(_r,_v)	(*((u32*)(&(FE_STCC_Y18_REG_PHYS->_r))) = _v)

/* For entry */
#define FE_STCC_Y18_RdFL(_r)		TE_REG_RdFL(FE_STCC_Y18_REG_SHDW, FE_STCC_Y18_REG_PHYS, _r)
#define FE_STCC_Y18_WrFL(_r)		TE_REG_WrFL(FE_STCC_Y18_REG_SHDW, FE_STCC_Y18_REG_PHYS, _r)

#define FE_STCC_Y18_Rd(_r,_v)		do{ _v = TE_REG_Rd(FE_STCC_Y18_REG_SHDW,_r); } while(0)
#define FE_STCC_Y18_Wr(_r,_v)		TE_REG_Wr(FE_STCC_Y18_REG_SHDW,_r,_v)

#define FE_STCC_Y18_Rd01(_r,_f01,_v01)	TE_REG_Rd01(FE_STCC_Y18_REG_SHDW,_r,_f01,_v01)
#define FE_STCC_Y18_Wr01(_r,_f01,_v01)	TE_REG_Wr01(FE_STCC_Y18_REG_SHDW,_r,_f01,_v01)


/**
 * FE_STCC Legacy Reg Access
 **/
#define FE_STCC_Y21_REG_SHDW		(g_te_reg_ctrl.stcc.shdw.y21_stcc)
#define FE_STCC_Y21_REG_PHYS		(g_te_reg_ctrl.stcc.phys.y21_stcc)

/* For direct access */
#define FE_STCC_Y21_REG_READ32(_r)	(*((u32*)(&(FE_STCC_Y21_REG_PHYS->_r))))
#define FE_STCC_Y21_REG_WRITE32(_r,_v)	(*((u32*)(&(FE_STCC_Y21_REG_PHYS->_r))) = _v)

/* For entry */
#define FE_STCC_Y21_RdFL(_r)		TE_REG_RdFL(FE_STCC_Y21_REG_SHDW, FE_STCC_Y21_REG_PHYS, _r)
#define FE_STCC_Y21_WrFL(_r)		TE_REG_WrFL(FE_STCC_Y21_REG_SHDW, FE_STCC_Y21_REG_PHYS, _r)

#define FE_STCC_Y21_Rd(_r,_v)		do{ _v = TE_REG_Rd(FE_STCC_Y21_REG_SHDW,_r); } while(0)
#define FE_STCC_Y21_Wr(_r,_v)		TE_REG_Wr(FE_STCC_Y21_REG_SHDW,_r,_v)

#define FE_STCC_Y21_Rd01(_r,_f01,_v01)	TE_REG_Rd01(FE_STCC_Y21_REG_SHDW,_r,_f01,_v01)
#define FE_STCC_Y21_Wr01(_r,_f01,_v01)	TE_REG_Wr01(FE_STCC_Y21_REG_SHDW,_r,_f01,_v01)

/**
 * FE_STCC Reg Access
 **/
#define FE_STCC_REG_SHDW		(g_te_reg_ctrl.stcc.shdw.reg)
#define FE_STCC_REG_PHYS		(g_te_reg_ctrl.stcc.phys.reg)

/* For direct access */
#define FE_STCC_REG_READ32(_r)		(*((u32*)(&(FE_STCC_REG_PHYS->_r))))
#define FE_STCC_REG_WRITE32(_r,_v)	(*((u32*)(&(FE_STCC_REG_PHYS->_r))) = _v)

/* For entry */
#define FE_STCC_RdFL(_r)		TE_REG_RdFL(FE_STCC_REG_SHDW, FE_STCC_REG_PHYS, _r)
#define FE_STCC_WrFL(_r)		TE_REG_WrFL(FE_STCC_REG_SHDW, FE_STCC_REG_PHYS, _r)

#define FE_STCC_Rd(_r,_v)		do{ _v = TE_REG_Rd(FE_STCC_REG_SHDW,_r); } while(0)
#define FE_STCC_Wr(_r,_v)		TE_REG_Wr(FE_STCC_REG_SHDW,_r,_v)

#define FE_STCC_Rd01(_r,_f01,_v01)	TE_REG_Rd01(FE_STCC_REG_SHDW,_r,_f01,_v01)
#define FE_STCC_Wr01(_r,_f01,_v01)	TE_REG_Wr01(FE_STCC_REG_SHDW,_r,_f01,_v01)

/**
 * ATSC3 Reg Access
 **/
#define ATSC3_REG_SHDW		(g_te_reg_ctrl.atsc3.shdw.reg)
#define ATSC3_REG_PHYS		(g_te_reg_ctrl.atsc3.phys.reg)

/* For direct access */
#define ATSC3_REG_READ32(_r)		(*((u32*)(&(ATSC3_REG_PHYS->_r))))
#define ATSC3_REG_WRITE32(_r,_v)	(*((u32*)(&(ATSC3_REG_PHYS->_r))) = _v)

/* For entry */
#define ATSC3_RdFL(_r)			TE_REG_RdFL(ATSC3_REG_SHDW, ATSC3_REG_PHYS, _r)
#define ATSC3_WrFL(_r)			TE_REG_WrFL(ATSC3_REG_SHDW, ATSC3_REG_PHYS, _r)

#define ATSC3_Rd(_r,_v)			do{ _v = TE_REG_Rd(ATSC3_REG_SHDW,_r); } while(0)
#define ATSC3_Wr(_r,_v)			TE_REG_Wr(ATSC3_REG_SHDW,_r,_v)

#define ATSC3_Rd01(_r,_f01,_v01)	TE_REG_Rd01(ATSC3_REG_SHDW,_r,_f01,_v01)
#define ATSC3_Wr01(_r,_f01,_v01)	TE_REG_Wr01(ATSC3_REG_SHDW,_r,_f01,_v01)

/**
 * ARIB2 Reg Access
 **/
#define ARIB2_REG_SHDW		(g_te_reg_ctrl.arib2.shdw.reg)
#define ARIB2_REG_PHYS		(g_te_reg_ctrl.arib2.phys.reg)

/* For direct access */
#define ARIB2_REG_READ32(_r)		(*((u32*)(&(ARIB2_REG_PHYS->_r))))
#define ARIB2_REG_WRITE32(_r,_v)	(*((u32*)(&(ARIB2_REG_PHYS->_r))) = _v)

/* For entry */
#define ARIB2_RdFL(_r)			TE_REG_RdFL(ARIB2_REG_SHDW, ARIB2_REG_PHYS, _r)
#define ARIB2_WrFL(_r)			TE_REG_WrFL(ARIB2_REG_SHDW, ARIB2_REG_PHYS, _r)

#define ARIB2_Rd(_r,_v)			do{ _v = TE_REG_Rd(ARIB2_REG_SHDW,_r); } while(0)
#define ARIB2_Wr(_r,_v)			TE_REG_Wr(ARIB2_REG_SHDW,_r,_v)

#define ARIB2_Rd01(_r,_f01,_v01)	TE_REG_Rd01(ARIB2_REG_SHDW,_r,_f01,_v01)
#define ARIB2_Wr01(_r,_f01,_v01)	TE_REG_Wr01(ARIB2_REG_SHDW,_r,_f01,_v01)

/**
 * DUMPER Reg Access
 **/
#define DUMPER_REG_SHDW		(g_te_reg_ctrl.dumper.shdw.reg)
#define DUMPER_REG_PHYS		(g_te_reg_ctrl.dumper.phys.reg)

/* For direct access */
#define DUMPER_REG_READ32(_r)		(*((u32*)(&(DUMPER_REG_PHYS->_r))))
#define DUMPER_REG_WRITE32(_r,_v)	(*((u32*)(&(DUMPER_REG_PHYS->_r))) = _v)

/* For entry */
#define DUMPER_RdFL(_r)			TE_REG_RdFL(DUMPER_REG_SHDW, DUMPER_REG_PHYS, _r)
#define DUMPER_WrFL(_r)			TE_REG_WrFL(DUMPER_REG_SHDW, DUMPER_REG_PHYS, _r)

#define DUMPER_Rd(_r,_v)		do{ _v = TE_REG_Rd(DUMPER_REG_SHDW,_r); } while(0)
#define DUMPER_Wr(_r,_v)		TE_REG_Wr(DUMPER_REG_SHDW,_r,_v)

#define DUMPER_Rd01(_r,_f01,_v01)	TE_REG_Rd01(DUMPER_REG_SHDW,_r,_f01,_v01)
#define DUMPER_Wr01(_r,_f01,_v01)	TE_REG_Wr01(DUMPER_REG_SHDW,_r,_f01,_v01)

/**
 * DSC Access
 **/

#define DSC_REG_SHDW(i)		(g_te_reg_ctrl.dsc[i].shdw.reg)
#define DSC_REG_PHYS(i)		(g_te_reg_ctrl.dsc[i].phys.reg)

/* For direct access */
#define DSC_REG_READ32(i,_r)		(*((u32*)(&(DSC_REG_PHYS(i)->_r))))
#define DSC_REG_WRITE32(i,_r,_v)	(*((u32*)(&(DSC_REG_PHYS(i)->_r))) = _v)

/* For entry */
#define DSC_RdFL(i,_r)			TE_REG_RdFL(DSC_REG_SHDW(i), DSC_REG_PHYS(i), _r)
#define DSC_WrFL(i,_r)			TE_REG_WrFL(DSC_REG_SHDW(i), DSC_REG_PHYS(i), _r)

#define DSC_Rd(i,_r,_v)			do{ _v = TE_REG_Rd(DSC_REG_SHDW(i),_r); } while(0)
#define DSC_Wr(i,_r,_v)			TE_REG_Wr(DSC_REG_SHDW(i),_r,_v)

#define DSC_Rd01(i,_r,_f01,_v01)	TE_REG_Rd01(DSC_REG_SHDW(i),_r,_f01,_v01)
#define DSC_Wr01(i,_r,_f01,_v01)	TE_REG_Wr01(DSC_REG_SHDW(i),_r,_f01,_v01)


/**
 * Extern Variables
 **/
struct te_reg_ctrl {
	TPI_REG_CTRL_T tpi;
	TOP_REG_CTRL_T top;
	FE_PIDF_REG_CTRL_T pidf;
	FE_TSBUF_REG_CTRL_T tsbuf;
	FE_STCC_REG_CTRL_T stcc;
	BE_REG_CTRL_T be;
	UPLOAD_REG_CTRL_T upload[TE_MAX_UPLOAD];
	CIPLUS_REG_CTRL_T ciplus;
	A3_REG_CTRL_T atsc3;
	ARIB2_REG_CTRL_T arib2;
	MCU_REG_CTRL_T mcu[TE_MAX_MCU];
	DUMPER_REG_CTRL_T dumper;
	DSC_REG_CTRL_T dsc[TE_MAX_DSC];
};

extern struct te_reg_ctrl g_te_reg_ctrl;

#endif
