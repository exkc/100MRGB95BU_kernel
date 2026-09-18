#ifndef _PDM_REG_H_
#define _PDM_REG_H_

typedef enum
{
    DISABLE_FLAG = 0,
    ENABLE_FLAG  = 1,
} PDM_FLAG;

typedef enum
{
    MASK_BIT_0 = 0,
    MASK_BIT_1 = 1,
} PDM_MASKER;

typedef enum
{
    PDM_CHANNEL_DISABLE = 0,
    PDM_MONO_LEFT       = 1,
    PDM_MONO_RIGHT      = 2,
    PDM_STEREO          = 3,
}PDM_MIC_CHANNEL_T;

typedef enum
{
    PDM_HIGHPASS_FILTER_OFF =0,
    PDM_HIGHPASS_FILTER_ON =1,
}PDM_ADCHPD_T;

typedef enum
{
    PDM_DMA_INT = 0x1,
    PDM_TRIGGER_INT = 0x2,
    PDM_VAD_INT = 0x4,
}PDM_RAW_STATUS_CLEAR_T;

typedef enum
{
    PDM_DESTINATION_CPU = 0x1,
    PDM_DESTINATION_DSP = 0x2,
    PDM_DESTINATION_MICOM = 0x4,
}PDM_DESTINATION_T;

typedef enum
{
    PDM_TRIGGER_MODE = 0x0,
    PDM_DMA_MODE = 0x1,
}PDM_TRANSFER_MODE_T;

typedef enum
{
    BURST_FIXED_WORD_SIZE_1  = 0,
    BURST_FIXED_WORD_SIZE_4  = 1,
    BURST_FIXED_WORD_SIZE_8  = 2,
    BURST_FIXED_WORD_SIZE_16 = 3,
}PDM_BURST_LENGTH_32_BIT_FIXED_WORD_SIZE_T;

typedef enum
{
    PDM_UNPACK =0,    // data unpacking
    PDM_PACK =1,    // data packing -
} PDM_FIFO_MODE_T;

typedef enum
{
    PCM_WORD_LENGTH_16BIT = 0,
    PCM_WORD_LENGTH_24BIT = 3,
} PDM_PCM_WORD_LENGTH_T;

typedef enum
{
    PDM_DMA_NONE = 0,
    PDM_DMA0_INTERRUPT = 1,
    PDM_DMA1_INTERRUPT = 2,
} PDM_DMA_INTR_NUM_T;

typedef enum
{
    FILTER_OFF = 0,
    FILTER_ON = 1,
} PDM_FILTER_SWITCH_T;

typedef union
{
    struct
    {
        uint32_t minor_version                  : 8;    //[7:0]
        uint32_t major_version                  : 8;    //[15:8]
        uint32_t develop_version                : 8;    //[23:16]
        uint32_t pdm_audio_ip_id                : 8;    //[31:24]
    } f;
    uint32_t w;
}REG_MMR_PDM_ID_T;

typedef union
{
    struct
    {
        uint32_t soft_reset                     : 1;    //[0]
        uint32_t pdm_demodulator_enable         : 1;    //[1]
        uint32_t dma_detec_monitor_enable       : 1;    //[2]
        uint32_t reserved_3                     : 1;    //[3]
        uint32_t mic_channel                    : 2;    //[5:4]
        uint32_t pdm_wordlen                    : 2;    //[7:6]
        uint32_t vad_decision_smoothing_enable  : 1;    //[8]
        uint32_t noise_supression_enable        : 1;    //[9]
        uint32_t vad_enable                     : 1;    //[10]
        uint32_t vad_pcmdata_direction          : 1;    //[11]
        uint32_t dma_pcmdata_ctrl               : 1;    //[12]
        uint32_t debugging0                     : 1;    //[13]
        uint32_t debugging_reserved             : 2;    //[15:14]
        uint32_t valid_cnt_clear                : 1;    //[16]
        uint32_t valid_cnt_enable               : 1;    //[17]
#if defined (CHIP_NAME_o26)
        uint32_t sel_adc_pcm                    : 1;    //[18]
        uint32_t sel_adc_pcm_val                : 1;    //[19]
        uint32_t reserved_31_20                 : 12;   //[31:20]
#else
        uint32_t reserved_31_18                 : 14;   //[31:18]
#endif
    } f;
    uint32_t w;
} REG_MMR_PDM_CTRL_T;

