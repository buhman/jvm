package java.lang;

public class String {
    private final byte[] value;

    public String() {
        this.value = new byte[0];
    }

    public String(String original) {
        this.value = original.value;
    }

    public String(byte[] value) {
        this.value = value;
    }

    public byte[] getBytes() {
        return this.value;
    }

    public String toString() {
        return this;
    }

    public static String valueOf(boolean b) {
        return b ? "true" : "false";
    }

    public static String valueOf(int i) {
        return Integer.toString(i);
    }

    public static String valueOf(long l) {
        return Long.toString(l);
    }

    public static String valueOf(float f) {
        return Float.toString(f);
    }

    public static String valueOf(double d) {
        return Double.toString(d);
    }

    public static String valueOf(Object obj) {
        return (obj == null) ? "null" : obj.toString();
    }
}
