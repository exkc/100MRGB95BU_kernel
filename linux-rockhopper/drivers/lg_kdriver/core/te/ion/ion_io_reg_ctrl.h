#ifndef _ION_IO_REG_CTRL_H_
#define _ION_IO_REG_CTRL_H_

#include "reg/te_reg_base.h"

enum ion_io_type {
	ION_IO_TYPE_TS = 0,
	ION_IO_TYPE_TLV,
	ION_IO_TYPE_LGC,
	ION_IO_TYPE_MAX
};

#define TX_ION g_io_ion

#define _UCOM_RdFL(_d, _shdw_, _phys_, _r)                 \
	ion_io_reg_read((_d), 0, ((u32 *)(&(_shdw_->_r))), \
			(uintptr_t)(&(_phys_->_r)))
#define _UCOM_WrFL(_d, _shdw_, _phys_, _r)                   \
	ion_io_reg_write((_d), 0, *((u32 *)(&(_shdw_->_r))), \
			 (uintptr_t)(&(_phys_->_r)))
#define _UCOM_Wr01(_d, _shdw_, _r, _f01, _v01) TE_REG_Wr01(_shdw_, _r, _f01, _v01)
#define _UCOM_Rd01(_d, _shdw_, _r, _f01, _v01) TE_REG_Rd01(_shdw_, _r, _f01, _v01)

#define TX_RdFL(_d, _shdw_, _phys_, _r) _UCOM_RdFL(_d, _shdw_, _phys_, _r)
#define TX_WrFL(_d, _shdw_, _phys_, _r) _UCOM_WrFL(_d, _shdw_, _phys_, _r)
#define TX_Wr01(_d, _shdw_, _r, _f01, _v01) \
	_UCOM_Wr01(_d, _shdw_, _r, _f01, _v01)
#define TX_Rd01(_d, _shdw_, _r, _f01, _v01) \
	_UCOM_Rd01(_d, _shdw_, _r, _f01, _v01)

#endif //_ION_IO_REG_CTRL_H_
