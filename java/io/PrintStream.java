package java.io;

import java.lang.String;

public class PrintStream
{
    public PrintStream() {
    }

    private final byte[] newline = {'\n'};

    public static native void write(byte[] buf);

    public void println() {
        write(newline);
    }

    public void println(byte[] buf) {
        write(buf);
        write(newline);
    }

    public void println(String s) {
        write(s.getBytes());
        write(newline);
    }

    public void print(byte[] buf) {
        write(buf);
    }

    public void print(String s) {
        write(s.getBytes());
    }
}
