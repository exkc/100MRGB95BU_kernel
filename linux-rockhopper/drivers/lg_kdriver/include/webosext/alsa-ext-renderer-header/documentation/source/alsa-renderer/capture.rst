Capture
=======


Introduction
------------

| This document describes the Capture driver in the kernel space. The document gives an overview of the Capture driver and provides details about its functionalities and implementation requirements.


Revision History
^^^^^^^^^^^^^^^^

======= ========== ====================== =======
Version Date       Changed by             Comment
======= ========== ====================== =======
1.0.8   2024-05-25 kwangshik.kim@lge.com  Add new capture path with alsa device for DAFC
1.0.7   2024-05-20 myoenggyu.choe@lge.com Update sampling rate for LE Audio
1.0.6   2024-04-19 kwangshik.kim@lge.com  Refine description
1.0.5   2023-11-15 kwonwoo.kang@lge.com   Applied new document template
1.0.4   2022-09-30 kwangshik.kim@lge.com  Add description about ALSA in overall description
1.0.3   2021-03-04 kwangshik.kim@lge.com  Update about COMMON_BT_SUR
1.0.2   2019-04-30 kenneth0.park@lge.com  Add More Description for Capture Normal
======= ========== ====================== =======


Terminology
^^^^^^^^^^^

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

================================ ==================================
Term                             Description
================================ ==================================
LGSE                             LG Sound Engine
WISA                             a hardware and software standard for wirelessly transmitting digital audio
BT                               Bluetooth soundoutput
SE_BT                            a Bluetooth soundoutput using a LGSE path of a "TV speaker + Bluetooth" sound output
OPTIC                            an optical sound output
OPTIC_LG                         an optical sound output for LG soundbars
SNDOUT                           a driver sound output
Dsnoop                           dsnoop is ALSA plugin allows several applications to record PCM data
LE Audio                         Low Energy audio
================================ ==================================


Technical Assistance
^^^^^^^^^^^^^^^^^^^^

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:

=============== ==========
Module          Owner
=============== ==========
capture         yookyung.uh@lge.com

                kwangshik.kim@lge.com
=============== ==========


Overview
--------


General Description
^^^^^^^^^^^^^^^^^^^
Audio Capture is the ALSA framework and is responsible for capturing supported TV soundouts.

Capture functionality is done by ALSA interface and ALSA interface guide is described in `ALSA Homepage. <https://www.alsa-project.org/wiki/Main_Page>`_

There are various types of sound output and related alsa device to capture

Normally after sound Output (Open/Connect) where capture audio data should be sent to is set,

For detail of sound output, please refer to :type:`common_output_ext_type_t`.

 * For Bitstream capture case, Bitrates value is updated from ALSA driver (BSP) during capture. So user would not set fixed value. (`hw:0,11`, `hw:0,14`)

 * For hw:0,11, user would not call ALSA API to use but DVBv5 PVR API. Please refer to DVBv5 PVR implementation guide for detail.

 * For hw:0,12, user would call dsnoop API to use. By dsnoop, different users could access simultaneously.

 * For hw:0,13, user would capture audio data for test or debugging with :type:`sndout_capture_path_t`

=========== ================================== ============ ============ =============== ============
Device Name Usage                              Remark       Channel      Format          Bitrates
            (:type:`common_output_ext_type_t`)                                           (available)
=========== ================================== ============ ============ =============== ============
hw:0,10     - :c:macro:`COMMON_BLUETOOTH`      PCM          2, 6         - S16_LE        - 44100
            - :c:macro:`COMMON_WISA`                                     - S32_LE        - 48000
            - :c:macro:`COMMON_SE_BT`
            - :c:macro:`COMMON_SE_BT_SUR`
            - :c:macro:`COMMON_DAP_HP_BT`
hw:0,11     From AENC to DVR                   Bitstream    N/A          N/A             Depend on ALSA driver
hw:0,12     Other Applications                 PCM          2 ~ 8        - S16_LE        - 44100
            (dsnoop)                                                     - S32_LE        - 48000
hw:0,13     Test                               PCM          2            - S16_LE        - 44100
                                                                         - S32_LE        - 48000
hw:0,14     :c:macro:`COMMON_WOWCAST`          Bitstream    2 ~ 8        - S16_LE        Depend on ALSA driver
                                                                         - S32_LE
hw:0,15     :c:macro:`COMMON_DAFC`             PCM          2 ~ 8        - S16_LE        - 48000
                                                                         - S32_LE
=========== ================================== ============ ============ =============== ============


Architecture
^^^^^^^^^^^^


Driver Architecture
*******************
The diagram below illustrates the main modules of the webOS audio framework, which is based on ALSA, and shows their interactions.

