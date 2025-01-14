package java.lang;

public class Runtime {
    private static final Runtime runtime;

    private Runtime() {
    }

    static {
        runtime = new Runtime();
    }

    private static native int _freeMemory();

    public long freeMemory() {
        return _freeMemory();
    }

    private static native void _gc();

    public void gc() {
        _gc();
    }

    public static Runtime getRuntime() {
        return runtime;
    }

    public long maxMemory() {
        return Long.MAX_VALUE;
    }

    private static native int _totalMemory();

    public long totalMemory() {
        return _totalMemory();
    }
}