typedef union
{
    struct
    {
        uint32_t raw_status_clear               : 3;    // [2:0]
        uint32_t reserved_3                     : 1;    // [3]
        uint32_t dma_mask                       : 4;    // [7:4]
        uint32_t destination                    : 4;    // [11:8]
        uint32_t interrupt_enable               : 1;    // [12]
        uint32_t trigger_interrupt_mask         : 1;    // [13]
        uint32_t reserved_15_14                 : 2;    // [15:14]
        uint32_t vad_interrupt_mask             : 4;    // [19:16]
        uint32_t reserved_31_20                 : 12;   // [31:20]
    } f;
    uint32_t w;
} REG_MMR_PDM_INT_T;

typedef union
{
    struct
    {
        uint32_t dma_enable                            : 1; // [0]
        uint32_t transfer_mode                         : 1; // [1]
        uint32_t burst_length_32_bit_fixed_word_size   : 2; // [3:2]
        uint32_t dma_channel                           : 2; // [5:4]
        uint32_t dma0_start_addr_set_enable            : 1; // [6]
        uint32_t dma1_start_addr_set_enable            : 1; // [7]
        uint32_t transfer_size                         : 8; // [15:8]
        uint32_t total_length                          : 15;// [30:16]
        uint32_t dma_controll_mode                     : 1; // [31]
    } f;
    uint32_t w;
} REG_MMR_PDM_DMAC_T;

typedef union
{
    struct
    {
        uint32_t dma_address_side_a             : 32;   // [31:0]
    } f;
    uint32_t w;
} REG_MMR_PDM_DMADSTADDR0_T;

typedef union
{
    struct
    {
        uint32_t dma_address_side_b             : 32;   // [31:0]
    } f;
    uint32_t w;
} REG_MMR_PDM_DMADSTADDR1_T;

typedef union
{
    struct
    {
        uint32_t fifo_flush                     : 1 ;   // [0]
        uint32_t reserved_31_1                  : 31 ;  // [31:1]
    } f;
    uint32_t w;
} REG_MMR_PDM_FIFO_T;

typedef union
{
    struct
    {
        uint32_t wae_b                          :16 ;   // [15:0]  decision SNR threshold of weight parameter(a) for speech in WAE algorithm.
	    uint32_t wae_a1                         :16 ;   // [31:16] noise estimation weight paramter for speech (Q format is samp with iir   filter)
    } f;
    uint32_t w;
} REG_MMR_VAD_WAE_B_A1_T;

typedef union
{
    struct
    {
        uint32_t wae_a2                         :16;    // [15:0]  noise estimation weight paramter for noise (Q format is samp with iir filter)
        uint32_t wae_c	                        :16;    // [31:16] speech estimation weight paramter (Q format is samp with iir filter)
    } f;
    uint32_t w;
} REG_MMR_VAD_WAE_A2_C_T;

typedef union
{
    struct
    {
        uint32_t dma0_fifo_cnt	                :15;    // [14:0]  The number not transferred data of fifo
        uint32_t reserved_31_15	                :17;    // [31:15] reseved

    } f;
    uint32_t w;
} REG_MMR_PDM_DMA_CNT_T;

typedef union
{
    struct
    {
        uint32_t vad_iir_coefficient_0	        :16; // [15:0]  "VAD IIR filter Coefficients 0 0x0000~0xFFFF"
        uint32_t vad_iir_coefficient_1	        :16; // [31:16] "VAD IIR filter Coefficients 1 0x0000~0xFFFF"
    } f;
    uint32_t w;
} REG_MMR_PDM_ENG_ZCR_COEF01_T;

typedef union
{
    struct
    {
        uint32_t vad_iir_coefficient_2	        :16; // [15:0]  "VAD IIR filter Coefficients 2 0x0000~0xFFFF"
        uint32_t vad_iir_coefficient_3	        :16; // [31:16] "VAD IIR filter Coefficients 3 0x0000~0xFFFF"
    } f;
    uint32_t w;
} REG_MMR_PDM_ENG_ZCR_COEF23_T;

typedef union
{
    struct
    {
        uint32_t vad_iir_coefficient_4	            :16; // [15:0]	"VAD IIR filter Coefficients 4 0x0000~0xFFFF"
        uint32_t q_format_of_vad_iir_coefficient	:4 ; // [19:16]	Q format of IIR filter coefficient
        uint32_t reserved_31_20		                :12; // [31:20] reseved
    } f;
    uint32_t w;
} REG_MMR_PDM_ENG_ZCR_COEF4_QFOM_T;

