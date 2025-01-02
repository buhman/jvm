package jvm.internal;

public class Loader {
    private Loader() {
    }

    public static native int getBuffer();

    public static native void load(int[] buffers);
}
