package sega.dreamcast.holly;

import sega.dreamcast.MemoryMap;
import jvm.internal.SH4Intrinsic;
import jvm.internal.Memory;

public class TAGlobalParameter {
    public static void end_of_list(int parameter_control_word
                                   ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, 0);
        Memory.putU4(store_queue + 8, 0);
        Memory.putU4(store_queue + 12, 0);
        Memory.putU4(store_queue + 16, 0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, 0);
        Memory.putU4(store_queue + 28, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void user_tile_clip(int parameter_control_word,
                                      int user_clip_x_min,
                                      int user_clip_y_min,
                                      int user_clip_x_max,
                                      int user_clip_y_max
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, 0);
        Memory.putU4(store_queue + 8, 0);
        Memory.putU4(store_queue + 12, 0);
        Memory.putU4(store_queue + 16, user_clip_x_min);
        Memory.putU4(store_queue + 20, user_clip_y_min);
        Memory.putU4(store_queue + 24, user_clip_x_max);
        Memory.putU4(store_queue + 28, user_clip_y_max);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void object_list_set(int parameter_control_word,
                                       int object_pointer,
                                       int bounding_box_x_min,
                                       int bounding_box_y_min,
                                       int bounding_box_x_max,
                                       int bounding_box_y_max
                                       ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, object_pointer);
        Memory.putU4(store_queue + 8, 0);
        Memory.putU4(store_queue + 12, 0);
        Memory.putU4(store_queue + 16, bounding_box_x_min);
        Memory.putU4(store_queue + 20, bounding_box_y_min);
        Memory.putU4(store_queue + 24, bounding_box_x_max);
        Memory.putU4(store_queue + 28, bounding_box_y_max);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_0(int parameter_control_word,
                                      int isp_tsp_instruction_word,
                                      int tsp_instruction_word,
                                      int texture_control_word,
                                      int data_size_for_sort_dma,
                                      int next_address_for_sort_dma
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, tsp_instruction_word);
        Memory.putU4(store_queue + 12, texture_control_word);
        Memory.putU4(store_queue + 16, 0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, data_size_for_sort_dma);
        Memory.putU4(store_queue + 28, next_address_for_sort_dma);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_1(int parameter_control_word,
                                      int isp_tsp_instruction_word,
                                      int tsp_instruction_word,
                                      int texture_control_word,
                                      float face_color_alpha,
                                      float face_color_r,
                                      float face_color_g,
                                      float face_color_b
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, tsp_instruction_word);
        Memory.putU4(store_queue + 12, texture_control_word);
        Memory.putF4(store_queue + 16, face_color_alpha);
        Memory.putF4(store_queue + 20, face_color_r);
        Memory.putF4(store_queue + 24, face_color_g);
        Memory.putF4(store_queue + 28, face_color_b);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_2(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, tsp_instruction_word);
        Memory.putU4(store_queue + 12, texture_control_word);
        Memory.putU4(store_queue + 16, 0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, data_size_for_sort_dma);
        Memory.putU4(store_queue + 28, next_address_for_sort_dma);
        Memory.putF4(store_queue + 32, face_color_alpha);
        Memory.putF4(store_queue + 36, face_color_r);
        Memory.putF4(store_queue + 40, face_color_g);
        Memory.putF4(store_queue + 44, face_color_b);
        Memory.putF4(store_queue + 48, face_offset_color_alpha);
        Memory.putF4(store_queue + 52, face_offset_color_r);
        Memory.putF4(store_queue + 56, face_offset_color_g);
        Memory.putF4(store_queue + 60, face_offset_color_b);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void polygon_type_3(int parameter_control_word,
                                      int isp_tsp_instruction_word,
                                      int tsp_instruction_word_0,
                                      int texture_control_word_0,
                                      int tsp_instruction_word_1,
                                      int texture_control_word_1,
                                      int data_size_for_sort_dma,
                                      int next_address_for_sort_dma
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, tsp_instruction_word_0);
        Memory.putU4(store_queue + 12, texture_control_word_0);
        Memory.putU4(store_queue + 16, tsp_instruction_word_1);
        Memory.putU4(store_queue + 20, texture_control_word_1);
        Memory.putU4(store_queue + 24, data_size_for_sort_dma);
        Memory.putU4(store_queue + 28, next_address_for_sort_dma);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_4(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, tsp_instruction_word_0);
        Memory.putU4(store_queue + 12, texture_control_word_0);
        Memory.putU4(store_queue + 16, tsp_instruction_word_1);
        Memory.putU4(store_queue + 20, texture_control_word_1);
        Memory.putU4(store_queue + 24, data_size_for_sort_dma);
        Memory.putU4(store_queue + 28, next_address_for_sort_dma);
        Memory.putF4(store_queue + 32, face_color_alpha_0);
        Memory.putF4(store_queue + 36, face_color_r_0);
        Memory.putF4(store_queue + 40, face_color_g_0);
        Memory.putF4(store_queue + 44, face_color_b_0);
        Memory.putF4(store_queue + 48, face_color_alpha_1);
        Memory.putF4(store_queue + 52, face_color_r_1);
        Memory.putF4(store_queue + 56, face_color_g_1);
        Memory.putF4(store_queue + 60, face_color_b_1);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void sprite(int parameter_control_word,
                              int isp_tsp_instruction_word,
                              int tsp_instruction_word,
                              int texture_control_word,
                              int base_color,
                              int offset_color,
                              int data_size_for_sort_dma,
                              int next_address_for_sort_dma
                              ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, tsp_instruction_word);
        Memory.putU4(store_queue + 12, texture_control_word);
        Memory.putU4(store_queue + 16, base_color);
        Memory.putU4(store_queue + 20, offset_color);
        Memory.putU4(store_queue + 24, data_size_for_sort_dma);
        Memory.putU4(store_queue + 28, next_address_for_sort_dma);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void modifier_volume(int parameter_control_word,
                                       int isp_tsp_instruction_word
                                       ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putU4(store_queue + 4, isp_tsp_instruction_word);
        Memory.putU4(store_queue + 8, 0);
        Memory.putU4(store_queue + 12, 0);
        Memory.putU4(store_queue + 16, 0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, 0);
        Memory.putU4(store_queue + 28, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
}
