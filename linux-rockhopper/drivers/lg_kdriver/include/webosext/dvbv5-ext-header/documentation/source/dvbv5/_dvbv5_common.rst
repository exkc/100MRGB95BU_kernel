Common
======

.. _dvbv5-open:

dvbv5 open()
---------------

.. seealso::

    :ref:`v4l-dvb-apis:dmx_fopen`

    :ref:`v4l-dvb-apis:ca_fopen`

Functional Requirements
  This function makes dvbv5 H/W resource enabled for each Device(ACAS/BCAS/CA/DMX).
  Other functions of dvbv5 device operate normally only when the device is enabled
  by this function.
  Some dvbv5 device driver can be opened to the user client several times. That is,
  it can operate in a multiple open state. The dvbv5 Device control should be
  possible with all file descriptions.

Responses to abnormal situations, including
  If abnormal data is set, the driver should return an error.
  The generic error codes are described at the :ref:`gen_errors` chapter.

Performance Requirements
  The response time of this function should be within 10ms,
  if there are no special reasons.

Constraints
  We will update the content soon.

Functions & Parameters
  .. code-block:: cpp

    int open( const char *device_name, int flags )

Return Value
  On success 0 is returned.

  On error -1 and the errno variable is set appropriately. The generic error
  codes are described at the :ref:`gen_errors` chapter.

Example
  .. code-block:: cpp

    // linuxtv-ext-header
    /* Common */
    #define DEFAULT_ACAS_DEV_NO "/dev/dvb/adapter0/acas0"
    #define DEFAULT_BCAS_DEV_NO "/dev/dvb/adapter0/bcas0"
    #define DEFAULT_CA_DEV_NO "/dev/dvb/adapter0/ca0"
    #define STRING_CIP0_DEV "/dev/dvb/adapter0/ca1"
    #define STRING_CIP1_DEV "/dev/dvb/adapter0/ca2"
    #define STRING_CIP2_DEV "/dev/dvb/adapter0/ca3"
    #define DVBV5_EXT_DEV_PATH_DELIVERY_CH_A "/dev/dvb/adapter0/delivery0"
    #define DVBV5_EXT_DEV_PATH_DELIVERY_CH_B "/dev/dvb/adapter0/delivery1"
    #define DVBV5_EXT_DEV_PATH_DELIVERY_CH_C "/dev/dvb/adapter0/delivery2"
    "/dev/dvb/adapter0/demux0"
    "/dev/dvb/adapter0/demux1"
    "/dev/dvb/adapter0/demux2"
    "/dev/dvb/adapter0/demux3"



.. _dvbv5-close:

dvbv5 close()
--------------

.. seealso::

    :ref:`v4l-dvb-apis:dmx_fclose`

    :ref:`v4l-dvb-apis:ca_fclose`

Functional Requirements
  Close the dvbv5 device driver. Even if all file descriptions are closed, the
  existing state must be maintained.

  The video device driver can be opened to the user client several times. That is,
  it can operate in a multiple open state.


Responses to abnormal situations, including
  If abnormal data is set, the driver should return an error.
  The generic error codes are described at the :ref:`gen_errors` chapter.

Performance Requirements
  The response time of this function should be within 10ms,
  if there are no special reasons.

Constraints
  We will update the content soon.

Functions & Parameters
  .. code-block:: cpp

    int close(int fd)

Return Value
  On success 0 is returned.

  On error -1 and the errno variable is set appropriately. The generic error
  codes are described at the :ref:`gen_errors` chapter.

Example
  .. code-block:: cpp

    int ret;

    ret = close(fd);
