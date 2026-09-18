External Input Status
=====================

.. seealso::

  :doc:`/v4l2/hdmi-input`
  :doc:`/v4l2/component-input`
  :doc:`/v4l2/av-input`

History
-------

.. _hyungyong.park: hyungyong.park@lge.com

======= ========== =============== =======
Version Date       Changed by      Comment
======= ========== =============== =======
1.0.2   2019-08-22 hyungyong.park_ Change status file path
1.0.1   2019-08-22 hyungyong.park_ Change hdmi status file name, Definition of open and connection_state
1.0.0   2019-06-21 hyungyong.park_ Create Implementation Guide for External Input status
======= ========== =============== =======

Overview
--------

For checking external input driver's status, we require some items and format to
describe that information. Even chip vendor also add some values for check
driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules.

#. Items should be placed key and value
#. Before you print the Items, print which linuxtv-ext-header version like below
   version=linuxtv-ext-header ver.1.0.1 (submissions/21)
#. If some of section need many categories, you should print "Start" & "End" for
   separate that information. (See the example below)

.. code-block:: bash

  example)
  version=linuxtv-ext-header ver.1.0.1 (submissions/21)
  ===== HDMI STATUS =====
  open:1
  connection_state:210
  hpd_state : 2
  hwport:1

Section
^^^^^^^

