demux Status
=============

.. seealso::

  :doc:`/dvbv5/demux`

History
-------

.. _seong.lee: seong.lee@lge.com

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
1.0.0   2020-04-14 seong.lee           initial
0.0.0   ...        ...                 ...
======= ========== =================== =======

Overview
--------

For checking demux driver's status, we require some items and format to
describe that information. Even chip vendor also add some values for check
driver status.

Detail
------

Default Print Rules
..........................

For parsing these information, we should follow below rules.

  #. Items should be placed key and value

  #. If some of section need many categories, you should print "Start" & "End"
     for separate that information. (See the example below)

.. code-block:: bash

  example)

  DEMUX PARAMETERS
  DMX_EXT_CID_PLATFORM: 0
  DMX_EXT_CID_COUNTRY: 0

  INPUT SOURCE STATUS
  DEMUX   SOURCE      PORT     TYPE
  0       IN_DEMOD    0        Parallel
  1       None        0        Serial
  2       IN_DEMOD    0        Parallel
  3       None        0        Serial

  PID FILTER STATUS
  Demux[0]
  NUM    PID       DEST
  0      0x0078    VD0
  5      0x0014    BUF
  6      0x0012    BUF
  11     0x0082    AD0
  12     0x006e    BUF
  14     0x0000    BUF
  16     0x0010    BUF

  Demux[2]
  NUM    PID       DEST
  15     0x0011    BUF

  PCR STATUS
  Num Enable  PID
  0   O       0x0078
  1   X       NONE

Section
.............

File location
  ``/proc/lgtv-driver/dvb_demux/``

File name
  ``status``

Device Status
..........................

DEMUX PARAMETERS
~~~~~~~~~~~~~~~~~~~~~~~~~~

DMX_EXT_CID_PLATFORM
    value of DMX_EXT_CID_PLATFORM, Default is "ATSC". ( ATSC / DVB / ISDB / COMMERCIAL )

DMX_EXT_CID_COUNTRY
    value of DMX_EXT_CID_COUNTRY, Default is "KR". ( KR / US / EU / CN / MA / JP / COLUMBIA )


INPUT SOURCE STATUS
~~~~~~~~~~~~~~~~~~~~~~~~~~

DEMUX
    port number of demux

SOURCE
    value of input_src_type(:cpp:any:`dmx_ext_source`), default is "None". (IN_DEMOD / EXT_DEMOD / CI / CIP / MEM / USB_CI / IPTV)

PORT
    value of input_port_num(:cpp:any:`dmx_ext_source`), default is 0.(decimal)

TYPE
    value of input_port_type(:cpp:any:`dmx_ext_source`), default is "Serial". ( Serial / Parallel)

.. code-block:: bash

	DEMUX   SOURCE     PORT     TYPE
	0       IN_DEMOD   0        Parallel

PID FILTER STATUS
~~~~~~~~~~~~~~~~~~~~~~~~~~

Demux[N]
    N is value of demux port

NUM
    value of filter index

PID
    value of PID(hex)

PES_TYPE
    value of pes_type in struct dmx_pes_filter_params.
    ( DMX_PES_VIDEO0 / DMX_PES_AUDIO0 / DMX_PES_TELETEXT0 / DMX_PES_SUBTITLE0 / DMX_PES_OTHER)
    or ( VD0 / AD0 / TTX0 / BUF ). DMX_PES_OTHER is "BUF".

.. code-block:: bash

   3. PID FILTER STATUS
   Demux[0]
   NUM   PID      DEST
   0     0x0078   VD0

PCR STATUS
~~~~~~~~~~~~~~~~~~~~~~~~~~

NUM
    value of PCR HW ( 0 / 1 )

Enable
    value of DMX_EXT_CID_PCR_ONOFF. ( Off = "X", On = "O" ), Default is "X".

PID
    value of PCR PID(hex), Default "None"

.. code-block:: bash

   4. PCR STATUS
   Num Enable   PID
   0   O        0x0078
   1   X        NONE

Example
-------

.. code-block:: bash

  $ cat /proc/lgtv-driver/dvb_demux/status

  DEMUX PARAMETERS
  DMX_EXT_CID_PLATFORM: 0
  DMX_EXT_CID_COUNTRY: 0

  INPUT SOURCE STATUS
  DEMUX   SOURCE      PORT     TYPE
  0       IN_DEMOD    0        Parallel
  1       None        0        Serial
  2       IN_DEMOD    0        Parallel
  3       None        0        Serial

  PID FILTER STATUS
  Demux[0]
  NUM    PID       DEST
  0      0x0078    VD0
  5      0x0014    BUF
  6      0x0012    BUF
  11     0x0082    AD0
  12     0x006e    BUF
  14     0x0000    BUF
  16     0x0010    BUF

  Demux[2]
  NUM    PID       DEST
  15     0x0011    BUF

  PCR STATUS
  Num Enable  PID
  0   O       0x0078
  1   X       NONE