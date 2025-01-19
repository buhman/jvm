package sega.dreamcast.holly;

import jvm.internal.Memory;

public class VideoOutput {
    public static void set_framebuffer_resolution(int x_size, int y_size)
    {
        Memory.putU4(Holly.Y_COEFF, CoreBits.y_coeff__coefficient_1(0x80)
                                  | CoreBits.y_coeff__coefficient_0_2(0x40));

        // in 6.10 fixed point; 0x0400 is 1x vertical scale
        Memory.putU4(Holly.SCALER_CTL, CoreBits.scaler_ctl__vertical_scale_factor(0x0400));

        Memory.putU4(Holly.FB_BURSTCTRL, CoreBits.fb_burstctrl__wr_burst(0x09)
                                       | CoreBits.fb_burstctrl__vid_lat(0x3f)
                                       | CoreBits.fb_burstctrl__vid_burst(0x39));

        Memory.putU4(Holly.FB_X_CLIP, CoreBits.fb_x_clip__fb_x_clip_max(x_size - 1)
                                    | CoreBits.fb_x_clip__fb_x_clip_min(0));

        Memory.putU4(Holly.FB_Y_CLIP, CoreBits.fb_y_clip__fb_y_clip_max(y_size - 1)
                                    | CoreBits.fb_y_clip__fb_y_clip_min(0));

        Memory.putU4(Holly.FB_R_SIZE, CoreBits.fb_r_size__fb_modulus(1)
                                    | CoreBits.fb_r_size__fb_y_size(y_size - 3)
                                    | CoreBits.fb_r_size__fb_x_size((x_size * 16) / 32 - 1));
    }

    public static void set_mode(VideoOutputMode mode)
    {
        Memory.putU4(Holly.SPG_LOAD, mode.spg_load);
        Memory.putU4(Holly.SPG_HBLANK, mode.spg_hblank);
        Memory.putU4(Holly.SPG_VBLANK, mode.spg_vblank);
        Memory.putU4(Holly.SPG_WIDTH, mode.spg_width);
        Memory.putU4(Holly.SPG_CONTROL, mode.spg_control);

        Memory.putU4(Holly.VO_STARTX, mode.vo_startx);
        Memory.putU4(Holly.VO_STARTY, mode.vo_starty);
        Memory.putU4(Holly.VO_CONTROL, mode.vo_control);

        Memory.putU4(Holly.SPG_HBLANK_INT, mode.spg_hblank_int);
        Memory.putU4(Holly.SPG_VBLANK_INT, mode.spg_vblank_int);

        Memory.putU4(Holly.FB_W_CTRL, CoreBits.fb_w_ctrl__fb_dither
                                    | CoreBits.fb_w_ctrl__fb_packmode__565_rgb_16bit);

        Memory.putU4(Holly.FB_R_CTRL, mode.fb_r_ctrl
                                    | CoreBits.fb_r_ctrl__fb_depth__565_rgb_16bit
                                    | CoreBits.fb_r_ctrl__fb_enable);
    }
}
