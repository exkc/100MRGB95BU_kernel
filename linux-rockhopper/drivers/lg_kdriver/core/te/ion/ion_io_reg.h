#ifndef _ION_IO_REG_H_
#define _ION_IO_REG_H_

#include <linux/types.h>

struct te_dev_ion;

int ion_io_reg_write(struct te_dev_ion *dev, u8 ch, u32 val, u32 addr);
int ion_io_reg_read(struct te_dev_ion *dev, u8 ch, u32 *val, u32 addr);
int ion_io_reg_set_clock_gate(struct te_dev_ion *dev, u8 ch, u8 idx, bool en);
int ion_io_reg_set_tp(struct te_dev_ion *dev, u8 ext_num, bool parallel);
int ion_io_reg_set_tlv(struct te_dev_ion *dev, u8 ext_num, bool parallel);
int ion_io_reg_set_lgc(struct te_dev_ion *dev, u8 ext_num, bool parallel);

int ion_io_reg_init(struct te_dev_ion *dev);
void ion_io_reg_release(struct te_dev_ion *dev);

#endif	/* _ION_IO_REG_H_ */
