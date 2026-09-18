#ifndef __IRBLASTER_H__
#define __IRBLASTER_H__

#define IRBLASTER_NEC		0x00
#define IRBLASTER_SI12		0x01
#define IRBLASTER_SI15		0x02
#define IRBLASTER_SI20		0x03
#define IRBLASTER_RC_5		0x04
#define IRBLASTER_RC_6		0x05
#define IRBLASTER_SANY		0x06
#define IRBLASTER_CUS0		0x07
#define IRBLASTER_MAX		0x08


typedef struct
{
  void (*init)(int index);
  void (*exit)(void);
  int (*status)(int prot_or_rpt);
  void (*tx)(int ptype);
} irblaster_driver_t;

irblaster_driver_t* get_irblaster_driver(void);

void irblaster_init(int index);
void irblaster_exit(void);
int irblaster_status(int prot_or_rpt);
void irblaster_tx(int ptype);

#endif	// __IRBLASTER_H__
