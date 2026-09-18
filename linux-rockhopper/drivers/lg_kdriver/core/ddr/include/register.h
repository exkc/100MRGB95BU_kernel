#ifndef _REGISTER_H
#define _REGISTER_H

#define REG_RD(addr)        (*(const volatile unsigned int __force *) (addr))
#define REG_WR(addr,b)      (*(volatile unsigned int __force *) (addr) = (b))
#define REG_ARD(addr)       REG_RD(&(addr))
#define REG_AWR(addr,b)     REG_WR(&(addr),(b))

/*
 * Array index: GPIO data address
 *   1:   0x4
 *   2:   0x8
 *   4:  0x10
 *   8:  0x20
 *  16:  0x40
 *  32:  0x80
 *  64: 0x100
 * 128: 0x200
 */
struct pl061_regs {
	uint32_t data[256];
	uint32_t dir;
	uint32_t is;
	uint32_t ibe;
	uint32_t iev;
	uint32_t ie;
	uint32_t ris;
	uint32_t mis;
	uint32_t ic;
};

#endif /* _REGISTER_H */
