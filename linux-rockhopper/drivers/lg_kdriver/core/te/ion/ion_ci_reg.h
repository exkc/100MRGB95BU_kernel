#ifndef _ION_CI_REG_H_
#define _ION_CI_REG_H_

#include <linux/types.h>

struct te_dev_ion;

int ion_ci_reg_init(struct te_dev_ion *dev);
void ion_ci_reg_release(struct te_dev_ion *dev);

int ion_ci_reg_write(struct te_dev_ion *dev, u8 ch, u32 val, u16 addr);
int ion_ci_reg_read(struct te_dev_ion *dev, u8 ch, u32 *val, u16 addr);

int ion_ci_reg_hw_init(struct te_dev_ion *dev);
int ion_ci_reg_hw_reset(struct te_dev_ion *dev);
int ion_ci_reg_reset_tp(struct te_dev_ion *dev);

/* For SLT */
int ion_ci_reg_init_tp_checker(struct te_dev_ion *dev, u16 pkt_cnt);
int ion_ci_reg_start_tp_checker(struct te_dev_ion *dev, u16 pkt_cnt);

/* For Pro:Idiom API */
int ion_ci_set_tpo_mode(struct te_dev_ion *dev, u8 is_serial);

#endif	/* _ION_CI_REG_H_ */
