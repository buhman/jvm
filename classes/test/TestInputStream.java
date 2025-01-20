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
        char c = (char)is.read();
        System.out.println(c);
    }
}
