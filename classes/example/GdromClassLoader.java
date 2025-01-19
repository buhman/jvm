package example;

import sega.dreamcast.gdrom.GdromExtentReader;
import sega.dreamcast.gdrom.GdromProtocol;
import sega.dreamcast.gdrom.GdromIF;
import sega.dreamcast.gdrom.G1IF;
import jvm.internal.Memory;
import filesystem.iso9660.VolumeParser;
import filesystem.iso9660.DirectoryRecordHandler;
import filesystem.iso9660.DirectoryRecord;
import jvm.internal.Loader;

class GdromDirectoryRecordHandler implements DirectoryRecordHandler {
    int address;
    int[] addresses;
    public int addresses_ix;
    static byte[] class_ext;

    static {
        class_ext = new byte[] { 'C', 'L', 'A', ';', '1' }; // CLA;1
    }

    public GdromDirectoryRecordHandler(int address, int[] addresses) {
        this.address = address;
        this.addresses = addresses;
        this.addresses_ix = 0;
    }

    public boolean isClassExt(DirectoryRecord dr) {
        int length = dr.lengthOfFileIdentifier();

        if (length < 6)
            return false;

        byte[] buf = dr.array;
        int offset = dr.offset + DirectoryRecord.FILE_IDENTIFIER_START;

        int ix = 0;
        for (int i = length - 5; i < length; i++) {
            if (buf[offset + i] != class_ext[ix]) {
                return false;
            }
            ix += 1;
        }
        System.out.println();
        return true;
    }

    public void handle(DirectoryRecord dr) {
        int extent = dr.locationOfExtent(); // sector number
        int length = dr.dataLength(); // bytes

        if (!isClassExt(dr)) {
            return;
        }

        // round up to nearest multiple of 2048
        length = (length + 2047) & ~(2047);

        Memory.putU4(G1IF.GDEN, 0);

        int sectors = length >> 11; // division by 2048
        GdromProtocol.cdReadDMA(extent + 150, sectors);

        GdromIF.startG1DMA(address, length);

        while ((Memory.getU4(G1IF.GDST) & 1) != 0);
        System.out.println("transfer complete");

        addresses[addresses_ix] = 0xa0000000 | address;
        addresses_ix += 1;
        address += length;
    }
}

class GdromClassLoader {
    public static void main() {
        // assume gdrom is already unlocked

        int data_track_fad = GdromProtocol.tocGetDataTrackFad();

        int[] buffer_addresses = new int[0x3000]; // maximum 12,288 class files

        int loader_buffer_address = Loader.getBuffer();
        GdromDirectoryRecordHandler handler = new GdromDirectoryRecordHandler(loader_buffer_address, buffer_addresses);
        GdromExtentReader reader = new GdromExtentReader();

        VolumeParser parser = new VolumeParser(data_track_fad - 150, reader, handler);
        parser.parse();

        Loader.load(buffer_addresses, handler.addresses_ix);
    }
}
