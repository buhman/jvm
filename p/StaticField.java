package p;

class StaticField {
    final static int foo = 1234;

    static int[] bar = {10, 11, 12, 13, 14};

    int qux;

    static int test() {
        int sum = 0;
        for (int i = 0; i < bar.length; i++) {
            sum += bar[i] * foo;
        }
        return sum;
    }

    public static void main() {
        test();
    }
}
