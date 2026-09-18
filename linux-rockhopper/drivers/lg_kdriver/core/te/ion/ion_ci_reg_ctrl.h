#ifndef _ION_CI_REG_CTRL_H_
#define _ION_CI_REG_CTRL_H_

#include "reg/te_reg_base.h"

#define TX_ION g_ci_ion

#define _SPI_RdFL(_d, _shdw_, _phys_, _r)                  \
	ion_ci_reg_read((_d), 0, ((u32 *)(&(_shdw_->_r))), \
			(uintptr_t)(&(_phys_->_r)))
#define _SPI_WrFL(_d, _shdw_, _phys_, _r)                   \
	ion_ci_reg_write((_d), 0, *((u32 *)(&(_shdw_->_r))), \
			 (uintptr_t)(&(_phys_->_r)))
#define _SPI_Wr01(_d, _shdw_, _r, _f01, _v01) TE_REG_Wr01(_shdw_, _r, _f01, _v01)
#define _SPI_Rd01(_d, _shdw_, _r, _f01, _v01) TE_REG_Rd01(_shdw_, _r, _f01, _v01)

#define TX_RdFL(_d, _shdw_, _phys_, _r) _SPI_RdFL(_d, _shdw_, _phys_, _r)
#define TX_WrFL(_d, _shdw_, _phys_, _r) _SPI_WrFL(_d, _shdw_, _phys_, _r)
#define TX_Wr01(_d, _shdw_, _r, _f01, _v01) \
	_SPI_Wr01(_d, _shdw_, _r, _f01, _v01)
#define TX_Rd01(_d, _shdw_, _r, _f01, _v01) \
	_SPI_Rd01(_d, _shdw_, _r, _f01, _v01)


#endif //_ION_CI_REG_CTRL_H_
