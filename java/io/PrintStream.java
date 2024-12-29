package java.io;

import java.lang.String;
import java.lang.Integer;

public class PrintStream
{
    public PrintStream() {
    }

    private final byte[] newline = {'\n'};

    public static native void write(byte[] buf);

    public static void write(String s) {
        write(s.getBytes());
    }

    public void print(byte[] buf) {
        write(buf);
    }

    public void print(boolean b) {
        write(String.valueOf(b));
    }

    public void print(int i) {
        write(String.valueOf(i));
    }

    public void print(long l) {
        write(String.valueOf(l));
    }

    public void print(float f) {
        write(String.valueOf(f));
    }

    public void print(double d) {
        write(String.valueOf(d));
    }

    public void print(Object obj) {
        write(String.valueOf(obj));
    }

    public void println() {
        write(newline);
    }

    public void println(byte[] buf) {
        write(buf);
        write(newline);
    }

    public void println(boolean b) {
        write(String.valueOf(b));
        write(newline);
    }

    public void println(int i) {
        write(String.valueOf(i));
        write(newline);
    }

    public void println(long l) {
        write(String.valueOf(l));
        write(newline);
    }

    public void println(float f) {
        write(String.valueOf(f));
        write(newline);
    }

    public void println(double d) {
        write(String.valueOf(d));
        write(newline);
    }

    public void println(Object obj) {
        write(String.valueOf(obj));
        write(newline);
    }
}
