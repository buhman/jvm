package sega.dreamcast.holly;

import sega.dreamcast.MemoryMap;
import sega.dreamcast.holly.ISPTSP;
import java.misc.Memory;

public class Background {
    private Background() {
    }

    public static void background(int background_start,
                                  int base_color)
    {
        int isp_tsp_instruction_word =
              ISPTSP.isp_tsp_instruction_word__depth_compare_mode__always
            | ISPTSP.isp_tsp_instruction_word__culling_mode__no_culling;

        int tsp_instruction_word =
              ISPTSP.tsp_instruction_word__src_alpha_instr__one
            | ISPTSP.tsp_instruction_word__dst_alpha_instr__zero
            | ISPTSP.tsp_instruction_word__fog_control__no_fog;

        int texture_control_word = 0;

        int vertex_x = 0;
        int vertex_y = 0;
        int vertex_z = 0x37c00000; // 0.00002

        int parameter = MemoryMap.texture_memory32 + background_start;

        Memory.putU4(parameter + 0, isp_tsp_instruction_word);
        Memory.putU4(parameter + 4, tsp_instruction_word);
        Memory.putU4(parameter + 8, texture_control_word);

        int vertex = parameter + 12;
        for (int i = 0; i < 3; i++) {
            Memory.putU4(vertex + 0, vertex_x);
            Memory.putU4(vertex + 4, vertex_y);
            Memory.putU4(vertex + 8, vertex_z);
            Memory.putU4(vertex + 12, base_color);
            vertex += 16;
        }
    }
}
