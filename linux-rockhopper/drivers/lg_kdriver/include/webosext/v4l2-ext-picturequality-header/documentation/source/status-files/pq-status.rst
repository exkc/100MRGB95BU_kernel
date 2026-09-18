PQ Status
=========

.. seealso::

  :doc:`/picturequality/pq`

History
-------
.. _hyeonseok8695.lee: hyeonseok8695.lee@lge.com
.. _youngin.choi: youngin.choi@lge.com

======= ========== ==================== =======
Version Date       Changed by           Comment
======= ========== ==================== =======
1.0.1   2023-09-11 `hyeonseok8695.lee`_ fix some paths
1.0.0   2019-05-30 `youngin.choi`_      Create Implementation Guide for PQ status
======= ========== ==================== =======

Overview
--------

For checking PQ driver's status, we require some items and format to describe
that information. Even chip vendor also add some values for check driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules:

1. Items should be placed CID and value

    * In case of simple integer : CID=value
      (ex: ``LED_DEMOMODE=0``)
    * In case of array : CID={value1,value2,value3,,,,,}
      (ex: ``HLG_Y_GAIN_TBL={0,1,2,3,,,,,,}``)
    * In case of struct : CID={member1:value1, member2:value2, .....}
      (ex: ``MEMC_MOTION_COMP={ type : 0, de-blur : 0, de-judder : 10}``)
    * In case of struct which include array : CID={member1:value1,
      member2:{value1 of member2, value2 of member2, ...}, ....}
      (ex: ``VPQ_GAMUT_MATRIX_POST={gamma: 0, degamma: 0, matrix:{0,1,2,3,,,,},
      mux_blend:{mux_l3d_in:1, ...., b4p_lut_x:{0,1,2,1,,,}}}``)

2. Before you print the Items, print which linuxtv-ext-header version like below:

    * ``version=linuxtv-ext-header ver.1.0.1 (submissions/21)``

3. print a chip name

    .. code-block:: bash

        example)version=linuxtv-ext-header ver.1.0.1 (submissions/21)chip_name=m16p3

3. chip_name=m16p3

Section
^^^^^^^

* File Path
  ``/proc/lgtv-driver/vpq/``

* File name
  ``pq-status``

