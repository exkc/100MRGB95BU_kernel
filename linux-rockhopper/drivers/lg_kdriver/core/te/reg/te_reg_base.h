#ifndef __TE_REG_BASE__
#define __TE_REG_BASE__
#include <linux/types.h>
#include <linux/compiler.h>

#define TE_REG_Data(_addr)		(*(volatile u32 *)(_addr))
#define TE_REG_Addr(_base,_ofs)   	(void __iomem*)((unsigned long)_base + _ofs)

#define TE_REG_RdFL(_shdw,_phys,_r)	((_shdw->_r)=(_phys->_r))
#define TE_REG_WrFL(_shdw,_phys,_r)	((_phys->_r)=(_shdw->_r))

#define TE_REG_Rd(_shdw, _r)		(*((u32*)(&(_shdw->_r))))
#define TE_REG_Wr(_shdw, _r,_v)		((TE_REG_Rd(_shdw,_r))=((u32)(_v)))

#define TE_REG_RdFd(_shdw,_r,_f01)	(_shdw->_r._f01)

#define TE_REG_Rd01(_shdw,_r,_f01,_v01)				\
	do { 					        	\
		(_v01) = (_shdw->_r._f01);			\
	} while(0)

#define TE_REG_Rd02(_shdw,_r,_f01,_v01,_f02,_v02)		\
	do { 							\
	        (_v01) = (_shdw->_r._f01);			\
		(_v02) = (_shdw->_r._f02);			\
	} while(0)


#define TE_REG_Wr01(_shdw,_r,_f01,_v01)	        		\
	do { 							\
                (_shdw->_r._f01) = (_v01);			\
	} while(0)

#define TE_REG_Wr02(_shdw,_r,_f01,_v01,_f02,_v02)		\
	do { 							\
		(_shdw->_r._f01) = (_v01);			\
		(_shdw->_r._f02) = (_v02);			\
	} while(0)


#endif  // __TE_REG_BASE__