typedef union
{
    struct
    {
        uint32_t hpgain                         :4;     // [3:0]
        uint32_t adchpd                         :1;     // [4]
        uint32_t soft_mute                      :1;     // [5]
        uint32_t reserved_7_6                   :2;     // [7:6]
        uint32_t sinc_shift                     :5;     // [12:8]
        uint32_t reserved_15_13                 :3;     // [15:13]
        uint32_t s_cycles                       :3;     // [18:16]
        uint32_t reserved_31_19                 :1;     // [19]
        uint32_t pdm_data_valid_delay           :3;     // [22:20]
        uint32_t reserved_23                    :1;     // [23]
        uint32_t wov_pdm_clkout_mux_sel         :4;     // [27:24]
        uint32_t reserved_31_28                 :4;     // [31:28]
    } f;
    uint32_t w;
} REG_MMR_PDM_CORE_CTRL_T;

typedef union
{
    struct
    {
        uint32_t fifo_pop_cnt	                :8;     // [7:0] Current pop data pointer
        uint32_t fifo_top_cnt	                :8;     // [15:8] Current top of fifo pointer
        uint32_t reserved_31_16	                :16;    // [31:16] reseved
    } f;
    uint32_t w;
} REG_MMR_PDM_FIFO_CNT_T;

typedef union
{
    struct
    {
        uint32_t pdm_fifo_data                  :32;    // [31:0] Read pcm data from FIFO
    } f;
    uint32_t w;
} REG_MMR_PDM_FIFO_DATA_T;

typedef union
{
    struct
    {
	    uint32_t snr_th0                        :16;    // [15:0] "SNR_th0 : wae_speeh/wae_noise threshold(Q format is same with iir filter) 0x0000~0xFFFF"
	    uint32_t snr_th1                        :16;    // [31:16] "SNR_th1 : wae_speeh/wae_noise threshold(Q format is samp with iir filter) 0x0000~0xFFFF"
    } f;
    uint32_t w;
} REG_MMR_PDM_VAD_SNR_TH_T;

typedef union
{
    struct
    {
	    uint32_t step_size                      :16;    // [15:0]  Step size(μ) for LMS in Q14 format
	    uint32_t min_vad_frames                 :4;     // [19:16] Min VAD active frames to trigger VAD event
	    uint32_t reserved_31_20	                :12;    // [31:20]
    } f;
    uint32_t w;
} REG_MMR_PDM_NS_STEP_SIZE_T;

typedef union
{
    struct
    {
        uint32_t mclkdiv                        :8;     // [7:0] PDM_CKO(digital mic input clock)= PDMCLK/(MCLKDIV*2)
        uint32_t reserved_15_8                  :8;     // [15:8] reseved
        uint32_t sinc_rate                      :16;    // [31:16] Samp_clk(sampling frequency)=PDM_CKO/SINC_RATE
    } f;
    uint32_t w;
} REG_MMR_PDM_CORE_CTRL2_T;

typedef union
{
    struct
    {
        uint32_t vad_intr_addr                  :32;    // [31:0] DMA write address when VAD interrupt active
    } f;
    uint32_t w;
} REG_MMR_VAD_INTR_ADDR_T;

typedef union
{
    struct
    {
        uint32_t vad_intr_addr_clear            :32;    // [31:0] VAD_INTR_ADDR value clear
    } f;
    uint32_t w;
} REG_MMR_VAD_INTR_ADDR_CLEAR_T;

typedef union
{
    struct
    {
        uint32_t vad_intr_num                   :2;    // [1:0] "2'b00 : None 2'b01 : PDM0 VAD Interrupt first 2'b10 : PDM1 VAD Interrupt first "
        uint32_t reserved_31_2                  :30;   // [31:2] reserved
    } f;
    uint32_t w;
} REG_MMR_VAD_INTR_NUM_T;

typedef union
{
    struct
    {
        uint32_t dma_intr_num                   :2;    // [1:0] 2'b00 : None, 2'b01 : DMA0 Interrupt, 2'b10 : DMA1 Interrupt
        uint32_t reserved_31_2                  :30;   // [31:2] reserved
    } f;
    uint32_t w;
} REG_MMR_DMA_INTR_NUM_T;

typedef union
{
    struct
    {
        uint32_t pcm_valid_cnt                  :32;   // [31:0] pcm valid cnt
    } f;
    uint32_t w;
}REG_MMR_PCM_VALID_CNT_T;

typedef union
{
    struct
    {
        uint32_t id                             :8;    // [7:0]
        uint32_t reserved_31_8                  :24;   // [31:8] reserved
    } f;
    uint32_t w;
}REG_MMR_IIR_ID_T;

typedef union
{
    struct
    {
        uint32_t coeff                          :24;    // [23:0] ] coeff
        uint32_t reserved_31_2                  :8;     // [31:24] reserved
    } f;
    uint32_t w;
} REG_MMR_FILTER_COEFF_T;

