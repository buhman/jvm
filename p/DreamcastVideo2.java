package p;

import sega.dreamcast.holly.Holly;
import sega.dreamcast.holly.CoreBits;
import java.misc.Memory;

class DreamcastVideo2 {
    public static void main() {
        System.out.print("FB_R_SOF1: ");
        System.out.println(Memory.getU4(Holly.FB_R_SOF1));

        System.out.print("FB_R_CTRL: ");
        System.out.println(Memory.getU4(Holly.FB_R_CTRL));

        int fb_r_ctrl =
              CoreBits.fb_r_ctrl__vclk_div__pclk_vclk_1
            | CoreBits.fb_r_ctrl__fb_depth__0888_rgb_32bit
            | CoreBits.fb_r_ctrl__fb_enable;
        Memory.putU4(Holly.FB_R_CTRL, fb_r_ctrl);

        int red = 0x00ff7700;
        int fb = 0xa5000000 + Memory.getU4(Holly.FB_R_SOF1);
        for (int i = 0; i < 640 * 480; i++) {
            Memory.putU4(fb + (i * 4), red);
        }
    }
}
