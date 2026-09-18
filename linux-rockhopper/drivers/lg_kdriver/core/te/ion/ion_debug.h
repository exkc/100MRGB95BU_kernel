#ifndef _ION_DEBUG_H_
#define _ION_DEBUG_H_

struct te_device;

int ion_debug_init(struct te_device *dev);
void ion_debug_release(struct te_device *dev);

#endif	/* _ION_DEBUG_H_ */
