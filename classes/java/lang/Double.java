package java.lang;

public class Double {
    public static final int MAX_EXPONENT = 1023;

    public static final double MAX_VALUE = 0x1.fffffffffffffp+1023;

    public static final int MIN_EXPONENT = -1022;

    public static final double MIN_NORMAL = 0x1.0p-1022;

    public static final double MIN_VALUE = 0x0.0000000000001p-1022;

    public static final double NaN = 0.0 / 0.0;

    public static final double NEGATIVE_INFINITY = -1.0 / 0.0;

    public static final double POSITIVE_INFINITY = 1.0 / 0.0;

    public static final int SIZE = 64;

    public static String toString(double f) {
        long integer = (long)f;
        double frac = (f - (double)integer) * 10000.0;
        long fraction = (long)frac;

        byte[] int_s = Long.toString(integer).getBytes();
        byte[] frac_s = Long.toString(fraction).getBytes();
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
