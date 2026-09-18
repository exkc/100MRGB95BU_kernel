#ifndef _REGS_H_
#define _REGS_H_

#include <linux/init.h>
#include <linux/types.h>

typedef uint32_t lgbus_addr_t;
lgbus_addr_t aud_phys_to_lgbus (phys_addr_t address);
phys_addr_t aud_base_address (void);

int __init aregs_init (void);
void __exit aregs_exit (void);
void aregs_dump_control_registers (void);
#endif
