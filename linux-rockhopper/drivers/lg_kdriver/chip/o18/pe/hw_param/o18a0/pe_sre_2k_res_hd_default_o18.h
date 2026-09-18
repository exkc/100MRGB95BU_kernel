/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

const PE_REG_PARAM_T sre_2k_res_hd_default_o18[] =
{
    {0x9100, 0x00000000},      // SHP_DP_CTRL_00         
    {0x9110, 0x0620031B},      // SHP_FD_CTRL_00         
    {0x9114, 0x0E000404},      // SHP_FD_CTRL_01         
    {0x9118, 0x10061004},      // SHP_FD_CTRL_02         
    {0x911C, 0xFFFF1800},      // SHP_FD_CTRL_03         
    {0x9120, 0x20800400},      // SHP_FD_CTRL_04         
    {0x9124, 0x50FF1000},      // SHP_FD_CTRL_05         
    {0x9128, 0x32FF0040},      // SHP_FD_CTRL_06         
    {0x912C, 0x40800000},      // SHP_FD_CTRL_07         
    {0x9130, 0x80403000},      // SHP_FD_CTRL_08         
    {0x9134, 0x00000010},      // SHP_FD_CTRL_09         
    {0x9138, 0x00200000},      // SHP_FD_CTRL_0A         
    {0x913C, 0x40002005},      // SHP_FD_CTRL_0B         
    {0x9140, 0x06200000},      // SHP_FD_CTRL_0C         
    {0x9144, 0x22800B40},      // SHP_FD_CTRL_0D         
    {0x9148, 0xBBFF7DC4},      // SHP_FD_CTRL_0E         
    {0x914C, 0x00000003},      // SHP_FD_CTRL_0F         
    {0x9150, 0x00000820},      // SHP_FD_CTRL_10         
    {0x9154, 0xC0701002},      // SHP_FD_CTRL_11         
    {0x9158, 0x2E000800},      // SHP_FD_CTRL_12         
    {0x9160, 0x00000001},      // SHP_MP_CTRL_00         
    {0x9164, 0x14202020},      // SHP_MP_CTRL_01         
    {0x9168, 0x00008000},      // SHP_MP_CTRL_02         
    {0x916C, 0x88F00F00},      // SHP_MP_CTRL_03         
    {0x9170, 0x00601000},      // SHP_MP_CTRL_04         
    {0x9174, 0x00010401},      // SHP_MP_CTRL_05         
    {0x9178, 0x00804010},      // SHP_MP_CTRL_06         
    {0x917C, 0xC0A08050},      // SHP_MP_CTRL_07         
    {0x9180, 0x50C06020},      // SHP_MP_CTRL_08         
    {0x9184, 0x20C0A080},      // SHP_MP_CTRL_09         
    {0x9188, 0x0000C060},      // SHP_MP_CTRL_0A         
    {0x918C, 0x00000007},      // SHP_MP_CTRL_0B         
    {0x9190, 0x10101820},      // SHP_MP_CTRL_0C         
    {0x9194, 0x0000F001},      // SHP_APL_CTRL_00        
    {0x91A0, 0xFFFF4010},      // SHP_LC_CTRL_00         
    {0x91A4, 0x20204030},      // SHP_LC_CTRL_01         
    {0x91A8, 0xFF303000},      // SHP_LC_CTRL_02         
    {0x91AC, 0x00000007},      // SHP_LC_CTRL_03         
    {0x91B0, 0x04080101},      // SHP_LC_CTRL_04         
    {0x91C0, 0x1E060001},      // SHP_DER_CTRL_00        
    {0x91C4, 0x81060604},      // SHP_DER_CTRL_01        
    {0x91C8, 0x00040400},      // SHP_DER_CTRL_02        
    {0x91CC, 0x00065008},      // SHP_DER_CTRL_03        
    {0x91D0, 0x00000008},      // SHP_DER_CTRL_04        
    {0x91D4, 0x00000000},      // SHP_DER_CTRL_05        
    {0x91D8, 0x30021800},      // SHP_DER_CTRL_06        
    {0x91DC, 0x90C06006},      // SHP_DER_CTRL_07        
    {0x91E0, 0x00000001},      // SHP_SP_CTRL_00         
    {0x91E4, 0x00101010},      // SHP_SP_CTRL_01         
    {0x91E8, 0x00002800},      // SHP_SP_CTRL_02         
    {0x91EC, 0x20000000},      // SHP_SP_CTRL_03         
    {0x91F0, 0x00401000},      // SHP_SP_CTRL_04         
    {0x91F4, 0x00030201},      // SHP_SP_CTRL_05         
    {0x91F8, 0x00FF100E},      // SHP_SP_CTRL_06         
    {0x91FC, 0xC0A08050},      // SHP_SP_CTRL_07         
    {0x9200, 0x50C06020},      // SHP_SP_CTRL_08         
    {0x9204, 0x20C0A080},      // SHP_SP_CTRL_09         
    {0x9208, 0x0000C060},      // SHP_SP_CTRL_0A         
    {0x920C, 0x00000007},      // SHP_SP_CTRL_0B         
    {0x9210, 0x04100C20},      // SHP_SP_CTRL_0C         
    {0x9220, 0x00002015},      // SHP_PTI_CTRL_00        
    {0x9224, 0x00008001},      // SHP_PTI_CTRL_01        
    {0x9228, 0x00000003},      // SHP_PTI_CTRL_02        
    {0x922C, 0x18201018},      // SHP_PTI_CTRL_03        
    {0x9230, 0x00042041},      // SHP_STI_CTRL_00        
    {0x9240, 0x40000011},      // SHP_TGEN_CTRL_00       
    {0x9244, 0x04080810},      // SHP_TGEN_CTRL_01       
    {0x9248, 0x003F05FF},      // SHP_TGEN_CTRL_02       
    {0x924C, 0x000048AB},      // SHP_TGEN_CTRL_03       
    {0x9254, 0x02021F04},      // SHP_TGEN_CTRL_04       
    {0x9258, 0x001F0050},      // SHP_TGEN_CTRL_05       
    {0x925C, 0x1A000000},      // SHP_TGEN_CTRL_06       
    {0x9260, 0x1A000000},      // SHP_TGEN_CTRL_07       
    {0x9264, 0x3F801F1F},      // SHP_TGEN_CTRL_08       
    {0x9268, 0x48ABCDFF},      // SHP_TGEN_CTRL_09       
    {0x926C, 0x00000007},      // SHP_TGEN_CTRL_0A       
    {0x9270, 0x18200000},      // SHP_TGEN_CTRL_0B       
    {0x9274, 0x00000100},      // SHP_SNR_CTRL_00        
    {0x9280, 0x00000001},      // SHP_DCTP_CTRL_00       
    {0x9284, 0x0FED0F99},      // SHP_DCTP_CTRL_01       
    {0x9288, 0x025B0046},      // SHP_DCTP_CTRL_02       
    {0x928C, 0x002B0FF1},      // SHP_DCTP_CTRL_03       
    {0x9290, 0x0FDC0FE1},      // SHP_DCTP_CTRL_04       
    {0x9294, 0x0F680050},      // SHP_DCTP_CTRL_05       
    {0x9298, 0x04DD0EA8},      // SHP_DCTP_CTRL_06       
    {0x929C, 0x0FB10F17},      // SHP_DCTP_CTRL_07       
    {0x92A0, 0x0FF80002},      // SHP_DCTP_CTRL_08       
    {0x92A4, 0x0F630059},      // SHP_DCTP_CTRL_09       
    {0x92A8, 0x04FE0E92},      // SHP_DCTP_CTRL_0A       
    {0x92AC, 0x0FAE0F08},      // SHP_DCTP_CTRL_0B       
    {0x92B0, 0x0FFA0004},      // SHP_DCTP_CTRL_0C       
    {0x92B4, 0x0F580063},      // SHP_DCTP_CTRL_0D       
    {0x92B8, 0x05160E86},      // SHP_DCTP_CTRL_0E       
    {0x92BC, 0x0FA90F00},      // SHP_DCTP_CTRL_0F       
    {0x92C0, 0x0FFA0007},      // SHP_DCTP_CTRL_10       
    {0x92C4, 0x0F680050},      // SHP_DCTP_CTRL_11       
    {0x92C8, 0x04DD0EA8},      // SHP_DCTP_CTRL_12       
    {0x92CC, 0x0FB10F17},      // SHP_DCTP_CTRL_13       
    {0x92D0, 0x0FF80002},      // SHP_DCTP_CTRL_14       
    {0x92D4, 0x0FB50005},      // SHP_DCTP_CTRL_15       
    {0x92D8, 0x03940F62},      // SHP_DCTP_CTRL_16       
    {0x92DC, 0x0FD70F93},      // SHP_DCTP_CTRL_17       
    {0x92E0, 0x0FF30FF4},      // SHP_DCTP_CTRL_18       
    {0x92E4, 0x80402000},      // SHP_DCTP_CTRL_19       
    {0x92E8, 0x0000FFC4},      // SHP_DCTP_CTRL_1A       
    {0x92EC, 0x088002E0},      // SHP_DCTP_CTRL_1B       
    {0x92F0, 0x40FF18D0},      // SHP_DCTP_CTRL_1C       
    {0x92F4, 0x000000FF},      // SHP_DCTP_CTRL_1D       
    {0x92F8, 0x00000007},      // SHP_DCTP_CTRL_1E       
    {0x92FC, 0x20200000},      // SHP_DCTP_CTRL_1F       
    {0x9300, 0x00000001},      // SHP_NNTG_CTRL_00       
    {0x9304, 0x00002B38},      // SHP_NNTG_CTRL_01       
    {0x9308, 0xBDE6E338},      // SHP_NNTG_CTRL_02       
    {0x930C, 0xD9F201CB},      // SHP_NNTG_CTRL_03       
    {0x9310, 0x1598773A},      // SHP_NNTG_CTRL_04       
    {0x9314, 0x82D28A5C},      // SHP_NNTG_CTRL_05       
    {0x932C, 0x00C0608C},      // SHP_NNTG_CTRL_06       
    {0x9330, 0x0E150158},      // SHP_NNTG_CTRL_07       
    {0x9334, 0x01F20FEE},      // SHP_NNTG_CTRL_08       
    {0x9338, 0x0E11011F},      // SHP_NNTG_CTRL_09       
    {0x933C, 0x03200120},      // SHP_NNTG_CTRL_0A       
    {0x9340, 0x0A200620},      // SHP_NNTG_CTRL_0B       
    {0x9344, 0x20801080},      // SHP_NNTG_CTRL_0C       
    {0x9348, 0xC0008040},      // SHP_NNTG_CTRL_0D       
    {0x934C, 0x40200840},      // SHP_NNTG_CTRL_0E       
    {0x9350, 0x00000004},      // SHP_NNTG_CTRL_0F       
    {0x9354, 0x10180000},      // SHP_NNTG_CTRL_10       
    {0x9360, 0x00000080},      // SHP_DP_SUM_CTRL_00     
    {0x9400, 0x80100179},      // SHP_DJ_CTRL_00         
    {0x9404, 0x00800000},      // SHP_DJ_CTRL_01         
    {0x9408, 0x00000410},      // SHP_DJ_CTRL_02         
    {0x940C, 0x80100840},      // SHP_DJ_CTRL_03         
    {0x9410, 0x00000000},      // SHP_DJ_CTRL_04         
    {0x9414, 0x00000000},      // SHP_DJ_CTRL_05         
    {0x9418, 0x00000040},      // SHP_DJ_CTRL_06         
    {0x941C, 0x00155550},      // SHP_DJ_CTRL_07         
    {0x9420, 0x00000040},      // SHP_DJ_CTRL_08         
    {0x9424, 0x002AA040},      // SHP_DJ_CTRL_09         
    {0x9428, 0x002AA040},      // SHP_DJ_CTRL_0A         
    {0x942C, 0x000AA040},      // SHP_DJ_CTRL_0B         
    {0x9430, 0x000000E4},      // SHP_DJ_CTRL_0C         
    {0x9434, 0x00005540},      // SHP_DJ_CTRL_0D         
    {0x9438, 0x00205542},      // SHP_DJ_CTRL_0E         
    {0x943C, 0x00081508},      // SHP_DJ_CTRL_0F         
    {0x9440, 0x00020420},      // SHP_DJ_CTRL_10         
    {0x9444, 0x00008080},      // SHP_DJ_CTRL_11         
    {0x9448, 0x00002A00},      // SHP_DJ_CTRL_12         
    {0x944C, 0x00002A00},      // SHP_DJ_CTRL_13         
    {0x9450, 0x00000008},      // SHP_DJ_CTRL_14         
    {0x9454, 0x00002800},      // SHP_DJ_CTRL_15         
    {0x9458, 0x00050A00},      // SHP_DJ_CTRL_16         
    {0x945C, 0x00054280},      // SHP_DJ_CTRL_17         
    {0x9460, 0x000550A0},      // SHP_DJ_CTRL_18         
    {0x9464, 0x00054280},      // SHP_DJ_CTRL_19         
    {0x9468, 0x00050A00},      // SHP_DJ_CTRL_1A         
    {0x946C, 0x00002800},      // SHP_DJ_CTRL_1B         
    {0x9470, 0x00000004},      // SHP_DJ_CTRL_1C         
    {0x9474, 0x00FF0618},      // SHP_DJ_CTRL_1D         
    {0x9478, 0x00FF0414},      // SHP_DJ_CTRL_1E         
    {0x947C, 0x00FF0920},      // SHP_DJ_CTRL_1F         
    {0x9480, 0x00011400},      // SHP_DJ_CTRL_20         
    {0x9490, 0x00000000},      // SHP_DIR_BLUR_CTRL_00   
    {0x9494, 0x00FF0020},      // SHP_DIR_BLUR_CTRL_01   
};

                                                                                                                                                                                    