package example;

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
import sega.dreamcast.holly.TAVertexParameter;
import sega.dreamcast.holly.TAGlobalParameter;
import sega.dreamcast.systembus.Systembus;
import sega.dreamcast.systembus.SystembusBits;
import sega.dreamcast.MemoryMap;
import model.UntitledModel;
import model.Vec3;
import model.FacePNT;
import model.ModelObject;
import java.misc.Memory;

/*
class Vec2 {
    float x;
    float y;
}
*/

class DreamcastVideo2 {
    static final int framebuffer_width = 640;
    static final int framebuffer_height = 480;

    static TAGlobalParameter.polygon_type_0 gt0;
    static TAVertexParameter.polygon_type_0 vt0;
    static TAGlobalParameter.end_of_list eol;

    //static Vec2[] vtx;

    static float theta;

    static int colors[] = {
        5156825, 14787722, 9529551,
        4729017, 10213073, 15956866,
        5362273, 8377157, 9797796,
        11479204, 4042586, 16676239
    };

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

        gt0 = new TAGlobalParameter.polygon_type_0(parameter_control_word,
                                                   isp_tsp_instruction_word,
                                                   tsp_instruction_word,
                                                   texture_control_word,
                                                   data_size_for_sort_dma,
                                                   next_address_for_sort_dma);

        vt0 = new TAVertexParameter.polygon_type_0(0,    // parameter_control_word
                                                   0.0f, // x
                                                   0.0f, // y
                                                   0.1f, // z
                                                   0);   // color

        eol = new TAGlobalParameter.end_of_list(TAParameter.para_control__para_type__end_of_list);

        /*
        vtx = new Vec2[3];
        for (int i = 0; i < 3; i++)
            vtx[i] = new Vec2();
        vtx[0].x =  0.0f;
        vtx[0].y =  1.0f;
        vtx[1].x =  0.866025f;
        vtx[1].y = -0.5f;
        vtx[2].x = -0.866025f;
        vtx[2].y = -0.5f;
        */
    }

    public static void transform_vertex(Vec3[] position, FacePNT pnt) {
        float px = position[pnt.position].x;
        float py = position[pnt.position].y;
        float pz = position[pnt.position].z;

        //px *= 0.5;
        //py *= 0.5;
        //pz *= 0.5;

        float x0 = px * Math.cos(theta) - py * Math.sin(theta);
        float y0 = px * Math.sin(theta) + py * Math.cos(theta);
        float z0 = pz;

        float theta2 = theta / 2.0f;

        float x1 = x0 * Math.cos(theta2) - z0 * Math.sin(theta2);
        float y1 = y0;
        float z1 = x0 * Math.sin(theta2) + z0 * Math.cos(theta2);

        // camera transform
        float z2 = 3f + z1;

        // perspective
        float x2 = x1 / z2;
        float y2 = y1 / z2;

        // screen space
        float x = x2 * 240f + 320f;
        float y = -y2 * 240f + 240f;
        float z = 1.0f / z2;

        DreamcastVideo2.vt0.x = x;
        DreamcastVideo2.vt0.y = y;
        DreamcastVideo2.vt0.z = z;
    }

    public static void transform_triangle(int n, Vec3[] position, FacePNT[] face) {
        for (int i = 0; i < 3; i++) {
            DreamcastVideo2.vt0.parameter_control_word = TAParameter.para_control__para_type__vertex_parameter;
            if (i == 2)
                DreamcastVideo2.vt0.parameter_control_word |= TAParameter.para_control__end_of_strip;
            transform_vertex(position, face[i]);
            DreamcastVideo2.vt0.base_color = colors[n];

            Memory.putSQ1(DreamcastVideo2.vt0, MemoryMap.ta_fifo_polygon_converter);
        }
    }

    public static void transfer_scene() {
        // global parameter
        Memory.putSQ1(DreamcastVideo2.gt0, MemoryMap.ta_fifo_polygon_converter);

        // vertex parameters
        ModelObject obj = UntitledModel.objects[0];
        for (int i = 0; i < obj.faces.length; i ++) {
            transform_triangle(i, UntitledModel.position, obj.faces[i]);
        }

        // end of list
        Memory.putSQ1(DreamcastVideo2.eol, MemoryMap.ta_fifo_polygon_converter);
    }

    public static void main() {
        Core.init();
        Core.fb_init(framebuffer_width, framebuffer_height);

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
        int num_render_passes = opb_size.length;

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

        int background_color = 0xff443300;
        Background.background(TextureMemoryAllocation.background_start[0],
                              background_color);
        Background.background(TextureMemoryAllocation.background_start[1],
                              background_color);

        int core = 0;
        int ta = 0;
        while (true) {
            // unpipelined render loop
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

            while (!(CoreBits.spg_status__vsync(Memory.getU4(Holly.SPG_STATUS)) != 0));
            Memory.putU4(Holly.FB_R_SOF1, TextureMemoryAllocation.framebuffer_start[core]);
            while ((CoreBits.spg_status__vsync(Memory.getU4(Holly.SPG_STATUS)) != 0));

            core = (core + 1) % 1;

            theta += Math.DEGREES_TO_RADIANS;
        }
    }
}