HDMI
""""

.. seealso::

  :doc:`/v4l2/hdmi-input`

File path
  * /proc/lgtv-driver/hdmi_status/hdmi.p0
  * /proc/lgtv-driver/hdmi_status/hdmi.p1
  * /proc/lgtv-driver/hdmi_status/hdmi.p2
  * /proc/lgtv-driver/hdmi_status/hdmi.p3
  * /proc/lgtv-driver/hdmi_status/hdmi.p4
  * ...

Contents
  * In case of key field, please use lowercase characters.
  * The values field means the state or the value of current driver.

======================================== ================ ========================================== ==========
Key                                      Value type            Description                             Remarks
======================================== ================ ========================================== ==========
open                                     Integer value    0 : closed, other value : open count
connection_state                         Integer value    0 : disconnect, other value : process pid
hpd_state                                Integer value                                               2.12 V4L2_CID_EXT_HDMI_HPD
hwport                                   Integer value                                               v4l2_ext_hdmi_timing_info
timing_h_freq                            Integer value                                               v4l2_ext_hdmi_timing_info
timing_v_freq                            Integer value                                               v4l2_ext_hdmi_timing_info
timing_h_total                           Integer value                                               v4l2_ext_hdmi_timing_info
timing_v_total                           Integer value                                               v4l2_ext_hdmi_timing_info
timing_active_x                          Integer value                                               v4l2_ext_video_rect
timing_active_y                          Integer value                                               v4l2_ext_video_rect
timing_active_w                          Integer value                                               v4l2_ext_video_rect
timing_active_h                          Integer value                                               v4l2_ext_video_rect
timing_scan_type                         Integer value                                               v4l2_ext_hdmi_timing_info
dvi_hdmi                                 Integer value                                               v4l2_ext_hdmi_mode
color_depth                              Integer value                                               v4l2_ext_hdmi_color_depth
allm_mode                                Integer value                                               v4l2_ext_hdmi_timing_info
drm_version                              Integer value                                               v4l2_ext_hdmi_drm_info
drm_length                               Integer value                                               v4l2_ext_hdmi_drm_info
drm_eotf_type                            Integer value                                               v4l2_ext_hdmi_drm_eotf
drm_meta_desc                            Integer value                                               v4l2_ext_hdmi_drm_meta_desc
drm_display_primaries_x0                 Integer value                                               v4l2_ext_hdmi_drm_info
drm_display_primaries_y0                 Integer value                                               v4l2_ext_hdmi_drm_info
drm_display_primaries_x1                 Integer value                                               v4l2_ext_hdmi_drm_info
drm_display_primaries_y1                 Integer value                                               v4l2_ext_hdmi_drm_info
drm_display_primaries_x2                 Integer value                                               v4l2_ext_hdmi_drm_info
drm_display_primaries_y2                 Integer value                                               v4l2_ext_hdmi_drm_info
drm_white_point_x                        Integer value                                               v4l2_ext_hdmi_drm_info
drm_white_point_y                        Integer value                                               v4l2_ext_hdmi_drm_info
drm_max_display_mastering_luminance      Integer value                                               v4l2_ext_hdmi_drm_info
drm_min_display_mastering_luminance      Integer value                                               v4l2_ext_hdmi_drm_info
drm_maximum_content_light_level          Integer value                                               v4l2_ext_hdmi_drm_info
drm_maximum_frame_average_light_level    Integer value                                               v4l2_ext_hdmi_drm_info
vsi_video_format                         Integer value                                               v4l2_ext_hdmi_vsi_video_format
vsi_st_3d                                Integer value                                               v4l2_ext_hdmi_vsi_3d_structure
vsi_ext_data_3d                          Integer value                                               v4l2_ext_hdmi_vsi_3d_ext_data
vsi_vic                                  Integer value                                               v4l2_ext_hdmi_vsi_vic
vsi_regid                                Array                                                       v4l2_ext_hdmi_vsi_info
vsi_payload                              Array                                                       v4l2_ext_hdmi_vsi_info
spd_vendor_name                          String                                                      v4l2_ext_hdmi_spd_info
spd_product_description                  String                                                      v4l2_ext_hdmi_spd_info
spd_source_device_info                   Integer value                                               v4l2_ext_hdmi_spd_info
avi_mode                                 Integer value                                               v4l2_ext_hdmi_mode
avi_pixel_encoding                       Integer value                                               v4l2_ext_hdmi_avi_csc
avi_active_info                          Integer value                                               v4l2_ext_hdmi_avi_active_info
avi_bar_info                             Integer value                                               v4l2_ext_hdmi_avi_bar_info
avi_scan_info                            Integer value                                               v4l2_ext_hdmi_avi_scan_info
avi_colorimetry                          Integer value                                               v4l2_ext_hdmi_avi_colorimetry
avi_picture_aspect_ratio                 Integer value                                               v4l2_ext_hdmi_avi_picture_arc
avi_active_format_aspect_ratio           Integer value                                               v4l2_ext_hdmi_avi_active_format_arc
avi_scaling                              Integer value                                               v4l2_ext_hdmi_avi_scaling
avi_vic                                  Integer value                                               v4l2_ext_hdmi_avi_info
avi_pixel_repeat                         Integer value                                               v4l2_ext_hdmi_avi_info
avi_it_content                           Integer value                                               v4l2_ext_hdmi_avi_it_content
avi_extended_colorimetry                 Integer value                                               v4l2_ext_hdmi_avi_ext_colorimetry
avi_rgb_quantization_range               Integer value                                               v4l2_ext_hdmi_avi_rgb_quantization_range
avi_ycc_quantization_range               Integer value                                               v4l2_ext_hdmi_avi_ycc_quantization_range
avi_content_type                         Integer value                                               v4l2_ext_hdmi_avi_content_type
avi_additional_colorimetry               Integer value                                               v4l2_ext_hdmi_avi_additional_colorimetry
avi_top_bar_end_line_number              Integer value                                               v4l2_ext_hdmi_avi_info
avi_bottom_bar_start_line_number         Integer value                                               v4l2_ext_hdmi_avi_info
avi_left_bar_end_pixel_number            Integer value                                               v4l2_ext_hdmi_avi_info
avi_right_bar_end_pixel_number           Integer value                                               v4l2_ext_hdmi_avi_info
packet_status                            Integer value                                               v4l2_ext_hdmi_packet_status
packet_type                              Integer value                                               v4l2_ext_hdmi_packet_status
packet_version                           Integer value                                               v4l2_ext_hdmi_packet_status
packet_length                            Integer value                                               v4l2_ext_hdmi_packet_status
packet_data_bytes                        Array                                                       v4l2_ext_hdmi_packet_status
dolby_hdr_type                           Integer value                                               v4l2_ext_hdmi_dolby_hdr_type
vrr_frequency                            Integer value                                               v4l2_ext_hdmi_vrr_frequency
emp_type                                 Integer value                                               v4l2_ext_hdmi_emp_type
emp_total_packet_number                  Integer value                                               v4l2_ext_hdmi_emp_info
emp_data                                 Array                                                       v4l2_ext_hdmi_emp_info
phy_lock_status                          Integer value                                               v4l2_ext_hdmi_phy_status
phy_tmds_clk_khz                         Integer value                                               v4l2_ext_hdmi_phy_status
phy_link_type                            Integer value                                               v4l2_ext_hdmi_link_type
phy_link_lane                            Integer value                                               v4l2_ext_hdmi_link_lane_number
phy_link_rate                            Integer value                                               v4l2_ext_hdmi_link_rate
phy_ctle_eq_min_range                    Array                                                       v4l2_ext_hdmi_phy_status
phy_ctle_eq_max_range                    Array                                                       v4l2_ext_hdmi_phy_status
phy_ctle_eq_result                       Array                                                       v4l2_ext_hdmi_phy_status
phy_error                                Array                                                       v4l2_ext_hdmi_phy_status
link_hpd                                 Integer value                                               v4l2_ext_hdmi_link_status
link_hdmi_5v                             Integer value                                               v4l2_ext_hdmi_link_status
link_rx_sense                            Integer value                                               v4l2_ext_hdmi_link_status
link_frame_rate_x100_hz                  Integer value                                               v4l2_ext_hdmi_link_status
link_dvi_hdmi_mode                       Integer value                                               v4l2_ext_hdmi_mode
link_video_width                         Integer value                                               v4l2_ext_hdmi_link_status
link_video_height                        Integer value                                               v4l2_ext_hdmi_link_status
link_color_space                         Integer value                                               v4l2_ext_hdmi_avi_csc
link_color_depth                         Integer value                                               v4l2_ext_hdmi_link_status
link_colorimetry                         Integer value                                               v4l2_ext_hdmi_avi_colorimetry
link_ext_colorimetry                     Integer value                                               v4l2_ext_hdmi_avi_ext_colorimetry
link_additional_colorimetry              Integer value                                               v4l2_ext_hdmi_avi_additional_colorimetry
link_hdr_type                            Integer value                                               v4l2_ext_hdr_mode
link_audio_format                        Integer value                                               v4l2_ext_hdmi_audio_format
link_audio_sampling_freq                 Integer value                                               v4l2_ext_hdmi_link_status
link_audio_channel_number                Integer value                                               v4l2_ext_hdmi_link_status
video_width_real                         Integer value                                               v4l2_ext_hdmi_video_status
video_htotal_real                        Integer value                                               v4l2_ext_hdmi_video_status
video_height_real                        Integer value                                               v4l2_ext_hdmi_video_status
video_vtotal_real                        Integer value                                               v4l2_ext_hdmi_video_status
pixel_clock_khz                          Integer value                                               v4l2_ext_hdmi_video_status
current_vrr_refresh_rate                 Integer value                                               v4l2_ext_hdmi_video_status
audio_pcm_N                              Integer value                                               v4l2_ext_hdmi_audio_status
audio_pcm_CTS                            Integer value                                               v4l2_ext_hdmi_audio_status
audio_LayoutBitValue                     Integer value                                               v4l2_ext_hdmi_audio_status
audio_ChannelStatusBits                  Integer value                                               v4l2_ext_hdmi_audio_status
hdcp_version                             Integer value                                               v4l2_ext_hdmi_hdcp_version
hdcp_auth_status                         Integer value                                               v4l2_ext_hdmi_hdcp_auth_status
hdcp_encEn                               Integer value                                               v4l2_ext_hdmi_hdcp_status
hdcp14_status.port                       Integer value                                               v4l2_ext_hdmi_hdcp14_status
hdcp14_status.An                         Array                                                       v4l2_ext_hdmi_hdcp14_status
hdcp14_status.Aksv                       Array                                                       v4l2_ext_hdmi_hdcp14_status
hdcp14_status.Bksv                       Array                                                       v4l2_ext_hdmi_hdcp14_status
hdcp14_status.Ri                         Array                                                       v4l2_ext_hdmi_hdcp14_status
hdcp14_status.Bcaps                      Integer value                                               v4l2_ext_hdmi_hdcp14_status
hdcp14_status.Bstatus                    Array                                                       v4l2_ext_hdmi_hdcp14_status
hdcp22_status.port                       Integer value                                               v4l2_ext_hdmi_hdcp22_status
hdcp22_status.ake_init_count_since_5v    Integer value                                               v4l2_ext_hdmi_hdcp22_status
hdcp22_status.reauth_req_count_since_5v  Integer value                                               v4l2_ext_hdmi_hdcp22_status
scdc_source_version                      Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_sink_version                        Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_rsed_update                         Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_flt_update                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_frl_start                           Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_source_test_update                  Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_rr_test                             Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ced_update                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_status_update                       Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_tmds_bit_clock_ratio                Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_scrambling_enable                   Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_tmds_scrambler_status               Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_flt_no_retrain                      Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_rr_enable                           Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ffe_levels                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_frl_rate                            Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_dsc_decode_fail                     Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_flt_ready                           Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_clk_detect                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch0_locked                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch1_locked                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch2_locked                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch3_locked                          Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_lane0_ltp_request                   Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_lane1_ltp_request                   Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_lane2_ltp_request                   Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_lane3_ltp_request                   Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch0_ced_valid                       Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch1_ced_valid                       Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch2_ced_valid                       Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch3_ced_valid                       Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch0_ced                             Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch1_ced                             Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch2_ced                             Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_ch3_ced                             Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_rs_correction_valid                 Integer value                                               v4l2_ext_hdmi_scdc_status
scdc_rs_correcton_count                  Integer value                                               v4l2_ext_hdmi_scdc_status
error                                    Integer value                                               v4l2_ext_hdmi_error_type
error_param1                             Integer value                                               v4l2_ext_hdmi_error_status
error_param2                             Integer value                                               v4l2_ext_hdmi_error_status
edid_size                                Integer value                                               v4l2_ext_hdmi_edid_size
edid_data_block                          Array                                                       2.10 V4L2_CID_EXT_HDMI_EDID
======================================== ================ ========================================== ==========

Example
  /proc/lgtv-driver/hdmi_status/hdmi.p0

  .. code-block:: bash

    version=linuxtv-ext-header ver.1.0.1 (submissions/21)
    ===== HDMI STATUS =====
    open:1
    connection_state:210
    hpd_state : 2
    hwport:1
    timing_h_freq:0
    timing_v_freq:600
    timing_h_total:2200
    timing_v_total:1125
    timing_active_w:1920
    timing_active_h:1080
    timing_scan_type:1
    dvi_hdmi:1
    color_depth:0
    allm_mode:0
    drm_version:0
    drm_length:0
    drm_eotf_type:0
    drm_meta_desc:0
    drm_display_primaries_x0:0
    drm_display_primaries_y0:0
    drm_display_primaries_x1:0
    drm_display_primaries_y1:0
    drm_display_primaries_x2:0
    drm_display_primaries_y2:0
    drm_white_point_x:0
    drm_white_point_y:0
    drm_max_display_mastering_luminance:0
    drm_min_display_mastering_luminance:0
    drm_maximum_content_light_level:0
    drm_maximum_frame_average_light_level:0

    vsi_video_format:0
    vsi_st_3d:0
    vsi_ext_data_3d:0
    vsi_vic:0
    vsi_regid:0x01,0x02...
    vsi_payload:0x01,0x02,0x03...

    spd_vendor_name:"LGBDP"
    spd_product_description:"XXXXX"
    spd_source_device_info:0

    avi_mode:0
    avi_pixel_encoding:0
    avi_active_info:0
    avi_bar_info:3
    avi_scan_info:0
    avi_colorimetry:0
    avi_picture_aspect_ratio:2
    avi_active_format_aspect_ratio:8
    avi_scaling:0
    avi_vic:16
    avi_pixel_repeat:0
    avi_it_content:0
    avi_extended_colorimetry:0
    avi_rgb_quantization_range:1
    avi_ycc_quantization_range:0
    avi_content_type:0
    avi_top_bar_end_line_number:36
    avi_bottom_bar_start_line_number:4
    avi_left_bar_end_pixel_number:148
    avi_right_bar_end_pixel_number:88

    packet_status:2
    packet_type:130
    packet_version:2
    packet_length:13
    packet_data_bytes:0x13, 0x0c, 0x28, 0x04, 0x10 ...

    dolby_hdr_type:0

    vrr_frequency:600

    emp_type:4096
    emp_total_packet_number:1
    emp_data: 0x00,0x00, 0x00 ...

    phy_lock_status:1
    phy_tmds_clk_khz:14850
    phy_link_type:0
    phy_link_lane:3
    phy_link_rate:3
    phy_ctle_eq_min_range:0x0, 0x0, 0x0, 0x0
    phy_ctle_eq_max_range:0x0, 0x0, 0x0, 0x0
    phy_ctle_eq_result:0xc, 0xc, 0xc, 0xc
    phy_error:0x0, 0x0, 0x0, 0x0

    link_hpd:1
    link_hdmi_5v:1
    link_rx_sense:1
    link_frame_rate_x100_hz:6000
    link_dvi_hdmi_mode:1
    link_video_width:1920
    link_video_height:1080
    link_color_space:0
    link_color_depth:8
    link_colorimetry:0
    link_ext_colorimetry:0
    link_additional_colorimetry:0
    link_hdr_type:0
    link_audio_format:0
    link_audio_sampling_freq:0
    link_audio_channel_number:0

    video_width_real:1920
    video_htotal_real:2200
    video_height_real:1080
    video_vtotal_real:1125
    pixel_clock_khz:148500
    current_vrr_refresh_rate:60

    audio_pcm_N:0
    audio_pcm_CTS:73729080
    audio_LayoutBitValue:20
    audio_ChannelStatusBits:68

    hdcp_version:0
    hdcp_auth_status:3
    hdcp_encEn:1
    hdcp14_status.port:60
    hdcp14_status.An:0x53 0xb0 0x9a 0xd9 0x53 0xb0 0x9a 0xd9
    hdcp14_status.Aksv:0xdf 0x63 0x49 0x4c 0x98
    hdcp14_status.Bksv:0x3c 0xa0 0xf4 0x66 0xf4
    hdcp14_status.Ri:0xfe 0xff
    hdcp14_status.Bcaps:129
    hdcp14_status.Bstatus:0x0 0x0
    hdcp22_status.port:0
    hdcp22_status.ake_init_count_since_5v:0
    hdcp22_status.reauth_req_count_since_5v:0

    scdc_source_version:0
    scdc_sink_version:1
    scdc_rsed_update:0
    scdc_flt_update:1
    scdc_frl_start:0
    scdc_source_test_update:0
    scdc_rr_test:0
    scdc_ced_update:0
    scdc_status_update:1
    scdc_tmds_bit_clock_ratio:0
    scdc_scrambling_enable:0
    scdc_tmds_scrambler_status:0
    scdc_flt_no_retrain:0
    scdc_rr_enable:0
    scdc_ffe_levels:0
    scdc_frl_rate:0
    scdc_dsc_decode_fail:0
    scdc_flt_ready:1
    scdc_clk_detect:1
    scdc_ch0_locked:1
    scdc_ch1_locked:1
    scdc_ch2_locked:1
    scdc_ch3_locked:0
    scdc_lane0_ltp_request:2
    scdc_lane1_ltp_request:11
    scdc_lane2_ltp_request:3
    scdc_lane3_ltp_request:3
    scdc_ch0_ced_valid:1
    scdc_ch1_ced_valid:1
    scdc_ch2_ced_valid:1
    scdc_ch3_ced_valid:0
    scdc_ch0_ced:0
    scdc_ch1_ced:0
    scdc_ch2_ced:0
    scdc_ch3_ced:0
    scdc_rs_correction_valid:0
    scdc_rs_correcton_count:0

    error : 0
    error_param1 : 0
    error_param2 : 0

    edid_size :2
    edid_data_block0 : 0x00, 0xff, 0xff, 0xff ..
    edid_data_block1 : 0x02, 0x03, 0x5b,0xf1 ..
    ..
    edid_data_block3 : ..

ADC
"""

