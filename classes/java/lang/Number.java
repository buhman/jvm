package java.lang;

public abstract class Number {
    public byte byteValue() {
        return (byte)intValue();
    }

    public Number() {
    }

    public abstract double doubleValue();

    public abstract float floatValue();

    public abstract int intValue();

    public abstract long longValue();

    public short shortValue() {
        return (byte)shortValue();
    }
}
