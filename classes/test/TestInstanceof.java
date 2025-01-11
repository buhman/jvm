package test;

class TestInstanceof {
    static boolean test1() {
        Object[][] a = new Object[1][1];
        return a instanceof Object[][];
    }
    public static void main() {
        System.out.println(test1());
    }
}
