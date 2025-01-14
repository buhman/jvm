package java.lang;

import java.lang.DecimalDigits;


public final class Integer
    extends Number
    implements Comparable<Integer> {

    public static final int MAX_VALUE = 2147483647;

    public static final int MIN_VALUE = -2147483648;

    public static final int SIZE = 32;

    private final int value;

    public Integer(int value) {
        this.value = value;
    }

    public Integer(String s)
        throws NumberFormatException {
        this.value = parseInt(s, 10);
    }

    public static int bitCount(int i) {
        int c;
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        c = ((i + (i >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
        return c;
    }

    public byte byteValue() {
        return (byte)value;
    }

    public int compareTo(Integer anotherInteger) {
        if (value == anotherInteger.value)
            return 0;
        if (value < anotherInteger.value)
            return -1;
        else
            return 1;
    }

    public static Integer decode(String nm)
        throws NumberFormatException {
        int length = nm.length();
        if (length == 0)
            throw new NumberFormatException(nm);
        int index = 0;
        char c;
        c = nm.charAt(index);
        if (c == '-' || c == '+')
            index += 1;
        boolean negative = (c == '-');
        int n;
        if (index >= length)
            throw new NumberFormatException(nm);
        c = nm.charAt(index);

        if (nm.startsWith("0x", index) || nm.startsWith("0X", index)) {
            String s = nm.substring(index + 2);
            n = parseInt(s, 16);
        } else if (c == '#') {
            String s = nm.substring(index + 1);
            n = parseInt(s, 16);
        } else if (c == '0') {
            String s = nm.substring(index + 1);
            n = parseInt(s, 8);
        } else {
            n = parseInt(nm, 10);
        }
        if (negative)
            n = -n;
        return new Integer(n);
    }

    public double doubleValue() {
        return (double)value;
    }

    public boolean equals(Object obj) {
        return obj instanceof Integer && value == ((Integer)obj).value;
    }

    public float floatValue() {
        return (float)value;
    }

    public int hashCode() {
        return value;
    }

    public static int highestOneBit(int i) {
        i |= i >>> 1;
        i |= i >>> 2;
        i |= i >>> 4;
        i |= i >>> 8;
        i |= i >>> 16;
        return i ^ (i >>> 1);
    }

    public int intValue() {
        return value;
    }

    public long longValue() {
        return (long)value;
    }

    public static int lowestOneBit(int value) {
        return value & (-value);
    }

    public static int numberOfLeadingZeros(int i) {
        int c = 0;
        if (i <= 0x0000ffff) { c += 16; i <<= 16; }
        if (i <= 0x00ffffff) { c += 8 ; i <<= 8 ; }
        if (i <= 0x0fffffff) { c += 4 ; i <<= 4 ; }
        if (i <= 0x3fffffff) { c += 2 ; i <<= 2 ; }
        if (i <= 0x7fffffff) { c += 1 ;           }
        return c;
    }

    public static int numberOfTrailingZeros(int i) {
        int c = 32;
        i &= -i;
        if (i != 0) c--;
        if ((i & 0x0000FFFF) != 0) c -= 16;
        if ((i & 0x00FF00FF) != 0) c -= 8;
        if ((i & 0x0F0F0F0F) != 0) c -= 4;
        if ((i & 0x33333333) != 0) c -= 2;
        if ((i & 0x55555555) != 0) c -= 1;
        return c;
    }

    public static int parseInt(String s)
        throws NumberFormatException {
        return parseInt(s, 10);
    }

    public static int parseInt(String s, int radix)
        throws NumberFormatException {
        int length = s.length();
        if (length == 0)
            throw new NumberFormatException(s);
        int index = 0;
        char c = s.charAt(index);
        if (c == '-' || c == '+')
            index += 1;
        boolean negative = (c == '-');
        if (index >= length)
            throw new NumberFormatException(s);
        if (length - index > 10)
            throw new NumberFormatException(s);
        int n = 0;
        while (index < length) {
            int value = Character.digit(s.charAt(index), radix);
            if (value < 0)
                throw new NumberFormatException(s);
            n *= radix;
            n += value;
            index += 1;
        }
        if (n < 0) // overflow
            throw new NumberFormatException(s);
        if (negative)
            n = -n;
        return n;
    }

    public static int reverse(int i) {
        i = ((i >> 1) & 0x55555555) | ((i & 0x55555555) << 1);
        i = ((i >> 2) & 0x33333333) | ((i & 0x33333333) << 2);
        i = ((i >> 4) & 0x0F0F0F0F) | ((i & 0x0F0F0F0F) << 4);
        i = ((i >> 8) & 0x00FF00FF) | ((i & 0x00FF00FF) << 8);
        i = ( i >> 16             ) | ( i               << 16);
        return i;
    }

    public static int reverseBytes(int i) {
        return (((i >> 24) & 0x000000ff) |
                ((i >> 8 ) & 0x0000ff00) |
                ((i << 8 ) & 0x00ff0000) |
                ((i << 24) & 0xff000000));
    }

    public static int rotateLeft(int i, int distance) {
        return (i << distance) | (i >>> (-distance));
    }

    public static int rotateRight(int i, int distance) {
        return (i << (-distance)) | (i >>> distance);
    }

    public short shortValue() {
        return (short)value;
    }

    public static int signum(int i) {
        return (i >> 31) | ((-i) >>> 31);
    }

    public static String toBinaryString(int i) {
        return toString(i, 2);
    }

    public static String toHexString(int i) {
        return toString(i, 16);
    }

    public static String toOctalString(int i) {
        return toString(i, 8);
    }

    private static int stringSize(int n) {
        int sign_digits = 0;
        if (n < 0) {
            sign_digits = 1;
            n = -n;
        }
        int digits = 1;
        int cmp = 10;
        for (int i = 0; i < 9; i++) {
            if (n < cmp)
                return digits + sign_digits;
            digits += 1;
            cmp *= 10;
        }
        return 10 + sign_digits;
    }

    public String toString()
    {
        return toString(value);
    }

    public static String toString(int i) {
        if (i == 0)
            return "0";
        if (i == MIN_VALUE)
            return "-2147483648";

        int pos = stringSize(i);
        byte[] buf = new byte[pos];

        boolean sign = i < 0;
        if (sign) {
            i = -i;
        }

        while (i >= 10) {
            int div = i / 100;
            int mod = i - (div * 100);

            short digits = DecimalDigits.DIGITS[mod];
            pos -= 2;
            buf[pos] = (byte)(digits >> 8);
            buf[pos+1] = (byte)(digits);

            i = div;
        }

        if (i != 0) {
            pos -= 1;
            buf[pos] = (byte)('0' + i);
        }

        if (sign) {
            pos -= 1;
            buf[pos] = (byte)'-';
        }
        return new String(buf);
    }

    public static String toString(int i, int radix) {
        if (i == 0)
            return "0";
        if (radix == 10)
            return toString(i);
        int pos = 32;
        byte[] buf = new byte[32];

        boolean sign = i < 0;
        if (sign) {
            i = -i;
        }

        while (i != 0) {
            int div = i / radix;
            int mod = i - (div * radix);
            char digit = Character.forDigit(mod, radix);
            pos -= 1;
            buf[pos] = (byte)digit;
            i = div;
        }

        if (sign) {
            pos -= 1;
            buf[pos] = (byte)'-';
        }
        return new String(buf, pos, 32 - pos);
    }

    public static Integer valueOf(int i) {
        return new Integer(i);
    }

    public static Integer valueOf(String s)
        throws NumberFormatException {
        return new Integer(Integer.parseInt(s));
    }

    public static Integer valueOf(String s, int radix)
        throws NumberFormatException {
        return new Integer(Integer.parseInt(s, radix));
    }
}
