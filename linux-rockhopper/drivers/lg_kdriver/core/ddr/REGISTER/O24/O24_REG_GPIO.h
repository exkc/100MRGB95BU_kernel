#ifndef _REG_GPIO_h
#define _REG_GPIO_h
//Header File for GPIO in \O24\O24_DRAM_MCU_Register_Manual.xls

#define REG_GPIO_GPIODATA                                                      (APB_GPIO_BASE+0x0000)
#define REG_GPIO_GPIODIR                                                       (APB_GPIO_BASE+0x0400)
#define REG_GPIO_GPIOIS                                                        (APB_GPIO_BASE+0x0404)
#define REG_GPIO_GPIOIBE                                                       (APB_GPIO_BASE+0x0408)
#define REG_GPIO_GPIOIEV                                                       (APB_GPIO_BASE+0x040C)
#define REG_GPIO_GPIOIE                                                        (APB_GPIO_BASE+0x0410)
#define REG_GPIO_GPIORIS                                                       (APB_GPIO_BASE+0x0414)
#define REG_GPIO_GPIOMIS                                                       (APB_GPIO_BASE+0x0418)
#define REG_GPIO_GPIOIC                                                        (APB_GPIO_BASE+0x041C)
#define REG_GPIO_GPIOAFSEL                                                     (APB_GPIO_BASE+0x0420)

typedef union {
	UINT32 udata32;
	struct {						//0xF0002000 RW
	UINT32 gpio_data                        :8;	//7:0	//Input data / Output data
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIODATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002400 RW
	UINT32 gpio_dir                         :8;	//7:0	//Bits set, pins output	Bits cleared, pins output
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIODIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002404 RW
	UINT32 gpio_is                          :8;	//7:0	//Bits clear, edge on corresponding pin is detected	Bits set, level on corresponding pin is detected
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOIS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002408 RW
	UINT32 gpio_be                          :8;	//7:0	//Bits set, both edges on corresponding pin trigger an interrupt.	Bits cleared, interrupt generation event is controlled by GPIOIEV.	Single edge, determined by corresponding bit in GPIOIEV register.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOIBE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000240C RW
	UINT32 gpio_iev                         :8;	//7:0	//Bits set, rising edges, or high levels on corresponding pins trigger interrupts.	Bits cleared, falli ng edges, or low levels on corresponding pin trigger interrupts.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOIEV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002410 RW
	UINT32 gpio_ie                          :8;	//7:0	//Bits set, corresponding pin is not masked.	Bits cleared, corresponding pin interrupt is masked.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOIE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002414 RO
	UINT32 gpio_ris                         :8;	//7:0	//Reflect the status of interrupts trigger conditions detection on pins (raw, prio r to masking). Bits set, requirements met by co rresponding pins.	Bits clear, requirements not met.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIORIS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002418 RO
	UINT32 gpio_mis                         :8;	//7:0	//Masked value of interrupt due to corresponding pin. 	Bits clear, GPIO line interrupt not active. 	Bits set, GPIO line asserting interrupt.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOMIS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF000241C RW
	UINT32 gpio_ic                          :8;	//7:0	//Bit written as 1, clears edge detection logic.	Bit written as 0, has no effect.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOIC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xF0002420 RW
	UINT32 gpio_afsel                       :8;	//7:0	//Bit set, enables hardware control mode.	Bit cleared, enables software control mode.
	UINT32 resvd                            :24; 
	};
}REG_GPIO_GPIOAFSEL_T;