* Contents

  ===============================	=======================================================	==================================	================================================================================
  Contents                       	relate CID                                             	Value                             	note
  ===============================	=======================================================	==================================	================================================================================
  LED_DEMOMODE                   	:c:macro:`V4L2_CID_EXT_LED_DEMOMODE`                   	refer to I/G of PQ                	eType:line/leftright/topbottom
  LED_EN                         	:c:macro:`V4L2_CID_EXT_LED_EN`                         	refer to I/G of PQ
  LED_DB_IDX                     	:c:macro:`V4L2_CID_EXT_LED_DB_IDX`                     	refer to I/G of PQ
  LED_CONTROL_SPI                	:c:macro:`V4L2_CID_EXT_LED_CONTROL_SPI`                	a current setting of spi ctrl reg.	eg. bitMask : BIT0 | BIT1 | BIT6
  MEMC_LOWDELAY_MODE             	:c:macro:`V4L2_CID_EXT_MEMC_LOWDELAY_MODE`             	refer to I/G of PQ
  MEMC_MOTION_COMP               	:c:macro:`V4L2_CID_EXT_MEMC_MOTION_COMP`               	refer to I/G of PQ                	memc_type:off/smooth/clear/user
  MEMC_MOTION_PRO                	:c:macro:`V4L2_CID_EXT_MEMC_MOTION_PRO`                	refer to I/G of PQ
  HDR_INV_GAMMA                  	:c:macro:`V4L2_CID_EXT_HDR_INV_GAMMA`                  	refer to I/G of PQ
  HDR_COLOR_CORRECTION           	:c:macro:`V4L2_CID_EXT_HDR_COLOR_CORRECTION`           	refer to I/G of PQ
  HLG_Y_GAIN_TBL                 	:c:macro:`V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL`             	refer to I/G of PQ
  DOLBY_PICTURE_MODE             	:c:macro:`V4L2_CID_EXT_DOLBY_PICTURE_MODE`             	refer to I/G of PQ                	uPictureMode:vivid/standard/cinema/cinema_bright/game
  DOLBY_PICTURE_MENU             	:c:macro:`V4L2_CID_EXT_DOLBY_PICTURE_MENU`             	refer to I/G of PQ                	eg. picture_menu : backlight/brigtness/color/contrast
  DOLBY_PWM_RATIO                	:c:macro:`V4L2_CID_EXT_DOLBY_PWM_RATIO`                	refer to I/G of PQ
  VPQ_PICTURE_CTRL               	:c:macro:`V4L2_CID_EXT_VPQ_PICTURE_CTRL`               	refer to I/G of PQ
  VPQ_BYPASS_BLOCK               	:c:macro:`V4L2_CID_EXT_VPQ_BYPASS_BLOCK`               	refer to I/G of PQ
  VPQ_BLACK_LEVEL                	:c:macro:`V4L2_CID_EXT_VPQ_BLACK_LEVEL`                	refer to I/G of PQ                	curr_input:atv/dtv/av/comp/hdmi/divx
  VPQ_LOW_DELAY_MODE             	:c:macro:`V4L2_CID_EXT_VPQ_LOW_DELAY_MODE`             	refer to I/G of PQ
  VPQ_DYNAMIC_CONTRAST_COLOR_GAIN	:c:macro:`V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN`	refer to I/G of PQ
  VPQ_TESTPATTERN                	:c:macro:`V4L2_CID_EXT_VPQ_TESTPATTERN`                	refer to I/G of PQ
  VPQ_COLORTEMP_DATA             	:c:macro:`V4L2_CID_EXT_VPQ_COLORTEMP_DATA`             	refer to I/G of PQ
  VPQ_REAL_CINEMA                	:c:macro:`V4L2_CID_EXT_VPQ_REAL_CINEMA`                	refer to I/G of PQ
  VPQ_GAMUT_MATRIX_PRE           	:c:macro:`V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE`           	refer to I/G of PQ
  VPQ_GAMUT_MATRIX_POST          	:c:macro:`V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST`          	refer to I/G of PQ
  VPQ_PQ_MODE_INFO               	:c:macro:`V4L2_CID_EXT_VPQ_PQ_MODE_INFO`               	refer to I/G of PQ                	hdrMode:sdr/dolby/hdr10/hlg/technicolor/hdrEffect colorimetry:bt601/bt709/bt2020
  ===============================	=======================================================	==================================	================================================================================

* Example

  .. code-block:: bash

    version=linuxtv-ext-header ver.1.0.1 (submissions/21)
    chip_name=m16p3
    LED_DEMOMODE={bOnOff:0, eType:line}
    LED_EN=0
    LED_DB_IDX=1
    LED_CONTROL_SPI={}
    MEMC_LOWDELAY_MODE=0
    MEMC_MOTION_COMP={memc_type:user, blur_level:0, judder_level:10}
    MEMC_MOTION_PRO=0
    HDR_INV_GAMMA=0
    HDR_COLOR_CORRECTION={uHueBlend:240, uSatBlend:512, uLgainx:{0, 5000, 10000, 15000, 20000, 25000, 30000, 65535}, ,,,,}
    EXT_HLG_Y_GAIN_TBL={0,1,2,3,,,,,,}
    DOLBY_PICTURE_MODE={bOnOff:0, uPictureMode:standard}
    DOLBY_PICTURE_MENU\={backlight:90, }
    DOLBY_PWM_RATIO=70
    VPQ_PICTURE_CTRL={sPcVal:{80, 90, 50, 50}, sContrast:512, ,,,,}
    .
    .
    .
