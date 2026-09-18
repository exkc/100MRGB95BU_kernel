ALSA ext renderer Status
============

.. note::

  For document writer, each status file must be splitted files.
  Or some new hierarchy for status files of audio(alsa).

History
-------

======= ========== ===================== =======
Version Date       Changed by            Comment
======= ========== ===================== =======
1.0.0   ...        ...                   ...
======= ========== ===================== =======

Overview
--------

For checking alsa renderer related driver's status, we require some items and format to
describe that information. Even chip vendor also add some values for
check driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules:

  #. Items should be placed key and value.

    * Key and value are classified into '='.
    * Key must comply the camel case.

  #. If some of section need many categories, you should print '[category]'
     & 'empty line' for separate that information. (See the example below)

.. code-block:: bash

  example) /proc/lgtv-driver/audio # cat sndout
  [SPK]
  Open=1
  Connect=1
  SpkOutputChannel=1
  Gain=0x800000
  Mute=0
  Delay=0
  ProcessingDelay=15
  I2SNumber=1
  Underflow=0

  [OPTIC]
  Open=0
  Connect=0
  Light=0
  OpticMode=PCM
  OutputCodec=PCM
  OutputChannel=2
  SrcCopyProtection=FREE
  OutputCopyProtection=FREE
  Gain=0x800000
  Mute=1
  Delay=0
  ProcessingDelay=0
  Underflow=0

Section
^^^^^^^