.. seealso::

  :doc:`/v4l2/component-input`

File path
  * /proc/lgtv-driver/adc_status/adc

Contents
  * In case of key field, please use lowercase characters.
  * The values field means the state or the value of current driver.

=================== ================ ========================================== ==========
Key                 Value type            Description                             Remarks
=================== ================ ========================================== ==========
open                Integer value    0:closed, other value:open count
input_src           0,1              - V4L2_EXT_ADC_INPUT_SRC_NONE = 0
                                     - V4L2_EXT_ADC_INPUT_SRC_COMP =1
timing_h_freq       Integer value                                               v4l2_ext_adc_timing_info
timing_v_freq       Integer value                                               v4l2_ext_adc_timing_info
timing_h_total      Integer value                                               v4l2_ext_adc_timing_info
timing_v_total      Integer value                                               v4l2_ext_adc_timing_info
timing_h_porch      Integer value                                               v4l2_ext_adc_timing_info
timing_v_porch      Integer value                                               v4l2_ext_adc_timing_info
timing_active_x     Integer value                                               v4l2_ext_video_rect
timing_active_y     Integer value                                               v4l2_ext_video_rect
timing_active_w     Integer value                                               v4l2_ext_video_rect
timing_active_h     Integer value                                               v4l2_ext_video_rect
timing_scan_type    Integer value                                               v4l2_ext_adc_timing_info
phase               Integer value                                               v4l2_ext_adc_timing_info
r_gain              Integer value                                               v4l2_ext_adc_calibration_data
g_gain              Integer value                                               v4l2_ext_adc_calibration_data
b_gain              Integer value                                               v4l2_ext_adc_calibration_data
r_offset            Integer value                                               v4l2_ext_adc_calibration_data
g_offset            Integer value                                               v4l2_ext_adc_calibration_data
b_offset            Integer value                                               v4l2_ext_adc_calibration_data
calibration_type    Integer value    - V4L2_EXT_ADC_CALIBRATION_TYPE_OTP=0      V4L2_CID_EXT_ADC_CALIBRATION_TYPE
                                     - V4L2_EXT_ADC_CALIBRATION_TYPE_EXTERNAL=1
                                     - V4L2_EXT_ADC_CALIBRATION_TYPE_INTERNAL=2
                                     - V4L2_EXT_ADC_CALIBRATION_TYPE_USER=3