typedef union
{
    struct
    {
        uint32_t bit_shift_anti_filter_out      :4;  // [3:0]   left shift 0~15
        uint32_t bit_shift_anti_filter_in       :4;  // [7:4]   barrel shifter -8~7
        uint32_t bit_shift_comp_filter_out      :4;  // [11:8]  left shift 0~15
        uint32_t bit_shift_comp_filter_in       :4;  // [15:12] barrel shifter -8~7
        uint32_t anti_aliasing_sel              :1;  // [16] 0 : no process, 1 : process
        uint32_t compensation_sel               :1;  // [17] 0 : no process, 1 : process
        uint32_t extra_filter_sel               :1;  // [18] 0 : no process, 1 : process
        uint32_t reserved_19                    :1;  // [19] reserved
        uint32_t enable                         :1;  // [20] enable
        uint32_t reserved_31_21                 :11; // [31:21] reserved
    } f;
    uint32_t w;
} REG_MMR_FILTER_CONTROL_T;

typedef union
{
    struct
    {
        uint32_t bit_shift_hpf_filter_out       :4;  // [3:0]   left shift 0~15
        uint32_t bit_shift_hpf_filter_in        :4;  // [7:4]   barrel shifter -8~7
        uint32_t reserved_31_8                  :24;  // [31:8] reserved
    } f;
    uint32_t w;
} REG_MMR_FILTER_CONTROL2_T;

typedef union
{
    struct
    {
        uint32_t pcm_buffer_size                : 32;   // [31:0]
    } f;
    uint32_t w;
} REG_MMR_PCM_BUFFER_SIZE_T;

typedef union
{
    struct
    {
        uint32_t dma0_addr_update               : 32;   // [31:0]
    } f;
    uint32_t w;
} REG_MMR_DMA0_ADDR_UPDATE_T;

typedef union
{
    struct
    {
        uint32_t dma1_addr_update               : 32;   // [31:0]
    } f;
    uint32_t w;
} REG_MMR_DMA1_ADDR_UPDATE_T;

