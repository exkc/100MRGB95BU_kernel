/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_shp_scl256_def.h
 *
 *  driver header for picture enhance sharpness parameters. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2015.04.23
 *	@see		
 */

#ifndef	_PE_SHP_SCL256_DEF_H_
#define	_PE_SHP_SCL256_DEF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_reg.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_SCL256_CO_NUM_12T_BASE		(120000)
#define PE_SHP_SCL256_CO_NUM_12T_0002		(120002)
#define PE_SHP_SCL256_CO_NUM_12T_0003		(120003)
#define PE_SHP_SCL256_CO_NUM_12T_0004		(120004)
#define PE_SHP_SCL256_CO_NUM_12T_0006		(120006)
#define PE_SHP_SCL256_CO_NUM_12T_0110		(120110)
#define PE_SHP_SCL256_CO_NUM_12T_0204		(120204)
#define PE_SHP_SCL256_CO_NUM_12T_0202		(120202)
#define PE_SHP_SCL256_CO_NUM_12T_0304		(120304)
#define PE_SHP_SCL256_CO_NUM_12T_0306		(120306)
#define PE_SHP_SCL256_CO_NUM_12T_0404		(120404)
#define PE_SHP_SCL256_CO_NUM_12T_0406		(120406)
//#define PE_SHP_SCL256_CO_NUM_12T_0508		(120508)
#define PE_SHP_SCL256_CO_NUM_12T_0606		(120606)
//#define PE_SHP_SCL256_CO_NUM_12T_0610		(120610)
//#define PE_SHP_SCL256_CO_NUM_12T_0708		(120708)
#define PE_SHP_SCL256_CO_NUM_12T_0806		(120806)
#define PE_SHP_SCL256_CO_NUM_12T_1006		(121006)
//#define PE_SHP_SCL256_CO_NUM_12T_1210		(121210)
#define PE_SHP_SCL256_CO_NUM_12T_1410		(121410)
#define PE_SHP_SCL256_CO_NUM_12T_0104		(120104)
#define PE_SHP_SCL256_CO_NUM_12T_1010		(121010)

#define PE_SHP_SCL256_CO_NUM_1212T_BASE		(12120000)
#define PE_SHP_SCL256_CO_NUM_1212T_0006		(12120006)
#define PE_SHP_SCL256_CO_NUM_1212T_0104		(12120104)
#define PE_SHP_SCL256_CO_NUM_1212T_0306		(12120306)
#define PE_SHP_SCL256_CO_NUM_1212T_0406		(12120406)
#define PE_SHP_SCL256_CO_NUM_1212T_0606		(12120606)
#define PE_SHP_SCL256_CO_NUM_1212T_0808		(12120808)
#define PE_SHP_SCL256_CO_NUM_1212T_1006		(12121006)
#define PE_SHP_SCL256_CO_NUM_1212T_1410		(12121410)

#define PE_SHP_SCL256_CO_NUM_1204T_BASE		(12040000)
#define PE_SHP_SCL256_CO_NUM_1204T_0006		(12040006)
#define PE_SHP_SCL256_CO_NUM_1204T_0406		(12040406)
#define PE_SHP_SCL256_CO_NUM_1204T_0606		(12040606)
#define PE_SHP_SCL256_CO_NUM_1204T_0808		(12040808)

#define PE_SHP_SCL256_CO_NUM_1206T_1510		(12061510)

#define PE_SHP_SCL256_CO_NUM_1202T_BASE		(12020000)
#define PE_SHP_SCL256_CO_NUM_1202T_0006		(12020006)
#define PE_SHP_SCL256_CO_NUM_1202T_1510		(12021510)

#define PE_SHP_SCL256_CO_NUM_0808T_BASE		(8080000)
#define PE_SHP_SCL256_CO_NUM_0808T_0610		(8080610)
#define PE_SHP_SCL256_CO_NUM_0808T_1210		(8081210)

