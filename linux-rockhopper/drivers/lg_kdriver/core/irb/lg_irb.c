#include <types.h>
#include <stdio.h>
#include <arch/irqs.h>
#include <arch/timers.h>
#include <interrupt.h>

#include <irblaster.h>
#include "lg_irb.h"


static volatile lg_irb_t *irb = (volatile lg_irb_t *)IRBLASTER_BASE;

static lg_irb_t *irb_database = (lg_irb_t *)(0x04000000);

volatile unsigned int lg_irb_irq_flag;

static int lg_irb_cur_protocol = 0;

char *lg_irb_get_protocol_name(int ptype);
void lg_irb_init_nec(lg_irb_t *cur);
void lg_irb_init_sirc(lg_irb_t *cur, int index);
void lg_irb_init_rc(lg_irb_t *cur, int index);
void lg_irb_init_sany(lg_irb_t *cur);
void lg_irb_init_cus(lg_irb_t *cur, int index);

static void irb_irq_handler(void *unused)
{
  if (irb->mis & PROTOCOL_MASK) {
    irb->icr = PROTOCOL_MASK;
    printf("%s protocol irq\n", lg_irb_get_protocol_name(lg_irb_cur_protocol));
  } else if (irb->mis & REPEAT_MASK) {
    irb->icr = REPEAT_MASK;
    printf("%s repeat irq\n", lg_irb_get_protocol_name(lg_irb_cur_protocol));
  }

  lg_irb_irq_flag = 1;
}

void lg_irb_init(int index)
{
  printf("lg_irb init\n");

  // nec
  lg_irb_init_nec(&irb_database[IRBLASTER_NEC]);

  // sirc12
  lg_irb_init_sirc(&irb_database[IRBLASTER_SI12], 0);
  // sirc15
  lg_irb_init_sirc(&irb_database[IRBLASTER_SI15], 1);
  // sirc20
  lg_irb_init_sirc(&irb_database[IRBLASTER_SI20], 2);

  // rc5
  lg_irb_init_rc(&irb_database[IRBLASTER_RC_5], 0);
  // rc6
  lg_irb_init_rc(&irb_database[IRBLASTER_RC_6], 1);

  // sanyo
  lg_irb_init_sany(&irb_database[IRBLASTER_SANY]);

  // custom
  lg_irb_init_cus(&irb_database[IRBLASTER_CUS0], index);

  interrupt_request(IRQ_IRBLASTER, irb_irq_handler, NULL);
  interrupt_active(IRQ_IRBLASTER);

  lg_irb_irq_flag = 0;
}

void lg_irb_exit(void)
{
  irb->cr = 0x00;
  interrupt_deactive(IRQ_IRBLASTER);
  lg_irb_irq_flag = 0;
  printf("lg_irb end\n");
}

/**
 * RET
 *  0: idle, 1: busy
 * ARG
 *  - prot_or_rpt
 *  0: protocol, 1: repeat
 **/
int lg_irb_status(int prot_or_rpt)
{
  int mask = 1 << prot_or_rpt;

  if ( irb->sr & mask ) {
    return 1;
  }
  return 0;
}

