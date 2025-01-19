package java.lang;

public abstract class Enum<E extends Enum<E>>
    implements Comparable<E> {

    final String name;

    final int ordinal;

    protected Enum(String name,
                   int ordinal) {
        this.name = name;
        this.ordinal = ordinal;
    }

    protected final Object clone()
        throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }

    public final int compareTo(E o) {
        if (getDeclaringClass() != o.getDeclaringClass())
            throw new ClassCastException();
        return ordinal - o.ordinal;
    }

    public final boolean equals(Object other) {
        return this == other;
    }

    public final Class<E> getDeclaringClass() {
        Class c = getClass();
        if (c.getSuperclass() != Enum.class)
            c = c.getSuperclass();
        return c;
    }

    public final int hashCode() {
        return ordinal;
    }

    public final String name() {
        return name;
    }

    public final int ordinal() {
        return ordinal;
    }

    public String toString() {
        return name;
    }

    public static <T extends Enum<T>> T valueOf(Class<T> enumType,
                                                String name) {
        return null;
    }
}
