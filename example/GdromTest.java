package example;

import sega.dreamcast.gdrom.GdromProtocol;
import sega.dreamcast.gdrom.G1IF;
import java.misc.Memory;
import filesystem.iso9660.VolumeParser;
import filesystem.iso9660.ExtentReader;

class GdromExtentReader implements ExtentReader {
    public void readInto(byte[] buf, int extent) {
        int starting_address = extent + 150;
        System.out.print("starting_address: ");
        System.out.println(starting_address);
        GdromProtocol.cdReadPIO(buf, starting_address, 1);
    }
}

class GdromTest {
    static byte[] buf;

    static {
        buf = new byte[2048];
    }

    public static void g1_dma_start(int start_address, int transfer_length) {
        int gdstar = start_address & ~(0b111 << 29);
        int gdlen = (transfer_length + 31) & ~(31);

        Memory.putU4(G1IF.GDAPRO, 0x8843407F);
        Memory.putU4(G1IF.G1GDRC, 0x00001001);
        Memory.putU4(G1IF.GDSTAR, gdstar);
        Memory.putU4(G1IF.GDLEN, gdlen);
        Memory.putU4(G1IF.GDDIR, 1);
        Memory.putU4(G1IF.GDEN, 1);
        Memory.putU4(G1IF.GDST, 1);
    }

    public static void main() {
        // assume gdrom is already unlocked

        int data_track_fad = GdromProtocol.tocGetDataTrackFad();

        //GdromProtocol.cdReadPIO(buf, primary_volume_descriptor, 1);

        GdromExtentReader reader = new GdromExtentReader();
        VolumeParser parser = new VolumeParser(data_track_fad - 150, reader);
        System.out.println("::parser parse::");
        parser.parse();
        /*
        System.out.println("data:");
        for (int i = 0; i < 16; i++) {
            System.out.print(((int)buf[i]) & 0xff);
            System.out.print(" ");
        }
        System.out.println();
        */

    }
}
