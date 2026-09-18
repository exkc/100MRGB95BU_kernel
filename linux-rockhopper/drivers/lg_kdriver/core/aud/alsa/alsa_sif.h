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


#ifndef _ALSA_SIF_KCONTROL_H_
#define _ALSA_SIF_KCONTROL_H_

void sif_set_data_drop (bool on_off);
int register_sif_kcontrols (struct snd_soc_card *card);

#endif /* _ALSA_SIF_KCONTROL_H_ */
