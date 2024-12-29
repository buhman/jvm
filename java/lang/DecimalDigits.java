package java.lang;

class DecimalDigits {
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
}
