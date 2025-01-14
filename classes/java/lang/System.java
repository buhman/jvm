package java.lang;

import java.io.PrintStream;

public final class System {
    public static PrintStream err;
    public static PrintStream out;

    private System() {
    }
    static {
        out = new PrintStream();
        err = new PrintStream();
    }

    public static void gc() {
        Runtime.getRuntime().gc();
    }

    private final native static int _hashCode(Object x);

    public static int identityHashCode(Object x) {
        return _hashCode(x);
    }
}
