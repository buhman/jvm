package jvm.internal;

import java.nio.file.Path;
import java.nio.file.FileSystem;

public class LibcPath implements Path {
    public byte[] path;

    public LibcPath(byte[] path) {
        this.path = path;
    }

    private static int copyInto(byte[] dest, int offset, String s) {
        int length = s.length();
        for (int i = 0; i < length; i++) {
            dest[offset + i] = (byte)s.charAt(i);
        }
        return offset + length;
    }

    public static LibcPath fromString(String first, String... more) {
        int length = first.length();
        for (int i = 0; i < more.length; i++) {
            length += more[i].length();
        }
        length += more.length + 1; // including C string null terminator

        byte[] path = new byte[length];
        int offset = 0;
        offset = copyInto(path, offset, first);
        byte sep = (byte)'/';
        for (int i = 0; i < more.length; i++) {
            path[offset++] = sep;
            offset = copyInto(path, offset, more[i]);
        }

        return new LibcPath(path);
    }

    public FileSystem getFileSystem() {
        return LibcFileSystem.getLibcFileSystem();
    }
}
