package java.lang;

import java.io.PrintStream;

public final class System {
    public static PrintStream out = null;

    private System() {
    }
    static {
        out = new PrintStream();
    }
}
