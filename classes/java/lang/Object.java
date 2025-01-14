package java.lang;

public class Object {
    public Object() {}

    protected Object clone()
        throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }

    public boolean equals(Object obj) {
        return this == obj;
    }

    private final native Class<?> _getClass();

    public final Class<?> getClass() {
        return _getClass();
    }

    private native int _hashCode();

    public int hashCode() {
        return _hashCode();
    }

    public String toString() {
        return getClass().getName() + "@" + Integer.toHexString(hashCode());
    }
}
