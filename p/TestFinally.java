package p;

import java.lang.Exception;

class TestFinally {
    static void test() throws Exception {
        try {
            try {
                System.out.println("try");
                throw new Exception("test exception");
            } catch (Exception e) {
                System.out.println("catch");
                throw e;
            } finally {
                System.out.println("finally");
            }
        } catch (Exception e) {
            System.out.println("catch2");
            throw e;
        } finally {
            System.out.println("finally2 asdf");
        }
    }

    public static void main(String[] args) throws Exception {
        test();
    }
}
