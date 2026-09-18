#ifndef _ION_IO_REG_SLAVE_H_
#define _ION_IO_REG_SLAVE_H_

#include <linux/types.h>
#include "ion_io_reg_ctrl.h"

struct te_dev_ion;

int ion_io_slave_reg_write(struct te_dev_ion *dev, u32 val, u16 addr);
int ion_io_slave_reg_read(struct te_dev_ion *dev, u32 *val, u16 addr);
int ion_io_slave_set_clock_gate(struct te_dev_ion *dev, u8 idx, bool en);
int ion_io_slave_do_reset(struct te_dev_ion *dev, u8 idx);
int ion_io_slave_set_mux(struct te_dev_ion *dev, u8 ext_num);
int ion_io_slave_set_ptg_cfg(struct te_dev_ion *dev);
int ion_io_slave_set_ptg_pkt0(struct te_dev_ion *dev);
int ion_io_slave_set_align_cfg(struct te_dev_ion *dev, u8 ext_num,
                               enum ion_io_type type, bool parallel);
int ion_io_slave_set_start_code(struct te_dev_ion *dev, u8 ext_num,
				enum ion_io_type type);

#endif	/* _ION_IO_REG_SLAVE_H_ */
