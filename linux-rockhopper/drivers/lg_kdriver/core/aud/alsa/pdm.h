/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

#ifndef _PDM_H_
#define _PDM_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct pdm_mic_tuning_data{
    unsigned int highpass_filter_on_off;
    unsigned int highpass_filter_coeff;
    unsigned int gain_soft_mute;
    unsigned int gain_sinc_shift;
    unsigned int s_cycles;
    unsigned int pdm_data_valid_delay;
    unsigned int wov_pdm_clkout_mux_sel;
};

/*------------------------------------------------------------------------------
    Extern Function Prototype Declaration
------------------------------------------------------------------------------*/
int pdm_set_mic_tuning_data (struct pdm_mic_tuning_data *tuning_data);
int pdm_get_mic_tuning_data (struct pdm_mic_tuning_data tunign_data[]);
int pdm_set_pull_down(bool on);

/*------------------------------------------------------------------------------
    Extern Variables
------------------------------------------------------------------------------*/

#endif /* _PDM_H_ */
