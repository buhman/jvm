package sega.dreamcast.holly;

public class TABits {
    public static int ta_ol_base__base_address(int n) {
        return (n & 16777184) << 0;
    }
    public static int ta_isp_base__base_address(int n) {
        return (n & 16777212) << 0;
    }
    public static int ta_ol_limit__limit_address(int n) {
        return (n & 16777184) << 0;
    }
    public static int ta_isp_limit__limit_address(int n) {
        return (n & 16777212) << 0;
    }
    public static int ta_next_opb__address(int n) {
        return (n & 16777184) << 0;
    }
    public static int ta_itp_current__address(int n) {
        return (n >> 0) & 16777215;
    }
    public static int ta_glob_tile_clip__tile_y_num(int n) {
        return (n & 15) << 16;
    }
    public static int ta_glob_tile_clip__tile_x_num(int n) {
        return (n & 31) << 0;
    }
    public static final int ta_alloc_ctrl__opb_mode__increasing_addresses = 0 << 20;
    public static final int ta_alloc_ctrl__opb_mode__decreasing_addresses = 1 << 20;
    public static final int ta_alloc_ctrl__pt_opb__no_list = 0 << 16;
    public static final int ta_alloc_ctrl__pt_opb__8x4byte = 1 << 16;
    public static final int ta_alloc_ctrl__pt_opb__16x4byte = 2 << 16;
    public static final int ta_alloc_ctrl__pt_opb__32x4byte = 3 << 16;
    public static final int ta_alloc_ctrl__tm_opb__no_list = 0 << 12;
    public static final int ta_alloc_ctrl__tm_opb__8x4byte = 1 << 12;
    public static final int ta_alloc_ctrl__tm_opb__16x4byte = 2 << 12;
    public static final int ta_alloc_ctrl__tm_opb__32x4byte = 3 << 12;
    public static final int ta_alloc_ctrl__t_opb__no_list = 0 << 8;
    public static final int ta_alloc_ctrl__t_opb__8x4byte = 1 << 8;
    public static final int ta_alloc_ctrl__t_opb__16x4byte = 2 << 8;
    public static final int ta_alloc_ctrl__t_opb__32x4byte = 3 << 8;
    public static final int ta_alloc_ctrl__om_opb__no_list = 0 << 4;
    public static final int ta_alloc_ctrl__om_opb__8x4byte = 1 << 4;
    public static final int ta_alloc_ctrl__om_opb__16x4byte = 2 << 4;
    public static final int ta_alloc_ctrl__om_opb__32x4byte = 3 << 4;
    public static final int ta_alloc_ctrl__o_opb__no_list = 0 << 0;
    public static final int ta_alloc_ctrl__o_opb__8x4byte = 1 << 0;
    public static final int ta_alloc_ctrl__o_opb__16x4byte = 2 << 0;
    public static final int ta_alloc_ctrl__o_opb__32x4byte = 3 << 0;
    public static final int ta_list_init__list_init = 1 << 31;
    public static int ta_yuv_tex_base__base_address(int n) {
        return (n & 16777208) << 0;
    }
    public static final int ta_yuv_tex_ctrl__yuv_form__yuv420 = 0 << 24;
    public static final int ta_yuv_tex_ctrl__yuv_form__yuv422 = 1 << 24;
    public static final int ta_yuv_tex_ctrl__yuv_tex__one_texture = 0 << 16;
    public static final int ta_yuv_tex_ctrl__yuv_tex__multiple_textures = 1 << 16;
    public static int ta_yuv_tex_ctrl__yuv_v_size(int n) {
        return (n & 63) << 8;
    }
    public static int ta_yuv_tex_ctrl__yuv_u_size(int n) {
        return (n & 63) << 0;
    }
    public static int ta_yuv_tex_cnt__yuv_num(int n) {
        return (n >> 0) & 8191;
    }
    public static final int ta_list_cont__list_cont = 1 << 31;
    public static int ta_next_opb_init__address(int n) {
        return (n & 16777184) << 0;
    }
    public static int ta_ol_pointers__entry(int n) {
        return (n >> 31) & 1;
    }
    public static int ta_ol_pointers__sprite(int n) {
        return (n >> 30) & 1;
    }
    public static int ta_ol_pointers__triangle(int n) {
        return (n >> 29) & 1;
    }
    public static int ta_ol_pointers__number_of_triangles_quads(int n) {
        return (n >> 25) & 15;
    }
    public static int ta_ol_pointers__shadow(int n) {
        return (n >> 24) & 1;
    }
    public static int ta_ol_pointers__pointer_address(int n) {
        return (n >> 2) & 4194303;
    }
    public static int ta_ol_pointers__skip(int n) {
        return (n >> 0) & 3;
    }
}
