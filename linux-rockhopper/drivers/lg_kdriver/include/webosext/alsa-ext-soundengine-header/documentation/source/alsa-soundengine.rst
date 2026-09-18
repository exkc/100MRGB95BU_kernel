ALSA Soundengine
==================

.. toctree::
  :maxdepth: 1
  :glob:

  alsa-soundengine/*

======== ==========
Priority Definition
======== ==========
1        Minimum APIs for DTV Audio
2        Minimum APIs for ATV
======== ==========

.. important::
  1. Value type should be ``int`` (default)

  .. figure:: alsa-soundengine/resources/alsa_struct-snd_ctl_elem_value.png
    :scale: 100%

  2. param[in] is put parameter and param[out] is get parameter.

  3. Whole functions should be excuted in 10 ms.
