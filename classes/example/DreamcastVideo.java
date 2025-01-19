package example;

import sega.dreamcast.holly.Holly;
import jvm.internal.Memory;

class DreamcastVideo {
    public static void main() {
        System.out.print("FB_R_SOF1: ");
        int a = Memory.getU4(Holly.FB_R_SOF1);
        System.out.println(Integer.toString(Holly.FB_R_SOF1));
        System.out.println(Integer.toString(a));
        System.out.print("FB_R_CTRL: ");
        int b = Memory.getU4(Holly.FB_R_CTRL);
        System.out.println(Integer.toString(b));
        System.out.println();

        int red = 0x000077ff;
        int fb = 0xa5000000 + a;
        for (int i = 0; i < 640 * 480; i++) {
            Memory.putU4(fb + (i * 4), red);
        }
    }
}