ADEC
""""

Path
''''

* /proc/lgtv-driver/audio/adec.p0
* /proc/lgtv-driver/audio/adec.p1

Contents
''''''''

================= ===================== ======================================= =======
Key               Example Values        Description                             Remarks
================= ===================== ======================================= =======
AdecPortNum       0,1,2,3 ...           Describe which port it is
Open              1,0                   Status of Open
Connect           UNKNOWN, ATP0, ...    None                                    Those values are based on :type:`adec_src_port_index_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_``.
Start             1,0                   Status of Start
UserCodec         UNKNOWN, PCM, AC3 ... What codec set on "Adec Codec" by user  Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
CurCodec          UNKNOWN, PCM, AC3 ... What codec that Adec actually decoding  Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
SrcCodec          UNKNOWN, PCM, AC3 ... Input source codec that defined by Adec Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
SrcBitrates       192                   Input source's bit rates (kb/s)
SrcSamplingRate   48                    Input source's Sampling rates (kHz)
SrcChannel        5.1                   Input source's channel number
OutputCodec       PCM                   Adec output codec                       Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
OutputChannel     2                     Adec output codec
PTS               123123124             Input source's PTS
Language          None, English, ...    Input source's language
DolbyDRCMode      LINE, RF, DRC_OFF     What user set on "Adec DolbyDRCMode"    Those values are based on :type:`adec_dolbydrc_mode_ext_type_t` in alsa-ext-adec.h
Downmix           LORO, LTRT            What user set on "Adec DownMixMode"     Those values are based on :type:`adec_downmix_mode_ext_type_t` in alsa-ext-adec.h
SyncMode          1,0                   What user set on "Adec SyncMode"        Those values are based on alsa-ext-adec.h
TrickMode         None, Pause, ...      What user set on "Adec TrickMode"       Those values are based on :type:`adec_trick_mode_ext_type_t` in alsa-ext-adec.h
Delay             15                    Delay for Adec X
Mute              1,0                   Mute for Adec X
Gain              0x800000              Gain for Adec X
AudioDescription  1,0                   Print AudioDescription On/Off Status
DefaultPRL        -2147483647           Value of DefaultPRL
Skip              0                     Skip count of lipsync module
Repeat            255                   Repeat count of lipsync module
Discontinuity     0                     Discontinuity count of lipsync module
FreeRun           0                     FreeRun count of lipsync module
Underflow         0                     Underflow count of fader
Overflow          0                     Overflow count of fader
================= ===================== ======================================= =======

Example
'''''''

.. code-block:: bash

  version=linuxtv-ext-header ver.1.0.1 (submissions/83)
  AdecPortNum=0
  Open=1
  Connect=ATP0
  Start=1
  UserCodec=AC3
  CurCodec=AC3
  SrcCodec=AC3
  SrcBitrate=256
  SrcSamplingRate=48000
  SrcChannel=2
  OutputCodec=PCM
  OutputChannel=8
  PTS=4294967295
  Language=0
  DolbyDRCMode=LINE
  DownmixMode=LTRT
  SyncMode=1
  TrickMode=NONE
  DualmonoMode=LR
  Gain=0x81DAFA
  Mute=0
  Delay=0
  AudioDescription=0
  EaseGain=0
  EaseDuration=0
  DefaultPRL=-2147483647
  Skip=0
  Repeat=255
  Discontinuity=0
  FreeRun=0
  Underflow=0
  Overflow=0

SNDOUT
""""""

Path
''''

* /proc/lgtv-driver/audio/sndout

Contents
''''''''

* SPK

================= ===================== =================================================================================================================================== =========
Key               Example Values        Description                                                                                                                         Remarks
================= ===================== =================================================================================================================================== =========
Open              1,0                   Status of Open
Connect           1,0                   Status of Connect
SpkOutputChannel  2                     What user set for spk output channel number
OutputCodec       UNKNOWN, PCM, AC3 ... Output Codec's for audio data through this sndout                                                                                   Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
Gain              0x800000              Gain for this sndout
Mute              1,0                   Mute for this sndout
Delay             15                    Delay for this sndout
ProcessingDelay   10                    Calculated total (input + output + driver internal) delay by driver                                                                 input will be selected by MainAudioOutput value output is SPK
I2SNumber         1                     Output channel(1=2ch, 2=4ch)
Underflow         0                     This value will be increased if this sndout can't output because there is no data or do not act.
SE_Index          0, 10, 20, ..., 0xFF  This value would be set if this sound output is connected to speicific Sound Engine Index (`lgse_index_ouptut_t`)                   0xFF means default and there is no sound engine connected
================= ===================== =================================================================================================================================== =========

* OPTIC

==================== ===================== =================================================================================================== =======
Key                  Example Values        Description                                                                                         Remarks
==================== ===================== =================================================================================================== =======
Open                 1,0                   Status of Open
Connect              1,0                   Status of Connect
Light                1,0                   Status of optic light
OpticMode            NONE, PCM, ...        What use set for "Sndout Spdif OutputType" optic                                                    Those values are based on alsa-ext-sndout.h
OutputCodec          UNKNOWN, PCM, AC3 ... Output Codec's for audio data through the optic                                                     Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``. If it's pass-through, use "Pass-Through"
OutputChannel        2                     Output audio data's channel number.                                                                 If it's pass-through, use "Pass-Through"
SrcCopyProtection    UNKNOWN, ...          Input's copy protection Info                                                                        Those values are based on alsa-ext-sndout.h
OutputCopyProtection UNKNOWN, FREE, ...    Output's copy protection Info                                                                       Those values are based on alsa-ext-sndout.h
Gain                 0x800000              Gain for this sndout
Mute                 1,0                   Mute for this sndout
Delay                15                    Delay for this sndout
ProcessingDelay      10                    Calculated total (input + output + driver internal) delay by driver                                 input will be selected by MainAudioOutput value output is OPTIC
Underflow            0                     This value will be increased if this sndout can't output because there is no data or do not act.
==================== ===================== =================================================================================================== =======

* OPTIC_LG

==================== ===================== =================================================================================================== =======
Key                  Example Values        Description                                                                                         Remarks
==================== ===================== =================================================================================================== =======
Open                 1,0                   Status of Open
Connect              1,0                   Status of Connect
Light                1,0                   Status of optic light
OpticMode            NONE, PCM, ...        What use set for "Sndout Spdif OutputType" optic                                                    Those values are based on alsa-ext-sndout.h
OutputCodec          UNKNOWN, PCM, AC3 ... Output Codec's for audio data through the optic                                                     Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``. If it's pass-through, use "Pass-Through"
OutputChannel        2                     Output audio data's channel number.                                                                 If it's pass-through, use "Pass-Through"
SrcCopyProtection    UNKNOWN, ...          Input's copy protection Info                                                                        Those values are based on alsa-ext-sndout.h
OutputCopyProtection UNKNOWN, FREE, ...    Output's copy protection Info                                                                       Those values are based on alsa-ext-sndout.h
SoundBarID           0xF048A6, ...         What driver set for send optic command
SoundBarVolume       10                    What driver set for send optic command
SoundBarMute         1,0                   What driver set for send optic command
SoundBarPower        1,0                   What driver set for send optic command
Gain                 0x800000              Gain for this sndout
Mute                 1,0                   Mute for this sndout
Delay                15                    Delay for this sndout
ProcessingDelay      10                    Calculated total (input + output + driver internal) delay by driver                                 input will be selected by MainAudioOutput value output is OPTIC_LG
Underflow            0                     This value will be increased if this sndout can't output because there is no data or do not act.
==================== ===================== =================================================================================================== =======

* ARC

==================== ===================== =================================================================================================== =======
Key                  Example Values        Description                                                                                         Remarks
==================== ===================== =================================================================================================== =======
Open                 1,0                   Status of Open
Connect              1,0                   Status of Connect
ArcOnOff             1,0                   Status of ARC on/off
ArcMode              NONE, PCM, ...        What use set for "Sndout Spdif OutputType" arc                                                      Those values are based on alsa-ext-sndout.h
OutputCodec          UNKNOWN, PCM, AC3 ... Output Codec's for audio data through the optic                                                     Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``. If it's pass-through, use "Pass-Through"
OutputChannel        2                     Output audio data's channel number.                                                                 If it's pass-through, use "Pass-Through"
SrcCopyProtection    UNKNOWN, ...          Input's copy protection Info                                                                        Those values are based on alsa-ext-sndout.h
OutputCopyProtection UNKNOWN, FREE, ...    Output's copy protection Info                                                                       Those values are based on alsa-ext-sndout.h
Gain                 0x800000              Gain for this sndout
Mute                 1,0                   Mute for this sndout
Delay                15                    Delay for this sndout
ProcessingDelay      10                    Calculated total (input + output + driver internal) delay by driver                                 input will be selected by MainAudioOutput value output is ARC
Underflow            0                     This value will be increased if this sndout can't output because there is no data or do not act.
==================== ===================== =================================================================================================== =======

* EARC

==================== ===================== =================================================================================================== =======
Key                  Example Values        Description                                                                                         Remarks
==================== ===================== =================================================================================================== =======
EArcOnOff            On, Off               Status of EARC
SetType              2                     Type among the values set to :c:macro:`SNDOUT_EARC_OUTPUT_TYPE`                                     Those values are based on :type:`sndout_earc_output_set_type_t` in alsa-ext-sndout.h.
CodecType            1                     Codec among the values set to :c:macro:`SNDOUT_EARC_OUTPUT_TYPE`                                    Those values are based on :type:`sndout_earc_output_codec_type_t` in alsa-ext-sndout.h.
ChannelNum           0                     Channel number among the values set to :c:macro:`SNDOUT_EARC_OUTPUT_TYPE`                           Those values are based on :type:`sndout_earc_output_channel_num_t` in alsa-ext-sndout.h.
OutputCodec          UNKNOWN, PCM, AC3 ... Output Codec's for audio data through this sndout                                                   Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
SampleRate           0                     Sample rate among the values set to :c:macro:`SNDOUT_EARC_OUTPUT_TYPE`                              Those values are based on :type:`sndout_earc_output_sample_rate_t` in alsa-ext-sndout.h.
MixOption            1                     Mix option among the values set to :c:macro:`SNDOUT_EARC_OUTPUT_TYPE`                               Those values are based on :type:`sndout_earc_output_mix_option_t` in alsa-ext-sndout.h.
Underflow            0                     This value will be increased if this sndout can't output because there is no data or do not act.
==================== ===================== =================================================================================================== =======

* BLUETOOTH, HP, WISA, SE_BT, SE_BT_SUR, COMMON_CAPTURE, SE_ARC

==================== ===================== ===================================================================================================================== =======
Key                  Example Values        Description                                                                                                           Remarks
==================== ===================== ===================================================================================================================== =======
Open                 1,0                   Status of Open
Connect              1,0                   Status of Connect
Gain                 0x800000              Gain for this sndout
Mute                 1,0                   Mute for this sndout
OutputCodec          UNKNOWN, PCM, AC3 ... Output Codec's for audio data through this sndout                                                                     Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
Delay                NA                    BT, WISA, SE_BT's delay is NA
ProcessingDelay      10                    Calculated total (input + output + driver internal) delay by driver                                                   input will be selected by MainAudioOutput value output is ARC
Underflow            0                     This value will be increased if this sndout can't output because there is no data or do not act.
SE_Index             0, 10, 20, ..., 0xFF     This value would be set if this sound output is connected to speicific Sound Engine Index (`lgse_index_ouptut_t`)  0xFF means default and there is no sound engine connected
==================== ===================== ===================================================================================================================== =======


* Misc

==================== ===================== ==================================================================================================== =======
Key                  Example Values        Description                                                                                          Remarks
==================== ===================== ==================================================================================================== =======
ConnectedAdec        0,1, ...              Connected adec port
ConnectedAmixer      0,1,2, ...            Connected audio mixer device
MainAudioOutput      ADEC0                 What user set for mainAudioOutput      Those values are based on alsa-ext-sndout.h
Underflow            0                     This value will be increased if this sndout can't output because there is no data or do not act.
==================== ===================== ==================================================================================================== =======

Example
'''''''

.. code-block:: bash

  [SPK]
  Open=1
  Connect=1
  SpkOutputChannel=1
  Gain=0x800000
  Mute=0
  Delay=0
  ProcessingDelay=15
  I2SNumber=1
  Underflow=0
  SE_Index=10

  [OPTIC]
  Open=0
  Connect=0
  Light=0
  OpticMode=PCM
  OutputCodec=PCM
  OutputChannel=2
  SrcCopyProtection=FREE
  OutputCopyProtection=FREE
  Gain=0x800000
  Mute=1
  Delay=0
  ProcessingDelay=0
  Underflow=0

  [OPTIC_LG]
  Open=0
  Connect=0
  Light=0
  OutputCodec=PCM
  OutputChannel=2
  SrcCopyProtection=FREE
  OutputCopyProtection=FREE
  SoundBarID=0xF048A6
  SoundBarVolume=0
  SoundBarMute=0
  SoundBarPower=0
  Gain=0x800000
  Mute=1
  Delay=0
  ProcessingDelay=0
  Underflow=0

  [ARC]
  Open=0
  Connect=0
  ArcOnOff=0
  ArcMode=PCM
  OutputCodec=PCM
  OutputChannel=2
  SrcCopyProtection=FREE
  OutputCopyProtection=FREE
  Gain=0x800000
  Mute=1
  Delay=0
  ProcessingDelay=0
  Underflow=0

  [EARC]
  EArcOnOff=Off
  SetType=2
  CodecType=1
  ChannelNum=0
  SampleRate=0
  MixOption=1
  Underflow=0

  [BLUETOOTH]
  Open=0
  Connect=0
  Gain=0x800000
  Mute=1
  Delay=NA
  ProcessingDelay=0

  [HP]
  Open=0
  Connect=0
  Gain=0x800000
  Mute=1
  Delay=0
  ProcessingDelay=0
  Underflow=0

  [WISA]
  Open=0
  Connect=0
  OutputChannel=0
  Gain=0x800000
  Mute=1
  Delay=NA
  ProcessingDelay=0

  [SE_BT]
  Open=0
  Connect=0
  Gain=0x800000
  Mute=1
  Delay=NA
  ProcessingDelay=0
  SE_Index=0xFF

  [SE_BT_SUR]
  Open=0
  Connect=0
  Gain=0x800000
  Mute=1
  Delay=NA
  ProcessingDelay=0
  SE_Index=0x20

  [COMMON_CAPTURE]
  Open=0
  Connect=0
  Gain=0x800000
  Mute=1
  Delay=NA
  ProcessingDelay=0

  [SE_ARC]
  Open=0
  Connect=0
  ArcOnOff=0
  ArcMode=PCM
  OutputCopyProtection=FREE
  Gain=0x800000
  Mute=1
  Delay=NA
  ProcessingDelay=0
  SE_Index=0xFF

  [Misc]
  ConnectedAdec=1
  ConnectedAmixer=5,6,7
  MainAudioOutput=ADEC1
  Underflow=3
