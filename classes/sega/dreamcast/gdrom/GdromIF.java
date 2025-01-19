package sega.dreamcast.gdrom;

import sega.dreamcast.gdrom.G1IF;
import jvm.internal.Memory;

public class GdromIF {
    // transfer_length is in bytes
    public static void startG1DMA(int start_address, int transfer_length) {
        int gdstar = start_address & ~(0b111 << 29);

        Memory.putU4(G1IF.GDAPRO, 0x8843007F);
        Memory.putU4(G1IF.G1GDRC, 0x00001001);
        Memory.putU4(G1IF.GDSTAR, gdstar);
        Memory.putU4(G1IF.GDLEN, transfer_length);
        Memory.putU4(G1IF.GDDIR, 1);
        Memory.putU4(G1IF.GDEN, 1);
        Memory.putU4(G1IF.GDST, 1);
    }
}
