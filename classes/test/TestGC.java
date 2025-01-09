package test;

class TestGC {
    static TestGC static_tgc;
    TestGC instance_tgc;

    void main() {
        System.out.println("static new TestGC");
        TestGC tgc = new TestGC();
        static_tgc = tgc;
        System.out.println("instance new TestGC");
        tgc.instance_tgc = new TestGC();
        System.out.println("stack new TestGC");
        TestGC stack = new TestGC();
    }
}
