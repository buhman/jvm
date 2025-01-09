package p;

class ByteArray {
    static byte test() {
        byte[] l = new byte[10];
        for (int i = 0; i < l.length; i++)
            l[i] = (byte)(i * 3);
        byte sum = 0;
        for (int i = 0; i < l.length; i++)
            sum += l[i];
        return sum;
    }

    public static void main() {
        System.out.println(test());
    }
}
