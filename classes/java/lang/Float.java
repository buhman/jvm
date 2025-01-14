package java.lang;

public class Float {
    public static final int MAX_EXPONENT = 127;

    public static final double MAX_VALUE = 0x1.fffffep+127f;

    public static final int MIN_EXPONENT = -126;

    public static final double MIN_NORMAL = 0x1.0p-126f;

    public static final double MIN_VALUE = 0x0.000002p-126f;

    public static final double NaN = 0.0f / 0.0f;

    public static final double NEGATIVE_INFINITY = -1.0f / 0.0f;

    public static final double POSITIVE_INFINITY = 1.0f / 0.0f;

    public static final int SIZE = 32;

    public static String toString(float f) {
        int integer = (int)f;
        float frac = (f - (float)integer) * 10000.0f;
        int fraction = (int)frac;

        byte[] int_s = Integer.toString(integer).getBytes();
        byte[] frac_s = Integer.toString(fraction).getBytes();
        int length = int_s.length + frac_s.length + 1;
        byte[] buf = new byte[length];

        int ix = 0;
        for (int i = 0; i < int_s.length; i++) {
            buf[ix] = int_s[i];
            ix += 1;
        }

        buf[ix] = (byte)'.';
        ix += 1;

        for (int i = 0; i < frac_s.length; i++) {
            buf[ix] = frac_s[i];
            ix += 1;
        }

        return new String(buf);
    }
}
