package java.lang;

public class Float {
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
