package java.lang;

public class Class {
    private Object object;
    private String name;

    private Class() {
    }

    private native String getClassName();

    public String getName() {
        if (this.name == null) {
            this.name = getClassName();
        }
        return this.name;
    }
}
