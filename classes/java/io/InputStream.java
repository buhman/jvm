package java.io;

public abstract class InputStream
    implements Closeable {

    public InputStream() {
    }

    public int available() throws IOException {
        return 0;
    }

    public void close() throws IOException {
    }

    public void mark(int readlimit) {
    }

    public abstract int read() throws IOException;

    public int read(byte[] b) throws IOException {
        return read(b, 0, b.length);
    }

    public int read(byte[] b,
                    int off,
                    int len) throws IOException {
        if (off < 0 || len < 0 || len > b.length - off)
            throw new IndexOutOfBoundsException();

        if (b == null)
            throw new NullPointerException();

        for (int i = 0; i < len; i++) {
            try {
                int c = read();
                boolean endOfStream = c == -1;
                if (endOfStream) {
                    if (i == 0)
                        return -1;
                    else
                        return i;
                }
                b[off + i] = (byte)c;
            } catch (IOException e) {
                if (i == 0)
                    throw e;
                else
                    return i;
            }
        }

        return len;
    }

    public void reset() throws IOException {
        throw new IOException();
    }

    public long skip(long n)
        throws IOException {

        long ni = n;
        while (ni > 0L) {
            int b = read();
            if (b < 0)
                break;
            ni -= 1;
        }
        return n - ni;
    }
}
