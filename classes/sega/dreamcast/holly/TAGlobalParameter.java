package sega.dreamcast.holly;

import sega.dreamcast.MemoryMap;
import sega.dreamcast.sh7091.StoreQueueBuffer;
import jvm.internal.SH4Intrinsic;
import jvm.internal.Memory;

public class TAGlobalParameter {
    public static class end_of_list
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public end_of_list(int parameter_control_word
                           ) {
            super();
            this.parameter_control_word = parameter_control_word;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, 0);
            putInt(8, 0);
            putInt(12, 0);
            putInt(16, 0);
            putInt(20, 0);
            putInt(24, 0);
            putInt(28, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class user_tile_clip
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.user_clip_x_min = user_clip_x_min;
            this.user_clip_y_min = user_clip_y_min;
            this.user_clip_x_max = user_clip_x_max;
            this.user_clip_y_max = user_clip_y_max;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, 0);
            putInt(8, 0);
            putInt(12, 0);
            putInt(16, user_clip_x_min);
            putInt(20, user_clip_y_min);
            putInt(24, user_clip_x_max);
            putInt(28, user_clip_y_max);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class object_list_set
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public int object_pointer;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.object_pointer = object_pointer;
            this.bounding_box_x_min = bounding_box_x_min;
            this.bounding_box_y_min = bounding_box_y_min;
            this.bounding_box_x_max = bounding_box_x_max;
            this.bounding_box_y_max = bounding_box_y_max;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, object_pointer);
            putInt(8, 0);
            putInt(12, 0);
            putInt(16, bounding_box_x_min);
            putInt(20, bounding_box_y_min);
            putInt(24, bounding_box_x_max);
            putInt(28, bounding_box_y_max);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_0
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word;
        public int texture_control_word;
        public int data_size_for_sort_dma;
        public int next_address_for_sort_dma;
        public polygon_type_0(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word,
                              int texture_control_word,
                              int data_size_for_sort_dma,
                              int next_address_for_sort_dma
                              ) {
            super();
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, tsp_instruction_word);
            putInt(12, texture_control_word);
            putInt(16, 0);
            putInt(20, 0);
            putInt(24, data_size_for_sort_dma);
            putInt(28, next_address_for_sort_dma);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_1
        extends StoreQueueBuffer
    {

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
            super();
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this.face_color_alpha = face_color_alpha;
            this.face_color_r = face_color_r;
            this.face_color_g = face_color_g;
            this.face_color_b = face_color_b;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, tsp_instruction_word);
            putInt(12, texture_control_word);
            putFloat(16, face_color_alpha);
            putFloat(20, face_color_r);
            putFloat(24, face_color_g);
            putFloat(28, face_color_b);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_2
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public int tsp_instruction_word;
        public int texture_control_word;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
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
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, tsp_instruction_word);
            putInt(12, texture_control_word);
            putInt(16, 0);
            putInt(20, 0);
            putInt(24, data_size_for_sort_dma);
            putInt(28, next_address_for_sort_dma);
            putFloat(32, face_color_alpha);
            putFloat(36, face_color_r);
            putFloat(40, face_color_g);
            putFloat(44, face_color_b);
            putFloat(48, face_offset_color_alpha);
            putFloat(52, face_offset_color_r);
            putFloat(56, face_offset_color_g);
            putFloat(60, face_offset_color_b);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_3
        extends StoreQueueBuffer
    {

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
            super();
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word_0 = tsp_instruction_word_0;
            this.texture_control_word_0 = texture_control_word_0;
            this.tsp_instruction_word_1 = tsp_instruction_word_1;
            this.texture_control_word_1 = texture_control_word_1;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, tsp_instruction_word_0);
            putInt(12, texture_control_word_0);
            putInt(16, tsp_instruction_word_1);
            putInt(20, texture_control_word_1);
            putInt(24, data_size_for_sort_dma);
            putInt(28, next_address_for_sort_dma);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_4
        extends StoreQueueBuffer
    {

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
            super();
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
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, tsp_instruction_word_0);
            putInt(12, texture_control_word_0);
            putInt(16, tsp_instruction_word_1);
            putInt(20, texture_control_word_1);
            putInt(24, data_size_for_sort_dma);
            putInt(28, next_address_for_sort_dma);
            putFloat(32, face_color_alpha_0);
            putFloat(36, face_color_r_0);
            putFloat(40, face_color_g_0);
            putFloat(44, face_color_b_0);
            putFloat(48, face_color_alpha_1);
            putFloat(52, face_color_r_1);
            putFloat(56, face_color_g_1);
            putFloat(60, face_color_b_1);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class sprite
        extends StoreQueueBuffer
    {

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
            super();
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
            this.tsp_instruction_word = tsp_instruction_word;
            this.texture_control_word = texture_control_word;
            this.base_color = base_color;
            this.offset_color = offset_color;
            this.data_size_for_sort_dma = data_size_for_sort_dma;
            this.next_address_for_sort_dma = next_address_for_sort_dma;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, tsp_instruction_word);
            putInt(12, texture_control_word);
            putInt(16, base_color);
            putInt(20, offset_color);
            putInt(24, data_size_for_sort_dma);
            putInt(28, next_address_for_sort_dma);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class modifier_volume
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public int isp_tsp_instruction_word;
        public modifier_volume(int parameter_control_word,
                               int isp_tsp_instruction_word
                               ) {
            super();
            this.parameter_control_word = parameter_control_word;
            this.isp_tsp_instruction_word = isp_tsp_instruction_word;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putInt(4, isp_tsp_instruction_word);
            putInt(8, 0);
            putInt(12, 0);
            putInt(16, 0);
            putInt(20, 0);
            putInt(24, 0);
            putInt(28, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
}
