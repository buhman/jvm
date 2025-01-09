package java.lang;

import java.lang.DecimalDigits;

public class Integer {
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

            short digits = DecimalDigits.DIGITS[mod];
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
