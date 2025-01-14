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

    private final native static Class<?> _getClass(Object o);

    public final Class<?> getClass() {
        return _getClass(this);
    }

    public int hashCode() {
        return System.identityHashCode(this);
    }

    public String toString() {
        return getClass().getName() + "@" + Integer.toHexString(hashCode());
    }
}
