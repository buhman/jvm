package sega.dreamcast.holly;


public class HollyBits {
    public class ID {
        public static int device_id(int n) {
            return (n >> 16) & 65535;
        }
        public static int vendor_id(int n) {
            return (n >> 0) & 65535;
        }
    }
    public class REVISION {
        public static int chip_revision(int n) {
            return (n >> 0) & 65535;
        }
    }
    public class SOFTRESET {
        public static final int sdram_if_soft_reset = 4;
        public static final int pipeline_soft_reset = 2;
        public static final int ta_soft_reset = 1;
    }
    public class STARTRENDER {
        public static final int start_render = 1;
    }
    public class TEST_SELECT {
        public static int diagdb_data(int n) {
            return (n >> 5) & 31;
        }
        public static int diagda_data(int n) {
            return (n >> 0) & 31;
        }
    }
    public class PARAM_BASE {
        public static int base_address(int n) {
            return (n & 15728640) << 0;
        }
    }
    public class REGION_BASE {
        public static int base_address(int n) {
            return (n & 16777212) << 0;
        }
    }
    public class SPAN_SORT_CFG {
        public static final int cache_bypass = 65536;
        public static final int offset_sort_enable = 256;
        public static final int span_sort_enable = 1;
    }
    public class VO_BORDER_COL {
        public static int chroma(int n) {
            return (n & 1) << 24;
        }
        public static int red(int n) {
            return (n & 255) << 16;
        }
        public static int green(int n) {
            return (n & 255) << 8;
        }
        public static int blue(int n) {
            return (n & 255) << 0;
        }
    }
    public class FB_R_CTRL {
        public class vclk_div {
            public static int pclk_vclk_2(int n) {
                return (n >> 23) & 1;
            }
            public static final int pclk_vclk_1 = 8388608;
        }
        public static final int fb_strip_buf_en = 4194304;
        public static int fb_stripsize(int n) {
            return (n & 62) << 16;
        }
        public static int fb_chroma_threshold(int n) {
            return (n & 255) << 8;
        }
        public static int fb_concat(int n) {
            return (n & 3) << 4;
        }
        public static final int fb_line_double = 2;
        public static final int fb_enable = 1;
        public class fb_depth {
            public static int _0555_rgb_16bit(int n) {
                return (n >> 2) & 3;
            }
            public static final int _0565_rgb_16bit = 4;
            public static final int _888_rgb_24bit_packed = 8;
            public static final int _0888_rgb_32bit = 12;
        }
    }
    public class FB_W_CTRL {
        public static int fb_alpha_threshold(int n) {
            return (n & 255) << 16;
        }
        public static int fb_kval(int n) {
            return (n & 255) << 8;
        }
        public static final int fb_dither = 8;
        public class fb_packmode {
            public static int _0555_krgb_16bit(int n) {
                return (n >> 0) & 7;
            }
            public static final int _565_rgb_16bit = 1;
            public static final int _4444_argb_16bit = 2;
            public static final int _1555_argb_16bit = 3;
            public static final int _888_rgb_24bit_packed = 4;
            public static final int _0888_krgb_32bit = 5;
            public static final int _8888_argb_32bit = 6;
        }
    }
    public class FB_W_LINESTRIDE {
        public static int fb_line_stride(int n) {
            return (n & 255) << 0;
        }
    }
    public class FB_R_SOF1 {
        public static int frame_buffer_read_address_frame_1(int n) {
            return (n & 16777212) << 0;
        }
    }
    public class FB_R_SOF2 {
        public static int frame_buffer_read_address_frame_2(int n) {
            return (n & 16777212) << 0;
        }
    }
    public class FB_R_SIZE {
        public static int fb_modulus(int n) {
            return (n & 1023) << 20;
        }
        public static int fb_y_size(int n) {
            return (n & 1023) << 10;
        }
        public static int fb_x_size(int n) {
            return (n & 1023) << 0;
        }
    }
    public class FB_W_SOF1 {
        public static int frame_buffer_write_address_frame_1(int n) {
            return (n & 33554428) << 0;
        }
    }
    public class FB_W_SOF2 {
        public static int frame_buffer_write_address_frame_2(int n) {
            return (n & 33554428) << 0;
        }
    }
    public class FB_X_CLIP {
        public static int fb_x_clip_max(int n) {
            return (n & 2047) << 16;
        }
        public static int fb_x_clip_min(int n) {
            return (n & 2047) << 0;
        }
    }
    public class FB_Y_CLIP {
        public static int fb_y_clip_max(int n) {
            return (n & 1023) << 16;
        }
        public static int fb_y_clip_min(int n) {
            return (n & 1023) << 0;
        }
    }
    public class FPU_SHAD_SCALE {
        public class simple_shadow_enable {
            public static int parameter_selection_volume_mode(int n) {
                return (n >> 8) & 1;
            }
            public static final int intensity_volume_mode = 256;
        }
        public static int scale_factor_for_shadows(int n) {
            return (n & 255) << 0;
        }
    }
    public class FPU_CULL_VAL {
        public static int culling_comparison_value(int n) {
            return (n & 2147483647) << 0;
        }
    }
    public class FPU_PARAM_CFG {
        public class region_header_type {
            public static int type_1(int n) {
                return (n >> 21) & 1;
            }
            public static final int type_2 = 2097152;
        }
        public static int tsp_parameter_burst_threshold(int n) {
            return (n & 63) << 14;
        }
        public static int isp_parameter_burst_threshold(int n) {
            return (n & 63) << 8;
        }
        public static int pointer_burst_size(int n) {
            return (n & 15) << 4;
        }
        public static int pointer_first_burst_size(int n) {
            return (n & 15) << 0;
        }
    }
    public class HALF_OFFSET {
        public class tsp_texel_sampling_position {
            public static final int top_left = 4;
            public static final int center = 4;
        }
        public class tsp_pixel_sampling_position {
            public static final int top_left = 2;
            public static final int center = 2;
        }
        public class fpu_pixel_sampling_position {
            public static final int top_left = 1;
            public static final int center = 1;
        }
    }
    public class FPU_PERP_VAL {
        public static int perpendicular_triangle_compare(int n) {
            return (n & 2147483647) << 0;
        }
    }
    public class ISP_BACKGND_D {
        public static int background_plane_depth(int n) {
            return (n & 268435455) << 4;
        }
    }
    public class ISP_BACKGND_T {
        public static final int cache_bypass = 268435456;
        public static final int shadow = 134217728;
        public static int skip(int n) {
            return (n & 7) << 24;
        }
        public static int tag_address(int n) {
            return (n & 2097151) << 3;
        }
        public static int tag_offset(int n) {
            return (n & 7) << 0;
        }
    }
    public class ISP_FEED_CFG {
        public static int cache_size_for_translucency(int n) {
            return (n & 1023) << 14;
        }
        public static int punch_through_chunk_size(int n) {
            return (n & 1023) << 4;
        }
        public static final int discard_mode = 8;
        public static final int pre_sort_mode = 1;
    }
    public class SDRAM_REFRESH {
        public static int refresh_counter_value(int n) {
            return (n & 255) << 0;
        }
    }
    public class SDRAM_ARB_CFG {
        public class override_value {
            public static int priority_only(int n) {
                return (n >> 18) & 15;
            }
            public static final int rendered_data = 262144;
            public static final int texture_vq_index = 524288;
            public static final int texture_normal_data_and_vq_codebook = 786432;
            public static final int tile_accelerator_isp_tsp_data = 1048576;
            public static final int tile_accelerator_pointers = 1310720;
            public static final int sh4 = 1572864;
            public static final int tsp_parameters = 1835008;
            public static final int tsp_region_data = 2097152;
            public static final int isp_pointer_data = 2359296;
            public static final int isp_parameters = 2621440;
            public static final int crt_controller = 2883584;
        }
        public class arbiter_priority_control {
            public static int priority_arbitration_only(int n) {
                return (n >> 16) & 3;
            }
            public static final int override_value_field = 65536;
            public static final int round_robin_counter = 131072;
        }
        public static int arbiter_crt_page_break_latency_count_value(int n) {
            return (n & 255) << 8;
        }
        public static int arbiter_page_break_latency_count_value(int n) {
            return (n & 255) << 0;
        }
    }
    public class SDRAM_CFG {
        public static int read_command_to_returned_data_delay(int n) {
            return (n & 7) << 26;
        }
        public static int cas_latency_value(int n) {
            return (n & 7) << 23;
        }
        public static int activate_to_activate_period(int n) {
            return (n & 3) << 21;
        }
        public static int read_to_write_period(int n) {
            return (n & 7) << 18;
        }
        public static int refresh_to_activate_period(int n) {
            return (n & 15) << 14;
        }
        public static int pre_charge_to_activate_period(int n) {
            return (n & 3) << 10;
        }
        public static int activate_to_pre_charge_period(int n) {
            return (n & 15) << 6;
        }
        public static int activate_to_read_write_command_period(int n) {
            return (n & 3) << 4;
        }
        public static int write_to_pre_charge_period(int n) {
            return (n & 3) << 2;
        }
        public static int read_to_pre_charge_period(int n) {
            return (n & 3) << 0;
        }
    }
    public class FOG_COL_RAM {
        public static int red(int n) {
            return (n & 255) << 16;
        }
        public static int green(int n) {
            return (n & 255) << 8;
        }
        public static int blue(int n) {
            return (n & 255) << 0;
        }
    }
    public class FOG_COL_VERT {
        public static int red(int n) {
            return (n & 255) << 16;
        }
        public static int green(int n) {
            return (n & 255) << 8;
        }
        public static int blue(int n) {
            return (n & 255) << 0;
        }
    }
    public class FOG_DENSITY {
        public static int fog_scale_mantissa(int n) {
            return (n & 255) << 8;
        }
        public static int fog_scale_exponent(int n) {
            return (n & 255) << 0;
        }
    }
    public class FOG_CLAMP_MAX {
        public static int alpha(int n) {
            return (n & 255) << 24;
        }
        public static int red(int n) {
            return (n & 255) << 16;
        }
        public static int green(int n) {
            return (n & 255) << 8;
        }
        public static int blue(int n) {
            return (n & 255) << 0;
        }
    }
    public class FOG_CLAMP_MIN {
        public static int alpha(int n) {
            return (n & 255) << 24;
        }
        public static int red(int n) {
            return (n & 255) << 16;
        }
        public static int green(int n) {
            return (n & 255) << 8;
        }
        public static int blue(int n) {
            return (n & 255) << 0;
        }
    }
    public class SPG_TRIGGER_POS {
        public static int trigger_v_count(int n) {
            return (n >> 16) & 1023;
        }
        public static int trigger_h_count(int n) {
            return (n >> 0) & 1023;
        }
    }
    public class SPG_HBLANK_INT {
        public static int hblank_in_interrupt(int n) {
            return (n >> 16) & 1023;
        }
        public static int line_comp_val(int n) {
            return (n & 1023) << 0;
        }
        public class hblank_int_mode {
            public static int output_equal_line_comp_val(int n) {
                return (n >> 12) & 3;
            }
            public static final int output_every_line_comp_val = 4096;
            public static final int output_every_line = 8192;
        }
    }
    public class SPG_VBLANK_INT {
        public static int vblank_out_interrupt_line_number(int n) {
            return (n & 1023) << 16;
        }
        public static int vblank_in_interrupt_line_number(int n) {
            return (n & 1023) << 0;
        }
    }
    public class SPG_CONTROL {
        public class csync_on_h {
            public static int hsync(int n) {
                return (n >> 9) & 1;
            }
            public static final int csync = 512;
        }
        public class sync_direction {
            public static int input(int n) {
                return (n >> 8) & 1;
            }
            public static final int output = 256;
        }
        public static final int pal = 128;
        public static final int ntsc = 64;
        public static final int force_field2 = 32;
        public static final int interlace = 16;
        public static final int spg_lock = 8;
        public class mcsync_pol {
            public static int active_low(int n) {
                return (n >> 2) & 1;
            }
            public static final int active_high = 4;
        }
        public class mvsync_pol {
            public static int active_low(int n) {
                return (n >> 1) & 1;
            }
            public static final int active_high = 2;
        }
        public class mhsync_pol {
            public static int active_low(int n) {
                return (n >> 0) & 1;
            }
            public static final int active_high = 1;
        }
    }
    public class SPG_HBLANK {
        public static int hbend(int n) {
            return (n & 1023) << 16;
        }
        public static int hbstart(int n) {
            return (n & 1023) << 0;
        }
    }
    public class SPG_LOAD {
        public static int vcount(int n) {
            return (n & 1023) << 16;
        }
        public static int hcount(int n) {
            return (n & 1023) << 0;
        }
    }
    public class SPG_VBLANK {
        public static int vbend(int n) {
            return (n & 1023) << 16;
        }
        public static int vbstart(int n) {
            return (n & 1023) << 0;
        }
    }
    public class SPG_WIDTH {
        public static int eqwidth(int n) {
            return (n & 1023) << 22;
        }
        public static int bpwidth(int n) {
            return (n & 1023) << 12;
        }
        public static int vswidth(int n) {
            return (n & 15) << 8;
        }
        public static int hswidth(int n) {
            return (n & 127) << 0;
        }
    }
    public class TEXT_CONTROL {
        public class code_book_endian {
            public static int little_endian(int n) {
                return (n >> 17) & 1;
            }
            public static final int big_endian = 131072;
        }
        public class index_endian {
            public static int little_endian(int n) {
                return (n >> 16) & 1;
            }
            public static final int big_endian = 65536;
        }
        public static int bank_bit(int n) {
            return (n & 31) << 8;
        }
        public static int stride(int n) {
            return (n & 31) << 0;
        }
    }
    public class VO_CONTROL {
        public static final int pclk_delay_reset = 2097152;
        public static int pclk_delay(int n) {
            return (n & 31) << 16;
        }
        public static final int pixel_double = 256;
        public static final int blank_video = 8;
        public class field_mode {
            public static int use_field_flag_from_spg(int n) {
                return (n >> 4) & 15;
            }
            public static final int use_inverse_of_field_flag_from_spg = 16;
            public static final int field_1_fixed = 32;
            public static final int field_2_fixed = 48;
            public static final int field_1_when_the_active_edges_of_hsync_and_vsync_match = 64;
            public static final int field_2_when_the_active_edges_of_hsync_and_vsync_match = 80;
            public static final int field_1_when_hsync_becomes_active_in_the_middle_of_the_vsync_active_edge = 96;
            public static final int field_2_when_hsync_becomes_active_in_the_middle_of_the_vsync_active_edge = 112;
            public static final int inverted_at_the_active_edge_of_vsync = 128;
        }
        public class blank_pol {
            public static int active_low(int n) {
                return (n >> 2) & 1;
            }
            public static final int active_high = 4;
        }
        public class vsync_pol {
            public static int active_low(int n) {
                return (n >> 1) & 1;
            }
            public static final int active_high = 2;
        }
        public class hsync_pol {
            public static int active_low(int n) {
                return (n >> 0) & 1;
            }
            public static final int active_high = 1;
        }
    }
    public class VO_STARTX {
        public static int horizontal_start_position(int n) {
            return (n & 1023) << 0;
        }
    }
    public class VO_STARTY {
        public static int vertical_start_position_on_field_2(int n) {
            return (n & 1023) << 16;
        }
        public static int vertical_start_position_on_field_1(int n) {
            return (n & 1023) << 0;
        }
    }
    public class SCALER_CTL {
        public class field_select {
            public static int field_1(int n) {
                return (n >> 18) & 1;
            }
            public static final int field_2 = 262144;
        }
        public static final int interlace = 131072;
        public static final int horizontal_scaling_enable = 65536;
        public static int vertical_scale_factor(int n) {
            return (n & 65535) << 0;
        }
    }
    public class PAL_RAM_CTRL {
        public class pixel_format {
            public static int argb1555(int n) {
                return (n >> 0) & 3;
            }
            public static final int rgb565 = 1;
            public static final int argb4444 = 2;
            public static final int argb8888 = 3;
        }
    }
    public class SPG_STATUS {
        public static int vsync(int n) {
            return (n >> 13) & 1;
        }
        public static int hsync(int n) {
            return (n >> 12) & 1;
        }
        public static int blank(int n) {
            return (n >> 11) & 1;
        }
        public static int fieldnum(int n) {
            return (n >> 10) & 1;
        }
        public static int scanline(int n) {
            return (n >> 0) & 1023;
        }
    }
    public class FB_BURSTCTRL {
        public static int wr_burst(int n) {
            return (n & 15) << 16;
        }
        public static int vid_lat(int n) {
            return (n & 127) << 8;
        }
        public static int vid_burst(int n) {
            return (n & 63) << 0;
        }
    }
    public class FB_C_SOF {
        public static int frame_buffer_current_read_address(int n) {
            return (n >> 0) & 16777215;
        }
    }
    public class Y_COEFF {
        public static int coefficient_1(int n) {
            return (n & 255) << 8;
        }
        public static int coefficient_0_2(int n) {
            return (n & 255) << 0;
        }
    }
    public class PT_ALPHA_REF {
        public static int alpha_reference_for_punch_through(int n) {
            return (n & 255) << 0;
        }
    }
    public class FOG_TABLE {
        public static int fog_table_data(int n) {
            return (n & 65535) << 0;
        }
    }
    public class PALETTE_RAM {
        public static int palette_data(int n) {
            return (n & -1) << 0;
        }
    }
}
