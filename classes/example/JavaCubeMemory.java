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
import sega.dreamcast.holly.VideoOutput;
import sega.dreamcast.holly.VideoOutputMode;
import sega.dreamcast.MemoryMap;
import model.CubeModel;
import model.Vec3;
import model.Vec2;
import model.FacePTN;
import model.ModelObject;
import jvm.internal.Memory;

public class JavaCubeMemory {
    static final int framebuffer_width = 640;
    static final int framebuffer_height = 480;

    static Vec2[] quad;
    static Vec2[] quad_uv;

    static float theta;

    public static int[] texture_extents;

    static String[] texture_filenames = {
        "JAVA_CUP.DAT;1",
        "JAVA_TEX.DAT;1",
    };

    static final int parameter_control_word = TAParameter.para_control__para_type__polygon_or_modifier_volume
                                            | TAParameter.para_control__list_type__translucent
                                            | TAParameter.obj_control__col_type__packed_color
                                            | TAParameter.obj_control__texture;

    static final int isp_tsp_instruction_word = ISPTSP.isp_tsp_instruction_word__depth_compare_mode__greater
                                              | ISPTSP.isp_tsp_instruction_word__culling_mode__no_culling;

    static final int tsp_instruction_word = ISPTSP.tsp_instruction_word__src_alpha_instr__src_alpha
                                          | ISPTSP.tsp_instruction_word__dst_alpha_instr__inverse_src_alpha
                                          | ISPTSP.tsp_instruction_word__fog_control__no_fog
                                          | ISPTSP.tsp_instruction_word__texture_u_size__512
                                          | ISPTSP.tsp_instruction_word__texture_v_size__1024
                                          | ISPTSP.tsp_instruction_word__use_alpha;

    static final int texture_address = TextureMemoryAllocation.texture_regions[0][0] + 512;
    static final int texture_control_word = ISPTSP.texture_control_word__pixel_format__4444
                                          | ISPTSP.texture_control_word__scan_order__non_twiddled
                                          | ISPTSP.texture_control_word__texture_address(texture_address / 8);

    static {
        texture_extents = new int[texture_filenames.length];
        for (int i = 0; i < texture_filenames.length; i++) {
            texture_extents[i] = -1;
        }
    }

    public static void transform_vertex(int parameter_control_word,
                                        Vec3[] position,
                                        Vec2[] texture,
                                        FacePTN ptn) {

        float px = position[ptn.position].x;
        float py = position[ptn.position].y;
        float pz = position[ptn.position].z;

        float theta2 = theta * 2.0f;
        float scale = (Math.sin(theta2) + 3.0f) * 0.3f;

        px *= scale;
        py *= scale;
        pz *= scale;

        float x0 = px * Math.cos(theta) - py * Math.sin(theta);
        float y0 = px * Math.sin(theta) + py * Math.cos(theta);
        float z0 = pz;

        float theta05 = theta * 0.5f;

        float x1 = x0 * Math.cos(theta05) - z0 * Math.sin(theta05);
        float y1 = y0;
        float z1 = x0 * Math.sin(theta05) + z0 * Math.cos(theta05);

        // camera transform
        float z2 = 3f + z1;

        // perspective
        float x2 = x1 / z2;
        float y2 = y1 / z2;

        // screen space
        float x = x2 * 240f + 320f;
        float y = -y2 * 240f + 240f;
        float z = 1.0f / z2;

        TAVertexParameter.polygon_type_3(parameter_control_word,
                                         x,
                                         y,
                                         z,
                                         texture[ptn.texture].x, // u
                                         texture[ptn.texture].y, // v
                                         0xff000000,  // base_color
                                         0); // offset_color
    }

    public static void transform_triangle(int n, Vec3[] position, Vec2[] texture, FacePTN[] face) {
        for (int i = 0; i < 3; i++) {
            int parameter_control_word = TAParameter.para_control__para_type__vertex_parameter;
            if (i == 2)
                parameter_control_word |= TAParameter.para_control__end_of_strip;
            transform_vertex(parameter_control_word, position, texture, face[i]);
        }
    }

    public static void transfer_cube_scene() {
        // global parameters
        TAGlobalParameter.polygon_type_0(parameter_control_word,
                                         isp_tsp_instruction_word,
                                         tsp_instruction_word,
                                         texture_control_word,
                                         0,  // data_size_for_sort_dma
                                         0); // next_address_for_sort_dma

        // triangle parameters
        ModelObject obj = CubeModel.objects[0];
        for (int i = 0; i < obj.faces.length; i ++) {
            transform_triangle(i, CubeModel.position, CubeModel.texture, obj.faces[i]);
        }

        // end of list
        TAGlobalParameter.end_of_list(TAParameter.para_control__para_type__end_of_list);
    }

