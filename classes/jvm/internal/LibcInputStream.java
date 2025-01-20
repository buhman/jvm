package jvm.internal;

import java.io.InputStream;
import java.io.IOException;

public class LibcInputStream extends InputStream {
    private int file; // is actually FILE *

    private static native int _open(byte[] path);

    public LibcInputStream(LibcPath path) {
        file = _open(path.path);
    }

    private static native int _available(int file);

    public int available() throws IOException {
        return _available(file);
    }

    private static native void _close(int file);

    public void close() throws IOException {
        _close(file);
    }

    private static native int _read(int file);

    public int read() throws IOException {
        return _read(file);
    }
}