typedef struct {
	REG_GPIO_GPIODATA_T                                        gpiodata;	//0xF0002000
	UINT32                                                    reserved0;	//0xF0002004
	UINT32                                                    reserved1;	//0xF0002008
	UINT32                                                    reserved2;	//0xF000200C
	UINT32                                                    reserved3;	//0xF0002010
	UINT32                                                    reserved4;	//0xF0002014
	UINT32                                                    reserved5;	//0xF0002018
	UINT32                                                    reserved6;	//0xF000201C
	UINT32                                                    reserved7;	//0xF0002020
	UINT32                                                    reserved8;	//0xF0002024
	UINT32                                                    reserved9;	//0xF0002028
	UINT32                                                   reserved10;	//0xF000202C
	UINT32                                                   reserved11;	//0xF0002030
	UINT32                                                   reserved12;	//0xF0002034
	UINT32                                                   reserved13;	//0xF0002038
	UINT32                                                   reserved14;	//0xF000203C
	UINT32                                                   reserved15;	//0xF0002040
	UINT32                                                   reserved16;	//0xF0002044
	UINT32                                                   reserved17;	//0xF0002048
	UINT32                                                   reserved18;	//0xF000204C
	UINT32                                                   reserved19;	//0xF0002050
	UINT32                                                   reserved20;	//0xF0002054
	UINT32                                                   reserved21;	//0xF0002058
	UINT32                                                   reserved22;	//0xF000205C
	UINT32                                                   reserved23;	//0xF0002060
	UINT32                                                   reserved24;	//0xF0002064
	UINT32                                                   reserved25;	//0xF0002068
	UINT32                                                   reserved26;	//0xF000206C
	UINT32                                                   reserved27;	//0xF0002070
	UINT32                                                   reserved28;	//0xF0002074
	UINT32                                                   reserved29;	//0xF0002078
	UINT32                                                   reserved30;	//0xF000207C
	UINT32                                                   reserved31;	//0xF0002080
	UINT32                                                   reserved32;	//0xF0002084
	UINT32                                                   reserved33;	//0xF0002088
	UINT32                                                   reserved34;	//0xF000208C
	UINT32                                                   reserved35;	//0xF0002090
	UINT32                                                   reserved36;	//0xF0002094
	UINT32                                                   reserved37;	//0xF0002098
	UINT32                                                   reserved38;	//0xF000209C
	UINT32                                                   reserved39;	//0xF00020A0
	UINT32                                                   reserved40;	//0xF00020A4
	UINT32                                                   reserved41;	//0xF00020A8
	UINT32                                                   reserved42;	//0xF00020AC
	UINT32                                                   reserved43;	//0xF00020B0
	UINT32                                                   reserved44;	//0xF00020B4
	UINT32                                                   reserved45;	//0xF00020B8
	UINT32                                                   reserved46;	//0xF00020BC
	UINT32                                                   reserved47;	//0xF00020C0
	UINT32                                                   reserved48;	//0xF00020C4
	UINT32                                                   reserved49;	//0xF00020C8
	UINT32                                                   reserved50;	//0xF00020CC
	UINT32                                                   reserved51;	//0xF00020D0
	UINT32                                                   reserved52;	//0xF00020D4
	UINT32                                                   reserved53;	//0xF00020D8
	UINT32                                                   reserved54;	//0xF00020DC
	UINT32                                                   reserved55;	//0xF00020E0
	UINT32                                                   reserved56;	//0xF00020E4
	UINT32                                                   reserved57;	//0xF00020E8
	UINT32                                                   reserved58;	//0xF00020EC
	UINT32                                                   reserved59;	//0xF00020F0
	UINT32                                                   reserved60;	//0xF00020F4
	UINT32                                                   reserved61;	//0xF00020F8
	UINT32                                                   reserved62;	//0xF00020FC
	UINT32                                                   reserved63;	//0xF0002100
	UINT32                                                   reserved64;	//0xF0002104
	UINT32                                                   reserved65;	//0xF0002108
	UINT32                                                   reserved66;	//0xF000210C
	UINT32                                                   reserved67;	//0xF0002110
	UINT32                                                   reserved68;	//0xF0002114
	UINT32                                                   reserved69;	//0xF0002118
	UINT32                                                   reserved70;	//0xF000211C
	UINT32                                                   reserved71;	//0xF0002120
	UINT32                                                   reserved72;	//0xF0002124
	UINT32                                                   reserved73;	//0xF0002128
	UINT32                                                   reserved74;	//0xF000212C
	UINT32                                                   reserved75;	//0xF0002130
	UINT32                                                   reserved76;	//0xF0002134
	UINT32                                                   reserved77;	//0xF0002138
	UINT32                                                   reserved78;	//0xF000213C
	UINT32                                                   reserved79;	//0xF0002140
	UINT32                                                   reserved80;	//0xF0002144
	UINT32                                                   reserved81;	//0xF0002148
	UINT32                                                   reserved82;	//0xF000214C
	UINT32                                                   reserved83;	//0xF0002150
	UINT32                                                   reserved84;	//0xF0002154
	UINT32                                                   reserved85;	//0xF0002158
	UINT32                                                   reserved86;	//0xF000215C
	UINT32                                                   reserved87;	//0xF0002160
	UINT32                                                   reserved88;	//0xF0002164
	UINT32                                                   reserved89;	//0xF0002168
	UINT32                                                   reserved90;	//0xF000216C
	UINT32                                                   reserved91;	//0xF0002170
	UINT32                                                   reserved92;	//0xF0002174
	UINT32                                                   reserved93;	//0xF0002178
	UINT32                                                   reserved94;	//0xF000217C
	UINT32                                                   reserved95;	//0xF0002180
	UINT32                                                   reserved96;	//0xF0002184
	UINT32                                                   reserved97;	//0xF0002188
	UINT32                                                   reserved98;	//0xF000218C
	UINT32                                                   reserved99;	//0xF0002190
	UINT32                                                  reserved100;	//0xF0002194
	UINT32                                                  reserved101;	//0xF0002198
	UINT32                                                  reserved102;	//0xF000219C
	UINT32                                                  reserved103;	//0xF00021A0
	UINT32                                                  reserved104;	//0xF00021A4
	UINT32                                                  reserved105;	//0xF00021A8
	UINT32                                                  reserved106;	//0xF00021AC
	UINT32                                                  reserved107;	//0xF00021B0
	UINT32                                                  reserved108;	//0xF00021B4
	UINT32                                                  reserved109;	//0xF00021B8
	UINT32                                                  reserved110;	//0xF00021BC
	UINT32                                                  reserved111;	//0xF00021C0
	UINT32                                                  reserved112;	//0xF00021C4
	UINT32                                                  reserved113;	//0xF00021C8
	UINT32                                                  reserved114;	//0xF00021CC
	UINT32                                                  reserved115;	//0xF00021D0
	UINT32                                                  reserved116;	//0xF00021D4
	UINT32                                                  reserved117;	//0xF00021D8
	UINT32                                                  reserved118;	//0xF00021DC
	UINT32                                                  reserved119;	//0xF00021E0
	UINT32                                                  reserved120;	//0xF00021E4
	UINT32                                                  reserved121;	//0xF00021E8
	UINT32                                                  reserved122;	//0xF00021EC
	UINT32                                                  reserved123;	//0xF00021F0
	UINT32                                                  reserved124;	//0xF00021F4
	UINT32                                                  reserved125;	//0xF00021F8
	UINT32                                                  reserved126;	//0xF00021FC
	UINT32                                                  reserved127;	//0xF0002200
	UINT32                                                  reserved128;	//0xF0002204
	UINT32                                                  reserved129;	//0xF0002208
	UINT32                                                  reserved130;	//0xF000220C
	UINT32                                                  reserved131;	//0xF0002210
	UINT32                                                  reserved132;	//0xF0002214
	UINT32                                                  reserved133;	//0xF0002218
	UINT32                                                  reserved134;	//0xF000221C
	UINT32                                                  reserved135;	//0xF0002220
	UINT32                                                  reserved136;	//0xF0002224
	UINT32                                                  reserved137;	//0xF0002228
	UINT32                                                  reserved138;	//0xF000222C
	UINT32                                                  reserved139;	//0xF0002230
	UINT32                                                  reserved140;	//0xF0002234
	UINT32                                                  reserved141;	//0xF0002238
	UINT32                                                  reserved142;	//0xF000223C
	UINT32                                                  reserved143;	//0xF0002240
	UINT32                                                  reserved144;	//0xF0002244
	UINT32                                                  reserved145;	//0xF0002248
	UINT32                                                  reserved146;	//0xF000224C
	UINT32                                                  reserved147;	//0xF0002250
	UINT32                                                  reserved148;	//0xF0002254
	UINT32                                                  reserved149;	//0xF0002258
	UINT32                                                  reserved150;	//0xF000225C
	UINT32                                                  reserved151;	//0xF0002260
	UINT32                                                  reserved152;	//0xF0002264
	UINT32                                                  reserved153;	//0xF0002268
	UINT32                                                  reserved154;	//0xF000226C
	UINT32                                                  reserved155;	//0xF0002270
	UINT32                                                  reserved156;	//0xF0002274
	UINT32                                                  reserved157;	//0xF0002278
	UINT32                                                  reserved158;	//0xF000227C
	UINT32                                                  reserved159;	//0xF0002280
	UINT32                                                  reserved160;	//0xF0002284
	UINT32                                                  reserved161;	//0xF0002288
	UINT32                                                  reserved162;	//0xF000228C
	UINT32                                                  reserved163;	//0xF0002290
	UINT32                                                  reserved164;	//0xF0002294
	UINT32                                                  reserved165;	//0xF0002298
	UINT32                                                  reserved166;	//0xF000229C
	UINT32                                                  reserved167;	//0xF00022A0
	UINT32                                                  reserved168;	//0xF00022A4
	UINT32                                                  reserved169;	//0xF00022A8
	UINT32                                                  reserved170;	//0xF00022AC
	UINT32                                                  reserved171;	//0xF00022B0
	UINT32                                                  reserved172;	//0xF00022B4
	UINT32                                                  reserved173;	//0xF00022B8
	UINT32                                                  reserved174;	//0xF00022BC
	UINT32                                                  reserved175;	//0xF00022C0
	UINT32                                                  reserved176;	//0xF00022C4
	UINT32                                                  reserved177;	//0xF00022C8
	UINT32                                                  reserved178;	//0xF00022CC
	UINT32                                                  reserved179;	//0xF00022D0
	UINT32                                                  reserved180;	//0xF00022D4
	UINT32                                                  reserved181;	//0xF00022D8
	UINT32                                                  reserved182;	//0xF00022DC
	UINT32                                                  reserved183;	//0xF00022E0
	UINT32                                                  reserved184;	//0xF00022E4
	UINT32                                                  reserved185;	//0xF00022E8
	UINT32                                                  reserved186;	//0xF00022EC
	UINT32                                                  reserved187;	//0xF00022F0
	UINT32                                                  reserved188;	//0xF00022F4
	UINT32                                                  reserved189;	//0xF00022F8
	UINT32                                                  reserved190;	//0xF00022FC
	UINT32                                                  reserved191;	//0xF0002300
	UINT32                                                  reserved192;	//0xF0002304
	UINT32                                                  reserved193;	//0xF0002308
	UINT32                                                  reserved194;	//0xF000230C
	UINT32                                                  reserved195;	//0xF0002310
	UINT32                                                  reserved196;	//0xF0002314
	UINT32                                                  reserved197;	//0xF0002318
	UINT32                                                  reserved198;	//0xF000231C
	UINT32                                                  reserved199;	//0xF0002320
	UINT32                                                  reserved200;	//0xF0002324
	UINT32                                                  reserved201;	//0xF0002328
	UINT32                                                  reserved202;	//0xF000232C
	UINT32                                                  reserved203;	//0xF0002330
	UINT32                                                  reserved204;	//0xF0002334
	UINT32                                                  reserved205;	//0xF0002338
	UINT32                                                  reserved206;	//0xF000233C
	UINT32                                                  reserved207;	//0xF0002340
	UINT32                                                  reserved208;	//0xF0002344
	UINT32                                                  reserved209;	//0xF0002348
	UINT32                                                  reserved210;	//0xF000234C
	UINT32                                                  reserved211;	//0xF0002350
	UINT32                                                  reserved212;	//0xF0002354
	UINT32                                                  reserved213;	//0xF0002358
	UINT32                                                  reserved214;	//0xF000235C
	UINT32                                                  reserved215;	//0xF0002360
	UINT32                                                  reserved216;	//0xF0002364
	UINT32                                                  reserved217;	//0xF0002368
	UINT32                                                  reserved218;	//0xF000236C
	UINT32                                                  reserved219;	//0xF0002370
	UINT32                                                  reserved220;	//0xF0002374
	UINT32                                                  reserved221;	//0xF0002378
	UINT32                                                  reserved222;	//0xF000237C
	UINT32                                                  reserved223;	//0xF0002380
	UINT32                                                  reserved224;	//0xF0002384
	UINT32                                                  reserved225;	//0xF0002388
	UINT32                                                  reserved226;	//0xF000238C
	UINT32                                                  reserved227;	//0xF0002390
	UINT32                                                  reserved228;	//0xF0002394
	UINT32                                                  reserved229;	//0xF0002398
	UINT32                                                  reserved230;	//0xF000239C
	UINT32                                                  reserved231;	//0xF00023A0
	UINT32                                                  reserved232;	//0xF00023A4
	UINT32                                                  reserved233;	//0xF00023A8
	UINT32                                                  reserved234;	//0xF00023AC
	UINT32                                                  reserved235;	//0xF00023B0
	UINT32                                                  reserved236;	//0xF00023B4
	UINT32                                                  reserved237;	//0xF00023B8
	UINT32                                                  reserved238;	//0xF00023BC
	UINT32                                                  reserved239;	//0xF00023C0
	UINT32                                                  reserved240;	//0xF00023C4
	UINT32                                                  reserved241;	//0xF00023C8
	UINT32                                                  reserved242;	//0xF00023CC
	UINT32                                                  reserved243;	//0xF00023D0
	UINT32                                                  reserved244;	//0xF00023D4
	UINT32                                                  reserved245;	//0xF00023D8
	UINT32                                                  reserved246;	//0xF00023DC
	UINT32                                                  reserved247;	//0xF00023E0
	UINT32                                                  reserved248;	//0xF00023E4
	UINT32                                                  reserved249;	//0xF00023E8
	UINT32                                                  reserved250;	//0xF00023EC
	UINT32                                                  reserved251;	//0xF00023F0
	UINT32                                                  reserved252;	//0xF00023F4
	UINT32                                                  reserved253;	//0xF00023F8
	UINT32                                                  reserved254;	//0xF00023FC
	REG_GPIO_GPIODIR_T                                          gpiodir;	//0xF0002400
	REG_GPIO_GPIOIS_T                                            gpiois;	//0xF0002404
	REG_GPIO_GPIOIBE_T                                          gpioibe;	//0xF0002408
	REG_GPIO_GPIOIEV_T                                          gpioiev;	//0xF000240C
	REG_GPIO_GPIOIE_T                                            gpioie;	//0xF0002410
	REG_GPIO_GPIORIS_T                                          gpioris;	//0xF0002414
	REG_GPIO_GPIOMIS_T                                          gpiomis;	//0xF0002418
	REG_GPIO_GPIOIC_T                                            gpioic;	//0xF000241C
	REG_GPIO_GPIOAFSEL_T                                      gpioafsel;	//0xF0002420
}REG_GPIO_T;

extern volatile REG_GPIO_T*                        gpREG_GPIO;
     
#endif
