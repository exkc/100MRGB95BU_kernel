PVR Status
==========

.. seealso::

  :doc:`/dvbv5/pvr`

History
-------

.. _hwachin.lee: hwachin.lee@lge.com

======= ========== ============== =======
Version Date       Changed by     Comment
======= ========== ============== =======
1.0.2   2019-07-10 `hwachin.lee`_ add property files
                                  /proc/lgtv-driver/dvb_dvr/prop_es_type
                                  /proc/lgtv-driver/dvb_dvr/prop_bw_capa
1.0.1   2019-06-19 `hwachin.lee`_ change driver status path /proc/lgtv-driver/dvr-status → /proc/lgtv-driver/dvb_dvr/status
1.0.0   2018-09-27 `hwachin.lee`_ Initial release
======= ========== ============== =======

Rules of description display
----------------------------

In case of idle status, no need to display for other values.

Driver Status Path
^^^^^^^^^^^^^^^^^^

``/proc/lgtv-driver/dvb_dvr/status``

Download Device
^^^^^^^^^^^^^^^

status
  idle / playing / paused

buffer status
  total download buffer size , occupied buffer size ( kbytes )

read size total
  total bytes for read function (mbytes)

Upload Device
^^^^^^^^^^^^^

status
  idle / playing / paused

buffer status
  total download buffer size , occupied buffer size ( kbytes )

av sync
  sync / free run

play rate
  -1600 / -800 / -400 / -200 / 0 / 50 / 100 / 200 / 400 / 800 / 1600

write size total
  total bytes for write function (mbytes)

Example
-------

.. code-block:: bash

  $ cat /proc/lgtv-driver/dvb_dvr/status

  down-ch0
  status : playing
  buffser state : total 4096kb, occupy 1024kb
  read size total : 102mb

  down-ch1
  status : idle

  up-ch0
  status : playing
  buffser state : total 4096kb, occupy 1024kb
  av sync : sync
  play rate : 100
  write size total : 88mb

  up-ch1
  status : idle

Miscellaneous PVR Properties
----------------------------

There are some functional difference or restriction due to the each Soc vendors
HW environments.

To implement run-time branch not compile time, those differences are described
on some specific ROOTFS location.

LG required spec is like below table.

== =============================== ====================================== =====
   Spec                            File Path                              Value
== =============================== ====================================== =====
1  ES with field picture encoded   /proc/lgtv-driver/dvb_dvr/prop_es_type | 0 : Encoded ES is Frame Picture
                                                                          | 1 : Encoded ES is Field Picture
2  Bandwidth capability limitation /proc/lgtv-driver/dvb_dvr/prop_bw_capa | 0 : No BW limitation APVR and 4K play
                                                                          | 1 : BW limitation APVR and 4K play
== =============================== ====================================== =====
