package sega.dreamcast.holly;

import sega.dreamcast.holly.Holly;
import sega.dreamcast.holly.CoreBits;
import sega.dreamcast.holly.TABits;
import java.misc.Memory;

public class TAFIFOPolygonConverter {
    private TAFIFOPolygonConverter() {
    }

    public static void init(int isp_tsp_parameters_start,
                            int isp_tsp_parameters_end,
                            int object_list_start,
                            int object_list_end,
                            int opb_total_size,
                            int ta_alloc,
                            int tile_width,   // in tile units
                            int tile_height)  // in tile units
    {
        // opb_size is the total size of all OPBs for all passes
        int ta_next_opb_offset = opb_total_size * tile_width * tile_height;

        int ta_glob_tile_clip = TABits.ta_glob_tile_clip__tile_y_num(tile_height - 1)
                              | TABits.ta_glob_tile_clip__tile_x_num(tile_width  - 1);

        Memory.putU4(Holly.SOFTRESET, CoreBits.softreset__ta_soft_reset);
        Memory.putU4(Holly.SOFTRESET, 0);

        Memory.putU4(Holly.TA_GLOB_TILE_CLIP, ta_glob_tile_clip);

        Memory.putU4(Holly.TA_ALLOC_CTRL, ta_alloc);

        Memory.putU4(Holly.TA_ISP_BASE, isp_tsp_parameters_start);
        Memory.putU4(Holly.TA_ISP_LIMIT, isp_tsp_parameters_end); // the end of isp_tsp_parameters
        Memory.putU4(Holly.TA_OL_BASE, object_list_start);
        Memory.putU4(Holly.TA_OL_LIMIT, object_list_end); // the end of the object_list
        Memory.putU4(Holly.TA_NEXT_OPB_INIT, object_list_start + ta_next_opb_offset);

        Memory.putU4(Holly.TA_LIST_INIT, TABits.ta_list_init__list_init);

        // dummy read
        Memory.getU4(Holly.TA_LIST_INIT);
    }

    public static void wait_opaque_list()
    {
        //while ((system.ISTNRM & istnrm::end_of_transferring_opaque_list) == 0) {
        //};
        //system.ISTNRM = istnrm::end_of_transferring_opaque_list;
        while (true) {
            int istnrm = Memory.getU4(0xa05f6900);
            if ((istnrm & (1 << 7)) != 0)
                break;
        }
        Memory.putU4(0xa05f6900, (1 << 7));
    }
}