fast_switch_mode    Integer value    0:Off, 1:On                                V4L2_CID_EXT_ADC_FAST_SWITCH
=================== ================ ========================================== ==========

Example
  /proc/lgtv-driver/hdmi_status/hdmi.p0

  .. code-block:: bash

    version=linuxtv-ext-header ver.1.0.1 (submissions/21)
    ===== ADC STATUS =====
    input_src:1
    timing_h_freq:674
    timing_v_freq:600
    timing_h_total:2200
    timing_v_total:1130
    timing_h_porch:154
    timing_v_porch:34
    timing_active_x:0
    timing_active_y:0
    timing_active_w:1920
    timing_active_h:1080
    timing_scan_type:1
    phase:12
    r_gain:3810
    g_gain:3824
    b_gain:3825
    r_offset:2048
    g_offset:2048
    b_offset:2048
    calibration_type:2
    fast_switch_mode:1

AVD
"""

.. seealso::

  :doc:`/v4l2/av-input`

  File path
  * /proc/lgtv-driver/avd_status/avd

Contents
  * In case of key field, please use lowercase characters.
  * The values field means the state or the value of current driver.

=================== ================ ============================================= ==========
Key                 Value type       Description                                   Remarks
=================== ================ ============================================= ==========
open                Integer value    0 : closed, interger value : open count
input_src           Integer value    - V4L2_EXT_AVD_INPUT_SRC_NONE = 0             Following the type of enum v4l2_ext_avd_input_src
                                     - V4L2_EXT_AVD_INPUT_SRC_ATV = 1
                                     - V4L2_EXT_AVD_INPUT_SRC_AV = 2
hwport              0~255            HW port
timing_h_freq       Integer value    h frequency                                   Following the type of enum v4l2_ext_avd_timing_info
timing_v_freq       Integer value    v frequency                                   Following the type of enum v4l2_ext_avd_timing_info
timing_h_porch      Integer value    h porch                                       Following the type of enum v4l2_ext_avd_timing_info
timing_v_porch      Integer value    v porch                                       Following the type of enum v4l2_ext_avd_timing_info
timing_active_w     Integer value    The w value of resolution                     Following the type of enum v4l2_ext_video_rect
timing_active_h     Integer value    The h value of resolution                     Following the type of enum v4l2_ext_video_rect
timing_active_x     Integer value    The x value of resolution                     Following the type of enum v4l2_ext_video_rect
timing_active_y     Integer value    The y value of resolution                     Following the type of enum v4l2_ext_video_rect
timing_vd_lock      Integer value                                                  Following the type of enum v4l2_ext_avd_timing_info
timing_h_lock       Integer value                                                  Following the type of enum v4l2_ext_avd_timing_info
timing_v_lock       Integer value                                                  Following the type of enum v4l2_ext_avd_timing_info
avd_sync            Integer value    0 (AVD Sync Not Locked), 1 (AVD Sync Locked)  V4L2_CID_EXT_AVD_VIDEO_SYNC
color_standard      Integer value                                                  VIDIOC_S_STD / VIDIOC_G_STD
auto_tuning_mode    Integer value                                                  V4L2_CID_EXT_AVD_AUTO_TUNING_MODE
noise_level         Integer value
=================== ================ ============================================= ==========

Example
  /proc/lgtv-driver/hdmi_status/hdmi.p0

  .. code-block:: bash

    version=linuxtv-ext-header ver.1.0.1 (submissions/21)
    ===== AVD STATUS =====
    open:0
    input_src:2
    hwport:2
    timing_h_freq:157
    timing_v_freq:599
    timing_h_porch:96
    timing_v_porch:18
    timing_active_w:704
    timing_active_h:480
    timing_active_x:0
    timing_active_y:0
    timing_vd_lock:1
    timing_h_lock:1
    timing_v_lock:1
    avd_sync:1
    color_standard:0xb000
    auto_tuning_mode:1
    noise_level:449
