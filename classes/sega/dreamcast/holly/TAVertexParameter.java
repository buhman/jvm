package sega.dreamcast.holly;

import sega.dreamcast.MemoryMap;
import jvm.internal.SH4Intrinsic;
import jvm.internal.Memory;

public class TAVertexParameter {
    public static void polygon_type_0(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      int base_color
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, 0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, base_color);
        Memory.putU4(store_queue + 28, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_1(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      float base_color_alpha,
                                      float base_color_r,
                                      float base_color_g,
                                      float base_color_b
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putF4(store_queue + 16, base_color_alpha);
        Memory.putF4(store_queue + 20, base_color_r);
        Memory.putF4(store_queue + 24, base_color_g);
        Memory.putF4(store_queue + 28, base_color_b);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_2(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      float base_intensity
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, 0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putF4(store_queue + 24, base_intensity);
        Memory.putU4(store_queue + 28, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_3(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      float u,
                                      float v,
                                      int base_color,
                                      int offset_color
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putF4(store_queue + 16, u);
        Memory.putF4(store_queue + 20, v);
        Memory.putU4(store_queue + 24, base_color);
        Memory.putU4(store_queue + 28, offset_color);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_4(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      int u_v,
                                      int base_color,
                                      int offset_color
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, u_v);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, base_color);
        Memory.putU4(store_queue + 28, offset_color);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_5(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putF4(store_queue + 16, u);
        Memory.putF4(store_queue + 20, v);
        Memory.putU4(store_queue + 24, 0);
        Memory.putU4(store_queue + 28, 0);
        Memory.putF4(store_queue + 32, base_color_alpha);
        Memory.putF4(store_queue + 36, base_color_r);
        Memory.putF4(store_queue + 40, base_color_g);
        Memory.putF4(store_queue + 44, base_color_b);
        Memory.putF4(store_queue + 48, offset_color_alpha);
        Memory.putF4(store_queue + 52, offset_color_r);
        Memory.putF4(store_queue + 56, offset_color_g);
        Memory.putF4(store_queue + 60, offset_color_b);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void polygon_type_6(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, u_v);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, 0);
        Memory.putU4(store_queue + 28, 0);
        Memory.putF4(store_queue + 32, base_color_alpha);
        Memory.putF4(store_queue + 36, base_color_r);
        Memory.putF4(store_queue + 40, base_color_g);
        Memory.putF4(store_queue + 44, base_color_b);
        Memory.putF4(store_queue + 48, offset_color_alpha);
        Memory.putF4(store_queue + 52, offset_color_r);
        Memory.putF4(store_queue + 56, offset_color_g);
        Memory.putF4(store_queue + 60, offset_color_b);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void polygon_type_7(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      float u,
                                      float v,
                                      float base_intensity,
                                      float offset_intensity
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putF4(store_queue + 16, u);
        Memory.putF4(store_queue + 20, v);
        Memory.putF4(store_queue + 24, base_intensity);
        Memory.putF4(store_queue + 28, offset_intensity);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_8(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      int u_v,
                                      float base_intensity,
                                      float offset_intensity
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, u_v);
        Memory.putU4(store_queue + 20, 0);
        Memory.putF4(store_queue + 24, base_intensity);
        Memory.putF4(store_queue + 28, offset_intensity);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_9(int parameter_control_word,
                                      float x,
                                      float y,
                                      float z,
                                      int base_color_0,
                                      int base_color_1
                                      ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, base_color_0);
        Memory.putU4(store_queue + 20, base_color_1);
        Memory.putU4(store_queue + 24, 0);
        Memory.putU4(store_queue + 28, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_10(int parameter_control_word,
                                       float x,
                                       float y,
                                       float z,
                                       int base_intensity_0,
                                       int base_intensity_1
                                       ) {
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, base_intensity_0);
        Memory.putU4(store_queue + 20, base_intensity_1);
        Memory.putU4(store_queue + 24, 0);
        Memory.putU4(store_queue + 28, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        SH4Intrinsic.pref1(store_queue);
    }
    public static void polygon_type_11(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putF4(store_queue + 16, u_0);
        Memory.putF4(store_queue + 20, v_0);
        Memory.putU4(store_queue + 24, base_color_0);
        Memory.putU4(store_queue + 28, offset_color_0);
        Memory.putF4(store_queue + 32, u_1);
        Memory.putF4(store_queue + 36, v_1);
        Memory.putU4(store_queue + 40, base_color_1);
        Memory.putU4(store_queue + 44, offset_color_1);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, 0);
        Memory.putU4(store_queue + 56, 0);
        Memory.putU4(store_queue + 60, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void polygon_type_12(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, u_v_0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, base_color_0);
        Memory.putU4(store_queue + 28, offset_color_0);
        Memory.putU4(store_queue + 32, u_v_1);
        Memory.putU4(store_queue + 36, 0);
        Memory.putU4(store_queue + 40, base_color_1);
        Memory.putU4(store_queue + 44, offset_color_1);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, 0);
        Memory.putU4(store_queue + 56, 0);
        Memory.putU4(store_queue + 60, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void polygon_type_13(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putF4(store_queue + 16, u_0);
        Memory.putF4(store_queue + 20, v_0);
        Memory.putU4(store_queue + 24, base_intensity_0);
        Memory.putF4(store_queue + 28, offset_intensity_0);
        Memory.putF4(store_queue + 32, u_1);
        Memory.putF4(store_queue + 36, v_1);
        Memory.putU4(store_queue + 40, base_intensity_1);
        Memory.putF4(store_queue + 44, offset_intensity_1);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, 0);
        Memory.putU4(store_queue + 56, 0);
        Memory.putU4(store_queue + 60, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void polygon_type_14(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, x);
        Memory.putF4(store_queue + 8, y);
        Memory.putF4(store_queue + 12, z);
        Memory.putU4(store_queue + 16, u_v_0);
        Memory.putU4(store_queue + 20, 0);
        Memory.putU4(store_queue + 24, base_intensity_0);
        Memory.putF4(store_queue + 28, offset_intensity_0);
        Memory.putU4(store_queue + 32, u_v_1);
        Memory.putU4(store_queue + 36, 0);
        Memory.putU4(store_queue + 40, base_intensity_1);
        Memory.putF4(store_queue + 44, offset_intensity_1);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, 0);
        Memory.putU4(store_queue + 56, 0);
        Memory.putU4(store_queue + 60, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void sprite_type_0(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, a_x);
        Memory.putF4(store_queue + 8, a_y);
        Memory.putF4(store_queue + 12, a_z);
        Memory.putF4(store_queue + 16, b_x);
        Memory.putF4(store_queue + 20, b_y);
        Memory.putF4(store_queue + 24, b_z);
        Memory.putF4(store_queue + 28, c_x);
        Memory.putF4(store_queue + 32, c_y);
        Memory.putF4(store_queue + 36, c_z);
        Memory.putF4(store_queue + 40, d_x);
        Memory.putF4(store_queue + 44, d_y);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, 0);
        Memory.putU4(store_queue + 56, 0);
        Memory.putU4(store_queue + 60, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void sprite_type_1(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, a_x);
        Memory.putF4(store_queue + 8, a_y);
        Memory.putF4(store_queue + 12, a_z);
        Memory.putF4(store_queue + 16, b_x);
        Memory.putF4(store_queue + 20, b_y);
        Memory.putF4(store_queue + 24, b_z);
        Memory.putF4(store_queue + 28, c_x);
        Memory.putF4(store_queue + 32, c_y);
        Memory.putF4(store_queue + 36, c_z);
        Memory.putF4(store_queue + 40, d_x);
        Memory.putF4(store_queue + 44, d_y);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, a_u_a_v);
        Memory.putU4(store_queue + 56, b_u_b_v);
        Memory.putU4(store_queue + 60, c_u_c_v);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
    public static void modifier_volume(int parameter_control_word,
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
        int store_queue = MemoryMap.store_queue;
        Memory.putU4(store_queue + 0, parameter_control_word);
        Memory.putF4(store_queue + 4, a_x);
        Memory.putF4(store_queue + 8, a_y);
        Memory.putF4(store_queue + 12, a_z);
        Memory.putF4(store_queue + 16, b_x);
        Memory.putF4(store_queue + 20, b_y);
        Memory.putF4(store_queue + 24, b_z);
        Memory.putF4(store_queue + 28, c_x);
        Memory.putF4(store_queue + 32, c_y);
        Memory.putF4(store_queue + 36, c_z);
        Memory.putU4(store_queue + 40, 0);
        Memory.putU4(store_queue + 44, 0);
        Memory.putU4(store_queue + 48, 0);
        Memory.putU4(store_queue + 52, 0);
        Memory.putU4(store_queue + 56, 0);
        Memory.putU4(store_queue + 60, 0);
        Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0
        Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1
        SH4Intrinsic.pref2(store_queue);
    }
}
