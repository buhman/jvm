package test;

class TestObjectArray {
    static boolean testInstanceEqual() {
        TestObjectArray t1 = new TestObjectArray();
        TestObjectArray t2 = new TestObjectArray();
        TestObjectArray t3 = new TestObjectArray();

        TestObjectArray[] a = {t1, t2, t3};

        return
            a[0] == t1 &&
            a[1] == t2 &&
            a[2] == t3 &&
            a[0] != t2 &&
            a[1] != t3 &&
            a[2] != t1;
    }

    static boolean testEmptyInstanceof() {
        TestObjectArray[] a = new TestObjectArray[1];

        return a instanceof TestObjectArray[];
    }

    static boolean testNullInstanceof() {
        TestObjectArray[] a = null;

        return !(a instanceof TestObjectArray[]);
    }

    public static void main() {
        System.out.print("testInstanceEqual: ");
        System.out.println(testInstanceEqual());

        System.out.print("testEmptyInstanceof: ");
        System.out.println(testEmptyInstanceof());

        System.out.print("testNullInstanceof: ");
        System.out.println(testNullInstanceof());
    }
}
