package java.misc;

public class Resource {
    private Resource() {
    }

    public static native int getResource(String name);
}
