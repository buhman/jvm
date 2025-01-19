package sega.dreamcast.holly;

import sega.dreamcast.MemoryMap;
import jvm.internal.Memory;

// this is for a "type 2" region array.
// region header type is specified in FPU_PARAM_CFG
public class RegionArray {
    private RegionArray() {
    }

    public static final int TILE = 0 * 4;
    public static final int OPAQUE_LIST_POINTER = 1 * 4;
    public static final int OPAQUE_MODIFIER_VOLUME_LIST_POINTER = 2 * 4;
    public static final int TRANSLUCENT_LIST_POINTER = 3 * 4;
    public static final int TRANSLUCENT_MODIFIER_VOLUME_LIST_POINTER = 4 * 4;
    public static final int PUNCH_THROUGH_LIST_POINTER =  5 * 4;

    public static final int ENTRY_SIZE = 6 * 4;

    public static final int TILE__LAST_REGION = (1 << 31);
    public static final int TILE__Z_CLEAR = (1 << 30);
    public static final int TILE__PRE_SORT = (1 << 29);
    public static final int TILE__FLUSH_ACCUMULATE = (1 << 28);
    public static int TILE__Y_POSITION(int n) {
        return ((n) & 0X3F) << 8;
    }
    public static int TILE__X_POSITION(int n) {
        return ((n) & 0X3F) << 2;
    }
    public static final int LIST_POINTER__EMPTY = (1 << 31);

    public static class OPBSize {
        int opaque;
        int opaque_modifier_volume;
        int translucent;
        int translucent_modifier_volume;
        int punch_through;

        public OPBSize(int opaque,
                       int opaque_modifier_volume,
                       int translucent,
                       int translucent_modifier_volume,
                       int punch_through)
        {
            this.opaque = opaque;
            this.opaque_modifier_volume = opaque_modifier_volume;
            this.translucent = translucent;
            this.translucent_modifier_volume = translucent_modifier_volume;
            this.punch_through = punch_through;
        }

        public int total()
        {
            return opaque
                 + opaque_modifier_volume
                 + translucent
                 + translucent_modifier_volume
                 + punch_through;
        }
    }

    public static void region_array(int width,  // in tile units (1 tile unit = 32 pixels)
                                    int height, // in tile units (1 tile unit = 32 pixels)
                                    OPBSize[] opb_size,
                                    int num_render_passes,
                                    int region_array_start,
                                    int object_list_start) {
        int region_array = MemoryMap.texture_memory32 + region_array_start;

        int num_tiles = width * height;
        int[] ol_base = new int[num_render_passes];

        ol_base[0] = object_list_start;
        for (int pass = 1; pass < num_render_passes; pass++) {
            ol_base[pass] = ol_base[pass - 1] + num_tiles * opb_size[pass - 1].total();
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int pass = 0; pass < num_render_passes; pass++) {
                    int tile_value = TILE__Y_POSITION(y)
                                   | TILE__X_POSITION(x);

                    if (pass == (num_render_passes - 1) && y == (height - 1) && x == (width - 1))
                        tile_value |= TILE__LAST_REGION;
                    if (pass != (num_render_passes - 1))
                        tile_value |= TILE__FLUSH_ACCUMULATE;
                    if (pass > 0)
                        tile_value |= TILE__Z_CLEAR;

                    int tile_index = y * width + x;

                    int opaque_list_pointer_value =
                        (opb_size[pass].opaque == 0) ? LIST_POINTER__EMPTY :
                        (ol_base[pass] + num_tiles * ( 0 )
                                       + (opb_size[pass].opaque * tile_index));

                    int opaque_modifier_volume_list_pointer_value =
                        (opb_size[pass].opaque_modifier_volume == 0) ? LIST_POINTER__EMPTY :
                        (ol_base[pass] + num_tiles * ( opb_size[pass].opaque )
                                       + (opb_size[pass].opaque_modifier_volume * tile_index));

                    int translucent_list_pointer_value =
                        (opb_size[pass].translucent == 0) ? LIST_POINTER__EMPTY :
                        (ol_base[pass] + num_tiles * ( opb_size[pass].opaque
                                                     + opb_size[pass].opaque_modifier_volume )
                                       + (opb_size[pass].translucent * tile_index));

                    int translucent_modifier_volume_list_pointer_value =
                        (opb_size[pass].translucent_modifier_volume == 0) ? LIST_POINTER__EMPTY :
                        (ol_base[pass] + num_tiles * ( opb_size[pass].opaque
                                                     + opb_size[pass].opaque_modifier_volume
                                                     + opb_size[pass].translucent )
                                       + (opb_size[pass].translucent_modifier_volume * tile_index));

                    int punch_through_list_pointer_value =
                        (opb_size[pass].punch_through == 0) ? LIST_POINTER__EMPTY :
                        (ol_base[pass] + num_tiles * ( opb_size[pass].opaque
                                                     + opb_size[pass].opaque_modifier_volume
                                                     + opb_size[pass].translucent
                                                     + opb_size[pass].translucent_modifier_volume )
                                       + (opb_size[pass].punch_through * tile_index));

                    Memory.putU4(region_array + TILE, tile_value);
                    Memory.putU4(region_array + OPAQUE_LIST_POINTER, opaque_list_pointer_value);
                    Memory.putU4(region_array + OPAQUE_MODIFIER_VOLUME_LIST_POINTER, opaque_modifier_volume_list_pointer_value);
                    Memory.putU4(region_array + TRANSLUCENT_LIST_POINTER, translucent_list_pointer_value);
                    Memory.putU4(region_array + TRANSLUCENT_MODIFIER_VOLUME_LIST_POINTER, translucent_modifier_volume_list_pointer_value);
                    Memory.putU4(region_array + PUNCH_THROUGH_LIST_POINTER, punch_through_list_pointer_value);

                    region_array += ENTRY_SIZE;
                }
            }
        }
    }
}
