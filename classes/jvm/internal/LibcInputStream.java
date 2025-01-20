package jvm.internal;

import java.io.InputStream;

public class LibcInputStream extends InputStream {
    private int file; // is actually FILE *

    private static native int _open(byte[] path);

    public LibcInputStream(LibcPath path) {
        file = _open(path.path);
    }

    private static native void _close(int file);

    public void close() {
        _close(file);
    }

    private static native int _read(int file);

    public int read() {
        return _read(file);
    }
}
