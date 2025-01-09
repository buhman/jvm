package sega.dreamcast.holly;


public class TAVertexParameter {
    public static class polygon_type_0 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int _res0;
        public int _res1;
        public int base_color;
        public int _res2;
        public polygon_type_0(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int base_color
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this._res0 = 0;
            this._res1 = 0;
            this.base_color = base_color;
            this._res2 = 0;
        }
    }
    public static class polygon_type_1 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float base_color_alpha;
        public float base_color_r;
        public float base_color_g;
        public float base_color_b;
        public polygon_type_1(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              float base_color_alpha,
                              float base_color_r,
                              float base_color_g,
                              float base_color_b
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_color_alpha = base_color_alpha;
            this.base_color_r = base_color_r;
            this.base_color_g = base_color_g;
            this.base_color_b = base_color_b;
        }
    }
    public static class polygon_type_2 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int _res0;
        public int _res1;
        public float base_intensity;
        public int _res2;
        public polygon_type_2(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              float base_intensity
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this._res0 = 0;
            this._res1 = 0;
            this.base_intensity = base_intensity;
            this._res2 = 0;
        }
    }
    public static class polygon_type_3 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float u;
        public float v;
        public int base_color;
        public int offset_color;
        public polygon_type_3(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              float u,
                              float v,
                              int base_color,
                              int offset_color
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this.base_color = base_color;
            this.offset_color = offset_color;
        }
    }
    public static class polygon_type_4 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v;
        public int _res0;
        public int base_color;
        public int offset_color;
        public polygon_type_4(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int u_v,
                              int base_color,
                              int offset_color
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v = u_v;
            this._res0 = 0;
            this.base_color = base_color;
            this.offset_color = offset_color;
        }
    }
    public static class polygon_type_5 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float u;
        public float v;
        public int _res0;
        public int _res1;
        public float base_color_alpha;
        public float base_color_r;
        public float base_color_g;
        public float base_color_b;
        public float offset_color_alpha;
        public float offset_color_r;
        public float offset_color_g;
        public float offset_color_b;
        public polygon_type_5(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              float u,
                              float v,
                              float base_color_alpha,
                              float base_color_r,
                              float base_color_g,
                              float base_color_b,
                              float offset_color_alpha,
                              float offset_color_r,
                              float offset_color_g,
                              float offset_color_b
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this._res0 = 0;
            this._res1 = 0;
            this.base_color_alpha = base_color_alpha;
            this.base_color_r = base_color_r;
            this.base_color_g = base_color_g;
            this.base_color_b = base_color_b;
            this.offset_color_alpha = offset_color_alpha;
            this.offset_color_r = offset_color_r;
            this.offset_color_g = offset_color_g;
            this.offset_color_b = offset_color_b;
        }
    }
    public static class polygon_type_6 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v;
        public int _res0;
        public int _res1;
        public int _res2;
        public float base_color_alpha;
        public float base_color_r;
        public float base_color_g;
        public float base_color_b;
        public float offset_color_alpha;
        public float offset_color_r;
        public float offset_color_g;
        public float offset_color_b;
        public polygon_type_6(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int u_v,
                              float base_color_alpha,
                              float base_color_r,
                              float base_color_g,
                              float base_color_b,
                              float offset_color_alpha,
                              float offset_color_r,
                              float offset_color_g,
                              float offset_color_b
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v = u_v;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this.base_color_alpha = base_color_alpha;
            this.base_color_r = base_color_r;
            this.base_color_g = base_color_g;
            this.base_color_b = base_color_b;
            this.offset_color_alpha = offset_color_alpha;
            this.offset_color_r = offset_color_r;
            this.offset_color_g = offset_color_g;
            this.offset_color_b = offset_color_b;
        }
    }
    public static class polygon_type_7 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float u;
        public float v;
        public float base_intensity;
        public float offset_intensity;
        public polygon_type_7(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              float u,
                              float v,
                              float base_intensity,
                              float offset_intensity
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this.base_intensity = base_intensity;
            this.offset_intensity = offset_intensity;
        }
    }
    public static class polygon_type_8 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v;
        public int _res0;
        public float base_intensity;
        public float offset_intensity;
        public polygon_type_8(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int u_v,
                              float base_intensity,
                              float offset_intensity
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v = u_v;
            this._res0 = 0;
            this.base_intensity = base_intensity;
            this.offset_intensity = offset_intensity;
        }
    }
    public static class polygon_type_9 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int base_color_0;
        public int base_color_1;
        public int _res0;
        public int _res1;
        public polygon_type_9(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int base_color_0,
                              int base_color_1
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_color_0 = base_color_0;
            this.base_color_1 = base_color_1;
            this._res0 = 0;
            this._res1 = 0;
        }
    }
    public static class polygon_type_10 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int base_intensity_0;
        public int base_intensity_1;
        public int _res0;
        public int _res1;
        public polygon_type_10(int parameter_control_word,
                               float x,
                               float y,
                               float z,
                               int base_intensity_0,
                               int base_intensity_1
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_intensity_0 = base_intensity_0;
            this.base_intensity_1 = base_intensity_1;
            this._res0 = 0;
            this._res1 = 0;
        }
    }
    public static class polygon_type_11 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float u_0;
        public float v_0;
        public int base_color_0;
        public int offset_color_0;
        public float u_1;
        public float v_1;
        public int base_color_1;
        public int offset_color_1;
        public int _res0;
        public int _res1;
        public int _res2;
        public int _res3;
        public polygon_type_11(int parameter_control_word,
                               float x,
                               float y,
                               float z,
                               float u_0,
                               float v_0,
                               int base_color_0,
                               int offset_color_0,
                               float u_1,
                               float v_1,
                               int base_color_1,
                               int offset_color_1
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_0 = u_0;
            this.v_0 = v_0;
            this.base_color_0 = base_color_0;
            this.offset_color_0 = offset_color_0;
            this.u_1 = u_1;
            this.v_1 = v_1;
            this.base_color_1 = base_color_1;
            this.offset_color_1 = offset_color_1;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
        }
    }
    public static class polygon_type_12 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v_0;
        public int _res0;
        public int base_color_0;
        public int offset_color_0;
        public int u_v_1;
        public int _res1;
        public int base_color_1;
        public int offset_color_1;
        public int _res2;
        public int _res3;
        public int _res4;
        public int _res5;
        public polygon_type_12(int parameter_control_word,
                               float x,
                               float y,
                               float z,
                               int u_v_0,
                               int base_color_0,
                               int offset_color_0,
                               int u_v_1,
                               int base_color_1,
                               int offset_color_1
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v_0 = u_v_0;
            this._res0 = 0;
            this.base_color_0 = base_color_0;
            this.offset_color_0 = offset_color_0;
            this.u_v_1 = u_v_1;
            this._res1 = 0;
            this.base_color_1 = base_color_1;
            this.offset_color_1 = offset_color_1;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
        }
    }
    public static class polygon_type_13 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float u_0;
        public float v_0;
        public int base_intensity_0;
        public float offset_intensity_0;
        public float u_1;
        public float v_1;
        public int base_intensity_1;
        public float offset_intensity_1;
        public int _res0;
        public int _res1;
        public int _res2;
        public int _res3;
        public polygon_type_13(int parameter_control_word,
                               float x,
                               float y,
                               float z,
                               float u_0,
                               float v_0,
                               int base_intensity_0,
                               float offset_intensity_0,
                               float u_1,
                               float v_1,
                               int base_intensity_1,
                               float offset_intensity_1
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_0 = u_0;
            this.v_0 = v_0;
            this.base_intensity_0 = base_intensity_0;
            this.offset_intensity_0 = offset_intensity_0;
            this.u_1 = u_1;
            this.v_1 = v_1;
            this.base_intensity_1 = base_intensity_1;
            this.offset_intensity_1 = offset_intensity_1;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
        }
    }
    public static class polygon_type_14 {
        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v_0;
        public int _res0;
        public int base_intensity_0;
        public float offset_intensity_0;
        public int u_v_1;
        public int _res1;
        public int base_intensity_1;
        public float offset_intensity_1;
        public int _res2;
        public int _res3;
        public int _res4;
        public int _res5;
        public polygon_type_14(int parameter_control_word,
                               float x,
                               float y,
                               float z,
                               int u_v_0,
                               int base_intensity_0,
                               float offset_intensity_0,
                               int u_v_1,
                               int base_intensity_1,
                               float offset_intensity_1
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v_0 = u_v_0;
            this._res0 = 0;
            this.base_intensity_0 = base_intensity_0;
            this.offset_intensity_0 = offset_intensity_0;
            this.u_v_1 = u_v_1;
            this._res1 = 0;
            this.base_intensity_1 = base_intensity_1;
            this.offset_intensity_1 = offset_intensity_1;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
        }
    }
    public static class sprite_type_0 {
        public int parameter_control_word;
        public float a_x;
        public float a_y;
        public float a_z;
        public float b_x;
        public float b_y;
        public float b_z;
        public float c_x;
        public float c_y;
        public float c_z;
        public float d_x;
        public float d_y;
        public int _res0;
        public int _res1;
        public int _res2;
        public int _res3;
        public sprite_type_0(int parameter_control_word,
                             float a_x,
                             float a_y,
                             float a_z,
                             float b_x,
                             float b_y,
                             float b_z,
                             float c_x,
                             float c_y,
                             float c_z,
                             float d_x,
                             float d_y
                             ) {
            this.parameter_control_word = parameter_control_word;
            this.a_x = a_x;
            this.a_y = a_y;
            this.a_z = a_z;
            this.b_x = b_x;
            this.b_y = b_y;
            this.b_z = b_z;
            this.c_x = c_x;
            this.c_y = c_y;
            this.c_z = c_z;
            this.d_x = d_x;
            this.d_y = d_y;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
        }
    }
    public static class sprite_type_1 {
        public int parameter_control_word;
        public float a_x;
        public float a_y;
        public float a_z;
        public float b_x;
        public float b_y;
        public float b_z;
        public float c_x;
        public float c_y;
        public float c_z;
        public float d_x;
        public float d_y;
        public int _res0;
        public int a_u_a_v;
        public int b_u_b_v;
        public int c_u_c_v;
        public sprite_type_1(int parameter_control_word,
                             float a_x,
                             float a_y,
                             float a_z,
                             float b_x,
                             float b_y,
                             float b_z,
                             float c_x,
                             float c_y,
                             float c_z,
                             float d_x,
                             float d_y,
                             int a_u_a_v,
                             int b_u_b_v,
                             int c_u_c_v
                             ) {
            this.parameter_control_word = parameter_control_word;
            this.a_x = a_x;
            this.a_y = a_y;
            this.a_z = a_z;
            this.b_x = b_x;
            this.b_y = b_y;
            this.b_z = b_z;
            this.c_x = c_x;
            this.c_y = c_y;
            this.c_z = c_z;
            this.d_x = d_x;
            this.d_y = d_y;
            this._res0 = 0;
            this.a_u_a_v = a_u_a_v;
            this.b_u_b_v = b_u_b_v;
            this.c_u_c_v = c_u_c_v;
        }
    }
    public static class modifier_volume {
        public int parameter_control_word;
        public float a_x;
        public float a_y;
        public float a_z;
        public float b_x;
        public float b_y;
        public float b_z;
        public float c_x;
        public float c_y;
        public float c_z;
        public int _res0;
        public int _res1;
        public int _res2;
        public int _res3;
        public int _res4;
        public int _res5;
        public modifier_volume(int parameter_control_word,
                               float a_x,
                               float a_y,
                               float a_z,
                               float b_x,
                               float b_y,
                               float b_z,
                               float c_x,
                               float c_y,
                               float c_z
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.a_x = a_x;
            this.a_y = a_y;
            this.a_z = a_z;
            this.b_x = b_x;
            this.b_y = b_y;
            this.b_z = b_z;
            this.c_x = c_x;
            this.c_y = c_y;
            this.c_z = c_z;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
        }
    }
}
