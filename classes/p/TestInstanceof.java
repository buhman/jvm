package p;

class TestInstanceof {
    public static boolean test() {
        TestInstanceof t = new TestInstanceof();
        return t instanceof Object;
    }
    public static void main() {
        System.out.println(test());
    }
}
