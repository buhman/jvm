package sega.dreamcast.holly;

public class VideoOutputMode {
    int fb_r_ctrl;
    int spg_load;
    int spg_hblank;
    int spg_vblank;
    int spg_width;
    int spg_control;
    int vo_startx;
    int vo_starty;
    int vo_control;
    int spg_hblank_int;
    int spg_vblank_int;

    public static VideoOutputMode vga;

    static {
        vga = new VideoOutputMode();
        vga.fb_r_ctrl      = CoreBits.fb_r_ctrl__vclk_div__pclk_vclk_1;
        vga.spg_load       = CoreBits.spg_load__vcount(0x20c)
                           | CoreBits.spg_load__hcount(0x359);
        vga.spg_hblank     = CoreBits.spg_hblank__hbend(0x07e)
                           | CoreBits.spg_hblank__hbstart(0x345);
        vga.spg_vblank     = CoreBits.spg_vblank__vbend(0x028)
                           | CoreBits.spg_vblank__vbstart(0x208);
        vga.spg_width      = CoreBits.spg_width__eqwidth(0x00f)
                           | CoreBits.spg_width__bpwidth(0x319)
                           | CoreBits.spg_width__vswidth(0x3)
                           | CoreBits.spg_width__hswidth(0x3f);
        vga.spg_control    = CoreBits.spg_control__sync_direction__output;
        vga.vo_startx      = CoreBits.vo_startx__horizontal_start_position(0x0a8);
        vga.vo_starty      = CoreBits.vo_starty__vertical_start_position_on_field_2(0x028)
                           | CoreBits.vo_starty__vertical_start_position_on_field_1(0x028);
        vga.vo_control     = CoreBits.vo_control__pclk_delay(0x16);
        vga.spg_hblank_int = CoreBits.spg_hblank_int__line_comp_val(0x345);
        vga.spg_vblank_int = CoreBits.spg_vblank_int__vblank_out_interrupt_line_number(0x015)
                           | CoreBits.spg_vblank_int__vblank_in_interrupt_line_number(0x208);
    }
}
