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
import model.UntitledModel;
import model.Vec3;
import model.Vec2;
import model.FacePTN;
import model.ModelObject;
import java.misc.Memory;
import java.misc.Resource;
import filesystem.iso9660.VolumeParser;
import filesystem.iso9660.DirectoryRecordHandler;
import filesystem.iso9660.DirectoryRecord;
import sega.dreamcast.gdrom.GdromExtentReader;
import sega.dreamcast.gdrom.GdromProtocol;
import sega.dreamcast.gdrom.GdromIF;
import sega.dreamcast.gdrom.G1IF;
import sega.dreamcast.gdrom.Gdrom;
import java.misc.Memory;

class JavaCubeDirectoryRecordHandler implements DirectoryRecordHandler {
    int[] texture_extents;
    String[] texture_filenames;

    JavaCubeDirectoryRecordHandler(int[] texture_extents, String[] texture_filenames) {
        this.texture_extents = texture_extents;
        this.texture_filenames = texture_filenames;
    }

    boolean bytesEqual(byte[] a, int a_offset, byte[] b, int length) {
        for (int i = 0; i < length; i++) {
            if (a[a_offset + i] != b[i])
                return false;
        }
        return true;
    }

    public int isTexture(DirectoryRecord dr) {
        int length = dr.lengthOfFileIdentifier();
        if (length != 14)
            return -1;

        byte[] buf = dr.array;
        int offset = dr.offset + DirectoryRecord.FILE_IDENTIFIER_START;

        if (buf[offset] != (byte)'J')
            return -1;

        for (int i = 0; i < texture_filenames.length; i++) {
            byte[] texture_filename = texture_filenames[i].getBytes();
            if (bytesEqual(buf, offset, texture_filename, length))
                return i;
        }
        return -1;
    }

    public void handle(DirectoryRecord dr) {
        int texture_index = isTexture(dr);
        if (texture_index >= 0) {
            int extent = dr.locationOfExtent(); // sector number
            /*
            System.out.print("texture extent: ");
            System.out.print(texture_index);
            System.out.print(": ");
            System.out.println(extent);
            */
            texture_extents[texture_index] = extent;
        }
    }
}

public class JavaCube {
    static final int framebuffer_width = 640;
    static final int framebuffer_height = 480;

    static TAGlobalParameter.polygon_type_0[] gt0;
    static TAVertexParameter.polygon_type_3 vt0;
    static TAGlobalParameter.end_of_list eol;

    static Vec2[] quad;
    static Vec2[] quad_uv;

    static float theta;

    static int colors[] = {
        5156825, 14787722, 9529551,
        4729017, 10213073, 15956866,
        5362273, 8377157, 9797796,
        11479204, 4042586, 16676239
    };

    public static int[] texture_extents;

    static String[] texture_filenames = {
        "JAVA_CUP.DAT;1",
        "JAVA_TEX.DAT;1",
    };

    static {
        texture_extents = new int[texture_filenames.length];
        for (int i = 0; i < texture_filenames.length; i++) {
            texture_extents[i] = -1;
        }

        int parameter_control_word = TAParameter.para_control__para_type__polygon_or_modifier_volume
                                   | TAParameter.para_control__list_type__translucent
                                   | TAParameter.obj_control__col_type__packed_color
                                   | TAParameter.obj_control__texture;

        int isp_tsp_instruction_word = ISPTSP.isp_tsp_instruction_word__depth_compare_mode__greater
                                     | ISPTSP.isp_tsp_instruction_word__culling_mode__no_culling;

        int tsp_instruction_word = ISPTSP.tsp_instruction_word__src_alpha_instr__src_alpha
                                 | ISPTSP.tsp_instruction_word__dst_alpha_instr__inverse_src_alpha
                                 | ISPTSP.tsp_instruction_word__fog_control__no_fog
                                 | ISPTSP.tsp_instruction_word__texture_u_size__512
                                 | ISPTSP.tsp_instruction_word__texture_v_size__1024
                                 | ISPTSP.tsp_instruction_word__use_alpha;

        int texture_address = TextureMemoryAllocation.texture_regions[1][0] + 512;
        int texture_control_word = ISPTSP.texture_control_word__pixel_format__4444
                                 | ISPTSP.texture_control_word__scan_order__non_twiddled
                                 | ISPTSP.texture_control_word__texture_address(texture_address / 8);

        int data_size_for_sort_dma = 0;
        int next_address_for_sort_dma = 0;

        gt0 = new TAGlobalParameter.polygon_type_0[2];
        gt0[0] = new TAGlobalParameter.polygon_type_0(parameter_control_word,
                                                      isp_tsp_instruction_word,
                                                      tsp_instruction_word,
                                                      texture_control_word,
                                                      data_size_for_sort_dma,
                                                      next_address_for_sort_dma);

        tsp_instruction_word = ISPTSP.tsp_instruction_word__src_alpha_instr__src_alpha
                             | ISPTSP.tsp_instruction_word__dst_alpha_instr__inverse_src_alpha
                             | ISPTSP.tsp_instruction_word__fog_control__no_fog
                             | ISPTSP.tsp_instruction_word__texture_u_size__128
                             | ISPTSP.tsp_instruction_word__texture_v_size__64
                             | ISPTSP.tsp_instruction_word__use_alpha;

        texture_address = TextureMemoryAllocation.texture_regions[1][0] + 512 + (512 * 512 * 2 * 2);
        texture_control_word = ISPTSP.texture_control_word__pixel_format__4444
                             | ISPTSP.texture_control_word__scan_order__non_twiddled
                             | ISPTSP.texture_control_word__texture_address(texture_address / 8);

        gt0[1] = new TAGlobalParameter.polygon_type_0(parameter_control_word,
                                                      isp_tsp_instruction_word,
                                                      tsp_instruction_word,
                                                      texture_control_word,
                                                      data_size_for_sort_dma,
                                                      next_address_for_sort_dma);

        vt0 = new TAVertexParameter.polygon_type_3(0,    // parameter_control_word
                                                   0.0f, // x
                                                   0.0f, // y
                                                   0.0f, // z
                                                   0.0f, // u
                                                   0.0f, // v
                                                   0,    // color
                                                   0);   // offset_color

        eol = new TAGlobalParameter.end_of_list(TAParameter.para_control__para_type__end_of_list);

        float x = 256.0f;
        float y = 208.0f;
        quad = new Vec2[4];
        quad[0] = new Vec2(x +   0.0f, y +  0.0f);
        quad[1] = new Vec2(x + 128.0f, y +  0.0f);
        quad[2] = new Vec2(x + 128.0f, y + 64.0f);
        quad[3] = new Vec2(x +   0.0f, y + 64.0f);

        quad_uv = new Vec2[4];
        quad_uv[0] = new Vec2(0.0f, 0.0f);
        quad_uv[1] = new Vec2(1.0f, 0.0f);
        quad_uv[2] = new Vec2(1.0f, 1.0f);
        quad_uv[3] = new Vec2(0.0f, 1.0f);
    }