.. image:: resources/audio-overview.png
  :width: 100%
  :alt: ADEC Overview

The capture data is decided by "Sndout Connect" function.

It means:

* If the driver output is not connected to the driver sound output,
  the capture PCM data from ALSA utility functions such as ALSA Play and ALSA Record must follow a default gain of 0 dB. Mute is off.

* If the driver output is connected to a :c:macro:`COMMON_BLUETOOTH` sound output,
  the captured PCM data of :c:macro:`COMMON_BLUETOOTH` output must follow the "Gain Output" and "Mute Output" 0x8 (BT) of the BT sound output.

* If a driver output is connected to :c:macro:`COMMON_WISA` sound output,
  the captured the PCM data of a :c:macro:`COMMON_WISA` output must follow "Gain Output" and "Mute Output" 0x40(Wisa)
  and the driver must support channel number selection using the "snd_pcm_hw_params_set_channels" function.

* If a driver output is connected to :c:macro:`COMMON_SE_BT` sound output,
  captured the PCM data of a :c:macro:`COMMON_SE_BT`, captured the PCM data of SE_BT must follow "Gain Output" and "Mute Output" 0x80(SE_BT)

* If a driver output is connected to :c:macro:`COMMON_SE_BT_SUR` sound output,
  captured the PCM data of a :c:macro:`COMMON_SE_BT_SUR` must follow "Gain Output" and "Mute Output" 0x400(SE_BT_SUR)

* If a driver output is connected to :c:macro:`COMMON_WOWCAST` sound output,
  captured the PCM data of a :c:macro:`COMMON_WOWCAST` must follow "Gain Output" and "Mute Output" 0x0800(WOWCAST)

* If a driver output is connected to :c:macro:`COMMON_DAP_HP_BT` sound output,
  captured the PCM data of a :c:macro:`COMMON_DAP_HP_BT` must follow "Gain Output" and "Mute Output" 0x1000(DAP_HP_BT)

* If a driver output is connected to :c:macro:`COMMON_DAFC` sound output,
  captured the PCM data of a :c:macro:`COMMON_DAFC` must follow "Gain Output" and "Mute Output" 0x2000(DAFC)

Requirements
------------


Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^

The data types and functions used in this module are located in the Data Types and Functions in the API List.

For LE(Low Energy) Audio support, ALSA capture device now supports 16kHz and 24kHz sampling rate format as well as 48kHZ sampling rate, 2channel, signed 16bit Little Endian format


Quality and Constraints
^^^^^^^^^^^^^^^^^^^^^^^


Performance
***********

The same level of performance is required during resampling


Design Constraints
******************

The followings are some limitations for the function to work:

1. Capture is affected by Input Gain and Output Gain.
2. It is not affected by changes in Input.
3. The application uses "hw:0,10" to activate the Capture function.

SIC Limitation
""""""""""""""

* If the currently implemented Capture is not connected to SNDOUT, it may result in the delivery of NULL data due to the mismatch in output rate. Therefore, it is important to ensure that the corresponding part is not a problem in future implementations.

* It is required to establish at least one SNDOUT Connect for capturing audio data.


Implementation
--------------

This section provides materials that are useful for Capture implementation.

The File Location section provides the location of the Git repository where you can get the header file in which the interface for the Capture implementation is defined.

The API List section provides a brief summary of Capture APIs that you must implement.


File Location
^^^^^^^^^^^^^

The Capture driver uses the standard ALSA interface and there is no interfaces defined separately by LG. Please refer to the standard ALSA interface files.


API List
^^^^^^^^


Data Types
**********

* No Datatypes


Functions
*********


Standard Functions
""""""""""""""""""