#define PE_SHP_SCL256_CO_NUM_06T_BASE		(60000)
#define PE_SHP_SCL256_CO_NUM_06T_0006		(60006)
#define PE_SHP_SCL256_CO_NUM_06T_0306		(60306)
#define PE_SHP_SCL256_CO_NUM_06T_0606		(60606)
#define PE_SHP_SCL256_CO_NUM_06T_0906		(60906)
#define PE_SHP_SCL256_CO_NUM_06T_1206		(61206)
#define PE_SHP_SCL256_CO_NUM_06T_1410		(61410)

#define PE_SHP_SCL256_CO_NUM_04T_BASE		(40000)
#define PE_SHP_SCL256_CO_NUM_04T_0007		(40007)
#define PE_SHP_SCL256_CO_NUM_04T_0107		(40107)
#define PE_SHP_SCL256_CO_NUM_04T_0307		(40307)
#define PE_SHP_SCL256_CO_NUM_04T_0607		(40607)
#define PE_SHP_SCL256_CO_NUM_04T_0807		(40807)
#define PE_SHP_SCL256_CO_NUM_04T_1007		(41007)
#define PE_SHP_SCL256_CO_NUM_04T_1407		(41407)
#define PE_SHP_SCL256_CO_NUM_04T_1410		(41410)
#define PE_SHP_SCL256_CO_NUM_04T_1514		(41514)
#define PE_SHP_SCL256_CO_NUM_04T_1515		(41515)

#define PE_SHP_SCL256_CO_NUM_08T_BASE		(80000)
#define PE_SHP_SCL256_CO_NUM_08T_0006		(80006)
#define PE_SHP_SCL256_CO_NUM_08T_0106		(80106)
#define PE_SHP_SCL256_CO_NUM_08T_0306		(80306)
#define PE_SHP_SCL256_CO_NUM_08T_0606		(80606)
#define PE_SHP_SCL256_CO_NUM_08T_0806		(80806)
#define PE_SHP_SCL256_CO_NUM_08T_1006		(81006)
#define PE_SHP_SCL256_CO_NUM_08T_1406		(81406)
#define PE_SHP_SCL256_CO_NUM_08T_1410		(81410)
#define PE_SHP_SCL256_CO_NUM_08T_1514		(81514)
#define PE_SHP_SCL256_CO_NUM_08T_1515		(81515)

#define PE_SHP_SCL256_CO_NUM_H12T_M_DFLT	PE_SHP_SCL256_CO_NUM_12T_0006
#define PE_SHP_SCL256_CO_NUM_H12T_S_DFLT	PE_SHP_SCL256_CO_NUM_12T_0610
#define PE_SHP_SCL256_CO_NUM_V06T_M_DFLT	PE_SHP_SCL256_CO_NUM_06T_0006
#define PE_SHP_SCL256_CO_NUM_V12T_M_DFLT	PE_SHP_SCL256_CO_NUM_12T_0006
#define PE_SHP_SCL256_CO_NUM_V12T_S_DFLT	PE_SHP_SCL256_CO_NUM_12T_0610
#define PE_SHP_SCL256_CO_NUM_H08T_M_DFLT	PE_SHP_SCL256_CO_NUM_08T_0006
#define PE_SHP_SCL256_CO_NUM_V08T_M_DFLT	PE_SHP_SCL256_CO_NUM_08T_0006
#define PE_SHP_SCL256_CO_NUM_V04T_M_DFLT	PE_SHP_SCL256_CO_NUM_04T_0007

#define PE_SHP_SCL256_CO_NUM_H1212T_M_DFLT	PE_SHP_SCL256_CO_NUM_1212T_0006
#define PE_SHP_SCL256_CO_NUM_H1204T_M_DFLT	PE_SHP_SCL256_CO_NUM_1204T_0006
#define PE_SHP_SCL256_CO_NUM_H0808T_S_DFLT	PE_SHP_SCL256_CO_NUM_0808T_0610



