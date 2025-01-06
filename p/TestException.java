package p;

class TestException {
    static void test2() throws Exception {
        throw new Exception("asdf exception");
    }

    static void test() throws Exception {
        try {
            test2();
        } catch (Exception e) {
            System.out.println(e);
            throw e;
        }
    }

    public static void main() throws Exception {
        test();
    }
}
