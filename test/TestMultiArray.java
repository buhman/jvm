package test;

class TestMultiArray {
    static boolean testInstanceof() {
        Object[][] a = new Object[2][3];
        return a instanceof Object[][];
    }

    static boolean testInstanceof2() {
        TestMultiArray[][] a = new TestMultiArray[2][3];
        return a instanceof Object[][];
    }

    public static void main(String[] args) {
        System.out.print("testInstanceof: ");
        System.out.println(testInstanceof());
        System.out.print("testInstanceof2: ");
        System.out.println(testInstanceof2());
    }
}