/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0002[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0003[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0004[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0110[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0204[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0202[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0304[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0404[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0406[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0806[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_1006[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_0104[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_1010[];
extern const PE_REG_PARAM_T scl_p256_12t_m_flt_1010[];
//extern const PE_REG_PARAM_T scl_p256_12t_s_flt_0508[];
//extern const PE_REG_PARAM_T scl_p256_12t_s_flt_0610[];
//extern const PE_REG_PARAM_T scl_p256_12t_s_flt_0708[];
//extern const PE_REG_PARAM_T scl_p256_12t_s_flt_1210[];

extern const PE_REG_PARAM_T scl_p256_04t_m_flt_0007[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_0107[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_0307[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_0607[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_0807[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_1007[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_1407[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_1514[];
extern const PE_REG_PARAM_T scl_p256_04t_m_flt_1515[];

//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_0006[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_0106[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_0306[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_0606[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_0806[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_1006[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_1406[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_1410[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_1514[];
//extern const PE_REG_PARAM_T scl_p256_08t_m_flt_1515[];

extern const PE_REG_PARAM_T scl_p256_12t_h_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_12t_h_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_0610[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_0806[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_1006[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_1210[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_1406[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_1514[];
extern const PE_REG_PARAM_T scl_p256_08t_f_flt_1515[];
extern const PE_REG_PARAM_T scl_p256_08t_h_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_08t_h_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_08t_h_flt_0008[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_0806[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_1006[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_1406[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_1514[];
extern const PE_REG_PARAM_T scl_p256_04t_f_flt_1515[];
extern const PE_REG_PARAM_T scl_p256_04t_h_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_04t_h_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_04t_h_flt_0308[];


extern const PE_REG_PARAM_T scl_p256_1212t_flt_0004[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0104[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0304[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0404[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0406[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0806[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_0808[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_1006[];
extern const PE_REG_PARAM_T scl_p256_1212t_flt_1410[];

extern const PE_REG_PARAM_T scl_p256_1208t_flt_0004[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_0104[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_0304[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_0806[];
extern const PE_REG_PARAM_T scl_p256_1208t_flt_1410[];

extern const PE_REG_PARAM_T scl_p256_1204t_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0008[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0308[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0406[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0808[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0910[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_1510[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_0610[];
extern const PE_REG_PARAM_T scl_p256_1204t_flt_repeat[];


extern const PE_REG_PARAM_T scl_p256_1206t_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_1206t_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_1206t_flt_1510[];
extern const PE_REG_PARAM_T scl_p256_1206t_flt_0610[];

extern const PE_REG_PARAM_T scl_p256_1202t_flt_0006[];
extern const PE_REG_PARAM_T scl_p256_1202t_flt_0308[];
extern const PE_REG_PARAM_T scl_p256_1202t_flt_1510[];

extern const PE_REG_PARAM_T scl_p256_0808t_flt_0004[];
extern const PE_REG_PARAM_T scl_p256_0808t_flt_0606[];
extern const PE_REG_PARAM_T scl_p256_0808t_flt_0610[];
extern const PE_REG_PARAM_T scl_p256_0808t_flt_1210[];

extern const PE_REG_PARAM_T scl_p256_0806t_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_0806t_flt_0610[];

extern const PE_REG_PARAM_T scl_p256_0804t_flt_0008[];
extern const PE_REG_PARAM_T scl_p256_0804t_flt_0306[];
extern const PE_REG_PARAM_T scl_p256_0804t_flt_0308[];
extern const PE_REG_PARAM_T scl_p256_0804t_flt_0910[];
extern const PE_REG_PARAM_T scl_p256_0804t_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_0804t_flt_1510[];
extern const PE_REG_PARAM_T scl_p256_0804t_flt_0610[];

extern const PE_REG_PARAM_T scl_p256_0802t_flt_0308[];

extern const PE_REG_PARAM_T scl_p256_0404t_flt_0308[];
extern const PE_REG_PARAM_T scl_p256_0404t_flt_0910[];
extern const PE_REG_PARAM_T scl_p256_0404t_flt_1410[];
extern const PE_REG_PARAM_T scl_p256_0404t_flt_1510[];
extern const PE_REG_PARAM_T scl_p256_0404t_flt_0610[];
extern const PE_REG_PARAM_T scl_p256_0404t_flt_0008[];

extern const PE_REG_PARAM_T scl_p256_0402t_flt_0308[];


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_SHP_SCL256_DEF_H_ */