// transmit prototol, not repeat
void lg_irb_tx(int ptype)
{
  lg_irb_t *db = (lg_irb_t *)(&irb_database[ptype]);
  int psize_arr[] = { SIZE_PTYPE_NEC, SIZE_PTYPE_SI12, SIZE_PTYPE_SI15, SIZE_PTYPE_SI20, SIZE_PTYPE_RC_5, SIZE_PTYPE_RC_6, SIZE_PTYPE_SANY };
  int psize, i;

  if (lg_irb_status(0)) {
    printf("tx is busy now\n");
    return;
  }

  lg_irb_cur_protocol = ptype;

  irb->imsc = db->imsc;
  irb->icrd = db->icrd;
  irb->fcrd = db->fcrd;
  irb->tpr = db->tpr;
  irb->rpr = db->rpr;
  irb->rpsr = db->rpsr;
  // exclude icr, cpr, tr

  if (ptype == IRBLASTER_CUS0) {
    irb->cpr = db->cpr;
    psize = (db->cpr & CPR_PSIZE_MASK) >> CPR_PSIZE;
  } else {
    psize = psize_arr[ptype];
  }

  for ( i = 0; i < psize; i++ ) {
    irb->prot_data[i].dr = db->prot_data[i].dr;
    if (ptype == IRBLASTER_CUS0) {
      irb->prot_data[i].dr_cr = db->prot_data[i].dr_cr;
      irb->prot_data[i].dr_zero = db->prot_data[i].dr_zero;
      irb->prot_data[i].dr_one = db->prot_data[i].dr_one;
    }
  }

#if 0
  for ( i = 0; i < 2; i++ ) {
    if (ptype == IRBLASTER_CUS0) {
      irb->rpt_data[i].dr = db->rpt_data[i].dr;
      irb->rpt_data[i].dr_cr = db->rpt_data[i].dr_cr;
      irb->rpt_data[i].dr_zero = db->rpt_data[i].dr_zero;
      irb->rpt_data[i].dr_one = db->rpt_data[i].dr_one;
    }
  }
#endif

  irb->cr = db->cr;
}


#if (CONFIG_REV == REV_0E)

void lg_irb_default_setting(lg_irb_t *cur)
{
  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = 10 <- carrier16 = pclk / (12 * 10)
  cur->icrd = 0x000a;

  // fcrd = 0
  cur->fcrd = 0x0000;

  // tpr = 10
  cur->tpr = 0x000a;

  // rpr = 4167
  cur->rpr = 0x1047;

  // rpsr = 0
  cur->rpsr = 0x0000;

}
#endif

