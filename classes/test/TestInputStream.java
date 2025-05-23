package test;

import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.io.InputStream;
import java.io.IOException;

class TestInputStream {
    public static void main() throws IOException {
        Path path = FileSystems.getDefault().getPath("/home/bilbo/source.txt");
        InputStream is = Files.newInputStream(path);
        int available = is.available();
        System.out.print("available: ");
        System.out.println(available);

        byte[] buf = new byte[available];
        int read = is.read(buf, 0, available);
        System.out.print("read: ");
        System.out.println(read);

        System.out.println(buf);
    }
}
