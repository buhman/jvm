package p;

import sega.dreamcast.holly.Background;
import sega.dreamcast.holly.Core;
import sega.dreamcast.holly.CoreBits;
import sega.dreamcast.holly.Holly;
import sega.dreamcast.holly.RegionArray;
import sega.dreamcast.holly.TABits;
import sega.dreamcast.holly.TAFIFOPolygonConverter;
import sega.dreamcast.holly.TAParameter;
import sega.dreamcast.holly.TextureMemoryAllocation;
import sega.dreamcast.holly.ISPTSP;
import java.misc.Memory;

class end_of_list {
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

class polygon_type_0 {
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

class vertex_polygon_type_0 {
    public int parameter_control_word;
    public float x;
    public float y;
    public float z;
    public int _res0;
    public int _res1;
    public int base_color;
    public int _res2;
    public vertex_polygon_type_0(int parameter_control_word,
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


class DreamcastVideo2 {
    static final int ta_fifo_polygon_converter = 0x10000000;

    public static polygon_type_0 pt0;
    public static vertex_polygon_type_0 vt0;
    public static end_of_list eol;

    static {
        int parameter_control_word = TAParameter.para_control__para_type__polygon_or_modifier_volume
                                   | TAParameter.para_control__list_type__opaque
                                   | TAParameter.obj_control__col_type__packed_color;

        int isp_tsp_instruction_word = ISPTSP.isp_tsp_instruction_word__depth_compare_mode__greater
                                     | ISPTSP.isp_tsp_instruction_word__culling_mode__no_culling;

        int tsp_instruction_word = ISPTSP.tsp_instruction_word__src_alpha_instr__one
                                 | ISPTSP.tsp_instruction_word__dst_alpha_instr__zero
                                 | ISPTSP.tsp_instruction_word__fog_control__no_fog;

        int texture_control_word = 0;
        int data_size_for_sort_dma = 0;
        int next_address_for_sort_dma = 0;

        pt0 = new polygon_type_0(parameter_control_word,
                                 isp_tsp_instruction_word,
                                 tsp_instruction_word,
                                 texture_control_word,
                                 data_size_for_sort_dma,
                                 next_address_for_sort_dma);

        vt0 = new vertex_polygon_type_0(0, // parameter_control_word
                                        0, // x
                                        0, // y
                                        0.1f, // z
                                        0xff00ff00); // color (green)

        eol = new end_of_list(TAParameter.para_control__para_type__end_of_list);
    }

    public static int polygon_vertex_parameter_control_word(boolean end_of_strip)
    {
        return TAParameter.para_control__para_type__vertex_parameter
             | (end_of_strip ? TAParameter.para_control__end_of_strip : 0);
    }


    public static void transfer_scene() {
        Memory.putSQ1(DreamcastVideo2.pt0, ta_fifo_polygon_converter);

        DreamcastVideo2.vt0.parameter_control_word = polygon_vertex_parameter_control_word(false);
        DreamcastVideo2.vt0.x = 10.0f;
        DreamcastVideo2.vt0.y = 10.0f;
        Memory.putSQ1(DreamcastVideo2.vt0, ta_fifo_polygon_converter);

        DreamcastVideo2.vt0.parameter_control_word = polygon_vertex_parameter_control_word(false);
        DreamcastVideo2.vt0.x = 100.0f;
        DreamcastVideo2.vt0.y = 10.0f;
        Memory.putSQ1(DreamcastVideo2.vt0, ta_fifo_polygon_converter);

        DreamcastVideo2.vt0.parameter_control_word = polygon_vertex_parameter_control_word(true);
        DreamcastVideo2.vt0.x = 100.0f;
        DreamcastVideo2.vt0.y = 100.0f;
        Memory.putSQ1(DreamcastVideo2.vt0, ta_fifo_polygon_converter);

        Memory.putSQ1(DreamcastVideo2.eol, ta_fifo_polygon_converter);
    }

    public static void main() {
        Core.init();

        int ta_alloc =
              TABits.ta_alloc_ctrl__opb_mode__increasing_addresses
            | TABits.ta_alloc_ctrl__pt_opb__no_list
            | TABits.ta_alloc_ctrl__tm_opb__no_list
            | TABits.ta_alloc_ctrl__t_opb__no_list
            | TABits.ta_alloc_ctrl__om_opb__no_list
            | TABits.ta_alloc_ctrl__o_opb__8x4byte
            ;

        RegionArray.OPBSize[] opb_size = {
            new RegionArray.OPBSize(8 * 4, // opaque
                                    0,     // opaque_modifier_volume
                                    0,     // translucent
                                    0,     // translucent_modifier_volume
                                    0)     // punch_through
        };

        int opb_size_total = opb_size[0].total();

        int framebuffer_width = 640;
        int framebuffer_height = 480;
        int num_render_passes = opb_size.length;

        Core.fb_init(framebuffer_width, framebuffer_height);

        RegionArray.region_array(framebuffer_width / 32,
                                 framebuffer_height / 32,
                                 opb_size,
                                 num_render_passes,
                                 TextureMemoryAllocation.region_array_start[0],
                                 TextureMemoryAllocation.object_list_start[0]);
        RegionArray.region_array(framebuffer_width / 32,
                                 framebuffer_height / 32,
                                 opb_size,
                                 num_render_passes,
                                 TextureMemoryAllocation.region_array_start[1],
                                 TextureMemoryAllocation.object_list_start[1]);

        int background_color = 0xffff00ff;
        Background.background(TextureMemoryAllocation.background_start[0],
                              background_color);
        Background.background(TextureMemoryAllocation.background_start[1],
                              background_color);

        //int ta = -1;
        //int core = -2;
        int core = 0;
        int ta = 0;
        while (true) {
            TAFIFOPolygonConverter.init(TextureMemoryAllocation.isp_tsp_parameters_start[ta],
                                        TextureMemoryAllocation.isp_tsp_parameters_end[ta],
                                        TextureMemoryAllocation.object_list_start[ta],
                                        TextureMemoryAllocation.object_list_end[ta],
                                        opb_size_total,
                                        ta_alloc,
                                        framebuffer_width / 32,
                                        framebuffer_height / 32);
            transfer_scene();
            TAFIFOPolygonConverter.wait_opaque_list();
            Core.start_render(TextureMemoryAllocation.region_array_start[ta],
                              TextureMemoryAllocation.isp_tsp_parameters_start[ta],
                              TextureMemoryAllocation.background_start[ta],
                              TextureMemoryAllocation.framebuffer_start[core],
                              framebuffer_width);
            Core.wait_end_of_render_tsp();
            Memory.putU4(Holly.FB_R_SOF1, TextureMemoryAllocation.framebuffer_start[core]);
            core = (core + 1) % 1;
        }
    }
}
