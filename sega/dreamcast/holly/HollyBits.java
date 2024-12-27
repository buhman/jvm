package sega.dreamcast.holly;

public class CoreBits {
    public static int id__device_id(int n) {
        return (n >> 16) & 65535;
    }
    public static int id__vendor_id(int n) {
        return (n >> 0) & 65535;
    }
    public static int revision__chip_revision(int n) {
        return (n >> 0) & 65535;
    }
    public static final int softreset__sdram_if_soft_reset = 1 << 2;
    public static final int softreset__pipeline_soft_reset = 1 << 1;
    public static final int softreset__ta_soft_reset = 1 << 0;
    public static final int startrender__start_render = 1 << 0;
    public static int test_select__diagdb_data(int n) {
        return (n >> 5) & 31;
    }
    public static int test_select__diagda_data(int n) {
        return (n >> 0) & 31;
    }
    public static int param_base__base_address(int n) {
        return (n & 15728640) << 0;
    }
    public static int region_base__base_address(int n) {
        return (n & 16777212) << 0;
    }
    public static final int span_sort_cfg__cache_bypass = 1 << 16;
    public static final int span_sort_cfg__offset_sort_enable = 1 << 8;
    public static final int span_sort_cfg__span_sort_enable = 1 << 0;
    public static int vo_border_col__chroma(int n) {
        return (n & 1) << 24;
    }
    public static int vo_border_col__red(int n) {
        return (n & 255) << 16;
    }
    public static int vo_border_col__green(int n) {
        return (n & 255) << 8;
    }
    public static int vo_border_col__blue(int n) {
        return (n & 255) << 0;
    }
    public static int fb_r_ctrl__vclk_div__pclk_vclk_2(int n) {
        return (n >> 23) & 1;
    }
    public static final int fb_r_ctrl__vclk_div__pclk_vclk_1 = 1 << 23;
    public static final int fb_r_ctrl__fb_strip_buf_en = 1 << 22;
    public static int fb_r_ctrl__fb_stripsize(int n) {
        return (n & 62) << 16;
    }
    public static int fb_r_ctrl__fb_chroma_threshold(int n) {
        return (n & 255) << 8;
    }
    public static int fb_r_ctrl__fb_concat(int n) {
        return (n & 3) << 4;
    }
    public static final int fb_r_ctrl__fb_line_double = 1 << 1;
    public static final int fb_r_ctrl__fb_enable = 1 << 0;
    public static int fb_r_ctrl__fb_depth__0555_rgb_16bit(int n) {
        return (n >> 2) & 3;
    }
    public static final int fb_r_ctrl__fb_depth__565_rgb_16bit = 1 << 2;
    public static final int fb_r_ctrl__fb_depth__888_rgb_24bit_packed = 2 << 2;
    public static final int fb_r_ctrl__fb_depth__0888_rgb_32bit = 3 << 2;
    public static int fb_w_ctrl__fb_alpha_threshold(int n) {
        return (n & 255) << 16;
    }
    public static int fb_w_ctrl__fb_kval(int n) {
        return (n & 255) << 8;
    }
    public static final int fb_w_ctrl__fb_dither = 1 << 3;
    public static int fb_w_ctrl__fb_packmode__0555_krgb_16bit(int n) {
        return (n >> 0) & 7;
    }
    public static final int fb_w_ctrl__fb_packmode__565_rgb_16bit = 1 << 0;
    public static final int fb_w_ctrl__fb_packmode__4444_argb_16bit = 2 << 0;
    public static final int fb_w_ctrl__fb_packmode__1555_argb_16bit = 3 << 0;
    public static final int fb_w_ctrl__fb_packmode__888_rgb_24bit_packed = 4 << 0;
    public static final int fb_w_ctrl__fb_packmode__0888_krgb_32bit = 5 << 0;
    public static final int fb_w_ctrl__fb_packmode__8888_argb_32bit = 6 << 0;
    public static int fb_w_linestride__fb_line_stride(int n) {
        return (n & 255) << 0;
    }
    public static int fb_r_sof1__frame_buffer_read_address_frame_1(int n) {
        return (n & 16777212) << 0;
    }
    public static int fb_r_sof2__frame_buffer_read_address_frame_2(int n) {
        return (n & 16777212) << 0;
    }
    public static int fb_r_size__fb_modulus(int n) {
        return (n & 1023) << 20;
    }
    public static int fb_r_size__fb_y_size(int n) {
        return (n & 1023) << 10;
    }
    public static int fb_r_size__fb_x_size(int n) {
        return (n & 1023) << 0;
    }
    public static int fb_w_sof1__frame_buffer_write_address_frame_1(int n) {
        return (n & 33554428) << 0;
    }
    public static int fb_w_sof2__frame_buffer_write_address_frame_2(int n) {
        return (n & 33554428) << 0;
    }
    public static int fb_x_clip__fb_x_clip_max(int n) {
        return (n & 2047) << 16;
    }
    public static int fb_x_clip__fb_x_clip_min(int n) {
        return (n & 2047) << 0;
    }
    public static int fb_y_clip__fb_y_clip_max(int n) {
        return (n & 1023) << 16;
    }
    public static int fb_y_clip__fb_y_clip_min(int n) {
        return (n & 1023) << 0;
    }
    public static int fpu_shad_scale__simple_shadow_enable__parameter_selection_volume_mode(int n) {
        return (n >> 8) & 1;
    }
    public static final int fpu_shad_scale__simple_shadow_enable__intensity_volume_mode = 1 << 8;
    public static int fpu_shad_scale__scale_factor_for_shadows(int n) {
        return (n & 255) << 0;
    }
    public static int fpu_cull_val__culling_comparison_value(int n) {
        return (n & 2147483647) << 0;
    }
    public static int fpu_param_cfg__region_header_type__type_1(int n) {
        return (n >> 21) & 1;
    }
    public static final int fpu_param_cfg__region_header_type__type_2 = 1 << 21;
    public static int fpu_param_cfg__tsp_parameter_burst_threshold(int n) {
        return (n & 63) << 14;
    }
    public static int fpu_param_cfg__isp_parameter_burst_threshold(int n) {
        return (n & 63) << 8;
    }
    public static int fpu_param_cfg__pointer_burst_size(int n) {
        return (n & 15) << 4;
    }
    public static int fpu_param_cfg__pointer_first_burst_size(int n) {
        return (n & 15) << 0;
    }
    public static final int half_offset__tsp_texel_sampling_position__top_left = 1 << 2;
    public static final int half_offset__tsp_texel_sampling_position__center = 1 << 2;
    public static final int half_offset__tsp_pixel_sampling_position__top_left = 1 << 1;
    public static final int half_offset__tsp_pixel_sampling_position__center = 1 << 1;
    public static final int half_offset__fpu_pixel_sampling_position__top_left = 1 << 0;
    public static final int half_offset__fpu_pixel_sampling_position__center = 1 << 0;
    public static int fpu_perp_val__perpendicular_triangle_compare(int n) {
        return (n & 2147483647) << 0;
    }
    public static int isp_backgnd_d__background_plane_depth(int n) {
        return (n & 268435455) << 4;
    }
    public static final int isp_backgnd_t__cache_bypass = 1 << 28;
    public static final int isp_backgnd_t__shadow = 1 << 27;
    public static int isp_backgnd_t__skip(int n) {
        return (n & 7) << 24;
    }
    public static int isp_backgnd_t__tag_address(int n) {
        return (n & 2097151) << 3;
    }
    public static int isp_backgnd_t__tag_offset(int n) {
        return (n & 7) << 0;
    }
    public static int isp_feed_cfg__cache_size_for_translucency(int n) {
        return (n & 1023) << 14;
    }
    public static int isp_feed_cfg__punch_through_chunk_size(int n) {
        return (n & 1023) << 4;
    }
    public static final int isp_feed_cfg__discard_mode = 1 << 3;
    public static final int isp_feed_cfg__pre_sort_mode = 1 << 0;
    public static int sdram_refresh__refresh_counter_value(int n) {
        return (n & 255) << 0;
    }
    public static int sdram_arb_cfg__override_value__priority_only(int n) {
        return (n >> 18) & 15;
    }
    public static final int sdram_arb_cfg__override_value__rendered_data = 1 << 18;
    public static final int sdram_arb_cfg__override_value__texture_vq_index = 2 << 18;
    public static final int sdram_arb_cfg__override_value__texture_normal_data_and_vq_codebook = 3 << 18;
    public static final int sdram_arb_cfg__override_value__tile_accelerator_isp_tsp_data = 4 << 18;
    public static final int sdram_arb_cfg__override_value__tile_accelerator_pointers = 5 << 18;
    public static final int sdram_arb_cfg__override_value__sh4 = 6 << 18;
    public static final int sdram_arb_cfg__override_value__tsp_parameters = 7 << 18;
    public static final int sdram_arb_cfg__override_value__tsp_region_data = 8 << 18;
    public static final int sdram_arb_cfg__override_value__isp_pointer_data = 9 << 18;
    public static final int sdram_arb_cfg__override_value__isp_parameters = 10 << 18;
    public static final int sdram_arb_cfg__override_value__crt_controller = 11 << 18;
    public static int sdram_arb_cfg__arbiter_priority_control__priority_arbitration_only(int n) {
        return (n >> 16) & 3;
    }
    public static final int sdram_arb_cfg__arbiter_priority_control__override_value_field = 1 << 16;
    public static final int sdram_arb_cfg__arbiter_priority_control__round_robin_counter = 2 << 16;
    public static int sdram_arb_cfg__arbiter_crt_page_break_latency_count_value(int n) {
        return (n & 255) << 8;
    }
    public static int sdram_arb_cfg__arbiter_page_break_latency_count_value(int n) {
        return (n & 255) << 0;
    }
    public static int sdram_cfg__read_command_to_returned_data_delay(int n) {
        return (n & 7) << 26;
    }
    public static int sdram_cfg__cas_latency_value(int n) {
        return (n & 7) << 23;
    }
    public static int sdram_cfg__activate_to_activate_period(int n) {
        return (n & 3) << 21;
    }
    public static int sdram_cfg__read_to_write_period(int n) {
        return (n & 7) << 18;
    }
    public static int sdram_cfg__refresh_to_activate_period(int n) {
        return (n & 15) << 14;
    }
    public static int sdram_cfg__pre_charge_to_activate_period(int n) {
        return (n & 3) << 10;
    }
    public static int sdram_cfg__activate_to_pre_charge_period(int n) {
        return (n & 15) << 6;
    }
    public static int sdram_cfg__activate_to_read_write_command_period(int n) {
        return (n & 3) << 4;
    }
    public static int sdram_cfg__write_to_pre_charge_period(int n) {
        return (n & 3) << 2;
    }
    public static int sdram_cfg__read_to_pre_charge_period(int n) {
        return (n & 3) << 0;
    }
    public static int fog_col_ram__red(int n) {
        return (n & 255) << 16;
    }
    public static int fog_col_ram__green(int n) {
        return (n & 255) << 8;
    }
    public static int fog_col_ram__blue(int n) {
        return (n & 255) << 0;
    }
    public static int fog_col_vert__red(int n) {
        return (n & 255) << 16;
    }
    public static int fog_col_vert__green(int n) {
        return (n & 255) << 8;
    }
    public static int fog_col_vert__blue(int n) {
        return (n & 255) << 0;
    }
    public static int fog_density__fog_scale_mantissa(int n) {
        return (n & 255) << 8;
    }
    public static int fog_density__fog_scale_exponent(int n) {
        return (n & 255) << 0;
    }
    public static int fog_clamp_max__alpha(int n) {
        return (n & 255) << 24;
    }
    public static int fog_clamp_max__red(int n) {
        return (n & 255) << 16;
    }
    public static int fog_clamp_max__green(int n) {
        return (n & 255) << 8;
    }
    public static int fog_clamp_max__blue(int n) {
        return (n & 255) << 0;
    }
    public static int fog_clamp_min__alpha(int n) {
        return (n & 255) << 24;
    }
    public static int fog_clamp_min__red(int n) {
        return (n & 255) << 16;
    }
    public static int fog_clamp_min__green(int n) {
        return (n & 255) << 8;
    }
    public static int fog_clamp_min__blue(int n) {
        return (n & 255) << 0;
    }
    public static int spg_trigger_pos__trigger_v_count(int n) {
        return (n >> 16) & 1023;
    }
    public static int spg_trigger_pos__trigger_h_count(int n) {
        return (n >> 0) & 1023;
    }
    public static int spg_hblank_int__hblank_in_interrupt(int n) {
        return (n >> 16) & 1023;
    }
    public static int spg_hblank_int__line_comp_val(int n) {
        return (n & 1023) << 0;
    }
    public static int spg_hblank_int__hblank_int_mode__output_equal_line_comp_val(int n) {
        return (n >> 12) & 3;
    }
    public static final int spg_hblank_int__hblank_int_mode__output_every_line_comp_val = 1 << 12;
    public static final int spg_hblank_int__hblank_int_mode__output_every_line = 2 << 12;
    public static int spg_vblank_int__vblank_out_interrupt_line_number(int n) {
        return (n & 1023) << 16;
    }
    public static int spg_vblank_int__vblank_in_interrupt_line_number(int n) {
        return (n & 1023) << 0;
    }
    public static int spg_control__csync_on_h__hsync(int n) {
        return (n >> 9) & 1;
    }
    public static final int spg_control__csync_on_h__csync = 1 << 9;
    public static int spg_control__sync_direction__input(int n) {
        return (n >> 8) & 1;
    }
    public static final int spg_control__sync_direction__output = 1 << 8;
    public static final int spg_control__pal = 1 << 7;
    public static final int spg_control__ntsc = 1 << 6;
    public static final int spg_control__force_field2 = 1 << 5;
    public static final int spg_control__interlace = 1 << 4;
    public static final int spg_control__spg_lock = 1 << 3;
    public static int spg_control__mcsync_pol__active_low(int n) {
        return (n >> 2) & 1;
    }
    public static final int spg_control__mcsync_pol__active_high = 1 << 2;
    public static int spg_control__mvsync_pol__active_low(int n) {
        return (n >> 1) & 1;
    }
    public static final int spg_control__mvsync_pol__active_high = 1 << 1;
    public static int spg_control__mhsync_pol__active_low(int n) {
        return (n >> 0) & 1;
    }
    public static final int spg_control__mhsync_pol__active_high = 1 << 0;
    public static int spg_hblank__hbend(int n) {
        return (n & 1023) << 16;
    }
    public static int spg_hblank__hbstart(int n) {
        return (n & 1023) << 0;
    }
    public static int spg_load__vcount(int n) {
        return (n & 1023) << 16;
    }
    public static int spg_load__hcount(int n) {
        return (n & 1023) << 0;
    }
    public static int spg_vblank__vbend(int n) {
        return (n & 1023) << 16;
    }
    public static int spg_vblank__vbstart(int n) {
        return (n & 1023) << 0;
    }
    public static int spg_width__eqwidth(int n) {
        return (n & 1023) << 22;
    }
    public static int spg_width__bpwidth(int n) {
        return (n & 1023) << 12;
    }
    public static int spg_width__vswidth(int n) {
        return (n & 15) << 8;
    }
    public static int spg_width__hswidth(int n) {
        return (n & 127) << 0;
    }
    public static int text_control__code_book_endian__little_endian(int n) {
        return (n >> 17) & 1;
    }
    public static final int text_control__code_book_endian__big_endian = 1 << 17;
    public static int text_control__index_endian__little_endian(int n) {
        return (n >> 16) & 1;
    }
    public static final int text_control__index_endian__big_endian = 1 << 16;
    public static int text_control__bank_bit(int n) {
        return (n & 31) << 8;
    }
    public static int text_control__stride(int n) {
        return (n & 31) << 0;
    }
    public static final int vo_control__pclk_delay_reset = 1 << 21;
    public static int vo_control__pclk_delay(int n) {
        return (n & 31) << 16;
    }
    public static final int vo_control__pixel_double = 1 << 8;
    public static final int vo_control__blank_video = 1 << 3;
    public static int vo_control__field_mode__use_field_flag_from_spg(int n) {
        return (n >> 4) & 15;
    }
    public static final int vo_control__field_mode__use_inverse_of_field_flag_from_spg = 1 << 4;
    public static final int vo_control__field_mode__field_1_fixed = 2 << 4;
    public static final int vo_control__field_mode__field_2_fixed = 3 << 4;
    public static final int vo_control__field_mode__field_1_when_the_active_edges_of_hsync_and_vsync_match = 4 << 4;
    public static final int vo_control__field_mode__field_2_when_the_active_edges_of_hsync_and_vsync_match = 5 << 4;
    public static final int vo_control__field_mode__field_1_when_hsync_becomes_active_in_the_middle_of_the_vsync_active_edge = 6 << 4;
    public static final int vo_control__field_mode__field_2_when_hsync_becomes_active_in_the_middle_of_the_vsync_active_edge = 7 << 4;
    public static final int vo_control__field_mode__inverted_at_the_active_edge_of_vsync = 8 << 4;
    public static int vo_control__blank_pol__active_low(int n) {
        return (n >> 2) & 1;
    }
    public static final int vo_control__blank_pol__active_high = 1 << 2;
    public static int vo_control__vsync_pol__active_low(int n) {
        return (n >> 1) & 1;
    }
    public static final int vo_control__vsync_pol__active_high = 1 << 1;
    public static int vo_control__hsync_pol__active_low(int n) {
        return (n >> 0) & 1;
    }
    public static final int vo_control__hsync_pol__active_high = 1 << 0;
    public static int vo_startx__horizontal_start_position(int n) {
        return (n & 1023) << 0;
    }
    public static int vo_starty__vertical_start_position_on_field_2(int n) {
        return (n & 1023) << 16;
    }
    public static int vo_starty__vertical_start_position_on_field_1(int n) {
        return (n & 1023) << 0;
    }
    public static int scaler_ctl__field_select__field_1(int n) {
        return (n >> 18) & 1;
    }
    public static final int scaler_ctl__field_select__field_2 = 1 << 18;
    public static final int scaler_ctl__interlace = 1 << 17;
    public static final int scaler_ctl__horizontal_scaling_enable = 1 << 16;
    public static int scaler_ctl__vertical_scale_factor(int n) {
        return (n & 65535) << 0;
    }
    public static int pal_ram_ctrl__pixel_format__argb1555(int n) {
        return (n >> 0) & 3;
    }
    public static final int pal_ram_ctrl__pixel_format__rgb565 = 1 << 0;
    public static final int pal_ram_ctrl__pixel_format__argb4444 = 2 << 0;
    public static final int pal_ram_ctrl__pixel_format__argb8888 = 3 << 0;
    public static int spg_status__vsync(int n) {
        return (n >> 13) & 1;
    }
    public static int spg_status__hsync(int n) {
        return (n >> 12) & 1;
    }
    public static int spg_status__blank(int n) {
        return (n >> 11) & 1;
    }
    public static int spg_status__fieldnum(int n) {
        return (n >> 10) & 1;
    }
    public static int spg_status__scanline(int n) {
        return (n >> 0) & 1023;
    }
    public static int fb_burstctrl__wr_burst(int n) {
        return (n & 15) << 16;
    }
    public static int fb_burstctrl__vid_lat(int n) {
        return (n & 127) << 8;
    }
    public static int fb_burstctrl__vid_burst(int n) {
        return (n & 63) << 0;
    }
    public static int fb_c_sof__frame_buffer_current_read_address(int n) {
        return (n >> 0) & 16777215;
    }
    public static int y_coeff__coefficient_1(int n) {
        return (n & 255) << 8;
    }
    public static int y_coeff__coefficient_0_2(int n) {
        return (n & 255) << 0;
    }
    public static int pt_alpha_ref__alpha_reference_for_punch_through(int n) {
        return (n & 255) << 0;
    }
    public static int fog_table__fog_table_data(int n) {
        return (n & 65535) << 0;
    }
    public static int palette_ram__palette_data(int n) {
        return (n & -1) << 0;
    }
}
