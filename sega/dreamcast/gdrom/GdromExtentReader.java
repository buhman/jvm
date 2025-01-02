package sega.dreamcast.gdrom;

import filesystem.iso9660.ExtentReader;

public class GdromExtentReader implements ExtentReader {
    public void readInto(byte[] buf, int extent) {
        int starting_address = extent + 150;
        GdromProtocol.cdReadPIO(buf, starting_address, 1);
    }
}