    public static void transfer_textures() {
        int texture = MemoryMap.texture_memory64 + TextureMemoryAllocation.texture_regions[0][0] + 512;

        int length = 512 * 512 * 2 * 2 / 4;
        int address = 0xac400000;
        for (int i = 0; i < length; i++) {
            int value = Memory.getU4(address);
            Memory.putU4(texture, value);
            address += 4;
            texture += 4;
        }
    }

    public static void main() {
        System.out.println("main1");

        System.out.println("transfer_textures");
        transfer_textures();
        System.out.println("transfer_textures2");

        int ta_alloc =
              TABits.ta_alloc_ctrl__opb_mode__increasing_addresses
            | TABits.ta_alloc_ctrl__pt_opb__no_list
            | TABits.ta_alloc_ctrl__tm_opb__no_list
            | TABits.ta_alloc_ctrl__t_opb__8x4byte
            | TABits.ta_alloc_ctrl__om_opb__no_list
            | TABits.ta_alloc_ctrl__o_opb__no_list
            ;

        RegionArray.OPBSize[] opb_size = {
            new RegionArray.OPBSize(0,     // opaque
                                    0,     // opaque_modifier_volume
                                    8 * 4, // translucent
                                    0,     // translucent_modifier_volume
                                    0)     // punch_through
        };
        int opb_size_total = opb_size[0].total();

        int background_color = 0xff100a00;
        Background.background(TextureMemoryAllocation.background_start[0],
                              0x00c0c0c0); // sega white
        Background.background(TextureMemoryAllocation.background_start[1],
                              0x00c0c0c0);//background_color); // dark black

        Memory.putU4(Holly.VO_BORDER_COL, background_color);

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

        Core.init();

        VideoOutput.set_framebuffer_resolution(640, 480);
        VideoOutput.set_mode(VideoOutputMode.vga);

        int core = 0;
        int ta = 0;
        System.out.println("main");
        int framebuffer_tiles_width = framebuffer_width / 32;
        int framebuffer_tiles_height = framebuffer_height / 32;

        // prime
        for (int i = 0; i < 2; i++) {
            TAFIFOPolygonConverter.init(TextureMemoryAllocation.isp_tsp_parameters_start[i],
                                        TextureMemoryAllocation.isp_tsp_parameters_end[i],
                                        TextureMemoryAllocation.object_list_start[i],
                                        TextureMemoryAllocation.object_list_end[i],
                                        opb_size_total,
                                        ta_alloc,
                                        framebuffer_tiles_width,
                                        framebuffer_tiles_height);
            transfer_cube_scene();
            if (i == 0)
                TAFIFOPolygonConverter.wait_translucent_list();
        }

        for (int i = 0; i < 2; i++) {
            Core.start_render(TextureMemoryAllocation.region_array_start[core],
                              TextureMemoryAllocation.isp_tsp_parameters_start[core],
                              TextureMemoryAllocation.background_start[1],
                              TextureMemoryAllocation.framebuffer_start[i],
                              framebuffer_width);
            if (i == 0)
                Core.wait_end_of_render_tsp();
        }

        while (true) {
            ta = (core + 1) & 1;

            // unpipelined render loop
            TAFIFOPolygonConverter.wait_translucent_list();
            TAFIFOPolygonConverter.init(TextureMemoryAllocation.isp_tsp_parameters_start[ta],
                                        TextureMemoryAllocation.isp_tsp_parameters_end[ta],
                                        TextureMemoryAllocation.object_list_start[ta],
                                        TextureMemoryAllocation.object_list_end[ta],
                                        opb_size_total,
                                        ta_alloc,
                                        framebuffer_tiles_width,
                                        framebuffer_tiles_height);
            transfer_cube_scene();

            Core.wait_end_of_render_tsp();
            Core.start_render(TextureMemoryAllocation.region_array_start[core],
                              TextureMemoryAllocation.isp_tsp_parameters_start[core],
                              TextureMemoryAllocation.background_start[core],
                              TextureMemoryAllocation.framebuffer_start[core],
                              framebuffer_width);

            while (!(CoreBits.spg_status__vsync(Memory.getU4(Holly.SPG_STATUS)) != 0));
            while ((CoreBits.spg_status__vsync(Memory.getU4(Holly.SPG_STATUS)) != 0));
            Memory.putU4(Holly.FB_R_SOF1, TextureMemoryAllocation.framebuffer_start[ta]);

            core = ta;

            theta += Math.DEGREES_TO_RADIANS;
        }
    }
}
