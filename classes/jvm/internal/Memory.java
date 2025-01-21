package jvm.internal;

public class Memory {
    public static native void putU4(int address, int value);
    public static native void putF4(int address, float value);
    public static native void putU2(int address, short value);
    public static native void putU1(int address, byte value);

    public static native int getU4(int address);
    public static native float getF4(int address);
    public static native short getU2(int address);
    public static native byte getU1(int address);

    public static native void putUnalignedU4(int address, int value, boolean bigEndian);
    public static native void putUnalignedU2(int address, short value, boolean bigEndian);
    public static native void putUnalignedF4(int address, float value, boolean bigEndian);

    public static native int getUnalignedU4(int address, boolean bigEndian);
    public static native short getUnalignedU2(int address, boolean bigEndian);
    public static native float getUnalignedF4(int address, boolean bigEndian);

    public static native boolean isBigEndian();

    public static native int allocate(int size);
}
