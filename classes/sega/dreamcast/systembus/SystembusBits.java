package sega.dreamcast.systembus;

public class SystembusBits {
    public static int c2dstat__texture_memory_start_address(int n) {
        return (n & 335544288) << 0;
    }
    public static int c2dlen__transfer_length(int n) {
        return (n & 16777184) << 0;
    }
    public static final int c2dst__start = 1 << 0;
    public static final int istnrm__end_of_transferring_punch_through_list = 1 << 21;
    public static final int istnrm__end_of_dma_sort_dma = 1 << 20;
    public static final int istnrm__end_of_dma_ch2_dma = 1 << 19;
    public static final int istnrm__end_of_dma_dev_dma = 1 << 18;
    public static final int istnrm__end_of_dma_ext_dma2 = 1 << 17;
    public static final int istnrm__end_of_dma_ext_dma1 = 1 << 16;
    public static final int istnrm__end_of_dma_aica_dma = 1 << 15;
    public static final int istnrm__end_of_dma_gd_dma = 1 << 14;
    public static final int istnrm__maple_v_blank_over_interrupt = 1 << 13;
    public static final int istnrm__end_of_dma_maple_dma = 1 << 12;
    public static final int istnrm__end_of_dma_pvr_dma = 1 << 11;
    public static final int istnrm__end_of_transferring_translucent_modifier_volume_list = 1 << 10;
    public static final int istnrm__end_of_transferring_translucent_list = 1 << 9;
    public static final int istnrm__end_of_transferring_opaque_modifier_volume_list = 1 << 8;
    public static final int istnrm__end_of_transferring_opaque_list = 1 << 7;
    public static final int istnrm__end_of_transferring_yuv = 1 << 6;
    public static final int istnrm__h_blank_in_interrupt = 1 << 5;
    public static final int istnrm__v_blank_out_interrupt = 1 << 4;
    public static final int istnrm__v_blank_in_interrupt = 1 << 3;
    public static final int istnrm__end_of_render_tsp = 1 << 2;
    public static final int istnrm__end_of_render_isp = 1 << 1;
    public static final int istnrm__end_of_render_video = 1 << 0;
    public static final int isterr__sh4__if_access_inhibited_area = 1 << 31;
    public static final int isterr__ddt__if_sort_dma_command_error = 1 << 28;
    public static final int isterr__g2__time_out_in_cpu_access = 1 << 27;
    public static final int isterr__g2__dev_dma_time_out = 1 << 26;
    public static final int isterr__g2__ext_dma2_time_out = 1 << 25;
    public static final int isterr__g2__ext_dma1_time_out = 1 << 24;
    public static final int isterr__g2__aica_dma_time_out = 1 << 23;
    public static final int isterr__g2__dev_dma_over_run = 1 << 22;
    public static final int isterr__g2__ext_dma2_over_run = 1 << 21;
    public static final int isterr__g2__ext_dma1_over_run = 1 << 20;
    public static final int isterr__g2__aica_dma_over_run = 1 << 19;
    public static final int isterr__g2__dev_dma_illegal_address_set = 1 << 18;
    public static final int isterr__g2__ext_dma2_illegal_address_set = 1 << 17;
    public static final int isterr__g2__ext_dma1_illegal_address_set = 1 << 16;
    public static final int isterr__g2__aica_dma_illegal_address_set = 1 << 15;
    public static final int isterr__g1__rom_flash_access_at_gd_dma = 1 << 14;
    public static final int isterr__g1__gd_dma_over_run = 1 << 13;
    public static final int isterr__g1__illegal_address_set = 1 << 12;
    public static final int isterr__maple__illegal_command = 1 << 11;
    public static final int isterr__maple__write_fifo_over_flow = 1 << 10;
    public static final int isterr__maple__dma_over_run = 1 << 9;
    public static final int isterr__maple__illegal_address_set = 1 << 8;
    public static final int isterr__pvrif__dma_over_run = 1 << 7;
    public static final int isterr__pvrif__illegal_address_set = 1 << 6;
    public static final int isterr__ta__fifo_overflow = 1 << 5;
    public static final int isterr__ta__illegal_parameter = 1 << 4;
    public static final int isterr__ta__object_list_pointer_overflow = 1 << 3;
    public static final int isterr__ta__isp_tsp_parameter_overflow = 1 << 2;
    public static final int isterr__render__hazard_processing_of_strip_buffer = 1 << 1;
    public static final int isterr__render__isp_out_of_cache = 1 << 0;
    public static int ffst__holly_cpu_if_block_internal_write_buffer(int n) {
        return (n >> 5) & 1;
    }
    public static int ffst__holly_g2_if_block_internal_write_buffer(int n) {
        return (n >> 4) & 1;
    }
    public static int ffst__aica_internal_write_buffer(int n) {
        return (n >> 0) & 1;
    }
}