    public static void transform_vertex(Vec3[] position, Vec2[] texture, FacePTN ptn) {
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

        vt0.x = x;
        vt0.y = y;
        vt0.z = z;
        vt0.u = texture[ptn.texture].x;
        vt0.v = texture[ptn.texture].y;
    }

    public static void transform_triangle(int n, Vec3[] position, Vec2[] texture, FacePTN[] face) {
        for (int i = 0; i < 3; i++) {
            vt0.parameter_control_word = TAParameter.para_control__para_type__vertex_parameter;
            if (i == 2)
                vt0.parameter_control_word |= TAParameter.para_control__end_of_strip;
            transform_vertex(position, texture, face[i]);
            vt0.base_color = colors[n];

            Memory.putSQ1(vt0, MemoryMap.ta_fifo_polygon_converter);
        }
    }

    public static void transform_quad() {
        // strip order:
        // 0 1 3 2

        vt0.z = 0.1f;

        vt0.parameter_control_word = TAParameter.para_control__para_type__vertex_parameter;
        vt0.x = quad[0].x;
        vt0.y = quad[0].y;
        vt0.u = quad_uv[0].x;
        vt0.v = quad_uv[0].y;
        Memory.putSQ1(vt0, MemoryMap.ta_fifo_polygon_converter);

        vt0.parameter_control_word = TAParameter.para_control__para_type__vertex_parameter;
        vt0.x = quad[1].x;
        vt0.y = quad[1].y;
        vt0.u = quad_uv[1].x;
        vt0.v = quad_uv[1].y;
        Memory.putSQ1(vt0, MemoryMap.ta_fifo_polygon_converter);

        vt0.parameter_control_word = TAParameter.para_control__para_type__vertex_parameter;
        vt0.x = quad[3].x;
        vt0.y = quad[3].y;
        vt0.u = quad_uv[3].x;
        vt0.v = quad_uv[3].y;
        Memory.putSQ1(vt0, MemoryMap.ta_fifo_polygon_converter);

        vt0.parameter_control_word = TAParameter.para_control__para_type__vertex_parameter
                                   | TAParameter.para_control__end_of_strip;
        vt0.x = quad[2].x;
        vt0.y = quad[2].y;
        vt0.u = quad_uv[2].x;
        vt0.v = quad_uv[2].y;
        Memory.putSQ1(vt0, MemoryMap.ta_fifo_polygon_converter);
    }

    public static void transfer_cube_scene() {
        // global parameters
        Memory.putSQ1(gt0[0], MemoryMap.ta_fifo_polygon_converter);

        // triangle parameters
        ModelObject obj = UntitledModel.objects[0];
        for (int i = 0; i < obj.faces.length; i ++) {
            transform_triangle(i, UntitledModel.position, UntitledModel.texture, obj.faces[i]);
        }

        // end of list
        Memory.putSQ1(eol, MemoryMap.ta_fifo_polygon_converter);
    }

