package sega.dreamcast.holly;

public class TextureMemoryAllocation {
                                                        /* frame A   frame B  */
    public static final int[] isp_tsp_parameters_start = { 0x000000, 0x080000 };
    public static final int[] isp_tsp_parameters_end   = { 0x07ffc0, 0x0fffc0 };
    public static final int[] background_start         = { 0x07ffc0, 0x0fffc0 };
    public static final int[] background_end           = { 0x080000, 0x100000 };
    public static final int[] object_list_start        = { 0x100000, 0x180000 };
    public static final int[] object_list_end          = { 0x17ffe0, 0x1fffe0 };
    public static final int[] region_array_start       = { 0x200000, 0x210000 };
    public static final int[] region_array_end         = { 0x210000, 0x220000 };
    public static final int[] framebuffer_start        = { 0x220000, 0x2c8c00 }; // 720 x 480 @ 16bpp
    public static final int[] framebuffer_end          = { 0x2c8c00, 0x371800 }; // 720 x 480 @ 16bpp

    public static final int[][] texture_regions        = {
       /* start     end      */
        { 0x200000, 0x400000 },
        { 0x600000, 0x800000 },
    };
}
