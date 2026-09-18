/*
 * atsc3_noti_table.h
 *
 *  Created on: 2023. 1. 13.
 *      Author: samin.ryu
 */

#ifndef _DBB_DEMOD_L1_TABLE
#define _DBB_DEMOD_L1_TABLE

/*
typedef struct {
	unsigned int offset;
	unsigned int ti_group_0;
	unsigned int ti_group_1;
	unsigned int ti_group_2;
	unsigned int ti_group_3;
} noti_ctrl_t;
//*/
//*
typedef struct {
	unsigned long long int offset:12;
	unsigned long long int ti_group_0:21;
	unsigned long long int ti_group_1:21;
	unsigned long long int ti_group_2:21;
	unsigned long long int ti_group_3:21;
} demod_a3_noti_ctrl_t;
//*/

//extern const demod_a3_noti_ctrl_t DEMOD_TABLE_A3_NOTI_WA[];
//extern const int DEMOD_TABLE_A3_NOTI_WA_NUM;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
demod_a3_noti_ctrl_t DEMOD_L1_TABLE_A3_NOTI_CTRL (UINT32 index);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
int DEMOD_L1_TABLE_Update (LX_DEMOD_L1_Context * core);
#endif
#endif /*  */