    public static void transfer_splash_scene() {
        // global parameters
        Memory.putSQ1(gt0[1], MemoryMap.ta_fifo_polygon_converter);

        // quad parameters
        transform_quad();

        // end of list
        Memory.putSQ1(eol, MemoryMap.ta_fifo_polygon_converter);
    }

    public static void transfer_textures() {
        int texture = TextureMemoryAllocation.texture_regions[1][0] + 512;

        int data_track_fad = GdromProtocol.tocGetDataTrackFad();

        JavaCubeDirectoryRecordHandler handler
            = new JavaCubeDirectoryRecordHandler(texture_extents, texture_filenames);
        GdromExtentReader reader = new GdromExtentReader();
        VolumeParser parser = new VolumeParser(data_track_fad - 150, reader, handler);
        parser.parse();

        for (int i = 0; i < texture_extents.length; i++) {
            int length = 512 * 512 * 2;
            int sectors = length >> 11; // division by 2048

            System.out.println(texture);
            if (texture_extents[i] >= 0) {
                int extent = texture_extents[i];
                Memory.putU4(G1IF.GDEN, 0);
                GdromProtocol.cdReadDMA(extent + 150, sectors);
                GdromIF.startG1DMA(MemoryMap.texture_memory64 + texture, length);
                while ((Memory.getU4(G1IF.GDST) & 1) != 0);
                System.out.println("transfer complete");
                int status = Memory.getU1(Gdrom.status);
                System.out.print("status: ");
                System.out.println(status);
            }

            texture += length;
        }
    }

    public static void transfer_java_powered() {
        int texture = TextureMemoryAllocation.texture_regions[1][0] + 512 + (512 * 512 * 2 * 2);

        // java_powered
        int[] java_powered = Resource.getResource("images/java_powered");
        int java_powered_length = (java_powered == null) ? 0 : java_powered.length;
        //System.out.print("images/java_powered length: ");
        //System.out.println(java_powered_length);

        for (int i = 0; i < java_powered_length; i++) {
            Memory.putU4(MemoryMap.texture_memory64 + texture, java_powered[i]);
            texture += 4;
        }
    }

    public static void boot_splash(int ta_alloc, int opb_size_total) {
        // unpipelined render loop
        TAFIFOPolygonConverter.init(TextureMemoryAllocation.isp_tsp_parameters_start[0],
                                    TextureMemoryAllocation.isp_tsp_parameters_end[0],
                                    TextureMemoryAllocation.object_list_start[0],
                                    TextureMemoryAllocation.object_list_end[0],
                                    opb_size_total,
                                    ta_alloc,
                                    framebuffer_width / 32,
                                    framebuffer_height / 32);
        transfer_splash_scene();
        TAFIFOPolygonConverter.wait_translucent_list();

        Core.start_render(TextureMemoryAllocation.region_array_start[0],
                          TextureMemoryAllocation.isp_tsp_parameters_start[0],
                          TextureMemoryAllocation.background_start[0],
                          TextureMemoryAllocation.framebuffer_start[0],
                          framebuffer_width);
        Core.wait_end_of_render_tsp();

        while ((CoreBits.spg_status__vsync(Memory.getU4(Holly.SPG_STATUS)) == 0));
        while (!(CoreBits.spg_status__vsync(Memory.getU4(Holly.SPG_STATUS)) == 0));
        VideoOutput.set_framebuffer_resolution(640, 480);
        VideoOutput.set_mode(VideoOutputMode.vga);
        Memory.putU4(Holly.FB_R_SOF1, TextureMemoryAllocation.framebuffer_start[0]);
    }

    public static void main() {
        System.out.println(Memory.getU4(Holly.FB_R_SOF1));

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

        transfer_java_powered();

        Background.background(TextureMemoryAllocation.background_start[0],
                              0x00c0c0c0); // sega white

        int num_render_passes = opb_size.length;
        RegionArray.region_array(framebuffer_width / 32,
                                 framebuffer_height / 32,
                                 opb_size,
                                 num_render_passes,
                                 TextureMemoryAllocation.region_array_start[0],
                                 TextureMemoryAllocation.object_list_start[0]);

        Core.init();

        for (int i = 0; i < 2; i++) {
            boot_splash(ta_alloc, opb_size_total);
        }

        transfer_textures();

        int background_color = 0xff100a00;
        Background.background(TextureMemoryAllocation.background_start[1],
                              background_color);

        Memory.putU4(Holly.VO_BORDER_COL, background_color);

        RegionArray.region_array(framebuffer_width / 32,
                                 framebuffer_height / 32,
                                 opb_size,
                                 num_render_passes,
                                 TextureMemoryAllocation.region_array_start[1],
                                 TextureMemoryAllocation.object_list_start[1]);

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
            transfer_cube_scene();
            TAFIFOPolygonConverter.wait_translucent_list();

            Core.start_render(TextureMemoryAllocation.region_array_start[ta],
                              TextureMemoryAllocation.isp_tsp_parameters_start[ta],
                              TextureMemoryAllocation.background_start[1],
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
