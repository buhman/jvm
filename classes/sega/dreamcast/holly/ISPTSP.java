package sega.dreamcast.holly;

public class ISPTSP {
    public static final int isp_tsp_instruction_word__depth_compare_mode__never = 0 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__less = 1 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__equal = 2 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__less_or_equal = 3 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__greater = 4 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__greater_or_equal = 5 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__not_equal = 6 << 29;
    public static final int isp_tsp_instruction_word__depth_compare_mode__always = 7 << 29;
    public static final int isp_tsp_instruction_word__volume_instruction__normal_polygon = 0 << 29;
    public static final int isp_tsp_instruction_word__volume_instruction__inside_last_polygon = 1 << 29;
    public static final int isp_tsp_instruction_word__volume_instruction__outside_last_polygon = 2 << 29;
    public static final int isp_tsp_instruction_word__culling_mode__no_culling = 0 << 27;
    public static final int isp_tsp_instruction_word__culling_mode__cull_if_small = 1 << 27;
    public static final int isp_tsp_instruction_word__culling_mode__cull_if_negative = 2 << 27;
    public static final int isp_tsp_instruction_word__culling_mode__cull_if_positive = 3 << 27;
    public static final int isp_tsp_instruction_word__z_write_disable = 1 << 26;
    public static final int isp_tsp_instruction_word__texture = 1 << 25;
    public static final int isp_tsp_instruction_word__offset = 1 << 24;
    public static final int isp_tsp_instruction_word__gouraud_shading = 1 << 23;
    public static final int isp_tsp_instruction_word__16bit_uv = 1 << 22;
    public static final int isp_tsp_instruction_word__cache_bypass = 1 << 21;
    public static final int isp_tsp_instruction_word__dcalc_ctrl = 1 << 20;
    public static final int tsp_instruction_word__src_alpha_instr__zero = 0 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__one = 1 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__other_color = 2 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__inverse_other_color = 3 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__src_alpha = 4 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__inverse_src_alpha = 5 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__dst_alpha = 6 << 29;
    public static final int tsp_instruction_word__src_alpha_instr__inverse_dst_alpha = 7 << 29;
    public static final int tsp_instruction_word__dst_alpha_instr__zero = 0 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__one = 1 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__other_color = 2 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__inverse_other_color = 3 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__src_alpha = 4 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__inverse_src_alpha = 5 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__dst_alpha = 6 << 26;
    public static final int tsp_instruction_word__dst_alpha_instr__inverse_dst_alpha = 7 << 26;
    public static final int tsp_instruction_word__src_select__primary_accumulation_buffer = 0 << 25;
    public static final int tsp_instruction_word__src_select__secondary_accumulation_buffer = 1 << 25;
    public static final int tsp_instruction_word__dst_select__primary_accumulation_buffer = 0 << 24;
    public static final int tsp_instruction_word__dst_select__secondary_accumulation_buffer = 1 << 24;
    public static final int tsp_instruction_word__fog_control__look_up_table = 0 << 22;
    public static final int tsp_instruction_word__fog_control__per_vertex = 1 << 22;
    public static final int tsp_instruction_word__fog_control__no_fog = 2 << 22;
    public static final int tsp_instruction_word__fog_control__look_up_table_mode_2 = 3 << 22;
    public static final int tsp_instruction_word__color_clamp = 1 << 21;
    public static final int tsp_instruction_word__use_alpha = 1 << 20;
    public static final int tsp_instruction_word__ignore_texture_alpha = 1 << 19;
    public static final int tsp_instruction_word__super_sample_texture = 1 << 12;
    public static int tsp_instruction_word__mip_map_d_adjust(int n) {
        return (n & 15) << 8;
    }
    public static final int tsp_instruction_word__flip_uv__none = 0 << 17;
    public static final int tsp_instruction_word__flip_uv__v = 1 << 17;
    public static final int tsp_instruction_word__flip_uv__u = 2 << 17;
    public static final int tsp_instruction_word__flip_uv__uv = 3 << 17;
    public static final int tsp_instruction_word__clamp_uv__none = 0 << 15;
    public static final int tsp_instruction_word__clamp_uv__v = 1 << 15;
    public static final int tsp_instruction_word__clamp_uv__u = 2 << 15;
    public static final int tsp_instruction_word__clamp_uv__uv = 3 << 15;
    public static final int tsp_instruction_word__filter_mode__point_sampled = 0 << 13;
    public static final int tsp_instruction_word__filter_mode__bilinear_filter = 1 << 13;
    public static final int tsp_instruction_word__filter_mode__trilinear_pass_a = 2 << 13;
    public static final int tsp_instruction_word__filter_mode__trilinear_pass_b = 3 << 13;
    public static final int tsp_instruction_word__texture_shading_instruction__decal = 0 << 6;
    public static final int tsp_instruction_word__texture_shading_instruction__modulate = 1 << 6;
    public static final int tsp_instruction_word__texture_shading_instruction__decal_alpha = 2 << 6;
    public static final int tsp_instruction_word__texture_shading_instruction__modulate_alpha = 3 << 6;
    public static final int tsp_instruction_word__texture_u_size__8 = 0 << 3;
    public static final int tsp_instruction_word__texture_u_size__16 = 1 << 3;
    public static final int tsp_instruction_word__texture_u_size__32 = 2 << 3;
    public static final int tsp_instruction_word__texture_u_size__64 = 3 << 3;
    public static final int tsp_instruction_word__texture_u_size__128 = 4 << 3;
    public static final int tsp_instruction_word__texture_u_size__256 = 5 << 3;
    public static final int tsp_instruction_word__texture_u_size__512 = 6 << 3;
    public static final int tsp_instruction_word__texture_u_size__1024 = 7 << 3;
    public static final int tsp_instruction_word__texture_v_size__8 = 0 << 0;
    public static final int tsp_instruction_word__texture_v_size__16 = 1 << 0;
    public static final int tsp_instruction_word__texture_v_size__32 = 2 << 0;
    public static final int tsp_instruction_word__texture_v_size__64 = 3 << 0;
    public static final int tsp_instruction_word__texture_v_size__128 = 4 << 0;
    public static final int tsp_instruction_word__texture_v_size__256 = 5 << 0;
    public static final int tsp_instruction_word__texture_v_size__512 = 6 << 0;
    public static final int tsp_instruction_word__texture_v_size__1024 = 7 << 0;
    public static final int texture_control_word__mip_mapped = 1 << 31;
    public static final int texture_control_word__vq_compressed = 1 << 30;
    public static int texture_control_word__palette_selector4(int n) {
        return (n & 63) << 21;
    }
    public static int texture_control_word__palette_selector8(int n) {
        return (n & 3) << 25;
    }
    public static int texture_control_word__stride_select(int n) {
        return (n >> 25) & 1;
    }
    public static int texture_control_word__texture_address(int n) {
        return (n & 2097151) << 0;
    }
    public static final int texture_control_word__pixel_format__1555 = 0 << 27;
    public static final int texture_control_word__pixel_format__565 = 1 << 27;
    public static final int texture_control_word__pixel_format__4444 = 2 << 27;
    public static final int texture_control_word__pixel_format__yuv422 = 3 << 27;
    public static final int texture_control_word__pixel_format__bump_map = 4 << 27;
    public static final int texture_control_word__pixel_format__4bpp_palette = 5 << 27;
    public static final int texture_control_word__pixel_format__8bpp_palette = 6 << 27;
    public static final int texture_control_word__scan_order__twiddled = 0 << 26;
    public static final int texture_control_word__scan_order__non_twiddled = 1 << 26;
}
