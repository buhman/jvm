package java.lang;

public final class Byte
    extends Number
    implements Comparable<Byte> {

    public static final byte MAX_VALUE = 127;

    public static final byte MIN_VALUE = -128;

    public static final int SIZE = 8;

    private final byte value;

    public Byte(byte value) {
        this.value = value;
    }

    public Byte(String s) throws NumberFormatException {
        this.value = parseByte(s, 10);
    }

    public byte byteValue() {
        return this.value;
    }

    public int compareTo(Byte anotherByte) {
        return this.value - anotherByte.value;
    }

    public static Byte decode(String nm)
        throws NumberFormatException {
        int i = Integer.decode(nm);
        if (i < MIN_VALUE || i > MAX_VALUE)
            throw new NumberFormatException();
        return new Byte((byte)i);
    }

    public double doubleValue() {
        return (double)value;
    }

    public boolean equals(Object obj) {
        return obj instanceof Byte && value == ((Byte)obj).value;
    }

    public float floatValue() {
        return (float)value;
    }

    public int hashCode() {
        return value;
    }

    public int intValue() {
        return (int)value;
    }

    public long longValue() {
        return (long)value;
    }

    public static byte parseByte(String s)
        throws NumberFormatException {
        return parseByte(s, 10);
    }

    public static byte parseByte(String s,
                                 int radix)
        throws NumberFormatException {
        int i = Integer.parseInt(s, radix);
        if (i < MIN_VALUE || i > MAX_VALUE)
            throw new NumberFormatException();
        return (byte)i;
    }

    public short shortValue() {
        return (short)value;
    }

    public String toString() {
        return Integer.toString(value);
    }

    public static String toString(byte b) {
        return Integer.toString(b);
    }

    public static Byte valueOf(byte b) {
        return new Byte(b);
    }

    public static Byte valueOf(String s)
        throws NumberFormatException {
        return new Byte(Byte.parseByte(s, 10));
    }

    public static Byte valueOf(String s, int radix)
        throws NumberFormatException {
        return new Byte(Byte.parseByte(s, radix));
    }
}
