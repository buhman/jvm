package test;

class TestClass {
    static void test1() {
        TestClass obj = new TestClass();
        System.out.println(obj.getClass().getName());
    }

    static void test2() {
        TestClass obj = new TestClass();
        System.out.println(obj);
    }

    public static void main() {
        test2();
    }
}
