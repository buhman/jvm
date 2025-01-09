package filesystem.iso9660;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;

class TestExtentReader implements ExtentReader {
    byte[] all_bytes;
    public TestExtentReader() {
        try {
            all_bytes = Files.readAllBytes(Paths.get("classes/classes.iso"));
        } catch (IOException e) {
            System.out.println("readAllBytes exception");
        }
    }

    public void readInto(byte[] buf, int extent) {
        int offset = extent * 2048;
        for (int i = 0; i < 2048; i++) {
            buf[i] = all_bytes[offset + i];
        }
    }
}
