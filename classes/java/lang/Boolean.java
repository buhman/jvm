package java.lang;

class Boolean
    implements Comparable<Boolean> {
    public static final Boolean FALSE = new Boolean(false);

    public static final Boolean TRUE = new Boolean(true);

    private final boolean value;

    public Boolean(boolean value) {
        this.value = value;
    }

    public Boolean(String s) {
        this(parseBoolean(s));
    }

    public boolean booleanValue() {
        return value;
    }

    public int compareTo(Boolean b) {
        return value == b.value ? 0 : (value ? 1 : -1);
    }

    public boolean equals(Object obj) {
        return (obj instanceof Boolean) && (value == ((Boolean)obj).booleanValue());
    }

    public int hashCode() {
        return value ? 1231 : 1237;
    }

    public static boolean parseBoolean(String s) {
        return "true".equalsIgnoreCase(s) ? true : false;
    }

    public String toString() {
        return String.valueOf(value);
    }

    public static String toString(boolean b) {
        return String.valueOf(b);
    }

    public static Boolean valueOf(boolean b) {
        return (b ? TRUE : FALSE);
    }

    public static Boolean valueOf(String s) {
        return parseBoolean(s) ? TRUE : FALSE;
    }
}
