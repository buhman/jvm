package p;

class StaticMethodOverloading {
    static int test() {
        return test(4);
    }

    static int test(int a) {
        return test(a, 3);
    }

    static int test(int a, int b) {
        return a * b + 1;
    }

    public static void main() {
        test();
    }
}