void lg_irb_init_nec(lg_irb_t *cur)
{
#if (CONFIG_REV == REV_0E)
  /* RTL SIM */
  lg_irb_default_setting(cur);
#else
  /* FPGA or ASIC */
  unsigned int carrier = 37.6 * KHZ;
  unsigned int duty = 12;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  // tpr = TPeriod * freq
  div = ((float)560 * carrier / MHZ + 0.5);
  cur->tpr = (unsigned int) div;

  // rpr = RPeriod * freq
  div = ((float)110 * carrier / KHZ + 0.5);
  cur->rpr = (unsigned int) div;

  // rpsr = 0
  cur->rpsr = 0x0000;

  printf("%s protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(IRBLASTER_NEC), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
#endif

  // address 8'b01011001
  cur->prot_data[0].dr = 0x0059;
  // ~address 8'b10100110
  cur->prot_data[1].dr = 0x00a6;
  // command 8'b00010110
  cur->prot_data[2].dr = 0x0016;

  // cr = NECX | COFF | TX | IrEn
  cur->cr = CR_PTYPE_NEC | CR_COFF_SET | CR_TX_SET | CR_IREN_SET;
}

/**
 * ARGS
 *  int index
 *   0: si12
 *   1: si15
 *   2: si20
 **/
void lg_irb_init_sirc(lg_irb_t *cur, int index)
{
  index += IRBLASTER_SI12;

#if (CONFIG_REV == REV_0E)
  lg_irb_default_setting(cur);
#else
  /* FPGA or ASIC */
  unsigned int carrier = 40 * KHZ;
  unsigned int duty = 12;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  // tpr = TPeriod * freq
  div = ((float)600 * carrier / MHZ + 0.5);
  cur->tpr = (unsigned int) div;

  // rpr = RPeriod * freq
  div = ((float)48 * carrier / KHZ + 0.5);
  cur->rpr = (unsigned int) div;

  // rpsr = 0
  cur->rpsr = 0x0000;

  printf("%s protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(index), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
#endif


  if (index == IRBLASTER_SI12) {
    // SIRC12
    // command 7'b0110010
    cur->prot_data[0].dr = 0x0013; //0x0032;
    // device 5'b01010
    cur->prot_data[1].dr = 0x0001; //0x000a;

    // cr = SI12 | TX | IrEn
    cur->cr = CR_PTYPE_SI12 | CR_TX_SET | CR_IREN_SET;
  } else if (index == IRBLASTER_SI15) {
    // SIRC15
    // command 7'b0110010
    cur->prot_data[0].dr = 0x0013; //0x0032;
    // device 8'b10101010
    cur->prot_data[1].dr = 0x0001; //0x00aa;

    // cr = SI15 | TX | IrEn
    cur->cr = CR_PTYPE_SI15 | CR_TX_SET | CR_IREN_SET;
  } else if (index == IRBLASTER_SI20) {
    // SIRC20
    // command 7'b0110010
    cur->prot_data[0].dr = 0x0013; //0x0032;
    // device 5'b01010
    cur->prot_data[1].dr = 0x0001; //0x000a;
    // extended 8'b10010110
    cur->prot_data[2].dr = 0x0096;

    // cr = SI20 | TX | IrEn
    cur->cr = CR_PTYPE_SI20 | CR_TX_SET | CR_IREN_SET;
  }
}

/**
 * ARGS
 *  int index
 *   0: rc_5
 *   1: rc_6
 **/
void lg_irb_init_rc(lg_irb_t *cur, int index)
{
  index += IRBLASTER_RC_5;

#if (CONFIG_REV == REV_0E)
  lg_irb_default_setting(cur);
#else
  /* FPGA or ASIC */
  unsigned int carrier = 36 * KHZ;
  unsigned int duty = 12;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  if (index == IRBLASTER_RC_5) {
    // tpr = TPeriod * freq
    div = ((float)889 * carrier / MHZ + 0.5);	/* 32 for 5MHz */
    cur->tpr = (unsigned int) div;

    // rpr = RPeriod * freq
    div = ((float)114 * carrier / KHZ + 0.5);
    cur->rpr = (unsigned int) div;

    // rpsr = 0
    cur->rpsr = 0x0000;

    printf("%s protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(index), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
  } else if (index == IRBLASTER_RC_6) {
    // tpr = TPeriod * freq
    div = ((float)444 * carrier / MHZ + 0.5); /* 16 for 5MHz */
    cur->tpr = (unsigned int) div;

    // rpr = RPeriod * freq
    div = ((float)108 * carrier / KHZ + 0.5);
    cur->rpr = (unsigned int) div;

    // rpsr = 0
    cur->rpsr = 0x0000;

    printf("%s protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(index), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
  }
#endif

  if (index == IRBLASTER_RC_5) {
    // RC5
    // address 5'b00101
    cur->prot_data[0].dr = 0x0005;
    // command 6'b110101
    cur->prot_data[1].dr = 0x0035;

    // cr = RC5 | TX | IrEn
    cur->cr = CR_PTYPE_RC_5 | CR_TX_SET | CR_IREN_SET;
  } else if (index == IRBLASTER_RC_6) {
    // RC6
    // mode 3'b000
    cur->prot_data[0].dr = 0x0000;
    // control 8'b00000100
    cur->prot_data[1].dr = 0x0004;
    // key 8'b00000001
    cur->prot_data[2].dr = 0x0001;

    // cr = RC6 | TX | IrEn
    cur->cr = CR_PTYPE_RC_6 | CR_TX_SET | CR_IREN_SET;
  }
}

void lg_irb_init_sany(lg_irb_t *cur)
{
#if (CONFIG_REV == REV_0E)
  lg_irb_default_setting(cur);
#else
    /* FPGA or ASIC */
  unsigned int carrier = 37.6 * KHZ;
  unsigned int duty = 12;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  // tpr = TPeriod * freq
  div = ((float)560 * carrier / MHZ + 0.5);
  cur->tpr = (unsigned int) div;

  // rpr = RPeriod * freq
  div = ((float)108 * carrier / KHZ + 0.5);
  cur->rpr = (unsigned int) div;

  // rpsr = 0
  cur->rpsr = 0x0000;

  printf("%s protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(IRBLASTER_SANY), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
#endif

  // custom_low 6'b101010
  cur->prot_data[0].dr = 0x002a;
  // custom_high 7'b1111111
  cur->prot_data[1].dr = 0x007f;
  // key 8'b00000110
  cur->prot_data[2].dr = 0x0006;

  // cr = SANY | TX | IrEn
  cur->cr = CR_PTYPE_SANY | CR_TX_SET | CR_IREN_SET;
}

void lg_irb_init_cus_nec(lg_irb_t *cur)
{
  // NEC but duty rate 1/4, with carrier
#if (CONFIG_REV == REV_0E)
  /* RTL SIM */
  lg_irb_default_setting(cur);
#else
  /* FPGA or ASIC */
  unsigned int carrier = 37.6 * KHZ;
  unsigned int duty = 16;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  // tpr = TPeriod * freq
  div = ((float)560 * carrier / MHZ + 0.5);
  cur->tpr = (unsigned int) div;

  // rpr = RPeriod * freq
  div = ((float)110 * carrier / KHZ + 0.5);
  cur->rpr = (unsigned int) div;

  // rpsr = 0
  cur->rpsr = 0x0000;

  printf("%s[NEC] protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(IRBLASTER_CUS0), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
#endif

  // dr0
  cur->prot_data[0].dr = 0x0001;
  cur->prot_data[0].dr_cr = 0x0081;
  cur->prot_data[0].dr_zero = 0x0000;
  cur->prot_data[0].dr_one = 0x0810;

  // dr1
  // address 8'b01011001

  //cur->prot_data[1].dr = 0x0059;
  cur->prot_data[1].dr = mirror_u8(((val & 0xff00) >> 8) & 0xff);

  cur->prot_data[1].dr_cr = 0x00c8;
  cur->prot_data[1].dr_zero = 0x0101;
  cur->prot_data[1].dr_one = 0x0301;


  // dr2
  // ~address 8'b10100110
  //cur->prot_data[2].dr = 0x00a6;
  cur->prot_data[2].dr = (~(db->prot_data[1].dr) ) & 0xff;
  cur->prot_data[2].dr_cr = 0x00c8;
  cur->prot_data[2].dr_zero = 0x0101;
  cur->prot_data[2].dr_one = 0x0301;

  // dr3
  // command 8'b00010110
  //cur->prot_data[3].dr = 0x0016;
  cur->prot_data[3].dr = mirror_u8(val & 0xff);
  cur->prot_data[3].dr_cr = 0x00c8;
  cur->prot_data[3].dr_zero = 0x0101;
  cur->prot_data[3].dr_one = 0x0301;

  // dr4
  // command 8'b11101001
  cur->prot_data[4].dr = (~(db->prot_data[3].dr) ) & 0xff;
  //cur->prot_data[4].dr = 0x00e9;
  cur->prot_data[4].dr_cr = 0x00c8;
  cur->prot_data[4].dr_zero = 0x0101;
  cur->prot_data[4].dr_one = 0x0301;

  // dr5
  cur->prot_data[5].dr = 0x0001;
  cur->prot_data[5].dr_cr = 0x00c1;
  cur->prot_data[5].dr_zero = 0x0101;
  cur->prot_data[5].dr_one = 0x0301;

  // cpr
  cur->cpr = (6 << CPR_PSIZE);

  // duty rate 1/4, with carrier
  // cr = CUS0 | DUTY | TX | IrEn
  cur->cr = CR_PTYPE_CUS0 | CR_DUTY_SET | CR_TX_SET | CR_IREN_SET;
}

void lg_irb_init_cus_075a(lg_irb_t *cur)
{
  // 075A
#if (CONFIG_REV == REV_0E)
  /* RTL SIM */
  lg_irb_default_setting(cur);
#else
  /* FPGA or ASIC */
  unsigned int carrier = 40 * KHZ;
  unsigned int duty = 12;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  // tpr = TPeriod * freq
  div = ((float)100 * carrier / MHZ + 0.5);
  cur->tpr = (unsigned int) div;

  // rpr = RPeriod * freq
  div = ((float)100 * carrier / KHZ + 0.5); /* do not use */
  cur->rpr = (unsigned int) div;

  // rpsr = 0
  cur->rpsr = 0x0000;

  printf("%s[075A] protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(IRBLASTER_CUS0), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
#endif

  // dr0
  cur->prot_data[0].dr = 0x0000;
  cur->prot_data[0].dr_cr = DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[0].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[0].dr_one = 0x0000;

  /* D0 '0' */
  // dr1
  // D0 first half
  cur->prot_data[1].dr = 0x0000;
  cur->prot_data[1].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[1].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[1].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr2
  // D0 second half
  cur->prot_data[2].dr = 0x0002;
  cur->prot_data[2].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[2].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[2].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  /* D1 '1' */
  // dr3
  // D1 first half
  cur->prot_data[3].dr = 0x0002;
  cur->prot_data[3].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[3].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[3].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr4
  // D1 second half
  cur->prot_data[4].dr = 0x0000;
  cur->prot_data[4].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[4].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[4].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  /* D2 '1' */
  // dr5
  // D2 first half
  cur->prot_data[5].dr = 0x0002;
  cur->prot_data[5].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[5].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[5].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr6
  // D2 second half
  cur->prot_data[6].dr = 0x0000;
  cur->prot_data[6].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[6].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[6].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  /* D3 '1' */
  // dr7
  // D3 first half
  cur->prot_data[7].dr = 0x0002;
  cur->prot_data[7].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[7].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[7].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr8
  // D3 second half
  cur->prot_data[8].dr = 0x0000;
  cur->prot_data[8].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[8].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[8].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  /* D4 '0' */
  // dr9
  // D4 first half
  cur->prot_data[9].dr = 0x0000;
  cur->prot_data[9].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[9].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[9].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr10
  // D4 second half
  cur->prot_data[10].dr = 0x0002;
  cur->prot_data[10].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[10].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[10].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  /* D5 '0' */
  // dr11
  // D5 first half
  cur->prot_data[11].dr = 0x0000;
  cur->prot_data[11].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[11].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[11].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr12
  // D5 second half
  cur->prot_data[12].dr = 0x0002;
  cur->prot_data[12].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[12].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[12].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  /* D6 '0' */
  // dr13
  // D6 first half
  cur->prot_data[13].dr = 0x0000;
  cur->prot_data[13].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 1;
  cur->prot_data[13].dr_zero = (51 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[13].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // dr14
  // D6 second half
  cur->prot_data[14].dr = 0x0002;
  cur->prot_data[14].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[14].dr_zero = (41 << DRX01_TAIL_OFFSET) | 5;
  cur->prot_data[14].dr_one = (5 << DRX01_TAIL_OFFSET) | 5;

  // cpr
  cur->cpr = (15 << CPR_PSIZE);

  // duty rate 1/3, with carrier
  // cr = CUS0 | DUTY | TX | IrEn
  cur->cr = CR_PTYPE_CUS0 | CR_TX_SET | CR_IREN_SET;
}

void lg_irb_init_cus_adb4pirb(lg_irb_t *cur)
{
  // 075A
#if (CONFIG_REV == REV_0E)
  /* RTL SIM */
  lg_irb_default_setting(cur);
#else
  /* FPGA or ASIC */
  unsigned int carrier = 57142;
  unsigned int duty = 12;
  unsigned int temp;
  unsigned int divider;
  unsigned int remainder;
  unsigned int fraction;
  unsigned int div;

  temp = duty * carrier;
  divider = PCLK / temp;
  remainder = PCLK % temp;
  temp = ((float)64*2/duty * remainder / carrier);
  fraction = (temp >> 1) + (temp & 1);

  // imsc = RPT disable | TX enable
  cur->imsc = 0x0001;

  // icrd = integer[ PCLK / ( DUTY * freq ) ]
  cur->icrd = divider;

  // fcrd = fractional[ PCLK / ( DUTY * freq ) ] * 64 + 0.5
  //cur->fcrd = (unsigned int)( (float)(div - (unsigned int)(div)) * 64 + 0.5 );
  cur->fcrd = fraction;

  // tpr = TPeriod * freq
  div = ((float)315 * carrier / MHZ + 0.5);
  cur->tpr = (unsigned int) div;

  // rpr = RPeriod * freq
  div = ((float)100 * carrier / KHZ + 0.5); /* do not use */
  cur->rpr = (unsigned int) div;

  // rpsr = 0
  cur->rpsr = 0x0000;

  printf("%s[ADB4PIRB] protocol setting ICRD=0x%08x, FCRD=0x%08x, TPR=0x%08x, RPR=0x%08x\n", lg_irb_get_protocol_name(IRBLASTER_CUS0), cur->icrd, cur->fcrd, cur->tpr, cur->rpr);
#endif

  /* Leader */
  // dr0
  cur->prot_data[0].dr = 0x0002;
  cur->prot_data[0].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | DRXCR_MSB | 2;
  cur->prot_data[0].dr_zero = (0 << DRX01_TAIL_OFFSET) | 1;
  cur->prot_data[0].dr_one = (3 << DRX01_TAIL_OFFSET) | 3;

  /* Data */
  // dr1
  // Data[7:0]
  cur->prot_data[1].dr = 0x0021;
  cur->prot_data[1].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[1].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[1].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // dr2
  // Data[15:8]
  cur->prot_data[2].dr = 0x0011;
  cur->prot_data[2].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[2].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[2].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // dr3
  // Data[23:16]
  cur->prot_data[3].dr = 0x0011;
  cur->prot_data[3].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[3].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[3].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // dr4
  // Data[31:24]
  cur->prot_data[4].dr = 0x0011;
  cur->prot_data[4].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[4].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[4].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  /* Stop */
  // dr5
  // Stop[7:0]
  cur->prot_data[5].dr = 0x0011;
  cur->prot_data[5].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[5].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[5].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // dr6
  // Stop[15:8]
  cur->prot_data[6].dr = 0x0014;
  cur->prot_data[6].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[6].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[6].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // dr7
  // Stop[23:16]
  cur->prot_data[7].dr = 0x0011;
  cur->prot_data[7].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[7].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[7].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // dr8
  // Stop[31:24]
  cur->prot_data[8].dr = 0x0024;
  cur->prot_data[8].dr_cr = DRXCR_MARKFIRSTONE | DRXCR_MARKFIRSTZERO | 8;
  cur->prot_data[8].dr_zero = (1 << DRX01_TAIL_OFFSET) | 0;
  cur->prot_data[8].dr_one = (0 << DRX01_TAIL_OFFSET) | 1;

  // cpr
  cur->cpr = (9 << CPR_PSIZE);

  // duty rate 1/3, with carrier
  // cr = CUS0 | DUTY | TX | IrEn
  cur->cr = CR_PTYPE_CUS0 | CR_TX_SET | CR_IREN_SET;
}

void lg_irb_init_cus(lg_irb_t *cur, int index)
{
  if (index == 0)		/* NEC */
    lg_irb_init_cus_nec(cur);
  else if (index == 1)		/* 075A */
    lg_irb_init_cus_075a(cur);
  else if (index == 2)		/* ADB 4PIRB */
    lg_irb_init_cus_adb4pirb(cur);
}

char *lg_irb_get_protocol_name(int ptype)
{

  switch(ptype) {
  case IRBLASTER_NEC:
    return "NEC";
    break;
  case IRBLASTER_SI12:
    return "SIRC_12";
    break;
  case IRBLASTER_SI15:
    return "SIRC_15";
    break;
  case IRBLASTER_SI20:
    return "SIRC_20";
    break;
  case IRBLASTER_RC_5:
    return "RC_5";
    break;
  case IRBLASTER_RC_6:
    return "RC_6";
    break;
  case IRBLASTER_SANY:
    return "Sanyo";
    break;
  case IRBLASTER_CUS0:
    return "Custom";
    break;
  }
  return "";

}

static irblaster_driver_t lg_irb_driver = {
  .init = lg_irb_init,
  .exit = lg_irb_exit,
  .status = lg_irb_status,
  .tx = lg_irb_tx,
};

irblaster_driver_t* get_irblaster_driver(void)
{
  return &lg_irb_driver;
}
