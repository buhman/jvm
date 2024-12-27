package sega.dreamcast;

public class MemoryMap {
    public static final int system_boot_rom                  = -1610612736; // 0xa0000000
    public static final int system                           = -1604360192; // 0xa05f6800
    public static final int maple_if                         = -1604359168; // 0xa05f6c00
    public static final int gdrom_if                         = -1604358144; // 0xa05f7000
    public static final int g1_if                            = -1604357120; // 0xa05f7400
    public static final int g2_if                            = -1604356096; // 0xa05f7800
    public static final int pvr_if                           = -1604355072; // 0xa05f7c00
    public static final int holly                            = -1604354048; // 0xa05f8000
    public static final int modem                            = -1604321280; // 0xa0600000
    public static final int aica_sound                       = -1603272704; // 0xa0700000
    public static final int aica_rtc                         = -1603207168; // 0xa0710000
    public static final int aica_wave_memory                 = -1602224128; // 0xa0800000
    public static final int texture_memory64                 = -1543503872; // 0xa4000000
    public static final int texture_memory32                 = -1526726656; // 0xa5000000
    public static final int system_memory                    = -1409286144; // 0xac000000
    public static final int ta_fifo_polygon_converter        =   268435456; // 0x10000000
    public static final int ta_fifo_yuv_converter            =   276824064; // 0x10800000
    public static final int ta_fifo_texture_memory           =   285212672; // 0x11000000
    public static final int ta_fifo_polygon_converter_mirror =   301989888; // 0x12000000
    public static final int ta_fifo_yuv_converter_mirror     =   310378496; // 0x12800000
    public static final int ta_fifo_texture_memory_mirror    =   318767104; // 0x13000000
    public static final int store_queue                      =  -536870912; // 0xe0000000
    public static final int sh7091_ic_a                      =  -268435456; // 0xf0000000
    public static final int sh7091_ic_d                      =  -251658240; // 0xf1000000
    public static final int sh7091_oc_a                      =  -201326592; // 0xf4000000
    public static final int sh7091_oc_d                      =  -184549376; // 0xf5000000
    public static final int sh7091                           =   -16777216; // 0xff000000
}
