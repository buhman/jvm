package test;

class TestGC {
    static TestGC static_tgc;
    TestGC instance_tgc;

    static void test() {
        System.out.println("static new TestGC");
        TestGC tgc = new TestGC();
        static_tgc = tgc;
        System.out.println("instance new TestGC");
        tgc.instance_tgc = new TestGC();
        System.out.println("stack new TestGC");
        TestGC stack = new TestGC();
    }

    static void test2() {
        for (int i = 0; i < 100; i++) {
            System.out.print("new TestGC: ");
            System.out.println(i);
            TestGC gc = new TestGC();
        }
    }

    public static void main() {
        test2();
    }
}
