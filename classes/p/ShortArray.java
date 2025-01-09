package p;

class ShortArray {
    static short test() {
        short[] l = new short[10];
        for (int i = 0; i < l.length; i++)
            l[i] = (short)(i * 3);
        short sum = 0;
        for (int i = 0; i < l.length; i++)
            sum += l[i];
        return sum;
    }

    public static void main() {
        test();
    }
}
