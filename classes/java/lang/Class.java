package java.lang;

public final class Class<T> {
    private Object klass; // struct class_entry *
    private String name;

    private Class() {
    }

    private static native String _getName(Object o);

    public String getName() {
        if (this.name == null) {
            this.name = _getName(this);
        }
        return this.name;
    }

    private static native Class<?> _getSuperclass(Class<?> c);

    public Class<? super T> getSuperclass() {
        return (Class<? super T>)(_getSuperclass(this));
    }
}
