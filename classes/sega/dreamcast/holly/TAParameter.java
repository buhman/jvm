package sega.dreamcast.holly;

public class TAParameter {
    public static final int para_control__para_type__end_of_list = 0 << 29;
    public static final int para_control__para_type__user_tile_clip = 1 << 29;
    public static final int para_control__para_type__object_list_set = 2 << 29;
    public static final int para_control__para_type__polygon_or_modifier_volume = 4 << 29;
    public static final int para_control__para_type__sprite = 5 << 29;
    public static final int para_control__para_type__vertex_parameter = 7 << 29;
    public static final int para_control__end_of_strip = 1 << 28;
    public static final int para_control__list_type__opaque = 0 << 24;
    public static final int para_control__list_type__opaque_modifier_volume = 1 << 24;
    public static final int para_control__list_type__translucent = 2 << 24;
    public static final int para_control__list_type__translucent_modifier_volume = 3 << 24;
    public static final int para_control__list_type__punch_through = 4 << 24;
    public static final int group_control__group_en__group_en = 1 << 23;
    public static final int group_control__strip_len__1_strip = 0 << 18;
    public static final int group_control__strip_len__2_strip = 1 << 18;
    public static final int group_control__strip_len__4_strip = 2 << 18;
    public static final int group_control__strip_len__6_strip = 3 << 18;
    public static final int group_control__user_clip__disabled = 0 << 16;
    public static final int group_control__user_clip__inside_enable = 2 << 16;
    public static final int group_control__user_clip__outside_enable = 3 << 16;
    public static final int obj_control__shadow = 1 << 7;
    public static final int obj_control__texture = 1 << 3;
    public static final int obj_control__offset = 1 << 2;
    public static final int obj_control__gouraud = 1 << 1;
    public static final int obj_control__16bit_uv = 1 << 0;
    public static final int obj_control__volume__with_two_volumes = 1 << 6;
    public static final int obj_control__volume__last_in_volume = 1 << 6;
    public static final int obj_control__col_type__packed_color = 0 << 4;
    public static final int obj_control__col_type__floating_color = 1 << 4;
    public static final int obj_control__col_type__intensity_mode_1 = 2 << 4;
    public static final int obj_control__col_type__intensity_mode_2 = 3 << 4;
}
