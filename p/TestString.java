package p;

class TestString {
    static int test() {
        String s = new String("asdf");
        byte[] b = s.getBytes();
        int sum = 0;
        for (int i = 0; i < b.length; i++) {
            sum += b[i];
        }
        return sum;
    }


    public static void main() {
        test();
    }
}
