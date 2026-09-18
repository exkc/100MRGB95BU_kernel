#ifndef _ION_CI_SLAVE_REG_H_
#define _ION_CI_SLAVE_REG_H_

#include <linux/types.h>

struct te_dev_ion;

int ion_ci_slave_reg_write(struct te_dev_ion *dev, u32 val, u16 addr);
int ion_ci_slave_reg_read(struct te_dev_ion *dev, u32 *val, u16 addr);

void ion_ci_slave_ctop_init(struct te_dev_ion *dev);
void ion_ci_slave_iomux_ctrl_init(struct te_dev_ion *dev);
void ion_ci_slave_mcrg_init(struct te_dev_ion *dev);
void ion_ci_slave_scrg_init(struct te_dev_ion *dev);
void ion_ci_slave_srds12to3_init(struct te_dev_ion *dev);

#endif	/* _ION_CI_SLAVE_REG_H_ */
