package java.lang;

public class Integer {
    public static final short[] DIGITS;
    static {
        short[] digits = new short[100];
        for (int h = 0; h < 10; h++) {
            int high = (h + '0') << 8;
            for (int l = 0; l < 10; l++) {
                int low = l + '0';
                digits[h * 10 + l] = (short)(high | low);
            }
        }
        DIGITS = digits;
    }

    public static int stringSize(int n) {
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

    public static String toString(int n) {
        int pos = stringSize(n);
        byte[] buf = new byte[pos];
        buf[0] = (char)'0';

        boolean sign = n < 0;
        if (sign) {
            n = -n;
        }

        while (n >= 10) {
            int div = n / 100;
            pos -= 2;
            int mod = n - (div * 100);

            short digits = DIGITS[mod];
            buf[pos] = (byte)(digits >> 8);
            buf[pos+1] = (byte)(digits);

            n = div;
        }

        if (n != 0) {
            pos -= 1;
            buf[pos] = (byte)('0' + n);
        }

        if (sign) {
            pos -= 1;
            buf[pos] = (byte)('-');
        }
        return new String(buf);
    }
}
