package p;

class TestException {
    static void test() throws Exception {
        throw new Exception("asdf");
    }

    public static void main() throws Exception {
        test();
    }
}
