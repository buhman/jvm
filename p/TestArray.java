package p;

class TestArray {
    static char[] test() {
        char[] a = {'a', 'b', 'c', 'd'};
        return a;
    }

    static char test2(char[] c) {
        return (char)((int)(c[0]) * 2);
    }

    public static void main() {
        char[] a = test();
        test2(a);
    }
}
