package sega.dreamcast.holly;


public class TAGlobalParameter {
    public class end_of_list {
        public int parameter_control_word;
        public int _res0;
        public int _res1;
        public int _res2;
        public int _res3;
        public int _res4;
        public int _res5;
        public int _res6;
        public end_of_list(int parameter_control_word
                           ) {
            this.parameter_control_word = parameter_control_word;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
        }
    }
    public class user_tile_clip {
        public int parameter_control_word;
        public int _res0;
        public int _res1;
        public int _res2;
        public int user_clip_x_min;
        public int user_clip_y_min;
        public int user_clip_x_max;
        public int user_clip_y_max;
        public user_tile_clip(int parameter_control_word,
                              int user_clip_x_min,
                              int user_clip_y_min,
                              int user_clip_x_max,
                              int user_clip_y_max
                              ) {
            this.parameter_control_word = parameter_control_word;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this.user_clip_x_min = user_clip_x_min;
            this.user_clip_y_min = user_clip_y_min;
            this.user_clip_x_max = user_clip_x_max;
            this.user_clip_y_max = user_clip_y_max;
        }
    }
    public class object_list_set {
        public int parameter_control_word;
        public int object_pointer;
        public int _res0;
        public int _res1;
        public int bounding_box_x_min;
        public int bounding_box_y_min;
        public int bounding_box_x_max;
        public int bounding_box_y_max;
        public object_list_set(int parameter_control_word,
                               int object_pointer,
                               int bounding_box_x_min,
                               int bounding_box_y_min,
                               int bounding_box_x_max,
                               int bounding_box_y_max
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.object_pointer = object_pointer;
            this._res0 = 0;
            this._res1 = 0;
            this.bounding_box_x_min = bounding_box_x_min;
            this.bounding_box_y_min = bounding_box_y_min;
            this.bounding_box_x_max = bounding_box_x_max;
            this.bounding_box_y_max = bounding_box_y_max;
        }
    }
    public class polygon_type_0 {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word;
        public int texture_control_word;
        public int _res0;
        public int _res1;
        public int data_size_for_sort_dma;
        public int next_address_for_sort_dma;
        public polygon_type_0(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word,
                              int texture_control_word,
                              int data_size_for_sort_dma,
                              int next_address_for_sort_dma
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this._res0 = 0;
            this._res1 = 0;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
        }
    }
    public class polygon_type_1 {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word;
        public int texture_control_word;
        public float face_color_alpha;
        public float face_color_r;
        public float face_color_g;
        public float face_color_b;
        public polygon_type_1(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word,
                              int texture_control_word,
                              float face_color_alpha,
                              float face_color_r,
                              float face_color_g,
                              float face_color_b
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this.face_color_alpha = face_color_alpha;
            this.face_color_r = face_color_r;
            this.face_color_g = face_color_g;
            this.face_color_b = face_color_b;
        }
    }
    public class polygon_type_2 {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word;
        public int texture_control_word;
        public int _res0;
        public int _res1;
        public int data_size_for_sort_dma;
        public int next_address_for_sort_dma;
        public float face_color_alpha;
        public float face_color_r;
        public float face_color_g;
        public float face_color_b;
        public float face_offset_color_alpha;
        public float face_offset_color_r;
        public float face_offset_color_g;
        public float face_offset_color_b;
        public polygon_type_2(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word,
                              int texture_control_word,
                              int data_size_for_sort_dma,
                              int next_address_for_sort_dma,
                              float face_color_alpha,
                              float face_color_r,
                              float face_color_g,
                              float face_color_b,
                              float face_offset_color_alpha,
                              float face_offset_color_r,
                              float face_offset_color_g,
                              float face_offset_color_b
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this._res0 = 0;
            this._res1 = 0;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
            this.face_color_alpha = face_color_alpha;
            this.face_color_r = face_color_r;
            this.face_color_g = face_color_g;
            this.face_color_b = face_color_b;
            this.face_offset_color_alpha = face_offset_color_alpha;
            this.face_offset_color_r = face_offset_color_r;
            this.face_offset_color_g = face_offset_color_g;
            this.face_offset_color_b = face_offset_color_b;
        }
    }
    public class polygon_type_3 {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word_0;
        public int texture_control_word_0;
        public int tsp_instruction_word_1;
        public int texture_control_word_1;
        public int data_size_for_sort_dma;
        public int next_address_for_sort_dma;
        public polygon_type_3(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word_0,
                              int texture_control_word_0,
                              int tsp_instruction_word_1,
                              int texture_control_word_1,
                              int data_size_for_sort_dma,
                              int next_address_for_sort_dma
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word_0 = tsp_instruction_word_0;
            this.texture_control_word_0 = texture_control_word_0;
            this.tsp_instruction_word_1 = tsp_instruction_word_1;
            this.texture_control_word_1 = texture_control_word_1;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
        }
    }
    public class polygon_type_4 {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word_0;
        public int texture_control_word_0;
        public int tsp_instruction_word_1;
        public int texture_control_word_1;
        public int data_size_for_sort_dma;
        public int next_address_for_sort_dma;
        public float face_color_alpha_0;
        public float face_color_r_0;
        public float face_color_g_0;
        public float face_color_b_0;
        public float face_color_alpha_1;
        public float face_color_r_1;
        public float face_color_g_1;
        public float face_color_b_1;
        public polygon_type_4(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word_0,
                              int texture_control_word_0,
                              int tsp_instruction_word_1,
                              int texture_control_word_1,
                              int data_size_for_sort_dma,
                              int next_address_for_sort_dma,
                              float face_color_alpha_0,
                              float face_color_r_0,
                              float face_color_g_0,
                              float face_color_b_0,
                              float face_color_alpha_1,
                              float face_color_r_1,
                              float face_color_g_1,
                              float face_color_b_1
                              ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word_0 = tsp_instruction_word_0;
            this.texture_control_word_0 = texture_control_word_0;
            this.tsp_instruction_word_1 = tsp_instruction_word_1;
            this.texture_control_word_1 = texture_control_word_1;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
            this.face_color_alpha_0 = face_color_alpha_0;
            this.face_color_r_0 = face_color_r_0;
            this.face_color_g_0 = face_color_g_0;
            this.face_color_b_0 = face_color_b_0;
            this.face_color_alpha_1 = face_color_alpha_1;
            this.face_color_r_1 = face_color_r_1;
            this.face_color_g_1 = face_color_g_1;
            this.face_color_b_1 = face_color_b_1;
        }
    }
    public class sprite {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word;
        public int texture_control_word;
        public int base_color;
        public int offset_color;
        public int data_size_for_sort_dma;
        public int next_address_for_sort_dma;
        public sprite(int parameter_control_word,
                      int isp_tsp_instruction_word,
                      int tsp_instruction_word,
                      int texture_control_word,
                      int base_color,
                      int offset_color,
                      int data_size_for_sort_dma,
                      int next_address_for_sort_dma
                      ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this.base_color = base_color;
            this.offset_color = offset_color;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
        }
    }
    public class modifier_volume {
        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int _res0;
        public int _res1;
        public int _res2;
        public int _res3;
        public int _res4;
        public int _res5;
        public modifier_volume(int parameter_control_word,
                               int isp_tsp_instruction_word
                               ) {
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
        }
    }
}
