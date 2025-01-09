package p;

class LongStaticField {
    static long foo = 10;

    static long test() {
        return foo;
    }

    public static void main() {
        test();
    }
}
