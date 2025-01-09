package p;

class Exception2 extends Exception {
    public Exception2(String message) {
        super(message);
    }
}

class TestException {
    static void test2() throws Exception2 {
        throw new Exception2("asdf exception");
    }

    static void test() throws Exception2 {
        try {
            test2();
        } catch (Exception e) {
            System.out.print("exception handler: ");
            System.out.println(e);
            throw e;
        }
    }

    public static void main() throws Exception2 {
        test();
    }
}