========================================================================================================================================================== ===============================================
Function                                                                                                                                                   Description
========================================================================================================================================================== ===============================================
`snd_pcm_open <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#ga8340c7dc0ac37f37afe5e7c21d6c528b>`_                                     Opens a PCM.
`snd_pcm_hw_params <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#ga1ca0dc120a484965e26cabf966502330>`_                                Install one PCM hardware configuration chosen from a configuration space and snd_pcm_prepare it.
`snd_pcm_hw_params_malloc <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga6e53d09a9c7cc3f2a692c0af99886237>`_          allocate an invalid snd_pcm_hw_params_t using standard malloc
`snd_pcm_hw_params_any <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga6e2dd8efbb7a4084bd05e6cc458d84f7>`_             Fill params with a full configuration space for a PCM.
`snd_pcm_hw_params_set_access <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga4c8f1c632931923531ca68ee048a8de8>`_      Restrict a configuration space to contain only one access type.
`snd_pcm_hw_params_set_format <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga6014e0e1ec7934f8c745290e83e59199>`_      Restrict a configuration space to contain only one format.
`snd_pcm_hw_params_set_rate_near <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga39124280d06ce63092a77e3f25ddd6ee>`_   Restrict a configuration space to have rate nearest to a target.
`snd_pcm_hw_params_set_channels <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga3a5b2a05c5d9869cc743dac71c0d270a>`_    Restrict a configuration space to contain only one channels count.
`snd_pcm_prepare <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#ga788d05de75f2d536f8443cb0306754d0>`_                                  Prepare PCM for use.
`snd_pcm_close <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#ga042aba7262a4cbb4d444b6fc08cb7124>`_                                    close PCM handle
`snd_pcm_format_width <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___helpers.html#ga8d4e07f2d68cc16f607857ed8a222a29>`_                   Return nominal bits per a PCM sample.
`snd_pcm_hw_params_free <https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m___h_w___params.html#ga8c094063e7a13be0b9a043be8616a181>`_            frees a previously allocated snd_pcm_hw_params_t
========================================================================================================================================================== ===============================================


Implementation Details
^^^^^^^^^^^^^^^^^^^^^^

**Normal PCM, ALSA API**

Code to capture PCM data from an ALSA capture device

.. code-block:: c

  /*
    A Minimal Capture Program

    This program opens an audio interface for capture, configures it for
    stereo, 16 bit, 44.1kHz, interleaved conventional read/write
    access. Then its reads a chunk of random data from it, and exits. It
    isn't meant to be a real program.

    From on Paul David's tutorial : http://equalarea.com/paul/alsa-audio.html

    Fixes rate and buffer problems

    sudo apt-get install libasound2-dev
    gcc -o alsa-record-example -lasound alsa-record-example.c && ./alsa-record-example hw:0
  */

  #include <stdio.h>
  #include <stdlib.h>
  #include <alsa/asoundlib.h>

  main (int argc, char *argv[])
  {
    int i;
    int err;
    char *buffer;
    int buffer_frames = 128;
    unsigned int rate = 44100;
    snd_pcm_t *capture_handle;
    snd_pcm_hw_params_t *hw_params;
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

    if ((err = snd_pcm_open (&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n",
                argv[1],
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "audio interface opened\n");

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params allocated\n");

    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params initialized\n");

    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params access setted\n");

    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, format)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params format setted\n");

    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params rate setted\n");

    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params channels setted\n");

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "hw_params setted\n");

    snd_pcm_hw_params_free (hw_params);

    fprintf(stdout, "hw_params freed\n");

    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                snd_strerror (err));
        exit (1);
    }

    fprintf(stdout, "audio interface prepared\n");

    buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

    fprintf(stdout, "buffer allocated\n");

    for (i = 0; i < 10; ++i) {
        if ((err = snd_pcm_readi (capture_handle, buffer, buffer_frames)) != buffer_frames) {
        fprintf (stderr, "read from audio interface failed (%s)\n",
                err, snd_strerror (err));
        exit (1);
        }
        fprintf(stdout, "read %d done\n", i);
    }

    free(buffer);

    fprintf(stdout, "buffer freed\n");

    snd_pcm_close (capture_handle);
    fprintf(stdout, "audio interface closed\n");

    exit (0);
  }

**Normal PCM, APLAY, ARECORD, AMIXER utils**

Code to capture PCM data from an ALSA capture device

.. code-block:: bash

  # amixer -c 0 cset name="Sndout Open" 8
  # amixer -c 0 cset name="Sndout Connect" 8,1,0
  // 0 is port number.
  # arecord -D hw:0,10 -c 2 -f S16_LE -r 48000 -d 10 -v /tmp/cap.pcm

**WISA, ALSA API**

.. code-block:: c

  #include <stdio.h>
  #include <stdlib.h>
  #include <alsa/asoundlib.h>

  main (int argc, char *argv[])
  {
    int i;
    int err;
    char *buffer;
    int buffer_frames = 128;
    unsigned int rate = 48000;
    snd_pcm_t *capture_handle;
    snd_pcm_hw_params_t *hw_params;
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

    if ((err = snd_pcm_open (&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
      fprintf (stderr, "cannot open audio device %s (%s)\n",
               argv[1],
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "audio interface opened\n");

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
      fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params allocated\n");

    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
      fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params initialized\n");

    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
      fprintf (stderr, "cannot set access type (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params access setted\n");

    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, format)) < 0) {
      fprintf (stderr, "cannot set sample format (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params format setted\n");

    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
      fprintf (stderr, "cannot set sample rate (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params rate setted\n");

    /* channel should be set to 6 */
    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 6)) < 0) {
      fprintf (stderr, "cannot set channel count (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params channels setted\n");

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
      fprintf (stderr, "cannot set parameters (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params setted\n");

    snd_pcm_hw_params_free (hw_params);

    fprintf(stdout, "hw_params freed\n");

    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
      fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "audio interface prepared\n");

    buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

    fprintf(stdout, "buffer allocated\n");

      while ( thread flag )
      {
          snd_pcm_readi(pcm , buffer , sz);

          if(snd_pcm_avail(pcm) > 0) continue;
          while(snd_pcm_wait(pcm, 10) == 0)
          {
              if(thread flag == false) break;
          }
      }

    free(buffer);

    fprintf(stdout, "buffer freed\n");

    snd_pcm_close (capture_handle);
    fprintf(stdout, "audio interface closed\n");

    exit (0);
  }

