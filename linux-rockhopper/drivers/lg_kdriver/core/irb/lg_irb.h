#ifndef __ARCH_LG_IRB_H__
#define __ARCH_LG_IRB_H__


#define REPEAT_MASK		0x02
#define PROTOCOL_MASK		0x01


#define CR_IREN 		0
#define CR_TX 			1
#define CR_RPT 			2
#define CR_COFF			3
#define CR_PTYPE		4
#define CR_DUTY			9

#define CR_IREN_SET		(1 << CR_IREN)
#define CR_IREN_CLR		~CR_IREN_SET
#define CR_TX_SET		(1 << CR_TX)
#define CR_TX_CLR		~CR_TX_SET
#define CR_RPT_SET		(1 << CR_RPT)
#define CR_RPT_CLR		~CR_RPT_SET
#define CR_COFF_SET		(1 << CR_COFF)
#define CR_COFF_CLR		~CR_COFF_SET
#define CR_PTYPE_SET		(0x1f << CR_PTYPE)
#define CR_PTYPE_CLR		~CR_PTYPE_SET
#define CR_PTYPE_NEC		(0x00 << CR_PTYPE)
#define CR_PTYPE_SI12		(0x01 << CR_PTYPE)
#define CR_PTYPE_SI15		(0x02 << CR_PTYPE)
#define CR_PTYPE_SI20		(0x03 << CR_PTYPE)
#define CR_PTYPE_RC_5		(0x04 << CR_PTYPE)
#define CR_PTYPE_RC_6		(0x05 << CR_PTYPE)
#define CR_PTYPE_SANY		(0x06 << CR_PTYPE)
#define CR_PTYPE_CUS0		(0x1f << CR_PTYPE)
#define CR_DUTY_SET		(1 << CR_DUTY)
#define CR_DUTY_CLR		~CR_DUTY_SET

#define CPR_PSIZE		0
#define CPR_RTYPE		6
#define CPR_RSIZE		8
#define CPR_RTPSP		13

#define CPR_PSIZE_MASK		(0x3f << CPR_PSIZE)

#define SR_BUSY			0
#define SR_RBUSY		1

#define SR_BUSY_SET		(1 << SR_BUSY)
#define SR_RBUSY_SET		(1 << SR_RBUSY)

#define SIZE_PTYPE_NEC		3
#define SIZE_PTYPE_SI12		2
#define SIZE_PTYPE_SI15		2
#define SIZE_PTYPE_SI20		3
#define SIZE_PTYPE_RC_5		2
#define SIZE_PTYPE_RC_6		3
#define SIZE_PTYPE_SANY		3

#define SIZE_PTYPE_CUS_MASK	0x3f

#define DRXCR_MARKFIRSTONE	(1 << 7)
#define DRXCR_MARKFIRSTZERO	(1 << 6)
#define DRXCR_TOGGLE		(1 << 5)
#define DRXCR_MSB		(1 << 4)

#define DRX01_TAIL_OFFSET	8

typedef struct lg_irb_unit
{
  volatile unsigned int dr;
  volatile unsigned int dr_cr;
  volatile unsigned int dr_zero;
  volatile unsigned int dr_one;
} lg_irb_unit_t;


typedef struct lg_irb
{
  volatile unsigned int cr;
  volatile unsigned int const sr;
  volatile unsigned int icrd;
  volatile unsigned int fcrd;
  volatile unsigned int tpr;
  volatile unsigned int rpr;
  volatile unsigned int rpsr;
  unsigned int const reserved1;
  volatile unsigned int imsc;
  volatile unsigned int const ris;
  volatile unsigned int const mis;
  volatile unsigned int icr;
  unsigned int const reserved2[48];
  volatile unsigned int cpr;
  volatile unsigned int tr;
  unsigned int const reserved3[2];
  lg_irb_unit_t prot_data[31];
  lg_irb_unit_t rpt_data[2];
} lg_irb_t;

#endif	// __ARCH_LG_IRB_H__

