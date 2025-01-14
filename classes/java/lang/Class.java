package java.lang;

public final class Class<T> {
    private Object object;
    private String name;

    private Class() {
    }

    private native String _getName();

    public String getName() {
        if (this.name == null) {
            this.name = _getName();
        }
        return this.name;
    }
}
