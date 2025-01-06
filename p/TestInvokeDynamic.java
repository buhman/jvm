package p;

class TestInvokeDynamic {
    static int test(String a, String b) {
        String c = a + b;
        return c.length();
    }

    public static void main() {
        test("asdf", "qwert");
    }
}
