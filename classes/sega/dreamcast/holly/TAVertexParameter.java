package sega.dreamcast.holly;

import sega.dreamcast.MemoryMap;
import sega.dreamcast.sh7091.StoreQueueBuffer;
import jvm.internal.SH4Intrinsic;
import jvm.internal.Memory;

public class TAVertexParameter {
    public static class polygon_type_0
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int base_color;
        public polygon_type_0(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int base_color
                              ) {
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_color = base_color;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, 0);
            putInt(20, 0);
            putInt(24, base_color);
            putInt(28, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_1
        extends StoreQueueBuffer
    {

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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_color_alpha = base_color_alpha;
            this.base_color_r = base_color_r;
            this.base_color_g = base_color_g;
            this.base_color_b = base_color_b;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putFloat(16, base_color_alpha);
            putFloat(20, base_color_r);
            putFloat(24, base_color_g);
            putFloat(28, base_color_b);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_2
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float base_intensity;
        public polygon_type_2(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              float base_intensity
                              ) {
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_intensity = base_intensity;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, 0);
            putInt(20, 0);
            putFloat(24, base_intensity);
            putInt(28, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_3
        extends StoreQueueBuffer
    {

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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this.base_color = base_color;
            this.offset_color = offset_color;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putFloat(16, u);
            putFloat(20, v);
            putInt(24, base_color);
            putInt(28, offset_color);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_4
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v = u_v;
            this.base_color = base_color;
            this.offset_color = offset_color;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, u_v);
            putInt(20, 0);
            putInt(24, base_color);
            putInt(28, offset_color);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_5
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public float u;
        public float v;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this.base_color_alpha = base_color_alpha;
            this.base_color_r = base_color_r;
            this.base_color_g = base_color_g;
            this.base_color_b = base_color_b;
            this.offset_color_alpha = offset_color_alpha;
            this.offset_color_r = offset_color_r;
            this.offset_color_g = offset_color_g;
            this.offset_color_b = offset_color_b;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putFloat(16, u);
            putFloat(20, v);
            putInt(24, 0);
            putInt(28, 0);
            putFloat(32, base_color_alpha);
            putFloat(36, base_color_r);
            putFloat(40, base_color_g);
            putFloat(44, base_color_b);
            putFloat(48, offset_color_alpha);
            putFloat(52, offset_color_r);
            putFloat(56, offset_color_g);
            putFloat(60, offset_color_b);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_6
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v = u_v;
            this.base_color_alpha = base_color_alpha;
            this.base_color_r = base_color_r;
            this.base_color_g = base_color_g;
            this.base_color_b = base_color_b;
            this.offset_color_alpha = offset_color_alpha;
            this.offset_color_r = offset_color_r;
            this.offset_color_g = offset_color_g;
            this.offset_color_b = offset_color_b;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, u_v);
            putInt(20, 0);
            putInt(24, 0);
            putInt(28, 0);
            putFloat(32, base_color_alpha);
            putFloat(36, base_color_r);
            putFloat(40, base_color_g);
            putFloat(44, base_color_b);
            putFloat(48, offset_color_alpha);
            putFloat(52, offset_color_r);
            putFloat(56, offset_color_g);
            putFloat(60, offset_color_b);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_7
        extends StoreQueueBuffer
    {

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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this.base_intensity = base_intensity;
            this.offset_intensity = offset_intensity;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putFloat(16, u);
            putFloat(20, v);
            putFloat(24, base_intensity);
            putFloat(28, offset_intensity);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_8
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v = u_v;
            this.base_intensity = base_intensity;
            this.offset_intensity = offset_intensity;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, u_v);
            putInt(20, 0);
            putFloat(24, base_intensity);
            putFloat(28, offset_intensity);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_9
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int base_color_0;
        public int base_color_1;
        public polygon_type_9(int parameter_control_word,
                              float x,
                              float y,
                              float z,
                              int base_color_0,
                              int base_color_1
                              ) {
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_color_0 = base_color_0;
            this.base_color_1 = base_color_1;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, base_color_0);
            putInt(20, base_color_1);
            putInt(24, 0);
            putInt(28, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_10
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int base_intensity_0;
        public int base_intensity_1;
        public polygon_type_10(int parameter_control_word,
                               float x,
                               float y,
                               float z,
                               int base_intensity_0,
                               int base_intensity_1
                               ) {
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.base_intensity_0 = base_intensity_0;
            this.base_intensity_1 = base_intensity_1;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, base_intensity_0);
            putInt(20, base_intensity_1);
            putInt(24, 0);
            putInt(28, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            SH4Intrinsic.pref1(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_11
        extends StoreQueueBuffer
    {

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
            super();
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
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putFloat(16, u_0);
            putFloat(20, v_0);
            putInt(24, base_color_0);
            putInt(28, offset_color_0);
            putFloat(32, u_1);
            putFloat(36, v_1);
            putInt(40, base_color_1);
            putInt(44, offset_color_1);
            putInt(48, 0);
            putInt(52, 0);
            putInt(56, 0);
            putInt(60, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_12
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v_0;
        public int base_color_0;
        public int offset_color_0;
        public int u_v_1;
        public int base_color_1;
        public int offset_color_1;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v_0 = u_v_0;
            this.base_color_0 = base_color_0;
            this.offset_color_0 = offset_color_0;
            this.u_v_1 = u_v_1;
            this.base_color_1 = base_color_1;
            this.offset_color_1 = offset_color_1;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, u_v_0);
            putInt(20, 0);
            putInt(24, base_color_0);
            putInt(28, offset_color_0);
            putInt(32, u_v_1);
            putInt(36, 0);
            putInt(40, base_color_1);
            putInt(44, offset_color_1);
            putInt(48, 0);
            putInt(52, 0);
            putInt(56, 0);
            putInt(60, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_13
        extends StoreQueueBuffer
    {

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
            super();
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
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putFloat(16, u_0);
            putFloat(20, v_0);
            putInt(24, base_intensity_0);
            putFloat(28, offset_intensity_0);
            putFloat(32, u_1);
            putFloat(36, v_1);
            putInt(40, base_intensity_1);
            putFloat(44, offset_intensity_1);
            putInt(48, 0);
            putInt(52, 0);
            putInt(56, 0);
            putInt(60, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class polygon_type_14
        extends StoreQueueBuffer
    {

        public int parameter_control_word;
        public float x;
        public float y;
        public float z;
        public int u_v_0;
        public int base_intensity_0;
        public float offset_intensity_0;
        public int u_v_1;
        public int base_intensity_1;
        public float offset_intensity_1;
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
            super();
            this.parameter_control_word = parameter_control_word;
            this.x = x;
            this.y = y;
            this.z = z;
            this.u_v_0 = u_v_0;
            this.base_intensity_0 = base_intensity_0;
            this.offset_intensity_0 = offset_intensity_0;
            this.u_v_1 = u_v_1;
            this.base_intensity_1 = base_intensity_1;
            this.offset_intensity_1 = offset_intensity_1;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, x);
            putFloat(8, y);
            putFloat(12, z);
            putInt(16, u_v_0);
            putInt(20, 0);
            putInt(24, base_intensity_0);
            putFloat(28, offset_intensity_0);
            putInt(32, u_v_1);
            putInt(36, 0);
            putInt(40, base_intensity_1);
            putFloat(44, offset_intensity_1);
            putInt(48, 0);
            putInt(52, 0);
            putInt(56, 0);
            putInt(60, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class sprite_type_0
        extends StoreQueueBuffer
    {

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
            super();
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
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, a_x);
            putFloat(8, a_y);
            putFloat(12, a_z);
            putFloat(16, b_x);
            putFloat(20, b_y);
            putFloat(24, b_z);
            putFloat(28, c_x);
            putFloat(32, c_y);
            putFloat(36, c_z);
            putFloat(40, d_x);
            putFloat(44, d_y);
            putInt(48, 0);
            putInt(52, 0);
            putInt(56, 0);
            putInt(60, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class sprite_type_1
        extends StoreQueueBuffer
    {

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
            super();
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
            this.a_u_a_v = a_u_a_v;
            this.b_u_b_v = b_u_b_v;
            this.c_u_c_v = c_u_c_v;
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, a_x);
            putFloat(8, a_y);
            putFloat(12, a_z);
            putFloat(16, b_x);
            putFloat(20, b_y);
            putFloat(24, b_z);
            putFloat(28, c_x);
            putFloat(32, c_y);
            putFloat(36, c_z);
            putFloat(40, d_x);
            putFloat(44, d_y);
            putInt(48, 0);
            putInt(52, a_u_a_v);
            putInt(56, b_u_b_v);
            putInt(60, c_u_c_v);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
    public static class modifier_volume
        extends StoreQueueBuffer
    {

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
            super();
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
        }
        public void submit() {
            putInt(0, parameter_control_word);
            putFloat(4, a_x);
            putFloat(8, a_y);
            putFloat(12, a_z);
            putFloat(16, b_x);
            putFloat(20, b_y);
            putFloat(24, b_z);
            putFloat(28, c_x);
            putFloat(32, c_y);
            putFloat(36, c_z);
            putInt(40, 0);
            putInt(44, 0);
            putInt(48, 0);
            putInt(52, 0);
            putInt(56, 0);
            putInt(60, 0);
            Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0
            Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1
            SH4Intrinsic.pref2(MemoryMap.store_queue);
        }
    }
}