**WISA, APLAY, ARECORD, AMIXER utils**

Code to capture PCM data from a WISA sound output using ALSA capture utility functions

.. code-block:: bash

  # amixer -c 0 cset name="Sndout Open" 0x40
  # amixer -c 0 cset name="Sndout Connect" 0x40,1,0
  // 0 is port number.
  # arecord -D hw:0,10 -c 6 -f S16_LE -r 48000 -d 10 -v /tmp/wisa.pcm


**Dsnoop for Applications**

Code to capture PCM data from a Dsnoop sound output using ALSA capture path

.. code-block:: c

  #include <stdio.h>
  #include <stdlib.h>
  #include <alsa/asoundlib.h>

  main (int argc, char *argv[])
  {
    int i;
    int err;
    char *buffer;
    int buffer_frames = 128;
    unsigned int rate = 48000;
    snd_pcm_t *capture_handle;
    snd_pcm_hw_params_t *hw_params;
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

    if ((err = snd_pcm_open (&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
      fprintf (stderr, "cannot open audio device %s (%s)\n",
               argv[1],
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "audio interface opened\n");

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
      fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params allocated\n");

    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
      fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params initialized\n");

    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_MMAP_INTERLEAVED)) < 0) {
      fprintf (stderr, "cannot set access type (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params access setted\n");

    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, format)) < 0) {
      fprintf (stderr, "cannot set sample format (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params format setted\n");

    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
      fprintf (stderr, "cannot set sample rate (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params rate setted\n");

    /* channel should be set to 6 */
    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 6)) < 0) {
      fprintf (stderr, "cannot set channel count (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params channels setted\n");

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
      fprintf (stderr, "cannot set parameters (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "hw_params setted\n");

    snd_pcm_hw_params_free (hw_params);

    fprintf(stdout, "hw_params freed\n");

    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
      fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
               snd_strerror (err));
      exit (1);
    }

    fprintf(stdout, "audio interface prepared\n");

    buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

    fprintf(stdout, "buffer allocated\n");

      while ( thread flag )
      {
          snd_pcm_mmap_readi(pcm , buffer , sz);

          if(snd_pcm_avail(pcm) > 0) continue;
          while(snd_pcm_wait(pcm, 10) == 0)
          {
              if(thread flag == false) break;
          }
      }

    free(buffer);

    fprintf(stdout, "buffer freed\n");

    snd_pcm_close (capture_handle);
    fprintf(stdout, "audio interface closed\n");

    exit (0);
  }

**DSNOOP, APLAY, ARECORD, AMIXER utils**

Code to capture PCM data from a DSNOOP sound output using ALSA capture utility functions

.. code-block:: bash

  # amixer -c 0 cset name="Sndout Open" 0x40
  # amixer -c 0 cset name="Sndout Connect" 0x40,1,0
  // 0 is port number.
  # arecord -D dsnoop:0,12 -c 6 -f S16_LE -r 48000 -d 10 -v /tmp/dsnoop.pcm
  # arecord -D plughw:0,12 -c 8 -f S32_LE -r 48000 -d 10 -v /tmp/dsnoop.wav
  # arecord -D hw:0,10 -c 6 -f S32_LE -r 48000 -d 10 -v /tmp/wisa.pcm


Testing
-------
To test the implementation of the Capture module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the Capture module and verifies the kernel event operations for the module by using a test execution file.
For more information, see :doc:`Capture’s SoCTS Unit Test manual </part4/socts/Documentation/source/producer-manual/producer-manual_alsa/producer-manual_alsa-adec_alsa-hdmi_alsa-gain_alsa-mute_alsa-capture>`.


References
----------
For additional information on related standards or technical topics, refer to:

| `ALSA-Project <https://www.alsa-project.org/wiki/Main_Page>`_
| `ALSA Kernel API Documentation <https://www.kernel.org/doc/html/v6.6-rc3/sound/kernel-api/index.html>`_