/**********************************************************
  top
**********************************************************/
typedef union
{
    REG_MMR_PDM_ID_T                   pdm_id;                  // 0x00
    REG_MMR_PDM_CTRL_T                 pdm_ctrl;                // 0x04
    REG_MMR_PDM_INT_T                  pdm_int;                 // 0x08
    REG_MMR_PDM_DMAC_T                 pdm_dmac;                // 0x0c
    REG_MMR_PDM_DMADSTADDR0_T          pdm_dmadstaddr0;         // 0x10
    REG_MMR_PDM_DMADSTADDR1_T          pdm_dmadstaddr1;         // 0x14
    REG_MMR_PDM_FIFO_T                 pdm_fifo;                // 0x18
    REG_MMR_VAD_WAE_B_A1_T             vad_wae_b_a1;            // 0x1c
    REG_MMR_VAD_WAE_A2_C_T             vad_wae_a2_c;            // 0x20
    REG_MMR_PDM_DMA_CNT_T              pdm_dma_cnt;             // 0x24
    REG_MMR_PDM_ENG_ZCR_COEF01_T       pdm_eng_zcr_coef01;      // 0x28
    REG_MMR_PDM_ENG_ZCR_COEF23_T       pdm_eng_zcr_coef23;      // 0x2c
    REG_MMR_PDM_ENG_ZCR_COEF4_QFOM_T   pdm_eng_zcr_coef4_qfom;  // 0x30
    REG_MMR_PDM_CORE_CTRL_T            pdm_core_ctrl;           // 0x34
    REG_MMR_PDM_FIFO_CNT_T             pdm_fifo_cnt;            // 0x38
    REG_MMR_PDM_FIFO_DATA_T            pdm_fifo_data;           // 0x3c
    REG_MMR_PDM_VAD_SNR_TH_T           pdm_vad_snr_th;          // 0x40
    REG_MMR_PDM_NS_STEP_SIZE_T         pdm_ns_step_size;        // 0x54
    REG_MMR_PDM_CORE_CTRL2_T           pdm_core_ctrl2;          // 0x58
    REG_MMR_VAD_INTR_ADDR_T            vad_intr_addr;           // 0x60
    REG_MMR_VAD_INTR_ADDR_CLEAR_T      vad_intr_addr_clear;     // 0x64
    REG_MMR_VAD_INTR_NUM_T             vad_intr_num;            // 0x68
    REG_MMR_DMA_INTR_NUM_T             dma_intr_num;            // 0x70
    REG_MMR_PCM_VALID_CNT_T            pcm_valid_count;         // 0x74
    REG_MMR_IIR_ID_T                   iir_id;                  // 0x78
    REG_MMR_FILTER_COEFF_T             aaf0_a0;                 // 0x80
    REG_MMR_FILTER_COEFF_T             aaf0_a1;                 // 0x84
    REG_MMR_FILTER_COEFF_T             aaf0_a2;                 // 0x88
    REG_MMR_FILTER_COEFF_T             aaf0_b0;                 // 0x8c
    REG_MMR_FILTER_COEFF_T             aaf0_b1;                 // 0x90
    REG_MMR_FILTER_COEFF_T             aaf0_b2;                 // 0x94
    REG_MMR_FILTER_COEFF_T             aaf1_a0;                 // 0x98
    REG_MMR_FILTER_COEFF_T             aaf1_a1;                 // 0x9c
    REG_MMR_FILTER_COEFF_T             aaf1_a2;                 // 0xa0
    REG_MMR_FILTER_COEFF_T             aaf1_b0;                 // 0xa4
    REG_MMR_FILTER_COEFF_T             aaf1_b1;                 // 0xa8
    REG_MMR_FILTER_COEFF_T             aaf1_b2;                 // 0xac
    REG_MMR_FILTER_COEFF_T             aaf2_a0;                 // 0xb0
    REG_MMR_FILTER_COEFF_T             aaf2_a1;                 // 0xb4
    REG_MMR_FILTER_COEFF_T             aaf2_a2;                 // 0xb8
    REG_MMR_FILTER_COEFF_T             aaf2_b0;                 // 0xbc
    REG_MMR_FILTER_COEFF_T             aaf2_b1;                 // 0xc0
    REG_MMR_FILTER_COEFF_T             aaf2_b2;                 // 0xc4
    REG_MMR_FILTER_COEFF_T             aaf3_a0;                 // 0xc8
    REG_MMR_FILTER_COEFF_T             aaf3_a1;                 // 0xcc
    REG_MMR_FILTER_COEFF_T             aaf3_a2;                 // 0xd0
    REG_MMR_FILTER_COEFF_T             aaf3_b0;                 // 0xd4
    REG_MMR_FILTER_COEFF_T             aaf3_b1;                 // 0xd8
    REG_MMR_FILTER_COEFF_T             aaf3_b2;                 // 0xdc
    REG_MMR_FILTER_COEFF_T             cf0_a0;                  // 0xe0
    REG_MMR_FILTER_COEFF_T             cf0_a1;                  // 0xe4
    REG_MMR_FILTER_COEFF_T             cf0_a2;                  // 0xe8
    REG_MMR_FILTER_COEFF_T             cf0_a3;                  // 0xec
    REG_MMR_FILTER_COEFF_T             cf0_a4;                  // 0xf0
    REG_MMR_FILTER_COEFF_T             cf0_a5;                  // 0xf4
    REG_MMR_FILTER_COEFF_T             cf0_b0;                  // 0x100
    REG_MMR_FILTER_COEFF_T             cf0_b1;                  // 0x104
    REG_MMR_FILTER_COEFF_T             cf0_b2;                  // 0x108
    REG_MMR_FILTER_COEFF_T             cf0_b3;                  // 0x10c
    REG_MMR_FILTER_COEFF_T             cf0_b4;                  // 0x110
    REG_MMR_FILTER_COEFF_T             cf0_b5;                  // 0x114
    REG_MMR_FILTER_CONTROL_T           filter_control;          // 0x120
    REG_MMR_FILTER_CONTROL2_T          filter_control2;         // 0x124
    REG_MMR_FILTER_COEFF_T             hpf_a0;                  // 0x128
    REG_MMR_FILTER_COEFF_T             hpf_a1;                  // 0x12c
    REG_MMR_FILTER_COEFF_T             hpf_a2;                  // 0x130
    REG_MMR_FILTER_COEFF_T             hpf_b0;                  // 0x134
    REG_MMR_FILTER_COEFF_T             hpf_b1;                  // 0x138
    REG_MMR_FILTER_COEFF_T             hpf_b2;                  // 0x13c
    REG_MMR_PCM_BUFFER_SIZE_T          pcm_buffer_size;         // 0x140
    REG_MMR_DMA0_ADDR_UPDATE_T         dma0_addr_update;        // 0x144
    REG_MMR_DMA1_ADDR_UPDATE_T         dma1_addr_update;        // 0x148

    uint32_t w;
} PDM_REG_T;
#endif

