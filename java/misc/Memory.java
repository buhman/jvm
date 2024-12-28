package java.misc;

public class Memory {
    public static native void putU4(int address, int value);
    public static native void putU2(int address, int value);
    public static native void putU1(int address, int value);

    public static native int getU4(int address);
    public static native int getU2(int address);
    public static native int getU1(int address);

    public static native void putSQ1(Object object, int address);
}
