package java.lang;

public class Object {
    public Object() {}

    public final native Class getClass();

    public native int hashCode();

    public String toString() {
        return getClass().getName() + "@" + Integer.toString(hashCode());
    }
}
