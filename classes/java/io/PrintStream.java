package java.io;

import java.lang.String;
import java.lang.Integer;

public class PrintStream
{
    public PrintStream() {
    }

    private static final byte[] newline = {'\n'};

    private static native void _write(byte[] buf);

    private static native void _write(char[] buf);

    private static native void _write(String s);

    public void print(byte[] buf) {
        _write(buf);
    }

    public void print(boolean b) {
        _write(String.valueOf(b));
    }

    public void print(char c) {
        _write(String.valueOf(c));
    }

    public void print(int i) {
        _write(String.valueOf(i));
    }

    public void print(long l) {
        _write(String.valueOf(l));
    }

    public void print(float f) {
        _write(String.valueOf(f));
    }

    public void print(double d) {
        _write(String.valueOf(d));
    }

    public void print(Object obj) {
        _write(String.valueOf(obj));
    }

    public void print(String s) {
        _write(String.valueOf(s));
    }

    public void println() {
        _write(newline);
    }

    public void println(byte[] buf) {
        _write(buf);
        _write(newline);
    }

    public void println(boolean b) {
        _write(String.valueOf(b));
        _write(newline);
    }

    public void println(char c) {
        _write(String.valueOf(c));
        _write(newline);
    }

    public void println(int i) {
        _write(String.valueOf(i));
        _write(newline);
    }

    public void println(long l) {
        _write(String.valueOf(l));
        _write(newline);
    }

    public void println(float f) {
        _write(String.valueOf(f));
        _write(newline);
    }

    public void println(double d) {
        _write(String.valueOf(d));
        _write(newline);
    }

    public void println(Object obj) {
        _write(String.valueOf(obj));
        _write(newline);
    }

    public void println(String s) {
        _write(String.valueOf(s));
        _write(newline);
    }
}
