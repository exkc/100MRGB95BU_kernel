DDR Status
=============

History
-------

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
0.0.1   2022-07-29 khkh.lee            initial
======= ========== =================== =======

Overview
--------

For checking DDR status, we require some items and format to
describe that information.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules.

  #. Items should be placed key and value
  #. You can check the status in the file

DDR Status
..........................

Info file location
  ``/proc/lgtv-driver/ddr/ddr_info``

DDR_SIZE
    Size of DDR.(GB)

CLOCK
    Associated RAM Clock Rates(MHz)

Example
-------

.. code-block:: bash

   cat /proc/lgtv-driver/ddr/ddr_info  
   DDR_SIZE=1.5
   CLOCK= 2000MHz
